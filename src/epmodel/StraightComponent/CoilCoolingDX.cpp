/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/CoilCoolingDX.hpp"
#include "StraightComponent/CoilCoolingDX_Impl.hpp"

#include "Model.hpp"
#include "ModelObject/CoilSystemCoolingDX.hpp"
#include "ModelObject/CoilSystemCoolingDX_Impl.hpp"
#include "ResourceObject/CoilCoolingDXCurveFitPerformance.hpp"
#include "ResourceObject/CoilCoolingDXCurveFitPerformance_Impl.hpp"
#include "ResourceObject/CoilCoolingDXCurveFitOperatingMode.hpp"
#include "ResourceObject/CoilCoolingDXCurveFitOperatingMode_Impl.hpp"
#include "Loop/AirLoopHVAC.hpp"
#include "HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "Node.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"
#include "Schedule/ScheduleConstant.hpp"
#include "ThermalZone.hpp"
#include "ThermalZone_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/Coil_Cooling_DX_FieldEnums.hxx>
#include <utilities/idd/CoilSystem_Cooling_DX_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/OutdoorAir_NodeList_FieldEnums.hxx>
#include <utilities/idf/WorkspaceExtensibleGroup.hpp>

namespace openstudio {
namespace epmodel {

  namespace {

    std::vector<CoilSystemCoolingDX> coilSystemsFor(const Model& model, const Handle& coilHandle) {
      std::vector<CoilSystemCoolingDX> result;
      for (const auto& system : model.getConcreteModelObjects<CoilSystemCoolingDX>()) {
        auto linkedCoil = system.coolingCoil();
        if (linkedCoil && linkedCoil->handle() == coilHandle) {
          result.push_back(system);
        }
      }
      return result;
    }

    void applyConstructorDefaults(CoilCoolingDX& coil) {
      ScheduleConstant alwaysOn(coil.model());
      OS_ASSERT(alwaysOn.setValue(1.0));
      OS_ASSERT(coil.setAvailabilitySchedule(alwaysOn));
      OS_ASSERT(coil.setCondenserInletNodeName(coil.nameString() + " Condenser Inlet Node"));
      OS_ASSERT(coil.setCondenserOutletNodeName(coil.nameString() + " Condenser Outlet Node"));
    }

    void applyDefaultPerformanceDefaults(CoilCoolingDXCurveFitPerformance& performance, const Model& model) {
      CoilCoolingDXCurveFitOperatingMode baseOperatingMode(model);
      baseOperatingMode.autosizeRatedGrossTotalCoolingCapacity();
      baseOperatingMode.autosizeRatedEvaporatorAirFlowRate();
      baseOperatingMode.autosizeRatedCondenserAirFlowRate();
      OS_ASSERT(baseOperatingMode.setMaximumCyclingRate(0.0));
      OS_ASSERT(baseOperatingMode.setRatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity(0.0));
      OS_ASSERT(baseOperatingMode.setLatentCapacityTimeConstant(0.0));
      OS_ASSERT(baseOperatingMode.setNominalTimeforCondensateRemovaltoBegin(0.0));
      OS_ASSERT(!baseOperatingMode.applyLatentDegradationtoSpeedsGreaterthan1());
      OS_ASSERT(baseOperatingMode.setCondenserType("AirCooled"));
      baseOperatingMode.autosizeNominalEvaporativeCondenserPumpPower();

      OS_ASSERT(performance.setCrankcaseHeaterCapacity(0.0));
      OS_ASSERT(performance.setMinimumOutdoorDryBulbTemperatureforCompressorOperation(-25.0));
      OS_ASSERT(performance.setMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation(10.0));
      OS_ASSERT(performance.setUnitInternalStaticAirPressure(773.3));
      OS_ASSERT(performance.setCapacityControlMethod("Discrete"));
      OS_ASSERT(performance.setEvaporativeCondenserBasinHeaterCapacity(0.0));
      OS_ASSERT(performance.setEvaporativeCondenserBasinHeaterSetpointTemperature(2.0));
      OS_ASSERT(performance.setCompressorFuelType("Electricity"));
      OS_ASSERT(performance.setBaseOperatingMode(baseOperatingMode));
    }

  }  // namespace

  CoilCoolingDX::CoilCoolingDX(const Model& model) : StraightComponent(CoilCoolingDX::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::CoilCoolingDX_Impl>());

    applyConstructorDefaults(*this);

    CoilCoolingDXCurveFitPerformance performance(model);
    applyDefaultPerformanceDefaults(performance, model);
    OS_ASSERT(setPerformanceObject(performance));
  }

  CoilCoolingDX::CoilCoolingDX(const Model& model, const CoilCoolingDXCurveFitPerformance& coilCoolingDXCurveFitPerformance)
    : StraightComponent(CoilCoolingDX::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::CoilCoolingDX_Impl>());

    applyConstructorDefaults(*this);
    OS_ASSERT(setPerformanceObject(coilCoolingDXCurveFitPerformance));
  }

  CoilCoolingDX::CoilCoolingDX(std::shared_ptr<detail::CoilCoolingDX_Impl> impl) : StraightComponent(std::move(impl)) {}

  IddObjectType CoilCoolingDX::iddObjectType() {
    return IddObjectType::Coil_Cooling_DX;
  }

  bool CoilCoolingDX::addToNode(Node& node) {
    return getImpl<detail::CoilCoolingDX_Impl>()->addToNode(node);
  }

  Schedule CoilCoolingDX::availabilitySchedule() const {
    return getImpl<detail::CoilCoolingDX_Impl>()->availabilitySchedule();
  }

  bool CoilCoolingDX::setAvailabilitySchedule(Schedule& schedule) {
    return getImpl<detail::CoilCoolingDX_Impl>()->setAvailabilitySchedule(schedule);
  }

  boost::optional<ThermalZone> CoilCoolingDX::condenserZone() const {
    return getImpl<detail::CoilCoolingDX_Impl>()->condenserZone();
  }

  bool CoilCoolingDX::setCondenserZone(const ThermalZone& thermalZone) {
    return getImpl<detail::CoilCoolingDX_Impl>()->setCondenserZone(thermalZone);
  }

  void CoilCoolingDX::resetCondenserZone() {
    getImpl<detail::CoilCoolingDX_Impl>()->resetCondenserZone();
  }

  CoilCoolingDXCurveFitPerformance CoilCoolingDX::performanceObject() const {
    return getImpl<detail::CoilCoolingDX_Impl>()->performanceObject();
  }

  bool CoilCoolingDX::setPerformanceObject(const CoilCoolingDXCurveFitPerformance& coilCoolingDXCurveFitPerformance) {
    return getImpl<detail::CoilCoolingDX_Impl>()->setPerformanceObject(coilCoolingDXCurveFitPerformance);
  }

  std::string CoilCoolingDX::condenserInletNodeName() const {
    return getImpl<detail::CoilCoolingDX_Impl>()->condenserInletNodeName();
  }

  bool CoilCoolingDX::setCondenserInletNodeName(const std::string& condenserInletNodeName) {
    return getImpl<detail::CoilCoolingDX_Impl>()->setCondenserInletNodeName(condenserInletNodeName);
  }

  std::string CoilCoolingDX::condenserOutletNodeName() const {
    return getImpl<detail::CoilCoolingDX_Impl>()->condenserOutletNodeName();
  }

  bool CoilCoolingDX::setCondenserOutletNodeName(const std::string& condenserOutletNodeName) {
    return getImpl<detail::CoilCoolingDX_Impl>()->setCondenserOutletNodeName(condenserOutletNodeName);
  }
}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    unsigned CoilCoolingDX_Impl::inletPort() const {
      return openstudio::Coil_Cooling_DXFields::EvaporatorInletNodeName;
    }

    unsigned CoilCoolingDX_Impl::outletPort() const {
      return openstudio::Coil_Cooling_DXFields::EvaporatorOutletNodeName;
    }

    boost::optional<std::string> CoilCoolingDX_Impl::setName(const std::string& newName, bool checkValidity) {
      const auto oldName = getObject<ModelObject>().nameString();
      const auto oldCondenserInletNodeName = condenserInletNodeName();
      const auto oldCondenserOutletNodeName = condenserOutletNodeName();
      const bool renameCondenserInlet = openstudio::istringEqual(oldCondenserInletNodeName, oldName + " Condenser Inlet Node");
      const bool renameCondenserOutlet = openstudio::istringEqual(oldCondenserOutletNodeName, oldName + " Condenser Outlet Node");

      auto result = openstudio::detail::WorkspaceObject_Impl::setName(newName, checkValidity);
      if (!result) {
        return boost::none;
      }

      if (renameCondenserInlet && !setCondenserInletNodeName(*result + " Condenser Inlet Node")) {
        OS_ASSERT(openstudio::detail::WorkspaceObject_Impl::setName(oldName, false));
        return boost::none;
      }
      if (renameCondenserOutlet && !setCondenserOutletNodeName(*result + " Condenser Outlet Node")) {
        if (renameCondenserInlet) {
          OS_ASSERT(setCondenserInletNodeName(oldCondenserInletNodeName));
        }
        OS_ASSERT(openstudio::detail::WorkspaceObject_Impl::setName(oldName, false));
        return boost::none;
      }

      return result;
    }

    bool CoilCoolingDX_Impl::addToNode(Node& node) {
      auto thisCoil = getObject<CoilCoolingDX>();
      if (thisCoil.containingHVACComponent()) {
        return false;
      }

      auto airLoop = node.airLoopHVAC();

      if (!(airLoop && airLoop->supplyComponent(node.handle()))) {
        return false;
      }

      auto systems = coilSystemsFor(model(), handle());
      if (systems.size() > 1u) {
        return false;
      }

      boost::optional<CoilSystemCoolingDX> system;
      bool createdSystem = false;
      if (systems.empty()) {
        // A bare DX coil is not valid branch equipment in EnergyPlus. Refuse
        // to replace legacy live topology unless the adapter already owns it.
        if (StraightComponent_Impl::airLoopHVAC()) {
          return false;
        }

        CoilSystemCoolingDX newSystem(model());
        if (!newSystem.setName(thisCoil.nameString() + " CoilSystem")) {
          newSystem.remove();
          return false;
        }
        auto systemImpl = newSystem.getImpl<CoilSystemCoolingDX_Impl>();
        OS_ASSERT(systemImpl);
        if (!systemImpl->configureForCoolingCoil(thisCoil)) {
          newSystem.remove();
          return false;
        }
        system = newSystem;
        createdSystem = true;
      } else {
        system = systems.front();
        auto systemImpl = system->getImpl<CoilSystemCoolingDX_Impl>();
        OS_ASSERT(systemImpl);
        if (!systemImpl->isCoherentForCoolingCoil(thisCoil)) {
          return false;
        }
      }

      if (system->addToNode(node)) {
        return true;
      }
      if (createdSystem) {
        system->remove();
      }
      return false;
    }

    boost::optional<CoilSystemCoolingDX> CoilCoolingDX_Impl::coilSystemCoolingDX() const {
      auto systems = coilSystemsFor(model(), handle());
      if (systems.size() == 1u) {
        return systems.front();
      }
      return boost::none;
    }

    bool CoilCoolingDX_Impl::removeFromLoop() {
      auto systems = coilSystemsFor(model(), handle());
      if (systems.size() > 1u) {
        return false;
      }
      if (systems.empty()) {
        return StraightComponent_Impl::removeFromLoop();
      }
      auto thisCoil = getObject<CoilCoolingDX>();
      auto systemImpl = systems.front().getImpl<CoilSystemCoolingDX_Impl>();
      OS_ASSERT(systemImpl);
      if (!systemImpl->isCoherentForCoolingCoil(thisCoil)) {
        return false;
      }
      return systems.front().removeFromLoop();
    }

    void CoilCoolingDX_Impl::disconnect() {
      auto systems = coilSystemsFor(model(), handle());
      if (systems.size() > 1u) {
        return;
      }
      if (systems.size() == 1u) {
        auto thisCoil = getObject<CoilCoolingDX>();
        auto systemImpl = systems.front().getImpl<CoilSystemCoolingDX_Impl>();
        OS_ASSERT(systemImpl);
        if (!systemImpl->isCoherentForCoolingCoil(thisCoil)) {
          return;
        }
        systems.front().disconnect();
        return;
      }
      StraightComponent_Impl::disconnect();
    }

    std::vector<IdfObject> CoilCoolingDX_Impl::remove() {
      if (!isRemovable()) {
        return {};
      }

      auto systems = coilSystemsFor(model(), handle());
      if (systems.size() > 1u) {
        return {};
      }

      std::vector<IdfObject> result;
      if (systems.size() == 1u) {
        auto system = systems.front();
        auto thisCoil = getObject<CoilCoolingDX>();
        auto systemImpl = system.getImpl<CoilSystemCoolingDX_Impl>();
        OS_ASSERT(systemImpl);
        if (!systemImpl->isCoherentForCoolingCoil(thisCoil)) {
          return {};
        }
        if ((system.airLoopHVAC() || system.airLoopHVACOutdoorAirSystem()) && !system.removeFromLoop()) {
          return {};
        }
        auto removedSystem = system.remove();
        if (model().getObject(system.handle())) {
          return {};
        }
        result.insert(result.end(), removedSystem.begin(), removedSystem.end());
      }

      const auto condenserInlet = condenserInletNodeName();
      removeUnusedCondenserOutdoorAirNode(condenserInlet);
      auto removedCoil = HVACComponent_Impl::remove();
      result.insert(result.end(), removedCoil.begin(), removedCoil.end());
      return result;
    }

    std::vector<ModelObject> CoilCoolingDX_Impl::children() const {
      return {performanceObject()};
    }

    Schedule CoilCoolingDX_Impl::availabilitySchedule() const {
      auto value = getObject<ModelObject>().getModelObjectTarget<Schedule>(openstudio::Coil_Cooling_DXFields::AvailabilityScheduleName);
      if (!value) {
        value = this->model().alwaysOnDiscreteSchedule();
        OS_ASSERT(value);
        const_cast<CoilCoolingDX_Impl*>(this)->setAvailabilitySchedule(*value);
        value = getObject<ModelObject>().getModelObjectTarget<Schedule>(openstudio::Coil_Cooling_DXFields::AvailabilityScheduleName);
      }
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingDX_Impl::setAvailabilitySchedule(Schedule& schedule) {
      if (schedule.model() != model()) {
        return false;
      }
      auto systems = coilSystemsFor(model(), handle());
      if (systems.size() > 1u) {
        return false;
      }

      const auto thisCoil = getObject<ModelObject>();
      const auto oldSchedule = thisCoil.getTarget(openstudio::Coil_Cooling_DXFields::AvailabilityScheduleName);
      if (!setPointer(openstudio::Coil_Cooling_DXFields::AvailabilityScheduleName, schedule.handle(), false)) {
        return false;
      }
      if (systems.size() == 1u && !systems.front().setPointer(openstudio::CoilSystem_Cooling_DXFields::AvailabilityScheduleName, schedule.handle())) {
        OS_ASSERT(setPointer(openstudio::Coil_Cooling_DXFields::AvailabilityScheduleName, oldSchedule ? oldSchedule->handle() : Handle(), false));
        return false;
      }
      return true;
    }

    boost::optional<ThermalZone> CoilCoolingDX_Impl::condenserZone() const {
      return getObject<ModelObject>().getModelObjectTarget<ThermalZone>(openstudio::Coil_Cooling_DXFields::CondenserZoneName);
    }

    bool CoilCoolingDX_Impl::setCondenserZone(const ThermalZone& thermalZone) {
      return setPointer(openstudio::Coil_Cooling_DXFields::CondenserZoneName, thermalZone.handle());
    }

    void CoilCoolingDX_Impl::resetCondenserZone() {
      bool result = setString(openstudio::Coil_Cooling_DXFields::CondenserZoneName, "");
      OS_ASSERT(result);
    }

    CoilCoolingDXCurveFitPerformance CoilCoolingDX_Impl::performanceObject() const {
      auto value =
        getObject<ModelObject>().getModelObjectTarget<CoilCoolingDXCurveFitPerformance>(openstudio::Coil_Cooling_DXFields::PerformanceObjectName);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingDX_Impl::setPerformanceObject(const CoilCoolingDXCurveFitPerformance& coilCoolingDXCurveFitPerformance) {
      return coilCoolingDXCurveFitPerformance.model() == model()
             && setPointer(openstudio::Coil_Cooling_DXFields::PerformanceObjectName, coilCoolingDXCurveFitPerformance.handle());
    }

    // Condenser inlet node name
    std::string CoilCoolingDX_Impl::condenserInletNodeName() const {
      const auto value = getString(openstudio::Coil_Cooling_DXFields::CondenserInletNodeName, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingDX_Impl::setCondenserInletNodeName(const std::string& condenserInletNodeName) {
      if (condenserInletNodeName.empty()) {
        return false;
      }

      const auto previousNodeName = getString(openstudio::Coil_Cooling_DXFields::CondenserInletNodeName).value_or("");
      const auto previousNode = resolvedNodeTarget(openstudio::Coil_Cooling_DXFields::CondenserInletNodeName);
      auto condenserInletNode = model().getOrCreateTransientByName<Node>(condenserInletNodeName);
      if (!setPointer(openstudio::Coil_Cooling_DXFields::CondenserInletNodeName, condenserInletNode.handle(), false)) {
        return false;
      }
      if (maintainCondenserOutdoorAirNode(previousNodeName)) {
        return true;
      }

      OS_ASSERT(setPointer(openstudio::Coil_Cooling_DXFields::CondenserInletNodeName, previousNode ? previousNode->handle() : Handle(), false));
      return false;
    }

    // Condenser outlet node name
    std::string CoilCoolingDX_Impl::condenserOutletNodeName() const {
      const auto value = getString(openstudio::Coil_Cooling_DXFields::CondenserOutletNodeName, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingDX_Impl::setCondenserOutletNodeName(const std::string& condenserOutletNodeName) {
      if (condenserOutletNodeName.empty()) {
        return false;
      }
      auto condenserOutletNode = model().getOrCreateTransientByName<Node>(condenserOutletNodeName);
      return setPointer(openstudio::Coil_Cooling_DXFields::CondenserOutletNodeName, condenserOutletNode.handle(), false);
    }

    bool CoilCoolingDX_Impl::maintainCondenserOutdoorAirNode(const std::string& previousNodeName) {
      const auto currentNodeName = getString(openstudio::Coil_Cooling_DXFields::CondenserInletNodeName);
      if (!(currentNodeName && !currentNodeName->empty())) {
        return false;
      }

      bool declaredByOutdoorAirNode = false;
      for (const auto& object : model().getObjectsByType(openstudio::IddObjectType::OutdoorAir_Node)) {
        if (openstudio::istringEqual(object.nameString(), *currentNodeName)) {
          declaredByOutdoorAirNode = true;
          break;
        }
      }

      bool declaredAsOutdoorAir = declaredByOutdoorAirNode;
      if (declaredByOutdoorAirNode) {
        // OutdoorAir:Node carries height and local-weather inputs that a node
        // list cannot preserve. Prefer it when both forms declare this node.
        removeCondenserOutdoorAirNodeListEntries(*currentNodeName);
      } else {
        for (const auto& object : model().getObjectsByType(openstudio::IddObjectType::OutdoorAir_NodeList)) {
          for (const auto& group : object.extensibleGroups()) {
            auto workspaceGroup = group.optionalCast<openstudio::WorkspaceExtensibleGroup>();
            if (!workspaceGroup) {
              continue;
            }
            auto nodeName = workspaceGroup->getString(openstudio::OutdoorAir_NodeListExtensibleFields::NodeorNodeListName);
            if (nodeName && openstudio::istringEqual(*nodeName, *currentNodeName)) {
              declaredAsOutdoorAir = true;
              break;
            }
          }
          if (declaredAsOutdoorAir) {
            break;
          }
        }
      }

      if (!declaredAsOutdoorAir) {
        auto nodeList = ModelObject::create(openstudio::IddObjectType::OutdoorAir_NodeList, model());
        auto group = nodeList.pushExtensibleGroup().optionalCast<openstudio::WorkspaceExtensibleGroup>();
        if (!(group && group->setString(openstudio::OutdoorAir_NodeListExtensibleFields::NodeorNodeListName, *currentNodeName))) {
          nodeList.remove();
          return false;
        }
      }

      if (!previousNodeName.empty() && !openstudio::istringEqual(previousNodeName, *currentNodeName)) {
        removeUnusedCondenserOutdoorAirNode(previousNodeName);
      }
      return true;
    }

    unsigned CoilCoolingDX_Impl::removeCondenserOutdoorAirNodeListEntries(const std::string& nodeName) {
      unsigned removedEntries = 0;
      for (auto object : model().getObjectsByType(openstudio::IddObjectType::OutdoorAir_NodeList)) {
        const auto groups = object.extensibleGroups();
        std::vector<unsigned> matchingGroups;
        for (const auto& group : groups) {
          auto workspaceGroup = group.optionalCast<openstudio::WorkspaceExtensibleGroup>();
          if (!workspaceGroup) {
            continue;
          }
          auto listedNodeName = workspaceGroup->getString(openstudio::OutdoorAir_NodeListExtensibleFields::NodeorNodeListName);
          if (listedNodeName && openstudio::istringEqual(*listedNodeName, nodeName)) {
            matchingGroups.push_back(workspaceGroup->groupIndex());
          }
        }

        removedEntries += static_cast<unsigned>(matchingGroups.size());
        if (!matchingGroups.empty() && (matchingGroups.size() == groups.size())) {
          object.remove();
          continue;
        }
        for (auto it = matchingGroups.rbegin(); it != matchingGroups.rend(); ++it) {
          object.eraseExtensibleGroup(*it);
        }
      }
      return removedEntries;
    }

    void CoilCoolingDX_Impl::removeUnusedCondenserOutdoorAirNode(const std::string& nodeName) {
      if (nodeName.empty()) {
        return;
      }

      // Outdoor-air declarations are shared model state. Remove an old entry
      // only after every non-declaration NodeType field has stopped using it.
      for (const auto& object : model().objects()) {
        if ((object.handle() == handle()) || (object.iddObject().type() == openstudio::IddObjectType::OutdoorAir_NodeList)) {
          continue;
        }
        for (unsigned fieldIndex = 0; fieldIndex < object.numFields(); ++fieldIndex) {
          const auto iddField = object.iddObject().getField(fieldIndex);
          if (!(iddField && (iddField->properties().type == openstudio::IddFieldType::NodeType))) {
            continue;
          }
          const auto fieldValue = object.getString(fieldIndex);
          if (fieldValue && openstudio::istringEqual(*fieldValue, nodeName)) {
            return;
          }
        }
      }

      removeCondenserOutdoorAirNodeListEntries(nodeName);
    }

    void CoilCoolingDX_Impl::doCanonicalize(LoadContext& context) {
      StraightComponent_Impl::doCanonicalize(context);

      const auto coilName = getObject<ModelObject>().nameString();
      auto condenserInlet = getString(openstudio::Coil_Cooling_DXFields::CondenserInletNodeName);
      if (!(condenserInlet && !condenserInlet->empty())) {
        detail::addLoadInfo(context, "Created missing condenser inlet node name for Coil:Cooling:DX '" + coilName + "'.");
      }
      resolvedOrCreatedNodeTarget(openstudio::Coil_Cooling_DXFields::CondenserInletNodeName, coilName + " Condenser Inlet Node");

      auto condenserOutlet = getString(openstudio::Coil_Cooling_DXFields::CondenserOutletNodeName);
      if (!(condenserOutlet && !condenserOutlet->empty())) {
        detail::addLoadInfo(context, "Created missing condenser outlet node name for Coil:Cooling:DX '" + coilName + "'.");
      }
      resolvedOrCreatedNodeTarget(openstudio::Coil_Cooling_DXFields::CondenserOutletNodeName, coilName + " Condenser Outlet Node");

      bool declaredByOutdoorAirNode = false;
      const auto repairedInlet = condenserInletNodeName();
      for (const auto& object : model().getObjectsByType(openstudio::IddObjectType::OutdoorAir_Node)) {
        if (openstudio::istringEqual(object.nameString(), repairedInlet)) {
          declaredByOutdoorAirNode = true;
          break;
        }
      }

      unsigned nodeListEntryCount = 0;
      for (const auto& object : model().getObjectsByType(openstudio::IddObjectType::OutdoorAir_NodeList)) {
        for (const auto& group : object.extensibleGroups()) {
          auto workspaceGroup = group.optionalCast<openstudio::WorkspaceExtensibleGroup>();
          if (!workspaceGroup) {
            continue;
          }
          auto listedNodeName = workspaceGroup->getString(openstudio::OutdoorAir_NodeListExtensibleFields::NodeorNodeListName);
          if (listedNodeName && openstudio::istringEqual(*listedNodeName, repairedInlet)) {
            ++nodeListEntryCount;
          }
        }
      }

      OS_ASSERT(maintainCondenserOutdoorAirNode());
      if (declaredByOutdoorAirNode && (nodeListEntryCount > 0u)) {
        detail::addLoadInfo(context, "Removed " + std::to_string(nodeListEntryCount)
                                       + " conflicting OutdoorAir:NodeList entry or entries for condenser inlet node '" + repairedInlet
                                       + "' on Coil:Cooling:DX '" + coilName + "'; preserved the richer OutdoorAir:Node declaration.");
      } else if (!declaredByOutdoorAirNode && (nodeListEntryCount == 0u)) {
        detail::addLoadInfo(context, "Created OutdoorAir:NodeList entry for condenser inlet node '" + repairedInlet + "' on Coil:Cooling:DX '"
                                       + coilName + "'.");
      }
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
