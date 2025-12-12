#include "ModelicaFile.hpp"
#include "ModelicaFileImpl.hpp"
#include <stdexcept>

namespace openstudio::modelica {

// ModelicaFile implementation

ModelicaFile::ModelicaFile(const openstudio::path& path) : m_impl(std::make_shared<detail::ModelicaFileImpl>(path)) {}

ModelicaFile::ModelicaFile(const ModelicaFile& other) = default;

ModelicaFile::ModelicaFile(ModelicaFile&& other) noexcept = default;

ModelicaFile& ModelicaFile::operator=(const ModelicaFile& other) = default;

ModelicaFile& ModelicaFile::operator=(ModelicaFile&& other) noexcept = default;

ModelicaFile::~ModelicaFile() = default;

void ModelicaFile::parse(std::string_view text) {
  m_impl->parse(text);
}

std::string ModelicaFile::getText() const {
  return m_impl->getText();
}

std::string ModelicaFile::printTree() const {
  return m_impl->printTree();
}

std::vector<ClassDefinition> ModelicaFile::getClassDefinitions() {
  auto implClasses = m_impl->getClassDefinitions();
  std::vector<ClassDefinition> result;
  result.reserve(implClasses.size());

  for (auto* implClass : implClasses) {
    result.emplace_back(ClassDefinition(implClass));
  }

  return result;
}

ClassDefinition ModelicaFile::getClassDefinitionByName(const std::string& name) {
  auto* implClass = m_impl->getClassDefinitionByName(name);
  return ClassDefinition(implClass);
}

ClassDefinition ModelicaFile::addClassDefinition(const std::string& text) {
  auto* implClass = m_impl->addClassDefinition(text);
  return ClassDefinition(implClass);
}

// ClassDefinition implementation

ClassDefinition::ClassDefinition() : m_impl(nullptr) {}

ClassDefinition::ClassDefinition(const ClassDefinition& other) = default;

ClassDefinition::ClassDefinition(ClassDefinition&& other) noexcept = default;

ClassDefinition& ClassDefinition::operator=(const ClassDefinition& other) = default;

ClassDefinition& ClassDefinition::operator=(ClassDefinition&& other) noexcept = default;

ClassDefinition::~ClassDefinition() = default;

ClassDefinition::ClassDefinition(detail::ClassDefinitionImpl* impl) : m_impl(impl) {}

std::string ClassDefinition::longClassSpecifier() const {
  return implChecked("longClassSpecifier")->longClassSpecifier();
}

std::string ClassDefinition::getText() const {
  return implChecked("getText")->getText();
}

void ClassDefinition::addComponentClause(const std::string& text) const {
  implChecked("addComponentClause")->addComponentClause(text);
}

std::vector<ConnectClause> ClassDefinition::getConnectClauses() const {
  auto* impl = implChecked("getConnectClauses");
  auto implConnections = impl->getConnectClauses();
  std::vector<ConnectClause> result;
  result.reserve(implConnections.size());
  for (auto* connection : implConnections) {
    result.emplace_back(ConnectClause(connection));
  }
  return result;
}

ConnectClause ClassDefinition::addConnectClause(const std::string& source, const std::string& target) const {
  auto* implConnection = implChecked("addConnectClause")->addConnectClause(source, target);
  return ConnectClause(implConnection);
}

bool ClassDefinition::removeConnectClause(const std::string& source, const std::string& target) const {
  return implChecked("removeConnectClause")->removeConnectClause(source, target);
}

bool ClassDefinition::isValid() const {
  return m_impl && m_impl->isActive();
}

// ConnectClause implementation

ConnectClause::ConnectClause() : m_impl(nullptr) {}

ConnectClause::ConnectClause(const ConnectClause& other) = default;

ConnectClause::ConnectClause(ConnectClause&& other) noexcept = default;

ConnectClause& ConnectClause::operator=(const ConnectClause& other) = default;

ConnectClause& ConnectClause::operator=(ConnectClause&& other) noexcept = default;

ConnectClause::~ConnectClause() = default;

ConnectClause::ConnectClause(detail::ConnectClauseImpl* impl) : m_impl(impl) {}

std::string ConnectClause::source() const {
  return implChecked("source")->source();
}

std::string ConnectClause::target() const {
  return implChecked("target")->target();
}

void ConnectClause::remove() {
  implChecked("remove")->remove();
  m_impl = nullptr;
}

bool ConnectClause::isValid() const {
  return m_impl && m_impl->isActive();
}

detail::ClassDefinitionImpl* ClassDefinition::implChecked(const char* methodName) const {
  if (!isValid()) {
    throw std::runtime_error(std::string("ClassDefinition handle is no longer valid; reacquire before calling ") + methodName);
  }
  return m_impl;
}

detail::ConnectClauseImpl* ConnectClause::implChecked(const char* methodName) const {
  if (!isValid()) {
    throw std::runtime_error(std::string("ConnectClause handle is no longer valid; reacquire before calling ") + methodName);
  }
  return m_impl;
}

}  // namespace openstudio::modelica
