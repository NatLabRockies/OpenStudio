/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "Loop/PlantLoop.hpp"
#include "Loop/PlantLoop_Impl.hpp"

#include "Model.hpp"
#include "StraightComponent/Node.hpp"
#include "ModelObject/Branch.hpp"
#include "ModelObject/Branch_Impl.hpp"
#include "ModelObject/BranchList.hpp"
#include "ModelObject/BranchList_Impl.hpp"
#include "Mixer/ConnectorMixer.hpp"
#include "Mixer/ConnectorMixer_Impl.hpp"
#include "HVACComponent/HVACComponent.hpp"
#include "ModelObject.hpp"
#include "HVACComponent/Splitter.hpp"
#include "Splitter/ConnectorSplitter.hpp"
#include "Splitter/ConnectorSplitter_Impl.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <algorithm>
#include <set>

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/OS_PlantLoop_FieldEnums.hxx>
#include <utilities/idd/PlantLoop_FieldEnums.hxx>

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

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

    // PlantLoop stores its topology in EnergyPlus branch/connective-tissue objects,
    // but the API we are trying to preserve is the higher-level OpenStudio loop API.
    // This helper keeps the two representations aligned after canonicalization and
    // after branch edits. The BranchList is the source of truth: one inlet branch,
    // one or more equipment branches in the middle, and one outlet branch. The
    // splitter and mixer are rebuilt to match that ordering exactly.
    bool PlantLoop_Impl::syncConnectorPorts(Splitter& splitter, Mixer& mixer, const Branch& inletBranch, const Branch& outletBranch,
                                            const std::vector<Branch>& equipmentBranches) const {
      auto splitterImpl = splitter.getImpl<openstudio::epmodel::detail::ConnectorSplitter_Impl>();
      auto mixerImpl = mixer.getImpl<openstudio::epmodel::detail::ConnectorMixer_Impl>();
      OS_ASSERT(splitterImpl);
      OS_ASSERT(mixerImpl);

      if (!splitterImpl->setInletBranch(inletBranch)) {
        return false;
      }
      if (!mixerImpl->setOutletBranch(outletBranch)) {
        return false;
      }

      while (splitter.outletModelObjects().size() > equipmentBranches.size()) {
        splitter.removePortForBranch(static_cast<unsigned>(splitter.outletModelObjects().size() - 1u));
      }
      while (mixer.inletModelObjects().size() > equipmentBranches.size()) {
        mixer.removePortForBranch(static_cast<unsigned>(mixer.inletModelObjects().size() - 1u));
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

      const auto branchContainsNode = [&](const Branch& branch, bool isInletBranch, bool isOutletBranch, bool isEquipmentBranch) {
        const auto components = branch.components();
        if (components.empty()) {
          if (isEquipmentBranch) {
            return model().getOrCreateTransientByName<Node>(branch.nameString() + " Node") == node;
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
      };

      if (branchContainsNode(inletBranch, true, false, false)) {
        return inletBranch;
      }

      for (const auto& branch : equipmentBranches) {
        if (branchContainsNode(branch, false, false, true)) {
          return branch;
        }
      }

      if (branchContainsNode(outletBranch, false, true, false)) {
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

      const auto branchContainsNode = [&](const Branch& branch, bool isInletBranch, bool isOutletBranch, bool isEquipmentBranch) {
        const auto components = branch.components();
        if (components.empty()) {
          if (isEquipmentBranch) {
            return model().getOrCreateTransientByName<Node>(branch.nameString() + " Node") == node;
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
      };

      if (branchContainsNode(inletBranch, true, false, false)) {
        return inletBranch;
      }

      for (const auto& branch : equipmentBranches) {
        if (branchContainsNode(branch, false, false, true)) {
          return branch;
        }
      }

      if (branchContainsNode(outletBranch, false, true, false)) {
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
        auto inletObject = splitter.inletModelObject();
        auto inlet = inletObject ? inletObject->optionalCast<Branch>() : boost::none;
        if (!inlet || !(*inlet == inletBranch)) {
          continue;
        }

        const auto outletObjects = splitter.outletModelObjects();
        if (outletObjects.size() != equipmentBranches.size()) {
          continue;
        }

        bool allOutletsMatch = true;
        for (unsigned i = 0; i < equipmentBranches.size(); ++i) {
          auto branch = outletObjects[i].optionalCast<Branch>();
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
        auto outletObject = mixer.outletModelObject();
        auto outlet = outletObject ? outletObject->optionalCast<Branch>() : boost::none;
        if (!outlet || !(*outlet == outletBranch)) {
          continue;
        }

        const auto inletObjects = mixer.inletModelObjects();
        if (inletObjects.size() != equipmentBranches.size()) {
          continue;
        }

        bool allInletsMatch = true;
        for (unsigned i = 0; i < equipmentBranches.size(); ++i) {
          auto branch = inletObjects[i].optionalCast<Branch>();
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
        auto inletObject = splitter.inletModelObject();
        auto inlet = inletObject ? inletObject->optionalCast<Branch>() : boost::none;
        if (!inlet || !(*inlet == inletBranch)) {
          continue;
        }

        const auto outletObjects = splitter.outletModelObjects();
        if (outletObjects.size() != equipmentBranches.size()) {
          continue;
        }

        bool allOutletsMatch = true;
        for (unsigned i = 0; i < equipmentBranches.size(); ++i) {
          auto branch = outletObjects[i].optionalCast<Branch>();
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
        auto outletObject = mixer.outletModelObject();
        auto outlet = outletObject ? outletObject->optionalCast<Branch>() : boost::none;
        if (!outlet || !(*outlet == outletBranch)) {
          continue;
        }

        const auto inletObjects = mixer.inletModelObjects();
        if (inletObjects.size() != equipmentBranches.size()) {
          continue;
        }

        bool allInletsMatch = true;
        for (unsigned i = 0; i < equipmentBranches.size(); ++i) {
          auto branch = inletObjects[i].optionalCast<Branch>();
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
        const auto components = branch.components();
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
        const auto components = branch.components();
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
        const auto components = branch.components();
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
        const auto components = branch.components();
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
        const auto components = branch.components();
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
        const auto components = branch.components();
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

    bool PlantLoop_Impl::addSupplyBranchForComponent(HVACComponent hvacComponent) {
      if (hvacComponent.model() != model()) {
        return false;
      }
      if (!hvacComponent.optionalCast<StraightComponent>()) {
        return false;
      }
      if (hvacComponent.loop()) {
        return false;
      }

      auto branchList = supplyBranchList();
      auto equipmentBranches = supplyEquipmentBranches();
      OS_ASSERT(!equipmentBranches.empty());

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

      auto splitter = supplySplitter();
      auto mixer = supplyMixer();
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
      boost::optional<Branch> targetBranch;
      for (const auto& branch : equipmentBranches) {
        const auto components = branch.components();
        if (std::ranges::find_if(components, [&](const auto& component) { return component.handle() == hvacComponent.handle(); }) != components.end()) {
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
      for (const auto& component : components) {
        auto straightComponent = component.optionalCast<StraightComponent>();
        if (!straightComponent) {
          return false;
        }
      }

      auto branchList = supplyBranchList();
      const bool keepAsDefaultBranch = (equipmentBranches.size() == 1u);
      if (!keepAsDefaultBranch) {
        if (!branchList.getImpl<detail::BranchList_Impl>()->removeBranch(*targetBranch)) {
          return false;
        }
      }

      targetBranch->getImpl<openstudio::epmodel::detail::Branch_Impl>()->clearComponents();

      for (const auto& component : components) {
        auto straightComponent = component.cast<StraightComponent>();
        straightComponent.disconnect();
      }

      auto splitter = supplySplitter();
      auto mixer = supplyMixer();
      if (!keepAsDefaultBranch) {
        targetBranch->remove();
      }
      return syncConnectorPorts(splitter, mixer, supplyInletBranch(), supplyOutletBranch(), supplyEquipmentBranches());
    }

    bool PlantLoop_Impl::addDemandBranchForComponent(HVACComponent hvacComponent, bool tertiary) {
      if (tertiary) {
        return false;
      }
      if (hvacComponent.model() != model()) {
        return false;
      }
      if (!hvacComponent.optionalCast<StraightComponent>()) {
        return false;
      }
      if (hvacComponent.loop()) {
        return false;
      }

      auto branchList = demandBranchList();
      auto equipmentBranches = demandEquipmentBranches();
      OS_ASSERT(!equipmentBranches.empty());

      // Mirror the supply-side behavior: the first real component should claim the
      // default empty equipment branch instead of forcing an unnecessary parallel
      // branch into existence.
      if ((equipmentBranches.size() == 1u) && equipmentBranches.front().components().empty()) {
        auto node = model().getOrCreateTransientByName<Node>(equipmentBranches.front().nameString() + " Node");
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

      auto splitter = demandSplitter();
      auto mixer = demandMixer();
      equipmentBranches = demandEquipmentBranches();
      if (!syncConnectorPorts(splitter, mixer, demandInletBranch(), demandOutletBranch(), equipmentBranches)) {
        branchList.getImpl<detail::BranchList_Impl>()->removeBranch(branch);
        branch.remove();
        return false;
      }

      auto node = model().getOrCreateTransientByName<Node>(branch.nameString() + " Node");
      if (!hvacComponent.addToNode(node)) {
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
      boost::optional<Branch> targetBranch;
      for (const auto& branch : equipmentBranches) {
        const auto components = branch.components();
        if (std::ranges::find_if(components, [&](const auto& component) { return component.handle() == hvacComponent.handle(); }) != components.end()) {
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
      for (const auto& component : components) {
        auto straightComponent = component.optionalCast<StraightComponent>();
        if (!straightComponent) {
          return false;
        }
      }

      auto branchList = demandBranchList();
      const bool keepAsDefaultBranch = (equipmentBranches.size() == 1u);
      if (!keepAsDefaultBranch) {
        if (!branchList.getImpl<detail::BranchList_Impl>()->removeBranch(*targetBranch)) {
          return false;
        }
      }

      targetBranch->getImpl<openstudio::epmodel::detail::Branch_Impl>()->clearComponents();

      for (const auto& component : components) {
        auto straightComponent = component.cast<StraightComponent>();
        straightComponent.disconnect();
      }

      auto splitter = demandSplitter();
      auto mixer = demandMixer();
      if (!keepAsDefaultBranch) {
        targetBranch->remove();
      }
      return syncConnectorPorts(splitter, mixer, demandInletBranch(), demandOutletBranch(), demandEquipmentBranches());
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

      // Plant-side splitter/mixer pair are keyed by inlet/outlet branches.
      // These connector objects are the fan-out/fan-in connective tissue for
      // the canonical plant-side equipment branches.
      const auto supplyInletBranchRef = supplyInletBranch();
      const auto supplyOutletBranchRef = supplyOutletBranch();
      const auto supplyEquipmentBranchRefs = supplyEquipmentBranches();

      boost::optional<ConnectorSplitter> supplySplitterObject;
      for (const auto& candidate : model().getConcreteModelObjects<ConnectorSplitter>()) {
        auto inletObject = candidate.inletModelObject();
        auto inlet = inletObject ? inletObject->optionalCast<Branch>() : boost::none;
        if (!inlet || !(*inlet == supplyInletBranchRef)) {
          continue;
        }

        const auto outletObjects = candidate.outletModelObjects();
        if (outletObjects.size() != supplyEquipmentBranchRefs.size()) {
          continue;
        }

        bool allOutletsMatch = true;
        for (unsigned i = 0; i < supplyEquipmentBranchRefs.size(); ++i) {
          auto branch = outletObjects[i].optionalCast<Branch>();
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
        auto outletObject = candidate.outletModelObject();
        auto outlet = outletObject ? outletObject->optionalCast<Branch>() : boost::none;
        if (!outlet || !(*outlet == supplyOutletBranchRef)) {
          continue;
        }

        const auto inletObjects = candidate.inletModelObjects();
        if (inletObjects.size() != supplyEquipmentBranchRefs.size()) {
          continue;
        }

        bool allInletsMatch = true;
        for (unsigned i = 0; i < supplyEquipmentBranchRefs.size(); ++i) {
          auto branch = inletObjects[i].optionalCast<Branch>();
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

      if ((supplySplitterObject->outletModelObjects().size() != supplyEquipmentBranchRefs.size())
          || (supplyMixerObject->inletModelObjects().size() != supplyEquipmentBranchRefs.size())) {
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
        auto inletObject = candidate.inletModelObject();
        auto inlet = inletObject ? inletObject->optionalCast<Branch>() : boost::none;
        if (!inlet || !(*inlet == demandInletBranchRef)) {
          continue;
        }

        const auto outletObjects = candidate.outletModelObjects();
        if (outletObjects.size() != demandEquipmentBranchRefs.size()) {
          continue;
        }

        bool allOutletsMatch = true;
        for (unsigned i = 0; i < demandEquipmentBranchRefs.size(); ++i) {
          auto branch = outletObjects[i].optionalCast<Branch>();
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
        auto outletObject = candidate.outletModelObject();
        auto outlet = outletObject ? outletObject->optionalCast<Branch>() : boost::none;
        if (!outlet || !(*outlet == demandOutletBranchRef)) {
          continue;
        }

        const auto inletObjects = candidate.inletModelObjects();
        if (inletObjects.size() != demandEquipmentBranchRefs.size()) {
          continue;
        }

        bool allInletsMatch = true;
        for (unsigned i = 0; i < demandEquipmentBranchRefs.size(); ++i) {
          auto branch = inletObjects[i].optionalCast<Branch>();
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

      if ((demandSplitterObject->outletModelObjects().size() != demandEquipmentBranchRefs.size())
          || (demandMixerObject->inletModelObjects().size() != demandEquipmentBranchRefs.size())) {
        detail::addLoadWarning(context,
                               "Demand-side connector port count mismatch for PlantLoop '" + loopName + "'. Rebuilding ports from BranchList order.");
      }

      OS_ASSERT(syncConnectorPorts(*demandSplitterObject, *demandMixerObject, demandInletBranchRef, demandOutletBranchRef, demandEquipmentBranchRefs));

      // Canonicalize plant-side branches and materialize default empty-branch nodes.
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

      // Canonicalize demand-side branches and materialize default empty-branch nodes.
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
    }

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
