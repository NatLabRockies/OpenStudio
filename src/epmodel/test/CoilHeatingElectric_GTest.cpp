/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../StraightComponent/CoilHeatingElectric.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoilHeatingElectric_DefaultConstructor) {
  Model model;
  CoilHeatingElectric coil(model);
  EXPECT_EQ(CoilHeatingElectric::iddObjectType(), coil.iddObject().type());
  EXPECT_FALSE(coil.nameString().empty());

  EXPECT_DOUBLE_EQ(1.0, coil.efficiency());
  EXPECT_TRUE(coil.isEfficiencyDefaulted());
  EXPECT_FALSE(coil.nominalCapacity());
  EXPECT_TRUE(coil.isNominalCapacityDefaulted());
  EXPECT_FALSE(coil.isNominalCapacityAutosized());
}

TEST_F(EPModelFixture, CoilHeatingElectric_ScalarAccessors_RoundTrip) {
  Model model;
  CoilHeatingElectric coil(model);

  EXPECT_TRUE(coil.setEfficiency(0.91));
  EXPECT_DOUBLE_EQ(0.91, coil.efficiency());
  EXPECT_FALSE(coil.isEfficiencyDefaulted());
  coil.resetEfficiency();
  EXPECT_DOUBLE_EQ(1.0, coil.efficiency());
  EXPECT_TRUE(coil.isEfficiencyDefaulted());

  EXPECT_TRUE(coil.setNominalCapacity(4200.0));
  ASSERT_TRUE(coil.nominalCapacity());
  EXPECT_DOUBLE_EQ(4200.0, *coil.nominalCapacity());
  EXPECT_FALSE(coil.isNominalCapacityDefaulted());
  EXPECT_FALSE(coil.isNominalCapacityAutosized());

  coil.autosizeNominalCapacity();
  EXPECT_TRUE(coil.isNominalCapacityAutosized());
  EXPECT_FALSE(coil.nominalCapacity());

  coil.resetNominalCapacity();
  EXPECT_TRUE(coil.isNominalCapacityDefaulted());
  EXPECT_FALSE(coil.isNominalCapacityAutosized());
  EXPECT_FALSE(coil.nominalCapacity());

  EXPECT_FALSE(coil.autosizedNominalCapacity());
}
