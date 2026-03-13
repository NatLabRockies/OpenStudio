/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include "ModelObject/WindowInterzone.hpp"
#include "ModelObject/WindowInterzone_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/Window_Interzone_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  WindowInterzone::WindowInterzone(const Model& model) : ModelObject(WindowInterzone::iddObjectType(), model) {}

  WindowInterzone::WindowInterzone(std::shared_ptr<detail::WindowInterzone_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType WindowInterzone::iddObjectType() {
    return IddObjectType::Window_Interzone;
  }

  double WindowInterzone::multiplier() const {
    return getImpl<detail::WindowInterzone_Impl>()->multiplier();
  }

  bool WindowInterzone::isMultiplierDefaulted() const {
    return getImpl<detail::WindowInterzone_Impl>()->isMultiplierDefaulted();
  }

  bool WindowInterzone::setMultiplier(double multiplier) {
    return getImpl<detail::WindowInterzone_Impl>()->setMultiplier(multiplier);
  }

  void WindowInterzone::resetMultiplier() {
    getImpl<detail::WindowInterzone_Impl>()->resetMultiplier();
  }

  boost::optional<double> WindowInterzone::startingXCoordinate() const {
    return getImpl<detail::WindowInterzone_Impl>()->startingXCoordinate();
  }

  bool WindowInterzone::setStartingXCoordinate(double startingXCoordinate) {
    return getImpl<detail::WindowInterzone_Impl>()->setStartingXCoordinate(startingXCoordinate);
  }

  void WindowInterzone::resetStartingXCoordinate() {
    getImpl<detail::WindowInterzone_Impl>()->resetStartingXCoordinate();
  }

  boost::optional<double> WindowInterzone::startingZCoordinate() const {
    return getImpl<detail::WindowInterzone_Impl>()->startingZCoordinate();
  }

  bool WindowInterzone::setStartingZCoordinate(double startingZCoordinate) {
    return getImpl<detail::WindowInterzone_Impl>()->setStartingZCoordinate(startingZCoordinate);
  }

  void WindowInterzone::resetStartingZCoordinate() {
    getImpl<detail::WindowInterzone_Impl>()->resetStartingZCoordinate();
  }

  boost::optional<double> WindowInterzone::length() const {
    return getImpl<detail::WindowInterzone_Impl>()->length();
  }

  bool WindowInterzone::setLength(double length) {
    return getImpl<detail::WindowInterzone_Impl>()->setLength(length);
  }

  void WindowInterzone::resetLength() {
    getImpl<detail::WindowInterzone_Impl>()->resetLength();
  }

  boost::optional<double> WindowInterzone::height() const {
    return getImpl<detail::WindowInterzone_Impl>()->height();
  }

  bool WindowInterzone::setHeight(double height) {
    return getImpl<detail::WindowInterzone_Impl>()->setHeight(height);
  }

  void WindowInterzone::resetHeight() {
    getImpl<detail::WindowInterzone_Impl>()->resetHeight();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double WindowInterzone_Impl::multiplier() const {
      const auto value = getDouble(openstudio::Window_InterzoneFields::Multiplier, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WindowInterzone_Impl::isMultiplierDefaulted() const {
      return isEmpty(openstudio::Window_InterzoneFields::Multiplier);
    }

    bool WindowInterzone_Impl::setMultiplier(double multiplier) {
      const bool result = setDouble(openstudio::Window_InterzoneFields::Multiplier, multiplier);
      OS_ASSERT(result);
      return result;
    }

    void WindowInterzone_Impl::resetMultiplier() {
      OS_ASSERT(setString(openstudio::Window_InterzoneFields::Multiplier, ""));
    }

    boost::optional<double> WindowInterzone_Impl::startingXCoordinate() const {
      return getDouble(openstudio::Window_InterzoneFields::StartingXCoordinate, true);
    }

    bool WindowInterzone_Impl::setStartingXCoordinate(double startingXCoordinate) {
      const bool result = setDouble(openstudio::Window_InterzoneFields::StartingXCoordinate, startingXCoordinate);
      OS_ASSERT(result);
      return result;
    }

    void WindowInterzone_Impl::resetStartingXCoordinate() {
      OS_ASSERT(setString(openstudio::Window_InterzoneFields::StartingXCoordinate, ""));
    }

    boost::optional<double> WindowInterzone_Impl::startingZCoordinate() const {
      return getDouble(openstudio::Window_InterzoneFields::StartingZCoordinate, true);
    }

    bool WindowInterzone_Impl::setStartingZCoordinate(double startingZCoordinate) {
      const bool result = setDouble(openstudio::Window_InterzoneFields::StartingZCoordinate, startingZCoordinate);
      OS_ASSERT(result);
      return result;
    }

    void WindowInterzone_Impl::resetStartingZCoordinate() {
      OS_ASSERT(setString(openstudio::Window_InterzoneFields::StartingZCoordinate, ""));
    }

    boost::optional<double> WindowInterzone_Impl::length() const {
      return getDouble(openstudio::Window_InterzoneFields::Length, true);
    }

    bool WindowInterzone_Impl::setLength(double length) {
      const bool result = setDouble(openstudio::Window_InterzoneFields::Length, length);
      OS_ASSERT(result);
      return result;
    }

    void WindowInterzone_Impl::resetLength() {
      OS_ASSERT(setString(openstudio::Window_InterzoneFields::Length, ""));
    }

    boost::optional<double> WindowInterzone_Impl::height() const {
      return getDouble(openstudio::Window_InterzoneFields::Height, true);
    }

    bool WindowInterzone_Impl::setHeight(double height) {
      const bool result = setDouble(openstudio::Window_InterzoneFields::Height, height);
      OS_ASSERT(result);
      return result;
    }

    void WindowInterzone_Impl::resetHeight() {
      OS_ASSERT(setString(openstudio::Window_InterzoneFields::Height, ""));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
