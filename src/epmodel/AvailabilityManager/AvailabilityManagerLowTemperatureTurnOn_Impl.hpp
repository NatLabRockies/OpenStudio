/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AVAILABILITYMANAGERLOWTEMPERATURETURNON_IMPL_HPP
#define EPMODEL_AVAILABILITYMANAGERLOWTEMPERATURETURNON_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API AvailabilityManagerLowTemperatureTurnOn_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~AvailabilityManagerLowTemperatureTurnOn_Impl() override = default;

  /** @name Temperature Accessors */
  //@{
  // Schema Alignment Notes:
  // - API: Keeps parity with openstudio::model scalar accessors for this field.
  // - Field Mapping: temperature ↔ AvailabilityManager:LowTemperatureTurnOn Temperature.
  double temperature() const;
  bool setTemperature(double temperature);
  //@}
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
