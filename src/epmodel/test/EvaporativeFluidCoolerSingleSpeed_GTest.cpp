/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"
#include "../StraightComponent/EvaporativeFluidCoolerSingleSpeed.hpp"
#include "../StraightComponent/Node.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, EvaporativeFluidCoolerSingleSpeed_DefaultConstructor) {
  Model model;
  EvaporativeFluidCoolerSingleSpeed evap(model);

  EXPECT_EQ(EvaporativeFluidCoolerSingleSpeed::iddObjectType(), evap.iddObject().type());
  EXPECT_FALSE(evap.nameString().empty());

  EXPECT_FALSE(evap.designAirFlowRate());
  EXPECT_TRUE(evap.isDesignAirFlowRateAutosized());

  EXPECT_FALSE(evap.fanPoweratDesignAirFlowRate());
  EXPECT_TRUE(evap.isFanPoweratDesignAirFlowRateAutosized());

  EXPECT_DOUBLE_EQ(0.03, evap.designSprayWaterFlowRate());
  EXPECT_EQ("UFactorTimesAreaAndDesignWaterFlowRate", evap.performanceInputMethod());
  EXPECT_DOUBLE_EQ(1.25, evap.heatRejectionCapacityandNominalCapacitySizingRatio());

  EXPECT_FALSE(evap.standardDesignCapacity());
  EXPECT_FALSE(evap.ufactorTimesAreaValueatDesignAirFlowRate());
  EXPECT_TRUE(evap.isUfactorTimesAreaValueatDesignAirFlowRateAutosized());

  EXPECT_FALSE(evap.designWaterFlowRate());
  EXPECT_TRUE(evap.isDesignWaterFlowRateAutosized());

  EXPECT_FALSE(evap.userSpecifiedDesignCapacity());
  EXPECT_FALSE(evap.designEnteringWaterTemperature());
  EXPECT_TRUE(evap.isDesignEnteringWaterTemperatureAutosized());

  EXPECT_DOUBLE_EQ(35.0, evap.designEnteringAirTemperature());
  EXPECT_DOUBLE_EQ(25.6, evap.designEnteringAirWetbulbTemperature());
  EXPECT_EQ("FanCycling", evap.capacityControl());
  EXPECT_DOUBLE_EQ(1.0, evap.sizingFactor());
  EXPECT_EQ("SaturatedExit", evap.evaporationLossMode());
  EXPECT_FALSE(evap.evaporationLossFactor());
  EXPECT_DOUBLE_EQ(0.008, evap.driftLossPercent());
  EXPECT_EQ("ConcentrationRatio", evap.blowdownCalculationMode());
  EXPECT_DOUBLE_EQ(3.0, evap.blowdownConcentrationRatio());
}

TEST_F(EPModelFixture, EvaporativeFluidCoolerSingleSpeed_ScalarAccessors_RoundTrip) {
  Model model;
  EvaporativeFluidCoolerSingleSpeed evap(model);

  EXPECT_TRUE(evap.setDesignAirFlowRate(1.35));
  ASSERT_TRUE(evap.designAirFlowRate());
  EXPECT_DOUBLE_EQ(1.35, *evap.designAirFlowRate());
  EXPECT_FALSE(evap.isDesignAirFlowRateAutosized());
  evap.autosizeDesignAirFlowRate();
  EXPECT_TRUE(evap.isDesignAirFlowRateAutosized());
  EXPECT_FALSE(evap.designAirFlowRate());

  EXPECT_TRUE(evap.setFanPoweratDesignAirFlowRate(210.0));
  ASSERT_TRUE(evap.fanPoweratDesignAirFlowRate());
  EXPECT_DOUBLE_EQ(210.0, *evap.fanPoweratDesignAirFlowRate());
  evap.autosizeFanPoweratDesignAirFlowRate();
  EXPECT_TRUE(evap.isFanPoweratDesignAirFlowRateAutosized());
  EXPECT_FALSE(evap.fanPoweratDesignAirFlowRate());

  EXPECT_TRUE(evap.setDesignSprayWaterFlowRate(0.06));
  EXPECT_DOUBLE_EQ(0.06, evap.designSprayWaterFlowRate());

  EXPECT_TRUE(evap.setPerformanceInputMethod("StandardDesignCapacity"));
  EXPECT_EQ("StandardDesignCapacity", evap.performanceInputMethod());

  EXPECT_TRUE(evap.setHeatRejectionCapacityandNominalCapacitySizingRatio(1.2));
  EXPECT_DOUBLE_EQ(1.2, evap.heatRejectionCapacityandNominalCapacitySizingRatio());

  EXPECT_TRUE(evap.setStandardDesignCapacity(9000.0));
  ASSERT_TRUE(evap.standardDesignCapacity());
  EXPECT_DOUBLE_EQ(9000.0, *evap.standardDesignCapacity());
  evap.resetStandardDesignCapacity();
  EXPECT_FALSE(evap.standardDesignCapacity());

  EXPECT_TRUE(evap.setUfactorTimesAreaValueatDesignAirFlowRate(1800.0));
  ASSERT_TRUE(evap.ufactorTimesAreaValueatDesignAirFlowRate());
  EXPECT_DOUBLE_EQ(1800.0, *evap.ufactorTimesAreaValueatDesignAirFlowRate());
  evap.resetUfactorTimesAreaValueatDesignAirFlowRate();
  EXPECT_FALSE(evap.ufactorTimesAreaValueatDesignAirFlowRate());
  evap.autosizeUfactorTimesAreaValueatDesignAirFlowRate();
  EXPECT_TRUE(evap.isUfactorTimesAreaValueatDesignAirFlowRateAutosized());
  EXPECT_FALSE(evap.ufactorTimesAreaValueatDesignAirFlowRate());

  EXPECT_TRUE(evap.setDesignWaterFlowRate(0.04));
  ASSERT_TRUE(evap.designWaterFlowRate());
  EXPECT_DOUBLE_EQ(0.04, *evap.designWaterFlowRate());
  evap.resetDesignWaterFlowRate();
  EXPECT_FALSE(evap.designWaterFlowRate());
  evap.autosizeDesignWaterFlowRate();
  EXPECT_TRUE(evap.isDesignWaterFlowRateAutosized());
  EXPECT_FALSE(evap.designWaterFlowRate());

  EXPECT_TRUE(evap.setUserSpecifiedDesignCapacity(10000.0));
  ASSERT_TRUE(evap.userSpecifiedDesignCapacity());
  EXPECT_DOUBLE_EQ(10000.0, *evap.userSpecifiedDesignCapacity());
  evap.resetUserSpecifiedDesignCapacity();
  EXPECT_FALSE(evap.userSpecifiedDesignCapacity());

  EXPECT_TRUE(evap.setDesignEnteringWaterTemperature(30.2));
  ASSERT_TRUE(evap.designEnteringWaterTemperature());
  EXPECT_DOUBLE_EQ(30.2, *evap.designEnteringWaterTemperature());
  EXPECT_FALSE(evap.isDesignEnteringWaterTemperatureAutosized());
  evap.autosizeDesignEnteringWaterTemperature();
  EXPECT_TRUE(evap.isDesignEnteringWaterTemperatureAutosized());
  EXPECT_FALSE(evap.designEnteringWaterTemperature());

  EXPECT_TRUE(evap.setDesignEnteringAirTemperature(33.1));
  EXPECT_DOUBLE_EQ(33.1, evap.designEnteringAirTemperature());

  EXPECT_TRUE(evap.setDesignEnteringAirWetbulbTemperature(22.4));
  EXPECT_DOUBLE_EQ(22.4, evap.designEnteringAirWetbulbTemperature());

  EXPECT_TRUE(evap.setCapacityControl("FluidBypass"));
  EXPECT_EQ("FluidBypass", evap.capacityControl());
  evap.resetCapacityControl();
  EXPECT_TRUE(evap.isCapacityControlDefaulted());

  EXPECT_TRUE(evap.setSizingFactor(1.1));
  EXPECT_DOUBLE_EQ(1.1, evap.sizingFactor());
  evap.resetSizingFactor();
  EXPECT_TRUE(evap.isSizingFactorDefaulted());

  EXPECT_TRUE(evap.setEvaporationLossMode("LossFactor"));
  EXPECT_EQ("LossFactor", evap.evaporationLossMode());
  evap.resetEvaporationLossMode();
  EXPECT_TRUE(evap.isEvaporationLossModeDefaulted());

  EXPECT_TRUE(evap.setEvaporationLossFactor(0.25));
  ASSERT_TRUE(evap.evaporationLossFactor());
  EXPECT_DOUBLE_EQ(0.25, *evap.evaporationLossFactor());
  evap.resetEvaporationLossFactor();
  EXPECT_FALSE(evap.evaporationLossFactor());

  EXPECT_TRUE(evap.setDriftLossPercent(0.007));
  EXPECT_DOUBLE_EQ(0.007, evap.driftLossPercent());
  evap.resetDriftLossPercent();
  EXPECT_TRUE(evap.isDriftLossPercentDefaulted());

  EXPECT_TRUE(evap.setBlowdownCalculationMode("ScheduledRate"));
  EXPECT_EQ("ScheduledRate", evap.blowdownCalculationMode());
  evap.resetBlowdownCalculationMode();
  EXPECT_TRUE(evap.isBlowdownCalculationModeDefaulted());

  EXPECT_TRUE(evap.setBlowdownConcentrationRatio(4.1));
  EXPECT_DOUBLE_EQ(4.1, evap.blowdownConcentrationRatio());
  evap.resetBlowdownConcentrationRatio();
  EXPECT_TRUE(evap.isBlowdownConcentrationRatioDefaulted());

  EXPECT_FALSE(evap.autosizedDesignAirFlowRate());
  EXPECT_FALSE(evap.autosizedFanPoweratDesignAirFlowRate());
  EXPECT_FALSE(evap.autosizedUfactorTimesAreaValueatDesignAirFlowRate());
  EXPECT_FALSE(evap.autosizedDesignWaterFlowRate());
  EXPECT_FALSE(evap.autosizedDesignEnteringWaterTemperature());
}

TEST_F(EPModelFixture, EvaporativeFluidCoolerSingleSpeed_AddToNode_PlantSupplyOnly) {
  Model model;
  EvaporativeFluidCoolerSingleSpeed evap(model);

  AirLoopHVAC airLoop(model);
  auto airSupplyOutletNode = airLoop.supplyOutletNode();
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
  auto plantSupplyOutletNode = plantLoop.supplyOutletNode();
  EXPECT_TRUE(evap.addToNode(plantSupplyOutletNode));
  EXPECT_EQ(7u, plantLoop.supplyComponents().size());
  ASSERT_TRUE(evap.loop());
  EXPECT_EQ(plantLoop.handle(), evap.loop()->handle());
  ASSERT_TRUE(evap.inletModelObject());
  ASSERT_TRUE(evap.outletModelObject());

  EvaporativeFluidCoolerSingleSpeed secondEvap(model);
  auto plantDemandOutletNode = plantLoop.demandOutletNode();
  EXPECT_FALSE(secondEvap.addToNode(plantDemandOutletNode));
  EXPECT_EQ(5u, plantLoop.demandComponents().size());
  EXPECT_FALSE(secondEvap.loop());
  EXPECT_FALSE(secondEvap.inletModelObject());
  EXPECT_FALSE(secondEvap.outletModelObject());
}

TEST_F(EPModelFixture, EvaporativeFluidCoolerSingleSpeed_InvalidInputsRejected) {
  Model model;
  EvaporativeFluidCoolerSingleSpeed evap(model);

  EXPECT_FALSE(evap.setDesignAirFlowRate(0.0));
  EXPECT_FALSE(evap.setDesignAirFlowRate(-1.0));
  EXPECT_TRUE(evap.isDesignAirFlowRateAutosized());

  EXPECT_FALSE(evap.setFanPoweratDesignAirFlowRate(0.0));
  EXPECT_FALSE(evap.setFanPoweratDesignAirFlowRate(-1.0));
  EXPECT_TRUE(evap.isFanPoweratDesignAirFlowRateAutosized());

  EXPECT_FALSE(evap.setDesignSprayWaterFlowRate(0.0));
  EXPECT_FALSE(evap.setDesignSprayWaterFlowRate(-1.0));
  EXPECT_DOUBLE_EQ(0.03, evap.designSprayWaterFlowRate());

  EXPECT_FALSE(evap.setPerformanceInputMethod("Not Valid Entry"));
  EXPECT_EQ("UFactorTimesAreaAndDesignWaterFlowRate", evap.performanceInputMethod());

  EXPECT_FALSE(evap.setCapacityControl("Not Valid Entry"));
  EXPECT_EQ("FanCycling", evap.capacityControl());

  EXPECT_FALSE(evap.setEvaporationLossMode("Not Valid Entry"));
  EXPECT_EQ("SaturatedExit", evap.evaporationLossMode());

  EXPECT_FALSE(evap.setBlowdownCalculationMode("Not Valid Entry"));
  EXPECT_EQ("ConcentrationRatio", evap.blowdownCalculationMode());
}
