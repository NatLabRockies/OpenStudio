/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ZoneHVACComponent/ZoneVentilationWindandStackOpenArea.hpp"
#include "ZoneHVACComponent/ZoneVentilationWindandStackOpenArea_Impl.hpp"

#include "HVACComponent/ThermalZone.hpp"
#include "HVACComponent/ThermalZone_Impl.hpp"
#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/ZoneVentilation_WindandStackOpenArea_FieldEnums.hxx>

#include <utility>

namespace openstudio {
namespace epmodel {

  ZoneVentilationWindandStackOpenArea::ZoneVentilationWindandStackOpenArea(const Model& model)
    : ZoneHVACComponent(ZoneVentilationWindandStackOpenArea::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::ZoneVentilationWindandStackOpenArea_Impl>());

    setOpeningArea(0.0);
    autocalculateOpeningEffectiveness();
    setEffectiveAngle(0.0);
    setHeightDifference(0.0);
    autocalculateDischargeCoefficientforOpening();
    setMinimumIndoorTemperature(-100.0);
    setMaximumIndoorTemperature(100.0);
    setDeltaTemperature(-100.0);
    setMinimumOutdoorTemperature(-100.0);
    setMaximumOutdoorTemperature(100.0);
    setMaximumWindSpeed(40.0);
  }

  ZoneVentilationWindandStackOpenArea::ZoneVentilationWindandStackOpenArea(std::shared_ptr<detail::ZoneVentilationWindandStackOpenArea_Impl> impl)
    : ZoneHVACComponent(std::move(impl)) {}

  IddObjectType ZoneVentilationWindandStackOpenArea::iddObjectType() {
    return IddObjectType::ZoneVentilation_WindandStackOpenArea;
  }

  double ZoneVentilationWindandStackOpenArea::openingArea() const {
    return getImpl<detail::ZoneVentilationWindandStackOpenArea_Impl>()->openingArea();
  }

  bool ZoneVentilationWindandStackOpenArea::setOpeningArea(double openingArea) {
    return getImpl<detail::ZoneVentilationWindandStackOpenArea_Impl>()->setOpeningArea(openingArea);
  }

  boost::optional<double> ZoneVentilationWindandStackOpenArea::openingEffectiveness() const {
    return getImpl<detail::ZoneVentilationWindandStackOpenArea_Impl>()->openingEffectiveness();
  }

  bool ZoneVentilationWindandStackOpenArea::isOpeningEffectivenessAutocalculated() const {
    return getImpl<detail::ZoneVentilationWindandStackOpenArea_Impl>()->isOpeningEffectivenessAutocalculated();
  }

  bool ZoneVentilationWindandStackOpenArea::setOpeningEffectiveness(double openingEffectiveness) {
    return getImpl<detail::ZoneVentilationWindandStackOpenArea_Impl>()->setOpeningEffectiveness(openingEffectiveness);
  }

  void ZoneVentilationWindandStackOpenArea::autocalculateOpeningEffectiveness() {
    getImpl<detail::ZoneVentilationWindandStackOpenArea_Impl>()->autocalculateOpeningEffectiveness();
  }

  double ZoneVentilationWindandStackOpenArea::effectiveAngle() const {
    return getImpl<detail::ZoneVentilationWindandStackOpenArea_Impl>()->effectiveAngle();
  }

  bool ZoneVentilationWindandStackOpenArea::setEffectiveAngle(double effectiveAngle) {
    return getImpl<detail::ZoneVentilationWindandStackOpenArea_Impl>()->setEffectiveAngle(effectiveAngle);
  }

  double ZoneVentilationWindandStackOpenArea::heightDifference() const {
    return getImpl<detail::ZoneVentilationWindandStackOpenArea_Impl>()->heightDifference();
  }

  bool ZoneVentilationWindandStackOpenArea::setHeightDifference(double heightDifference) {
    return getImpl<detail::ZoneVentilationWindandStackOpenArea_Impl>()->setHeightDifference(heightDifference);
  }

  boost::optional<double> ZoneVentilationWindandStackOpenArea::dischargeCoefficientforOpening() const {
    return getImpl<detail::ZoneVentilationWindandStackOpenArea_Impl>()->dischargeCoefficientforOpening();
  }

  bool ZoneVentilationWindandStackOpenArea::isDischargeCoefficientforOpeningAutocalculated() const {
    return getImpl<detail::ZoneVentilationWindandStackOpenArea_Impl>()->isDischargeCoefficientforOpeningAutocalculated();
  }

  bool ZoneVentilationWindandStackOpenArea::setDischargeCoefficientforOpening(double dischargeCoefficientforOpening) {
    return getImpl<detail::ZoneVentilationWindandStackOpenArea_Impl>()->setDischargeCoefficientforOpening(dischargeCoefficientforOpening);
  }

  void ZoneVentilationWindandStackOpenArea::autocalculateDischargeCoefficientforOpening() {
    getImpl<detail::ZoneVentilationWindandStackOpenArea_Impl>()->autocalculateDischargeCoefficientforOpening();
  }

  double ZoneVentilationWindandStackOpenArea::minimumIndoorTemperature() const {
    return getImpl<detail::ZoneVentilationWindandStackOpenArea_Impl>()->minimumIndoorTemperature();
  }

  bool ZoneVentilationWindandStackOpenArea::setMinimumIndoorTemperature(double minimumIndoorTemperature) {
    return getImpl<detail::ZoneVentilationWindandStackOpenArea_Impl>()->setMinimumIndoorTemperature(minimumIndoorTemperature);
  }

  double ZoneVentilationWindandStackOpenArea::maximumIndoorTemperature() const {
    return getImpl<detail::ZoneVentilationWindandStackOpenArea_Impl>()->maximumIndoorTemperature();
  }

  bool ZoneVentilationWindandStackOpenArea::setMaximumIndoorTemperature(double maximumIndoorTemperature) {
    return getImpl<detail::ZoneVentilationWindandStackOpenArea_Impl>()->setMaximumIndoorTemperature(maximumIndoorTemperature);
  }

  double ZoneVentilationWindandStackOpenArea::deltaTemperature() const {
    return getImpl<detail::ZoneVentilationWindandStackOpenArea_Impl>()->deltaTemperature();
  }

  bool ZoneVentilationWindandStackOpenArea::setDeltaTemperature(double deltaTemperature) {
    return getImpl<detail::ZoneVentilationWindandStackOpenArea_Impl>()->setDeltaTemperature(deltaTemperature);
  }

  double ZoneVentilationWindandStackOpenArea::minimumOutdoorTemperature() const {
    return getImpl<detail::ZoneVentilationWindandStackOpenArea_Impl>()->minimumOutdoorTemperature();
  }

  bool ZoneVentilationWindandStackOpenArea::setMinimumOutdoorTemperature(double minimumOutdoorTemperature) {
    return getImpl<detail::ZoneVentilationWindandStackOpenArea_Impl>()->setMinimumOutdoorTemperature(minimumOutdoorTemperature);
  }

  double ZoneVentilationWindandStackOpenArea::maximumOutdoorTemperature() const {
    return getImpl<detail::ZoneVentilationWindandStackOpenArea_Impl>()->maximumOutdoorTemperature();
  }

  bool ZoneVentilationWindandStackOpenArea::setMaximumOutdoorTemperature(double maximumOutdoorTemperature) {
    return getImpl<detail::ZoneVentilationWindandStackOpenArea_Impl>()->setMaximumOutdoorTemperature(maximumOutdoorTemperature);
  }

  double ZoneVentilationWindandStackOpenArea::maximumWindSpeed() const {
    return getImpl<detail::ZoneVentilationWindandStackOpenArea_Impl>()->maximumWindSpeed();
  }

  bool ZoneVentilationWindandStackOpenArea::setMaximumWindSpeed(double maximumWindSpeed) {
    return getImpl<detail::ZoneVentilationWindandStackOpenArea_Impl>()->setMaximumWindSpeed(maximumWindSpeed);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double ZoneVentilationWindandStackOpenArea_Impl::openingArea() const {
      auto value = getDouble(ZoneVentilation_WindandStackOpenAreaFields::OpeningArea, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneVentilationWindandStackOpenArea_Impl::setOpeningArea(double openingArea) {
      return setDouble(ZoneVentilation_WindandStackOpenAreaFields::OpeningArea, openingArea);
    }

    boost::optional<double> ZoneVentilationWindandStackOpenArea_Impl::openingEffectiveness() const {
      return getDouble(ZoneVentilation_WindandStackOpenAreaFields::OpeningEffectiveness, false);
    }

    bool ZoneVentilationWindandStackOpenArea_Impl::isOpeningEffectivenessAutocalculated() const {
      if (auto value = getString(ZoneVentilation_WindandStackOpenAreaFields::OpeningEffectiveness, true)) {
        return openstudio::istringEqual(value.get(), "Autocalculate");
      }
      return false;
    }

    bool ZoneVentilationWindandStackOpenArea_Impl::setOpeningEffectiveness(double openingEffectiveness) {
      return setDouble(ZoneVentilation_WindandStackOpenAreaFields::OpeningEffectiveness, openingEffectiveness);
    }

    void ZoneVentilationWindandStackOpenArea_Impl::autocalculateOpeningEffectiveness() {
      OS_ASSERT(setString(ZoneVentilation_WindandStackOpenAreaFields::OpeningEffectiveness, "autocalculate"));
    }

    double ZoneVentilationWindandStackOpenArea_Impl::effectiveAngle() const {
      auto value = getDouble(ZoneVentilation_WindandStackOpenAreaFields::EffectiveAngle, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneVentilationWindandStackOpenArea_Impl::setEffectiveAngle(double effectiveAngle) {
      return setDouble(ZoneVentilation_WindandStackOpenAreaFields::EffectiveAngle, effectiveAngle);
    }

    double ZoneVentilationWindandStackOpenArea_Impl::heightDifference() const {
      auto value = getDouble(ZoneVentilation_WindandStackOpenAreaFields::HeightDifference, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneVentilationWindandStackOpenArea_Impl::setHeightDifference(double heightDifference) {
      return setDouble(ZoneVentilation_WindandStackOpenAreaFields::HeightDifference, heightDifference);
    }

    boost::optional<double> ZoneVentilationWindandStackOpenArea_Impl::dischargeCoefficientforOpening() const {
      return getDouble(ZoneVentilation_WindandStackOpenAreaFields::DischargeCoefficientforOpening, false);
    }

    bool ZoneVentilationWindandStackOpenArea_Impl::isDischargeCoefficientforOpeningAutocalculated() const {
      if (auto value = getString(ZoneVentilation_WindandStackOpenAreaFields::DischargeCoefficientforOpening, true)) {
        return openstudio::istringEqual(value.get(), "Autocalculate");
      }
      return false;
    }

    bool ZoneVentilationWindandStackOpenArea_Impl::setDischargeCoefficientforOpening(double dischargeCoefficientforOpening) {
      return setDouble(ZoneVentilation_WindandStackOpenAreaFields::DischargeCoefficientforOpening, dischargeCoefficientforOpening);
    }

    void ZoneVentilationWindandStackOpenArea_Impl::autocalculateDischargeCoefficientforOpening() {
      OS_ASSERT(setString(ZoneVentilation_WindandStackOpenAreaFields::DischargeCoefficientforOpening, "autocalculate"));
    }

    double ZoneVentilationWindandStackOpenArea_Impl::minimumIndoorTemperature() const {
      auto value = getDouble(ZoneVentilation_WindandStackOpenAreaFields::MinimumIndoorTemperature, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneVentilationWindandStackOpenArea_Impl::setMinimumIndoorTemperature(double minimumIndoorTemperature) {
      return setDouble(ZoneVentilation_WindandStackOpenAreaFields::MinimumIndoorTemperature, minimumIndoorTemperature);
    }

    double ZoneVentilationWindandStackOpenArea_Impl::maximumIndoorTemperature() const {
      auto value = getDouble(ZoneVentilation_WindandStackOpenAreaFields::MaximumIndoorTemperature, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneVentilationWindandStackOpenArea_Impl::setMaximumIndoorTemperature(double maximumIndoorTemperature) {
      return setDouble(ZoneVentilation_WindandStackOpenAreaFields::MaximumIndoorTemperature, maximumIndoorTemperature);
    }

    double ZoneVentilationWindandStackOpenArea_Impl::deltaTemperature() const {
      auto value = getDouble(ZoneVentilation_WindandStackOpenAreaFields::DeltaTemperature, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneVentilationWindandStackOpenArea_Impl::setDeltaTemperature(double deltaTemperature) {
      return setDouble(ZoneVentilation_WindandStackOpenAreaFields::DeltaTemperature, deltaTemperature);
    }

    double ZoneVentilationWindandStackOpenArea_Impl::minimumOutdoorTemperature() const {
      auto value = getDouble(ZoneVentilation_WindandStackOpenAreaFields::MinimumOutdoorTemperature, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneVentilationWindandStackOpenArea_Impl::setMinimumOutdoorTemperature(double minimumOutdoorTemperature) {
      return setDouble(ZoneVentilation_WindandStackOpenAreaFields::MinimumOutdoorTemperature, minimumOutdoorTemperature);
    }

    double ZoneVentilationWindandStackOpenArea_Impl::maximumOutdoorTemperature() const {
      auto value = getDouble(ZoneVentilation_WindandStackOpenAreaFields::MaximumOutdoorTemperature, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneVentilationWindandStackOpenArea_Impl::setMaximumOutdoorTemperature(double maximumOutdoorTemperature) {
      return setDouble(ZoneVentilation_WindandStackOpenAreaFields::MaximumOutdoorTemperature, maximumOutdoorTemperature);
    }

    double ZoneVentilationWindandStackOpenArea_Impl::maximumWindSpeed() const {
      auto value = getDouble(ZoneVentilation_WindandStackOpenAreaFields::MaximumWindSpeed, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneVentilationWindandStackOpenArea_Impl::setMaximumWindSpeed(double maximumWindSpeed) {
      return setDouble(ZoneVentilation_WindandStackOpenAreaFields::MaximumWindSpeed, maximumWindSpeed);
    }

    unsigned ZoneVentilationWindandStackOpenArea_Impl::inletPort() const {
      return 0u;
    }

    unsigned ZoneVentilationWindandStackOpenArea_Impl::outletPort() const {
      return 0u;
    }

    boost::optional<ThermalZone> ZoneVentilationWindandStackOpenArea_Impl::thermalZone() const {
      auto target = getTarget(ZoneVentilation_WindandStackOpenAreaFields::ZoneorSpaceName);
      if (!target) {
        return boost::none;
      }
      return target->optionalCast<ThermalZone>();
    }

    bool ZoneVentilationWindandStackOpenArea_Impl::addToThermalZone(ThermalZone& thermalZone) {
      if (thermalZone.model() != model()) {
        return false;
      }

      removeFromThermalZone();
      return setPointer(ZoneVentilation_WindandStackOpenAreaFields::ZoneorSpaceName, thermalZone.handle());
    }

    void ZoneVentilationWindandStackOpenArea_Impl::removeFromThermalZone() {
      OS_ASSERT(setPointer(ZoneVentilation_WindandStackOpenAreaFields::ZoneorSpaceName, Handle()));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
