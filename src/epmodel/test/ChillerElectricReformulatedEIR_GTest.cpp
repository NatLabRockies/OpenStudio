/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Curve/CurveBicubic.hpp"
#include "../Curve/CurveBiquadratic.hpp"
#include "../Curve/CurveLinear.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../StraightComponent/Node.hpp"
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

  EXPECT_EQ(CurveBiquadratic::iddObjectType(), chiller.coolingCapacityFunctionOfTemperature().iddObject().type());
  EXPECT_EQ(CurveBiquadratic::iddObjectType(), chiller.electricInputToCoolingOutputRatioFunctionOfTemperature().iddObject().type());
  EXPECT_EQ(CurveBicubic::iddObjectType(), chiller.electricInputToCoolingOutputRatioFunctionOfPLR().iddObject().type());

  EXPECT_DOUBLE_EQ(3.99, chiller.referenceCOP());
  EXPECT_TRUE(chiller.isReferenceCapacityAutosized());
  EXPECT_TRUE(chiller.isReferenceChilledWaterFlowRateAutosized());
  EXPECT_TRUE(chiller.isDesignHeatRecoveryWaterFlowRateAutosized());
  EXPECT_DOUBLE_EQ(1.0, chiller.condenserHeatRecoveryRelativeCapacityFraction());
  EXPECT_FALSE(chiller.heatRecoveryInletHighTemperatureLimitSchedule());
  EXPECT_FALSE(chiller.heatRecoveryLeavingTemperatureSetpointNode());
  EXPECT_EQ("General", chiller.endUseSubcategory());
  EXPECT_EQ("ConstantFlow", chiller.condenserFlowControl());
  EXPECT_DOUBLE_EQ(0.2, chiller.condenserMinimumFlowFraction());
  EXPECT_DOUBLE_EQ(0.0, chiller.thermosiphonMinimumTemperatureDifference());
  EXPECT_FALSE(chiller.condenserLoopFlowRateFractionFunctionofLoopPartLoadRatioCurve());
  EXPECT_FALSE(chiller.temperatureDifferenceAcrossCondenserSchedule());
  EXPECT_FALSE(chiller.thermosiphonCapacityFractionCurve());
  EXPECT_FALSE(chiller.chilledWaterLoop());
  EXPECT_FALSE(chiller.condenserWaterLoop());
  EXPECT_FALSE(chiller.heatRecoveryLoop());
}

TEST_F(EPModelFixture, ChillerElectricReformulatedEIR_CurveConstructorAndRelationships) {
  Model model;
  CurveBiquadratic CCFofT(model);
  CurveBiquadratic EIRToCorfOfT(model);
  CurveBicubic EIRToCorfOfPLR(model);
  CurveLinear condenserLoopPLR(model);
  CurveLinear thermosiphonCurve(model);
  ScheduleConstant heatRecoveryLimit(model);
  ScheduleConstant condenserDeltaT(model);
  Node setpointNode(model);

  ChillerElectricReformulatedEIR chiller(model, CCFofT, EIRToCorfOfT, EIRToCorfOfPLR);

  EXPECT_EQ(CCFofT.handle(), chiller.coolingCapacityFunctionOfTemperature().handle());
  EXPECT_EQ(EIRToCorfOfT.handle(), chiller.electricInputToCoolingOutputRatioFunctionOfTemperature().handle());
  EXPECT_EQ(EIRToCorfOfPLR.handle(), chiller.electricInputToCoolingOutputRatioFunctionOfPLR().handle());

  EXPECT_TRUE(chiller.setHeatRecoveryInletHighTemperatureLimitSchedule(heatRecoveryLimit));
  ASSERT_TRUE(chiller.heatRecoveryInletHighTemperatureLimitSchedule());
  EXPECT_EQ(heatRecoveryLimit.handle(), chiller.heatRecoveryInletHighTemperatureLimitSchedule()->handle());
  chiller.resetHeatRecoveryInletHighTemperatureLimitSchedule();
  EXPECT_FALSE(chiller.heatRecoveryInletHighTemperatureLimitSchedule());

  EXPECT_TRUE(chiller.setHeatRecoveryLeavingTemperatureSetpointNode(setpointNode));
  ASSERT_TRUE(chiller.heatRecoveryLeavingTemperatureSetpointNode());
  EXPECT_EQ(setpointNode.handle(), chiller.heatRecoveryLeavingTemperatureSetpointNode()->handle());
  chiller.resetHeatRecoveryLeavingTemperatureSetpointNode();
  EXPECT_FALSE(chiller.heatRecoveryLeavingTemperatureSetpointNode());

  EXPECT_TRUE(chiller.setCondenserLoopFlowRateFractionFunctionofLoopPartLoadRatioCurve(condenserLoopPLR));
  ASSERT_TRUE(chiller.condenserLoopFlowRateFractionFunctionofLoopPartLoadRatioCurve());
  EXPECT_EQ(condenserLoopPLR.handle(), chiller.condenserLoopFlowRateFractionFunctionofLoopPartLoadRatioCurve()->handle());
  chiller.resetCondenserLoopFlowRateFractionFunctionofLoopPartLoadRatioCurve();
  EXPECT_FALSE(chiller.condenserLoopFlowRateFractionFunctionofLoopPartLoadRatioCurve());

  EXPECT_TRUE(chiller.setTemperatureDifferenceAcrossCondenserSchedule(condenserDeltaT));
  ASSERT_TRUE(chiller.temperatureDifferenceAcrossCondenserSchedule());
  EXPECT_EQ(condenserDeltaT.handle(), chiller.temperatureDifferenceAcrossCondenserSchedule()->handle());
  chiller.resetTemperatureDifferenceAcrossCondenserSchedule();
  EXPECT_FALSE(chiller.temperatureDifferenceAcrossCondenserSchedule());

  EXPECT_TRUE(chiller.setThermosiphonCapacityFractionCurve(thermosiphonCurve));
  ASSERT_TRUE(chiller.thermosiphonCapacityFractionCurve());
  EXPECT_EQ(thermosiphonCurve.handle(), chiller.thermosiphonCapacityFractionCurve()->handle());
  chiller.resetThermosiphonCapacityFractionCurve();
  EXPECT_FALSE(chiller.thermosiphonCapacityFractionCurve());
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

  EXPECT_TRUE(chiller.setReferenceLeavingChilledWaterTemperature(6.5));
  EXPECT_DOUBLE_EQ(6.5, chiller.referenceLeavingChilledWaterTemperature());
  chiller.resetReferenceLeavingChilledWaterTemperature();
  EXPECT_TRUE(chiller.isReferenceLeavingChilledWaterTemperatureDefaulted());

  EXPECT_TRUE(chiller.setReferenceLeavingCondenserWaterTemperature(35.0));
  EXPECT_DOUBLE_EQ(35.0, chiller.referenceLeavingCondenserWaterTemperature());
  chiller.resetReferenceLeavingCondenserWaterTemperature();
  EXPECT_TRUE(chiller.isReferenceLeavingCondenserWaterTemperatureDefaulted());

  EXPECT_TRUE(chiller.setReferenceChilledWaterFlowRate(0.022));
  ASSERT_TRUE(chiller.referenceChilledWaterFlowRate());
  EXPECT_DOUBLE_EQ(0.022, *chiller.referenceChilledWaterFlowRate());
  chiller.autosizeReferenceChilledWaterFlowRate();
  EXPECT_TRUE(chiller.isReferenceChilledWaterFlowRateAutosized());

  EXPECT_TRUE(chiller.isReferenceCondenserWaterFlowRateAutosized());
  EXPECT_TRUE(chiller.setReferenceCondenserWaterFlowRate(0.03));
  ASSERT_TRUE(chiller.referenceCondenserWaterFlowRate());
  EXPECT_DOUBLE_EQ(0.03, *chiller.referenceCondenserWaterFlowRate());
  chiller.autosizeReferenceCondenserWaterFlowRate();
  EXPECT_TRUE(chiller.isReferenceCondenserWaterFlowRateAutosized());
  EXPECT_TRUE(chiller.setReferenceCondenserWaterFlowRate(0.04));
  ASSERT_TRUE(chiller.referenceCondenserWaterFlowRate());
  EXPECT_DOUBLE_EQ(0.04, *chiller.referenceCondenserWaterFlowRate());
  chiller.resetReferenceCondenserWaterFlowRate();
  EXPECT_TRUE(chiller.isReferenceCondenserWaterFlowRateAutosized());

  EXPECT_EQ("LeavingCondenserWaterTemperature", chiller.electricInputToCoolingOutputRatioFunctionOfPLRType());
  EXPECT_TRUE(chiller.setElectricInputToCoolingOutputRatioFunctionOfPLRType("Lift"));
  EXPECT_EQ("Lift", chiller.electricInputToCoolingOutputRatioFunctionOfPLRType());
  chiller.resetElectricInputToCoolingOutputRatioFunctionOfPLRType();
  EXPECT_EQ("LeavingCondenserWaterTemperature", chiller.electricInputToCoolingOutputRatioFunctionOfPLRType());

  EXPECT_TRUE(chiller.setMinimumPartLoadRatio(0.15));
  EXPECT_DOUBLE_EQ(0.15, chiller.minimumPartLoadRatio());
  chiller.resetMinimumPartLoadRatio();
  EXPECT_TRUE(chiller.isMinimumPartLoadRatioDefaulted());

  EXPECT_TRUE(chiller.setMaximumPartLoadRatio(0.95));
  EXPECT_DOUBLE_EQ(0.95, chiller.maximumPartLoadRatio());
  chiller.resetMaximumPartLoadRatio();
  EXPECT_TRUE(chiller.isMaximumPartLoadRatioDefaulted());

  EXPECT_TRUE(chiller.setOptimumPartLoadRatio(0.72));
  EXPECT_DOUBLE_EQ(0.72, chiller.optimumPartLoadRatio());
  chiller.resetOptimumPartLoadRatio();
  EXPECT_TRUE(chiller.isOptimumPartLoadRatioDefaulted());

  EXPECT_TRUE(chiller.setMinimumUnloadingRatio(0.18));
  EXPECT_DOUBLE_EQ(0.18, chiller.minimumUnloadingRatio());
  chiller.resetMinimumUnloadingRatio();
  EXPECT_TRUE(chiller.isMinimumUnloadingRatioDefaulted());

  EXPECT_TRUE(chiller.setFractionofCompressorElectricConsumptionRejectedbyCondenser(0.92));
  EXPECT_DOUBLE_EQ(0.92, chiller.fractionofCompressorElectricConsumptionRejectedbyCondenser());
  chiller.resetFractionofCompressorElectricConsumptionRejectedbyCondenser();
  EXPECT_TRUE(chiller.isFractionofCompressorElectricConsumptionRejectedbyCondenserDefaulted());

  EXPECT_TRUE(chiller.setLeavingChilledWaterLowerTemperatureLimit(3.0));
  EXPECT_DOUBLE_EQ(3.0, chiller.leavingChilledWaterLowerTemperatureLimit());
  chiller.resetLeavingChilledWaterLowerTemperatureLimit();
  EXPECT_TRUE(chiller.isLeavingChilledWaterLowerTemperatureLimitDefaulted());

  EXPECT_EQ("NotModulated", chiller.chillerFlowMode());
  EXPECT_TRUE(chiller.setChillerFlowMode("VariableFlow"));
  EXPECT_EQ("LeavingSetpointModulated", chiller.chillerFlowMode());
  chiller.resetChillerFlowMode();
  EXPECT_TRUE(chiller.isChillerFlowModeDefaulted());
  EXPECT_EQ("NotModulated", chiller.chillerFlowMode());

  EXPECT_TRUE(chiller.setDesignHeatRecoveryWaterFlowRate(0.01));
  ASSERT_TRUE(chiller.designHeatRecoveryWaterFlowRate());
  EXPECT_DOUBLE_EQ(0.01, *chiller.designHeatRecoveryWaterFlowRate());
  chiller.autosizeDesignHeatRecoveryWaterFlowRate();
  EXPECT_TRUE(chiller.isDesignHeatRecoveryWaterFlowRateAutosized());

  EXPECT_TRUE(chiller.setSizingFactor(1.1));
  EXPECT_DOUBLE_EQ(1.1, chiller.sizingFactor());
  chiller.resetSizingFactor();
  EXPECT_TRUE(chiller.isSizingFactorDefaulted());

  EXPECT_TRUE(chiller.setCondenserHeatRecoveryRelativeCapacityFraction(0.25));
  EXPECT_DOUBLE_EQ(0.25, chiller.condenserHeatRecoveryRelativeCapacityFraction());

  EXPECT_TRUE(chiller.setEndUseSubcategory("Cooling"));
  EXPECT_EQ("Cooling", chiller.endUseSubcategory());

  EXPECT_TRUE(chiller.setCondenserFlowControl("ConstantFlow"));
  EXPECT_EQ("ConstantFlow", chiller.condenserFlowControl());

  EXPECT_TRUE(chiller.setCondenserMinimumFlowFraction(0.2));
  EXPECT_DOUBLE_EQ(0.2, chiller.condenserMinimumFlowFraction());

  EXPECT_TRUE(chiller.setThermosiphonMinimumTemperatureDifference(0.5));
  EXPECT_DOUBLE_EQ(0.5, chiller.thermosiphonMinimumTemperatureDifference());
}

TEST_F(EPModelFixture, ChillerElectricReformulatedEIR_PlantLoopAttachmentParity) {
  Model model;
  PlantLoop chilledWaterLoop(model);
  PlantLoop condenserLoop(model);
  PlantLoop heatRecoveryLoop(model);
  ChillerElectricReformulatedEIR chiller(model);

  EXPECT_TRUE(chilledWaterLoop.addSupplyBranchForComponent(chiller));
  ASSERT_TRUE(chiller.chilledWaterLoop());
  EXPECT_EQ(chilledWaterLoop.handle(), chiller.chilledWaterLoop()->handle());

  EXPECT_TRUE(condenserLoop.addDemandBranchForComponent(chiller));
  ASSERT_TRUE(chiller.condenserWaterLoop());
  EXPECT_EQ(condenserLoop.handle(), chiller.condenserWaterLoop()->handle());

  EXPECT_TRUE(heatRecoveryLoop.addDemandBranchForComponent(chiller));
  ASSERT_TRUE(chiller.heatRecoveryLoop());
  EXPECT_EQ(heatRecoveryLoop.handle(), chiller.heatRecoveryLoop()->handle());
  ASSERT_TRUE(chiller.condenserWaterLoop());
  EXPECT_EQ(condenserLoop.handle(), chiller.condenserWaterLoop()->handle());

  ASSERT_TRUE(chiller.chilledWaterInletNode());
  ASSERT_TRUE(chiller.chilledWaterOutletNode());
  ASSERT_TRUE(chiller.condenserInletNode());
  ASSERT_TRUE(chiller.condenserOutletNode());
  ASSERT_TRUE(chiller.heatRecoveryInletNode());
  ASSERT_TRUE(chiller.heatRecoveryOutletNode());

  Node condenserSupplyOutletNode = condenserLoop.supplyOutletNode();
  EXPECT_FALSE(chiller.addToTertiaryNode(condenserSupplyOutletNode));

  Node heatRecoveryInletNode = *chiller.heatRecoveryInletNode();
  EXPECT_FALSE(chiller.addToTertiaryNode(heatRecoveryInletNode));

  EXPECT_TRUE(chiller.removeFromSecondaryPlantLoop());
  EXPECT_FALSE(chiller.condenserWaterLoop());
  EXPECT_FALSE(chiller.condenserInletNode());
  EXPECT_FALSE(chiller.condenserOutletNode());
  ASSERT_TRUE(chiller.heatRecoveryLoop());
  EXPECT_EQ(heatRecoveryLoop.handle(), chiller.heatRecoveryLoop()->handle());
  ASSERT_TRUE(chiller.heatRecoveryInletNode());
  ASSERT_TRUE(chiller.heatRecoveryOutletNode());
}

TEST_F(EPModelFixture, ChillerElectricReformulatedEIR_AddToNodeDemandRoutingParity) {
  Model model;
  ChillerElectricReformulatedEIR chiller(model);

  PlantLoop chilledWaterLoop(model);
  PlantLoop condenserLoop(model);
  PlantLoop replacementCondenserLoop(model);
  PlantLoop heatRecoveryLoop(model);

  EXPECT_TRUE(chilledWaterLoop.addSupplyBranchForComponent(chiller));
  ASSERT_TRUE(chiller.chilledWaterLoop());
  EXPECT_EQ(chilledWaterLoop.handle(), chiller.chilledWaterLoop()->handle());
  EXPECT_FALSE(chiller.condenserWaterLoop());
  EXPECT_FALSE(chiller.heatRecoveryLoop());

  EXPECT_TRUE(condenserLoop.addDemandBranchForComponent(chiller));
  ASSERT_TRUE(chiller.condenserWaterLoop());
  EXPECT_EQ(condenserLoop.handle(), chiller.condenserWaterLoop()->handle());
  EXPECT_FALSE(chiller.heatRecoveryLoop());

  Node initialHeatRecoveryDemandNode = heatRecoveryLoop.demandInletNode();
  EXPECT_TRUE(chiller.addToNode(initialHeatRecoveryDemandNode));
  ASSERT_TRUE(chiller.heatRecoveryLoop());
  EXPECT_EQ(heatRecoveryLoop.handle(), chiller.heatRecoveryLoop()->handle());
  ASSERT_TRUE(chiller.condenserWaterLoop());
  EXPECT_EQ(condenserLoop.handle(), chiller.condenserWaterLoop()->handle());
  ASSERT_TRUE(chiller.chilledWaterLoop());
  EXPECT_EQ(chilledWaterLoop.handle(), chiller.chilledWaterLoop()->handle());

  EXPECT_TRUE(chiller.removeFromTertiaryPlantLoop());
  EXPECT_FALSE(chiller.heatRecoveryLoop());

  EXPECT_TRUE(heatRecoveryLoop.addDemandBranchForComponent(chiller));
  ASSERT_TRUE(chiller.heatRecoveryLoop());
  EXPECT_EQ(heatRecoveryLoop.handle(), chiller.heatRecoveryLoop()->handle());
  ASSERT_TRUE(chiller.condenserWaterLoop());
  EXPECT_EQ(condenserLoop.handle(), chiller.condenserWaterLoop()->handle());

  Node replacementDemandNode = replacementCondenserLoop.demandOutletNode();
  EXPECT_TRUE(chiller.addToNode(replacementDemandNode));
  ASSERT_TRUE(chiller.condenserWaterLoop());
  EXPECT_EQ(replacementCondenserLoop.handle(), chiller.condenserWaterLoop()->handle());
  ASSERT_TRUE(chiller.chilledWaterLoop());
  EXPECT_EQ(chilledWaterLoop.handle(), chiller.chilledWaterLoop()->handle());
  ASSERT_TRUE(chiller.heatRecoveryLoop());
  EXPECT_EQ(heatRecoveryLoop.handle(), chiller.heatRecoveryLoop()->handle());

  EXPECT_TRUE(chiller.removeFromTertiaryPlantLoop());
  EXPECT_FALSE(chiller.heatRecoveryLoop());

  Node heatRecoverySupplyNode = heatRecoveryLoop.supplyOutletNode();
  EXPECT_FALSE(chiller.addToTertiaryNode(heatRecoverySupplyNode));
  EXPECT_FALSE(chiller.heatRecoveryLoop());

  Node heatRecoveryDemandNode = heatRecoveryLoop.demandInletNode();
  EXPECT_TRUE(chiller.addToNode(heatRecoveryDemandNode));
  ASSERT_TRUE(chiller.heatRecoveryLoop());
  EXPECT_EQ(heatRecoveryLoop.handle(), chiller.heatRecoveryLoop()->handle());
  ASSERT_TRUE(chiller.condenserWaterLoop());
  EXPECT_EQ(replacementCondenserLoop.handle(), chiller.condenserWaterLoop()->handle());
  ASSERT_TRUE(chiller.chilledWaterLoop());
  EXPECT_EQ(chilledWaterLoop.handle(), chiller.chilledWaterLoop()->handle());
}
