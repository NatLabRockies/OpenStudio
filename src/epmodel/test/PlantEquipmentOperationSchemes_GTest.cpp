/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/PlantEquipmentOperationSchemes.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, PlantEquipmentOperationSchemes_DefaultConstructor) {
  Model model;
  PlantEquipmentOperationSchemes schemes(model);

  EXPECT_EQ(PlantEquipmentOperationSchemes::iddObjectType(), schemes.iddObject().type());
  EXPECT_FALSE(schemes.controlScheme2ObjectType());

  auto values = PlantEquipmentOperationSchemes::controlSchemeObjectTypeValues();
}

TEST_F(EPModelFixture, PlantEquipmentOperationSchemes_ScalarAccessors_RoundTrip) {
  Model model;
  PlantEquipmentOperationSchemes schemes(model);

  auto values = PlantEquipmentOperationSchemes::controlSchemeObjectTypeValues();
  std::string firstValue = values.empty() ? "PlantEquipmentOperation:HeatingLoad" : values[0];
  std::string secondValue;
  if (values.size() > 1) {
    secondValue = values[1];
  } else if (!values.empty()) {
    secondValue = values[0];
  } else {
    secondValue = "PlantEquipmentOperation:CoolingLoad";
  }

  EXPECT_TRUE(schemes.setControlScheme1ObjectType(firstValue));
  EXPECT_EQ(firstValue, schemes.controlScheme1ObjectType());

  EXPECT_TRUE(schemes.setControlScheme2ObjectType(secondValue));
  auto schemeTwo = schemes.controlScheme2ObjectType();
  ASSERT_TRUE(schemeTwo);
  EXPECT_EQ(secondValue, *schemeTwo);

  schemes.resetControlScheme2ObjectType();
  auto resetValue = schemes.controlScheme2ObjectType();
  ASSERT_TRUE(resetValue);
  EXPECT_TRUE(resetValue->empty());
}
