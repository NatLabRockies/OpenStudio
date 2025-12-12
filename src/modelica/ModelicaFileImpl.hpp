#ifndef MODELICA_MODELICAFILE_IMPL_H
#define MODELICA_MODELICAFILE_IMPL_H

#include "modelica/antlr/modelicaLexer.h"
#include "utilities/core/Filesystem.hpp"
#include "utilities/core/Logger.hpp"
#include "antlr/modelicaParser.h"
#include <algorithm>
#include <cassert>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

namespace openstudio::modelica::detail {

class ClassDefinitionImpl;
class ComponentClauseImpl;
class ConnectClauseImpl;
class ModelicaSyntaxWrapper;
//template <typename T>
template <typename T, class Derived>
class ModelicaSyntax;

class ModelicaFileImpl : public std::enable_shared_from_this<ModelicaFileImpl>
{
  template <typename T, class Derived>
  friend class ModelicaSyntax;

 public:
  ModelicaFileImpl(const openstudio::path& path);

  void parse(std::string_view text);

  std::string getText() const;
  std::string printTree() const;

  std::vector<ClassDefinitionImpl*> getClassDefinitions();
  ClassDefinitionImpl* getClassDefinitionByName(const std::string& name);
  ClassDefinitionImpl* addClassDefinition(const std::string& text);

 protected:
  void updateCTX();

  modelicaParser* parser() const;

  template <typename T, class Derived>
  void addModelicaSyntax(ModelicaSyntax<T, Derived>* syntax) {
    m_syntaxStore.emplace_back(syntax);
  }

  template <typename T, class Derived>
  void removeModelicaSyntax(ModelicaSyntax<T, Derived>* syntax) {
    m_syntaxStore.erase(std::remove_if(m_syntaxStore.begin(), m_syntaxStore.end(), [syntax](const auto& wrapper) { return wrapper == syntax; }),
                        m_syntaxStore.end());
  }

 private:
  std::unique_ptr<antlr4::ANTLRInputStream> m_inputStream{nullptr};
  std::unique_ptr<modelicaLexer> m_modelicaLexer{nullptr};
  std::unique_ptr<antlr4::CommonTokenStream> m_tokenStream{nullptr};
  std::unique_ptr<modelicaParser> m_modelicaParser{nullptr};
  std::vector<ModelicaSyntaxWrapper> m_syntaxStore;
  // cppcheck-suppress unusedStructMember
  std::unordered_map<std::string, std::unique_ptr<ClassDefinitionImpl>> m_classDefinitions;
  // cppcheck-suppress unusedStructMember
  std::vector<ClassDefinitionImpl*> m_cachedClassDefinitions;
  bool m_classDefinitionsDirty = true;

  void ensureClassDefinitionCache();
  void rebuildClassDefinitionCache();

  REGISTER_LOGGER("openstudio.modelica.ModelicaFileImpl");
};

template <typename T, class Derived>
class ModelicaSyntax
{
  friend class ModelicaFileImpl;

 public:
  ModelicaSyntax(std::shared_ptr<ModelicaFileImpl> modelicaFile, T* ctx)  // NOLINT
    : m_modelicaFile(std::move(modelicaFile)), m_ctx(ctx), m_id(Derived::idFromCTX(ctx)) {
    if (auto file = m_modelicaFile.lock()) {
      file->addModelicaSyntax(this);
    }
  }
  ModelicaSyntax(const ModelicaSyntax&) = delete;  // NOLINT
  ModelicaSyntax(ModelicaSyntax&&) = default;      // NOLINT
  ModelicaSyntax& operator=(const ModelicaSyntax&) = delete;
  ModelicaSyntax& operator=(ModelicaSyntax&&) = delete;
  virtual ~ModelicaSyntax() {
    if (auto file = m_modelicaFile.lock()) {
      file->removeModelicaSyntax(this);
    }
  }

  std::string getText() const {
    if (auto file = m_modelicaFile.lock()) {
      auto* parser = file->parser();
      if (parser) {
        auto* tokens = dynamic_cast<antlr4::CommonTokenStream*>(parser->getTokenStream());
        if (tokens && ctx()->getStart() && ctx()->getStop()) {
          return tokens->getText(ctx()->getStart(), ctx()->getStop());
        }
      }
    }
    return ctx()->getText();  // fallback
  }

  void updateCTX() {
    auto file = m_modelicaFile.lock();
    if (!file) {
      return;
    }
    auto* parser = file->parser();
    if (!parser) {
      return;
    }
    std::string currentID = id();
    setCTX(nullptr);

    // Find the same class definition in the newly parsed tree
    auto allContexts = antlr4::tree::xpath::XPath::findAll(parser->stored_definition(), std::string(Derived::xpath), parser);

    for (auto* ctx : allContexts) {
      auto* typed_ctx = dynamic_cast<T*>(ctx);
      if (!typed_ctx) {
        continue;
      }
      const auto id = Derived::idFromCTX(typed_ctx);
      if (id == currentID) {
        assert(typed_ctx != nullptr);
        setCTX(typed_ctx);
        break;
      }
    }
    if (!m_ctx) {
      m_active = false;
    }
  }

  std::string id() const {
    return m_id;
  }

  bool isActive() const {
    return m_active;
  }

 protected:
  T* ctx() const {
    return m_ctx;
  }

  void setCTX(T* newCtx) {
    m_ctx = newCtx;
    m_active = (m_ctx != nullptr);
  }

  ModelicaFileImpl* modelicaFile() {
    return m_modelicaFile.lock().get();
  }

  modelicaParser* parser() {
    auto file = m_modelicaFile.lock();
    return file ? file->parser() : nullptr;
  }

  std::shared_ptr<ModelicaFileImpl> modelicaFileShared() const {
    return m_modelicaFile.lock();
  }

 private:
  std::weak_ptr<ModelicaFileImpl> m_modelicaFile;
  T* m_ctx;
  std::string m_id;
  bool m_active = true;
};

// Non-owning type-erased wrapper for ModelicaSyntax templates
class ModelicaSyntaxWrapper
{
 public:
  // Constructor template that accepts any ModelicaSyntax<T>*
  template <typename T, class Derived>
  ModelicaSyntaxWrapper(ModelicaSyntax<T, Derived>* syntax) : m_impl(std::make_unique<Impl<T, Derived>>(syntax)) {}

  // Forward common operations through type erasure
  void updateCTX() {
    m_impl->updateCTX();
  }
  //std::string id() const { return m_impl->id(); }
  //ModelicaFile* modelicaFile() { return m_impl->modelicaFile(); }

  // Comparison operators for removal from store
  template <typename T, class Derived>
  bool operator==(const ModelicaSyntax<T, Derived>* syntax) const {
    return m_impl && m_impl->equals(syntax);
  }

  template <typename T, class Derived>
  bool operator!=(const ModelicaSyntax<T, Derived>* syntax) const {
    return !(*this == syntax);
  }

 private:
  // Abstract base for type erasure
  struct ImplBase
  {
    ImplBase() = default;
    ImplBase(const ImplBase&) = default;
    ImplBase(ImplBase&&) = default;
    ImplBase& operator=(const ImplBase&) = default;
    ImplBase& operator=(ImplBase&&) = default;
    virtual ~ImplBase() = default;
    virtual void updateCTX() = 0;
    virtual bool equals(const void* ptr) const = 0;
  };

  // Concrete implementation that holds a non-owning pointer
  template <typename T, class Derived>
  struct Impl : ImplBase
  {
    ModelicaSyntax<T, Derived>* syntax;  // Non-owning pointer

    explicit Impl(ModelicaSyntax<T, Derived>* s) : syntax(s) {}

    void updateCTX() override {
      if (syntax) {
        syntax->updateCTX();
      }
    }
    //std::string id() const override { return syntax->id(); }
    //ModelicaFile* modelicaFile() override { return syntax->modelicaFile(); }
    bool equals(const void* ptr) const override {
      return syntax == ptr;
    }
  };

  std::unique_ptr<ImplBase> m_impl;
};

class ClassDefinitionImpl : public ModelicaSyntax<modelicaParser::Class_definitionContext, ClassDefinitionImpl>
{
 public:
  friend class ConnectClauseImpl;
  ClassDefinitionImpl(std::shared_ptr<ModelicaFileImpl> modelicaFile, modelicaParser::Class_definitionContext* ctx)
    : ModelicaSyntax<modelicaParser::Class_definitionContext, ClassDefinitionImpl>(std::move(modelicaFile), ctx) {}
  // cppcheck-suppress unusedStructMember
  static constexpr std::string_view xpath = "//class_definition";
  std::string longClassSpecifier() const;

  std::vector<ComponentClauseImpl*> componentClauses();
  void addComponentClause(const std::string& text);
  void markComponentClausesDirty();
  void setClassContext(modelicaParser::Class_definitionContext* ctx);
  std::vector<ConnectClauseImpl*> getConnectClauses();
  ConnectClauseImpl* addConnectClause(const std::string& source, const std::string& target);
  bool removeConnectClause(const std::string& source, const std::string& target);

  static std::string idFromCTX(modelicaParser::Class_definitionContext* ctx);

 private:
  void ensureComponentClauseCache();
  void rebuildComponentClauseCache();
  void deactivateComponentClauses();
  void ensureConnectionCache();
  void rebuildConnectionCache();
  void deactivateConnections();
  void markConnectionsDirty();
  void removeConnectClause(const ConnectClauseImpl* connection);
  modelicaParser::Equation_sectionContext* selectEquationSection() const;
  static std::pair<std::string, std::string> validateAndNormalizeConnectClause(const std::string& source, const std::string& target);

  // cppcheck-suppress unusedStructMember
  std::unordered_map<std::string, std::unique_ptr<ComponentClauseImpl>> m_componentClauses;
  // cppcheck-suppress unusedStructMember
  std::vector<ComponentClauseImpl*> m_cachedComponentClauses;
  bool m_componentClausesDirty = true;
  // cppcheck-suppress unusedStructMember
  std::unordered_map<std::string, std::unique_ptr<ConnectClauseImpl>> m_connections;
  // cppcheck-suppress unusedStructMember
  std::vector<ConnectClauseImpl*> m_cachedConnections;
  bool m_connectionsDirty = true;

  REGISTER_LOGGER("openstudio.modelica.ClassDefinitionImpl");
};

class ComponentClauseImpl : public ModelicaSyntax<modelicaParser::Component_clauseContext, ComponentClauseImpl>
{
 public:
  ComponentClauseImpl(std::shared_ptr<ModelicaFileImpl> modelicaFile, modelicaParser::Component_clauseContext* ctx)
    : ModelicaSyntax<modelicaParser::Component_clauseContext, ComponentClauseImpl>(std::move(modelicaFile), ctx) {}
  // cppcheck-suppress unusedStructMember
  static constexpr std::string_view xpath = "//component_clause";

  //std::vector<ComponentDeclaration> componentDeclarations();
  void setComponentContext(modelicaParser::Component_clauseContext* ctx) {
    setCTX(ctx);
  }

  static std::string idFromCTX(modelicaParser::Component_clauseContext* ctx);
};

class ConnectClauseImpl : public ModelicaSyntax<modelicaParser::Connect_clauseContext, ConnectClauseImpl>
{
 public:
  friend class ClassDefinitionImpl;
  ConnectClauseImpl(std::shared_ptr<ModelicaFileImpl> modelicaFile, ClassDefinitionImpl* owner, modelicaParser::Connect_clauseContext* ctx)
    : ModelicaSyntax<modelicaParser::Connect_clauseContext, ConnectClauseImpl>(std::move(modelicaFile), ctx), m_owner(owner) {}
  // cppcheck-suppress unusedStructMember
  static constexpr std::string_view xpath = "//connect_clause";

  std::string source() const;
  std::string target() const;
  void remove();
  void setConnectClauseContext(modelicaParser::Connect_clauseContext* ctx) {
    setCTX(ctx);
  }
  static std::string idFromCTX(modelicaParser::Connect_clauseContext* ctx);
  static std::string connectionIdFromEndpoints(const std::string& source, const std::string& target);

 private:
  modelicaParser::EquationContext* equationContext() const;

  ClassDefinitionImpl* m_owner;
};

}  // namespace openstudio::modelica::detail

#endif  // MODELICA_MODELICAFILE_IMPL_H
