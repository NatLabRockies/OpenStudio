/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ZoneBaseboardOutdoorTemperatureControlled.hpp"
#include "ZoneBaseboardOutdoorTemperatureControlled_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/ZoneBaseboard_OutdoorTemperatureControlled_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  ZoneBaseboardOutdoorTemperatureControlled::ZoneBaseboardOutdoorTemperatureControlled(const Model& model)
    : ModelObject(ZoneBaseboardOutdoorTemperatureControlled::iddObjectType(), model) {}

  ZoneBaseboardOutdoorTemperatureControlled::ZoneBaseboardOutdoorTemperatureControlled(
    std::shared_ptr<detail::ZoneBaseboardOutdoorTemperatureControlled_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType ZoneBaseboardOutdoorTemperatureControlled::iddObjectType() {
    return IddObjectType::ZoneBaseboard_OutdoorTemperatureControlled;
  }

  double ZoneBaseboardOutdoorTemperatureControlled::capacityAtLowTemperature() const {
    return getImpl<detail::ZoneBaseboardOutdoorTemperatureControlled_Impl>()->capacityAtLowTemperature();
  }

  bool ZoneBaseboardOutdoorTemperatureControlled::setCapacityAtLowTemperature(double capacityAtLowTemperature) {
    return getImpl<detail::ZoneBaseboardOutdoorTemperatureControlled_Impl>()->setCapacityAtLowTemperature(capacityAtLowTemperature);
  }

  double ZoneBaseboardOutdoorTemperatureControlled::lowTemperature() const {
    return getImpl<detail::ZoneBaseboardOutdoorTemperatureControlled_Impl>()->lowTemperature();
  }

  bool ZoneBaseboardOutdoorTemperatureControlled::setLowTemperature(double lowTemperature) {
    return getImpl<detail::ZoneBaseboardOutdoorTemperatureControlled_Impl>()->setLowTemperature(lowTemperature);
  }

  double ZoneBaseboardOutdoorTemperatureControlled::capacityAtHighTemperature() const {
    return getImpl<detail::ZoneBaseboardOutdoorTemperatureControlled_Impl>()->capacityAtHighTemperature();
  }

  bool ZoneBaseboardOutdoorTemperatureControlled::setCapacityAtHighTemperature(double capacityAtHighTemperature) {
    return getImpl<detail::ZoneBaseboardOutdoorTemperatureControlled_Impl>()->setCapacityAtHighTemperature(capacityAtHighTemperature);
  }

  double ZoneBaseboardOutdoorTemperatureControlled::highTemperature() const {
    return getImpl<detail::ZoneBaseboardOutdoorTemperatureControlled_Impl>()->highTemperature();
  }

  bool ZoneBaseboardOutdoorTemperatureControlled::setHighTemperature(double highTemperature) {
    return getImpl<detail::ZoneBaseboardOutdoorTemperatureControlled_Impl>()->setHighTemperature(highTemperature);
  }

  double ZoneBaseboardOutdoorTemperatureControlled::fractionRadiant() const {
    return getImpl<detail::ZoneBaseboardOutdoorTemperatureControlled_Impl>()->fractionRadiant();
  }

  bool ZoneBaseboardOutdoorTemperatureControlled::setFractionRadiant(double fractionRadiant) {
    return getImpl<detail::ZoneBaseboardOutdoorTemperatureControlled_Impl>()->setFractionRadiant(fractionRadiant);
  }

  bool ZoneBaseboardOutdoorTemperatureControlled::isFractionRadiantDefaulted() const {
    return getImpl<detail::ZoneBaseboardOutdoorTemperatureControlled_Impl>()->isFractionRadiantDefaulted();
  }

  void ZoneBaseboardOutdoorTemperatureControlled::resetFractionRadiant() {
    getImpl<detail::ZoneBaseboardOutdoorTemperatureControlled_Impl>()->resetFractionRadiant();
  }

  std::string ZoneBaseboardOutdoorTemperatureControlled::endUseSubcategory() const {
    return getImpl<detail::ZoneBaseboardOutdoorTemperatureControlled_Impl>()->endUseSubcategory();
  }

  bool ZoneBaseboardOutdoorTemperatureControlled::setEndUseSubcategory(const std::string& endUseSubcategory) {
    return getImpl<detail::ZoneBaseboardOutdoorTemperatureControlled_Impl>()->setEndUseSubcategory(endUseSubcategory);
  }

  bool ZoneBaseboardOutdoorTemperatureControlled::isEndUseSubcategoryDefaulted() const {
    return getImpl<detail::ZoneBaseboardOutdoorTemperatureControlled_Impl>()->isEndUseSubcategoryDefaulted();
  }

  void ZoneBaseboardOutdoorTemperatureControlled::resetEndUseSubcategory() {
    getImpl<detail::ZoneBaseboardOutdoorTemperatureControlled_Impl>()->resetEndUseSubcategory();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double ZoneBaseboardOutdoorTemperatureControlled_Impl::capacityAtLowTemperature() const {
      const auto value = getDouble(openstudio::ZoneBaseboard_OutdoorTemperatureControlledFields::CapacityatLowTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneBaseboardOutdoorTemperatureControlled_Impl::setCapacityAtLowTemperature(double capacityAtLowTemperature) {
      return setDouble(openstudio::ZoneBaseboard_OutdoorTemperatureControlledFields::CapacityatLowTemperature, capacityAtLowTemperature);
    }

    double ZoneBaseboardOutdoorTemperatureControlled_Impl::lowTemperature() const {
      const auto value = getDouble(openstudio::ZoneBaseboard_OutdoorTemperatureControlledFields::LowTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneBaseboardOutdoorTemperatureControlled_Impl::setLowTemperature(double lowTemperature) {
      const bool result = setDouble(openstudio::ZoneBaseboard_OutdoorTemperatureControlledFields::LowTemperature, lowTemperature);
      OS_ASSERT(result);
      return result;
    }

    double ZoneBaseboardOutdoorTemperatureControlled_Impl::capacityAtHighTemperature() const {
      const auto value = getDouble(openstudio::ZoneBaseboard_OutdoorTemperatureControlledFields::CapacityatHighTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneBaseboardOutdoorTemperatureControlled_Impl::setCapacityAtHighTemperature(double capacityAtHighTemperature) {
      return setDouble(openstudio::ZoneBaseboard_OutdoorTemperatureControlledFields::CapacityatHighTemperature, capacityAtHighTemperature);
    }

    double ZoneBaseboardOutdoorTemperatureControlled_Impl::highTemperature() const {
      const auto value = getDouble(openstudio::ZoneBaseboard_OutdoorTemperatureControlledFields::HighTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneBaseboardOutdoorTemperatureControlled_Impl::setHighTemperature(double highTemperature) {
      const bool result = setDouble(openstudio::ZoneBaseboard_OutdoorTemperatureControlledFields::HighTemperature, highTemperature);
      OS_ASSERT(result);
      return result;
    }

    double ZoneBaseboardOutdoorTemperatureControlled_Impl::fractionRadiant() const {
      const auto value = getDouble(openstudio::ZoneBaseboard_OutdoorTemperatureControlledFields::FractionRadiant, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneBaseboardOutdoorTemperatureControlled_Impl::setFractionRadiant(double fractionRadiant) {
      return setDouble(openstudio::ZoneBaseboard_OutdoorTemperatureControlledFields::FractionRadiant, fractionRadiant);
    }

    bool ZoneBaseboardOutdoorTemperatureControlled_Impl::isFractionRadiantDefaulted() const {
      return isEmpty(openstudio::ZoneBaseboard_OutdoorTemperatureControlledFields::FractionRadiant);
    }

    void ZoneBaseboardOutdoorTemperatureControlled_Impl::resetFractionRadiant() {
      OS_ASSERT(setString(openstudio::ZoneBaseboard_OutdoorTemperatureControlledFields::FractionRadiant, ""));
    }

    std::string ZoneBaseboardOutdoorTemperatureControlled_Impl::endUseSubcategory() const {
      auto value = getString(openstudio::ZoneBaseboard_OutdoorTemperatureControlledFields::EndUseSubcategory, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneBaseboardOutdoorTemperatureControlled_Impl::setEndUseSubcategory(const std::string& endUseSubcategory) {
      const bool result = setString(openstudio::ZoneBaseboard_OutdoorTemperatureControlledFields::EndUseSubcategory, endUseSubcategory);
      OS_ASSERT(result);
      return result;
    }

    bool ZoneBaseboardOutdoorTemperatureControlled_Impl::isEndUseSubcategoryDefaulted() const {
      return isEmpty(openstudio::ZoneBaseboard_OutdoorTemperatureControlledFields::EndUseSubcategory);
    }

    void ZoneBaseboardOutdoorTemperatureControlled_Impl::resetEndUseSubcategory() {
      OS_ASSERT(setString(openstudio::ZoneBaseboard_OutdoorTemperatureControlledFields::EndUseSubcategory, ""));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
