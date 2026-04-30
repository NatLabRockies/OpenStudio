/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ResourceObject/TableIndependentVariable.hpp"
#include "ResourceObject/TableIndependentVariable_Impl.hpp"

#include "Curve/TableLookup.hpp"
#include "Curve/TableLookup_Impl.hpp"
#include "Model.hpp"
#include "ModelObject/ModelObject.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idf/IdfExtensibleGroup.hpp>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/Table_IndependentVariable_FieldEnums.hxx>

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

std::string TableIndependentVariable_Impl::interpolationMethod() const {
  auto value = getString(Table_IndependentVariableFields::InterpolationMethod, true);
  OS_ASSERT(value);
  return value.get();
}

bool TableIndependentVariable_Impl::isInterpolationMethodDefaulted() const {
  return isEmpty(Table_IndependentVariableFields::InterpolationMethod);
}

bool TableIndependentVariable_Impl::setInterpolationMethod(const std::string& interpolationMethod) {
  return setString(Table_IndependentVariableFields::InterpolationMethod, interpolationMethod);
}

void TableIndependentVariable_Impl::resetInterpolationMethod() {
  OS_ASSERT(setString(Table_IndependentVariableFields::InterpolationMethod, ""));
}

std::string TableIndependentVariable_Impl::extrapolationMethod() const {
  auto value = getString(Table_IndependentVariableFields::ExtrapolationMethod, true);
  OS_ASSERT(value);
  return value.get();
}

bool TableIndependentVariable_Impl::isExtrapolationMethodDefaulted() const {
  return isEmpty(Table_IndependentVariableFields::ExtrapolationMethod);
}

bool TableIndependentVariable_Impl::setExtrapolationMethod(const std::string& extrapolationMethod) {
  return setString(Table_IndependentVariableFields::ExtrapolationMethod, extrapolationMethod);
}

void TableIndependentVariable_Impl::resetExtrapolationMethod() {
  OS_ASSERT(setString(Table_IndependentVariableFields::ExtrapolationMethod, ""));
}

boost::optional<double> TableIndependentVariable_Impl::minimumValue() const {
  return getDouble(Table_IndependentVariableFields::MinimumValue, true);
}

bool TableIndependentVariable_Impl::setMinimumValue(double minimumValue) {
  return setDouble(Table_IndependentVariableFields::MinimumValue, minimumValue);
}

void TableIndependentVariable_Impl::resetMinimumValue() {
  OS_ASSERT(setString(Table_IndependentVariableFields::MinimumValue, ""));
}

boost::optional<double> TableIndependentVariable_Impl::maximumValue() const {
  return getDouble(Table_IndependentVariableFields::MaximumValue, true);
}

bool TableIndependentVariable_Impl::setMaximumValue(double maximumValue) {
  return setDouble(Table_IndependentVariableFields::MaximumValue, maximumValue);
}

void TableIndependentVariable_Impl::resetMaximumValue() {
  OS_ASSERT(setString(Table_IndependentVariableFields::MaximumValue, ""));
}

boost::optional<double> TableIndependentVariable_Impl::normalizationReferenceValue() const {
  return getDouble(Table_IndependentVariableFields::NormalizationReferenceValue, true);
}

bool TableIndependentVariable_Impl::setNormalizationReferenceValue(double normalizationReferenceValue) {
  return setDouble(Table_IndependentVariableFields::NormalizationReferenceValue, normalizationReferenceValue);
}

void TableIndependentVariable_Impl::resetNormalizationReferenceValue() {
  OS_ASSERT(setString(Table_IndependentVariableFields::NormalizationReferenceValue, ""));
}

std::string TableIndependentVariable_Impl::unitType() const {
  auto value = getString(Table_IndependentVariableFields::UnitType, true);
  OS_ASSERT(value);
  return value.get();
}

bool TableIndependentVariable_Impl::isUnitTypeDefaulted() const {
  return isEmpty(Table_IndependentVariableFields::UnitType);
}

bool TableIndependentVariable_Impl::setUnitType(const std::string& unitType) {
  return setString(Table_IndependentVariableFields::UnitType, unitType);
}

void TableIndependentVariable_Impl::resetUnitType() {
  OS_ASSERT(setString(Table_IndependentVariableFields::UnitType, ""));
}

std::vector<TableLookup> TableIndependentVariable_Impl::tableLookups() const {
  std::vector<TableLookup> result;
  for (const auto& tableLookup : model().getModelObjects<TableLookup>()) {
    for (const auto& independentVariable : tableLookup.independentVariables()) {
      if (independentVariable.handle() == handle()) {
        result.push_back(tableLookup);
        break;
      }
    }
  }
  return result;
}

bool TableIndependentVariable_Impl::addValue(double value) {
  auto group = getObject<ModelObject>().pushExtensibleGroup();
  const bool result = group.setDouble(Table_IndependentVariableExtensibleFields::Value, value);
  if (!result) {
    getObject<ModelObject>().eraseExtensibleGroup(group.groupIndex());
  }
  return result;
}

bool TableIndependentVariable_Impl::removeValue(unsigned groupIndex) {
  if (groupIndex >= numberofValues()) {
    return false;
  }
  getObject<ModelObject>().eraseExtensibleGroup(groupIndex);
  return true;
}

void TableIndependentVariable_Impl::removeAllValues() {
  clearExtensibleGroups();
}

std::vector<double> TableIndependentVariable_Impl::values() const {
  std::vector<double> result;
  for (const auto& group : extensibleGroups()) {
    auto value = group.getDouble(Table_IndependentVariableExtensibleFields::Value);
    OS_ASSERT(value);
    result.push_back(value.get());
  }
  return result;
}

bool TableIndependentVariable_Impl::setValues(const std::vector<double>& values) {
  clearExtensibleGroups();
  bool result = true;
  for (double value : values) {
    result &= addValue(value);
  }
  return result;
}

unsigned TableIndependentVariable_Impl::numberofValues() const {
  return numExtensibleGroups();
}

}  // namespace detail

TableIndependentVariable::TableIndependentVariable(const Model& model) : ResourceObject(TableIndependentVariable::iddObjectType(), model) {
  OS_ASSERT(getImpl<detail::TableIndependentVariable_Impl>());

  bool ok = true;
  ok = setInterpolationMethod("Linear");
  OS_ASSERT(ok);
  ok = setExtrapolationMethod("Constant");
  OS_ASSERT(ok);
  ok = setUnitType("Dimensionless");
  OS_ASSERT(ok);
  getImpl<detail::TableIndependentVariable_Impl>()->removeAllValues();
}

TableIndependentVariable::TableIndependentVariable(std::shared_ptr<detail::TableIndependentVariable_Impl> impl) : ResourceObject(std::move(impl)) {}

IddObjectType TableIndependentVariable::iddObjectType() {
  return IddObjectType::Table_IndependentVariable;
}

std::vector<std::string> TableIndependentVariable::interpolationMethodValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), Table_IndependentVariableFields::InterpolationMethod);
}

std::vector<std::string> TableIndependentVariable::validInterpolationMethodValues() {
  return interpolationMethodValues();
}

std::vector<std::string> TableIndependentVariable::extrapolationMethodValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), Table_IndependentVariableFields::ExtrapolationMethod);
}

std::vector<std::string> TableIndependentVariable::validExtrapolationMethodValues() {
  return extrapolationMethodValues();
}

std::vector<std::string> TableIndependentVariable::unitTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), Table_IndependentVariableFields::UnitType);
}

std::vector<std::string> TableIndependentVariable::validUnitTypeValues() {
  return unitTypeValues();
}

std::string TableIndependentVariable::interpolationMethod() const {
  return getImpl<detail::TableIndependentVariable_Impl>()->interpolationMethod();
}

bool TableIndependentVariable::isInterpolationMethodDefaulted() const {
  return getImpl<detail::TableIndependentVariable_Impl>()->isInterpolationMethodDefaulted();
}

bool TableIndependentVariable::setInterpolationMethod(const std::string& interpolationMethod) {
  return getImpl<detail::TableIndependentVariable_Impl>()->setInterpolationMethod(interpolationMethod);
}

void TableIndependentVariable::resetInterpolationMethod() {
  getImpl<detail::TableIndependentVariable_Impl>()->resetInterpolationMethod();
}

std::string TableIndependentVariable::extrapolationMethod() const {
  return getImpl<detail::TableIndependentVariable_Impl>()->extrapolationMethod();
}

bool TableIndependentVariable::isExtrapolationMethodDefaulted() const {
  return getImpl<detail::TableIndependentVariable_Impl>()->isExtrapolationMethodDefaulted();
}

bool TableIndependentVariable::setExtrapolationMethod(const std::string& extrapolationMethod) {
  return getImpl<detail::TableIndependentVariable_Impl>()->setExtrapolationMethod(extrapolationMethod);
}

void TableIndependentVariable::resetExtrapolationMethod() {
  getImpl<detail::TableIndependentVariable_Impl>()->resetExtrapolationMethod();
}

boost::optional<double> TableIndependentVariable::minimumValue() const {
  return getImpl<detail::TableIndependentVariable_Impl>()->minimumValue();
}

bool TableIndependentVariable::setMinimumValue(double minimumValue) {
  return getImpl<detail::TableIndependentVariable_Impl>()->setMinimumValue(minimumValue);
}

void TableIndependentVariable::resetMinimumValue() {
  getImpl<detail::TableIndependentVariable_Impl>()->resetMinimumValue();
}

boost::optional<double> TableIndependentVariable::maximumValue() const {
  return getImpl<detail::TableIndependentVariable_Impl>()->maximumValue();
}

bool TableIndependentVariable::setMaximumValue(double maximumValue) {
  return getImpl<detail::TableIndependentVariable_Impl>()->setMaximumValue(maximumValue);
}

void TableIndependentVariable::resetMaximumValue() {
  getImpl<detail::TableIndependentVariable_Impl>()->resetMaximumValue();
}

boost::optional<double> TableIndependentVariable::normalizationReferenceValue() const {
  return getImpl<detail::TableIndependentVariable_Impl>()->normalizationReferenceValue();
}

bool TableIndependentVariable::setNormalizationReferenceValue(double normalizationReferenceValue) {
  return getImpl<detail::TableIndependentVariable_Impl>()->setNormalizationReferenceValue(normalizationReferenceValue);
}

void TableIndependentVariable::resetNormalizationReferenceValue() {
  getImpl<detail::TableIndependentVariable_Impl>()->resetNormalizationReferenceValue();
}

std::string TableIndependentVariable::unitType() const {
  return getImpl<detail::TableIndependentVariable_Impl>()->unitType();
}

bool TableIndependentVariable::isUnitTypeDefaulted() const {
  return getImpl<detail::TableIndependentVariable_Impl>()->isUnitTypeDefaulted();
}

bool TableIndependentVariable::setUnitType(const std::string& unitType) {
  return getImpl<detail::TableIndependentVariable_Impl>()->setUnitType(unitType);
}

void TableIndependentVariable::resetUnitType() {
  getImpl<detail::TableIndependentVariable_Impl>()->resetUnitType();
}

std::vector<TableLookup> TableIndependentVariable::tableLookups() const {
  return getImpl<detail::TableIndependentVariable_Impl>()->tableLookups();
}

bool TableIndependentVariable::addValue(double value) {
  return getImpl<detail::TableIndependentVariable_Impl>()->addValue(value);
}

bool TableIndependentVariable::removeValue(unsigned groupIndex) {
  return getImpl<detail::TableIndependentVariable_Impl>()->removeValue(groupIndex);
}

void TableIndependentVariable::removeAllValues() {
  getImpl<detail::TableIndependentVariable_Impl>()->removeAllValues();
}

std::vector<double> TableIndependentVariable::values() const {
  return getImpl<detail::TableIndependentVariable_Impl>()->values();
}

bool TableIndependentVariable::setValues(const std::vector<double>& values) {
  return getImpl<detail::TableIndependentVariable_Impl>()->setValues(values);
}

unsigned TableIndependentVariable::numberofValues() const {
  return getImpl<detail::TableIndependentVariable_Impl>()->numberofValues();
}

}  // namespace epmodel
}  // namespace openstudio
