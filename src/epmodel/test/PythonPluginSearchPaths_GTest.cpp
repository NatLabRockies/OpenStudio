/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ResourceObject/PythonPluginSearchPaths.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, PythonPluginSearchPaths_DefaultConstructor) {
  Model model;
  PythonPluginSearchPaths pythonPluginSearchPaths(model);
  EXPECT_EQ(PythonPluginSearchPaths::iddObjectType(), pythonPluginSearchPaths.iddObject().type());
  EXPECT_FALSE(pythonPluginSearchPaths.nameString().empty());
}

TEST_F(EPModelFixture, PythonPluginSearchPaths_ScalarAccessors_RoundTrip) {
  Model model;
  PythonPluginSearchPaths searchPaths(model);

  EXPECT_TRUE(searchPaths.setAddCurrentWorkingDirectoryToSearchPath(false));
  EXPECT_FALSE(searchPaths.addCurrentWorkingDirectoryToSearchPath());
  EXPECT_FALSE(searchPaths.isAddCurrentWorkingDirectoryToSearchPathDefaulted());
  searchPaths.resetAddCurrentWorkingDirectoryToSearchPath();
  EXPECT_TRUE(searchPaths.addCurrentWorkingDirectoryToSearchPath());
  EXPECT_TRUE(searchPaths.isAddCurrentWorkingDirectoryToSearchPathDefaulted());

  EXPECT_TRUE(searchPaths.setAddInputFileDirectoryToSearchPath(false));
  EXPECT_FALSE(searchPaths.addInputFileDirectoryToSearchPath());
  EXPECT_FALSE(searchPaths.isAddInputFileDirectoryToSearchPathDefaulted());
  searchPaths.resetAddInputFileDirectoryToSearchPath();
  EXPECT_TRUE(searchPaths.addInputFileDirectoryToSearchPath());
  EXPECT_TRUE(searchPaths.isAddInputFileDirectoryToSearchPathDefaulted());

  EXPECT_TRUE(searchPaths.setAddEpinEnvironmentVariableToSearchPath(false));
  EXPECT_FALSE(searchPaths.addEpinEnvironmentVariableToSearchPath());
  EXPECT_FALSE(searchPaths.isAddEpinEnvironmentVariableToSearchPathDefaulted());
  searchPaths.resetAddEpinEnvironmentVariableToSearchPath();
  EXPECT_TRUE(searchPaths.addEpinEnvironmentVariableToSearchPath());
  EXPECT_TRUE(searchPaths.isAddEpinEnvironmentVariableToSearchPathDefaulted());
}
