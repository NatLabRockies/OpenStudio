/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../WaterToAirComponent/CoilUserDefined.hpp"

#include <utilities/idd/Coil_UserDefined_FieldEnums.hxx>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoilUserDefined_DefaultConstructor) {
  Model model;
  CoilUserDefined coil(model);
  EXPECT_EQ(CoilUserDefined::iddObjectType(), coil.iddObject().type());
}

TEST_F(EPModelFixture, CoilUserDefined_ScalarAccessors_RoundTrip) {
  Model model;
  CoilUserDefined coil(model);

  ASSERT_TRUE(coil.setInt(openstudio::Coil_UserDefinedFields::NumberofAirConnections, 1));
  EXPECT_EQ(1, coil.numberofAirConnections());

  ASSERT_TRUE(coil.setInt(openstudio::Coil_UserDefinedFields::NumberofAirConnections, 2));
  EXPECT_EQ(2, coil.numberofAirConnections());
}
