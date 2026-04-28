/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/ComplianceBuilding.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ComplianceBuilding_DefaultConstructor) {
  Model model;
  ComplianceBuilding complianceBuilding(model);
  EXPECT_EQ(ComplianceBuilding::iddObjectType(), complianceBuilding.iddObject().type());
}

TEST_F(EPModelFixture, ComplianceBuilding_ScalarAccessors_RoundTrip) {
  Model model;
  ComplianceBuilding complianceBuilding(model);

  EXPECT_TRUE(complianceBuilding.isBuildingRotationforAppendixGDefaulted());

  EXPECT_TRUE(complianceBuilding.setBuildingRotationforAppendixG(90.0));
  EXPECT_DOUBLE_EQ(90.0, complianceBuilding.buildingRotationforAppendixG());
  EXPECT_FALSE(complianceBuilding.isBuildingRotationforAppendixGDefaulted());

  complianceBuilding.resetBuildingRotationforAppendixG();
  EXPECT_TRUE(complianceBuilding.isBuildingRotationforAppendixGDefaulted());
  EXPECT_DOUBLE_EQ(0.0, complianceBuilding.buildingRotationforAppendixG());
}
