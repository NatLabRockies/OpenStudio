/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include <utilities/idd/FluidCooler_TwoSpeed_FieldEnums.hxx>

#include "EPModelFixture.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"
#include "../StraightComponent/FluidCoolerTwoSpeed.hpp"
#include "../StraightComponent/Node.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, FluidCoolerTwoSpeed_DefaultConstructor) {
  Model model;
  FluidCoolerTwoSpeed fluidCooler(model);

  EXPECT_EQ(FluidCoolerTwoSpeed::iddObjectType(), fluidCooler.iddObject().type());
  EXPECT_FALSE(fluidCooler.nameString().empty());

  EXPECT_EQ("NominalCapacity", fluidCooler.performanceInputMethod());

  EXPECT_FALSE(fluidCooler.highFanSpeedUfactorTimesAreaValue());
  EXPECT_TRUE(fluidCooler.isHighFanSpeedUfactorTimesAreaValueAutosized());

  EXPECT_FALSE(fluidCooler.lowFanSpeedUfactorTimesAreaValue());
  EXPECT_TRUE(fluidCooler.isLowFanSpeedUfactorTimesAreaValueAutosized());

  EXPECT_DOUBLE_EQ(0.6, fluidCooler.lowFanSpeedUFactorTimesAreaSizingFactor());
  EXPECT_DOUBLE_EQ(58601.0, fluidCooler.highSpeedNominalCapacity());

  ASSERT_TRUE(fluidCooler.lowSpeedNominalCapacity());
  EXPECT_DOUBLE_EQ(28601.0, *fluidCooler.lowSpeedNominalCapacity());
  EXPECT_FALSE(fluidCooler.isLowSpeedNominalCapacityAutosized());

  EXPECT_DOUBLE_EQ(0.5, fluidCooler.lowSpeedNominalCapacitySizingFactor());
  EXPECT_DOUBLE_EQ(51.67, fluidCooler.designEnteringWaterTemperature());
  EXPECT_DOUBLE_EQ(35.0, fluidCooler.designEnteringAirTemperature());
  EXPECT_DOUBLE_EQ(25.6, fluidCooler.designEnteringAirWetbulbTemperature());

  ASSERT_TRUE(fluidCooler.designWaterFlowRate());
  EXPECT_DOUBLE_EQ(0.001388, *fluidCooler.designWaterFlowRate());
  EXPECT_FALSE(fluidCooler.isDesignWaterFlowRateAutosized());

  ASSERT_TRUE(fluidCooler.highFanSpeedAirFlowRate());
  EXPECT_DOUBLE_EQ(9.911, *fluidCooler.highFanSpeedAirFlowRate());
  EXPECT_FALSE(fluidCooler.isHighFanSpeedAirFlowRateAutosized());

  EXPECT_FALSE(fluidCooler.highFanSpeedFanPower());
  EXPECT_TRUE(fluidCooler.isHighFanSpeedFanPowerAutosized());

  ASSERT_TRUE(fluidCooler.lowFanSpeedAirFlowRate());
  EXPECT_DOUBLE_EQ(4.955, *fluidCooler.lowFanSpeedAirFlowRate());
  EXPECT_FALSE(fluidCooler.isLowFanSpeedAirFlowRateAutosized());

  EXPECT_DOUBLE_EQ(0.5, fluidCooler.lowFanSpeedAirFlowRateSizingFactor());
  EXPECT_FALSE(fluidCooler.lowFanSpeedFanPower());
  EXPECT_TRUE(fluidCooler.isLowFanSpeedFanPowerAutosized());
  EXPECT_DOUBLE_EQ(0.16, fluidCooler.lowFanSpeedFanPowerSizingFactor());
}

TEST_F(EPModelFixture, FluidCoolerTwoSpeed_ScalarAccessors_RoundTrip) {
  Model model;
  FluidCoolerTwoSpeed fluidCooler(model);

  const auto performanceInputMethods = FluidCoolerTwoSpeed::performanceInputMethodValues();
  ASSERT_EQ(2u, performanceInputMethods.size());
  EXPECT_EQ("UFactorTimesAreaAndDesignWaterFlowRate", performanceInputMethods[0]);
  EXPECT_EQ("NominalCapacity", performanceInputMethods[1]);

  EXPECT_TRUE(fluidCooler.setPerformanceInputMethod("UFactorTimesAreaAndDesignWaterFlowRate"));
  EXPECT_EQ("UFactorTimesAreaAndDesignWaterFlowRate", fluidCooler.performanceInputMethod());

  EXPECT_TRUE(fluidCooler.setHighFanSpeedUfactorTimesAreaValue(3100.0));
  ASSERT_TRUE(fluidCooler.highFanSpeedUfactorTimesAreaValue());
  EXPECT_DOUBLE_EQ(3100.0, *fluidCooler.highFanSpeedUfactorTimesAreaValue());
  EXPECT_FALSE(fluidCooler.isHighFanSpeedUfactorTimesAreaValueAutosized());
  fluidCooler.autosizeHighFanSpeedUfactorTimesAreaValue();
  EXPECT_TRUE(fluidCooler.isHighFanSpeedUfactorTimesAreaValueAutosized());
  EXPECT_FALSE(fluidCooler.highFanSpeedUfactorTimesAreaValue());

  EXPECT_TRUE(fluidCooler.setLowFanSpeedUfactorTimesAreaValue(1700.0));
  ASSERT_TRUE(fluidCooler.lowFanSpeedUfactorTimesAreaValue());
  EXPECT_DOUBLE_EQ(1700.0, *fluidCooler.lowFanSpeedUfactorTimesAreaValue());
  EXPECT_FALSE(fluidCooler.isLowFanSpeedUfactorTimesAreaValueAutosized());
  fluidCooler.autosizeLowFanSpeedUfactorTimesAreaValue();
  EXPECT_TRUE(fluidCooler.isLowFanSpeedUfactorTimesAreaValueAutosized());
  EXPECT_FALSE(fluidCooler.lowFanSpeedUfactorTimesAreaValue());

  EXPECT_TRUE(fluidCooler.setLowFanSpeedUFactorTimesAreaSizingFactor(0.58));
  EXPECT_DOUBLE_EQ(0.58, fluidCooler.lowFanSpeedUFactorTimesAreaSizingFactor());

  EXPECT_TRUE(fluidCooler.setHighSpeedNominalCapacity(64000.0));
  EXPECT_DOUBLE_EQ(64000.0, fluidCooler.highSpeedNominalCapacity());

  EXPECT_TRUE(fluidCooler.setLowSpeedNominalCapacity(30000.0));
  ASSERT_TRUE(fluidCooler.lowSpeedNominalCapacity());
  EXPECT_DOUBLE_EQ(30000.0, *fluidCooler.lowSpeedNominalCapacity());
  EXPECT_FALSE(fluidCooler.isLowSpeedNominalCapacityAutosized());
  fluidCooler.autosizeLowSpeedNominalCapacity();
  EXPECT_TRUE(fluidCooler.isLowSpeedNominalCapacityAutosized());
  EXPECT_FALSE(fluidCooler.lowSpeedNominalCapacity());

  EXPECT_TRUE(fluidCooler.setLowSpeedNominalCapacitySizingFactor(0.45));
  EXPECT_DOUBLE_EQ(0.45, fluidCooler.lowSpeedNominalCapacitySizingFactor());

  EXPECT_TRUE(fluidCooler.setDesignEnteringWaterTemperature(46.0));
  EXPECT_DOUBLE_EQ(46.0, fluidCooler.designEnteringWaterTemperature());

  EXPECT_TRUE(fluidCooler.setDesignEnteringAirTemperature(31.0));
  EXPECT_DOUBLE_EQ(31.0, fluidCooler.designEnteringAirTemperature());

  EXPECT_TRUE(fluidCooler.setDesignEnteringAirWetbulbTemperature(22.0));
  EXPECT_DOUBLE_EQ(22.0, fluidCooler.designEnteringAirWetbulbTemperature());

  EXPECT_TRUE(fluidCooler.setDesignWaterFlowRate(0.0022));
  ASSERT_TRUE(fluidCooler.designWaterFlowRate());
  EXPECT_DOUBLE_EQ(0.0022, *fluidCooler.designWaterFlowRate());
  EXPECT_FALSE(fluidCooler.isDesignWaterFlowRateAutosized());
  fluidCooler.autosizeDesignWaterFlowRate();
  EXPECT_TRUE(fluidCooler.isDesignWaterFlowRateAutosized());
  EXPECT_FALSE(fluidCooler.designWaterFlowRate());

  EXPECT_TRUE(fluidCooler.setHighFanSpeedAirFlowRate(12.2));
  ASSERT_TRUE(fluidCooler.highFanSpeedAirFlowRate());
  EXPECT_DOUBLE_EQ(12.2, *fluidCooler.highFanSpeedAirFlowRate());
  EXPECT_FALSE(fluidCooler.isHighFanSpeedAirFlowRateAutosized());
  fluidCooler.autosizeHighFanSpeedAirFlowRate();
  EXPECT_TRUE(fluidCooler.isHighFanSpeedAirFlowRateAutosized());
  EXPECT_FALSE(fluidCooler.highFanSpeedAirFlowRate());

  EXPECT_TRUE(fluidCooler.setHighFanSpeedFanPower(1650.0));
  ASSERT_TRUE(fluidCooler.highFanSpeedFanPower());
  EXPECT_DOUBLE_EQ(1650.0, *fluidCooler.highFanSpeedFanPower());
  EXPECT_FALSE(fluidCooler.isHighFanSpeedFanPowerAutosized());
  fluidCooler.autosizeHighFanSpeedFanPower();
  EXPECT_TRUE(fluidCooler.isHighFanSpeedFanPowerAutosized());
  EXPECT_FALSE(fluidCooler.highFanSpeedFanPower());

  EXPECT_TRUE(fluidCooler.setLowFanSpeedAirFlowRate(6.2));
  ASSERT_TRUE(fluidCooler.lowFanSpeedAirFlowRate());
  EXPECT_DOUBLE_EQ(6.2, *fluidCooler.lowFanSpeedAirFlowRate());
  EXPECT_FALSE(fluidCooler.isLowFanSpeedAirFlowRateAutosized());
  fluidCooler.autosizeLowFanSpeedAirFlowRate();
  EXPECT_TRUE(fluidCooler.isLowFanSpeedAirFlowRateAutosized());
  EXPECT_FALSE(fluidCooler.lowFanSpeedAirFlowRate());

  EXPECT_TRUE(fluidCooler.setLowFanSpeedAirFlowRateSizingFactor(0.47));
  EXPECT_DOUBLE_EQ(0.47, fluidCooler.lowFanSpeedAirFlowRateSizingFactor());

  EXPECT_TRUE(fluidCooler.setLowFanSpeedFanPower(720.0));
  ASSERT_TRUE(fluidCooler.lowFanSpeedFanPower());
  EXPECT_DOUBLE_EQ(720.0, *fluidCooler.lowFanSpeedFanPower());
  EXPECT_FALSE(fluidCooler.isLowFanSpeedFanPowerAutosized());
  fluidCooler.autosizeLowFanSpeedFanPower();
  EXPECT_TRUE(fluidCooler.isLowFanSpeedFanPowerAutosized());
  EXPECT_FALSE(fluidCooler.lowFanSpeedFanPower());

  EXPECT_TRUE(fluidCooler.setLowFanSpeedFanPowerSizingFactor(0.2));
  EXPECT_DOUBLE_EQ(0.2, fluidCooler.lowFanSpeedFanPowerSizingFactor());

  EXPECT_FALSE(fluidCooler.autosizedHighFanSpeedUfactorTimesAreaValue());
  EXPECT_FALSE(fluidCooler.autosizedLowFanSpeedUfactorTimesAreaValue());
  EXPECT_FALSE(fluidCooler.autosizedLowSpeedNominalCapacity());
  EXPECT_FALSE(fluidCooler.autosizedDesignWaterFlowRate());
  EXPECT_FALSE(fluidCooler.autosizedHighFanSpeedAirFlowRate());
  EXPECT_FALSE(fluidCooler.autosizedHighFanSpeedFanPower());
  EXPECT_FALSE(fluidCooler.autosizedLowFanSpeedAirFlowRate());
  EXPECT_FALSE(fluidCooler.autosizedLowFanSpeedFanPower());
}

TEST_F(EPModelFixture, FluidCoolerTwoSpeed_AddToNode_PlantSupplyOnly) {
  Model model;
  FluidCoolerTwoSpeed fluidCooler(model);

  AirLoopHVAC airLoop(model);
  Node airSupplyOutletNode = airLoop.supplyOutletNode();
  EXPECT_FALSE(fluidCooler.addToNode(airSupplyOutletNode));
  EXPECT_EQ(2u, airLoop.supplyComponents().size());
  EXPECT_FALSE(fluidCooler.loop());
  EXPECT_FALSE(fluidCooler.inletModelObject());
  EXPECT_FALSE(fluidCooler.outletModelObject());

  auto splitterBranch = airLoop.zoneSplitter().lastOutletModelObject();
  ASSERT_TRUE(splitterBranch);
  auto demandBranchNode = splitterBranch->optionalCast<Node>();
  ASSERT_TRUE(demandBranchNode);
  EXPECT_FALSE(fluidCooler.addToNode(*demandBranchNode));
  EXPECT_EQ(5u, airLoop.demandComponents().size());
  EXPECT_FALSE(fluidCooler.loop());
  EXPECT_FALSE(fluidCooler.inletModelObject());
  EXPECT_FALSE(fluidCooler.outletModelObject());

  PlantLoop plantLoop(model);
  Node plantSupplyOutletNode = plantLoop.supplyOutletNode();
  EXPECT_TRUE(fluidCooler.addToNode(plantSupplyOutletNode));
  EXPECT_EQ(7u, plantLoop.supplyComponents().size());
  ASSERT_TRUE(fluidCooler.loop());
  EXPECT_EQ(plantLoop.handle(), fluidCooler.loop()->handle());
  ASSERT_TRUE(fluidCooler.inletModelObject());
  ASSERT_TRUE(fluidCooler.outletModelObject());

  auto inletNode = fluidCooler.getModelObjectTarget<Node>(openstudio::FluidCooler_TwoSpeedFields::WaterInletNodeName);
  auto outletNode = fluidCooler.getModelObjectTarget<Node>(openstudio::FluidCooler_TwoSpeedFields::WaterOutletNodeName);
  ASSERT_TRUE(inletNode);
  ASSERT_TRUE(outletNode);
  EXPECT_EQ(fluidCooler.inletModelObject()->handle(), inletNode->handle());
  EXPECT_EQ(fluidCooler.outletModelObject()->handle(), outletNode->handle());

  FluidCoolerTwoSpeed secondFluidCooler(model);
  Node plantDemandOutletNode = plantLoop.demandOutletNode();
  EXPECT_FALSE(secondFluidCooler.addToNode(plantDemandOutletNode));
  EXPECT_EQ(5u, plantLoop.demandComponents().size());
  EXPECT_FALSE(secondFluidCooler.loop());
  EXPECT_FALSE(secondFluidCooler.inletModelObject());
  EXPECT_FALSE(secondFluidCooler.outletModelObject());
}
