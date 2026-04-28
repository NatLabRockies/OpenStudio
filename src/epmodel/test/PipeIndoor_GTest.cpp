/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../LayeredConstruction/Construction.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../ResourceObject/ScheduleTypeLimits.hpp"
#include "../Schedule/ScheduleCompact.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"
#include "../StraightComponent/Node.hpp"
#include "../StraightComponent/PipeIndoor.hpp"
#include "../StraightComponent/PipeIndoor_Impl.hpp"
#include <utilities/idd/Pipe_Indoor_FieldEnums.hxx>
#include <algorithm>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, PipeIndoor_DefaultConstructor) {
  Model model;
  PipeIndoor pipe(model);
  EXPECT_EQ(PipeIndoor::iddObjectType(), pipe.iddObject().type());
  EXPECT_FALSE(pipe.nameString().empty());

  EXPECT_EQ(openstudio::Pipe_IndoorFields::FluidInletNodeName, pipe.inletPort());
  EXPECT_EQ(openstudio::Pipe_IndoorFields::FluidOutletNodeName, pipe.outletPort());

  EXPECT_EQ("Zone", pipe.environmentType());
  EXPECT_DOUBLE_EQ(0.05, pipe.pipeInsideDiameter());
  EXPECT_DOUBLE_EQ(100.0, pipe.pipeLength());
}

TEST_F(EPModelFixture, PipeIndoor_ScalarAccessors_RoundTrip) {
  Model model;
  PipeIndoor pipe(model);

  const auto envValues = PipeIndoor::environmentTypeValues();
  EXPECT_TRUE(std::find(envValues.begin(), envValues.end(), "Zone") != envValues.end());
  EXPECT_TRUE(std::find(envValues.begin(), envValues.end(), "Schedule") != envValues.end());

  EXPECT_TRUE(pipe.setEnvironmentType("Schedule"));
  EXPECT_EQ("Schedule", pipe.environmentType());

  EXPECT_TRUE(pipe.setPipeInsideDiameter(0.125));
  EXPECT_DOUBLE_EQ(0.125, pipe.pipeInsideDiameter());
  EXPECT_FALSE(pipe.setPipeInsideDiameter(-10.0));
  EXPECT_DOUBLE_EQ(0.125, pipe.pipeInsideDiameter());

  EXPECT_TRUE(pipe.setPipeLength(42.0));
  EXPECT_DOUBLE_EQ(42.0, pipe.pipeLength());
  EXPECT_FALSE(pipe.setPipeLength(-10.0));
  EXPECT_DOUBLE_EQ(42.0, pipe.pipeLength());

  EXPECT_FALSE(pipe.setEnvironmentType("InvalidOption"));
}

TEST_F(EPModelFixture, PipeIndoor_RelationshipAccessors_AndScheduleValidation) {
  Model model;
  PipeIndoor pipe(model);

  Construction construction(model);
  EXPECT_TRUE(pipe.setConstruction(construction));
  ASSERT_TRUE(pipe.construction());
  EXPECT_EQ(construction.handle(), pipe.construction()->handle());
  pipe.resetConstruction();
  EXPECT_FALSE(pipe.construction());

  ThermalZone zone(model);
  EXPECT_TRUE(pipe.setAmbientTemperatureZone(zone));
  ASSERT_TRUE(pipe.ambientTemperatureZone());
  EXPECT_EQ(zone.handle(), pipe.ambientTemperatureZone()->handle());
  pipe.resetAmbientTemperatureZone();
  EXPECT_FALSE(pipe.ambientTemperatureZone());

  ScheduleCompact temperatureSchedule(model);
  ASSERT_TRUE(temperatureSchedule.setToConstantValue(21.5));
  EXPECT_TRUE(pipe.setAmbientTemperatureSchedule(temperatureSchedule));
  ASSERT_TRUE(pipe.ambientTemperatureSchedule());
  EXPECT_EQ(temperatureSchedule.handle(), pipe.ambientTemperatureSchedule()->handle());
  ASSERT_TRUE(temperatureSchedule.scheduleTypeLimits());
  ASSERT_TRUE(temperatureSchedule.scheduleTypeLimits()->numericType());
  EXPECT_EQ("Continuous", *temperatureSchedule.scheduleTypeLimits()->numericType());
  EXPECT_EQ("Temperature", temperatureSchedule.scheduleTypeLimits()->unitType());
  EXPECT_FALSE(temperatureSchedule.scheduleTypeLimits()->lowerLimitValue());
  EXPECT_FALSE(temperatureSchedule.scheduleTypeLimits()->upperLimitValue());

  ScheduleCompact velocitySchedule(model);
  ASSERT_TRUE(velocitySchedule.setToConstantValue(0.35));
  EXPECT_TRUE(pipe.setAmbientAirVelocitySchedule(velocitySchedule));
  ASSERT_TRUE(pipe.ambientAirVelocitySchedule());
  EXPECT_EQ(velocitySchedule.handle(), pipe.ambientAirVelocitySchedule()->handle());
  ASSERT_TRUE(velocitySchedule.scheduleTypeLimits());
  ASSERT_TRUE(velocitySchedule.scheduleTypeLimits()->numericType());
  EXPECT_EQ("Continuous", *velocitySchedule.scheduleTypeLimits()->numericType());
  EXPECT_EQ("Velocity", velocitySchedule.scheduleTypeLimits()->unitType());
  ASSERT_TRUE(velocitySchedule.scheduleTypeLimits()->lowerLimitValue());
  EXPECT_DOUBLE_EQ(0.0, *velocitySchedule.scheduleTypeLimits()->lowerLimitValue());
  EXPECT_FALSE(velocitySchedule.scheduleTypeLimits()->upperLimitValue());

  ScheduleCompact wrongTemperatureSchedule(model);
  ASSERT_TRUE(wrongTemperatureSchedule.setToConstantValue(21.0));
  ScheduleTypeLimits discreteTemperatureLimits(model);
  ASSERT_TRUE(discreteTemperatureLimits.setUnitType("Temperature"));
  ASSERT_TRUE(discreteTemperatureLimits.setNumericType("Discrete"));
  ASSERT_TRUE(wrongTemperatureSchedule.setScheduleTypeLimits(discreteTemperatureLimits));
  EXPECT_FALSE(pipe.setAmbientTemperatureSchedule(wrongTemperatureSchedule));
  EXPECT_EQ(temperatureSchedule.cast<ModelObject>(), pipe.ambientTemperatureSchedule()->cast<ModelObject>());

  ScheduleCompact wrongVelocitySchedule(model);
  ASSERT_TRUE(wrongVelocitySchedule.setToConstantValue(0.1));
  ScheduleTypeLimits wrongVelocityLimits(model);
  ASSERT_TRUE(wrongVelocityLimits.setUnitType("Velocity"));
  ASSERT_TRUE(wrongVelocityLimits.setNumericType("Continuous"));
  ASSERT_TRUE(wrongVelocityLimits.setLowerLimitValue(-0.1));
  ASSERT_TRUE(wrongVelocitySchedule.setScheduleTypeLimits(wrongVelocityLimits));
  EXPECT_FALSE(pipe.setAmbientAirVelocitySchedule(wrongVelocitySchedule));
  EXPECT_EQ(velocitySchedule.cast<ModelObject>(), pipe.ambientAirVelocitySchedule()->cast<ModelObject>());

  pipe.resetAmbientTemperatureSchedule();
  pipe.resetAmbientAirVelocitySchedule();
  EXPECT_FALSE(pipe.ambientTemperatureSchedule());
  EXPECT_FALSE(pipe.ambientAirVelocitySchedule());
}

TEST_F(EPModelFixture, PipeIndoor_AddToNode_PlantOnlyAndClone) {
  Model model;
  PipeIndoor pipe(model);

  AirLoopHVAC airLoop(model);
  auto airSupplyOutletNode = airLoop.supplyOutletNode();
  EXPECT_FALSE(pipe.addToNode(airSupplyOutletNode));
  EXPECT_EQ(2u, airLoop.supplyComponents().size());

  auto airDemandNode = airLoop.zoneSplitter().lastOutletModelObject()->cast<Node>();
  EXPECT_FALSE(pipe.addToNode(airDemandNode));
  EXPECT_EQ(5u, airLoop.demandComponents().size());

  PlantLoop plantLoop(model);
  auto supplyOutletNode = plantLoop.supplyOutletNode();
  EXPECT_TRUE(pipe.addToNode(supplyOutletNode));
  EXPECT_EQ(7u, plantLoop.supplyComponents().size());
  ASSERT_TRUE(pipe.plantLoop());
  ASSERT_TRUE(pipe.inletModelObject());
  ASSERT_TRUE(pipe.outletModelObject());

  auto inletNode = pipe.getModelObjectTarget<Node>(openstudio::Pipe_IndoorFields::FluidInletNodeName);
  auto outletNode = pipe.getModelObjectTarget<Node>(openstudio::Pipe_IndoorFields::FluidOutletNodeName);
  ASSERT_TRUE(inletNode);
  ASSERT_TRUE(outletNode);
  EXPECT_EQ(pipe.inletModelObject()->handle(), inletNode->handle());
  EXPECT_EQ(pipe.outletModelObject()->handle(), outletNode->handle());

  auto demandOutletNode = plantLoop.demandOutletNode();
  EXPECT_TRUE(pipe.addToNode(demandOutletNode));
  EXPECT_EQ(7u, plantLoop.demandComponents().size());
  EXPECT_EQ(5u, plantLoop.supplyComponents().size());
  ASSERT_TRUE(pipe.plantLoop());
  ASSERT_TRUE(pipe.inletModelObject());
  ASSERT_TRUE(pipe.outletModelObject());

  PipeIndoor pipe2(model);
  EXPECT_TRUE(pipe2.addToNode(demandOutletNode));
  EXPECT_EQ(9u, plantLoop.demandComponents().size());

  PlantLoop plantLoop2(model);
  auto secondLoopDemandOutletNode = plantLoop2.demandOutletNode();
  EXPECT_TRUE(pipe.addToNode(secondLoopDemandOutletNode));
  EXPECT_EQ(7u, plantLoop2.demandComponents().size());
  EXPECT_EQ(7u, plantLoop.demandComponents().size());
  ASSERT_TRUE(pipe.loop());
  EXPECT_EQ(plantLoop2.handle(), pipe.loop()->handle());

  auto pipeCloneObject = model.addObject(pipe.idfObject());
  ASSERT_TRUE(pipeCloneObject);
  auto pipeClone = pipeCloneObject->cast<PipeIndoor>();
  supplyOutletNode = plantLoop.supplyOutletNode();
  EXPECT_TRUE(pipeClone.addToNode(supplyOutletNode));
  EXPECT_EQ(7u, plantLoop.supplyComponents().size());
  ASSERT_TRUE(pipeClone.inletModelObject());
  ASSERT_TRUE(pipeClone.outletModelObject());

  ASSERT_TRUE(pipe.loop());
  ASSERT_TRUE(pipeClone.loop());
  ASSERT_TRUE(pipeClone.inletModelObject());
  ASSERT_TRUE(pipeClone.outletModelObject());

  pipe.disconnect();
  EXPECT_FALSE(pipe.loop());
  EXPECT_FALSE(pipe.inletModelObject());
  EXPECT_FALSE(pipe.outletModelObject());
  EXPECT_EQ(5u, plantLoop2.demandComponents().size());

  pipeClone.disconnect();
  EXPECT_FALSE(pipeClone.loop());
  EXPECT_FALSE(pipeClone.inletModelObject());
  EXPECT_FALSE(pipeClone.outletModelObject());
  EXPECT_EQ(5u, plantLoop.supplyComponents().size());
}
