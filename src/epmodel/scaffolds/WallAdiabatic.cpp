/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "WallAdiabatic.hpp"
#include "WallAdiabatic_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/Wall_Adiabatic_FieldEnums.hxx>

#include <utility>

namespace openstudio {
namespace epmodel {

  WallAdiabatic::WallAdiabatic(const Model& model) : ModelObject(WallAdiabatic::iddObjectType(), model) {}

  WallAdiabatic::WallAdiabatic(std::shared_ptr<detail::WallAdiabatic_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType WallAdiabatic::iddObjectType() {
    return IddObjectType::Wall_Adiabatic;
  }

  boost::optional<double> WallAdiabatic::azimuthAngle() const {
    return getImpl<detail::WallAdiabatic_Impl>()->azimuthAngle();
  }

  bool WallAdiabatic::setAzimuthAngle(double azimuthAngle) {
    return getImpl<detail::WallAdiabatic_Impl>()->setAzimuthAngle(azimuthAngle);
  }

  void WallAdiabatic::resetAzimuthAngle() {
    getImpl<detail::WallAdiabatic_Impl>()->resetAzimuthAngle();
  }

  double WallAdiabatic::tiltAngle() const {
    return getImpl<detail::WallAdiabatic_Impl>()->tiltAngle();
  }

  bool WallAdiabatic::isTiltAngleDefaulted() const {
    return getImpl<detail::WallAdiabatic_Impl>()->isTiltAngleDefaulted();
  }

  bool WallAdiabatic::setTiltAngle(double tiltAngle) {
    return getImpl<detail::WallAdiabatic_Impl>()->setTiltAngle(tiltAngle);
  }

  void WallAdiabatic::resetTiltAngle() {
    getImpl<detail::WallAdiabatic_Impl>()->resetTiltAngle();
  }

  boost::optional<double> WallAdiabatic::startingXCoordinate() const {
    return getImpl<detail::WallAdiabatic_Impl>()->startingXCoordinate();
  }

  bool WallAdiabatic::setStartingXCoordinate(double startingXCoordinate) {
    return getImpl<detail::WallAdiabatic_Impl>()->setStartingXCoordinate(startingXCoordinate);
  }

  void WallAdiabatic::resetStartingXCoordinate() {
    getImpl<detail::WallAdiabatic_Impl>()->resetStartingXCoordinate();
  }

  boost::optional<double> WallAdiabatic::startingYCoordinate() const {
    return getImpl<detail::WallAdiabatic_Impl>()->startingYCoordinate();
  }

  bool WallAdiabatic::setStartingYCoordinate(double startingYCoordinate) {
    return getImpl<detail::WallAdiabatic_Impl>()->setStartingYCoordinate(startingYCoordinate);
  }

  void WallAdiabatic::resetStartingYCoordinate() {
    getImpl<detail::WallAdiabatic_Impl>()->resetStartingYCoordinate();
  }

  boost::optional<double> WallAdiabatic::startingZCoordinate() const {
    return getImpl<detail::WallAdiabatic_Impl>()->startingZCoordinate();
  }

  bool WallAdiabatic::setStartingZCoordinate(double startingZCoordinate) {
    return getImpl<detail::WallAdiabatic_Impl>()->setStartingZCoordinate(startingZCoordinate);
  }

  void WallAdiabatic::resetStartingZCoordinate() {
    getImpl<detail::WallAdiabatic_Impl>()->resetStartingZCoordinate();
  }

  boost::optional<double> WallAdiabatic::length() const {
    return getImpl<detail::WallAdiabatic_Impl>()->length();
  }

  bool WallAdiabatic::setLength(double length) {
    return getImpl<detail::WallAdiabatic_Impl>()->setLength(length);
  }

  void WallAdiabatic::resetLength() {
    getImpl<detail::WallAdiabatic_Impl>()->resetLength();
  }

  boost::optional<double> WallAdiabatic::height() const {
    return getImpl<detail::WallAdiabatic_Impl>()->height();
  }

  bool WallAdiabatic::setHeight(double height) {
    return getImpl<detail::WallAdiabatic_Impl>()->setHeight(height);
  }

  void WallAdiabatic::resetHeight() {
    getImpl<detail::WallAdiabatic_Impl>()->resetHeight();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    boost::optional<double> WallAdiabatic_Impl::azimuthAngle() const {
      return getDouble(openstudio::Wall_AdiabaticFields::AzimuthAngle, true);
    }

    bool WallAdiabatic_Impl::setAzimuthAngle(double azimuthAngle) {
      const bool result = setDouble(openstudio::Wall_AdiabaticFields::AzimuthAngle, azimuthAngle);
      return result;
    }

    void WallAdiabatic_Impl::resetAzimuthAngle() {
      const bool result = setString(openstudio::Wall_AdiabaticFields::AzimuthAngle, "");
      OS_ASSERT(result);
    }

    double WallAdiabatic_Impl::tiltAngle() const {
      const auto value = getDouble(openstudio::Wall_AdiabaticFields::TiltAngle, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WallAdiabatic_Impl::isTiltAngleDefaulted() const {
      return isEmpty(openstudio::Wall_AdiabaticFields::TiltAngle);
    }

    bool WallAdiabatic_Impl::setTiltAngle(double tiltAngle) {
      const bool result = setDouble(openstudio::Wall_AdiabaticFields::TiltAngle, tiltAngle);
      return result;
    }

    void WallAdiabatic_Impl::resetTiltAngle() {
      const bool result = setString(openstudio::Wall_AdiabaticFields::TiltAngle, "");
      OS_ASSERT(result);
    }

    boost::optional<double> WallAdiabatic_Impl::startingXCoordinate() const {
      return getDouble(openstudio::Wall_AdiabaticFields::StartingXCoordinate, true);
    }

    bool WallAdiabatic_Impl::setStartingXCoordinate(double startingXCoordinate) {
      const bool result = setDouble(openstudio::Wall_AdiabaticFields::StartingXCoordinate, startingXCoordinate);
      OS_ASSERT(result);
      return result;
    }

    void WallAdiabatic_Impl::resetStartingXCoordinate() {
      const bool result = setString(openstudio::Wall_AdiabaticFields::StartingXCoordinate, "");
      OS_ASSERT(result);
    }

    boost::optional<double> WallAdiabatic_Impl::startingYCoordinate() const {
      return getDouble(openstudio::Wall_AdiabaticFields::StartingYCoordinate, true);
    }

    bool WallAdiabatic_Impl::setStartingYCoordinate(double startingYCoordinate) {
      const bool result = setDouble(openstudio::Wall_AdiabaticFields::StartingYCoordinate, startingYCoordinate);
      OS_ASSERT(result);
      return result;
    }

    void WallAdiabatic_Impl::resetStartingYCoordinate() {
      const bool result = setString(openstudio::Wall_AdiabaticFields::StartingYCoordinate, "");
      OS_ASSERT(result);
    }

    boost::optional<double> WallAdiabatic_Impl::startingZCoordinate() const {
      return getDouble(openstudio::Wall_AdiabaticFields::StartingZCoordinate, true);
    }

    bool WallAdiabatic_Impl::setStartingZCoordinate(double startingZCoordinate) {
      const bool result = setDouble(openstudio::Wall_AdiabaticFields::StartingZCoordinate, startingZCoordinate);
      OS_ASSERT(result);
      return result;
    }

    void WallAdiabatic_Impl::resetStartingZCoordinate() {
      const bool result = setString(openstudio::Wall_AdiabaticFields::StartingZCoordinate, "");
      OS_ASSERT(result);
    }

    boost::optional<double> WallAdiabatic_Impl::length() const {
      return getDouble(openstudio::Wall_AdiabaticFields::Length, true);
    }

    bool WallAdiabatic_Impl::setLength(double length) {
      const bool result = setDouble(openstudio::Wall_AdiabaticFields::Length, length);
      OS_ASSERT(result);
      return result;
    }

    void WallAdiabatic_Impl::resetLength() {
      const bool result = setString(openstudio::Wall_AdiabaticFields::Length, "");
      OS_ASSERT(result);
    }

    boost::optional<double> WallAdiabatic_Impl::height() const {
      return getDouble(openstudio::Wall_AdiabaticFields::Height, true);
    }

    bool WallAdiabatic_Impl::setHeight(double height) {
      const bool result = setDouble(openstudio::Wall_AdiabaticFields::Height, height);
      OS_ASSERT(result);
      return result;
    }

    void WallAdiabatic_Impl::resetHeight() {
      const bool result = setString(openstudio::Wall_AdiabaticFields::Height, "");
      OS_ASSERT(result);
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
