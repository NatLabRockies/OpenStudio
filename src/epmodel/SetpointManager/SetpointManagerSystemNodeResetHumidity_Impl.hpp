/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SETPOINTMANAGERSYSTEMNODERESETHUMIDITY_IMPL_HPP
#define EPMODEL_SETPOINTMANAGERSYSTEMNODERESETHUMIDITY_IMPL_HPP

#include "SetpointManager/SetpointManager_Impl.hpp"

namespace openstudio {
namespace epmodel {
  namespace detail {

    class EPMODEL_API SetpointManagerSystemNodeResetHumidity_Impl : public SetpointManager_Impl
    {
     public:
      using SetpointManager_Impl::SetpointManager_Impl;
      virtual ~SetpointManagerSystemNodeResetHumidity_Impl() override = default;

      double setpointatLowReferenceHumidityRatio() const;
      bool setSetpointatLowReferenceHumidityRatio(double setpointatLowReferenceHumidityRatio);

      double setpointatHighReferenceHumidityRatio() const;
      bool setSetpointatHighReferenceHumidityRatio(double setpointatHighReferenceHumidityRatio);

      double lowReferenceHumidityRatio() const;
      bool setLowReferenceHumidityRatio(double lowReferenceHumidityRatio);

      double highReferenceHumidityRatio() const;
      bool setHighReferenceHumidityRatio(double highReferenceHumidityRatio);

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
