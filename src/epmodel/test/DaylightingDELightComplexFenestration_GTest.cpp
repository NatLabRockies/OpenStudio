/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/DaylightingDELightComplexFenestration.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, DaylightingDELightComplexFenestration_DefaultConstructor) {
  Model model;
  DaylightingDELightComplexFenestration fenestration(model);
  EXPECT_EQ(DaylightingDELightComplexFenestration::iddObjectType(), fenestration.iddObject().type());
}

TEST_F(EPModelFixture, DaylightingDELightComplexFenestration_ScalarAccessors_RoundTrip) {
  Model model;
  DaylightingDELightComplexFenestration fenestration(model);

  EXPECT_TRUE(fenestration.setName("DELight CFS-1"));
  EXPECT_EQ("DELight CFS-1", fenestration.nameString());

  EXPECT_TRUE(fenestration.setComplexFenestrationType("MyBTDFType"));
  EXPECT_EQ("MyBTDFType", fenestration.complexFenestrationType());

  EXPECT_TRUE(fenestration.setFenestrationRotation(27.5));
  EXPECT_DOUBLE_EQ(27.5, fenestration.fenestrationRotation());
  EXPECT_FALSE(fenestration.isFenestrationRotationDefaulted());

  fenestration.resetFenestrationRotation();
  EXPECT_TRUE(fenestration.isFenestrationRotationDefaulted());
  EXPECT_DOUBLE_EQ(0.0, fenestration.fenestrationRotation());
}
