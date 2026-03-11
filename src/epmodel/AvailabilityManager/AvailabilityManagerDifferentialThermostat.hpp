/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AVAILABILITYMANAGERDIFFERENTIALTHERMOSTAT_HPP
#define EPMODEL_AVAILABILITYMANAGERDIFFERENTIALTHERMOSTAT_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class AvailabilityManagerDifferentialThermostat_Impl;
}

class EPMODEL_API AvailabilityManagerDifferentialThermostat : public ModelObject
{
 public:
  explicit AvailabilityManagerDifferentialThermostat(const Model& model);

  virtual ~AvailabilityManagerDifferentialThermostat() override = default;
  AvailabilityManagerDifferentialThermostat(const AvailabilityManagerDifferentialThermostat& other) = default;
  AvailabilityManagerDifferentialThermostat(AvailabilityManagerDifferentialThermostat&& other) = default;
  AvailabilityManagerDifferentialThermostat& operator=(const AvailabilityManagerDifferentialThermostat&) = default;
  AvailabilityManagerDifferentialThermostat& operator=(AvailabilityManagerDifferentialThermostat&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: Preserves openstudio::model scalar accessor names/signatures for this model-counterpart class.
  // - Field Mapping: temperatureDifferenceOnLimit maps to E+ Temperature Difference On Limit.
  // - Field Mapping: temperatureDifferenceOffLimit maps to E+ Temperature Difference Off Limit.
  // - TODO(parity): Keep relationship fields (hotNode/coldNode) out of this scalar-only scaffold pass.
  double temperatureDifferenceOnLimit() const;
  bool setTemperatureDifferenceOnLimit(double temperatureDifferenceOnLimit);

  double temperatureDifferenceOffLimit() const;
  bool setTemperatureDifferenceOffLimit(double temperatureDifferenceOffLimit);

 protected:
  using ImplType = detail::AvailabilityManagerDifferentialThermostat_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit AvailabilityManagerDifferentialThermostat(std::shared_ptr<detail::AvailabilityManagerDifferentialThermostat_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
