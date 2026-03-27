/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../StraightComponent/FanOnOff.hpp"
#include "../StraightComponent/Node.hpp"
#include "../WaterToAirComponent/CoilCoolingWaterToAirHeatPumpEquationFit.hpp"
#include "../WaterToAirComponent/CoilHeatingWater.hpp"
#include "../WaterToAirComponent/CoilHeatingWaterToAirHeatPumpEquationFit.hpp"
#include "../ZoneHVACComponent/ZoneHVACWaterToAirHeatPump.hpp"

#include <utilities/idd/ZoneHVAC_WaterToAirHeatPump_FieldEnums.hxx>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ZoneHVACWaterToAirHeatPump_DefaultConstructor) {
  Model model;
  ZoneHVACWaterToAirHeatPump wahp(model);

  EXPECT_FALSE(wahp.supplyAirFlowRateDuringCoolingOperation());
  EXPECT_FALSE(wahp.isSupplyAirFlowRateDuringCoolingOperationAutosized());
  EXPECT_FALSE(wahp.supplyAirFlowRateDuringHeatingOperation());
  EXPECT_FALSE(wahp.isSupplyAirFlowRateDuringHeatingOperationAutosized());
  EXPECT_FALSE(wahp.supplyAirFlowRateWhenNoCoolingorHeatingisNeeded());
  EXPECT_FALSE(wahp.isSupplyAirFlowRateWhenNoCoolingorHeatingisNeededAutosized());
  EXPECT_TRUE(wahp.noLoadSupplyAirFlowRateControlSetToLowSpeed());
  EXPECT_FALSE(wahp.outdoorAirFlowRateDuringCoolingOperation());
  EXPECT_FALSE(wahp.isOutdoorAirFlowRateDuringCoolingOperationAutosized());
  EXPECT_FALSE(wahp.outdoorAirFlowRateDuringHeatingOperation());
  EXPECT_FALSE(wahp.isOutdoorAirFlowRateDuringHeatingOperationAutosized());
  EXPECT_FALSE(wahp.outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded());
  EXPECT_FALSE(wahp.isOutdoorAirFlowRateWhenNoCoolingorHeatingisNeededAutosized());
  EXPECT_FALSE(wahp.maximumSupplyAirTemperaturefromSupplementalHeater());
  EXPECT_TRUE(wahp.isMaximumSupplyAirTemperaturefromSupplementalHeaterAutosized());
  EXPECT_TRUE(wahp.isFanPlacementDefaulted());
  EXPECT_TRUE(wahp.isHeatPumpCoilWaterFlowModeDefaulted());
}

TEST_F(EPModelFixture, ZoneHVACWaterToAirHeatPump_ScalarAccessors_RoundTrip) {
  Model model;
  ZoneHVACWaterToAirHeatPump wahp(model);

  EXPECT_TRUE(wahp.setSupplyAirFlowRateDuringCoolingOperation(0.52));
  ASSERT_TRUE(wahp.supplyAirFlowRateDuringCoolingOperation());
  EXPECT_DOUBLE_EQ(0.52, wahp.supplyAirFlowRateDuringCoolingOperation().get());
  wahp.autosizeSupplyAirFlowRateDuringCoolingOperation();
  EXPECT_TRUE(wahp.isSupplyAirFlowRateDuringCoolingOperationAutosized());

  EXPECT_TRUE(wahp.setSupplyAirFlowRateDuringHeatingOperation(0.48));
  ASSERT_TRUE(wahp.supplyAirFlowRateDuringHeatingOperation());
  EXPECT_DOUBLE_EQ(0.48, wahp.supplyAirFlowRateDuringHeatingOperation().get());
  wahp.autosizeSupplyAirFlowRateDuringHeatingOperation();
  EXPECT_TRUE(wahp.isSupplyAirFlowRateDuringHeatingOperationAutosized());

  EXPECT_TRUE(wahp.setSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded(0.16));
  ASSERT_TRUE(wahp.supplyAirFlowRateWhenNoCoolingorHeatingisNeeded());
  EXPECT_DOUBLE_EQ(0.16, wahp.supplyAirFlowRateWhenNoCoolingorHeatingisNeeded().get());
  wahp.resetSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded();
  EXPECT_FALSE(wahp.supplyAirFlowRateWhenNoCoolingorHeatingisNeeded());
  wahp.autosizeSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded();
  EXPECT_TRUE(wahp.isSupplyAirFlowRateWhenNoCoolingorHeatingisNeededAutosized());

  EXPECT_TRUE(wahp.setNoLoadSupplyAirFlowRateControlSetToLowSpeed(true));
  EXPECT_TRUE(wahp.noLoadSupplyAirFlowRateControlSetToLowSpeed());

  EXPECT_TRUE(wahp.setOutdoorAirFlowRateDuringCoolingOperation(0.25));
  wahp.autosizeOutdoorAirFlowRateDuringCoolingOperation();
  EXPECT_TRUE(wahp.isOutdoorAirFlowRateDuringCoolingOperationAutosized());

  EXPECT_TRUE(wahp.setOutdoorAirFlowRateDuringHeatingOperation(0.22));
  wahp.autosizeOutdoorAirFlowRateDuringHeatingOperation();
  EXPECT_TRUE(wahp.isOutdoorAirFlowRateDuringHeatingOperationAutosized());

  EXPECT_TRUE(wahp.setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(0.08));
  wahp.resetOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded();
  EXPECT_FALSE(wahp.outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded());
  wahp.autosizeOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded();
  EXPECT_TRUE(wahp.isOutdoorAirFlowRateWhenNoCoolingorHeatingisNeededAutosized());

  EXPECT_TRUE(wahp.setMaximumSupplyAirTemperaturefromSupplementalHeater(55.0));
  ASSERT_TRUE(wahp.maximumSupplyAirTemperaturefromSupplementalHeater());
  EXPECT_DOUBLE_EQ(55.0, wahp.maximumSupplyAirTemperaturefromSupplementalHeater().get());
  wahp.autosizeMaximumSupplyAirTemperaturefromSupplementalHeater();
  EXPECT_TRUE(wahp.isMaximumSupplyAirTemperaturefromSupplementalHeaterAutosized());

  EXPECT_TRUE(wahp.setMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation(18.5));
  EXPECT_DOUBLE_EQ(18.5, wahp.maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation());
  wahp.resetMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation();
  EXPECT_TRUE(wahp.isMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperationDefaulted());

  EXPECT_TRUE(wahp.setFanPlacement("BlowThrough"));
  EXPECT_EQ("BlowThrough", wahp.fanPlacement());
  wahp.resetFanPlacement();
  EXPECT_TRUE(wahp.isFanPlacementDefaulted());

  EXPECT_TRUE(wahp.setHeatPumpCoilWaterFlowMode("Cycling"));
  EXPECT_EQ("Cycling", wahp.heatPumpCoilWaterFlowMode());
  wahp.resetHeatPumpCoilWaterFlowMode();
  EXPECT_TRUE(wahp.isHeatPumpCoilWaterFlowModeDefaulted());

  EXPECT_TRUE(wahp.setDXHeatingCoilSizingRatio(1.1));
  EXPECT_DOUBLE_EQ(1.1, wahp.dXHeatingCoilSizingRatio());
}

TEST_F(EPModelFixture, ZoneHVACWaterToAirHeatPump_TopologyAndChildren) {
  Model model;

  FanOnOff fan(model);
  CoilHeatingWaterToAirHeatPumpEquationFit heatingCoil(model);
  CoilCoolingWaterToAirHeatPumpEquationFit coolingCoil(model);
  CoilHeatingWater supplementalHeatingCoil(model);

  ZoneHVACWaterToAirHeatPump wahp(model);

  EXPECT_EQ(openstudio::ZoneHVAC_WaterToAirHeatPumpFields::AirInletNodeName, wahp.inletPort());
  EXPECT_EQ(openstudio::ZoneHVAC_WaterToAirHeatPumpFields::AirOutletNodeName, wahp.outletPort());

  EXPECT_TRUE(wahp.setSupplyAirFan(fan));
  EXPECT_TRUE(wahp.setHeatingCoil(heatingCoil));
  EXPECT_TRUE(wahp.setCoolingCoil(coolingCoil));
  EXPECT_TRUE(wahp.setSupplementalHeatingCoil(supplementalHeatingCoil));

  EXPECT_EQ(fan, wahp.supplyAirFan());
  EXPECT_EQ(heatingCoil, wahp.heatingCoil());
  EXPECT_EQ(coolingCoil, wahp.coolingCoil());
  EXPECT_EQ(supplementalHeatingCoil, wahp.supplementalHeatingCoil());

  const auto children = wahp.children();
  ASSERT_EQ(4u, children.size());
  EXPECT_EQ(fan, children[0]);
  EXPECT_EQ(heatingCoil, children[1]);
  EXPECT_EQ(coolingCoil, children[2]);
  EXPECT_EQ(supplementalHeatingCoil, children[3]);

  EXPECT_TRUE(fan.containingZoneHVACComponent());
  EXPECT_EQ(wahp, fan.containingZoneHVACComponent().get());
  EXPECT_TRUE(heatingCoil.containingZoneHVACComponent());
  EXPECT_EQ(wahp, heatingCoil.containingZoneHVACComponent().get());
  EXPECT_TRUE(coolingCoil.containingZoneHVACComponent());
  EXPECT_EQ(wahp, coolingCoil.containingZoneHVACComponent().get());
  EXPECT_TRUE(supplementalHeatingCoil.containingZoneHVACComponent());
  EXPECT_EQ(wahp, supplementalHeatingCoil.containingZoneHVACComponent().get());

  ThermalZone zone(model);
  EXPECT_TRUE(wahp.addToThermalZone(zone));
  EXPECT_TRUE(wahp.inletNode());
  EXPECT_TRUE(wahp.outletNode());
  wahp.removeFromThermalZone();
  EXPECT_FALSE(wahp.inletNode());
  EXPECT_FALSE(wahp.outletNode());
}
