/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AVAILABILITYMANAGEROPTIMUMSTART_IMPL_HPP
#define EPMODEL_AVAILABILITYMANAGEROPTIMUMSTART_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API AvailabilityManagerOptimumStart_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~AvailabilityManagerOptimumStart_Impl() override = default;

      std::string controlType() const;
      bool setControlType(const std::string& controlType);

      double maximumValueforOptimumStartTime() const;
      bool setMaximumValueforOptimumStartTime(double maximumValueforOptimumStartTime);

      std::string controlAlgorithm() const;
      bool setControlAlgorithm(const std::string& controlAlgorithm);

      double constantTemperatureGradientduringCooling() const;
      bool setConstantTemperatureGradientduringCooling(double constantTemperatureGradientduringCooling);

      double constantTemperatureGradientduringHeating() const;
      bool setConstantTemperatureGradientduringHeating(double constantTemperatureGradientduringHeating);

      double initialTemperatureGradientduringCooling() const;
      bool setInitialTemperatureGradientduringCooling(double initialTemperatureGradientduringCooling);

      double initialTemperatureGradientduringHeating() const;
      bool setInitialTemperatureGradientduringHeating(double initialTemperatureGradientduringHeating);

      double constantStartTime() const;
      bool setConstantStartTime(double constantStartTime);

      int numberofPreviousDays() const;
      bool setNumberofPreviousDays(int numberofPreviousDays);

      std::vector<std::string> controlTypeValues() const;
      std::vector<std::string> controlAlgorithmValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
