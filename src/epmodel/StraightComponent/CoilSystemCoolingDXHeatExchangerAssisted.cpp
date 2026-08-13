/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/CoilSystemCoolingDXHeatExchangerAssisted.hpp"
#include "StraightComponent/CoilSystemCoolingDXHeatExchangerAssisted_Impl.hpp"

#include "AirToAirComponent/AirToAirComponent.hpp"
#include "AirToAirComponent/HeatExchangerAirToAirSensibleAndLatent.hpp"
#include "AirToAirComponent/HeatExchangerAirToAirSensibleAndLatent_Impl.hpp"
#include "AirToAirComponent/HeatExchangerDesiccantBalancedFlow.hpp"
#include "HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "Model.hpp"
#include "ModelObject.hpp"
#include "ModelObject/ModelObject_Impl.hpp"
#include "StraightComponent/CoilCoolingDXSingleSpeed.hpp"
#include "StraightComponent/Node.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/CoilSystem_Cooling_DX_HeatExchangerAssisted_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

#include <sstream>
#include <stdexcept>

namespace openstudio {
namespace epmodel {

  namespace {

    constexpr auto kHeatExchangerField = openstudio::CoilSystem_Cooling_DX_HeatExchangerAssistedFields::HeatExchangerName;
    constexpr auto kCoolingCoilField = openstudio::CoilSystem_Cooling_DX_HeatExchangerAssistedFields::CoolingCoilName;
    constexpr auto kHeatExchangerObjectTypeField = openstudio::CoilSystem_Cooling_DX_HeatExchangerAssistedFields::HeatExchangerObjectType;
    constexpr auto kCoolingCoilObjectTypeField = openstudio::CoilSystem_Cooling_DX_HeatExchangerAssistedFields::CoolingCoilObjectType;

  }  // namespace

  CoilSystemCoolingDXHeatExchangerAssisted::CoilSystemCoolingDXHeatExchangerAssisted(const Model& model)
    : StraightComponent(CoilSystemCoolingDXHeatExchangerAssisted::iddObjectType(), model) {
    CoilCoolingDXSingleSpeed coolingCoil(model);
    OS_ASSERT(setCoolingCoil(coolingCoil));

    HeatExchangerAirToAirSensibleAndLatent heatExchanger(model);
    OS_ASSERT(heatExchanger.setSupplyAirOutletTemperatureControl(false));
    OS_ASSERT(setHeatExchanger(heatExchanger));
  }

  CoilSystemCoolingDXHeatExchangerAssisted::CoilSystemCoolingDXHeatExchangerAssisted(const Model& model, const AirToAirComponent& heatExchanger)
    : StraightComponent(CoilSystemCoolingDXHeatExchangerAssisted::iddObjectType(), model) {
    if (heatExchanger.model() != model) {
      remove();
      throw std::invalid_argument("The assisted DX coil-system heat exchanger must belong to the same model.");
    }

    CoilCoolingDXSingleSpeed coolingCoil(model);
    OS_ASSERT(setCoolingCoil(coolingCoil));
    if (!setHeatExchanger(heatExchanger)) {
      remove();
      std::ostringstream message;
      message << "Unable to set " << briefDescription() << "'s Heat Exchanger " << heatExchanger.briefDescription() << '.';
      throw std::runtime_error(message.str());
    }
  }

  CoilSystemCoolingDXHeatExchangerAssisted::CoilSystemCoolingDXHeatExchangerAssisted(
    std::shared_ptr<detail::CoilSystemCoolingDXHeatExchangerAssisted_Impl> impl)
    : StraightComponent(std::move(impl)) {}

  IddObjectType CoilSystemCoolingDXHeatExchangerAssisted::iddObjectType() {
    return IddObjectType::CoilSystem_Cooling_DX_HeatExchangerAssisted;
  }

  AirToAirComponent CoilSystemCoolingDXHeatExchangerAssisted::heatExchanger() const {
    return getImpl<detail::CoilSystemCoolingDXHeatExchangerAssisted_Impl>()->heatExchanger();
  }

  bool CoilSystemCoolingDXHeatExchangerAssisted::setHeatExchanger(const AirToAirComponent& heatExchanger) {
    return getImpl<detail::CoilSystemCoolingDXHeatExchangerAssisted_Impl>()->setHeatExchanger(heatExchanger);
  }

  StraightComponent CoilSystemCoolingDXHeatExchangerAssisted::coolingCoil() const {
    return getImpl<detail::CoilSystemCoolingDXHeatExchangerAssisted_Impl>()->coolingCoil();
  }

  bool CoilSystemCoolingDXHeatExchangerAssisted::setCoolingCoil(const StraightComponent& coolingCoil) {
    return getImpl<detail::CoilSystemCoolingDXHeatExchangerAssisted_Impl>()->setCoolingCoil(coolingCoil);
  }

  bool CoilSystemCoolingDXHeatExchangerAssisted::addToNode(Node& node) {
    return getImpl<detail::CoilSystemCoolingDXHeatExchangerAssisted_Impl>()->addToNode(node);
  }

  std::vector<std::string> CoilSystemCoolingDXHeatExchangerAssisted::heatExchangerObjectTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::CoilSystem_Cooling_DX_HeatExchangerAssistedFields::HeatExchangerObjectType);
  }

  std::vector<std::string> CoilSystemCoolingDXHeatExchangerAssisted::coolingCoilObjectTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::CoilSystem_Cooling_DX_HeatExchangerAssistedFields::CoolingCoilObjectType);
  }

  // Heat exchanger object-type accessors
  std::string CoilSystemCoolingDXHeatExchangerAssisted::heatExchangerObjectType() const {
    return getImpl<detail::CoilSystemCoolingDXHeatExchangerAssisted_Impl>()->heatExchangerObjectType();
  }

  bool CoilSystemCoolingDXHeatExchangerAssisted::setHeatExchangerObjectType(const std::string& heatExchangerObjectType) {
    return getImpl<detail::CoilSystemCoolingDXHeatExchangerAssisted_Impl>()->setHeatExchangerObjectType(heatExchangerObjectType);
  }

  // Cooling coil object-type accessors
  std::string CoilSystemCoolingDXHeatExchangerAssisted::coolingCoilObjectType() const {
    return getImpl<detail::CoilSystemCoolingDXHeatExchangerAssisted_Impl>()->coolingCoilObjectType();
  }

  bool CoilSystemCoolingDXHeatExchangerAssisted::setCoolingCoilObjectType(const std::string& coolingCoilObjectType) {
    return getImpl<detail::CoilSystemCoolingDXHeatExchangerAssisted_Impl>()->setCoolingCoilObjectType(coolingCoilObjectType);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    namespace {

      template <typename T>
      boost::optional<T> optionalTarget(const ModelObject_Impl& impl, unsigned fieldIndex) {
        return impl.getObject<ModelObject>().getModelObjectTarget<T>(fieldIndex);
      }

      template <typename T>
      T requiredTarget(const ModelObject_Impl& impl, unsigned fieldIndex, const char* label) {
        auto value = optionalTarget<T>(impl, fieldIndex);
        if (!value) {
          std::ostringstream message;
          message << impl.briefDescription() << " does not have a " << label << " attached.";
          throw std::runtime_error(message.str());
        }
        return *value;
      }

      template <typename T>
      bool setTypedRelationship(ModelObject_Impl& impl, unsigned objectTypeField, unsigned objectField, const T& target) {
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

      bool clearHeatExchangerNodes(AirToAirComponent heatExchanger) {
        auto impl = heatExchanger.getImpl<ModelObject_Impl>();
        return impl->setPointer(heatExchanger.primaryAirInletPort(), Handle(), false)
               && impl->setPointer(heatExchanger.primaryAirOutletPort(), Handle(), false)
               && impl->setPointer(heatExchanger.secondaryAirInletPort(), Handle(), false)
               && impl->setPointer(heatExchanger.secondaryAirOutletPort(), Handle(), false);
      }

      bool clearCoolingCoilNodes(StraightComponent coolingCoil) {
        auto impl = coolingCoil.getImpl<ModelObject_Impl>();
        return impl->setPointer(coolingCoil.inletPort(), Handle(), false) && impl->setPointer(coolingCoil.outletPort(), Handle(), false);
      }

    }  // namespace

    unsigned CoilSystemCoolingDXHeatExchangerAssisted_Impl::inletPort() const {
      // EnergyPlus CoilSystem:Cooling:DX:HeatExchangerAssisted has no direct inlet/outlet node fields.
      return 0;
    }

    unsigned CoilSystemCoolingDXHeatExchangerAssisted_Impl::outletPort() const {
      // Node connectivity is delegated to the referenced heat exchanger/cooling coil.
      return 0;
    }

    boost::optional<ModelObject> CoilSystemCoolingDXHeatExchangerAssisted_Impl::inletModelObject() const {
      if (auto heatExchanger = optionalTarget<AirToAirComponent>(*this, kHeatExchangerField)) {
        return heatExchanger->primaryAirInletModelObject();
      }
      return boost::none;
    }

    boost::optional<ModelObject> CoilSystemCoolingDXHeatExchangerAssisted_Impl::outletModelObject() const {
      if (auto heatExchanger = optionalTarget<AirToAirComponent>(*this, kHeatExchangerField)) {
        return heatExchanger->secondaryAirOutletModelObject();
      }
      return boost::none;
    }

    bool CoilSystemCoolingDXHeatExchangerAssisted_Impl::addToNode(Node& /*node*/) {
      return false;
    }

    std::vector<ModelObject> CoilSystemCoolingDXHeatExchangerAssisted_Impl::children() const {
      std::vector<ModelObject> result;
      if (auto coolingCoil = optionalTarget<StraightComponent>(*this, kCoolingCoilField)) {
        result.push_back(coolingCoil->cast<ModelObject>());
      }
      if (auto heatExchanger = optionalTarget<AirToAirComponent>(*this, kHeatExchangerField)) {
        result.push_back(heatExchanger->cast<ModelObject>());
      }
      return result;
    }

    std::vector<openstudio::IdfObject> CoilSystemCoolingDXHeatExchangerAssisted_Impl::remove() {
      if (!isRemovable()) {
        return {};
      }

      const auto ownedChildren = children();
      auto removedParent = StraightComponent_Impl::remove();
      if (removedParent.empty()) {
        return {};
      }

      std::vector<openstudio::IdfObject> result;
      for (const auto& child : ownedChildren) {
        if (auto component = child.optionalCast<HVACComponent>()) {
          auto removed = component->remove();
          result.insert(result.end(), removed.begin(), removed.end());
        }
      }
      result.insert(result.end(), removedParent.begin(), removedParent.end());
      return result;
    }

    void CoilSystemCoolingDXHeatExchangerAssisted_Impl::disconnect() {
      if (auto heatExchanger = optionalTarget<AirToAirComponent>(*this, kHeatExchangerField)) {
        clearHeatExchangerNodes(*heatExchanger);
      }
      if (auto coolingCoil = optionalTarget<StraightComponent>(*this, kCoolingCoilField)) {
        clearCoolingCoilNodes(*coolingCoil);
      }
    }

    bool CoilSystemCoolingDXHeatExchangerAssisted_Impl::setAirInletNode(const Node& node) {
      if (node.model() != model()) {
        return false;
      }
      return reconcileContainedAirPath(node, outletModelObject() ? outletModelObject()->optionalCast<Node>() : boost::none);
    }

    bool CoilSystemCoolingDXHeatExchangerAssisted_Impl::setAirOutletNode(const Node& node) {
      if (node.model() != model()) {
        return false;
      }
      return reconcileContainedAirPath(inletModelObject() ? inletModelObject()->optionalCast<Node>() : boost::none, node);
    }

    bool CoilSystemCoolingDXHeatExchangerAssisted_Impl::reconcileContainedAirPath(const boost::optional<Node>& inletNode,
                                                                                  const boost::optional<Node>& outletNode) {
      auto heatExchanger = optionalTarget<AirToAirComponent>(*this, kHeatExchangerField);
      auto coolingCoil = optionalTarget<StraightComponent>(*this, kCoolingCoilField);
      if (!heatExchanger || !coolingCoil) {
        return false;
      }

      auto thisObject = getObject<ModelObject>();
      if (!thisObject.name()) {
        thisObject.createName();
      }
      const auto baseName = thisObject.nameString();
      const auto matchingConnector = [&](const boost::optional<ModelObject>& first, const boost::optional<ModelObject>& second) {
        auto firstNode = first ? first->optionalCast<Node>() : boost::none;
        auto secondNode = second ? second->optionalCast<Node>() : boost::none;
        if (!firstNode || !secondNode || firstNode->handle() != secondNode->handle()) {
          return boost::optional<Node>();
        }
        if ((inletNode && firstNode->handle() == inletNode->handle()) || (outletNode && firstNode->handle() == outletNode->handle())) {
          return boost::optional<Node>();
        }
        return firstNode;
      };

      auto supplyOutletNode = matchingConnector(heatExchanger->primaryAirOutletModelObject(), coolingCoil->inletModelObject());
      if (!supplyOutletNode) {
        supplyOutletNode = model().getOrCreateTransientByName<Node>(baseName + " HX Supply Air Outlet - Cooling Inlet Node");
      }
      auto exhaustInletNode = matchingConnector(coolingCoil->outletModelObject(), heatExchanger->secondaryAirInletModelObject());
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
      result = coolingCoilImpl->setPointer(coolingCoil->inletPort(), supplyOutletNode->handle(), false) && result;
      result = coolingCoilImpl->setPointer(coolingCoil->outletPort(), exhaustInletNode->handle(), false) && result;
      result = heatExchangerImpl->setPointer(heatExchanger->secondaryAirInletPort(), exhaustInletNode->handle(), false) && result;
      if (outletNode) {
        result = heatExchangerImpl->setPointer(heatExchanger->secondaryAirOutletPort(), outletNode->handle(), false) && result;
      }
      return result;
    }

    AirToAirComponent CoilSystemCoolingDXHeatExchangerAssisted_Impl::heatExchanger() const {
      return requiredTarget<AirToAirComponent>(*this, kHeatExchangerField, "Heat Exchanger");
    }

    bool CoilSystemCoolingDXHeatExchangerAssisted_Impl::setHeatExchanger(const AirToAirComponent& heatExchanger) {
      if (auto owner = heatExchanger.containingHVACComponent(); owner && owner->handle() != handle()) {
        return false;
      }
      if (heatExchanger.airLoopHVACOutdoorAirSystem()) {
        return false;
      }

      const auto oldHeatExchanger = optionalTarget<AirToAirComponent>(*this, kHeatExchangerField);
      const auto inletNode = inletModelObject() ? inletModelObject()->optionalCast<Node>() : boost::none;
      const auto outletNode = outletModelObject() ? outletModelObject()->optionalCast<Node>() : boost::none;
      if (!setTypedRelationship(*this, kHeatExchangerObjectTypeField, kHeatExchangerField, heatExchanger)) {
        return false;
      }
      if (oldHeatExchanger && oldHeatExchanger->handle() != heatExchanger.handle()) {
        clearHeatExchangerNodes(*oldHeatExchanger);
      }
      if (!optionalTarget<StraightComponent>(*this, kCoolingCoilField)) {
        return true;
      }
      return reconcileContainedAirPath(inletNode, outletNode);
    }

    StraightComponent CoilSystemCoolingDXHeatExchangerAssisted_Impl::coolingCoil() const {
      return requiredTarget<StraightComponent>(*this, kCoolingCoilField, "Cooling Coil");
    }

    bool CoilSystemCoolingDXHeatExchangerAssisted_Impl::setCoolingCoil(const StraightComponent& coolingCoil) {
      if (auto owner = coolingCoil.containingHVACComponent(); owner && owner->handle() != handle()) {
        return false;
      }
      if (coolingCoil.loop() || coolingCoil.airLoopHVACOutdoorAirSystem()) {
        return false;
      }

      const auto oldCoolingCoil = optionalTarget<StraightComponent>(*this, kCoolingCoilField);
      const auto inletNode = inletModelObject() ? inletModelObject()->optionalCast<Node>() : boost::none;
      const auto outletNode = outletModelObject() ? outletModelObject()->optionalCast<Node>() : boost::none;
      if (!setTypedRelationship(*this, kCoolingCoilObjectTypeField, kCoolingCoilField, coolingCoil)) {
        return false;
      }
      if (oldCoolingCoil && oldCoolingCoil->handle() != coolingCoil.handle()) {
        clearCoolingCoilNodes(*oldCoolingCoil);
      }
      if (!optionalTarget<AirToAirComponent>(*this, kHeatExchangerField)) {
        return true;
      }
      return reconcileContainedAirPath(inletNode, outletNode);
    }

    void CoilSystemCoolingDXHeatExchangerAssisted_Impl::doCanonicalize(LoadContext& context) {
      StraightComponent_Impl::doCanonicalize(context);

      auto heatExchanger = optionalTarget<AirToAirComponent>(*this, kHeatExchangerField);
      if (!heatExchanger) {
        heatExchanger = HeatExchangerAirToAirSensibleAndLatent(model());
        heatExchanger->cast<HeatExchangerAirToAirSensibleAndLatent>().setSupplyAirOutletTemperatureControl(false);
        detail::addLoadInfo(context,
                            "Created the missing heat exchanger for assisted DX coil system '" + getObject<ModelObject>().nameString() + "'.");
      }
      OS_ASSERT(setTypedRelationship(*this, kHeatExchangerObjectTypeField, kHeatExchangerField, *heatExchanger));

      auto coolingCoil = optionalTarget<StraightComponent>(*this, kCoolingCoilField);
      if (!coolingCoil) {
        coolingCoil = CoilCoolingDXSingleSpeed(model());
        detail::addLoadInfo(context, "Created the missing cooling coil for assisted DX coil system '" + getObject<ModelObject>().nameString() + "'.");
      }
      OS_ASSERT(setTypedRelationship(*this, kCoolingCoilObjectTypeField, kCoolingCoilField, *coolingCoil));

      const auto inletNode = inletModelObject() ? inletModelObject()->optionalCast<Node>() : boost::none;
      const auto outletNode = outletModelObject() ? outletModelObject()->optionalCast<Node>() : boost::none;
      reconcileContainedAirPath(inletNode, outletNode);
    }

    // Heat exchanger object-type accessors
    std::string CoilSystemCoolingDXHeatExchangerAssisted_Impl::heatExchangerObjectType() const {
      const auto value = getString(openstudio::CoilSystem_Cooling_DX_HeatExchangerAssistedFields::HeatExchangerObjectType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilSystemCoolingDXHeatExchangerAssisted_Impl::setHeatExchangerObjectType(const std::string& heatExchangerObjectType) {
      return setString(openstudio::CoilSystem_Cooling_DX_HeatExchangerAssistedFields::HeatExchangerObjectType, heatExchangerObjectType);
    }

    // Cooling coil object-type accessors
    std::string CoilSystemCoolingDXHeatExchangerAssisted_Impl::coolingCoilObjectType() const {
      const auto value = getString(openstudio::CoilSystem_Cooling_DX_HeatExchangerAssistedFields::CoolingCoilObjectType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilSystemCoolingDXHeatExchangerAssisted_Impl::setCoolingCoilObjectType(const std::string& coolingCoilObjectType) {
      return setString(openstudio::CoilSystem_Cooling_DX_HeatExchangerAssistedFields::CoolingCoilObjectType, coolingCoilObjectType);
    }

    std::vector<std::string> CoilSystemCoolingDXHeatExchangerAssisted_Impl::heatExchangerObjectTypeValues() const {
      return openstudio::epmodel::CoilSystemCoolingDXHeatExchangerAssisted::heatExchangerObjectTypeValues();
    }

    std::vector<std::string> CoilSystemCoolingDXHeatExchangerAssisted_Impl::coolingCoilObjectTypeValues() const {
      return openstudio::epmodel::CoilSystemCoolingDXHeatExchangerAssisted::coolingCoilObjectTypeValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
