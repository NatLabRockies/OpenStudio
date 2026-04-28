/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/CoilSystemCoolingDXHeatExchangerAssisted.hpp"
#include "StraightComponent/CoilSystemCoolingDXHeatExchangerAssisted_Impl.hpp"

#include "AirToAirComponent/AirToAirComponent.hpp"
#include "AirToAirComponent/HeatExchangerAirToAirSensibleAndLatent.hpp"
#include "AirToAirComponent/HeatExchangerAirToAirSensibleAndLatent_Impl.hpp"
#include "Model.hpp"
#include "ModelObject.hpp"
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
    CoilCoolingDXSingleSpeed coolingCoil(model);
    OS_ASSERT(setCoolingCoil(coolingCoil));
    if (!setHeatExchanger(heatExchanger)) {
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
      T requiredTarget(const ModelObject_Impl& impl, unsigned fieldIndex, const char* label) {
        auto value = impl.getObject<ModelObject>().getModelObjectTarget<T>(fieldIndex);
        if (!value) {
          std::ostringstream message;
          message << impl.briefDescription() << " does not have a " << label << " attached.";
          throw std::runtime_error(message.str());
        }
        return *value;
      }

      template <typename T>
      bool setTypedRelationship(ModelObject_Impl& impl, unsigned objectTypeField, unsigned objectField, const T& target) {
        if (!impl.setString(objectTypeField, target.iddObject().name())) {
          return false;
        }
        return impl.setPointer(objectField, target.handle());
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

    bool CoilSystemCoolingDXHeatExchangerAssisted_Impl::addToNode(Node& /*node*/) {
      return false;
    }

    std::vector<ModelObject> CoilSystemCoolingDXHeatExchangerAssisted_Impl::children() const {
      return {coolingCoil().cast<ModelObject>(), heatExchanger().cast<ModelObject>()};
    }

    AirToAirComponent CoilSystemCoolingDXHeatExchangerAssisted_Impl::heatExchanger() const {
      return requiredTarget<AirToAirComponent>(*this, kHeatExchangerField, "Heat Exchanger");
    }

    bool CoilSystemCoolingDXHeatExchangerAssisted_Impl::setHeatExchanger(const AirToAirComponent& heatExchanger) {
      return setTypedRelationship(*this, kHeatExchangerObjectTypeField, kHeatExchangerField, heatExchanger);
    }

    StraightComponent CoilSystemCoolingDXHeatExchangerAssisted_Impl::coolingCoil() const {
      return requiredTarget<StraightComponent>(*this, kCoolingCoilField, "Cooling Coil");
    }

    bool CoilSystemCoolingDXHeatExchangerAssisted_Impl::setCoolingCoil(const StraightComponent& coolingCoil) {
      return setTypedRelationship(*this, kCoolingCoilObjectTypeField, kCoolingCoilField, coolingCoil);
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
