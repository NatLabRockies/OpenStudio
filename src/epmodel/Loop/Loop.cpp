/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "Loop/Loop.hpp"
#include "Loop/Loop_Impl.hpp"

#include "HVACComponent/HVACComponent.hpp"
#include "Mixer/Mixer.hpp"
#include "Model.hpp"
#include "ModelObject.hpp"
#include "Node.hpp"
#include "Splitter.hpp"

#include <utilities/data/DataEnums.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idf/Handle.hpp>
#include <utilities/idf/IdfObject.hpp>
#include <utilities/core/Logger.hpp>

openstudio::epmodel::Node openstudio::epmodel::Loop::supplyInletNode() const {
  return getImpl<detail::Loop_Impl>()->supplyInletNode();
}

openstudio::epmodel::Node openstudio::epmodel::Loop::supplyOutletNode() const {
  return getImpl<detail::Loop_Impl>()->supplyOutletNode();
}

std::vector<openstudio::epmodel::Node> openstudio::epmodel::Loop::supplyOutletNodes() const {
  return getImpl<detail::Loop_Impl>()->supplyOutletNodes();
}

openstudio::epmodel::Node openstudio::epmodel::Loop::demandInletNode() const {
  return getImpl<detail::Loop_Impl>()->demandInletNode();
}

openstudio::epmodel::Node openstudio::epmodel::Loop::demandOutletNode() const {
  return getImpl<detail::Loop_Impl>()->demandOutletNode();
}

std::vector<openstudio::epmodel::Node> openstudio::epmodel::Loop::demandInletNodes() const {
  return getImpl<detail::Loop_Impl>()->demandInletNodes();
}

std::vector<openstudio::epmodel::ModelObject> openstudio::epmodel::Loop::supplyComponents(const openstudio::epmodel::HVACComponent& inletComp,
                                                                                           const openstudio::epmodel::HVACComponent& outletComp,
                                                                                           openstudio::IddObjectType type) const {
  return getImpl<detail::Loop_Impl>()->supplyComponents(inletComp, outletComp, type);
}

std::vector<openstudio::epmodel::ModelObject> openstudio::epmodel::Loop::supplyComponents(openstudio::IddObjectType type) const {
  return getImpl<detail::Loop_Impl>()->supplyComponents(type);
}

std::vector<openstudio::epmodel::ModelObject> openstudio::epmodel::Loop::demandComponents(const openstudio::epmodel::HVACComponent& inletComp,
                                                                                           const openstudio::epmodel::HVACComponent& outletComp,
                                                                                           openstudio::IddObjectType type) const {
  return getImpl<detail::Loop_Impl>()->demandComponents(inletComp, outletComp, type);
}

std::vector<openstudio::epmodel::ModelObject> openstudio::epmodel::Loop::demandComponents(openstudio::IddObjectType type) const {
  return getImpl<detail::Loop_Impl>()->demandComponents(type);
}

std::vector<openstudio::epmodel::ModelObject> openstudio::epmodel::Loop::components(openstudio::IddObjectType type) const {
  return getImpl<detail::Loop_Impl>()->components(type);
}

std::vector<openstudio::epmodel::ModelObject> openstudio::epmodel::Loop::components(const openstudio::epmodel::HVACComponent& inletComp,
                                                                                     const openstudio::epmodel::HVACComponent& outletComp,
                                                                                     openstudio::IddObjectType type) {
  return getImpl<detail::Loop_Impl>()->components(inletComp, outletComp, type);
}

boost::optional<openstudio::epmodel::ModelObject> openstudio::epmodel::Loop::component(openstudio::Handle handle) const {
  return getImpl<detail::Loop_Impl>()->component(handle);
}

boost::optional<openstudio::epmodel::ModelObject> openstudio::epmodel::Loop::demandComponent(openstudio::Handle handle) const {
  return getImpl<detail::Loop_Impl>()->demandComponent(handle);
}

boost::optional<openstudio::epmodel::ModelObject> openstudio::epmodel::Loop::supplyComponent(openstudio::Handle handle) const {
  return getImpl<detail::Loop_Impl>()->supplyComponent(handle);
}

std::vector<openstudio::IdfObject> openstudio::epmodel::Loop::remove() {
  return getImpl<detail::Loop_Impl>()->remove();
}

openstudio::epmodel::Splitter openstudio::epmodel::Loop::demandSplitter() const {
  return getImpl<detail::Loop_Impl>()->demandSplitter();
}

openstudio::epmodel::Mixer openstudio::epmodel::Loop::demandMixer() const {
  return getImpl<detail::Loop_Impl>()->demandMixer();
}

openstudio::epmodel::ModelObject openstudio::epmodel::Loop::clone(openstudio::epmodel::Model model) const {
  return getImpl<detail::Loop_Impl>()->clone(model);
}

std::vector<openstudio::epmodel::ModelObject> openstudio::epmodel::Loop::children() const {
  return getImpl<detail::Loop_Impl>()->children();
}

void openstudio::epmodel::Loop::autosize() {
  return getImpl<detail::Loop_Impl>()->autosize();
}

void openstudio::epmodel::Loop::applySizingValues() {
  return getImpl<detail::Loop_Impl>()->applySizingValues();
}

openstudio::ComponentType openstudio::epmodel::Loop::componentType() const {
  return getImpl<detail::Loop_Impl>()->componentType();
}

std::vector<openstudio::FuelType> openstudio::epmodel::Loop::coolingFuelTypes() const {
  return getImpl<detail::Loop_Impl>()->coolingFuelTypes();
}

std::vector<openstudio::FuelType> openstudio::epmodel::Loop::heatingFuelTypes() const {
  return getImpl<detail::Loop_Impl>()->heatingFuelTypes();
}

std::vector<openstudio::AppGFuelType> openstudio::epmodel::Loop::appGHeatingFuelTypes() const {
  return getImpl<detail::Loop_Impl>()->appGHeatingFuelTypes();
}

openstudio::epmodel::Loop::Loop(std::shared_ptr<ImplType> impl) : ParentObject(std::move(impl)) {}

openstudio::epmodel::Loop::Loop(openstudio::IddObjectType type, const openstudio::epmodel::Model& model) : ParentObject(type, model) {}
