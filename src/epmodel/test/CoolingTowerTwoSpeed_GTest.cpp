/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ResourceObject/ScheduleTypeLimits.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"
#include "../StraightComponent/CoolingTowerTwoSpeed.hpp"
#include "../StraightComponent/Node.hpp"

#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/CoolingTower_TwoSpeed_FieldEnums.hxx>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoolingTowerTwoSpeed_DefaultConstructor) {
  Model model;
  CoolingTowerTwoSpeed coolingTower(model);
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::CoolingTower_TwoSpeed), coolingTower.iddObject().type());
  EXPECT_FALSE(coolingTower.nameString().empty());

  EXPECT_FALSE(coolingTower.designWaterFlowRate());
  EXPECT_TRUE(coolingTower.isDesignWaterFlowRateAutosized());
  EXPECT_FALSE(coolingTower.highFanSpeedAirFlowRate());
  EXPECT_TRUE(coolingTower.isHighFanSpeedAirFlowRateAutosized());
  EXPECT_FALSE(coolingTower.highFanSpeedFanPower());
  EXPECT_TRUE(coolingTower.isHighFanSpeedFanPowerAutosized());
  EXPECT_FALSE(coolingTower.highFanSpeedUFactorTimesAreaValue());
  EXPECT_TRUE(coolingTower.isHighFanSpeedUFactorTimesAreaValueAutosized());
  EXPECT_FALSE(coolingTower.lowFanSpeedAirFlowRate());
  EXPECT_TRUE(coolingTower.isLowFanSpeedAirFlowRateAutosized());
  EXPECT_EQ(0.5, coolingTower.lowFanSpeedAirFlowRateSizingFactor());
  EXPECT_TRUE(coolingTower.isLowFanSpeedAirFlowRateSizingFactorDefaulted());
  EXPECT_FALSE(coolingTower.lowFanSpeedFanPower());
  EXPECT_TRUE(coolingTower.isLowFanSpeedFanPowerAutosized());
  EXPECT_EQ(0.16, coolingTower.lowFanSpeedFanPowerSizingFactor());
  EXPECT_TRUE(coolingTower.isLowFanSpeedFanPowerSizingFactorDefaulted());
  EXPECT_FALSE(coolingTower.lowFanSpeedUFactorTimesAreaValue());
  EXPECT_TRUE(coolingTower.isLowFanSpeedUFactorTimesAreaValueAutosized());
  EXPECT_EQ(0.6, coolingTower.lowFanSpeedUFactorTimesAreaSizingFactor());
  EXPECT_TRUE(coolingTower.isLowFanSpeedUFactorTimesAreaSizingFactorDefaulted());

  ASSERT_TRUE(coolingTower.freeConvectionRegimeAirFlowRate());
  EXPECT_EQ(0.0, coolingTower.freeConvectionRegimeAirFlowRate().get());
  EXPECT_TRUE(coolingTower.isFreeConvectionRegimeAirFlowRateDefaulted());
  EXPECT_FALSE(coolingTower.isFreeConvectionRegimeAirFlowRateAutosized());
  EXPECT_EQ(0.1, coolingTower.freeConvectionRegimeAirFlowRateSizingFactor());
  EXPECT_TRUE(coolingTower.isFreeConvectionRegimeAirFlowRateSizingFactorDefaulted());

  ASSERT_TRUE(coolingTower.freeConvectionRegimeUFactorTimesAreaValue());
  EXPECT_EQ(0.0, coolingTower.freeConvectionRegimeUFactorTimesAreaValue().get());
  EXPECT_TRUE(coolingTower.isFreeConvectionRegimeUFactorTimesAreaValueDefaulted());
  EXPECT_FALSE(coolingTower.isFreeConvectionRegimeUFactorTimesAreaValueAutosized());
  EXPECT_EQ(0.1, coolingTower.freeConvectionUFactorTimesAreaValueSizingFactor());
  EXPECT_TRUE(coolingTower.isFreeConvectionUFactorTimesAreaValueSizingFactorDefaulted());
  EXPECT_EQ(1.0, coolingTower.sizingFactor());
  EXPECT_EQ(35.0, coolingTower.designInletAirDryBulbTemperature());
  EXPECT_EQ(25.6, coolingTower.designInletAirWetBulbTemperature());
  EXPECT_FALSE(coolingTower.designApproachTemperature());
  EXPECT_TRUE(coolingTower.isDesignApproachTemperatureAutosized());
  EXPECT_FALSE(coolingTower.designRangeTemperature());
  EXPECT_TRUE(coolingTower.isDesignRangeTemperatureAutosized());
  EXPECT_EQ("General", coolingTower.endUseSubcategory());
  EXPECT_EQ("UFactorTimesAreaAndDesignWaterFlowRate", coolingTower.performanceInputMethod());
  EXPECT_TRUE(coolingTower.isPerformanceInputMethodDefaulted());
  EXPECT_EQ(1.25, coolingTower.heatRejectionCapacityandNominalCapacitySizingRatio());
  EXPECT_TRUE(coolingTower.isHeatRejectionCapacityandNominalCapacitySizingRatioDefaulted());
  EXPECT_FALSE(coolingTower.highSpeedNominalCapacity());
  EXPECT_FALSE(coolingTower.lowSpeedNominalCapacity());
  EXPECT_FALSE(coolingTower.isLowSpeedNominalCapacityAutosized());
  EXPECT_EQ(0.5, coolingTower.lowSpeedNominalCapacitySizingFactor());
  EXPECT_TRUE(coolingTower.isLowSpeedNominalCapacitySizingFactorDefaulted());
  EXPECT_FALSE(coolingTower.freeConvectionNominalCapacity());
  EXPECT_FALSE(coolingTower.isFreeConvectionNominalCapacityAutosized());
  EXPECT_EQ(0.1, coolingTower.freeConvectionNominalCapacitySizingFactor());
  EXPECT_TRUE(coolingTower.isFreeConvectionNominalCapacitySizingFactorDefaulted());
  EXPECT_EQ(0.0, coolingTower.basinHeaterCapacity());
  EXPECT_TRUE(coolingTower.isBasinHeaterCapacityDefaulted());
  EXPECT_EQ(2.0, coolingTower.basinHeaterSetpointTemperature());
  EXPECT_TRUE(coolingTower.isBasinHeaterSetpointTemperatureDefaulted());
  EXPECT_FALSE(coolingTower.basinHeaterOperatingSchedule());
  EXPECT_EQ("SaturatedExit", coolingTower.evaporationLossMode());
  EXPECT_TRUE(coolingTower.isEvaporationLossModeDefaulted());
  EXPECT_EQ(0.2, coolingTower.evaporationLossFactor());
  EXPECT_TRUE(coolingTower.isEvaporationLossFactorDefaulted());
  EXPECT_EQ(0.008, coolingTower.driftLossPercent());
  EXPECT_TRUE(coolingTower.isDriftLossPercentDefaulted());
  EXPECT_EQ("ConcentrationRatio", coolingTower.blowdownCalculationMode());
  EXPECT_TRUE(coolingTower.isBlowdownCalculationModeDefaulted());
  EXPECT_EQ(3.0, coolingTower.blowdownConcentrationRatio());
  EXPECT_TRUE(coolingTower.isBlowdownConcentrationRatioDefaulted());
  EXPECT_FALSE(coolingTower.blowdownMakeupWaterUsageSchedule());
  EXPECT_EQ(1, coolingTower.numberofCells());
  EXPECT_TRUE(coolingTower.isNumberofCellsDefaulted());
  EXPECT_EQ("MinimalCell", coolingTower.cellControl());
  EXPECT_TRUE(coolingTower.isCellControlDefaulted());
  EXPECT_EQ(0.33, coolingTower.cellMinimumWaterFlowRateFraction());
  EXPECT_TRUE(coolingTower.isCellMinimumWaterFlowRateFractionDefaulted());
  EXPECT_EQ(2.5, coolingTower.cellMaximumWaterFlowRateFraction());
  EXPECT_TRUE(coolingTower.isCellMaximumWaterFlowRateFractionDefaulted());
}

TEST_F(EPModelFixture, CoolingTowerTwoSpeed_ScalarAccessors_RoundTrip) {
  Model model;
  CoolingTowerTwoSpeed coolingTower(model);

  EXPECT_FALSE(CoolingTowerTwoSpeed::performanceInputMethodValues().empty());
  EXPECT_FALSE(CoolingTowerTwoSpeed::evaporationLossModeValues().empty());
  EXPECT_FALSE(CoolingTowerTwoSpeed::blowdownCalculationModeValues().empty());
  EXPECT_FALSE(CoolingTowerTwoSpeed::cellControlValues().empty());

  coolingTower.autosizeDesignWaterFlowRate();
  EXPECT_TRUE(coolingTower.isDesignWaterFlowRateAutosized());
  EXPECT_TRUE(coolingTower.setDesignWaterFlowRate(0.02));
  ASSERT_TRUE(coolingTower.designWaterFlowRate());
  EXPECT_DOUBLE_EQ(0.02, *coolingTower.designWaterFlowRate());
  EXPECT_FALSE(coolingTower.isDesignWaterFlowRateAutosized());
  coolingTower.resetDesignWaterFlowRate();
  EXPECT_FALSE(coolingTower.designWaterFlowRate());

  EXPECT_TRUE(coolingTower.setHighFanSpeedAirFlowRate(4.2));
  ASSERT_TRUE(coolingTower.highFanSpeedAirFlowRate());
  EXPECT_DOUBLE_EQ(4.2, *coolingTower.highFanSpeedAirFlowRate());

  EXPECT_TRUE(coolingTower.setHighFanSpeedFanPower(1200.0));
  ASSERT_TRUE(coolingTower.highFanSpeedFanPower());
  EXPECT_DOUBLE_EQ(1200.0, *coolingTower.highFanSpeedFanPower());

  coolingTower.autosizeLowFanSpeedAirFlowRate();
  EXPECT_TRUE(coolingTower.isLowFanSpeedAirFlowRateAutosized());
  auto lowFanSpeedAirFlowRateToken = coolingTower.getString(openstudio::CoolingTower_TwoSpeedFields::LowFanSpeedAirFlowRate, false);
  ASSERT_TRUE(lowFanSpeedAirFlowRateToken);
  EXPECT_TRUE(openstudio::istringEqual(*lowFanSpeedAirFlowRateToken, "autocalculate"));
  EXPECT_TRUE(coolingTower.setLowFanSpeedAirFlowRate(2.1));
  ASSERT_TRUE(coolingTower.lowFanSpeedAirFlowRate());
  EXPECT_DOUBLE_EQ(2.1, *coolingTower.lowFanSpeedAirFlowRate());

  coolingTower.autosizeLowFanSpeedFanPower();
  EXPECT_TRUE(coolingTower.isLowFanSpeedFanPowerAutosized());
  auto lowFanSpeedFanPowerToken = coolingTower.getString(openstudio::CoolingTower_TwoSpeedFields::LowFanSpeedFanPower, false);
  ASSERT_TRUE(lowFanSpeedFanPowerToken);
  EXPECT_TRUE(openstudio::istringEqual(*lowFanSpeedFanPowerToken, "autocalculate"));

  coolingTower.autosizeFreeConvectionRegimeAirFlowRate();
  EXPECT_TRUE(coolingTower.isFreeConvectionRegimeAirFlowRateAutosized());
  auto freeConvectionAirFlowRateToken = coolingTower.getString(openstudio::CoolingTower_TwoSpeedFields::FreeConvectionRegimeAirFlowRate, false);
  ASSERT_TRUE(freeConvectionAirFlowRateToken);
  EXPECT_TRUE(openstudio::istringEqual(*freeConvectionAirFlowRateToken, "autocalculate"));
  coolingTower.resetFreeConvectionRegimeAirFlowRate();
  ASSERT_TRUE(coolingTower.freeConvectionRegimeAirFlowRate());
  EXPECT_DOUBLE_EQ(0.0, *coolingTower.freeConvectionRegimeAirFlowRate());
  EXPECT_TRUE(coolingTower.isFreeConvectionRegimeAirFlowRateDefaulted());

  EXPECT_TRUE(coolingTower.setPerformanceInputMethod("NominalCapacity"));
  EXPECT_EQ("NominalCapacity", coolingTower.performanceInputMethod());
  EXPECT_FALSE(coolingTower.isPerformanceInputMethodDefaulted());
  coolingTower.resetPerformanceInputMethod();
  EXPECT_TRUE(coolingTower.isPerformanceInputMethodDefaulted());

  coolingTower.autosizeLowSpeedNominalCapacity();
  EXPECT_TRUE(coolingTower.isLowSpeedNominalCapacityAutosized());
  EXPECT_TRUE(coolingTower.setLowSpeedNominalCapacity(12000.0));
  ASSERT_TRUE(coolingTower.lowSpeedNominalCapacity());
  EXPECT_DOUBLE_EQ(12000.0, *coolingTower.lowSpeedNominalCapacity());

  coolingTower.autosizeFreeConvectionNominalCapacity();
  EXPECT_TRUE(coolingTower.isFreeConvectionNominalCapacityAutosized());
  EXPECT_TRUE(coolingTower.setFreeConvectionNominalCapacity(2400.0));
  ASSERT_TRUE(coolingTower.freeConvectionNominalCapacity());
  EXPECT_DOUBLE_EQ(2400.0, *coolingTower.freeConvectionNominalCapacity());

  EXPECT_TRUE(coolingTower.setEvaporationLossMode("LossFactor"));
  EXPECT_EQ("LossFactor", coolingTower.evaporationLossMode());

  EXPECT_TRUE(coolingTower.setBlowdownCalculationMode("ConcentrationRatio"));
  EXPECT_EQ("ConcentrationRatio", coolingTower.blowdownCalculationMode());

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

TEST_F(EPModelFixture, CoolingTowerTwoSpeed_RelationshipSetters_RoundTrip) {
  Model model;
  CoolingTowerTwoSpeed coolingTower(model);
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

TEST_F(EPModelFixture, CoolingTowerTwoSpeed_ScheduleRelationships_MatchCanonicalCompatibility) {
  Model model;
  CoolingTowerTwoSpeed coolingTower(model);

  ScheduleConstant continuousAvailabilitySchedule(model);
  ASSERT_TRUE(continuousAvailabilitySchedule.setValue(1.0));
  ScheduleTypeLimits continuousAvailabilityLimits(model);
  ASSERT_TRUE(continuousAvailabilityLimits.setUnitType("Availability"));
  ASSERT_TRUE(continuousAvailabilityLimits.setNumericType("Continuous"));
  ASSERT_TRUE(continuousAvailabilityLimits.setLowerLimitValue(0.0));
  ASSERT_TRUE(continuousAvailabilityLimits.setUpperLimitValue(1.0));
  ASSERT_TRUE(continuousAvailabilitySchedule.setScheduleTypeLimits(continuousAvailabilityLimits));

  EXPECT_TRUE(coolingTower.setBasinHeaterOperatingSchedule(continuousAvailabilitySchedule));
  ASSERT_TRUE(coolingTower.basinHeaterOperatingSchedule());
  EXPECT_EQ(continuousAvailabilitySchedule.handle(), coolingTower.basinHeaterOperatingSchedule()->handle());

  ScheduleConstant discreteVolumetricFlowSchedule(model);
  ASSERT_TRUE(discreteVolumetricFlowSchedule.setValue(0.0025));
  ScheduleTypeLimits discreteVolumetricFlowLimits(model);
  ASSERT_TRUE(discreteVolumetricFlowLimits.setUnitType("VolumetricFlowRate"));
  ASSERT_TRUE(discreteVolumetricFlowLimits.setNumericType("Discrete"));
  ASSERT_TRUE(discreteVolumetricFlowLimits.setLowerLimitValue(0.0));
  ASSERT_TRUE(discreteVolumetricFlowSchedule.setScheduleTypeLimits(discreteVolumetricFlowLimits));

  EXPECT_TRUE(coolingTower.setBlowdownMakeupWaterUsageSchedule(discreteVolumetricFlowSchedule));
  ASSERT_TRUE(coolingTower.blowdownMakeupWaterUsageSchedule());
  EXPECT_EQ(discreteVolumetricFlowSchedule.handle(), coolingTower.blowdownMakeupWaterUsageSchedule()->handle());

  ScheduleConstant temperatureSchedule(model);
  ASSERT_TRUE(temperatureSchedule.setValue(12.0));
  ScheduleTypeLimits temperatureLimits(model);
  ASSERT_TRUE(temperatureLimits.setUnitType("Temperature"));
  ASSERT_TRUE(temperatureSchedule.setScheduleTypeLimits(temperatureLimits));

  EXPECT_FALSE(coolingTower.setBasinHeaterOperatingSchedule(temperatureSchedule));
  ASSERT_TRUE(coolingTower.basinHeaterOperatingSchedule());
  EXPECT_EQ(continuousAvailabilitySchedule.handle(), coolingTower.basinHeaterOperatingSchedule()->handle());

  EXPECT_FALSE(coolingTower.setBlowdownMakeupWaterUsageSchedule(temperatureSchedule));
  ASSERT_TRUE(coolingTower.blowdownMakeupWaterUsageSchedule());
  EXPECT_EQ(discreteVolumetricFlowSchedule.handle(), coolingTower.blowdownMakeupWaterUsageSchedule()->handle());
}

TEST_F(EPModelFixture, CoolingTowerTwoSpeed_AddToNode_PlantSupplyOnly) {
  Model model;
  CoolingTowerTwoSpeed coolingTower(model);

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

  CoolingTowerTwoSpeed secondTower(model);
  auto plantDemandOutletNode = plantLoop.demandOutletNode();
  EXPECT_FALSE(secondTower.addToNode(plantDemandOutletNode));
  EXPECT_EQ(5u, plantLoop.demandComponents().size());
}
