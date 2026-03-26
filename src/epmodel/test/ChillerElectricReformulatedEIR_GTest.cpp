/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../WaterToWaterComponent/ChillerElectricReformulatedEIR.hpp"

#include <limits>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ChillerElectricReformulatedEIR_DefaultConstructor) {
  Model model;
  ChillerElectricReformulatedEIR chiller(model);
  EXPECT_EQ(ChillerElectricReformulatedEIR::iddObjectType(), chiller.iddObject().type());
  EXPECT_FALSE(chiller.nameString().empty());
  EXPECT_NE(std::numeric_limits<unsigned>::max(), chiller.supplyInletPort());
  EXPECT_NE(std::numeric_limits<unsigned>::max(), chiller.demandInletPort());
  EXPECT_NE(std::numeric_limits<unsigned>::max(), chiller.tertiaryInletPort());
}

TEST_F(EPModelFixture, ChillerElectricReformulatedEIR_ScalarAccessors_RoundTrip) {
  Model model;
  ChillerElectricReformulatedEIR chiller(model);

  EXPECT_TRUE(chiller.setReferenceCapacity(700000.0));
  ASSERT_TRUE(chiller.referenceCapacity());
  EXPECT_DOUBLE_EQ(700000.0, *chiller.referenceCapacity());
  EXPECT_FALSE(chiller.isReferenceCapacityAutosized());
  chiller.autosizeReferenceCapacity();
  EXPECT_TRUE(chiller.isReferenceCapacityAutosized());

  EXPECT_TRUE(chiller.setReferenceCOP(4.0));
  EXPECT_DOUBLE_EQ(4.0, chiller.referenceCOP());

  EXPECT_TRUE(chiller.setReferenceLeavingCondenserWaterTemperature(35.0));
  EXPECT_DOUBLE_EQ(35.0, chiller.referenceLeavingCondenserWaterTemperature());
  chiller.resetReferenceLeavingCondenserWaterTemperature();
  EXPECT_TRUE(chiller.isReferenceLeavingCondenserWaterTemperatureDefaulted());

  EXPECT_TRUE(chiller.setReferenceCondenserWaterFlowRate(0.03));
  ASSERT_TRUE(chiller.referenceCondenserWaterFlowRate());
  EXPECT_DOUBLE_EQ(0.03, *chiller.referenceCondenserWaterFlowRate());
  chiller.autosizeReferenceCondenserWaterFlowRate();
  EXPECT_TRUE(chiller.isReferenceCondenserWaterFlowRateAutosized());

  EXPECT_TRUE(chiller.setElectricInputToCoolingOutputRatioFunctionOfPLRType("Lift"));
  EXPECT_EQ("Lift", chiller.electricInputToCoolingOutputRatioFunctionOfPLRType());
  chiller.resetElectricInputToCoolingOutputRatioFunctionOfPLRType();

  EXPECT_TRUE(chiller.setChillerFlowMode("VariableFlow"));
  EXPECT_EQ("LeavingSetpointModulated", chiller.chillerFlowMode());
  chiller.resetChillerFlowMode();
  EXPECT_TRUE(chiller.isChillerFlowModeDefaulted());

  EXPECT_TRUE(chiller.setDesignHeatRecoveryWaterFlowRate(0.01));
  ASSERT_TRUE(chiller.designHeatRecoveryWaterFlowRate());
  EXPECT_DOUBLE_EQ(0.01, *chiller.designHeatRecoveryWaterFlowRate());
  chiller.autosizeDesignHeatRecoveryWaterFlowRate();
  EXPECT_TRUE(chiller.isDesignHeatRecoveryWaterFlowRateAutosized());

  EXPECT_TRUE(chiller.setCondenserFlowControl("ConstantFlow"));
  EXPECT_EQ("ConstantFlow", chiller.condenserFlowControl());

  EXPECT_TRUE(chiller.setCondenserMinimumFlowFraction(0.2));
  EXPECT_DOUBLE_EQ(0.2, chiller.condenserMinimumFlowFraction());

  EXPECT_TRUE(chiller.setThermosiphonMinimumTemperatureDifference(0.5));
  EXPECT_DOUBLE_EQ(0.5, chiller.thermosiphonMinimumTemperatureDifference());
}
