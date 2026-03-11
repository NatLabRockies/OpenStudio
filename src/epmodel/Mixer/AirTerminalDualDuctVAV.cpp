/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "Mixer/AirTerminalDualDuctVAV.hpp"
#include "Mixer/AirTerminalDualDuctVAV_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/AirTerminal_DualDuct_VAV_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

AirTerminalDualDuctVAV::AirTerminalDualDuctVAV(const Model& model) : ModelObject(AirTerminalDualDuctVAV::iddObjectType(), model) {}

AirTerminalDualDuctVAV::AirTerminalDualDuctVAV(std::shared_ptr<detail::AirTerminalDualDuctVAV_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType AirTerminalDualDuctVAV::iddObjectType() {
  return IddObjectType::AirTerminal_DualDuct_VAV;
}

boost::optional<double> AirTerminalDualDuctVAV::maximumDamperAirFlowRate() const {
  return getImpl<detail::AirTerminalDualDuctVAV_Impl>()->maximumDamperAirFlowRate();
}

bool AirTerminalDualDuctVAV::isMaximumDamperAirFlowRateAutosized() const {
  return getImpl<detail::AirTerminalDualDuctVAV_Impl>()->isMaximumDamperAirFlowRateAutosized();
}

bool AirTerminalDualDuctVAV::setMaximumDamperAirFlowRate(double maximumDamperAirFlowRate) {
  return getImpl<detail::AirTerminalDualDuctVAV_Impl>()->setMaximumDamperAirFlowRate(maximumDamperAirFlowRate);
}

void AirTerminalDualDuctVAV::autosizeMaximumDamperAirFlowRate() {
  getImpl<detail::AirTerminalDualDuctVAV_Impl>()->autosizeMaximumDamperAirFlowRate();
}

double AirTerminalDualDuctVAV::zoneMinimumAirFlowFraction() const {
  return getImpl<detail::AirTerminalDualDuctVAV_Impl>()->zoneMinimumAirFlowFraction();
}

bool AirTerminalDualDuctVAV::setZoneMinimumAirFlowFraction(double zoneMinimumAirFlowFraction) {
  return getImpl<detail::AirTerminalDualDuctVAV_Impl>()->setZoneMinimumAirFlowFraction(zoneMinimumAirFlowFraction);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

boost::optional<double> AirTerminalDualDuctVAV_Impl::maximumDamperAirFlowRate() const {
  return getDouble(openstudio::AirTerminal_DualDuct_VAVFields::MaximumDamperAirFlowRate, true);
}

bool AirTerminalDualDuctVAV_Impl::isMaximumDamperAirFlowRateAutosized() const {
  if (auto value = getString(openstudio::AirTerminal_DualDuct_VAVFields::MaximumDamperAirFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool AirTerminalDualDuctVAV_Impl::setMaximumDamperAirFlowRate(double maximumDamperAirFlowRate) {
  return setDouble(openstudio::AirTerminal_DualDuct_VAVFields::MaximumDamperAirFlowRate, maximumDamperAirFlowRate);
}

void AirTerminalDualDuctVAV_Impl::autosizeMaximumDamperAirFlowRate() {
  OS_ASSERT(setString(openstudio::AirTerminal_DualDuct_VAVFields::MaximumDamperAirFlowRate, "autosize"));
}

double AirTerminalDualDuctVAV_Impl::zoneMinimumAirFlowFraction() const {
  const auto value = getDouble(openstudio::AirTerminal_DualDuct_VAVFields::ZoneMinimumAirFlowFraction, true);
  OS_ASSERT(value);
  return *value;
}

bool AirTerminalDualDuctVAV_Impl::setZoneMinimumAirFlowFraction(double zoneMinimumAirFlowFraction) {
  return setDouble(openstudio::AirTerminal_DualDuct_VAVFields::ZoneMinimumAirFlowFraction, zoneMinimumAirFlowFraction);
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
