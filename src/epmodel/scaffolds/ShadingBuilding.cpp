/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ShadingBuilding.hpp"
#include "ShadingBuilding_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/Shading_Building_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  ShadingBuilding::ShadingBuilding(const Model& model) : ModelObject(ShadingBuilding::iddObjectType(), model) {}

  ShadingBuilding::ShadingBuilding(std::shared_ptr<detail::ShadingBuilding_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType ShadingBuilding::iddObjectType() {
    return IddObjectType::Shading_Building;
  }

  boost::optional<double> ShadingBuilding::azimuthAngle() const {
    return getImpl<detail::ShadingBuilding_Impl>()->azimuthAngle();
  }

  bool ShadingBuilding::setAzimuthAngle(double azimuthAngle) {
    return getImpl<detail::ShadingBuilding_Impl>()->setAzimuthAngle(azimuthAngle);
  }

  void ShadingBuilding::resetAzimuthAngle() {
    getImpl<detail::ShadingBuilding_Impl>()->resetAzimuthAngle();
  }

  double ShadingBuilding::tiltAngle() const {
    return getImpl<detail::ShadingBuilding_Impl>()->tiltAngle();
  }

  bool ShadingBuilding::isTiltAngleDefaulted() const {
    return getImpl<detail::ShadingBuilding_Impl>()->isTiltAngleDefaulted();
  }

  bool ShadingBuilding::setTiltAngle(double tiltAngle) {
    return getImpl<detail::ShadingBuilding_Impl>()->setTiltAngle(tiltAngle);
  }

  void ShadingBuilding::resetTiltAngle() {
    getImpl<detail::ShadingBuilding_Impl>()->resetTiltAngle();
  }

  boost::optional<double> ShadingBuilding::startingXCoordinate() const {
    return getImpl<detail::ShadingBuilding_Impl>()->startingXCoordinate();
  }

  bool ShadingBuilding::setStartingXCoordinate(double startingXCoordinate) {
    return getImpl<detail::ShadingBuilding_Impl>()->setStartingXCoordinate(startingXCoordinate);
  }

  void ShadingBuilding::resetStartingXCoordinate() {
    getImpl<detail::ShadingBuilding_Impl>()->resetStartingXCoordinate();
  }

  boost::optional<double> ShadingBuilding::startingYCoordinate() const {
    return getImpl<detail::ShadingBuilding_Impl>()->startingYCoordinate();
  }

  bool ShadingBuilding::setStartingYCoordinate(double startingYCoordinate) {
    return getImpl<detail::ShadingBuilding_Impl>()->setStartingYCoordinate(startingYCoordinate);
  }

  void ShadingBuilding::resetStartingYCoordinate() {
    getImpl<detail::ShadingBuilding_Impl>()->resetStartingYCoordinate();
  }

  boost::optional<double> ShadingBuilding::startingZCoordinate() const {
    return getImpl<detail::ShadingBuilding_Impl>()->startingZCoordinate();
  }

  bool ShadingBuilding::setStartingZCoordinate(double startingZCoordinate) {
    return getImpl<detail::ShadingBuilding_Impl>()->setStartingZCoordinate(startingZCoordinate);
  }

  void ShadingBuilding::resetStartingZCoordinate() {
    getImpl<detail::ShadingBuilding_Impl>()->resetStartingZCoordinate();
  }

  boost::optional<double> ShadingBuilding::length() const {
    return getImpl<detail::ShadingBuilding_Impl>()->length();
  }

  bool ShadingBuilding::setLength(double length) {
    return getImpl<detail::ShadingBuilding_Impl>()->setLength(length);
  }

  void ShadingBuilding::resetLength() {
    getImpl<detail::ShadingBuilding_Impl>()->resetLength();
  }

  boost::optional<double> ShadingBuilding::height() const {
    return getImpl<detail::ShadingBuilding_Impl>()->height();
  }

  bool ShadingBuilding::setHeight(double height) {
    return getImpl<detail::ShadingBuilding_Impl>()->setHeight(height);
  }

  void ShadingBuilding::resetHeight() {
    getImpl<detail::ShadingBuilding_Impl>()->resetHeight();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    boost::optional<double> ShadingBuilding_Impl::azimuthAngle() const {
      return getDouble(openstudio::Shading_BuildingFields::AzimuthAngle, true);
    }

    bool ShadingBuilding_Impl::setAzimuthAngle(double azimuthAngle) {
      return setDouble(openstudio::Shading_BuildingFields::AzimuthAngle, azimuthAngle);
    }

    void ShadingBuilding_Impl::resetAzimuthAngle() {
      OS_ASSERT(setString(openstudio::Shading_BuildingFields::AzimuthAngle, ""));
    }

    double ShadingBuilding_Impl::tiltAngle() const {
      const auto value = getDouble(openstudio::Shading_BuildingFields::TiltAngle, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ShadingBuilding_Impl::isTiltAngleDefaulted() const {
      return !getDouble(openstudio::Shading_BuildingFields::TiltAngle, false);
    }

    bool ShadingBuilding_Impl::setTiltAngle(double tiltAngle) {
      return setDouble(openstudio::Shading_BuildingFields::TiltAngle, tiltAngle);
    }

    void ShadingBuilding_Impl::resetTiltAngle() {
      OS_ASSERT(setString(openstudio::Shading_BuildingFields::TiltAngle, ""));
    }

    boost::optional<double> ShadingBuilding_Impl::startingXCoordinate() const {
      return getDouble(openstudio::Shading_BuildingFields::StartingXCoordinate, true);
    }

    bool ShadingBuilding_Impl::setStartingXCoordinate(double startingXCoordinate) {
      const bool result = setDouble(openstudio::Shading_BuildingFields::StartingXCoordinate, startingXCoordinate);
      OS_ASSERT(result);
      return result;
    }

    void ShadingBuilding_Impl::resetStartingXCoordinate() {
      OS_ASSERT(setString(openstudio::Shading_BuildingFields::StartingXCoordinate, ""));
    }

    boost::optional<double> ShadingBuilding_Impl::startingYCoordinate() const {
      return getDouble(openstudio::Shading_BuildingFields::StartingYCoordinate, true);
    }

    bool ShadingBuilding_Impl::setStartingYCoordinate(double startingYCoordinate) {
      const bool result = setDouble(openstudio::Shading_BuildingFields::StartingYCoordinate, startingYCoordinate);
      OS_ASSERT(result);
      return result;
    }

    void ShadingBuilding_Impl::resetStartingYCoordinate() {
      OS_ASSERT(setString(openstudio::Shading_BuildingFields::StartingYCoordinate, ""));
    }

    boost::optional<double> ShadingBuilding_Impl::startingZCoordinate() const {
      return getDouble(openstudio::Shading_BuildingFields::StartingZCoordinate, true);
    }

    bool ShadingBuilding_Impl::setStartingZCoordinate(double startingZCoordinate) {
      const bool result = setDouble(openstudio::Shading_BuildingFields::StartingZCoordinate, startingZCoordinate);
      OS_ASSERT(result);
      return result;
    }

    void ShadingBuilding_Impl::resetStartingZCoordinate() {
      OS_ASSERT(setString(openstudio::Shading_BuildingFields::StartingZCoordinate, ""));
    }

    boost::optional<double> ShadingBuilding_Impl::length() const {
      return getDouble(openstudio::Shading_BuildingFields::Length, true);
    }

    bool ShadingBuilding_Impl::setLength(double length) {
      const bool result = setDouble(openstudio::Shading_BuildingFields::Length, length);
      OS_ASSERT(result);
      return result;
    }

    void ShadingBuilding_Impl::resetLength() {
      OS_ASSERT(setString(openstudio::Shading_BuildingFields::Length, ""));
    }

    boost::optional<double> ShadingBuilding_Impl::height() const {
      return getDouble(openstudio::Shading_BuildingFields::Height, true);
    }

    bool ShadingBuilding_Impl::setHeight(double height) {
      const bool result = setDouble(openstudio::Shading_BuildingFields::Height, height);
      OS_ASSERT(result);
      return result;
    }

    void ShadingBuilding_Impl::resetHeight() {
      OS_ASSERT(setString(openstudio::Shading_BuildingFields::Height, ""));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
