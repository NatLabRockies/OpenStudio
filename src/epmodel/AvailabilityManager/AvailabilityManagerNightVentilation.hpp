/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AVAILABILITYMANAGERNIGHTVENTILATION_HPP
#define EPMODEL_AVAILABILITYMANAGERNIGHTVENTILATION_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class AvailabilityManagerNightVentilation_Impl;
  }

  class EPMODEL_API AvailabilityManagerNightVentilation : public ModelObject
  {
   public:
    explicit AvailabilityManagerNightVentilation(const Model& model);

    virtual ~AvailabilityManagerNightVentilation() override = default;
    AvailabilityManagerNightVentilation(const AvailabilityManagerNightVentilation& other) = default;
    AvailabilityManagerNightVentilation(AvailabilityManagerNightVentilation&& other) = default;
    AvailabilityManagerNightVentilation& operator=(const AvailabilityManagerNightVentilation&) = default;
    AvailabilityManagerNightVentilation& operator=(AvailabilityManagerNightVentilation&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: Preserves openstudio::model scalar accessor names/signatures for this model-counterpart class.
    // - Field Mapping: ventilationTemperatureDifference, ventilationTemperatureLowLimit, and
    //   nightVentingFlowFraction map directly to E+ AvailabilityManager:NightVentilation fields.
    // - TODO(parity): Keep relationship fields (Applicability/Fan/VentilationTemperature schedules and ControlZone) out of this scalar-only scaffold pass.
    /** ventilationTemperatureDifference */
    double ventilationTemperatureDifference() const;
    bool setVentilationTemperatureDifference(double ventilationTemperatureDifference);

    /** ventilationTemperatureLowLimit */
    double ventilationTemperatureLowLimit() const;
    bool setVentilationTemperatureLowLimit(double ventilationTemperatureLowLimit);

    /** nightVentingFlowFraction */
    double nightVentingFlowFraction() const;
    bool setNightVentingFlowFraction(double nightVentingFlowFraction);

   protected:
    using ImplType = detail::AvailabilityManagerNightVentilation_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit AvailabilityManagerNightVentilation(std::shared_ptr<detail::AvailabilityManagerNightVentilation_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
