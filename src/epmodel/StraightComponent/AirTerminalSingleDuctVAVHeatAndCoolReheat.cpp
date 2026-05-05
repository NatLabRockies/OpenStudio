/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/AirTerminalSingleDuctVAVHeatAndCoolReheat.hpp"
#include "StraightComponent/AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl.hpp"

#include "HVACComponent.hpp"
#include "HVACComponent/ThermalZone.hpp"
#include "HVACComponent/ThermalZone_Impl.hpp"
#include "Loop/AirLoopHVAC.hpp"
#include "Loop/PlantLoop.hpp"
#include "Mixer/AirLoopHVACZoneMixer.hpp"
#include "Model.hpp"
#include "ModelObject.hpp"
#include "ModelObject/ZoneHVACAirDistributionUnit.hpp"
#include "ModelObject/ZoneHVACAirDistributionUnit_Impl.hpp"
#include "ModelObject/ZoneHVACEquipmentConnections.hpp"
#include "ModelObject/ZoneHVACEquipmentConnections_Impl.hpp"
#include "ModelObject/ZoneHVACEquipmentList.hpp"
#include "ModelObject/ZoneHVACEquipmentList_Impl.hpp"
#include "Node.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"
#include "Splitter/AirLoopHVACZoneSplitter.hpp"

#include <algorithm>
#include <utilities/core/Assert.hpp>
#include <utilities/core/Logger.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/AirTerminal_SingleDuct_VAV_HeatAndCool_Reheat_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/ZoneHVAC_AirDistributionUnit_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  namespace {

    void applyConstructorDefaults(AirTerminalSingleDuctVAVHeatAndCoolReheat& terminal) {
      terminal.autosizeMaximumAirFlowRate();
      OS_ASSERT(terminal.setZoneMinimumAirFlowFraction(0.0));
      terminal.autosizeMaximumHotWaterorSteamFlowRate();
      OS_ASSERT(terminal.setMinimumHotWaterorSteamFlowRate(0.0));
      OS_ASSERT(terminal.setConvergenceTolerance(0.001));
      OS_ASSERT(terminal.setMaximumReheatAirTemperature(1000.0));
    }

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

  }  // namespace

  AirTerminalSingleDuctVAVHeatAndCoolReheat::AirTerminalSingleDuctVAVHeatAndCoolReheat(const Model& model)
    : StraightComponent(AirTerminalSingleDuctVAVHeatAndCoolReheat::iddObjectType(), model) {
    applyConstructorDefaults(*this);
  }

  AirTerminalSingleDuctVAVHeatAndCoolReheat::AirTerminalSingleDuctVAVHeatAndCoolReheat(
    std::shared_ptr<detail::AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl> impl)
    : StraightComponent(std::move(impl)) {}

  IddObjectType AirTerminalSingleDuctVAVHeatAndCoolReheat::iddObjectType() {
    return IddObjectType::AirTerminal_SingleDuct_VAV_HeatAndCool_Reheat;
  }

  bool AirTerminalSingleDuctVAVHeatAndCoolReheat::addToNode(Node& node) {
    return getImpl<detail::AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl>()->addToNode(node);
  }

  boost::optional<Schedule> AirTerminalSingleDuctVAVHeatAndCoolReheat::availabilitySchedule() const {
    return getImpl<detail::AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl>()->availabilitySchedule();
  }

  bool AirTerminalSingleDuctVAVHeatAndCoolReheat::setAvailabilitySchedule(Schedule& schedule) {
    return getImpl<detail::AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl>()->setAvailabilitySchedule(schedule);
  }

  void AirTerminalSingleDuctVAVHeatAndCoolReheat::resetAvailabilitySchedule() {
    getImpl<detail::AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl>()->resetAvailabilitySchedule();
  }

  HVACComponent AirTerminalSingleDuctVAVHeatAndCoolReheat::reheatCoil() const {
    return getImpl<detail::AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl>()->reheatCoil();
  }

  bool AirTerminalSingleDuctVAVHeatAndCoolReheat::setReheatCoil(const HVACComponent& heatingCoilName) {
    return getImpl<detail::AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl>()->setReheatCoil(heatingCoilName);
  }

  boost::optional<Schedule> AirTerminalSingleDuctVAVHeatAndCoolReheat::minimumAirFlowTurndownSchedule() const {
    return getImpl<detail::AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl>()->minimumAirFlowTurndownSchedule();
  }

  bool AirTerminalSingleDuctVAVHeatAndCoolReheat::setMinimumAirFlowTurndownSchedule(Schedule& schedule) {
    return getImpl<detail::AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl>()->setMinimumAirFlowTurndownSchedule(schedule);
  }

  void AirTerminalSingleDuctVAVHeatAndCoolReheat::resetMinimumAirFlowTurndownSchedule() {
    getImpl<detail::AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl>()->resetMinimumAirFlowTurndownSchedule();
  }

  boost::optional<double> AirTerminalSingleDuctVAVHeatAndCoolReheat::maximumAirFlowRate() const {
    return getImpl<detail::AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl>()->maximumAirFlowRate();
  }

  bool AirTerminalSingleDuctVAVHeatAndCoolReheat::isMaximumAirFlowRateAutosized() const {
    return getImpl<detail::AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl>()->isMaximumAirFlowRateAutosized();
  }

  bool AirTerminalSingleDuctVAVHeatAndCoolReheat::setMaximumAirFlowRate(double maximumAirFlowRate) {
    return getImpl<detail::AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl>()->setMaximumAirFlowRate(maximumAirFlowRate);
  }

  void AirTerminalSingleDuctVAVHeatAndCoolReheat::autosizeMaximumAirFlowRate() {
    getImpl<detail::AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl>()->autosizeMaximumAirFlowRate();
  }

  double AirTerminalSingleDuctVAVHeatAndCoolReheat::zoneMinimumAirFlowFraction() const {
    return getImpl<detail::AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl>()->zoneMinimumAirFlowFraction();
  }

  bool AirTerminalSingleDuctVAVHeatAndCoolReheat::setZoneMinimumAirFlowFraction(double zoneMinimumAirFlowFraction) {
    return getImpl<detail::AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl>()->setZoneMinimumAirFlowFraction(zoneMinimumAirFlowFraction);
  }

  boost::optional<double> AirTerminalSingleDuctVAVHeatAndCoolReheat::maximumHotWaterorSteamFlowRate() const {
    return getImpl<detail::AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl>()->maximumHotWaterorSteamFlowRate();
  }

  bool AirTerminalSingleDuctVAVHeatAndCoolReheat::isMaximumHotWaterorSteamFlowRateAutosized() const {
    return getImpl<detail::AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl>()->isMaximumHotWaterorSteamFlowRateAutosized();
  }

  bool AirTerminalSingleDuctVAVHeatAndCoolReheat::setMaximumHotWaterorSteamFlowRate(double maximumHotWaterorSteamFlowRate) {
    return getImpl<detail::AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl>()->setMaximumHotWaterorSteamFlowRate(maximumHotWaterorSteamFlowRate);
  }

  void AirTerminalSingleDuctVAVHeatAndCoolReheat::autosizeMaximumHotWaterorSteamFlowRate() {
    getImpl<detail::AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl>()->autosizeMaximumHotWaterorSteamFlowRate();
  }

  double AirTerminalSingleDuctVAVHeatAndCoolReheat::minimumHotWaterorSteamFlowRate() const {
    return getImpl<detail::AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl>()->minimumHotWaterorSteamFlowRate();
  }

  bool AirTerminalSingleDuctVAVHeatAndCoolReheat::setMinimumHotWaterorSteamFlowRate(double minimumHotWaterorSteamFlowRate) {
    return getImpl<detail::AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl>()->setMinimumHotWaterorSteamFlowRate(minimumHotWaterorSteamFlowRate);
  }

  double AirTerminalSingleDuctVAVHeatAndCoolReheat::convergenceTolerance() const {
    return getImpl<detail::AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl>()->convergenceTolerance();
  }

  bool AirTerminalSingleDuctVAVHeatAndCoolReheat::setConvergenceTolerance(double convergenceTolerance) {
    return getImpl<detail::AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl>()->setConvergenceTolerance(convergenceTolerance);
  }

  double AirTerminalSingleDuctVAVHeatAndCoolReheat::maximumReheatAirTemperature() const {
    return getImpl<detail::AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl>()->maximumReheatAirTemperature();
  }

  bool AirTerminalSingleDuctVAVHeatAndCoolReheat::setMaximumReheatAirTemperature(double maximumReheatAirTemperature) {
    return getImpl<detail::AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl>()->setMaximumReheatAirTemperature(maximumReheatAirTemperature);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    boost::optional<ZoneHVACAirDistributionUnit> AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl::zoneHVACAirDistributionUnit() const {
      auto terminal = getObject<openstudio::epmodel::ModelObject>();
      for (const auto& source : terminal.getSources(openstudio::IddObjectType::ZoneHVAC_AirDistributionUnit)) {
        if (auto adu = source.optionalCast<openstudio::epmodel::ZoneHVACAirDistributionUnit>()) {
          return adu;
        }
      }
      return boost::none;
    }

    std::vector<ModelObject> AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl::children() const {
      std::vector<ModelObject> result;
      auto coil =
        getObject<ModelObject>().getModelObjectTarget<HVACComponent>(openstudio::AirTerminal_SingleDuct_VAV_HeatAndCool_ReheatFields::ReheatCoilName);
      if (coil) {
        result.push_back(*coil);
      }
      return result;
    }

    std::vector<openstudio::IdfObject> AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl::remove() {
      auto thisObject = getObject<openstudio::epmodel::ModelObject>();
      auto coil = thisObject.getModelObjectTarget<openstudio::epmodel::HVACComponent>(
        openstudio::AirTerminal_SingleDuct_VAV_HeatAndCool_ReheatFields::ReheatCoilName);

      removeFromLoop();

      if (coil) {
        if (auto plantLoop = coil->plantLoop()) {
          plantLoop->removeDemandBranchWithComponent(*coil);
        }
      }

      return HVACComponent_Impl::remove();
    }

    bool AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl::removeFromLoop() {
      auto thisObject = getObject<openstudio::epmodel::ModelObject>();
      auto thermalZone = thermalZoneContainingTerminal(model(), thisObject);
      auto inletNode = inletModelObject();
      auto outletNode = outletModelObject();
      auto coil = thisObject.getModelObjectTarget<openstudio::epmodel::HVACComponent>(
        openstudio::AirTerminal_SingleDuct_VAV_HeatAndCool_ReheatFields::ReheatCoilName);
      auto plantLoop = coil ? coil->plantLoop() : boost::optional<openstudio::epmodel::PlantLoop>{};

      bool shouldRemoveTerminalInletNode = false;
      if (auto terminal = thisObject.optionalCast<openstudio::epmodel::HVACComponent>()) {
        if (auto airLoop = terminal->airLoopHVAC()) {
          if (inletNode && outletNode) {
            const auto splitter = airLoop->zoneSplitter();
            const auto mixer = airLoop->zoneMixer();
            const auto splitterBranchIndex = splitter.branchIndexForOutletModelObject(*inletNode);
            shouldRemoveTerminalInletNode =
              (splitter.outletModelObject(splitterBranchIndex) == *inletNode) && (mixer.inletModelObject(splitterBranchIndex) == *outletNode);
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

      if (plantLoop && coil && !plantLoop->removeDemandBranchWithComponent(*coil)) {
        return false;
      }

      return removedFromAirLoop || static_cast<bool>(thermalZone) || cleanedADU || static_cast<bool>(plantLoop);
    }

    bool AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl::addToNode(Node& node) {
      return addToNode(node, AddToNodeFailureStage::None);
    }

    bool AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl::addToNode(Node& node, AddToNodeFailureStage failureStage) {
      if (node.model() != model()) {
        return false;
      }

      if (getObject<openstudio::epmodel::HVACComponent>().loop()) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctVAVHeatAndCoolReheat",
                 "Refusing to add an already-connected terminal to node '" << node.nameString() << "'.");
        return false;
      }

      auto airLoop = node.airLoopHVAC();
      if (!airLoop) {
        return false;
      }

      auto zoneSplitter = airLoop->zoneSplitter();
      auto zoneMixer = airLoop->zoneMixer();
      const auto thisNode = node.cast<ModelObject>();
      const auto splitterOutlets = zoneSplitter.outletModelObjects();
      const auto splitterIt = std::ranges::find(splitterOutlets, thisNode);
      if (splitterIt == splitterOutlets.end()) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctVAVHeatAndCoolReheat",
                 "addToNode requires the drop node to be a ZoneSplitter outlet node for the target AirLoopHVAC.");
        return false;
      }
      const auto splitterBranchIndex = static_cast<unsigned>(std::distance(splitterOutlets.begin(), splitterIt));

      auto mixerInlet = zoneMixer.inletModelObject(splitterBranchIndex);
      if (!mixerInlet) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctVAVHeatAndCoolReheat",
                 "addToNode requires a corresponding ZoneMixer inlet for ZoneSplitter branch index " << splitterBranchIndex << ".");
        return false;
      }
      auto thermalZone = owningThermalZoneForBranchNode(model(), node);
      if ((*mixerInlet != thisNode) && !isServedZoneReturnNode(thermalZone, *mixerInlet)) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctVAVHeatAndCoolReheat",
                 "addToNode requires the drop node to either feed the ZoneMixer directly or be the served zone inlet node.");
        return false;
      }

      auto thisObject = getObject<openstudio::epmodel::ModelObject>();
      if (!thisObject.name()) {
        thisObject.createName();
        if (!thisObject.name()) {
          return false;
        }
      }

      auto adu = zoneHVACAirDistributionUnit();
      const auto previousADUOutletNode = adu ? adu->outletNode() : boost::optional<Node>{};

      const std::string inletNodeName = node.nameString() + " - " + thisObject.nameString() + " Inlet Node";
      auto inletNode = model().getOrCreateTransientByName<openstudio::epmodel::Node>(inletNodeName);

      bool splitterRewired = false;
      bool inletAssigned = false;
      bool outletAssigned = false;
      bool aduUpdated = false;
      bool zoneRegistered = false;

      const auto rollback = [&]() {
        if (zoneRegistered && thermalZone) {
          (void)unregisterTerminalFromThermalZone(thisObject, *thermalZone);
        }
        if (adu && aduUpdated) {
          if (previousADUOutletNode) {
            (void)adu->getImpl<openstudio::epmodel::detail::ZoneHVACAirDistributionUnit_Impl>()->setOutletNode(*previousADUOutletNode);
          } else {
            (void)adu->setPointer(openstudio::ZoneHVAC_AirDistributionUnitFields::AirDistributionUnitOutletNodeName, openstudio::Handle());
          }
        }
        if (outletAssigned) {
          (void)setPointer(outletPort(), openstudio::Handle(), false);
        }
        if (inletAssigned) {
          (void)setPointer(inletPort(), openstudio::Handle(), false);
        }
        if (splitterRewired) {
          (void)zoneSplitter.setOutletModelObject(splitterBranchIndex, thisNode);
        }
        if (inletNode.sources().empty()) {
          inletNode.remove();
        }
      };

      if (!zoneSplitter.setOutletModelObject(splitterBranchIndex, inletNode.cast<ModelObject>())) {
        return false;
      }
      splitterRewired = true;

      if (!setPointer(inletPort(), inletNode.handle(), false)) {
        rollback();
        return false;
      }
      inletAssigned = true;

      if (!setPointer(outletPort(), node.handle(), false)) {
        rollback();
        return false;
      }
      outletAssigned = true;

      if (adu) {
        if (!adu->getImpl<openstudio::epmodel::detail::ZoneHVACAirDistributionUnit_Impl>()->setOutletNode(node)) {
          rollback();
          return false;
        }
        aduUpdated = true;
      }

      if (failureStage == AddToNodeFailureStage::AfterADUUpdateBeforeZoneRegistration) {
        rollback();
        return false;
      }

      if (thermalZone) {
        if (!registerTerminalWithThermalZone(thisObject, *thermalZone)) {
          rollback();
          return false;
        }
        zoneRegistered = true;
      }

      return true;
    }

    boost::optional<Schedule> AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl::availabilitySchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(
        openstudio::AirTerminal_SingleDuct_VAV_HeatAndCool_ReheatFields::AvailabilityScheduleName);
    }

    bool AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl::setAvailabilitySchedule(Schedule& schedule) {
      return ModelObject_Impl::setSchedule(openstudio::AirTerminal_SingleDuct_VAV_HeatAndCool_ReheatFields::AvailabilityScheduleName,
                                           "AirTerminalSingleDuctVAVHeatAndCoolReheat", "Availability", schedule);
    }

    void AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl::resetAvailabilitySchedule() {
      OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_VAV_HeatAndCool_ReheatFields::AvailabilityScheduleName, ""));
    }

    HVACComponent AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl::reheatCoil() const {
      auto coil =
        getObject<ModelObject>().getModelObjectTarget<HVACComponent>(openstudio::AirTerminal_SingleDuct_VAV_HeatAndCool_ReheatFields::ReheatCoilName);
      OS_ASSERT(coil);
      return *coil;
    }

    bool AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl::setReheatCoil(const HVACComponent& heatingCoilName) {
      if (heatingCoilName.model() != model()) {
        return false;
      }
      return setPointer(openstudio::AirTerminal_SingleDuct_VAV_HeatAndCool_ReheatFields::ReheatCoilName, heatingCoilName.handle(), false);
    }

    boost::optional<Schedule> AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl::minimumAirFlowTurndownSchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(
        openstudio::AirTerminal_SingleDuct_VAV_HeatAndCool_ReheatFields::MinimumAirFlowTurndownScheduleName);
    }

    bool AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl::setMinimumAirFlowTurndownSchedule(Schedule& schedule) {
      return ModelObject_Impl::setSchedule(openstudio::AirTerminal_SingleDuct_VAV_HeatAndCool_ReheatFields::MinimumAirFlowTurndownScheduleName,
                                           "AirTerminalSingleDuctVAVHeatAndCoolReheat", "Minimum Air Flow Turndown", schedule);
    }

    void AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl::resetMinimumAirFlowTurndownSchedule() {
      OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_VAV_HeatAndCool_ReheatFields::MinimumAirFlowTurndownScheduleName, ""));
    }

    boost::optional<double> AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl::maximumAirFlowRate() const {
      return getDouble(openstudio::AirTerminal_SingleDuct_VAV_HeatAndCool_ReheatFields::MaximumAirFlowRate, true);
    }

    bool AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl::isMaximumAirFlowRateAutosized() const {
      if (auto value = getString(openstudio::AirTerminal_SingleDuct_VAV_HeatAndCool_ReheatFields::MaximumAirFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl::setMaximumAirFlowRate(double maximumAirFlowRate) {
      return setDouble(openstudio::AirTerminal_SingleDuct_VAV_HeatAndCool_ReheatFields::MaximumAirFlowRate, maximumAirFlowRate);
    }

    void AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl::autosizeMaximumAirFlowRate() {
      OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_VAV_HeatAndCool_ReheatFields::MaximumAirFlowRate, "autosize"));
    }

    double AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl::zoneMinimumAirFlowFraction() const {
      const auto value = getDouble(openstudio::AirTerminal_SingleDuct_VAV_HeatAndCool_ReheatFields::ZoneMinimumAirFlowFraction, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl::setZoneMinimumAirFlowFraction(double zoneMinimumAirFlowFraction) {
      return setDouble(openstudio::AirTerminal_SingleDuct_VAV_HeatAndCool_ReheatFields::ZoneMinimumAirFlowFraction, zoneMinimumAirFlowFraction);
    }

    boost::optional<double> AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl::maximumHotWaterorSteamFlowRate() const {
      return getDouble(openstudio::AirTerminal_SingleDuct_VAV_HeatAndCool_ReheatFields::MaximumHotWaterorSteamFlowRate, true);
    }

    bool AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl::isMaximumHotWaterorSteamFlowRateAutosized() const {
      if (auto value = getString(openstudio::AirTerminal_SingleDuct_VAV_HeatAndCool_ReheatFields::MaximumHotWaterorSteamFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl::setMaximumHotWaterorSteamFlowRate(double maximumHotWaterorSteamFlowRate) {
      return setDouble(openstudio::AirTerminal_SingleDuct_VAV_HeatAndCool_ReheatFields::MaximumHotWaterorSteamFlowRate,
                       maximumHotWaterorSteamFlowRate);
    }

    void AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl::autosizeMaximumHotWaterorSteamFlowRate() {
      OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_VAV_HeatAndCool_ReheatFields::MaximumHotWaterorSteamFlowRate, "autosize"));
    }

    double AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl::minimumHotWaterorSteamFlowRate() const {
      const auto value = getDouble(openstudio::AirTerminal_SingleDuct_VAV_HeatAndCool_ReheatFields::MinimumHotWaterorSteamFlowRate, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl::setMinimumHotWaterorSteamFlowRate(double minimumHotWaterorSteamFlowRate) {
      return setDouble(openstudio::AirTerminal_SingleDuct_VAV_HeatAndCool_ReheatFields::MinimumHotWaterorSteamFlowRate,
                       minimumHotWaterorSteamFlowRate);
    }

    double AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl::convergenceTolerance() const {
      const auto value = getDouble(openstudio::AirTerminal_SingleDuct_VAV_HeatAndCool_ReheatFields::ConvergenceTolerance, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl::setConvergenceTolerance(double convergenceTolerance) {
      return setDouble(openstudio::AirTerminal_SingleDuct_VAV_HeatAndCool_ReheatFields::ConvergenceTolerance, convergenceTolerance);
    }

    double AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl::maximumReheatAirTemperature() const {
      const auto value = getDouble(openstudio::AirTerminal_SingleDuct_VAV_HeatAndCool_ReheatFields::MaximumReheatAirTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl::setMaximumReheatAirTemperature(double maximumReheatAirTemperature) {
      return setDouble(openstudio::AirTerminal_SingleDuct_VAV_HeatAndCool_ReheatFields::MaximumReheatAirTemperature, maximumReheatAirTemperature);
    }

    unsigned AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl::inletPort() const {
      return openstudio::AirTerminal_SingleDuct_VAV_HeatAndCool_ReheatFields::AirInletNodeName;
    }

    unsigned AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl::outletPort() const {
      return openstudio::AirTerminal_SingleDuct_VAV_HeatAndCool_ReheatFields::AirOutletNodeName;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
