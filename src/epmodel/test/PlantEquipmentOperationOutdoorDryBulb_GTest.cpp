/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include <gtest/gtest.h>
#include <utilities/idd/PlantEquipmentOperation_OutdoorDryBulb_FieldEnums.hxx>
#include <utilities/idf/IdfExtensibleGroup.hpp>

#include "EPModelFixture.hpp"
#include "PlantEquipmentOperationRangeBasedScheme/PlantEquipmentOperationOutdoorDryBulb.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, PlantEquipmentOperationOutdoorDryBulb_DefaultConstructor) {
  Model model;
  PlantEquipmentOperationOutdoorDryBulb dryBulb(model);
  EXPECT_EQ(PlantEquipmentOperationOutdoorDryBulb::iddObjectType(), dryBulb.iddObject().type());
  EXPECT_FALSE(dryBulb.nameString().empty());
}

TEST_F(EPModelFixture, PlantEquipmentOperationOutdoorDryBulb_ScalarAccessors_RoundTrip) {
  Model model;
  PlantEquipmentOperationOutdoorDryBulb dryBulb(model);

  EXPECT_DOUBLE_EQ(70.0, dryBulb.maximumUpperLimit());
  EXPECT_DOUBLE_EQ(-70.0, dryBulb.minimumLowerLimit());

  const auto lowerField = openstudio::PlantEquipmentOperation_OutdoorDryBulbExtensibleFields::DryBulbTemperatureRangeLowerLimit;
  const auto upperField = openstudio::PlantEquipmentOperation_OutdoorDryBulbExtensibleFields::DryBulbTemperatureRangeUpperLimit;

  auto firstGroup = dryBulb.pushExtensibleGroup();
  ASSERT_FALSE(firstGroup.empty());
  ASSERT_TRUE(firstGroup.setDouble(lowerField, -12.5));
  ASSERT_TRUE(firstGroup.setDouble(upperField, 4.9));
  EXPECT_DOUBLE_EQ(4.9, dryBulb.maximumUpperLimit());
  EXPECT_DOUBLE_EQ(-12.5, dryBulb.minimumLowerLimit());

  auto secondGroup = dryBulb.pushExtensibleGroup();
  ASSERT_FALSE(secondGroup.empty());
  ASSERT_TRUE(secondGroup.setDouble(lowerField, 4.9));
  ASSERT_TRUE(secondGroup.setDouble(upperField, 23.0));
  EXPECT_DOUBLE_EQ(23.0, dryBulb.maximumUpperLimit());
  EXPECT_DOUBLE_EQ(-12.5, dryBulb.minimumLowerLimit());
}
