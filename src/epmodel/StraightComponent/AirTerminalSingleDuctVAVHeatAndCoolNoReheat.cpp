/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/AirTerminalSingleDuctVAVHeatAndCoolNoReheat.hpp"
#include "StraightComponent/AirTerminalSingleDuctVAVHeatAndCoolNoReheat_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/AirTerminal_SingleDuct_VAV_HeatAndCool_NoReheat_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

AirTerminalSingleDuctVAVHeatAndCoolNoReheat::AirTerminalSingleDuctVAVHeatAndCoolNoReheat(const Model& model)
  : StraightComponent(AirTerminalSingleDuctVAVHeatAndCoolNoReheat::iddObjectType(), model) {}

AirTerminalSingleDuctVAVHeatAndCoolNoReheat::AirTerminalSingleDuctVAVHeatAndCoolNoReheat(
  std::shared_ptr<detail::AirTerminalSingleDuctVAVHeatAndCoolNoReheat_Impl> impl)
  : StraightComponent(std::move(impl)) {}

IddObjectType AirTerminalSingleDuctVAVHeatAndCoolNoReheat::iddObjectType() {
  return IddObjectType::AirTerminal_SingleDuct_VAV_HeatAndCool_NoReheat;
}

boost::optional<double> AirTerminalSingleDuctVAVHeatAndCoolNoReheat::maximumAirFlowRate() const {
  return getImpl<detail::AirTerminalSingleDuctVAVHeatAndCoolNoReheat_Impl>()->maximumAirFlowRate();
}

bool AirTerminalSingleDuctVAVHeatAndCoolNoReheat::isMaximumAirFlowRateAutosized() const {
  return getImpl<detail::AirTerminalSingleDuctVAVHeatAndCoolNoReheat_Impl>()->isMaximumAirFlowRateAutosized();
}

bool AirTerminalSingleDuctVAVHeatAndCoolNoReheat::setMaximumAirFlowRate(double maximumAirFlowRate) {
  return getImpl<detail::AirTerminalSingleDuctVAVHeatAndCoolNoReheat_Impl>()->setMaximumAirFlowRate(maximumAirFlowRate);
}

void AirTerminalSingleDuctVAVHeatAndCoolNoReheat::autosizeMaximumAirFlowRate() {
  getImpl<detail::AirTerminalSingleDuctVAVHeatAndCoolNoReheat_Impl>()->autosizeMaximumAirFlowRate();
}

double AirTerminalSingleDuctVAVHeatAndCoolNoReheat::zoneMinimumAirFlowFraction() const {
  return getImpl<detail::AirTerminalSingleDuctVAVHeatAndCoolNoReheat_Impl>()->zoneMinimumAirFlowFraction();
}

bool AirTerminalSingleDuctVAVHeatAndCoolNoReheat::setZoneMinimumAirFlowFraction(double zoneMinimumAirFlowFraction) {
  return getImpl<detail::AirTerminalSingleDuctVAVHeatAndCoolNoReheat_Impl>()->setZoneMinimumAirFlowFraction(zoneMinimumAirFlowFraction);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

boost::optional<double> AirTerminalSingleDuctVAVHeatAndCoolNoReheat_Impl::maximumAirFlowRate() const {
  return getDouble(openstudio::AirTerminal_SingleDuct_VAV_HeatAndCool_NoReheatFields::MaximumAirFlowRate, true);
}

bool AirTerminalSingleDuctVAVHeatAndCoolNoReheat_Impl::isMaximumAirFlowRateAutosized() const {
  if (auto value = getString(openstudio::AirTerminal_SingleDuct_VAV_HeatAndCool_NoReheatFields::MaximumAirFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool AirTerminalSingleDuctVAVHeatAndCoolNoReheat_Impl::setMaximumAirFlowRate(double maximumAirFlowRate) {
  return setDouble(openstudio::AirTerminal_SingleDuct_VAV_HeatAndCool_NoReheatFields::MaximumAirFlowRate, maximumAirFlowRate);
}

void AirTerminalSingleDuctVAVHeatAndCoolNoReheat_Impl::autosizeMaximumAirFlowRate() {
  OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_VAV_HeatAndCool_NoReheatFields::MaximumAirFlowRate, "autosize"));
}

double AirTerminalSingleDuctVAVHeatAndCoolNoReheat_Impl::zoneMinimumAirFlowFraction() const {
  const auto value = getDouble(openstudio::AirTerminal_SingleDuct_VAV_HeatAndCool_NoReheatFields::ZoneMinimumAirFlowFraction, true);
  OS_ASSERT(value);
  return *value;
}

bool AirTerminalSingleDuctVAVHeatAndCoolNoReheat_Impl::setZoneMinimumAirFlowFraction(double zoneMinimumAirFlowFraction) {
  return setDouble(openstudio::AirTerminal_SingleDuct_VAV_HeatAndCool_NoReheatFields::ZoneMinimumAirFlowFraction, zoneMinimumAirFlowFraction);
}

unsigned AirTerminalSingleDuctVAVHeatAndCoolNoReheat_Impl::inletPort() const {
  return openstudio::AirTerminal_SingleDuct_VAV_HeatAndCool_NoReheatFields::AirInletNodeName;
}

unsigned AirTerminalSingleDuctVAVHeatAndCoolNoReheat_Impl::outletPort() const {
  return openstudio::AirTerminal_SingleDuct_VAV_HeatAndCool_NoReheatFields::AirOutletNodeName;
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
