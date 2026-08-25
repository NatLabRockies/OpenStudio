/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/AirTerminalSingleDuctConstantVolumeFourPipeBeam.hpp"
#include "StraightComponent/AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl.hpp"
#include "StraightComponent/CoilCoolingFourPipeBeam.hpp"
#include "StraightComponent/CoilCoolingFourPipeBeam_Impl.hpp"
#include "StraightComponent/CoilHeatingFourPipeBeam.hpp"
#include "StraightComponent/CoilHeatingFourPipeBeam_Impl.hpp"
#include "StraightComponent/CompoundTerminalTopologyInspection.hpp"
#include "Loop/AirLoopHVAC_Impl.hpp"

#include "HVACComponent/ThermalZone.hpp"
#include "HVACComponent.hpp"
#include "HVACComponent/ThermalZone_Impl.hpp"
#include "Loop/AirLoopHVAC.hpp"
#include "Loop/PlantLoop.hpp"
#include "Loop/PlantLoop_Impl.hpp"
#include "Mixer/AirLoopHVACZoneMixer.hpp"
#include "Mixer/AirLoopHVACZoneMixer_Impl.hpp"
#include "Model.hpp"
#include "Model_Impl.hpp"
#include "ModelObject.hpp"
#include "ModelObject/ZoneHVACAirDistributionUnit.hpp"
#include "ModelObject/ZoneHVACAirDistributionUnit_Impl.hpp"
#include "ModelObject/ZoneHVACEquipmentConnections.hpp"
#include "ModelObject/ZoneHVACEquipmentConnections_Impl.hpp"
#include "ModelObject/ZoneHVACEquipmentList.hpp"
#include "ModelObject/ZoneHVACEquipmentList_Impl.hpp"
#include "Node.hpp"
#include "Node_Impl.hpp"
#include "Splitter/AirLoopHVACZoneSplitter.hpp"
#include "Splitter/AirLoopHVACZoneSplitter_Impl.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"

#include <algorithm>
#include <iterator>
#include <utilities/core/Assert.hpp>
#include <utilities/core/Logger.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/AirTerminal_SingleDuct_ConstantVolume_FourPipeBeam_FieldEnums.hxx>
#include <utilities/idd/OS_AirTerminal_SingleDuct_ConstantVolume_FourPipeBeam_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/ZoneHVAC_EquipmentConnections_FieldEnums.hxx>
#include <utilities/idd/ZoneHVAC_AirDistributionUnit_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  namespace {

    using detail::existingNodeField;
    using detail::existingObjectField;
    using detail::isSoleOwnedChild;

    void applyConstructorDefaults(AirTerminalSingleDuctConstantVolumeFourPipeBeam& terminal) {
      terminal.autosizeDesignPrimaryAirVolumeFlowRate();
      terminal.autosizeDesignChilledWaterVolumeFlowRate();
      terminal.autosizeDesignHotWaterVolumeFlowRate();
      terminal.autosizeZoneTotalBeamLength();
    }

    struct FourPipeBeamTopologyRemovalPlans
    {
      boost::optional<CoilCoolingFourPipeBeam> coolingCoil;
      boost::optional<CoilHeatingFourPipeBeam> heatingCoil;
      std::unique_ptr<detail::AirLoopHVAC_Impl::SingleDuctTerminalRemovalPlan> externalTopology;
    };

    std::unique_ptr<FourPipeBeamTopologyRemovalPlans> prepareFourPipeBeamTopologyRemoval(const ModelObject& terminalObject) {
      auto result = std::make_unique<FourPipeBeamTopologyRemovalPlans>();

      const auto coolingRelationship =
        existingObjectField(terminalObject, openstudio::OS_AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::CoolingCoilName);
      if (coolingRelationship.set) {
        const auto coolingCoil = coolingRelationship.object ? coolingRelationship.object->optionalCast<CoilCoolingFourPipeBeam>() : boost::none;
        if (!coolingCoil || !isSoleOwnedChild(terminalObject, *coolingCoil)) {
          return nullptr;
        }
        result->coolingCoil = *coolingCoil;
      }

      const auto heatingRelationship =
        existingObjectField(terminalObject, openstudio::OS_AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::HeatingCoilName);
      if (heatingRelationship.set) {
        const auto heatingCoil = heatingRelationship.object ? heatingRelationship.object->optionalCast<CoilHeatingFourPipeBeam>() : boost::none;
        if (!heatingCoil || !isSoleOwnedChild(terminalObject, *heatingCoil)) {
          return nullptr;
        }
        result->heatingCoil = *heatingCoil;
      }

      auto terminal = terminalObject.cast<StraightComponent>();
      if (detail::AirLoopHVAC_Impl::SingleDuctTerminalRemovalPlan::hasTopology(terminal)) {
        result->externalTopology = detail::AirLoopHVAC_Impl::SingleDuctTerminalRemovalPlan::prepare(terminal);
        if (!result->externalTopology) {
          return nullptr;
        }
      }

      if (result->coolingCoil) {
        const auto inlet = existingNodeField(*result->coolingCoil, result->coolingCoil->inletPort());
        const auto outlet = existingNodeField(*result->coolingCoil, result->coolingCoil->outletPort());
        if ((inlet.set || outlet.set) && (!inlet.node || !outlet.node)) {
          return nullptr;
        }
      }

      if (result->heatingCoil) {
        const auto inlet = existingNodeField(*result->heatingCoil, result->heatingCoil->inletPort());
        const auto outlet = existingNodeField(*result->heatingCoil, result->heatingCoil->outletPort());
        if ((inlet.set || outlet.set) && (!inlet.node || !outlet.node)) {
          return nullptr;
        }
      }

      return result;
    }

  }  // namespace

  AirTerminalSingleDuctConstantVolumeFourPipeBeam::AirTerminalSingleDuctConstantVolumeFourPipeBeam(const Model& model)
    : StraightComponent(AirTerminalSingleDuctConstantVolumeFourPipeBeam::iddObjectType(), model) {
    auto impl = getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl>();
    OS_ASSERT(impl);
    detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
    impl->canonicalize(context);

    if (!name()) {
      createName();
    }

    auto alwaysOn = model.alwaysOnDiscreteSchedule();
    OS_ASSERT(setPrimaryAirAvailabilitySchedule(alwaysOn));
    OS_ASSERT(setCoolingAvailabilitySchedule(alwaysOn));
    OS_ASSERT(setHeatingAvailabilitySchedule(alwaysOn));

    applyConstructorDefaults(*this);
  }

  AirTerminalSingleDuctConstantVolumeFourPipeBeam::AirTerminalSingleDuctConstantVolumeFourPipeBeam(const Model& model, HVACComponent& coolingCoil,
                                                                                                   HVACComponent& heatingCoil)
    : StraightComponent(AirTerminalSingleDuctConstantVolumeFourPipeBeam::iddObjectType(), model) {
    auto impl = getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl>();
    OS_ASSERT(impl);
    detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
    impl->canonicalize(context);

    if (!name()) {
      createName();
    }

    auto alwaysOn = model.alwaysOnDiscreteSchedule();
    OS_ASSERT(setPrimaryAirAvailabilitySchedule(alwaysOn));
    OS_ASSERT(setCoolingAvailabilitySchedule(alwaysOn));
    OS_ASSERT(setHeatingAvailabilitySchedule(alwaysOn));
    applyConstructorDefaults(*this);

    if (!setCoolingCoil(coolingCoil)) {
      remove();
      LOG_FREE_AND_THROW("openstudio.epmodel.AirTerminalSingleDuctConstantVolumeFourPipeBeam",
                         "Cannot set the cooling coil, make sure you use OS_Coil_Cooling_FourPipeBeam");
    }
    if (!setHeatingCoil(heatingCoil)) {
      remove();
      LOG_FREE_AND_THROW("openstudio.epmodel.AirTerminalSingleDuctConstantVolumeFourPipeBeam",
                         "Cannot set the heating coil, make sure you use OS_Coil_Heating_FourPipeBeam");
    }
  }

  AirTerminalSingleDuctConstantVolumeFourPipeBeam::AirTerminalSingleDuctConstantVolumeFourPipeBeam(
    std::shared_ptr<detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl> impl)
    : StraightComponent(std::move(impl)) {}

  IddObjectType AirTerminalSingleDuctConstantVolumeFourPipeBeam::iddObjectType() {
    return IddObjectType::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeam;
  }

  bool AirTerminalSingleDuctConstantVolumeFourPipeBeam::addToNode(Node& node) {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl>()->addToNode(node);
  }

  Schedule AirTerminalSingleDuctConstantVolumeFourPipeBeam::primaryAirAvailabilitySchedule() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl>()->primaryAirAvailabilitySchedule();
  }

  bool AirTerminalSingleDuctConstantVolumeFourPipeBeam::setPrimaryAirAvailabilitySchedule(Schedule& schedule) {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl>()->setPrimaryAirAvailabilitySchedule(schedule);
  }

  Schedule AirTerminalSingleDuctConstantVolumeFourPipeBeam::coolingAvailabilitySchedule() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl>()->coolingAvailabilitySchedule();
  }

  bool AirTerminalSingleDuctConstantVolumeFourPipeBeam::setCoolingAvailabilitySchedule(Schedule& schedule) {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl>()->setCoolingAvailabilitySchedule(schedule);
  }

  Schedule AirTerminalSingleDuctConstantVolumeFourPipeBeam::heatingAvailabilitySchedule() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl>()->heatingAvailabilitySchedule();
  }

  bool AirTerminalSingleDuctConstantVolumeFourPipeBeam::setHeatingAvailabilitySchedule(Schedule& schedule) {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl>()->setHeatingAvailabilitySchedule(schedule);
  }

  boost::optional<Node> AirTerminalSingleDuctConstantVolumeFourPipeBeam::primaryAirInletNode() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl>()->primaryAirInletNode();
  }

  boost::optional<Node> AirTerminalSingleDuctConstantVolumeFourPipeBeam::primaryAirOutletNode() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl>()->primaryAirOutletNode();
  }

  boost::optional<HVACComponent> AirTerminalSingleDuctConstantVolumeFourPipeBeam::coolingCoil() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl>()->coolingCoil();
  }

  bool AirTerminalSingleDuctConstantVolumeFourPipeBeam::setCoolingCoil(const HVACComponent& coolingCoil) {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl>()->setCoolingCoil(coolingCoil);
  }

  boost::optional<HVACComponent> AirTerminalSingleDuctConstantVolumeFourPipeBeam::heatingCoil() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl>()->heatingCoil();
  }

  bool AirTerminalSingleDuctConstantVolumeFourPipeBeam::setHeatingCoil(const HVACComponent& heatingCoil) {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl>()->setHeatingCoil(heatingCoil);
  }

  boost::optional<double> AirTerminalSingleDuctConstantVolumeFourPipeBeam::designPrimaryAirVolumeFlowRate() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl>()->designPrimaryAirVolumeFlowRate();
  }

  bool AirTerminalSingleDuctConstantVolumeFourPipeBeam::isDesignPrimaryAirVolumeFlowRateAutosized() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl>()->isDesignPrimaryAirVolumeFlowRateAutosized();
  }

  bool AirTerminalSingleDuctConstantVolumeFourPipeBeam::setDesignPrimaryAirVolumeFlowRate(double designPrimaryAirVolumeFlowRate) {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl>()->setDesignPrimaryAirVolumeFlowRate(designPrimaryAirVolumeFlowRate);
  }

  void AirTerminalSingleDuctConstantVolumeFourPipeBeam::autosizeDesignPrimaryAirVolumeFlowRate() {
    getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl>()->autosizeDesignPrimaryAirVolumeFlowRate();
  }

  boost::optional<double> AirTerminalSingleDuctConstantVolumeFourPipeBeam::designChilledWaterVolumeFlowRate() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl>()->designChilledWaterVolumeFlowRate();
  }

  bool AirTerminalSingleDuctConstantVolumeFourPipeBeam::isDesignChilledWaterVolumeFlowRateAutosized() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl>()->isDesignChilledWaterVolumeFlowRateAutosized();
  }

  bool AirTerminalSingleDuctConstantVolumeFourPipeBeam::setDesignChilledWaterVolumeFlowRate(double designChilledWaterVolumeFlowRate) {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl>()->setDesignChilledWaterVolumeFlowRate(
      designChilledWaterVolumeFlowRate);
  }

  void AirTerminalSingleDuctConstantVolumeFourPipeBeam::autosizeDesignChilledWaterVolumeFlowRate() {
    getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl>()->autosizeDesignChilledWaterVolumeFlowRate();
  }

  boost::optional<double> AirTerminalSingleDuctConstantVolumeFourPipeBeam::designHotWaterVolumeFlowRate() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl>()->designHotWaterVolumeFlowRate();
  }

  bool AirTerminalSingleDuctConstantVolumeFourPipeBeam::isDesignHotWaterVolumeFlowRateAutosized() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl>()->isDesignHotWaterVolumeFlowRateAutosized();
  }

  bool AirTerminalSingleDuctConstantVolumeFourPipeBeam::setDesignHotWaterVolumeFlowRate(double designHotWaterVolumeFlowRate) {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl>()->setDesignHotWaterVolumeFlowRate(designHotWaterVolumeFlowRate);
  }

  void AirTerminalSingleDuctConstantVolumeFourPipeBeam::autosizeDesignHotWaterVolumeFlowRate() {
    getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl>()->autosizeDesignHotWaterVolumeFlowRate();
  }

  boost::optional<double> AirTerminalSingleDuctConstantVolumeFourPipeBeam::zoneTotalBeamLength() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl>()->zoneTotalBeamLength();
  }

  bool AirTerminalSingleDuctConstantVolumeFourPipeBeam::isZoneTotalBeamLengthAutosized() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl>()->isZoneTotalBeamLengthAutosized();
  }

  bool AirTerminalSingleDuctConstantVolumeFourPipeBeam::setZoneTotalBeamLength(double zoneTotalBeamLength) {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl>()->setZoneTotalBeamLength(zoneTotalBeamLength);
  }

  void AirTerminalSingleDuctConstantVolumeFourPipeBeam::autosizeZoneTotalBeamLength() {
    getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl>()->autosizeZoneTotalBeamLength();
  }

  double AirTerminalSingleDuctConstantVolumeFourPipeBeam::ratedPrimaryAirFlowRateperBeamLength() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl>()->ratedPrimaryAirFlowRateperBeamLength();
  }

  bool AirTerminalSingleDuctConstantVolumeFourPipeBeam::isRatedPrimaryAirFlowRateperBeamLengthDefaulted() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl>()->isRatedPrimaryAirFlowRateperBeamLengthDefaulted();
  }

  bool AirTerminalSingleDuctConstantVolumeFourPipeBeam::setRatedPrimaryAirFlowRateperBeamLength(double ratedPrimaryAirFlowRateperBeamLength) {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl>()->setRatedPrimaryAirFlowRateperBeamLength(
      ratedPrimaryAirFlowRateperBeamLength);
  }

  void AirTerminalSingleDuctConstantVolumeFourPipeBeam::resetRatedPrimaryAirFlowRateperBeamLength() {
    getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl>()->resetRatedPrimaryAirFlowRateperBeamLength();
  }

  boost::optional<PlantLoop> AirTerminalSingleDuctConstantVolumeFourPipeBeam::chilledWaterPlantLoop() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl>()->chilledWaterPlantLoop();
  }

  boost::optional<Node> AirTerminalSingleDuctConstantVolumeFourPipeBeam::chilledWaterInletNode() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl>()->chilledWaterInletNode();
  }

  boost::optional<Node> AirTerminalSingleDuctConstantVolumeFourPipeBeam::chilledWaterOutletNode() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl>()->chilledWaterOutletNode();
  }

  boost::optional<PlantLoop> AirTerminalSingleDuctConstantVolumeFourPipeBeam::hotWaterPlantLoop() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl>()->hotWaterPlantLoop();
  }

  boost::optional<Node> AirTerminalSingleDuctConstantVolumeFourPipeBeam::hotWaterInletNode() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl>()->hotWaterInletNode();
  }

  boost::optional<Node> AirTerminalSingleDuctConstantVolumeFourPipeBeam::hotWaterOutletNode() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl>()->hotWaterOutletNode();
  }

  unsigned detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::inletPort() const {
    return openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::PrimaryAirInletNodeName;
  }

  unsigned detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::outletPort() const {
    return openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::PrimaryAirOutletNodeName;
  }

  bool detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::addToNode(Node& node) {
    if (node.model() != model()) {
      LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctConstantVolumeFourPipeBeam",
               "addToNode requires a node in the same model as the four-pipe beam.");
      return false;
    }

    auto thisObject = getObject<openstudio::epmodel::ModelObject>();
    auto terminal = thisObject.cast<StraightComponent>();
    auto plan = detail::AirLoopHVAC_Impl::SingleDuctTerminalInsertionPlan::prepare(terminal, node);
    if (!plan) {
      LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctConstantVolumeFourPipeBeam",
               "addToNode requires a terminal-free effective demand branch on the target AirLoopHVAC.");
      return false;
    }
    if (!plan->apply()) {
      return false;
    }
    plan->commit();
    return true;
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    boost::optional<ZoneHVACAirDistributionUnit> AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::zoneHVACAirDistributionUnit() const {
      auto terminal = getObject<openstudio::epmodel::ModelObject>();
      for (const auto& source : terminal.getSources(openstudio::IddObjectType::ZoneHVAC_AirDistributionUnit)) {
        if (auto adu = source.optionalCast<openstudio::epmodel::ZoneHVACAirDistributionUnit>()) {
          return adu;
        }
      }
      return boost::none;
    }

    std::vector<ModelObject> AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::children() const {
      std::vector<ModelObject> result;
      auto coolingCoil = getObject<ModelObject>().getModelObjectTarget<ModelObject>(
        openstudio::OS_AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::CoolingCoilName);
      if (coolingCoil) {
        result.push_back(*coolingCoil);
      }
      auto heatingCoil = getObject<ModelObject>().getModelObjectTarget<ModelObject>(
        openstudio::OS_AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::HeatingCoilName);
      if (heatingCoil) {
        result.push_back(*heatingCoil);
      }
      return result;
    }

    bool AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::isRemovable() const {
      if (!HVACComponent_Impl::isRemovable()) {
        return false;
      }
      const auto topologyPlans = prepareFourPipeBeamTopologyRemoval(getObject<ModelObject>());
      if (!topologyPlans) {
        return false;
      }

      unsigned coolingPlanCount = 0u;
      unsigned heatingPlanCount = 0u;
      boost::optional<Handle> coolingLoopHandle;
      boost::optional<Handle> heatingLoopHandle;
      const bool coolingPortsSet = topologyPlans->coolingCoil
                                   && (existingNodeField(*topologyPlans->coolingCoil, topologyPlans->coolingCoil->inletPort()).set
                                       || existingNodeField(*topologyPlans->coolingCoil, topologyPlans->coolingCoil->outletPort()).set);
      const bool heatingPortsSet = topologyPlans->heatingCoil
                                   && (existingNodeField(*topologyPlans->heatingCoil, topologyPlans->heatingCoil->inletPort()).set
                                       || existingNodeField(*topologyPlans->heatingCoil, topologyPlans->heatingCoil->outletPort()).set);
      for (const auto& plantLoop : model().getConcreteModelObjects<PlantLoop>()) {
        auto plantLoopImpl = plantLoop.getImpl<PlantLoop_Impl>();
        OS_ASSERT(plantLoopImpl);
        if (coolingPortsSet && topologyPlans->coolingCoil) {
          if (plantLoopImpl->prepareBeamCoilDemandBranchRemoval(*topologyPlans->coolingCoil)) {
            ++coolingPlanCount;
            coolingLoopHandle = plantLoop.handle();
          }
        }
        if (heatingPortsSet && topologyPlans->heatingCoil) {
          if (plantLoopImpl->prepareBeamCoilDemandBranchRemoval(*topologyPlans->heatingCoil)) {
            ++heatingPlanCount;
            heatingLoopHandle = plantLoop.handle();
          }
        }
      }

      if ((coolingPortsSet && coolingPlanCount != 1u) || (heatingPortsSet && heatingPlanCount != 1u)) {
        return false;
      }
      return !coolingLoopHandle || !heatingLoopHandle || *coolingLoopHandle != *heatingLoopHandle;
    }

    std::vector<openstudio::IdfObject> AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::remove() {
      if (!isRemovable()) {
        return {};
      }
      auto terminal = getObject<ModelObject>();
      auto thisModel = model();
      const auto terminalHandle = terminal.handle();
      const auto topologyPlans = prepareFourPipeBeamTopologyRemoval(terminal);
      if (!topologyPlans) {
        return {};
      }
      auto coolingCoil = topologyPlans->coolingCoil;
      auto heatingCoil = topologyPlans->heatingCoil;
      const bool coolingHasTopology =
        coolingCoil
        && (existingNodeField(*coolingCoil, coolingCoil->inletPort()).set || existingNodeField(*coolingCoil, coolingCoil->outletPort()).set);
      const bool heatingHasTopology =
        heatingCoil
        && (existingNodeField(*heatingCoil, heatingCoil->inletPort()).set || existingNodeField(*heatingCoil, heatingCoil->outletPort()).set);
      if ((topologyPlans->externalTopology || coolingHasTopology || heatingHasTopology) && !removeFromLoop()) {
        return {};
      }

      auto result = HVACComponent_Impl::remove();
      if (result.empty() || thisModel.getObject(terminalHandle)) {
        return {};
      }
      if (coolingCoil && thisModel.getObject(coolingCoil->handle())) {
        const auto removedCoil = coolingCoil->remove();
        result.insert(result.end(), removedCoil.begin(), removedCoil.end());
      }
      if (heatingCoil && thisModel.getObject(heatingCoil->handle())) {
        const auto removedCoil = heatingCoil->remove();
        result.insert(result.end(), removedCoil.begin(), removedCoil.end());
      }
      return result;
    }

    bool AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::removeFromLoop() {
      if (!HVACComponent_Impl::isRemovable()) {
        return false;
      }
      const auto topologyPlans = prepareFourPipeBeamTopologyRemoval(getObject<ModelObject>());
      if (!topologyPlans) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctConstantVolumeFourPipeBeam",
                 "Refusing to remove a four-pipe beam whose child, air, zone, ADU, plenum, or plant topology is not exact.");
        return false;
      }

      std::unique_ptr<PlantLoop_Impl::BeamCoilDemandBranchRemovalPlan> coolingPlantPlan;
      std::unique_ptr<PlantLoop_Impl::BeamCoilDemandBranchRemovalPlan> heatingPlantPlan;
      boost::optional<Handle> coolingLoopHandle;
      boost::optional<Handle> heatingLoopHandle;
      const bool coolingPortsSet = topologyPlans->coolingCoil
                                   && (existingNodeField(*topologyPlans->coolingCoil, topologyPlans->coolingCoil->inletPort()).set
                                       || existingNodeField(*topologyPlans->coolingCoil, topologyPlans->coolingCoil->outletPort()).set);
      const bool heatingPortsSet = topologyPlans->heatingCoil
                                   && (existingNodeField(*topologyPlans->heatingCoil, topologyPlans->heatingCoil->inletPort()).set
                                       || existingNodeField(*topologyPlans->heatingCoil, topologyPlans->heatingCoil->outletPort()).set);
      for (const auto& plantLoop : model().getConcreteModelObjects<PlantLoop>()) {
        auto plantLoopImpl = plantLoop.getImpl<PlantLoop_Impl>();
        OS_ASSERT(plantLoopImpl);
        if (coolingPortsSet && topologyPlans->coolingCoil) {
          if (auto candidate = plantLoopImpl->prepareBeamCoilDemandBranchRemoval(*topologyPlans->coolingCoil)) {
            if (coolingPlantPlan) {
              return false;
            }
            coolingPlantPlan = std::move(candidate);
            coolingLoopHandle = plantLoop.handle();
          }
        }
        if (heatingPortsSet && topologyPlans->heatingCoil) {
          if (auto candidate = plantLoopImpl->prepareBeamCoilDemandBranchRemoval(*topologyPlans->heatingCoil)) {
            if (heatingPlantPlan) {
              return false;
            }
            heatingPlantPlan = std::move(candidate);
            heatingLoopHandle = plantLoop.handle();
          }
        }
      }

      if ((coolingPortsSet && !coolingPlantPlan) || (heatingPortsSet && !heatingPlantPlan)
          || (coolingLoopHandle && heatingLoopHandle && *coolingLoopHandle == *heatingLoopHandle)) {
        return false;
      }
      if (!topologyPlans->externalTopology && !coolingPlantPlan && !heatingPlantPlan) {
        return false;
      }

      if (coolingPlantPlan) {
        coolingPlantPlan->commit();
      }
      if (heatingPlantPlan) {
        heatingPlantPlan->commit();
      }
      if (topologyPlans->externalTopology) {
        topologyPlans->externalTopology->commit();
      }
      return true;
    }

    Schedule AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::primaryAirAvailabilitySchedule() const {
      auto schedule = getObject<ModelObject>().getModelObjectTarget<Schedule>(
        openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::PrimaryAirAvailabilityScheduleName);
      if (!schedule) {
        LOG_FREE(Error, "openstudio.epmodel.AirTerminalSingleDuctConstantVolumeFourPipeBeam",
                 "Required primary air availability schedule not set, repairing persisted state with the model always-on discrete schedule");
        schedule = model().alwaysOnDiscreteSchedule();
        OS_ASSERT(schedule);
        const bool ok = const_cast<AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl*>(this)->setPrimaryAirAvailabilitySchedule(*schedule);
        OS_ASSERT(ok);
        schedule = getObject<ModelObject>().getModelObjectTarget<Schedule>(
          openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::PrimaryAirAvailabilityScheduleName);
      }
      OS_ASSERT(schedule);
      return *schedule;
    }

    bool AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::setPrimaryAirAvailabilitySchedule(Schedule& schedule) {
      return ModelObject_Impl::setSchedule(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::PrimaryAirAvailabilityScheduleName,
                                           "AirTerminalSingleDuctConstantVolumeFourPipeBeam", "Primary Air Availability", schedule);
    }

    Schedule AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::coolingAvailabilitySchedule() const {
      auto schedule = getObject<ModelObject>().getModelObjectTarget<Schedule>(
        openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::CoolingAvailabilityScheduleName);
      if (!schedule) {
        LOG_FREE(Error, "openstudio.epmodel.AirTerminalSingleDuctConstantVolumeFourPipeBeam",
                 "Required cooling availability schedule not set, repairing persisted state with the model always-on discrete schedule");
        schedule = model().alwaysOnDiscreteSchedule();
        OS_ASSERT(schedule);
        const bool ok = const_cast<AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl*>(this)->setCoolingAvailabilitySchedule(*schedule);
        OS_ASSERT(ok);
        schedule = getObject<ModelObject>().getModelObjectTarget<Schedule>(
          openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::CoolingAvailabilityScheduleName);
      }
      OS_ASSERT(schedule);
      return *schedule;
    }

    bool AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::setCoolingAvailabilitySchedule(Schedule& schedule) {
      return ModelObject_Impl::setSchedule(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::CoolingAvailabilityScheduleName,
                                           "AirTerminalSingleDuctConstantVolumeFourPipeBeam", "Cooling Availability", schedule);
    }

    Schedule AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::heatingAvailabilitySchedule() const {
      auto schedule = getObject<ModelObject>().getModelObjectTarget<Schedule>(
        openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::HeatingAvailabilityScheduleName);
      if (!schedule) {
        LOG_FREE(Error, "openstudio.epmodel.AirTerminalSingleDuctConstantVolumeFourPipeBeam",
                 "Required heating availability schedule not set, repairing persisted state with the model always-on discrete schedule");
        schedule = model().alwaysOnDiscreteSchedule();
        OS_ASSERT(schedule);
        const bool ok = const_cast<AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl*>(this)->setHeatingAvailabilitySchedule(*schedule);
        OS_ASSERT(ok);
        schedule = getObject<ModelObject>().getModelObjectTarget<Schedule>(
          openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::HeatingAvailabilityScheduleName);
      }
      OS_ASSERT(schedule);
      return *schedule;
    }

    bool AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::setHeatingAvailabilitySchedule(Schedule& schedule) {
      return ModelObject_Impl::setSchedule(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::HeatingAvailabilityScheduleName,
                                           "AirTerminalSingleDuctConstantVolumeFourPipeBeam", "Heating Availability", schedule);
    }

    boost::optional<Node> AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::primaryAirInletNode() const {
      const auto inlet = inletModelObject();
      return inlet ? inlet->optionalCast<Node>() : boost::none;
    }

    boost::optional<Node> AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::primaryAirOutletNode() const {
      const auto outlet = outletModelObject();
      return outlet ? outlet->optionalCast<Node>() : boost::none;
    }

    boost::optional<HVACComponent> AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::coolingCoil() const {
      return getObject<ModelObject>().getModelObjectTarget<HVACComponent>(
        openstudio::OS_AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::CoolingCoilName);
    }

    bool AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::setCoolingCoil(const HVACComponent& coolingCoil) {
      if (coolingCoil.model() != model()) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctConstantVolumeFourPipeBeam",
                 "Unsupported cooling coil from a different model for AirTerminalSingleDuctConstantVolumeFourPipeBeam.");
        return false;
      }
      if (coolingCoil.iddObject().type() != IddObjectType::OS_Coil_Cooling_FourPipeBeam) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctConstantVolumeFourPipeBeam",
                 "Unsupported cooling coil type '" << coolingCoil.iddObject().name() << "' for AirTerminalSingleDuctConstantVolumeFourPipeBeam.");
        return false;
      }
      auto terminal = getObject<ModelObject>();
      const auto previousCoil =
        terminal.getModelObjectTarget<HVACComponent>(openstudio::OS_AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::CoolingCoilName);
      if (previousCoil && previousCoil->handle() == coolingCoil.handle()) {
        return true;
      }
      if (const auto owner = coolingCoil.containingHVACComponent(); owner && owner->handle() != terminal.handle()) {
        return false;
      }
      return setPointer(openstudio::OS_AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::CoolingCoilName, coolingCoil.handle(), false);
    }

    boost::optional<HVACComponent> AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::heatingCoil() const {
      return getObject<ModelObject>().getModelObjectTarget<HVACComponent>(
        openstudio::OS_AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::HeatingCoilName);
    }

    bool AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::setHeatingCoil(const HVACComponent& heatingCoil) {
      if (heatingCoil.model() != model()) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctConstantVolumeFourPipeBeam",
                 "Unsupported heating coil from a different model for AirTerminalSingleDuctConstantVolumeFourPipeBeam.");
        return false;
      }
      if (heatingCoil.iddObject().type() != IddObjectType::OS_Coil_Heating_FourPipeBeam) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctConstantVolumeFourPipeBeam",
                 "Unsupported heating coil type '" << heatingCoil.iddObject().name() << "' for AirTerminalSingleDuctConstantVolumeFourPipeBeam.");
        return false;
      }
      auto terminal = getObject<ModelObject>();
      const auto previousCoil =
        terminal.getModelObjectTarget<HVACComponent>(openstudio::OS_AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::HeatingCoilName);
      if (previousCoil && previousCoil->handle() == heatingCoil.handle()) {
        return true;
      }
      if (const auto owner = heatingCoil.containingHVACComponent(); owner && owner->handle() != terminal.handle()) {
        return false;
      }
      return setPointer(openstudio::OS_AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::HeatingCoilName, heatingCoil.handle(), false);
    }

    boost::optional<double> AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::designPrimaryAirVolumeFlowRate() const {
      return getDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::DesignPrimaryAirVolumeFlowRate, true);
    }

    bool AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::isDesignPrimaryAirVolumeFlowRateAutosized() const {
      if (auto value = getString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::DesignPrimaryAirVolumeFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::setDesignPrimaryAirVolumeFlowRate(double designPrimaryAirVolumeFlowRate) {
      return setDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::DesignPrimaryAirVolumeFlowRate,
                       designPrimaryAirVolumeFlowRate);
    }

    void AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::autosizeDesignPrimaryAirVolumeFlowRate() {
      OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::DesignPrimaryAirVolumeFlowRate, "autosize"));
    }

    boost::optional<double> AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::designChilledWaterVolumeFlowRate() const {
      return getDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::DesignChilledWaterVolumeFlowRate, true);
    }

    bool AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::isDesignChilledWaterVolumeFlowRateAutosized() const {
      if (auto value = getString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::DesignChilledWaterVolumeFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::setDesignChilledWaterVolumeFlowRate(double designChilledWaterVolumeFlowRate) {
      return setDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::DesignChilledWaterVolumeFlowRate,
                       designChilledWaterVolumeFlowRate);
    }

    void AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::autosizeDesignChilledWaterVolumeFlowRate() {
      OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::DesignChilledWaterVolumeFlowRate, "autosize"));
    }

    boost::optional<double> AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::designHotWaterVolumeFlowRate() const {
      return getDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::DesignHotWaterVolumeFlowRate, true);
    }

    bool AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::isDesignHotWaterVolumeFlowRateAutosized() const {
      if (auto value = getString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::DesignHotWaterVolumeFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::setDesignHotWaterVolumeFlowRate(double designHotWaterVolumeFlowRate) {
      return setDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::DesignHotWaterVolumeFlowRate,
                       designHotWaterVolumeFlowRate);
    }

    void AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::autosizeDesignHotWaterVolumeFlowRate() {
      OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::DesignHotWaterVolumeFlowRate, "autosize"));
    }

    boost::optional<double> AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::zoneTotalBeamLength() const {
      return getDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::ZoneTotalBeamLength, true);
    }

    bool AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::isZoneTotalBeamLengthAutosized() const {
      if (auto value = getString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::ZoneTotalBeamLength, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::setZoneTotalBeamLength(double zoneTotalBeamLength) {
      return setDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::ZoneTotalBeamLength, zoneTotalBeamLength);
    }

    void AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::autosizeZoneTotalBeamLength() {
      OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::ZoneTotalBeamLength, "autosize"));
    }

    double AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::ratedPrimaryAirFlowRateperBeamLength() const {
      const auto value = getDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::RatedPrimaryAirFlowRateperBeamLength, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::isRatedPrimaryAirFlowRateperBeamLengthDefaulted() const {
      return isEmpty(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::RatedPrimaryAirFlowRateperBeamLength);
    }

    bool AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::setRatedPrimaryAirFlowRateperBeamLength(double ratedPrimaryAirFlowRateperBeamLength) {
      return setDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::RatedPrimaryAirFlowRateperBeamLength,
                       ratedPrimaryAirFlowRateperBeamLength);
    }

    void AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::resetRatedPrimaryAirFlowRateperBeamLength() {
      OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::RatedPrimaryAirFlowRateperBeamLength, ""));
    }

    boost::optional<PlantLoop> AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::chilledWaterPlantLoop() const {
      const auto coil = coolingCoil();
      return coil ? coil->plantLoop() : boost::none;
    }

    boost::optional<Node> AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::chilledWaterInletNode() const {
      const auto coil = coolingCoil();
      if (!coil) {
        return boost::none;
      }
      const auto straightCoil = coil->optionalCast<StraightComponent>();
      if (!straightCoil) {
        return boost::none;
      }
      const auto inlet = straightCoil->inletModelObject();
      return inlet ? inlet->optionalCast<Node>() : boost::none;
    }

    boost::optional<Node> AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::chilledWaterOutletNode() const {
      const auto coil = coolingCoil();
      if (!coil) {
        return boost::none;
      }
      const auto straightCoil = coil->optionalCast<StraightComponent>();
      if (!straightCoil) {
        return boost::none;
      }
      const auto outlet = straightCoil->outletModelObject();
      return outlet ? outlet->optionalCast<Node>() : boost::none;
    }

    boost::optional<PlantLoop> AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::hotWaterPlantLoop() const {
      const auto coil = heatingCoil();
      return coil ? coil->plantLoop() : boost::none;
    }

    boost::optional<Node> AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::hotWaterInletNode() const {
      const auto coil = heatingCoil();
      if (!coil) {
        return boost::none;
      }
      const auto straightCoil = coil->optionalCast<StraightComponent>();
      if (!straightCoil) {
        return boost::none;
      }
      const auto inlet = straightCoil->inletModelObject();
      return inlet ? inlet->optionalCast<Node>() : boost::none;
    }

    boost::optional<Node> AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::hotWaterOutletNode() const {
      const auto coil = heatingCoil();
      if (!coil) {
        return boost::none;
      }
      const auto straightCoil = coil->optionalCast<StraightComponent>();
      if (!straightCoil) {
        return boost::none;
      }
      const auto outlet = straightCoil->outletModelObject();
      return outlet ? outlet->optionalCast<Node>() : boost::none;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
