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

  /** BuildingStory is a transient OpenStudio concept backed by OS:BuildingStory IDD storage.
   *  It owns a companion SpaceList that IS written to the EnergyPlus IDF. */
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
