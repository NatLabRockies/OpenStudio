/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ParentObject/RefrigerationGasCoolerAirCooled.hpp"
#include "ParentObject/RefrigerationGasCoolerAirCooled_Impl.hpp"

#include "Model.hpp"

#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/Refrigeration_GasCooler_AirCooled_FieldEnums.hxx>
#include <utilities/core/Assert.hpp>

#include <boost/optional.hpp>

namespace openstudio {
namespace epmodel {

  namespace detail {

    std::string RefrigerationGasCoolerAirCooled_Impl::gasCoolerFanSpeedControlType() const {
      boost::optional<std::string> value = getString(Refrigeration_GasCooler_AirCooledFields::GasCoolerFanSpeedControlType, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool RefrigerationGasCoolerAirCooled_Impl::isGasCoolerFanSpeedControlTypeDefaulted() const {
      return isEmpty(Refrigeration_GasCooler_AirCooledFields::GasCoolerFanSpeedControlType);
    }

    bool RefrigerationGasCoolerAirCooled_Impl::setGasCoolerFanSpeedControlType(const std::string& gasCoolerFanSpeedControlType) {
      const bool result = setString(Refrigeration_GasCooler_AirCooledFields::GasCoolerFanSpeedControlType, gasCoolerFanSpeedControlType);
      OS_ASSERT(result);
      return result;
    }

    void RefrigerationGasCoolerAirCooled_Impl::resetGasCoolerFanSpeedControlType() {
      const bool result = setString(Refrigeration_GasCooler_AirCooledFields::GasCoolerFanSpeedControlType, "");
      OS_ASSERT(result);
    }

    double RefrigerationGasCoolerAirCooled_Impl::ratedFanPower() const {
      boost::optional<double> value = getDouble(Refrigeration_GasCooler_AirCooledFields::RatedFanPower, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool RefrigerationGasCoolerAirCooled_Impl::isRatedFanPowerDefaulted() const {
      return isEmpty(Refrigeration_GasCooler_AirCooledFields::RatedFanPower);
    }

    bool RefrigerationGasCoolerAirCooled_Impl::setRatedFanPower(double ratedFanPower) {
      return setDouble(Refrigeration_GasCooler_AirCooledFields::RatedFanPower, ratedFanPower);
    }

    void RefrigerationGasCoolerAirCooled_Impl::resetRatedFanPower() {
      const bool result = setString(Refrigeration_GasCooler_AirCooledFields::RatedFanPower, "");
      OS_ASSERT(result);
    }

    double RefrigerationGasCoolerAirCooled_Impl::minimumFanAirFlowRatio() const {
      boost::optional<double> value = getDouble(Refrigeration_GasCooler_AirCooledFields::MinimumFanAirFlowRatio, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool RefrigerationGasCoolerAirCooled_Impl::isMinimumFanAirFlowRatioDefaulted() const {
      return isEmpty(Refrigeration_GasCooler_AirCooledFields::MinimumFanAirFlowRatio);
    }

    bool RefrigerationGasCoolerAirCooled_Impl::setMinimumFanAirFlowRatio(double minimumFanAirFlowRatio) {
      return setDouble(Refrigeration_GasCooler_AirCooledFields::MinimumFanAirFlowRatio, minimumFanAirFlowRatio);
    }

    void RefrigerationGasCoolerAirCooled_Impl::resetMinimumFanAirFlowRatio() {
      const bool result = setString(Refrigeration_GasCooler_AirCooledFields::MinimumFanAirFlowRatio, "");
      OS_ASSERT(result);
    }

    double RefrigerationGasCoolerAirCooled_Impl::transitionTemperature() const {
      boost::optional<double> value = getDouble(Refrigeration_GasCooler_AirCooledFields::TransitionTemperature, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool RefrigerationGasCoolerAirCooled_Impl::isTransitionTemperatureDefaulted() const {
      return isEmpty(Refrigeration_GasCooler_AirCooledFields::TransitionTemperature);
    }

    bool RefrigerationGasCoolerAirCooled_Impl::setTransitionTemperature(double transitionTemperature) {
      const bool result = setDouble(Refrigeration_GasCooler_AirCooledFields::TransitionTemperature, transitionTemperature);
      OS_ASSERT(result);
      return result;
    }

    void RefrigerationGasCoolerAirCooled_Impl::resetTransitionTemperature() {
      const bool result = setString(Refrigeration_GasCooler_AirCooledFields::TransitionTemperature, "");
      OS_ASSERT(result);
    }

    double RefrigerationGasCoolerAirCooled_Impl::transcriticalApproachTemperature() const {
      boost::optional<double> value = getDouble(Refrigeration_GasCooler_AirCooledFields::TranscriticalApproachTemperature, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool RefrigerationGasCoolerAirCooled_Impl::isTranscriticalApproachTemperatureDefaulted() const {
      return isEmpty(Refrigeration_GasCooler_AirCooledFields::TranscriticalApproachTemperature);
    }

    bool RefrigerationGasCoolerAirCooled_Impl::setTranscriticalApproachTemperature(double transcriticalApproachTemperature) {
      const bool result = setDouble(Refrigeration_GasCooler_AirCooledFields::TranscriticalApproachTemperature, transcriticalApproachTemperature);
      OS_ASSERT(result);
      return result;
    }

    void RefrigerationGasCoolerAirCooled_Impl::resetTranscriticalApproachTemperature() {
      const bool result = setString(Refrigeration_GasCooler_AirCooledFields::TranscriticalApproachTemperature, "");
      OS_ASSERT(result);
    }

    double RefrigerationGasCoolerAirCooled_Impl::subcriticalTemperatureDifference() const {
      boost::optional<double> value = getDouble(Refrigeration_GasCooler_AirCooledFields::SubcriticalTemperatureDifference, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool RefrigerationGasCoolerAirCooled_Impl::isSubcriticalTemperatureDifferenceDefaulted() const {
      return isEmpty(Refrigeration_GasCooler_AirCooledFields::SubcriticalTemperatureDifference);
    }

    bool RefrigerationGasCoolerAirCooled_Impl::setSubcriticalTemperatureDifference(double subcriticalTemperatureDifference) {
      const bool result = setDouble(Refrigeration_GasCooler_AirCooledFields::SubcriticalTemperatureDifference, subcriticalTemperatureDifference);
      OS_ASSERT(result);
      return result;
    }

    void RefrigerationGasCoolerAirCooled_Impl::resetSubcriticalTemperatureDifference() {
      const bool result = setString(Refrigeration_GasCooler_AirCooledFields::SubcriticalTemperatureDifference, "");
      OS_ASSERT(result);
    }

    double RefrigerationGasCoolerAirCooled_Impl::minimumCondensingTemperature() const {
      boost::optional<double> value = getDouble(Refrigeration_GasCooler_AirCooledFields::MinimumCondensingTemperature, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool RefrigerationGasCoolerAirCooled_Impl::isMinimumCondensingTemperatureDefaulted() const {
      return isEmpty(Refrigeration_GasCooler_AirCooledFields::MinimumCondensingTemperature);
    }

    bool RefrigerationGasCoolerAirCooled_Impl::setMinimumCondensingTemperature(double minimumCondensingTemperature) {
      const bool result = setDouble(Refrigeration_GasCooler_AirCooledFields::MinimumCondensingTemperature, minimumCondensingTemperature);
      OS_ASSERT(result);
      return result;
    }

    void RefrigerationGasCoolerAirCooled_Impl::resetMinimumCondensingTemperature() {
      const bool result = setString(Refrigeration_GasCooler_AirCooledFields::MinimumCondensingTemperature, "");
      OS_ASSERT(result);
    }

    std::string RefrigerationGasCoolerAirCooled_Impl::endUseSubcategory() const {
      boost::optional<std::string> value = getString(Refrigeration_GasCooler_AirCooledFields::EndUseSubcategory, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool RefrigerationGasCoolerAirCooled_Impl::isEndUseSubcategoryDefaulted() const {
      return isEmpty(Refrigeration_GasCooler_AirCooledFields::EndUseSubcategory);
    }

    bool RefrigerationGasCoolerAirCooled_Impl::setEndUseSubcategory(const std::string& endUseSubcategory) {
      const bool result = setString(Refrigeration_GasCooler_AirCooledFields::EndUseSubcategory, endUseSubcategory);
      OS_ASSERT(result);
      return result;
    }

    void RefrigerationGasCoolerAirCooled_Impl::resetEndUseSubcategory() {
      const bool result = setString(Refrigeration_GasCooler_AirCooledFields::EndUseSubcategory, "");
      OS_ASSERT(result);
    }

    double RefrigerationGasCoolerAirCooled_Impl::gasCoolerRefrigerantOperatingChargeInventory() const {
      boost::optional<double> value = getDouble(Refrigeration_GasCooler_AirCooledFields::GasCoolerRefrigerantOperatingChargeInventory, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool RefrigerationGasCoolerAirCooled_Impl::isGasCoolerRefrigerantOperatingChargeInventoryDefaulted() const {
      return isEmpty(Refrigeration_GasCooler_AirCooledFields::GasCoolerRefrigerantOperatingChargeInventory);
    }

    bool RefrigerationGasCoolerAirCooled_Impl::setGasCoolerRefrigerantOperatingChargeInventory(double gasCoolerRefrigerantOperatingChargeInventory) {
      const bool result = setDouble(Refrigeration_GasCooler_AirCooledFields::GasCoolerRefrigerantOperatingChargeInventory,
                                    gasCoolerRefrigerantOperatingChargeInventory);
      OS_ASSERT(result);
      return result;
    }

    void RefrigerationGasCoolerAirCooled_Impl::resetGasCoolerRefrigerantOperatingChargeInventory() {
      const bool result = setString(Refrigeration_GasCooler_AirCooledFields::GasCoolerRefrigerantOperatingChargeInventory, "");
      OS_ASSERT(result);
    }

    double RefrigerationGasCoolerAirCooled_Impl::gasCoolerReceiverRefrigerantInventory() const {
      boost::optional<double> value = getDouble(Refrigeration_GasCooler_AirCooledFields::GasCoolerReceiverRefrigerantInventory, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool RefrigerationGasCoolerAirCooled_Impl::isGasCoolerReceiverRefrigerantInventoryDefaulted() const {
      return isEmpty(Refrigeration_GasCooler_AirCooledFields::GasCoolerReceiverRefrigerantInventory);
    }

    bool RefrigerationGasCoolerAirCooled_Impl::setGasCoolerReceiverRefrigerantInventory(double gasCoolerReceiverRefrigerantInventory) {
      const bool result =
        setDouble(Refrigeration_GasCooler_AirCooledFields::GasCoolerReceiverRefrigerantInventory, gasCoolerReceiverRefrigerantInventory);
      OS_ASSERT(result);
      return result;
    }

    void RefrigerationGasCoolerAirCooled_Impl::resetGasCoolerReceiverRefrigerantInventory() {
      const bool result = setString(Refrigeration_GasCooler_AirCooledFields::GasCoolerReceiverRefrigerantInventory, "");
      OS_ASSERT(result);
    }

    double RefrigerationGasCoolerAirCooled_Impl::gasCoolerOutletPipingRefrigerantInventory() const {
      boost::optional<double> value = getDouble(Refrigeration_GasCooler_AirCooledFields::GasCoolerOutletPipingRefrigerantInventory, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool RefrigerationGasCoolerAirCooled_Impl::isGasCoolerOutletPipingRefrigerantInventoryDefaulted() const {
      return isEmpty(Refrigeration_GasCooler_AirCooledFields::GasCoolerOutletPipingRefrigerantInventory);
    }

    bool RefrigerationGasCoolerAirCooled_Impl::setGasCoolerOutletPipingRefrigerantInventory(double gasCoolerOutletPipingRefrigerantInventory) {
      const bool result =
        setDouble(Refrigeration_GasCooler_AirCooledFields::GasCoolerOutletPipingRefrigerantInventory, gasCoolerOutletPipingRefrigerantInventory);
      OS_ASSERT(result);
      return result;
    }

    void RefrigerationGasCoolerAirCooled_Impl::resetGasCoolerOutletPipingRefrigerantInventory() {
      const bool result = setString(Refrigeration_GasCooler_AirCooledFields::GasCoolerOutletPipingRefrigerantInventory, "");
      OS_ASSERT(result);
    }

  }  // namespace detail

  RefrigerationGasCoolerAirCooled::RefrigerationGasCoolerAirCooled(const Model& model)
    : ParentObject(RefrigerationGasCoolerAirCooled::iddObjectType(), model) {}

  RefrigerationGasCoolerAirCooled::RefrigerationGasCoolerAirCooled(std::shared_ptr<detail::RefrigerationGasCoolerAirCooled_Impl> impl)
    : ParentObject(std::move(impl)) {}

  IddObjectType RefrigerationGasCoolerAirCooled::iddObjectType() {
    return IddObjectType::Refrigeration_GasCooler_AirCooled;
  }

  std::vector<std::string> RefrigerationGasCoolerAirCooled::gasCoolerFanSpeedControlTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          Refrigeration_GasCooler_AirCooledFields::GasCoolerFanSpeedControlType);
  }

  std::string RefrigerationGasCoolerAirCooled::gasCoolerFanSpeedControlType() const {
    return getImpl<detail::RefrigerationGasCoolerAirCooled_Impl>()->gasCoolerFanSpeedControlType();
  }

  bool RefrigerationGasCoolerAirCooled::isGasCoolerFanSpeedControlTypeDefaulted() const {
    return getImpl<detail::RefrigerationGasCoolerAirCooled_Impl>()->isGasCoolerFanSpeedControlTypeDefaulted();
  }

  bool RefrigerationGasCoolerAirCooled::setGasCoolerFanSpeedControlType(const std::string& gasCoolerFanSpeedControlType) {
    return getImpl<detail::RefrigerationGasCoolerAirCooled_Impl>()->setGasCoolerFanSpeedControlType(gasCoolerFanSpeedControlType);
  }

  void RefrigerationGasCoolerAirCooled::resetGasCoolerFanSpeedControlType() {
    getImpl<detail::RefrigerationGasCoolerAirCooled_Impl>()->resetGasCoolerFanSpeedControlType();
  }

  double RefrigerationGasCoolerAirCooled::ratedFanPower() const {
    return getImpl<detail::RefrigerationGasCoolerAirCooled_Impl>()->ratedFanPower();
  }

  bool RefrigerationGasCoolerAirCooled::isRatedFanPowerDefaulted() const {
    return getImpl<detail::RefrigerationGasCoolerAirCooled_Impl>()->isRatedFanPowerDefaulted();
  }

  bool RefrigerationGasCoolerAirCooled::setRatedFanPower(double ratedFanPower) {
    return getImpl<detail::RefrigerationGasCoolerAirCooled_Impl>()->setRatedFanPower(ratedFanPower);
  }

  void RefrigerationGasCoolerAirCooled::resetRatedFanPower() {
    getImpl<detail::RefrigerationGasCoolerAirCooled_Impl>()->resetRatedFanPower();
  }

  double RefrigerationGasCoolerAirCooled::minimumFanAirFlowRatio() const {
    return getImpl<detail::RefrigerationGasCoolerAirCooled_Impl>()->minimumFanAirFlowRatio();
  }

  bool RefrigerationGasCoolerAirCooled::isMinimumFanAirFlowRatioDefaulted() const {
    return getImpl<detail::RefrigerationGasCoolerAirCooled_Impl>()->isMinimumFanAirFlowRatioDefaulted();
  }

  bool RefrigerationGasCoolerAirCooled::setMinimumFanAirFlowRatio(double minimumFanAirFlowRatio) {
    return getImpl<detail::RefrigerationGasCoolerAirCooled_Impl>()->setMinimumFanAirFlowRatio(minimumFanAirFlowRatio);
  }

  void RefrigerationGasCoolerAirCooled::resetMinimumFanAirFlowRatio() {
    getImpl<detail::RefrigerationGasCoolerAirCooled_Impl>()->resetMinimumFanAirFlowRatio();
  }

  double RefrigerationGasCoolerAirCooled::transitionTemperature() const {
    return getImpl<detail::RefrigerationGasCoolerAirCooled_Impl>()->transitionTemperature();
  }

  bool RefrigerationGasCoolerAirCooled::isTransitionTemperatureDefaulted() const {
    return getImpl<detail::RefrigerationGasCoolerAirCooled_Impl>()->isTransitionTemperatureDefaulted();
  }

  bool RefrigerationGasCoolerAirCooled::setTransitionTemperature(double transitionTemperature) {
    return getImpl<detail::RefrigerationGasCoolerAirCooled_Impl>()->setTransitionTemperature(transitionTemperature);
  }

  void RefrigerationGasCoolerAirCooled::resetTransitionTemperature() {
    getImpl<detail::RefrigerationGasCoolerAirCooled_Impl>()->resetTransitionTemperature();
  }

  double RefrigerationGasCoolerAirCooled::transcriticalApproachTemperature() const {
    return getImpl<detail::RefrigerationGasCoolerAirCooled_Impl>()->transcriticalApproachTemperature();
  }

  bool RefrigerationGasCoolerAirCooled::isTranscriticalApproachTemperatureDefaulted() const {
    return getImpl<detail::RefrigerationGasCoolerAirCooled_Impl>()->isTranscriticalApproachTemperatureDefaulted();
  }

  bool RefrigerationGasCoolerAirCooled::setTranscriticalApproachTemperature(double transcriticalApproachTemperature) {
    return getImpl<detail::RefrigerationGasCoolerAirCooled_Impl>()->setTranscriticalApproachTemperature(transcriticalApproachTemperature);
  }

  void RefrigerationGasCoolerAirCooled::resetTranscriticalApproachTemperature() {
    getImpl<detail::RefrigerationGasCoolerAirCooled_Impl>()->resetTranscriticalApproachTemperature();
  }

  double RefrigerationGasCoolerAirCooled::subcriticalTemperatureDifference() const {
    return getImpl<detail::RefrigerationGasCoolerAirCooled_Impl>()->subcriticalTemperatureDifference();
  }

  bool RefrigerationGasCoolerAirCooled::isSubcriticalTemperatureDifferenceDefaulted() const {
    return getImpl<detail::RefrigerationGasCoolerAirCooled_Impl>()->isSubcriticalTemperatureDifferenceDefaulted();
  }

  bool RefrigerationGasCoolerAirCooled::setSubcriticalTemperatureDifference(double subcriticalTemperatureDifference) {
    return getImpl<detail::RefrigerationGasCoolerAirCooled_Impl>()->setSubcriticalTemperatureDifference(subcriticalTemperatureDifference);
  }

  void RefrigerationGasCoolerAirCooled::resetSubcriticalTemperatureDifference() {
    getImpl<detail::RefrigerationGasCoolerAirCooled_Impl>()->resetSubcriticalTemperatureDifference();
  }

  double RefrigerationGasCoolerAirCooled::minimumCondensingTemperature() const {
    return getImpl<detail::RefrigerationGasCoolerAirCooled_Impl>()->minimumCondensingTemperature();
  }

  bool RefrigerationGasCoolerAirCooled::isMinimumCondensingTemperatureDefaulted() const {
    return getImpl<detail::RefrigerationGasCoolerAirCooled_Impl>()->isMinimumCondensingTemperatureDefaulted();
  }

  bool RefrigerationGasCoolerAirCooled::setMinimumCondensingTemperature(double minimumCondensingTemperature) {
    return getImpl<detail::RefrigerationGasCoolerAirCooled_Impl>()->setMinimumCondensingTemperature(minimumCondensingTemperature);
  }

  void RefrigerationGasCoolerAirCooled::resetMinimumCondensingTemperature() {
    getImpl<detail::RefrigerationGasCoolerAirCooled_Impl>()->resetMinimumCondensingTemperature();
  }

  std::string RefrigerationGasCoolerAirCooled::endUseSubcategory() const {
    return getImpl<detail::RefrigerationGasCoolerAirCooled_Impl>()->endUseSubcategory();
  }

  bool RefrigerationGasCoolerAirCooled::isEndUseSubcategoryDefaulted() const {
    return getImpl<detail::RefrigerationGasCoolerAirCooled_Impl>()->isEndUseSubcategoryDefaulted();
  }

  bool RefrigerationGasCoolerAirCooled::setEndUseSubcategory(const std::string& endUseSubcategory) {
    return getImpl<detail::RefrigerationGasCoolerAirCooled_Impl>()->setEndUseSubcategory(endUseSubcategory);
  }

  void RefrigerationGasCoolerAirCooled::resetEndUseSubcategory() {
    getImpl<detail::RefrigerationGasCoolerAirCooled_Impl>()->resetEndUseSubcategory();
  }

  double RefrigerationGasCoolerAirCooled::gasCoolerRefrigerantOperatingChargeInventory() const {
    return getImpl<detail::RefrigerationGasCoolerAirCooled_Impl>()->gasCoolerRefrigerantOperatingChargeInventory();
  }

  bool RefrigerationGasCoolerAirCooled::isGasCoolerRefrigerantOperatingChargeInventoryDefaulted() const {
    return getImpl<detail::RefrigerationGasCoolerAirCooled_Impl>()->isGasCoolerRefrigerantOperatingChargeInventoryDefaulted();
  }

  bool RefrigerationGasCoolerAirCooled::setGasCoolerRefrigerantOperatingChargeInventory(double gasCoolerRefrigerantOperatingChargeInventory) {
    return getImpl<detail::RefrigerationGasCoolerAirCooled_Impl>()->setGasCoolerRefrigerantOperatingChargeInventory(
      gasCoolerRefrigerantOperatingChargeInventory);
  }

  void RefrigerationGasCoolerAirCooled::resetGasCoolerRefrigerantOperatingChargeInventory() {
    getImpl<detail::RefrigerationGasCoolerAirCooled_Impl>()->resetGasCoolerRefrigerantOperatingChargeInventory();
  }

  double RefrigerationGasCoolerAirCooled::gasCoolerReceiverRefrigerantInventory() const {
    return getImpl<detail::RefrigerationGasCoolerAirCooled_Impl>()->gasCoolerReceiverRefrigerantInventory();
  }

  bool RefrigerationGasCoolerAirCooled::isGasCoolerReceiverRefrigerantInventoryDefaulted() const {
    return getImpl<detail::RefrigerationGasCoolerAirCooled_Impl>()->isGasCoolerReceiverRefrigerantInventoryDefaulted();
  }

  bool RefrigerationGasCoolerAirCooled::setGasCoolerReceiverRefrigerantInventory(double gasCoolerReceiverRefrigerantInventory) {
    return getImpl<detail::RefrigerationGasCoolerAirCooled_Impl>()->setGasCoolerReceiverRefrigerantInventory(gasCoolerReceiverRefrigerantInventory);
  }

  void RefrigerationGasCoolerAirCooled::resetGasCoolerReceiverRefrigerantInventory() {
    getImpl<detail::RefrigerationGasCoolerAirCooled_Impl>()->resetGasCoolerReceiverRefrigerantInventory();
  }

  double RefrigerationGasCoolerAirCooled::gasCoolerOutletPipingRefrigerantInventory() const {
    return getImpl<detail::RefrigerationGasCoolerAirCooled_Impl>()->gasCoolerOutletPipingRefrigerantInventory();
  }

  bool RefrigerationGasCoolerAirCooled::isGasCoolerOutletPipingRefrigerantInventoryDefaulted() const {
    return getImpl<detail::RefrigerationGasCoolerAirCooled_Impl>()->isGasCoolerOutletPipingRefrigerantInventoryDefaulted();
  }

  bool RefrigerationGasCoolerAirCooled::setGasCoolerOutletPipingRefrigerantInventory(double gasCoolerOutletPipingRefrigerantInventory) {
    return getImpl<detail::RefrigerationGasCoolerAirCooled_Impl>()->setGasCoolerOutletPipingRefrigerantInventory(
      gasCoolerOutletPipingRefrigerantInventory);
  }

  void RefrigerationGasCoolerAirCooled::resetGasCoolerOutletPipingRefrigerantInventory() {
    getImpl<detail::RefrigerationGasCoolerAirCooled_Impl>()->resetGasCoolerOutletPipingRefrigerantInventory();
  }

}  // namespace epmodel
}  // namespace openstudio
