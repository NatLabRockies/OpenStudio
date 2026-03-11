/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/GroundHeatTransferSlabInsulation.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, GroundHeatTransferSlabInsulation_DefaultConstructor) {
  Model model;
  GroundHeatTransferSlabInsulation object(model);
  EXPECT_EQ(GroundHeatTransferSlabInsulation::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, GroundHeatTransferSlabInsulation_ScalarAccessors_RoundTrip) {
  Model model;
  GroundHeatTransferSlabInsulation object(model);

  EXPECT_TRUE(object.isRINSRvalueofunderslabinsulationDefaulted());
  EXPECT_TRUE(object.setRINSRvalueofunderslabinsulation(1.5));
  EXPECT_DOUBLE_EQ(1.5, object.rINSRvalueofunderslabinsulation());
  EXPECT_FALSE(object.isRINSRvalueofunderslabinsulationDefaulted());
  object.resetRINSRvalueofunderslabinsulation();
  EXPECT_TRUE(object.isRINSRvalueofunderslabinsulationDefaulted());

  EXPECT_TRUE(object.isDINSWidthofstripofunderslabinsulationDefaulted());
  EXPECT_TRUE(object.setDINSWidthofstripofunderslabinsulation(0.8));
  EXPECT_DOUBLE_EQ(0.8, object.dINSWidthofstripofunderslabinsulation());
  EXPECT_FALSE(object.isDINSWidthofstripofunderslabinsulationDefaulted());
  object.resetDINSWidthofstripofunderslabinsulation();
  EXPECT_TRUE(object.isDINSWidthofstripofunderslabinsulationDefaulted());

  EXPECT_TRUE(object.isRVINSRvalueofverticalinsulationDefaulted());
  EXPECT_TRUE(object.setRVINSRvalueofverticalinsulation(2.1));
  EXPECT_DOUBLE_EQ(2.1, object.rVINSRvalueofverticalinsulation());
  EXPECT_FALSE(object.isRVINSRvalueofverticalinsulationDefaulted());
  object.resetRVINSRvalueofverticalinsulation();
  EXPECT_TRUE(object.isRVINSRvalueofverticalinsulationDefaulted());

  EXPECT_TRUE(object.isZVINSDepthofverticalinsulationDefaulted());
  EXPECT_TRUE(object.setZVINSDepthofverticalinsulation(0.6));
  EXPECT_DOUBLE_EQ(0.6, object.zVINSDepthofverticalinsulation());
  EXPECT_FALSE(object.isZVINSDepthofverticalinsulationDefaulted());
  object.resetZVINSDepthofverticalinsulation();
  EXPECT_TRUE(object.isZVINSDepthofverticalinsulationDefaulted());

  const auto values = GroundHeatTransferSlabInsulation::iVINSFlagIsthereverticalinsulationValues();
  EXPECT_FALSE(values.empty());
  EXPECT_TRUE(object.isIVINSFlagIsthereverticalinsulationDefaulted());
  EXPECT_TRUE(object.setIVINSFlagIsthereverticalinsulation("1"));
  EXPECT_EQ("1", object.iVINSFlagIsthereverticalinsulation());
  EXPECT_FALSE(object.isIVINSFlagIsthereverticalinsulationDefaulted());
  object.resetIVINSFlagIsthereverticalinsulation();
  EXPECT_TRUE(object.isIVINSFlagIsthereverticalinsulationDefaulted());
}
