/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AVAILABILITYMANAGERNIGHTVENTILATION_IMPL_HPP
#define EPMODEL_AVAILABILITYMANAGERNIGHTVENTILATION_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API AvailabilityManagerNightVentilation_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~AvailabilityManagerNightVentilation_Impl() override = default;

      // ventilationTemperatureDifference
      double ventilationTemperatureDifference() const;
      bool setVentilationTemperatureDifference(double ventilationTemperatureDifference);

      // ventilationTemperatureLowLimit
      double ventilationTemperatureLowLimit() const;
      bool setVentilationTemperatureLowLimit(double ventilationTemperatureLowLimit);

      // nightVentingFlowFraction
      double nightVentingFlowFraction() const;
      bool setNightVentingFlowFraction(double nightVentingFlowFraction);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
