/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "GlazedDoorInterzone.hpp"
#include "GlazedDoorInterzone_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/GlazedDoor_Interzone_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  GlazedDoorInterzone::GlazedDoorInterzone(const Model& model) : ModelObject(GlazedDoorInterzone::iddObjectType(), model) {}

  GlazedDoorInterzone::GlazedDoorInterzone(std::shared_ptr<detail::GlazedDoorInterzone_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType GlazedDoorInterzone::iddObjectType() {
    return IddObjectType::GlazedDoor_Interzone;
  }

  double GlazedDoorInterzone::multiplier() const {
    return getImpl<detail::GlazedDoorInterzone_Impl>()->multiplier();
  }

  bool GlazedDoorInterzone::setMultiplier(double multiplier) {
    return getImpl<detail::GlazedDoorInterzone_Impl>()->setMultiplier(multiplier);
  }

  bool GlazedDoorInterzone::isMultiplierDefaulted() const {
    return getImpl<detail::GlazedDoorInterzone_Impl>()->isMultiplierDefaulted();
  }

  void GlazedDoorInterzone::resetMultiplier() {
    getImpl<detail::GlazedDoorInterzone_Impl>()->resetMultiplier();
  }

  boost::optional<double> GlazedDoorInterzone::startingXCoordinate() const {
    return getImpl<detail::GlazedDoorInterzone_Impl>()->startingXCoordinate();
  }

  bool GlazedDoorInterzone::setStartingXCoordinate(double startingXCoordinate) {
    return getImpl<detail::GlazedDoorInterzone_Impl>()->setStartingXCoordinate(startingXCoordinate);
  }

  void GlazedDoorInterzone::resetStartingXCoordinate() {
    getImpl<detail::GlazedDoorInterzone_Impl>()->resetStartingXCoordinate();
  }

  boost::optional<double> GlazedDoorInterzone::startingZCoordinate() const {
    return getImpl<detail::GlazedDoorInterzone_Impl>()->startingZCoordinate();
  }

  bool GlazedDoorInterzone::setStartingZCoordinate(double startingZCoordinate) {
    return getImpl<detail::GlazedDoorInterzone_Impl>()->setStartingZCoordinate(startingZCoordinate);
  }

  void GlazedDoorInterzone::resetStartingZCoordinate() {
    getImpl<detail::GlazedDoorInterzone_Impl>()->resetStartingZCoordinate();
  }

  boost::optional<double> GlazedDoorInterzone::length() const {
    return getImpl<detail::GlazedDoorInterzone_Impl>()->length();
  }

  bool GlazedDoorInterzone::setLength(double length) {
    return getImpl<detail::GlazedDoorInterzone_Impl>()->setLength(length);
  }

  void GlazedDoorInterzone::resetLength() {
    getImpl<detail::GlazedDoorInterzone_Impl>()->resetLength();
  }

  boost::optional<double> GlazedDoorInterzone::height() const {
    return getImpl<detail::GlazedDoorInterzone_Impl>()->height();
  }

  bool GlazedDoorInterzone::setHeight(double height) {
    return getImpl<detail::GlazedDoorInterzone_Impl>()->setHeight(height);
  }

  void GlazedDoorInterzone::resetHeight() {
    getImpl<detail::GlazedDoorInterzone_Impl>()->resetHeight();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double GlazedDoorInterzone_Impl::multiplier() const {
      const auto value = getDouble(openstudio::GlazedDoor_InterzoneFields::Multiplier, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GlazedDoorInterzone_Impl::setMultiplier(double multiplier) {
      return setDouble(openstudio::GlazedDoor_InterzoneFields::Multiplier, multiplier);
    }

    bool GlazedDoorInterzone_Impl::isMultiplierDefaulted() const {
      return isEmpty(openstudio::GlazedDoor_InterzoneFields::Multiplier);
    }

    void GlazedDoorInterzone_Impl::resetMultiplier() {
      OS_ASSERT(setString(openstudio::GlazedDoor_InterzoneFields::Multiplier, ""));
    }

    boost::optional<double> GlazedDoorInterzone_Impl::startingXCoordinate() const {
      return getDouble(openstudio::GlazedDoor_InterzoneFields::StartingXCoordinate, true);
    }

    bool GlazedDoorInterzone_Impl::setStartingXCoordinate(double startingXCoordinate) {
      return setDouble(openstudio::GlazedDoor_InterzoneFields::StartingXCoordinate, startingXCoordinate);
    }

    void GlazedDoorInterzone_Impl::resetStartingXCoordinate() {
      OS_ASSERT(setString(openstudio::GlazedDoor_InterzoneFields::StartingXCoordinate, ""));
    }

    boost::optional<double> GlazedDoorInterzone_Impl::startingZCoordinate() const {
      return getDouble(openstudio::GlazedDoor_InterzoneFields::StartingZCoordinate, true);
    }

    bool GlazedDoorInterzone_Impl::setStartingZCoordinate(double startingZCoordinate) {
      return setDouble(openstudio::GlazedDoor_InterzoneFields::StartingZCoordinate, startingZCoordinate);
    }

    void GlazedDoorInterzone_Impl::resetStartingZCoordinate() {
      OS_ASSERT(setString(openstudio::GlazedDoor_InterzoneFields::StartingZCoordinate, ""));
    }

    boost::optional<double> GlazedDoorInterzone_Impl::length() const {
      return getDouble(openstudio::GlazedDoor_InterzoneFields::Length, true);
    }

    bool GlazedDoorInterzone_Impl::setLength(double length) {
      return setDouble(openstudio::GlazedDoor_InterzoneFields::Length, length);
    }

    void GlazedDoorInterzone_Impl::resetLength() {
      OS_ASSERT(setString(openstudio::GlazedDoor_InterzoneFields::Length, ""));
    }

    boost::optional<double> GlazedDoorInterzone_Impl::height() const {
      return getDouble(openstudio::GlazedDoor_InterzoneFields::Height, true);
    }

    bool GlazedDoorInterzone_Impl::setHeight(double height) {
      return setDouble(openstudio::GlazedDoor_InterzoneFields::Height, height);
    }

    void GlazedDoorInterzone_Impl::resetHeight() {
      OS_ASSERT(setString(openstudio::GlazedDoor_InterzoneFields::Height, ""));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
