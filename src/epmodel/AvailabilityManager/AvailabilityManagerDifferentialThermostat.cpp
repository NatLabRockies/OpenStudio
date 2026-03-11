/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "AvailabilityManager/AvailabilityManagerDifferentialThermostat.hpp"
#include "AvailabilityManager/AvailabilityManagerDifferentialThermostat_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/AvailabilityManager_DifferentialThermostat_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

AvailabilityManagerDifferentialThermostat::AvailabilityManagerDifferentialThermostat(const Model& model)
  : ModelObject(AvailabilityManagerDifferentialThermostat::iddObjectType(), model) {
  setTemperatureDifferenceOnLimit(10.0);
  setTemperatureDifferenceOffLimit(2.0);
}

AvailabilityManagerDifferentialThermostat::AvailabilityManagerDifferentialThermostat(
  std::shared_ptr<detail::AvailabilityManagerDifferentialThermostat_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType AvailabilityManagerDifferentialThermostat::iddObjectType() {
  return IddObjectType::AvailabilityManager_DifferentialThermostat;
}

double AvailabilityManagerDifferentialThermostat::temperatureDifferenceOnLimit() const {
  return getImpl<detail::AvailabilityManagerDifferentialThermostat_Impl>()->temperatureDifferenceOnLimit();
}

bool AvailabilityManagerDifferentialThermostat::setTemperatureDifferenceOnLimit(double temperatureDifferenceOnLimit) {
  return getImpl<detail::AvailabilityManagerDifferentialThermostat_Impl>()->setTemperatureDifferenceOnLimit(temperatureDifferenceOnLimit);
}

double AvailabilityManagerDifferentialThermostat::temperatureDifferenceOffLimit() const {
  return getImpl<detail::AvailabilityManagerDifferentialThermostat_Impl>()->temperatureDifferenceOffLimit();
}

bool AvailabilityManagerDifferentialThermostat::setTemperatureDifferenceOffLimit(double temperatureDifferenceOffLimit) {
  return getImpl<detail::AvailabilityManagerDifferentialThermostat_Impl>()->setTemperatureDifferenceOffLimit(temperatureDifferenceOffLimit);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

double AvailabilityManagerDifferentialThermostat_Impl::temperatureDifferenceOnLimit() const {
  const auto value = getDouble(openstudio::AvailabilityManager_DifferentialThermostatFields::TemperatureDifferenceOnLimit, true);
  OS_ASSERT(value);
  return *value;
}

bool AvailabilityManagerDifferentialThermostat_Impl::setTemperatureDifferenceOnLimit(double temperatureDifferenceOnLimit) {
  const bool result = setDouble(openstudio::AvailabilityManager_DifferentialThermostatFields::TemperatureDifferenceOnLimit,
                                temperatureDifferenceOnLimit);
  OS_ASSERT(result);
  return result;
}

double AvailabilityManagerDifferentialThermostat_Impl::temperatureDifferenceOffLimit() const {
  const auto value = getDouble(openstudio::AvailabilityManager_DifferentialThermostatFields::TemperatureDifferenceOffLimit, true);
  OS_ASSERT(value);
  return *value;
}

bool AvailabilityManagerDifferentialThermostat_Impl::setTemperatureDifferenceOffLimit(double temperatureDifferenceOffLimit) {
  const bool result = setDouble(openstudio::AvailabilityManager_DifferentialThermostatFields::TemperatureDifferenceOffLimit,
                                temperatureDifferenceOffLimit);
  OS_ASSERT(result);
  return result;
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
