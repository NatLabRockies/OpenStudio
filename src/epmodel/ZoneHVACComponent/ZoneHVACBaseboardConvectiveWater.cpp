/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ZoneHVACComponent/ZoneHVACBaseboardConvectiveWater.hpp"
#include "ZoneHVACComponent/ZoneHVACBaseboardConvectiveWater_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/ZoneHVAC_Baseboard_Convective_Water_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  ZoneHVACBaseboardConvectiveWater::ZoneHVACBaseboardConvectiveWater(const Model& model)
    : ModelObject(ZoneHVACBaseboardConvectiveWater::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::ZoneHVACBaseboardConvectiveWater_Impl>());

    OS_ASSERT(setHeatingDesignCapacityMethod("HeatingDesignCapacity"));
    autosizeHeatingDesignCapacity();
    OS_ASSERT(setHeatingDesignCapacityPerFloorArea(0.0));
    OS_ASSERT(setFractionofAutosizedHeatingDesignCapacity(0.8));
    OS_ASSERT(setConvergenceTolerance(0.001));
  }

  ZoneHVACBaseboardConvectiveWater::ZoneHVACBaseboardConvectiveWater(std::shared_ptr<detail::ZoneHVACBaseboardConvectiveWater_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType ZoneHVACBaseboardConvectiveWater::iddObjectType() {
    return IddObjectType::ZoneHVAC_Baseboard_Convective_Water;
  }

  std::vector<std::string> ZoneHVACBaseboardConvectiveWater::heatingDesignCapacityMethodValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          ZoneHVAC_Baseboard_Convective_WaterFields::HeatingDesignCapacityMethod);
  }

  std::string ZoneHVACBaseboardConvectiveWater::heatingDesignCapacityMethod() const {
    return getImpl<detail::ZoneHVACBaseboardConvectiveWater_Impl>()->heatingDesignCapacityMethod();
  }

  bool ZoneHVACBaseboardConvectiveWater::setHeatingDesignCapacityMethod(const std::string& heatingDesignCapacityMethod) {
    return getImpl<detail::ZoneHVACBaseboardConvectiveWater_Impl>()->setHeatingDesignCapacityMethod(heatingDesignCapacityMethod);
  }

  boost::optional<double> ZoneHVACBaseboardConvectiveWater::heatingDesignCapacity() const {
    return getImpl<detail::ZoneHVACBaseboardConvectiveWater_Impl>()->heatingDesignCapacity();
  }

  bool ZoneHVACBaseboardConvectiveWater::isHeatingDesignCapacityAutosized() const {
    return getImpl<detail::ZoneHVACBaseboardConvectiveWater_Impl>()->isHeatingDesignCapacityAutosized();
  }

  bool ZoneHVACBaseboardConvectiveWater::setHeatingDesignCapacity(double heatingDesignCapacity) {
    return getImpl<detail::ZoneHVACBaseboardConvectiveWater_Impl>()->setHeatingDesignCapacity(heatingDesignCapacity);
  }

  void ZoneHVACBaseboardConvectiveWater::autosizeHeatingDesignCapacity() {
    getImpl<detail::ZoneHVACBaseboardConvectiveWater_Impl>()->autosizeHeatingDesignCapacity();
  }

  double ZoneHVACBaseboardConvectiveWater::heatingDesignCapacityPerFloorArea() const {
    return getImpl<detail::ZoneHVACBaseboardConvectiveWater_Impl>()->heatingDesignCapacityPerFloorArea();
  }

  bool ZoneHVACBaseboardConvectiveWater::setHeatingDesignCapacityPerFloorArea(double heatingDesignCapacityPerFloorArea) {
    return getImpl<detail::ZoneHVACBaseboardConvectiveWater_Impl>()->setHeatingDesignCapacityPerFloorArea(heatingDesignCapacityPerFloorArea);
  }

  double ZoneHVACBaseboardConvectiveWater::fractionofAutosizedHeatingDesignCapacity() const {
    return getImpl<detail::ZoneHVACBaseboardConvectiveWater_Impl>()->fractionofAutosizedHeatingDesignCapacity();
  }

  bool ZoneHVACBaseboardConvectiveWater::setFractionofAutosizedHeatingDesignCapacity(double fractionofAutosizedHeatingDesignCapacity) {
    return getImpl<detail::ZoneHVACBaseboardConvectiveWater_Impl>()->setFractionofAutosizedHeatingDesignCapacity(
      fractionofAutosizedHeatingDesignCapacity);
  }

  boost::optional<double> ZoneHVACBaseboardConvectiveWater::uFactorTimesAreaValue() const {
    return getImpl<detail::ZoneHVACBaseboardConvectiveWater_Impl>()->uFactorTimesAreaValue();
  }

  bool ZoneHVACBaseboardConvectiveWater::isUFactorTimesAreaValueDefaulted() const {
    return getImpl<detail::ZoneHVACBaseboardConvectiveWater_Impl>()->isUFactorTimesAreaValueDefaulted();
  }

  bool ZoneHVACBaseboardConvectiveWater::isUFactorTimesAreaValueAutosized() const {
    return getImpl<detail::ZoneHVACBaseboardConvectiveWater_Impl>()->isUFactorTimesAreaValueAutosized();
  }

  bool ZoneHVACBaseboardConvectiveWater::setUFactorTimesAreaValue(double uFactorTimesAreaValue) {
    return getImpl<detail::ZoneHVACBaseboardConvectiveWater_Impl>()->setUFactorTimesAreaValue(uFactorTimesAreaValue);
  }

  void ZoneHVACBaseboardConvectiveWater::resetUFactorTimesAreaValue() {
    getImpl<detail::ZoneHVACBaseboardConvectiveWater_Impl>()->resetUFactorTimesAreaValue();
  }

  void ZoneHVACBaseboardConvectiveWater::autosizeUFactorTimesAreaValue() {
    getImpl<detail::ZoneHVACBaseboardConvectiveWater_Impl>()->autosizeUFactorTimesAreaValue();
  }

  boost::optional<double> ZoneHVACBaseboardConvectiveWater::maximumWaterFlowRate() const {
    return getImpl<detail::ZoneHVACBaseboardConvectiveWater_Impl>()->maximumWaterFlowRate();
  }

  bool ZoneHVACBaseboardConvectiveWater::isMaximumWaterFlowRateDefaulted() const {
    return getImpl<detail::ZoneHVACBaseboardConvectiveWater_Impl>()->isMaximumWaterFlowRateDefaulted();
  }

  bool ZoneHVACBaseboardConvectiveWater::isMaximumWaterFlowRateAutosized() const {
    return getImpl<detail::ZoneHVACBaseboardConvectiveWater_Impl>()->isMaximumWaterFlowRateAutosized();
  }

  bool ZoneHVACBaseboardConvectiveWater::setMaximumWaterFlowRate(double maximumWaterFlowRate) {
    return getImpl<detail::ZoneHVACBaseboardConvectiveWater_Impl>()->setMaximumWaterFlowRate(maximumWaterFlowRate);
  }

  void ZoneHVACBaseboardConvectiveWater::resetMaximumWaterFlowRate() {
    getImpl<detail::ZoneHVACBaseboardConvectiveWater_Impl>()->resetMaximumWaterFlowRate();
  }

  void ZoneHVACBaseboardConvectiveWater::autosizeMaximumWaterFlowRate() {
    getImpl<detail::ZoneHVACBaseboardConvectiveWater_Impl>()->autosizeMaximumWaterFlowRate();
  }

  double ZoneHVACBaseboardConvectiveWater::convergenceTolerance() const {
    return getImpl<detail::ZoneHVACBaseboardConvectiveWater_Impl>()->convergenceTolerance();
  }

  bool ZoneHVACBaseboardConvectiveWater::isConvergenceToleranceDefaulted() const {
    return getImpl<detail::ZoneHVACBaseboardConvectiveWater_Impl>()->isConvergenceToleranceDefaulted();
  }

  bool ZoneHVACBaseboardConvectiveWater::setConvergenceTolerance(double convergenceTolerance) {
    return getImpl<detail::ZoneHVACBaseboardConvectiveWater_Impl>()->setConvergenceTolerance(convergenceTolerance);
  }

  void ZoneHVACBaseboardConvectiveWater::resetConvergenceTolerance() {
    getImpl<detail::ZoneHVACBaseboardConvectiveWater_Impl>()->resetConvergenceTolerance();
  }

  namespace detail {

    std::string ZoneHVACBaseboardConvectiveWater_Impl::heatingDesignCapacityMethod() const {
      auto value = getString(ZoneHVAC_Baseboard_Convective_WaterFields::HeatingDesignCapacityMethod, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACBaseboardConvectiveWater_Impl::setHeatingDesignCapacityMethod(const std::string& heatingDesignCapacityMethod) {
      const bool result = setString(ZoneHVAC_Baseboard_Convective_WaterFields::HeatingDesignCapacityMethod, heatingDesignCapacityMethod);
      return result;
    }

    boost::optional<double> ZoneHVACBaseboardConvectiveWater_Impl::heatingDesignCapacity() const {
      return getDouble(ZoneHVAC_Baseboard_Convective_WaterFields::HeatingDesignCapacity, true);
    }

    bool ZoneHVACBaseboardConvectiveWater_Impl::isHeatingDesignCapacityAutosized() const {
      bool result = false;
      if (auto value = getString(ZoneHVAC_Baseboard_Convective_WaterFields::HeatingDesignCapacity, true)) {
        result = openstudio::istringEqual(*value, "autosize");
      }
      return result;
    }

    bool ZoneHVACBaseboardConvectiveWater_Impl::setHeatingDesignCapacity(double heatingDesignCapacity) {
      const bool result = setDouble(ZoneHVAC_Baseboard_Convective_WaterFields::HeatingDesignCapacity, heatingDesignCapacity);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACBaseboardConvectiveWater_Impl::autosizeHeatingDesignCapacity() {
      OS_ASSERT(setString(ZoneHVAC_Baseboard_Convective_WaterFields::HeatingDesignCapacity, "autosize"));
    }

    double ZoneHVACBaseboardConvectiveWater_Impl::heatingDesignCapacityPerFloorArea() const {
      auto value = getDouble(ZoneHVAC_Baseboard_Convective_WaterFields::HeatingDesignCapacityPerFloorArea, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACBaseboardConvectiveWater_Impl::setHeatingDesignCapacityPerFloorArea(double heatingDesignCapacityPerFloorArea) {
      const bool result = setDouble(ZoneHVAC_Baseboard_Convective_WaterFields::HeatingDesignCapacityPerFloorArea, heatingDesignCapacityPerFloorArea);
      OS_ASSERT(result);
      return result;
    }

    double ZoneHVACBaseboardConvectiveWater_Impl::fractionofAutosizedHeatingDesignCapacity() const {
      auto value = getDouble(ZoneHVAC_Baseboard_Convective_WaterFields::FractionofAutosizedHeatingDesignCapacity, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACBaseboardConvectiveWater_Impl::setFractionofAutosizedHeatingDesignCapacity(double fractionofAutosizedHeatingDesignCapacity) {
      const bool result =
        setDouble(ZoneHVAC_Baseboard_Convective_WaterFields::FractionofAutosizedHeatingDesignCapacity, fractionofAutosizedHeatingDesignCapacity);
      OS_ASSERT(result);
      return result;
    }

    boost::optional<double> ZoneHVACBaseboardConvectiveWater_Impl::uFactorTimesAreaValue() const {
      return getDouble(ZoneHVAC_Baseboard_Convective_WaterFields::UFactorTimesAreaValue, true);
    }

    bool ZoneHVACBaseboardConvectiveWater_Impl::isUFactorTimesAreaValueDefaulted() const {
      return isEmpty(ZoneHVAC_Baseboard_Convective_WaterFields::UFactorTimesAreaValue);
    }

    bool ZoneHVACBaseboardConvectiveWater_Impl::isUFactorTimesAreaValueAutosized() const {
      bool result = false;
      if (auto value = getString(ZoneHVAC_Baseboard_Convective_WaterFields::UFactorTimesAreaValue, true)) {
        result = openstudio::istringEqual(*value, "autosize");
      }
      return result;
    }

    bool ZoneHVACBaseboardConvectiveWater_Impl::setUFactorTimesAreaValue(double uFactorTimesAreaValue) {
      const bool result = setDouble(ZoneHVAC_Baseboard_Convective_WaterFields::UFactorTimesAreaValue, uFactorTimesAreaValue);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACBaseboardConvectiveWater_Impl::resetUFactorTimesAreaValue() {
      OS_ASSERT(setString(ZoneHVAC_Baseboard_Convective_WaterFields::UFactorTimesAreaValue, ""));
    }

    void ZoneHVACBaseboardConvectiveWater_Impl::autosizeUFactorTimesAreaValue() {
      OS_ASSERT(setString(ZoneHVAC_Baseboard_Convective_WaterFields::UFactorTimesAreaValue, "autosize"));
    }

    boost::optional<double> ZoneHVACBaseboardConvectiveWater_Impl::maximumWaterFlowRate() const {
      return getDouble(ZoneHVAC_Baseboard_Convective_WaterFields::MaximumWaterFlowRate, true);
    }

    bool ZoneHVACBaseboardConvectiveWater_Impl::isMaximumWaterFlowRateDefaulted() const {
      return isEmpty(ZoneHVAC_Baseboard_Convective_WaterFields::MaximumWaterFlowRate);
    }

    bool ZoneHVACBaseboardConvectiveWater_Impl::isMaximumWaterFlowRateAutosized() const {
      bool result = false;
      if (auto value = getString(ZoneHVAC_Baseboard_Convective_WaterFields::MaximumWaterFlowRate, true)) {
        result = openstudio::istringEqual(*value, "autosize");
      }
      return result;
    }

    bool ZoneHVACBaseboardConvectiveWater_Impl::setMaximumWaterFlowRate(double maximumWaterFlowRate) {
      const bool result = setDouble(ZoneHVAC_Baseboard_Convective_WaterFields::MaximumWaterFlowRate, maximumWaterFlowRate);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACBaseboardConvectiveWater_Impl::resetMaximumWaterFlowRate() {
      OS_ASSERT(setString(ZoneHVAC_Baseboard_Convective_WaterFields::MaximumWaterFlowRate, ""));
    }

    void ZoneHVACBaseboardConvectiveWater_Impl::autosizeMaximumWaterFlowRate() {
      OS_ASSERT(setString(ZoneHVAC_Baseboard_Convective_WaterFields::MaximumWaterFlowRate, "autosize"));
    }

    double ZoneHVACBaseboardConvectiveWater_Impl::convergenceTolerance() const {
      auto value = getDouble(ZoneHVAC_Baseboard_Convective_WaterFields::ConvergenceTolerance, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACBaseboardConvectiveWater_Impl::isConvergenceToleranceDefaulted() const {
      return isEmpty(ZoneHVAC_Baseboard_Convective_WaterFields::ConvergenceTolerance);
    }

    bool ZoneHVACBaseboardConvectiveWater_Impl::setConvergenceTolerance(double convergenceTolerance) {
      const bool result = setDouble(ZoneHVAC_Baseboard_Convective_WaterFields::ConvergenceTolerance, convergenceTolerance);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACBaseboardConvectiveWater_Impl::resetConvergenceTolerance() {
      OS_ASSERT(setString(ZoneHVAC_Baseboard_Convective_WaterFields::ConvergenceTolerance, ""));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
