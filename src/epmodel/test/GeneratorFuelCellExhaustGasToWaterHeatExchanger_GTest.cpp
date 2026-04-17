/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Generator/GeneratorFuelCell.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../Loop/Loop.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"
#include "../StraightComponent/GeneratorFuelCellExhaustGasToWaterHeatExchanger.hpp"
#include "../StraightComponent/Node.hpp"

#include <utilities/idd/Generator_FuelCell_FieldEnums.hxx>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, GeneratorFuelCellExhaustGasToWaterHeatExchanger_DefaultConstructor) {
  Model model;
  GeneratorFuelCellExhaustGasToWaterHeatExchanger exchanger(model);
  EXPECT_EQ(GeneratorFuelCellExhaustGasToWaterHeatExchanger::iddObjectType(), exchanger.iddObject().type());
  EXPECT_DOUBLE_EQ(0.0004, exchanger.heatRecoveryWaterMaximumFlowRate());
  EXPECT_EQ("Condensing", exchanger.heatExchangerCalculationMethod());
  ASSERT_TRUE(exchanger.method2Parameterhxs0());
  ASSERT_TRUE(exchanger.method2Parameterhxs1());
  ASSERT_TRUE(exchanger.method2Parameterhxs2());
  ASSERT_TRUE(exchanger.method2Parameterhxs3());
  ASSERT_TRUE(exchanger.method2Parameterhxs4());
  EXPECT_DOUBLE_EQ(83.1, exchanger.method2Parameterhxs0().get());
  EXPECT_DOUBLE_EQ(4798.0, exchanger.method2Parameterhxs1().get());
  EXPECT_DOUBLE_EQ(-138e3, exchanger.method2Parameterhxs2().get());
  EXPECT_DOUBLE_EQ(-353.8e3, exchanger.method2Parameterhxs3().get());
  EXPECT_DOUBLE_EQ(5.15e8, exchanger.method2Parameterhxs4().get());
  ASSERT_TRUE(exchanger.method4hxl1Coefficient());
  ASSERT_TRUE(exchanger.method4hxl2Coefficient());
  ASSERT_TRUE(exchanger.method4CondensationThreshold());
  EXPECT_DOUBLE_EQ(-0.000196, exchanger.method4hxl1Coefficient().get());
  EXPECT_DOUBLE_EQ(0.0031, exchanger.method4hxl2Coefficient().get());
  EXPECT_DOUBLE_EQ(35.0, exchanger.method4CondensationThreshold().get());
  EXPECT_FALSE(exchanger.exhaustOutletAirNode());
  EXPECT_FALSE(exchanger.fuelCell());
}

TEST_F(EPModelFixture, GeneratorFuelCellExhaustGasToWaterHeatExchanger_NodeConstructorAndRelationships) {
  Model model;
  Node exhaustNode(model);
  GeneratorFuelCellExhaustGasToWaterHeatExchanger exchanger(model, exhaustNode);

  EXPECT_EQ("FixedEffectiveness", exchanger.heatExchangerCalculationMethod());
  ASSERT_TRUE(exchanger.method1HeatExchangerEffectiveness());
  EXPECT_DOUBLE_EQ(1.0, exchanger.method1HeatExchangerEffectiveness().get());
  ASSERT_TRUE(exchanger.exhaustOutletAirNode());
  EXPECT_EQ(exhaustNode, exchanger.exhaustOutletAirNode().get());

  Node replacementNode(model);
  EXPECT_TRUE(exchanger.setExhaustOutletAirNode(replacementNode));
  ASSERT_TRUE(exchanger.exhaustOutletAirNode());
  EXPECT_EQ(replacementNode, exchanger.exhaustOutletAirNode().get());
  exchanger.resetExhaustOutletAirNode();
  EXPECT_FALSE(exchanger.exhaustOutletAirNode());

  GeneratorFuelCell generator(model);
  EXPECT_TRUE(generator.setPointer(openstudio::Generator_FuelCellFields::HeatExchangerName, exchanger.handle()));
  ASSERT_TRUE(exchanger.fuelCell());
  EXPECT_EQ(generator, exchanger.fuelCell().get());
}

TEST_F(EPModelFixture, GeneratorFuelCellExhaustGasToWaterHeatExchanger_ScalarAccessors_RoundTrip) {
  Model model;
  GeneratorFuelCellExhaustGasToWaterHeatExchanger exchanger(model);

  EXPECT_TRUE(exchanger.setHeatRecoveryWaterMaximumFlowRate(0.0042));
  EXPECT_DOUBLE_EQ(0.0042, exchanger.heatRecoveryWaterMaximumFlowRate());
  exchanger.resetHeatRecoveryWaterMaximumFlowRate();
  EXPECT_DOUBLE_EQ(0.0, exchanger.heatRecoveryWaterMaximumFlowRate());

  auto methods = GeneratorFuelCellExhaustGasToWaterHeatExchanger::heatExchangerCalculationMethodValues();
  ASSERT_FALSE(methods.empty());
  EXPECT_TRUE(exchanger.setHeatExchangerCalculationMethod(methods.front()));
  EXPECT_EQ(methods.front(), exchanger.heatExchangerCalculationMethod());
  exchanger.resetHeatExchangerCalculationMethod();
  EXPECT_EQ("FixedEffectiveness", exchanger.heatExchangerCalculationMethod());

  EXPECT_TRUE(exchanger.setMethod1HeatExchangerEffectiveness(0.91));
  ASSERT_TRUE(exchanger.method1HeatExchangerEffectiveness());
  EXPECT_DOUBLE_EQ(0.91, exchanger.method1HeatExchangerEffectiveness().get());
  exchanger.resetMethod1HeatExchangerEffectiveness();
  EXPECT_FALSE(exchanger.method1HeatExchangerEffectiveness());

  EXPECT_TRUE(exchanger.setMethod2Parameterhxs0(1.0));
  EXPECT_TRUE(exchanger.setMethod2Parameterhxs1(2.0));
  EXPECT_TRUE(exchanger.setMethod2Parameterhxs2(3.0));
  EXPECT_TRUE(exchanger.setMethod2Parameterhxs3(4.0));
  EXPECT_TRUE(exchanger.setMethod2Parameterhxs4(5.0));
  ASSERT_TRUE(exchanger.method2Parameterhxs0());
  ASSERT_TRUE(exchanger.method2Parameterhxs1());
  ASSERT_TRUE(exchanger.method2Parameterhxs2());
  ASSERT_TRUE(exchanger.method2Parameterhxs3());
  ASSERT_TRUE(exchanger.method2Parameterhxs4());
  EXPECT_DOUBLE_EQ(1.0, exchanger.method2Parameterhxs0().get());
  EXPECT_DOUBLE_EQ(2.0, exchanger.method2Parameterhxs1().get());
  EXPECT_DOUBLE_EQ(3.0, exchanger.method2Parameterhxs2().get());
  EXPECT_DOUBLE_EQ(4.0, exchanger.method2Parameterhxs3().get());
  EXPECT_DOUBLE_EQ(5.0, exchanger.method2Parameterhxs4().get());
  exchanger.resetMethod2Parameterhxs0();
  exchanger.resetMethod2Parameterhxs1();
  exchanger.resetMethod2Parameterhxs2();
  exchanger.resetMethod2Parameterhxs3();
  exchanger.resetMethod2Parameterhxs4();
  EXPECT_FALSE(exchanger.method2Parameterhxs0());
  EXPECT_FALSE(exchanger.method2Parameterhxs1());
  EXPECT_FALSE(exchanger.method2Parameterhxs2());
  EXPECT_FALSE(exchanger.method2Parameterhxs3());
  EXPECT_FALSE(exchanger.method2Parameterhxs4());

  EXPECT_TRUE(exchanger.setMethod3h0GasCoefficient(1.1));
  EXPECT_TRUE(exchanger.setMethod3NdotGasRefCoefficient(1.2));
  EXPECT_TRUE(exchanger.setMethod3nCoefficient(1.3));
  EXPECT_TRUE(exchanger.setMethod3GasArea(1.4));
  EXPECT_TRUE(exchanger.setMethod3h0WaterCoefficient(1.5));
  EXPECT_TRUE(exchanger.setMethod3NdotWaterrefCoefficient(1.6));
  EXPECT_TRUE(exchanger.setMethod3mCoefficient(1.7));
  EXPECT_TRUE(exchanger.setMethod3WaterArea(1.8));
  EXPECT_TRUE(exchanger.setMethod3FAdjustmentFactor(1.9));
  ASSERT_TRUE(exchanger.method3h0GasCoefficient());
  ASSERT_TRUE(exchanger.method3NdotGasRefCoefficient());
  ASSERT_TRUE(exchanger.method3nCoefficient());
  ASSERT_TRUE(exchanger.method3GasArea());
  ASSERT_TRUE(exchanger.method3h0WaterCoefficient());
  ASSERT_TRUE(exchanger.method3NdotWaterrefCoefficient());
  ASSERT_TRUE(exchanger.method3mCoefficient());
  ASSERT_TRUE(exchanger.method3WaterArea());
  ASSERT_TRUE(exchanger.method3FAdjustmentFactor());
  EXPECT_DOUBLE_EQ(1.1, exchanger.method3h0GasCoefficient().get());
  EXPECT_DOUBLE_EQ(1.2, exchanger.method3NdotGasRefCoefficient().get());
  EXPECT_DOUBLE_EQ(1.3, exchanger.method3nCoefficient().get());
  EXPECT_DOUBLE_EQ(1.4, exchanger.method3GasArea().get());
  EXPECT_DOUBLE_EQ(1.5, exchanger.method3h0WaterCoefficient().get());
  EXPECT_DOUBLE_EQ(1.6, exchanger.method3NdotWaterrefCoefficient().get());
  EXPECT_DOUBLE_EQ(1.7, exchanger.method3mCoefficient().get());
  EXPECT_DOUBLE_EQ(1.8, exchanger.method3WaterArea().get());
  EXPECT_DOUBLE_EQ(1.9, exchanger.method3FAdjustmentFactor().get());
  exchanger.resetMethod3h0GasCoefficient();
  exchanger.resetMethod3NdotGasRefCoefficient();
  exchanger.resetMethod3nCoefficient();
  exchanger.resetMethod3GasArea();
  exchanger.resetMethod3h0WaterCoefficient();
  exchanger.resetMethod3NdotWaterrefCoefficient();
  exchanger.resetMethod3mCoefficient();
  exchanger.resetMethod3WaterArea();
  exchanger.resetMethod3FAdjustmentFactor();
  EXPECT_FALSE(exchanger.method3h0GasCoefficient());
  EXPECT_FALSE(exchanger.method3NdotGasRefCoefficient());
  EXPECT_FALSE(exchanger.method3nCoefficient());
  EXPECT_FALSE(exchanger.method3GasArea());
  EXPECT_FALSE(exchanger.method3h0WaterCoefficient());
  EXPECT_FALSE(exchanger.method3NdotWaterrefCoefficient());
  EXPECT_FALSE(exchanger.method3mCoefficient());
  EXPECT_FALSE(exchanger.method3WaterArea());
  EXPECT_FALSE(exchanger.method3FAdjustmentFactor());

  EXPECT_TRUE(exchanger.setMethod4hxl1Coefficient(2.1));
  EXPECT_TRUE(exchanger.setMethod4hxl2Coefficient(2.2));
  EXPECT_TRUE(exchanger.setMethod4CondensationThreshold(2.3));
  ASSERT_TRUE(exchanger.method4hxl1Coefficient());
  ASSERT_TRUE(exchanger.method4hxl2Coefficient());
  ASSERT_TRUE(exchanger.method4CondensationThreshold());
  EXPECT_DOUBLE_EQ(2.1, exchanger.method4hxl1Coefficient().get());
  EXPECT_DOUBLE_EQ(2.2, exchanger.method4hxl2Coefficient().get());
  EXPECT_DOUBLE_EQ(2.3, exchanger.method4CondensationThreshold().get());
  exchanger.resetMethod4hxl1Coefficient();
  exchanger.resetMethod4hxl2Coefficient();
  exchanger.resetMethod4CondensationThreshold();
  EXPECT_FALSE(exchanger.method4hxl1Coefficient());
  EXPECT_FALSE(exchanger.method4hxl2Coefficient());
  EXPECT_FALSE(exchanger.method4CondensationThreshold());
}

TEST_F(EPModelFixture, GeneratorFuelCellExhaustGasToWaterHeatExchanger_AddToNode_PlantLoopOnly) {
  Model model;
  AirLoopHVAC airLoop(model);
  PlantLoop plantLoop(model);
  GeneratorFuelCellExhaustGasToWaterHeatExchanger supplyExchanger(model);
  GeneratorFuelCellExhaustGasToWaterHeatExchanger demandExchanger(model);

  auto airSupplyNode = airLoop.supplyOutletNode();
  auto airDemandNode = airLoop.zoneSplitter().lastOutletModelObject()->cast<Node>();
  auto plantSupplyNode = plantLoop.supplyOutletNode();
  auto plantDemandNode = plantLoop.demandInletNode();
  Node unconnectedNode(model);

  EXPECT_FALSE(supplyExchanger.addToNode(airSupplyNode));
  EXPECT_FALSE(supplyExchanger.addToNode(airDemandNode));
  EXPECT_FALSE(supplyExchanger.addToNode(unconnectedNode));

  EXPECT_TRUE(supplyExchanger.addToNode(plantSupplyNode));
  ASSERT_TRUE(supplyExchanger.loop());
  EXPECT_EQ(plantLoop.handle(), supplyExchanger.loop()->handle());
  ASSERT_TRUE(supplyExchanger.inletModelObject());
  ASSERT_TRUE(supplyExchanger.outletModelObject());
  EXPECT_TRUE(plantLoop.supplyComponent(supplyExchanger.handle()));
  EXPECT_FALSE(plantLoop.demandComponent(supplyExchanger.handle()));

  EXPECT_TRUE(demandExchanger.addToNode(plantDemandNode));
  ASSERT_TRUE(demandExchanger.loop());
  EXPECT_EQ(plantLoop.handle(), demandExchanger.loop()->handle());
  ASSERT_TRUE(demandExchanger.inletModelObject());
  ASSERT_TRUE(demandExchanger.outletModelObject());
  EXPECT_TRUE(plantLoop.demandComponent(demandExchanger.handle()));
  EXPECT_FALSE(plantLoop.supplyComponent(demandExchanger.handle()));

  EXPECT_TRUE(supplyExchanger.removeFromLoop());
  EXPECT_FALSE(supplyExchanger.loop());
  EXPECT_TRUE(demandExchanger.removeFromLoop());
  EXPECT_FALSE(demandExchanger.loop());
}
