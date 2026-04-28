/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Curve/CurveCubic.hpp"
#include "../HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../ParentObject/CoilPerformanceDXCooling.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../StraightComponent/CoilCoolingDXTwoStageWithHumidityControlMode.hpp"
#include "../StraightComponent/Node.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoilCoolingDXTwoStageWithHumidityControlMode_DefaultConstructor) {
  Model model;
  CoilCoolingDXTwoStageWithHumidityControlMode coil(model);
  EXPECT_EQ(CoilCoolingDXTwoStageWithHumidityControlMode::iddObjectType(), coil.iddObject().type());
  EXPECT_FALSE(coil.nameString().empty());

  EXPECT_EQ(2, coil.numberofCapacityStages());
  EXPECT_EQ(1, coil.numberofEnhancedDehumidificationModes());
  EXPECT_DOUBLE_EQ(0.0, coil.crankcaseHeaterCapacity());
  EXPECT_DOUBLE_EQ(10.0, coil.maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation());
  EXPECT_DOUBLE_EQ(0.0, coil.basinHeaterCapacity());
  EXPECT_DOUBLE_EQ(2.0, coil.basinHeaterSetpointTemperature());
  EXPECT_DOUBLE_EQ(-25.0, coil.minimumOutdoorDryBulbTemperatureforCompressorOperation());
  EXPECT_FALSE(coil.availabilitySchedule());
  EXPECT_FALSE(coil.crankcaseHeaterCapacityFunctionofTemperatureCurve());
  EXPECT_FALSE(coil.normalModeStage1CoilPerformance());
  EXPECT_FALSE(coil.normalModeStage1Plus2CoilPerformance());
  EXPECT_FALSE(coil.dehumidificationMode1Stage1CoilPerformance());
  EXPECT_FALSE(coil.dehumidificationMode1Stage1Plus2CoilPerformance());
  EXPECT_FALSE(coil.basinHeaterOperatingSchedule());
  EXPECT_TRUE(coil.children().empty());
}

TEST_F(EPModelFixture, CoilCoolingDXTwoStageWithHumidityControlMode_ScalarAccessors_RoundTrip) {
  Model model;
  CoilCoolingDXTwoStageWithHumidityControlMode coil(model);

  EXPECT_TRUE(coil.setCrankcaseHeaterCapacity(85.0));
  EXPECT_DOUBLE_EQ(85.0, coil.crankcaseHeaterCapacity());

  EXPECT_TRUE(coil.setMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation(12.5));
  EXPECT_DOUBLE_EQ(12.5, coil.maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation());

  EXPECT_TRUE(coil.setNumberofCapacityStages(2));
  EXPECT_EQ(2, coil.numberofCapacityStages());

  EXPECT_TRUE(coil.setNumberofEnhancedDehumidificationModes(1));
  EXPECT_EQ(1, coil.numberofEnhancedDehumidificationModes());

  EXPECT_TRUE(coil.setBasinHeaterCapacity(30.0));
  EXPECT_DOUBLE_EQ(30.0, coil.basinHeaterCapacity());

  EXPECT_TRUE(coil.setBasinHeaterSetpointTemperature(3.5));
  EXPECT_DOUBLE_EQ(3.5, coil.basinHeaterSetpointTemperature());

  EXPECT_TRUE(coil.setMinimumOutdoorDryBulbTemperatureforCompressorOperation(-12.0));
  EXPECT_DOUBLE_EQ(-12.0, coil.minimumOutdoorDryBulbTemperatureforCompressorOperation());
}

TEST_F(EPModelFixture, CoilCoolingDXTwoStageWithHumidityControlMode_RelationshipSetters_RoundTrip) {
  Model model;
  CoilCoolingDXTwoStageWithHumidityControlMode coil(model);

  ScheduleConstant availability(model);
  ASSERT_TRUE(availability.setValue(0.2));
  ScheduleConstant basinSchedule(model);
  ASSERT_TRUE(basinSchedule.setValue(0.7));
  CurveCubic crankcaseCurve(model);
  CoilPerformanceDXCooling stage1(model);
  CoilPerformanceDXCooling stage12(model);
  CoilPerformanceDXCooling dehum1(model);
  CoilPerformanceDXCooling dehum12(model);

  EXPECT_TRUE(coil.setAvailabilitySchedule(availability));
  ASSERT_TRUE(coil.availabilitySchedule());
  EXPECT_EQ(availability.handle(), coil.availabilitySchedule()->handle());

  EXPECT_TRUE(coil.setCrankcaseHeaterCapacityFunctionofTemperatureCurve(crankcaseCurve));
  ASSERT_TRUE(coil.crankcaseHeaterCapacityFunctionofTemperatureCurve());
  EXPECT_EQ(crankcaseCurve.handle(), coil.crankcaseHeaterCapacityFunctionofTemperatureCurve()->handle());

  EXPECT_TRUE(coil.setNormalModeStage1CoilPerformance(stage1));
  ASSERT_TRUE(coil.normalModeStage1CoilPerformance());
  EXPECT_EQ(stage1.handle(), coil.normalModeStage1CoilPerformance()->handle());

  EXPECT_TRUE(coil.setNormalModeStage1Plus2CoilPerformance(stage12));
  ASSERT_TRUE(coil.normalModeStage1Plus2CoilPerformance());
  EXPECT_EQ(stage12.handle(), coil.normalModeStage1Plus2CoilPerformance()->handle());

  EXPECT_TRUE(coil.setDehumidificationMode1Stage1CoilPerformance(dehum1));
  ASSERT_TRUE(coil.dehumidificationMode1Stage1CoilPerformance());
  EXPECT_EQ(dehum1.handle(), coil.dehumidificationMode1Stage1CoilPerformance()->handle());

  EXPECT_TRUE(coil.setDehumidificationMode1Stage1Plus2CoilPerformance(dehum12));
  ASSERT_TRUE(coil.dehumidificationMode1Stage1Plus2CoilPerformance());
  EXPECT_EQ(dehum12.handle(), coil.dehumidificationMode1Stage1Plus2CoilPerformance()->handle());

  EXPECT_TRUE(coil.setBasinHeaterOperatingSchedule(basinSchedule));
  ASSERT_TRUE(coil.basinHeaterOperatingSchedule());
  EXPECT_EQ(basinSchedule.handle(), coil.basinHeaterOperatingSchedule()->handle());

  const auto children = coil.children();
  ASSERT_EQ(4u, children.size());
  EXPECT_EQ(stage1.handle(), children[0].handle());
  EXPECT_EQ(stage12.handle(), children[1].handle());
  EXPECT_EQ(dehum1.handle(), children[2].handle());
  EXPECT_EQ(dehum12.handle(), children[3].handle());

  coil.resetAvailabilitySchedule();
  coil.resetCrankcaseHeaterCapacityFunctionofTemperatureCurve();
  coil.resetNormalModeStage1CoilPerformance();
  coil.resetNormalModeStage1Plus2CoilPerformance();
  coil.resetDehumidificationMode1Stage1CoilPerformance();
  coil.resetDehumidificationMode1Stage1Plus2CoilPerformance();
  coil.resetBasinHeaterOperatingSchedule();

  EXPECT_FALSE(coil.availabilitySchedule());
  EXPECT_FALSE(coil.crankcaseHeaterCapacityFunctionofTemperatureCurve());
  EXPECT_FALSE(coil.normalModeStage1CoilPerformance());
  EXPECT_FALSE(coil.normalModeStage1Plus2CoilPerformance());
  EXPECT_FALSE(coil.dehumidificationMode1Stage1CoilPerformance());
  EXPECT_FALSE(coil.dehumidificationMode1Stage1Plus2CoilPerformance());
  EXPECT_FALSE(coil.basinHeaterOperatingSchedule());
  EXPECT_TRUE(coil.children().empty());
}

TEST_F(EPModelFixture, CoilCoolingDXTwoStageWithHumidityControlMode_AddToNodeSupplyOnly) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACOutdoorAirSystem oaSystem(model);
  CoilCoolingDXTwoStageWithHumidityControlMode supplyCoil(model);
  CoilCoolingDXTwoStageWithHumidityControlMode demandCoil(model);
  CoilCoolingDXTwoStageWithHumidityControlMode oaCoil(model);

  auto supplyInletNode = airLoop.supplyInletNode();
  EXPECT_TRUE(supplyCoil.addToNode(supplyInletNode));
  ASSERT_TRUE(supplyCoil.inletModelObject());
  EXPECT_EQ(supplyInletNode, supplyCoil.inletModelObject()->cast<Node>());
  EXPECT_TRUE(supplyCoil.outletModelObject());

  auto supplyOutlet = supplyCoil.outletModelObject()->cast<Node>();
  ASSERT_TRUE(supplyOutlet.inletModelObject());
  EXPECT_EQ(supplyCoil.handle(), supplyOutlet.inletModelObject()->handle());

  auto demandInletNode = airLoop.demandInletNode();
  EXPECT_FALSE(demandCoil.addToNode(demandInletNode));
  EXPECT_FALSE(demandCoil.inletModelObject());
  EXPECT_FALSE(demandCoil.outletModelObject());

  auto oaNode = oaSystem.outboardOANode();
  ASSERT_TRUE(oaNode);
  EXPECT_FALSE(oaCoil.addToNode(*oaNode));
  EXPECT_FALSE(oaCoil.inletModelObject());
  EXPECT_FALSE(oaCoil.outletModelObject());
}
