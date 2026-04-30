/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Curve/CurveBiquadratic.hpp"
#include "../Curve/CurveBiquadratic_Impl.hpp"
#include "../Curve/CurveQuadratic.hpp"
#include "../Curve/CurveQuadratic_Impl.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../StraightComponent/Node.hpp"
#include "../WaterToWaterComponent/HeatPumpPlantLoopEIRCooling.hpp"
#include "../WaterToWaterComponent/HeatPumpPlantLoopEIRHeating.hpp"
#include "../WaterToWaterComponent/HeatPumpPlantLoopEIRHeating_Impl.hpp"

#include <limits>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, HeatPumpPlantLoopEIRHeating_DefaultConstructor) {
  Model model;
  HeatPumpPlantLoopEIRHeating hp(model);

  EXPECT_EQ(HeatPumpPlantLoopEIRHeating::iddObjectType(), hp.iddObject().type());
  EXPECT_NE(std::numeric_limits<unsigned>::max(), hp.supplyInletPort());
  EXPECT_NE(std::numeric_limits<unsigned>::max(), hp.demandInletPort());
  EXPECT_NE(std::numeric_limits<unsigned>::max(), hp.tertiaryInletPort());
  EXPECT_EQ("AirSource", hp.condenserType());

  EXPECT_TRUE(hp.isLoadSideReferenceFlowRateAutosized());
  EXPECT_TRUE(hp.isSourceSideReferenceFlowRateAutosized());
  EXPECT_TRUE(hp.isHeatRecoveryReferenceFlowRateAutosized());
  EXPECT_TRUE(hp.isReferenceCapacityAutosized());

  EXPECT_FALSE(hp.loadSideReferenceFlowRate());
  EXPECT_FALSE(hp.sourceSideReferenceFlowRate());
  EXPECT_FALSE(hp.heatRecoveryReferenceFlowRate());
  EXPECT_FALSE(hp.referenceCapacity());

  EXPECT_EQ(CurveBiquadratic::iddObjectType(), hp.capacityModifierFunctionofTemperatureCurve().iddObject().type());
  EXPECT_EQ(CurveBiquadratic::iddObjectType(), hp.electricInputtoOutputRatioModifierFunctionofTemperatureCurve().iddObject().type());
  EXPECT_EQ(CurveQuadratic::iddObjectType(), hp.electricInputtoOutputRatioModifierFunctionofPartLoadRatioCurve().iddObject().type());
  EXPECT_FALSE(hp.companionCoolingHeatPump());
  EXPECT_FALSE(hp.minimumSupplyWaterTemperatureCurve());
  EXPECT_FALSE(hp.maximumSupplyWaterTemperatureCurve());
  EXPECT_FALSE(hp.dryOutdoorCorrectionFactorCurve());
  EXPECT_FALSE(hp.defrostEnergyInputRatioFunctionofTemperatureCurve());
  EXPECT_FALSE(hp.timedEmpiricalDefrostFrequencyCurve());
  EXPECT_FALSE(hp.timedEmpiricalDefrostHeatLoadPenaltyCurve());
  EXPECT_FALSE(hp.timedEmpiricalDefrostHeatInputEnergyFractionCurve());
  EXPECT_FALSE(hp.heatRecoveryCapacityModifierFunctionofTemperatureCurve());
  EXPECT_FALSE(hp.heatRecoveryElectricInputtoOutputRatioModifierFunctionofTemperatureCurve());

  EXPECT_FALSE(hp.loadSideWaterLoop());
  EXPECT_FALSE(hp.sourceSideWaterLoop());
  EXPECT_FALSE(hp.heatRecoveryLoop());
  EXPECT_FALSE(hp.loadSideWaterInletNode());
  EXPECT_FALSE(hp.loadSideWaterOutletNode());
  EXPECT_FALSE(hp.sourceSideWaterInletNode());
  EXPECT_FALSE(hp.sourceSideWaterOutletNode());
  EXPECT_FALSE(hp.heatRecoveryInletNode());
  EXPECT_FALSE(hp.heatRecoveryOutletNode());

  EXPECT_DOUBLE_EQ(7.5, hp.referenceCoefficientofPerformance());
  EXPECT_DOUBLE_EQ(1.0, hp.sizingFactor());
  EXPECT_DOUBLE_EQ(1.0, hp.heatingToCoolingCapacitySizingRatio());
  EXPECT_EQ("CoolingCapacity", hp.heatPumpSizingMethod());
  EXPECT_EQ("Load", hp.controlType());
  EXPECT_EQ("ConstantFlow", hp.flowMode());
  EXPECT_DOUBLE_EQ(0.0, hp.minimumPartLoadRatio());
  EXPECT_DOUBLE_EQ(-100.0, hp.minimumSourceInletTemperature());
  EXPECT_DOUBLE_EQ(100.0, hp.maximumSourceInletTemperature());
  EXPECT_DOUBLE_EQ(10.0, hp.maximumOutdoorDryBulbTemperatureForDefrostOperation());
  EXPECT_EQ("None", hp.heatPumpDefrostControl());
  EXPECT_DOUBLE_EQ(0.058333, hp.heatPumpDefrostTimePeriodFraction());
  EXPECT_DOUBLE_EQ(4.5, hp.minimumHeatRecoveryOutletTemperature());
}

TEST_F(EPModelFixture, HeatPumpPlantLoopEIRHeating_CurveConstructorAndSetters) {
  Model model;
  CurveBiquadratic capacityCurve(model);
  CurveBiquadratic eirFT(model);
  CurveQuadratic eirFPLR(model);

  HeatPumpPlantLoopEIRHeating hp(model, capacityCurve, eirFT, eirFPLR);
  EXPECT_EQ(capacityCurve, hp.capacityModifierFunctionofTemperatureCurve());
  EXPECT_EQ(eirFT, hp.electricInputtoOutputRatioModifierFunctionofTemperatureCurve());
  EXPECT_EQ(eirFPLR, hp.electricInputtoOutputRatioModifierFunctionofPartLoadRatioCurve());

  CurveBiquadratic replacementCapacity(model);
  CurveBiquadratic replacementEirFT(model);
  CurveQuadratic replacementEirFPLR(model);
  CurveQuadratic minSupply(model);
  CurveQuadratic maxSupply(model);
  CurveQuadratic dryOutdoor(model);
  CurveBiquadratic defrostEir(model);
  CurveQuadratic defrostFrequency(model);
  CurveQuadratic defrostPenalty(model);
  CurveQuadratic defrostEnergyFraction(model);
  CurveBiquadratic heatRecoveryCapacity(model);
  CurveBiquadratic heatRecoveryEir(model);

  EXPECT_TRUE(hp.setCapacityModifierFunctionofTemperatureCurve(replacementCapacity));
  EXPECT_TRUE(hp.setElectricInputtoOutputRatioModifierFunctionofTemperatureCurve(replacementEirFT));
  EXPECT_TRUE(hp.setElectricInputtoOutputRatioModifierFunctionofPartLoadRatioCurve(replacementEirFPLR));
  EXPECT_TRUE(hp.setMinimumSupplyWaterTemperatureCurve(minSupply));
  EXPECT_TRUE(hp.setMaximumSupplyWaterTemperatureCurve(maxSupply));
  EXPECT_TRUE(hp.setDryOutdoorCorrectionFactorCurve(dryOutdoor));
  EXPECT_TRUE(hp.setDefrostEnergyInputRatioFunctionofTemperatureCurve(defrostEir));
  EXPECT_TRUE(hp.setTimedEmpiricalDefrostFrequencyCurve(defrostFrequency));
  EXPECT_TRUE(hp.setTimedEmpiricalDefrostHeatLoadPenaltyCurve(defrostPenalty));
  EXPECT_TRUE(hp.setTimedEmpiricalDefrostHeatInputEnergyFractionCurve(defrostEnergyFraction));
  EXPECT_TRUE(hp.setHeatRecoveryCapacityModifierFunctionofTemperatureCurve(heatRecoveryCapacity));
  EXPECT_TRUE(hp.setHeatRecoveryElectricInputtoOutputRatioModifierFunctionofTemperatureCurve(heatRecoveryEir));

  EXPECT_EQ(replacementCapacity, hp.capacityModifierFunctionofTemperatureCurve());
  EXPECT_EQ(replacementEirFT, hp.electricInputtoOutputRatioModifierFunctionofTemperatureCurve());
  EXPECT_EQ(replacementEirFPLR, hp.electricInputtoOutputRatioModifierFunctionofPartLoadRatioCurve());
  ASSERT_TRUE(hp.minimumSupplyWaterTemperatureCurve());
  EXPECT_EQ(minSupply, hp.minimumSupplyWaterTemperatureCurve().get());
  ASSERT_TRUE(hp.maximumSupplyWaterTemperatureCurve());
  EXPECT_EQ(maxSupply, hp.maximumSupplyWaterTemperatureCurve().get());
  ASSERT_TRUE(hp.dryOutdoorCorrectionFactorCurve());
  EXPECT_EQ(dryOutdoor, hp.dryOutdoorCorrectionFactorCurve().get());
  ASSERT_TRUE(hp.defrostEnergyInputRatioFunctionofTemperatureCurve());
  EXPECT_EQ(defrostEir, hp.defrostEnergyInputRatioFunctionofTemperatureCurve().get());
  ASSERT_TRUE(hp.timedEmpiricalDefrostFrequencyCurve());
  EXPECT_EQ(defrostFrequency, hp.timedEmpiricalDefrostFrequencyCurve().get());
  ASSERT_TRUE(hp.timedEmpiricalDefrostHeatLoadPenaltyCurve());
  EXPECT_EQ(defrostPenalty, hp.timedEmpiricalDefrostHeatLoadPenaltyCurve().get());
  ASSERT_TRUE(hp.timedEmpiricalDefrostHeatInputEnergyFractionCurve());
  EXPECT_EQ(defrostEnergyFraction, hp.timedEmpiricalDefrostHeatInputEnergyFractionCurve().get());
  ASSERT_TRUE(hp.heatRecoveryCapacityModifierFunctionofTemperatureCurve());
  EXPECT_EQ(heatRecoveryCapacity, hp.heatRecoveryCapacityModifierFunctionofTemperatureCurve().get());
  ASSERT_TRUE(hp.heatRecoveryElectricInputtoOutputRatioModifierFunctionofTemperatureCurve());
  EXPECT_EQ(heatRecoveryEir, hp.heatRecoveryElectricInputtoOutputRatioModifierFunctionofTemperatureCurve().get());

  hp.resetMinimumSupplyWaterTemperatureCurve();
  hp.resetMaximumSupplyWaterTemperatureCurve();
  hp.resetDryOutdoorCorrectionFactorCurve();
  hp.resetDefrostEnergyInputRatioFunctionofTemperatureCurve();
  hp.resetTimedEmpiricalDefrostFrequencyCurve();
  hp.resetTimedEmpiricalDefrostHeatLoadPenaltyCurve();
  hp.resetTimedEmpiricalDefrostHeatInputEnergyFractionCurve();
  hp.resetHeatRecoveryCapacityModifierFunctionofTemperatureCurve();
  hp.resetHeatRecoveryElectricInputtoOutputRatioModifierFunctionofTemperatureCurve();

  EXPECT_FALSE(hp.minimumSupplyWaterTemperatureCurve());
  EXPECT_FALSE(hp.maximumSupplyWaterTemperatureCurve());
  EXPECT_FALSE(hp.dryOutdoorCorrectionFactorCurve());
  EXPECT_FALSE(hp.defrostEnergyInputRatioFunctionofTemperatureCurve());
  EXPECT_FALSE(hp.timedEmpiricalDefrostFrequencyCurve());
  EXPECT_FALSE(hp.timedEmpiricalDefrostHeatLoadPenaltyCurve());
  EXPECT_FALSE(hp.timedEmpiricalDefrostHeatInputEnergyFractionCurve());
  EXPECT_FALSE(hp.heatRecoveryCapacityModifierFunctionofTemperatureCurve());
  EXPECT_FALSE(hp.heatRecoveryElectricInputtoOutputRatioModifierFunctionofTemperatureCurve());
}

TEST_F(EPModelFixture, HeatPumpPlantLoopEIRHeating_CompanionCoolingHeatPumpRoundTrip) {
  Model model;
  HeatPumpPlantLoopEIRCooling cooling(model);
  HeatPumpPlantLoopEIRHeating heating(model);

  EXPECT_FALSE(heating.companionCoolingHeatPump());
  EXPECT_TRUE(heating.setCompanionCoolingHeatPump(cooling));
  ASSERT_TRUE(heating.companionCoolingHeatPump());
  EXPECT_EQ(cooling, heating.companionCoolingHeatPump().get());
}

TEST_F(EPModelFixture, HeatPumpPlantLoopEIRHeating_Remove) {
  Model model;
  HeatPumpPlantLoopEIRHeating hp(model);

  const auto initialObjects = model.objects().size();
  EXPECT_FALSE(hp.remove().empty());
  EXPECT_EQ(initialObjects - 1, model.objects().size());
  EXPECT_TRUE(model.getModelObjects<HeatPumpPlantLoopEIRHeating>().empty());
}

TEST_F(EPModelFixture, HeatPumpPlantLoopEIRHeating_Clone) {
  Model model;
  CurveBiquadratic capacityCurve(model);
  CurveBiquadratic eirFT(model);
  CurveQuadratic eirFPLR(model);

  HeatPumpPlantLoopEIRHeating hp(model, capacityCurve, eirFT, eirFPLR);
  EXPECT_EQ(2u, model.getModelObjects<CurveBiquadratic>().size());
  EXPECT_EQ(1u, model.getModelObjects<CurveQuadratic>().size());

  {
    auto hpCloneObject = model.addObject(hp.idfObject());
    ASSERT_TRUE(hpCloneObject);
    auto hpClone = hpCloneObject->cast<HeatPumpPlantLoopEIRHeating>();
    EXPECT_EQ(capacityCurve, hpClone.capacityModifierFunctionofTemperatureCurve());
    EXPECT_EQ(eirFT, hpClone.electricInputtoOutputRatioModifierFunctionofTemperatureCurve());
    EXPECT_EQ(eirFPLR, hpClone.electricInputtoOutputRatioModifierFunctionofPartLoadRatioCurve());
    EXPECT_EQ(2u, model.getModelObjects<CurveBiquadratic>().size());
    EXPECT_EQ(1u, model.getModelObjects<CurveQuadratic>().size());
  }

  {
    Model model2;
    const auto hpIdfObject = hp.idfObject();
    const auto hpCloneObjects = model2.addObjects({capacityCurve.idfObject(), eirFT.idfObject(), eirFPLR.idfObject(), hpIdfObject});
    ASSERT_EQ(4u, hpCloneObjects.size());
    auto hpClones = model2.getModelObjects<HeatPumpPlantLoopEIRHeating>();
    ASSERT_EQ(1u, hpClones.size());
    auto hpClone = hpClones.front();
    EXPECT_EQ(CurveBiquadratic::iddObjectType(), hpClone.capacityModifierFunctionofTemperatureCurve().iddObject().type());
    EXPECT_EQ(CurveBiquadratic::iddObjectType(), hpClone.electricInputtoOutputRatioModifierFunctionofTemperatureCurve().iddObject().type());
    EXPECT_EQ(CurveQuadratic::iddObjectType(), hpClone.electricInputtoOutputRatioModifierFunctionofPartLoadRatioCurve().iddObject().type());
    EXPECT_EQ(2u, model2.getModelObjects<CurveBiquadratic>().size());
    EXPECT_EQ(1u, model2.getModelObjects<CurveQuadratic>().size());
  }
}

TEST_F(EPModelFixture, HeatPumpPlantLoopEIRHeating_ScalarAccessors_RoundTrip) {
  Model model;
  HeatPumpPlantLoopEIRHeating hp(model);

  const auto condenserTypes = HeatPumpPlantLoopEIRHeating::condenserTypeValues();
  ASSERT_FALSE(condenserTypes.empty());
  EXPECT_TRUE(hp.setCondenserType("AirSource"));
  EXPECT_FALSE(hp.setCondenserType("WaterSource"));
  EXPECT_EQ("AirSource", hp.condenserType());

  EXPECT_TRUE(hp.setLoadSideReferenceFlowRate(0.101));
  ASSERT_TRUE(hp.loadSideReferenceFlowRate());
  EXPECT_DOUBLE_EQ(0.101, *hp.loadSideReferenceFlowRate());
  hp.autosizeLoadSideReferenceFlowRate();
  EXPECT_TRUE(hp.isLoadSideReferenceFlowRateAutosized());

  EXPECT_TRUE(hp.setSourceSideReferenceFlowRate(0.202));
  ASSERT_TRUE(hp.sourceSideReferenceFlowRate());
  EXPECT_DOUBLE_EQ(0.202, *hp.sourceSideReferenceFlowRate());
  hp.autosizeSourceSideReferenceFlowRate();
  EXPECT_TRUE(hp.isSourceSideReferenceFlowRateAutosized());

  EXPECT_TRUE(hp.setHeatRecoveryReferenceFlowRate(0.303));
  ASSERT_TRUE(hp.heatRecoveryReferenceFlowRate());
  EXPECT_DOUBLE_EQ(0.303, *hp.heatRecoveryReferenceFlowRate());
  hp.autosizeHeatRecoveryReferenceFlowRate();
  EXPECT_TRUE(hp.isHeatRecoveryReferenceFlowRateAutosized());

  EXPECT_TRUE(hp.setReferenceCapacity(12450.0));
  ASSERT_TRUE(hp.referenceCapacity());
  EXPECT_DOUBLE_EQ(12450.0, *hp.referenceCapacity());
  hp.autosizeReferenceCapacity();
  EXPECT_TRUE(hp.isReferenceCapacityAutosized());

  EXPECT_TRUE(hp.setReferenceCoefficientofPerformance(6.9));
  EXPECT_DOUBLE_EQ(6.9, hp.referenceCoefficientofPerformance());

  EXPECT_TRUE(hp.setSizingFactor(1.2));
  EXPECT_DOUBLE_EQ(1.2, hp.sizingFactor());

  EXPECT_TRUE(hp.setHeatingToCoolingCapacitySizingRatio(1.08));
  EXPECT_DOUBLE_EQ(1.08, hp.heatingToCoolingCapacitySizingRatio());

  EXPECT_TRUE(hp.setHeatPumpSizingMethod("CoolingCapacity"));
  EXPECT_EQ("CoolingCapacity", hp.heatPumpSizingMethod());

  EXPECT_TRUE(hp.setControlType("Setpoint"));
  EXPECT_EQ("Setpoint", hp.controlType());

  EXPECT_TRUE(hp.setFlowMode("VariableSpeedPumping"));
  EXPECT_EQ("VariableSpeedPumping", hp.flowMode());

  EXPECT_TRUE(hp.setMinimumPartLoadRatio(0.25));
  EXPECT_DOUBLE_EQ(0.25, hp.minimumPartLoadRatio());

  EXPECT_TRUE(hp.setMinimumSourceInletTemperature(-9.0));
  EXPECT_DOUBLE_EQ(-9.0, hp.minimumSourceInletTemperature());

  EXPECT_TRUE(hp.setMaximumSourceInletTemperature(77.0));
  EXPECT_DOUBLE_EQ(77.0, hp.maximumSourceInletTemperature());

  EXPECT_TRUE(hp.setMaximumOutdoorDryBulbTemperatureForDefrostOperation(5.0));
  EXPECT_DOUBLE_EQ(5.0, hp.maximumOutdoorDryBulbTemperatureForDefrostOperation());

  EXPECT_TRUE(hp.setHeatPumpDefrostControl("None"));
  EXPECT_EQ("None", hp.heatPumpDefrostControl());

  EXPECT_TRUE(hp.setHeatPumpDefrostTimePeriodFraction(0.08));
  EXPECT_DOUBLE_EQ(0.08, hp.heatPumpDefrostTimePeriodFraction());

  EXPECT_TRUE(hp.setMinimumHeatRecoveryOutletTemperature(6.0));
  EXPECT_DOUBLE_EQ(6.0, hp.minimumHeatRecoveryOutletTemperature());
}

TEST_F(EPModelFixture, HeatPumpPlantLoopEIRHeating_PlantLoopAttachmentParity) {
  Model model;
  PlantLoop loadLoop(model);
  PlantLoop sourceLoop(model);
  PlantLoop heatRecoveryLoop(model);
  HeatPumpPlantLoopEIRHeating hp(model);

  EXPECT_TRUE(loadLoop.addSupplyBranchForComponent(hp));
  ASSERT_TRUE(hp.loadSideWaterLoop());
  EXPECT_EQ(loadLoop.handle(), hp.loadSideWaterLoop()->handle());
  ASSERT_TRUE(hp.loadSideWaterInletNode());
  EXPECT_EQ(hp.supplyInletModelObject()->cast<Node>(), hp.loadSideWaterInletNode().get());
  ASSERT_TRUE(hp.loadSideWaterOutletNode());
  EXPECT_EQ(hp.supplyOutletModelObject()->cast<Node>(), hp.loadSideWaterOutletNode().get());

  EXPECT_TRUE(sourceLoop.addDemandBranchForComponent(hp));
  ASSERT_TRUE(hp.sourceSideWaterLoop());
  EXPECT_EQ(sourceLoop.handle(), hp.sourceSideWaterLoop()->handle());
  EXPECT_EQ("WaterSource", hp.condenserType());
  EXPECT_FALSE(hp.setCondenserType("AirSource"));
  ASSERT_TRUE(hp.sourceSideWaterInletNode());
  EXPECT_EQ(hp.demandInletModelObject()->cast<Node>(), hp.sourceSideWaterInletNode().get());
  ASSERT_TRUE(hp.sourceSideWaterOutletNode());
  EXPECT_EQ(hp.demandOutletModelObject()->cast<Node>(), hp.sourceSideWaterOutletNode().get());

  boost::optional<Node> heatRecoveryNode;
  for (const auto& component : heatRecoveryLoop.demandComponents()) {
    if (auto node = component.optionalCast<Node>()) {
      heatRecoveryNode = *node;
      break;
    }
  }
  ASSERT_TRUE(heatRecoveryNode);
  EXPECT_TRUE(hp.addToNode(*heatRecoveryNode));
  ASSERT_TRUE(hp.heatRecoveryLoop());
  EXPECT_EQ(heatRecoveryLoop.handle(), hp.heatRecoveryLoop()->handle());
  ASSERT_TRUE(hp.heatRecoveryInletNode());
  EXPECT_EQ(hp.tertiaryInletModelObject()->cast<Node>(), hp.heatRecoveryInletNode().get());
  ASSERT_TRUE(hp.heatRecoveryOutletNode());
  EXPECT_EQ(hp.tertiaryOutletModelObject()->cast<Node>(), hp.heatRecoveryOutletNode().get());

  auto loadSupplyOutletNode = loadLoop.supplyOutletNode();
  EXPECT_FALSE(hp.addToTertiaryNode(loadSupplyOutletNode));

  EXPECT_TRUE(hp.removeFromSecondaryPlantLoop());
  EXPECT_EQ("AirSource", hp.condenserType());
  EXPECT_FALSE(hp.sourceSideWaterLoop());
  EXPECT_FALSE(hp.sourceSideWaterInletNode());
  EXPECT_FALSE(hp.sourceSideWaterOutletNode());
  EXPECT_FALSE(hp.demandInletModelObject());
  EXPECT_FALSE(hp.demandOutletModelObject());
  EXPECT_FALSE(hp.setCondenserType("WaterSource"));
}
