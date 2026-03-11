/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/GeometryTransform.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, GeometryTransform_DefaultConstructor) {
  Model model;
  GeometryTransform geometryTransform(model);
  EXPECT_EQ(GeometryTransform::iddObjectType(), geometryTransform.iddObject().type());
}

TEST_F(EPModelFixture, GeometryTransform_ScalarAccessors_RoundTrip) {
  Model model;
  GeometryTransform geometryTransform(model);

  EXPECT_FALSE(geometryTransform.isPlaneofTransformDefaulted());
  const std::string defaultPlane = geometryTransform.planeofTransform();

  const auto planeValues = GeometryTransform::planeofTransformValues();
  EXPECT_FALSE(planeValues.empty());

  EXPECT_TRUE(geometryTransform.setPlaneofTransform("XZ"));
  EXPECT_EQ("XZ", geometryTransform.planeofTransform());
  EXPECT_FALSE(geometryTransform.isPlaneofTransformDefaulted());
  geometryTransform.resetPlaneofTransform();
  EXPECT_FALSE(geometryTransform.isPlaneofTransformDefaulted());
  EXPECT_EQ(defaultPlane, geometryTransform.planeofTransform());

  EXPECT_TRUE(geometryTransform.setCurrentAspectRatio(1.25));
  EXPECT_DOUBLE_EQ(1.25, geometryTransform.currentAspectRatio());

  EXPECT_TRUE(geometryTransform.setNewAspectRatio(0.9));
  EXPECT_DOUBLE_EQ(0.9, geometryTransform.newAspectRatio());
}
