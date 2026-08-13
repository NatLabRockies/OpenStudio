/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/AirTerminalSingleDuctConstantVolumeNoReheat.hpp"
#include "StraightComponent/AirTerminalSingleDuctConstantVolumeNoReheat_Impl.hpp"

#include "HVACComponent.hpp"
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
#include "StraightComponent/SingleDuctTerminalInsertionPlan.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/Logger.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/AirTerminal_SingleDuct_ConstantVolume_NoReheat_FieldEnums.hxx>
#include <utilities/idd/ZoneHVAC_AirDistributionUnit_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <algorithm>

namespace openstudio {
namespace epmodel {

  namespace {

    boost::optional<ThermalZone> thermalZoneContainingTerminal(const Model& model, const ModelObject& terminal) {
      for (const auto& zone : model.getConcreteModelObjects<ThermalZone>()) {
        const auto equipment = zone.equipment();
        if (std::ranges::find(equipment, terminal) != equipment.end()) {
          return zone;
        }
      }
      return boost::none;
    }

    bool unregisterTerminalFromThermalZone(const ModelObject& terminal, ThermalZone& thermalZone) {
      auto zoneImpl = thermalZone.getImpl<detail::ThermalZone_Impl>();
      OS_ASSERT(zoneImpl);
      return zoneImpl->getZoneHVACEquipmentList().removeEquipment(terminal);
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

    bool AirTerminalSingleDuctConstantVolumeNoReheat_Impl::removeFromLoop() {
      auto thisObject = getObject<openstudio::epmodel::ModelObject>();
      auto thermalZone = thermalZoneContainingTerminal(model(), thisObject);
      auto inletNode = inletModelObject();
      auto outletNode = outletModelObject();
      const bool shouldRemoveTerminalInletNode = inletNode && outletNode && isDemandBranchStartComponent();

      if (!StraightComponent_Impl::removeFromLoop()) {
        return false;
      }

      if (thermalZone && !unregisterTerminalFromThermalZone(thisObject, *thermalZone)) {
        return false;
      }

      if (auto adu = zoneHVACAirDistributionUnit()) {
        if (!adu->setPointer(openstudio::ZoneHVAC_AirDistributionUnitFields::AirDistributionUnitOutletNodeName, openstudio::Handle())) {
          return false;
        }
        if (!adu->setString(openstudio::ZoneHVAC_AirDistributionUnitFields::AirTerminalObjectType, "")) {
          return false;
        }
        if (!adu->setPointer(openstudio::ZoneHVAC_AirDistributionUnitFields::AirTerminalName, openstudio::Handle())) {
          return false;
        }
      }

      setPointer(inletPort(), openstudio::Handle(), false);
      setPointer(outletPort(), openstudio::Handle(), false);

      if (shouldRemoveTerminalInletNode) {
        if (auto node = inletNode->optionalCast<openstudio::epmodel::Node>()) {
          node->remove();
        }
      }

      return true;
    }

    bool AirTerminalSingleDuctConstantVolumeNoReheat_Impl::addToNode(Node& node) {
      return addToNode(node, AddToNodeFailureStage::None);
    }

    bool AirTerminalSingleDuctConstantVolumeNoReheat_Impl::addToNode(Node& node, AddToNodeFailureStage failureStage) {
      if (node.model() != model()) {
        return false;
      }

      auto thisObject = getObject<openstudio::epmodel::ModelObject>();
      auto terminal = thisObject.cast<StraightComponent>();
      auto plan = SingleDuctTerminalInsertionPlan::prepare(terminal, node);
      if (!plan) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctConstantVolumeNoReheat",
                 "addToNode requires a terminal-free effective demand branch on the target AirLoopHVAC.");
        return false;
      }

      if (!plan->apply(failureStage == AddToNodeFailureStage::AfterADUUpdateBeforeZoneRegistration)) {
        return false;
      }
      return plan->commit();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
