/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include <gtest/gtest.h>
#include <utilities/idd/PlantEquipmentOperation_OutdoorDewpoint_FieldEnums.hxx>
#include <utilities/idf/IdfExtensibleGroup.hpp>

#include "EPModelFixture.hpp"
#include "PlantEquipmentOperationRangeBasedScheme/PlantEquipmentOperationOutdoorDewpoint.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, PlantEquipmentOperationOutdoorDewpoint_DefaultConstructor) {
  Model model;
  PlantEquipmentOperationOutdoorDewpoint dewpoint(model);
  EXPECT_EQ(PlantEquipmentOperationOutdoorDewpoint::iddObjectType(), dewpoint.iddObject().type());
  EXPECT_FALSE(dewpoint.nameString().empty());
}

TEST_F(EPModelFixture, PlantEquipmentOperationOutdoorDewpoint_ScalarAccessors_RoundTrip) {
  Model model;
  PlantEquipmentOperationOutdoorDewpoint dewpoint(model);

  EXPECT_DOUBLE_EQ(70.0, dewpoint.maximumUpperLimit());
  EXPECT_DOUBLE_EQ(-70.0, dewpoint.minimumLowerLimit());

  const auto lowerField = openstudio::PlantEquipmentOperation_OutdoorDewpointExtensibleFields::DewpointTemperatureRangeLowerLimit;
  const auto upperField = openstudio::PlantEquipmentOperation_OutdoorDewpointExtensibleFields::DewpointTemperatureRangeUpperLimit;

  auto firstGroup = dewpoint.pushExtensibleGroup();
  ASSERT_FALSE(firstGroup.empty());
  ASSERT_TRUE(firstGroup.setDouble(lowerField, -12.3));
  ASSERT_TRUE(firstGroup.setDouble(upperField, 5.6));
  EXPECT_DOUBLE_EQ(5.6, dewpoint.maximumUpperLimit());
  EXPECT_DOUBLE_EQ(-12.3, dewpoint.minimumLowerLimit());

  auto secondGroup = dewpoint.pushExtensibleGroup();
  ASSERT_FALSE(secondGroup.empty());
  ASSERT_TRUE(secondGroup.setDouble(lowerField, 0.0));
  ASSERT_TRUE(secondGroup.setDouble(upperField, 18.0));
  EXPECT_DOUBLE_EQ(18.0, dewpoint.maximumUpperLimit());
  EXPECT_DOUBLE_EQ(-12.3, dewpoint.minimumLowerLimit());
}
