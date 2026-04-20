/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "WindowPropertyStormWindow.hpp"
#include "WindowPropertyStormWindow_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/WindowProperty_StormWindow_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  WindowPropertyStormWindow::WindowPropertyStormWindow(const Model& model) : ModelObject(WindowPropertyStormWindow::iddObjectType(), model) {}

  WindowPropertyStormWindow::WindowPropertyStormWindow(std::shared_ptr<detail::WindowPropertyStormWindow_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType WindowPropertyStormWindow::iddObjectType() {
    return IddObjectType::WindowProperty_StormWindow;
  }

  double WindowPropertyStormWindow::distanceBetweenStormGlassLayerandAdjacentGlass() const {
    return getImpl<detail::WindowPropertyStormWindow_Impl>()->distanceBetweenStormGlassLayerandAdjacentGlass();
  }

  bool WindowPropertyStormWindow::isDistanceBetweenStormGlassLayerandAdjacentGlassDefaulted() const {
    return getImpl<detail::WindowPropertyStormWindow_Impl>()->isDistanceBetweenStormGlassLayerandAdjacentGlassDefaulted();
  }

  bool WindowPropertyStormWindow::setDistanceBetweenStormGlassLayerandAdjacentGlass(double distanceBetweenStormGlassLayerandAdjacentGlass) {
    return getImpl<detail::WindowPropertyStormWindow_Impl>()->setDistanceBetweenStormGlassLayerandAdjacentGlass(
      distanceBetweenStormGlassLayerandAdjacentGlass);
  }

  void WindowPropertyStormWindow::resetDistanceBetweenStormGlassLayerandAdjacentGlass() {
    getImpl<detail::WindowPropertyStormWindow_Impl>()->resetDistanceBetweenStormGlassLayerandAdjacentGlass();
  }

  int WindowPropertyStormWindow::monththatStormGlassLayerisPutOn() const {
    return getImpl<detail::WindowPropertyStormWindow_Impl>()->monththatStormGlassLayerisPutOn();
  }

  bool WindowPropertyStormWindow::setMonththatStormGlassLayerisPutOn(int monththatStormGlassLayerisPutOn) {
    return getImpl<detail::WindowPropertyStormWindow_Impl>()->setMonththatStormGlassLayerisPutOn(monththatStormGlassLayerisPutOn);
  }

  int WindowPropertyStormWindow::dayofMonththatStormGlassLayerisPutOn() const {
    return getImpl<detail::WindowPropertyStormWindow_Impl>()->dayofMonththatStormGlassLayerisPutOn();
  }

  bool WindowPropertyStormWindow::setDayofMonththatStormGlassLayerisPutOn(int dayofMonththatStormGlassLayerisPutOn) {
    return getImpl<detail::WindowPropertyStormWindow_Impl>()->setDayofMonththatStormGlassLayerisPutOn(dayofMonththatStormGlassLayerisPutOn);
  }

  int WindowPropertyStormWindow::monththatStormGlassLayerisTakenOff() const {
    return getImpl<detail::WindowPropertyStormWindow_Impl>()->monththatStormGlassLayerisTakenOff();
  }

  bool WindowPropertyStormWindow::setMonththatStormGlassLayerisTakenOff(int monththatStormGlassLayerisTakenOff) {
    return getImpl<detail::WindowPropertyStormWindow_Impl>()->setMonththatStormGlassLayerisTakenOff(monththatStormGlassLayerisTakenOff);
  }

  int WindowPropertyStormWindow::dayofMonththatStormGlassLayerisTakenOff() const {
    return getImpl<detail::WindowPropertyStormWindow_Impl>()->dayofMonththatStormGlassLayerisTakenOff();
  }

  bool WindowPropertyStormWindow::setDayofMonththatStormGlassLayerisTakenOff(int dayofMonththatStormGlassLayerisTakenOff) {
    return getImpl<detail::WindowPropertyStormWindow_Impl>()->setDayofMonththatStormGlassLayerisTakenOff(dayofMonththatStormGlassLayerisTakenOff);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double WindowPropertyStormWindow_Impl::distanceBetweenStormGlassLayerandAdjacentGlass() const {
      const auto value = getDouble(openstudio::WindowProperty_StormWindowFields::DistanceBetweenStormGlassLayerandAdjacentGlass, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WindowPropertyStormWindow_Impl::isDistanceBetweenStormGlassLayerandAdjacentGlassDefaulted() const {
      return isEmpty(openstudio::WindowProperty_StormWindowFields::DistanceBetweenStormGlassLayerandAdjacentGlass);
    }

    bool WindowPropertyStormWindow_Impl::setDistanceBetweenStormGlassLayerandAdjacentGlass(double distanceBetweenStormGlassLayerandAdjacentGlass) {
      const bool result = setDouble(openstudio::WindowProperty_StormWindowFields::DistanceBetweenStormGlassLayerandAdjacentGlass,
                                    distanceBetweenStormGlassLayerandAdjacentGlass);
      OS_ASSERT(result);
      return result;
    }

    void WindowPropertyStormWindow_Impl::resetDistanceBetweenStormGlassLayerandAdjacentGlass() {
      OS_ASSERT(setString(openstudio::WindowProperty_StormWindowFields::DistanceBetweenStormGlassLayerandAdjacentGlass, ""));
    }

    int WindowPropertyStormWindow_Impl::monththatStormGlassLayerisPutOn() const {
      const auto value = getInt(openstudio::WindowProperty_StormWindowFields::MonththatStormGlassLayerisPutOn, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WindowPropertyStormWindow_Impl::setMonththatStormGlassLayerisPutOn(int monththatStormGlassLayerisPutOn) {
      const bool result = setInt(openstudio::WindowProperty_StormWindowFields::MonththatStormGlassLayerisPutOn, monththatStormGlassLayerisPutOn);
      OS_ASSERT(result);
      return result;
    }

    int WindowPropertyStormWindow_Impl::dayofMonththatStormGlassLayerisPutOn() const {
      const auto value = getInt(openstudio::WindowProperty_StormWindowFields::DayofMonththatStormGlassLayerisPutOn, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WindowPropertyStormWindow_Impl::setDayofMonththatStormGlassLayerisPutOn(int dayofMonththatStormGlassLayerisPutOn) {
      const bool result =
        setInt(openstudio::WindowProperty_StormWindowFields::DayofMonththatStormGlassLayerisPutOn, dayofMonththatStormGlassLayerisPutOn);
      OS_ASSERT(result);
      return result;
    }

    int WindowPropertyStormWindow_Impl::monththatStormGlassLayerisTakenOff() const {
      const auto value = getInt(openstudio::WindowProperty_StormWindowFields::MonththatStormGlassLayerisTakenOff, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WindowPropertyStormWindow_Impl::setMonththatStormGlassLayerisTakenOff(int monththatStormGlassLayerisTakenOff) {
      const bool result =
        setInt(openstudio::WindowProperty_StormWindowFields::MonththatStormGlassLayerisTakenOff, monththatStormGlassLayerisTakenOff);
      OS_ASSERT(result);
      return result;
    }

    int WindowPropertyStormWindow_Impl::dayofMonththatStormGlassLayerisTakenOff() const {
      const auto value = getInt(openstudio::WindowProperty_StormWindowFields::DayofMonththatStormGlassLayerisTakenOff, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WindowPropertyStormWindow_Impl::setDayofMonththatStormGlassLayerisTakenOff(int dayofMonththatStormGlassLayerisTakenOff) {
      const bool result =
        setInt(openstudio::WindowProperty_StormWindowFields::DayofMonththatStormGlassLayerisTakenOff, dayofMonththatStormGlassLayerisTakenOff);
      OS_ASSERT(result);
      return result;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
