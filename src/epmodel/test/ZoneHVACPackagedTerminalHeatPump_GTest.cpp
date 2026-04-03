/***********************************************************************************************************************  
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.  
*  See also https://openstudio.net/license  
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ZoneHVACComponent/ZoneHVACPackagedTerminalHeatPump.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../Schedule/ScheduleCompact.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Schedule/ScheduleConstant_Impl.hpp"
#include "../StraightComponent/Node.hpp"
#include "../StraightComponent/CoilCoolingDXSingleSpeed.hpp"
#include "../StraightComponent/CoilHeatingDXSingleSpeed.hpp"
#include "../StraightComponent/CoilHeatingElectric.hpp"
#include "../StraightComponent/FanOnOff.hpp"

#include <utilities/idd/ZoneHVAC_PackagedTerminalHeatPump_FieldEnums.hxx>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ZoneHVACPackagedTerminalHeatPump_DefaultConstructor) {
  Model model;
  ZoneHVACPackagedTerminalHeatPump pthp(model);

  EXPECT_FALSE(pthp.supplyAirFlowRateDuringCoolingOperation());
  EXPECT_FALSE(pthp.isSupplyAirFlowRateDuringCoolingOperationAutosized());
  EXPECT_FALSE(pthp.supplyAirFlowRateDuringHeatingOperation());
  EXPECT_FALSE(pthp.isSupplyAirFlowRateDuringHeatingOperationAutosized());
  EXPECT_FALSE(pthp.supplyAirFlowRateWhenNoCoolingorHeatingisNeeded());
  EXPECT_FALSE(pthp.isSupplyAirFlowRateWhenNoCoolingorHeatingisNeededAutosized());
  EXPECT_FALSE(pthp.noLoadSupplyAirFlowRateControlSetToLowSpeed());
  EXPECT_FALSE(pthp.outdoorAirFlowRateDuringCoolingOperation());
  EXPECT_FALSE(pthp.isOutdoorAirFlowRateDuringCoolingOperationAutosized());
  EXPECT_FALSE(pthp.outdoorAirFlowRateDuringHeatingOperation());
  EXPECT_FALSE(pthp.isOutdoorAirFlowRateDuringHeatingOperationAutosized());
  EXPECT_FALSE(pthp.outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded());
  EXPECT_FALSE(pthp.isOutdoorAirFlowRateWhenNoCoolingorHeatingisNeededAutosized());
  EXPECT_TRUE(pthp.isHeatingConvergenceToleranceDefaulted());
  EXPECT_TRUE(pthp.isMinimumOutdoorDryBulbTemperatureforCompressorOperationDefaulted());
  EXPECT_TRUE(pthp.isCoolingConvergenceToleranceDefaulted());
  EXPECT_TRUE(pthp.isMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperationDefaulted());
  EXPECT_TRUE(pthp.isFanPlacementDefaulted());
  EXPECT_EQ("", pthp.fanPlacement());
}

TEST_F(EPModelFixture, ZoneHVACPackagedTerminalHeatPump_ScalarAccessors_RoundTrip) {
  Model model;
  ZoneHVACPackagedTerminalHeatPump pthp(model);

  EXPECT_TRUE(pthp.setSupplyAirFlowRateDuringCoolingOperation(0.55));
  ASSERT_TRUE(pthp.supplyAirFlowRateDuringCoolingOperation());
  EXPECT_DOUBLE_EQ(0.55, pthp.supplyAirFlowRateDuringCoolingOperation().get());
  EXPECT_FALSE(pthp.isSupplyAirFlowRateDuringCoolingOperationAutosized());
  pthp.autosizeSupplyAirFlowRateDuringCoolingOperation();
  EXPECT_TRUE(pthp.isSupplyAirFlowRateDuringCoolingOperationAutosized());

  EXPECT_TRUE(pthp.setSupplyAirFlowRateDuringHeatingOperation(0.6));
  ASSERT_TRUE(pthp.supplyAirFlowRateDuringHeatingOperation());
  EXPECT_DOUBLE_EQ(0.6, pthp.supplyAirFlowRateDuringHeatingOperation().get());
  pthp.autosizeSupplyAirFlowRateDuringHeatingOperation();
  EXPECT_TRUE(pthp.isSupplyAirFlowRateDuringHeatingOperationAutosized());

  EXPECT_TRUE(pthp.setSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded(0.15));
  ASSERT_TRUE(pthp.supplyAirFlowRateWhenNoCoolingorHeatingisNeeded());
  EXPECT_DOUBLE_EQ(0.15, pthp.supplyAirFlowRateWhenNoCoolingorHeatingisNeeded().get());
  pthp.resetSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded();
  EXPECT_FALSE(pthp.supplyAirFlowRateWhenNoCoolingorHeatingisNeeded());
  pthp.autosizeSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded();
  EXPECT_TRUE(pthp.isSupplyAirFlowRateWhenNoCoolingorHeatingisNeededAutosized());

  EXPECT_TRUE(pthp.setNoLoadSupplyAirFlowRateControlSetToLowSpeed(true));
  EXPECT_TRUE(pthp.noLoadSupplyAirFlowRateControlSetToLowSpeed());

  EXPECT_TRUE(pthp.setOutdoorAirFlowRateDuringCoolingOperation(0.2));
  pthp.autosizeOutdoorAirFlowRateDuringCoolingOperation();
  EXPECT_TRUE(pthp.isOutdoorAirFlowRateDuringCoolingOperationAutosized());

  EXPECT_TRUE(pthp.setOutdoorAirFlowRateDuringHeatingOperation(0.18));
  pthp.autosizeOutdoorAirFlowRateDuringHeatingOperation();
  EXPECT_TRUE(pthp.isOutdoorAirFlowRateDuringHeatingOperationAutosized());

  EXPECT_TRUE(pthp.setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(0.05));
  pthp.resetOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded();
  EXPECT_FALSE(pthp.outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded());
  pthp.autosizeOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded();
  EXPECT_TRUE(pthp.isOutdoorAirFlowRateWhenNoCoolingorHeatingisNeededAutosized());

  EXPECT_TRUE(pthp.setHeatingConvergenceTolerance(0.0025));
  EXPECT_DOUBLE_EQ(0.0025, pthp.heatingConvergenceTolerance());
  pthp.resetHeatingConvergenceTolerance();
  EXPECT_TRUE(pthp.isHeatingConvergenceToleranceDefaulted());

  const double legacyMinOdb = pthp.minimumOutdoorDryBulbTemperatureforCompressorOperation();
  EXPECT_FALSE(pthp.setMinimumOutdoorDryBulbTemperatureforCompressorOperation(-18.0));
  EXPECT_DOUBLE_EQ(legacyMinOdb, pthp.minimumOutdoorDryBulbTemperatureforCompressorOperation());
  pthp.resetMinimumOutdoorDryBulbTemperatureforCompressorOperation();
  EXPECT_TRUE(pthp.isMinimumOutdoorDryBulbTemperatureforCompressorOperationDefaulted());

  EXPECT_TRUE(pthp.setCoolingConvergenceTolerance(0.0027));
  EXPECT_DOUBLE_EQ(0.0027, pthp.coolingConvergenceTolerance());
  pthp.resetCoolingConvergenceTolerance();
  EXPECT_TRUE(pthp.isCoolingConvergenceToleranceDefaulted());

  EXPECT_TRUE(pthp.setMaximumSupplyAirTemperaturefromSupplementalHeater(60.0));
  ASSERT_TRUE(pthp.maximumSupplyAirTemperaturefromSupplementalHeater());
  EXPECT_DOUBLE_EQ(60.0, pthp.maximumSupplyAirTemperaturefromSupplementalHeater().get());
  pthp.autosizeMaximumSupplyAirTemperaturefromSupplementalHeater();
  EXPECT_TRUE(pthp.isMaximumSupplyAirTemperaturefromSupplementalHeaterAutosized());

  EXPECT_TRUE(pthp.setMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation(18.0));
  EXPECT_DOUBLE_EQ(18.0, pthp.maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation());
  pthp.resetMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation();
  EXPECT_TRUE(pthp.isMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperationDefaulted());

  EXPECT_TRUE(pthp.setFanPlacement("BlowThrough"));
  EXPECT_EQ("BlowThrough", pthp.fanPlacement());
  pthp.resetFanPlacement();
  EXPECT_TRUE(pthp.isFanPlacementDefaulted());

  EXPECT_TRUE(pthp.setDXHeatingCoilSizingRatio(1.1));
  EXPECT_DOUBLE_EQ(1.1, pthp.dXHeatingCoilSizingRatio());
}

TEST_F(EPModelFixture, ZoneHVACPackagedTerminalHeatPump_TopologyAndChildren) {
  Model model;
  FanOnOff fan(model);
  CoilHeatingDXSingleSpeed heatingCoil(model);
  CoilCoolingDXSingleSpeed coolingCoil(model);
  CoilHeatingElectric supplementalHeatingCoil(model);
  ZoneHVACPackagedTerminalHeatPump pthp(model);

  EXPECT_EQ(openstudio::ZoneHVAC_PackagedTerminalHeatPumpFields::AirInletNodeName, pthp.inletPort());
  EXPECT_EQ(openstudio::ZoneHVAC_PackagedTerminalHeatPumpFields::AirOutletNodeName, pthp.outletPort());

  EXPECT_TRUE(pthp.setSupplyAirFan(fan));
  EXPECT_TRUE(pthp.setHeatingCoil(heatingCoil));
  EXPECT_TRUE(pthp.setCoolingCoil(coolingCoil));
  EXPECT_TRUE(pthp.setSupplementalHeatingCoil(supplementalHeatingCoil));

  EXPECT_EQ(fan, pthp.supplyAirFan());
  EXPECT_EQ(heatingCoil, pthp.heatingCoil());
  EXPECT_EQ(coolingCoil, pthp.coolingCoil());
  EXPECT_EQ(supplementalHeatingCoil, pthp.supplementalHeatingCoil());

  const auto children = pthp.children();
  ASSERT_EQ(4u, children.size());
  EXPECT_EQ(fan, children.at(0));
  EXPECT_EQ(heatingCoil, children.at(1));
  EXPECT_EQ(coolingCoil, children.at(2));
  EXPECT_EQ(supplementalHeatingCoil, children.at(3));

  EXPECT_EQ(pthp, fan.containingZoneHVACComponent().get());
  EXPECT_EQ(pthp, heatingCoil.containingZoneHVACComponent().get());
  EXPECT_EQ(pthp, coolingCoil.containingZoneHVACComponent().get());
  EXPECT_EQ(pthp, supplementalHeatingCoil.containingZoneHVACComponent().get());

  ThermalZone zone(model);
  EXPECT_TRUE(pthp.addToThermalZone(zone));
  ASSERT_TRUE(pthp.inletNode());
  ASSERT_TRUE(pthp.outletNode());
  EXPECT_TRUE(pthp.thermalZone());
  pthp.removeFromThermalZone();
  EXPECT_FALSE(pthp.thermalZone());
}

TEST_F(EPModelFixture, ZoneHVACPackagedTerminalHeatPump_ScheduleRelationships_RoundTrip) {
  Model model;
  ZoneHVACPackagedTerminalHeatPump pthp(model);

  auto defaultAvailability = pthp.availabilitySchedule().optionalCast<ScheduleConstant>();
  ASSERT_TRUE(defaultAvailability);
  EXPECT_DOUBLE_EQ(1.0, defaultAvailability->value());
  auto defaultFanMode = pthp.supplyAirFanOperatingModeSchedule().optionalCast<ScheduleConstant>();
  ASSERT_TRUE(defaultFanMode);
  EXPECT_DOUBLE_EQ(1.0, defaultFanMode->value());

  ScheduleCompact availability(model);
  ScheduleCompact fanMode(model);
  ASSERT_TRUE(availability.setToConstantValue(0.6));
  ASSERT_TRUE(fanMode.setToConstantValue(0.0));

  EXPECT_TRUE(pthp.setAvailabilitySchedule(availability));
  EXPECT_TRUE(pthp.setSupplyAirFanOperatingModeSchedule(fanMode));
  EXPECT_EQ(availability.handle(), pthp.availabilitySchedule().handle());
  EXPECT_EQ(fanMode.handle(), pthp.supplyAirFanOperatingModeSchedule().handle());
}
