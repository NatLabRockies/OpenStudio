/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/SurfaceContaminantSourceAndSinkGenericBoundaryLayerDiffusion.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, SurfaceContaminantSourceAndSinkGenericBoundaryLayerDiffusion_DefaultConstructor) {
  Model model;
  SurfaceContaminantSourceAndSinkGenericBoundaryLayerDiffusion obj(model);
  EXPECT_EQ(SurfaceContaminantSourceAndSinkGenericBoundaryLayerDiffusion::iddObjectType(), obj.iddObject().type());
}

TEST_F(EPModelFixture, SurfaceContaminantSourceAndSinkGenericBoundaryLayerDiffusion_ScalarAccessors_RoundTrip) {
  Model model;
  SurfaceContaminantSourceAndSinkGenericBoundaryLayerDiffusion obj(model);

  // Mass Transfer Coefficient: optional, minimum 0.0, no default
  EXPECT_FALSE(obj.massTransferCoefficient());
  EXPECT_TRUE(obj.setMassTransferCoefficient(0.5));
  ASSERT_TRUE(obj.massTransferCoefficient());
  EXPECT_DOUBLE_EQ(0.5, obj.massTransferCoefficient().get());
  // boundary: 0.0 is valid (minimum 0.0 inclusive)
  EXPECT_TRUE(obj.setMassTransferCoefficient(0.0));
  ASSERT_TRUE(obj.massTransferCoefficient());
  EXPECT_DOUBLE_EQ(0.0, obj.massTransferCoefficient().get());
  // below minimum should fail
  EXPECT_FALSE(obj.setMassTransferCoefficient(-0.1));
  // reset
  obj.resetMassTransferCoefficient();
  EXPECT_FALSE(obj.massTransferCoefficient());

  // Henry Adsorption Constant or Partition Coefficient: optional, minimum> 0.0, no default
  EXPECT_FALSE(obj.henryAdsorptionConstantorPartitionCoefficient());
  EXPECT_TRUE(obj.setHenryAdsorptionConstantorPartitionCoefficient(1.5));
  ASSERT_TRUE(obj.henryAdsorptionConstantorPartitionCoefficient());
  EXPECT_DOUBLE_EQ(1.5, obj.henryAdsorptionConstantorPartitionCoefficient().get());
  // boundary: 0.0 is invalid (minimum> 0.0 exclusive)
  EXPECT_FALSE(obj.setHenryAdsorptionConstantorPartitionCoefficient(0.0));
  // negative should fail
  EXPECT_FALSE(obj.setHenryAdsorptionConstantorPartitionCoefficient(-1.0));
  // small positive should succeed
  EXPECT_TRUE(obj.setHenryAdsorptionConstantorPartitionCoefficient(0.001));
  ASSERT_TRUE(obj.henryAdsorptionConstantorPartitionCoefficient());
  EXPECT_DOUBLE_EQ(0.001, obj.henryAdsorptionConstantorPartitionCoefficient().get());
  // reset
  obj.resetHenryAdsorptionConstantorPartitionCoefficient();
  EXPECT_FALSE(obj.henryAdsorptionConstantorPartitionCoefficient());
}
