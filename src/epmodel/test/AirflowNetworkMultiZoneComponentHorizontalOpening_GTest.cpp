/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/AirflowNetworkMultiZoneComponentHorizontalOpening.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AirflowNetworkMultiZoneComponentHorizontalOpening_DefaultConstructor) {
  Model model;
  AirflowNetworkMultiZoneComponentHorizontalOpening opening(model);
  EXPECT_EQ(AirflowNetworkMultiZoneComponentHorizontalOpening::iddObjectType(), opening.iddObject().type());
}

TEST_F(EPModelFixture, AirflowNetworkMultiZoneComponentHorizontalOpening_ScalarAccessors_RoundTrip) {
  Model model;
  AirflowNetworkMultiZoneComponentHorizontalOpening opening(model);

  EXPECT_TRUE(opening.setAirMassFlowCoefficientWhenOpeningisClosed(0.0025));
  EXPECT_DOUBLE_EQ(0.0025, opening.airMassFlowCoefficientWhenOpeningisClosed());

  EXPECT_TRUE(opening.isAirMassFlowExponentWhenOpeningisClosedDefaulted());
  EXPECT_DOUBLE_EQ(0.65, opening.airMassFlowExponentWhenOpeningisClosed());
  EXPECT_TRUE(opening.setAirMassFlowExponentWhenOpeningisClosed(0.8));
  EXPECT_DOUBLE_EQ(0.8, opening.airMassFlowExponentWhenOpeningisClosed());
  EXPECT_FALSE(opening.isAirMassFlowExponentWhenOpeningisClosedDefaulted());
  opening.resetAirMassFlowExponentWhenOpeningisClosed();
  EXPECT_TRUE(opening.isAirMassFlowExponentWhenOpeningisClosedDefaulted());
  EXPECT_DOUBLE_EQ(0.65, opening.airMassFlowExponentWhenOpeningisClosed());

  EXPECT_TRUE(opening.isSlopingPlaneAngleDefaulted());
  EXPECT_DOUBLE_EQ(90.0, opening.slopingPlaneAngle());
  EXPECT_TRUE(opening.setSlopingPlaneAngle(45.0));
  EXPECT_DOUBLE_EQ(45.0, opening.slopingPlaneAngle());
  EXPECT_FALSE(opening.isSlopingPlaneAngleDefaulted());
  opening.resetSlopingPlaneAngle();
  EXPECT_TRUE(opening.isSlopingPlaneAngleDefaulted());
  EXPECT_DOUBLE_EQ(90.0, opening.slopingPlaneAngle());

  EXPECT_TRUE(opening.setDischargeCoefficient(0.52));
  EXPECT_DOUBLE_EQ(0.52, opening.dischargeCoefficient());
}
