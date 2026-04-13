/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "Loop/PlantLoop.hpp"
#include "Loop/PlantLoop_Impl.hpp"

#include "Model.hpp"
#include "AvailabilityManager/AvailabilityManager.hpp"
#include "PlantEquipmentOperationScheme/PlantEquipmentOperationScheme.hpp"
#include "ModelObject/AvailabilityManagerAssignmentList.hpp"
#include "ModelObject/AvailabilityManagerAssignmentList_Impl.hpp"
#include "ModelObject/PlantEquipmentOperationSchemes.hpp"
#include "ModelObject/PlantEquipmentOperationSchemes_Impl.hpp"
#include "ModelObject/SizingPlant.hpp"
#include "ModelObject/SizingPlant_Impl.hpp"
#include "PlantEquipmentOperationScheme/PlantEquipmentOperationCoolingLoad.hpp"
#include "PlantEquipmentOperationScheme/PlantEquipmentOperationHeatingLoad.hpp"
#include "Schedule/Schedule.hpp"
#include "StraightComponent/Node.hpp"
#include "ModelObject/Branch.hpp"
#include "ModelObject/Branch_Impl.hpp"
#include "ModelObject/BranchList.hpp"
#include "ModelObject/BranchList_Impl.hpp"
#include "Mixer/ConnectorMixer.hpp"
#include "Mixer/ConnectorMixer_Impl.hpp"
#include "HVACComponent/HVACComponent.hpp"
#include "ModelObject.hpp"
#include "Splitter/Splitter.hpp"
#include "Splitter/ConnectorSplitter.hpp"
#include "Splitter/ConnectorSplitter_Impl.hpp"
#include "WaterToAirComponent/CoilCoolingWater.hpp"
#include "WaterToAirComponent/CoilCoolingWater_Impl.hpp"
#include "WaterToAirComponent/CoilHeatingWater.hpp"
#include "WaterToAirComponent/CoilHeatingWater_Impl.hpp"
#include "StraightComponent/StraightComponent.hpp"
#include "StraightComponent/CoilCoolingLowTempRadiantConstFlow.hpp"
#include "StraightComponent/CoilCoolingLowTempRadiantConstFlow_Impl.hpp"
#include "StraightComponent/CoilCoolingLowTempRadiantVarFlow.hpp"
#include "StraightComponent/CoilCoolingLowTempRadiantVarFlow_Impl.hpp"
#include "StraightComponent/CoilCoolingWaterPanelRadiant.hpp"
#include "StraightComponent/CoilCoolingWaterPanelRadiant_Impl.hpp"
#include "StraightComponent/CoilHeatingLowTempRadiantConstFlow.hpp"
#include "StraightComponent/CoilHeatingWaterBaseboardRadiant.hpp"
#include "StraightComponent/CoilHeatingLowTempRadiantConstFlow_Impl.hpp"
#include "StraightComponent/CoilHeatingWaterBaseboardRadiant_Impl.hpp"
#include "StraightComponent/CoilHeatingLowTempRadiantVarFlow.hpp"
#include "StraightComponent/CoilHeatingLowTempRadiantVarFlow_Impl.hpp"
#include "WaterToWaterComponent/WaterToWaterComponent.hpp"
#include "WaterToWaterComponent/WaterToWaterComponent_Impl.hpp"
#include "ZoneHVACComponent/ZoneHVACCoolingPanelRadiantConvectiveWater.hpp"
#include "ZoneHVACComponent/ZoneHVACCoolingPanelRadiantConvectiveWater_Impl.hpp"
#include "ZoneHVACComponent/ZoneHVACLowTempRadiantConstFlow.hpp"
#include "ZoneHVACComponent/ZoneHVACBaseboardRadiantConvectiveWater.hpp"
#include "ZoneHVACComponent/ZoneHVACBaseboardRadiantConvectiveWater_Impl.hpp"
#include "ZoneHVACComponent/ZoneHVACLowTempRadiantConstFlow_Impl.hpp"
#include "ZoneHVACComponent/ZoneHVACLowTempRadiantVarFlow.hpp"
#include "ZoneHVACComponent/ZoneHVACLowTempRadiantVarFlow_Impl.hpp"

#include <algorithm>
#include <set>

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/OS_PlantLoop_FieldEnums.hxx>
#include <utilities/idd/PlantLoop_FieldEnums.hxx>
#include <utilities/idd/Sizing_Plant_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  PlantLoop::PlantLoop(const Model& model) : Loop(PlantLoop::iddObjectType(), model) {
    detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
    getImpl<detail::PlantLoop_Impl>()->canonicalize(context);
  }

  PlantLoop::PlantLoop(std::shared_ptr<detail::PlantLoop_Impl> impl) : Loop(std::move(impl)) {}

  IddObjectType PlantLoop::iddObjectType() {
    return IddObjectType::PlantLoop;
  }

  std::string PlantLoop::loadDistributionScheme() const {
    return getImpl<detail::PlantLoop_Impl>()->loadDistributionScheme();
  }

  bool PlantLoop::setLoadDistributionScheme(const std::string& scheme) {
    return getImpl<detail::PlantLoop_Impl>()->setLoadDistributionScheme(scheme);
  }

  std::string PlantLoop::fluidType() const {
    return getImpl<detail::PlantLoop_Impl>()->fluidType();
  }

  bool PlantLoop::setFluidType(const std::string& value) {
    return getImpl<detail::PlantLoop_Impl>()->setFluidType(value);
  }

  int PlantLoop::glycolConcentration() const {
    return getImpl<detail::PlantLoop_Impl>()->glycolConcentration();
  }

  bool PlantLoop::setGlycolConcentration(int glycolConcentration) {
    return getImpl<detail::PlantLoop_Impl>()->setGlycolConcentration(glycolConcentration);
  }

  double PlantLoop::maximumLoopTemperature() const {
    return getImpl<detail::PlantLoop_Impl>()->maximumLoopTemperature();
  }

  bool PlantLoop::setMaximumLoopTemperature(double value) {
    return getImpl<detail::PlantLoop_Impl>()->setMaximumLoopTemperature(value);
  }

  double PlantLoop::minimumLoopTemperature() const {
    return getImpl<detail::PlantLoop_Impl>()->minimumLoopTemperature();
  }

  bool PlantLoop::setMinimumLoopTemperature(double value) {
    return getImpl<detail::PlantLoop_Impl>()->setMinimumLoopTemperature(value);
  }

  boost::optional<double> PlantLoop::maximumLoopFlowRate() const {
    return getImpl<detail::PlantLoop_Impl>()->maximumLoopFlowRate();
  }

  bool PlantLoop::setMaximumLoopFlowRate(double value) {
    return getImpl<detail::PlantLoop_Impl>()->setMaximumLoopFlowRate(value);
  }

  bool PlantLoop::isMaximumLoopFlowRateAutosized() const {
    return getImpl<detail::PlantLoop_Impl>()->isMaximumLoopFlowRateAutosized();
  }

  void PlantLoop::autosizeMaximumLoopFlowRate() {
    getImpl<detail::PlantLoop_Impl>()->autosizeMaximumLoopFlowRate();
  }

  boost::optional<double> PlantLoop::minimumLoopFlowRate() const {
    return getImpl<detail::PlantLoop_Impl>()->minimumLoopFlowRate();
  }

  bool PlantLoop::setMinimumLoopFlowRate(double value) {
    return getImpl<detail::PlantLoop_Impl>()->setMinimumLoopFlowRate(value);
  }

  bool PlantLoop::isMinimumLoopFlowRateAutosized() const {
    return getImpl<detail::PlantLoop_Impl>()->isMinimumLoopFlowRateAutosized();
  }

  void PlantLoop::autosizeMinimumLoopFlowRate() {
    getImpl<detail::PlantLoop_Impl>()->autosizeMinimumLoopFlowRate();
  }

  boost::optional<double> PlantLoop::plantLoopVolume() const {
    return getImpl<detail::PlantLoop_Impl>()->plantLoopVolume();
  }

  bool PlantLoop::setPlantLoopVolume(double value) {
    return getImpl<detail::PlantLoop_Impl>()->setPlantLoopVolume(value);
  }

  bool PlantLoop::isPlantLoopVolumeAutocalculated() const {
    return getImpl<detail::PlantLoop_Impl>()->isPlantLoopVolumeAutocalculated();
  }

  void PlantLoop::autocalculatePlantLoopVolume() {
    getImpl<detail::PlantLoop_Impl>()->autocalculatePlantLoopVolume();
  }

  std::string PlantLoop::commonPipeSimulation() const {
    return getImpl<detail::PlantLoop_Impl>()->commonPipeSimulation();
  }

  bool PlantLoop::isCommonPipeSimulationDefaulted() const {
    return getImpl<detail::PlantLoop_Impl>()->isCommonPipeSimulationDefaulted();
  }

  bool PlantLoop::setCommonPipeSimulation(const std::string& value) {
    return getImpl<detail::PlantLoop_Impl>()->setCommonPipeSimulation(value);
  }

  void PlantLoop::resetCommonPipeSimulation() {
    getImpl<detail::PlantLoop_Impl>()->resetCommonPipeSimulation();
  }

  Node PlantLoop::loopTemperatureSetpointNode() {
    return getImpl<detail::PlantLoop_Impl>()->loopTemperatureSetpointNode();
  }

  bool PlantLoop::setLoopTemperatureSetpointNode(Node& node) {
    return getImpl<detail::PlantLoop_Impl>()->setLoopTemperatureSetpointNode(node);
  }

  boost::optional<PlantEquipmentOperationHeatingLoad> PlantLoop::plantEquipmentOperationHeatingLoad() const {
    return getImpl<detail::PlantLoop_Impl>()->plantEquipmentOperationHeatingLoad();
  }

  bool PlantLoop::setPlantEquipmentOperationHeatingLoad(const PlantEquipmentOperationHeatingLoad& plantOperation) {
    return getImpl<detail::PlantLoop_Impl>()->setPlantEquipmentOperationHeatingLoad(plantOperation);
  }

  void PlantLoop::resetPlantEquipmentOperationHeatingLoad() {
    getImpl<detail::PlantLoop_Impl>()->resetPlantEquipmentOperationHeatingLoad();
  }

  bool PlantLoop::setPlantEquipmentOperationHeatingLoadSchedule(Schedule& schedule) {
    return getImpl<detail::PlantLoop_Impl>()->setPlantEquipmentOperationHeatingLoadSchedule(schedule);
  }

  void PlantLoop::resetPlantEquipmentOperationHeatingLoadSchedule() {
    getImpl<detail::PlantLoop_Impl>()->resetPlantEquipmentOperationHeatingLoadSchedule();
  }

  boost::optional<Schedule> PlantLoop::plantEquipmentOperationHeatingLoadSchedule() const {
    return getImpl<detail::PlantLoop_Impl>()->plantEquipmentOperationHeatingLoadSchedule();
  }

  boost::optional<PlantEquipmentOperationCoolingLoad> PlantLoop::plantEquipmentOperationCoolingLoad() const {
    return getImpl<detail::PlantLoop_Impl>()->plantEquipmentOperationCoolingLoad();
  }

  bool PlantLoop::setPlantEquipmentOperationCoolingLoad(const PlantEquipmentOperationCoolingLoad& plantOperation) {
    return getImpl<detail::PlantLoop_Impl>()->setPlantEquipmentOperationCoolingLoad(plantOperation);
  }

  void PlantLoop::resetPlantEquipmentOperationCoolingLoad() {
    getImpl<detail::PlantLoop_Impl>()->resetPlantEquipmentOperationCoolingLoad();
  }

  bool PlantLoop::setPlantEquipmentOperationCoolingLoadSchedule(Schedule& schedule) {
    return getImpl<detail::PlantLoop_Impl>()->setPlantEquipmentOperationCoolingLoadSchedule(schedule);
  }

  boost::optional<Schedule> PlantLoop::plantEquipmentOperationCoolingLoadSchedule() const {
    return getImpl<detail::PlantLoop_Impl>()->plantEquipmentOperationCoolingLoadSchedule();
  }

  void PlantLoop::resetPlantEquipmentOperationCoolingLoadSchedule() {
    getImpl<detail::PlantLoop_Impl>()->resetPlantEquipmentOperationCoolingLoadSchedule();
  }

  boost::optional<PlantEquipmentOperationScheme> PlantLoop::primaryPlantEquipmentOperationScheme() const {
    return getImpl<detail::PlantLoop_Impl>()->primaryPlantEquipmentOperationScheme();
  }

  bool PlantLoop::setPrimaryPlantEquipmentOperationScheme(const PlantEquipmentOperationScheme& plantOperation) {
    return getImpl<detail::PlantLoop_Impl>()->setPrimaryPlantEquipmentOperationScheme(plantOperation);
  }

  void PlantLoop::resetPrimaryPlantEquipmentOperationScheme() {
    getImpl<detail::PlantLoop_Impl>()->resetPrimaryPlantEquipmentOperationScheme();
  }

  bool PlantLoop::setPrimaryPlantEquipmentOperationSchemeSchedule(Schedule& schedule) {
    return getImpl<detail::PlantLoop_Impl>()->setPrimaryPlantEquipmentOperationSchemeSchedule(schedule);
  }

  void PlantLoop::resetPrimaryPlantEquipmentOperationSchemeSchedule() {
    getImpl<detail::PlantLoop_Impl>()->resetPrimaryPlantEquipmentOperationSchemeSchedule();
  }

  boost::optional<Schedule> PlantLoop::primaryPlantEquipmentOperationSchemeSchedule() const {
    return getImpl<detail::PlantLoop_Impl>()->primaryPlantEquipmentOperationSchemeSchedule();
  }

  bool PlantLoop::setComponentSetpointOperationSchemeSchedule(Schedule& schedule) {
    return getImpl<detail::PlantLoop_Impl>()->setComponentSetpointOperationSchemeSchedule(schedule);
  }

  void PlantLoop::resetComponentSetpointOperationSchemeSchedule() {
    getImpl<detail::PlantLoop_Impl>()->resetComponentSetpointOperationSchemeSchedule();
  }

  boost::optional<Schedule> PlantLoop::componentSetpointOperationSchemeSchedule() const {
    return getImpl<detail::PlantLoop_Impl>()->componentSetpointOperationSchemeSchedule();
  }

  Node PlantLoop::supplyInletNode() const {
    return getImpl<detail::PlantLoop_Impl>()->supplyInletNode();
  }

  Node PlantLoop::supplyOutletNode() const {
    return getImpl<detail::PlantLoop_Impl>()->supplyOutletNode();
  }

  std::vector<Node> PlantLoop::supplyOutletNodes() const {
    return getImpl<detail::PlantLoop_Impl>()->supplyOutletNodes();
  }

  Node PlantLoop::demandInletNode() const {
    return getImpl<detail::PlantLoop_Impl>()->demandInletNode();
  }

  std::vector<Node> PlantLoop::demandInletNodes() const {
    return getImpl<detail::PlantLoop_Impl>()->demandInletNodes();
  }

  Node PlantLoop::demandOutletNode() const {
    return getImpl<detail::PlantLoop_Impl>()->demandOutletNode();
  }

  Mixer PlantLoop::supplyMixer() const {
    return getImpl<detail::PlantLoop_Impl>()->supplyMixer();
  }

  Splitter PlantLoop::supplySplitter() const {
    return getImpl<detail::PlantLoop_Impl>()->supplySplitter();
  }

  Mixer PlantLoop::demandMixer() {
    return getImpl<detail::PlantLoop_Impl>()->demandMixer();
  }

  Splitter PlantLoop::demandSplitter() {
    return getImpl<detail::PlantLoop_Impl>()->demandSplitter();
  }

  std::vector<ModelObject> PlantLoop::supplyComponents(const HVACComponent& inletComp, const HVACComponent& outletComp,
                                                       openstudio::IddObjectType type) const {
    return getImpl<detail::PlantLoop_Impl>()->supplyComponents(inletComp, outletComp, type);
  }

  std::vector<ModelObject> PlantLoop::supplyComponents(openstudio::IddObjectType type) const {
    return getImpl<detail::PlantLoop_Impl>()->supplyComponents(type);
  }

  std::vector<ModelObject> PlantLoop::demandComponents(const HVACComponent& inletComp, const HVACComponent& outletComp,
                                                       openstudio::IddObjectType type) const {
    return getImpl<detail::PlantLoop_Impl>()->demandComponents(inletComp, outletComp, type);
  }

  std::vector<ModelObject> PlantLoop::demandComponents(openstudio::IddObjectType type) const {
    return getImpl<detail::PlantLoop_Impl>()->demandComponents(type);
  }

  bool PlantLoop::addSupplyBranchForComponent(HVACComponent hvacComponent) {
    return getImpl<detail::PlantLoop_Impl>()->addSupplyBranchForComponent(hvacComponent);
  }

  bool PlantLoop::removeSupplyBranchWithComponent(HVACComponent hvacComponent) {
    return getImpl<detail::PlantLoop_Impl>()->removeSupplyBranchWithComponent(hvacComponent);
  }

  bool PlantLoop::addDemandBranchForComponent(HVACComponent hvacComponent, bool tertiary) {
    return getImpl<detail::PlantLoop_Impl>()->addDemandBranchForComponent(hvacComponent, tertiary);
  }

  bool PlantLoop::removeDemandBranchWithComponent(HVACComponent hvacComponent) {
    return getImpl<detail::PlantLoop_Impl>()->removeDemandBranchWithComponent(hvacComponent);
  }

  SizingPlant PlantLoop::sizingPlant() const {
    return getImpl<detail::PlantLoop_Impl>()->sizingPlant();
  }

  std::vector<AvailabilityManager> PlantLoop::availabilityManagers() const {
    return getImpl<detail::PlantLoop_Impl>()->availabilityManagers();
  }

  bool PlantLoop::addAvailabilityManager(const AvailabilityManager& availabilityManager) {
    return getImpl<detail::PlantLoop_Impl>()->addAvailabilityManager(availabilityManager);
  }

  bool PlantLoop::addAvailabilityManager(const AvailabilityManager& availabilityManager, unsigned priority) {
    return getImpl<detail::PlantLoop_Impl>()->addAvailabilityManager(availabilityManager, priority);
  }

  bool PlantLoop::setAvailabilityManagers(const std::vector<AvailabilityManager>& availabilityManagers) {
    return getImpl<detail::PlantLoop_Impl>()->setAvailabilityManagers(availabilityManagers);
  }

  void PlantLoop::resetAvailabilityManagers() {
    getImpl<detail::PlantLoop_Impl>()->resetAvailabilityManagers();
  }

  bool PlantLoop::removeAvailabilityManager(const AvailabilityManager& availabilityManager) {
    return getImpl<detail::PlantLoop_Impl>()->removeAvailabilityManager(availabilityManager);
  }

  bool PlantLoop::removeAvailabilityManager(unsigned priority) {
    return getImpl<detail::PlantLoop_Impl>()->removeAvailabilityManager(priority);
  }

  bool PlantLoop::setAvailabilityManagerPriority(const AvailabilityManager& availabilityManager, unsigned priority) {
    return getImpl<detail::PlantLoop_Impl>()->setAvailabilityManagerPriority(availabilityManager, priority);
  }

  unsigned PlantLoop::availabilityManagerPriority(const AvailabilityManager& availabilityManager) const {
    return getImpl<detail::PlantLoop_Impl>()->availabilityManagerPriority(availabilityManager);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

    namespace {

      // PlantLoop still stores branch topology in the raw EnergyPlus branch
      // objects, so a number of small local helpers are needed to answer
      // higher-level OpenStudio questions without promoting them into broader
      // reusable APIs prematurely. Keep these helpers file-local unless and
      // until the same behavior is needed in more than one loop
      // implementation.
      bool branchContainsNode(Model model, const Branch& branch, const Node& node, const Node& inletNode, const Node& outletNode,
                              bool isInletBranch, bool isOutletBranch, bool isEquipmentBranch) {
        // Empty equipment branches are represented by a transient branch node
        // rather than a persisted component row. The inlet and outlet anchor
        // branches use the loop's canonical inlet/outlet nodes instead.
      const auto components = branch.components();
      if (components.empty()) {
        if (isEquipmentBranch) {
          return model.getOrCreateTransientByName<Node>(branch.nameString() + " Node") == node;
        }
        if (isInletBranch) {
          return inletNode == node;
        }
        if (isOutletBranch) {
          return outletNode == node;
        }
        return false;
      }

      if (auto firstInletNode = branch.componentInletNode(0u)) {
        if (*firstInletNode == node) {
          return true;
        }
      }

      for (unsigned i = 0; i < components.size(); ++i) {
        if (auto branchOutletNode = branch.componentOutletNode(i)) {
          if (*branchOutletNode == node) {
            return true;
          }
        }
      }

      return false;
      }

      // Plant-loop projection is driven by exact node-role matches, not by
      // child names or parent type alone. That keeps traversal aligned with
      // the actual branch row that was inserted into the loop.
      bool sameNodeTargets(const boost::optional<Node>& lhs, const boost::optional<Node>& rhs) {
        return lhs && rhs && (*lhs == *rhs);
      }

      // Some radiant families persist the parent ZoneHVAC object on the branch
      // even though the canonical OpenStudio API exposes a child coil on the
      // loop. This helper projects the stored parent row back to the transient
      // child coil when the branch inlet/outlet nodes line up with that
      // specific heating or cooling role.
      boost::optional<ModelObject> projectPlantTraversalComponent(const ModelObject& component, const boost::optional<Node>& branchInletNode,
                                                                  const boost::optional<Node>& branchOutletNode) {
        if (auto radiant = component.optionalCast<ZoneHVACLowTempRadiantConstFlow>()) {
          const auto heatingCoil = radiant->heatingCoil();
          const auto heatingInlet = heatingCoil.inletModelObject() ? heatingCoil.inletModelObject()->optionalCast<Node>() : boost::none;
          const auto heatingOutlet = heatingCoil.outletModelObject() ? heatingCoil.outletModelObject()->optionalCast<Node>() : boost::none;
          if (sameNodeTargets(branchInletNode, heatingInlet) && sameNodeTargets(branchOutletNode, heatingOutlet)) {
            return heatingCoil.cast<ModelObject>();
          }

          const auto coolingCoil = radiant->coolingCoil();
          const auto coolingInlet = coolingCoil.inletModelObject() ? coolingCoil.inletModelObject()->optionalCast<Node>() : boost::none;
          const auto coolingOutlet = coolingCoil.outletModelObject() ? coolingCoil.outletModelObject()->optionalCast<Node>() : boost::none;
          if (sameNodeTargets(branchInletNode, coolingInlet) && sameNodeTargets(branchOutletNode, coolingOutlet)) {
            return coolingCoil.cast<ModelObject>();
          }
        }

        if (auto radiant = component.optionalCast<ZoneHVACLowTempRadiantVarFlow>()) {
          if (auto heating = radiant->heatingCoil()) {
            auto heatingCoil = heating->cast<CoilHeatingLowTempRadiantVarFlow>();
            const auto heatingInlet = heatingCoil.inletModelObject() ? heatingCoil.inletModelObject()->optionalCast<Node>() : boost::none;
            const auto heatingOutlet = heatingCoil.outletModelObject() ? heatingCoil.outletModelObject()->optionalCast<Node>() : boost::none;
            if (sameNodeTargets(branchInletNode, heatingInlet) && sameNodeTargets(branchOutletNode, heatingOutlet)) {
              return heatingCoil.cast<ModelObject>();
            }
          }

          if (auto cooling = radiant->coolingCoil()) {
            auto coolingCoil = cooling->cast<CoilCoolingLowTempRadiantVarFlow>();
            const auto coolingInlet = coolingCoil.inletModelObject() ? coolingCoil.inletModelObject()->optionalCast<Node>() : boost::none;
            const auto coolingOutlet = coolingCoil.outletModelObject() ? coolingCoil.outletModelObject()->optionalCast<Node>() : boost::none;
            if (sameNodeTargets(branchInletNode, coolingInlet) && sameNodeTargets(branchOutletNode, coolingOutlet)) {
              return coolingCoil.cast<ModelObject>();
            }
          }
        }

        if (auto baseboard = component.optionalCast<ZoneHVACBaseboardRadiantConvectiveWater>()) {
          const auto heatingCoil = baseboard->heatingCoil().cast<CoilHeatingWaterBaseboardRadiant>();
          const auto heatingInlet = heatingCoil.inletModelObject() ? heatingCoil.inletModelObject()->optionalCast<Node>() : boost::none;
          const auto heatingOutlet = heatingCoil.outletModelObject() ? heatingCoil.outletModelObject()->optionalCast<Node>() : boost::none;
          if (sameNodeTargets(branchInletNode, heatingInlet) && sameNodeTargets(branchOutletNode, heatingOutlet)) {
            return heatingCoil.cast<ModelObject>();
          }
        }

        if (auto panel = component.optionalCast<ZoneHVACCoolingPanelRadiantConvectiveWater>()) {
          const auto coolingCoil = panel->coolingCoil().cast<CoilCoolingWaterPanelRadiant>();
          const auto coolingInlet = coolingCoil.inletModelObject() ? coolingCoil.inletModelObject()->optionalCast<Node>() : boost::none;
          const auto coolingOutlet = coolingCoil.outletModelObject() ? coolingCoil.outletModelObject()->optionalCast<Node>() : boost::none;
          if (sameNodeTargets(branchInletNode, coolingInlet) && sameNodeTargets(branchOutletNode, coolingOutlet)) {
            return coolingCoil.cast<ModelObject>();
          }
        }

        return component;
      }

      // Branch rows remain the persisted source of truth. This helper only
      // rewrites the traversal view that higher-level OpenStudio-style APIs
      // return to callers.
      std::vector<ModelObject> projectedBranchComponents(const Branch& branch) {
        const auto rawComponents = branch.components();
        std::vector<ModelObject> result;
        result.reserve(rawComponents.size());
        for (unsigned i = 0; i < rawComponents.size(); ++i) {
          result.push_back(*projectPlantTraversalComponent(rawComponents[i], branch.componentInletNode(i), branch.componentOutletNode(i)));
        }
        return result;
      }

    }  // namespace

    // PlantLoop stores its topology in EnergyPlus branch/connective-tissue objects,
    // but the API we are trying to preserve is the higher-level OpenStudio loop API.
    // This helper keeps the two representations aligned after canonicalization and
    // after branch edits. The BranchList is the source of truth: one inlet branch,
    // one or more equipment branches in the middle, and one outlet branch. The
    // splitter and mixer are rebuilt to match that ordering exactly.
    bool PlantLoop_Impl::syncConnectorPorts(ConnectorSplitter& splitter, ConnectorMixer& mixer, const Branch& inletBranch,
                                            const Branch& outletBranch,
                                            const std::vector<Branch>& equipmentBranches) const {
      if (!splitter.getImpl<openstudio::epmodel::detail::ConnectorSplitter_Impl>()->setInletBranch(inletBranch)) {
        return false;
      }
      if (!mixer.getImpl<openstudio::epmodel::detail::ConnectorMixer_Impl>()->setOutletBranch(outletBranch)) {
        return false;
      }

      while (splitter.nextBranchIndex() > equipmentBranches.size()) {
        splitter.removePortForBranch(splitter.nextBranchIndex() - 1u);
      }
      while (mixer.nextBranchIndex() > equipmentBranches.size()) {
        mixer.removePortForBranch(mixer.nextBranchIndex() - 1u);
      }

      for (unsigned i = 0; i < equipmentBranches.size(); ++i) {
        if (!splitter.setOutletModelObject(i, equipmentBranches[i].cast<ModelObject>())) {
          return false;
        }
        if (!mixer.setInletModelObject(i, equipmentBranches[i].cast<ModelObject>())) {
          return false;
        }
      }

      return true;
    }

    // Nodes on a PlantLoop are resolved back to a Branch so higher-level APIs can
    // answer questions like "which branch am I on?" and remove a branch by giving
    // one of its nodes. Empty equipment branches are represented by a transient
    // branch node, while inlet and outlet branches fall back to the loop endpoint
    // nodes when they do not yet contain real components.
    boost::optional<Branch> PlantLoop_Impl::supplyBranchForNode(const Node& node) const {
      const auto inletBranch = supplyInletBranch();
      const auto outletBranch = supplyOutletBranch();
      const auto equipmentBranches = supplyEquipmentBranches();
      const auto inletNode = supplyInletNode();
      const auto outletNode = supplyOutletNode();

      if (branchContainsNode(model(), inletBranch, node, inletNode, outletNode, true, false, false)) {
        return inletBranch;
      }

      for (const auto& branch : equipmentBranches) {
        if (branchContainsNode(model(), branch, node, inletNode, outletNode, false, false, true)) {
          return branch;
        }
      }

      if (branchContainsNode(model(), outletBranch, node, inletNode, outletNode, false, true, false)) {
        return outletBranch;
      }

      return boost::none;
    }

    // Demand-side branch lookup follows the same rules as plant side. Keeping the
    // logic parallel makes it easier to reason about supply and demand behavior
    // together when topology repair or traversal changes.
    boost::optional<Branch> PlantLoop_Impl::demandBranchForNode(const Node& node) const {
      const auto inletBranch = demandInletBranch();
      const auto outletBranch = demandOutletBranch();
      const auto equipmentBranches = demandEquipmentBranches();
      const auto inletNode = demandInletNode();
      const auto outletNode = demandOutletNode();

      if (branchContainsNode(model(), inletBranch, node, inletNode, outletNode, true, false, false)) {
        return inletBranch;
      }

      for (const auto& branch : equipmentBranches) {
        if (branchContainsNode(model(), branch, node, inletNode, outletNode, false, false, true)) {
          return branch;
        }
      }

      if (branchContainsNode(model(), outletBranch, node, inletNode, outletNode, false, true, false)) {
        return outletBranch;
      }

      return boost::none;
    }

    Node PlantLoop_Impl::supplyInletNode() const {
      auto node = getObject<PlantLoop>().getModelObjectTarget<Node>(openstudio::PlantLoopFields::PlantSideInletNodeName);
      OS_ASSERT(node);
      return *node;
    }

    Node PlantLoop_Impl::supplyOutletNode() const {
      auto node = getObject<PlantLoop>().getModelObjectTarget<Node>(openstudio::PlantLoopFields::PlantSideOutletNodeName);
      OS_ASSERT(node);
      return *node;
    }

    std::vector<Node> PlantLoop_Impl::supplyOutletNodes() const {
      return {supplyOutletNode()};
    }

    Node PlantLoop_Impl::demandInletNode() const {
      auto node = getObject<PlantLoop>().getModelObjectTarget<Node>(openstudio::PlantLoopFields::DemandSideInletNodeName);
      OS_ASSERT(node);
      return *node;
    }

    std::vector<Node> PlantLoop_Impl::demandInletNodes() const {
      return {demandInletNode()};
    }

    Node PlantLoop_Impl::demandOutletNode() const {
      auto node = getObject<PlantLoop>().getModelObjectTarget<Node>(openstudio::PlantLoopFields::DemandSideOutletNodeName);
      OS_ASSERT(node);
      return *node;
    }

    BranchList PlantLoop_Impl::supplyBranchList() const {
      auto branchList = getObject<PlantLoop>().getModelObjectTarget<BranchList>(openstudio::PlantLoopFields::PlantSideBranchListName);
      OS_ASSERT(branchList);
      return *branchList;
    }

    BranchList PlantLoop_Impl::demandBranchList() const {
      auto branchList = getObject<PlantLoop>().getModelObjectTarget<BranchList>(openstudio::PlantLoopFields::DemandSideBranchListName);
      OS_ASSERT(branchList);
      return *branchList;
    }

    Branch PlantLoop_Impl::supplyInletBranch() const {
      const auto branches = supplyBranchList().branches();
      OS_ASSERT(branches.size() >= 3u);
      return branches.front();
    }

    Branch PlantLoop_Impl::supplyOutletBranch() const {
      const auto branches = supplyBranchList().branches();
      OS_ASSERT(branches.size() >= 3u);
      return branches.back();
    }

    Branch PlantLoop_Impl::demandInletBranch() const {
      const auto branches = demandBranchList().branches();
      OS_ASSERT(branches.size() >= 3u);
      return branches.front();
    }

    Branch PlantLoop_Impl::demandOutletBranch() const {
      const auto branches = demandBranchList().branches();
      OS_ASSERT(branches.size() >= 3u);
      return branches.back();
    }

    std::vector<Branch> PlantLoop_Impl::supplyEquipmentBranches() const {
      auto branches = supplyBranchList().branches();
      OS_ASSERT(branches.size() >= 3u);
      return std::vector<Branch>(std::next(branches.begin()), std::prev(branches.end()));
    }

    std::vector<Branch> PlantLoop_Impl::demandEquipmentBranches() const {
      auto branches = demandBranchList().branches();
      OS_ASSERT(branches.size() >= 3u);
      return std::vector<Branch>(std::next(branches.begin()), std::prev(branches.end()));
    }

    Splitter PlantLoop_Impl::supplySplitter() const {
      const auto inletBranch = supplyInletBranch();
      const auto equipmentBranches = supplyEquipmentBranches();
      boost::optional<ConnectorSplitter> result;
      for (const auto& splitter : model().getConcreteModelObjects<ConnectorSplitter>()) {
        auto inlet = splitter.getModelObjectTarget<Branch>(splitter.inletPort());
        if (!inlet || !(*inlet == inletBranch)) {
          continue;
        }

        if (splitter.nextBranchIndex() != equipmentBranches.size()) {
          continue;
        }

        bool allOutletsMatch = true;
        for (unsigned i = 0; i < equipmentBranches.size(); ++i) {
          auto branch = splitter.getModelObjectTarget<Branch>(splitter.outletPort(i));
          if (!branch || !(*branch == equipmentBranches[i])) {
            allOutletsMatch = false;
            break;
          }
        }

        if (allOutletsMatch) {
          result = splitter;
          break;
        }
      }
      OS_ASSERT(result);
      return *result;
    }

    Mixer PlantLoop_Impl::supplyMixer() const {
      const auto outletBranch = supplyOutletBranch();
      const auto equipmentBranches = supplyEquipmentBranches();
      boost::optional<ConnectorMixer> result;
      for (const auto& mixer : model().getConcreteModelObjects<ConnectorMixer>()) {
        auto outlet = mixer.getModelObjectTarget<Branch>(mixer.outletPort());
        if (!outlet || !(*outlet == outletBranch)) {
          continue;
        }

        if (mixer.nextBranchIndex() != equipmentBranches.size()) {
          continue;
        }

        bool allInletsMatch = true;
        for (unsigned i = 0; i < equipmentBranches.size(); ++i) {
          auto branch = mixer.getModelObjectTarget<Branch>(mixer.inletPort(i));
          if (!branch || !(*branch == equipmentBranches[i])) {
            allInletsMatch = false;
            break;
          }
        }

        if (allInletsMatch) {
          result = mixer;
          break;
        }
      }
      OS_ASSERT(result);
      return *result;
    }

    Splitter PlantLoop_Impl::demandSplitter() const {
      const auto inletBranch = demandInletBranch();
      const auto equipmentBranches = demandEquipmentBranches();
      boost::optional<ConnectorSplitter> result;
      for (const auto& splitter : model().getConcreteModelObjects<ConnectorSplitter>()) {
        auto inlet = splitter.getModelObjectTarget<Branch>(splitter.inletPort());
        if (!inlet || !(*inlet == inletBranch)) {
          continue;
        }

        if (splitter.nextBranchIndex() != equipmentBranches.size()) {
          continue;
        }

        bool allOutletsMatch = true;
        for (unsigned i = 0; i < equipmentBranches.size(); ++i) {
          auto branch = splitter.getModelObjectTarget<Branch>(splitter.outletPort(i));
          if (!branch || !(*branch == equipmentBranches[i])) {
            allOutletsMatch = false;
            break;
          }
        }

        if (allOutletsMatch) {
          result = splitter;
          break;
        }
      }
      OS_ASSERT(result);
      return *result;
    }

    Mixer PlantLoop_Impl::demandMixer() const {
      const auto outletBranch = demandOutletBranch();
      const auto equipmentBranches = demandEquipmentBranches();
      boost::optional<ConnectorMixer> result;
      for (const auto& mixer : model().getConcreteModelObjects<ConnectorMixer>()) {
        auto outlet = mixer.getModelObjectTarget<Branch>(mixer.outletPort());
        if (!outlet || !(*outlet == outletBranch)) {
          continue;
        }

        if (mixer.nextBranchIndex() != equipmentBranches.size()) {
          continue;
        }

        bool allInletsMatch = true;
        for (unsigned i = 0; i < equipmentBranches.size(); ++i) {
          auto branch = mixer.getModelObjectTarget<Branch>(mixer.inletPort(i));
          if (!branch || !(*branch == equipmentBranches[i])) {
            allInletsMatch = false;
            break;
          }
        }

        if (allInletsMatch) {
          result = mixer;
          break;
        }
      }
      OS_ASSERT(result);
      return *result;
    }

    std::vector<ModelObject> PlantLoop_Impl::supplyComponents(const HVACComponent& inletComp, const HVACComponent& outletComp,
                                                              openstudio::IddObjectType type) const {
      AdjacencyBuilder builder;
      const auto supplyInlet = supplyInletNode().cast<ModelObject>();
      const auto splitter = supplySplitter().cast<ModelObject>();
      const auto mixer = supplyMixer().cast<ModelObject>();
      const auto supplyOutlet = supplyOutletNode().cast<ModelObject>();

      ModelObject previousObject = supplyInlet;
      {
        const auto branch = supplyInletBranch();
        const auto components = projectedBranchComponents(branch);
        if (!components.empty()) {
          if (auto inletNode = branch.componentInletNode(0u)) {
            if (previousObject != inletNode->cast<ModelObject>()) {
              builder.addLink(previousObject, inletNode->cast<ModelObject>());
            }
            previousObject = inletNode->cast<ModelObject>();
          }

          for (unsigned i = 0; i < components.size(); ++i) {
            if (previousObject != components[i]) {
              builder.addLink(previousObject, components[i]);
            }
            previousObject = components[i];

            if (auto outletNode = branch.componentOutletNode(i)) {
              if (previousObject != outletNode->cast<ModelObject>()) {
                builder.addLink(previousObject, outletNode->cast<ModelObject>());
              }
              previousObject = outletNode->cast<ModelObject>();
            }
          }
        }
      }

      if (previousObject != splitter) {
        builder.addLink(previousObject, splitter);
      }

      for (const auto& branch : supplyEquipmentBranches()) {
        previousObject = splitter;
        const auto components = projectedBranchComponents(branch);
        if (components.empty()) {
          const auto branchNode = model().getOrCreateTransientByName<Node>(branch.nameString() + " Node").cast<ModelObject>();
          if (previousObject != branchNode) {
            builder.addLink(previousObject, branchNode);
          }
          previousObject = branchNode;
        } else {
          if (auto inletNode = branch.componentInletNode(0u)) {
            if (previousObject != inletNode->cast<ModelObject>()) {
              builder.addLink(previousObject, inletNode->cast<ModelObject>());
            }
            previousObject = inletNode->cast<ModelObject>();
          }

          for (unsigned i = 0; i < components.size(); ++i) {
            if (previousObject != components[i]) {
              builder.addLink(previousObject, components[i]);
            }
            previousObject = components[i];

            if (auto outletNode = branch.componentOutletNode(i)) {
              if (previousObject != outletNode->cast<ModelObject>()) {
                builder.addLink(previousObject, outletNode->cast<ModelObject>());
              }
              previousObject = outletNode->cast<ModelObject>();
            }
          }
        }

        if (previousObject != mixer) {
          builder.addLink(previousObject, mixer);
        }
      }

      previousObject = mixer;
      {
        const auto branch = supplyOutletBranch();
        const auto components = projectedBranchComponents(branch);
        if (!components.empty()) {
          if (auto inletNode = branch.componentInletNode(0u)) {
            if (previousObject != inletNode->cast<ModelObject>()) {
              builder.addLink(previousObject, inletNode->cast<ModelObject>());
            }
            previousObject = inletNode->cast<ModelObject>();
          }

          for (unsigned i = 0; i < components.size(); ++i) {
            if (previousObject != components[i]) {
              builder.addLink(previousObject, components[i]);
            }
            previousObject = components[i];

            if (auto outletNode = branch.componentOutletNode(i)) {
              if (previousObject != outletNode->cast<ModelObject>()) {
                builder.addLink(previousObject, outletNode->cast<ModelObject>());
              }
              previousObject = outletNode->cast<ModelObject>();
            }
          }
        }
      }

      if (previousObject != supplyOutlet) {
        builder.addLink(previousObject, supplyOutlet);
      }

      auto pathObjects = builder.walkPath(model(), inletComp, outletComp);
      if (type == openstudio::IddObjectType::Catchall) {
        return pathObjects;
      }

      std::vector<ModelObject> filtered;
      filtered.reserve(pathObjects.size());
      for (const auto& object : pathObjects) {
        if (object.iddObject().type() == type) {
          filtered.push_back(object);
        }
      }
      return filtered;
    }

    std::vector<ModelObject> PlantLoop_Impl::supplyComponents(openstudio::IddObjectType type) const {
      return supplyComponents(supplyInletNode(), supplyOutletNode(), type);
    }

    std::vector<ModelObject> PlantLoop_Impl::demandComponents(const HVACComponent& inletComp, const HVACComponent& outletComp,
                                                              openstudio::IddObjectType type) const {
      AdjacencyBuilder builder;
      const auto demandInlet = demandInletNode().cast<ModelObject>();
      const auto splitter = demandSplitter().cast<ModelObject>();
      const auto mixer = demandMixer().cast<ModelObject>();
      const auto demandOutlet = demandOutletNode().cast<ModelObject>();

      ModelObject previousObject = demandInlet;
      {
        const auto branch = demandInletBranch();
        const auto components = projectedBranchComponents(branch);
        if (!components.empty()) {
          if (auto inletNode = branch.componentInletNode(0u)) {
            if (previousObject != inletNode->cast<ModelObject>()) {
              builder.addLink(previousObject, inletNode->cast<ModelObject>());
            }
            previousObject = inletNode->cast<ModelObject>();
          }

          for (unsigned i = 0; i < components.size(); ++i) {
            if (previousObject != components[i]) {
              builder.addLink(previousObject, components[i]);
            }
            previousObject = components[i];

            if (auto outletNode = branch.componentOutletNode(i)) {
              if (previousObject != outletNode->cast<ModelObject>()) {
                builder.addLink(previousObject, outletNode->cast<ModelObject>());
              }
              previousObject = outletNode->cast<ModelObject>();
            }
          }
        }
      }

      if (previousObject != splitter) {
        builder.addLink(previousObject, splitter);
      }

      for (const auto& branch : demandEquipmentBranches()) {
        previousObject = splitter;
        const auto components = projectedBranchComponents(branch);
        if (components.empty()) {
          const auto branchNode = model().getOrCreateTransientByName<Node>(branch.nameString() + " Node").cast<ModelObject>();
          if (previousObject != branchNode) {
            builder.addLink(previousObject, branchNode);
          }
          previousObject = branchNode;
        } else {
          if (auto inletNode = branch.componentInletNode(0u)) {
            if (previousObject != inletNode->cast<ModelObject>()) {
              builder.addLink(previousObject, inletNode->cast<ModelObject>());
            }
            previousObject = inletNode->cast<ModelObject>();
          }

          for (unsigned i = 0; i < components.size(); ++i) {
            if (previousObject != components[i]) {
              builder.addLink(previousObject, components[i]);
            }
            previousObject = components[i];

            if (auto outletNode = branch.componentOutletNode(i)) {
              if (previousObject != outletNode->cast<ModelObject>()) {
                builder.addLink(previousObject, outletNode->cast<ModelObject>());
              }
              previousObject = outletNode->cast<ModelObject>();
            }
          }
        }

        if (previousObject != mixer) {
          builder.addLink(previousObject, mixer);
        }
      }

      previousObject = mixer;
      {
        const auto branch = demandOutletBranch();
        const auto components = projectedBranchComponents(branch);
        if (!components.empty()) {
          if (auto inletNode = branch.componentInletNode(0u)) {
            if (previousObject != inletNode->cast<ModelObject>()) {
              builder.addLink(previousObject, inletNode->cast<ModelObject>());
            }
            previousObject = inletNode->cast<ModelObject>();
          }

          for (unsigned i = 0; i < components.size(); ++i) {
            if (previousObject != components[i]) {
              builder.addLink(previousObject, components[i]);
            }
            previousObject = components[i];

            if (auto outletNode = branch.componentOutletNode(i)) {
              if (previousObject != outletNode->cast<ModelObject>()) {
                builder.addLink(previousObject, outletNode->cast<ModelObject>());
              }
              previousObject = outletNode->cast<ModelObject>();
            }
          }
        }
      }

      if (previousObject != demandOutlet) {
        builder.addLink(previousObject, demandOutlet);
      }

      auto pathObjects = builder.walkPath(model(), inletComp, outletComp);
      if (type == openstudio::IddObjectType::Catchall) {
        return pathObjects;
      }

      std::vector<ModelObject> filtered;
      filtered.reserve(pathObjects.size());
      for (const auto& object : pathObjects) {
        if (object.iddObject().type() == type) {
          filtered.push_back(object);
        }
      }
      return filtered;
    }

    std::vector<ModelObject> PlantLoop_Impl::demandComponents(openstudio::IddObjectType type) const {
      return demandComponents(demandInletNode(), demandOutletNode(), type);
    }

    boost::optional<Branch> PlantLoop_Impl::branchForNode(const Node& node) const {
      if (auto branch = supplyBranchForNode(node)) {
        return branch;
      }
      return demandBranchForNode(node);
    }

    std::string PlantLoop_Impl::loadDistributionScheme() const {
      const auto value = getString(openstudio::PlantLoopFields::LoadDistributionScheme, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool PlantLoop_Impl::setLoadDistributionScheme(const std::string& scheme) {
      auto normalized = scheme;
      if (openstudio::istringEqual(normalized, "Sequential")) {
        normalized = "SequentialLoad";
      } else if (openstudio::istringEqual(normalized, "Uniform")) {
        normalized = "UniformLoad";
      }
      return setString(openstudio::PlantLoopFields::LoadDistributionScheme, normalized);
    }

    std::string PlantLoop_Impl::fluidType() const {
      const auto value = getString(openstudio::PlantLoopFields::FluidType, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool PlantLoop_Impl::setFluidType(const std::string& value) {
      return setString(openstudio::PlantLoopFields::FluidType, value);
    }

    int PlantLoop_Impl::glycolConcentration() const {
      return getInt(openstudio::OS_PlantLoopFields::GlycolConcentration, true).get();
    }

    bool PlantLoop_Impl::setGlycolConcentration(int glycolConcentration) {
      return setInt(openstudio::OS_PlantLoopFields::GlycolConcentration, glycolConcentration);
    }

    double PlantLoop_Impl::maximumLoopTemperature() const {
      const auto value = getDouble(openstudio::PlantLoopFields::MaximumLoopTemperature, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool PlantLoop_Impl::setMaximumLoopTemperature(double value) {
      return setDouble(openstudio::PlantLoopFields::MaximumLoopTemperature, value);
    }

    double PlantLoop_Impl::minimumLoopTemperature() const {
      const auto value = getDouble(openstudio::PlantLoopFields::MinimumLoopTemperature, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool PlantLoop_Impl::setMinimumLoopTemperature(double value) {
      return setDouble(openstudio::PlantLoopFields::MinimumLoopTemperature, value);
    }

    boost::optional<double> PlantLoop_Impl::maximumLoopFlowRate() const {
      return getDouble(openstudio::PlantLoopFields::MaximumLoopFlowRate, true);
    }

    bool PlantLoop_Impl::setMaximumLoopFlowRate(double value) {
      return setDouble(openstudio::PlantLoopFields::MaximumLoopFlowRate, value);
    }

    bool PlantLoop_Impl::isMaximumLoopFlowRateAutosized() const {
      if (const auto value = getString(openstudio::PlantLoopFields::MaximumLoopFlowRate, true)) {
        return openstudio::istringEqual(value.get(), "Autosize");
      }
      return false;
    }

    void PlantLoop_Impl::autosizeMaximumLoopFlowRate() {
      OS_ASSERT(setString(openstudio::PlantLoopFields::MaximumLoopFlowRate, "Autosize"));
    }

    boost::optional<double> PlantLoop_Impl::minimumLoopFlowRate() const {
      return getDouble(openstudio::PlantLoopFields::MinimumLoopFlowRate, true);
    }

    bool PlantLoop_Impl::setMinimumLoopFlowRate(double value) {
      return setDouble(openstudio::PlantLoopFields::MinimumLoopFlowRate, value);
    }

    bool PlantLoop_Impl::isMinimumLoopFlowRateAutosized() const {
      if (const auto value = getString(openstudio::PlantLoopFields::MinimumLoopFlowRate, true)) {
        return openstudio::istringEqual(value.get(), "Autosize");
      }
      return false;
    }

    void PlantLoop_Impl::autosizeMinimumLoopFlowRate() {
      OS_ASSERT(setString(openstudio::PlantLoopFields::MinimumLoopFlowRate, "Autosize"));
    }

    boost::optional<double> PlantLoop_Impl::plantLoopVolume() const {
      return getDouble(openstudio::PlantLoopFields::PlantLoopVolume, true);
    }

    bool PlantLoop_Impl::setPlantLoopVolume(double value) {
      return setDouble(openstudio::PlantLoopFields::PlantLoopVolume, value);
    }

    bool PlantLoop_Impl::isPlantLoopVolumeAutocalculated() const {
      if (const auto value = getString(openstudio::PlantLoopFields::PlantLoopVolume, true)) {
        return openstudio::istringEqual(value.get(), "Autocalculate");
      }
      return false;
    }

    void PlantLoop_Impl::autocalculatePlantLoopVolume() {
      OS_ASSERT(setString(openstudio::PlantLoopFields::PlantLoopVolume, "Autocalculate"));
    }

    std::string PlantLoop_Impl::commonPipeSimulation() const {
      const auto value = getString(openstudio::PlantLoopFields::CommonPipeSimulation, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool PlantLoop_Impl::isCommonPipeSimulationDefaulted() const {
      return isEmpty(openstudio::PlantLoopFields::CommonPipeSimulation);
    }

    bool PlantLoop_Impl::setCommonPipeSimulation(const std::string& value) {
      return setString(openstudio::PlantLoopFields::CommonPipeSimulation, value);
    }

    void PlantLoop_Impl::resetCommonPipeSimulation() {
      OS_ASSERT(setString(openstudio::PlantLoopFields::CommonPipeSimulation, ""));
    }

    Node PlantLoop_Impl::loopTemperatureSetpointNode() const {
      auto node = getObject<PlantLoop>().getModelObjectTarget<Node>(openstudio::PlantLoopFields::LoopTemperatureSetpointNodeName);
      OS_ASSERT(node);
      return *node;
    }

    bool PlantLoop_Impl::setLoopTemperatureSetpointNode(Node& node) {
      if (node.model() != model()) {
        return false;
      }
      return setPointer(openstudio::PlantLoopFields::LoopTemperatureSetpointNodeName, node.handle(), false);
    }

    PlantEquipmentOperationSchemes PlantLoop_Impl::plantEquipmentOperationSchemes() const {
      auto operationSchemes =
        getObject<PlantLoop>().getModelObjectTarget<PlantEquipmentOperationSchemes>(openstudio::PlantLoopFields::PlantEquipmentOperationSchemeName);
      OS_ASSERT(operationSchemes);
      return *operationSchemes;
    }

    boost::optional<PlantEquipmentOperationHeatingLoad> PlantLoop_Impl::plantEquipmentOperationHeatingLoad() const {
      return plantEquipmentOperationSchemes().plantEquipmentOperationHeatingLoad();
    }

    bool PlantLoop_Impl::setPlantEquipmentOperationHeatingLoad(const PlantEquipmentOperationHeatingLoad& plantOperation) {
      return plantEquipmentOperationSchemes().getImpl<detail::PlantEquipmentOperationSchemes_Impl>()->setPlantEquipmentOperationHeatingLoad(
        plantOperation);
    }

    void PlantLoop_Impl::resetPlantEquipmentOperationHeatingLoad() {
      plantEquipmentOperationSchemes().getImpl<detail::PlantEquipmentOperationSchemes_Impl>()->resetPlantEquipmentOperationHeatingLoad();
    }

    bool PlantLoop_Impl::setPlantEquipmentOperationHeatingLoadSchedule(Schedule& schedule) {
      return plantEquipmentOperationSchemes().getImpl<detail::PlantEquipmentOperationSchemes_Impl>()->setPlantEquipmentOperationHeatingLoadSchedule(
        schedule);
    }

    void PlantLoop_Impl::resetPlantEquipmentOperationHeatingLoadSchedule() {
      plantEquipmentOperationSchemes().getImpl<detail::PlantEquipmentOperationSchemes_Impl>()->resetPlantEquipmentOperationHeatingLoadSchedule();
    }

    boost::optional<Schedule> PlantLoop_Impl::plantEquipmentOperationHeatingLoadSchedule() const {
      return plantEquipmentOperationSchemes().plantEquipmentOperationHeatingLoadSchedule();
    }

    boost::optional<PlantEquipmentOperationCoolingLoad> PlantLoop_Impl::plantEquipmentOperationCoolingLoad() const {
      return plantEquipmentOperationSchemes().plantEquipmentOperationCoolingLoad();
    }

    bool PlantLoop_Impl::setPlantEquipmentOperationCoolingLoad(const PlantEquipmentOperationCoolingLoad& plantOperation) {
      return plantEquipmentOperationSchemes().getImpl<detail::PlantEquipmentOperationSchemes_Impl>()->setPlantEquipmentOperationCoolingLoad(
        plantOperation);
    }

    void PlantLoop_Impl::resetPlantEquipmentOperationCoolingLoad() {
      plantEquipmentOperationSchemes().getImpl<detail::PlantEquipmentOperationSchemes_Impl>()->resetPlantEquipmentOperationCoolingLoad();
    }

    bool PlantLoop_Impl::setPlantEquipmentOperationCoolingLoadSchedule(Schedule& schedule) {
      return plantEquipmentOperationSchemes().getImpl<detail::PlantEquipmentOperationSchemes_Impl>()->setPlantEquipmentOperationCoolingLoadSchedule(
        schedule);
    }

    boost::optional<Schedule> PlantLoop_Impl::plantEquipmentOperationCoolingLoadSchedule() const {
      return plantEquipmentOperationSchemes().plantEquipmentOperationCoolingLoadSchedule();
    }

    void PlantLoop_Impl::resetPlantEquipmentOperationCoolingLoadSchedule() {
      plantEquipmentOperationSchemes().getImpl<detail::PlantEquipmentOperationSchemes_Impl>()->resetPlantEquipmentOperationCoolingLoadSchedule();
    }

    boost::optional<PlantEquipmentOperationScheme> PlantLoop_Impl::primaryPlantEquipmentOperationScheme() const {
      return plantEquipmentOperationSchemes().primaryPlantEquipmentOperationScheme();
    }

    bool PlantLoop_Impl::setPrimaryPlantEquipmentOperationScheme(const PlantEquipmentOperationScheme& plantOperation) {
      return plantEquipmentOperationSchemes().getImpl<detail::PlantEquipmentOperationSchemes_Impl>()->setPrimaryPlantEquipmentOperationScheme(
        plantOperation);
    }

    void PlantLoop_Impl::resetPrimaryPlantEquipmentOperationScheme() {
      plantEquipmentOperationSchemes().getImpl<detail::PlantEquipmentOperationSchemes_Impl>()->resetPrimaryPlantEquipmentOperationScheme();
    }

    bool PlantLoop_Impl::setPrimaryPlantEquipmentOperationSchemeSchedule(Schedule& schedule) {
      return plantEquipmentOperationSchemes()
        .getImpl<detail::PlantEquipmentOperationSchemes_Impl>()
        ->setPrimaryPlantEquipmentOperationSchemeSchedule(schedule);
    }

    void PlantLoop_Impl::resetPrimaryPlantEquipmentOperationSchemeSchedule() {
      plantEquipmentOperationSchemes().getImpl<detail::PlantEquipmentOperationSchemes_Impl>()->resetPrimaryPlantEquipmentOperationSchemeSchedule();
    }

    boost::optional<Schedule> PlantLoop_Impl::primaryPlantEquipmentOperationSchemeSchedule() const {
      return plantEquipmentOperationSchemes().primaryPlantEquipmentOperationSchemeSchedule();
    }

    bool PlantLoop_Impl::setComponentSetpointOperationSchemeSchedule(Schedule& schedule) {
      return plantEquipmentOperationSchemes().getImpl<detail::PlantEquipmentOperationSchemes_Impl>()->setComponentSetpointOperationSchemeSchedule(
        schedule);
    }

    void PlantLoop_Impl::resetComponentSetpointOperationSchemeSchedule() {
      plantEquipmentOperationSchemes().getImpl<detail::PlantEquipmentOperationSchemes_Impl>()->resetComponentSetpointOperationSchemeSchedule();
    }

    boost::optional<Schedule> PlantLoop_Impl::componentSetpointOperationSchemeSchedule() const {
      return plantEquipmentOperationSchemes().componentSetpointOperationSchemeSchedule();
    }

    SizingPlant PlantLoop_Impl::sizingPlant() const {
      boost::optional<SizingPlant> result;
      for (const auto& candidate : model().getConcreteModelObjects<SizingPlant>()) {
        auto plantLoop = candidate.getModelObjectTarget<PlantLoop>(openstudio::Sizing_PlantFields::PlantorCondenserLoopName);
        if (!plantLoop || !(*plantLoop == getObject<PlantLoop>())) {
          continue;
        }

        if (!result) {
          result = candidate;
        }
      }

      OS_ASSERT(result);
      return *result;
    }

    AvailabilityManagerAssignmentList PlantLoop_Impl::availabilityManagerAssignmentList() const {
      auto assignmentList =
        getObject<PlantLoop>().getModelObjectTarget<AvailabilityManagerAssignmentList>(openstudio::PlantLoopFields::AvailabilityManagerListName);
      OS_ASSERT(assignmentList);
      return *assignmentList;
    }

    std::vector<AvailabilityManager> PlantLoop_Impl::availabilityManagers() const {
      return availabilityManagerAssignmentList().availabilityManagers();
    }

    bool PlantLoop_Impl::addAvailabilityManager(const AvailabilityManager& availabilityManager) {
      const auto type = availabilityManager.iddObject().type();
      if ((type == IddObjectType::AvailabilityManager_NightCycle) || (type == IddObjectType::AvailabilityManager_HybridVentilation)
          || (type == IddObjectType::AvailabilityManager_NightVentilation)) {
        return false;
      }
      return availabilityManagerAssignmentList().addAvailabilityManager(availabilityManager);
    }

    bool PlantLoop_Impl::addAvailabilityManager(const AvailabilityManager& availabilityManager, unsigned priority) {
      if (!addAvailabilityManager(availabilityManager)) {
        return false;
      }
      return availabilityManagerAssignmentList().setAvailabilityManagerPriority(availabilityManager, priority);
    }

    bool PlantLoop_Impl::setAvailabilityManagers(const std::vector<AvailabilityManager>& availabilityManagers) {
      for (const auto& availabilityManager : availabilityManagers) {
        const auto type = availabilityManager.iddObject().type();
        if ((type == IddObjectType::AvailabilityManager_NightCycle) || (type == IddObjectType::AvailabilityManager_HybridVentilation)
            || (type == IddObjectType::AvailabilityManager_NightVentilation)) {
          return false;
        }
      }
      return availabilityManagerAssignmentList().setAvailabilityManagers(availabilityManagers);
    }

    void PlantLoop_Impl::resetAvailabilityManagers() {
      availabilityManagerAssignmentList().resetAvailabilityManagers();
    }

    bool PlantLoop_Impl::removeAvailabilityManager(const AvailabilityManager& availabilityManager) {
      return availabilityManagerAssignmentList().removeAvailabilityManager(availabilityManager);
    }

    bool PlantLoop_Impl::removeAvailabilityManager(unsigned priority) {
      return availabilityManagerAssignmentList().removeAvailabilityManager(priority);
    }

    bool PlantLoop_Impl::setAvailabilityManagerPriority(const AvailabilityManager& availabilityManager, unsigned priority) {
      return availabilityManagerAssignmentList().setAvailabilityManagerPriority(availabilityManager, priority);
    }

    unsigned PlantLoop_Impl::availabilityManagerPriority(const AvailabilityManager& availabilityManager) const {
      return availabilityManagerAssignmentList().availabilityManagerPriority(availabilityManager);
    }

    bool PlantLoop_Impl::addSupplyBranchForComponent(HVACComponent hvacComponent) {
      if (hvacComponent.model() != model()) {
        return false;
      }
      if (!hvacComponent.optionalCast<StraightComponent>() && !hvacComponent.optionalCast<WaterToWaterComponent>()) {
        return false;
      }
      if (hvacComponent.optionalCast<StraightComponent>() && hvacComponent.loop()) {
        return false;
      }
      if (auto waterToWater = hvacComponent.optionalCast<WaterToWaterComponent>()) {
        if (waterToWater->plantLoop()) {
          return false;
        }
      }

      auto branchList = supplyBranchList();
      auto equipmentBranches = supplyEquipmentBranches();
      OS_ASSERT(!equipmentBranches.empty());
      auto splitter = supplySplitter().cast<ConnectorSplitter>();
      auto mixer = supplyMixer().cast<ConnectorMixer>();

      // A newly canonicalized loop starts with one empty equipment branch. Reuse
      // that branch instead of manufacturing a second branch the first time
      // equipment is added.
      if ((equipmentBranches.size() == 1u) && equipmentBranches.front().components().empty()) {
        auto node = model().getOrCreateTransientByName<Node>(equipmentBranches.front().nameString() + " Node");
        return hvacComponent.addToNode(node);
      }

      const auto insertIndex = static_cast<unsigned>(branchList.branches().size() - 1u);
      Branch branch(model());
      if (!branch.setName(getObject<PlantLoop>().nameString() + " Supply Branch " + std::to_string(static_cast<unsigned>(equipmentBranches.size() + 1u)))) {
        branch.setName(model().nextName(openstudio::IddObjectType::Branch, true));
      }
      if (!branchList.getImpl<detail::BranchList_Impl>()->insertBranch(insertIndex, branch)) {
        return false;
      }

      equipmentBranches = supplyEquipmentBranches();
      if (!syncConnectorPorts(splitter, mixer, supplyInletBranch(), supplyOutletBranch(), equipmentBranches)) {
        branchList.getImpl<detail::BranchList_Impl>()->removeBranch(branch);
        branch.remove();
        return false;
      }

      auto node = model().getOrCreateTransientByName<Node>(branch.nameString() + " Node");
      if (!hvacComponent.addToNode(node)) {
        branchList.getImpl<detail::BranchList_Impl>()->removeBranch(branch);
        syncConnectorPorts(splitter, mixer, supplyInletBranch(), supplyOutletBranch(), supplyEquipmentBranches());
        branch.remove();
        return false;
      }

      return true;
    }

    bool PlantLoop_Impl::removeSupplyBranchWithComponent(HVACComponent hvacComponent) {
      if (!supplyComponent(hvacComponent.handle())) {
        return false;
      }

      auto equipmentBranches = supplyEquipmentBranches();
      const auto targetComponent = hvacComponent.cast<ModelObject>();
      boost::optional<Branch> targetBranch;
      for (const auto& branch : equipmentBranches) {
        const auto components = branch.components();
        if (std::ranges::find(components, targetComponent) != components.end()) {
          targetBranch = branch;
          break;
        }
      }

      if (!targetBranch) {
        if (auto node = hvacComponent.optionalCast<Node>()) {
          auto branch = branchForNode(*node);
          if (branch && (std::ranges::find(equipmentBranches, *branch) != equipmentBranches.end())) {
            targetBranch = *branch;
          }
        }
      }

      if (!targetBranch) {
        return false;
      }

      const auto components = targetBranch->components();

      auto branchList = supplyBranchList();
      const bool keepAsDefaultBranch = (equipmentBranches.size() == 1u);
      auto splitter = supplySplitter().cast<ConnectorSplitter>();
      auto mixer = supplyMixer().cast<ConnectorMixer>();
      if (!keepAsDefaultBranch) {
        if (!branchList.getImpl<detail::BranchList_Impl>()->removeBranch(*targetBranch)) {
          return false;
        }
      }

      targetBranch->getImpl<openstudio::epmodel::detail::Branch_Impl>()->clearComponents();

      for (auto component : components) {
        if (auto straightComponent = component.optionalCast<StraightComponent>()) {
          straightComponent->disconnect();
        } else if (auto waterToWater = component.optionalCast<WaterToWaterComponent>()) {
          component.setPointer(waterToWater->supplyInletPort(), Handle());
          component.setPointer(waterToWater->supplyOutletPort(), Handle());
        } else {
          return false;
        }
      }

      if (!keepAsDefaultBranch) {
        targetBranch->remove();
      }

      if (!syncConnectorPorts(splitter, mixer, supplyInletBranch(), supplyOutletBranch(), supplyEquipmentBranches())) {
        return false;
      }

      if (!getObject<PlantLoop>().getModelObjectTarget<Node>(openstudio::PlantLoopFields::LoopTemperatureSetpointNodeName)) {
        OS_ASSERT(setPointer(openstudio::PlantLoopFields::LoopTemperatureSetpointNodeName, supplyOutletNode().handle(), false));
      }

      return true;
    }

    bool PlantLoop_Impl::addDemandBranchForComponent(HVACComponent hvacComponent, bool tertiary) {
      if (hvacComponent.model() != model()) {
        return false;
      }
      if (!hvacComponent.optionalCast<StraightComponent>() && !hvacComponent.optionalCast<CoilHeatingWater>()
          && !hvacComponent.optionalCast<CoilCoolingWater>() && !hvacComponent.optionalCast<WaterToWaterComponent>()) {
        return false;
      }
      if (auto waterToAir = hvacComponent.optionalCast<CoilHeatingWater>()) {
        if (tertiary || waterToAir->plantLoop()) {
          return false;
        }
      } else if (auto waterToAir = hvacComponent.optionalCast<CoilCoolingWater>()) {
        if (tertiary || waterToAir->plantLoop()) {
          return false;
        }
      }
      if (hvacComponent.optionalCast<StraightComponent>() && hvacComponent.loop()) {
        return false;
      }
      if (auto waterToWater = hvacComponent.optionalCast<WaterToWaterComponent>()) {
        if (tertiary) {
          if (waterToWater->tertiaryPlantLoop()) {
            return false;
          }
        }
      } else if (tertiary) {
        return false;
      }

      auto branchList = demandBranchList();
      auto equipmentBranches = demandEquipmentBranches();
      OS_ASSERT(!equipmentBranches.empty());
      auto splitter = demandSplitter().cast<ConnectorSplitter>();
      auto mixer = demandMixer().cast<ConnectorMixer>();

      // Mirror the supply-side behavior: the first real component should claim the
      // default empty equipment branch instead of forcing an unnecessary parallel
      // branch into existence.
      if ((equipmentBranches.size() == 1u) && equipmentBranches.front().components().empty()) {
        auto node = model().getOrCreateTransientByName<Node>(equipmentBranches.front().nameString() + " Node");
        if (tertiary) {
          return hvacComponent.cast<WaterToWaterComponent>().addToTertiaryNode(node);
        }
        return hvacComponent.addToNode(node);
      }

      const auto insertIndex = static_cast<unsigned>(branchList.branches().size() - 1u);
      Branch branch(model());
      if (!branch.setName(getObject<PlantLoop>().nameString() + " Demand Branch " + std::to_string(static_cast<unsigned>(equipmentBranches.size() + 1u)))) {
        branch.setName(model().nextName(openstudio::IddObjectType::Branch, true));
      }
      if (!branchList.getImpl<detail::BranchList_Impl>()->insertBranch(insertIndex, branch)) {
        return false;
      }

      equipmentBranches = demandEquipmentBranches();
      if (!syncConnectorPorts(splitter, mixer, demandInletBranch(), demandOutletBranch(), equipmentBranches)) {
        branchList.getImpl<detail::BranchList_Impl>()->removeBranch(branch);
        branch.remove();
        return false;
      }

      auto node = model().getOrCreateTransientByName<Node>(branch.nameString() + " Node");
      bool connected = false;
      if (tertiary) {
        connected = hvacComponent.cast<WaterToWaterComponent>().addToTertiaryNode(node);
      } else {
        connected = hvacComponent.addToNode(node);
      }
      if (!connected) {
        branchList.getImpl<detail::BranchList_Impl>()->removeBranch(branch);
        syncConnectorPorts(splitter, mixer, demandInletBranch(), demandOutletBranch(), demandEquipmentBranches());
        branch.remove();
        return false;
      }

      return true;
    }

    bool PlantLoop_Impl::removeDemandBranchWithComponent(HVACComponent hvacComponent) {
      if (!demandComponent(hvacComponent.handle())) {
        return false;
      }

      auto equipmentBranches = demandEquipmentBranches();
      const auto targetComponent = hvacComponent.cast<ModelObject>();
      boost::optional<Branch> targetBranch;
      for (const auto& branch : equipmentBranches) {
        const auto components = branch.components();
        if (std::ranges::find(components, targetComponent) != components.end()) {
          targetBranch = branch;
          break;
        }
      }

      if (!targetBranch) {
        if (auto node = hvacComponent.optionalCast<Node>()) {
          auto branch = branchForNode(*node);
          if (branch && (std::ranges::find(equipmentBranches, *branch) != equipmentBranches.end())) {
            targetBranch = *branch;
          }
        }
      }

      if (!targetBranch) {
        return false;
      }

      const auto components = targetBranch->components();

      auto branchList = demandBranchList();
      const bool keepAsDefaultBranch = (equipmentBranches.size() == 1u);
      auto splitter = demandSplitter().cast<ConnectorSplitter>();
      auto mixer = demandMixer().cast<ConnectorMixer>();

      for (auto component : components) {
        if (auto straightComponent = component.optionalCast<StraightComponent>()) {
          straightComponent->disconnect();
        } else if (auto waterToAir = component.optionalCast<CoilHeatingWater>()) {
          if (!waterToAir->removeFromPlantLoop()) {
            return false;
          }
          if (!waterToAir->airLoopHVAC()) {
            waterToAir->remove();
          }
        } else if (auto waterToAir = component.optionalCast<CoilCoolingWater>()) {
          if (!waterToAir->removeFromPlantLoop()) {
            return false;
          }
          if (!waterToAir->airLoopHVAC()) {
            waterToAir->remove();
          }
        } else if (auto waterToWater = component.optionalCast<WaterToWaterComponent>()) {
          if (auto tertiaryLoop = waterToWater->tertiaryPlantLoop(); tertiaryLoop && tertiaryLoop->handle() == getObject<PlantLoop>().handle()) {
            component.setPointer(waterToWater->tertiaryInletPort(), Handle());
            component.setPointer(waterToWater->tertiaryOutletPort(), Handle());
          } else {
            component.setPointer(waterToWater->demandInletPort(), Handle());
            component.setPointer(waterToWater->demandOutletPort(), Handle());
          }
        } else {
          return false;
        }
      }

      if (!keepAsDefaultBranch) {
        if (!branchList.getImpl<detail::BranchList_Impl>()->removeBranch(*targetBranch)) {
          return false;
        }
      }

      targetBranch->getImpl<openstudio::epmodel::detail::Branch_Impl>()->clearComponents();

      if (!keepAsDefaultBranch) {
        targetBranch->remove();
      }

      if (!syncConnectorPorts(splitter, mixer, demandInletBranch(), demandOutletBranch(), demandEquipmentBranches())) {
        return false;
      }

      if (!getObject<PlantLoop>().getModelObjectTarget<Node>(openstudio::PlantLoopFields::LoopTemperatureSetpointNodeName)) {
        OS_ASSERT(setPointer(openstudio::PlantLoopFields::LoopTemperatureSetpointNodeName, supplyOutletNode().handle(), false));
      }

      return true;
    }

    void PlantLoop_Impl::doCanonicalize(LoadContext& context) {
      auto plantLoop = getObject<PlantLoop>();
      OS_ASSERT(!plantLoop.nameString().empty());
      const auto loopName = plantLoop.nameString();

      // Canonical PlantLoop shape:
      // - each side has an inlet node and an outlet node on the PlantLoop object
      // - each side has a BranchList ordered as inlet branch, equipment branches,
      //   outlet branch
      // - each side has a splitter/mixer pair whose ports point at those branches
      //   in BranchList order
      //
      // This mirrors the baseline topology created by openstudio::model::PlantLoop:
      // inlet node -> splitter -> equipment branch region -> mixer -> outlet node.
      // Imported IDF can arrive in looser shapes, so canonicalization repairs it
      // into this form before normal API methods run.
      //
      // In particular:
      // - zero branches becomes one inlet branch, one equipment branch, one outlet branch
      // - one branch is treated as the equipment branch, with inlet/outlet added around it
      // - two branches are treated as parallel equipment branches, with inlet/outlet
      //   added around them
      // - three or more branches are interpreted as inlet / equipment... / outlet
      //
      // After this method returns, accessors and topology operations are allowed to
      // assume the repaired shape and assert on violations instead of carrying
      // defensive fallback logic.

      // Canonical topology anchor points.
      // These node references are the loop entry/exit contracts for plant
      // supply and demand traversal. Materialize them first so branch and
      // connector repair has stable anchors to attach to.
      getOrCreateTarget<Node>(openstudio::PlantLoopFields::PlantSideInletNodeName, loopName + " Supply Inlet Node");
      getOrCreateTarget<Node>(openstudio::PlantLoopFields::PlantSideOutletNodeName, loopName + " Supply Outlet Node");
      getOrCreateTarget<Node>(openstudio::PlantLoopFields::DemandSideInletNodeName, loopName + " Demand Inlet Node");
      getOrCreateTarget<Node>(openstudio::PlantLoopFields::DemandSideOutletNodeName, loopName + " Demand Outlet Node");

      // Plant-side BranchList is the E+ source-of-truth for branch order.
      // Keep the canonical inlet/equipment/outlet branch contract intact so
      // traversal and branch mutation can reason from stored branch order.
      const auto supplyBranchListName = loopName + " Supply Branch List";
      auto supplyBranchListTarget = getOrCreateTarget<BranchList>(openstudio::PlantLoopFields::PlantSideBranchListName, supplyBranchListName);
      if (supplyBranchListTarget.nameString().empty()) {
        supplyBranchListTarget.setName(supplyBranchListName);
      }

      auto supplyBranchListImpl = supplyBranchListTarget.getImpl<detail::BranchList_Impl>();

      auto supplyBranches = supplyBranchListTarget.branches();
      if (supplyBranches.empty()) {
        Branch inletBranch(model());
        if (!inletBranch.setName(loopName + " Supply Inlet Branch")) {
          inletBranch.setName(model().nextName(openstudio::IddObjectType::Branch, true));
        }
        supplyBranchListImpl->addBranch(inletBranch);

        Branch equipmentBranch(model());
        if (!equipmentBranch.setName(loopName + " Supply Branch 1")) {
          equipmentBranch.setName(model().nextName(openstudio::IddObjectType::Branch, true));
        }
        supplyBranchListImpl->addBranch(equipmentBranch);

        Branch outletBranch(model());
        if (!outletBranch.setName(loopName + " Supply Outlet Branch")) {
          outletBranch.setName(model().nextName(openstudio::IddObjectType::Branch, true));
        }
        supplyBranchListImpl->addBranch(outletBranch);
        detail::addLoadInfo(context, "Created canonical plant-side branches for PlantLoop '" + loopName + "'.");
        supplyBranches = supplyBranchListTarget.branches();
      } else if (supplyBranches.size() == 1u) {
        Branch inletBranch(model());
        if (!inletBranch.setName(loopName + " Supply Inlet Branch")) {
          inletBranch.setName(model().nextName(openstudio::IddObjectType::Branch, true));
        }
        supplyBranchListImpl->insertBranch(0u, inletBranch);

        Branch outletBranch(model());
        if (!outletBranch.setName(loopName + " Supply Outlet Branch")) {
          outletBranch.setName(model().nextName(openstudio::IddObjectType::Branch, true));
        }
        supplyBranchListImpl->addBranch(outletBranch);
        detail::addLoadWarning(context,
                               "Plant-side BranchList for PlantLoop '" + loopName + "' only had one branch. Treated it as the equipment branch and added inlet and outlet branches.");
        supplyBranches = supplyBranchListTarget.branches();
      } else if (supplyBranches.size() == 2u) {
        Branch inletBranch(model());
        if (!inletBranch.setName(loopName + " Supply Inlet Branch")) {
          inletBranch.setName(model().nextName(openstudio::IddObjectType::Branch, true));
        }
        supplyBranchListImpl->insertBranch(0u, inletBranch);

        Branch outletBranch(model());
        if (!outletBranch.setName(loopName + " Supply Outlet Branch")) {
          outletBranch.setName(model().nextName(openstudio::IddObjectType::Branch, true));
        }
        supplyBranchListImpl->addBranch(outletBranch);
        detail::addLoadWarning(context,
                               "Plant-side BranchList for PlantLoop '" + loopName
                                 + "' only had two branches. Preserved both as parallel equipment branches and added inlet and outlet branches.");
        supplyBranches = supplyBranchListTarget.branches();
      }

      if (supplyBranches.front().nameString().empty()) {
        supplyBranches.front().setName(loopName + " Supply Inlet Branch");
      }
      if (supplyBranches.back().nameString().empty()) {
        supplyBranches.back().setName(loopName + " Supply Outlet Branch");
      }
      for (unsigned i = 1u; i + 1u < supplyBranches.size(); ++i) {
        if (supplyBranches[i].nameString().empty()) {
          supplyBranches[i].setName(loopName + " Supply Branch " + std::to_string(i));
        }
      }

      // Demand-side BranchList mirrors the same inlet/equipment/outlet contract.
      // Demand topology uses separate branch storage but the same traversal
      // assumptions as plant side.
      const auto demandBranchListName = loopName + " Demand Branch List";
      auto demandBranchListTarget = getOrCreateTarget<BranchList>(openstudio::PlantLoopFields::DemandSideBranchListName, demandBranchListName);
      if (demandBranchListTarget.nameString().empty()) {
        demandBranchListTarget.setName(demandBranchListName);
      }

      auto demandBranchListImpl = demandBranchListTarget.getImpl<detail::BranchList_Impl>();

      auto demandBranches = demandBranchListTarget.branches();
      if (demandBranches.empty()) {
        Branch inletBranch(model());
        if (!inletBranch.setName(loopName + " Demand Inlet Branch")) {
          inletBranch.setName(model().nextName(openstudio::IddObjectType::Branch, true));
        }
        demandBranchListImpl->addBranch(inletBranch);

        Branch equipmentBranch(model());
        if (!equipmentBranch.setName(loopName + " Demand Branch 1")) {
          equipmentBranch.setName(model().nextName(openstudio::IddObjectType::Branch, true));
        }
        demandBranchListImpl->addBranch(equipmentBranch);

        Branch outletBranch(model());
        if (!outletBranch.setName(loopName + " Demand Outlet Branch")) {
          outletBranch.setName(model().nextName(openstudio::IddObjectType::Branch, true));
        }
        demandBranchListImpl->addBranch(outletBranch);
        detail::addLoadInfo(context, "Created canonical demand-side branches for PlantLoop '" + loopName + "'.");
        demandBranches = demandBranchListTarget.branches();
      } else if (demandBranches.size() == 1u) {
        Branch inletBranch(model());
        if (!inletBranch.setName(loopName + " Demand Inlet Branch")) {
          inletBranch.setName(model().nextName(openstudio::IddObjectType::Branch, true));
        }
        demandBranchListImpl->insertBranch(0u, inletBranch);

        Branch outletBranch(model());
        if (!outletBranch.setName(loopName + " Demand Outlet Branch")) {
          outletBranch.setName(model().nextName(openstudio::IddObjectType::Branch, true));
        }
        demandBranchListImpl->addBranch(outletBranch);
        detail::addLoadWarning(context,
                               "Demand-side BranchList for PlantLoop '" + loopName + "' only had one branch. Treated it as the equipment branch and added inlet and outlet branches.");
        demandBranches = demandBranchListTarget.branches();
      } else if (demandBranches.size() == 2u) {
        Branch inletBranch(model());
        if (!inletBranch.setName(loopName + " Demand Inlet Branch")) {
          inletBranch.setName(model().nextName(openstudio::IddObjectType::Branch, true));
        }
        demandBranchListImpl->insertBranch(0u, inletBranch);

        Branch outletBranch(model());
        if (!outletBranch.setName(loopName + " Demand Outlet Branch")) {
          outletBranch.setName(model().nextName(openstudio::IddObjectType::Branch, true));
        }
        demandBranchListImpl->addBranch(outletBranch);
        detail::addLoadWarning(context,
                               "Demand-side BranchList for PlantLoop '" + loopName
                                 + "' only had two branches. Preserved both as parallel equipment branches and added inlet and outlet branches.");
        demandBranches = demandBranchListTarget.branches();
      }

      if (demandBranches.front().nameString().empty()) {
        demandBranches.front().setName(loopName + " Demand Inlet Branch");
      }
      if (demandBranches.back().nameString().empty()) {
        demandBranches.back().setName(loopName + " Demand Outlet Branch");
      }
      for (unsigned i = 1u; i + 1u < demandBranches.size(); ++i) {
        if (demandBranches[i].nameString().empty()) {
          demandBranches[i].setName(loopName + " Demand Branch " + std::to_string(i));
        }
      }

      // Canonicalize the branch rows first so the branch names are stable
      // before we materialize the empty equipment-branch nodes that the
      // connector paths expect to exist.
      auto supplyBranchListObject = supplyBranchList();
      for (const auto& branch : supplyBranchListObject.branches()) {
        if (auto branchImpl = branch.getImpl<openstudio::epmodel::detail::Branch_Impl>()) {
          branchImpl->canonicalize(context);
        }
      }

      for (const auto& branch : supplyEquipmentBranches()) {
        if (branch.components().empty()) {
          model().getOrCreateTransientByName<Node>(branch.nameString() + " Node");
        }
      }

      auto demandBranchListObject = demandBranchList();
      for (const auto& branch : demandBranchListObject.branches()) {
        if (auto branchImpl = branch.getImpl<openstudio::epmodel::detail::Branch_Impl>()) {
          branchImpl->canonicalize(context);
        }
      }

      for (const auto& branch : demandEquipmentBranches()) {
        if (branch.components().empty()) {
          model().getOrCreateTransientByName<Node>(branch.nameString() + " Node");
        }
      }

      // Plant-side splitter/mixer pair are keyed by inlet/outlet branches.
      // These connector objects are the fan-out/fan-in connective tissue for
      // the canonical plant-side equipment branches.
      const auto supplyInletBranchRef = supplyInletBranch();
      const auto supplyOutletBranchRef = supplyOutletBranch();
      const auto supplyEquipmentBranchRefs = supplyEquipmentBranches();

      boost::optional<ConnectorSplitter> supplySplitterObject;
      for (const auto& candidate : model().getConcreteModelObjects<ConnectorSplitter>()) {
        auto inlet = candidate.getModelObjectTarget<Branch>(candidate.inletPort());
        if (!inlet || !(*inlet == supplyInletBranchRef)) {
          continue;
        }

        if (candidate.nextBranchIndex() != supplyEquipmentBranchRefs.size()) {
          continue;
        }

        bool allOutletsMatch = true;
        for (unsigned i = 0; i < supplyEquipmentBranchRefs.size(); ++i) {
          auto branch = candidate.getModelObjectTarget<Branch>(candidate.outletPort(i));
          if (!branch || !(*branch == supplyEquipmentBranchRefs[i])) {
            allOutletsMatch = false;
            break;
          }
        }

        if (allOutletsMatch) {
          supplySplitterObject = candidate;
          break;
        }
      }
      if (!supplySplitterObject) {
        supplySplitterObject = ConnectorSplitter(model());
        supplySplitterObject->setName(loopName + " Supply Splitter");
        detail::addLoadInfo(context,
                            "Created missing plant-side Connector:Splitter '" + supplySplitterObject->nameString() + "' for PlantLoop '" + loopName + "'.");
      }

      boost::optional<ConnectorMixer> supplyMixerObject;
      for (const auto& candidate : model().getConcreteModelObjects<ConnectorMixer>()) {
        auto outlet = candidate.getModelObjectTarget<Branch>(candidate.outletPort());
        if (!outlet || !(*outlet == supplyOutletBranchRef)) {
          continue;
        }

        if (candidate.nextBranchIndex() != supplyEquipmentBranchRefs.size()) {
          continue;
        }

        bool allInletsMatch = true;
        for (unsigned i = 0; i < supplyEquipmentBranchRefs.size(); ++i) {
          auto branch = candidate.getModelObjectTarget<Branch>(candidate.inletPort(i));
          if (!branch || !(*branch == supplyEquipmentBranchRefs[i])) {
            allInletsMatch = false;
            break;
          }
        }

        if (allInletsMatch) {
          supplyMixerObject = candidate;
          break;
        }
      }
      if (!supplyMixerObject) {
        supplyMixerObject = ConnectorMixer(model());
        supplyMixerObject->setName(loopName + " Supply Mixer");
        detail::addLoadInfo(context,
                            "Created missing plant-side Connector:Mixer '" + supplyMixerObject->nameString() + "' for PlantLoop '" + loopName + "'.");
      }

      if ((supplySplitterObject->nextBranchIndex() != supplyEquipmentBranchRefs.size())
          || (supplyMixerObject->nextBranchIndex() != supplyEquipmentBranchRefs.size())) {
        detail::addLoadWarning(context,
                               "Plant-side connector port count mismatch for PlantLoop '" + loopName + "'. Rebuilding ports from BranchList order.");
      }

      OS_ASSERT(syncConnectorPorts(*supplySplitterObject, *supplyMixerObject, supplyInletBranchRef, supplyOutletBranchRef, supplyEquipmentBranchRefs));

      // Demand-side splitter/mixer pair mirror the same branch contract.
      // Keep the branch ports synchronized to the BranchList instead of
      // letting connector extensibles become an independent source of truth.
      const auto demandInletBranchRef = demandInletBranch();
      const auto demandOutletBranchRef = demandOutletBranch();
      const auto demandEquipmentBranchRefs = demandEquipmentBranches();

      boost::optional<ConnectorSplitter> demandSplitterObject;
      for (const auto& candidate : model().getConcreteModelObjects<ConnectorSplitter>()) {
        auto inlet = candidate.getModelObjectTarget<Branch>(candidate.inletPort());
        if (!inlet || !(*inlet == demandInletBranchRef)) {
          continue;
        }

        if (candidate.nextBranchIndex() != demandEquipmentBranchRefs.size()) {
          continue;
        }

        bool allOutletsMatch = true;
        for (unsigned i = 0; i < demandEquipmentBranchRefs.size(); ++i) {
          auto branch = candidate.getModelObjectTarget<Branch>(candidate.outletPort(i));
          if (!branch || !(*branch == demandEquipmentBranchRefs[i])) {
            allOutletsMatch = false;
            break;
          }
        }

        if (allOutletsMatch) {
          demandSplitterObject = candidate;
          break;
        }
      }
      if (!demandSplitterObject) {
        demandSplitterObject = ConnectorSplitter(model());
        demandSplitterObject->setName(loopName + " Demand Splitter");
        detail::addLoadInfo(context,
                            "Created missing demand-side Connector:Splitter '" + demandSplitterObject->nameString() + "' for PlantLoop '" + loopName + "'.");
      }

      boost::optional<ConnectorMixer> demandMixerObject;
      for (const auto& candidate : model().getConcreteModelObjects<ConnectorMixer>()) {
        auto outlet = candidate.getModelObjectTarget<Branch>(candidate.outletPort());
        if (!outlet || !(*outlet == demandOutletBranchRef)) {
          continue;
        }

        if (candidate.nextBranchIndex() != demandEquipmentBranchRefs.size()) {
          continue;
        }

        bool allInletsMatch = true;
        for (unsigned i = 0; i < demandEquipmentBranchRefs.size(); ++i) {
          auto branch = candidate.getModelObjectTarget<Branch>(candidate.inletPort(i));
          if (!branch || !(*branch == demandEquipmentBranchRefs[i])) {
            allInletsMatch = false;
            break;
          }
        }

        if (allInletsMatch) {
          demandMixerObject = candidate;
          break;
        }
      }
      if (!demandMixerObject) {
        demandMixerObject = ConnectorMixer(model());
        demandMixerObject->setName(loopName + " Demand Mixer");
        detail::addLoadInfo(context,
                            "Created missing demand-side Connector:Mixer '" + demandMixerObject->nameString() + "' for PlantLoop '" + loopName + "'.");
      }

      if ((demandSplitterObject->nextBranchIndex() != demandEquipmentBranchRefs.size())
          || (demandMixerObject->nextBranchIndex() != demandEquipmentBranchRefs.size())) {
        detail::addLoadWarning(context,
                               "Demand-side connector port count mismatch for PlantLoop '" + loopName + "'. Rebuilding ports from BranchList order.");
      }

      OS_ASSERT(syncConnectorPorts(*demandSplitterObject, *demandMixerObject, demandInletBranchRef, demandOutletBranchRef, demandEquipmentBranchRefs));

      // PlantLoop owns one canonical setpoint anchor, one sizing object, and
      // one availability-manager assignment list. Create or repair them here so
      // the public loop-facing APIs can trust that these relationships exist.
      if (auto setpointNode = plantLoop.getModelObjectTarget<Node>(openstudio::PlantLoopFields::LoopTemperatureSetpointNodeName)) {
        (void)setpointNode;
      } else {
        const auto originalSetpointNodeName = plantLoop.getString(openstudio::PlantLoopFields::LoopTemperatureSetpointNodeName);
        bool repairedByName = false;
        if (originalSetpointNodeName && !originalSetpointNodeName->empty()) {
          for (const auto& candidate : model().getObjectsByName(*originalSetpointNodeName, true, true)) {
            if (auto node = candidate.optionalCast<Node>()) {
              OS_ASSERT(setPointer(openstudio::PlantLoopFields::LoopTemperatureSetpointNodeName, node->handle(), false));
              detail::addLoadWarning(context,
                                     "Recovered Loop Temperature Setpoint Node for PlantLoop '" + loopName + "' by matching Node '"
                                       + node->nameString() + "' by name.");
              repairedByName = true;
              break;
            }
          }
        }

        if (!repairedByName) {
          OS_ASSERT(setPointer(openstudio::PlantLoopFields::LoopTemperatureSetpointNodeName, supplyOutletNode().handle(), false));
          if (originalSetpointNodeName && !originalSetpointNodeName->empty()) {
            detail::addLoadWarning(context,
                                   "PlantLoop '" + loopName + "' had an invalid Loop Temperature Setpoint Node reference. Reset it to the supply outlet node.");
          } else {
            detail::addLoadInfo(context,
                                "Created default Loop Temperature Setpoint Node reference for PlantLoop '" + loopName + "' on the supply outlet node.");
          }
        }
      }

      std::vector<SizingPlant> sizingPlantsForLoop;
      for (const auto& candidate : model().getConcreteModelObjects<SizingPlant>()) {
        auto ownedLoop = candidate.getModelObjectTarget<PlantLoop>(openstudio::Sizing_PlantFields::PlantorCondenserLoopName);
        if (ownedLoop && (*ownedLoop == plantLoop)) {
          sizingPlantsForLoop.push_back(candidate);
        }
      }

      if (sizingPlantsForLoop.empty()) {
        SizingPlant sizingPlant(model(), plantLoop);
        if (!sizingPlant.setName(loopName + " Sizing Plant")) {
          sizingPlant.setName(model().nextName(openstudio::IddObjectType::Sizing_Plant, true));
        }
        detail::addLoadInfo(context, "Created missing Sizing:Plant '" + sizingPlant.nameString() + "' for PlantLoop '" + loopName + "'.");
      } else if (sizingPlantsForLoop.size() > 1u) {
        for (unsigned i = 1u; i < sizingPlantsForLoop.size(); ++i) {
          OS_ASSERT(sizingPlantsForLoop[i].setString(openstudio::Sizing_PlantFields::PlantorCondenserLoopName, ""));
        }
        detail::addLoadWarning(context,
                               "PlantLoop '" + loopName + "' had multiple Sizing:Plant objects attached. Kept '"
                                 + sizingPlantsForLoop.front().nameString() + "' and detached the extras.");
      }

      auto assignmentList =
        getOrCreateTarget<AvailabilityManagerAssignmentList>(openstudio::PlantLoopFields::AvailabilityManagerListName, loopName + " Availability Manager List");
      if (assignmentList.nameString().empty()) {
        assignmentList.setName(loopName + " Availability Manager List");
      }
      assignmentList.getImpl<detail::AvailabilityManagerAssignmentList_Impl>()->canonicalize(context);

      auto operationSchemes = getOrCreateTarget<PlantEquipmentOperationSchemes>(openstudio::PlantLoopFields::PlantEquipmentOperationSchemeName,
                                                                                loopName + " Operation Schemes");
      if (operationSchemes.nameString().empty()) {
        operationSchemes.setName(loopName + " Operation Schemes");
      }
      operationSchemes.getImpl<detail::PlantEquipmentOperationSchemes_Impl>()->canonicalize(context);

    }

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
