/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ZoneHVACComponent/ZoneVentilationWindandStackOpenArea.hpp"
#include "ZoneHVACComponent/ZoneVentilationWindandStackOpenArea_Impl.hpp"

#include "HVACComponent/ThermalZone.hpp"
#include "HVACComponent/ThermalZone_Impl.hpp"
#include "Model.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"

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

    auto alwaysOn = model.alwaysOnDiscreteSchedule();
    OS_ASSERT(setOpeningAreaFractionSchedule(alwaysOn));
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

  Schedule ZoneVentilationWindandStackOpenArea::openingAreaFractionSchedule() const {
    return getImpl<detail::ZoneVentilationWindandStackOpenArea_Impl>()->openingAreaFractionSchedule();
  }

  bool ZoneVentilationWindandStackOpenArea::setOpeningAreaFractionSchedule(Schedule& schedule) {
    return getImpl<detail::ZoneVentilationWindandStackOpenArea_Impl>()->setOpeningAreaFractionSchedule(schedule);
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

  boost::optional<Schedule> ZoneVentilationWindandStackOpenArea::minimumIndoorTemperatureSchedule() const {
    return getImpl<detail::ZoneVentilationWindandStackOpenArea_Impl>()->minimumIndoorTemperatureSchedule();
  }

  bool ZoneVentilationWindandStackOpenArea::setMinimumIndoorTemperatureSchedule(Schedule& schedule) {
    return getImpl<detail::ZoneVentilationWindandStackOpenArea_Impl>()->setMinimumIndoorTemperatureSchedule(schedule);
  }

  void ZoneVentilationWindandStackOpenArea::resetMinimumIndoorTemperatureSchedule() {
    getImpl<detail::ZoneVentilationWindandStackOpenArea_Impl>()->resetMinimumIndoorTemperatureSchedule();
  }

  double ZoneVentilationWindandStackOpenArea::maximumIndoorTemperature() const {
    return getImpl<detail::ZoneVentilationWindandStackOpenArea_Impl>()->maximumIndoorTemperature();
  }

  bool ZoneVentilationWindandStackOpenArea::setMaximumIndoorTemperature(double maximumIndoorTemperature) {
    return getImpl<detail::ZoneVentilationWindandStackOpenArea_Impl>()->setMaximumIndoorTemperature(maximumIndoorTemperature);
  }

  boost::optional<Schedule> ZoneVentilationWindandStackOpenArea::maximumIndoorTemperatureSchedule() const {
    return getImpl<detail::ZoneVentilationWindandStackOpenArea_Impl>()->maximumIndoorTemperatureSchedule();
  }

  bool ZoneVentilationWindandStackOpenArea::setMaximumIndoorTemperatureSchedule(Schedule& schedule) {
    return getImpl<detail::ZoneVentilationWindandStackOpenArea_Impl>()->setMaximumIndoorTemperatureSchedule(schedule);
  }

  void ZoneVentilationWindandStackOpenArea::resetMaximumIndoorTemperatureSchedule() {
    getImpl<detail::ZoneVentilationWindandStackOpenArea_Impl>()->resetMaximumIndoorTemperatureSchedule();
  }

  double ZoneVentilationWindandStackOpenArea::deltaTemperature() const {
    return getImpl<detail::ZoneVentilationWindandStackOpenArea_Impl>()->deltaTemperature();
  }

  bool ZoneVentilationWindandStackOpenArea::setDeltaTemperature(double deltaTemperature) {
    return getImpl<detail::ZoneVentilationWindandStackOpenArea_Impl>()->setDeltaTemperature(deltaTemperature);
  }

  boost::optional<Schedule> ZoneVentilationWindandStackOpenArea::deltaTemperatureSchedule() const {
    return getImpl<detail::ZoneVentilationWindandStackOpenArea_Impl>()->deltaTemperatureSchedule();
  }

  bool ZoneVentilationWindandStackOpenArea::setDeltaTemperatureSchedule(Schedule& schedule) {
    return getImpl<detail::ZoneVentilationWindandStackOpenArea_Impl>()->setDeltaTemperatureSchedule(schedule);
  }

  void ZoneVentilationWindandStackOpenArea::resetDeltaTemperatureSchedule() {
    getImpl<detail::ZoneVentilationWindandStackOpenArea_Impl>()->resetDeltaTemperatureSchedule();
  }

  double ZoneVentilationWindandStackOpenArea::minimumOutdoorTemperature() const {
    return getImpl<detail::ZoneVentilationWindandStackOpenArea_Impl>()->minimumOutdoorTemperature();
  }

  bool ZoneVentilationWindandStackOpenArea::setMinimumOutdoorTemperature(double minimumOutdoorTemperature) {
    return getImpl<detail::ZoneVentilationWindandStackOpenArea_Impl>()->setMinimumOutdoorTemperature(minimumOutdoorTemperature);
  }

  boost::optional<Schedule> ZoneVentilationWindandStackOpenArea::minimumOutdoorTemperatureSchedule() const {
    return getImpl<detail::ZoneVentilationWindandStackOpenArea_Impl>()->minimumOutdoorTemperatureSchedule();
  }

  bool ZoneVentilationWindandStackOpenArea::setMinimumOutdoorTemperatureSchedule(Schedule& schedule) {
    return getImpl<detail::ZoneVentilationWindandStackOpenArea_Impl>()->setMinimumOutdoorTemperatureSchedule(schedule);
  }

  void ZoneVentilationWindandStackOpenArea::resetMinimumOutdoorTemperatureSchedule() {
    getImpl<detail::ZoneVentilationWindandStackOpenArea_Impl>()->resetMinimumOutdoorTemperatureSchedule();
  }

  double ZoneVentilationWindandStackOpenArea::maximumOutdoorTemperature() const {
    return getImpl<detail::ZoneVentilationWindandStackOpenArea_Impl>()->maximumOutdoorTemperature();
  }

  bool ZoneVentilationWindandStackOpenArea::setMaximumOutdoorTemperature(double maximumOutdoorTemperature) {
    return getImpl<detail::ZoneVentilationWindandStackOpenArea_Impl>()->setMaximumOutdoorTemperature(maximumOutdoorTemperature);
  }

  boost::optional<Schedule> ZoneVentilationWindandStackOpenArea::maximumOutdoorTemperatureSchedule() const {
    return getImpl<detail::ZoneVentilationWindandStackOpenArea_Impl>()->maximumOutdoorTemperatureSchedule();
  }

  bool ZoneVentilationWindandStackOpenArea::setMaximumOutdoorTemperatureSchedule(Schedule& schedule) {
    return getImpl<detail::ZoneVentilationWindandStackOpenArea_Impl>()->setMaximumOutdoorTemperatureSchedule(schedule);
  }

  void ZoneVentilationWindandStackOpenArea::resetMaximumOutdoorTemperatureSchedule() {
    getImpl<detail::ZoneVentilationWindandStackOpenArea_Impl>()->resetMaximumOutdoorTemperatureSchedule();
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

    void ZoneVentilationWindandStackOpenArea_Impl::doCanonicalize(LoadContext& context) {
      auto owner = getObject<ModelObject>();
      constexpr auto field = openstudio::ZoneVentilation_WindandStackOpenAreaFields::OpeningAreaFractionScheduleName;
      const auto rawSchedule = openstudio::detail::IdfObject_Impl::getString(field, false, true);
      if ((!rawSchedule || rawSchedule->empty()) && !owner.getModelObjectTarget<Schedule>(field)) {
        auto alwaysOn = model().alwaysOnDiscreteSchedule();
        if (setOpeningAreaFractionSchedule(alwaysOn)) {
          detail::addLoadInfo(context, "Attached the always-on opening-area-fraction schedule to ZoneVentilation:WindandStackOpenArea '"
                                         + owner.nameString() + "'.");
        } else {
          detail::addLoadError(context, "Failed to attach the always-on opening-area-fraction schedule to ZoneVentilation:WindandStackOpenArea '"
                                          + owner.nameString() + "'.");
        }
      }
    }

    double ZoneVentilationWindandStackOpenArea_Impl::openingArea() const {
      auto value = getDouble(ZoneVentilation_WindandStackOpenAreaFields::OpeningArea, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneVentilationWindandStackOpenArea_Impl::setOpeningArea(double openingArea) {
      return setDouble(ZoneVentilation_WindandStackOpenAreaFields::OpeningArea, openingArea);
    }

    Schedule ZoneVentilationWindandStackOpenArea_Impl::openingAreaFractionSchedule() const {
      auto target = getObject<ModelObject>().getModelObjectTarget<Schedule>(
        openstudio::ZoneVentilation_WindandStackOpenAreaFields::OpeningAreaFractionScheduleName);
      OS_ASSERT(target);
      return *target;
    }

    bool ZoneVentilationWindandStackOpenArea_Impl::setOpeningAreaFractionSchedule(Schedule& schedule) {
      return ModelObject_Impl::setSchedule(openstudio::ZoneVentilation_WindandStackOpenAreaFields::OpeningAreaFractionScheduleName,
                                           "ZoneVentilationWindandStackOpenArea", "Opening Area Fraction Schedule", schedule);
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

    boost::optional<Schedule> ZoneVentilationWindandStackOpenArea_Impl::minimumIndoorTemperatureSchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(
        openstudio::ZoneVentilation_WindandStackOpenAreaFields::MinimumIndoorTemperatureScheduleName);
    }

    bool ZoneVentilationWindandStackOpenArea_Impl::setMinimumIndoorTemperatureSchedule(Schedule& schedule) {
      return ModelObject_Impl::setSchedule(openstudio::ZoneVentilation_WindandStackOpenAreaFields::MinimumIndoorTemperatureScheduleName,
                                           "ZoneVentilationWindandStackOpenArea", "Minimum Indoor Temperature", schedule);
    }

    void ZoneVentilationWindandStackOpenArea_Impl::resetMinimumIndoorTemperatureSchedule() {
      constexpr auto field = openstudio::ZoneVentilation_WindandStackOpenAreaFields::MinimumIndoorTemperatureScheduleName;
      OS_ASSERT(setPointer(field, Handle(), false));
      OS_ASSERT(openstudio::detail::IdfObject_Impl::setString(field, "", false));
    }

    double ZoneVentilationWindandStackOpenArea_Impl::maximumIndoorTemperature() const {
      auto value = getDouble(ZoneVentilation_WindandStackOpenAreaFields::MaximumIndoorTemperature, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneVentilationWindandStackOpenArea_Impl::setMaximumIndoorTemperature(double maximumIndoorTemperature) {
      return setDouble(ZoneVentilation_WindandStackOpenAreaFields::MaximumIndoorTemperature, maximumIndoorTemperature);
    }

    boost::optional<Schedule> ZoneVentilationWindandStackOpenArea_Impl::maximumIndoorTemperatureSchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(
        openstudio::ZoneVentilation_WindandStackOpenAreaFields::MaximumIndoorTemperatureScheduleName);
    }

    bool ZoneVentilationWindandStackOpenArea_Impl::setMaximumIndoorTemperatureSchedule(Schedule& schedule) {
      return ModelObject_Impl::setSchedule(openstudio::ZoneVentilation_WindandStackOpenAreaFields::MaximumIndoorTemperatureScheduleName,
                                           "ZoneVentilationWindandStackOpenArea", "Maximum Indoor Temperature", schedule);
    }

    void ZoneVentilationWindandStackOpenArea_Impl::resetMaximumIndoorTemperatureSchedule() {
      constexpr auto field = openstudio::ZoneVentilation_WindandStackOpenAreaFields::MaximumIndoorTemperatureScheduleName;
      OS_ASSERT(setPointer(field, Handle(), false));
      OS_ASSERT(openstudio::detail::IdfObject_Impl::setString(field, "", false));
    }

    double ZoneVentilationWindandStackOpenArea_Impl::deltaTemperature() const {
      auto value = getDouble(ZoneVentilation_WindandStackOpenAreaFields::DeltaTemperature, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneVentilationWindandStackOpenArea_Impl::setDeltaTemperature(double deltaTemperature) {
      return setDouble(ZoneVentilation_WindandStackOpenAreaFields::DeltaTemperature, deltaTemperature);
    }

    boost::optional<Schedule> ZoneVentilationWindandStackOpenArea_Impl::deltaTemperatureSchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(
        openstudio::ZoneVentilation_WindandStackOpenAreaFields::DeltaTemperatureScheduleName);
    }

    bool ZoneVentilationWindandStackOpenArea_Impl::setDeltaTemperatureSchedule(Schedule& schedule) {
      return ModelObject_Impl::setSchedule(openstudio::ZoneVentilation_WindandStackOpenAreaFields::DeltaTemperatureScheduleName,
                                           "ZoneVentilationWindandStackOpenArea", "Delta Temperature", schedule);
    }

    void ZoneVentilationWindandStackOpenArea_Impl::resetDeltaTemperatureSchedule() {
      constexpr auto field = openstudio::ZoneVentilation_WindandStackOpenAreaFields::DeltaTemperatureScheduleName;
      OS_ASSERT(setPointer(field, Handle(), false));
      OS_ASSERT(openstudio::detail::IdfObject_Impl::setString(field, "", false));
    }

    double ZoneVentilationWindandStackOpenArea_Impl::minimumOutdoorTemperature() const {
      auto value = getDouble(ZoneVentilation_WindandStackOpenAreaFields::MinimumOutdoorTemperature, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneVentilationWindandStackOpenArea_Impl::setMinimumOutdoorTemperature(double minimumOutdoorTemperature) {
      return setDouble(ZoneVentilation_WindandStackOpenAreaFields::MinimumOutdoorTemperature, minimumOutdoorTemperature);
    }

    boost::optional<Schedule> ZoneVentilationWindandStackOpenArea_Impl::minimumOutdoorTemperatureSchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(
        openstudio::ZoneVentilation_WindandStackOpenAreaFields::MinimumOutdoorTemperatureScheduleName);
    }

    bool ZoneVentilationWindandStackOpenArea_Impl::setMinimumOutdoorTemperatureSchedule(Schedule& schedule) {
      return ModelObject_Impl::setSchedule(openstudio::ZoneVentilation_WindandStackOpenAreaFields::MinimumOutdoorTemperatureScheduleName,
                                           "ZoneVentilationWindandStackOpenArea", "Minimum Outdoor Temperature", schedule);
    }

    void ZoneVentilationWindandStackOpenArea_Impl::resetMinimumOutdoorTemperatureSchedule() {
      constexpr auto field = openstudio::ZoneVentilation_WindandStackOpenAreaFields::MinimumOutdoorTemperatureScheduleName;
      OS_ASSERT(setPointer(field, Handle(), false));
      OS_ASSERT(openstudio::detail::IdfObject_Impl::setString(field, "", false));
    }

    double ZoneVentilationWindandStackOpenArea_Impl::maximumOutdoorTemperature() const {
      auto value = getDouble(ZoneVentilation_WindandStackOpenAreaFields::MaximumOutdoorTemperature, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneVentilationWindandStackOpenArea_Impl::setMaximumOutdoorTemperature(double maximumOutdoorTemperature) {
      return setDouble(ZoneVentilation_WindandStackOpenAreaFields::MaximumOutdoorTemperature, maximumOutdoorTemperature);
    }

    boost::optional<Schedule> ZoneVentilationWindandStackOpenArea_Impl::maximumOutdoorTemperatureSchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(
        openstudio::ZoneVentilation_WindandStackOpenAreaFields::MaximumOutdoorTemperatureScheduleName);
    }

    bool ZoneVentilationWindandStackOpenArea_Impl::setMaximumOutdoorTemperatureSchedule(Schedule& schedule) {
      return ModelObject_Impl::setSchedule(openstudio::ZoneVentilation_WindandStackOpenAreaFields::MaximumOutdoorTemperatureScheduleName,
                                           "ZoneVentilationWindandStackOpenArea", "Maximum Outdoor Temperature", schedule);
    }

    void ZoneVentilationWindandStackOpenArea_Impl::resetMaximumOutdoorTemperatureSchedule() {
      constexpr auto field = openstudio::ZoneVentilation_WindandStackOpenAreaFields::MaximumOutdoorTemperatureScheduleName;
      OS_ASSERT(setPointer(field, Handle(), false));
      OS_ASSERT(openstudio::detail::IdfObject_Impl::setString(field, "", false));
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
