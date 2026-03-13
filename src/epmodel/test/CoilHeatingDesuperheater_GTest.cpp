/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"
#include "../StraightComponent/CoilHeatingDesuperheater.hpp"
#include "../StraightComponent/Node.hpp"

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

TEST_F(EPModelFixture, CoilHeatingDesuperheater_AddToNode_SupplyOnly) {
  Model model;
  CoilHeatingDesuperheater coil(model);

  AirLoopHVAC airLoop(model);
  Node supplyOutletNode = airLoop.supplyOutletNode();
  EXPECT_TRUE(coil.addToNode(supplyOutletNode));

  auto splitterBranch = airLoop.zoneSplitter().lastOutletModelObject();
  ASSERT_TRUE(splitterBranch);
  auto splitterBranchNode = splitterBranch->optionalCast<Node>();
  ASSERT_TRUE(splitterBranchNode);
  EXPECT_FALSE(coil.addToNode(*splitterBranchNode));

  PlantLoop plantLoop(model);
  Node plantSupplyNode = plantLoop.supplyOutletNode();
  EXPECT_FALSE(coil.addToNode(plantSupplyNode));
  Node plantDemandNode = plantLoop.demandOutletNode();
  EXPECT_FALSE(coil.addToNode(plantDemandNode));
}
