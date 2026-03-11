/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "Loop_Impl.hpp"

#include "HVACComponent.hpp"
#include "Loop.hpp"
#include "Mixer.hpp"
#include "Model.hpp"
#include "ModelObject.hpp"
#include "Node.hpp"
#include "NodeList.hpp"
#include "NodeList_Impl.hpp"
#include "Splitter.hpp"

#include <utilities/data/DataEnums.hpp>
#include <utilities/idf/IdfObject.hpp>
#include <utilities/core/Logger.hpp>

#include <algorithm>

namespace openstudio {
namespace epmodel {
namespace detail {

  openstudio::epmodel::Node Loop_Impl::supplyInletNode() const {
    LOG_FREE_AND_THROW("openstudio.epmodel.Loop", "Loop_Impl::supplyInletNode is not implemented for epmodel.");
  }

  openstudio::epmodel::Node Loop_Impl::supplyOutletNode() const {
    LOG_FREE_AND_THROW("openstudio.epmodel.Loop", "Loop_Impl::supplyOutletNode is not implemented for epmodel.");
  }

  std::vector<openstudio::epmodel::Node> Loop_Impl::supplyOutletNodes() const {
    return {};
  }

  openstudio::epmodel::Node Loop_Impl::demandInletNode() const {
    LOG_FREE_AND_THROW("openstudio.epmodel.Loop", "Loop_Impl::demandInletNode is not implemented for epmodel.");
  }

  openstudio::epmodel::Node Loop_Impl::demandOutletNode() const {
    LOG_FREE_AND_THROW("openstudio.epmodel.Loop", "Loop_Impl::demandOutletNode is not implemented for epmodel.");
  }

  std::vector<openstudio::epmodel::Node> Loop_Impl::demandInletNodes() const {
    return {};
  }

  std::vector<openstudio::epmodel::ModelObject> Loop_Impl::supplyComponents(const openstudio::epmodel::HVACComponent&,
                                                                            const openstudio::epmodel::HVACComponent&,
                                                                            openstudio::IddObjectType) const {
    return {};
  }

  std::vector<openstudio::epmodel::ModelObject> Loop_Impl::supplyComponents(openstudio::IddObjectType) const {
    return {};
  }

  std::vector<openstudio::epmodel::ModelObject> Loop_Impl::demandComponents(const openstudio::epmodel::HVACComponent&,
                                                                            const openstudio::epmodel::HVACComponent&,
                                                                            openstudio::IddObjectType) const {
    return {};
  }

  std::vector<openstudio::epmodel::ModelObject> Loop_Impl::demandComponents(openstudio::IddObjectType) const {
    return {};
  }

  std::vector<openstudio::epmodel::ModelObject> Loop_Impl::components(openstudio::IddObjectType type) const {
    auto result = this->supplyComponents(type);
    const auto demand = this->demandComponents(type);
    result.insert(result.end(), demand.begin(), demand.end());
    return result;
  }

  std::vector<openstudio::epmodel::ModelObject> Loop_Impl::components(const openstudio::epmodel::HVACComponent&,
                                                                      const openstudio::epmodel::HVACComponent&,
                                                                      openstudio::IddObjectType) {
    return {};
  }

  boost::optional<openstudio::epmodel::ModelObject> Loop_Impl::component(openstudio::Handle handle) const {
    if (auto supplyComp = this->supplyComponent(handle)) {
      return supplyComp;
    }
    return this->demandComponent(handle);
  }

  boost::optional<openstudio::epmodel::ModelObject> Loop_Impl::demandComponent(openstudio::Handle handle) const {
    auto comps = demandComponents(openstudio::IddObjectType::Catchall);
    auto it = std::find_if(comps.begin(), comps.end(), [&](const ModelObject& comp) { return comp.handle() == handle; });
    if (it != comps.end()) {
      return *it;
    }
    return boost::none;
  }

  boost::optional<openstudio::epmodel::ModelObject> Loop_Impl::supplyComponent(openstudio::Handle handle) const {
    auto comps = supplyComponents(openstudio::IddObjectType::Catchall);
    auto it = std::find_if(comps.begin(), comps.end(), [&](const ModelObject& comp) { return comp.handle() == handle; });
    if (it != comps.end()) {
      return *it;
    }
    return boost::none;
  }

  std::vector<openstudio::IdfObject> Loop_Impl::remove() {
    return ParentObject_Impl::remove();
  }

  openstudio::epmodel::Splitter Loop_Impl::demandSplitter() const {
    return openstudio::epmodel::Splitter(model());
  }

  openstudio::epmodel::Mixer Loop_Impl::demandMixer() const {
    return openstudio::epmodel::Mixer(model());
  }

  openstudio::epmodel::ModelObject Loop_Impl::clone(openstudio::epmodel::Model model) const {
    return openstudio::epmodel::ModelObject::create(openstudio::IddObjectType::Catchall, model);
  }

  std::vector<openstudio::epmodel::ModelObject> Loop_Impl::children() const {
    return {};
  }

  void Loop_Impl::autosize() {}

  void Loop_Impl::applySizingValues() {}

  openstudio::ComponentType Loop_Impl::componentType() const {
    return openstudio::ComponentType();
  }

  std::vector<openstudio::FuelType> Loop_Impl::coolingFuelTypes() const {
    return {};
  }

  std::vector<openstudio::FuelType> Loop_Impl::heatingFuelTypes() const {
    return {};
  }

  std::vector<openstudio::AppGFuelType> Loop_Impl::appGHeatingFuelTypes() const {
    return {};
  }

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
