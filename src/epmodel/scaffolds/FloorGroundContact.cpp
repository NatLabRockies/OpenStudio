/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "FloorGroundContact.hpp"
#include "FloorGroundContact_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/Floor_GroundContact_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  FloorGroundContact::FloorGroundContact(const Model& model) : ModelObject(FloorGroundContact::iddObjectType(), model) {}

  FloorGroundContact::FloorGroundContact(std::shared_ptr<detail::FloorGroundContact_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType FloorGroundContact::iddObjectType() {
    return IddObjectType::Floor_GroundContact;
  }

  boost::optional<double> FloorGroundContact::azimuthAngle() const {
    return getImpl<detail::FloorGroundContact_Impl>()->azimuthAngle();
  }

  bool FloorGroundContact::setAzimuthAngle(double azimuthAngle) {
    return getImpl<detail::FloorGroundContact_Impl>()->setAzimuthAngle(azimuthAngle);
  }

  void FloorGroundContact::resetAzimuthAngle() {
    getImpl<detail::FloorGroundContact_Impl>()->resetAzimuthAngle();
  }

  double FloorGroundContact::tiltAngle() const {
    return getImpl<detail::FloorGroundContact_Impl>()->tiltAngle();
  }

  bool FloorGroundContact::isTiltAngleDefaulted() const {
    return getImpl<detail::FloorGroundContact_Impl>()->isTiltAngleDefaulted();
  }

  bool FloorGroundContact::setTiltAngle(double tiltAngle) {
    return getImpl<detail::FloorGroundContact_Impl>()->setTiltAngle(tiltAngle);
  }

  void FloorGroundContact::resetTiltAngle() {
    getImpl<detail::FloorGroundContact_Impl>()->resetTiltAngle();
  }

  boost::optional<double> FloorGroundContact::startingXCoordinate() const {
    return getImpl<detail::FloorGroundContact_Impl>()->startingXCoordinate();
  }

  bool FloorGroundContact::setStartingXCoordinate(double startingXCoordinate) {
    return getImpl<detail::FloorGroundContact_Impl>()->setStartingXCoordinate(startingXCoordinate);
  }

  void FloorGroundContact::resetStartingXCoordinate() {
    getImpl<detail::FloorGroundContact_Impl>()->resetStartingXCoordinate();
  }

  boost::optional<double> FloorGroundContact::startingYCoordinate() const {
    return getImpl<detail::FloorGroundContact_Impl>()->startingYCoordinate();
  }

  bool FloorGroundContact::setStartingYCoordinate(double startingYCoordinate) {
    return getImpl<detail::FloorGroundContact_Impl>()->setStartingYCoordinate(startingYCoordinate);
  }

  void FloorGroundContact::resetStartingYCoordinate() {
    getImpl<detail::FloorGroundContact_Impl>()->resetStartingYCoordinate();
  }

  boost::optional<double> FloorGroundContact::startingZCoordinate() const {
    return getImpl<detail::FloorGroundContact_Impl>()->startingZCoordinate();
  }

  bool FloorGroundContact::setStartingZCoordinate(double startingZCoordinate) {
    return getImpl<detail::FloorGroundContact_Impl>()->setStartingZCoordinate(startingZCoordinate);
  }

  void FloorGroundContact::resetStartingZCoordinate() {
    getImpl<detail::FloorGroundContact_Impl>()->resetStartingZCoordinate();
  }

  boost::optional<double> FloorGroundContact::length() const {
    return getImpl<detail::FloorGroundContact_Impl>()->length();
  }

  bool FloorGroundContact::setLength(double length) {
    return getImpl<detail::FloorGroundContact_Impl>()->setLength(length);
  }

  void FloorGroundContact::resetLength() {
    getImpl<detail::FloorGroundContact_Impl>()->resetLength();
  }

  boost::optional<double> FloorGroundContact::width() const {
    return getImpl<detail::FloorGroundContact_Impl>()->width();
  }

  bool FloorGroundContact::setWidth(double width) {
    return getImpl<detail::FloorGroundContact_Impl>()->setWidth(width);
  }

  void FloorGroundContact::resetWidth() {
    getImpl<detail::FloorGroundContact_Impl>()->resetWidth();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    boost::optional<double> FloorGroundContact_Impl::azimuthAngle() const {
      return getDouble(openstudio::Floor_GroundContactFields::AzimuthAngle, true);
    }

    bool FloorGroundContact_Impl::setAzimuthAngle(double azimuthAngle) {
      return setDouble(openstudio::Floor_GroundContactFields::AzimuthAngle, azimuthAngle);
    }

    void FloorGroundContact_Impl::resetAzimuthAngle() {
      OS_ASSERT(setString(openstudio::Floor_GroundContactFields::AzimuthAngle, ""));
    }

    double FloorGroundContact_Impl::tiltAngle() const {
      const auto value = getDouble(openstudio::Floor_GroundContactFields::TiltAngle, true);
      OS_ASSERT(value);
      return *value;
    }

    bool FloorGroundContact_Impl::isTiltAngleDefaulted() const {
      return isEmpty(openstudio::Floor_GroundContactFields::TiltAngle);
    }

    bool FloorGroundContact_Impl::setTiltAngle(double tiltAngle) {
      return setDouble(openstudio::Floor_GroundContactFields::TiltAngle, tiltAngle);
    }

    void FloorGroundContact_Impl::resetTiltAngle() {
      OS_ASSERT(setString(openstudio::Floor_GroundContactFields::TiltAngle, ""));
    }

    boost::optional<double> FloorGroundContact_Impl::startingXCoordinate() const {
      return getDouble(openstudio::Floor_GroundContactFields::StartingXCoordinate, true);
    }

    bool FloorGroundContact_Impl::setStartingXCoordinate(double startingXCoordinate) {
      const bool result = setDouble(openstudio::Floor_GroundContactFields::StartingXCoordinate, startingXCoordinate);
      OS_ASSERT(result);
      return result;
    }

    void FloorGroundContact_Impl::resetStartingXCoordinate() {
      OS_ASSERT(setString(openstudio::Floor_GroundContactFields::StartingXCoordinate, ""));
    }

    boost::optional<double> FloorGroundContact_Impl::startingYCoordinate() const {
      return getDouble(openstudio::Floor_GroundContactFields::StartingYCoordinate, true);
    }

    bool FloorGroundContact_Impl::setStartingYCoordinate(double startingYCoordinate) {
      const bool result = setDouble(openstudio::Floor_GroundContactFields::StartingYCoordinate, startingYCoordinate);
      OS_ASSERT(result);
      return result;
    }

    void FloorGroundContact_Impl::resetStartingYCoordinate() {
      OS_ASSERT(setString(openstudio::Floor_GroundContactFields::StartingYCoordinate, ""));
    }

    boost::optional<double> FloorGroundContact_Impl::startingZCoordinate() const {
      return getDouble(openstudio::Floor_GroundContactFields::StartingZCoordinate, true);
    }

    bool FloorGroundContact_Impl::setStartingZCoordinate(double startingZCoordinate) {
      const bool result = setDouble(openstudio::Floor_GroundContactFields::StartingZCoordinate, startingZCoordinate);
      OS_ASSERT(result);
      return result;
    }

    void FloorGroundContact_Impl::resetStartingZCoordinate() {
      OS_ASSERT(setString(openstudio::Floor_GroundContactFields::StartingZCoordinate, ""));
    }

    boost::optional<double> FloorGroundContact_Impl::length() const {
      return getDouble(openstudio::Floor_GroundContactFields::Length, true);
    }

    bool FloorGroundContact_Impl::setLength(double length) {
      const bool result = setDouble(openstudio::Floor_GroundContactFields::Length, length);
      OS_ASSERT(result);
      return result;
    }

    void FloorGroundContact_Impl::resetLength() {
      OS_ASSERT(setString(openstudio::Floor_GroundContactFields::Length, ""));
    }

    boost::optional<double> FloorGroundContact_Impl::width() const {
      return getDouble(openstudio::Floor_GroundContactFields::Width, true);
    }

    bool FloorGroundContact_Impl::setWidth(double width) {
      const bool result = setDouble(openstudio::Floor_GroundContactFields::Width, width);
      OS_ASSERT(result);
      return result;
    }

    void FloorGroundContact_Impl::resetWidth() {
      OS_ASSERT(setString(openstudio::Floor_GroundContactFields::Width, ""));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
