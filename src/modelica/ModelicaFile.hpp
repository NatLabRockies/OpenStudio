#ifndef MODELICA_MODELICAFILE_H
#define MODELICA_MODELICAFILE_H

#include "ModelicaAPI.hpp"
#include "utilities/core/Filesystem.hpp"
#include <memory>
#include <string>
#include <string_view>
#include <vector>

namespace openstudio::modelica {

namespace detail {
  class ModelicaFileImpl;
  class ClassDefinitionImpl;
  class ConnectClauseImpl;
}  // namespace detail

class ClassDefinition;
class ConnectClause;

/**
 * A parsed Modelica source file backed by the OpenStudio Modelica parser.
 *
 * ModelicaFile owns the parsed token stream and exposes helper methods for
 * interrogating and mutating the class definitions contained in the file.
 */
class MODELICA_API ModelicaFile
{
 public:
  /** Construct a ModelicaFile by reading and parsing the file located at @p path. */
  ModelicaFile(const openstudio::path& path);

  /// @name Special member functions
  /// @{
  /** Copy-construct a ModelicaFile, sharing the underlying implementation. */
  ModelicaFile(const ModelicaFile& other);

  /** Move-construct a ModelicaFile, transferring ownership of the implementation. */
  ModelicaFile(ModelicaFile&& other) noexcept;

  /** Copy-assign a ModelicaFile, sharing the underlying implementation. */
  ModelicaFile& operator=(const ModelicaFile& other);

  /** Move-assign a ModelicaFile, transferring ownership of the implementation. */
  ModelicaFile& operator=(ModelicaFile&& other) noexcept;
  /// @}

  /** Destroy the ModelicaFile. */
  ~ModelicaFile();

  /** Parse Modelica source text, replacing the current contents. */
  void parse(std::string_view text);

  /** Return the raw Modelica source text represented by this file. */
  std::string getText() const;

  /**
   * Return a formatted representation of the parse tree primarily for debugging.
   */
  std::string printTree() const;

  /** Retrieve all top-level class definitions contained in the file. */
  std::vector<ClassDefinition> getClassDefinitions();

  /** Retrieve the class definition whose long class specifier matches @p name. */
  ClassDefinition getClassDefinitionByName(const std::string& name);

  /** Append a new class definition represented by @p text to the file. */
  ClassDefinition addClassDefinition(const std::string& text);

 private:
  // cppcheck-suppress unusedStructMember
  std::shared_ptr<detail::ModelicaFileImpl> m_impl;
};

/**
 * Represents one Modelica class inside the file.
 *
 * Objects you fetch from ModelicaFile automatically stay in sync with the file:
 * after an edit or parse they keep working as long as the class still exists
 * (same long specifier). If the class is deleted or renamed, calling a method
 * simply throws and you can fetch it again via getClassDefinitions().
 */
class MODELICA_API ClassDefinition
{
 public:
  /// @name Construction & Assignment
  /// @{
  /** Create an empty/invalid ClassDefinition handle. */
  ClassDefinition();

  /** Copy-construct a ClassDefinition, sharing the underlying implementation. */
  ClassDefinition(const ClassDefinition& other);

  /** Move-construct a ClassDefinition, transferring ownership of the implementation. */
  ClassDefinition(ClassDefinition&& other) noexcept;

  /** Copy-assign a ClassDefinition, sharing the underlying implementation. */
  ClassDefinition& operator=(const ClassDefinition& other);

  /** Move-assign a ClassDefinition, transferring ownership of the implementation. */
  ClassDefinition& operator=(ClassDefinition&& other) noexcept;
  /// @}

  /** Destroy the ClassDefinition. */
  ~ClassDefinition();

  /** Return the fully-qualified name (long class specifier) of the class. */
  std::string longClassSpecifier() const;

  /** Return the raw Modelica text for this class definition. */
  std::string getText() const;

  /** Append a new component clause, represented by @p text, to the class body. */
  void addComponentClause(const std::string& text) const;

  /** Retrieve all connect_clauses contained in this class definition. */
  std::vector<ConnectClause> getConnectClauses() const;

  /** Append a `connect(@p source, @p target);` statement to the equation section. */
  ConnectClause addConnectClause(const std::string& source, const std::string& target) const;

  /** Remove the first connect clause matching @p source and @p target, returning true on success. */
  bool removeConnectClause(const std::string& source, const std::string& target) const;

  /** Return true if this handle still refers to a live class definition. */
  bool isValid() const;

 private:
  friend class ModelicaFile;
  explicit ClassDefinition(detail::ClassDefinitionImpl* impl);
  detail::ClassDefinitionImpl* implChecked(const char* methodName) const;

  // cppcheck-suppress unusedStructMember
  detail::ClassDefinitionImpl* m_impl;
};

/**
 * Represents a single `connect(lhs, rhs);` statement.
 *
 * Retrieved objects continue to work after edits while the connect clause exists.
 * If the clause is removed, the next call throws so you know to fetch it again with
 * ClassDefinition::getConnectClauses().
 */
class MODELICA_API ConnectClause
{
 public:
  ConnectClause();
  ConnectClause(const ConnectClause& other);
  ConnectClause(ConnectClause&& other) noexcept;
  ConnectClause& operator=(const ConnectClause& other);
  ConnectClause& operator=(ConnectClause&& other) noexcept;
  ~ConnectClause();

  /** Left-hand side component reference of the connect statement. */
  std::string source() const;

  /** Right-hand side component reference of the connect statement. */
  std::string target() const;

  /** Remove this connect clause from the owning class definition. */
  void remove();

  /** Return true if this handle still refers to a live connect clause. */
  bool isValid() const;

 private:
  friend class ClassDefinition;
  explicit ConnectClause(detail::ConnectClauseImpl* impl);
  detail::ConnectClauseImpl* implChecked(const char* methodName) const;

  // cppcheck-suppress unusedStructMember
  detail::ConnectClauseImpl* m_impl;
};

}  // namespace openstudio::modelica

#endif  // MODELICA_MODELICAFILE_H
