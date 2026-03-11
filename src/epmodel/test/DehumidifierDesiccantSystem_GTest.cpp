/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/DehumidifierDesiccantSystem.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, DehumidifierDesiccantSystem_DefaultConstructor) {
  Model model;
  DehumidifierDesiccantSystem dehumidifier(model);
  EXPECT_EQ(DehumidifierDesiccantSystem::iddObjectType(), dehumidifier.iddObject().type());
}

TEST_F(EPModelFixture, DehumidifierDesiccantSystem_ScalarAccessors_RoundTrip) {
  Model model;
  DehumidifierDesiccantSystem dehumidifier(model);

  EXPECT_TRUE(dehumidifier.setDesiccantHeatExchangerObjectType("HeatExchanger:Desiccant:BalancedFlow"));
  EXPECT_EQ("HeatExchanger:Desiccant:BalancedFlow", dehumidifier.desiccantHeatExchangerObjectType());

  EXPECT_TRUE(dehumidifier.setRegenerationAirFanObjectType("Fan:SystemModel"));
  EXPECT_EQ("Fan:SystemModel", dehumidifier.regenerationAirFanObjectType());

  EXPECT_TRUE(dehumidifier.isRegenerationAirFanPlacementDefaulted());
  EXPECT_EQ("DrawThrough", dehumidifier.regenerationAirFanPlacement());
  EXPECT_TRUE(dehumidifier.setRegenerationAirFanPlacement("BlowThrough"));
  EXPECT_EQ("BlowThrough", dehumidifier.regenerationAirFanPlacement());
  dehumidifier.resetRegenerationAirFanPlacement();
  EXPECT_TRUE(dehumidifier.isRegenerationAirFanPlacementDefaulted());
  EXPECT_EQ("DrawThrough", dehumidifier.regenerationAirFanPlacement());

  EXPECT_TRUE(dehumidifier.setRegenerationAirHeaterObjectType("Coil:Heating:Electric"));
  ASSERT_TRUE(dehumidifier.regenerationAirHeaterObjectType());
  EXPECT_EQ("Coil:Heating:Electric", dehumidifier.regenerationAirHeaterObjectType().get());
  dehumidifier.resetRegenerationAirHeaterObjectType();
  EXPECT_TRUE(dehumidifier.regenerationAirHeaterObjectType());

  EXPECT_TRUE(dehumidifier.isRegenerationInletAirSetpointTemperatureDefaulted());
  EXPECT_DOUBLE_EQ(46.0, dehumidifier.regenerationInletAirSetpointTemperature());
  EXPECT_TRUE(dehumidifier.setRegenerationInletAirSetpointTemperature(55.0));
  EXPECT_DOUBLE_EQ(55.0, dehumidifier.regenerationInletAirSetpointTemperature());
  dehumidifier.resetRegenerationInletAirSetpointTemperature();
  EXPECT_TRUE(dehumidifier.isRegenerationInletAirSetpointTemperatureDefaulted());
  EXPECT_DOUBLE_EQ(46.0, dehumidifier.regenerationInletAirSetpointTemperature());

  EXPECT_TRUE(dehumidifier.setCompanionCoolingCoilObjectType("Coil:Cooling:DX:SingleSpeed"));
  ASSERT_TRUE(dehumidifier.companionCoolingCoilObjectType());
  EXPECT_EQ("Coil:Cooling:DX:SingleSpeed", dehumidifier.companionCoolingCoilObjectType().get());
  dehumidifier.resetCompanionCoolingCoilObjectType();
  EXPECT_TRUE(dehumidifier.companionCoolingCoilObjectType());

  EXPECT_TRUE(dehumidifier.isCompanionCoolingCoilUpstreamofDehumidifierProcessInletDefaulted());
  EXPECT_FALSE(dehumidifier.companionCoolingCoilUpstreamofDehumidifierProcessInlet());
  EXPECT_TRUE(dehumidifier.setCompanionCoolingCoilUpstreamofDehumidifierProcessInlet(true));
  EXPECT_TRUE(dehumidifier.companionCoolingCoilUpstreamofDehumidifierProcessInlet());
  dehumidifier.resetCompanionCoolingCoilUpstreamofDehumidifierProcessInlet();
  EXPECT_TRUE(dehumidifier.isCompanionCoolingCoilUpstreamofDehumidifierProcessInletDefaulted());
  EXPECT_FALSE(dehumidifier.companionCoolingCoilUpstreamofDehumidifierProcessInlet());

  EXPECT_TRUE(dehumidifier.isCompanionCoilRegenerationAirHeatingDefaulted());
  EXPECT_FALSE(dehumidifier.companionCoilRegenerationAirHeating());
  EXPECT_TRUE(dehumidifier.setCompanionCoilRegenerationAirHeating(true));
  EXPECT_TRUE(dehumidifier.companionCoilRegenerationAirHeating());
  dehumidifier.resetCompanionCoilRegenerationAirHeating();
  EXPECT_TRUE(dehumidifier.isCompanionCoilRegenerationAirHeatingDefaulted());
  EXPECT_FALSE(dehumidifier.companionCoilRegenerationAirHeating());

  EXPECT_TRUE(dehumidifier.setExhaustFanMaximumFlowRate(0.9));
  ASSERT_TRUE(dehumidifier.exhaustFanMaximumFlowRate());
  EXPECT_DOUBLE_EQ(0.9, dehumidifier.exhaustFanMaximumFlowRate().get());
  dehumidifier.resetExhaustFanMaximumFlowRate();
  EXPECT_FALSE(dehumidifier.exhaustFanMaximumFlowRate());

  EXPECT_TRUE(dehumidifier.setExhaustFanMaximumPower(250.0));
  ASSERT_TRUE(dehumidifier.exhaustFanMaximumPower());
  EXPECT_DOUBLE_EQ(250.0, dehumidifier.exhaustFanMaximumPower().get());
  dehumidifier.resetExhaustFanMaximumPower();
  EXPECT_FALSE(dehumidifier.exhaustFanMaximumPower());
}
