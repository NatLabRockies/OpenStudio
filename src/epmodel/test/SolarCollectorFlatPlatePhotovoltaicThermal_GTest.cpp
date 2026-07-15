/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../StraightComponent/Node.hpp"
#include "../StraightComponent/SolarCollectorFlatPlatePhotovoltaicThermal.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"

#include <utilities/idd/SolarCollector_FlatPlate_PhotovoltaicThermal_FieldEnums.hxx>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, SolarCollectorFlatPlatePhotovoltaicThermal_DefaultConstructor) {
  Model model;
  SolarCollectorFlatPlatePhotovoltaicThermal object(model);
  EXPECT_EQ(SolarCollectorFlatPlatePhotovoltaicThermal::iddObjectType(), object.iddObject().type());
  EXPECT_FALSE(object.nameString().empty());
}

TEST_F(EPModelFixture, SolarCollectorFlatPlatePhotovoltaicThermal_ScalarAccessors_RoundTrip) {
  Model model;
  SolarCollectorFlatPlatePhotovoltaicThermal object(model);

  EXPECT_FALSE(object.designFlowRate());
  EXPECT_FALSE(object.isDesignFlowRateAutosized());

  EXPECT_TRUE(object.setDesignFlowRate(0.0123));
  ASSERT_TRUE(object.designFlowRate());
  EXPECT_DOUBLE_EQ(0.0123, object.designFlowRate().get());
  EXPECT_FALSE(object.isDesignFlowRateAutosized());

  object.autosizeDesignFlowRate();
  EXPECT_TRUE(object.isDesignFlowRateAutosized());

  object.resetDesignFlowRate();
  EXPECT_FALSE(object.designFlowRate());
}

TEST_F(EPModelFixture, SolarCollectorFlatPlatePhotovoltaicThermal_AddToNode_RoutesByLoopContext) {
  Model model;

  SolarCollectorFlatPlatePhotovoltaicThermal airCollector(model);
  AirLoopHVAC airLoop(model);

  auto airSupplyOutletNode = airLoop.supplyOutletNode();
  EXPECT_FALSE(airCollector.addToNode(airSupplyOutletNode));
  EXPECT_FALSE(airCollector.loop());

  auto demandBranchObject = airLoop.zoneSplitter().lastOutletModelObject();
  ASSERT_TRUE(demandBranchObject);
  auto demandBranchNode = demandBranchObject->optionalCast<Node>();
  ASSERT_TRUE(demandBranchNode);
  EXPECT_FALSE(airCollector.addToNode(*demandBranchNode));
  EXPECT_FALSE(airCollector.loop());

  AirLoopHVACOutdoorAirSystem oaSystem(model);
  auto airSupplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(oaSystem.addToNode(airSupplyInletNode));
  auto outboardOANode = oaSystem.outboardOANode();
  ASSERT_TRUE(outboardOANode);
  EXPECT_TRUE(airCollector.addToNode(*outboardOANode));
  EXPECT_TRUE(oaSystem.oaComponent(airCollector.handle()).has_value());
  ASSERT_TRUE(airCollector.getString(openstudio::SolarCollector_FlatPlate_PhotovoltaicThermalFields::ThermalWorkingFluidType, true));
  EXPECT_EQ("Air", airCollector.getString(openstudio::SolarCollector_FlatPlate_PhotovoltaicThermalFields::ThermalWorkingFluidType, true).get());
  EXPECT_TRUE(airCollector.getModelObjectTarget<Node>(openstudio::SolarCollector_FlatPlate_PhotovoltaicThermalFields::AirInletNodeName).has_value());
  EXPECT_TRUE(airCollector.getModelObjectTarget<Node>(openstudio::SolarCollector_FlatPlate_PhotovoltaicThermalFields::AirOutletNodeName).has_value());
  EXPECT_FALSE(
    airCollector.getModelObjectTarget<Node>(openstudio::SolarCollector_FlatPlate_PhotovoltaicThermalFields::WaterInletNodeName).has_value());
  EXPECT_FALSE(
    airCollector.getModelObjectTarget<Node>(openstudio::SolarCollector_FlatPlate_PhotovoltaicThermalFields::WaterOutletNodeName).has_value());

  SolarCollectorFlatPlatePhotovoltaicThermal waterCollector(model);
  PlantLoop plantLoop(model);
  auto plantDemandOutletNode = plantLoop.demandOutletNode();
  EXPECT_FALSE(waterCollector.addToNode(plantDemandOutletNode));
  EXPECT_FALSE(waterCollector.loop());

  auto plantSupplyOutletNode = plantLoop.supplyOutletNode();
  EXPECT_TRUE(waterCollector.addToNode(plantSupplyOutletNode));
  ASSERT_TRUE(waterCollector.loop());
  ASSERT_TRUE(waterCollector.plantLoop());
  EXPECT_EQ(plantLoop.handle(), waterCollector.plantLoop()->handle());
  ASSERT_TRUE(waterCollector.getString(openstudio::SolarCollector_FlatPlate_PhotovoltaicThermalFields::ThermalWorkingFluidType, true));
  EXPECT_EQ("Water", waterCollector.getString(openstudio::SolarCollector_FlatPlate_PhotovoltaicThermalFields::ThermalWorkingFluidType, true).get());
  EXPECT_TRUE(
    waterCollector.getModelObjectTarget<Node>(openstudio::SolarCollector_FlatPlate_PhotovoltaicThermalFields::WaterInletNodeName).has_value());
  EXPECT_TRUE(
    waterCollector.getModelObjectTarget<Node>(openstudio::SolarCollector_FlatPlate_PhotovoltaicThermalFields::WaterOutletNodeName).has_value());
  EXPECT_FALSE(
    waterCollector.getModelObjectTarget<Node>(openstudio::SolarCollector_FlatPlate_PhotovoltaicThermalFields::AirInletNodeName).has_value());
  EXPECT_FALSE(
    waterCollector.getModelObjectTarget<Node>(openstudio::SolarCollector_FlatPlate_PhotovoltaicThermalFields::AirOutletNodeName).has_value());

  EXPECT_FALSE(waterCollector.addToNode(plantDemandOutletNode));
  ASSERT_TRUE(waterCollector.plantLoop());
  EXPECT_EQ(plantLoop.handle(), waterCollector.plantLoop()->handle());
  EXPECT_FALSE(waterCollector.airLoopHVAC());
  EXPECT_EQ("Water", waterCollector.getString(openstudio::SolarCollector_FlatPlate_PhotovoltaicThermalFields::ThermalWorkingFluidType, true).get());
  EXPECT_TRUE(
    waterCollector.getModelObjectTarget<Node>(openstudio::SolarCollector_FlatPlate_PhotovoltaicThermalFields::WaterInletNodeName).has_value());
  EXPECT_TRUE(
    waterCollector.getModelObjectTarget<Node>(openstudio::SolarCollector_FlatPlate_PhotovoltaicThermalFields::WaterOutletNodeName).has_value());

  AirLoopHVAC moveAirLoop(model);
  AirLoopHVACOutdoorAirSystem moveOASystem(model);
  auto moveAirSupplyInletNode = moveAirLoop.supplyInletNode();
  ASSERT_TRUE(moveOASystem.addToNode(moveAirSupplyInletNode));
  auto moveOutboardOANode = moveOASystem.outboardOANode();
  ASSERT_TRUE(moveOutboardOANode);

  EXPECT_TRUE(waterCollector.addToNode(*moveOutboardOANode));
  EXPECT_FALSE(waterCollector.plantLoop());
  EXPECT_TRUE(moveOASystem.oaComponent(waterCollector.handle()).has_value());
  EXPECT_EQ("Air", waterCollector.getString(openstudio::SolarCollector_FlatPlate_PhotovoltaicThermalFields::ThermalWorkingFluidType, true).get());
  EXPECT_TRUE(
    waterCollector.getModelObjectTarget<Node>(openstudio::SolarCollector_FlatPlate_PhotovoltaicThermalFields::AirInletNodeName).has_value());
  EXPECT_TRUE(
    waterCollector.getModelObjectTarget<Node>(openstudio::SolarCollector_FlatPlate_PhotovoltaicThermalFields::AirOutletNodeName).has_value());
}
