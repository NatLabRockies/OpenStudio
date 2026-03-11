/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ParentObject/RefrigerationCondenserEvaporativeCooled.hpp"
#include "ParentObject/RefrigerationCondenserEvaporativeCooled_Impl.hpp"

#include "Model.hpp"

#include <boost/optional.hpp>
#include <utilities/core/Assert.hpp>
#include <utilities/core/String.hpp>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/Refrigeration_Condenser_EvaporativeCooled_FieldEnums.hxx>

#include <utility>

namespace openstudio {
namespace epmodel {

  namespace detail {

    double RefrigerationCondenserEvaporativeCooled_Impl::ratedEffectiveTotalHeatRejectionRate() const {
      boost::optional<double> value = getDouble(Refrigeration_Condenser_EvaporativeCooledFields::RatedEffectiveTotalHeatRejectionRate, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool RefrigerationCondenserEvaporativeCooled_Impl::setRatedEffectiveTotalHeatRejectionRate(double ratedEffectiveTotalHeatRejectionRate) {
      return setDouble(Refrigeration_Condenser_EvaporativeCooledFields::RatedEffectiveTotalHeatRejectionRate, ratedEffectiveTotalHeatRejectionRate);
    }

    double RefrigerationCondenserEvaporativeCooled_Impl::ratedSubcoolingTemperatureDifference() const {
      boost::optional<double> value = getDouble(Refrigeration_Condenser_EvaporativeCooledFields::RatedSubcoolingTemperatureDifference, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool RefrigerationCondenserEvaporativeCooled_Impl::isRatedSubcoolingTemperatureDifferenceDefaulted() const {
      return isEmpty(Refrigeration_Condenser_EvaporativeCooledFields::RatedSubcoolingTemperatureDifference);
    }

    bool RefrigerationCondenserEvaporativeCooled_Impl::setRatedSubcoolingTemperatureDifference(double ratedSubcoolingTemperatureDifference) {
      return setDouble(Refrigeration_Condenser_EvaporativeCooledFields::RatedSubcoolingTemperatureDifference, ratedSubcoolingTemperatureDifference);
    }

    void RefrigerationCondenserEvaporativeCooled_Impl::resetRatedSubcoolingTemperatureDifference() {
      const bool result = setString(Refrigeration_Condenser_EvaporativeCooledFields::RatedSubcoolingTemperatureDifference, "");
      OS_ASSERT(result);
    }

    std::string RefrigerationCondenserEvaporativeCooled_Impl::fanSpeedControlType() const {
      boost::optional<std::string> value = getString(Refrigeration_Condenser_EvaporativeCooledFields::FanSpeedControlType, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool RefrigerationCondenserEvaporativeCooled_Impl::isFanSpeedControlTypeDefaulted() const {
      return isEmpty(Refrigeration_Condenser_EvaporativeCooledFields::FanSpeedControlType);
    }

    bool RefrigerationCondenserEvaporativeCooled_Impl::setFanSpeedControlType(const std::string& fanSpeedControlType) {
      return setString(Refrigeration_Condenser_EvaporativeCooledFields::FanSpeedControlType, fanSpeedControlType);
    }

    void RefrigerationCondenserEvaporativeCooled_Impl::resetFanSpeedControlType() {
      const bool result = setString(Refrigeration_Condenser_EvaporativeCooledFields::FanSpeedControlType, "");
      OS_ASSERT(result);
    }

    double RefrigerationCondenserEvaporativeCooled_Impl::ratedFanPower() const {
      boost::optional<double> value = getDouble(Refrigeration_Condenser_EvaporativeCooledFields::RatedFanPower, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool RefrigerationCondenserEvaporativeCooled_Impl::setRatedFanPower(double ratedFanPower) {
      return setDouble(Refrigeration_Condenser_EvaporativeCooledFields::RatedFanPower, ratedFanPower);
    }

    double RefrigerationCondenserEvaporativeCooled_Impl::minimumFanAirFlowRatio() const {
      boost::optional<double> value = getDouble(Refrigeration_Condenser_EvaporativeCooledFields::MinimumFanAirFlowRatio, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool RefrigerationCondenserEvaporativeCooled_Impl::isMinimumFanAirFlowRatioDefaulted() const {
      return isEmpty(Refrigeration_Condenser_EvaporativeCooledFields::MinimumFanAirFlowRatio);
    }

    bool RefrigerationCondenserEvaporativeCooled_Impl::setMinimumFanAirFlowRatio(double minimumFanAirFlowRatio) {
      return setDouble(Refrigeration_Condenser_EvaporativeCooledFields::MinimumFanAirFlowRatio, minimumFanAirFlowRatio);
    }

    void RefrigerationCondenserEvaporativeCooled_Impl::resetMinimumFanAirFlowRatio() {
      const bool result = setString(Refrigeration_Condenser_EvaporativeCooledFields::MinimumFanAirFlowRatio, "");
      OS_ASSERT(result);
    }

    double RefrigerationCondenserEvaporativeCooled_Impl::approachTemperatureConstantTerm() const {
      boost::optional<double> value = getDouble(Refrigeration_Condenser_EvaporativeCooledFields::ApproachTemperatureConstantTerm, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool RefrigerationCondenserEvaporativeCooled_Impl::isApproachTemperatureConstantTermDefaulted() const {
      return isEmpty(Refrigeration_Condenser_EvaporativeCooledFields::ApproachTemperatureConstantTerm);
    }

    bool RefrigerationCondenserEvaporativeCooled_Impl::setApproachTemperatureConstantTerm(double approachTemperatureConstantTerm) {
      return setDouble(Refrigeration_Condenser_EvaporativeCooledFields::ApproachTemperatureConstantTerm, approachTemperatureConstantTerm);
    }

    void RefrigerationCondenserEvaporativeCooled_Impl::resetApproachTemperatureConstantTerm() {
      const bool result = setString(Refrigeration_Condenser_EvaporativeCooledFields::ApproachTemperatureConstantTerm, "");
      OS_ASSERT(result);
    }

    double RefrigerationCondenserEvaporativeCooled_Impl::approachTemperatureCoefficient2() const {
      boost::optional<double> value = getDouble(Refrigeration_Condenser_EvaporativeCooledFields::ApproachTemperatureCoefficient2, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool RefrigerationCondenserEvaporativeCooled_Impl::isApproachTemperatureCoefficient2Defaulted() const {
      return isEmpty(Refrigeration_Condenser_EvaporativeCooledFields::ApproachTemperatureCoefficient2);
    }

    bool RefrigerationCondenserEvaporativeCooled_Impl::setApproachTemperatureCoefficient2(double approachTemperatureCoefficient2) {
      return setDouble(Refrigeration_Condenser_EvaporativeCooledFields::ApproachTemperatureCoefficient2, approachTemperatureCoefficient2);
    }

    void RefrigerationCondenserEvaporativeCooled_Impl::resetApproachTemperatureCoefficient2() {
      const bool result = setString(Refrigeration_Condenser_EvaporativeCooledFields::ApproachTemperatureCoefficient2, "");
      OS_ASSERT(result);
    }

    double RefrigerationCondenserEvaporativeCooled_Impl::approachTemperatureCoefficient3() const {
      boost::optional<double> value = getDouble(Refrigeration_Condenser_EvaporativeCooledFields::ApproachTemperatureCoefficient3, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool RefrigerationCondenserEvaporativeCooled_Impl::isApproachTemperatureCoefficient3Defaulted() const {
      return isEmpty(Refrigeration_Condenser_EvaporativeCooledFields::ApproachTemperatureCoefficient3);
    }

    bool RefrigerationCondenserEvaporativeCooled_Impl::setApproachTemperatureCoefficient3(double approachTemperatureCoefficient3) {
      return setDouble(Refrigeration_Condenser_EvaporativeCooledFields::ApproachTemperatureCoefficient3, approachTemperatureCoefficient3);
    }

    void RefrigerationCondenserEvaporativeCooled_Impl::resetApproachTemperatureCoefficient3() {
      const bool result = setString(Refrigeration_Condenser_EvaporativeCooledFields::ApproachTemperatureCoefficient3, "");
      OS_ASSERT(result);
    }

    double RefrigerationCondenserEvaporativeCooled_Impl::approachTemperatureCoefficient4() const {
      boost::optional<double> value = getDouble(Refrigeration_Condenser_EvaporativeCooledFields::ApproachTemperatureCoefficient4, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool RefrigerationCondenserEvaporativeCooled_Impl::isApproachTemperatureCoefficient4Defaulted() const {
      return isEmpty(Refrigeration_Condenser_EvaporativeCooledFields::ApproachTemperatureCoefficient4);
    }

    bool RefrigerationCondenserEvaporativeCooled_Impl::setApproachTemperatureCoefficient4(double approachTemperatureCoefficient4) {
      return setDouble(Refrigeration_Condenser_EvaporativeCooledFields::ApproachTemperatureCoefficient4, approachTemperatureCoefficient4);
    }

    void RefrigerationCondenserEvaporativeCooled_Impl::resetApproachTemperatureCoefficient4() {
      const bool result = setString(Refrigeration_Condenser_EvaporativeCooledFields::ApproachTemperatureCoefficient4, "");
      OS_ASSERT(result);
    }

    double RefrigerationCondenserEvaporativeCooled_Impl::minimumCapacityFactor() const {
      boost::optional<double> value = getDouble(Refrigeration_Condenser_EvaporativeCooledFields::MinimumCapacityFactor, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool RefrigerationCondenserEvaporativeCooled_Impl::isMinimumCapacityFactorDefaulted() const {
      return isEmpty(Refrigeration_Condenser_EvaporativeCooledFields::MinimumCapacityFactor);
    }

    bool RefrigerationCondenserEvaporativeCooled_Impl::setMinimumCapacityFactor(double minimumCapacityFactor) {
      return setDouble(Refrigeration_Condenser_EvaporativeCooledFields::MinimumCapacityFactor, minimumCapacityFactor);
    }

    void RefrigerationCondenserEvaporativeCooled_Impl::resetMinimumCapacityFactor() {
      setString(Refrigeration_Condenser_EvaporativeCooledFields::MinimumCapacityFactor, "");
    }

    double RefrigerationCondenserEvaporativeCooled_Impl::maximumCapacityFactor() const {
      boost::optional<double> value = getDouble(Refrigeration_Condenser_EvaporativeCooledFields::MaximumCapacityFactor, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool RefrigerationCondenserEvaporativeCooled_Impl::isMaximumCapacityFactorDefaulted() const {
      return isEmpty(Refrigeration_Condenser_EvaporativeCooledFields::MaximumCapacityFactor);
    }

    bool RefrigerationCondenserEvaporativeCooled_Impl::setMaximumCapacityFactor(double maximumCapacityFactor) {
      return setDouble(Refrigeration_Condenser_EvaporativeCooledFields::MaximumCapacityFactor, maximumCapacityFactor);
    }

    void RefrigerationCondenserEvaporativeCooled_Impl::resetMaximumCapacityFactor() {
      setString(Refrigeration_Condenser_EvaporativeCooledFields::MaximumCapacityFactor, "");
    }

    boost::optional<double> RefrigerationCondenserEvaporativeCooled_Impl::ratedAirFlowRate() const {
      return getDouble(Refrigeration_Condenser_EvaporativeCooledFields::RatedAirFlowRate, true);
    }

    bool RefrigerationCondenserEvaporativeCooled_Impl::isRatedAirFlowRateDefaulted() const {
      return isEmpty(Refrigeration_Condenser_EvaporativeCooledFields::RatedAirFlowRate);
    }

    bool RefrigerationCondenserEvaporativeCooled_Impl::isRatedAirFlowRateAutocalculated() const {
      if (auto value = getString(Refrigeration_Condenser_EvaporativeCooledFields::RatedAirFlowRate, true)) {
        return openstudio::istringEqual(*value, "autocalculate");
      }
      return false;
    }

    bool RefrigerationCondenserEvaporativeCooled_Impl::setRatedAirFlowRate(double ratedAirFlowRate) {
      return setDouble(Refrigeration_Condenser_EvaporativeCooledFields::RatedAirFlowRate, ratedAirFlowRate);
    }

    void RefrigerationCondenserEvaporativeCooled_Impl::resetRatedAirFlowRate() {
      setString(Refrigeration_Condenser_EvaporativeCooledFields::RatedAirFlowRate, "");
    }

    void RefrigerationCondenserEvaporativeCooled_Impl::autocalculateRatedAirFlowRate() {
      const bool result = setString(Refrigeration_Condenser_EvaporativeCooledFields::RatedAirFlowRate, "autocalculate");
      OS_ASSERT(result);
    }

    double RefrigerationCondenserEvaporativeCooled_Impl::basinHeaterCapacity() const {
      boost::optional<double> value = getDouble(Refrigeration_Condenser_EvaporativeCooledFields::BasinHeaterCapacity, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool RefrigerationCondenserEvaporativeCooled_Impl::isBasinHeaterCapacityDefaulted() const {
      return isEmpty(Refrigeration_Condenser_EvaporativeCooledFields::BasinHeaterCapacity);
    }

    bool RefrigerationCondenserEvaporativeCooled_Impl::setBasinHeaterCapacity(double basinHeaterCapacity) {
      return setDouble(Refrigeration_Condenser_EvaporativeCooledFields::BasinHeaterCapacity, basinHeaterCapacity);
    }

    void RefrigerationCondenserEvaporativeCooled_Impl::resetBasinHeaterCapacity() {
      setString(Refrigeration_Condenser_EvaporativeCooledFields::BasinHeaterCapacity, "");
    }

    double RefrigerationCondenserEvaporativeCooled_Impl::basinHeaterSetpointTemperature() const {
      boost::optional<double> value = getDouble(Refrigeration_Condenser_EvaporativeCooledFields::BasinHeaterSetpointTemperature, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool RefrigerationCondenserEvaporativeCooled_Impl::isBasinHeaterSetpointTemperatureDefaulted() const {
      return isEmpty(Refrigeration_Condenser_EvaporativeCooledFields::BasinHeaterSetpointTemperature);
    }

    bool RefrigerationCondenserEvaporativeCooled_Impl::setBasinHeaterSetpointTemperature(double basinHeaterSetpointTemperature) {
      return setDouble(Refrigeration_Condenser_EvaporativeCooledFields::BasinHeaterSetpointTemperature, basinHeaterSetpointTemperature);
    }

    void RefrigerationCondenserEvaporativeCooled_Impl::resetBasinHeaterSetpointTemperature() {
      setString(Refrigeration_Condenser_EvaporativeCooledFields::BasinHeaterSetpointTemperature, "");
    }

    boost::optional<double> RefrigerationCondenserEvaporativeCooled_Impl::ratedWaterPumpPower() const {
      return getDouble(Refrigeration_Condenser_EvaporativeCooledFields::RatedWaterPumpPower, true);
    }

    bool RefrigerationCondenserEvaporativeCooled_Impl::isRatedWaterPumpPowerDefaulted() const {
      return isEmpty(Refrigeration_Condenser_EvaporativeCooledFields::RatedWaterPumpPower);
    }

    bool RefrigerationCondenserEvaporativeCooled_Impl::isRatedWaterPumpPowerAutocalculated() const {
      if (auto value = getString(Refrigeration_Condenser_EvaporativeCooledFields::RatedWaterPumpPower, true)) {
        return openstudio::istringEqual(*value, "autocalculate");
      }
      return false;
    }

    bool RefrigerationCondenserEvaporativeCooled_Impl::setRatedWaterPumpPower(double ratedWaterPumpPower) {
      return setDouble(Refrigeration_Condenser_EvaporativeCooledFields::RatedWaterPumpPower, ratedWaterPumpPower);
    }

    void RefrigerationCondenserEvaporativeCooled_Impl::resetRatedWaterPumpPower() {
      setString(Refrigeration_Condenser_EvaporativeCooledFields::RatedWaterPumpPower, "");
    }

    void RefrigerationCondenserEvaporativeCooled_Impl::autocalculateRatedWaterPumpPower() {
      const bool result = setString(Refrigeration_Condenser_EvaporativeCooledFields::RatedWaterPumpPower, "autocalculate");
      OS_ASSERT(result);
    }

    std::string RefrigerationCondenserEvaporativeCooled_Impl::endUseSubcategory() const {
      boost::optional<std::string> value = getString(Refrigeration_Condenser_EvaporativeCooledFields::EndUseSubcategory, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool RefrigerationCondenserEvaporativeCooled_Impl::isEndUseSubcategoryDefaulted() const {
      return isEmpty(Refrigeration_Condenser_EvaporativeCooledFields::EndUseSubcategory);
    }

    bool RefrigerationCondenserEvaporativeCooled_Impl::setEndUseSubcategory(const std::string& endUseSubcategory) {
      return setString(Refrigeration_Condenser_EvaporativeCooledFields::EndUseSubcategory, endUseSubcategory);
    }

    void RefrigerationCondenserEvaporativeCooled_Impl::resetEndUseSubcategory() {
      setString(Refrigeration_Condenser_EvaporativeCooledFields::EndUseSubcategory, "");
    }

    double RefrigerationCondenserEvaporativeCooled_Impl::condenserRefrigerantOperatingChargeInventory() const {
      boost::optional<double> value = getDouble(Refrigeration_Condenser_EvaporativeCooledFields::CondenserRefrigerantOperatingChargeInventory, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool RefrigerationCondenserEvaporativeCooled_Impl::isCondenserRefrigerantOperatingChargeInventoryDefaulted() const {
      return isEmpty(Refrigeration_Condenser_EvaporativeCooledFields::CondenserRefrigerantOperatingChargeInventory);
    }

    bool RefrigerationCondenserEvaporativeCooled_Impl::setCondenserRefrigerantOperatingChargeInventory(
      double condenserRefrigerantOperatingChargeInventory) {
      return setDouble(Refrigeration_Condenser_EvaporativeCooledFields::CondenserRefrigerantOperatingChargeInventory,
                       condenserRefrigerantOperatingChargeInventory);
    }

    void RefrigerationCondenserEvaporativeCooled_Impl::resetCondenserRefrigerantOperatingChargeInventory() {
      setString(Refrigeration_Condenser_EvaporativeCooledFields::CondenserRefrigerantOperatingChargeInventory, "");
    }

    double RefrigerationCondenserEvaporativeCooled_Impl::condensateReceiverRefrigerantInventory() const {
      boost::optional<double> value = getDouble(Refrigeration_Condenser_EvaporativeCooledFields::CondensateReceiverRefrigerantInventory, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool RefrigerationCondenserEvaporativeCooled_Impl::isCondensateReceiverRefrigerantInventoryDefaulted() const {
      return isEmpty(Refrigeration_Condenser_EvaporativeCooledFields::CondensateReceiverRefrigerantInventory);
    }

    bool RefrigerationCondenserEvaporativeCooled_Impl::setCondensateReceiverRefrigerantInventory(double condensateReceiverRefrigerantInventory) {
      return setDouble(Refrigeration_Condenser_EvaporativeCooledFields::CondensateReceiverRefrigerantInventory,
                       condensateReceiverRefrigerantInventory);
    }

    void RefrigerationCondenserEvaporativeCooled_Impl::resetCondensateReceiverRefrigerantInventory() {
      setString(Refrigeration_Condenser_EvaporativeCooledFields::CondensateReceiverRefrigerantInventory, "");
    }

    double RefrigerationCondenserEvaporativeCooled_Impl::condensatePipingRefrigerantInventory() const {
      boost::optional<double> value = getDouble(Refrigeration_Condenser_EvaporativeCooledFields::CondensatePipingRefrigerantInventory, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool RefrigerationCondenserEvaporativeCooled_Impl::isCondensatePipingRefrigerantInventoryDefaulted() const {
      return isEmpty(Refrigeration_Condenser_EvaporativeCooledFields::CondensatePipingRefrigerantInventory);
    }

    bool RefrigerationCondenserEvaporativeCooled_Impl::setCondensatePipingRefrigerantInventory(double condensatePipingRefrigerantInventory) {
      return setDouble(Refrigeration_Condenser_EvaporativeCooledFields::CondensatePipingRefrigerantInventory, condensatePipingRefrigerantInventory);
    }

    void RefrigerationCondenserEvaporativeCooled_Impl::resetCondensatePipingRefrigerantInventory() {
      setString(Refrigeration_Condenser_EvaporativeCooledFields::CondensatePipingRefrigerantInventory, "");
    }

  }  // namespace detail

  RefrigerationCondenserEvaporativeCooled::RefrigerationCondenserEvaporativeCooled(const Model& model)
    : ParentObject(RefrigerationCondenserEvaporativeCooled::iddObjectType(), model) {}

  RefrigerationCondenserEvaporativeCooled::RefrigerationCondenserEvaporativeCooled(
    std::shared_ptr<detail::RefrigerationCondenserEvaporativeCooled_Impl> impl)
    : ParentObject(std::move(impl)) {}

  IddObjectType RefrigerationCondenserEvaporativeCooled::iddObjectType() {
    return IddObjectType::Refrigeration_Condenser_EvaporativeCooled;
  }

  std::vector<std::string> RefrigerationCondenserEvaporativeCooled::fanSpeedControlTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          Refrigeration_Condenser_EvaporativeCooledFields::FanSpeedControlType);
  }

  double RefrigerationCondenserEvaporativeCooled::ratedEffectiveTotalHeatRejectionRate() const {
    return getImpl<detail::RefrigerationCondenserEvaporativeCooled_Impl>()->ratedEffectiveTotalHeatRejectionRate();
  }

  bool RefrigerationCondenserEvaporativeCooled::setRatedEffectiveTotalHeatRejectionRate(double ratedEffectiveTotalHeatRejectionRate) {
    return getImpl<detail::RefrigerationCondenserEvaporativeCooled_Impl>()->setRatedEffectiveTotalHeatRejectionRate(
      ratedEffectiveTotalHeatRejectionRate);
  }

  double RefrigerationCondenserEvaporativeCooled::ratedSubcoolingTemperatureDifference() const {
    return getImpl<detail::RefrigerationCondenserEvaporativeCooled_Impl>()->ratedSubcoolingTemperatureDifference();
  }

  bool RefrigerationCondenserEvaporativeCooled::isRatedSubcoolingTemperatureDifferenceDefaulted() const {
    return getImpl<detail::RefrigerationCondenserEvaporativeCooled_Impl>()->isRatedSubcoolingTemperatureDifferenceDefaulted();
  }

  bool RefrigerationCondenserEvaporativeCooled::setRatedSubcoolingTemperatureDifference(double ratedSubcoolingTemperatureDifference) {
    return getImpl<detail::RefrigerationCondenserEvaporativeCooled_Impl>()->setRatedSubcoolingTemperatureDifference(
      ratedSubcoolingTemperatureDifference);
  }

  void RefrigerationCondenserEvaporativeCooled::resetRatedSubcoolingTemperatureDifference() {
    getImpl<detail::RefrigerationCondenserEvaporativeCooled_Impl>()->resetRatedSubcoolingTemperatureDifference();
  }

  std::string RefrigerationCondenserEvaporativeCooled::fanSpeedControlType() const {
    return getImpl<detail::RefrigerationCondenserEvaporativeCooled_Impl>()->fanSpeedControlType();
  }

  bool RefrigerationCondenserEvaporativeCooled::isFanSpeedControlTypeDefaulted() const {
    return getImpl<detail::RefrigerationCondenserEvaporativeCooled_Impl>()->isFanSpeedControlTypeDefaulted();
  }

  bool RefrigerationCondenserEvaporativeCooled::setFanSpeedControlType(const std::string& fanSpeedControlType) {
    return getImpl<detail::RefrigerationCondenserEvaporativeCooled_Impl>()->setFanSpeedControlType(fanSpeedControlType);
  }

  void RefrigerationCondenserEvaporativeCooled::resetFanSpeedControlType() {
    getImpl<detail::RefrigerationCondenserEvaporativeCooled_Impl>()->resetFanSpeedControlType();
  }

  double RefrigerationCondenserEvaporativeCooled::ratedFanPower() const {
    return getImpl<detail::RefrigerationCondenserEvaporativeCooled_Impl>()->ratedFanPower();
  }

  bool RefrigerationCondenserEvaporativeCooled::setRatedFanPower(double ratedFanPower) {
    return getImpl<detail::RefrigerationCondenserEvaporativeCooled_Impl>()->setRatedFanPower(ratedFanPower);
  }

  double RefrigerationCondenserEvaporativeCooled::minimumFanAirFlowRatio() const {
    return getImpl<detail::RefrigerationCondenserEvaporativeCooled_Impl>()->minimumFanAirFlowRatio();
  }

  bool RefrigerationCondenserEvaporativeCooled::isMinimumFanAirFlowRatioDefaulted() const {
    return getImpl<detail::RefrigerationCondenserEvaporativeCooled_Impl>()->isMinimumFanAirFlowRatioDefaulted();
  }

  bool RefrigerationCondenserEvaporativeCooled::setMinimumFanAirFlowRatio(double minimumFanAirFlowRatio) {
    return getImpl<detail::RefrigerationCondenserEvaporativeCooled_Impl>()->setMinimumFanAirFlowRatio(minimumFanAirFlowRatio);
  }

  void RefrigerationCondenserEvaporativeCooled::resetMinimumFanAirFlowRatio() {
    getImpl<detail::RefrigerationCondenserEvaporativeCooled_Impl>()->resetMinimumFanAirFlowRatio();
  }

  double RefrigerationCondenserEvaporativeCooled::approachTemperatureConstantTerm() const {
    return getImpl<detail::RefrigerationCondenserEvaporativeCooled_Impl>()->approachTemperatureConstantTerm();
  }

  bool RefrigerationCondenserEvaporativeCooled::isApproachTemperatureConstantTermDefaulted() const {
    return getImpl<detail::RefrigerationCondenserEvaporativeCooled_Impl>()->isApproachTemperatureConstantTermDefaulted();
  }

  bool RefrigerationCondenserEvaporativeCooled::setApproachTemperatureConstantTerm(double approachTemperatureConstantTerm) {
    return getImpl<detail::RefrigerationCondenserEvaporativeCooled_Impl>()->setApproachTemperatureConstantTerm(approachTemperatureConstantTerm);
  }

  void RefrigerationCondenserEvaporativeCooled::resetApproachTemperatureConstantTerm() {
    getImpl<detail::RefrigerationCondenserEvaporativeCooled_Impl>()->resetApproachTemperatureConstantTerm();
  }

  double RefrigerationCondenserEvaporativeCooled::approachTemperatureCoefficient2() const {
    return getImpl<detail::RefrigerationCondenserEvaporativeCooled_Impl>()->approachTemperatureCoefficient2();
  }

  bool RefrigerationCondenserEvaporativeCooled::isApproachTemperatureCoefficient2Defaulted() const {
    return getImpl<detail::RefrigerationCondenserEvaporativeCooled_Impl>()->isApproachTemperatureCoefficient2Defaulted();
  }

  bool RefrigerationCondenserEvaporativeCooled::setApproachTemperatureCoefficient2(double approachTemperatureCoefficient2) {
    return getImpl<detail::RefrigerationCondenserEvaporativeCooled_Impl>()->setApproachTemperatureCoefficient2(approachTemperatureCoefficient2);
  }

  void RefrigerationCondenserEvaporativeCooled::resetApproachTemperatureCoefficient2() {
    getImpl<detail::RefrigerationCondenserEvaporativeCooled_Impl>()->resetApproachTemperatureCoefficient2();
  }

  double RefrigerationCondenserEvaporativeCooled::approachTemperatureCoefficient3() const {
    return getImpl<detail::RefrigerationCondenserEvaporativeCooled_Impl>()->approachTemperatureCoefficient3();
  }

  bool RefrigerationCondenserEvaporativeCooled::isApproachTemperatureCoefficient3Defaulted() const {
    return getImpl<detail::RefrigerationCondenserEvaporativeCooled_Impl>()->isApproachTemperatureCoefficient3Defaulted();
  }

  bool RefrigerationCondenserEvaporativeCooled::setApproachTemperatureCoefficient3(double approachTemperatureCoefficient3) {
    return getImpl<detail::RefrigerationCondenserEvaporativeCooled_Impl>()->setApproachTemperatureCoefficient3(approachTemperatureCoefficient3);
  }

  void RefrigerationCondenserEvaporativeCooled::resetApproachTemperatureCoefficient3() {
    getImpl<detail::RefrigerationCondenserEvaporativeCooled_Impl>()->resetApproachTemperatureCoefficient3();
  }

  double RefrigerationCondenserEvaporativeCooled::approachTemperatureCoefficient4() const {
    return getImpl<detail::RefrigerationCondenserEvaporativeCooled_Impl>()->approachTemperatureCoefficient4();
  }

  bool RefrigerationCondenserEvaporativeCooled::isApproachTemperatureCoefficient4Defaulted() const {
    return getImpl<detail::RefrigerationCondenserEvaporativeCooled_Impl>()->isApproachTemperatureCoefficient4Defaulted();
  }

  bool RefrigerationCondenserEvaporativeCooled::setApproachTemperatureCoefficient4(double approachTemperatureCoefficient4) {
    return getImpl<detail::RefrigerationCondenserEvaporativeCooled_Impl>()->setApproachTemperatureCoefficient4(approachTemperatureCoefficient4);
  }

  void RefrigerationCondenserEvaporativeCooled::resetApproachTemperatureCoefficient4() {
    getImpl<detail::RefrigerationCondenserEvaporativeCooled_Impl>()->resetApproachTemperatureCoefficient4();
  }

  double RefrigerationCondenserEvaporativeCooled::minimumCapacityFactor() const {
    return getImpl<detail::RefrigerationCondenserEvaporativeCooled_Impl>()->minimumCapacityFactor();
  }

  bool RefrigerationCondenserEvaporativeCooled::isMinimumCapacityFactorDefaulted() const {
    return getImpl<detail::RefrigerationCondenserEvaporativeCooled_Impl>()->isMinimumCapacityFactorDefaulted();
  }

  bool RefrigerationCondenserEvaporativeCooled::setMinimumCapacityFactor(double minimumCapacityFactor) {
    return getImpl<detail::RefrigerationCondenserEvaporativeCooled_Impl>()->setMinimumCapacityFactor(minimumCapacityFactor);
  }

  void RefrigerationCondenserEvaporativeCooled::resetMinimumCapacityFactor() {
    getImpl<detail::RefrigerationCondenserEvaporativeCooled_Impl>()->resetMinimumCapacityFactor();
  }

  double RefrigerationCondenserEvaporativeCooled::maximumCapacityFactor() const {
    return getImpl<detail::RefrigerationCondenserEvaporativeCooled_Impl>()->maximumCapacityFactor();
  }

  bool RefrigerationCondenserEvaporativeCooled::isMaximumCapacityFactorDefaulted() const {
    return getImpl<detail::RefrigerationCondenserEvaporativeCooled_Impl>()->isMaximumCapacityFactorDefaulted();
  }

  bool RefrigerationCondenserEvaporativeCooled::setMaximumCapacityFactor(double maximumCapacityFactor) {
    return getImpl<detail::RefrigerationCondenserEvaporativeCooled_Impl>()->setMaximumCapacityFactor(maximumCapacityFactor);
  }

  void RefrigerationCondenserEvaporativeCooled::resetMaximumCapacityFactor() {
    getImpl<detail::RefrigerationCondenserEvaporativeCooled_Impl>()->resetMaximumCapacityFactor();
  }

  boost::optional<double> RefrigerationCondenserEvaporativeCooled::ratedAirFlowRate() const {
    return getImpl<detail::RefrigerationCondenserEvaporativeCooled_Impl>()->ratedAirFlowRate();
  }

  bool RefrigerationCondenserEvaporativeCooled::isRatedAirFlowRateDefaulted() const {
    return getImpl<detail::RefrigerationCondenserEvaporativeCooled_Impl>()->isRatedAirFlowRateDefaulted();
  }

  bool RefrigerationCondenserEvaporativeCooled::isRatedAirFlowRateAutocalculated() const {
    return getImpl<detail::RefrigerationCondenserEvaporativeCooled_Impl>()->isRatedAirFlowRateAutocalculated();
  }

  bool RefrigerationCondenserEvaporativeCooled::setRatedAirFlowRate(double ratedAirFlowRate) {
    return getImpl<detail::RefrigerationCondenserEvaporativeCooled_Impl>()->setRatedAirFlowRate(ratedAirFlowRate);
  }

  void RefrigerationCondenserEvaporativeCooled::resetRatedAirFlowRate() {
    getImpl<detail::RefrigerationCondenserEvaporativeCooled_Impl>()->resetRatedAirFlowRate();
  }

  void RefrigerationCondenserEvaporativeCooled::autocalculateRatedAirFlowRate() {
    getImpl<detail::RefrigerationCondenserEvaporativeCooled_Impl>()->autocalculateRatedAirFlowRate();
  }

  double RefrigerationCondenserEvaporativeCooled::basinHeaterCapacity() const {
    return getImpl<detail::RefrigerationCondenserEvaporativeCooled_Impl>()->basinHeaterCapacity();
  }

  bool RefrigerationCondenserEvaporativeCooled::isBasinHeaterCapacityDefaulted() const {
    return getImpl<detail::RefrigerationCondenserEvaporativeCooled_Impl>()->isBasinHeaterCapacityDefaulted();
  }

  bool RefrigerationCondenserEvaporativeCooled::setBasinHeaterCapacity(double basinHeaterCapacity) {
    return getImpl<detail::RefrigerationCondenserEvaporativeCooled_Impl>()->setBasinHeaterCapacity(basinHeaterCapacity);
  }

  void RefrigerationCondenserEvaporativeCooled::resetBasinHeaterCapacity() {
    getImpl<detail::RefrigerationCondenserEvaporativeCooled_Impl>()->resetBasinHeaterCapacity();
  }

  double RefrigerationCondenserEvaporativeCooled::basinHeaterSetpointTemperature() const {
    return getImpl<detail::RefrigerationCondenserEvaporativeCooled_Impl>()->basinHeaterSetpointTemperature();
  }

  bool RefrigerationCondenserEvaporativeCooled::isBasinHeaterSetpointTemperatureDefaulted() const {
    return getImpl<detail::RefrigerationCondenserEvaporativeCooled_Impl>()->isBasinHeaterSetpointTemperatureDefaulted();
  }

  bool RefrigerationCondenserEvaporativeCooled::setBasinHeaterSetpointTemperature(double basinHeaterSetpointTemperature) {
    return getImpl<detail::RefrigerationCondenserEvaporativeCooled_Impl>()->setBasinHeaterSetpointTemperature(basinHeaterSetpointTemperature);
  }

  void RefrigerationCondenserEvaporativeCooled::resetBasinHeaterSetpointTemperature() {
    getImpl<detail::RefrigerationCondenserEvaporativeCooled_Impl>()->resetBasinHeaterSetpointTemperature();
  }

  boost::optional<double> RefrigerationCondenserEvaporativeCooled::ratedWaterPumpPower() const {
    return getImpl<detail::RefrigerationCondenserEvaporativeCooled_Impl>()->ratedWaterPumpPower();
  }

  bool RefrigerationCondenserEvaporativeCooled::isRatedWaterPumpPowerDefaulted() const {
    return getImpl<detail::RefrigerationCondenserEvaporativeCooled_Impl>()->isRatedWaterPumpPowerDefaulted();
  }

  bool RefrigerationCondenserEvaporativeCooled::isRatedWaterPumpPowerAutocalculated() const {
    return getImpl<detail::RefrigerationCondenserEvaporativeCooled_Impl>()->isRatedWaterPumpPowerAutocalculated();
  }

  bool RefrigerationCondenserEvaporativeCooled::setRatedWaterPumpPower(double ratedWaterPumpPower) {
    return getImpl<detail::RefrigerationCondenserEvaporativeCooled_Impl>()->setRatedWaterPumpPower(ratedWaterPumpPower);
  }

  void RefrigerationCondenserEvaporativeCooled::resetRatedWaterPumpPower() {
    getImpl<detail::RefrigerationCondenserEvaporativeCooled_Impl>()->resetRatedWaterPumpPower();
  }

  void RefrigerationCondenserEvaporativeCooled::autocalculateRatedWaterPumpPower() {
    getImpl<detail::RefrigerationCondenserEvaporativeCooled_Impl>()->autocalculateRatedWaterPumpPower();
  }

  std::string RefrigerationCondenserEvaporativeCooled::endUseSubcategory() const {
    return getImpl<detail::RefrigerationCondenserEvaporativeCooled_Impl>()->endUseSubcategory();
  }

  bool RefrigerationCondenserEvaporativeCooled::isEndUseSubcategoryDefaulted() const {
    return getImpl<detail::RefrigerationCondenserEvaporativeCooled_Impl>()->isEndUseSubcategoryDefaulted();
  }

  bool RefrigerationCondenserEvaporativeCooled::setEndUseSubcategory(const std::string& endUseSubcategory) {
    return getImpl<detail::RefrigerationCondenserEvaporativeCooled_Impl>()->setEndUseSubcategory(endUseSubcategory);
  }

  void RefrigerationCondenserEvaporativeCooled::resetEndUseSubcategory() {
    getImpl<detail::RefrigerationCondenserEvaporativeCooled_Impl>()->resetEndUseSubcategory();
  }

  double RefrigerationCondenserEvaporativeCooled::condenserRefrigerantOperatingChargeInventory() const {
    return getImpl<detail::RefrigerationCondenserEvaporativeCooled_Impl>()->condenserRefrigerantOperatingChargeInventory();
  }

  bool RefrigerationCondenserEvaporativeCooled::isCondenserRefrigerantOperatingChargeInventoryDefaulted() const {
    return getImpl<detail::RefrigerationCondenserEvaporativeCooled_Impl>()->isCondenserRefrigerantOperatingChargeInventoryDefaulted();
  }

  bool RefrigerationCondenserEvaporativeCooled::setCondenserRefrigerantOperatingChargeInventory(double condenserRefrigerantOperatingChargeInventory) {
    return getImpl<detail::RefrigerationCondenserEvaporativeCooled_Impl>()->setCondenserRefrigerantOperatingChargeInventory(
      condenserRefrigerantOperatingChargeInventory);
  }

  void RefrigerationCondenserEvaporativeCooled::resetCondenserRefrigerantOperatingChargeInventory() {
    getImpl<detail::RefrigerationCondenserEvaporativeCooled_Impl>()->resetCondenserRefrigerantOperatingChargeInventory();
  }

  double RefrigerationCondenserEvaporativeCooled::condensateReceiverRefrigerantInventory() const {
    return getImpl<detail::RefrigerationCondenserEvaporativeCooled_Impl>()->condensateReceiverRefrigerantInventory();
  }

  bool RefrigerationCondenserEvaporativeCooled::isCondensateReceiverRefrigerantInventoryDefaulted() const {
    return getImpl<detail::RefrigerationCondenserEvaporativeCooled_Impl>()->isCondensateReceiverRefrigerantInventoryDefaulted();
  }

  bool RefrigerationCondenserEvaporativeCooled::setCondensateReceiverRefrigerantInventory(double condensateReceiverRefrigerantInventory) {
    return getImpl<detail::RefrigerationCondenserEvaporativeCooled_Impl>()->setCondensateReceiverRefrigerantInventory(
      condensateReceiverRefrigerantInventory);
  }

  void RefrigerationCondenserEvaporativeCooled::resetCondensateReceiverRefrigerantInventory() {
    getImpl<detail::RefrigerationCondenserEvaporativeCooled_Impl>()->resetCondensateReceiverRefrigerantInventory();
  }

  double RefrigerationCondenserEvaporativeCooled::condensatePipingRefrigerantInventory() const {
    return getImpl<detail::RefrigerationCondenserEvaporativeCooled_Impl>()->condensatePipingRefrigerantInventory();
  }

  bool RefrigerationCondenserEvaporativeCooled::isCondensatePipingRefrigerantInventoryDefaulted() const {
    return getImpl<detail::RefrigerationCondenserEvaporativeCooled_Impl>()->isCondensatePipingRefrigerantInventoryDefaulted();
  }

  bool RefrigerationCondenserEvaporativeCooled::setCondensatePipingRefrigerantInventory(double condensatePipingRefrigerantInventory) {
    return getImpl<detail::RefrigerationCondenserEvaporativeCooled_Impl>()->setCondensatePipingRefrigerantInventory(
      condensatePipingRefrigerantInventory);
  }

  void RefrigerationCondenserEvaporativeCooled::resetCondensatePipingRefrigerantInventory() {
    getImpl<detail::RefrigerationCondenserEvaporativeCooled_Impl>()->resetCondensatePipingRefrigerantInventory();
  }

}  // namespace epmodel
}  // namespace openstudio
