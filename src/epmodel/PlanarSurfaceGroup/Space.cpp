/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "PlanarSurfaceGroup/Space.hpp"
#include "PlanarSurfaceGroup/Space_Impl.hpp"

#include "Loop/AirLoopHVAC.hpp"
#include "Loop/AirLoopHVAC_Impl.hpp"
#include "Model.hpp"
#include "PlanarSurface/Surface.hpp"
#include "PlanarSurface/Surface_Impl.hpp"
#include "PlanarSurface/SubSurface.hpp"
#include "PlanarSurface/SubSurface_Impl.hpp"
#include "ResourceObject/DesignSpecificationOutdoorAir.hpp"
#include "ResourceObject/DesignSpecificationOutdoorAir_Impl.hpp"
#include "ModelObject/BuildingStory.hpp"
#include "ModelObject/BuildingStory_Impl.hpp"
#include "ModelObject/SpaceList.hpp"
#include "ModelObject/SpaceList_Impl.hpp"
#include "ModelObject/DesignSpecificationOutdoorAirSpaceList.hpp"
#include "ModelObject/DesignSpecificationOutdoorAirSpaceList_Impl.hpp"
#include "SizingZone.hpp"
#include "SizingZone_Impl.hpp"
#include "HVACComponent/ThermalZone.hpp"
#include "HVACComponent/ThermalZone_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/geometry/BoundingBox.hpp>
#include <utilities/geometry/Geometry.hpp>
#include <utilities/geometry/Polyhedron.hpp>
#include <utilities/geometry/Transformation.hpp>
#include <utilities/geometry/Vector3d.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/Sizing_Zone_FieldEnums.hxx>
#include <utilities/idd/Space_FieldEnums.hxx>

#include <algorithm>
#include <fmt/format.h>

namespace openstudio {
namespace epmodel {

  Space::Space(const Model& model) : PlanarSurfaceGroup(Space::iddObjectType(), model) {
    auto impl = getImpl<detail::Space_Impl>();
    OS_ASSERT(impl);
    detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
    impl->canonicalize(context);
  }

  Space::Space(std::shared_ptr<detail::Space_Impl> impl) : PlanarSurfaceGroup(std::move(impl)) {}

  IddObjectType Space::iddObjectType() {
    return IddObjectType::Space;
  }

  boost::optional<Space> Space::fromFloorPrint(const std::vector<Point3d>& floorPrint, double floorHeight, const Model& model,
                                               const std::string& spaceName) {
    if (floorHeight <= 0) {
      LOG(Error, "Cannot create a space with floorHeight " << floorHeight << ".");
      return boost::none;
    }

    unsigned numPoints = floorPrint.size();
    if (numPoints < 3) {
      LOG(Error, "Cannot create a space for floorPrint of size " << floorPrint.size() << ".");
      return boost::none;
    }

    double z = floorPrint[0].z();
    double tol = 0.000001;
    for (const Point3d& point : floorPrint) {
      if (std::abs(point.z() - z) > tol) {
        LOG(Error, "Inconsistent z height in floorPrint.");
        return boost::none;
      }
    }

    std::vector<Point3d> reorderedFloorPrint;
    reorderedFloorPrint.reserve(numPoints);
    std::transform(floorPrint.cbegin(), floorPrint.cend(), std::back_inserter(reorderedFloorPrint),
                   [&z](const auto& pt) { return Point3d{pt.x(), pt.y(), z}; });

    boost::optional<Vector3d> outwardNormal = getOutwardNormal(reorderedFloorPrint);
    if (!outwardNormal) {
      LOG(Error, "Cannot compute outwardNormal for floorPrint.");
      return boost::none;
    }

    if (outwardNormal->z() > -1 + tol) {
      LOG(Error, "OutwardNormal of floorPrint must point down to create space.");
      return boost::none;
    }

    Space space(model);
    if (!spaceName.empty()) {
      space.setName(spaceName);
    }

    // Floor
    Surface floor(reorderedFloorPrint, model);
    if (!spaceName.empty()) {
      floor.setName(fmt::format("{} Floor", space.nameString()));
    }
    floor.setSpace(space);

    double zCeiling = z + floorHeight;
    std::vector<Point3d> points;
    points.reserve(4);

    // Walls
    for (unsigned i = 1; i <= numPoints; ++i) {
      points = {
        {reorderedFloorPrint[i - 1].x(), reorderedFloorPrint[i - 1].y(), zCeiling},
        {reorderedFloorPrint[i % numPoints].x(), reorderedFloorPrint[i % numPoints].y(), zCeiling},
        {reorderedFloorPrint[i % numPoints].x(), reorderedFloorPrint[i % numPoints].y(), z},
        {reorderedFloorPrint[i - 1].x(), reorderedFloorPrint[i - 1].y(), z},
      };
      Surface wall(points, model);
      if (!spaceName.empty()) {
        wall.setName(fmt::format("{} Wall {}", space.nameString(), i));
      }
      wall.setSpace(space);
    }

    // RoofCeiling
    std::vector<Point3d> ceilingPoints;
    ceilingPoints.reserve(numPoints);
    std::transform(reorderedFloorPrint.crbegin(), reorderedFloorPrint.crend(), std::back_inserter(ceilingPoints),
                   [zCeiling](const auto& pt) { return Point3d{pt.x(), pt.y(), zCeiling}; });
    Surface roofCeiling(ceilingPoints, model);
    if (!spaceName.empty()) {
      roofCeiling.setName(fmt::format("{} RoofCeiling", space.nameString()));
    }
    roofCeiling.setSpace(space);

    return space;
  }

  double Space::ceilingHeight() const {
    return getImpl<detail::Space_Impl>()->ceilingHeight();
  }

  bool Space::isCeilingHeightDefaulted() const {
    return getImpl<detail::Space_Impl>()->isCeilingHeightDefaulted();
  }

  bool Space::isCeilingHeightAutocalculated() const {
    return getImpl<detail::Space_Impl>()->isCeilingHeightAutocalculated();
  }

  bool Space::setCeilingHeight(double ceilingHeight) {
    return getImpl<detail::Space_Impl>()->setCeilingHeight(ceilingHeight);
  }

  void Space::autocalculateCeilingHeight() {
    getImpl<detail::Space_Impl>()->autocalculateCeilingHeight();
  }

  void Space::resetCeilingHeight() {
    getImpl<detail::Space_Impl>()->resetCeilingHeight();
  }

  double Space::volume() const {
    return getImpl<detail::Space_Impl>()->volume();
  }

  bool Space::isVolumeDefaulted() const {
    return getImpl<detail::Space_Impl>()->isVolumeDefaulted();
  }

  bool Space::isVolumeAutocalculated() const {
    return getImpl<detail::Space_Impl>()->isVolumeAutocalculated();
  }

  bool Space::setVolume(double volume) {
    return getImpl<detail::Space_Impl>()->setVolume(volume);
  }

  void Space::autocalculateVolume() {
    getImpl<detail::Space_Impl>()->autocalculateVolume();
  }

  void Space::resetVolume() {
    getImpl<detail::Space_Impl>()->resetVolume();
  }

  double Space::floorArea() const {
    return getImpl<detail::Space_Impl>()->floorArea();
  }

  bool Space::isFloorAreaDefaulted() const {
    return getImpl<detail::Space_Impl>()->isFloorAreaDefaulted();
  }

  bool Space::isFloorAreaAutocalculated() const {
    return getImpl<detail::Space_Impl>()->isFloorAreaAutocalculated();
  }

  bool Space::setFloorArea(double floorArea) {
    return getImpl<detail::Space_Impl>()->setFloorArea(floorArea);
  }

  void Space::autocalculateFloorArea() {
    getImpl<detail::Space_Impl>()->autocalculateFloorArea();
  }

  void Space::resetFloorArea() {
    getImpl<detail::Space_Impl>()->resetFloorArea();
  }

  boost::optional<BuildingStory> Space::buildingStory() const {
    return getImpl<detail::Space_Impl>()->buildingStory();
  }

  bool Space::setBuildingStory(BuildingStory& buildingStory) {
    return getImpl<detail::Space_Impl>()->setBuildingStory(buildingStory);
  }

  boost::optional<ThermalZone> Space::thermalZone() const {
    return getImpl<detail::Space_Impl>()->thermalZone();
  }

  bool Space::setThermalZone(const ThermalZone& thermalZone) {
    return getImpl<detail::Space_Impl>()->setThermalZone(thermalZone);
  }

  void Space::resetThermalZone() {
    return getImpl<detail::Space_Impl>()->resetThermalZone();
  }

  boost::optional<DesignSpecificationOutdoorAir> Space::designSpecificationOutdoorAir() const {
    return getImpl<detail::Space_Impl>()->designSpecificationOutdoorAir();
  }

  bool Space::setDesignSpecificationOutdoorAir(const DesignSpecificationOutdoorAir& designSpecificationOutdoorAir) {
    return getImpl<detail::Space_Impl>()->setDesignSpecificationOutdoorAir(designSpecificationOutdoorAir);
  }

  std::vector<Surface> Space::surfaces() const {
    return getImpl<detail::Space_Impl>()->surfaces();
  }

  void Space::unmatchSurfaces() {
    getImpl<detail::Space_Impl>()->unmatchSurfaces();
  }

  void Space::matchSurfaces(Space& other) {
    getImpl<detail::Space_Impl>()->matchSurfaces(other);
  }

  void Space::intersectSurfaces(Space& other) {
    getImpl<detail::Space_Impl>()->intersectSurfaces(other);
  }

  Polyhedron Space::polyhedron() const {
    return getImpl<detail::Space_Impl>()->polyhedron();
  }

  bool Space::isEnclosedVolume() const {
    return getImpl<detail::Space_Impl>()->isEnclosedVolume();
  }

  void matchSurfaces(std::vector<Space>& spaces) {
    std::vector<BoundingBox> bounds;
    bounds.reserve(spaces.size());
    for (const Space& space : spaces) {
      bounds.push_back(space.transformation() * space.boundingBox());
    }

    for (unsigned i = 0; i < spaces.size(); ++i) {
      for (unsigned j = i + 1; j < spaces.size(); ++j) {
        if (!bounds[i].intersects(bounds[j])) {
          continue;
        }
        spaces[i].matchSurfaces(spaces[j]);
      }
    }
  }

  void unmatchSurfaces(std::vector<Space>& spaces) {
    for (Space& space : spaces) {
      space.unmatchSurfaces();
    }
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    namespace {

      constexpr const char* orphanDSOASpaceListName = "Orphan Spaces DSOA Space List";

      void syncAllAirLoopCMVEntries(const openstudio::epmodel::Model& model) {
        for (const auto& airLoop : model.getConcreteModelObjects<openstudio::epmodel::AirLoopHVAC>()) {
          airLoop.getImpl<openstudio::epmodel::detail::AirLoopHVAC_Impl>()->syncControllerMechanicalVentilationZoneOutdoorAirEntries();
        }
      }

      boost::optional<openstudio::epmodel::DesignSpecificationOutdoorAirSpaceList> findListContainingSpace(const openstudio::epmodel::Model& model,
                                                                                                           const openstudio::epmodel::Space& space) {
        boost::optional<openstudio::epmodel::DesignSpecificationOutdoorAirSpaceList> result;
        for (const auto& list : model.getConcreteModelObjects<openstudio::epmodel::DesignSpecificationOutdoorAirSpaceList>()) {
          if (list.designSpecificationOutdoorAir(space)) {
            if (result) {
              OS_ASSERT(result->handle() == list.handle());
            }
            result = list;
          }
        }
        return result;
      }

      openstudio::epmodel::DesignSpecificationOutdoorAirSpaceList getOrCreateOrphanSpaceList(const openstudio::epmodel::Model& model) {
        if (auto existing =
              model.getConcreteModelObjectByName<openstudio::epmodel::DesignSpecificationOutdoorAirSpaceList>(orphanDSOASpaceListName)) {
          return *existing;
        }
        auto created = openstudio::epmodel::DesignSpecificationOutdoorAirSpaceList(model);
        created.setName(orphanDSOASpaceListName);
        return created;
      }

      openstudio::epmodel::DesignSpecificationOutdoorAirSpaceList getOrCreateZoneSpaceList(const openstudio::epmodel::ThermalZone& zone) {
        auto sizingZone = zone.sizingZone();
        auto sizingZoneImpl = sizingZone.getImpl<openstudio::epmodel::detail::SizingZone_Impl>();
        OS_ASSERT(sizingZoneImpl);
        auto dsoaSpaceList = sizingZoneImpl->designSpecificationOutdoorAirSpaceList();
        if (dsoaSpaceList) {
          return *dsoaSpaceList;
        }

        auto created = openstudio::epmodel::DesignSpecificationOutdoorAirSpaceList(zone.model());
        created.setName(zone.nameString() + " DSOA Space List");
        OS_ASSERT(sizingZoneImpl->setDesignSpecificationOutdoorAirSpaceList(created));
        return created;
      }

      void removeSpaceFromAllListsExcept(const openstudio::epmodel::Space& space, openstudio::Handle keepListHandle) {
        for (const auto& list : space.model().getConcreteModelObjects<openstudio::epmodel::DesignSpecificationOutdoorAirSpaceList>()) {
          if (list.handle() == keepListHandle) {
            continue;
          }
          list.getImpl<openstudio::epmodel::detail::DesignSpecificationOutdoorAirSpaceList_Impl>()->removeSpace(space);
        }
      }

    }  // namespace

    double Space_Impl::ceilingHeight() const {
      boost::optional<double> value = getDouble(openstudio::SpaceFields::CeilingHeight, true);
      if (value) {
        return value.get();
      }

      double result = 0;

      // TODO: need a better method
      double roofHeight = 0;
      int numRoof = 0;
      double floorHeight = 0;
      int numFloor = 0;
      for (const Surface& surface : this->surfaces()) {
        if (istringEqual(surface.surfaceType(), "Floor")) {
          for (const Point3d& point : surface.vertices()) {
            floorHeight += point.z();
            ++numFloor;
          }
        } else if (Surface::isCeilingLike(surface.surfaceType())) {
          for (const Point3d& point : surface.vertices()) {
            roofHeight += point.z();
            ++numRoof;
          }
        }
      }

      if ((numRoof > 0) && (numFloor > 0)) {
        roofHeight /= numRoof;
        floorHeight /= numFloor;
        result = roofHeight - floorHeight;
      }

      return result;
    }

    bool Space_Impl::isCeilingHeightDefaulted() const {
      return isEmpty(openstudio::SpaceFields::CeilingHeight);
    }

    bool Space_Impl::isCeilingHeightAutocalculated() const {
      if (auto value = getString(openstudio::SpaceFields::CeilingHeight, true)) {
        return openstudio::istringEqual(*value, "autocalculate");
      }
      return false;
    }

    double Space_Impl::volume() const {
      boost::optional<double> value = getDouble(openstudio::SpaceFields::Volume, true);
      if (value) {
        return value.get();
      }

      auto volumePoly = this->polyhedron();

      if (volumePoly.isEnclosedVolume()) {
        if (volumePoly.isCompletelyInsideOut()) {
          const double volume = volumePoly.polyhedronVolume();
          LOG(Error, briefDescription() << " has all of its Surfaces that are inside-out. Call Space::fixSurfacesWithIncorrectOrientation().");
          return -volume;
        } else if (!volumePoly.hasAnySurfaceWithIncorrectOrientation()) {
          return volumePoly.polyhedronVolume();
        } else {
          LOG(Warn, briefDescription() << " has some Surfaces with incorrection orientation. Call Space::fixSurfacesWithIncorrectOrientation(). "
                                          "Falling back to ceilingHeight * floorArea. Volume calculation will be potentially inaccurate.");
        }
      } else {
        LOG(Warn, briefDescription() << " is not enclosed, there are " << volumePoly.edgesNotTwo().size()
                                     << " edges that aren't used exactly twice. "
                                        "Falling back to ceilingHeight * floorArea. Volume calculation will be potentially inaccurate.");
      }

      const double result = this->ceilingHeight() * this->floorArea();

      return result;
    }

    bool Space_Impl::isVolumeDefaulted() const {
      return isEmpty(openstudio::SpaceFields::Volume);
    }

    bool Space_Impl::isVolumeAutocalculated() const {
      if (auto value = getString(openstudio::SpaceFields::Volume, true)) {
        return openstudio::istringEqual(*value, "autocalculate");
      }
      return false;
    }

    double Space_Impl::floorArea() const {
      boost::optional<double> value = getDouble(openstudio::SpaceFields::FloorArea, true);
      if (value) {
        return value.get();
      }

      // get all surfaces, sort so results are repeatable
      std::vector<Surface> surfaces = this->surfaces();
      std::sort(surfaces.begin(), surfaces.end(), IdfObjectNameLess());

      double result = 0;
      for (const Surface& surface : surfaces) {
        if (istringEqual(surface.surfaceType(), "Floor")) {
          // TODO:
          // if (surface.isAirWall()) {
          //   continue;
          // }
          result += surface.grossArea();
        }
      }
      return result;
    }

    bool Space_Impl::isFloorAreaDefaulted() const {
      return isEmpty(openstudio::SpaceFields::FloorArea);
    }

    bool Space_Impl::isFloorAreaAutocalculated() const {
      if (auto value = getString(openstudio::SpaceFields::FloorArea, true)) {
        return openstudio::istringEqual(*value, "autocalculate");
      }
      return false;
    }

    bool Space_Impl::setCeilingHeight(double ceilingHeight) {
      const bool result = setDouble(openstudio::SpaceFields::CeilingHeight, ceilingHeight);
      OS_ASSERT(result);
      return result;
    }

    void Space_Impl::autocalculateCeilingHeight() {
      OS_ASSERT(setString(openstudio::SpaceFields::CeilingHeight, "autocalculate"));
    }

    void Space_Impl::resetCeilingHeight() {
      OS_ASSERT(setString(openstudio::SpaceFields::CeilingHeight, ""));
    }

    bool Space_Impl::setVolume(double volume) {
      const bool result = setDouble(openstudio::SpaceFields::Volume, volume);
      OS_ASSERT(result);
      return result;
    }

    void Space_Impl::autocalculateVolume() {
      OS_ASSERT(setString(openstudio::SpaceFields::Volume, "autocalculate"));
    }

    void Space_Impl::resetVolume() {
      OS_ASSERT(setString(openstudio::SpaceFields::Volume, ""));
    }

    bool Space_Impl::setFloorArea(double floorArea) {
      const bool result = setDouble(openstudio::SpaceFields::FloorArea, floorArea);
      OS_ASSERT(result);
      return result;
    }

    void Space_Impl::autocalculateFloorArea() {
      OS_ASSERT(setString(openstudio::SpaceFields::FloorArea, "autocalculate"));
    }

    void Space_Impl::resetFloorArea() {
      OS_ASSERT(setString(openstudio::SpaceFields::FloorArea, ""));
    }

    boost::optional<BuildingStory> Space_Impl::buildingStory() const {
      for (const WorkspaceObject& wo : getSources(IddObjectType::SpaceList)) {
        auto spaceList = wo.cast<SpaceList>();
        if (auto story = BuildingStory::fromSpaceList(spaceList)) {
          return story;
        }
      }
      return boost::none;
    }

    bool Space_Impl::setBuildingStory(BuildingStory& buildingStory) {
      return buildingStory.addSpace(getObject<Space>());
    }

    boost::optional<openstudio::epmodel::ThermalZone> Space_Impl::thermalZone() const {
      return getObject<openstudio::epmodel::Space>().getModelObjectTarget<openstudio::epmodel::ThermalZone>(openstudio::SpaceFields::ZoneName);
    }

    bool Space_Impl::setThermalZone(const openstudio::epmodel::ThermalZone& thermalZone) {
      auto thisSpace = getObject<openstudio::epmodel::Space>();
      auto currentDSOA = designSpecificationOutdoorAir();
      if (!setPointer(openstudio::SpaceFields::ZoneName, thermalZone.handle(), false)) {
        return false;
      }
      if (currentDSOA) {
        OS_ASSERT(setDesignSpecificationOutdoorAir(*currentDSOA));
      }
      return true;
    }

    void Space_Impl::resetThermalZone() {
      auto currentDSOA = designSpecificationOutdoorAir();
      OS_ASSERT(setString(openstudio::SpaceFields::ZoneName, ""));
      if (currentDSOA) {
        OS_ASSERT(setDesignSpecificationOutdoorAir(*currentDSOA));
      }
    }

    boost::optional<openstudio::epmodel::DesignSpecificationOutdoorAir> Space_Impl::designSpecificationOutdoorAir() const {
      auto thisSpace = getObject<openstudio::epmodel::Space>();
      if (auto zone = thermalZone()) {
        auto sizingZone = zone->sizingZone();
        auto sizingZoneImpl = sizingZone.getImpl<openstudio::epmodel::detail::SizingZone_Impl>();
        OS_ASSERT(sizingZoneImpl);
        if (auto dsoaSpaceList = sizingZoneImpl->designSpecificationOutdoorAirSpaceList()) {
          if (auto dsoa = dsoaSpaceList->designSpecificationOutdoorAir(thisSpace)) {
            return dsoa;
          }
        }
      }
      if (auto list = findListContainingSpace(model(), thisSpace)) {
        return list->designSpecificationOutdoorAir(thisSpace);
      }
      return boost::none;
    }

    bool Space_Impl::setDesignSpecificationOutdoorAir(const openstudio::epmodel::DesignSpecificationOutdoorAir& designSpecificationOutdoorAir) {
      auto thisSpace = getObject<openstudio::epmodel::Space>();
      if (designSpecificationOutdoorAir.model() != thisSpace.model()) {
        return false;
      }

      openstudio::epmodel::DesignSpecificationOutdoorAirSpaceList targetList =
        thermalZone() ? getOrCreateZoneSpaceList(*thermalZone()) : getOrCreateOrphanSpaceList(model());
      OS_ASSERT(targetList.getImpl<openstudio::epmodel::detail::DesignSpecificationOutdoorAirSpaceList_Impl>()->setDesignSpecificationOutdoorAir(
        thisSpace, designSpecificationOutdoorAir));

      removeSpaceFromAllListsExcept(thisSpace, targetList.handle());
      syncAllAirLoopCMVEntries(model());
      return true;
    }

    Polyhedron Space_Impl::polyhedron() const {
      auto sfs = surfaces();
      std::vector<Surface3d> surface3ds;
      surface3ds.reserve(sfs.size());
      for (size_t surfNum = 0; auto& surface : sfs) {
        surface3ds.emplace_back(surface.vertices(), surface.nameString(), surfNum++);
      }
      return {surface3ds};
    }

    bool Space_Impl::isEnclosedVolume() const {
      if (m_cachedIsEnclosed.has_value()) {
        return m_cachedIsEnclosed.get();
      }
      auto volumePoly = this->polyhedron();
      auto isVolEnclosed = volumePoly.isEnclosedVolume();
      if (!isVolEnclosed) {
        const auto edgesNot2 = volumePoly.edgesNotTwo();
        LOG(Warn, briefDescription() << " is not enclosed, there are " << edgesNot2.size() << " edges that aren't used exactly twice");
        for (const auto& edge : edgesNot2) {
          LOG(Debug, edge);
        }
      }
      return isVolEnclosed;
    }

    std::vector<Surface> Space_Impl::surfaces() const {
      return castVector<Surface>(getObject<openstudio::epmodel::Space>().getSources(Surface::iddObjectType()));
    }

    void Space_Impl::unmatchSurfaces() {
      for (Surface& surface : this->surfaces()) {
        boost::optional<Surface> adjacentSurface = surface.adjacentSurface();
        if (adjacentSurface) {
          surface.resetAdjacentSurface();
          adjacentSurface->resetAdjacentSurface();
        }

        for (SubSurface& subSurface : surface.subSurfaces()) {
          boost::optional<SubSurface> adjacentSubSurface = subSurface.adjacentSubSurface();
          if (adjacentSubSurface) {
            subSurface.resetAdjacentSubSurface();
            adjacentSubSurface->resetAdjacentSubSurface();
          }
        }
      }
    }

    void Space_Impl::matchSurfaces(Space& other) {
      double tol = 0.01;

      if (this->handle() == other.handle()) {
        return;
      }

      // transform from other to this coordinates
      Transformation transformation = this->transformation().inverse() * other.transformation();

      for (Surface& surface : this->surfaces()) {
        if (surface.adjacentSurface()) {
          continue;
        }
        std::vector<Point3d> vertices = surface.vertices();
        boost::optional<Vector3d> outwardNormal = getOutwardNormal(vertices);
        if (!outwardNormal) {
          continue;
        }

        for (Surface& otherSurface : other.surfaces()) {
          if (otherSurface.adjacentSurface()) {
            continue;
          }
          std::vector<Point3d> otherVertices = transformation * otherSurface.vertices();
          boost::optional<Vector3d> otherOutwardNormal = getOutwardNormal(otherVertices);
          if (!otherOutwardNormal) {
            continue;
          }

          double dot = outwardNormal->dot(*otherOutwardNormal);

          if (dot > -0.98) {
            continue;
          }

          std::reverse(otherVertices.begin(), otherVertices.end());

          if (circularEqual(vertices, otherVertices, tol)) {

            // TODO: check constructions?
            surface.setAdjacentSurface(otherSurface);
            otherSurface.setAdjacentSurface(surface);

            // once surfaces are matched, check subsurfaces
            for (SubSurface& subSurface : surface.subSurfaces()) {

              vertices = removeCollinear(subSurface.vertices());

              for (SubSurface& otherSubSurface : otherSurface.subSurfaces()) {

                otherVertices = removeCollinear(transformation * otherSubSurface.vertices());
                std::reverse(otherVertices.begin(), otherVertices.end());

                if (circularEqual(vertices, otherVertices, tol)) {

                  // TODO: check constructions?
                  subSurface.setAdjacentSubSurface(otherSubSurface);
                  otherSubSurface.setAdjacentSubSurface(subSurface);
                }
              }
            }
          }
        }
      }
    }

    void Space_Impl::intersectSurfaces(Space& other) {
      if (this->handle() == other.handle()) {
        return;
      }

      std::string name = nameString();
      std::string otherName = other.nameString();
      LOG(Debug, "Intersecting space " << name << " with space " << otherName);

      std::vector<Surface> surfaces = this->surfaces();
      std::vector<Surface> otherSurfaces = other.surfaces();

      std::sort(surfaces.begin(), surfaces.end(), [](const Surface& a, const Surface& b) -> bool { return a.grossArea() > b.grossArea(); });
      std::sort(otherSurfaces.begin(), otherSurfaces.end(), [](const Surface& a, const Surface& b) -> bool { return a.grossArea() > b.grossArea(); });

      std::map<std::string, bool> hasSubSurfaceMap;
      std::map<std::string, bool> hasAdjacentSurfaceMap;
      std::set<std::string> completedIntersections;

      bool anyNewSurfaces = true;
      while (anyNewSurfaces) {

        anyNewSurfaces = false;
        std::vector<Surface> newSurfaces;
        std::vector<Surface> newOtherSurfaces;

        for (Surface& surface : surfaces) {
          std::string surfaceHandle = toString(surface.handle());

          if (hasSubSurfaceMap.find(surfaceHandle) == hasSubSurfaceMap.end()) {
            hasSubSurfaceMap[surfaceHandle] = !surface.subSurfaces().empty();
            hasAdjacentSurfaceMap[surfaceHandle] = surface.adjacentSurface().has_value();
          }

          if (hasSubSurfaceMap[surfaceHandle] || hasAdjacentSurfaceMap[surfaceHandle]) {
            continue;
          }

          for (Surface& otherSurface : otherSurfaces) {
            std::string otherSurfaceHandle = toString(otherSurface.handle());

            if (hasSubSurfaceMap.find(otherSurfaceHandle) == hasSubSurfaceMap.end()) {
              hasSubSurfaceMap[otherSurfaceHandle] = !otherSurface.subSurfaces().empty();
              hasAdjacentSurfaceMap[otherSurfaceHandle] = otherSurface.adjacentSurface().has_value();
            }

            if (hasSubSurfaceMap[otherSurfaceHandle] || hasAdjacentSurfaceMap[otherSurfaceHandle]) {
              continue;
            }

            // see if we have already tested these for intersection,
            // surfaces that previously did not intersect will not intersect if vertices change
            // surfaces that previously did intersect will intersect exactly
            std::string intersectionKey = surfaceHandle + otherSurfaceHandle;
            if (completedIntersections.find(intersectionKey) != completedIntersections.end()) {
              continue;
            }
            completedIntersections.insert(intersectionKey);

            // number of surfaces in each space will only increase in intersect
            boost::optional<SurfaceIntersection> intersection = surface.computeIntersection(otherSurface);
            if (intersection) {
              std::vector<Surface> newSurfaces1 = intersection->newSurfaces1();
              std::vector<Surface> newSurfaces2 = intersection->newSurfaces2();

              // surfaces involved in this intersection are ineligible to be re-intersected with other surfaces in this intersection
              std::vector<Surface> ineligibleSurfaces;
              ineligibleSurfaces.reserve(newSurfaces1.size() + 1);
              ineligibleSurfaces.push_back(surface);
              ineligibleSurfaces.insert(ineligibleSurfaces.end(), newSurfaces1.begin(), newSurfaces1.end());

              std::vector<Surface> ineligibleOtherSurfaces;
              ineligibleOtherSurfaces.reserve(newSurfaces2.size() + 1);
              ineligibleOtherSurfaces.push_back(otherSurface);
              ineligibleOtherSurfaces.insert(ineligibleOtherSurfaces.end(), newSurfaces2.begin(), newSurfaces2.end());
              for (Surface& ineligibleSurface : ineligibleSurfaces) {
                for (Surface& ineligibleOtherSurface : ineligibleOtherSurfaces) {
                  std::string ineligibleIntersectionKey = toString(ineligibleSurface.handle()) + toString(ineligibleOtherSurface.handle());
                  completedIntersections.insert(ineligibleIntersectionKey);
                }
              }

              newSurfaces.reserve(newSurfaces.size() + newSurfaces1.size());
              newSurfaces.insert(newSurfaces.end(), std::make_move_iterator(newSurfaces1.begin()), std::make_move_iterator(newSurfaces1.end()));
              newOtherSurfaces.reserve(newOtherSurfaces.size() + newSurfaces2.size());
              newOtherSurfaces.insert(newOtherSurfaces.end(), std::make_move_iterator(newSurfaces2.begin()),
                                      std::make_move_iterator(newSurfaces2.end()));
            }
          }
        }

        if (!newSurfaces.empty()) {
          surfaces.insert(surfaces.end(), newSurfaces.begin(), newSurfaces.end());
          anyNewSurfaces = true;
        }
        if (!newOtherSurfaces.empty()) {
          otherSurfaces.insert(otherSurfaces.end(), newOtherSurfaces.begin(), newOtherSurfaces.end());
          anyNewSurfaces = true;
        }
      }
    }

    // E+ Space has no origin or rotation fields — always identity.
    Transformation Space_Impl::transformation() const {
      return {};
    }

    Transformation Space_Impl::buildingTransformation() const {
      return transformation();
    }

    bool Space_Impl::setTransformation(const Transformation& /*transformation*/) {
      // TODO: there are no origin X,Y,Z nor relative North Axis fields
      return false;
    }

    bool Space_Impl::changeTransformation(const Transformation& transformation) {
      Transformation oldTransformation = this->transformation();
      if (!setTransformation(transformation)) {
        return false;
      }

      // (Tnew^-1 * Told) * xold = xnew — keeps children at their absolute position
      Transformation childTransformation = transformation.inverse() * oldTransformation;

      for (Surface& surface : surfaces()) {
        bool test = surface.setVertices(childTransformation * surface.vertices());
        if (!test) {
          LOG(Error, "Could not transform vertices for Surface '" << surface.nameString() << "'.");
        }
        for (SubSurface& subSurface : surface.subSurfaces()) {
          test = subSurface.setVertices(childTransformation * subSurface.vertices());
          if (!test) {
            LOG(Error, "Could not transform vertices for SubSurface '" << subSurface.nameString() << "'.");
          }
        }
      }

      return true;
    }

    BoundingBox Space_Impl::boundingBox() const {
      BoundingBox result;
      for (const Surface& surface : surfaces()) {
        result.addPoints(surface.vertices());
      }
      return result;
    }

    void Space_Impl::doCanonicalize(LoadContext& context) {
      auto thisSpace = getObject<openstudio::epmodel::Space>();
      auto zone = thermalZone();
      if (zone) {
        zone->getImpl<openstudio::epmodel::detail::ThermalZone_Impl>()->canonicalize(context);
      }

      std::vector<std::pair<openstudio::epmodel::DesignSpecificationOutdoorAirSpaceList, openstudio::epmodel::DesignSpecificationOutdoorAir>>
        assignments;
      for (const auto& list : model().getConcreteModelObjects<openstudio::epmodel::DesignSpecificationOutdoorAirSpaceList>()) {
        if (auto dsoa = list.designSpecificationOutdoorAir(thisSpace)) {
          assignments.emplace_back(list, *dsoa);
        }
      }
      if (assignments.empty()) {
        return;
      }

      std::sort(assignments.begin(), assignments.end(),
                [](const auto& lhs, const auto& rhs) { return lhs.first.nameString() < rhs.first.nameString(); });

      openstudio::epmodel::DesignSpecificationOutdoorAirSpaceList canonicalList =
        zone ? getOrCreateZoneSpaceList(*zone) : getOrCreateOrphanSpaceList(model());
      auto canonicalDSOA = assignments.front().second;
      bool canonicalListHadAssignment = false;
      for (const auto& [list, dsoa] : assignments) {
        if (list.handle() == canonicalList.handle()) {
          canonicalListHadAssignment = true;
          canonicalDSOA = dsoa;
          break;
        }
      }

      OS_ASSERT(canonicalList.getImpl<openstudio::epmodel::detail::DesignSpecificationOutdoorAirSpaceList_Impl>()->setDesignSpecificationOutdoorAir(
        thisSpace, canonicalDSOA));
      removeSpaceFromAllListsExcept(thisSpace, canonicalList.handle());

      if (assignments.size() > 1u) {
        detail::addLoadInfo(context, "Normalized duplicate DSOA assignments for Space '" + thisSpace.nameString()
                                       + "' into DesignSpecification:OutdoorAir:SpaceList '" + canonicalList.nameString() + "'.");
        bool hasConflictingAssignments = false;
        for (const auto& [_, dsoa] : assignments) {
          if (dsoa.handle() != canonicalDSOA.handle()) {
            hasConflictingAssignments = true;
            break;
          }
        }
        if (hasConflictingAssignments) {
          detail::addLoadWarning(context, "Space '" + thisSpace.nameString()
                                            + "' had conflicting DSOA assignments across lists; canonicalization kept assignment from '"
                                            + canonicalList.nameString() + "'.");
        }
      }

      if (!canonicalListHadAssignment) {
        detail::addLoadInfo(context,
                            "Moved Space '" + thisSpace.nameString() + "' DSOA assignment into canonical list '" + canonicalList.nameString() + "'.");
      }

      if (auto orphanList =
            model().getConcreteModelObjectByName<openstudio::epmodel::DesignSpecificationOutdoorAirSpaceList>(orphanDSOASpaceListName)) {
        if (orphanList->numExtensibleGroups() == 0u) {
          orphanList->remove();
          detail::addLoadInfo(context,
                              std::string("Removed empty orphan DesignSpecification:OutdoorAir:SpaceList '") + orphanDSOASpaceListName + "'.");
        }
      }
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
