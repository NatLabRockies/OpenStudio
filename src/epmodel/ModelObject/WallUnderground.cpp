/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include "ModelObject/WallUnderground.hpp"
#include "ModelObject/WallUnderground_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/Wall_Underground_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  WallUnderground::WallUnderground(const Model& model) : ModelObject(WallUnderground::iddObjectType(), model) {}

  WallUnderground::WallUnderground(std::shared_ptr<detail::WallUnderground_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType WallUnderground::iddObjectType() {
    return IddObjectType::Wall_Underground;
  }

  boost::optional<double> WallUnderground::azimuthAngle() const {
    return getImpl<detail::WallUnderground_Impl>()->azimuthAngle();
  }

  bool WallUnderground::setAzimuthAngle(double azimuthAngle) {
    return getImpl<detail::WallUnderground_Impl>()->setAzimuthAngle(azimuthAngle);
  }

  void WallUnderground::resetAzimuthAngle() {
    getImpl<detail::WallUnderground_Impl>()->resetAzimuthAngle();
  }

  double WallUnderground::tiltAngle() const {
    return getImpl<detail::WallUnderground_Impl>()->tiltAngle();
  }

  bool WallUnderground::isTiltAngleDefaulted() const {
    return getImpl<detail::WallUnderground_Impl>()->isTiltAngleDefaulted();
  }

  bool WallUnderground::setTiltAngle(double tiltAngle) {
    return getImpl<detail::WallUnderground_Impl>()->setTiltAngle(tiltAngle);
  }

  void WallUnderground::resetTiltAngle() {
    getImpl<detail::WallUnderground_Impl>()->resetTiltAngle();
  }

  boost::optional<double> WallUnderground::startingXCoordinate() const {
    return getImpl<detail::WallUnderground_Impl>()->startingXCoordinate();
  }

  bool WallUnderground::setStartingXCoordinate(double startingXCoordinate) {
    return getImpl<detail::WallUnderground_Impl>()->setStartingXCoordinate(startingXCoordinate);
  }

  void WallUnderground::resetStartingXCoordinate() {
    getImpl<detail::WallUnderground_Impl>()->resetStartingXCoordinate();
  }

  boost::optional<double> WallUnderground::startingYCoordinate() const {
    return getImpl<detail::WallUnderground_Impl>()->startingYCoordinate();
  }

  bool WallUnderground::setStartingYCoordinate(double startingYCoordinate) {
    return getImpl<detail::WallUnderground_Impl>()->setStartingYCoordinate(startingYCoordinate);
  }

  void WallUnderground::resetStartingYCoordinate() {
    getImpl<detail::WallUnderground_Impl>()->resetStartingYCoordinate();
  }

  boost::optional<double> WallUnderground::startingZCoordinate() const {
    return getImpl<detail::WallUnderground_Impl>()->startingZCoordinate();
  }

  bool WallUnderground::setStartingZCoordinate(double startingZCoordinate) {
    return getImpl<detail::WallUnderground_Impl>()->setStartingZCoordinate(startingZCoordinate);
  }

  void WallUnderground::resetStartingZCoordinate() {
    getImpl<detail::WallUnderground_Impl>()->resetStartingZCoordinate();
  }

  boost::optional<double> WallUnderground::length() const {
    return getImpl<detail::WallUnderground_Impl>()->length();
  }

  bool WallUnderground::setLength(double length) {
    return getImpl<detail::WallUnderground_Impl>()->setLength(length);
  }

  void WallUnderground::resetLength() {
    getImpl<detail::WallUnderground_Impl>()->resetLength();
  }

  boost::optional<double> WallUnderground::height() const {
    return getImpl<detail::WallUnderground_Impl>()->height();
  }

  bool WallUnderground::setHeight(double height) {
    return getImpl<detail::WallUnderground_Impl>()->setHeight(height);
  }

  void WallUnderground::resetHeight() {
    getImpl<detail::WallUnderground_Impl>()->resetHeight();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    boost::optional<double> WallUnderground_Impl::azimuthAngle() const {
      return getDouble(openstudio::Wall_UndergroundFields::AzimuthAngle, true);
    }

    bool WallUnderground_Impl::setAzimuthAngle(double azimuthAngle) {
      const bool result = setDouble(openstudio::Wall_UndergroundFields::AzimuthAngle, azimuthAngle);
      return result;
    }

    void WallUnderground_Impl::resetAzimuthAngle() {
      const bool result = setString(openstudio::Wall_UndergroundFields::AzimuthAngle, "");
      OS_ASSERT(result);
    }

    double WallUnderground_Impl::tiltAngle() const {
      const auto value = getDouble(openstudio::Wall_UndergroundFields::TiltAngle, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WallUnderground_Impl::isTiltAngleDefaulted() const {
      return isEmpty(openstudio::Wall_UndergroundFields::TiltAngle);
    }

    bool WallUnderground_Impl::setTiltAngle(double tiltAngle) {
      const bool result = setDouble(openstudio::Wall_UndergroundFields::TiltAngle, tiltAngle);
      return result;
    }

    void WallUnderground_Impl::resetTiltAngle() {
      const bool result = setString(openstudio::Wall_UndergroundFields::TiltAngle, "");
      OS_ASSERT(result);
    }

    boost::optional<double> WallUnderground_Impl::startingXCoordinate() const {
      return getDouble(openstudio::Wall_UndergroundFields::StartingXCoordinate, true);
    }

    bool WallUnderground_Impl::setStartingXCoordinate(double startingXCoordinate) {
      const bool result = setDouble(openstudio::Wall_UndergroundFields::StartingXCoordinate, startingXCoordinate);
      OS_ASSERT(result);
      return result;
    }

    void WallUnderground_Impl::resetStartingXCoordinate() {
      const bool result = setString(openstudio::Wall_UndergroundFields::StartingXCoordinate, "");
      OS_ASSERT(result);
    }

    boost::optional<double> WallUnderground_Impl::startingYCoordinate() const {
      return getDouble(openstudio::Wall_UndergroundFields::StartingYCoordinate, true);
    }

    bool WallUnderground_Impl::setStartingYCoordinate(double startingYCoordinate) {
      const bool result = setDouble(openstudio::Wall_UndergroundFields::StartingYCoordinate, startingYCoordinate);
      OS_ASSERT(result);
      return result;
    }

    void WallUnderground_Impl::resetStartingYCoordinate() {
      const bool result = setString(openstudio::Wall_UndergroundFields::StartingYCoordinate, "");
      OS_ASSERT(result);
    }

    boost::optional<double> WallUnderground_Impl::startingZCoordinate() const {
      return getDouble(openstudio::Wall_UndergroundFields::StartingZCoordinate, true);
    }

    bool WallUnderground_Impl::setStartingZCoordinate(double startingZCoordinate) {
      const bool result = setDouble(openstudio::Wall_UndergroundFields::StartingZCoordinate, startingZCoordinate);
      OS_ASSERT(result);
      return result;
    }

    void WallUnderground_Impl::resetStartingZCoordinate() {
      const bool result = setString(openstudio::Wall_UndergroundFields::StartingZCoordinate, "");
      OS_ASSERT(result);
    }

    boost::optional<double> WallUnderground_Impl::length() const {
      return getDouble(openstudio::Wall_UndergroundFields::Length, true);
    }

    bool WallUnderground_Impl::setLength(double length) {
      const bool result = setDouble(openstudio::Wall_UndergroundFields::Length, length);
      OS_ASSERT(result);
      return result;
    }

    void WallUnderground_Impl::resetLength() {
      const bool result = setString(openstudio::Wall_UndergroundFields::Length, "");
      OS_ASSERT(result);
    }

    boost::optional<double> WallUnderground_Impl::height() const {
      return getDouble(openstudio::Wall_UndergroundFields::Height, true);
    }

    bool WallUnderground_Impl::setHeight(double height) {
      const bool result = setDouble(openstudio::Wall_UndergroundFields::Height, height);
      OS_ASSERT(result);
      return result;
    }

    void WallUnderground_Impl::resetHeight() {
      const bool result = setString(openstudio::Wall_UndergroundFields::Height, "");
      OS_ASSERT(result);
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
