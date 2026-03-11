/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/DuctLossMakeupAir.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, DuctLossMakeupAir_DefaultConstructor) {
  Model model;
  DuctLossMakeupAir ductLossMakeupAir(model);
  EXPECT_EQ(DuctLossMakeupAir::iddObjectType(), ductLossMakeupAir.iddObject().type());
}

TEST_F(EPModelFixture, DuctLossMakeupAir_ScalarAccessors_RoundTrip) {
  Model model;
  DuctLossMakeupAir ductLossMakeupAir(model);

  EXPECT_TRUE(ductLossMakeupAir.setName("Main Duct Makeup Air"));
  EXPECT_EQ("Main Duct Makeup Air", ductLossMakeupAir.nameString());
}
