/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include <gtest/gtest.h>
#include <utilities/idd/PlantEquipmentOperation_OutdoorRelativeHumidity_FieldEnums.hxx>
#include <utilities/idf/IdfExtensibleGroup.hpp>

#include "EPModelFixture.hpp"
#include "PlantEquipmentOperationRangeBasedScheme/PlantEquipmentOperationOutdoorRelativeHumidity.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, PlantEquipmentOperationOutdoorRelativeHumidity_DefaultConstructor) {
  Model model;
  PlantEquipmentOperationOutdoorRelativeHumidity humidity(model);
  EXPECT_EQ(PlantEquipmentOperationOutdoorRelativeHumidity::iddObjectType(), humidity.iddObject().type());
  EXPECT_FALSE(humidity.nameString().empty());
}

TEST_F(EPModelFixture, PlantEquipmentOperationOutdoorRelativeHumidity_ScalarAccessors_RoundTrip) {
  Model model;
  PlantEquipmentOperationOutdoorRelativeHumidity humidity(model);

  EXPECT_DOUBLE_EQ(100.0, humidity.maximumUpperLimit());
  EXPECT_DOUBLE_EQ(0.0, humidity.minimumLowerLimit());

  const auto lowerField = openstudio::PlantEquipmentOperation_OutdoorRelativeHumidityExtensibleFields::RelativeHumidityRangeLowerLimit;
  const auto upperField = openstudio::PlantEquipmentOperation_OutdoorRelativeHumidityExtensibleFields::RelativeHumidityRangeUpperLimit;

  auto firstGroup = humidity.pushExtensibleGroup();
  ASSERT_FALSE(firstGroup.empty());
  ASSERT_TRUE(firstGroup.setDouble(lowerField, 23.2));
  ASSERT_TRUE(firstGroup.setDouble(upperField, 50.4));
  EXPECT_DOUBLE_EQ(50.4, humidity.maximumUpperLimit());
  EXPECT_DOUBLE_EQ(23.2, humidity.minimumLowerLimit());

  auto secondGroup = humidity.pushExtensibleGroup();
  ASSERT_FALSE(secondGroup.empty());
  ASSERT_TRUE(secondGroup.setDouble(lowerField, 50.4));
  ASSERT_TRUE(secondGroup.setDouble(upperField, 99.9));
  EXPECT_DOUBLE_EQ(99.9, humidity.maximumUpperLimit());
  EXPECT_DOUBLE_EQ(23.2, humidity.minimumLowerLimit());
}
