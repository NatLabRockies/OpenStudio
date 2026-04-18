/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "WaterToAirComponent/CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit.hpp"
#include "WaterToAirComponent/CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl.hpp"

#include "Curve/Curve.hpp"
#include "Curve/CurveBiquadratic.hpp"
#include "Curve/Curve_Impl.hpp"
#include "Curve/CurveLinear.hpp"
#include "Curve/CurveQuadratic.hpp"
#include "Model.hpp"
#include "ModelObject/AirflowNetworkDistributionComponentCoil.hpp"
#include "ModelObject/AirflowNetworkDistributionComponentCoil_Impl.hpp"
#include "ParentObject/CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData.hpp"
#include "ParentObject/CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/AirflowNetwork_Distribution_Component_Coil_FieldEnums.hxx>
#include <utilities/idd/Coil_Cooling_WaterToAirHeatPump_VariableSpeedEquationFit_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idf/WorkspaceExtensibleGroup.hpp>

#include <cmath>

namespace openstudio {
namespace epmodel {

CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit(const Model& model)
  : WaterToAirComponent(CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit::iddObjectType(), model) {
  auto alwaysOn = model.alwaysOnDiscreteSchedule();
  OS_ASSERT(setAvailabilitySchedule(alwaysOn));
  getImpl<detail::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl>()->setConstructorScalarDefaults();

  CurveQuadratic partLoadFraction(model);
  OS_ASSERT(partLoadFraction.setCoefficient1Constant(0.85));
  OS_ASSERT(partLoadFraction.setCoefficient2x(0.15));
  OS_ASSERT(partLoadFraction.setCoefficient3xPOW2(0.0));
  OS_ASSERT(partLoadFraction.setMinimumValueofx(0.0));
  OS_ASSERT(partLoadFraction.setMaximumValueofx(1.0));
  OS_ASSERT(setEnergyPartLoadFractionCurve(partLoadFraction));
}

CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit(
  const Model& model, const Curve& partLoadFraction)
  : WaterToAirComponent(CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit::iddObjectType(), model) {
  auto alwaysOn = model.alwaysOnDiscreteSchedule();
  OS_ASSERT(setAvailabilitySchedule(alwaysOn));
  getImpl<detail::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl>()->setConstructorScalarDefaults();
  OS_ASSERT(setEnergyPartLoadFractionCurve(partLoadFraction));
}

CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit(
  std::shared_ptr<detail::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl> impl)
  : WaterToAirComponent(std::move(impl)) {}

IddObjectType CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit::iddObjectType() {
  return IddObjectType::Coil_Cooling_WaterToAirHeatPump_VariableSpeedEquationFit;
}

Schedule CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit::availabilitySchedule() const {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl>()->availabilitySchedule();
}

bool CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit::setAvailabilitySchedule(Schedule& schedule) {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl>()->setAvailabilitySchedule(schedule);
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

boost::optional<double> CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit::autosizedGrossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel()
  const {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl>()
    ->autosizedGrossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel();
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

boost::optional<double> CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit::autosizedRatedAirFlowRateAtSelectedNominalSpeedLevel() const {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl>()->autosizedRatedAirFlowRateAtSelectedNominalSpeedLevel();
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

boost::optional<double> CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit::autosizedRatedWaterFlowRateAtSelectedNominalSpeedLevel() const {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl>()->autosizedRatedWaterFlowRateAtSelectedNominalSpeedLevel();
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

Curve CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit::energyPartLoadFractionCurve() const {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl>()->energyPartLoadFractionCurve();
}

bool CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit::setEnergyPartLoadFractionCurve(const Curve& curve) {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl>()->setEnergyPartLoadFractionCurve(curve);
}

std::vector<CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData> CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit::speeds() const {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl>()->speeds();
}

bool CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit::addSpeed(
  const CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData& speed) {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl>()->addSpeed(speed);
}

void CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit::removeSpeed(
  const CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData& speed) {
  getImpl<detail::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl>()->removeSpeed(speed);
}

void CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit::removeAllSpeeds() {
  getImpl<detail::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl>()->removeAllSpeeds();
}

AirflowNetworkDistributionComponentCoil CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit::getAirflowNetworkEquivalentDuct(double length,
                                                                                                                             double diameter) {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl>()->getAirflowNetworkEquivalentDuct(length, diameter);
}

boost::optional<AirflowNetworkDistributionComponentCoil> CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit::airflowNetworkEquivalentDuct() const {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl>()->airflowNetworkEquivalentDuct();
}

std::vector<ModelObject> CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit::children() const {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl>()->children();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

namespace {

using Fields = openstudio::Coil_Cooling_WaterToAirHeatPump_VariableSpeedEquationFitFields;
using ExtensibleFields = openstudio::Coil_Cooling_WaterToAirHeatPump_VariableSpeedEquationFitExtensibleFields;

std::vector<AirflowNetworkDistributionComponentCoil> attachedAirflowNetworkDistributionComponentCoils(const ModelObject& object) {
  std::vector<AirflowNetworkDistributionComponentCoil> result;
  for (const auto& source : object.getSources(AirflowNetworkDistributionComponentCoil::iddObjectType())) {
    if (auto afnComponent = source.optionalCast<AirflowNetworkDistributionComponentCoil>()) {
      result.push_back(*afnComponent);
    }
  }
  return result;
}

// Transient speed-data wrappers are keyed by parent handle plus row index so
// repeated `speeds()` calls can recover the same wrapper objects.
std::string transientSpeedDataPrefix(const openstudio::epmodel::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit& parent) {
  return "__transient__" + openstudio::toString(parent.handle()) + "__cooling_wtahp_vs_speed_";
}

boost::optional<CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData> transientSpeedDataByName(
  const Model& model, const std::string& name) {
  for (const auto& speed : model.getConcreteModelObjects<CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData>(true)) {
    if (const auto speedName = speed.name()) {
      if (openstudio::istringEqual(*speedName, name)) {
        return speed;
      }
    }
  }
  return boost::none;
}

// When rows are inserted or removed, rename the attached transient wrappers so
// stable wrapper identity follows the current row ordering.
void renameAttachedSpeedData(const openstudio::epmodel::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit& parent, unsigned oldIndex,
                             unsigned newIndex) {
  if (oldIndex == newIndex) {
    return;
  }
  const auto oldName = transientSpeedDataName(parent, oldIndex);
  if (auto speed = transientSpeedDataByName(parent.model(), oldName)) {
    const bool ok = speed->setName(transientSpeedDataName(parent, newIndex)).has_value();
    OS_ASSERT(ok);
  }
}

}  // namespace

std::string transientSpeedDataName(const openstudio::epmodel::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit& parent, unsigned speedIndex) {
  return transientSpeedDataPrefix(parent) + openstudio::toString(speedIndex);
}

unsigned CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::airInletPort() const {
  return Fields::IndoorAirInletNodeName;
}

unsigned CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::airOutletPort() const {
  return Fields::IndoorAirOutletNodeName;
}

unsigned CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::waterInletPort() const {
  return Fields::WatertoRefrigerantHXWaterInletNodeName;
}

unsigned CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::waterOutletPort() const {
  return Fields::WatertoRefrigerantHXWaterOutletNodeName;
}

Schedule CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::availabilitySchedule() const {
  auto schedule = getObject<ModelObject>().getModelObjectTarget<Schedule>(Fields::AvailabilityScheduleName);
  if (!schedule) {
    LOG_FREE(Error, "openstudio.epmodel.CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit",
             "Required availability schedule not set, repairing persisted state with the model always-on discrete schedule");
    schedule = model().alwaysOnDiscreteSchedule();
    const bool ok = const_cast<CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl*>(this)->setAvailabilitySchedule(*schedule);
    OS_ASSERT(ok);
    schedule = getObject<ModelObject>().getModelObjectTarget<Schedule>(Fields::AvailabilityScheduleName);
  }
  OS_ASSERT(schedule);
  return *schedule;
}

bool CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::setAvailabilitySchedule(Schedule& schedule) {
  return setSchedule(Fields::AvailabilityScheduleName, "CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit", "Availability Schedule",
                     schedule);
}

int CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::nominalSpeedLevel() const {
  const auto value = getInt(Fields::NominalSpeedLevel, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::setNominalSpeedLevel(int nominalSpeedLevel) {
  const bool result = setInt(Fields::NominalSpeedLevel, nominalSpeedLevel);
  OS_ASSERT(result);
  return result;
}

boost::optional<double> CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::grossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel() const {
  return getDouble(Fields::GrossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel, true);
}

bool CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::isGrossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevelAutosized() const {
  if (const auto value = getString(Fields::GrossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::setGrossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel(
  double grossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel) {
  return setDouble(Fields::GrossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel, grossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel);
}

void CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::autosizeGrossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel() {
  OS_ASSERT(setString(Fields::GrossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel, "autosize"));
}

boost::optional<double> CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::autosizedGrossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel()
  const {
  return boost::none;
}

boost::optional<double> CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::ratedAirFlowRateAtSelectedNominalSpeedLevel() const {
  return getDouble(Fields::RatedAirFlowRateAtSelectedNominalSpeedLevel, true);
}

bool CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::isRatedAirFlowRateAtSelectedNominalSpeedLevelAutosized() const {
  if (const auto value = getString(Fields::RatedAirFlowRateAtSelectedNominalSpeedLevel, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::setRatedAirFlowRateAtSelectedNominalSpeedLevel(
  double ratedAirFlowRateAtSelectedNominalSpeedLevel) {
  return setDouble(Fields::RatedAirFlowRateAtSelectedNominalSpeedLevel, ratedAirFlowRateAtSelectedNominalSpeedLevel);
}

void CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::autosizeRatedAirFlowRateAtSelectedNominalSpeedLevel() {
  OS_ASSERT(setString(Fields::RatedAirFlowRateAtSelectedNominalSpeedLevel, "autosize"));
}

boost::optional<double> CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::autosizedRatedAirFlowRateAtSelectedNominalSpeedLevel() const {
  return boost::none;
}

boost::optional<double> CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::ratedWaterFlowRateAtSelectedNominalSpeedLevel() const {
  return getDouble(Fields::RatedWaterFlowRateAtSelectedNominalSpeedLevel, true);
}

bool CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::isRatedWaterFlowRateAtSelectedNominalSpeedLevelAutosized() const {
  if (const auto value = getString(Fields::RatedWaterFlowRateAtSelectedNominalSpeedLevel, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::setRatedWaterFlowRateAtSelectedNominalSpeedLevel(
  double ratedWaterFlowRateAtSelectedNominalSpeedLevel) {
  return setDouble(Fields::RatedWaterFlowRateAtSelectedNominalSpeedLevel, ratedWaterFlowRateAtSelectedNominalSpeedLevel);
}

void CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::autosizeRatedWaterFlowRateAtSelectedNominalSpeedLevel() {
  OS_ASSERT(setString(Fields::RatedWaterFlowRateAtSelectedNominalSpeedLevel, "autosize"));
}

boost::optional<double> CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::autosizedRatedWaterFlowRateAtSelectedNominalSpeedLevel() const {
  return boost::none;
}

double CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::nominalTimeforCondensatetoBeginLeavingtheCoil() const {
  const auto value = getDouble(Fields::NominalTimeforCondensatetoBeginLeavingtheCoil, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::setNominalTimeforCondensatetoBeginLeavingtheCoil(
  double nominalTimeforCondensatetoBeginLeavingtheCoil) {
  return setDouble(Fields::NominalTimeforCondensatetoBeginLeavingtheCoil, nominalTimeforCondensatetoBeginLeavingtheCoil);
}

double CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::initialMoistureEvaporationRateDividedbySteadyStateACLatentCapacity() const {
  const auto value = getDouble(Fields::InitialMoistureEvaporationRateDividedbySteadyStateACLatentCapacity, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::setInitialMoistureEvaporationRateDividedbySteadyStateACLatentCapacity(
  double initialMoistureEvaporationRateDividedbySteadyStateACLatentCapacity) {
  return setDouble(Fields::InitialMoistureEvaporationRateDividedbySteadyStateACLatentCapacity,
                   initialMoistureEvaporationRateDividedbySteadyStateACLatentCapacity);
}

double CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::maximumCyclingRate() const {
  const auto value = getDouble(Fields::MaximumCyclingRate, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::setMaximumCyclingRate(double maximumCyclingRate) {
  return setDouble(Fields::MaximumCyclingRate, maximumCyclingRate);
}

double CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::latentCapacityTimeConstant() const {
  const auto value = getDouble(Fields::LatentCapacityTimeConstant, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::setLatentCapacityTimeConstant(double latentCapacityTimeConstant) {
  return setDouble(Fields::LatentCapacityTimeConstant, latentCapacityTimeConstant);
}

double CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::fanDelayTime() const {
  const auto value = getDouble(Fields::FanDelayTime, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::setFanDelayTime(double fanDelayTime) {
  return setDouble(Fields::FanDelayTime, fanDelayTime);
}

bool CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::useHotGasReheat() const {
  const auto value = getInt(Fields::FlagforUsingHotGasReheat0or1, true);
  OS_ASSERT(value);
  return (*value == 1);
}

bool CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::setUseHotGasReheat(bool useHotGasReheat) {
  return setInt(Fields::FlagforUsingHotGasReheat0or1, useHotGasReheat ? 1 : 0);
}

Curve CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::energyPartLoadFractionCurve() const {
  auto value = getObject<ModelObject>().getModelObjectTarget<Curve>(Fields::EnergyPartLoadFractionCurveName);
  OS_ASSERT(value);
  return *value;
}

bool CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::setEnergyPartLoadFractionCurve(const Curve& curve) {
  return setPointer(Fields::EnergyPartLoadFractionCurveName, curve.handle(), false);
}

std::vector<CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData> CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::speeds() const {
  std::vector<CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData> result;
  const auto parent = getObject<openstudio::epmodel::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit>();
  const auto groups = parent.extensibleGroups();
  result.reserve(groups.size());
  for (unsigned i = 0; i < groups.size(); ++i) {
    result.push_back(model().getOrCreateTransientByName<openstudio::epmodel::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData>(
      detail::transientSpeedDataName(parent, i)));
  }
  return result;
}

bool CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::addSpeed(
  const CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData& speed) {
  const auto parent = getObject<openstudio::epmodel::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit>();
  auto group = getObject<ModelObject>().pushExtensibleGroup().cast<WorkspaceExtensibleGroup>();
  bool ok = true;
  ok = group.setDouble(ExtensibleFields::SpeedReferenceUnitGrossRatedTotalCoolingCapacity, speed.referenceUnitGrossRatedTotalCoolingCapacity()) && ok;
  ok = group.setDouble(ExtensibleFields::SpeedReferenceUnitGrossRatedSensibleHeatRatio, speed.referenceUnitGrossRatedSensibleHeatRatio()) && ok;
  ok = group.setDouble(ExtensibleFields::SpeedReferenceUnitGrossRatedCoolingCOP, speed.referenceUnitGrossRatedCoolingCOP()) && ok;
  ok = group.setDouble(ExtensibleFields::SpeedReferenceUnitRatedAirFlowRate, speed.referenceUnitRatedAirFlowRate()) && ok;
  ok = group.setDouble(ExtensibleFields::SpeedReferenceUnitRatedWaterFlowRate, speed.referenceUnitRatedWaterFlowRate()) && ok;
  ok = group.setPointer(ExtensibleFields::SpeedTotalCoolingCapacityFunctionofTemperatureCurveName,
                        speed.totalCoolingCapacityFunctionofTemperatureCurve().handle()) && ok;
  ok = group.setPointer(ExtensibleFields::SpeedTotalCoolingCapacityFunctionofAirFlowFractionCurveName,
                        speed.totalCoolingCapacityFunctionofAirFlowFractionCurve().handle()) && ok;
  ok = group.setPointer(ExtensibleFields::SpeedTotalCoolingCapacityFunctionofWaterFlowFractionCurveName,
                        speed.totalCoolingCapacityFunctionofWaterFlowFractionCurve().handle()) && ok;
  ok = group.setPointer(ExtensibleFields::SpeedEnergyInputRatioFunctionofTemperatureCurveName,
                        speed.energyInputRatioFunctionofTemperatureCurve().handle()) && ok;
  ok = group.setPointer(ExtensibleFields::SpeedEnergyInputRatioFunctionofAirFlowFractionCurveName,
                        speed.energyInputRatioFunctionofAirFlowFractionCurve().handle()) && ok;
  ok = group.setPointer(ExtensibleFields::SpeedEnergyInputRatioFunctionofWaterFlowFractionCurveName,
                        speed.energyInputRatioFunctionofWaterFlowFractionCurve().handle()) && ok;
  ok = group.setDouble(ExtensibleFields::SpeedReferenceUnitWasteHeatFractionofInputPowerAtRatedConditions,
                       speed.referenceUnitWasteHeatFractionofInputPowerAtRatedConditions()) && ok;
  ok = group.setPointer(ExtensibleFields::SpeedWasteHeatFunctionofTemperatureCurveName, speed.wasteHeatFunctionofTemperatureCurve().handle()) && ok;
  if (!ok) {
    getObject<ModelObject>().eraseExtensibleGroup(group.groupIndex());
    return false;
  }
  OS_ASSERT(setInt(Fields::NumberofSpeeds, static_cast<int>(getObject<ModelObject>().numExtensibleGroups())));
  auto attachedSpeed = speed;
  const bool renamed = attachedSpeed.setName(detail::transientSpeedDataName(parent, group.groupIndex())).has_value();
  OS_ASSERT(renamed);
  return true;
}

void CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::removeSpeed(
  const CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData& speed) {
  const auto parent = getObject<openstudio::epmodel::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit>();
  if (const auto speedName = speed.name()) {
    const auto groups = parent.extensibleGroups();
    for (unsigned i = 0; i < groups.size(); ++i) {
      if (openstudio::istringEqual(*speedName, detail::transientSpeedDataName(parent, i))) {
        const auto previousCount = static_cast<unsigned>(groups.size());
        getObject<ModelObject>().eraseExtensibleGroup(i);
        const auto remainingSpeeds = static_cast<int>(getObject<ModelObject>().numExtensibleGroups());
        for (unsigned oldIndex = i + 1; oldIndex < previousCount; ++oldIndex) {
          renameAttachedSpeedData(parent, oldIndex, oldIndex - 1);
        }
        if (remainingSpeeds > 0) {
          OS_ASSERT(setInt(Fields::NumberofSpeeds, remainingSpeeds));
        } else {
          OS_ASSERT(setString(Fields::NumberofSpeeds, ""));
        }
        if (remainingSpeeds > 0 && nominalSpeedLevel() > remainingSpeeds) {
          OS_ASSERT(setNominalSpeedLevel(remainingSpeeds));
        }
        return;
      }
    }
  }
}

void CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::removeAllSpeeds() {
  getObject<ModelObject>().clearExtensibleGroups();
  OS_ASSERT(setString(Fields::NumberofSpeeds, ""));
}

std::vector<ModelObject> CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::children() const {
  std::vector<ModelObject> result;
  for (const auto& speed : speeds()) {
    result.push_back(speed);
  }
  result.push_back(energyPartLoadFractionCurve());
  for (const auto& afnComponent : attachedAirflowNetworkDistributionComponentCoils(getObject<ModelObject>())) {
    result.push_back(afnComponent);
  }
  return result;
}

std::vector<IdfObject> CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::remove() {
  if (!isRemovable()) {
    return {};
  }

  auto speedWrappers = speeds();
  for (auto& speed : speedWrappers) {
    speed.remove();
  }

  for (auto& afnComponent : attachedAirflowNetworkDistributionComponentCoils(getObject<ModelObject>())) {
    afnComponent.remove();
  }

  return WaterToAirComponent_Impl::remove();
}

AirflowNetworkDistributionComponentCoil CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::getAirflowNetworkEquivalentDuct(double length,
                                                                                                                                     double diameter) {
  constexpr const char* coilObjectType = "Coil:Cooling:WaterToAirHeatPump:VariableSpeedEquationFit";
  if (auto component = airflowNetworkEquivalentDuct()) {
    if (!openstudio::istringEqual(component->coilObjectType(), coilObjectType)) {
      OS_ASSERT(component->setCoilObjectType(coilObjectType));
    }
    if (component->airPathLength() != length) {
      component->setAirPathLength(length);
    }
    if (component->airPathHydraulicDiameter() != diameter) {
      component->setAirPathHydraulicDiameter(diameter);
    }
    return *component;
  }

  AirflowNetworkDistributionComponentCoil component(model());
  OS_ASSERT(component.setPointer(openstudio::AirflowNetwork_Distribution_Component_CoilFields::CoilName, handle()));
  OS_ASSERT(component.setCoilObjectType(coilObjectType));
  OS_ASSERT(component.setAirPathLength(length));
  OS_ASSERT(component.setAirPathHydraulicDiameter(diameter));
  return component;
}

boost::optional<AirflowNetworkDistributionComponentCoil> CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::airflowNetworkEquivalentDuct() const {
  auto afnComponents = attachedAirflowNetworkDistributionComponentCoils(getObject<ModelObject>());
  if (afnComponents.size() == 1u) {
    return afnComponents.front();
  }
  if (afnComponents.size() > 1u) {
    LOG_FREE(Warn, "openstudio.epmodel.CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit",
             briefDescription() << " has more than one AirflowNetwork distribution component coil attached, returning first.");
    return afnComponents.front();
  }
  return boost::none;
}

void CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::setConstructorScalarDefaults() {
  OS_ASSERT(setNominalSpeedLevel(1));
  autosizeGrossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel();
  autosizeRatedAirFlowRateAtSelectedNominalSpeedLevel();
  autosizeRatedWaterFlowRateAtSelectedNominalSpeedLevel();
  OS_ASSERT(setNominalTimeforCondensatetoBeginLeavingtheCoil(0.0));
  OS_ASSERT(setInitialMoistureEvaporationRateDividedbySteadyStateACLatentCapacity(0.0));
  OS_ASSERT(setMaximumCyclingRate(2.5));
  OS_ASSERT(setLatentCapacityTimeConstant(60.0));
  OS_ASSERT(setFanDelayTime(60.0));
  OS_ASSERT(setUseHotGasReheat(false));
  OS_ASSERT(setString(Fields::NumberofSpeeds, ""));
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
