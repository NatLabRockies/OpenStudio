/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRTOAIRCOMPONENT_HPP
#define EPMODEL_AIRTOAIRCOMPONENT_HPP

#include "EPModelAPI.hpp"
#include "HVACComponent/HVACComponent.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;
  class ModelObject;
  class Node;

  namespace detail {
    class AirToAirComponent_Impl;
  }

  class EPMODEL_API AirToAirComponent : public HVACComponent
  {
   public:
    virtual ~AirToAirComponent() override = default;
    AirToAirComponent(const AirToAirComponent& other) = default;
    AirToAirComponent(AirToAirComponent&& other) = default;
    AirToAirComponent& operator=(const AirToAirComponent&) = default;
    AirToAirComponent& operator=(AirToAirComponent&&) = default;

    unsigned primaryAirInletPort() const;
    unsigned primaryAirOutletPort() const;
    unsigned secondaryAirInletPort() const;
    unsigned secondaryAirOutletPort() const;

    boost::optional<ModelObject> primaryAirInletModelObject() const;
    boost::optional<ModelObject> primaryAirOutletModelObject() const;
    boost::optional<ModelObject> secondaryAirInletModelObject() const;
    boost::optional<ModelObject> secondaryAirOutletModelObject() const;

    bool addToNode(Node& node);
    std::vector<IdfObject> remove();

   protected:
    using ImplType = detail::AirToAirComponent_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit AirToAirComponent(std::shared_ptr<detail::AirToAirComponent_Impl> impl);
    AirToAirComponent(IddObjectType type, const Model& model);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
