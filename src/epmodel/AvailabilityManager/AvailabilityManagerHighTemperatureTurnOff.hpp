/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AVAILABILITYMANAGERHIGHTEMPERATURETURNOFF_HPP
#define EPMODEL_AVAILABILITYMANAGERHIGHTEMPERATURETURNOFF_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class AvailabilityManagerHighTemperatureTurnOff_Impl;
}

class EPMODEL_API AvailabilityManagerHighTemperatureTurnOff : public ModelObject
{
 public:
  explicit AvailabilityManagerHighTemperatureTurnOff(const Model& model);

  virtual ~AvailabilityManagerHighTemperatureTurnOff() override = default;
  AvailabilityManagerHighTemperatureTurnOff(const AvailabilityManagerHighTemperatureTurnOff& other) = default;
  AvailabilityManagerHighTemperatureTurnOff(AvailabilityManagerHighTemperatureTurnOff&& other) = default;
  AvailabilityManagerHighTemperatureTurnOff& operator=(const AvailabilityManagerHighTemperatureTurnOff&) = default;
  AvailabilityManagerHighTemperatureTurnOff& operator=(AvailabilityManagerHighTemperatureTurnOff&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: Preserves openstudio::model scalar accessor name/signature for this model-counterpart class.
  // - Field Mapping: temperature maps to E+ AvailabilityManager:HighTemperatureTurnOff Temperature.
  // - TODO(parity): Keep relationship field sensorNode out of this scalar-only scaffold pass.
  double temperature() const;
  bool setTemperature(double temperature);

 protected:
  using ImplType = detail::AvailabilityManagerHighTemperatureTurnOff_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit AvailabilityManagerHighTemperatureTurnOff(std::shared_ptr<detail::AvailabilityManagerHighTemperatureTurnOff_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
