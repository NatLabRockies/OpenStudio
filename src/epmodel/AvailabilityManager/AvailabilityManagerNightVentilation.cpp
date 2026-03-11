/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "AvailabilityManager/AvailabilityManagerNightVentilation.hpp"
#include "AvailabilityManager/AvailabilityManagerNightVentilation_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/AvailabilityManager_NightVentilation_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

AvailabilityManagerNightVentilation::AvailabilityManagerNightVentilation(const Model& model)
  : ModelObject(AvailabilityManagerNightVentilation::iddObjectType(), model) {
  setVentilationTemperatureDifference(2.0);
  setVentilationTemperatureLowLimit(15.0);
  setNightVentingFlowFraction(0.333);
}

AvailabilityManagerNightVentilation::AvailabilityManagerNightVentilation(
  std::shared_ptr<detail::AvailabilityManagerNightVentilation_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType AvailabilityManagerNightVentilation::iddObjectType() {
  return IddObjectType::AvailabilityManager_NightVentilation;
}

double AvailabilityManagerNightVentilation::ventilationTemperatureDifference() const {
  return getImpl<detail::AvailabilityManagerNightVentilation_Impl>()->ventilationTemperatureDifference();
}

bool AvailabilityManagerNightVentilation::setVentilationTemperatureDifference(double ventilationTemperatureDifference) {
  return getImpl<detail::AvailabilityManagerNightVentilation_Impl>()->setVentilationTemperatureDifference(ventilationTemperatureDifference);
}

double AvailabilityManagerNightVentilation::ventilationTemperatureLowLimit() const {
  return getImpl<detail::AvailabilityManagerNightVentilation_Impl>()->ventilationTemperatureLowLimit();
}

bool AvailabilityManagerNightVentilation::setVentilationTemperatureLowLimit(double ventilationTemperatureLowLimit) {
  return getImpl<detail::AvailabilityManagerNightVentilation_Impl>()->setVentilationTemperatureLowLimit(ventilationTemperatureLowLimit);
}

double AvailabilityManagerNightVentilation::nightVentingFlowFraction() const {
  return getImpl<detail::AvailabilityManagerNightVentilation_Impl>()->nightVentingFlowFraction();
}

bool AvailabilityManagerNightVentilation::setNightVentingFlowFraction(double nightVentingFlowFraction) {
  return getImpl<detail::AvailabilityManagerNightVentilation_Impl>()->setNightVentingFlowFraction(nightVentingFlowFraction);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

double AvailabilityManagerNightVentilation_Impl::ventilationTemperatureDifference() const {
  const auto value = getDouble(openstudio::AvailabilityManager_NightVentilationFields::VentilationTemperatureDifference, true);
  OS_ASSERT(value);
  return *value;
}

bool AvailabilityManagerNightVentilation_Impl::setVentilationTemperatureDifference(double ventilationTemperatureDifference) {
  const bool result =
    setDouble(openstudio::AvailabilityManager_NightVentilationFields::VentilationTemperatureDifference, ventilationTemperatureDifference);
  OS_ASSERT(result);
  return result;
}

double AvailabilityManagerNightVentilation_Impl::ventilationTemperatureLowLimit() const {
  const auto value = getDouble(openstudio::AvailabilityManager_NightVentilationFields::VentilationTemperatureLowLimit, true);
  OS_ASSERT(value);
  return *value;
}

bool AvailabilityManagerNightVentilation_Impl::setVentilationTemperatureLowLimit(double ventilationTemperatureLowLimit) {
  const bool result = setDouble(openstudio::AvailabilityManager_NightVentilationFields::VentilationTemperatureLowLimit, ventilationTemperatureLowLimit);
  OS_ASSERT(result);
  return result;
}

double AvailabilityManagerNightVentilation_Impl::nightVentingFlowFraction() const {
  const auto value = getDouble(openstudio::AvailabilityManager_NightVentilationFields::NightVentingFlowFraction, true);
  OS_ASSERT(value);
  return *value;
}

bool AvailabilityManagerNightVentilation_Impl::setNightVentingFlowFraction(double nightVentingFlowFraction) {
  return setDouble(openstudio::AvailabilityManager_NightVentilationFields::NightVentingFlowFraction, nightVentingFlowFraction);
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
