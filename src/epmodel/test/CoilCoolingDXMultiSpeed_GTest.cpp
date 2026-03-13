/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"
#include "../StraightComponent/CoilCoolingDXMultiSpeed.hpp"
#include "../StraightComponent/Node.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoilCoolingDXMultiSpeed_DefaultConstructor) {
  Model model;
  CoilCoolingDXMultiSpeed coil(model);
  EXPECT_EQ(CoilCoolingDXMultiSpeed::iddObjectType(), coil.iddObject().type());
  EXPECT_FALSE(coil.nameString().empty());

  EXPECT_EQ("AirCooled", coil.condenserType());
  EXPECT_FALSE(coil.applyPartLoadFractiontoSpeedsGreaterthan1());
  EXPECT_DOUBLE_EQ(0.0, coil.crankcaseHeaterCapacity());
  EXPECT_DOUBLE_EQ(10.0, coil.maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation());
  EXPECT_DOUBLE_EQ(-25.0, coil.minimumOutdoorDryBulbTemperatureforCompressorOperation());
  EXPECT_DOUBLE_EQ(0.0, coil.basinHeaterCapacity());
  EXPECT_DOUBLE_EQ(2.0, coil.basinHeaterSetpointTemperature());
  EXPECT_EQ("NaturalGas", coil.fuelType());
}

TEST_F(EPModelFixture, CoilCoolingDXMultiSpeed_ScalarAccessors_RoundTrip) {
  Model model;
  CoilCoolingDXMultiSpeed coil(model);

  ASSERT_FALSE(CoilCoolingDXMultiSpeed::condenserTypeValues().empty());
  ASSERT_FALSE(CoilCoolingDXMultiSpeed::fuelTypeValues().empty());

  EXPECT_TRUE(coil.setCondenserType("EvaporativelyCooled"));
  EXPECT_EQ("EvaporativelyCooled", coil.condenserType());

  EXPECT_TRUE(coil.setApplyPartLoadFractiontoSpeedsGreaterthan1(true));
  EXPECT_TRUE(coil.applyPartLoadFractiontoSpeedsGreaterthan1());

  EXPECT_TRUE(coil.setApplyLatentDegradationtoSpeedsGreaterthan1(false));
  EXPECT_FALSE(coil.applyLatentDegradationtoSpeedsGreaterthan1());
  EXPECT_FALSE(coil.isApplyLatentDegradationtoSpeedsGreaterthan1Defaulted());
  coil.resetApplyLatentDegradationtoSpeedsGreaterthan1();
  EXPECT_TRUE(coil.isApplyLatentDegradationtoSpeedsGreaterthan1Defaulted());

  EXPECT_TRUE(coil.setCrankcaseHeaterCapacity(105.0));
  EXPECT_DOUBLE_EQ(105.0, coil.crankcaseHeaterCapacity());

  EXPECT_TRUE(coil.setMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation(9.0));
  EXPECT_DOUBLE_EQ(9.0, coil.maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation());

  EXPECT_TRUE(coil.setMinimumOutdoorDryBulbTemperatureforCompressorOperation(-7.5));
  EXPECT_DOUBLE_EQ(-7.5, coil.minimumOutdoorDryBulbTemperatureforCompressorOperation());

  EXPECT_TRUE(coil.setBasinHeaterCapacity(20.0));
  EXPECT_DOUBLE_EQ(20.0, coil.basinHeaterCapacity());

  EXPECT_TRUE(coil.setBasinHeaterSetpointTemperature(3.0));
  EXPECT_DOUBLE_EQ(3.0, coil.basinHeaterSetpointTemperature());

  EXPECT_TRUE(coil.setFuelType("Electricity"));
  EXPECT_EQ("Electricity", coil.fuelType());
}

TEST_F(EPModelFixture, CoilCoolingDXMultiSpeed_AddToNodeSupplyOnly) {
  Model model;
  AirLoopHVAC airLoop(model);
  CoilCoolingDXMultiSpeed supplyCoil(model);
  CoilCoolingDXMultiSpeed demandCoil(model);

  auto supplyInletNode = airLoop.supplyInletNode();
  EXPECT_TRUE(supplyCoil.addToNode(supplyInletNode));
  ASSERT_TRUE(supplyCoil.inletModelObject());
  EXPECT_EQ(supplyInletNode, supplyCoil.inletModelObject()->cast<Node>());
  EXPECT_TRUE(supplyCoil.outletModelObject());

  auto demandInletNode = airLoop.demandInletNode();
  EXPECT_FALSE(demandCoil.addToNode(demandInletNode));
  EXPECT_FALSE(demandCoil.airLoopHVAC());
}
