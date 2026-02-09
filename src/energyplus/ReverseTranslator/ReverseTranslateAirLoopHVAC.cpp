/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "../ReverseTranslator.hpp"

#include "../../model/AirLoopHVAC.hpp"
#include "../../model/AirLoopHVAC_Impl.hpp"
#include "../../model/HVACComponent.hpp"
#include "../../model/HVACComponent_Impl.hpp"
#include "../../model/Node.hpp"
#include "../../model/Node_Impl.hpp"
#include "../../model/PortList.hpp"
#include "../../model/PortList_Impl.hpp"
#include "../../model/Space.hpp"
#include "../../model/Space_Impl.hpp"
#include "../../model/Splitter.hpp"
#include "../../model/ThermalZone.hpp"
#include "../../model/ThermalZone_Impl.hpp"
#include "../../model/AirLoopHVACOutdoorAirSystem.hpp"
#include "../../model/AirLoopHVACOutdoorAirSystem_Impl.hpp"
#include "../../model/ScheduleCompact.hpp"
#include "../../model/ScheduleCompact_Impl.hpp"
#include "../../model/AirTerminalSingleDuctConstantVolumeNoReheat.hpp"
#include "../../model/AirTerminalSingleDuctConstantVolumeNoReheat_Impl.hpp"
#include <utilities/idd/AirLoopHVAC_FieldEnums.hxx>
#include <utilities/idd/AirLoopHVAC_ZoneMixer_FieldEnums.hxx>
#include <utilities/idd/ZoneHVAC_AirDistributionUnit_FieldEnums.hxx>
#include <utilities/idd/BranchList_FieldEnums.hxx>
#include <utilities/idd/Branch_FieldEnums.hxx>
#include <utilities/idd/NodeList_FieldEnums.hxx>
#include <utilities/idd/ConnectorList_FieldEnums.hxx>
#include <utilities/idd/ZoneHVAC_EquipmentConnections_FieldEnums.hxx>
#include "../../utilities/idd/IddEnums.hpp"
#include <utilities/idd/IddEnums.hxx>
#include "../../utilities/idf/WorkspaceExtensibleGroup.hpp"
#include "utilities/core/Compare.hpp"

using namespace openstudio::model;

namespace openstudio {

namespace energyplus {

  OptionalModelObject ReverseTranslator::translateAirLoopHVAC(const WorkspaceObject& workspaceObject) {
    if (workspaceObject.iddObject().type() != IddObjectType::AirLoopHVAC) {
      LOG(Error, "WorkspaceObject is not IddObjectType: AirLoopHVAC");
      return boost::none;
    }

    // Validate required-fields are present and valid, bail early if not
    const std::string supplyInletNodeName = workspaceObject.getString(AirLoopHVACFields::SupplySideInletNodeName).value_or("");
    if (supplyInletNodeName.empty()) {
      LOG(Error, workspaceObject.briefDescription() << ": Missing required field 'Supply Inlet Node Name'");
      return boost::none;
    }

    const std::string supplyOutletNodeorNodeListName = workspaceObject.getString(AirLoopHVACFields::SupplySideOutletNodeNames).value_or("");
    if (supplyOutletNodeorNodeListName.empty()) {
      LOG(Error, workspaceObject.briefDescription() << ": Missing required field 'Supply Outlet Node Names'");
      return boost::none;
    }

    const std::string demandInletNodeorNodeListName = workspaceObject.getString(AirLoopHVACFields::DemandSideInletNodeNames).value_or("");
    if (demandInletNodeorNodeListName.empty()) {
      LOG(Error, workspaceObject.briefDescription() << ": Missing required field 'Demand Inlet Node Names'");
      return boost::none;
    }

    const std::string demandOutletNodeName = workspaceObject.getString(AirLoopHVACFields::DemandSideOutletNodeName).value_or("");
    if (demandOutletNodeName.empty()) {
      LOG(Error, workspaceObject.briefDescription() << ": Missing required field 'Demand Outlet Node Name'");
      return boost::none;
    }

    OptionalWorkspaceObject supplyBranchList_ = workspaceObject.getTarget(AirLoopHVACFields::BranchListName);
    if (!supplyBranchList_) {
      LOG(Error, workspaceObject.briefDescription() << ": Missing required field 'Branch List Name'");
      return boost::none;
    }
    auto supplyBranchList = std::move(*supplyBranchList_);

    OptionalWorkspaceObject connectorList_ = workspaceObject.getTarget(AirLoopHVACFields::ConnectorListName);

    // TODO: this fails to grab a potential NodeList object... issue is likely that the Name field of the NodeList (and OutdoorAir:Node too)
    // has `\type node` instead of being `\reference node`
    // workspaceObject.getTarget(AirLoopHVACFields::SupplySideOutletNodeorNodeListName)
    OptionalWorkspaceObject supplyOutletNodeList_ = m_workspace.getObjectByTypeAndName(IddObjectType::NodeList, supplyOutletNodeorNodeListName);
    OptionalWorkspaceObject demandInletNodeList_ = m_workspace.getObjectByTypeAndName(IddObjectType::NodeList, demandInletNodeorNodeListName);

    std::vector<std::string> supplyOutletNodeNames;
    std::vector<std::string> demandInletNodeNames;

    // Determine if dual duct or not
    bool dualDuct = false;
    bool hasConnectorList = connectorList_.has_value();
    std::string supplySplitterName;
    const unsigned numSupplyBranches = supplyBranchList.numExtensibleGroups();

    // Valid are 1 (main only) and 3 (main + hot + cold = 3)
    if (numSupplyBranches == 1) {
      dualDuct = false;
      if (hasConnectorList) {
        LOG(Error, workspaceObject.briefDescription() << ", Connector List should not be present for single duct system.");
        return boost::none;
      }
      if (supplyOutletNodeList_.has_value()) {
        if (supplyOutletNodeList_->numExtensibleGroups() > 1) {
          LOG(Error, supplyOutletNodeList_->briefDescription() << ": Supply Outlet Node List has more than one node listed, only the first will be "
                                                                  "used. Single duct systems should only have one supply outlet node.");
        }
        supplyOutletNodeNames.push_back(
          supplyOutletNodeList_->getExtensibleGroup(0).getString(NodeListExtensibleFields::NodeName).value_or(supplyOutletNodeorNodeListName));
      } else {
        supplyOutletNodeNames.push_back(supplyOutletNodeorNodeListName);
      }
      if (demandInletNodeList_.has_value()) {
        if (demandInletNodeList_->numExtensibleGroups() > 1) {
          LOG(Error, demandInletNodeList_->briefDescription() << ": Demand Inlet Node List has more than one node listed, only the first will be "
                                                                 "used. Single duct systems should only have one demand inlet node.");
        }
        demandInletNodeNames.push_back(
          demandInletNodeList_->getExtensibleGroup(0).getString(NodeListExtensibleFields::NodeName).value_or(demandInletNodeorNodeListName));
      } else {
        demandInletNodeNames.push_back(demandInletNodeorNodeListName);
      }
    } else if (numSupplyBranches == 3) {
      dualDuct = true;
      if (!hasConnectorList) {
        LOG(Error, workspaceObject.briefDescription() << ", Connector List is required for dual duct system.");
        return boost::none;
      }
      if (connectorList_->numExtensibleGroups() != 1) {
        LOG(Error, connectorList_->briefDescription() << ": Connector List should have exactly one extensible group for dual duct system, but it has "
                                                      << connectorList_->numExtensibleGroups() << ".");
        return boost::none;
      }
      auto connectorEg = connectorList_->getExtensibleGroup(0);
      supplySplitterName = connectorEg.getString(ConnectorListExtensibleFields::ConnectorName).value_or("");
      if (!openstudio::istringEqual(connectorEg.getString(ConnectorListExtensibleFields::ConnectorObjectType).value_or(""), "Connector:Splitter")) {
        LOG(Error, connectorList_->briefDescription() << ": Connector Object Type should be 'Connector:Splitter' for dual duct system.");
        return boost::none;
      }

      if (supplyOutletNodeList_.has_value()) {
        const unsigned numSupplyOutletNodes = supplyOutletNodeList_->numExtensibleGroups();
        if (numSupplyOutletNodes < 2) {
          LOG(Error, supplyOutletNodeList_->briefDescription()
                       << ": Supply Outlet Node List should have two nodes listed for dual duct system, one for each branch.");
          return boost::none;
        } else if (numSupplyOutletNodes > 2) {
          LOG(Error, supplyOutletNodeList_->briefDescription() << ": Supply Outlet Node List has more than two nodes listed, only the first two will "
                                                                  "be used. Dual duct systems should only have two supply outlet nodes.");
        }
        for (unsigned i = 0; const auto& eg : supplyOutletNodeList_->extensibleGroups()) {
          if (i >= 2) {
            break;
          }
          boost::optional<std::string> nodeName = eg.getString(NodeListExtensibleFields::NodeName);
          if (nodeName && !nodeName->empty()) {
            supplyOutletNodeNames.push_back(*nodeName);
            ++i;
          }
        }
      } else {
        LOG(Error, workspaceObject.briefDescription()
                     << ": For dual duct systems, Supply Outlet Node Names should reference a NodeList with two nodes, one for each branch.");
        return boost::none;
      }

      if (demandInletNodeList_.has_value()) {
        const unsigned numDemandInletNodes = demandInletNodeList_->numExtensibleGroups();
        if (numDemandInletNodes < 2) {
          LOG(Error, demandInletNodeList_->briefDescription()
                       << ": Demand Inlet Node List should have two nodes listed for dual duct system, one for each branch.");
          return boost::none;
        } else if (numDemandInletNodes > 2) {
          LOG(Error, demandInletNodeList_->briefDescription() << ": Demand Inlet Node List has more than two nodes listed, only the first two will "
                                                                 "be used. Dual duct systems should only have two demand inlet nodes.");
        }
        for (unsigned i = 0; const auto& eg : demandInletNodeList_->extensibleGroups()) {
          if (i >= 2) {
            break;
          }
          boost::optional<std::string> nodeName = eg.getString(NodeListExtensibleFields::NodeName);
          if (nodeName && !nodeName->empty()) {
            demandInletNodeNames.push_back(*nodeName);
            ++i;
          }
        }
      } else {
        LOG(Error, workspaceObject.briefDescription()
                     << ": For dual duct systems, Demand Inlet Node Names should reference a NodeList with two nodes, one for each branch.");
        return boost::none;
      }
      // Invalid cases:
    } else if (numSupplyBranches == 0) {
      LOG(Error, workspaceObject.briefDescription() << ", Air Loop HVAC objects must have at least one supply branch.");
      return boost::none;
    } else if (numSupplyBranches == 2) {
      LOG(Error, workspaceObject.briefDescription()
                   << ", Air Loop HVAC objects cannot have two branches only (if single duct: 1 (main), if dual duct 3 (main + hot + cold)");
      return boost::none;
    } else if (numSupplyBranches > 3) {
      LOG(Error, workspaceObject.briefDescription() << ", Three duct systems are not supported.");
      return boost::none;
    }

    // We're valid, time to assign
    openstudio::model::AirLoopHVAC airLoopHVAC(m_model, dualDuct);
    airLoopHVAC.setName(workspaceObject.nameString());

    // One node
    Node supplyInletNode = airLoopHVAC.supplyInletNode();
    Node demandOutletNode = airLoopHVAC.demandOutletNode();
    supplyInletNode.setName(supplyInletNodeName);
    demandOutletNode.setName(demandOutletNodeName);

    // Potentially more than one
    for (size_t i = 0; auto& node : airLoopHVAC.supplyOutletNodes()) {
      node.setName(supplyOutletNodeNames[i]);
      ++i;
    }
    for (size_t i = 0; auto& node : airLoopHVAC.supplyOutletNodes()) {
      node.setName(supplyOutletNodeNames[i]);
      ++i;
    }
    if (dualDuct) {
      airLoopHVAC.supplySplitter()->setName(supplySplitterName);
    }

    // Design Supply Air Flow Rate: Autosizable, defaults to 0 (weirdly)
    if (auto val_ = workspaceObject.getDouble(AirLoopHVACFields::DesignSupplyAirFlowRate, true)) {
      airLoopHVAC.setDesignSupplyAirFlowRate(*val_);
    } else {
      auto s_ = workspaceObject.getString(AirLoopHVACFields::DesignSupplyAirFlowRate, false, true);
      OS_ASSERT(s_);  // Shouldn't happen
      if (istringEqual(s_.get(), "Autosize")) {
        airLoopHVAC.autosizeDesignSupplyAirFlowRate();
      } else {
        LOG(Error, workspaceObject.briefDescription() << ": Invalid value for DesignSupplyAirFlowRate: " << s_.get());
      }
    }

    if (!dualDuct) {
      if (auto supplyBranch_ =
            supplyBranchList.getExtensibleGroup(0).cast<WorkspaceExtensibleGroup>().getTarget(BranchListExtensibleFields::BranchName)) {
        Node supplyOutletNode = airLoopHVAC.supplyOutletNode();
        populateBranch(*supplyBranch_, supplyOutletNode, false, true);
      } else {
        LOG(Error, supplyBranchList.briefDescription() << ": Missing supply branch");
        return boost::none;
      }
    } else {
      // For dual duct we want to reverse the order of the components on the main branch, since the connection node is on the supply inlet node side, and not the outlet node side like in the single duct case
      if (auto supplyBranch_ =
            supplyBranchList.getExtensibleGroup(0).cast<WorkspaceExtensibleGroup>().getTarget(BranchListExtensibleFields::BranchName)) {
        Node supplyInletNode = airLoopHVAC.supplyInletNode();
        bool reverseOrder = true;
        populateBranch(*supplyBranch_, supplyInletNode, reverseOrder, true);
      } else {
        LOG(Error, supplyBranchList.briefDescription() << ": Missing main supply branch");
        return boost::none;
      }

      for (unsigned i = 1; i < numSupplyBranches; ++i) {
        if (auto supplyBranch_ =
              supplyBranchList.getExtensibleGroup(i).cast<WorkspaceExtensibleGroup>().getTarget(BranchListExtensibleFields::BranchName)) {
          Node connectionNode = airLoopHVAC.supplyOutletNodes()[i - 1];
          bool reverseOrder = false;
          populateBranch(*supplyBranch_, connectionNode, reverseOrder, true);
        } else {
          LOG(Error, supplyBranchList.briefDescription() << ": Missing supply branch at index " << i);
          return boost::none;
        }
      }
    }

    // March through the zone on the demand side and add branches for them.
    // We want to start by adding the stuff between splitter and mixer, or in the dual duct case, the demandOutletNodes() aren't yet initialized and
    // there is only one
    // Find the zone mixer for this air loop
    std::vector<WorkspaceObject> _airLoopHVACZoneMixers;
    _airLoopHVACZoneMixers = m_workspace.getObjectsByType(IddObjectType::AirLoopHVAC_ZoneMixer);

    boost::optional<WorkspaceObject> _airLoopHVACZoneMixer;
    for (const auto& elem : _airLoopHVACZoneMixers) {
      boost::optional<std::string> mixerOutletNodeName;
      mixerOutletNodeName = elem.getString(AirLoopHVAC_ZoneMixerFields::OutletNodeName);

      if (mixerOutletNodeName && mixerOutletNodeName.get() == demandOutletNodeName) {
        _airLoopHVACZoneMixer = elem;
        break;
      }
    }
    if (_airLoopHVACZoneMixer) {
      for (int i = 2; _airLoopHVACZoneMixer->getString(i); i++) {

        std::vector<WorkspaceObject> _zoneHVACEquipmentConnections;

        std::string mixerInletNodeName = _airLoopHVACZoneMixer->getString(i).get();

        _zoneHVACEquipmentConnections = m_workspace.getObjectsByType(IddObjectType::ZoneHVAC_EquipmentConnections);

        for (const auto& _zoneHVACEquipmentConnection : _zoneHVACEquipmentConnections) {

          OptionalString returnAirNodeName =
            _zoneHVACEquipmentConnection.getString(ZoneHVAC_EquipmentConnectionsFields::ZoneReturnAirNodeorNodeListName);
          OptionalString inletAirNodeName =
            _zoneHVACEquipmentConnection.getString(ZoneHVAC_EquipmentConnectionsFields::ZoneAirInletNodeorNodeListName);
          OptionalString zoneName = _zoneHVACEquipmentConnection.getString(ZoneHVAC_EquipmentConnectionsFields::ZoneName);
          OptionalString zoneEquipListName =
            _zoneHVACEquipmentConnection.getString(ZoneHVAC_EquipmentConnectionsFields::ZoneConditioningEquipmentListName);

          OptionalWorkspaceObject _zone;
          OptionalWorkspaceObject _zoneEquipmentList;
          OptionalWorkspaceObject _zoneEquipment;
          OptionalWorkspaceObject _airTerminal;

          if (returnAirNodeName && returnAirNodeName.get() == mixerInletNodeName && zoneName && zoneEquipListName) {
            _zone = m_workspace.getObjectByTypeAndName(IddObjectType::Zone, *zoneName);

            _zoneEquipmentList = m_workspace.getObjectByTypeAndName(IddObjectType::ZoneHVAC_EquipmentList, zoneEquipListName.get());

            if (!_zone) {
              LOG(Error, airLoopHVAC.briefDescription() << " is connected to a zone that does not exist.");

              break;
            }

            if (!_zoneEquipmentList) {
              LOG(Error, _zone->briefDescription() << " does not have a zone equipment list, but it is attached to a loop.");

              break;
            }

            OptionalString optionalString;
            for (int j = 1; (optionalString = _zoneEquipmentList->getString(j)); j = j + 4) {
              boost::optional<std::string> zoneEquipmentName = _zoneEquipmentList->getString(j + 1);
              // Possible Zone Equipment
              //
              // ZoneHVAC:AirDistributionUnit
              // AirTerminal:SingleDuct:ConstantVolume:NoReheat (previously named AirTerminal:SingleDuct:Uncontrolled before 9.0.0)
              // ZoneHVAC:EnergyRecoveryVentilator
              // ZoneHVAC:FourPipeFanCoil
              // ZoneHVAC:OutdoorAirUnit
              // ZoneHVAC:PackagedTerminalAirConditioner
              // ZoneHVAC:PackagedTerminalHeatPump
              // ZoneHVAC:UnitHeater
              // ZoneHVAC:UnitVentilator
              // ZoneHVAC:VentilatedSlab
              // ZoneHVAC:WaterToAirHeatPump
              // ZoneHVAC:WindowAirConditioner
              // ZoneHVAC:Baseboard:RadiantConvective:Electric
              // ZoneHVAC:Baseboard:RadiantConvective:Water
              // ZoneHVAC:Baseboard:RadiantConvective:Steam
              // ZoneHVAC:Baseboard:Convective:Electric
              // ZoneHVAC:Baseboard:Convective:Water
              // ZoneHVAC:HighTemperatureRadiant
              // ZoneHVAC:LowTemperatureRadiant:VariableFlow
              // ZoneHVAC:LowTemperatureRadiant:ConstantFlow
              // ZoneHVAC:LowTemperatureRadiant:Electric
              // ZoneHVAC:Dehumidifier:DX
              // ZoneHVAC:IdealLoadsAirSystem
              // Fan:ZoneExhaust
              // WaterHeater:HeatPump
              //
              if (zoneEquipmentName) {
                // TODO: this block shouldn't happen. Unlike AirTerminal:SingleDuct:Uncontrolled (deprecated in 9.0.0, removed in 9.2.0)
                // this object cannot be placed directly on a branch and uses a ZoneHVAC:AirDistributionUnit
                if (istringEqual(optionalString.get(), "AirTerminal:SingleDuct:ConstantVolume:NoReheat")) {
                  _airTerminal =
                    m_workspace.getObjectByTypeAndName(IddObjectType::AirTerminal_SingleDuct_ConstantVolume_NoReheat, zoneEquipmentName.get());

                  break;
                } else if (istringEqual(optionalString.get(), "ZoneHVAC:AirDistributionUnit")) {
                  boost::optional<WorkspaceObject> _airDistributionUnit =
                    m_workspace.getObjectByTypeAndName(IddObjectType::ZoneHVAC_AirDistributionUnit, zoneEquipmentName.get());

                  if (_airDistributionUnit) {
                    boost::optional<std::string> airUnitName;
                    boost::optional<std::string> airUnitType;

                    airUnitType = _airDistributionUnit->getString(ZoneHVAC_AirDistributionUnitFields::AirTerminalObjectType);
                    airUnitName = _airDistributionUnit->getString(ZoneHVAC_AirDistributionUnitFields::AirTerminalName);

                    if (airUnitName && airUnitType) {
                      _airTerminal = m_workspace.getObjectByTypeAndName(IddObjectType(airUnitType.get()), airUnitName.get());
                    }
                  }

                  break;
                }
              }
            }

            OptionalModelObject airTerminalModelObject;
            OptionalSpace space;
            OptionalStraightComponent straightComponent;
            OptionalThermalZone thermalZone;

            if (_airTerminal) {
              airTerminalModelObject = translateAndMapWorkspaceObject(_airTerminal.get());
            }

            if (_zone) {
              if (OptionalModelObject mo = translateAndMapWorkspaceObject(_zone.get())) {
                space = mo->optionalCast<Space>();
              }
            }

            if (space) {
              thermalZone = space->thermalZone();
            }

            if (airTerminalModelObject) {
              straightComponent = airTerminalModelObject->optionalCast<StraightComponent>();
            }

            bool success = false;

            if (straightComponent && thermalZone) {
              success = airLoopHVAC.addBranchForZone(thermalZone.get(), straightComponent.get());
            } else if (thermalZone) {
              Model m;

              success = airLoopHVAC.addBranchForZone(thermalZone.get(), boost::none);
            }

            if (success) {
              if (inletAirNodeName) {
                thermalZone->inletPortList().airLoopHVACModelObject()->cast<Node>().setName(inletAirNodeName.get());
              }
              if (returnAirNodeName) {
                thermalZone->returnAirModelObject()->cast<Node>().setName(returnAirNodeName.get());
              }
            }
          }
        }
      }
    }

    // TODO: handle ControllerList for Coil:Cooling:Water etc

    return airLoopHVAC;
  }

}  // namespace energyplus

}  // namespace openstudio
