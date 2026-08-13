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
#include "Loop/PlantLoop_Impl.hpp"
#include "Mixer/AirLoopHVACZoneMixer.hpp"
#include "Mixer/AirLoopHVACZoneMixer_Impl.hpp"
#include "Splitter/AirLoopHVACZoneSplitter.hpp"
#include "Model.hpp"
#include "ModelObject.hpp"
#include "ModelObject/Branch.hpp"
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
#include "WaterToAirComponent/WaterToAirComponent.hpp"
#include "WaterToAirComponent/WaterToAirComponent_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/Logger.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/AirTerminal_SingleDuct_ConstantVolume_FourPipeInduction_FieldEnums.hxx>
#include <utilities/idd/Coil_Cooling_Water_FieldEnums.hxx>
#include <utilities/idd/Coil_Heating_Water_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/ZoneHVAC_EquipmentConnections_FieldEnums.hxx>
#include <utilities/idd/ZoneHVAC_AirDistributionUnit_FieldEnums.hxx>
#include <utilities/idf/WorkspaceObject_Impl.hpp>

#include <algorithm>
#include <iterator>
#include <vector>

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

    boost::optional<ThermalZone> thermalZoneContainingExhaustNode(const Model& model, const boost::optional<Node>& exhaustNode) {
      if (!exhaustNode) {
        return boost::none;
      }
      for (const auto& zone : model.getConcreteModelObjects<ThermalZone>()) {
        auto zoneImpl = zone.getImpl<detail::ThermalZone_Impl>();
        OS_ASSERT(zoneImpl);
        auto connections = zoneImpl->zoneHVACEquipmentConnections();
        if (!connections) {
          continue;
        }
        const auto exhaustNodes = connections->zoneAirExhaustNodes();
        if (std::ranges::find(exhaustNodes, *exhaustNode) != exhaustNodes.end()) {
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

    struct InductionDemandBranchRemovalPlan
    {
      bool valid = true;
      boost::optional<PlantLoop> plantLoop;
      boost::optional<Branch> branch;
    };

    InductionDemandBranchRemovalPlan inductionDemandBranchRemovalPlan(const boost::optional<HVACComponent>& coil) {
      InductionDemandBranchRemovalPlan result;
      if (!coil) {
        return result;
      }

      auto resolvedPlantLoop = coil->plantLoop();
      if (!resolvedPlantLoop) {
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
      auto plantLoopImpl = resolvedPlantLoop->getImpl<detail::PlantLoop_Impl>();
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

      result.plantLoop = *resolvedPlantLoop;
      result.branch = *targetBranch;
      return result;
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

  bool AirTerminalSingleDuctConstantVolumeFourPipeInduction::setCoolingCoil(const HVACComponent& coolingCoil) {
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
      auto thisObject = getObject<openstudio::epmodel::ModelObject>();
      auto ownedChildren = children();
      const bool hadTopology = static_cast<bool>(inletModelObject()) || static_cast<bool>(outletModelObject())
                               || static_cast<bool>(inducedAirInletNode()) || static_cast<bool>(thermalZoneContainingTerminal(model(), thisObject))
                               || static_cast<bool>(zoneHVACAirDistributionUnit());
      bool childHadPlantTopology = false;
      for (const auto& child : ownedChildren) {
        if (auto component = child.optionalCast<openstudio::epmodel::HVACComponent>(); component && component->plantLoop()) {
          childHadPlantTopology = true;
          break;
        }
      }

      if ((hadTopology || childHadPlantTopology) && !removeFromLoop()) {
        return {};
      }
      if (!maintainContainedAirPath()) {
        return {};
      }

      auto result = HVACComponent_Impl::remove();
      if (result.empty()) {
        return result;
      }

      for (auto& child : ownedChildren) {
        auto removedChild = child.remove();
        result.insert(result.end(), removedChild.begin(), removedChild.end());
      }
      return result;
    }

    bool AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::removeFromLoop() {
      auto thisObject = getObject<openstudio::epmodel::ModelObject>();
      auto thermalZone = thermalZoneContainingTerminal(model(), thisObject);
      auto inletNode = inletModelObject();
      auto outletNode = outletModelObject();
      boost::optional<Node> inducedAirInletNode = this->inducedAirInletNode();
      if (!thermalZone) {
        // removeBranchForZone can release the equipment-list projection before
        // asking the claimed terminal to remove itself. The exhaust projection
        // remains authoritative enough to recover the owning zone.
        thermalZone = thermalZoneContainingExhaustNode(model(), inducedAirInletNode);
      }
      auto heatingCoil = thisObject.getModelObjectTarget<openstudio::epmodel::HVACComponent>(
        openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::HeatingCoilName);
      auto coolingCoil = this->coolingCoil();
      auto heatingPlantRemovalPlan = inductionDemandBranchRemovalPlan(heatingCoil);
      auto coolingPlantRemovalPlan = inductionDemandBranchRemovalPlan(coolingCoil);
      if (!heatingPlantRemovalPlan.valid || !coolingPlantRemovalPlan.valid) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctConstantVolumeFourPipeInduction",
                 "Refusing to remove a four-pipe induction terminal whose coil does not belong to exactly one demand-equipment branch.");
        return false;
      }
      if (coolingPlantRemovalPlan.plantLoop && heatingPlantRemovalPlan.plantLoop && coolingPlantRemovalPlan.branch && heatingPlantRemovalPlan.branch
          && (*coolingPlantRemovalPlan.plantLoop == *heatingPlantRemovalPlan.plantLoop)
          && (*coolingPlantRemovalPlan.branch == *heatingPlantRemovalPlan.branch)) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctConstantVolumeFourPipeInduction",
                 "Refusing to remove a four-pipe induction terminal whose cooling and heating coils share one demand-equipment branch.");
        return false;
      }

      // Both water sides are preflighted before any air, zone, or plant state
      // is mutated. This keeps the compound terminal intact when persisted
      // plant topology is malformed.
      bool removedFromPlantLoop = false;
      if (coolingPlantRemovalPlan.plantLoop && coolingCoil) {
        if (!coolingPlantRemovalPlan.plantLoop->removeDemandBranchWithComponent(*coolingCoil)) {
          return false;
        }
        removedFromPlantLoop = true;
      }
      if (heatingPlantRemovalPlan.plantLoop && heatingCoil) {
        if (!heatingPlantRemovalPlan.plantLoop->removeDemandBranchWithComponent(*heatingCoil)) {
          return false;
        }
        removedFromPlantLoop = true;
      }

      bool shouldRemoveTerminalInletNode = false;
      if (auto terminal = thisObject.optionalCast<openstudio::epmodel::HVACComponent>()) {
        if (auto airLoop = terminal->airLoopHVAC()) {
          if (inletNode && outletNode) {
            const auto splitter = airLoop->zoneSplitter();
            const auto splitterBranchIndex = splitter.branchIndexForOutletModelObject(*inletNode);
            shouldRemoveTerminalInletNode = splitter.outletModelObject(splitterBranchIndex) == *inletNode;
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

      bool removedInducedAirInletNode = false;
      if (inducedAirInletNode) {
        if (thermalZone) {
          auto zoneImpl = thermalZone->getImpl<detail::ThermalZone_Impl>();
          OS_ASSERT(zoneImpl);
          auto zoneConnections = zoneImpl->getZoneHVACEquipmentConnections();
          if (!zoneConnections.getImpl<detail::ZoneHVACEquipmentConnections_Impl>()->removeZoneAirExhaustNode(*inducedAirInletNode)) {
            return false;
          }
        }
        setPointer(inducedAirInletPort(), openstudio::Handle(), false);
        inducedAirInletNode->remove();
        removedInducedAirInletNode = !model().getObject(inducedAirInletNode->handle());
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

      if (!maintainContainedAirPath()) {
        return false;
      }

      return removedFromAirLoop || static_cast<bool>(thermalZone) || removedInducedAirInletNode || removedFromPlantLoop || cleanedADU;
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
      if ((heatingCoil.model() != model()) || (heatingCoil.iddObject().type() != IddObjectType::Coil_Heating_Water)) {
        return false;
      }
      auto mutableHeatingCoil = heatingCoil;
      auto terminal = getObject<ModelObject>();
      auto previousCoil =
        terminal.getModelObjectTarget<HVACComponent>(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::HeatingCoilName);
      if (previousCoil && previousCoil->handle() == heatingCoil.handle()) {
        return maintainContainedAirPath();
      }
      if (auto owner = heatingCoil.containingHVACComponent(); owner && owner->handle() != terminal.handle()) {
        return false;
      }
      if (heatingCoil.getTarget(openstudio::Coil_Heating_WaterFields::AirInletNodeName)
          || heatingCoil.getTarget(openstudio::Coil_Heating_WaterFields::AirOutletNodeName)) {
        return false;
      }
      if (previousCoil) {
        OS_ASSERT(previousCoil->setPointer(openstudio::Coil_Heating_WaterFields::AirInletNodeName, Handle()));
        OS_ASSERT(previousCoil->setPointer(openstudio::Coil_Heating_WaterFields::AirOutletNodeName, Handle()));
      }
      if (!setPointer(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::HeatingCoilName, heatingCoil.handle(), false)) {
        OS_ASSERT(setPointer(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::HeatingCoilName,
                             previousCoil ? previousCoil->handle() : Handle(), false));
        if (previousCoil) {
          OS_ASSERT(maintainContainedAirPath());
        }
        return false;
      }
      if (!maintainContainedAirPath()) {
        OS_ASSERT(mutableHeatingCoil.setPointer(openstudio::Coil_Heating_WaterFields::AirInletNodeName, Handle()));
        OS_ASSERT(mutableHeatingCoil.setPointer(openstudio::Coil_Heating_WaterFields::AirOutletNodeName, Handle()));
        OS_ASSERT(setPointer(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::HeatingCoilName,
                             previousCoil ? previousCoil->handle() : Handle(), false));
        OS_ASSERT(maintainContainedAirPath());
        return false;
      }
      return true;
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
        if ((coolingCoil->model() != model()) || (coolingCoil->iddObject().type() != IddObjectType::Coil_Cooling_Water)) {
          return false;
        }
        auto mutableCoolingCoil = *coolingCoil;
        auto terminal = getObject<ModelObject>();
        auto previousCoil =
          terminal.getModelObjectTarget<HVACComponent>(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::CoolingCoilName);
        if (previousCoil && previousCoil->handle() == coolingCoil->handle()) {
          return maintainContainedAirPath();
        }
        if (auto owner = coolingCoil->containingHVACComponent(); owner && owner->handle() != terminal.handle()) {
          return false;
        }
        if (coolingCoil->getTarget(openstudio::Coil_Cooling_WaterFields::AirInletNodeName)
            || coolingCoil->getTarget(openstudio::Coil_Cooling_WaterFields::AirOutletNodeName)) {
          return false;
        }
        if (previousCoil) {
          OS_ASSERT(previousCoil->setPointer(openstudio::Coil_Cooling_WaterFields::AirInletNodeName, Handle()));
          OS_ASSERT(previousCoil->setPointer(openstudio::Coil_Cooling_WaterFields::AirOutletNodeName, Handle()));
        }
        if (!setPointer(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::CoolingCoilName, coolingCoil->handle(), false)) {
          OS_ASSERT(setPointer(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::CoolingCoilName,
                               previousCoil ? previousCoil->handle() : Handle(), false));
          if (previousCoil) {
            OS_ASSERT(maintainContainedAirPath());
          }
          return false;
        }
        if (!maintainContainedAirPath()) {
          OS_ASSERT(mutableCoolingCoil.setPointer(openstudio::Coil_Cooling_WaterFields::AirInletNodeName, Handle()));
          OS_ASSERT(mutableCoolingCoil.setPointer(openstudio::Coil_Cooling_WaterFields::AirOutletNodeName, Handle()));
          OS_ASSERT(setPointer(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::CoolingCoilName,
                               previousCoil ? previousCoil->handle() : Handle(), false));
          OS_ASSERT(maintainContainedAirPath());
          return false;
        }
        return true;
      }
      resetCoolingCoil();
      return true;
    }

    void AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::resetCoolingCoil() {
      if (auto previousCoil = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(
            openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::CoolingCoilName)) {
        OS_ASSERT(previousCoil->setPointer(openstudio::Coil_Cooling_WaterFields::AirInletNodeName, Handle()));
        OS_ASSERT(previousCoil->setPointer(openstudio::Coil_Cooling_WaterFields::AirOutletNodeName, Handle()));
      }
      OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::CoolingCoilObjectType, ""));
      OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::CoolingCoilName, ""));
      OS_ASSERT(maintainContainedAirPath());
    }

    bool AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::maintainContainedAirPath() {
      return reconcileContainedAirPath(false, nullptr);
    }

    void AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::doCanonicalize(LoadContext& context) {
      if (!repairContainedAirPath(context)) {
        detail::addLoadError(context, "Failed to repair contained air path for AirTerminal:SingleDuct:ConstantVolume:FourPipeInduction '"
                                        + getObject<ModelObject>().nameString() + "'.");
      }
    }

    bool AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::repairContainedAirPath(LoadContext& context) {
      return reconcileContainedAirPath(true, &context);
    }

    bool AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::reconcileContainedAirPath(bool allowChildNodeRecovery, LoadContext* context) {
      auto terminal = getObject<ModelObject>();
      auto heatingCoil =
        terminal.getModelObjectTarget<HVACComponent>(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::HeatingCoilName);
      auto coolingCoil =
        terminal.getModelObjectTarget<HVACComponent>(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::CoolingCoilName);
      if (heatingCoil && context) {
        const bool supported = heatingCoil->iddObject().type() == IddObjectType::Coil_Heating_Water;
        const auto owner = heatingCoil->containingHVACComponent();
        if (!supported || (owner && owner->handle() != terminal.handle())) {
          detail::addLoadWarning(*context, "Dropped " + std::string(supported ? "shared" : "unsupported")
                                             + " heating-coil reference from AirTerminal:SingleDuct:ConstantVolume:FourPipeInduction '"
                                             + terminal.nameString() + "'.");
          OS_ASSERT(setPointer(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::HeatingCoilName, Handle(), false));
          heatingCoil = boost::none;
        }
      }
      if (coolingCoil && context) {
        const bool supported = coolingCoil->iddObject().type() == IddObjectType::Coil_Cooling_Water;
        const auto owner = coolingCoil->containingHVACComponent();
        if (!supported || (owner && owner->handle() != terminal.handle())) {
          detail::addLoadWarning(*context, "Dropped " + std::string(supported ? "shared" : "unsupported")
                                             + " cooling-coil reference from AirTerminal:SingleDuct:ConstantVolume:FourPipeInduction '"
                                             + terminal.nameString() + "'.");
          OS_ASSERT(setPointer(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::CoolingCoilName, Handle(), false));
          coolingCoil = boost::none;
        }
      }
      if (!heatingCoil) {
        if (coolingCoil && coolingCoil->iddObject().type() != IddObjectType::Coil_Cooling_Water) {
          return false;
        }
        const bool hadExternalTopology = static_cast<bool>(inletModelObject()) || static_cast<bool>(outletModelObject())
                                         || static_cast<bool>(resolvedNodeTarget(inducedAirInletPort()))
                                         || static_cast<bool>(thermalZoneContainingTerminal(model(), terminal))
                                         || static_cast<bool>(zoneHVACAirDistributionUnit());
        if (context && hadExternalTopology) {
          // An incomplete air terminal may still own a valid plant-connected
          // optional cooling coil. Detach only the invalid air/zone projection.
          if (coolingCoil) {
            OS_ASSERT(setPointer(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::CoolingCoilName, Handle(), false));
          }
          const bool detached = removeFromLoop();
          if (coolingCoil) {
            OS_ASSERT(
              setPointer(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::CoolingCoilName, coolingCoil->handle(), false));
          }
          if (!detached) {
            detail::addLoadError(*context, "Could not detach incomplete AirTerminal:SingleDuct:ConstantVolume:FourPipeInduction '"
                                             + terminal.nameString() + "' from its external topology.");
            return false;
          }
        }
        bool changed = false;
        std::vector<Node> orphanCandidates;
        if (coolingCoil) {
          for (const auto field : {openstudio::Coil_Cooling_WaterFields::AirInletNodeName, openstudio::Coil_Cooling_WaterFields::AirOutletNodeName}) {
            if (auto node = coolingCoil->getModelObjectTarget<Node>(field)) {
              orphanCandidates.push_back(*node);
            }
            changed = changed || static_cast<bool>(coolingCoil->getTarget(field));
            OS_ASSERT(coolingCoil->setPointer(field, Handle()));
          }
        }
        const auto previousHeatingType =
          getString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::HeatingCoilObjectType, false, true).value_or("");
        const auto previousCoolingType =
          getString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::CoolingCoilObjectType, false, true).value_or("");
        const auto expectedCoolingType = coolingCoil ? coolingCoil->iddObject().name() : "";
        changed = changed || !previousHeatingType.empty() || !openstudio::istringEqual(previousCoolingType, expectedCoolingType);
        const auto previousHeatingName =
          getString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::HeatingCoilName, false, true).value_or("");
        changed = changed || !previousHeatingName.empty();
        OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::HeatingCoilName, ""));
        OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::HeatingCoilObjectType, ""));
        OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::CoolingCoilObjectType, expectedCoolingType));
        if (!coolingCoil) {
          const auto previousCoolingName =
            getString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::CoolingCoilName, false, true).value_or("");
          changed = changed || !previousCoolingName.empty();
          OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::CoolingCoilName, ""));
        }
        if (auto target = terminal.getTarget(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::ZoneMixerName)) {
          changed = true;
          auto oldMixer = target->optionalCast<AirLoopHVACZoneMixer>();
          OS_ASSERT(setPointer(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::ZoneMixerName, Handle(), false));
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
        OS_ASSERT(setPointer(inducedAirInletPort(), Handle(), false));
        OS_ASSERT(setPointer(outletPort(), Handle(), false));
        if ((changed || hadExternalTopology) && context) {
          detail::addLoadWarning(*context, "Detached incomplete AirTerminal:SingleDuct:ConstantVolume:FourPipeInduction '" + terminal.nameString()
                                             + "' and cleared its unresolved heating-coil reference.");
        }
        return true;
      }
      if ((heatingCoil->iddObject().type() != IddObjectType::Coil_Heating_Water)
          || (coolingCoil && coolingCoil->iddObject().type() != IddObjectType::Coil_Cooling_Water)) {
        return false;
      }
      bool changed = false;
      const auto storedHeatingType =
        terminal.getString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::HeatingCoilObjectType);
      changed = !storedHeatingType || !openstudio::istringEqual(*storedHeatingType, heatingCoil->iddObject().name());
      if (!setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::HeatingCoilObjectType,
                     heatingCoil->iddObject().name())) {
        return false;
      }
      if (coolingCoil) {
        const auto storedCoolingType =
          terminal.getString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::CoolingCoilObjectType);
        changed = changed || !storedCoolingType || !openstudio::istringEqual(*storedCoolingType, coolingCoil->iddObject().name());
        if (!setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::CoolingCoilObjectType,
                       coolingCoil->iddObject().name())) {
          return false;
        }
      } else {
        const auto previousCoolingName =
          getString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::CoolingCoilName, false, true).value_or("");
        const auto previousCoolingType =
          getString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::CoolingCoilObjectType, false, true).value_or("");
        changed = changed || !previousCoolingName.empty() || !previousCoolingType.empty();
        OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::CoolingCoilName, ""));
        OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::CoolingCoilObjectType, ""));
      }

      auto supplyNode = resolvedNodeTarget(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::SupplyAirInletNodeName);
      auto inducedNode = resolvedNodeTarget(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::InducedAirInletNodeName);
      auto outletNode = resolvedNodeTarget(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::AirOutletNodeName);
      if (!supplyNode || !inducedNode || !outletNode) {
        auto heatingOutletNode = heatingCoil->getModelObjectTarget<Node>(openstudio::Coil_Heating_WaterFields::AirOutletNodeName);
        changed = changed || static_cast<bool>(heatingCoil->getTarget(openstudio::Coil_Heating_WaterFields::AirInletNodeName))
                  || static_cast<bool>(heatingOutletNode);
        OS_ASSERT(heatingCoil->setPointer(openstudio::Coil_Heating_WaterFields::AirInletNodeName, Handle()));
        OS_ASSERT(heatingCoil->setPointer(openstudio::Coil_Heating_WaterFields::AirOutletNodeName, Handle()));
        boost::optional<Node> coolingOutletNode;
        if (coolingCoil) {
          coolingOutletNode = coolingCoil->getModelObjectTarget<Node>(openstudio::Coil_Cooling_WaterFields::AirOutletNodeName);
          changed = changed || static_cast<bool>(coolingCoil->getTarget(openstudio::Coil_Cooling_WaterFields::AirInletNodeName))
                    || static_cast<bool>(coolingOutletNode);
          OS_ASSERT(coolingCoil->setPointer(openstudio::Coil_Cooling_WaterFields::AirInletNodeName, Handle()));
          OS_ASSERT(coolingCoil->setPointer(openstudio::Coil_Cooling_WaterFields::AirOutletNodeName, Handle()));
        }
        if (auto target = terminal.getTarget(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::ZoneMixerName)) {
          changed = true;
          if (auto oldMixer = target->optionalCast<AirLoopHVACZoneMixer>()) {
            bool exclusivelyOwned = true;
            for (const auto& source : oldMixer->sources()) {
              if (source.handle() != terminal.handle()) {
                exclusivelyOwned = false;
                break;
              }
            }
            OS_ASSERT(setPointer(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::ZoneMixerName, Handle(), false));
            if (exclusivelyOwned) {
              oldMixer->remove();
            }
          } else {
            OS_ASSERT(setPointer(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::ZoneMixerName, Handle(), false));
          }
        }
        if (heatingOutletNode && heatingOutletNode->sources().empty()) {
          heatingOutletNode->remove();
        }
        if (coolingOutletNode && coolingOutletNode->sources().empty()) {
          coolingOutletNode->remove();
        }
        if (changed && context) {
          detail::addLoadInfo(*context, "Reconciled contained air path for AirTerminal:SingleDuct:ConstantVolume:FourPipeInduction '"
                                          + terminal.nameString() + "'.");
        }
        return true;
      }
      if (!terminal.name() && !terminal.createName()) {
        return false;
      }
      const auto baseName = terminal.nameString();

      boost::optional<AirLoopHVACZoneMixer> mixer;
      if (auto target = terminal.getTarget(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::ZoneMixerName)) {
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
      if (auto node = heatingCoil->getModelObjectTarget<Node>(openstudio::Coil_Heating_WaterFields::AirInletNodeName)) {
        displacedNodeCandidates.push_back(*node);
      }
      if (auto node = heatingCoil->getModelObjectTarget<Node>(openstudio::Coil_Heating_WaterFields::AirOutletNodeName)) {
        displacedNodeCandidates.push_back(*node);
      }
      if (coolingCoil) {
        if (auto node = coolingCoil->getModelObjectTarget<Node>(openstudio::Coil_Cooling_WaterFields::AirInletNodeName)) {
          displacedNodeCandidates.push_back(*node);
        }
        if (auto node = coolingCoil->getModelObjectTarget<Node>(openstudio::Coil_Cooling_WaterFields::AirOutletNodeName)) {
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

      boost::optional<Node> heatingOutletNode;
      boost::optional<Node> coolingOutletNode;
      if (allowChildNodeRecovery && mixer) {
        const auto currentHeatingOutlet = heatingCoil->getModelObjectTarget<Node>(openstudio::Coil_Heating_WaterFields::AirOutletNodeName);
        const auto currentInducedMixerInlet =
          mixer->inletModelObjects().size() > 1u ? mixer->inletModelObjects()[1].optionalCast<Node>() : boost::optional<Node>{};
        if (coolingCoil) {
          const auto currentCoolingInlet = coolingCoil->getModelObjectTarget<Node>(openstudio::Coil_Cooling_WaterFields::AirInletNodeName);
          if (currentHeatingOutlet && currentCoolingInlet && *currentHeatingOutlet == *currentCoolingInlet && *currentHeatingOutlet != *supplyNode
              && *currentHeatingOutlet != *inducedNode && *currentHeatingOutlet != *outletNode) {
            heatingOutletNode = currentHeatingOutlet;
          }
          const auto currentCoolingOutlet = coolingCoil->getModelObjectTarget<Node>(openstudio::Coil_Cooling_WaterFields::AirOutletNodeName);
          if (currentCoolingOutlet && currentInducedMixerInlet && *currentCoolingOutlet == *currentInducedMixerInlet
              && *currentCoolingOutlet != *supplyNode && *currentCoolingOutlet != *inducedNode && *currentCoolingOutlet != *outletNode) {
            coolingOutletNode = currentCoolingOutlet;
          }
        } else if (currentHeatingOutlet && currentInducedMixerInlet && *currentHeatingOutlet == *currentInducedMixerInlet
                   && *currentHeatingOutlet != *supplyNode && *currentHeatingOutlet != *inducedNode && *currentHeatingOutlet != *outletNode) {
          heatingOutletNode = currentHeatingOutlet;
        }
      }
      if (!heatingOutletNode) {
        heatingOutletNode = model().getOrCreateTransientByName<Node>(baseName + " Heating Coil Outlet");
      }
      if (coolingCoil && !coolingOutletNode) {
        coolingOutletNode = model().getOrCreateTransientByName<Node>(baseName + " Cooling Coil Outlet");
      }

      changed = changed || heatingCoil->getModelObjectTarget<Node>(openstudio::Coil_Heating_WaterFields::AirInletNodeName) != inducedNode
                || heatingCoil->getModelObjectTarget<Node>(openstudio::Coil_Heating_WaterFields::AirOutletNodeName) != heatingOutletNode;
      if (!heatingCoil->setPointer(openstudio::Coil_Heating_WaterFields::AirInletNodeName, inducedNode->handle())
          || !heatingCoil->setPointer(openstudio::Coil_Heating_WaterFields::AirOutletNodeName, heatingOutletNode->handle())) {
        return false;
      }

      Node inducedMixerInlet = *heatingOutletNode;
      if (coolingCoil) {
        OS_ASSERT(coolingOutletNode);
        changed = changed || coolingCoil->getModelObjectTarget<Node>(openstudio::Coil_Cooling_WaterFields::AirInletNodeName) != heatingOutletNode
                  || coolingCoil->getModelObjectTarget<Node>(openstudio::Coil_Cooling_WaterFields::AirOutletNodeName) != coolingOutletNode;
        if (!coolingCoil->setPointer(openstudio::Coil_Cooling_WaterFields::AirInletNodeName, heatingOutletNode->handle())
            || !coolingCoil->setPointer(openstudio::Coil_Cooling_WaterFields::AirOutletNodeName, coolingOutletNode->handle())) {
          return false;
        }
        inducedMixerInlet = *coolingOutletNode;
      }
      if (!mixer) {
        mixer = AirLoopHVACZoneMixer(model());
        changed = true;
        if (!mixer->setName(baseName + " Mixer")
            || !setPointer(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::ZoneMixerName, mixer->handle(), false)) {
          return false;
        }
      }
      auto mixerImpl = mixer->getImpl<detail::AirLoopHVACZoneMixer_Impl>();
      OS_ASSERT(mixerImpl);
      const auto previousMixerInlets = mixer->inletModelObjects();
      const auto previousMixerOutlet = mixer->getModelObjectTarget<Node>(mixer->outletPort());
      changed = changed || !previousMixerOutlet || *previousMixerOutlet != *outletNode || previousMixerInlets.size() != 2u
                || previousMixerInlets[0] != supplyNode->cast<ModelObject>() || previousMixerInlets[1] != inducedMixerInlet.cast<ModelObject>();
      if (!mixerImpl->setOutletNode(*outletNode) || !mixer->setInletModelObject(0u, supplyNode->cast<ModelObject>())
          || !mixer->setInletModelObject(1u, inducedMixerInlet.cast<ModelObject>())) {
        return false;
      }
      while (mixer->inletModelObjects().size() > 2u) {
        auto displacedNode = mixer->inletModelObjects().back().optionalCast<Node>();
        mixer->removePortForBranch(static_cast<unsigned>(mixer->inletModelObjects().size() - 1u));
        if (displacedNode && displacedNode->sources().empty() && model().getObject(displacedNode->handle())) {
          displacedNode->remove();
        }
      }
      for (auto& displacedNode : displacedNodeCandidates) {
        if (displacedNode == *supplyNode || displacedNode == *inducedNode || displacedNode == *outletNode || displacedNode == *heatingOutletNode
            || (coolingOutletNode && displacedNode == *coolingOutletNode)) {
          continue;
        }
        if (model().getObject(displacedNode.handle()) && displacedNode.sources().empty()) {
          displacedNode.remove();
        }
      }
      if (changed && context) {
        detail::addLoadInfo(*context, "Reconciled contained air path for AirTerminal:SingleDuct:ConstantVolume:FourPipeInduction '"
                                        + terminal.nameString() + "'.");
      }
      return true;
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
      return addToNode(node, AddToNodeFailureStage::None);
    }

    bool AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::addToNode(Node& node, AddToNodeFailureStage failureStage) {
      if (node.model() != model()) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctConstantVolumeFourPipeInduction",
                 "addToNode requires a node in the same model as the four-pipe induction terminal.");
        return false;
      }

      auto thisObject = getObject<ModelObject>();
      auto heatingChild =
        thisObject.getModelObjectTarget<HVACComponent>(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::HeatingCoilName);
      auto coolingChild =
        thisObject.getModelObjectTarget<HVACComponent>(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::CoolingCoilName);
      if (!heatingChild || heatingChild->iddObject().type() != IddObjectType::Coil_Heating_Water
          || (coolingChild && coolingChild->iddObject().type() != IddObjectType::Coil_Cooling_Water)) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctConstantVolumeFourPipeInduction",
                 "addToNode requires supported water-coil children before topology is changed.");
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
      auto thermalZone = owningThermalZoneForBranchNode(model(), node);
      if ((*mixerInlet != thisNode) && !isServedZoneReturnNode(thermalZone, *mixerInlet)) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctConstantVolumeFourPipeInduction",
                 "addToNode requires the drop node to either feed the ZoneMixer directly or be the served zone inlet node.");
        return false;
      }

      if (inletModelObject() || outletModelObject()) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctConstantVolumeFourPipeInduction",
                 "addToNode refuses to insert an already-connected four-pipe induction terminal.");
        return false;
      }

      if (!thisObject.name()) {
        thisObject.createName();
        if (!thisObject.name()) {
          return false;
        }
      }

      const std::string inletNodeName = node.nameString() + " - " + thisObject.nameString() + " Inlet Node";
      const bool inletNodeExisted = static_cast<bool>(model().getConcreteModelObjectByName<Node>(inletNodeName));
      auto inletNode = model().getOrCreateTransientByName<Node>(inletNodeName);
      auto adu = zoneHVACAirDistributionUnit();
      const auto aduOutletField = openstudio::ZoneHVAC_AirDistributionUnitFields::AirDistributionUnitOutletNodeName;
      const auto originalADUOutlet = adu ? adu->getString(aduOutletField, false, true) : boost::optional<std::string>{};

      boost::optional<ZoneHVACEquipmentConnections> zoneConnections;
      boost::optional<std::string> originalExhaustTarget;
      boost::optional<Node> exhaustNode;
      bool exhaustNodeExisted = true;
      bool terminalRegistered = false;
      bool terminalWasRegistered = false;
      if (thermalZone) {
        const auto zoneEquipment = thermalZone->equipment();
        terminalWasRegistered = std::ranges::find(zoneEquipment, thisObject) != zoneEquipment.end();
        auto zoneImpl = thermalZone->getImpl<detail::ThermalZone_Impl>();
        OS_ASSERT(zoneImpl);
        zoneConnections = zoneImpl->getZoneHVACEquipmentConnections();
        originalExhaustTarget =
          zoneConnections->getString(openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneAirExhaustNodeorNodeListName, false, true);
        const auto exhaustNodeName = thermalZone->nameString() + " Exhaust Node";
        exhaustNodeExisted = static_cast<bool>(model().getConcreteModelObjectByName<Node>(exhaustNodeName));
      }

      auto rollback = [&]() {
        if (terminalRegistered && thermalZone) {
          OS_ASSERT(unregisterTerminalFromThermalZone(thisObject, *thermalZone));
        }
        OS_ASSERT(setPointer(inducedAirInletPort(), Handle(), false));
        OS_ASSERT(setPointer(inletPort(), Handle(), false));
        OS_ASSERT(setPointer(outletPort(), Handle(), false));
        if (adu) {
          auto aduWorkspaceImpl = adu->getImpl<openstudio::detail::WorkspaceObject_Impl>();
          OS_ASSERT(aduWorkspaceImpl);
          OS_ASSERT(aduWorkspaceImpl->setPointer(aduOutletField, Handle(), false));
          OS_ASSERT(aduWorkspaceImpl->openstudio::detail::IdfObject_Impl::setString(aduOutletField, originalADUOutlet.value_or(""), false));
        }
        OS_ASSERT(zoneSplitter.setOutletModelObject(splitterBranchIndex, node.cast<ModelObject>()));
        if (zoneConnections) {
          const auto exhaustField = openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneAirExhaustNodeorNodeListName;
          auto connectionsWorkspaceImpl = zoneConnections->getImpl<openstudio::detail::WorkspaceObject_Impl>();
          OS_ASSERT(connectionsWorkspaceImpl);
          OS_ASSERT(connectionsWorkspaceImpl->setPointer(exhaustField, Handle(), false));
          OS_ASSERT(connectionsWorkspaceImpl->openstudio::detail::IdfObject_Impl::setString(exhaustField, originalExhaustTarget.value_or(""), false));
        }
        OS_ASSERT(maintainContainedAirPath());
        if (!inletNodeExisted && inletNode.sources().empty()) {
          inletNode.remove();
        }
        if (exhaustNode && !exhaustNodeExisted && exhaustNode->sources().empty()) {
          exhaustNode->remove();
        }
        return false;
      };

      if (!zoneSplitter.setOutletModelObject(splitterBranchIndex, inletNode.cast<ModelObject>())) {
        return rollback();
      }

      if (!setPointer(inletPort(), inletNode.handle(), false)) {
        return rollback();
      }

      if (!setPointer(outletPort(), node.handle(), false)) {
        return rollback();
      }

      if (adu) {
        adu->getImpl<openstudio::epmodel::detail::ZoneHVACAirDistributionUnit_Impl>()->setOutletNode(node);
      }

      if (thermalZone) {
        exhaustNode = zoneExhaustNodeForThermalZone(*thermalZone);
        if (!exhaustNode) {
          return rollback();
        }

        if (!setPointer(inducedAirInletPort(), exhaustNode->handle())) {
          return rollback();
        }

        if (!registerTerminalWithThermalZone(thisObject, *thermalZone)) {
          LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctConstantVolumeFourPipeInduction",
                   "addToNode failed to register the four-pipe induction terminal with the owning thermal zone.");
          return rollback();
        }
        terminalRegistered = !terminalWasRegistered;
      }

      if (failureStage == AddToNodeFailureStage::AfterTopologyPrepared) {
        return rollback();
      }
      if (!maintainContainedAirPath()) {
        return rollback();
      }
      return true;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
