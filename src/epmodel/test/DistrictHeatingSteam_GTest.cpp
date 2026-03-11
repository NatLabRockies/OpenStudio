/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../StraightComponent/DistrictHeatingSteam.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, DistrictHeatingSteam_DefaultConstructor) {
  Model model;
  DistrictHeatingSteam districtHeatingSteam(model);
  EXPECT_EQ(DistrictHeatingSteam::iddObjectType(), districtHeatingSteam.iddObject().type());
  EXPECT_FALSE(districtHeatingSteam.nameString().empty());
  EXPECT_TRUE(districtHeatingSteam.isNominalCapacityAutosized());
  EXPECT_FALSE(districtHeatingSteam.nominalCapacity());
}

TEST_F(EPModelFixture, DistrictHeatingSteam_ScalarAccessors_RoundTrip) {
  Model model;
  DistrictHeatingSteam districtHeatingSteam(model);

  EXPECT_TRUE(districtHeatingSteam.setNominalCapacity(12345.0));
  ASSERT_TRUE(districtHeatingSteam.nominalCapacity());
  EXPECT_DOUBLE_EQ(12345.0, districtHeatingSteam.nominalCapacity().get());
  EXPECT_FALSE(districtHeatingSteam.isNominalCapacityAutosized());

  districtHeatingSteam.autosizeNominalCapacity();
  EXPECT_TRUE(districtHeatingSteam.isNominalCapacityAutosized());
  EXPECT_FALSE(districtHeatingSteam.nominalCapacity());

  EXPECT_FALSE(districtHeatingSteam.autosizedNominalCapacity());
}
