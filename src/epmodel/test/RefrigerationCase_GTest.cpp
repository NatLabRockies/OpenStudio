/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ParentObject/RefrigerationCase.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, RefrigerationCase_DefaultConstructor) {
  Model model;
  RefrigerationCase refrigerationCase(model);
  EXPECT_EQ(RefrigerationCase::iddObjectType(), openstudio::IddObjectType::Refrigeration_Case);
}

TEST_F(EPModelFixture, RefrigerationCase_ScalarAccessors_RoundTrip) {
  Model model;
  RefrigerationCase refrigerationCase(model);

  EXPECT_TRUE(refrigerationCase.setRatedAmbientTemperature(25.0));
  EXPECT_DOUBLE_EQ(25.0, refrigerationCase.ratedAmbientTemperature());
  EXPECT_FALSE(refrigerationCase.isRatedAmbientTemperatureDefaulted());
  refrigerationCase.resetRatedAmbientTemperature();
  EXPECT_TRUE(refrigerationCase.isRatedAmbientTemperatureDefaulted());

  const auto defrostTypes = RefrigerationCase::caseDefrostTypeValues();
  ASSERT_FALSE(defrostTypes.empty());
  EXPECT_TRUE(refrigerationCase.setCaseDefrostType(defrostTypes.front()));
  EXPECT_EQ(defrostTypes.front(), refrigerationCase.caseDefrostType());
  refrigerationCase.resetCaseDefrostType();
  EXPECT_TRUE(refrigerationCase.isCaseDefrostTypeDefaulted());

  const auto latentValues = RefrigerationCase::latentCaseCreditCurveTypeValues();
  ASSERT_FALSE(latentValues.empty());
  EXPECT_TRUE(refrigerationCase.setLatentCaseCreditCurveType(latentValues.front()));
  EXPECT_EQ(latentValues.front(), refrigerationCase.latentCaseCreditCurveType());

  EXPECT_TRUE(refrigerationCase.setInstalledCaseLightingPowerperUnitLength(42.0));
  ASSERT_TRUE(refrigerationCase.installedCaseLightingPowerperUnitLength());
  EXPECT_DOUBLE_EQ(42.0, refrigerationCase.installedCaseLightingPowerperUnitLength().get());
  refrigerationCase.resetInstalledCaseLightingPowerperUnitLength();
  EXPECT_FALSE(refrigerationCase.installedCaseLightingPowerperUnitLength());

  EXPECT_TRUE(refrigerationCase.setDesignEvaporatorTemperatureorBrineInletTemperature(-5.0));
  ASSERT_TRUE(refrigerationCase.designEvaporatorTemperatureorBrineInletTemperature());
  EXPECT_DOUBLE_EQ(-5.0, refrigerationCase.designEvaporatorTemperatureorBrineInletTemperature().get());
  refrigerationCase.resetDesignEvaporatorTemperatureorBrineInletTemperature();
  EXPECT_FALSE(refrigerationCase.designEvaporatorTemperatureorBrineInletTemperature());

  EXPECT_TRUE(refrigerationCase.setAverageRefrigerantChargeInventory(1.25));
  EXPECT_DOUBLE_EQ(1.25, refrigerationCase.averageRefrigerantChargeInventory());
}
