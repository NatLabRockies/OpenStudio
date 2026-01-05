/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>
#include "ModelFixture.hpp"
#include "../PlantComponentUserDefined.hpp"
#include "../PlantComponentUserDefined_Impl.hpp"
#include "../AirLoopHVAC.hpp"
#include "../PlantLoop.hpp"
#include "../ThermalZone.hpp"
#include "../Node.hpp"
#include "../Node_Impl.hpp"
#include "../AirLoopHVACZoneSplitter.hpp"
#include "../EnergyManagementSystemProgramCallingManager.hpp"
#include "../EnergyManagementSystemProgram.hpp"
#include "../EnergyManagementSystemActuator.hpp"
#include "../EnergyManagementSystemMeteredOutputVariable.hpp"

//using namespace openstudio::model;
using namespace openstudio::energyplus;
using namespace openstudio::model;
using namespace openstudio;

TEST_F(ModelFixture, PlantComponentUserDefined_PlantComponentUserDefined) {
  ::testing::FLAGS_gtest_death_test_style = "threadsafe";

  ASSERT_EXIT(
    {
      Model m;
      PlantComponentUserDefined boiler(m);

      exit(0);
    },
    ::testing::ExitedWithCode(0), "");
}

TEST_F(ModelFixture, PlantComponentUserDefined_connections) {
  Model m;
  PlantComponentUserDefined boiler(m);

  Node inletNode(m);
  Node outletNode(m);

  m.connect(inletNode, inletNode.outletPort(), boiler, boiler.inletPort());
  m.connect(boiler, boiler.outletPort(), outletNode, outletNode.inletPort());

  ASSERT_TRUE(boiler.inletModelObject());
  ASSERT_TRUE(boiler.outletModelObject());

  EXPECT_EQ(inletNode.handle(), boiler.inletModelObject()->handle());
  EXPECT_EQ(outletNode.handle(), boiler.outletModelObject()->handle());
}

TEST_F(ModelFixture, PlantComponentUserDefined_addToNode) {
  Model m;
  PlantComponentUserDefined testObject(m);

  AirLoopHVAC airLoop(m);

  Node supplyOutletNode = airLoop.supplyOutletNode();

  EXPECT_FALSE(testObject.addToNode(supplyOutletNode));
  EXPECT_EQ((unsigned)2, airLoop.supplyComponents().size());

  Node inletNode = airLoop.zoneSplitter().lastOutletModelObject()->cast<Node>();

  EXPECT_FALSE(testObject.addToNode(inletNode));
  EXPECT_EQ((unsigned)5, airLoop.demandComponents().size());

  PlantLoop plantLoop(m);
  supplyOutletNode = plantLoop.supplyOutletNode();
  EXPECT_TRUE(testObject.addToNode(supplyOutletNode));
  EXPECT_EQ((unsigned)7, plantLoop.supplyComponents().size());
  EXPECT_EQ((unsigned)5, plantLoop.demandComponents().size());

  Node demandOutletNode = plantLoop.demandOutletNode();
  EXPECT_TRUE(testObject.addToNode(demandOutletNode));
  EXPECT_EQ((unsigned)5, plantLoop.supplyComponents().size());
  EXPECT_EQ((unsigned)7, plantLoop.demandComponents().size());

  // m.save(toPath("./PlantComponentUserDefinedTestBefore.osm"), true);
  EXPECT_EQ((unsigned)7, plantLoop.demandComponents().size());
  EnergyManagementSystemActuator actuator = testObject.designVolumeFlowRateActuator().get();

  auto testObjectClone = testObject.clone(m).cast<PlantComponentUserDefined>();
  EXPECT_TRUE(testObject.designVolumeFlowRateActuator());
  EXPECT_TRUE(testObjectClone.designVolumeFlowRateActuator());
  EXPECT_TRUE(testObjectClone.designVolumeFlowRateActuator().get().actuatedComponent());
  EXPECT_EQ(testObjectClone.designVolumeFlowRateActuator().get().actuatedComponent().get().handle(), testObjectClone.handle());
  // m.save(toPath("./PlantComponentUserDefinedTestClone.osm"), true);
}

TEST_F(ModelFixture, PlantComponentUserDefined_remove) {
  Model m;

  PlantLoop plant(m);
  PlantComponentUserDefined b1(m);
  EXPECT_EQ(8u, m.getObjectsByType(EnergyManagementSystemActuator::iddObjectType()).size());
  //EXPECT_EQ(3u, m.getObjectsByType(EnergyManagementSystemProgramCallingManager::iddObjectType()).size());
  PlantComponentUserDefined b2(m);
  EXPECT_EQ(16u, m.getObjectsByType(EnergyManagementSystemActuator::iddObjectType()).size());
  //EXPECT_EQ(6u, m.getObjectsByType(EnergyManagementSystemProgramCallingManager::iddObjectType()).size());

  EXPECT_FALSE(b1.loop());
  EXPECT_FALSE(b2.loop());

  EXPECT_EQ(plant.supplyComponents(Node::iddObjectType()).size(), 3u);

  EXPECT_TRUE(plant.addSupplyBranchForComponent(b1));
  EXPECT_GT(plant.supplyComponents(b1, plant.supplyOutletNode()).size(), 0u);
  EXPECT_TRUE(b1.loop());
  EXPECT_EQ(plant.supplyComponents(Node::iddObjectType()).size(), 4u);
  {
    auto node = b1.outletModelObject()->cast<Node>();
    EXPECT_TRUE(b2.addToNode(node));
    EXPECT_GT(plant.supplyComponents(b2, plant.supplyOutletNode()).size(), 0u);
    EXPECT_TRUE(b2.loop());
  }

  EXPECT_EQ(plant.supplyComponents(Node::iddObjectType()).size(), 5u);

  EXPECT_GT(plant.supplyComponents(b1, plant.supplyOutletNode()).size(), 0u);
  EXPECT_GT(plant.supplyComponents(b2, plant.supplyOutletNode()).size(), 0u);
  EXPECT_EQ(plant.demandComponents(b1, plant.demandOutletNode()).size(), 0u);
  EXPECT_EQ(plant.demandComponents(b2, plant.demandOutletNode()).size(), 0u);

  auto n1 = b1.outletModelObject().get();
  auto n2 = b2.outletModelObject().get();

  b1.remove();
  EXPECT_EQ(plant.supplyComponents(b1, plant.supplyOutletNode()).size(), 0u);
  EXPECT_GT(plant.supplyComponents(b2, plant.supplyOutletNode()).size(), 0u);
  EXPECT_EQ(plant.supplyComponents(Node::iddObjectType()).size(), 4u);
  EXPECT_EQ(8u, m.getObjectsByType(EnergyManagementSystemActuator::iddObjectType()).size());
  //EXPECT_EQ(3u, m.getObjectsByType(EnergyManagementSystemProgramCallingManager::iddObjectType()).size());
  b2.remove();
  EXPECT_EQ(plant.supplyComponents(b2, plant.supplyOutletNode()).size(), 0u);
  EXPECT_EQ(plant.supplyComponents(Node::iddObjectType()).size(), 3u);
  EXPECT_EQ(0u, m.getObjectsByType(EnergyManagementSystemActuator::iddObjectType()).size());
  //EXPECT_EQ(0u, m.getObjectsByType(EnergyManagementSystemProgramCallingManager::iddObjectType()).size());

  EXPECT_TRUE(n1.handle().isNull());
  EXPECT_TRUE(n2.handle().isNull());
}

TEST_F(ModelFixture, PlantComponentUserDefined_programs) {
  Model m;

  PlantLoop plant(m);
  PlantComponentUserDefined b1(m);
  EnergyManagementSystemProgramCallingManager mainPCM(m);
  EnergyManagementSystemProgramCallingManager initPCM(m);
  EnergyManagementSystemProgramCallingManager simPCM(m);
  EXPECT_TRUE(b1.setMainModelProgramCallingManager(mainPCM));
  EXPECT_EQ(mainPCM, b1.mainModelProgramCallingManager().get());
  EXPECT_TRUE(b1.setPlantInitializationProgramCallingManager(initPCM));
  EXPECT_EQ(initPCM, b1.plantInitializationProgramCallingManager().get());
  EXPECT_TRUE(b1.setPlantSimulationProgramCallingManager(simPCM));
  EXPECT_EQ(simPCM, b1.plantSimulationProgramCallingManager().get());
  b1.resetMainModelProgramCallingManager();
  b1.resetPlantInitializationProgramCallingManager();
  b1.resetPlantSimulationProgramCallingManager();
  EXPECT_FALSE(b1.mainModelProgramCallingManager());
  EXPECT_FALSE(b1.plantInitializationProgramCallingManager());
  EXPECT_FALSE(b1.plantSimulationProgramCallingManager());
}

TEST_F(ModelFixture, PlantComponentUserDefined_zone) {
  Model m;

  PlantLoop plant(m);
  ThermalZone tz(m);
  PlantComponentUserDefined b1(m);

  EXPECT_TRUE(b1.setAmbientZone(tz));
  EXPECT_EQ(tz, b1.ambientZone().get());
  b1.resetAmbientZone();
  EXPECT_FALSE(b1.ambientZone());
}

TEST_F(ModelFixture, PlantComponentUserDefined_constructor) {
  Model m;

  PlantLoop plant(m);
  PlantComponentUserDefined b1(m);

  EXPECT_EQ("MeetsLoadWithNominalCapacityHiOutLimit", b1.plantLoadingMode());
  EXPECT_EQ("NeedsFlowIfLoopOn", b1.plantLoopFlowRequestMode());
  EXPECT_FALSE(b1.setPlantLoopFlowRequestMode("bad value"));
  EXPECT_FALSE(b1.setPlantLoadingMode("bad value"));
  EXPECT_TRUE(b1.setPlantLoopFlowRequestMode("NeedsFlowAndTurnsLoopOn"));
  EXPECT_TRUE(b1.setPlantLoopFlowRequestMode("ReceivesWhateverFlowAvailable"));
  EXPECT_TRUE(b1.setPlantLoadingMode("MeetsLoadWithNominalCapacityLowOutLimit"));
  EXPECT_TRUE(b1.setPlantLoadingMode("MeetsLoadWithNominalCapacity"));
  EXPECT_TRUE(b1.setPlantLoadingMode("MeetsLoadWithPassiveCapacity"));
  EXPECT_TRUE(b1.setPlantLoadingMode("DemandsLoad"));

  EXPECT_TRUE(b1.designVolumeFlowRateActuator());
  EXPECT_TRUE(b1.minimumLoadingCapacityActuator());
  EXPECT_TRUE(b1.maximumLoadingCapacityActuator());
  EXPECT_TRUE(b1.minimumMassFlowRateActuator());
  EXPECT_TRUE(b1.maximumMassFlowRateActuator());
  EXPECT_TRUE(b1.optimalLoadingCapacityActuator());
  EXPECT_TRUE(b1.outletTemperatureActuator());
  EXPECT_TRUE(b1.massFlowRateActuator());

  EXPECT_TRUE(b1.designVolumeFlowRateActuator().get().actuatedComponent());
  EXPECT_EQ(b1.handle(), b1.designVolumeFlowRateActuator().get().actuatedComponent().get().handle());
}

TEST_F(ModelFixture, PlantComponentUserDefined_EMSProgram_emsMeteredOutputVariables) {

  Model m;
  PlantComponentUserDefined plant_comp(m);
  plant_comp.setPlantLoadingMode("MeetsLoadWithNominalCapacityHiOutLimit");
  plant_comp.setPlantLoopFlowRequestMode("NeedsFlowIfLoopIsOn");

  //PlantComponentUserDefined has CompType::None until it has EMS MeteredOutputVariables
  EXPECT_EQ(ComponentType(ComponentType::None), plant_comp.componentType());
  EXPECT_TRUE(testFuelTypeEquality({}, plant_comp.coolingFuelTypes()));
  EXPECT_TRUE(testFuelTypeEquality({}, plant_comp.heatingFuelTypes()));
  EXPECT_TRUE(testAppGFuelTypeEquality({}, plant_comp.appGHeatingFuelTypes()));

  EXPECT_EQ(0, plant_comp.energyManagementSystemMeteredOutputVariables().size());

  // I create an EMSMeteredOutputVar of type "Heating" and "Electricity" into the plantSimulationProgram,
  // and check that the PlantComponentUserDefined has the right fuel types
  auto sim_pgrm = plant_comp.plantSimulationProgram().get();
  sim_pgrm.setName("Sim_Pgrm");
  sim_pgrm.setBody("SET Elec_Htg_Cons = 0");
  {
    EnergyManagementSystemMeteredOutputVariable meteredoutvar(m, "Plant Heating Comp Electricity Consumption");
    EXPECT_TRUE(meteredoutvar.setEMSVariableName("Elec_Htg_Cons"));
    EXPECT_TRUE(meteredoutvar.setUpdateFrequency("SystemTimestep"));
    EXPECT_TRUE(meteredoutvar.setEMSProgramOrSubroutineName(sim_pgrm));
    EXPECT_TRUE(meteredoutvar.setResourceType("Electricity"));
    EXPECT_TRUE(meteredoutvar.setGroupType("HVAC"));
    EXPECT_TRUE(meteredoutvar.setEndUseCategory("Heating"));
    EXPECT_TRUE(meteredoutvar.setEndUseSubcategory(""));
    EXPECT_TRUE(meteredoutvar.setUnits("J"));
    EXPECT_EQ(ComponentType(ComponentType::Heating), meteredoutvar.componentType());
    EXPECT_TRUE(testFuelTypeEquality({}, meteredoutvar.coolingFuelTypes()));
    EXPECT_TRUE(testFuelTypeEquality({FuelType::Electricity}, meteredoutvar.heatingFuelTypes()));
    EXPECT_TRUE(testAppGFuelTypeEquality({AppGFuelType::Electric}, meteredoutvar.appGHeatingFuelTypes()));
  }

  EXPECT_EQ(1, plant_comp.energyManagementSystemMeteredOutputVariables().size());
  EXPECT_EQ(ComponentType(ComponentType::Heating), plant_comp.componentType());
  EXPECT_TRUE(testFuelTypeEquality({}, plant_comp.coolingFuelTypes()));
  EXPECT_TRUE(testFuelTypeEquality({FuelType::Electricity}, plant_comp.heatingFuelTypes()));
  EXPECT_TRUE(testAppGFuelTypeEquality({AppGFuelType::Electric}, plant_comp.appGHeatingFuelTypes()));

  // Plant inherits it correctly AFTER I assign the PlantComponentUserDefined on the supply side
  PlantLoop plant(m);
  EXPECT_EQ(ComponentType(ComponentType::None), plant.componentType());
  EXPECT_TRUE(testFuelTypeEquality({}, plant.coolingFuelTypes()));
  EXPECT_TRUE(testFuelTypeEquality({}, plant.heatingFuelTypes()));
  EXPECT_TRUE(testAppGFuelTypeEquality({}, plant.appGHeatingFuelTypes()));

  EXPECT_TRUE(plant.addSupplyBranchForComponent(plant_comp));
  EXPECT_EQ(ComponentType(ComponentType::Heating), plant.componentType());
  EXPECT_TRUE(testFuelTypeEquality({}, plant.coolingFuelTypes()));
  EXPECT_TRUE(testFuelTypeEquality({FuelType::Electricity}, plant.heatingFuelTypes()));
  EXPECT_TRUE(testAppGFuelTypeEquality({AppGFuelType::Electric}, plant.appGHeatingFuelTypes()));

  // Test with a second variable, this type "Chillers" with "Natural Gas"
  sim_pgrm.setBody("SET Elec_Htg_Cons = 0\nSET Elec_Clg_Cons = 0");
  {
    EnergyManagementSystemMeteredOutputVariable meteredoutvar2(m, "Plant Cooling Comp Electricity Consumption");
    EXPECT_TRUE(meteredoutvar2.setEMSVariableName("Elec_Htg_Cons"));
    EXPECT_TRUE(meteredoutvar2.setUpdateFrequency("SystemTimestep"));
    EXPECT_TRUE(meteredoutvar2.setEMSProgramOrSubroutineName(sim_pgrm));
    EXPECT_TRUE(meteredoutvar2.setResourceType("NaturalGas"));
    EXPECT_TRUE(meteredoutvar2.setGroupType("HVAC"));
    EXPECT_TRUE(meteredoutvar2.setEndUseCategory("Chillers"));
    EXPECT_TRUE(meteredoutvar2.setEndUseSubcategory(""));
    EXPECT_TRUE(meteredoutvar2.setUnits("J"));
    EXPECT_EQ(ComponentType(ComponentType::Cooling), meteredoutvar2.componentType());
    EXPECT_TRUE(testFuelTypeEquality({FuelType::Gas}, meteredoutvar2.coolingFuelTypes()));
    EXPECT_TRUE(testFuelTypeEquality({}, meteredoutvar2.heatingFuelTypes()));
    EXPECT_TRUE(testAppGFuelTypeEquality({}, meteredoutvar2.appGHeatingFuelTypes()));
  }

  EXPECT_EQ(2, plant_comp.energyManagementSystemMeteredOutputVariables().size());
  EXPECT_EQ(ComponentType(ComponentType::Both), plant_comp.componentType());
  EXPECT_TRUE(testFuelTypeEquality({FuelType::Gas}, plant_comp.coolingFuelTypes()));
  EXPECT_TRUE(testFuelTypeEquality({FuelType::Electricity}, plant_comp.heatingFuelTypes()));
  EXPECT_TRUE(testAppGFuelTypeEquality({AppGFuelType::Electric}, plant_comp.appGHeatingFuelTypes()));

  EXPECT_EQ(ComponentType(ComponentType::Both), plant.componentType());
  EXPECT_TRUE(testFuelTypeEquality({FuelType::Gas}, plant.coolingFuelTypes()));
  EXPECT_TRUE(testFuelTypeEquality({FuelType::Electricity}, plant.heatingFuelTypes()));
  EXPECT_TRUE(testAppGFuelTypeEquality({AppGFuelType::Electric}, plant.appGHeatingFuelTypes()));

  // Test with a third varaible, this time in the mainModelProgram, "OnSiteGeneration" (Cogeneration) with Diesel
  EnergyManagementSystemProgram main_pgrm(m);
  main_pgrm.setBody("SET Cogen_Cons = 0");
  EXPECT_TRUE(plant_comp.setMainModelProgram(main_pgrm));
  {
    EnergyManagementSystemMeteredOutputVariable meteredoutvar3(m, "Plant Cogen Comp Diesel Consumption");
    EXPECT_TRUE(meteredoutvar3.setEMSVariableName("Cogen_Cons"));
    EXPECT_TRUE(meteredoutvar3.setUpdateFrequency("SystemTimestep"));
    EXPECT_TRUE(meteredoutvar3.setEMSProgramOrSubroutineName(main_pgrm));
    EXPECT_TRUE(meteredoutvar3.setResourceType("Diesel"));
    EXPECT_TRUE(meteredoutvar3.setGroupType("HVAC"));
    EXPECT_TRUE(meteredoutvar3.setEndUseCategory("OnSiteGeneration"));
    EXPECT_TRUE(meteredoutvar3.setEndUseSubcategory(""));
    EXPECT_TRUE(meteredoutvar3.setUnits("J"));
    EXPECT_EQ(ComponentType(ComponentType::Heating), meteredoutvar3.componentType());
    EXPECT_TRUE(testFuelTypeEquality({}, meteredoutvar3.coolingFuelTypes()));
    EXPECT_TRUE(testFuelTypeEquality({FuelType::Diesel}, meteredoutvar3.heatingFuelTypes()));
    EXPECT_TRUE(testAppGFuelTypeEquality({AppGFuelType::Fuel}, meteredoutvar3.appGHeatingFuelTypes()));
  }

  EXPECT_EQ(3, plant_comp.energyManagementSystemMeteredOutputVariables().size());
  EXPECT_EQ(ComponentType(ComponentType::Both), plant_comp.componentType());
  EXPECT_TRUE(testFuelTypeEquality({FuelType::Gas}, plant_comp.coolingFuelTypes()));
  EXPECT_TRUE(testFuelTypeEquality({FuelType::Electricity, FuelType::Diesel}, plant_comp.heatingFuelTypes()));
  EXPECT_TRUE(testAppGFuelTypeEquality({AppGFuelType::Electric, AppGFuelType::Fuel}, plant_comp.appGHeatingFuelTypes()));

  EXPECT_EQ(ComponentType(ComponentType::Both), plant.componentType());
  EXPECT_TRUE(testFuelTypeEquality({FuelType::Gas}, plant.coolingFuelTypes()));
  EXPECT_TRUE(testFuelTypeEquality({FuelType::Electricity, FuelType::Diesel}, plant.heatingFuelTypes()));
  EXPECT_TRUE(testAppGFuelTypeEquality({AppGFuelType::Electric, AppGFuelType::Fuel}, plant.appGHeatingFuelTypes()));
}
