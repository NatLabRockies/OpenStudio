/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/PythonPluginTrendVariable.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, PythonPluginTrendVariable_DefaultConstructor) {
  Model model;
  PythonPluginTrendVariable trendVariable(model);

  EXPECT_EQ(PythonPluginTrendVariable::iddObjectType(), trendVariable.iddObject().type());
  EXPECT_EQ(4, trendVariable.numberofTimestepstobeLogged());
}

TEST_F(EPModelFixture, PythonPluginTrendVariable_ScalarAccessors_RoundTrip) {
  Model model;
  PythonPluginTrendVariable trendVariable(model);

  EXPECT_TRUE(trendVariable.setNumberofTimestepstobeLogged(9));
  EXPECT_EQ(9, trendVariable.numberofTimestepstobeLogged());
}
