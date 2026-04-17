/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../StraightComponent/CoilCoolingDXVariableSpeed.hpp"
#include "../StraightComponent/CoilHeatingDXVariableSpeed.hpp"
#include "../StraightComponent/CoilSystemIntegratedHeatPumpAirSource.hpp"
#include "../StraightComponent/Node.hpp"
#include "../StraightComponent/StraightComponent.hpp"
#include "../WaterToAirComponent/CoilWaterHeatingAirToWaterHeatPumpVariableSpeed.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoilSystemIntegratedHeatPumpAirSource_DefaultConstructor) {
  Model model;
  CoilSystemIntegratedHeatPumpAirSource coilSystem(model);
  EXPECT_EQ(CoilSystemIntegratedHeatPumpAirSource::iddObjectType(), coilSystem.iddObject().type());
  EXPECT_FALSE(coilSystem.nameString().empty());

  EXPECT_DOUBLE_EQ(20.0, coilSystem.indoorTemperatureLimitForSCWHMode());
  EXPECT_DOUBLE_EQ(27.0, coilSystem.ambientTemperatureLimitForSCWHMode());
  EXPECT_DOUBLE_EQ(20.0, coilSystem.indoorTemperatureAboveWhichWHHasHigherPriority());
  EXPECT_DOUBLE_EQ(20.0, coilSystem.ambientTemperatureAboveWhichWHHasHigherPriority());
  EXPECT_EQ(0, coilSystem.flagtoIndicateLoadControlInSCWHMode());
  EXPECT_EQ(1, coilSystem.minimumSpeedLevelForSCWHMode());
  EXPECT_DOUBLE_EQ(0.0, coilSystem.maximumWaterFlowVolumeBeforeSwitchingfromSCDWHtoSCWHMode());
  EXPECT_EQ(1, coilSystem.minimumSpeedLevelForSCDWHMode());
  EXPECT_DOUBLE_EQ(360.0, coilSystem.maximumRunningTimeBeforeAllowingElectricResistanceHeatUseDuringSHDWHMode());
  EXPECT_EQ(1, coilSystem.minimumSpeedLevelForSHDWHMode());

  const auto children = coilSystem.children();
  ASSERT_EQ(8u, children.size());

  EXPECT_EQ(coilSystem.spaceCoolingCoil().handle(), children[0].handle());
  EXPECT_EQ(coilSystem.spaceHeatingCoil().handle(), children[1].handle());
  EXPECT_EQ(coilSystem.dedicatedWaterHeatingCoil().handle(), children[2].handle());
  EXPECT_EQ(coilSystem.scwhCoil().handle(), children[3].handle());
  EXPECT_EQ(coilSystem.scdwhCoolingCoil().handle(), children[4].handle());
  EXPECT_EQ(coilSystem.scdwhWaterHeatingCoil().handle(), children[5].handle());
  EXPECT_EQ(coilSystem.shdwhHeatingCoil().handle(), children[6].handle());
  EXPECT_EQ(coilSystem.shdwhWaterHeatingCoil().handle(), children[7].handle());

}

TEST_F(EPModelFixture, CoilSystemIntegratedHeatPumpAirSource_ScalarAccessors_RoundTrip) {
  Model model;
  CoilSystemIntegratedHeatPumpAirSource coilSystem(model);

  EXPECT_TRUE(coilSystem.setIndoorTemperatureLimitForSCWHMode(21.5));
  EXPECT_DOUBLE_EQ(21.5, coilSystem.indoorTemperatureLimitForSCWHMode());

  EXPECT_TRUE(coilSystem.setAmbientTemperatureLimitForSCWHMode(28.5));
  EXPECT_DOUBLE_EQ(28.5, coilSystem.ambientTemperatureLimitForSCWHMode());

  EXPECT_TRUE(coilSystem.setIndoorTemperatureAboveWhichWHHasHigherPriority(19.5));
  EXPECT_DOUBLE_EQ(19.5, coilSystem.indoorTemperatureAboveWhichWHHasHigherPriority());

  EXPECT_TRUE(coilSystem.setAmbientTemperatureAboveWhichWHHasHigherPriority(18.5));
  EXPECT_DOUBLE_EQ(18.5, coilSystem.ambientTemperatureAboveWhichWHHasHigherPriority());

  EXPECT_TRUE(coilSystem.setFlagtoIndicateLoadControlInSCWHMode(1));
  EXPECT_EQ(1, coilSystem.flagtoIndicateLoadControlInSCWHMode());

  EXPECT_TRUE(coilSystem.setMinimumSpeedLevelForSCWHMode(2));
  EXPECT_EQ(2, coilSystem.minimumSpeedLevelForSCWHMode());

  EXPECT_TRUE(coilSystem.setMaximumWaterFlowVolumeBeforeSwitchingfromSCDWHtoSCWHMode(0.25));
  EXPECT_DOUBLE_EQ(0.25, coilSystem.maximumWaterFlowVolumeBeforeSwitchingfromSCDWHtoSCWHMode());

  EXPECT_TRUE(coilSystem.setMinimumSpeedLevelForSCDWHMode(3));
  EXPECT_EQ(3, coilSystem.minimumSpeedLevelForSCDWHMode());

  EXPECT_TRUE(coilSystem.setMaximumRunningTimeBeforeAllowingElectricResistanceHeatUseDuringSHDWHMode(420.0));
  EXPECT_DOUBLE_EQ(420.0, coilSystem.maximumRunningTimeBeforeAllowingElectricResistanceHeatUseDuringSHDWHMode());

  EXPECT_TRUE(coilSystem.setMinimumSpeedLevelForSHDWHMode(4));
  EXPECT_EQ(4, coilSystem.minimumSpeedLevelForSHDWHMode());
}

TEST_F(EPModelFixture, CoilSystemIntegratedHeatPumpAirSource_RelationshipSetters_RoundTrip) {
  Model model;
  CoilSystemIntegratedHeatPumpAirSource coilSystem(model);

  CoilCoolingDXVariableSpeed spaceCoolingCoil(model);
  ASSERT_TRUE(spaceCoolingCoil.setName("Test Space Cooling Coil"));
  CoilHeatingDXVariableSpeed spaceHeatingCoil(model);
  ASSERT_TRUE(spaceHeatingCoil.setName("Test Space Heating Coil"));
  CoilWaterHeatingAirToWaterHeatPumpVariableSpeed dedicatedWaterHeatingCoil(model);
  ASSERT_TRUE(dedicatedWaterHeatingCoil.setName("Test Dedicated Water Heating Coil"));
  CoilWaterHeatingAirToWaterHeatPumpVariableSpeed scwhCoil(model);
  ASSERT_TRUE(scwhCoil.setName("Test SCWH Coil"));
  CoilCoolingDXVariableSpeed scdwhCoolingCoil(model);
  ASSERT_TRUE(scdwhCoolingCoil.setName("Test SCDWH Cooling Coil"));
  CoilWaterHeatingAirToWaterHeatPumpVariableSpeed scdwhWaterHeatingCoil(model);
  ASSERT_TRUE(scdwhWaterHeatingCoil.setName("Test SCDWH Water Heating Coil"));
  CoilHeatingDXVariableSpeed shdwhHeatingCoil(model);
  ASSERT_TRUE(shdwhHeatingCoil.setName("Test SHDWH Heating Coil"));
  CoilWaterHeatingAirToWaterHeatPumpVariableSpeed shdwhWaterHeatingCoil(model);
  ASSERT_TRUE(shdwhWaterHeatingCoil.setName("Test SHDWH Water Heating Coil"));

  EXPECT_TRUE(coilSystem.setSpaceCoolingCoil(spaceCoolingCoil));
  EXPECT_TRUE(coilSystem.setSpaceHeatingCoil(spaceHeatingCoil));
  EXPECT_TRUE(coilSystem.setDedicatedWaterHeatingCoil(dedicatedWaterHeatingCoil));
  EXPECT_TRUE(coilSystem.setSCWHCoil(scwhCoil));
  EXPECT_TRUE(coilSystem.setSCDWHCoolingCoil(scdwhCoolingCoil));
  EXPECT_TRUE(coilSystem.setSCDWHWaterHeatingCoil(scdwhWaterHeatingCoil));
  EXPECT_TRUE(coilSystem.setSHDWHHeatingCoil(shdwhHeatingCoil));
  EXPECT_TRUE(coilSystem.setSHDWHWaterHeatingCoil(shdwhWaterHeatingCoil));

  EXPECT_EQ(spaceCoolingCoil.handle(), coilSystem.spaceCoolingCoil().handle());
  EXPECT_EQ(spaceHeatingCoil.handle(), coilSystem.spaceHeatingCoil().handle());
  EXPECT_EQ(dedicatedWaterHeatingCoil.handle(), coilSystem.dedicatedWaterHeatingCoil().handle());
  EXPECT_EQ(scwhCoil.handle(), coilSystem.scwhCoil().handle());
  EXPECT_EQ(scdwhCoolingCoil.handle(), coilSystem.scdwhCoolingCoil().handle());
  EXPECT_EQ(scdwhWaterHeatingCoil.handle(), coilSystem.scdwhWaterHeatingCoil().handle());
  EXPECT_EQ(shdwhHeatingCoil.handle(), coilSystem.shdwhHeatingCoil().handle());
  EXPECT_EQ(shdwhWaterHeatingCoil.handle(), coilSystem.shdwhWaterHeatingCoil().handle());

  const auto children = coilSystem.children();
  ASSERT_EQ(8u, children.size());
  EXPECT_EQ(spaceCoolingCoil.handle(), children[0].handle());
  EXPECT_EQ(spaceHeatingCoil.handle(), children[1].handle());
  EXPECT_EQ(dedicatedWaterHeatingCoil.handle(), children[2].handle());
  EXPECT_EQ(scwhCoil.handle(), children[3].handle());
  EXPECT_EQ(scdwhCoolingCoil.handle(), children[4].handle());
  EXPECT_EQ(scdwhWaterHeatingCoil.handle(), children[5].handle());
  EXPECT_EQ(shdwhHeatingCoil.handle(), children[6].handle());
  EXPECT_EQ(shdwhWaterHeatingCoil.handle(), children[7].handle());
}

TEST_F(EPModelFixture, CoilSystemIntegratedHeatPumpAirSource_RelationshipConstructor) {
  Model model;
  CoilCoolingDXVariableSpeed spaceCoolingCoil(model);
  CoilHeatingDXVariableSpeed spaceHeatingCoil(model);
  CoilWaterHeatingAirToWaterHeatPumpVariableSpeed dedicatedWaterHeatingCoil(model);
  CoilWaterHeatingAirToWaterHeatPumpVariableSpeed scwhCoil(model);
  CoilCoolingDXVariableSpeed scdwhCoolingCoil(model);
  CoilWaterHeatingAirToWaterHeatPumpVariableSpeed scdwhWaterHeatingCoil(model);
  CoilHeatingDXVariableSpeed shdwhHeatingCoil(model);
  CoilWaterHeatingAirToWaterHeatPumpVariableSpeed shdwhWaterHeatingCoil(model);

  CoilSystemIntegratedHeatPumpAirSource coilSystem(model, spaceCoolingCoil, spaceHeatingCoil, dedicatedWaterHeatingCoil, scwhCoil,
                                                    scdwhCoolingCoil, scdwhWaterHeatingCoil, shdwhHeatingCoil, shdwhWaterHeatingCoil);

  EXPECT_EQ(spaceCoolingCoil.handle(), coilSystem.spaceCoolingCoil().handle());
  EXPECT_EQ(spaceHeatingCoil.handle(), coilSystem.spaceHeatingCoil().handle());
  EXPECT_EQ(dedicatedWaterHeatingCoil.handle(), coilSystem.dedicatedWaterHeatingCoil().handle());
  EXPECT_EQ(scwhCoil.handle(), coilSystem.scwhCoil().handle());
  EXPECT_EQ(scdwhCoolingCoil.handle(), coilSystem.scdwhCoolingCoil().handle());
  EXPECT_EQ(scdwhWaterHeatingCoil.handle(), coilSystem.scdwhWaterHeatingCoil().handle());
  EXPECT_EQ(shdwhHeatingCoil.handle(), coilSystem.shdwhHeatingCoil().handle());
  EXPECT_EQ(shdwhWaterHeatingCoil.handle(), coilSystem.shdwhWaterHeatingCoil().handle());
  EXPECT_DOUBLE_EQ(20.0, coilSystem.indoorTemperatureAboveWhichWHHasHigherPriority());
  EXPECT_DOUBLE_EQ(20.0, coilSystem.ambientTemperatureAboveWhichWHHasHigherPriority());
}

TEST_F(EPModelFixture, CoilSystemIntegratedHeatPumpAirSource_StraightComponentPortsWithoutLoopPlacement) {
  Model model;
  CoilSystemIntegratedHeatPumpAirSource coilSystem(model);
  Node node(model);

  EXPECT_TRUE(coilSystem.optionalCast<StraightComponent>());
  EXPECT_EQ(0u, coilSystem.inletPort());
  EXPECT_EQ(0u, coilSystem.outletPort());
  EXPECT_FALSE(coilSystem.addToNode(node));
}
