/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/ZoneThermalChimney.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ZoneThermalChimney_DefaultConstructor) {
  Model model;
  ZoneThermalChimney chimney(model);

  EXPECT_EQ(ZoneThermalChimney::iddObjectType(), chimney.iddObject().type());
  EXPECT_DOUBLE_EQ(0.0, chimney.widthOfTheAbsorberWall());
  EXPECT_DOUBLE_EQ(0.0, chimney.crossSectionalAreaOfAirChannelOutlet());
  EXPECT_DOUBLE_EQ(0.8, chimney.dischargeCoefficient());
  EXPECT_TRUE(chimney.isDischargeCoefficientDefaulted());
}

TEST_F(EPModelFixture, ZoneThermalChimney_ScalarAccessors_RoundTrip) {
  Model model;
  ZoneThermalChimney chimney(model);

  EXPECT_FALSE(chimney.setWidthOfTheAbsorberWall(-0.1));
  EXPECT_FALSE(chimney.setCrossSectionalAreaOfAirChannelOutlet(-1.0));
  EXPECT_FALSE(chimney.setDischargeCoefficient(-0.1));
  EXPECT_FALSE(chimney.setDischargeCoefficient(1.1));

  EXPECT_TRUE(chimney.setWidthOfTheAbsorberWall(0.85));
  EXPECT_TRUE(chimney.setCrossSectionalAreaOfAirChannelOutlet(0.12));
  EXPECT_TRUE(chimney.setDischargeCoefficient(0.65));

  EXPECT_DOUBLE_EQ(0.85, chimney.widthOfTheAbsorberWall());
  EXPECT_DOUBLE_EQ(0.12, chimney.crossSectionalAreaOfAirChannelOutlet());
  EXPECT_DOUBLE_EQ(0.65, chimney.dischargeCoefficient());
  EXPECT_FALSE(chimney.isDischargeCoefficientDefaulted());

  chimney.resetDischargeCoefficient();
  EXPECT_TRUE(chimney.isDischargeCoefficientDefaulted());
  EXPECT_DOUBLE_EQ(0.8, chimney.dischargeCoefficient());
}
