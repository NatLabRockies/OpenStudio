/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <algorithm>
#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/AirflowNetworkMultiZoneExternalNode.hpp"
using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AirflowNetworkMultiZoneExternalNode_DefaultConstructor) {
  Model model;
  AirflowNetworkMultiZoneExternalNode externalNode(model);
  EXPECT_EQ(AirflowNetworkMultiZoneExternalNode::iddObjectType(), externalNode.iddObject().type());
}

TEST_F(EPModelFixture, AirflowNetworkMultiZoneExternalNode_ScalarAccessors_RoundTrip) {
  Model model;
  AirflowNetworkMultiZoneExternalNode externalNode(model);

  EXPECT_TRUE(externalNode.isExternalNodeHeightDefaulted());
  EXPECT_DOUBLE_EQ(0.0, externalNode.externalNodeHeight());
  EXPECT_TRUE(externalNode.setExternalNodeHeight(12.5));
  EXPECT_DOUBLE_EQ(12.5, externalNode.externalNodeHeight());
  EXPECT_FALSE(externalNode.isExternalNodeHeightDefaulted());
  externalNode.resetExternalNodeHeight();
  EXPECT_TRUE(externalNode.isExternalNodeHeightDefaulted());
  EXPECT_DOUBLE_EQ(0.0, externalNode.externalNodeHeight());

  EXPECT_TRUE(externalNode.isSymmetricWindPressureCoefficientCurveDefaulted());
  EXPECT_FALSE(externalNode.symmetricWindPressureCoefficientCurve());
  EXPECT_TRUE(externalNode.setSymmetricWindPressureCoefficientCurve(true));
  EXPECT_TRUE(externalNode.symmetricWindPressureCoefficientCurve());
  EXPECT_FALSE(externalNode.isSymmetricWindPressureCoefficientCurveDefaulted());
  externalNode.resetSymmetricWindPressureCoefficientCurve();
  EXPECT_TRUE(externalNode.isSymmetricWindPressureCoefficientCurveDefaulted());
  EXPECT_FALSE(externalNode.symmetricWindPressureCoefficientCurve());

  const auto angleTypeValues = AirflowNetworkMultiZoneExternalNode::windAngleTypeValues();
  EXPECT_FALSE(angleTypeValues.empty());
  EXPECT_NE(std::find(angleTypeValues.begin(), angleTypeValues.end(), "Absolute"), angleTypeValues.end());
  EXPECT_NE(std::find(angleTypeValues.begin(), angleTypeValues.end(), "Relative"), angleTypeValues.end());

  EXPECT_TRUE(externalNode.isWindAngleTypeDefaulted());
  EXPECT_EQ("Absolute", externalNode.windAngleType());
  EXPECT_TRUE(externalNode.setWindAngleType("Relative"));
  EXPECT_EQ("Relative", externalNode.windAngleType());
  EXPECT_FALSE(externalNode.isWindAngleTypeDefaulted());
  externalNode.resetWindAngleType();
  EXPECT_TRUE(externalNode.isWindAngleTypeDefaulted());
  EXPECT_EQ("Absolute", externalNode.windAngleType());
}
