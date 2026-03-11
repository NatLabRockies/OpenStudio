/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "ModelObject/UtilityCostTariff.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, UtilityCostTariff_DefaultConstructor) {
  Model model;
  UtilityCostTariff tariff(model);

  EXPECT_EQ(UtilityCostTariff::iddObjectType(), tariff.iddObject().type());
  EXPECT_FALSE(UtilityCostTariff::conversionFactorChoiceValues().empty());
  EXPECT_FALSE(UtilityCostTariff::demandWindowLengthValues().empty());
  EXPECT_FALSE(UtilityCostTariff::buyOrSellValues().empty());
  EXPECT_FALSE(tariff.conversionFactorChoice());
  EXPECT_FALSE(tariff.energyConversionFactor());
  EXPECT_FALSE(tariff.demandConversionFactor());
  EXPECT_FALSE(tariff.demandWindowLength());
  EXPECT_FALSE(tariff.monthlyChargeorVariableName());
  EXPECT_FALSE(tariff.minimumMonthlyChargeorVariableName());
  EXPECT_FALSE(tariff.groupName());
  EXPECT_FALSE(tariff.buyOrSell().empty());
}

TEST_F(EPModelFixture, UtilityCostTariff_ScalarAccessors_RoundTrip) {
  Model model;
  UtilityCostTariff tariff(model);

  ASSERT_FALSE(UtilityCostTariff::conversionFactorChoiceValues().empty());
  ASSERT_FALSE(UtilityCostTariff::demandWindowLengthValues().empty());
  ASSERT_FALSE(UtilityCostTariff::buyOrSellValues().empty());

  const auto conversionChoice = UtilityCostTariff::conversionFactorChoiceValues().front();
  const auto demandWindowLength = UtilityCostTariff::demandWindowLengthValues().front();
  const auto buyOrSell = UtilityCostTariff::buyOrSellValues().front();

  EXPECT_TRUE(tariff.setConversionFactorChoice(conversionChoice));
  EXPECT_TRUE(tariff.setEnergyConversionFactor(1.5));
  EXPECT_TRUE(tariff.setDemandConversionFactor(2.5));
  EXPECT_TRUE(tariff.setDemandWindowLength(demandWindowLength));
  EXPECT_TRUE(tariff.setMonthlyChargeorVariableName("monthly"));
  EXPECT_TRUE(tariff.setMinimumMonthlyChargeorVariableName("minimum"));
  EXPECT_TRUE(tariff.setGroupName("group"));
  EXPECT_TRUE(tariff.setBuyOrSell(buyOrSell));

  ASSERT_TRUE(tariff.conversionFactorChoice());
  EXPECT_EQ(conversionChoice, *tariff.conversionFactorChoice());
  ASSERT_TRUE(tariff.energyConversionFactor());
  EXPECT_DOUBLE_EQ(1.5, *tariff.energyConversionFactor());
  ASSERT_TRUE(tariff.demandConversionFactor());
  EXPECT_DOUBLE_EQ(2.5, *tariff.demandConversionFactor());
  ASSERT_TRUE(tariff.demandWindowLength());
  EXPECT_EQ(demandWindowLength, *tariff.demandWindowLength());
  ASSERT_TRUE(tariff.monthlyChargeorVariableName());
  EXPECT_EQ("monthly", *tariff.monthlyChargeorVariableName());
  ASSERT_TRUE(tariff.minimumMonthlyChargeorVariableName());
  EXPECT_EQ("minimum", *tariff.minimumMonthlyChargeorVariableName());
  ASSERT_TRUE(tariff.groupName());
  EXPECT_EQ("group", *tariff.groupName());
  EXPECT_EQ(buyOrSell, tariff.buyOrSell());

  tariff.resetConversionFactorChoice();
  EXPECT_FALSE(tariff.conversionFactorChoice());

  tariff.resetEnergyConversionFactor();
  EXPECT_FALSE(tariff.energyConversionFactor());

  tariff.resetDemandConversionFactor();
  EXPECT_FALSE(tariff.demandConversionFactor());

  tariff.resetDemandWindowLength();
  EXPECT_FALSE(tariff.demandWindowLength());

  tariff.resetMonthlyChargeorVariableName();
  EXPECT_FALSE(tariff.monthlyChargeorVariableName());

  tariff.resetMinimumMonthlyChargeorVariableName();
  EXPECT_FALSE(tariff.minimumMonthlyChargeorVariableName());

  tariff.resetGroupName();
  EXPECT_FALSE(tariff.groupName());
}
