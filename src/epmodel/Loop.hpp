/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_LOOP_HPP
#define EPMODEL_LOOP_HPP

#include "EPModelAPI.hpp"
#include "ParentObject.hpp"

#include "../utilities/core/Logger.hpp"
#include "../utilities/idf/Handle.hpp"
#include <utilities/idd/IddEnums.hxx>

#include <boost/optional.hpp>

#include <vector>

namespace openstudio {

class AppGFuelType;
class ComponentType;
class FuelType;
class IddObjectType;
class IdfObject;

namespace epmodel {

  namespace detail {
    class Loop_Impl;
  }

  class HVACComponent;
  class Mixer;
  class Model;
  class ModelObject;
  class Node;
  class Splitter;

  class EPMODEL_API Loop : public ParentObject
  {
   public:
    virtual ~Loop() override = default;
    Loop(const Loop& other) = default;
    Loop(Loop&& other) = default;
    Loop& operator=(const Loop&) = default;
    Loop& operator=(Loop&&) = default;

    virtual Node supplyInletNode() const;
    virtual Node supplyOutletNode() const;
    virtual std::vector<Node> supplyOutletNodes() const;
    virtual Node demandInletNode() const;
    virtual Node demandOutletNode() const;
    virtual std::vector<Node> demandInletNodes() const;

    virtual std::vector<ModelObject> supplyComponents(const HVACComponent& inletComp, const HVACComponent& outletComp,
                                                      openstudio::IddObjectType type = openstudio::IddObjectType::Catchall) const;

    virtual std::vector<ModelObject> supplyComponents(openstudio::IddObjectType type = openstudio::IddObjectType::Catchall) const;

    virtual std::vector<ModelObject> demandComponents(const HVACComponent& inletComp, const HVACComponent& outletComp,
                                                      openstudio::IddObjectType type = openstudio::IddObjectType::Catchall) const;

    virtual std::vector<ModelObject> demandComponents(openstudio::IddObjectType type = openstudio::IddObjectType::Catchall) const;

    virtual std::vector<ModelObject> components(openstudio::IddObjectType type = openstudio::IddObjectType::Catchall) const;

    std::vector<ModelObject> components(const HVACComponent& inletComp, const HVACComponent& outletComp,
                                        openstudio::IddObjectType type = openstudio::IddObjectType::Catchall);

    virtual boost::optional<ModelObject> component(openstudio::Handle handle) const;
    virtual boost::optional<ModelObject> demandComponent(openstudio::Handle handle) const;
    virtual boost::optional<ModelObject> supplyComponent(openstudio::Handle handle) const;

    virtual std::vector<openstudio::IdfObject> remove();

    Splitter demandSplitter() const;
    Mixer demandMixer() const;

    virtual ModelObject clone(Model model) const;
    virtual std::vector<ModelObject> children() const;

    void autosize();
    void applySizingValues();

    ComponentType componentType() const;
    std::vector<FuelType> coolingFuelTypes() const;
    std::vector<FuelType> heatingFuelTypes() const;
    std::vector<AppGFuelType> appGHeatingFuelTypes() const;

   protected:
    friend class Model;
    friend class openstudio::IdfObject;

    using ImplType = detail::Loop_Impl;

    explicit Loop(std::shared_ptr<ImplType> impl);
    Loop(IddObjectType type, const Model& model);

   private:
    REGISTER_LOGGER("openstudio.epmodel.Loop");
  };

  using OptionalLoop = boost::optional<Loop>;

}  // namespace epmodel
}  // namespace openstudio

#endif
