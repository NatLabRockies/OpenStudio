/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/AirTerminalSingleDuctVAVNoReheat.hpp"
#include "StraightComponent/AirTerminalSingleDuctVAVNoReheat_Impl.hpp"

#include "HVACComponent.hpp"
#include "HVACComponent/ThermalZone.hpp"
#include "HVACComponent/ThermalZone_Impl.hpp"
#include "Loop/AirLoopHVAC.hpp"
#include "Loop/AirLoopHVAC_Impl.hpp"
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
#include "Schedule/ScheduleConstant.hpp"
#include "Splitter/AirLoopHVACZoneSplitter.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/Logger.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/AirTerminal_SingleDuct_VAV_NoReheat_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/ZoneHVAC_AirDistributionUnit_FieldEnums.hxx>
#include <algorithm>

namespace openstudio {
namespace epmodel {

  namespace {

    void assertSuccessfulMutation(bool result) {
      OS_ASSERT(result);
      (void)result;
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

  AirTerminalSingleDuctVAVNoReheat::AirTerminalSingleDuctVAVNoReheat(const Model& model)
    : StraightComponent(AirTerminalSingleDuctVAVNoReheat::iddObjectType(), model) {
    ScheduleConstant alwaysOn(model);
    assertSuccessfulMutation(alwaysOn.setValue(1.0));
    assertSuccessfulMutation(setAvailabilitySchedule(alwaysOn));
    autosizeMaximumAirFlowRate();
    assertSuccessfulMutation(setZoneMinimumAirFlowInputMethod("Constant"));
    assertSuccessfulMutation(setConstantMinimumAirFlowFraction(0.3));
  }

  AirTerminalSingleDuctVAVNoReheat::AirTerminalSingleDuctVAVNoReheat(const Model& model, Schedule& schedule)
    : StraightComponent(AirTerminalSingleDuctVAVNoReheat::iddObjectType(), model) {
    if (!setAvailabilitySchedule(schedule)) {
      remove();
      LOG_FREE_AND_THROW("openstudio.epmodel.AirTerminalSingleDuctVAVNoReheat",
                         "Could not construct " << briefDescription() << ", because the availability schedule could not be assigned.");
    }
    autosizeMaximumAirFlowRate();
    assertSuccessfulMutation(setZoneMinimumAirFlowInputMethod("Constant"));
    assertSuccessfulMutation(setConstantMinimumAirFlowFraction(0.3));
  }

  AirTerminalSingleDuctVAVNoReheat::AirTerminalSingleDuctVAVNoReheat(std::shared_ptr<detail::AirTerminalSingleDuctVAVNoReheat_Impl> impl)
    : StraightComponent(std::move(impl)) {}

  IddObjectType AirTerminalSingleDuctVAVNoReheat::iddObjectType() {
    return IddObjectType::AirTerminal_SingleDuct_VAV_NoReheat;
  }

  std::vector<std::string> AirTerminalSingleDuctVAVNoReheat::zoneMinimumAirFlowInputMethodValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::AirTerminal_SingleDuct_VAV_NoReheatFields::ZoneMinimumAirFlowInputMethod);
  }

  bool AirTerminalSingleDuctVAVNoReheat::addToNode(Node& node) {
    return getImpl<detail::AirTerminalSingleDuctVAVNoReheat_Impl>()->addToNode(node);
  }

  Schedule AirTerminalSingleDuctVAVNoReheat::availabilitySchedule() const {
    return getImpl<detail::AirTerminalSingleDuctVAVNoReheat_Impl>()->availabilitySchedule();
  }

  bool AirTerminalSingleDuctVAVNoReheat::setAvailabilitySchedule(Schedule& schedule) {
    return getImpl<detail::AirTerminalSingleDuctVAVNoReheat_Impl>()->setAvailabilitySchedule(schedule);
  }

  boost::optional<Schedule> AirTerminalSingleDuctVAVNoReheat::minimumAirFlowFractionSchedule() const {
    return getImpl<detail::AirTerminalSingleDuctVAVNoReheat_Impl>()->minimumAirFlowFractionSchedule();
  }

  bool AirTerminalSingleDuctVAVNoReheat::setMinimumAirFlowFractionSchedule(Schedule& schedule) {
    return getImpl<detail::AirTerminalSingleDuctVAVNoReheat_Impl>()->setMinimumAirFlowFractionSchedule(schedule);
  }

  void AirTerminalSingleDuctVAVNoReheat::resetMinimumAirFlowFractionSchedule() {
    getImpl<detail::AirTerminalSingleDuctVAVNoReheat_Impl>()->resetMinimumAirFlowFractionSchedule();
  }

  boost::optional<Schedule> AirTerminalSingleDuctVAVNoReheat::minimumAirFlowTurndownSchedule() const {
    return getImpl<detail::AirTerminalSingleDuctVAVNoReheat_Impl>()->minimumAirFlowTurndownSchedule();
  }

  bool AirTerminalSingleDuctVAVNoReheat::setMinimumAirFlowTurndownSchedule(Schedule& schedule) {
    return getImpl<detail::AirTerminalSingleDuctVAVNoReheat_Impl>()->setMinimumAirFlowTurndownSchedule(schedule);
  }

  void AirTerminalSingleDuctVAVNoReheat::resetMinimumAirFlowTurndownSchedule() {
    getImpl<detail::AirTerminalSingleDuctVAVNoReheat_Impl>()->resetMinimumAirFlowTurndownSchedule();
  }

  boost::optional<double> AirTerminalSingleDuctVAVNoReheat::maximumAirFlowRate() const {
    return getImpl<detail::AirTerminalSingleDuctVAVNoReheat_Impl>()->maximumAirFlowRate();
  }

  bool AirTerminalSingleDuctVAVNoReheat::isMaximumAirFlowRateAutosized() const {
    return getImpl<detail::AirTerminalSingleDuctVAVNoReheat_Impl>()->isMaximumAirFlowRateAutosized();
  }

  bool AirTerminalSingleDuctVAVNoReheat::setMaximumAirFlowRate(double maximumAirFlowRate) {
    return getImpl<detail::AirTerminalSingleDuctVAVNoReheat_Impl>()->setMaximumAirFlowRate(maximumAirFlowRate);
  }

  void AirTerminalSingleDuctVAVNoReheat::resetMaximumAirFlowRate() {
    getImpl<detail::AirTerminalSingleDuctVAVNoReheat_Impl>()->resetMaximumAirFlowRate();
  }

  void AirTerminalSingleDuctVAVNoReheat::autosizeMaximumAirFlowRate() {
    getImpl<detail::AirTerminalSingleDuctVAVNoReheat_Impl>()->autosizeMaximumAirFlowRate();
  }

  boost::optional<std::string> AirTerminalSingleDuctVAVNoReheat::zoneMinimumAirFlowInputMethod() const {
    return getImpl<detail::AirTerminalSingleDuctVAVNoReheat_Impl>()->zoneMinimumAirFlowInputMethod();
  }

  bool AirTerminalSingleDuctVAVNoReheat::setZoneMinimumAirFlowInputMethod(const std::string& zoneMinimumAirFlowInputMethod) {
    return getImpl<detail::AirTerminalSingleDuctVAVNoReheat_Impl>()->setZoneMinimumAirFlowInputMethod(zoneMinimumAirFlowInputMethod);
  }

  void AirTerminalSingleDuctVAVNoReheat::resetZoneMinimumAirFlowInputMethod() {
    getImpl<detail::AirTerminalSingleDuctVAVNoReheat_Impl>()->resetZoneMinimumAirFlowInputMethod();
  }

  boost::optional<double> AirTerminalSingleDuctVAVNoReheat::constantMinimumAirFlowFraction() const {
    return getImpl<detail::AirTerminalSingleDuctVAVNoReheat_Impl>()->constantMinimumAirFlowFraction();
  }

  bool AirTerminalSingleDuctVAVNoReheat::isConstantMinimumAirFlowFractionAutosized() const {
    return getImpl<detail::AirTerminalSingleDuctVAVNoReheat_Impl>()->isConstantMinimumAirFlowFractionAutosized();
  }

  bool AirTerminalSingleDuctVAVNoReheat::isConstantMinimumAirFlowFractionDefaulted() const {
    return getImpl<detail::AirTerminalSingleDuctVAVNoReheat_Impl>()->isConstantMinimumAirFlowFractionDefaulted();
  }

  bool AirTerminalSingleDuctVAVNoReheat::setConstantMinimumAirFlowFraction(double constantMinimumAirFlowFraction) {
    return getImpl<detail::AirTerminalSingleDuctVAVNoReheat_Impl>()->setConstantMinimumAirFlowFraction(constantMinimumAirFlowFraction);
  }

  void AirTerminalSingleDuctVAVNoReheat::resetConstantMinimumAirFlowFraction() {
    getImpl<detail::AirTerminalSingleDuctVAVNoReheat_Impl>()->resetConstantMinimumAirFlowFraction();
  }

  void AirTerminalSingleDuctVAVNoReheat::autosizeConstantMinimumAirFlowFraction() {
    getImpl<detail::AirTerminalSingleDuctVAVNoReheat_Impl>()->autosizeConstantMinimumAirFlowFraction();
  }

  boost::optional<double> AirTerminalSingleDuctVAVNoReheat::fixedMinimumAirFlowRate() const {
    return getImpl<detail::AirTerminalSingleDuctVAVNoReheat_Impl>()->fixedMinimumAirFlowRate();
  }

  bool AirTerminalSingleDuctVAVNoReheat::isFixedMinimumAirFlowRateAutosized() const {
    return getImpl<detail::AirTerminalSingleDuctVAVNoReheat_Impl>()->isFixedMinimumAirFlowRateAutosized();
  }

  bool AirTerminalSingleDuctVAVNoReheat::isFixedMinimumAirFlowRateDefaulted() const {
    return getImpl<detail::AirTerminalSingleDuctVAVNoReheat_Impl>()->isFixedMinimumAirFlowRateDefaulted();
  }

  bool AirTerminalSingleDuctVAVNoReheat::setFixedMinimumAirFlowRate(double fixedMinimumAirFlowRate) {
    return getImpl<detail::AirTerminalSingleDuctVAVNoReheat_Impl>()->setFixedMinimumAirFlowRate(fixedMinimumAirFlowRate);
  }

  void AirTerminalSingleDuctVAVNoReheat::resetFixedMinimumAirFlowRate() {
    getImpl<detail::AirTerminalSingleDuctVAVNoReheat_Impl>()->resetFixedMinimumAirFlowRate();
  }

  void AirTerminalSingleDuctVAVNoReheat::autosizeFixedMinimumAirFlowRate() {
    getImpl<detail::AirTerminalSingleDuctVAVNoReheat_Impl>()->autosizeFixedMinimumAirFlowRate();
  }

  unsigned detail::AirTerminalSingleDuctVAVNoReheat_Impl::inletPort() const {
    return openstudio::AirTerminal_SingleDuct_VAV_NoReheatFields::AirInletNodeName;
  }

  unsigned detail::AirTerminalSingleDuctVAVNoReheat_Impl::outletPort() const {
    return openstudio::AirTerminal_SingleDuct_VAV_NoReheatFields::AirOutletNodeName;
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    boost::optional<ZoneHVACAirDistributionUnit> AirTerminalSingleDuctVAVNoReheat_Impl::zoneHVACAirDistributionUnit() const {
      auto terminal = getObject<openstudio::epmodel::ModelObject>();
      for (const auto& source : terminal.getSources(openstudio::IddObjectType::ZoneHVAC_AirDistributionUnit)) {
        if (auto adu = source.optionalCast<openstudio::epmodel::ZoneHVACAirDistributionUnit>()) {
          return adu;
        }
      }
      return boost::none;
    }

    bool AirTerminalSingleDuctVAVNoReheat_Impl::removeFromLoop() {
      auto thisObject = getObject<openstudio::epmodel::ModelObject>();
      auto thermalZone = thermalZoneContainingTerminal(model(), thisObject);
      auto inletNode = inletModelObject();
      auto outletNode = outletModelObject();
      bool shouldRemoveTerminalInletNode = false;
      if (auto terminal = thisObject.optionalCast<openstudio::epmodel::HVACComponent>()) {
        if (auto airLoop = terminal->airLoopHVAC()) {
          if (inletNode && outletNode) {
            const auto splitter = airLoop->zoneSplitter();
            const auto splitterBranchIndex = splitter.branchIndexForOutletModelObject(*inletNode);
            shouldRemoveTerminalInletNode = splitter.outletModelObject(splitterBranchIndex) == *inletNode;
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

      return removedFromAirLoop || static_cast<bool>(thermalZone) || cleanedADU;
    }

    bool AirTerminalSingleDuctVAVNoReheat_Impl::addToNode(Node& node) {
      if (node.model() != model()) {
        return false;
      }

      if (getObject<openstudio::epmodel::HVACComponent>().loop()) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctVAVNoReheat",
                 "Refusing to add an already-connected terminal to node '" << node.nameString() << "'.");
        return false;
      }

      auto airLoop = node.airLoopHVAC();
      if (!airLoop) {
        return false;
      }

      auto zoneSplitter = airLoop->zoneSplitter();
      const auto thisNode = node.cast<ModelObject>();
      const auto splitterOutlets = zoneSplitter.outletModelObjects();
      const auto splitterIt = std::ranges::find(splitterOutlets, thisNode);
      if (splitterIt == splitterOutlets.end()) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctVAVNoReheat",
                 "addToNode requires the drop node to be a ZoneSplitter outlet node for the target AirLoopHVAC.");
        return false;
      }
      const auto splitterBranchIndex = static_cast<unsigned>(std::distance(splitterOutlets.begin(), splitterIt));

      auto airLoopImpl = airLoop->getImpl<detail::AirLoopHVAC_Impl>();
      OS_ASSERT(airLoopImpl);
      auto mixerInlet = airLoopImpl->effectiveDemandReturnNodeForBranchStart(node);
      if (!mixerInlet) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctVAVNoReheat",
                 "addToNode requires one effective ZoneMixer return for the selected ZoneSplitter branch.");
        return false;
      }
      auto thermalZone = owningThermalZoneForBranchNode(model(), node);
      if ((*mixerInlet != thisNode) && !isServedZoneReturnNode(thermalZone, *mixerInlet)) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctVAVNoReheat",
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
        if (!adu->getImpl<openstudio::epmodel::detail::ZoneHVACAirDistributionUnit_Impl>()->setOutletNode(node)) {
          return false;
        }
      }

      if (thermalZone) {
        if (!registerTerminalWithThermalZone(thisObject, *thermalZone)) {
          return false;
        }
      }

      return true;
    }

    boost::optional<double> AirTerminalSingleDuctVAVNoReheat_Impl::maximumAirFlowRate() const {
      return getDouble(openstudio::AirTerminal_SingleDuct_VAV_NoReheatFields::MaximumAirFlowRate, true);
    }

    bool AirTerminalSingleDuctVAVNoReheat_Impl::isMaximumAirFlowRateAutosized() const {
      if (auto value = getString(openstudio::AirTerminal_SingleDuct_VAV_NoReheatFields::MaximumAirFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool AirTerminalSingleDuctVAVNoReheat_Impl::setMaximumAirFlowRate(double maximumAirFlowRate) {
      const bool result = setDouble(openstudio::AirTerminal_SingleDuct_VAV_NoReheatFields::MaximumAirFlowRate, maximumAirFlowRate);
      OS_ASSERT(result);
      return result;
    }

    void AirTerminalSingleDuctVAVNoReheat_Impl::resetMaximumAirFlowRate() {
      const bool result = setString(openstudio::AirTerminal_SingleDuct_VAV_NoReheatFields::MaximumAirFlowRate, "");
      OS_ASSERT(result);
    }

    void AirTerminalSingleDuctVAVNoReheat_Impl::autosizeMaximumAirFlowRate() {
      const bool result = setString(openstudio::AirTerminal_SingleDuct_VAV_NoReheatFields::MaximumAirFlowRate, "autosize");
      OS_ASSERT(result);
    }

    boost::optional<std::string> AirTerminalSingleDuctVAVNoReheat_Impl::zoneMinimumAirFlowInputMethod() const {
      return getString(openstudio::AirTerminal_SingleDuct_VAV_NoReheatFields::ZoneMinimumAirFlowInputMethod, true);
    }

    bool AirTerminalSingleDuctVAVNoReheat_Impl::setZoneMinimumAirFlowInputMethod(const std::string& zoneMinimumAirFlowInputMethod) {
      const bool result =
        setString(openstudio::AirTerminal_SingleDuct_VAV_NoReheatFields::ZoneMinimumAirFlowInputMethod, zoneMinimumAirFlowInputMethod);
      OS_ASSERT(result);
      return result;
    }

    void AirTerminalSingleDuctVAVNoReheat_Impl::resetZoneMinimumAirFlowInputMethod() {
      const bool result = setString(openstudio::AirTerminal_SingleDuct_VAV_NoReheatFields::ZoneMinimumAirFlowInputMethod, "");
      OS_ASSERT(result);
    }

    std::vector<std::string> AirTerminalSingleDuctVAVNoReheat_Impl::zoneMinimumAirFlowInputMethodValues() const {
      return AirTerminalSingleDuctVAVNoReheat::zoneMinimumAirFlowInputMethodValues();
    }

    Schedule AirTerminalSingleDuctVAVNoReheat_Impl::availabilitySchedule() const {
      auto schedule =
        getObject<ModelObject>().getModelObjectTarget<Schedule>(openstudio::AirTerminal_SingleDuct_VAV_NoReheatFields::AvailabilityScheduleName);
      OS_ASSERT(schedule);
      return *schedule;
    }

    bool AirTerminalSingleDuctVAVNoReheat_Impl::setAvailabilitySchedule(Schedule& schedule) {
      return ModelObject_Impl::setSchedule(openstudio::AirTerminal_SingleDuct_VAV_NoReheatFields::AvailabilityScheduleName,
                                           "AirTerminalSingleDuctVAVNoReheat", "Availability", schedule);
    }

    boost::optional<Schedule> AirTerminalSingleDuctVAVNoReheat_Impl::minimumAirFlowFractionSchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(
        openstudio::AirTerminal_SingleDuct_VAV_NoReheatFields::MinimumAirFlowFractionScheduleName);
    }

    bool AirTerminalSingleDuctVAVNoReheat_Impl::setMinimumAirFlowFractionSchedule(Schedule& schedule) {
      return ModelObject_Impl::setSchedule(openstudio::AirTerminal_SingleDuct_VAV_NoReheatFields::MinimumAirFlowFractionScheduleName,
                                           "AirTerminalSingleDuctVAVNoReheat", "Minimum Air Flow Fraction", schedule);
    }

    void AirTerminalSingleDuctVAVNoReheat_Impl::resetMinimumAirFlowFractionSchedule() {
      OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_VAV_NoReheatFields::MinimumAirFlowFractionScheduleName, ""));
    }

    boost::optional<Schedule> AirTerminalSingleDuctVAVNoReheat_Impl::minimumAirFlowTurndownSchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(
        openstudio::AirTerminal_SingleDuct_VAV_NoReheatFields::MinimumAirFlowTurndownScheduleName);
    }

    bool AirTerminalSingleDuctVAVNoReheat_Impl::setMinimumAirFlowTurndownSchedule(Schedule& schedule) {
      return ModelObject_Impl::setSchedule(openstudio::AirTerminal_SingleDuct_VAV_NoReheatFields::MinimumAirFlowTurndownScheduleName,
                                           "AirTerminalSingleDuctVAVNoReheat", "Minimum Air Flow Turndown", schedule);
    }

    void AirTerminalSingleDuctVAVNoReheat_Impl::resetMinimumAirFlowTurndownSchedule() {
      OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_VAV_NoReheatFields::MinimumAirFlowTurndownScheduleName, ""));
    }

    boost::optional<double> AirTerminalSingleDuctVAVNoReheat_Impl::constantMinimumAirFlowFraction() const {
      return getDouble(openstudio::AirTerminal_SingleDuct_VAV_NoReheatFields::ConstantMinimumAirFlowFraction, true);
    }

    bool AirTerminalSingleDuctVAVNoReheat_Impl::isConstantMinimumAirFlowFractionAutosized() const {
      if (auto value = getString(openstudio::AirTerminal_SingleDuct_VAV_NoReheatFields::ConstantMinimumAirFlowFraction, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool AirTerminalSingleDuctVAVNoReheat_Impl::isConstantMinimumAirFlowFractionDefaulted() const {
      return isEmpty(openstudio::AirTerminal_SingleDuct_VAV_NoReheatFields::ConstantMinimumAirFlowFraction);
    }

    bool AirTerminalSingleDuctVAVNoReheat_Impl::setConstantMinimumAirFlowFraction(double constantMinimumAirFlowFraction) {
      const bool result =
        setDouble(openstudio::AirTerminal_SingleDuct_VAV_NoReheatFields::ConstantMinimumAirFlowFraction, constantMinimumAirFlowFraction);
      OS_ASSERT(result);
      return result;
    }

    void AirTerminalSingleDuctVAVNoReheat_Impl::resetConstantMinimumAirFlowFraction() {
      const bool result = setString(openstudio::AirTerminal_SingleDuct_VAV_NoReheatFields::ConstantMinimumAirFlowFraction, "");
      OS_ASSERT(result);
    }

    void AirTerminalSingleDuctVAVNoReheat_Impl::autosizeConstantMinimumAirFlowFraction() {
      const bool result = setString(openstudio::AirTerminal_SingleDuct_VAV_NoReheatFields::ConstantMinimumAirFlowFraction, "autosize");
      OS_ASSERT(result);
    }

    boost::optional<double> AirTerminalSingleDuctVAVNoReheat_Impl::fixedMinimumAirFlowRate() const {
      return getDouble(openstudio::AirTerminal_SingleDuct_VAV_NoReheatFields::FixedMinimumAirFlowRate, true);
    }

    bool AirTerminalSingleDuctVAVNoReheat_Impl::isFixedMinimumAirFlowRateAutosized() const {
      if (auto value = getString(openstudio::AirTerminal_SingleDuct_VAV_NoReheatFields::FixedMinimumAirFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool AirTerminalSingleDuctVAVNoReheat_Impl::isFixedMinimumAirFlowRateDefaulted() const {
      return isEmpty(openstudio::AirTerminal_SingleDuct_VAV_NoReheatFields::FixedMinimumAirFlowRate);
    }

    bool AirTerminalSingleDuctVAVNoReheat_Impl::setFixedMinimumAirFlowRate(double fixedMinimumAirFlowRate) {
      const bool result = setDouble(openstudio::AirTerminal_SingleDuct_VAV_NoReheatFields::FixedMinimumAirFlowRate, fixedMinimumAirFlowRate);
      OS_ASSERT(result);
      return result;
    }

    void AirTerminalSingleDuctVAVNoReheat_Impl::resetFixedMinimumAirFlowRate() {
      const bool result = setString(openstudio::AirTerminal_SingleDuct_VAV_NoReheatFields::FixedMinimumAirFlowRate, "");
      OS_ASSERT(result);
    }

    void AirTerminalSingleDuctVAVNoReheat_Impl::autosizeFixedMinimumAirFlowRate() {
      const bool result = setString(openstudio::AirTerminal_SingleDuct_VAV_NoReheatFields::FixedMinimumAirFlowRate, "autosize");
      OS_ASSERT(result);
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
