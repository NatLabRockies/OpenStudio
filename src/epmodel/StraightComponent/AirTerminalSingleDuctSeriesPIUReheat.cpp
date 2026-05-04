/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/AirTerminalSingleDuctSeriesPIUReheat.hpp"
#include "StraightComponent/AirTerminalSingleDuctSeriesPIUReheat_Impl.hpp"

#include "HVACComponent/ThermalZone.hpp"
#include "HVACComponent/ThermalZone_Impl.hpp"
#include "HVACComponent.hpp"
#include "Loop/AirLoopHVAC.hpp"
#include "Loop/PlantLoop.hpp"
#include "Mixer/AirLoopHVACZoneMixer.hpp"
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

#include <algorithm>
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
             || (type == IddObjectType::Fan_VariableVolume) || (type == IddObjectType::OS_Fan_ConstantVolume)
             || (type == IddObjectType::OS_Fan_SystemModel) || (type == IddObjectType::OS_Fan_OnOff)
             || (type == IddObjectType::OS_Fan_VariableVolume);
    }

    bool isSupportedSeriesPIUReheatCoil(const HVACComponent& hvacComponent) {
      const auto type = hvacComponent.iddObject().type();
      return (type == IddObjectType::Coil_Heating_Electric) || (type == IddObjectType::Coil_Heating_Fuel)
             || (type == IddObjectType::Coil_Heating_Water) || (type == IddObjectType::OS_Coil_Heating_Electric)
             || (type == IddObjectType::OS_Coil_Heating_Gas) || (type == IddObjectType::OS_Coil_Heating_Water);
    }

    boost::optional<ThermalZone> owningThermalZoneForZoneNode(const Model& model, const Node& node) {
      for (const auto& thermalZone : model.getConcreteModelObjects<ThermalZone>()) {
        if (thermalZone.zoneAirNode() == node) {
          return thermalZone;
        }
      }
      return boost::none;
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

  }  // namespace

  AirTerminalSingleDuctSeriesPIUReheat::AirTerminalSingleDuctSeriesPIUReheat(const Model& model)
    : StraightComponent(AirTerminalSingleDuctSeriesPIUReheat::iddObjectType(), model) {
    autosizeMaximumAirFlowRate();
    autosizeMaximumPrimaryAirFlowRate();
    autosizeMinimumPrimaryAirFlowFraction();
    autosizeMaximumHotWaterorSteamFlowRate();
    OS_ASSERT(setMinimumHotWaterorSteamFlowRate(0.0));
    OS_ASSERT(setConvergenceTolerance(0.001));
    OS_ASSERT(setFanControlType("ConstantSpeed"));
    OS_ASSERT(setMinimumFanTurnDownRatio(0.3));
    OS_ASSERT(setHeatingControlType("Staged"));
    OS_ASSERT(setDesignHeatingDischargeAirTemperature(32.1));
    OS_ASSERT(setHighLimitHeatingDischargeAirTemperature(37.7));
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
      if (!setPointer(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::FanName, fanComponent.handle(), false)) {
        return false;
      }

      const auto type = fanComponent.iddObject().type();
      if (type == IddObjectType::Fan_ConstantVolume || type == IddObjectType::OS_Fan_ConstantVolume) {
        return setFanControlType("ConstantSpeed");
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
      return setPointer(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::ReheatCoilName, coil.handle(), false);
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
      auto reheat = thisObject.getModelObjectTarget<openstudio::epmodel::HVACComponent>(
        openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::ReheatCoilName);

      if (!removeFromLoop()) {
        return {};
      }

      if (reheat) {
        if (auto plantLoop = reheat->plantLoop()) {
          plantLoop->removeDemandBranchWithComponent(*reheat);
        }
      }

      return HVACComponent_Impl::remove();
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
      auto plantLoop = reheat ? reheat->plantLoop() : boost::optional<openstudio::epmodel::PlantLoop>{};
      auto secondaryNode = secondaryAirInletNode();
      if (!thermalZone && secondaryNode) {
        thermalZone = thermalZoneContainingExhaustNode(model(), *secondaryNode);
      }

      bool shouldRemoveTerminalInletNode = false;
      if (auto terminal = thisObject.optionalCast<openstudio::epmodel::HVACComponent>()) {
        if (auto airLoop = terminal->airLoopHVAC()) {
          if (inletNode && outletNode) {
            const auto splitter = airLoop->zoneSplitter();
            const auto mixer = airLoop->zoneMixer();
            const auto splitterBranchIndex = splitter.branchIndexForOutletModelObject(*inletNode);
            shouldRemoveTerminalInletNode =
              (splitter.outletModelObject(splitterBranchIndex) == *inletNode) && (mixer.inletModelObject(splitterBranchIndex) == *outletNode);
          }
        }
      }

      bool removedFromAirLoop = false;
      if (inletNode && outletNode) {
        if (!StraightComponent_Impl::removeFromLoop()) {
          return false;
        }
        removedFromAirLoop = true;
      }

      if (thermalZone) {
        if (!unregisterTerminalFromZone(*thermalZone, thisObject)) {
          return false;
        }
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

        if (secondaryNode->sources().empty()) {
          secondaryNode->remove();
          removedSecondaryNode = true;
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
      if (plantLoop && reheat) {
        if (!plantLoop->removeDemandBranchWithComponent(*reheat)) {
          return false;
        }
        removedFromPlantLoop = true;
      }

      return removedFromAirLoop || static_cast<bool>(thermalZone) || removedSecondaryNode || cleanedADU || removedFromPlantLoop;
    }

    bool AirTerminalSingleDuctSeriesPIUReheat_Impl::addToNode(Node& node) {
      if (node.model() != model()) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctSeriesPIUReheat",
                 "addToNode requires a node in the same model as the series PIU terminal.");
        return false;
      }

      if (getObject<openstudio::epmodel::HVACComponent>().loop()) {
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
      auto zoneMixer = airLoop->zoneMixer();
      const auto thisNode = node.cast<ModelObject>();
      const auto splitterOutlets = zoneSplitter.outletModelObjects();
      const auto splitterIt = std::find(splitterOutlets.begin(), splitterOutlets.end(), thisNode);
      if (splitterIt == splitterOutlets.end()) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctSeriesPIUReheat",
                 "addToNode requires the drop node to be a ZoneSplitter outlet node for the target AirLoopHVAC.");
        return false;
      }
      const auto splitterBranchIndex = static_cast<unsigned>(std::distance(splitterOutlets.begin(), splitterIt));

      auto mixerInlet = zoneMixer.inletModelObject(splitterBranchIndex);
      if (!mixerInlet) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctSeriesPIUReheat",
                 "addToNode requires a corresponding ZoneMixer inlet for ZoneSplitter branch index " << splitterBranchIndex << ".");
        return false;
      }
      if (*mixerInlet != thisNode) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctSeriesPIUReheat",
                 "addToNode requires the ZoneMixer inlet for ZoneSplitter branch index " << splitterBranchIndex << " to match the drop node.");
        return false;
      }

      auto thermalZone = owningThermalZoneForZoneNode(model(), node);
      if (!thermalZone) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctSeriesPIUReheat",
                 "addToNode requires the drop node to be the current zone-branch node for an attached thermal zone.");
        return false;
      }

      auto thisObject = getObject<ModelObject>();
      if (!thisObject.name()) {
        thisObject.createName();
        if (!thisObject.name()) {
          return false;
        }
      }

      auto zoneImpl = thermalZone->getImpl<detail::ThermalZone_Impl>();
      OS_ASSERT(zoneImpl);
      auto zoneConnections = zoneImpl->getZoneHVACEquipmentConnections();
      auto adu = zoneHVACAirDistributionUnit();
      const auto previousADUOutletNode = adu ? adu->outletNode() : boost::optional<Node>{};

      const std::string inletNodeName = node.nameString() + " - " + thisObject.nameString() + " Inlet Node";
      auto inletNode = model().getOrCreateTransientByName<Node>(inletNodeName);
      const std::string secondaryNodeName = node.nameString() + " - " + thisObject.nameString() + " Secondary Air Inlet Node";
      auto secondaryNode = model().getOrCreateTransientByName<Node>(secondaryNodeName);

      bool splitterRewired = false;
      bool inletAssigned = false;
      bool outletAssigned = false;
      bool secondaryAssigned = false;
      bool exhaustRegistered = false;
      bool aduUpdated = false;
      bool zoneRegistered = false;

      const auto rollback = [&]() {
        if (zoneRegistered) {
          unregisterTerminalFromZone(*thermalZone, thisObject);
        }
        if (exhaustRegistered) {
          (void)zoneConnections.getImpl<detail::ZoneHVACEquipmentConnections_Impl>()->removeZoneAirExhaustNode(secondaryNode);
        }
        if (secondaryAssigned) {
          (void)setPointer(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::SecondaryAirInletNodeName, openstudio::Handle(), false);
        }
        if (adu && aduUpdated) {
          if (previousADUOutletNode) {
            (void)adu->getImpl<openstudio::epmodel::detail::ZoneHVACAirDistributionUnit_Impl>()->setOutletNode(*previousADUOutletNode);
          } else {
            (void)adu->setPointer(openstudio::ZoneHVAC_AirDistributionUnitFields::AirDistributionUnitOutletNodeName, openstudio::Handle());
          }
        }
        if (outletAssigned) {
          (void)setPointer(outletPort(), openstudio::Handle(), false);
        }
        if (inletAssigned) {
          (void)setPointer(inletPort(), openstudio::Handle(), false);
        }
        if (splitterRewired) {
          (void)zoneSplitter.setOutletModelObject(splitterBranchIndex, thisNode);
        }
        if (secondaryNode.sources().empty()) {
          secondaryNode.remove();
        }
        if (inletNode.sources().empty()) {
          inletNode.remove();
        }
      };

      if (!zoneSplitter.setOutletModelObject(splitterBranchIndex, inletNode.cast<ModelObject>())) {
        return false;
      }
      splitterRewired = true;

      if (!setPointer(inletPort(), inletNode.handle(), false)) {
        rollback();
        return false;
      }
      inletAssigned = true;

      if (!setPointer(outletPort(), node.handle(), false)) {
        rollback();
        return false;
      }
      outletAssigned = true;

      if (!setPointer(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::SecondaryAirInletNodeName, secondaryNode.handle(), false)) {
        rollback();
        return false;
      }
      secondaryAssigned = true;

      if (!zoneConnections.getImpl<detail::ZoneHVACEquipmentConnections_Impl>()->addZoneAirExhaustNode(secondaryNode)) {
        rollback();
        return false;
      }
      exhaustRegistered = true;

      if (adu) {
        if (!adu->getImpl<openstudio::epmodel::detail::ZoneHVACAirDistributionUnit_Impl>()->setOutletNode(node)) {
          rollback();
          return false;
        }
        aduUpdated = true;
      }

      if (!registerTerminalWithZone(*thermalZone, thisObject)) {
        rollback();
        return false;
      }
      zoneRegistered = true;

      auto fanComponent = fan();
      auto loopSchedule = airLoop->availabilitySchedule();
      if (!syncFanAvailabilityWithLoop(fanComponent, loopSchedule)) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctSeriesPIUReheat",
                 "Unable to synchronize PIU fan availability schedule for " << briefDescription() << ".");
        rollback();
        return false;
      }

      return true;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
