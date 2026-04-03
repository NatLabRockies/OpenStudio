/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "../ModelObject/ModelObject.hpp"
#include "EPModelFixture.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../Schedule/ScheduleCompact.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Schedule/ScheduleConstant_Impl.hpp"
#include "../StraightComponent/CoilHeatingElectric.hpp"
#include "../StraightComponent/FanConstantVolume.hpp"
#include "../StraightComponent/Node.hpp"
#include "../WaterToAirComponent/CoilCoolingWater.hpp"
#include "../ZoneHVACComponent/ZoneHVACUnitVentilator.hpp"

#include <utilities/idd/ZoneHVAC_UnitVentilator_FieldEnums.hxx>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ZoneHVACUnitVentilator_DefaultConstructor) {
  Model model;
  ZoneHVACUnitVentilator ventilator(model);

  EXPECT_EQ(ZoneHVACUnitVentilator::iddObjectType(), ventilator.iddObject().type());
  EXPECT_TRUE(ventilator.isMaximumSupplyAirFlowRateAutosized());
  EXPECT_EQ("VariablePercent", ventilator.outdoorAirControlType());
  EXPECT_TRUE(ventilator.isMinimumOutdoorAirFlowRateAutosized());
  EXPECT_TRUE(ventilator.isMaximumOutdoorAirFlowRateAutosized());
  EXPECT_DOUBLE_EQ(0.001, ventilator.heatingConvergenceTolerance());
  EXPECT_DOUBLE_EQ(0.001, ventilator.coolingConvergenceTolerance());
}

TEST_F(EPModelFixture, ZoneHVACUnitVentilator_ScalarAccessors_RoundTrip) {
  Model model;
  ZoneHVACUnitVentilator ventilator(model);

  EXPECT_TRUE(ventilator.setMaximumSupplyAirFlowRate(0.42));
  EXPECT_FALSE(ventilator.isMaximumSupplyAirFlowRateAutosized());

  auto controlTypes = ZoneHVACUnitVentilator::outdoorAirControlTypeValues();
  ASSERT_FALSE(controlTypes.empty());
  std::string overrideType = controlTypes[0];
  if (overrideType == "VariablePercent" && controlTypes.size() > 1) {
    overrideType = controlTypes[1];
  }
  EXPECT_TRUE(ventilator.setOutdoorAirControlType(overrideType));
  EXPECT_EQ(overrideType, ventilator.outdoorAirControlType());

  EXPECT_TRUE(ventilator.setMinimumOutdoorAirFlowRate(0.1));
  EXPECT_TRUE(ventilator.setMaximumOutdoorAirFlowRate(0.52));
  EXPECT_TRUE(ventilator.setHeatingConvergenceTolerance(0.005));
  EXPECT_TRUE(ventilator.setCoolingConvergenceTolerance(0.004));

  ASSERT_TRUE(ventilator.minimumOutdoorAirFlowRate());
  EXPECT_DOUBLE_EQ(0.1, ventilator.minimumOutdoorAirFlowRate().value());
  ASSERT_TRUE(ventilator.maximumOutdoorAirFlowRate());
  EXPECT_DOUBLE_EQ(0.52, ventilator.maximumOutdoorAirFlowRate().value());
  EXPECT_DOUBLE_EQ(0.005, ventilator.heatingConvergenceTolerance());
  EXPECT_DOUBLE_EQ(0.004, ventilator.coolingConvergenceTolerance());

  ventilator.autosizeMaximumSupplyAirFlowRate();
  EXPECT_TRUE(ventilator.isMaximumSupplyAirFlowRateAutosized());
  EXPECT_FALSE(ventilator.maximumSupplyAirFlowRate());

  ventilator.autosizeMinimumOutdoorAirFlowRate();
  EXPECT_TRUE(ventilator.isMinimumOutdoorAirFlowRateAutosized());
  EXPECT_FALSE(ventilator.minimumOutdoorAirFlowRate());

  ventilator.autosizeMaximumOutdoorAirFlowRate();
  EXPECT_TRUE(ventilator.isMaximumOutdoorAirFlowRateAutosized());
  EXPECT_FALSE(ventilator.maximumOutdoorAirFlowRate());
}

TEST_F(EPModelFixture, ZoneHVACUnitVentilator_TopologyAndChildren) {
  Model model;
  ZoneHVACUnitVentilator ventilator(model);
  ThermalZone zone(model);

  EXPECT_EQ(openstudio::ZoneHVAC_UnitVentilatorFields::AirInletNodeName, ventilator.inletPort());
  EXPECT_EQ(openstudio::ZoneHVAC_UnitVentilatorFields::AirOutletNodeName, ventilator.outletPort());

  EXPECT_TRUE(ventilator.addToThermalZone(zone));
  ASSERT_TRUE(ventilator.thermalZone());
  EXPECT_EQ(zone, ventilator.thermalZone().get());
  EXPECT_TRUE(ventilator.inletNode());
  EXPECT_TRUE(ventilator.outletNode());

  FanConstantVolume supplyFan(model);
  CoilHeatingElectric heatingCoil(model);
  CoilCoolingWater coolingCoil(model);

  ASSERT_TRUE(ventilator.setPointer(openstudio::ZoneHVAC_UnitVentilatorFields::SupplyAirFanName, supplyFan.handle()));
  ASSERT_TRUE(ventilator.setPointer(openstudio::ZoneHVAC_UnitVentilatorFields::HeatingCoilName, heatingCoil.handle()));
  ASSERT_TRUE(ventilator.setPointer(openstudio::ZoneHVAC_UnitVentilatorFields::CoolingCoilName, coolingCoil.handle()));

  const auto children = ventilator.children();
  ASSERT_EQ(3u, children.size());
  EXPECT_EQ(supplyFan.handle(), children[0].handle());
  EXPECT_EQ(heatingCoil.handle(), children[1].handle());
  EXPECT_EQ(coolingCoil.handle(), children[2].handle());

  ventilator.removeFromThermalZone();
  EXPECT_FALSE(ventilator.thermalZone());
  EXPECT_FALSE(ventilator.inletNode());
  EXPECT_FALSE(ventilator.outletNode());
}

TEST_F(EPModelFixture, ZoneHVACUnitVentilator_HvacRelationships_RoundTrip) {
  Model model;
  ZoneHVACUnitVentilator ventilator(model);

  auto defaultSchedule = ventilator.availabilitySchedule().optionalCast<ScheduleConstant>();
  ASSERT_TRUE(defaultSchedule);
  EXPECT_DOUBLE_EQ(1.0, defaultSchedule->value());

  ScheduleCompact availability(model);
  ScheduleCompact minimumOutdoorAir(model);
  ScheduleCompact maximumOutdoorAir(model);
  ScheduleCompact fanMode(model);
  ASSERT_TRUE(availability.setToConstantValue(0.5));
  ASSERT_TRUE(minimumOutdoorAir.setToConstantValue(0.2));
  ASSERT_TRUE(maximumOutdoorAir.setToConstantValue(0.7));
  ASSERT_TRUE(fanMode.setToConstantValue(1.0));

  EXPECT_TRUE(ventilator.setAvailabilitySchedule(availability));
  EXPECT_TRUE(ventilator.setMinimumOutdoorAirSchedule(minimumOutdoorAir));
  EXPECT_TRUE(ventilator.setMaximumOutdoorAirFractionorTemperatureSchedule(maximumOutdoorAir));
  EXPECT_TRUE(ventilator.setSupplyAirFanOperatingModeSchedule(fanMode));

  EXPECT_EQ(availability.handle(), ventilator.availabilitySchedule().handle());
  EXPECT_EQ(minimumOutdoorAir.handle(), ventilator.minimumOutdoorAirSchedule().handle());
  EXPECT_EQ(maximumOutdoorAir.handle(), ventilator.maximumOutdoorAirFractionorTemperatureSchedule().handle());
  ASSERT_TRUE(ventilator.supplyAirFanOperatingModeSchedule());
  EXPECT_EQ(fanMode.handle(), ventilator.supplyAirFanOperatingModeSchedule()->handle());

  FanConstantVolume supplyFan(model);
  CoilHeatingElectric heatingCoil(model);
  CoilCoolingWater coolingCoil(model);
  EXPECT_TRUE(ventilator.setSupplyAirFan(supplyFan));
  EXPECT_TRUE(ventilator.setHeatingCoil(heatingCoil));
  EXPECT_TRUE(ventilator.setCoolingCoil(coolingCoil));
  EXPECT_EQ(supplyFan.handle(), ventilator.supplyAirFan().handle());
  ASSERT_TRUE(ventilator.heatingCoil());
  EXPECT_EQ(heatingCoil.handle(), ventilator.heatingCoil()->handle());
  ASSERT_TRUE(ventilator.coolingCoil());
  EXPECT_EQ(coolingCoil.handle(), ventilator.coolingCoil()->handle());

  ventilator.resetSupplyAirFanOperatingModeSchedule();
  EXPECT_FALSE(ventilator.supplyAirFanOperatingModeSchedule());
  ventilator.resetHeatingCoil();
  EXPECT_FALSE(ventilator.heatingCoil());
  ventilator.resetCoolingCoil();
  EXPECT_FALSE(ventilator.coolingCoil());
}
