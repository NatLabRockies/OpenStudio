/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SETPOINTMANAGEROUTDOORAIRPRETREAT_IMPL_HPP
#define EPMODEL_SETPOINTMANAGEROUTDOORAIRPRETREAT_IMPL_HPP

#include "SetpointManager/SetpointManager_Impl.hpp"

namespace openstudio {
namespace epmodel {
  namespace detail {

    class EPMODEL_API SetpointManagerOutdoorAirPretreat_Impl : public SetpointManager_Impl
    {
     public:
      using SetpointManager_Impl::SetpointManager_Impl;
      virtual ~SetpointManagerOutdoorAirPretreat_Impl() override = default;

      double minimumSetpointTemperature() const;
      bool isMinimumSetpointTemperatureDefaulted() const;
      bool setMinimumSetpointTemperature(double minimumSetpointTemperature);
      void resetMinimumSetpointTemperature();

      double maximumSetpointTemperature() const;
      bool isMaximumSetpointTemperatureDefaulted() const;
      bool setMaximumSetpointTemperature(double maximumSetpointTemperature);
      void resetMaximumSetpointTemperature();

      double minimumSetpointHumidityRatio() const;
      bool isMinimumSetpointHumidityRatioDefaulted() const;
      bool setMinimumSetpointHumidityRatio(double minimumSetpointHumidityRatio);
      void resetMinimumSetpointHumidityRatio();

      double maximumSetpointHumidityRatio() const;
      bool isMaximumSetpointHumidityRatioDefaulted() const;
      bool setMaximumSetpointHumidityRatio(double maximumSetpointHumidityRatio);
      void resetMaximumSetpointHumidityRatio();

      void resetControlVariable();

     protected:
      unsigned setpointNodeFieldIndex() const override;
      unsigned controlVariableFieldIndex() const override;

      void doCanonicalize(LoadContext& context) override;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
