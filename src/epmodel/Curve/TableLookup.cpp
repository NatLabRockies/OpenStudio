/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "Curve/TableLookup.hpp"
#include "Curve/TableLookup_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/Table_Lookup_FieldEnums.hxx>

#include <vector>
#include <utility>

namespace openstudio {
namespace epmodel {

  namespace detail {

    std::string TableLookup_Impl::normalizationMethod() const {
      auto value = getString(Table_LookupFields::NormalizationMethod, true);
      OS_ASSERT(value);
      return value.get();
    }

    double TableLookup_Impl::normalizationDivisor() const {
      auto value = getDouble(Table_LookupFields::NormalizationDivisor, true);
      OS_ASSERT(value);
      return value.get();
    }

    boost::optional<double> TableLookup_Impl::minimumOutput() const {
      return getDouble(Table_LookupFields::MinimumOutput, true);
    }

    boost::optional<double> TableLookup_Impl::maximumOutput() const {
      return getDouble(Table_LookupFields::MaximumOutput, true);
    }

    std::string TableLookup_Impl::outputUnitType() const {
      auto value = getString(Table_LookupFields::OutputUnitType, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool TableLookup_Impl::setNormalizationMethod(const std::string& normalizationMethod) {
      return setString(Table_LookupFields::NormalizationMethod, normalizationMethod);
    }

    bool TableLookup_Impl::setNormalizationDivisor(double normalizationDivisor) {
      return setDouble(Table_LookupFields::NormalizationDivisor, normalizationDivisor);
    }

    bool TableLookup_Impl::setMinimumOutput(double minimumOutput) {
      return setDouble(Table_LookupFields::MinimumOutput, minimumOutput);
    }

    void TableLookup_Impl::resetMinimumOutput() {
      OS_ASSERT(setString(Table_LookupFields::MinimumOutput, ""));
    }

    bool TableLookup_Impl::setMaximumOutput(double maximumOutput) {
      return setDouble(Table_LookupFields::MaximumOutput, maximumOutput);
    }

    void TableLookup_Impl::resetMaximumOutput() {
      OS_ASSERT(setString(Table_LookupFields::MaximumOutput, ""));
    }

    bool TableLookup_Impl::setOutputUnitType(const std::string& outputUnitType) {
      return setString(Table_LookupFields::OutputUnitType, outputUnitType);
    }

    boost::optional<int> TableLookup_Impl::externalFileColumnNumber() const {
      return getInt(Table_LookupFields::ExternalFileColumnNumber, true);
    }

    bool TableLookup_Impl::setExternalFileColumnNumber(int externalFileColumnNumber) {
      return setInt(Table_LookupFields::ExternalFileColumnNumber, externalFileColumnNumber);
    }

    void TableLookup_Impl::resetExternalFileColumnNumber() {
      OS_ASSERT(setString(Table_LookupFields::ExternalFileColumnNumber, ""));
    }

    boost::optional<int> TableLookup_Impl::externalFileStartingRowNumber() const {
      return getInt(Table_LookupFields::ExternalFileStartingRowNumber, true);
    }

    bool TableLookup_Impl::setExternalFileStartingRowNumber(int externalFileStartingRowNumber) {
      return setInt(Table_LookupFields::ExternalFileStartingRowNumber, externalFileStartingRowNumber);
    }

    void TableLookup_Impl::resetExternalFileStartingRowNumber() {
      OS_ASSERT(setString(Table_LookupFields::ExternalFileStartingRowNumber, ""));
    }

  }  // namespace detail

  TableLookup::TableLookup(const Model& model) : ModelObject(TableLookup::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::TableLookup_Impl>());

    bool ok = true;
    ok = setNormalizationMethod("None");
    OS_ASSERT(ok);
    ok = setNormalizationDivisor(1.0);
    OS_ASSERT(ok);
    ok = setOutputUnitType("Dimensionless");
    OS_ASSERT(ok);
  }

  TableLookup::TableLookup(std::shared_ptr<detail::TableLookup_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType TableLookup::iddObjectType() {
    return IddObjectType::Table_Lookup;
  }

  std::vector<std::string> TableLookup::normalizationMethodValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), Table_LookupFields::NormalizationMethod);
  }

  std::vector<std::string> TableLookup::validNormalizationMethodValues() {
    return normalizationMethodValues();
  }

  std::vector<std::string> TableLookup::outputUnitTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), Table_LookupFields::OutputUnitType);
  }

  std::vector<std::string> TableLookup::validOutputUnitTypeValues() {
    return outputUnitTypeValues();
  }

  std::string TableLookup::normalizationMethod() const {
    return getImpl<detail::TableLookup_Impl>()->normalizationMethod();
  }

  double TableLookup::normalizationDivisor() const {
    return getImpl<detail::TableLookup_Impl>()->normalizationDivisor();
  }

  boost::optional<double> TableLookup::minimumOutput() const {
    return getImpl<detail::TableLookup_Impl>()->minimumOutput();
  }

  boost::optional<double> TableLookup::maximumOutput() const {
    return getImpl<detail::TableLookup_Impl>()->maximumOutput();
  }

  std::string TableLookup::outputUnitType() const {
    return getImpl<detail::TableLookup_Impl>()->outputUnitType();
  }

  bool TableLookup::setNormalizationMethod(const std::string& normalizationMethod) {
    return getImpl<detail::TableLookup_Impl>()->setNormalizationMethod(normalizationMethod);
  }

  bool TableLookup::setNormalizationDivisor(double normalizationDivisor) {
    return getImpl<detail::TableLookup_Impl>()->setNormalizationDivisor(normalizationDivisor);
  }

  bool TableLookup::setMinimumOutput(double minimumOutput) {
    return getImpl<detail::TableLookup_Impl>()->setMinimumOutput(minimumOutput);
  }

  void TableLookup::resetMinimumOutput() {
    getImpl<detail::TableLookup_Impl>()->resetMinimumOutput();
  }

  bool TableLookup::setMaximumOutput(double maximumOutput) {
    return getImpl<detail::TableLookup_Impl>()->setMaximumOutput(maximumOutput);
  }

  void TableLookup::resetMaximumOutput() {
    getImpl<detail::TableLookup_Impl>()->resetMaximumOutput();
  }

  bool TableLookup::setOutputUnitType(const std::string& outputUnitType) {
    return getImpl<detail::TableLookup_Impl>()->setOutputUnitType(outputUnitType);
  }

  boost::optional<int> TableLookup::externalFileColumnNumber() const {
    return getImpl<detail::TableLookup_Impl>()->externalFileColumnNumber();
  }

  bool TableLookup::setExternalFileColumnNumber(int externalFileColumnNumber) {
    return getImpl<detail::TableLookup_Impl>()->setExternalFileColumnNumber(externalFileColumnNumber);
  }

  void TableLookup::resetExternalFileColumnNumber() {
    getImpl<detail::TableLookup_Impl>()->resetExternalFileColumnNumber();
  }

  boost::optional<int> TableLookup::externalFileStartingRowNumber() const {
    return getImpl<detail::TableLookup_Impl>()->externalFileStartingRowNumber();
  }

  bool TableLookup::setExternalFileStartingRowNumber(int externalFileStartingRowNumber) {
    return getImpl<detail::TableLookup_Impl>()->setExternalFileStartingRowNumber(externalFileStartingRowNumber);
  }

  void TableLookup::resetExternalFileStartingRowNumber() {
    getImpl<detail::TableLookup_Impl>()->resetExternalFileStartingRowNumber();
  }

}  // namespace epmodel
}  // namespace openstudio
