/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"
#include "../StraightComponent/HumidifierSteamGas.hpp"
#include "../StraightComponent/Node.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, HumidifierSteamGas_DefaultConstructor) {
  Model model;
  HumidifierSteamGas humidifier(model);
  EXPECT_EQ(HumidifierSteamGas::iddObjectType(), humidifier.iddObject().type());
  EXPECT_FALSE(humidifier.nameString().empty());

  EXPECT_TRUE(humidifier.isRatedCapacityAutosized());
  EXPECT_FALSE(humidifier.ratedCapacity());

  ASSERT_TRUE(humidifier.ratedGasUseRate());
  EXPECT_DOUBLE_EQ(104000.0, humidifier.ratedGasUseRate().get());
  EXPECT_FALSE(humidifier.isRatedGasUseRateAutosized());

  EXPECT_DOUBLE_EQ(0.8, humidifier.thermalEfficiency());
  EXPECT_TRUE(humidifier.isThermalEfficiencyDefaulted());

  EXPECT_FALSE(humidifier.ratedFanPower());

  EXPECT_DOUBLE_EQ(0.0, humidifier.auxiliaryElectricPower());
  EXPECT_TRUE(humidifier.isAuxiliaryElectricPowerDefaulted());

  EXPECT_EQ("FixedInletWaterTemperature", humidifier.inletWaterTemperatureOption());
  EXPECT_TRUE(humidifier.isInletWaterTemperatureOptionDefaulted());
}

TEST_F(EPModelFixture, HumidifierSteamGas_ScalarAccessors_RoundTrip) {
  Model model;
  HumidifierSteamGas humidifier(model);

  EXPECT_TRUE(humidifier.setRatedCapacity(0.42));
  ASSERT_TRUE(humidifier.ratedCapacity());
  EXPECT_DOUBLE_EQ(0.42, humidifier.ratedCapacity().get());
  EXPECT_FALSE(humidifier.isRatedCapacityAutosized());
  humidifier.autosizeRatedCapacity();
  EXPECT_TRUE(humidifier.isRatedCapacityAutosized());
  EXPECT_FALSE(humidifier.ratedCapacity());

  EXPECT_TRUE(humidifier.setRatedGasUseRate(1234.0));
  ASSERT_TRUE(humidifier.ratedGasUseRate());
  EXPECT_DOUBLE_EQ(1234.0, humidifier.ratedGasUseRate().get());
  EXPECT_FALSE(humidifier.isRatedGasUseRateAutosized());
  humidifier.autosizeRatedGasUseRate();
  EXPECT_TRUE(humidifier.isRatedGasUseRateAutosized());
  EXPECT_FALSE(humidifier.ratedGasUseRate());
  humidifier.resetRatedGasUseRate();
  EXPECT_FALSE(humidifier.ratedGasUseRate());
  EXPECT_FALSE(humidifier.isRatedGasUseRateAutosized());

  EXPECT_TRUE(humidifier.setThermalEfficiency(0.9));
  EXPECT_DOUBLE_EQ(0.9, humidifier.thermalEfficiency());
  EXPECT_FALSE(humidifier.isThermalEfficiencyDefaulted());
  humidifier.resetThermalEfficiency();
  EXPECT_DOUBLE_EQ(0.8, humidifier.thermalEfficiency());
  EXPECT_TRUE(humidifier.isThermalEfficiencyDefaulted());

  EXPECT_TRUE(humidifier.setRatedFanPower(110.0));
  ASSERT_TRUE(humidifier.ratedFanPower());
  EXPECT_DOUBLE_EQ(110.0, humidifier.ratedFanPower().get());
  humidifier.resetRatedFanPower();
  EXPECT_FALSE(humidifier.ratedFanPower());

  EXPECT_TRUE(humidifier.setAuxiliaryElectricPower(8.0));
  EXPECT_DOUBLE_EQ(8.0, humidifier.auxiliaryElectricPower());
  EXPECT_FALSE(humidifier.isAuxiliaryElectricPowerDefaulted());
  humidifier.resetAuxiliaryElectricPower();
  EXPECT_DOUBLE_EQ(0.0, humidifier.auxiliaryElectricPower());
  EXPECT_TRUE(humidifier.isAuxiliaryElectricPowerDefaulted());

  EXPECT_TRUE(humidifier.setInletWaterTemperatureOption("VariableInletWaterTemperature"));
  EXPECT_EQ("VariableInletWaterTemperature", humidifier.inletWaterTemperatureOption());
  EXPECT_FALSE(humidifier.isInletWaterTemperatureOptionDefaulted());
  humidifier.resetInletWaterTemperatureOption();
  EXPECT_EQ("FixedInletWaterTemperature", humidifier.inletWaterTemperatureOption());
  EXPECT_TRUE(humidifier.isInletWaterTemperatureOptionDefaulted());

  EXPECT_FALSE(humidifier.autosizedRatedCapacity());
  EXPECT_FALSE(humidifier.autosizedRatedGasUseRate());
}

TEST_F(EPModelFixture, HumidifierSteamGas_AddToNodeSupplyOnly) {
  Model model;
  AirLoopHVAC airLoop(model);
  HumidifierSteamGas supplyHumidifier(model);
  HumidifierSteamGas demandHumidifier(model);

  auto supplyInletNode = airLoop.supplyInletNode();
  EXPECT_TRUE(supplyHumidifier.addToNode(supplyInletNode));
  ASSERT_TRUE(supplyHumidifier.inletModelObject());
  EXPECT_EQ(supplyInletNode, supplyHumidifier.inletModelObject()->cast<Node>());
  EXPECT_TRUE(supplyHumidifier.outletModelObject());

  auto demandInletNode = airLoop.demandInletNode();
  EXPECT_FALSE(demandHumidifier.addToNode(demandInletNode));
  EXPECT_FALSE(demandHumidifier.airLoopHVAC());
}

TEST_F(EPModelFixture, HumidifierSteamGas_AddToNodeSupportsOutboardOANode) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACOutdoorAirSystem oaSystem(model);
  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(oaSystem.addToNode(supplyInletNode));

  auto outboardOANode = oaSystem.outboardOANode();
  ASSERT_TRUE(outboardOANode);

  HumidifierSteamGas humidifier(model);
  EXPECT_TRUE(humidifier.addToNode(*outboardOANode));
  EXPECT_EQ(3u, oaSystem.oaComponents().size());
}
