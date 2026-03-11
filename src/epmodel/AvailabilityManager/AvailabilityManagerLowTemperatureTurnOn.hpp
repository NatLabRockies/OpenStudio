/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AVAILABILITYMANAGERLOWTEMPERATURETURNON_HPP
#define EPMODEL_AVAILABILITYMANAGERLOWTEMPERATURETURNON_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class AvailabilityManagerLowTemperatureTurnOn_Impl;
}

class EPMODEL_API AvailabilityManagerLowTemperatureTurnOn : public ModelObject
{
 public:
  explicit AvailabilityManagerLowTemperatureTurnOn(const Model& model);

  virtual ~AvailabilityManagerLowTemperatureTurnOn() override = default;
  AvailabilityManagerLowTemperatureTurnOn(const AvailabilityManagerLowTemperatureTurnOn& other) = default;
  AvailabilityManagerLowTemperatureTurnOn(AvailabilityManagerLowTemperatureTurnOn&& other) = default;
  AvailabilityManagerLowTemperatureTurnOn& operator=(const AvailabilityManagerLowTemperatureTurnOn&) = default;
  AvailabilityManagerLowTemperatureTurnOn& operator=(AvailabilityManagerLowTemperatureTurnOn&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: Preserves openstudio::model scalar accessor name/signature for this model-counterpart class.
  // - Field Mapping: temperature maps to E+ AvailabilityManager:LowTemperatureTurnOn Temperature.
  // - TODO(parity): Keep relationship field sensorNode out of this scalar-only scaffold pass.
  double temperature() const;
  bool setTemperature(double temperature);

 protected:
  using ImplType = detail::AvailabilityManagerLowTemperatureTurnOn_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit AvailabilityManagerLowTemperatureTurnOn(std::shared_ptr<detail::AvailabilityManagerLowTemperatureTurnOn_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
