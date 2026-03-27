/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "../ModelObject/ModelObject.hpp"
#include "EPModelFixture.hpp"
#include "../HVACComponent/ThermalZone.hpp"
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
