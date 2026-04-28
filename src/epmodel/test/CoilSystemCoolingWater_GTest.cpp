/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include <algorithm>

#include "EPModelFixture.hpp"
#include "../HVACComponent/ControllerWaterCoil.hpp"
#include "../HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../WaterToAirComponent/CoilCoolingWater.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"
#include "../StraightComponent/CoilSystemCoolingWater.hpp"
#include "../StraightComponent/CoilSystemCoolingWaterHeatExchangerAssisted.hpp"
#include <utilities/idd/CoilSystem_Cooling_Water_FieldEnums.hxx>
#include "../StraightComponent/Node.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoilSystemCoolingWater_DefaultConstructor) {
  Model model;
  CoilSystemCoolingWater coilSystem(model);
  EXPECT_EQ(CoilSystemCoolingWater::iddObjectType(), coilSystem.iddObject().type());
  EXPECT_FALSE(coilSystem.nameString().empty());

  EXPECT_EQ("None", coilSystem.dehumidificationControlType());
  EXPECT_TRUE(coilSystem.runonSensibleLoad());
  EXPECT_FALSE(coilSystem.runonLatentLoad());
  EXPECT_DOUBLE_EQ(0.0, coilSystem.minimumAirToWaterTemperatureOffset());
  EXPECT_TRUE(coilSystem.economizerLockout());
  EXPECT_DOUBLE_EQ(0.0, coilSystem.minimumWaterLoopTemperatureForHeatRecovery());
  EXPECT_EQ(model.alwaysOnDiscreteSchedule().handle(), coilSystem.availabilitySchedule().handle());
  EXPECT_EQ("Coil:Cooling:Water", coilSystem.coolingCoil().iddObject().name());
}

TEST_F(EPModelFixture, CoilSystemCoolingWater_ScalarAccessors_RoundTrip) {
  Model model;
  CoilSystemCoolingWater coilSystem(model);

  const auto dehumidificationControlTypes = CoilSystemCoolingWater::dehumidificationControlTypeValues();
  EXPECT_FALSE(dehumidificationControlTypes.empty());
  EXPECT_TRUE(std::find(dehumidificationControlTypes.begin(), dehumidificationControlTypes.end(), "CoolReheat")
              != dehumidificationControlTypes.end());

  EXPECT_TRUE(coilSystem.setDehumidificationControlType("CoolReheat"));
  EXPECT_EQ("CoolReheat", coilSystem.dehumidificationControlType());
  EXPECT_FALSE(coilSystem.setDehumidificationControlType("Invalid Dehumidification Control Type"));

  EXPECT_TRUE(coilSystem.setRunonSensibleLoad(false));
  EXPECT_FALSE(coilSystem.runonSensibleLoad());

  EXPECT_TRUE(coilSystem.setRunonLatentLoad(true));
  EXPECT_TRUE(coilSystem.runonLatentLoad());

  EXPECT_TRUE(coilSystem.setMinimumAirToWaterTemperatureOffset(1.0));
  EXPECT_DOUBLE_EQ(1.0, coilSystem.minimumAirToWaterTemperatureOffset());

  EXPECT_TRUE(coilSystem.setEconomizerLockout(false));
  EXPECT_FALSE(coilSystem.economizerLockout());

  EXPECT_TRUE(coilSystem.setMinimumWaterLoopTemperatureForHeatRecovery(1.2));
  EXPECT_DOUBLE_EQ(1.2, coilSystem.minimumWaterLoopTemperatureForHeatRecovery());
}

TEST_F(EPModelFixture, CoilSystemCoolingWater_RelationshipAccessors_RoundTrip) {
  Model model;
  CoilSystemCoolingWater coilSystem(model);
  ScheduleConstant availabilitySchedule(model);
  CoilSystemCoolingWaterHeatExchangerAssisted heatExchangerAssisted(model);
  CoilCoolingWater companionCoil(model);
  CoilSystemCoolingWaterHeatExchangerAssisted invalidCompanion(model);

  EXPECT_TRUE(coilSystem.setAvailabilitySchedule(availabilitySchedule));
  EXPECT_EQ(availabilitySchedule.handle(), coilSystem.availabilitySchedule().handle());

  EXPECT_TRUE(coilSystem.setCoolingCoil(heatExchangerAssisted));
  EXPECT_EQ(heatExchangerAssisted.handle(), coilSystem.coolingCoil().handle());

  EXPECT_TRUE(coilSystem.setCompanionCoilUsedForHeatRecovery(companionCoil));
  ASSERT_TRUE(coilSystem.companionCoilUsedForHeatRecovery());
  EXPECT_EQ(companionCoil.handle(), coilSystem.companionCoilUsedForHeatRecovery()->handle());

  EXPECT_FALSE(coilSystem.setCompanionCoilUsedForHeatRecovery(invalidCompanion));
  EXPECT_EQ(companionCoil.handle(), coilSystem.companionCoilUsedForHeatRecovery()->handle());

  coilSystem.resetCompanionCoilUsedForHeatRecovery();
  EXPECT_FALSE(coilSystem.companionCoilUsedForHeatRecovery());

  const auto children = coilSystem.children();
  ASSERT_EQ(1u, children.size());
  EXPECT_EQ(heatExchangerAssisted.handle(), children.front().handle());
}

TEST_F(EPModelFixture, CoilSystemCoolingWater_ExplicitConstructor) {
  Model model;
  CoilSystemCoolingWaterHeatExchangerAssisted heatExchangerAssisted(model);
  CoilSystemCoolingWater coilSystem(model, heatExchangerAssisted);

  EXPECT_EQ(heatExchangerAssisted.handle(), coilSystem.coolingCoil().handle());
  EXPECT_EQ(model.alwaysOnDiscreteSchedule().handle(), coilSystem.availabilitySchedule().handle());
  EXPECT_EQ("None", coilSystem.dehumidificationControlType());
}

TEST_F(EPModelFixture, CoilSystemCoolingWater_AddToNodeCurrentPaths) {
  Model model;
  AirLoopHVAC airLoop(model);
  CoilSystemCoolingWater supplyCoilSystem(model);
  CoilSystemCoolingWater outdoorAirCoilSystem(model);
  CoilSystemCoolingWater demandCoilSystem(model);
  AirLoopHVACOutdoorAirSystem oaSystem(model);

  auto supplyInletNode = airLoop.supplyInletNode();
  EXPECT_TRUE(supplyCoilSystem.addToNode(supplyInletNode));
  ASSERT_TRUE(supplyCoilSystem.inletModelObject());
  EXPECT_EQ(supplyInletNode, supplyCoilSystem.inletModelObject()->cast<Node>());
  EXPECT_TRUE(supplyCoilSystem.outletModelObject());

  auto demandInletNode = airLoop.demandInletNode();
  EXPECT_FALSE(demandCoilSystem.addToNode(demandInletNode));
  EXPECT_FALSE(demandCoilSystem.airLoopHVAC());

  auto supplyOutletNode = airLoop.supplyOutletNode();
  ASSERT_TRUE(oaSystem.addToNode(supplyOutletNode));
  auto outboardOANode = oaSystem.outboardOANode();
  ASSERT_TRUE(outboardOANode);
  EXPECT_TRUE(outdoorAirCoilSystem.addToNode(*outboardOANode));
  const auto oaComponents = oaSystem.oaComponents();
  EXPECT_FALSE(oaComponents.empty());
  EXPECT_TRUE(
    std::any_of(oaComponents.begin(), oaComponents.end(), [&](const auto& object) { return object.handle() == outdoorAirCoilSystem.handle(); }));
}

TEST_F(EPModelFixture, CoilSystemCoolingWater_ContainedCoolingCoilDoesNotCreateStandaloneController) {
  Model model;
  CoilSystemCoolingWater system(model);
  CoilCoolingWater coil(model);
  AirLoopHVAC airLoop(model);
  PlantLoop plantLoop(model);

  ASSERT_TRUE(system.setCoolingCoil(coil));

  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(system.addToNode(supplyInletNode));
  ASSERT_TRUE(plantLoop.addDemandBranchForComponent(coil));

  EXPECT_FALSE(coil.controllerWaterCoil());
}
