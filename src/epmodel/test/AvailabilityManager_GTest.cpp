/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"

#include "../Loop/AirLoopHVAC.hpp"
#include "../AvailabilityManagerAssignmentList.hpp"
#include "../AvailabilityManager/AvailabilityManagerNightCycle.hpp"
#include "../AvailabilityManager/AvailabilityManagerNightVentilation.hpp"

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

  ASSERT_TRUE(airLoop.addAvailabilityManager(availabilityManager1));
  auto managers = airLoop.availabilityManagers();
  ASSERT_EQ(1u, managers.size());
  EXPECT_EQ(availabilityManager1, managers.front());
  EXPECT_EQ(1u, airLoop.availabilityManagerPriority(availabilityManager1));

  ASSERT_TRUE(airLoop.addAvailabilityManager(availabilityManager2, 1u));
  managers = airLoop.availabilityManagers();
  ASSERT_EQ(2u, managers.size());
  EXPECT_EQ(availabilityManager2, managers[0]);
  EXPECT_EQ(availabilityManager1, managers[1]);
  EXPECT_EQ(1u, airLoop.availabilityManagerPriority(availabilityManager2));
  EXPECT_EQ(2u, airLoop.availabilityManagerPriority(availabilityManager1));

  ASSERT_TRUE(airLoop.setAvailabilityManagerPriority(availabilityManager1, 1u));
  managers = airLoop.availabilityManagers();
  ASSERT_EQ(2u, managers.size());
  EXPECT_EQ(availabilityManager1, managers[0]);
  EXPECT_EQ(availabilityManager2, managers[1]);

  ASSERT_TRUE(availabilityManager1.loop());
  auto owningAirLoop = availabilityManager1.airLoopHVAC();
  ASSERT_TRUE(owningAirLoop);
  EXPECT_EQ(airLoop, *owningAirLoop);

  ASSERT_TRUE(airLoop.removeAvailabilityManager(availabilityManager2));
  managers = airLoop.availabilityManagers();
  ASSERT_EQ(1u, managers.size());
  EXPECT_EQ(availabilityManager1, managers.front());

  ASSERT_TRUE(airLoop.removeAvailabilityManager(1u));
  EXPECT_TRUE(airLoop.availabilityManagers().empty());

  ASSERT_TRUE(airLoop.setAvailabilityManagers({availabilityManager2, availabilityManager1}));
  managers = airLoop.availabilityManagers();
  ASSERT_EQ(2u, managers.size());
  EXPECT_EQ(availabilityManager2, managers[0]);
  EXPECT_EQ(availabilityManager1, managers[1]);

  airLoop.resetAvailabilityManagers();
  EXPECT_TRUE(airLoop.availabilityManagers().empty());
}
