/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "AirTerminalSingleDuctUserDefined.hpp"
#include "AirTerminalSingleDuctUserDefined_Impl.hpp"

#include "HVACComponent.hpp"
#include "HVACComponent/ThermalZone.hpp"
#include "HVACComponent/ThermalZone_Impl.hpp"
#include "Loop/AirLoopHVAC.hpp"
#include "Loop/AirLoopHVAC_Impl.hpp"
#include "Model.hpp"
#include "ModelObject.hpp"
#include "ModelObject/ZoneHVACAirDistributionUnit.hpp"
#include "ModelObject/ZoneHVACAirDistributionUnit_Impl.hpp"
#include "ModelObject/ZoneHVACEquipmentConnections.hpp"
#include "ModelObject/ZoneHVACEquipmentConnections_Impl.hpp"
#include "ModelObject/ZoneHVACEquipmentList.hpp"
#include "Node.hpp"
#include "Mixer/AirLoopHVACZoneMixer.hpp"
#include "Splitter/AirLoopHVACZoneSplitter.hpp"

#include <algorithm>
#include <utilities/core/Assert.hpp>
#include <utilities/core/Logger.hpp>
#include <utilities/idd/AirTerminal_SingleDuct_UserDefined_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
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
      auto equipmentList = zoneImpl->getZoneHVACEquipmentList();
      const auto equipment = equipmentList.equipment();
      return (std::ranges::find(equipment, terminal) == equipment.end()) || equipmentList.removeEquipment(terminal);
    }

  }  // namespace

  AirTerminalSingleDuctUserDefined::AirTerminalSingleDuctUserDefined(const Model& model)
    : StraightComponent(AirTerminalSingleDuctUserDefined::iddObjectType(), model) {
    OS_ASSERT(setNumberofPlantLoopConnections(0));
  }

  AirTerminalSingleDuctUserDefined::AirTerminalSingleDuctUserDefined(std::shared_ptr<detail::AirTerminalSingleDuctUserDefined_Impl> impl)
    : StraightComponent(std::move(impl)) {}

  IddObjectType AirTerminalSingleDuctUserDefined::iddObjectType() {
    return IddObjectType::AirTerminal_SingleDuct_UserDefined;
  }

  bool AirTerminalSingleDuctUserDefined::addToNode(Node& node) {
    return getImpl<detail::AirTerminalSingleDuctUserDefined_Impl>()->addToNode(node);
  }

  int AirTerminalSingleDuctUserDefined::numberofPlantLoopConnections() const {
    return getImpl<detail::AirTerminalSingleDuctUserDefined_Impl>()->numberofPlantLoopConnections();
  }

  bool AirTerminalSingleDuctUserDefined::setNumberofPlantLoopConnections(int numberofPlantLoopConnections) {
    return getImpl<detail::AirTerminalSingleDuctUserDefined_Impl>()->setNumberofPlantLoopConnections(numberofPlantLoopConnections);
  }

  // Detail implementations for the scalar accessors
  namespace detail {

    unsigned AirTerminalSingleDuctUserDefined_Impl::inletPort() const {
      return openstudio::AirTerminal_SingleDuct_UserDefinedFields::PrimaryAirInletNodeName;
    }

    unsigned AirTerminalSingleDuctUserDefined_Impl::outletPort() const {
      return openstudio::AirTerminal_SingleDuct_UserDefinedFields::PrimaryAirOutletNodeName;
    }

    boost::optional<ZoneHVACAirDistributionUnit> AirTerminalSingleDuctUserDefined_Impl::zoneHVACAirDistributionUnit() const {
      auto terminal = getObject<openstudio::epmodel::ModelObject>();
      for (const auto& source : terminal.getSources(openstudio::IddObjectType::ZoneHVAC_AirDistributionUnit)) {
        if (auto adu = source.optionalCast<openstudio::epmodel::ZoneHVACAirDistributionUnit>()) {
          return adu;
        }
      }
      return boost::none;
    }

    bool AirTerminalSingleDuctUserDefined_Impl::addToNode(Node& node) {
      return addToNode(node, AddToNodeFailureStage::None);
    }

    bool AirTerminalSingleDuctUserDefined_Impl::addToNode(Node& node, AddToNodeFailureStage failureStage) {
      if (node.model() != model()) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctUserDefined", "addToNode requires a node in the same model as the terminal.");
        return false;
      }

      if (getObject<openstudio::epmodel::HVACComponent>().loop()) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctUserDefined",
                 "Refusing to add an already-connected terminal to node '" << node.nameString() << "'.");
        return false;
      }

      auto airLoop = node.airLoopHVAC();
      if (!airLoop) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctUserDefined", "addToNode requires a node that resolves to an AirLoopHVAC context.");
        return false;
      }

      auto zoneSplitter = airLoop->zoneSplitter();
      const auto thisNode = node.cast<ModelObject>();
      const auto splitterOutlets = zoneSplitter.outletModelObjects();
      const auto splitterIt = std::ranges::find(splitterOutlets, thisNode);
      if (splitterIt == splitterOutlets.end()) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctUserDefined",
                 "addToNode requires the drop node to be a ZoneSplitter outlet node for the target AirLoopHVAC.");
        return false;
      }
      const auto splitterBranchIndex = static_cast<unsigned>(std::distance(splitterOutlets.begin(), splitterIt));

      auto airLoopImpl = airLoop->getImpl<detail::AirLoopHVAC_Impl>();
      OS_ASSERT(airLoopImpl);
      auto mixerInlet = airLoopImpl->effectiveDemandReturnNodeForBranchStart(node);
      if (!mixerInlet) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctUserDefined",
                 "addToNode requires one effective ZoneMixer return for the selected ZoneSplitter branch.");
        return false;
      }
      auto thermalZone = owningThermalZoneForBranchNode(model(), node);
      if ((*mixerInlet != thisNode) && !isServedZoneReturnNode(thermalZone, *mixerInlet)) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctUserDefined",
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

    bool AirTerminalSingleDuctUserDefined_Impl::removeFromLoop() {
      auto thisObject = getObject<openstudio::epmodel::ModelObject>();
      auto thermalZone = thermalZoneContainingTerminal(model(), thisObject);
      auto inletNode = inletModelObject();
      auto outletNode = outletModelObject();
      if (!thermalZone && outletNode) {
        if (auto outletZoneNode = outletNode->optionalCast<Node>()) {
          thermalZone = owningThermalZoneForBranchNode(model(), *outletZoneNode);
        }
      }

      const bool shouldRemoveTerminalInletNode = inletNode && outletNode && isDemandBranchStartComponent();

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

      if (!setPointer(inletPort(), openstudio::Handle(), false)) {
        return false;
      }
      if (!setPointer(outletPort(), openstudio::Handle(), false)) {
        return false;
      }

      if (shouldRemoveTerminalInletNode) {
        if (auto node = inletNode->optionalCast<openstudio::epmodel::Node>()) {
          node->remove();
        }
      }

      return removedFromAirLoop || static_cast<bool>(thermalZone) || cleanedADU;
    }

    int AirTerminalSingleDuctUserDefined_Impl::numberofPlantLoopConnections() const {
      const auto value = getInt(openstudio::AirTerminal_SingleDuct_UserDefinedFields::NumberofPlantLoopConnections, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirTerminalSingleDuctUserDefined_Impl::setNumberofPlantLoopConnections(int numberofPlantLoopConnections) {
      return setInt(openstudio::AirTerminal_SingleDuct_UserDefinedFields::NumberofPlantLoopConnections, numberofPlantLoopConnections);
    }

  }  // namespace detail

}  // namespace epmodel
}  // namespace openstudio
