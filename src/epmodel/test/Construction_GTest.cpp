/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../LayeredConstruction/Construction.hpp"
#include "../LayeredConstruction/Construction_Impl.hpp"
#include "../OpaqueMaterial/StandardOpaqueMaterial.hpp"
#include "../OpaqueMaterial/StandardOpaqueMaterial_Impl.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, Construction_DefaultConstructor) {
  Model model;
  Construction construction(model);
  EXPECT_EQ(Construction::iddObjectType(), construction.iddObject().type());
}

TEST_F(EPModelFixture, Construction_ScalarAccessors_RoundTrip) {
  Model model;
  Construction construction(model);

  // Construction has no class-specific simple scalar fields; base Name scalar is the roundtrip coverage.
  EXPECT_TRUE(construction.setName("EPModel Construction"));
  EXPECT_EQ("EPModel Construction", construction.nameString());
}

TEST_F(EPModelFixture, Construction_IsSymmetric) {
  Model model;
  Construction construction(model);
  EXPECT_TRUE(construction.isSymmetric());

  StandardOpaqueMaterial outer(model);
  StandardOpaqueMaterial inner(model);
  EXPECT_TRUE(construction.setLayers({outer}));
  EXPECT_TRUE(construction.isSymmetric());

  EXPECT_TRUE(construction.setLayers({outer, inner}));
  EXPECT_FALSE(construction.isSymmetric());

  EXPECT_TRUE(construction.setLayers({outer, inner, outer}));
  EXPECT_TRUE(construction.isSymmetric());

  // Layers are compared by object, not by properties
  StandardOpaqueMaterial outerCopy(model);
  EXPECT_TRUE(construction.setLayers({outer, inner, outerCopy}));
  EXPECT_FALSE(construction.isSymmetric());
}

TEST_F(EPModelFixture, Construction_EqualLayers_ReverseEqualLayers) {
  Model model;
  Construction construction(model);
  Construction other(model);

  // Two constructions without layers are both equal and reverse equal
  EXPECT_TRUE(construction.equalLayers(other));
  EXPECT_TRUE(construction.reverseEqualLayers(other));

  StandardOpaqueMaterial outer(model);
  StandardOpaqueMaterial inner(model);
  EXPECT_TRUE(construction.setLayers({outer, inner}));
  EXPECT_FALSE(construction.equalLayers(other));
  EXPECT_FALSE(construction.reverseEqualLayers(other));

  EXPECT_TRUE(other.setLayers({outer, inner}));
  EXPECT_TRUE(construction.equalLayers(other));
  EXPECT_FALSE(construction.reverseEqualLayers(other));

  EXPECT_TRUE(other.setLayers({inner, outer}));
  EXPECT_FALSE(construction.equalLayers(other));
  EXPECT_TRUE(construction.reverseEqualLayers(other));
  EXPECT_TRUE(other.reverseEqualLayers(construction));

  // A prefix is not enough
  EXPECT_TRUE(other.setLayers({inner, outer, inner}));
  EXPECT_FALSE(construction.equalLayers(other));
  EXPECT_FALSE(construction.reverseEqualLayers(other));
  EXPECT_FALSE(other.equalLayers(construction));
  EXPECT_FALSE(other.reverseEqualLayers(construction));

  // A symmetric construction is reverse equal to itself
  EXPECT_TRUE(other.isSymmetric());
  EXPECT_TRUE(other.equalLayers(other));
  EXPECT_TRUE(other.reverseEqualLayers(other));
  EXPECT_FALSE(construction.reverseEqualLayers(construction));

  // Layers are compared by object, not by properties
  StandardOpaqueMaterial outerCopy(model);
  EXPECT_TRUE(other.setLayers({outerCopy, inner}));
  EXPECT_FALSE(construction.equalLayers(other));
}

TEST_F(EPModelFixture, Construction_ReverseConstruction) {
  Model model;
  StandardOpaqueMaterial outer(model);
  StandardOpaqueMaterial inner(model);

  // A symmetric construction is its own reverse
  Construction symmetric(model);
  EXPECT_TRUE(symmetric.setLayers({outer, inner, outer}));
  EXPECT_EQ(symmetric, symmetric.reverseConstruction());
  EXPECT_EQ(1, model.getConcreteModelObjects<Construction>().size());

  // No existing match: a new one is created
  Construction construction(model);
  EXPECT_TRUE(construction.setName("Wall"));
  EXPECT_TRUE(construction.setLayers({outer, inner}));
  auto reversed = construction.reverseConstruction();
  EXPECT_NE(construction, reversed);
  EXPECT_EQ("Wall Reversed", reversed.nameString());
  EXPECT_TRUE(construction.reverseEqualLayers(reversed));
  EXPECT_EQ(3, model.getConcreteModelObjects<Construction>().size());

  // An existing match is reused, in both directions
  EXPECT_EQ(reversed, construction.reverseConstruction());
  EXPECT_EQ(construction, reversed.reverseConstruction());
  EXPECT_EQ(3, model.getConcreteModelObjects<Construction>().size());
}
