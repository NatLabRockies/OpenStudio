/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ResourceObject/PythonPluginInstance.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, PythonPluginInstance_DefaultConstructor) {
  Model model;
  PythonPluginInstance pythonPluginInstance(model);
  EXPECT_EQ(PythonPluginInstance::iddObjectType(), pythonPluginInstance.iddObject().type());
  EXPECT_FALSE(pythonPluginInstance.nameString().empty());
}

TEST_F(EPModelFixture, PythonPluginInstance_ScalarAccessors_RoundTrip) {
  Model model;
  PythonPluginInstance pythonPluginInstance(model);

  EXPECT_TRUE(pythonPluginInstance.setPluginClassName("MyPlugin"));
  EXPECT_EQ("MyPlugin", pythonPluginInstance.pluginClassName());

  EXPECT_TRUE(pythonPluginInstance.setPythonModuleName("plugin_module"));
  EXPECT_EQ("plugin_module", pythonPluginInstance.pythonModuleName());

  EXPECT_TRUE(pythonPluginInstance.setRunDuringWarmupDays(true));
  EXPECT_TRUE(pythonPluginInstance.runDuringWarmupDays());
  EXPECT_FALSE(pythonPluginInstance.isRunDuringWarmupDaysDefaulted());

  pythonPluginInstance.resetRunDuringWarmupDays();
  EXPECT_FALSE(pythonPluginInstance.runDuringWarmupDays());
  EXPECT_TRUE(pythonPluginInstance.isRunDuringWarmupDaysDefaulted());
}
