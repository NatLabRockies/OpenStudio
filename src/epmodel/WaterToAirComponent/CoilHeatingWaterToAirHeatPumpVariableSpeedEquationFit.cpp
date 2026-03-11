/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "WaterToAirComponent/CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit.hpp"
#include "WaterToAirComponent/CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/Coil_Heating_WaterToAirHeatPump_VariableSpeedEquationFit_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit(const Model& model)
  : ModelObject(CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit::iddObjectType(), model) {}

CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit(
  std::shared_ptr<detail::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit::iddObjectType() {
  return IddObjectType::Coil_Heating_WaterToAirHeatPump_VariableSpeedEquationFit;
}

int CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit::nominalSpeedLevel() const {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl>()->nominalSpeedLevel();
}

bool CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit::setNominalSpeedLevel(int nominalSpeedLevel) {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl>()->setNominalSpeedLevel(nominalSpeedLevel);
}

boost::optional<double> CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit::ratedHeatingCapacityAtSelectedNominalSpeedLevel() const {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl>()
    ->ratedHeatingCapacityAtSelectedNominalSpeedLevel();
}

bool CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit::isRatedHeatingCapacityAtSelectedNominalSpeedLevelAutosized() const {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl>()
    ->isRatedHeatingCapacityAtSelectedNominalSpeedLevelAutosized();
}

bool CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit::setRatedHeatingCapacityAtSelectedNominalSpeedLevel(
  double ratedHeatingCapacityAtSelectedNominalSpeedLevel) {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl>()
    ->setRatedHeatingCapacityAtSelectedNominalSpeedLevel(ratedHeatingCapacityAtSelectedNominalSpeedLevel);
}

void CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit::autosizeRatedHeatingCapacityAtSelectedNominalSpeedLevel() {
  getImpl<detail::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl>()
    ->autosizeRatedHeatingCapacityAtSelectedNominalSpeedLevel();
}

boost::optional<double> CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit::ratedAirFlowRateAtSelectedNominalSpeedLevel() const {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl>()->ratedAirFlowRateAtSelectedNominalSpeedLevel();
}

bool CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit::isRatedAirFlowRateAtSelectedNominalSpeedLevelAutosized() const {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl>()->isRatedAirFlowRateAtSelectedNominalSpeedLevelAutosized();
}

bool CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit::setRatedAirFlowRateAtSelectedNominalSpeedLevel(
  double ratedAirFlowRateAtSelectedNominalSpeedLevel) {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl>()
    ->setRatedAirFlowRateAtSelectedNominalSpeedLevel(ratedAirFlowRateAtSelectedNominalSpeedLevel);
}

void CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit::autosizeRatedAirFlowRateAtSelectedNominalSpeedLevel() {
  getImpl<detail::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl>()->autosizeRatedAirFlowRateAtSelectedNominalSpeedLevel();
}

boost::optional<double> CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit::ratedWaterFlowRateAtSelectedNominalSpeedLevel() const {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl>()->ratedWaterFlowRateAtSelectedNominalSpeedLevel();
}

bool CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit::isRatedWaterFlowRateAtSelectedNominalSpeedLevelAutosized() const {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl>()
    ->isRatedWaterFlowRateAtSelectedNominalSpeedLevelAutosized();
}

bool CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit::setRatedWaterFlowRateAtSelectedNominalSpeedLevel(
  double ratedWaterFlowRateAtSelectedNominalSpeedLevel) {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl>()
    ->setRatedWaterFlowRateAtSelectedNominalSpeedLevel(ratedWaterFlowRateAtSelectedNominalSpeedLevel);
}

void CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit::autosizeRatedWaterFlowRateAtSelectedNominalSpeedLevel() {
  getImpl<detail::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl>()->autosizeRatedWaterFlowRateAtSelectedNominalSpeedLevel();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

int CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::nominalSpeedLevel() const {
  const auto value = getInt(openstudio::Coil_Heating_WaterToAirHeatPump_VariableSpeedEquationFitFields::NominalSpeedLevel, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::setNominalSpeedLevel(int nominalSpeedLevel) {
  const bool result =
    setInt(openstudio::Coil_Heating_WaterToAirHeatPump_VariableSpeedEquationFitFields::NominalSpeedLevel, nominalSpeedLevel);
  OS_ASSERT(result);
  return result;
}

boost::optional<double> CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::ratedHeatingCapacityAtSelectedNominalSpeedLevel() const {
  return getDouble(openstudio::Coil_Heating_WaterToAirHeatPump_VariableSpeedEquationFitFields::RatedHeatingCapacityAtSelectedNominalSpeedLevel,
                   true);
}

bool CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::isRatedHeatingCapacityAtSelectedNominalSpeedLevelAutosized() const {
  if (const auto value =
        getString(openstudio::Coil_Heating_WaterToAirHeatPump_VariableSpeedEquationFitFields::RatedHeatingCapacityAtSelectedNominalSpeedLevel,
                  true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::setRatedHeatingCapacityAtSelectedNominalSpeedLevel(
  double ratedHeatingCapacityAtSelectedNominalSpeedLevel) {
  return setDouble(
    openstudio::Coil_Heating_WaterToAirHeatPump_VariableSpeedEquationFitFields::RatedHeatingCapacityAtSelectedNominalSpeedLevel,
    ratedHeatingCapacityAtSelectedNominalSpeedLevel);
}

void CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::autosizeRatedHeatingCapacityAtSelectedNominalSpeedLevel() {
  OS_ASSERT(setString(
    openstudio::Coil_Heating_WaterToAirHeatPump_VariableSpeedEquationFitFields::RatedHeatingCapacityAtSelectedNominalSpeedLevel, "autosize"));
}

boost::optional<double> CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::ratedAirFlowRateAtSelectedNominalSpeedLevel() const {
  return getDouble(openstudio::Coil_Heating_WaterToAirHeatPump_VariableSpeedEquationFitFields::RatedAirFlowRateAtSelectedNominalSpeedLevel,
                   true);
}

bool CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::isRatedAirFlowRateAtSelectedNominalSpeedLevelAutosized() const {
  if (const auto value =
        getString(openstudio::Coil_Heating_WaterToAirHeatPump_VariableSpeedEquationFitFields::RatedAirFlowRateAtSelectedNominalSpeedLevel,
                  true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::setRatedAirFlowRateAtSelectedNominalSpeedLevel(
  double ratedAirFlowRateAtSelectedNominalSpeedLevel) {
  return setDouble(openstudio::Coil_Heating_WaterToAirHeatPump_VariableSpeedEquationFitFields::RatedAirFlowRateAtSelectedNominalSpeedLevel,
                   ratedAirFlowRateAtSelectedNominalSpeedLevel);
}

void CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::autosizeRatedAirFlowRateAtSelectedNominalSpeedLevel() {
  OS_ASSERT(
    setString(openstudio::Coil_Heating_WaterToAirHeatPump_VariableSpeedEquationFitFields::RatedAirFlowRateAtSelectedNominalSpeedLevel, "autosize"));
}

boost::optional<double> CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::ratedWaterFlowRateAtSelectedNominalSpeedLevel() const {
  return getDouble(openstudio::Coil_Heating_WaterToAirHeatPump_VariableSpeedEquationFitFields::RatedWaterFlowRateAtSelectedNominalSpeedLevel,
                   true);
}

bool CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::isRatedWaterFlowRateAtSelectedNominalSpeedLevelAutosized() const {
  if (const auto value =
        getString(openstudio::Coil_Heating_WaterToAirHeatPump_VariableSpeedEquationFitFields::RatedWaterFlowRateAtSelectedNominalSpeedLevel,
                  true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::setRatedWaterFlowRateAtSelectedNominalSpeedLevel(
  double ratedWaterFlowRateAtSelectedNominalSpeedLevel) {
  return setDouble(openstudio::Coil_Heating_WaterToAirHeatPump_VariableSpeedEquationFitFields::RatedWaterFlowRateAtSelectedNominalSpeedLevel,
                   ratedWaterFlowRateAtSelectedNominalSpeedLevel);
}

void CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::autosizeRatedWaterFlowRateAtSelectedNominalSpeedLevel() {
  OS_ASSERT(setString(openstudio::Coil_Heating_WaterToAirHeatPump_VariableSpeedEquationFitFields::RatedWaterFlowRateAtSelectedNominalSpeedLevel,
                      "autosize"));
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
