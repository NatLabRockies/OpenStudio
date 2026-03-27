/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../StraightComponent/CoilHeatingElectric.hpp"
#include "../StraightComponent/FanConstantVolume.hpp"
#include "../StraightComponent/Node.hpp"
#include "../ZoneHVACComponent/ZoneHVACUnitHeater.hpp"

#include <utilities/idd/ZoneHVAC_UnitHeater_FieldEnums.hxx>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ZoneHVACUnitHeater_DefaultConstructor) {
  Model model;
  ZoneHVACUnitHeater unitHeater(model);

  EXPECT_EQ(ZoneHVACUnitHeater::iddObjectType(), unitHeater.iddObject().type());
  EXPECT_TRUE(unitHeater.isMaximumSupplyAirFlowRateAutosized());
  EXPECT_EQ("No", unitHeater.fanControlType());
  EXPECT_TRUE(unitHeater.isMaximumHotWaterFlowRateAutosized());
  EXPECT_DOUBLE_EQ(0.0, unitHeater.minimumHotWaterFlowRate());
  EXPECT_FALSE(unitHeater.isMinimumHotWaterFlowRateDefaulted());
  EXPECT_DOUBLE_EQ(0.001, unitHeater.heatingConvergenceTolerance());
  EXPECT_FALSE(unitHeater.isHeatingConvergenceToleranceDefaulted());
}

TEST_F(EPModelFixture, ZoneHVACUnitHeater_ScalarAccessors_RoundTrip) {
  Model model;
  ZoneHVACUnitHeater unitHeater(model);

  EXPECT_TRUE(unitHeater.setMaximumSupplyAirFlowRate(0.42));
  EXPECT_FALSE(unitHeater.isMaximumSupplyAirFlowRateAutosized());
  EXPECT_TRUE(unitHeater.setFanControlType("Yes"));
  EXPECT_TRUE(unitHeater.setMaximumHotWaterFlowRate(0.05));
  EXPECT_TRUE(unitHeater.setMinimumHotWaterFlowRate(0.02));
  EXPECT_TRUE(unitHeater.setHeatingConvergenceTolerance(0.01));

  ASSERT_TRUE(unitHeater.maximumSupplyAirFlowRate());
  EXPECT_DOUBLE_EQ(0.42, unitHeater.maximumSupplyAirFlowRate().value());
  EXPECT_EQ("Yes", unitHeater.fanControlType());
  ASSERT_TRUE(unitHeater.maximumHotWaterFlowRate());
  EXPECT_DOUBLE_EQ(0.05, unitHeater.maximumHotWaterFlowRate().value());
  EXPECT_DOUBLE_EQ(0.02, unitHeater.minimumHotWaterFlowRate());
  EXPECT_FALSE(unitHeater.isMinimumHotWaterFlowRateDefaulted());
  EXPECT_DOUBLE_EQ(0.01, unitHeater.heatingConvergenceTolerance());
  EXPECT_FALSE(unitHeater.isHeatingConvergenceToleranceDefaulted());

  unitHeater.autosizeMaximumSupplyAirFlowRate();
  EXPECT_TRUE(unitHeater.isMaximumSupplyAirFlowRateAutosized());
  EXPECT_FALSE(unitHeater.maximumSupplyAirFlowRate());

  unitHeater.resetMaximumHotWaterFlowRate();
  EXPECT_FALSE(unitHeater.maximumHotWaterFlowRate());
  unitHeater.autosizeMaximumHotWaterFlowRate();
  EXPECT_TRUE(unitHeater.isMaximumHotWaterFlowRateAutosized());

  unitHeater.resetMinimumHotWaterFlowRate();
  EXPECT_TRUE(unitHeater.isMinimumHotWaterFlowRateDefaulted());

  unitHeater.resetHeatingConvergenceTolerance();
  EXPECT_TRUE(unitHeater.isHeatingConvergenceToleranceDefaulted());
}

TEST_F(EPModelFixture, ZoneHVACUnitHeater_TopologyAndChildren) {
  Model model;
  ThermalZone zone(model);
  ZoneHVACUnitHeater unitHeater(model);

  EXPECT_EQ(openstudio::ZoneHVAC_UnitHeaterFields::AirInletNodeName, unitHeater.inletPort());
  EXPECT_EQ(openstudio::ZoneHVAC_UnitHeaterFields::AirOutletNodeName, unitHeater.outletPort());

  EXPECT_TRUE(unitHeater.addToThermalZone(zone));
  EXPECT_TRUE(unitHeater.inletNode());
  EXPECT_TRUE(unitHeater.outletNode());

  unitHeater.removeFromThermalZone();
  EXPECT_FALSE(unitHeater.inletNode());
  EXPECT_FALSE(unitHeater.outletNode());

  FanConstantVolume fan(model);
  CoilHeatingElectric coil(model);

  EXPECT_TRUE(unitHeater.setPointer(openstudio::ZoneHVAC_UnitHeaterFields::SupplyAirFanName, fan.handle()));
  EXPECT_TRUE(unitHeater.setPointer(openstudio::ZoneHVAC_UnitHeaterFields::HeatingCoilName, coil.handle()));

  const auto children = unitHeater.children();
  ASSERT_EQ(2u, children.size());
  EXPECT_EQ(fan.handle(), children[0].handle());
  EXPECT_EQ(coil.handle(), children[1].handle());
}
