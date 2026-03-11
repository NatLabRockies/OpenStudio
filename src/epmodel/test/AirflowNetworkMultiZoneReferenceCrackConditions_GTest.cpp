/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/AirflowNetworkMultiZoneReferenceCrackConditions.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AirflowNetworkMultiZoneReferenceCrackConditions_DefaultConstructor) {
  Model model;
  AirflowNetworkMultiZoneReferenceCrackConditions referenceCrackConditions(model);
  EXPECT_EQ(AirflowNetworkMultiZoneReferenceCrackConditions::iddObjectType(), referenceCrackConditions.iddObject().type());
}

TEST_F(EPModelFixture, AirflowNetworkMultiZoneReferenceCrackConditions_ScalarAccessors_RoundTrip) {
  Model model;
  AirflowNetworkMultiZoneReferenceCrackConditions referenceCrackConditions(model);

  EXPECT_TRUE(referenceCrackConditions.setReferenceTemperature(19.4));
  EXPECT_DOUBLE_EQ(19.4, referenceCrackConditions.referenceTemperature());

  EXPECT_TRUE(referenceCrackConditions.isReferenceBarometricPressureDefaulted());
  EXPECT_DOUBLE_EQ(101325.0, referenceCrackConditions.referenceBarometricPressure());

  EXPECT_TRUE(referenceCrackConditions.setReferenceBarometricPressure(100125.0));
  EXPECT_DOUBLE_EQ(100125.0, referenceCrackConditions.referenceBarometricPressure());
  EXPECT_FALSE(referenceCrackConditions.isReferenceBarometricPressureDefaulted());

  referenceCrackConditions.resetReferenceBarometricPressure();
  EXPECT_TRUE(referenceCrackConditions.isReferenceBarometricPressureDefaulted());
  EXPECT_DOUBLE_EQ(101325.0, referenceCrackConditions.referenceBarometricPressure());

  EXPECT_TRUE(referenceCrackConditions.isReferenceHumidityRatioDefaulted());
  EXPECT_DOUBLE_EQ(0.0, referenceCrackConditions.referenceHumidityRatio());

  EXPECT_TRUE(referenceCrackConditions.setReferenceHumidityRatio(0.0067));
  EXPECT_DOUBLE_EQ(0.0067, referenceCrackConditions.referenceHumidityRatio());
  EXPECT_FALSE(referenceCrackConditions.isReferenceHumidityRatioDefaulted());

  referenceCrackConditions.resetReferenceHumidityRatio();
  EXPECT_TRUE(referenceCrackConditions.isReferenceHumidityRatioDefaulted());
  EXPECT_DOUBLE_EQ(0.0, referenceCrackConditions.referenceHumidityRatio());
}
