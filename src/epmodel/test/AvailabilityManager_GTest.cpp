/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"

#include "../AirLoopHVAC.hpp"
#include "../AvailabilityManagerAssignmentList.hpp"
#include "../AvailabilityManagerNightCycle.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AvailabilityManagerNightCycle_DefaultConstructor) {
  Model model;
  AvailabilityManagerNightCycle availabilityManager(model);
  EXPECT_EQ(AvailabilityManagerNightCycle::iddObjectType(), availabilityManager.iddObject().type());
  EXPECT_FALSE(availabilityManager.nameString().empty());
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
