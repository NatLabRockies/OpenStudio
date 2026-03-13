/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AVAILABILITYMANAGERDIFFERENTIALTHERMOSTAT_IMPL_HPP
#define EPMODEL_AVAILABILITYMANAGERDIFFERENTIALTHERMOSTAT_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API AvailabilityManagerDifferentialThermostat_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~AvailabilityManagerDifferentialThermostat_Impl() override = default;

  // Temperature Difference On Limit accessors
  double temperatureDifferenceOnLimit() const;
  bool setTemperatureDifferenceOnLimit(double temperatureDifferenceOnLimit);

  // Temperature Difference Off Limit accessors
  double temperatureDifferenceOffLimit() const;
  bool setTemperatureDifferenceOffLimit(double temperatureDifferenceOffLimit);
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
