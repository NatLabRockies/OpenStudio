/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/AirflowNetworkDistributionDuctViewFactors.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AirflowNetworkDistributionDuctViewFactors_DefaultConstructor) {
  Model model;
  AirflowNetworkDistributionDuctViewFactors ductViewFactors(model);
  EXPECT_EQ(AirflowNetworkDistributionDuctViewFactors::iddObjectType(), ductViewFactors.iddObject().type());
}

TEST_F(EPModelFixture, AirflowNetworkDistributionDuctViewFactors_ScalarAccessors_RoundTrip) {
  Model model;
  AirflowNetworkDistributionDuctViewFactors ductViewFactors(model);

  EXPECT_TRUE(ductViewFactors.isDuctSurfaceExposureFractionDefaulted());
  EXPECT_DOUBLE_EQ(0.0, ductViewFactors.ductSurfaceExposureFraction());
  EXPECT_TRUE(ductViewFactors.setDuctSurfaceExposureFraction(0.4));
  EXPECT_DOUBLE_EQ(0.4, ductViewFactors.ductSurfaceExposureFraction());
  EXPECT_FALSE(ductViewFactors.isDuctSurfaceExposureFractionDefaulted());
  EXPECT_FALSE(ductViewFactors.setDuctSurfaceExposureFraction(1.2));
  ductViewFactors.resetDuctSurfaceExposureFraction();
  EXPECT_TRUE(ductViewFactors.isDuctSurfaceExposureFractionDefaulted());
  EXPECT_DOUBLE_EQ(0.0, ductViewFactors.ductSurfaceExposureFraction());

  EXPECT_TRUE(ductViewFactors.isDuctSurfaceEmittanceDefaulted());
  EXPECT_DOUBLE_EQ(0.9, ductViewFactors.ductSurfaceEmittance());
  EXPECT_TRUE(ductViewFactors.setDuctSurfaceEmittance(0.7));
  EXPECT_DOUBLE_EQ(0.7, ductViewFactors.ductSurfaceEmittance());
  EXPECT_FALSE(ductViewFactors.isDuctSurfaceEmittanceDefaulted());
  EXPECT_FALSE(ductViewFactors.setDuctSurfaceEmittance(-0.1));
  ductViewFactors.resetDuctSurfaceEmittance();
  EXPECT_TRUE(ductViewFactors.isDuctSurfaceEmittanceDefaulted());
  EXPECT_DOUBLE_EQ(0.9, ductViewFactors.ductSurfaceEmittance());
}
