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

  /** \brief SurfacePropertyIncidentSolarMultiplier.
   *
   * \par EnergyPlus object
   * \epobject{group-advanced-surface-concepts.html#surfacepropertyincidentsolarmultiplier,SurfaceProperty:IncidentSolarMultiplier}.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::SurfacePropertyIncidentSolarMultiplier</code>. <b>Changed:</b> EPModel exposes direct construction from <code>Model</code>; Model construction requires a subsurface. The incident-solar multiplier is exposed; surface and schedule relationships are not available.
   *
   * \par Known limitations
   * No known EPModel-specific limitations.
   */
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
