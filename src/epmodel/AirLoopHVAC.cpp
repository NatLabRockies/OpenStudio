/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "AirLoopHVAC.hpp"
#include "AirLoopHVAC_Impl.hpp"

#include "BranchList.hpp"
#include "BranchList_Impl.hpp"
#include "Branch.hpp"
#include "AirLoopHVACReturnPath.hpp"
#include "AirLoopHVACReturnPath_Impl.hpp"
#include "AirLoopHVACSupplyPath.hpp"
#include "AirLoopHVACSupplyPath_Impl.hpp"
#include "AirLoopHVACZoneMixer.hpp"
#include "AirLoopHVACZoneMixer_Impl.hpp"
#include "AirLoopHVACZoneSplitter.hpp"
#include "AirLoopHVACZoneSplitter_Impl.hpp"
#include "AirLoopHVACOutdoorAirSystem.hpp"
#include "AirLoopHVACOutdoorAirSystem_Impl.hpp"
#include "ControllerOutdoorAir.hpp"
#include "ControllerOutdoorAir_Impl.hpp"
#include "ControllerMechanicalVentilation.hpp"
#include "ControllerMechanicalVentilation_Impl.hpp"
#include "Loop.hpp"
#include "Loop_Impl.hpp"
#include "Model.hpp"
#include "Node.hpp"
#include "NodeList.hpp"
#include "NodeList_Impl.hpp"
#include "HVACComponent.hpp"
#include "ModelObject.hpp"
#include "StraightComponent.hpp"
#include "ThermalZone.hpp"
#include "ThermalZone_Impl.hpp"
#include "SizingZone.hpp"
#include "SizingZone_Impl.hpp"
#include "DesignSpecificationOutdoorAirSpaceList.hpp"
#include "DesignSpecificationOutdoorAirSpaceList_Impl.hpp"
#include "ZoneHVACEquipmentConnections.hpp"
#include "ZoneHVACEquipmentConnections_Impl.hpp"

#include <utilities/idd/AirLoopHVAC_FieldEnums.hxx>
#include <utilities/idd/AirLoopHVAC_ReturnPath_FieldEnums.hxx>
#include <utilities/idd/AirLoopHVAC_SupplyPath_FieldEnums.hxx>
#include <utilities/idd/AirLoopHVAC_ZoneMixer_FieldEnums.hxx>
#include <utilities/idd/AirLoopHVAC_ZoneSplitter_FieldEnums.hxx>
#include <utilities/idd/Branch_FieldEnums.hxx>
#include <utilities/idd/BranchList_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/NodeList_FieldEnums.hxx>
#include <utilities/idd/ZoneHVAC_EquipmentConnections_FieldEnums.hxx>
#include <utilities/idd/Sizing_Zone_FieldEnums.hxx>
#include <utilities/core/Logger.hpp>
#include <utilities/core/Assert.hpp>
#include <utilities/idf/IdfExtensibleGroup.hpp>
#include <utilities/idf/WorkspaceExtensibleGroup.hpp>

#include <algorithm>
#include <set>
#include <vector>

namespace openstudio {
namespace epmodel {

  AirLoopHVAC::AirLoopHVAC(const Model& model) : Loop(openstudio::IddObjectType::AirLoopHVAC, model) {
    auto impl = getImpl<detail::AirLoopHVAC_Impl>();
    OS_ASSERT(impl);
    detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
    impl->canonicalize(context);
  }

  AirLoopHVAC::AirLoopHVAC(std::shared_ptr<detail::AirLoopHVAC_Impl> impl) : Loop(std::move(impl)) {}

  IddObjectType AirLoopHVAC::iddObjectType() {
    return IddObjectType::AirLoopHVAC;
  }

  Node AirLoopHVAC::supplyInletNode() const {
    return getImpl<detail::AirLoopHVAC_Impl>()->supplyInletNode();
  }

  Node AirLoopHVAC::supplyOutletNode() const {
    return getImpl<detail::AirLoopHVAC_Impl>()->supplyOutletNode();
  }

  std::vector<Node> AirLoopHVAC::supplyOutletNodes() const {
    return getImpl<detail::AirLoopHVAC_Impl>()->supplyOutletNodes();
  }

  Node AirLoopHVAC::demandInletNode() const {
    return getImpl<detail::AirLoopHVAC_Impl>()->demandInletNode();
  }

  Node AirLoopHVAC::demandOutletNode() const {
    return getImpl<detail::AirLoopHVAC_Impl>()->demandOutletNode();
  }

  std::vector<Node> AirLoopHVAC::demandInletNodes() const {
    return getImpl<detail::AirLoopHVAC_Impl>()->demandInletNodes();
  }

  AirLoopHVACZoneSplitter AirLoopHVAC::zoneSplitter() const {
    return getImpl<detail::AirLoopHVAC_Impl>()->zoneSplitter();
  }

  AirLoopHVACZoneMixer AirLoopHVAC::zoneMixer() const {
    return getImpl<detail::AirLoopHVAC_Impl>()->zoneMixer();
  }

  std::vector<ModelObject> AirLoopHVAC::supplyComponents(const HVACComponent& inletComp, const HVACComponent& outletComp,
                                                         openstudio::IddObjectType type) const {
    return getImpl<detail::AirLoopHVAC_Impl>()->supplyComponents(inletComp, outletComp, type);
  }

  std::vector<ModelObject> AirLoopHVAC::supplyComponents(openstudio::IddObjectType type) const {
    return getImpl<detail::AirLoopHVAC_Impl>()->supplyComponents(type);
  }

  std::vector<ModelObject> AirLoopHVAC::demandComponents(const HVACComponent& inletComp, const HVACComponent& outletComp,
                                                         openstudio::IddObjectType type) const {
    return getImpl<detail::AirLoopHVAC_Impl>()->demandComponents(inletComp, outletComp, type);
  }

  std::vector<ModelObject> AirLoopHVAC::demandComponents(openstudio::IddObjectType type) const {
    return getImpl<detail::AirLoopHVAC_Impl>()->demandComponents(type);
  }

  boost::optional<AirLoopHVACOutdoorAirSystem> AirLoopHVAC::airLoopHVACOutdoorAirSystem() const {
    return getImpl<detail::AirLoopHVAC_Impl>()->airLoopHVACOutdoorAirSystem();
  }

  std::vector<ThermalZone> AirLoopHVAC::thermalZones() const {
    return getImpl<detail::AirLoopHVAC_Impl>()->thermalZones();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    namespace {

      // Resolve a terminal on the demand branch by matching a straight component inlet
      // to the splitter outlet branch node.
      boost::optional<ModelObject> terminalForInletNode(const ModelObject& splitterOutletNode) {
        for (const auto& object : splitterOutletNode.model().objects()) {
          auto component = object.optionalCast<StraightComponent>();
          if (!component) {
            continue;
          }

          const auto inletObject = component->inletModelObject();
          if (!inletObject) {
            continue;
          }

          auto inletNode = inletObject->optionalCast<Node>();
          if (!inletNode) {
            continue;
          }

          if (*inletNode == splitterOutletNode) {
            return component.get().cast<ModelObject>();
          }
        }
        return boost::none;
      }

      // Resolve a ThermalZone from a zone inlet node using ZoneHVAC:EquipmentConnections.
      boost::optional<ThermalZone> zoneForInletNode(const Node& inletNode) {
        const auto& model = inletNode.model();
        std::vector<ThermalZone> zones;

        const auto inletNameMatches = [&](const ZoneHVACEquipmentConnections& conn) -> bool {
          if (auto directInlet = conn.zoneAirInletNode()) {
            return (*directInlet == inletNode);
          }

          const auto inletNodeOrListName = conn.getString(openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneAirInletNodeorNodeListName);
          if (!inletNodeOrListName || inletNodeOrListName->empty()) {
            return false;
          }

          if (openstudio::istringEqual(*inletNodeOrListName, inletNode.nameString())) {
            return true;
          }

          if (auto nodeList = model.getObjectByTypeAndName(openstudio::IddObjectType::NodeList, *inletNodeOrListName)) {
            for (const auto& group : nodeList->extensibleGroups()) {
              const auto listedNodeName = group.getString(openstudio::NodeListExtensibleFields::NodeName);
              if (listedNodeName && openstudio::istringEqual(*listedNodeName, inletNode.nameString())) {
                return true;
              }
            }
          }

          return false;
        };

        for (const auto& conn : model.getConcreteModelObjects<ZoneHVACEquipmentConnections>()) {
          if (!inletNameMatches(conn)) {
            continue;
          }
          if (auto zone = conn.thermalZone()) {
            zones.push_back(*zone);
          }
        }

        if (zones.empty()) {
          return boost::none;
        }

        std::sort(zones.begin(), zones.end(), [](const ThermalZone& lhs, const ThermalZone& rhs) { return lhs.nameString() < rhs.nameString(); });

        if (zones.size() > 1u) {
          LOG_FREE(Warn, "openstudio.epmodel.AirLoopHVAC",
                   "Multiple ThermalZones reference zone inlet node '" << inletNode.nameString() << "'. Using first zone by name ordering.");
        }

        return zones.front();
      }

      // Resolve a ThermalZone from a zone outlet/return node using ZoneHVAC:EquipmentConnections.
      boost::optional<ModelObject> zoneForOutletNode(const ModelObject& outletObject) {
        auto outletNode = outletObject.optionalCast<Node>();
        if (!outletNode) {
          return boost::none;
        }

        const auto& model = outletNode->model();
        std::vector<ThermalZone> zones;

        const auto outletNameMatches = [&](const ZoneHVACEquipmentConnections& conn) -> bool {
          if (auto directOutlet = conn.zoneReturnAirNode()) {
            return (*directOutlet == *outletNode);
          }

          const auto outletNodeOrListName = conn.getString(openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneReturnAirNodeorNodeListName);
          if (!outletNodeOrListName || outletNodeOrListName->empty()) {
            return false;
          }

          if (openstudio::istringEqual(*outletNodeOrListName, outletNode->nameString())) {
            return true;
          }

          if (auto nodeList = model.getObjectByTypeAndName(openstudio::IddObjectType::NodeList, *outletNodeOrListName)) {
            for (const auto& group : nodeList->extensibleGroups()) {
              const auto listedNodeName = group.getString(openstudio::NodeListExtensibleFields::NodeName);
              if (listedNodeName && openstudio::istringEqual(*listedNodeName, outletNode->nameString())) {
                return true;
              }
            }
          }

          return false;
        };

        for (const auto& conn : model.getConcreteModelObjects<ZoneHVACEquipmentConnections>()) {
          if (!outletNameMatches(conn)) {
            continue;
          }
          if (auto zone = conn.thermalZone()) {
            zones.push_back(*zone);
          }
        }

        if (zones.empty()) {
          return boost::none;
        }

        std::sort(zones.begin(), zones.end(), [](const ThermalZone& lhs, const ThermalZone& rhs) { return lhs.nameString() < rhs.nameString(); });

        if (zones.size() > 1u) {
          LOG_FREE(Warn, "openstudio.epmodel.AirLoopHVAC",
                   "Multiple ThermalZones reference zone outlet node '" << outletNode->nameString() << "'. Using first zone by name ordering.");
        }

        return zones.front().cast<ModelObject>();
      }

      // Resolve the outlet node for a terminal object when available.
      boost::optional<ModelObject> outletForTerminal(const ModelObject& terminal) {
        auto component = terminal.optionalCast<StraightComponent>();
        if (!component) {
          return boost::none;
        }

        auto outletObject = component->outletModelObject();
        if (!outletObject) {
          return boost::none;
        }

        return outletObject;
      }

    }  // namespace

    void AirLoopHVAC_Impl::doCanonicalize(LoadContext& context) {
      auto airLoop = getObject<AirLoopHVAC>();
      OS_ASSERT(!airLoop.nameString().empty());
      const auto loopName = airLoop.nameString();

      {  // Canonical topology anchor points.
         // These node references are the entry/exit contracts used by supply
         // and demand path traversal; if they drift, most loop APIs become
         // ambiguous. We always materialize them first.
        getOrCreateTarget<Node>(AirLoopHVACFields::SupplySideInletNodeName, loopName + " Supply Inlet Node");
        detail::NodeList_Impl::ensureAttachedNodeList(context, airLoop, AirLoopHVACFields::SupplySideOutletNodeNames, " Supply Outlet Nodes",
                                                      " Supply Outlet Node");
        detail::NodeList_Impl::ensureAttachedNodeList(context, airLoop, AirLoopHVACFields::DemandSideInletNodeNames, " Demand Inlet Nodes",
                                                      " Demand Inlet Node");
        getOrCreateTarget<Node>(AirLoopHVACFields::DemandSideOutletNodeName, loopName + " Demand Outlet Node");

        {  // Supply branch storage contract.
           // BranchList is the E+ source-of-truth for supply component order.
           // Ensure at least one branch exists so path extraction can build a
           // deterministic adjacency graph.
          auto branchList = getOrCreateTarget<BranchList>(AirLoopHVACFields::BranchListName);
          if (branchList.branches().empty()) {
            const auto branch = Branch(model());
            branchList.getImpl<detail::BranchList_Impl>()->addBranch(branch);
            detail::addLoadInfo(context, "Added default Branch '" + branch.nameString() + "' to BranchList '" + branchList.nameString()
                                           + "' for AirLoopHVAC '" + airLoop.nameString() + "'.");
          }
        }
      }

      {  // Demand-side splitter anchor keyed by demand inlet node.
         // This reproduces openstudio::model topology assumptions while storing
         // the association using E+ node-linkage semantics.
        boost::optional<AirLoopHVACZoneSplitter> zoneSplitter;
        const auto inletNode = demandInletNode();
        for (auto& zp : model().getConcreteModelObjects<AirLoopHVACZoneSplitter>()) {
          if (zp.getImpl<detail::AirLoopHVACZoneSplitter_Impl>()->inletNode() == inletNode) {
            zoneSplitter = zp;
            break;
          }
        }
        if (!zoneSplitter) {
          zoneSplitter = AirLoopHVACZoneSplitter(model());
          zoneSplitter->setName(loopName + " Zone Splitter");
          zoneSplitter->getImpl<detail::AirLoopHVACZoneSplitter_Impl>()->setInletNode(inletNode);
          detail::addLoadInfo(context,
                              "Created missing AirLoopHVAC:ZoneSplitter '" + zoneSplitter->nameString() + "' for AirLoopHVAC '" + loopName + "'.");
        }
        zoneSplitter->getImpl<detail::AirLoopHVACZoneSplitter_Impl>()->canonicalize(context);
      }

      {  // Demand-side mixer anchor keyed by demand outlet node.
         // Splitter + mixer pair define branch fan-out/fan-in boundaries.
        boost::optional<AirLoopHVACZoneMixer> zoneMixer;
        const auto outletNode = demandOutletNode();
        for (auto& zm : model().getConcreteModelObjects<AirLoopHVACZoneMixer>()) {
          if (zm.getImpl<detail::AirLoopHVACZoneMixer_Impl>()->outletNode() == outletNode) {
            zoneMixer = zm;
            break;
          }
        }
        if (!zoneMixer) {
          zoneMixer = AirLoopHVACZoneMixer(model());
          zoneMixer->setName(loopName + " Zone Mixer");
          zoneMixer->getImpl<detail::AirLoopHVACZoneMixer_Impl>()->setOutletNode(outletNode);
          detail::addLoadInfo(context, "Created missing AirLoopHVAC:ZoneMixer '" + zoneMixer->nameString() + "' for AirLoopHVAC '" + loopName + "'.");
        }
        zoneMixer->getImpl<detail::AirLoopHVACZoneMixer_Impl>()->canonicalize(context);
      }

      {  // SupplyPath object keyed by demand inlet node.
         // Path objects are connective tissue in E+ schema; we keep them
         // explicit so traversal and mutation do not infer hidden links.
        boost::optional<AirLoopHVACSupplyPath> supplyPath;
        const auto inletNode = demandInletNode();
        for (auto& sp : model().getConcreteModelObjects<AirLoopHVACSupplyPath>()) {
          if (sp.getImpl<detail::AirLoopHVACSupplyPath_Impl>()->supplyAirPathInletNode() == inletNode) {
            supplyPath = sp;
            break;
          }
        }
        if (!supplyPath) {
          supplyPath = AirLoopHVACSupplyPath(model());
          supplyPath->setName(loopName + " Supply Path");
          supplyPath->getImpl<detail::AirLoopHVACSupplyPath_Impl>()->setSupplyAirPathInletNode(airLoop.demandInletNode());
          detail::addLoadInfo(context,
                              "Created missing AirLoopHVAC:SupplyPath '" + supplyPath->nameString() + "' for AirLoopHVAC '" + loopName + "'.");
        }
        supplyPath->getImpl<detail::AirLoopHVACSupplyPath_Impl>()->canonicalize(context);
      }

      {  // ReturnPath object keyed by demand outlet node.
         // Together with SupplyPath this keeps demand topology round-trippable
         // through IDF connective-tissue objects.
        boost::optional<AirLoopHVACReturnPath> returnPath;
        const auto outletNode = demandOutletNode();
        for (auto& rp : model().getConcreteModelObjects<AirLoopHVACReturnPath>()) {
          if (rp.getImpl<detail::AirLoopHVACReturnPath_Impl>()->returnAirPathOutletNode() == outletNode) {
            returnPath = rp;
            break;
          }
        }
        if (!returnPath) {
          returnPath = AirLoopHVACReturnPath(model());
          returnPath->setName(loopName + " Return Path");
          returnPath->getImpl<detail::AirLoopHVACReturnPath_Impl>()->setReturnAirPathOutletNode(airLoop.demandOutletNode());
          detail::addLoadInfo(context,
                              "Created missing AirLoopHVAC:ReturnPath '" + returnPath->nameString() + "' for AirLoopHVAC '" + loopName + "'.");
        }
        returnPath->getImpl<detail::AirLoopHVACReturnPath_Impl>()->canonicalize(context);
      }

      {  // Ensure there is at least one Node between the zone splitter and mixer
        auto zs = zoneSplitter();
        auto zm = zoneMixer();

        if (zs.outletModelObjects().size() != zm.inletModelObjects().size()) {
          const auto splitterBranches = zs.outletModelObjects().size();
          const auto mixerBranches = zm.inletModelObjects().size();
          while (!zs.outletModelObjects().empty()) {
            zs.removePortForBranch(static_cast<unsigned>(zs.outletModelObjects().size() - 1u));
          }
          while (!zm.inletModelObjects().empty()) {
            zm.removePortForBranch(static_cast<unsigned>(zm.inletModelObjects().size() - 1u));
          }
          detail::addLoadWarning(context, "ZoneSplitter/ZoneMixer branch count mismatch for AirLoopHVAC '" + loopName
                                            + "' (splitter=" + std::to_string(splitterBranches) + ", mixer=" + std::to_string(mixerBranches)
                                            + "). Cleared branch node ports to rebuild.");
        }

        if (zs.outletModelObjects().empty()) {
          Node branchNode(model());
          branchNode.setName(loopName + " Demand Branch Node");
          zs.setOutletModelObject(0u, branchNode);
          zm.setInletModelObject(0u, branchNode);
          detail::addLoadInfo(context, "Created demand branch node '" + branchNode.nameString()
                                         + "' between ZoneSplitter and ZoneMixer for AirLoopHVAC '" + loopName + "'.");
        }
      }

      {  // OA/CMV linkage is loop-scoped.
         // At most one OA system is supported on an AirLoopHVAC. Canonicalize
         // that OA system first, then rebuild CMV zone OA entries from loop thermal zones.
        if (auto oaSystem = airLoopHVACOutdoorAirSystem()) {
          auto oaSystemImpl = oaSystem->getImpl<detail::AirLoopHVACOutdoorAirSystem_Impl>();
          OS_ASSERT(oaSystemImpl);
          oaSystemImpl->canonicalize(context);
        }

        syncControllerMechanicalVentilationZoneOutdoorAirEntries();
      }
    }

    void AirLoopHVAC_Impl::syncControllerMechanicalVentilationZoneOutdoorAirEntries() {
      auto airLoop = getObject<AirLoopHVAC>();
      std::vector<std::pair<openstudio::epmodel::ThermalZone, openstudio::epmodel::DesignSpecificationOutdoorAirSpaceList>> entries;
      for (const auto& zone : airLoop.thermalZones()) {
        auto sizingZone = zone.sizingZone();
        auto dsoaSpaceList = sizingZone.getImpl<openstudio::epmodel::detail::SizingZone_Impl>()->designSpecificationOutdoorAirSpaceList();
        if (dsoaSpaceList) {
          entries.emplace_back(zone, *dsoaSpaceList);
        }
      }

      auto oaSystem = airLoopHVACOutdoorAirSystem();
      if (!oaSystem) {
        return;
      }

      auto oaController = oaSystem->getControllerOutdoorAir();
      auto cmv = oaController.getImpl<detail::ControllerOutdoorAir_Impl>()->optionalControllerMechanicalVentilation();
      if (!cmv) {
        return;
      }

      // Big picture: CMV extensible groups are not the source of truth. The
      // source of truth is ThermalZone -> Sizing:Zone ->
      // DesignSpecification:OutdoorAir:SpaceList. CMV entries are just the E+
      // runtime projection of that relationship for this air loop.
      auto cmvImpl = cmv->getImpl<openstudio::epmodel::detail::ControllerMechanicalVentilation_Impl>();
      OS_ASSERT(cmvImpl);
      cmvImpl->clearZoneOutdoorAirEntries();
      for (const auto& [zone, dsoaSpaceList] : entries) {
        OS_ASSERT(cmvImpl->addZoneOutdoorAirEntry(zone, dsoaSpaceList));
      }
    }

    Node AirLoopHVAC_Impl::supplyInletNode() const {
      auto node = getObject<AirLoopHVAC>().getModelObjectTarget<Node>(AirLoopHVACFields::SupplySideInletNodeName);
      OS_ASSERT(node);
      return *node;
    }

    std::vector<Node> AirLoopHVAC_Impl::supplyOutletNodes() const {
      auto airLoop = getObject<AirLoopHVAC>();
      auto nodeList = airLoop.getModelObjectTarget<NodeList>(AirLoopHVACFields::SupplySideOutletNodeNames);
      OS_ASSERT(nodeList);
      const auto nodes = nodeList->nodes();
      OS_ASSERT(!nodes.empty());
      return nodes;
    }

    Node AirLoopHVAC_Impl::supplyOutletNode() const {
      return supplyOutletNodes().front();
    }

    std::vector<Node> AirLoopHVAC_Impl::demandInletNodes() const {
      auto airLoop = getObject<AirLoopHVAC>();
      auto nodeList = airLoop.getModelObjectTarget<NodeList>(AirLoopHVACFields::DemandSideInletNodeNames);
      OS_ASSERT(nodeList);
      const auto nodes = nodeList->nodes();
      OS_ASSERT(!nodes.empty());
      return nodes;
    }

    Node AirLoopHVAC_Impl::demandInletNode() const {
      return demandInletNodes().front();
    }

    Node AirLoopHVAC_Impl::demandOutletNode() const {
      auto node = getObject<AirLoopHVAC>().getModelObjectTarget<Node>(AirLoopHVACFields::DemandSideOutletNodeName);
      OS_ASSERT(node);
      return *node;
    }

    BranchList AirLoopHVAC_Impl::branchList() const {
      auto branchList = getObject<AirLoopHVAC>().getModelObjectTarget<BranchList>(AirLoopHVACFields::BranchListName);
      OS_ASSERT(branchList);
      return *branchList;
    }

    AirLoopHVACReturnPath AirLoopHVAC_Impl::airLoopHVACReturnPath() const {
      // ReturnPath is associated to an AirLoopHVAC through the demand-side outlet node name.
      const auto demandOutlet = demandOutletNode();
      boost::optional<AirLoopHVACReturnPath> result;

      // First try to find an existing ReturnPath already keyed to this demand outlet node.
      for (const auto& returnPath : model().getConcreteModelObjects<AirLoopHVACReturnPath>()) {
        if (auto target = returnPath.getTarget(AirLoopHVAC_ReturnPathFields::ReturnAirPathOutletNodeName)) {
          if (*target == demandOutlet) {
            result = returnPath;
            break;
          }
        }
      }
      OS_ASSERT(result);
      return *result;
    }

    AirLoopHVACSupplyPath AirLoopHVAC_Impl::airLoopHVACSupplyPath() const {
      // SupplyPath is associated to an AirLoopHVAC through the demand-side inlet node name.
      const auto demandInlet = demandInletNode();
      boost::optional<AirLoopHVACSupplyPath> result;

      // First try to find an existing SupplyPath already keyed to this demand inlet node.
      for (const auto& supplyPath : model().getConcreteModelObjects<AirLoopHVACSupplyPath>()) {
        if (auto target = supplyPath.getTarget(AirLoopHVAC_SupplyPathFields::SupplyAirPathInletNodeName)) {
          if (*target == demandInlet) {
            result = supplyPath;
            break;
          }
        }
      }
      OS_ASSERT(result);
      return *result;
    }

    AirLoopHVACZoneSplitter AirLoopHVAC_Impl::zoneSplitter() const {
      const auto supplyPath = airLoopHVACSupplyPath();
      boost::optional<AirLoopHVACZoneSplitter> result;
      for (const auto& component : supplyPath.components()) {
        if (auto splitter = component.optionalCast<AirLoopHVACZoneSplitter>()) {
          result = *splitter;
          break;
        }
      }
      OS_ASSERT(result);
      return *result;
    }

    AirLoopHVACZoneMixer AirLoopHVAC_Impl::zoneMixer() const {
      const auto returnPath = airLoopHVACReturnPath();
      boost::optional<AirLoopHVACZoneMixer> result;
      for (const auto& component : returnPath.components()) {
        if (auto mixer = component.optionalCast<AirLoopHVACZoneMixer>()) {
          result = *mixer;
          break;
        }
      }
      OS_ASSERT(result);
      return *result;
    }

    Node AirLoopHVAC_Impl::demandBranchNode() const {
      // Mirror openstudio::model demand-side topology:
      // Demand Inlet Node -> ZoneSplitter -> Branch Node -> ZoneMixer -> Demand Outlet Node
      // Canonicalization owns the repairs; this accessor expects canonicalized state.
      auto splitter = zoneSplitter();
      auto mixer = zoneMixer();

      boost::optional<Node> branchNode;

      // Prefer splitter first outlet node target if present.
      for (const auto& group : splitter.extensibleGroups()) {
        auto workspaceGroup = group.optionalCast<openstudio::WorkspaceExtensibleGroup>();
        OS_ASSERT(workspaceGroup);
        if (auto target = workspaceGroup->getTarget(AirLoopHVAC_ZoneSplitterExtensibleFields::OutletNodeName)) {
          if (auto node = target->optionalCast<Node>()) {
            branchNode = *node;
            break;
          }
        }
      }

      // Otherwise use mixer first inlet node target if present.
      if (!branchNode) {
        for (const auto& group : mixer.extensibleGroups()) {
          auto workspaceGroup = group.optionalCast<openstudio::WorkspaceExtensibleGroup>();
          OS_ASSERT(workspaceGroup);
          if (auto target = workspaceGroup->getTarget(AirLoopHVAC_ZoneMixerExtensibleFields::InletNodeName)) {
            if (auto node = target->optionalCast<Node>()) {
              branchNode = *node;
              break;
            }
          }
        }
      }

      if (!branchNode) {
        OS_ASSERT(false);
      }

      return *branchNode;
    }

    std::vector<ModelObject> AirLoopHVAC_Impl::supplyComponents(const HVACComponent& inletComp, const HVACComponent& outletComp,
                                                                openstudio::IddObjectType type) const {

      // Build an adjacency graph from BranchList ordering and explicit node
      // links. This makes supply traversal deterministic and independent from
      // call-site assumptions about specific component classes.
      AdjacencyBuilder builder;
      ModelObject previousObject = supplyInletNode();

      const auto branchListName = getString(AirLoopHVACFields::BranchListName);
      if (!(branchListName && !branchListName->empty())) {
        OS_ASSERT(false);
        return {};
      }
      auto branchListObject = workspace().getObjectByTypeAndName(openstudio::IddObjectType::BranchList, *branchListName);
      if (!branchListObject) {
        OS_ASSERT(false);
        return {};
      }
      auto branchList = branchListObject->optionalCast<BranchList>();
      if (!branchList) {
        OS_ASSERT(false);
        return {};
      }
      const auto branches = branchList->branches();
      if (branches.empty()) {
        OS_ASSERT(false);
        return {};
      }
      const auto& supplyBranch = branches.front();
      const auto groups = supplyBranch.extensibleGroups();
      for (const auto& group : groups) {
        const auto componentType = group.getString(BranchExtensibleFields::ComponentObjectType);
        const auto componentName = group.getString(BranchExtensibleFields::ComponentName);
        if (!componentType || componentType->empty() || !componentName || componentName->empty()) {
          OS_ASSERT(false);
          continue;
        }

        openstudio::IddObjectType componentIddType = openstudio::IddObjectType::Catchall;
        try {
          componentIddType = openstudio::IddObjectType(*componentType);
        } catch (...) {  // NOLINT
          OS_ASSERT(false);
          continue;
        }

        auto componentObject = model().getObjectByTypeAndName(componentIddType, *componentName);
        if (!componentObject) {
          OS_ASSERT(false);
          continue;
        }
        auto supplyComponent = componentObject->optionalCast<ModelObject>();
        if (!supplyComponent) {
          OS_ASSERT(false);
          continue;
        }

        // Preserve branch ordering exactly as listed in Branch extensibles;
        // this is the canonical sequencing contract for supply traversal.
        builder.addLink(previousObject, *supplyComponent);
        previousObject = *supplyComponent;

        auto workspaceGroup = group.optionalCast<openstudio::WorkspaceExtensibleGroup>();
        OS_ASSERT(workspaceGroup);
        auto target = workspaceGroup->getTarget(BranchExtensibleFields::ComponentOutletNodeName);
        boost::optional<Node> outletNode;
        if (target) {
          outletNode = target->optionalCast<Node>();
        }
        if (!outletNode) {
          OS_ASSERT(false);
          continue;
        }
        builder.addLink(previousObject, *outletNode);
        previousObject = *outletNode;
      }

      const auto outletNode = supplyOutletNode();
      // Default-constructed loops may still have only partial branch topology.
      // Close the chain to supply outlet so path walking always has a terminal
      // anchor even before richer supply components are added.
      if (previousObject != outletNode) {
        builder.addLink(previousObject, outletNode);
      }

      // Traverse once through the canonical adjacency graph instead of
      // re-deriving branch relationships per query call.
      auto pathObjects = builder.walkPath(model(), inletComp, outletComp);

      // Type filtering is a pure view operation over the resolved path.
      if (type == openstudio::IddObjectType::Catchall) {
        return pathObjects;
      }

      std::vector<ModelObject> filtered;
      for (const auto& obj : pathObjects) {
        if (obj.iddObject().type() == type) {
          filtered.push_back(obj);
        }
      }
      return filtered;
    }

    std::vector<ModelObject> AirLoopHVAC_Impl::supplyComponents(openstudio::IddObjectType type) const {
      return supplyComponents(supplyInletNode(), supplyOutletNode(), type);
    }

    std::vector<ModelObject> AirLoopHVAC_Impl::demandComponents(const HVACComponent& inletComp, const HVACComponent& outletComp,
                                                                openstudio::IddObjectType type) const {
      AdjacencyBuilder builder;
      const auto demandInlet = demandInletNode();
      const auto demandOutlet = demandOutletNode();
      const auto zoneSplitter = this->zoneSplitter();
      const auto zoneMixer = this->zoneMixer();

      auto buildDemandBranchLeg = [&](const ModelObject& splitterOutletObject, const ModelObject& mixerInletObject) {
        // Construct one demand leg at a time from splitter outlet to mixer
        // inlet, explicitly stitching terminal/zone objects where they can be
        // resolved. This keeps leg construction local and debuggable.
        std::vector<ModelObject> chain;
        chain.reserve(5);
        std::set<openstudio::Handle> seenInChain;

        auto appendDistinct = [&](const ModelObject& obj) {
          if (seenInChain.insert(obj.handle()).second) {
            chain.push_back(obj);
          }
        };

        appendDistinct(splitterOutletObject);

        // Resolve terminal-driven leg internals once to avoid ambiguous
        // backtracking across zone-level relationships.
        bool zoneAdded = false;
        if (auto terminal = terminalForInletNode(splitterOutletObject)) {
          appendDistinct(*terminal);

          if (auto terminalOutlet = outletForTerminal(*terminal)) {
            appendDistinct(*terminalOutlet);

            if (auto terminalOutletNode = terminalOutlet->optionalCast<Node>()) {
              if (auto zone = zoneForInletNode(*terminalOutletNode)) {
                appendDistinct(zone.get().cast<ModelObject>());
                zoneAdded = true;
              }
            }
          }
        }

        // Fallback for incomplete terminal linkage: still anchor zone via
        // mixer-side node so demand graph remains connected.
        if (!zoneAdded) {
          if (auto zone = zoneForOutletNode(mixerInletObject)) {
            appendDistinct(*zone);
          }
        }

        // Anchor each leg at mixer inlet; we intentionally do not model full
        // intra-zone graph details in this loop-level traversal API.
        appendDistinct(mixerInletObject);

        builder.addLink(zoneSplitter, chain.front());
        for (size_t i = 0; i + 1 < chain.size(); ++i) {
          builder.addLink(chain[i], chain[i + 1]);
        }
        builder.addLink(chain.back(), zoneMixer);
      };

      builder.addLink(demandInlet, zoneSplitter);

      const auto splitterOutlets = zoneSplitter.outletModelObjects();
      const auto mixerInlets = zoneMixer.inletModelObjects();
      // Canonical demand topology keeps splitter outlets and mixer inlets in
      // lockstep. Keep an assert for invariant drift and still guard indexing
      // with min() in non-assert builds.
      OS_ASSERT(splitterOutlets.size() == mixerInlets.size());
      const auto branchCount = std::min(splitterOutlets.size(), mixerInlets.size());

      for (unsigned i = 0; i < branchCount; ++i) {
        buildDemandBranchLeg(splitterOutlets[i], mixerInlets[i]);
      }

      builder.addLink(zoneMixer, demandOutlet);
      const auto pathObjects = builder.walkPath(model(), demandInlet, demandOutlet);

      auto inletIt = std::find(pathObjects.begin(), pathObjects.end(), inletComp);
      if (inletIt == pathObjects.end()) {
        return {};
      }

      auto outletIt = std::find(inletIt, pathObjects.end(), outletComp);
      if (outletIt == pathObjects.end()) {
        return {};
      }

      std::vector<ModelObject> subPath(inletIt, std::next(outletIt));
      if (type == openstudio::IddObjectType::Catchall) {
        return subPath;
      }

      std::vector<ModelObject> filtered;
      filtered.reserve(subPath.size());
      for (const auto& obj : subPath) {
        if (obj.iddObject().type() == type) {
          filtered.push_back(obj);
        }
      }
      return filtered;
    }

    std::vector<ModelObject> AirLoopHVAC_Impl::demandComponents(openstudio::IddObjectType type) const {
      return demandComponents(demandInletNode(), demandOutletNode(), type);
    }

    boost::optional<openstudio::epmodel::AirLoopHVACOutdoorAirSystem> AirLoopHVAC_Impl::airLoopHVACOutdoorAirSystem() const {
      auto oaSystems =
        subsetCastVector<openstudio::epmodel::AirLoopHVACOutdoorAirSystem>(supplyComponents(openstudio::IddObjectType::AirLoopHVAC_OutdoorAirSystem));
      if (oaSystems.empty()) {
        return boost::none;
      }
      OS_ASSERT(oaSystems.size() == 1u);
      return oaSystems.front();
    }

    std::vector<openstudio::epmodel::ThermalZone> AirLoopHVAC_Impl::thermalZones() const {
      auto zones = subsetCastVector<openstudio::epmodel::ThermalZone>(demandComponents(openstudio::IddObjectType::Zone));
      return zones;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
