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

  /** \brief Abstract base for components with two air streams.
   *
   * \par EnergyPlus object
   * This class has no single EnergyPlus object; concrete subclasses such as
   * \epobject{group-heat-recovery.html#heatexchangerairtoairsensibleandlatent,HeatExchanger:AirToAir:SensibleAndLatent} and \epobject{group-heat-recovery.html#heatexchangerdesiccantbalancedflow,HeatExchanger:Desiccant:BalancedFlow} provide the persisted objects.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model base is `openstudio::model::AirToAirComponent`; concrete subclasses provide
   * the type-specific fields and relationships.
   *
   * \par Known limitations
   * The base does not establish a universal connection policy; each concrete air-to-air component owns its topology.
   */
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
