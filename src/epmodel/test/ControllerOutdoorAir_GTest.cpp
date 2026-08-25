/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"

#include "../Curve/CurveBiquadratic.hpp"
#include "../Curve/CurveBiquadratic_Impl.hpp"
#include "../Curve/CurveLinear.hpp"
#include "../Curve/CurveLinear_Impl.hpp"
#include "../Curve/TableLookup.hpp"
#include "../ModelObject/Branch.hpp"
#include "../ModelObject/Branch_Impl.hpp"
#include "../ModelObject/BranchList.hpp"
#include "../ModelObject/BranchList_Impl.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/AirLoopHVAC_Impl.hpp"
#include "../HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "../HVACComponent/AirLoopHVACOutdoorAirSystem_Impl.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"
#include "../ModelObject/AirLoopHVACDedicatedOutdoorAirSystem.hpp"
#include "../ModelObject/ControllerMechanicalVentilation.hpp"
#include "../ModelObject/ControllerMechanicalVentilation_Impl.hpp"
#include "../ModelObject/DesignSpecificationOutdoorAirSpaceList.hpp"
#include "../ModelObject/DesignSpecificationOutdoorAirSpaceList_Impl.hpp"
#include "../ParentObject/ControllerOutdoorAir.hpp"
#include "../ParentObject/ControllerOutdoorAir_Impl.hpp"
#include "../ResourceObject/DesignSpecificationOutdoorAir.hpp"
#include "../ResourceObject/DesignSpecificationOutdoorAir_Impl.hpp"
#include "../ResourceObject/ScheduleTypeLimits.hpp"
#include "../Schedule/Schedule.hpp"
#include "../Schedule/Schedule_Impl.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Schedule/ScheduleConstant_Impl.hpp"
#include "../StraightComponent/Node.hpp"
#include "../ModelObject/SizingZone.hpp"
#include "../ModelObject/SizingZone_Impl.hpp"
#include "../PlanarSurfaceGroup/Space.hpp"
#include "../PlanarSurfaceGroup/Space_Impl.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../HVACComponent/ThermalZone_Impl.hpp"

#include <utilities/core/Filesystem.hpp>
#include <utilities/core/UUID.hpp>
#include <utilities/idd/AirLoopHVAC_FieldEnums.hxx>
#include <utilities/idd/Branch_FieldEnums.hxx>
#include <utilities/idd/BranchList_FieldEnums.hxx>
#include <utilities/idd/Controller_OutdoorAir_FieldEnums.hxx>
#include <utilities/idd/Controller_MechanicalVentilation_FieldEnums.hxx>
#include <utilities/idd/Sizing_Zone_FieldEnums.hxx>
#include <utilities/idf/WorkspaceObject_Impl.hpp>
#include <utilities/idf/WorkspaceExtensibleGroup.hpp>

#include <algorithm>
#include <array>
#include <iterator>
#include <sstream>
#include <utility>

using namespace openstudio::epmodel;

namespace {

class ScopedFileRemoval
{
 public:
  explicit ScopedFileRemoval(openstudio::path path) : m_path(std::move(path)) {}

  ~ScopedFileRemoval() {
    boost::system::error_code error;
    boost::filesystem::remove(m_path, error);
  }

 private:
  openstudio::path m_path;
};

openstudio::path uniqueIdfPath(const std::string& stem) {
  return openstudio::tempDir() / openstudio::toPath(stem + "-" + openstudio::removeBraces(openstudio::createUUID()) + ".idf");
}

void expectScheduleTypeLimits(const Schedule& schedule, const std::string& numericType, const std::string& unitType) {
  ASSERT_TRUE(schedule.scheduleTypeLimits());
  const auto limits = *schedule.scheduleTypeLimits();
  ASSERT_TRUE(limits.numericType());
  EXPECT_EQ(numericType, *limits.numericType());
  EXPECT_EQ(unitType, limits.unitType());
  ASSERT_TRUE(limits.lowerLimitValue());
  ASSERT_TRUE(limits.upperLimitValue());
  EXPECT_DOUBLE_EQ(0.0, *limits.lowerLimitValue());
  EXPECT_DOUBLE_EQ(1.0, *limits.upperLimitValue());
}

std::vector<std::pair<openstudio::Handle, std::string>> exactObjectInventory(const Model& model) {
  std::vector<std::pair<openstudio::Handle, std::string>> result;
  for (const auto& object : model.objects()) {
    std::ostringstream text;
    object.idfObject().print(text);
    result.emplace_back(object.handle(), text.str());
  }
  std::ranges::sort(result, {}, &std::pair<openstudio::Handle, std::string>::first);
  return result;
}

}  // namespace

TEST_F(EPModelFixture, API_ControllerOutdoorAir_DefaultConstructor) {
  Model model;
  ControllerOutdoorAir controller(model);
  EXPECT_EQ(ControllerOutdoorAir::iddObjectType(), controller.iddObject().type());
}

TEST_F(EPModelFixture, API_ControllerOutdoorAir_ScalarAccessors_RoundTrip) {
  Model model;
  ControllerOutdoorAir controller(model);

  ASSERT_TRUE(controller.setMinimumOutdoorAirFlowRate(0.42));
  ASSERT_TRUE(controller.minimumOutdoorAirFlowRate());
  EXPECT_NEAR(0.42, *controller.minimumOutdoorAirFlowRate(), 1e-9);
  EXPECT_FALSE(controller.isMinimumOutdoorAirFlowRateAutosized());
  controller.autosizeMinimumOutdoorAirFlowRate();
  EXPECT_TRUE(controller.isMinimumOutdoorAirFlowRateAutosized());

  ASSERT_TRUE(controller.setMaximumOutdoorAirFlowRate(0.84));
  ASSERT_TRUE(controller.maximumOutdoorAirFlowRate());
  EXPECT_NEAR(0.84, *controller.maximumOutdoorAirFlowRate(), 1e-9);
  EXPECT_FALSE(controller.isMaximumOutdoorAirFlowRateAutosized());
  controller.autosizeMaximumOutdoorAirFlowRate();
  EXPECT_TRUE(controller.isMaximumOutdoorAirFlowRateAutosized());

  const auto economizerControlTypeValues = ControllerOutdoorAir::economizerControlTypeValues();
  ASSERT_FALSE(economizerControlTypeValues.empty());
  EXPECT_TRUE(controller.setEconomizerControlType(economizerControlTypeValues.front()));
  EXPECT_EQ(economizerControlTypeValues.front(), controller.getEconomizerControlType());

  const auto actionTypeValues = ControllerOutdoorAir::economizerControlActionTypeValues();
  ASSERT_FALSE(actionTypeValues.empty());
  EXPECT_TRUE(controller.setEconomizerControlActionType(actionTypeValues.front()));
  EXPECT_EQ(actionTypeValues.front(), controller.getEconomizerControlActionType());

  EXPECT_TRUE(controller.setEconomizerMaximumLimitDryBulbTemperature(26.0));
  ASSERT_TRUE(controller.getEconomizerMaximumLimitDryBulbTemperature());
  EXPECT_NEAR(26.0, *controller.getEconomizerMaximumLimitDryBulbTemperature(), 1e-9);
  controller.resetEconomizerMaximumLimitDryBulbTemperature();
  EXPECT_FALSE(controller.getEconomizerMaximumLimitDryBulbTemperature());

  EXPECT_TRUE(controller.setEconomizerMaximumLimitEnthalpy(45000.0));
  ASSERT_TRUE(controller.getEconomizerMaximumLimitEnthalpy());
  EXPECT_NEAR(45000.0, *controller.getEconomizerMaximumLimitEnthalpy(), 1e-9);
  controller.resetEconomizerMaximumLimitEnthalpy();
  EXPECT_FALSE(controller.getEconomizerMaximumLimitEnthalpy());

  EXPECT_TRUE(controller.setEconomizerMaximumLimitDewpointTemperature(14.0));
  ASSERT_TRUE(controller.getEconomizerMaximumLimitDewpointTemperature());
  EXPECT_NEAR(14.0, *controller.getEconomizerMaximumLimitDewpointTemperature(), 1e-9);
  controller.resetEconomizerMaximumLimitDewpointTemperature();
  EXPECT_FALSE(controller.getEconomizerMaximumLimitDewpointTemperature());

  EXPECT_TRUE(controller.setEconomizerMinimumLimitDryBulbTemperature(-5.0));
  ASSERT_TRUE(controller.getEconomizerMinimumLimitDryBulbTemperature());
  EXPECT_NEAR(-5.0, *controller.getEconomizerMinimumLimitDryBulbTemperature(), 1e-9);
  controller.resetEconomizerMinimumLimitDryBulbTemperature();
  EXPECT_FALSE(controller.getEconomizerMinimumLimitDryBulbTemperature());

  const auto lockoutTypeValues = ControllerOutdoorAir::lockoutTypeValues();
  ASSERT_FALSE(lockoutTypeValues.empty());
  EXPECT_TRUE(controller.setLockoutType(lockoutTypeValues.front()));
  EXPECT_EQ(lockoutTypeValues.front(), controller.getLockoutType());

  const auto minimumLimitTypeValues = ControllerOutdoorAir::minimumLimitTypeValues();
  ASSERT_FALSE(minimumLimitTypeValues.empty());
  EXPECT_TRUE(controller.setMinimumLimitType(minimumLimitTypeValues.front()));
  EXPECT_EQ(minimumLimitTypeValues.front(), controller.getMinimumLimitType());

  EXPECT_TRUE(controller.setHighHumidityOutdoorAirFlowRatio(1.25));
  EXPECT_NEAR(1.25, controller.getHighHumidityOutdoorAirFlowRatio(), 1e-9);

  EXPECT_TRUE(controller.setControlHighIndoorHumidityBasedOnOutdoorHumidityRatio(false));
  EXPECT_FALSE(controller.getControlHighIndoorHumidityBasedOnOutdoorHumidityRatio());

  const auto heatRecoveryBypassControlTypeValues = ControllerOutdoorAir::heatRecoveryBypassControlTypeValues();
  ASSERT_FALSE(heatRecoveryBypassControlTypeValues.empty());
  EXPECT_TRUE(controller.setHeatRecoveryBypassControlType(heatRecoveryBypassControlTypeValues.front()));
  ASSERT_TRUE(controller.getHeatRecoveryBypassControlType());
  EXPECT_EQ(heatRecoveryBypassControlTypeValues.front(), *controller.getHeatRecoveryBypassControlType());

  const auto economizerOperationStagingValues = ControllerOutdoorAir::economizerOperationStagingValues();
  ASSERT_FALSE(economizerOperationStagingValues.empty());
  EXPECT_TRUE(controller.setEconomizerOperationStaging(economizerOperationStagingValues.front()));
  EXPECT_EQ(economizerOperationStagingValues.front(), controller.economizerOperationStaging());
}

TEST_F(EPModelFixture, ControllerOutdoorAir_RelationshipAccessorsRoundTripAndReset) {
  Model model;
  ControllerOutdoorAir controller(model);
  ScheduleConstant minimumOutdoorAir(model);
  ScheduleConstant minimumFraction(model);
  ScheduleConstant maximumFraction(model);
  ScheduleConstant timeOfDay(model);
  CurveLinear linearCurve(model);
  TableLookup tableLookup(model);
  ThermalZone zone(model);

  EXPECT_FALSE(controller.minimumOutdoorAirSchedule());
  EXPECT_FALSE(controller.minimumFractionofOutdoorAirSchedule());
  EXPECT_FALSE(controller.maximumFractionofOutdoorAirSchedule());
  EXPECT_FALSE(controller.timeofDayEconomizerControlSchedule());
  EXPECT_FALSE(controller.electronicEnthalpyLimitCurve());
  EXPECT_FALSE(controller.humidistatControlZone());
  ASSERT_TRUE(controller.getHighHumidityControl());
  EXPECT_FALSE(*controller.getHighHumidityControl());

  ASSERT_TRUE(minimumOutdoorAir.setValue(1.0));
  ASSERT_TRUE(minimumFraction.setValue(0.25));
  ASSERT_TRUE(maximumFraction.setValue(0.9));
  ASSERT_TRUE(timeOfDay.setValue(1.0));
  ASSERT_TRUE(controller.setMinimumOutdoorAirSchedule(minimumOutdoorAir));
  ASSERT_TRUE(controller.setMinimumFractionofOutdoorAirSchedule(minimumFraction));
  ASSERT_TRUE(controller.setMaximumFractionofOutdoorAirSchedule(maximumFraction));
  ASSERT_TRUE(controller.setTimeofDayEconomizerControlSchedule(timeOfDay));
  ASSERT_TRUE(controller.setElectronicEnthalpyLimitCurve(linearCurve));
  ASSERT_TRUE(controller.setHumidistatControlZone(zone));

  EXPECT_EQ(minimumOutdoorAir.handle(), controller.minimumOutdoorAirSchedule()->handle());
  EXPECT_EQ(minimumFraction.handle(), controller.minimumFractionofOutdoorAirSchedule()->handle());
  EXPECT_EQ(maximumFraction.handle(), controller.maximumFractionofOutdoorAirSchedule()->handle());
  EXPECT_EQ(timeOfDay.handle(), controller.timeofDayEconomizerControlSchedule()->handle());
  EXPECT_EQ(linearCurve.handle(), controller.electronicEnthalpyLimitCurve()->handle());
  EXPECT_EQ(zone.handle(), controller.humidistatControlZone()->handle());
  ASSERT_TRUE(controller.getHighHumidityControl());
  EXPECT_TRUE(*controller.getHighHumidityControl());
  expectScheduleTypeLimits(minimumOutdoorAir, "Continuous", "Dimensionless");
  expectScheduleTypeLimits(minimumFraction, "Continuous", "Dimensionless");
  expectScheduleTypeLimits(maximumFraction, "Continuous", "Dimensionless");
  expectScheduleTypeLimits(timeOfDay, "Discrete", "Availability");

  ASSERT_TRUE(controller.setElectronicEnthalpyLimitCurve(tableLookup));
  EXPECT_EQ(tableLookup.handle(), controller.electronicEnthalpyLimitCurve()->handle());

  const std::array<openstudio::Handle, 7> resourceHandles = {minimumOutdoorAir.handle(),
                                                             minimumFraction.handle(),
                                                             maximumFraction.handle(),
                                                             timeOfDay.handle(),
                                                             linearCurve.handle(),
                                                             tableLookup.handle(),
                                                             zone.handle()};
  controller.resetMinimumOutdoorAirSchedule();
  controller.resetMinimumFractionofOutdoorAirSchedule();
  controller.resetMaximumFractionofOutdoorAirSchedule();
  controller.resetTimeofDayEconomizerControlSchedule();
  controller.resetElectronicEnthalpyLimitCurve();
  controller.resetHumidistatControlZone();
  EXPECT_FALSE(controller.minimumOutdoorAirSchedule());
  EXPECT_FALSE(controller.minimumFractionofOutdoorAirSchedule());
  EXPECT_FALSE(controller.maximumFractionofOutdoorAirSchedule());
  EXPECT_FALSE(controller.timeofDayEconomizerControlSchedule());
  EXPECT_FALSE(controller.electronicEnthalpyLimitCurve());
  EXPECT_FALSE(controller.humidistatControlZone());
  ASSERT_TRUE(controller.getHighHumidityControl());
  EXPECT_FALSE(*controller.getHighHumidityControl());
  for (const auto& handle : resourceHandles) {
    EXPECT_TRUE(model.getObject(handle));
  }
}

TEST_F(EPModelFixture, ControllerOutdoorAir_RelationshipSettersRejectWithoutChangingTargetsOrRawText) {
  Model model;
  ControllerOutdoorAir controller(model);
  ScheduleConstant acceptedMinimum(model);
  ScheduleConstant acceptedMinimumFraction(model);
  ScheduleConstant acceptedMaximumFraction(model);
  ScheduleConstant acceptedTimeOfDay(model);
  CurveLinear acceptedCurve(model);
  ThermalZone acceptedZone(model);
  ASSERT_TRUE(controller.setMinimumOutdoorAirSchedule(acceptedMinimum));
  ASSERT_TRUE(controller.setMinimumFractionofOutdoorAirSchedule(acceptedMinimumFraction));
  ASSERT_TRUE(controller.setMaximumFractionofOutdoorAirSchedule(acceptedMaximumFraction));
  ASSERT_TRUE(controller.setTimeofDayEconomizerControlSchedule(acceptedTimeOfDay));
  ASSERT_TRUE(controller.setElectronicEnthalpyLimitCurve(acceptedCurve));
  ASSERT_TRUE(controller.setHumidistatControlZone(acceptedZone));

  Model foreignModel;
  ScheduleConstant foreignSchedule(foreignModel);
  CurveLinear foreignCurve(foreignModel);
  ThermalZone foreignZone(foreignModel);
  EXPECT_FALSE(controller.setMinimumOutdoorAirSchedule(foreignSchedule));
  EXPECT_FALSE(controller.setMinimumFractionofOutdoorAirSchedule(foreignSchedule));
  EXPECT_FALSE(controller.setMaximumFractionofOutdoorAirSchedule(foreignSchedule));
  EXPECT_FALSE(controller.setTimeofDayEconomizerControlSchedule(foreignSchedule));
  EXPECT_FALSE(controller.setElectronicEnthalpyLimitCurve(foreignCurve));
  EXPECT_FALSE(controller.setHumidistatControlZone(foreignZone));
  EXPECT_EQ(acceptedMinimum.handle(), controller.minimumOutdoorAirSchedule()->handle());
  EXPECT_EQ(acceptedMinimumFraction.handle(), controller.minimumFractionofOutdoorAirSchedule()->handle());
  EXPECT_EQ(acceptedMaximumFraction.handle(), controller.maximumFractionofOutdoorAirSchedule()->handle());
  EXPECT_EQ(acceptedTimeOfDay.handle(), controller.timeofDayEconomizerControlSchedule()->handle());
  EXPECT_EQ(acceptedCurve.handle(), controller.electronicEnthalpyLimitCurve()->handle());
  EXPECT_EQ(acceptedZone.handle(), controller.humidistatControlZone()->handle());

  ScheduleConstant incompatibleContinuous(model);
  ScheduleTypeLimits incompatibleContinuousLimits(model);
  ASSERT_TRUE(incompatibleContinuousLimits.setNumericType("Continuous"));
  ASSERT_TRUE(incompatibleContinuousLimits.setUnitType("Dimensionless"));
  ASSERT_TRUE(incompatibleContinuousLimits.setLowerLimitValue(-0.1));
  ASSERT_TRUE(incompatibleContinuousLimits.setUpperLimitValue(1.0));
  ASSERT_TRUE(incompatibleContinuous.setScheduleTypeLimits(incompatibleContinuousLimits));
  ScheduleConstant incompatibleDiscrete(model);
  ScheduleTypeLimits incompatibleDiscreteLimits(model);
  ASSERT_TRUE(incompatibleDiscreteLimits.setNumericType("Continuous"));
  ASSERT_TRUE(incompatibleDiscreteLimits.setUnitType("Availability"));
  ASSERT_TRUE(incompatibleDiscreteLimits.setLowerLimitValue(0.0));
  ASSERT_TRUE(incompatibleDiscreteLimits.setUpperLimitValue(1.0));
  ASSERT_TRUE(incompatibleDiscrete.setScheduleTypeLimits(incompatibleDiscreteLimits));
  CurveBiquadratic incompatibleCurve(model);
  EXPECT_FALSE(controller.setMinimumOutdoorAirSchedule(incompatibleContinuous));
  EXPECT_FALSE(controller.setMinimumFractionofOutdoorAirSchedule(incompatibleContinuous));
  EXPECT_FALSE(controller.setMaximumFractionofOutdoorAirSchedule(incompatibleContinuous));
  EXPECT_FALSE(controller.setTimeofDayEconomizerControlSchedule(incompatibleDiscrete));
  EXPECT_FALSE(controller.setElectronicEnthalpyLimitCurve(incompatibleCurve));

  auto workspaceImpl = controller.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(workspaceImpl);
  const std::array<std::pair<unsigned, std::string>, 6> rawFields = {{
    {openstudio::Controller_OutdoorAirFields::MinimumOutdoorAirScheduleName, "Unresolved Minimum OA Schedule"},
    {openstudio::Controller_OutdoorAirFields::MinimumFractionofOutdoorAirScheduleName, "Unresolved Minimum Fraction Schedule"},
    {openstudio::Controller_OutdoorAirFields::MaximumFractionofOutdoorAirScheduleName, "Unresolved Maximum Fraction Schedule"},
    {openstudio::Controller_OutdoorAirFields::TimeofDayEconomizerControlScheduleName, "Unresolved Time of Day Schedule"},
    {openstudio::Controller_OutdoorAirFields::ElectronicEnthalpyLimitCurveName, "Unresolved Electronic Enthalpy Curve"},
    {openstudio::Controller_OutdoorAirFields::HumidistatControlZoneName, "Unresolved Humidistat Zone"},
  }};
  for (const auto& [field, value] : rawFields) {
    ASSERT_TRUE(workspaceImpl->setPointer(field, openstudio::Handle(), false));
    ASSERT_TRUE(workspaceImpl->openstudio::detail::IdfObject_Impl::setString(field, value, false));
  }
  ASSERT_TRUE(
    workspaceImpl->openstudio::detail::IdfObject_Impl::setString(openstudio::Controller_OutdoorAirFields::HighHumidityControl, "Yes", false));

  EXPECT_FALSE(controller.setMinimumOutdoorAirSchedule(incompatibleContinuous));
  EXPECT_FALSE(controller.setMinimumFractionofOutdoorAirSchedule(incompatibleContinuous));
  EXPECT_FALSE(controller.setMaximumFractionofOutdoorAirSchedule(incompatibleContinuous));
  EXPECT_FALSE(controller.setTimeofDayEconomizerControlSchedule(incompatibleDiscrete));
  EXPECT_FALSE(controller.setElectronicEnthalpyLimitCurve(incompatibleCurve));
  EXPECT_FALSE(controller.setHumidistatControlZone(foreignZone));
  for (const auto& [field, value] : rawFields) {
    EXPECT_EQ(value, workspaceImpl->openstudio::detail::IdfObject_Impl::getString(field, false, true).value_or(""));
  }
  EXPECT_EQ("Yes",
            workspaceImpl->openstudio::detail::IdfObject_Impl::getString(openstudio::Controller_OutdoorAirFields::HighHumidityControl, false, true)
              .value_or(""));
}

TEST_F(EPModelFixture, ControllerOutdoorAir_LoadRepairsInvalidOptionalRelationshipsAndIsIdempotent) {
  const auto idfPath = uniqueIdfPath("epmodel-controller-outdoor-air-relationship-repair");
  const ScopedFileRemoval removeIdf(idfPath);

  Model model;
  ControllerOutdoorAir invalidController(model);
  ControllerOutdoorAir zoneController(model);
  ScheduleConstant incompatibleSchedule(model);
  ScheduleTypeLimits incompatibleLimits(model);
  CurveBiquadratic incompatibleCurve(model);
  ThermalZone validZone(model);
  ASSERT_TRUE(invalidController.setName("Invalid Relationship OA Controller"));
  ASSERT_TRUE(zoneController.setName("Valid Humidistat OA Controller"));
  ASSERT_TRUE(incompatibleSchedule.setName("Retained Incompatible OA Schedule"));
  ASSERT_TRUE(incompatibleCurve.setName("Retained Incompatible OA Curve"));
  ASSERT_TRUE(validZone.setName("Retained Humidistat Zone"));
  ASSERT_TRUE(incompatibleLimits.setNumericType("Continuous"));
  ASSERT_TRUE(incompatibleLimits.setUnitType("Dimensionless"));
  ASSERT_TRUE(incompatibleLimits.setLowerLimitValue(-0.1));
  ASSERT_TRUE(incompatibleLimits.setUpperLimitValue(1.0));
  ASSERT_TRUE(incompatibleSchedule.setScheduleTypeLimits(incompatibleLimits));
  auto invalidImpl = invalidController.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  auto zoneImpl = zoneController.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(invalidImpl);
  ASSERT_TRUE(zoneImpl);
  ASSERT_TRUE(invalidImpl->setPointer(openstudio::Controller_OutdoorAirFields::MinimumOutdoorAirScheduleName, incompatibleSchedule.handle(), false));
  ASSERT_TRUE(invalidImpl->setPointer(openstudio::Controller_OutdoorAirFields::ElectronicEnthalpyLimitCurveName, incompatibleCurve.handle(), false));
  ASSERT_TRUE(invalidImpl->setPointer(openstudio::Controller_OutdoorAirFields::MinimumFractionofOutdoorAirScheduleName, openstudio::Handle(), false));
  ASSERT_TRUE(invalidImpl->openstudio::detail::IdfObject_Impl::setString(
    openstudio::Controller_OutdoorAirFields::MinimumFractionofOutdoorAirScheduleName, "Missing Fraction Schedule", false));
  ASSERT_TRUE(invalidImpl->setPointer(openstudio::Controller_OutdoorAirFields::HumidistatControlZoneName, openstudio::Handle(), false));
  ASSERT_TRUE(invalidImpl->openstudio::detail::IdfObject_Impl::setString(openstudio::Controller_OutdoorAirFields::HumidistatControlZoneName,
                                                                         "Missing Humidistat Zone", false));
  ASSERT_TRUE(invalidImpl->openstudio::detail::IdfObject_Impl::setString(openstudio::Controller_OutdoorAirFields::HighHumidityControl, "Yes", false));
  ASSERT_TRUE(zoneImpl->setPointer(openstudio::Controller_OutdoorAirFields::HumidistatControlZoneName, validZone.handle(), false));
  ASSERT_TRUE(zoneImpl->openstudio::detail::IdfObject_Impl::setString(openstudio::Controller_OutdoorAirFields::HighHumidityControl, "No", false));
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedInvalid = loadedModel->getConcreteModelObjectByName<ControllerOutdoorAir>("Invalid Relationship OA Controller");
  auto loadedZoneController = loadedModel->getConcreteModelObjectByName<ControllerOutdoorAir>("Valid Humidistat OA Controller");
  auto loadedSchedule = loadedModel->getConcreteModelObjectByName<ScheduleConstant>("Retained Incompatible OA Schedule");
  auto loadedCurve = loadedModel->getConcreteModelObjectByName<CurveBiquadratic>("Retained Incompatible OA Curve");
  auto loadedZone = loadedModel->getConcreteModelObjectByName<ThermalZone>("Retained Humidistat Zone");
  ASSERT_TRUE(loadedInvalid);
  ASSERT_TRUE(loadedZoneController);
  ASSERT_TRUE(loadedSchedule);
  ASSERT_TRUE(loadedCurve);
  ASSERT_TRUE(loadedZone);
  EXPECT_FALSE(loadedInvalid->minimumOutdoorAirSchedule());
  EXPECT_FALSE(loadedInvalid->minimumFractionofOutdoorAirSchedule());
  EXPECT_FALSE(loadedInvalid->electronicEnthalpyLimitCurve());
  EXPECT_FALSE(loadedInvalid->humidistatControlZone());
  ASSERT_TRUE(loadedInvalid->getHighHumidityControl());
  EXPECT_FALSE(*loadedInvalid->getHighHumidityControl());
  ASSERT_TRUE(loadedZoneController->humidistatControlZone());
  EXPECT_EQ(loadedZone->handle(), loadedZoneController->humidistatControlZone()->handle());
  ASSERT_TRUE(loadedZoneController->getHighHumidityControl());
  EXPECT_TRUE(*loadedZoneController->getHighHumidityControl());

  const auto objectCount = loadedModel->getModelObjects<ModelObject>().size();
  const auto zoneHandle = loadedZoneController->humidistatControlZone()->handle();
  const auto report = loadedModel->canonicalize();
  EXPECT_EQ(0u, report.errorCount);
  EXPECT_EQ(objectCount, loadedModel->getModelObjects<ModelObject>().size());
  EXPECT_EQ(zoneHandle, loadedZoneController->humidistatControlZone()->handle());
}

TEST_F(EPModelFixture, ControllerOutdoorAir_RelationshipsSurviveOrdinaryReloadMutationAndRemoval) {
  const auto firstIdfPath = uniqueIdfPath("epmodel-controller-outdoor-air-relationships-first");
  const auto secondIdfPath = uniqueIdfPath("epmodel-controller-outdoor-air-relationships-second");
  const ScopedFileRemoval removeFirstIdf(firstIdfPath);
  const ScopedFileRemoval removeSecondIdf(secondIdfPath);

  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACOutdoorAirSystem oaSystem(model);
  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(oaSystem.addToNode(supplyInletNode));
  auto controller = oaSystem.getControllerOutdoorAir();
  ScheduleConstant minimumOutdoorAir(model);
  ScheduleConstant minimumFraction(model);
  ScheduleConstant maximumFraction(model);
  ScheduleConstant timeOfDay(model);
  CurveLinear enthalpyCurve(model);
  ThermalZone humidistatZone(model);
  ASSERT_TRUE(oaSystem.setName("Relationship OA System"));
  ASSERT_TRUE(controller.setName("Relationship OA Controller"));
  ASSERT_TRUE(minimumOutdoorAir.setName("Relationship Minimum OA Schedule"));
  ASSERT_TRUE(minimumFraction.setName("Relationship Minimum Fraction Schedule"));
  ASSERT_TRUE(maximumFraction.setName("Relationship Maximum Fraction Schedule"));
  ASSERT_TRUE(timeOfDay.setName("Relationship Time of Day Schedule"));
  ASSERT_TRUE(enthalpyCurve.setName("Relationship Electronic Enthalpy Curve"));
  ASSERT_TRUE(humidistatZone.setName("Relationship Humidistat Zone"));
  ASSERT_TRUE(controller.setMinimumOutdoorAirSchedule(minimumOutdoorAir));
  ASSERT_TRUE(controller.setMinimumFractionofOutdoorAirSchedule(minimumFraction));
  ASSERT_TRUE(controller.setMaximumFractionofOutdoorAirSchedule(maximumFraction));
  ASSERT_TRUE(controller.setTimeofDayEconomizerControlSchedule(timeOfDay));
  ASSERT_TRUE(controller.setElectronicEnthalpyLimitCurve(enthalpyCurve));
  ASSERT_TRUE(controller.setHumidistatControlZone(humidistatZone));
  ASSERT_TRUE(model.save(firstIdfPath, true));

  auto loadedModel = Model::load(firstIdfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedOA = loadedModel->getConcreteModelObjectByName<AirLoopHVACOutdoorAirSystem>("Relationship OA System");
  auto loadedController = loadedModel->getConcreteModelObjectByName<ControllerOutdoorAir>("Relationship OA Controller");
  auto loadedMinimum = loadedModel->getConcreteModelObjectByName<ScheduleConstant>("Relationship Minimum OA Schedule");
  auto loadedCurve = loadedModel->getConcreteModelObjectByName<CurveLinear>("Relationship Electronic Enthalpy Curve");
  auto loadedZone = loadedModel->getConcreteModelObjectByName<ThermalZone>("Relationship Humidistat Zone");
  ASSERT_TRUE(loadedOA);
  ASSERT_TRUE(loadedController);
  ASSERT_TRUE(loadedMinimum);
  ASSERT_TRUE(loadedCurve);
  ASSERT_TRUE(loadedZone);
  EXPECT_EQ(loadedController->handle(), loadedOA->getControllerOutdoorAir().handle());
  EXPECT_EQ(loadedMinimum->handle(), loadedController->minimumOutdoorAirSchedule()->handle());
  EXPECT_EQ(loadedCurve->handle(), loadedController->electronicEnthalpyLimitCurve()->handle());
  EXPECT_EQ(loadedZone->handle(), loadedController->humidistatControlZone()->handle());

  ScheduleConstant replacementMinimum(*loadedModel);
  ASSERT_TRUE(replacementMinimum.setName("Replacement Minimum OA Schedule"));
  ASSERT_TRUE(loadedController->setMinimumOutdoorAirSchedule(replacementMinimum));
  loadedController->resetMinimumFractionofOutdoorAirSchedule();
  loadedController->resetMaximumFractionofOutdoorAirSchedule();
  loadedController->resetTimeofDayEconomizerControlSchedule();
  loadedController->resetElectronicEnthalpyLimitCurve();
  loadedController->resetHumidistatControlZone();
  ASSERT_TRUE(loadedModel->save(secondIdfPath, true));

  auto reloadedModel = Model::load(secondIdfPath);
  ASSERT_TRUE(reloadedModel);
  auto reloadedOA = reloadedModel->getConcreteModelObjectByName<AirLoopHVACOutdoorAirSystem>("Relationship OA System");
  auto reloadedController = reloadedModel->getConcreteModelObjectByName<ControllerOutdoorAir>("Relationship OA Controller");
  auto reloadedReplacement = reloadedModel->getConcreteModelObjectByName<ScheduleConstant>("Replacement Minimum OA Schedule");
  auto reloadedCurve = reloadedModel->getConcreteModelObjectByName<CurveLinear>("Relationship Electronic Enthalpy Curve");
  auto reloadedZone = reloadedModel->getConcreteModelObjectByName<ThermalZone>("Relationship Humidistat Zone");
  ASSERT_TRUE(reloadedOA);
  ASSERT_TRUE(reloadedController);
  ASSERT_TRUE(reloadedReplacement);
  ASSERT_TRUE(reloadedCurve);
  ASSERT_TRUE(reloadedZone);
  EXPECT_EQ(reloadedReplacement->handle(), reloadedController->minimumOutdoorAirSchedule()->handle());
  EXPECT_FALSE(reloadedController->minimumFractionofOutdoorAirSchedule());
  EXPECT_FALSE(reloadedController->maximumFractionofOutdoorAirSchedule());
  EXPECT_FALSE(reloadedController->timeofDayEconomizerControlSchedule());
  EXPECT_FALSE(reloadedController->electronicEnthalpyLimitCurve());
  EXPECT_FALSE(reloadedController->humidistatControlZone());

  ControllerOutdoorAir replacementController(*reloadedModel);
  ASSERT_TRUE(reloadedOA->setControllerOutdoorAir(replacementController));
  EXPECT_EQ(replacementController.handle(), reloadedOA->getControllerOutdoorAir().handle());
  EXPECT_FALSE(reloadedController->remove().empty());
  EXPECT_TRUE(reloadedModel->getObject(reloadedReplacement->handle()));
  EXPECT_TRUE(reloadedModel->getObject(reloadedCurve->handle()));
  EXPECT_TRUE(reloadedModel->getObject(reloadedZone->handle()));
}

TEST_F(EPModelFixture, ControllerOutdoorAir_DedicatedRelationshipsPersistAfterReturningToOrdinaryOwnership) {
  const auto idfPath = uniqueIdfPath("epmodel-controller-outdoor-air-dedicated-relationships");
  const ScopedFileRemoval removeIdf(idfPath);

  Model model;
  AirLoopHVACOutdoorAirSystem dedicatedOA(model);
  auto controller = dedicatedOA.getControllerOutdoorAir();
  ScheduleConstant minimumOutdoorAir(model);
  CurveLinear enthalpyCurve(model);
  ThermalZone humidistatZone(model);
  ASSERT_TRUE(dedicatedOA.setName("Dedicated Relationship OA System"));
  ASSERT_TRUE(controller.setName("Dedicated Relationship OA Controller"));
  ASSERT_TRUE(minimumOutdoorAir.setName("Dedicated Minimum OA Schedule"));
  ASSERT_TRUE(enthalpyCurve.setName("Dedicated Electronic Enthalpy Curve"));
  ASSERT_TRUE(humidistatZone.setName("Dedicated Humidistat Zone"));
  ASSERT_TRUE(controller.setMinimumOutdoorAirSchedule(minimumOutdoorAir));
  ASSERT_TRUE(controller.setElectronicEnthalpyLimitCurve(enthalpyCurve));
  ASSERT_TRUE(controller.setHumidistatControlZone(humidistatZone));

  AirLoopHVACDedicatedOutdoorAirSystem doas(dedicatedOA);
  auto projectedController = dedicatedOA.getControllerOutdoorAir();
  EXPECT_EQ(controller.handle(), projectedController.handle());
  EXPECT_EQ(minimumOutdoorAir.handle(), projectedController.minimumOutdoorAirSchedule()->handle());
  EXPECT_EQ(enthalpyCurve.handle(), projectedController.electronicEnthalpyLimitCurve()->handle());
  EXPECT_EQ(humidistatZone.handle(), projectedController.humidistatControlZone()->handle());

  EXPECT_FALSE(doas.remove().empty());
  EXPECT_FALSE(dedicatedOA.airLoopHVACDedicatedOutdoorAirSystem());
  auto restoredController = dedicatedOA.getControllerOutdoorAir();
  EXPECT_EQ(controller.handle(), restoredController.handle());
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedController = loadedModel->getConcreteModelObjectByName<ControllerOutdoorAir>("Dedicated Relationship OA Controller");
  auto loadedMinimum = loadedModel->getConcreteModelObjectByName<ScheduleConstant>("Dedicated Minimum OA Schedule");
  auto loadedCurve = loadedModel->getConcreteModelObjectByName<CurveLinear>("Dedicated Electronic Enthalpy Curve");
  auto loadedZone = loadedModel->getConcreteModelObjectByName<ThermalZone>("Dedicated Humidistat Zone");
  ASSERT_TRUE(loadedController);
  ASSERT_TRUE(loadedMinimum);
  ASSERT_TRUE(loadedCurve);
  ASSERT_TRUE(loadedZone);
  EXPECT_EQ(loadedMinimum->handle(), loadedController->minimumOutdoorAirSchedule()->handle());
  EXPECT_EQ(loadedCurve->handle(), loadedController->electronicEnthalpyLimitCurve()->handle());
  EXPECT_EQ(loadedZone->handle(), loadedController->humidistatControlZone()->handle());
}

TEST_F(EPModelFixture, API_ControllerOutdoorAir_ControllerMechanicalVentilationOnDemandCreation) {
  Model model;
  ControllerOutdoorAir controller(model);
  const auto numCMV = [&model]() { return model.getObjectsByType(openstudio::IddObjectType::Controller_MechanicalVentilation).size(); };

  EXPECT_EQ(0, numCMV());

  auto controllerMechanicalVentilation = controller.controllerMechanicalVentilation();
  EXPECT_EQ(ControllerMechanicalVentilation::iddObjectType(), controllerMechanicalVentilation.iddObject().type());
  ASSERT_EQ(1, numCMV());

  auto secondRead = controller.controllerMechanicalVentilation();
  EXPECT_EQ(secondRead, controllerMechanicalVentilation);
}

TEST_F(EPModelFixture, ControllerOutdoorAir_MechanicalVentilationEnforcesUniqueOwnershipAndPreservesReplacement) {
  Model model;
  ControllerOutdoorAir firstController(model);
  ControllerOutdoorAir secondController(model);
  auto firstMechanicalVentilation = firstController.controllerMechanicalVentilation();
  const auto firstMechanicalVentilationHandle = firstMechanicalVentilation.handle();

  ASSERT_TRUE(firstMechanicalVentilation.controllerOutdoorAir());
  EXPECT_EQ(firstController, *firstMechanicalVentilation.controllerOutdoorAir());
  EXPECT_TRUE(firstController.setControllerMechanicalVentilation(firstMechanicalVentilation));
  EXPECT_FALSE(secondController.setControllerMechanicalVentilation(firstMechanicalVentilation));
  EXPECT_FALSE(detail::ControllerMechanicalVentilation_Impl::observeOutdoorAirClaimField(secondController).hasEvidence);

  ControllerMechanicalVentilation replacement(model);
  ASSERT_TRUE(firstController.setControllerMechanicalVentilation(replacement));
  EXPECT_EQ(replacement, firstController.controllerMechanicalVentilation());
  EXPECT_FALSE(firstMechanicalVentilation.controllerOutdoorAir());
  EXPECT_TRUE(model.getObject(firstMechanicalVentilationHandle));
  ASSERT_TRUE(replacement.controllerOutdoorAir());
  EXPECT_EQ(firstController, *replacement.controllerOutdoorAir());

  Model foreignModel;
  ControllerMechanicalVentilation foreign(foreignModel);
  EXPECT_FALSE(firstController.setControllerMechanicalVentilation(foreign));
  EXPECT_EQ(replacement, firstController.controllerMechanicalVentilation());
}

TEST_F(EPModelFixture, ControllerOutdoorAir_MalformedMechanicalVentilationAliasRejectsWithoutMutationAndCanonicalizeClearsAlias) {
  Model model;
  ControllerOutdoorAir owner(model);
  ControllerOutdoorAir malformedClaimant(model);
  auto mechanicalVentilation = owner.controllerMechanicalVentilation();
  constexpr unsigned field = openstudio::Controller_OutdoorAirFields::MechanicalVentilationControllerName;

  auto malformedImpl = malformedClaimant.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(malformedImpl);
  ASSERT_TRUE(malformedImpl->setPointer(field, openstudio::Handle(), false));
  ASSERT_TRUE(malformedImpl->openstudio::detail::IdfObject_Impl::setString(field, mechanicalVentilation.nameString(), false));
  const auto countBefore = model.getConcreteModelObjects<ControllerMechanicalVentilation>().size();

  EXPECT_FALSE(mechanicalVentilation.controllerOutdoorAir());
  EXPECT_FALSE(malformedClaimant.setControllerMechanicalVentilation(mechanicalVentilation));
  EXPECT_THROW(malformedClaimant.controllerMechanicalVentilation(), openstudio::Exception);
  EXPECT_EQ(mechanicalVentilation.nameString(), malformedImpl->openstudio::detail::IdfObject_Impl::getString(field, false, true).value_or(""));
  EXPECT_EQ(countBefore, model.getConcreteModelObjects<ControllerMechanicalVentilation>().size());

  const auto report = model.canonicalize(SanitizationPolicy::Repair);
  EXPECT_EQ(0u, report.errorCount);
  EXPECT_FALSE(detail::ControllerMechanicalVentilation_Impl::observeOutdoorAirClaimField(malformedClaimant).hasEvidence);
  ASSERT_TRUE(mechanicalVentilation.controllerOutdoorAir());
  EXPECT_EQ(owner, *mechanicalVentilation.controllerOutdoorAir());
  EXPECT_EQ(countBefore, model.getConcreteModelObjects<ControllerMechanicalVentilation>().size());

  ControllerOutdoorAir ambiguousClaimant(model);
  ControllerMechanicalVentilation firstDuplicate(model);
  ControllerMechanicalVentilation secondDuplicate(model);
  auto firstDuplicateImpl = firstDuplicate.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  auto secondDuplicateImpl = secondDuplicate.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  auto ambiguousImpl = ambiguousClaimant.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(firstDuplicateImpl);
  ASSERT_TRUE(secondDuplicateImpl);
  ASSERT_TRUE(ambiguousImpl);
  ASSERT_TRUE(firstDuplicateImpl->setName("Ambiguous CMV", false));
  ASSERT_TRUE(secondDuplicateImpl->setName("Ambiguous CMV", false));
  ASSERT_TRUE(ambiguousImpl->setPointer(field, openstudio::Handle(), false));
  ASSERT_TRUE(ambiguousImpl->openstudio::detail::IdfObject_Impl::setString(field, "Ambiguous CMV", false));

  const auto duplicateReport = model.canonicalize(SanitizationPolicy::Repair);
  EXPECT_EQ(0u, duplicateReport.errorCount);
  EXPECT_FALSE(detail::ControllerMechanicalVentilation_Impl::observeOutdoorAirClaimField(ambiguousClaimant).hasEvidence);
}

TEST_F(EPModelFixture, ControllerOutdoorAir_LoadSplitsSharedMechanicalVentilationAndHydratesCanonicalClaims) {
  const auto idfPath = uniqueIdfPath("epmodel-controller-outdoor-air-shared-cmv");
  const auto secondIdfPath = uniqueIdfPath("epmodel-controller-outdoor-air-shared-cmv-second");
  const ScopedFileRemoval removeIdf(idfPath);
  const ScopedFileRemoval removeSecondIdf(secondIdfPath);

  Model model;
  ControllerOutdoorAir firstController(model);
  ControllerOutdoorAir secondController(model);
  ScheduleConstant availability(model);
  ThermalZone servedZone(model);
  DesignSpecificationOutdoorAirSpaceList dsoaSpaceList(model);
  ASSERT_TRUE(firstController.setName("First Shared CMV Owner"));
  ASSERT_TRUE(secondController.setName("Second Shared CMV Owner"));
  ASSERT_TRUE(availability.setName("Shared CMV Availability"));
  ASSERT_TRUE(servedZone.setName("Shared CMV Served Zone"));
  ASSERT_TRUE(dsoaSpaceList.setName("Shared CMV DSOA Space List"));
  ASSERT_TRUE(availability.setValue(1.0));
  auto sharedMechanicalVentilation = firstController.controllerMechanicalVentilation();
  ASSERT_TRUE(sharedMechanicalVentilation.setName("Imported Shared CMV"));
  ASSERT_TRUE(sharedMechanicalVentilation.setAvailabilitySchedule(availability));
  ASSERT_TRUE(sharedMechanicalVentilation.setDemandControlledVentilation(true));
  ASSERT_TRUE(sharedMechanicalVentilation.setSystemOutdoorAirMethod("ZoneSum"));
  auto sharedMechanicalVentilationImpl = sharedMechanicalVentilation.getImpl<detail::ControllerMechanicalVentilation_Impl>();
  ASSERT_TRUE(sharedMechanicalVentilationImpl);
  ASSERT_TRUE(sharedMechanicalVentilationImpl->addZoneOutdoorAirEntry(servedZone, dsoaSpaceList));

  constexpr unsigned field = openstudio::Controller_OutdoorAirFields::MechanicalVentilationControllerName;
  auto secondControllerImpl = secondController.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(secondControllerImpl);
  ASSERT_TRUE(secondControllerImpl->setPointer(field, sharedMechanicalVentilation.handle(), false));
  ASSERT_EQ(2u, sharedMechanicalVentilation.getModelObjectSources<ControllerOutdoorAir>().size());
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedFirst = loadedModel->getConcreteModelObjectByName<ControllerOutdoorAir>("First Shared CMV Owner");
  auto loadedSecond = loadedModel->getConcreteModelObjectByName<ControllerOutdoorAir>("Second Shared CMV Owner");
  auto loadedAvailability = loadedModel->getConcreteModelObjectByName<ScheduleConstant>("Shared CMV Availability");
  auto loadedZone = loadedModel->getConcreteModelObjectByName<ThermalZone>("Shared CMV Served Zone");
  auto loadedDSOA = loadedModel->getConcreteModelObjectByName<DesignSpecificationOutdoorAirSpaceList>("Shared CMV DSOA Space List");
  ASSERT_TRUE(loadedFirst);
  ASSERT_TRUE(loadedSecond);
  ASSERT_TRUE(loadedAvailability);
  ASSERT_TRUE(loadedZone);
  ASSERT_TRUE(loadedDSOA);
  ASSERT_EQ(2u, loadedModel->getConcreteModelObjects<ControllerMechanicalVentilation>().size());

  auto firstCMV = loadedFirst->controllerMechanicalVentilation();
  auto secondCMV = loadedSecond->controllerMechanicalVentilation();
  const auto firstCMVHandle = firstCMV.handle();
  const auto secondCMVHandle = secondCMV.handle();
  const auto firstCMVName = firstCMV.nameString();
  const auto secondCMVName = secondCMV.nameString();
  EXPECT_NE(firstCMV, secondCMV);
  const std::array<std::pair<ControllerOutdoorAir, ControllerMechanicalVentilation>, 2> loadedRelationships{std::make_pair(*loadedFirst, firstCMV),
                                                                                                            std::make_pair(*loadedSecond, secondCMV)};
  for (const auto& [controller, cmv] : loadedRelationships) {
    const auto observation = detail::ControllerMechanicalVentilation_Impl::observeOutdoorAirClaimField(controller);
    EXPECT_TRUE(observation.canonical);
    EXPECT_FALSE(observation.rawTarget);
    ASSERT_TRUE(observation.managedTargetHandle);
    EXPECT_EQ(cmv.handle(), *observation.managedTargetHandle);
    ASSERT_TRUE(cmv.controllerOutdoorAir());
    EXPECT_EQ(controller, *cmv.controllerOutdoorAir());
    EXPECT_EQ(loadedAvailability->handle(), cmv.availabilitySchedule().handle());
    EXPECT_TRUE(cmv.demandControlledVentilation());
    EXPECT_EQ("ZoneSum", cmv.systemOutdoorAirMethod());
    const auto entries = cmv.getImpl<detail::ControllerMechanicalVentilation_Impl>()->zoneOutdoorAirEntries();
    ASSERT_EQ(1u, entries.size());
    EXPECT_EQ(loadedZone->handle(), entries.front().first.handle());
    EXPECT_EQ(loadedDSOA->handle(), entries.front().second.handle());
  }

  const auto secondReport = loadedModel->canonicalize(SanitizationPolicy::Repair);
  EXPECT_EQ(0u, secondReport.errorCount);
  EXPECT_EQ(2u, loadedModel->getConcreteModelObjects<ControllerMechanicalVentilation>().size());
  EXPECT_EQ(firstCMVHandle, loadedFirst->controllerMechanicalVentilation().handle());
  EXPECT_EQ(secondCMVHandle, loadedSecond->controllerMechanicalVentilation().handle());
  ASSERT_TRUE(loadedModel->save(secondIdfPath, true));

  auto reloadedModel = Model::load(secondIdfPath);
  ASSERT_TRUE(reloadedModel);
  auto reloadedFirst = reloadedModel->getConcreteModelObjectByName<ControllerOutdoorAir>("First Shared CMV Owner");
  auto reloadedSecond = reloadedModel->getConcreteModelObjectByName<ControllerOutdoorAir>("Second Shared CMV Owner");
  ASSERT_TRUE(reloadedFirst);
  ASSERT_TRUE(reloadedSecond);
  ASSERT_EQ(2u, reloadedModel->getConcreteModelObjects<ControllerMechanicalVentilation>().size());
  auto reloadedFirstCMV = reloadedFirst->controllerMechanicalVentilation();
  auto reloadedSecondCMV = reloadedSecond->controllerMechanicalVentilation();
  EXPECT_EQ(firstCMVName, reloadedFirstCMV.nameString());
  EXPECT_EQ(secondCMVName, reloadedSecondCMV.nameString());
  EXPECT_EQ(*reloadedFirst, *reloadedFirstCMV.controllerOutdoorAir());
  EXPECT_EQ(*reloadedSecond, *reloadedSecondCMV.controllerOutdoorAir());
  auto reloadedAvailability = reloadedModel->getConcreteModelObjectByName<ScheduleConstant>("Shared CMV Availability");
  auto reloadedZone = reloadedModel->getConcreteModelObjectByName<ThermalZone>("Shared CMV Served Zone");
  auto reloadedDSOA = reloadedModel->getConcreteModelObjectByName<DesignSpecificationOutdoorAirSpaceList>("Shared CMV DSOA Space List");
  ASSERT_TRUE(reloadedAvailability);
  ASSERT_TRUE(reloadedZone);
  ASSERT_TRUE(reloadedDSOA);
  for (const auto& cmv : {reloadedFirstCMV, reloadedSecondCMV}) {
    EXPECT_EQ(reloadedAvailability->handle(), cmv.availabilitySchedule().handle());
    EXPECT_TRUE(cmv.demandControlledVentilation());
    EXPECT_EQ("ZoneSum", cmv.systemOutdoorAirMethod());
    const auto entries = cmv.getImpl<detail::ControllerMechanicalVentilation_Impl>()->zoneOutdoorAirEntries();
    ASSERT_EQ(1u, entries.size());
    EXPECT_EQ(reloadedZone->handle(), entries.front().first.handle());
    EXPECT_EQ(reloadedDSOA->handle(), entries.front().second.handle());
  }
}

TEST_F(EPModelFixture, ControllerMechanicalVentilation_RowSyncIsNoOpForSharedOrdinaryOutdoorAirController) {
  Model model;
  AirLoopHVAC firstLoop(model);
  AirLoopHVAC secondLoop(model);
  AirLoopHVACOutdoorAirSystem firstOutdoorAirSystem(model);
  AirLoopHVACOutdoorAirSystem secondOutdoorAirSystem(model);
  auto firstSupplyInlet = firstLoop.supplyInletNode();
  auto secondSupplyInlet = secondLoop.supplyInletNode();
  ASSERT_TRUE(firstOutdoorAirSystem.addToNode(firstSupplyInlet));
  ASSERT_TRUE(secondOutdoorAirSystem.addToNode(secondSupplyInlet));
  ThermalZone zone(model);
  auto firstBranchObject = firstLoop.zoneSplitter().lastOutletModelObject();
  ASSERT_TRUE(firstBranchObject);
  auto firstBranchNode = firstBranchObject->optionalCast<Node>();
  ASSERT_TRUE(firstBranchNode);
  ASSERT_TRUE(zone.addToNode(*firstBranchNode));
  for (auto sizingZone : model.getConcreteModelObjects<SizingZone>()) {
    ASSERT_FALSE(sizingZone.remove().empty());
  }
  ASSERT_TRUE(model.getConcreteModelObjects<SizingZone>().empty());

  auto sharedController = firstOutdoorAirSystem.getControllerOutdoorAir();
  ASSERT_TRUE(secondOutdoorAirSystem.setControllerOutdoorAir(sharedController));
  auto mechanicalVentilation = sharedController.controllerMechanicalVentilation();
  DesignSpecificationOutdoorAirSpaceList dsoaSpaceList(model);
  auto mechanicalVentilationImpl = mechanicalVentilation.getImpl<detail::ControllerMechanicalVentilation_Impl>();
  ASSERT_TRUE(mechanicalVentilationImpl);
  ASSERT_TRUE(mechanicalVentilationImpl->addZoneOutdoorAirEntry(zone, dsoaSpaceList));
  ASSERT_EQ(1u, mechanicalVentilation.numExtensibleGroups());
  ASSERT_TRUE(model.getConcreteModelObjects<SizingZone>().empty());
  std::vector<openstudio::Handle> inventoryBefore;
  std::ranges::transform(model.objects(), std::back_inserter(inventoryBefore), [](const auto& object) { return object.handle(); });
  std::ranges::sort(inventoryBefore);
  std::ostringstream rawBefore;
  mechanicalVentilation.idfObject().print(rawBefore);

  firstLoop.getImpl<detail::AirLoopHVAC_Impl>()->syncControllerMechanicalVentilationZoneOutdoorAirEntries();
  EXPECT_EQ(1u, mechanicalVentilation.numExtensibleGroups());
  EXPECT_FALSE(sharedController.airLoopHVACOutdoorAirSystem());
  EXPECT_EQ(sharedController, *mechanicalVentilation.controllerOutdoorAir());
  EXPECT_TRUE(model.getConcreteModelObjects<SizingZone>().empty());
  std::vector<openstudio::Handle> inventoryAfter;
  std::ranges::transform(model.objects(), std::back_inserter(inventoryAfter), [](const auto& object) { return object.handle(); });
  std::ranges::sort(inventoryAfter);
  EXPECT_EQ(inventoryBefore, inventoryAfter);
  std::ostringstream rawAfter;
  mechanicalVentilation.idfObject().print(rawAfter);
  EXPECT_EQ(rawBefore.str(), rawAfter.str());
}

TEST_F(EPModelFixture, ControllerMechanicalVentilation_RowSyncRejectsRawNodeAnchorBeforeTraversal) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACOutdoorAirSystem outdoorAirSystem(model);
  auto supplyInlet = airLoop.supplyInletNode();
  ASSERT_TRUE(outdoorAirSystem.addToNode(supplyInlet));
  ThermalZone zone(model);
  auto branchObject = airLoop.zoneSplitter().lastOutletModelObject();
  ASSERT_TRUE(branchObject);
  auto branchNode = branchObject->optionalCast<Node>();
  ASSERT_TRUE(branchNode);
  ASSERT_TRUE(zone.addToNode(*branchNode));

  auto mechanicalVentilation = outdoorAirSystem.getControllerOutdoorAir().controllerMechanicalVentilation();
  for (auto sizingZone : model.getConcreteModelObjects<SizingZone>()) {
    ASSERT_FALSE(sizingZone.remove().empty());
  }
  ASSERT_TRUE(model.getConcreteModelObjects<SizingZone>().empty());
  DesignSpecificationOutdoorAirSpaceList dsoaSpaceList(model);
  auto mechanicalVentilationImpl = mechanicalVentilation.getImpl<detail::ControllerMechanicalVentilation_Impl>();
  ASSERT_TRUE(mechanicalVentilationImpl);
  ASSERT_TRUE(mechanicalVentilationImpl->addZoneOutdoorAirEntry(zone, dsoaSpaceList));

  auto airLoopWorkspaceImpl = airLoop.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(airLoopWorkspaceImpl);
  ASSERT_TRUE(airLoopWorkspaceImpl->openstudio::detail::IdfObject_Impl::setString(openstudio::AirLoopHVACFields::SupplySideOutletNodeNames,
                                                                                  "Conflicting Raw Supply Outlet NodeList", false));
  const auto before = exactObjectInventory(model);

  airLoop.getImpl<detail::AirLoopHVAC_Impl>()->syncControllerMechanicalVentilationZoneOutdoorAirEntries();

  EXPECT_EQ(before, exactObjectInventory(model));
  EXPECT_TRUE(model.getConcreteModelObjects<SizingZone>().empty());
}

TEST_F(EPModelFixture, ControllerMechanicalVentilation_RowSyncRejectsRawDuplicateOutdoorAirOwnershipChain) {
  enum class MalformedCase
  {
    OutdoorAirBranchRow,
    BranchListMembership,
    AirLoopOwner,
  };

  for (const auto malformedCase : {MalformedCase::OutdoorAirBranchRow, MalformedCase::BranchListMembership, MalformedCase::AirLoopOwner}) {
    Model model;
    AirLoopHVAC airLoop(model);
    AirLoopHVACOutdoorAirSystem outdoorAirSystem(model);
    auto supplyInlet = airLoop.supplyInletNode();
    ASSERT_TRUE(outdoorAirSystem.addToNode(supplyInlet));
    ThermalZone zone(model);
    auto branchObject = airLoop.zoneSplitter().lastOutletModelObject();
    ASSERT_TRUE(branchObject);
    auto branchNode = branchObject->optionalCast<Node>();
    ASSERT_TRUE(branchNode);
    ASSERT_TRUE(zone.addToNode(*branchNode));

    auto mechanicalVentilation = outdoorAirSystem.getControllerOutdoorAir().controllerMechanicalVentilation();
    for (auto sizingZone : model.getConcreteModelObjects<SizingZone>()) {
      ASSERT_FALSE(sizingZone.remove().empty());
    }
    ASSERT_TRUE(model.getConcreteModelObjects<SizingZone>().empty());
    DesignSpecificationOutdoorAirSpaceList dsoaSpaceList(model);
    auto mechanicalVentilationImpl = mechanicalVentilation.getImpl<detail::ControllerMechanicalVentilation_Impl>();
    ASSERT_TRUE(mechanicalVentilationImpl);
    ASSERT_TRUE(mechanicalVentilationImpl->addZoneOutdoorAirEntry(zone, dsoaSpaceList));

    auto supplyBranchList = airLoop.getModelObjectTarget<BranchList>(openstudio::AirLoopHVACFields::BranchListName);
    ASSERT_TRUE(supplyBranchList);
    boost::optional<Branch> outdoorAirBranch;
    for (const auto& branch : supplyBranchList->branches()) {
      const auto components = branch.components();
      if (std::ranges::find(components, outdoorAirSystem.cast<ModelObject>()) != components.end()) {
        ASSERT_FALSE(outdoorAirBranch);
        outdoorAirBranch = branch;
      }
    }
    ASSERT_TRUE(outdoorAirBranch);

    if (malformedCase == MalformedCase::OutdoorAirBranchRow) {
      Branch rawAliasBranch(model);
      ASSERT_TRUE(rawAliasBranch.pushExtensibleGroup().optionalCast<openstudio::WorkspaceExtensibleGroup>());
      auto aliasImpl = rawAliasBranch.getImpl<openstudio::detail::WorkspaceObject_Impl>();
      ASSERT_TRUE(aliasImpl);
      const auto typeField =
        rawAliasBranch.iddObject().index(openstudio::ExtensibleIndex(0u, openstudio::BranchExtensibleFields::ComponentObjectType));
      const auto nameField = rawAliasBranch.iddObject().index(openstudio::ExtensibleIndex(0u, openstudio::BranchExtensibleFields::ComponentName));
      ASSERT_TRUE(aliasImpl->openstudio::detail::IdfObject_Impl::setString(typeField, outdoorAirSystem.iddObject().name(), false));
      ASSERT_TRUE(aliasImpl->openstudio::detail::IdfObject_Impl::setString(nameField, outdoorAirSystem.nameString(), false));
    } else if (malformedCase == MalformedCase::BranchListMembership) {
      BranchList rawAliasList(model);
      ASSERT_TRUE(rawAliasList.pushExtensibleGroup().optionalCast<openstudio::WorkspaceExtensibleGroup>());
      auto aliasImpl = rawAliasList.getImpl<openstudio::detail::WorkspaceObject_Impl>();
      ASSERT_TRUE(aliasImpl);
      const auto branchField = rawAliasList.iddObject().index(openstudio::ExtensibleIndex(0u, openstudio::BranchListExtensibleFields::BranchName));
      ASSERT_TRUE(aliasImpl->openstudio::detail::IdfObject_Impl::setString(branchField, outdoorAirBranch->nameString(), false));
    } else {
      AirLoopHVAC rawAliasOwner(model);
      auto aliasImpl = rawAliasOwner.getImpl<openstudio::detail::WorkspaceObject_Impl>();
      ASSERT_TRUE(aliasImpl);
      ASSERT_TRUE(aliasImpl->openstudio::detail::IdfObject_Impl::setString(openstudio::AirLoopHVACFields::BranchListName,
                                                                           supplyBranchList->nameString(), false));
    }

    const auto before = exactObjectInventory(model);
    airLoop.getImpl<detail::AirLoopHVAC_Impl>()->syncControllerMechanicalVentilationZoneOutdoorAirEntries();
    EXPECT_EQ(before, exactObjectInventory(model));
    EXPECT_TRUE(model.getConcreteModelObjects<SizingZone>().empty());
  }
}

TEST_F(EPModelFixture, API_ControllerOutdoorAir_Canonicalize_DoesNotSynthesizeCMVWithoutServedZoneDSOA) {
  Model model;
  const auto numCMV = [&model]() { return model.getObjectsByType(openstudio::IddObjectType::Controller_MechanicalVentilation).size(); };
  AirLoopHVAC airLoop(model);
  AirLoopHVACOutdoorAirSystem outdoorAirSystem(model);
  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(outdoorAirSystem.addToNode(supplyInletNode));

  ThermalZone zone(model);
  auto branchObject = airLoop.zoneSplitter().lastOutletModelObject();
  ASSERT_TRUE(branchObject);
  auto branchNode = branchObject->optionalCast<Node>();
  ASSERT_TRUE(branchNode);
  ASSERT_TRUE(zone.addToNode(*branchNode));

  auto controller = outdoorAirSystem.getControllerOutdoorAir();
  EXPECT_EQ(0, numCMV());

  model.canonicalize(SanitizationPolicy::Repair);

  controller = outdoorAirSystem.getControllerOutdoorAir();
  EXPECT_EQ(0, numCMV());
}

TEST_F(EPModelFixture, API_ControllerOutdoorAir_Canonicalize_SynthesizesCMVAndZoneEntriesForServedZoneDSOA) {
  Model model;
  const auto numCMV = [&model]() { return model.getObjectsByType(openstudio::IddObjectType::Controller_MechanicalVentilation).size(); };
  AirLoopHVAC airLoop(model);
  AirLoopHVACOutdoorAirSystem outdoorAirSystem(model);
  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(outdoorAirSystem.addToNode(supplyInletNode));

  ThermalZone zone(model);
  auto branchObject = airLoop.zoneSplitter().lastOutletModelObject();
  ASSERT_TRUE(branchObject);
  auto branchNode = branchObject->optionalCast<Node>();
  ASSERT_TRUE(branchNode);
  ASSERT_TRUE(zone.addToNode(*branchNode));

  Space space(model);
  ASSERT_TRUE(space.setThermalZone(zone));
  DesignSpecificationOutdoorAir dsoa(model);
  ASSERT_TRUE(space.setDesignSpecificationOutdoorAir(dsoa));

  auto controller = outdoorAirSystem.getControllerOutdoorAir();
  EXPECT_EQ(0, numCMV());
  constexpr unsigned mechanicalVentilationField = openstudio::Controller_OutdoorAirFields::MechanicalVentilationControllerName;
  auto controllerWorkspaceImpl = controller.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(controllerWorkspaceImpl);
  ASSERT_TRUE(controllerWorkspaceImpl->setPointer(mechanicalVentilationField, openstudio::Handle(), false));
  ASSERT_TRUE(
    controllerWorkspaceImpl->openstudio::detail::IdfObject_Impl::setString(mechanicalVentilationField, "Missing Mechanical Ventilation", false));

  model.canonicalize(SanitizationPolicy::Repair);

  controller = outdoorAirSystem.getControllerOutdoorAir();
  ASSERT_EQ(1, numCMV());
  const auto repairedObservation = detail::ControllerMechanicalVentilation_Impl::observeOutdoorAirClaimField(controller);
  EXPECT_TRUE(repairedObservation.canonical);
  EXPECT_FALSE(repairedObservation.rawTarget);
  auto cmv = controller.controllerMechanicalVentilation();
  ASSERT_EQ(1u, cmv.numExtensibleGroups());

  auto group = cmv.extensibleGroups().front();
  auto workspaceGroup = group.optionalCast<openstudio::WorkspaceExtensibleGroup>();
  ASSERT_TRUE(workspaceGroup);

  auto zoneTarget = workspaceGroup->getTarget(openstudio::Controller_MechanicalVentilationExtensibleFields::ZoneorZoneListName);
  ASSERT_TRUE(zoneTarget);
  auto zoneCast = zoneTarget->optionalCast<ThermalZone>();
  ASSERT_TRUE(zoneCast);
  EXPECT_EQ(zone, *zoneCast);

  auto dsoaTarget = workspaceGroup->getTarget(openstudio::Controller_MechanicalVentilationExtensibleFields::DesignSpecificationOutdoorAirObjectName);
  ASSERT_TRUE(dsoaTarget);
  auto sizingZone = zone.sizingZone();
  auto expectedDsoaObject = sizingZone.getModelObjectTarget<ModelObject>(openstudio::Sizing_ZoneFields::DesignSpecificationOutdoorAirObjectName);
  ASSERT_TRUE(expectedDsoaObject);
  auto dsoaAsModelObject = dsoaTarget->optionalCast<ModelObject>();
  ASSERT_TRUE(dsoaAsModelObject);
  EXPECT_EQ(*expectedDsoaObject, *dsoaAsModelObject);
}

TEST_F(EPModelFixture, API_ControllerMechanicalVentilation_ImplOnlyZoneOutdoorAirEntries_LoopScoped) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACOutdoorAirSystem outdoorAirSystem(model);
  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(outdoorAirSystem.addToNode(supplyInletNode));

  ThermalZone zoneWithDSOA(model);
  auto branchObject = airLoop.zoneSplitter().lastOutletModelObject();
  ASSERT_TRUE(branchObject);
  auto branchNode = branchObject->optionalCast<Node>();
  ASSERT_TRUE(branchNode);
  ASSERT_TRUE(zoneWithDSOA.addToNode(*branchNode));

  Space spaceWithDSOA(model);
  ASSERT_TRUE(spaceWithDSOA.setThermalZone(zoneWithDSOA));
  DesignSpecificationOutdoorAir dsoa(model);
  ASSERT_TRUE(spaceWithDSOA.setDesignSpecificationOutdoorAir(dsoa));

  auto cmv = outdoorAirSystem.getControllerOutdoorAir().controllerMechanicalVentilation();
  airLoop.getImpl<openstudio::epmodel::detail::AirLoopHVAC_Impl>()->syncControllerMechanicalVentilationZoneOutdoorAirEntries();
  auto entries = cmv.getImpl<openstudio::epmodel::detail::ControllerMechanicalVentilation_Impl>()->zoneOutdoorAirEntries();
  ASSERT_EQ(1u, entries.size());
  EXPECT_EQ(zoneWithDSOA, entries.front().first);
}

TEST_F(EPModelFixture, ControllerMechanicalVentilation_RowSyncSupportsZoneOnlyDirectDSOA) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-cmv-zone-only-direct-dsoa.idf");
  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACOutdoorAirSystem outdoorAirSystem(model);
  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(outdoorAirSystem.addToNode(supplyInletNode));

  ThermalZone zone(model);
  ASSERT_TRUE(zone.setName("Zone Only Direct DSOA Zone"));
  ASSERT_TRUE(airLoop.addBranchForZone(zone));
  EXPECT_TRUE(model.getConcreteModelObjects<Space>().empty());

  DesignSpecificationOutdoorAir dsoa(model);
  ASSERT_TRUE(dsoa.setName("Zone Only Direct DSOA"));
  auto sizingZone = zone.sizingZone();
  ASSERT_TRUE(sizingZone.setPointer(openstudio::Sizing_ZoneFields::DesignSpecificationOutdoorAirObjectName, dsoa.handle()));
  EXPECT_FALSE(sizingZone.getImpl<detail::SizingZone_Impl>()->designSpecificationOutdoorAirSpaceList());

  auto cmv = outdoorAirSystem.getControllerOutdoorAir().controllerMechanicalVentilation();
  auto cmvImpl = cmv.getImpl<detail::ControllerMechanicalVentilation_Impl>();
  ASSERT_TRUE(cmvImpl);
  airLoop.getImpl<detail::AirLoopHVAC_Impl>()->syncControllerMechanicalVentilationZoneOutdoorAirEntries();
  const auto entries = cmvImpl->zoneOutdoorAirEntries();
  ASSERT_EQ(1u, entries.size());
  EXPECT_EQ(zone.handle(), entries.front().first.handle());
  EXPECT_EQ(dsoa.handle(), entries.front().second.handle());
  EXPECT_TRUE(entries.front().second.optionalCast<DesignSpecificationOutdoorAir>());
  EXPECT_FALSE(entries.front().second.optionalCast<DesignSpecificationOutdoorAirSpaceList>());
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  EXPECT_TRUE(loadedModel->getConcreteModelObjects<Space>().empty());
  auto loadedCMV = loadedModel->getConcreteModelObjectByName<ControllerMechanicalVentilation>(cmv.nameString());
  ASSERT_TRUE(loadedCMV);
  const auto loadedEntries = loadedCMV->getImpl<detail::ControllerMechanicalVentilation_Impl>()->zoneOutdoorAirEntries();
  ASSERT_EQ(1u, loadedEntries.size());
  EXPECT_EQ("Zone Only Direct DSOA Zone", loadedEntries.front().first.nameString());
  EXPECT_EQ("Zone Only Direct DSOA", loadedEntries.front().second.nameString());
  EXPECT_TRUE(loadedEntries.front().second.optionalCast<DesignSpecificationOutdoorAir>());

  openstudio::filesystem::remove(idfPath);
}

TEST_F(EPModelFixture, API_ControllerMechanicalVentilation_RebuildOnThermalZoneAddToNode) {
  Model model;
  AirLoopHVAC loopA(model);
  AirLoopHVACOutdoorAirSystem oaA(model);
  auto supplyInletNodeA = loopA.supplyInletNode();
  ASSERT_TRUE(oaA.addToNode(supplyInletNodeA));
  AirLoopHVAC loopB(model);
  AirLoopHVACOutdoorAirSystem oaB(model);
  auto supplyInletNodeB = loopB.supplyInletNode();
  ASSERT_TRUE(oaB.addToNode(supplyInletNodeB));

  auto branchObjA = loopA.zoneSplitter().lastOutletModelObject();
  ASSERT_TRUE(branchObjA);
  auto branchNodeA = branchObjA->optionalCast<Node>();
  ASSERT_TRUE(branchNodeA);
  auto branchObjB = loopB.zoneSplitter().lastOutletModelObject();
  ASSERT_TRUE(branchObjB);
  auto branchNodeB = branchObjB->optionalCast<Node>();
  ASSERT_TRUE(branchNodeB);

  ThermalZone zone(model);
  ASSERT_TRUE(zone.addToNode(*branchNodeA));
  Space space(model);
  ASSERT_TRUE(space.setThermalZone(zone));
  DesignSpecificationOutdoorAir dsoa(model);
  ASSERT_TRUE(space.setDesignSpecificationOutdoorAir(dsoa));

  auto cmvA = oaA.getControllerOutdoorAir().controllerMechanicalVentilation();
  auto cmvB = oaB.getControllerOutdoorAir().controllerMechanicalVentilation();
  loopA.getImpl<openstudio::epmodel::detail::AirLoopHVAC_Impl>()->syncControllerMechanicalVentilationZoneOutdoorAirEntries();
  loopB.getImpl<openstudio::epmodel::detail::AirLoopHVAC_Impl>()->syncControllerMechanicalVentilationZoneOutdoorAirEntries();

  auto entriesA = cmvA.getImpl<openstudio::epmodel::detail::ControllerMechanicalVentilation_Impl>()->zoneOutdoorAirEntries();
  auto entriesB = cmvB.getImpl<openstudio::epmodel::detail::ControllerMechanicalVentilation_Impl>()->zoneOutdoorAirEntries();
  ASSERT_EQ(1u, entriesA.size());
  EXPECT_EQ(zone, entriesA.front().first);

  ASSERT_TRUE(zone.addToNode(*branchNodeB));

  entriesB = cmvB.getImpl<openstudio::epmodel::detail::ControllerMechanicalVentilation_Impl>()->zoneOutdoorAirEntries();
  ASSERT_EQ(1u, entriesB.size());
  EXPECT_EQ(zone, entriesB.front().first);
}
