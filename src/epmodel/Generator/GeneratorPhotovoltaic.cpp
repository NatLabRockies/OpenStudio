/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "GeneratorPhotovoltaic.hpp"
#include "GeneratorPhotovoltaic_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/Generator_Photovoltaic_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

GeneratorPhotovoltaic::GeneratorPhotovoltaic(const Model& model) : ModelObject(GeneratorPhotovoltaic::iddObjectType(), model) {}

GeneratorPhotovoltaic::GeneratorPhotovoltaic(std::shared_ptr<detail::GeneratorPhotovoltaic_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType GeneratorPhotovoltaic::iddObjectType() {
  return IddObjectType::Generator_Photovoltaic;
}

std::vector<std::string> GeneratorPhotovoltaic::heatTransferIntegrationModeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Generator_PhotovoltaicFields::HeatTransferIntegrationMode);
}

std::string GeneratorPhotovoltaic::heatTransferIntegrationMode() const {
  return getImpl<detail::GeneratorPhotovoltaic_Impl>()->heatTransferIntegrationMode();
}

bool GeneratorPhotovoltaic::isHeatTransferIntegrationModeDefaulted() const {
  return getImpl<detail::GeneratorPhotovoltaic_Impl>()->isHeatTransferIntegrationModeDefaulted();
}

bool GeneratorPhotovoltaic::setHeatTransferIntegrationMode(const std::string& heatTransferIntegrationMode) {
  return getImpl<detail::GeneratorPhotovoltaic_Impl>()->setHeatTransferIntegrationMode(heatTransferIntegrationMode);
}

void GeneratorPhotovoltaic::resetHeatTransferIntegrationMode() {
  getImpl<detail::GeneratorPhotovoltaic_Impl>()->resetHeatTransferIntegrationMode();
}

double GeneratorPhotovoltaic::numberOfModulesInParallel() const {
  return getImpl<detail::GeneratorPhotovoltaic_Impl>()->numberOfModulesInParallel();
}

bool GeneratorPhotovoltaic::isNumberOfModulesInParallelDefaulted() const {
  return getImpl<detail::GeneratorPhotovoltaic_Impl>()->isNumberOfModulesInParallelDefaulted();
}

bool GeneratorPhotovoltaic::setNumberOfModulesInParallel(double numberOfModulesInParallel) {
  return getImpl<detail::GeneratorPhotovoltaic_Impl>()->setNumberOfModulesInParallel(numberOfModulesInParallel);
}

void GeneratorPhotovoltaic::resetNumberOfModulesInParallel() {
  getImpl<detail::GeneratorPhotovoltaic_Impl>()->resetNumberOfModulesInParallel();
}

double GeneratorPhotovoltaic::numberOfModulesInSeries() const {
  return getImpl<detail::GeneratorPhotovoltaic_Impl>()->numberOfModulesInSeries();
}

bool GeneratorPhotovoltaic::isNumberOfModulesInSeriesDefaulted() const {
  return getImpl<detail::GeneratorPhotovoltaic_Impl>()->isNumberOfModulesInSeriesDefaulted();
}

bool GeneratorPhotovoltaic::setNumberOfModulesInSeries(double numberOfModulesInSeries) {
  return getImpl<detail::GeneratorPhotovoltaic_Impl>()->setNumberOfModulesInSeries(numberOfModulesInSeries);
}

void GeneratorPhotovoltaic::resetNumberOfModulesInSeries() {
  getImpl<detail::GeneratorPhotovoltaic_Impl>()->resetNumberOfModulesInSeries();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

std::string GeneratorPhotovoltaic_Impl::heatTransferIntegrationMode() const {
  if (const auto value = getString(openstudio::Generator_PhotovoltaicFields::HeatTransferIntegrationMode, false)) {
    if (!value->empty()) {
      return *value;
    }
  }
  return "Decoupled";
}

bool GeneratorPhotovoltaic_Impl::isHeatTransferIntegrationModeDefaulted() const {
  return isEmpty(openstudio::Generator_PhotovoltaicFields::HeatTransferIntegrationMode);
}

bool GeneratorPhotovoltaic_Impl::setHeatTransferIntegrationMode(const std::string& heatTransferIntegrationMode) {
  return setString(openstudio::Generator_PhotovoltaicFields::HeatTransferIntegrationMode, heatTransferIntegrationMode);
}

void GeneratorPhotovoltaic_Impl::resetHeatTransferIntegrationMode() {
  OS_ASSERT(setString(openstudio::Generator_PhotovoltaicFields::HeatTransferIntegrationMode, ""));
}

double GeneratorPhotovoltaic_Impl::numberOfModulesInParallel() const {
  if (const auto value = getDouble(openstudio::Generator_PhotovoltaicFields::NumberofSeriesStringsinParallel, false)) {
    return *value;
  }
  return 1.0;
}

bool GeneratorPhotovoltaic_Impl::isNumberOfModulesInParallelDefaulted() const {
  return isEmpty(openstudio::Generator_PhotovoltaicFields::NumberofSeriesStringsinParallel);
}

bool GeneratorPhotovoltaic_Impl::setNumberOfModulesInParallel(double numberOfModulesInParallel) {
  return setDouble(openstudio::Generator_PhotovoltaicFields::NumberofSeriesStringsinParallel, numberOfModulesInParallel);
}

void GeneratorPhotovoltaic_Impl::resetNumberOfModulesInParallel() {
  OS_ASSERT(setString(openstudio::Generator_PhotovoltaicFields::NumberofSeriesStringsinParallel, ""));
}

double GeneratorPhotovoltaic_Impl::numberOfModulesInSeries() const {
  if (const auto value = getDouble(openstudio::Generator_PhotovoltaicFields::NumberofModulesinSeries, false)) {
    return *value;
  }
  return 1.0;
}

bool GeneratorPhotovoltaic_Impl::isNumberOfModulesInSeriesDefaulted() const {
  return isEmpty(openstudio::Generator_PhotovoltaicFields::NumberofModulesinSeries);
}

bool GeneratorPhotovoltaic_Impl::setNumberOfModulesInSeries(double numberOfModulesInSeries) {
  return setDouble(openstudio::Generator_PhotovoltaicFields::NumberofModulesinSeries, numberOfModulesInSeries);
}

void GeneratorPhotovoltaic_Impl::resetNumberOfModulesInSeries() {
  OS_ASSERT(setString(openstudio::Generator_PhotovoltaicFields::NumberofModulesinSeries, ""));
}

std::vector<std::string> GeneratorPhotovoltaic_Impl::heatTransferIntegrationModeValues() const {
  return GeneratorPhotovoltaic::heatTransferIntegrationModeValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
