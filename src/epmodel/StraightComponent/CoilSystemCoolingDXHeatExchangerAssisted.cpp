/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/CoilSystemCoolingDXHeatExchangerAssisted.hpp"
#include "StraightComponent/CoilSystemCoolingDXHeatExchangerAssisted_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/CoilSystem_Cooling_DX_HeatExchangerAssisted_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

  CoilSystemCoolingDXHeatExchangerAssisted::CoilSystemCoolingDXHeatExchangerAssisted(const Model& model)
    : StraightComponent(CoilSystemCoolingDXHeatExchangerAssisted::iddObjectType(), model) {}

  CoilSystemCoolingDXHeatExchangerAssisted::CoilSystemCoolingDXHeatExchangerAssisted(
    std::shared_ptr<detail::CoilSystemCoolingDXHeatExchangerAssisted_Impl> impl)
    : StraightComponent(std::move(impl)) {}

  IddObjectType CoilSystemCoolingDXHeatExchangerAssisted::iddObjectType() {
    return IddObjectType::CoilSystem_Cooling_DX_HeatExchangerAssisted;
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

    unsigned CoilSystemCoolingDXHeatExchangerAssisted_Impl::inletPort() const {
      // EnergyPlus CoilSystem:Cooling:DX:HeatExchangerAssisted has no direct inlet/outlet node fields.
      return 0;
    }

    unsigned CoilSystemCoolingDXHeatExchangerAssisted_Impl::outletPort() const {
      // Node connectivity is delegated to the referenced heat exchanger/cooling coil.
      return 0;
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
