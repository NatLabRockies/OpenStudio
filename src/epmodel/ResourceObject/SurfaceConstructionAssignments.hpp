/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SURFACECONSTRUCTIONASSIGNMENTS_HPP
#define EPMODEL_SURFACECONSTRUCTIONASSIGNMENTS_HPP

#include "EPModelAPI.hpp"
#include "ResourceObject/ResourceObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <boost/optional.hpp>

#include <memory>

namespace openstudio {
namespace epmodel {

  class ConstructionBase;
  class Model;

  namespace detail {
    class SurfaceConstructionAssignments_Impl;
  }

  /** \brief Floor, wall, and roof/ceiling constructions for one boundary-condition category of a ConstructionAssignmentSet.
   *
   * \par EnergyPlus object
   * \epobject{group-surface-construction-elements.html#surfaceconstructionassignments,SurfaceConstructionAssignments}
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::DefaultSurfaceConstructions</code>.
   * <b>Renamed:</b> <code>openstudio::model::DefaultSurfaceConstructions</code> is
   * <code>openstudio::epmodel::SurfaceConstructionAssignments</code>, matching the EnergyPlus object name. The methods names match the Model ones.
   *
   * \par Known limitations
   * No known EPModel-specific limitations.
   */
  class EPMODEL_API SurfaceConstructionAssignments : public ResourceObject
  {
   public:
    explicit SurfaceConstructionAssignments(const Model& model);

    virtual ~SurfaceConstructionAssignments() override = default;
    SurfaceConstructionAssignments(const SurfaceConstructionAssignments& other) = default;
    SurfaceConstructionAssignments(SurfaceConstructionAssignments&& other) = default;
    SurfaceConstructionAssignments& operator=(const SurfaceConstructionAssignments&) = default;
    SurfaceConstructionAssignments& operator=(SurfaceConstructionAssignments&&) = default;

    static IddObjectType iddObjectType();

    boost::optional<ConstructionBase> floorConstruction() const;
    bool setFloorConstruction(const ConstructionBase& construction);
    void resetFloorConstruction();

    boost::optional<ConstructionBase> wallConstruction() const;
    bool setWallConstruction(const ConstructionBase& construction);
    void resetWallConstruction();

    boost::optional<ConstructionBase> roofCeilingConstruction() const;
    bool setRoofCeilingConstruction(const ConstructionBase& construction);
    void resetRoofCeilingConstruction();

    /// Fills each empty construction slot of this object from other. Slots already set on this object are kept.
    void merge(const SurfaceConstructionAssignments& other);

   protected:
    using ImplType = detail::SurfaceConstructionAssignments_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SurfaceConstructionAssignments(std::shared_ptr<detail::SurfaceConstructionAssignments_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
