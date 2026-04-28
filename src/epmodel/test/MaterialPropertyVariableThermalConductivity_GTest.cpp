/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/MaterialPropertyVariableThermalConductivity.hpp"
#include "../OpaqueMaterial/MasslessOpaqueMaterial.hpp"
#include <utilities/idd/MaterialProperty_VariableThermalConductivity_FieldEnums.hxx>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, MaterialPropertyVariableThermalConductivity_DefaultConstructor) {
  Model model;
  MaterialPropertyVariableThermalConductivity object(model);
  EXPECT_EQ(MaterialPropertyVariableThermalConductivity::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, MaterialPropertyVariableThermalConductivity_ScalarAccessors_RoundTrip) {
  Model model;
  MasslessOpaqueMaterial material(model);
  MaterialPropertyVariableThermalConductivity object(model);

  EXPECT_FALSE(object.setName("Variable Thermal Conductivity Material Property"));
  EXPECT_TRUE(object.nameString().empty());

  ASSERT_FALSE(material.nameString().empty());
  EXPECT_TRUE(object.setString(openstudio::MaterialProperty_VariableThermalConductivityFields::Name, material.nameString()));
  auto name = object.getString(openstudio::MaterialProperty_VariableThermalConductivityFields::Name, true);
  ASSERT_TRUE(name);
  EXPECT_EQ(material.nameString(), *name);
}
