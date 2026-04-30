/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include <utilities/idd/AirflowNetwork_Distribution_Component_Coil_FieldEnums.hxx>
#include <utilities/idd/Coil_Heating_Water_FieldEnums.hxx>
#include <utilities/idd/Controller_WaterCoil_FieldEnums.hxx>

#include "EPModelFixture.hpp"
#include "../ModelObject/AirflowNetworkDistributionComponentCoil.hpp"
#include "../ModelObject/AirflowNetworkDistributionComponentCoil_Impl.hpp"
#include "../HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "../HVACComponent/ControllerWaterCoil.hpp"
#include "../HVACComponent/ControllerWaterCoil_Impl.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../Schedule/Schedule.hpp"
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

  EXPECT_EQ(std::vector<std::string>({"UFactorTimesAreaAndDesignWaterFlowRate", "NominalCapacity"}),
            CoilHeatingWater::performanceInputMethodValues());
  EXPECT_EQ("UFactorTimesAreaAndDesignWaterFlowRate", coil.performanceInputMethod());

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

  EXPECT_FALSE(coil.setPerformanceInputMethod("InvalidPerformanceInputMethod"));
  EXPECT_EQ("NominalCapacity", coil.performanceInputMethod());
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

TEST_F(EPModelFixture, CoilHeatingWater_RemoveCleansUpAttachedControllerWaterCoil) {
  Model model;
  CoilHeatingWater coil(model);
  AirLoopHVAC airLoop(model);
  PlantLoop plantLoop(model);

  auto supplyOutletNode = airLoop.supplyOutletNode();
  ASSERT_TRUE(coil.addToNode(supplyOutletNode));
  ASSERT_TRUE(plantLoop.addDemandBranchForComponent(coil));
  ASSERT_EQ(1u, model.getModelObjects<ControllerWaterCoil>().size());

  coil.remove();

  EXPECT_TRUE(model.getModelObjects<ControllerWaterCoil>().empty());
}

TEST_F(EPModelFixture, CoilHeatingWater_AirflowNetworkEquivalentDuctRoundTrip) {
  Model model;
  CoilHeatingWater coil(model);

  EXPECT_FALSE(coil.airflowNetworkEquivalentDuct());

  auto afnComponent = coil.getAirflowNetworkEquivalentDuct(1.25, 0.41);
  EXPECT_EQ(AirflowNetworkDistributionComponentCoil::iddObjectType(), afnComponent.iddObject().type());
  EXPECT_EQ("Coil:Heating:Water", afnComponent.coilObjectType());
  EXPECT_DOUBLE_EQ(1.25, afnComponent.airPathLength());
  EXPECT_DOUBLE_EQ(0.41, afnComponent.airPathHydraulicDiameter());

  auto attached = coil.airflowNetworkEquivalentDuct();
  ASSERT_TRUE(attached);
  EXPECT_EQ(afnComponent.handle(), attached->handle());

  EXPECT_TRUE(afnComponent.setCoilObjectType("Coil:Cooling:WaterToAirHeatPump:EquationFit"));

  const auto children = coil.children();
  ASSERT_EQ(1u, children.size());
  EXPECT_EQ(afnComponent.handle(), children.front().handle());

  auto updated = coil.getAirflowNetworkEquivalentDuct(2.5, 0.82);
  EXPECT_EQ(afnComponent.handle(), updated.handle());
  EXPECT_EQ("Coil:Heating:Water", updated.coilObjectType());
  EXPECT_DOUBLE_EQ(2.5, updated.airPathLength());
  EXPECT_DOUBLE_EQ(0.82, updated.airPathHydraulicDiameter());
}

TEST_F(EPModelFixture, CoilHeatingWater_AirflowNetworkEquivalentDuctReturnsFirstAttachedComponentWhenMultipleAttachmentsExist) {
  Model model;
  CoilHeatingWater coil(model);

  auto first = coil.getAirflowNetworkEquivalentDuct(1.25, 0.41);
  AirflowNetworkDistributionComponentCoil duplicate(model);
  ASSERT_TRUE(duplicate.setPointer(openstudio::AirflowNetwork_Distribution_Component_CoilFields::CoilName, coil.handle()));
  ASSERT_TRUE(duplicate.setCoilObjectType("Coil:Heating:Water"));
  ASSERT_TRUE(duplicate.setAirPathLength(3.5));
  ASSERT_TRUE(duplicate.setAirPathHydraulicDiameter(0.63));

  auto attached = coil.airflowNetworkEquivalentDuct();
  ASSERT_TRUE(attached);
  EXPECT_EQ(first.handle(), attached->handle());

  const auto children = coil.children();
  ASSERT_EQ(2u, children.size());
  EXPECT_EQ(first.handle(), children[0].handle());
  EXPECT_EQ(duplicate.handle(), children[1].handle());
}

TEST_F(EPModelFixture, CoilHeatingWater_RemoveCleansUpAttachedAirflowNetworkComponent) {
  Model model;
  CoilHeatingWater coil(model);
  coil.getAirflowNetworkEquivalentDuct(1.25, 0.41);

  ASSERT_EQ(1u, model.getModelObjects<AirflowNetworkDistributionComponentCoil>().size());

  coil.remove();

  EXPECT_TRUE(model.getModelObjects<AirflowNetworkDistributionComponentCoil>().empty());
}

TEST_F(EPModelFixture, CoilHeatingWater_AvailabilityScheduleGetterRepairsMissingRequiredReference) {
  Model model;
  CoilHeatingWater coil(model);

  ASSERT_TRUE(coil.setPointer(openstudio::Coil_Heating_WaterFields::AvailabilityScheduleName, openstudio::Handle()));
  EXPECT_FALSE(coil.getModelObjectTarget<Schedule>(openstudio::Coil_Heating_WaterFields::AvailabilityScheduleName));

  const auto schedule = coil.availabilitySchedule();
  EXPECT_EQ(model.alwaysOnDiscreteSchedule().handle(), schedule.handle());

  const auto repairedSchedule = coil.getModelObjectTarget<Schedule>(openstudio::Coil_Heating_WaterFields::AvailabilityScheduleName);
  ASSERT_TRUE(repairedSchedule);
  EXPECT_EQ(schedule.handle(), repairedSchedule->handle());
}
