/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "PlanarSurface/SubSurface.hpp"
#include "PlanarSurface/SubSurface_Impl.hpp"

#include "Model.hpp"
#include "PlanarSurface/Surface.hpp"
#include "PlanarSurface/Surface_Impl.hpp"
#include "PlanarSurfaceGroup/Space.hpp"
#include "ResourceObject/WindowPropertyFrameAndDivider.hpp"
#include "ResourceObject/WindowPropertyFrameAndDivider_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/geometry/BoundingBox.hpp>
#include <utilities/geometry/Geometry.hpp>
#include <utilities/geometry/Intersection.hpp>
#include <utilities/geometry/Transformation.hpp>
#include <utilities/idd/FenestrationSurface_Detailed_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idf/WorkspaceObject.hpp>

namespace openstudio {
namespace epmodel {

  SubSurface::SubSurface(const std::vector<Point3d>& vertices, const Model& model) : PlanarSurface(SubSurface::iddObjectType(), model) {
    getImpl<detail::SubSurface_Impl>()->setVertices(vertices);
  }

  SubSurface::SubSurface(std::shared_ptr<detail::SubSurface_Impl> impl) : PlanarSurface(std::move(impl)) {}

  IddObjectType SubSurface::iddObjectType() {
    return IddObjectType::FenestrationSurface_Detailed;
  }

  std::vector<std::string> SubSurface::validSubSurfaceTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::FenestrationSurface_DetailedFields::SurfaceType);
  }

  std::string SubSurface::subSurfaceType() const {
    return getImpl<detail::SubSurface_Impl>()->subSurfaceType();
  }

  bool SubSurface::isSubSurfaceTypeDefaulted() const {
    return getImpl<detail::SubSurface_Impl>()->isSubSurfaceTypeDefaulted();
  }

  bool SubSurface::setSubSurfaceType(const std::string& subSurfaceType) {
    return getImpl<detail::SubSurface_Impl>()->setSubSurfaceType(subSurfaceType);
  }

  void SubSurface::resetSubSurfaceType() {
    getImpl<detail::SubSurface_Impl>()->resetSubSurfaceType();
  }

  boost::optional<double> SubSurface::viewFactortoGround() const {
    return getImpl<detail::SubSurface_Impl>()->viewFactortoGround();
  }

  bool SubSurface::isViewFactortoGroundDefaulted() const {
    return getImpl<detail::SubSurface_Impl>()->isViewFactortoGroundDefaulted();
  }

  bool SubSurface::isViewFactortoGroundAutocalculated() const {
    return getImpl<detail::SubSurface_Impl>()->isViewFactortoGroundAutocalculated();
  }

  bool SubSurface::setViewFactortoGround(double viewFactortoGround) {
    return getImpl<detail::SubSurface_Impl>()->setViewFactortoGround(viewFactortoGround);
  }

  void SubSurface::resetViewFactortoGround() {
    getImpl<detail::SubSurface_Impl>()->resetViewFactortoGround();
  }

  void SubSurface::autocalculateViewFactortoGround() {
    getImpl<detail::SubSurface_Impl>()->autocalculateViewFactortoGround();
  }

  double SubSurface::multiplier() const {
    return getImpl<detail::SubSurface_Impl>()->multiplier();
  }

  bool SubSurface::isMultiplierDefaulted() const {
    return getImpl<detail::SubSurface_Impl>()->isMultiplierDefaulted();
  }

  bool SubSurface::setMultiplier(double multiplier) {
    return getImpl<detail::SubSurface_Impl>()->setMultiplier(multiplier);
  }

  void SubSurface::resetMultiplier() {
    getImpl<detail::SubSurface_Impl>()->resetMultiplier();
  }

  unsigned int SubSurface::numberofVertices() const {
    return getImpl<detail::SubSurface_Impl>()->numberofVertices();
  }

  bool SubSurface::isNumberofVerticesDefaulted() const {
    return getImpl<detail::SubSurface_Impl>()->isNumberofVerticesDefaulted();
  }

  bool SubSurface::isNumberofVerticesAutocalculated() const {
    return getImpl<detail::SubSurface_Impl>()->isNumberofVerticesAutocalculated();
  }

  bool SubSurface::setNumberofVertices(unsigned int numberofVertices) {
    return getImpl<detail::SubSurface_Impl>()->setNumberofVertices(numberofVertices);
  }

  void SubSurface::resetNumberofVertices() {
    getImpl<detail::SubSurface_Impl>()->resetNumberofVertices();
  }

  void SubSurface::autocalculateNumberofVertices() {
    getImpl<detail::SubSurface_Impl>()->autocalculateNumberofVertices();
  }

  bool SubSurface::allowWindowPropertyFrameAndDivider() const {
    return getImpl<detail::SubSurface_Impl>()->allowWindowPropertyFrameAndDivider();
  }

  boost::optional<WindowPropertyFrameAndDivider> SubSurface::windowPropertyFrameAndDivider() const {
    return getImpl<detail::SubSurface_Impl>()->windowPropertyFrameAndDivider();
  }

  bool SubSurface::setWindowPropertyFrameAndDivider(const WindowPropertyFrameAndDivider& windowPropertyFrameAndDivider) {
    return getImpl<detail::SubSurface_Impl>()->setWindowPropertyFrameAndDivider(windowPropertyFrameAndDivider);
  }

  void SubSurface::resetWindowPropertyFrameAndDivider() {
    getImpl<detail::SubSurface_Impl>()->resetWindowPropertyFrameAndDivider();
  }

  boost::optional<Surface> SubSurface::surface() const {
    return getImpl<detail::SubSurface_Impl>()->surface();
  }

  bool SubSurface::setSurface(const Surface& surface) {
    return getImpl<detail::SubSurface_Impl>()->setSurface(surface);
  }

  boost::optional<SubSurface> SubSurface::adjacentSubSurface() const {
    return getImpl<detail::SubSurface_Impl>()->adjacentSubSurface();
  }

  bool SubSurface::setAdjacentSubSurface(SubSurface& subSurface) {
    return getImpl<detail::SubSurface_Impl>()->setAdjacentSubSurface(subSurface);
  }

  void SubSurface::resetAdjacentSubSurface() {
    getImpl<detail::SubSurface_Impl>()->resetAdjacentSubSurface();
  }

  /** Assign default sub surface type based on vertices. */
  void SubSurface::assignDefaultSubSurfaceType() {
    getImpl<detail::SubSurface_Impl>()->assignDefaultSubSurfaceType();
  }

  std::string SubSurface::outsideBoundaryCondition() const {
    return getImpl<detail::SubSurface_Impl>()->outsideBoundaryCondition();
  }

  double SubSurface::roughOpeningArea() const {
    return getImpl<detail::SubSurface_Impl>()->roughOpeningArea();
  }

  std::vector<Point3d> SubSurface::roughOpeningVertices() const {
    return getImpl<detail::SubSurface_Impl>()->roughOpeningVertices();
  }

  double SubSurface::frameArea() const {
    return getImpl<detail::SubSurface_Impl>()->frameArea();
  }

  double SubSurface::dividerArea() const {
    return getImpl<detail::SubSurface_Impl>()->dividerArea();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::string remap_subSurfaceType(const std::string& subSurfaceType) {

      // openstudio
      // \key FixedWindow
      // \key OperableWindow
      // \key Door
      // \key GlassDoor
      // \key OverheadDoor
      // \key Skylight
      // \key TubularDaylightDome
      // \key TubularDaylightDiffuser

      // energyplus
      // \key Window
      // \key Door
      // \key GlassDoor
      // \key TubularDaylightDome
      // \key TubularDaylightDiffuser

      constexpr std::array<std::pair<const char*, const char*>, 8> os_to_ep{{
        {"FixedWindow", "Window"},
        {"OperableWindow", "Window"},
        {"Door", "Door"},
        {"GlassDoor", "GlassDoor"},
        {"OverheadDoor", "Door"},
        {"Skylight", "Window"},
        {"TubularDaylightDome", "TubularDaylightDome"},
        {"TubularDaylightDiffuser", "TubularDaylightDiffuser"},
      }};
      return {std::find_if(os_to_ep.cbegin(), os_to_ep.cend(), [&subSurfaceType](auto pair) {
                return openstudio::istringEqual(subSurfaceType, pair.first);
              })->second};
    }

    std::string SubSurface_Impl::subSurfaceType() const {
      auto value = getString(openstudio::FenestrationSurface_DetailedFields::SurfaceType, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool SubSurface_Impl::isSubSurfaceTypeDefaulted() const {
      return isEmpty(openstudio::FenestrationSurface_DetailedFields::SurfaceType);
    }

    bool SubSurface_Impl::setSubSurfaceType(const std::string& subSurfaceType) {
      return setString(openstudio::FenestrationSurface_DetailedFields::SurfaceType, subSurfaceType, true);
    }

    void SubSurface_Impl::resetSubSurfaceType() {
      OS_ASSERT(setString(openstudio::FenestrationSurface_DetailedFields::SurfaceType, ""));
    }

    boost::optional<double> SubSurface_Impl::viewFactortoGround() const {
      return getDouble(openstudio::FenestrationSurface_DetailedFields::ViewFactortoGround, true);
    }

    bool SubSurface_Impl::isViewFactortoGroundDefaulted() const {
      return isEmpty(openstudio::FenestrationSurface_DetailedFields::ViewFactortoGround);
    }

    bool SubSurface_Impl::isViewFactortoGroundAutocalculated() const {
      if (auto value = getString(openstudio::FenestrationSurface_DetailedFields::ViewFactortoGround, true)) {
        return openstudio::istringEqual(value.get(), "Autocalculate");
      }
      return false;
    }

    bool SubSurface_Impl::setViewFactortoGround(double viewFactortoGround) {
      return setDouble(openstudio::FenestrationSurface_DetailedFields::ViewFactortoGround, viewFactortoGround);
    }

    void SubSurface_Impl::resetViewFactortoGround() {
      OS_ASSERT(setString(openstudio::FenestrationSurface_DetailedFields::ViewFactortoGround, ""));
    }

    void SubSurface_Impl::autocalculateViewFactortoGround() {
      OS_ASSERT(setString(openstudio::FenestrationSurface_DetailedFields::ViewFactortoGround, "Autocalculate"));
    }

    double SubSurface_Impl::multiplier() const {
      auto value = getDouble(openstudio::FenestrationSurface_DetailedFields::Multiplier, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SubSurface_Impl::isMultiplierDefaulted() const {
      return isEmpty(openstudio::FenestrationSurface_DetailedFields::Multiplier);
    }

    bool SubSurface_Impl::setMultiplier(double multiplier) {
      return setDouble(openstudio::FenestrationSurface_DetailedFields::Multiplier, multiplier);
    }

    void SubSurface_Impl::resetMultiplier() {
      OS_ASSERT(setString(openstudio::FenestrationSurface_DetailedFields::Multiplier, ""));
    }

    unsigned int SubSurface_Impl::numberofVertices() const {
      if (auto value = getInt(openstudio::FenestrationSurface_DetailedFields::NumberofVertices, true)) {
        return static_cast<unsigned int>(*value);
      }
      return static_cast<unsigned int>(vertices().size());
    }

    bool SubSurface_Impl::isNumberofVerticesDefaulted() const {
      return isEmpty(openstudio::FenestrationSurface_DetailedFields::NumberofVertices);
    }

    bool SubSurface_Impl::isNumberofVerticesAutocalculated() const {
      if (auto value = getString(openstudio::FenestrationSurface_DetailedFields::NumberofVertices, true)) {
        return openstudio::istringEqual(value.get(), "Autocalculate");
      }
      return false;
    }

    bool SubSurface_Impl::setNumberofVertices(unsigned int numberofVertices) {
      return setInt(openstudio::FenestrationSurface_DetailedFields::NumberofVertices, numberofVertices);
    }

    void SubSurface_Impl::resetNumberofVertices() {
      OS_ASSERT(setString(openstudio::FenestrationSurface_DetailedFields::NumberofVertices, ""));
    }

    void SubSurface_Impl::autocalculateNumberofVertices() {
      OS_ASSERT(setString(openstudio::FenestrationSurface_DetailedFields::NumberofVertices, "Autocalculate"));
    }

    bool SubSurface_Impl::setVertices(const std::vector<Point3d>& vertices) {
      bool result = PlanarSurface_Impl::setVertices(vertices);

      if (isEmpty(openstudio::FenestrationSurface_DetailedFields::SurfaceType)) {
        if (result) {
          this->assignDefaultSubSurfaceType();
        } else {
          LOG(Error, "Cannot compute default SubSurface properties.");
        }
      }

      return result;
    }

    boost::optional<Space> SubSurface_Impl::space() const {
      if (boost::optional<Surface> surface = this->surface()) {
        return surface->space();
      }
      return boost::none;
    }

    bool SubSurface_Impl::subtractFromGrossArea() const {
      return true;
    }

    boost::optional<Surface> SubSurface_Impl::surface() const {
      return getObject<SubSurface>().getModelObjectTarget<Surface>(openstudio::FenestrationSurface_DetailedFields::BuildingSurfaceName);
    }

    bool SubSurface_Impl::setSurface(const Surface& surface) {
      bool emptySurface = isEmpty(openstudio::FenestrationSurface_DetailedFields::BuildingSurfaceName);
      bool result = setPointer(openstudio::FenestrationSurface_DetailedFields::BuildingSurfaceName, surface.handle());
      if (result && emptySurface && isSubSurfaceTypeDefaulted()) {
        assignDefaultSubSurfaceType();
      }
      return result;
    }

    std::string SubSurface_Impl::defaultSubSurfaceType() const {
      std::string result;

      boost::optional<Surface> surface = this->surface();
      if (!surface) {
        double degTilt = radToDeg(this->tilt());
        if (degTilt < 60) {
          result = "Skylight";
        } else if (degTilt < 179) {
          result = "FixedWindow";
        } else {
          result = "Skylight";
        }
      } else {
        std::string surfaceType = surface->surfaceType();
        if (istringEqual("Roof", surfaceType) || istringEqual("Ceiling", surfaceType)  // RoofCeiling
            || istringEqual("Floor", surfaceType)) {
          result = "Skylight";
        } else {
          double surfaceMinZ = std::numeric_limits<double>::max();
          for (const Point3d& point : surface->vertices()) {
            surfaceMinZ = std::min(surfaceMinZ, point.z());
          }

          double thisMinZ = std::numeric_limits<double>::max();
          for (const Point3d& point : this->vertices()) {
            thisMinZ = std::min(thisMinZ, point.z());
          }

          if (thisMinZ <= surfaceMinZ) {
            bool isGlassDoor = false;

            // DLM: this surface could have been initialized to FixedWindow and get its construction
            // from the default construction set, this was the source of #1924
            // TODO: missing ConstructionBase
            // boost::optional<ConstructionBase> construction = this->construction();
            // if (!this->isConstructionDefaulted() && construction && construction->isFenestration()) {
            //   isGlassDoor = true;
            // }

            boost::optional<std::string> value = getString(openstudio::FenestrationSurface_DetailedFields::SurfaceType);
            if (value && istringEqual("GlassDoor", *value)) {
              isGlassDoor = true;
            }

            if (isGlassDoor) {
              result = "GlassDoor";
            } else {
              result = "Door";
            }
          } else {
            result = "FixedWindow";
          }
        }
      }

      return remap_subSurfaceType(result);
    }

    void SubSurface_Impl::assignDefaultSubSurfaceType() {
      std::string defaultSubSurfaceType = this->defaultSubSurfaceType();
      bool test = setSubSurfaceType(defaultSubSurfaceType);
      OS_ASSERT(test);
    }

    bool SubSurface_Impl::allowWindowPropertyFrameAndDivider() const {
      std::string type = subSurfaceType();
      // return istringEqual("FixedWindow", type) || istringEqual("OperableWindow", type) || istringEqual("Skylight", type)
      //        || istringEqual("GlassDoor", type);
      return istringEqual("Window", type) || istringEqual("GlassDoor", type);
    }

    boost::optional<WindowPropertyFrameAndDivider> SubSurface_Impl::windowPropertyFrameAndDivider() const {
      return getObject<SubSurface>().getModelObjectTarget<WindowPropertyFrameAndDivider>(
        openstudio::FenestrationSurface_DetailedFields::FrameandDividerName);
    }

    bool SubSurface_Impl::setWindowPropertyFrameAndDivider(const WindowPropertyFrameAndDivider& windowPropertyFrameAndDivider) {
      if (!allowWindowPropertyFrameAndDivider()) {
        return false;
      }
      return setPointer(openstudio::FenestrationSurface_DetailedFields::FrameandDividerName, windowPropertyFrameAndDivider.handle());
    }

    void SubSurface_Impl::resetWindowPropertyFrameAndDivider() {
      OS_ASSERT(setString(openstudio::FenestrationSurface_DetailedFields::FrameandDividerName, ""));
    }

    boost::optional<SubSurface> SubSurface_Impl::adjacentSubSurface() const {
      return getObject<SubSurface>().getModelObjectTarget<SubSurface>(openstudio::FenestrationSurface_DetailedFields::OutsideBoundaryConditionObject);
    }

    bool SubSurface_Impl::setAdjacentSubSurface(SubSurface& subSurface) {
      bool isSameSubSurface = (subSurface.handle() == getObject<SubSurface>().handle());

      if (multiplier() != subSurface.multiplier()) {
        return false;
      }

      boost::optional<Surface> thisSurface = surface();
      boost::optional<Surface> otherSurface = subSurface.surface();
      if (!thisSurface || !otherSurface) {
        return false;
      }

      boost::optional<Surface> adjacentSurface = thisSurface->adjacentSurface();
      if (!adjacentSurface || adjacentSurface->handle() != otherSurface->handle()) {
        return false;
      }

      std::string thisType = subSurfaceType();
      std::string otherType = subSurface.subSurfaceType();
      if (thisType != otherType) {
        if (thisType != defaultSubSurfaceType()) {
          subSurface.setSubSurfaceType(thisType);
        } else {
          setSubSurfaceType(otherType);
        }
      }

      resetAdjacentSubSurface();
      if (!isSameSubSurface) {
        subSurface.resetAdjacentSubSurface();
      }

      bool result = setPointer(openstudio::FenestrationSurface_DetailedFields::OutsideBoundaryConditionObject, subSurface.handle());
      OS_ASSERT(result);
      if (!isSameSubSurface) {
        result = subSurface.getImpl<SubSurface_Impl>()->setPointer(openstudio::FenestrationSurface_DetailedFields::OutsideBoundaryConditionObject,
                                                                   getObject<SubSurface>().handle());
        OS_ASSERT(result);
      }
      return true;
    }

    void SubSurface_Impl::resetAdjacentSubSurface() {
      OS_ASSERT(setString(openstudio::FenestrationSurface_DetailedFields::OutsideBoundaryConditionObject, ""));
      for (WorkspaceObject& wo : getSources(IddObjectType::FenestrationSurface_Detailed)) {
        OS_ASSERT(wo.setString(openstudio::FenestrationSurface_DetailedFields::OutsideBoundaryConditionObject, ""));
      }
    }

    std::string SubSurface_Impl::outsideBoundaryCondition() const {
      if (auto oSurface = surface()) {
        return oSurface->outsideBoundaryCondition();
      }
      return {};
    }

    std::vector<Point3d> SubSurface_Impl::roughOpeningVertices() const {
      if (auto frameAndDivider = windowPropertyFrameAndDivider()) {
        double fw = frameAndDivider->frameWidth();
        Transformation faceTransform = Transformation::alignFace(vertices());
        std::vector<Point3d> faceVertices = faceTransform.inverse() * vertices();
        auto offset = openstudio::buffer(faceVertices, fw, 0.01);
        if (!offset) {
          faceVertices = openstudio::reverse(faceVertices);
          offset = openstudio::buffer(faceVertices, fw, 0.01);
          if (!offset) {
            return vertices();
          }
        }
        return faceTransform * offset.get();
      }
      return vertices();
    }

    double SubSurface_Impl::roughOpeningArea() const {
      if (auto area = openstudio::getArea(roughOpeningVertices())) {
        return *area;
      }
      return grossArea();
    }

    double SubSurface_Impl::frameArea() const {
      return roughOpeningArea() - grossArea();
    }

    double SubSurface_Impl::dividerArea() const {
      double divArea = 0;
      if (auto frameAndDivider = windowPropertyFrameAndDivider()) {
        double dividerWidth = frameAndDivider->dividerWidth();
        if (dividerWidth == 0) {
          return divArea;
        }
        Transformation faceTransform = Transformation::alignFace(vertices());
        std::vector<Point3d> faceVertices = faceTransform.inverse() * vertices();
        BoundingBox bb;
        bb.addPoints(faceVertices);
        double numHorizDividers = frameAndDivider->numberOfHorizontalDividers();
        if (numHorizDividers != 0 && bb.maxX().has_value() && bb.minX().has_value()) {
          divArea += numHorizDividers * dividerWidth * (*bb.maxX() - *bb.minX());
        }
        double numVertDividers = frameAndDivider->numberOfVerticalDividers();
        if (numVertDividers != 0 && bb.maxY().has_value() && bb.minY().has_value()) {
          divArea += numVertDividers * dividerWidth * (*bb.maxY() - *bb.minY());
        }
      }
      return divArea;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
