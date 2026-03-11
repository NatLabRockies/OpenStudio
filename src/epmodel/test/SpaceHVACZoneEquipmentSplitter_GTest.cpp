/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/SpaceHVACZoneEquipmentSplitter.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, SpaceHVACZoneEquipmentSplitter_DefaultConstructor) {
  Model model;
  SpaceHVACZoneEquipmentSplitter object(model);
  EXPECT_EQ(SpaceHVACZoneEquipmentSplitter::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, SpaceHVACZoneEquipmentSplitter_ScalarAccessors_RoundTrip) {
  Model model;
  SpaceHVACZoneEquipmentSplitter object(model);

  EXPECT_TRUE(object.setZoneEquipmentObjectType("AirLoopHVAC:UnitarySystem"));
  EXPECT_EQ("AirLoopHVAC:UnitarySystem", object.zoneEquipmentObjectType());

  EXPECT_TRUE(object.isThermostatControlMethodDefaulted());
  EXPECT_EQ("SingleSpace", object.thermostatControlMethod());
  EXPECT_TRUE(object.setThermostatControlMethod("Maximum"));
  EXPECT_EQ("Maximum", object.thermostatControlMethod());
  EXPECT_FALSE(object.isThermostatControlMethodDefaulted());
  object.resetThermostatControlMethod();
  EXPECT_TRUE(object.isThermostatControlMethodDefaulted());
  EXPECT_EQ("SingleSpace", object.thermostatControlMethod());

  EXPECT_TRUE(object.isSpaceFractionMethodDefaulted());
  EXPECT_EQ("DesignCoolingLoad", object.spaceFractionMethod());
  EXPECT_TRUE(object.setSpaceFractionMethod("Volume"));
  EXPECT_EQ("Volume", object.spaceFractionMethod());
  EXPECT_FALSE(object.isSpaceFractionMethodDefaulted());
  object.resetSpaceFractionMethod();
  EXPECT_TRUE(object.isSpaceFractionMethodDefaulted());
  EXPECT_EQ("DesignCoolingLoad", object.spaceFractionMethod());

  const auto zoneEquipmentObjectTypes = SpaceHVACZoneEquipmentSplitter::zoneEquipmentObjectTypeValues();
  EXPECT_FALSE(zoneEquipmentObjectTypes.empty());

  const auto thermostatControlMethods = SpaceHVACZoneEquipmentSplitter::thermostatControlMethodValues();
  EXPECT_EQ(3u, thermostatControlMethods.size());
  EXPECT_EQ("SingleSpace", thermostatControlMethods[0]);
  EXPECT_EQ("Maximum", thermostatControlMethods[1]);
  EXPECT_EQ("Ideal", thermostatControlMethods[2]);

  const auto spaceFractionMethods = SpaceHVACZoneEquipmentSplitter::spaceFractionMethodValues();
  EXPECT_EQ(5u, spaceFractionMethods.size());
  EXPECT_EQ("DesignCoolingLoad", spaceFractionMethods[0]);
  EXPECT_EQ("DesignHeatingLoad", spaceFractionMethods[1]);
  EXPECT_EQ("FloorArea", spaceFractionMethods[2]);
  EXPECT_EQ("Volume", spaceFractionMethods[3]);
  EXPECT_EQ("PerimeterLength", spaceFractionMethods[4]);
}
