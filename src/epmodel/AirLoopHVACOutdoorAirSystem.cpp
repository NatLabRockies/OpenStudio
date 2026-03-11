/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "AirLoopHVACOutdoorAirSystem.hpp"
#include "AirLoopHVACOutdoorAirSystem_Impl.hpp"

#include "AirLoopHVAC.hpp"
#include "AirLoopHVAC_Impl.hpp"
#include "AirLoopHVACControllerList.hpp"
#include "AirLoopHVACControllerList_Impl.hpp"
#include "AirLoopHVACOutdoorAirSystemEquipmentList.hpp"
#include "AirLoopHVACOutdoorAirSystemEquipmentList_Impl.hpp"
#include "Branch.hpp"
#include "Branch_Impl.hpp"
#include "BranchList.hpp"
#include "BranchList_Impl.hpp"
#include "ControllerOutdoorAir.hpp"
#include "ControllerOutdoorAir_Impl.hpp"
#include "Model.hpp"
#include "ModelObject.hpp"
#include "Node.hpp"
#include "OutdoorAirMixer.hpp"
#include "OutdoorAirMixer_Impl.hpp"

#include <algorithm>
#include <utilities/core/Assert.hpp>
#include <utilities/core/Compare.hpp>
#include <utilities/idd/AirLoopHVAC_OutdoorAirSystem_FieldEnums.hxx>
#include <utilities/idd/OutdoorAir_Mixer_FieldEnums.hxx>
#include <utilities/idf/IdfExtensibleGroup.hpp>

namespace openstudio {
namespace epmodel {

  AirLoopHVACOutdoorAirSystem::AirLoopHVACOutdoorAirSystem(const Model& model) : HVACComponent(AirLoopHVACOutdoorAirSystem::iddObjectType(), model) {
    auto impl = getImpl<detail::AirLoopHVACOutdoorAirSystem_Impl>();
    OS_ASSERT(impl);
    detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
    impl->canonicalize(context);
  }

  AirLoopHVACOutdoorAirSystem::AirLoopHVACOutdoorAirSystem(std::shared_ptr<detail::AirLoopHVACOutdoorAirSystem_Impl> impl)
    : HVACComponent(std::move(impl)) {}

  IddObjectType AirLoopHVACOutdoorAirSystem::iddObjectType() {
    return IddObjectType::AirLoopHVAC_OutdoorAirSystem;
  }

  unsigned AirLoopHVACOutdoorAirSystem::returnAirPort() const {
    return getImpl<detail::AirLoopHVACOutdoorAirSystem_Impl>()->returnAirPort();
  }

  unsigned AirLoopHVACOutdoorAirSystem::outdoorAirPort() const {
    return getImpl<detail::AirLoopHVACOutdoorAirSystem_Impl>()->outdoorAirPort();
  }

  unsigned AirLoopHVACOutdoorAirSystem::reliefAirPort() const {
    return getImpl<detail::AirLoopHVACOutdoorAirSystem_Impl>()->reliefAirPort();
  }

  unsigned AirLoopHVACOutdoorAirSystem::mixedAirPort() const {
    return getImpl<detail::AirLoopHVACOutdoorAirSystem_Impl>()->mixedAirPort();
  }

  boost::optional<ModelObject> AirLoopHVACOutdoorAirSystem::returnAirModelObject() const {
    return getImpl<detail::AirLoopHVACOutdoorAirSystem_Impl>()->returnAirModelObject();
  }

  boost::optional<ModelObject> AirLoopHVACOutdoorAirSystem::outdoorAirModelObject() const {
    return getImpl<detail::AirLoopHVACOutdoorAirSystem_Impl>()->outdoorAirModelObject();
  }

  boost::optional<ModelObject> AirLoopHVACOutdoorAirSystem::reliefAirModelObject() const {
    return getImpl<detail::AirLoopHVACOutdoorAirSystem_Impl>()->reliefAirModelObject();
  }

  boost::optional<ModelObject> AirLoopHVACOutdoorAirSystem::mixedAirModelObject() const {
    return getImpl<detail::AirLoopHVACOutdoorAirSystem_Impl>()->mixedAirModelObject();
  }

  std::vector<ModelObject> AirLoopHVACOutdoorAirSystem::oaComponents(openstudio::IddObjectType type) const {
    return getImpl<detail::AirLoopHVACOutdoorAirSystem_Impl>()->oaComponents(type);
  }

  std::vector<ModelObject> AirLoopHVACOutdoorAirSystem::reliefComponents(openstudio::IddObjectType type) const {
    return getImpl<detail::AirLoopHVACOutdoorAirSystem_Impl>()->reliefComponents(type);
  }

  std::vector<ModelObject> AirLoopHVACOutdoorAirSystem::components(openstudio::IddObjectType type) const {
    return getImpl<detail::AirLoopHVACOutdoorAirSystem_Impl>()->components(type);
  }

  boost::optional<ModelObject> AirLoopHVACOutdoorAirSystem::component(openstudio::Handle handle) const {
    return getImpl<detail::AirLoopHVACOutdoorAirSystem_Impl>()->component(handle);
  }

  boost::optional<ModelObject> AirLoopHVACOutdoorAirSystem::oaComponent(openstudio::Handle handle) const {
    return getImpl<detail::AirLoopHVACOutdoorAirSystem_Impl>()->oaComponent(handle);
  }

  boost::optional<ModelObject> AirLoopHVACOutdoorAirSystem::reliefComponent(openstudio::Handle handle) const {
    return getImpl<detail::AirLoopHVACOutdoorAirSystem_Impl>()->reliefComponent(handle);
  }

  ControllerOutdoorAir AirLoopHVACOutdoorAirSystem::getControllerOutdoorAir() const {
    return getImpl<detail::AirLoopHVACOutdoorAirSystem_Impl>()->getControllerOutdoorAir();
  }

  bool AirLoopHVACOutdoorAirSystem::setControllerOutdoorAir(const ControllerOutdoorAir& controllerOutdoorAir) {
    return getImpl<detail::AirLoopHVACOutdoorAirSystem_Impl>()->setControllerOutdoorAir(controllerOutdoorAir);
  }

  boost::optional<Node> AirLoopHVACOutdoorAirSystem::outboardOANode() const {
    return getImpl<detail::AirLoopHVACOutdoorAirSystem_Impl>()->outboardOANode();
  }

  boost::optional<Node> AirLoopHVACOutdoorAirSystem::outboardReliefNode() const {
    return getImpl<detail::AirLoopHVACOutdoorAirSystem_Impl>()->outboardReliefNode();
  }

  bool AirLoopHVACOutdoorAirSystem::addToNode(Node& node) {
    return getImpl<detail::AirLoopHVACOutdoorAirSystem_Impl>()->addToNode(node);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    unsigned AirLoopHVACOutdoorAirSystem_Impl::returnAirPort() const {
      return openstudio::OutdoorAir_MixerFields::ReturnAirStreamNodeName;
    }

    unsigned AirLoopHVACOutdoorAirSystem_Impl::outdoorAirPort() const {
      return openstudio::OutdoorAir_MixerFields::OutdoorAirStreamNodeName;
    }

    unsigned AirLoopHVACOutdoorAirSystem_Impl::reliefAirPort() const {
      return openstudio::OutdoorAir_MixerFields::ReliefAirStreamNodeName;
    }

    unsigned AirLoopHVACOutdoorAirSystem_Impl::mixedAirPort() const {
      return openstudio::OutdoorAir_MixerFields::MixedAirNodeName;
    }

    openstudio::epmodel::AirLoopHVACOutdoorAirSystemEquipmentList AirLoopHVACOutdoorAirSystem_Impl::airLoopHVACOutdoorAirSystemEquipmentList() const {
      auto oaSystem = getObject<openstudio::epmodel::AirLoopHVACOutdoorAirSystem>();
      auto equipmentList = oaSystem.getModelObjectTarget<openstudio::epmodel::AirLoopHVACOutdoorAirSystemEquipmentList>(
        openstudio::AirLoopHVAC_OutdoorAirSystemFields::OutdoorAirEquipmentListName);
      OS_ASSERT(equipmentList);
      return *equipmentList;
    }

    openstudio::epmodel::OutdoorAirMixer AirLoopHVACOutdoorAirSystem_Impl::outdoorAirMixer() const {
      const auto mixers = subsetCastVector<openstudio::epmodel::OutdoorAirMixer>(airLoopHVACOutdoorAirSystemEquipmentList().equipment());
      OS_ASSERT(mixers.size() == 1u);
      return mixers.front();
    }

    boost::optional<openstudio::epmodel::ModelObject> AirLoopHVACOutdoorAirSystem_Impl::returnAirModelObject() const {
      auto mixer = outdoorAirMixer();

      if (auto node = mixer.getModelObjectTarget<openstudio::epmodel::Node>(returnAirPort())) {
        return node->cast<openstudio::epmodel::ModelObject>();
      }

      if (auto nodeName = mixer.getString(returnAirPort())) {
        OS_ASSERT(nodeName->empty());
      }
      return boost::none;
    }

    boost::optional<openstudio::epmodel::ModelObject> AirLoopHVACOutdoorAirSystem_Impl::outdoorAirModelObject() const {
      auto mixer = outdoorAirMixer();

      if (auto node = mixer.getModelObjectTarget<openstudio::epmodel::Node>(outdoorAirPort())) {
        return node->cast<openstudio::epmodel::ModelObject>();
      }

      if (auto nodeName = mixer.getString(outdoorAirPort())) {
        OS_ASSERT(nodeName->empty());
      }
      return boost::none;
    }

    boost::optional<openstudio::epmodel::ModelObject> AirLoopHVACOutdoorAirSystem_Impl::reliefAirModelObject() const {
      auto mixer = outdoorAirMixer();

      if (auto node = mixer.getModelObjectTarget<openstudio::epmodel::Node>(reliefAirPort())) {
        return node->cast<openstudio::epmodel::ModelObject>();
      }

      if (auto nodeName = mixer.getString(reliefAirPort())) {
        OS_ASSERT(nodeName->empty());
      }
      return boost::none;
    }

    boost::optional<openstudio::epmodel::ModelObject> AirLoopHVACOutdoorAirSystem_Impl::mixedAirModelObject() const {
      auto mixer = outdoorAirMixer();

      if (auto node = mixer.getModelObjectTarget<openstudio::epmodel::Node>(mixedAirPort())) {
        return node->cast<openstudio::epmodel::ModelObject>();
      }

      if (auto nodeName = mixer.getString(mixedAirPort())) {
        OS_ASSERT(nodeName->empty());
      }
      return boost::none;
    }

    std::vector<openstudio::epmodel::ModelObject> AirLoopHVACOutdoorAirSystem_Impl::oaComponents(openstudio::IddObjectType) const {
      auto oaSystem = getObject<openstudio::epmodel::AirLoopHVACOutdoorAirSystem>();
      auto equipmentList = oaSystem.getModelObjectTarget<openstudio::epmodel::AirLoopHVACOutdoorAirSystemEquipmentList>(
        openstudio::AirLoopHVAC_OutdoorAirSystemFields::OutdoorAirEquipmentListName);
      if (!equipmentList) {
        return {};
      }
      return equipmentList->equipment();
    }

    std::vector<openstudio::epmodel::ModelObject> AirLoopHVACOutdoorAirSystem_Impl::reliefComponents(openstudio::IddObjectType type) const {
      if (auto mo = reliefAirModelObject()) {
        if ((type == openstudio::IddObjectType::Catchall) || (mo->iddObject().type() == type)) {
          return {*mo};
        }
      }
      return {};
    }

    std::vector<openstudio::epmodel::ModelObject> AirLoopHVACOutdoorAirSystem_Impl::components(openstudio::IddObjectType type) const {
      auto result = oaComponents(type);
      auto relief = reliefComponents(type);
      result.insert(result.end(), relief.begin(), relief.end());
      return result;
    }

    boost::optional<openstudio::epmodel::ModelObject> AirLoopHVACOutdoorAirSystem_Impl::component(openstudio::Handle handle) const {
      if (auto result = oaComponent(handle)) {
        return result;
      }
      return reliefComponent(handle);
    }

    boost::optional<openstudio::epmodel::ModelObject> AirLoopHVACOutdoorAirSystem_Impl::oaComponent(openstudio::Handle handle) const {
      auto comps = oaComponents(openstudio::IddObjectType::Catchall);
      auto it = std::find_if(comps.begin(), comps.end(), [&](const openstudio::epmodel::ModelObject& comp) { return comp.handle() == handle; });
      if (it != comps.end()) {
        return *it;
      }
      return boost::none;
    }

    boost::optional<openstudio::epmodel::ModelObject> AirLoopHVACOutdoorAirSystem_Impl::reliefComponent(openstudio::Handle handle) const {
      auto comps = reliefComponents(openstudio::IddObjectType::Catchall);
      auto it = std::ranges::find_if(comps, [&](const openstudio::epmodel::ModelObject& comp) { return comp.handle() == handle; });
      if (it != comps.end()) {
        return *it;
      }
      return boost::none;
    }

    openstudio::epmodel::ControllerOutdoorAir AirLoopHVACOutdoorAirSystem_Impl::getControllerOutdoorAir() const {
      auto controller = airLoopHVACControllerList().optionalControllerOutdoorAir();
      OS_ASSERT(controller);
      return *controller;
    }

    bool AirLoopHVACOutdoorAirSystem_Impl::setControllerOutdoorAir(const openstudio::epmodel::ControllerOutdoorAir& controllerOutdoorAir) {
      auto controllerList = airLoopHVACControllerList();
      const bool result =
        controllerList.getImpl<openstudio::epmodel::detail::AirLoopHVACControllerList_Impl>()->setControllerOutdoorAir(controllerOutdoorAir);
      if (result) {
        if (auto airLoop = this->airLoopHVAC()) {
          airLoop->getImpl<openstudio::epmodel::detail::AirLoopHVAC_Impl>()->syncControllerMechanicalVentilationZoneOutdoorAirEntries();
        }
      }
      return result;
    }

    openstudio::epmodel::AirLoopHVACControllerList AirLoopHVACOutdoorAirSystem_Impl::airLoopHVACControllerList() const {
      auto oaSystem = getObject<openstudio::epmodel::AirLoopHVACOutdoorAirSystem>();
      auto controllerList = oaSystem.getModelObjectTarget<openstudio::epmodel::AirLoopHVACControllerList>(
        openstudio::AirLoopHVAC_OutdoorAirSystemFields::ControllerListName);
      OS_ASSERT(controllerList);
      return *controllerList;
    }

    boost::optional<openstudio::epmodel::Node> AirLoopHVACOutdoorAirSystem_Impl::outboardOANode() const {
      if (auto mo = outdoorAirModelObject()) {
        return mo->optionalCast<openstudio::epmodel::Node>();
      }
      return boost::none;
    }

    boost::optional<openstudio::epmodel::Node> AirLoopHVACOutdoorAirSystem_Impl::outboardReliefNode() const {
      if (auto mo = reliefAirModelObject()) {
        return mo->optionalCast<openstudio::epmodel::Node>();
      }
      return boost::none;
    }

    void AirLoopHVACOutdoorAirSystem_Impl::doCanonicalize(LoadContext& context) {
      auto oaSystem = getObject<openstudio::epmodel::AirLoopHVACOutdoorAirSystem>();
      auto oaSystemName = oaSystem.nameString();

      // Maintain the non-optional OA controller invariant to match getControllerOutdoorAir().
      auto controllerList = oaSystem.getModelObjectTarget<openstudio::epmodel::AirLoopHVACControllerList>(
        openstudio::AirLoopHVAC_OutdoorAirSystemFields::ControllerListName);
      if (!controllerList) {
        auto createdControllerList = openstudio::epmodel::AirLoopHVACControllerList(model());
        createdControllerList.setName(oaSystem.nameString() + " Controller List");
        OS_ASSERT(oaSystem.setPointer(openstudio::AirLoopHVAC_OutdoorAirSystemFields::ControllerListName, createdControllerList.handle()));
        controllerList = createdControllerList;
        detail::addLoadInfo(context, "Created missing AirLoopHVAC:ControllerList '" + createdControllerList.nameString()
                                       + "' for AirLoopHVAC:OutdoorAirSystem '" + oaSystem.nameString() + "'.");
      }
      OS_ASSERT(controllerList);
      auto controllerListObject = *controllerList;
      controllerListObject.getImpl<openstudio::epmodel::detail::AirLoopHVACControllerList_Impl>()->canonicalize(context);

      auto oaController = controllerListObject.optionalControllerOutdoorAir();
      if (!oaController) {
        auto createdController = openstudio::epmodel::ControllerOutdoorAir(model());
        createdController.setName(model().nextName(openstudio::IddObjectType::Controller_OutdoorAir, true));
        OS_ASSERT(
          controllerListObject.getImpl<openstudio::epmodel::detail::AirLoopHVACControllerList_Impl>()->setControllerOutdoorAir(createdController));
        oaController = createdController;
        detail::addLoadInfo(context, "Created missing Controller:OutdoorAir '" + createdController.nameString()
                                       + "' for AirLoopHVAC:OutdoorAirSystem '" + oaSystem.nameString() + "'.");
      }
      OS_ASSERT(oaController);
      oaController->getImpl<openstudio::epmodel::detail::ControllerOutdoorAir_Impl>()->canonicalize(context);

      auto el = oaSystem.getModelObjectTarget<openstudio::epmodel::AirLoopHVACOutdoorAirSystemEquipmentList>(
        openstudio::AirLoopHVAC_OutdoorAirSystemFields::OutdoorAirEquipmentListName);

      if (!el) {
        el = openstudio::epmodel::AirLoopHVACOutdoorAirSystemEquipmentList(model());
        el->setName(oaSystem.nameString() + " equipment list");
        OS_ASSERT(oaSystem.setPointer(openstudio::AirLoopHVAC_OutdoorAirSystemFields::OutdoorAirEquipmentListName, el->handle()));
        detail::addLoadInfo(context, "Created missing AirLoopHVAC:OutdoorAirSystem:EquipmentList '" + el->nameString()
                                       + "' for AirLoopHVAC:OutdoorAirSystem '" + oaSystem.nameString() + "'.");
      }

      OS_ASSERT(el);
      el->getImpl<detail::AirLoopHVACOutdoorAirSystemEquipmentList_Impl>()->canonicalize(context);

      boost::optional<OutdoorAirMixer> mixer;
      const auto mixers = subsetCastVector<openstudio::epmodel::OutdoorAirMixer>(el->equipment());
      if (mixers.empty()) {
        mixer = OutdoorAirMixer(model());
        mixer->setName(oaSystem.nameString() + " mixer");
        OS_ASSERT(el->getImpl<detail::AirLoopHVACOutdoorAirSystemEquipmentList_Impl>()->addEquipment(*mixer));
        detail::addLoadInfo(context, "Created missing OutdoorAir:Mixer '" + mixer->nameString() + "' for AirLoopHVAC:OutdoorAirSystem '"
                                       + oaSystem.nameString() + "'.");
      } else {
        mixer = mixers.front();
        // Remove any mixer after the first one
        if (mixers.size() > 1u) {
          auto duplicateMixers = mixers;
          duplicateMixers.erase(duplicateMixers.begin());
          for (const auto& duplicateMixer : duplicateMixers) {
            if (el->getImpl<detail::AirLoopHVACOutdoorAirSystemEquipmentList_Impl>()->removeEquipment(duplicateMixer)) {
              detail::addLoadInfo(context, "Removed duplicate OutdoorAir:Mixer '" + duplicateMixer.nameString()
                                             + "' from AirLoopHVAC:OutdoorAirSystem '" + oaSystem.nameString() + "'.");
            }
          }
        }
      }

      OS_ASSERT(mixer);

      if (!mixer->getModelObjectTarget<openstudio::epmodel::Node>(returnAirPort())) {
        if (auto nodeName = mixer->getString(returnAirPort()); nodeName && !nodeName->empty()) {
          auto node = model().getOrCreateTransientByName<openstudio::epmodel::Node>(*nodeName);
          OS_ASSERT(mixer->setPointer(returnAirPort(), node.handle()));
        }
      }

      if (!mixer->getModelObjectTarget<openstudio::epmodel::Node>(mixedAirPort())) {
        if (auto nodeName = mixer->getString(mixedAirPort()); nodeName && !nodeName->empty()) {
          auto node = model().getOrCreateTransientByName<openstudio::epmodel::Node>(*nodeName);
          OS_ASSERT(mixer->setPointer(mixedAirPort(), node.handle()));
        }
      }

      if (!mixer->getModelObjectTarget<openstudio::epmodel::Node>(outdoorAirPort())) {
        const auto nodeName = [&]() -> std::string {
          if (auto value = mixer->getString(outdoorAirPort()); value && !value->empty()) {
            return *value;
          }
          return oaSystemName + " Outboard OA Node";
        }();
        auto node = model().getOrCreateTransientByName<openstudio::epmodel::Node>(nodeName);
        OS_ASSERT(mixer->setPointer(outdoorAirPort(), node.handle()));
      }

      if (!mixer->getModelObjectTarget<openstudio::epmodel::Node>(reliefAirPort())) {
        const auto nodeName = [&]() -> std::string {
          if (auto value = mixer->getString(reliefAirPort()); value && !value->empty()) {
            return *value;
          }
          return oaSystemName + " Relief Node";
        }();
        auto node = model().getOrCreateTransientByName<openstudio::epmodel::Node>(nodeName);
        OS_ASSERT(mixer->setPointer(reliefAirPort(), node.handle()));
      }

    }

    bool AirLoopHVACOutdoorAirSystem_Impl::addToNode(Node& node) {
      auto airLoop = node.airLoopHVAC();
      if (!airLoop) {
        return false;
      }

      if (!airLoop->supplyComponents(openstudio::epmodel::AirLoopHVACOutdoorAirSystem::iddObjectType()).empty()) {
        return false;
      }

      if (!airLoop->supplyComponent(node.handle())) {
        return false;
      }

      const auto nodeName = node.name();
      if (!nodeName || nodeName->empty()) {
        return false;
      }

      auto thisObject = getObject<openstudio::epmodel::ModelObject>();
      if (!thisObject.name()) {
        thisObject.createName();
        if (!thisObject.name()) {
          return false;
        }
      }

      auto branchList = airLoop->getImpl<openstudio::epmodel::detail::AirLoopHVAC_Impl>()->branchList();
      auto branches = branchList.branches();
      if (branches.empty()) {
        return false;
      }
      auto branch = branches.front();

      std::string returnNodeName;
      std::string mixedNodeName;

      const auto components = branch.components();
      if (components.empty()) {
        const auto supplyInlet = airLoop->supplyInletNode();
        const auto supplyOutlet = airLoop->supplyOutletNode();
        if (node != supplyInlet && node != supplyOutlet) {
          return false;
        }
        if (!branch.getImpl<openstudio::epmodel::detail::Branch_Impl>()->appendComponent(thisObject, supplyInlet.nameString(),
                                                                                         supplyOutlet.nameString())) {
          return false;
        }
        returnNodeName = supplyInlet.nameString();
        mixedNodeName = supplyOutlet.nameString();
      } else {
        bool inserted = false;
        for (std::size_t i = 0; i < components.size(); ++i) {
          auto inletNode = branch.componentInletNode(static_cast<unsigned>(i));
          auto outletNode = branch.componentOutletNode(static_cast<unsigned>(i));
          const bool matchesInlet = inletNode && openstudio::istringEqual(inletNode->nameString(), *nodeName);
          const bool matchesOutlet = outletNode && openstudio::istringEqual(outletNode->nameString(), *nodeName);
          if (!matchesInlet && !matchesOutlet) {
            continue;
          }

          const std::string newNodeName = *nodeName + " - " + thisObject.nameString() + " Mixed Air";
          const unsigned insertIndex = matchesInlet ? static_cast<unsigned>(i) : static_cast<unsigned>(i + 1);
          if (matchesOutlet && (i + 1u == components.size())) {
            returnNodeName = newNodeName;
            mixedNodeName = *nodeName;
          } else {
            returnNodeName = *nodeName;
            mixedNodeName = newNodeName;
          }
          if (!branch.getImpl<openstudio::epmodel::detail::Branch_Impl>()->insertComponent(insertIndex, thisObject, returnNodeName, mixedNodeName)) {
            return false;
          }

          if (matchesInlet) {
            auto newNode = model().getOrCreateTransientByName<openstudio::epmodel::Node>(newNodeName);
            if (!branch.getImpl<openstudio::epmodel::detail::Branch_Impl>()->setComponentInletNode(insertIndex + 1u, newNode)) {
              return false;
            }
          } else {
            auto newNode = model().getOrCreateTransientByName<openstudio::epmodel::Node>(newNodeName);
            if (!branch.getImpl<openstudio::epmodel::detail::Branch_Impl>()->setComponentOutletNode(insertIndex - 1u, newNode)) {
              return false;
            }
          }

          inserted = true;
          break;
        }

        if (!inserted) {
          return false;
        }
      }

      auto mixerObject = outdoorAirMixer();
      auto returnNode = model().getOrCreateTransientByName<openstudio::epmodel::Node>(returnNodeName);
      auto mixedNode = model().getOrCreateTransientByName<openstudio::epmodel::Node>(mixedNodeName);
      if (!mixerObject.setPointer(returnAirPort(), returnNode.handle())) {
        return false;
      }
      if (!mixerObject.setPointer(mixedAirPort(), mixedNode.handle())) {
        return false;
      }

      auto airLoopImpl = airLoop->getImpl<openstudio::epmodel::detail::AirLoopHVAC_Impl>();
      OS_ASSERT(airLoopImpl);
      airLoopImpl->syncControllerMechanicalVentilationZoneOutdoorAirEntries();
      airLoopImpl->syncSetpointManagerMixedAirFanNodes();
      return true;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
