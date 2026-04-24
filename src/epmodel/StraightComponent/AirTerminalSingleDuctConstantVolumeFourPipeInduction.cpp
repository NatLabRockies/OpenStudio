/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/AirTerminalSingleDuctConstantVolumeFourPipeInduction.hpp"
#include "StraightComponent/AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl.hpp"

#include "HVACComponent/HVACComponent.hpp"
#include "HVACComponent/HVACComponent_Impl.hpp"
#include "HVACComponent/ThermalZone.hpp"
#include "HVACComponent/ThermalZone_Impl.hpp"
#include "Loop/AirLoopHVAC.hpp"
#include "Loop/AirLoopHVAC_Impl.hpp"
#include "Loop/PlantLoop.hpp"
#include "Mixer/AirLoopHVACZoneMixer.hpp"
#include "Splitter/AirLoopHVACZoneSplitter.hpp"
#include "Model.hpp"
#include "ModelObject.hpp"
#include "ModelObject/ZoneHVACAirDistributionUnit.hpp"
#include "ModelObject/ZoneHVACAirDistributionUnit_Impl.hpp"
#include "ModelObject/ZoneHVACEquipmentConnections.hpp"
#include "ModelObject/ZoneHVACEquipmentConnections_Impl.hpp"
#include "ModelObject/ZoneHVACEquipmentList.hpp"
#include "ModelObject/ZoneHVACEquipmentList_Impl.hpp"
#include "Node.hpp"
#include "Node_Impl.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/Logger.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/AirTerminal_SingleDuct_ConstantVolume_FourPipeInduction_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/ZoneHVAC_EquipmentConnections_FieldEnums.hxx>
#include <utilities/idd/ZoneHVAC_AirDistributionUnit_FieldEnums.hxx>

#include <algorithm>
#include <iterator>

namespace openstudio {
namespace epmodel {

  namespace {

    void applyConstructorDefaults(AirTerminalSingleDuctConstantVolumeFourPipeInduction& terminal) {
      terminal.autosizeMaximumTotalAirFlowRate();
      terminal.autosizeMaximumHotWaterFlowRate();
      terminal.autosizeMaximumColdWaterFlowRate();
      OS_ASSERT(terminal.setMinimumColdWaterFlowRate(0.0));
      OS_ASSERT(terminal.setCoolingConvergenceTolerance(0.001));
      OS_ASSERT(terminal.setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::ZoneMixerName, ""));
    }

    boost::optional<ThermalZone> owningThermalZoneForBranchNode(const Model& model, const Node& node) {
      for (const auto& zone : model.getConcreteModelObjects<ThermalZone>()) {
        if (zone.zoneAirNode() == node) {
          return zone;
        }
      }
      return boost::none;
    }

    bool registerTerminalWithThermalZone(const ModelObject& terminal, ThermalZone& thermalZone) {
      auto zoneImpl = thermalZone.getImpl<detail::ThermalZone_Impl>();
      OS_ASSERT(zoneImpl);
      return zoneImpl->getZoneHVACEquipmentList().addEquipment(terminal);
    }

    boost::optional<ThermalZone> thermalZoneContainingTerminal(const Model& model, const ModelObject& terminal) {
      for (const auto& zone : model.getConcreteModelObjects<ThermalZone>()) {
        const auto equipment = zone.equipment();
        if (std::find(equipment.begin(), equipment.end(), terminal) != equipment.end()) {
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

    boost::optional<Node> zoneExhaustNodeForThermalZone(ThermalZone& thermalZone) {
      auto zoneImpl = thermalZone.getImpl<detail::ThermalZone_Impl>();
      OS_ASSERT(zoneImpl);

      auto zoneConnections = zoneImpl->getZoneHVACEquipmentConnections();
      if (auto exhaustNode =
            zoneConnections.getModelObjectTarget<Node>(openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneAirExhaustNodeorNodeListName)) {
        return exhaustNode;
      }

      auto exhaustNode = thermalZone.model().getOrCreateTransientByName<Node>(thermalZone.nameString() + " Exhaust Node");
      if (!zoneConnections.setPointer(openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneAirExhaustNodeorNodeListName, exhaustNode.handle())) {
        return boost::none;
      }
      return exhaustNode;
    }

  }  // namespace

  AirTerminalSingleDuctConstantVolumeFourPipeInduction::AirTerminalSingleDuctConstantVolumeFourPipeInduction(const Model& model)
    : StraightComponent(AirTerminalSingleDuctConstantVolumeFourPipeInduction::iddObjectType(), model) {
    auto impl = getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>();
    OS_ASSERT(impl);
    detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
    impl->canonicalize(context);
    applyConstructorDefaults(*this);
  }

  AirTerminalSingleDuctConstantVolumeFourPipeInduction::AirTerminalSingleDuctConstantVolumeFourPipeInduction(const Model& model,
                                                                                                             HVACComponent& heatingCoil)
    : StraightComponent(AirTerminalSingleDuctConstantVolumeFourPipeInduction::iddObjectType(), model) {
    auto impl = getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>();
    OS_ASSERT(impl);
    detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
    impl->canonicalize(context);
    applyConstructorDefaults(*this);
    OS_ASSERT(setHeatingCoil(heatingCoil));
  }

  AirTerminalSingleDuctConstantVolumeFourPipeInduction::AirTerminalSingleDuctConstantVolumeFourPipeInduction(
    std::shared_ptr<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl> impl)
    : StraightComponent(std::move(impl)) {}

  IddObjectType AirTerminalSingleDuctConstantVolumeFourPipeInduction::iddObjectType() {
    return IddObjectType::AirTerminal_SingleDuct_ConstantVolume_FourPipeInduction;
  }

  boost::optional<Schedule> AirTerminalSingleDuctConstantVolumeFourPipeInduction::availabilitySchedule() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->availabilitySchedule();
  }

  bool AirTerminalSingleDuctConstantVolumeFourPipeInduction::setAvailabilitySchedule(Schedule& schedule) {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->setAvailabilitySchedule(schedule);
  }

  void AirTerminalSingleDuctConstantVolumeFourPipeInduction::resetAvailabilitySchedule() {
    getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->resetAvailabilitySchedule();
  }

  boost::optional<double> AirTerminalSingleDuctConstantVolumeFourPipeInduction::maximumTotalAirFlowRate() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->maximumTotalAirFlowRate();
  }

  bool AirTerminalSingleDuctConstantVolumeFourPipeInduction::isMaximumTotalAirFlowRateAutosized() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->isMaximumTotalAirFlowRateAutosized();
  }

  bool AirTerminalSingleDuctConstantVolumeFourPipeInduction::setMaximumTotalAirFlowRate(double maximumTotalAirFlowRate) {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->setMaximumTotalAirFlowRate(maximumTotalAirFlowRate);
  }

  void AirTerminalSingleDuctConstantVolumeFourPipeInduction::autosizeMaximumTotalAirFlowRate() {
    getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->autosizeMaximumTotalAirFlowRate();
  }

  double AirTerminalSingleDuctConstantVolumeFourPipeInduction::inductionRatio() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->inductionRatio();
  }

  bool AirTerminalSingleDuctConstantVolumeFourPipeInduction::isInductionRatioDefaulted() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->isInductionRatioDefaulted();
  }

  bool AirTerminalSingleDuctConstantVolumeFourPipeInduction::setInductionRatio(double inductionRatio) {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->setInductionRatio(inductionRatio);
  }

  void AirTerminalSingleDuctConstantVolumeFourPipeInduction::resetInductionRatio() {
    getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->resetInductionRatio();
  }

  HVACComponent AirTerminalSingleDuctConstantVolumeFourPipeInduction::heatingCoil() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->heatingCoil();
  }

  bool AirTerminalSingleDuctConstantVolumeFourPipeInduction::setHeatingCoil(const HVACComponent& heatingCoil) {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->setHeatingCoil(heatingCoil);
  }

  boost::optional<double> AirTerminalSingleDuctConstantVolumeFourPipeInduction::maximumHotWaterFlowRate() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->maximumHotWaterFlowRate();
  }

  bool AirTerminalSingleDuctConstantVolumeFourPipeInduction::isMaximumHotWaterFlowRateAutosized() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->isMaximumHotWaterFlowRateAutosized();
  }

  bool AirTerminalSingleDuctConstantVolumeFourPipeInduction::setMaximumHotWaterFlowRate(double maximumHotWaterFlowRate) {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->setMaximumHotWaterFlowRate(maximumHotWaterFlowRate);
  }

  void AirTerminalSingleDuctConstantVolumeFourPipeInduction::resetMaximumHotWaterFlowRate() {
    getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->resetMaximumHotWaterFlowRate();
  }

  void AirTerminalSingleDuctConstantVolumeFourPipeInduction::autosizeMaximumHotWaterFlowRate() {
    getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->autosizeMaximumHotWaterFlowRate();
  }

  double AirTerminalSingleDuctConstantVolumeFourPipeInduction::minimumHotWaterFlowRate() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->minimumHotWaterFlowRate();
  }

  bool AirTerminalSingleDuctConstantVolumeFourPipeInduction::isMinimumHotWaterFlowRateDefaulted() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->isMinimumHotWaterFlowRateDefaulted();
  }

  bool AirTerminalSingleDuctConstantVolumeFourPipeInduction::setMinimumHotWaterFlowRate(double minimumHotWaterFlowRate) {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->setMinimumHotWaterFlowRate(minimumHotWaterFlowRate);
  }

  void AirTerminalSingleDuctConstantVolumeFourPipeInduction::resetMinimumHotWaterFlowRate() {
    getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->resetMinimumHotWaterFlowRate();
  }

  double AirTerminalSingleDuctConstantVolumeFourPipeInduction::heatingConvergenceTolerance() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->heatingConvergenceTolerance();
  }

  bool AirTerminalSingleDuctConstantVolumeFourPipeInduction::isHeatingConvergenceToleranceDefaulted() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->isHeatingConvergenceToleranceDefaulted();
  }

  bool AirTerminalSingleDuctConstantVolumeFourPipeInduction::setHeatingConvergenceTolerance(double heatingConvergenceTolerance) {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->setHeatingConvergenceTolerance(heatingConvergenceTolerance);
  }

  void AirTerminalSingleDuctConstantVolumeFourPipeInduction::resetHeatingConvergenceTolerance() {
    getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->resetHeatingConvergenceTolerance();
  }

  boost::optional<HVACComponent> AirTerminalSingleDuctConstantVolumeFourPipeInduction::coolingCoil() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->coolingCoil();
  }

  bool AirTerminalSingleDuctConstantVolumeFourPipeInduction::setCoolingCoil(const boost::optional<HVACComponent>& coolingCoil) {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->setCoolingCoil(coolingCoil);
  }

  void AirTerminalSingleDuctConstantVolumeFourPipeInduction::resetCoolingCoil() {
    getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->resetCoolingCoil();
  }

  boost::optional<double> AirTerminalSingleDuctConstantVolumeFourPipeInduction::maximumColdWaterFlowRate() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->maximumColdWaterFlowRate();
  }

  bool AirTerminalSingleDuctConstantVolumeFourPipeInduction::isMaximumColdWaterFlowRateAutosized() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->isMaximumColdWaterFlowRateAutosized();
  }

  bool AirTerminalSingleDuctConstantVolumeFourPipeInduction::setMaximumColdWaterFlowRate(double maximumColdWaterFlowRate) {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->setMaximumColdWaterFlowRate(maximumColdWaterFlowRate);
  }

  void AirTerminalSingleDuctConstantVolumeFourPipeInduction::resetMaximumColdWaterFlowRate() {
    getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->resetMaximumColdWaterFlowRate();
  }

  void AirTerminalSingleDuctConstantVolumeFourPipeInduction::autosizeMaximumColdWaterFlowRate() {
    getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->autosizeMaximumColdWaterFlowRate();
  }

  double AirTerminalSingleDuctConstantVolumeFourPipeInduction::minimumColdWaterFlowRate() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->minimumColdWaterFlowRate();
  }

  bool AirTerminalSingleDuctConstantVolumeFourPipeInduction::isMinimumColdWaterFlowRateDefaulted() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->isMinimumColdWaterFlowRateDefaulted();
  }

  bool AirTerminalSingleDuctConstantVolumeFourPipeInduction::setMinimumColdWaterFlowRate(double minimumColdWaterFlowRate) {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->setMinimumColdWaterFlowRate(minimumColdWaterFlowRate);
  }

  void AirTerminalSingleDuctConstantVolumeFourPipeInduction::resetMinimumColdWaterFlowRate() {
    getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->resetMinimumColdWaterFlowRate();
  }

  double AirTerminalSingleDuctConstantVolumeFourPipeInduction::coolingConvergenceTolerance() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->coolingConvergenceTolerance();
  }

  bool AirTerminalSingleDuctConstantVolumeFourPipeInduction::isCoolingConvergenceToleranceDefaulted() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->isCoolingConvergenceToleranceDefaulted();
  }

  bool AirTerminalSingleDuctConstantVolumeFourPipeInduction::setCoolingConvergenceTolerance(double coolingConvergenceTolerance) {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->setCoolingConvergenceTolerance(coolingConvergenceTolerance);
  }

  void AirTerminalSingleDuctConstantVolumeFourPipeInduction::resetCoolingConvergenceTolerance() {
    getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->resetCoolingConvergenceTolerance();
  }

  boost::optional<Node> AirTerminalSingleDuctConstantVolumeFourPipeInduction::inducedAirInletNode() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->inducedAirInletNode();
  }

  unsigned AirTerminalSingleDuctConstantVolumeFourPipeInduction::inducedAirInletPort() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->inducedAirInletPort();
  }

  bool AirTerminalSingleDuctConstantVolumeFourPipeInduction::addToNode(Node& node) {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->addToNode(node);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    boost::optional<ZoneHVACAirDistributionUnit> AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::zoneHVACAirDistributionUnit() const {
      auto terminal = getObject<openstudio::epmodel::ModelObject>();
      for (const auto& source : terminal.getSources(openstudio::IddObjectType::ZoneHVAC_AirDistributionUnit)) {
        if (auto adu = source.optionalCast<openstudio::epmodel::ZoneHVACAirDistributionUnit>()) {
          return adu;
        }
      }
      return boost::none;
    }

    std::vector<ModelObject> AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::children() const {
      std::vector<ModelObject> result;
      if (auto coolingCoil = this->coolingCoil()) {
        result.push_back(*coolingCoil);
      }
      auto heatingCoil = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(
        openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::HeatingCoilName);
      if (heatingCoil) {
        result.push_back(*heatingCoil);
      }
      return result;
    }

    std::vector<openstudio::IdfObject> AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::remove() {
      removeFromLoop();
      return HVACComponent_Impl::remove();
    }

    bool AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::removeFromLoop() {
      auto thisObject = getObject<openstudio::epmodel::ModelObject>();
      auto thermalZone = thermalZoneContainingTerminal(model(), thisObject);
      auto inletNode = inletModelObject();
      auto outletNode = outletModelObject();
      auto heatingCoil = thisObject.getModelObjectTarget<openstudio::epmodel::HVACComponent>(
        openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::HeatingCoilName);
      auto coolingCoil = this->coolingCoil();
      auto hotWaterPlantLoop = heatingCoil ? heatingCoil->plantLoop() : boost::optional<openstudio::epmodel::PlantLoop>{};
      auto coldWaterPlantLoop = coolingCoil ? coolingCoil->plantLoop() : boost::optional<openstudio::epmodel::PlantLoop>{};

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

      if (thermalZone && !unregisterTerminalFromThermalZone(thisObject, *thermalZone)) {
        return false;
      }

      boost::optional<Node> inducedAirInletNode = this->inducedAirInletNode();
      if (inducedAirInletNode) {
        if (thermalZone && thermalZone->equipment().empty()) {
          auto zoneImpl = thermalZone->getImpl<detail::ThermalZone_Impl>();
          OS_ASSERT(zoneImpl);
          auto zoneConnections = zoneImpl->getZoneHVACEquipmentConnections();
          const auto exhaustField = openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneAirExhaustNodeorNodeListName;
          if (auto exhaustNode = zoneConnections.getModelObjectTarget<Node>(exhaustField)) {
            if (*exhaustNode == *inducedAirInletNode) {
              zoneConnections.setPointer(exhaustField, openstudio::Handle());
            }
          }
        }
        setPointer(inducedAirInletPort(), openstudio::Handle(), false);

        if (inducedAirInletNode->sources().empty()) {
          inducedAirInletNode->remove();
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

      setPointer(inletPort(), openstudio::Handle(), false);
      setPointer(outletPort(), openstudio::Handle(), false);

      if (shouldRemoveTerminalInletNode) {
        if (auto node = inletNode->optionalCast<openstudio::epmodel::Node>()) {
          node->remove();
        }
      }

      bool removedFromPlantLoop = false;
      if (coldWaterPlantLoop && coolingCoil) {
        if (!coldWaterPlantLoop->removeDemandBranchWithComponent(*coolingCoil)) {
          return false;
        }
        removedFromPlantLoop = true;
      }
      if (hotWaterPlantLoop && heatingCoil) {
        if (!hotWaterPlantLoop->removeDemandBranchWithComponent(*heatingCoil)) {
          return false;
        }
        removedFromPlantLoop = true;
      }

      return removedFromAirLoop || static_cast<bool>(thermalZone) || removedFromPlantLoop || cleanedADU;
    }

    boost::optional<Schedule> AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::availabilitySchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(
        openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::AvailabilityScheduleName);
    }

    unsigned AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::inletPort() const {
      return openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::SupplyAirInletNodeName;
    }

    unsigned AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::outletPort() const {
      return openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::AirOutletNodeName;
    }

    bool AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::setAvailabilitySchedule(Schedule& schedule) {
      return ModelObject_Impl::setSchedule(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::AvailabilityScheduleName,
                                           "AirTerminalSingleDuctConstantVolumeFourPipeInduction", "Availability", schedule);
    }

    void AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::resetAvailabilitySchedule() {
      OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::AvailabilityScheduleName, ""));
    }

    boost::optional<double> AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::maximumTotalAirFlowRate() const {
      return getDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::MaximumTotalAirFlowRate, true);
    }

    bool AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::isMaximumTotalAirFlowRateAutosized() const {
      if (auto value = getString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::MaximumTotalAirFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::setMaximumTotalAirFlowRate(double maximumTotalAirFlowRate) {
      return setDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::MaximumTotalAirFlowRate, maximumTotalAirFlowRate);
    }

    void AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::autosizeMaximumTotalAirFlowRate() {
      OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::MaximumTotalAirFlowRate, "autosize"));
    }

    double AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::inductionRatio() const {
      const auto value = getDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::InductionRatio, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::isInductionRatioDefaulted() const {
      return isEmpty(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::InductionRatio);
    }

    bool AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::setInductionRatio(double inductionRatio) {
      return setDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::InductionRatio, inductionRatio);
    }

    void AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::resetInductionRatio() {
      OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::InductionRatio, ""));
    }

    HVACComponent AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::heatingCoil() const {
      auto coil = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(
        openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::HeatingCoilName);
      OS_ASSERT(coil);
      return *coil;
    }

    bool AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::setHeatingCoil(const HVACComponent& heatingCoil) {
      if (heatingCoil.model() != model()) {
        return false;
      }
      return setPointer(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::HeatingCoilName, heatingCoil.handle(), false);
    }

    boost::optional<double> AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::maximumHotWaterFlowRate() const {
      return getDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::MaximumHotWaterFlowRate, true);
    }

    bool AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::isMaximumHotWaterFlowRateAutosized() const {
      if (auto value = getString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::MaximumHotWaterFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::setMaximumHotWaterFlowRate(double maximumHotWaterFlowRate) {
      return setDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::MaximumHotWaterFlowRate, maximumHotWaterFlowRate);
    }

    void AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::resetMaximumHotWaterFlowRate() {
      OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::MaximumHotWaterFlowRate, ""));
    }

    void AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::autosizeMaximumHotWaterFlowRate() {
      OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::MaximumHotWaterFlowRate, "autosize"));
    }

    double AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::minimumHotWaterFlowRate() const {
      const auto value = getDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::MinimumHotWaterFlowRate, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::isMinimumHotWaterFlowRateDefaulted() const {
      return isEmpty(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::MinimumHotWaterFlowRate);
    }

    bool AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::setMinimumHotWaterFlowRate(double minimumHotWaterFlowRate) {
      return setDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::MinimumHotWaterFlowRate, minimumHotWaterFlowRate);
    }

    void AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::resetMinimumHotWaterFlowRate() {
      OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::MinimumHotWaterFlowRate, ""));
    }

    double AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::heatingConvergenceTolerance() const {
      const auto value = getDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::HeatingConvergenceTolerance, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::isHeatingConvergenceToleranceDefaulted() const {
      return isEmpty(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::HeatingConvergenceTolerance);
    }

    bool AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::setHeatingConvergenceTolerance(double heatingConvergenceTolerance) {
      return setDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::HeatingConvergenceTolerance,
                       heatingConvergenceTolerance);
    }

    void AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::resetHeatingConvergenceTolerance() {
      OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::HeatingConvergenceTolerance, ""));
    }

    boost::optional<HVACComponent> AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::coolingCoil() const {
      return getObject<ModelObject>().getModelObjectTarget<HVACComponent>(
        openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::CoolingCoilName);
    }

    bool AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::setCoolingCoil(const boost::optional<HVACComponent>& coolingCoil) {
      if (coolingCoil) {
        if (coolingCoil->model() != model()) {
          return false;
        }
        return setPointer(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::CoolingCoilName, coolingCoil->handle(), false);
      }
      resetCoolingCoil();
      return true;
    }

    void AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::resetCoolingCoil() {
      OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::CoolingCoilName, ""));
    }

    boost::optional<double> AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::maximumColdWaterFlowRate() const {
      return getDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::MaximumColdWaterFlowRate, true);
    }

    bool AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::isMaximumColdWaterFlowRateAutosized() const {
      if (auto value = getString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::MaximumColdWaterFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::setMaximumColdWaterFlowRate(double maximumColdWaterFlowRate) {
      return setDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::MaximumColdWaterFlowRate, maximumColdWaterFlowRate);
    }

    void AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::resetMaximumColdWaterFlowRate() {
      OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::MaximumColdWaterFlowRate, ""));
    }

    void AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::autosizeMaximumColdWaterFlowRate() {
      OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::MaximumColdWaterFlowRate, "autosize"));
    }

    double AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::minimumColdWaterFlowRate() const {
      const auto value = getDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::MinimumColdWaterFlowRate, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::isMinimumColdWaterFlowRateDefaulted() const {
      return isEmpty(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::MinimumColdWaterFlowRate);
    }

    bool AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::setMinimumColdWaterFlowRate(double minimumColdWaterFlowRate) {
      return setDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::MinimumColdWaterFlowRate, minimumColdWaterFlowRate);
    }

    void AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::resetMinimumColdWaterFlowRate() {
      OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::MinimumColdWaterFlowRate, ""));
    }

    double AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::coolingConvergenceTolerance() const {
      const auto value = getDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::CoolingConvergenceTolerance, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::isCoolingConvergenceToleranceDefaulted() const {
      return isEmpty(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::CoolingConvergenceTolerance);
    }

    bool AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::setCoolingConvergenceTolerance(double coolingConvergenceTolerance) {
      return setDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::CoolingConvergenceTolerance,
                       coolingConvergenceTolerance);
    }

    void AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::resetCoolingConvergenceTolerance() {
      OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::CoolingConvergenceTolerance, ""));
    }

    boost::optional<Node> AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::inducedAirInletNode() const {
      return getObject<ModelObject>().getModelObjectTarget<Node>(
        openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::InducedAirInletNodeName);
    }

    unsigned AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::inducedAirInletPort() const {
      return openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::InducedAirInletNodeName;
    }

    bool AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::addToNode(Node& node) {
      if (node.model() != model()) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctConstantVolumeFourPipeInduction",
                 "addToNode requires a node in the same model as the four-pipe induction terminal.");
        return false;
      }

      auto airLoop = node.airLoopHVAC();
      if (!airLoop) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctConstantVolumeFourPipeInduction",
                 "addToNode requires a node that resolves to an AirLoopHVAC context.");
        return false;
      }

      auto zoneSplitter = airLoop->zoneSplitter();
      auto zoneMixer = airLoop->zoneMixer();
      const auto thisNode = node.cast<ModelObject>();
      const auto splitterOutlets = zoneSplitter.outletModelObjects();
      const auto splitterIt = std::find(splitterOutlets.begin(), splitterOutlets.end(), thisNode);
      if (splitterIt == splitterOutlets.end()) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctConstantVolumeFourPipeInduction",
                 "addToNode requires the drop node to be a ZoneSplitter outlet node for the target AirLoopHVAC.");
        return false;
      }
      const auto splitterBranchIndex = static_cast<unsigned>(std::distance(splitterOutlets.begin(), splitterIt));

      auto mixerInlet = zoneMixer.inletModelObject(splitterBranchIndex);
      if (!mixerInlet) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctConstantVolumeFourPipeInduction",
                 "addToNode requires a corresponding ZoneMixer inlet for ZoneSplitter branch index " << splitterBranchIndex << ".");
        return false;
      }
      if (*mixerInlet != thisNode) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctConstantVolumeFourPipeInduction",
                 "addToNode requires the ZoneMixer inlet for ZoneSplitter branch index " << splitterBranchIndex << " to match the drop node.");
        return false;
      }

      if (inletModelObject() || outletModelObject()) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctConstantVolumeFourPipeInduction",
                 "addToNode refuses to insert an already-connected four-pipe induction terminal.");
        return false;
      }

      auto thisObject = getObject<ModelObject>();
      if (!thisObject.name()) {
        thisObject.createName();
        if (!thisObject.name()) {
          return false;
        }
      }

      const std::string inletNodeName = node.nameString() + " - " + thisObject.nameString() + " Inlet Node";
      auto inletNode = model().getOrCreateTransientByName<Node>(inletNodeName);
      if (!zoneSplitter.setOutletModelObject(splitterBranchIndex, inletNode.cast<ModelObject>())) {
        return false;
      }

      if (!setPointer(inletPort(), inletNode.handle(), false)) {
        return false;
      }

      if (!setPointer(outletPort(), node.handle(), false)) {
        return false;
      }

      if (auto adu = zoneHVACAirDistributionUnit()) {
        adu->getImpl<openstudio::epmodel::detail::ZoneHVACAirDistributionUnit_Impl>()->setOutletNode(node);
      }

      if (auto thermalZone = owningThermalZoneForBranchNode(model(), node)) {
        auto exhaustNode = zoneExhaustNodeForThermalZone(*thermalZone);
        if (!exhaustNode) {
          return false;
        }

        if (!setPointer(inducedAirInletPort(), exhaustNode->handle())) {
          return false;
        }

        if (!registerTerminalWithThermalZone(thisObject, *thermalZone)) {
          LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctConstantVolumeFourPipeInduction",
                   "addToNode failed to register the four-pipe induction terminal with the owning thermal zone.");
          return false;
        }
      }

      return true;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
