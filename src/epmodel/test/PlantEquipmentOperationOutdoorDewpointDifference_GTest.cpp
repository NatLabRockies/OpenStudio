/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include <gtest/gtest.h>
#include <utilities/idd/PlantEquipmentOperation_OutdoorDewpointDifference_FieldEnums.hxx>
#include <utilities/idf/IdfExtensibleGroup.hpp>

#include "EPModelFixture.hpp"
#include "../PlantEquipmentOperationRangeBasedScheme/PlantEquipmentOperationOutdoorDewpointDifference.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, PlantEquipmentOperationOutdoorDewpointDifference_DefaultConstructor) {
  Model model;
  PlantEquipmentOperationOutdoorDewpointDifference dewpointDifference(model);
  EXPECT_EQ(PlantEquipmentOperationOutdoorDewpointDifference::iddObjectType(), dewpointDifference.iddObject().type());
  EXPECT_FALSE(dewpointDifference.nameString().empty());
}

TEST_F(EPModelFixture, PlantEquipmentOperationOutdoorDewpointDifference_ScalarAccessors_RoundTrip) {
  Model model;
  PlantEquipmentOperationOutdoorDewpointDifference dewpointDifference(model);

  EXPECT_DOUBLE_EQ(100.0, dewpointDifference.maximumUpperLimit());
  EXPECT_DOUBLE_EQ(-50.0, dewpointDifference.minimumLowerLimit());

  const auto lowerField = openstudio::PlantEquipmentOperation_OutdoorDewpointDifferenceExtensibleFields::DewpointTemperatureDifferenceRangeLowerLimit;
  const auto upperField = openstudio::PlantEquipmentOperation_OutdoorDewpointDifferenceExtensibleFields::DewpointTemperatureDifferenceRangeUpperLimit;

  auto firstGroup = dewpointDifference.pushExtensibleGroup();
  ASSERT_FALSE(firstGroup.empty());
  ASSERT_TRUE(firstGroup.setDouble(lowerField, -20.0));
  ASSERT_TRUE(firstGroup.setDouble(upperField, 10.0));
  EXPECT_DOUBLE_EQ(10.0, dewpointDifference.maximumUpperLimit());
  EXPECT_DOUBLE_EQ(-20.0, dewpointDifference.minimumLowerLimit());

  auto secondGroup = dewpointDifference.pushExtensibleGroup();
  ASSERT_FALSE(secondGroup.empty());
  ASSERT_TRUE(secondGroup.setDouble(lowerField, 5.0));
  ASSERT_TRUE(secondGroup.setDouble(upperField, 30.0));
  EXPECT_DOUBLE_EQ(30.0, dewpointDifference.maximumUpperLimit());
  EXPECT_DOUBLE_EQ(-20.0, dewpointDifference.minimumLowerLimit());
}
