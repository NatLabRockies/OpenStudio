/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include "ZoneAirBalanceOutdoorAir.hpp"
#include "ZoneAirBalanceOutdoorAir_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/ZoneAirBalance_OutdoorAir_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  ZoneAirBalanceOutdoorAir::ZoneAirBalanceOutdoorAir(const Model& model) : ModelObject(ZoneAirBalanceOutdoorAir::iddObjectType(), model) {}

  ZoneAirBalanceOutdoorAir::ZoneAirBalanceOutdoorAir(std::shared_ptr<detail::ZoneAirBalanceOutdoorAir_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType ZoneAirBalanceOutdoorAir::iddObjectType() {
    return IddObjectType::ZoneAirBalance_OutdoorAir;
  }

  std::vector<std::string> ZoneAirBalanceOutdoorAir::airBalanceMethodValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::ZoneAirBalance_OutdoorAirFields::AirBalanceMethod);
  }

  std::string ZoneAirBalanceOutdoorAir::airBalanceMethod() const {
    return getImpl<detail::ZoneAirBalanceOutdoorAir_Impl>()->airBalanceMethod();
  }

  bool ZoneAirBalanceOutdoorAir::isAirBalanceMethodDefaulted() const {
    return getImpl<detail::ZoneAirBalanceOutdoorAir_Impl>()->isAirBalanceMethodDefaulted();
  }

  bool ZoneAirBalanceOutdoorAir::setAirBalanceMethod(const std::string& airBalanceMethod) {
    return getImpl<detail::ZoneAirBalanceOutdoorAir_Impl>()->setAirBalanceMethod(airBalanceMethod);
  }

  void ZoneAirBalanceOutdoorAir::resetAirBalanceMethod() {
    getImpl<detail::ZoneAirBalanceOutdoorAir_Impl>()->resetAirBalanceMethod();
  }

  double ZoneAirBalanceOutdoorAir::inducedOutdoorAirDueToUnbalancedDuctLeakage() const {
    return getImpl<detail::ZoneAirBalanceOutdoorAir_Impl>()->inducedOutdoorAirDueToUnbalancedDuctLeakage();
  }

  bool ZoneAirBalanceOutdoorAir::isInducedOutdoorAirDueToUnbalancedDuctLeakageDefaulted() const {
    return getImpl<detail::ZoneAirBalanceOutdoorAir_Impl>()->isInducedOutdoorAirDueToUnbalancedDuctLeakageDefaulted();
  }

  bool ZoneAirBalanceOutdoorAir::setInducedOutdoorAirDueToUnbalancedDuctLeakage(double inducedOutdoorAirDueToUnbalancedDuctLeakage) {
    return getImpl<detail::ZoneAirBalanceOutdoorAir_Impl>()->setInducedOutdoorAirDueToUnbalancedDuctLeakage(
      inducedOutdoorAirDueToUnbalancedDuctLeakage);
  }

  void ZoneAirBalanceOutdoorAir::resetInducedOutdoorAirDueToUnbalancedDuctLeakage() {
    getImpl<detail::ZoneAirBalanceOutdoorAir_Impl>()->resetInducedOutdoorAirDueToUnbalancedDuctLeakage();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::string ZoneAirBalanceOutdoorAir_Impl::airBalanceMethod() const {
      const auto value = getString(openstudio::ZoneAirBalance_OutdoorAirFields::AirBalanceMethod, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneAirBalanceOutdoorAir_Impl::isAirBalanceMethodDefaulted() const {
      return isEmpty(openstudio::ZoneAirBalance_OutdoorAirFields::AirBalanceMethod);
    }

    bool ZoneAirBalanceOutdoorAir_Impl::setAirBalanceMethod(const std::string& airBalanceMethod) {
      return setString(openstudio::ZoneAirBalance_OutdoorAirFields::AirBalanceMethod, airBalanceMethod);
    }

    void ZoneAirBalanceOutdoorAir_Impl::resetAirBalanceMethod() {
      OS_ASSERT(setString(openstudio::ZoneAirBalance_OutdoorAirFields::AirBalanceMethod, ""));
    }

    std::vector<std::string> ZoneAirBalanceOutdoorAir_Impl::airBalanceMethodValues() const {
      return openstudio::epmodel::ZoneAirBalanceOutdoorAir::airBalanceMethodValues();
    }

    double ZoneAirBalanceOutdoorAir_Impl::inducedOutdoorAirDueToUnbalancedDuctLeakage() const {
      const auto value = getDouble(openstudio::ZoneAirBalance_OutdoorAirFields::InducedOutdoorAirDuetoUnbalancedDuctLeakage, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneAirBalanceOutdoorAir_Impl::isInducedOutdoorAirDueToUnbalancedDuctLeakageDefaulted() const {
      return isEmpty(openstudio::ZoneAirBalance_OutdoorAirFields::InducedOutdoorAirDuetoUnbalancedDuctLeakage);
    }

    bool ZoneAirBalanceOutdoorAir_Impl::setInducedOutdoorAirDueToUnbalancedDuctLeakage(double inducedOutdoorAirDueToUnbalancedDuctLeakage) {
      const bool result = setDouble(openstudio::ZoneAirBalance_OutdoorAirFields::InducedOutdoorAirDuetoUnbalancedDuctLeakage,
                                    inducedOutdoorAirDueToUnbalancedDuctLeakage);
      OS_ASSERT(result);
      return result;
    }

    void ZoneAirBalanceOutdoorAir_Impl::resetInducedOutdoorAirDueToUnbalancedDuctLeakage() {
      OS_ASSERT(setString(openstudio::ZoneAirBalance_OutdoorAirFields::InducedOutdoorAirDuetoUnbalancedDuctLeakage, ""));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
