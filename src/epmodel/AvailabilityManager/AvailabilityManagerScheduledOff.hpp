/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AVAILABILITYMANAGERSCHEDULEDOFF_HPP
#define EPMODEL_AVAILABILITYMANAGERSCHEDULEDOFF_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class AvailabilityManagerScheduledOff_Impl;
}

class EPMODEL_API AvailabilityManagerScheduledOff : public ModelObject
{
 public:
  explicit AvailabilityManagerScheduledOff(const Model& model);

  virtual ~AvailabilityManagerScheduledOff() override = default;
  AvailabilityManagerScheduledOff(const AvailabilityManagerScheduledOff& other) = default;
  AvailabilityManagerScheduledOff(AvailabilityManagerScheduledOff&& other) = default;
  AvailabilityManagerScheduledOff& operator=(const AvailabilityManagerScheduledOff&) = default;
  AvailabilityManagerScheduledOff& operator=(AvailabilityManagerScheduledOff&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: Preserves model-counterpart class naming for AvailabilityManagerScheduledOff.
  // - Field Mapping: EnergyPlus AvailabilityManager:ScheduledOff exposes only Schedule Name beyond Name.
  // - ForwardTranslator evidence: model::ForwardTranslateAvailabilityManagerScheduledOff maps only Schedule Name.
  // - TODO(parity): Keep Schedule Name as a relationship field for a later relationship-focused pass.

 protected:
  using ImplType = detail::AvailabilityManagerScheduledOff_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit AvailabilityManagerScheduledOff(std::shared_ptr<detail::AvailabilityManagerScheduledOff_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
