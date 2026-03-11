/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include <gtest/gtest.h>
#include <utilities/idd/PlantEquipmentOperation_OutdoorWetBulb_FieldEnums.hxx>
#include <utilities/idf/IdfExtensibleGroup.hpp>

#include "EPModelFixture.hpp"
#include "PlantEquipmentOperationRangeBasedScheme/PlantEquipmentOperationOutdoorWetBulb.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, PlantEquipmentOperationOutdoorWetBulb_DefaultConstructor) {
  Model model;
  PlantEquipmentOperationOutdoorWetBulb wetBulb(model);
  EXPECT_EQ(PlantEquipmentOperationOutdoorWetBulb::iddObjectType(), wetBulb.iddObject().type());
  EXPECT_FALSE(wetBulb.nameString().empty());
}

TEST_F(EPModelFixture, PlantEquipmentOperationOutdoorWetBulb_ScalarAccessors_RoundTrip) {
  Model model;
  PlantEquipmentOperationOutdoorWetBulb wetBulb(model);

  EXPECT_DOUBLE_EQ(70.0, wetBulb.maximumUpperLimit());
  EXPECT_DOUBLE_EQ(-70.0, wetBulb.minimumLowerLimit());

  const auto lowerField = openstudio::PlantEquipmentOperation_OutdoorWetBulbExtensibleFields::WetBulbTemperatureRangeLowerLimit;
  const auto upperField = openstudio::PlantEquipmentOperation_OutdoorWetBulbExtensibleFields::WetBulbTemperatureRangeUpperLimit;

  auto firstGroup = wetBulb.pushExtensibleGroup();
  ASSERT_FALSE(firstGroup.empty());
  ASSERT_TRUE(firstGroup.setDouble(lowerField, -15.0));
  ASSERT_TRUE(firstGroup.setDouble(upperField, 2.5));
  EXPECT_DOUBLE_EQ(2.5, wetBulb.maximumUpperLimit());
  EXPECT_DOUBLE_EQ(-15.0, wetBulb.minimumLowerLimit());

  auto secondGroup = wetBulb.pushExtensibleGroup();
  ASSERT_FALSE(secondGroup.empty());
  ASSERT_TRUE(secondGroup.setDouble(lowerField, 2.5));
  ASSERT_TRUE(secondGroup.setDouble(upperField, 18.0));
  EXPECT_DOUBLE_EQ(18.0, wetBulb.maximumUpperLimit());
  EXPECT_DOUBLE_EQ(-15.0, wetBulb.minimumLowerLimit());
}
