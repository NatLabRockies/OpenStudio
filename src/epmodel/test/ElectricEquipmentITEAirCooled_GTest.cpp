/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../SpaceLoadInstance/ElectricEquipmentITEAirCooled.hpp"

#include <utilities/idd/ElectricEquipment_ITE_AirCooled_FieldEnums.hxx>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ElectricEquipmentITEAirCooled_DefaultConstructor) {
  Model model;
  ElectricEquipmentITEAirCooled object(model);
  EXPECT_EQ(ElectricEquipmentITEAirCooled::iddObjectType(), object.iddObject().type());
  EXPECT_FALSE(object.nameString().empty());
}

TEST_F(EPModelFixture, ElectricEquipmentITEAirCooled_ScalarAccessors_RoundTrip) {
  Model model;
  ElectricEquipmentITEAirCooled object(model);

  EXPECT_TRUE(object.setCPUEndUseSubcategory("CPU-Proc"));
  EXPECT_EQ("CPU-Proc", object.cPUEndUseSubcategory());
  object.resetCPUEndUseSubcategory();
  EXPECT_TRUE(object.isCPUEndUseSubcategoryDefaulted());
  EXPECT_EQ("ITE-CPU", object.cPUEndUseSubcategory());

  EXPECT_TRUE(object.setFanEndUseSubcategory("Fan-Proc"));
  EXPECT_EQ("Fan-Proc", object.fanEndUseSubcategory());
  object.resetFanEndUseSubcategory();
  EXPECT_TRUE(object.isFanEndUseSubcategoryDefaulted());
  EXPECT_EQ("ITE-Fans", object.fanEndUseSubcategory());

  EXPECT_TRUE(object.setElectricPowerSupplyEndUseSubcategory("UPS-Proc"));
  EXPECT_EQ("UPS-Proc", object.electricPowerSupplyEndUseSubcategory());
  object.resetElectricPowerSupplyEndUseSubcategory();
  EXPECT_TRUE(object.isElectricPowerSupplyEndUseSubcategoryDefaulted());
  EXPECT_EQ("ITE-UPS", object.electricPowerSupplyEndUseSubcategory());

  EXPECT_TRUE(object.setDouble(openstudio::ElectricEquipment_ITE_AirCooledFields::WattsperUnit, 1200.0));
  EXPECT_TRUE(object.setMultiplier(2.0));
  auto wattsPerUnit = object.getDouble(openstudio::ElectricEquipment_ITE_AirCooledFields::WattsperUnit, true);
  ASSERT_TRUE(wattsPerUnit);
  EXPECT_DOUBLE_EQ(2400.0, *wattsPerUnit);

  object.resetMultiplier();
}
