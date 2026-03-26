/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "WaterToWaterComponent/ChillerElectricASHRAE205.hpp"
#include "WaterToWaterComponent/ChillerElectricASHRAE205_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/Chiller_Electric_ASHRAE205_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>

namespace openstudio {
namespace epmodel {

ChillerElectricASHRAE205::ChillerElectricASHRAE205(const Model& model)
  : WaterToWaterComponent(ChillerElectricASHRAE205::iddObjectType(), model) {}

ChillerElectricASHRAE205::ChillerElectricASHRAE205(std::shared_ptr<detail::ChillerElectricASHRAE205_Impl> impl)
  : WaterToWaterComponent(std::move(impl)) {}

IddObjectType ChillerElectricASHRAE205::iddObjectType() {
  return IddObjectType::Chiller_Electric_ASHRAE205;
}

std::vector<std::string> ChillerElectricASHRAE205::performanceInterpolationMethodValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::Chiller_Electric_ASHRAE205Fields::PerformanceInterpolationMethod);
}

std::vector<std::string> ChillerElectricASHRAE205::ambientTemperatureIndicatorValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::Chiller_Electric_ASHRAE205Fields::AmbientTemperatureIndicator);
}

std::vector<std::string> ChillerElectricASHRAE205::chillerFlowModeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::Chiller_Electric_ASHRAE205Fields::ChillerFlowMode);
}

std::string ChillerElectricASHRAE205::performanceInterpolationMethod() const {
  return getImpl<detail::ChillerElectricASHRAE205_Impl>()->performanceInterpolationMethod();
}

bool ChillerElectricASHRAE205::setPerformanceInterpolationMethod(const std::string& performanceInterpolationMethod) {
  return getImpl<detail::ChillerElectricASHRAE205_Impl>()->setPerformanceInterpolationMethod(performanceInterpolationMethod);
}

boost::optional<double> ChillerElectricASHRAE205::ratedCapacity() const {
  return getImpl<detail::ChillerElectricASHRAE205_Impl>()->ratedCapacity();
}

bool ChillerElectricASHRAE205::isRatedCapacityAutosized() const {
  return getImpl<detail::ChillerElectricASHRAE205_Impl>()->isRatedCapacityAutosized();
}

bool ChillerElectricASHRAE205::setRatedCapacity(double ratedCapacity) {
  return getImpl<detail::ChillerElectricASHRAE205_Impl>()->setRatedCapacity(ratedCapacity);
}

void ChillerElectricASHRAE205::autosizeRatedCapacity() {
  getImpl<detail::ChillerElectricASHRAE205_Impl>()->autosizeRatedCapacity();
}

double ChillerElectricASHRAE205::sizingFactor() const {
  return getImpl<detail::ChillerElectricASHRAE205_Impl>()->sizingFactor();
}

bool ChillerElectricASHRAE205::setSizingFactor(double sizingFactor) {
  return getImpl<detail::ChillerElectricASHRAE205_Impl>()->setSizingFactor(sizingFactor);
}

std::string ChillerElectricASHRAE205::ambientTemperatureIndicator() const {
  return getImpl<detail::ChillerElectricASHRAE205_Impl>()->ambientTemperatureIndicator();
}

boost::optional<std::string> ChillerElectricASHRAE205::ambientTemperatureOutdoorAirNodeName() const {
  return getImpl<detail::ChillerElectricASHRAE205_Impl>()->ambientTemperatureOutdoorAirNodeName();
}

bool ChillerElectricASHRAE205::setAmbientTemperatureOutdoorAirNodeName(const std::string& ambientTemperatureOutdoorAirNodeName) {
  return getImpl<detail::ChillerElectricASHRAE205_Impl>()->setAmbientTemperatureOutdoorAirNodeName(ambientTemperatureOutdoorAirNodeName);
}

void ChillerElectricASHRAE205::resetAmbientTemperatureOutdoorAirNodeName() {
  getImpl<detail::ChillerElectricASHRAE205_Impl>()->resetAmbientTemperatureOutdoorAirNodeName();
}

boost::optional<double> ChillerElectricASHRAE205::chilledWaterMaximumRequestedFlowRate() const {
  return getImpl<detail::ChillerElectricASHRAE205_Impl>()->chilledWaterMaximumRequestedFlowRate();
}

bool ChillerElectricASHRAE205::isChilledWaterMaximumRequestedFlowRateAutosized() const {
  return getImpl<detail::ChillerElectricASHRAE205_Impl>()->isChilledWaterMaximumRequestedFlowRateAutosized();
}

bool ChillerElectricASHRAE205::setChilledWaterMaximumRequestedFlowRate(double chilledWaterMaximumRequestedFlowRate) {
  return getImpl<detail::ChillerElectricASHRAE205_Impl>()->setChilledWaterMaximumRequestedFlowRate(chilledWaterMaximumRequestedFlowRate);
}

void ChillerElectricASHRAE205::autosizeChilledWaterMaximumRequestedFlowRate() {
  getImpl<detail::ChillerElectricASHRAE205_Impl>()->autosizeChilledWaterMaximumRequestedFlowRate();
}

boost::optional<double> ChillerElectricASHRAE205::condenserMaximumRequestedFlowRate() const {
  return getImpl<detail::ChillerElectricASHRAE205_Impl>()->condenserMaximumRequestedFlowRate();
}

bool ChillerElectricASHRAE205::isCondenserMaximumRequestedFlowRateAutosized() const {
  return getImpl<detail::ChillerElectricASHRAE205_Impl>()->isCondenserMaximumRequestedFlowRateAutosized();
}

bool ChillerElectricASHRAE205::setCondenserMaximumRequestedFlowRate(double condenserMaximumRequestedFlowRate) {
  return getImpl<detail::ChillerElectricASHRAE205_Impl>()->setCondenserMaximumRequestedFlowRate(condenserMaximumRequestedFlowRate);
}

void ChillerElectricASHRAE205::autosizeCondenserMaximumRequestedFlowRate() {
  getImpl<detail::ChillerElectricASHRAE205_Impl>()->autosizeCondenserMaximumRequestedFlowRate();
}

std::string ChillerElectricASHRAE205::chillerFlowMode() const {
  return getImpl<detail::ChillerElectricASHRAE205_Impl>()->chillerFlowMode();
}

bool ChillerElectricASHRAE205::setChillerFlowMode(const std::string& chillerFlowMode) {
  return getImpl<detail::ChillerElectricASHRAE205_Impl>()->setChillerFlowMode(chillerFlowMode);
}

boost::optional<double> ChillerElectricASHRAE205::oilCoolerDesignFlowRate() const {
  return getImpl<detail::ChillerElectricASHRAE205_Impl>()->oilCoolerDesignFlowRate();
}

bool ChillerElectricASHRAE205::setOilCoolerDesignFlowRate(double oilCoolerDesignFlowRate) {
  return getImpl<detail::ChillerElectricASHRAE205_Impl>()->setOilCoolerDesignFlowRate(oilCoolerDesignFlowRate);
}

void ChillerElectricASHRAE205::resetOilCoolerDesignFlowRate() {
  getImpl<detail::ChillerElectricASHRAE205_Impl>()->resetOilCoolerDesignFlowRate();
}

boost::optional<double> ChillerElectricASHRAE205::auxiliaryCoolingDesignFlowRate() const {
  return getImpl<detail::ChillerElectricASHRAE205_Impl>()->auxiliaryCoolingDesignFlowRate();
}

bool ChillerElectricASHRAE205::setAuxiliaryCoolingDesignFlowRate(double auxiliaryCoolingDesignFlowRate) {
  return getImpl<detail::ChillerElectricASHRAE205_Impl>()->setAuxiliaryCoolingDesignFlowRate(auxiliaryCoolingDesignFlowRate);
}

void ChillerElectricASHRAE205::resetAuxiliaryCoolingDesignFlowRate() {
  getImpl<detail::ChillerElectricASHRAE205_Impl>()->resetAuxiliaryCoolingDesignFlowRate();
}

std::string ChillerElectricASHRAE205::endUseSubcategory() const {
  return getImpl<detail::ChillerElectricASHRAE205_Impl>()->endUseSubcategory();
}

bool ChillerElectricASHRAE205::isEndUseSubcategoryDefaulted() const {
  return getImpl<detail::ChillerElectricASHRAE205_Impl>()->isEndUseSubcategoryDefaulted();
}

bool ChillerElectricASHRAE205::setEndUseSubcategory(const std::string& endUseSubcategory) {
  return getImpl<detail::ChillerElectricASHRAE205_Impl>()->setEndUseSubcategory(endUseSubcategory);
}

void ChillerElectricASHRAE205::resetEndUseSubcategory() {
  getImpl<detail::ChillerElectricASHRAE205_Impl>()->resetEndUseSubcategory();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

std::string ChillerElectricASHRAE205_Impl::performanceInterpolationMethod() const {
  const auto value = getString(openstudio::Chiller_Electric_ASHRAE205Fields::PerformanceInterpolationMethod, true);
  OS_ASSERT(value);
  return *value;
}

bool ChillerElectricASHRAE205_Impl::setPerformanceInterpolationMethod(const std::string& performanceInterpolationMethod) {
  const bool result = setString(openstudio::Chiller_Electric_ASHRAE205Fields::PerformanceInterpolationMethod, performanceInterpolationMethod);
  return result;
}

boost::optional<double> ChillerElectricASHRAE205_Impl::ratedCapacity() const {
  return getDouble(openstudio::Chiller_Electric_ASHRAE205Fields::RatedCapacity, true);
}

bool ChillerElectricASHRAE205_Impl::isRatedCapacityAutosized() const {
  if (auto value = getString(openstudio::Chiller_Electric_ASHRAE205Fields::RatedCapacity, true)) {
    return openstudio::istringEqual(*value, "Autosize");
  }
  return false;
}

bool ChillerElectricASHRAE205_Impl::setRatedCapacity(double ratedCapacity) {
  const bool result = setDouble(openstudio::Chiller_Electric_ASHRAE205Fields::RatedCapacity, ratedCapacity);
  return result;
}

void ChillerElectricASHRAE205_Impl::autosizeRatedCapacity() {
  OS_ASSERT(setString(openstudio::Chiller_Electric_ASHRAE205Fields::RatedCapacity, "Autosize"));
}

double ChillerElectricASHRAE205_Impl::sizingFactor() const {
  const auto value = getDouble(openstudio::Chiller_Electric_ASHRAE205Fields::SizingFactor, true);
  OS_ASSERT(value);
  return *value;
}

bool ChillerElectricASHRAE205_Impl::setSizingFactor(double sizingFactor) {
  const bool result = setDouble(openstudio::Chiller_Electric_ASHRAE205Fields::SizingFactor, sizingFactor);
  return result;
}

std::string ChillerElectricASHRAE205_Impl::ambientTemperatureIndicator() const {
  const auto value = getString(openstudio::Chiller_Electric_ASHRAE205Fields::AmbientTemperatureIndicator, true);
  OS_ASSERT(value);
  return *value;
}

bool ChillerElectricASHRAE205_Impl::setAmbientTemperatureIndicator(const std::string& ambientTemperatureIndicator) {
  const bool result = setString(openstudio::Chiller_Electric_ASHRAE205Fields::AmbientTemperatureIndicator, ambientTemperatureIndicator);
  return result;
}

boost::optional<std::string> ChillerElectricASHRAE205_Impl::ambientTemperatureOutdoorAirNodeName() const {
  return getString(openstudio::Chiller_Electric_ASHRAE205Fields::AmbientTemperatureOutdoorAirNodeName, false);
}

bool ChillerElectricASHRAE205_Impl::setAmbientTemperatureOutdoorAirNodeName(const std::string& ambientTemperatureOutdoorAirNodeName) {
  const bool result = setString(openstudio::Chiller_Electric_ASHRAE205Fields::AmbientTemperatureOutdoorAirNodeName,
                                ambientTemperatureOutdoorAirNodeName);
  if (result) {
    const bool ok = setAmbientTemperatureIndicator("Outdoors");
    OS_ASSERT(ok);
  }
  return result;
}

void ChillerElectricASHRAE205_Impl::resetAmbientTemperatureOutdoorAirNodeName() {
  OS_ASSERT(setString(openstudio::Chiller_Electric_ASHRAE205Fields::AmbientTemperatureOutdoorAirNodeName, ""));
}

boost::optional<double> ChillerElectricASHRAE205_Impl::chilledWaterMaximumRequestedFlowRate() const {
  return getDouble(openstudio::Chiller_Electric_ASHRAE205Fields::ChilledWaterMaximumRequestedFlowRate, true);
}

bool ChillerElectricASHRAE205_Impl::isChilledWaterMaximumRequestedFlowRateAutosized() const {
  if (auto value = getString(openstudio::Chiller_Electric_ASHRAE205Fields::ChilledWaterMaximumRequestedFlowRate, true)) {
    return openstudio::istringEqual(*value, "Autosize");
  }
  return false;
}

bool ChillerElectricASHRAE205_Impl::setChilledWaterMaximumRequestedFlowRate(double chilledWaterMaximumRequestedFlowRate) {
  const bool result =
    setDouble(openstudio::Chiller_Electric_ASHRAE205Fields::ChilledWaterMaximumRequestedFlowRate, chilledWaterMaximumRequestedFlowRate);
  return result;
}

void ChillerElectricASHRAE205_Impl::autosizeChilledWaterMaximumRequestedFlowRate() {
  OS_ASSERT(setString(openstudio::Chiller_Electric_ASHRAE205Fields::ChilledWaterMaximumRequestedFlowRate, "Autosize"));
}

boost::optional<double> ChillerElectricASHRAE205_Impl::condenserMaximumRequestedFlowRate() const {
  return getDouble(openstudio::Chiller_Electric_ASHRAE205Fields::CondenserMaximumRequestedFlowRate, true);
}

bool ChillerElectricASHRAE205_Impl::isCondenserMaximumRequestedFlowRateAutosized() const {
  if (auto value = getString(openstudio::Chiller_Electric_ASHRAE205Fields::CondenserMaximumRequestedFlowRate, true)) {
    return openstudio::istringEqual(*value, "Autosize");
  }
  return false;
}

bool ChillerElectricASHRAE205_Impl::setCondenserMaximumRequestedFlowRate(double condenserMaximumRequestedFlowRate) {
  const bool result =
    setDouble(openstudio::Chiller_Electric_ASHRAE205Fields::CondenserMaximumRequestedFlowRate, condenserMaximumRequestedFlowRate);
  return result;
}

void ChillerElectricASHRAE205_Impl::autosizeCondenserMaximumRequestedFlowRate() {
  OS_ASSERT(setString(openstudio::Chiller_Electric_ASHRAE205Fields::CondenserMaximumRequestedFlowRate, "Autosize"));
}

std::string ChillerElectricASHRAE205_Impl::chillerFlowMode() const {
  const auto value = getString(openstudio::Chiller_Electric_ASHRAE205Fields::ChillerFlowMode, true);
  OS_ASSERT(value);
  return *value;
}

bool ChillerElectricASHRAE205_Impl::setChillerFlowMode(const std::string& chillerFlowMode) {
  const bool result = setString(openstudio::Chiller_Electric_ASHRAE205Fields::ChillerFlowMode, chillerFlowMode);
  return result;
}

boost::optional<double> ChillerElectricASHRAE205_Impl::oilCoolerDesignFlowRate() const {
  return getDouble(openstudio::Chiller_Electric_ASHRAE205Fields::OilCoolerDesignFlowRate, true);
}

bool ChillerElectricASHRAE205_Impl::setOilCoolerDesignFlowRate(double oilCoolerDesignFlowRate) {
  const bool result = setDouble(openstudio::Chiller_Electric_ASHRAE205Fields::OilCoolerDesignFlowRate, oilCoolerDesignFlowRate);
  return result;
}

void ChillerElectricASHRAE205_Impl::resetOilCoolerDesignFlowRate() {
  OS_ASSERT(setString(openstudio::Chiller_Electric_ASHRAE205Fields::OilCoolerDesignFlowRate, ""));
}

boost::optional<double> ChillerElectricASHRAE205_Impl::auxiliaryCoolingDesignFlowRate() const {
  return getDouble(openstudio::Chiller_Electric_ASHRAE205Fields::AuxiliaryCoolingDesignFlowRate, true);
}

bool ChillerElectricASHRAE205_Impl::setAuxiliaryCoolingDesignFlowRate(double auxiliaryCoolingDesignFlowRate) {
  const bool result =
    setDouble(openstudio::Chiller_Electric_ASHRAE205Fields::AuxiliaryCoolingDesignFlowRate, auxiliaryCoolingDesignFlowRate);
  return result;
}

void ChillerElectricASHRAE205_Impl::resetAuxiliaryCoolingDesignFlowRate() {
  OS_ASSERT(setString(openstudio::Chiller_Electric_ASHRAE205Fields::AuxiliaryCoolingDesignFlowRate, ""));
}

std::string ChillerElectricASHRAE205_Impl::endUseSubcategory() const {
  const auto value = getString(openstudio::Chiller_Electric_ASHRAE205Fields::EndUseSubcategory, true);
  OS_ASSERT(value);
  return *value;
}

bool ChillerElectricASHRAE205_Impl::isEndUseSubcategoryDefaulted() const {
  return isEmpty(openstudio::Chiller_Electric_ASHRAE205Fields::EndUseSubcategory);
}

bool ChillerElectricASHRAE205_Impl::setEndUseSubcategory(const std::string& endUseSubcategory) {
  const bool result = setString(openstudio::Chiller_Electric_ASHRAE205Fields::EndUseSubcategory, endUseSubcategory);
  OS_ASSERT(result);
  return result;
}

void ChillerElectricASHRAE205_Impl::resetEndUseSubcategory() {
  OS_ASSERT(setString(openstudio::Chiller_Electric_ASHRAE205Fields::EndUseSubcategory, ""));
}

std::vector<std::string> ChillerElectricASHRAE205_Impl::performanceInterpolationMethodValues() const {
  return ChillerElectricASHRAE205::performanceInterpolationMethodValues();
}

std::vector<std::string> ChillerElectricASHRAE205_Impl::ambientTemperatureIndicatorValues() const {
  return ChillerElectricASHRAE205::ambientTemperatureIndicatorValues();
}

std::vector<std::string> ChillerElectricASHRAE205_Impl::chillerFlowModeValues() const {
  return ChillerElectricASHRAE205::chillerFlowModeValues();
}

unsigned ChillerElectricASHRAE205_Impl::supplyInletPort() const {
  return openstudio::Chiller_Electric_ASHRAE205Fields::ChilledWaterInletNodeName;
}

unsigned ChillerElectricASHRAE205_Impl::supplyOutletPort() const {
  return openstudio::Chiller_Electric_ASHRAE205Fields::ChilledWaterOutletNodeName;
}

unsigned ChillerElectricASHRAE205_Impl::demandInletPort() const {
  return openstudio::Chiller_Electric_ASHRAE205Fields::CondenserInletNodeName;
}

unsigned ChillerElectricASHRAE205_Impl::demandOutletPort() const {
  return openstudio::Chiller_Electric_ASHRAE205Fields::CondenserOutletNodeName;
}

unsigned ChillerElectricASHRAE205_Impl::tertiaryInletPort() const {
  return openstudio::Chiller_Electric_ASHRAE205Fields::HeatRecoveryInletNodeName;
}

unsigned ChillerElectricASHRAE205_Impl::tertiaryOutletPort() const {
  return openstudio::Chiller_Electric_ASHRAE205Fields::HeatRecoveryOutletNodeName;
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
