/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "DaylightingDeviceLightWell.hpp"
#include "DaylightingDeviceLightWell_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/DaylightingDevice_LightWell_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  DaylightingDeviceLightWell::DaylightingDeviceLightWell(const Model& model) : ModelObject(DaylightingDeviceLightWell::iddObjectType(), model) {}

  DaylightingDeviceLightWell::DaylightingDeviceLightWell(std::shared_ptr<detail::DaylightingDeviceLightWell_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType DaylightingDeviceLightWell::iddObjectType() {
    return IddObjectType::DaylightingDevice_LightWell;
  }

  double DaylightingDeviceLightWell::heightofWell() const {
    return getImpl<detail::DaylightingDeviceLightWell_Impl>()->heightofWell();
  }

  bool DaylightingDeviceLightWell::setHeightofWell(double heightofWell) {
    return getImpl<detail::DaylightingDeviceLightWell_Impl>()->setHeightofWell(heightofWell);
  }

  double DaylightingDeviceLightWell::perimeterofBottomofWell() const {
    return getImpl<detail::DaylightingDeviceLightWell_Impl>()->perimeterofBottomofWell();
  }

  bool DaylightingDeviceLightWell::setPerimeterofBottomofWell(double perimeterofBottomofWell) {
    return getImpl<detail::DaylightingDeviceLightWell_Impl>()->setPerimeterofBottomofWell(perimeterofBottomofWell);
  }

  double DaylightingDeviceLightWell::areaofBottomofWell() const {
    return getImpl<detail::DaylightingDeviceLightWell_Impl>()->areaofBottomofWell();
  }

  bool DaylightingDeviceLightWell::setAreaofBottomofWell(double areaofBottomofWell) {
    return getImpl<detail::DaylightingDeviceLightWell_Impl>()->setAreaofBottomofWell(areaofBottomofWell);
  }

  double DaylightingDeviceLightWell::visibleReflectanceofWellWalls() const {
    return getImpl<detail::DaylightingDeviceLightWell_Impl>()->visibleReflectanceofWellWalls();
  }

  bool DaylightingDeviceLightWell::setVisibleReflectanceofWellWalls(double visibleReflectanceofWellWalls) {
    return getImpl<detail::DaylightingDeviceLightWell_Impl>()->setVisibleReflectanceofWellWalls(visibleReflectanceofWellWalls);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double DaylightingDeviceLightWell_Impl::heightofWell() const {
      const auto value = getDouble(openstudio::DaylightingDevice_LightWellFields::HeightofWell, true);
      OS_ASSERT(value);
      return *value;
    }

    bool DaylightingDeviceLightWell_Impl::setHeightofWell(double heightofWell) {
      const bool result = setDouble(openstudio::DaylightingDevice_LightWellFields::HeightofWell, heightofWell);
      OS_ASSERT(result);
      return result;
    }

    double DaylightingDeviceLightWell_Impl::perimeterofBottomofWell() const {
      const auto value = getDouble(openstudio::DaylightingDevice_LightWellFields::PerimeterofBottomofWell, true);
      OS_ASSERT(value);
      return *value;
    }

    bool DaylightingDeviceLightWell_Impl::setPerimeterofBottomofWell(double perimeterofBottomofWell) {
      const bool result = setDouble(openstudio::DaylightingDevice_LightWellFields::PerimeterofBottomofWell, perimeterofBottomofWell);
      OS_ASSERT(result);
      return result;
    }

    double DaylightingDeviceLightWell_Impl::areaofBottomofWell() const {
      const auto value = getDouble(openstudio::DaylightingDevice_LightWellFields::AreaofBottomofWell, true);
      OS_ASSERT(value);
      return *value;
    }

    bool DaylightingDeviceLightWell_Impl::setAreaofBottomofWell(double areaofBottomofWell) {
      const bool result = setDouble(openstudio::DaylightingDevice_LightWellFields::AreaofBottomofWell, areaofBottomofWell);
      OS_ASSERT(result);
      return result;
    }

    double DaylightingDeviceLightWell_Impl::visibleReflectanceofWellWalls() const {
      const auto value = getDouble(openstudio::DaylightingDevice_LightWellFields::VisibleReflectanceofWellWalls, true);
      OS_ASSERT(value);
      return *value;
    }

    bool DaylightingDeviceLightWell_Impl::setVisibleReflectanceofWellWalls(double visibleReflectanceofWellWalls) {
      const bool result = setDouble(openstudio::DaylightingDevice_LightWellFields::VisibleReflectanceofWellWalls, visibleReflectanceofWellWalls);
      OS_ASSERT(result);
      return result;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
