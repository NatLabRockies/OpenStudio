/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/GeneratorFuelCellInverter.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, GeneratorFuelCellInverter_DefaultConstructor) {
  Model model;
  GeneratorFuelCellInverter inverter(model);
  EXPECT_EQ(GeneratorFuelCellInverter::iddObjectType(), inverter.iddObject().type());
}

TEST_F(EPModelFixture, GeneratorFuelCellInverter_ScalarAccessors_RoundTrip) {
  Model model;
  GeneratorFuelCellInverter inverter(model);

  auto calculationModes = GeneratorFuelCellInverter::inverterEfficiencyCalculationModeValues();
  ASSERT_FALSE(calculationModes.empty());
  EXPECT_TRUE(inverter.setInverterEfficiencyCalculationMode(calculationModes.front()));
  EXPECT_EQ(calculationModes.front(), inverter.inverterEfficiencyCalculationMode());
  inverter.resetInverterEfficiencyCalculationMode();
  EXPECT_EQ("Constant", inverter.inverterEfficiencyCalculationMode());

  EXPECT_TRUE(inverter.setInverterEfficiency(0.94));
  EXPECT_DOUBLE_EQ(0.94, inverter.inverterEfficiency());
  inverter.resetInverterEfficiency();
  EXPECT_DOUBLE_EQ(1.0, inverter.inverterEfficiency());
}
