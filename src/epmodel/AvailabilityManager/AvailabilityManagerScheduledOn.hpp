/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AVAILABILITYMANAGERSCHEDULEDON_HPP
#define EPMODEL_AVAILABILITYMANAGERSCHEDULEDON_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class AvailabilityManagerScheduledOn_Impl;
}

class EPMODEL_API AvailabilityManagerScheduledOn : public ModelObject
{
 public:
  explicit AvailabilityManagerScheduledOn(const Model& model);

  virtual ~AvailabilityManagerScheduledOn() override = default;
  AvailabilityManagerScheduledOn(const AvailabilityManagerScheduledOn& other) = default;
  AvailabilityManagerScheduledOn(AvailabilityManagerScheduledOn&& other) = default;
  AvailabilityManagerScheduledOn& operator=(const AvailabilityManagerScheduledOn&) = default;
  AvailabilityManagerScheduledOn& operator=(AvailabilityManagerScheduledOn&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: Preserves model-counterpart class naming for AvailabilityManagerScheduledOn.
  // - Field Mapping: EnergyPlus AvailabilityManager:ScheduledOn exposes only Schedule Name beyond Name.
  // - ForwardTranslator evidence: model::ForwardTranslateAvailabilityManagerScheduledOn maps only Schedule Name.
  // - TODO(parity): Keep Schedule Name as a relationship field for a later relationship-focused pass.

 protected:
  using ImplType = detail::AvailabilityManagerScheduledOn_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit AvailabilityManagerScheduledOn(std::shared_ptr<detail::AvailabilityManagerScheduledOn_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
