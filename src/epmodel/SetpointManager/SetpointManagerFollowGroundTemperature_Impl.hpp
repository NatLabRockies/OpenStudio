/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SETPOINTMANAGERFOLLOWGROUNDTEMPERATURE_IMPL_HPP
#define EPMODEL_SETPOINTMANAGERFOLLOWGROUNDTEMPERATURE_IMPL_HPP

#include "SetpointManager/SetpointManager_Impl.hpp"

namespace openstudio {
namespace epmodel {
  namespace detail {

    class EPMODEL_API SetpointManagerFollowGroundTemperature_Impl : public SetpointManager_Impl
    {
     public:
      using SetpointManager_Impl::SetpointManager_Impl;
      virtual ~SetpointManagerFollowGroundTemperature_Impl() override = default;

      std::string referenceGroundTemperatureObjectType() const;
      bool setReferenceGroundTemperatureObjectType(const std::string& groundTemperatureObjType);

      double offsetTemperatureDifference() const;
      bool setOffsetTemperatureDifference(double offsetTemperatureDifference);

      double maximumSetpointTemperature() const;
      bool setMaximumSetpointTemperature(double maximumSetpointTemperature);

      double minimumSetpointTemperature() const;
      bool setMinimumSetpointTemperature(double minimumSetpointTemperature);

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
