/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/MatrixTwoDimension.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, MatrixTwoDimension_DefaultConstructor) {
  Model model;
  MatrixTwoDimension matrix(model);
  EXPECT_EQ(MatrixTwoDimension::iddObjectType(), matrix.iddObject().type());
}

TEST_F(EPModelFixture, MatrixTwoDimension_ScalarAccessors_RoundTrip) {
  Model model;
  MatrixTwoDimension matrix(model);

  EXPECT_TRUE(matrix.setNumberofRows(3));
  EXPECT_EQ(3, matrix.numberofRows());

  EXPECT_TRUE(matrix.setNumberofColumns(4));
  EXPECT_EQ(4, matrix.numberofColumns());
}
