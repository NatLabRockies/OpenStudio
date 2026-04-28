/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include <utilities/idd/FluidCooler_SingleSpeed_FieldEnums.hxx>

#include "EPModelFixture.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"
#include "../StraightComponent/FluidCoolerSingleSpeed.hpp"
#include "../StraightComponent/Node.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, FluidCoolerSingleSpeed_DefaultConstructor) {
  Model model;
  FluidCoolerSingleSpeed fluidCooler(model);

  EXPECT_EQ(FluidCoolerSingleSpeed::iddObjectType(), fluidCooler.iddObject().type());
  EXPECT_FALSE(fluidCooler.nameString().empty());

  EXPECT_EQ("NominalCapacity", fluidCooler.performanceInputMethod());

  EXPECT_FALSE(fluidCooler.designAirFlowRateUfactorTimesAreaValue());
  EXPECT_TRUE(fluidCooler.isDesignAirFlowRateUfactorTimesAreaValueAutosized());

  EXPECT_DOUBLE_EQ(58601.0, fluidCooler.nominalCapacity());
  EXPECT_DOUBLE_EQ(51.67, fluidCooler.designEnteringWaterTemperature());
  EXPECT_DOUBLE_EQ(35.0, fluidCooler.designEnteringAirTemperature());
  EXPECT_DOUBLE_EQ(25.6, fluidCooler.designEnteringAirWetbulbTemperature());

  ASSERT_TRUE(fluidCooler.designWaterFlowRate());
  EXPECT_DOUBLE_EQ(0.001388, *fluidCooler.designWaterFlowRate());
  EXPECT_FALSE(fluidCooler.isDesignWaterFlowRateAutosized());

  ASSERT_TRUE(fluidCooler.designAirFlowRate());
  EXPECT_DOUBLE_EQ(9.911, *fluidCooler.designAirFlowRate());
  EXPECT_FALSE(fluidCooler.isDesignAirFlowRateAutosized());

  EXPECT_FALSE(fluidCooler.designAirFlowRateFanPower());
  EXPECT_TRUE(fluidCooler.isDesignAirFlowRateFanPowerAutosized());
}

TEST_F(EPModelFixture, FluidCoolerSingleSpeed_ScalarAccessors_RoundTrip) {
  Model model;
  FluidCoolerSingleSpeed fluidCooler(model);

  const auto performanceInputMethods = FluidCoolerSingleSpeed::performanceInputMethodValues();
  ASSERT_EQ(2u, performanceInputMethods.size());
  EXPECT_EQ("UFactorTimesAreaAndDesignWaterFlowRate", performanceInputMethods[0]);
  EXPECT_EQ("NominalCapacity", performanceInputMethods[1]);

  EXPECT_TRUE(fluidCooler.setPerformanceInputMethod("UFactorTimesAreaAndDesignWaterFlowRate"));
  EXPECT_EQ("UFactorTimesAreaAndDesignWaterFlowRate", fluidCooler.performanceInputMethod());

  EXPECT_TRUE(fluidCooler.setDesignAirFlowRateUfactorTimesAreaValue(1500.0));
  ASSERT_TRUE(fluidCooler.designAirFlowRateUfactorTimesAreaValue());
  EXPECT_DOUBLE_EQ(1500.0, *fluidCooler.designAirFlowRateUfactorTimesAreaValue());
  EXPECT_FALSE(fluidCooler.isDesignAirFlowRateUfactorTimesAreaValueAutosized());
  fluidCooler.autosizeDesignAirFlowRateUfactorTimesAreaValue();
  EXPECT_TRUE(fluidCooler.isDesignAirFlowRateUfactorTimesAreaValueAutosized());
  EXPECT_FALSE(fluidCooler.designAirFlowRateUfactorTimesAreaValue());

  EXPECT_TRUE(fluidCooler.setNominalCapacity(64000.0));
  EXPECT_DOUBLE_EQ(64000.0, fluidCooler.nominalCapacity());

  EXPECT_TRUE(fluidCooler.setDesignEnteringWaterTemperature(45.0));
  EXPECT_DOUBLE_EQ(45.0, fluidCooler.designEnteringWaterTemperature());

  EXPECT_TRUE(fluidCooler.setDesignEnteringAirTemperature(30.0));
  EXPECT_DOUBLE_EQ(30.0, fluidCooler.designEnteringAirTemperature());

  EXPECT_TRUE(fluidCooler.setDesignEnteringAirWetbulbTemperature(21.5));
  EXPECT_DOUBLE_EQ(21.5, fluidCooler.designEnteringAirWetbulbTemperature());

  EXPECT_TRUE(fluidCooler.setDesignWaterFlowRate(0.003));
  ASSERT_TRUE(fluidCooler.designWaterFlowRate());
  EXPECT_DOUBLE_EQ(0.003, *fluidCooler.designWaterFlowRate());
  EXPECT_FALSE(fluidCooler.isDesignWaterFlowRateAutosized());
  fluidCooler.autosizeDesignWaterFlowRate();
  EXPECT_TRUE(fluidCooler.isDesignWaterFlowRateAutosized());
  EXPECT_FALSE(fluidCooler.designWaterFlowRate());

  EXPECT_TRUE(fluidCooler.setDesignAirFlowRate(11.0));
  ASSERT_TRUE(fluidCooler.designAirFlowRate());
  EXPECT_DOUBLE_EQ(11.0, *fluidCooler.designAirFlowRate());
  EXPECT_FALSE(fluidCooler.isDesignAirFlowRateAutosized());
  fluidCooler.autosizeDesignAirFlowRate();
  EXPECT_TRUE(fluidCooler.isDesignAirFlowRateAutosized());
  EXPECT_FALSE(fluidCooler.designAirFlowRate());

  EXPECT_TRUE(fluidCooler.setDesignAirFlowRateFanPower(350.0));
  ASSERT_TRUE(fluidCooler.designAirFlowRateFanPower());
  EXPECT_DOUBLE_EQ(350.0, *fluidCooler.designAirFlowRateFanPower());
  EXPECT_FALSE(fluidCooler.isDesignAirFlowRateFanPowerAutosized());
  fluidCooler.autosizeDesignAirFlowRateFanPower();
  EXPECT_TRUE(fluidCooler.isDesignAirFlowRateFanPowerAutosized());
  EXPECT_FALSE(fluidCooler.designAirFlowRateFanPower());

  EXPECT_FALSE(fluidCooler.autosizedDesignAirFlowRateUfactorTimesAreaValue());
  EXPECT_FALSE(fluidCooler.autosizedDesignWaterFlowRate());
  EXPECT_FALSE(fluidCooler.autosizedDesignAirFlowRate());
  EXPECT_FALSE(fluidCooler.autosizedDesignAirFlowRateFanPower());
}

TEST_F(EPModelFixture, FluidCoolerSingleSpeed_AddToNode_PlantSupplyOnly) {
  Model model;
  FluidCoolerSingleSpeed fluidCooler(model);

  AirLoopHVAC airLoop(model);
  Node airSupplyOutletNode = airLoop.supplyOutletNode();
  EXPECT_FALSE(fluidCooler.addToNode(airSupplyOutletNode));
  EXPECT_FALSE(fluidCooler.loop());
  EXPECT_FALSE(fluidCooler.inletModelObject());
  EXPECT_FALSE(fluidCooler.outletModelObject());

  auto splitterBranch = airLoop.zoneSplitter().lastOutletModelObject();
  ASSERT_TRUE(splitterBranch);
  auto demandBranchNode = splitterBranch->optionalCast<Node>();
  ASSERT_TRUE(demandBranchNode);
  EXPECT_FALSE(fluidCooler.addToNode(*demandBranchNode));
  EXPECT_FALSE(fluidCooler.loop());
  EXPECT_FALSE(fluidCooler.inletModelObject());
  EXPECT_FALSE(fluidCooler.outletModelObject());

  PlantLoop plantLoop(model);
  Node plantSupplyOutletNode = plantLoop.supplyOutletNode();
  EXPECT_TRUE(fluidCooler.addToNode(plantSupplyOutletNode));
  ASSERT_TRUE(fluidCooler.loop());
  EXPECT_EQ(plantLoop.handle(), fluidCooler.loop()->handle());
  ASSERT_TRUE(fluidCooler.inletModelObject());
  ASSERT_TRUE(fluidCooler.outletModelObject());

  auto inletNode = fluidCooler.getModelObjectTarget<Node>(openstudio::FluidCooler_SingleSpeedFields::WaterInletNodeName);
  auto outletNode = fluidCooler.getModelObjectTarget<Node>(openstudio::FluidCooler_SingleSpeedFields::WaterOutletNodeName);
  ASSERT_TRUE(inletNode);
  ASSERT_TRUE(outletNode);
  EXPECT_EQ(fluidCooler.inletModelObject()->handle(), inletNode->handle());
  EXPECT_EQ(fluidCooler.outletModelObject()->handle(), outletNode->handle());

  FluidCoolerSingleSpeed secondFluidCooler(model);
  Node plantDemandOutletNode = plantLoop.demandOutletNode();
  EXPECT_FALSE(secondFluidCooler.addToNode(plantDemandOutletNode));
  EXPECT_FALSE(secondFluidCooler.loop());
  EXPECT_FALSE(secondFluidCooler.inletModelObject());
  EXPECT_FALSE(secondFluidCooler.outletModelObject());
}
