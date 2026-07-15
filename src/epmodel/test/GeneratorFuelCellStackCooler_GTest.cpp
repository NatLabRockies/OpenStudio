/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Generator/GeneratorFuelCell.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"
#include "../StraightComponent/GeneratorFuelCellStackCooler.hpp"
#include "../StraightComponent/Node.hpp"

#include <utilities/idd/Generator_FuelCell_FieldEnums.hxx>

#include <algorithm>
#include <array>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, GeneratorFuelCellStackCooler_DefaultConstructor) {
  Model model;
  GeneratorFuelCellStackCooler stackCooler(model);
  EXPECT_EQ(GeneratorFuelCellStackCooler::iddObjectType(), stackCooler.iddObject().type());
}

TEST_F(EPModelFixture, GeneratorFuelCellStackCooler_ScalarAccessors_RoundTrip) {
  Model model;
  GeneratorFuelCellStackCooler stackCooler(model);

  EXPECT_DOUBLE_EQ(20.0, stackCooler.nominalStackTemperature());
  EXPECT_TRUE(stackCooler.setNominalStackTemperature(200.0));
  EXPECT_DOUBLE_EQ(200.0, stackCooler.nominalStackTemperature());
  stackCooler.resetNominalStackTemperature();
  EXPECT_DOUBLE_EQ(20.0, stackCooler.nominalStackTemperature());

  EXPECT_TRUE(stackCooler.setActualStackTemperature(210.0));
  EXPECT_DOUBLE_EQ(210.0, stackCooler.actualStackTemperature());
  stackCooler.resetActualStackTemperature();
  EXPECT_DOUBLE_EQ(20.0, stackCooler.actualStackTemperature());

  EXPECT_TRUE(stackCooler.setCoefficientr0(0.1));
  EXPECT_TRUE(stackCooler.setCoefficientr1(0.2));
  EXPECT_TRUE(stackCooler.setCoefficientr2(0.3));
  EXPECT_TRUE(stackCooler.setCoefficientr3(0.4));
  EXPECT_DOUBLE_EQ(0.1, stackCooler.coefficientr0());
  EXPECT_DOUBLE_EQ(0.2, stackCooler.coefficientr1());
  EXPECT_DOUBLE_EQ(0.3, stackCooler.coefficientr2());
  EXPECT_DOUBLE_EQ(0.4, stackCooler.coefficientr3());

  EXPECT_TRUE(stackCooler.setStackCoolantFlowRate(1.25));
  EXPECT_TRUE(stackCooler.setStackCoolerUFactorTimesAreaValue(1.35));
  EXPECT_TRUE(stackCooler.setFscogenAdjustmentFactor(0.45));
  EXPECT_DOUBLE_EQ(1.25, stackCooler.stackCoolantFlowRate());
  EXPECT_DOUBLE_EQ(1.35, stackCooler.stackCoolerUFactorTimesAreaValue());
  EXPECT_DOUBLE_EQ(0.45, stackCooler.fscogenAdjustmentFactor());

  EXPECT_TRUE(stackCooler.setStackCogenerationExchangerArea(2.1));
  EXPECT_TRUE(stackCooler.setStackCogenerationExchangerNominalFlowRate(2.2));
  EXPECT_TRUE(stackCooler.setStackCogenerationExchangerNominalHeatTransferCoefficient(2.3));
  EXPECT_TRUE(stackCooler.setStackCogenerationExchangerNominalHeatTransferCoefficientExponent(2.4));
  EXPECT_DOUBLE_EQ(2.1, stackCooler.stackCogenerationExchangerArea());
  EXPECT_DOUBLE_EQ(2.2, stackCooler.stackCogenerationExchangerNominalFlowRate());
  EXPECT_DOUBLE_EQ(2.3, stackCooler.stackCogenerationExchangerNominalHeatTransferCoefficient());
  EXPECT_DOUBLE_EQ(2.4, stackCooler.stackCogenerationExchangerNominalHeatTransferCoefficientExponent());

  EXPECT_TRUE(stackCooler.setStackCoolerPumpPower(300.0));
  EXPECT_DOUBLE_EQ(300.0, stackCooler.stackCoolerPumpPower());

  EXPECT_FALSE(stackCooler.setStackCoolerPumpHeatLossFraction(2.0));
  EXPECT_TRUE(stackCooler.setStackCoolerPumpHeatLossFraction(0.7));
  EXPECT_DOUBLE_EQ(0.7, stackCooler.stackCoolerPumpHeatLossFraction());

  EXPECT_TRUE(stackCooler.setStackAirCoolerFanCoefficientf0(3.1));
  EXPECT_TRUE(stackCooler.setStackAirCoolerFanCoefficientf1(3.2));
  EXPECT_TRUE(stackCooler.setStackAirCoolerFanCoefficientf2(3.3));
  EXPECT_DOUBLE_EQ(3.1, stackCooler.stackAirCoolerFanCoefficientf0());
  EXPECT_DOUBLE_EQ(3.2, stackCooler.stackAirCoolerFanCoefficientf1());
  EXPECT_DOUBLE_EQ(3.3, stackCooler.stackAirCoolerFanCoefficientf2());

  stackCooler.resetCoefficientr0();
  stackCooler.resetCoefficientr1();
  stackCooler.resetCoefficientr2();
  stackCooler.resetCoefficientr3();
  stackCooler.resetStackCoolantFlowRate();
  stackCooler.resetStackCoolerUFactorTimesAreaValue();
  stackCooler.resetFscogenAdjustmentFactor();
  stackCooler.resetStackCogenerationExchangerArea();
  stackCooler.resetStackCogenerationExchangerNominalFlowRate();
  stackCooler.resetStackCogenerationExchangerNominalHeatTransferCoefficient();
  stackCooler.resetStackCogenerationExchangerNominalHeatTransferCoefficientExponent();
  stackCooler.resetStackCoolerPumpPower();
  stackCooler.resetStackCoolerPumpHeatLossFraction();
  stackCooler.resetStackAirCoolerFanCoefficientf0();
  stackCooler.resetStackAirCoolerFanCoefficientf1();
  stackCooler.resetStackAirCoolerFanCoefficientf2();

  EXPECT_DOUBLE_EQ(0.0, stackCooler.coefficientr0());
  EXPECT_DOUBLE_EQ(0.0, stackCooler.coefficientr1());
  EXPECT_DOUBLE_EQ(0.0, stackCooler.coefficientr2());
  EXPECT_DOUBLE_EQ(0.0, stackCooler.coefficientr3());
  EXPECT_DOUBLE_EQ(1.0, stackCooler.stackCoolantFlowRate());
  EXPECT_DOUBLE_EQ(1.0, stackCooler.stackCoolerUFactorTimesAreaValue());
  EXPECT_DOUBLE_EQ(0.0, stackCooler.fscogenAdjustmentFactor());
  EXPECT_DOUBLE_EQ(1.0, stackCooler.stackCogenerationExchangerArea());
  EXPECT_DOUBLE_EQ(1.0, stackCooler.stackCogenerationExchangerNominalFlowRate());
  EXPECT_DOUBLE_EQ(0.0, stackCooler.stackCogenerationExchangerNominalHeatTransferCoefficient());
  EXPECT_DOUBLE_EQ(0.0, stackCooler.stackCogenerationExchangerNominalHeatTransferCoefficientExponent());
  EXPECT_DOUBLE_EQ(0.0, stackCooler.stackCoolerPumpPower());
  EXPECT_DOUBLE_EQ(0.0, stackCooler.stackCoolerPumpHeatLossFraction());
  EXPECT_DOUBLE_EQ(0.0, stackCooler.stackAirCoolerFanCoefficientf0());
  EXPECT_DOUBLE_EQ(0.0, stackCooler.stackAirCoolerFanCoefficientf1());
  EXPECT_DOUBLE_EQ(0.0, stackCooler.stackAirCoolerFanCoefficientf2());
}

TEST_F(EPModelFixture, GeneratorFuelCellStackCooler_RelationshipsAndAddToNode_PlantLoopOnly) {
  Model model;
  GeneratorFuelCellStackCooler stackCooler(model);

  EXPECT_FALSE(stackCooler.fuelCell());

  GeneratorFuelCell generator(model);
  EXPECT_TRUE(generator.setPointer(openstudio::Generator_FuelCellFields::StackCoolerName, stackCooler.handle()));
  ASSERT_TRUE(stackCooler.fuelCell());
  EXPECT_EQ(generator, stackCooler.fuelCell().get());

  GeneratorFuelCell replacementGenerator(model);
  EXPECT_TRUE(replacementGenerator.setPointer(openstudio::Generator_FuelCellFields::StackCoolerName, stackCooler.handle()));
  ASSERT_TRUE(generator.getTarget(openstudio::Generator_FuelCellFields::StackCoolerName));
  ASSERT_TRUE(replacementGenerator.getTarget(openstudio::Generator_FuelCellFields::StackCoolerName));
  EXPECT_EQ(stackCooler.handle(), generator.getTarget(openstudio::Generator_FuelCellFields::StackCoolerName)->handle());
  EXPECT_EQ(stackCooler.handle(), replacementGenerator.getTarget(openstudio::Generator_FuelCellFields::StackCoolerName)->handle());
  const std::array<GeneratorFuelCell, 2> candidateOwners{generator, replacementGenerator};
  const auto expectedFallbackOwner = *std::max_element(candidateOwners.begin(), candidateOwners.end());
  ASSERT_TRUE(stackCooler.fuelCell());
  EXPECT_EQ(expectedFallbackOwner, stackCooler.fuelCell().get());

  AirLoopHVAC airLoop(model);
  PlantLoop plantLoop(model);
  GeneratorFuelCellStackCooler demandStackCooler(model);
  Node unconnectedNode(model);

  auto airSupplyNode = airLoop.supplyOutletNode();
  auto airDemandNode = airLoop.zoneSplitter().lastOutletModelObject()->cast<Node>();
  auto plantSupplyNode = plantLoop.supplyOutletNode();
  auto plantDemandNode = plantLoop.demandInletNode();

  EXPECT_FALSE(stackCooler.addToNode(airSupplyNode));
  EXPECT_FALSE(stackCooler.loop());
  EXPECT_FALSE(stackCooler.inletModelObject());
  EXPECT_FALSE(stackCooler.outletModelObject());

  EXPECT_FALSE(stackCooler.addToNode(airDemandNode));
  EXPECT_FALSE(stackCooler.loop());
  EXPECT_FALSE(stackCooler.inletModelObject());
  EXPECT_FALSE(stackCooler.outletModelObject());

  EXPECT_FALSE(stackCooler.addToNode(unconnectedNode));
  EXPECT_FALSE(stackCooler.loop());
  EXPECT_FALSE(stackCooler.inletModelObject());
  EXPECT_FALSE(stackCooler.outletModelObject());

  EXPECT_TRUE(stackCooler.addToNode(plantSupplyNode));
  ASSERT_TRUE(stackCooler.loop());
  EXPECT_EQ(plantLoop.handle(), stackCooler.loop()->handle());
  ASSERT_TRUE(stackCooler.inletModelObject());
  ASSERT_TRUE(stackCooler.outletModelObject());
  const auto stackCoolerInletHandle = stackCooler.inletModelObject()->handle();
  const auto stackCoolerOutletHandle = stackCooler.outletModelObject()->handle();
  EXPECT_TRUE(plantLoop.supplyComponent(stackCooler.handle()));
  EXPECT_FALSE(plantLoop.demandComponent(stackCooler.handle()));

  EXPECT_FALSE(stackCooler.addToNode(airSupplyNode));
  ASSERT_TRUE(stackCooler.loop());
  EXPECT_EQ(plantLoop.handle(), stackCooler.loop()->handle());
  ASSERT_TRUE(stackCooler.inletModelObject());
  ASSERT_TRUE(stackCooler.outletModelObject());
  EXPECT_EQ(stackCoolerInletHandle, stackCooler.inletModelObject()->handle());
  EXPECT_EQ(stackCoolerOutletHandle, stackCooler.outletModelObject()->handle());
  EXPECT_TRUE(plantLoop.supplyComponent(stackCooler.handle()));
  EXPECT_FALSE(plantLoop.demandComponent(stackCooler.handle()));

  EXPECT_TRUE(demandStackCooler.addToNode(plantDemandNode));
  ASSERT_TRUE(demandStackCooler.loop());
  EXPECT_EQ(plantLoop.handle(), demandStackCooler.loop()->handle());
  ASSERT_TRUE(demandStackCooler.inletModelObject());
  ASSERT_TRUE(demandStackCooler.outletModelObject());
  EXPECT_TRUE(plantLoop.demandComponent(demandStackCooler.handle()));
  EXPECT_FALSE(plantLoop.supplyComponent(demandStackCooler.handle()));

  PlantLoop secondPlantLoop(model);
  auto secondPlantSupplyNode = secondPlantLoop.supplyOutletNode();
  EXPECT_TRUE(stackCooler.addToNode(secondPlantSupplyNode));
  ASSERT_TRUE(stackCooler.loop());
  EXPECT_EQ(secondPlantLoop.handle(), stackCooler.loop()->handle());
  EXPECT_FALSE(plantLoop.supplyComponent(stackCooler.handle()));
  EXPECT_FALSE(plantLoop.demandComponent(stackCooler.handle()));
  EXPECT_TRUE(secondPlantLoop.supplyComponent(stackCooler.handle()));
  EXPECT_FALSE(secondPlantLoop.demandComponent(stackCooler.handle()));

  EXPECT_TRUE(stackCooler.removeFromLoop());
  EXPECT_FALSE(stackCooler.loop());
  EXPECT_TRUE(demandStackCooler.removeFromLoop());
  EXPECT_FALSE(demandStackCooler.loop());
}
