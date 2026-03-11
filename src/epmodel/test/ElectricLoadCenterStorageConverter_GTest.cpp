/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ParentObject/ElectricLoadCenterStorageConverter.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ElectricLoadCenterStorageConverter_DefaultConstructor) {
  Model model;
  ElectricLoadCenterStorageConverter converter(model);
  EXPECT_EQ(ElectricLoadCenterStorageConverter::iddObjectType(), converter.iddObject().type());
}

TEST_F(EPModelFixture, ElectricLoadCenterStorageConverter_ScalarAccessors_RoundTrip) {
  Model model;
  ElectricLoadCenterStorageConverter converter(model);

  const auto methodValues = ElectricLoadCenterStorageConverter::powerConversionEfficiencyMethodValues();
  ASSERT_FALSE(methodValues.empty());

  ASSERT_TRUE(converter.simpleFixedEfficiency());
  EXPECT_DOUBLE_EQ(0.95, *converter.simpleFixedEfficiency());
  EXPECT_EQ("SimpleFixed", converter.powerConversionEfficiencyMethod());

  ASSERT_TRUE(converter.setSimpleFixedEfficiency(0.90));
  ASSERT_TRUE(converter.simpleFixedEfficiency());
  EXPECT_DOUBLE_EQ(0.90, *converter.simpleFixedEfficiency());
  EXPECT_EQ("SimpleFixed", converter.powerConversionEfficiencyMethod());
  EXPECT_FALSE(converter.designMaximumContinuousInputPower());

  ASSERT_TRUE(converter.setDesignMaximumContinuousInputPower(7500.0));
  ASSERT_TRUE(converter.designMaximumContinuousInputPower());
  EXPECT_DOUBLE_EQ(7500.0, *converter.designMaximumContinuousInputPower());
  EXPECT_EQ("FunctionOfPower", converter.powerConversionEfficiencyMethod());
  EXPECT_FALSE(converter.simpleFixedEfficiency());

  EXPECT_TRUE(converter.isAncillaryPowerConsumedInStandbyDefaulted());
  ASSERT_TRUE(converter.setAncillaryPowerConsumedInStandby(120.0));
  EXPECT_FALSE(converter.isAncillaryPowerConsumedInStandbyDefaulted());
  EXPECT_DOUBLE_EQ(120.0, converter.ancillaryPowerConsumedInStandby());
  converter.resetAncillaryPowerConsumedInStandby();
  EXPECT_TRUE(converter.isAncillaryPowerConsumedInStandbyDefaulted());

  EXPECT_TRUE(converter.isRadiativeFractionDefaulted());
  ASSERT_TRUE(converter.setRadiativeFraction(0.15));
  EXPECT_FALSE(converter.isRadiativeFractionDefaulted());
  EXPECT_DOUBLE_EQ(0.15, converter.radiativeFraction());
  converter.resetRadiativeFraction();
  EXPECT_TRUE(converter.isRadiativeFractionDefaulted());
}
