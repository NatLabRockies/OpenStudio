/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>
#include <utilities/idd/PlantEquipmentOperation_CoolingLoad_FieldEnums.hxx>
#include <utilities/idf/IdfExtensibleGroup.hpp>

#include "EPModelFixture.hpp"
#include "../PlantEquipmentOperationScheme/PlantEquipmentOperationCoolingLoad.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, PlantEquipmentOperationCoolingLoad_DefaultConstructor) {
  Model model;
  PlantEquipmentOperationCoolingLoad coolingLoad(model);
  EXPECT_EQ(PlantEquipmentOperationCoolingLoad::iddObjectType(), coolingLoad.iddObject().type());
  EXPECT_FALSE(coolingLoad.nameString().empty());
}

TEST_F(EPModelFixture, PlantEquipmentOperationCoolingLoad_ScalarAccessors_RoundTrip) {
  Model model;
  PlantEquipmentOperationCoolingLoad coolingLoad(model);

  EXPECT_DOUBLE_EQ(1e9, coolingLoad.maximumUpperLimit());
  EXPECT_DOUBLE_EQ(0.0, coolingLoad.minimumLowerLimit());

  const auto lowerField = openstudio::PlantEquipmentOperation_CoolingLoadExtensibleFields::LoadRangeLowerLimit;
  const auto upperField = openstudio::PlantEquipmentOperation_CoolingLoadExtensibleFields::LoadRangeUpperLimit;

  auto firstGroup = coolingLoad.pushExtensibleGroup();
  ASSERT_FALSE(firstGroup.empty());
  ASSERT_TRUE(firstGroup.setDouble(lowerField, 5.0));
  ASSERT_TRUE(firstGroup.setDouble(upperField, 123.4));
  EXPECT_DOUBLE_EQ(123.4, coolingLoad.maximumUpperLimit());
  EXPECT_DOUBLE_EQ(5.0, coolingLoad.minimumLowerLimit());

  auto secondGroup = coolingLoad.pushExtensibleGroup();
  ASSERT_FALSE(secondGroup.empty());
  ASSERT_TRUE(secondGroup.setDouble(lowerField, 50.0));
  ASSERT_TRUE(secondGroup.setDouble(upperField, 500.0));
  EXPECT_DOUBLE_EQ(500.0, coolingLoad.maximumUpperLimit());
  EXPECT_DOUBLE_EQ(5.0, coolingLoad.minimumLowerLimit());
}
