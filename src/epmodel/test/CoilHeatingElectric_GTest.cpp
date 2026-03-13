/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../Loop/AirLoopHVAC.hpp"
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

TEST_F(EPModelFixture, CoilHeatingElectric_AddToNodeRejectsOutboardOANode) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACOutdoorAirSystem oaSystem(model);
  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(oaSystem.addToNode(supplyInletNode));
  auto outboardOANode = oaSystem.outboardOANode();
  ASSERT_TRUE(outboardOANode);

  CoilHeatingElectric coil(model);
  EXPECT_FALSE(coil.addToNode(*outboardOANode));
}
