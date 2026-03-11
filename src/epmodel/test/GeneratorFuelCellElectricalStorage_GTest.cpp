/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/GeneratorFuelCellElectricalStorage.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, GeneratorFuelCellElectricalStorage_DefaultConstructor) {
  Model model;
  GeneratorFuelCellElectricalStorage electricalStorage(model);
  EXPECT_EQ(GeneratorFuelCellElectricalStorage::iddObjectType(), electricalStorage.iddObject().type());
}

TEST_F(EPModelFixture, GeneratorFuelCellElectricalStorage_ScalarAccessors_RoundTrip) {
  Model model;
  GeneratorFuelCellElectricalStorage electricalStorage(model);

  auto choiceofModelValues = GeneratorFuelCellElectricalStorage::choiceofModelValues();
  ASSERT_FALSE(choiceofModelValues.empty());
  EXPECT_TRUE(electricalStorage.setChoiceofModel(choiceofModelValues.front()));
  EXPECT_EQ(choiceofModelValues.front(), electricalStorage.choiceofModel());
  electricalStorage.resetChoiceofModel();
  EXPECT_EQ("SimpleEfficiencyWithConstraints", electricalStorage.choiceofModel());

  EXPECT_TRUE(electricalStorage.setNominalChargingEnergeticEfficiency(0.94));
  EXPECT_DOUBLE_EQ(0.94, electricalStorage.nominalChargingEnergeticEfficiency());
  electricalStorage.resetNominalChargingEnergeticEfficiency();
  EXPECT_DOUBLE_EQ(1.0, electricalStorage.nominalChargingEnergeticEfficiency());

  EXPECT_TRUE(electricalStorage.setNominalDischargingEnergeticEfficiency(0.91));
  EXPECT_DOUBLE_EQ(0.91, electricalStorage.nominalDischargingEnergeticEfficiency());
  electricalStorage.resetNominalDischargingEnergeticEfficiency();
  EXPECT_DOUBLE_EQ(1.0, electricalStorage.nominalDischargingEnergeticEfficiency());

  EXPECT_TRUE(electricalStorage.setSimpleMaximumCapacity(45000.0));
  EXPECT_DOUBLE_EQ(45000.0, electricalStorage.simpleMaximumCapacity());
  electricalStorage.resetSimpleMaximumCapacity();
  EXPECT_DOUBLE_EQ(0.0, electricalStorage.simpleMaximumCapacity());

  EXPECT_TRUE(electricalStorage.setSimpleMaximumPowerDraw(2300.0));
  EXPECT_DOUBLE_EQ(2300.0, electricalStorage.simpleMaximumPowerDraw());
  electricalStorage.resetSimpleMaximumPowerDraw();
  EXPECT_DOUBLE_EQ(0.0, electricalStorage.simpleMaximumPowerDraw());

  EXPECT_TRUE(electricalStorage.setSimpleMaximumPowerStore(2700.0));
  EXPECT_DOUBLE_EQ(2700.0, electricalStorage.simpleMaximumPowerStore());
  electricalStorage.resetSimpleMaximumPowerStore();
  EXPECT_DOUBLE_EQ(0.0, electricalStorage.simpleMaximumPowerStore());

  EXPECT_TRUE(electricalStorage.setInitialChargeState(1200.0));
  EXPECT_DOUBLE_EQ(1200.0, electricalStorage.initialChargeState());
  electricalStorage.resetInitialChargeState();
  EXPECT_DOUBLE_EQ(0.0, electricalStorage.initialChargeState());
}
