/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/PythonPluginOutputVariable.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, PythonPluginOutputVariable_DefaultConstructor) {
  Model model;
  PythonPluginOutputVariable outVar(model);
  EXPECT_EQ(PythonPluginOutputVariable::iddObjectType(), outVar.iddObject().type());
  EXPECT_TRUE(outVar.typeofDatainVariable().empty());
  EXPECT_TRUE(outVar.updateFrequency().empty());
}

TEST_F(EPModelFixture, PythonPluginOutputVariable_ScalarAccessors_RoundTrip) {
  Model model;
  PythonPluginOutputVariable outVar(model);

  EXPECT_TRUE(outVar.setTypeofDatainVariable("Summed"));
  EXPECT_EQ("Summed", outVar.typeofDatainVariable());

  EXPECT_TRUE(outVar.setUpdateFrequency("SystemTimestep"));
  EXPECT_EQ("SystemTimestep", outVar.updateFrequency());

  EXPECT_TRUE(outVar.setUnits("m3/s"));
  ASSERT_TRUE(outVar.units());
  EXPECT_EQ("m3/s", outVar.units().get());
  outVar.resetUnits();
  ASSERT_TRUE(outVar.units());
  EXPECT_TRUE(outVar.units()->empty());

  EXPECT_TRUE(outVar.setResourceType("Electricity"));
  ASSERT_TRUE(outVar.resourceType());
  EXPECT_EQ("Electricity", outVar.resourceType().get());
  outVar.resetResourceType();
  ASSERT_TRUE(outVar.resourceType());
  EXPECT_TRUE(outVar.resourceType()->empty());

  EXPECT_TRUE(outVar.setGroupType("HVAC"));
  ASSERT_TRUE(outVar.groupType());
  EXPECT_EQ("HVAC", outVar.groupType().get());
  outVar.resetGroupType();
  ASSERT_TRUE(outVar.groupType());
  EXPECT_TRUE(outVar.groupType()->empty());

  EXPECT_TRUE(outVar.setEndUseCategory("Cooling"));
  ASSERT_TRUE(outVar.endUseCategory());
  EXPECT_EQ("Cooling", outVar.endUseCategory().get());
  outVar.resetEndUseCategory();
  ASSERT_TRUE(outVar.endUseCategory());
  EXPECT_TRUE(outVar.endUseCategory()->empty());

  EXPECT_TRUE(outVar.setEndUseSubcategory("CustomMeter"));
  ASSERT_TRUE(outVar.endUseSubcategory());
  EXPECT_EQ("CustomMeter", outVar.endUseSubcategory().get());
  outVar.resetEndUseSubcategory();
  ASSERT_TRUE(outVar.endUseSubcategory());
  EXPECT_TRUE(outVar.endUseSubcategory()->empty());
}
