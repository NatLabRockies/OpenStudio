/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "PlanarSurface/Surface.hpp"
#include "PlanarSurface/Surface_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/BuildingSurface_Detailed_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

  Surface::Surface(const Model& model) : ModelObject(Surface::iddObjectType(), model) {}

  Surface::Surface(std::shared_ptr<detail::Surface_Impl> impl) : ModelObject(std::move(impl)) {}

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

  bool Surface::setViewFactortoGround(boost::optional<double> viewFactortoGround) {
    return getImpl<detail::Surface_Impl>()->setViewFactortoGround(viewFactortoGround);
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

  boost::optional<double> Surface::numberofVertices() const {
    return getImpl<detail::Surface_Impl>()->numberofVertices();
  }

  bool Surface::isNumberofVerticesDefaulted() const {
    return getImpl<detail::Surface_Impl>()->isNumberofVerticesDefaulted();
  }

  bool Surface::isNumberofVerticesAutocalculated() const {
    return getImpl<detail::Surface_Impl>()->isNumberofVerticesAutocalculated();
  }

  bool Surface::setNumberofVertices(boost::optional<double> numberofVertices) {
    return getImpl<detail::Surface_Impl>()->setNumberofVertices(numberofVertices);
  }

  bool Surface::setNumberofVertices(double numberofVertices) {
    return getImpl<detail::Surface_Impl>()->setNumberofVertices(numberofVertices);
  }

  void Surface::resetNumberofVertices() {
    getImpl<detail::Surface_Impl>()->resetNumberofVertices();
  }

  void Surface::autocalculateNumberofVertices() {
    getImpl<detail::Surface_Impl>()->autocalculateNumberofVertices();
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
      return setString(openstudio::BuildingSurface_DetailedFields::OutsideBoundaryCondition, outsideBoundaryCondition, true);
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

    bool Surface_Impl::setViewFactortoGround(boost::optional<double> viewFactortoGround) {
      bool result = false;
      if (viewFactortoGround) {
        result = setDouble(openstudio::BuildingSurface_DetailedFields::ViewFactortoGround, viewFactortoGround.get());
      } else {
        result = setString(openstudio::BuildingSurface_DetailedFields::ViewFactortoGround, "");
      }
      return result;
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

    boost::optional<double> Surface_Impl::numberofVertices() const {
      return getDouble(openstudio::BuildingSurface_DetailedFields::NumberofVertices, true);
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

    bool Surface_Impl::setNumberofVertices(boost::optional<double> numberofVertices) {
      bool result = false;
      if (numberofVertices) {
        result = setDouble(openstudio::BuildingSurface_DetailedFields::NumberofVertices, numberofVertices.get());
      } else {
        result = setString(openstudio::BuildingSurface_DetailedFields::NumberofVertices, "");
      }
      return result;
    }

    bool Surface_Impl::setNumberofVertices(double numberofVertices) {
      return setDouble(openstudio::BuildingSurface_DetailedFields::NumberofVertices, numberofVertices);
    }

    void Surface_Impl::resetNumberofVertices() {
      OS_ASSERT(setString(openstudio::BuildingSurface_DetailedFields::NumberofVertices, ""));
    }

    void Surface_Impl::autocalculateNumberofVertices() {
      OS_ASSERT(setString(openstudio::BuildingSurface_DetailedFields::NumberofVertices, "Autocalculate"));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
