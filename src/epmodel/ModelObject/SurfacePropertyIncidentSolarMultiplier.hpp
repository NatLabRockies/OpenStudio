/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_SURFACEPROPERTYINCIDENTSOLARMULTIPLIER_HPP
#define EPMODEL_SURFACEPROPERTYINCIDENTSOLARMULTIPLIER_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class SurfacePropertyIncidentSolarMultiplier_Impl;
  }

  class EPMODEL_API SurfacePropertyIncidentSolarMultiplier : public ModelObject
  {
   public:
    explicit SurfacePropertyIncidentSolarMultiplier(const Model& model);

    virtual ~SurfacePropertyIncidentSolarMultiplier() override = default;
    SurfacePropertyIncidentSolarMultiplier(const SurfacePropertyIncidentSolarMultiplier& other) = default;
    SurfacePropertyIncidentSolarMultiplier(SurfacePropertyIncidentSolarMultiplier&& other) = default;
    SurfacePropertyIncidentSolarMultiplier& operator=(const SurfacePropertyIncidentSolarMultiplier&) = default;
    SurfacePropertyIncidentSolarMultiplier& operator=(SurfacePropertyIncidentSolarMultiplier&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: Preserve the openstudio::model scalar accessor naming (incidentSolarMultiplier/setIncidentSolarMultiplier) for this model-counterpart type.
    // - Field Mapping: incidentSolarMultiplier maps to SurfaceProperty:IncidentSolarMultiplier's Incident Solar Multiplier field and defaults to 1.0 per translateSurfacePropertyIncidentSolarMultiplier.
    // - Field Mapping: Surface Name (GlazedExtSubSurfNames) and Incident Solar Multiplier Schedule Name (ScheduleNames) are object-list references and therefore excluded here.
    double incidentSolarMultiplier() const;
    bool setIncidentSolarMultiplier(double incidentSolarMultiplier);

   protected:
    using ImplType = detail::SurfacePropertyIncidentSolarMultiplier_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SurfacePropertyIncidentSolarMultiplier(std::shared_ptr<detail::SurfacePropertyIncidentSolarMultiplier_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
