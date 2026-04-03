/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ZoneHVACComponent/ZoneHVACUnitVentilator.hpp"
#include "ZoneHVACComponent/ZoneHVACUnitVentilator_Impl.hpp"

#include "HVACComponent.hpp"
#include "Model.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"
#include "Schedule/ScheduleConstant.hpp"

#include <boost/none.hpp>

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/ZoneHVAC_UnitVentilator_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  ZoneHVACUnitVentilator::ZoneHVACUnitVentilator(const Model& model) : ZoneHVACComponent(ZoneHVACUnitVentilator::iddObjectType(), model) {
    ScheduleConstant alwaysOn(model);
    OS_ASSERT(alwaysOn.setValue(1.0));
    OS_ASSERT(setAvailabilitySchedule(alwaysOn));
    OS_ASSERT(setOutdoorAirControlType("VariablePercent"));
    autosizeMaximumSupplyAirFlowRate();
    autosizeMinimumOutdoorAirFlowRate();
    autosizeMaximumOutdoorAirFlowRate();
    OS_ASSERT(setHeatingConvergenceTolerance(0.001));
    OS_ASSERT(setCoolingConvergenceTolerance(0.001));
  }

  ZoneHVACUnitVentilator::ZoneHVACUnitVentilator(std::shared_ptr<detail::ZoneHVACUnitVentilator_Impl> impl)
    : ZoneHVACComponent(std::move(impl)) {}

  IddObjectType ZoneHVACUnitVentilator::iddObjectType() {
    return IddObjectType::ZoneHVAC_UnitVentilator;
  }

  std::vector<std::string> ZoneHVACUnitVentilator::outdoorAirControlTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), ZoneHVAC_UnitVentilatorFields::OutdoorAirControlType);
  }

  Schedule ZoneHVACUnitVentilator::availabilitySchedule() const {
    return getImpl<detail::ZoneHVACUnitVentilator_Impl>()->availabilitySchedule();
  }

  bool ZoneHVACUnitVentilator::setAvailabilitySchedule(Schedule& schedule) {
    return getImpl<detail::ZoneHVACUnitVentilator_Impl>()->setAvailabilitySchedule(schedule);
  }

  boost::optional<double> ZoneHVACUnitVentilator::maximumSupplyAirFlowRate() const {
    return getImpl<detail::ZoneHVACUnitVentilator_Impl>()->maximumSupplyAirFlowRate();
  }

  bool ZoneHVACUnitVentilator::isMaximumSupplyAirFlowRateAutosized() const {
    return getImpl<detail::ZoneHVACUnitVentilator_Impl>()->isMaximumSupplyAirFlowRateAutosized();
  }

  bool ZoneHVACUnitVentilator::setMaximumSupplyAirFlowRate(double maximumSupplyAirFlowRate) {
    return getImpl<detail::ZoneHVACUnitVentilator_Impl>()->setMaximumSupplyAirFlowRate(maximumSupplyAirFlowRate);
  }

  void ZoneHVACUnitVentilator::autosizeMaximumSupplyAirFlowRate() {
    getImpl<detail::ZoneHVACUnitVentilator_Impl>()->autosizeMaximumSupplyAirFlowRate();
  }

  boost::optional<double> ZoneHVACUnitVentilator::autosizedMaximumSupplyAirFlowRate() const {
    return getImpl<detail::ZoneHVACUnitVentilator_Impl>()->autosizedMaximumSupplyAirFlowRate();
  }

  Schedule ZoneHVACUnitVentilator::minimumOutdoorAirSchedule() const {
    return getImpl<detail::ZoneHVACUnitVentilator_Impl>()->minimumOutdoorAirSchedule();
  }

  bool ZoneHVACUnitVentilator::setMinimumOutdoorAirSchedule(Schedule& schedule) {
    return getImpl<detail::ZoneHVACUnitVentilator_Impl>()->setMinimumOutdoorAirSchedule(schedule);
  }

  Schedule ZoneHVACUnitVentilator::maximumOutdoorAirFractionorTemperatureSchedule() const {
    return getImpl<detail::ZoneHVACUnitVentilator_Impl>()->maximumOutdoorAirFractionorTemperatureSchedule();
  }

  bool ZoneHVACUnitVentilator::setMaximumOutdoorAirFractionorTemperatureSchedule(Schedule& schedule) {
    return getImpl<detail::ZoneHVACUnitVentilator_Impl>()->setMaximumOutdoorAirFractionorTemperatureSchedule(schedule);
  }

  HVACComponent ZoneHVACUnitVentilator::supplyAirFan() const {
    return getImpl<detail::ZoneHVACUnitVentilator_Impl>()->supplyAirFan();
  }

  bool ZoneHVACUnitVentilator::setSupplyAirFan(const HVACComponent& supplyAirFan) {
    return getImpl<detail::ZoneHVACUnitVentilator_Impl>()->setSupplyAirFan(supplyAirFan);
  }

  boost::optional<Schedule> ZoneHVACUnitVentilator::supplyAirFanOperatingModeSchedule() const {
    return getImpl<detail::ZoneHVACUnitVentilator_Impl>()->supplyAirFanOperatingModeSchedule();
  }

  bool ZoneHVACUnitVentilator::setSupplyAirFanOperatingModeSchedule(Schedule& schedule) {
    return getImpl<detail::ZoneHVACUnitVentilator_Impl>()->setSupplyAirFanOperatingModeSchedule(schedule);
  }

  void ZoneHVACUnitVentilator::resetSupplyAirFanOperatingModeSchedule() {
    getImpl<detail::ZoneHVACUnitVentilator_Impl>()->resetSupplyAirFanOperatingModeSchedule();
  }

  boost::optional<HVACComponent> ZoneHVACUnitVentilator::heatingCoil() const {
    return getImpl<detail::ZoneHVACUnitVentilator_Impl>()->heatingCoil();
  }

  bool ZoneHVACUnitVentilator::setHeatingCoil(const HVACComponent& heatingCoil) {
    return getImpl<detail::ZoneHVACUnitVentilator_Impl>()->setHeatingCoil(heatingCoil);
  }

  void ZoneHVACUnitVentilator::resetHeatingCoil() {
    getImpl<detail::ZoneHVACUnitVentilator_Impl>()->resetHeatingCoil();
  }

  boost::optional<HVACComponent> ZoneHVACUnitVentilator::coolingCoil() const {
    return getImpl<detail::ZoneHVACUnitVentilator_Impl>()->coolingCoil();
  }

  bool ZoneHVACUnitVentilator::setCoolingCoil(const HVACComponent& coolingCoil) {
    return getImpl<detail::ZoneHVACUnitVentilator_Impl>()->setCoolingCoil(coolingCoil);
  }

  void ZoneHVACUnitVentilator::resetCoolingCoil() {
    getImpl<detail::ZoneHVACUnitVentilator_Impl>()->resetCoolingCoil();
  }

  std::string ZoneHVACUnitVentilator::outdoorAirControlType() const {
    return getImpl<detail::ZoneHVACUnitVentilator_Impl>()->outdoorAirControlType();
  }

  bool ZoneHVACUnitVentilator::setOutdoorAirControlType(const std::string& outdoorAirControlType) {
    return getImpl<detail::ZoneHVACUnitVentilator_Impl>()->setOutdoorAirControlType(outdoorAirControlType);
  }

  boost::optional<double> ZoneHVACUnitVentilator::minimumOutdoorAirFlowRate() const {
    return getImpl<detail::ZoneHVACUnitVentilator_Impl>()->minimumOutdoorAirFlowRate();
  }

  bool ZoneHVACUnitVentilator::isMinimumOutdoorAirFlowRateAutosized() const {
    return getImpl<detail::ZoneHVACUnitVentilator_Impl>()->isMinimumOutdoorAirFlowRateAutosized();
  }

  bool ZoneHVACUnitVentilator::setMinimumOutdoorAirFlowRate(double minimumOutdoorAirFlowRate) {
    return getImpl<detail::ZoneHVACUnitVentilator_Impl>()->setMinimumOutdoorAirFlowRate(minimumOutdoorAirFlowRate);
  }

  void ZoneHVACUnitVentilator::autosizeMinimumOutdoorAirFlowRate() {
    getImpl<detail::ZoneHVACUnitVentilator_Impl>()->autosizeMinimumOutdoorAirFlowRate();
  }

  boost::optional<double> ZoneHVACUnitVentilator::autosizedMinimumOutdoorAirFlowRate() const {
    return getImpl<detail::ZoneHVACUnitVentilator_Impl>()->autosizedMinimumOutdoorAirFlowRate();
  }

  boost::optional<double> ZoneHVACUnitVentilator::maximumOutdoorAirFlowRate() const {
    return getImpl<detail::ZoneHVACUnitVentilator_Impl>()->maximumOutdoorAirFlowRate();
  }

  bool ZoneHVACUnitVentilator::isMaximumOutdoorAirFlowRateAutosized() const {
    return getImpl<detail::ZoneHVACUnitVentilator_Impl>()->isMaximumOutdoorAirFlowRateAutosized();
  }

  bool ZoneHVACUnitVentilator::setMaximumOutdoorAirFlowRate(double maximumOutdoorAirFlowRate) {
    return getImpl<detail::ZoneHVACUnitVentilator_Impl>()->setMaximumOutdoorAirFlowRate(maximumOutdoorAirFlowRate);
  }

  void ZoneHVACUnitVentilator::autosizeMaximumOutdoorAirFlowRate() {
    getImpl<detail::ZoneHVACUnitVentilator_Impl>()->autosizeMaximumOutdoorAirFlowRate();
  }

  boost::optional<double> ZoneHVACUnitVentilator::autosizedMaximumOutdoorAirFlowRate() const {
    return getImpl<detail::ZoneHVACUnitVentilator_Impl>()->autosizedMaximumOutdoorAirFlowRate();
  }

  double ZoneHVACUnitVentilator::heatingConvergenceTolerance() const {
    return getImpl<detail::ZoneHVACUnitVentilator_Impl>()->heatingConvergenceTolerance();
  }

  bool ZoneHVACUnitVentilator::setHeatingConvergenceTolerance(double heatingConvergenceTolerance) {
    return getImpl<detail::ZoneHVACUnitVentilator_Impl>()->setHeatingConvergenceTolerance(heatingConvergenceTolerance);
  }

  double ZoneHVACUnitVentilator::coolingConvergenceTolerance() const {
    return getImpl<detail::ZoneHVACUnitVentilator_Impl>()->coolingConvergenceTolerance();
  }

  bool ZoneHVACUnitVentilator::setCoolingConvergenceTolerance(double coolingConvergenceTolerance) {
    return getImpl<detail::ZoneHVACUnitVentilator_Impl>()->setCoolingConvergenceTolerance(coolingConvergenceTolerance);
  }

  std::vector<ModelObject> ZoneHVACUnitVentilator::children() const {
    return getImpl<detail::ZoneHVACUnitVentilator_Impl>()->children();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    Schedule ZoneHVACUnitVentilator_Impl::availabilitySchedule() const {
      auto target = getObject<ModelObject>().getModelObjectTarget<Schedule>(ZoneHVAC_UnitVentilatorFields::AvailabilityScheduleName);
      OS_ASSERT(target);
      return *target;
    }

    bool ZoneHVACUnitVentilator_Impl::setAvailabilitySchedule(Schedule& schedule) {
      return ModelObject_Impl::setSchedule(ZoneHVAC_UnitVentilatorFields::AvailabilityScheduleName, "ZoneHVACUnitVentilator", "Availability",
                                           schedule);
    }

    boost::optional<double> ZoneHVACUnitVentilator_Impl::maximumSupplyAirFlowRate() const {
      return getDouble(ZoneHVAC_UnitVentilatorFields::MaximumSupplyAirFlowRate, true);
    }

    bool ZoneHVACUnitVentilator_Impl::isMaximumSupplyAirFlowRateAutosized() const {
      if (auto value = getString(ZoneHVAC_UnitVentilatorFields::MaximumSupplyAirFlowRate, true)) {
        return openstudio::istringEqual(value.get(), "autosize");
      }
      return false;
    }

    bool ZoneHVACUnitVentilator_Impl::setMaximumSupplyAirFlowRate(double maximumSupplyAirFlowRate) {
      const bool result = setDouble(ZoneHVAC_UnitVentilatorFields::MaximumSupplyAirFlowRate, maximumSupplyAirFlowRate);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACUnitVentilator_Impl::autosizeMaximumSupplyAirFlowRate() {
      OS_ASSERT(setString(ZoneHVAC_UnitVentilatorFields::MaximumSupplyAirFlowRate, "autosize"));
    }

    std::string ZoneHVACUnitVentilator_Impl::outdoorAirControlType() const {
      auto value = getString(ZoneHVAC_UnitVentilatorFields::OutdoorAirControlType, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACUnitVentilator_Impl::setOutdoorAirControlType(const std::string& outdoorAirControlType) {
      const bool result = setString(ZoneHVAC_UnitVentilatorFields::OutdoorAirControlType, outdoorAirControlType);
      OS_ASSERT(result);
      return result;
    }

    boost::optional<double> ZoneHVACUnitVentilator_Impl::minimumOutdoorAirFlowRate() const {
      return getDouble(ZoneHVAC_UnitVentilatorFields::MinimumOutdoorAirFlowRate, true);
    }

    bool ZoneHVACUnitVentilator_Impl::isMinimumOutdoorAirFlowRateAutosized() const {
      if (auto value = getString(ZoneHVAC_UnitVentilatorFields::MinimumOutdoorAirFlowRate, true)) {
        return openstudio::istringEqual(value.get(), "autosize");
      }
      return false;
    }

    bool ZoneHVACUnitVentilator_Impl::setMinimumOutdoorAirFlowRate(double minimumOutdoorAirFlowRate) {
      const bool result = setDouble(ZoneHVAC_UnitVentilatorFields::MinimumOutdoorAirFlowRate, minimumOutdoorAirFlowRate);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACUnitVentilator_Impl::autosizeMinimumOutdoorAirFlowRate() {
      OS_ASSERT(setString(ZoneHVAC_UnitVentilatorFields::MinimumOutdoorAirFlowRate, "autosize"));
    }

    boost::optional<double> ZoneHVACUnitVentilator_Impl::maximumOutdoorAirFlowRate() const {
      return getDouble(ZoneHVAC_UnitVentilatorFields::MaximumOutdoorAirFlowRate, true);
    }

    bool ZoneHVACUnitVentilator_Impl::isMaximumOutdoorAirFlowRateAutosized() const {
      if (auto value = getString(ZoneHVAC_UnitVentilatorFields::MaximumOutdoorAirFlowRate, true)) {
        return openstudio::istringEqual(value.get(), "autosize");
      }
      return false;
    }

    bool ZoneHVACUnitVentilator_Impl::setMaximumOutdoorAirFlowRate(double maximumOutdoorAirFlowRate) {
      const bool result = setDouble(ZoneHVAC_UnitVentilatorFields::MaximumOutdoorAirFlowRate, maximumOutdoorAirFlowRate);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACUnitVentilator_Impl::autosizeMaximumOutdoorAirFlowRate() {
      OS_ASSERT(setString(ZoneHVAC_UnitVentilatorFields::MaximumOutdoorAirFlowRate, "autosize"));
    }

    double ZoneHVACUnitVentilator_Impl::heatingConvergenceTolerance() const {
      auto value = getDouble(ZoneHVAC_UnitVentilatorFields::HeatingConvergenceTolerance, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACUnitVentilator_Impl::setHeatingConvergenceTolerance(double heatingConvergenceTolerance) {
      const bool result = setDouble(ZoneHVAC_UnitVentilatorFields::HeatingConvergenceTolerance, heatingConvergenceTolerance);
      OS_ASSERT(result);
      return result;
    }

    double ZoneHVACUnitVentilator_Impl::coolingConvergenceTolerance() const {
      auto value = getDouble(ZoneHVAC_UnitVentilatorFields::CoolingConvergenceTolerance, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACUnitVentilator_Impl::setCoolingConvergenceTolerance(double coolingConvergenceTolerance) {
      const bool result = setDouble(ZoneHVAC_UnitVentilatorFields::CoolingConvergenceTolerance, coolingConvergenceTolerance);
      OS_ASSERT(result);
      return result;
    }

    std::vector<ModelObject> ZoneHVACUnitVentilator_Impl::children() const {
      std::vector<ModelObject> result;

      if (auto const supplyFan = getObject<ModelObject>().getTarget(ZoneHVAC_UnitVentilatorFields::SupplyAirFanName)) {
        if (auto mo = model().getModelObject<ModelObject>(supplyFan->handle())) {
          result.push_back(*mo);
        }
      }
      if (auto const heatingCoil = getObject<ModelObject>().getTarget(ZoneHVAC_UnitVentilatorFields::HeatingCoilName)) {
        if (auto mo = model().getModelObject<ModelObject>(heatingCoil->handle())) {
          result.push_back(*mo);
        }
      }
      if (auto const coolingCoil = getObject<ModelObject>().getTarget(ZoneHVAC_UnitVentilatorFields::CoolingCoilName)) {
        if (auto mo = model().getModelObject<ModelObject>(coolingCoil->handle())) {
          result.push_back(*mo);
        }
      }

      return result;
    }

    unsigned ZoneHVACUnitVentilator_Impl::inletPort() const {
      return ZoneHVAC_UnitVentilatorFields::AirInletNodeName;
    }

    unsigned ZoneHVACUnitVentilator_Impl::outletPort() const {
      return ZoneHVAC_UnitVentilatorFields::AirOutletNodeName;
    }

    boost::optional<double> ZoneHVACUnitVentilator_Impl::autosizedMaximumSupplyAirFlowRate() const {
      // epmodel does not currently resolve autosized values from SQL results.
      return boost::none;
    }

    Schedule ZoneHVACUnitVentilator_Impl::minimumOutdoorAirSchedule() const {
      auto target = getObject<ModelObject>().getModelObjectTarget<Schedule>(ZoneHVAC_UnitVentilatorFields::MinimumOutdoorAirScheduleName);
      OS_ASSERT(target);
      return *target;
    }

    bool ZoneHVACUnitVentilator_Impl::setMinimumOutdoorAirSchedule(Schedule& schedule) {
      if (schedule.model() != model()) {
        return false;
      }
      return setPointer(ZoneHVAC_UnitVentilatorFields::MinimumOutdoorAirScheduleName, schedule.handle(), false);
    }

    Schedule ZoneHVACUnitVentilator_Impl::maximumOutdoorAirFractionorTemperatureSchedule() const {
      auto target = getObject<ModelObject>().getModelObjectTarget<Schedule>(
        ZoneHVAC_UnitVentilatorFields::MaximumOutdoorAirFractionorTemperatureScheduleName);
      OS_ASSERT(target);
      return *target;
    }

    bool ZoneHVACUnitVentilator_Impl::setMaximumOutdoorAirFractionorTemperatureSchedule(Schedule& schedule) {
      if (schedule.model() != model()) {
        return false;
      }
      return setPointer(ZoneHVAC_UnitVentilatorFields::MaximumOutdoorAirFractionorTemperatureScheduleName, schedule.handle(), false);
    }

    HVACComponent ZoneHVACUnitVentilator_Impl::supplyAirFan() const {
      auto target = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(ZoneHVAC_UnitVentilatorFields::SupplyAirFanName);
      OS_ASSERT(target);
      return *target;
    }

    bool ZoneHVACUnitVentilator_Impl::setSupplyAirFan(const HVACComponent& supplyAirFan) {
      if (supplyAirFan.model() != model()) {
        return false;
      }
      return setPointer(ZoneHVAC_UnitVentilatorFields::SupplyAirFanName, supplyAirFan.handle(), false);
    }

    boost::optional<Schedule> ZoneHVACUnitVentilator_Impl::supplyAirFanOperatingModeSchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(ZoneHVAC_UnitVentilatorFields::SupplyAirFanOperatingModeScheduleName);
    }

    bool ZoneHVACUnitVentilator_Impl::setSupplyAirFanOperatingModeSchedule(Schedule& schedule) {
      return ModelObject_Impl::setSchedule(ZoneHVAC_UnitVentilatorFields::SupplyAirFanOperatingModeScheduleName, "ZoneHVACUnitVentilator",
                                           "Supply Air Fan Operating Mode", schedule);
    }

    void ZoneHVACUnitVentilator_Impl::resetSupplyAirFanOperatingModeSchedule() {
      OS_ASSERT(setString(ZoneHVAC_UnitVentilatorFields::SupplyAirFanOperatingModeScheduleName, ""));
    }

    boost::optional<HVACComponent> ZoneHVACUnitVentilator_Impl::heatingCoil() const {
      return getObject<ModelObject>().getModelObjectTarget<HVACComponent>(ZoneHVAC_UnitVentilatorFields::HeatingCoilName);
    }

    bool ZoneHVACUnitVentilator_Impl::setHeatingCoil(const HVACComponent& heatingCoil) {
      if (heatingCoil.model() != model()) {
        return false;
      }
      return setPointer(ZoneHVAC_UnitVentilatorFields::HeatingCoilName, heatingCoil.handle(), false);
    }

    void ZoneHVACUnitVentilator_Impl::resetHeatingCoil() {
      OS_ASSERT(setString(ZoneHVAC_UnitVentilatorFields::HeatingCoilName, ""));
    }

    boost::optional<HVACComponent> ZoneHVACUnitVentilator_Impl::coolingCoil() const {
      return getObject<ModelObject>().getModelObjectTarget<HVACComponent>(ZoneHVAC_UnitVentilatorFields::CoolingCoilName);
    }

    bool ZoneHVACUnitVentilator_Impl::setCoolingCoil(const HVACComponent& coolingCoil) {
      if (coolingCoil.model() != model()) {
        return false;
      }
      return setPointer(ZoneHVAC_UnitVentilatorFields::CoolingCoilName, coolingCoil.handle(), false);
    }

    void ZoneHVACUnitVentilator_Impl::resetCoolingCoil() {
      OS_ASSERT(setString(ZoneHVAC_UnitVentilatorFields::CoolingCoilName, ""));
    }

    boost::optional<double> ZoneHVACUnitVentilator_Impl::autosizedMinimumOutdoorAirFlowRate() const {
      return boost::none;
    }

    boost::optional<double> ZoneHVACUnitVentilator_Impl::autosizedMaximumOutdoorAirFlowRate() const {
      return boost::none;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
