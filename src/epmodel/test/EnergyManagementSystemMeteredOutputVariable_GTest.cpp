/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/EnergyManagementSystemMeteredOutputVariable.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, EnergyManagementSystemMeteredOutputVariable_DefaultConstructor) {
  Model model;
  EnergyManagementSystemMeteredOutputVariable emsMeteredOutputVariable(model, "Plant Heating Comp Electricity Consumption");

  EXPECT_EQ(EnergyManagementSystemMeteredOutputVariable::iddObjectType(), emsMeteredOutputVariable.iddObject().type());
  EXPECT_EQ("Plant Heating Comp Electricity Consumption", emsMeteredOutputVariable.emsVariableName());
  EXPECT_EQ("SystemTimestep", emsMeteredOutputVariable.updateFrequency());
  EXPECT_EQ("Electricity", emsMeteredOutputVariable.resourceType());
  EXPECT_EQ("Building", emsMeteredOutputVariable.groupType());
  EXPECT_EQ("Fans", emsMeteredOutputVariable.endUseCategory());
}

TEST_F(EPModelFixture, EnergyManagementSystemMeteredOutputVariable_ScalarAccessors_RoundTrip) {
  Model model;
  EnergyManagementSystemMeteredOutputVariable emsMeteredOutputVariable(model, "Plant Heating Comp Electricity Consumption");

  EXPECT_FALSE(EnergyManagementSystemMeteredOutputVariable::updateFrequencyValues().empty());
  EXPECT_FALSE(EnergyManagementSystemMeteredOutputVariable::resourceTypeValues().empty());
  EXPECT_FALSE(EnergyManagementSystemMeteredOutputVariable::groupTypeValues().empty());
  EXPECT_FALSE(EnergyManagementSystemMeteredOutputVariable::endUseCategoryValues().empty());

  EXPECT_TRUE(emsMeteredOutputVariable.setEMSVariableName("Plant Cooling Comp Electricity Consumption"));
  EXPECT_EQ("Plant Cooling Comp Electricity Consumption", emsMeteredOutputVariable.emsVariableName());

  EXPECT_TRUE(emsMeteredOutputVariable.setUpdateFrequency("ZoneTimestep"));
  EXPECT_EQ("ZoneTimestep", emsMeteredOutputVariable.updateFrequency());

  EXPECT_TRUE(emsMeteredOutputVariable.setResourceType("NaturalGas"));
  EXPECT_EQ("NaturalGas", emsMeteredOutputVariable.resourceType());

  EXPECT_TRUE(emsMeteredOutputVariable.setGroupType("HVAC"));
  EXPECT_EQ("HVAC", emsMeteredOutputVariable.groupType());

  EXPECT_TRUE(emsMeteredOutputVariable.setEndUseCategory("Heating"));
  EXPECT_EQ("Heating", emsMeteredOutputVariable.endUseCategory());

  EXPECT_TRUE(emsMeteredOutputVariable.setEndUseSubcategory("BoilerLoop"));
  EXPECT_EQ("BoilerLoop", emsMeteredOutputVariable.endUseSubcategory());

  emsMeteredOutputVariable.resetEndUseSubcategory();
  EXPECT_TRUE(emsMeteredOutputVariable.endUseSubcategory().empty());

  EXPECT_TRUE(emsMeteredOutputVariable.setUnits("J"));
  EXPECT_EQ("J", emsMeteredOutputVariable.units());

  emsMeteredOutputVariable.resetUnits();
  EXPECT_TRUE(emsMeteredOutputVariable.units().empty());
}
