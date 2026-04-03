/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/AirTerminalSingleDuctConstantVolumeNoReheat.hpp"
#include "StraightComponent/AirTerminalSingleDuctConstantVolumeNoReheat_Impl.hpp"

#include "Loop/AirLoopHVAC.hpp"
#include "Loop/AirLoopHVAC_Impl.hpp"
#include "Mixer/AirLoopHVACZoneMixer.hpp"
#include "Splitter/AirLoopHVACZoneSplitter.hpp"
#include "Model.hpp"
#include "ModelObject.hpp"
#include "Node.hpp"
#include "HVACComponent/ThermalZone.hpp"
#include "ModelObject/ZoneHVACAirDistributionUnit.hpp"
#include "ModelObject/ZoneHVACAirDistributionUnit_Impl.hpp"
#include "ModelObject/ZoneHVACEquipmentConnections.hpp"
#include "ModelObject/ZoneHVACEquipmentConnections_Impl.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"
#include "Schedule/ScheduleConstant.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/Logger.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/AirTerminal_SingleDuct_ConstantVolume_NoReheat_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <algorithm>

namespace openstudio {
namespace epmodel {

  AirTerminalSingleDuctConstantVolumeNoReheat::AirTerminalSingleDuctConstantVolumeNoReheat(const Model& model)
    : StraightComponent(AirTerminalSingleDuctConstantVolumeNoReheat::iddObjectType(), model) {
    auto impl = getImpl<detail::AirTerminalSingleDuctConstantVolumeNoReheat_Impl>();
    OS_ASSERT(impl);
    detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
    impl->canonicalize(context);
    ScheduleConstant alwaysOn(model);
    OS_ASSERT(alwaysOn.setValue(1.0));
    OS_ASSERT(setAvailabilitySchedule(alwaysOn));
  }

  AirTerminalSingleDuctConstantVolumeNoReheat::AirTerminalSingleDuctConstantVolumeNoReheat(
    std::shared_ptr<detail::AirTerminalSingleDuctConstantVolumeNoReheat_Impl> impl)
    : StraightComponent(std::move(impl)) {}

  IddObjectType AirTerminalSingleDuctConstantVolumeNoReheat::iddObjectType() {
    return IddObjectType::AirTerminal_SingleDuct_ConstantVolume_NoReheat;
  }

  bool AirTerminalSingleDuctConstantVolumeNoReheat::addToNode(Node& node) {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeNoReheat_Impl>()->addToNode(node);
  }

  Schedule AirTerminalSingleDuctConstantVolumeNoReheat::availabilitySchedule() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeNoReheat_Impl>()->availabilitySchedule();
  }

  bool AirTerminalSingleDuctConstantVolumeNoReheat::setAvailabilitySchedule(Schedule& schedule) {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeNoReheat_Impl>()->setAvailabilitySchedule(schedule);
  }

  boost::optional<double> AirTerminalSingleDuctConstantVolumeNoReheat::maximumAirFlowRate() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeNoReheat_Impl>()->maximumAirFlowRate();
  }

  bool AirTerminalSingleDuctConstantVolumeNoReheat::isMaximumAirFlowRateAutosized() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeNoReheat_Impl>()->isMaximumAirFlowRateAutosized();
  }

  bool AirTerminalSingleDuctConstantVolumeNoReheat::setMaximumAirFlowRate(double maximumAirFlowRate) {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeNoReheat_Impl>()->setMaximumAirFlowRate(maximumAirFlowRate);
  }

  void AirTerminalSingleDuctConstantVolumeNoReheat::autosizeMaximumAirFlowRate() {
    getImpl<detail::AirTerminalSingleDuctConstantVolumeNoReheat_Impl>()->autosizeMaximumAirFlowRate();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    unsigned AirTerminalSingleDuctConstantVolumeNoReheat_Impl::inletPort() const {
      return AirTerminal_SingleDuct_ConstantVolume_NoReheatFields::AirInletNodeName;
    }

    unsigned AirTerminalSingleDuctConstantVolumeNoReheat_Impl::outletPort() const {
      return AirTerminal_SingleDuct_ConstantVolume_NoReheatFields::AirOutletNodeName;
    }

    boost::optional<openstudio::epmodel::AirLoopHVAC> AirTerminalSingleDuctConstantVolumeNoReheat_Impl::airLoopHVAC() const {
      auto outletObject = outletModelObject();
      auto outletNode = outletObject ? outletObject->optionalCast<openstudio::epmodel::Node>() : boost::none;
      if (!outletNode) {
        return boost::none;
      }

      boost::optional<openstudio::epmodel::ThermalZone> thermalZone;
      for (const auto& connections : model().getConcreteModelObjects<openstudio::epmodel::ZoneHVACEquipmentConnections>()) {
        auto zoneInlet = connections.zoneAirInletNode();
        auto zone = connections.thermalZone();
        if (zoneInlet && zone && (*zoneInlet == *outletNode)) {
          thermalZone = zone;
          break;
        }
      }
      if (!thermalZone) {
        return boost::none;
      }

      for (const auto& airLoop : model().getConcreteModelObjects<openstudio::epmodel::AirLoopHVAC>()) {
        const auto loopZones = airLoop.thermalZones();
        if (std::ranges::find(loopZones, *thermalZone) != loopZones.end()) {
          return airLoop;
        }
      }

      return boost::none;
    }

    boost::optional<openstudio::epmodel::ZoneHVACAirDistributionUnit>
      AirTerminalSingleDuctConstantVolumeNoReheat_Impl::zoneHVACAirDistributionUnit() const {
      auto terminal = getObject<openstudio::epmodel::ModelObject>();
      for (const auto& source : terminal.getSources(openstudio::IddObjectType::ZoneHVAC_AirDistributionUnit)) {
        if (auto adu = source.optionalCast<openstudio::epmodel::ZoneHVACAirDistributionUnit>()) {
          return adu;
        }
      }
      return boost::none;
    }

    Schedule AirTerminalSingleDuctConstantVolumeNoReheat_Impl::availabilitySchedule() const {
      auto schedule = getObject<ModelObject>().getModelObjectTarget<Schedule>(
        AirTerminal_SingleDuct_ConstantVolume_NoReheatFields::AvailabilityScheduleName);
      OS_ASSERT(schedule);
      return *schedule;
    }

    bool AirTerminalSingleDuctConstantVolumeNoReheat_Impl::setAvailabilitySchedule(Schedule& schedule) {
      return ModelObject_Impl::setSchedule(AirTerminal_SingleDuct_ConstantVolume_NoReheatFields::AvailabilityScheduleName,
                                           "AirTerminalSingleDuctConstantVolumeNoReheat", "Availability", schedule);
    }

    boost::optional<double> AirTerminalSingleDuctConstantVolumeNoReheat_Impl::maximumAirFlowRate() const {
      return getDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_NoReheatFields::MaximumAirFlowRate, true);
    }

    bool AirTerminalSingleDuctConstantVolumeNoReheat_Impl::isMaximumAirFlowRateAutosized() const {
      if (auto value = getString(openstudio::AirTerminal_SingleDuct_ConstantVolume_NoReheatFields::MaximumAirFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool AirTerminalSingleDuctConstantVolumeNoReheat_Impl::setMaximumAirFlowRate(double maximumAirFlowRate) {
      return setDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_NoReheatFields::MaximumAirFlowRate, maximumAirFlowRate);
    }

    void AirTerminalSingleDuctConstantVolumeNoReheat_Impl::autosizeMaximumAirFlowRate() {
      OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_NoReheatFields::MaximumAirFlowRate, "autosize"));
    }

    bool AirTerminalSingleDuctConstantVolumeNoReheat_Impl::addToNode(Node& node) {
      if (node.model() != model()) {
        return false;
      }

      auto airLoop = node.airLoopHVAC();
      if (!airLoop) {
        return false;
      }

      auto zoneSplitter = airLoop->zoneSplitter();
      auto zoneMixer = airLoop->zoneMixer();
      const auto thisNode = node.cast<ModelObject>();
      const auto splitterOutlets = zoneSplitter.outletModelObjects();
      const auto splitterIt = std::ranges::find(splitterOutlets, thisNode);
      if (splitterIt == splitterOutlets.end()) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctConstantVolumeNoReheat",
                 "addToNode requires the drop node to be a ZoneSplitter outlet node for the target AirLoopHVAC.");
        return false;
      }
      const auto splitterBranchIndex = static_cast<unsigned>(std::distance(splitterOutlets.begin(), splitterIt));

      auto mixerInlet = zoneMixer.inletModelObject(splitterBranchIndex);
      if (!mixerInlet) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctConstantVolumeNoReheat",
                 "addToNode requires a corresponding ZoneMixer inlet for ZoneSplitter branch index " << splitterBranchIndex << ".");
        return false;
      }

      auto thisObject = getObject<openstudio::epmodel::ModelObject>();
      if (!thisObject.name()) {
        thisObject.createName();
        if (!thisObject.name()) {
          return false;
        }
      }

      const std::string inletNodeName = node.nameString() + " - " + thisObject.nameString() + " Inlet Node";
      auto inletNode = model().getOrCreateTransientByName<openstudio::epmodel::Node>(inletNodeName);

      if (!zoneSplitter.setOutletModelObject(splitterBranchIndex, inletNode.cast<ModelObject>())) {
        return false;
      }

      if (!setPointer(inletPort(), inletNode.handle())) {
        return false;
      }

      if (!setPointer(outletPort(), node.handle())) {
        return false;
      }
      if (auto adu = zoneHVACAirDistributionUnit()) {
        adu->getImpl<openstudio::epmodel::detail::ZoneHVACAirDistributionUnit_Impl>()->setOutletNode(node);
      }

      return true;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
