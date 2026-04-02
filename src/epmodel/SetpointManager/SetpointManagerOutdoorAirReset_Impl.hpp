/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SETPOINTMANAGEROUTDOORAIRRESET_IMPL_HPP
#define EPMODEL_SETPOINTMANAGEROUTDOORAIRRESET_IMPL_HPP

#include "SetpointManager/SetpointManager_Impl.hpp"

namespace openstudio {
namespace epmodel {
  namespace detail {

    class EPMODEL_API SetpointManagerOutdoorAirReset_Impl : public SetpointManager_Impl
    {
     public:
      using SetpointManager_Impl::SetpointManager_Impl;
      virtual ~SetpointManagerOutdoorAirReset_Impl() override = default;

      bool isControlVariableDefaulted() const;
      void resetControlVariable();

      double setpointatOutdoorLowTemperature() const;
      bool setSetpointatOutdoorLowTemperature(double setpointatOutdoorLowTemperature);

      double outdoorLowTemperature() const;
      bool setOutdoorLowTemperature(double outdoorLowTemperature);

      double setpointatOutdoorHighTemperature() const;
      bool setSetpointatOutdoorHighTemperature(double setpointatOutdoorHighTemperature);

      double outdoorHighTemperature() const;
      bool setOutdoorHighTemperature(double outdoorHighTemperature);

      boost::optional<double> setpointatOutdoorLowTemperature2() const;
      bool setSetpointatOutdoorLowTemperature2(boost::optional<double> setpointatOutdoorLowTemperature2);
      void resetSetpointatOutdoorLowTemperature2();

      boost::optional<double> outdoorLowTemperature2() const;
      bool setOutdoorLowTemperature2(boost::optional<double> outdoorLowTemperature2);
      void resetOutdoorLowTemperature2();

      boost::optional<double> setpointatOutdoorHighTemperature2() const;
      bool setSetpointatOutdoorHighTemperature2(boost::optional<double> setpointatOutdoorHighTemperature2);
      void resetSetpointatOutdoorHighTemperature2();

      boost::optional<double> outdoorHighTemperature2() const;
      bool setOutdoorHighTemperature2(boost::optional<double> outdoorHighTemperature2);
      void resetOutdoorHighTemperature2();

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
