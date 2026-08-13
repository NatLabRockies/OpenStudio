/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/SingleDuctTerminalRemovalPlan.hpp"

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
#include "Splitter/AirLoopHVACSupplyPlenum.hpp"
#include "Splitter/AirLoopHVACZoneSplitter.hpp"
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

      struct ExistingNodeField
      {
        bool set = false;
        boost::optional<Node> node;
      };

      ExistingNodeField existingNodeField(const ModelObject& object, unsigned field) {
        ExistingNodeField result;
        const auto managedValue = object.getField(field, false);
        auto workspaceImpl = object.getImpl<openstudio::detail::WorkspaceObject_Impl>();
        OS_ASSERT(workspaceImpl);
        const auto rawValue = workspaceImpl->openstudio::detail::IdfObject_Impl::getString(field, false, true);
        if ((!managedValue || managedValue->empty()) && (!rawValue || rawValue->empty())) {
          return result;
        }

        result.set = true;
        if (!managedValue || managedValue->empty()) {
          return result;
        }
        const auto targetHandle = toUUID(*managedValue);
        if (targetHandle.isNull()) {
          return result;
        }
        if (auto target = object.model().getObject(targetHandle)) {
          result.node = target->optionalCast<Node>();
        }
        return result;
      }
    }  // namespace

    SingleDuctTerminalRemovalPlan::SingleDuctTerminalRemovalPlan(ModelObject terminal, unsigned inletPort, unsigned outletPort,
                                                                 std::unique_ptr<AirLoopHVAC_Impl::DemandBranchStartReservation> branchReservation,
                                                                 boost::optional<ModelObject> inletNode, boost::optional<ModelObject> outletNode,
                                                                 boost::optional<ModelObject> equipmentList,
                                                                 boost::optional<ModelObject> airDistributionUnit)
      : m_terminal(std::move(terminal)),
        m_inletPort(inletPort),
        m_outletPort(outletPort),
        m_branchReservation(std::move(branchReservation)),
        m_inletNode(std::move(inletNode)),
        m_outletNode(std::move(outletNode)),
        m_equipmentList(std::move(equipmentList)),
        m_airDistributionUnit(std::move(airDistributionUnit)) {}

    bool SingleDuctTerminalRemovalPlan::hasTopology(const StraightComponent& terminal) {
      const auto terminalObject = terminal.cast<ModelObject>();
      if (existingNodeField(terminalObject, terminal.inletPort()).set || existingNodeField(terminalObject, terminal.outletPort()).set) {
        return true;
      }

      for (const auto& zone : terminal.model().getConcreteModelObjects<ThermalZone>()) {
        const auto equipment = zone.equipment();
        if (std::ranges::find(equipment, terminalObject) != equipment.end()) {
          return true;
        }
      }

      return !terminalObject.getSources(openstudio::IddObjectType::ZoneHVAC_AirDistributionUnit).empty();
    }

    std::unique_ptr<SingleDuctTerminalRemovalPlan> SingleDuctTerminalRemovalPlan::prepare(StraightComponent& terminal,
                                                                                          const std::vector<ModelObject>& containedInletSources,
                                                                                          const boost::optional<Node>& authoritativeOutlet,
                                                                                          bool allowMissingZoneRegistration) {
      const auto inletPort = terminal.inletPort();
      const auto outletPort = terminal.outletPort();
      if (inletPort == 0u || outletPort == 0u || inletPort == outletPort) {
        return nullptr;
      }

      auto terminalObject = terminal.cast<ModelObject>();
      std::vector<Handle> containedInletSourceHandles;
      containedInletSourceHandles.reserve(containedInletSources.size());
      for (const auto& source : containedInletSources) {
        const auto type = source.iddObject().type();
        if (source.model() != terminal.model() || source.handle() == terminalObject.handle() || type == AirLoopHVACSupplyPlenum::iddObjectType()
            || type == AirLoopHVACZoneSplitter::iddObjectType()
            || std::ranges::find(containedInletSourceHandles, source.handle()) != containedInletSourceHandles.end()) {
          return nullptr;
        }
        containedInletSourceHandles.push_back(source.handle());
      }

      const auto inletField = existingNodeField(terminalObject, inletPort);
      const auto outletField = existingNodeField(terminalObject, outletPort);
      if (authoritativeOutlet && authoritativeOutlet->model() != terminal.model()) {
        return nullptr;
      }
      if ((!authoritativeOutlet && (inletField.set != outletField.set || (inletField.set && (!inletField.node || !outletField.node))))
          || (authoritativeOutlet && (!inletField.set || !inletField.node))) {
        return nullptr;
      }

      boost::optional<ModelObject> inletNode;
      boost::optional<ModelObject> outletNode;
      std::unique_ptr<AirLoopHVAC_Impl::DemandBranchStartReservation> branchReservation;
      boost::optional<ThermalZone> servedZone;
      const auto effectiveOutletNode = authoritativeOutlet ? authoritativeOutlet : outletField.node;
      if (inletField.node && effectiveOutletNode) {
        const auto typedInletNode = inletField.node;
        const auto typedOutletNode = effectiveOutletNode;
        if (!typedInletNode || !typedOutletNode) {
          return nullptr;
        }
        if (authoritativeOutlet) {
          for (const auto& candidateAirLoop : terminal.model().getConcreteModelObjects<AirLoopHVAC>()) {
            auto airLoopImpl = candidateAirLoop.getImpl<AirLoopHVAC_Impl>();
            OS_ASSERT(airLoopImpl);
            auto candidateReservation = airLoopImpl->reserveDemandBranchStartBypass(terminal, *authoritativeOutlet, outletField.node);
            if (!candidateReservation) {
              continue;
            }
            if (branchReservation) {
              return nullptr;
            }
            branchReservation = std::move(candidateReservation);
          }
        } else if (const auto airLoop = terminal.airLoopHVAC()) {
          auto airLoopImpl = airLoop->getImpl<AirLoopHVAC_Impl>();
          OS_ASSERT(airLoopImpl);
          branchReservation = airLoopImpl->reserveDemandBranchStartBypass(terminal);
        }
        if (!branchReservation) {
          return nullptr;
        }
        servedZone = branchReservation->thermalZone();
        inletNode = typedInletNode->cast<ModelObject>();
        outletNode = typedOutletNode->cast<ModelObject>();

        const auto inletSources = typedInletNode->sources();
        const auto terminalSourceCount =
          std::ranges::count_if(inletSources, [&](const auto& source) { return source.handle() == terminalObject.handle(); });
        const auto connectorSourceCount = std::ranges::count_if(inletSources, [](const auto& source) {
          const auto type = source.iddObject().type();
          return type == AirLoopHVACSupplyPlenum::iddObjectType() || type == AirLoopHVACZoneSplitter::iddObjectType();
        });
        const bool hasEveryContainedSource = std::ranges::all_of(containedInletSourceHandles, [&](const auto& sourceHandle) {
          return std::ranges::count_if(inletSources, [&](const auto& source) { return source.handle() == sourceHandle; }) == 1;
        });
        if (inletSources.size() != 2u + containedInletSourceHandles.size() || terminalSourceCount != 1u || connectorSourceCount != 1u
            || !hasEveryContainedSource) {
          return nullptr;
        }
      } else if (terminal.loop()) {
        return nullptr;
      }

      std::vector<ThermalZone> registeredZones;
      for (const auto& zone : terminal.model().getConcreteModelObjects<ThermalZone>()) {
        const auto equipment = zone.equipment();
        const auto count = std::ranges::count(equipment, terminalObject);
        if (count > 1) {
          return nullptr;
        }
        if (count == 1) {
          registeredZones.push_back(zone);
        }
      }
      if (registeredZones.size() > 1u) {
        return nullptr;
      }
      if (branchReservation) {
        if (servedZone) {
          if ((!allowMissingZoneRegistration && registeredZones.size() != 1u) || (allowMissingZoneRegistration && registeredZones.size() > 1u)
              || (!registeredZones.empty() && registeredZones.front() != *servedZone)) {
            return nullptr;
          }
        } else if (!registeredZones.empty()) {
          return nullptr;
        }
      }

      boost::optional<ModelObject> equipmentList;
      if (!registeredZones.empty()) {
        auto zoneImpl = registeredZones.front().getImpl<ThermalZone_Impl>();
        OS_ASSERT(zoneImpl);
        const auto list = zoneImpl->zoneHVACEquipmentList();
        if (!list) {
          return nullptr;
        }
        equipmentList = list->cast<ModelObject>();
      }

      std::vector<ModelObject> airDistributionUnits;
      for (const auto& source : terminalObject.getSources(openstudio::IddObjectType::ZoneHVAC_AirDistributionUnit)) {
        if (auto airDistributionUnit = source.optionalCast<ZoneHVACAirDistributionUnit>()) {
          const auto linkedTerminal = airDistributionUnit->airTerminal();
          if (!linkedTerminal || (*linkedTerminal != terminalObject)) {
            return nullptr;
          }
          airDistributionUnits.push_back(airDistributionUnit->cast<ModelObject>());
        }
      }
      if (airDistributionUnits.size() > 1u) {
        return nullptr;
      }

      const boost::optional<ModelObject> airDistributionUnit =
        airDistributionUnits.empty() ? boost::none : boost::optional<ModelObject>(airDistributionUnits.front());
      if (!branchReservation && !equipmentList && !airDistributionUnit) {
        return nullptr;
      }

      return std::unique_ptr<SingleDuctTerminalRemovalPlan>(new SingleDuctTerminalRemovalPlan(
        terminalObject, inletPort, outletPort, std::move(branchReservation), inletNode, outletNode, equipmentList, airDistributionUnit));
    }

    void SingleDuctTerminalRemovalPlan::commit() {
      if (m_branchReservation) {
        const auto outletNode = m_outletNode ? m_outletNode->optionalCast<Node>() : boost::optional<Node>();
        OS_ASSERT(outletNode);
        assertSuccessfulMutation(m_branchReservation->replaceWith(*outletNode));
        assertSuccessfulMutation(m_branchReservation->commit());
      }

      if (m_equipmentList) {
        auto equipmentList = m_equipmentList->optionalCast<ZoneHVACEquipmentList>();
        OS_ASSERT(equipmentList);
        assertSuccessfulMutation(equipmentList->removeEquipment(m_terminal));
      }

      if (m_airDistributionUnit) {
        auto airDistributionUnit = m_airDistributionUnit->optionalCast<ZoneHVACAirDistributionUnit>();
        OS_ASSERT(airDistributionUnit);
        auto airDistributionUnitImpl = airDistributionUnit->getImpl<ZoneHVACAirDistributionUnit_Impl>();
        OS_ASSERT(airDistributionUnitImpl);
        assertSuccessfulMutation(
          airDistributionUnitImpl->setPointer(openstudio::ZoneHVAC_AirDistributionUnitFields::AirDistributionUnitOutletNodeName, Handle(), false));
        assertSuccessfulMutation(
          airDistributionUnitImpl->setString(openstudio::ZoneHVAC_AirDistributionUnitFields::AirTerminalObjectType, "", false));
        assertSuccessfulMutation(
          airDistributionUnitImpl->setPointer(openstudio::ZoneHVAC_AirDistributionUnitFields::AirTerminalName, Handle(), false));
      }

      auto terminalImpl = m_terminal.getImpl<ModelObject_Impl>();
      OS_ASSERT(terminalImpl);
      assertSuccessfulMutation(terminalImpl->setPointer(m_inletPort, Handle(), false));
      assertSuccessfulMutation(terminalImpl->setPointer(m_outletPort, Handle(), false));

      if (m_inletNode && m_terminal.model().getObject(m_inletNode->handle())) {
        auto inletNode = m_inletNode->optionalCast<Node>();
        OS_ASSERT(inletNode);
        if (inletNode) {
          inletNode->remove();
          OS_ASSERT(!m_terminal.model().getObject(m_inletNode->handle()));
        }
      }
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
