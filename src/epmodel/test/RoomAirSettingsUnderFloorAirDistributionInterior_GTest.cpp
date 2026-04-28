/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include <algorithm>

#include "EPModelFixture.hpp"
#include "../scaffolds/RoomAirSettingsUnderFloorAirDistributionInterior.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, RoomAirSettingsUnderFloorAirDistributionInterior_DefaultConstructor) {
  Model model;
  RoomAirSettingsUnderFloorAirDistributionInterior object(model);
  EXPECT_EQ(RoomAirSettingsUnderFloorAirDistributionInterior::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, RoomAirSettingsUnderFloorAirDistributionInterior_ScalarAccessors_RoundTrip) {
  Model model;
  RoomAirSettingsUnderFloorAirDistributionInterior object(model);

  const auto floorDiffuserTypeValues = RoomAirSettingsUnderFloorAirDistributionInterior::floorDiffuserTypeValues();
  EXPECT_FALSE(floorDiffuserTypeValues.empty());
  EXPECT_TRUE(std::find(floorDiffuserTypeValues.begin(), floorDiffuserTypeValues.end(), "Swirl") != floorDiffuserTypeValues.end());

  EXPECT_TRUE(object.isThermostatHeightDefaulted());
  EXPECT_TRUE(object.isComfortHeightDefaulted());
  EXPECT_TRUE(object.isTemperatureDifferenceThresholdforReportingDefaulted());
  EXPECT_TRUE(object.isFloorDiffuserTypeDefaulted());

  EXPECT_DOUBLE_EQ(1.2, object.thermostatHeight());
  EXPECT_DOUBLE_EQ(1.1, object.comfortHeight());
  EXPECT_DOUBLE_EQ(0.4, object.temperatureDifferenceThresholdforReporting());
  EXPECT_EQ("Swirl", object.floorDiffuserType());

  EXPECT_TRUE(object.setThermostatHeight(1.35));
  EXPECT_TRUE(object.setComfortHeight(1.25));
  EXPECT_TRUE(object.setTemperatureDifferenceThresholdforReporting(0.5));
  EXPECT_TRUE(object.setFloorDiffuserType("Custom"));

  EXPECT_DOUBLE_EQ(1.35, object.thermostatHeight());
  EXPECT_DOUBLE_EQ(1.25, object.comfortHeight());
  EXPECT_DOUBLE_EQ(0.5, object.temperatureDifferenceThresholdforReporting());
  EXPECT_EQ("Custom", object.floorDiffuserType());

  EXPECT_FALSE(object.setThermostatHeight(0.0));
  EXPECT_FALSE(object.setComfortHeight(0.0));
  EXPECT_FALSE(object.setTemperatureDifferenceThresholdforReporting(-0.01));
  EXPECT_FALSE(object.setFloorDiffuserType("NotAChoice"));

  EXPECT_TRUE(object.isNumberofDiffusersDefaulted());
  EXPECT_TRUE(object.setNumberofDiffusers(6.0));
  ASSERT_TRUE(object.numberofDiffusers());
  EXPECT_DOUBLE_EQ(6.0, object.numberofDiffusers().get());
  EXPECT_FALSE(object.setNumberofDiffusers(0.0));
  object.autocalculateNumberofDiffusers();
  EXPECT_TRUE(object.isNumberofDiffusersAutocalculated());

  EXPECT_TRUE(object.setPowerperPlume(250.0));
  ASSERT_TRUE(object.powerperPlume());
  EXPECT_DOUBLE_EQ(250.0, object.powerperPlume().get());
  EXPECT_FALSE(object.setPowerperPlume(-1.0));
  object.autocalculatePowerperPlume();
  EXPECT_TRUE(object.isPowerperPlumeAutocalculated());

  EXPECT_TRUE(object.setDesignEffectiveAreaofDiffuser(0.02));
  ASSERT_TRUE(object.designEffectiveAreaofDiffuser());
  EXPECT_DOUBLE_EQ(0.02, object.designEffectiveAreaofDiffuser().get());
  EXPECT_FALSE(object.setDesignEffectiveAreaofDiffuser(0.0));
  object.autocalculateDesignEffectiveAreaofDiffuser();
  EXPECT_TRUE(object.isDesignEffectiveAreaofDiffuserAutocalculated());

  EXPECT_TRUE(object.setDiffuserSlotAnglefromVertical(35.0));
  ASSERT_TRUE(object.diffuserSlotAnglefromVertical());
  EXPECT_DOUBLE_EQ(35.0, object.diffuserSlotAnglefromVertical().get());
  EXPECT_FALSE(object.setDiffuserSlotAnglefromVertical(95.0));
  object.autocalculateDiffuserSlotAnglefromVertical();
  EXPECT_TRUE(object.isDiffuserSlotAnglefromVerticalAutocalculated());

  EXPECT_TRUE(object.setTransitionHeight(1.6));
  ASSERT_TRUE(object.transitionHeight());
  EXPECT_DOUBLE_EQ(1.6, object.transitionHeight().get());
  EXPECT_FALSE(object.setTransitionHeight(0.0));
  object.autocalculateTransitionHeight();
  EXPECT_TRUE(object.isTransitionHeightAutocalculated());

  EXPECT_TRUE(object.isCoefficientADefaulted());
  EXPECT_TRUE(object.setCoefficientA(0.3));
  ASSERT_TRUE(object.coefficientA());
  EXPECT_DOUBLE_EQ(0.3, object.coefficientA().get());
  object.autocalculateCoefficientA();
  EXPECT_TRUE(object.isCoefficientAAutocalculated());

  EXPECT_TRUE(object.setCoefficientB(0.4));
  ASSERT_TRUE(object.coefficientB());
  EXPECT_DOUBLE_EQ(0.4, object.coefficientB().get());

  EXPECT_TRUE(object.setCoefficientC(0.5));
  ASSERT_TRUE(object.coefficientC());
  EXPECT_DOUBLE_EQ(0.5, object.coefficientC().get());

  EXPECT_TRUE(object.setCoefficientD(0.6));
  ASSERT_TRUE(object.coefficientD());
  EXPECT_DOUBLE_EQ(0.6, object.coefficientD().get());

  EXPECT_TRUE(object.setCoefficientE(0.7));
  ASSERT_TRUE(object.coefficientE());
  EXPECT_DOUBLE_EQ(0.7, object.coefficientE().get());
}
