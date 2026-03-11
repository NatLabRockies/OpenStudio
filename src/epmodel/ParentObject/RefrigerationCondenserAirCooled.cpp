/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ParentObject/RefrigerationCondenserAirCooled.hpp"
#include "ParentObject/RefrigerationCondenserAirCooled_Impl.hpp"

#include "Model.hpp"

#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/Refrigeration_Condenser_AirCooled_FieldEnums.hxx>
#include <utilities/core/Assert.hpp>

#include <boost/optional.hpp>

namespace openstudio {
namespace epmodel {

  namespace detail {

    double RefrigerationCondenserAirCooled_Impl::ratedSubcoolingTemperatureDifference() const {
      boost::optional<double> value = getDouble(Refrigeration_Condenser_AirCooledFields::RatedSubcoolingTemperatureDifference, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool RefrigerationCondenserAirCooled_Impl::isRatedSubcoolingTemperatureDifferenceDefaulted() const {
      return isEmpty(Refrigeration_Condenser_AirCooledFields::RatedSubcoolingTemperatureDifference);
    }

    bool RefrigerationCondenserAirCooled_Impl::setRatedSubcoolingTemperatureDifference(double ratedSubcoolingTemperatureDifference) {
      return setDouble(Refrigeration_Condenser_AirCooledFields::RatedSubcoolingTemperatureDifference, ratedSubcoolingTemperatureDifference);
    }

    void RefrigerationCondenserAirCooled_Impl::resetRatedSubcoolingTemperatureDifference() {
      const bool result = setString(Refrigeration_Condenser_AirCooledFields::RatedSubcoolingTemperatureDifference, "");
      OS_ASSERT(result);
    }

    std::string RefrigerationCondenserAirCooled_Impl::condenserFanSpeedControlType() const {
      boost::optional<std::string> value = getString(Refrigeration_Condenser_AirCooledFields::CondenserFanSpeedControlType, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool RefrigerationCondenserAirCooled_Impl::isCondenserFanSpeedControlTypeDefaulted() const {
      return isEmpty(Refrigeration_Condenser_AirCooledFields::CondenserFanSpeedControlType);
    }

    bool RefrigerationCondenserAirCooled_Impl::setCondenserFanSpeedControlType(const std::string& condenserFanSpeedControlType) {
      return setString(Refrigeration_Condenser_AirCooledFields::CondenserFanSpeedControlType, condenserFanSpeedControlType);
    }

    void RefrigerationCondenserAirCooled_Impl::resetCondenserFanSpeedControlType() {
      const bool result = setString(Refrigeration_Condenser_AirCooledFields::CondenserFanSpeedControlType, "");
      OS_ASSERT(result);
    }

    double RefrigerationCondenserAirCooled_Impl::ratedFanPower() const {
      boost::optional<double> value = getDouble(Refrigeration_Condenser_AirCooledFields::RatedFanPower, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool RefrigerationCondenserAirCooled_Impl::isRatedFanPowerDefaulted() const {
      return isEmpty(Refrigeration_Condenser_AirCooledFields::RatedFanPower);
    }

    bool RefrigerationCondenserAirCooled_Impl::setRatedFanPower(double ratedFanPower) {
      return setDouble(Refrigeration_Condenser_AirCooledFields::RatedFanPower, ratedFanPower);
    }

    void RefrigerationCondenserAirCooled_Impl::resetRatedFanPower() {
      const bool result = setString(Refrigeration_Condenser_AirCooledFields::RatedFanPower, "");
      OS_ASSERT(result);
    }

    double RefrigerationCondenserAirCooled_Impl::minimumFanAirFlowRatio() const {
      boost::optional<double> value = getDouble(Refrigeration_Condenser_AirCooledFields::MinimumFanAirFlowRatio, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool RefrigerationCondenserAirCooled_Impl::isMinimumFanAirFlowRatioDefaulted() const {
      return isEmpty(Refrigeration_Condenser_AirCooledFields::MinimumFanAirFlowRatio);
    }

    bool RefrigerationCondenserAirCooled_Impl::setMinimumFanAirFlowRatio(double minimumFanAirFlowRatio) {
      return setDouble(Refrigeration_Condenser_AirCooledFields::MinimumFanAirFlowRatio, minimumFanAirFlowRatio);
    }

    void RefrigerationCondenserAirCooled_Impl::resetMinimumFanAirFlowRatio() {
      const bool result = setString(Refrigeration_Condenser_AirCooledFields::MinimumFanAirFlowRatio, "");
      OS_ASSERT(result);
    }

    std::string RefrigerationCondenserAirCooled_Impl::endUseSubcategory() const {
      boost::optional<std::string> value = getString(Refrigeration_Condenser_AirCooledFields::EndUseSubcategory, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool RefrigerationCondenserAirCooled_Impl::isEndUseSubcategoryDefaulted() const {
      return isEmpty(Refrigeration_Condenser_AirCooledFields::EndUseSubcategory);
    }

    bool RefrigerationCondenserAirCooled_Impl::setEndUseSubcategory(const std::string& endUseSubcategory) {
      const bool result = setString(Refrigeration_Condenser_AirCooledFields::EndUseSubcategory, endUseSubcategory);
      OS_ASSERT(result);
      return result;
    }

    void RefrigerationCondenserAirCooled_Impl::resetEndUseSubcategory() {
      const bool result = setString(Refrigeration_Condenser_AirCooledFields::EndUseSubcategory, "");
      OS_ASSERT(result);
    }

    double RefrigerationCondenserAirCooled_Impl::condenserRefrigerantOperatingChargeInventory() const {
      boost::optional<double> value = getDouble(Refrigeration_Condenser_AirCooledFields::CondenserRefrigerantOperatingChargeInventory, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool RefrigerationCondenserAirCooled_Impl::isCondenserRefrigerantOperatingChargeInventoryDefaulted() const {
      return isEmpty(Refrigeration_Condenser_AirCooledFields::CondenserRefrigerantOperatingChargeInventory);
    }

    bool RefrigerationCondenserAirCooled_Impl::setCondenserRefrigerantOperatingChargeInventory(double condenserRefrigerantOperatingChargeInventory) {
      return setDouble(Refrigeration_Condenser_AirCooledFields::CondenserRefrigerantOperatingChargeInventory,
                       condenserRefrigerantOperatingChargeInventory);
    }

    void RefrigerationCondenserAirCooled_Impl::resetCondenserRefrigerantOperatingChargeInventory() {
      const bool result = setString(Refrigeration_Condenser_AirCooledFields::CondenserRefrigerantOperatingChargeInventory, "");
      OS_ASSERT(result);
    }

    double RefrigerationCondenserAirCooled_Impl::condensateReceiverRefrigerantInventory() const {
      boost::optional<double> value = getDouble(Refrigeration_Condenser_AirCooledFields::CondensateReceiverRefrigerantInventory, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool RefrigerationCondenserAirCooled_Impl::isCondensateReceiverRefrigerantInventoryDefaulted() const {
      return isEmpty(Refrigeration_Condenser_AirCooledFields::CondensateReceiverRefrigerantInventory);
    }

    bool RefrigerationCondenserAirCooled_Impl::setCondensateReceiverRefrigerantInventory(double condensateReceiverRefrigerantInventory) {
      return setDouble(Refrigeration_Condenser_AirCooledFields::CondensateReceiverRefrigerantInventory, condensateReceiverRefrigerantInventory);
    }

    void RefrigerationCondenserAirCooled_Impl::resetCondensateReceiverRefrigerantInventory() {
      const bool result = setString(Refrigeration_Condenser_AirCooledFields::CondensateReceiverRefrigerantInventory, "");
      OS_ASSERT(result);
    }

    double RefrigerationCondenserAirCooled_Impl::condensatePipingRefrigerantInventory() const {
      boost::optional<double> value = getDouble(Refrigeration_Condenser_AirCooledFields::CondensatePipingRefrigerantInventory, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool RefrigerationCondenserAirCooled_Impl::isCondensatePipingRefrigerantInventoryDefaulted() const {
      return isEmpty(Refrigeration_Condenser_AirCooledFields::CondensatePipingRefrigerantInventory);
    }

    bool RefrigerationCondenserAirCooled_Impl::setCondensatePipingRefrigerantInventory(double condensatePipingRefrigerantInventory) {
      return setDouble(Refrigeration_Condenser_AirCooledFields::CondensatePipingRefrigerantInventory, condensatePipingRefrigerantInventory);
    }

    void RefrigerationCondenserAirCooled_Impl::resetCondensatePipingRefrigerantInventory() {
      const bool result = setString(Refrigeration_Condenser_AirCooledFields::CondensatePipingRefrigerantInventory, "");
      OS_ASSERT(result);
    }

  }  // namespace detail

  RefrigerationCondenserAirCooled::RefrigerationCondenserAirCooled(const Model& model)
    : ParentObject(RefrigerationCondenserAirCooled::iddObjectType(), model) {}

  RefrigerationCondenserAirCooled::RefrigerationCondenserAirCooled(std::shared_ptr<detail::RefrigerationCondenserAirCooled_Impl> impl)
    : ParentObject(std::move(impl)) {}

  IddObjectType RefrigerationCondenserAirCooled::iddObjectType() {
    return IddObjectType::Refrigeration_Condenser_AirCooled;
  }

  std::vector<std::string> RefrigerationCondenserAirCooled::condenserFanSpeedControlTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          Refrigeration_Condenser_AirCooledFields::CondenserFanSpeedControlType);
  }

  double RefrigerationCondenserAirCooled::ratedSubcoolingTemperatureDifference() const {
    return getImpl<detail::RefrigerationCondenserAirCooled_Impl>()->ratedSubcoolingTemperatureDifference();
  }

  bool RefrigerationCondenserAirCooled::isRatedSubcoolingTemperatureDifferenceDefaulted() const {
    return getImpl<detail::RefrigerationCondenserAirCooled_Impl>()->isRatedSubcoolingTemperatureDifferenceDefaulted();
  }

  bool RefrigerationCondenserAirCooled::setRatedSubcoolingTemperatureDifference(double ratedSubcoolingTemperatureDifference) {
    return getImpl<detail::RefrigerationCondenserAirCooled_Impl>()->setRatedSubcoolingTemperatureDifference(ratedSubcoolingTemperatureDifference);
  }

  void RefrigerationCondenserAirCooled::resetRatedSubcoolingTemperatureDifference() {
    getImpl<detail::RefrigerationCondenserAirCooled_Impl>()->resetRatedSubcoolingTemperatureDifference();
  }

  std::string RefrigerationCondenserAirCooled::condenserFanSpeedControlType() const {
    return getImpl<detail::RefrigerationCondenserAirCooled_Impl>()->condenserFanSpeedControlType();
  }

  bool RefrigerationCondenserAirCooled::isCondenserFanSpeedControlTypeDefaulted() const {
    return getImpl<detail::RefrigerationCondenserAirCooled_Impl>()->isCondenserFanSpeedControlTypeDefaulted();
  }

  bool RefrigerationCondenserAirCooled::setCondenserFanSpeedControlType(const std::string& condenserFanSpeedControlType) {
    return getImpl<detail::RefrigerationCondenserAirCooled_Impl>()->setCondenserFanSpeedControlType(condenserFanSpeedControlType);
  }

  void RefrigerationCondenserAirCooled::resetCondenserFanSpeedControlType() {
    getImpl<detail::RefrigerationCondenserAirCooled_Impl>()->resetCondenserFanSpeedControlType();
  }

  double RefrigerationCondenserAirCooled::ratedFanPower() const {
    return getImpl<detail::RefrigerationCondenserAirCooled_Impl>()->ratedFanPower();
  }

  bool RefrigerationCondenserAirCooled::isRatedFanPowerDefaulted() const {
    return getImpl<detail::RefrigerationCondenserAirCooled_Impl>()->isRatedFanPowerDefaulted();
  }

  bool RefrigerationCondenserAirCooled::setRatedFanPower(double ratedFanPower) {
    return getImpl<detail::RefrigerationCondenserAirCooled_Impl>()->setRatedFanPower(ratedFanPower);
  }

  void RefrigerationCondenserAirCooled::resetRatedFanPower() {
    getImpl<detail::RefrigerationCondenserAirCooled_Impl>()->resetRatedFanPower();
  }

  double RefrigerationCondenserAirCooled::minimumFanAirFlowRatio() const {
    return getImpl<detail::RefrigerationCondenserAirCooled_Impl>()->minimumFanAirFlowRatio();
  }

  bool RefrigerationCondenserAirCooled::isMinimumFanAirFlowRatioDefaulted() const {
    return getImpl<detail::RefrigerationCondenserAirCooled_Impl>()->isMinimumFanAirFlowRatioDefaulted();
  }

  bool RefrigerationCondenserAirCooled::setMinimumFanAirFlowRatio(double minimumFanAirFlowRatio) {
    return getImpl<detail::RefrigerationCondenserAirCooled_Impl>()->setMinimumFanAirFlowRatio(minimumFanAirFlowRatio);
  }

  void RefrigerationCondenserAirCooled::resetMinimumFanAirFlowRatio() {
    getImpl<detail::RefrigerationCondenserAirCooled_Impl>()->resetMinimumFanAirFlowRatio();
  }

  std::string RefrigerationCondenserAirCooled::endUseSubcategory() const {
    return getImpl<detail::RefrigerationCondenserAirCooled_Impl>()->endUseSubcategory();
  }

  bool RefrigerationCondenserAirCooled::isEndUseSubcategoryDefaulted() const {
    return getImpl<detail::RefrigerationCondenserAirCooled_Impl>()->isEndUseSubcategoryDefaulted();
  }

  bool RefrigerationCondenserAirCooled::setEndUseSubcategory(const std::string& endUseSubcategory) {
    return getImpl<detail::RefrigerationCondenserAirCooled_Impl>()->setEndUseSubcategory(endUseSubcategory);
  }

  void RefrigerationCondenserAirCooled::resetEndUseSubcategory() {
    getImpl<detail::RefrigerationCondenserAirCooled_Impl>()->resetEndUseSubcategory();
  }

  double RefrigerationCondenserAirCooled::condenserRefrigerantOperatingChargeInventory() const {
    return getImpl<detail::RefrigerationCondenserAirCooled_Impl>()->condenserRefrigerantOperatingChargeInventory();
  }

  bool RefrigerationCondenserAirCooled::isCondenserRefrigerantOperatingChargeInventoryDefaulted() const {
    return getImpl<detail::RefrigerationCondenserAirCooled_Impl>()->isCondenserRefrigerantOperatingChargeInventoryDefaulted();
  }

  bool RefrigerationCondenserAirCooled::setCondenserRefrigerantOperatingChargeInventory(double condenserRefrigerantOperatingChargeInventory) {
    return getImpl<detail::RefrigerationCondenserAirCooled_Impl>()->setCondenserRefrigerantOperatingChargeInventory(
      condenserRefrigerantOperatingChargeInventory);
  }

  void RefrigerationCondenserAirCooled::resetCondenserRefrigerantOperatingChargeInventory() {
    getImpl<detail::RefrigerationCondenserAirCooled_Impl>()->resetCondenserRefrigerantOperatingChargeInventory();
  }

  double RefrigerationCondenserAirCooled::condensateReceiverRefrigerantInventory() const {
    return getImpl<detail::RefrigerationCondenserAirCooled_Impl>()->condensateReceiverRefrigerantInventory();
  }

  bool RefrigerationCondenserAirCooled::isCondensateReceiverRefrigerantInventoryDefaulted() const {
    return getImpl<detail::RefrigerationCondenserAirCooled_Impl>()->isCondensateReceiverRefrigerantInventoryDefaulted();
  }

  bool RefrigerationCondenserAirCooled::setCondensateReceiverRefrigerantInventory(double condensateReceiverRefrigerantInventory) {
    return getImpl<detail::RefrigerationCondenserAirCooled_Impl>()->setCondensateReceiverRefrigerantInventory(condensateReceiverRefrigerantInventory);
  }

  void RefrigerationCondenserAirCooled::resetCondensateReceiverRefrigerantInventory() {
    getImpl<detail::RefrigerationCondenserAirCooled_Impl>()->resetCondensateReceiverRefrigerantInventory();
  }

  double RefrigerationCondenserAirCooled::condensatePipingRefrigerantInventory() const {
    return getImpl<detail::RefrigerationCondenserAirCooled_Impl>()->condensatePipingRefrigerantInventory();
  }

  bool RefrigerationCondenserAirCooled::isCondensatePipingRefrigerantInventoryDefaulted() const {
    return getImpl<detail::RefrigerationCondenserAirCooled_Impl>()->isCondensatePipingRefrigerantInventoryDefaulted();
  }

  bool RefrigerationCondenserAirCooled::setCondensatePipingRefrigerantInventory(double condensatePipingRefrigerantInventory) {
    return getImpl<detail::RefrigerationCondenserAirCooled_Impl>()->setCondensatePipingRefrigerantInventory(condensatePipingRefrigerantInventory);
  }

  void RefrigerationCondenserAirCooled::resetCondensatePipingRefrigerantInventory() {
    getImpl<detail::RefrigerationCondenserAirCooled_Impl>()->resetCondensatePipingRefrigerantInventory();
  }

}  // namespace epmodel
}  // namespace openstudio
