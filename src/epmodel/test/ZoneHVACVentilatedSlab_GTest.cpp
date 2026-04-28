/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "EPModelFixture.hpp"

#include "../scaffolds/ZoneHVACVentilatedSlab.hpp"

#include <algorithm>

using namespace openstudio;
using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ZoneHVACVentilatedSlab_ScalarAccessors_RoundTrip) {
  Model model;
  ZoneHVACVentilatedSlab slab(model);

  EXPECT_TRUE(slab.setMaximumAirFlowRate(1.25));
  EXPECT_TRUE(slab.maximumAirFlowRate());
  EXPECT_DOUBLE_EQ(1.25, *slab.maximumAirFlowRate());
  EXPECT_FALSE(slab.isMaximumAirFlowRateAutosized());
  slab.autosizeMaximumAirFlowRate();
  EXPECT_TRUE(slab.isMaximumAirFlowRateAutosized());

  EXPECT_TRUE(slab.setMinimumOutdoorAirFlowRate(0.2));
  EXPECT_TRUE(slab.minimumOutdoorAirFlowRate());
  EXPECT_DOUBLE_EQ(0.2, *slab.minimumOutdoorAirFlowRate());
  EXPECT_FALSE(slab.isMinimumOutdoorAirFlowRateAutosized());
  slab.autosizeMinimumOutdoorAirFlowRate();
  EXPECT_TRUE(slab.isMinimumOutdoorAirFlowRateAutosized());

  EXPECT_TRUE(slab.setMaximumOutdoorAirFlowRate(0.35));
  EXPECT_TRUE(slab.maximumOutdoorAirFlowRate());
  EXPECT_DOUBLE_EQ(0.35, *slab.maximumOutdoorAirFlowRate());
  EXPECT_FALSE(slab.isMaximumOutdoorAirFlowRateAutosized());
  slab.autosizeMaximumOutdoorAirFlowRate();
  EXPECT_TRUE(slab.isMaximumOutdoorAirFlowRateAutosized());

  auto outdoorAirValues = ZoneHVACVentilatedSlab::outdoorAirControlTypeValues();
  EXPECT_FALSE(outdoorAirValues.empty());
  EXPECT_NE(outdoorAirValues.end(), std::find(outdoorAirValues.begin(), outdoorAirValues.end(), "VariablePercent"));
  EXPECT_TRUE(slab.setOutdoorAirControlType("FixedTemperature"));
  EXPECT_EQ("FixedTemperature", slab.outdoorAirControlType());

  auto configValues = ZoneHVACVentilatedSlab::systemConfigurationTypeValues();
  EXPECT_FALSE(configValues.empty());
  EXPECT_TRUE(slab.setSystemConfigurationType(configValues.back()));
  EXPECT_FALSE(slab.isSystemConfigurationTypeDefaulted());
  slab.resetSystemConfigurationType();
  EXPECT_TRUE(slab.isSystemConfigurationTypeDefaulted());

  EXPECT_TRUE(slab.setHollowCoreInsideDiameter(0.045));
  EXPECT_TRUE(slab.hollowCoreInsideDiameter());
  EXPECT_NEAR(0.045, *slab.hollowCoreInsideDiameter(), 1e-8);
  slab.resetHollowCoreInsideDiameter();
  EXPECT_TRUE(slab.hollowCoreInsideDiameter());

  EXPECT_TRUE(slab.setHollowCoreLength(2.5));
  EXPECT_TRUE(slab.hollowCoreLength());
  EXPECT_NEAR(2.5, *slab.hollowCoreLength(), 1e-8);
  slab.resetHollowCoreLength();
  EXPECT_FALSE(slab.hollowCoreLength());

  auto temperatureValues = ZoneHVACVentilatedSlab::temperatureControlTypeValues();
  EXPECT_FALSE(temperatureValues.empty());
  EXPECT_TRUE(slab.setTemperatureControlType(temperatureValues.front()));
  EXPECT_FALSE(slab.isTemperatureControlTypeDefaulted());
  slab.resetTemperatureControlType();
  EXPECT_TRUE(slab.isTemperatureControlTypeDefaulted());

  auto coilOptionValues = ZoneHVACVentilatedSlab::coilOptionTypeValues();
  EXPECT_FALSE(coilOptionValues.empty());
  EXPECT_TRUE(slab.setCoilOptionType(coilOptionValues.front()));
  EXPECT_EQ(coilOptionValues.front(), slab.coilOptionType());

  auto heatingCoilValues = ZoneHVACVentilatedSlab::heatingCoilObjectTypeValues();
  EXPECT_FALSE(heatingCoilValues.empty());
  EXPECT_TRUE(slab.setHeatingCoilObjectType(heatingCoilValues.front()));
  EXPECT_TRUE(slab.heatingCoilObjectType());
  slab.resetHeatingCoilObjectType();
  EXPECT_TRUE(slab.heatingCoilObjectType());
  EXPECT_TRUE(slab.heatingCoilObjectType()->empty());

  auto coolingCoilValues = ZoneHVACVentilatedSlab::coolingCoilObjectTypeValues();
  EXPECT_FALSE(coolingCoilValues.empty());
  EXPECT_TRUE(slab.setCoolingCoilObjectType(coolingCoilValues.front()));
  EXPECT_TRUE(slab.coolingCoilObjectType());
  slab.resetCoolingCoilObjectType();
  EXPECT_TRUE(slab.coolingCoilObjectType());
  EXPECT_TRUE(slab.coolingCoilObjectType()->empty());
}
