/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "RoofCeilingDetailed.hpp"
#include "RoofCeilingDetailed_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/RoofCeiling_Detailed_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  RoofCeilingDetailed::RoofCeilingDetailed(const Model& model) : ModelObject(RoofCeilingDetailed::iddObjectType(), model) {}

  RoofCeilingDetailed::RoofCeilingDetailed(std::shared_ptr<detail::RoofCeilingDetailed_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType RoofCeilingDetailed::iddObjectType() {
    return IddObjectType::RoofCeiling_Detailed;
  }

  std::vector<std::string> RoofCeilingDetailed::outsideBoundaryConditionValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::RoofCeiling_DetailedFields::OutsideBoundaryCondition);
  }

  std::vector<std::string> RoofCeilingDetailed::sunExposureValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::RoofCeiling_DetailedFields::SunExposure);
  }

  std::vector<std::string> RoofCeilingDetailed::windExposureValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::RoofCeiling_DetailedFields::WindExposure);
  }

  std::string RoofCeilingDetailed::outsideBoundaryCondition() const {
    return getImpl<detail::RoofCeilingDetailed_Impl>()->outsideBoundaryCondition();
  }

  bool RoofCeilingDetailed::setOutsideBoundaryCondition(const std::string& outsideBoundaryCondition) {
    return getImpl<detail::RoofCeilingDetailed_Impl>()->setOutsideBoundaryCondition(outsideBoundaryCondition);
  }

  std::string RoofCeilingDetailed::sunExposure() const {
    return getImpl<detail::RoofCeilingDetailed_Impl>()->sunExposure();
  }

  bool RoofCeilingDetailed::isSunExposureDefaulted() const {
    return getImpl<detail::RoofCeilingDetailed_Impl>()->isSunExposureDefaulted();
  }

  bool RoofCeilingDetailed::setSunExposure(const std::string& sunExposure) {
    return getImpl<detail::RoofCeilingDetailed_Impl>()->setSunExposure(sunExposure);
  }

  void RoofCeilingDetailed::resetSunExposure() {
    getImpl<detail::RoofCeilingDetailed_Impl>()->resetSunExposure();
  }

  std::string RoofCeilingDetailed::windExposure() const {
    return getImpl<detail::RoofCeilingDetailed_Impl>()->windExposure();
  }

  bool RoofCeilingDetailed::isWindExposureDefaulted() const {
    return getImpl<detail::RoofCeilingDetailed_Impl>()->isWindExposureDefaulted();
  }

  bool RoofCeilingDetailed::setWindExposure(const std::string& windExposure) {
    return getImpl<detail::RoofCeilingDetailed_Impl>()->setWindExposure(windExposure);
  }

  void RoofCeilingDetailed::resetWindExposure() {
    getImpl<detail::RoofCeilingDetailed_Impl>()->resetWindExposure();
  }

  boost::optional<double> RoofCeilingDetailed::viewFactortoGround() const {
    return getImpl<detail::RoofCeilingDetailed_Impl>()->viewFactortoGround();
  }

  bool RoofCeilingDetailed::setViewFactortoGround(double viewFactortoGround) {
    return getImpl<detail::RoofCeilingDetailed_Impl>()->setViewFactortoGround(viewFactortoGround);
  }

  bool RoofCeilingDetailed::isViewFactortoGroundAutocalculated() const {
    return getImpl<detail::RoofCeilingDetailed_Impl>()->isViewFactortoGroundAutocalculated();
  }

  void RoofCeilingDetailed::autocalculateViewFactortoGround() {
    getImpl<detail::RoofCeilingDetailed_Impl>()->autocalculateViewFactortoGround();
  }

  void RoofCeilingDetailed::resetViewFactortoGround() {
    getImpl<detail::RoofCeilingDetailed_Impl>()->resetViewFactortoGround();
  }

  boost::optional<int> RoofCeilingDetailed::numberofVertices() const {
    return getImpl<detail::RoofCeilingDetailed_Impl>()->numberofVertices();
  }

  bool RoofCeilingDetailed::setNumberofVertices(int numberofVertices) {
    return getImpl<detail::RoofCeilingDetailed_Impl>()->setNumberofVertices(numberofVertices);
  }

  bool RoofCeilingDetailed::isNumberofVerticesAutocalculated() const {
    return getImpl<detail::RoofCeilingDetailed_Impl>()->isNumberofVerticesAutocalculated();
  }

  void RoofCeilingDetailed::autocalculateNumberofVertices() {
    getImpl<detail::RoofCeilingDetailed_Impl>()->autocalculateNumberofVertices();
  }

  void RoofCeilingDetailed::resetNumberofVertices() {
    getImpl<detail::RoofCeilingDetailed_Impl>()->resetNumberofVertices();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::string RoofCeilingDetailed_Impl::outsideBoundaryCondition() const {
      const auto value = getString(openstudio::RoofCeiling_DetailedFields::OutsideBoundaryCondition, true);
      OS_ASSERT(value);
      return *value;
    }

    bool RoofCeilingDetailed_Impl::setOutsideBoundaryCondition(const std::string& outsideBoundaryCondition) {
      return setString(openstudio::RoofCeiling_DetailedFields::OutsideBoundaryCondition, outsideBoundaryCondition);
    }

    std::string RoofCeilingDetailed_Impl::sunExposure() const {
      const auto value = getString(openstudio::RoofCeiling_DetailedFields::SunExposure, true);
      OS_ASSERT(value);
      return *value;
    }

    bool RoofCeilingDetailed_Impl::isSunExposureDefaulted() const {
      return isEmpty(openstudio::RoofCeiling_DetailedFields::SunExposure);
    }

    bool RoofCeilingDetailed_Impl::setSunExposure(const std::string& sunExposure) {
      return setString(openstudio::RoofCeiling_DetailedFields::SunExposure, sunExposure);
    }

    void RoofCeilingDetailed_Impl::resetSunExposure() {
      OS_ASSERT(setString(openstudio::RoofCeiling_DetailedFields::SunExposure, ""));
    }

    std::string RoofCeilingDetailed_Impl::windExposure() const {
      const auto value = getString(openstudio::RoofCeiling_DetailedFields::WindExposure, true);
      OS_ASSERT(value);
      return *value;
    }

    bool RoofCeilingDetailed_Impl::isWindExposureDefaulted() const {
      return isEmpty(openstudio::RoofCeiling_DetailedFields::WindExposure);
    }

    bool RoofCeilingDetailed_Impl::setWindExposure(const std::string& windExposure) {
      return setString(openstudio::RoofCeiling_DetailedFields::WindExposure, windExposure);
    }

    void RoofCeilingDetailed_Impl::resetWindExposure() {
      OS_ASSERT(setString(openstudio::RoofCeiling_DetailedFields::WindExposure, ""));
    }

    boost::optional<double> RoofCeilingDetailed_Impl::viewFactortoGround() const {
      return getDouble(openstudio::RoofCeiling_DetailedFields::ViewFactortoGround, true);
    }

    bool RoofCeilingDetailed_Impl::setViewFactortoGround(double viewFactortoGround) {
      return setDouble(openstudio::RoofCeiling_DetailedFields::ViewFactortoGround, viewFactortoGround);
    }

    bool RoofCeilingDetailed_Impl::isViewFactortoGroundAutocalculated() const {
      if (const auto value = getString(openstudio::RoofCeiling_DetailedFields::ViewFactortoGround, true)) {
        return openstudio::istringEqual(*value, "autocalculate");
      }
      return false;
    }

    void RoofCeilingDetailed_Impl::autocalculateViewFactortoGround() {
      OS_ASSERT(setString(openstudio::RoofCeiling_DetailedFields::ViewFactortoGround, "autocalculate"));
    }

    void RoofCeilingDetailed_Impl::resetViewFactortoGround() {
      OS_ASSERT(setString(openstudio::RoofCeiling_DetailedFields::ViewFactortoGround, ""));
    }

    boost::optional<int> RoofCeilingDetailed_Impl::numberofVertices() const {
      return getInt(openstudio::RoofCeiling_DetailedFields::NumberofVertices, true);
    }

    bool RoofCeilingDetailed_Impl::setNumberofVertices(int numberofVertices) {
      return setInt(openstudio::RoofCeiling_DetailedFields::NumberofVertices, numberofVertices);
    }

    bool RoofCeilingDetailed_Impl::isNumberofVerticesAutocalculated() const {
      if (const auto value = getString(openstudio::RoofCeiling_DetailedFields::NumberofVertices, true)) {
        return openstudio::istringEqual(*value, "autocalculate");
      }
      return false;
    }

    void RoofCeilingDetailed_Impl::autocalculateNumberofVertices() {
      OS_ASSERT(setString(openstudio::RoofCeiling_DetailedFields::NumberofVertices, "autocalculate"));
    }

    void RoofCeilingDetailed_Impl::resetNumberofVertices() {
      OS_ASSERT(setString(openstudio::RoofCeiling_DetailedFields::NumberofVertices, ""));
    }

    std::vector<std::string> RoofCeilingDetailed_Impl::outsideBoundaryConditionValues() const {
      return openstudio::epmodel::RoofCeilingDetailed::outsideBoundaryConditionValues();
    }

    std::vector<std::string> RoofCeilingDetailed_Impl::sunExposureValues() const {
      return openstudio::epmodel::RoofCeilingDetailed::sunExposureValues();
    }

    std::vector<std::string> RoofCeilingDetailed_Impl::windExposureValues() const {
      return openstudio::epmodel::RoofCeilingDetailed::windExposureValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
