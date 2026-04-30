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
#include "../StraightComponent/Node.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, HeatPumpAirToWaterFuelFiredCooling_DefaultConstructor) {
  Model model;
  HeatPumpAirToWaterFuelFiredCooling hp(model);

  EXPECT_EQ(HeatPumpAirToWaterFuelFiredCooling::iddObjectType(), hp.iddObject().type());
  EXPECT_FALSE(hp.nameString().empty());

  EXPECT_FALSE(hp.companionHeatingHeatPump());
  EXPECT_EQ("NaturalGas", hp.fuelType());
  EXPECT_EQ("General", hp.endUseSubcategory());
  EXPECT_TRUE(hp.isEndUseSubcategoryDefaulted());
  EXPECT_TRUE(hp.isNominalCoolingCapacityAutosized());
  EXPECT_DOUBLE_EQ(1.0, hp.nominalCOP());
  EXPECT_TRUE(hp.isDesignFlowRateAutosized());
  EXPECT_DOUBLE_EQ(7.0, hp.designSupplyTemperature());
  ASSERT_TRUE(hp.designTemperatureLift());
  EXPECT_DOUBLE_EQ(11.1, hp.designTemperatureLift().get());
  EXPECT_FALSE(hp.isDesignTemperatureLiftAutosized());
  EXPECT_DOUBLE_EQ(1.0, hp.sizingFactor());
  EXPECT_EQ("NotModulated", hp.flowMode());
  EXPECT_EQ("DryBulb", hp.outdoorAirTemperatureCurveInputVariable());
  EXPECT_EQ("EnteringEvaporator", hp.waterTemperatureCurveInputVariable());
  EXPECT_DOUBLE_EQ(0.1, hp.minimumPartLoadRatio());
  EXPECT_DOUBLE_EQ(1.0, hp.maximumPartLoadRatio());
  EXPECT_FALSE(hp.cyclingRatioFactorCurve());
  EXPECT_DOUBLE_EQ(0.0, hp.nominalAuxiliaryElectricPower());
  EXPECT_FALSE(hp.auxiliaryElectricEnergyInputRatioFunctionofTemperatureCurve());
  EXPECT_FALSE(hp.auxiliaryElectricEnergyInputRatioFunctionofPLRCurve());
  EXPECT_DOUBLE_EQ(0.0, hp.standbyElectricPower());
  EXPECT_DOUBLE_EQ(0.25, hp.minimumUnloadingRatio());

  auto normalizedCapacityCurve = hp.normalizedCapacityFunctionofTemperatureCurve().cast<CurveBiquadratic>();
  EXPECT_EQ("GAHP Cooling CapFT", normalizedCapacityCurve.nameString());
  EXPECT_DOUBLE_EQ(1.0, normalizedCapacityCurve.coefficient1Constant());
  EXPECT_DOUBLE_EQ(5.0, normalizedCapacityCurve.minimumValueofx());
  EXPECT_DOUBLE_EQ(35.0, normalizedCapacityCurve.maximumValueofy());

  auto eirFT = hp.fuelEnergyInputRatioFunctionofTemperatureCurve().cast<CurveBiquadratic>();
  EXPECT_EQ("GAHP Cooling EIRFT", eirFT.nameString());
  EXPECT_DOUBLE_EQ(1.0, eirFT.coefficient1Constant());
  EXPECT_DOUBLE_EQ(24.0, eirFT.minimumValueofy());

  auto eirFPLR = hp.fuelEnergyInputRatioFunctionofPLRCurve().cast<CurveQuadratic>();
  EXPECT_EQ("GAHP Cooling EIRFPLR", eirFPLR.nameString());
  EXPECT_DOUBLE_EQ(1.0, eirFPLR.coefficient1Constant());
  EXPECT_DOUBLE_EQ(1.0, eirFPLR.maximumValueofx());
}

TEST_F(EPModelFixture, HeatPumpAirToWaterFuelFiredCooling_RelationshipAndScalarAccessors_RoundTrip) {
  Model model;
  HeatPumpAirToWaterFuelFiredCooling hp(model);

  HeatPumpAirToWaterFuelFiredHeating companion(model);
  EXPECT_TRUE(hp.setCompanionHeatingHeatPump(companion));
  ASSERT_TRUE(hp.companionHeatingHeatPump());
  EXPECT_EQ(companion.handle(), hp.companionHeatingHeatPump()->handle());

  Model otherModel;
  HeatPumpAirToWaterFuelFiredHeating foreignCompanion(otherModel);
  EXPECT_FALSE(hp.setCompanionHeatingHeatPump(foreignCompanion));
  ASSERT_TRUE(hp.companionHeatingHeatPump());
  EXPECT_EQ(companion.handle(), hp.companionHeatingHeatPump()->handle());
  hp.resetCompanionHeatingHeatPump();
  EXPECT_FALSE(hp.companionHeatingHeatPump());

  EXPECT_TRUE(hp.setEndUseSubcategory("Process"));
  EXPECT_EQ("Process", hp.endUseSubcategory());
  hp.resetEndUseSubcategory();
  EXPECT_TRUE(hp.isEndUseSubcategoryDefaulted());

  EXPECT_TRUE(hp.setNominalCoolingCapacity(12000.0));
  ASSERT_TRUE(hp.nominalCoolingCapacity());
  EXPECT_DOUBLE_EQ(12000.0, hp.nominalCoolingCapacity().get());
  hp.autosizeNominalCoolingCapacity();
  EXPECT_TRUE(hp.isNominalCoolingCapacityAutosized());
  hp.resetNominalCoolingCapacity();
  EXPECT_FALSE(hp.nominalCoolingCapacity());

  EXPECT_TRUE(hp.setNominalCOP(1.35));
  EXPECT_DOUBLE_EQ(1.35, hp.nominalCOP());

  EXPECT_TRUE(hp.setDesignFlowRate(0.015));
  ASSERT_TRUE(hp.designFlowRate());
  EXPECT_DOUBLE_EQ(0.015, hp.designFlowRate().get());
  hp.autosizeDesignFlowRate();
  EXPECT_TRUE(hp.isDesignFlowRateAutosized());
  hp.resetDesignFlowRate();
  EXPECT_FALSE(hp.designFlowRate());

  EXPECT_TRUE(hp.setDesignSupplyTemperature(6.7));
  EXPECT_DOUBLE_EQ(6.7, hp.designSupplyTemperature());

  EXPECT_TRUE(hp.setDesignTemperatureLift(9.8));
  ASSERT_TRUE(hp.designTemperatureLift());
  EXPECT_DOUBLE_EQ(9.8, hp.designTemperatureLift().get());
  hp.autosizeDesignTemperatureLift();
  EXPECT_TRUE(hp.isDesignTemperatureLiftAutosized());

  EXPECT_TRUE(hp.setSizingFactor(1.2));
  EXPECT_DOUBLE_EQ(1.2, hp.sizingFactor());

  const auto fuelTypeValues = HeatPumpAirToWaterFuelFiredCooling::fuelTypeValues();
  ASSERT_FALSE(fuelTypeValues.empty());
  EXPECT_TRUE(hp.setFuelType(fuelTypeValues.front()));
  EXPECT_EQ(fuelTypeValues.front(), hp.fuelType());

  const auto flowModeValues = HeatPumpAirToWaterFuelFiredCooling::flowModeValues();
  ASSERT_FALSE(flowModeValues.empty());
  EXPECT_TRUE(hp.setFlowMode(flowModeValues.front()));
  EXPECT_EQ(flowModeValues.front(), hp.flowMode());

  const auto outdoorCurveInputValues = HeatPumpAirToWaterFuelFiredCooling::outdoorAirTemperatureCurveInputVariableValues();
  ASSERT_FALSE(outdoorCurveInputValues.empty());
  EXPECT_TRUE(hp.setOutdoorAirTemperatureCurveInputVariable(outdoorCurveInputValues.front()));
  EXPECT_EQ(outdoorCurveInputValues.front(), hp.outdoorAirTemperatureCurveInputVariable());

  const auto waterCurveInputValues = HeatPumpAirToWaterFuelFiredCooling::waterTemperatureCurveInputVariableValues();
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

  CurveQuadratic cyclingCurve(model);
  EXPECT_TRUE(hp.setCyclingRatioFactorCurve(cyclingCurve));
  ASSERT_TRUE(hp.cyclingRatioFactorCurve());
  EXPECT_EQ(cyclingCurve.handle(), hp.cyclingRatioFactorCurve()->handle());
  EXPECT_FALSE(hp.setCyclingRatioFactorCurve(foreignQuadratic));
  hp.resetCyclingRatioFactorCurve();
  EXPECT_FALSE(hp.cyclingRatioFactorCurve());

  EXPECT_TRUE(hp.setNominalAuxiliaryElectricPower(150.0));
  EXPECT_DOUBLE_EQ(150.0, hp.nominalAuxiliaryElectricPower());

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

  EXPECT_TRUE(hp.setStandbyElectricPower(23.0));
  EXPECT_DOUBLE_EQ(23.0, hp.standbyElectricPower());

  EXPECT_TRUE(hp.setMinimumUnloadingRatio(0.4));
  EXPECT_DOUBLE_EQ(0.4, hp.minimumUnloadingRatio());

  auto copiedObject = model.addObject(hp.idfObject());
  ASSERT_TRUE(copiedObject);
  auto copied = copiedObject->cast<HeatPumpAirToWaterFuelFiredCooling>();
  EXPECT_EQ(hp.fuelType(), copied.fuelType());
  EXPECT_EQ(hp.normalizedCapacityFunctionofTemperatureCurve().handle(), copied.normalizedCapacityFunctionofTemperatureCurve().handle());
  EXPECT_EQ(hp.fuelEnergyInputRatioFunctionofTemperatureCurve().handle(), copied.fuelEnergyInputRatioFunctionofTemperatureCurve().handle());
  EXPECT_EQ(hp.fuelEnergyInputRatioFunctionofPLRCurve().handle(), copied.fuelEnergyInputRatioFunctionofPLRCurve().handle());
}

TEST_F(EPModelFixture, HeatPumpAirToWaterFuelFiredCooling_ExplicitCurveConstructor_UsesPassedCurves) {
  Model model;
  CurveBiquadratic normalizedCapacityCurve(model);
  CurveBiquadratic eirFT(model);
  CurveQuadratic eirFPLR(model);

  HeatPumpAirToWaterFuelFiredCooling hp(model, normalizedCapacityCurve, eirFT, eirFPLR);
  EXPECT_EQ(normalizedCapacityCurve.handle(), hp.normalizedCapacityFunctionofTemperatureCurve().handle());
  EXPECT_EQ(eirFT.handle(), hp.fuelEnergyInputRatioFunctionofTemperatureCurve().handle());
  EXPECT_EQ(eirFPLR.handle(), hp.fuelEnergyInputRatioFunctionofPLRCurve().handle());
}

TEST_F(EPModelFixture, HeatPumpAirToWaterFuelFiredCooling_ExplicitCurveConstructor_RejectsForeignCurves) {
  Model model;
  Model foreignModel;
  CurveBiquadratic normalizedCapacityCurve(foreignModel);
  CurveBiquadratic eirFT(foreignModel);
  CurveQuadratic eirFPLR(foreignModel);

  EXPECT_THROW(HeatPumpAirToWaterFuelFiredCooling(model, normalizedCapacityCurve, eirFT, eirFPLR), openstudio::Exception);
  EXPECT_TRUE(model.getModelObjects<HeatPumpAirToWaterFuelFiredCooling>().empty());
}

TEST_F(EPModelFixture, HeatPumpAirToWaterFuelFiredCooling_AddToNode_PlantSupplyOnly) {
  Model model;
  HeatPumpAirToWaterFuelFiredCooling rejectedCooling(model);

  AirLoopHVAC airLoop(model);
  Node airSupplyNode = airLoop.supplyOutletNode();
  const auto initialAirSupplyCount = airLoop.supplyComponents().size();
  EXPECT_FALSE(rejectedCooling.addToNode(airSupplyNode));
  EXPECT_EQ(initialAirSupplyCount, airLoop.supplyComponents().size());

  Node airDemandNode = airLoop.zoneSplitter().lastOutletModelObject()->cast<Node>();
  const auto initialAirDemandCount = airLoop.demandComponents().size();
  EXPECT_FALSE(rejectedCooling.addToNode(airDemandNode));
  EXPECT_EQ(initialAirDemandCount, airLoop.demandComponents().size());

  PlantLoop plantLoop(model);
  Node plantDemandNode = plantLoop.demandOutletNode();
  const auto initialDemandCount = plantLoop.demandComponents().size();
  EXPECT_FALSE(rejectedCooling.addToNode(plantDemandNode));
  EXPECT_EQ(initialDemandCount, plantLoop.demandComponents().size());

  Node unconnectedNode = model.getOrCreateTransientByName<Node>("Unconnected HeatPumpAirToWaterFuelFiredCooling Node");
  EXPECT_FALSE(rejectedCooling.addToNode(unconnectedNode));
  EXPECT_FALSE(rejectedCooling.loop());
  EXPECT_FALSE(rejectedCooling.inletModelObject());
  EXPECT_FALSE(rejectedCooling.outletModelObject());

  HeatPumpAirToWaterFuelFiredCooling cooling(model);
  Node plantSupplyNode = plantLoop.supplyOutletNode();
  const auto initialSupplyCount = plantLoop.supplyComponents().size();
  EXPECT_TRUE(cooling.addToNode(plantSupplyNode));
  EXPECT_GT(plantLoop.supplyComponents().size(), initialSupplyCount);
  ASSERT_TRUE(cooling.plantLoop());
  EXPECT_EQ(plantLoop.handle(), cooling.plantLoop()->handle());
  ASSERT_TRUE(cooling.inletModelObject());
  ASSERT_TRUE(cooling.outletModelObject());

  cooling.disconnect();
  EXPECT_FALSE(cooling.plantLoop());
  EXPECT_FALSE(cooling.inletModelObject());
  EXPECT_FALSE(cooling.outletModelObject());

  PlantLoop secondPlantLoop(model);
  EXPECT_TRUE(secondPlantLoop.addSupplyBranchForComponent(cooling));
  ASSERT_TRUE(cooling.plantLoop());
  EXPECT_EQ(secondPlantLoop.handle(), cooling.plantLoop()->handle());
}
