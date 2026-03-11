/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "AvailabilityManager/AvailabilityManagerLowTemperatureTurnOn.hpp"
#include "AvailabilityManager/AvailabilityManagerLowTemperatureTurnOn_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/AvailabilityManager_LowTemperatureTurnOn_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

AvailabilityManagerLowTemperatureTurnOn::AvailabilityManagerLowTemperatureTurnOn(const Model& model)
  : ModelObject(AvailabilityManagerLowTemperatureTurnOn::iddObjectType(), model) {
  setTemperature(30.0);
}

AvailabilityManagerLowTemperatureTurnOn::AvailabilityManagerLowTemperatureTurnOn(
  std::shared_ptr<detail::AvailabilityManagerLowTemperatureTurnOn_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType AvailabilityManagerLowTemperatureTurnOn::iddObjectType() {
  return IddObjectType::AvailabilityManager_LowTemperatureTurnOn;
}

double AvailabilityManagerLowTemperatureTurnOn::temperature() const {
  return getImpl<detail::AvailabilityManagerLowTemperatureTurnOn_Impl>()->temperature();
}

bool AvailabilityManagerLowTemperatureTurnOn::setTemperature(double temperature) {
  return getImpl<detail::AvailabilityManagerLowTemperatureTurnOn_Impl>()->setTemperature(temperature);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

double AvailabilityManagerLowTemperatureTurnOn_Impl::temperature() const {
  const auto value = getDouble(openstudio::AvailabilityManager_LowTemperatureTurnOnFields::Temperature, true);
  OS_ASSERT(value);
  return *value;
}

bool AvailabilityManagerLowTemperatureTurnOn_Impl::setTemperature(double temperature) {
  const bool result = setDouble(openstudio::AvailabilityManager_LowTemperatureTurnOnFields::Temperature, temperature);
  OS_ASSERT(result);
  return result;
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
