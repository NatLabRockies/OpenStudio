/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ZoneHVACComponent/ZoneHVACLowTempRadiantConstFlow.hpp"
#include "ZoneHVACComponent/ZoneHVACLowTempRadiantConstFlow_Impl.hpp"

#include "Model.hpp"
#include "ModelObject/ModelObject.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"
#include "StraightComponent/CoilCoolingLowTempRadiantConstFlow.hpp"
#include "StraightComponent/CoilCoolingLowTempRadiantConstFlow_Impl.hpp"
#include "StraightComponent/CoilHeatingLowTempRadiantConstFlow.hpp"
#include "StraightComponent/CoilHeatingLowTempRadiantConstFlow_Impl.hpp"

#include "../utilities/core/Assert.hpp"
#include "../utilities/core/Compare.hpp"

#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/ZoneHVAC_LowTemperatureRadiant_ConstantFlow_FieldEnums.hxx>
#include <utilities/idd/ZoneHVAC_LowTemperatureRadiant_ConstantFlow_Design_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {
namespace detail {

constexpr const char* kDefaultFluidtoRadiantSurfaceHeatTransferModel = "ConvectionOnly";
constexpr const char* kDefaultTemperatureControlType = "MeanAirTemperature";
constexpr double kDefaultHydronicTubingInsideDiameter = 0.013;
constexpr double kDefaultHydronicTubingOutsideDiameter = 0.016;
constexpr double kDefaultHydronicTubingConductivity = 0.35;
constexpr double kDefaultRunningMeanOutdoorDryBulbTemperatureWeightingFactor = 0.8;
constexpr double kDefaultMotorEfficiency = 0.9;
constexpr double kDefaultFractionofMotorInefficienciestoFluidStream = 0.0;

// These companion coils are transient views over parent-owned storage, so they
// still need a stable model-level identity while the parent exists. We key that
// identity off the parent handle instead of the parent display name so a rename
// does not orphan the transient child. The "__transient__" prefix is just a
// blunt marker that this name is internal plumbing, not a user-facing naming
// convention.
std::string transientHeatingCoilName(const openstudio::epmodel::ZoneHVACLowTempRadiantConstFlow& parent) {
  return "__transient__" + openstudio::toString(parent.handle()) + "__heating_low_temp_radiant_const_flow";
}

std::string transientCoolingCoilName(const openstudio::epmodel::ZoneHVACLowTempRadiantConstFlow& parent) {
  return "__transient__" + openstudio::toString(parent.handle()) + "__cooling_low_temp_radiant_const_flow";
}

}  // namespace detail

ZoneHVACLowTempRadiantConstFlow::ZoneHVACLowTempRadiantConstFlow(const Model& model)
  : ZoneHVACComponent(ZoneHVACLowTempRadiantConstFlow::iddObjectType(), model) {
  auto impl = getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>();
  OS_ASSERT(impl);
  impl->ensureDesignObject();
}

ZoneHVACLowTempRadiantConstFlow::ZoneHVACLowTempRadiantConstFlow(std::shared_ptr<detail::ZoneHVACLowTempRadiantConstFlow_Impl> impl)
  : ZoneHVACComponent(std::move(impl)) {}

IddObjectType ZoneHVACLowTempRadiantConstFlow::iddObjectType() {
  return IddObjectType::ZoneHVAC_LowTemperatureRadiant_ConstantFlow;
}

std::vector<std::string> ZoneHVACLowTempRadiantConstFlow::numberofCircuitsValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::NumberofCircuits);
}

std::vector<std::string> ZoneHVACLowTempRadiantConstFlow::fluidtoRadiantSurfaceHeatTransferModelValues() {
  return getIddKeyNames(IddFactory::instance().getObject(IddObjectType::ZoneHVAC_LowTemperatureRadiant_ConstantFlow_Design).get(),
                        ZoneHVAC_LowTemperatureRadiant_ConstantFlow_DesignFields::FluidtoRadiantSurfaceHeatTransferModel);
}

std::vector<std::string> ZoneHVACLowTempRadiantConstFlow::temperatureControlTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(IddObjectType::ZoneHVAC_LowTemperatureRadiant_ConstantFlow_Design).get(),
                        ZoneHVAC_LowTemperatureRadiant_ConstantFlow_DesignFields::TemperatureControlType);
}

boost::optional<Schedule> ZoneHVACLowTempRadiantConstFlow::availabilitySchedule() const {
  return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->availabilitySchedule();
}

bool ZoneHVACLowTempRadiantConstFlow::setAvailabilitySchedule(Schedule& schedule) {
  return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->setAvailabilitySchedule(schedule);
}

void ZoneHVACLowTempRadiantConstFlow::resetAvailabilitySchedule() {
  getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->resetAvailabilitySchedule();
}

CoilHeatingLowTempRadiantConstFlow ZoneHVACLowTempRadiantConstFlow::heatingCoil() const {
  return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->heatingCoil();
}

CoilCoolingLowTempRadiantConstFlow ZoneHVACLowTempRadiantConstFlow::coolingCoil() const {
  return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->coolingCoil();
}

boost::optional<Schedule> ZoneHVACLowTempRadiantConstFlow::pumpFlowRateSchedule() const {
  return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->pumpFlowRateSchedule();
}

bool ZoneHVACLowTempRadiantConstFlow::setPumpFlowRateSchedule(Schedule& schedule) {
  return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->setPumpFlowRateSchedule(schedule);
}

void ZoneHVACLowTempRadiantConstFlow::resetPumpFlowRateSchedule() {
  getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->resetPumpFlowRateSchedule();
}

boost::optional<Schedule> ZoneHVACLowTempRadiantConstFlow::changeoverDelayTimePeriodSchedule() const {
  return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->changeoverDelayTimePeriodSchedule();
}

bool ZoneHVACLowTempRadiantConstFlow::setChangeoverDelayTimePeriodSchedule(Schedule& schedule) {
  return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->setChangeoverDelayTimePeriodSchedule(schedule);
}

void ZoneHVACLowTempRadiantConstFlow::resetChangeoverDelayTimePeriodSchedule() {
  getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->resetChangeoverDelayTimePeriodSchedule();
}

std::vector<ModelObject> ZoneHVACLowTempRadiantConstFlow::children() const {
  return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->children();
}

std::string ZoneHVACLowTempRadiantConstFlow::fluidtoRadiantSurfaceHeatTransferModel() const {
  return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->fluidtoRadiantSurfaceHeatTransferModel();
}

bool ZoneHVACLowTempRadiantConstFlow::isFluidtoRadiantSurfaceHeatTransferModelDefaulted() const {
  return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->isFluidtoRadiantSurfaceHeatTransferModelDefaulted();
}

bool ZoneHVACLowTempRadiantConstFlow::setFluidtoRadiantSurfaceHeatTransferModel(const std::string& fluidtoRadiantSurfaceHeatTransferModel) {
  return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->setFluidtoRadiantSurfaceHeatTransferModel(
    fluidtoRadiantSurfaceHeatTransferModel);
}

void ZoneHVACLowTempRadiantConstFlow::resetFluidtoRadiantSurfaceHeatTransferModel() {
  getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->resetFluidtoRadiantSurfaceHeatTransferModel();
}

double ZoneHVACLowTempRadiantConstFlow::hydronicTubingInsideDiameter() const {
  return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->hydronicTubingInsideDiameter();
}

bool ZoneHVACLowTempRadiantConstFlow::isHydronicTubingInsideDiameterDefaulted() const {
  return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->isHydronicTubingInsideDiameterDefaulted();
}

bool ZoneHVACLowTempRadiantConstFlow::setHydronicTubingInsideDiameter(double hydronicTubingInsideDiameter) {
  return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->setHydronicTubingInsideDiameter(hydronicTubingInsideDiameter);
}

void ZoneHVACLowTempRadiantConstFlow::resetHydronicTubingInsideDiameter() {
  getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->resetHydronicTubingInsideDiameter();
}

double ZoneHVACLowTempRadiantConstFlow::hydronicTubingOutsideDiameter() const {
  return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->hydronicTubingOutsideDiameter();
}

bool ZoneHVACLowTempRadiantConstFlow::isHydronicTubingOutsideDiameterDefaulted() const {
  return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->isHydronicTubingOutsideDiameterDefaulted();
}

bool ZoneHVACLowTempRadiantConstFlow::setHydronicTubingOutsideDiameter(double hydronicTubingOutsideDiameter) {
  return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->setHydronicTubingOutsideDiameter(hydronicTubingOutsideDiameter);
}

void ZoneHVACLowTempRadiantConstFlow::resetHydronicTubingOutsideDiameter() {
  getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->resetHydronicTubingOutsideDiameter();
}

double ZoneHVACLowTempRadiantConstFlow::hydronicTubingConductivity() const {
  return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->hydronicTubingConductivity();
}

bool ZoneHVACLowTempRadiantConstFlow::isHydronicTubingConductivityDefaulted() const {
  return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->isHydronicTubingConductivityDefaulted();
}

bool ZoneHVACLowTempRadiantConstFlow::setHydronicTubingConductivity(double hydronicTubingConductivity) {
  return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->setHydronicTubingConductivity(hydronicTubingConductivity);
}

void ZoneHVACLowTempRadiantConstFlow::resetHydronicTubingConductivity() {
  getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->resetHydronicTubingConductivity();
}

std::string ZoneHVACLowTempRadiantConstFlow::temperatureControlType() const {
  return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->temperatureControlType();
}

bool ZoneHVACLowTempRadiantConstFlow::isTemperatureControlTypeDefaulted() const {
  return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->isTemperatureControlTypeDefaulted();
}

bool ZoneHVACLowTempRadiantConstFlow::setTemperatureControlType(const std::string& temperatureControlType) {
  return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->setTemperatureControlType(temperatureControlType);
}

void ZoneHVACLowTempRadiantConstFlow::resetTemperatureControlType() {
  getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->resetTemperatureControlType();
}

double ZoneHVACLowTempRadiantConstFlow::runningMeanOutdoorDryBulbTemperatureWeightingFactor() const {
  return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->runningMeanOutdoorDryBulbTemperatureWeightingFactor();
}

bool ZoneHVACLowTempRadiantConstFlow::isRunningMeanOutdoorDryBulbTemperatureWeightingFactorDefaulted() const {
  return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->isRunningMeanOutdoorDryBulbTemperatureWeightingFactorDefaulted();
}

bool ZoneHVACLowTempRadiantConstFlow::setRunningMeanOutdoorDryBulbTemperatureWeightingFactor(
  double runningMeanOutdoorDryBulbTemperatureWeightingFactor) {
  return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->setRunningMeanOutdoorDryBulbTemperatureWeightingFactor(
    runningMeanOutdoorDryBulbTemperatureWeightingFactor);
}

void ZoneHVACLowTempRadiantConstFlow::resetRunningMeanOutdoorDryBulbTemperatureWeightingFactor() {
  getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->resetRunningMeanOutdoorDryBulbTemperatureWeightingFactor();
}

double ZoneHVACLowTempRadiantConstFlow::motorEfficiency() const {
  return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->motorEfficiency();
}

bool ZoneHVACLowTempRadiantConstFlow::isMotorEfficiencyDefaulted() const {
  return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->isMotorEfficiencyDefaulted();
}

bool ZoneHVACLowTempRadiantConstFlow::setMotorEfficiency(double motorEfficiency) {
  return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->setMotorEfficiency(motorEfficiency);
}

void ZoneHVACLowTempRadiantConstFlow::resetMotorEfficiency() {
  getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->resetMotorEfficiency();
}

double ZoneHVACLowTempRadiantConstFlow::fractionofMotorInefficienciestoFluidStream() const {
  return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->fractionofMotorInefficienciestoFluidStream();
}

bool ZoneHVACLowTempRadiantConstFlow::isFractionofMotorInefficienciestoFluidStreamDefaulted() const {
  return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->isFractionofMotorInefficienciestoFluidStreamDefaulted();
}

bool ZoneHVACLowTempRadiantConstFlow::setFractionofMotorInefficienciestoFluidStream(double fractionofMotorInefficienciestoFluidStream) {
  return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->setFractionofMotorInefficienciestoFluidStream(
    fractionofMotorInefficienciestoFluidStream);
}

void ZoneHVACLowTempRadiantConstFlow::resetFractionofMotorInefficienciestoFluidStream() {
  getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->resetFractionofMotorInefficienciestoFluidStream();
}

boost::optional<double> ZoneHVACLowTempRadiantConstFlow::hydronicTubingLength() const {
  return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->hydronicTubingLength();
}

bool ZoneHVACLowTempRadiantConstFlow::isHydronicTubingLengthAutosized() const {
  return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->isHydronicTubingLengthAutosized();
}

bool ZoneHVACLowTempRadiantConstFlow::setHydronicTubingLength(double hydronicTubingLength) {
  return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->setHydronicTubingLength(hydronicTubingLength);
}

void ZoneHVACLowTempRadiantConstFlow::autosizeHydronicTubingLength() {
  getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->autosizeHydronicTubingLength();
}

boost::optional<double> ZoneHVACLowTempRadiantConstFlow::ratedFlowRate() const {
  return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->ratedFlowRate();
}

bool ZoneHVACLowTempRadiantConstFlow::isRatedFlowRateAutosized() const {
  return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->isRatedFlowRateAutosized();
}

bool ZoneHVACLowTempRadiantConstFlow::setRatedFlowRate(double ratedFlowRate) {
  return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->setRatedFlowRate(ratedFlowRate);
}

void ZoneHVACLowTempRadiantConstFlow::autosizeRatedFlowRate() {
  getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->autosizeRatedFlowRate();
}

double ZoneHVACLowTempRadiantConstFlow::ratedPumpHead() const {
  return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->ratedPumpHead();
}

bool ZoneHVACLowTempRadiantConstFlow::isRatedPumpHeadDefaulted() const {
  return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->isRatedPumpHeadDefaulted();
}

bool ZoneHVACLowTempRadiantConstFlow::setRatedPumpHead(double ratedPumpHead) {
  return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->setRatedPumpHead(ratedPumpHead);
}

void ZoneHVACLowTempRadiantConstFlow::resetRatedPumpHead() {
  getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->resetRatedPumpHead();
}

boost::optional<double> ZoneHVACLowTempRadiantConstFlow::ratedPowerConsumption() const {
  return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->ratedPowerConsumption();
}

bool ZoneHVACLowTempRadiantConstFlow::setRatedPowerConsumption(double ratedPowerConsumption) {
  return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->setRatedPowerConsumption(ratedPowerConsumption);
}

void ZoneHVACLowTempRadiantConstFlow::resetRatedPowerConsumption() {
  getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->resetRatedPowerConsumption();
}

std::string ZoneHVACLowTempRadiantConstFlow::numberofCircuits() const {
  return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->numberofCircuits();
}

bool ZoneHVACLowTempRadiantConstFlow::isNumberofCircuitsDefaulted() const {
  return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->isNumberofCircuitsDefaulted();
}

bool ZoneHVACLowTempRadiantConstFlow::setNumberofCircuits(const std::string& numberofCircuits) {
  return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->setNumberofCircuits(numberofCircuits);
}

void ZoneHVACLowTempRadiantConstFlow::resetNumberofCircuits() {
  getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->resetNumberofCircuits();
}

double ZoneHVACLowTempRadiantConstFlow::circuitLength() const {
  return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->circuitLength();
}

bool ZoneHVACLowTempRadiantConstFlow::isCircuitLengthDefaulted() const {
  return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->isCircuitLengthDefaulted();
}

bool ZoneHVACLowTempRadiantConstFlow::setCircuitLength(double circuitLength) {
  return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->setCircuitLength(circuitLength);
}

void ZoneHVACLowTempRadiantConstFlow::resetCircuitLength() {
  getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->resetCircuitLength();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

unsigned ZoneHVACLowTempRadiantConstFlow_Impl::inletPort() const {
  return 0u;
}

unsigned ZoneHVACLowTempRadiantConstFlow_Impl::outletPort() const {
  return 0u;
}

boost::optional<Schedule> ZoneHVACLowTempRadiantConstFlow_Impl::availabilitySchedule() const {
  return getObject<ModelObject>().getModelObjectTarget<Schedule>(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::AvailabilityScheduleName);
}

bool ZoneHVACLowTempRadiantConstFlow_Impl::setAvailabilitySchedule(Schedule& schedule) {
  return setPointer(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::AvailabilityScheduleName, schedule.handle(), false);
}

void ZoneHVACLowTempRadiantConstFlow_Impl::resetAvailabilitySchedule() {
  OS_ASSERT(setString(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::AvailabilityScheduleName, "", false));
}

CoilHeatingLowTempRadiantConstFlow ZoneHVACLowTempRadiantConstFlow_Impl::heatingCoil() const {
  const auto parent = getObject<openstudio::epmodel::ZoneHVACLowTempRadiantConstFlow>();
  return model().getOrCreateTransientByName<openstudio::epmodel::CoilHeatingLowTempRadiantConstFlow>(detail::transientHeatingCoilName(parent));
}

CoilCoolingLowTempRadiantConstFlow ZoneHVACLowTempRadiantConstFlow_Impl::coolingCoil() const {
  const auto parent = getObject<openstudio::epmodel::ZoneHVACLowTempRadiantConstFlow>();
  return model().getOrCreateTransientByName<openstudio::epmodel::CoilCoolingLowTempRadiantConstFlow>(detail::transientCoolingCoilName(parent));
}

boost::optional<Schedule> ZoneHVACLowTempRadiantConstFlow_Impl::pumpFlowRateSchedule() const {
  return getObject<ModelObject>().getModelObjectTarget<Schedule>(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::PumpFlowRateScheduleName);
}

bool ZoneHVACLowTempRadiantConstFlow_Impl::setPumpFlowRateSchedule(Schedule& schedule) {
  return setPointer(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::PumpFlowRateScheduleName, schedule.handle(), false);
}

void ZoneHVACLowTempRadiantConstFlow_Impl::resetPumpFlowRateSchedule() {
  OS_ASSERT(setString(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::PumpFlowRateScheduleName, "", false));
}

boost::optional<Schedule> ZoneHVACLowTempRadiantConstFlow_Impl::changeoverDelayTimePeriodSchedule() const {
  if (auto design = designObject()) {
    return design->getModelObjectTarget<Schedule>(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlow_DesignFields::ChangeoverDelayTimePeriodSchedule);
  }
  return boost::none;
}

bool ZoneHVACLowTempRadiantConstFlow_Impl::setChangeoverDelayTimePeriodSchedule(Schedule& schedule) {
  auto design = ensureDesignObject();
  return design.setPointer(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlow_DesignFields::ChangeoverDelayTimePeriodSchedule,
                           schedule.handle());
}

void ZoneHVACLowTempRadiantConstFlow_Impl::resetChangeoverDelayTimePeriodSchedule() {
  auto design = ensureDesignObject();
  OS_ASSERT(design.setString(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlow_DesignFields::ChangeoverDelayTimePeriodSchedule, ""));
}

std::vector<ModelObject> ZoneHVACLowTempRadiantConstFlow_Impl::children() const {
  return {heatingCoil().cast<ModelObject>(), coolingCoil().cast<ModelObject>()};
}

void ZoneHVACLowTempRadiantConstFlow_Impl::doCanonicalize(LoadContext& context) {
  if (context.repairEnabled()) {
    ensureDesignObject();
  }
}

boost::optional<ModelObject> ZoneHVACLowTempRadiantConstFlow_Impl::designObject() const {
  if (auto target = getTarget(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::DesignObject)) {
    if (auto typed = target->optionalCast<ModelObject>()) {
      return *typed;
    }
  }

  if (auto name = getString(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::DesignObject, true); name && !name->empty()) {
    if (auto obj = workspace().getObjectByTypeAndName(IddObjectType::ZoneHVAC_LowTemperatureRadiant_ConstantFlow_Design, *name, true)) {
      if (auto typed = obj->optionalCast<ModelObject>()) {
        auto* self = const_cast<ZoneHVACLowTempRadiantConstFlow_Impl*>(this);
        self->setPointer(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::DesignObject, typed->handle(), false);
        return *typed;
      }
    }
  }

  return boost::none;
}

ModelObject ZoneHVACLowTempRadiantConstFlow_Impl::ensureDesignObject() {
  if (auto existing = designObject()) {
    return *existing;
  }

  auto created = ModelObject::create(IddObjectType::ZoneHVAC_LowTemperatureRadiant_ConstantFlow_Design, model());
  if (const auto existingName = getString(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::DesignObject, true);
      existingName && !existingName->empty()) {
    created.setName(*existingName);
  } else {
    created.setName(getObject<ModelObject>().nameString() + " Design");
  }
  OS_ASSERT(setPointer(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::DesignObject, created.handle(), false));
  return created;
}

std::string ZoneHVACLowTempRadiantConstFlow_Impl::fluidtoRadiantSurfaceHeatTransferModel() const {
  if (const auto design = designObject()) {
    if (const auto value =
          design->getString(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlow_DesignFields::FluidtoRadiantSurfaceHeatTransferModel, true)) {
      return *value;
    }
  }
  return kDefaultFluidtoRadiantSurfaceHeatTransferModel;
}

bool ZoneHVACLowTempRadiantConstFlow_Impl::isFluidtoRadiantSurfaceHeatTransferModelDefaulted() const {
  if (const auto design = designObject()) {
    return design->isEmpty(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlow_DesignFields::FluidtoRadiantSurfaceHeatTransferModel);
  }
  return true;
}

bool ZoneHVACLowTempRadiantConstFlow_Impl::setFluidtoRadiantSurfaceHeatTransferModel(
  const std::string& fluidtoRadiantSurfaceHeatTransferModel) {
  auto design = ensureDesignObject();
  return design.setString(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlow_DesignFields::FluidtoRadiantSurfaceHeatTransferModel,
                          fluidtoRadiantSurfaceHeatTransferModel);
}

void ZoneHVACLowTempRadiantConstFlow_Impl::resetFluidtoRadiantSurfaceHeatTransferModel() {
  auto design = ensureDesignObject();
  OS_ASSERT(design.setString(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlow_DesignFields::FluidtoRadiantSurfaceHeatTransferModel, ""));
}

double ZoneHVACLowTempRadiantConstFlow_Impl::hydronicTubingInsideDiameter() const {
  if (const auto design = designObject()) {
    if (const auto value = design->getDouble(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlow_DesignFields::HydronicTubingInsideDiameter, true)) {
      return *value;
    }
  }
  return kDefaultHydronicTubingInsideDiameter;
}

bool ZoneHVACLowTempRadiantConstFlow_Impl::isHydronicTubingInsideDiameterDefaulted() const {
  if (const auto design = designObject()) {
    return design->isEmpty(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlow_DesignFields::HydronicTubingInsideDiameter);
  }
  return true;
}

bool ZoneHVACLowTempRadiantConstFlow_Impl::setHydronicTubingInsideDiameter(double hydronicTubingInsideDiameter) {
  auto design = ensureDesignObject();
  return design.setDouble(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlow_DesignFields::HydronicTubingInsideDiameter,
                          hydronicTubingInsideDiameter);
}

void ZoneHVACLowTempRadiantConstFlow_Impl::resetHydronicTubingInsideDiameter() {
  auto design = ensureDesignObject();
  OS_ASSERT(design.setString(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlow_DesignFields::HydronicTubingInsideDiameter, ""));
}

double ZoneHVACLowTempRadiantConstFlow_Impl::hydronicTubingOutsideDiameter() const {
  if (const auto design = designObject()) {
    if (const auto value =
          design->getDouble(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlow_DesignFields::HydronicTubingOutsideDiameter, true)) {
      return *value;
    }
  }
  return kDefaultHydronicTubingOutsideDiameter;
}

bool ZoneHVACLowTempRadiantConstFlow_Impl::isHydronicTubingOutsideDiameterDefaulted() const {
  if (const auto design = designObject()) {
    return design->isEmpty(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlow_DesignFields::HydronicTubingOutsideDiameter);
  }
  return true;
}

bool ZoneHVACLowTempRadiantConstFlow_Impl::setHydronicTubingOutsideDiameter(double hydronicTubingOutsideDiameter) {
  auto design = ensureDesignObject();
  return design.setDouble(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlow_DesignFields::HydronicTubingOutsideDiameter,
                          hydronicTubingOutsideDiameter);
}

void ZoneHVACLowTempRadiantConstFlow_Impl::resetHydronicTubingOutsideDiameter() {
  auto design = ensureDesignObject();
  OS_ASSERT(design.setString(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlow_DesignFields::HydronicTubingOutsideDiameter, ""));
}

double ZoneHVACLowTempRadiantConstFlow_Impl::hydronicTubingConductivity() const {
  if (const auto design = designObject()) {
    if (const auto value = design->getDouble(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlow_DesignFields::HydronicTubingConductivity, true)) {
      return *value;
    }
  }
  return kDefaultHydronicTubingConductivity;
}

bool ZoneHVACLowTempRadiantConstFlow_Impl::isHydronicTubingConductivityDefaulted() const {
  if (const auto design = designObject()) {
    return design->isEmpty(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlow_DesignFields::HydronicTubingConductivity);
  }
  return true;
}

bool ZoneHVACLowTempRadiantConstFlow_Impl::setHydronicTubingConductivity(double hydronicTubingConductivity) {
  auto design = ensureDesignObject();
  return design.setDouble(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlow_DesignFields::HydronicTubingConductivity,
                          hydronicTubingConductivity);
}

void ZoneHVACLowTempRadiantConstFlow_Impl::resetHydronicTubingConductivity() {
  auto design = ensureDesignObject();
  OS_ASSERT(design.setString(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlow_DesignFields::HydronicTubingConductivity, ""));
}

std::string ZoneHVACLowTempRadiantConstFlow_Impl::temperatureControlType() const {
  if (const auto design = designObject()) {
    if (const auto value = design->getString(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlow_DesignFields::TemperatureControlType, true)) {
      return *value;
    }
  }
  return kDefaultTemperatureControlType;
}

bool ZoneHVACLowTempRadiantConstFlow_Impl::isTemperatureControlTypeDefaulted() const {
  if (const auto design = designObject()) {
    return design->isEmpty(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlow_DesignFields::TemperatureControlType);
  }
  return true;
}

bool ZoneHVACLowTempRadiantConstFlow_Impl::setTemperatureControlType(const std::string& temperatureControlType) {
  auto design = ensureDesignObject();
  return design.setString(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlow_DesignFields::TemperatureControlType, temperatureControlType);
}

void ZoneHVACLowTempRadiantConstFlow_Impl::resetTemperatureControlType() {
  auto design = ensureDesignObject();
  OS_ASSERT(design.setString(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlow_DesignFields::TemperatureControlType, ""));
}

double ZoneHVACLowTempRadiantConstFlow_Impl::runningMeanOutdoorDryBulbTemperatureWeightingFactor() const {
  if (const auto design = designObject()) {
    if (const auto value = design->getDouble(
          openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlow_DesignFields::RunningMeanOutdoorDryBulbTemperatureWeightingFactor, true)) {
      return *value;
    }
  }
  return kDefaultRunningMeanOutdoorDryBulbTemperatureWeightingFactor;
}

bool ZoneHVACLowTempRadiantConstFlow_Impl::isRunningMeanOutdoorDryBulbTemperatureWeightingFactorDefaulted() const {
  if (const auto design = designObject()) {
    return design->isEmpty(
      openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlow_DesignFields::RunningMeanOutdoorDryBulbTemperatureWeightingFactor);
  }
  return true;
}

bool ZoneHVACLowTempRadiantConstFlow_Impl::setRunningMeanOutdoorDryBulbTemperatureWeightingFactor(
  double runningMeanOutdoorDryBulbTemperatureWeightingFactor) {
  auto design = ensureDesignObject();
  return design.setDouble(
    openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlow_DesignFields::RunningMeanOutdoorDryBulbTemperatureWeightingFactor,
    runningMeanOutdoorDryBulbTemperatureWeightingFactor);
}

void ZoneHVACLowTempRadiantConstFlow_Impl::resetRunningMeanOutdoorDryBulbTemperatureWeightingFactor() {
  auto design = ensureDesignObject();
  OS_ASSERT(design.setString(
    openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlow_DesignFields::RunningMeanOutdoorDryBulbTemperatureWeightingFactor, ""));
}

double ZoneHVACLowTempRadiantConstFlow_Impl::motorEfficiency() const {
  if (const auto design = designObject()) {
    if (const auto value = design->getDouble(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlow_DesignFields::MotorEfficiency, true)) {
      return *value;
    }
  }
  return kDefaultMotorEfficiency;
}

bool ZoneHVACLowTempRadiantConstFlow_Impl::isMotorEfficiencyDefaulted() const {
  if (const auto design = designObject()) {
    return design->isEmpty(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlow_DesignFields::MotorEfficiency);
  }
  return true;
}

bool ZoneHVACLowTempRadiantConstFlow_Impl::setMotorEfficiency(double motorEfficiency) {
  auto design = ensureDesignObject();
  return design.setDouble(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlow_DesignFields::MotorEfficiency, motorEfficiency);
}

void ZoneHVACLowTempRadiantConstFlow_Impl::resetMotorEfficiency() {
  auto design = ensureDesignObject();
  OS_ASSERT(design.setString(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlow_DesignFields::MotorEfficiency, ""));
}

double ZoneHVACLowTempRadiantConstFlow_Impl::fractionofMotorInefficienciestoFluidStream() const {
  if (const auto design = designObject()) {
    if (const auto value = design->getDouble(
          openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlow_DesignFields::FractionofMotorInefficienciestoFluidStream, true)) {
      return *value;
    }
  }
  return kDefaultFractionofMotorInefficienciestoFluidStream;
}

bool ZoneHVACLowTempRadiantConstFlow_Impl::isFractionofMotorInefficienciestoFluidStreamDefaulted() const {
  if (const auto design = designObject()) {
    return design->isEmpty(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlow_DesignFields::FractionofMotorInefficienciestoFluidStream);
  }
  return true;
}

bool ZoneHVACLowTempRadiantConstFlow_Impl::setFractionofMotorInefficienciestoFluidStream(
  double fractionofMotorInefficienciestoFluidStream) {
  auto design = ensureDesignObject();
  return design.setDouble(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlow_DesignFields::FractionofMotorInefficienciestoFluidStream,
                          fractionofMotorInefficienciestoFluidStream);
}

void ZoneHVACLowTempRadiantConstFlow_Impl::resetFractionofMotorInefficienciestoFluidStream() {
  auto design = ensureDesignObject();
  OS_ASSERT(design.setString(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlow_DesignFields::FractionofMotorInefficienciestoFluidStream,
                             ""));
}

boost::optional<double> ZoneHVACLowTempRadiantConstFlow_Impl::hydronicTubingLength() const {
  return getDouble(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::HydronicTubingLength, true);
}

bool ZoneHVACLowTempRadiantConstFlow_Impl::isHydronicTubingLengthAutosized() const {
  if (auto value = getString(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::HydronicTubingLength, true)) {
    return openstudio::istringEqual(*value, "Autosize");
  }
  return false;
}

bool ZoneHVACLowTempRadiantConstFlow_Impl::setHydronicTubingLength(double hydronicTubingLength) {
  return setDouble(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::HydronicTubingLength, hydronicTubingLength, false);
}

void ZoneHVACLowTempRadiantConstFlow_Impl::autosizeHydronicTubingLength() {
  OS_ASSERT(setString(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::HydronicTubingLength, "Autosize", false));
}

boost::optional<double> ZoneHVACLowTempRadiantConstFlow_Impl::ratedFlowRate() const {
  return getDouble(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::RatedFlowRate, true);
}

bool ZoneHVACLowTempRadiantConstFlow_Impl::isRatedFlowRateAutosized() const {
  if (auto value = getString(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::RatedFlowRate, true)) {
    return openstudio::istringEqual(*value, "Autosize");
  }
  return false;
}

bool ZoneHVACLowTempRadiantConstFlow_Impl::setRatedFlowRate(double ratedFlowRate) {
  return setDouble(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::RatedFlowRate, ratedFlowRate, false);
}

void ZoneHVACLowTempRadiantConstFlow_Impl::autosizeRatedFlowRate() {
  OS_ASSERT(setString(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::RatedFlowRate, "Autosize", false));
}

double ZoneHVACLowTempRadiantConstFlow_Impl::ratedPumpHead() const {
  auto value = getDouble(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::RatedPumpHead, true);
  OS_ASSERT(value);
  return *value;
}

bool ZoneHVACLowTempRadiantConstFlow_Impl::isRatedPumpHeadDefaulted() const {
  return isEmpty(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::RatedPumpHead);
}

bool ZoneHVACLowTempRadiantConstFlow_Impl::setRatedPumpHead(double ratedPumpHead) {
  return setDouble(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::RatedPumpHead, ratedPumpHead, false);
}

void ZoneHVACLowTempRadiantConstFlow_Impl::resetRatedPumpHead() {
  OS_ASSERT(setString(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::RatedPumpHead, "", false));
}

boost::optional<double> ZoneHVACLowTempRadiantConstFlow_Impl::ratedPowerConsumption() const {
  return getDouble(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::RatedPowerConsumption, true);
}

bool ZoneHVACLowTempRadiantConstFlow_Impl::setRatedPowerConsumption(double ratedPowerConsumption) {
  return setDouble(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::RatedPowerConsumption, ratedPowerConsumption, false);
}

void ZoneHVACLowTempRadiantConstFlow_Impl::resetRatedPowerConsumption() {
  OS_ASSERT(setString(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::RatedPowerConsumption, "", false));
}

std::string ZoneHVACLowTempRadiantConstFlow_Impl::numberofCircuits() const {
  auto value = getString(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::NumberofCircuits, true);
  OS_ASSERT(value);
  return *value;
}

bool ZoneHVACLowTempRadiantConstFlow_Impl::isNumberofCircuitsDefaulted() const {
  return isEmpty(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::NumberofCircuits);
}

bool ZoneHVACLowTempRadiantConstFlow_Impl::setNumberofCircuits(const std::string& numberofCircuits) {
  return setString(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::NumberofCircuits, numberofCircuits, false);
}

void ZoneHVACLowTempRadiantConstFlow_Impl::resetNumberofCircuits() {
  OS_ASSERT(setString(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::NumberofCircuits, "", false));
}

double ZoneHVACLowTempRadiantConstFlow_Impl::circuitLength() const {
  auto value = getDouble(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::CircuitLength, true);
  OS_ASSERT(value);
  return *value;
}

bool ZoneHVACLowTempRadiantConstFlow_Impl::isCircuitLengthDefaulted() const {
  return isEmpty(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::CircuitLength);
}

bool ZoneHVACLowTempRadiantConstFlow_Impl::setCircuitLength(double circuitLength) {
  return setDouble(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::CircuitLength, circuitLength, false);
}

void ZoneHVACLowTempRadiantConstFlow_Impl::resetCircuitLength() {
  OS_ASSERT(setString(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::CircuitLength, "", false));
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
