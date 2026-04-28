/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"
#include "../StraightComponent/CoolingTowerSingleSpeed.hpp"
#include "../StraightComponent/Node.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoolingTowerSingleSpeed_DefaultConstructor) {
  Model model;
  CoolingTowerSingleSpeed coolingTower(model);
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::CoolingTower_SingleSpeed), coolingTower.iddObject().type());
  EXPECT_FALSE(coolingTower.nameString().empty());
  EXPECT_EQ("UFactorTimesAreaAndDesignWaterFlowRate", coolingTower.performanceInputMethod());
  EXPECT_FALSE(coolingTower.isPerformanceInputMethodDefaulted());
  EXPECT_FALSE(coolingTower.basinHeaterOperatingSchedule());
  EXPECT_FALSE(coolingTower.blowdownMakeupWaterUsageSchedule());
}

TEST_F(EPModelFixture, CoolingTowerSingleSpeed_ScalarAccessors_RoundTrip) {
  Model model;
  CoolingTowerSingleSpeed coolingTower(model);

  EXPECT_FALSE(CoolingTowerSingleSpeed::performanceInputMethodValues().empty());
  EXPECT_FALSE(CoolingTowerSingleSpeed::evaporationLossModeValues().empty());

  EXPECT_TRUE(coolingTower.setPerformanceInputMethod("NominalCapacity"));
  EXPECT_EQ("NominalCapacity", coolingTower.performanceInputMethod());
  EXPECT_FALSE(coolingTower.isPerformanceInputMethodDefaulted());
  coolingTower.resetPerformanceInputMethod();
  EXPECT_TRUE(coolingTower.isPerformanceInputMethodDefaulted());

  coolingTower.autosizeDesignWaterFlowRate();
  EXPECT_TRUE(coolingTower.isDesignWaterFlowRateAutosized());
  EXPECT_TRUE(coolingTower.setDesignWaterFlowRate(0.0123));
  ASSERT_TRUE(coolingTower.designWaterFlowRate());
  EXPECT_DOUBLE_EQ(0.0123, *coolingTower.designWaterFlowRate());
  EXPECT_FALSE(coolingTower.isDesignWaterFlowRateAutosized());
  coolingTower.resetDesignWaterFlowRate();
  EXPECT_FALSE(coolingTower.designWaterFlowRate());

  EXPECT_TRUE(coolingTower.setFanPoweratDesignAirFlowRate(4200.0));
  ASSERT_TRUE(coolingTower.fanPoweratDesignAirFlowRate());
  EXPECT_DOUBLE_EQ(4200.0, *coolingTower.fanPoweratDesignAirFlowRate());

  EXPECT_TRUE(coolingTower.setUFactorTimesAreaValueatDesignAirFlowRate(1234.0));
  ASSERT_TRUE(coolingTower.uFactorTimesAreaValueatDesignAirFlowRate());
  EXPECT_DOUBLE_EQ(1234.0, *coolingTower.uFactorTimesAreaValueatDesignAirFlowRate());
  coolingTower.autosizeUFactorTimesAreaValueatDesignAirFlowRate();
  EXPECT_TRUE(coolingTower.isUFactorTimesAreaValueatDesignAirFlowRateAutosized());

  EXPECT_TRUE(coolingTower.setEvaporationLossMode("LossFactor"));
  EXPECT_EQ("LossFactor", coolingTower.evaporationLossMode());

  EXPECT_TRUE(coolingTower.setBlowdownCalculationMode("ConcentrationRatio"));
  EXPECT_EQ("ConcentrationRatio", coolingTower.blowdownCalculationMode());

  EXPECT_TRUE(coolingTower.setCapacityControl("FanCycling"));
  EXPECT_EQ("FanCycling", coolingTower.capacityControl());

  EXPECT_TRUE(coolingTower.setNumberofCells(2));
  EXPECT_EQ(2, coolingTower.numberofCells());

  EXPECT_TRUE(coolingTower.setCellControl("MaximalCell"));
  EXPECT_EQ("MaximalCell", coolingTower.cellControl());

  EXPECT_TRUE(coolingTower.setDesignInletAirDryBulbTemperature(35.0));
  EXPECT_DOUBLE_EQ(35.0, coolingTower.designInletAirDryBulbTemperature());

  EXPECT_TRUE(coolingTower.setDesignInletAirWetBulbTemperature(25.6));
  EXPECT_DOUBLE_EQ(25.6, coolingTower.designInletAirWetBulbTemperature());

  coolingTower.autosizeDesignApproachTemperature();
  EXPECT_TRUE(coolingTower.isDesignApproachTemperatureAutosized());
  EXPECT_TRUE(coolingTower.setDesignApproachTemperature(5.0));
  ASSERT_TRUE(coolingTower.designApproachTemperature());
  EXPECT_DOUBLE_EQ(5.0, *coolingTower.designApproachTemperature());

  coolingTower.autosizeDesignRangeTemperature();
  EXPECT_TRUE(coolingTower.isDesignRangeTemperatureAutosized());
  EXPECT_TRUE(coolingTower.setDesignRangeTemperature(5.5));
  ASSERT_TRUE(coolingTower.designRangeTemperature());
  EXPECT_DOUBLE_EQ(5.5, *coolingTower.designRangeTemperature());

  EXPECT_TRUE(coolingTower.setEndUseSubcategory("Heat Rejection"));
  EXPECT_EQ("Heat Rejection", coolingTower.endUseSubcategory());
}

TEST_F(EPModelFixture, CoolingTowerSingleSpeed_RelationshipSetters_RoundTrip) {
  Model model;
  CoolingTowerSingleSpeed coolingTower(model);
  ScheduleConstant basinSchedule(model);
  ScheduleConstant blowdownSchedule(model);
  ASSERT_TRUE(basinSchedule.setValue(0.25));
  ASSERT_TRUE(blowdownSchedule.setValue(0.5));

  EXPECT_TRUE(coolingTower.setBasinHeaterOperatingSchedule(basinSchedule));
  ASSERT_TRUE(coolingTower.basinHeaterOperatingSchedule());
  EXPECT_EQ(basinSchedule.handle(), coolingTower.basinHeaterOperatingSchedule()->handle());

  EXPECT_TRUE(coolingTower.setBlowdownMakeupWaterUsageSchedule(blowdownSchedule));
  ASSERT_TRUE(coolingTower.blowdownMakeupWaterUsageSchedule());
  EXPECT_EQ(blowdownSchedule.handle(), coolingTower.blowdownMakeupWaterUsageSchedule()->handle());

  coolingTower.resetBasinHeaterOperatingSchedule();
  coolingTower.resetBlowdownMakeupWaterUsageSchedule();
  EXPECT_FALSE(coolingTower.basinHeaterOperatingSchedule());
  EXPECT_FALSE(coolingTower.blowdownMakeupWaterUsageSchedule());
}

TEST_F(EPModelFixture, CoolingTowerSingleSpeed_AddToNode_PlantSupplyOnly) {
  Model model;
  CoolingTowerSingleSpeed coolingTower(model);

  AirLoopHVAC airLoop(model);
  auto airSupplyOutletNode = airLoop.supplyOutletNode();
  EXPECT_FALSE(coolingTower.addToNode(airSupplyOutletNode));
  EXPECT_EQ(2u, airLoop.supplyComponents().size());

  auto splitterBranch = airLoop.zoneSplitter().lastOutletModelObject();
  ASSERT_TRUE(splitterBranch);
  auto demandBranchNode = splitterBranch->optionalCast<Node>();
  ASSERT_TRUE(demandBranchNode);
  EXPECT_FALSE(coolingTower.addToNode(*demandBranchNode));
  EXPECT_EQ(5u, airLoop.demandComponents().size());

  PlantLoop plantLoop(model);
  auto plantSupplyOutletNode = plantLoop.supplyOutletNode();
  EXPECT_TRUE(coolingTower.addToNode(plantSupplyOutletNode));
  EXPECT_EQ(7u, plantLoop.supplyComponents().size());
  ASSERT_TRUE(coolingTower.inletModelObject());
  ASSERT_TRUE(coolingTower.outletModelObject());

  CoolingTowerSingleSpeed secondTower(model);
  auto plantDemandOutletNode = plantLoop.demandOutletNode();
  EXPECT_FALSE(secondTower.addToNode(plantDemandOutletNode));
  EXPECT_EQ(5u, plantLoop.demandComponents().size());
}
