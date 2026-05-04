/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"

#include "../ModelObject/OutputConstructions.hpp"
#include "../ModelObject/OutputConstructions_Impl.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, OutputConstructions_DefaultConstructor) {
  Model model;
  auto outputConstructions = model.getUniqueModelObject<OutputConstructions>();

  EXPECT_EQ(OutputConstructions::iddObjectType(), outputConstructions.iddObject().type());
  EXPECT_TRUE(outputConstructions.reportConstructions());
  EXPECT_FALSE(outputConstructions.reportMaterials());
}

TEST_F(EPModelFixture, OutputConstructions_ScalarAccessors_RoundTrip) {
  Model model;
  auto outputConstructions = model.getUniqueModelObject<OutputConstructions>();

  EXPECT_TRUE(outputConstructions.setReportConstructions(false));
  EXPECT_FALSE(outputConstructions.reportConstructions());
  EXPECT_FALSE(outputConstructions.reportMaterials());

  EXPECT_TRUE(outputConstructions.setReportMaterials(true));
  EXPECT_FALSE(outputConstructions.reportConstructions());
  EXPECT_TRUE(outputConstructions.reportMaterials());

  EXPECT_TRUE(outputConstructions.setReportConstructions(true));
  EXPECT_TRUE(outputConstructions.reportConstructions());
  EXPECT_TRUE(outputConstructions.reportMaterials());

  EXPECT_TRUE(outputConstructions.setReportMaterials(false));
  EXPECT_TRUE(outputConstructions.reportConstructions());
  EXPECT_FALSE(outputConstructions.reportMaterials());
}
