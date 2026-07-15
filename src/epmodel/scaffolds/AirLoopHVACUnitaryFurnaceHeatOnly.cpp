/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "AirLoopHVACUnitaryFurnaceHeatOnly.hpp"
#include "AirLoopHVACUnitaryFurnaceHeatOnly_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/AirLoopHVAC_Unitary_Furnace_HeatOnly_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

  AirLoopHVACUnitaryFurnaceHeatOnly::AirLoopHVACUnitaryFurnaceHeatOnly(const Model& model)
    : ModelObject(AirLoopHVACUnitaryFurnaceHeatOnly::iddObjectType(), model) {}

  AirLoopHVACUnitaryFurnaceHeatOnly::AirLoopHVACUnitaryFurnaceHeatOnly(std::shared_ptr<detail::AirLoopHVACUnitaryFurnaceHeatOnly_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType AirLoopHVACUnitaryFurnaceHeatOnly::iddObjectType() {
    return IddObjectType::AirLoopHVAC_Unitary_Furnace_HeatOnly;
  }

  std::vector<std::string> AirLoopHVACUnitaryFurnaceHeatOnly::supplyFanObjectTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::AirLoopHVAC_Unitary_Furnace_HeatOnlyFields::SupplyFanObjectType);
  }

  std::vector<std::string> AirLoopHVACUnitaryFurnaceHeatOnly::fanPlacementValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::AirLoopHVAC_Unitary_Furnace_HeatOnlyFields::FanPlacement);
  }

  std::vector<std::string> AirLoopHVACUnitaryFurnaceHeatOnly::heatingCoilObjectTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::AirLoopHVAC_Unitary_Furnace_HeatOnlyFields::HeatingCoilObjectType);
  }

  boost::optional<double> AirLoopHVACUnitaryFurnaceHeatOnly::maximumSupplyAirTemperature() const {
    return getImpl<detail::AirLoopHVACUnitaryFurnaceHeatOnly_Impl>()->maximumSupplyAirTemperature();
  }

  bool AirLoopHVACUnitaryFurnaceHeatOnly::isMaximumSupplyAirTemperatureDefaulted() const {
    return getImpl<detail::AirLoopHVACUnitaryFurnaceHeatOnly_Impl>()->isMaximumSupplyAirTemperatureDefaulted();
  }

  bool AirLoopHVACUnitaryFurnaceHeatOnly::isMaximumSupplyAirTemperatureAutosized() const {
    return getImpl<detail::AirLoopHVACUnitaryFurnaceHeatOnly_Impl>()->isMaximumSupplyAirTemperatureAutosized();
  }

  bool AirLoopHVACUnitaryFurnaceHeatOnly::setMaximumSupplyAirTemperature(double maximumSupplyAirTemperature) {
    return getImpl<detail::AirLoopHVACUnitaryFurnaceHeatOnly_Impl>()->setMaximumSupplyAirTemperature(maximumSupplyAirTemperature);
  }

  void AirLoopHVACUnitaryFurnaceHeatOnly::resetMaximumSupplyAirTemperature() {
    getImpl<detail::AirLoopHVACUnitaryFurnaceHeatOnly_Impl>()->resetMaximumSupplyAirTemperature();
  }

  void AirLoopHVACUnitaryFurnaceHeatOnly::autosizeMaximumSupplyAirTemperature() {
    getImpl<detail::AirLoopHVACUnitaryFurnaceHeatOnly_Impl>()->autosizeMaximumSupplyAirTemperature();
  }

  boost::optional<double> AirLoopHVACUnitaryFurnaceHeatOnly::heatingSupplyAirFlowRate() const {
    return getImpl<detail::AirLoopHVACUnitaryFurnaceHeatOnly_Impl>()->heatingSupplyAirFlowRate();
  }

  bool AirLoopHVACUnitaryFurnaceHeatOnly::isHeatingSupplyAirFlowRateAutosized() const {
    return getImpl<detail::AirLoopHVACUnitaryFurnaceHeatOnly_Impl>()->isHeatingSupplyAirFlowRateAutosized();
  }

  bool AirLoopHVACUnitaryFurnaceHeatOnly::setHeatingSupplyAirFlowRate(double heatingSupplyAirFlowRate) {
    return getImpl<detail::AirLoopHVACUnitaryFurnaceHeatOnly_Impl>()->setHeatingSupplyAirFlowRate(heatingSupplyAirFlowRate);
  }

  void AirLoopHVACUnitaryFurnaceHeatOnly::autosizeHeatingSupplyAirFlowRate() {
    getImpl<detail::AirLoopHVACUnitaryFurnaceHeatOnly_Impl>()->autosizeHeatingSupplyAirFlowRate();
  }

  std::string AirLoopHVACUnitaryFurnaceHeatOnly::supplyFanObjectType() const {
    return getImpl<detail::AirLoopHVACUnitaryFurnaceHeatOnly_Impl>()->supplyFanObjectType();
  }

  bool AirLoopHVACUnitaryFurnaceHeatOnly::setSupplyFanObjectType(const std::string& supplyFanObjectType) {
    return getImpl<detail::AirLoopHVACUnitaryFurnaceHeatOnly_Impl>()->setSupplyFanObjectType(supplyFanObjectType);
  }

  std::string AirLoopHVACUnitaryFurnaceHeatOnly::fanPlacement() const {
    return getImpl<detail::AirLoopHVACUnitaryFurnaceHeatOnly_Impl>()->fanPlacement();
  }

  bool AirLoopHVACUnitaryFurnaceHeatOnly::setFanPlacement(const std::string& fanPlacement) {
    return getImpl<detail::AirLoopHVACUnitaryFurnaceHeatOnly_Impl>()->setFanPlacement(fanPlacement);
  }

  bool AirLoopHVACUnitaryFurnaceHeatOnly::isFanPlacementDefaulted() const {
    return getImpl<detail::AirLoopHVACUnitaryFurnaceHeatOnly_Impl>()->isFanPlacementDefaulted();
  }

  void AirLoopHVACUnitaryFurnaceHeatOnly::resetFanPlacement() {
    getImpl<detail::AirLoopHVACUnitaryFurnaceHeatOnly_Impl>()->resetFanPlacement();
  }

  std::string AirLoopHVACUnitaryFurnaceHeatOnly::heatingCoilObjectType() const {
    return getImpl<detail::AirLoopHVACUnitaryFurnaceHeatOnly_Impl>()->heatingCoilObjectType();
  }

  bool AirLoopHVACUnitaryFurnaceHeatOnly::setHeatingCoilObjectType(const std::string& heatingCoilObjectType) {
    return getImpl<detail::AirLoopHVACUnitaryFurnaceHeatOnly_Impl>()->setHeatingCoilObjectType(heatingCoilObjectType);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    boost::optional<double> AirLoopHVACUnitaryFurnaceHeatOnly_Impl::maximumSupplyAirTemperature() const {
      return getDouble(openstudio::AirLoopHVAC_Unitary_Furnace_HeatOnlyFields::MaximumSupplyAirTemperature, true);
    }

    bool AirLoopHVACUnitaryFurnaceHeatOnly_Impl::isMaximumSupplyAirTemperatureDefaulted() const {
      return isEmpty(openstudio::AirLoopHVAC_Unitary_Furnace_HeatOnlyFields::MaximumSupplyAirTemperature);
    }

    bool AirLoopHVACUnitaryFurnaceHeatOnly_Impl::isMaximumSupplyAirTemperatureAutosized() const {
      if (auto value = getString(openstudio::AirLoopHVAC_Unitary_Furnace_HeatOnlyFields::MaximumSupplyAirTemperature, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool AirLoopHVACUnitaryFurnaceHeatOnly_Impl::setMaximumSupplyAirTemperature(double maximumSupplyAirTemperature) {
      const bool result = setDouble(openstudio::AirLoopHVAC_Unitary_Furnace_HeatOnlyFields::MaximumSupplyAirTemperature, maximumSupplyAirTemperature);
      OS_ASSERT(result);
      return result;
    }

    void AirLoopHVACUnitaryFurnaceHeatOnly_Impl::resetMaximumSupplyAirTemperature() {
      OS_ASSERT(setString(openstudio::AirLoopHVAC_Unitary_Furnace_HeatOnlyFields::MaximumSupplyAirTemperature, ""));
    }

    void AirLoopHVACUnitaryFurnaceHeatOnly_Impl::autosizeMaximumSupplyAirTemperature() {
      OS_ASSERT(setString(openstudio::AirLoopHVAC_Unitary_Furnace_HeatOnlyFields::MaximumSupplyAirTemperature, "autosize"));
    }

    boost::optional<double> AirLoopHVACUnitaryFurnaceHeatOnly_Impl::heatingSupplyAirFlowRate() const {
      return getDouble(openstudio::AirLoopHVAC_Unitary_Furnace_HeatOnlyFields::HeatingSupplyAirFlowRate, true);
    }

    bool AirLoopHVACUnitaryFurnaceHeatOnly_Impl::isHeatingSupplyAirFlowRateAutosized() const {
      if (auto value = getString(openstudio::AirLoopHVAC_Unitary_Furnace_HeatOnlyFields::HeatingSupplyAirFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool AirLoopHVACUnitaryFurnaceHeatOnly_Impl::setHeatingSupplyAirFlowRate(double heatingSupplyAirFlowRate) {
      return setDouble(openstudio::AirLoopHVAC_Unitary_Furnace_HeatOnlyFields::HeatingSupplyAirFlowRate, heatingSupplyAirFlowRate);
    }

    void AirLoopHVACUnitaryFurnaceHeatOnly_Impl::autosizeHeatingSupplyAirFlowRate() {
      OS_ASSERT(setString(openstudio::AirLoopHVAC_Unitary_Furnace_HeatOnlyFields::HeatingSupplyAirFlowRate, "autosize"));
    }

    std::string AirLoopHVACUnitaryFurnaceHeatOnly_Impl::supplyFanObjectType() const {
      const auto value = getString(openstudio::AirLoopHVAC_Unitary_Furnace_HeatOnlyFields::SupplyFanObjectType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirLoopHVACUnitaryFurnaceHeatOnly_Impl::setSupplyFanObjectType(const std::string& supplyFanObjectType) {
      return setString(openstudio::AirLoopHVAC_Unitary_Furnace_HeatOnlyFields::SupplyFanObjectType, supplyFanObjectType);
    }

    std::string AirLoopHVACUnitaryFurnaceHeatOnly_Impl::fanPlacement() const {
      const auto value = getString(openstudio::AirLoopHVAC_Unitary_Furnace_HeatOnlyFields::FanPlacement, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirLoopHVACUnitaryFurnaceHeatOnly_Impl::setFanPlacement(const std::string& fanPlacement) {
      return setString(openstudio::AirLoopHVAC_Unitary_Furnace_HeatOnlyFields::FanPlacement, fanPlacement);
    }

    bool AirLoopHVACUnitaryFurnaceHeatOnly_Impl::isFanPlacementDefaulted() const {
      return isEmpty(openstudio::AirLoopHVAC_Unitary_Furnace_HeatOnlyFields::FanPlacement);
    }

    void AirLoopHVACUnitaryFurnaceHeatOnly_Impl::resetFanPlacement() {
      OS_ASSERT(setString(openstudio::AirLoopHVAC_Unitary_Furnace_HeatOnlyFields::FanPlacement, ""));
    }

    std::string AirLoopHVACUnitaryFurnaceHeatOnly_Impl::heatingCoilObjectType() const {
      const auto value = getString(openstudio::AirLoopHVAC_Unitary_Furnace_HeatOnlyFields::HeatingCoilObjectType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirLoopHVACUnitaryFurnaceHeatOnly_Impl::setHeatingCoilObjectType(const std::string& heatingCoilObjectType) {
      return setString(openstudio::AirLoopHVAC_Unitary_Furnace_HeatOnlyFields::HeatingCoilObjectType, heatingCoilObjectType);
    }

    std::vector<std::string> AirLoopHVACUnitaryFurnaceHeatOnly_Impl::supplyFanObjectTypeValues() const {
      return openstudio::epmodel::AirLoopHVACUnitaryFurnaceHeatOnly::supplyFanObjectTypeValues();
    }

    std::vector<std::string> AirLoopHVACUnitaryFurnaceHeatOnly_Impl::fanPlacementValues() const {
      return openstudio::epmodel::AirLoopHVACUnitaryFurnaceHeatOnly::fanPlacementValues();
    }

    std::vector<std::string> AirLoopHVACUnitaryFurnaceHeatOnly_Impl::heatingCoilObjectTypeValues() const {
      return openstudio::epmodel::AirLoopHVACUnitaryFurnaceHeatOnly::heatingCoilObjectTypeValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
