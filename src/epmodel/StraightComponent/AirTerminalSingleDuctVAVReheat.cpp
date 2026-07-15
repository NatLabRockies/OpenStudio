/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/AirTerminalSingleDuctVAVReheat.hpp"
#include "StraightComponent/AirTerminalSingleDuctVAVReheat_Impl.hpp"

#include "HVACComponent/ThermalZone.hpp"
#include "HVACComponent/ThermalZone_Impl.hpp"
#include "HVACComponent.hpp"
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
#include "Splitter/AirLoopHVACZoneSplitter.hpp"
#include "Schedule/Schedule_Impl.hpp"
#include "Schedule/ScheduleConstant.hpp"

#include <algorithm>
#include <utilities/core/Assert.hpp>
#include <utilities/core/Logger.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/AirTerminal_SingleDuct_VAV_Reheat_FieldEnums.hxx>
#include <utilities/idd/Coil_Heating_Electric_FieldEnums.hxx>
#include <utilities/idd/Coil_Heating_Fuel_FieldEnums.hxx>
#include <utilities/idd/Coil_Heating_Water_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/ZoneHVAC_AirDistributionUnit_FieldEnums.hxx>

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

    bool setCoilAirNodes(HVACComponent& coil, const std::string& inletNodeName, const Node& outletNode) {
      switch (coil.iddObject().type().value()) {
        case IddObjectType::Coil_Heating_Fuel: {
          return coil.setString(openstudio::Coil_Heating_FuelFields::AirInletNodeName, inletNodeName)
                 && coil.setPointer(openstudio::Coil_Heating_FuelFields::AirOutletNodeName, outletNode.handle());
        }
        case IddObjectType::Coil_Heating_Electric: {
          return coil.setString(openstudio::Coil_Heating_ElectricFields::AirInletNodeName, inletNodeName)
                 && coil.setPointer(openstudio::Coil_Heating_ElectricFields::AirOutletNodeName, outletNode.handle());
        }
        case IddObjectType::Coil_Heating_Water: {
          return coil.setString(openstudio::Coil_Heating_WaterFields::AirInletNodeName, inletNodeName)
                 && coil.setPointer(openstudio::Coil_Heating_WaterFields::AirOutletNodeName, outletNode.handle());
        }
        default:
          return false;
      }
    }

    bool updateReheatCoilAirPath(ModelObject& terminal, HVACComponent& coil) {
      if (!terminal.name()) {
        terminal.createName();
      }
      if (terminal.nameString().empty()) {
        return false;
      }

      const std::string damperOutletNodeName = terminal.nameString() + " Damper Outlet";
      if (!terminal.setString(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::ReheatCoilObjectType, coil.iddObject().name())) {
        return false;
      }
      if (!terminal.setString(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::DamperAirOutletNodeName, damperOutletNodeName)) {
        return false;
      }

      auto outletNode = terminal.getModelObjectTarget<Node>(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::AirOutletNodeName);
      if (!outletNode) {
        return true;
      }

      return setCoilAirNodes(coil, damperOutletNodeName, *outletNode);
    }

  }  // namespace

  AirTerminalSingleDuctVAVReheat::AirTerminalSingleDuctVAVReheat(const Model& model)
    : StraightComponent(AirTerminalSingleDuctVAVReheat::iddObjectType(), model) {
    ScheduleConstant alwaysOn(model);
    OS_ASSERT(alwaysOn.setValue(1.0));
    OS_ASSERT(setAvailabilitySchedule(alwaysOn));
    autosizeMaximumAirFlowRate();
    OS_ASSERT(setZoneMinimumAirFlowInputMethod("Constant"));
    OS_ASSERT(setConstantMinimumAirFlowFraction(0.3));
    OS_ASSERT(setFixedMinimumAirFlowRate(0.0));
    OS_ASSERT(setMaximumFlowPerZoneFloorAreaDuringReheat(0.0));
    OS_ASSERT(setMinimumHotWaterOrStreamFlowRate(0.0));
    OS_ASSERT(setConvergenceTolerance(0.001));
    OS_ASSERT(setDamperHeatingAction("Normal"));
    autosizeMaximumFlowPerZoneFloorAreaDuringReheat();
    autosizeMaximumFlowFractionDuringReheat();
    OS_ASSERT(setMaximumReheatAirTemperature(35.0));
    autosizeMaximumHotWaterOrSteamFlowRate();
  }

  AirTerminalSingleDuctVAVReheat::AirTerminalSingleDuctVAVReheat(std::shared_ptr<detail::AirTerminalSingleDuctVAVReheat_Impl> impl)
    : StraightComponent(std::move(impl)) {}

  IddObjectType AirTerminalSingleDuctVAVReheat::iddObjectType() {
    return IddObjectType::AirTerminal_SingleDuct_VAV_Reheat;
  }

  std::vector<std::string> AirTerminalSingleDuctVAVReheat::zoneMinimumAirFlowInputMethodValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::ZoneMinimumAirFlowInputMethod);
  }

  std::vector<std::string> AirTerminalSingleDuctVAVReheat::damperHeatingActionValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::DamperHeatingAction);
  }

  bool AirTerminalSingleDuctVAVReheat::addToNode(Node& node) {
    return getImpl<detail::AirTerminalSingleDuctVAVReheat_Impl>()->addToNode(node);
  }

  HVACComponent AirTerminalSingleDuctVAVReheat::reheatCoil() const {
    return getImpl<detail::AirTerminalSingleDuctVAVReheat_Impl>()->reheatCoil();
  }

  bool AirTerminalSingleDuctVAVReheat::setReheatCoil(HVACComponent& coil) {
    return getImpl<detail::AirTerminalSingleDuctVAVReheat_Impl>()->setReheatCoil(coil);
  }

  Schedule AirTerminalSingleDuctVAVReheat::availabilitySchedule() const {
    return getImpl<detail::AirTerminalSingleDuctVAVReheat_Impl>()->availabilitySchedule();
  }

  bool AirTerminalSingleDuctVAVReheat::setAvailabilitySchedule(Schedule& schedule) {
    return getImpl<detail::AirTerminalSingleDuctVAVReheat_Impl>()->setAvailabilitySchedule(schedule);
  }

  boost::optional<Schedule> AirTerminalSingleDuctVAVReheat::minimumAirFlowFractionSchedule() const {
    return getImpl<detail::AirTerminalSingleDuctVAVReheat_Impl>()->minimumAirFlowFractionSchedule();
  }

  bool AirTerminalSingleDuctVAVReheat::setMinimumAirFlowFractionSchedule(Schedule& schedule) {
    return getImpl<detail::AirTerminalSingleDuctVAVReheat_Impl>()->setMinimumAirFlowFractionSchedule(schedule);
  }

  void AirTerminalSingleDuctVAVReheat::resetMinimumAirFlowFractionSchedule() {
    getImpl<detail::AirTerminalSingleDuctVAVReheat_Impl>()->resetMinimumAirFlowFractionSchedule();
  }

  boost::optional<Schedule> AirTerminalSingleDuctVAVReheat::minimumAirFlowTurndownSchedule() const {
    return getImpl<detail::AirTerminalSingleDuctVAVReheat_Impl>()->minimumAirFlowTurndownSchedule();
  }

  bool AirTerminalSingleDuctVAVReheat::setMinimumAirFlowTurndownSchedule(Schedule& schedule) {
    return getImpl<detail::AirTerminalSingleDuctVAVReheat_Impl>()->setMinimumAirFlowTurndownSchedule(schedule);
  }

  void AirTerminalSingleDuctVAVReheat::resetMinimumAirFlowTurndownSchedule() {
    getImpl<detail::AirTerminalSingleDuctVAVReheat_Impl>()->resetMinimumAirFlowTurndownSchedule();
  }

  boost::optional<double> AirTerminalSingleDuctVAVReheat::maximumAirFlowRate() const {
    return getImpl<detail::AirTerminalSingleDuctVAVReheat_Impl>()->maximumAirFlowRate();
  }

  bool AirTerminalSingleDuctVAVReheat::isMaximumAirFlowRateAutosized() const {
    return getImpl<detail::AirTerminalSingleDuctVAVReheat_Impl>()->isMaximumAirFlowRateAutosized();
  }

  bool AirTerminalSingleDuctVAVReheat::setMaximumAirFlowRate(double maximumAirFlowRate) {
    return getImpl<detail::AirTerminalSingleDuctVAVReheat_Impl>()->setMaximumAirFlowRate(maximumAirFlowRate);
  }

  void AirTerminalSingleDuctVAVReheat::autosizeMaximumAirFlowRate() {
    getImpl<detail::AirTerminalSingleDuctVAVReheat_Impl>()->autosizeMaximumAirFlowRate();
  }

  std::string AirTerminalSingleDuctVAVReheat::zoneMinimumAirFlowInputMethod() {
    return getImpl<detail::AirTerminalSingleDuctVAVReheat_Impl>()->zoneMinimumAirFlowInputMethod();
  }

  std::string AirTerminalSingleDuctVAVReheat::zoneMinimumAirFlowMethod() {
    return getImpl<detail::AirTerminalSingleDuctVAVReheat_Impl>()->zoneMinimumAirFlowInputMethod();
  }

  bool AirTerminalSingleDuctVAVReheat::setZoneMinimumAirFlowInputMethod(const std::string& value) {
    return getImpl<detail::AirTerminalSingleDuctVAVReheat_Impl>()->setZoneMinimumAirFlowInputMethod(value);
  }

  bool AirTerminalSingleDuctVAVReheat::setZoneMinimumAirFlowMethod(const std::string& value) {
    return getImpl<detail::AirTerminalSingleDuctVAVReheat_Impl>()->setZoneMinimumAirFlowInputMethod(value);
  }

  boost::optional<double> AirTerminalSingleDuctVAVReheat::constantMinimumAirFlowFraction() const {
    return getImpl<detail::AirTerminalSingleDuctVAVReheat_Impl>()->constantMinimumAirFlowFraction();
  }

  bool AirTerminalSingleDuctVAVReheat::isConstantMinimumAirFlowFractionAutosized() const {
    return getImpl<detail::AirTerminalSingleDuctVAVReheat_Impl>()->isConstantMinimumAirFlowFractionAutosized();
  }

  bool AirTerminalSingleDuctVAVReheat::setConstantMinimumAirFlowFraction(double value) {
    return getImpl<detail::AirTerminalSingleDuctVAVReheat_Impl>()->setConstantMinimumAirFlowFraction(value);
  }

  void AirTerminalSingleDuctVAVReheat::autosizeConstantMinimumAirFlowFraction() {
    getImpl<detail::AirTerminalSingleDuctVAVReheat_Impl>()->autosizeConstantMinimumAirFlowFraction();
  }

  boost::optional<double> AirTerminalSingleDuctVAVReheat::fixedMinimumAirFlowRate() const {
    return getImpl<detail::AirTerminalSingleDuctVAVReheat_Impl>()->fixedMinimumAirFlowRate();
  }

  bool AirTerminalSingleDuctVAVReheat::isFixedMinimumAirFlowRateAutosized() const {
    return getImpl<detail::AirTerminalSingleDuctVAVReheat_Impl>()->isFixedMinimumAirFlowRateAutosized();
  }

  bool AirTerminalSingleDuctVAVReheat::setFixedMinimumAirFlowRate(double value) {
    return getImpl<detail::AirTerminalSingleDuctVAVReheat_Impl>()->setFixedMinimumAirFlowRate(value);
  }

  void AirTerminalSingleDuctVAVReheat::autosizeFixedMinimumAirFlowRate() {
    getImpl<detail::AirTerminalSingleDuctVAVReheat_Impl>()->autosizeFixedMinimumAirFlowRate();
  }

  boost::optional<double> AirTerminalSingleDuctVAVReheat::maximumHotWaterOrSteamFlowRate() {
    return getImpl<detail::AirTerminalSingleDuctVAVReheat_Impl>()->maximumHotWaterOrSteamFlowRate();
  }

  bool AirTerminalSingleDuctVAVReheat::isMaximumHotWaterOrSteamFlowRateAutosized() const {
    return getImpl<detail::AirTerminalSingleDuctVAVReheat_Impl>()->isMaximumHotWaterOrSteamFlowRateAutosized();
  }

  bool AirTerminalSingleDuctVAVReheat::setMaximumHotWaterOrSteamFlowRate(double value) {
    return getImpl<detail::AirTerminalSingleDuctVAVReheat_Impl>()->setMaximumHotWaterOrSteamFlowRate(value);
  }

  void AirTerminalSingleDuctVAVReheat::autosizeMaximumHotWaterOrSteamFlowRate() {
    getImpl<detail::AirTerminalSingleDuctVAVReheat_Impl>()->autosizeMaximumHotWaterOrSteamFlowRate();
  }

  double AirTerminalSingleDuctVAVReheat::minimumHotWaterOrSteamFlowRate() {
    return getImpl<detail::AirTerminalSingleDuctVAVReheat_Impl>()->minimumHotWaterOrSteamFlowRate();
  }

  bool AirTerminalSingleDuctVAVReheat::setMinimumHotWaterOrStreamFlowRate(double value) {
    return getImpl<detail::AirTerminalSingleDuctVAVReheat_Impl>()->setMinimumHotWaterOrStreamFlowRate(value);
  }

  double AirTerminalSingleDuctVAVReheat::convergenceTolerance() {
    return getImpl<detail::AirTerminalSingleDuctVAVReheat_Impl>()->convergenceTolerance();
  }

  bool AirTerminalSingleDuctVAVReheat::setConvergenceTolerance(double value) {
    return getImpl<detail::AirTerminalSingleDuctVAVReheat_Impl>()->setConvergenceTolerance(value);
  }

  std::string AirTerminalSingleDuctVAVReheat::damperHeatingAction() {
    return getImpl<detail::AirTerminalSingleDuctVAVReheat_Impl>()->damperHeatingAction();
  }

  bool AirTerminalSingleDuctVAVReheat::setDamperHeatingAction(const std::string& value) {
    return getImpl<detail::AirTerminalSingleDuctVAVReheat_Impl>()->setDamperHeatingAction(value);
  }

  boost::optional<double> AirTerminalSingleDuctVAVReheat::maximumFlowPerZoneFloorAreaDuringReheat() {
    return getImpl<detail::AirTerminalSingleDuctVAVReheat_Impl>()->maximumFlowPerZoneFloorAreaDuringReheat();
  }

  bool AirTerminalSingleDuctVAVReheat::isMaximumFlowPerZoneFloorAreaDuringReheatAutosized() const {
    return getImpl<detail::AirTerminalSingleDuctVAVReheat_Impl>()->isMaximumFlowPerZoneFloorAreaDuringReheatAutosized();
  }

  bool AirTerminalSingleDuctVAVReheat::setMaximumFlowPerZoneFloorAreaDuringReheat(double value) {
    return getImpl<detail::AirTerminalSingleDuctVAVReheat_Impl>()->setMaximumFlowPerZoneFloorAreaDuringReheat(value);
  }

  void AirTerminalSingleDuctVAVReheat::autosizeMaximumFlowPerZoneFloorAreaDuringReheat() {
    getImpl<detail::AirTerminalSingleDuctVAVReheat_Impl>()->autosizeMaximumFlowPerZoneFloorAreaDuringReheat();
  }

  void AirTerminalSingleDuctVAVReheat::resetMaximumFlowPerZoneFloorAreaDuringReheat() {
    getImpl<detail::AirTerminalSingleDuctVAVReheat_Impl>()->resetMaximumFlowPerZoneFloorAreaDuringReheat();
  }

  boost::optional<double> AirTerminalSingleDuctVAVReheat::maximumFlowFractionDuringReheat() {
    return getImpl<detail::AirTerminalSingleDuctVAVReheat_Impl>()->maximumFlowFractionDuringReheat();
  }

  bool AirTerminalSingleDuctVAVReheat::isMaximumFlowFractionDuringReheatAutosized() const {
    return getImpl<detail::AirTerminalSingleDuctVAVReheat_Impl>()->isMaximumFlowFractionDuringReheatAutosized();
  }

  bool AirTerminalSingleDuctVAVReheat::setMaximumFlowFractionDuringReheat(double value) {
    return getImpl<detail::AirTerminalSingleDuctVAVReheat_Impl>()->setMaximumFlowFractionDuringReheat(value);
  }

  void AirTerminalSingleDuctVAVReheat::autosizeMaximumFlowFractionDuringReheat() {
    getImpl<detail::AirTerminalSingleDuctVAVReheat_Impl>()->autosizeMaximumFlowFractionDuringReheat();
  }

  void AirTerminalSingleDuctVAVReheat::resetMaximumFlowFractionDuringReheat() {
    getImpl<detail::AirTerminalSingleDuctVAVReheat_Impl>()->resetMaximumFlowFractionDuringReheat();
  }

  double AirTerminalSingleDuctVAVReheat::maximumReheatAirTemperature() {
    return getImpl<detail::AirTerminalSingleDuctVAVReheat_Impl>()->maximumReheatAirTemperature();
  }

  bool AirTerminalSingleDuctVAVReheat::setMaximumReheatAirTemperature(double value) {
    return getImpl<detail::AirTerminalSingleDuctVAVReheat_Impl>()->setMaximumReheatAirTemperature(value);
  }

  unsigned detail::AirTerminalSingleDuctVAVReheat_Impl::inletPort() const {
    return openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::AirInletNodeName;
  }

  unsigned detail::AirTerminalSingleDuctVAVReheat_Impl::outletPort() const {
    return openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::AirOutletNodeName;
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    boost::optional<ZoneHVACAirDistributionUnit> AirTerminalSingleDuctVAVReheat_Impl::zoneHVACAirDistributionUnit() const {
      auto terminal = getObject<openstudio::epmodel::ModelObject>();
      for (const auto& source : terminal.getSources(openstudio::IddObjectType::ZoneHVAC_AirDistributionUnit)) {
        if (auto adu = source.optionalCast<openstudio::epmodel::ZoneHVACAirDistributionUnit>()) {
          return adu;
        }
      }
      return boost::none;
    }

    std::vector<ModelObject> AirTerminalSingleDuctVAVReheat_Impl::children() const {
      std::vector<ModelObject> result;
      auto coil = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::ReheatCoilName);
      if (coil) {
        result.push_back(*coil);
      }
      return result;
    }

    std::vector<openstudio::IdfObject> AirTerminalSingleDuctVAVReheat_Impl::remove() {
      auto thisObject = getObject<openstudio::epmodel::ModelObject>();
      auto coil =
        thisObject.getModelObjectTarget<openstudio::epmodel::HVACComponent>(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::ReheatCoilName);

      removeFromLoop();

      if (coil) {
        if (auto plantLoop = coil->plantLoop()) {
          plantLoop->removeDemandBranchWithComponent(*coil);
        }
      }

      return HVACComponent_Impl::remove();
    }

    bool AirTerminalSingleDuctVAVReheat_Impl::removeFromLoop() {
      auto thisObject = getObject<openstudio::epmodel::ModelObject>();
      auto thermalZone = thermalZoneContainingTerminal(model(), thisObject);
      auto inletNode = inletModelObject();
      auto outletNode = outletModelObject();
      auto coil =
        thisObject.getModelObjectTarget<openstudio::epmodel::HVACComponent>(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::ReheatCoilName);
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

    bool AirTerminalSingleDuctVAVReheat_Impl::addToNode(Node& node) {
      if (node.model() != model()) {
        return false;
      }

      if (getObject<openstudio::epmodel::HVACComponent>().loop()) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctVAVReheat",
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
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctVAVReheat",
                 "addToNode requires the drop node to be a ZoneSplitter outlet node for the target AirLoopHVAC.");
        return false;
      }
      const auto splitterBranchIndex = static_cast<unsigned>(std::distance(splitterOutlets.begin(), splitterIt));

      auto mixerInlet = zoneMixer.inletModelObject(splitterBranchIndex);
      if (!mixerInlet) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctVAVReheat",
                 "addToNode requires a corresponding ZoneMixer inlet for ZoneSplitter branch index " << splitterBranchIndex << ".");
        return false;
      }
      auto thermalZone = owningThermalZoneForBranchNode(model(), node);
      if ((*mixerInlet != thisNode) && !isServedZoneReturnNode(thermalZone, *mixerInlet)) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctVAVReheat",
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

      if (auto coil = thisObject.getModelObjectTarget<openstudio::epmodel::HVACComponent>(
            openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::ReheatCoilName)) {
        if (!updateReheatCoilAirPath(thisObject, *coil)) {
          return false;
        }
      }

      return true;
    }

    HVACComponent AirTerminalSingleDuctVAVReheat_Impl::reheatCoil() const {
      auto coil = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::ReheatCoilName);
      OS_ASSERT(coil);
      return *coil;
    }

    bool AirTerminalSingleDuctVAVReheat_Impl::setReheatCoil(HVACComponent& coil) {
      if (coil.model() != model()) {
        return false;
      }

      const auto iddObjectType = coil.iddObject().type();
      if ((iddObjectType != IddObjectType::OS_Coil_Heating_Gas) && (iddObjectType != IddObjectType::OS_Coil_Heating_Electric)
          && (iddObjectType != IddObjectType::OS_Coil_Heating_Water) && (iddObjectType != IddObjectType::Coil_Heating_Fuel)
          && (iddObjectType != IddObjectType::Coil_Heating_Electric) && (iddObjectType != IddObjectType::Coil_Heating_Water)) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctVAVReheat",
                 "Unsupported reheat coil type '" << coil.iddObject().name() << "' for AirTerminalSingleDuctVAVReheat.");
        return false;
      }

      auto terminal = getObject<openstudio::epmodel::ModelObject>();
      return setPointer(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::ReheatCoilName, coil.handle(), false)
             && updateReheatCoilAirPath(terminal, coil);
    }

    Schedule AirTerminalSingleDuctVAVReheat_Impl::availabilitySchedule() const {
      auto schedule =
        getObject<ModelObject>().getModelObjectTarget<Schedule>(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::AvailabilityScheduleName);
      OS_ASSERT(schedule);
      return *schedule;
    }

    bool AirTerminalSingleDuctVAVReheat_Impl::setAvailabilitySchedule(Schedule& schedule) {
      return ModelObject_Impl::setSchedule(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::AvailabilityScheduleName,
                                           "AirTerminalSingleDuctVAVReheat", "Availability", schedule);
    }

    boost::optional<Schedule> AirTerminalSingleDuctVAVReheat_Impl::minimumAirFlowFractionSchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(
        openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::MinimumAirFlowFractionScheduleName);
    }

    bool AirTerminalSingleDuctVAVReheat_Impl::setMinimumAirFlowFractionSchedule(Schedule& schedule) {
      return ModelObject_Impl::setSchedule(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::MinimumAirFlowFractionScheduleName,
                                           "AirTerminalSingleDuctVAVReheat", "Minimum Air Flow Fraction", schedule);
    }

    void AirTerminalSingleDuctVAVReheat_Impl::resetMinimumAirFlowFractionSchedule() {
      OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::MinimumAirFlowFractionScheduleName, ""));
    }

    boost::optional<Schedule> AirTerminalSingleDuctVAVReheat_Impl::minimumAirFlowTurndownSchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(
        openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::MinimumAirFlowTurndownScheduleName);
    }

    bool AirTerminalSingleDuctVAVReheat_Impl::setMinimumAirFlowTurndownSchedule(Schedule& schedule) {
      return ModelObject_Impl::setSchedule(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::MinimumAirFlowTurndownScheduleName,
                                           "AirTerminalSingleDuctVAVReheat", "Minimum Air Flow Turndown", schedule);
    }

    void AirTerminalSingleDuctVAVReheat_Impl::resetMinimumAirFlowTurndownSchedule() {
      OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::MinimumAirFlowTurndownScheduleName, ""));
    }

    boost::optional<double> AirTerminalSingleDuctVAVReheat_Impl::maximumAirFlowRate() const {
      return getDouble(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::MaximumAirFlowRate, true);
    }

    bool AirTerminalSingleDuctVAVReheat_Impl::isMaximumAirFlowRateAutosized() const {
      if (auto value = getString(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::MaximumAirFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize") || openstudio::istringEqual(*value, "autocalculate");
      }
      return false;
    }

    bool AirTerminalSingleDuctVAVReheat_Impl::setMaximumAirFlowRate(double maximumAirFlowRate) {
      return setDouble(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::MaximumAirFlowRate, maximumAirFlowRate);
    }

    void AirTerminalSingleDuctVAVReheat_Impl::autosizeMaximumAirFlowRate() {
      const bool result = setString(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::MaximumAirFlowRate, "autosize");
      OS_ASSERT(result);
    }

    std::string AirTerminalSingleDuctVAVReheat_Impl::zoneMinimumAirFlowInputMethod() {
      const auto value = getString(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::ZoneMinimumAirFlowInputMethod, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirTerminalSingleDuctVAVReheat_Impl::setZoneMinimumAirFlowInputMethod(const std::string& value) {
      return setString(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::ZoneMinimumAirFlowInputMethod, value);
    }

    std::vector<std::string> AirTerminalSingleDuctVAVReheat_Impl::zoneMinimumAirFlowInputMethodValues() const {
      return AirTerminalSingleDuctVAVReheat::zoneMinimumAirFlowInputMethodValues();
    }

    boost::optional<double> AirTerminalSingleDuctVAVReheat_Impl::constantMinimumAirFlowFraction() const {
      return getDouble(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::ConstantMinimumAirFlowFraction, true);
    }

    bool AirTerminalSingleDuctVAVReheat_Impl::isConstantMinimumAirFlowFractionAutosized() const {
      if (auto value = getString(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::ConstantMinimumAirFlowFraction, true)) {
        return openstudio::istringEqual(*value, "autosize") || openstudio::istringEqual(*value, "autocalculate");
      }
      return false;
    }

    bool AirTerminalSingleDuctVAVReheat_Impl::setConstantMinimumAirFlowFraction(double value) {
      return setDouble(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::ConstantMinimumAirFlowFraction, value);
    }

    void AirTerminalSingleDuctVAVReheat_Impl::autosizeConstantMinimumAirFlowFraction() {
      const bool result = setString(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::ConstantMinimumAirFlowFraction, "autosize");
      OS_ASSERT(result);
    }

    boost::optional<double> AirTerminalSingleDuctVAVReheat_Impl::fixedMinimumAirFlowRate() const {
      return getDouble(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::FixedMinimumAirFlowRate, true);
    }

    bool AirTerminalSingleDuctVAVReheat_Impl::isFixedMinimumAirFlowRateAutosized() const {
      if (auto value = getString(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::FixedMinimumAirFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize") || openstudio::istringEqual(*value, "autocalculate");
      }
      return false;
    }

    bool AirTerminalSingleDuctVAVReheat_Impl::setFixedMinimumAirFlowRate(double value) {
      return setDouble(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::FixedMinimumAirFlowRate, value);
    }

    void AirTerminalSingleDuctVAVReheat_Impl::autosizeFixedMinimumAirFlowRate() {
      const bool result = setString(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::FixedMinimumAirFlowRate, "autosize");
      OS_ASSERT(result);
    }

    boost::optional<double> AirTerminalSingleDuctVAVReheat_Impl::maximumHotWaterOrSteamFlowRate() {
      return getDouble(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::MaximumHotWaterorSteamFlowRate, true);
    }

    bool AirTerminalSingleDuctVAVReheat_Impl::isMaximumHotWaterOrSteamFlowRateAutosized() const {
      if (auto value = getString(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::MaximumHotWaterorSteamFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize") || openstudio::istringEqual(*value, "autocalculate");
      }
      return false;
    }

    bool AirTerminalSingleDuctVAVReheat_Impl::setMaximumHotWaterOrSteamFlowRate(double value) {
      return setDouble(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::MaximumHotWaterorSteamFlowRate, value);
    }

    void AirTerminalSingleDuctVAVReheat_Impl::autosizeMaximumHotWaterOrSteamFlowRate() {
      const bool result = setString(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::MaximumHotWaterorSteamFlowRate, "autosize");
      OS_ASSERT(result);
    }

    double AirTerminalSingleDuctVAVReheat_Impl::minimumHotWaterOrSteamFlowRate() {
      const auto value = getDouble(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::MinimumHotWaterorSteamFlowRate, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirTerminalSingleDuctVAVReheat_Impl::setMinimumHotWaterOrStreamFlowRate(double value) {
      return setDouble(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::MinimumHotWaterorSteamFlowRate, value);
    }

    double AirTerminalSingleDuctVAVReheat_Impl::convergenceTolerance() {
      const auto value = getDouble(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::ConvergenceTolerance, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirTerminalSingleDuctVAVReheat_Impl::setConvergenceTolerance(double value) {
      return setDouble(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::ConvergenceTolerance, value);
    }

    std::string AirTerminalSingleDuctVAVReheat_Impl::damperHeatingAction() {
      const auto value = getString(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::DamperHeatingAction, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirTerminalSingleDuctVAVReheat_Impl::setDamperHeatingAction(const std::string& value) {
      return setString(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::DamperHeatingAction, value);
    }

    std::vector<std::string> AirTerminalSingleDuctVAVReheat_Impl::damperHeatingActionValues() const {
      return AirTerminalSingleDuctVAVReheat::damperHeatingActionValues();
    }

    boost::optional<double> AirTerminalSingleDuctVAVReheat_Impl::maximumFlowPerZoneFloorAreaDuringReheat() {
      return getDouble(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::MaximumFlowperZoneFloorAreaDuringReheat, true);
    }

    bool AirTerminalSingleDuctVAVReheat_Impl::isMaximumFlowPerZoneFloorAreaDuringReheatAutosized() const {
      if (auto value = getString(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::MaximumFlowperZoneFloorAreaDuringReheat, true)) {
        return openstudio::istringEqual(*value, "autosize") || openstudio::istringEqual(*value, "autocalculate");
      }
      return false;
    }

    bool AirTerminalSingleDuctVAVReheat_Impl::setMaximumFlowPerZoneFloorAreaDuringReheat(double value) {
      return setDouble(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::MaximumFlowperZoneFloorAreaDuringReheat, value);
    }

    void AirTerminalSingleDuctVAVReheat_Impl::autosizeMaximumFlowPerZoneFloorAreaDuringReheat() {
      const bool result = setString(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::MaximumFlowperZoneFloorAreaDuringReheat, "autocalculate");
      OS_ASSERT(result);
    }

    void AirTerminalSingleDuctVAVReheat_Impl::resetMaximumFlowPerZoneFloorAreaDuringReheat() {
      const bool result = setString(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::MaximumFlowperZoneFloorAreaDuringReheat, "");
      OS_ASSERT(result);
    }

    boost::optional<double> AirTerminalSingleDuctVAVReheat_Impl::maximumFlowFractionDuringReheat() {
      return getDouble(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::MaximumFlowFractionDuringReheat, true);
    }

    bool AirTerminalSingleDuctVAVReheat_Impl::isMaximumFlowFractionDuringReheatAutosized() const {
      if (auto value = getString(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::MaximumFlowFractionDuringReheat, true)) {
        return openstudio::istringEqual(*value, "autosize") || openstudio::istringEqual(*value, "autocalculate");
      }
      return false;
    }

    bool AirTerminalSingleDuctVAVReheat_Impl::setMaximumFlowFractionDuringReheat(double value) {
      return setDouble(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::MaximumFlowFractionDuringReheat, value);
    }

    void AirTerminalSingleDuctVAVReheat_Impl::autosizeMaximumFlowFractionDuringReheat() {
      const bool result = setString(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::MaximumFlowFractionDuringReheat, "autocalculate");
      OS_ASSERT(result);
    }

    void AirTerminalSingleDuctVAVReheat_Impl::resetMaximumFlowFractionDuringReheat() {
      const bool result = setString(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::MaximumFlowFractionDuringReheat, "");
      OS_ASSERT(result);
    }

    double AirTerminalSingleDuctVAVReheat_Impl::maximumReheatAirTemperature() {
      const auto value = getDouble(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::MaximumReheatAirTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirTerminalSingleDuctVAVReheat_Impl::setMaximumReheatAirTemperature(double value) {
      return setDouble(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::MaximumReheatAirTemperature, value);
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
