/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SETPOINTMANAGERFOLLOWSYSTEMNODETEMPERATURE_IMPL_HPP
#define EPMODEL_SETPOINTMANAGERFOLLOWSYSTEMNODETEMPERATURE_IMPL_HPP

#include "SetpointManager/SetpointManager_Impl.hpp"

namespace openstudio {
namespace epmodel {
  namespace detail {

    class EPMODEL_API SetpointManagerFollowSystemNodeTemperature_Impl : public SetpointManager_Impl
    {
     public:
      using SetpointManager_Impl::SetpointManager_Impl;
      virtual ~SetpointManagerFollowSystemNodeTemperature_Impl() override = default;

      std::string referenceTemperatureType() const;
      bool setReferenceTemperatureType(const std::string& referenceTemperatureType);

      double offsetTemperatureDifference() const;
      bool setOffsetTemperatureDifference(double offsetTemperatureDifference);

      double maximumLimitSetpointTemperature() const;
      bool setMaximumLimitSetpointTemperature(double maximumLimitSetpointTemperature);

      double minimumLimitSetpointTemperature() const;
      bool setMinimumLimitSetpointTemperature(double minimumLimitSetpointTemperature);

      bool isAllowedOnPlantLoop() const override;

     protected:
      unsigned setpointNodeFieldIndex() const override;
      unsigned controlVariableFieldIndex() const override;

      void doCanonicalize(LoadContext& context) override;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
