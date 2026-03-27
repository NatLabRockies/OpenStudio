/***********************************************************************************************************************  
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.  
*  See also https://openstudio.net/license  
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../StraightComponent/Node.hpp"
#include "../ZoneHVACComponent/ZoneHVACLowTemperatureRadiantElectric.hpp"

using namespace openstudio;
using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ZoneHVACLowTemperatureRadiantElectric_DefaultConstructor) {
  Model model;
  ZoneHVACLowTemperatureRadiantElectric radiant(model);

  EXPECT_FALSE(radiant.maximumElectricalPowertoPanel());
  EXPECT_TRUE(radiant.isMaximumElectricalPowertoPanelDefaulted());
  EXPECT_TRUE(radiant.isMaximumElectricalPowertoPanelAutosized());
  EXPECT_TRUE(radiant.isTemperatureControlTypeDefaulted());
  EXPECT_TRUE(radiant.isSetpointControlTypeDefaulted());
  EXPECT_TRUE(radiant.isHeatingThrottlingRangeDefaulted());
  EXPECT_EQ(0u, radiant.inletPort());
  EXPECT_EQ(0u, radiant.outletPort());
}

TEST_F(EPModelFixture, ZoneHVACLowTemperatureRadiantElectric_ScalarAccessors_RoundTrip) {
  Model model;
  ZoneHVACLowTemperatureRadiantElectric radiant(model);

  EXPECT_TRUE(radiant.setMaximumElectricalPowertoPanel(150.0));
  ASSERT_TRUE(radiant.maximumElectricalPowertoPanel());
  EXPECT_DOUBLE_EQ(150.0, radiant.maximumElectricalPowertoPanel().get());
  radiant.autosizeMaximumElectricalPowertoPanel();
  EXPECT_TRUE(radiant.isMaximumElectricalPowertoPanelAutosized());
  radiant.resetMaximumElectricalPowertoPanel();
  EXPECT_TRUE(radiant.isMaximumElectricalPowertoPanelDefaulted());

  auto temperatureControlTypes = ZoneHVACLowTemperatureRadiantElectric::temperatureControlTypeValues();
  ASSERT_FALSE(temperatureControlTypes.empty());
  EXPECT_TRUE(radiant.setTemperatureControlType(temperatureControlTypes.front()));
  EXPECT_EQ(temperatureControlTypes.front(), radiant.temperatureControlType());
  radiant.resetTemperatureControlType();
  EXPECT_TRUE(radiant.isTemperatureControlTypeDefaulted());

  EXPECT_TRUE(radiant.setSetpointControlType("ZeroFlowPower"));
  EXPECT_EQ("ZeroFlowPower", radiant.setpointControlType());
  EXPECT_FALSE(radiant.isSetpointControlTypeDefaulted());
  radiant.resetSetpointControlType();
  EXPECT_TRUE(radiant.isSetpointControlTypeDefaulted());

  EXPECT_TRUE(radiant.setHeatingThrottlingRange(2.5));
  EXPECT_DOUBLE_EQ(2.5, radiant.heatingThrottlingRange());
  radiant.resetHeatingThrottlingRange();
  EXPECT_TRUE(radiant.isHeatingThrottlingRangeDefaulted());
}

TEST_F(EPModelFixture, ZoneHVACLowTemperatureRadiantElectric_ZoneAttachment) {
  Model model;
  ThermalZone zone(model);
  ZoneHVACLowTemperatureRadiantElectric radiant(model);

  EXPECT_TRUE(radiant.addToThermalZone(zone));
  ASSERT_TRUE(radiant.thermalZone());
  EXPECT_EQ(zone, radiant.thermalZone().get());
  EXPECT_FALSE(radiant.inletNode());
  EXPECT_FALSE(radiant.outletNode());

  radiant.removeFromThermalZone();
  EXPECT_FALSE(radiant.thermalZone());
}
