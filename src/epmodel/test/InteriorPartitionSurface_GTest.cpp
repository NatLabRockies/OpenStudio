/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../PlanarSurface/InteriorPartitionSurface.hpp"
#include "../PlanarSurface/InteriorPartitionSurface_Impl.hpp"

#include <utilities/core/Filesystem.hpp>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, InteriorPartitionSurface_DefaultConstructor) {
  Model model;
  InteriorPartitionSurface interiorPartitionSurface({{0, 0, 1}, {0, 0, 0}, {1, 0, 0}, {1, 0, 1}}, model);
  EXPECT_EQ(InteriorPartitionSurface::iddObjectType(), interiorPartitionSurface.iddObject().type());
  EXPECT_FALSE(interiorPartitionSurface.nameString().empty());
  ASSERT_TRUE(interiorPartitionSurface.surfaceArea());
  EXPECT_DOUBLE_EQ(1.0, *interiorPartitionSurface.surfaceArea());
  EXPECT_DOUBLE_EQ(1.0, interiorPartitionSurface.grossArea());
}

TEST_F(EPModelFixture, InteriorPartitionSurface_ScalarAccessors_RoundTrip) {
  Model model;
  InteriorPartitionSurface interiorPartitionSurface({{0, 0, 1}, {0, 0, 0}, {1, 0, 0}, {1, 0, 1}}, model);

  EXPECT_TRUE(interiorPartitionSurface.converttoInternalMass());
  EXPECT_TRUE(interiorPartitionSurface.isConverttoInternalMassDefaulted());
  EXPECT_FALSE(interiorPartitionSurface.setConverttoInternalMass(false));
  EXPECT_TRUE(interiorPartitionSurface.setConverttoInternalMass(true));
  interiorPartitionSurface.resetConverttoInternalMass();
  EXPECT_TRUE(interiorPartitionSurface.converttoInternalMass());

  ASSERT_TRUE(interiorPartitionSurface.surfaceArea());
  EXPECT_DOUBLE_EQ(1.0, *interiorPartitionSurface.surfaceArea());
  EXPECT_TRUE(interiorPartitionSurface.setSurfaceArea(6.5));
  ASSERT_TRUE(interiorPartitionSurface.surfaceArea());
  EXPECT_DOUBLE_EQ(6.5, *interiorPartitionSurface.surfaceArea());
  EXPECT_FALSE(interiorPartitionSurface.setSurfaceArea(boost::optional<double>{}));
  ASSERT_TRUE(interiorPartitionSurface.surfaceArea());
  EXPECT_DOUBLE_EQ(6.5, *interiorPartitionSurface.surfaceArea());
  interiorPartitionSurface.resetSurfaceArea();
  ASSERT_TRUE(interiorPartitionSurface.surfaceArea());
  EXPECT_DOUBLE_EQ(6.5, *interiorPartitionSurface.surfaceArea());

  EXPECT_FALSE(interiorPartitionSurface.numberofVertices());
  EXPECT_TRUE(interiorPartitionSurface.isNumberofVerticesDefaulted());
  EXPECT_FALSE(interiorPartitionSurface.isNumberofVerticesAutocalculated());
  EXPECT_FALSE(interiorPartitionSurface.setNumberofVertices(4.0));
  EXPECT_TRUE(interiorPartitionSurface.setNumberofVertices(boost::optional<double>{}));
  interiorPartitionSurface.autocalculateNumberofVertices();
  interiorPartitionSurface.resetNumberofVertices();
}

TEST_F(EPModelFixture, InteriorPartitionSurface_SetVerticesProjectsSurfaceArea) {
  Model model;
  InteriorPartitionSurface interiorPartitionSurface({{0, 0, 1}, {0, 0, 0}, {1, 0, 0}, {1, 0, 1}}, model);

  EXPECT_TRUE(interiorPartitionSurface.setVertices({{0, 0, 2}, {0, 0, 0}, {1, 0, 0}, {1, 0, 2}}));
  ASSERT_TRUE(interiorPartitionSurface.surfaceArea());
  EXPECT_DOUBLE_EQ(2.0, *interiorPartitionSurface.surfaceArea());
  EXPECT_DOUBLE_EQ(2.0, interiorPartitionSurface.grossArea());

  EXPECT_FALSE(interiorPartitionSurface.setVertices({{0, 0, 0}, {1, 0, 0}}));
  ASSERT_TRUE(interiorPartitionSurface.surfaceArea());
  EXPECT_DOUBLE_EQ(2.0, *interiorPartitionSurface.surfaceArea());

  EXPECT_FALSE(interiorPartitionSurface.setVertices({{0, 0, 0}, {1, 0, 0}, {2, 0, 0}}));
  ASSERT_TRUE(interiorPartitionSurface.surfaceArea());
  EXPECT_DOUBLE_EQ(2.0, *interiorPartitionSurface.surfaceArea());

  EXPECT_FALSE(interiorPartitionSurface.setVertices({{0, 0, 0}, {1, 1, 0}, {0, 1, 0}, {1, 0, 0}}));
  ASSERT_TRUE(interiorPartitionSurface.surfaceArea());
  EXPECT_DOUBLE_EQ(2.0, *interiorPartitionSurface.surfaceArea());
}

TEST_F(EPModelFixture, InteriorPartitionSurface_InvalidConstructorDoesNotLeakObject) {
  Model model;

  EXPECT_THROW(InteriorPartitionSurface({{0, 0, 0}, {1, 0, 0}}, model), openstudio::Exception);
  EXPECT_TRUE(model.getConcreteModelObjects<InteriorPartitionSurface>().empty());

  EXPECT_THROW(InteriorPartitionSurface({{0, 0, 0}, {1, 0, 0}, {2, 0, 0}}, model), openstudio::Exception);
  EXPECT_TRUE(model.getConcreteModelObjects<InteriorPartitionSurface>().empty());
}

TEST_F(EPModelFixture, InteriorPartitionSurface_SurfaceAreaPersistsAcrossLoad) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-interior-partition-surface-area.idf");

  Model model;
  InteriorPartitionSurface surface({{0, 0, 2}, {0, 0, 0}, {1, 0, 0}, {1, 0, 2}}, model);
  ASSERT_TRUE(surface.setName("Interior Mass Surface"));
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedSurface = loadedModel->getConcreteModelObjectByName<InteriorPartitionSurface>("Interior Mass Surface");
  ASSERT_TRUE(loadedSurface);
  ASSERT_TRUE(loadedSurface->surfaceArea());
  EXPECT_DOUBLE_EQ(2.0, *loadedSurface->surfaceArea());
  EXPECT_DOUBLE_EQ(2.0, loadedSurface->grossArea());

  EXPECT_TRUE(loadedSurface->setVertices({{0, 0, 3}, {0, 0, 0}, {1, 0, 0}, {1, 0, 3}}));
  ASSERT_TRUE(loadedSurface->surfaceArea());
  EXPECT_DOUBLE_EQ(3.0, *loadedSurface->surfaceArea());
}
