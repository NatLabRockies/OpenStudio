/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_STRAIGHTCOMPONENT_IMPL_HPP
#define EPMODEL_STRAIGHTCOMPONENT_IMPL_HPP

#include "HVACComponent/HVACComponent_Impl.hpp"
#include "ModelObject.hpp"

#include <boost/optional.hpp>

namespace openstudio {
namespace epmodel {
  class AirLoopHVACOutdoorAirSystem;
  namespace detail {

    class EPMODEL_API StraightComponent_Impl : public HVACComponent_Impl
    {
     public:
      using HVACComponent_Impl::HVACComponent_Impl;
      virtual ~StraightComponent_Impl() override = default;

      virtual unsigned inletPort() const = 0;
      virtual unsigned outletPort() const = 0;

      virtual boost::optional<ModelObject> inletModelObject() const;
      virtual boost::optional<ModelObject> outletModelObject() const;
      virtual bool removeFromLoop();
      virtual std::vector<openstudio::IdfObject> remove() override;
      virtual void disconnect() override;
      void doCanonicalize(LoadContext& context) override;

      virtual bool addToNode(Node& node) override;

     protected:
      bool addToOutdoorAirSystem(AirLoopHVACOutdoorAirSystem& oaSystem, Node& node);
      bool removeFromOutdoorAirSystem(AirLoopHVACOutdoorAirSystem& oaSystem);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
