/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "AvailabilityManagerNightCycle.hpp"
#include "AvailabilityManagerNightCycle_Impl.hpp"

#include "AirLoopHVAC.hpp"
#include "AirLoopHVAC_Impl.hpp"
#include "Loop.hpp"
#include "Loop_Impl.hpp"
#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/AvailabilityManager_NightCycle_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

AvailabilityManagerNightCycle::AvailabilityManagerNightCycle(const Model& model)
  : AvailabilityManager(AvailabilityManagerNightCycle::iddObjectType(), model) {
  auto impl = getImpl<detail::AvailabilityManagerNightCycle_Impl>();
  OS_ASSERT(impl);
  detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
  impl->canonicalize(context);
}

AvailabilityManagerNightCycle::AvailabilityManagerNightCycle(std::shared_ptr<detail::AvailabilityManagerNightCycle_Impl> impl)
  : AvailabilityManager(std::move(impl)) {}

IddObjectType AvailabilityManagerNightCycle::iddObjectType() {
  return IddObjectType::AvailabilityManager_NightCycle;
}

std::vector<std::string> AvailabilityManagerNightCycle::controlTypeValues() {
  return {"StayOff", "CycleOnAny", "CycleOnControlZone", "CycleOnAnyZoneFansOnly", "CycleOnAnyCoolingOrHeatingZone",
          "CycleOnAnyCoolingZone", "CycleOnAnyHeatingZone", "CycleOnAnyHeatingZoneFansOnly"};
}

boost::optional<AirLoopHVAC> AvailabilityManagerNightCycle::airLoopHVAC() const {
  return getImpl<detail::AvailabilityManagerNightCycle_Impl>()->airLoopHVAC();
}

std::string AvailabilityManagerNightCycle::controlType() const {
  return getImpl<detail::AvailabilityManagerNightCycle_Impl>()->controlType();
}

bool AvailabilityManagerNightCycle::setControlType(const std::string& controlType) {
  return getImpl<detail::AvailabilityManagerNightCycle_Impl>()->setControlType(controlType);
}

void AvailabilityManagerNightCycle::resetControlType() {
  getImpl<detail::AvailabilityManagerNightCycle_Impl>()->resetControlType();
}

bool AvailabilityManagerNightCycle::isControlTypeDefaulted() const {
  return getImpl<detail::AvailabilityManagerNightCycle_Impl>()->isControlTypeDefaulted();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

boost::optional<openstudio::epmodel::AirLoopHVAC> AvailabilityManagerNightCycle_Impl::airLoopHVAC() const {
  auto owner = loop();
  if (!owner) {
    return boost::none;
  }
  return owner->optionalCast<openstudio::epmodel::AirLoopHVAC>();
}

std::string AvailabilityManagerNightCycle_Impl::controlType() const {
  if (auto value = getString(openstudio::AvailabilityManager_NightCycleFields::ControlType, true)) {
    return *value;
  }
  return "";
}

bool AvailabilityManagerNightCycle_Impl::setControlType(const std::string& controlType) {
  return setString(openstudio::AvailabilityManager_NightCycleFields::ControlType, controlType);
}

void AvailabilityManagerNightCycle_Impl::resetControlType() {
  OS_ASSERT(setString(openstudio::AvailabilityManager_NightCycleFields::ControlType, ""));
}

bool AvailabilityManagerNightCycle_Impl::isControlTypeDefaulted() const {
  return !getString(openstudio::AvailabilityManager_NightCycleFields::ControlType, false);
}

std::vector<std::string> AvailabilityManagerNightCycle_Impl::controlTypeValues() const {
  return openstudio::epmodel::AvailabilityManagerNightCycle::controlTypeValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
