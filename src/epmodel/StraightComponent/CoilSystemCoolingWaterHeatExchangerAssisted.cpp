/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/CoilSystemCoolingWaterHeatExchangerAssisted.hpp"
#include "StraightComponent/CoilSystemCoolingWaterHeatExchangerAssisted_Impl.hpp"

#include "AirToAirComponent/AirToAirComponent.hpp"
#include "AirToAirComponent/AirToAirComponent_Impl.hpp"
#include "AirToAirComponent/HeatExchangerAirToAirSensibleAndLatent.hpp"
#include "Branch.hpp"
#include "Branch_Impl.hpp"
#include "BranchList.hpp"
#include "Loop/AirLoopHVAC.hpp"
#include "Loop/AirLoopHVAC_Impl.hpp"
#include "Model.hpp"
#include "ModelObject.hpp"
#include "ModelObject/ModelObject_Impl.hpp"
#include "Node.hpp"
#include "SetpointManager/SetpointManagerMixedAir.hpp"
#include "SetpointManager/SetpointManagerMixedAir_Impl.hpp"
#include "HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "StraightComponent/StraightComponent.hpp"
#include "WaterToAirComponent/CoilCoolingWater.hpp"
#include "WaterToAirComponent/CoilCoolingWater_Impl.hpp"
#include "WaterToAirComponent/WaterToAirComponent.hpp"
#include "WaterToAirComponent/WaterToAirComponent_Impl.hpp"

#include <algorithm>
#include <sstream>
#include <stdexcept>

#include <utilities/core/Assert.hpp>
#include <utilities/idd/CoilSystem_Cooling_Water_HeatExchangerAssisted_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/SetpointManager_MixedAir_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  namespace {

    constexpr auto kHeatExchangerField = openstudio::CoilSystem_Cooling_Water_HeatExchangerAssistedFields::HeatExchangerName;
    constexpr auto kCoolingCoilField = openstudio::CoilSystem_Cooling_Water_HeatExchangerAssistedFields::CoolingCoilName;
    constexpr auto kHeatExchangerObjectTypeField = openstudio::CoilSystem_Cooling_Water_HeatExchangerAssistedFields::HeatExchangerObjectType;
    constexpr auto kCoolingCoilObjectTypeField = openstudio::CoilSystem_Cooling_Water_HeatExchangerAssistedFields::CoolingCoilObjectType;

  }  // namespace

  CoilSystemCoolingWaterHeatExchangerAssisted::CoilSystemCoolingWaterHeatExchangerAssisted(const Model& model)
    : StraightComponent(CoilSystemCoolingWaterHeatExchangerAssisted::iddObjectType(), model) {
    CoilCoolingWater coolingCoil(model);
    OS_ASSERT(setCoolingCoil(coolingCoil));

    HeatExchangerAirToAirSensibleAndLatent heatExchanger(model);
    OS_ASSERT(setHeatExchanger(heatExchanger));
  }

  CoilSystemCoolingWaterHeatExchangerAssisted::CoilSystemCoolingWaterHeatExchangerAssisted(const Model& model, const AirToAirComponent& heatExchanger)
    : StraightComponent(CoilSystemCoolingWaterHeatExchangerAssisted::iddObjectType(), model) {
    if (heatExchanger.model() != model) {
      remove();
      throw std::invalid_argument("The assisted water coil-system heat exchanger must belong to the same model.");
    }

    if (!setHeatExchanger(heatExchanger)) {
      remove();
      std::ostringstream message;
      message << "Unable to set " << briefDescription() << "'s Heat Exchanger " << heatExchanger.briefDescription() << '.';
      throw std::runtime_error(message.str());
    }

    CoilCoolingWater coolingCoil(model);
    OS_ASSERT(setCoolingCoil(coolingCoil));
  }

  CoilSystemCoolingWaterHeatExchangerAssisted::CoilSystemCoolingWaterHeatExchangerAssisted(
    std::shared_ptr<detail::CoilSystemCoolingWaterHeatExchangerAssisted_Impl> impl)
    : StraightComponent(std::move(impl)) {}

  IddObjectType CoilSystemCoolingWaterHeatExchangerAssisted::iddObjectType() {
    return IddObjectType::CoilSystem_Cooling_Water_HeatExchangerAssisted;
  }

  std::vector<std::string> CoilSystemCoolingWaterHeatExchangerAssisted::heatExchangerObjectTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::CoilSystem_Cooling_Water_HeatExchangerAssistedFields::HeatExchangerObjectType);
  }

  AirToAirComponent CoilSystemCoolingWaterHeatExchangerAssisted::heatExchanger() const {
    return getImpl<detail::CoilSystemCoolingWaterHeatExchangerAssisted_Impl>()->heatExchanger();
  }

  bool CoilSystemCoolingWaterHeatExchangerAssisted::setHeatExchanger(const AirToAirComponent& heatExchanger) {
    return getImpl<detail::CoilSystemCoolingWaterHeatExchangerAssisted_Impl>()->setHeatExchanger(heatExchanger);
  }

  WaterToAirComponent CoilSystemCoolingWaterHeatExchangerAssisted::coolingCoil() const {
    return getImpl<detail::CoilSystemCoolingWaterHeatExchangerAssisted_Impl>()->coolingCoil();
  }

  bool CoilSystemCoolingWaterHeatExchangerAssisted::setCoolingCoil(const WaterToAirComponent& coolingCoil) {
    return getImpl<detail::CoilSystemCoolingWaterHeatExchangerAssisted_Impl>()->setCoolingCoil(coolingCoil);
  }

  bool CoilSystemCoolingWaterHeatExchangerAssisted::addToNode(Node& node) {
    return getImpl<detail::CoilSystemCoolingWaterHeatExchangerAssisted_Impl>()->addToNode(node);
  }

  std::string CoilSystemCoolingWaterHeatExchangerAssisted::heatExchangerObjectType() const {
    return getImpl<detail::CoilSystemCoolingWaterHeatExchangerAssisted_Impl>()->heatExchangerObjectType();
  }

  bool CoilSystemCoolingWaterHeatExchangerAssisted::setHeatExchangerObjectType(const std::string& heatExchangerObjectType) {
    return getImpl<detail::CoilSystemCoolingWaterHeatExchangerAssisted_Impl>()->setHeatExchangerObjectType(heatExchangerObjectType);
  }

  std::vector<std::string> CoilSystemCoolingWaterHeatExchangerAssisted::coolingCoilObjectTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::CoilSystem_Cooling_Water_HeatExchangerAssistedFields::CoolingCoilObjectType);
  }

  std::string CoilSystemCoolingWaterHeatExchangerAssisted::coolingCoilObjectType() const {
    return getImpl<detail::CoilSystemCoolingWaterHeatExchangerAssisted_Impl>()->coolingCoilObjectType();
  }

  bool CoilSystemCoolingWaterHeatExchangerAssisted::setCoolingCoilObjectType(const std::string& coolingCoilObjectType) {
    return getImpl<detail::CoilSystemCoolingWaterHeatExchangerAssisted_Impl>()->setCoolingCoilObjectType(coolingCoilObjectType);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    namespace {

      template <typename T>
      boost::optional<T> optionalPointerTarget(const ModelObject_Impl& impl, unsigned fieldIndex) {
        return impl.getObject<ModelObject>().getModelObjectTarget<T>(fieldIndex);
      }

      template <typename T>
      T requiredPointerTarget(const ModelObject_Impl& impl, unsigned fieldIndex, const char* label) {
        auto value = optionalPointerTarget<T>(impl, fieldIndex);
        if (!value) {
          std::ostringstream message;
          message << impl.briefDescription() << " does not have a " << label << " attached.";
          throw std::runtime_error(message.str());
        }
        return *value;
      }

      template <typename T>
      bool setPointerRelationship(ModelObject_Impl& impl, unsigned objectTypeField, unsigned objectField, const T& target) {
        if (target.model() != impl.model()) {
          return false;
        }

        const auto oldType = impl.getString(objectTypeField).value_or("");
        const auto oldTarget = impl.getObject<ModelObject>().getTarget(objectField);
        if (!impl.setString(objectTypeField, target.iddObject().name()) || !impl.setPointer(objectField, target.handle(), false)) {
          OS_ASSERT(impl.setString(objectTypeField, oldType));
          OS_ASSERT(impl.setPointer(objectField, oldTarget ? oldTarget->handle() : Handle(), false));
          return false;
        }
        return true;
      }

      bool clearHeatExchangerAirNodes(AirToAirComponent heatExchanger) {
        auto impl = heatExchanger.getImpl<ModelObject_Impl>();
        return impl->setPointer(heatExchanger.primaryAirInletPort(), Handle(), false)
               && impl->setPointer(heatExchanger.primaryAirOutletPort(), Handle(), false)
               && impl->setPointer(heatExchanger.secondaryAirInletPort(), Handle(), false)
               && impl->setPointer(heatExchanger.secondaryAirOutletPort(), Handle(), false);
      }

      bool clearCoolingCoilAirNodes(WaterToAirComponent coolingCoil) {
        auto impl = coolingCoil.getImpl<ModelObject_Impl>();
        const bool result =
          impl->setPointer(coolingCoil.airInletPort(), Handle(), false) && impl->setPointer(coolingCoil.airOutletPort(), Handle(), false);
        if (auto coil = coolingCoil.optionalCast<CoilCoolingWater>()) {
          coil->getImpl<CoilCoolingWater_Impl>()->syncControllerAfterAirTopologyChange();
        }
        return result;
      }

    }  // namespace

    bool CoilSystemCoolingWaterHeatExchangerAssisted_Impl::addToNode(Node& node) {
      auto airLoop = node.airLoopHVAC();
      if (!(airLoop && airLoop->supplyComponent(node.handle()))) {
        return false;
      }

      if (!StraightComponent_Impl::addToNode(node)) {
        return false;
      }

      const auto boundaries = branchBoundaryNodes();
      return boundaries && reconcileContainedAirPath(boundaries->first, boundaries->second);
    }

    boost::optional<std::pair<Node, Node>> CoilSystemCoolingWaterHeatExchangerAssisted_Impl::branchBoundaryNodes() const {
      const auto thisObject = getObject<ModelObject>();
      const auto thisComponent = thisObject.optionalCast<HVACComponent>();
      const auto airLoop = thisComponent ? thisComponent->airLoopHVAC() : boost::none;
      if (!airLoop) {
        return boost::none;
      }

      const auto branches = airLoop->getImpl<AirLoopHVAC_Impl>()->branchList().branches();
      boost::optional<std::pair<Node, Node>> result;
      for (const auto& branch : branches) {
        const auto components = branch.components();
        for (unsigned i = 0; i < components.size(); ++i) {
          if (components[i].handle() != handle()) {
            continue;
          }
          const auto inletNode = branch.componentInletNode(i);
          const auto outletNode = branch.componentOutletNode(i);
          if (!inletNode || !outletNode || result) {
            return boost::none;
          }
          result = std::make_pair(*inletNode, *outletNode);
        }
      }
      return result;
    }

    boost::optional<ModelObject> CoilSystemCoolingWaterHeatExchangerAssisted_Impl::inletModelObject() const {
      if (auto heatExchanger = optionalPointerTarget<AirToAirComponent>(*this, kHeatExchangerField)) {
        return heatExchanger->primaryAirInletModelObject();
      }
      return boost::none;
    }

    boost::optional<ModelObject> CoilSystemCoolingWaterHeatExchangerAssisted_Impl::outletModelObject() const {
      if (auto heatExchanger = optionalPointerTarget<AirToAirComponent>(*this, kHeatExchangerField)) {
        return heatExchanger->secondaryAirOutletModelObject();
      }
      return boost::none;
    }

    std::vector<ModelObject> CoilSystemCoolingWaterHeatExchangerAssisted_Impl::children() const {
      std::vector<ModelObject> result;
      const auto thisObject = getObject<ModelObject>();

      if (auto coolingCoil = thisObject.getModelObjectTarget<WaterToAirComponent>(kCoolingCoilField)) {
        result.push_back(coolingCoil->cast<ModelObject>());
      }
      if (auto heatExchanger = thisObject.getModelObjectTarget<AirToAirComponent>(kHeatExchangerField)) {
        result.push_back(heatExchanger->cast<ModelObject>());
      }

      return result;
    }

    std::vector<IdfObject> CoilSystemCoolingWaterHeatExchangerAssisted_Impl::remove() {
      if (!isRemovable()) {
        return {};
      }

      const auto ownedChildren = children();
      auto removedParent = StraightComponent_Impl::remove();
      if (removedParent.empty()) {
        return {};
      }

      // The cooling coil may have an independent plant attachment. Removing it
      // through its normal path after containment is released heals that branch.
      std::vector<IdfObject> result;
      for (const auto& child : ownedChildren) {
        if (auto component = child.optionalCast<HVACComponent>()) {
          auto removed = component->remove();
          result.insert(result.end(), removed.begin(), removed.end());
        }
      }
      result.insert(result.end(), removedParent.begin(), removedParent.end());
      return result;
    }

    void CoilSystemCoolingWaterHeatExchangerAssisted_Impl::disconnect() {
      removeStorageSetpointManager();
      if (auto heatExchanger = optionalPointerTarget<AirToAirComponent>(*this, kHeatExchangerField)) {
        clearHeatExchangerAirNodes(*heatExchanger);
      }
      if (auto coolingCoil = optionalPointerTarget<WaterToAirComponent>(*this, kCoolingCoilField)) {
        clearCoolingCoilAirNodes(*coolingCoil);
      }
    }

    unsigned CoilSystemCoolingWaterHeatExchangerAssisted_Impl::inletPort() const {
      // EnergyPlus CoilSystem:Cooling:Water:HeatExchangerAssisted has no direct inlet/outlet node fields.
      return 0;
    }

    unsigned CoilSystemCoolingWaterHeatExchangerAssisted_Impl::outletPort() const {
      // Node connectivity is delegated to the referenced heat exchanger/cooling coil.
      return 0;
    }

    bool CoilSystemCoolingWaterHeatExchangerAssisted_Impl::setAirInletNode(const Node& node) {
      if (node.model() != model()) {
        return false;
      }
      return reconcileContainedAirPath(node, outletModelObject() ? outletModelObject()->optionalCast<Node>() : boost::none);
    }

    bool CoilSystemCoolingWaterHeatExchangerAssisted_Impl::setAirOutletNode(const Node& node) {
      if (node.model() != model()) {
        return false;
      }
      return reconcileContainedAirPath(inletModelObject() ? inletModelObject()->optionalCast<Node>() : boost::none, node);
    }

    bool CoilSystemCoolingWaterHeatExchangerAssisted_Impl::reconcileContainedAirPath(const boost::optional<Node>& inletNode,
                                                                                     const boost::optional<Node>& outletNode) {
      auto heatExchanger = optionalPointerTarget<AirToAirComponent>(*this, kHeatExchangerField);
      auto coolingCoil = optionalPointerTarget<WaterToAirComponent>(*this, kCoolingCoilField);
      if (!heatExchanger || !coolingCoil) {
        return false;
      }

      auto thisObject = getObject<ModelObject>();
      if (!thisObject.name()) {
        thisObject.createName();
      }
      const auto baseName = thisObject.nameString();
      const auto matchingConnector = [&](const boost::optional<ModelObject>& first, const boost::optional<ModelObject>& second) {
        const auto firstNode = first ? first->optionalCast<Node>() : boost::none;
        const auto secondNode = second ? second->optionalCast<Node>() : boost::none;
        if (!firstNode || !secondNode || firstNode->handle() != secondNode->handle()) {
          return boost::optional<Node>();
        }
        if ((inletNode && firstNode->handle() == inletNode->handle()) || (outletNode && firstNode->handle() == outletNode->handle())) {
          return boost::optional<Node>();
        }
        return firstNode;
      };

      auto supplyOutletNode = matchingConnector(heatExchanger->primaryAirOutletModelObject(), coolingCoil->airInletModelObject());
      if (!supplyOutletNode) {
        supplyOutletNode = model().getOrCreateTransientByName<Node>(baseName + " HX Supply Air Outlet - Cooling Inlet Node");
      }
      auto exhaustInletNode = matchingConnector(coolingCoil->airOutletModelObject(), heatExchanger->secondaryAirInletModelObject());
      if (!exhaustInletNode) {
        exhaustInletNode = model().getOrCreateTransientByName<Node>(baseName + " HX Exhaust Air Inlet - Cooling Outlet Node");
      }

      bool result = true;
      auto heatExchangerImpl = heatExchanger->getImpl<ModelObject_Impl>();
      auto coolingCoilImpl = coolingCoil->getImpl<ModelObject_Impl>();
      if (inletNode) {
        result = heatExchangerImpl->setPointer(heatExchanger->primaryAirInletPort(), inletNode->handle(), false) && result;
      }
      result = heatExchangerImpl->setPointer(heatExchanger->primaryAirOutletPort(), supplyOutletNode->handle(), false) && result;
      result = coolingCoilImpl->setPointer(coolingCoil->airInletPort(), supplyOutletNode->handle(), false) && result;
      result = coolingCoilImpl->setPointer(coolingCoil->airOutletPort(), exhaustInletNode->handle(), false) && result;
      result = heatExchangerImpl->setPointer(heatExchanger->secondaryAirInletPort(), exhaustInletNode->handle(), false) && result;
      if (outletNode) {
        result = heatExchangerImpl->setPointer(heatExchanger->secondaryAirOutletPort(), outletNode->handle(), false) && result;
      }
      if (auto coil = coolingCoil->optionalCast<CoilCoolingWater>()) {
        coil->getImpl<CoilCoolingWater_Impl>()->syncControllerAfterAirTopologyChange();
      }
      syncStorageSetpointManager();
      return result;
    }

    void CoilSystemCoolingWaterHeatExchangerAssisted_Impl::syncStorageSetpointManager() {
      const auto thisComponent = getObject<ModelObject>().optionalCast<HVACComponent>();
      const auto airLoop = thisComponent ? thisComponent->airLoopHVAC() : boost::none;
      const auto coolingCoil = optionalPointerTarget<WaterToAirComponent>(*this, kCoolingCoilField);
      const auto setpointNodeObject = coolingCoil ? coolingCoil->airOutletModelObject() : boost::none;
      const auto setpointNode = setpointNodeObject ? setpointNodeObject->optionalCast<Node>() : boost::none;
      if (!airLoop || !setpointNode) {
        return;
      }

      boost::optional<StraightComponent> selectedFan;
      const auto supplyComponents = airLoop->supplyComponents();
      for (auto it = supplyComponents.rbegin(); it != supplyComponents.rend(); ++it) {
        const auto type = it->iddObject().type();
        const bool supportedFan = type == IddObjectType::Fan_ConstantVolume || type == IddObjectType::Fan_VariableVolume
                                  || type == IddObjectType::Fan_SystemModel || type == IddObjectType::Fan_ComponentModel;
        if (supportedFan) {
          selectedFan = it->optionalCast<StraightComponent>();
          break;
        }
      }
      if (!selectedFan) {
        removeStorageSetpointManager();
        return;
      }

      const auto fanInletObject = selectedFan->inletModelObject();
      const auto fanOutletObject = selectedFan->outletModelObject();
      const auto fanInletNode = fanInletObject ? fanInletObject->optionalCast<Node>() : boost::none;
      const auto fanOutletNode = fanOutletObject ? fanOutletObject->optionalCast<Node>() : boost::none;
      if (!fanInletNode || !fanOutletNode) {
        return;
      }

      const auto expectedName = setpointNode->nameString() + " OS Default SPM";
      auto setpointManager = model().getConcreteModelObjectByName<SetpointManagerMixedAir>(expectedName);
      if (!setpointManager) {
        for (const auto& candidate : model().getConcreteModelObjects<SetpointManagerMixedAir>()) {
          const auto candidateNode = candidate.setpointNode();
          if (candidateNode && candidateNode->handle() == setpointNode->handle() && candidate.nameString().ends_with(" OS Default SPM")) {
            setpointManager = candidate;
            break;
          }
        }
      }
      if (!setpointManager) {
        setpointManager = SetpointManagerMixedAir(model());
        OS_ASSERT(setpointManager->setName(expectedName));
      }

      OS_ASSERT(setpointManager->setControlVariable("Temperature"));
      OS_ASSERT(
        setpointManager->setPointer(openstudio::SetpointManager_MixedAirFields::ReferenceSetpointNodeName, airLoop->supplyOutletNode().handle()));
      OS_ASSERT(setpointManager->setPointer(openstudio::SetpointManager_MixedAirFields::FanInletNodeName, fanInletNode->handle()));
      OS_ASSERT(setpointManager->setPointer(openstudio::SetpointManager_MixedAirFields::FanOutletNodeName, fanOutletNode->handle()));
      OS_ASSERT(setpointManager->setPointer(openstudio::SetpointManager_MixedAirFields::SetpointNodeorNodeListName, setpointNode->handle()));
    }

    void CoilSystemCoolingWaterHeatExchangerAssisted_Impl::removeStorageSetpointManager() {
      const auto coolingCoil = optionalPointerTarget<WaterToAirComponent>(*this, kCoolingCoilField);
      const auto setpointNodeObject = coolingCoil ? coolingCoil->airOutletModelObject() : boost::none;
      const auto setpointNode = setpointNodeObject ? setpointNodeObject->optionalCast<Node>() : boost::none;
      if (!setpointNode) {
        return;
      }
      for (auto& candidate : model().getConcreteModelObjects<SetpointManagerMixedAir>()) {
        const auto candidateNode = candidate.setpointNode();
        if (candidateNode && candidateNode->handle() == setpointNode->handle() && candidate.nameString().ends_with(" OS Default SPM")) {
          candidate.remove();
        }
      }
    }

    AirToAirComponent CoilSystemCoolingWaterHeatExchangerAssisted_Impl::heatExchanger() const {
      return requiredPointerTarget<AirToAirComponent>(*this, kHeatExchangerField, "Heat Exchanger");
    }

    bool CoilSystemCoolingWaterHeatExchangerAssisted_Impl::setHeatExchanger(const AirToAirComponent& heatExchanger) {
      if (heatExchanger.model() != model()) {
        return false;
      }
      const auto allowedTypes = heatExchangerObjectTypeValues();
      if (std::find(allowedTypes.begin(), allowedTypes.end(), heatExchanger.iddObject().name()) == allowedTypes.end()) {
        return false;
      }
      if (auto owner = heatExchanger.containingHVACComponent(); owner && owner->handle() != handle()) {
        return false;
      }
      if (heatExchanger.airLoopHVAC() || heatExchanger.airLoopHVACOutdoorAirSystem()) {
        return false;
      }

      const auto oldHeatExchanger = optionalPointerTarget<AirToAirComponent>(*this, kHeatExchangerField);
      const auto inletNode = inletModelObject() ? inletModelObject()->optionalCast<Node>() : boost::none;
      const auto outletNode = outletModelObject() ? outletModelObject()->optionalCast<Node>() : boost::none;
      if (!setPointerRelationship(*this, kHeatExchangerObjectTypeField, kHeatExchangerField, heatExchanger)) {
        return false;
      }
      if (oldHeatExchanger && oldHeatExchanger->handle() != heatExchanger.handle()) {
        clearHeatExchangerAirNodes(*oldHeatExchanger);
      }
      if (!optionalPointerTarget<WaterToAirComponent>(*this, kCoolingCoilField)) {
        return true;
      }
      if (!inletNode && !outletNode) {
        return true;
      }
      return reconcileContainedAirPath(inletNode, outletNode);
    }

    WaterToAirComponent CoilSystemCoolingWaterHeatExchangerAssisted_Impl::coolingCoil() const {
      return requiredPointerTarget<WaterToAirComponent>(*this, kCoolingCoilField, "Cooling Coil");
    }

    bool CoilSystemCoolingWaterHeatExchangerAssisted_Impl::setCoolingCoil(const WaterToAirComponent& coolingCoil) {
      if (coolingCoil.model() != model()) {
        return false;
      }
      const auto allowedTypes = coolingCoilObjectTypeValues();
      if (std::find(allowedTypes.begin(), allowedTypes.end(), coolingCoil.iddObject().name()) == allowedTypes.end()) {
        return false;
      }
      if (auto owner = coolingCoil.containingHVACComponent(); owner && owner->handle() != handle()) {
        return false;
      }
      if (coolingCoil.airLoopHVAC() || coolingCoil.airLoopHVACOutdoorAirSystem()) {
        return false;
      }

      const auto oldCoolingCoil = optionalPointerTarget<WaterToAirComponent>(*this, kCoolingCoilField);
      const auto inletNode = inletModelObject() ? inletModelObject()->optionalCast<Node>() : boost::none;
      const auto outletNode = outletModelObject() ? outletModelObject()->optionalCast<Node>() : boost::none;
      if (!setPointerRelationship(*this, kCoolingCoilObjectTypeField, kCoolingCoilField, coolingCoil)) {
        return false;
      }
      if (oldCoolingCoil && oldCoolingCoil->handle() != coolingCoil.handle()) {
        clearCoolingCoilAirNodes(*oldCoolingCoil);
      }
      if (!optionalPointerTarget<AirToAirComponent>(*this, kHeatExchangerField)) {
        return true;
      }
      if (!inletNode && !outletNode) {
        return true;
      }
      return reconcileContainedAirPath(inletNode, outletNode);
    }

    void CoilSystemCoolingWaterHeatExchangerAssisted_Impl::doCanonicalize(LoadContext& context) {
      StraightComponent_Impl::doCanonicalize(context);

      auto heatExchanger = optionalPointerTarget<AirToAirComponent>(*this, kHeatExchangerField);
      if (!heatExchanger) {
        heatExchanger = HeatExchangerAirToAirSensibleAndLatent(model());
        detail::addLoadInfo(context,
                            "Created the missing heat exchanger for assisted water coil system '" + getObject<ModelObject>().nameString() + "'.");
      }
      OS_ASSERT(setPointerRelationship(*this, kHeatExchangerObjectTypeField, kHeatExchangerField, *heatExchanger));

      auto coolingCoil = optionalPointerTarget<WaterToAirComponent>(*this, kCoolingCoilField);
      if (!coolingCoil) {
        coolingCoil = CoilCoolingWater(model());
        detail::addLoadInfo(context,
                            "Created the missing cooling coil for assisted water coil system '" + getObject<ModelObject>().nameString() + "'.");
      }
      OS_ASSERT(setPointerRelationship(*this, kCoolingCoilObjectTypeField, kCoolingCoilField, *coolingCoil));

      if (const auto boundaries = branchBoundaryNodes()) {
        reconcileContainedAirPath(boundaries->first, boundaries->second);
      } else {
        const auto inletNode = inletModelObject() ? inletModelObject()->optionalCast<Node>() : boost::none;
        const auto outletNode = outletModelObject() ? outletModelObject()->optionalCast<Node>() : boost::none;
        if (inletNode || outletNode) {
          reconcileContainedAirPath(inletNode, outletNode);
        }
      }
    }

    std::string CoilSystemCoolingWaterHeatExchangerAssisted_Impl::heatExchangerObjectType() const {
      const auto value = getString(openstudio::CoilSystem_Cooling_Water_HeatExchangerAssistedFields::HeatExchangerObjectType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilSystemCoolingWaterHeatExchangerAssisted_Impl::setHeatExchangerObjectType(const std::string& heatExchangerObjectType) {
      const bool result =
        setString(openstudio::CoilSystem_Cooling_Water_HeatExchangerAssistedFields::HeatExchangerObjectType, heatExchangerObjectType);
      return result;
    }

    std::vector<std::string> CoilSystemCoolingWaterHeatExchangerAssisted_Impl::heatExchangerObjectTypeValues() const {
      return openstudio::epmodel::CoilSystemCoolingWaterHeatExchangerAssisted::heatExchangerObjectTypeValues();
    }

    std::string CoilSystemCoolingWaterHeatExchangerAssisted_Impl::coolingCoilObjectType() const {
      const auto value = getString(openstudio::CoilSystem_Cooling_Water_HeatExchangerAssistedFields::CoolingCoilObjectType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilSystemCoolingWaterHeatExchangerAssisted_Impl::setCoolingCoilObjectType(const std::string& coolingCoilObjectType) {
      const bool result = setString(openstudio::CoilSystem_Cooling_Water_HeatExchangerAssistedFields::CoolingCoilObjectType, coolingCoilObjectType);
      return result;
    }

    std::vector<std::string> CoilSystemCoolingWaterHeatExchangerAssisted_Impl::coolingCoilObjectTypeValues() const {
      return openstudio::epmodel::CoilSystemCoolingWaterHeatExchangerAssisted::coolingCoilObjectTypeValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
