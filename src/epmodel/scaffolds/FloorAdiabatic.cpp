/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "FloorAdiabatic.hpp"
#include "FloorAdiabatic_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/Floor_Adiabatic_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  FloorAdiabatic::FloorAdiabatic(const Model& model) : ModelObject(FloorAdiabatic::iddObjectType(), model) {}

  FloorAdiabatic::FloorAdiabatic(std::shared_ptr<detail::FloorAdiabatic_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType FloorAdiabatic::iddObjectType() {
    return IddObjectType::Floor_Adiabatic;
  }

  // AzimuthAngle
  boost::optional<double> FloorAdiabatic::azimuthAngle() const {
    return getImpl<detail::FloorAdiabatic_Impl>()->azimuthAngle();
  }

  bool FloorAdiabatic::setAzimuthAngle(double azimuthAngle) {
    return getImpl<detail::FloorAdiabatic_Impl>()->setAzimuthAngle(azimuthAngle);
  }

  void FloorAdiabatic::resetAzimuthAngle() {
    getImpl<detail::FloorAdiabatic_Impl>()->resetAzimuthAngle();
  }

  // TiltAngle
  double FloorAdiabatic::tiltAngle() const {
    return getImpl<detail::FloorAdiabatic_Impl>()->tiltAngle();
  }

  bool FloorAdiabatic::isTiltAngleDefaulted() const {
    return getImpl<detail::FloorAdiabatic_Impl>()->isTiltAngleDefaulted();
  }

  bool FloorAdiabatic::setTiltAngle(double tiltAngle) {
    return getImpl<detail::FloorAdiabatic_Impl>()->setTiltAngle(tiltAngle);
  }

  void FloorAdiabatic::resetTiltAngle() {
    getImpl<detail::FloorAdiabatic_Impl>()->resetTiltAngle();
  }

  // StartingXCoordinate
  boost::optional<double> FloorAdiabatic::startingXCoordinate() const {
    return getImpl<detail::FloorAdiabatic_Impl>()->startingXCoordinate();
  }

  bool FloorAdiabatic::setStartingXCoordinate(double startingXCoordinate) {
    return getImpl<detail::FloorAdiabatic_Impl>()->setStartingXCoordinate(startingXCoordinate);
  }

  void FloorAdiabatic::resetStartingXCoordinate() {
    getImpl<detail::FloorAdiabatic_Impl>()->resetStartingXCoordinate();
  }

  // StartingYCoordinate
  boost::optional<double> FloorAdiabatic::startingYCoordinate() const {
    return getImpl<detail::FloorAdiabatic_Impl>()->startingYCoordinate();
  }

  bool FloorAdiabatic::setStartingYCoordinate(double startingYCoordinate) {
    return getImpl<detail::FloorAdiabatic_Impl>()->setStartingYCoordinate(startingYCoordinate);
  }

  void FloorAdiabatic::resetStartingYCoordinate() {
    getImpl<detail::FloorAdiabatic_Impl>()->resetStartingYCoordinate();
  }

  // StartingZCoordinate
  boost::optional<double> FloorAdiabatic::startingZCoordinate() const {
    return getImpl<detail::FloorAdiabatic_Impl>()->startingZCoordinate();
  }

  bool FloorAdiabatic::setStartingZCoordinate(double startingZCoordinate) {
    return getImpl<detail::FloorAdiabatic_Impl>()->setStartingZCoordinate(startingZCoordinate);
  }

  void FloorAdiabatic::resetStartingZCoordinate() {
    getImpl<detail::FloorAdiabatic_Impl>()->resetStartingZCoordinate();
  }

  // Length
  boost::optional<double> FloorAdiabatic::length() const {
    return getImpl<detail::FloorAdiabatic_Impl>()->length();
  }

  bool FloorAdiabatic::setLength(double length) {
    return getImpl<detail::FloorAdiabatic_Impl>()->setLength(length);
  }

  void FloorAdiabatic::resetLength() {
    getImpl<detail::FloorAdiabatic_Impl>()->resetLength();
  }

  // Width
  boost::optional<double> FloorAdiabatic::width() const {
    return getImpl<detail::FloorAdiabatic_Impl>()->width();
  }

  bool FloorAdiabatic::setWidth(double width) {
    return getImpl<detail::FloorAdiabatic_Impl>()->setWidth(width);
  }

  void FloorAdiabatic::resetWidth() {
    getImpl<detail::FloorAdiabatic_Impl>()->resetWidth();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    // AzimuthAngle
    boost::optional<double> FloorAdiabatic_Impl::azimuthAngle() const {
      return getDouble(openstudio::Floor_AdiabaticFields::AzimuthAngle, true);
    }

    bool FloorAdiabatic_Impl::setAzimuthAngle(double azimuthAngle) {
      return setDouble(openstudio::Floor_AdiabaticFields::AzimuthAngle, azimuthAngle);
    }

    void FloorAdiabatic_Impl::resetAzimuthAngle() {
      OS_ASSERT(setString(openstudio::Floor_AdiabaticFields::AzimuthAngle, ""));
    }

    // TiltAngle
    double FloorAdiabatic_Impl::tiltAngle() const {
      const auto value = getDouble(openstudio::Floor_AdiabaticFields::TiltAngle, true);
      OS_ASSERT(value);
      return *value;
    }

    bool FloorAdiabatic_Impl::isTiltAngleDefaulted() const {
      return isEmpty(openstudio::Floor_AdiabaticFields::TiltAngle);
    }

    bool FloorAdiabatic_Impl::setTiltAngle(double tiltAngle) {
      return setDouble(openstudio::Floor_AdiabaticFields::TiltAngle, tiltAngle);
    }

    void FloorAdiabatic_Impl::resetTiltAngle() {
      OS_ASSERT(setString(openstudio::Floor_AdiabaticFields::TiltAngle, ""));
    }

    // StartingXCoordinate
    boost::optional<double> FloorAdiabatic_Impl::startingXCoordinate() const {
      return getDouble(openstudio::Floor_AdiabaticFields::StartingXCoordinate, true);
    }

    bool FloorAdiabatic_Impl::setStartingXCoordinate(double startingXCoordinate) {
      const bool result = setDouble(openstudio::Floor_AdiabaticFields::StartingXCoordinate, startingXCoordinate);
      OS_ASSERT(result);
      return result;
    }

    void FloorAdiabatic_Impl::resetStartingXCoordinate() {
      OS_ASSERT(setString(openstudio::Floor_AdiabaticFields::StartingXCoordinate, ""));
    }

    // StartingYCoordinate
    boost::optional<double> FloorAdiabatic_Impl::startingYCoordinate() const {
      return getDouble(openstudio::Floor_AdiabaticFields::StartingYCoordinate, true);
    }

    bool FloorAdiabatic_Impl::setStartingYCoordinate(double startingYCoordinate) {
      const bool result = setDouble(openstudio::Floor_AdiabaticFields::StartingYCoordinate, startingYCoordinate);
      OS_ASSERT(result);
      return result;
    }

    void FloorAdiabatic_Impl::resetStartingYCoordinate() {
      OS_ASSERT(setString(openstudio::Floor_AdiabaticFields::StartingYCoordinate, ""));
    }

    // StartingZCoordinate
    boost::optional<double> FloorAdiabatic_Impl::startingZCoordinate() const {
      return getDouble(openstudio::Floor_AdiabaticFields::StartingZCoordinate, true);
    }

    bool FloorAdiabatic_Impl::setStartingZCoordinate(double startingZCoordinate) {
      const bool result = setDouble(openstudio::Floor_AdiabaticFields::StartingZCoordinate, startingZCoordinate);
      OS_ASSERT(result);
      return result;
    }

    void FloorAdiabatic_Impl::resetStartingZCoordinate() {
      OS_ASSERT(setString(openstudio::Floor_AdiabaticFields::StartingZCoordinate, ""));
    }

    // Length
    boost::optional<double> FloorAdiabatic_Impl::length() const {
      return getDouble(openstudio::Floor_AdiabaticFields::Length, true);
    }

    bool FloorAdiabatic_Impl::setLength(double length) {
      const bool result = setDouble(openstudio::Floor_AdiabaticFields::Length, length);
      OS_ASSERT(result);
      return result;
    }

    void FloorAdiabatic_Impl::resetLength() {
      OS_ASSERT(setString(openstudio::Floor_AdiabaticFields::Length, ""));
    }

    // Width
    boost::optional<double> FloorAdiabatic_Impl::width() const {
      return getDouble(openstudio::Floor_AdiabaticFields::Width, true);
    }

    bool FloorAdiabatic_Impl::setWidth(double width) {
      const bool result = setDouble(openstudio::Floor_AdiabaticFields::Width, width);
      OS_ASSERT(result);
      return result;
    }

    void FloorAdiabatic_Impl::resetWidth() {
      OS_ASSERT(setString(openstudio::Floor_AdiabaticFields::Width, ""));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
