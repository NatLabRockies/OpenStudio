/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/AirflowNetworkMultiZoneSurfaceEffectiveLeakageArea.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AirflowNetworkMultiZoneSurfaceEffectiveLeakageArea_DefaultConstructor) {
  Model model;
  AirflowNetworkMultiZoneSurfaceEffectiveLeakageArea effectiveLeakageArea(model);
  EXPECT_EQ(AirflowNetworkMultiZoneSurfaceEffectiveLeakageArea::iddObjectType(), effectiveLeakageArea.iddObject().type());
}

TEST_F(EPModelFixture, AirflowNetworkMultiZoneSurfaceEffectiveLeakageArea_ScalarAccessors_RoundTrip) {
  Model model;
  AirflowNetworkMultiZoneSurfaceEffectiveLeakageArea effectiveLeakageArea(model);

  EXPECT_TRUE(effectiveLeakageArea.setEffectiveLeakageArea(0.021));
  EXPECT_DOUBLE_EQ(0.021, effectiveLeakageArea.effectiveLeakageArea());

  EXPECT_TRUE(effectiveLeakageArea.isDischargeCoefficientDefaulted());
  EXPECT_DOUBLE_EQ(1.0, effectiveLeakageArea.dischargeCoefficient());
  EXPECT_TRUE(effectiveLeakageArea.setDischargeCoefficient(0.63));
  EXPECT_DOUBLE_EQ(0.63, effectiveLeakageArea.dischargeCoefficient());
  EXPECT_FALSE(effectiveLeakageArea.isDischargeCoefficientDefaulted());
  effectiveLeakageArea.resetDischargeCoefficient();
  EXPECT_TRUE(effectiveLeakageArea.isDischargeCoefficientDefaulted());
  EXPECT_DOUBLE_EQ(1.0, effectiveLeakageArea.dischargeCoefficient());

  EXPECT_TRUE(effectiveLeakageArea.isReferencePressureDifferenceDefaulted());
  EXPECT_DOUBLE_EQ(4.0, effectiveLeakageArea.referencePressureDifference());
  EXPECT_TRUE(effectiveLeakageArea.setReferencePressureDifference(12.5));
  EXPECT_DOUBLE_EQ(12.5, effectiveLeakageArea.referencePressureDifference());
  EXPECT_FALSE(effectiveLeakageArea.isReferencePressureDifferenceDefaulted());
  effectiveLeakageArea.resetReferencePressureDifference();
  EXPECT_TRUE(effectiveLeakageArea.isReferencePressureDifferenceDefaulted());
  EXPECT_DOUBLE_EQ(4.0, effectiveLeakageArea.referencePressureDifference());

  EXPECT_TRUE(effectiveLeakageArea.isAirMassFlowExponentDefaulted());
  EXPECT_DOUBLE_EQ(0.65, effectiveLeakageArea.airMassFlowExponent());
  EXPECT_TRUE(effectiveLeakageArea.setAirMassFlowExponent(0.58));
  EXPECT_DOUBLE_EQ(0.58, effectiveLeakageArea.airMassFlowExponent());
  EXPECT_FALSE(effectiveLeakageArea.isAirMassFlowExponentDefaulted());
  effectiveLeakageArea.resetAirMassFlowExponent();
  EXPECT_TRUE(effectiveLeakageArea.isAirMassFlowExponentDefaulted());
  EXPECT_DOUBLE_EQ(0.65, effectiveLeakageArea.airMassFlowExponent());
}
