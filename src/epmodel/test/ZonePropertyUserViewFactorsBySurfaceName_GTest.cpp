/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"

#include "../ModelObject/ZonePropertyUserViewFactorsBySurfaceName.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, API_ZonePropertyUserViewFactorsBySurfaceName_DefaultConstructor) {
  Model model;
  ZonePropertyUserViewFactorsBySurfaceName viewFactors(model);
  EXPECT_EQ(ZonePropertyUserViewFactorsBySurfaceName::iddObjectType(), viewFactors.iddObject().type());
}

TEST_F(EPModelFixture, ZonePropertyUserViewFactorsBySurfaceName_ScalarAccessors_RoundTrip) {
  Model model;
  ZonePropertyUserViewFactorsBySurfaceName viewFactors(model);

  // This IDD type does not expose a Name field, so setName should fail and the string stay empty.
  EXPECT_FALSE(viewFactors.setName("Zone View Factors"));
  EXPECT_EQ("", viewFactors.nameString());
}
