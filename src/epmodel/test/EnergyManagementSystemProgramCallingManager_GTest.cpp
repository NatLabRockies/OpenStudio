/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/EnergyManagementSystemProgramCallingManager.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, EnergyManagementSystemProgramCallingManager_DefaultConstructor) {
  Model model;
  EnergyManagementSystemProgramCallingManager emsProgramCallingManager(model);

  EXPECT_EQ(EnergyManagementSystemProgramCallingManager::iddObjectType(), emsProgramCallingManager.iddObject().type());
  EXPECT_EQ("BeginNewEnvironment", emsProgramCallingManager.callingPoint());
}

TEST_F(EPModelFixture, EnergyManagementSystemProgramCallingManager_ScalarAccessors_RoundTrip) {
  Model model;
  EnergyManagementSystemProgramCallingManager emsProgramCallingManager(model);

  EXPECT_FALSE(EnergyManagementSystemProgramCallingManager::validCallingPointValues().empty());

  EXPECT_TRUE(emsProgramCallingManager.setCallingPoint("BeginZoneTimestepBeforeSetCurrentWeather"));
  EXPECT_EQ("BeginZoneTimestepBeforeSetCurrentWeather", emsProgramCallingManager.callingPoint());
}
