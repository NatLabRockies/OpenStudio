/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/EnergyManagementSystemInternalVariable.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, EnergyManagementSystemInternalVariable_DefaultConstructor) {
  Model model;
  EnergyManagementSystemInternalVariable emsInternalVariable(model, "Zone Air Volume");
  EXPECT_EQ(EnergyManagementSystemInternalVariable::iddObjectType(), emsInternalVariable.iddObject().type());
  EXPECT_EQ("Zone Air Volume", emsInternalVariable.internalDataType());
  EXPECT_TRUE(emsInternalVariable.internalDataIndexKeyName().empty());
}

TEST_F(EPModelFixture, EnergyManagementSystemInternalVariable_ScalarAccessors_RoundTrip) {
  Model model;
  EnergyManagementSystemInternalVariable emsInternalVariable(model, "Zone Air Volume");

  EXPECT_TRUE(emsInternalVariable.setInternalDataIndexKeyName("SPACE 1-1"));
  EXPECT_EQ("SPACE 1-1", emsInternalVariable.internalDataIndexKeyName());

  emsInternalVariable.resetInternalDataIndexKeyName();
  EXPECT_TRUE(emsInternalVariable.internalDataIndexKeyName().empty());

  EXPECT_TRUE(emsInternalVariable.setInternalDataType("Zone Floor Area"));
  EXPECT_EQ("Zone Floor Area", emsInternalVariable.internalDataType());
}
