/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/CoilSystemCoolingWaterHeatExchangerAssisted.hpp"
#include "StraightComponent/CoilSystemCoolingWaterHeatExchangerAssisted_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/CoilSystem_Cooling_Water_HeatExchangerAssisted_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

  CoilSystemCoolingWaterHeatExchangerAssisted::CoilSystemCoolingWaterHeatExchangerAssisted(const Model& model)
    : StraightComponent(CoilSystemCoolingWaterHeatExchangerAssisted::iddObjectType(), model) {}

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

    unsigned CoilSystemCoolingWaterHeatExchangerAssisted_Impl::inletPort() const {
      // EnergyPlus CoilSystem:Cooling:Water:HeatExchangerAssisted has no direct inlet/outlet node fields.
      return 0;
    }

    unsigned CoilSystemCoolingWaterHeatExchangerAssisted_Impl::outletPort() const {
      // Node connectivity is delegated to the referenced heat exchanger/cooling coil.
      return 0;
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
