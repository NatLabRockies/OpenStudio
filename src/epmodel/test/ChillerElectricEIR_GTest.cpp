/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Curve/CurveBiquadratic.hpp"
#include "../Curve/CurveQuadratic.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../Loop/PlantLoop_Impl.hpp"
#include "../ModelObject/SizingPlant.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../StraightComponent/Node.hpp"
#include "../WaterToWaterComponent/ChillerElectricEIR.hpp"
#include "../WaterToWaterComponent/ChillerElectricEIR_Impl.hpp"

#include <utilities/idd/Chiller_Electric_EIR_FieldEnums.hxx>

#include <limits>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ChillerElectricEIR_DefaultConstructor) {
  Model model;
  ChillerElectricEIR chiller(model);

  EXPECT_EQ(ChillerElectricEIR::iddObjectType(), chiller.iddObject().type());
  EXPECT_FALSE(chiller.nameString().empty());
  EXPECT_NE(std::numeric_limits<unsigned>::max(), chiller.supplyInletPort());
  EXPECT_NE(std::numeric_limits<unsigned>::max(), chiller.demandInletPort());
  EXPECT_NE(std::numeric_limits<unsigned>::max(), chiller.tertiaryInletPort());

  EXPECT_EQ(CurveBiquadratic::iddObjectType(), chiller.coolingCapacityFunctionOfTemperature().iddObject().type());
  EXPECT_EQ(CurveBiquadratic::iddObjectType(), chiller.electricInputToCoolingOutputRatioFunctionOfTemperature().iddObject().type());
  EXPECT_EQ(CurveQuadratic::iddObjectType(), chiller.electricInputToCoolingOutputRatioFunctionOfPLR().iddObject().type());

  EXPECT_DOUBLE_EQ(5.5, chiller.referenceCOP());
  EXPECT_EQ("AirCooled", chiller.condenserType());
  EXPECT_TRUE(chiller.isReferenceCapacityAutosized());
  EXPECT_TRUE(chiller.isReferenceChilledWaterFlowRateAutosized());
  EXPECT_TRUE(chiller.isEmpty(openstudio::Chiller_Electric_EIRFields::DesignHeatRecoveryWaterFlowRate));
  EXPECT_DOUBLE_EQ(10.0, chiller.basinHeaterSetpointTemperature());
  EXPECT_FALSE(chiller.basinHeaterSchedule());

  EXPECT_TRUE(chiller.isEmpty(openstudio::Chiller_Electric_EIRFields::CondenserHeatRecoveryRelativeCapacityFraction));
  EXPECT_TRUE(chiller.isEmpty(openstudio::Chiller_Electric_EIRFields::HeatRecoveryInletHighTemperatureLimitScheduleName));
  EXPECT_TRUE(chiller.isEmpty(openstudio::Chiller_Electric_EIRFields::HeatRecoveryLeavingTemperatureSetpointNodeName));
  EXPECT_TRUE(chiller.isEmpty(openstudio::Chiller_Electric_EIRFields::EndUseSubcategory));
  EXPECT_TRUE(chiller.isEmpty(openstudio::Chiller_Electric_EIRFields::CondenserFlowControl));
  EXPECT_TRUE(chiller.isEmpty(openstudio::Chiller_Electric_EIRFields::CondenserLoopFlowRateFractionFunctionofLoopPartLoadRatioCurveName));
  EXPECT_TRUE(chiller.isEmpty(openstudio::Chiller_Electric_EIRFields::TemperatureDifferenceAcrossCondenserScheduleName));
  EXPECT_TRUE(chiller.isEmpty(openstudio::Chiller_Electric_EIRFields::CondenserMinimumFlowFraction));
  EXPECT_TRUE(chiller.isEmpty(openstudio::Chiller_Electric_EIRFields::ThermosiphonCapacityFractionCurveName));
  EXPECT_TRUE(chiller.isEmpty(openstudio::Chiller_Electric_EIRFields::ThermosiphonMinimumTemperatureDifference));
  EXPECT_FALSE(chiller.chilledWaterLoop());
  EXPECT_FALSE(chiller.condenserWaterLoop());
  EXPECT_FALSE(chiller.heatRecoveryLoop());
}

TEST_F(EPModelFixture, ChillerElectricEIR_CurveConstructorAndRelationships) {
  Model model;
  CurveBiquadratic CCFofT(model);
  CurveBiquadratic EIRToCorfOfT(model);
  CurveQuadratic EIRToCorfOfPLR(model);
  CurveQuadratic condenserLoopPLR(model);
  CurveQuadratic thermosiphonCurve(model);
  ScheduleConstant basinHeater(model);
  ScheduleConstant heatRecoveryLimit(model);
  ScheduleConstant condenserDeltaT(model);
  Node setpointNode(model);

  ChillerElectricEIR chiller(model, CCFofT, EIRToCorfOfT, EIRToCorfOfPLR);

  EXPECT_EQ(CCFofT.handle(), chiller.coolingCapacityFunctionOfTemperature().handle());
  EXPECT_EQ(EIRToCorfOfT.handle(), chiller.electricInputToCoolingOutputRatioFunctionOfTemperature().handle());
  EXPECT_EQ(EIRToCorfOfPLR.handle(), chiller.electricInputToCoolingOutputRatioFunctionOfPLR().handle());

  EXPECT_TRUE(chiller.setBasinHeaterSchedule(basinHeater));
  ASSERT_TRUE(chiller.basinHeaterSchedule());
  EXPECT_EQ(basinHeater.handle(), chiller.basinHeaterSchedule()->handle());
  chiller.resetBasinHeaterSchedule();
  EXPECT_FALSE(chiller.basinHeaterSchedule());

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

TEST_F(EPModelFixture, ChillerElectricEIR_ScalarAccessors_RoundTrip) {
  Model model;
  ChillerElectricEIR chiller(model);

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

  EXPECT_TRUE(chiller.setReferenceEnteringCondenserFluidTemperature(29.0));
  EXPECT_DOUBLE_EQ(29.0, chiller.referenceEnteringCondenserFluidTemperature());
  chiller.resetReferenceEnteringCondenserFluidTemperature();
  EXPECT_TRUE(chiller.isReferenceEnteringCondenserFluidTemperatureDefaulted());

  EXPECT_TRUE(chiller.setReferenceChilledWaterFlowRate(0.022));
  ASSERT_TRUE(chiller.referenceChilledWaterFlowRate());
  EXPECT_DOUBLE_EQ(0.022, *chiller.referenceChilledWaterFlowRate());
  chiller.autosizeReferenceChilledWaterFlowRate();
  EXPECT_TRUE(chiller.isReferenceChilledWaterFlowRateAutosized());

  EXPECT_TRUE(chiller.setReferenceCondenserFluidFlowRate(0.031));
  ASSERT_TRUE(chiller.referenceCondenserFluidFlowRate());
  EXPECT_DOUBLE_EQ(0.031, *chiller.referenceCondenserFluidFlowRate());
  chiller.autosizeReferenceCondenserFluidFlowRate();
  EXPECT_TRUE(chiller.isReferenceCondenserFluidFlowRateAutosized());

  EXPECT_TRUE(chiller.setMinimumPartLoadRatio(0.12));
  EXPECT_DOUBLE_EQ(0.12, chiller.minimumPartLoadRatio());
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

  EXPECT_TRUE(chiller.setCondenserType("EvaporativelyCooled"));
  EXPECT_EQ("EvaporativelyCooled", chiller.condenserType());
  chiller.resetCondenserType();
  EXPECT_TRUE(chiller.isCondenserTypeDefaulted());

  EXPECT_TRUE(chiller.setCondenserFanPowerRatio(0.08));
  EXPECT_DOUBLE_EQ(0.08, chiller.condenserFanPowerRatio());
  chiller.resetCondenserFanPowerRatio();
  EXPECT_TRUE(chiller.isCondenserFanPowerRatioDefaulted());

  EXPECT_TRUE(chiller.setFractionofCompressorElectricConsumptionRejectedbyCondenser(0.93));
  EXPECT_DOUBLE_EQ(0.93, chiller.fractionofCompressorElectricConsumptionRejectedbyCondenser());
  chiller.resetFractionofCompressorElectricConsumptionRejectedbyCondenser();
  EXPECT_TRUE(chiller.isFractionofCompressorElectricConsumptionRejectedbyCondenserDefaulted());

  EXPECT_TRUE(chiller.setLeavingChilledWaterLowerTemperatureLimit(3.0));
  EXPECT_DOUBLE_EQ(3.0, chiller.leavingChilledWaterLowerTemperatureLimit());
  chiller.resetLeavingChilledWaterLowerTemperatureLimit();
  EXPECT_TRUE(chiller.isLeavingChilledWaterLowerTemperatureLimitDefaulted());

  EXPECT_TRUE(chiller.setChillerFlowMode("VariableFlow"));
  EXPECT_EQ("LeavingSetpointModulated", chiller.chillerFlowMode());
  chiller.resetChillerFlowMode();
  EXPECT_TRUE(chiller.isChillerFlowModeDefaulted());

  EXPECT_TRUE(chiller.setDesignHeatRecoveryWaterFlowRate(0.01));
  ASSERT_TRUE(chiller.designHeatRecoveryWaterFlowRate());
  EXPECT_DOUBLE_EQ(0.01, *chiller.designHeatRecoveryWaterFlowRate());
  chiller.autosizeDesignHeatRecoveryWaterFlowRate();
  EXPECT_TRUE(chiller.isDesignHeatRecoveryWaterFlowRateAutosized());

  EXPECT_TRUE(chiller.setSizingFactor(1.1));
  EXPECT_DOUBLE_EQ(1.1, chiller.sizingFactor());
  chiller.resetSizingFactor();
  EXPECT_TRUE(chiller.isSizingFactorDefaulted());

  EXPECT_TRUE(chiller.setBasinHeaterCapacity(120.0));
  EXPECT_DOUBLE_EQ(120.0, chiller.basinHeaterCapacity());
  chiller.resetBasinHeaterCapacity();
  EXPECT_TRUE(chiller.isBasinHeaterCapacityDefaulted());

  EXPECT_TRUE(chiller.setBasinHeaterSetpointTemperature(5.0));
  EXPECT_DOUBLE_EQ(5.0, chiller.basinHeaterSetpointTemperature());
  chiller.resetBasinHeaterSetpointTemperature();
  EXPECT_TRUE(chiller.isBasinHeaterSetpointTemperatureDefaulted());

  EXPECT_TRUE(chiller.setCondenserHeatRecoveryRelativeCapacityFraction(0.2));
  EXPECT_DOUBLE_EQ(0.2, chiller.condenserHeatRecoveryRelativeCapacityFraction());

  EXPECT_TRUE(chiller.setEndUseSubcategory("Cooling"));
  EXPECT_EQ("Cooling", chiller.endUseSubcategory());

  EXPECT_TRUE(chiller.setCondenserFlowControl("ConstantFlow"));
  EXPECT_EQ("ConstantFlow", chiller.condenserFlowControl());

  EXPECT_TRUE(chiller.setCondenserMinimumFlowFraction(0.25));
  EXPECT_DOUBLE_EQ(0.25, chiller.condenserMinimumFlowFraction());

  EXPECT_TRUE(chiller.setThermosiphonMinimumTemperatureDifference(0.3));
  EXPECT_DOUBLE_EQ(0.3, chiller.thermosiphonMinimumTemperatureDifference());
}

TEST_F(EPModelFixture, ChillerElectricEIR_CondenserTypeParity) {
  Model model;
  PlantLoop chilledWaterLoop(model);
  PlantLoop condenserLoop(model);
  ChillerElectricEIR chiller(model);

  EXPECT_EQ("AirCooled", chiller.condenserType());
  EXPECT_TRUE(chiller.setCondenserType("EvaporativelyCooled"));
  EXPECT_EQ("EvaporativelyCooled", chiller.condenserType());
  EXPECT_TRUE(chiller.setCondenserType("AirCooled"));
  EXPECT_EQ("AirCooled", chiller.condenserType());
  EXPECT_FALSE(chiller.setCondenserType("WaterCooled"));
  EXPECT_EQ("AirCooled", chiller.condenserType());

  EXPECT_TRUE(chilledWaterLoop.addSupplyBranchForComponent(chiller));
  EXPECT_TRUE(chiller.setCondenserType("EvaporativelyCooled"));
  EXPECT_EQ("EvaporativelyCooled", chiller.condenserType());
  EXPECT_TRUE(chiller.setCondenserType("AirCooled"));
  EXPECT_EQ("AirCooled", chiller.condenserType());
  EXPECT_FALSE(chiller.setCondenserType("WaterCooled"));
  EXPECT_EQ("AirCooled", chiller.condenserType());

  EXPECT_TRUE(condenserLoop.addDemandBranchForComponent(chiller));
  ASSERT_TRUE(chiller.condenserWaterLoop());
  EXPECT_EQ(condenserLoop.handle(), chiller.condenserWaterLoop()->handle());
  EXPECT_EQ("WaterCooled", chiller.condenserType());
  EXPECT_FALSE(chiller.setCondenserType("AirCooled"));
  EXPECT_FALSE(chiller.setCondenserType("EvaporativelyCooled"));
  EXPECT_EQ("WaterCooled", chiller.condenserType());

  EXPECT_TRUE(chiller.removeFromSecondaryPlantLoop());
  EXPECT_FALSE(chiller.condenserWaterLoop());
  EXPECT_EQ("AirCooled", chiller.condenserType());
  EXPECT_TRUE(chiller.setCondenserType("EvaporativelyCooled"));
  EXPECT_EQ("EvaporativelyCooled", chiller.condenserType());
  EXPECT_TRUE(chiller.setCondenserType("AirCooled"));
  EXPECT_EQ("AirCooled", chiller.condenserType());
  EXPECT_FALSE(chiller.setCondenserType("WaterCooled"));
  EXPECT_EQ("AirCooled", chiller.condenserType());
}

TEST_F(EPModelFixture, ChillerElectricEIR_PlantLoopAttachmentParity) {
  Model model;
  PlantLoop chilledWaterLoop(model);
  PlantLoop condenserLoop(model);
  PlantLoop heatRecoveryLoop(model);
  ChillerElectricEIR chiller(model);

  EXPECT_TRUE(chilledWaterLoop.addSupplyBranchForComponent(chiller));
  ASSERT_TRUE(chiller.chilledWaterLoop());
  EXPECT_EQ(chilledWaterLoop.handle(), chiller.chilledWaterLoop()->handle());

  EXPECT_TRUE(condenserLoop.addDemandBranchForComponent(chiller));
  ASSERT_TRUE(chiller.condenserWaterLoop());
  EXPECT_EQ(condenserLoop.handle(), chiller.condenserWaterLoop()->handle());
  EXPECT_EQ("WaterCooled", chiller.condenserType());

  EXPECT_TRUE(heatRecoveryLoop.addDemandBranchForComponent(chiller));
  ASSERT_TRUE(chiller.heatRecoveryLoop());
  EXPECT_EQ(heatRecoveryLoop.handle(), chiller.heatRecoveryLoop()->handle());
  EXPECT_FALSE(chiller.isEmpty(openstudio::Chiller_Electric_EIRFields::DesignHeatRecoveryWaterFlowRate));
  EXPECT_TRUE(chiller.isDesignHeatRecoveryWaterFlowRateAutosized());
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
  EXPECT_EQ("AirCooled", chiller.condenserType());
}

TEST_F(EPModelFixture, ChillerElectricEIR_AddToNodeDemandRoutingParity) {
  Model model;
  ChillerElectricEIR chiller(model);

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
  EXPECT_EQ("WaterCooled", chiller.condenserType());

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

TEST_F(EPModelFixture, ChillerElectricEIR_SequentialLastOwnerLoopRemovalLifecycle) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-chiller-electric-eir-sequential-last-owner-removal.idf");

  Model model;
  PlantLoop chilledWaterLoop(model);
  PlantLoop condenserWaterLoop(model);
  PlantLoop heatRecoveryLoop(model);
  ChillerElectricEIR chiller(model);
  ASSERT_TRUE(chilledWaterLoop.setName("Final Electric EIR Chilled Water Loop"));
  ASSERT_TRUE(condenserWaterLoop.setName("Second Electric EIR Condenser Water Loop"));
  ASSERT_TRUE(heatRecoveryLoop.setName("First Electric EIR Heat Recovery Loop"));
  ASSERT_TRUE(chiller.setName("Sequential Deleted Electric EIR Chiller"));
  ASSERT_TRUE(chilledWaterLoop.addSupplyBranchForComponent(chiller));
  ASSERT_TRUE(condenserWaterLoop.addDemandBranchForComponent(chiller));
  ASSERT_TRUE(heatRecoveryLoop.addDemandBranchForComponent(chiller));
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedChilledWaterLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Final Electric EIR Chilled Water Loop");
  auto loadedCondenserWaterLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Second Electric EIR Condenser Water Loop");
  auto loadedHeatRecoveryLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("First Electric EIR Heat Recovery Loop");
  auto loadedChiller = loadedModel->getConcreteModelObjectByName<ChillerElectricEIR>("Sequential Deleted Electric EIR Chiller");
  ASSERT_TRUE(loadedChilledWaterLoop);
  ASSERT_TRUE(loadedCondenserWaterLoop);
  ASSERT_TRUE(loadedHeatRecoveryLoop);
  ASSERT_TRUE(loadedChiller);
  ASSERT_TRUE(loadedChiller->chilledWaterLoop());
  ASSERT_TRUE(loadedChiller->condenserWaterLoop());
  ASSERT_TRUE(loadedChiller->heatRecoveryLoop());
  EXPECT_EQ("WaterCooled", loadedChiller->condenserType());

  const auto chillerHandle = loadedChiller->handle();
  const auto removeOwnerLoop = [&](PlantLoop& loop) {
    std::vector<openstudio::Handle> topologyHandles;
    for (const auto& component : loop.supplyComponents()) {
      if (component.handle() != chillerHandle) {
        topologyHandles.push_back(component.handle());
      }
    }
    for (const auto& component : loop.demandComponents()) {
      if (component.handle() != chillerHandle) {
        topologyHandles.push_back(component.handle());
      }
    }
    const auto loopHandle = loop.handle();
    const auto sizingPlantHandle = loop.sizingPlant().handle();
    EXPECT_FALSE(loop.remove().empty());
    EXPECT_FALSE(loadedModel->getObject(loopHandle));
    EXPECT_FALSE(loadedModel->getObject(sizingPlantHandle));
    for (const auto& handle : topologyHandles) {
      EXPECT_FALSE(loadedModel->getObject(handle));
    }
  };

  removeOwnerLoop(*loadedHeatRecoveryLoop);
  ASSERT_TRUE(loadedModel->getObject(chillerHandle));
  EXPECT_FALSE(loadedChiller->heatRecoveryLoop());
  EXPECT_FALSE(loadedChiller->heatRecoveryInletNode());
  EXPECT_FALSE(loadedChiller->heatRecoveryOutletNode());
  ASSERT_TRUE(loadedChiller->chilledWaterLoop());
  ASSERT_TRUE(loadedChiller->condenserWaterLoop());
  EXPECT_EQ(*loadedChilledWaterLoop, *loadedChiller->chilledWaterLoop());
  EXPECT_EQ(*loadedCondenserWaterLoop, *loadedChiller->condenserWaterLoop());
  EXPECT_TRUE(loadedChiller->chilledWaterInletNode());
  EXPECT_TRUE(loadedChiller->chilledWaterOutletNode());
  EXPECT_TRUE(loadedChiller->condenserInletNode());
  EXPECT_TRUE(loadedChiller->condenserOutletNode());
  EXPECT_EQ("WaterCooled", loadedChiller->condenserType());

  removeOwnerLoop(*loadedCondenserWaterLoop);
  ASSERT_TRUE(loadedModel->getObject(chillerHandle));
  EXPECT_FALSE(loadedChiller->condenserWaterLoop());
  EXPECT_FALSE(loadedChiller->condenserInletNode());
  EXPECT_FALSE(loadedChiller->condenserOutletNode());
  EXPECT_FALSE(loadedChiller->heatRecoveryLoop());
  ASSERT_TRUE(loadedChiller->chilledWaterLoop());
  EXPECT_EQ(*loadedChilledWaterLoop, *loadedChiller->chilledWaterLoop());
  EXPECT_TRUE(loadedChiller->chilledWaterInletNode());
  EXPECT_TRUE(loadedChiller->chilledWaterOutletNode());
  EXPECT_EQ("AirCooled", loadedChiller->condenserType());

  removeOwnerLoop(*loadedChilledWaterLoop);
  EXPECT_FALSE(loadedModel->getObject(chillerHandle));

  ASSERT_TRUE(loadedModel->save(idfPath, true));
  auto reloadedModel = Model::load(idfPath);
  ASSERT_TRUE(reloadedModel);
  EXPECT_FALSE(reloadedModel->getConcreteModelObjectByName<PlantLoop>("First Electric EIR Heat Recovery Loop"));
  EXPECT_FALSE(reloadedModel->getConcreteModelObjectByName<PlantLoop>("Second Electric EIR Condenser Water Loop"));
  EXPECT_FALSE(reloadedModel->getConcreteModelObjectByName<PlantLoop>("Final Electric EIR Chilled Water Loop"));
  EXPECT_FALSE(reloadedModel->getConcreteModelObjectByName<ChillerElectricEIR>("Sequential Deleted Electric EIR Chiller"));

  openstudio::filesystem::remove(idfPath);
}

TEST_F(EPModelFixture, ChillerElectricEIR_TripleOwnerLoopRemovalLifecycle) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-chiller-electric-eir-triple-owner-primary-removal.idf");

  Model model;
  PlantLoop chilledWaterLoop(model);
  PlantLoop condenserWaterLoop(model);
  PlantLoop heatRecoveryLoop(model);
  ChillerElectricEIR chiller(model);
  ASSERT_TRUE(chilledWaterLoop.setName("Removed Chiller Chilled Water Loop"));
  ASSERT_TRUE(condenserWaterLoop.setName("Surviving Chiller Condenser Water Loop"));
  ASSERT_TRUE(heatRecoveryLoop.setName("Surviving Chiller Heat Recovery Loop"));
  ASSERT_TRUE(chiller.setName("Surviving Triple Owner Chiller"));
  ASSERT_TRUE(chilledWaterLoop.addSupplyBranchForComponent(chiller));
  ASSERT_TRUE(condenserWaterLoop.addDemandBranchForComponent(chiller));
  ASSERT_TRUE(heatRecoveryLoop.addDemandBranchForComponent(chiller));
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedChilledWaterLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Removed Chiller Chilled Water Loop");
  auto loadedCondenserWaterLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Surviving Chiller Condenser Water Loop");
  auto loadedHeatRecoveryLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Surviving Chiller Heat Recovery Loop");
  auto loadedChiller = loadedModel->getConcreteModelObjectByName<ChillerElectricEIR>("Surviving Triple Owner Chiller");
  ASSERT_TRUE(loadedChilledWaterLoop);
  ASSERT_TRUE(loadedCondenserWaterLoop);
  ASSERT_TRUE(loadedHeatRecoveryLoop);
  ASSERT_TRUE(loadedChiller);
  ASSERT_TRUE(loadedChiller->chilledWaterLoop());
  ASSERT_TRUE(loadedChiller->condenserWaterLoop());
  ASSERT_TRUE(loadedChiller->heatRecoveryLoop());
  EXPECT_EQ(*loadedChilledWaterLoop, *loadedChiller->chilledWaterLoop());
  EXPECT_EQ(*loadedCondenserWaterLoop, *loadedChiller->condenserWaterLoop());
  EXPECT_EQ(*loadedHeatRecoveryLoop, *loadedChiller->heatRecoveryLoop());
  EXPECT_EQ(1u, loadedChilledWaterLoop->supplyComponents(ChillerElectricEIR::iddObjectType()).size());
  EXPECT_EQ(1u, loadedCondenserWaterLoop->demandComponents(ChillerElectricEIR::iddObjectType()).size());
  EXPECT_EQ(1u, loadedHeatRecoveryLoop->demandComponents(ChillerElectricEIR::iddObjectType()).size());
  EXPECT_TRUE(loadedChiller->chilledWaterInletNode());
  EXPECT_TRUE(loadedChiller->chilledWaterOutletNode());
  EXPECT_TRUE(loadedChiller->condenserInletNode());
  EXPECT_TRUE(loadedChiller->condenserOutletNode());
  EXPECT_TRUE(loadedChiller->heatRecoveryInletNode());
  EXPECT_TRUE(loadedChiller->heatRecoveryOutletNode());
  EXPECT_EQ("WaterCooled", loadedChiller->condenserType());

  std::vector<openstudio::Handle> chilledWaterTopologyHandles;
  for (const auto& component : loadedChilledWaterLoop->supplyComponents()) {
    if (component.handle() != loadedChiller->handle()) {
      chilledWaterTopologyHandles.push_back(component.handle());
    }
  }
  for (const auto& component : loadedChilledWaterLoop->demandComponents()) {
    chilledWaterTopologyHandles.push_back(component.handle());
  }
  const auto chilledWaterLoopHandle = loadedChilledWaterLoop->handle();
  const auto chilledWaterSizingHandle = loadedChilledWaterLoop->sizingPlant().handle();
  const auto chillerHandle = loadedChiller->handle();
  EXPECT_FALSE(loadedChilledWaterLoop->remove().empty());
  EXPECT_FALSE(loadedModel->getObject(chilledWaterLoopHandle));
  EXPECT_FALSE(loadedModel->getObject(chilledWaterSizingHandle));
  for (const auto& handle : chilledWaterTopologyHandles) {
    EXPECT_FALSE(loadedModel->getObject(handle));
  }
  EXPECT_TRUE(loadedModel->getObject(chillerHandle));
  EXPECT_FALSE(loadedChiller->chilledWaterLoop());
  EXPECT_FALSE(loadedChiller->chilledWaterInletNode());
  EXPECT_FALSE(loadedChiller->chilledWaterOutletNode());
  ASSERT_TRUE(loadedChiller->condenserWaterLoop());
  ASSERT_TRUE(loadedChiller->heatRecoveryLoop());
  EXPECT_EQ(*loadedCondenserWaterLoop, *loadedChiller->condenserWaterLoop());
  EXPECT_EQ(*loadedHeatRecoveryLoop, *loadedChiller->heatRecoveryLoop());
  EXPECT_EQ(1u, loadedCondenserWaterLoop->demandComponents(ChillerElectricEIR::iddObjectType()).size());
  EXPECT_EQ(1u, loadedHeatRecoveryLoop->demandComponents(ChillerElectricEIR::iddObjectType()).size());
  EXPECT_TRUE(loadedChiller->condenserInletNode());
  EXPECT_TRUE(loadedChiller->condenserOutletNode());
  EXPECT_TRUE(loadedChiller->heatRecoveryInletNode());
  EXPECT_TRUE(loadedChiller->heatRecoveryOutletNode());
  EXPECT_EQ("WaterCooled", loadedChiller->condenserType());

  PlantLoop replacementChilledWaterLoop(*loadedModel);
  ASSERT_TRUE(replacementChilledWaterLoop.setName("Replacement Chiller Chilled Water Loop"));
  ASSERT_TRUE(replacementChilledWaterLoop.addSupplyBranchForComponent(*loadedChiller));
  ASSERT_TRUE(loadedModel->save(idfPath, true));

  auto reloadedModel = Model::load(idfPath);
  ASSERT_TRUE(reloadedModel);
  auto reloadedChilledWaterLoop = reloadedModel->getConcreteModelObjectByName<PlantLoop>("Replacement Chiller Chilled Water Loop");
  auto reloadedCondenserWaterLoop = reloadedModel->getConcreteModelObjectByName<PlantLoop>("Surviving Chiller Condenser Water Loop");
  auto reloadedHeatRecoveryLoop = reloadedModel->getConcreteModelObjectByName<PlantLoop>("Surviving Chiller Heat Recovery Loop");
  auto reloadedChiller = reloadedModel->getConcreteModelObjectByName<ChillerElectricEIR>("Surviving Triple Owner Chiller");
  ASSERT_TRUE(reloadedChilledWaterLoop);
  ASSERT_TRUE(reloadedCondenserWaterLoop);
  ASSERT_TRUE(reloadedHeatRecoveryLoop);
  ASSERT_TRUE(reloadedChiller);
  EXPECT_FALSE(reloadedModel->getConcreteModelObjectByName<PlantLoop>("Removed Chiller Chilled Water Loop"));
  ASSERT_TRUE(reloadedChiller->chilledWaterLoop());
  ASSERT_TRUE(reloadedChiller->condenserWaterLoop());
  ASSERT_TRUE(reloadedChiller->heatRecoveryLoop());
  EXPECT_EQ(*reloadedChilledWaterLoop, *reloadedChiller->chilledWaterLoop());
  EXPECT_EQ(*reloadedCondenserWaterLoop, *reloadedChiller->condenserWaterLoop());
  EXPECT_EQ(*reloadedHeatRecoveryLoop, *reloadedChiller->heatRecoveryLoop());
  EXPECT_EQ(1u, reloadedChilledWaterLoop->supplyComponents(ChillerElectricEIR::iddObjectType()).size());
  EXPECT_EQ(1u, reloadedCondenserWaterLoop->demandComponents(ChillerElectricEIR::iddObjectType()).size());
  EXPECT_EQ(1u, reloadedHeatRecoveryLoop->demandComponents(ChillerElectricEIR::iddObjectType()).size());
  EXPECT_TRUE(reloadedChiller->chilledWaterInletNode());
  EXPECT_TRUE(reloadedChiller->chilledWaterOutletNode());
  EXPECT_TRUE(reloadedChiller->condenserInletNode());
  EXPECT_TRUE(reloadedChiller->condenserOutletNode());
  EXPECT_TRUE(reloadedChiller->heatRecoveryInletNode());
  EXPECT_TRUE(reloadedChiller->heatRecoveryOutletNode());
  EXPECT_EQ("WaterCooled", reloadedChiller->condenserType());

  std::vector<openstudio::Handle> condenserWaterTopologyHandles;
  for (const auto& component : reloadedCondenserWaterLoop->supplyComponents()) {
    condenserWaterTopologyHandles.push_back(component.handle());
  }
  for (const auto& component : reloadedCondenserWaterLoop->demandComponents()) {
    if (component.handle() != reloadedChiller->handle()) {
      condenserWaterTopologyHandles.push_back(component.handle());
    }
  }
  const auto condenserWaterLoopHandle = reloadedCondenserWaterLoop->handle();
  const auto condenserWaterSizingHandle = reloadedCondenserWaterLoop->sizingPlant().handle();
  const auto reloadedChillerHandle = reloadedChiller->handle();
  EXPECT_FALSE(reloadedCondenserWaterLoop->remove().empty());
  EXPECT_FALSE(reloadedModel->getObject(condenserWaterLoopHandle));
  EXPECT_FALSE(reloadedModel->getObject(condenserWaterSizingHandle));
  for (const auto& handle : condenserWaterTopologyHandles) {
    EXPECT_FALSE(reloadedModel->getObject(handle));
  }
  EXPECT_TRUE(reloadedModel->getObject(reloadedChillerHandle));
  EXPECT_FALSE(reloadedChiller->condenserWaterLoop());
  EXPECT_FALSE(reloadedChiller->condenserInletNode());
  EXPECT_FALSE(reloadedChiller->condenserOutletNode());
  ASSERT_TRUE(reloadedChiller->chilledWaterLoop());
  ASSERT_TRUE(reloadedChiller->heatRecoveryLoop());
  EXPECT_EQ(*reloadedChilledWaterLoop, *reloadedChiller->chilledWaterLoop());
  EXPECT_EQ(*reloadedHeatRecoveryLoop, *reloadedChiller->heatRecoveryLoop());
  EXPECT_EQ(1u, reloadedChilledWaterLoop->supplyComponents(ChillerElectricEIR::iddObjectType()).size());
  EXPECT_EQ(1u, reloadedHeatRecoveryLoop->demandComponents(ChillerElectricEIR::iddObjectType()).size());
  EXPECT_TRUE(reloadedChiller->chilledWaterInletNode());
  EXPECT_TRUE(reloadedChiller->chilledWaterOutletNode());
  EXPECT_TRUE(reloadedChiller->heatRecoveryInletNode());
  EXPECT_TRUE(reloadedChiller->heatRecoveryOutletNode());
  EXPECT_EQ("AirCooled", reloadedChiller->condenserType());

  PlantLoop replacementCondenserWaterLoop(*reloadedModel);
  ASSERT_TRUE(replacementCondenserWaterLoop.setName("Replacement Chiller Condenser Water Loop"));
  ASSERT_TRUE(replacementCondenserWaterLoop.addDemandBranchForComponent(*reloadedChiller));
  EXPECT_EQ("WaterCooled", reloadedChiller->condenserType());
  ASSERT_TRUE(reloadedModel->save(idfPath, true));

  auto finalModel = Model::load(idfPath);
  ASSERT_TRUE(finalModel);
  auto finalChilledWaterLoop = finalModel->getConcreteModelObjectByName<PlantLoop>("Replacement Chiller Chilled Water Loop");
  auto finalCondenserWaterLoop = finalModel->getConcreteModelObjectByName<PlantLoop>("Replacement Chiller Condenser Water Loop");
  auto finalHeatRecoveryLoop = finalModel->getConcreteModelObjectByName<PlantLoop>("Surviving Chiller Heat Recovery Loop");
  auto finalChiller = finalModel->getConcreteModelObjectByName<ChillerElectricEIR>("Surviving Triple Owner Chiller");
  ASSERT_TRUE(finalChilledWaterLoop);
  ASSERT_TRUE(finalCondenserWaterLoop);
  ASSERT_TRUE(finalHeatRecoveryLoop);
  ASSERT_TRUE(finalChiller);
  EXPECT_FALSE(finalModel->getConcreteModelObjectByName<PlantLoop>("Removed Chiller Chilled Water Loop"));
  EXPECT_FALSE(finalModel->getConcreteModelObjectByName<PlantLoop>("Surviving Chiller Condenser Water Loop"));
  ASSERT_TRUE(finalChiller->chilledWaterLoop());
  ASSERT_TRUE(finalChiller->condenserWaterLoop());
  ASSERT_TRUE(finalChiller->heatRecoveryLoop());
  EXPECT_EQ(*finalChilledWaterLoop, *finalChiller->chilledWaterLoop());
  EXPECT_EQ(*finalCondenserWaterLoop, *finalChiller->condenserWaterLoop());
  EXPECT_EQ(*finalHeatRecoveryLoop, *finalChiller->heatRecoveryLoop());
  EXPECT_EQ(1u, finalChilledWaterLoop->supplyComponents(ChillerElectricEIR::iddObjectType()).size());
  EXPECT_EQ(1u, finalCondenserWaterLoop->demandComponents(ChillerElectricEIR::iddObjectType()).size());
  EXPECT_EQ(1u, finalHeatRecoveryLoop->demandComponents(ChillerElectricEIR::iddObjectType()).size());
  EXPECT_TRUE(finalChiller->chilledWaterInletNode());
  EXPECT_TRUE(finalChiller->chilledWaterOutletNode());
  EXPECT_TRUE(finalChiller->condenserInletNode());
  EXPECT_TRUE(finalChiller->condenserOutletNode());
  EXPECT_TRUE(finalChiller->heatRecoveryInletNode());
  EXPECT_TRUE(finalChiller->heatRecoveryOutletNode());
  EXPECT_EQ("WaterCooled", finalChiller->condenserType());

  std::vector<openstudio::Handle> heatRecoveryTopologyHandles;
  for (const auto& component : finalHeatRecoveryLoop->supplyComponents()) {
    heatRecoveryTopologyHandles.push_back(component.handle());
  }
  for (const auto& component : finalHeatRecoveryLoop->demandComponents()) {
    if (component.handle() != finalChiller->handle()) {
      heatRecoveryTopologyHandles.push_back(component.handle());
    }
  }
  const auto heatRecoveryLoopHandle = finalHeatRecoveryLoop->handle();
  const auto heatRecoverySizingHandle = finalHeatRecoveryLoop->sizingPlant().handle();
  const auto finalChillerHandle = finalChiller->handle();
  EXPECT_FALSE(finalHeatRecoveryLoop->remove().empty());
  EXPECT_FALSE(finalModel->getObject(heatRecoveryLoopHandle));
  EXPECT_FALSE(finalModel->getObject(heatRecoverySizingHandle));
  for (const auto& handle : heatRecoveryTopologyHandles) {
    EXPECT_FALSE(finalModel->getObject(handle));
  }
  ASSERT_TRUE(finalModel->getObject(finalChillerHandle));
  EXPECT_FALSE(finalChiller->heatRecoveryLoop());
  EXPECT_FALSE(finalChiller->heatRecoveryInletNode());
  EXPECT_FALSE(finalChiller->heatRecoveryOutletNode());
  ASSERT_TRUE(finalChiller->chilledWaterLoop());
  ASSERT_TRUE(finalChiller->condenserWaterLoop());
  EXPECT_EQ(*finalChilledWaterLoop, *finalChiller->chilledWaterLoop());
  EXPECT_EQ(*finalCondenserWaterLoop, *finalChiller->condenserWaterLoop());
  EXPECT_EQ(1u, finalChilledWaterLoop->supplyComponents(ChillerElectricEIR::iddObjectType()).size());
  EXPECT_EQ(1u, finalCondenserWaterLoop->demandComponents(ChillerElectricEIR::iddObjectType()).size());
  EXPECT_TRUE(finalChiller->chilledWaterInletNode());
  EXPECT_TRUE(finalChiller->chilledWaterOutletNode());
  EXPECT_TRUE(finalChiller->condenserInletNode());
  EXPECT_TRUE(finalChiller->condenserOutletNode());
  EXPECT_EQ("WaterCooled", finalChiller->condenserType());

  PlantLoop replacementHeatRecoveryLoop(*finalModel);
  ASSERT_TRUE(replacementHeatRecoveryLoop.setName("Replacement Chiller Heat Recovery Loop"));
  ASSERT_TRUE(replacementHeatRecoveryLoop.addDemandBranchForComponent(*finalChiller));
  ASSERT_TRUE(finalModel->save(idfPath, true));

  auto completedModel = Model::load(idfPath);
  ASSERT_TRUE(completedModel);
  auto completedChilledWaterLoop = completedModel->getConcreteModelObjectByName<PlantLoop>("Replacement Chiller Chilled Water Loop");
  auto completedCondenserWaterLoop = completedModel->getConcreteModelObjectByName<PlantLoop>("Replacement Chiller Condenser Water Loop");
  auto completedHeatRecoveryLoop = completedModel->getConcreteModelObjectByName<PlantLoop>("Replacement Chiller Heat Recovery Loop");
  auto completedChiller = completedModel->getConcreteModelObjectByName<ChillerElectricEIR>("Surviving Triple Owner Chiller");
  ASSERT_TRUE(completedChilledWaterLoop);
  ASSERT_TRUE(completedCondenserWaterLoop);
  ASSERT_TRUE(completedHeatRecoveryLoop);
  ASSERT_TRUE(completedChiller);
  EXPECT_FALSE(completedModel->getConcreteModelObjectByName<PlantLoop>("Removed Chiller Chilled Water Loop"));
  EXPECT_FALSE(completedModel->getConcreteModelObjectByName<PlantLoop>("Surviving Chiller Condenser Water Loop"));
  EXPECT_FALSE(completedModel->getConcreteModelObjectByName<PlantLoop>("Surviving Chiller Heat Recovery Loop"));
  ASSERT_TRUE(completedChiller->chilledWaterLoop());
  ASSERT_TRUE(completedChiller->condenserWaterLoop());
  ASSERT_TRUE(completedChiller->heatRecoveryLoop());
  EXPECT_EQ(*completedChilledWaterLoop, *completedChiller->chilledWaterLoop());
  EXPECT_EQ(*completedCondenserWaterLoop, *completedChiller->condenserWaterLoop());
  EXPECT_EQ(*completedHeatRecoveryLoop, *completedChiller->heatRecoveryLoop());
  EXPECT_EQ(1u, completedChilledWaterLoop->supplyComponents(ChillerElectricEIR::iddObjectType()).size());
  EXPECT_EQ(1u, completedCondenserWaterLoop->demandComponents(ChillerElectricEIR::iddObjectType()).size());
  EXPECT_EQ(1u, completedHeatRecoveryLoop->demandComponents(ChillerElectricEIR::iddObjectType()).size());
  EXPECT_TRUE(completedChiller->chilledWaterInletNode());
  EXPECT_TRUE(completedChiller->chilledWaterOutletNode());
  EXPECT_TRUE(completedChiller->condenserInletNode());
  EXPECT_TRUE(completedChiller->condenserOutletNode());
  EXPECT_TRUE(completedChiller->heatRecoveryInletNode());
  EXPECT_TRUE(completedChiller->heatRecoveryOutletNode());
  EXPECT_EQ("WaterCooled", completedChiller->condenserType());

  openstudio::filesystem::remove(idfPath);
}
