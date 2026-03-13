/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "MeterCustomDecrement.hpp"
#include "MeterCustomDecrement_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/Meter_CustomDecrement_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  MeterCustomDecrement::MeterCustomDecrement(const Model& model, const std::string& sourceMeterName)
    : ModelObject(MeterCustomDecrement::iddObjectType(), model) {
    OS_ASSERT(setSourceMeterName(sourceMeterName));
    OS_ASSERT(setFuelType("Electricity"));
  }

  MeterCustomDecrement::MeterCustomDecrement(std::shared_ptr<detail::MeterCustomDecrement_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType MeterCustomDecrement::iddObjectType() {
    return IddObjectType::Meter_CustomDecrement;
  }

  std::vector<std::string> MeterCustomDecrement::fuelTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Meter_CustomDecrementFields::ResourceType);
  }

  boost::optional<std::string> MeterCustomDecrement::fuelType() const {
    return getImpl<detail::MeterCustomDecrement_Impl>()->fuelType();
  }

  bool MeterCustomDecrement::setFuelType(const std::string& fuelType) {
    return getImpl<detail::MeterCustomDecrement_Impl>()->setFuelType(fuelType);
  }

  void MeterCustomDecrement::resetFuelType() {
    getImpl<detail::MeterCustomDecrement_Impl>()->resetFuelType();
  }

  std::string MeterCustomDecrement::sourceMeterName() const {
    return getImpl<detail::MeterCustomDecrement_Impl>()->sourceMeterName();
  }

  bool MeterCustomDecrement::setSourceMeterName(const std::string& sourceMeterName) {
    return getImpl<detail::MeterCustomDecrement_Impl>()->setSourceMeterName(sourceMeterName);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    boost::optional<std::string> MeterCustomDecrement_Impl::fuelType() const {
      if (isEmpty(openstudio::Meter_CustomDecrementFields::ResourceType)) {
        return boost::none;
      }
      return getString(openstudio::Meter_CustomDecrementFields::ResourceType, true);
    }

    bool MeterCustomDecrement_Impl::setFuelType(const std::string& fuelType) {
      return setString(openstudio::Meter_CustomDecrementFields::ResourceType, fuelType);
    }

    void MeterCustomDecrement_Impl::resetFuelType() {
      OS_ASSERT(setString(openstudio::Meter_CustomDecrementFields::ResourceType, ""));
    }

    std::vector<std::string> MeterCustomDecrement_Impl::fuelTypeValues() const {
      return openstudio::epmodel::MeterCustomDecrement::fuelTypeValues();
    }

    std::string MeterCustomDecrement_Impl::sourceMeterName() const {
      const auto value = getString(openstudio::Meter_CustomDecrementFields::SourceMeterName, true);
      OS_ASSERT(value);
      return *value;
    }

    bool MeterCustomDecrement_Impl::setSourceMeterName(const std::string& sourceMeterName) {
      const bool result = setString(openstudio::Meter_CustomDecrementFields::SourceMeterName, sourceMeterName);
      OS_ASSERT(result);
      return result;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
