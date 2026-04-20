/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/HVACTemplateSystemDualDuct.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, HVACTemplateSystemDualDuct_DefaultConstructor) {
  Model model;
  HVACTemplateSystemDualDuct object(model);
  EXPECT_EQ(HVACTemplateSystemDualDuct::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, HVACTemplateSystemDualDuct_ScalarAccessors_RoundTrip) {
  Model model;
  HVACTemplateSystemDualDuct object(model);

  EXPECT_TRUE(object.setSystemConfigurationType("DualFanVariableVolume"));
  EXPECT_EQ("DualFanVariableVolume", object.systemConfigurationType());

  EXPECT_TRUE(object.setMainSupplyFanMaximumFlowRate(1.2));
  ASSERT_TRUE(object.mainSupplyFanMaximumFlowRate());
  EXPECT_DOUBLE_EQ(1.2, object.mainSupplyFanMaximumFlowRate().get());
  EXPECT_FALSE(object.isMainSupplyFanMaximumFlowRateAutosized());
  object.autosizeMainSupplyFanMaximumFlowRate();
  EXPECT_TRUE(object.isMainSupplyFanMaximumFlowRateAutosized());

  EXPECT_TRUE(object.setEconomizerUpperTemperatureLimit(26.0));
  ASSERT_TRUE(object.economizerUpperTemperatureLimit());
  EXPECT_DOUBLE_EQ(26.0, object.economizerUpperTemperatureLimit().get());
  object.resetEconomizerUpperTemperatureLimit();
  EXPECT_FALSE(object.economizerUpperTemperatureLimit());

  EXPECT_TRUE(object.setReturnFan(true));
  EXPECT_TRUE(object.returnFan());
  EXPECT_TRUE(object.setReturnFanTotalEfficiency(0.75));
  EXPECT_DOUBLE_EQ(0.75, object.returnFanTotalEfficiency());

  EXPECT_TRUE(object.setHumidifierRatedElectricPower(800.0));
  ASSERT_TRUE(object.humidifierRatedElectricPower());
  EXPECT_DOUBLE_EQ(800.0, object.humidifierRatedElectricPower().get());
  object.autosizeHumidifierRatedElectricPower();
  EXPECT_TRUE(object.isHumidifierRatedElectricPowerAutosized());

  EXPECT_FALSE(object.setSystemConfigurationType("InvalidChoice"));
  EXPECT_FALSE(object.setMainSupplyFanMinimumFlowFraction(2.0));
  EXPECT_FALSE(object.setReturnFanTotalEfficiency(0.0));

  EXPECT_GE(HVACTemplateSystemDualDuct::systemConfigurationTypeValues().size(), 1u);
  EXPECT_GE(HVACTemplateSystemDualDuct::coolingCoilTypeValues().size(), 1u);
  EXPECT_GE(HVACTemplateSystemDualDuct::economizerTypeValues().size(), 1u);
}
