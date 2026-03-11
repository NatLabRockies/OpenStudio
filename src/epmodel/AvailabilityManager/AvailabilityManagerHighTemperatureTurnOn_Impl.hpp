/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AVAILABILITYMANAGERHIGHTEMPERATURETURNON_IMPL_HPP
#define EPMODEL_AVAILABILITYMANAGERHIGHTEMPERATURETURNON_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API AvailabilityManagerHighTemperatureTurnOn_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~AvailabilityManagerHighTemperatureTurnOn_Impl() override = default;

  double temperature() const;
  bool setTemperature(double temperature);
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
