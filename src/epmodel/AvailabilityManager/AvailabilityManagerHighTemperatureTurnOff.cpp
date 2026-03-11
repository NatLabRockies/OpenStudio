/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "AvailabilityManager/AvailabilityManagerHighTemperatureTurnOff.hpp"
#include "AvailabilityManager/AvailabilityManagerHighTemperatureTurnOff_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/AvailabilityManager_HighTemperatureTurnOff_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

AvailabilityManagerHighTemperatureTurnOff::AvailabilityManagerHighTemperatureTurnOff(const Model& model)
  : ModelObject(AvailabilityManagerHighTemperatureTurnOff::iddObjectType(), model) {
  setTemperature(30.0);
}

AvailabilityManagerHighTemperatureTurnOff::AvailabilityManagerHighTemperatureTurnOff(
  std::shared_ptr<detail::AvailabilityManagerHighTemperatureTurnOff_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType AvailabilityManagerHighTemperatureTurnOff::iddObjectType() {
  return IddObjectType::AvailabilityManager_HighTemperatureTurnOff;
}

double AvailabilityManagerHighTemperatureTurnOff::temperature() const {
  return getImpl<detail::AvailabilityManagerHighTemperatureTurnOff_Impl>()->temperature();
}

bool AvailabilityManagerHighTemperatureTurnOff::setTemperature(double temperature) {
  return getImpl<detail::AvailabilityManagerHighTemperatureTurnOff_Impl>()->setTemperature(temperature);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

double AvailabilityManagerHighTemperatureTurnOff_Impl::temperature() const {
  const auto value = getDouble(openstudio::AvailabilityManager_HighTemperatureTurnOffFields::Temperature, true);
  OS_ASSERT(value);
  return *value;
}

bool AvailabilityManagerHighTemperatureTurnOff_Impl::setTemperature(double temperature) {
  const bool result = setDouble(openstudio::AvailabilityManager_HighTemperatureTurnOffFields::Temperature, temperature);
  OS_ASSERT(result);
  return result;
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
