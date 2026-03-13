/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include "Model.hpp"
#include "ModelObject/WallExterior.hpp"
#include "ModelObject/WallExterior_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/Wall_Exterior_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  WallExterior::WallExterior(const Model& model) : ModelObject(WallExterior::iddObjectType(), model) {}

  WallExterior::WallExterior(std::shared_ptr<detail::WallExterior_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType WallExterior::iddObjectType() {
    return IddObjectType::Wall_Exterior;
  }

  boost::optional<double> WallExterior::azimuthAngle() const {
    return getImpl<detail::WallExterior_Impl>()->azimuthAngle();
  }

  bool WallExterior::setAzimuthAngle(double azimuthAngle) {
    return getImpl<detail::WallExterior_Impl>()->setAzimuthAngle(azimuthAngle);
  }

  void WallExterior::resetAzimuthAngle() {
    getImpl<detail::WallExterior_Impl>()->resetAzimuthAngle();
  }

  double WallExterior::tiltAngle() const {
    return getImpl<detail::WallExterior_Impl>()->tiltAngle();
  }

  bool WallExterior::isTiltAngleDefaulted() const {
    return getImpl<detail::WallExterior_Impl>()->isTiltAngleDefaulted();
  }

  bool WallExterior::setTiltAngle(double tiltAngle) {
    return getImpl<detail::WallExterior_Impl>()->setTiltAngle(tiltAngle);
  }

  void WallExterior::resetTiltAngle() {
    getImpl<detail::WallExterior_Impl>()->resetTiltAngle();
  }

  boost::optional<double> WallExterior::startingXCoordinate() const {
    return getImpl<detail::WallExterior_Impl>()->startingXCoordinate();
  }

  bool WallExterior::setStartingXCoordinate(double startingXCoordinate) {
    return getImpl<detail::WallExterior_Impl>()->setStartingXCoordinate(startingXCoordinate);
  }

  void WallExterior::resetStartingXCoordinate() {
    getImpl<detail::WallExterior_Impl>()->resetStartingXCoordinate();
  }

  boost::optional<double> WallExterior::startingYCoordinate() const {
    return getImpl<detail::WallExterior_Impl>()->startingYCoordinate();
  }

  bool WallExterior::setStartingYCoordinate(double startingYCoordinate) {
    return getImpl<detail::WallExterior_Impl>()->setStartingYCoordinate(startingYCoordinate);
  }

  void WallExterior::resetStartingYCoordinate() {
    getImpl<detail::WallExterior_Impl>()->resetStartingYCoordinate();
  }

  boost::optional<double> WallExterior::startingZCoordinate() const {
    return getImpl<detail::WallExterior_Impl>()->startingZCoordinate();
  }

  bool WallExterior::setStartingZCoordinate(double startingZCoordinate) {
    return getImpl<detail::WallExterior_Impl>()->setStartingZCoordinate(startingZCoordinate);
  }

  void WallExterior::resetStartingZCoordinate() {
    getImpl<detail::WallExterior_Impl>()->resetStartingZCoordinate();
  }

  boost::optional<double> WallExterior::length() const {
    return getImpl<detail::WallExterior_Impl>()->length();
  }

  bool WallExterior::setLength(double length) {
    return getImpl<detail::WallExterior_Impl>()->setLength(length);
  }

  void WallExterior::resetLength() {
    getImpl<detail::WallExterior_Impl>()->resetLength();
  }

  boost::optional<double> WallExterior::height() const {
    return getImpl<detail::WallExterior_Impl>()->height();
  }

  bool WallExterior::setHeight(double height) {
    return getImpl<detail::WallExterior_Impl>()->setHeight(height);
  }

  void WallExterior::resetHeight() {
    getImpl<detail::WallExterior_Impl>()->resetHeight();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    boost::optional<double> WallExterior_Impl::azimuthAngle() const {
      return getDouble(openstudio::Wall_ExteriorFields::AzimuthAngle, true);
    }

    bool WallExterior_Impl::setAzimuthAngle(double azimuthAngle) {
      const bool result = setDouble(openstudio::Wall_ExteriorFields::AzimuthAngle, azimuthAngle);
      return result;
    }

    void WallExterior_Impl::resetAzimuthAngle() {
      const bool result = setString(openstudio::Wall_ExteriorFields::AzimuthAngle, "");
      OS_ASSERT(result);
    }

    double WallExterior_Impl::tiltAngle() const {
      const auto value = getDouble(openstudio::Wall_ExteriorFields::TiltAngle, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WallExterior_Impl::isTiltAngleDefaulted() const {
      return isEmpty(openstudio::Wall_ExteriorFields::TiltAngle);
    }

    bool WallExterior_Impl::setTiltAngle(double tiltAngle) {
      const bool result = setDouble(openstudio::Wall_ExteriorFields::TiltAngle, tiltAngle);
      return result;
    }

    void WallExterior_Impl::resetTiltAngle() {
      const bool result = setString(openstudio::Wall_ExteriorFields::TiltAngle, "");
      OS_ASSERT(result);
    }

    boost::optional<double> WallExterior_Impl::startingXCoordinate() const {
      return getDouble(openstudio::Wall_ExteriorFields::StartingXCoordinate, true);
    }

    bool WallExterior_Impl::setStartingXCoordinate(double startingXCoordinate) {
      const bool result = setDouble(openstudio::Wall_ExteriorFields::StartingXCoordinate, startingXCoordinate);
      OS_ASSERT(result);
      return result;
    }

    void WallExterior_Impl::resetStartingXCoordinate() {
      const bool result = setString(openstudio::Wall_ExteriorFields::StartingXCoordinate, "");
      OS_ASSERT(result);
    }

    boost::optional<double> WallExterior_Impl::startingYCoordinate() const {
      return getDouble(openstudio::Wall_ExteriorFields::StartingYCoordinate, true);
    }

    bool WallExterior_Impl::setStartingYCoordinate(double startingYCoordinate) {
      const bool result = setDouble(openstudio::Wall_ExteriorFields::StartingYCoordinate, startingYCoordinate);
      OS_ASSERT(result);
      return result;
    }

    void WallExterior_Impl::resetStartingYCoordinate() {
      const bool result = setString(openstudio::Wall_ExteriorFields::StartingYCoordinate, "");
      OS_ASSERT(result);
    }

    boost::optional<double> WallExterior_Impl::startingZCoordinate() const {
      return getDouble(openstudio::Wall_ExteriorFields::StartingZCoordinate, true);
    }

    bool WallExterior_Impl::setStartingZCoordinate(double startingZCoordinate) {
      const bool result = setDouble(openstudio::Wall_ExteriorFields::StartingZCoordinate, startingZCoordinate);
      OS_ASSERT(result);
      return result;
    }

    void WallExterior_Impl::resetStartingZCoordinate() {
      const bool result = setString(openstudio::Wall_ExteriorFields::StartingZCoordinate, "");
      OS_ASSERT(result);
    }

    boost::optional<double> WallExterior_Impl::length() const {
      return getDouble(openstudio::Wall_ExteriorFields::Length, true);
    }

    bool WallExterior_Impl::setLength(double length) {
      const bool result = setDouble(openstudio::Wall_ExteriorFields::Length, length);
      OS_ASSERT(result);
      return result;
    }

    void WallExterior_Impl::resetLength() {
      const bool result = setString(openstudio::Wall_ExteriorFields::Length, "");
      OS_ASSERT(result);
    }

    boost::optional<double> WallExterior_Impl::height() const {
      return getDouble(openstudio::Wall_ExteriorFields::Height, true);
    }

    bool WallExterior_Impl::setHeight(double height) {
      const bool result = setDouble(openstudio::Wall_ExteriorFields::Height, height);
      OS_ASSERT(result);
      return result;
    }

    void WallExterior_Impl::resetHeight() {
      const bool result = setString(openstudio::Wall_ExteriorFields::Height, "");
      OS_ASSERT(result);
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
