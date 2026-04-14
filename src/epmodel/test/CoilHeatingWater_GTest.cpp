/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include <utilities/idd/Controller_WaterCoil_FieldEnums.hxx>

#include "EPModelFixture.hpp"
#include "../HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "../HVACComponent/ControllerWaterCoil.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Schedule/ScheduleConstant_Impl.hpp"
#include "../StraightComponent/Node.hpp"
#include "../WaterToAirComponent/CoilHeatingWater.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoilHeatingWater_DefaultConstructor) {
  Model model;
  CoilHeatingWater coil(model);
  EXPECT_EQ(CoilHeatingWater::iddObjectType(), coil.iddObject().type());
  auto availability = coil.availabilitySchedule().optionalCast<ScheduleConstant>();
  ASSERT_TRUE(availability);
  EXPECT_EQ(model.alwaysOnDiscreteSchedule().handle(), availability->handle());
  EXPECT_EQ(availability->handle(), coil.availableSchedule().handle());
}

TEST_F(EPModelFixture, CoilHeatingWater_ScheduleConstructorAndSetter) {
  Model model;
  ScheduleConstant availability(model);
  availability.setValue(0.0);

  CoilHeatingWater coil(model, availability);
  EXPECT_EQ(availability.handle(), coil.availabilitySchedule().handle());
  EXPECT_EQ(availability.handle(), coil.availableSchedule().handle());

  ScheduleConstant replacement(model);
  replacement.setValue(1.0);
  EXPECT_TRUE(coil.setAvailabilitySchedule(replacement));
  EXPECT_EQ(replacement.handle(), coil.availabilitySchedule().handle());

  EXPECT_TRUE(coil.setAvailableSchedule(availability));
  EXPECT_EQ(availability.handle(), coil.availabilitySchedule().handle());
}

TEST_F(EPModelFixture, CoilHeatingWater_ScalarAccessors_RoundTrip) {
  Model model;
  CoilHeatingWater coil(model);

  EXPECT_TRUE(coil.setUFactorTimesAreaValue(512.0));
  ASSERT_TRUE(coil.uFactorTimesAreaValue());
  EXPECT_DOUBLE_EQ(512.0, coil.uFactorTimesAreaValue().get());
  EXPECT_FALSE(coil.isUFactorTimesAreaValueAutosized());
  coil.autosizeUFactorTimesAreaValue();
  EXPECT_TRUE(coil.isUFactorTimesAreaValueAutosized());
  EXPECT_FALSE(coil.autosizedUFactorTimesAreaValue());

  EXPECT_TRUE(coil.setMaximumWaterFlowRate(0.0014));
  ASSERT_TRUE(coil.maximumWaterFlowRate());
  EXPECT_DOUBLE_EQ(0.0014, coil.maximumWaterFlowRate().get());
  EXPECT_FALSE(coil.isMaximumWaterFlowRateAutosized());
  coil.autosizeMaximumWaterFlowRate();
  EXPECT_TRUE(coil.isMaximumWaterFlowRateAutosized());
  EXPECT_FALSE(coil.autosizedMaximumWaterFlowRate());

  EXPECT_TRUE(coil.setPerformanceInputMethod("NominalCapacity"));
  EXPECT_EQ("NominalCapacity", coil.performanceInputMethod());

  EXPECT_TRUE(coil.setRatedCapacity(10250.0));
  ASSERT_TRUE(coil.ratedCapacity());
  EXPECT_DOUBLE_EQ(10250.0, coil.ratedCapacity().get());
  EXPECT_FALSE(coil.isRatedCapacityAutosized());
  coil.autosizeRatedCapacity();
  EXPECT_TRUE(coil.isRatedCapacityAutosized());
  EXPECT_FALSE(coil.autosizedRatedCapacity());

  EXPECT_TRUE(coil.setRatedInletWaterTemperature(60.0));
  EXPECT_DOUBLE_EQ(60.0, coil.ratedInletWaterTemperature());

  EXPECT_TRUE(coil.setRatedInletAirTemperature(16.5));
  EXPECT_DOUBLE_EQ(16.5, coil.ratedInletAirTemperature());

  EXPECT_TRUE(coil.setRatedOutletWaterTemperature(49.0));
  EXPECT_DOUBLE_EQ(49.0, coil.ratedOutletWaterTemperature());

  EXPECT_TRUE(coil.setRatedOutletAirTemperature(31.0));
  EXPECT_DOUBLE_EQ(31.0, coil.ratedOutletAirTemperature());

  EXPECT_TRUE(coil.setRatedRatioForAirAndWaterConvection(0.45));
  EXPECT_DOUBLE_EQ(0.45, coil.ratedRatioForAirAndWaterConvection());
}

TEST_F(EPModelFixture, CoilHeatingWater_AddToNodeSupportsOutboardOANode) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACOutdoorAirSystem oaSystem(model);
  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(oaSystem.addToNode(supplyInletNode));

  auto outboardOANode = oaSystem.outboardOANode();
  ASSERT_TRUE(outboardOANode);

  CoilHeatingWater coil(model);

  EXPECT_TRUE(coil.addToNode(*outboardOANode));

  const auto oaComponents = oaSystem.oaComponents();
  ASSERT_EQ(3u, oaComponents.size());
  EXPECT_EQ(coil.handle(), oaComponents[1].handle());
}

TEST_F(EPModelFixture, CoilHeatingWater_ControllerWaterCoil_IsInferredFromLoopNodes) {
  Model model;
  CoilHeatingWater coil(model);
  AirLoopHVAC airLoop(model);
  PlantLoop plantLoop(model);

  auto supplyOutletNode = airLoop.supplyOutletNode();
  ASSERT_TRUE(coil.addToNode(supplyOutletNode));
  EXPECT_FALSE(coil.controllerWaterCoil());

  ASSERT_TRUE(plantLoop.addDemandBranchForComponent(coil));
  auto controller = coil.controllerWaterCoil();
  ASSERT_TRUE(controller);
  ASSERT_TRUE(controller->action());
  EXPECT_EQ("Normal", *controller->action());

  auto actuatorNode = controller->actuatorNode();
  auto sensorNode = controller->sensorNode();
  ASSERT_TRUE(actuatorNode);
  ASSERT_TRUE(sensorNode);
  ASSERT_TRUE(coil.waterInletModelObject());
  ASSERT_TRUE(coil.airOutletModelObject());
  EXPECT_EQ(coil.waterInletModelObject()->handle(), actuatorNode->handle());
  EXPECT_EQ(coil.airOutletModelObject()->handle(), sensorNode->handle());

  ASSERT_TRUE(plantLoop.removeDemandBranchWithComponent(coil));
  EXPECT_FALSE(coil.controllerWaterCoil());
}
