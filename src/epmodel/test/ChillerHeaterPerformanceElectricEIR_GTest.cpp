/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ParentObject/ChillerHeaterPerformanceElectricEIR.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ChillerHeaterPerformanceElectricEIR_DefaultConstructor) {
  Model model;
  ChillerHeaterPerformanceElectricEIR chiller(model);
  EXPECT_EQ(ChillerHeaterPerformanceElectricEIR::iddObjectType(), chiller.iddObject().type());
  EXPECT_FALSE(chiller.nameString().empty());
}

TEST_F(EPModelFixture, ChillerHeaterPerformanceElectricEIR_ScalarAccessors_RoundTrip) {
  Model model;
  ChillerHeaterPerformanceElectricEIR chiller(model);

  EXPECT_TRUE(chiller.setReferenceCoolingModeEvaporatorCapacity(10000.0));
  ASSERT_TRUE(chiller.referenceCoolingModeEvaporatorCapacity());
  EXPECT_DOUBLE_EQ(10000.0, *chiller.referenceCoolingModeEvaporatorCapacity());
  EXPECT_FALSE(chiller.isReferenceCoolingModeEvaporatorCapacityAutosized());
  chiller.autosizeReferenceCoolingModeEvaporatorCapacity();
  EXPECT_TRUE(chiller.isReferenceCoolingModeEvaporatorCapacityAutosized());

  const auto chilledWaterFlowModeTypeValues = ChillerHeaterPerformanceElectricEIR::chilledWaterFlowModeTypeValues();
  ASSERT_FALSE(chilledWaterFlowModeTypeValues.empty());
  EXPECT_TRUE(chiller.setChilledWaterFlowModeType(chilledWaterFlowModeTypeValues.front()));
  EXPECT_EQ(chilledWaterFlowModeTypeValues.front(), chiller.chilledWaterFlowModeType());

  EXPECT_TRUE(chiller.setDesignChilledWaterFlowRate(0.01));
  ASSERT_TRUE(chiller.designChilledWaterFlowRate());
  EXPECT_DOUBLE_EQ(0.01, *chiller.designChilledWaterFlowRate());
  EXPECT_FALSE(chiller.isDesignChilledWaterFlowRateAutosized());
  chiller.autosizeDesignChilledWaterFlowRate();
  EXPECT_TRUE(chiller.isDesignChilledWaterFlowRateAutosized());
  chiller.resetDesignChilledWaterFlowRate();
  EXPECT_FALSE(chiller.designChilledWaterFlowRate());

  EXPECT_TRUE(chiller.setDesignCondenserWaterFlowRate(0.015));
  ASSERT_TRUE(chiller.designCondenserWaterFlowRate());
  EXPECT_DOUBLE_EQ(0.015, *chiller.designCondenserWaterFlowRate());
  chiller.autosizeDesignCondenserWaterFlowRate();
  EXPECT_TRUE(chiller.isDesignCondenserWaterFlowRateAutosized());

  const auto condenserTypeValues = ChillerHeaterPerformanceElectricEIR::condenserTypeValues();
  ASSERT_FALSE(condenserTypeValues.empty());
  EXPECT_TRUE(chiller.setCondenserType(condenserTypeValues.front()));
  EXPECT_EQ(condenserTypeValues.front(), chiller.condenserType());

  const auto coolingModeTempCurveValues =
    ChillerHeaterPerformanceElectricEIR::coolingModeTemperatureCurveCondenserWaterIndependentVariableValues();
  ASSERT_FALSE(coolingModeTempCurveValues.empty());
  EXPECT_TRUE(chiller.setCoolingModeTemperatureCurveCondenserWaterIndependentVariable(coolingModeTempCurveValues.front()));
  EXPECT_EQ(coolingModeTempCurveValues.front(), chiller.coolingModeTemperatureCurveCondenserWaterIndependentVariable());

  const auto heatingModeTempCurveValues =
    ChillerHeaterPerformanceElectricEIR::heatingModeTemperatureCurveCondenserWaterIndependentVariableValues();
  ASSERT_FALSE(heatingModeTempCurveValues.empty());
  EXPECT_TRUE(chiller.setHeatingModeTemperatureCurveCondenserWaterIndependentVariable(heatingModeTempCurveValues.front()));
  EXPECT_EQ(heatingModeTempCurveValues.front(), chiller.heatingModeTemperatureCurveCondenserWaterIndependentVariable());

  EXPECT_TRUE(chiller.setReferenceCoolingModeCOP(3.2));
  EXPECT_DOUBLE_EQ(3.2, chiller.referenceCoolingModeCOP());

  EXPECT_TRUE(chiller.setSizingFactor(1.1));
  EXPECT_DOUBLE_EQ(1.1, chiller.sizingFactor());
}
