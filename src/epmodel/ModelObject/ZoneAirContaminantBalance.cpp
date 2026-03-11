/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include "ZoneAirContaminantBalance.hpp"
#include "ZoneAirContaminantBalance_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/ZoneAirContaminantBalance_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  ZoneAirContaminantBalance::ZoneAirContaminantBalance(const Model& model) : ModelObject(ZoneAirContaminantBalance::iddObjectType(), model) {}

  ZoneAirContaminantBalance::ZoneAirContaminantBalance(std::shared_ptr<detail::ZoneAirContaminantBalance_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType ZoneAirContaminantBalance::iddObjectType() {
    return IddObjectType::ZoneAirContaminantBalance;
  }

  bool ZoneAirContaminantBalance::carbonDioxideConcentration() const {
    return getImpl<detail::ZoneAirContaminantBalance_Impl>()->carbonDioxideConcentration();
  }

  bool ZoneAirContaminantBalance::isCarbonDioxideConcentrationDefaulted() const {
    return getImpl<detail::ZoneAirContaminantBalance_Impl>()->isCarbonDioxideConcentrationDefaulted();
  }

  bool ZoneAirContaminantBalance::setCarbonDioxideConcentration(bool carbonDioxideConcentration) {
    return getImpl<detail::ZoneAirContaminantBalance_Impl>()->setCarbonDioxideConcentration(carbonDioxideConcentration);
  }

  void ZoneAirContaminantBalance::setCarbonDioxideConcentrationNoFail(bool carbonDioxideConcentration) {
    const bool result = setCarbonDioxideConcentration(carbonDioxideConcentration);
    OS_ASSERT(result);
  }

  void ZoneAirContaminantBalance::resetCarbonDioxideConcentration() {
    getImpl<detail::ZoneAirContaminantBalance_Impl>()->resetCarbonDioxideConcentration();
  }

  bool ZoneAirContaminantBalance::genericContaminantConcentration() const {
    return getImpl<detail::ZoneAirContaminantBalance_Impl>()->genericContaminantConcentration();
  }

  bool ZoneAirContaminantBalance::isGenericContaminantConcentrationDefaulted() const {
    return getImpl<detail::ZoneAirContaminantBalance_Impl>()->isGenericContaminantConcentrationDefaulted();
  }

  bool ZoneAirContaminantBalance::setGenericContaminantConcentration(bool genericContaminantConcentration) {
    return getImpl<detail::ZoneAirContaminantBalance_Impl>()->setGenericContaminantConcentration(genericContaminantConcentration);
  }

  void ZoneAirContaminantBalance::resetGenericContaminantConcentration() {
    getImpl<detail::ZoneAirContaminantBalance_Impl>()->resetGenericContaminantConcentration();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace {

    bool getBooleanFieldValue(const detail::ModelObject_Impl& impl, int fieldIndex) {
      const auto value = impl.getString(fieldIndex, true);
      OS_ASSERT(value);
      return openstudio::istringEqual(*value, "Yes");
    }

    bool setBooleanFieldValue(detail::ModelObject_Impl& impl, int fieldIndex, bool value) {
      return impl.setString(fieldIndex, value ? "Yes" : "No");
    }

  }  // namespace
}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    bool ZoneAirContaminantBalance_Impl::carbonDioxideConcentration() const {
      return getBooleanFieldValue(*this, openstudio::ZoneAirContaminantBalanceFields::CarbonDioxideConcentration);
    }

    bool ZoneAirContaminantBalance_Impl::isCarbonDioxideConcentrationDefaulted() const {
      return isEmpty(openstudio::ZoneAirContaminantBalanceFields::CarbonDioxideConcentration);
    }

    bool ZoneAirContaminantBalance_Impl::setCarbonDioxideConcentration(bool carbonDioxideConcentration) {
      const bool result =
        setBooleanFieldValue(*this, openstudio::ZoneAirContaminantBalanceFields::CarbonDioxideConcentration, carbonDioxideConcentration);
      OS_ASSERT(result);
      return result;
    }

    void ZoneAirContaminantBalance_Impl::resetCarbonDioxideConcentration() {
      OS_ASSERT(setString(openstudio::ZoneAirContaminantBalanceFields::CarbonDioxideConcentration, ""));
    }

    bool ZoneAirContaminantBalance_Impl::genericContaminantConcentration() const {
      return getBooleanFieldValue(*this, openstudio::ZoneAirContaminantBalanceFields::GenericContaminantConcentration);
    }

    bool ZoneAirContaminantBalance_Impl::isGenericContaminantConcentrationDefaulted() const {
      return isEmpty(openstudio::ZoneAirContaminantBalanceFields::GenericContaminantConcentration);
    }

    bool ZoneAirContaminantBalance_Impl::setGenericContaminantConcentration(bool genericContaminantConcentration) {
      const bool result =
        setBooleanFieldValue(*this, openstudio::ZoneAirContaminantBalanceFields::GenericContaminantConcentration, genericContaminantConcentration);
      OS_ASSERT(result);
      return result;
    }

    void ZoneAirContaminantBalance_Impl::resetGenericContaminantConcentration() {
      OS_ASSERT(setString(openstudio::ZoneAirContaminantBalanceFields::GenericContaminantConcentration, ""));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
