/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILDXASHRAE205PERFORMANCE_IMPL_HPP
#define EPMODEL_COILDXASHRAE205PERFORMANCE_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API CoilDXASHRAE205Performance_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~CoilDXASHRAE205Performance_Impl() override = default;

      std::string representationFileName() const;
      bool setRepresentationFileName(const std::string& representationFileName);

      std::string performanceInterpolationMethod() const;
      bool setPerformanceInterpolationMethod(const std::string& performanceInterpolationMethod);
      void resetPerformanceInterpolationMethod();
      bool isPerformanceInterpolationMethodDefaulted() const;

      boost::optional<double> ratedTotalCoolingCapacity() const;
      bool setRatedTotalCoolingCapacity(double ratedTotalCoolingCapacity);
      void resetRatedTotalCoolingCapacity();
      void autosizeRatedTotalCoolingCapacity();
      bool isRatedTotalCoolingCapacityAutosized() const;

      boost::optional<double> ratedSteadyStateHeatingCapacity() const;
      bool setRatedSteadyStateHeatingCapacity(double ratedSteadyStateHeatingCapacity);
      void resetRatedSteadyStateHeatingCapacity();
      void autosizeRatedSteadyStateHeatingCapacity();
      bool isRatedSteadyStateHeatingCapacityAutosized() const;

      std::vector<std::string> performanceInterpolationMethodValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
