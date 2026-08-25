/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../StraightComponent/Node.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../HVACComponent/ThermalZone_Impl.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../ModelObject/NodeList.hpp"
#include "../ModelObject/NodeList_Impl.hpp"
#include "../ModelObject/ZoneHVACEquipmentList.hpp"
#include "../ModelObject/ZoneHVACEquipmentConnections.hpp"
#include "../ModelObject/ZoneHVACEquipmentConnections_Impl.hpp"

#include <utilities/idd/ZoneHVAC_EquipmentConnections_FieldEnums.hxx>
#include <utilities/core/Filesystem.hpp>
#include <utilities/core/UUID.hpp>
#include <utilities/idf/WorkspaceObject_Impl.hpp>

#include <utility>

using namespace openstudio::epmodel;

namespace {

class ScopedFileRemoval
{
 public:
  explicit ScopedFileRemoval(openstudio::path path) : m_path(std::move(path)) {}

  ~ScopedFileRemoval() {
    boost::system::error_code error;
    boost::filesystem::remove(m_path, error);
  }

 private:
  openstudio::path m_path;
};

}  // namespace

TEST_F(EPModelFixture, API_ZoneHVACEquipmentConnections_ThermalZoneConstructor) {
  Model model;
  ThermalZone zone(model);
  ZoneHVACEquipmentConnections equipmentConnections(zone);
  EXPECT_EQ(ZoneHVACEquipmentConnections::iddObjectType(), equipmentConnections.iddObject().type());
  EXPECT_EQ(zone, equipmentConnections.thermalZone());
  EXPECT_EQ(zone.nameString() + " Zone Air Node", equipmentConnections.zoneAirNode().nameString());
}

TEST_F(EPModelFixture, API_ZoneHVACEquipmentConnections_SettersAndGetters) {
  Model model;
  ThermalZone zone(model);
  ZoneHVACEquipmentList equipmentList(model);
  ZoneHVACEquipmentConnections equipmentConnections(zone);
  auto zoneInletNode = model.getOrCreateTransientByName<Node>("Zone Inlet Node");
  auto zoneExhaustNode = model.getOrCreateTransientByName<Node>("Zone Exhaust Node");
  auto zoneReturnNode = model.getOrCreateTransientByName<Node>("Zone Return Node");

  auto equipmentConnectionsImpl = equipmentConnections.getImpl<detail::ZoneHVACEquipmentConnections_Impl>();
  ASSERT_TRUE(equipmentConnectionsImpl);

  ASSERT_TRUE(equipmentConnectionsImpl->setZoneHVACEquipmentList(equipmentList));
  ASSERT_TRUE(equipmentConnectionsImpl->addZoneAirInletNode(zoneInletNode));
  ASSERT_TRUE(equipmentConnectionsImpl->addZoneAirExhaustNode(zoneExhaustNode));
  ASSERT_TRUE(equipmentConnectionsImpl->addZoneReturnAirNode(zoneReturnNode));

  auto linkedZone = equipmentConnections.thermalZone();
  EXPECT_EQ(zone, linkedZone);

  auto linkedEquipmentList = equipmentConnections.zoneHVACEquipmentList();
  EXPECT_EQ(equipmentList, linkedEquipmentList);

  auto linkedZoneAirNode = equipmentConnections.zoneAirNode();
  EXPECT_EQ(zone.nameString() + " Zone Air Node", linkedZoneAirNode.nameString());

  const auto zoneAirInletNodes = equipmentConnections.zoneAirInletNodes();
  ASSERT_EQ(1u, zoneAirInletNodes.size());
  EXPECT_EQ(zoneInletNode, zoneAirInletNodes.front());
  EXPECT_NE(linkedZoneAirNode, zoneAirInletNodes.front());

  const auto inletTarget = equipmentConnections.getTarget(openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneAirInletNodeorNodeListName);
  ASSERT_TRUE(inletTarget);
  EXPECT_TRUE(inletTarget->optionalCast<NodeList>());

  const auto zoneAirExhaustNodes = equipmentConnections.zoneAirExhaustNodes();
  ASSERT_EQ(1u, zoneAirExhaustNodes.size());
  EXPECT_EQ(zoneExhaustNode, zoneAirExhaustNodes.front());

  const auto zoneReturnAirNodes = equipmentConnections.zoneReturnAirNodes();
  ASSERT_EQ(1u, zoneReturnAirNodes.size());
  EXPECT_EQ(zoneReturnNode, zoneReturnAirNodes.front());
}

TEST_F(EPModelFixture, API_ZoneHVACEquipmentConnections_MultipleAggregateNodesUseNodeList) {
  Model model;
  ThermalZone zone(model);
  ZoneHVACEquipmentConnections equipmentConnections(zone);
  auto inlet1 = model.getOrCreateTransientByName<Node>("Zone Inlet 1");
  auto inlet2 = model.getOrCreateTransientByName<Node>("Zone Inlet 2");

  auto equipmentConnectionsImpl = equipmentConnections.getImpl<detail::ZoneHVACEquipmentConnections_Impl>();
  ASSERT_TRUE(equipmentConnectionsImpl);
  ASSERT_TRUE(equipmentConnectionsImpl->addZoneAirInletNode(inlet1));
  ASSERT_TRUE(equipmentConnectionsImpl->addZoneAirInletNode(inlet2));

  const auto inletNodes = equipmentConnections.zoneAirInletNodes();
  ASSERT_EQ(2u, inletNodes.size());
  EXPECT_EQ(inlet1, inletNodes[0]);
  EXPECT_EQ(inlet2, inletNodes[1]);

  const auto inletTarget = equipmentConnections.getTarget(openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneAirInletNodeorNodeListName);
  ASSERT_TRUE(inletTarget);
  auto inletNodeList = inletTarget->optionalCast<NodeList>();
  ASSERT_TRUE(inletNodeList);
  EXPECT_EQ(2u, inletNodeList->nodes().size());

  ASSERT_TRUE(equipmentConnectionsImpl->removeZoneAirInletNode(inlet1));
  ASSERT_TRUE(equipmentConnectionsImpl->removeZoneAirInletNode(inlet2));
  EXPECT_TRUE(equipmentConnections.zoneAirInletNodes().empty());
}

TEST_F(EPModelFixture, ZoneHVACEquipmentConnections_CanonicalizeSplitsLegacyZoneAirNodeAndInletAlias) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  ASSERT_TRUE(airLoop.addBranchForZone(zone));

  auto connections = zone.getImpl<detail::ThermalZone_Impl>()->zoneHVACEquipmentConnections();
  ASSERT_TRUE(connections);
  auto connectionsImpl = connections->getImpl<detail::ZoneHVACEquipmentConnections_Impl>();
  ASSERT_TRUE(connectionsImpl);
  const auto inletNodes = connections->zoneAirInletNodes();
  ASSERT_EQ(1u, inletNodes.size());
  const auto inletNode = inletNodes.front();
  constexpr unsigned zoneAirNodeField = openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneAirNodeName;

  // Intentional legacy fixture: older EPModel construction used one Node for
  // both the A3 inlet and A5 zone sensing roles.
  ASSERT_TRUE(connectionsImpl->setPointer(zoneAirNodeField, inletNode.handle(), false));
  EXPECT_EQ(inletNode, connections->zoneAirNode());
  const auto objectCountBeforeReport = model.objects().size();
  const auto reportOnly = model.canonicalize(SanitizationPolicy::ReportOnly);
  EXPECT_GT(reportOnly.warningCount, 0u);
  EXPECT_EQ(objectCountBeforeReport, model.objects().size());
  EXPECT_EQ(inletNode, connections->zoneAirNode());

  const auto repair = model.canonicalize(SanitizationPolicy::Repair);
  EXPECT_GT(repair.infoCount, 0u);
  const auto repairedZoneAirNode = connections->zoneAirNode();
  EXPECT_NE(inletNode, repairedZoneAirNode);
  EXPECT_EQ(inletNode, connections->zoneAirInletNodes().front());
  const auto objectCountAfterRepair = model.objects().size();
  const auto repairedHandle = repairedZoneAirNode.handle();

  model.canonicalize(SanitizationPolicy::Repair);
  EXPECT_EQ(objectCountAfterRepair, model.objects().size());
  EXPECT_EQ(repairedHandle, connections->zoneAirNode().handle());
  EXPECT_EQ(inletNode, connections->zoneAirInletNodes().front());

  // Save the old alias again and prove normal load canonicalization repairs a
  // persisted legacy model without changing the A3 inlet.
  ASSERT_TRUE(connectionsImpl->setPointer(zoneAirNodeField, inletNode.handle(), false));
  const auto idfPath =
    openstudio::tempDir() / openstudio::toPath("epmodel-zone-node-alias-" + openstudio::removeBraces(openstudio::createUUID()) + ".idf");
  ScopedFileRemoval cleanup(idfPath);
  ASSERT_TRUE(model.save(idfPath, true));
  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  const auto loadedZones = loadedModel->getConcreteModelObjects<ThermalZone>();
  ASSERT_EQ(1u, loadedZones.size());
  auto loadedConnections = loadedZones.front().getImpl<detail::ThermalZone_Impl>()->zoneHVACEquipmentConnections();
  ASSERT_TRUE(loadedConnections);
  const auto loadedInletNodes = loadedConnections->zoneAirInletNodes();
  ASSERT_EQ(1u, loadedInletNodes.size());
  EXPECT_NE(loadedInletNodes.front(), loadedConnections->zoneAirNode());
}

TEST_F(EPModelFixture, ZoneHVACEquipmentConnections_ReportOnlyPreservesRawInletEvidence) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  ASSERT_TRUE(airLoop.addBranchForZone(zone));

  auto connections = zone.getImpl<detail::ThermalZone_Impl>()->zoneHVACEquipmentConnections();
  ASSERT_TRUE(connections);
  auto connectionsImpl = connections->getImpl<detail::ZoneHVACEquipmentConnections_Impl>();
  auto workspaceImpl = connections->getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(connectionsImpl);
  ASSERT_TRUE(workspaceImpl);

  const auto inletNodes = connections->zoneAirInletNodes();
  ASSERT_EQ(1u, inletNodes.size());
  const auto inletTarget = connections->getTarget(openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneAirInletNodeorNodeListName);
  ASSERT_TRUE(inletTarget);
  const auto inletNodeList = inletTarget->optionalCast<NodeList>();
  ASSERT_TRUE(inletNodeList);

  constexpr unsigned inletField = openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneAirInletNodeorNodeListName;
  constexpr unsigned zoneAirNodeField = openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneAirNodeName;

  // Intentional raw-only imported evidence. ReportOnly must observe this name
  // without enrolling the NodeList pointer or otherwise materializing nodes.
  ASSERT_TRUE(connectionsImpl->setPointer(inletField, openstudio::Handle(), false));
  ASSERT_TRUE(workspaceImpl->openstudio::detail::IdfObject_Impl::setString(inletField, inletNodeList->nameString()));
  ASSERT_TRUE(connectionsImpl->setPointer(zoneAirNodeField, inletNodes.front().handle(), false));
  const auto managedInletBefore = connections->getField(inletField, false);
  const auto rawInletBefore = workspaceImpl->openstudio::detail::IdfObject_Impl::getString(inletField, false, true);
  const auto objectCountBefore = model.objects().size();

  const auto reportOnly = model.canonicalize(SanitizationPolicy::ReportOnly);
  EXPECT_GT(reportOnly.warningCount, 0u);
  EXPECT_EQ(objectCountBefore, model.objects().size());
  EXPECT_TRUE(managedInletBefore == connections->getField(inletField, false));
  EXPECT_TRUE(rawInletBefore == workspaceImpl->openstudio::detail::IdfObject_Impl::getString(inletField, false, true));
  EXPECT_EQ(inletNodes.front().handle(), connections->zoneAirNode().handle());

  // A managed pointer loaded from duplicate-name evidence is likewise not a
  // trustworthy basis for repair: Workspace may have selected either match.
  ASSERT_TRUE(connectionsImpl->setPointer(inletField, inletNodeList->handle(), false));
  NodeList duplicateInletNodeList(model);
  ASSERT_TRUE(duplicateInletNodeList.setName(inletNodeList->nameString()));
  auto duplicateImpl = duplicateInletNodeList.getImpl<detail::NodeList_Impl>();
  ASSERT_TRUE(duplicateImpl);
  Node duplicateInletNode(model);
  ASSERT_TRUE(duplicateImpl->addNode(duplicateInletNode));
  const auto managedDuplicateBefore = connections->getField(inletField, false);
  const auto objectCountBeforeDuplicateReport = model.objects().size();

  const auto duplicateReportOnly = model.canonicalize(SanitizationPolicy::ReportOnly);
  EXPECT_GT(duplicateReportOnly.warningCount, 0u);
  EXPECT_EQ(objectCountBeforeDuplicateReport, model.objects().size());
  EXPECT_TRUE(managedDuplicateBefore == connections->getField(inletField, false));
  EXPECT_EQ(inletNodes.front().handle(), connections->zoneAirNode().handle());
}

TEST_F(EPModelFixture, ZoneHVACEquipmentConnections_ReportOnlyDoesNotCreateMissingZoneAirNode) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  ASSERT_TRUE(airLoop.addBranchForZone(zone));

  auto connections = zone.getImpl<detail::ThermalZone_Impl>()->zoneHVACEquipmentConnections();
  ASSERT_TRUE(connections);
  auto connectionsImpl = connections->getImpl<detail::ZoneHVACEquipmentConnections_Impl>();
  auto workspaceImpl = connections->getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(connectionsImpl);
  ASSERT_TRUE(workspaceImpl);
  constexpr unsigned zoneAirNodeField = openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneAirNodeName;

  ASSERT_TRUE(connectionsImpl->setPointer(zoneAirNodeField, openstudio::Handle(), false));
  const auto managedBefore = connections->getField(zoneAirNodeField, false);
  const auto rawBefore = workspaceImpl->openstudio::detail::IdfObject_Impl::getString(zoneAirNodeField, false, true);
  const auto objectCountBefore = model.objects().size();

  const auto reportOnly = model.canonicalize(SanitizationPolicy::ReportOnly);
  EXPECT_GT(reportOnly.warningCount, 0u);
  EXPECT_EQ(objectCountBefore, model.objects().size());
  EXPECT_TRUE(managedBefore == connections->getField(zoneAirNodeField, false));
  EXPECT_TRUE(rawBefore == workspaceImpl->openstudio::detail::IdfObject_Impl::getString(zoneAirNodeField, false, true));

  const auto repair = model.canonicalize(SanitizationPolicy::Repair);
  EXPECT_GT(repair.infoCount, 0u);
  EXPECT_EQ(zone.nameString() + " Zone Air Node", connections->zoneAirNode().nameString());
}
