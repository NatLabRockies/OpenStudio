/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SETPOINTMANAGERWARMEST_IMPL_HPP
#define EPMODEL_SETPOINTMANAGERWARMEST_IMPL_HPP

#include "SetpointManager/SetpointManager_Impl.hpp"

namespace openstudio {
namespace epmodel {
  namespace detail {

    class EPMODEL_API SetpointManagerWarmest_Impl : public SetpointManager_Impl
    {
     public:
      using SetpointManager_Impl::SetpointManager_Impl;
      virtual ~SetpointManagerWarmest_Impl() override = default;

      double minimumSetpointTemperature() const;
      bool setMinimumSetpointTemperature(double minimumSetpointTemperature);

      double maximumSetpointTemperature() const;
      bool setMaximumSetpointTemperature(double maximumSetpointTemperature);

      std::string strategy() const;
      bool setStrategy(const std::string& strategy);

     protected:
      unsigned setpointNodeFieldIndex() const override;
      unsigned controlVariableFieldIndex() const override;

      void doCanonicalize(LoadContext& context) override;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
