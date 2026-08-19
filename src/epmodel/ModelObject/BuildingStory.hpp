/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_BUILDINGSTORY_HPP
#define EPMODEL_BUILDINGSTORY_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class Space;
  class SpaceList;

  namespace detail {
    class BuildingStory_Impl;
  }

  /** \brief Represents a building story and its associated spaces.
   *
   * \par EnergyPlus object
   * No standalone EnergyPlus object; this is a projected wrapper backed by <code>OS:BuildingStory</code> storage and a companion \epobject{group-thermal-zone-description-geometry.html#spacelist,SpaceList}.
   *
   * \par Important behavior
   * Story metadata and the space association are written through the companion <code>SpaceList</code>.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::BuildingStory</code>.
   * Model-only story conveniences such as default construction/schedule sets, rendering color, coordinate searches, and bounding-box helpers are not exposed.
   *
   * \par Known limitations
   * Story metadata is projected through the companion <code>SpaceList</code>; it is not an independent EnergyPlus object.
   */
  class EPMODEL_API BuildingStory : public ModelObject
  {
   public:
    static constexpr bool is_transient = true;

    explicit BuildingStory(const Model& model);

    virtual ~BuildingStory() override = default;
    BuildingStory(const BuildingStory& other) = default;
    BuildingStory(BuildingStory&& other) = default;
    BuildingStory& operator=(const BuildingStory&) = default;
    BuildingStory& operator=(BuildingStory&&) = default;

    static IddObjectType iddObjectType();

    boost::optional<double> nominalZCoordinate() const;
    bool setNominalZCoordinate(double nominalZCoordinate);
    void resetNominalZCoordinate();

    boost::optional<double> nominalFloortoFloorHeight() const;
    bool setNominalFloortoFloorHeight(double nominalFloortoFloorHeight);
    void resetNominalFloortoFloorHeight();

    boost::optional<double> nominalFloortoCeilingHeight() const;
    bool setNominalFloortoCeilingHeight(double nominalFloortoCeilingHeight);
    void resetNominalFloortoCeilingHeight();

    /** Returns the companion SpaceList written to the EnergyPlus IDF. */
    SpaceList spaceList() const;

    /** Reconstruct a BuildingStory from an existing SpaceList whose comment encodes
     *  BuildingStory metadata (starts with "BuildingStory(").
     *  Returns boost::none if the SpaceList is not a BuildingStory companion. */
    static boost::optional<BuildingStory> fromSpaceList(const SpaceList& spaceList);

    /** Add a Space to this BuildingStory. */
    bool addSpace(const Space& space);

    /** Returns all Spaces on this BuildingStory. */
    std::vector<Space> spaces() const;

   protected:
    using ImplType = detail::BuildingStory_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit BuildingStory(std::shared_ptr<detail::BuildingStory_Impl> impl);

   private:
    explicit BuildingStory(const SpaceList& spaceList);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
