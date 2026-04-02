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
