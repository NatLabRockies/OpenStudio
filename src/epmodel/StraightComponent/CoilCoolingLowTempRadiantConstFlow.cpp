/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/CoilCoolingLowTempRadiantConstFlow.hpp"
#include "StraightComponent/CoilCoolingLowTempRadiantConstFlow_Impl.hpp"

#include "Model.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"
#include "StraightComponent/Node.hpp"
#include "ZoneHVACComponent/ZoneHVACLowTempRadiantConstFlow.hpp"
#include "ModelObject/ZoneHVACLowTempRadiantConstFlowDesign.hpp"
#include "ModelObject/ZoneHVACLowTempRadiantConstFlowDesign_Impl.hpp"
#include "ZoneHVACComponent/ZoneHVACLowTempRadiantConstFlow_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/OS_Coil_Cooling_LowTemperatureRadiant_ConstantFlow_FieldEnums.hxx>
#include <utilities/idd/ZoneHVAC_LowTemperatureRadiant_ConstantFlow_FieldEnums.hxx>
#include <utilities/idd/ZoneHVAC_LowTemperatureRadiant_ConstantFlow_Design_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

CoilCoolingLowTempRadiantConstFlow::CoilCoolingLowTempRadiantConstFlow(const Model& model)
  : StraightComponent(CoilCoolingLowTempRadiantConstFlow::iddObjectType(), model, false, true) {}

CoilCoolingLowTempRadiantConstFlow::CoilCoolingLowTempRadiantConstFlow(std::shared_ptr<detail::CoilCoolingLowTempRadiantConstFlow_Impl> impl)
  : StraightComponent(std::move(impl)) {}

IddObjectType CoilCoolingLowTempRadiantConstFlow::iddObjectType() {
  return IddObjectType::OS_Coil_Cooling_LowTemperatureRadiant_ConstantFlow;
}

boost::optional<Schedule> CoilCoolingLowTempRadiantConstFlow::coolingHighWaterTemperatureSchedule() const {
  return getImpl<detail::CoilCoolingLowTempRadiantConstFlow_Impl>()->coolingHighWaterTemperatureSchedule();
}

boost::optional<Schedule> CoilCoolingLowTempRadiantConstFlow::coolingLowWaterTemperatureSchedule() const {
  return getImpl<detail::CoilCoolingLowTempRadiantConstFlow_Impl>()->coolingLowWaterTemperatureSchedule();
}

boost::optional<Schedule> CoilCoolingLowTempRadiantConstFlow::coolingHighControlTemperatureSchedule() const {
  return getImpl<detail::CoilCoolingLowTempRadiantConstFlow_Impl>()->coolingHighControlTemperatureSchedule();
}

boost::optional<Schedule> CoilCoolingLowTempRadiantConstFlow::coolingLowControlTemperatureSchedule() const {
  return getImpl<detail::CoilCoolingLowTempRadiantConstFlow_Impl>()->coolingLowControlTemperatureSchedule();
}

std::string CoilCoolingLowTempRadiantConstFlow::condensationControlType() const {
  return getImpl<detail::CoilCoolingLowTempRadiantConstFlow_Impl>()->condensationControlType();
}

bool CoilCoolingLowTempRadiantConstFlow::isCondensationControlTypeDefaulted() const {
  return getImpl<detail::CoilCoolingLowTempRadiantConstFlow_Impl>()->isCondensationControlTypeDefaulted();
}

double CoilCoolingLowTempRadiantConstFlow::condensationControlDewpointOffset() const {
  return getImpl<detail::CoilCoolingLowTempRadiantConstFlow_Impl>()->condensationControlDewpointOffset();
}

bool CoilCoolingLowTempRadiantConstFlow::isCondensationControlDewpointOffsetDefaulted() const {
  return getImpl<detail::CoilCoolingLowTempRadiantConstFlow_Impl>()->isCondensationControlDewpointOffsetDefaulted();
}

bool CoilCoolingLowTempRadiantConstFlow::setCoolingHighWaterTemperatureSchedule(Schedule& schedule) {
  return getImpl<detail::CoilCoolingLowTempRadiantConstFlow_Impl>()->setCoolingHighWaterTemperatureSchedule(schedule);
}

void CoilCoolingLowTempRadiantConstFlow::resetCoolingHighWaterTemperatureSchedule() {
  getImpl<detail::CoilCoolingLowTempRadiantConstFlow_Impl>()->resetCoolingHighWaterTemperatureSchedule();
}

bool CoilCoolingLowTempRadiantConstFlow::setCoolingLowWaterTemperatureSchedule(Schedule& schedule) {
  return getImpl<detail::CoilCoolingLowTempRadiantConstFlow_Impl>()->setCoolingLowWaterTemperatureSchedule(schedule);
}

void CoilCoolingLowTempRadiantConstFlow::resetCoolingLowWaterTemperatureSchedule() {
  getImpl<detail::CoilCoolingLowTempRadiantConstFlow_Impl>()->resetCoolingLowWaterTemperatureSchedule();
}

bool CoilCoolingLowTempRadiantConstFlow::setCoolingHighControlTemperatureSchedule(Schedule& schedule) {
  return getImpl<detail::CoilCoolingLowTempRadiantConstFlow_Impl>()->setCoolingHighControlTemperatureSchedule(schedule);
}

void CoilCoolingLowTempRadiantConstFlow::resetCoolingHighControlTemperatureSchedule() {
  getImpl<detail::CoilCoolingLowTempRadiantConstFlow_Impl>()->resetCoolingHighControlTemperatureSchedule();
}

bool CoilCoolingLowTempRadiantConstFlow::setCoolingLowControlTemperatureSchedule(Schedule& schedule) {
  return getImpl<detail::CoilCoolingLowTempRadiantConstFlow_Impl>()->setCoolingLowControlTemperatureSchedule(schedule);
}

void CoilCoolingLowTempRadiantConstFlow::resetCoolingLowControlTemperatureSchedule() {
  getImpl<detail::CoilCoolingLowTempRadiantConstFlow_Impl>()->resetCoolingLowControlTemperatureSchedule();
}

bool CoilCoolingLowTempRadiantConstFlow::setCondensationControlType(const std::string& condensationControlType) {
  return getImpl<detail::CoilCoolingLowTempRadiantConstFlow_Impl>()->setCondensationControlType(condensationControlType);
}

void CoilCoolingLowTempRadiantConstFlow::resetCondensationControlType() {
  getImpl<detail::CoilCoolingLowTempRadiantConstFlow_Impl>()->resetCondensationControlType();
}

bool CoilCoolingLowTempRadiantConstFlow::setCondensationControlDewpointOffset(double condensationControlDewpointOffset) {
  return getImpl<detail::CoilCoolingLowTempRadiantConstFlow_Impl>()->setCondensationControlDewpointOffset(condensationControlDewpointOffset);
}

void CoilCoolingLowTempRadiantConstFlow::resetCondensationControlDewpointOffset() {
  getImpl<detail::CoilCoolingLowTempRadiantConstFlow_Impl>()->resetCondensationControlDewpointOffset();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

constexpr const char* kDefaultCondensationControlType = "SimpleOff";
constexpr double kDefaultCondensationControlDewpointOffset = 1.0;

unsigned CoilCoolingLowTempRadiantConstFlow_Impl::inletPort() const {
  return openstudio::OS_Coil_Cooling_LowTemperatureRadiant_ConstantFlowFields::CoolingWaterInletNodeName;
}

unsigned CoilCoolingLowTempRadiantConstFlow_Impl::outletPort() const {
  return openstudio::OS_Coil_Cooling_LowTemperatureRadiant_ConstantFlowFields::CoolingWaterOutletNodeName;
}

boost::optional<ModelObject> CoilCoolingLowTempRadiantConstFlow_Impl::inletModelObject() const {
  if (auto p = parent()) {
    if (auto node = p->getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->resolvedNodeTarget(
          openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::CoolingWaterInletNodeName)) {
      return node->cast<ModelObject>();
    }
  }
  return boost::none;
}

boost::optional<ModelObject> CoilCoolingLowTempRadiantConstFlow_Impl::outletModelObject() const {
  if (auto p = parent()) {
    if (auto node = p->getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->resolvedNodeTarget(
          openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::CoolingWaterOutletNodeName)) {
      return node->cast<ModelObject>();
    }
  }
  return boost::none;
}

bool CoilCoolingLowTempRadiantConstFlow_Impl::addToNode(Node& /*node*/) {
  // This transient child is only a view over parent-owned radiant storage.
  return false;
}

bool CoilCoolingLowTempRadiantConstFlow_Impl::removeFromLoop() {
  return false;
}

void CoilCoolingLowTempRadiantConstFlow_Impl::disconnect() {}

boost::optional<ZoneHVACLowTempRadiantConstFlow> CoilCoolingLowTempRadiantConstFlow_Impl::parent() const {
  const auto thisName = getObject<openstudio::epmodel::CoilCoolingLowTempRadiantConstFlow>().name();
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
    if (openstudio::istringEqual(*thisName, detail::transientCoolingCoilName(candidate))) {
      return candidate;
    }
  }
  return boost::none;
}

boost::optional<Schedule> CoilCoolingLowTempRadiantConstFlow_Impl::coolingHighWaterTemperatureSchedule() const {
  if (auto p = parent()) {
    return p->getModelObjectTarget<Schedule>(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::CoolingHighWaterTemperatureScheduleName);
  }
  return boost::none;
}

boost::optional<Schedule> CoilCoolingLowTempRadiantConstFlow_Impl::coolingLowWaterTemperatureSchedule() const {
  if (auto p = parent()) {
    return p->getModelObjectTarget<Schedule>(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::CoolingLowWaterTemperatureScheduleName);
  }
  return boost::none;
}

boost::optional<Schedule> CoilCoolingLowTempRadiantConstFlow_Impl::coolingHighControlTemperatureSchedule() const {
  if (auto p = parent()) {
    return p->getModelObjectTarget<Schedule>(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::CoolingHighControlTemperatureScheduleName);
  }
  return boost::none;
}

boost::optional<Schedule> CoilCoolingLowTempRadiantConstFlow_Impl::coolingLowControlTemperatureSchedule() const {
  if (auto p = parent()) {
    return p->getModelObjectTarget<Schedule>(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::CoolingLowControlTemperatureScheduleName);
  }
  return boost::none;
}

std::string CoilCoolingLowTempRadiantConstFlow_Impl::condensationControlType() const {
  if (auto p = parent()) {
    if (const auto design = p->getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->designObject()) {
      return design->getImpl<detail::ZoneHVACLowTempRadiantConstFlowDesign_Impl>()->condensationControlType();
    }
  }
  return kDefaultCondensationControlType;
}

bool CoilCoolingLowTempRadiantConstFlow_Impl::isCondensationControlTypeDefaulted() const {
  if (auto p = parent()) {
    if (const auto design = p->getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->designObject()) {
      return design->getImpl<detail::ZoneHVACLowTempRadiantConstFlowDesign_Impl>()->isCondensationControlTypeDefaulted();
    }
  }
  return true;
}

double CoilCoolingLowTempRadiantConstFlow_Impl::condensationControlDewpointOffset() const {
  if (auto p = parent()) {
    if (const auto design = p->getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->designObject()) {
      return design->getImpl<detail::ZoneHVACLowTempRadiantConstFlowDesign_Impl>()->condensationControlDewpointOffset();
    }
  }
  return kDefaultCondensationControlDewpointOffset;
}

bool CoilCoolingLowTempRadiantConstFlow_Impl::isCondensationControlDewpointOffsetDefaulted() const {
  if (auto p = parent()) {
    if (const auto design = p->getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->designObject()) {
      return design->getImpl<detail::ZoneHVACLowTempRadiantConstFlowDesign_Impl>()->isCondensationControlDewpointOffsetDefaulted();
    }
  }
  return true;
}

bool CoilCoolingLowTempRadiantConstFlow_Impl::setCoolingHighWaterTemperatureSchedule(Schedule& schedule) {
  if (auto p = parent()) {
    return p->setPointer(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::CoolingHighWaterTemperatureScheduleName,
                         schedule.handle());
  }
  return false;
}

void CoilCoolingLowTempRadiantConstFlow_Impl::resetCoolingHighWaterTemperatureSchedule() {
  if (auto p = parent()) {
    OS_ASSERT(p->setString(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::CoolingHighWaterTemperatureScheduleName, ""));
  }
}

bool CoilCoolingLowTempRadiantConstFlow_Impl::setCoolingLowWaterTemperatureSchedule(Schedule& schedule) {
  if (auto p = parent()) {
    return p->setPointer(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::CoolingLowWaterTemperatureScheduleName,
                         schedule.handle());
  }
  return false;
}

void CoilCoolingLowTempRadiantConstFlow_Impl::resetCoolingLowWaterTemperatureSchedule() {
  if (auto p = parent()) {
    OS_ASSERT(p->setString(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::CoolingLowWaterTemperatureScheduleName, ""));
  }
}

bool CoilCoolingLowTempRadiantConstFlow_Impl::setCoolingHighControlTemperatureSchedule(Schedule& schedule) {
  if (auto p = parent()) {
    return p->setPointer(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::CoolingHighControlTemperatureScheduleName,
                         schedule.handle());
  }
  return false;
}

void CoilCoolingLowTempRadiantConstFlow_Impl::resetCoolingHighControlTemperatureSchedule() {
  if (auto p = parent()) {
    OS_ASSERT(p->setString(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::CoolingHighControlTemperatureScheduleName, ""));
  }
}

bool CoilCoolingLowTempRadiantConstFlow_Impl::setCoolingLowControlTemperatureSchedule(Schedule& schedule) {
  if (auto p = parent()) {
    return p->setPointer(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::CoolingLowControlTemperatureScheduleName,
                         schedule.handle());
  }
  return false;
}

void CoilCoolingLowTempRadiantConstFlow_Impl::resetCoolingLowControlTemperatureSchedule() {
  if (auto p = parent()) {
    OS_ASSERT(p->setString(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::CoolingLowControlTemperatureScheduleName, ""));
  }
}

bool CoilCoolingLowTempRadiantConstFlow_Impl::setCondensationControlType(const std::string& condensationControlType) {
  if (auto p = parent()) {
    auto design = p->getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->ensureDesignObject();
    return design.getImpl<detail::ZoneHVACLowTempRadiantConstFlowDesign_Impl>()->setCondensationControlType(condensationControlType);
  }
  return false;
}

void CoilCoolingLowTempRadiantConstFlow_Impl::resetCondensationControlType() {
  if (auto p = parent()) {
    auto design = p->getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->ensureDesignObject();
    design.getImpl<detail::ZoneHVACLowTempRadiantConstFlowDesign_Impl>()->resetCondensationControlType();
  }
}

bool CoilCoolingLowTempRadiantConstFlow_Impl::setCondensationControlDewpointOffset(double condensationControlDewpointOffset) {
  if (auto p = parent()) {
    auto design = p->getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->ensureDesignObject();
    return design.getImpl<detail::ZoneHVACLowTempRadiantConstFlowDesign_Impl>()->setCondensationControlDewpointOffset(
      condensationControlDewpointOffset);
  }
  return false;
}

void CoilCoolingLowTempRadiantConstFlow_Impl::resetCondensationControlDewpointOffset() {
  if (auto p = parent()) {
    auto design = p->getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->ensureDesignObject();
    design.getImpl<detail::ZoneHVACLowTempRadiantConstFlowDesign_Impl>()->resetCondensationControlDewpointOffset();
  }
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
