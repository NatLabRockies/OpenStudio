/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SPACE_HPP
#define EPMODEL_SPACE_HPP

#include "EPModelAPI.hpp"
#include "PlanarSurfaceGroup/PlanarSurfaceGroup.hpp"

#include "../utilities/geometry/Point3d.hpp"
#include "../utilities/idd/IddEnums.hpp"

#include <memory>

namespace openstudio {

class Polyhedron;
class Transformation;

namespace epmodel {

  class BuildingStory;
  class Model;
  class DesignSpecificationOutdoorAir;
  class Surface;
  class ThermalZone;

  namespace detail {
    class Space_Impl;
  }

  /** \brief Represents the EnergyPlus Space object.
   *
   * \par EnergyPlus object
   * \epobject{group-thermal-zone-description-geometry.html#space,Space}
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::Space</code>. <b>Changed:</b> design-specification outdoor air is routed through <code>Sizing:Zone</code> and <code>DesignSpecification:OutdoorAir:SpaceList</code>, rather than an OS:Space field. EPModel stores ceiling height, volume, and floor area directly on <code>Space</code>.
   *
   * \par Known limitations
   * Surface assignment synchronizes redundant BuildingSurface Zone Name fields. Unzoned-space outdoor-air assignment uses an orphan space-list object.
   */
  class EPMODEL_API Space : public PlanarSurfaceGroup
  {
   public:
    explicit Space(const Model& model);

    static boost::optional<Space> fromFloorPrint(const std::vector<Point3d>& floorPrint, double floorHeight, const Model& model,
                                                 const std::string& spaceName = {});

    virtual ~Space() override = default;
    Space(const Space& other) = default;
    Space(Space&& other) = default;
    Space& operator=(const Space&) = default;
    Space& operator=(Space&&) = default;

    static IddObjectType iddObjectType();

    double ceilingHeight() const;
    bool setCeilingHeight(double ceilingHeight);
    bool isCeilingHeightDefaulted() const;
    bool isCeilingHeightAutocalculated() const;
    void autocalculateCeilingHeight();
    void resetCeilingHeight();

    double volume() const;
    bool setVolume(double volume);
    bool isVolumeDefaulted() const;
    bool isVolumeAutocalculated() const;
    void autocalculateVolume();
    void resetVolume();

    double floorArea() const;
    bool setFloorArea(double floorArea);
    bool isFloorAreaDefaulted() const;
    bool isFloorAreaAutocalculated() const;
    void autocalculateFloorArea();
    void resetFloorArea();

    boost::optional<BuildingStory> buildingStory() const;
    bool setBuildingStory(BuildingStory& buildingStory);

    boost::optional<ThermalZone> thermalZone() const;
    bool setThermalZone(const ThermalZone& thermalZone);
    void resetThermalZone();
    boost::optional<DesignSpecificationOutdoorAir> designSpecificationOutdoorAir() const;
    bool setDesignSpecificationOutdoorAir(const DesignSpecificationOutdoorAir& designSpecificationOutdoorAir);

    /// Returns all \link Surface Surfaces \endlink in this space.
    std::vector<Surface> surfaces() const;

    /** Unmatch any matched surfaces and sub surfaces in this space. */
    void unmatchSurfaces();

    /** Match surfaces and sub surfaces in this space with those in the other. */
    void matchSurfaces(Space& other);

    /** Intersect surfaces in this space with those in the other. */
    void intersectSurfaces(Space& other);

    Polyhedron polyhedron() const;
    bool isEnclosedVolume() const;

   protected:
    using ImplType = detail::Space_Impl;

    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;
    friend class Model;

    explicit Space(std::shared_ptr<detail::Space_Impl> impl);

   private:
    REGISTER_LOGGER("openstudio.epmodel.Space");
  };

  /** Intersect surfaces between all spaces in the vector. */
  EPMODEL_API void intersectSurfaces(std::vector<Space>& spaces);

  /** Match surfaces and sub surfaces between all spaces in the vector. */
  EPMODEL_API void matchSurfaces(std::vector<Space>& spaces);

  /** Unmatch surfaces and sub surfaces for all spaces in the vector. */
  EPMODEL_API void unmatchSurfaces(std::vector<Space>& spaces);

}  // namespace epmodel
}  // namespace openstudio

#endif
