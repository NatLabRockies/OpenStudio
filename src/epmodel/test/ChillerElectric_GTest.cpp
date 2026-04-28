/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include <algorithm>
#include <limits>

#include "EPModelFixture.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../StraightComponent/Node.hpp"
#include "../WaterToWaterComponent/ChillerElectric.hpp"
#include <utilities/idd/Chiller_Electric_FieldEnums.hxx>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ChillerElectric_DefaultConstructor) {
  Model model;
  ChillerElectric chiller(model);

  EXPECT_EQ(ChillerElectric::iddObjectType(), chiller.iddObject().type());
  EXPECT_FALSE(chiller.nameString().empty());
  EXPECT_EQ(openstudio::Chiller_ElectricFields::ChilledWaterInletNodeName, chiller.supplyInletPort());
  EXPECT_EQ(openstudio::Chiller_ElectricFields::ChilledWaterOutletNodeName, chiller.supplyOutletPort());
  EXPECT_EQ(openstudio::Chiller_ElectricFields::CondenserInletNodeName, chiller.demandInletPort());
  EXPECT_EQ(openstudio::Chiller_ElectricFields::CondenserOutletNodeName, chiller.demandOutletPort());
  EXPECT_EQ(openstudio::Chiller_ElectricFields::HeatRecoveryInletNodeName, chiller.tertiaryInletPort());
  EXPECT_EQ(openstudio::Chiller_ElectricFields::HeatRecoveryOutletNodeName, chiller.tertiaryOutletPort());
  EXPECT_EQ("AirCooled", chiller.condenserType());
  EXPECT_EQ("NotModulated", chiller.chillerFlowMode());
  EXPECT_DOUBLE_EQ(1.0, chiller.sizingFactor());
  EXPECT_DOUBLE_EQ(2.0, chiller.basinHeaterSetpointTemperature());
  EXPECT_DOUBLE_EQ(0.0, chiller.thermosiphonMinimumTemperatureDifference());
  EXPECT_FALSE(chiller.chilledWaterLoop());
  EXPECT_FALSE(chiller.condenserWaterLoop());
  EXPECT_FALSE(chiller.heatRecoveryLoop());
}

TEST_F(EPModelFixture, ChillerElectric_ScalarAccessors_RoundTrip) {
  Model model;
  ChillerElectric chiller(model);

  const auto condenserTypes = ChillerElectric::condenserTypeValues();
  EXPECT_FALSE(condenserTypes.empty());
  EXPECT_TRUE(std::find(condenserTypes.begin(), condenserTypes.end(), "AirCooled") != condenserTypes.end());

  const auto chillerFlowModes = ChillerElectric::chillerFlowModeValues();
  EXPECT_FALSE(chillerFlowModes.empty());
  EXPECT_TRUE(std::find(chillerFlowModes.begin(), chillerFlowModes.end(), "NotModulated") != chillerFlowModes.end());

  EXPECT_TRUE(chiller.setCondenserType("WaterCooled"));
  EXPECT_EQ("WaterCooled", chiller.condenserType());
  EXPECT_FALSE(chiller.setCondenserType("BogusCondenserType"));
  EXPECT_EQ("WaterCooled", chiller.condenserType());
  chiller.resetCondenserType();
  EXPECT_TRUE(chiller.isCondenserTypeDefaulted());
  EXPECT_EQ("AirCooled", chiller.condenserType());

  EXPECT_TRUE(chiller.setNominalCapacity(700000.0));
  ASSERT_TRUE(chiller.nominalCapacity());
  EXPECT_DOUBLE_EQ(700000.0, chiller.nominalCapacity().get());
  EXPECT_FALSE(chiller.isNominalCapacityAutosized());
  chiller.autosizeNominalCapacity();
  EXPECT_TRUE(chiller.isNominalCapacityAutosized());

  EXPECT_TRUE(chiller.setNominalCOP(3.4));
  EXPECT_DOUBLE_EQ(3.4, chiller.nominalCOP());

  EXPECT_TRUE(chiller.setMinimumPartLoadRatio(0.12));
  ASSERT_TRUE(chiller.minimumPartLoadRatio());
  EXPECT_DOUBLE_EQ(0.12, chiller.minimumPartLoadRatio().get());
  chiller.resetMinimumPartLoadRatio();
  EXPECT_FALSE(chiller.minimumPartLoadRatio());

  EXPECT_TRUE(chiller.setTemperatureRiseCoefficient(1.6));
  EXPECT_DOUBLE_EQ(1.6, chiller.temperatureRiseCoefficient());

  EXPECT_TRUE(chiller.setDesignChilledWaterFlowRate(0.024));
  ASSERT_TRUE(chiller.designChilledWaterFlowRate());
  EXPECT_DOUBLE_EQ(0.024, chiller.designChilledWaterFlowRate().get());
  chiller.autosizeDesignChilledWaterFlowRate();
  EXPECT_TRUE(chiller.isDesignChilledWaterFlowRateAutosized());
  chiller.resetDesignChilledWaterFlowRate();
  EXPECT_FALSE(chiller.designChilledWaterFlowRate());

  EXPECT_TRUE(chiller.setChillerFlowMode("ConstantFlow"));
  EXPECT_EQ("ConstantFlow", chiller.chillerFlowMode());
  EXPECT_FALSE(chiller.setChillerFlowMode("BogusFlowMode"));
  EXPECT_EQ("ConstantFlow", chiller.chillerFlowMode());
  chiller.resetChillerFlowMode();
  EXPECT_TRUE(chiller.isChillerFlowModeDefaulted());
  EXPECT_EQ("NotModulated", chiller.chillerFlowMode());

  EXPECT_TRUE(chiller.setDesignHeatRecoveryWaterFlowRate(0.007));
  ASSERT_TRUE(chiller.designHeatRecoveryWaterFlowRate());
  EXPECT_DOUBLE_EQ(0.007, chiller.designHeatRecoveryWaterFlowRate().get());
  chiller.autosizeDesignHeatRecoveryWaterFlowRate();
  EXPECT_TRUE(chiller.isDesignHeatRecoveryWaterFlowRateAutosized());

  EXPECT_TRUE(chiller.setSizingFactor(1.1));
  EXPECT_DOUBLE_EQ(1.1, chiller.sizingFactor());
  chiller.resetSizingFactor();
  EXPECT_TRUE(chiller.isSizingFactorDefaulted());
  EXPECT_DOUBLE_EQ(1.0, chiller.sizingFactor());

  EXPECT_TRUE(chiller.setBasinHeaterSetpointTemperature(6.2));
  EXPECT_DOUBLE_EQ(6.2, chiller.basinHeaterSetpointTemperature());
  chiller.resetBasinHeaterSetpointTemperature();
  EXPECT_TRUE(chiller.isBasinHeaterSetpointTemperatureDefaulted());
  EXPECT_DOUBLE_EQ(2.0, chiller.basinHeaterSetpointTemperature());

  EXPECT_TRUE(chiller.setCondenserHeatRecoveryRelativeCapacityFraction(0.4));
  ASSERT_TRUE(chiller.condenserHeatRecoveryRelativeCapacityFraction());
  EXPECT_DOUBLE_EQ(0.4, chiller.condenserHeatRecoveryRelativeCapacityFraction().get());
  chiller.resetCondenserHeatRecoveryRelativeCapacityFraction();
  EXPECT_FALSE(chiller.condenserHeatRecoveryRelativeCapacityFraction());

  EXPECT_TRUE(chiller.setEndUseSubcategory("Cooling"));
  EXPECT_EQ("Cooling", chiller.endUseSubcategory());
  chiller.resetEndUseSubcategory();
  EXPECT_TRUE(chiller.isEndUseSubcategoryDefaulted());

  EXPECT_TRUE(chiller.setThermosiphonMinimumTemperatureDifference(1.2));
  EXPECT_DOUBLE_EQ(1.2, chiller.thermosiphonMinimumTemperatureDifference());
  chiller.resetThermosiphonMinimumTemperatureDifference();
  EXPECT_TRUE(chiller.isThermosiphonMinimumTemperatureDifferenceDefaulted());
  EXPECT_DOUBLE_EQ(0.0, chiller.thermosiphonMinimumTemperatureDifference());
}

TEST_F(EPModelFixture, ChillerElectric_PlantLoopAttachmentParity_NoControllers) {
  Model model;
  PlantLoop chilledWaterLoop(model);
  PlantLoop condenserLoop(model);
  PlantLoop heatRecoveryLoop(model);
  ChillerElectric chiller(model);

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
  ASSERT_TRUE(chiller.condenserWaterLoop());
  EXPECT_EQ(condenserLoop.handle(), chiller.condenserWaterLoop()->handle());
  ASSERT_TRUE(chiller.chilledWaterInletNode());
  ASSERT_TRUE(chiller.chilledWaterOutletNode());
  ASSERT_TRUE(chiller.condenserInletNode());
  ASSERT_TRUE(chiller.condenserOutletNode());
  ASSERT_TRUE(chiller.heatRecoveryInletNode());
  ASSERT_TRUE(chiller.heatRecoveryOutletNode());
  EXPECT_EQ(chiller.supplyInletModelObject()->cast<Node>(), chiller.chilledWaterInletNode().get());
  EXPECT_EQ(chiller.supplyOutletModelObject()->cast<Node>(), chiller.chilledWaterOutletNode().get());
  EXPECT_EQ(chiller.demandInletModelObject()->cast<Node>(), chiller.condenserInletNode().get());
  EXPECT_EQ(chiller.demandOutletModelObject()->cast<Node>(), chiller.condenserOutletNode().get());
  EXPECT_EQ(chiller.tertiaryInletModelObject()->cast<Node>(), chiller.heatRecoveryInletNode().get());
  EXPECT_EQ(chiller.tertiaryOutletModelObject()->cast<Node>(), chiller.heatRecoveryOutletNode().get());

  Node condenserOutletNode = condenserLoop.supplyOutletNode();
  EXPECT_FALSE(chiller.addToTertiaryNode(condenserOutletNode));
  ASSERT_TRUE(chiller.heatRecoveryLoop());
  EXPECT_EQ(heatRecoveryLoop.handle(), chiller.heatRecoveryLoop()->handle());

  ASSERT_TRUE(chiller.heatRecoveryInletNode());
  Node heatRecoveryInletNode = *chiller.heatRecoveryInletNode();
  EXPECT_FALSE(chiller.addToTertiaryNode(heatRecoveryInletNode));
  ASSERT_TRUE(chiller.heatRecoveryLoop());
  EXPECT_EQ(heatRecoveryLoop.handle(), chiller.heatRecoveryLoop()->handle());

  EXPECT_TRUE(chiller.removeFromSecondaryPlantLoop());
  EXPECT_FALSE(chiller.condenserWaterLoop());
  EXPECT_FALSE(chiller.condenserInletNode());
  EXPECT_FALSE(chiller.condenserOutletNode());
  EXPECT_FALSE(chiller.demandInletModelObject());
  EXPECT_FALSE(chiller.demandOutletModelObject());
  ASSERT_TRUE(chiller.chilledWaterLoop());
  EXPECT_EQ(chilledWaterLoop.handle(), chiller.chilledWaterLoop()->handle());
  ASSERT_TRUE(chiller.heatRecoveryLoop());
  EXPECT_EQ(heatRecoveryLoop.handle(), chiller.heatRecoveryLoop()->handle());
  EXPECT_EQ("AirCooled", chiller.condenserType());
}

TEST_F(EPModelFixture, ChillerElectric_AddToNodeDemandRoutingParity) {
  Model model;
  ChillerElectric chiller(model);

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

  Node initialHeatRecoveryDemandNode = heatRecoveryLoop.demandInletNode();
  EXPECT_TRUE(chiller.addToNode(initialHeatRecoveryDemandNode));
  ASSERT_TRUE(chiller.heatRecoveryLoop());
  EXPECT_EQ(heatRecoveryLoop.handle(), chiller.heatRecoveryLoop()->handle());
  ASSERT_TRUE(chiller.condenserWaterLoop());
  EXPECT_EQ(condenserLoop.handle(), chiller.condenserWaterLoop()->handle());
  ASSERT_TRUE(chiller.chilledWaterLoop());
  EXPECT_EQ(chilledWaterLoop.handle(), chiller.chilledWaterLoop()->handle());
  ASSERT_TRUE(chiller.heatRecoveryInletNode());
  EXPECT_EQ(chiller.tertiaryInletModelObject()->cast<Node>(), chiller.heatRecoveryInletNode().get());
  ASSERT_TRUE(chiller.heatRecoveryOutletNode());
  EXPECT_EQ(chiller.tertiaryOutletModelObject()->cast<Node>(), chiller.heatRecoveryOutletNode().get());

  EXPECT_TRUE(chiller.removeFromTertiaryPlantLoop());
  EXPECT_FALSE(chiller.heatRecoveryLoop());
  EXPECT_FALSE(chiller.heatRecoveryInletNode());
  EXPECT_FALSE(chiller.heatRecoveryOutletNode());
  EXPECT_FALSE(chiller.tertiaryInletModelObject());
  EXPECT_FALSE(chiller.tertiaryOutletModelObject());

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
  ASSERT_TRUE(chiller.heatRecoveryInletNode());
  EXPECT_EQ(chiller.tertiaryInletModelObject()->cast<Node>(), chiller.heatRecoveryInletNode().get());
  ASSERT_TRUE(chiller.heatRecoveryOutletNode());
  EXPECT_EQ(chiller.tertiaryOutletModelObject()->cast<Node>(), chiller.heatRecoveryOutletNode().get());
}
