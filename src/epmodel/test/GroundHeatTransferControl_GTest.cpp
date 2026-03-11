/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/GroundHeatTransferControl.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, GroundHeatTransferControl_DefaultConstructor) {
  Model model;
  GroundHeatTransferControl object(model);
  EXPECT_EQ(GroundHeatTransferControl::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, GroundHeatTransferControl_ScalarAccessors_RoundTrip) {
  Model model;
  GroundHeatTransferControl object(model);

  EXPECT_FALSE(object.runBasementPreprocessor());
  EXPECT_TRUE(object.isRunBasementPreprocessorDefaulted());
  EXPECT_FALSE(object.runSlabPreprocessor());
  EXPECT_TRUE(object.isRunSlabPreprocessorDefaulted());

  EXPECT_TRUE(object.setRunBasementPreprocessor(true));
  EXPECT_TRUE(object.runBasementPreprocessor());
  EXPECT_FALSE(object.isRunBasementPreprocessorDefaulted());

  EXPECT_TRUE(object.setRunSlabPreprocessor(true));
  EXPECT_TRUE(object.runSlabPreprocessor());
  EXPECT_FALSE(object.isRunSlabPreprocessorDefaulted());

  object.resetRunBasementPreprocessor();
  EXPECT_FALSE(object.runBasementPreprocessor());
  EXPECT_TRUE(object.isRunBasementPreprocessorDefaulted());

  object.resetRunSlabPreprocessor();
  EXPECT_FALSE(object.runSlabPreprocessor());
  EXPECT_TRUE(object.isRunSlabPreprocessorDefaulted());
}
