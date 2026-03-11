/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/AirflowNetworkMultiZoneSurfaceCrack.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AirflowNetworkMultiZoneSurfaceCrack_DefaultConstructor) {
  Model model;
  AirflowNetworkMultiZoneSurfaceCrack surfaceCrack(model);
  EXPECT_EQ(AirflowNetworkMultiZoneSurfaceCrack::iddObjectType(), surfaceCrack.iddObject().type());
}

TEST_F(EPModelFixture, AirflowNetworkMultiZoneSurfaceCrack_ScalarAccessors_RoundTrip) {
  Model model;
  AirflowNetworkMultiZoneSurfaceCrack surfaceCrack(model);

  EXPECT_TRUE(surfaceCrack.setAirMassFlowCoefficientatReferenceConditions(0.0011));
  EXPECT_DOUBLE_EQ(0.0011, surfaceCrack.airMassFlowCoefficientatReferenceConditions());

  EXPECT_TRUE(surfaceCrack.isAirMassFlowExponentDefaulted());
  EXPECT_DOUBLE_EQ(0.65, surfaceCrack.airMassFlowExponent());

  EXPECT_TRUE(surfaceCrack.setAirMassFlowExponent(0.72));
  EXPECT_DOUBLE_EQ(0.72, surfaceCrack.airMassFlowExponent());
  EXPECT_FALSE(surfaceCrack.isAirMassFlowExponentDefaulted());

  surfaceCrack.resetAirMassFlowExponent();
  EXPECT_TRUE(surfaceCrack.isAirMassFlowExponentDefaulted());
  EXPECT_DOUBLE_EQ(0.65, surfaceCrack.airMassFlowExponent());
}
