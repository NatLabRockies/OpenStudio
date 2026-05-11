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

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/geometry/Geometry.hpp>
#include <utilities/idd/FenestrationSurface_Detailed_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

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

  bool SubSurface::setViewFactortoGround(boost::optional<double> viewFactortoGround) {
    return getImpl<detail::SubSurface_Impl>()->setViewFactortoGround(viewFactortoGround);
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

  boost::optional<double> SubSurface::numberofVertices() const {
    return getImpl<detail::SubSurface_Impl>()->numberofVertices();
  }

  bool SubSurface::isNumberofVerticesDefaulted() const {
    return getImpl<detail::SubSurface_Impl>()->isNumberofVerticesDefaulted();
  }

  bool SubSurface::isNumberofVerticesAutocalculated() const {
    return getImpl<detail::SubSurface_Impl>()->isNumberofVerticesAutocalculated();
  }

  bool SubSurface::setNumberofVertices(boost::optional<double> numberofVertices) {
    return getImpl<detail::SubSurface_Impl>()->setNumberofVertices(numberofVertices);
  }

  bool SubSurface::setNumberofVertices(double numberofVertices) {
    return getImpl<detail::SubSurface_Impl>()->setNumberofVertices(numberofVertices);
  }

  void SubSurface::resetNumberofVertices() {
    getImpl<detail::SubSurface_Impl>()->resetNumberofVertices();
  }

  void SubSurface::autocalculateNumberofVertices() {
    getImpl<detail::SubSurface_Impl>()->autocalculateNumberofVertices();
  }

  boost::optional<Surface> SubSurface::surface() const {
    return getImpl<detail::SubSurface_Impl>()->surface();
  }

  bool SubSurface::setSurface(const Surface& surface) {
    return getImpl<detail::SubSurface_Impl>()->setSurface(surface);
  }

  /** Assign default sub surface type based on vertices. */
  void SubSurface::assignDefaultSubSurfaceType() {
    getImpl<detail::SubSurface_Impl>()->assignDefaultSubSurfaceType();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

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

    bool SubSurface_Impl::setViewFactortoGround(boost::optional<double> viewFactortoGround) {
      bool result = false;
      if (viewFactortoGround) {
        result = setDouble(openstudio::FenestrationSurface_DetailedFields::ViewFactortoGround, viewFactortoGround.get());
      } else {
        result = setString(openstudio::FenestrationSurface_DetailedFields::ViewFactortoGround, "");
      }
      return result;
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

    boost::optional<double> SubSurface_Impl::numberofVertices() const {
      return getDouble(openstudio::FenestrationSurface_DetailedFields::NumberofVertices, true);
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

    bool SubSurface_Impl::setNumberofVertices(boost::optional<double> numberofVertices) {
      bool result = false;
      if (numberofVertices) {
        result = setDouble(openstudio::FenestrationSurface_DetailedFields::NumberofVertices, numberofVertices.get());
      } else {
        result = setString(openstudio::FenestrationSurface_DetailedFields::NumberofVertices, "");
      }
      return result;
    }

    bool SubSurface_Impl::setNumberofVertices(double numberofVertices) {
      return setDouble(openstudio::FenestrationSurface_DetailedFields::NumberofVertices, numberofVertices);
    }

    void SubSurface_Impl::resetNumberofVertices() {
      OS_ASSERT(setString(openstudio::FenestrationSurface_DetailedFields::NumberofVertices, ""));
    }

    void SubSurface_Impl::autocalculateNumberofVertices() {
      OS_ASSERT(setString(openstudio::FenestrationSurface_DetailedFields::NumberofVertices, "Autocalculate"));
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
        if (istringEqual("RoofCeiling", surfaceType) || istringEqual("Floor", surfaceType)) {
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

      return result;
    }

    void SubSurface_Impl::assignDefaultSubSurfaceType() {
      std::string defaultSubSurfaceType = this->defaultSubSurfaceType();
      bool test = setSubSurfaceType(defaultSubSurfaceType);
      OS_ASSERT(test);
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
