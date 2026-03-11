/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_LOOP_IMPL_HPP
#define EPMODEL_LOOP_IMPL_HPP

#include "ParentObject/ParentObject_Impl.hpp"
#include "Model.hpp"
#include "ModelObject.hpp"

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

  virtual std::vector<openstudio::IdfObject> remove();
  virtual openstudio::epmodel::Splitter demandSplitter() const;
  virtual openstudio::epmodel::Mixer demandMixer() const;
  virtual openstudio::epmodel::ModelObject clone(openstudio::epmodel::Model model) const;
  virtual std::vector<openstudio::epmodel::ModelObject> children() const;

  virtual void autosize();
  virtual void applySizingValues();
  virtual openstudio::ComponentType componentType() const;
  virtual std::vector<openstudio::FuelType> coolingFuelTypes() const;
  virtual std::vector<openstudio::FuelType> heatingFuelTypes() const;
  virtual std::vector<openstudio::AppGFuelType> appGHeatingFuelTypes() const;

 protected:
  struct AdjacencyBuilder {
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

    std::vector<openstudio::epmodel::ModelObject> walkPath(const openstudio::epmodel::Model& model,
                                                           const openstudio::epmodel::ModelObject& start,
                                                           const openstudio::epmodel::ModelObject& target) const {
      std::vector<openstudio::epmodel::ModelObject> path;
      std::set<Handle> visited;
      auto currentHandle = start.handle();
      const auto targetHandle = target.handle();

      while (true) {
        auto currentObject = model.getModelObject<openstudio::epmodel::ModelObject>(currentHandle);
        if (!currentObject) {
          break;
        }
        path.push_back(currentObject.get());
        if (visited.contains(currentHandle)) {
          break;
        }
        visited.insert(currentHandle);

        if (currentHandle == targetHandle) {
          break;
        }

        const auto it = adjacencyList.find(currentHandle);
        if (it == adjacencyList.end() || it->second.empty()) {
          break;
        }

        currentHandle = it->second.front();
      }

      return path;
    }
  };
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
