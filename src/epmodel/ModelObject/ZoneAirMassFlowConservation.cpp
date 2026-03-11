/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ZoneAirMassFlowConservation.hpp"
#include "ZoneAirMassFlowConservation_Impl.hpp"

#include "Model.hpp"

#include <utility>

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/ZoneAirMassFlowConservation_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  ZoneAirMassFlowConservation::ZoneAirMassFlowConservation(const Model& model) : ModelObject(ZoneAirMassFlowConservation::iddObjectType(), model) {}

  ZoneAirMassFlowConservation::ZoneAirMassFlowConservation(std::shared_ptr<detail::ZoneAirMassFlowConservation_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType ZoneAirMassFlowConservation::iddObjectType() {
    return IddObjectType::ZoneAirMassFlowConservation;
  }

  std::vector<std::string> ZoneAirMassFlowConservation::adjustZoneMixingandReturnForAirMassFlowBalanceValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::ZoneAirMassFlowConservationFields::AdjustZoneMixingandReturnForAirMassFlowBalance);
  }

  std::vector<std::string> ZoneAirMassFlowConservation::infiltrationBalancingMethodValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::ZoneAirMassFlowConservationFields::InfiltrationBalancingMethod);
  }

  std::vector<std::string> ZoneAirMassFlowConservation::infiltrationBalancingZonesValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::ZoneAirMassFlowConservationFields::InfiltrationBalancingZones);
  }

  std::string ZoneAirMassFlowConservation::adjustZoneMixingandReturnForAirMassFlowBalance() const {
    return getImpl<detail::ZoneAirMassFlowConservation_Impl>()->adjustZoneMixingandReturnForAirMassFlowBalance();
  }

  bool ZoneAirMassFlowConservation::isAdjustZoneMixingandReturnForAirMassFlowBalanceDefaulted() const {
    return getImpl<detail::ZoneAirMassFlowConservation_Impl>()->isAdjustZoneMixingandReturnForAirMassFlowBalanceDefaulted();
  }

  std::string ZoneAirMassFlowConservation::infiltrationBalancingMethod() const {
    return getImpl<detail::ZoneAirMassFlowConservation_Impl>()->infiltrationBalancingMethod();
  }

  bool ZoneAirMassFlowConservation::isInfiltrationBalancingMethodDefaulted() const {
    return getImpl<detail::ZoneAirMassFlowConservation_Impl>()->isInfiltrationBalancingMethodDefaulted();
  }

  std::string ZoneAirMassFlowConservation::infiltrationBalancingZones() const {
    return getImpl<detail::ZoneAirMassFlowConservation_Impl>()->infiltrationBalancingZones();
  }

  bool ZoneAirMassFlowConservation::isInfiltrationBalancingZonesDefaulted() const {
    return getImpl<detail::ZoneAirMassFlowConservation_Impl>()->isInfiltrationBalancingZonesDefaulted();
  }

  bool ZoneAirMassFlowConservation::setAdjustZoneMixingandReturnForAirMassFlowBalance(
    const std::string& adjustZoneMixingandReturnForAirMassFlowBalance) {
    return getImpl<detail::ZoneAirMassFlowConservation_Impl>()->setAdjustZoneMixingandReturnForAirMassFlowBalance(
      adjustZoneMixingandReturnForAirMassFlowBalance);
  }

  void ZoneAirMassFlowConservation::resetAdjustZoneMixingandReturnForAirMassFlowBalance() {
    getImpl<detail::ZoneAirMassFlowConservation_Impl>()->resetAdjustZoneMixingandReturnForAirMassFlowBalance();
  }

  bool ZoneAirMassFlowConservation::setInfiltrationBalancingMethod(const std::string& infiltrationBalancingMethod) {
    return getImpl<detail::ZoneAirMassFlowConservation_Impl>()->setInfiltrationBalancingMethod(infiltrationBalancingMethod);
  }

  void ZoneAirMassFlowConservation::resetInfiltrationBalancingMethod() {
    getImpl<detail::ZoneAirMassFlowConservation_Impl>()->resetInfiltrationBalancingMethod();
  }

  bool ZoneAirMassFlowConservation::setInfiltrationBalancingZones(const std::string& infiltrationBalancingZones) {
    return getImpl<detail::ZoneAirMassFlowConservation_Impl>()->setInfiltrationBalancingZones(infiltrationBalancingZones);
  }

  void ZoneAirMassFlowConservation::resetInfiltrationBalancingZones() {
    getImpl<detail::ZoneAirMassFlowConservation_Impl>()->resetInfiltrationBalancingZones();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::string ZoneAirMassFlowConservation_Impl::adjustZoneMixingandReturnForAirMassFlowBalance() const {
      const auto value = getString(openstudio::ZoneAirMassFlowConservationFields::AdjustZoneMixingandReturnForAirMassFlowBalance, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneAirMassFlowConservation_Impl::isAdjustZoneMixingandReturnForAirMassFlowBalanceDefaulted() const {
      return isEmpty(openstudio::ZoneAirMassFlowConservationFields::AdjustZoneMixingandReturnForAirMassFlowBalance);
    }

    std::string ZoneAirMassFlowConservation_Impl::infiltrationBalancingMethod() const {
      const auto value = getString(openstudio::ZoneAirMassFlowConservationFields::InfiltrationBalancingMethod, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneAirMassFlowConservation_Impl::isInfiltrationBalancingMethodDefaulted() const {
      return isEmpty(openstudio::ZoneAirMassFlowConservationFields::InfiltrationBalancingMethod);
    }

    std::string ZoneAirMassFlowConservation_Impl::infiltrationBalancingZones() const {
      const auto value = getString(openstudio::ZoneAirMassFlowConservationFields::InfiltrationBalancingZones, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneAirMassFlowConservation_Impl::isInfiltrationBalancingZonesDefaulted() const {
      return isEmpty(openstudio::ZoneAirMassFlowConservationFields::InfiltrationBalancingZones);
    }

    bool ZoneAirMassFlowConservation_Impl::setAdjustZoneMixingandReturnForAirMassFlowBalance(
      const std::string& adjustZoneMixingandReturnForAirMassFlowBalance) {
      const bool result = setString(openstudio::ZoneAirMassFlowConservationFields::AdjustZoneMixingandReturnForAirMassFlowBalance,
                                    adjustZoneMixingandReturnForAirMassFlowBalance, false);
      OS_ASSERT(result);
      return result;
    }

    void ZoneAirMassFlowConservation_Impl::resetAdjustZoneMixingandReturnForAirMassFlowBalance() {
      const bool result = setString(openstudio::ZoneAirMassFlowConservationFields::AdjustZoneMixingandReturnForAirMassFlowBalance, "", false);
      OS_ASSERT(result);
    }

    bool ZoneAirMassFlowConservation_Impl::setInfiltrationBalancingMethod(const std::string& infiltrationBalancingMethod) {
      const bool result = setString(openstudio::ZoneAirMassFlowConservationFields::InfiltrationBalancingMethod, infiltrationBalancingMethod, false);
      OS_ASSERT(result);
      return result;
    }

    void ZoneAirMassFlowConservation_Impl::resetInfiltrationBalancingMethod() {
      const bool result = setString(openstudio::ZoneAirMassFlowConservationFields::InfiltrationBalancingMethod, "", false);
      OS_ASSERT(result);
    }

    bool ZoneAirMassFlowConservation_Impl::setInfiltrationBalancingZones(const std::string& infiltrationBalancingZones) {
      const bool result = setString(openstudio::ZoneAirMassFlowConservationFields::InfiltrationBalancingZones, infiltrationBalancingZones, false);
      OS_ASSERT(result);
      return result;
    }

    void ZoneAirMassFlowConservation_Impl::resetInfiltrationBalancingZones() {
      const bool result = setString(openstudio::ZoneAirMassFlowConservationFields::InfiltrationBalancingZones, "", false);
      OS_ASSERT(result);
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
