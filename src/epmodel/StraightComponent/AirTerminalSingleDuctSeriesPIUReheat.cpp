/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/AirTerminalSingleDuctSeriesPIUReheat.hpp"
#include "StraightComponent/AirTerminalSingleDuctSeriesPIUReheat_Impl.hpp"

#include "HVACComponent/ThermalZone.hpp"
#include "HVACComponent/ThermalZone_Impl.hpp"
#include "HVACComponent.hpp"
#include "Branch.hpp"
#include "Loop/AirLoopHVAC.hpp"
#include "Loop/AirLoopHVAC_Impl.hpp"
#include "Loop/PlantLoop.hpp"
#include "Loop/PlantLoop_Impl.hpp"
#include "Mixer/AirLoopHVACZoneMixer.hpp"
#include "Mixer/AirLoopHVACZoneMixer_Impl.hpp"
#include "Model.hpp"
#include "ModelObject.hpp"
#include "ModelObject/ZoneHVACAirDistributionUnit.hpp"
#include "ModelObject/ZoneHVACAirDistributionUnit_Impl.hpp"
#include "ModelObject/ZoneHVACEquipmentConnections.hpp"
#include "ModelObject/ZoneHVACEquipmentConnections_Impl.hpp"
#include "ModelObject/ZoneHVACEquipmentList.hpp"
#include "ModelObject/ZoneHVACEquipmentList_Impl.hpp"
#include "Node.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"
#include "Splitter/AirLoopHVACZoneSplitter.hpp"
#include "StraightComponent/FanConstantVolume.hpp"
#include "StraightComponent/FanOnOff.hpp"
#include "StraightComponent/FanSystemModel.hpp"
#include "StraightComponent/FanVariableVolume.hpp"
#include "WaterToAirComponent/WaterToAirComponent.hpp"
#include "WaterToAirComponent/WaterToAirComponent_Impl.hpp"

#include <algorithm>
#include <memory>
#include <vector>
#include <utilities/core/Assert.hpp>
#include <utilities/core/Logger.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/AirTerminal_SingleDuct_SeriesPIU_Reheat_FieldEnums.hxx>
#include <utilities/idd/Coil_Heating_Electric_FieldEnums.hxx>
#include <utilities/idd/Coil_Heating_Fuel_FieldEnums.hxx>
#include <utilities/idd/Coil_Heating_Water_FieldEnums.hxx>
#include <utilities/idd/Fan_ConstantVolume_FieldEnums.hxx>
#include <utilities/idd/Fan_OnOff_FieldEnums.hxx>
#include <utilities/idd/Fan_SystemModel_FieldEnums.hxx>
#include <utilities/idd/Fan_VariableVolume_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/ZoneHVAC_AirDistributionUnit_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  namespace {

    bool isSupportedSeriesPIUFan(const HVACComponent& hvacComponent) {
      const auto type = hvacComponent.iddObject().type();
      return (type == IddObjectType::Fan_ConstantVolume) || (type == IddObjectType::Fan_SystemModel) || (type == IddObjectType::Fan_OnOff)
             || (type == IddObjectType::Fan_VariableVolume);
    }

    bool isSupportedSeriesPIUReheatCoil(const HVACComponent& hvacComponent) {
      const auto type = hvacComponent.iddObject().type();
      return (type == IddObjectType::Coil_Heating_Electric) || (type == IddObjectType::Coil_Heating_Fuel)
             || (type == IddObjectType::Coil_Heating_Water);
    }

    boost::optional<ThermalZone> owningThermalZoneForZoneNode(const Model& model, const Node& node) {
      for (const auto& connections : model.getConcreteModelObjects<ZoneHVACEquipmentConnections>()) {
        const auto inletNodes = connections.zoneAirInletNodes();
        if (std::ranges::find(inletNodes, node) != inletNodes.end()) {
          return connections.thermalZone();
        }
      }
      return boost::none;
    }

    bool isServedZoneReturnNode(const boost::optional<ThermalZone>& thermalZone, const ModelObject& nodeObject) {
      auto node = nodeObject.optionalCast<Node>();
      if (!thermalZone || !node) {
        return false;
      }

      auto zoneImpl = thermalZone->getImpl<detail::ThermalZone_Impl>();
      OS_ASSERT(zoneImpl);
      auto connections = zoneImpl->zoneHVACEquipmentConnections();
      if (!connections) {
        return false;
      }

      const auto returnNodes = connections->zoneReturnAirNodes();
      return std::ranges::find(returnNodes, *node) != returnNodes.end();
    }

    boost::optional<ThermalZone> thermalZoneContainingTerminal(const Model& model, const ModelObject& terminal) {
      for (const auto& thermalZone : model.getConcreteModelObjects<ThermalZone>()) {
        const auto equipment = thermalZone.equipment();
        if (std::ranges::find(equipment, terminal) != equipment.end()) {
          return thermalZone;
        }
      }
      return boost::none;
    }

    boost::optional<ThermalZone> thermalZoneContainingExhaustNode(const Model& model, const Node& node) {
      for (const auto& thermalZone : model.getConcreteModelObjects<ThermalZone>()) {
        auto zoneImpl = thermalZone.getImpl<detail::ThermalZone_Impl>();
        OS_ASSERT(zoneImpl);
        auto connections = zoneImpl->zoneHVACEquipmentConnections();
        if (connections) {
          const auto exhaustNodes = connections->zoneAirExhaustNodes();
          if (std::ranges::find(exhaustNodes, node) != exhaustNodes.end()) {
            return thermalZone;
          }
        }
      }
      return boost::none;
    }

    bool registerTerminalWithZone(ThermalZone& thermalZone, const ModelObject& terminal) {
      auto zoneImpl = thermalZone.getImpl<detail::ThermalZone_Impl>();
      OS_ASSERT(zoneImpl);

      if (!zoneImpl->getZoneHVACEquipmentList().addEquipment(terminal)) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctSeriesPIUReheat",
                 "Failed to register " << terminal.briefDescription() << " with thermal zone " << thermalZone.briefDescription() << ".");
        return false;
      }

      return true;
    }

    bool unregisterTerminalFromZone(ThermalZone& thermalZone, const ModelObject& terminal) {
      auto zoneImpl = thermalZone.getImpl<detail::ThermalZone_Impl>();
      OS_ASSERT(zoneImpl);
      return zoneImpl->getZoneHVACEquipmentList().removeEquipment(terminal);
    }

    struct DemandBranchRemovalPlan
    {
      bool valid = true;
      boost::optional<PlantLoop> plantLoop;
    };

    DemandBranchRemovalPlan demandBranchRemovalPlan(const boost::optional<HVACComponent>& coil) {
      DemandBranchRemovalPlan result;
      if (!coil) {
        return result;
      }

      auto plantLoop = coil->plantLoop();
      if (!plantLoop) {
        return result;
      }

      boost::optional<ModelObject> inletObject;
      boost::optional<ModelObject> outletObject;
      if (auto straightCoil = coil->optionalCast<StraightComponent>()) {
        inletObject = straightCoil->inletModelObject();
        outletObject = straightCoil->outletModelObject();
      } else if (auto waterCoil = coil->optionalCast<WaterToAirComponent>()) {
        inletObject = waterCoil->waterInletModelObject();
        outletObject = waterCoil->waterOutletModelObject();
      }
      const auto inletNode = inletObject ? inletObject->optionalCast<Node>() : boost::none;
      const auto outletNode = outletObject ? outletObject->optionalCast<Node>() : boost::none;
      auto plantLoopImpl = plantLoop->getImpl<detail::PlantLoop_Impl>();
      OS_ASSERT(plantLoopImpl);
      const auto inletBranch = inletNode ? plantLoopImpl->branchForNode(*inletNode) : boost::none;
      const auto outletBranch = outletNode ? plantLoopImpl->branchForNode(*outletNode) : boost::none;
      const auto equipmentBranches = plantLoopImpl->demandEquipmentBranches();

      boost::optional<Branch> targetBranch;
      for (const auto& candidate : {inletBranch, outletBranch}) {
        if (!candidate) {
          continue;
        }
        if (std::ranges::find(equipmentBranches, *candidate) == equipmentBranches.end() || (targetBranch && (*targetBranch != *candidate))) {
          result.valid = false;
          return result;
        }
        targetBranch = *candidate;
      }

      if (!targetBranch) {
        result.valid = false;
        return result;
      }

      result.plantLoop = *plantLoop;
      return result;
    }

    bool syncFanAvailabilityWithLoop(HVACComponent& fan, Schedule& schedule) {
      const auto type = fan.iddObject().type();
      if (type == IddObjectType::Fan_ConstantVolume || type == IddObjectType::OS_Fan_ConstantVolume) {
        return fan.setPointer(openstudio::Fan_ConstantVolumeFields::AvailabilityScheduleName, schedule.handle());
      }
      if (type == IddObjectType::Fan_SystemModel || type == IddObjectType::OS_Fan_SystemModel) {
        return fan.setPointer(openstudio::Fan_SystemModelFields::AvailabilityScheduleName, schedule.handle());
      }
      if (type == IddObjectType::Fan_OnOff || type == IddObjectType::OS_Fan_OnOff) {
        return fan.setPointer(openstudio::Fan_OnOffFields::AvailabilityScheduleName, schedule.handle());
      }
      if (type == IddObjectType::Fan_VariableVolume || type == IddObjectType::OS_Fan_VariableVolume) {
        return fan.setPointer(openstudio::Fan_VariableVolumeFields::AvailabilityScheduleName, schedule.handle());
      }
      return false;
    }

    void applyConstructorDefaults(AirTerminalSingleDuctSeriesPIUReheat& terminal) {
      terminal.autosizeMaximumAirFlowRate();
      terminal.autosizeMaximumPrimaryAirFlowRate();
      terminal.autosizeMinimumPrimaryAirFlowFraction();
      terminal.autosizeMaximumHotWaterorSteamFlowRate();
      const bool minimumFlowSet = terminal.setMinimumHotWaterorSteamFlowRate(0.0);
      const bool convergenceSet = terminal.setConvergenceTolerance(0.001);
      const bool fanControlSet = terminal.setFanControlType("ConstantSpeed");
      const bool fanTurnDownSet = terminal.setMinimumFanTurnDownRatio(0.3);
      const bool heatingControlSet = terminal.setHeatingControlType("Staged");
      const bool designTemperatureSet = terminal.setDesignHeatingDischargeAirTemperature(32.1);
      const bool highLimitTemperatureSet = terminal.setHighLimitHeatingDischargeAirTemperature(37.7);
      OS_ASSERT(minimumFlowSet && convergenceSet && fanControlSet && fanTurnDownSet && heatingControlSet && designTemperatureSet
                && highLimitTemperatureSet);
    }

  }  // namespace

  AirTerminalSingleDuctSeriesPIUReheat::AirTerminalSingleDuctSeriesPIUReheat(const Model& model)
    : StraightComponent(AirTerminalSingleDuctSeriesPIUReheat::iddObjectType(), model) {
    applyConstructorDefaults(*this);
  }

  AirTerminalSingleDuctSeriesPIUReheat::AirTerminalSingleDuctSeriesPIUReheat(const Model& model, HVACComponent& fan, HVACComponent& reheatCoil)
    : StraightComponent(AirTerminalSingleDuctSeriesPIUReheat::iddObjectType(), model) {
    // Validate both child relationships before assigning either one. This
    // keeps a failed constructor from temporarily taking ownership of, and
    // then deleting, a valid child supplied by the caller.
    if ((fan.model() != model) || !isSupportedSeriesPIUFan(fan)) {
      remove();
      LOG_FREE_AND_THROW("openstudio.epmodel.AirTerminalSingleDuctSeriesPIUReheat",
                         "Could not construct " << briefDescription() << ", because the fan type was invalid or from another model.");
    }
    if ((reheatCoil.model() != model) || !isSupportedSeriesPIUReheatCoil(reheatCoil)) {
      remove();
      LOG_FREE_AND_THROW("openstudio.epmodel.AirTerminalSingleDuctSeriesPIUReheat",
                         "Could not construct " << briefDescription() << ", because the reheat coil type was invalid or from another model.");
    }
    if (!setFan(fan)) {
      remove();
      LOG_FREE_AND_THROW("openstudio.epmodel.AirTerminalSingleDuctSeriesPIUReheat",
                         "Could not construct " << briefDescription() << ", because the fan type was invalid or from another model.");
    }
    if (!setReheatCoil(reheatCoil)) {
      remove();
      LOG_FREE_AND_THROW("openstudio.epmodel.AirTerminalSingleDuctSeriesPIUReheat",
                         "Could not construct " << briefDescription() << ", because the reheat coil type was invalid or from another model.");
    }
    applyConstructorDefaults(*this);
  }

  AirTerminalSingleDuctSeriesPIUReheat::AirTerminalSingleDuctSeriesPIUReheat(std::shared_ptr<detail::AirTerminalSingleDuctSeriesPIUReheat_Impl> impl)
    : StraightComponent(std::move(impl)) {}

  IddObjectType AirTerminalSingleDuctSeriesPIUReheat::iddObjectType() {
    return IddObjectType::AirTerminal_SingleDuct_SeriesPIU_Reheat;
  }

  std::vector<std::string> AirTerminalSingleDuctSeriesPIUReheat::fanControlTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::FanControlType);
  }

  std::vector<std::string> AirTerminalSingleDuctSeriesPIUReheat::heatingControlTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::HeatingControlType);
  }

  boost::optional<Schedule> AirTerminalSingleDuctSeriesPIUReheat::availabilitySchedule() const {
    return getImpl<detail::AirTerminalSingleDuctSeriesPIUReheat_Impl>()->availabilitySchedule();
  }

  bool AirTerminalSingleDuctSeriesPIUReheat::setAvailabilitySchedule(Schedule& schedule) {
    return getImpl<detail::AirTerminalSingleDuctSeriesPIUReheat_Impl>()->setAvailabilitySchedule(schedule);
  }

  void AirTerminalSingleDuctSeriesPIUReheat::resetAvailabilitySchedule() {
    getImpl<detail::AirTerminalSingleDuctSeriesPIUReheat_Impl>()->resetAvailabilitySchedule();
  }

  bool AirTerminalSingleDuctSeriesPIUReheat::addToNode(Node& node) {
    return getImpl<detail::AirTerminalSingleDuctSeriesPIUReheat_Impl>()->addToNode(node);
  }

  HVACComponent AirTerminalSingleDuctSeriesPIUReheat::fan() const {
    return getImpl<detail::AirTerminalSingleDuctSeriesPIUReheat_Impl>()->fan();
  }

  bool AirTerminalSingleDuctSeriesPIUReheat::setFan(const HVACComponent& fan) {
    return getImpl<detail::AirTerminalSingleDuctSeriesPIUReheat_Impl>()->setFan(fan);
  }

  HVACComponent AirTerminalSingleDuctSeriesPIUReheat::reheatCoil() const {
    return getImpl<detail::AirTerminalSingleDuctSeriesPIUReheat_Impl>()->reheatCoil();
  }

  bool AirTerminalSingleDuctSeriesPIUReheat::setReheatCoil(const HVACComponent& coil) {
    return getImpl<detail::AirTerminalSingleDuctSeriesPIUReheat_Impl>()->setReheatCoil(coil);
  }

  boost::optional<Node> AirTerminalSingleDuctSeriesPIUReheat::secondaryAirInletNode() const {
    return getImpl<detail::AirTerminalSingleDuctSeriesPIUReheat_Impl>()->secondaryAirInletNode();
  }

  boost::optional<double> AirTerminalSingleDuctSeriesPIUReheat::maximumAirFlowRate() const {
    return getImpl<detail::AirTerminalSingleDuctSeriesPIUReheat_Impl>()->maximumAirFlowRate();
  }

  bool AirTerminalSingleDuctSeriesPIUReheat::isMaximumAirFlowRateAutosized() const {
    return getImpl<detail::AirTerminalSingleDuctSeriesPIUReheat_Impl>()->isMaximumAirFlowRateAutosized();
  }

  bool AirTerminalSingleDuctSeriesPIUReheat::setMaximumAirFlowRate(double maximumAirFlowRate) {
    return getImpl<detail::AirTerminalSingleDuctSeriesPIUReheat_Impl>()->setMaximumAirFlowRate(maximumAirFlowRate);
  }

  void AirTerminalSingleDuctSeriesPIUReheat::autosizeMaximumAirFlowRate() {
    getImpl<detail::AirTerminalSingleDuctSeriesPIUReheat_Impl>()->autosizeMaximumAirFlowRate();
  }

  boost::optional<double> AirTerminalSingleDuctSeriesPIUReheat::maximumPrimaryAirFlowRate() const {
    return getImpl<detail::AirTerminalSingleDuctSeriesPIUReheat_Impl>()->maximumPrimaryAirFlowRate();
  }

  bool AirTerminalSingleDuctSeriesPIUReheat::isMaximumPrimaryAirFlowRateAutosized() const {
    return getImpl<detail::AirTerminalSingleDuctSeriesPIUReheat_Impl>()->isMaximumPrimaryAirFlowRateAutosized();
  }

  bool AirTerminalSingleDuctSeriesPIUReheat::setMaximumPrimaryAirFlowRate(double maximumPrimaryAirFlowRate) {
    return getImpl<detail::AirTerminalSingleDuctSeriesPIUReheat_Impl>()->setMaximumPrimaryAirFlowRate(maximumPrimaryAirFlowRate);
  }

  void AirTerminalSingleDuctSeriesPIUReheat::autosizeMaximumPrimaryAirFlowRate() {
    getImpl<detail::AirTerminalSingleDuctSeriesPIUReheat_Impl>()->autosizeMaximumPrimaryAirFlowRate();
  }

  boost::optional<double> AirTerminalSingleDuctSeriesPIUReheat::minimumPrimaryAirFlowFraction() const {
    return getImpl<detail::AirTerminalSingleDuctSeriesPIUReheat_Impl>()->minimumPrimaryAirFlowFraction();
  }

  bool AirTerminalSingleDuctSeriesPIUReheat::isMinimumPrimaryAirFlowFractionAutosized() const {
    return getImpl<detail::AirTerminalSingleDuctSeriesPIUReheat_Impl>()->isMinimumPrimaryAirFlowFractionAutosized();
  }

  bool AirTerminalSingleDuctSeriesPIUReheat::setMinimumPrimaryAirFlowFraction(double minimumPrimaryAirFlowFraction) {
    return getImpl<detail::AirTerminalSingleDuctSeriesPIUReheat_Impl>()->setMinimumPrimaryAirFlowFraction(minimumPrimaryAirFlowFraction);
  }

  void AirTerminalSingleDuctSeriesPIUReheat::autosizeMinimumPrimaryAirFlowFraction() {
    getImpl<detail::AirTerminalSingleDuctSeriesPIUReheat_Impl>()->autosizeMinimumPrimaryAirFlowFraction();
  }

  boost::optional<double> AirTerminalSingleDuctSeriesPIUReheat::maximumHotWaterorSteamFlowRate() const {
    return getImpl<detail::AirTerminalSingleDuctSeriesPIUReheat_Impl>()->maximumHotWaterorSteamFlowRate();
  }

  bool AirTerminalSingleDuctSeriesPIUReheat::isMaximumHotWaterorSteamFlowRateAutosized() const {
    return getImpl<detail::AirTerminalSingleDuctSeriesPIUReheat_Impl>()->isMaximumHotWaterorSteamFlowRateAutosized();
  }

  bool AirTerminalSingleDuctSeriesPIUReheat::setMaximumHotWaterorSteamFlowRate(double maximumHotWaterorSteamFlowRate) {
    return getImpl<detail::AirTerminalSingleDuctSeriesPIUReheat_Impl>()->setMaximumHotWaterorSteamFlowRate(maximumHotWaterorSteamFlowRate);
  }

  void AirTerminalSingleDuctSeriesPIUReheat::resetMaximumHotWaterorSteamFlowRate() {
    getImpl<detail::AirTerminalSingleDuctSeriesPIUReheat_Impl>()->resetMaximumHotWaterorSteamFlowRate();
  }

  void AirTerminalSingleDuctSeriesPIUReheat::autosizeMaximumHotWaterorSteamFlowRate() {
    getImpl<detail::AirTerminalSingleDuctSeriesPIUReheat_Impl>()->autosizeMaximumHotWaterorSteamFlowRate();
  }

  double AirTerminalSingleDuctSeriesPIUReheat::minimumHotWaterorSteamFlowRate() const {
    return getImpl<detail::AirTerminalSingleDuctSeriesPIUReheat_Impl>()->minimumHotWaterorSteamFlowRate();
  }

  bool AirTerminalSingleDuctSeriesPIUReheat::setMinimumHotWaterorSteamFlowRate(double minimumHotWaterorSteamFlowRate) {
    return getImpl<detail::AirTerminalSingleDuctSeriesPIUReheat_Impl>()->setMinimumHotWaterorSteamFlowRate(minimumHotWaterorSteamFlowRate);
  }

  double AirTerminalSingleDuctSeriesPIUReheat::convergenceTolerance() const {
    return getImpl<detail::AirTerminalSingleDuctSeriesPIUReheat_Impl>()->convergenceTolerance();
  }

  bool AirTerminalSingleDuctSeriesPIUReheat::setConvergenceTolerance(double convergenceTolerance) {
    return getImpl<detail::AirTerminalSingleDuctSeriesPIUReheat_Impl>()->setConvergenceTolerance(convergenceTolerance);
  }

  std::string AirTerminalSingleDuctSeriesPIUReheat::fanControlType() const {
    return getImpl<detail::AirTerminalSingleDuctSeriesPIUReheat_Impl>()->fanControlType();
  }

  bool AirTerminalSingleDuctSeriesPIUReheat::setFanControlType(const std::string& fanControlType) {
    return getImpl<detail::AirTerminalSingleDuctSeriesPIUReheat_Impl>()->setFanControlType(fanControlType);
  }

  double AirTerminalSingleDuctSeriesPIUReheat::minimumFanTurnDownRatio() const {
    return getImpl<detail::AirTerminalSingleDuctSeriesPIUReheat_Impl>()->minimumFanTurnDownRatio();
  }

  bool AirTerminalSingleDuctSeriesPIUReheat::setMinimumFanTurnDownRatio(double minimumFanTurnDownRatio) {
    return getImpl<detail::AirTerminalSingleDuctSeriesPIUReheat_Impl>()->setMinimumFanTurnDownRatio(minimumFanTurnDownRatio);
  }

  std::string AirTerminalSingleDuctSeriesPIUReheat::heatingControlType() const {
    return getImpl<detail::AirTerminalSingleDuctSeriesPIUReheat_Impl>()->heatingControlType();
  }

  bool AirTerminalSingleDuctSeriesPIUReheat::setHeatingControlType(const std::string& heatingControlType) {
    return getImpl<detail::AirTerminalSingleDuctSeriesPIUReheat_Impl>()->setHeatingControlType(heatingControlType);
  }

  double AirTerminalSingleDuctSeriesPIUReheat::designHeatingDischargeAirTemperature() const {
    return getImpl<detail::AirTerminalSingleDuctSeriesPIUReheat_Impl>()->designHeatingDischargeAirTemperature();
  }

  bool AirTerminalSingleDuctSeriesPIUReheat::setDesignHeatingDischargeAirTemperature(double designHeatingDischargeAirTemperature) {
    return getImpl<detail::AirTerminalSingleDuctSeriesPIUReheat_Impl>()->setDesignHeatingDischargeAirTemperature(
      designHeatingDischargeAirTemperature);
  }

  double AirTerminalSingleDuctSeriesPIUReheat::highLimitHeatingDischargeAirTemperature() const {
    return getImpl<detail::AirTerminalSingleDuctSeriesPIUReheat_Impl>()->highLimitHeatingDischargeAirTemperature();
  }

  bool AirTerminalSingleDuctSeriesPIUReheat::setHighLimitHeatingDischargeAirTemperature(double highLimitHeatingDischargeAirTemperature) {
    return getImpl<detail::AirTerminalSingleDuctSeriesPIUReheat_Impl>()->setHighLimitHeatingDischargeAirTemperature(
      highLimitHeatingDischargeAirTemperature);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    // Owns the complete provisional insertion of a series PIU. Primary air
    // topology exists for terminal-only branches; secondary-air, exhaust,
    // equipment, and ADU projections are enrolled only for a served zone.
    class AirTerminalSingleDuctSeriesPIUReheat_Impl::InsertionPlan
    {
     public:
      static std::unique_ptr<InsertionPlan> prepare(AirTerminalSingleDuctSeriesPIUReheat_Impl& terminalImpl, AirLoopHVAC airLoop,
                                                    AirLoopHVACZoneSplitter splitter, unsigned branchIndex, Node outletNode,
                                                    boost::optional<ThermalZone> thermalZone) {
        auto terminal = terminalImpl.getObject<ModelObject>();
        const std::string inletNodeName = outletNode.nameString() + " - " + terminal.nameString() + " Inlet Node";
        const bool inletNodeExisted = static_cast<bool>(terminalImpl.model().getConcreteModelObjectByName<Node>(inletNodeName));
        auto inletNode = terminalImpl.model().getOrCreateTransientByName<Node>(inletNodeName);

        boost::optional<Node> secondaryNode;
        bool secondaryNodeExisted = false;
        if (thermalZone) {
          const std::string secondaryNodeName = outletNode.nameString() + " - " + terminal.nameString() + " Secondary Air Inlet Node";
          secondaryNodeExisted = static_cast<bool>(terminalImpl.model().getConcreteModelObjectByName<Node>(secondaryNodeName));
          secondaryNode = terminalImpl.model().getOrCreateTransientByName<Node>(secondaryNodeName);
        }

        auto plan = std::unique_ptr<InsertionPlan>(new InsertionPlan(terminalImpl, std::move(airLoop), std::move(splitter), branchIndex,
                                                                     std::move(outletNode), std::move(inletNode), !inletNodeExisted,
                                                                     std::move(thermalZone), std::move(secondaryNode), !secondaryNodeExisted));
        if (!plan->prepareTopology()) {
          return nullptr;
        }
        return plan;
      }

      InsertionPlan(const InsertionPlan&) = delete;
      InsertionPlan& operator=(const InsertionPlan&) = delete;
      InsertionPlan(InsertionPlan&& other) noexcept
        : m_state(other.m_state),
          m_terminalImpl(other.m_terminalImpl),
          m_airLoop(std::move(other.m_airLoop)),
          m_splitter(std::move(other.m_splitter)),
          m_branchIndex(other.m_branchIndex),
          m_outletNode(std::move(other.m_outletNode)),
          m_inletNode(std::move(other.m_inletNode)),
          m_inletNodeCreated(other.m_inletNodeCreated),
          m_thermalZone(std::move(other.m_thermalZone)),
          m_secondaryNode(std::move(other.m_secondaryNode)),
          m_secondaryNodeCreated(other.m_secondaryNodeCreated),
          m_zoneConnections(std::move(other.m_zoneConnections)),
          m_airDistributionUnit(std::move(other.m_airDistributionUnit)),
          m_previousADUOutletTarget(std::move(other.m_previousADUOutletTarget)),
          m_previousADUOutletNodeName(std::move(other.m_previousADUOutletNodeName)),
          m_splitterRewired(other.m_splitterRewired),
          m_inletAssigned(other.m_inletAssigned),
          m_outletAssigned(other.m_outletAssigned),
          m_secondaryAssigned(other.m_secondaryAssigned),
          m_exhaustRegistered(other.m_exhaustRegistered),
          m_aduUpdated(other.m_aduUpdated),
          m_zoneRegistered(other.m_zoneRegistered) {
        other.m_state = State::MovedFrom;
      }
      InsertionPlan& operator=(InsertionPlan&&) = delete;

      ~InsertionPlan() {
        if (m_state == State::Prepared) {
          cleanupPreparedState();
        }
      }

      bool commit() {
        OS_ASSERT(m_state == State::Prepared);
        auto fanObject = m_terminalImpl->fan();
        auto loopAvailability = m_airLoop.availabilitySchedule();
        if (!syncFanAvailabilityWithLoop(fanObject, loopAvailability)) {
          return false;
        }
        m_state = State::Committed;
        return true;
      }

     private:
      enum class State
      {
        Prepared,
        Committed,
        MovedFrom,
      };

      InsertionPlan(AirTerminalSingleDuctSeriesPIUReheat_Impl& terminalImpl, AirLoopHVAC airLoop, AirLoopHVACZoneSplitter splitter,
                    unsigned branchIndex, Node outletNode, Node inletNode, bool inletNodeCreated, boost::optional<ThermalZone> thermalZone,
                    boost::optional<Node> secondaryNode, bool secondaryNodeCreated)
        : m_terminalImpl(&terminalImpl),
          m_airLoop(std::move(airLoop)),
          m_splitter(std::move(splitter)),
          m_branchIndex(branchIndex),
          m_outletNode(std::move(outletNode)),
          m_inletNode(std::move(inletNode)),
          m_inletNodeCreated(inletNodeCreated),
          m_thermalZone(std::move(thermalZone)),
          m_secondaryNode(std::move(secondaryNode)),
          m_secondaryNodeCreated(secondaryNodeCreated) {}

      bool prepareTopology() {
        auto terminal = m_terminalImpl->getObject<ModelObject>();
        if (m_thermalZone) {
          auto zoneImpl = m_thermalZone->getImpl<detail::ThermalZone_Impl>();
          OS_ASSERT(zoneImpl);
          m_zoneConnections = zoneImpl->getZoneHVACEquipmentConnections();
          m_airDistributionUnit = m_terminalImpl->zoneHVACAirDistributionUnit();
          if (m_airDistributionUnit) {
            m_previousADUOutletNodeName =
              m_airDistributionUnit->getString(openstudio::ZoneHVAC_AirDistributionUnitFields::AirDistributionUnitOutletNodeName, false, true);
            if (auto target = m_airDistributionUnit->getTarget(openstudio::ZoneHVAC_AirDistributionUnitFields::AirDistributionUnitOutletNodeName)) {
              m_previousADUOutletTarget = target->optionalCast<ModelObject>();
            }
          }
        }

        if (!m_splitter.setOutletModelObject(m_branchIndex, m_inletNode.cast<ModelObject>())) {
          return false;
        }
        m_splitterRewired = true;
        if (!m_terminalImpl->setPointer(m_terminalImpl->inletPort(), m_inletNode.handle(), false)) {
          return false;
        }
        m_inletAssigned = true;
        if (!m_terminalImpl->setPointer(m_terminalImpl->outletPort(), m_outletNode.handle(), false)) {
          return false;
        }
        m_outletAssigned = true;

        if (!m_thermalZone) {
          return true;
        }

        OS_ASSERT(m_secondaryNode && m_zoneConnections);
        if (!m_terminalImpl->setPointer(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::SecondaryAirInletNodeName,
                                        m_secondaryNode->handle(), false)) {
          return false;
        }
        m_secondaryAssigned = true;

        const auto originalExhaustNodes = m_zoneConnections->zoneAirExhaustNodes();
        const bool wasExhaustRegistered = std::ranges::find(originalExhaustNodes, *m_secondaryNode) != originalExhaustNodes.end();
        const bool exhaustResult = m_zoneConnections->getImpl<detail::ZoneHVACEquipmentConnections_Impl>()->addZoneAirExhaustNode(*m_secondaryNode);
        const auto currentExhaustNodes = m_zoneConnections->zoneAirExhaustNodes();
        m_exhaustRegistered = !wasExhaustRegistered && (std::ranges::find(currentExhaustNodes, *m_secondaryNode) != currentExhaustNodes.end());
        if (!exhaustResult) {
          return false;
        }

        if (m_airDistributionUnit) {
          if (!m_airDistributionUnit->getImpl<detail::ZoneHVACAirDistributionUnit_Impl>()->setOutletNode(m_outletNode)) {
            return false;
          }
          m_aduUpdated = true;
        }

        const auto originalEquipment = m_thermalZone->equipment();
        const bool wasZoneRegistered = std::ranges::find(originalEquipment, terminal) != originalEquipment.end();
        const bool zoneResult = registerTerminalWithZone(*m_thermalZone, terminal);
        const auto currentEquipment = m_thermalZone->equipment();
        m_zoneRegistered = !wasZoneRegistered && (std::ranges::find(currentEquipment, terminal) != currentEquipment.end());
        return zoneResult;
      }

      void cleanupPreparedState() {
        auto terminal = m_terminalImpl->getObject<ModelObject>();
        if (m_zoneRegistered && m_thermalZone) {
          const bool removed = unregisterTerminalFromZone(*m_thermalZone, terminal);
          OS_ASSERT(removed);
          (void)removed;
        }
        if (m_aduUpdated && m_airDistributionUnit) {
          auto aduImpl = m_airDistributionUnit->getImpl<detail::ZoneHVACAirDistributionUnit_Impl>();
          OS_ASSERT(aduImpl);
          const bool restored =
            m_previousADUOutletTarget ? aduImpl->setPointer(openstudio::ZoneHVAC_AirDistributionUnitFields::AirDistributionUnitOutletNodeName,
                                                            m_previousADUOutletTarget->handle(), false)
            : m_previousADUOutletNodeName
              ? aduImpl->setString(openstudio::ZoneHVAC_AirDistributionUnitFields::AirDistributionUnitOutletNodeName, *m_previousADUOutletNodeName,
                                   false)
              : aduImpl->setPointer(openstudio::ZoneHVAC_AirDistributionUnitFields::AirDistributionUnitOutletNodeName, Handle(), false);
          OS_ASSERT(restored);
          (void)restored;
        }
        if (m_exhaustRegistered && m_zoneConnections && m_secondaryNode) {
          const bool removed = m_zoneConnections->getImpl<detail::ZoneHVACEquipmentConnections_Impl>()->removeZoneAirExhaustNode(*m_secondaryNode);
          OS_ASSERT(removed);
          (void)removed;
        }
        if (m_secondaryAssigned) {
          const bool cleared = m_terminalImpl->setPointer(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::SecondaryAirInletNodeName,
                                                          openstudio::Handle(), false);
          OS_ASSERT(cleared);
          (void)cleared;
        }
        if (m_outletAssigned) {
          const bool cleared = m_terminalImpl->setPointer(m_terminalImpl->outletPort(), openstudio::Handle(), false);
          OS_ASSERT(cleared);
          (void)cleared;
        }
        if (m_inletAssigned) {
          const bool cleared = m_terminalImpl->setPointer(m_terminalImpl->inletPort(), openstudio::Handle(), false);
          OS_ASSERT(cleared);
          (void)cleared;
        }
        if (m_splitterRewired) {
          const bool restored = m_splitter.setOutletModelObject(m_branchIndex, m_outletNode.cast<ModelObject>());
          OS_ASSERT(restored);
          (void)restored;
        }
        if (m_secondaryNodeCreated && m_secondaryNode && m_terminalImpl->model().getObject(m_secondaryNode->handle())) {
          m_secondaryNode->remove();
        }
        if (m_inletNodeCreated && m_terminalImpl->model().getObject(m_inletNode.handle())) {
          m_inletNode.remove();
        }
      }

      State m_state = State::Prepared;
      AirTerminalSingleDuctSeriesPIUReheat_Impl* m_terminalImpl;
      AirLoopHVAC m_airLoop;
      AirLoopHVACZoneSplitter m_splitter;
      unsigned m_branchIndex;
      Node m_outletNode;
      Node m_inletNode;
      bool m_inletNodeCreated;
      boost::optional<ThermalZone> m_thermalZone;
      boost::optional<Node> m_secondaryNode;
      bool m_secondaryNodeCreated;
      boost::optional<ZoneHVACEquipmentConnections> m_zoneConnections;
      boost::optional<ZoneHVACAirDistributionUnit> m_airDistributionUnit;
      boost::optional<ModelObject> m_previousADUOutletTarget;
      boost::optional<std::string> m_previousADUOutletNodeName;
      bool m_splitterRewired = false;
      bool m_inletAssigned = false;
      bool m_outletAssigned = false;
      bool m_secondaryAssigned = false;
      bool m_exhaustRegistered = false;
      bool m_aduUpdated = false;
      bool m_zoneRegistered = false;
    };

    boost::optional<Schedule> AirTerminalSingleDuctSeriesPIUReheat_Impl::availabilitySchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(
        openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::AvailabilityScheduleName);
    }

    bool AirTerminalSingleDuctSeriesPIUReheat_Impl::setAvailabilitySchedule(Schedule& schedule) {
      return ModelObject_Impl::setSchedule(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::AvailabilityScheduleName,
                                           "AirTerminalSingleDuctSeriesPIUReheat", "Availability", schedule);
    }

    void AirTerminalSingleDuctSeriesPIUReheat_Impl::resetAvailabilitySchedule() {
      OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::AvailabilityScheduleName, ""));
    }

    HVACComponent AirTerminalSingleDuctSeriesPIUReheat_Impl::fan() const {
      auto fan = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::FanName);
      OS_ASSERT(fan);
      return *fan;
    }

    bool AirTerminalSingleDuctSeriesPIUReheat_Impl::setFan(const HVACComponent& fanComponent) {
      if ((fanComponent.model() != model()) || !isSupportedSeriesPIUFan(fanComponent)) {
        return false;
      }
      auto mutableFan = fanComponent;
      auto terminal = getObject<ModelObject>();
      auto previousFan = terminal.getModelObjectTarget<HVACComponent>(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::FanName);
      if (previousFan && previousFan->handle() == fanComponent.handle()) {
        return maintainContainedAirPath();
      }
      if (auto owner = fanComponent.containingHVACComponent(); owner && owner->handle() != terminal.handle()) {
        return false;
      }
      const auto type = fanComponent.iddObject().type();
      const auto previousFanControlType = getString(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::FanControlType, false, true);
      auto rollbackFanAssignment = [&]() {
        if (type == IddObjectType::Fan_ConstantVolume) {
          OS_ASSERT(mutableFan.setPointer(openstudio::Fan_ConstantVolumeFields::AirInletNodeName, Handle()));
          OS_ASSERT(mutableFan.setPointer(openstudio::Fan_ConstantVolumeFields::AirOutletNodeName, Handle()));
        } else if (type == IddObjectType::Fan_SystemModel) {
          OS_ASSERT(mutableFan.setPointer(openstudio::Fan_SystemModelFields::AirInletNodeName, Handle()));
          OS_ASSERT(mutableFan.setPointer(openstudio::Fan_SystemModelFields::AirOutletNodeName, Handle()));
        } else if (type == IddObjectType::Fan_OnOff) {
          OS_ASSERT(mutableFan.setPointer(openstudio::Fan_OnOffFields::AirInletNodeName, Handle()));
          OS_ASSERT(mutableFan.setPointer(openstudio::Fan_OnOffFields::AirOutletNodeName, Handle()));
        } else if (type == IddObjectType::Fan_VariableVolume) {
          OS_ASSERT(mutableFan.setPointer(openstudio::Fan_VariableVolumeFields::AirInletNodeName, Handle()));
          OS_ASSERT(mutableFan.setPointer(openstudio::Fan_VariableVolumeFields::AirOutletNodeName, Handle()));
        }
        OS_ASSERT(
          setPointer(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::FanName, previousFan ? previousFan->handle() : Handle(), false));
        OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::FanControlType, previousFanControlType.value_or("")));
        OS_ASSERT(maintainContainedAirPath());
      };
      const bool hasAirPath = (type == IddObjectType::Fan_ConstantVolume
                               && (fanComponent.getTarget(openstudio::Fan_ConstantVolumeFields::AirInletNodeName)
                                   || fanComponent.getTarget(openstudio::Fan_ConstantVolumeFields::AirOutletNodeName)))
                              || (type == IddObjectType::Fan_SystemModel
                                  && (fanComponent.getTarget(openstudio::Fan_SystemModelFields::AirInletNodeName)
                                      || fanComponent.getTarget(openstudio::Fan_SystemModelFields::AirOutletNodeName)))
                              || (type == IddObjectType::Fan_OnOff
                                  && (fanComponent.getTarget(openstudio::Fan_OnOffFields::AirInletNodeName)
                                      || fanComponent.getTarget(openstudio::Fan_OnOffFields::AirOutletNodeName)))
                              || (type == IddObjectType::Fan_VariableVolume
                                  && (fanComponent.getTarget(openstudio::Fan_VariableVolumeFields::AirInletNodeName)
                                      || fanComponent.getTarget(openstudio::Fan_VariableVolumeFields::AirOutletNodeName)));
      if (hasAirPath) {
        return false;
      }
      if (previousFan) {
        const auto previousType = previousFan->iddObject().type();
        if (previousType == IddObjectType::Fan_ConstantVolume) {
          OS_ASSERT(previousFan->setPointer(openstudio::Fan_ConstantVolumeFields::AirInletNodeName, Handle()));
          OS_ASSERT(previousFan->setPointer(openstudio::Fan_ConstantVolumeFields::AirOutletNodeName, Handle()));
        } else if (previousType == IddObjectType::Fan_SystemModel) {
          OS_ASSERT(previousFan->setPointer(openstudio::Fan_SystemModelFields::AirInletNodeName, Handle()));
          OS_ASSERT(previousFan->setPointer(openstudio::Fan_SystemModelFields::AirOutletNodeName, Handle()));
        } else if (previousType == IddObjectType::Fan_OnOff) {
          OS_ASSERT(previousFan->setPointer(openstudio::Fan_OnOffFields::AirInletNodeName, Handle()));
          OS_ASSERT(previousFan->setPointer(openstudio::Fan_OnOffFields::AirOutletNodeName, Handle()));
        } else if (previousType == IddObjectType::Fan_VariableVolume) {
          OS_ASSERT(previousFan->setPointer(openstudio::Fan_VariableVolumeFields::AirInletNodeName, Handle()));
          OS_ASSERT(previousFan->setPointer(openstudio::Fan_VariableVolumeFields::AirOutletNodeName, Handle()));
        }
      }
      if (!setPointer(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::FanName, fanComponent.handle(), false)) {
        rollbackFanAssignment();
        return false;
      }

      if (type == IddObjectType::Fan_ConstantVolume || type == IddObjectType::OS_Fan_ConstantVolume) {
        if (!setFanControlType("ConstantSpeed")) {
          rollbackFanAssignment();
          return false;
        }
      }
      if (!maintainContainedAirPath()) {
        rollbackFanAssignment();
        return false;
      }
      return true;
    }

    HVACComponent AirTerminalSingleDuctSeriesPIUReheat_Impl::reheatCoil() const {
      auto coil =
        getObject<ModelObject>().getModelObjectTarget<HVACComponent>(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::ReheatCoilName);
      OS_ASSERT(coil);
      return *coil;
    }

    bool AirTerminalSingleDuctSeriesPIUReheat_Impl::setReheatCoil(const HVACComponent& coil) {
      if ((coil.model() != model()) || !isSupportedSeriesPIUReheatCoil(coil)) {
        return false;
      }
      auto mutableCoil = coil;
      auto terminal = getObject<ModelObject>();
      auto previousCoil = terminal.getModelObjectTarget<HVACComponent>(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::ReheatCoilName);
      if (previousCoil && previousCoil->handle() == coil.handle()) {
        return maintainContainedAirPath();
      }
      if (auto owner = coil.containingHVACComponent(); owner && owner->handle() != terminal.handle()) {
        return false;
      }
      const auto coilType = coil.iddObject().type();
      const bool hasAirPath = (coilType == IddObjectType::Coil_Heating_Electric
                               && (coil.getTarget(openstudio::Coil_Heating_ElectricFields::AirInletNodeName)
                                   || coil.getTarget(openstudio::Coil_Heating_ElectricFields::AirOutletNodeName)))
                              || (coilType == IddObjectType::Coil_Heating_Fuel
                                  && (coil.getTarget(openstudio::Coil_Heating_FuelFields::AirInletNodeName)
                                      || coil.getTarget(openstudio::Coil_Heating_FuelFields::AirOutletNodeName)))
                              || (coilType == IddObjectType::Coil_Heating_Water
                                  && (coil.getTarget(openstudio::Coil_Heating_WaterFields::AirInletNodeName)
                                      || coil.getTarget(openstudio::Coil_Heating_WaterFields::AirOutletNodeName)));
      if (hasAirPath) {
        return false;
      }
      if (previousCoil) {
        const auto previousType = previousCoil->iddObject().type();
        if (previousType == IddObjectType::Coil_Heating_Electric) {
          OS_ASSERT(previousCoil->setPointer(openstudio::Coil_Heating_ElectricFields::AirInletNodeName, Handle()));
          OS_ASSERT(previousCoil->setPointer(openstudio::Coil_Heating_ElectricFields::AirOutletNodeName, Handle()));
        } else if (previousType == IddObjectType::Coil_Heating_Fuel) {
          OS_ASSERT(previousCoil->setPointer(openstudio::Coil_Heating_FuelFields::AirInletNodeName, Handle()));
          OS_ASSERT(previousCoil->setPointer(openstudio::Coil_Heating_FuelFields::AirOutletNodeName, Handle()));
        } else if (previousType == IddObjectType::Coil_Heating_Water) {
          OS_ASSERT(previousCoil->setPointer(openstudio::Coil_Heating_WaterFields::AirInletNodeName, Handle()));
          OS_ASSERT(previousCoil->setPointer(openstudio::Coil_Heating_WaterFields::AirOutletNodeName, Handle()));
        }
      }
      if (!setPointer(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::ReheatCoilName, coil.handle(), false)) {
        OS_ASSERT(setPointer(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::ReheatCoilName,
                             previousCoil ? previousCoil->handle() : Handle(), false));
        if (previousCoil) {
          OS_ASSERT(maintainContainedAirPath());
        }
        return false;
      }
      if (!maintainContainedAirPath()) {
        if (coilType == IddObjectType::Coil_Heating_Electric) {
          OS_ASSERT(mutableCoil.setPointer(openstudio::Coil_Heating_ElectricFields::AirInletNodeName, Handle()));
          OS_ASSERT(mutableCoil.setPointer(openstudio::Coil_Heating_ElectricFields::AirOutletNodeName, Handle()));
        } else if (coilType == IddObjectType::Coil_Heating_Fuel) {
          OS_ASSERT(mutableCoil.setPointer(openstudio::Coil_Heating_FuelFields::AirInletNodeName, Handle()));
          OS_ASSERT(mutableCoil.setPointer(openstudio::Coil_Heating_FuelFields::AirOutletNodeName, Handle()));
        } else if (coilType == IddObjectType::Coil_Heating_Water) {
          OS_ASSERT(mutableCoil.setPointer(openstudio::Coil_Heating_WaterFields::AirInletNodeName, Handle()));
          OS_ASSERT(mutableCoil.setPointer(openstudio::Coil_Heating_WaterFields::AirOutletNodeName, Handle()));
        }
        OS_ASSERT(setPointer(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::ReheatCoilName,
                             previousCoil ? previousCoil->handle() : Handle(), false));
        OS_ASSERT(maintainContainedAirPath());
        return false;
      }
      return true;
    }

    bool AirTerminalSingleDuctSeriesPIUReheat_Impl::maintainContainedAirPath() {
      return reconcileContainedAirPath(false, nullptr);
    }

    void AirTerminalSingleDuctSeriesPIUReheat_Impl::doCanonicalize(LoadContext& context) {
      if (!repairContainedAirPath(context)) {
        detail::addLoadError(context, "Failed to repair contained air path for AirTerminal:SingleDuct:SeriesPIU:Reheat '"
                                        + getObject<ModelObject>().nameString() + "'.");
      }
    }

    bool AirTerminalSingleDuctSeriesPIUReheat_Impl::repairContainedAirPath(LoadContext& context) {
      return reconcileContainedAirPath(true, &context);
    }

    bool AirTerminalSingleDuctSeriesPIUReheat_Impl::reconcileContainedAirPath(bool allowChildNodeRecovery, LoadContext* context) {
      auto terminal = getObject<ModelObject>();
      auto fanComponent = terminal.getModelObjectTarget<HVACComponent>(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::FanName);
      auto reheatComponent = terminal.getModelObjectTarget<HVACComponent>(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::ReheatCoilName);
      if (fanComponent && context) {
        const bool supported = isSupportedSeriesPIUFan(*fanComponent);
        const auto owner = fanComponent->containingHVACComponent();
        if (!supported || (owner && owner->handle() != terminal.handle())) {
          detail::addLoadWarning(*context, "Dropped " + std::string(supported ? "shared" : "unsupported")
                                             + " fan reference from AirTerminal:SingleDuct:SeriesPIU:Reheat '" + terminal.nameString() + "'.");
          OS_ASSERT(setPointer(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::FanName, Handle(), false));
          fanComponent = boost::none;
        }
      }
      if (reheatComponent && context) {
        const bool supported = isSupportedSeriesPIUReheatCoil(*reheatComponent);
        const auto owner = reheatComponent->containingHVACComponent();
        if (!supported || (owner && owner->handle() != terminal.handle())) {
          detail::addLoadWarning(*context, "Dropped " + std::string(supported ? "shared" : "unsupported")
                                             + " reheat-coil reference from AirTerminal:SingleDuct:SeriesPIU:Reheat '" + terminal.nameString()
                                             + "'.");
          OS_ASSERT(setPointer(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::ReheatCoilName, Handle(), false));
          reheatComponent = boost::none;
        }
      }
      if (!fanComponent || !reheatComponent) {
        if ((fanComponent && !isSupportedSeriesPIUFan(*fanComponent)) || (reheatComponent && !isSupportedSeriesPIUReheatCoil(*reheatComponent))) {
          return false;
        }
        const bool hadExternalTopology =
          static_cast<bool>(inletModelObject()) || static_cast<bool>(outletModelObject())
          || static_cast<bool>(resolvedNodeTarget(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::SecondaryAirInletNodeName))
          || static_cast<bool>(thermalZoneContainingTerminal(model(), terminal)) || static_cast<bool>(zoneHVACAirDistributionUnit());
        if (context && hadExternalTopology) {
          // An incomplete air terminal may still own a valid plant-connected
          // reheat coil. Detach only the invalid air/zone projection here.
          if (reheatComponent) {
            OS_ASSERT(setPointer(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::ReheatCoilName, Handle(), false));
          }
          const bool detached = removeFromLoop();
          if (reheatComponent) {
            OS_ASSERT(setPointer(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::ReheatCoilName, reheatComponent->handle(), false));
          }
          if (!detached) {
            detail::addLoadError(*context, "Could not detach incomplete AirTerminal:SingleDuct:SeriesPIU:Reheat '" + terminal.nameString()
                                             + "' from its external topology.");
            return false;
          }
        }
        bool changed = false;
        std::vector<Node> orphanCandidates;
        const auto clearAirPath = [&](HVACComponent& component) {
          boost::optional<ModelObject> inlet;
          boost::optional<ModelObject> outlet;
          unsigned inletPort = 0u;
          unsigned outletPort = 0u;
          if (auto straight = component.optionalCast<StraightComponent>()) {
            inlet = straight->inletModelObject();
            outlet = straight->outletModelObject();
            inletPort = straight->inletPort();
            outletPort = straight->outletPort();
          } else if (auto waterToAir = component.optionalCast<WaterToAirComponent>()) {
            inlet = waterToAir->airInletModelObject();
            outlet = waterToAir->airOutletModelObject();
            inletPort = waterToAir->airInletPort();
            outletPort = waterToAir->airOutletPort();
          } else {
            return false;
          }
          changed = changed || static_cast<bool>(inlet) || static_cast<bool>(outlet);
          for (const auto& object : {inlet, outlet}) {
            if (object) {
              if (auto node = object->optionalCast<Node>()) {
                orphanCandidates.push_back(*node);
              }
            }
          }
          return component.setPointer(inletPort, Handle()) && component.setPointer(outletPort, Handle());
        };
        if ((fanComponent && !clearAirPath(*fanComponent)) || (reheatComponent && !clearAirPath(*reheatComponent))) {
          return false;
        }
        const auto previousCoilType =
          getString(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::ReheatCoilObjectType, false, true).value_or("");
        const auto expectedCoilType = reheatComponent ? reheatComponent->iddObject().name() : "";
        changed = changed || !openstudio::istringEqual(previousCoilType, expectedCoilType);
        OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::ReheatCoilObjectType, expectedCoilType));
        if (!fanComponent) {
          const auto previousFanName = getString(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::FanName, false, true).value_or("");
          changed = changed || !previousFanName.empty();
          OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::FanName, ""));
        }
        if (!reheatComponent) {
          const auto previousCoilName =
            getString(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::ReheatCoilName, false, true).value_or("");
          changed = changed || !previousCoilName.empty();
          OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::ReheatCoilName, ""));
        }
        if (auto target = terminal.getTarget(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::ZoneMixerName)) {
          changed = true;
          auto oldMixer = target->optionalCast<AirLoopHVACZoneMixer>();
          OS_ASSERT(setPointer(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::ZoneMixerName, Handle(), false));
          if (oldMixer) {
            const bool exclusivelyOwned =
              std::ranges::all_of(oldMixer->sources(), [&terminal](const auto& source) { return source.handle() == terminal.handle(); });
            if (exclusivelyOwned) {
              oldMixer->remove();
            }
          }
        }
        for (auto& node : orphanCandidates) {
          if (node.sources().empty() && model().getObject(node.handle())) {
            node.remove();
          }
        }
        OS_ASSERT(setPointer(inletPort(), Handle(), false));
        OS_ASSERT(setPointer(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::SecondaryAirInletNodeName, Handle(), false));
        OS_ASSERT(setPointer(outletPort(), Handle(), false));
        if ((changed || hadExternalTopology) && context) {
          detail::addLoadWarning(*context, "Detached incomplete AirTerminal:SingleDuct:SeriesPIU:Reheat '" + terminal.nameString()
                                             + "' and cleared its unresolved child references.");
        }
        return true;
      }
      const auto fanType = fanComponent->iddObject().type();
      const auto coilType = reheatComponent->iddObject().type();
      if (((fanType != IddObjectType::Fan_ConstantVolume) && (fanType != IddObjectType::Fan_SystemModel) && (fanType != IddObjectType::Fan_OnOff)
           && (fanType != IddObjectType::Fan_VariableVolume))
          || ((coilType != IddObjectType::Coil_Heating_Electric) && (coilType != IddObjectType::Coil_Heating_Fuel)
              && (coilType != IddObjectType::Coil_Heating_Water))) {
        return false;
      }
      bool changed = false;
      const auto storedCoilType = terminal.getString(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::ReheatCoilObjectType);
      changed = !storedCoilType || !openstudio::istringEqual(*storedCoilType, reheatComponent->iddObject().name());
      if (!setString(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::ReheatCoilObjectType, reheatComponent->iddObject().name())) {
        return false;
      }

      auto supplyNode = resolvedNodeTarget(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::SupplyAirInletNodeName);
      auto secondaryNode = resolvedNodeTarget(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::SecondaryAirInletNodeName);
      auto outletNode = resolvedNodeTarget(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::OutletNodeName);
      if (!supplyNode || !secondaryNode || !outletNode) {
        boost::optional<Node> mixerOutletNode;
        boost::optional<Node> fanOutletNode;
        if (fanType == IddObjectType::Fan_ConstantVolume) {
          mixerOutletNode = fanComponent->getModelObjectTarget<Node>(openstudio::Fan_ConstantVolumeFields::AirInletNodeName);
          fanOutletNode = fanComponent->getModelObjectTarget<Node>(openstudio::Fan_ConstantVolumeFields::AirOutletNodeName);
          OS_ASSERT(fanComponent->setPointer(openstudio::Fan_ConstantVolumeFields::AirInletNodeName, Handle()));
          OS_ASSERT(fanComponent->setPointer(openstudio::Fan_ConstantVolumeFields::AirOutletNodeName, Handle()));
        } else if (fanType == IddObjectType::Fan_SystemModel) {
          mixerOutletNode = fanComponent->getModelObjectTarget<Node>(openstudio::Fan_SystemModelFields::AirInletNodeName);
          fanOutletNode = fanComponent->getModelObjectTarget<Node>(openstudio::Fan_SystemModelFields::AirOutletNodeName);
          OS_ASSERT(fanComponent->setPointer(openstudio::Fan_SystemModelFields::AirInletNodeName, Handle()));
          OS_ASSERT(fanComponent->setPointer(openstudio::Fan_SystemModelFields::AirOutletNodeName, Handle()));
        } else if (fanType == IddObjectType::Fan_OnOff) {
          mixerOutletNode = fanComponent->getModelObjectTarget<Node>(openstudio::Fan_OnOffFields::AirInletNodeName);
          fanOutletNode = fanComponent->getModelObjectTarget<Node>(openstudio::Fan_OnOffFields::AirOutletNodeName);
          OS_ASSERT(fanComponent->setPointer(openstudio::Fan_OnOffFields::AirInletNodeName, Handle()));
          OS_ASSERT(fanComponent->setPointer(openstudio::Fan_OnOffFields::AirOutletNodeName, Handle()));
        } else {
          mixerOutletNode = fanComponent->getModelObjectTarget<Node>(openstudio::Fan_VariableVolumeFields::AirInletNodeName);
          fanOutletNode = fanComponent->getModelObjectTarget<Node>(openstudio::Fan_VariableVolumeFields::AirOutletNodeName);
          OS_ASSERT(fanComponent->setPointer(openstudio::Fan_VariableVolumeFields::AirInletNodeName, Handle()));
          OS_ASSERT(fanComponent->setPointer(openstudio::Fan_VariableVolumeFields::AirOutletNodeName, Handle()));
        }
        changed = changed || static_cast<bool>(mixerOutletNode) || static_cast<bool>(fanOutletNode);
        if (coilType == IddObjectType::Coil_Heating_Electric) {
          changed = changed || static_cast<bool>(reheatComponent->getTarget(openstudio::Coil_Heating_ElectricFields::AirInletNodeName))
                    || static_cast<bool>(reheatComponent->getTarget(openstudio::Coil_Heating_ElectricFields::AirOutletNodeName));
          OS_ASSERT(reheatComponent->setPointer(openstudio::Coil_Heating_ElectricFields::AirInletNodeName, Handle()));
          OS_ASSERT(reheatComponent->setPointer(openstudio::Coil_Heating_ElectricFields::AirOutletNodeName, Handle()));
        } else if (coilType == IddObjectType::Coil_Heating_Fuel) {
          changed = changed || static_cast<bool>(reheatComponent->getTarget(openstudio::Coil_Heating_FuelFields::AirInletNodeName))
                    || static_cast<bool>(reheatComponent->getTarget(openstudio::Coil_Heating_FuelFields::AirOutletNodeName));
          OS_ASSERT(reheatComponent->setPointer(openstudio::Coil_Heating_FuelFields::AirInletNodeName, Handle()));
          OS_ASSERT(reheatComponent->setPointer(openstudio::Coil_Heating_FuelFields::AirOutletNodeName, Handle()));
        } else {
          changed = changed || static_cast<bool>(reheatComponent->getTarget(openstudio::Coil_Heating_WaterFields::AirInletNodeName))
                    || static_cast<bool>(reheatComponent->getTarget(openstudio::Coil_Heating_WaterFields::AirOutletNodeName));
          OS_ASSERT(reheatComponent->setPointer(openstudio::Coil_Heating_WaterFields::AirInletNodeName, Handle()));
          OS_ASSERT(reheatComponent->setPointer(openstudio::Coil_Heating_WaterFields::AirOutletNodeName, Handle()));
        }
        if (auto target = terminal.getTarget(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::ZoneMixerName)) {
          changed = true;
          if (auto oldMixer = target->optionalCast<AirLoopHVACZoneMixer>()) {
            bool exclusivelyOwned = true;
            for (const auto& source : oldMixer->sources()) {
              if (source.handle() != terminal.handle()) {
                exclusivelyOwned = false;
                break;
              }
            }
            OS_ASSERT(setPointer(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::ZoneMixerName, Handle(), false));
            if (exclusivelyOwned) {
              oldMixer->remove();
            }
          } else {
            OS_ASSERT(setPointer(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::ZoneMixerName, Handle(), false));
          }
        }
        if (mixerOutletNode && mixerOutletNode->sources().empty()) {
          mixerOutletNode->remove();
        }
        if (fanOutletNode && fanOutletNode->sources().empty()) {
          fanOutletNode->remove();
        }
        if (changed && context) {
          detail::addLoadInfo(*context, "Reconciled contained air path for AirTerminal:SingleDuct:SeriesPIU:Reheat '" + terminal.nameString() + "'.");
        }
        return true;
      }
      if (!terminal.name() && !terminal.createName()) {
        return false;
      }
      const auto baseName = terminal.nameString();

      boost::optional<AirLoopHVACZoneMixer> mixer;
      if (auto target = terminal.getTarget(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::ZoneMixerName)) {
        mixer = target->optionalCast<AirLoopHVACZoneMixer>();
      }
      if (mixer) {
        for (const auto& source : mixer->sources()) {
          if (source.handle() != terminal.handle()) {
            mixer = boost::none;
            changed = true;
            break;
          }
        }
      }

      std::vector<Node> displacedNodeCandidates;
      if (fanType == IddObjectType::Fan_ConstantVolume) {
        if (auto node = fanComponent->getModelObjectTarget<Node>(openstudio::Fan_ConstantVolumeFields::AirInletNodeName)) {
          displacedNodeCandidates.push_back(*node);
        }
        if (auto node = fanComponent->getModelObjectTarget<Node>(openstudio::Fan_ConstantVolumeFields::AirOutletNodeName)) {
          displacedNodeCandidates.push_back(*node);
        }
      } else if (fanType == IddObjectType::Fan_SystemModel) {
        if (auto node = fanComponent->getModelObjectTarget<Node>(openstudio::Fan_SystemModelFields::AirInletNodeName)) {
          displacedNodeCandidates.push_back(*node);
        }
        if (auto node = fanComponent->getModelObjectTarget<Node>(openstudio::Fan_SystemModelFields::AirOutletNodeName)) {
          displacedNodeCandidates.push_back(*node);
        }
      } else if (fanType == IddObjectType::Fan_OnOff) {
        if (auto node = fanComponent->getModelObjectTarget<Node>(openstudio::Fan_OnOffFields::AirInletNodeName)) {
          displacedNodeCandidates.push_back(*node);
        }
        if (auto node = fanComponent->getModelObjectTarget<Node>(openstudio::Fan_OnOffFields::AirOutletNodeName)) {
          displacedNodeCandidates.push_back(*node);
        }
      } else {
        if (auto node = fanComponent->getModelObjectTarget<Node>(openstudio::Fan_VariableVolumeFields::AirInletNodeName)) {
          displacedNodeCandidates.push_back(*node);
        }
        if (auto node = fanComponent->getModelObjectTarget<Node>(openstudio::Fan_VariableVolumeFields::AirOutletNodeName)) {
          displacedNodeCandidates.push_back(*node);
        }
      }
      if (coilType == IddObjectType::Coil_Heating_Electric) {
        if (auto node = reheatComponent->getModelObjectTarget<Node>(openstudio::Coil_Heating_ElectricFields::AirInletNodeName)) {
          displacedNodeCandidates.push_back(*node);
        }
        if (auto node = reheatComponent->getModelObjectTarget<Node>(openstudio::Coil_Heating_ElectricFields::AirOutletNodeName)) {
          displacedNodeCandidates.push_back(*node);
        }
      } else if (coilType == IddObjectType::Coil_Heating_Fuel) {
        if (auto node = reheatComponent->getModelObjectTarget<Node>(openstudio::Coil_Heating_FuelFields::AirInletNodeName)) {
          displacedNodeCandidates.push_back(*node);
        }
        if (auto node = reheatComponent->getModelObjectTarget<Node>(openstudio::Coil_Heating_FuelFields::AirOutletNodeName)) {
          displacedNodeCandidates.push_back(*node);
        }
      } else {
        if (auto node = reheatComponent->getModelObjectTarget<Node>(openstudio::Coil_Heating_WaterFields::AirInletNodeName)) {
          displacedNodeCandidates.push_back(*node);
        }
        if (auto node = reheatComponent->getModelObjectTarget<Node>(openstudio::Coil_Heating_WaterFields::AirOutletNodeName)) {
          displacedNodeCandidates.push_back(*node);
        }
      }
      if (mixer) {
        if (auto node = mixer->getModelObjectTarget<Node>(mixer->outletPort())) {
          displacedNodeCandidates.push_back(*node);
        }
        for (const auto& inlet : mixer->inletModelObjects()) {
          if (auto node = inlet.optionalCast<Node>()) {
            displacedNodeCandidates.push_back(*node);
          }
        }
      }

      boost::optional<Node> mixerOutletNode;
      boost::optional<Node> fanOutletNode;
      if (allowChildNodeRecovery && mixer) {
        const auto currentMixerOutlet = mixer->getModelObjectTarget<Node>(mixer->outletPort());
        const auto currentFanInlet =
          fanType == IddObjectType::Fan_ConstantVolume
            ? fanComponent->getModelObjectTarget<Node>(openstudio::Fan_ConstantVolumeFields::AirInletNodeName)
          : fanType == IddObjectType::Fan_SystemModel ? fanComponent->getModelObjectTarget<Node>(openstudio::Fan_SystemModelFields::AirInletNodeName)
          : fanType == IddObjectType::Fan_OnOff       ? fanComponent->getModelObjectTarget<Node>(openstudio::Fan_OnOffFields::AirInletNodeName)
                                                : fanComponent->getModelObjectTarget<Node>(openstudio::Fan_VariableVolumeFields::AirInletNodeName);
        if (currentMixerOutlet && currentFanInlet && *currentMixerOutlet == *currentFanInlet && *currentMixerOutlet != *supplyNode
            && *currentMixerOutlet != *secondaryNode && *currentMixerOutlet != *outletNode) {
          mixerOutletNode = currentMixerOutlet;
        }
        const auto currentFanOutlet =
          fanType == IddObjectType::Fan_ConstantVolume
            ? fanComponent->getModelObjectTarget<Node>(openstudio::Fan_ConstantVolumeFields::AirOutletNodeName)
          : fanType == IddObjectType::Fan_SystemModel ? fanComponent->getModelObjectTarget<Node>(openstudio::Fan_SystemModelFields::AirOutletNodeName)
          : fanType == IddObjectType::Fan_OnOff       ? fanComponent->getModelObjectTarget<Node>(openstudio::Fan_OnOffFields::AirOutletNodeName)
                                                : fanComponent->getModelObjectTarget<Node>(openstudio::Fan_VariableVolumeFields::AirOutletNodeName);
        const auto currentCoilInlet = coilType == IddObjectType::Coil_Heating_Electric
                                        ? reheatComponent->getModelObjectTarget<Node>(openstudio::Coil_Heating_ElectricFields::AirInletNodeName)
                                      : coilType == IddObjectType::Coil_Heating_Fuel
                                        ? reheatComponent->getModelObjectTarget<Node>(openstudio::Coil_Heating_FuelFields::AirInletNodeName)
                                        : reheatComponent->getModelObjectTarget<Node>(openstudio::Coil_Heating_WaterFields::AirInletNodeName);
        if (currentFanOutlet && currentCoilInlet && *currentFanOutlet == *currentCoilInlet && *currentFanOutlet != *supplyNode
            && *currentFanOutlet != *secondaryNode && *currentFanOutlet != *outletNode) {
          fanOutletNode = currentFanOutlet;
        }
      }
      if (!mixerOutletNode) {
        mixerOutletNode = model().getOrCreateTransientByName<Node>(baseName + " Mixer Outlet");
      }
      if (!fanOutletNode) {
        fanOutletNode = model().getOrCreateTransientByName<Node>(baseName + " Fan Outlet");
      }
      if (!mixer) {
        mixer = AirLoopHVACZoneMixer(model());
        changed = true;
        if (!mixer->setName(baseName + " Mixer")
            || !setPointer(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::ZoneMixerName, mixer->handle(), false)) {
          return false;
        }
      }
      auto mixerImpl = mixer->getImpl<detail::AirLoopHVACZoneMixer_Impl>();
      OS_ASSERT(mixerImpl);
      const auto previousMixerInlets = mixer->inletModelObjects();
      const auto previousMixerOutlet = mixer->getModelObjectTarget<Node>(mixer->outletPort());
      changed = changed || !previousMixerOutlet || *previousMixerOutlet != *mixerOutletNode || previousMixerInlets.size() != 2u
                || previousMixerInlets[0] != secondaryNode->cast<ModelObject>() || previousMixerInlets[1] != supplyNode->cast<ModelObject>();
      if (!mixerImpl->setOutletNode(*mixerOutletNode) || !mixer->setInletModelObject(0u, secondaryNode->cast<ModelObject>())
          || !mixer->setInletModelObject(1u, supplyNode->cast<ModelObject>())) {
        return false;
      }
      while (mixer->inletModelObjects().size() > 2u) {
        auto displacedNode = mixer->inletModelObjects().back().optionalCast<Node>();
        mixer->removePortForBranch(static_cast<unsigned>(mixer->inletModelObjects().size() - 1u));
        if (displacedNode && displacedNode->sources().empty() && model().getObject(displacedNode->handle())) {
          displacedNode->remove();
        }
      }

      bool fanResult = false;
      if (fanType == IddObjectType::Fan_ConstantVolume) {
        changed = changed || fanComponent->getModelObjectTarget<Node>(openstudio::Fan_ConstantVolumeFields::AirInletNodeName) != mixerOutletNode
                  || fanComponent->getModelObjectTarget<Node>(openstudio::Fan_ConstantVolumeFields::AirOutletNodeName) != fanOutletNode;
        fanResult = fanComponent->setPointer(openstudio::Fan_ConstantVolumeFields::AirInletNodeName, mixerOutletNode->handle())
                    && fanComponent->setPointer(openstudio::Fan_ConstantVolumeFields::AirOutletNodeName, fanOutletNode->handle());
      } else if (fanType == IddObjectType::Fan_SystemModel) {
        changed = changed || fanComponent->getModelObjectTarget<Node>(openstudio::Fan_SystemModelFields::AirInletNodeName) != mixerOutletNode
                  || fanComponent->getModelObjectTarget<Node>(openstudio::Fan_SystemModelFields::AirOutletNodeName) != fanOutletNode;
        fanResult = fanComponent->setPointer(openstudio::Fan_SystemModelFields::AirInletNodeName, mixerOutletNode->handle())
                    && fanComponent->setPointer(openstudio::Fan_SystemModelFields::AirOutletNodeName, fanOutletNode->handle());
      } else if (fanType == IddObjectType::Fan_OnOff) {
        changed = changed || fanComponent->getModelObjectTarget<Node>(openstudio::Fan_OnOffFields::AirInletNodeName) != mixerOutletNode
                  || fanComponent->getModelObjectTarget<Node>(openstudio::Fan_OnOffFields::AirOutletNodeName) != fanOutletNode;
        fanResult = fanComponent->setPointer(openstudio::Fan_OnOffFields::AirInletNodeName, mixerOutletNode->handle())
                    && fanComponent->setPointer(openstudio::Fan_OnOffFields::AirOutletNodeName, fanOutletNode->handle());
      } else {
        changed = changed || fanComponent->getModelObjectTarget<Node>(openstudio::Fan_VariableVolumeFields::AirInletNodeName) != mixerOutletNode
                  || fanComponent->getModelObjectTarget<Node>(openstudio::Fan_VariableVolumeFields::AirOutletNodeName) != fanOutletNode;
        fanResult = fanComponent->setPointer(openstudio::Fan_VariableVolumeFields::AirInletNodeName, mixerOutletNode->handle())
                    && fanComponent->setPointer(openstudio::Fan_VariableVolumeFields::AirOutletNodeName, fanOutletNode->handle());
      }
      if (!fanResult) {
        return false;
      }

      bool result = false;
      if (coilType == IddObjectType::Coil_Heating_Electric) {
        changed = changed || reheatComponent->getModelObjectTarget<Node>(openstudio::Coil_Heating_ElectricFields::AirInletNodeName) != fanOutletNode
                  || reheatComponent->getModelObjectTarget<Node>(openstudio::Coil_Heating_ElectricFields::AirOutletNodeName) != outletNode;
        result = reheatComponent->setPointer(openstudio::Coil_Heating_ElectricFields::AirInletNodeName, fanOutletNode->handle())
                 && reheatComponent->setPointer(openstudio::Coil_Heating_ElectricFields::AirOutletNodeName, outletNode->handle());
      } else if (coilType == IddObjectType::Coil_Heating_Fuel) {
        changed = changed || reheatComponent->getModelObjectTarget<Node>(openstudio::Coil_Heating_FuelFields::AirInletNodeName) != fanOutletNode
                  || reheatComponent->getModelObjectTarget<Node>(openstudio::Coil_Heating_FuelFields::AirOutletNodeName) != outletNode;
        result = reheatComponent->setPointer(openstudio::Coil_Heating_FuelFields::AirInletNodeName, fanOutletNode->handle())
                 && reheatComponent->setPointer(openstudio::Coil_Heating_FuelFields::AirOutletNodeName, outletNode->handle());
      } else {
        changed = changed || reheatComponent->getModelObjectTarget<Node>(openstudio::Coil_Heating_WaterFields::AirInletNodeName) != fanOutletNode
                  || reheatComponent->getModelObjectTarget<Node>(openstudio::Coil_Heating_WaterFields::AirOutletNodeName) != outletNode;
        result = reheatComponent->setPointer(openstudio::Coil_Heating_WaterFields::AirInletNodeName, fanOutletNode->handle())
                 && reheatComponent->setPointer(openstudio::Coil_Heating_WaterFields::AirOutletNodeName, outletNode->handle());
      }
      if (result) {
        for (auto& displacedNode : displacedNodeCandidates) {
          if (displacedNode == *supplyNode || displacedNode == *secondaryNode || displacedNode == *outletNode || displacedNode == *mixerOutletNode
              || displacedNode == *fanOutletNode) {
            continue;
          }
          if (model().getObject(displacedNode.handle()) && displacedNode.sources().empty()) {
            displacedNode.remove();
          }
        }
      }
      if (result && changed && context) {
        detail::addLoadInfo(*context, "Reconciled contained air path for AirTerminal:SingleDuct:SeriesPIU:Reheat '" + terminal.nameString() + "'.");
      }
      return result;
    }

    boost::optional<Node> AirTerminalSingleDuctSeriesPIUReheat_Impl::secondaryAirInletNode() const {
      return getObject<ModelObject>().getModelObjectTarget<Node>(
        openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::SecondaryAirInletNodeName);
    }

    boost::optional<double> AirTerminalSingleDuctSeriesPIUReheat_Impl::maximumAirFlowRate() const {
      return getDouble(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::MaximumAirFlowRate, true);
    }

    bool AirTerminalSingleDuctSeriesPIUReheat_Impl::isMaximumAirFlowRateAutosized() const {
      if (auto value = getString(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::MaximumAirFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool AirTerminalSingleDuctSeriesPIUReheat_Impl::setMaximumAirFlowRate(double maximumAirFlowRate) {
      const bool result = setDouble(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::MaximumAirFlowRate, maximumAirFlowRate);
      OS_ASSERT(result);
      return result;
    }

    void AirTerminalSingleDuctSeriesPIUReheat_Impl::autosizeMaximumAirFlowRate() {
      const bool result = setString(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::MaximumAirFlowRate, "autosize");
      OS_ASSERT(result);
    }

    boost::optional<double> AirTerminalSingleDuctSeriesPIUReheat_Impl::maximumPrimaryAirFlowRate() const {
      return getDouble(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::MaximumPrimaryAirFlowRate, true);
    }

    bool AirTerminalSingleDuctSeriesPIUReheat_Impl::isMaximumPrimaryAirFlowRateAutosized() const {
      if (auto value = getString(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::MaximumPrimaryAirFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool AirTerminalSingleDuctSeriesPIUReheat_Impl::setMaximumPrimaryAirFlowRate(double maximumPrimaryAirFlowRate) {
      const bool result = setDouble(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::MaximumPrimaryAirFlowRate, maximumPrimaryAirFlowRate);
      OS_ASSERT(result);
      return result;
    }

    void AirTerminalSingleDuctSeriesPIUReheat_Impl::autosizeMaximumPrimaryAirFlowRate() {
      const bool result = setString(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::MaximumPrimaryAirFlowRate, "autosize");
      OS_ASSERT(result);
    }

    boost::optional<double> AirTerminalSingleDuctSeriesPIUReheat_Impl::minimumPrimaryAirFlowFraction() const {
      return getDouble(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::MinimumPrimaryAirFlowFraction, true);
    }

    bool AirTerminalSingleDuctSeriesPIUReheat_Impl::isMinimumPrimaryAirFlowFractionAutosized() const {
      if (auto value = getString(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::MinimumPrimaryAirFlowFraction, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool AirTerminalSingleDuctSeriesPIUReheat_Impl::setMinimumPrimaryAirFlowFraction(double minimumPrimaryAirFlowFraction) {
      const bool result =
        setDouble(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::MinimumPrimaryAirFlowFraction, minimumPrimaryAirFlowFraction);
      OS_ASSERT(result);
      return result;
    }

    void AirTerminalSingleDuctSeriesPIUReheat_Impl::autosizeMinimumPrimaryAirFlowFraction() {
      const bool result = setString(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::MinimumPrimaryAirFlowFraction, "autosize");
      OS_ASSERT(result);
    }

    boost::optional<double> AirTerminalSingleDuctSeriesPIUReheat_Impl::maximumHotWaterorSteamFlowRate() const {
      return getDouble(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::MaximumHotWaterorSteamFlowRate, true);
    }

    bool AirTerminalSingleDuctSeriesPIUReheat_Impl::isMaximumHotWaterorSteamFlowRateAutosized() const {
      if (auto value = getString(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::MaximumHotWaterorSteamFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool AirTerminalSingleDuctSeriesPIUReheat_Impl::setMaximumHotWaterorSteamFlowRate(double maximumHotWaterorSteamFlowRate) {
      const bool result =
        setDouble(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::MaximumHotWaterorSteamFlowRate, maximumHotWaterorSteamFlowRate);
      OS_ASSERT(result);
      return result;
    }

    void AirTerminalSingleDuctSeriesPIUReheat_Impl::resetMaximumHotWaterorSteamFlowRate() {
      OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::MaximumHotWaterorSteamFlowRate, ""));
    }

    void AirTerminalSingleDuctSeriesPIUReheat_Impl::autosizeMaximumHotWaterorSteamFlowRate() {
      OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::MaximumHotWaterorSteamFlowRate, "autosize"));
    }

    double AirTerminalSingleDuctSeriesPIUReheat_Impl::minimumHotWaterorSteamFlowRate() const {
      const auto value = getDouble(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::MinimumHotWaterorSteamFlowRate, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirTerminalSingleDuctSeriesPIUReheat_Impl::setMinimumHotWaterorSteamFlowRate(double minimumHotWaterorSteamFlowRate) {
      return setDouble(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::MinimumHotWaterorSteamFlowRate, minimumHotWaterorSteamFlowRate);
    }

    double AirTerminalSingleDuctSeriesPIUReheat_Impl::convergenceTolerance() const {
      const auto value = getDouble(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::ConvergenceTolerance, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirTerminalSingleDuctSeriesPIUReheat_Impl::setConvergenceTolerance(double convergenceTolerance) {
      return setDouble(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::ConvergenceTolerance, convergenceTolerance);
    }

    std::string AirTerminalSingleDuctSeriesPIUReheat_Impl::fanControlType() const {
      const auto value = getString(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::FanControlType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirTerminalSingleDuctSeriesPIUReheat_Impl::setFanControlType(const std::string& fanControlType) {
      auto fanComponent =
        getObject<ModelObject>().getModelObjectTarget<HVACComponent>(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::FanName);
      if (fanComponent
          && ((fanComponent->iddObject().type() == IddObjectType::Fan_ConstantVolume)
              || (fanComponent->iddObject().type() == IddObjectType::OS_Fan_ConstantVolume))
          && istringEqual(fanControlType, "VariableSpeed")) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctSeriesPIUReheat",
                 "Rejecting VariableSpeed fan control for a constant-volume fan on " << briefDescription() << ".");
        return false;
      }

      return setString(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::FanControlType, fanControlType);
    }

    double AirTerminalSingleDuctSeriesPIUReheat_Impl::minimumFanTurnDownRatio() const {
      const auto value = getDouble(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::MinimumFanTurnDownRatio, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirTerminalSingleDuctSeriesPIUReheat_Impl::setMinimumFanTurnDownRatio(double minimumFanTurnDownRatio) {
      return setDouble(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::MinimumFanTurnDownRatio, minimumFanTurnDownRatio);
    }

    std::string AirTerminalSingleDuctSeriesPIUReheat_Impl::heatingControlType() const {
      const auto value = getString(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::HeatingControlType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirTerminalSingleDuctSeriesPIUReheat_Impl::setHeatingControlType(const std::string& heatingControlType) {
      return setString(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::HeatingControlType, heatingControlType);
    }

    double AirTerminalSingleDuctSeriesPIUReheat_Impl::designHeatingDischargeAirTemperature() const {
      const auto value = getDouble(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::DesignHeatingDischargeAirTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirTerminalSingleDuctSeriesPIUReheat_Impl::setDesignHeatingDischargeAirTemperature(double designHeatingDischargeAirTemperature) {
      return setDouble(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::DesignHeatingDischargeAirTemperature,
                       designHeatingDischargeAirTemperature);
    }

    double AirTerminalSingleDuctSeriesPIUReheat_Impl::highLimitHeatingDischargeAirTemperature() const {
      const auto value = getDouble(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::HighLimitHeatingDischargeAirTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirTerminalSingleDuctSeriesPIUReheat_Impl::setHighLimitHeatingDischargeAirTemperature(double highLimitHeatingDischargeAirTemperature) {
      return setDouble(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::HighLimitHeatingDischargeAirTemperature,
                       highLimitHeatingDischargeAirTemperature);
    }

    std::vector<std::string> AirTerminalSingleDuctSeriesPIUReheat_Impl::fanControlTypeValues() const {
      return openstudio::epmodel::AirTerminalSingleDuctSeriesPIUReheat::fanControlTypeValues();
    }

    std::vector<std::string> AirTerminalSingleDuctSeriesPIUReheat_Impl::heatingControlTypeValues() const {
      return openstudio::epmodel::AirTerminalSingleDuctSeriesPIUReheat::heatingControlTypeValues();
    }

    unsigned AirTerminalSingleDuctSeriesPIUReheat_Impl::inletPort() const {
      return openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::SupplyAirInletNodeName;
    }

    unsigned AirTerminalSingleDuctSeriesPIUReheat_Impl::outletPort() const {
      return openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::OutletNodeName;
    }

    std::vector<ModelObject> AirTerminalSingleDuctSeriesPIUReheat_Impl::children() const {
      std::vector<ModelObject> result;
      if (auto reheat =
            getObject<ModelObject>().getModelObjectTarget<HVACComponent>(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::ReheatCoilName)) {
        result.push_back(*reheat);
      }
      if (auto fanComponent =
            getObject<ModelObject>().getModelObjectTarget<HVACComponent>(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::FanName)) {
        result.push_back(*fanComponent);
      }
      return result;
    }

    bool AirTerminalSingleDuctSeriesPIUReheat_Impl::isRemovable() const {
      if (!HVACComponent_Impl::isRemovable()) {
        return false;
      }
      const auto reheat =
        getObject<ModelObject>().getModelObjectTarget<HVACComponent>(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::ReheatCoilName);
      return demandBranchRemovalPlan(reheat).valid;
    }

    boost::optional<ZoneHVACAirDistributionUnit> AirTerminalSingleDuctSeriesPIUReheat_Impl::zoneHVACAirDistributionUnit() const {
      auto terminal = getObject<ModelObject>();
      for (const auto& source : terminal.getSources(openstudio::IddObjectType::ZoneHVAC_AirDistributionUnit)) {
        if (auto adu = source.optionalCast<openstudio::epmodel::ZoneHVACAirDistributionUnit>()) {
          return adu;
        }
      }
      return boost::none;
    }

    std::vector<openstudio::IdfObject> AirTerminalSingleDuctSeriesPIUReheat_Impl::remove() {
      auto thisObject = getObject<openstudio::epmodel::ModelObject>();
      auto thisModel = model();
      const auto thisHandle = thisObject.handle();
      const auto ownedChildren = children();

      if (!removeFromLoop()) {
        // A clean disconnected object (including an object being cleaned up by
        // a failed constructor) has no loop work to report. Only reject full
        // removal when topology or ownership references still remain.
        const auto reheat = thisObject.getModelObjectTarget<openstudio::epmodel::HVACComponent>(
          openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::ReheatCoilName);
        if (inletModelObject() || outletModelObject() || secondaryAirInletNode() || thermalZoneContainingTerminal(thisModel, thisObject)
            || zoneHVACAirDistributionUnit() || (reheat && reheat->plantLoop())) {
          return {};
        }
      }
      if (!maintainContainedAirPath()) {
        return {};
      }

      auto result = HVACComponent_Impl::remove();
      if (result.empty() || thisModel.getObject(thisHandle)) {
        return {};
      }

      // epmodel's generic ParentObject removal does not yet cascade children.
      // Match model ownership here, but only after topology teardown and the
      // parent removal have both succeeded.
      for (auto child : ownedChildren) {
        if (thisModel.getObject(child.handle())) {
          auto removedChildObjects = child.remove();
          result.insert(result.end(), removedChildObjects.begin(), removedChildObjects.end());
        }
      }
      return result;
    }

    bool AirTerminalSingleDuctSeriesPIUReheat_Impl::removeFromLoop() {
      auto thisObject = getObject<openstudio::epmodel::ModelObject>();
      auto inletNode = inletModelObject();
      auto outletNode = outletModelObject();
      auto thermalZone = thermalZoneContainingTerminal(model(), thisObject);
      if (!thermalZone && outletNode) {
        if (auto outletZoneNode = outletNode->optionalCast<Node>()) {
          thermalZone = owningThermalZoneForZoneNode(model(), *outletZoneNode);
        }
      }
      auto reheat = thisObject.getModelObjectTarget<openstudio::epmodel::HVACComponent>(
        openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::ReheatCoilName);
      auto plantRemovalPlan = demandBranchRemovalPlan(reheat);
      if (!plantRemovalPlan.valid) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctSeriesPIUReheat",
                 "Refusing to remove a terminal whose reheat coil does not belong to exactly one demand-equipment branch.");
        return false;
      }
      auto secondaryNode = secondaryAirInletNode();
      if (!thermalZone && secondaryNode) {
        thermalZone = thermalZoneContainingExhaustNode(model(), *secondaryNode);
      }

      bool shouldRemoveTerminalInletNode = inletNode && outletNode && isDemandBranchStartComponent();
      if (!shouldRemoveTerminalInletNode && inletNode) {
        if (auto terminalInletNode = inletNode->optionalCast<openstudio::epmodel::Node>()) {
          // Preserve direct-branch recovery when this terminal's outlet is stale.
          // The effective topology resolver deliberately rejects an inconsistent
          // graph, but the splitter outlet still identifies this legacy repair case.
          if (auto airLoop = terminalInletNode->airLoopHVAC()) {
            const auto splitter = airLoop->zoneSplitter();
            const auto splitterOutlets = splitter.outletModelObjects();
            const auto splitterIt = std::ranges::find(splitterOutlets, *inletNode);
            if (splitterIt != splitterOutlets.end()) {
              const auto mixerInlets = airLoop->zoneMixer().inletModelObjects();
              shouldRemoveTerminalInletNode = std::ranges::any_of(mixerInlets, [&](const auto& mixerInlet) {
                return isServedZoneReturnNode(thermalZone, mixerInlet) || (!thermalZone && outletNode && (mixerInlet == *outletNode));
              });
            }
          }
        }
      }

      boost::optional<Handle> originalOutletHandle;
      bool repairedZoneOutlet = false;
      if (thermalZone && inletNode && shouldRemoveTerminalInletNode) {
        boost::optional<Node> canonicalZoneOutlet;
        auto zoneImpl = thermalZone->getImpl<detail::ThermalZone_Impl>();
        OS_ASSERT(zoneImpl);
        if (auto connections = zoneImpl->zoneHVACEquipmentConnections()) {
          const auto zoneInletNodes = connections->zoneAirInletNodes();

          // An ADU outlet is the strongest surviving association after a terminal's own
          // outlet field has gone stale.
          if (auto adu = zoneHVACAirDistributionUnit()) {
            if (auto aduOutlet = adu->outletNode(); std::ranges::find(zoneInletNodes, *aduOutlet) != zoneInletNodes.end()) {
              canonicalZoneOutlet = *aduOutlet;
            }
          }

          // Otherwise match the inlet node name created by addToNode to the zone inlet
          // that originally occupied this splitter branch.
          if (!canonicalZoneOutlet) {
            for (const auto& candidate : zoneInletNodes) {
              const auto expectedTerminalInletName = candidate.nameString() + " - " + thisObject.nameString() + " Inlet Node";
              if (inletNode->nameString() == expectedTerminalInletName) {
                canonicalZoneOutlet = candidate;
                break;
              }
            }
          }

          if (!canonicalZoneOutlet && zoneInletNodes.size() == 1u) {
            canonicalZoneOutlet = zoneInletNodes.front();
          }
        }

        if (!canonicalZoneOutlet) {
          return false;
        }

        if (!outletNode || (*outletNode != canonicalZoneOutlet->cast<ModelObject>())) {
          if (outletNode) {
            originalOutletHandle = outletNode->handle();
          }
          if (!setPointer(outletPort(), canonicalZoneOutlet->handle(), false)) {
            return false;
          }
          outletNode = canonicalZoneOutlet->cast<ModelObject>();
          repairedZoneOutlet = true;
        }
      }

      bool removedFromAirLoop = false;
      if (inletNode && outletNode) {
        if (!StraightComponent_Impl::removeFromLoop()) {
          if (repairedZoneOutlet) {
            (void)setPointer(outletPort(), originalOutletHandle ? *originalOutletHandle : Handle(), false);
          }
          return false;
        }
        removedFromAirLoop = true;
      }

      if (thermalZone) {
        // Stale-registration recovery is intentionally idempotent: the zone may already have dropped the terminal while its branch and
        // secondary-air node still need cleanup.
        (void)unregisterTerminalFromZone(*thermalZone, thisObject);
      }

      bool removedSecondaryNode = false;
      if (secondaryNode) {
        auto zoneImpl = thermalZone ? thermalZone->getImpl<detail::ThermalZone_Impl>() : nullptr;
        if (zoneImpl) {
          auto zoneConnections = zoneImpl->getZoneHVACEquipmentConnections();
          if (!zoneConnections.getImpl<detail::ZoneHVACEquipmentConnections_Impl>()->removeZoneAirExhaustNode(*secondaryNode)) {
            return false;
          }
        }

        if (!setPointer(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::SecondaryAirInletNodeName, openstudio::Handle(), false)) {
          return false;
        }

        const auto secondaryNodeHandle = secondaryNode->handle();
        secondaryNode->remove();
        removedSecondaryNode = !model().getObject(secondaryNodeHandle);
        if (!removedSecondaryNode) {
          return false;
        }
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

      if (!setPointer(inletPort(), openstudio::Handle(), false)) {
        return false;
      }
      if (!setPointer(outletPort(), openstudio::Handle(), false)) {
        return false;
      }

      if (shouldRemoveTerminalInletNode) {
        if (auto node = inletNode->optionalCast<openstudio::epmodel::Node>()) {
          node->remove();
        }
      }

      bool removedFromPlantLoop = false;
      if (plantRemovalPlan.plantLoop && reheat) {
        if (!plantRemovalPlan.plantLoop->removeDemandBranchWithComponent(*reheat)) {
          return false;
        }
        removedFromPlantLoop = true;
      }

      if (!maintainContainedAirPath()) {
        return false;
      }

      return removedFromAirLoop || static_cast<bool>(thermalZone) || removedSecondaryNode || cleanedADU || removedFromPlantLoop;
    }

    bool AirTerminalSingleDuctSeriesPIUReheat_Impl::addToNode(Node& node) {
      return addToNode(node, AddToNodeFailureStage::None);
    }

    bool AirTerminalSingleDuctSeriesPIUReheat_Impl::addToNode(Node& node, AddToNodeFailureStage failureStage) {
      if (node.model() != model()) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctSeriesPIUReheat",
                 "addToNode requires a node in the same model as the series PIU terminal.");
        return false;
      }

      if (getObject<openstudio::epmodel::HVACComponent>().loop() || inletModelObject() || outletModelObject() || secondaryAirInletNode()) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctSeriesPIUReheat",
                 "Refusing to add an already-connected series PIU terminal to node '" << node.nameString() << "'.");
        return false;
      }

      auto airLoop = node.airLoopHVAC();
      if (!airLoop) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctSeriesPIUReheat",
                 "addToNode requires a node that resolves to an AirLoopHVAC context.");
        return false;
      }

      auto zoneSplitter = airLoop->zoneSplitter();
      const auto thisNode = node.cast<ModelObject>();
      const auto splitterOutlets = zoneSplitter.outletModelObjects();
      const auto splitterIt = std::find(splitterOutlets.begin(), splitterOutlets.end(), thisNode);
      if (splitterIt == splitterOutlets.end()) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctSeriesPIUReheat",
                 "addToNode requires the drop node to be a ZoneSplitter outlet node for the target AirLoopHVAC.");
        return false;
      }
      const auto splitterBranchIndex = static_cast<unsigned>(std::distance(splitterOutlets.begin(), splitterIt));

      auto airLoopImpl = airLoop->getImpl<detail::AirLoopHVAC_Impl>();
      OS_ASSERT(airLoopImpl);
      auto mixerInlet = airLoopImpl->effectiveDemandReturnNodeForBranchStart(node);
      if (!mixerInlet) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctSeriesPIUReheat",
                 "addToNode requires one effective ZoneMixer return for the selected ZoneSplitter branch.");
        return false;
      }
      auto thermalZone = owningThermalZoneForZoneNode(model(), node);
      if ((*mixerInlet != thisNode) && !isServedZoneReturnNode(thermalZone, *mixerInlet)) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctSeriesPIUReheat",
                 "addToNode requires the drop node to either feed the ZoneMixer directly or be the served zone inlet node.");
        return false;
      }

      auto thisObject = getObject<ModelObject>();
      const auto fanComponent = thisObject.getModelObjectTarget<HVACComponent>(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::FanName);
      const auto reheatComponent =
        thisObject.getModelObjectTarget<HVACComponent>(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::ReheatCoilName);
      if (!fanComponent || !reheatComponent) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctSeriesPIUReheat",
                 "addToNode requires both the fan and reheat coil relationships to be established before insertion.");
        return false;
      }
      if (!thisObject.name()) {
        thisObject.createName();
        if (!thisObject.name()) {
          return false;
        }
      }

      auto insertion = InsertionPlan::prepare(*this, *airLoop, zoneSplitter, splitterBranchIndex, node, thermalZone);
      if (!insertion) {
        return false;
      }
      if (failureStage == AddToNodeFailureStage::AfterTopologyPrepared) {
        return false;
      }
      if (!maintainContainedAirPath()) {
        insertion.reset();
        OS_ASSERT(maintainContainedAirPath());
        return false;
      }
      if (!insertion->commit()) {
        insertion.reset();
        OS_ASSERT(maintainContainedAirPath());
        return false;
      }
      return true;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
