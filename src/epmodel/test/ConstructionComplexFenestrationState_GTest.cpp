/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <algorithm>
#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/ConstructionComplexFenestrationState.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ConstructionComplexFenestrationState_DefaultConstructor) {
  Model model;
  ConstructionComplexFenestrationState object(model);
  EXPECT_EQ(ConstructionComplexFenestrationState::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, ConstructionComplexFenestrationState_ScalarAccessors_RoundTrip) {
  Model model;
  ConstructionComplexFenestrationState object(model);

  const auto basisTypeValues = ConstructionComplexFenestrationState::basisTypeValues();
  EXPECT_FALSE(basisTypeValues.empty());
  EXPECT_NE(std::find(basisTypeValues.begin(), basisTypeValues.end(), "LBNLWINDOW"), basisTypeValues.end());
  EXPECT_NE(std::find(basisTypeValues.begin(), basisTypeValues.end(), "UserDefined"), basisTypeValues.end());

  const auto basisSymmetryTypeValues = ConstructionComplexFenestrationState::basisSymmetryTypeValues();
  EXPECT_FALSE(basisSymmetryTypeValues.empty());
  EXPECT_NE(std::find(basisSymmetryTypeValues.begin(), basisSymmetryTypeValues.end(), "None"), basisSymmetryTypeValues.end());
  EXPECT_NE(std::find(basisSymmetryTypeValues.begin(), basisSymmetryTypeValues.end(), "Axisymmetric"), basisSymmetryTypeValues.end());

  EXPECT_TRUE(object.isBasisTypeDefaulted());
  EXPECT_EQ("LBNLWINDOW", object.basisType());
  EXPECT_TRUE(object.setBasisType("UserDefined"));
  EXPECT_EQ("UserDefined", object.basisType());
  EXPECT_FALSE(object.isBasisTypeDefaulted());
  object.resetBasisType();
  EXPECT_TRUE(object.isBasisTypeDefaulted());
  EXPECT_EQ("LBNLWINDOW", object.basisType());

  EXPECT_TRUE(object.isBasisSymmetryTypeDefaulted());
  EXPECT_EQ("None", object.basisSymmetryType());
  EXPECT_TRUE(object.setBasisSymmetryType("Axisymmetric"));
  EXPECT_EQ("Axisymmetric", object.basisSymmetryType());
  EXPECT_FALSE(object.isBasisSymmetryTypeDefaulted());
  object.resetBasisSymmetryType();
  EXPECT_TRUE(object.isBasisSymmetryTypeDefaulted());
  EXPECT_EQ("None", object.basisSymmetryType());
}
