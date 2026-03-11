/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "Model.hpp"
#include "ModelObject/Window.hpp"
#include "ModelObject/Window_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/Window_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  Window::Window(const Model& model) : ModelObject(Window::iddObjectType(), model) {}

  Window::Window(std::shared_ptr<detail::Window_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType Window::iddObjectType() {
    return IddObjectType::Window;
  }

  double Window::multiplier() const {
    return getImpl<detail::Window_Impl>()->multiplier();
  }

  bool Window::isMultiplierDefaulted() const {
    return getImpl<detail::Window_Impl>()->isMultiplierDefaulted();
  }

  bool Window::setMultiplier(double multiplier) {
    return getImpl<detail::Window_Impl>()->setMultiplier(multiplier);
  }

  void Window::resetMultiplier() {
    getImpl<detail::Window_Impl>()->resetMultiplier();
  }

  boost::optional<double> Window::startingXCoordinate() const {
    return getImpl<detail::Window_Impl>()->startingXCoordinate();
  }

  bool Window::setStartingXCoordinate(double startingXCoordinate) {
    return getImpl<detail::Window_Impl>()->setStartingXCoordinate(startingXCoordinate);
  }

  void Window::resetStartingXCoordinate() {
    getImpl<detail::Window_Impl>()->resetStartingXCoordinate();
  }

  boost::optional<double> Window::startingZCoordinate() const {
    return getImpl<detail::Window_Impl>()->startingZCoordinate();
  }

  bool Window::setStartingZCoordinate(double startingZCoordinate) {
    return getImpl<detail::Window_Impl>()->setStartingZCoordinate(startingZCoordinate);
  }

  void Window::resetStartingZCoordinate() {
    getImpl<detail::Window_Impl>()->resetStartingZCoordinate();
  }

  boost::optional<double> Window::length() const {
    return getImpl<detail::Window_Impl>()->length();
  }

  bool Window::setLength(double length) {
    return getImpl<detail::Window_Impl>()->setLength(length);
  }

  void Window::resetLength() {
    getImpl<detail::Window_Impl>()->resetLength();
  }

  boost::optional<double> Window::height() const {
    return getImpl<detail::Window_Impl>()->height();
  }

  bool Window::setHeight(double height) {
    return getImpl<detail::Window_Impl>()->setHeight(height);
  }

  void Window::resetHeight() {
    getImpl<detail::Window_Impl>()->resetHeight();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double Window_Impl::multiplier() const {
      const auto value = getDouble(openstudio::WindowFields::Multiplier, true);
      OS_ASSERT(value);
      return *value;
    }

    bool Window_Impl::isMultiplierDefaulted() const {
      return isEmpty(openstudio::WindowFields::Multiplier);
    }

    boost::optional<double> Window_Impl::startingXCoordinate() const {
      return getDouble(openstudio::WindowFields::StartingXCoordinate, true);
    }

    boost::optional<double> Window_Impl::startingZCoordinate() const {
      return getDouble(openstudio::WindowFields::StartingZCoordinate, true);
    }

    boost::optional<double> Window_Impl::length() const {
      return getDouble(openstudio::WindowFields::Length, true);
    }

    boost::optional<double> Window_Impl::height() const {
      return getDouble(openstudio::WindowFields::Height, true);
    }

    bool Window_Impl::setMultiplier(double multiplier) {
      const bool result = setDouble(openstudio::WindowFields::Multiplier, multiplier);
      OS_ASSERT(result);
      return result;
    }

    bool Window_Impl::setStartingXCoordinate(double startingXCoordinate) {
      const bool result = setDouble(openstudio::WindowFields::StartingXCoordinate, startingXCoordinate);
      OS_ASSERT(result);
      return result;
    }

    bool Window_Impl::setStartingZCoordinate(double startingZCoordinate) {
      const bool result = setDouble(openstudio::WindowFields::StartingZCoordinate, startingZCoordinate);
      OS_ASSERT(result);
      return result;
    }

    bool Window_Impl::setLength(double length) {
      const bool result = setDouble(openstudio::WindowFields::Length, length);
      OS_ASSERT(result);
      return result;
    }

    bool Window_Impl::setHeight(double height) {
      const bool result = setDouble(openstudio::WindowFields::Height, height);
      OS_ASSERT(result);
      return result;
    }

    void Window_Impl::resetMultiplier() {
      const bool result = setString(openstudio::WindowFields::Multiplier, "");
      OS_ASSERT(result);
    }

    void Window_Impl::resetStartingXCoordinate() {
      const bool result = setString(openstudio::WindowFields::StartingXCoordinate, "");
      OS_ASSERT(result);
    }

    void Window_Impl::resetStartingZCoordinate() {
      const bool result = setString(openstudio::WindowFields::StartingZCoordinate, "");
      OS_ASSERT(result);
    }

    void Window_Impl::resetLength() {
      const bool result = setString(openstudio::WindowFields::Length, "");
      OS_ASSERT(result);
    }

    void Window_Impl::resetHeight() {
      const bool result = setString(openstudio::WindowFields::Height, "");
      OS_ASSERT(result);
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
