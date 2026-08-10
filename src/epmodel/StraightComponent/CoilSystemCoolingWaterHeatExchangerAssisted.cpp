/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/CoilSystemCoolingWaterHeatExchangerAssisted.hpp"
#include "StraightComponent/CoilSystemCoolingWaterHeatExchangerAssisted_Impl.hpp"

#include "AirToAirComponent/AirToAirComponent.hpp"
#include "AirToAirComponent/AirToAirComponent_Impl.hpp"
#include "AirToAirComponent/HeatExchangerAirToAirSensibleAndLatent.hpp"
#include "Model.hpp"
#include "Loop/AirLoopHVAC.hpp"
#include "ModelObject.hpp"
#include "Node.hpp"
#include "HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "WaterToAirComponent/CoilCoolingWater.hpp"
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
      T requiredPointerTarget(const ModelObject_Impl& impl, unsigned fieldIndex, const char* label) {
        auto value = impl.getObject<ModelObject>().getModelObjectTarget<T>(fieldIndex);
        if (!value) {
          std::ostringstream message;
          message << impl.briefDescription() << " does not have a " << label << " attached.";
          throw std::runtime_error(message.str());
        }
        return *value;
      }

      template <typename T>
      bool setPointerRelationship(ModelObject_Impl& impl, unsigned objectTypeField, unsigned objectField, const T& target) {
        if (!impl.setString(objectTypeField, target.iddObject().name())) {
          return false;
        }
        return impl.setPointer(objectField, target.handle(), false);
      }

    }  // namespace

    bool CoilSystemCoolingWaterHeatExchangerAssisted_Impl::addToNode(Node& node) {
      if (node.airLoopHVACOutdoorAirSystem()) {
        return StraightComponent_Impl::addToNode(node);
      }

      auto airLoop = node.airLoopHVAC();
      if (!(airLoop && airLoop->supplyComponent(node.handle()))) {
        return false;
      }

      return StraightComponent_Impl::addToNode(node);
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

    unsigned CoilSystemCoolingWaterHeatExchangerAssisted_Impl::inletPort() const {
      // EnergyPlus CoilSystem:Cooling:Water:HeatExchangerAssisted has no direct inlet/outlet node fields.
      return 0;
    }

    unsigned CoilSystemCoolingWaterHeatExchangerAssisted_Impl::outletPort() const {
      // Node connectivity is delegated to the referenced heat exchanger/cooling coil.
      return 0;
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
      return setPointerRelationship(*this, kHeatExchangerObjectTypeField, kHeatExchangerField, heatExchanger);
    }

    WaterToAirComponent CoilSystemCoolingWaterHeatExchangerAssisted_Impl::coolingCoil() const {
      return requiredPointerTarget<WaterToAirComponent>(*this, kCoolingCoilField, "Cooling Coil");
    }

    bool CoilSystemCoolingWaterHeatExchangerAssisted_Impl::setCoolingCoil(const WaterToAirComponent& coolingCoil) {
      return setPointerRelationship(*this, kCoolingCoilObjectTypeField, kCoolingCoilField, coolingCoil);
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
