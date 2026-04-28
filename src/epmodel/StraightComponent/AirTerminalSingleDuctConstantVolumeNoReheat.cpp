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
#include "HVACComponent/ThermalZone.hpp"
#include "HVACComponent/ThermalZone_Impl.hpp"
#include "Model.hpp"
#include "ModelObject.hpp"
#include "Node.hpp"
#include "ModelObject/ZoneHVACAirDistributionUnit.hpp"
#include "ModelObject/ZoneHVACAirDistributionUnit_Impl.hpp"
#include "ModelObject/ZoneHVACEquipmentList.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/Logger.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/AirTerminal_SingleDuct_ConstantVolume_NoReheat_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <algorithm>

namespace openstudio {
namespace epmodel {

  namespace {

    boost::optional<ThermalZone> owningThermalZoneForBranchNode(const Model& model, const Node& node) {
      for (const auto& zone : model.getConcreteModelObjects<ThermalZone>()) {
        if (zone.zoneAirNode() == node) {
          return zone;
        }
      }
      return boost::none;
    }

  }  // namespace

  AirTerminalSingleDuctConstantVolumeNoReheat::AirTerminalSingleDuctConstantVolumeNoReheat(const Model& model)
    : StraightComponent(AirTerminalSingleDuctConstantVolumeNoReheat::iddObjectType(), model) {
    auto impl = getImpl<detail::AirTerminalSingleDuctConstantVolumeNoReheat_Impl>();
    OS_ASSERT(impl);
    detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
    impl->canonicalize(context);
    auto alwaysOn = model.alwaysOnDiscreteSchedule();
    OS_ASSERT(setAvailabilitySchedule(alwaysOn));
    autosizeMaximumAirFlowRate();
  }

  AirTerminalSingleDuctConstantVolumeNoReheat::AirTerminalSingleDuctConstantVolumeNoReheat(const Model& model, Schedule& availabilitySchedule)
    : StraightComponent(AirTerminalSingleDuctConstantVolumeNoReheat::iddObjectType(), model) {
    auto impl = getImpl<detail::AirTerminalSingleDuctConstantVolumeNoReheat_Impl>();
    OS_ASSERT(impl);
    detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
    impl->canonicalize(context);
    OS_ASSERT(setAvailabilitySchedule(availabilitySchedule));
    autosizeMaximumAirFlowRate();
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

  boost::optional<double> AirTerminalSingleDuctConstantVolumeNoReheat::autosizedMaximumAirFlowRate() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeNoReheat_Impl>()->autosizedMaximumAirFlowRate();
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
      auto schedule =
        getObject<ModelObject>().getModelObjectTarget<Schedule>(AirTerminal_SingleDuct_ConstantVolume_NoReheatFields::AvailabilityScheduleName);
      if (!schedule) {
        LOG_FREE(Error, "openstudio.epmodel.AirTerminalSingleDuctConstantVolumeNoReheat",
                 "Required availability schedule not set, repairing persisted state with the model always-on discrete schedule");
        schedule = model().alwaysOnDiscreteSchedule();
        const bool ok = const_cast<AirTerminalSingleDuctConstantVolumeNoReheat_Impl*>(this)->setAvailabilitySchedule(*schedule);
        OS_ASSERT(ok);
        schedule =
          getObject<ModelObject>().getModelObjectTarget<Schedule>(AirTerminal_SingleDuct_ConstantVolume_NoReheatFields::AvailabilityScheduleName);
      }
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

    boost::optional<double> AirTerminalSingleDuctConstantVolumeNoReheat_Impl::autosizedMaximumAirFlowRate() const {
      return boost::none;
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

      if (auto thermalZone = owningThermalZoneForBranchNode(model(), node)) {
        if (!thermalZone->getImpl<detail::ThermalZone_Impl>()->getZoneHVACEquipmentList().addEquipment(thisObject)) {
          return false;
        }
      }

      return true;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
