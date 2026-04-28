/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Curve/CurveCubic.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../ModelObject/CoolingTowerPerformanceYorkCalc.hpp"
#include "../ResourceObject/ScheduleTypeLimits.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"
#include "../StraightComponent/CoolingTowerVariableSpeed.hpp"
#include "../StraightComponent/Node.hpp"

#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/CoolingTower_VariableSpeed_FieldEnums.hxx>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoolingTowerVariableSpeed_DefaultConstructor) {
  Model model;
  CoolingTowerVariableSpeed coolingTower(model);
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::CoolingTower_VariableSpeed), coolingTower.iddObject().type());
  EXPECT_FALSE(coolingTower.nameString().empty());

  ASSERT_TRUE(coolingTower.modelType());
  EXPECT_EQ("CoolToolsCrossFlow", coolingTower.modelType().get());
  EXPECT_FALSE(coolingTower.modelCoefficient());

  ASSERT_TRUE(coolingTower.designInletAirWetBulbTemperature());
  EXPECT_DOUBLE_EQ(25.5556, coolingTower.designInletAirWetBulbTemperature().get());
  ASSERT_TRUE(coolingTower.designApproachTemperature());
  EXPECT_DOUBLE_EQ(3.8889, coolingTower.designApproachTemperature().get());
  ASSERT_TRUE(coolingTower.designRangeTemperature());
  EXPECT_DOUBLE_EQ(5.5556, coolingTower.designRangeTemperature().get());

  EXPECT_FALSE(coolingTower.designWaterFlowRate());
  EXPECT_TRUE(coolingTower.isDesignWaterFlowRateAutosized());
  EXPECT_FALSE(coolingTower.designAirFlowRate());
  EXPECT_TRUE(coolingTower.isDesignAirFlowRateAutosized());
  EXPECT_FALSE(coolingTower.designFanPower());
  EXPECT_TRUE(coolingTower.isDesignFanPowerAutosized());

  ASSERT_TRUE(coolingTower.minimumAirFlowRateRatio());
  EXPECT_DOUBLE_EQ(0.2, coolingTower.minimumAirFlowRateRatio().get());
  ASSERT_TRUE(coolingTower.fractionofTowerCapacityinFreeConvectionRegime());
  EXPECT_DOUBLE_EQ(0.125, coolingTower.fractionofTowerCapacityinFreeConvectionRegime().get());
  ASSERT_TRUE(coolingTower.basinHeaterCapacity());
  EXPECT_DOUBLE_EQ(0.0, coolingTower.basinHeaterCapacity().get());
  ASSERT_TRUE(coolingTower.basinHeaterSetpointTemperature());
  EXPECT_DOUBLE_EQ(2.0, coolingTower.basinHeaterSetpointTemperature().get());
  EXPECT_FALSE(coolingTower.basinHeaterOperatingSchedule());

  EXPECT_EQ("SaturatedExit", coolingTower.evaporationLossMode());
  EXPECT_DOUBLE_EQ(0.2, coolingTower.evaporationLossFactor());
  ASSERT_TRUE(coolingTower.driftLossPercent());
  EXPECT_DOUBLE_EQ(0.008, coolingTower.driftLossPercent().get());
  EXPECT_EQ("ConcentrationRatio", coolingTower.blowdownCalculationMode());
  ASSERT_TRUE(coolingTower.blowdownConcentrationRatio());
  EXPECT_DOUBLE_EQ(3.0, coolingTower.blowdownConcentrationRatio().get());
  EXPECT_FALSE(coolingTower.blowdownMakeupWaterUsageSchedule());

  EXPECT_FALSE(coolingTower.numberofCells());
  EXPECT_EQ("MinimalCell", coolingTower.cellControl());
  EXPECT_TRUE(coolingTower.isCellControlDefaulted());
  EXPECT_FALSE(coolingTower.cellMinimumWaterFlowRateFraction());
  EXPECT_FALSE(coolingTower.cellMaximumWaterFlowRateFraction());

  ASSERT_TRUE(coolingTower.sizingFactor());
  EXPECT_DOUBLE_EQ(1.0, coolingTower.sizingFactor().get());
  EXPECT_EQ("General", coolingTower.endUseSubcategory());
  EXPECT_TRUE(coolingTower.fanPowerRatioFunctionofAirFlowRateRatioCurve());
}

TEST_F(EPModelFixture, CoolingTowerVariableSpeed_ScalarAndRelationshipAccessors_RoundTrip) {
  Model model;
  CoolingTowerVariableSpeed coolingTower(model);

  EXPECT_FALSE(CoolingTowerVariableSpeed::modelTypeValues().empty());
  EXPECT_FALSE(CoolingTowerVariableSpeed::evaporationLossModeValues().empty());
  EXPECT_FALSE(CoolingTowerVariableSpeed::blowdownCalculationModeValues().empty());
  EXPECT_FALSE(CoolingTowerVariableSpeed::cellControlValues().empty());

  CoolingTowerPerformanceYorkCalc modelCoefficient(model);
  EXPECT_TRUE(coolingTower.setModelCoefficient(modelCoefficient));
  ASSERT_TRUE(coolingTower.modelCoefficient());
  EXPECT_EQ(modelCoefficient.handle(), coolingTower.modelCoefficient()->handle());

  CurveCubic fanCurve(model);
  EXPECT_TRUE(fanCurve.setCoefficient1Constant(0.1));
  EXPECT_TRUE(fanCurve.setCoefficient2x(0.2));
  EXPECT_TRUE(fanCurve.setCoefficient3xPOW2(0.3));
  EXPECT_TRUE(fanCurve.setCoefficient4xPOW3(0.4));
  EXPECT_TRUE(fanCurve.setMinimumValueofx(0.1));
  EXPECT_TRUE(fanCurve.setMaximumValueofx(1.0));
  EXPECT_TRUE(coolingTower.setFanPowerRatioFunctionofAirFlowRateRatioCurve(fanCurve));
  ASSERT_TRUE(coolingTower.fanPowerRatioFunctionofAirFlowRateRatioCurve());
  EXPECT_EQ(fanCurve.handle(), coolingTower.fanPowerRatioFunctionofAirFlowRateRatioCurve()->handle());

  coolingTower.autosizeDesignWaterFlowRate();
  EXPECT_TRUE(coolingTower.isDesignWaterFlowRateAutosized());
  auto designWaterFlowRateToken = coolingTower.getString(openstudio::CoolingTower_VariableSpeedFields::DesignWaterFlowRate, false);
  ASSERT_TRUE(designWaterFlowRateToken);
  EXPECT_TRUE(openstudio::istringEqual(*designWaterFlowRateToken, "autosize"));
  EXPECT_TRUE(coolingTower.setDesignWaterFlowRate(0.0123));
  ASSERT_TRUE(coolingTower.designWaterFlowRate());
  EXPECT_DOUBLE_EQ(0.0123, *coolingTower.designWaterFlowRate());
  EXPECT_FALSE(coolingTower.isDesignWaterFlowRateAutosized());

  EXPECT_TRUE(coolingTower.setDesignAirFlowRate(4.56));
  ASSERT_TRUE(coolingTower.designAirFlowRate());
  EXPECT_DOUBLE_EQ(4.56, *coolingTower.designAirFlowRate());

  EXPECT_TRUE(coolingTower.setDesignFanPower(7800.0));
  ASSERT_TRUE(coolingTower.designFanPower());
  EXPECT_DOUBLE_EQ(7800.0, *coolingTower.designFanPower());

  EXPECT_TRUE(coolingTower.setMinimumAirFlowRateRatio(0.25));
  ASSERT_TRUE(coolingTower.minimumAirFlowRateRatio());
  EXPECT_DOUBLE_EQ(0.25, *coolingTower.minimumAirFlowRateRatio());

  EXPECT_TRUE(coolingTower.setNumberofCells(2));
  ASSERT_TRUE(coolingTower.numberofCells());
  EXPECT_EQ(2, *coolingTower.numberofCells());

  coolingTower.resetModelCoefficient();
  coolingTower.resetFanPowerRatioFunctionofAirFlowRateRatioCurve();
  EXPECT_FALSE(coolingTower.modelCoefficient());
  EXPECT_FALSE(coolingTower.fanPowerRatioFunctionofAirFlowRateRatioCurve());
}

TEST_F(EPModelFixture, CoolingTowerVariableSpeed_ScheduleRelationships_MatchCanonicalCompatibility) {
  Model model;
  CoolingTowerVariableSpeed coolingTower(model);

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
  ASSERT_TRUE(temperatureLimits.setNumericType("Continuous"));
  ASSERT_TRUE(temperatureSchedule.setScheduleTypeLimits(temperatureLimits));

  EXPECT_FALSE(coolingTower.setBasinHeaterOperatingSchedule(temperatureSchedule));
  ASSERT_TRUE(coolingTower.basinHeaterOperatingSchedule());
  EXPECT_EQ(continuousAvailabilitySchedule.handle(), coolingTower.basinHeaterOperatingSchedule()->handle());

  EXPECT_FALSE(coolingTower.setBlowdownMakeupWaterUsageSchedule(temperatureSchedule));
  ASSERT_TRUE(coolingTower.blowdownMakeupWaterUsageSchedule());
  EXPECT_EQ(discreteVolumetricFlowSchedule.handle(), coolingTower.blowdownMakeupWaterUsageSchedule()->handle());
}

TEST_F(EPModelFixture, CoolingTowerVariableSpeed_AddToNode) {
  Model model;
  CoolingTowerVariableSpeed coolingTower(model);

  AirLoopHVAC airLoop(model);
  Node airSupplyOutletNode = airLoop.supplyOutletNode();
  EXPECT_FALSE(coolingTower.addToNode(airSupplyOutletNode));
  EXPECT_EQ(2u, airLoop.supplyComponents().size());

  auto demandBranchNode = airLoop.zoneSplitter().lastOutletModelObject()->optionalCast<Node>();
  ASSERT_TRUE(demandBranchNode);
  EXPECT_FALSE(coolingTower.addToNode(*demandBranchNode));
  EXPECT_EQ(5u, airLoop.demandComponents().size());

  PlantLoop plantLoop(model);
  Node plantSupplyOutletNode = plantLoop.supplyOutletNode();
  EXPECT_TRUE(coolingTower.addToNode(plantSupplyOutletNode));
  EXPECT_EQ(7u, plantLoop.supplyComponents().size());

  CoolingTowerVariableSpeed secondTower(model);
  Node plantDemandOutletNode = plantLoop.demandOutletNode();
  EXPECT_FALSE(secondTower.addToNode(plantDemandOutletNode));
  EXPECT_EQ(5u, plantLoop.demandComponents().size());
}
