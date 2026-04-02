/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SETPOINTMANAGERSINGLEZONEREHEAT_IMPL_HPP
#define EPMODEL_SETPOINTMANAGERSINGLEZONEREHEAT_IMPL_HPP

#include "SetpointManager/SetpointManager_Impl.hpp"

namespace openstudio {
namespace epmodel {
  class Node;
  class ThermalZone;
  namespace detail {

    class EPMODEL_API SetpointManagerSingleZoneReheat_Impl : public SetpointManager_Impl
    {
     public:
      using SetpointManager_Impl::SetpointManager_Impl;
      virtual ~SetpointManagerSingleZoneReheat_Impl() override = default;

      double minimumSupplyAirTemperature() const;
      bool setMinimumSupplyAirTemperature(double minimumSupplyAirTemperature);

      double maximumSupplyAirTemperature() const;
      bool setMaximumSupplyAirTemperature(double maximumSupplyAirTemperature);

      bool addToNode(Node& node) override;
      bool setControlZone(const ThermalZone& thermalZone);

      boost::optional<openstudio::epmodel::Node> setpointNode() const override;
      std::string controlVariable() const override;
      bool setControlVariable(const std::string& value) override;

     protected:
      void doCanonicalize(LoadContext& context) override;

     private:
      bool setSetpointNode(const openstudio::epmodel::Node& node) override;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
