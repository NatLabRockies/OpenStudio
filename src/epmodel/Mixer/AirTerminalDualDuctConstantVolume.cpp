/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "Mixer/AirTerminalDualDuctConstantVolume.hpp"
#include "Mixer/AirTerminalDualDuctConstantVolume_Impl.hpp"

#include "Loop/AirLoopHVAC_Impl.hpp"
#include "Model.hpp"
#include "Schedule/Schedule.hpp"
#include "StraightComponent/Node.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/AirTerminal_DualDuct_ConstantVolume_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

#include <limits>

namespace openstudio {
namespace epmodel {

  AirTerminalDualDuctConstantVolume::AirTerminalDualDuctConstantVolume(const Model& model)
    : Mixer(AirTerminalDualDuctConstantVolume::iddObjectType(), model) {
    auto alwaysOn = model.alwaysOnDiscreteSchedule();
    OS_ASSERT(setPointer(openstudio::AirTerminal_DualDuct_ConstantVolumeFields::AvailabilityScheduleName, alwaysOn.handle()));
    autosizeMaximumAirFlowRate();
  }

  AirTerminalDualDuctConstantVolume::AirTerminalDualDuctConstantVolume(std::shared_ptr<detail::AirTerminalDualDuctConstantVolume_Impl> impl)
    : Mixer(std::move(impl)) {}

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

  boost::optional<Node> AirTerminalDualDuctConstantVolume::hotAirInletNode() const {
    return getImpl<detail::AirTerminalDualDuctConstantVolume_Impl>()->hotAirInletNode();
  }

  boost::optional<Node> AirTerminalDualDuctConstantVolume::coldAirInletNode() const {
    return getImpl<detail::AirTerminalDualDuctConstantVolume_Impl>()->coldAirInletNode();
  }

  bool AirTerminalDualDuctConstantVolume::addToNode(Node& node) {
    return getImpl<detail::AirTerminalDualDuctConstantVolume_Impl>()->addToNode(node);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    unsigned AirTerminalDualDuctConstantVolume_Impl::outletPort() const {
      return openstudio::AirTerminal_DualDuct_ConstantVolumeFields::AirOutletNodeName;
    }

    unsigned AirTerminalDualDuctConstantVolume_Impl::inletPort(unsigned branchIndex) const {
      if (branchIndex == 0u) {
        return openstudio::AirTerminal_DualDuct_ConstantVolumeFields::HotAirInletNodeName;
      }
      if (branchIndex == 1u) {
        return openstudio::AirTerminal_DualDuct_ConstantVolumeFields::ColdAirInletNodeName;
      }
      return std::numeric_limits<unsigned>::max();
    }

    bool AirTerminalDualDuctConstantVolume_Impl::addToNode(openstudio::epmodel::Node& node) {
      if (node.model() != model()) {
        return false;
      }

      auto terminal = getObject<AirTerminalDualDuctConstantVolume>().cast<Mixer>();
      return AirLoopHVAC_Impl::addDualDuctTerminalToNode(terminal, node);
    }

    std::vector<openstudio::IdfObject> AirTerminalDualDuctConstantVolume_Impl::remove() {
      auto terminal = getObject<AirTerminalDualDuctConstantVolume>().cast<Mixer>();
      if (!AirLoopHVAC_Impl::removeDualDuctTerminalFromAirLoopHVAC(terminal)) {
        return {};
      }
      return Mixer_Impl::remove();
    }

    boost::optional<openstudio::epmodel::Node> AirTerminalDualDuctConstantVolume_Impl::hotAirInletNode() const {
      if (auto object = inletModelObject(0u)) {
        return object->optionalCast<Node>();
      }
      return boost::none;
    }

    boost::optional<openstudio::epmodel::Node> AirTerminalDualDuctConstantVolume_Impl::coldAirInletNode() const {
      if (auto object = inletModelObject(1u)) {
        return object->optionalCast<Node>();
      }
      return boost::none;
    }

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
