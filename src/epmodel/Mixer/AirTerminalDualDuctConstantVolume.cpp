/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "Mixer/AirTerminalDualDuctConstantVolume.hpp"
#include "Mixer/AirTerminalDualDuctConstantVolume_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/AirTerminal_DualDuct_ConstantVolume_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

AirTerminalDualDuctConstantVolume::AirTerminalDualDuctConstantVolume(const Model& model)
  : ModelObject(AirTerminalDualDuctConstantVolume::iddObjectType(), model) {}

AirTerminalDualDuctConstantVolume::AirTerminalDualDuctConstantVolume(
  std::shared_ptr<detail::AirTerminalDualDuctConstantVolume_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType AirTerminalDualDuctConstantVolume::iddObjectType() {
  return IddObjectType::AirTerminal_DualDuct_ConstantVolume;
}

boost::optional<double> AirTerminalDualDuctConstantVolume::maximumAirFlowRate() const {
  return getImpl<detail::AirTerminalDualDuctConstantVolume_Impl>()->maximumAirFlowRate();
}

bool AirTerminalDualDuctConstantVolume::isMaximumAirFlowRateAutosized() const {
  return getImpl<detail::AirTerminalDualDuctConstantVolume_Impl>()->isMaximumAirFlowRateAutosized();
}

bool AirTerminalDualDuctConstantVolume::setMaximumAirFlowRate(double maximumAirFlowRate) {
  return getImpl<detail::AirTerminalDualDuctConstantVolume_Impl>()->setMaximumAirFlowRate(maximumAirFlowRate);
}

void AirTerminalDualDuctConstantVolume::autosizeMaximumAirFlowRate() {
  getImpl<detail::AirTerminalDualDuctConstantVolume_Impl>()->autosizeMaximumAirFlowRate();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

boost::optional<double> AirTerminalDualDuctConstantVolume_Impl::maximumAirFlowRate() const {
  return getDouble(openstudio::AirTerminal_DualDuct_ConstantVolumeFields::MaximumAirFlowRate, true);
}

bool AirTerminalDualDuctConstantVolume_Impl::isMaximumAirFlowRateAutosized() const {
  if (auto value = getString(openstudio::AirTerminal_DualDuct_ConstantVolumeFields::MaximumAirFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool AirTerminalDualDuctConstantVolume_Impl::setMaximumAirFlowRate(double maximumAirFlowRate) {
  return setDouble(openstudio::AirTerminal_DualDuct_ConstantVolumeFields::MaximumAirFlowRate, maximumAirFlowRate);
}

void AirTerminalDualDuctConstantVolume_Impl::autosizeMaximumAirFlowRate() {
  OS_ASSERT(setString(openstudio::AirTerminal_DualDuct_ConstantVolumeFields::MaximumAirFlowRate, "autosize"));
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
