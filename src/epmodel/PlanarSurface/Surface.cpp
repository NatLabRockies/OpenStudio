/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "PlanarSurface/Surface.hpp"
#include "PlanarSurface/Surface_Impl.hpp"

#include "Model.hpp"
#include "PlanarSurfaceGroup/Space.hpp"
#include "PlanarSurfaceGroup/Space_Impl.hpp"
#include "PlanarSurface/SubSurface.hpp"
#include "PlanarSurface/SubSurface_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/geometry/Geometry.hpp>
#include <utilities/geometry/Intersection.hpp>
#include <utilities/geometry/Point3d.hpp>
#include <utilities/geometry/Transformation.hpp>
#include <utilities/idd/BuildingSurface_Detailed_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idf/IdfExtensibleGroup.hpp>
#include <utility>
#include <utility>

namespace openstudio {
namespace epmodel {

  Surface::Surface(const std::vector<Point3d>& vertices, const Model& model) : PlanarSurface(Surface::iddObjectType(), model) {
    getImpl<detail::Surface_Impl>()->setVertices(vertices);
  }

  Surface::Surface(std::shared_ptr<detail::Surface_Impl> impl) : PlanarSurface(std::move(impl)) {}

  IddObjectType Surface::iddObjectType() {
    return IddObjectType::BuildingSurface_Detailed;
  }

  std::vector<std::string> Surface::validSurfaceTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::BuildingSurface_DetailedFields::SurfaceType);
  }

  std::vector<std::string> Surface::validOutsideBoundaryConditionValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::BuildingSurface_DetailedFields::OutsideBoundaryCondition);
  }

  std::vector<std::string> Surface::validSunExposureValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::BuildingSurface_DetailedFields::SunExposure);
  }

  std::vector<std::string> Surface::validWindExposureValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::BuildingSurface_DetailedFields::WindExposure);
  }

  std::string Surface::surfaceType() const {
    return getImpl<detail::Surface_Impl>()->surfaceType();
  }

  bool Surface::setSurfaceType(const std::string& surfaceType) {
    return getImpl<detail::Surface_Impl>()->setSurfaceType(surfaceType);
  }

  std::string Surface::outsideBoundaryCondition() const {
    return getImpl<detail::Surface_Impl>()->outsideBoundaryCondition();
  }

  bool Surface::setOutsideBoundaryCondition(const std::string& outsideBoundaryCondition) {
    return getImpl<detail::Surface_Impl>()->setOutsideBoundaryCondition(outsideBoundaryCondition);
  }

  std::string Surface::sunExposure() const {
    return getImpl<detail::Surface_Impl>()->sunExposure();
  }

  bool Surface::isSunExposureDefaulted() const {
    return getImpl<detail::Surface_Impl>()->isSunExposureDefaulted();
  }

  bool Surface::setSunExposure(const std::string& sunExposure) {
    return getImpl<detail::Surface_Impl>()->setSunExposure(sunExposure);
  }

  void Surface::resetSunExposure() {
    getImpl<detail::Surface_Impl>()->resetSunExposure();
  }

  std::string Surface::windExposure() const {
    return getImpl<detail::Surface_Impl>()->windExposure();
  }

  bool Surface::isWindExposureDefaulted() const {
    return getImpl<detail::Surface_Impl>()->isWindExposureDefaulted();
  }

  bool Surface::setWindExposure(const std::string& windExposure) {
    return getImpl<detail::Surface_Impl>()->setWindExposure(windExposure);
  }

  void Surface::resetWindExposure() {
    getImpl<detail::Surface_Impl>()->resetWindExposure();
  }

  boost::optional<double> Surface::viewFactortoGround() const {
    return getImpl<detail::Surface_Impl>()->viewFactortoGround();
  }

  bool Surface::isViewFactortoGroundDefaulted() const {
    return getImpl<detail::Surface_Impl>()->isViewFactortoGroundDefaulted();
  }

  bool Surface::isViewFactortoGroundAutocalculated() const {
    return getImpl<detail::Surface_Impl>()->isViewFactortoGroundAutocalculated();
  }

  bool Surface::setViewFactortoGround(double viewFactortoGround) {
    return getImpl<detail::Surface_Impl>()->setViewFactortoGround(viewFactortoGround);
  }

  void Surface::resetViewFactortoGround() {
    getImpl<detail::Surface_Impl>()->resetViewFactortoGround();
  }

  void Surface::autocalculateViewFactortoGround() {
    getImpl<detail::Surface_Impl>()->autocalculateViewFactortoGround();
  }

  unsigned int Surface::numberofVertices() const {
    return getImpl<detail::Surface_Impl>()->numberofVertices();
  }

  bool Surface::isNumberofVerticesDefaulted() const {
    return getImpl<detail::Surface_Impl>()->isNumberofVerticesDefaulted();
  }

  bool Surface::isNumberofVerticesAutocalculated() const {
    return getImpl<detail::Surface_Impl>()->isNumberofVerticesAutocalculated();
  }

  bool Surface::setNumberofVertices(unsigned int numberofVertices) {
    return getImpl<detail::Surface_Impl>()->setNumberofVertices(numberofVertices);
  }

  void Surface::resetNumberofVertices() {
    getImpl<detail::Surface_Impl>()->resetNumberofVertices();
  }

  void Surface::autocalculateNumberofVertices() {
    getImpl<detail::Surface_Impl>()->autocalculateNumberofVertices();
  }

  bool Surface::setSpace(const Space& space) {
    return getImpl<detail::Surface_Impl>()->setSpace(space);
  }

  std::vector<SubSurface> Surface::subSurfaces() const {
    return getImpl<detail::Surface_Impl>()->subSurfaces();
  }

  boost::optional<Surface> Surface::adjacentSurface() const {
    return getImpl<detail::Surface_Impl>()->adjacentSurface();
  }

  bool Surface::setAdjacentSurface(Surface& surface) {
    return getImpl<detail::Surface_Impl>()->setAdjacentSurface(surface);
  }

  void Surface::resetAdjacentSurface() {
    getImpl<detail::Surface_Impl>()->resetAdjacentSurface();
  }

  bool Surface::intersect(Surface& otherSurface) {
    return getImpl<detail::Surface_Impl>()->intersect(otherSurface);
  }

  boost::optional<SurfaceIntersection> Surface::computeIntersection(Surface& otherSurface) {
    return getImpl<detail::Surface_Impl>()->computeIntersection(otherSurface);
  }

  boost::optional<Surface> Surface::createAdjacentSurface(const Space& otherSpace) {
    return getImpl<detail::Surface_Impl>()->createAdjacentSurface(otherSpace);
  }

  bool Surface::isGroundSurface() const {
    return getImpl<detail::Surface_Impl>()->isGroundSurface();
  }

  bool Surface::isPartOfEnvelope() const {
    return getImpl<detail::Surface_Impl>()->isPartOfEnvelope();
  }

  void Surface::assignDefaultSurfaceType() {
    getImpl<detail::Surface_Impl>()->assignDefaultSurfaceType();
  }

  void Surface::assignDefaultBoundaryCondition() {
    getImpl<detail::Surface_Impl>()->assignDefaultBoundaryCondition();
  }

  void Surface::assignDefaultSunExposure() {
    getImpl<detail::Surface_Impl>()->assignDefaultSunExposure();
  }

  void Surface::assignDefaultWindExposure() {
    getImpl<detail::Surface_Impl>()->assignDefaultWindExposure();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::string Surface_Impl::surfaceType() const {
      auto value = getString(openstudio::BuildingSurface_DetailedFields::SurfaceType, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool Surface_Impl::setSurfaceType(const std::string& surfaceType) {
      return setString(openstudio::BuildingSurface_DetailedFields::SurfaceType, surfaceType, true);
    }

    std::string Surface_Impl::outsideBoundaryCondition() const {
      auto value = getString(openstudio::BuildingSurface_DetailedFields::OutsideBoundaryCondition, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool Surface_Impl::setOutsideBoundaryCondition(const std::string& outsideBoundaryCondition) {
      bool result = false;

      boost::optional<Surface> adjacentSurface = this->adjacentSurface();
      // boost::optional<SurfacePropertyOtherSideCoefficients> surfacePropertyOtherSideCoefficients = this->surfacePropertyOtherSideCoefficients();
      // boost::optional<SurfacePropertyOtherSideConditionsModel> surfacePropertyOtherSideConditionsModel =
      //   this->surfacePropertyOtherSideConditionsModel();

      if (istringEqual("Surface", outsideBoundaryCondition)) {
        if (adjacentSurface) {
          result = setString(openstudio::BuildingSurface_DetailedFields::OutsideBoundaryCondition, outsideBoundaryCondition, true);
        }
      } else if (istringEqual("OtherSideCoefficients", outsideBoundaryCondition)) {
        // if (surfacePropertyOtherSideCoefficients) {
        //   result = setString(openstudio::BuildingSurface_DetailedFields::OutsideBoundaryCondition, outsideBoundaryCondition, true);
        // }
      } else if (istringEqual("OtherSideConditionsModel", outsideBoundaryCondition)) {
        // if (surfacePropertyOtherSideConditionsModel) {
        //   result = setString(openstudio::BuildingSurface_DetailedFields::OutsideBoundaryCondition, outsideBoundaryCondition, true);
        // }
      } else {
        this->resetAdjacentSurface();
        // this->resetSurfacePropertyOtherSideCoefficients();
        // this->resetSurfacePropertyOtherSideConditionsModel();
        result = setString(openstudio::BuildingSurface_DetailedFields::OutsideBoundaryCondition, outsideBoundaryCondition, true);
        if (result) {
          this->assignDefaultSunExposure(false);
          this->assignDefaultWindExposure(false);

          if (istringEqual("Adiabatic", outsideBoundaryCondition)) {
            // remove all subsurfaces
            int n_subsurfaces = 0;
            for (auto& subSurface : subSurfaces()) {
              subSurface.remove();
              ++n_subsurfaces;
            }
            if (n_subsurfaces > 0) {
              // Note JM 2019-03-05: Warn user, it's not obvious that this is happening and they might try to access again
              // one of these subsurfaces which are now disconnected objects
              LOG(Warn, "Setting the Outside Boundary Condition for Surface '" << this->nameString() << "' to 'Adiabatic', removed " << n_subsurfaces
                                                                               << " SubSurfaces.");
            }
          }
        } else if (adjacentSurface) {
          // restore the adjacent surface if set boundary condition fails
          bool test = setAdjacentSurface(*adjacentSurface);
          OS_ASSERT(test);
          // } else if (surfacePropertyOtherSideCoefficients) {
          //   // restore the surfacePropertyOtherSideCoefficientse if set boundary condition fails
          //   bool test = setSurfacePropertyOtherSideCoefficients(*surfacePropertyOtherSideCoefficients);
          //   OS_ASSERT(test);
          // } else if (surfacePropertyOtherSideConditionsModel) {
          //   // restore the surfacePropertyOtherSideConditionsModel if set boundary condition fails
          //   bool test = setSurfacePropertyOtherSideConditionsModel(*surfacePropertyOtherSideConditionsModel);
          //   OS_ASSERT(test);
        }
      }

      // if (driverMethod) {
      //   this->emitChangeSignals();  // emit signals here
      // }

      return result;
    }

    std::string Surface_Impl::sunExposure() const {
      auto value = getString(openstudio::BuildingSurface_DetailedFields::SunExposure, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool Surface_Impl::isSunExposureDefaulted() const {
      return isEmpty(openstudio::BuildingSurface_DetailedFields::SunExposure);
    }

    bool Surface_Impl::setSunExposure(const std::string& sunExposure) {
      return setString(openstudio::BuildingSurface_DetailedFields::SunExposure, sunExposure, true);
    }

    void Surface_Impl::resetSunExposure() {
      OS_ASSERT(setString(openstudio::BuildingSurface_DetailedFields::SunExposure, ""));
    }

    std::string Surface_Impl::windExposure() const {
      auto value = getString(openstudio::BuildingSurface_DetailedFields::WindExposure, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool Surface_Impl::isWindExposureDefaulted() const {
      return isEmpty(openstudio::BuildingSurface_DetailedFields::WindExposure);
    }

    bool Surface_Impl::setWindExposure(const std::string& windExposure) {
      return setString(openstudio::BuildingSurface_DetailedFields::WindExposure, windExposure, true);
    }

    void Surface_Impl::resetWindExposure() {
      OS_ASSERT(setString(openstudio::BuildingSurface_DetailedFields::WindExposure, ""));
    }

    boost::optional<double> Surface_Impl::viewFactortoGround() const {
      return getDouble(openstudio::BuildingSurface_DetailedFields::ViewFactortoGround, true);
    }

    bool Surface_Impl::isViewFactortoGroundDefaulted() const {
      return isEmpty(openstudio::BuildingSurface_DetailedFields::ViewFactortoGround);
    }

    bool Surface_Impl::isViewFactortoGroundAutocalculated() const {
      if (auto value = getString(openstudio::BuildingSurface_DetailedFields::ViewFactortoGround, true)) {
        return openstudio::istringEqual(value.get(), "Autocalculate");
      }
      return false;
    }

    bool Surface_Impl::setViewFactortoGround(double viewFactortoGround) {
      return setDouble(openstudio::BuildingSurface_DetailedFields::ViewFactortoGround, viewFactortoGround);
    }

    void Surface_Impl::resetViewFactortoGround() {
      OS_ASSERT(setString(openstudio::BuildingSurface_DetailedFields::ViewFactortoGround, ""));
    }

    void Surface_Impl::autocalculateViewFactortoGround() {
      OS_ASSERT(setString(openstudio::BuildingSurface_DetailedFields::ViewFactortoGround, "Autocalculate"));
    }

    unsigned int Surface_Impl::numberofVertices() const {
      if (auto value = getInt(openstudio::BuildingSurface_DetailedFields::NumberofVertices, true)) {
        return static_cast<unsigned int>(*value);
      }
      return static_cast<unsigned int>(vertices().size());
    }

    bool Surface_Impl::isNumberofVerticesDefaulted() const {
      return isEmpty(openstudio::BuildingSurface_DetailedFields::NumberofVertices);
    }

    bool Surface_Impl::isNumberofVerticesAutocalculated() const {
      if (auto value = getString(openstudio::BuildingSurface_DetailedFields::NumberofVertices, true)) {
        return openstudio::istringEqual(value.get(), "Autocalculate");
      }
      return false;
    }

    bool Surface_Impl::setNumberofVertices(unsigned int numberofVertices) {
      return setInt(openstudio::BuildingSurface_DetailedFields::NumberofVertices, numberofVertices);
    }

    void Surface_Impl::resetNumberofVertices() {
      OS_ASSERT(setString(openstudio::BuildingSurface_DetailedFields::NumberofVertices, ""));
    }

    void Surface_Impl::autocalculateNumberofVertices() {
      OS_ASSERT(setString(openstudio::BuildingSurface_DetailedFields::NumberofVertices, "Autocalculate"));
    }

    boost::optional<Space> Surface_Impl::space() const {
      return getObject<openstudio::epmodel::Surface>().getModelObjectTarget<openstudio::epmodel::Space>(
        openstudio::BuildingSurface_DetailedFields::SpaceName);
    }

    bool Surface_Impl::subtractFromGrossArea() const {
      return false;
    }

    bool Surface_Impl::setVertices(const std::vector<Point3d>& vertices) {
      bool result = PlanarSurface_Impl::setVertices(vertices);

      if (isEmpty(openstudio::BuildingSurface_DetailedFields::SurfaceType)) {
        if (result) {
          this->assignDefaultSurfaceType(false);
          this->assignDefaultBoundaryCondition(false);
          this->assignDefaultSunExposure(false);
          this->assignDefaultWindExposure(false);
          this->emitChangeSignals();  // emit signals here
        } else {
          LOG(Error, "Cannot compute default Surface properties.");
        }
      }

      return result;
    }

    std::vector<SubSurface> Surface_Impl::subSurfaces() const {
      return castVector<SubSurface>(getObject<openstudio::epmodel::Surface>().getSources(openstudio::epmodel::SubSurface::iddObjectType()));
    }

    bool Surface_Impl::setSpace(const Space& space) {
      return setPointer(openstudio::BuildingSurface_DetailedFields::SpaceName, space.handle());
    }

    boost::optional<Surface> Surface_Impl::adjacentSurface() const {
      return getObject<Surface>().getModelObjectTarget<Surface>(openstudio::BuildingSurface_DetailedFields::OutsideBoundaryConditionObject);
    }

    bool Surface_Impl::setAdjacentSurface(Surface& surface) {

      // matching surface with self is ok for stories with multipliers
      bool isSameSurface = false;
      if (surface.handle() == this->handle()) {
        isSameSurface = true;
      }

      // matching surface with other surface in same space is ok for stories with multipliers
      //boost::optional<Space> thisSpace = this->space();
      //boost::optional<Space> otherSpace = surface.space();
      //if (!thisSpace || !otherSpace || (thisSpace->handle() == otherSpace->handle())){
      //  return false;
      //}

      boost::optional<Surface> adjacentSurface = this->adjacentSurface();
      boost::optional<Surface> otherAdjacentSurface = surface.adjacentSurface();

      // if other surface is pointing to this
      bool isNewMatch = true;
      if (otherAdjacentSurface && (otherAdjacentSurface->handle() == this->handle())) {
        // if this is pointing to other surface
        if (adjacentSurface && (adjacentSurface->handle() == surface.handle())) {
          isNewMatch = false;
        }
      }

      // this is basically testing if surface is in same model as this
      bool test = this->setPointer(openstudio::BuildingSurface_DetailedFields::OutsideBoundaryConditionObject, surface.handle());
      if (test) {

        // clean all other surfaces pointing to this (unless it is surface)
        for (const WorkspaceObject& wo : this->getSources(Surface::iddObjectType())) {
          if (wo.handle() == surface.handle()) {
            continue;
          }

          auto otherSurface = wo.cast<Surface>();
          test = otherSurface.setString(openstudio::BuildingSurface_DetailedFields::OutsideBoundaryConditionObject, "");
          OS_ASSERT(test);
          otherSurface.assignDefaultBoundaryCondition();
          otherSurface.assignDefaultSunExposure();
          otherSurface.assignDefaultWindExposure();

          for (SubSurface& subSurface : otherSurface.subSurfaces()) {
            subSurface.resetAdjacentSubSurface();
          }
        }

        if (!isSameSurface) {
          // clean all other surfaces pointing to surface (unless it is this)
          for (const WorkspaceObject& wo : surface.getSources(Surface::iddObjectType())) {
            if (wo.handle() == this->handle()) {
              continue;
            }

            auto otherSurface = wo.cast<Surface>();
            test = otherSurface.setString(openstudio::BuildingSurface_DetailedFields::OutsideBoundaryConditionObject, "");
            OS_ASSERT(test);
            otherSurface.assignDefaultBoundaryCondition();
            otherSurface.assignDefaultSunExposure();
            otherSurface.assignDefaultWindExposure();

            for (SubSurface& subSurface : otherSurface.subSurfaces()) {
              subSurface.resetAdjacentSubSurface();
            }
          }
        }

        // this and surface are newly pointing to each other, clean sub surfaces on both
        if (isNewMatch) {
          for (SubSurface& subSurface : this->subSurfaces()) {
            subSurface.resetAdjacentSubSurface();
          }
          if (!isSameSurface) {
            for (SubSurface& subSurface : surface.subSurfaces()) {
              subSurface.resetAdjacentSubSurface();
            }
          }
        }

        // pointer was set up above, it may be unset during calls to resetAdjacentSubSurface above, just reset it here
        bool test = this->setPointer(openstudio::BuildingSurface_DetailedFields::OutsideBoundaryConditionObject, surface.handle());
        OS_ASSERT(test);
        test = this->setString(openstudio::BuildingSurface_DetailedFields::OutsideBoundaryCondition, "Surface");
        OS_ASSERT(test);
        this->assignDefaultSunExposure();
        this->assignDefaultWindExposure();

        if (!isSameSurface) {
          test = surface.setPointer(openstudio::BuildingSurface_DetailedFields::OutsideBoundaryConditionObject, this->handle());
          OS_ASSERT(test);
          test = surface.setString(openstudio::BuildingSurface_DetailedFields::OutsideBoundaryCondition, "Surface");
          OS_ASSERT(test);
          surface.assignDefaultSunExposure();
          surface.assignDefaultWindExposure();
        }
      }
      return test;
    }

    void Surface_Impl::resetAdjacentSurface() {

      // need to be careful to only call assignDefaultBoundaryCondition if adjacentSurface
      // is set as assignDefaultBoundaryCondition can call resetAdjacentSurface
      boost::optional<Surface> adjacentSurface = this->adjacentSurface();
      if (adjacentSurface) {
        bool test = setString(openstudio::BuildingSurface_DetailedFields::OutsideBoundaryConditionObject, "");
        OS_ASSERT(test);
        this->assignDefaultBoundaryCondition();
        this->assignDefaultSunExposure();
        this->assignDefaultWindExposure();
      }

      // unset all matched sub surfaces
      for (SubSurface& subSurface : this->subSurfaces()) {
        subSurface.resetAdjacentSubSurface();
      }

      // clean all other surfaces pointing to this
      for (const WorkspaceObject& wo : this->getSources(Surface::iddObjectType())) {

        auto otherSurface = wo.cast<Surface>();
        bool test = otherSurface.setString(openstudio::BuildingSurface_DetailedFields::OutsideBoundaryConditionObject, "");
        OS_ASSERT(test);
        otherSurface.assignDefaultBoundaryCondition();
        otherSurface.assignDefaultSunExposure();
        otherSurface.assignDefaultWindExposure();

        for (SubSurface& subSurface : otherSurface.subSurfaces()) {
          subSurface.resetAdjacentSubSurface();
        }
      }
    }

    bool Surface_Impl::isGroundSurface() const {
      std::string outsideBoundaryCondition = this->outsideBoundaryCondition();

      static constexpr std::array groundBoundaryConditions{
        "Ground",
        "GroundFCfactorMethod",
        "GroundSlabPreprocessorAverage",
        "GroundSlabPreprocessorCore",
        "GroundSlabPreprocessorPerimeter",
        "GroundBasementPreprocessorAverageWall",
        "GroundBasementPreprocessorAverageFloor",
        "GroundBasementPreprocessorUpperWall",
        "GroundBasementPreprocessorLowerWall",
        "Foundation",
      };
      return std::find_if(groundBoundaryConditions.cbegin(), groundBoundaryConditions.cend(),
                          [&outsideBoundaryCondition](auto c) { return openstudio::istringEqual(outsideBoundaryCondition, c); })
             != groundBoundaryConditions.cend();
    }

    bool Surface_Impl::isPartOfEnvelope() const {
      std::string bc = this->outsideBoundaryCondition();
      bool result = (istringEqual("Outdoors", bc) || this->isGroundSurface());
      return result;
    }

    void Surface_Impl::assignDefaultSurfaceType(bool /*emitChangeSignals*/) {
      double degTilt = radToDeg(this->tilt());
      bool ok = true;
      if (degTilt < 60) {
        ok = setSurfaceType("Roof");  // RoofCeiling
        OS_ASSERT(ok);
      } else if (degTilt < 179) {
        ok = setSurfaceType("Wall");
        OS_ASSERT(ok);
      } else {
        ok = setSurfaceType("Floor");
        OS_ASSERT(ok);
      }
      // if (emitChangeSignals) { this->emitChangeSignals(); }
    }

    void Surface_Impl::assignDefaultBoundaryCondition(bool /*emitChangeSignals*/) {
      if (this->adjacentSurface()) {
        bool test = this->setOutsideBoundaryCondition("Surface");
        OS_ASSERT(test);
        // TODO
        // } else if (this->surfacePropertyOtherSideCoefficients()) {
        //   bool test = this->setOutsideBoundaryCondition("OtherSideCoefficients");
        //   OS_ASSERT(test);
        // } else if (this->surfacePropertyOtherSideConditionsModel()) {
        //   bool test = this->setOutsideBoundaryCondition("OtherSideConditionsModel");
        //   OS_ASSERT(test);
        // } else if (this->adjacentFoundation()) {
        //   bool test = this->setOutsideBoundaryCondition("Foundation");
        //   OS_ASSERT(test);
      } else if (istringEqual("Floor", this->surfaceType())) {
        bool test = this->setOutsideBoundaryCondition("Ground");
        OS_ASSERT(test);
      } else {
        bool test = this->setOutsideBoundaryCondition("Outdoors");
        OS_ASSERT(test);
      }
      // if (emitChangeSignals) { this->emitChangeSignals(); }
    }

    void Surface_Impl::assignDefaultSunExposure(bool /*emitChangeSignals*/) {
      std::string outsideBoundaryCondition = this->outsideBoundaryCondition();
      if (istringEqual("Outdoors", outsideBoundaryCondition)) {
        bool test = this->setSunExposure("SunExposed");
        OS_ASSERT(test);
      } else if (istringEqual("Surface", outsideBoundaryCondition) || istringEqual("OtherSideCoefficients", outsideBoundaryCondition)
                 || istringEqual("Adiabatic", outsideBoundaryCondition) || this->isGroundSurface()) {
        bool test = this->setSunExposure("NoSun");
        OS_ASSERT(test);
      } else {
        std::string surfaceType = this->surfaceType();
        if (istringEqual("Floor", surfaceType)) {
          bool test = this->setSunExposure("NoSun");
          OS_ASSERT(test);
        } else {
          bool test = this->setSunExposure("SunExposed");
          OS_ASSERT(test);
        }
      }
      // if (emitChangeSignals) { this->emitChangeSignals(); }
    }

    void Surface_Impl::assignDefaultWindExposure(bool /*emitChangeSignals*/) {
      std::string outsideBoundaryCondition = this->outsideBoundaryCondition();
      if (istringEqual("Outdoors", outsideBoundaryCondition)) {
        bool test = this->setWindExposure("WindExposed");
        OS_ASSERT(test);
      } else if (istringEqual("Surface", outsideBoundaryCondition) || istringEqual("OtherSideCoefficients", outsideBoundaryCondition)
                 || istringEqual("Adiabatic", outsideBoundaryCondition) || this->isGroundSurface()) {
        bool test = this->setWindExposure("NoWind");
        OS_ASSERT(test);
      } else {
        std::string surfaceType = this->surfaceType();
        if (istringEqual("Floor", surfaceType)) {
          bool test = this->setWindExposure("NoWind");
          OS_ASSERT(test);
        } else {
          bool test = this->setWindExposure("WindExposed");
          OS_ASSERT(test);
        }
      }
      // if (emitChangeSignals) { this->emitChangeSignals(); }
    }

    bool Surface_Impl::intersect(Surface& otherSurface) {
      boost::optional<SurfaceIntersection> intersection = computeIntersection(otherSurface);
      return intersection.has_value();
    }

    boost::optional<SurfaceIntersection> Surface_Impl::computeIntersection(Surface& otherSurface) {
      double tol = 0.01;       //  1 cm tolerance
      double areaTol = 0.001;  // 10 cm2 tolerance

      constexpr bool extraLogging = false;

      boost::optional<Space> space = this->space();
      boost::optional<Space> otherSpace = otherSurface.space();

      if (!space || !otherSpace || space->handle() == otherSpace->handle()) {
        LOG(Error, "Cannot find spaces for each surface in intersection or surfaces in same space.");
        return boost::none;
      }

      if (!this->subSurfaces().empty() || !otherSurface.subSurfaces().empty()) {
        LOG(Error, "Subsurfaces are not allowed in intersection");
        return boost::none;
      }

      if (this->adjacentSurface() || otherSurface.adjacentSurface()) {
        LOG(Error, "Adjacent surfaces are not allowed in intersection");
        return boost::none;
      }

      // goes from local system to building coordinates
      Transformation spaceTransformation = space->transformation();
      Transformation otherSpaceTransformation = otherSpace->transformation();

      // do the intersection in building coordinates

      Plane plane = spaceTransformation * this->plane();
      Plane otherPlane = otherSpaceTransformation * otherSurface.plane();

      if (!plane.reverseEqual(otherPlane)) {
        //LOG(Info, "Planes are not reverse equal, intersection of '" << this->nameString() << "' with '" << otherSurface.nameString() << "' fails");
        return boost::none;
      }

      // get vertices in building coordinates
      std::vector<Point3d> buildingVertices = spaceTransformation * this->vertices();
      std::vector<Point3d> otherBuildingVertices = otherSpaceTransformation * otherSurface.vertices();

      if ((buildingVertices.size() < 3) || (otherBuildingVertices.size() < 3)) {
        LOG(Error, "Fewer than 3 vertices, intersection of '" << this->nameString() << "' with '" << otherSurface.nameString() << "' fails");
        return boost::none;
      }

      // goes from face coordinates of building vertices to building coordinates
      Transformation faceTransformation;
      Transformation faceTransformationInverse;
      try {
        faceTransformation = Transformation::alignFace(buildingVertices);
        faceTransformationInverse = faceTransformation.inverse();
      } catch (const std::exception&) {
        LOG(Error, "Cannot compute face transform, intersection of '" << this->nameString() << "' with '" << otherSurface.nameString() << "' fails");
        return boost::none;
      }

      // put building vertices into face coordinates
      std::vector<Point3d> faceVertices = faceTransformationInverse * buildingVertices;
      std::vector<Point3d> otherFaceVertices = faceTransformationInverse * otherBuildingVertices;

      // boost polygon wants vertices in clockwise order, faceVertices must be reversed, otherFaceVertices already CCW
      std::reverse(faceVertices.begin(), faceVertices.end());
      //std::reverse(otherFaceVertices.begin(), otherFaceVertices.end());

      //LOG(Info, "Trying intersection of '" << this->nameString() << "' with '" << otherSurface.nameString());
      if constexpr (extraLogging) {
        Point3dVectorVector tmp{faceVertices, otherFaceVertices};
        LOG(Debug, tmp);
      }
      boost::optional<IntersectionResult> intersection = openstudio::intersect(faceVertices, otherFaceVertices, tol);
      if (!intersection) {
        //LOG(Info, "No intersection");
        return boost::none;
      }

      if constexpr (extraLogging) {
        Point3dVectorVector tmp;
        Point3dVectorVector newPolys = intersection->newPolygons2();
        tmp.reserve(newPolys.size() + 1);
        tmp.push_back(intersection->polygon2());
        tmp.insert(tmp.end(), std::make_move_iterator(newPolys.begin()), std::make_move_iterator(newPolys.end()));
        LOG(Debug, tmp);
      }

      // DA - Change tolerance. Current tolerance is 0.0001 which is 1cm2 which is unrealistic
      // tolerance could be fixed, say 10cm2 or as a proportion of the area of the polygon. 4cm2
      // on a polygon of area 570m2 is a tiny fraction
      boost::optional<double> area1 = getArea(faceVertices);
      boost::optional<double> area2 = getArea(otherFaceVertices);
      if (area1) {
        if (std::abs(area1.get() - intersection->area1()) > areaTol) {
          LOG(Error, "Initial area of surface '" << this->nameString() << "' " << area1.get() << " does not equal post intersection area "
                                                 << intersection->area1());
          if constexpr (extraLogging) {
            Point3dVectorVector tmp1{faceVertices, otherFaceVertices};
            LOG(Debug, tmp1);
            Point3dVectorVector tmp;
            tmp.push_back(intersection->polygon1());
            for (auto& x : intersection->newPolygons1()) {
              tmp.push_back(x);
            }
            LOG(Debug, tmp);
          }
        }
      }
      if (area2) {
        if (std::abs(area2.get() - intersection->area2()) > areaTol) {
          LOG(Error, "Initial area of other surface '" << otherSurface.nameString() << "' " << area2.get()
                                                       << " does not equal post intersection area " << intersection->area2());
          if constexpr (extraLogging) {
            Point3dVectorVector tmp1{faceVertices, otherFaceVertices};
            LOG(Debug, tmp1);
            Point3dVectorVector tmp;
            tmp.push_back(intersection->polygon2());
            for (auto& x : intersection->newPolygons2()) {
              tmp.push_back(x);
            }
            LOG(Debug, tmp);
          }
        }
      }

      // non-zero intersection
      // could match here but will save that for other discrete operation
      Surface surface(std::dynamic_pointer_cast<Surface_Impl>(this->shared_from_this()));
      std::vector<Surface> newSurfaces;
      std::vector<Surface> newOtherSurfaces;

      //LOG(Debug, "Before intersection");
      //LOG(Debug, surface);
      //LOG(Debug, otherSurface);

      // goes from building coordinates to local system
      Transformation spaceTransformationInverse = spaceTransformation.inverse();
      Transformation otherSpaceTransformationInverse = otherSpaceTransformation.inverse();

      std::vector<std::vector<Point3d>> newPolygons1 = intersection->newPolygons1();
      std::vector<std::vector<Point3d>> newPolygons2 = intersection->newPolygons2();

      // modify vertices for surface in this space
      std::vector<Point3d> newBuildingVertices = faceTransformation * intersection->polygon1();
      std::vector<Point3d> newVertices = spaceTransformationInverse * newBuildingVertices;
      std::reverse(newVertices.begin(), newVertices.end());
      newVertices = reorderULC(newVertices);
      this->setVertices(newVertices);
      //this->setAdjacentSurface(otherSurface);

      // modify vertices for surface in other space
      std::vector<Point3d> newOtherBuildingVertices = faceTransformation * intersection->polygon2();
      std::vector<Point3d> newOtherVertices = otherSpaceTransformationInverse * newOtherBuildingVertices;
      newOtherVertices = reorderULC(newOtherVertices);
      otherSurface.setVertices(newOtherVertices);
      //otherSurface.setAdjacentSurface(surface);

      if (newPolygons1.empty() && newPolygons2.empty()) {
        // both surfaces intersect perfectly, no-op
      } else {
        // new surfaces are created
        // create new surfaces in this space
        for (const auto& newPoly1 : newPolygons1) {

          // new surface in this space
          newBuildingVertices = faceTransformation * newPoly1;
          newVertices = spaceTransformationInverse * newBuildingVertices;
          std::reverse(newVertices.begin(), newVertices.end());
          newVertices = reorderULC(newVertices);
          Surface newSurface(newVertices, this->model());
          newSurface.setSpace(*space);
          newSurfaces.push_back(newSurface);
        }

        // create new surfaces in other space
        for (const auto& newPoly2 : newPolygons2) {

          // new surface in other space
          newOtherBuildingVertices = faceTransformation * newPoly2;
          newOtherVertices = otherSpaceTransformationInverse * newOtherBuildingVertices;
          newOtherVertices = reorderULC(newOtherVertices);
          Surface newOtherSurface(newOtherVertices, this->model());
          newOtherSurface.setSpace(*otherSpace);
          newOtherSurfaces.push_back(newOtherSurface);
        }
      }

      SurfaceIntersection result(std::move(surface), std::move(otherSurface), std::move(newSurfaces), std::move(newOtherSurfaces));
      LOG(Info, "Intersection of '" << this->nameString() << "' with '" << result.surface2().nameString() << "' results in " << result);

      return result;
    }

    boost::optional<Surface> Surface_Impl::createAdjacentSurface(const Space& otherSpace) {
      boost::optional<Space> space = this->space();
      if (!space || (space->handle() == otherSpace.handle())) {
        return boost::none;
      }

      Transformation thisSpaceT = space->transformation();
      Transformation otherSpaceT = otherSpace.transformation();
      Transformation transformation = otherSpaceT.inverse() * thisSpaceT;

      std::vector<Point3d> vertices = transformation * this->vertices();
      std::reverse(vertices.begin(), vertices.end());

      Model model = this->model();

      // Be careful not to call clone as you will get duplicate sub surfaces
      Surface otherSurface(vertices, model);
      otherSurface.setName(this->nameString() + " Reversed");
      // TODO: otherSurface.resetConstruction();  // this will use surface's construction on export, TODO: do something better

      std::string surfaceType = this->surfaceType();
      if (surfaceType == "RoofCeiling") {
        otherSurface.setSurfaceType("Floor");
      } else if (surfaceType == "Floor") {
        otherSurface.setSurfaceType("RoofCeiling");
      } else if (surfaceType == "Wall") {
        otherSurface.setSurfaceType("Wall");
      }

      otherSurface.setSpace(otherSpace);

      this->setAdjacentSurface(otherSurface);

      for (SubSurface& subSurface : this->subSurfaces()) {
        vertices = transformation * subSurface.vertices();
        std::reverse(vertices.begin(), vertices.end());

        SubSurface otherSubSurface(vertices, model);
        otherSubSurface.setName(subSurface.nameString() + " Reversed");
        // otherSubSurface.resetConstruction();  // this will use sub surface's construction on export, TODO: do something better
        otherSubSurface.setSubSurfaceType(subSurface.subSurfaceType());
        otherSubSurface.setSurface(otherSurface);
        otherSubSurface.setAdjacentSubSurface(subSurface);
      }

      return otherSurface;
    }

  }  // namespace detail

  SurfaceIntersection::SurfaceIntersection(Surface surface1, Surface surface2, std::vector<Surface> newSurfaces1, std::vector<Surface> newSurfaces2)
    : m_surface1(std::move(surface1)),
      m_surface2(std::move(surface2)),
      m_newSurfaces1(std::move(newSurfaces1)),
      m_newSurfaces2(std::move(newSurfaces2)) {}

  Surface SurfaceIntersection::surface1() const {
    return m_surface1;
  }

  Surface SurfaceIntersection::surface2() const {
    return m_surface2;
  }

  std::vector<Surface> SurfaceIntersection::newSurfaces1() const {
    return m_newSurfaces1;
  }

  std::vector<Surface> SurfaceIntersection::newSurfaces2() const {
    return m_newSurfaces2;
  }

  std::ostream& operator<<(std::ostream& os, const SurfaceIntersection& surfaceIntersection) {
    os << "(" << surfaceIntersection.surface1().nameString() << "), ";

    os << "(" << surfaceIntersection.surface2().nameString() << "), ";

    os << "[";
    std::vector<Surface> newSurfaces1 = surfaceIntersection.newSurfaces1();
    for (unsigned i = 0; i < newSurfaces1.size(); ++i) {
      os << newSurfaces1[i].nameString();
      if (i != newSurfaces1.size() - 1) {
        os << ", ";
      }
    }

    os << "], [";
    std::vector<Surface> newSurfaces2 = surfaceIntersection.newSurfaces2();
    for (unsigned i = 0; i < newSurfaces2.size(); ++i) {
      os << newSurfaces2[i].nameString();
      if (i != newSurfaces2.size() - 1) {
        os << ", ";
      }
    }
    os << "]";

    return os;
  }

}  // namespace epmodel
}  // namespace openstudio
