/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/AirTerminalSingleDuctInletSideMixer.hpp"
#include "StraightComponent/AirTerminalSingleDuctInletSideMixer_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/AirTerminal_SingleDuct_Mixer_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

AirTerminalSingleDuctInletSideMixer::AirTerminalSingleDuctInletSideMixer(const Model& model)
  : StraightComponent(AirTerminalSingleDuctInletSideMixer::iddObjectType(), model) {
  OS_ASSERT(setPerPersonVentilationRateMode("CurrentOccupancy"));
}

AirTerminalSingleDuctInletSideMixer::AirTerminalSingleDuctInletSideMixer(
  std::shared_ptr<detail::AirTerminalSingleDuctInletSideMixer_Impl> impl)
  : StraightComponent(std::move(impl)) {}

IddObjectType AirTerminalSingleDuctInletSideMixer::iddObjectType() {
  return IddObjectType::AirTerminal_SingleDuct_Mixer;
}

std::vector<std::string> AirTerminalSingleDuctInletSideMixer::perPersonVentilationRateModeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::AirTerminal_SingleDuct_MixerFields::PerPersonVentilationRateMode);
}

std::string AirTerminalSingleDuctInletSideMixer::perPersonVentilationRateMode() const {
  return getImpl<detail::AirTerminalSingleDuctInletSideMixer_Impl>()->perPersonVentilationRateMode();
}

bool AirTerminalSingleDuctInletSideMixer::setPerPersonVentilationRateMode(const std::string& perPersonVentilationRateMode) {
  return getImpl<detail::AirTerminalSingleDuctInletSideMixer_Impl>()->setPerPersonVentilationRateMode(perPersonVentilationRateMode);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

unsigned AirTerminalSingleDuctInletSideMixer_Impl::inletPort() const {
  return openstudio::AirTerminal_SingleDuct_MixerFields::MixerPrimaryAirInletNodeName;
}

unsigned AirTerminalSingleDuctInletSideMixer_Impl::outletPort() const {
  return openstudio::AirTerminal_SingleDuct_MixerFields::MixerOutletNodeName;
}

std::string AirTerminalSingleDuctInletSideMixer_Impl::perPersonVentilationRateMode() const {
  const auto value = getString(openstudio::AirTerminal_SingleDuct_MixerFields::PerPersonVentilationRateMode, true);
  OS_ASSERT(value);
  return *value;
}

bool AirTerminalSingleDuctInletSideMixer_Impl::setPerPersonVentilationRateMode(const std::string& perPersonVentilationRateMode) {
  return setString(openstudio::AirTerminal_SingleDuct_MixerFields::PerPersonVentilationRateMode, perPersonVentilationRateMode);
}

std::vector<std::string> AirTerminalSingleDuctInletSideMixer_Impl::perPersonVentilationRateModeValues() const {
  return AirTerminalSingleDuctInletSideMixer::perPersonVentilationRateModeValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
