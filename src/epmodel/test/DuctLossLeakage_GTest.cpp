/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/DuctLossLeakage.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, DuctLossLeakage_DefaultConstructor) {
  Model model;
  DuctLossLeakage ductLossLeakage(model);
  EXPECT_EQ(DuctLossLeakage::iddObjectType(), ductLossLeakage.iddObject().type());
}

TEST_F(EPModelFixture, DuctLossLeakage_ScalarAccessors_RoundTrip) {
  Model model;
  DuctLossLeakage ductLossLeakage(model);

  EXPECT_TRUE(ductLossLeakage.setName("Main Duct Leakage"));
  EXPECT_EQ("Main Duct Leakage", ductLossLeakage.nameString());
}
