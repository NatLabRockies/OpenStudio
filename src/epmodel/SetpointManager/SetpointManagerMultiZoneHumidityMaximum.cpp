/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SetpointManager/SetpointManagerMultiZoneHumidityMaximum.hpp"
#include "SetpointManager/SetpointManagerMultiZoneHumidityMaximum_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/Compare.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/SetpointManager_MultiZone_Humidity_Maximum_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

SetpointManagerMultiZoneHumidityMaximum::SetpointManagerMultiZoneHumidityMaximum(const Model& model)
  : SetpointManager(SetpointManagerMultiZoneHumidityMaximum::iddObjectType(), model) {
  auto impl = getImpl<detail::SetpointManagerMultiZoneHumidityMaximum_Impl>();
  OS_ASSERT(impl);
  OS_ASSERT(setMinimumSetpointHumidityRatio(0.008));
  OS_ASSERT(setMaximumSetpointHumidityRatio(0.015));
  detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
  impl->canonicalize(context);
}

SetpointManagerMultiZoneHumidityMaximum::SetpointManagerMultiZoneHumidityMaximum(
  std::shared_ptr<detail::SetpointManagerMultiZoneHumidityMaximum_Impl> impl)
  : SetpointManager(std::move(impl)) {}

IddObjectType SetpointManagerMultiZoneHumidityMaximum::iddObjectType() {
  return IddObjectType::SetpointManager_MultiZone_Humidity_Maximum;
}

std::vector<std::string> SetpointManagerMultiZoneHumidityMaximum::controlVariableValues() {
  return {"MaximumHumidityRatio"};
}

std::string SetpointManagerMultiZoneHumidityMaximum::controlVariable() const {
  return "MaximumHumidityRatio";
}

double SetpointManagerMultiZoneHumidityMaximum::minimumSetpointHumidityRatio() const {
  return getImpl<detail::SetpointManagerMultiZoneHumidityMaximum_Impl>()->minimumSetpointHumidityRatio();
}

double SetpointManagerMultiZoneHumidityMaximum::maximumSetpointHumidityRatio() const {
  return getImpl<detail::SetpointManagerMultiZoneHumidityMaximum_Impl>()->maximumSetpointHumidityRatio();
}

bool SetpointManagerMultiZoneHumidityMaximum::setControlVariable(const std::string& controlVariable) {
  return openstudio::istringEqual(controlVariable, "MaximumHumidityRatio");
}

bool SetpointManagerMultiZoneHumidityMaximum::setMinimumSetpointHumidityRatio(double minimumSetpointHumidityRatio) {
  const bool result = getImpl<detail::SetpointManagerMultiZoneHumidityMaximum_Impl>()->setMinimumSetpointHumidityRatio(minimumSetpointHumidityRatio);
  OS_ASSERT(result);
  return result;
}

bool SetpointManagerMultiZoneHumidityMaximum::setMaximumSetpointHumidityRatio(double maximumSetpointHumidityRatio) {
  const bool result = getImpl<detail::SetpointManagerMultiZoneHumidityMaximum_Impl>()->setMaximumSetpointHumidityRatio(maximumSetpointHumidityRatio);
  OS_ASSERT(result);
  return result;
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

double SetpointManagerMultiZoneHumidityMaximum_Impl::minimumSetpointHumidityRatio() const {
  const auto value = getDouble(openstudio::SetpointManager_MultiZone_Humidity_MaximumFields::MinimumSetpointHumidityRatio, true);
  OS_ASSERT(value);
  return *value;
}

double SetpointManagerMultiZoneHumidityMaximum_Impl::maximumSetpointHumidityRatio() const {
  const auto value = getDouble(openstudio::SetpointManager_MultiZone_Humidity_MaximumFields::MaximumSetpointHumidityRatio, true);
  OS_ASSERT(value);
  return *value;
}

bool SetpointManagerMultiZoneHumidityMaximum_Impl::setMinimumSetpointHumidityRatio(double minimumSetpointHumidityRatio) {
  const bool result =
    setDouble(openstudio::SetpointManager_MultiZone_Humidity_MaximumFields::MinimumSetpointHumidityRatio, minimumSetpointHumidityRatio);
  OS_ASSERT(result);
  return result;
}

bool SetpointManagerMultiZoneHumidityMaximum_Impl::setMaximumSetpointHumidityRatio(double maximumSetpointHumidityRatio) {
  const bool result =
    setDouble(openstudio::SetpointManager_MultiZone_Humidity_MaximumFields::MaximumSetpointHumidityRatio, maximumSetpointHumidityRatio);
  OS_ASSERT(result);
  return result;
}

unsigned SetpointManagerMultiZoneHumidityMaximum_Impl::setpointNodeFieldIndex() const {
  return openstudio::SetpointManager_MultiZone_Humidity_MaximumFields::SetpointNodeorNodeListName;
}

unsigned SetpointManagerMultiZoneHumidityMaximum_Impl::controlVariableFieldIndex() const {
  // E+ SetpointManager:MultiZone:Humidity:Maximum has no explicit control variable field;
  // this placeholder index satisfies the abstract SetpointManager_Impl contract.
  return openstudio::SetpointManager_MultiZone_Humidity_MaximumFields::HVACAirLoopName;
}

void SetpointManagerMultiZoneHumidityMaximum_Impl::doCanonicalize(LoadContext& context) {
  SetpointManager_Impl::doCanonicalize(context);

  if (auto value = getDouble(openstudio::SetpointManager_MultiZone_Humidity_MaximumFields::MinimumSetpointHumidityRatio, true)) {
    (void)value;
  } else {
    OS_ASSERT(setDouble(openstudio::SetpointManager_MultiZone_Humidity_MaximumFields::MinimumSetpointHumidityRatio, 0.008));
    detail::addLoadInfo(context, "Set default Minimum Setpoint Humidity Ratio to 0.008 for SetpointManager:MultiZone:Humidity:Maximum '"
                                   + getObject<ModelObject>().nameString() + "'.");
  }

  if (auto value = getDouble(openstudio::SetpointManager_MultiZone_Humidity_MaximumFields::MaximumSetpointHumidityRatio, true)) {
    (void)value;
  } else {
    OS_ASSERT(setDouble(openstudio::SetpointManager_MultiZone_Humidity_MaximumFields::MaximumSetpointHumidityRatio, 0.015));
    detail::addLoadInfo(context, "Set default Maximum Setpoint Humidity Ratio to 0.015 for SetpointManager:MultiZone:Humidity:Maximum '"
                                   + getObject<ModelObject>().nameString() + "'.");
  }
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
