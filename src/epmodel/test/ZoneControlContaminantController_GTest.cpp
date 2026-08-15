/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../HVACComponent/ThermalZone_Impl.hpp"
#include "../ModelObject/ZoneControlContaminantController.hpp"
#include "../ModelObject/ZoneControlContaminantController_Impl.hpp"
#include "../ResourceObject/ScheduleTypeLimits.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Schedule/ScheduleConstant_Impl.hpp"

#include <utilities/core/Filesystem.hpp>
#include <utilities/core/UUID.hpp>
#include <utilities/idd/ZoneControl_ContaminantController_FieldEnums.hxx>
#include <utilities/idf/IdfObject_Impl.hpp>
#include <utilities/idf/WorkspaceObject_Impl.hpp>

#include <utility>

using namespace openstudio::epmodel;

namespace {

class ScopedContaminantControllerFileRemoval
{
 public:
  explicit ScopedContaminantControllerFileRemoval(openstudio::path path) : m_path(std::move(path)) {}

  ~ScopedContaminantControllerFileRemoval() {
    boost::system::error_code error;
    boost::filesystem::remove(m_path, error);
  }

 private:
  openstudio::path m_path;
};

openstudio::path uniqueContaminantControllerIdfPath(const std::string& stem) {
  return openstudio::tempDir() / openstudio::toPath(stem + "-" + openstudio::removeBraces(openstudio::createUUID()) + ".idf");
}

}  // namespace

TEST_F(EPModelFixture, ZoneControlContaminantController_DefaultConstructor) {
  Model model;
  ZoneControlContaminantController controller(model);
  EXPECT_EQ(ZoneControlContaminantController::iddObjectType(), controller.iddObject().type());
  EXPECT_FALSE(controller.controlledZone());
  EXPECT_FALSE(controller.carbonDioxideControlAvailabilitySchedule());
  EXPECT_FALSE(controller.carbonDioxideSetpointSchedule());
  EXPECT_FALSE(controller.minimumCarbonDioxideConcentrationSchedule());
  EXPECT_FALSE(controller.genericContaminantControlAvailabilitySchedule());
  EXPECT_FALSE(controller.genericContaminantSetpointSchedule());
}

TEST_F(EPModelFixture, ZoneControlContaminantController_ScalarAccessors_RoundTrip) {
  Model model;
  ZoneControlContaminantController controller(model);

  EXPECT_TRUE(controller.setName("Controller A"));
  EXPECT_EQ("Controller A", controller.nameString());
}

TEST_F(EPModelFixture, ZoneControlContaminantController_RelationshipsAndGeneratedScheduleLimits) {
  Model model;
  ThermalZone zone(model);
  ZoneControlContaminantController controller(model);
  ScheduleConstant carbonDioxideAvailability(model);
  ScheduleConstant carbonDioxideSetpoint(model);
  ScheduleConstant minimumCarbonDioxide(model);
  ScheduleConstant genericAvailability(model);
  ScheduleConstant genericSetpoint(model);
  ASSERT_TRUE(carbonDioxideAvailability.setValue(1.0));
  ASSERT_TRUE(carbonDioxideSetpoint.setValue(1000.0));
  ASSERT_TRUE(minimumCarbonDioxide.setValue(400.0));
  ASSERT_TRUE(genericAvailability.setValue(1.0));
  ASSERT_TRUE(genericSetpoint.setValue(500.0));

  ASSERT_TRUE(controller.setCarbonDioxideControlAvailabilitySchedule(carbonDioxideAvailability));
  ASSERT_TRUE(controller.setCarbonDioxideSetpointSchedule(carbonDioxideSetpoint));
  ASSERT_TRUE(controller.setMinimumCarbonDioxideConcentrationSchedule(minimumCarbonDioxide));
  ASSERT_TRUE(controller.setGenericContaminantControlAvailabilitySchedule(genericAvailability));
  ASSERT_TRUE(controller.setGenericContaminantSetpointSchedule(genericSetpoint));
  ASSERT_TRUE(zone.setZoneControlContaminantController(controller));

  ASSERT_TRUE(controller.controlledZone());
  EXPECT_EQ(zone.handle(), controller.controlledZone()->handle());
  ASSERT_TRUE(zone.zoneControlContaminantController());
  EXPECT_EQ(controller.handle(), zone.zoneControlContaminantController()->handle());
  ASSERT_TRUE(controller.carbonDioxideControlAvailabilitySchedule());
  ASSERT_TRUE(controller.carbonDioxideSetpointSchedule());
  ASSERT_TRUE(controller.minimumCarbonDioxideConcentrationSchedule());
  ASSERT_TRUE(controller.genericContaminantControlAvailabilitySchedule());
  ASSERT_TRUE(controller.genericContaminantSetpointSchedule());
  EXPECT_EQ(carbonDioxideAvailability.handle(), controller.carbonDioxideControlAvailabilitySchedule()->handle());
  EXPECT_EQ(carbonDioxideSetpoint.handle(), controller.carbonDioxideSetpointSchedule()->handle());
  EXPECT_EQ(minimumCarbonDioxide.handle(), controller.minimumCarbonDioxideConcentrationSchedule()->handle());
  EXPECT_EQ(genericAvailability.handle(), controller.genericContaminantControlAvailabilitySchedule()->handle());
  EXPECT_EQ(genericSetpoint.handle(), controller.genericContaminantSetpointSchedule()->handle());

  for (const auto& schedule : {carbonDioxideAvailability, genericAvailability}) {
    ASSERT_TRUE(schedule.scheduleTypeLimits());
    const auto limits = *schedule.scheduleTypeLimits();
    ASSERT_TRUE(limits.numericType());
    EXPECT_EQ("Discrete", *limits.numericType());
    EXPECT_EQ("Availability", limits.unitType());
    ASSERT_TRUE(limits.lowerLimitValue());
    ASSERT_TRUE(limits.upperLimitValue());
    EXPECT_DOUBLE_EQ(0.0, *limits.lowerLimitValue());
    EXPECT_DOUBLE_EQ(1.0, *limits.upperLimitValue());
  }

  for (const auto& schedule : {carbonDioxideSetpoint, minimumCarbonDioxide, genericSetpoint}) {
    ASSERT_TRUE(schedule.scheduleTypeLimits());
    const auto limits = *schedule.scheduleTypeLimits();
    ASSERT_TRUE(limits.numericType());
    EXPECT_EQ("Continuous", *limits.numericType());
    EXPECT_TRUE(limits.isUnitTypeDefaulted());
    ASSERT_TRUE(limits.lowerLimitValue());
    EXPECT_DOUBLE_EQ(0.0, *limits.lowerLimitValue());
    EXPECT_FALSE(limits.upperLimitValue());
  }

  controller.resetCarbonDioxideControlAvailabilitySchedule();
  controller.resetCarbonDioxideSetpointSchedule();
  controller.resetMinimumCarbonDioxideConcentrationSchedule();
  controller.resetGenericContaminantControlAvailabilitySchedule();
  controller.resetGenericContaminantSetpointSchedule();
  EXPECT_FALSE(controller.carbonDioxideControlAvailabilitySchedule());
  EXPECT_FALSE(controller.carbonDioxideSetpointSchedule());
  EXPECT_FALSE(controller.minimumCarbonDioxideConcentrationSchedule());
  EXPECT_FALSE(controller.genericContaminantControlAvailabilitySchedule());
  EXPECT_FALSE(controller.genericContaminantSetpointSchedule());
}

TEST_F(EPModelFixture, ZoneControlContaminantController_RejectionAndUnresolvedRawPreservation) {
  Model model;
  ZoneControlContaminantController controller(model);
  ScheduleConstant acceptedAvailability(model);
  ScheduleConstant acceptedSetpoint(model);
  ASSERT_TRUE(acceptedAvailability.setValue(1.0));
  ASSERT_TRUE(acceptedSetpoint.setValue(900.0));
  ASSERT_TRUE(controller.setCarbonDioxideControlAvailabilitySchedule(acceptedAvailability));
  ASSERT_TRUE(controller.setGenericContaminantSetpointSchedule(acceptedSetpoint));

  ScheduleConstant incompatibleAvailability(model);
  ScheduleTypeLimits continuousAvailability(model);
  ASSERT_TRUE(continuousAvailability.setNumericType("Continuous"));
  ASSERT_TRUE(continuousAvailability.setUnitType("Availability"));
  ASSERT_TRUE(continuousAvailability.setLowerLimitValue(0.0));
  ASSERT_TRUE(continuousAvailability.setUpperLimitValue(1.0));
  ASSERT_TRUE(incompatibleAvailability.setScheduleTypeLimits(continuousAvailability));
  EXPECT_FALSE(controller.setCarbonDioxideControlAvailabilitySchedule(incompatibleAvailability));
  ASSERT_TRUE(controller.carbonDioxideControlAvailabilitySchedule());
  EXPECT_EQ(acceptedAvailability.handle(), controller.carbonDioxideControlAvailabilitySchedule()->handle());

  ScheduleConstant incompatibleSetpoint(model);
  ScheduleTypeLimits temperatureLimits(model);
  ASSERT_TRUE(temperatureLimits.setNumericType("Continuous"));
  ASSERT_TRUE(temperatureLimits.setUnitType("Temperature"));
  ASSERT_TRUE(temperatureLimits.setLowerLimitValue(0.0));
  ASSERT_TRUE(incompatibleSetpoint.setScheduleTypeLimits(temperatureLimits));
  EXPECT_FALSE(controller.setGenericContaminantSetpointSchedule(incompatibleSetpoint));
  ASSERT_TRUE(controller.genericContaminantSetpointSchedule());
  EXPECT_EQ(acceptedSetpoint.handle(), controller.genericContaminantSetpointSchedule()->handle());

  Model foreignModel;
  ScheduleConstant foreign(foreignModel);
  EXPECT_FALSE(controller.setGenericContaminantSetpointSchedule(foreign));
  ASSERT_TRUE(controller.genericContaminantSetpointSchedule());
  EXPECT_EQ(acceptedSetpoint.handle(), controller.genericContaminantSetpointSchedule()->handle());

  ZoneControlContaminantController malformed(model);
  auto workspaceImpl = malformed.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(workspaceImpl);
  constexpr auto field = openstudio::ZoneControl_ContaminantControllerFields::GenericContaminantSetpointScheduleName;

  // This unresolved raw field represents imported malformed state that validated public setters cannot create.
  ASSERT_TRUE(workspaceImpl->setPointer(field, openstudio::Handle(), false));
  ASSERT_TRUE(workspaceImpl->openstudio::detail::IdfObject_Impl::setString(field, "Missing Generic Contaminant Schedule", false));
  EXPECT_FALSE(malformed.genericContaminantSetpointSchedule());
  EXPECT_EQ("Missing Generic Contaminant Schedule", workspaceImpl->openstudio::detail::IdfObject_Impl::getString(field, false, true).value_or(""));
  EXPECT_FALSE(malformed.setGenericContaminantSetpointSchedule(foreign));
  EXPECT_EQ("Missing Generic Contaminant Schedule", workspaceImpl->openstudio::detail::IdfObject_Impl::getString(field, false, true).value_or(""));

  malformed.resetGenericContaminantSetpointSchedule();
  EXPECT_FALSE(malformed.genericContaminantSetpointSchedule());
  EXPECT_EQ("", workspaceImpl->openstudio::detail::IdfObject_Impl::getString(field, false, true).value_or(""));
}

TEST_F(EPModelFixture, ZoneControlContaminantController_ReloadMutationAndRemoval) {
  const auto firstIdfPath = uniqueContaminantControllerIdfPath("epmodel-contaminant-controller-first");
  const auto secondIdfPath = uniqueContaminantControllerIdfPath("epmodel-contaminant-controller-second");
  const ScopedContaminantControllerFileRemoval removeFirstIdf(firstIdfPath);
  const ScopedContaminantControllerFileRemoval removeSecondIdf(secondIdfPath);

  Model model;
  ThermalZone zone(model);
  ZoneControlContaminantController controller(model);
  ScheduleConstant carbonDioxideAvailability(model);
  ScheduleConstant carbonDioxideSetpoint(model);
  ScheduleConstant minimumCarbonDioxide(model);
  ScheduleConstant genericAvailability(model);
  ScheduleConstant genericSetpoint(model);
  ASSERT_TRUE(zone.setName("Contaminant Controller Zone"));
  ASSERT_TRUE(controller.setName("Reload Contaminant Controller"));
  ASSERT_TRUE(carbonDioxideAvailability.setName("Carbon Dioxide Availability"));
  ASSERT_TRUE(carbonDioxideSetpoint.setName("Initial Carbon Dioxide Setpoint"));
  ASSERT_TRUE(minimumCarbonDioxide.setName("Minimum Carbon Dioxide"));
  ASSERT_TRUE(genericAvailability.setName("Generic Contaminant Availability"));
  ASSERT_TRUE(genericSetpoint.setName("Generic Contaminant Setpoint"));
  ASSERT_TRUE(carbonDioxideAvailability.setValue(1.0));
  ASSERT_TRUE(carbonDioxideSetpoint.setValue(1000.0));
  ASSERT_TRUE(minimumCarbonDioxide.setValue(400.0));
  ASSERT_TRUE(genericAvailability.setValue(1.0));
  ASSERT_TRUE(genericSetpoint.setValue(500.0));
  ASSERT_TRUE(controller.setCarbonDioxideControlAvailabilitySchedule(carbonDioxideAvailability));
  ASSERT_TRUE(controller.setCarbonDioxideSetpointSchedule(carbonDioxideSetpoint));
  ASSERT_TRUE(controller.setMinimumCarbonDioxideConcentrationSchedule(minimumCarbonDioxide));
  ASSERT_TRUE(controller.setGenericContaminantControlAvailabilitySchedule(genericAvailability));
  ASSERT_TRUE(controller.setGenericContaminantSetpointSchedule(genericSetpoint));
  ASSERT_TRUE(zone.setZoneControlContaminantController(controller));
  ASSERT_TRUE(model.save(firstIdfPath, true));

  auto loadedModel = Model::load(firstIdfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedZone = loadedModel->getConcreteModelObjectByName<ThermalZone>("Contaminant Controller Zone");
  auto loadedController = loadedModel->getConcreteModelObjectByName<ZoneControlContaminantController>("Reload Contaminant Controller");
  ASSERT_TRUE(loadedZone);
  ASSERT_TRUE(loadedController);
  ASSERT_TRUE(loadedController->controlledZone());
  EXPECT_EQ(loadedZone->handle(), loadedController->controlledZone()->handle());
  ASSERT_TRUE(loadedController->carbonDioxideControlAvailabilitySchedule());
  ASSERT_TRUE(loadedController->carbonDioxideSetpointSchedule());
  ASSERT_TRUE(loadedController->minimumCarbonDioxideConcentrationSchedule());
  ASSERT_TRUE(loadedController->genericContaminantControlAvailabilitySchedule());
  ASSERT_TRUE(loadedController->genericContaminantSetpointSchedule());
  EXPECT_EQ("Carbon Dioxide Availability", loadedController->carbonDioxideControlAvailabilitySchedule()->nameString());
  EXPECT_EQ("Initial Carbon Dioxide Setpoint", loadedController->carbonDioxideSetpointSchedule()->nameString());
  EXPECT_EQ("Minimum Carbon Dioxide", loadedController->minimumCarbonDioxideConcentrationSchedule()->nameString());
  EXPECT_EQ("Generic Contaminant Availability", loadedController->genericContaminantControlAvailabilitySchedule()->nameString());
  EXPECT_EQ("Generic Contaminant Setpoint", loadedController->genericContaminantSetpointSchedule()->nameString());

  ScheduleConstant replacementSetpoint(*loadedModel);
  ASSERT_TRUE(replacementSetpoint.setName("Replacement Carbon Dioxide Setpoint"));
  ASSERT_TRUE(replacementSetpoint.setValue(950.0));
  ASSERT_TRUE(loadedController->setCarbonDioxideSetpointSchedule(replacementSetpoint));
  loadedController->resetMinimumCarbonDioxideConcentrationSchedule();
  ASSERT_TRUE(loadedModel->save(secondIdfPath, true));

  auto reloadedModel = Model::load(secondIdfPath);
  ASSERT_TRUE(reloadedModel);
  auto reloadedZone = reloadedModel->getConcreteModelObjectByName<ThermalZone>("Contaminant Controller Zone");
  auto reloadedController = reloadedModel->getConcreteModelObjectByName<ZoneControlContaminantController>("Reload Contaminant Controller");
  ASSERT_TRUE(reloadedZone);
  ASSERT_TRUE(reloadedController);
  ASSERT_TRUE(reloadedController->controlledZone());
  EXPECT_EQ(reloadedZone->handle(), reloadedController->controlledZone()->handle());
  ASSERT_TRUE(reloadedZone->zoneControlContaminantController());
  EXPECT_EQ(reloadedController->handle(), reloadedZone->zoneControlContaminantController()->handle());
  ASSERT_TRUE(reloadedController->carbonDioxideSetpointSchedule());
  EXPECT_EQ("Replacement Carbon Dioxide Setpoint", reloadedController->carbonDioxideSetpointSchedule()->nameString());
  EXPECT_FALSE(reloadedController->minimumCarbonDioxideConcentrationSchedule());
  ASSERT_TRUE(reloadedController->carbonDioxideControlAvailabilitySchedule());
  ASSERT_TRUE(reloadedController->genericContaminantControlAvailabilitySchedule());
  ASSERT_TRUE(reloadedController->genericContaminantSetpointSchedule());

  const auto retainedScheduleNames = {"Carbon Dioxide Availability",      "Initial Carbon Dioxide Setpoint", "Minimum Carbon Dioxide",
                                      "Generic Contaminant Availability", "Generic Contaminant Setpoint",    "Replacement Carbon Dioxide Setpoint"};
  EXPECT_FALSE(reloadedController->remove().empty());
  EXPECT_FALSE(reloadedZone->zoneControlContaminantController());
  EXPECT_TRUE(reloadedModel->getObject(reloadedZone->handle()));
  for (const auto* scheduleName : retainedScheduleNames) {
    EXPECT_TRUE(reloadedModel->getConcreteModelObjectByName<ScheduleConstant>(scheduleName));
  }
}
