/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ParentObject/ComponentCostAdjustments.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ComponentCostAdjustments_DefaultConstructor) {
  Model model;
  ComponentCostAdjustments componentCostAdjustments(model);
  EXPECT_EQ(ComponentCostAdjustments::iddObjectType(), componentCostAdjustments.iddObject().type());
}

TEST_F(EPModelFixture, ComponentCostAdjustments_ScalarAccessors_RoundTrip) {
  Model model;
  ComponentCostAdjustments componentCostAdjustments(model);

  EXPECT_FALSE(componentCostAdjustments.miscellaneousCostperConditionedArea());
  EXPECT_FALSE(componentCostAdjustments.designandEngineeringFees());
  EXPECT_FALSE(componentCostAdjustments.contractorFee());
  EXPECT_FALSE(componentCostAdjustments.contingency());
  EXPECT_FALSE(componentCostAdjustments.permitsBondingandInsurance());
  EXPECT_FALSE(componentCostAdjustments.commissioningFee());
  EXPECT_FALSE(componentCostAdjustments.regionalAdjustmentFactor());

  EXPECT_TRUE(componentCostAdjustments.setMiscellaneousCostperConditionedArea(12.5));
  ASSERT_TRUE(componentCostAdjustments.miscellaneousCostperConditionedArea());
  EXPECT_DOUBLE_EQ(12.5, componentCostAdjustments.miscellaneousCostperConditionedArea().get());

  EXPECT_TRUE(componentCostAdjustments.setDesignandEngineeringFees(0.08));
  ASSERT_TRUE(componentCostAdjustments.designandEngineeringFees());
  EXPECT_DOUBLE_EQ(0.08, componentCostAdjustments.designandEngineeringFees().get());

  EXPECT_TRUE(componentCostAdjustments.setContractorFee(0.10));
  ASSERT_TRUE(componentCostAdjustments.contractorFee());
  EXPECT_DOUBLE_EQ(0.10, componentCostAdjustments.contractorFee().get());

  EXPECT_TRUE(componentCostAdjustments.setContingency(0.15));
  ASSERT_TRUE(componentCostAdjustments.contingency());
  EXPECT_DOUBLE_EQ(0.15, componentCostAdjustments.contingency().get());

  EXPECT_TRUE(componentCostAdjustments.setPermitsBondingandInsurance(0.03));
  ASSERT_TRUE(componentCostAdjustments.permitsBondingandInsurance());
  EXPECT_DOUBLE_EQ(0.03, componentCostAdjustments.permitsBondingandInsurance().get());

  EXPECT_TRUE(componentCostAdjustments.setCommissioningFee(0.02));
  ASSERT_TRUE(componentCostAdjustments.commissioningFee());
  EXPECT_DOUBLE_EQ(0.02, componentCostAdjustments.commissioningFee().get());

  EXPECT_TRUE(componentCostAdjustments.setRegionalAdjustmentFactor(1.12));
  ASSERT_TRUE(componentCostAdjustments.regionalAdjustmentFactor());
  EXPECT_DOUBLE_EQ(1.12, componentCostAdjustments.regionalAdjustmentFactor().get());

  componentCostAdjustments.resetMiscellaneousCostperConditionedArea();
  componentCostAdjustments.resetDesignandEngineeringFees();
  componentCostAdjustments.resetContractorFee();
  componentCostAdjustments.resetContingency();
  componentCostAdjustments.resetPermitsBondingandInsurance();
  componentCostAdjustments.resetCommissioningFee();
  componentCostAdjustments.resetRegionalAdjustmentFactor();

  EXPECT_FALSE(componentCostAdjustments.miscellaneousCostperConditionedArea());
  EXPECT_FALSE(componentCostAdjustments.designandEngineeringFees());
  EXPECT_FALSE(componentCostAdjustments.contractorFee());
  EXPECT_FALSE(componentCostAdjustments.contingency());
  EXPECT_FALSE(componentCostAdjustments.permitsBondingandInsurance());
  EXPECT_FALSE(componentCostAdjustments.commissioningFee());
  EXPECT_FALSE(componentCostAdjustments.regionalAdjustmentFactor());
}
