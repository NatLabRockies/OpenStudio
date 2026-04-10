/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ModelObject/ZoneHVACLowTempRadiantConstFlowDesign.hpp"
#include "ModelObject/ZoneHVACLowTempRadiantConstFlowDesign_Impl.hpp"

#include "Model.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddEnums.hxx>
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
constexpr const char* kDefaultCondensationControlType = "SimpleOff";
constexpr double kDefaultCondensationControlDewpointOffset = 1.0;
}  // namespace detail

ZoneHVACLowTempRadiantConstFlowDesign::ZoneHVACLowTempRadiantConstFlowDesign(const Model& model)
  : ModelObject(ZoneHVACLowTempRadiantConstFlowDesign::iddObjectType(), model) {
  OS_ASSERT(getImpl<detail::ZoneHVACLowTempRadiantConstFlowDesign_Impl>());
}

ZoneHVACLowTempRadiantConstFlowDesign::ZoneHVACLowTempRadiantConstFlowDesign(
  std::shared_ptr<detail::ZoneHVACLowTempRadiantConstFlowDesign_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType ZoneHVACLowTempRadiantConstFlowDesign::iddObjectType() {
  return IddObjectType::ZoneHVAC_LowTemperatureRadiant_ConstantFlow_Design;
}

std::vector<std::string> ZoneHVACLowTempRadiantConstFlowDesign::fluidtoRadiantSurfaceHeatTransferModelValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        ZoneHVAC_LowTemperatureRadiant_ConstantFlow_DesignFields::FluidtoRadiantSurfaceHeatTransferModel);
}

std::vector<std::string> ZoneHVACLowTempRadiantConstFlowDesign::temperatureControlTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        ZoneHVAC_LowTemperatureRadiant_ConstantFlow_DesignFields::TemperatureControlType);
}

boost::optional<Schedule> ZoneHVACLowTempRadiantConstFlowDesign::changeoverDelayTimePeriodSchedule() const {
  return getImpl<detail::ZoneHVACLowTempRadiantConstFlowDesign_Impl>()->changeoverDelayTimePeriodSchedule();
}

std::string ZoneHVACLowTempRadiantConstFlowDesign::fluidtoRadiantSurfaceHeatTransferModel() const {
  return getImpl<detail::ZoneHVACLowTempRadiantConstFlowDesign_Impl>()->fluidtoRadiantSurfaceHeatTransferModel();
}

bool ZoneHVACLowTempRadiantConstFlowDesign::isFluidtoRadiantSurfaceHeatTransferModelDefaulted() const {
  return getImpl<detail::ZoneHVACLowTempRadiantConstFlowDesign_Impl>()->isFluidtoRadiantSurfaceHeatTransferModelDefaulted();
}

double ZoneHVACLowTempRadiantConstFlowDesign::hydronicTubingInsideDiameter() const {
  return getImpl<detail::ZoneHVACLowTempRadiantConstFlowDesign_Impl>()->hydronicTubingInsideDiameter();
}

bool ZoneHVACLowTempRadiantConstFlowDesign::isHydronicTubingInsideDiameterDefaulted() const {
  return getImpl<detail::ZoneHVACLowTempRadiantConstFlowDesign_Impl>()->isHydronicTubingInsideDiameterDefaulted();
}

double ZoneHVACLowTempRadiantConstFlowDesign::hydronicTubingOutsideDiameter() const {
  return getImpl<detail::ZoneHVACLowTempRadiantConstFlowDesign_Impl>()->hydronicTubingOutsideDiameter();
}

bool ZoneHVACLowTempRadiantConstFlowDesign::isHydronicTubingOutsideDiameterDefaulted() const {
  return getImpl<detail::ZoneHVACLowTempRadiantConstFlowDesign_Impl>()->isHydronicTubingOutsideDiameterDefaulted();
}

double ZoneHVACLowTempRadiantConstFlowDesign::hydronicTubingConductivity() const {
  return getImpl<detail::ZoneHVACLowTempRadiantConstFlowDesign_Impl>()->hydronicTubingConductivity();
}

bool ZoneHVACLowTempRadiantConstFlowDesign::isHydronicTubingConductivityDefaulted() const {
  return getImpl<detail::ZoneHVACLowTempRadiantConstFlowDesign_Impl>()->isHydronicTubingConductivityDefaulted();
}

std::string ZoneHVACLowTempRadiantConstFlowDesign::temperatureControlType() const {
  return getImpl<detail::ZoneHVACLowTempRadiantConstFlowDesign_Impl>()->temperatureControlType();
}

bool ZoneHVACLowTempRadiantConstFlowDesign::isTemperatureControlTypeDefaulted() const {
  return getImpl<detail::ZoneHVACLowTempRadiantConstFlowDesign_Impl>()->isTemperatureControlTypeDefaulted();
}

double ZoneHVACLowTempRadiantConstFlowDesign::runningMeanOutdoorDryBulbTemperatureWeightingFactor() const {
  return getImpl<detail::ZoneHVACLowTempRadiantConstFlowDesign_Impl>()->runningMeanOutdoorDryBulbTemperatureWeightingFactor();
}

bool ZoneHVACLowTempRadiantConstFlowDesign::isRunningMeanOutdoorDryBulbTemperatureWeightingFactorDefaulted() const {
  return getImpl<detail::ZoneHVACLowTempRadiantConstFlowDesign_Impl>()->isRunningMeanOutdoorDryBulbTemperatureWeightingFactorDefaulted();
}

double ZoneHVACLowTempRadiantConstFlowDesign::motorEfficiency() const {
  return getImpl<detail::ZoneHVACLowTempRadiantConstFlowDesign_Impl>()->motorEfficiency();
}

bool ZoneHVACLowTempRadiantConstFlowDesign::isMotorEfficiencyDefaulted() const {
  return getImpl<detail::ZoneHVACLowTempRadiantConstFlowDesign_Impl>()->isMotorEfficiencyDefaulted();
}

double ZoneHVACLowTempRadiantConstFlowDesign::fractionofMotorInefficienciestoFluidStream() const {
  return getImpl<detail::ZoneHVACLowTempRadiantConstFlowDesign_Impl>()->fractionofMotorInefficienciestoFluidStream();
}

bool ZoneHVACLowTempRadiantConstFlowDesign::isFractionofMotorInefficienciestoFluidStreamDefaulted() const {
  return getImpl<detail::ZoneHVACLowTempRadiantConstFlowDesign_Impl>()->isFractionofMotorInefficienciestoFluidStreamDefaulted();
}

std::string ZoneHVACLowTempRadiantConstFlowDesign::condensationControlType() const {
  return getImpl<detail::ZoneHVACLowTempRadiantConstFlowDesign_Impl>()->condensationControlType();
}

bool ZoneHVACLowTempRadiantConstFlowDesign::isCondensationControlTypeDefaulted() const {
  return getImpl<detail::ZoneHVACLowTempRadiantConstFlowDesign_Impl>()->isCondensationControlTypeDefaulted();
}

double ZoneHVACLowTempRadiantConstFlowDesign::condensationControlDewpointOffset() const {
  return getImpl<detail::ZoneHVACLowTempRadiantConstFlowDesign_Impl>()->condensationControlDewpointOffset();
}

bool ZoneHVACLowTempRadiantConstFlowDesign::isCondensationControlDewpointOffsetDefaulted() const {
  return getImpl<detail::ZoneHVACLowTempRadiantConstFlowDesign_Impl>()->isCondensationControlDewpointOffsetDefaulted();
}

namespace detail {

boost::optional<Schedule> ZoneHVACLowTempRadiantConstFlowDesign_Impl::changeoverDelayTimePeriodSchedule() const {
  return getObject<ModelObject>().getModelObjectTarget<Schedule>(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlow_DesignFields::ChangeoverDelayTimePeriodSchedule);
}

bool ZoneHVACLowTempRadiantConstFlowDesign_Impl::setChangeoverDelayTimePeriodSchedule(Schedule& schedule) {
  return setPointer(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlow_DesignFields::ChangeoverDelayTimePeriodSchedule,
                    schedule.handle(), false);
}

void ZoneHVACLowTempRadiantConstFlowDesign_Impl::resetChangeoverDelayTimePeriodSchedule() {
  OS_ASSERT(setString(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlow_DesignFields::ChangeoverDelayTimePeriodSchedule, "", false));
}

std::string ZoneHVACLowTempRadiantConstFlowDesign_Impl::fluidtoRadiantSurfaceHeatTransferModel() const {
  if (const auto value = getString(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlow_DesignFields::FluidtoRadiantSurfaceHeatTransferModel, true)) {
    return *value;
  }
  return kDefaultFluidtoRadiantSurfaceHeatTransferModel;
}

bool ZoneHVACLowTempRadiantConstFlowDesign_Impl::isFluidtoRadiantSurfaceHeatTransferModelDefaulted() const {
  return isEmpty(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlow_DesignFields::FluidtoRadiantSurfaceHeatTransferModel);
}

bool ZoneHVACLowTempRadiantConstFlowDesign_Impl::setFluidtoRadiantSurfaceHeatTransferModel(const std::string& v) {
  return setString(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlow_DesignFields::FluidtoRadiantSurfaceHeatTransferModel, v);
}

void ZoneHVACLowTempRadiantConstFlowDesign_Impl::resetFluidtoRadiantSurfaceHeatTransferModel() {
  OS_ASSERT(setString(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlow_DesignFields::FluidtoRadiantSurfaceHeatTransferModel, ""));
}

double ZoneHVACLowTempRadiantConstFlowDesign_Impl::hydronicTubingInsideDiameter() const {
  if (const auto value = getDouble(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlow_DesignFields::HydronicTubingInsideDiameter, true)) {
    return *value;
  }
  return kDefaultHydronicTubingInsideDiameter;
}

bool ZoneHVACLowTempRadiantConstFlowDesign_Impl::isHydronicTubingInsideDiameterDefaulted() const {
  return isEmpty(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlow_DesignFields::HydronicTubingInsideDiameter);
}

bool ZoneHVACLowTempRadiantConstFlowDesign_Impl::setHydronicTubingInsideDiameter(double v) {
  return setDouble(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlow_DesignFields::HydronicTubingInsideDiameter, v);
}

void ZoneHVACLowTempRadiantConstFlowDesign_Impl::resetHydronicTubingInsideDiameter() {
  OS_ASSERT(setString(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlow_DesignFields::HydronicTubingInsideDiameter, ""));
}

double ZoneHVACLowTempRadiantConstFlowDesign_Impl::hydronicTubingOutsideDiameter() const {
  if (const auto value = getDouble(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlow_DesignFields::HydronicTubingOutsideDiameter, true)) {
    return *value;
  }
  return kDefaultHydronicTubingOutsideDiameter;
}

bool ZoneHVACLowTempRadiantConstFlowDesign_Impl::isHydronicTubingOutsideDiameterDefaulted() const {
  return isEmpty(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlow_DesignFields::HydronicTubingOutsideDiameter);
}

bool ZoneHVACLowTempRadiantConstFlowDesign_Impl::setHydronicTubingOutsideDiameter(double v) {
  return setDouble(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlow_DesignFields::HydronicTubingOutsideDiameter, v);
}

void ZoneHVACLowTempRadiantConstFlowDesign_Impl::resetHydronicTubingOutsideDiameter() {
  OS_ASSERT(setString(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlow_DesignFields::HydronicTubingOutsideDiameter, ""));
}

double ZoneHVACLowTempRadiantConstFlowDesign_Impl::hydronicTubingConductivity() const {
  if (const auto value = getDouble(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlow_DesignFields::HydronicTubingConductivity, true)) {
    return *value;
  }
  return kDefaultHydronicTubingConductivity;
}

bool ZoneHVACLowTempRadiantConstFlowDesign_Impl::isHydronicTubingConductivityDefaulted() const {
  return isEmpty(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlow_DesignFields::HydronicTubingConductivity);
}

bool ZoneHVACLowTempRadiantConstFlowDesign_Impl::setHydronicTubingConductivity(double v) {
  return setDouble(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlow_DesignFields::HydronicTubingConductivity, v);
}

void ZoneHVACLowTempRadiantConstFlowDesign_Impl::resetHydronicTubingConductivity() {
  OS_ASSERT(setString(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlow_DesignFields::HydronicTubingConductivity, ""));
}

std::string ZoneHVACLowTempRadiantConstFlowDesign_Impl::temperatureControlType() const {
  if (const auto value = getString(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlow_DesignFields::TemperatureControlType, true)) {
    return *value;
  }
  return kDefaultTemperatureControlType;
}

bool ZoneHVACLowTempRadiantConstFlowDesign_Impl::isTemperatureControlTypeDefaulted() const {
  return isEmpty(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlow_DesignFields::TemperatureControlType);
}

bool ZoneHVACLowTempRadiantConstFlowDesign_Impl::setTemperatureControlType(const std::string& v) {
  return setString(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlow_DesignFields::TemperatureControlType, v);
}

void ZoneHVACLowTempRadiantConstFlowDesign_Impl::resetTemperatureControlType() {
  OS_ASSERT(setString(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlow_DesignFields::TemperatureControlType, ""));
}

double ZoneHVACLowTempRadiantConstFlowDesign_Impl::runningMeanOutdoorDryBulbTemperatureWeightingFactor() const {
  if (const auto value =
        getDouble(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlow_DesignFields::RunningMeanOutdoorDryBulbTemperatureWeightingFactor, true)) {
    return *value;
  }
  return kDefaultRunningMeanOutdoorDryBulbTemperatureWeightingFactor;
}

bool ZoneHVACLowTempRadiantConstFlowDesign_Impl::isRunningMeanOutdoorDryBulbTemperatureWeightingFactorDefaulted() const {
  return isEmpty(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlow_DesignFields::RunningMeanOutdoorDryBulbTemperatureWeightingFactor);
}

bool ZoneHVACLowTempRadiantConstFlowDesign_Impl::setRunningMeanOutdoorDryBulbTemperatureWeightingFactor(double v) {
  return setDouble(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlow_DesignFields::RunningMeanOutdoorDryBulbTemperatureWeightingFactor, v);
}

void ZoneHVACLowTempRadiantConstFlowDesign_Impl::resetRunningMeanOutdoorDryBulbTemperatureWeightingFactor() {
  OS_ASSERT(setString(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlow_DesignFields::RunningMeanOutdoorDryBulbTemperatureWeightingFactor, ""));
}

double ZoneHVACLowTempRadiantConstFlowDesign_Impl::motorEfficiency() const {
  if (const auto value = getDouble(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlow_DesignFields::MotorEfficiency, true)) {
    return *value;
  }
  return kDefaultMotorEfficiency;
}

bool ZoneHVACLowTempRadiantConstFlowDesign_Impl::isMotorEfficiencyDefaulted() const {
  return isEmpty(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlow_DesignFields::MotorEfficiency);
}

bool ZoneHVACLowTempRadiantConstFlowDesign_Impl::setMotorEfficiency(double v) {
  return setDouble(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlow_DesignFields::MotorEfficiency, v);
}

void ZoneHVACLowTempRadiantConstFlowDesign_Impl::resetMotorEfficiency() {
  OS_ASSERT(setString(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlow_DesignFields::MotorEfficiency, ""));
}

double ZoneHVACLowTempRadiantConstFlowDesign_Impl::fractionofMotorInefficienciestoFluidStream() const {
  if (const auto value =
        getDouble(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlow_DesignFields::FractionofMotorInefficienciestoFluidStream, true)) {
    return *value;
  }
  return kDefaultFractionofMotorInefficienciestoFluidStream;
}

bool ZoneHVACLowTempRadiantConstFlowDesign_Impl::isFractionofMotorInefficienciestoFluidStreamDefaulted() const {
  return isEmpty(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlow_DesignFields::FractionofMotorInefficienciestoFluidStream);
}

bool ZoneHVACLowTempRadiantConstFlowDesign_Impl::setFractionofMotorInefficienciestoFluidStream(double v) {
  return setDouble(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlow_DesignFields::FractionofMotorInefficienciestoFluidStream, v);
}

void ZoneHVACLowTempRadiantConstFlowDesign_Impl::resetFractionofMotorInefficienciestoFluidStream() {
  OS_ASSERT(setString(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlow_DesignFields::FractionofMotorInefficienciestoFluidStream, ""));
}

std::string ZoneHVACLowTempRadiantConstFlowDesign_Impl::condensationControlType() const {
  if (const auto value = getString(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlow_DesignFields::CondensationControlType, true)) {
    return *value;
  }
  return kDefaultCondensationControlType;
}

bool ZoneHVACLowTempRadiantConstFlowDesign_Impl::isCondensationControlTypeDefaulted() const {
  return isEmpty(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlow_DesignFields::CondensationControlType);
}

bool ZoneHVACLowTempRadiantConstFlowDesign_Impl::setCondensationControlType(const std::string& v) {
  return setString(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlow_DesignFields::CondensationControlType, v);
}

void ZoneHVACLowTempRadiantConstFlowDesign_Impl::resetCondensationControlType() {
  OS_ASSERT(setString(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlow_DesignFields::CondensationControlType, ""));
}

double ZoneHVACLowTempRadiantConstFlowDesign_Impl::condensationControlDewpointOffset() const {
  if (const auto value =
        getDouble(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlow_DesignFields::CondensationControlDewpointOffset, true)) {
    return *value;
  }
  return kDefaultCondensationControlDewpointOffset;
}

bool ZoneHVACLowTempRadiantConstFlowDesign_Impl::isCondensationControlDewpointOffsetDefaulted() const {
  return isEmpty(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlow_DesignFields::CondensationControlDewpointOffset);
}

bool ZoneHVACLowTempRadiantConstFlowDesign_Impl::setCondensationControlDewpointOffset(double v) {
  return setDouble(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlow_DesignFields::CondensationControlDewpointOffset, v);
}

void ZoneHVACLowTempRadiantConstFlowDesign_Impl::resetCondensationControlDewpointOffset() {
  OS_ASSERT(setString(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlow_DesignFields::CondensationControlDewpointOffset, ""));
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
