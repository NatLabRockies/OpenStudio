/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "DoorInterzone.hpp"
#include "DoorInterzone_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/Door_Interzone_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  DoorInterzone::DoorInterzone(const Model& model) : ModelObject(DoorInterzone::iddObjectType(), model) {}

  DoorInterzone::DoorInterzone(std::shared_ptr<detail::DoorInterzone_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType DoorInterzone::iddObjectType() {
    return IddObjectType::Door_Interzone;
  }

  double DoorInterzone::multiplier() const {
    return getImpl<detail::DoorInterzone_Impl>()->multiplier();
  }

  bool DoorInterzone::isMultiplierDefaulted() const {
    return getImpl<detail::DoorInterzone_Impl>()->isMultiplierDefaulted();
  }

  bool DoorInterzone::setMultiplier(double multiplier) {
    return getImpl<detail::DoorInterzone_Impl>()->setMultiplier(multiplier);
  }

  void DoorInterzone::resetMultiplier() {
    getImpl<detail::DoorInterzone_Impl>()->resetMultiplier();
  }

  boost::optional<double> DoorInterzone::startingXCoordinate() const {
    return getImpl<detail::DoorInterzone_Impl>()->startingXCoordinate();
  }

  bool DoorInterzone::setStartingXCoordinate(double startingXCoordinate) {
    return getImpl<detail::DoorInterzone_Impl>()->setStartingXCoordinate(startingXCoordinate);
  }

  void DoorInterzone::resetStartingXCoordinate() {
    getImpl<detail::DoorInterzone_Impl>()->resetStartingXCoordinate();
  }

  boost::optional<double> DoorInterzone::startingZCoordinate() const {
    return getImpl<detail::DoorInterzone_Impl>()->startingZCoordinate();
  }

  bool DoorInterzone::setStartingZCoordinate(double startingZCoordinate) {
    return getImpl<detail::DoorInterzone_Impl>()->setStartingZCoordinate(startingZCoordinate);
  }

  void DoorInterzone::resetStartingZCoordinate() {
    getImpl<detail::DoorInterzone_Impl>()->resetStartingZCoordinate();
  }

  boost::optional<double> DoorInterzone::length() const {
    return getImpl<detail::DoorInterzone_Impl>()->length();
  }

  bool DoorInterzone::setLength(double length) {
    return getImpl<detail::DoorInterzone_Impl>()->setLength(length);
  }

  void DoorInterzone::resetLength() {
    getImpl<detail::DoorInterzone_Impl>()->resetLength();
  }

  boost::optional<double> DoorInterzone::height() const {
    return getImpl<detail::DoorInterzone_Impl>()->height();
  }

  bool DoorInterzone::setHeight(double height) {
    return getImpl<detail::DoorInterzone_Impl>()->setHeight(height);
  }

  void DoorInterzone::resetHeight() {
    getImpl<detail::DoorInterzone_Impl>()->resetHeight();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double DoorInterzone_Impl::multiplier() const {
      const auto value = getDouble(openstudio::Door_InterzoneFields::Multiplier, true);
      OS_ASSERT(value);
      return *value;
    }

    bool DoorInterzone_Impl::isMultiplierDefaulted() const {
      return isEmpty(openstudio::Door_InterzoneFields::Multiplier);
    }

    bool DoorInterzone_Impl::setMultiplier(double multiplier) {
      return setDouble(openstudio::Door_InterzoneFields::Multiplier, multiplier);
    }

    void DoorInterzone_Impl::resetMultiplier() {
      OS_ASSERT(setString(openstudio::Door_InterzoneFields::Multiplier, ""));
    }

    boost::optional<double> DoorInterzone_Impl::startingXCoordinate() const {
      return getDouble(openstudio::Door_InterzoneFields::StartingXCoordinate, true);
    }

    bool DoorInterzone_Impl::setStartingXCoordinate(double startingXCoordinate) {
      return setDouble(openstudio::Door_InterzoneFields::StartingXCoordinate, startingXCoordinate);
    }

    void DoorInterzone_Impl::resetStartingXCoordinate() {
      OS_ASSERT(setString(openstudio::Door_InterzoneFields::StartingXCoordinate, ""));
    }

    boost::optional<double> DoorInterzone_Impl::startingZCoordinate() const {
      return getDouble(openstudio::Door_InterzoneFields::StartingZCoordinate, true);
    }

    bool DoorInterzone_Impl::setStartingZCoordinate(double startingZCoordinate) {
      return setDouble(openstudio::Door_InterzoneFields::StartingZCoordinate, startingZCoordinate);
    }

    void DoorInterzone_Impl::resetStartingZCoordinate() {
      OS_ASSERT(setString(openstudio::Door_InterzoneFields::StartingZCoordinate, ""));
    }

    boost::optional<double> DoorInterzone_Impl::length() const {
      return getDouble(openstudio::Door_InterzoneFields::Length, true);
    }

    bool DoorInterzone_Impl::setLength(double length) {
      return setDouble(openstudio::Door_InterzoneFields::Length, length);
    }

    void DoorInterzone_Impl::resetLength() {
      OS_ASSERT(setString(openstudio::Door_InterzoneFields::Length, ""));
    }

    boost::optional<double> DoorInterzone_Impl::height() const {
      return getDouble(openstudio::Door_InterzoneFields::Height, true);
    }

    bool DoorInterzone_Impl::setHeight(double height) {
      return setDouble(openstudio::Door_InterzoneFields::Height, height);
    }

    void DoorInterzone_Impl::resetHeight() {
      OS_ASSERT(setString(openstudio::Door_InterzoneFields::Height, ""));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
