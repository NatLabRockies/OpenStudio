/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/AirTerminalSingleDuctInletSideMixer.hpp"
#include "StraightComponent/AirTerminalSingleDuctInletSideMixer_Impl.hpp"
#include "Loop/AirLoopHVAC_Impl.hpp"

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

    boost::optional<ThermalZone> thermalZoneContainingTerminal(const Model& model, const ModelObject& terminal) {
      for (const auto& zone : model.getConcreteModelObjects<ThermalZone>()) {
        const auto equipment = zone.equipment();
        if (std::ranges::find(equipment, terminal) != equipment.end()) {
          return zone;
        }
      }
      return boost::none;
    }

    bool hasInletSideConnectionType(const ModelObject& terminal) {
      const auto connectionType = terminal.getString(openstudio::AirTerminal_SingleDuct_MixerFields::MixerConnectionType, true);
      return connectionType && openstudio::istringEqual(*connectionType, "InletSide");
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

    class DownstreamZoneHVACDetachmentGuard
    {
     public:
      DownstreamZoneHVACDetachmentGuard(boost::optional<ZoneHVACComponent> component, boost::optional<ThermalZone> zone)
        : m_component(std::move(component)), m_zone(std::move(zone)) {}

      DownstreamZoneHVACDetachmentGuard(const DownstreamZoneHVACDetachmentGuard&) = delete;
      DownstreamZoneHVACDetachmentGuard& operator=(const DownstreamZoneHVACDetachmentGuard&) = delete;
      DownstreamZoneHVACDetachmentGuard(DownstreamZoneHVACDetachmentGuard&&) = delete;
      DownstreamZoneHVACDetachmentGuard& operator=(DownstreamZoneHVACDetachmentGuard&&) = delete;

      ~DownstreamZoneHVACDetachmentGuard() {
        if (m_detached && !restore()) {
          LOG_FREE(Error, "openstudio.epmodel.AirTerminalSingleDuctInletSideMixer",
                   "Failed to restore downstream zone HVAC equipment while unwinding inlet-side mixer removal.");
        }
      }

      bool detach() {
        if (m_component && m_zone) {
          // The downstream component must still be able to discover the mixer
          // while clearing its secondary-air and ZoneHVAC-unit fields.
          m_detached = true;
          m_component->removeFromThermalZone();
          const auto currentZone = m_component->thermalZone();
          const auto equipment = m_zone->equipment();
          return !currentZone && (std::ranges::find(equipment, m_component->cast<ModelObject>()) == equipment.end());
        }
        return true;
      }

      bool restore() {
        if (!m_detached) {
          return true;
        }
        const auto currentZone = m_component->thermalZone();
        const auto equipment = m_zone->equipment();
        const bool registered = std::ranges::find(equipment, m_component->cast<ModelObject>()) != equipment.end();
        if (currentZone && (*currentZone == *m_zone) && registered) {
          m_detached = false;
          return true;
        }
        if (currentZone && (*currentZone != *m_zone)) {
          return false;
        }
        m_component->removeFromThermalZone();
        if (!m_component->addToThermalZone(*m_zone)) {
          return false;
        }
        const auto restoredZone = m_component->thermalZone();
        const auto restoredEquipment = m_zone->equipment();
        if (!restoredZone || (*restoredZone != *m_zone)
            || (std::ranges::find(restoredEquipment, m_component->cast<ModelObject>()) == restoredEquipment.end())) {
          return false;
        }
        m_detached = false;
        return true;
      }

     private:
      boost::optional<ZoneHVACComponent> m_component;
      boost::optional<ThermalZone> m_zone;
      bool m_detached = false;
    };

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
      if (!hasInletSideConnectionType(thisObject)) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctInletSideMixer",
                 "Refusing inlet-side removal semantics for AirTerminal:SingleDuct:Mixer '" << thisObject.nameString()
                                                                                            << "' because it is not InletSide.");
        return {};
      }
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
      if (!hasInletSideConnectionType(thisObject)) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctInletSideMixer",
                 "Refusing inlet-side loop removal semantics for AirTerminal:SingleDuct:Mixer '" << thisObject.nameString()
                                                                                                 << "' because it is not InletSide.");
        return false;
      }
      auto outletNode = outletModelObject();
      boost::optional<ZoneHVACComponent> downstreamZoneHVAC;
      boost::optional<ThermalZone> downstreamZone;

      if (auto outlet = outletNode ? outletNode->optionalCast<openstudio::epmodel::Node>() : boost::optional<openstudio::epmodel::Node>{}) {
        downstreamZoneHVAC = downstreamZoneHVACForTerminalOutlet(model(), *outlet);
        if (downstreamZoneHVAC) {
          downstreamZone = downstreamZoneHVAC->thermalZone();
        }
      }

      auto terminal = thisObject.cast<StraightComponent>();
      const bool terminalHasTopology = AirLoopHVAC_Impl::SingleDuctTerminalRemovalPlan::hasTopology(terminal);
      auto removalPlan = terminalHasTopology ? AirLoopHVAC_Impl::SingleDuctTerminalRemovalPlan::prepare(terminal) : nullptr;
      if (terminalHasTopology && !removalPlan) {
        return false;
      }

      DownstreamZoneHVACDetachmentGuard downstreamGuard(downstreamZoneHVAC, downstreamZone);
      if (!downstreamGuard.detach()) {
        return false;
      }

      // Rehome the downstream zone equipment while terminal removal is still
      // entirely provisional. If this fallible step fails, the guard can
      // restore the original inlet-side relationship and the removal plan has
      // not crossed its commit barrier.
      if (!downstreamGuard.restore()) {
        return false;
      }

      if (removalPlan) {
        removalPlan->commit();
      }

      return terminalHasTopology || static_cast<bool>(downstreamZoneHVAC);
    }

    bool AirTerminalSingleDuctInletSideMixer_Impl::addToNode(Node& node) {
      if (!hasInletSideConnectionType(getObject<openstudio::epmodel::ModelObject>())) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctInletSideMixer",
                 "addToNode only supports AirTerminal:SingleDuct:Mixer objects with an InletSide connection type.");
        return false;
      }

      if (node.model() != model()) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctInletSideMixer",
                 "addToNode requires a node in the same model as the inlet-side mixer terminal.");
        return false;
      }

      auto thisObject = getObject<ModelObject>();
      auto terminal = thisObject.cast<StraightComponent>();
      auto plan = AirLoopHVAC_Impl::SingleDuctTerminalInsertionPlan::prepare(terminal, node);
      if (!plan) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctInletSideMixer",
                 "addToNode requires a terminal-free effective demand branch on the target AirLoopHVAC.");
        return false;
      }
      if (!plan->apply()) {
        return false;
      }
      plan->commit();
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

    void AirTerminalSingleDuctInletSideMixer_Impl::doCanonicalize(LoadContext& context) {
      StraightComponent_Impl::doCanonicalize(context);

      const auto connectionType = getString(openstudio::AirTerminal_SingleDuct_MixerFields::MixerConnectionType, true);
      if (!connectionType || connectionType->empty()) {
        OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_MixerFields::MixerConnectionType, "InletSide"));
        detail::addLoadInfo(context, "Set the required mixer connection type for AirTerminal:SingleDuct:Mixer '"
                                       + getObject<ModelObject>().nameString() + "' to InletSide.");
      }
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
