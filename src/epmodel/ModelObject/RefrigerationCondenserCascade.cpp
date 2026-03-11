/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include "ModelObject/RefrigerationCondenserCascade.hpp"
#include "ModelObject/RefrigerationCondenserCascade_Impl.hpp"

#include "Model.hpp"

#include <utility>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/Refrigeration_Condenser_Cascade_FieldEnums.hxx>
#include <utilities/core/Assert.hpp>

namespace openstudio {
namespace epmodel {

  RefrigerationCondenserCascade::RefrigerationCondenserCascade(const Model& model)
    : ModelObject(RefrigerationCondenserCascade::iddObjectType(), model) {}

  RefrigerationCondenserCascade::RefrigerationCondenserCascade(std::shared_ptr<detail::RefrigerationCondenserCascade_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType RefrigerationCondenserCascade::iddObjectType() {
    return IddObjectType::Refrigeration_Condenser_Cascade;
  }

  std::vector<std::string> RefrigerationCondenserCascade::condensingTemperatureControlTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          Refrigeration_Condenser_CascadeFields::CondensingTemperatureControlType);
  }

  double RefrigerationCondenserCascade::ratedCondensingTemperature() const {
    return getImpl<detail::RefrigerationCondenserCascade_Impl>()->ratedCondensingTemperature();
  }

  double RefrigerationCondenserCascade::ratedApproachTemperatureDifference() const {
    return getImpl<detail::RefrigerationCondenserCascade_Impl>()->ratedApproachTemperatureDifference();
  }

  bool RefrigerationCondenserCascade::isRatedApproachTemperatureDifferenceDefaulted() const {
    return getImpl<detail::RefrigerationCondenserCascade_Impl>()->isRatedApproachTemperatureDifferenceDefaulted();
  }

  double RefrigerationCondenserCascade::ratedEffectiveTotalHeatRejectionRate() const {
    return getImpl<detail::RefrigerationCondenserCascade_Impl>()->ratedEffectiveTotalHeatRejectionRate();
  }

  std::string RefrigerationCondenserCascade::condensingTemperatureControlType() const {
    return getImpl<detail::RefrigerationCondenserCascade_Impl>()->condensingTemperatureControlType();
  }

  bool RefrigerationCondenserCascade::isCondensingTemperatureControlTypeDefaulted() const {
    return getImpl<detail::RefrigerationCondenserCascade_Impl>()->isCondensingTemperatureControlTypeDefaulted();
  }

  boost::optional<double> RefrigerationCondenserCascade::condenserRefrigerantOperatingChargeInventory() const {
    return getImpl<detail::RefrigerationCondenserCascade_Impl>()->condenserRefrigerantOperatingChargeInventory();
  }

  boost::optional<double> RefrigerationCondenserCascade::condensateReceiverRefrigerantInventory() const {
    return getImpl<detail::RefrigerationCondenserCascade_Impl>()->condensateReceiverRefrigerantInventory();
  }

  boost::optional<double> RefrigerationCondenserCascade::condensatePipingRefrigerantInventory() const {
    return getImpl<detail::RefrigerationCondenserCascade_Impl>()->condensatePipingRefrigerantInventory();
  }

  bool RefrigerationCondenserCascade::setRatedCondensingTemperature(double ratedCondensingTemperature) {
    return getImpl<detail::RefrigerationCondenserCascade_Impl>()->setRatedCondensingTemperature(ratedCondensingTemperature);
  }

  bool RefrigerationCondenserCascade::setRatedApproachTemperatureDifference(double ratedApproachTemperatureDifference) {
    return getImpl<detail::RefrigerationCondenserCascade_Impl>()->setRatedApproachTemperatureDifference(ratedApproachTemperatureDifference);
  }

  void RefrigerationCondenserCascade::resetRatedApproachTemperatureDifference() {
    getImpl<detail::RefrigerationCondenserCascade_Impl>()->resetRatedApproachTemperatureDifference();
  }

  bool RefrigerationCondenserCascade::setRatedEffectiveTotalHeatRejectionRate(double ratedEffectiveTotalHeatRejectionRate) {
    return getImpl<detail::RefrigerationCondenserCascade_Impl>()->setRatedEffectiveTotalHeatRejectionRate(ratedEffectiveTotalHeatRejectionRate);
  }

  bool RefrigerationCondenserCascade::setCondensingTemperatureControlType(const std::string& condensingTemperatureControlType) {
    return getImpl<detail::RefrigerationCondenserCascade_Impl>()->setCondensingTemperatureControlType(condensingTemperatureControlType);
  }

  void RefrigerationCondenserCascade::resetCondensingTemperatureControlType() {
    getImpl<detail::RefrigerationCondenserCascade_Impl>()->resetCondensingTemperatureControlType();
  }

  bool RefrigerationCondenserCascade::setCondenserRefrigerantOperatingChargeInventory(double condenserRefrigerantOperatingChargeInventory) {
    return getImpl<detail::RefrigerationCondenserCascade_Impl>()->setCondenserRefrigerantOperatingChargeInventory(
      condenserRefrigerantOperatingChargeInventory);
  }

  void RefrigerationCondenserCascade::resetCondenserRefrigerantOperatingChargeInventory() {
    getImpl<detail::RefrigerationCondenserCascade_Impl>()->resetCondenserRefrigerantOperatingChargeInventory();
  }

  bool RefrigerationCondenserCascade::setCondensateReceiverRefrigerantInventory(double condensateReceiverRefrigerantInventory) {
    return getImpl<detail::RefrigerationCondenserCascade_Impl>()->setCondensateReceiverRefrigerantInventory(condensateReceiverRefrigerantInventory);
  }

  void RefrigerationCondenserCascade::resetCondensateReceiverRefrigerantInventory() {
    getImpl<detail::RefrigerationCondenserCascade_Impl>()->resetCondensateReceiverRefrigerantInventory();
  }

  bool RefrigerationCondenserCascade::setCondensatePipingRefrigerantInventory(double condensatePipingRefrigerantInventory) {
    return getImpl<detail::RefrigerationCondenserCascade_Impl>()->setCondensatePipingRefrigerantInventory(condensatePipingRefrigerantInventory);
  }

  void RefrigerationCondenserCascade::resetCondensatePipingRefrigerantInventory() {
    getImpl<detail::RefrigerationCondenserCascade_Impl>()->resetCondensatePipingRefrigerantInventory();
  }

  namespace detail {

    double RefrigerationCondenserCascade_Impl::ratedCondensingTemperature() const {
      const auto value = getDouble(Refrigeration_Condenser_CascadeFields::RatedCondensingTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    double RefrigerationCondenserCascade_Impl::ratedApproachTemperatureDifference() const {
      const auto value = getDouble(Refrigeration_Condenser_CascadeFields::RatedApproachTemperatureDifference, true);
      OS_ASSERT(value);
      return *value;
    }

    bool RefrigerationCondenserCascade_Impl::isRatedApproachTemperatureDifferenceDefaulted() const {
      return isEmpty(Refrigeration_Condenser_CascadeFields::RatedApproachTemperatureDifference);
    }

    double RefrigerationCondenserCascade_Impl::ratedEffectiveTotalHeatRejectionRate() const {
      const auto value = getDouble(Refrigeration_Condenser_CascadeFields::RatedEffectiveTotalHeatRejectionRate, true);
      OS_ASSERT(value);
      return *value;
    }

    std::string RefrigerationCondenserCascade_Impl::condensingTemperatureControlType() const {
      const auto value = getString(Refrigeration_Condenser_CascadeFields::CondensingTemperatureControlType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool RefrigerationCondenserCascade_Impl::isCondensingTemperatureControlTypeDefaulted() const {
      return isEmpty(Refrigeration_Condenser_CascadeFields::CondensingTemperatureControlType);
    }

    boost::optional<double> RefrigerationCondenserCascade_Impl::condenserRefrigerantOperatingChargeInventory() const {
      return getDouble(Refrigeration_Condenser_CascadeFields::CondenserRefrigerantOperatingChargeInventory, true);
    }

    boost::optional<double> RefrigerationCondenserCascade_Impl::condensateReceiverRefrigerantInventory() const {
      return getDouble(Refrigeration_Condenser_CascadeFields::CondensateReceiverRefrigerantInventory, true);
    }

    boost::optional<double> RefrigerationCondenserCascade_Impl::condensatePipingRefrigerantInventory() const {
      return getDouble(Refrigeration_Condenser_CascadeFields::CondensatePipingRefrigerantInventory, true);
    }

    bool RefrigerationCondenserCascade_Impl::setRatedCondensingTemperature(double ratedCondensingTemperature) {
      return setDouble(Refrigeration_Condenser_CascadeFields::RatedCondensingTemperature, ratedCondensingTemperature);
    }

    bool RefrigerationCondenserCascade_Impl::setRatedApproachTemperatureDifference(double ratedApproachTemperatureDifference) {
      return setDouble(Refrigeration_Condenser_CascadeFields::RatedApproachTemperatureDifference, ratedApproachTemperatureDifference);
    }

    void RefrigerationCondenserCascade_Impl::resetRatedApproachTemperatureDifference() {
      const bool result = setString(Refrigeration_Condenser_CascadeFields::RatedApproachTemperatureDifference, "");
      OS_ASSERT(result);
    }

    bool RefrigerationCondenserCascade_Impl::setRatedEffectiveTotalHeatRejectionRate(double ratedEffectiveTotalHeatRejectionRate) {
      return setDouble(Refrigeration_Condenser_CascadeFields::RatedEffectiveTotalHeatRejectionRate, ratedEffectiveTotalHeatRejectionRate);
    }

    bool RefrigerationCondenserCascade_Impl::setCondensingTemperatureControlType(const std::string& condensingTemperatureControlType) {
      return setString(Refrigeration_Condenser_CascadeFields::CondensingTemperatureControlType, condensingTemperatureControlType);
    }

    void RefrigerationCondenserCascade_Impl::resetCondensingTemperatureControlType() {
      const bool result = setString(Refrigeration_Condenser_CascadeFields::CondensingTemperatureControlType, "");
      OS_ASSERT(result);
    }

    bool RefrigerationCondenserCascade_Impl::setCondenserRefrigerantOperatingChargeInventory(double condenserRefrigerantOperatingChargeInventory) {
      return setDouble(Refrigeration_Condenser_CascadeFields::CondenserRefrigerantOperatingChargeInventory,
                       condenserRefrigerantOperatingChargeInventory);
    }

    void RefrigerationCondenserCascade_Impl::resetCondenserRefrigerantOperatingChargeInventory() {
      const bool result = setString(Refrigeration_Condenser_CascadeFields::CondenserRefrigerantOperatingChargeInventory, "");
      OS_ASSERT(result);
    }

    bool RefrigerationCondenserCascade_Impl::setCondensateReceiverRefrigerantInventory(double condensateReceiverRefrigerantInventory) {
      return setDouble(Refrigeration_Condenser_CascadeFields::CondensateReceiverRefrigerantInventory, condensateReceiverRefrigerantInventory);
    }

    void RefrigerationCondenserCascade_Impl::resetCondensateReceiverRefrigerantInventory() {
      const bool result = setString(Refrigeration_Condenser_CascadeFields::CondensateReceiverRefrigerantInventory, "");
      OS_ASSERT(result);
    }

    bool RefrigerationCondenserCascade_Impl::setCondensatePipingRefrigerantInventory(double condensatePipingRefrigerantInventory) {
      return setDouble(Refrigeration_Condenser_CascadeFields::CondensatePipingRefrigerantInventory, condensatePipingRefrigerantInventory);
    }

    void RefrigerationCondenserCascade_Impl::resetCondensatePipingRefrigerantInventory() {
      const bool result = setString(Refrigeration_Condenser_CascadeFields::CondensatePipingRefrigerantInventory, "");
      OS_ASSERT(result);
    }

  }  // namespace detail

}  // namespace epmodel
}  // namespace openstudio
