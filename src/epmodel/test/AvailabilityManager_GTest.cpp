/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"

#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../Loop/PlantLoop_Impl.hpp"
#include "../Model.hpp"
#include "../ModelObject/AvailabilityManagerAssignmentList.hpp"
#include "../ModelObject/AvailabilityManagerAssignmentList_Impl.hpp"
#include "../AvailabilityManager/AvailabilityManagerScheduledOn.hpp"
#include "../AvailabilityManager/AvailabilityManagerScheduledOn_Impl.hpp"
#include "../AvailabilityManager/AvailabilityManagerNightCycle.hpp"
#include "../AvailabilityManager/AvailabilityManagerNightVentilation.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Schedule/ScheduleConstant_Impl.hpp"

#include <utilities/core/Filesystem.hpp>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AvailabilityManagerNightCycle_DefaultConstructor) {
  Model model;
  AvailabilityManagerNightCycle availabilityManager(model);
  EXPECT_EQ(AvailabilityManagerNightCycle::iddObjectType(), availabilityManager.iddObject().type());
  EXPECT_FALSE(availabilityManager.nameString().empty());
}

TEST_F(EPModelFixture, AvailabilityManagerNightCycle_ScalarAccessors_RoundTrip) {
  Model model;
  AvailabilityManagerNightCycle availabilityManager(model);

  EXPECT_TRUE(availabilityManager.isControlTypeDefaulted());
  EXPECT_FALSE(availabilityManager.isThermostatToleranceDefaulted());
  EXPECT_FALSE(availabilityManager.isCyclingRunTimeDefaulted());
  EXPECT_TRUE(availabilityManager.isCyclingRunTimeControlTypeDefaulted());

  EXPECT_TRUE(availabilityManager.setControlType("CycleOnAnyHeatingZone"));
  EXPECT_EQ("CycleOnAnyHeatingZone", availabilityManager.controlType());
  EXPECT_TRUE(availabilityManager.setThermostatTolerance(1.25));
  EXPECT_DOUBLE_EQ(1.25, availabilityManager.thermostatTolerance());
  EXPECT_TRUE(availabilityManager.setCyclingRunTime(900.0));
  EXPECT_DOUBLE_EQ(900.0, availabilityManager.cyclingRunTime());
  EXPECT_TRUE(availabilityManager.setCyclingRunTimeControlType("Thermostat"));
  EXPECT_EQ("Thermostat", availabilityManager.cyclingRunTimeControlType());

  availabilityManager.resetControlType();
  availabilityManager.resetThermostatTolerance();
  availabilityManager.resetCyclingRunTime();
  availabilityManager.resetCyclingRunTimeControlType();
  EXPECT_TRUE(availabilityManager.isControlTypeDefaulted());
  EXPECT_TRUE(availabilityManager.isThermostatToleranceDefaulted());
  EXPECT_TRUE(availabilityManager.isCyclingRunTimeDefaulted());
  EXPECT_TRUE(availabilityManager.isCyclingRunTimeControlTypeDefaulted());
}

TEST_F(EPModelFixture, AvailabilityManagerNightVentilation_DefaultConstructor) {
  Model model;
  AvailabilityManagerNightVentilation availabilityManager(model);

  EXPECT_EQ(AvailabilityManagerNightVentilation::iddObjectType(), availabilityManager.iddObject().type());
  EXPECT_FALSE(availabilityManager.nameString().empty());
}

TEST_F(EPModelFixture, AvailabilityManagerNightVentilation_ScalarAccessors_RoundTrip) {
  Model model;
  AvailabilityManagerNightVentilation availabilityManager(model);

  EXPECT_DOUBLE_EQ(2.0, availabilityManager.ventilationTemperatureDifference());
  EXPECT_DOUBLE_EQ(15.0, availabilityManager.ventilationTemperatureLowLimit());
  EXPECT_DOUBLE_EQ(0.333, availabilityManager.nightVentingFlowFraction());

  EXPECT_TRUE(availabilityManager.setVentilationTemperatureDifference(3.5));
  EXPECT_DOUBLE_EQ(3.5, availabilityManager.ventilationTemperatureDifference());
  EXPECT_TRUE(availabilityManager.setVentilationTemperatureLowLimit(10.0));
  EXPECT_DOUBLE_EQ(10.0, availabilityManager.ventilationTemperatureLowLimit());
  EXPECT_TRUE(availabilityManager.setNightVentingFlowFraction(0.5));
  EXPECT_DOUBLE_EQ(0.5, availabilityManager.nightVentingFlowFraction());
}

TEST_F(EPModelFixture, AvailabilityManagerAssignmentList_DefaultConstructor) {
  Model model;
  AvailabilityManagerAssignmentList assignmentList(model);
  EXPECT_EQ(AvailabilityManagerAssignmentList::iddObjectType(), assignmentList.iddObject().type());
  EXPECT_TRUE(assignmentList.availabilityManagers().empty());
}

TEST_F(EPModelFixture, AirLoopHVAC_AvailabilityManagerApis) {
  Model model;
  AirLoopHVAC airLoop(model);
  AvailabilityManagerNightCycle availabilityManager1(model);
  AvailabilityManagerNightCycle availabilityManager2(model);

  auto managers = airLoop.availabilityManagers();
  ASSERT_EQ(1u, managers.size());
  auto scheduledOn = managers.front().optionalCast<AvailabilityManagerScheduledOn>();
  ASSERT_TRUE(scheduledOn);
  EXPECT_EQ(1u, airLoop.availabilityManagerPriority(*scheduledOn));

  ASSERT_TRUE(airLoop.addAvailabilityManager(availabilityManager1));
  managers = airLoop.availabilityManagers();
  ASSERT_EQ(2u, managers.size());
  EXPECT_EQ(2u, airLoop.availabilityManagerPriority(availabilityManager1));
  EXPECT_EQ(1u, airLoop.availabilityManagerPriority(*scheduledOn));

  ASSERT_TRUE(airLoop.addAvailabilityManager(availabilityManager2, 1u));
  managers = airLoop.availabilityManagers();
  ASSERT_EQ(3u, managers.size());
  EXPECT_EQ(availabilityManager2, managers[0]);
  EXPECT_EQ(1u, airLoop.availabilityManagerPriority(availabilityManager2));
  EXPECT_EQ(2u, airLoop.availabilityManagerPriority(*scheduledOn));
  EXPECT_EQ(3u, airLoop.availabilityManagerPriority(availabilityManager1));

  ASSERT_TRUE(airLoop.setAvailabilityManagerPriority(availabilityManager1, 1u));
  managers = airLoop.availabilityManagers();
  ASSERT_EQ(3u, managers.size());
  EXPECT_EQ(availabilityManager1, managers[0]);
  EXPECT_EQ(2u, airLoop.availabilityManagerPriority(availabilityManager2));
  EXPECT_EQ(3u, airLoop.availabilityManagerPriority(*scheduledOn));

  ASSERT_TRUE(availabilityManager1.loop());
  auto owningAirLoop = availabilityManager1.airLoopHVAC();
  ASSERT_TRUE(owningAirLoop);
  EXPECT_EQ(airLoop, *owningAirLoop);

  ASSERT_TRUE(airLoop.removeAvailabilityManager(availabilityManager2));
  managers = airLoop.availabilityManagers();
  ASSERT_EQ(2u, managers.size());
  EXPECT_EQ(availabilityManager1, managers.front());

  ASSERT_TRUE(airLoop.removeAvailabilityManager(1u));
  managers = airLoop.availabilityManagers();
  ASSERT_EQ(1u, managers.size());
  EXPECT_TRUE(managers.front().optionalCast<AvailabilityManagerScheduledOn>());

  ASSERT_TRUE(airLoop.setAvailabilityManagers({availabilityManager2, availabilityManager1}));
  managers = airLoop.availabilityManagers();
  ASSERT_EQ(3u, managers.size());
  EXPECT_EQ(availabilityManager2, managers[0]);
  EXPECT_EQ(availabilityManager1, managers[1]);
  EXPECT_TRUE(managers[2].optionalCast<AvailabilityManagerScheduledOn>());

  airLoop.resetAvailabilityManagers();
  managers = airLoop.availabilityManagers();
  ASSERT_EQ(1u, managers.size());
  EXPECT_TRUE(managers.front().optionalCast<AvailabilityManagerScheduledOn>());
}

TEST_F(EPModelFixture, PlantLoop_AvailabilityManagerAssignmentLifecycle) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-plant-availability-manager-lifecycle.idf");

  Model model;
  PlantLoop plantLoop(model);
  ScheduleConstant firstSchedule(model);
  ScheduleConstant secondSchedule(model);
  AvailabilityManagerScheduledOn firstManager(model);
  AvailabilityManagerScheduledOn secondManager(model);
  ASSERT_TRUE(plantLoop.setName("Availability Control Plant Loop"));
  ASSERT_TRUE(firstSchedule.setName("First Availability Schedule"));
  ASSERT_TRUE(secondSchedule.setName("Second Availability Schedule"));
  ASSERT_TRUE(firstManager.setName("First Plant Availability Manager"));
  ASSERT_TRUE(secondManager.setName("Second Plant Availability Manager"));
  ASSERT_TRUE(firstSchedule.setValue(1.0));
  ASSERT_TRUE(secondSchedule.setValue(0.5));
  ASSERT_TRUE(firstManager.setSchedule(firstSchedule));
  ASSERT_TRUE(secondManager.setSchedule(secondSchedule));

  ASSERT_TRUE(plantLoop.addAvailabilityManager(firstManager));
  ASSERT_TRUE(plantLoop.addAvailabilityManager(secondManager, 1u));
  ASSERT_EQ(2u, plantLoop.availabilityManagers().size());
  EXPECT_EQ(secondManager, plantLoop.availabilityManagers()[0]);
  EXPECT_EQ(firstManager, plantLoop.availabilityManagers()[1]);
  ASSERT_TRUE(plantLoop.setAvailabilityManagerPriority(firstManager, 1u));
  EXPECT_EQ(firstManager, plantLoop.availabilityManagers()[0]);
  EXPECT_EQ(secondManager, plantLoop.availabilityManagers()[1]);
  ASSERT_TRUE(firstManager.loop());
  ASSERT_TRUE(secondManager.loop());
  EXPECT_EQ(plantLoop.handle(), firstManager.loop()->handle());
  EXPECT_EQ(plantLoop.handle(), secondManager.loop()->handle());
  EXPECT_EQ(firstSchedule, firstManager.schedule());
  EXPECT_EQ(secondSchedule, secondManager.schedule());
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedPlantLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Availability Control Plant Loop");
  auto loadedFirstManager = loadedModel->getConcreteModelObjectByName<AvailabilityManagerScheduledOn>("First Plant Availability Manager");
  auto loadedSecondManager = loadedModel->getConcreteModelObjectByName<AvailabilityManagerScheduledOn>("Second Plant Availability Manager");
  auto loadedFirstSchedule = loadedModel->getConcreteModelObjectByName<ScheduleConstant>("First Availability Schedule");
  auto loadedSecondSchedule = loadedModel->getConcreteModelObjectByName<ScheduleConstant>("Second Availability Schedule");
  ASSERT_TRUE(loadedPlantLoop);
  ASSERT_TRUE(loadedFirstManager);
  ASSERT_TRUE(loadedSecondManager);
  ASSERT_TRUE(loadedFirstSchedule);
  ASSERT_TRUE(loadedSecondSchedule);

  ASSERT_EQ(2u, loadedPlantLoop->availabilityManagers().size());
  EXPECT_EQ(*loadedFirstManager, loadedPlantLoop->availabilityManagers()[0]);
  EXPECT_EQ(*loadedSecondManager, loadedPlantLoop->availabilityManagers()[1]);
  EXPECT_EQ(1u, loadedPlantLoop->availabilityManagerPriority(*loadedFirstManager));
  EXPECT_EQ(2u, loadedPlantLoop->availabilityManagerPriority(*loadedSecondManager));
  ASSERT_TRUE(loadedFirstManager->loop());
  ASSERT_TRUE(loadedSecondManager->loop());
  EXPECT_EQ(loadedPlantLoop->handle(), loadedFirstManager->loop()->handle());
  EXPECT_EQ(loadedPlantLoop->handle(), loadedSecondManager->loop()->handle());
  EXPECT_EQ(*loadedFirstSchedule, loadedFirstManager->schedule());
  EXPECT_EQ(*loadedSecondSchedule, loadedSecondManager->schedule());

  ASSERT_TRUE(loadedPlantLoop->setAvailabilityManagerPriority(*loadedSecondManager, 1u));
  EXPECT_EQ(*loadedSecondManager, loadedPlantLoop->availabilityManagers()[0]);
  EXPECT_EQ(*loadedFirstManager, loadedPlantLoop->availabilityManagers()[1]);
  ASSERT_TRUE(loadedPlantLoop->removeAvailabilityManager(*loadedSecondManager));
  ASSERT_EQ(1u, loadedPlantLoop->availabilityManagers().size());
  EXPECT_EQ(*loadedFirstManager, loadedPlantLoop->availabilityManagers().front());
  EXPECT_FALSE(loadedSecondManager->loop());
  EXPECT_TRUE(loadedModel->getObject(loadedSecondManager->handle()));
  EXPECT_TRUE(loadedModel->getObject(loadedSecondSchedule->handle()));

  ASSERT_TRUE(loadedPlantLoop->addAvailabilityManager(*loadedSecondManager, 1u));
  ASSERT_EQ(2u, loadedPlantLoop->availabilityManagers().size());
  EXPECT_EQ(*loadedSecondManager, loadedPlantLoop->availabilityManagers()[0]);
  EXPECT_EQ(*loadedFirstManager, loadedPlantLoop->availabilityManagers()[1]);

  const auto firstManagerHandle = loadedFirstManager->handle();
  const auto plantLoopHandle = loadedPlantLoop->handle();
  EXPECT_FALSE(loadedFirstManager->remove().empty());
  EXPECT_FALSE(loadedModel->getObject(firstManagerHandle));
  ASSERT_EQ(1u, loadedPlantLoop->availabilityManagers().size());
  EXPECT_EQ(*loadedSecondManager, loadedPlantLoop->availabilityManagers().front());
  ASSERT_TRUE(loadedSecondManager->loop());
  EXPECT_EQ(plantLoopHandle, loadedSecondManager->loop()->handle());

  loadedPlantLoop->resetAvailabilityManagers();
  EXPECT_TRUE(loadedPlantLoop->availabilityManagers().empty());
  EXPECT_FALSE(loadedSecondManager->loop());
  EXPECT_TRUE(loadedModel->getObject(loadedSecondManager->handle()));
  EXPECT_TRUE(loadedModel->getObject(loadedFirstSchedule->handle()));
  EXPECT_TRUE(loadedModel->getObject(loadedSecondSchedule->handle()));
  EXPECT_TRUE(loadedModel->getObject(plantLoopHandle));
  EXPECT_EQ(1u, loadedModel->getConcreteModelObjects<AvailabilityManagerAssignmentList>().size());

  openstudio::filesystem::remove(idfPath);
}
