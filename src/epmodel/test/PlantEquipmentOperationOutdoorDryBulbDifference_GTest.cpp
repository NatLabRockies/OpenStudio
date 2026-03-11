/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include <gtest/gtest.h>
#include <utilities/idd/PlantEquipmentOperation_OutdoorDryBulbDifference_FieldEnums.hxx>
#include <utilities/idf/IdfExtensibleGroup.hpp>

#include "EPModelFixture.hpp"
#include "PlantEquipmentOperationRangeBasedScheme/PlantEquipmentOperationOutdoorDryBulbDifference.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, PlantEquipmentOperationOutdoorDryBulbDifference_DefaultConstructor) {
  Model model;
  PlantEquipmentOperationOutdoorDryBulbDifference difference(model);
  EXPECT_EQ(PlantEquipmentOperationOutdoorDryBulbDifference::iddObjectType(), difference.iddObject().type());
  EXPECT_FALSE(difference.nameString().empty());
}

TEST_F(EPModelFixture, PlantEquipmentOperationOutdoorDryBulbDifference_ScalarAccessors_RoundTrip) {
  Model model;
  PlantEquipmentOperationOutdoorDryBulbDifference difference(model);

  EXPECT_DOUBLE_EQ(100.0, difference.maximumUpperLimit());
  EXPECT_DOUBLE_EQ(-50.0, difference.minimumLowerLimit());

  const auto lowerField = openstudio::PlantEquipmentOperation_OutdoorDryBulbDifferenceExtensibleFields::DryBulbTemperatureDifferenceRangeLowerLimit;
  const auto upperField = openstudio::PlantEquipmentOperation_OutdoorDryBulbDifferenceExtensibleFields::DryBulbTemperatureDifferenceRangeUpperLimit;

  auto firstGroup = difference.pushExtensibleGroup();
  ASSERT_FALSE(firstGroup.empty());
  ASSERT_TRUE(firstGroup.setDouble(lowerField, -14.2));
  ASSERT_TRUE(firstGroup.setDouble(upperField, 5.3));
  EXPECT_DOUBLE_EQ(5.3, difference.maximumUpperLimit());
  EXPECT_DOUBLE_EQ(-14.2, difference.minimumLowerLimit());

  auto secondGroup = difference.pushExtensibleGroup();
  ASSERT_FALSE(secondGroup.empty());
  ASSERT_TRUE(secondGroup.setDouble(lowerField, 5.4));
  ASSERT_TRUE(secondGroup.setDouble(upperField, 29.7));
  EXPECT_DOUBLE_EQ(29.7, difference.maximumUpperLimit());
  EXPECT_DOUBLE_EQ(-14.2, difference.minimumLowerLimit());
}
