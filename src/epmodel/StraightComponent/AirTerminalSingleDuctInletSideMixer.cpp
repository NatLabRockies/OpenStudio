/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/AirTerminalSingleDuctInletSideMixer.hpp"
#include "StraightComponent/AirTerminalSingleDuctInletSideMixer_Impl.hpp"

#include "HVACComponent/ThermalZone.hpp"
#include "HVACComponent/ThermalZone_Impl.hpp"
#include "ModelObject/ZoneHVACAirDistributionUnit.hpp"
#include "ModelObject/ZoneHVACAirDistributionUnit_Impl.hpp"
#include "ModelObject/ZoneHVACEquipmentConnections.hpp"
#include "ModelObject/ZoneHVACEquipmentConnections_Impl.hpp"
#include "ModelObject/ZoneHVACEquipmentList.hpp"
#include "ModelObject/ZoneHVACEquipmentList_Impl.hpp"
#include "Model.hpp"
#include "Model_Impl.hpp"
#include "ModelObject.hpp"
#include "Node.hpp"
#include "Node_Impl.hpp"
#include "Loop/AirLoopHVAC.hpp"
#include "Loop/AirLoopHVAC_Impl.hpp"
#include "Mixer/AirLoopHVACZoneMixer.hpp"
#include "Mixer/AirLoopHVACZoneMixer_Impl.hpp"
#include "Splitter/AirLoopHVACZoneSplitter.hpp"
#include "Splitter/AirLoopHVACZoneSplitter_Impl.hpp"
#include "ZoneHVACComponent/ZoneHVACComponent.hpp"
#include "ZoneHVACComponent/ZoneHVACComponent_Impl.hpp"

#include <algorithm>
#include <utilities/core/Assert.hpp>
#include <utilities/core/Logger.hpp>
#include <utilities/idd/AirTerminal_SingleDuct_Mixer_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/ZoneHVAC_AirDistributionUnit_FieldEnums.hxx>
#include <utilities/idd/ZoneHVAC_EquipmentConnections_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  namespace {

    boost::optional<ThermalZone> owningThermalZoneForBranchNode(const Model& model, const Node& node) {
      for (const auto& connections : model.getConcreteModelObjects<ZoneHVACEquipmentConnections>()) {
        const auto inletNodes = connections.zoneAirInletNodes();
        if (std::ranges::find(inletNodes, node) != inletNodes.end()) {
          return connections.thermalZone();
        }
      }
      return boost::none;
    }

    bool isServedZoneReturnNode(const boost::optional<ThermalZone>& thermalZone, const ModelObject& nodeObject) {
      auto node = nodeObject.optionalCast<Node>();
      if (!thermalZone || !node) {
        return false;
      }

      auto zoneImpl = thermalZone->getImpl<detail::ThermalZone_Impl>();
      OS_ASSERT(zoneImpl);
      auto connections = zoneImpl->zoneHVACEquipmentConnections();
      if (!connections) {
        return false;
      }

      const auto returnNodes = connections->zoneReturnAirNodes();
      return std::ranges::find(returnNodes, *node) != returnNodes.end();
    }

    boost::optional<ThermalZone> thermalZoneContainingTerminal(const Model& model, const ModelObject& terminal) {
      for (const auto& zone : model.getConcreteModelObjects<ThermalZone>()) {
        const auto equipment = zone.equipment();
        if (std::ranges::find(equipment, terminal) != equipment.end()) {
          return zone;
        }
      }
      return boost::none;
    }

    bool registerTerminalWithThermalZone(const ModelObject& terminal, ThermalZone& thermalZone) {
      auto zoneImpl = thermalZone.getImpl<detail::ThermalZone_Impl>();
      OS_ASSERT(zoneImpl);
      return zoneImpl->getZoneHVACEquipmentList().addEquipment(terminal);
    }

    bool unregisterTerminalFromThermalZone(const ModelObject& terminal, ThermalZone& thermalZone) {
      auto zoneImpl = thermalZone.getImpl<detail::ThermalZone_Impl>();
      OS_ASSERT(zoneImpl);
      return zoneImpl->getZoneHVACEquipmentList().removeEquipment(terminal);
    }

    boost::optional<ZoneHVACComponent> downstreamZoneHVACForTerminalOutlet(const Model& model, const Node& outletNode) {
      for (const auto& zoneHVAC : model.getModelObjects<ZoneHVACComponent>()) {
        auto inlet = zoneHVAC.inletNode();
        if (!inlet || (*inlet != outletNode)) {
          continue;
        }

        auto thermalZone = zoneHVAC.thermalZone();
        if (!thermalZone) {
          continue;
        }

        const auto equipment = thermalZone->equipment();
        if (std::ranges::find(equipment, zoneHVAC.cast<ModelObject>()) != equipment.end()) {
          return zoneHVAC;
        }
      }

      return boost::none;
    }

  }  // namespace

  AirTerminalSingleDuctInletSideMixer::AirTerminalSingleDuctInletSideMixer(const Model& model)
    : StraightComponent(AirTerminalSingleDuctInletSideMixer::iddObjectType(), model) {
    auto impl = getImpl<detail::AirTerminalSingleDuctInletSideMixer_Impl>();
    OS_ASSERT(impl);
    detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
    impl->canonicalize(context);
    OS_ASSERT(setPerPersonVentilationRateMode("CurrentOccupancy"));
  }

  AirTerminalSingleDuctInletSideMixer::AirTerminalSingleDuctInletSideMixer(std::shared_ptr<detail::AirTerminalSingleDuctInletSideMixer_Impl> impl)
    : StraightComponent(std::move(impl)) {}

  IddObjectType AirTerminalSingleDuctInletSideMixer::iddObjectType() {
    return IddObjectType::AirTerminal_SingleDuct_Mixer;
  }

  std::vector<std::string> AirTerminalSingleDuctInletSideMixer::perPersonVentilationRateModeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::AirTerminal_SingleDuct_MixerFields::PerPersonVentilationRateMode);
  }

  bool AirTerminalSingleDuctInletSideMixer::addToNode(Node& node) {
    return getImpl<detail::AirTerminalSingleDuctInletSideMixer_Impl>()->addToNode(node);
  }

  std::string AirTerminalSingleDuctInletSideMixer::perPersonVentilationRateMode() const {
    return getImpl<detail::AirTerminalSingleDuctInletSideMixer_Impl>()->perPersonVentilationRateMode();
  }

  bool AirTerminalSingleDuctInletSideMixer::setPerPersonVentilationRateMode(const std::string& perPersonVentilationRateMode) {
    return getImpl<detail::AirTerminalSingleDuctInletSideMixer_Impl>()->setPerPersonVentilationRateMode(perPersonVentilationRateMode);
  }

  unsigned AirTerminalSingleDuctInletSideMixer::secondaryAirInletPort() const {
    return getImpl<detail::AirTerminalSingleDuctInletSideMixer_Impl>()->secondaryAirInletPort();
  }

  boost::optional<Node> AirTerminalSingleDuctInletSideMixer::secondaryAirInletNode() const {
    return getImpl<detail::AirTerminalSingleDuctInletSideMixer_Impl>()->secondaryAirInletNode();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    boost::optional<ZoneHVACAirDistributionUnit> AirTerminalSingleDuctInletSideMixer_Impl::zoneHVACAirDistributionUnit() const {
      for (const auto& source : getObject<ModelObject>().getSources(openstudio::IddObjectType::ZoneHVAC_AirDistributionUnit)) {
        if (auto adu = source.optionalCast<openstudio::epmodel::ZoneHVACAirDistributionUnit>()) {
          return adu;
        }
      }
      return boost::none;
    }

    std::vector<openstudio::IdfObject> AirTerminalSingleDuctInletSideMixer_Impl::remove() {
      const auto thisObject = getObject<openstudio::epmodel::ModelObject>();
      const auto inletNode = inletModelObject();
      const auto outletNode = outletModelObject();
      const auto thermalZone = thermalZoneContainingTerminal(model(), thisObject);
      const auto adu = zoneHVACAirDistributionUnit();
      const auto outletNodeAsNode = outletNode ? outletNode->optionalCast<openstudio::epmodel::Node>() : boost::optional<openstudio::epmodel::Node>{};
      const auto downstreamZoneHVAC =
        outletNodeAsNode ? downstreamZoneHVACForTerminalOutlet(model(), *outletNodeAsNode) : boost::optional<ZoneHVACComponent>{};
      const bool needsLoopCleanup = inletNode || outletNode || thermalZone || adu || downstreamZoneHVAC;

      if (needsLoopCleanup && !removeFromLoop()) {
        return {};
      }
      return HVACComponent_Impl::remove();
    }

    bool AirTerminalSingleDuctInletSideMixer_Impl::removeFromLoop() {
      auto thisObject = getObject<openstudio::epmodel::ModelObject>();
      auto thermalZone = thermalZoneContainingTerminal(model(), thisObject);
      auto inletNode = inletModelObject();
      auto outletNode = outletModelObject();
      boost::optional<ZoneHVACComponent> downstreamZoneHVAC;
      boost::optional<ThermalZone> downstreamZone;

      if (auto outlet = outletNode ? outletNode->optionalCast<openstudio::epmodel::Node>() : boost::optional<openstudio::epmodel::Node>{}) {
        downstreamZoneHVAC = downstreamZoneHVACForTerminalOutlet(model(), *outlet);
        if (downstreamZoneHVAC) {
          downstreamZone = downstreamZoneHVAC->thermalZone();
        }
      }

      bool shouldRemoveTerminalInletNode = false;
      if (auto terminal = thisObject.optionalCast<openstudio::epmodel::HVACComponent>()) {
        if (auto airLoop = terminal->airLoopHVAC()) {
          if (inletNode && outletNode) {
            const auto splitter = airLoop->zoneSplitter();
            const auto mixer = airLoop->zoneMixer();
            const auto splitterOutlets = splitter.outletModelObjects();
            const auto splitterIt = std::ranges::find(splitterOutlets, *inletNode);
            if (splitterIt != splitterOutlets.end()) {
              const auto splitterBranchIndex = static_cast<unsigned>(std::distance(splitterOutlets.begin(), splitterIt));
              shouldRemoveTerminalInletNode =
                (splitter.outletModelObject(splitterBranchIndex) == *inletNode) && (mixer.inletModelObject(splitterBranchIndex) == *outletNode);
            }
          }
        }
      }

      bool removedFromAirLoop = false;
      if (inletNode && outletNode) {
        if (!StraightComponent_Impl::removeFromLoop()) {
          return false;
        }
        removedFromAirLoop = true;
      }

      if (thermalZone && !unregisterTerminalFromThermalZone(thisObject, *thermalZone)) {
        return false;
      }

      bool cleanedADU = false;
      if (auto adu = zoneHVACAirDistributionUnit()) {
        if (!adu->setPointer(openstudio::ZoneHVAC_AirDistributionUnitFields::AirDistributionUnitOutletNodeName, openstudio::Handle())) {
          return false;
        }
        if (!adu->setString(openstudio::ZoneHVAC_AirDistributionUnitFields::AirTerminalObjectType, "")) {
          return false;
        }
        if (!adu->setPointer(openstudio::ZoneHVAC_AirDistributionUnitFields::AirTerminalName, openstudio::Handle())) {
          return false;
        }
        cleanedADU = true;
      }

      setPointer(inletPort(), openstudio::Handle(), false);
      setPointer(outletPort(), openstudio::Handle(), false);

      if (shouldRemoveTerminalInletNode) {
        if (auto node = inletNode->optionalCast<openstudio::epmodel::Node>()) {
          node->remove();
        }
      }

      if (downstreamZoneHVAC && downstreamZone) {
        downstreamZoneHVAC->removeFromThermalZone();
        if (!downstreamZoneHVAC->addToThermalZone(*downstreamZone)) {
          return false;
        }
      }

      return removedFromAirLoop || static_cast<bool>(thermalZone) || cleanedADU || static_cast<bool>(downstreamZoneHVAC);
    }

    bool AirTerminalSingleDuctInletSideMixer_Impl::addToNode(Node& node) {
      if (node.model() != model()) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctInletSideMixer",
                 "addToNode requires a node in the same model as the inlet-side mixer terminal.");
        return false;
      }

      if (getObject<openstudio::epmodel::HVACComponent>().loop()) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctInletSideMixer",
                 "Refusing to add an already-connected inlet-side mixer terminal to node '" << node.nameString() << "'.");
        return false;
      }

      auto airLoop = node.airLoopHVAC();
      if (!airLoop) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctInletSideMixer",
                 "addToNode requires a node that resolves to an AirLoopHVAC context.");
        return false;
      }

      auto zoneSplitter = airLoop->zoneSplitter();
      auto zoneMixer = airLoop->zoneMixer();
      const auto thisNode = node.cast<ModelObject>();
      const auto splitterOutlets = zoneSplitter.outletModelObjects();
      const auto splitterIt = std::ranges::find(splitterOutlets, thisNode);
      if (splitterIt == splitterOutlets.end()) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctInletSideMixer",
                 "addToNode requires the drop node to be a ZoneSplitter outlet node for the target AirLoopHVAC.");
        return false;
      }
      const auto splitterBranchIndex = static_cast<unsigned>(std::distance(splitterOutlets.begin(), splitterIt));

      auto mixerInlet = zoneMixer.inletModelObject(splitterBranchIndex);
      if (!mixerInlet) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctInletSideMixer",
                 "addToNode requires a corresponding ZoneMixer inlet for ZoneSplitter branch index " << splitterBranchIndex << ".");
        return false;
      }
      auto thermalZone = owningThermalZoneForBranchNode(model(), node);
      if ((*mixerInlet != thisNode) && !isServedZoneReturnNode(thermalZone, *mixerInlet)) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctInletSideMixer",
                 "addToNode requires the drop node to either feed the ZoneMixer directly or be the served zone inlet node.");
        return false;
      }

      auto thisObject = getObject<ModelObject>();
      if (!thisObject.name()) {
        thisObject.createName();
        if (!thisObject.name()) {
          return false;
        }
      }

      const std::string inletNodeName = node.nameString() + " - " + thisObject.nameString() + " Inlet Node";
      auto inletNode = model().getOrCreateTransientByName<Node>(inletNodeName);
      if (!zoneSplitter.setOutletModelObject(splitterBranchIndex, inletNode.cast<ModelObject>())) {
        return false;
      }

      if (!setPointer(inletPort(), inletNode.handle(), false)) {
        return false;
      }

      if (!setPointer(outletPort(), node.handle(), false)) {
        return false;
      }

      if (auto adu = zoneHVACAirDistributionUnit()) {
        if (!adu->getImpl<detail::ZoneHVACAirDistributionUnit_Impl>()->setOutletNode(node)) {
          return false;
        }
      }

      if (thermalZone) {
        if (!registerTerminalWithThermalZone(thisObject, *thermalZone)) {
          LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctInletSideMixer",
                   "addToNode failed to register the inlet-side mixer terminal with the owning thermal zone.");
          return false;
        }
      }

      return true;
    }

    std::string AirTerminalSingleDuctInletSideMixer_Impl::perPersonVentilationRateMode() const {
      const auto value = getString(openstudio::AirTerminal_SingleDuct_MixerFields::PerPersonVentilationRateMode, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirTerminalSingleDuctInletSideMixer_Impl::setPerPersonVentilationRateMode(const std::string& perPersonVentilationRateMode) {
      return setString(openstudio::AirTerminal_SingleDuct_MixerFields::PerPersonVentilationRateMode, perPersonVentilationRateMode);
    }

    std::vector<std::string> AirTerminalSingleDuctInletSideMixer_Impl::perPersonVentilationRateModeValues() const {
      return AirTerminalSingleDuctInletSideMixer::perPersonVentilationRateModeValues();
    }

    unsigned AirTerminalSingleDuctInletSideMixer_Impl::inletPort() const {
      return openstudio::AirTerminal_SingleDuct_MixerFields::MixerPrimaryAirInletNodeName;
    }

    unsigned AirTerminalSingleDuctInletSideMixer_Impl::outletPort() const {
      return openstudio::AirTerminal_SingleDuct_MixerFields::MixerOutletNodeName;
    }

    unsigned AirTerminalSingleDuctInletSideMixer_Impl::secondaryAirInletPort() const {
      return openstudio::AirTerminal_SingleDuct_MixerFields::MixerSecondaryAirInletNodeName;
    }

    boost::optional<Node> AirTerminalSingleDuctInletSideMixer_Impl::secondaryAirInletNode() const {
      return getObject<ModelObject>().getModelObjectTarget<Node>(secondaryAirInletPort());
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
