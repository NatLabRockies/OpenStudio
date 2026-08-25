/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SETPOINTMANAGER_IMPL_HPP
#define EPMODEL_SETPOINTMANAGER_IMPL_HPP

#include "HVACComponent/HVACComponent_Impl.hpp"
#include "StraightComponent/Node.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API SetpointManager_Impl : public HVACComponent_Impl
    {
     public:
      using HVACComponent_Impl::HVACComponent_Impl;
      virtual ~SetpointManager_Impl() override = default;

      virtual boost::optional<openstudio::epmodel::Node> setpointNode() const = 0;

      virtual std::string controlVariable() const = 0;
      virtual bool setControlVariable(const std::string& value) = 0;

      virtual bool isAllowedOnPlantLoop() const;
      bool addToNode(openstudio::epmodel::Node& node) override;

      boost::optional<Loop> loop() const override;
      boost::optional<AirLoopHVAC> airLoopHVAC() const override;
      boost::optional<PlantLoop> plantLoop() const override;
      boost::optional<AirLoopHVACOutdoorAirSystem> airLoopHVACOutdoorAirSystem() const override;

      void doCanonicalize(LoadContext& context) override;

     protected:
      void canonicalizeSetpointNodeField(LoadContext& context, unsigned fieldIndex);

     private:
      virtual bool setSetpointNode(const openstudio::epmodel::Node& node) = 0;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
