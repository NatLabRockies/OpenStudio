/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/PerformancePrecisionTradeoffs.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, PerformancePrecisionTradeoffs_DefaultConstructor) {
  Model model;
  PerformancePrecisionTradeoffs object(model);

  EXPECT_EQ(PerformancePrecisionTradeoffs::iddObjectType(), object.iddObject().type());

  EXPECT_TRUE(object.isUseCoilDirectSolutionsDefaulted());
  EXPECT_FALSE(object.useCoilDirectSolutions());

  EXPECT_TRUE(object.isZoneRadiantExchangeAlgorithmDefaulted());
  EXPECT_EQ("ScriptF", object.zoneRadiantExchangeAlgorithm());

  EXPECT_TRUE(object.isOverrideModeDefaulted());
  EXPECT_EQ("Normal", object.overrideMode());

  EXPECT_TRUE(object.isMaxZoneTempDiffDefaulted());
  EXPECT_DOUBLE_EQ(0.3, object.maxZoneTempDiff());

  EXPECT_TRUE(object.isMaxAllowedDelTempDefaulted());
  EXPECT_DOUBLE_EQ(0.002, object.maxAllowedDelTemp());

  EXPECT_TRUE(object.isUseRepresentativeSurfacesforCalculationsDefaulted());
  EXPECT_FALSE(object.useRepresentativeSurfacesforCalculations());
}

TEST_F(EPModelFixture, PerformancePrecisionTradeoffs_ScalarAccessors_RoundTrip) {
  Model model;
  PerformancePrecisionTradeoffs object(model);

  EXPECT_TRUE(object.setUseCoilDirectSolutions(true));
  EXPECT_FALSE(object.isUseCoilDirectSolutionsDefaulted());
  EXPECT_TRUE(object.useCoilDirectSolutions());
  object.resetUseCoilDirectSolutions();
  EXPECT_TRUE(object.isUseCoilDirectSolutionsDefaulted());

  EXPECT_TRUE(object.setZoneRadiantExchangeAlgorithm("CarrollMRT"));
  EXPECT_EQ("CarrollMRT", object.zoneRadiantExchangeAlgorithm());
  EXPECT_FALSE(object.isZoneRadiantExchangeAlgorithmDefaulted());
  EXPECT_FALSE(object.setZoneRadiantExchangeAlgorithm("BADENUM"));
  object.resetZoneRadiantExchangeAlgorithm();
  EXPECT_TRUE(object.isZoneRadiantExchangeAlgorithmDefaulted());

  EXPECT_TRUE(object.setOverrideMode("Advanced"));
  EXPECT_EQ("Advanced", object.overrideMode());
  EXPECT_FALSE(object.isOverrideModeDefaulted());
  EXPECT_FALSE(object.setOverrideMode("BADENUM"));
  object.resetOverrideMode();
  EXPECT_TRUE(object.isOverrideModeDefaulted());

  EXPECT_TRUE(object.setMaxZoneTempDiff(0.65));
  EXPECT_DOUBLE_EQ(0.65, object.maxZoneTempDiff());
  EXPECT_FALSE(object.isMaxZoneTempDiffDefaulted());
  EXPECT_FALSE(object.setMaxZoneTempDiff(30.0));
  object.resetMaxZoneTempDiff();
  EXPECT_TRUE(object.isMaxZoneTempDiffDefaulted());

  EXPECT_TRUE(object.setMaxAllowedDelTemp(0.05));
  EXPECT_DOUBLE_EQ(0.05, object.maxAllowedDelTemp());
  EXPECT_FALSE(object.isMaxAllowedDelTempDefaulted());
  EXPECT_FALSE(object.setMaxAllowedDelTemp(1.0));
  object.resetMaxAllowedDelTemp();
  EXPECT_TRUE(object.isMaxAllowedDelTempDefaulted());

  EXPECT_TRUE(object.setUseRepresentativeSurfacesforCalculations(true));
  EXPECT_FALSE(object.isUseRepresentativeSurfacesforCalculationsDefaulted());
  EXPECT_TRUE(object.useRepresentativeSurfacesforCalculations());
  object.resetUseRepresentativeSurfacesforCalculations();
  EXPECT_TRUE(object.isUseRepresentativeSurfacesforCalculationsDefaulted());

  const auto zoneAlgoValues = PerformancePrecisionTradeoffs::zoneRadiantExchangeAlgorithmValues();
  EXPECT_GE(zoneAlgoValues.size(), 1u);

  const auto validZoneAlgoValues = PerformancePrecisionTradeoffs::validZoneRadiantExchangeAlgorithmValues();
  EXPECT_EQ(zoneAlgoValues, validZoneAlgoValues);

  const auto overrideValues = PerformancePrecisionTradeoffs::overrideModeValues();
  EXPECT_GE(overrideValues.size(), 1u);

  const auto validOverrideValues = PerformancePrecisionTradeoffs::validOverrideModeValues();
  EXPECT_EQ(overrideValues, validOverrideValues);
}
