/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "WaterToAirComponent/CoilHeatingWater.hpp"
#include "WaterToAirComponent/CoilHeatingWater_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/Coil_Heating_Water_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

CoilHeatingWater::CoilHeatingWater(const Model& model) : WaterToAirComponent(CoilHeatingWater::iddObjectType(), model) {}

CoilHeatingWater::CoilHeatingWater(std::shared_ptr<detail::CoilHeatingWater_Impl> impl) : WaterToAirComponent(std::move(impl)) {}

IddObjectType CoilHeatingWater::iddObjectType() {
  return IddObjectType::Coil_Heating_Water;
}

std::vector<std::string> CoilHeatingWater::performanceInputMethodValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Coil_Heating_WaterFields::PerformanceInputMethod);
}

boost::optional<double> CoilHeatingWater::uFactorTimesAreaValue() const {
  return getImpl<detail::CoilHeatingWater_Impl>()->uFactorTimesAreaValue();
}

bool CoilHeatingWater::setUFactorTimesAreaValue(double value) {
  return getImpl<detail::CoilHeatingWater_Impl>()->setUFactorTimesAreaValue(value);
}

bool CoilHeatingWater::isUFactorTimesAreaValueAutosized() const {
  return getImpl<detail::CoilHeatingWater_Impl>()->isUFactorTimesAreaValueAutosized();
}

void CoilHeatingWater::autosizeUFactorTimesAreaValue() {
  getImpl<detail::CoilHeatingWater_Impl>()->autosizeUFactorTimesAreaValue();
}

boost::optional<double> CoilHeatingWater::maximumWaterFlowRate() const {
  return getImpl<detail::CoilHeatingWater_Impl>()->maximumWaterFlowRate();
}

bool CoilHeatingWater::setMaximumWaterFlowRate(double value) {
  return getImpl<detail::CoilHeatingWater_Impl>()->setMaximumWaterFlowRate(value);
}

bool CoilHeatingWater::isMaximumWaterFlowRateAutosized() const {
  return getImpl<detail::CoilHeatingWater_Impl>()->isMaximumWaterFlowRateAutosized();
}

void CoilHeatingWater::autosizeMaximumWaterFlowRate() {
  getImpl<detail::CoilHeatingWater_Impl>()->autosizeMaximumWaterFlowRate();
}

std::string CoilHeatingWater::performanceInputMethod() const {
  return getImpl<detail::CoilHeatingWater_Impl>()->performanceInputMethod();
}

bool CoilHeatingWater::setPerformanceInputMethod(const std::string& value) {
  return getImpl<detail::CoilHeatingWater_Impl>()->setPerformanceInputMethod(value);
}

boost::optional<double> CoilHeatingWater::ratedCapacity() const {
  return getImpl<detail::CoilHeatingWater_Impl>()->ratedCapacity();
}

bool CoilHeatingWater::setRatedCapacity(double value) {
  return getImpl<detail::CoilHeatingWater_Impl>()->setRatedCapacity(value);
}

bool CoilHeatingWater::isRatedCapacityAutosized() const {
  return getImpl<detail::CoilHeatingWater_Impl>()->isRatedCapacityAutosized();
}

void CoilHeatingWater::autosizeRatedCapacity() {
  getImpl<detail::CoilHeatingWater_Impl>()->autosizeRatedCapacity();
}

double CoilHeatingWater::ratedInletWaterTemperature() const {
  return getImpl<detail::CoilHeatingWater_Impl>()->ratedInletWaterTemperature();
}

bool CoilHeatingWater::setRatedInletWaterTemperature(double value) {
  return getImpl<detail::CoilHeatingWater_Impl>()->setRatedInletWaterTemperature(value);
}

double CoilHeatingWater::ratedInletAirTemperature() const {
  return getImpl<detail::CoilHeatingWater_Impl>()->ratedInletAirTemperature();
}

bool CoilHeatingWater::setRatedInletAirTemperature(double value) {
  return getImpl<detail::CoilHeatingWater_Impl>()->setRatedInletAirTemperature(value);
}

double CoilHeatingWater::ratedOutletWaterTemperature() const {
  return getImpl<detail::CoilHeatingWater_Impl>()->ratedOutletWaterTemperature();
}

bool CoilHeatingWater::setRatedOutletWaterTemperature(double value) {
  return getImpl<detail::CoilHeatingWater_Impl>()->setRatedOutletWaterTemperature(value);
}

double CoilHeatingWater::ratedOutletAirTemperature() const {
  return getImpl<detail::CoilHeatingWater_Impl>()->ratedOutletAirTemperature();
}

bool CoilHeatingWater::setRatedOutletAirTemperature(double value) {
  return getImpl<detail::CoilHeatingWater_Impl>()->setRatedOutletAirTemperature(value);
}

double CoilHeatingWater::ratedRatioForAirAndWaterConvection() const {
  return getImpl<detail::CoilHeatingWater_Impl>()->ratedRatioForAirAndWaterConvection();
}

bool CoilHeatingWater::setRatedRatioForAirAndWaterConvection(double value) {
  return getImpl<detail::CoilHeatingWater_Impl>()->setRatedRatioForAirAndWaterConvection(value);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

unsigned CoilHeatingWater_Impl::airInletPort() const {
  return openstudio::Coil_Heating_WaterFields::AirInletNodeName;
}

unsigned CoilHeatingWater_Impl::airOutletPort() const {
  return openstudio::Coil_Heating_WaterFields::AirOutletNodeName;
}

unsigned CoilHeatingWater_Impl::waterInletPort() const {
  return openstudio::Coil_Heating_WaterFields::WaterInletNodeName;
}

unsigned CoilHeatingWater_Impl::waterOutletPort() const {
  return openstudio::Coil_Heating_WaterFields::WaterOutletNodeName;
}

boost::optional<double> CoilHeatingWater_Impl::uFactorTimesAreaValue() const {
  return getDouble(openstudio::Coil_Heating_WaterFields::UFactorTimesAreaValue, true);
}

bool CoilHeatingWater_Impl::setUFactorTimesAreaValue(double value) {
  return setDouble(openstudio::Coil_Heating_WaterFields::UFactorTimesAreaValue, value);
}

bool CoilHeatingWater_Impl::isUFactorTimesAreaValueAutosized() const {
  if (const auto value = getString(openstudio::Coil_Heating_WaterFields::UFactorTimesAreaValue, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

void CoilHeatingWater_Impl::autosizeUFactorTimesAreaValue() {
  OS_ASSERT(setString(openstudio::Coil_Heating_WaterFields::UFactorTimesAreaValue, "autosize"));
}

boost::optional<double> CoilHeatingWater_Impl::maximumWaterFlowRate() const {
  return getDouble(openstudio::Coil_Heating_WaterFields::MaximumWaterFlowRate, true);
}

bool CoilHeatingWater_Impl::setMaximumWaterFlowRate(double value) {
  return setDouble(openstudio::Coil_Heating_WaterFields::MaximumWaterFlowRate, value);
}

bool CoilHeatingWater_Impl::isMaximumWaterFlowRateAutosized() const {
  if (const auto value = getString(openstudio::Coil_Heating_WaterFields::MaximumWaterFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

void CoilHeatingWater_Impl::autosizeMaximumWaterFlowRate() {
  OS_ASSERT(setString(openstudio::Coil_Heating_WaterFields::MaximumWaterFlowRate, "autosize"));
}

std::string CoilHeatingWater_Impl::performanceInputMethod() const {
  const auto value = getString(openstudio::Coil_Heating_WaterFields::PerformanceInputMethod, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilHeatingWater_Impl::setPerformanceInputMethod(const std::string& value) {
  return setString(openstudio::Coil_Heating_WaterFields::PerformanceInputMethod, value);
}

boost::optional<double> CoilHeatingWater_Impl::ratedCapacity() const {
  return getDouble(openstudio::Coil_Heating_WaterFields::RatedCapacity, true);
}

bool CoilHeatingWater_Impl::setRatedCapacity(double value) {
  return setDouble(openstudio::Coil_Heating_WaterFields::RatedCapacity, value);
}

bool CoilHeatingWater_Impl::isRatedCapacityAutosized() const {
  if (const auto value = getString(openstudio::Coil_Heating_WaterFields::RatedCapacity, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

void CoilHeatingWater_Impl::autosizeRatedCapacity() {
  OS_ASSERT(setString(openstudio::Coil_Heating_WaterFields::RatedCapacity, "autosize"));
}

double CoilHeatingWater_Impl::ratedInletWaterTemperature() const {
  const auto value = getDouble(openstudio::Coil_Heating_WaterFields::RatedInletWaterTemperature, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilHeatingWater_Impl::setRatedInletWaterTemperature(double value) {
  return setDouble(openstudio::Coil_Heating_WaterFields::RatedInletWaterTemperature, value);
}

double CoilHeatingWater_Impl::ratedInletAirTemperature() const {
  const auto value = getDouble(openstudio::Coil_Heating_WaterFields::RatedInletAirTemperature, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilHeatingWater_Impl::setRatedInletAirTemperature(double value) {
  return setDouble(openstudio::Coil_Heating_WaterFields::RatedInletAirTemperature, value);
}

double CoilHeatingWater_Impl::ratedOutletWaterTemperature() const {
  const auto value = getDouble(openstudio::Coil_Heating_WaterFields::RatedOutletWaterTemperature, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilHeatingWater_Impl::setRatedOutletWaterTemperature(double value) {
  return setDouble(openstudio::Coil_Heating_WaterFields::RatedOutletWaterTemperature, value);
}

double CoilHeatingWater_Impl::ratedOutletAirTemperature() const {
  const auto value = getDouble(openstudio::Coil_Heating_WaterFields::RatedOutletAirTemperature, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilHeatingWater_Impl::setRatedOutletAirTemperature(double value) {
  return setDouble(openstudio::Coil_Heating_WaterFields::RatedOutletAirTemperature, value);
}

double CoilHeatingWater_Impl::ratedRatioForAirAndWaterConvection() const {
  const auto value = getDouble(openstudio::Coil_Heating_WaterFields::RatedRatioforAirandWaterConvection, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilHeatingWater_Impl::setRatedRatioForAirAndWaterConvection(double value) {
  return setDouble(openstudio::Coil_Heating_WaterFields::RatedRatioforAirandWaterConvection, value);
}

std::vector<std::string> CoilHeatingWater_Impl::performanceInputMethodValues() const {
  return CoilHeatingWater::performanceInputMethodValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
