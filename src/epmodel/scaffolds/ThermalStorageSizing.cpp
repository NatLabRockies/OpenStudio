/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ThermalStorageSizing.hpp"
#include "ThermalStorageSizing_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/ThermalStorage_Sizing_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  ThermalStorageSizing::ThermalStorageSizing(const Model& model) : ModelObject(ThermalStorageSizing::iddObjectType(), model) {}

  ThermalStorageSizing::ThermalStorageSizing(std::shared_ptr<detail::ThermalStorageSizing_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType ThermalStorageSizing::iddObjectType() {
    return IddObjectType::ThermalStorage_Sizing;
  }

  // On-peak period start time
  double ThermalStorageSizing::onPeakPeriodStartTime() const {
    return getImpl<detail::ThermalStorageSizing_Impl>()->onPeakPeriodStartTime();
  }

  bool ThermalStorageSizing::setOnPeakPeriodStartTime(double onPeakPeriodStartTime) {
    return getImpl<detail::ThermalStorageSizing_Impl>()->setOnPeakPeriodStartTime(onPeakPeriodStartTime);
  }

  // On-peak period end time
  double ThermalStorageSizing::onPeakPeriodEndTime() const {
    return getImpl<detail::ThermalStorageSizing_Impl>()->onPeakPeriodEndTime();
  }

  bool ThermalStorageSizing::setOnPeakPeriodEndTime(double onPeakPeriodEndTime) {
    return getImpl<detail::ThermalStorageSizing_Impl>()->setOnPeakPeriodEndTime(onPeakPeriodEndTime);
  }

  // Sizing factor
  double ThermalStorageSizing::sizingFactor() const {
    return getImpl<detail::ThermalStorageSizing_Impl>()->sizingFactor();
  }

  bool ThermalStorageSizing::setSizingFactor(double sizingFactor) {
    return getImpl<detail::ThermalStorageSizing_Impl>()->setSizingFactor(sizingFactor);
  }

  bool ThermalStorageSizing::isSizingFactorDefaulted() const {
    return getImpl<detail::ThermalStorageSizing_Impl>()->isSizingFactorDefaulted();
  }

  void ThermalStorageSizing::resetSizingFactor() {
    getImpl<detail::ThermalStorageSizing_Impl>()->resetSizingFactor();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    // On-peak period start time
    double ThermalStorageSizing_Impl::onPeakPeriodStartTime() const {
      const auto value = getDouble(ThermalStorage_SizingFields::OnPeakPeriodStartTime, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ThermalStorageSizing_Impl::setOnPeakPeriodStartTime(double onPeakPeriodStartTime) {
      const bool result = setDouble(ThermalStorage_SizingFields::OnPeakPeriodStartTime, onPeakPeriodStartTime);
      OS_ASSERT(result);
      return result;
    }

    // On-peak period end time
    double ThermalStorageSizing_Impl::onPeakPeriodEndTime() const {
      const auto value = getDouble(ThermalStorage_SizingFields::OnPeakPeriodEndTime, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ThermalStorageSizing_Impl::setOnPeakPeriodEndTime(double onPeakPeriodEndTime) {
      const bool result = setDouble(ThermalStorage_SizingFields::OnPeakPeriodEndTime, onPeakPeriodEndTime);
      OS_ASSERT(result);
      return result;
    }

    // Sizing factor
    double ThermalStorageSizing_Impl::sizingFactor() const {
      const auto value = getDouble(ThermalStorage_SizingFields::SizingFactor, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ThermalStorageSizing_Impl::setSizingFactor(double sizingFactor) {
      return setDouble(ThermalStorage_SizingFields::SizingFactor, sizingFactor);
    }

    bool ThermalStorageSizing_Impl::isSizingFactorDefaulted() const {
      return isEmpty(ThermalStorage_SizingFields::SizingFactor);
    }

    void ThermalStorageSizing_Impl::resetSizingFactor() {
      const bool result = setString(ThermalStorage_SizingFields::SizingFactor, "");
      OS_ASSERT(result);
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
