/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../ModelObject/EnergyManagementSystemActuator.hpp"
#include "../ModelObject/EnergyManagementSystemProgram.hpp"
#include "../ModelObject/EnergyManagementSystemProgramCallingManager.hpp"
#include "../StraightComponent/Node.hpp"
#include "../WaterToAirComponent/CoilUserDefined.hpp"

#include <utilities/idd/Coil_UserDefined_FieldEnums.hxx>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoilUserDefined_DefaultConstructor) {
  Model model;
  CoilUserDefined coil(model);
  EXPECT_EQ(CoilUserDefined::iddObjectType(), coil.iddObject().type());
  EXPECT_EQ(openstudio::Coil_UserDefinedFields::AirConnection1InletNodeName, coil.airInletPort());
  EXPECT_EQ(openstudio::Coil_UserDefinedFields::AirConnection1OutletNodeName, coil.airOutletPort());
  EXPECT_EQ(openstudio::Coil_UserDefinedFields::PlantConnectionInletNodeName, coil.waterInletPort());
  EXPECT_EQ(openstudio::Coil_UserDefinedFields::PlantConnectionOutletNodeName, coil.waterOutletPort());
  EXPECT_FALSE(coil.airInletModelObject());
  EXPECT_FALSE(coil.airOutletModelObject());
  EXPECT_FALSE(coil.waterInletModelObject());
  EXPECT_FALSE(coil.waterOutletModelObject());
  EXPECT_EQ(0, coil.numberofAirConnections());

  EXPECT_EQ("UserDefinedComponentModel", coil.overallModelSimulationProgramCallingManager().callingPoint());
  EXPECT_EQ("UserDefinedComponentModel", coil.modelSetupandSizingProgramCallingManager().callingPoint());
  EXPECT_FALSE(coil.overallSimulationProgram().handle().isNull());
  EXPECT_FALSE(coil.initializationSimulationProgram().handle().isNull());
  ASSERT_TRUE(coil.airOutletTemperatureActuator().actuatedComponent());
  EXPECT_EQ(coil.handle(), coil.airOutletTemperatureActuator().actuatedComponent()->handle());
  ASSERT_TRUE(coil.plantOutletTemperatureActuator().actuatedComponent());
  EXPECT_EQ(coil.handle(), coil.plantOutletTemperatureActuator().actuatedComponent()->handle());

  const auto children = coil.children();
  EXPECT_EQ(12u, children.size());
}

TEST_F(EPModelFixture, CoilUserDefined_ScalarAccessors_RoundTrip) {
  Model model;
  CoilUserDefined coil(model);

  ASSERT_TRUE(coil.setInt(openstudio::Coil_UserDefinedFields::NumberofAirConnections, 1));
  EXPECT_EQ(1, coil.numberofAirConnections());

  ASSERT_TRUE(coil.setInt(openstudio::Coil_UserDefinedFields::NumberofAirConnections, 2));
  EXPECT_EQ(2, coil.numberofAirConnections());
}

TEST_F(EPModelFixture, CoilUserDefined_EMSRelationshipsAndRename) {
  Model model;
  CoilUserDefined coil(model);
  ASSERT_TRUE(coil.setName("My CoilUserDefined"));

  ThermalZone ambientZone(model);
  EXPECT_TRUE(coil.setAmbientZone(ambientZone));
  ASSERT_TRUE(coil.ambientZone());
  EXPECT_EQ(ambientZone.handle(), coil.ambientZone()->handle());
  coil.resetAmbientZone();
  EXPECT_FALSE(coil.ambientZone());

  EnergyManagementSystemProgramCallingManager overallPCM(model);
  ASSERT_TRUE(overallPCM.setCallingPoint("UserDefinedComponentModel"));
  EnergyManagementSystemProgram overallProgram(model);
  ASSERT_TRUE(overallPCM.addProgram(overallProgram));
  EXPECT_TRUE(coil.setOverallModelSimulationProgramCallingManager(overallPCM));
  EXPECT_TRUE(coil.setOverallSimulationProgram(overallProgram));
  EXPECT_EQ(overallPCM.handle(), coil.overallModelSimulationProgramCallingManager().handle());
  EXPECT_EQ(overallProgram.handle(), coil.overallSimulationProgram().handle());

  EnergyManagementSystemProgramCallingManager sizingPCM(model);
  ASSERT_TRUE(sizingPCM.setCallingPoint("UserDefinedComponentModel"));
  EnergyManagementSystemProgram initializationProgram(model);
  ASSERT_TRUE(sizingPCM.addProgram(initializationProgram));
  EXPECT_TRUE(coil.setModelSetupandSizingProgramCallingManager(sizingPCM));
  EXPECT_TRUE(coil.setInitializationSimulationProgram(initializationProgram));
  EXPECT_EQ(sizingPCM.handle(), coil.modelSetupandSizingProgramCallingManager().handle());
  EXPECT_EQ(initializationProgram.handle(), coil.initializationSimulationProgram().handle());

  EnergyManagementSystemActuator airOutletTemperatureActuator(coil, "Air Connection 1", "Outlet Temperature");
  EXPECT_TRUE(coil.setAirOutletTemperatureActuator(airOutletTemperatureActuator));
  EXPECT_EQ(airOutletTemperatureActuator.handle(), coil.airOutletTemperatureActuator().handle());

  coil.renameEMSSubComponents();
  EXPECT_EQ("My_CoilUserDefined_overallModelSimulationProgramCallingManager", coil.overallModelSimulationProgramCallingManager().nameString());
  EXPECT_EQ("My_CoilUserDefined_modelSetupandSizingProgramCallingManager", coil.modelSetupandSizingProgramCallingManager().nameString());
  EXPECT_EQ("My_CoilUserDefined_overallSimulationProgram", coil.overallSimulationProgram().nameString());
  EXPECT_EQ("My_CoilUserDefined_initializationSimulationProgram", coil.initializationSimulationProgram().nameString());
  EXPECT_EQ("My_CoilUserDefined_airOutletTemperatureActuator", coil.airOutletTemperatureActuator().nameString());
}

TEST_F(EPModelFixture, CoilUserDefined_AddToNodeSupportsOutboardOANode) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACOutdoorAirSystem oaSystem(model);
  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(oaSystem.addToNode(supplyInletNode));

  auto outboardOANode = oaSystem.outboardOANode();
  ASSERT_TRUE(outboardOANode);

  CoilUserDefined coil(model);

  EXPECT_TRUE(coil.addToNode(*outboardOANode));
  EXPECT_EQ(1, coil.numberofAirConnections());

  const auto oaComponents = oaSystem.oaComponents();
  ASSERT_EQ(3u, oaComponents.size());
  EXPECT_EQ(coil.handle(), oaComponents[1].handle());
}

TEST_F(EPModelFixture, CoilUserDefined_AddToAndRemoveFromLoops_PreserveTopologyAndDerivedAirConnectionCount) {
  Model model;
  CoilUserDefined coil(model);

  AirLoopHVAC airLoop(model);

  auto supplyOutletNode = airLoop.supplyOutletNode();
  ASSERT_TRUE(coil.addToNode(supplyOutletNode));
  EXPECT_EQ(1, coil.numberofAirConnections());
  ASSERT_TRUE(coil.airLoopHVAC());
  EXPECT_EQ(airLoop.handle(), coil.airLoopHVAC()->handle());

  EXPECT_TRUE(coil.removeFromAirLoopHVAC());
  EXPECT_EQ(0, coil.numberofAirConnections());
  EXPECT_FALSE(coil.airLoopHVAC());
}
