/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SETPOINTMANAGERSINGLEZONEONESTAGEHEATING_IMPL_HPP
#define EPMODEL_SETPOINTMANAGERSINGLEZONEONESTAGEHEATING_IMPL_HPP

#include "SetpointManager/SetpointManager_Impl.hpp"

namespace openstudio {
namespace epmodel {
  namespace detail {

    class EPMODEL_API SetpointManagerSingleZoneOneStageHeating_Impl : public SetpointManager_Impl
    {
     public:
      using SetpointManager_Impl::SetpointManager_Impl;
      virtual ~SetpointManagerSingleZoneOneStageHeating_Impl() override = default;

      double heatingStageOnSupplyAirSetpointTemperature() const;
      bool setHeatingStageOnSupplyAirSetpointTemperature(double heatingStageOnSupplyAirSetpointTemperature);

      double heatingStageOffSupplyAirSetpointTemperature() const;
      bool setHeatingStageOffSupplyAirSetpointTemperature(double heatingStageOffSupplyAirSetpointTemperature);

     protected:
      unsigned setpointNodeFieldIndex() const override;
      unsigned controlVariableFieldIndex() const override;

      void doCanonicalize(LoadContext& context) override;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
