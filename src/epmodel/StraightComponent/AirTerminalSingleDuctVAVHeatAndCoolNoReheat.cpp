/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/AirTerminalSingleDuctVAVHeatAndCoolNoReheat.hpp"
#include "StraightComponent/AirTerminalSingleDuctVAVHeatAndCoolNoReheat_Impl.hpp"

#include "HVACComponent/ThermalZone.hpp"
#include "HVACComponent/ThermalZone_Impl.hpp"
#include "Model.hpp"
#include "ModelObject.hpp"
#include "ModelObject/ZoneHVACAirDistributionUnit.hpp"
#include "ModelObject/ZoneHVACAirDistributionUnit_Impl.hpp"
#include "ModelObject/ZoneHVACEquipmentList.hpp"
#include "Node.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"
#include "StraightComponent/SingleDuctTerminalInsertionPlan.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/Logger.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/AirTerminal_SingleDuct_VAV_HeatAndCool_NoReheat_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/ZoneHVAC_AirDistributionUnit_FieldEnums.hxx>
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

  AirTerminalSingleDuctVAVHeatAndCoolNoReheat::AirTerminalSingleDuctVAVHeatAndCoolNoReheat(const Model& model)
    : StraightComponent(AirTerminalSingleDuctVAVHeatAndCoolNoReheat::iddObjectType(), model) {
    autosizeMaximumAirFlowRate();
    OS_ASSERT(setZoneMinimumAirFlowFraction(0.0));
  }

  AirTerminalSingleDuctVAVHeatAndCoolNoReheat::AirTerminalSingleDuctVAVHeatAndCoolNoReheat(
    std::shared_ptr<detail::AirTerminalSingleDuctVAVHeatAndCoolNoReheat_Impl> impl)
    : StraightComponent(std::move(impl)) {}

  IddObjectType AirTerminalSingleDuctVAVHeatAndCoolNoReheat::iddObjectType() {
    return IddObjectType::AirTerminal_SingleDuct_VAV_HeatAndCool_NoReheat;
  }

  bool AirTerminalSingleDuctVAVHeatAndCoolNoReheat::addToNode(Node& node) {
    return getImpl<detail::AirTerminalSingleDuctVAVHeatAndCoolNoReheat_Impl>()->addToNode(node);
  }

  boost::optional<Schedule> AirTerminalSingleDuctVAVHeatAndCoolNoReheat::availabilitySchedule() const {
    return getImpl<detail::AirTerminalSingleDuctVAVHeatAndCoolNoReheat_Impl>()->availabilitySchedule();
  }

  bool AirTerminalSingleDuctVAVHeatAndCoolNoReheat::setAvailabilitySchedule(Schedule& schedule) {
    return getImpl<detail::AirTerminalSingleDuctVAVHeatAndCoolNoReheat_Impl>()->setAvailabilitySchedule(schedule);
  }

  void AirTerminalSingleDuctVAVHeatAndCoolNoReheat::resetAvailabilitySchedule() {
    getImpl<detail::AirTerminalSingleDuctVAVHeatAndCoolNoReheat_Impl>()->resetAvailabilitySchedule();
  }

  boost::optional<Schedule> AirTerminalSingleDuctVAVHeatAndCoolNoReheat::minimumAirFlowTurndownSchedule() const {
    return getImpl<detail::AirTerminalSingleDuctVAVHeatAndCoolNoReheat_Impl>()->minimumAirFlowTurndownSchedule();
  }

  bool AirTerminalSingleDuctVAVHeatAndCoolNoReheat::setMinimumAirFlowTurndownSchedule(Schedule& schedule) {
    return getImpl<detail::AirTerminalSingleDuctVAVHeatAndCoolNoReheat_Impl>()->setMinimumAirFlowTurndownSchedule(schedule);
  }

  void AirTerminalSingleDuctVAVHeatAndCoolNoReheat::resetMinimumAirFlowTurndownSchedule() {
    getImpl<detail::AirTerminalSingleDuctVAVHeatAndCoolNoReheat_Impl>()->resetMinimumAirFlowTurndownSchedule();
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

    boost::optional<ZoneHVACAirDistributionUnit> AirTerminalSingleDuctVAVHeatAndCoolNoReheat_Impl::zoneHVACAirDistributionUnit() const {
      auto terminal = getObject<openstudio::epmodel::ModelObject>();
      for (const auto& source : terminal.getSources(openstudio::IddObjectType::ZoneHVAC_AirDistributionUnit)) {
        if (auto adu = source.optionalCast<openstudio::epmodel::ZoneHVACAirDistributionUnit>()) {
          return adu;
        }
      }
      return boost::none;
    }

    bool AirTerminalSingleDuctVAVHeatAndCoolNoReheat_Impl::removeFromLoop() {
      auto thisObject = getObject<openstudio::epmodel::ModelObject>();
      auto thermalZone = thermalZoneContainingTerminal(model(), thisObject);
      auto inletNode = inletModelObject();
      auto outletNode = outletModelObject();
      const bool shouldRemoveTerminalInletNode = inletNode && outletNode && isDemandBranchStartComponent();

      bool removedFromAirLoop = false;
      if (inletNode && outletNode) {
        if (!StraightComponent_Impl::removeFromLoop()) {
          return false;
        }
        removedFromAirLoop = true;
      }

      if (thermalZone && !unregisterTerminalFromThermalZone(thisObject, *thermalZone)) {
        return false;
      }

      bool cleanedADU = false;
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
        cleanedADU = true;
      }

      setPointer(inletPort(), openstudio::Handle(), false);
      setPointer(outletPort(), openstudio::Handle(), false);

      if (shouldRemoveTerminalInletNode) {
        if (auto node = inletNode->optionalCast<openstudio::epmodel::Node>()) {
          node->remove();
        }
      }

      return removedFromAirLoop || static_cast<bool>(thermalZone) || cleanedADU;
    }

    bool AirTerminalSingleDuctVAVHeatAndCoolNoReheat_Impl::addToNode(Node& node) {
      if (node.model() != model()) {
        return false;
      }

      auto thisObject = getObject<openstudio::epmodel::ModelObject>();
      auto terminal = thisObject.cast<StraightComponent>();
      auto plan = SingleDuctTerminalInsertionPlan::prepare(terminal, node);
      if (!plan) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctVAVHeatAndCoolNoReheat",
                 "addToNode requires a terminal-free effective demand branch on the target AirLoopHVAC.");
        return false;
      }

      if (!plan->apply()) {
        return false;
      }
      return plan->commit();
    }

    boost::optional<Schedule> AirTerminalSingleDuctVAVHeatAndCoolNoReheat_Impl::availabilitySchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(
        openstudio::AirTerminal_SingleDuct_VAV_HeatAndCool_NoReheatFields::AvailabilityScheduleName);
    }

    bool AirTerminalSingleDuctVAVHeatAndCoolNoReheat_Impl::setAvailabilitySchedule(Schedule& schedule) {
      return ModelObject_Impl::setSchedule(openstudio::AirTerminal_SingleDuct_VAV_HeatAndCool_NoReheatFields::AvailabilityScheduleName,
                                           "AirTerminalSingleDuctVAVHeatAndCoolNoReheat", "Availability", schedule);
    }

    void AirTerminalSingleDuctVAVHeatAndCoolNoReheat_Impl::resetAvailabilitySchedule() {
      OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_VAV_HeatAndCool_NoReheatFields::AvailabilityScheduleName, ""));
    }

    boost::optional<Schedule> AirTerminalSingleDuctVAVHeatAndCoolNoReheat_Impl::minimumAirFlowTurndownSchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(
        openstudio::AirTerminal_SingleDuct_VAV_HeatAndCool_NoReheatFields::MinimumAirFlowTurndownScheduleName);
    }

    bool AirTerminalSingleDuctVAVHeatAndCoolNoReheat_Impl::setMinimumAirFlowTurndownSchedule(Schedule& schedule) {
      return ModelObject_Impl::setSchedule(openstudio::AirTerminal_SingleDuct_VAV_HeatAndCool_NoReheatFields::MinimumAirFlowTurndownScheduleName,
                                           "AirTerminalSingleDuctVAVHeatAndCoolNoReheat", "Minimum Air Flow Turndown", schedule);
    }

    void AirTerminalSingleDuctVAVHeatAndCoolNoReheat_Impl::resetMinimumAirFlowTurndownSchedule() {
      OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_VAV_HeatAndCool_NoReheatFields::MinimumAirFlowTurndownScheduleName, ""));
    }

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
