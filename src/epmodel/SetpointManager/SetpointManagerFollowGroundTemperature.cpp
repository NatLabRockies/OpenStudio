/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SetpointManager/SetpointManagerFollowGroundTemperature.hpp"
#include "SetpointManager/SetpointManagerFollowGroundTemperature_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/SetpointManager_FollowGroundTemperature_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

SetpointManagerFollowGroundTemperature::SetpointManagerFollowGroundTemperature(const Model& model)
  : SetpointManager(SetpointManagerFollowGroundTemperature::iddObjectType(), model) {
  auto impl = getImpl<detail::SetpointManagerFollowGroundTemperature_Impl>();
  OS_ASSERT(impl);
  OS_ASSERT(setControlVariable("Temperature"));
  OS_ASSERT(setOffsetTemperatureDifference(0.0));
  OS_ASSERT(setMaximumSetpointTemperature(80.0));
  OS_ASSERT(setMinimumSetpointTemperature(10.0));
  detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
  impl->canonicalize(context);
}

SetpointManagerFollowGroundTemperature::SetpointManagerFollowGroundTemperature(
  std::shared_ptr<detail::SetpointManagerFollowGroundTemperature_Impl> impl)
  : SetpointManager(std::move(impl)) {}

IddObjectType SetpointManagerFollowGroundTemperature::iddObjectType() {
  return IddObjectType::SetpointManager_FollowGroundTemperature;
}

std::vector<std::string> SetpointManagerFollowGroundTemperature::controlVariableValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::SetpointManager_FollowGroundTemperatureFields::ControlVariable);
}

std::vector<std::string> SetpointManagerFollowGroundTemperature::referenceGroundTemperatureObjectTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::SetpointManager_FollowGroundTemperatureFields::ReferenceGroundTemperatureObjectType);
}

std::string SetpointManagerFollowGroundTemperature::referenceGroundTemperatureObjectType() const {
  return getImpl<detail::SetpointManagerFollowGroundTemperature_Impl>()->referenceGroundTemperatureObjectType();
}

double SetpointManagerFollowGroundTemperature::offsetTemperatureDifference() const {
  return getImpl<detail::SetpointManagerFollowGroundTemperature_Impl>()->offsetTemperatureDifference();
}

double SetpointManagerFollowGroundTemperature::maximumSetpointTemperature() const {
  return getImpl<detail::SetpointManagerFollowGroundTemperature_Impl>()->maximumSetpointTemperature();
}

double SetpointManagerFollowGroundTemperature::minimumSetpointTemperature() const {
  return getImpl<detail::SetpointManagerFollowGroundTemperature_Impl>()->minimumSetpointTemperature();
}

bool SetpointManagerFollowGroundTemperature::setReferenceGroundTemperatureObjectType(const std::string& groundTemperatureObjType) {
  return getImpl<detail::SetpointManagerFollowGroundTemperature_Impl>()->setReferenceGroundTemperatureObjectType(groundTemperatureObjType);
}

bool SetpointManagerFollowGroundTemperature::setOffsetTemperatureDifference(double offsetTemperatureDifference) {
  const bool result = getImpl<detail::SetpointManagerFollowGroundTemperature_Impl>()->setOffsetTemperatureDifference(offsetTemperatureDifference);
  OS_ASSERT(result);
  return result;
}

bool SetpointManagerFollowGroundTemperature::setMaximumSetpointTemperature(double maximumSetpointTemperature) {
  const bool result = getImpl<detail::SetpointManagerFollowGroundTemperature_Impl>()->setMaximumSetpointTemperature(maximumSetpointTemperature);
  OS_ASSERT(result);
  return result;
}

bool SetpointManagerFollowGroundTemperature::setMinimumSetpointTemperature(double minimumSetpointTemperature) {
  const bool result = getImpl<detail::SetpointManagerFollowGroundTemperature_Impl>()->setMinimumSetpointTemperature(minimumSetpointTemperature);
  OS_ASSERT(result);
  return result;
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

std::string SetpointManagerFollowGroundTemperature_Impl::referenceGroundTemperatureObjectType() const {
  const auto value = getString(openstudio::SetpointManager_FollowGroundTemperatureFields::ReferenceGroundTemperatureObjectType, true);
  OS_ASSERT(value);
  return *value;
}

double SetpointManagerFollowGroundTemperature_Impl::offsetTemperatureDifference() const {
  const auto value = getDouble(openstudio::SetpointManager_FollowGroundTemperatureFields::OffsetTemperatureDifference, true);
  OS_ASSERT(value);
  return *value;
}

double SetpointManagerFollowGroundTemperature_Impl::maximumSetpointTemperature() const {
  const auto value = getDouble(openstudio::SetpointManager_FollowGroundTemperatureFields::MaximumSetpointTemperature, true);
  OS_ASSERT(value);
  return *value;
}

double SetpointManagerFollowGroundTemperature_Impl::minimumSetpointTemperature() const {
  const auto value = getDouble(openstudio::SetpointManager_FollowGroundTemperatureFields::MinimumSetpointTemperature, true);
  OS_ASSERT(value);
  return *value;
}

bool SetpointManagerFollowGroundTemperature_Impl::setReferenceGroundTemperatureObjectType(const std::string& groundTemperatureObjType) {
  return setString(openstudio::SetpointManager_FollowGroundTemperatureFields::ReferenceGroundTemperatureObjectType, groundTemperatureObjType);
}

bool SetpointManagerFollowGroundTemperature_Impl::setOffsetTemperatureDifference(double offsetTemperatureDifference) {
  const bool result = setDouble(openstudio::SetpointManager_FollowGroundTemperatureFields::OffsetTemperatureDifference, offsetTemperatureDifference);
  OS_ASSERT(result);
  return result;
}

bool SetpointManagerFollowGroundTemperature_Impl::setMaximumSetpointTemperature(double maximumSetpointTemperature) {
  const bool result = setDouble(openstudio::SetpointManager_FollowGroundTemperatureFields::MaximumSetpointTemperature, maximumSetpointTemperature);
  OS_ASSERT(result);
  return result;
}

bool SetpointManagerFollowGroundTemperature_Impl::setMinimumSetpointTemperature(double minimumSetpointTemperature) {
  const bool result = setDouble(openstudio::SetpointManager_FollowGroundTemperatureFields::MinimumSetpointTemperature, minimumSetpointTemperature);
  OS_ASSERT(result);
  return result;
}

unsigned SetpointManagerFollowGroundTemperature_Impl::setpointNodeFieldIndex() const {
  return openstudio::SetpointManager_FollowGroundTemperatureFields::SetpointNodeorNodeListName;
}

unsigned SetpointManagerFollowGroundTemperature_Impl::controlVariableFieldIndex() const {
  return openstudio::SetpointManager_FollowGroundTemperatureFields::ControlVariable;
}

void SetpointManagerFollowGroundTemperature_Impl::doCanonicalize(LoadContext& context) {
  SetpointManager_Impl::doCanonicalize(context);

  if (auto value = getString(openstudio::SetpointManager_FollowGroundTemperatureFields::ControlVariable, true)) {
    if (!value->empty()) {
      // continue
    } else {
      OS_ASSERT(setString(openstudio::SetpointManager_FollowGroundTemperatureFields::ControlVariable, "Temperature"));
      detail::addLoadInfo(context, "Set default Control Variable to 'Temperature' for SetpointManager:FollowGroundTemperature '"
                                     + getObject<ModelObject>().nameString() + "'.");
    }
  } else {
    OS_ASSERT(setString(openstudio::SetpointManager_FollowGroundTemperatureFields::ControlVariable, "Temperature"));
    detail::addLoadInfo(context, "Set default Control Variable to 'Temperature' for SetpointManager:FollowGroundTemperature '"
                                   + getObject<ModelObject>().nameString() + "'.");
  }

  if (auto value = getString(openstudio::SetpointManager_FollowGroundTemperatureFields::ReferenceGroundTemperatureObjectType, true)) {
    if (!value->empty()) {
      // continue
    } else {
      OS_ASSERT(setString(openstudio::SetpointManager_FollowGroundTemperatureFields::ReferenceGroundTemperatureObjectType,
                          "Site:GroundTemperature:BuildingSurface"));
      detail::addLoadInfo(context,
                          "Set default Reference Ground Temperature Object Type to 'Site:GroundTemperature:BuildingSurface' for "
                          "SetpointManager:FollowGroundTemperature '"
                            + getObject<ModelObject>().nameString() + "'.");
    }
  } else {
    OS_ASSERT(
      setString(openstudio::SetpointManager_FollowGroundTemperatureFields::ReferenceGroundTemperatureObjectType,
                "Site:GroundTemperature:BuildingSurface"));
    detail::addLoadInfo(context,
                        "Set default Reference Ground Temperature Object Type to 'Site:GroundTemperature:BuildingSurface' for "
                        "SetpointManager:FollowGroundTemperature '"
                          + getObject<ModelObject>().nameString() + "'.");
  }

  if (auto value = getDouble(openstudio::SetpointManager_FollowGroundTemperatureFields::OffsetTemperatureDifference, true)) {
    (void)value;
  } else {
    OS_ASSERT(setDouble(openstudio::SetpointManager_FollowGroundTemperatureFields::OffsetTemperatureDifference, 0.0));
    detail::addLoadInfo(context, "Set default Offset Temperature Difference to 0 for SetpointManager:FollowGroundTemperature '"
                                   + getObject<ModelObject>().nameString() + "'.");
  }

  if (auto value = getDouble(openstudio::SetpointManager_FollowGroundTemperatureFields::MaximumSetpointTemperature, true)) {
    (void)value;
  } else {
    OS_ASSERT(setDouble(openstudio::SetpointManager_FollowGroundTemperatureFields::MaximumSetpointTemperature, 80.0));
    detail::addLoadInfo(context, "Set default Maximum Setpoint Temperature to 80 for SetpointManager:FollowGroundTemperature '"
                                   + getObject<ModelObject>().nameString() + "'.");
  }

  if (auto value = getDouble(openstudio::SetpointManager_FollowGroundTemperatureFields::MinimumSetpointTemperature, true)) {
    (void)value;
  } else {
    OS_ASSERT(setDouble(openstudio::SetpointManager_FollowGroundTemperatureFields::MinimumSetpointTemperature, 10.0));
    detail::addLoadInfo(context, "Set default Minimum Setpoint Temperature to 10 for SetpointManager:FollowGroundTemperature '"
                                   + getObject<ModelObject>().nameString() + "'.");
  }
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
