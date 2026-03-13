/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"
#include "../StraightComponent/AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass.hpp"
#include "../StraightComponent/Node.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_DefaultConstructor) {
  Model model;
  AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass unitary(model);
  EXPECT_EQ(AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::iddObjectType(), unitary.iddObject().type());
}

TEST_F(EPModelFixture, AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_ScalarAccessors_RoundTrip) {
  Model model;
  AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass unitary(model);

  EXPECT_TRUE(unitary.setSystemAirFlowRateDuringCoolingOperation(1.1));
  ASSERT_TRUE(unitary.systemAirFlowRateDuringCoolingOperation());
  EXPECT_DOUBLE_EQ(1.1, unitary.systemAirFlowRateDuringCoolingOperation().get());
  EXPECT_FALSE(unitary.isSystemAirFlowRateDuringCoolingOperationAutosized());
  unitary.autosizeSystemAirFlowRateDuringCoolingOperation();
  EXPECT_TRUE(unitary.isSystemAirFlowRateDuringCoolingOperationAutosized());

  EXPECT_TRUE(unitary.setSystemAirFlowRateDuringHeatingOperation(1.2));
  ASSERT_TRUE(unitary.systemAirFlowRateDuringHeatingOperation());
  EXPECT_DOUBLE_EQ(1.2, unitary.systemAirFlowRateDuringHeatingOperation().get());
  EXPECT_FALSE(unitary.isSystemAirFlowRateDuringHeatingOperationAutosized());
  unitary.autosizeSystemAirFlowRateDuringHeatingOperation();
  EXPECT_TRUE(unitary.isSystemAirFlowRateDuringHeatingOperationAutosized());

  EXPECT_TRUE(unitary.setSystemAirFlowRateWhenNoCoolingorHeatingisNeeded(0.7));
  ASSERT_TRUE(unitary.systemAirFlowRateWhenNoCoolingorHeatingisNeeded());
  EXPECT_DOUBLE_EQ(0.7, unitary.systemAirFlowRateWhenNoCoolingorHeatingisNeeded().get());
  EXPECT_FALSE(unitary.isSystemAirFlowRateWhenNoCoolingorHeatingisNeededAutosized());
  unitary.autosizeSystemAirFlowRateWhenNoCoolingorHeatingisNeeded();
  EXPECT_TRUE(unitary.isSystemAirFlowRateWhenNoCoolingorHeatingisNeededAutosized());

  EXPECT_TRUE(unitary.setOutdoorAirFlowRateDuringCoolingOperation(0.3));
  ASSERT_TRUE(unitary.outdoorAirFlowRateDuringCoolingOperation());
  EXPECT_DOUBLE_EQ(0.3, unitary.outdoorAirFlowRateDuringCoolingOperation().get());
  EXPECT_FALSE(unitary.isOutdoorAirFlowRateDuringCoolingOperationAutosized());
  unitary.autosizeOutdoorAirFlowRateDuringCoolingOperation();
  EXPECT_TRUE(unitary.isOutdoorAirFlowRateDuringCoolingOperationAutosized());

  EXPECT_TRUE(unitary.setOutdoorAirFlowRateDuringHeatingOperation(0.35));
  ASSERT_TRUE(unitary.outdoorAirFlowRateDuringHeatingOperation());
  EXPECT_DOUBLE_EQ(0.35, unitary.outdoorAirFlowRateDuringHeatingOperation().get());
  EXPECT_FALSE(unitary.isOutdoorAirFlowRateDuringHeatingOperationAutosized());
  unitary.autosizeOutdoorAirFlowRateDuringHeatingOperation();
  EXPECT_TRUE(unitary.isOutdoorAirFlowRateDuringHeatingOperationAutosized());

  EXPECT_TRUE(unitary.setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(0.2));
  ASSERT_TRUE(unitary.outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded());
  EXPECT_DOUBLE_EQ(0.2, unitary.outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded().get());
  EXPECT_FALSE(unitary.isOutdoorAirFlowRateWhenNoCoolingorHeatingisNeededAutosized());
  unitary.autosizeOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded();
  EXPECT_TRUE(unitary.isOutdoorAirFlowRateWhenNoCoolingorHeatingisNeededAutosized());

  EXPECT_TRUE(unitary.setSupplyAirFanPlacement("DrawThrough"));
  EXPECT_EQ("DrawThrough", unitary.supplyAirFanPlacement());

  EXPECT_TRUE(unitary.setPriorityControlMode("ZonePriority"));
  EXPECT_EQ("ZonePriority", unitary.priorityControlMode());

  EXPECT_TRUE(unitary.setMinimumOutletAirTemperatureDuringCoolingOperation(9.5));
  EXPECT_DOUBLE_EQ(9.5, unitary.minimumOutletAirTemperatureDuringCoolingOperation());

  EXPECT_TRUE(unitary.setMaximumOutletAirTemperatureDuringHeatingOperation(48.0));
  EXPECT_DOUBLE_EQ(48.0, unitary.maximumOutletAirTemperatureDuringHeatingOperation());

  EXPECT_TRUE(unitary.setDehumidificationControlType("CoolReheat"));
  EXPECT_EQ("CoolReheat", unitary.dehumidificationControlType());

  EXPECT_TRUE(unitary.setMinimumRuntimeBeforeOperatingModeChange(0.25));
  EXPECT_DOUBLE_EQ(0.25, unitary.minimumRuntimeBeforeOperatingModeChange());
}

TEST_F(EPModelFixture, AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_AddToNodeSupplyOnly) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass supplyUnitary(model);
  AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass demandUnitary(model);

  auto supplyInletNode = airLoop.supplyInletNode();
  EXPECT_TRUE(supplyUnitary.addToNode(supplyInletNode));
  ASSERT_TRUE(supplyUnitary.inletModelObject());
  EXPECT_EQ(supplyInletNode, supplyUnitary.inletModelObject()->cast<Node>());
  EXPECT_TRUE(supplyUnitary.outletModelObject());

  auto demandInletNode = airLoop.demandInletNode();
  EXPECT_FALSE(demandUnitary.addToNode(demandInletNode));
  EXPECT_FALSE(demandUnitary.airLoopHVAC());
}
