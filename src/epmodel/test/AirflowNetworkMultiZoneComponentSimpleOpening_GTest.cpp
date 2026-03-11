/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/AirflowNetworkMultiZoneComponentSimpleOpening.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AirflowNetworkMultiZoneComponentSimpleOpening_DefaultConstructor) {
  Model model;
  AirflowNetworkMultiZoneComponentSimpleOpening opening(model);
  EXPECT_EQ(AirflowNetworkMultiZoneComponentSimpleOpening::iddObjectType(), opening.iddObject().type());
}

TEST_F(EPModelFixture, AirflowNetworkMultiZoneComponentSimpleOpening_ScalarAccessors_RoundTrip) {
  Model model;
  AirflowNetworkMultiZoneComponentSimpleOpening opening(model);

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

  EXPECT_TRUE(opening.setMinimumDensityDifferenceforTwoWayFlow(0.12));
  EXPECT_DOUBLE_EQ(0.12, opening.minimumDensityDifferenceforTwoWayFlow());

  EXPECT_TRUE(opening.setDischargeCoefficient(0.52));
  EXPECT_DOUBLE_EQ(0.52, opening.dischargeCoefficient());
}
