/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "Mixer/AirTerminalDualDuctVAV.hpp"
#include "Mixer/AirTerminalDualDuctVAV_Impl.hpp"

#include "Loop/AirLoopHVAC_Impl.hpp"
#include "Model.hpp"
#include "StraightComponent/Node.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/AirTerminal_DualDuct_VAV_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

#include <limits>

namespace openstudio {
namespace epmodel {

  AirTerminalDualDuctVAV::AirTerminalDualDuctVAV(const Model& model) : Mixer(AirTerminalDualDuctVAV::iddObjectType(), model) {
    autosizeMaximumDamperAirFlowRate();
    OS_ASSERT(setZoneMinimumAirFlowFraction(0.3));
  }

  AirTerminalDualDuctVAV::AirTerminalDualDuctVAV(std::shared_ptr<detail::AirTerminalDualDuctVAV_Impl> impl) : Mixer(std::move(impl)) {}

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

  namespace detail {

    unsigned AirTerminalDualDuctVAV_Impl::outletPort() const {
      return openstudio::AirTerminal_DualDuct_VAVFields::AirOutletNodeName;
    }

    unsigned AirTerminalDualDuctVAV_Impl::inletPort(unsigned branchIndex) const {
      if (branchIndex == 0u) {
        return openstudio::AirTerminal_DualDuct_VAVFields::HotAirInletNodeName;
      }
      if (branchIndex == 1u) {
        return openstudio::AirTerminal_DualDuct_VAVFields::ColdAirInletNodeName;
      }
      return std::numeric_limits<unsigned>::max();
    }

    bool AirTerminalDualDuctVAV_Impl::addToNode(openstudio::epmodel::Node& node) {
      if (node.model() != model()) {
        return false;
      }

      auto terminal = getObject<AirTerminalDualDuctVAV>().cast<Mixer>();
      return AirLoopHVAC_Impl::addDualDuctTerminalToNode(terminal, node);
    }

    std::vector<openstudio::IdfObject> AirTerminalDualDuctVAV_Impl::remove() {
      auto terminal = getObject<AirTerminalDualDuctVAV>().cast<Mixer>();
      AirLoopHVAC_Impl::removeDualDuctTerminalFromAirLoopHVAC(terminal);
      return Mixer_Impl::remove();
    }

    boost::optional<openstudio::epmodel::Node> AirTerminalDualDuctVAV_Impl::hotAirInletNode() const {
      if (auto object = inletModelObject(0u)) {
        return object->optionalCast<Node>();
      }
      return boost::none;
    }

    boost::optional<openstudio::epmodel::Node> AirTerminalDualDuctVAV_Impl::coldAirInletNode() const {
      if (auto object = inletModelObject(1u)) {
        return object->optionalCast<Node>();
      }
      return boost::none;
    }

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

  }  // namespace detail

  double AirTerminalDualDuctVAV::zoneMinimumAirFlowFraction() const {
    return getImpl<detail::AirTerminalDualDuctVAV_Impl>()->zoneMinimumAirFlowFraction();
  }

  bool AirTerminalDualDuctVAV::setZoneMinimumAirFlowFraction(double zoneMinimumAirFlowFraction) {
    return getImpl<detail::AirTerminalDualDuctVAV_Impl>()->setZoneMinimumAirFlowFraction(zoneMinimumAirFlowFraction);
  }

  boost::optional<Node> AirTerminalDualDuctVAV::hotAirInletNode() const {
    return getImpl<detail::AirTerminalDualDuctVAV_Impl>()->hotAirInletNode();
  }

  boost::optional<Node> AirTerminalDualDuctVAV::coldAirInletNode() const {
    return getImpl<detail::AirTerminalDualDuctVAV_Impl>()->coldAirInletNode();
  }

  bool AirTerminalDualDuctVAV::addToNode(Node& node) {
    return getImpl<detail::AirTerminalDualDuctVAV_Impl>()->addToNode(node);
  }

  namespace detail {

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
