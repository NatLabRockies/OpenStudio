/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>
#include <utilities/idd/PlantEquipmentOperation_HeatingLoad_FieldEnums.hxx>
#include <utilities/idf/IdfExtensibleGroup.hpp>

#include "EPModelFixture.hpp"
#include "../PlantEquipmentOperationScheme/PlantEquipmentOperationHeatingLoad.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, PlantEquipmentOperationHeatingLoad_DefaultConstructor) {
  Model model;
  PlantEquipmentOperationHeatingLoad heatingLoad(model);
  EXPECT_EQ(PlantEquipmentOperationHeatingLoad::iddObjectType(), heatingLoad.iddObject().type());
  EXPECT_FALSE(heatingLoad.nameString().empty());
}

TEST_F(EPModelFixture, PlantEquipmentOperationHeatingLoad_ScalarAccessors_RoundTrip) {
  Model model;
  PlantEquipmentOperationHeatingLoad heatingLoad(model);

  EXPECT_DOUBLE_EQ(1e9, heatingLoad.maximumUpperLimit());
  EXPECT_DOUBLE_EQ(0.0, heatingLoad.minimumLowerLimit());

  const auto lowerField = openstudio::PlantEquipmentOperation_HeatingLoadExtensibleFields::LoadRangeLowerLimit;
  const auto upperField = openstudio::PlantEquipmentOperation_HeatingLoadExtensibleFields::LoadRangeUpperLimit;

  auto firstGroup = heatingLoad.pushExtensibleGroup();
  ASSERT_FALSE(firstGroup.empty());
  ASSERT_TRUE(firstGroup.setDouble(lowerField, 5.0));
  ASSERT_TRUE(firstGroup.setDouble(upperField, 123.4));
  EXPECT_DOUBLE_EQ(123.4, heatingLoad.maximumUpperLimit());
  EXPECT_DOUBLE_EQ(5.0, heatingLoad.minimumLowerLimit());

  auto secondGroup = heatingLoad.pushExtensibleGroup();
  ASSERT_FALSE(secondGroup.empty());
  ASSERT_TRUE(secondGroup.setDouble(lowerField, 50.0));
  ASSERT_TRUE(secondGroup.setDouble(upperField, 500.0));
  EXPECT_DOUBLE_EQ(500.0, heatingLoad.maximumUpperLimit());
  EXPECT_DOUBLE_EQ(5.0, heatingLoad.minimumLowerLimit());
}
