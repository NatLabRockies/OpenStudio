/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include "Roof.hpp"
#include "Roof_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/Roof_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  Roof::Roof(const Model& model) : ModelObject(Roof::iddObjectType(), model) {}

  Roof::Roof(std::shared_ptr<detail::Roof_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType Roof::iddObjectType() {
    return IddObjectType::Roof;
  }

  boost::optional<double> Roof::azimuthAngle() const {
    return getImpl<detail::Roof_Impl>()->azimuthAngle();
  }

  bool Roof::setAzimuthAngle(double azimuthAngle) {
    return getImpl<detail::Roof_Impl>()->setAzimuthAngle(azimuthAngle);
  }

  void Roof::resetAzimuthAngle() {
    getImpl<detail::Roof_Impl>()->resetAzimuthAngle();
  }

  double Roof::tiltAngle() const {
    return getImpl<detail::Roof_Impl>()->tiltAngle();
  }

  bool Roof::isTiltAngleDefaulted() const {
    return getImpl<detail::Roof_Impl>()->isTiltAngleDefaulted();
  }

  bool Roof::setTiltAngle(double tiltAngle) {
    return getImpl<detail::Roof_Impl>()->setTiltAngle(tiltAngle);
  }

  void Roof::resetTiltAngle() {
    getImpl<detail::Roof_Impl>()->resetTiltAngle();
  }

  boost::optional<double> Roof::startingXCoordinate() const {
    return getImpl<detail::Roof_Impl>()->startingXCoordinate();
  }

  bool Roof::setStartingXCoordinate(double startingXCoordinate) {
    return getImpl<detail::Roof_Impl>()->setStartingXCoordinate(startingXCoordinate);
  }

  void Roof::resetStartingXCoordinate() {
    getImpl<detail::Roof_Impl>()->resetStartingXCoordinate();
  }

  boost::optional<double> Roof::startingYCoordinate() const {
    return getImpl<detail::Roof_Impl>()->startingYCoordinate();
  }

  bool Roof::setStartingYCoordinate(double startingYCoordinate) {
    return getImpl<detail::Roof_Impl>()->setStartingYCoordinate(startingYCoordinate);
  }

  void Roof::resetStartingYCoordinate() {
    getImpl<detail::Roof_Impl>()->resetStartingYCoordinate();
  }

  boost::optional<double> Roof::startingZCoordinate() const {
    return getImpl<detail::Roof_Impl>()->startingZCoordinate();
  }

  bool Roof::setStartingZCoordinate(double startingZCoordinate) {
    return getImpl<detail::Roof_Impl>()->setStartingZCoordinate(startingZCoordinate);
  }

  void Roof::resetStartingZCoordinate() {
    getImpl<detail::Roof_Impl>()->resetStartingZCoordinate();
  }

  boost::optional<double> Roof::length() const {
    return getImpl<detail::Roof_Impl>()->length();
  }

  bool Roof::setLength(double length) {
    return getImpl<detail::Roof_Impl>()->setLength(length);
  }

  void Roof::resetLength() {
    getImpl<detail::Roof_Impl>()->resetLength();
  }

  boost::optional<double> Roof::width() const {
    return getImpl<detail::Roof_Impl>()->width();
  }

  bool Roof::setWidth(double width) {
    return getImpl<detail::Roof_Impl>()->setWidth(width);
  }

  void Roof::resetWidth() {
    getImpl<detail::Roof_Impl>()->resetWidth();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    boost::optional<double> Roof_Impl::azimuthAngle() const {
      return getDouble(openstudio::RoofFields::AzimuthAngle, true);
    }

    bool Roof_Impl::setAzimuthAngle(double azimuthAngle) {
      return setDouble(openstudio::RoofFields::AzimuthAngle, azimuthAngle);
    }

    void Roof_Impl::resetAzimuthAngle() {
      OS_ASSERT(setString(openstudio::RoofFields::AzimuthAngle, ""));
    }

    double Roof_Impl::tiltAngle() const {
      const auto value = getDouble(openstudio::RoofFields::TiltAngle, true);
      OS_ASSERT(value);
      return *value;
    }

    bool Roof_Impl::isTiltAngleDefaulted() const {
      return isEmpty(openstudio::RoofFields::TiltAngle);
    }

    bool Roof_Impl::setTiltAngle(double tiltAngle) {
      return setDouble(openstudio::RoofFields::TiltAngle, tiltAngle);
    }

    void Roof_Impl::resetTiltAngle() {
      OS_ASSERT(setString(openstudio::RoofFields::TiltAngle, ""));
    }

    boost::optional<double> Roof_Impl::startingXCoordinate() const {
      return getDouble(openstudio::RoofFields::StartingXCoordinate, true);
    }

    bool Roof_Impl::setStartingXCoordinate(double startingXCoordinate) {
      return setDouble(openstudio::RoofFields::StartingXCoordinate, startingXCoordinate);
    }

    void Roof_Impl::resetStartingXCoordinate() {
      OS_ASSERT(setString(openstudio::RoofFields::StartingXCoordinate, ""));
    }

    boost::optional<double> Roof_Impl::startingYCoordinate() const {
      return getDouble(openstudio::RoofFields::StartingYCoordinate, true);
    }

    bool Roof_Impl::setStartingYCoordinate(double startingYCoordinate) {
      return setDouble(openstudio::RoofFields::StartingYCoordinate, startingYCoordinate);
    }

    void Roof_Impl::resetStartingYCoordinate() {
      OS_ASSERT(setString(openstudio::RoofFields::StartingYCoordinate, ""));
    }

    boost::optional<double> Roof_Impl::startingZCoordinate() const {
      return getDouble(openstudio::RoofFields::StartingZCoordinate, true);
    }

    bool Roof_Impl::setStartingZCoordinate(double startingZCoordinate) {
      return setDouble(openstudio::RoofFields::StartingZCoordinate, startingZCoordinate);
    }

    void Roof_Impl::resetStartingZCoordinate() {
      OS_ASSERT(setString(openstudio::RoofFields::StartingZCoordinate, ""));
    }

    boost::optional<double> Roof_Impl::length() const {
      return getDouble(openstudio::RoofFields::Length, true);
    }

    bool Roof_Impl::setLength(double length) {
      return setDouble(openstudio::RoofFields::Length, length);
    }

    void Roof_Impl::resetLength() {
      OS_ASSERT(setString(openstudio::RoofFields::Length, ""));
    }

    boost::optional<double> Roof_Impl::width() const {
      return getDouble(openstudio::RoofFields::Width, true);
    }

    bool Roof_Impl::setWidth(double width) {
      return setDouble(openstudio::RoofFields::Width, width);
    }

    void Roof_Impl::resetWidth() {
      OS_ASSERT(setString(openstudio::RoofFields::Width, ""));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
