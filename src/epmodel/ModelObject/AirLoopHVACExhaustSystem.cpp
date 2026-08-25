/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "AirLoopHVACExhaustSystem.hpp"
#include "AirLoopHVACExhaustSystem_Impl.hpp"

#include "HVACComponent/HVACComponent.hpp"
#include "HVACComponent/ThermalZone.hpp"
#include "HVACComponent/ThermalZone_Impl.hpp"
#include "Mixer/AirLoopHVACZoneMixer.hpp"
#include "Mixer/AirLoopHVACZoneMixer_Impl.hpp"
#include "Model.hpp"
#include "ModelObject/ZoneHVACEquipmentConnections.hpp"
#include "ModelObject/ZoneHVACEquipmentConnections_Impl.hpp"
#include "StraightComponent/FanComponentModel.hpp"
#include "StraightComponent/FanComponentModel_Impl.hpp"
#include "StraightComponent/FanSystemModel.hpp"
#include "StraightComponent/FanSystemModel_Impl.hpp"
#include "StraightComponent/Node.hpp"
#include "StraightComponent/StraightComponent.hpp"
#include "ModelObject/ZoneHVACExhaustControl.hpp"
#include "ModelObject/ZoneHVACExhaustControl_Impl.hpp"

#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/AirLoopHVAC_ExhaustSystem_FieldEnums.hxx>
#include <utilities/idd/ZoneHVAC_EquipmentConnections_FieldEnums.hxx>
#include <utilities/idd/ZoneHVAC_ExhaustControl_FieldEnums.hxx>

#include <algorithm>
#include <stdexcept>

namespace openstudio {
namespace epmodel {

  namespace {

    std::string uniqueObjectName(const Model& model, const std::string& baseName) {
      if (model.getObjectsByName(baseName, true).empty()) {
        return baseName;
      }

      for (unsigned suffix = 2u;; ++suffix) {
        const auto candidate = baseName + " " + std::to_string(suffix);
        if (model.getObjectsByName(candidate, true).empty()) {
          return candidate;
        }
      }
    }

  }  // namespace

  AirLoopHVACExhaustSystem::AirLoopHVACExhaustSystem(const Model& model) : ModelObject(AirLoopHVACExhaustSystem::iddObjectType(), model) {}

  AirLoopHVACExhaustSystem::AirLoopHVACExhaustSystem(const Model& model, FanSystemModel& fan) : AirLoopHVACExhaustSystem(model) {
    if (!getImpl<detail::AirLoopHVACExhaustSystem_Impl>()->initialize(fan)) {
      remove();
      throw std::runtime_error("Unable to construct an air-loop exhaust system from the requested Fan:SystemModel.");
    }
  }

  AirLoopHVACExhaustSystem::AirLoopHVACExhaustSystem(const Model& model, FanComponentModel& fan) : AirLoopHVACExhaustSystem(model) {
    if (!getImpl<detail::AirLoopHVACExhaustSystem_Impl>()->initialize(fan)) {
      remove();
      throw std::runtime_error("Unable to construct an air-loop exhaust system from the requested Fan:ComponentModel.");
    }
  }

  AirLoopHVACExhaustSystem::AirLoopHVACExhaustSystem(std::shared_ptr<detail::AirLoopHVACExhaustSystem_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType AirLoopHVACExhaustSystem::iddObjectType() {
    return IddObjectType::AirLoopHVAC_ExhaustSystem;
  }

  boost::optional<AirLoopHVACZoneMixer> AirLoopHVACExhaustSystem::zoneMixer() const {
    return getImpl<detail::AirLoopHVACExhaustSystem_Impl>()->zoneMixer();
  }

  boost::optional<HVACComponent> AirLoopHVACExhaustSystem::fan() const {
    return getImpl<detail::AirLoopHVACExhaustSystem_Impl>()->fan();
  }

  std::vector<ZoneHVACExhaustControl> AirLoopHVACExhaustSystem::zoneHVACExhaustControls() const {
    return getImpl<detail::AirLoopHVACExhaustSystem_Impl>()->zoneHVACExhaustControls();
  }

  boost::optional<ZoneHVACExhaustControl> AirLoopHVACExhaustSystem::addZone(ThermalZone& thermalZone) {
    return getImpl<detail::AirLoopHVACExhaustSystem_Impl>()->addZone(thermalZone);
  }

  bool AirLoopHVACExhaustSystem::removeZoneHVACExhaustControl(ZoneHVACExhaustControl& control) {
    return getImpl<detail::AirLoopHVACExhaustSystem_Impl>()->removeZoneHVACExhaustControl(control);
  }

  namespace detail {

    boost::optional<openstudio::epmodel::AirLoopHVACZoneMixer> AirLoopHVACExhaustSystem_Impl::zoneMixer() const {
      return getObject<ModelObject>().getModelObjectTarget<openstudio::epmodel::AirLoopHVACZoneMixer>(
        openstudio::AirLoopHVAC_ExhaustSystemFields::ZoneMixerName);
    }

    boost::optional<openstudio::epmodel::HVACComponent> AirLoopHVACExhaustSystem_Impl::fan() const {
      auto fan =
        getObject<ModelObject>().getModelObjectTarget<openstudio::epmodel::HVACComponent>(openstudio::AirLoopHVAC_ExhaustSystemFields::FanName);
      if (!fan) {
        return boost::none;
      }

      const auto declaredType = getString(openstudio::AirLoopHVAC_ExhaustSystemFields::FanObjectType, false, true);
      if (!declaredType) {
        return boost::none;
      }

      const auto actualType = fan->iddObject().type();
      if ((openstudio::istringEqual(*declaredType, "Fan:SystemModel") && actualType == openstudio::IddObjectType::Fan_SystemModel)
          || (openstudio::istringEqual(*declaredType, "Fan:ComponentModel") && actualType == openstudio::IddObjectType::Fan_ComponentModel)) {
        return fan;
      }
      return boost::none;
    }

    std::vector<openstudio::epmodel::ZoneHVACExhaustControl> AirLoopHVACExhaustSystem_Impl::zoneHVACExhaustControls() const {
      const auto mixer = zoneMixer();
      if (!mixer) {
        return {};
      }

      const auto inletObjects = mixer->inletModelObjects();
      std::vector<std::pair<std::size_t, openstudio::epmodel::ZoneHVACExhaustControl>> indexedControls;
      for (const auto& control : model().getConcreteModelObjects<openstudio::epmodel::ZoneHVACExhaustControl>()) {
        const auto outlet = control.outletNode();
        if (!outlet) {
          continue;
        }
        const auto inlet = std::ranges::find(inletObjects, outlet->cast<ModelObject>());
        if (inlet == inletObjects.end()) {
          continue;
        }
        const auto owner = control.airLoopHVACExhaustSystem();
        if (owner && (owner->handle() == handle())) {
          indexedControls.emplace_back(static_cast<std::size_t>(std::distance(inletObjects.begin(), inlet)), control);
        }
      }

      std::ranges::stable_sort(indexedControls, [](const auto& left, const auto& right) { return left.first < right.first; });
      std::vector<openstudio::epmodel::ZoneHVACExhaustControl> result;
      result.reserve(indexedControls.size());
      for (const auto& indexedControl : indexedControls) {
        result.push_back(indexedControl.second);
      }
      return result;
    }

    bool AirLoopHVACExhaustSystem_Impl::initialize(openstudio::epmodel::FanSystemModel& fan) {
      auto component = fan.cast<openstudio::epmodel::HVACComponent>();
      return initializeFan(component, "Fan:SystemModel");
    }

    bool AirLoopHVACExhaustSystem_Impl::initialize(openstudio::epmodel::FanComponentModel& fan) {
      auto component = fan.cast<openstudio::epmodel::HVACComponent>();
      return initializeFan(component, "Fan:ComponentModel");
    }

    bool AirLoopHVACExhaustSystem_Impl::initializeFan(openstudio::epmodel::HVACComponent& fan, const std::string& fanObjectType) {
      if (fan.model() != model()) {
        return false;
      }

      const auto expectedType = openstudio::istringEqual(fanObjectType, "Fan:SystemModel") ? openstudio::IddObjectType::Fan_SystemModel
                                                                                           : openstudio::IddObjectType::Fan_ComponentModel;
      if ((fan.iddObject().type() != expectedType) || !fan.sources().empty()) {
        return false;
      }

      auto straightFan = fan.optionalCast<openstudio::epmodel::StraightComponent>();
      if (!straightFan || straightFan->inletModelObject() || straightFan->outletModelObject()) {
        return false;
      }

      auto systemObject = getObject<openstudio::epmodel::ModelObject>();
      openstudio::epmodel::AirLoopHVACZoneMixer mixer(model());
      openstudio::epmodel::Node mixerOutlet(model());
      openstudio::epmodel::Node fanOutlet(model());
      if (!mixer.setName(uniqueObjectName(model(), systemObject.nameString() + " Zone Mixer"))
          || !mixerOutlet.setName(uniqueObjectName(model(), systemObject.nameString() + " Mixer Outlet Node"))
          || !fanOutlet.setName(uniqueObjectName(model(), systemObject.nameString() + " Fan Outlet Node"))) {
        mixer.remove();
        mixerOutlet.remove();
        fanOutlet.remove();
        return false;
      }

      auto fanImpl = fan.getImpl<detail::ModelObject_Impl>();
      OS_ASSERT(fanImpl);
      const auto rollback = [&]() {
        fanImpl->setPointer(straightFan->inletPort(), Handle(), false);
        fanImpl->setPointer(straightFan->outletPort(), Handle(), false);
        setPointer(openstudio::AirLoopHVAC_ExhaustSystemFields::ZoneMixerName, Handle(), false);
        setString(openstudio::AirLoopHVAC_ExhaustSystemFields::FanObjectType, "", false);
        setPointer(openstudio::AirLoopHVAC_ExhaustSystemFields::FanName, Handle(), false);
        mixer.remove();
        if (mixerOutlet.sources().empty()) {
          mixerOutlet.remove();
        }
        if (fanOutlet.sources().empty()) {
          fanOutlet.remove();
        }
      };

      if (!mixer.setOutletModelObject(mixerOutlet.cast<openstudio::epmodel::ModelObject>())
          || !fanImpl->setPointer(straightFan->inletPort(), mixerOutlet.handle(), false)
          || !fanImpl->setPointer(straightFan->outletPort(), fanOutlet.handle(), false)
          || !systemObject.setPointer(openstudio::AirLoopHVAC_ExhaustSystemFields::ZoneMixerName, mixer.handle())
          || !systemObject.setString(openstudio::AirLoopHVAC_ExhaustSystemFields::FanObjectType, fanObjectType)
          || !systemObject.setPointer(openstudio::AirLoopHVAC_ExhaustSystemFields::FanName, fan.handle())) {
        rollback();
        return false;
      }

      return true;
    }

    boost::optional<openstudio::epmodel::ZoneHVACExhaustControl>
      AirLoopHVACExhaustSystem_Impl::addZone(openstudio::epmodel::ThermalZone& thermalZone) {
      if (thermalZone.model() != model()) {
        return boost::none;
      }

      auto mixer = zoneMixer();
      auto centralFan = fan();
      if (!mixer || !centralFan) {
        return boost::none;
      }

      auto straightFan = centralFan->optionalCast<openstudio::epmodel::StraightComponent>();
      const auto mixerOutlet = mixer->outletModelObject();
      if (!straightFan || !mixerOutlet || !straightFan->inletModelObject() || !straightFan->outletModelObject()
          || (*mixerOutlet != *straightFan->inletModelObject())) {
        return boost::none;
      }

      for (const auto& other : model().getConcreteModelObjects<openstudio::epmodel::AirLoopHVACExhaustSystem>()) {
        if (other.handle() == handle()) {
          continue;
        }
        const auto otherMixer = other.zoneMixer();
        const auto otherFan = other.fan();
        if ((otherMixer && (*otherMixer == *mixer)) || (otherFan && (*otherFan == *centralFan))) {
          return boost::none;
        }
      }

      openstudio::epmodel::ZoneHVACExhaustControl control(model());
      openstudio::epmodel::Node inlet(model());
      openstudio::epmodel::Node outlet(model());
      if (!control.setName(uniqueObjectName(model(), thermalZone.nameString() + " Central Exhaust Control"))
          || !inlet.setName(uniqueObjectName(model(), control.nameString() + " Inlet Node"))
          || !outlet.setName(uniqueObjectName(model(), control.nameString() + " Outlet Node"))) {
        control.remove();
        inlet.remove();
        outlet.remove();
        return boost::none;
      }

      auto controlImpl = control.getImpl<openstudio::epmodel::detail::ZoneHVACExhaustControl_Impl>();
      OS_ASSERT(controlImpl);
      if (!controlImpl->setPointer(openstudio::ZoneHVAC_ExhaustControlFields::ZoneName, thermalZone.handle(), false)
          || !controlImpl->setPointer(openstudio::ZoneHVAC_ExhaustControlFields::InletNodeName, inlet.handle(), false)
          || !controlImpl->setPointer(openstudio::ZoneHVAC_ExhaustControlFields::OutletNodeName, outlet.handle(), false)) {
        controlImpl->ModelObject_Impl::remove();
        inlet.remove();
        outlet.remove();
        return boost::none;
      }

      const unsigned branchIndex = mixer->nextBranchIndex();
      if (!mixer->setInletModelObject(branchIndex, outlet.cast<openstudio::epmodel::ModelObject>())) {
        controlImpl->ModelObject_Impl::remove();
        inlet.remove();
        outlet.remove();
        return boost::none;
      }

      auto zoneImpl = thermalZone.getImpl<openstudio::epmodel::detail::ThermalZone_Impl>();
      OS_ASSERT(zoneImpl);
      auto connections = zoneImpl->getZoneHVACEquipmentConnections();
      auto connectionsImpl = connections.getImpl<openstudio::epmodel::detail::ZoneHVACEquipmentConnections_Impl>();
      OS_ASSERT(connectionsImpl);
      if (!connectionsImpl->hasExclusiveZoneAirExhaustNodeStorage()) {
        mixer->removePortForBranch(branchIndex);
        controlImpl->ModelObject_Impl::remove();
        inlet.remove();
        outlet.remove();
        return boost::none;
      }
      if (!connectionsImpl->addZoneAirExhaustNode(inlet)) {
        mixer->removePortForBranch(branchIndex);
        controlImpl->ModelObject_Impl::remove();
        if (inlet.sources().empty()) {
          inlet.remove();
        }
        if (outlet.sources().empty()) {
          outlet.remove();
        }
        return boost::none;
      }

      return control;
    }

    bool AirLoopHVACExhaustSystem_Impl::removeZoneHVACExhaustControl(openstudio::epmodel::ZoneHVACExhaustControl& control) {
      return !removeZoneHVACExhaustControlObjects(control).empty();
    }

    bool AirLoopHVACExhaustSystem_Impl::canRemoveZoneHVACExhaustControl(const openstudio::epmodel::ZoneHVACExhaustControl& control) const {
      if (control.model() != model()) {
        return false;
      }
      const auto owner = control.airLoopHVACExhaustSystem();
      const auto thermalZone = control.thermalZone();
      const auto inlet = control.inletNode();
      const auto outlet = control.outletNode();
      const auto mixer = zoneMixer();
      if (!owner || (owner->handle() != handle()) || !thermalZone || !inlet || !outlet || !mixer) {
        return false;
      }

      const auto mixerInlets = mixer->inletModelObjects();
      if (std::ranges::count(mixerInlets, outlet->cast<openstudio::epmodel::ModelObject>()) != 1) {
        return false;
      }

      auto zoneImpl = thermalZone->getImpl<openstudio::epmodel::detail::ThermalZone_Impl>();
      OS_ASSERT(zoneImpl);
      const auto connections = zoneImpl->zoneHVACEquipmentConnections();
      if (!connections) {
        return false;
      }
      const auto connectionsImpl = connections->getImpl<openstudio::epmodel::detail::ZoneHVACEquipmentConnections_Impl>();
      OS_ASSERT(connectionsImpl);
      if (!connectionsImpl->hasExclusiveZoneAirExhaustNodeStorage() || (std::ranges::count(connections->zoneAirExhaustNodes(), *inlet) != 1)
          || (*inlet == *outlet)) {
        return false;
      }

      constexpr unsigned exhaustField = openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneAirExhaustNodeorNodeListName;
      const auto registrationTarget = connections->getTarget(exhaustField);
      if (!registrationTarget) {
        return false;
      }
      const auto registrationSourceHandle = registrationTarget->handle() == inlet->handle() ? connections->handle() : registrationTarget->handle();
      const auto inletSources = inlet->sources();
      if (inletSources.size() != 2u) {
        return false;
      }
      bool foundControlInlet = false;
      bool foundRegistration = false;
      for (const auto& source : inletSources) {
        const auto sourceFields = source.getSourceIndices(inlet->handle());
        if (source.handle() == control.handle()) {
          foundControlInlet = (sourceFields.size() == 1u) && (sourceFields.front() == openstudio::ZoneHVAC_ExhaustControlFields::InletNodeName);
        } else if (source.handle() == registrationSourceHandle) {
          foundRegistration = sourceFields.size() == 1u;
          if (registrationSourceHandle == connections->handle()) {
            foundRegistration = foundRegistration && (sourceFields.front() == exhaustField);
          }
        } else {
          return false;
        }
      }
      if (!foundControlInlet || !foundRegistration) {
        return false;
      }

      const auto outletSources = outlet->sources();
      if (outletSources.size() != 2u) {
        return false;
      }
      bool foundControlOutlet = false;
      bool foundMixer = false;
      for (const auto& source : outletSources) {
        const auto sourceFields = source.getSourceIndices(outlet->handle());
        if (source.handle() == control.handle()) {
          foundControlOutlet = (sourceFields.size() == 1u) && (sourceFields.front() == openstudio::ZoneHVAC_ExhaustControlFields::OutletNodeName);
        } else if (source.handle() == mixer->handle()) {
          foundMixer = sourceFields.size() == 1u;
        } else {
          return false;
        }
      }
      return foundControlOutlet && foundMixer;
    }

    std::vector<openstudio::IdfObject>
      AirLoopHVACExhaustSystem_Impl::removeZoneHVACExhaustControlObjects(openstudio::epmodel::ZoneHVACExhaustControl& control) {
      if (!canRemoveZoneHVACExhaustControl(control)) {
        return {};
      }
      const auto owner = control.airLoopHVACExhaustSystem();
      const auto thermalZone = control.thermalZone();
      const auto inlet = control.inletNode();
      const auto outlet = control.outletNode();
      auto mixer = zoneMixer();
      if (!owner || (owner->handle() != handle()) || !thermalZone || !inlet || !outlet || !mixer) {
        return {};
      }

      const auto mixerInlets = mixer->inletModelObjects();
      const auto outletObject = outlet->cast<openstudio::epmodel::ModelObject>();
      if (std::ranges::count(mixerInlets, outletObject) != 1) {
        return {};
      }
      const auto branchIndex = static_cast<unsigned>(std::distance(mixerInlets.begin(), std::ranges::find(mixerInlets, outletObject)));

      auto zoneImpl = thermalZone->getImpl<openstudio::epmodel::detail::ThermalZone_Impl>();
      OS_ASSERT(zoneImpl);
      auto connections = zoneImpl->zoneHVACEquipmentConnections();
      if (!connections) {
        return {};
      }
      auto connectionsImpl = connections->getImpl<openstudio::epmodel::detail::ZoneHVACEquipmentConnections_Impl>();
      OS_ASSERT(connectionsImpl);
      if (std::ranges::count(connections->zoneAirExhaustNodes(), *inlet) != 1) {
        return {};
      }

      if (!connectionsImpl->removeZoneAirExhaustNode(*inlet)) {
        return {};
      }
      mixer->removePortForBranch(branchIndex);

      auto controlImpl = control.getImpl<openstudio::epmodel::detail::ZoneHVACExhaustControl_Impl>();
      OS_ASSERT(controlImpl);
      auto result = controlImpl->ModelObject_Impl::remove();
      OS_ASSERT(!result.empty());
      for (auto node : {*inlet, *outlet}) {
        if (model().getObject(node.handle()) && node.sources().empty()) {
          auto removed = node.remove();
          result.insert(result.end(), removed.begin(), removed.end());
        }
      }
      return result;
    }

    std::vector<openstudio::IdfObject> AirLoopHVACExhaustSystem_Impl::remove() {
      std::vector<openstudio::IdfObject> result;
      auto owningModel = model();
      auto mixer = zoneMixer();
      auto centralFan = fan();
      for (const auto& other : owningModel.getConcreteModelObjects<openstudio::epmodel::AirLoopHVACExhaustSystem>()) {
        if (other.handle() == handle()) {
          continue;
        }
        const auto otherMixer = other.zoneMixer();
        const auto otherFan = other.fan();
        if ((mixer && otherMixer && (*otherMixer == *mixer)) || (centralFan && otherFan && (*otherFan == *centralFan))) {
          return {};
        }
      }

      auto controls = zoneHVACExhaustControls();
      if (!std::ranges::all_of(controls, [this](const auto& control) { return canRemoveZoneHVACExhaustControl(control); })) {
        return {};
      }
      std::vector<Handle> privateControlNodes;
      privateControlNodes.reserve(2u * controls.size());
      for (const auto& control : controls) {
        const auto inlet = control.inletNode();
        const auto outlet = control.outletNode();
        OS_ASSERT(inlet);
        OS_ASSERT(outlet);
        privateControlNodes.push_back(inlet->handle());
        privateControlNodes.push_back(outlet->handle());
      }
      std::ranges::sort(privateControlNodes);
      if (std::ranges::adjacent_find(privateControlNodes) != privateControlNodes.end()) {
        return {};
      }
      for (auto control : controls) {
        auto removed = removeZoneHVACExhaustControlObjects(control);
        if (removed.empty()) {
          return {};
        }
        result.insert(result.end(), removed.begin(), removed.end());
      }

      boost::optional<openstudio::epmodel::Node> mixerOutlet;
      boost::optional<openstudio::epmodel::Node> fanOutlet;
      boost::optional<openstudio::epmodel::StraightComponent> straightFan;
      if (mixer) {
        if (const auto object = mixer->outletModelObject()) {
          mixerOutlet = object->optionalCast<openstudio::epmodel::Node>();
        }
      }
      if (centralFan) {
        straightFan = centralFan->optionalCast<openstudio::epmodel::StraightComponent>();
        if (straightFan) {
          if (const auto object = straightFan->outletModelObject()) {
            fanOutlet = object->optionalCast<openstudio::epmodel::Node>();
          }
        }
      }

      auto removedParent = ModelObject_Impl::remove();
      if (removedParent.empty()) {
        return {};
      }

      if (mixer && owningModel.getObject(mixer->handle()) && mixer->sources().empty()) {
        auto removed = mixer->remove();
        result.insert(result.end(), removed.begin(), removed.end());
      }
      if (centralFan && straightFan && owningModel.getObject(centralFan->handle())) {
        auto fanImpl = centralFan->getImpl<detail::ModelObject_Impl>();
        OS_ASSERT(fanImpl);
        if (mixerOutlet && straightFan->inletModelObject()
            && (*straightFan->inletModelObject() == mixerOutlet->cast<openstudio::epmodel::ModelObject>())) {
          OS_ASSERT(fanImpl->setPointer(straightFan->inletPort(), Handle(), false));
        }
        if (fanOutlet && straightFan->outletModelObject()
            && (*straightFan->outletModelObject() == fanOutlet->cast<openstudio::epmodel::ModelObject>())) {
          OS_ASSERT(fanImpl->setPointer(straightFan->outletPort(), Handle(), false));
        }
      }
      for (auto node : {mixerOutlet, fanOutlet}) {
        if (node && owningModel.getObject(node->handle()) && node->sources().empty()) {
          auto removed = node->remove();
          result.insert(result.end(), removed.begin(), removed.end());
        }
      }
      result.insert(result.end(), removedParent.begin(), removedParent.end());
      return result;
    }

  }  // namespace detail

}  // namespace epmodel
}  // namespace openstudio
