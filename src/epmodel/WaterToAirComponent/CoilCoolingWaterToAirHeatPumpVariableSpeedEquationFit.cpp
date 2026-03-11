/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "WaterToAirComponent/CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit.hpp"
#include "WaterToAirComponent/CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/Coil_Cooling_WaterToAirHeatPump_VariableSpeedEquationFit_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit(const Model& model)
  : ModelObject(CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit::iddObjectType(), model) {}

CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit(
  std::shared_ptr<detail::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit::iddObjectType() {
  return IddObjectType::Coil_Cooling_WaterToAirHeatPump_VariableSpeedEquationFit;
}

int CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit::nominalSpeedLevel() const {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl>()->nominalSpeedLevel();
}

bool CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit::setNominalSpeedLevel(int nominalSpeedLevel) {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl>()->setNominalSpeedLevel(nominalSpeedLevel);
}

boost::optional<double> CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit::grossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel() const {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl>()
    ->grossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel();
}

bool CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit::isGrossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevelAutosized() const {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl>()
    ->isGrossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevelAutosized();
}

bool CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit::setGrossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel(
  double grossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel) {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl>()
    ->setGrossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel(grossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel);
}

void CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit::autosizeGrossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel() {
  getImpl<detail::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl>()
    ->autosizeGrossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel();
}

boost::optional<double> CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit::ratedAirFlowRateAtSelectedNominalSpeedLevel() const {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl>()->ratedAirFlowRateAtSelectedNominalSpeedLevel();
}

bool CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit::isRatedAirFlowRateAtSelectedNominalSpeedLevelAutosized() const {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl>()->isRatedAirFlowRateAtSelectedNominalSpeedLevelAutosized();
}

bool CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit::setRatedAirFlowRateAtSelectedNominalSpeedLevel(
  double ratedAirFlowRateAtSelectedNominalSpeedLevel) {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl>()
    ->setRatedAirFlowRateAtSelectedNominalSpeedLevel(ratedAirFlowRateAtSelectedNominalSpeedLevel);
}

void CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit::autosizeRatedAirFlowRateAtSelectedNominalSpeedLevel() {
  getImpl<detail::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl>()->autosizeRatedAirFlowRateAtSelectedNominalSpeedLevel();
}

boost::optional<double> CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit::ratedWaterFlowRateAtSelectedNominalSpeedLevel() const {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl>()->ratedWaterFlowRateAtSelectedNominalSpeedLevel();
}

bool CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit::isRatedWaterFlowRateAtSelectedNominalSpeedLevelAutosized() const {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl>()
    ->isRatedWaterFlowRateAtSelectedNominalSpeedLevelAutosized();
}

bool CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit::setRatedWaterFlowRateAtSelectedNominalSpeedLevel(
  double ratedWaterFlowRateAtSelectedNominalSpeedLevel) {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl>()
    ->setRatedWaterFlowRateAtSelectedNominalSpeedLevel(ratedWaterFlowRateAtSelectedNominalSpeedLevel);
}

void CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit::autosizeRatedWaterFlowRateAtSelectedNominalSpeedLevel() {
  getImpl<detail::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl>()->autosizeRatedWaterFlowRateAtSelectedNominalSpeedLevel();
}

double CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit::nominalTimeforCondensatetoBeginLeavingtheCoil() const {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl>()->nominalTimeforCondensatetoBeginLeavingtheCoil();
}

bool CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit::setNominalTimeforCondensatetoBeginLeavingtheCoil(
  double nominalTimeforCondensatetoBeginLeavingtheCoil) {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl>()->setNominalTimeforCondensatetoBeginLeavingtheCoil(
    nominalTimeforCondensatetoBeginLeavingtheCoil);
}

double CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit::initialMoistureEvaporationRateDividedbySteadyStateACLatentCapacity() const {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl>()
    ->initialMoistureEvaporationRateDividedbySteadyStateACLatentCapacity();
}

bool CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit::setInitialMoistureEvaporationRateDividedbySteadyStateACLatentCapacity(
  double initialMoistureEvaporationRateDividedbySteadyStateACLatentCapacity) {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl>()
    ->setInitialMoistureEvaporationRateDividedbySteadyStateACLatentCapacity(
      initialMoistureEvaporationRateDividedbySteadyStateACLatentCapacity);
}

double CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit::maximumCyclingRate() const {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl>()->maximumCyclingRate();
}

bool CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit::setMaximumCyclingRate(double maximumCyclingRate) {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl>()->setMaximumCyclingRate(maximumCyclingRate);
}

double CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit::latentCapacityTimeConstant() const {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl>()->latentCapacityTimeConstant();
}

bool CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit::setLatentCapacityTimeConstant(double latentCapacityTimeConstant) {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl>()->setLatentCapacityTimeConstant(latentCapacityTimeConstant);
}

double CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit::fanDelayTime() const {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl>()->fanDelayTime();
}

bool CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit::setFanDelayTime(double fanDelayTime) {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl>()->setFanDelayTime(fanDelayTime);
}

bool CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit::useHotGasReheat() const {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl>()->useHotGasReheat();
}

bool CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit::setUseHotGasReheat(bool useHotGasReheat) {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl>()->setUseHotGasReheat(useHotGasReheat);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

int CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::nominalSpeedLevel() const {
  const auto value = getInt(openstudio::Coil_Cooling_WaterToAirHeatPump_VariableSpeedEquationFitFields::NominalSpeedLevel, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::setNominalSpeedLevel(int nominalSpeedLevel) {
  const bool result =
    setInt(openstudio::Coil_Cooling_WaterToAirHeatPump_VariableSpeedEquationFitFields::NominalSpeedLevel, nominalSpeedLevel);
  OS_ASSERT(result);
  return result;
}

boost::optional<double> CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::grossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel() const {
  return getDouble(openstudio::Coil_Cooling_WaterToAirHeatPump_VariableSpeedEquationFitFields::GrossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel,
                   true);
}

bool CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::isGrossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevelAutosized() const {
  if (const auto value =
        getString(openstudio::Coil_Cooling_WaterToAirHeatPump_VariableSpeedEquationFitFields::GrossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel,
                  true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::setGrossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel(
  double grossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel) {
  return setDouble(
    openstudio::Coil_Cooling_WaterToAirHeatPump_VariableSpeedEquationFitFields::GrossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel,
    grossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel);
}

void CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::autosizeGrossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel() {
  OS_ASSERT(setString(
    openstudio::Coil_Cooling_WaterToAirHeatPump_VariableSpeedEquationFitFields::GrossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel,
    "autosize"));
}

boost::optional<double> CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::ratedAirFlowRateAtSelectedNominalSpeedLevel() const {
  return getDouble(openstudio::Coil_Cooling_WaterToAirHeatPump_VariableSpeedEquationFitFields::RatedAirFlowRateAtSelectedNominalSpeedLevel, true);
}

bool CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::isRatedAirFlowRateAtSelectedNominalSpeedLevelAutosized() const {
  if (const auto value =
        getString(openstudio::Coil_Cooling_WaterToAirHeatPump_VariableSpeedEquationFitFields::RatedAirFlowRateAtSelectedNominalSpeedLevel, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::setRatedAirFlowRateAtSelectedNominalSpeedLevel(
  double ratedAirFlowRateAtSelectedNominalSpeedLevel) {
  return setDouble(openstudio::Coil_Cooling_WaterToAirHeatPump_VariableSpeedEquationFitFields::RatedAirFlowRateAtSelectedNominalSpeedLevel,
                   ratedAirFlowRateAtSelectedNominalSpeedLevel);
}

void CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::autosizeRatedAirFlowRateAtSelectedNominalSpeedLevel() {
  OS_ASSERT(
    setString(openstudio::Coil_Cooling_WaterToAirHeatPump_VariableSpeedEquationFitFields::RatedAirFlowRateAtSelectedNominalSpeedLevel, "autosize"));
}

boost::optional<double> CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::ratedWaterFlowRateAtSelectedNominalSpeedLevel() const {
  return getDouble(openstudio::Coil_Cooling_WaterToAirHeatPump_VariableSpeedEquationFitFields::RatedWaterFlowRateAtSelectedNominalSpeedLevel,
                   true);
}

bool CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::isRatedWaterFlowRateAtSelectedNominalSpeedLevelAutosized() const {
  if (const auto value = getString(openstudio::Coil_Cooling_WaterToAirHeatPump_VariableSpeedEquationFitFields::RatedWaterFlowRateAtSelectedNominalSpeedLevel,
                                   true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::setRatedWaterFlowRateAtSelectedNominalSpeedLevel(
  double ratedWaterFlowRateAtSelectedNominalSpeedLevel) {
  return setDouble(openstudio::Coil_Cooling_WaterToAirHeatPump_VariableSpeedEquationFitFields::RatedWaterFlowRateAtSelectedNominalSpeedLevel,
                   ratedWaterFlowRateAtSelectedNominalSpeedLevel);
}

void CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::autosizeRatedWaterFlowRateAtSelectedNominalSpeedLevel() {
  OS_ASSERT(setString(openstudio::Coil_Cooling_WaterToAirHeatPump_VariableSpeedEquationFitFields::RatedWaterFlowRateAtSelectedNominalSpeedLevel,
                      "autosize"));
}

double CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::nominalTimeforCondensatetoBeginLeavingtheCoil() const {
  const auto value =
    getDouble(openstudio::Coil_Cooling_WaterToAirHeatPump_VariableSpeedEquationFitFields::NominalTimeforCondensatetoBeginLeavingtheCoil, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::setNominalTimeforCondensatetoBeginLeavingtheCoil(
  double nominalTimeforCondensatetoBeginLeavingtheCoil) {
  return setDouble(openstudio::Coil_Cooling_WaterToAirHeatPump_VariableSpeedEquationFitFields::NominalTimeforCondensatetoBeginLeavingtheCoil,
                   nominalTimeforCondensatetoBeginLeavingtheCoil);
}

double CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::initialMoistureEvaporationRateDividedbySteadyStateACLatentCapacity() const {
  const auto value = getDouble(
    openstudio::Coil_Cooling_WaterToAirHeatPump_VariableSpeedEquationFitFields::InitialMoistureEvaporationRateDividedbySteadyStateACLatentCapacity,
    true);
  OS_ASSERT(value);
  return *value;
}

bool CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::setInitialMoistureEvaporationRateDividedbySteadyStateACLatentCapacity(
  double initialMoistureEvaporationRateDividedbySteadyStateACLatentCapacity) {
  return setDouble(
    openstudio::Coil_Cooling_WaterToAirHeatPump_VariableSpeedEquationFitFields::InitialMoistureEvaporationRateDividedbySteadyStateACLatentCapacity,
    initialMoistureEvaporationRateDividedbySteadyStateACLatentCapacity);
}

double CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::maximumCyclingRate() const {
  const auto value = getDouble(openstudio::Coil_Cooling_WaterToAirHeatPump_VariableSpeedEquationFitFields::MaximumCyclingRate, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::setMaximumCyclingRate(double maximumCyclingRate) {
  return setDouble(openstudio::Coil_Cooling_WaterToAirHeatPump_VariableSpeedEquationFitFields::MaximumCyclingRate, maximumCyclingRate);
}

double CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::latentCapacityTimeConstant() const {
  const auto value = getDouble(openstudio::Coil_Cooling_WaterToAirHeatPump_VariableSpeedEquationFitFields::LatentCapacityTimeConstant, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::setLatentCapacityTimeConstant(double latentCapacityTimeConstant) {
  return setDouble(openstudio::Coil_Cooling_WaterToAirHeatPump_VariableSpeedEquationFitFields::LatentCapacityTimeConstant,
                   latentCapacityTimeConstant);
}

double CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::fanDelayTime() const {
  const auto value = getDouble(openstudio::Coil_Cooling_WaterToAirHeatPump_VariableSpeedEquationFitFields::FanDelayTime, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::setFanDelayTime(double fanDelayTime) {
  return setDouble(openstudio::Coil_Cooling_WaterToAirHeatPump_VariableSpeedEquationFitFields::FanDelayTime, fanDelayTime);
}

bool CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::useHotGasReheat() const {
  const auto value = getInt(openstudio::Coil_Cooling_WaterToAirHeatPump_VariableSpeedEquationFitFields::FlagforUsingHotGasReheat0or1, true);
  OS_ASSERT(value);
  return (*value == 1);
}

bool CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::setUseHotGasReheat(bool useHotGasReheat) {
  return setInt(openstudio::Coil_Cooling_WaterToAirHeatPump_VariableSpeedEquationFitFields::FlagforUsingHotGasReheat0or1,
                useHotGasReheat ? 1 : 0);
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
