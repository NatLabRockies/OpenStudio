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
#include <utilities/idd/ZoneHVAC_AirDistributionUnit_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {
  namespace detail {

    namespace {
      void assertSuccessfulMutation(bool result) {
        OS_ASSERT(result);
        (void)result;
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

    std::unique_ptr<SingleDuctTerminalRemovalPlan> SingleDuctTerminalRemovalPlan::prepare(StraightComponent& terminal) {
      const auto inletPort = terminal.inletPort();
      const auto outletPort = terminal.outletPort();
      if (inletPort == 0u || outletPort == 0u || inletPort == outletPort) {
        return nullptr;
      }

      auto terminalObject = terminal.cast<ModelObject>();
      const auto inletObject = terminal.inletModelObject();
      const auto outletObject = terminal.outletModelObject();
      if (static_cast<bool>(inletObject) != static_cast<bool>(outletObject)) {
        return nullptr;
      }

      boost::optional<ModelObject> inletNode;
      boost::optional<ModelObject> outletNode;
      std::unique_ptr<AirLoopHVAC_Impl::DemandBranchStartReservation> branchReservation;
      boost::optional<ThermalZone> servedZone;
      if (inletObject && outletObject) {
        const auto typedInletNode = inletObject->optionalCast<Node>();
        const auto typedOutletNode = outletObject->optionalCast<Node>();
        const auto airLoop = terminal.airLoopHVAC();
        if (!typedInletNode || !typedOutletNode || !airLoop) {
          return nullptr;
        }
        auto airLoopImpl = airLoop->getImpl<AirLoopHVAC_Impl>();
        OS_ASSERT(airLoopImpl);
        branchReservation = airLoopImpl->reserveDemandBranchStartBypass(terminal);
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
        if (inletSources.size() != 2u || terminalSourceCount != 1u || connectorSourceCount != 1u) {
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
          if (registeredZones.size() != 1u || (registeredZones.front() != *servedZone)) {
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
