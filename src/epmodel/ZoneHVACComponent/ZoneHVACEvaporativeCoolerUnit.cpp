/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ZoneHVACComponent/ZoneHVACEvaporativeCoolerUnit.hpp"
#include "ZoneHVACComponent/ZoneHVACEvaporativeCoolerUnit_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/String.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/ZoneHVAC_EvaporativeCoolerUnit_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  ZoneHVACEvaporativeCoolerUnit::ZoneHVACEvaporativeCoolerUnit(const Model& model)
    : ModelObject(ZoneHVACEvaporativeCoolerUnit::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::ZoneHVACEvaporativeCoolerUnit_Impl>());

    autosizeDesignSupplyAirFlowRate();
    OS_ASSERT(setFanPlacement("BlowThrough"));
    OS_ASSERT(setCoolerUnitControlMethod("ZoneTemperatureDeadbandOnOffCycling"));
    OS_ASSERT(setThrottlingRangeTemperatureDifference(1.0));
    OS_ASSERT(setCoolingLoadControlThresholdHeatTransferRate(100.0));
    OS_ASSERT(setShutOffRelativeHumidity(100.0));
  }

  ZoneHVACEvaporativeCoolerUnit::ZoneHVACEvaporativeCoolerUnit(std::shared_ptr<detail::ZoneHVACEvaporativeCoolerUnit_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType ZoneHVACEvaporativeCoolerUnit::iddObjectType() {
    return IddObjectType::ZoneHVAC_EvaporativeCoolerUnit;
  }

  std::vector<std::string> ZoneHVACEvaporativeCoolerUnit::fanPlacementValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::ZoneHVAC_EvaporativeCoolerUnitFields::FanPlacement);
  }

  std::vector<std::string> ZoneHVACEvaporativeCoolerUnit::coolerUnitControlMethodValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::ZoneHVAC_EvaporativeCoolerUnitFields::CoolerUnitControlMethod);
  }

  boost::optional<double> ZoneHVACEvaporativeCoolerUnit::designSupplyAirFlowRate() const {
    return getImpl<detail::ZoneHVACEvaporativeCoolerUnit_Impl>()->designSupplyAirFlowRate();
  }

  bool ZoneHVACEvaporativeCoolerUnit::setDesignSupplyAirFlowRate(double designSupplyAirFlowRate) {
    return getImpl<detail::ZoneHVACEvaporativeCoolerUnit_Impl>()->setDesignSupplyAirFlowRate(designSupplyAirFlowRate);
  }

  bool ZoneHVACEvaporativeCoolerUnit::isDesignSupplyAirFlowRateAutosized() const {
    return getImpl<detail::ZoneHVACEvaporativeCoolerUnit_Impl>()->isDesignSupplyAirFlowRateAutosized();
  }

  void ZoneHVACEvaporativeCoolerUnit::autosizeDesignSupplyAirFlowRate() {
    getImpl<detail::ZoneHVACEvaporativeCoolerUnit_Impl>()->autosizeDesignSupplyAirFlowRate();
  }

  std::string ZoneHVACEvaporativeCoolerUnit::fanPlacement() const {
    return getImpl<detail::ZoneHVACEvaporativeCoolerUnit_Impl>()->fanPlacement();
  }

  bool ZoneHVACEvaporativeCoolerUnit::setFanPlacement(const std::string& fanPlacement) {
    return getImpl<detail::ZoneHVACEvaporativeCoolerUnit_Impl>()->setFanPlacement(fanPlacement);
  }

  std::string ZoneHVACEvaporativeCoolerUnit::coolerUnitControlMethod() const {
    return getImpl<detail::ZoneHVACEvaporativeCoolerUnit_Impl>()->coolerUnitControlMethod();
  }

  bool ZoneHVACEvaporativeCoolerUnit::setCoolerUnitControlMethod(const std::string& coolerUnitControlMethod) {
    return getImpl<detail::ZoneHVACEvaporativeCoolerUnit_Impl>()->setCoolerUnitControlMethod(coolerUnitControlMethod);
  }

  double ZoneHVACEvaporativeCoolerUnit::throttlingRangeTemperatureDifference() const {
    return getImpl<detail::ZoneHVACEvaporativeCoolerUnit_Impl>()->throttlingRangeTemperatureDifference();
  }

  bool ZoneHVACEvaporativeCoolerUnit::setThrottlingRangeTemperatureDifference(double throttlingRangeTemperatureDifference) {
    return getImpl<detail::ZoneHVACEvaporativeCoolerUnit_Impl>()->setThrottlingRangeTemperatureDifference(throttlingRangeTemperatureDifference);
  }

  double ZoneHVACEvaporativeCoolerUnit::coolingLoadControlThresholdHeatTransferRate() const {
    return getImpl<detail::ZoneHVACEvaporativeCoolerUnit_Impl>()->coolingLoadControlThresholdHeatTransferRate();
  }

  bool ZoneHVACEvaporativeCoolerUnit::setCoolingLoadControlThresholdHeatTransferRate(double coolingLoadControlThresholdHeatTransferRate) {
    return getImpl<detail::ZoneHVACEvaporativeCoolerUnit_Impl>()->setCoolingLoadControlThresholdHeatTransferRate(
      coolingLoadControlThresholdHeatTransferRate);
  }

  double ZoneHVACEvaporativeCoolerUnit::shutOffRelativeHumidity() const {
    return getImpl<detail::ZoneHVACEvaporativeCoolerUnit_Impl>()->shutOffRelativeHumidity();
  }

  bool ZoneHVACEvaporativeCoolerUnit::setShutOffRelativeHumidity(double shutOffRelativeHumidity) {
    return getImpl<detail::ZoneHVACEvaporativeCoolerUnit_Impl>()->setShutOffRelativeHumidity(shutOffRelativeHumidity);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    boost::optional<double> ZoneHVACEvaporativeCoolerUnit_Impl::designSupplyAirFlowRate() const {
      return getDouble(openstudio::ZoneHVAC_EvaporativeCoolerUnitFields::DesignSupplyAirFlowRate, true);
    }

    bool ZoneHVACEvaporativeCoolerUnit_Impl::setDesignSupplyAirFlowRate(double designSupplyAirFlowRate) {
      const bool result = setDouble(openstudio::ZoneHVAC_EvaporativeCoolerUnitFields::DesignSupplyAirFlowRate, designSupplyAirFlowRate);
      OS_ASSERT(result);
      return result;
    }

    bool ZoneHVACEvaporativeCoolerUnit_Impl::isDesignSupplyAirFlowRateAutosized() const {
      if (auto value = getString(openstudio::ZoneHVAC_EvaporativeCoolerUnitFields::DesignSupplyAirFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    void ZoneHVACEvaporativeCoolerUnit_Impl::autosizeDesignSupplyAirFlowRate() {
      OS_ASSERT(setString(openstudio::ZoneHVAC_EvaporativeCoolerUnitFields::DesignSupplyAirFlowRate, "autosize"));
    }

    std::string ZoneHVACEvaporativeCoolerUnit_Impl::fanPlacement() const {
      const auto value = getString(openstudio::ZoneHVAC_EvaporativeCoolerUnitFields::FanPlacement, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneHVACEvaporativeCoolerUnit_Impl::setFanPlacement(const std::string& fanPlacement) {
      const bool result = setString(openstudio::ZoneHVAC_EvaporativeCoolerUnitFields::FanPlacement, fanPlacement);
      OS_ASSERT(result);
      return result;
    }

    std::string ZoneHVACEvaporativeCoolerUnit_Impl::coolerUnitControlMethod() const {
      const auto value = getString(openstudio::ZoneHVAC_EvaporativeCoolerUnitFields::CoolerUnitControlMethod, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneHVACEvaporativeCoolerUnit_Impl::setCoolerUnitControlMethod(const std::string& coolerUnitControlMethod) {
      const bool result = setString(openstudio::ZoneHVAC_EvaporativeCoolerUnitFields::CoolerUnitControlMethod, coolerUnitControlMethod);
      OS_ASSERT(result);
      return result;
    }

    double ZoneHVACEvaporativeCoolerUnit_Impl::throttlingRangeTemperatureDifference() const {
      const auto value = getDouble(openstudio::ZoneHVAC_EvaporativeCoolerUnitFields::ThrottlingRangeTemperatureDifference, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneHVACEvaporativeCoolerUnit_Impl::setThrottlingRangeTemperatureDifference(double throttlingRangeTemperatureDifference) {
      const bool result =
        setDouble(openstudio::ZoneHVAC_EvaporativeCoolerUnitFields::ThrottlingRangeTemperatureDifference, throttlingRangeTemperatureDifference);
      OS_ASSERT(result);
      return result;
    }

    double ZoneHVACEvaporativeCoolerUnit_Impl::coolingLoadControlThresholdHeatTransferRate() const {
      const auto value = getDouble(openstudio::ZoneHVAC_EvaporativeCoolerUnitFields::CoolingLoadControlThresholdHeatTransferRate, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneHVACEvaporativeCoolerUnit_Impl::setCoolingLoadControlThresholdHeatTransferRate(double coolingLoadControlThresholdHeatTransferRate) {
      const bool result = setDouble(openstudio::ZoneHVAC_EvaporativeCoolerUnitFields::CoolingLoadControlThresholdHeatTransferRate,
                                    coolingLoadControlThresholdHeatTransferRate);
      OS_ASSERT(result);
      return result;
    }

    double ZoneHVACEvaporativeCoolerUnit_Impl::shutOffRelativeHumidity() const {
      const auto value = getDouble(openstudio::ZoneHVAC_EvaporativeCoolerUnitFields::ShutOffRelativeHumidity, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneHVACEvaporativeCoolerUnit_Impl::setShutOffRelativeHumidity(double shutOffRelativeHumidity) {
      const auto shutOffIndex = static_cast<unsigned>(openstudio::ZoneHVAC_EvaporativeCoolerUnitFields::ShutOffRelativeHumidity);
      while (numFields() <= shutOffIndex) {
        OS_ASSERT(pushString("", false));
      }
      const bool result = setDouble(openstudio::ZoneHVAC_EvaporativeCoolerUnitFields::ShutOffRelativeHumidity, shutOffRelativeHumidity, false);
      OS_ASSERT(result);
      return result;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
