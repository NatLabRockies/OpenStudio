/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include <gtest/gtest.h>
#include <utilities/idd/PlantEquipmentOperation_OutdoorWetBulbDifference_FieldEnums.hxx>
#include <utilities/idf/IdfExtensibleGroup.hpp>

#include "EPModelFixture.hpp"
#include "PlantEquipmentOperationRangeBasedScheme/PlantEquipmentOperationOutdoorWetBulbDifference.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, PlantEquipmentOperationOutdoorWetBulbDifference_DefaultConstructor) {
  Model model;
  PlantEquipmentOperationOutdoorWetBulbDifference difference(model);
  EXPECT_EQ(PlantEquipmentOperationOutdoorWetBulbDifference::iddObjectType(), difference.iddObject().type());
  EXPECT_FALSE(difference.nameString().empty());
}

TEST_F(EPModelFixture, PlantEquipmentOperationOutdoorWetBulbDifference_ScalarAccessors_RoundTrip) {
  Model model;
  PlantEquipmentOperationOutdoorWetBulbDifference difference(model);

  EXPECT_DOUBLE_EQ(100.0, difference.maximumUpperLimit());
  EXPECT_DOUBLE_EQ(-50.0, difference.minimumLowerLimit());

  const auto lowerField = openstudio::PlantEquipmentOperation_OutdoorWetBulbDifferenceExtensibleFields::WetBulbTemperatureDifferenceRangeLowerLimit;
  const auto upperField = openstudio::PlantEquipmentOperation_OutdoorWetBulbDifferenceExtensibleFields::WetBulbTemperatureDifferenceRangeUpperLimit;

  auto firstGroup = difference.pushExtensibleGroup();
  ASSERT_FALSE(firstGroup.empty());
  ASSERT_TRUE(firstGroup.setDouble(lowerField, -12.3));
  ASSERT_TRUE(firstGroup.setDouble(upperField, 6.4));
  EXPECT_DOUBLE_EQ(6.4, difference.maximumUpperLimit());
  EXPECT_DOUBLE_EQ(-12.3, difference.minimumLowerLimit());

  auto secondGroup = difference.pushExtensibleGroup();
  ASSERT_FALSE(secondGroup.empty());
  ASSERT_TRUE(secondGroup.setDouble(lowerField, 6.5));
  ASSERT_TRUE(secondGroup.setDouble(upperField, 18.9));
  EXPECT_DOUBLE_EQ(18.9, difference.maximumUpperLimit());
  EXPECT_DOUBLE_EQ(-12.3, difference.minimumLowerLimit());
}
