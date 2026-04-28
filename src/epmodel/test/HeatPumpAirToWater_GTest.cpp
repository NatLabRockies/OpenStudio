/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"

#include "../Curve/CurveBicubic.hpp"
#include "../Curve/CurveCubic.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../ResourceObject/ScheduleTypeLimits.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"
#include "../StraightComponent/HeatPumpAirToWater.hpp"
#include "../StraightComponent/Node.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, HeatPumpAirToWater_DefaultConstructor) {
  Model model;
  HeatPumpAirToWater hp(model);

  EXPECT_EQ(HeatPumpAirToWater::iddObjectType(), hp.iddObject().type());
  EXPECT_FALSE(hp.nameString().empty());

  EXPECT_EQ("Load", hp.operatingModeControlMethod());
  EXPECT_EQ("SingleMode", hp.operatingModeControlOptionforMultipleUnit());
  EXPECT_FALSE(hp.operatingModeControlSchedule());
  EXPECT_DOUBLE_EQ(0.0, hp.minimumPartLoadRatio());
  EXPECT_FALSE(hp.airInletNodeName());
  EXPECT_FALSE(hp.airOutletNodeName());
  EXPECT_EQ("None", hp.heatPumpDefrostControl());
  EXPECT_FALSE(hp.defrostEnergyInputRatioFunctionofTemperatureCurve());
  EXPECT_EQ("VariableSpeed", hp.controlType());
  EXPECT_FALSE(hp.crankcaseHeaterCapacityFunctionofTemperatureCurve());
}

TEST_F(EPModelFixture, HeatPumpAirToWater_RelationshipAndScalarAccessors_RoundTrip) {
  Model model;
  HeatPumpAirToWater hp(model);

  EXPECT_TRUE(hp.setOperatingModeControlMethod("EMSControlled"));
  EXPECT_EQ("EMSControlled", hp.operatingModeControlMethod());
  EXPECT_FALSE(hp.setOperatingModeControlMethod("ScheduledModes"));
  EXPECT_EQ("EMSControlled", hp.operatingModeControlMethod());

  ScheduleConstant operatingModeSchedule(model);
  ASSERT_TRUE(operatingModeSchedule.setValue(2.0));
  EXPECT_TRUE(hp.setOperatingModeControlSchedule(operatingModeSchedule));
  ASSERT_TRUE(hp.operatingModeControlSchedule());
  EXPECT_EQ(operatingModeSchedule.handle(), hp.operatingModeControlSchedule()->handle());
  EXPECT_EQ("ScheduledModes", hp.operatingModeControlMethod());
  ASSERT_TRUE(operatingModeSchedule.scheduleTypeLimits());
  ASSERT_TRUE(operatingModeSchedule.scheduleTypeLimits()->numericType());
  EXPECT_EQ("Discrete", operatingModeSchedule.scheduleTypeLimits()->numericType().get());
  ASSERT_TRUE(operatingModeSchedule.scheduleTypeLimits()->lowerLimitValue());
  EXPECT_DOUBLE_EQ(0.0, operatingModeSchedule.scheduleTypeLimits()->lowerLimitValue().get());
  ASSERT_TRUE(operatingModeSchedule.scheduleTypeLimits()->upperLimitValue());
  EXPECT_DOUBLE_EQ(2.0, operatingModeSchedule.scheduleTypeLimits()->upperLimitValue().get());

  ScheduleConstant incompatibleSchedule(model);
  ASSERT_TRUE(incompatibleSchedule.setValue(25.0));
  ScheduleTypeLimits temperatureLimits(model);
  ASSERT_TRUE(temperatureLimits.setNumericType("Continuous"));
  ASSERT_TRUE(temperatureLimits.setUnitType("Temperature"));
  ASSERT_TRUE(incompatibleSchedule.setScheduleTypeLimits(temperatureLimits));
  EXPECT_FALSE(hp.setOperatingModeControlSchedule(incompatibleSchedule));
  ASSERT_TRUE(hp.operatingModeControlSchedule());
  EXPECT_EQ(operatingModeSchedule.handle(), hp.operatingModeControlSchedule()->handle());
  EXPECT_EQ("ScheduledModes", hp.operatingModeControlMethod());

  Model otherModel;
  ScheduleConstant foreignSchedule(otherModel);
  ASSERT_TRUE(foreignSchedule.setValue(1.0));
  EXPECT_FALSE(hp.setOperatingModeControlSchedule(foreignSchedule));
  ASSERT_TRUE(hp.operatingModeControlSchedule());
  EXPECT_EQ(operatingModeSchedule.handle(), hp.operatingModeControlSchedule()->handle());

  hp.resetOperatingModeControlSchedule();
  EXPECT_FALSE(hp.operatingModeControlSchedule());
  EXPECT_EQ("Load", hp.operatingModeControlMethod());

  EXPECT_TRUE(hp.setOperatingModeControlOptionforMultipleUnit("Balanced"));
  EXPECT_EQ("Balanced", hp.operatingModeControlOptionforMultipleUnit());

  EXPECT_TRUE(hp.setMinimumPartLoadRatio(0.21));
  EXPECT_DOUBLE_EQ(0.21, hp.minimumPartLoadRatio());

  EXPECT_TRUE(hp.setAirInletNodeName("AWHP Air Inlet Node"));
  EXPECT_TRUE(hp.setAirOutletNodeName("AWHP Air Outlet Node"));
  ASSERT_TRUE(hp.airInletNodeName());
  ASSERT_TRUE(hp.airOutletNodeName());
  EXPECT_EQ("AWHP Air Inlet Node", hp.airInletNodeName().get());
  EXPECT_EQ("AWHP Air Outlet Node", hp.airOutletNodeName().get());
  hp.resetAirInletNodeName();
  EXPECT_FALSE(hp.airInletNodeName());
  ASSERT_TRUE(hp.airOutletNodeName());
  EXPECT_EQ("AWHP Air Outlet Node", hp.airOutletNodeName().get());
  hp.resetAirOutletNodeName();
  EXPECT_FALSE(hp.airOutletNodeName());

  EXPECT_TRUE(hp.setMaximumOutdoorDryBulbTemperatureForDefrostOperation(7.5));
  EXPECT_DOUBLE_EQ(7.5, hp.maximumOutdoorDryBulbTemperatureForDefrostOperation());

  EXPECT_TRUE(hp.setHeatPumpDefrostControl("Timed"));
  EXPECT_EQ("Timed", hp.heatPumpDefrostControl());

  EXPECT_TRUE(hp.setHeatPumpDefrostTimePeriodFraction(0.12));
  EXPECT_DOUBLE_EQ(0.12, hp.heatPumpDefrostTimePeriodFraction());

  EXPECT_TRUE(hp.setResistiveDefrostHeaterCapacity(450.0));
  EXPECT_DOUBLE_EQ(450.0, hp.resistiveDefrostHeaterCapacity());

  CurveBicubic defrostCurve(model);
  EXPECT_TRUE(hp.setDefrostEnergyInputRatioFunctionofTemperatureCurve(defrostCurve));
  ASSERT_TRUE(hp.defrostEnergyInputRatioFunctionofTemperatureCurve());
  EXPECT_EQ(defrostCurve.handle(), hp.defrostEnergyInputRatioFunctionofTemperatureCurve()->handle());
  CurveBicubic alternateDefrostCurve(model);
  EXPECT_TRUE(hp.setDefrostEnergyInputRatioFunctionofTemperatureCurve(alternateDefrostCurve));
  ASSERT_TRUE(hp.defrostEnergyInputRatioFunctionofTemperatureCurve());
  EXPECT_EQ(alternateDefrostCurve.handle(), hp.defrostEnergyInputRatioFunctionofTemperatureCurve()->handle());
  Model defrostCurveModel;
  CurveBicubic foreignDefrostCurve(defrostCurveModel);
  EXPECT_FALSE(hp.setDefrostEnergyInputRatioFunctionofTemperatureCurve(foreignDefrostCurve));
  ASSERT_TRUE(hp.defrostEnergyInputRatioFunctionofTemperatureCurve());
  EXPECT_EQ(alternateDefrostCurve.handle(), hp.defrostEnergyInputRatioFunctionofTemperatureCurve()->handle());
  hp.resetDefrostEnergyInputRatioFunctionofTemperatureCurve();
  EXPECT_FALSE(hp.defrostEnergyInputRatioFunctionofTemperatureCurve());

  EXPECT_TRUE(hp.setHeatPumpMultiplier(3));
  EXPECT_EQ(3, hp.heatPumpMultiplier());

  EXPECT_TRUE(hp.setControlType("FixedSpeed"));
  EXPECT_EQ("FixedSpeed", hp.controlType());

  EXPECT_TRUE(hp.setCrankcaseHeaterCapacity(50.0));
  EXPECT_DOUBLE_EQ(50.0, hp.crankcaseHeaterCapacity());

  CurveCubic crankcaseCurve(model);
  EXPECT_TRUE(hp.setCrankcaseHeaterCapacityFunctionofTemperatureCurve(crankcaseCurve));
  ASSERT_TRUE(hp.crankcaseHeaterCapacityFunctionofTemperatureCurve());
  EXPECT_EQ(crankcaseCurve.handle(), hp.crankcaseHeaterCapacityFunctionofTemperatureCurve()->handle());
  CurveCubic alternateCrankcaseCurve(model);
  EXPECT_TRUE(hp.setCrankcaseHeaterCapacityFunctionofTemperatureCurve(alternateCrankcaseCurve));
  ASSERT_TRUE(hp.crankcaseHeaterCapacityFunctionofTemperatureCurve());
  EXPECT_EQ(alternateCrankcaseCurve.handle(), hp.crankcaseHeaterCapacityFunctionofTemperatureCurve()->handle());
  Model crankcaseCurveModel;
  CurveCubic foreignCrankcaseCurve(crankcaseCurveModel);
  EXPECT_FALSE(hp.setCrankcaseHeaterCapacityFunctionofTemperatureCurve(foreignCrankcaseCurve));
  ASSERT_TRUE(hp.crankcaseHeaterCapacityFunctionofTemperatureCurve());
  EXPECT_EQ(alternateCrankcaseCurve.handle(), hp.crankcaseHeaterCapacityFunctionofTemperatureCurve()->handle());
  hp.resetCrankcaseHeaterCapacityFunctionofTemperatureCurve();
  EXPECT_FALSE(hp.crankcaseHeaterCapacityFunctionofTemperatureCurve());

  EXPECT_TRUE(hp.setMaximumAmbientTemperatureforCrankcaseHeaterOperation(8.0));
  EXPECT_DOUBLE_EQ(8.0, hp.maximumAmbientTemperatureforCrankcaseHeaterOperation());

  hp.resetControlType();
  EXPECT_TRUE(hp.isControlTypeDefaulted());
  EXPECT_EQ("VariableSpeed", hp.controlType());
}

TEST_F(EPModelFixture, HeatPumpAirToWater_AddToNode_IsRejected) {
  Model model;
  HeatPumpAirToWater hp(model);

  AirLoopHVAC airLoop(model);
  Node airSupplyNode = airLoop.supplyOutletNode();
  const auto initialAirSupplyCount = airLoop.supplyComponents().size();
  EXPECT_FALSE(hp.addToNode(airSupplyNode));
  EXPECT_EQ(initialAirSupplyCount, airLoop.supplyComponents().size());

  Node airDemandNode = airLoop.zoneSplitter().lastOutletModelObject()->cast<Node>();
  const auto initialAirDemandCount = airLoop.demandComponents().size();
  EXPECT_FALSE(hp.addToNode(airDemandNode));
  EXPECT_EQ(initialAirDemandCount, airLoop.demandComponents().size());

  PlantLoop plantLoop(model);
  Node plantSupplyNode = plantLoop.supplyOutletNode();
  const auto initialPlantSupplyCount = plantLoop.supplyComponents().size();
  EXPECT_FALSE(hp.addToNode(plantSupplyNode));
  EXPECT_EQ(initialPlantSupplyCount, plantLoop.supplyComponents().size());
  EXPECT_FALSE(plantLoop.addSupplyBranchForComponent(hp));
  EXPECT_EQ(initialPlantSupplyCount, plantLoop.supplyComponents().size());

  Node plantDemandNode = plantLoop.demandOutletNode();
  const auto initialPlantDemandCount = plantLoop.demandComponents().size();
  EXPECT_FALSE(hp.addToNode(plantDemandNode));
  EXPECT_EQ(initialPlantDemandCount, plantLoop.demandComponents().size());
  EXPECT_FALSE(plantLoop.addDemandBranchForComponent(hp));
  EXPECT_EQ(initialPlantDemandCount, plantLoop.demandComponents().size());

  Node unconnectedNode = model.getOrCreateTransientByName<Node>("Unconnected HeatPumpAirToWater Node");
  EXPECT_FALSE(hp.addToNode(unconnectedNode));
  EXPECT_FALSE(hp.loop());
  EXPECT_FALSE(hp.inletModelObject());
  EXPECT_FALSE(hp.outletModelObject());
}
