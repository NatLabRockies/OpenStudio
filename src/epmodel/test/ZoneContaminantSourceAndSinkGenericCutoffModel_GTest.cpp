/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/ZoneContaminantSourceAndSinkGenericCutoffModel.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ZoneContaminantSourceAndSinkGenericCutoffModel_DefaultConstructor) {
  Model model;
  ZoneContaminantSourceAndSinkGenericCutoffModel obj(model);
  EXPECT_EQ(ZoneContaminantSourceAndSinkGenericCutoffModel::iddObjectType(), obj.iddObject().type());
}

TEST_F(EPModelFixture, ZoneContaminantSourceAndSinkGenericCutoffModel_ScalarAccessors_RoundTrip) {
  Model model;
  ZoneContaminantSourceAndSinkGenericCutoffModel obj(model);

  // Design Generation Rate Coefficient: optional (minimum 0.0 inclusive)
  EXPECT_FALSE(obj.designGenerationRateCoefficient());
  EXPECT_TRUE(obj.setDesignGenerationRateCoefficient(0.5));
  ASSERT_TRUE(obj.designGenerationRateCoefficient());
  EXPECT_DOUBLE_EQ(0.5, obj.designGenerationRateCoefficient().get());
  EXPECT_TRUE(obj.setDesignGenerationRateCoefficient(0.0));
  ASSERT_TRUE(obj.designGenerationRateCoefficient());
  EXPECT_DOUBLE_EQ(0.0, obj.designGenerationRateCoefficient().get());
  EXPECT_FALSE(obj.setDesignGenerationRateCoefficient(-0.1));
  obj.resetDesignGenerationRateCoefficient();
  EXPECT_FALSE(obj.designGenerationRateCoefficient());

  // Cutoff Generic Contaminant at which Emission Ceases: optional (minimum> 0.0 exclusive)
  EXPECT_FALSE(obj.cutoffGenericContaminantAtWhichEmissionCeases());
  EXPECT_TRUE(obj.setCutoffGenericContaminantAtWhichEmissionCeases(12.0));
  ASSERT_TRUE(obj.cutoffGenericContaminantAtWhichEmissionCeases());
  EXPECT_DOUBLE_EQ(12.0, obj.cutoffGenericContaminantAtWhichEmissionCeases().get());
  EXPECT_FALSE(obj.setCutoffGenericContaminantAtWhichEmissionCeases(0.0));
  EXPECT_FALSE(obj.setCutoffGenericContaminantAtWhichEmissionCeases(-1.0));
  EXPECT_TRUE(obj.setCutoffGenericContaminantAtWhichEmissionCeases(0.001));
  ASSERT_TRUE(obj.cutoffGenericContaminantAtWhichEmissionCeases());
  EXPECT_DOUBLE_EQ(0.001, obj.cutoffGenericContaminantAtWhichEmissionCeases().get());
  obj.resetCutoffGenericContaminantAtWhichEmissionCeases();
  EXPECT_FALSE(obj.cutoffGenericContaminantAtWhichEmissionCeases());
}
