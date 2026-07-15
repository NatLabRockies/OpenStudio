/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ResourceObject/ScheduleTypeLimits.hpp"
#include "ResourceObject/ScheduleTypeLimits_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/ScheduleTypeLimits_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  ScheduleTypeLimits::ScheduleTypeLimits(const Model& model) : ModelObject(ScheduleTypeLimits::iddObjectType(), model) {}

  ScheduleTypeLimits::ScheduleTypeLimits(std::shared_ptr<detail::ScheduleTypeLimits_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType ScheduleTypeLimits::iddObjectType() {
    return IddObjectType::ScheduleTypeLimits;
  }

  std::vector<std::string> ScheduleTypeLimits::numericTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::ScheduleTypeLimitsFields::NumericType);
  }

  std::vector<std::string> ScheduleTypeLimits::unitTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::ScheduleTypeLimitsFields::UnitType);
  }

  boost::optional<double> ScheduleTypeLimits::lowerLimitValue() const {
    return getImpl<detail::ScheduleTypeLimits_Impl>()->lowerLimitValue();
  }

  bool ScheduleTypeLimits::setLowerLimitValue(double lowerLimitValue) {
    return getImpl<detail::ScheduleTypeLimits_Impl>()->setLowerLimitValue(lowerLimitValue);
  }

  void ScheduleTypeLimits::resetLowerLimitValue() {
    getImpl<detail::ScheduleTypeLimits_Impl>()->resetLowerLimitValue();
  }

  boost::optional<double> ScheduleTypeLimits::upperLimitValue() const {
    return getImpl<detail::ScheduleTypeLimits_Impl>()->upperLimitValue();
  }

  bool ScheduleTypeLimits::setUpperLimitValue(double upperLimitValue) {
    return getImpl<detail::ScheduleTypeLimits_Impl>()->setUpperLimitValue(upperLimitValue);
  }

  void ScheduleTypeLimits::resetUpperLimitValue() {
    getImpl<detail::ScheduleTypeLimits_Impl>()->resetUpperLimitValue();
  }

  boost::optional<std::string> ScheduleTypeLimits::numericType() const {
    return getImpl<detail::ScheduleTypeLimits_Impl>()->numericType();
  }

  bool ScheduleTypeLimits::setNumericType(const std::string& numericType) {
    return getImpl<detail::ScheduleTypeLimits_Impl>()->setNumericType(numericType);
  }

  void ScheduleTypeLimits::resetNumericType() {
    getImpl<detail::ScheduleTypeLimits_Impl>()->resetNumericType();
  }

  std::string ScheduleTypeLimits::unitType() const {
    return getImpl<detail::ScheduleTypeLimits_Impl>()->unitType();
  }

  bool ScheduleTypeLimits::isUnitTypeDefaulted() const {
    return getImpl<detail::ScheduleTypeLimits_Impl>()->isUnitTypeDefaulted();
  }

  bool ScheduleTypeLimits::setUnitType(const std::string& unitType) {
    return getImpl<detail::ScheduleTypeLimits_Impl>()->setUnitType(unitType);
  }

  void ScheduleTypeLimits::resetUnitType() {
    getImpl<detail::ScheduleTypeLimits_Impl>()->resetUnitType();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    boost::optional<double> ScheduleTypeLimits_Impl::lowerLimitValue() const {
      return getDouble(openstudio::ScheduleTypeLimitsFields::LowerLimitValue, true);
    }

    bool ScheduleTypeLimits_Impl::setLowerLimitValue(double lowerLimitValue) {
      return setDouble(openstudio::ScheduleTypeLimitsFields::LowerLimitValue, lowerLimitValue);
    }

    void ScheduleTypeLimits_Impl::resetLowerLimitValue() {
      OS_ASSERT(setString(openstudio::ScheduleTypeLimitsFields::LowerLimitValue, ""));
    }

    boost::optional<double> ScheduleTypeLimits_Impl::upperLimitValue() const {
      return getDouble(openstudio::ScheduleTypeLimitsFields::UpperLimitValue, true);
    }

    bool ScheduleTypeLimits_Impl::setUpperLimitValue(double upperLimitValue) {
      return setDouble(openstudio::ScheduleTypeLimitsFields::UpperLimitValue, upperLimitValue);
    }

    void ScheduleTypeLimits_Impl::resetUpperLimitValue() {
      OS_ASSERT(setString(openstudio::ScheduleTypeLimitsFields::UpperLimitValue, ""));
    }

    boost::optional<std::string> ScheduleTypeLimits_Impl::numericType() const {
      return getString(openstudio::ScheduleTypeLimitsFields::NumericType, true, true);
    }

    bool ScheduleTypeLimits_Impl::setNumericType(const std::string& numericType) {
      return setString(openstudio::ScheduleTypeLimitsFields::NumericType, numericType);
    }

    void ScheduleTypeLimits_Impl::resetNumericType() {
      OS_ASSERT(setString(openstudio::ScheduleTypeLimitsFields::NumericType, ""));
    }

    std::string ScheduleTypeLimits_Impl::unitType() const {
      auto value = getString(openstudio::ScheduleTypeLimitsFields::UnitType, true, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ScheduleTypeLimits_Impl::isUnitTypeDefaulted() const {
      return isEmpty(openstudio::ScheduleTypeLimitsFields::UnitType);
    }

    bool ScheduleTypeLimits_Impl::setUnitType(const std::string& unitType) {
      return setString(openstudio::ScheduleTypeLimitsFields::UnitType, unitType);
    }

    void ScheduleTypeLimits_Impl::resetUnitType() {
      OS_ASSERT(setString(openstudio::ScheduleTypeLimitsFields::UnitType, ""));
    }

    std::vector<std::string> ScheduleTypeLimits_Impl::numericTypeValues() const {
      return openstudio::epmodel::ScheduleTypeLimits::numericTypeValues();
    }

    std::vector<std::string> ScheduleTypeLimits_Impl::unitTypeValues() const {
      return openstudio::epmodel::ScheduleTypeLimits::unitTypeValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
