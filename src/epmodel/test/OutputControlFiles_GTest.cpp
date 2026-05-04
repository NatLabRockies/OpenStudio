/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"

#include "../ModelObject/OutputControlFiles.hpp"
#include "../ModelObject/OutputControlFiles_Impl.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, OutputControlFiles_DefaultConstructor) {
  Model model;
  auto outputControlFiles = model.getUniqueModelObject<OutputControlFiles>();

  EXPECT_EQ(OutputControlFiles::iddObjectType(), outputControlFiles.iddObject().type());
  EXPECT_FALSE(outputControlFiles.outputCSV());
  EXPECT_TRUE(outputControlFiles.outputMTR());
  EXPECT_TRUE(outputControlFiles.outputESO());
  EXPECT_TRUE(outputControlFiles.outputJSON());
  EXPECT_TRUE(outputControlFiles.outputScreen());
  EXPECT_TRUE(outputControlFiles.outputPlantComponentSizing());
}

TEST_F(EPModelFixture, OutputControlFiles_ScalarAccessors_RoundTrip) {
  Model model;
  auto outputControlFiles = model.getUniqueModelObject<OutputControlFiles>();

  EXPECT_TRUE(outputControlFiles.setOutputCSV(true));
  EXPECT_TRUE(outputControlFiles.outputCSV());

  EXPECT_TRUE(outputControlFiles.setOutputMTR(false));
  EXPECT_FALSE(outputControlFiles.outputMTR());

  EXPECT_TRUE(outputControlFiles.setOutputJSON(false));
  EXPECT_FALSE(outputControlFiles.outputJSON());

  EXPECT_TRUE(outputControlFiles.setOutputScreen(false));
  EXPECT_FALSE(outputControlFiles.outputScreen());

  EXPECT_TRUE(outputControlFiles.setOutputPlantComponentSizing(false));
  EXPECT_FALSE(outputControlFiles.outputPlantComponentSizing());
}
