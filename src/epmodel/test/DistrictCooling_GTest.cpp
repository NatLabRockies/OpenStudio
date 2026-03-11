/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../StraightComponent/DistrictCooling.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, DistrictCooling_DefaultConstructor) {
  Model model;
  DistrictCooling districtCooling(model);
  EXPECT_EQ(DistrictCooling::iddObjectType(), districtCooling.iddObject().type());
  EXPECT_FALSE(districtCooling.nameString().empty());
  EXPECT_TRUE(districtCooling.isNominalCapacityAutosized());
  EXPECT_FALSE(districtCooling.nominalCapacity());
}

TEST_F(EPModelFixture, DistrictCooling_ScalarAccessors_RoundTrip) {
  Model model;
  DistrictCooling districtCooling(model);

  EXPECT_TRUE(districtCooling.setNominalCapacity(12345.0));
  ASSERT_TRUE(districtCooling.nominalCapacity());
  EXPECT_DOUBLE_EQ(12345.0, districtCooling.nominalCapacity().get());
  EXPECT_FALSE(districtCooling.isNominalCapacityAutosized());

  districtCooling.autosizeNominalCapacity();
  EXPECT_TRUE(districtCooling.isNominalCapacityAutosized());
  EXPECT_FALSE(districtCooling.nominalCapacity());

  EXPECT_FALSE(districtCooling.autosizedNominalCapacity());
}
