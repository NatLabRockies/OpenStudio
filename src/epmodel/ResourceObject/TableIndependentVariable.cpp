/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ResourceObject/TableIndependentVariable.hpp"
#include "ResourceObject/TableIndependentVariable_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/Table_IndependentVariable_FieldEnums.hxx>

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

    boost::optional<std::string> TableIndependentVariable_Impl::externalFileName() const {
      return getString(Table_IndependentVariableFields::ExternalFileName, true, true);
    }

    bool TableIndependentVariable_Impl::setExternalFileName(const std::string& externalFileName) {
      return setString(Table_IndependentVariableFields::ExternalFileName, externalFileName);
    }

    void TableIndependentVariable_Impl::resetExternalFileName() {
      OS_ASSERT(setString(Table_IndependentVariableFields::ExternalFileName, ""));
    }

    boost::optional<int> TableIndependentVariable_Impl::externalFileColumnNumber() const {
      return getInt(Table_IndependentVariableFields::ExternalFileColumnNumber, true);
    }

    bool TableIndependentVariable_Impl::setExternalFileColumnNumber(int externalFileColumnNumber) {
      return setInt(Table_IndependentVariableFields::ExternalFileColumnNumber, externalFileColumnNumber);
    }

    void TableIndependentVariable_Impl::resetExternalFileColumnNumber() {
      OS_ASSERT(setString(Table_IndependentVariableFields::ExternalFileColumnNumber, ""));
    }

    boost::optional<int> TableIndependentVariable_Impl::externalFileStartingRowNumber() const {
      return getInt(Table_IndependentVariableFields::ExternalFileStartingRowNumber, true);
    }

    bool TableIndependentVariable_Impl::setExternalFileStartingRowNumber(int externalFileStartingRowNumber) {
      return setInt(Table_IndependentVariableFields::ExternalFileStartingRowNumber, externalFileStartingRowNumber);
    }

    void TableIndependentVariable_Impl::resetExternalFileStartingRowNumber() {
      OS_ASSERT(setString(Table_IndependentVariableFields::ExternalFileStartingRowNumber, ""));
    }

  }  // namespace detail

  TableIndependentVariable::TableIndependentVariable(const Model& model) : ModelObject(TableIndependentVariable::iddObjectType(), model) {}

  TableIndependentVariable::TableIndependentVariable(std::shared_ptr<detail::TableIndependentVariable_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType TableIndependentVariable::iddObjectType() {
    return IddObjectType::Table_IndependentVariable;
  }

  std::vector<std::string> TableIndependentVariable::interpolationMethodValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), Table_IndependentVariableFields::InterpolationMethod);
  }

  std::vector<std::string> TableIndependentVariable::extrapolationMethodValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), Table_IndependentVariableFields::ExtrapolationMethod);
  }

  std::vector<std::string> TableIndependentVariable::unitTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), Table_IndependentVariableFields::UnitType);
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

  boost::optional<std::string> TableIndependentVariable::externalFileName() const {
    return getImpl<detail::TableIndependentVariable_Impl>()->externalFileName();
  }

  bool TableIndependentVariable::setExternalFileName(const std::string& externalFileName) {
    return getImpl<detail::TableIndependentVariable_Impl>()->setExternalFileName(externalFileName);
  }

  void TableIndependentVariable::resetExternalFileName() {
    getImpl<detail::TableIndependentVariable_Impl>()->resetExternalFileName();
  }

  boost::optional<int> TableIndependentVariable::externalFileColumnNumber() const {
    return getImpl<detail::TableIndependentVariable_Impl>()->externalFileColumnNumber();
  }

  bool TableIndependentVariable::setExternalFileColumnNumber(int externalFileColumnNumber) {
    return getImpl<detail::TableIndependentVariable_Impl>()->setExternalFileColumnNumber(externalFileColumnNumber);
  }

  void TableIndependentVariable::resetExternalFileColumnNumber() {
    getImpl<detail::TableIndependentVariable_Impl>()->resetExternalFileColumnNumber();
  }

  boost::optional<int> TableIndependentVariable::externalFileStartingRowNumber() const {
    return getImpl<detail::TableIndependentVariable_Impl>()->externalFileStartingRowNumber();
  }

  bool TableIndependentVariable::setExternalFileStartingRowNumber(int externalFileStartingRowNumber) {
    return getImpl<detail::TableIndependentVariable_Impl>()->setExternalFileStartingRowNumber(externalFileStartingRowNumber);
  }

  void TableIndependentVariable::resetExternalFileStartingRowNumber() {
    getImpl<detail::TableIndependentVariable_Impl>()->resetExternalFileStartingRowNumber();
  }

}  // namespace epmodel
}  // namespace openstudio
