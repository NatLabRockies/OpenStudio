/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>
#include "EnergyPlusFixture.hpp"

#include "../ForwardTranslator.hpp"

#include "../../model/Model.hpp"
#include "../../model/AirLoopHVAC.hpp"
#include "../../model/AirLoopHVACOutdoorAirSystem.hpp"
#include "../../model/AirTerminalSingleDuctConstantVolumeNoReheat.hpp"
#include "../../model/ControllerOutdoorAir.hpp"
#include "../../model/EvaporativeCoolerDirectResearchSpecial.hpp"
#include "../../model/HeatExchangerAirToAirSensibleAndLatent.hpp"
#include "../../model/Node.hpp"
#include "../../model/Node_Impl.hpp"
#include "../../model/Schedule.hpp"
#include "../../model/Space.hpp"
#include "../../model/ThermalZone.hpp"

#include "../../utilities/idf/IdfObject_Impl.hpp"
#include "../../utilities/idf/WorkspaceExtensibleGroup.hpp"
#include "../../utilities/idf/WorkspaceObject.hpp"
#include "../../utilities/idf/WorkspaceObject_Impl.hpp"

#include <utilities/idd/AirLoopHVAC_OutdoorAirSystem_FieldEnums.hxx>
#include <utilities/idd/AirLoopHVAC_OutdoorAirSystem_EquipmentList_FieldEnums.hxx>
#include <utilities/idd/EvaporativeCooler_Direct_ResearchSpecial_FieldEnums.hxx>
#include <utilities/idd/HeatExchanger_AirToAir_SensibleAndLatent_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/OutdoorAir_Mixer_FieldEnums.hxx>

using namespace openstudio::energyplus;
using namespace openstudio::model;
using namespace openstudio;

TEST_F(EnergyPlusFixture, ForwardTranslator_AirLoopHVACOutdoorAirSystem_EquipmentListOrder) {
  // Test for #5696: the AirLoopHVAC:OutdoorAirSystem:EquipmentList components must be listed in actual air flow order:
  // outside air to OutdoorAir:Mixer, mixer last).
  // E+ 26.2's new node-connection verification (added in E+ PR #11659) rejects the model and it fails to run.
  // Previously the ForwardTranslator hardcoded the OutdoorAir:Mixer as the first component, ahead of any OA-branch equipment
  Model m;

  AirLoopHVAC a(m);
  ControllerOutdoorAir controllerOutdoorAir(m);
  AirLoopHVACOutdoorAirSystem outdoorAirSystem(m, controllerOutdoorAir);

  Node supplyInletNode = a.supplyInletNode();
  EXPECT_TRUE(outdoorAirSystem.addToNode(supplyInletNode));

  ThermalZone z(m);
  Space s(m);
  s.setThermalZone(z);
  auto alwaysOn = m.alwaysOnDiscreteSchedule();
  AirTerminalSingleDuctConstantVolumeNoReheat atu(m, alwaysOn);
  EXPECT_TRUE(a.addBranchForZone(z, atu));

  // Add an EvaporativeCooler:Direct:ResearchSpecial on the outdoor air branch, upstream of the
  // OutdoorAir:Mixer (this mirrors what Model::addExampleModelObjects() does)
  EvaporativeCoolerDirectResearchSpecial evapCooler(m, alwaysOn);
  boost::optional<Node> oaNode = outdoorAirSystem.outdoorAirModelObject()->optionalCast<Node>();
  ASSERT_TRUE(oaNode);
  EXPECT_TRUE(evapCooler.addToNode(oaNode.get()));

  // Add a HeatExchanger:AirToAir:SensibleAndLatent in between the evap cooler and the mixer, to
  // make sure a second (and different HVACComponent type) OA-branch component in the chain still
  // gets ordered correctly, ahead of the mixer, and doesn't get duplicated on the relief side
  HeatExchangerAirToAirSensibleAndLatent heatExchanger(m);
  boost::optional<Node> evapOutletNode = evapCooler.outletModelObject()->optionalCast<Node>();
  ASSERT_TRUE(evapOutletNode);
  EXPECT_TRUE(heatExchanger.addToNode(evapOutletNode.get()));

  ForwardTranslator ft;
  Workspace w = ft.translateModel(m);

  WorkspaceObjectVector idf_oa_systems(w.getObjectsByType(IddObjectType::AirLoopHVAC_OutdoorAirSystem));
  ASSERT_EQ(1u, idf_oa_systems.size());
  const WorkspaceObject& idf_oa_system = idf_oa_systems[0];

  boost::optional<WorkspaceObject> idf_eq_list_ = idf_oa_system.getTarget(AirLoopHVAC_OutdoorAirSystemFields::OutdoorAirEquipmentListName);
  ASSERT_TRUE(idf_eq_list_);

  ASSERT_EQ(3u, idf_eq_list_->extensibleGroups().size());

  // Verify the equipment list is not just in the right order, but that it actually matches the
  // real node wiring: each component's inlet node must be the previous component's outlet node,
  // starting from the true outdoor air node.
  ASSERT_TRUE(outdoorAirSystem.outboardOANode());
  std::string prevOutletNodeName = outdoorAirSystem.outboardOANode()->nameString();

  // Component 1: the evaporative cooler, since it is upstream of everything else (closest to outside air)
  {
    auto w_eg = idf_eq_list_->extensibleGroups()[0].cast<WorkspaceExtensibleGroup>();
    EXPECT_EQ("EvaporativeCooler:Direct:ResearchSpecial",
              w_eg.getString(AirLoopHVAC_OutdoorAirSystem_EquipmentListExtensibleFields::ComponentObjectType).get());
    auto idf_evapCooler_ = w_eg.getTarget(AirLoopHVAC_OutdoorAirSystem_EquipmentListExtensibleFields::ComponentName);
    ASSERT_TRUE(idf_evapCooler_);
    EXPECT_EQ(evapCooler.nameString(), idf_evapCooler_->nameString());

    EXPECT_EQ(prevOutletNodeName, idf_evapCooler_->getString(EvaporativeCooler_Direct_ResearchSpecialFields::AirInletNodeName).get());
    prevOutletNodeName = idf_evapCooler_->getString(EvaporativeCooler_Direct_ResearchSpecialFields::AirOutletNodeName).get();
  }

  // Component 2: the heat exchanger, in between the evap cooler and the mixer
  {
    auto w_eg = idf_eq_list_->extensibleGroups()[1].cast<WorkspaceExtensibleGroup>();
    EXPECT_EQ("HeatExchanger:AirToAir:SensibleAndLatent",
              w_eg.getString(AirLoopHVAC_OutdoorAirSystem_EquipmentListExtensibleFields::ComponentObjectType).get());
    auto idf_heatExchanger_ = w_eg.getTarget(AirLoopHVAC_OutdoorAirSystem_EquipmentListExtensibleFields::ComponentName);
    ASSERT_TRUE(idf_heatExchanger_);
    EXPECT_EQ(heatExchanger.nameString(), idf_heatExchanger_->nameString());

    EXPECT_EQ(prevOutletNodeName, idf_heatExchanger_->getString(HeatExchanger_AirToAir_SensibleAndLatentFields::SupplyAirInletNodeName).get());
    prevOutletNodeName = idf_heatExchanger_->getString(HeatExchanger_AirToAir_SensibleAndLatentFields::SupplyAirOutletNodeName).get();
  }

  // Component 3: the OutdoorAir:Mixer, listed last since it is the furthest downstream on the OA branch
  {
    auto w_eg = idf_eq_list_->extensibleGroups()[2].cast<WorkspaceExtensibleGroup>();
    EXPECT_EQ("OutdoorAir:Mixer", w_eg.getString(AirLoopHVAC_OutdoorAirSystem_EquipmentListExtensibleFields::ComponentObjectType).get());
    auto idf_mixer_ = w_eg.getTarget(AirLoopHVAC_OutdoorAirSystem_EquipmentListExtensibleFields::ComponentName);
    ASSERT_TRUE(idf_mixer_);

    EXPECT_EQ(prevOutletNodeName, idf_mixer_->getString(OutdoorAir_MixerFields::OutdoorAirStreamNodeName).get());
  }
}
