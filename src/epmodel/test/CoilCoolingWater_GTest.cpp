/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include <utilities/idd/CoilSystem_Cooling_Water_FieldEnums.hxx>
#include <utilities/idd/CoilSystem_Cooling_Water_HeatExchangerAssisted_FieldEnums.hxx>
#include <utilities/idd/Controller_WaterCoil_FieldEnums.hxx>

#include "EPModelFixture.hpp"
#include "../HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "../HVACComponent/ControllerWaterCoil.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Schedule/ScheduleConstant_Impl.hpp"
#include "../StraightComponent/CoilSystemCoolingWater.hpp"
#include "../StraightComponent/CoilSystemCoolingWaterHeatExchangerAssisted.hpp"
#include "../StraightComponent/Node.hpp"
#include "../WaterToAirComponent/CoilCoolingWater.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoilCoolingWater_DefaultConstructor) {
  Model model;
  CoilCoolingWater coil(model);
  EXPECT_EQ(CoilCoolingWater::iddObjectType(), coil.iddObject().type());
  auto availability = coil.availabilitySchedule().optionalCast<ScheduleConstant>();
  ASSERT_TRUE(availability);
  EXPECT_EQ(model.alwaysOnDiscreteSchedule().handle(), availability->handle());
  EXPECT_EQ(availability->handle(), coil.availableSchedule().handle());
}

TEST_F(EPModelFixture, CoilCoolingWater_ScheduleConstructorAndSetter) {
  Model model;
  ScheduleConstant availability(model);
  availability.setValue(0.0);

  CoilCoolingWater coil(model, availability);
  EXPECT_EQ(availability.handle(), coil.availabilitySchedule().handle());
  EXPECT_EQ(availability.handle(), coil.availableSchedule().handle());

  ScheduleConstant replacement(model);
  replacement.setValue(1.0);
  EXPECT_TRUE(coil.setAvailabilitySchedule(replacement));
  EXPECT_EQ(replacement.handle(), coil.availabilitySchedule().handle());

  EXPECT_TRUE(coil.setAvailableSchedule(availability));
  EXPECT_EQ(availability.handle(), coil.availabilitySchedule().handle());
}

TEST_F(EPModelFixture, CoilCoolingWater_ScalarAccessors_RoundTrip) {
  Model model;
  CoilCoolingWater coil(model);

  EXPECT_TRUE(coil.setDesignWaterFlowRate(0.0011));
  ASSERT_TRUE(coil.designWaterFlowRate());
  EXPECT_DOUBLE_EQ(0.0011, coil.designWaterFlowRate().get());
  EXPECT_FALSE(coil.isDesignWaterFlowRateAutosized());
  coil.autosizeDesignWaterFlowRate();
  EXPECT_TRUE(coil.isDesignWaterFlowRateAutosized());

  EXPECT_TRUE(coil.setDesignAirFlowRate(0.87));
  ASSERT_TRUE(coil.designAirFlowRate());
  EXPECT_DOUBLE_EQ(0.87, coil.designAirFlowRate().get());
  EXPECT_FALSE(coil.isDesignAirFlowRateAutosized());
  coil.autosizeDesignAirFlowRate();
  EXPECT_TRUE(coil.isDesignAirFlowRateAutosized());

  EXPECT_TRUE(coil.setDesignInletWaterTemperature(6.8));
  ASSERT_TRUE(coil.designInletWaterTemperature());
  EXPECT_DOUBLE_EQ(6.8, coil.designInletWaterTemperature().get());
  EXPECT_FALSE(coil.isDesignInletWaterTemperatureAutosized());
  coil.autosizeDesignInletWaterTemperature();
  EXPECT_TRUE(coil.isDesignInletWaterTemperatureAutosized());

  EXPECT_TRUE(coil.setDesignInletAirTemperature(26.1));
  ASSERT_TRUE(coil.designInletAirTemperature());
  EXPECT_DOUBLE_EQ(26.1, coil.designInletAirTemperature().get());
  EXPECT_FALSE(coil.isDesignInletAirTemperatureAutosized());
  coil.autosizeDesignInletAirTemperature();
  EXPECT_TRUE(coil.isDesignInletAirTemperatureAutosized());

  EXPECT_TRUE(coil.setDesignOutletAirTemperature(12.4));
  ASSERT_TRUE(coil.designOutletAirTemperature());
  EXPECT_DOUBLE_EQ(12.4, coil.designOutletAirTemperature().get());
  EXPECT_FALSE(coil.isDesignOutletAirTemperatureAutosized());
  coil.autosizeDesignOutletAirTemperature();
  EXPECT_TRUE(coil.isDesignOutletAirTemperatureAutosized());

  EXPECT_TRUE(coil.setDesignInletAirHumidityRatio(0.0105));
  ASSERT_TRUE(coil.designInletAirHumidityRatio());
  EXPECT_DOUBLE_EQ(0.0105, coil.designInletAirHumidityRatio().get());
  EXPECT_FALSE(coil.isDesignInletAirHumidityRatioAutosized());
  coil.autosizeDesignInletAirHumidityRatio();
  EXPECT_TRUE(coil.isDesignInletAirHumidityRatioAutosized());

  EXPECT_TRUE(coil.setDesignOutletAirHumidityRatio(0.0084));
  ASSERT_TRUE(coil.designOutletAirHumidityRatio());
  EXPECT_DOUBLE_EQ(0.0084, coil.designOutletAirHumidityRatio().get());
  EXPECT_FALSE(coil.isDesignOutletAirHumidityRatioAutosized());
  coil.autosizeDesignOutletAirHumidityRatio();
  EXPECT_TRUE(coil.isDesignOutletAirHumidityRatioAutosized());

  EXPECT_TRUE(coil.setTypeOfAnalysis("DetailedAnalysis"));
  EXPECT_EQ("DetailedAnalysis", coil.typeOfAnalysis());

  EXPECT_TRUE(coil.setHeatExchangerConfiguration("CounterFlow"));
  EXPECT_EQ("CounterFlow", coil.heatExchangerConfiguration());
}

TEST_F(EPModelFixture, CoilCoolingWater_AddToNodeSupportsOutboardOANode) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACOutdoorAirSystem oaSystem(model);
  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(oaSystem.addToNode(supplyInletNode));

  auto outboardOANode = oaSystem.outboardOANode();
  ASSERT_TRUE(outboardOANode);

  CoilCoolingWater coil(model);

  EXPECT_TRUE(coil.addToNode(*outboardOANode));

  const auto oaComponents = oaSystem.oaComponents();
  ASSERT_EQ(3u, oaComponents.size());
  EXPECT_EQ(coil.handle(), oaComponents[1].handle());
}

TEST_F(EPModelFixture, CoilCoolingWater_RemoveDetachesFromOutdoorAirSystem) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACOutdoorAirSystem oaSystem(model);
  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(oaSystem.addToNode(supplyInletNode));

  auto outboardOANode = oaSystem.outboardOANode();
  ASSERT_TRUE(outboardOANode);

  CoilCoolingWater coil(model);
  ASSERT_TRUE(coil.addToNode(*outboardOANode));
  ASSERT_EQ(3u, oaSystem.oaComponents().size());
  const auto coilHandle = coil.handle();

  coil.remove();

  EXPECT_LT(oaSystem.oaComponents().size(), 3u);
  EXPECT_FALSE(oaSystem.component(coilHandle));
}

TEST_F(EPModelFixture, CoilCoolingWater_ControllerWaterCoil_IsInferredFromLoopNodes) {
  Model model;
  CoilCoolingWater coil(model);
  AirLoopHVAC airLoop(model);
  PlantLoop plantLoop(model);

  auto supplyOutletNode = airLoop.supplyOutletNode();
  ASSERT_TRUE(coil.addToNode(supplyOutletNode));
  EXPECT_FALSE(coil.controllerWaterCoil());

  ASSERT_TRUE(plantLoop.addDemandBranchForComponent(coil));
  auto controller = coil.controllerWaterCoil();
  ASSERT_TRUE(controller);
  ASSERT_TRUE(controller->action());
  EXPECT_EQ("Reverse", *controller->action());

  auto actuatorNode = controller->getModelObjectTarget<Node>(openstudio::Controller_WaterCoilFields::ActuatorNodeName);
  auto sensorNode = controller->getModelObjectTarget<Node>(openstudio::Controller_WaterCoilFields::SensorNodeName);
  ASSERT_TRUE(actuatorNode);
  ASSERT_TRUE(sensorNode);
  ASSERT_TRUE(coil.waterInletModelObject());
  ASSERT_TRUE(coil.airOutletModelObject());
  EXPECT_EQ(coil.waterInletModelObject()->handle(), actuatorNode->handle());
  EXPECT_EQ(coil.airOutletModelObject()->handle(), sensorNode->handle());

  ASSERT_TRUE(plantLoop.removeDemandBranchWithComponent(coil));
  EXPECT_FALSE(coil.controllerWaterCoil());
}

TEST_F(EPModelFixture, CoilCoolingWater_DoesNotCreateControllerWhenReferencedByCoilSystemCoolingWater) {
  Model model;
  CoilCoolingWater coil(model);
  CoilSystemCoolingWater system(model);
  AirLoopHVAC airLoop(model);
  PlantLoop plantLoop(model);

  ASSERT_TRUE(system.setPointer(openstudio::CoilSystem_Cooling_WaterFields::CoolingCoilName, coil.handle()));

  auto supplyOutletNode = airLoop.supplyOutletNode();
  ASSERT_TRUE(coil.addToNode(supplyOutletNode));
  ASSERT_TRUE(plantLoop.addDemandBranchForComponent(coil));

  EXPECT_FALSE(coil.controllerWaterCoil());
}

TEST_F(EPModelFixture, CoilCoolingWater_DoesNotCreateControllerWhenReferencedThroughHeatExchangerAssistedParentSystem) {
  Model model;
  CoilCoolingWater coil(model);
  CoilSystemCoolingWater system(model);
  CoilSystemCoolingWaterHeatExchangerAssisted hxAssisted(model);
  AirLoopHVAC airLoop(model);
  PlantLoop plantLoop(model);

  ASSERT_TRUE(hxAssisted.setPointer(openstudio::CoilSystem_Cooling_Water_HeatExchangerAssistedFields::CoolingCoilName, coil.handle()));
  ASSERT_TRUE(system.setPointer(openstudio::CoilSystem_Cooling_WaterFields::CoolingCoilName, hxAssisted.handle()));

  auto supplyOutletNode = airLoop.supplyOutletNode();
  ASSERT_TRUE(coil.addToNode(supplyOutletNode));
  ASSERT_TRUE(plantLoop.addDemandBranchForComponent(coil));

  EXPECT_FALSE(coil.controllerWaterCoil());
}

TEST_F(EPModelFixture, CoilCoolingWater_AutosizedValueAccessorsReturnNoneWithoutSqlSupport) {
  Model model;
  CoilCoolingWater coil(model);

  coil.autosizeDesignWaterFlowRate();
  coil.autosizeDesignAirFlowRate();
  coil.autosizeDesignInletWaterTemperature();
  coil.autosizeDesignInletAirTemperature();
  coil.autosizeDesignOutletAirTemperature();
  coil.autosizeDesignInletAirHumidityRatio();
  coil.autosizeDesignOutletAirHumidityRatio();

  EXPECT_FALSE(coil.autosizedDesignWaterFlowRate());
  EXPECT_FALSE(coil.autosizedDesignAirFlowRate());
  EXPECT_FALSE(coil.autosizedDesignInletWaterTemperature());
  EXPECT_FALSE(coil.autosizedDesignInletAirTemperature());
  EXPECT_FALSE(coil.autosizedDesignOutletAirTemperature());
  EXPECT_FALSE(coil.autosizedDesignInletAirHumidityRatio());
  EXPECT_FALSE(coil.autosizedDesignOutletAirHumidityRatio());
  EXPECT_FALSE(coil.autosizedDesignCoilLoad());
}
