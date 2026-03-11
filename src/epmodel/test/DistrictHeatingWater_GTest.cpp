/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../StraightComponent/DistrictHeatingWater.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, DistrictHeatingWater_DefaultConstructor) {
  Model model;
  DistrictHeatingWater districtHeatingWater(model);
  EXPECT_EQ(DistrictHeatingWater::iddObjectType(), districtHeatingWater.iddObject().type());
  EXPECT_FALSE(districtHeatingWater.nameString().empty());
  EXPECT_TRUE(districtHeatingWater.isNominalCapacityAutosized());
  EXPECT_FALSE(districtHeatingWater.nominalCapacity());
}

TEST_F(EPModelFixture, DistrictHeatingWater_ScalarAccessors_RoundTrip) {
  Model model;
  DistrictHeatingWater districtHeatingWater(model);

  EXPECT_TRUE(districtHeatingWater.setNominalCapacity(12345.0));
  ASSERT_TRUE(districtHeatingWater.nominalCapacity());
  EXPECT_DOUBLE_EQ(12345.0, districtHeatingWater.nominalCapacity().get());
  EXPECT_FALSE(districtHeatingWater.isNominalCapacityAutosized());

  districtHeatingWater.autosizeNominalCapacity();
  EXPECT_TRUE(districtHeatingWater.isNominalCapacityAutosized());
  EXPECT_FALSE(districtHeatingWater.nominalCapacity());

  EXPECT_FALSE(districtHeatingWater.autosizedNominalCapacity());
}
