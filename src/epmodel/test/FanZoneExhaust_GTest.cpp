/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../HVACComponent/ThermalZone_Impl.hpp"
#include "../ModelObject/ZoneHVACEquipmentConnections.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../StraightComponent/Node.hpp"
#include "../ZoneHVACComponent/FanZoneExhaust.hpp"
#include "../ZoneHVACComponent/FanZoneExhaust_Impl.hpp"

#include <utilities/idd/Fan_ZoneExhaust_FieldEnums.hxx>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, FanZoneExhaust_DefaultConstructor) {
  Model model;
  FanZoneExhaust fan(model);
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::Fan_ZoneExhaust), fan.iddObject().type());
}

TEST_F(EPModelFixture, FanZoneExhaust_ScalarAccessors_RoundTrip) {
  Model model;
  FanZoneExhaust fan(model);

  EXPECT_TRUE(fan.setFanTotalEfficiency(0.72));
  EXPECT_DOUBLE_EQ(0.72, fan.fanTotalEfficiency());
  EXPECT_DOUBLE_EQ(0.72, fan.fanEfficiency());

  EXPECT_TRUE(fan.setFanEfficiency(0.68));
  EXPECT_DOUBLE_EQ(0.68, fan.fanTotalEfficiency());

  EXPECT_TRUE(fan.setPressureRise(320.0));
  EXPECT_DOUBLE_EQ(320.0, fan.pressureRise());

  EXPECT_TRUE(fan.setMaximumFlowRate(0.55));
  ASSERT_TRUE(fan.maximumFlowRate());
  EXPECT_DOUBLE_EQ(0.55, fan.maximumFlowRate().get());
  fan.resetMaximumFlowRate();
  EXPECT_FALSE(fan.maximumFlowRate());

  EXPECT_TRUE(fan.setEndUseSubcategory("Exhaust"));
  EXPECT_EQ("Exhaust", fan.endUseSubcategory());

  const auto couplingModes = FanZoneExhaust::systemAvailabilityManagerCouplingModeValues();
  ASSERT_FALSE(couplingModes.empty());
  EXPECT_TRUE(fan.setSystemAvailabilityManagerCouplingMode(couplingModes.front()));
  EXPECT_EQ(couplingModes.front(), fan.systemAvailabilityManagerCouplingMode());
}

TEST_F(EPModelFixture, FanZoneExhaust_ScheduleAccessors_RoundTrip) {
  Model model;
  FanZoneExhaust fan(model);
  ScheduleConstant availability(model);
  ScheduleConstant flowFraction(model);
  ScheduleConstant minimumTemperature(model);
  ScheduleConstant balancedFraction(model);

  EXPECT_FALSE(fan.availabilitySchedule());
  EXPECT_FALSE(fan.flowFractionSchedule());
  EXPECT_FALSE(fan.minimumZoneTemperatureLimitSchedule());
  EXPECT_FALSE(fan.balancedExhaustFractionSchedule());

  EXPECT_TRUE(fan.setAvailabilitySchedule(availability));
  EXPECT_TRUE(fan.setFlowFractionSchedule(flowFraction));
  EXPECT_TRUE(fan.setMinimumZoneTemperatureLimitSchedule(minimumTemperature));
  EXPECT_TRUE(fan.setBalancedExhaustFractionSchedule(balancedFraction));
  EXPECT_EQ(availability, *fan.availabilitySchedule());
  EXPECT_EQ(flowFraction, *fan.flowFractionSchedule());
  EXPECT_EQ(minimumTemperature, *fan.minimumZoneTemperatureLimitSchedule());
  EXPECT_EQ(balancedFraction, *fan.balancedExhaustFractionSchedule());

  fan.resetAvailabilitySchedule();
  fan.resetFlowFractionSchedule();
  fan.resetMinimumZoneTemperatureLimitSchedule();
  fan.resetBalancedExhaustFractionSchedule();
  EXPECT_FALSE(fan.availabilitySchedule());
  EXPECT_FALSE(fan.flowFractionSchedule());
  EXPECT_FALSE(fan.minimumZoneTemperatureLimitSchedule());
  EXPECT_FALSE(fan.balancedExhaustFractionSchedule());
}

TEST_F(EPModelFixture, FanZoneExhaust_Topology) {
  Model model;
  FanZoneExhaust fan(model);
  ThermalZone zone(model);

  EXPECT_EQ(openstudio::Fan_ZoneExhaustFields::AirInletNodeName, fan.inletPort());
  EXPECT_EQ(openstudio::Fan_ZoneExhaustFields::AirOutletNodeName, fan.outletPort());

  EXPECT_TRUE(fan.addToThermalZone(zone));
  ASSERT_TRUE(fan.thermalZone());
  EXPECT_EQ(zone, fan.thermalZone().get());
  auto inlet = fan.inletNode();
  auto outlet = fan.outletNode();
  ASSERT_TRUE(inlet);
  ASSERT_TRUE(outlet);

  auto connections = zone.getImpl<detail::ThermalZone_Impl>()->zoneHVACEquipmentConnections();
  ASSERT_TRUE(connections);
  EXPECT_TRUE(connections->zoneAirInletNodes().empty());
  const auto exhaustNodes = connections->zoneAirExhaustNodes();
  ASSERT_EQ(1u, exhaustNodes.size());
  EXPECT_EQ(*inlet, exhaustNodes.front());

  fan.removeFromThermalZone();
  EXPECT_FALSE(fan.thermalZone());
  EXPECT_FALSE(fan.inletNode());
  EXPECT_FALSE(fan.outletNode());
  EXPECT_TRUE(connections->zoneAirExhaustNodes().empty());
}

TEST_F(EPModelFixture, FanZoneExhaust_ZoneMoveSurvivesReload) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-zone-exhaust-move.idf");
  Model model;
  FanZoneExhaust fan(model);
  ThermalZone firstZone(model);
  ThermalZone secondZone(model);
  ASSERT_TRUE(fan.setName("Movable Zone Exhaust Fan"));
  ASSERT_TRUE(firstZone.setName("First Exhaust Zone"));
  ASSERT_TRUE(secondZone.setName("Second Exhaust Zone"));

  ASSERT_TRUE(fan.addToThermalZone(firstZone));
  auto firstConnections = firstZone.getImpl<detail::ThermalZone_Impl>()->zoneHVACEquipmentConnections();
  ASSERT_TRUE(firstConnections);
  ASSERT_EQ(1u, firstConnections->zoneAirExhaustNodes().size());

  ASSERT_TRUE(fan.addToThermalZone(secondZone));
  EXPECT_TRUE(firstConnections->zoneAirExhaustNodes().empty());
  ASSERT_TRUE(fan.thermalZone());
  EXPECT_EQ(secondZone, *fan.thermalZone());
  auto secondConnections = secondZone.getImpl<detail::ThermalZone_Impl>()->zoneHVACEquipmentConnections();
  ASSERT_TRUE(secondConnections);
  ASSERT_EQ(1u, secondConnections->zoneAirExhaustNodes().size());
  EXPECT_EQ(*fan.inletNode(), secondConnections->zoneAirExhaustNodes().front());

  ASSERT_TRUE(model.save(idfPath, true));
  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedFan = loadedModel->getConcreteModelObjectByName<FanZoneExhaust>("Movable Zone Exhaust Fan");
  auto loadedSecondZone = loadedModel->getConcreteModelObjectByName<ThermalZone>("Second Exhaust Zone");
  ASSERT_TRUE(loadedFan);
  ASSERT_TRUE(loadedSecondZone);
  ASSERT_TRUE(loadedFan->thermalZone());
  EXPECT_EQ(*loadedSecondZone, *loadedFan->thermalZone());
  ASSERT_TRUE(loadedFan->inletNode());
  ASSERT_TRUE(loadedFan->outletNode());
  const auto loadedInletHandle = loadedFan->inletNode()->handle();
  const auto loadedOutletHandle = loadedFan->outletNode()->handle();

  loadedFan->removeFromThermalZone();
  EXPECT_FALSE(loadedFan->thermalZone());
  auto loadedConnections = loadedSecondZone->getImpl<detail::ThermalZone_Impl>()->zoneHVACEquipmentConnections();
  ASSERT_TRUE(loadedConnections);
  EXPECT_TRUE(loadedConnections->zoneAirExhaustNodes().empty());
  EXPECT_FALSE(loadedFan->inletNode());
  EXPECT_FALSE(loadedFan->outletNode());
  EXPECT_FALSE(loadedModel->getObject(loadedInletHandle));
  EXPECT_FALSE(loadedModel->getObject(loadedOutletHandle));

  openstudio::filesystem::remove(idfPath);
}
