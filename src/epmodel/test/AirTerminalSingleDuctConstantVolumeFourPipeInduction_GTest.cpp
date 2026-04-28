#include <gtest/gtest.h>

#include "EPModelFixture.hpp"

#include "../HVACComponent/HVACComponent.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../HVACComponent/ThermalZone_Impl.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../ModelObject/ZoneHVACEquipmentConnections.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../StraightComponent/AirTerminalSingleDuctConstantVolumeFourPipeInduction.hpp"
#include "../WaterToAirComponent/CoilCoolingWater.hpp"
#include "../WaterToAirComponent/CoilHeatingWater.hpp"
#include "../StraightComponent/Node.hpp"

#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/ZoneHVAC_EquipmentConnections_FieldEnums.hxx>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeFourPipeInduction_DefaultConstructor) {
  Model model;
  AirTerminalSingleDuctConstantVolumeFourPipeInduction terminal(model);

  EXPECT_EQ(AirTerminalSingleDuctConstantVolumeFourPipeInduction::iddObjectType(), terminal.iddObject().type());
  EXPECT_FALSE(terminal.nameString().empty());
  EXPECT_FALSE(terminal.availabilitySchedule());
  EXPECT_TRUE(terminal.isMaximumTotalAirFlowRateAutosized());
  EXPECT_DOUBLE_EQ(2.5, terminal.inductionRatio());
  EXPECT_TRUE(terminal.isMaximumHotWaterFlowRateAutosized());
  EXPECT_DOUBLE_EQ(0.0, terminal.minimumHotWaterFlowRate());
  EXPECT_DOUBLE_EQ(0.001, terminal.heatingConvergenceTolerance());
  EXPECT_FALSE(terminal.coolingCoil());
  EXPECT_TRUE(terminal.isMaximumColdWaterFlowRateAutosized());
  EXPECT_DOUBLE_EQ(0.0, terminal.minimumColdWaterFlowRate());
  EXPECT_DOUBLE_EQ(0.001, terminal.coolingConvergenceTolerance());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeFourPipeInduction_HeatingCoilConstructor) {
  Model model;
  CoilHeatingWater heatingCoil(model);
  AirTerminalSingleDuctConstantVolumeFourPipeInduction terminal(model, heatingCoil);

  EXPECT_EQ(heatingCoil.handle(), terminal.heatingCoil().handle());
  EXPECT_FALSE(terminal.availabilitySchedule());
  EXPECT_FALSE(terminal.coolingCoil());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeFourPipeInduction_AvailabilityAndCoils_RoundTripAndValidation) {
  Model model;
  CoilHeatingWater heatingCoil(model);
  AirTerminalSingleDuctConstantVolumeFourPipeInduction terminal(model, heatingCoil);

  ScheduleConstant availability(model);
  ASSERT_TRUE(availability.setValue(1.0));
  EXPECT_TRUE(terminal.setAvailabilitySchedule(availability));
  ASSERT_TRUE(terminal.availabilitySchedule());
  EXPECT_EQ(availability.handle(), terminal.availabilitySchedule()->handle());
  terminal.resetAvailabilitySchedule();
  EXPECT_FALSE(terminal.availabilitySchedule());

  CoilCoolingWater coolingCoil(model);
  EXPECT_TRUE(terminal.setCoolingCoil(coolingCoil));
  ASSERT_TRUE(terminal.coolingCoil());
  EXPECT_EQ(coolingCoil.handle(), terminal.coolingCoil()->handle());
  terminal.resetCoolingCoil();
  EXPECT_FALSE(terminal.coolingCoil());

  CoilHeatingWater replacementHeating(model);
  EXPECT_TRUE(terminal.setHeatingCoil(replacementHeating));
  EXPECT_EQ(replacementHeating.handle(), terminal.heatingCoil().handle());

  Model foreignModel;
  CoilCoolingWater foreignCooling(foreignModel);
  CoilHeatingWater foreignHeating(foreignModel);
  boost::optional<HVACComponent> foreignCoolingAsComponent = foreignCooling.cast<HVACComponent>();
  EXPECT_FALSE(terminal.setCoolingCoil(foreignCoolingAsComponent));
  EXPECT_FALSE(terminal.setHeatingCoil(foreignHeating.cast<HVACComponent>()));
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeFourPipeInduction_AddToNode_RejectsInvalidNodesAndContexts) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  CoilHeatingWater heatingCoil(model);
  AirTerminalSingleDuctConstantVolumeFourPipeInduction terminal(model, heatingCoil);
  Node standaloneNode(model);
  auto supplyInletNode = airLoop.supplyInletNode();
  auto zoneAirNode = zone.zoneAirNode();

  EXPECT_FALSE(terminal.addToNode(standaloneNode));
  EXPECT_FALSE(terminal.addToNode(supplyInletNode));
  EXPECT_FALSE(terminal.addToNode(zoneAirNode));
  EXPECT_FALSE(terminal.inletModelObject());
  EXPECT_FALSE(terminal.outletModelObject());
  EXPECT_FALSE(terminal.inducedAirInletNode());
  EXPECT_FALSE(terminal.airLoopHVAC());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeFourPipeInduction_AddToNode_ResolvesAirLoopHVACRegistersZoneEquipmentAndExhaustNode) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  CoilHeatingWater heatingCoil(model);
  CoilCoolingWater coolingCoil(model);
  AirTerminalSingleDuctConstantVolumeFourPipeInduction terminal(model, heatingCoil);
  EXPECT_TRUE(terminal.setCoolingCoil(coolingCoil));

  EXPECT_TRUE(airLoop.addBranchForZone(zone, terminal));

  auto linkedAirLoop = terminal.airLoopHVAC();
  ASSERT_TRUE(linkedAirLoop);
  EXPECT_EQ(airLoop, *linkedAirLoop);

  auto inletObject = terminal.inletModelObject();
  ASSERT_TRUE(inletObject);
  auto inletNode = inletObject->optionalCast<Node>();
  ASSERT_TRUE(inletNode);

  auto outletObject = terminal.outletModelObject();
  ASSERT_TRUE(outletObject);
  auto outletNode = outletObject->optionalCast<Node>();
  ASSERT_TRUE(outletNode);
  EXPECT_EQ(zone.zoneAirNode(), *outletNode);

  ASSERT_TRUE(terminal.inducedAirInletNode());
  auto zoneImpl = zone.getImpl<detail::ThermalZone_Impl>();
  ASSERT_TRUE(zoneImpl);
  auto zoneConnections = zoneImpl->zoneHVACEquipmentConnections();
  ASSERT_TRUE(zoneConnections);
  auto exhaustNode = zoneConnections->getModelObjectTarget<Node>(openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneAirExhaustNodeorNodeListName);
  ASSERT_TRUE(exhaustNode);
  EXPECT_EQ(*exhaustNode, terminal.inducedAirInletNode().get());

  const auto equipment = zone.equipment();
  ASSERT_EQ(1u, equipment.size());
  EXPECT_EQ(terminal.cast<ModelObject>(), equipment.front());
  ASSERT_TRUE(zone.airLoopHVACTerminal());
  EXPECT_EQ(terminal.cast<HVACComponent>(), *zone.airLoopHVACTerminal());
}
