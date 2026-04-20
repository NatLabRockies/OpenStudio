/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/ConstructionWindowDataFile.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ConstructionWindowDataFile_DefaultConstructor) {
  Model model;
  ConstructionWindowDataFile object(model);
  EXPECT_EQ(ConstructionWindowDataFile::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, ConstructionWindowDataFile_ScalarAccessors_RoundTrip) {
  Model model;
  ConstructionWindowDataFile object(model);

  EXPECT_TRUE(object.setFileName("CustomWindowDataFile.dat"));
  ASSERT_TRUE(object.fileName());
  EXPECT_EQ("CustomWindowDataFile.dat", object.fileName().get());

  object.resetFileName();
  if (const auto fileName = object.fileName()) {
    EXPECT_NE("CustomWindowDataFile.dat", fileName.get());
  }
}
