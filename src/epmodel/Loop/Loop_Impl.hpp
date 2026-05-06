/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_LOOP_IMPL_HPP
#define EPMODEL_LOOP_IMPL_HPP

#include "ParentObject/ParentObject_Impl.hpp"
#include "Model.hpp"
#include "ModelObject.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idf/Handle.hpp>

namespace openstudio {
class AppGFuelType;
class ComponentType;
class FuelType;
struct IddObjectType;
class IdfObject;

namespace epmodel {
  class HVACComponent;
  class Mixer;
  class Model;
  class ModelObject;
  class Node;
  class NodeList;
  class Splitter;

  namespace detail {

    class EPMODEL_API Loop_Impl : public ParentObject_Impl
    {
     public:
      using ParentObject_Impl::ParentObject_Impl;
      virtual ~Loop_Impl() override = default;

      virtual openstudio::epmodel::Node supplyInletNode() const;
      virtual openstudio::epmodel::Node supplyOutletNode() const;
      virtual std::vector<openstudio::epmodel::Node> supplyOutletNodes() const;
      virtual openstudio::epmodel::Node demandInletNode() const;
      virtual openstudio::epmodel::Node demandOutletNode() const;
      virtual std::vector<openstudio::epmodel::Node> demandInletNodes() const;

      virtual std::vector<openstudio::epmodel::ModelObject> supplyComponents(const openstudio::epmodel::HVACComponent& inletComp,
                                                                             const openstudio::epmodel::HVACComponent& outletComp,
                                                                             openstudio::IddObjectType type) const;
      virtual std::vector<openstudio::epmodel::ModelObject> supplyComponents(openstudio::IddObjectType type) const;
      virtual std::vector<openstudio::epmodel::ModelObject> demandComponents(const openstudio::epmodel::HVACComponent& inletComp,
                                                                             const openstudio::epmodel::HVACComponent& outletComp,
                                                                             openstudio::IddObjectType type) const;
      virtual std::vector<openstudio::epmodel::ModelObject> demandComponents(openstudio::IddObjectType type) const;
      virtual std::vector<openstudio::epmodel::ModelObject> components(openstudio::IddObjectType type) const;
      std::vector<openstudio::epmodel::ModelObject> components(const openstudio::epmodel::HVACComponent& inletComp,
                                                               const openstudio::epmodel::HVACComponent& outletComp, openstudio::IddObjectType type);

      virtual boost::optional<openstudio::epmodel::ModelObject> component(openstudio::Handle handle) const;
      virtual boost::optional<openstudio::epmodel::ModelObject> demandComponent(openstudio::Handle handle) const;
      virtual boost::optional<openstudio::epmodel::ModelObject> supplyComponent(openstudio::Handle handle) const;

      virtual std::vector<openstudio::IdfObject> remove() override;
      virtual openstudio::epmodel::Splitter demandSplitter() const;
      virtual openstudio::epmodel::Mixer demandMixer() const;
      virtual openstudio::epmodel::ModelObject clone(openstudio::epmodel::Model model) const;
      virtual std::vector<openstudio::epmodel::ModelObject> children() const override;

      virtual void autosize();
      virtual void applySizingValues();
      virtual openstudio::ComponentType componentType() const;
      virtual std::vector<openstudio::FuelType> coolingFuelTypes() const;
      virtual std::vector<openstudio::FuelType> heatingFuelTypes() const;
      virtual std::vector<openstudio::AppGFuelType> appGHeatingFuelTypes() const;

     public:
      // Loop traversal in epmodel is built from local topology objects such as
      // Branch, Splitter, Mixer, and path objects. Different loop types expose that
      // topology in different storage forms, but the higher-level APIs still need to
      // answer the same question: "what is the ordered sequence of objects between
      // these two points on the loop?"
      //
      // AdjacencyBuilder is a small utility for that job. Callers add the directed
      // links that represent the loop topology they want to expose, then ask for the
      // path from one object to another.
      //
      // The important detail is that this is not limited to a single straight chain.
      // Plant loops, and the demand side of air loops, can fan out into parallel
      // branches and merge again later. `walkPath()` keeps only the subgraph that
      // lies on some path from `start` to `target`, then emits those objects in a
      // deterministic order that respects the added edge ordering. That gives loop
      // APIs a stable traversal without making callers implement graph logic over and
      // over again.
      struct AdjacencyBuilder
      {
        using AdjacencyList = std::map<Handle, std::vector<Handle>>;

        AdjacencyList adjacencyList;

        void addNode(const openstudio::epmodel::ModelObject& obj) {
          adjacencyList.try_emplace(obj.handle(), std::vector<Handle>{});
        }

        void addLink(const openstudio::epmodel::ModelObject& from, const openstudio::epmodel::ModelObject& to) {
          addNode(from);
          addNode(to);
          adjacencyList[from.handle()].push_back(to.handle());
        }

        // Return the ordered objects that participate in the topology between
        // `start` and `target`. If there is no path, return an empty vector.
        std::vector<openstudio::epmodel::ModelObject> walkPath(const openstudio::epmodel::Model& model, const openstudio::epmodel::ModelObject& start,
                                                               const openstudio::epmodel::ModelObject& target) const {
          const auto startHandle = start.handle();
          const auto targetHandle = target.handle();

          auto startObject = model.getModelObject<openstudio::epmodel::ModelObject>(startHandle);
          auto targetObject = model.getModelObject<openstudio::epmodel::ModelObject>(targetHandle);
          if (!startObject || !targetObject) {
            return {};
          }

          std::set<Handle> forwardReachable;
          std::vector<Handle> stack{startHandle};
          while (!stack.empty()) {
            const auto current = stack.back();
            stack.pop_back();
            if (!forwardReachable.insert(current).second) {
              continue;
            }

            if (const auto it = adjacencyList.find(current); it != adjacencyList.end()) {
              for (auto childIt = it->second.rbegin(); childIt != it->second.rend(); ++childIt) {
                stack.push_back(*childIt);
              }
            }
          }

          if (!forwardReachable.contains(targetHandle)) {
            return {};
          }

          std::map<Handle, std::vector<Handle>> reverseAdjacency;
          for (const auto& [from, children] : adjacencyList) {
            reverseAdjacency.try_emplace(from, std::vector<Handle>{});
            for (const auto& to : children) {
              reverseAdjacency[to].push_back(from);
            }
          }

          std::set<Handle> backwardReachable;
          stack = {targetHandle};
          while (!stack.empty()) {
            const auto current = stack.back();
            stack.pop_back();
            if (!backwardReachable.insert(current).second) {
              continue;
            }

            if (const auto it = reverseAdjacency.find(current); it != reverseAdjacency.end()) {
              for (auto parentIt = it->second.rbegin(); parentIt != it->second.rend(); ++parentIt) {
                stack.push_back(*parentIt);
              }
            }
          }

          std::set<Handle> relevantHandles;
          for (const auto& handle : forwardReachable) {
            if (backwardReachable.contains(handle)) {
              relevantHandles.insert(handle);
            }
          }

          if (!(relevantHandles.contains(startHandle) && relevantHandles.contains(targetHandle))) {
            return {};
          }

          std::map<Handle, unsigned> indegree;
          for (const auto& handle : relevantHandles) {
            indegree.emplace(handle, 0u);
          }

          for (const auto& [from, children] : adjacencyList) {
            if (!relevantHandles.contains(from)) {
              continue;
            }
            for (const auto& to : children) {
              if (relevantHandles.contains(to)) {
                ++indegree[to];
              }
            }
          }

          std::vector<openstudio::epmodel::ModelObject> path;
          std::set<Handle> emitted;
          stack = {startHandle};

          while (!stack.empty()) {
            const auto current = stack.back();
            stack.pop_back();
            if (!emitted.insert(current).second) {
              continue;
            }

            auto currentObject = model.getModelObject<openstudio::epmodel::ModelObject>(current);
            if (!currentObject) {
              return {};
            }
            path.push_back(currentObject.get());

            if (const auto it = adjacencyList.find(current); it != adjacencyList.end()) {
              for (auto childIt = it->second.rbegin(); childIt != it->second.rend(); ++childIt) {
                const auto& child = *childIt;
                if (!relevantHandles.contains(child)) {
                  continue;
                }
                auto indegreeIt = indegree.find(child);
                if (indegreeIt == indegree.end()) {
                  continue;
                }
                OS_ASSERT(indegreeIt->second > 0u);
                --indegreeIt->second;
                if (indegreeIt->second == 0u) {
                  stack.push_back(child);
                }
              }
            }
          }

          if (path.empty() || path.back().handle() != targetHandle) {
            return {};
          }

          return path;
        }
      };

     protected:
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
