/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../StraightComponent/CoilHeatingDesuperheater.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoilHeatingDesuperheater_DefaultConstructor) {
  Model model;
  CoilHeatingDesuperheater coil(model);
  EXPECT_EQ(CoilHeatingDesuperheater::iddObjectType(), coil.iddObject().type());
  EXPECT_FALSE(coil.nameString().empty());

  EXPECT_DOUBLE_EQ(0.8, coil.heatReclaimRecoveryEfficiency());
  EXPECT_FALSE(coil.isHeatReclaimRecoveryEfficiencyDefaulted());

  EXPECT_DOUBLE_EQ(0.0, coil.onCycleParasiticElectricLoad());
  EXPECT_DOUBLE_EQ(0.0, coil.parasiticElectricLoad());
  EXPECT_FALSE(coil.isOnCycleParasiticElectricLoadDefaulted());
  EXPECT_FALSE(coil.isParasiticElectricLoadDefaulted());
}

TEST_F(EPModelFixture, CoilHeatingDesuperheater_ScalarAccessors_RoundTrip) {
  Model model;
  CoilHeatingDesuperheater coil(model);

  EXPECT_TRUE(coil.setHeatReclaimRecoveryEfficiency(0.67));
  EXPECT_DOUBLE_EQ(0.67, coil.heatReclaimRecoveryEfficiency());
  EXPECT_FALSE(coil.isHeatReclaimRecoveryEfficiencyDefaulted());

  coil.resetHeatReclaimRecoveryEfficiency();
  EXPECT_FALSE(coil.isHeatReclaimRecoveryEfficiencyDefaulted());
  EXPECT_DOUBLE_EQ(0.67, coil.heatReclaimRecoveryEfficiency());

  EXPECT_TRUE(coil.setOnCycleParasiticElectricLoad(123.0));
  EXPECT_DOUBLE_EQ(123.0, coil.onCycleParasiticElectricLoad());
  EXPECT_DOUBLE_EQ(123.0, coil.parasiticElectricLoad());
  EXPECT_FALSE(coil.isOnCycleParasiticElectricLoadDefaulted());
  EXPECT_FALSE(coil.isParasiticElectricLoadDefaulted());

  EXPECT_TRUE(coil.setParasiticElectricLoad(55.0));
  EXPECT_DOUBLE_EQ(55.0, coil.onCycleParasiticElectricLoad());
  EXPECT_DOUBLE_EQ(55.0, coil.parasiticElectricLoad());

  coil.resetParasiticElectricLoad();
  EXPECT_FALSE(coil.isOnCycleParasiticElectricLoadDefaulted());
  EXPECT_FALSE(coil.isParasiticElectricLoadDefaulted());
  EXPECT_DOUBLE_EQ(55.0, coil.onCycleParasiticElectricLoad());

  EXPECT_TRUE(coil.setParasiticElectricLoad(44.0));
  coil.resetOnCycleParasiticElectricLoad();
  EXPECT_FALSE(coil.isOnCycleParasiticElectricLoadDefaulted());
  EXPECT_FALSE(coil.isParasiticElectricLoadDefaulted());
  EXPECT_DOUBLE_EQ(44.0, coil.parasiticElectricLoad());
}
