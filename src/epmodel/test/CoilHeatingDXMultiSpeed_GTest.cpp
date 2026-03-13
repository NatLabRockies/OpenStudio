/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"
#include "../StraightComponent/CoilHeatingDXMultiSpeed.hpp"
#include "../StraightComponent/Node.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoilHeatingDXMultiSpeed_DefaultConstructor) {
  Model model;
  CoilHeatingDXMultiSpeed coil(model);
  EXPECT_EQ(CoilHeatingDXMultiSpeed::iddObjectType(), coil.iddObject().type());
  EXPECT_FALSE(coil.nameString().empty());

  EXPECT_DOUBLE_EQ(-8.0, coil.minimumOutdoorDryBulbTemperatureforCompressorOperation());
  EXPECT_DOUBLE_EQ(0.0, coil.crankcaseHeaterCapacity());
  EXPECT_DOUBLE_EQ(10.0, coil.maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation());
  EXPECT_DOUBLE_EQ(5.0, coil.maximumOutdoorDryBulbTemperatureforDefrostOperation());
  EXPECT_EQ("Resistive", coil.defrostStrategy());
  EXPECT_EQ("OnDemand", coil.defrostControl());
  EXPECT_NEAR(0.058333, coil.defrostTimePeriodFraction(), 0.000001);
  EXPECT_TRUE(coil.isResistiveDefrostHeaterCapacityAutosized());
  EXPECT_FALSE(coil.resistiveDefrostHeaterCapacity());
  EXPECT_FALSE(coil.applyPartLoadFractiontoSpeedsGreaterthan1());
  EXPECT_EQ("NaturalGas", coil.fuelType());
  EXPECT_EQ(4, coil.regionnumberforCalculatingHSPF());
}

TEST_F(EPModelFixture, CoilHeatingDXMultiSpeed_ScalarAccessors_RoundTrip) {
  Model model;
  CoilHeatingDXMultiSpeed coil(model);

  ASSERT_FALSE(CoilHeatingDXMultiSpeed::defrostStrategyValues().empty());
  ASSERT_FALSE(CoilHeatingDXMultiSpeed::defrostControlValues().empty());
  ASSERT_FALSE(CoilHeatingDXMultiSpeed::fuelTypeValues().empty());

  EXPECT_TRUE(coil.setMinimumOutdoorDryBulbTemperatureforCompressorOperation(-10.0));
  EXPECT_DOUBLE_EQ(-10.0, coil.minimumOutdoorDryBulbTemperatureforCompressorOperation());

  EXPECT_TRUE(coil.setOutdoorDryBulbTemperaturetoTurnOnCompressor(4.0));
  ASSERT_TRUE(coil.outdoorDryBulbTemperaturetoTurnOnCompressor());
  EXPECT_DOUBLE_EQ(4.0, *coil.outdoorDryBulbTemperaturetoTurnOnCompressor());
  coil.resetOutdoorDryBulbTemperaturetoTurnOnCompressor();
  EXPECT_FALSE(coil.outdoorDryBulbTemperaturetoTurnOnCompressor());

  EXPECT_TRUE(coil.setCrankcaseHeaterCapacity(120.0));
  EXPECT_DOUBLE_EQ(120.0, coil.crankcaseHeaterCapacity());

  EXPECT_TRUE(coil.setMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation(11.0));
  EXPECT_DOUBLE_EQ(11.0, coil.maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation());

  EXPECT_TRUE(coil.setMaximumOutdoorDryBulbTemperatureforDefrostOperation(6.0));
  EXPECT_DOUBLE_EQ(6.0, coil.maximumOutdoorDryBulbTemperatureforDefrostOperation());

  EXPECT_TRUE(coil.setDefrostStrategy("ReverseCycle"));
  EXPECT_EQ("ReverseCycle", coil.defrostStrategy());

  EXPECT_TRUE(coil.setDefrostControl("Timed"));
  EXPECT_EQ("Timed", coil.defrostControl());

  EXPECT_TRUE(coil.setDefrostTimePeriodFraction(0.1));
  EXPECT_DOUBLE_EQ(0.1, coil.defrostTimePeriodFraction());

  coil.autosizeResistiveDefrostHeaterCapacity();
  EXPECT_TRUE(coil.isResistiveDefrostHeaterCapacityAutosized());
  EXPECT_FALSE(coil.resistiveDefrostHeaterCapacity());
  EXPECT_TRUE(coil.setResistiveDefrostHeaterCapacity(400.0));
  ASSERT_TRUE(coil.resistiveDefrostHeaterCapacity());
  EXPECT_DOUBLE_EQ(400.0, *coil.resistiveDefrostHeaterCapacity());
  EXPECT_FALSE(coil.isResistiveDefrostHeaterCapacityAutosized());

  EXPECT_TRUE(coil.setApplyPartLoadFractiontoSpeedsGreaterthan1(true));
  EXPECT_TRUE(coil.applyPartLoadFractiontoSpeedsGreaterthan1());

  EXPECT_TRUE(coil.setFuelType("Electricity"));
  EXPECT_EQ("Electricity", coil.fuelType());

  EXPECT_TRUE(coil.setRegionnumberforCalculatingHSPF(5));
  EXPECT_EQ(5, coil.regionnumberforCalculatingHSPF());
}

TEST_F(EPModelFixture, CoilHeatingDXMultiSpeed_AddToNodeSupplyOnly) {
  Model model;
  AirLoopHVAC airLoop(model);
  CoilHeatingDXMultiSpeed supplyCoil(model);
  CoilHeatingDXMultiSpeed demandCoil(model);

  auto supplyInletNode = airLoop.supplyInletNode();
  EXPECT_TRUE(supplyCoil.addToNode(supplyInletNode));
  ASSERT_TRUE(supplyCoil.inletModelObject());
  EXPECT_EQ(supplyInletNode, supplyCoil.inletModelObject()->cast<Node>());
  EXPECT_TRUE(supplyCoil.outletModelObject());

  auto demandInletNode = airLoop.demandInletNode();
  EXPECT_FALSE(demandCoil.addToNode(demandInletNode));
  EXPECT_FALSE(demandCoil.airLoopHVAC());
}
