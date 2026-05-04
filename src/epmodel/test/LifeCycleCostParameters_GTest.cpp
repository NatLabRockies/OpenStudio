/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ParentObject/LifeCycleCostParameters.hpp"
#include "../ParentObject/LifeCycleCostParameters_Impl.hpp"

#include <utilities/time/Date.hpp>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, LifeCycleCostParameters_DefaultConstructor) {
  Model model;
  auto lifeCycleCostParameters = model.getUniqueModelObject<LifeCycleCostParameters>();
  EXPECT_EQ(LifeCycleCostParameters::iddObjectType(), lifeCycleCostParameters.iddObject().type());
}

TEST_F(EPModelFixture, LifeCycleCostParameters_ScalarAccessors_RoundTrip) {
  Model model;
  auto lcc = model.getUniqueModelObject<LifeCycleCostParameters>();

  EXPECT_TRUE(lcc.setDiscountingConvention("MidYear"));
  EXPECT_EQ("MidYear", lcc.discountingConvention());

  EXPECT_TRUE(lcc.setInflationApproach("CurrentDollar"));
  EXPECT_TRUE(lcc.isInflationApproachDefaulted() == false);
  EXPECT_FALSE(lcc.realDiscountRate());

  EXPECT_TRUE(lcc.setNominalDiscountRate(0.05));
  ASSERT_TRUE(lcc.nominalDiscountRate());
  EXPECT_NEAR(0.05, lcc.nominalDiscountRate().get(), 1e-9);

  EXPECT_TRUE(lcc.setInflation(0.02));
  ASSERT_TRUE(lcc.inflation());
  EXPECT_NEAR(0.02, lcc.inflation().get(), 1e-9);

  EXPECT_TRUE(lcc.setBaseDateMonth(openstudio::MonthOfYear("February")));
  EXPECT_EQ("February", lcc.baseDateMonth().valueDescription());

  EXPECT_TRUE(lcc.setBaseDateYear(2026));
  EXPECT_EQ(2026, lcc.baseDateYear());

  EXPECT_TRUE(lcc.setServiceDateMonth(openstudio::MonthOfYear("March")));
  EXPECT_EQ("March", lcc.serviceDateMonth().valueDescription());

  EXPECT_TRUE(lcc.setServiceDateYear(2027));
  EXPECT_EQ(2027, lcc.serviceDateYear());

  EXPECT_TRUE(lcc.setLengthOfStudyPeriodInYears(30));
  EXPECT_EQ(30, lcc.lengthOfStudyPeriodInYears());

  EXPECT_TRUE(lcc.setTaxRate(0.35));
  ASSERT_TRUE(lcc.taxRate());
  EXPECT_NEAR(0.35, lcc.taxRate().get(), 1e-9);
  lcc.resetTaxRate();
  EXPECT_FALSE(lcc.taxRate());

  EXPECT_TRUE(lcc.setDepreciationMethod("None"));
  EXPECT_EQ("None", lcc.depreciationMethod());
}
