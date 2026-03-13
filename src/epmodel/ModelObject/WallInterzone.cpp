/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include "Model.hpp"
#include "ModelObject/WallInterzone.hpp"
#include "ModelObject/WallInterzone_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/Wall_Interzone_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  WallInterzone::WallInterzone(const Model& model) : ModelObject(WallInterzone::iddObjectType(), model) {}

  WallInterzone::WallInterzone(std::shared_ptr<detail::WallInterzone_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType WallInterzone::iddObjectType() {
    return IddObjectType::Wall_Interzone;
  }

  boost::optional<double> WallInterzone::azimuthAngle() const {
    return getImpl<detail::WallInterzone_Impl>()->azimuthAngle();
  }

  bool WallInterzone::setAzimuthAngle(double azimuthAngle) {
    return getImpl<detail::WallInterzone_Impl>()->setAzimuthAngle(azimuthAngle);
  }

  void WallInterzone::resetAzimuthAngle() {
    getImpl<detail::WallInterzone_Impl>()->resetAzimuthAngle();
  }

  double WallInterzone::tiltAngle() const {
    return getImpl<detail::WallInterzone_Impl>()->tiltAngle();
  }

  bool WallInterzone::isTiltAngleDefaulted() const {
    return getImpl<detail::WallInterzone_Impl>()->isTiltAngleDefaulted();
  }

  bool WallInterzone::setTiltAngle(double tiltAngle) {
    return getImpl<detail::WallInterzone_Impl>()->setTiltAngle(tiltAngle);
  }

  void WallInterzone::resetTiltAngle() {
    getImpl<detail::WallInterzone_Impl>()->resetTiltAngle();
  }

  boost::optional<double> WallInterzone::startingXCoordinate() const {
    return getImpl<detail::WallInterzone_Impl>()->startingXCoordinate();
  }

  bool WallInterzone::setStartingXCoordinate(double startingXCoordinate) {
    return getImpl<detail::WallInterzone_Impl>()->setStartingXCoordinate(startingXCoordinate);
  }

  void WallInterzone::resetStartingXCoordinate() {
    getImpl<detail::WallInterzone_Impl>()->resetStartingXCoordinate();
  }

  boost::optional<double> WallInterzone::startingYCoordinate() const {
    return getImpl<detail::WallInterzone_Impl>()->startingYCoordinate();
  }

  bool WallInterzone::setStartingYCoordinate(double startingYCoordinate) {
    return getImpl<detail::WallInterzone_Impl>()->setStartingYCoordinate(startingYCoordinate);
  }

  void WallInterzone::resetStartingYCoordinate() {
    getImpl<detail::WallInterzone_Impl>()->resetStartingYCoordinate();
  }

  boost::optional<double> WallInterzone::startingZCoordinate() const {
    return getImpl<detail::WallInterzone_Impl>()->startingZCoordinate();
  }

  bool WallInterzone::setStartingZCoordinate(double startingZCoordinate) {
    return getImpl<detail::WallInterzone_Impl>()->setStartingZCoordinate(startingZCoordinate);
  }

  void WallInterzone::resetStartingZCoordinate() {
    getImpl<detail::WallInterzone_Impl>()->resetStartingZCoordinate();
  }

  boost::optional<double> WallInterzone::length() const {
    return getImpl<detail::WallInterzone_Impl>()->length();
  }

  bool WallInterzone::setLength(double length) {
    return getImpl<detail::WallInterzone_Impl>()->setLength(length);
  }

  void WallInterzone::resetLength() {
    getImpl<detail::WallInterzone_Impl>()->resetLength();
  }

  boost::optional<double> WallInterzone::height() const {
    return getImpl<detail::WallInterzone_Impl>()->height();
  }

  bool WallInterzone::setHeight(double height) {
    return getImpl<detail::WallInterzone_Impl>()->setHeight(height);
  }

  void WallInterzone::resetHeight() {
    getImpl<detail::WallInterzone_Impl>()->resetHeight();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    boost::optional<double> WallInterzone_Impl::azimuthAngle() const {
      return getDouble(openstudio::Wall_InterzoneFields::AzimuthAngle, true);
    }

    bool WallInterzone_Impl::setAzimuthAngle(double azimuthAngle) {
      const bool result = setDouble(openstudio::Wall_InterzoneFields::AzimuthAngle, azimuthAngle);
      return result;
    }

    void WallInterzone_Impl::resetAzimuthAngle() {
      const bool result = setString(openstudio::Wall_InterzoneFields::AzimuthAngle, "");
      OS_ASSERT(result);
    }

    double WallInterzone_Impl::tiltAngle() const {
      const auto value = getDouble(openstudio::Wall_InterzoneFields::TiltAngle, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WallInterzone_Impl::isTiltAngleDefaulted() const {
      return isEmpty(openstudio::Wall_InterzoneFields::TiltAngle);
    }

    bool WallInterzone_Impl::setTiltAngle(double tiltAngle) {
      const bool result = setDouble(openstudio::Wall_InterzoneFields::TiltAngle, tiltAngle);
      return result;
    }

    void WallInterzone_Impl::resetTiltAngle() {
      const bool result = setString(openstudio::Wall_InterzoneFields::TiltAngle, "");
      OS_ASSERT(result);
    }

    boost::optional<double> WallInterzone_Impl::startingXCoordinate() const {
      return getDouble(openstudio::Wall_InterzoneFields::StartingXCoordinate, true);
    }

    bool WallInterzone_Impl::setStartingXCoordinate(double startingXCoordinate) {
      const bool result = setDouble(openstudio::Wall_InterzoneFields::StartingXCoordinate, startingXCoordinate);
      OS_ASSERT(result);
      return result;
    }

    void WallInterzone_Impl::resetStartingXCoordinate() {
      const bool result = setString(openstudio::Wall_InterzoneFields::StartingXCoordinate, "");
      OS_ASSERT(result);
    }

    boost::optional<double> WallInterzone_Impl::startingYCoordinate() const {
      return getDouble(openstudio::Wall_InterzoneFields::StartingYCoordinate, true);
    }

    bool WallInterzone_Impl::setStartingYCoordinate(double startingYCoordinate) {
      const bool result = setDouble(openstudio::Wall_InterzoneFields::StartingYCoordinate, startingYCoordinate);
      OS_ASSERT(result);
      return result;
    }

    void WallInterzone_Impl::resetStartingYCoordinate() {
      const bool result = setString(openstudio::Wall_InterzoneFields::StartingYCoordinate, "");
      OS_ASSERT(result);
    }

    boost::optional<double> WallInterzone_Impl::startingZCoordinate() const {
      return getDouble(openstudio::Wall_InterzoneFields::StartingZCoordinate, true);
    }

    bool WallInterzone_Impl::setStartingZCoordinate(double startingZCoordinate) {
      const bool result = setDouble(openstudio::Wall_InterzoneFields::StartingZCoordinate, startingZCoordinate);
      OS_ASSERT(result);
      return result;
    }

    void WallInterzone_Impl::resetStartingZCoordinate() {
      const bool result = setString(openstudio::Wall_InterzoneFields::StartingZCoordinate, "");
      OS_ASSERT(result);
    }

    boost::optional<double> WallInterzone_Impl::length() const {
      return getDouble(openstudio::Wall_InterzoneFields::Length, true);
    }

    bool WallInterzone_Impl::setLength(double length) {
      const bool result = setDouble(openstudio::Wall_InterzoneFields::Length, length);
      OS_ASSERT(result);
      return result;
    }

    void WallInterzone_Impl::resetLength() {
      const bool result = setString(openstudio::Wall_InterzoneFields::Length, "");
      OS_ASSERT(result);
    }

    boost::optional<double> WallInterzone_Impl::height() const {
      return getDouble(openstudio::Wall_InterzoneFields::Height, true);
    }

    bool WallInterzone_Impl::setHeight(double height) {
      const bool result = setDouble(openstudio::Wall_InterzoneFields::Height, height);
      OS_ASSERT(result);
      return result;
    }

    void WallInterzone_Impl::resetHeight() {
      const bool result = setString(openstudio::Wall_InterzoneFields::Height, "");
      OS_ASSERT(result);
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
