/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ZoneHVACComponent/RefrigerationAirChiller.hpp"
#include "ZoneHVACComponent/RefrigerationAirChiller_Impl.hpp"

#include "Model.hpp"

#include "../utilities/core/Assert.hpp"
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/Refrigeration_AirChiller_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  RefrigerationAirChiller::RefrigerationAirChiller(const Model& model) : ModelObject(RefrigerationAirChiller::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::RefrigerationAirChiller_Impl>());

    OS_ASSERT(setCapacityRatingType("UnitLoadFactorSensibleOnly"));
    OS_ASSERT(setRatedCoolingSourceTemperature(0.0));
    OS_ASSERT(setRatedTemperatureDifferenceDT1(10.0));
    OS_ASSERT(setCapacityCorrectionCurveType("LinearSHR60"));
    OS_ASSERT(setRatedTotalHeatingPower(1000.0));
    OS_ASSERT(setRatedAirFlow(1.0));
    OS_ASSERT(setFanSpeedControlType("Fixed"));
    OS_ASSERT(setDefrostType("Electric"));
    OS_ASSERT(setDefrostControlType("TimeSchedule"));
    OS_ASSERT(setVerticalLocation("Middle"));
  }

  RefrigerationAirChiller::RefrigerationAirChiller(std::shared_ptr<detail::RefrigerationAirChiller_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType RefrigerationAirChiller::iddObjectType() {
    return IddObjectType::Refrigeration_AirChiller;
  }

  std::vector<std::string> RefrigerationAirChiller::capacityRatingTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), Refrigeration_AirChillerFields::CapacityRatingType);
  }

  std::vector<std::string> RefrigerationAirChiller::capacityCorrectionCurveTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), Refrigeration_AirChillerFields::CapacityCorrectionCurveType);
  }

  std::vector<std::string> RefrigerationAirChiller::fanSpeedControlTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), Refrigeration_AirChillerFields::FanSpeedControlType);
  }

  std::vector<std::string> RefrigerationAirChiller::defrostTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), Refrigeration_AirChillerFields::DefrostType);
  }

  std::vector<std::string> RefrigerationAirChiller::defrostControlTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), Refrigeration_AirChillerFields::DefrostControlType);
  }

  std::vector<std::string> RefrigerationAirChiller::verticalLocationValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), Refrigeration_AirChillerFields::VerticalLocation);
  }

  std::string RefrigerationAirChiller::capacityRatingType() const {
    return getImpl<detail::RefrigerationAirChiller_Impl>()->capacityRatingType();
  }

  boost::optional<double> RefrigerationAirChiller::ratedUnitLoadFactor() const {
    return getImpl<detail::RefrigerationAirChiller_Impl>()->ratedUnitLoadFactor();
  }

  bool RefrigerationAirChiller::setRatedUnitLoadFactor(double ratedUnitLoadFactor) {
    return getImpl<detail::RefrigerationAirChiller_Impl>()->setRatedUnitLoadFactor(ratedUnitLoadFactor);
  }

  void RefrigerationAirChiller::resetRatedUnitLoadFactor() {
    getImpl<detail::RefrigerationAirChiller_Impl>()->resetRatedUnitLoadFactor();
  }

  boost::optional<double> RefrigerationAirChiller::ratedCapacity() const {
    return getImpl<detail::RefrigerationAirChiller_Impl>()->ratedCapacity();
  }

  bool RefrigerationAirChiller::setRatedCapacity(double ratedCapacity) {
    return getImpl<detail::RefrigerationAirChiller_Impl>()->setRatedCapacity(ratedCapacity);
  }

  void RefrigerationAirChiller::resetRatedCapacity() {
    getImpl<detail::RefrigerationAirChiller_Impl>()->resetRatedCapacity();
  }

  double RefrigerationAirChiller::ratedRelativeHumidity() const {
    return getImpl<detail::RefrigerationAirChiller_Impl>()->ratedRelativeHumidity();
  }

  bool RefrigerationAirChiller::isRatedRelativeHumidityDefaulted() const {
    return getImpl<detail::RefrigerationAirChiller_Impl>()->isRatedRelativeHumidityDefaulted();
  }

  bool RefrigerationAirChiller::setRatedRelativeHumidity(double ratedRelativeHumidity) {
    return getImpl<detail::RefrigerationAirChiller_Impl>()->setRatedRelativeHumidity(ratedRelativeHumidity);
  }

  void RefrigerationAirChiller::resetRatedRelativeHumidity() {
    getImpl<detail::RefrigerationAirChiller_Impl>()->resetRatedRelativeHumidity();
  }

  double RefrigerationAirChiller::ratedCoolingSourceTemperature() const {
    return getImpl<detail::RefrigerationAirChiller_Impl>()->ratedCoolingSourceTemperature();
  }

  bool RefrigerationAirChiller::setRatedCoolingSourceTemperature(double ratedCoolingSourceTemperature) {
    return getImpl<detail::RefrigerationAirChiller_Impl>()->setRatedCoolingSourceTemperature(ratedCoolingSourceTemperature);
  }

  double RefrigerationAirChiller::ratedTemperatureDifferenceDT1() const {
    return getImpl<detail::RefrigerationAirChiller_Impl>()->ratedTemperatureDifferenceDT1();
  }

  bool RefrigerationAirChiller::setRatedTemperatureDifferenceDT1(double ratedTemperatureDifferenceDT1) {
    return getImpl<detail::RefrigerationAirChiller_Impl>()->setRatedTemperatureDifferenceDT1(ratedTemperatureDifferenceDT1);
  }

  boost::optional<double> RefrigerationAirChiller::maximumTemperatureDifferenceBetweenInletAirandEvaporatingTemperature() const {
    return getImpl<detail::RefrigerationAirChiller_Impl>()->maximumTemperatureDifferenceBetweenInletAirandEvaporatingTemperature();
  }

  bool RefrigerationAirChiller::setMaximumTemperatureDifferenceBetweenInletAirandEvaporatingTemperature(
    double maximumTemperatureDifferenceBetweenInletAirandEvaporatingTemperature) {
    return getImpl<detail::RefrigerationAirChiller_Impl>()->setMaximumTemperatureDifferenceBetweenInletAirandEvaporatingTemperature(
      maximumTemperatureDifferenceBetweenInletAirandEvaporatingTemperature);
  }

  void RefrigerationAirChiller::resetMaximumTemperatureDifferenceBetweenInletAirandEvaporatingTemperature() {
    getImpl<detail::RefrigerationAirChiller_Impl>()->resetMaximumTemperatureDifferenceBetweenInletAirandEvaporatingTemperature();
  }

  double RefrigerationAirChiller::coilMaterialCorrectionFactor() const {
    return getImpl<detail::RefrigerationAirChiller_Impl>()->coilMaterialCorrectionFactor();
  }

  bool RefrigerationAirChiller::isCoilMaterialCorrectionFactorDefaulted() const {
    return getImpl<detail::RefrigerationAirChiller_Impl>()->isCoilMaterialCorrectionFactorDefaulted();
  }

  bool RefrigerationAirChiller::setCoilMaterialCorrectionFactor(double coilMaterialCorrectionFactor) {
    return getImpl<detail::RefrigerationAirChiller_Impl>()->setCoilMaterialCorrectionFactor(coilMaterialCorrectionFactor);
  }

  void RefrigerationAirChiller::resetCoilMaterialCorrectionFactor() {
    getImpl<detail::RefrigerationAirChiller_Impl>()->resetCoilMaterialCorrectionFactor();
  }

  double RefrigerationAirChiller::refrigerantCorrectionFactor() const {
    return getImpl<detail::RefrigerationAirChiller_Impl>()->refrigerantCorrectionFactor();
  }

  bool RefrigerationAirChiller::isRefrigerantCorrectionFactorDefaulted() const {
    return getImpl<detail::RefrigerationAirChiller_Impl>()->isRefrigerantCorrectionFactorDefaulted();
  }

  bool RefrigerationAirChiller::setRefrigerantCorrectionFactor(double refrigerantCorrectionFactor) {
    return getImpl<detail::RefrigerationAirChiller_Impl>()->setRefrigerantCorrectionFactor(refrigerantCorrectionFactor);
  }

  void RefrigerationAirChiller::resetRefrigerantCorrectionFactor() {
    getImpl<detail::RefrigerationAirChiller_Impl>()->resetRefrigerantCorrectionFactor();
  }

  std::string RefrigerationAirChiller::capacityCorrectionCurveType() const {
    return getImpl<detail::RefrigerationAirChiller_Impl>()->capacityCorrectionCurveType();
  }

  bool RefrigerationAirChiller::isCapacityCorrectionCurveTypeDefaulted() const {
    return getImpl<detail::RefrigerationAirChiller_Impl>()->isCapacityCorrectionCurveTypeDefaulted();
  }

  bool RefrigerationAirChiller::setCapacityCorrectionCurveType(const std::string& capacityCorrectionCurveType) {
    return getImpl<detail::RefrigerationAirChiller_Impl>()->setCapacityCorrectionCurveType(capacityCorrectionCurveType);
  }

  void RefrigerationAirChiller::resetCapacityCorrectionCurveType() {
    getImpl<detail::RefrigerationAirChiller_Impl>()->resetCapacityCorrectionCurveType();
  }

  double RefrigerationAirChiller::sHR60CorrectionFactor() const {
    return getImpl<detail::RefrigerationAirChiller_Impl>()->sHR60CorrectionFactor();
  }

  bool RefrigerationAirChiller::isSHR60CorrectionFactorDefaulted() const {
    return getImpl<detail::RefrigerationAirChiller_Impl>()->isSHR60CorrectionFactorDefaulted();
  }

  bool RefrigerationAirChiller::setSHR60CorrectionFactor(double sHR60CorrectionFactor) {
    return getImpl<detail::RefrigerationAirChiller_Impl>()->setSHR60CorrectionFactor(sHR60CorrectionFactor);
  }

  void RefrigerationAirChiller::resetSHR60CorrectionFactor() {
    getImpl<detail::RefrigerationAirChiller_Impl>()->resetSHR60CorrectionFactor();
  }

  double RefrigerationAirChiller::ratedTotalHeatingPower() const {
    return getImpl<detail::RefrigerationAirChiller_Impl>()->ratedTotalHeatingPower();
  }

  bool RefrigerationAirChiller::setRatedTotalHeatingPower(double ratedTotalHeatingPower) {
    return getImpl<detail::RefrigerationAirChiller_Impl>()->setRatedTotalHeatingPower(ratedTotalHeatingPower);
  }

  std::string RefrigerationAirChiller::fanSpeedControlType() const {
    return getImpl<detail::RefrigerationAirChiller_Impl>()->fanSpeedControlType();
  }

  bool RefrigerationAirChiller::isFanSpeedControlTypeDefaulted() const {
    return getImpl<detail::RefrigerationAirChiller_Impl>()->isFanSpeedControlTypeDefaulted();
  }

  bool RefrigerationAirChiller::setFanSpeedControlType(const std::string& fanSpeedControlType) {
    return getImpl<detail::RefrigerationAirChiller_Impl>()->setFanSpeedControlType(fanSpeedControlType);
  }

  void RefrigerationAirChiller::resetFanSpeedControlType() {
    getImpl<detail::RefrigerationAirChiller_Impl>()->resetFanSpeedControlType();
  }

  double RefrigerationAirChiller::ratedFanPower() const {
    return getImpl<detail::RefrigerationAirChiller_Impl>()->ratedFanPower();
  }

  bool RefrigerationAirChiller::isRatedFanPowerDefaulted() const {
    return getImpl<detail::RefrigerationAirChiller_Impl>()->isRatedFanPowerDefaulted();
  }

  bool RefrigerationAirChiller::setRatedFanPower(double ratedFanPower) {
    return getImpl<detail::RefrigerationAirChiller_Impl>()->setRatedFanPower(ratedFanPower);
  }

  void RefrigerationAirChiller::resetRatedFanPower() {
    getImpl<detail::RefrigerationAirChiller_Impl>()->resetRatedFanPower();
  }

  double RefrigerationAirChiller::ratedAirFlow() const {
    return getImpl<detail::RefrigerationAirChiller_Impl>()->ratedAirFlow();
  }

  bool RefrigerationAirChiller::setRatedAirFlow(double ratedAirFlow) {
    return getImpl<detail::RefrigerationAirChiller_Impl>()->setRatedAirFlow(ratedAirFlow);
  }

  double RefrigerationAirChiller::minimumFanAirFlowRatio() const {
    return getImpl<detail::RefrigerationAirChiller_Impl>()->minimumFanAirFlowRatio();
  }

  bool RefrigerationAirChiller::isMinimumFanAirFlowRatioDefaulted() const {
    return getImpl<detail::RefrigerationAirChiller_Impl>()->isMinimumFanAirFlowRatioDefaulted();
  }

  bool RefrigerationAirChiller::setMinimumFanAirFlowRatio(double minimumFanAirFlowRatio) {
    return getImpl<detail::RefrigerationAirChiller_Impl>()->setMinimumFanAirFlowRatio(minimumFanAirFlowRatio);
  }

  void RefrigerationAirChiller::resetMinimumFanAirFlowRatio() {
    getImpl<detail::RefrigerationAirChiller_Impl>()->resetMinimumFanAirFlowRatio();
  }

  std::string RefrigerationAirChiller::defrostType() const {
    return getImpl<detail::RefrigerationAirChiller_Impl>()->defrostType();
  }

  bool RefrigerationAirChiller::isDefrostTypeDefaulted() const {
    return getImpl<detail::RefrigerationAirChiller_Impl>()->isDefrostTypeDefaulted();
  }

  bool RefrigerationAirChiller::setDefrostType(const std::string& defrostType) {
    return getImpl<detail::RefrigerationAirChiller_Impl>()->setDefrostType(defrostType);
  }

  void RefrigerationAirChiller::resetDefrostType() {
    getImpl<detail::RefrigerationAirChiller_Impl>()->resetDefrostType();
  }

  std::string RefrigerationAirChiller::defrostControlType() const {
    return getImpl<detail::RefrigerationAirChiller_Impl>()->defrostControlType();
  }

  bool RefrigerationAirChiller::isDefrostControlTypeDefaulted() const {
    return getImpl<detail::RefrigerationAirChiller_Impl>()->isDefrostControlTypeDefaulted();
  }

  bool RefrigerationAirChiller::setDefrostControlType(const std::string& defrostControlType) {
    return getImpl<detail::RefrigerationAirChiller_Impl>()->setDefrostControlType(defrostControlType);
  }

  void RefrigerationAirChiller::resetDefrostControlType() {
    getImpl<detail::RefrigerationAirChiller_Impl>()->resetDefrostControlType();
  }

  boost::optional<double> RefrigerationAirChiller::defrostPower() const {
    return getImpl<detail::RefrigerationAirChiller_Impl>()->defrostPower();
  }

  bool RefrigerationAirChiller::setDefrostPower(double defrostPower) {
    return getImpl<detail::RefrigerationAirChiller_Impl>()->setDefrostPower(defrostPower);
  }

  void RefrigerationAirChiller::resetDefrostPower() {
    getImpl<detail::RefrigerationAirChiller_Impl>()->resetDefrostPower();
  }

  boost::optional<double> RefrigerationAirChiller::temperatureTerminationDefrostFractiontoIce() const {
    return getImpl<detail::RefrigerationAirChiller_Impl>()->temperatureTerminationDefrostFractiontoIce();
  }

  bool RefrigerationAirChiller::setTemperatureTerminationDefrostFractiontoIce(double temperatureTerminationDefrostFractiontoIce) {
    return getImpl<detail::RefrigerationAirChiller_Impl>()->setTemperatureTerminationDefrostFractiontoIce(temperatureTerminationDefrostFractiontoIce);
  }

  void RefrigerationAirChiller::resetTemperatureTerminationDefrostFractiontoIce() {
    getImpl<detail::RefrigerationAirChiller_Impl>()->resetTemperatureTerminationDefrostFractiontoIce();
  }

  std::string RefrigerationAirChiller::verticalLocation() const {
    return getImpl<detail::RefrigerationAirChiller_Impl>()->verticalLocation();
  }

  bool RefrigerationAirChiller::isVerticalLocationDefaulted() const {
    return getImpl<detail::RefrigerationAirChiller_Impl>()->isVerticalLocationDefaulted();
  }

  bool RefrigerationAirChiller::setVerticalLocation(const std::string& verticalLocation) {
    return getImpl<detail::RefrigerationAirChiller_Impl>()->setVerticalLocation(verticalLocation);
  }

  void RefrigerationAirChiller::resetVerticalLocation() {
    getImpl<detail::RefrigerationAirChiller_Impl>()->resetVerticalLocation();
  }

  double RefrigerationAirChiller::averageRefrigerantChargeInventory() const {
    return getImpl<detail::RefrigerationAirChiller_Impl>()->averageRefrigerantChargeInventory();
  }

  bool RefrigerationAirChiller::isAverageRefrigerantChargeInventoryDefaulted() const {
    return getImpl<detail::RefrigerationAirChiller_Impl>()->isAverageRefrigerantChargeInventoryDefaulted();
  }

  bool RefrigerationAirChiller::setAverageRefrigerantChargeInventory(double averageRefrigerantChargeInventory) {
    return getImpl<detail::RefrigerationAirChiller_Impl>()->setAverageRefrigerantChargeInventory(averageRefrigerantChargeInventory);
  }

  void RefrigerationAirChiller::resetAverageRefrigerantChargeInventory() {
    getImpl<detail::RefrigerationAirChiller_Impl>()->resetAverageRefrigerantChargeInventory();
  }

  bool RefrigerationAirChiller::setCapacityRatingType(const std::string& capacityRatingType) {
    return getImpl<detail::RefrigerationAirChiller_Impl>()->setCapacityRatingType(capacityRatingType);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::string RefrigerationAirChiller_Impl::capacityRatingType() const {
      auto value = getString(Refrigeration_AirChillerFields::CapacityRatingType, true);
      OS_ASSERT(value);
      return value.get();
    }

    boost::optional<double> RefrigerationAirChiller_Impl::ratedUnitLoadFactor() const {
      return getDouble(Refrigeration_AirChillerFields::RatedUnitLoadFactor, true);
    }

    bool RefrigerationAirChiller_Impl::setRatedUnitLoadFactor(double ratedUnitLoadFactor) {
      const bool result = setDouble(Refrigeration_AirChillerFields::RatedUnitLoadFactor, ratedUnitLoadFactor);
      OS_ASSERT(result);
      return result;
    }

    void RefrigerationAirChiller_Impl::resetRatedUnitLoadFactor() {
      OS_ASSERT(setString(Refrigeration_AirChillerFields::RatedUnitLoadFactor, ""));
    }

    boost::optional<double> RefrigerationAirChiller_Impl::ratedCapacity() const {
      return getDouble(Refrigeration_AirChillerFields::RatedCapacity, true);
    }

    bool RefrigerationAirChiller_Impl::setRatedCapacity(double ratedCapacity) {
      const bool result = setDouble(Refrigeration_AirChillerFields::RatedCapacity, ratedCapacity);
      OS_ASSERT(result);
      return result;
    }

    void RefrigerationAirChiller_Impl::resetRatedCapacity() {
      OS_ASSERT(setString(Refrigeration_AirChillerFields::RatedCapacity, ""));
    }

    double RefrigerationAirChiller_Impl::ratedRelativeHumidity() const {
      auto value = getDouble(Refrigeration_AirChillerFields::RatedRelativeHumidity, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool RefrigerationAirChiller_Impl::isRatedRelativeHumidityDefaulted() const {
      return isEmpty(Refrigeration_AirChillerFields::RatedRelativeHumidity);
    }

    bool RefrigerationAirChiller_Impl::setRatedRelativeHumidity(double ratedRelativeHumidity) {
      const bool result = setDouble(Refrigeration_AirChillerFields::RatedRelativeHumidity, ratedRelativeHumidity);
      OS_ASSERT(result);
      return result;
    }

    void RefrigerationAirChiller_Impl::resetRatedRelativeHumidity() {
      OS_ASSERT(setString(Refrigeration_AirChillerFields::RatedRelativeHumidity, ""));
    }

    double RefrigerationAirChiller_Impl::ratedCoolingSourceTemperature() const {
      auto value = getDouble(Refrigeration_AirChillerFields::RatedCoolingSourceTemperature, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool RefrigerationAirChiller_Impl::setRatedCoolingSourceTemperature(double ratedCoolingSourceTemperature) {
      const bool result = setDouble(Refrigeration_AirChillerFields::RatedCoolingSourceTemperature, ratedCoolingSourceTemperature);
      OS_ASSERT(result);
      return result;
    }

    double RefrigerationAirChiller_Impl::ratedTemperatureDifferenceDT1() const {
      auto value = getDouble(Refrigeration_AirChillerFields::RatedTemperatureDifferenceDT1, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool RefrigerationAirChiller_Impl::setRatedTemperatureDifferenceDT1(double ratedTemperatureDifferenceDT1) {
      const bool result = setDouble(Refrigeration_AirChillerFields::RatedTemperatureDifferenceDT1, ratedTemperatureDifferenceDT1);
      OS_ASSERT(result);
      return result;
    }

    boost::optional<double> RefrigerationAirChiller_Impl::maximumTemperatureDifferenceBetweenInletAirandEvaporatingTemperature() const {
      return getDouble(Refrigeration_AirChillerFields::MaximumTemperatureDifferenceBetweenInletAirandEvaporatingTemperature, true);
    }

    bool RefrigerationAirChiller_Impl::setMaximumTemperatureDifferenceBetweenInletAirandEvaporatingTemperature(
      double maximumTemperatureDifferenceBetweenInletAirandEvaporatingTemperature) {
      const bool result = setDouble(Refrigeration_AirChillerFields::MaximumTemperatureDifferenceBetweenInletAirandEvaporatingTemperature,
                                    maximumTemperatureDifferenceBetweenInletAirandEvaporatingTemperature);
      OS_ASSERT(result);
      return result;
    }

    void RefrigerationAirChiller_Impl::resetMaximumTemperatureDifferenceBetweenInletAirandEvaporatingTemperature() {
      OS_ASSERT(setString(Refrigeration_AirChillerFields::MaximumTemperatureDifferenceBetweenInletAirandEvaporatingTemperature, ""));
    }

    double RefrigerationAirChiller_Impl::coilMaterialCorrectionFactor() const {
      auto value = getDouble(Refrigeration_AirChillerFields::CoilMaterialCorrectionFactor, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool RefrigerationAirChiller_Impl::isCoilMaterialCorrectionFactorDefaulted() const {
      return isEmpty(Refrigeration_AirChillerFields::CoilMaterialCorrectionFactor);
    }

    bool RefrigerationAirChiller_Impl::setCoilMaterialCorrectionFactor(double coilMaterialCorrectionFactor) {
      const bool result = setDouble(Refrigeration_AirChillerFields::CoilMaterialCorrectionFactor, coilMaterialCorrectionFactor);
      OS_ASSERT(result);
      return result;
    }

    void RefrigerationAirChiller_Impl::resetCoilMaterialCorrectionFactor() {
      OS_ASSERT(setString(Refrigeration_AirChillerFields::CoilMaterialCorrectionFactor, ""));
    }

    double RefrigerationAirChiller_Impl::refrigerantCorrectionFactor() const {
      auto value = getDouble(Refrigeration_AirChillerFields::RefrigerantCorrectionFactor, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool RefrigerationAirChiller_Impl::isRefrigerantCorrectionFactorDefaulted() const {
      return isEmpty(Refrigeration_AirChillerFields::RefrigerantCorrectionFactor);
    }

    bool RefrigerationAirChiller_Impl::setRefrigerantCorrectionFactor(double refrigerantCorrectionFactor) {
      const bool result = setDouble(Refrigeration_AirChillerFields::RefrigerantCorrectionFactor, refrigerantCorrectionFactor);
      OS_ASSERT(result);
      return result;
    }

    void RefrigerationAirChiller_Impl::resetRefrigerantCorrectionFactor() {
      OS_ASSERT(setString(Refrigeration_AirChillerFields::RefrigerantCorrectionFactor, ""));
    }

    std::string RefrigerationAirChiller_Impl::capacityCorrectionCurveType() const {
      auto value = getString(Refrigeration_AirChillerFields::CapacityCorrectionCurveType, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool RefrigerationAirChiller_Impl::isCapacityCorrectionCurveTypeDefaulted() const {
      return isEmpty(Refrigeration_AirChillerFields::CapacityCorrectionCurveType);
    }

    bool RefrigerationAirChiller_Impl::setCapacityCorrectionCurveType(const std::string& capacityCorrectionCurveType) {
      const bool result = setString(Refrigeration_AirChillerFields::CapacityCorrectionCurveType, capacityCorrectionCurveType);
      OS_ASSERT(result);
      return result;
    }

    void RefrigerationAirChiller_Impl::resetCapacityCorrectionCurveType() {
      OS_ASSERT(setString(Refrigeration_AirChillerFields::CapacityCorrectionCurveType, ""));
    }

    double RefrigerationAirChiller_Impl::sHR60CorrectionFactor() const {
      auto value = getDouble(Refrigeration_AirChillerFields::SHR60CorrectionFactor, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool RefrigerationAirChiller_Impl::isSHR60CorrectionFactorDefaulted() const {
      return isEmpty(Refrigeration_AirChillerFields::SHR60CorrectionFactor);
    }

    bool RefrigerationAirChiller_Impl::setSHR60CorrectionFactor(double sHR60CorrectionFactor) {
      const bool result = setDouble(Refrigeration_AirChillerFields::SHR60CorrectionFactor, sHR60CorrectionFactor);
      OS_ASSERT(result);
      return result;
    }

    void RefrigerationAirChiller_Impl::resetSHR60CorrectionFactor() {
      OS_ASSERT(setString(Refrigeration_AirChillerFields::SHR60CorrectionFactor, ""));
    }

    double RefrigerationAirChiller_Impl::ratedTotalHeatingPower() const {
      auto value = getDouble(Refrigeration_AirChillerFields::RatedTotalHeatingPower, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool RefrigerationAirChiller_Impl::setRatedTotalHeatingPower(double ratedTotalHeatingPower) {
      const bool result = setDouble(Refrigeration_AirChillerFields::RatedTotalHeatingPower, ratedTotalHeatingPower);
      OS_ASSERT(result);
      return result;
    }

    std::string RefrigerationAirChiller_Impl::fanSpeedControlType() const {
      auto value = getString(Refrigeration_AirChillerFields::FanSpeedControlType, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool RefrigerationAirChiller_Impl::isFanSpeedControlTypeDefaulted() const {
      return isEmpty(Refrigeration_AirChillerFields::FanSpeedControlType);
    }

    bool RefrigerationAirChiller_Impl::setFanSpeedControlType(const std::string& fanSpeedControlType) {
      const bool result = setString(Refrigeration_AirChillerFields::FanSpeedControlType, fanSpeedControlType);
      OS_ASSERT(result);
      return result;
    }

    void RefrigerationAirChiller_Impl::resetFanSpeedControlType() {
      OS_ASSERT(setString(Refrigeration_AirChillerFields::FanSpeedControlType, ""));
    }

    double RefrigerationAirChiller_Impl::ratedFanPower() const {
      auto value = getDouble(Refrigeration_AirChillerFields::RatedFanPower, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool RefrigerationAirChiller_Impl::isRatedFanPowerDefaulted() const {
      return isEmpty(Refrigeration_AirChillerFields::RatedFanPower);
    }

    bool RefrigerationAirChiller_Impl::setRatedFanPower(double ratedFanPower) {
      const bool result = setDouble(Refrigeration_AirChillerFields::RatedFanPower, ratedFanPower);
      OS_ASSERT(result);
      return result;
    }

    void RefrigerationAirChiller_Impl::resetRatedFanPower() {
      OS_ASSERT(setString(Refrigeration_AirChillerFields::RatedFanPower, ""));
    }

    double RefrigerationAirChiller_Impl::ratedAirFlow() const {
      auto value = getDouble(Refrigeration_AirChillerFields::RatedAirFlow, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool RefrigerationAirChiller_Impl::setRatedAirFlow(double ratedAirFlow) {
      const bool result = setDouble(Refrigeration_AirChillerFields::RatedAirFlow, ratedAirFlow);
      OS_ASSERT(result);
      return result;
    }

    double RefrigerationAirChiller_Impl::minimumFanAirFlowRatio() const {
      auto value = getDouble(Refrigeration_AirChillerFields::MinimumFanAirFlowRatio, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool RefrigerationAirChiller_Impl::isMinimumFanAirFlowRatioDefaulted() const {
      return isEmpty(Refrigeration_AirChillerFields::MinimumFanAirFlowRatio);
    }

    bool RefrigerationAirChiller_Impl::setMinimumFanAirFlowRatio(double minimumFanAirFlowRatio) {
      const bool result = setDouble(Refrigeration_AirChillerFields::MinimumFanAirFlowRatio, minimumFanAirFlowRatio);
      OS_ASSERT(result);
      return result;
    }

    void RefrigerationAirChiller_Impl::resetMinimumFanAirFlowRatio() {
      OS_ASSERT(setString(Refrigeration_AirChillerFields::MinimumFanAirFlowRatio, ""));
    }

    std::string RefrigerationAirChiller_Impl::defrostType() const {
      auto value = getString(Refrigeration_AirChillerFields::DefrostType, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool RefrigerationAirChiller_Impl::isDefrostTypeDefaulted() const {
      return isEmpty(Refrigeration_AirChillerFields::DefrostType);
    }

    bool RefrigerationAirChiller_Impl::setDefrostType(const std::string& defrostType) {
      const bool result = setString(Refrigeration_AirChillerFields::DefrostType, defrostType);
      OS_ASSERT(result);
      return result;
    }

    void RefrigerationAirChiller_Impl::resetDefrostType() {
      OS_ASSERT(setString(Refrigeration_AirChillerFields::DefrostType, ""));
    }

    std::string RefrigerationAirChiller_Impl::defrostControlType() const {
      auto value = getString(Refrigeration_AirChillerFields::DefrostControlType, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool RefrigerationAirChiller_Impl::isDefrostControlTypeDefaulted() const {
      return isEmpty(Refrigeration_AirChillerFields::DefrostControlType);
    }

    bool RefrigerationAirChiller_Impl::setDefrostControlType(const std::string& defrostControlType) {
      const bool result = setString(Refrigeration_AirChillerFields::DefrostControlType, defrostControlType);
      OS_ASSERT(result);
      return result;
    }

    void RefrigerationAirChiller_Impl::resetDefrostControlType() {
      OS_ASSERT(setString(Refrigeration_AirChillerFields::DefrostControlType, ""));
    }

    boost::optional<double> RefrigerationAirChiller_Impl::defrostPower() const {
      return getDouble(Refrigeration_AirChillerFields::DefrostPower, true);
    }

    bool RefrigerationAirChiller_Impl::setDefrostPower(double defrostPower) {
      const bool result = setDouble(Refrigeration_AirChillerFields::DefrostPower, defrostPower);
      OS_ASSERT(result);
      return result;
    }

    void RefrigerationAirChiller_Impl::resetDefrostPower() {
      OS_ASSERT(setString(Refrigeration_AirChillerFields::DefrostPower, ""));
    }

    boost::optional<double> RefrigerationAirChiller_Impl::temperatureTerminationDefrostFractiontoIce() const {
      return getDouble(Refrigeration_AirChillerFields::TemperatureTerminationDefrostFractiontoIce, true);
    }

    bool RefrigerationAirChiller_Impl::setTemperatureTerminationDefrostFractiontoIce(double temperatureTerminationDefrostFractiontoIce) {
      const bool result =
        setDouble(Refrigeration_AirChillerFields::TemperatureTerminationDefrostFractiontoIce, temperatureTerminationDefrostFractiontoIce);
      OS_ASSERT(result);
      return result;
    }

    void RefrigerationAirChiller_Impl::resetTemperatureTerminationDefrostFractiontoIce() {
      OS_ASSERT(setString(Refrigeration_AirChillerFields::TemperatureTerminationDefrostFractiontoIce, ""));
    }

    std::string RefrigerationAirChiller_Impl::verticalLocation() const {
      auto value = getString(Refrigeration_AirChillerFields::VerticalLocation, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool RefrigerationAirChiller_Impl::isVerticalLocationDefaulted() const {
      return isEmpty(Refrigeration_AirChillerFields::VerticalLocation);
    }

    bool RefrigerationAirChiller_Impl::setVerticalLocation(const std::string& verticalLocation) {
      const bool result = setString(Refrigeration_AirChillerFields::VerticalLocation, verticalLocation);
      OS_ASSERT(result);
      return result;
    }

    void RefrigerationAirChiller_Impl::resetVerticalLocation() {
      OS_ASSERT(setString(Refrigeration_AirChillerFields::VerticalLocation, ""));
    }

    double RefrigerationAirChiller_Impl::averageRefrigerantChargeInventory() const {
      auto value = getDouble(Refrigeration_AirChillerFields::AverageRefrigerantChargeInventory, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool RefrigerationAirChiller_Impl::isAverageRefrigerantChargeInventoryDefaulted() const {
      return isEmpty(Refrigeration_AirChillerFields::AverageRefrigerantChargeInventory);
    }

    bool RefrigerationAirChiller_Impl::setAverageRefrigerantChargeInventory(double averageRefrigerantChargeInventory) {
      const bool result = setDouble(Refrigeration_AirChillerFields::AverageRefrigerantChargeInventory, averageRefrigerantChargeInventory);
      OS_ASSERT(result);
      return result;
    }

    void RefrigerationAirChiller_Impl::resetAverageRefrigerantChargeInventory() {
      OS_ASSERT(setString(Refrigeration_AirChillerFields::AverageRefrigerantChargeInventory, ""));
    }

    bool RefrigerationAirChiller_Impl::setCapacityRatingType(const std::string& capacityRatingType) {
      const bool result = setString(Refrigeration_AirChillerFields::CapacityRatingType, capacityRatingType);
      OS_ASSERT(result);
      return result;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
