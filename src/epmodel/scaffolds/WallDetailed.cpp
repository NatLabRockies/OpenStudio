/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "Model.hpp"
#include "scaffolds/WallDetailed.hpp"
#include "scaffolds/WallDetailed_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/Wall_Detailed_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  WallDetailed::WallDetailed(const Model& model) : ModelObject(WallDetailed::iddObjectType(), model) {}

  WallDetailed::WallDetailed(std::shared_ptr<detail::WallDetailed_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType WallDetailed::iddObjectType() {
    return IddObjectType::Wall_Detailed;
  }

  std::vector<std::string> WallDetailed::outsideBoundaryConditionValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Wall_DetailedFields::OutsideBoundaryCondition);
  }

  std::vector<std::string> WallDetailed::sunExposureValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Wall_DetailedFields::SunExposure);
  }

  std::vector<std::string> WallDetailed::windExposureValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Wall_DetailedFields::WindExposure);
  }

  std::string WallDetailed::outsideBoundaryCondition() const {
    return getImpl<detail::WallDetailed_Impl>()->outsideBoundaryCondition();
  }

  bool WallDetailed::setOutsideBoundaryCondition(const std::string& outsideBoundaryCondition) {
    return getImpl<detail::WallDetailed_Impl>()->setOutsideBoundaryCondition(outsideBoundaryCondition);
  }

  std::string WallDetailed::sunExposure() const {
    return getImpl<detail::WallDetailed_Impl>()->sunExposure();
  }

  bool WallDetailed::setSunExposure(const std::string& sunExposure) {
    return getImpl<detail::WallDetailed_Impl>()->setSunExposure(sunExposure);
  }

  bool WallDetailed::isSunExposureDefaulted() const {
    return getImpl<detail::WallDetailed_Impl>()->isSunExposureDefaulted();
  }

  void WallDetailed::resetSunExposure() {
    getImpl<detail::WallDetailed_Impl>()->resetSunExposure();
  }

  std::string WallDetailed::windExposure() const {
    return getImpl<detail::WallDetailed_Impl>()->windExposure();
  }

  bool WallDetailed::setWindExposure(const std::string& windExposure) {
    return getImpl<detail::WallDetailed_Impl>()->setWindExposure(windExposure);
  }

  bool WallDetailed::isWindExposureDefaulted() const {
    return getImpl<detail::WallDetailed_Impl>()->isWindExposureDefaulted();
  }

  void WallDetailed::resetWindExposure() {
    getImpl<detail::WallDetailed_Impl>()->resetWindExposure();
  }

  boost::optional<double> WallDetailed::viewFactorToGround() const {
    return getImpl<detail::WallDetailed_Impl>()->viewFactorToGround();
  }

  bool WallDetailed::isViewFactorToGroundDefaulted() const {
    return getImpl<detail::WallDetailed_Impl>()->isViewFactorToGroundDefaulted();
  }

  bool WallDetailed::isViewFactorToGroundAutocalculated() const {
    return getImpl<detail::WallDetailed_Impl>()->isViewFactorToGroundAutocalculated();
  }

  bool WallDetailed::setViewFactorToGround(double viewFactorToGround) {
    return getImpl<detail::WallDetailed_Impl>()->setViewFactorToGround(viewFactorToGround);
  }

  void WallDetailed::resetViewFactorToGround() {
    getImpl<detail::WallDetailed_Impl>()->resetViewFactorToGround();
  }

  void WallDetailed::autocalculateViewFactorToGround() {
    getImpl<detail::WallDetailed_Impl>()->autocalculateViewFactorToGround();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::string WallDetailed_Impl::outsideBoundaryCondition() const {
      const auto value = getString(openstudio::Wall_DetailedFields::OutsideBoundaryCondition, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WallDetailed_Impl::setOutsideBoundaryCondition(const std::string& outsideBoundaryCondition) {
      return setString(openstudio::Wall_DetailedFields::OutsideBoundaryCondition, outsideBoundaryCondition);
    }

    std::string WallDetailed_Impl::sunExposure() const {
      const auto value = getString(openstudio::Wall_DetailedFields::SunExposure, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WallDetailed_Impl::setSunExposure(const std::string& sunExposure) {
      return setString(openstudio::Wall_DetailedFields::SunExposure, sunExposure);
    }

    bool WallDetailed_Impl::isSunExposureDefaulted() const {
      return isEmpty(openstudio::Wall_DetailedFields::SunExposure);
    }

    void WallDetailed_Impl::resetSunExposure() {
      OS_ASSERT(setString(openstudio::Wall_DetailedFields::SunExposure, ""));
    }

    std::string WallDetailed_Impl::windExposure() const {
      const auto value = getString(openstudio::Wall_DetailedFields::WindExposure, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WallDetailed_Impl::setWindExposure(const std::string& windExposure) {
      return setString(openstudio::Wall_DetailedFields::WindExposure, windExposure);
    }

    bool WallDetailed_Impl::isWindExposureDefaulted() const {
      return isEmpty(openstudio::Wall_DetailedFields::WindExposure);
    }

    void WallDetailed_Impl::resetWindExposure() {
      OS_ASSERT(setString(openstudio::Wall_DetailedFields::WindExposure, ""));
    }

    boost::optional<double> WallDetailed_Impl::viewFactorToGround() const {
      return getDouble(openstudio::Wall_DetailedFields::ViewFactortoGround, true);
    }

    bool WallDetailed_Impl::isViewFactorToGroundDefaulted() const {
      return isEmpty(openstudio::Wall_DetailedFields::ViewFactortoGround);
    }

    bool WallDetailed_Impl::isViewFactorToGroundAutocalculated() const {
      if (auto value = getString(openstudio::Wall_DetailedFields::ViewFactortoGround, true)) {
        return openstudio::istringEqual(*value, "autocalculate");
      }
      return false;
    }

    bool WallDetailed_Impl::setViewFactorToGround(double viewFactorToGround) {
      return setDouble(openstudio::Wall_DetailedFields::ViewFactortoGround, viewFactorToGround);
    }

    void WallDetailed_Impl::resetViewFactorToGround() {
      OS_ASSERT(setString(openstudio::Wall_DetailedFields::ViewFactortoGround, ""));
    }

    void WallDetailed_Impl::autocalculateViewFactorToGround() {
      OS_ASSERT(setString(openstudio::Wall_DetailedFields::ViewFactortoGround, "autocalculate"));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
