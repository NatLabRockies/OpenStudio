/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/AirTerminalSingleDuctVAVReheat.hpp"
#include "StraightComponent/AirTerminalSingleDuctVAVReheat_Impl.hpp"

#include "HVACComponent/ThermalZone.hpp"
#include "HVACComponent/ThermalZone_Impl.hpp"
#include "HVACComponent.hpp"
#include "Loop/PlantLoop.hpp"
#include "Model.hpp"
#include "ModelObject.hpp"
#include "ModelObject/ZoneHVACAirDistributionUnit.hpp"
#include "ModelObject/ZoneHVACAirDistributionUnit_Impl.hpp"
#include "ModelObject/ZoneHVACEquipmentList.hpp"
#include "Node.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"
#include "Schedule/ScheduleConstant.hpp"
#include "StraightComponent/SingleDuctTerminalInsertionPlan.hpp"

#include <algorithm>
#include <utilities/core/Assert.hpp>
#include <utilities/core/Logger.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/core/UUID.hpp>
#include <utilities/idd/AirTerminal_SingleDuct_VAV_Reheat_FieldEnums.hxx>
#include <utilities/idd/Coil_Heating_Electric_FieldEnums.hxx>
#include <utilities/idd/Coil_Heating_Fuel_FieldEnums.hxx>
#include <utilities/idd/Coil_Heating_Water_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/ZoneHVAC_AirDistributionUnit_FieldEnums.hxx>
#include <utilities/idf/WorkspaceObject_Impl.hpp>

namespace openstudio {
namespace epmodel {

  namespace {

    void assertSuccessfulMutation(bool result) {
      OS_ASSERT(result);
      (void)result;
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

    bool unregisterTerminalFromThermalZone(const ModelObject& terminal, ThermalZone& thermalZone) {
      auto zoneImpl = thermalZone.getImpl<detail::ThermalZone_Impl>();
      OS_ASSERT(zoneImpl);
      return zoneImpl->getZoneHVACEquipmentList().removeEquipment(terminal);
    }

    struct ReheatCoilAirFields
    {
      unsigned inlet;
      unsigned outlet;
    };

    boost::optional<ReheatCoilAirFields> reheatCoilAirFields(const HVACComponent& coil) {
      switch (coil.iddObject().type().value()) {
        case IddObjectType::Coil_Heating_Fuel:
          return ReheatCoilAirFields{openstudio::Coil_Heating_FuelFields::AirInletNodeName, openstudio::Coil_Heating_FuelFields::AirOutletNodeName};
        case IddObjectType::Coil_Heating_Electric:
          return ReheatCoilAirFields{openstudio::Coil_Heating_ElectricFields::AirInletNodeName,
                                     openstudio::Coil_Heating_ElectricFields::AirOutletNodeName};
        case IddObjectType::Coil_Heating_Water:
          return ReheatCoilAirFields{openstudio::Coil_Heating_WaterFields::AirInletNodeName, openstudio::Coil_Heating_WaterFields::AirOutletNodeName};
        default:
          return boost::none;
      }
    }

    boost::optional<ModelObject> managedFieldTarget(const ModelObject& object, unsigned field) {
      const auto managedValue = object.getField(field, false);
      if (!managedValue) {
        return boost::none;
      }
      const auto targetHandle = toUUID(*managedValue);
      if (targetHandle.isNull()) {
        return boost::none;
      }
      if (auto target = object.model().getObject(targetHandle)) {
        return target->optionalCast<ModelObject>();
      }
      return boost::none;
    }

    class WorkspaceFieldSnapshot
    {
     public:
      WorkspaceFieldSnapshot(ModelObject object, unsigned field, bool pointerField)
        : m_object(std::move(object)), m_field(field), m_pointerField(pointerField), m_target(managedFieldTarget(m_object, m_field)) {
        auto workspaceImpl = m_object.getImpl<openstudio::detail::WorkspaceObject_Impl>();
        OS_ASSERT(workspaceImpl);
        m_rawValue = workspaceImpl->openstudio::detail::IdfObject_Impl::getString(m_field, false, true);
      }

      bool restore() const {
        auto workspaceImpl = m_object.getImpl<openstudio::detail::WorkspaceObject_Impl>();
        OS_ASSERT(workspaceImpl);
        if (m_target) {
          return workspaceImpl->setPointer(m_field, m_target->handle(), false);
        }

        bool restored = true;
        if (m_pointerField) {
          restored = workspaceImpl->setPointer(m_field, Handle(), false);
        }
        if (m_rawValue) {
          restored = workspaceImpl->openstudio::detail::IdfObject_Impl::setString(m_field, *m_rawValue, false) && restored;
        } else if (!m_pointerField) {
          restored = workspaceImpl->openstudio::detail::IdfObject_Impl::setString(m_field, "", false) && restored;
        }
        return restored;
      }

     private:
      ModelObject m_object;
      unsigned m_field;
      bool m_pointerField;
      boost::optional<ModelObject> m_target;
      boost::optional<std::string> m_rawValue;
    };

    // Restores the VAV reheat terminal's contained air path if insertion does
    // not commit. The shared insertion plan owns the surrounding connector,
    // terminal-port, ADU, and zone-equipment changes.
    class ReheatCoilAirPathSnapshot
    {
     public:
      ReheatCoilAirPathSnapshot(ModelObject terminal, ModelObject coil, const ReheatCoilAirFields& coilFields)
        : m_terminal(std::move(terminal)),
          m_terminalCoilType(m_terminal, openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::ReheatCoilObjectType, false),
          m_terminalDamperOutlet(m_terminal, openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::DamperAirOutletNodeName, true),
          m_coilInlet(coil, coilFields.inlet, true),
          m_coilOutlet(std::move(coil), coilFields.outlet, true) {
        for (const auto& node : m_terminal.model().getConcreteModelObjects<Node>()) {
          m_nodeNames.emplace_back(node.handle(), node.nameString());
        }
      }

      ReheatCoilAirPathSnapshot(const ReheatCoilAirPathSnapshot&) = delete;
      ReheatCoilAirPathSnapshot& operator=(const ReheatCoilAirPathSnapshot&) = delete;

      ~ReheatCoilAirPathSnapshot() {
        if (!m_committed) {
          rollback();
        }
      }

      void commit() {
        m_committed = true;
      }

     private:
      void rollback() {
        auto currentDamperOutlet = managedFieldTarget(m_terminal, openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::DamperAirOutletNodeName);
        auto currentDamperNode = currentDamperOutlet ? currentDamperOutlet->optionalCast<Node>() : boost::optional<Node>{};
        auto previousNode = m_nodeNames.end();
        if (currentDamperNode) {
          previousNode = std::ranges::find_if(m_nodeNames, [&](const auto& entry) { return entry.first == currentDamperNode->handle(); });
          if ((previousNode != m_nodeNames.end()) && currentDamperNode->nameString() != previousNode->second) {
            assertSuccessfulMutation(static_cast<bool>(currentDamperNode->setName(previousNode->second)));
          }
        }

        assertSuccessfulMutation(m_coilOutlet.restore());
        assertSuccessfulMutation(m_coilInlet.restore());
        assertSuccessfulMutation(m_terminalDamperOutlet.restore());
        assertSuccessfulMutation(m_terminalCoilType.restore());

        if (currentDamperNode && (previousNode == m_nodeNames.end()) && m_terminal.model().getObject(currentDamperNode->handle())) {
          OS_ASSERT(currentDamperNode->sources().empty());
          currentDamperNode->remove();
        }
      }

      ModelObject m_terminal;
      WorkspaceFieldSnapshot m_terminalCoilType;
      WorkspaceFieldSnapshot m_terminalDamperOutlet;
      WorkspaceFieldSnapshot m_coilInlet;
      WorkspaceFieldSnapshot m_coilOutlet;
      std::vector<std::pair<Handle, std::string>> m_nodeNames;
      bool m_committed = false;
    };

  }  // namespace

  AirTerminalSingleDuctVAVReheat::AirTerminalSingleDuctVAVReheat(const Model& model)
    : StraightComponent(AirTerminalSingleDuctVAVReheat::iddObjectType(), model) {
    ScheduleConstant alwaysOn(model);
    assertSuccessfulMutation(alwaysOn.setValue(1.0));
    assertSuccessfulMutation(setAvailabilitySchedule(alwaysOn));
    autosizeMaximumAirFlowRate();
    assertSuccessfulMutation(setZoneMinimumAirFlowInputMethod("Constant"));
    assertSuccessfulMutation(setConstantMinimumAirFlowFraction(0.3));
    assertSuccessfulMutation(setFixedMinimumAirFlowRate(0.0));
    assertSuccessfulMutation(setMaximumFlowPerZoneFloorAreaDuringReheat(0.0));
    assertSuccessfulMutation(setMinimumHotWaterOrStreamFlowRate(0.0));
    assertSuccessfulMutation(setConvergenceTolerance(0.001));
    assertSuccessfulMutation(setDamperHeatingAction("Normal"));
    autosizeMaximumFlowPerZoneFloorAreaDuringReheat();
    autosizeMaximumFlowFractionDuringReheat();
    assertSuccessfulMutation(setMaximumReheatAirTemperature(35.0));
    autosizeMaximumHotWaterOrSteamFlowRate();
  }

  AirTerminalSingleDuctVAVReheat::AirTerminalSingleDuctVAVReheat(const Model& model, Schedule& availabilitySchedule, HVACComponent& coil)
    : StraightComponent(AirTerminalSingleDuctVAVReheat::iddObjectType(), model) {
    if (!setAvailabilitySchedule(availabilitySchedule)) {
      remove();
      LOG_FREE_AND_THROW("openstudio.epmodel.AirTerminalSingleDuctVAVReheat",
                         "Could not construct " << briefDescription() << ", because the availability schedule could not be assigned.");
    }
    if (!setReheatCoil(coil)) {
      remove();
      LOG_FREE_AND_THROW("openstudio.epmodel.AirTerminalSingleDuctVAVReheat",
                         "Could not construct " << briefDescription() << ", because the reheat coil type was invalid or from another model.");
    }
    autosizeMaximumAirFlowRate();
    assertSuccessfulMutation(setZoneMinimumAirFlowInputMethod("Constant"));
    assertSuccessfulMutation(setConstantMinimumAirFlowFraction(0.3));
    assertSuccessfulMutation(setFixedMinimumAirFlowRate(0.0));
    assertSuccessfulMutation(setMaximumFlowPerZoneFloorAreaDuringReheat(0.0));
    assertSuccessfulMutation(setMinimumHotWaterOrStreamFlowRate(0.0));
    assertSuccessfulMutation(setConvergenceTolerance(0.001));
    assertSuccessfulMutation(setDamperHeatingAction("Normal"));
    autosizeMaximumFlowPerZoneFloorAreaDuringReheat();
    autosizeMaximumFlowFractionDuringReheat();
    assertSuccessfulMutation(setMaximumReheatAirTemperature(35.0));
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

    bool AirTerminalSingleDuctVAVReheat_Impl::maintainReheatCoilAirPath(HVACComponent& coil) {
      auto terminal = getObject<openstudio::epmodel::ModelObject>();
      if (!terminal.name()) {
        terminal.createName();
      }
      if (terminal.nameString().empty()) {
        return false;
      }

      if (!setString(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::ReheatCoilObjectType, coil.iddObject().name())) {
        return false;
      }

      const std::string suggestedDamperOutletNodeName = terminal.nameString() + " Damper Outlet";
      auto damperOutletNode =
        resolvedOrCreatedNodeTarget(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::DamperAirOutletNodeName, suggestedDamperOutletNodeName);
      if (damperOutletNode.nameString() != suggestedDamperOutletNodeName) {
        if (!damperOutletNode.setName(suggestedDamperOutletNodeName)) {
          return false;
        }
      }

      const auto outletNode = resolvedNodeTarget(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::AirOutletNodeName);
      switch (coil.iddObject().type().value()) {
        case IddObjectType::Coil_Heating_Fuel:
          return coil.setPointer(openstudio::Coil_Heating_FuelFields::AirInletNodeName, damperOutletNode.handle())
                 && (!outletNode || coil.setPointer(openstudio::Coil_Heating_FuelFields::AirOutletNodeName, outletNode->handle()));
        case IddObjectType::Coil_Heating_Electric:
          return coil.setPointer(openstudio::Coil_Heating_ElectricFields::AirInletNodeName, damperOutletNode.handle())
                 && (!outletNode || coil.setPointer(openstudio::Coil_Heating_ElectricFields::AirOutletNodeName, outletNode->handle()));
        case IddObjectType::Coil_Heating_Water:
          return coil.setPointer(openstudio::Coil_Heating_WaterFields::AirInletNodeName, damperOutletNode.handle())
                 && (!outletNode || coil.setPointer(openstudio::Coil_Heating_WaterFields::AirOutletNodeName, outletNode->handle()));
        default:
          return false;
      }
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
      auto ownedChildren = children();
      const bool hadTopology = static_cast<bool>(inletModelObject()) || static_cast<bool>(outletModelObject())
                               || static_cast<bool>(thermalZoneContainingTerminal(model(), thisObject))
                               || static_cast<bool>(zoneHVACAirDistributionUnit());
      bool childHadPlantTopology = false;
      for (const auto& child : ownedChildren) {
        if (auto component = child.optionalCast<openstudio::epmodel::HVACComponent>(); component && component->plantLoop()) {
          childHadPlantTopology = true;
          break;
        }
      }

      if ((hadTopology || childHadPlantTopology) && !removeFromLoop()) {
        return {};
      }

      auto result = HVACComponent_Impl::remove();
      if (result.empty()) {
        return result;
      }

      for (auto& child : ownedChildren) {
        auto removedChild = child.remove();
        result.insert(result.end(), removedChild.begin(), removedChild.end());
      }
      return result;
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
      if (inletNode || outletNode) {
        if (!inletNode || !outletNode || !isDemandBranchStartComponent()) {
          return false;
        }
        shouldRemoveTerminalInletNode = true;
      }

      // Water-coil teardown may synchronize controller state through the owning
      // air loop. Preflight the air branch above, then detach the plant side while
      // that canonical air path is still available.
      if (plantLoop && coil && !plantLoop->removeDemandBranchWithComponent(*coil)) {
        return false;
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

      return removedFromAirLoop || static_cast<bool>(thermalZone) || cleanedADU || static_cast<bool>(plantLoop);
    }

    bool AirTerminalSingleDuctVAVReheat_Impl::addToNode(Node& node) {
      return addToNode(node, AddToNodeFailureStage::None);
    }

    bool AirTerminalSingleDuctVAVReheat_Impl::addToNode(Node& node, AddToNodeFailureStage failureStage) {
      if (node.model() != model()) {
        return false;
      }

      auto thisObject = getObject<openstudio::epmodel::ModelObject>();
      auto coil = thisObject.getModelObjectTarget<HVACComponent>(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::ReheatCoilName);
      if (!coil) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctVAVReheat", "Refusing to connect a terminal without its required reheat coil.");
        return false;
      }
      const auto coilFields = reheatCoilAirFields(*coil);
      if (!coilFields) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctVAVReheat",
                 "Refusing to connect a terminal whose reheat coil does not expose a supported air path.");
        return false;
      }

      auto terminal = thisObject.cast<StraightComponent>();
      auto plan = SingleDuctTerminalInsertionPlan::prepare(terminal, node);
      if (!plan) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctVAVReheat",
                 "addToNode requires a terminal-free effective demand branch on the target AirLoopHVAC.");
        return false;
      }
      ReheatCoilAirPathSnapshot coilPathSnapshot(thisObject, coil->cast<ModelObject>(), *coilFields);
      if (!plan->apply()) {
        return false;
      }

      if (!maintainReheatCoilAirPath(*coil)) {
        return false;
      }
      if (failureStage == AddToNodeFailureStage::AfterReheatCoilAirPathPrepared) {
        return false;
      }
      if (!plan->commit()) {
        return false;
      }

      coilPathSnapshot.commit();
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

      if (!reheatCoilAirFields(coil)) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctVAVReheat",
                 "Unsupported reheat coil type '" << coil.iddObject().name() << "' for AirTerminalSingleDuctVAVReheat.");
        return false;
      }

      return setPointer(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::ReheatCoilName, coil.handle(), false) && maintainReheatCoilAirPath(coil);
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
