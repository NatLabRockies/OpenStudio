/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CONSTRUCTIONASSIGNMENTSET_HPP
#define EPMODEL_CONSTRUCTIONASSIGNMENTSET_HPP

#include "EPModelAPI.hpp"
#include "ResourceObject/ResourceObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <boost/optional.hpp>

#include <memory>

namespace openstudio {
namespace epmodel {

  class ConstructionBase;
  class Model;
  class SubSurfaceConstructionAssignments;
  class SurfaceConstructionAssignments;

  namespace detail {
    class ConstructionAssignmentSet_Impl;
  }

  /** \brief Assigns constructions to surfaces, sub-surfaces, and interior partitions that do not name one, based on their type and
   *  outside boundary condition.
   *
   * \par EnergyPlus object
   * \epobject{group-surface-construction-elements.html#constructionassignmentset,ConstructionAssignmentSet}
   *
   * \par Important behavior
   * A set applies only when a Building or Space references it, through <code>Building::setConstructionAssignmentSet</code> or
   * <code>Space::setConstructionAssignmentSet</code>. EnergyPlus uses the Space-level set first, then the Building-level set.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::DefaultConstructionSet</code>.
   * <b>Renamed:</b> <code>openstudio::model::DefaultConstructionSet</code> is <code>openstudio::epmodel::ConstructionAssignmentSet</code>,
   * matching the EnergyPlus object name. The surface and sub-surface accessors are renamed to match the EnergyPlus fields, for example
   * <code>defaultExteriorSurfaceConstructions()</code> is <code>exteriorSurfaceConstructionAssignments()</code> and
   * <code>defaultInteriorSubSurfaceConstructions()</code> is <code>interiorSubSurfaceConstructionAssignments()</code>, with matching
   * setters and resets. They return <code>SurfaceConstructionAssignments</code> and <code>SubSurfaceConstructionAssignments</code>.
   * <b>Not yet available:</b> <code>getDefaultConstruction()</code> and <code>collapseToSpaceAndBuilding()</code>.
   * <b>Removed:</b> <code>spaceShadingConstruction()</code>, <code>buildingShadingConstruction()</code>,
   * <code>siteShadingConstruction()</code> and their setters and resets. The EnergyPlus object has no shading slots, and EnergyPlus
   * shading surfaces have no construction field.
   *
   * \par Known limitations
   * Only Building and Space can reference a set. Model's SpaceType and BuildingStory assignments have no EnergyPlus equivalent.
   */
  class EPMODEL_API ConstructionAssignmentSet : public ResourceObject
  {
   public:
    explicit ConstructionAssignmentSet(const Model& model);

    virtual ~ConstructionAssignmentSet() override = default;
    ConstructionAssignmentSet(const ConstructionAssignmentSet& other) = default;
    ConstructionAssignmentSet(ConstructionAssignmentSet&& other) = default;
    ConstructionAssignmentSet& operator=(const ConstructionAssignmentSet&) = default;
    ConstructionAssignmentSet& operator=(ConstructionAssignmentSet&&) = default;

    static IddObjectType iddObjectType();

    boost::optional<SurfaceConstructionAssignments> exteriorSurfaceConstructionAssignments() const;
    bool setExteriorSurfaceConstructionAssignments(const SurfaceConstructionAssignments& surfaceConstructionAssignments);
    void resetExteriorSurfaceConstructionAssignments();

    boost::optional<SurfaceConstructionAssignments> interiorSurfaceConstructionAssignments() const;
    bool setInteriorSurfaceConstructionAssignments(const SurfaceConstructionAssignments& surfaceConstructionAssignments);
    void resetInteriorSurfaceConstructionAssignments();

    boost::optional<SurfaceConstructionAssignments> groundContactSurfaceConstructionAssignments() const;
    bool setGroundContactSurfaceConstructionAssignments(const SurfaceConstructionAssignments& surfaceConstructionAssignments);
    void resetGroundContactSurfaceConstructionAssignments();

    boost::optional<SubSurfaceConstructionAssignments> exteriorSubSurfaceConstructionAssignments() const;
    bool setExteriorSubSurfaceConstructionAssignments(const SubSurfaceConstructionAssignments& subSurfaceConstructionAssignments);
    void resetExteriorSubSurfaceConstructionAssignments();

    boost::optional<SubSurfaceConstructionAssignments> interiorSubSurfaceConstructionAssignments() const;
    bool setInteriorSubSurfaceConstructionAssignments(const SubSurfaceConstructionAssignments& subSurfaceConstructionAssignments);
    void resetInteriorSubSurfaceConstructionAssignments();

    boost::optional<ConstructionBase> interiorPartitionConstruction() const;
    bool setInteriorPartitionConstruction(const ConstructionBase& construction);
    void resetInteriorPartitionConstruction();

    boost::optional<ConstructionBase> adiabaticSurfaceConstruction() const;
    bool setAdiabaticSurfaceConstruction(const ConstructionBase& construction);
    void resetAdiabaticSurfaceConstruction();

    /** Fills each empty slot of this set from other. Slots already set on this set are kept. When both sets reference different
     *  surface or sub-surface assignments for the same category, those are merged too; if this set's assignments object is also used
     *  elsewhere, it is cloned first so the other users are unaffected. */
    void merge(const ConstructionAssignmentSet& other);

   protected:
    using ImplType = detail::ConstructionAssignmentSet_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ConstructionAssignmentSet(std::shared_ptr<detail::ConstructionAssignmentSet_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
