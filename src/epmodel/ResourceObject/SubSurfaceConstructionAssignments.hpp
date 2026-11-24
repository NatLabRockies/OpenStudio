/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SUBSURFACECONSTRUCTIONASSIGNMENTS_HPP
#define EPMODEL_SUBSURFACECONSTRUCTIONASSIGNMENTS_HPP

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
    class SubSurfaceConstructionAssignments_Impl;
  }

  /** \brief Sub-surface constructions, by sub-surface type, for one boundary-condition category of a ConstructionAssignmentSet.
   *
   * \par EnergyPlus object
   * \epobject{group-surface-construction-elements.html#subsurfaceconstructionassignments,SubSurfaceConstructionAssignments}
   *
   * \par Important behavior
   * EnergyPlus resolves the generic <code>Window</code> sub-surface type through the fixed-window construction.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::DefaultSubSurfaceConstructions</code>.
   * <b>Renamed:</b> <code>openstudio::model::DefaultSubSurfaceConstructions</code> is
   * <code>openstudio::epmodel::SubSurfaceConstructionAssignments</code>, matching the EnergyPlus object name. The methods names match the Model ones.
   *
   * \par Known limitations
   * No known EPModel-specific limitations.
   */
  class EPMODEL_API SubSurfaceConstructionAssignments : public ResourceObject
  {
   public:
    explicit SubSurfaceConstructionAssignments(const Model& model);

    virtual ~SubSurfaceConstructionAssignments() override = default;
    SubSurfaceConstructionAssignments(const SubSurfaceConstructionAssignments& other) = default;
    SubSurfaceConstructionAssignments(SubSurfaceConstructionAssignments&& other) = default;
    SubSurfaceConstructionAssignments& operator=(const SubSurfaceConstructionAssignments&) = default;
    SubSurfaceConstructionAssignments& operator=(SubSurfaceConstructionAssignments&&) = default;

    static IddObjectType iddObjectType();

    boost::optional<ConstructionBase> fixedWindowConstruction() const;
    bool setFixedWindowConstruction(const ConstructionBase& construction);
    void resetFixedWindowConstruction();

    boost::optional<ConstructionBase> operableWindowConstruction() const;
    bool setOperableWindowConstruction(const ConstructionBase& construction);
    void resetOperableWindowConstruction();

    boost::optional<ConstructionBase> doorConstruction() const;
    bool setDoorConstruction(const ConstructionBase& construction);
    void resetDoorConstruction();

    boost::optional<ConstructionBase> glassDoorConstruction() const;
    bool setGlassDoorConstruction(const ConstructionBase& construction);
    void resetGlassDoorConstruction();

    boost::optional<ConstructionBase> overheadDoorConstruction() const;
    bool setOverheadDoorConstruction(const ConstructionBase& construction);
    void resetOverheadDoorConstruction();

    boost::optional<ConstructionBase> skylightConstruction() const;
    bool setSkylightConstruction(const ConstructionBase& construction);
    void resetSkylightConstruction();

    boost::optional<ConstructionBase> tubularDaylightDomeConstruction() const;
    bool setTubularDaylightDomeConstruction(const ConstructionBase& construction);
    void resetTubularDaylightDomeConstruction();

    boost::optional<ConstructionBase> tubularDaylightDiffuserConstruction() const;
    bool setTubularDaylightDiffuserConstruction(const ConstructionBase& construction);
    void resetTubularDaylightDiffuserConstruction();

    /// Fills each empty construction slot of this object from other. Slots already set on this object are kept.
    void merge(const SubSurfaceConstructionAssignments& other);

   protected:
    using ImplType = detail::SubSurfaceConstructionAssignments_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SubSurfaceConstructionAssignments(std::shared_ptr<detail::SubSurfaceConstructionAssignments_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
