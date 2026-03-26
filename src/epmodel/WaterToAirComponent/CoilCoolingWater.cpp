/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "WaterToAirComponent/CoilCoolingWater.hpp"
#include "WaterToAirComponent/CoilCoolingWater_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/Coil_Cooling_Water_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

CoilCoolingWater::CoilCoolingWater(const Model& model) : WaterToAirComponent(CoilCoolingWater::iddObjectType(), model) {}

CoilCoolingWater::CoilCoolingWater(std::shared_ptr<detail::CoilCoolingWater_Impl> impl) : WaterToAirComponent(std::move(impl)) {}

IddObjectType CoilCoolingWater::iddObjectType() {
  return IddObjectType::Coil_Cooling_Water;
}

std::vector<std::string> CoilCoolingWater::typeOfAnalysisValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Coil_Cooling_WaterFields::TypeofAnalysis);
}

std::vector<std::string> CoilCoolingWater::heatExchangerConfigurationValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::Coil_Cooling_WaterFields::HeatExchangerConfiguration);
}

boost::optional<double> CoilCoolingWater::designWaterFlowRate() const {
  return getImpl<detail::CoilCoolingWater_Impl>()->designWaterFlowRate();
}

bool CoilCoolingWater::setDesignWaterFlowRate(double value) {
  return getImpl<detail::CoilCoolingWater_Impl>()->setDesignWaterFlowRate(value);
}

bool CoilCoolingWater::isDesignWaterFlowRateAutosized() const {
  return getImpl<detail::CoilCoolingWater_Impl>()->isDesignWaterFlowRateAutosized();
}

void CoilCoolingWater::autosizeDesignWaterFlowRate() {
  getImpl<detail::CoilCoolingWater_Impl>()->autosizeDesignWaterFlowRate();
}

boost::optional<double> CoilCoolingWater::designAirFlowRate() const {
  return getImpl<detail::CoilCoolingWater_Impl>()->designAirFlowRate();
}

bool CoilCoolingWater::setDesignAirFlowRate(double value) {
  return getImpl<detail::CoilCoolingWater_Impl>()->setDesignAirFlowRate(value);
}

bool CoilCoolingWater::isDesignAirFlowRateAutosized() const {
  return getImpl<detail::CoilCoolingWater_Impl>()->isDesignAirFlowRateAutosized();
}

void CoilCoolingWater::autosizeDesignAirFlowRate() {
  getImpl<detail::CoilCoolingWater_Impl>()->autosizeDesignAirFlowRate();
}

boost::optional<double> CoilCoolingWater::designInletWaterTemperature() const {
  return getImpl<detail::CoilCoolingWater_Impl>()->designInletWaterTemperature();
}

bool CoilCoolingWater::setDesignInletWaterTemperature(double value) {
  return getImpl<detail::CoilCoolingWater_Impl>()->setDesignInletWaterTemperature(value);
}

bool CoilCoolingWater::isDesignInletWaterTemperatureAutosized() const {
  return getImpl<detail::CoilCoolingWater_Impl>()->isDesignInletWaterTemperatureAutosized();
}

void CoilCoolingWater::autosizeDesignInletWaterTemperature() {
  getImpl<detail::CoilCoolingWater_Impl>()->autosizeDesignInletWaterTemperature();
}

boost::optional<double> CoilCoolingWater::designInletAirTemperature() const {
  return getImpl<detail::CoilCoolingWater_Impl>()->designInletAirTemperature();
}

bool CoilCoolingWater::setDesignInletAirTemperature(double value) {
  return getImpl<detail::CoilCoolingWater_Impl>()->setDesignInletAirTemperature(value);
}

bool CoilCoolingWater::isDesignInletAirTemperatureAutosized() const {
  return getImpl<detail::CoilCoolingWater_Impl>()->isDesignInletAirTemperatureAutosized();
}

void CoilCoolingWater::autosizeDesignInletAirTemperature() {
  getImpl<detail::CoilCoolingWater_Impl>()->autosizeDesignInletAirTemperature();
}

boost::optional<double> CoilCoolingWater::designOutletAirTemperature() const {
  return getImpl<detail::CoilCoolingWater_Impl>()->designOutletAirTemperature();
}

bool CoilCoolingWater::setDesignOutletAirTemperature(double value) {
  return getImpl<detail::CoilCoolingWater_Impl>()->setDesignOutletAirTemperature(value);
}

bool CoilCoolingWater::isDesignOutletAirTemperatureAutosized() const {
  return getImpl<detail::CoilCoolingWater_Impl>()->isDesignOutletAirTemperatureAutosized();
}

void CoilCoolingWater::autosizeDesignOutletAirTemperature() {
  getImpl<detail::CoilCoolingWater_Impl>()->autosizeDesignOutletAirTemperature();
}

boost::optional<double> CoilCoolingWater::designInletAirHumidityRatio() const {
  return getImpl<detail::CoilCoolingWater_Impl>()->designInletAirHumidityRatio();
}

bool CoilCoolingWater::setDesignInletAirHumidityRatio(double value) {
  return getImpl<detail::CoilCoolingWater_Impl>()->setDesignInletAirHumidityRatio(value);
}

bool CoilCoolingWater::isDesignInletAirHumidityRatioAutosized() const {
  return getImpl<detail::CoilCoolingWater_Impl>()->isDesignInletAirHumidityRatioAutosized();
}

void CoilCoolingWater::autosizeDesignInletAirHumidityRatio() {
  getImpl<detail::CoilCoolingWater_Impl>()->autosizeDesignInletAirHumidityRatio();
}

boost::optional<double> CoilCoolingWater::designOutletAirHumidityRatio() const {
  return getImpl<detail::CoilCoolingWater_Impl>()->designOutletAirHumidityRatio();
}

bool CoilCoolingWater::setDesignOutletAirHumidityRatio(double value) {
  return getImpl<detail::CoilCoolingWater_Impl>()->setDesignOutletAirHumidityRatio(value);
}

bool CoilCoolingWater::isDesignOutletAirHumidityRatioAutosized() const {
  return getImpl<detail::CoilCoolingWater_Impl>()->isDesignOutletAirHumidityRatioAutosized();
}

void CoilCoolingWater::autosizeDesignOutletAirHumidityRatio() {
  getImpl<detail::CoilCoolingWater_Impl>()->autosizeDesignOutletAirHumidityRatio();
}

std::string CoilCoolingWater::typeOfAnalysis() const {
  return getImpl<detail::CoilCoolingWater_Impl>()->typeOfAnalysis();
}

bool CoilCoolingWater::setTypeOfAnalysis(const std::string& value) {
  return getImpl<detail::CoilCoolingWater_Impl>()->setTypeOfAnalysis(value);
}

std::string CoilCoolingWater::heatExchangerConfiguration() const {
  return getImpl<detail::CoilCoolingWater_Impl>()->heatExchangerConfiguration();
}

bool CoilCoolingWater::setHeatExchangerConfiguration(const std::string& value) {
  return getImpl<detail::CoilCoolingWater_Impl>()->setHeatExchangerConfiguration(value);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

unsigned CoilCoolingWater_Impl::airInletPort() const {
  return openstudio::Coil_Cooling_WaterFields::AirInletNodeName;
}

unsigned CoilCoolingWater_Impl::airOutletPort() const {
  return openstudio::Coil_Cooling_WaterFields::AirOutletNodeName;
}

unsigned CoilCoolingWater_Impl::waterInletPort() const {
  return openstudio::Coil_Cooling_WaterFields::WaterInletNodeName;
}

unsigned CoilCoolingWater_Impl::waterOutletPort() const {
  return openstudio::Coil_Cooling_WaterFields::WaterOutletNodeName;
}

boost::optional<double> CoilCoolingWater_Impl::designWaterFlowRate() const {
  return getDouble(openstudio::Coil_Cooling_WaterFields::DesignWaterFlowRate, true);
}

bool CoilCoolingWater_Impl::setDesignWaterFlowRate(double value) {
  return setDouble(openstudio::Coil_Cooling_WaterFields::DesignWaterFlowRate, value);
}

bool CoilCoolingWater_Impl::isDesignWaterFlowRateAutosized() const {
  if (const auto value = getString(openstudio::Coil_Cooling_WaterFields::DesignWaterFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

void CoilCoolingWater_Impl::autosizeDesignWaterFlowRate() {
  OS_ASSERT(setString(openstudio::Coil_Cooling_WaterFields::DesignWaterFlowRate, "autosize"));
}

boost::optional<double> CoilCoolingWater_Impl::designAirFlowRate() const {
  return getDouble(openstudio::Coil_Cooling_WaterFields::DesignAirFlowRate, true);
}

bool CoilCoolingWater_Impl::setDesignAirFlowRate(double value) {
  return setDouble(openstudio::Coil_Cooling_WaterFields::DesignAirFlowRate, value);
}

bool CoilCoolingWater_Impl::isDesignAirFlowRateAutosized() const {
  if (const auto value = getString(openstudio::Coil_Cooling_WaterFields::DesignAirFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

void CoilCoolingWater_Impl::autosizeDesignAirFlowRate() {
  OS_ASSERT(setString(openstudio::Coil_Cooling_WaterFields::DesignAirFlowRate, "autosize"));
}

boost::optional<double> CoilCoolingWater_Impl::designInletWaterTemperature() const {
  return getDouble(openstudio::Coil_Cooling_WaterFields::DesignInletWaterTemperature, true);
}

bool CoilCoolingWater_Impl::setDesignInletWaterTemperature(double value) {
  return setDouble(openstudio::Coil_Cooling_WaterFields::DesignInletWaterTemperature, value);
}

bool CoilCoolingWater_Impl::isDesignInletWaterTemperatureAutosized() const {
  if (const auto value = getString(openstudio::Coil_Cooling_WaterFields::DesignInletWaterTemperature, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

void CoilCoolingWater_Impl::autosizeDesignInletWaterTemperature() {
  OS_ASSERT(setString(openstudio::Coil_Cooling_WaterFields::DesignInletWaterTemperature, "autosize"));
}

boost::optional<double> CoilCoolingWater_Impl::designInletAirTemperature() const {
  return getDouble(openstudio::Coil_Cooling_WaterFields::DesignInletAirTemperature, true);
}

bool CoilCoolingWater_Impl::setDesignInletAirTemperature(double value) {
  return setDouble(openstudio::Coil_Cooling_WaterFields::DesignInletAirTemperature, value);
}

bool CoilCoolingWater_Impl::isDesignInletAirTemperatureAutosized() const {
  if (const auto value = getString(openstudio::Coil_Cooling_WaterFields::DesignInletAirTemperature, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

void CoilCoolingWater_Impl::autosizeDesignInletAirTemperature() {
  OS_ASSERT(setString(openstudio::Coil_Cooling_WaterFields::DesignInletAirTemperature, "autosize"));
}

boost::optional<double> CoilCoolingWater_Impl::designOutletAirTemperature() const {
  return getDouble(openstudio::Coil_Cooling_WaterFields::DesignOutletAirTemperature, true);
}

bool CoilCoolingWater_Impl::setDesignOutletAirTemperature(double value) {
  return setDouble(openstudio::Coil_Cooling_WaterFields::DesignOutletAirTemperature, value);
}

bool CoilCoolingWater_Impl::isDesignOutletAirTemperatureAutosized() const {
  if (const auto value = getString(openstudio::Coil_Cooling_WaterFields::DesignOutletAirTemperature, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

void CoilCoolingWater_Impl::autosizeDesignOutletAirTemperature() {
  OS_ASSERT(setString(openstudio::Coil_Cooling_WaterFields::DesignOutletAirTemperature, "autosize"));
}

boost::optional<double> CoilCoolingWater_Impl::designInletAirHumidityRatio() const {
  return getDouble(openstudio::Coil_Cooling_WaterFields::DesignInletAirHumidityRatio, true);
}

bool CoilCoolingWater_Impl::setDesignInletAirHumidityRatio(double value) {
  return setDouble(openstudio::Coil_Cooling_WaterFields::DesignInletAirHumidityRatio, value);
}

bool CoilCoolingWater_Impl::isDesignInletAirHumidityRatioAutosized() const {
  if (const auto value = getString(openstudio::Coil_Cooling_WaterFields::DesignInletAirHumidityRatio, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

void CoilCoolingWater_Impl::autosizeDesignInletAirHumidityRatio() {
  OS_ASSERT(setString(openstudio::Coil_Cooling_WaterFields::DesignInletAirHumidityRatio, "autosize"));
}

boost::optional<double> CoilCoolingWater_Impl::designOutletAirHumidityRatio() const {
  return getDouble(openstudio::Coil_Cooling_WaterFields::DesignOutletAirHumidityRatio, true);
}

bool CoilCoolingWater_Impl::setDesignOutletAirHumidityRatio(double value) {
  return setDouble(openstudio::Coil_Cooling_WaterFields::DesignOutletAirHumidityRatio, value);
}

bool CoilCoolingWater_Impl::isDesignOutletAirHumidityRatioAutosized() const {
  if (const auto value = getString(openstudio::Coil_Cooling_WaterFields::DesignOutletAirHumidityRatio, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

void CoilCoolingWater_Impl::autosizeDesignOutletAirHumidityRatio() {
  OS_ASSERT(setString(openstudio::Coil_Cooling_WaterFields::DesignOutletAirHumidityRatio, "autosize"));
}

std::string CoilCoolingWater_Impl::typeOfAnalysis() const {
  const auto value = getString(openstudio::Coil_Cooling_WaterFields::TypeofAnalysis, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilCoolingWater_Impl::setTypeOfAnalysis(const std::string& value) {
  return setString(openstudio::Coil_Cooling_WaterFields::TypeofAnalysis, value);
}

std::string CoilCoolingWater_Impl::heatExchangerConfiguration() const {
  const auto value = getString(openstudio::Coil_Cooling_WaterFields::HeatExchangerConfiguration, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilCoolingWater_Impl::setHeatExchangerConfiguration(const std::string& value) {
  return setString(openstudio::Coil_Cooling_WaterFields::HeatExchangerConfiguration, value);
}

std::vector<std::string> CoilCoolingWater_Impl::typeOfAnalysisValues() const {
  return CoilCoolingWater::typeOfAnalysisValues();
}

std::vector<std::string> CoilCoolingWater_Impl::heatExchangerConfigurationValues() const {
  return CoilCoolingWater::heatExchangerConfigurationValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
