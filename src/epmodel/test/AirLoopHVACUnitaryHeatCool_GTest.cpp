/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/AirLoopHVAC_Impl.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../Loop/PlantLoop_Impl.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../StraightComponent/AirLoopHVACUnitaryHeatCool.hpp"
#include "../StraightComponent/AirLoopHVACUnitaryHeatCool_Impl.hpp"
#include "../StraightComponent/AirLoopHVACUnitaryHeatPumpAirToAir.hpp"
#include "../StraightComponent/AirLoopHVACUnitaryHeatPumpAirToAir_Impl.hpp"
#include "../StraightComponent/CoilCoolingDXSingleSpeed.hpp"
#include "../StraightComponent/CoilCoolingDXSingleSpeed_Impl.hpp"
#include "../StraightComponent/CoilHeatingElectric.hpp"
#include "../StraightComponent/CoilHeatingElectric_Impl.hpp"
#include "../StraightComponent/CoilHeatingGas.hpp"
#include "../StraightComponent/CoilHeatingGas_Impl.hpp"
#include "../StraightComponent/FanOnOff.hpp"
#include "../StraightComponent/FanOnOff_Impl.hpp"
#include "../StraightComponent/FanConstantVolume.hpp"
#include "../StraightComponent/Node.hpp"
#include "../WaterToAirComponent/CoilHeatingWater.hpp"
#include "../WaterToAirComponent/CoilHeatingWater_Impl.hpp"

#include <utilities/idd/AirLoopHVAC_UnitaryHeatCool_FieldEnums.hxx>
#include <utilities/core/Filesystem.hpp>
#include <utilities/core/PathHelpers.hpp>

#include <algorithm>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AirLoopHVACUnitaryHeatCool_DefaultConstructor) {
  Model model;
  AirLoopHVACUnitaryHeatCool unitary(model);
  EXPECT_EQ(AirLoopHVACUnitaryHeatCool::iddObjectType(), unitary.iddObject().type());
}

TEST_F(EPModelFixture, AirLoopHVACUnitaryHeatCool_RelationshipConstructorAndChildren) {
  Model model;
  ScheduleConstant availability(model);
  FanOnOff fan(model);
  CoilHeatingGas heating(model);
  CoilCoolingDXSingleSpeed cooling(model);
  CoilHeatingElectric reheat(model);

  AirLoopHVACUnitaryHeatCool unitary(model, availability, fan, heating, cooling);
  ASSERT_TRUE(unitary.setReheatCoil(reheat));

  EXPECT_EQ(availability.handle(), unitary.availabilitySchedule().handle());
  EXPECT_EQ(fan.handle(), unitary.supplyFan().handle());
  EXPECT_EQ(heating.handle(), unitary.heatingCoil().handle());
  EXPECT_EQ(cooling.handle(), unitary.coolingCoil().handle());
  ASSERT_TRUE(unitary.reheatCoil());
  EXPECT_EQ(reheat.handle(), unitary.reheatCoil()->handle());
  EXPECT_EQ(fan.iddObject().name(), unitary.supplyFanObjectType());
  EXPECT_EQ(heating.iddObject().name(), unitary.heatingCoilObjectType());
  EXPECT_EQ(cooling.iddObject().name(), unitary.coolingCoilObjectType());
  EXPECT_EQ(reheat.iddObject().name(), unitary.reheatCoilObjectType().get());

  const auto children = unitary.children();
  ASSERT_EQ(4u, children.size());
  EXPECT_EQ(fan.handle(), children[0].handle());
  EXPECT_EQ(heating.handle(), children[1].handle());
  EXPECT_EQ(cooling.handle(), children[2].handle());
  EXPECT_EQ(reheat.handle(), children[3].handle());
}

TEST_F(EPModelFixture, AirLoopHVACUnitaryHeatCool_DrawThroughContainedAirPath) {
  Model model;
  AirLoopHVAC airLoop(model);
  FanOnOff fan(model);
  CoilHeatingGas heating(model);
  CoilCoolingDXSingleSpeed cooling(model);
  CoilHeatingElectric reheat(model);
  AirLoopHVACUnitaryHeatCool unitary(model);

  ASSERT_TRUE(unitary.setFanPlacement("DrawThrough"));
  ASSERT_TRUE(unitary.setSupplyFan(fan));
  ASSERT_TRUE(unitary.setHeatingCoil(heating));
  ASSERT_TRUE(unitary.setCoolingCoil(cooling));
  ASSERT_TRUE(unitary.setReheatCoil(reheat));
  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(unitary.addToNode(supplyInletNode));

  ASSERT_TRUE(unitary.inletModelObject());
  ASSERT_TRUE(unitary.outletModelObject());
  ASSERT_TRUE(unitary.coolingCoilOutletNode());
  ASSERT_TRUE(unitary.heatingCoilOutletNode());
  ASSERT_TRUE(unitary.fanOutletNode());
  EXPECT_EQ(*unitary.inletModelObject(), *cooling.inletModelObject());
  EXPECT_EQ(*unitary.coolingCoilOutletNode(), *heating.inletModelObject());
  EXPECT_EQ(*unitary.heatingCoilOutletNode(), *fan.inletModelObject());
  EXPECT_EQ(*unitary.fanOutletNode(), *reheat.inletModelObject());
  EXPECT_EQ(*unitary.outletModelObject(), *reheat.outletModelObject());
}

TEST_F(EPModelFixture, AirLoopHVACUnitaryHeatCool_AirLoopRemovalOwnsChildren) {
  Model model;
  AirLoopHVAC airLoop(model);
  FanOnOff fan(model);
  CoilHeatingGas heating(model);
  CoilCoolingDXSingleSpeed cooling(model);
  AirLoopHVACUnitaryHeatCool unitary(model);
  ASSERT_TRUE(unitary.setSupplyFan(fan));
  ASSERT_TRUE(unitary.setHeatingCoil(heating));
  ASSERT_TRUE(unitary.setCoolingCoil(cooling));
  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(unitary.addToNode(supplyInletNode));

  const auto airLoopHandle = airLoop.handle();
  const auto unitaryHandle = unitary.handle();
  const auto fanHandle = fan.handle();
  const auto heatingHandle = heating.handle();
  const auto coolingHandle = cooling.handle();
  EXPECT_FALSE(airLoop.remove().empty());
  EXPECT_FALSE(model.getObject(airLoopHandle));
  EXPECT_FALSE(model.getObject(unitaryHandle));
  EXPECT_FALSE(model.getObject(fanHandle));
  EXPECT_FALSE(model.getObject(heatingHandle));
  EXPECT_FALSE(model.getObject(coolingHandle));
}

TEST_F(EPModelFixture, AirLoopHVACUnitaryHeatCool_LoadedOwnershipLifecycle) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-unitary-heat-cool-ownership.idf");
  Model model;
  AirLoopHVAC airLoop(model);
  FanOnOff fan(model);
  CoilHeatingGas heating(model);
  CoilCoolingDXSingleSpeed cooling(model);
  AirLoopHVACUnitaryHeatCool unitary(model);
  ASSERT_TRUE(airLoop.setName("Loaded Unitary Air Loop"));
  ASSERT_TRUE(unitary.setName("Loaded Unitary Heat Cool"));
  ASSERT_TRUE(fan.setName("Loaded Unitary Fan"));
  ASSERT_TRUE(heating.setName("Loaded Unitary Heating Coil"));
  ASSERT_TRUE(cooling.setName("Loaded Unitary Cooling Coil"));
  ASSERT_TRUE(unitary.setSupplyFan(fan));
  ASSERT_TRUE(unitary.setHeatingCoil(heating));
  ASSERT_TRUE(unitary.setCoolingCoil(cooling));
  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(unitary.addToNode(supplyInletNode));
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedLoop = loadedModel->getConcreteModelObjectByName<AirLoopHVAC>("Loaded Unitary Air Loop");
  auto loadedUnitary = loadedModel->getConcreteModelObjectByName<AirLoopHVACUnitaryHeatCool>("Loaded Unitary Heat Cool");
  ASSERT_TRUE(loadedLoop);
  ASSERT_TRUE(loadedUnitary);
  EXPECT_EQ("Loaded Unitary Fan", loadedUnitary->supplyFan().nameString());
  EXPECT_EQ("Loaded Unitary Heating Coil", loadedUnitary->heatingCoil().nameString());
  EXPECT_EQ("Loaded Unitary Cooling Coil", loadedUnitary->coolingCoil().nameString());
  EXPECT_EQ(3u, loadedUnitary->children().size());

  EXPECT_FALSE(loadedLoop->remove().empty());
  EXPECT_FALSE(loadedModel->getConcreteModelObjectByName<AirLoopHVACUnitaryHeatCool>("Loaded Unitary Heat Cool"));
  EXPECT_FALSE(loadedModel->getConcreteModelObjectByName<FanOnOff>("Loaded Unitary Fan"));
  EXPECT_FALSE(loadedModel->getConcreteModelObjectByName<CoilHeatingGas>("Loaded Unitary Heating Coil"));
  EXPECT_FALSE(loadedModel->getConcreteModelObjectByName<CoilCoolingDXSingleSpeed>("Loaded Unitary Cooling Coil"));

  openstudio::filesystem::remove(idfPath);
}

TEST_F(EPModelFixture, AirLoopHVACUnitaryHeatCool_DirectRemovalOwnsPlantConnectedChild) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-unitary-heat-cool-plant-child-removal.idf");
  Model model;
  PlantLoop plantLoop(model);
  CoilHeatingWater heating(model);
  AirLoopHVACUnitaryHeatCool unitary(model);
  ASSERT_TRUE(plantLoop.setName("Surviving Plant Loop"));
  ASSERT_TRUE(heating.setName("Removed Unitary Water Coil"));
  ASSERT_TRUE(plantLoop.addDemandBranchForComponent(heating));
  ASSERT_TRUE(unitary.setHeatingCoil(heating));
  const auto unitaryHandle = unitary.handle();
  const auto heatingHandle = heating.handle();
  const auto plantHandle = plantLoop.handle();

  EXPECT_FALSE(unitary.remove().empty());
  EXPECT_FALSE(model.getObject(unitaryHandle));
  EXPECT_FALSE(model.getObject(heatingHandle));
  EXPECT_TRUE(model.getObject(plantHandle));
  const auto remainingDemandComponents = plantLoop.demandComponents(openstudio::IddObjectType::Catchall);
  EXPECT_TRUE(
    std::ranges::none_of(remainingDemandComponents, [&heatingHandle](const auto& component) { return component.handle() == heatingHandle; }));
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  EXPECT_TRUE(loadedModel->getConcreteModelObjectByName<PlantLoop>("Surviving Plant Loop"));
  EXPECT_FALSE(loadedModel->getConcreteModelObjectByName<CoilHeatingWater>("Removed Unitary Water Coil"));

  openstudio::filesystem::remove(idfPath);
}

TEST_F(EPModelFixture, AirLoopHVACUnitaryHeatCool_RejectsConflictingChildOwnershipWithoutMutation) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACUnitaryHeatCool firstUnitary(model);
  AirLoopHVACUnitaryHeatCool secondUnitary(model);
  FanOnOff ownedFan(model);
  FanConstantVolume loopFan(model);
  CoilHeatingElectric heating(model);

  ASSERT_TRUE(firstUnitary.setSupplyFan(ownedFan));
  EXPECT_FALSE(secondUnitary.setSupplyFan(ownedFan));
  EXPECT_EQ(ownedFan.handle(), firstUnitary.supplyFan().handle());
  EXPECT_TRUE(secondUnitary.children().empty());

  auto supplyInlet = airLoop.supplyInletNode();
  ASSERT_TRUE(loopFan.addToNode(supplyInlet));
  EXPECT_FALSE(secondUnitary.setSupplyFan(loopFan));
  EXPECT_TRUE(secondUnitary.children().empty());

  ASSERT_TRUE(secondUnitary.setHeatingCoil(heating));
  EXPECT_FALSE(secondUnitary.setReheatCoil(heating));
  EXPECT_EQ(heating.handle(), secondUnitary.heatingCoil().handle());
  EXPECT_FALSE(secondUnitary.reheatCoil());
}

TEST_F(EPModelFixture, AirLoopHVACUnitaryHeatCool_ReplacementAndResetDisconnectFormerAirPath) {
  Model model;
  AirLoopHVACUnitaryHeatCool unitary(model);
  FanOnOff firstFan(model);
  FanOnOff secondFan(model);
  CoilHeatingElectric reheat(model);

  ASSERT_TRUE(unitary.setSupplyFan(firstFan));
  ASSERT_TRUE(firstFan.inletModelObject());
  ASSERT_TRUE(firstFan.outletModelObject());
  ASSERT_TRUE(unitary.setSupplyFan(secondFan));
  EXPECT_FALSE(firstFan.inletModelObject());
  EXPECT_FALSE(firstFan.outletModelObject());

  ASSERT_TRUE(unitary.setReheatCoil(reheat));
  ASSERT_TRUE(reheat.inletModelObject());
  ASSERT_TRUE(reheat.outletModelObject());
  unitary.resetReheatCoil();
  EXPECT_FALSE(reheat.inletModelObject());
  EXPECT_FALSE(reheat.outletModelObject());
}

TEST_F(EPModelFixture, AirLoopHVACUnitaryHeatCool_LoadRepairsBlankAvailability) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-unitary-heat-cool-blank-availability.idf");
  Model model;
  AirLoopHVACUnitaryHeatCool unitary(model);
  ASSERT_TRUE(unitary.setName("Blank Availability Unitary"));
  ASSERT_TRUE(unitary.setString(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::AvailabilityScheduleName, ""));
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedUnitary = loadedModel->getConcreteModelObjectByName<AirLoopHVACUnitaryHeatCool>("Blank Availability Unitary");
  ASSERT_TRUE(loadedUnitary);
  EXPECT_EQ(loadedModel->alwaysOnDiscreteSchedule().handle(), loadedUnitary->availabilitySchedule().handle());

  openstudio::filesystem::remove(idfPath);
}

TEST_F(EPModelFixture, AirLoopHVACUnitaryHeatCool_RawObjectTypeCannotDesynchronizeTypedChild) {
  Model model;
  AirLoopHVACUnitaryHeatCool unitary(model);
  FanOnOff fan(model);
  CoilHeatingElectric reheat(model);
  ASSERT_TRUE(unitary.setSupplyFan(fan));
  ASSERT_TRUE(unitary.setReheatCoil(reheat));

  EXPECT_FALSE(unitary.setSupplyFanObjectType("Fan:ConstantVolume"));
  EXPECT_EQ(fan.iddObject().name(), unitary.supplyFanObjectType());
  EXPECT_FALSE(unitary.setReheatCoilObjectType("Coil:Heating:Fuel"));
  unitary.resetReheatCoilObjectType();
  EXPECT_EQ(reheat.iddObject().name(), unitary.reheatCoilObjectType().get());
}

TEST_F(EPModelFixture, AirLoopHVAC_SharedUnitaryChildRemovalRetriesAfterBothParents) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-shared-unitary-child-removal.idf");
  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACUnitaryHeatCool firstUnitary(model);
  AirLoopHVACUnitaryHeatCool secondUnitary(model);
  FanOnOff sharedFan(model);
  ASSERT_TRUE(airLoop.setName("Shared Child Air Loop"));
  ASSERT_TRUE(firstUnitary.setName("First Shared Child Unitary"));
  ASSERT_TRUE(secondUnitary.setName("Second Shared Child Unitary"));
  ASSERT_TRUE(sharedFan.setName("Shared Unitary Fan"));
  ASSERT_TRUE(firstUnitary.setSupplyFan(sharedFan));
  ASSERT_TRUE(secondUnitary.setString(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::SupplyFanObjectType, sharedFan.iddObject().name()));
  ASSERT_TRUE(secondUnitary.setPointer(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::SupplyFanName, sharedFan.handle()));
  auto supplyInlet = airLoop.supplyInletNode();
  ASSERT_TRUE(firstUnitary.addToNode(supplyInlet));
  ASSERT_TRUE(secondUnitary.addToNode(supplyInlet));
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedLoop = loadedModel->getConcreteModelObjectByName<AirLoopHVAC>("Shared Child Air Loop");
  auto loadedFan = loadedModel->getConcreteModelObjectByName<FanOnOff>("Shared Unitary Fan");
  ASSERT_TRUE(loadedLoop);
  ASSERT_TRUE(loadedFan);
  const auto claimingUnitariesFor = [](Model& candidateModel, const FanOnOff& candidateFan) {
    std::vector<AirLoopHVACUnitaryHeatCool> result;
    for (const auto& candidateUnitary : candidateModel.getConcreteModelObjects<AirLoopHVACUnitaryHeatCool>()) {
      const auto children = candidateUnitary.children();
      if (std::ranges::any_of(children, [&candidateFan](const auto& child) { return child.handle() == candidateFan.handle(); })) {
        result.push_back(candidateUnitary);
      }
    }
    return result;
  };
  auto claimingUnitaries = claimingUnitariesFor(*loadedModel, *loadedFan);
  ASSERT_EQ(1u, claimingUnitaries.size());
  EXPECT_EQ("First Shared Child Unitary", claimingUnitaries.front().nameString());
  ASSERT_TRUE(claimingUnitaries.front().inletModelObject());
  ASSERT_TRUE(claimingUnitaries.front().outletModelObject());
  ASSERT_TRUE(loadedFan->inletModelObject());
  ASSERT_TRUE(loadedFan->outletModelObject());
  EXPECT_EQ(*claimingUnitaries.front().inletModelObject(), *loadedFan->inletModelObject());
  EXPECT_EQ(*claimingUnitaries.front().outletModelObject(), *loadedFan->outletModelObject());

  auto independentlyLoadedModel = Model::load(idfPath);
  ASSERT_TRUE(independentlyLoadedModel);
  auto independentlyLoadedFan = independentlyLoadedModel->getConcreteModelObjectByName<FanOnOff>("Shared Unitary Fan");
  ASSERT_TRUE(independentlyLoadedFan);
  const auto independentlyClaimingUnitaries = claimingUnitariesFor(*independentlyLoadedModel, *independentlyLoadedFan);
  ASSERT_EQ(1u, independentlyClaimingUnitaries.size());
  EXPECT_EQ("First Shared Child Unitary", independentlyClaimingUnitaries.front().nameString());

  const auto sharedFanHandle = loadedFan->handle();
  EXPECT_FALSE(loadedLoop->remove().empty());
  EXPECT_FALSE(loadedModel->getObject(sharedFanHandle));

  openstudio::filesystem::remove(idfPath);
}

TEST_F(EPModelFixture, AirLoopHVACUnitaryHeatCool_LoadYieldsSharedChildToOtherCompoundOwner) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-cross-compound-shared-unitary-child.idf");
  Model model;
  AirLoopHVACUnitaryHeatPumpAirToAir heatPump(model);
  AirLoopHVACUnitaryHeatCool heatCool(model);
  FanOnOff sharedFan(model);
  ASSERT_TRUE(heatPump.setName("Established Heat Pump"));
  ASSERT_TRUE(heatCool.setName("Conflicting Heat Cool"));
  ASSERT_TRUE(sharedFan.setName("Cross Compound Shared Fan"));
  ASSERT_TRUE(heatPump.setSupplyAirFan(sharedFan));
  ASSERT_TRUE(heatCool.setString(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::SupplyFanObjectType, sharedFan.iddObject().name()));
  ASSERT_TRUE(heatCool.setPointer(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::SupplyFanName, sharedFan.handle()));
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedHeatPump = loadedModel->getConcreteModelObjectByName<AirLoopHVACUnitaryHeatPumpAirToAir>("Established Heat Pump");
  auto loadedHeatCool = loadedModel->getConcreteModelObjectByName<AirLoopHVACUnitaryHeatCool>("Conflicting Heat Cool");
  auto loadedFan = loadedModel->getConcreteModelObjectByName<FanOnOff>("Cross Compound Shared Fan");
  ASSERT_TRUE(loadedHeatPump);
  ASSERT_TRUE(loadedHeatCool);
  ASSERT_TRUE(loadedFan);
  EXPECT_EQ(loadedFan->handle(), loadedHeatPump->supplyAirFan().handle());
  EXPECT_TRUE(loadedHeatCool->children().empty());
  const auto owner = loadedFan->containingHVACComponent();
  ASSERT_TRUE(owner);
  EXPECT_EQ(loadedHeatPump->handle(), owner->handle());
  ASSERT_TRUE(loadedFan->inletModelObject());
  ASSERT_TRUE(loadedFan->outletModelObject());

  const auto reloadedPath = openstudio::tempDir() / openstudio::toPath("epmodel-cross-compound-shared-unitary-child-reloaded.idf");
  ASSERT_TRUE(loadedModel->save(reloadedPath, true));
  auto reloadedModel = Model::load(reloadedPath);
  ASSERT_TRUE(reloadedModel);
  auto reloadedHeatPump = reloadedModel->getConcreteModelObjectByName<AirLoopHVACUnitaryHeatPumpAirToAir>("Established Heat Pump");
  auto reloadedHeatCool = reloadedModel->getConcreteModelObjectByName<AirLoopHVACUnitaryHeatCool>("Conflicting Heat Cool");
  ASSERT_TRUE(reloadedHeatPump);
  ASSERT_TRUE(reloadedHeatCool);
  EXPECT_EQ("Cross Compound Shared Fan", reloadedHeatPump->supplyAirFan().nameString());
  EXPECT_TRUE(reloadedHeatCool->children().empty());

  openstudio::filesystem::remove(idfPath);
  openstudio::filesystem::remove(reloadedPath);
}

TEST_F(EPModelFixture, AirLoopHVACUnitaryHeatCool_LoadKeepsFirstRoleForDuplicatedChild) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-unitary-heat-cool-duplicate-role.idf");
  Model model;
  AirLoopHVACUnitaryHeatCool heatCool(model);
  CoilHeatingElectric sharedCoil(model);
  ASSERT_TRUE(heatCool.setName("Duplicate Role Heat Cool"));
  ASSERT_TRUE(sharedCoil.setName("Duplicate Role Heating Coil"));
  ASSERT_TRUE(heatCool.setHeatingCoil(sharedCoil));
  ASSERT_TRUE(heatCool.setString(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::ReheatCoilObjectType, sharedCoil.iddObject().name()));
  ASSERT_TRUE(heatCool.setPointer(openstudio::AirLoopHVAC_UnitaryHeatCoolFields::ReheatCoilName, sharedCoil.handle()));
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedHeatCool = loadedModel->getConcreteModelObjectByName<AirLoopHVACUnitaryHeatCool>("Duplicate Role Heat Cool");
  auto loadedCoil = loadedModel->getConcreteModelObjectByName<CoilHeatingElectric>("Duplicate Role Heating Coil");
  ASSERT_TRUE(loadedHeatCool);
  ASSERT_TRUE(loadedCoil);
  EXPECT_EQ(loadedCoil->handle(), loadedHeatCool->heatingCoil().handle());
  EXPECT_FALSE(loadedHeatCool->reheatCoil());
  const auto children = loadedHeatCool->children();
  ASSERT_EQ(1u, children.size());
  EXPECT_EQ(loadedCoil->handle(), children.front().handle());

  openstudio::filesystem::remove(idfPath);
}

TEST_F(EPModelFixture, AirLoopHVACUnitaryHeatCool_ScalarAccessors_RoundTrip) {
  Model model;
  AirLoopHVACUnitaryHeatCool unitary(model);

  EXPECT_TRUE(unitary.setMaximumSupplyAirTemperature(48.0));
  ASSERT_TRUE(unitary.maximumSupplyAirTemperature());
  EXPECT_DOUBLE_EQ(48.0, unitary.maximumSupplyAirTemperature().get());
  EXPECT_FALSE(unitary.isMaximumSupplyAirTemperatureAutosized());
  EXPECT_FALSE(unitary.isMaximumSupplyAirTemperatureDefaulted());
  unitary.resetMaximumSupplyAirTemperature();
  EXPECT_TRUE(unitary.isMaximumSupplyAirTemperatureDefaulted());
  unitary.autosizeMaximumSupplyAirTemperature();
  EXPECT_TRUE(unitary.isMaximumSupplyAirTemperatureAutosized());

  EXPECT_TRUE(unitary.setCoolingSupplyAirFlowRate(1.1));
  ASSERT_TRUE(unitary.coolingSupplyAirFlowRate());
  EXPECT_DOUBLE_EQ(1.1, unitary.coolingSupplyAirFlowRate().get());
  unitary.autosizeCoolingSupplyAirFlowRate();
  EXPECT_TRUE(unitary.isCoolingSupplyAirFlowRateAutosized());

  EXPECT_TRUE(unitary.setHeatingSupplyAirFlowRate(1.2));
  ASSERT_TRUE(unitary.heatingSupplyAirFlowRate());
  EXPECT_DOUBLE_EQ(1.2, unitary.heatingSupplyAirFlowRate().get());
  unitary.autosizeHeatingSupplyAirFlowRate();
  EXPECT_TRUE(unitary.isHeatingSupplyAirFlowRateAutosized());

  EXPECT_TRUE(unitary.setNoLoadSupplyAirFlowRate(0.5));
  ASSERT_TRUE(unitary.noLoadSupplyAirFlowRate());
  EXPECT_DOUBLE_EQ(0.5, unitary.noLoadSupplyAirFlowRate().get());
  unitary.resetNoLoadSupplyAirFlowRate();
  EXPECT_FALSE(unitary.noLoadSupplyAirFlowRate());

  EXPECT_FALSE(unitary.setSupplyFanObjectType("Fan:OnOff"));

  EXPECT_TRUE(unitary.setFanPlacement("DrawThrough"));
  EXPECT_EQ("DrawThrough", unitary.fanPlacement());
  EXPECT_FALSE(unitary.isFanPlacementDefaulted());
  unitary.resetFanPlacement();
  EXPECT_TRUE(unitary.isFanPlacementDefaulted());

  EXPECT_FALSE(unitary.setHeatingCoilObjectType("Coil:Heating:Fuel"));

  EXPECT_FALSE(unitary.setCoolingCoilObjectType("Coil:Cooling:DX:SingleSpeed"));

  EXPECT_TRUE(unitary.setDehumidificationControlType("CoolReheat"));
  EXPECT_EQ("CoolReheat", unitary.dehumidificationControlType());
  EXPECT_FALSE(unitary.isDehumidificationControlTypeDefaulted());
  unitary.resetDehumidificationControlType();
  EXPECT_TRUE(unitary.isDehumidificationControlTypeDefaulted());

  EXPECT_FALSE(unitary.setReheatCoilObjectType("Coil:Heating:Electric"));
  unitary.resetReheatCoilObjectType();
  ASSERT_TRUE(unitary.reheatCoilObjectType());
  EXPECT_TRUE(unitary.reheatCoilObjectType()->empty());
}
