/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "Mixer/AirTerminalDualDuctVAVOutdoorAir.hpp"
#include "Mixer/AirTerminalDualDuctVAVOutdoorAir_Impl.hpp"

#include "Loop/AirLoopHVAC_Impl.hpp"
#include "HVACComponent/HVACComponent.hpp"
#include "Model.hpp"
#include "StraightComponent/Node.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/AirTerminal_DualDuct_VAV_OutdoorAir_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

#include <limits>

namespace openstudio {
namespace epmodel {

AirTerminalDualDuctVAVOutdoorAir::AirTerminalDualDuctVAVOutdoorAir(const Model& model)
  : Mixer(AirTerminalDualDuctVAVOutdoorAir::iddObjectType(), model) {
  // Keep non-optional scalar getter strictness aligned with preserved model API.
  OS_ASSERT(setPerPersonVentilationRateMode("CurrentOccupancy"));

  // Mirror model constructor autosize behavior for Maximum Terminal Air Flow Rate.
  autosizeMaximumTerminalAirFlowRate();
}

AirTerminalDualDuctVAVOutdoorAir::AirTerminalDualDuctVAVOutdoorAir(std::shared_ptr<detail::AirTerminalDualDuctVAVOutdoorAir_Impl> impl)
  : Mixer(std::move(impl)) {}

IddObjectType AirTerminalDualDuctVAVOutdoorAir::iddObjectType() {
  return IddObjectType::AirTerminal_DualDuct_VAV_OutdoorAir;
}

std::vector<std::string> AirTerminalDualDuctVAVOutdoorAir::perPersonVentilationRateModeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::AirTerminal_DualDuct_VAV_OutdoorAirFields::PerPersonVentilationRateMode);
}

boost::optional<double> AirTerminalDualDuctVAVOutdoorAir::maximumTerminalAirFlowRate() const {
  return getImpl<detail::AirTerminalDualDuctVAVOutdoorAir_Impl>()->maximumTerminalAirFlowRate();
}

bool AirTerminalDualDuctVAVOutdoorAir::isMaximumTerminalAirFlowRateAutosized() const {
  return getImpl<detail::AirTerminalDualDuctVAVOutdoorAir_Impl>()->isMaximumTerminalAirFlowRateAutosized();
}

bool AirTerminalDualDuctVAVOutdoorAir::setMaximumTerminalAirFlowRate(double maximumTerminalAirFlowRate) {
  return getImpl<detail::AirTerminalDualDuctVAVOutdoorAir_Impl>()->setMaximumTerminalAirFlowRate(maximumTerminalAirFlowRate);
}

void AirTerminalDualDuctVAVOutdoorAir::autosizeMaximumTerminalAirFlowRate() {
  getImpl<detail::AirTerminalDualDuctVAVOutdoorAir_Impl>()->autosizeMaximumTerminalAirFlowRate();
}

std::string AirTerminalDualDuctVAVOutdoorAir::perPersonVentilationRateMode() const {
  return getImpl<detail::AirTerminalDualDuctVAVOutdoorAir_Impl>()->perPersonVentilationRateMode();
}

bool AirTerminalDualDuctVAVOutdoorAir::setPerPersonVentilationRateMode(const std::string& perPersonVentilationRateMode) {
  return getImpl<detail::AirTerminalDualDuctVAVOutdoorAir_Impl>()->setPerPersonVentilationRateMode(perPersonVentilationRateMode);
}

boost::optional<Node> AirTerminalDualDuctVAVOutdoorAir::outdoorAirInletNode() const {
  return getImpl<detail::AirTerminalDualDuctVAVOutdoorAir_Impl>()->outdoorAirInletNode();
}

boost::optional<Node> AirTerminalDualDuctVAVOutdoorAir::recirculatedAirInletNode() const {
  return getImpl<detail::AirTerminalDualDuctVAVOutdoorAir_Impl>()->recirculatedAirInletNode();
}

bool AirTerminalDualDuctVAVOutdoorAir::addToNode(Node& node) {
  return getImpl<detail::AirTerminalDualDuctVAVOutdoorAir_Impl>()->addToNode(node);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

unsigned AirTerminalDualDuctVAVOutdoorAir_Impl::outletPort() const {
  return openstudio::AirTerminal_DualDuct_VAV_OutdoorAirFields::AirOutletNodeName;
}

unsigned AirTerminalDualDuctVAVOutdoorAir_Impl::inletPort(unsigned branchIndex) const {
  if (branchIndex == 0u) {
    return openstudio::AirTerminal_DualDuct_VAV_OutdoorAirFields::OutdoorAirInletNodeName;
  }
  if (branchIndex == 1u) {
    return openstudio::AirTerminal_DualDuct_VAV_OutdoorAirFields::RecirculatedAirInletNodeName;
  }
  return std::numeric_limits<unsigned>::max();
}

bool AirTerminalDualDuctVAVOutdoorAir_Impl::addToNode(openstudio::epmodel::Node& node) {
  auto terminal = getObject<AirTerminalDualDuctVAVOutdoorAir>().cast<Mixer>();
  return AirLoopHVAC_Impl::addDualDuctTerminalToNode(terminal, node);
}

boost::optional<openstudio::epmodel::Node> AirTerminalDualDuctVAVOutdoorAir_Impl::outdoorAirInletNode() const {
  if (auto object = inletModelObject(0u)) {
    return object->optionalCast<Node>();
  }
  return boost::none;
}

boost::optional<openstudio::epmodel::Node> AirTerminalDualDuctVAVOutdoorAir_Impl::recirculatedAirInletNode() const {
  if (auto object = inletModelObject(1u)) {
    return object->optionalCast<Node>();
  }
  return boost::none;
}

boost::optional<double> AirTerminalDualDuctVAVOutdoorAir_Impl::maximumTerminalAirFlowRate() const {
  return getDouble(openstudio::AirTerminal_DualDuct_VAV_OutdoorAirFields::MaximumTerminalAirFlowRate, true);
}

bool AirTerminalDualDuctVAVOutdoorAir_Impl::isMaximumTerminalAirFlowRateAutosized() const {
  if (auto value = getString(openstudio::AirTerminal_DualDuct_VAV_OutdoorAirFields::MaximumTerminalAirFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool AirTerminalDualDuctVAVOutdoorAir_Impl::setMaximumTerminalAirFlowRate(double maximumTerminalAirFlowRate) {
  return setDouble(openstudio::AirTerminal_DualDuct_VAV_OutdoorAirFields::MaximumTerminalAirFlowRate, maximumTerminalAirFlowRate);
}

void AirTerminalDualDuctVAVOutdoorAir_Impl::autosizeMaximumTerminalAirFlowRate() {
  OS_ASSERT(setString(openstudio::AirTerminal_DualDuct_VAV_OutdoorAirFields::MaximumTerminalAirFlowRate, "autosize"));
}

std::string AirTerminalDualDuctVAVOutdoorAir_Impl::perPersonVentilationRateMode() const {
  const auto value = getString(openstudio::AirTerminal_DualDuct_VAV_OutdoorAirFields::PerPersonVentilationRateMode, true);
  OS_ASSERT(value);
  return *value;
}

bool AirTerminalDualDuctVAVOutdoorAir_Impl::setPerPersonVentilationRateMode(const std::string& perPersonVentilationRateMode) {
  return setString(openstudio::AirTerminal_DualDuct_VAV_OutdoorAirFields::PerPersonVentilationRateMode, perPersonVentilationRateMode);
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
