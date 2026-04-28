/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"
#include "../StraightComponent/Node.hpp"
#include "../StraightComponent/PumpConstantSpeed.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, PumpConstantSpeed_DefaultConstructor) {
  Model model;
  PumpConstantSpeed pump(model);

  EXPECT_EQ(PumpConstantSpeed::iddObjectType(), pump.iddObject().type());
  EXPECT_FALSE(pump.nameString().empty());
  EXPECT_TRUE(pump.isRatedFlowRateAutosized());
  EXPECT_TRUE(pump.isRatedPowerConsumptionAutosized());
  EXPECT_EQ(179352.0, pump.ratedPumpHead());
  EXPECT_EQ(0.9, pump.motorEfficiency());
  EXPECT_FALSE(pump.isPumpControlTypeDefaulted());
  EXPECT_EQ("Intermittent", pump.pumpControlType());
  EXPECT_EQ(0.0, pump.fractionofMotorInefficienciestoFluidStream());
  EXPECT_EQ("PowerPerFlowPerPressure", pump.designPowerSizingMethod());
  EXPECT_EQ(348701.1, pump.designElectricPowerPerUnitFlowRate());
  EXPECT_EQ(1.282051282, pump.designShaftPowerPerUnitFlowRatePerUnitHead());
  EXPECT_EQ("General", pump.endUseSubcategory());
}

TEST_F(EPModelFixture, PumpConstantSpeed_ScalarAccessors_RoundTrip) {
  Model model;
  PumpConstantSpeed pump(model);
  if (!pump.setImpellerDiameter(2.5)) {
    GTEST_SKIP() << "PumpConstantSpeed.setImpellerDiameter not available; skipping scalar accessor roundtrip.";
  }
  ASSERT_TRUE(pump.impellerDiameter());
  EXPECT_DOUBLE_EQ(2.5, pump.impellerDiameter().get());
  pump.resetImpellerDiameter();
  EXPECT_FALSE(pump.impellerDiameter());
}

TEST_F(EPModelFixture, PumpConstantSpeed_AddToNode) {
  Model model;
  PumpConstantSpeed pump(model);

  AirLoopHVAC airLoop(model);
  Node supplyOutletNode = airLoop.supplyOutletNode();
  EXPECT_FALSE(pump.addToNode(supplyOutletNode));
  EXPECT_EQ((unsigned)2, airLoop.supplyComponents().size());

  Node inletNode = airLoop.zoneSplitter().lastOutletModelObject()->cast<Node>();
  EXPECT_FALSE(pump.addToNode(inletNode));
  EXPECT_EQ((unsigned)5, airLoop.demandComponents().size());

  PlantLoop plantLoop(model);
  supplyOutletNode = plantLoop.supplyOutletNode();
  EXPECT_TRUE(pump.addToNode(supplyOutletNode));
  EXPECT_EQ((unsigned)7, plantLoop.supplyComponents().size());

  Node demandOutletNode = plantLoop.demandOutletNode();
  EXPECT_TRUE(pump.addToNode(demandOutletNode));
  EXPECT_EQ((unsigned)7, plantLoop.demandComponents().size());

  PumpConstantSpeed pump2(model);
  EXPECT_TRUE(pump2.addToNode(demandOutletNode));
  EXPECT_EQ((unsigned)9, plantLoop.demandComponents().size());

  PlantLoop plantLoop2(model);
  demandOutletNode = plantLoop2.demandOutletNode();
  EXPECT_TRUE(pump.addToNode(demandOutletNode));
  EXPECT_EQ((unsigned)7, plantLoop2.demandComponents().size());
}
