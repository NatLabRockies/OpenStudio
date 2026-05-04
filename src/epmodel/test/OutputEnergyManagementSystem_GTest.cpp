/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"

#include "../ModelObject/OutputEnergyManagementSystem.hpp"
#include "../ModelObject/OutputEnergyManagementSystem_Impl.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, OutputEnergyManagementSystem_DefaultConstructor) {
  Model model;
  auto outputEnergyManagementSystem = model.getUniqueModelObject<OutputEnergyManagementSystem>();

  EXPECT_EQ(OutputEnergyManagementSystem::iddObjectType(), outputEnergyManagementSystem.iddObject().type());
  EXPECT_TRUE(outputEnergyManagementSystem.isActuatorAvailabilityDictionaryReportingDefaulted());
  EXPECT_TRUE(outputEnergyManagementSystem.isInternalVariableAvailabilityDictionaryReportingDefaulted());
  EXPECT_TRUE(outputEnergyManagementSystem.isEMSRuntimeLanguageDebugOutputLevelDefaulted());
}

TEST_F(EPModelFixture, OutputEnergyManagementSystem_ScalarAccessors_RoundTrip) {
  Model model;
  auto outputEnergyManagementSystem = model.getUniqueModelObject<OutputEnergyManagementSystem>();

  EXPECT_FALSE(OutputEnergyManagementSystem::actuatorAvailabilityDictionaryReportingValues().empty());
  EXPECT_FALSE(OutputEnergyManagementSystem::internalVariableAvailabilityDictionaryReportingValues().empty());
  EXPECT_FALSE(OutputEnergyManagementSystem::eMSRuntimeLanguageDebugOutputLevelValues().empty());

  EXPECT_TRUE(outputEnergyManagementSystem.setActuatorAvailabilityDictionaryReporting("NotByUniqueKeyNames"));
  EXPECT_EQ("NotByUniqueKeyNames", outputEnergyManagementSystem.actuatorAvailabilityDictionaryReporting());
  EXPECT_FALSE(outputEnergyManagementSystem.isActuatorAvailabilityDictionaryReportingDefaulted());

  EXPECT_TRUE(outputEnergyManagementSystem.setInternalVariableAvailabilityDictionaryReporting("Verbose"));
  EXPECT_EQ("Verbose", outputEnergyManagementSystem.internalVariableAvailabilityDictionaryReporting());
  EXPECT_FALSE(outputEnergyManagementSystem.isInternalVariableAvailabilityDictionaryReportingDefaulted());

  EXPECT_TRUE(outputEnergyManagementSystem.setEMSRuntimeLanguageDebugOutputLevel("Verbose"));
  EXPECT_EQ("Verbose", outputEnergyManagementSystem.eMSRuntimeLanguageDebugOutputLevel());
  EXPECT_FALSE(outputEnergyManagementSystem.isEMSRuntimeLanguageDebugOutputLevelDefaulted());

  outputEnergyManagementSystem.resetActuatorAvailabilityDictionaryReporting();
  outputEnergyManagementSystem.resetInternalVariableAvailabilityDictionaryReporting();
  outputEnergyManagementSystem.resetEMSRuntimeLanguageDebugOutputLevel();

  EXPECT_TRUE(outputEnergyManagementSystem.isActuatorAvailabilityDictionaryReportingDefaulted());
  EXPECT_TRUE(outputEnergyManagementSystem.isInternalVariableAvailabilityDictionaryReportingDefaulted());
  EXPECT_TRUE(outputEnergyManagementSystem.isEMSRuntimeLanguageDebugOutputLevelDefaulted());
}
