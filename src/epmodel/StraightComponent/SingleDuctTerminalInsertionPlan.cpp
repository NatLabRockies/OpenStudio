/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/SingleDuctTerminalInsertionPlan.hpp"

#include "HVACComponent/ThermalZone.hpp"
#include "HVACComponent/ThermalZone_Impl.hpp"
#include "Loop/AirLoopHVAC.hpp"
#include "Model.hpp"
#include "ModelObject/ModelObject_Impl.hpp"
#include "ModelObject/ZoneHVACAirDistributionUnit.hpp"
#include "ModelObject/ZoneHVACAirDistributionUnit_Impl.hpp"
#include "ModelObject/ZoneHVACEquipmentList.hpp"
#include "ModelObject/ZoneHVACEquipmentList_Impl.hpp"
#include "Node.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <algorithm>
#include <utilities/core/Assert.hpp>
#include <utilities/core/UUID.hpp>
#include <utilities/idd/ZoneHVAC_AirDistributionUnit_FieldEnums.hxx>
#include <utilities/idf/WorkspaceObject_Impl.hpp>

namespace openstudio {
namespace epmodel {
  namespace detail {

    namespace {
      void assertSuccessfulMutation(bool result) {
        OS_ASSERT(result);
        (void)result;
      }
    }  // namespace

    SingleDuctTerminalInsertionPlan::SingleDuctTerminalInsertionPlan(
      ModelObject terminal, std::unique_ptr<AirLoopHVAC_Impl::DemandBranchStartReservation> branchReservation, ModelObject outletNode,
      ModelObject inletNode, bool createdInletNode, unsigned inletPort, unsigned outletPort, boost::optional<ModelObject> airDistributionUnit,
      boost::optional<ModelObject> equipmentList, boost::optional<ModelObject> previousAirDistributionUnitOutletTarget,
      boost::optional<std::string> previousAirDistributionUnitOutletNodeName)
      : m_terminal(std::move(terminal)),
        m_branchReservation(std::move(branchReservation)),
        m_outletNode(std::move(outletNode)),
        m_inletNode(std::move(inletNode)),
        m_inletPort(inletPort),
        m_outletPort(outletPort),
        m_airDistributionUnit(std::move(airDistributionUnit)),
        m_equipmentList(std::move(equipmentList)),
        m_previousAirDistributionUnitOutletTarget(std::move(previousAirDistributionUnitOutletTarget)),
        m_previousAirDistributionUnitOutletNodeName(std::move(previousAirDistributionUnitOutletNodeName)),
        m_createdInletNode(createdInletNode) {}

    SingleDuctTerminalInsertionPlan::~SingleDuctTerminalInsertionPlan() {
      if (!m_committed) {
        rollback();
      }
    }

    std::unique_ptr<SingleDuctTerminalInsertionPlan> SingleDuctTerminalInsertionPlan::prepare(StraightComponent& terminal, Node& outletNode) {
      if (terminal.model() != outletNode.model()) {
        return nullptr;
      }

      const auto inletPort = terminal.inletPort();
      const auto outletPort = terminal.outletPort();
      if (inletPort == 0u || outletPort == 0u || inletPort == outletPort) {
        return nullptr;
      }

      auto terminalObject = terminal.cast<ModelObject>();
      auto terminalWorkspaceImpl = terminalObject.getImpl<openstudio::detail::WorkspaceObject_Impl>();
      OS_ASSERT(terminalWorkspaceImpl);
      const auto portIsBlank = [&](unsigned port) {
        const auto managedValue = terminalObject.getField(port, false);
        const auto rawValue = terminalWorkspaceImpl->openstudio::detail::IdfObject_Impl::getString(port, false, true);
        return (!managedValue || managedValue->empty()) && (!rawValue || rawValue->empty());
      };
      if (!portIsBlank(inletPort) || !portIsBlank(outletPort) || terminal.loop()) {
        return nullptr;
      }

      auto airLoop = outletNode.airLoopHVAC();
      if (!airLoop) {
        return nullptr;
      }
      auto airLoopImpl = airLoop->getImpl<AirLoopHVAC_Impl>();
      OS_ASSERT(airLoopImpl);
      auto branchReservation = airLoopImpl->reserveDemandBranchStart(outletNode);
      if (!branchReservation) {
        return nullptr;
      }

      std::vector<ModelObject> airDistributionUnits;
      for (const auto& source : terminalObject.getSources(openstudio::IddObjectType::ZoneHVAC_AirDistributionUnit)) {
        if (source.optionalCast<ZoneHVACAirDistributionUnit>()) {
          airDistributionUnits.push_back(source.cast<ModelObject>());
        }
      }
      if (airDistributionUnits.size() > 1u) {
        return nullptr;
      }

      boost::optional<ModelObject> equipmentList;
      if (auto thermalZone = branchReservation->thermalZone()) {
        auto thermalZoneImpl = thermalZone->getImpl<ThermalZone_Impl>();
        OS_ASSERT(thermalZoneImpl);
        auto list = thermalZoneImpl->zoneHVACEquipmentList();
        if (!list) {
          return nullptr;
        }
        const auto equipment = list->equipment();
        if (std::ranges::find(equipment, terminalObject) != equipment.end()) {
          return nullptr;
        }
        equipmentList = list->cast<ModelObject>();
      }

      boost::optional<ModelObject> previousAirDistributionUnitOutletTarget;
      boost::optional<std::string> previousAirDistributionUnitOutletNodeName;
      if (!airDistributionUnits.empty()) {
        const auto& airDistributionUnit = airDistributionUnits.front();
        const auto outletField = openstudio::ZoneHVAC_AirDistributionUnitFields::AirDistributionUnitOutletNodeName;
        if (auto managedField = airDistributionUnit.getField(outletField, false)) {
          const auto targetHandle = toUUID(*managedField);
          if (!targetHandle.isNull()) {
            if (auto target = terminal.model().getObject(targetHandle)) {
              previousAirDistributionUnitOutletTarget = target->optionalCast<ModelObject>();
            }
          }
        }
        if (!previousAirDistributionUnitOutletTarget) {
          auto workspaceImpl = airDistributionUnit.getImpl<openstudio::detail::WorkspaceObject_Impl>();
          OS_ASSERT(workspaceImpl);
          previousAirDistributionUnitOutletNodeName = workspaceImpl->openstudio::detail::IdfObject_Impl::getString(outletField, false, true);
        }
      }

      if (!terminalObject.name()) {
        terminalObject.createName();
        if (!terminalObject.name()) {
          return nullptr;
        }
      }
      const std::string inletNodeName = outletNode.nameString() + " - " + terminalObject.nameString() + " Inlet Node";
      const bool inletNodeExisted = static_cast<bool>(terminal.model().getConcreteModelObjectByName<Node>(inletNodeName));
      auto inletNode = terminal.model().getOrCreateTransientByName<Node>(inletNodeName);

      const boost::optional<ModelObject> airDistributionUnit =
        airDistributionUnits.empty() ? boost::none : boost::optional<ModelObject>(airDistributionUnits.front());
      return std::unique_ptr<SingleDuctTerminalInsertionPlan>(new SingleDuctTerminalInsertionPlan(
        terminalObject, std::move(branchReservation), outletNode.cast<ModelObject>(), inletNode.cast<ModelObject>(), !inletNodeExisted, inletPort,
        outletPort, airDistributionUnit, equipmentList, previousAirDistributionUnitOutletTarget, previousAirDistributionUnitOutletNodeName));
    }

    bool SingleDuctTerminalInsertionPlan::setTerminalPointer(unsigned fieldIndex, const Handle& targetHandle) {
      auto terminalImpl = m_terminal.getImpl<ModelObject_Impl>();
      OS_ASSERT(terminalImpl);
      return terminalImpl->setPointer(fieldIndex, targetHandle, false);
    }

    bool SingleDuctTerminalInsertionPlan::apply(bool failAfterAirDistributionUnitUpdate) {
      if (m_applyAttempted) {
        return false;
      }
      m_applyAttempted = true;

      auto inletNode = m_inletNode.optionalCast<Node>();
      auto outletNode = m_outletNode.optionalCast<Node>();
      OS_ASSERT(m_branchReservation && inletNode && outletNode);
      if (!inletNode || !outletNode || !m_branchReservation->replaceWith(*inletNode)) {
        return false;
      }

      m_inletAssignmentAttempted = true;
      if (!setTerminalPointer(m_inletPort, inletNode->handle())) {
        return false;
      }

      m_outletAssignmentAttempted = true;
      if (!setTerminalPointer(m_outletPort, outletNode->handle())) {
        return false;
      }

      if (m_airDistributionUnit) {
        auto airDistributionUnit = m_airDistributionUnit->optionalCast<ZoneHVACAirDistributionUnit>();
        OS_ASSERT(airDistributionUnit);
        m_airDistributionUnitUpdateAttempted = true;
        if (!airDistributionUnit || !airDistributionUnit->getImpl<ZoneHVACAirDistributionUnit_Impl>()->setOutletNode(*outletNode)) {
          return false;
        }
      }

      if (failAfterAirDistributionUnitUpdate) {
        return false;
      }

      if (m_equipmentList) {
        auto equipmentList = m_equipmentList->optionalCast<ZoneHVACEquipmentList>();
        OS_ASSERT(equipmentList);
        if (!equipmentList || !equipmentList->addEquipment(m_terminal)) {
          if (equipmentList) {
            const auto equipment = equipmentList->equipment();
            m_zoneRegistered = std::ranges::find(equipment, m_terminal) != equipment.end();
          }
          return false;
        }
        m_zoneRegistered = true;
      }

      m_applySucceeded = true;
      return true;
    }

    bool SingleDuctTerminalInsertionPlan::commit() {
      if (!m_applySucceeded || !m_branchReservation->commit()) {
        return false;
      }
      m_committed = true;
      return true;
    }

    void SingleDuctTerminalInsertionPlan::rollback() {
      OS_ASSERT(m_branchReservation);
      if (!m_branchReservation->restore()) {
        OS_ASSERT(false);
        return;
      }

      if (m_zoneRegistered && m_equipmentList) {
        auto equipmentList = m_equipmentList->optionalCast<ZoneHVACEquipmentList>();
        OS_ASSERT(equipmentList);
        if (equipmentList) {
          assertSuccessfulMutation(equipmentList->removeEquipment(m_terminal));
        }
      }

      if (m_airDistributionUnit && m_airDistributionUnitUpdateAttempted) {
        auto airDistributionUnit = m_airDistributionUnit->optionalCast<ZoneHVACAirDistributionUnit>();
        OS_ASSERT(airDistributionUnit);
        if (airDistributionUnit) {
          auto airDistributionUnitImpl = airDistributionUnit->getImpl<ZoneHVACAirDistributionUnit_Impl>();
          OS_ASSERT(airDistributionUnitImpl);
          const auto outletField = openstudio::ZoneHVAC_AirDistributionUnitFields::AirDistributionUnitOutletNodeName;
          bool restored = false;
          if (m_previousAirDistributionUnitOutletTarget) {
            restored = airDistributionUnitImpl->setPointer(outletField, m_previousAirDistributionUnitOutletTarget->handle(), false);
          } else if (m_previousAirDistributionUnitOutletNodeName) {
            const bool pointerCleared = airDistributionUnitImpl->setPointer(outletField, Handle(), false);
            const bool rawRestored = airDistributionUnitImpl->openstudio::detail::IdfObject_Impl::setString(
              outletField, *m_previousAirDistributionUnitOutletNodeName, false);
            restored = pointerCleared && rawRestored;
          } else {
            restored = airDistributionUnitImpl->setPointer(outletField, Handle(), false);
          }
          assertSuccessfulMutation(restored);
        }
      }

      if (m_outletAssignmentAttempted) {
        assertSuccessfulMutation(setTerminalPointer(m_outletPort, Handle()));
      }
      if (m_inletAssignmentAttempted) {
        assertSuccessfulMutation(setTerminalPointer(m_inletPort, Handle()));
      }
      if (m_createdInletNode && m_terminal.model().getObject(m_inletNode.handle())) {
        auto inletNode = m_inletNode.optionalCast<Node>();
        OS_ASSERT(inletNode);
        if (inletNode) {
          inletNode->remove();
        }
      }
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
