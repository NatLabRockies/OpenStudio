/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Schedule/ScheduleConstant_Impl.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"
#include "../StraightComponent/CoilHeatingElectric.hpp"
#include "../StraightComponent/Node.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoilHeatingElectric_DefaultConstructor) {
  Model model;
  CoilHeatingElectric coil(model);
  EXPECT_EQ(CoilHeatingElectric::iddObjectType(), coil.iddObject().type());
  EXPECT_FALSE(coil.nameString().empty());

  EXPECT_DOUBLE_EQ(1.0, coil.efficiency());
  EXPECT_TRUE(coil.isEfficiencyDefaulted());
  EXPECT_FALSE(coil.nominalCapacity());
  EXPECT_TRUE(coil.isNominalCapacityDefaulted());
  EXPECT_FALSE(coil.isNominalCapacityAutosized());
  auto availability = coil.availabilitySchedule().optionalCast<ScheduleConstant>();
  ASSERT_TRUE(availability);
  EXPECT_DOUBLE_EQ(1.0, availability->value());
  EXPECT_FALSE(coil.temperatureSetpointNode());
}

TEST_F(EPModelFixture, CoilHeatingElectric_ScalarAccessors_RoundTrip) {
  Model model;
  CoilHeatingElectric coil(model);

  EXPECT_TRUE(coil.setEfficiency(0.91));
  EXPECT_DOUBLE_EQ(0.91, coil.efficiency());
  EXPECT_FALSE(coil.isEfficiencyDefaulted());
  coil.resetEfficiency();
  EXPECT_DOUBLE_EQ(1.0, coil.efficiency());
  EXPECT_TRUE(coil.isEfficiencyDefaulted());

  EXPECT_TRUE(coil.setNominalCapacity(4200.0));
  ASSERT_TRUE(coil.nominalCapacity());
  EXPECT_DOUBLE_EQ(4200.0, *coil.nominalCapacity());
  EXPECT_FALSE(coil.isNominalCapacityDefaulted());
  EXPECT_FALSE(coil.isNominalCapacityAutosized());

  coil.autosizeNominalCapacity();
  EXPECT_TRUE(coil.isNominalCapacityAutosized());
  EXPECT_FALSE(coil.nominalCapacity());

  coil.resetNominalCapacity();
  EXPECT_TRUE(coil.isNominalCapacityDefaulted());
  EXPECT_FALSE(coil.isNominalCapacityAutosized());
  EXPECT_FALSE(coil.nominalCapacity());

  EXPECT_FALSE(coil.autosizedNominalCapacity());
}

TEST_F(EPModelFixture, CoilHeatingElectric_RelationshipSetters_RoundTrip) {
  Model model;
  CoilHeatingElectric coil(model);
  ScheduleConstant availability(model);
  ASSERT_TRUE(availability.setValue(0.25));
  Node setpointNode(model);

  EXPECT_TRUE(coil.setAvailabilitySchedule(availability));
  EXPECT_EQ(availability.handle(), coil.availabilitySchedule().handle());

  EXPECT_TRUE(coil.setTemperatureSetpointNode(setpointNode));
  ASSERT_TRUE(coil.temperatureSetpointNode());
  EXPECT_EQ(setpointNode.handle(), coil.temperatureSetpointNode()->handle());
  coil.resetTemperatureSetpointNode();
  EXPECT_FALSE(coil.temperatureSetpointNode());
}

TEST_F(EPModelFixture, CoilHeatingElectric_AddToNodeRejectsAirLoopDemandNode) {
  Model model;
  AirLoopHVAC airLoop(model);
  CoilHeatingElectric coil(model);

  auto branchObject = airLoop.zoneSplitter().lastOutletModelObject();
  ASSERT_TRUE(branchObject);
  auto demandBranchNode = branchObject->optionalCast<Node>();
  ASSERT_TRUE(demandBranchNode);

  ThermalZone zone(model);
  ASSERT_TRUE(zone.addToNode(*demandBranchNode));
  EXPECT_FALSE(coil.addToNode(*demandBranchNode));
}

TEST_F(EPModelFixture, CoilHeatingElectric_AddToNodeSupportsOutboardOANode) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACOutdoorAirSystem oaSystem(model);
  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(oaSystem.addToNode(supplyInletNode));
  auto outboardOANode = oaSystem.outboardOANode();
  ASSERT_TRUE(outboardOANode);

  CoilHeatingElectric coil(model);
  EXPECT_TRUE(coil.addToNode(*outboardOANode));
  EXPECT_EQ(3u, oaSystem.oaComponents().size());
}
