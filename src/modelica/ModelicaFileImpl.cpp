#include "ModelicaFileImpl.hpp"
#include "antlr/modelicaParser.h"
#include "antlr/modelicaLexer.h"
#include "../utilities/core/Logger.hpp"
#include "../utilities/core/Filesystem.hpp"
#include <antlr4-runtime.h>
#include <antlr4-runtime/tree/xpath/XPath.h>
#include <fmt/core.h>
#include <cctype>
#include <fstream>
#include <sstream>
#include <unordered_set>
#include <utility>

namespace openstudio::modelica::detail {

namespace {
  std::string buildLongClassName(modelicaParser::Long_class_specifierContext* longClass) {
    if (!longClass) {
      return {};
    }
    std::string name;
    const auto& identifiers = longClass->IDENT();
    for (size_t i = 0; i < identifiers.size(); ++i) {
      if (i > 0) {
        name += ".";
      }
      name += identifiers[i]->getText();
    }
    return name;
  }
}  // namespace

ModelicaFileImpl::ModelicaFileImpl(const openstudio::path& path) {
  openstudio::filesystem::ifstream moFile(path, std::ios::in | std::ios::binary);
  if (!moFile.is_open()) {
    LOG_AND_THROW(fmt::format("Unable to open Modelica file '{}'", path.generic_string()));
  }
  std::stringstream buffer;
  buffer << moFile.rdbuf();

  parse(buffer.str());
}

void ModelicaFileImpl::parse(std::string_view text) {
  //m_text = text;

  // Create ANTLR input stream
  m_inputStream = std::make_unique<antlr4::ANTLRInputStream>(text);
  m_modelicaLexer = std::make_unique<modelicaLexer>(m_inputStream.get());
  m_tokenStream = std::make_unique<antlr4::CommonTokenStream>(m_modelicaLexer.get());
  m_modelicaParser = std::make_unique<modelicaParser>(m_tokenStream.get());
  //m_ctx = m_modelicaParser->stored_definition();

  updateCTX();
  m_classDefinitionsDirty = true;
}

modelicaParser* ModelicaFileImpl::parser() const {
  return m_modelicaParser.get();
}

void ModelicaFileImpl::updateCTX() {
  for (auto& syntax : m_syntaxStore) {
    if (syntax) {
      syntax->updateCTX();
    }
  }
}

std::string ModelicaFileImpl::getText() const {
  return m_modelicaParser->getTokenStream()->getText();
}

std::string ModelicaFileImpl::printTree() const {
  std::stringstream ss;

  const std::function<void(antlr4::tree::ParseTree*, antlr4::Parser*, int)> to_s = [&ss, &to_s](antlr4::tree::ParseTree* tree, antlr4::Parser* parser,
                                                                                                int indent) {
    if (!tree) {
      return;
    }

    // Print indentation
    for (int i = 0; i < indent; i++) {
      ss << "  ";
    }

    // Check if the node is a rule (internal) or a leaf (token)
    auto* ruleContext = dynamic_cast<antlr4::ParserRuleContext*>(tree);
    if (ruleContext) {
      // Internal rule node - print rule name
      ss << "rule:  " << parser->getRuleNames()[ruleContext->getRuleIndex()] << std::endl;  // NOLINT
    } else {
      // Leaf token node - print actual token text
      ss << "token: " << tree->getText() << std::endl;  // NOLINT
    }

    // Recursively print children with increased indentation
    for (auto* child : tree->children) {
      to_s(child, parser, indent + 1);
    }
  };

  to_s(m_modelicaParser->stored_definition(), m_modelicaParser.get(), 0);

  return ss.str();
}

void ModelicaFileImpl::ensureClassDefinitionCache() {
  if (!m_classDefinitionsDirty) {
    return;
  }
  rebuildClassDefinitionCache();
  m_classDefinitionsDirty = false;
}

void ModelicaFileImpl::rebuildClassDefinitionCache() {
  m_cachedClassDefinitions.clear();
  if (!m_modelicaParser) {
    return;
  }

  auto class_definitions =
    antlr4::tree::xpath::XPath::findAll(m_modelicaParser->stored_definition(), std::string(ClassDefinitionImpl::xpath), m_modelicaParser.get());

  std::unordered_set<std::string> seenIds;
  auto self = shared_from_this();

  for (auto* ctx : class_definitions) {
    auto* class_def_ctx = dynamic_cast<modelicaParser::Class_definitionContext*>(ctx);
    if (!class_def_ctx || !class_def_ctx->class_specifier() || !class_def_ctx->class_specifier()->long_class_specifier()) {
      continue;
    }

    const std::string id = ClassDefinitionImpl::idFromCTX(class_def_ctx);
    seenIds.insert(id);

    auto it = m_classDefinitions.find(id);
    if (it == m_classDefinitions.end()) {
      auto impl = std::make_unique<ClassDefinitionImpl>(self, class_def_ctx);
      auto* ptr = impl.get();
      m_classDefinitions.emplace(id, std::move(impl));
      ptr->markComponentClausesDirty();
      m_cachedClassDefinitions.push_back(ptr);
    } else {
      auto* ptr = it->second.get();
      ptr->setClassContext(class_def_ctx);
      m_cachedClassDefinitions.push_back(ptr);
    }
  }

  for (auto& [id, impl] : m_classDefinitions) {
    if (!seenIds.contains(id)) {
      impl->setClassContext(nullptr);
    }
  }
}

std::vector<ClassDefinitionImpl*> ModelicaFileImpl::getClassDefinitions() {
  ensureClassDefinitionCache();
  return m_cachedClassDefinitions;
}

ClassDefinitionImpl* ModelicaFileImpl::getClassDefinitionByName(const std::string& name) {
  ensureClassDefinitionCache();
  auto it = m_classDefinitions.find(name);
  if (it == m_classDefinitions.end() || !it->second->isActive()) {
    LOG_AND_THROW("Class definition not found: " + name);
  }
  return it->second.get();
}

ClassDefinitionImpl* ModelicaFileImpl::addClassDefinition(const std::string& text) {
  // First, validate that the new text is a valid class definition
  std::string newClassId;
  try {
    antlr4::ANTLRInputStream testStream(text);
    modelicaLexer testLexer(&testStream);
    antlr4::CommonTokenStream testTokens(&testLexer);
    modelicaParser testParser(&testTokens);

    // Try to parse as a class definition
    auto* classDefCtx = testParser.class_definition();
    if (!classDefCtx || testParser.getNumberOfSyntaxErrors() > 0) {
      LOG_AND_THROW("Invalid class definition syntax: " + text);
    }

    // Only accept long class definitions, reject short class specifiers
    if (!classDefCtx->class_specifier() || !classDefCtx->class_specifier()->long_class_specifier()) {
      LOG_AND_THROW("Only long class definitions are supported, not short class specifiers: " + text);
    }
    newClassId = ClassDefinitionImpl::idFromCTX(classDefCtx);
  } catch (const std::exception& e) {
    LOG_AND_THROW("Failed to parse class definition: " + std::string(e.what()));
  }

  // Get current file content
  std::string currentContent = getText();

  // Find insertion point after the last class definition
  size_t insertPos = currentContent.length();

  // Find all existing class definitions to get the end of the last one
  auto existingClasses = getClassDefinitions();
  if (!existingClasses.empty()) {
    // Get the context of the last class definition
    const auto& lastClass = existingClasses.back();
    auto* lastCtx = lastClass->ctx();

    // Find the end position of the last class in the original text
    auto* stopToken = lastCtx->getStop();
    if (stopToken) {
      size_t endPos = stopToken->getStopIndex() + 1;
      insertPos = endPos;
    }
  }

  // Insert the new class definition after the last one
  currentContent.insert(insertPos, "\n" + text + "\n");

  // Reparse the entire file with new content
  parse(currentContent);
  ensureClassDefinitionCache();
  auto it = m_classDefinitions.find(newClassId);
  if (it == m_classDefinitions.end()) {
    LOG_AND_THROW("Failed to retrieve class definition after insertion");
  }
  return it->second.get();
}

std::string ClassDefinitionImpl::longClassSpecifier() const {
  if (!ctx() || !ctx()->class_specifier() || !ctx()->class_specifier()->long_class_specifier()) {
    return {};
  }
  return buildLongClassName(ctx()->class_specifier()->long_class_specifier());
}

std::vector<ComponentClauseImpl*> ClassDefinitionImpl::componentClauses() {
  ensureComponentClauseCache();
  return m_cachedComponentClauses;
}

void ClassDefinitionImpl::addComponentClause(const std::string& text) {
  try {
    antlr4::ANTLRInputStream testStream(text);
    modelicaLexer testLexer(&testStream);
    antlr4::CommonTokenStream testTokens(&testLexer);
    modelicaParser testParser(&testTokens);
    const auto* componentClauseCtx = testParser.component_clause();
    if (!componentClauseCtx || testParser.getNumberOfSyntaxErrors() > 0) {
      LOG_AND_THROW("Invalid component clause syntax: " + text);
    }
  } catch (const std::exception& e) {
    LOG_AND_THROW("Failed to parse component clause: " + std::string(e.what()));
  }

  // Find insertion point - look for the composition within this class
  auto* composition = ctx()->class_specifier()->long_class_specifier()->composition();
  if (!composition) {
    LOG_AND_THROW("Cannot find composition in class definition");
  }

  // Get the element list (vector of elements)
  auto elementList = composition->element_list();

  // Find the end position - either after the last element or at the composition end
  antlr4::Token* stopToken = nullptr;
  if (!elementList.empty()) {
    // Insert after the last element
    stopToken = elementList.back()->getStop();
  } else {
    // Empty element list, insert at the start of composition
    stopToken = composition->getStart();
  }
  if (!stopToken) {
    LOG_AND_THROW("Cannot determine insertion position for component clause");
  }

  // Get the full file content
  auto file = modelicaFileShared();
  if (!file) {
    LOG_AND_THROW("ModelicaFile is no longer available");
  }

  std::string fullContent = file->getText();

  // Calculate the insertion position using ANTLR token positions
  size_t insertPos = stopToken->getStopIndex() + 1;

  // Insert the new component clause with proper formatting
  fullContent.insert(insertPos, "\n  " + text + "\n");

  // Reparse the entire file
  file->parse(fullContent);
  markComponentClausesDirty();
}

void ClassDefinitionImpl::markComponentClausesDirty() {
  m_componentClausesDirty = true;
}

void ClassDefinitionImpl::setClassContext(modelicaParser::Class_definitionContext* ctx) {
  setCTX(ctx);
  markComponentClausesDirty();
  markConnectionsDirty();
  if (!ctx) {
    deactivateComponentClauses();
    deactivateConnections();
  }
}

void ClassDefinitionImpl::ensureComponentClauseCache() {
  if (!m_componentClausesDirty) {
    return;
  }
  rebuildComponentClauseCache();
  m_componentClausesDirty = false;
}

void ClassDefinitionImpl::rebuildComponentClauseCache() {
  m_cachedComponentClauses.clear();

  auto parserPtr = parser();
  auto* classCtx = ctx();
  if (!parserPtr || !classCtx) {
    deactivateComponentClauses();
    return;
  }

  const auto component_clause = antlr4::tree::xpath::XPath::findAll(classCtx, std::string(ComponentClauseImpl::xpath), parserPtr);
  std::unordered_set<std::string> seenIds;
  auto fileShared = modelicaFileShared();

  for (auto* c : component_clause) {
    auto* component_clause_ctx = dynamic_cast<modelicaParser::Component_clauseContext*>(c);
    if (!component_clause_ctx) {
      continue;
    }
    const std::string id = ComponentClauseImpl::idFromCTX(component_clause_ctx);
    seenIds.insert(id);

    auto it = m_componentClauses.find(id);
    if (it == m_componentClauses.end()) {
      auto impl = std::make_unique<ComponentClauseImpl>(fileShared, component_clause_ctx);
      auto* ptr = impl.get();
      m_componentClauses.emplace(id, std::move(impl));
      m_cachedComponentClauses.push_back(ptr);
    } else {
      auto* ptr = it->second.get();
      ptr->setComponentContext(component_clause_ctx);
      m_cachedComponentClauses.push_back(ptr);
    }
  }

  for (auto& [id, impl] : m_componentClauses) {
    if (!seenIds.contains(id)) {
      impl->setComponentContext(nullptr);
    }
  }
}

void ClassDefinitionImpl::deactivateComponentClauses() {
  for (auto& [id, impl] : m_componentClauses) {
    impl->setComponentContext(nullptr);
  }
  m_cachedComponentClauses.clear();
}

void ClassDefinitionImpl::markConnectionsDirty() {
  m_connectionsDirty = true;
}

std::vector<ConnectClauseImpl*> ClassDefinitionImpl::getConnectClauses() {
  ensureConnectionCache();
  return m_cachedConnections;
}

ConnectClauseImpl* ClassDefinitionImpl::addConnectClause(const std::string& source, const std::string& target) {
  auto normalized = validateAndNormalizeConnectClause(source, target);
  const std::string& normalizedSource = normalized.first;
  const std::string& normalizedTarget = normalized.second;
  const std::string connectionId = ConnectClauseImpl::connectionIdFromEndpoints(normalizedSource, normalizedTarget);

  ensureConnectionCache();
  if (auto it = m_connections.find(connectionId); (it != m_connections.end()) && it->second->isActive()) {
    LOG_AND_THROW("Connection already exists: connect(" + normalizedSource + ", " + normalizedTarget + ")");
  }

  auto* equationSection = selectEquationSection();
  if (!equationSection) {
    LOG_AND_THROW("Cannot find equation section in class definition");
  }

  auto file = modelicaFileShared();
  if (!file) {
    LOG_AND_THROW("ModelicaFile is no longer available");
  }

  std::string fullContent = file->getText();
  std::string connectStatement = "connect(" + normalizedSource + ", " + normalizedTarget + ");";

  size_t insertPos = 0;
  const auto equations = equationSection->equation();
  if (!equations.empty()) {
    auto* lastEq = equations.back();
    auto* stopToken = lastEq->getStop();
    if (!stopToken) {
      LOG_AND_THROW("Cannot determine insertion position for connection");
    }
    insertPos = static_cast<size_t>(stopToken->getStopIndex() + 1);
  } else {
    auto* stopToken = equationSection->getStop();
    if (!stopToken) {
      LOG_AND_THROW("Cannot determine insertion position for connection");
    }
    insertPos = static_cast<size_t>(stopToken->getStopIndex() + 1);
  }

  std::string insertion = "\n  " + connectStatement;
  fullContent.insert(insertPos, insertion);
  fullContent.insert(insertPos + insertion.size(), "\n");

  file->parse(fullContent);
  markConnectionsDirty();
  ensureConnectionCache();
  auto it = m_connections.find(connectionId);
  if (it == m_connections.end()) {
    LOG_AND_THROW("Failed to locate connection after insertion");
  }
  return it->second.get();
}

bool ClassDefinitionImpl::removeConnectClause(const std::string& source, const std::string& target) {
  auto normalized = validateAndNormalizeConnectClause(source, target);
  const std::string connectionId = ConnectClauseImpl::connectionIdFromEndpoints(normalized.first, normalized.second);

  ensureConnectionCache();
  auto it = m_connections.find(connectionId);
  if (it == m_connections.end() || !it->second->isActive()) {
    return false;
  }

  removeConnectClause(it->second.get());
  return true;
}

void ClassDefinitionImpl::ensureConnectionCache() {
  if (!m_connectionsDirty) {
    return;
  }
  rebuildConnectionCache();
  m_connectionsDirty = false;
}

void ClassDefinitionImpl::rebuildConnectionCache() {
  m_cachedConnections.clear();

  auto parserPtr = parser();
  auto* classCtx = ctx();
  if (!parserPtr || !classCtx) {
    deactivateConnections();
    return;
  }

  const auto connectClauses = antlr4::tree::xpath::XPath::findAll(classCtx, std::string(ConnectClauseImpl::xpath), parserPtr);
  std::unordered_set<std::string> seenIds;
  auto file = modelicaFileShared();
  if (!file) {
    deactivateConnections();
    return;
  }

  for (auto* clause : connectClauses) {
    auto* connectCtx = dynamic_cast<modelicaParser::Connect_clauseContext*>(clause);
    if (!connectCtx) {
      continue;
    }
    const std::string id = ConnectClauseImpl::idFromCTX(connectCtx);
    seenIds.insert(id);

    auto it = m_connections.find(id);
    if (it == m_connections.end()) {
      auto impl = std::make_unique<ConnectClauseImpl>(file, this, connectCtx);
      auto* ptr = impl.get();
      m_connections.emplace(id, std::move(impl));
      m_cachedConnections.push_back(ptr);
    } else {
      auto* ptr = it->second.get();
      ptr->setConnectClauseContext(connectCtx);
      m_cachedConnections.push_back(ptr);
    }
  }

  for (auto& [id, impl] : m_connections) {
    if (!seenIds.contains(id)) {
      impl->setConnectClauseContext(nullptr);
    }
  }
}

void ClassDefinitionImpl::deactivateConnections() {
  for (auto& [id, impl] : m_connections) {
    impl->setConnectClauseContext(nullptr);
  }
  m_cachedConnections.clear();
}

void ClassDefinitionImpl::removeConnectClause(const ConnectClauseImpl* connection) {
  if (!connection) {
    return;
  }

  auto* equationCtx = connection->equationContext();
  if (!equationCtx) {
    LOG_AND_THROW("Cannot find equation context for connection removal");
  }

  auto file = modelicaFileShared();
  if (!file) {
    LOG_AND_THROW("ModelicaFile is no longer available");
  }

  auto* startToken = equationCtx->getStart();
  auto* stopToken = equationCtx->getStop();
  if (!startToken || !stopToken) {
    LOG_AND_THROW("Cannot determine connection range for removal");
  }

  std::string fullContent = file->getText();
  size_t startPos = static_cast<size_t>(startToken->getStartIndex());
  size_t endPos = static_cast<size_t>(stopToken->getStopIndex() + 1);

  while (endPos < fullContent.size() && (fullContent[endPos] == ' ' || fullContent[endPos] == '\t')) {
    ++endPos;
  }
  while (endPos < fullContent.size() && (fullContent[endPos] == '\r' || fullContent[endPos] == '\n')) {
    ++endPos;
  }

  while (startPos > 0 && (fullContent[startPos - 1] == ' ' || fullContent[startPos - 1] == '\t')) {
    --startPos;
  }
  if (startPos > 0 && (fullContent[startPos - 1] == '\n')) {
    --startPos;
    if (startPos > 0 && fullContent[startPos - 1] == '\r') {
      --startPos;
    }
  }

  fullContent.erase(startPos, endPos - startPos);
  file->parse(fullContent);
  markConnectionsDirty();
}

modelicaParser::Equation_sectionContext* ClassDefinitionImpl::selectEquationSection() const {
  auto* specifier = ctx()->class_specifier();
  if (!specifier || !specifier->long_class_specifier()) {
    return nullptr;
  }

  auto* composition = specifier->long_class_specifier()->composition();
  if (!composition) {
    return nullptr;
  }

  modelicaParser::Equation_sectionContext* fallback = nullptr;
  const auto sections = composition->equation_section();
  for (auto* section : sections) {
    if (!section) {
      continue;
    }
    auto* start = section->getStart();
    if (start && start->getText() != "initial") {
      return section;
    }
    if (!fallback) {
      fallback = section;
    }
  }
  return fallback;
}

std::pair<std::string, std::string> ClassDefinitionImpl::validateAndNormalizeConnectClause(const std::string& source, const std::string& target) {
  try {
    std::string clause = "connect(" + source + "," + target + ")";
    antlr4::ANTLRInputStream testStream(clause);
    modelicaLexer testLexer(&testStream);
    antlr4::CommonTokenStream testTokens(&testLexer);
    modelicaParser testParser(&testTokens);
    auto* connectCtx = testParser.connect_clause();
    if (!connectCtx || testParser.getNumberOfSyntaxErrors() > 0) {
      LOG_AND_THROW("Invalid connection syntax: " + clause);
    }
    auto refs = connectCtx->component_reference();
    if (refs.size() != 2) {
      LOG_AND_THROW("Connection must reference two components: " + clause);
    }
    return {refs[0]->getText(), refs[1]->getText()};
  } catch (const std::exception& e) {
    LOG_AND_THROW("Failed to parse connection clause: " + std::string(e.what()));
  }
}

std::string ClassDefinitionImpl::idFromCTX(modelicaParser::Class_definitionContext* ctx) {
  auto* specifier = ctx->class_specifier();
  if (!specifier) {
    LOG_AND_THROW("ClassDefinition context has null class_specifier");
  }

  if (!specifier->long_class_specifier()) {
    LOG_AND_THROW("ClassDefinition context has null long_class_specifier");
  }

  return buildLongClassName(specifier->long_class_specifier());
}

std::string ComponentClauseImpl::idFromCTX(modelicaParser::Component_clauseContext* ctx) {
  if (!ctx) {
    return "";
  }

  std::string id;

  // Find the containing class definition to make this globally unique
  auto* parent = ctx->parent;
  while (parent) {
    auto* classDefCtx = dynamic_cast<modelicaParser::Class_definitionContext*>(parent);
    if (classDefCtx) {
      // Found the containing class, use its name as a prefix
      auto* specifier = classDefCtx->class_specifier();
      if (specifier && specifier->long_class_specifier()) {
        id = buildLongClassName(specifier->long_class_specifier()) + "::";
      }
      break;
    }
    parent = parent->parent;
  }

  // Get the type specifier (e.g., "Real", "parameter Real", "Modelica.Units.SI.Temperature")
  if (ctx->type_specifier()) {
    id += ctx->type_specifier()->getText();
  }

  // Get the first component declaration name to make it unique within the class
  if ((ctx->component_list() != nullptr) && !ctx->component_list()->component_declaration().empty()) {
    auto* firstComponent = ctx->component_list()->component_declaration()[0];
    if (firstComponent && firstComponent->declaration() && firstComponent->declaration()->IDENT()) {
      id += "::" + firstComponent->declaration()->IDENT()->getText();
    }
  }

  return id;
}

std::string ConnectClauseImpl::source() const {
  if (!ctx()) {
    return "";
  }
  const auto refs = ctx()->component_reference();
  if (refs.empty()) {
    return "";
  }
  return refs[0]->getText();
}

std::string ConnectClauseImpl::target() const {
  if (!ctx()) {
    return "";
  }
  const auto refs = ctx()->component_reference();
  if (refs.size() < 2) {
    return "";
  }
  return refs[1]->getText();
}

void ConnectClauseImpl::remove() {
  if (m_owner) {
    m_owner->removeConnectClause(this);
  }
}

std::string ConnectClauseImpl::idFromCTX(modelicaParser::Connect_clauseContext* ctx) {
  if (!ctx) {
    return "";
  }
  const auto refs = ctx->component_reference();
  if (refs.size() != 2) {
    return "";
  }
  return connectionIdFromEndpoints(refs[0]->getText(), refs[1]->getText());
}

std::string ConnectClauseImpl::connectionIdFromEndpoints(const std::string& source, const std::string& target) {
  return source + "->" + target;
}

modelicaParser::EquationContext* ConnectClauseImpl::equationContext() const {
  auto* parentCtx = ctx() ? ctx()->parent : nullptr;
  while (parentCtx) {
    if (auto* equationCtx = dynamic_cast<modelicaParser::EquationContext*>(parentCtx)) {
      return equationCtx;
    }
    parentCtx = parentCtx->parent;
  }
  return nullptr;
}

//std::vector<ComponentDeclaration> ComponentClause::componentDeclarations() {
//  std::vector<ComponentDeclaration> result;
//
//  const auto component_declarations = antlr4::tree::xpath::XPath::findAll(ctx(), "//Component_declaration", parser());
//
//  for (auto* c : component_declarations) {
//    auto* component_declaration_ctx = dynamic_cast<modelicaParser::Component_declarationContext*>(c);
//    assert(component_declaration_ctx != nullptr);
//    result.emplace_back(modelicaFile(), component_declaration_ctx);  // NOLINT
//  }
//
//  return result;
//}

//std::string ComponentDeclaration::idFromCTX([[maybe_unused]] modelicaParser::Component_declarationContext* ctx) {
//  // TODO
//  return "";
//}

//std::vector<Declaration> ClassDefinition::declarations() {
//  class_definition::GetDeclarationsVisitor v;
//  v.visit(m_ctx);
//  return v.getResult();
//}
//
//void ClassDefinition::addDeclaration(const std::string& declarationText) {
//  const auto el = m_ctx->class_specifier()->long_class_specifier()->composition()->element_list();
//
//  antlr4::ANTLRInputStream input(declarationText + ";");  // Ensure it's a complete statement
//  modelicaLexer lexer(&input);
//  antlr4::CommonTokenStream tempTokens(&lexer);
//  modelicaParser tempParser(&tempTokens);
//
//  [[maybe_unused]] const auto* component = tempParser.component_clause();
//
//  // Attempt to parse as a component_clause (variable declaration)
//  modelicaParser::Component_clauseContext* parsedDecl = nullptr;
//}
//
//Declaration::Declaration(modelicaParser::DeclarationContext* ctx) : m_ctx(ctx) {}
//
//std::string Declaration::name() const {
//  return m_ctx->IDENT()->getText();
//}

}  // namespace openstudio::modelica::detail
