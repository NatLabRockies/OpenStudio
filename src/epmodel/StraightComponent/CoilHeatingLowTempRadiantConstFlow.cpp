/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/CoilHeatingLowTempRadiantConstFlow.hpp"
#include "StraightComponent/CoilHeatingLowTempRadiantConstFlow_Impl.hpp"

#include "Model.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"
#include "StraightComponent/Node.hpp"
#include "ZoneHVACComponent/ZoneHVACLowTempRadiantConstFlow.hpp"
#include "ZoneHVACComponent/ZoneHVACLowTempRadiantConstFlow_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/OS_Coil_Heating_LowTemperatureRadiant_ConstantFlow_FieldEnums.hxx>
#include <utilities/idd/ZoneHVAC_LowTemperatureRadiant_ConstantFlow_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

CoilHeatingLowTempRadiantConstFlow::CoilHeatingLowTempRadiantConstFlow(const Model& model)
  : StraightComponent(CoilHeatingLowTempRadiantConstFlow::iddObjectType(), model, false, true) {}

CoilHeatingLowTempRadiantConstFlow::CoilHeatingLowTempRadiantConstFlow(std::shared_ptr<detail::CoilHeatingLowTempRadiantConstFlow_Impl> impl)
  : StraightComponent(std::move(impl)) {}

IddObjectType CoilHeatingLowTempRadiantConstFlow::iddObjectType() {
  return IddObjectType::OS_Coil_Heating_LowTemperatureRadiant_ConstantFlow;
}

boost::optional<Schedule> CoilHeatingLowTempRadiantConstFlow::heatingHighWaterTemperatureSchedule() const {
  return getImpl<detail::CoilHeatingLowTempRadiantConstFlow_Impl>()->heatingHighWaterTemperatureSchedule();
}

boost::optional<Schedule> CoilHeatingLowTempRadiantConstFlow::heatingLowWaterTemperatureSchedule() const {
  return getImpl<detail::CoilHeatingLowTempRadiantConstFlow_Impl>()->heatingLowWaterTemperatureSchedule();
}

boost::optional<Schedule> CoilHeatingLowTempRadiantConstFlow::heatingHighControlTemperatureSchedule() const {
  return getImpl<detail::CoilHeatingLowTempRadiantConstFlow_Impl>()->heatingHighControlTemperatureSchedule();
}

boost::optional<Schedule> CoilHeatingLowTempRadiantConstFlow::heatingLowControlTemperatureSchedule() const {
  return getImpl<detail::CoilHeatingLowTempRadiantConstFlow_Impl>()->heatingLowControlTemperatureSchedule();
}

bool CoilHeatingLowTempRadiantConstFlow::setHeatingHighWaterTemperatureSchedule(Schedule& schedule) {
  return getImpl<detail::CoilHeatingLowTempRadiantConstFlow_Impl>()->setHeatingHighWaterTemperatureSchedule(schedule);
}

void CoilHeatingLowTempRadiantConstFlow::resetHeatingHighWaterTemperatureSchedule() {
  getImpl<detail::CoilHeatingLowTempRadiantConstFlow_Impl>()->resetHeatingHighWaterTemperatureSchedule();
}

bool CoilHeatingLowTempRadiantConstFlow::setHeatingLowWaterTemperatureSchedule(Schedule& schedule) {
  return getImpl<detail::CoilHeatingLowTempRadiantConstFlow_Impl>()->setHeatingLowWaterTemperatureSchedule(schedule);
}

void CoilHeatingLowTempRadiantConstFlow::resetHeatingLowWaterTemperatureSchedule() {
  getImpl<detail::CoilHeatingLowTempRadiantConstFlow_Impl>()->resetHeatingLowWaterTemperatureSchedule();
}

bool CoilHeatingLowTempRadiantConstFlow::setHeatingHighControlTemperatureSchedule(Schedule& schedule) {
  return getImpl<detail::CoilHeatingLowTempRadiantConstFlow_Impl>()->setHeatingHighControlTemperatureSchedule(schedule);
}

void CoilHeatingLowTempRadiantConstFlow::resetHeatingHighControlTemperatureSchedule() {
  getImpl<detail::CoilHeatingLowTempRadiantConstFlow_Impl>()->resetHeatingHighControlTemperatureSchedule();
}

bool CoilHeatingLowTempRadiantConstFlow::setHeatingLowControlTemperatureSchedule(Schedule& schedule) {
  return getImpl<detail::CoilHeatingLowTempRadiantConstFlow_Impl>()->setHeatingLowControlTemperatureSchedule(schedule);
}

void CoilHeatingLowTempRadiantConstFlow::resetHeatingLowControlTemperatureSchedule() {
  getImpl<detail::CoilHeatingLowTempRadiantConstFlow_Impl>()->resetHeatingLowControlTemperatureSchedule();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

unsigned CoilHeatingLowTempRadiantConstFlow_Impl::inletPort() const {
  return openstudio::OS_Coil_Heating_LowTemperatureRadiant_ConstantFlowFields::HeatingWaterInletNodeName;
}

unsigned CoilHeatingLowTempRadiantConstFlow_Impl::outletPort() const {
  return openstudio::OS_Coil_Heating_LowTemperatureRadiant_ConstantFlowFields::HeatingWaterOutletNodeName;
}

boost::optional<ModelObject> CoilHeatingLowTempRadiantConstFlow_Impl::inletModelObject() const {
  if (auto p = parent()) {
    if (auto node = p->getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->resolvedNodeTarget(
          openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::HeatingWaterInletNodeName)) {
      return node->cast<ModelObject>();
    }
  }
  return boost::none;
}

boost::optional<ModelObject> CoilHeatingLowTempRadiantConstFlow_Impl::outletModelObject() const {
  if (auto p = parent()) {
    if (auto node = p->getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->resolvedNodeTarget(
          openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::HeatingWaterOutletNodeName)) {
      return node->cast<ModelObject>();
    }
  }
  return boost::none;
}

bool CoilHeatingLowTempRadiantConstFlow_Impl::addToNode(Node& /*node*/) {
  // This transient child is only a view over parent-owned radiant storage.
  return false;
}

bool CoilHeatingLowTempRadiantConstFlow_Impl::removeFromLoop() {
  return false;
}

void CoilHeatingLowTempRadiantConstFlow_Impl::disconnect() {}

boost::optional<ZoneHVACLowTempRadiantConstFlow> CoilHeatingLowTempRadiantConstFlow_Impl::parent() const {
  const auto thisName = getObject<openstudio::epmodel::CoilHeatingLowTempRadiantConstFlow>().name();
  if (!thisName) {
    return boost::none;
  }

  // This is intentionally a name-based reverse lookup for now. These transient
  // companion coils are not persisted EnergyPlus objects, and today they do not
  // carry an explicit parent handle. The stable transient name gives us a way
  // to recover the owning radiant parent without inventing fake persisted
  // relationship fields. It works, but it is also a sign that a future
  // transient-ownership mechanism could be cleaner than reverse name matching.
  for (const auto& candidate : model().getConcreteModelObjects<openstudio::epmodel::ZoneHVACLowTempRadiantConstFlow>()) {
    if (openstudio::istringEqual(*thisName, detail::transientHeatingCoilName(candidate))) {
      return candidate;
    }
  }
  return boost::none;
}

boost::optional<Schedule> CoilHeatingLowTempRadiantConstFlow_Impl::heatingHighWaterTemperatureSchedule() const {
  if (auto p = parent()) {
    return p->getModelObjectTarget<Schedule>(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::HeatingHighWaterTemperatureScheduleName);
  }
  return boost::none;
}

boost::optional<Schedule> CoilHeatingLowTempRadiantConstFlow_Impl::heatingLowWaterTemperatureSchedule() const {
  if (auto p = parent()) {
    return p->getModelObjectTarget<Schedule>(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::HeatingLowWaterTemperatureScheduleName);
  }
  return boost::none;
}

boost::optional<Schedule> CoilHeatingLowTempRadiantConstFlow_Impl::heatingHighControlTemperatureSchedule() const {
  if (auto p = parent()) {
    return p->getModelObjectTarget<Schedule>(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::HeatingHighControlTemperatureScheduleName);
  }
  return boost::none;
}

boost::optional<Schedule> CoilHeatingLowTempRadiantConstFlow_Impl::heatingLowControlTemperatureSchedule() const {
  if (auto p = parent()) {
    return p->getModelObjectTarget<Schedule>(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::HeatingLowControlTemperatureScheduleName);
  }
  return boost::none;
}

bool CoilHeatingLowTempRadiantConstFlow_Impl::setHeatingHighWaterTemperatureSchedule(Schedule& schedule) {
  if (auto p = parent()) {
    return p->setPointer(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::HeatingHighWaterTemperatureScheduleName,
                         schedule.handle());
  }
  return false;
}

void CoilHeatingLowTempRadiantConstFlow_Impl::resetHeatingHighWaterTemperatureSchedule() {
  if (auto p = parent()) {
    OS_ASSERT(p->setString(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::HeatingHighWaterTemperatureScheduleName, ""));
  }
}

bool CoilHeatingLowTempRadiantConstFlow_Impl::setHeatingLowWaterTemperatureSchedule(Schedule& schedule) {
  if (auto p = parent()) {
    return p->setPointer(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::HeatingLowWaterTemperatureScheduleName,
                         schedule.handle());
  }
  return false;
}

void CoilHeatingLowTempRadiantConstFlow_Impl::resetHeatingLowWaterTemperatureSchedule() {
  if (auto p = parent()) {
    OS_ASSERT(p->setString(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::HeatingLowWaterTemperatureScheduleName, ""));
  }
}

bool CoilHeatingLowTempRadiantConstFlow_Impl::setHeatingHighControlTemperatureSchedule(Schedule& schedule) {
  if (auto p = parent()) {
    return p->setPointer(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::HeatingHighControlTemperatureScheduleName,
                         schedule.handle());
  }
  return false;
}

void CoilHeatingLowTempRadiantConstFlow_Impl::resetHeatingHighControlTemperatureSchedule() {
  if (auto p = parent()) {
    OS_ASSERT(p->setString(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::HeatingHighControlTemperatureScheduleName, ""));
  }
}

bool CoilHeatingLowTempRadiantConstFlow_Impl::setHeatingLowControlTemperatureSchedule(Schedule& schedule) {
  if (auto p = parent()) {
    return p->setPointer(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::HeatingLowControlTemperatureScheduleName,
                         schedule.handle());
  }
  return false;
}

void CoilHeatingLowTempRadiantConstFlow_Impl::resetHeatingLowControlTemperatureSchedule() {
  if (auto p = parent()) {
    OS_ASSERT(p->setString(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::HeatingLowControlTemperatureScheduleName, ""));
  }
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
