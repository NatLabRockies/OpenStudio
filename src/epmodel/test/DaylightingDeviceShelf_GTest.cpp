/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/DaylightingDeviceShelf.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, DaylightingDeviceShelf_DefaultConstructor) {
  Model model;
  DaylightingDeviceShelf shelf(model);
  EXPECT_EQ(DaylightingDeviceShelf::iddObjectType(), shelf.iddObject().type());
}

TEST_F(EPModelFixture, DaylightingDeviceShelf_ScalarAccessors_RoundTrip) {
  Model model;
  DaylightingDeviceShelf shelf(model);

  EXPECT_FALSE(shelf.viewFactortoOutsideShelf());

  EXPECT_TRUE(shelf.setViewFactortoOutsideShelf(0.42));
  ASSERT_TRUE(shelf.viewFactortoOutsideShelf());
  EXPECT_DOUBLE_EQ(0.42, *shelf.viewFactortoOutsideShelf());

  shelf.resetViewFactortoOutsideShelf();
  EXPECT_FALSE(shelf.viewFactortoOutsideShelf());
}
