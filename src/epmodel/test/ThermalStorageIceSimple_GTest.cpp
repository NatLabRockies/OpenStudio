/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <algorithm>

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/ThermalStorageIceSimple.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ThermalStorageIceSimple_DefaultConstructor) {
  Model model;
  ThermalStorageIceSimple ice(model);
  EXPECT_EQ(ThermalStorageIceSimple::iddObjectType(), ice.iddObject().type());
}

TEST_F(EPModelFixture, ThermalStorageIceSimple_ScalarAccessors_RoundTrip) {
  Model model;
  ThermalStorageIceSimple ice(model);

  EXPECT_TRUE(ice.setCapacity(2.25));
  ASSERT_TRUE(ice.capacity());
  EXPECT_DOUBLE_EQ(2.25, ice.capacity().get());
  EXPECT_FALSE(ice.isCapacityAutosized());
  ice.autosizeCapacity();
  EXPECT_TRUE(ice.isCapacityAutosized());
  EXPECT_FALSE(ice.capacity());

  EXPECT_TRUE(ice.setIceStorageType("IceOnCoilInternal"));
  EXPECT_EQ("IceOnCoilInternal", ice.iceStorageType());

  const auto iceStorageTypes = ThermalStorageIceSimple::iceStorageTypeValues();
  EXPECT_GE(iceStorageTypes.size(), 2u);
  EXPECT_NE(std::find(iceStorageTypes.begin(), iceStorageTypes.end(), "IceOnCoilInternal"), iceStorageTypes.end());
}
