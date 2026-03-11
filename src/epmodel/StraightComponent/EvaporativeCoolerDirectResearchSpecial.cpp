/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/EvaporativeCoolerDirectResearchSpecial.hpp"
#include "StraightComponent/EvaporativeCoolerDirectResearchSpecial_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/EvaporativeCooler_Direct_ResearchSpecial_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

EvaporativeCoolerDirectResearchSpecial::EvaporativeCoolerDirectResearchSpecial(const Model& model)
  : StraightComponent(EvaporativeCoolerDirectResearchSpecial::iddObjectType(), model) {
  autosizeRecirculatingWaterPumpPowerConsumption();
  autosizePrimaryAirDesignFlowRate();
}

EvaporativeCoolerDirectResearchSpecial::EvaporativeCoolerDirectResearchSpecial(
  std::shared_ptr<detail::EvaporativeCoolerDirectResearchSpecial_Impl> impl)
  : StraightComponent(std::move(impl)) {}

IddObjectType EvaporativeCoolerDirectResearchSpecial::iddObjectType() {
  return IddObjectType::EvaporativeCooler_Direct_ResearchSpecial;
}

double EvaporativeCoolerDirectResearchSpecial::coolerDesignEffectiveness() const {
  return getImpl<detail::EvaporativeCoolerDirectResearchSpecial_Impl>()->coolerDesignEffectiveness();
}

double EvaporativeCoolerDirectResearchSpecial::coolerEffectiveness() const {
  return getImpl<detail::EvaporativeCoolerDirectResearchSpecial_Impl>()->coolerDesignEffectiveness();
}

bool EvaporativeCoolerDirectResearchSpecial::setCoolerDesignEffectiveness(double value) {
  return getImpl<detail::EvaporativeCoolerDirectResearchSpecial_Impl>()->setCoolerDesignEffectiveness(value);
}

bool EvaporativeCoolerDirectResearchSpecial::setCoolerEffectiveness(double value) {
  return getImpl<detail::EvaporativeCoolerDirectResearchSpecial_Impl>()->setCoolerDesignEffectiveness(value);
}

boost::optional<double> EvaporativeCoolerDirectResearchSpecial::recirculatingWaterPumpPowerConsumption() const {
  return getImpl<detail::EvaporativeCoolerDirectResearchSpecial_Impl>()->recirculatingWaterPumpPowerConsumption();
}

bool EvaporativeCoolerDirectResearchSpecial::setRecirculatingWaterPumpPowerConsumption(double value) {
  return getImpl<detail::EvaporativeCoolerDirectResearchSpecial_Impl>()->setRecirculatingWaterPumpPowerConsumption(value);
}

void EvaporativeCoolerDirectResearchSpecial::autosizeRecirculatingWaterPumpPowerConsumption() {
  getImpl<detail::EvaporativeCoolerDirectResearchSpecial_Impl>()->autosizeRecirculatingWaterPumpPowerConsumption();
}

bool EvaporativeCoolerDirectResearchSpecial::isRecirculatingWaterPumpPowerConsumptionAutosized() const {
  return getImpl<detail::EvaporativeCoolerDirectResearchSpecial_Impl>()->isRecirculatingWaterPumpPowerConsumptionAutosized();
}

boost::optional<double> EvaporativeCoolerDirectResearchSpecial::primaryAirDesignFlowRate() const {
  return getImpl<detail::EvaporativeCoolerDirectResearchSpecial_Impl>()->primaryAirDesignFlowRate();
}

bool EvaporativeCoolerDirectResearchSpecial::setPrimaryAirDesignFlowRate(double value) {
  return getImpl<detail::EvaporativeCoolerDirectResearchSpecial_Impl>()->setPrimaryAirDesignFlowRate(value);
}

void EvaporativeCoolerDirectResearchSpecial::autosizePrimaryAirDesignFlowRate() {
  getImpl<detail::EvaporativeCoolerDirectResearchSpecial_Impl>()->autosizePrimaryAirDesignFlowRate();
}

bool EvaporativeCoolerDirectResearchSpecial::isPrimaryAirDesignFlowRateAutosized() const {
  return getImpl<detail::EvaporativeCoolerDirectResearchSpecial_Impl>()->isPrimaryAirDesignFlowRateAutosized();
}

double EvaporativeCoolerDirectResearchSpecial::driftLossFraction() const {
  return getImpl<detail::EvaporativeCoolerDirectResearchSpecial_Impl>()->driftLossFraction();
}

bool EvaporativeCoolerDirectResearchSpecial::setDriftLossFraction(double value) {
  return getImpl<detail::EvaporativeCoolerDirectResearchSpecial_Impl>()->setDriftLossFraction(value);
}

double EvaporativeCoolerDirectResearchSpecial::blowdownConcentrationRatio() const {
  return getImpl<detail::EvaporativeCoolerDirectResearchSpecial_Impl>()->blowdownConcentrationRatio();
}

bool EvaporativeCoolerDirectResearchSpecial::setBlowdownConcentrationRatio(double value) {
  return getImpl<detail::EvaporativeCoolerDirectResearchSpecial_Impl>()->setBlowdownConcentrationRatio(value);
}

double EvaporativeCoolerDirectResearchSpecial::waterPumpPowerSizingFactor() const {
  return getImpl<detail::EvaporativeCoolerDirectResearchSpecial_Impl>()->waterPumpPowerSizingFactor();
}

bool EvaporativeCoolerDirectResearchSpecial::setWaterPumpPowerSizingFactor(double waterPumpPowerSizingFactor) {
  return getImpl<detail::EvaporativeCoolerDirectResearchSpecial_Impl>()->setWaterPumpPowerSizingFactor(waterPumpPowerSizingFactor);
}

double EvaporativeCoolerDirectResearchSpecial::evaporativeOperationMinimumDrybulbTemperature() const {
  return getImpl<detail::EvaporativeCoolerDirectResearchSpecial_Impl>()->evaporativeOperationMinimumDrybulbTemperature();
}

bool EvaporativeCoolerDirectResearchSpecial::setEvaporativeOperationMinimumDrybulbTemperature(
  double evaporativeOperationMinimumDrybulbTemperature) {
  return getImpl<detail::EvaporativeCoolerDirectResearchSpecial_Impl>()->setEvaporativeOperationMinimumDrybulbTemperature(
    evaporativeOperationMinimumDrybulbTemperature);
}

double EvaporativeCoolerDirectResearchSpecial::evaporativeOperationMaximumLimitWetbulbTemperature() const {
  return getImpl<detail::EvaporativeCoolerDirectResearchSpecial_Impl>()->evaporativeOperationMaximumLimitWetbulbTemperature();
}

bool EvaporativeCoolerDirectResearchSpecial::setEvaporativeOperationMaximumLimitWetbulbTemperature(
  double evaporativeOperationMaximumLimitWetbulbTemperature) {
  return getImpl<detail::EvaporativeCoolerDirectResearchSpecial_Impl>()->setEvaporativeOperationMaximumLimitWetbulbTemperature(
    evaporativeOperationMaximumLimitWetbulbTemperature);
}

double EvaporativeCoolerDirectResearchSpecial::evaporativeOperationMaximumLimitDrybulbTemperature() const {
  return getImpl<detail::EvaporativeCoolerDirectResearchSpecial_Impl>()->evaporativeOperationMaximumLimitDrybulbTemperature();
}

bool EvaporativeCoolerDirectResearchSpecial::setEvaporativeOperationMaximumLimitDrybulbTemperature(
  double evaporativeOperationMaximumLimitDrybulbTemperature) {
  return getImpl<detail::EvaporativeCoolerDirectResearchSpecial_Impl>()->setEvaporativeOperationMaximumLimitDrybulbTemperature(
    evaporativeOperationMaximumLimitDrybulbTemperature);
}

boost::optional<double> EvaporativeCoolerDirectResearchSpecial::autosizedRecirculatingWaterPumpPowerConsumption() const {
  return getImpl<detail::EvaporativeCoolerDirectResearchSpecial_Impl>()->autosizedRecirculatingWaterPumpPowerConsumption();
}

boost::optional<double> EvaporativeCoolerDirectResearchSpecial::autosizedPrimaryAirDesignFlowRate() const {
  return getImpl<detail::EvaporativeCoolerDirectResearchSpecial_Impl>()->autosizedPrimaryAirDesignFlowRate();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

unsigned EvaporativeCoolerDirectResearchSpecial_Impl::inletPort() const {
  return openstudio::EvaporativeCooler_Direct_ResearchSpecialFields::AirInletNodeName;
}

unsigned EvaporativeCoolerDirectResearchSpecial_Impl::outletPort() const {
  return openstudio::EvaporativeCooler_Direct_ResearchSpecialFields::AirOutletNodeName;
}

double EvaporativeCoolerDirectResearchSpecial_Impl::coolerDesignEffectiveness() const {
  const auto value = getDouble(openstudio::EvaporativeCooler_Direct_ResearchSpecialFields::CoolerDesignEffectiveness, true);
  OS_ASSERT(value);
  return *value;
}

bool EvaporativeCoolerDirectResearchSpecial_Impl::setCoolerDesignEffectiveness(double value) {
  return setDouble(openstudio::EvaporativeCooler_Direct_ResearchSpecialFields::CoolerDesignEffectiveness, value);
}

boost::optional<double> EvaporativeCoolerDirectResearchSpecial_Impl::recirculatingWaterPumpPowerConsumption() const {
  return getDouble(openstudio::EvaporativeCooler_Direct_ResearchSpecialFields::RecirculatingWaterPumpDesignPower, true);
}

bool EvaporativeCoolerDirectResearchSpecial_Impl::setRecirculatingWaterPumpPowerConsumption(double value) {
  return setDouble(openstudio::EvaporativeCooler_Direct_ResearchSpecialFields::RecirculatingWaterPumpDesignPower, value);
}

void EvaporativeCoolerDirectResearchSpecial_Impl::autosizeRecirculatingWaterPumpPowerConsumption() {
  OS_ASSERT(setString(openstudio::EvaporativeCooler_Direct_ResearchSpecialFields::RecirculatingWaterPumpDesignPower, "Autosize"));
}

bool EvaporativeCoolerDirectResearchSpecial_Impl::isRecirculatingWaterPumpPowerConsumptionAutosized() const {
  if (auto value = getString(openstudio::EvaporativeCooler_Direct_ResearchSpecialFields::RecirculatingWaterPumpDesignPower, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

boost::optional<double> EvaporativeCoolerDirectResearchSpecial_Impl::primaryAirDesignFlowRate() const {
  return getDouble(openstudio::EvaporativeCooler_Direct_ResearchSpecialFields::PrimaryAirDesignFlowRate, true);
}

bool EvaporativeCoolerDirectResearchSpecial_Impl::setPrimaryAirDesignFlowRate(double value) {
  return setDouble(openstudio::EvaporativeCooler_Direct_ResearchSpecialFields::PrimaryAirDesignFlowRate, value);
}

void EvaporativeCoolerDirectResearchSpecial_Impl::autosizePrimaryAirDesignFlowRate() {
  OS_ASSERT(setString(openstudio::EvaporativeCooler_Direct_ResearchSpecialFields::PrimaryAirDesignFlowRate, "Autosize"));
}

bool EvaporativeCoolerDirectResearchSpecial_Impl::isPrimaryAirDesignFlowRateAutosized() const {
  if (auto value = getString(openstudio::EvaporativeCooler_Direct_ResearchSpecialFields::PrimaryAirDesignFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

double EvaporativeCoolerDirectResearchSpecial_Impl::driftLossFraction() const {
  const auto value = getDouble(openstudio::EvaporativeCooler_Direct_ResearchSpecialFields::DriftLossFraction, true);
  OS_ASSERT(value);
  return *value;
}

bool EvaporativeCoolerDirectResearchSpecial_Impl::setDriftLossFraction(double value) {
  return setDouble(openstudio::EvaporativeCooler_Direct_ResearchSpecialFields::DriftLossFraction, value);
}

double EvaporativeCoolerDirectResearchSpecial_Impl::blowdownConcentrationRatio() const {
  const auto value = getDouble(openstudio::EvaporativeCooler_Direct_ResearchSpecialFields::BlowdownConcentrationRatio, true);
  OS_ASSERT(value);
  return *value;
}

bool EvaporativeCoolerDirectResearchSpecial_Impl::setBlowdownConcentrationRatio(double value) {
  return setDouble(openstudio::EvaporativeCooler_Direct_ResearchSpecialFields::BlowdownConcentrationRatio, value);
}

double EvaporativeCoolerDirectResearchSpecial_Impl::waterPumpPowerSizingFactor() const {
  const auto value = getDouble(openstudio::EvaporativeCooler_Direct_ResearchSpecialFields::WaterPumpPowerSizingFactor, true);
  OS_ASSERT(value);
  return *value;
}

bool EvaporativeCoolerDirectResearchSpecial_Impl::setWaterPumpPowerSizingFactor(double waterPumpPowerSizingFactor) {
  const bool result =
    setDouble(openstudio::EvaporativeCooler_Direct_ResearchSpecialFields::WaterPumpPowerSizingFactor, waterPumpPowerSizingFactor);
  OS_ASSERT(result);
  return result;
}

double EvaporativeCoolerDirectResearchSpecial_Impl::evaporativeOperationMinimumDrybulbTemperature() const {
  const auto value = getDouble(openstudio::EvaporativeCooler_Direct_ResearchSpecialFields::EvaporativeOperationMinimumDrybulbTemperature, true);
  OS_ASSERT(value);
  return *value;
}

bool EvaporativeCoolerDirectResearchSpecial_Impl::setEvaporativeOperationMinimumDrybulbTemperature(
  double evaporativeOperationMinimumDrybulbTemperature) {
  return setDouble(openstudio::EvaporativeCooler_Direct_ResearchSpecialFields::EvaporativeOperationMinimumDrybulbTemperature,
                   evaporativeOperationMinimumDrybulbTemperature);
}

double EvaporativeCoolerDirectResearchSpecial_Impl::evaporativeOperationMaximumLimitWetbulbTemperature() const {
  const auto value =
    getDouble(openstudio::EvaporativeCooler_Direct_ResearchSpecialFields::EvaporativeOperationMaximumLimitWetbulbTemperature, true);
  OS_ASSERT(value);
  return *value;
}

bool EvaporativeCoolerDirectResearchSpecial_Impl::setEvaporativeOperationMaximumLimitWetbulbTemperature(
  double evaporativeOperationMaximumLimitWetbulbTemperature) {
  return setDouble(openstudio::EvaporativeCooler_Direct_ResearchSpecialFields::EvaporativeOperationMaximumLimitWetbulbTemperature,
                   evaporativeOperationMaximumLimitWetbulbTemperature);
}

double EvaporativeCoolerDirectResearchSpecial_Impl::evaporativeOperationMaximumLimitDrybulbTemperature() const {
  const auto value =
    getDouble(openstudio::EvaporativeCooler_Direct_ResearchSpecialFields::EvaporativeOperationMaximumLimitDrybulbTemperature, true);
  OS_ASSERT(value);
  return *value;
}

bool EvaporativeCoolerDirectResearchSpecial_Impl::setEvaporativeOperationMaximumLimitDrybulbTemperature(
  double evaporativeOperationMaximumLimitDrybulbTemperature) {
  return setDouble(openstudio::EvaporativeCooler_Direct_ResearchSpecialFields::EvaporativeOperationMaximumLimitDrybulbTemperature,
                   evaporativeOperationMaximumLimitDrybulbTemperature);
}

boost::optional<double> EvaporativeCoolerDirectResearchSpecial_Impl::autosizedRecirculatingWaterPumpPowerConsumption() const {
  // epmodel does not currently resolve autosized values from SQL results.
  return boost::none;
}

boost::optional<double> EvaporativeCoolerDirectResearchSpecial_Impl::autosizedPrimaryAirDesignFlowRate() const {
  // epmodel does not currently resolve autosized values from SQL results.
  return boost::none;
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
