/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AVAILABILITYMANAGERLOWTEMPERATURETURNOFF_HPP
#define EPMODEL_AVAILABILITYMANAGERLOWTEMPERATURETURNOFF_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class AvailabilityManagerLowTemperatureTurnOff_Impl;
}

class EPMODEL_API AvailabilityManagerLowTemperatureTurnOff : public ModelObject
{
 public:
  explicit AvailabilityManagerLowTemperatureTurnOff(const Model& model);

  virtual ~AvailabilityManagerLowTemperatureTurnOff() override = default;
  AvailabilityManagerLowTemperatureTurnOff(const AvailabilityManagerLowTemperatureTurnOff& other) = default;
  AvailabilityManagerLowTemperatureTurnOff(AvailabilityManagerLowTemperatureTurnOff&& other) = default;
  AvailabilityManagerLowTemperatureTurnOff& operator=(const AvailabilityManagerLowTemperatureTurnOff&) = default;
  AvailabilityManagerLowTemperatureTurnOff& operator=(AvailabilityManagerLowTemperatureTurnOff&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: Preserves openstudio::model scalar accessor name/signature for this model-counterpart class.
  // - Field Mapping: temperature maps to E+ AvailabilityManager:LowTemperatureTurnOff Temperature.
  // - TODO(parity): Keep relationship fields sensorNode and applicabilitySchedule out of this scalar-only scaffold pass.
  double temperature() const;
  bool setTemperature(double temperature);

 protected:
  using ImplType = detail::AvailabilityManagerLowTemperatureTurnOff_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit AvailabilityManagerLowTemperatureTurnOff(std::shared_ptr<detail::AvailabilityManagerLowTemperatureTurnOff_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
