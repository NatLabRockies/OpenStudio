/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Generator/GeneratorPhotovoltaic.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, GeneratorPhotovoltaic_DefaultConstructor) {
  Model model;
  GeneratorPhotovoltaic generator(model);
  EXPECT_EQ(GeneratorPhotovoltaic::iddObjectType(), generator.iddObject().type());
}

TEST_F(EPModelFixture, GeneratorPhotovoltaic_ScalarAccessors_RoundTrip) {
  Model model;
  GeneratorPhotovoltaic generator(model);

  const auto modes = GeneratorPhotovoltaic::heatTransferIntegrationModeValues();
  ASSERT_FALSE(modes.empty());

  EXPECT_TRUE(generator.isHeatTransferIntegrationModeDefaulted());
  EXPECT_EQ("Decoupled", generator.heatTransferIntegrationMode());
  EXPECT_TRUE(generator.setHeatTransferIntegrationMode("IntegratedSurfaceOutsideFace"));
  EXPECT_EQ("IntegratedSurfaceOutsideFace", generator.heatTransferIntegrationMode());
  EXPECT_FALSE(generator.isHeatTransferIntegrationModeDefaulted());
  generator.resetHeatTransferIntegrationMode();
  EXPECT_TRUE(generator.isHeatTransferIntegrationModeDefaulted());
  EXPECT_EQ("Decoupled", generator.heatTransferIntegrationMode());

  EXPECT_TRUE(generator.isNumberOfModulesInParallelDefaulted());
  EXPECT_DOUBLE_EQ(1.0, generator.numberOfModulesInParallel());
  EXPECT_TRUE(generator.setNumberOfModulesInParallel(2.0));
  EXPECT_DOUBLE_EQ(2.0, generator.numberOfModulesInParallel());
  EXPECT_FALSE(generator.isNumberOfModulesInParallelDefaulted());
  generator.resetNumberOfModulesInParallel();
  EXPECT_TRUE(generator.isNumberOfModulesInParallelDefaulted());
  EXPECT_DOUBLE_EQ(1.0, generator.numberOfModulesInParallel());

  EXPECT_TRUE(generator.isNumberOfModulesInSeriesDefaulted());
  EXPECT_DOUBLE_EQ(1.0, generator.numberOfModulesInSeries());
  EXPECT_TRUE(generator.setNumberOfModulesInSeries(3.0));
  EXPECT_DOUBLE_EQ(3.0, generator.numberOfModulesInSeries());
  EXPECT_FALSE(generator.isNumberOfModulesInSeriesDefaulted());
  generator.resetNumberOfModulesInSeries();
  EXPECT_TRUE(generator.isNumberOfModulesInSeriesDefaulted());
  EXPECT_DOUBLE_EQ(1.0, generator.numberOfModulesInSeries());
}
