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
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"
#include "../StraightComponent/HeatPumpAirToWaterFuelFiredCooling.hpp"
#include "../StraightComponent/HeatPumpAirToWaterFuelFiredCooling_Impl.hpp"
#include "../StraightComponent/HeatPumpAirToWaterFuelFiredHeating.hpp"
#include "../StraightComponent/HeatPumpAirToWaterFuelFiredHeating_Impl.hpp"
#include "../StraightComponent/Node.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, HeatPumpAirToWaterFuelFiredHeating_DefaultConstructor) {
  Model model;
  HeatPumpAirToWaterFuelFiredHeating hp(model);

  EXPECT_EQ(HeatPumpAirToWaterFuelFiredHeating::iddObjectType(), hp.iddObject().type());
  EXPECT_FALSE(hp.nameString().empty());

  EXPECT_FALSE(hp.companionCoolingHeatPump());
  EXPECT_EQ("NaturalGas", hp.fuelType());
  EXPECT_EQ("General", hp.endUseSubcategory());
  EXPECT_TRUE(hp.isEndUseSubcategoryDefaulted());
  EXPECT_TRUE(hp.isNominalHeatingCapacityAutosized());
  EXPECT_DOUBLE_EQ(1.0, hp.nominalCOP());
  EXPECT_TRUE(hp.isDesignFlowRateAutosized());
  EXPECT_DOUBLE_EQ(60.0, hp.designSupplyTemperature());
  ASSERT_TRUE(hp.designTemperatureLift());
  EXPECT_DOUBLE_EQ(11.1, hp.designTemperatureLift().get());
  EXPECT_FALSE(hp.isDesignTemperatureLiftAutosized());
  EXPECT_DOUBLE_EQ(1.0, hp.sizingFactor());
  EXPECT_EQ("NotModulated", hp.flowMode());
  EXPECT_EQ("DryBulb", hp.outdoorAirTemperatureCurveInputVariable());
  EXPECT_EQ("EnteringCondenser", hp.waterTemperatureCurveInputVariable());
  EXPECT_DOUBLE_EQ(0.1, hp.minimumPartLoadRatio());
  EXPECT_DOUBLE_EQ(1.0, hp.maximumPartLoadRatio());
  EXPECT_EQ("Timed", hp.defrostControlType());
  EXPECT_DOUBLE_EQ(0.0, hp.defrostOperationTimeFraction());
  EXPECT_FALSE(hp.fuelEnergyInputRatioDefrostAdjustmentCurve());
  EXPECT_DOUBLE_EQ(0.0, hp.resistiveDefrostHeaterCapacity());
  EXPECT_DOUBLE_EQ(5.0, hp.maximumOutdoorDrybulbTemperatureforDefrostOperation());
  EXPECT_FALSE(hp.cyclingRatioFactorCurve());
  EXPECT_DOUBLE_EQ(0.0, hp.nominalAuxiliaryElectricPower());
  EXPECT_FALSE(hp.auxiliaryElectricEnergyInputRatioFunctionofTemperatureCurve());
  EXPECT_FALSE(hp.auxiliaryElectricEnergyInputRatioFunctionofPLRCurve());
  EXPECT_DOUBLE_EQ(0.0, hp.standbyElectricPower());
  EXPECT_DOUBLE_EQ(0.25, hp.minimumUnloadingRatio());

  auto normalizedCapacityCurve = hp.normalizedCapacityFunctionofTemperatureCurve().cast<CurveBiquadratic>();
  EXPECT_EQ("GAHP Heating CapFT", normalizedCapacityCurve.nameString());
  EXPECT_DOUBLE_EQ(1.0, normalizedCapacityCurve.coefficient1Constant());
  EXPECT_DOUBLE_EQ(5.0, normalizedCapacityCurve.minimumValueofx());
  EXPECT_DOUBLE_EQ(35.0, normalizedCapacityCurve.maximumValueofy());

  auto eirFT = hp.fuelEnergyInputRatioFunctionofTemperatureCurve().cast<CurveBiquadratic>();
  EXPECT_EQ("GAHP Heating EIRFT", eirFT.nameString());
  EXPECT_DOUBLE_EQ(1.0, eirFT.coefficient1Constant());
  EXPECT_DOUBLE_EQ(24.0, eirFT.minimumValueofy());

  auto eirFPLR = hp.fuelEnergyInputRatioFunctionofPLRCurve().cast<CurveQuadratic>();
  EXPECT_EQ("GAHP Heating EIRFPLR", eirFPLR.nameString());
  EXPECT_DOUBLE_EQ(1.0, eirFPLR.coefficient1Constant());
  EXPECT_DOUBLE_EQ(1.0, eirFPLR.maximumValueofx());
}

TEST_F(EPModelFixture, HeatPumpAirToWaterFuelFiredHeating_RelationshipAndScalarAccessors_RoundTrip) {
  Model model;
  HeatPumpAirToWaterFuelFiredHeating hp(model);

  HeatPumpAirToWaterFuelFiredCooling companion(model);
  EXPECT_TRUE(hp.setCompanionCoolingHeatPump(companion));
  ASSERT_TRUE(hp.companionCoolingHeatPump());
  EXPECT_EQ(companion.handle(), hp.companionCoolingHeatPump()->handle());

  Model otherModel;
  HeatPumpAirToWaterFuelFiredCooling foreignCompanion(otherModel);
  EXPECT_FALSE(hp.setCompanionCoolingHeatPump(foreignCompanion));
  ASSERT_TRUE(hp.companionCoolingHeatPump());
  EXPECT_EQ(companion.handle(), hp.companionCoolingHeatPump()->handle());
  hp.resetCompanionCoolingHeatPump();
  EXPECT_FALSE(hp.companionCoolingHeatPump());

  EXPECT_TRUE(hp.setEndUseSubcategory("Process"));
  EXPECT_EQ("Process", hp.endUseSubcategory());
  hp.resetEndUseSubcategory();
  EXPECT_TRUE(hp.isEndUseSubcategoryDefaulted());

  EXPECT_TRUE(hp.setNominalHeatingCapacity(15000.0));
  ASSERT_TRUE(hp.nominalHeatingCapacity());
  EXPECT_DOUBLE_EQ(15000.0, hp.nominalHeatingCapacity().get());
  hp.autosizeNominalHeatingCapacity();
  EXPECT_TRUE(hp.isNominalHeatingCapacityAutosized());
  hp.resetNominalHeatingCapacity();
  EXPECT_FALSE(hp.nominalHeatingCapacity());

  EXPECT_TRUE(hp.setNominalCOP(1.45));
  EXPECT_DOUBLE_EQ(1.45, hp.nominalCOP());

  EXPECT_TRUE(hp.setDesignFlowRate(0.020));
  ASSERT_TRUE(hp.designFlowRate());
  EXPECT_DOUBLE_EQ(0.020, hp.designFlowRate().get());
  hp.autosizeDesignFlowRate();
  EXPECT_TRUE(hp.isDesignFlowRateAutosized());
  hp.resetDesignFlowRate();
  EXPECT_FALSE(hp.designFlowRate());

  EXPECT_TRUE(hp.setDesignSupplyTemperature(55.0));
  EXPECT_DOUBLE_EQ(55.0, hp.designSupplyTemperature());

  EXPECT_TRUE(hp.setDesignTemperatureLift(10.0));
  ASSERT_TRUE(hp.designTemperatureLift());
  EXPECT_DOUBLE_EQ(10.0, hp.designTemperatureLift().get());
  hp.autosizeDesignTemperatureLift();
  EXPECT_TRUE(hp.isDesignTemperatureLiftAutosized());

  EXPECT_TRUE(hp.setSizingFactor(1.15));
  EXPECT_DOUBLE_EQ(1.15, hp.sizingFactor());

  const auto fuelTypeValues = HeatPumpAirToWaterFuelFiredHeating::fuelTypeValues();
  ASSERT_FALSE(fuelTypeValues.empty());
  EXPECT_TRUE(hp.setFuelType(fuelTypeValues.front()));
  EXPECT_EQ(fuelTypeValues.front(), hp.fuelType());

  const auto flowModeValues = HeatPumpAirToWaterFuelFiredHeating::flowModeValues();
  ASSERT_FALSE(flowModeValues.empty());
  EXPECT_TRUE(hp.setFlowMode(flowModeValues.front()));
  EXPECT_EQ(flowModeValues.front(), hp.flowMode());

  const auto outdoorCurveInputValues = HeatPumpAirToWaterFuelFiredHeating::outdoorAirTemperatureCurveInputVariableValues();
  ASSERT_FALSE(outdoorCurveInputValues.empty());
  EXPECT_TRUE(hp.setOutdoorAirTemperatureCurveInputVariable(outdoorCurveInputValues.front()));
  EXPECT_EQ(outdoorCurveInputValues.front(), hp.outdoorAirTemperatureCurveInputVariable());

  const auto waterCurveInputValues = HeatPumpAirToWaterFuelFiredHeating::waterTemperatureCurveInputVariableValues();
  ASSERT_FALSE(waterCurveInputValues.empty());
  EXPECT_TRUE(hp.setWaterTemperatureCurveInputVariable(waterCurveInputValues.front()));
  EXPECT_EQ(waterCurveInputValues.front(), hp.waterTemperatureCurveInputVariable());

  CurveBiquadratic normalizedCapacityCurve(model);
  CurveBiquadratic eirFT(model);
  CurveQuadratic eirFPLR(model);
  EXPECT_TRUE(hp.setNormalizedCapacityFunctionofTemperatureCurve(normalizedCapacityCurve));
  EXPECT_TRUE(hp.setFuelEnergyInputRatioFunctionofTemperatureCurve(eirFT));
  EXPECT_TRUE(hp.setFuelEnergyInputRatioFunctionofPLRCurve(eirFPLR));
  EXPECT_EQ(normalizedCapacityCurve.handle(), hp.normalizedCapacityFunctionofTemperatureCurve().handle());
  EXPECT_EQ(eirFT.handle(), hp.fuelEnergyInputRatioFunctionofTemperatureCurve().handle());
  EXPECT_EQ(eirFPLR.handle(), hp.fuelEnergyInputRatioFunctionofPLRCurve().handle());

  Model foreignCurveModel;
  CurveBiquadratic foreignBiquadratic(foreignCurveModel);
  CurveQuadratic foreignQuadratic(foreignCurveModel);
  EXPECT_FALSE(hp.setNormalizedCapacityFunctionofTemperatureCurve(foreignBiquadratic));
  EXPECT_FALSE(hp.setFuelEnergyInputRatioFunctionofTemperatureCurve(foreignBiquadratic));
  EXPECT_FALSE(hp.setFuelEnergyInputRatioFunctionofPLRCurve(foreignQuadratic));
  EXPECT_EQ(normalizedCapacityCurve.handle(), hp.normalizedCapacityFunctionofTemperatureCurve().handle());
  EXPECT_EQ(eirFT.handle(), hp.fuelEnergyInputRatioFunctionofTemperatureCurve().handle());
  EXPECT_EQ(eirFPLR.handle(), hp.fuelEnergyInputRatioFunctionofPLRCurve().handle());

  EXPECT_TRUE(hp.setMinimumPartLoadRatio(0.2));
  EXPECT_DOUBLE_EQ(0.2, hp.minimumPartLoadRatio());

  EXPECT_TRUE(hp.setMaximumPartLoadRatio(0.95));
  EXPECT_DOUBLE_EQ(0.95, hp.maximumPartLoadRatio());

  const auto defrostControlTypeValues = HeatPumpAirToWaterFuelFiredHeating::defrostControlTypeValues();
  ASSERT_FALSE(defrostControlTypeValues.empty());
  EXPECT_TRUE(hp.setDefrostControlType(defrostControlTypeValues.front()));
  EXPECT_EQ(defrostControlTypeValues.front(), hp.defrostControlType());

  EXPECT_TRUE(hp.setDefrostOperationTimeFraction(0.15));
  EXPECT_DOUBLE_EQ(0.15, hp.defrostOperationTimeFraction());

  CurveQuadratic defrostCurve(model);
  EXPECT_TRUE(hp.setFuelEnergyInputRatioDefrostAdjustmentCurve(defrostCurve));
  ASSERT_TRUE(hp.fuelEnergyInputRatioDefrostAdjustmentCurve());
  EXPECT_EQ(defrostCurve.handle(), hp.fuelEnergyInputRatioDefrostAdjustmentCurve()->handle());
  EXPECT_FALSE(hp.setFuelEnergyInputRatioDefrostAdjustmentCurve(foreignQuadratic));
  hp.resetFuelEnergyInputRatioDefrostAdjustmentCurve();
  EXPECT_FALSE(hp.fuelEnergyInputRatioDefrostAdjustmentCurve());

  EXPECT_TRUE(hp.setResistiveDefrostHeaterCapacity(500.0));
  EXPECT_DOUBLE_EQ(500.0, hp.resistiveDefrostHeaterCapacity());

  EXPECT_TRUE(hp.setMaximumOutdoorDrybulbTemperatureforDefrostOperation(3.0));
  EXPECT_DOUBLE_EQ(3.0, hp.maximumOutdoorDrybulbTemperatureforDefrostOperation());

  CurveQuadratic cyclingCurve(model);
  EXPECT_TRUE(hp.setCyclingRatioFactorCurve(cyclingCurve));
  ASSERT_TRUE(hp.cyclingRatioFactorCurve());
  EXPECT_EQ(cyclingCurve.handle(), hp.cyclingRatioFactorCurve()->handle());
  EXPECT_FALSE(hp.setCyclingRatioFactorCurve(foreignQuadratic));
  hp.resetCyclingRatioFactorCurve();
  EXPECT_FALSE(hp.cyclingRatioFactorCurve());

  EXPECT_TRUE(hp.setNominalAuxiliaryElectricPower(250.0));
  EXPECT_DOUBLE_EQ(250.0, hp.nominalAuxiliaryElectricPower());

  CurveBiquadratic auxiliaryEirFT(model);
  CurveQuadratic auxiliaryEirFPLR(model);
  EXPECT_TRUE(hp.setAuxiliaryElectricEnergyInputRatioFunctionofTemperatureCurve(auxiliaryEirFT));
  EXPECT_TRUE(hp.setAuxiliaryElectricEnergyInputRatioFunctionofPLRCurve(auxiliaryEirFPLR));
  ASSERT_TRUE(hp.auxiliaryElectricEnergyInputRatioFunctionofTemperatureCurve());
  ASSERT_TRUE(hp.auxiliaryElectricEnergyInputRatioFunctionofPLRCurve());
  EXPECT_EQ(auxiliaryEirFT.handle(), hp.auxiliaryElectricEnergyInputRatioFunctionofTemperatureCurve()->handle());
  EXPECT_EQ(auxiliaryEirFPLR.handle(), hp.auxiliaryElectricEnergyInputRatioFunctionofPLRCurve()->handle());
  EXPECT_FALSE(hp.setAuxiliaryElectricEnergyInputRatioFunctionofTemperatureCurve(foreignBiquadratic));
  EXPECT_FALSE(hp.setAuxiliaryElectricEnergyInputRatioFunctionofPLRCurve(foreignQuadratic));
  hp.resetAuxiliaryElectricEnergyInputRatioFunctionofTemperatureCurve();
  hp.resetAuxiliaryElectricEnergyInputRatioFunctionofPLRCurve();
  EXPECT_FALSE(hp.auxiliaryElectricEnergyInputRatioFunctionofTemperatureCurve());
  EXPECT_FALSE(hp.auxiliaryElectricEnergyInputRatioFunctionofPLRCurve());

  EXPECT_TRUE(hp.setStandbyElectricPower(40.0));
  EXPECT_DOUBLE_EQ(40.0, hp.standbyElectricPower());

  EXPECT_TRUE(hp.setMinimumUnloadingRatio(0.5));
  EXPECT_DOUBLE_EQ(0.5, hp.minimumUnloadingRatio());

  auto copiedObject = model.addObject(hp.idfObject());
  ASSERT_TRUE(copiedObject);
  auto copied = copiedObject->cast<HeatPumpAirToWaterFuelFiredHeating>();
  EXPECT_EQ(hp.fuelType(), copied.fuelType());
  EXPECT_EQ(hp.normalizedCapacityFunctionofTemperatureCurve().handle(), copied.normalizedCapacityFunctionofTemperatureCurve().handle());
  EXPECT_EQ(hp.fuelEnergyInputRatioFunctionofTemperatureCurve().handle(), copied.fuelEnergyInputRatioFunctionofTemperatureCurve().handle());
  EXPECT_EQ(hp.fuelEnergyInputRatioFunctionofPLRCurve().handle(), copied.fuelEnergyInputRatioFunctionofPLRCurve().handle());
}

TEST_F(EPModelFixture, HeatPumpAirToWaterFuelFiredHeating_ExplicitCurveConstructor_UsesPassedCurves) {
  Model model;
  CurveBiquadratic normalizedCapacityCurve(model);
  CurveBiquadratic eirFT(model);
  CurveQuadratic eirFPLR(model);

  HeatPumpAirToWaterFuelFiredHeating hp(model, normalizedCapacityCurve, eirFT, eirFPLR);
  EXPECT_EQ(normalizedCapacityCurve.handle(), hp.normalizedCapacityFunctionofTemperatureCurve().handle());
  EXPECT_EQ(eirFT.handle(), hp.fuelEnergyInputRatioFunctionofTemperatureCurve().handle());
  EXPECT_EQ(eirFPLR.handle(), hp.fuelEnergyInputRatioFunctionofPLRCurve().handle());
}

TEST_F(EPModelFixture, HeatPumpAirToWaterFuelFiredHeating_ExplicitCurveConstructor_RejectsForeignCurves) {
  Model model;
  Model foreignModel;
  CurveBiquadratic normalizedCapacityCurve(foreignModel);
  CurveBiquadratic eirFT(foreignModel);
  CurveQuadratic eirFPLR(foreignModel);

  EXPECT_THROW(HeatPumpAirToWaterFuelFiredHeating(model, normalizedCapacityCurve, eirFT, eirFPLR), openstudio::Exception);
  EXPECT_TRUE(model.getModelObjects<HeatPumpAirToWaterFuelFiredHeating>().empty());
}

TEST_F(EPModelFixture, HeatPumpAirToWaterFuelFiredHeating_Remove_ClearsCompanionRelationship) {
  Model model;
  HeatPumpAirToWaterFuelFiredHeating heating(model);
  HeatPumpAirToWaterFuelFiredCooling cooling(model);

  EXPECT_TRUE(heating.setCompanionCoolingHeatPump(cooling));
  EXPECT_TRUE(cooling.setCompanionHeatingHeatPump(heating));
  ASSERT_TRUE(heating.companionCoolingHeatPump());
  ASSERT_TRUE(cooling.companionHeatingHeatPump());

  const auto initialObjectCount = model.objects().size();
  EXPECT_FALSE(heating.remove().empty());
  EXPECT_EQ(initialObjectCount - 1, model.objects().size());
  EXPECT_FALSE(cooling.companionHeatingHeatPump());
  EXPECT_EQ(0u, model.getModelObjects<HeatPumpAirToWaterFuelFiredHeating>().size());
  EXPECT_EQ(1u, model.getModelObjects<HeatPumpAirToWaterFuelFiredCooling>().size());
}

TEST_F(EPModelFixture, HeatPumpAirToWaterFuelFiredHeating_AddToNode_PlantSupplyOnly) {
  Model model;
  HeatPumpAirToWaterFuelFiredHeating rejectedHeating(model);

  AirLoopHVAC airLoop(model);
  Node airSupplyNode = airLoop.supplyOutletNode();
  const auto initialAirSupplyCount = airLoop.supplyComponents().size();
  EXPECT_FALSE(rejectedHeating.addToNode(airSupplyNode));
  EXPECT_EQ(initialAirSupplyCount, airLoop.supplyComponents().size());

  Node airDemandNode = airLoop.zoneSplitter().lastOutletModelObject()->cast<Node>();
  const auto initialAirDemandCount = airLoop.demandComponents().size();
  EXPECT_FALSE(rejectedHeating.addToNode(airDemandNode));
  EXPECT_EQ(initialAirDemandCount, airLoop.demandComponents().size());

  PlantLoop plantLoop(model);
  Node plantDemandNode = plantLoop.demandOutletNode();
  const auto initialDemandCount = plantLoop.demandComponents().size();
  EXPECT_FALSE(rejectedHeating.addToNode(plantDemandNode));
  EXPECT_EQ(initialDemandCount, plantLoop.demandComponents().size());

  Node unconnectedNode = model.getOrCreateTransientByName<Node>("Unconnected HeatPumpAirToWaterFuelFiredHeating Node");
  EXPECT_FALSE(rejectedHeating.addToNode(unconnectedNode));
  EXPECT_FALSE(rejectedHeating.loop());
  EXPECT_FALSE(rejectedHeating.inletModelObject());
  EXPECT_FALSE(rejectedHeating.outletModelObject());

  HeatPumpAirToWaterFuelFiredHeating heating(model);
  Node plantSupplyNode = plantLoop.supplyOutletNode();
  const auto initialSupplyCount = plantLoop.supplyComponents().size();
  EXPECT_TRUE(heating.addToNode(plantSupplyNode));
  EXPECT_GT(plantLoop.supplyComponents().size(), initialSupplyCount);
  ASSERT_TRUE(heating.plantLoop());
  EXPECT_EQ(plantLoop.handle(), heating.plantLoop()->handle());
  ASSERT_TRUE(heating.inletModelObject());
  ASSERT_TRUE(heating.outletModelObject());

  heating.disconnect();
  EXPECT_FALSE(heating.plantLoop());
  EXPECT_FALSE(heating.inletModelObject());
  EXPECT_FALSE(heating.outletModelObject());

  PlantLoop secondPlantLoop(model);
  EXPECT_TRUE(secondPlantLoop.addSupplyBranchForComponent(heating));
  ASSERT_TRUE(heating.plantLoop());
  EXPECT_EQ(secondPlantLoop.handle(), heating.plantLoop()->handle());
}
