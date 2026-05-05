/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "GlazedDoor.hpp"
#include "GlazedDoor_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/GlazedDoor_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  GlazedDoor::GlazedDoor(const Model& model) : ModelObject(GlazedDoor::iddObjectType(), model) {}

  GlazedDoor::GlazedDoor(std::shared_ptr<detail::GlazedDoor_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType GlazedDoor::iddObjectType() {
    return IddObjectType::GlazedDoor;
  }

  double GlazedDoor::multiplier() const {
    return getImpl<detail::GlazedDoor_Impl>()->multiplier();
  }

  bool GlazedDoor::isMultiplierDefaulted() const {
    return getImpl<detail::GlazedDoor_Impl>()->isMultiplierDefaulted();
  }

  bool GlazedDoor::setMultiplier(double multiplier) {
    return getImpl<detail::GlazedDoor_Impl>()->setMultiplier(multiplier);
  }

  void GlazedDoor::resetMultiplier() {
    getImpl<detail::GlazedDoor_Impl>()->resetMultiplier();
  }

  boost::optional<double> GlazedDoor::startingXCoordinate() const {
    return getImpl<detail::GlazedDoor_Impl>()->startingXCoordinate();
  }

  bool GlazedDoor::setStartingXCoordinate(double startingXCoordinate) {
    return getImpl<detail::GlazedDoor_Impl>()->setStartingXCoordinate(startingXCoordinate);
  }

  void GlazedDoor::resetStartingXCoordinate() {
    getImpl<detail::GlazedDoor_Impl>()->resetStartingXCoordinate();
  }

  boost::optional<double> GlazedDoor::startingZCoordinate() const {
    return getImpl<detail::GlazedDoor_Impl>()->startingZCoordinate();
  }

  bool GlazedDoor::setStartingZCoordinate(double startingZCoordinate) {
    return getImpl<detail::GlazedDoor_Impl>()->setStartingZCoordinate(startingZCoordinate);
  }

  void GlazedDoor::resetStartingZCoordinate() {
    getImpl<detail::GlazedDoor_Impl>()->resetStartingZCoordinate();
  }

  boost::optional<double> GlazedDoor::length() const {
    return getImpl<detail::GlazedDoor_Impl>()->length();
  }

  bool GlazedDoor::setLength(double length) {
    return getImpl<detail::GlazedDoor_Impl>()->setLength(length);
  }

  void GlazedDoor::resetLength() {
    getImpl<detail::GlazedDoor_Impl>()->resetLength();
  }

  boost::optional<double> GlazedDoor::height() const {
    return getImpl<detail::GlazedDoor_Impl>()->height();
  }

  bool GlazedDoor::setHeight(double height) {
    return getImpl<detail::GlazedDoor_Impl>()->setHeight(height);
  }

  void GlazedDoor::resetHeight() {
    getImpl<detail::GlazedDoor_Impl>()->resetHeight();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double GlazedDoor_Impl::multiplier() const {
      const auto value = getDouble(openstudio::GlazedDoorFields::Multiplier, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GlazedDoor_Impl::isMultiplierDefaulted() const {
      return isEmpty(openstudio::GlazedDoorFields::Multiplier);
    }

    bool GlazedDoor_Impl::setMultiplier(double multiplier) {
      return setDouble(openstudio::GlazedDoorFields::Multiplier, multiplier);
    }

    void GlazedDoor_Impl::resetMultiplier() {
      OS_ASSERT(setString(openstudio::GlazedDoorFields::Multiplier, ""));
    }

    boost::optional<double> GlazedDoor_Impl::startingXCoordinate() const {
      return getDouble(openstudio::GlazedDoorFields::StartingXCoordinate, true);
    }

    bool GlazedDoor_Impl::setStartingXCoordinate(double startingXCoordinate) {
      return setDouble(openstudio::GlazedDoorFields::StartingXCoordinate, startingXCoordinate);
    }

    void GlazedDoor_Impl::resetStartingXCoordinate() {
      OS_ASSERT(setString(openstudio::GlazedDoorFields::StartingXCoordinate, ""));
    }

    boost::optional<double> GlazedDoor_Impl::startingZCoordinate() const {
      return getDouble(openstudio::GlazedDoorFields::StartingZCoordinate, true);
    }

    bool GlazedDoor_Impl::setStartingZCoordinate(double startingZCoordinate) {
      return setDouble(openstudio::GlazedDoorFields::StartingZCoordinate, startingZCoordinate);
    }

    void GlazedDoor_Impl::resetStartingZCoordinate() {
      OS_ASSERT(setString(openstudio::GlazedDoorFields::StartingZCoordinate, ""));
    }

    boost::optional<double> GlazedDoor_Impl::length() const {
      return getDouble(openstudio::GlazedDoorFields::Length, true);
    }

    bool GlazedDoor_Impl::setLength(double length) {
      return setDouble(openstudio::GlazedDoorFields::Length, length);
    }

    void GlazedDoor_Impl::resetLength() {
      OS_ASSERT(setString(openstudio::GlazedDoorFields::Length, ""));
    }

    boost::optional<double> GlazedDoor_Impl::height() const {
      return getDouble(openstudio::GlazedDoorFields::Height, true);
    }

    bool GlazedDoor_Impl::setHeight(double height) {
      return setDouble(openstudio::GlazedDoorFields::Height, height);
    }

    void GlazedDoor_Impl::resetHeight() {
      OS_ASSERT(setString(openstudio::GlazedDoorFields::Height, ""));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
