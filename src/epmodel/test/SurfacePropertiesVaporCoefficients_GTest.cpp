/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/SurfacePropertiesVaporCoefficients.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, SurfacePropertiesVaporCoefficients_DefaultConstructor) {
  Model model;
  SurfacePropertiesVaporCoefficients obj(model);
  EXPECT_EQ(SurfacePropertiesVaporCoefficients::iddObjectType(), obj.iddObject().type());
}

TEST_F(EPModelFixture, SurfacePropertiesVaporCoefficients_ScalarAccessors_RoundTrip) {
  Model model;
  SurfacePropertiesVaporCoefficients obj(model);

  // A2 - Constant External Vapor Transfer Coefficient (bool, default No)
  EXPECT_FALSE(obj.constantExternalVaporTransferCoefficient());
  EXPECT_TRUE(obj.isConstantExternalVaporTransferCoefficientDefaulted());
  EXPECT_TRUE(obj.setConstantExternalVaporTransferCoefficient(true));
  EXPECT_TRUE(obj.constantExternalVaporTransferCoefficient());
  EXPECT_FALSE(obj.isConstantExternalVaporTransferCoefficientDefaulted());
  obj.resetConstantExternalVaporTransferCoefficient();
  EXPECT_TRUE(obj.isConstantExternalVaporTransferCoefficientDefaulted());
  EXPECT_FALSE(obj.constantExternalVaporTransferCoefficient());

  // N1 - External Vapor Coefficient Value (double, default 0, minimum 0.0)
  EXPECT_DOUBLE_EQ(0.0, obj.externalVaporCoefficientValue());
  EXPECT_TRUE(obj.isExternalVaporCoefficientValueDefaulted());
  EXPECT_TRUE(obj.setExternalVaporCoefficientValue(0.5));
  EXPECT_DOUBLE_EQ(0.5, obj.externalVaporCoefficientValue());
  EXPECT_FALSE(obj.isExternalVaporCoefficientValueDefaulted());
  obj.resetExternalVaporCoefficientValue();
  EXPECT_TRUE(obj.isExternalVaporCoefficientValueDefaulted());
  EXPECT_DOUBLE_EQ(0.0, obj.externalVaporCoefficientValue());

  // A3 - Constant Internal vapor Transfer Coefficient (bool, default No)
  EXPECT_FALSE(obj.constantInternalvaporTransferCoefficient());
  EXPECT_TRUE(obj.isConstantInternalvaporTransferCoefficientDefaulted());
  EXPECT_TRUE(obj.setConstantInternalvaporTransferCoefficient(true));
  EXPECT_TRUE(obj.constantInternalvaporTransferCoefficient());
  EXPECT_FALSE(obj.isConstantInternalvaporTransferCoefficientDefaulted());
  obj.resetConstantInternalvaporTransferCoefficient();
  EXPECT_TRUE(obj.isConstantInternalvaporTransferCoefficientDefaulted());
  EXPECT_FALSE(obj.constantInternalvaporTransferCoefficient());

  // N2 - Internal Vapor Coefficient Value (double, default 0, minimum 0.0)
  EXPECT_DOUBLE_EQ(0.0, obj.internalVaporCoefficientValue());
  EXPECT_TRUE(obj.isInternalVaporCoefficientValueDefaulted());
  EXPECT_TRUE(obj.setInternalVaporCoefficientValue(1.2));
  EXPECT_DOUBLE_EQ(1.2, obj.internalVaporCoefficientValue());
  EXPECT_FALSE(obj.isInternalVaporCoefficientValueDefaulted());
  obj.resetInternalVaporCoefficientValue();
  EXPECT_TRUE(obj.isInternalVaporCoefficientValueDefaulted());
  EXPECT_DOUBLE_EQ(0.0, obj.internalVaporCoefficientValue());
}
