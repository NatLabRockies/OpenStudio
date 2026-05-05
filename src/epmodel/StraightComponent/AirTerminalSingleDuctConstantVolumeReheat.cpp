/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/AirTerminalSingleDuctConstantVolumeReheat.hpp"
#include "StraightComponent/AirTerminalSingleDuctConstantVolumeReheat_Impl.hpp"

#include "HVACComponent/ThermalZone.hpp"
#include "HVACComponent/ThermalZone_Impl.hpp"
#include "HVACComponent.hpp"
#include "Loop/AirLoopHVAC.hpp"
#include "Loop/PlantLoop.hpp"
#include "Model.hpp"
#include "ModelObject.hpp"
#include "ModelObject/ZoneHVACAirDistributionUnit.hpp"
#include "ModelObject/ZoneHVACAirDistributionUnit_Impl.hpp"
#include "ModelObject/ZoneHVACEquipmentConnections.hpp"
#include "ModelObject/ZoneHVACEquipmentConnections_Impl.hpp"
#include "ModelObject/ZoneHVACEquipmentList.hpp"
#include "ModelObject/ZoneHVACEquipmentList_Impl.hpp"
#include "Node.hpp"
#include "Mixer/AirLoopHVACZoneMixer.hpp"
#include "Splitter/AirLoopHVACZoneSplitter.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"

#include <algorithm>
#include <utilities/core/Assert.hpp>
#include <utilities/core/Logger.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/AirTerminal_SingleDuct_ConstantVolume_Reheat_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/ZoneHVAC_AirDistributionUnit_FieldEnums.hxx>
#include <utilities/idd/ZoneHVAC_EquipmentConnections_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  namespace {

    void applyConstructorDefaults(AirTerminalSingleDuctConstantVolumeReheat& terminal) {
      terminal.autosizeMaximumAirFlowRate();
      terminal.autosizeMaximumHotWaterorSteamFlowRate();
      OS_ASSERT(terminal.setMinimumHotWaterorSteamFlowRate(0.0));
      OS_ASSERT(terminal.setConvergenceTolerance(0.001));
      OS_ASSERT(terminal.setMaximumReheatAirTemperature(35.0));
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

  AirTerminalSingleDuctConstantVolumeReheat::AirTerminalSingleDuctConstantVolumeReheat(const Model& model)
    : StraightComponent(AirTerminalSingleDuctConstantVolumeReheat::iddObjectType(), model) {
    auto impl = getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>();
    OS_ASSERT(impl);
    detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
    impl->canonicalize(context);

    auto alwaysOn = model.alwaysOnDiscreteSchedule();
    OS_ASSERT(setAvailabilitySchedule(alwaysOn));
    applyConstructorDefaults(*this);
  }

  AirTerminalSingleDuctConstantVolumeReheat::AirTerminalSingleDuctConstantVolumeReheat(const Model& model, Schedule& availabilitySchedule,
                                                                                       HVACComponent& reheatCoil)
    : StraightComponent(AirTerminalSingleDuctConstantVolumeReheat::iddObjectType(), model) {
    auto impl = getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>();
    OS_ASSERT(impl);
    detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
    impl->canonicalize(context);

    OS_ASSERT(setAvailabilitySchedule(availabilitySchedule));
    OS_ASSERT(setReheatCoil(reheatCoil));
    applyConstructorDefaults(*this);
  }

  AirTerminalSingleDuctConstantVolumeReheat::AirTerminalSingleDuctConstantVolumeReheat(
    std::shared_ptr<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl> impl)
    : StraightComponent(std::move(impl)) {}

  IddObjectType AirTerminalSingleDuctConstantVolumeReheat::iddObjectType() {
    return IddObjectType::AirTerminal_SingleDuct_ConstantVolume_Reheat;
  }

  bool AirTerminalSingleDuctConstantVolumeReheat::addToNode(Node& node) {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->addToNode(node);
  }

  Schedule AirTerminalSingleDuctConstantVolumeReheat::availabilitySchedule() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->availabilitySchedule();
  }

  bool AirTerminalSingleDuctConstantVolumeReheat::setAvailabilitySchedule(Schedule& schedule) {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->setAvailabilitySchedule(schedule);
  }

  HVACComponent AirTerminalSingleDuctConstantVolumeReheat::reheatCoil() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->reheatCoil();
  }

  bool AirTerminalSingleDuctConstantVolumeReheat::setReheatCoil(const HVACComponent& coil) {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->setReheatCoil(coil);
  }

  void AirTerminalSingleDuctConstantVolumeReheat::resetReheatCoil() {
    getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->resetReheatCoil();
  }

  boost::optional<double> AirTerminalSingleDuctConstantVolumeReheat::maximumAirFlowRate() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->maximumAirFlowRate();
  }

  bool AirTerminalSingleDuctConstantVolumeReheat::isMaximumAirFlowRateAutosized() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->isMaximumAirFlowRateAutosized();
  }

  bool AirTerminalSingleDuctConstantVolumeReheat::setMaximumAirFlowRate(double maximumAirFlowRate) {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->setMaximumAirFlowRate(maximumAirFlowRate);
  }

  void AirTerminalSingleDuctConstantVolumeReheat::resetMaximumAirFlowRate() {
    getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->resetMaximumAirFlowRate();
  }

  void AirTerminalSingleDuctConstantVolumeReheat::autosizeMaximumAirFlowRate() {
    getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->autosizeMaximumAirFlowRate();
  }

  boost::optional<double> AirTerminalSingleDuctConstantVolumeReheat::maximumHotWaterorSteamFlowRate() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->maximumHotWaterorSteamFlowRate();
  }

  bool AirTerminalSingleDuctConstantVolumeReheat::isMaximumHotWaterorSteamFlowRateAutosized() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->isMaximumHotWaterorSteamFlowRateAutosized();
  }

  bool AirTerminalSingleDuctConstantVolumeReheat::setMaximumHotWaterorSteamFlowRate(double maximumHotWaterorSteamFlowRate) {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->setMaximumHotWaterorSteamFlowRate(maximumHotWaterorSteamFlowRate);
  }

  void AirTerminalSingleDuctConstantVolumeReheat::resetMaximumHotWaterorSteamFlowRate() {
    getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->resetMaximumHotWaterorSteamFlowRate();
  }

  void AirTerminalSingleDuctConstantVolumeReheat::autosizeMaximumHotWaterorSteamFlowRate() {
    getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->autosizeMaximumHotWaterorSteamFlowRate();
  }

  double AirTerminalSingleDuctConstantVolumeReheat::minimumHotWaterorSteamFlowRate() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->minimumHotWaterorSteamFlowRate();
  }

  bool AirTerminalSingleDuctConstantVolumeReheat::isMinimumHotWaterorSteamFlowRateDefaulted() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->isMinimumHotWaterorSteamFlowRateDefaulted();
  }

  bool AirTerminalSingleDuctConstantVolumeReheat::setMinimumHotWaterorSteamFlowRate(double minimumHotWaterorSteamFlowRate) {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->setMinimumHotWaterorSteamFlowRate(minimumHotWaterorSteamFlowRate);
  }

  void AirTerminalSingleDuctConstantVolumeReheat::resetMinimumHotWaterorSteamFlowRate() {
    getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->resetMinimumHotWaterorSteamFlowRate();
  }

  double AirTerminalSingleDuctConstantVolumeReheat::convergenceTolerance() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->convergenceTolerance();
  }

  bool AirTerminalSingleDuctConstantVolumeReheat::isConvergenceToleranceDefaulted() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->isConvergenceToleranceDefaulted();
  }

  bool AirTerminalSingleDuctConstantVolumeReheat::setConvergenceTolerance(double convergenceTolerance) {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->setConvergenceTolerance(convergenceTolerance);
  }

  void AirTerminalSingleDuctConstantVolumeReheat::resetConvergenceTolerance() {
    getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->resetConvergenceTolerance();
  }

  double AirTerminalSingleDuctConstantVolumeReheat::maximumReheatAirTemperature() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->maximumReheatAirTemperature();
  }

  bool AirTerminalSingleDuctConstantVolumeReheat::isMaximumReheatAirTemperatureDefaulted() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->isMaximumReheatAirTemperatureDefaulted();
  }

  bool AirTerminalSingleDuctConstantVolumeReheat::setMaximumReheatAirTemperature(double maximumReheatAirTemperature) {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->setMaximumReheatAirTemperature(maximumReheatAirTemperature);
  }

  void AirTerminalSingleDuctConstantVolumeReheat::resetMaximumReheatAirTemperature() {
    getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->resetMaximumReheatAirTemperature();
  }

  unsigned detail::AirTerminalSingleDuctConstantVolumeReheat_Impl::inletPort() const {
    return openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::AirInletNodeName;
  }

  unsigned detail::AirTerminalSingleDuctConstantVolumeReheat_Impl::outletPort() const {
    return openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::AirOutletNodeName;
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    boost::optional<ZoneHVACAirDistributionUnit> AirTerminalSingleDuctConstantVolumeReheat_Impl::zoneHVACAirDistributionUnit() const {
      auto terminal = getObject<openstudio::epmodel::ModelObject>();
      for (const auto& source : terminal.getSources(openstudio::IddObjectType::ZoneHVAC_AirDistributionUnit)) {
        if (auto adu = source.optionalCast<openstudio::epmodel::ZoneHVACAirDistributionUnit>()) {
          return adu;
        }
      }
      return boost::none;
    }

    std::vector<ModelObject> AirTerminalSingleDuctConstantVolumeReheat_Impl::children() const {
      std::vector<ModelObject> result;
      auto coil =
        getObject<ModelObject>().getModelObjectTarget<HVACComponent>(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::ReheatCoilName);
      if (coil) {
        result.push_back(*coil);
      }
      return result;
    }

    std::vector<openstudio::IdfObject> AirTerminalSingleDuctConstantVolumeReheat_Impl::remove() {
      auto thisObject = getObject<openstudio::epmodel::ModelObject>();
      auto coil = thisObject.getModelObjectTarget<openstudio::epmodel::HVACComponent>(
        openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::ReheatCoilName);

      removeFromLoop();

      if (coil) {
        if (auto plantLoop = coil->plantLoop()) {
          plantLoop->removeDemandBranchWithComponent(*coil);
        }
      }

      return HVACComponent_Impl::remove();
    }

    bool AirTerminalSingleDuctConstantVolumeReheat_Impl::removeFromLoop() {
      auto thisObject = getObject<openstudio::epmodel::ModelObject>();
      auto thermalZone = thermalZoneContainingTerminal(model(), thisObject);
      auto inletNode = inletModelObject();
      auto outletNode = outletModelObject();
      auto coil = thisObject.getModelObjectTarget<openstudio::epmodel::HVACComponent>(
        openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::ReheatCoilName);
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

      return removedFromAirLoop || static_cast<bool>(thermalZone) || static_cast<bool>(plantLoop);
    }

    bool AirTerminalSingleDuctConstantVolumeReheat_Impl::addToNode(Node& node) {
      if (node.model() != model()) {
        return false;
      }

      if (getObject<openstudio::epmodel::HVACComponent>().loop()) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctConstantVolumeReheat",
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
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctConstantVolumeReheat",
                 "addToNode requires the drop node to be a ZoneSplitter outlet node for the target AirLoopHVAC.");
        return false;
      }
      const auto splitterBranchIndex = static_cast<unsigned>(std::distance(splitterOutlets.begin(), splitterIt));

      auto mixerInlet = zoneMixer.inletModelObject(splitterBranchIndex);
      if (!mixerInlet) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctConstantVolumeReheat",
                 "addToNode requires a corresponding ZoneMixer inlet for ZoneSplitter branch index " << splitterBranchIndex << ".");
        return false;
      }
      auto thermalZone = owningThermalZoneForBranchNode(model(), node);
      if ((*mixerInlet != thisNode) && !isServedZoneReturnNode(thermalZone, *mixerInlet)) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctConstantVolumeReheat",
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

      const std::string inletNodeName = node.nameString() + " - " + thisObject.nameString() + " Inlet Node";
      auto inletNode = model().getOrCreateTransientByName<openstudio::epmodel::Node>(inletNodeName);

      if (!zoneSplitter.setOutletModelObject(splitterBranchIndex, inletNode.cast<ModelObject>())) {
        return false;
      }

      if (!setPointer(inletPort(), inletNode.handle())) {
        return false;
      }

      if (!setPointer(outletPort(), node.handle())) {
        return false;
      }

      if (auto adu = zoneHVACAirDistributionUnit()) {
        adu->getImpl<openstudio::epmodel::detail::ZoneHVACAirDistributionUnit_Impl>()->setOutletNode(node);
      }

      if (thermalZone) {
        if (!registerTerminalWithThermalZone(thisObject, *thermalZone)) {
          return false;
        }
      }

      return true;
    }

    Schedule AirTerminalSingleDuctConstantVolumeReheat_Impl::availabilitySchedule() const {
      auto schedule = getObject<ModelObject>().getModelObjectTarget<Schedule>(
        openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::AvailabilityScheduleName);
      if (!schedule) {
        LOG_FREE(Error, "openstudio.epmodel.AirTerminalSingleDuctConstantVolumeReheat",
                 "Required availability schedule not set, repairing persisted state with the model always-on discrete schedule");
        schedule = model().alwaysOnDiscreteSchedule();
        const bool ok = const_cast<AirTerminalSingleDuctConstantVolumeReheat_Impl*>(this)->setAvailabilitySchedule(*schedule);
        OS_ASSERT(ok);
        schedule = getObject<ModelObject>().getModelObjectTarget<Schedule>(
          openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::AvailabilityScheduleName);
      }
      OS_ASSERT(schedule);
      return *schedule;
    }

    bool AirTerminalSingleDuctConstantVolumeReheat_Impl::setAvailabilitySchedule(Schedule& schedule) {
      return ModelObject_Impl::setSchedule(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::AvailabilityScheduleName,
                                           "AirTerminalSingleDuctConstantVolumeReheat", "Availability", schedule);
    }

    HVACComponent AirTerminalSingleDuctConstantVolumeReheat_Impl::reheatCoil() const {
      auto coil =
        getObject<ModelObject>().getModelObjectTarget<HVACComponent>(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::ReheatCoilName);
      OS_ASSERT(coil);
      return *coil;
    }

    bool AirTerminalSingleDuctConstantVolumeReheat_Impl::setReheatCoil(const HVACComponent& coil) {
      if (coil.model() != model()) {
        return false;
      }

      const auto iddObjectType = coil.iddObject().type();
      if ((iddObjectType != IddObjectType::OS_Coil_Heating_Gas) && (iddObjectType != IddObjectType::OS_Coil_Heating_Electric)
          && (iddObjectType != IddObjectType::OS_Coil_Heating_Water) && (iddObjectType != IddObjectType::Coil_Heating_Fuel)
          && (iddObjectType != IddObjectType::Coil_Heating_Electric) && (iddObjectType != IddObjectType::Coil_Heating_Water)) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctConstantVolumeReheat",
                 "Unsupported reheat coil type '" << coil.iddObject().name() << "' for AirTerminalSingleDuctConstantVolumeReheat.");
        return false;
      }

      return setPointer(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::ReheatCoilName, coil.handle(), false);
    }

    void AirTerminalSingleDuctConstantVolumeReheat_Impl::resetReheatCoil() {
      OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::ReheatCoilName, ""));
    }

    boost::optional<double> AirTerminalSingleDuctConstantVolumeReheat_Impl::maximumAirFlowRate() const {
      return getDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::MaximumAirFlowRate, true);
    }

    bool AirTerminalSingleDuctConstantVolumeReheat_Impl::isMaximumAirFlowRateAutosized() const {
      if (auto value = getString(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::MaximumAirFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool AirTerminalSingleDuctConstantVolumeReheat_Impl::setMaximumAirFlowRate(double maximumAirFlowRate) {
      return setDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::MaximumAirFlowRate, maximumAirFlowRate);
    }

    void AirTerminalSingleDuctConstantVolumeReheat_Impl::resetMaximumAirFlowRate() {
      OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::MaximumAirFlowRate, ""));
    }

    void AirTerminalSingleDuctConstantVolumeReheat_Impl::autosizeMaximumAirFlowRate() {
      OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::MaximumAirFlowRate, "autosize"));
    }

    boost::optional<double> AirTerminalSingleDuctConstantVolumeReheat_Impl::maximumHotWaterorSteamFlowRate() const {
      return getDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::MaximumHotWaterorSteamFlowRate, true);
    }

    bool AirTerminalSingleDuctConstantVolumeReheat_Impl::isMaximumHotWaterorSteamFlowRateAutosized() const {
      if (auto value = getString(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::MaximumHotWaterorSteamFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool AirTerminalSingleDuctConstantVolumeReheat_Impl::setMaximumHotWaterorSteamFlowRate(double maximumHotWaterorSteamFlowRate) {
      return setDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::MaximumHotWaterorSteamFlowRate,
                       maximumHotWaterorSteamFlowRate);
    }

    void AirTerminalSingleDuctConstantVolumeReheat_Impl::resetMaximumHotWaterorSteamFlowRate() {
      OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::MaximumHotWaterorSteamFlowRate, ""));
    }

    void AirTerminalSingleDuctConstantVolumeReheat_Impl::autosizeMaximumHotWaterorSteamFlowRate() {
      OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::MaximumHotWaterorSteamFlowRate, "autosize"));
    }

    double AirTerminalSingleDuctConstantVolumeReheat_Impl::minimumHotWaterorSteamFlowRate() const {
      const auto value = getDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::MinimumHotWaterorSteamFlowRate, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirTerminalSingleDuctConstantVolumeReheat_Impl::isMinimumHotWaterorSteamFlowRateDefaulted() const {
      return isEmpty(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::MinimumHotWaterorSteamFlowRate);
    }

    bool AirTerminalSingleDuctConstantVolumeReheat_Impl::setMinimumHotWaterorSteamFlowRate(double minimumHotWaterorSteamFlowRate) {
      return setDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::MinimumHotWaterorSteamFlowRate,
                       minimumHotWaterorSteamFlowRate);
    }

    void AirTerminalSingleDuctConstantVolumeReheat_Impl::resetMinimumHotWaterorSteamFlowRate() {
      OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::MinimumHotWaterorSteamFlowRate, ""));
    }

    double AirTerminalSingleDuctConstantVolumeReheat_Impl::convergenceTolerance() const {
      const auto value = getDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::ConvergenceTolerance, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirTerminalSingleDuctConstantVolumeReheat_Impl::isConvergenceToleranceDefaulted() const {
      return isEmpty(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::ConvergenceTolerance);
    }

    bool AirTerminalSingleDuctConstantVolumeReheat_Impl::setConvergenceTolerance(double convergenceTolerance) {
      return setDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::ConvergenceTolerance, convergenceTolerance);
    }

    void AirTerminalSingleDuctConstantVolumeReheat_Impl::resetConvergenceTolerance() {
      OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::ConvergenceTolerance, ""));
    }

    double AirTerminalSingleDuctConstantVolumeReheat_Impl::maximumReheatAirTemperature() const {
      const auto value = getDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::MaximumReheatAirTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirTerminalSingleDuctConstantVolumeReheat_Impl::isMaximumReheatAirTemperatureDefaulted() const {
      return isEmpty(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::MaximumReheatAirTemperature);
    }

    bool AirTerminalSingleDuctConstantVolumeReheat_Impl::setMaximumReheatAirTemperature(double maximumReheatAirTemperature) {
      return setDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::MaximumReheatAirTemperature, maximumReheatAirTemperature);
    }

    void AirTerminalSingleDuctConstantVolumeReheat_Impl::resetMaximumReheatAirTemperature() {
      OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::MaximumReheatAirTemperature, ""));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
