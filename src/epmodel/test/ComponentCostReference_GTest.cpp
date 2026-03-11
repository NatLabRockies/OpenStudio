/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/ComponentCostReference.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ComponentCostReference_DefaultConstructor) {
  Model model;
  ComponentCostReference componentCostReference(model);
  EXPECT_EQ(ComponentCostReference::iddObjectType(), componentCostReference.iddObject().type());
}

TEST_F(EPModelFixture, ComponentCostReference_ScalarAccessors_RoundTrip) {
  Model model;
  ComponentCostReference componentCostReference(model);

  EXPECT_FALSE(componentCostReference.referenceBuildingLineItemCosts());
  EXPECT_FALSE(componentCostReference.referenceBuildingMiscellaneousCostperConditionedArea());
  EXPECT_FALSE(componentCostReference.referenceBuildingDesignandEngineeringFees());
  EXPECT_FALSE(componentCostReference.referenceBuildingContractorFee());
  EXPECT_FALSE(componentCostReference.referenceBuildingContingency());
  EXPECT_FALSE(componentCostReference.referenceBuildingPermitsBondingandInsurance());
  EXPECT_FALSE(componentCostReference.referenceBuildingCommissioningFee());
  EXPECT_FALSE(componentCostReference.referenceBuildingRegionalAdjustmentFactor());

  EXPECT_TRUE(componentCostReference.setReferenceBuildingLineItemCosts(45000.0));
  ASSERT_TRUE(componentCostReference.referenceBuildingLineItemCosts());
  EXPECT_DOUBLE_EQ(45000.0, componentCostReference.referenceBuildingLineItemCosts().get());

  EXPECT_TRUE(componentCostReference.setReferenceBuildingMiscellaneousCostperConditionedArea(17.5));
  ASSERT_TRUE(componentCostReference.referenceBuildingMiscellaneousCostperConditionedArea());
  EXPECT_DOUBLE_EQ(17.5, componentCostReference.referenceBuildingMiscellaneousCostperConditionedArea().get());

  EXPECT_TRUE(componentCostReference.setReferenceBuildingDesignandEngineeringFees(0.08));
  ASSERT_TRUE(componentCostReference.referenceBuildingDesignandEngineeringFees());
  EXPECT_DOUBLE_EQ(0.08, componentCostReference.referenceBuildingDesignandEngineeringFees().get());

  EXPECT_TRUE(componentCostReference.setReferenceBuildingContractorFee(0.10));
  ASSERT_TRUE(componentCostReference.referenceBuildingContractorFee());
  EXPECT_DOUBLE_EQ(0.10, componentCostReference.referenceBuildingContractorFee().get());

  EXPECT_TRUE(componentCostReference.setReferenceBuildingContingency(0.15));
  ASSERT_TRUE(componentCostReference.referenceBuildingContingency());
  EXPECT_DOUBLE_EQ(0.15, componentCostReference.referenceBuildingContingency().get());

  EXPECT_TRUE(componentCostReference.setReferenceBuildingPermitsBondingandInsurance(0.03));
  ASSERT_TRUE(componentCostReference.referenceBuildingPermitsBondingandInsurance());
  EXPECT_DOUBLE_EQ(0.03, componentCostReference.referenceBuildingPermitsBondingandInsurance().get());

  EXPECT_TRUE(componentCostReference.setReferenceBuildingCommissioningFee(0.02));
  ASSERT_TRUE(componentCostReference.referenceBuildingCommissioningFee());
  EXPECT_DOUBLE_EQ(0.02, componentCostReference.referenceBuildingCommissioningFee().get());

  EXPECT_TRUE(componentCostReference.setReferenceBuildingRegionalAdjustmentFactor(1.12));
  ASSERT_TRUE(componentCostReference.referenceBuildingRegionalAdjustmentFactor());
  EXPECT_DOUBLE_EQ(1.12, componentCostReference.referenceBuildingRegionalAdjustmentFactor().get());

  componentCostReference.resetReferenceBuildingLineItemCosts();
  componentCostReference.resetReferenceBuildingMiscellaneousCostperConditionedArea();
  componentCostReference.resetReferenceBuildingDesignandEngineeringFees();
  componentCostReference.resetReferenceBuildingContractorFee();
  componentCostReference.resetReferenceBuildingContingency();
  componentCostReference.resetReferenceBuildingPermitsBondingandInsurance();
  componentCostReference.resetReferenceBuildingCommissioningFee();
  componentCostReference.resetReferenceBuildingRegionalAdjustmentFactor();

  EXPECT_FALSE(componentCostReference.referenceBuildingLineItemCosts());
  EXPECT_FALSE(componentCostReference.referenceBuildingMiscellaneousCostperConditionedArea());
  EXPECT_FALSE(componentCostReference.referenceBuildingDesignandEngineeringFees());
  EXPECT_FALSE(componentCostReference.referenceBuildingContractorFee());
  EXPECT_FALSE(componentCostReference.referenceBuildingContingency());
  EXPECT_FALSE(componentCostReference.referenceBuildingPermitsBondingandInsurance());
  EXPECT_FALSE(componentCostReference.referenceBuildingCommissioningFee());
  EXPECT_FALSE(componentCostReference.referenceBuildingRegionalAdjustmentFactor());
}
