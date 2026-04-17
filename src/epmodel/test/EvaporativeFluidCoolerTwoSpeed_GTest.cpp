/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include <utilities/idd/EvaporativeFluidCooler_TwoSpeed_FieldEnums.hxx>

#include "EPModelFixture.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"
#include "../StraightComponent/EvaporativeFluidCoolerTwoSpeed.hpp"
#include "../StraightComponent/Node.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, EvaporativeFluidCoolerTwoSpeed_DefaultConstructor) {
  Model model;
  EvaporativeFluidCoolerTwoSpeed evap(model);

  EXPECT_EQ(EvaporativeFluidCoolerTwoSpeed::iddObjectType(), evap.iddObject().type());
  EXPECT_FALSE(evap.nameString().empty());

  EXPECT_FALSE(evap.highFanSpeedAirFlowRate());
  EXPECT_TRUE(evap.isHighFanSpeedAirFlowRateAutosized());

  EXPECT_FALSE(evap.highFanSpeedFanPower());
  EXPECT_TRUE(evap.isHighFanSpeedFanPowerAutosized());

  EXPECT_FALSE(evap.lowFanSpeedAirFlowRate());
  EXPECT_TRUE(evap.isLowFanSpeedAirFlowRateAutosized());

  EXPECT_DOUBLE_EQ(0.5, evap.lowFanSpeedAirFlowRateSizingFactor());

  EXPECT_FALSE(evap.lowFanSpeedFanPower());
  EXPECT_TRUE(evap.isLowFanSpeedFanPowerAutosized());

  EXPECT_DOUBLE_EQ(0.5, evap.lowFanSpeedFanPowerSizingFactor());
  EXPECT_DOUBLE_EQ(0.002208, evap.designSprayWaterFlowRate());
  EXPECT_EQ("UFactorTimesAreaAndDesignWaterFlowRate", evap.performanceInputMethod());
  EXPECT_DOUBLE_EQ(1.25, evap.heatRejectionCapacityandNominalCapacitySizingRatio());

  EXPECT_FALSE(evap.highSpeedStandardDesignCapacity());
  EXPECT_FALSE(evap.lowSpeedStandardDesignCapacity());
  EXPECT_TRUE(evap.isLowSpeedStandardDesignCapacityAutosized());
  EXPECT_DOUBLE_EQ(0.5, evap.lowSpeedStandardCapacitySizingFactor());

  EXPECT_FALSE(evap.highFanSpeedUfactorTimesAreaValue());
  EXPECT_TRUE(evap.isHighFanSpeedUfactorTimesAreaValueAutosized());

  EXPECT_FALSE(evap.lowFanSpeedUfactorTimesAreaValue());
  EXPECT_TRUE(evap.isLowFanSpeedUfactorTimesAreaValueAutosized());

  EXPECT_DOUBLE_EQ(0.6, evap.lowFanSpeedUFactorTimesAreaSizingFactor());

  EXPECT_FALSE(evap.designWaterFlowRate());
  EXPECT_TRUE(evap.isDesignWaterFlowRateAutosized());

  EXPECT_FALSE(evap.highSpeedUserSpecifiedDesignCapacity());
  EXPECT_FALSE(evap.lowSpeedUserSpecifiedDesignCapacity());
  EXPECT_TRUE(evap.isLowSpeedUserSpecifiedDesignCapacityAutosized());
  EXPECT_DOUBLE_EQ(0.5, evap.lowSpeedUserSpecifiedDesignCapacitySizingFactor());

  EXPECT_FALSE(evap.designEnteringWaterTemperature());
  EXPECT_TRUE(evap.isDesignEnteringWaterTemperatureAutosized());

  EXPECT_DOUBLE_EQ(35.0, evap.designEnteringAirTemperature());
  EXPECT_DOUBLE_EQ(25.6, evap.designEnteringAirWetbulbTemperature());
  EXPECT_DOUBLE_EQ(1.0, evap.highSpeedSizingFactor());
  EXPECT_EQ("SaturatedExit", evap.evaporationLossMode());
  EXPECT_FALSE(evap.evaporationLossFactor());
  EXPECT_DOUBLE_EQ(0.008, evap.driftLossPercent());
  EXPECT_EQ("ConcentrationRatio", evap.blowdownCalculationMode());
  EXPECT_DOUBLE_EQ(3.0, evap.blowdownConcentrationRatio());
}

TEST_F(EPModelFixture, EvaporativeFluidCoolerTwoSpeed_ScalarAccessors_RoundTrip) {
  Model model;
  EvaporativeFluidCoolerTwoSpeed evap(model);

  EXPECT_FALSE(EvaporativeFluidCoolerTwoSpeed::performanceInputMethodValues().empty());
  EXPECT_FALSE(EvaporativeFluidCoolerTwoSpeed::evaporationLossModeValues().empty());
  EXPECT_FALSE(EvaporativeFluidCoolerTwoSpeed::blowdownCalculationModeValues().empty());

  EXPECT_TRUE(evap.setHighFanSpeedAirFlowRate(4.1));
  ASSERT_TRUE(evap.highFanSpeedAirFlowRate());
  EXPECT_DOUBLE_EQ(4.1, *evap.highFanSpeedAirFlowRate());
  EXPECT_FALSE(evap.isHighFanSpeedAirFlowRateAutosized());
  evap.autosizeHighFanSpeedAirFlowRate();
  EXPECT_TRUE(evap.isHighFanSpeedAirFlowRateAutosized());

  EXPECT_TRUE(evap.setHighFanSpeedFanPower(1400.0));
  ASSERT_TRUE(evap.highFanSpeedFanPower());
  EXPECT_DOUBLE_EQ(1400.0, *evap.highFanSpeedFanPower());
  evap.autosizeHighFanSpeedFanPower();
  EXPECT_TRUE(evap.isHighFanSpeedFanPowerAutosized());

  EXPECT_TRUE(evap.setLowFanSpeedAirFlowRate(2.3));
  ASSERT_TRUE(evap.lowFanSpeedAirFlowRate());
  EXPECT_DOUBLE_EQ(2.3, *evap.lowFanSpeedAirFlowRate());
  evap.autosizeLowFanSpeedAirFlowRate();
  EXPECT_TRUE(evap.isLowFanSpeedAirFlowRateAutosized());

  EXPECT_TRUE(evap.setLowFanSpeedAirFlowRateSizingFactor(0.55));
  EXPECT_DOUBLE_EQ(0.55, evap.lowFanSpeedAirFlowRateSizingFactor());

  EXPECT_TRUE(evap.setLowFanSpeedFanPower(600.0));
  ASSERT_TRUE(evap.lowFanSpeedFanPower());
  EXPECT_DOUBLE_EQ(600.0, *evap.lowFanSpeedFanPower());
  evap.autosizeLowFanSpeedFanPower();
  EXPECT_TRUE(evap.isLowFanSpeedFanPowerAutosized());

  EXPECT_TRUE(evap.setLowFanSpeedFanPowerSizingFactor(0.52));
  EXPECT_DOUBLE_EQ(0.52, evap.lowFanSpeedFanPowerSizingFactor());

  EXPECT_TRUE(evap.setDesignSprayWaterFlowRate(0.004));
  EXPECT_DOUBLE_EQ(0.004, evap.designSprayWaterFlowRate());

  EXPECT_TRUE(evap.setPerformanceInputMethod("StandardDesignCapacity"));
  EXPECT_EQ("StandardDesignCapacity", evap.performanceInputMethod());

  EXPECT_TRUE(evap.setHeatRejectionCapacityandNominalCapacitySizingRatio(1.15));
  EXPECT_DOUBLE_EQ(1.15, evap.heatRejectionCapacityandNominalCapacitySizingRatio());

  EXPECT_TRUE(evap.setHighSpeedStandardDesignCapacity(9500.0));
  ASSERT_TRUE(evap.highSpeedStandardDesignCapacity());
  EXPECT_DOUBLE_EQ(9500.0, *evap.highSpeedStandardDesignCapacity());
  evap.resetHighSpeedStandardDesignCapacity();
  EXPECT_FALSE(evap.highSpeedStandardDesignCapacity());

  EXPECT_TRUE(evap.setLowSpeedStandardDesignCapacity(4200.0));
  ASSERT_TRUE(evap.lowSpeedStandardDesignCapacity());
  EXPECT_DOUBLE_EQ(4200.0, *evap.lowSpeedStandardDesignCapacity());
  evap.resetLowSpeedStandardDesignCapacity();
  EXPECT_FALSE(evap.lowSpeedStandardDesignCapacity());
  evap.autosizeLowSpeedStandardDesignCapacity();
  EXPECT_TRUE(evap.isLowSpeedStandardDesignCapacityAutosized());

  EXPECT_TRUE(evap.setLowSpeedStandardCapacitySizingFactor(0.48));
  EXPECT_DOUBLE_EQ(0.48, evap.lowSpeedStandardCapacitySizingFactor());

  EXPECT_TRUE(evap.setHighFanSpeedUfactorTimesAreaValue(2800.0));
  ASSERT_TRUE(evap.highFanSpeedUfactorTimesAreaValue());
  EXPECT_DOUBLE_EQ(2800.0, *evap.highFanSpeedUfactorTimesAreaValue());
  evap.resetHighFanSpeedUfactorTimesAreaValue();
  EXPECT_FALSE(evap.highFanSpeedUfactorTimesAreaValue());
  evap.autosizeHighFanSpeedUfactorTimesAreaValue();
  EXPECT_TRUE(evap.isHighFanSpeedUfactorTimesAreaValueAutosized());

  EXPECT_TRUE(evap.setLowFanSpeedUfactorTimesAreaValue(1500.0));
  ASSERT_TRUE(evap.lowFanSpeedUfactorTimesAreaValue());
  EXPECT_DOUBLE_EQ(1500.0, *evap.lowFanSpeedUfactorTimesAreaValue());
  evap.resetLowFanSpeedUfactorTimesAreaValue();
  EXPECT_FALSE(evap.lowFanSpeedUfactorTimesAreaValue());
  evap.autosizeLowFanSpeedUfactorTimesAreaValue();
  EXPECT_TRUE(evap.isLowFanSpeedUfactorTimesAreaValueAutosized());

  EXPECT_TRUE(evap.setLowFanSpeedUFactorTimesAreaSizingFactor(0.61));
  EXPECT_DOUBLE_EQ(0.61, evap.lowFanSpeedUFactorTimesAreaSizingFactor());

  EXPECT_TRUE(evap.setDesignWaterFlowRate(0.03));
  ASSERT_TRUE(evap.designWaterFlowRate());
  EXPECT_DOUBLE_EQ(0.03, *evap.designWaterFlowRate());
  evap.resetDesignWaterFlowRate();
  EXPECT_FALSE(evap.designWaterFlowRate());
  evap.autosizeDesignWaterFlowRate();
  EXPECT_TRUE(evap.isDesignWaterFlowRateAutosized());

  EXPECT_TRUE(evap.setHighSpeedUserSpecifiedDesignCapacity(13000.0));
  ASSERT_TRUE(evap.highSpeedUserSpecifiedDesignCapacity());
  EXPECT_DOUBLE_EQ(13000.0, *evap.highSpeedUserSpecifiedDesignCapacity());
  evap.resetHighSpeedUserSpecifiedDesignCapacity();
  EXPECT_FALSE(evap.highSpeedUserSpecifiedDesignCapacity());

  EXPECT_TRUE(evap.setLowSpeedUserSpecifiedDesignCapacity(6800.0));
  ASSERT_TRUE(evap.lowSpeedUserSpecifiedDesignCapacity());
  EXPECT_DOUBLE_EQ(6800.0, *evap.lowSpeedUserSpecifiedDesignCapacity());
  evap.resetLowSpeedUserSpecifiedDesignCapacity();
  EXPECT_FALSE(evap.lowSpeedUserSpecifiedDesignCapacity());
  evap.autosizeLowSpeedUserSpecifiedDesignCapacity();
  EXPECT_TRUE(evap.isLowSpeedUserSpecifiedDesignCapacityAutosized());

  EXPECT_TRUE(evap.setLowSpeedUserSpecifiedDesignCapacitySizingFactor(0.46));
  EXPECT_DOUBLE_EQ(0.46, evap.lowSpeedUserSpecifiedDesignCapacitySizingFactor());

  EXPECT_TRUE(evap.setDesignEnteringWaterTemperature(30.5));
  ASSERT_TRUE(evap.designEnteringWaterTemperature());
  EXPECT_DOUBLE_EQ(30.5, *evap.designEnteringWaterTemperature());
  evap.autosizeDesignEnteringWaterTemperature();
  EXPECT_TRUE(evap.isDesignEnteringWaterTemperatureAutosized());

  EXPECT_TRUE(evap.setDesignEnteringAirTemperature(33.4));
  EXPECT_DOUBLE_EQ(33.4, evap.designEnteringAirTemperature());

  EXPECT_TRUE(evap.setDesignEnteringAirWetbulbTemperature(23.7));
  EXPECT_DOUBLE_EQ(23.7, evap.designEnteringAirWetbulbTemperature());

  EXPECT_TRUE(evap.setHighSpeedSizingFactor(1.08));
  EXPECT_DOUBLE_EQ(1.08, evap.highSpeedSizingFactor());

  EXPECT_TRUE(evap.setEvaporationLossMode("LossFactor"));
  EXPECT_EQ("LossFactor", evap.evaporationLossMode());

  EXPECT_TRUE(evap.setEvaporationLossFactor(0.23));
  ASSERT_TRUE(evap.evaporationLossFactor());
  EXPECT_DOUBLE_EQ(0.23, *evap.evaporationLossFactor());
  evap.resetEvaporationLossFactor();
  EXPECT_FALSE(evap.evaporationLossFactor());

  EXPECT_TRUE(evap.setDriftLossPercent(0.007));
  EXPECT_DOUBLE_EQ(0.007, evap.driftLossPercent());

  EXPECT_TRUE(evap.setBlowdownCalculationMode("ScheduledRate"));
  EXPECT_EQ("ScheduledRate", evap.blowdownCalculationMode());

  EXPECT_TRUE(evap.setBlowdownConcentrationRatio(4.2));
  EXPECT_DOUBLE_EQ(4.2, evap.blowdownConcentrationRatio());

  EXPECT_FALSE(evap.autosizedHighFanSpeedAirFlowRate());
  EXPECT_FALSE(evap.autosizedHighFanSpeedFanPower());
  EXPECT_FALSE(evap.autosizedLowFanSpeedAirFlowRate());
  EXPECT_FALSE(evap.autosizedLowFanSpeedFanPower());
  EXPECT_FALSE(evap.autosizedLowSpeedStandardDesignCapacity());
  EXPECT_FALSE(evap.autosizedHighFanSpeedUfactorTimesAreaValue());
  EXPECT_FALSE(evap.autosizedLowFanSpeedUfactorTimesAreaValue());
  EXPECT_FALSE(evap.autosizedDesignWaterFlowRate());
  EXPECT_FALSE(evap.autosizedLowSpeedUserSpecifiedDesignCapacity());
  EXPECT_FALSE(evap.autosizedDesignEnteringWaterTemperature());
}

TEST_F(EPModelFixture, EvaporativeFluidCoolerTwoSpeed_AddToNode_PlantSupplyOnly) {
  Model model;
  EvaporativeFluidCoolerTwoSpeed evap(model);

  AirLoopHVAC airLoop(model);
  Node airSupplyOutletNode = airLoop.supplyOutletNode();
  EXPECT_FALSE(evap.addToNode(airSupplyOutletNode));
  EXPECT_EQ(2u, airLoop.supplyComponents().size());
  EXPECT_FALSE(evap.loop());
  EXPECT_FALSE(evap.inletModelObject());
  EXPECT_FALSE(evap.outletModelObject());

  auto splitterBranch = airLoop.zoneSplitter().lastOutletModelObject();
  ASSERT_TRUE(splitterBranch);
  auto demandBranchNode = splitterBranch->optionalCast<Node>();
  ASSERT_TRUE(demandBranchNode);
  EXPECT_FALSE(evap.addToNode(*demandBranchNode));
  EXPECT_EQ(5u, airLoop.demandComponents().size());
  EXPECT_FALSE(evap.loop());
  EXPECT_FALSE(evap.inletModelObject());
  EXPECT_FALSE(evap.outletModelObject());

  PlantLoop plantLoop(model);
  Node plantSupplyOutletNode = plantLoop.supplyOutletNode();
  EXPECT_TRUE(evap.addToNode(plantSupplyOutletNode));
  EXPECT_EQ(7u, plantLoop.supplyComponents().size());
  ASSERT_TRUE(evap.loop());
  EXPECT_EQ(plantLoop.handle(), evap.loop()->handle());
  ASSERT_TRUE(evap.inletModelObject());
  ASSERT_TRUE(evap.outletModelObject());

  auto inletNode = evap.getModelObjectTarget<Node>(openstudio::EvaporativeFluidCooler_TwoSpeedFields::WaterInletNodeName);
  auto outletNode = evap.getModelObjectTarget<Node>(openstudio::EvaporativeFluidCooler_TwoSpeedFields::WaterOutletNodeName);
  ASSERT_TRUE(inletNode);
  ASSERT_TRUE(outletNode);
  EXPECT_EQ(evap.inletModelObject()->handle(), inletNode->handle());
  EXPECT_EQ(evap.outletModelObject()->handle(), outletNode->handle());

  EvaporativeFluidCoolerTwoSpeed secondEvap(model);
  Node plantDemandOutletNode = plantLoop.demandOutletNode();
  EXPECT_FALSE(secondEvap.addToNode(plantDemandOutletNode));
  EXPECT_EQ(5u, plantLoop.demandComponents().size());
  EXPECT_FALSE(secondEvap.loop());
  EXPECT_FALSE(secondEvap.inletModelObject());
  EXPECT_FALSE(secondEvap.outletModelObject());
}
