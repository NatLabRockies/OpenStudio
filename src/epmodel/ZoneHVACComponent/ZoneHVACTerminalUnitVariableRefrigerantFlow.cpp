/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include "ZoneHVACComponent/ZoneHVACTerminalUnitVariableRefrigerantFlow.hpp"
#include "ZoneHVACComponent/ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl.hpp"

#include "HVACComponent/ThermalZone.hpp"
#include "HVACComponent/ThermalZone_Impl.hpp"
#include "Model.hpp"
#include "ModelObject.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"
#include "Schedule/ScheduleConstant.hpp"

#include "../utilities/core/Assert.hpp"

#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/ZoneHVAC_TerminalUnit_VariableRefrigerantFlow_FieldEnums.hxx>
#include <utility>

namespace openstudio {
namespace epmodel {

  ZoneHVACTerminalUnitVariableRefrigerantFlow::ZoneHVACTerminalUnitVariableRefrigerantFlow(const Model& model)
    : ZoneHVACComponent(ZoneHVACTerminalUnitVariableRefrigerantFlow::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl>());
    ScheduleConstant alwaysOn(model);
    OS_ASSERT(alwaysOn.setValue(1.0));
    OS_ASSERT(setTerminalUnitAvailabilityschedule(alwaysOn));
    OS_ASSERT(setSupplyAirFanOperatingModeSchedule(alwaysOn));
  }

  ZoneHVACTerminalUnitVariableRefrigerantFlow::ZoneHVACTerminalUnitVariableRefrigerantFlow(
    std::shared_ptr<detail::ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl> impl)
    : ZoneHVACComponent(std::move(impl)) {}

  IddObjectType ZoneHVACTerminalUnitVariableRefrigerantFlow::iddObjectType() {
    return IddObjectType::ZoneHVAC_TerminalUnit_VariableRefrigerantFlow;
  }

  std::vector<std::string> ZoneHVACTerminalUnitVariableRefrigerantFlow::supplyAirFanPlacementValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::SupplyAirFanPlacement);
  }

  Schedule ZoneHVACTerminalUnitVariableRefrigerantFlow::terminalUnitAvailabilityschedule() const {
    return getImpl<detail::ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl>()->terminalUnitAvailabilityschedule();
  }

  bool ZoneHVACTerminalUnitVariableRefrigerantFlow::setTerminalUnitAvailabilityschedule(Schedule& schedule) {
    return getImpl<detail::ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl>()->setTerminalUnitAvailabilityschedule(schedule);
  }

  namespace {

    const detail::ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl* impl(const ZoneHVACTerminalUnitVariableRefrigerantFlow* object) {
      return object->getImpl<detail::ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl>().get();
    }

    detail::ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl* impl(ZoneHVACTerminalUnitVariableRefrigerantFlow* object) {
      return object->getImpl<detail::ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl>().get();
    }

  }  // namespace

  boost::optional<double> ZoneHVACTerminalUnitVariableRefrigerantFlow::supplyAirFlowRateDuringCoolingOperation() const {
    return impl(this)->supplyAirFlowRateDuringCoolingOperation();
  }

  bool ZoneHVACTerminalUnitVariableRefrigerantFlow::isSupplyAirFlowRateDuringCoolingOperationAutosized() const {
    return impl(this)->isSupplyAirFlowRateDuringCoolingOperationAutosized();
  }

  bool ZoneHVACTerminalUnitVariableRefrigerantFlow::setSupplyAirFlowRateDuringCoolingOperation(double supplyAirFlowRateDuringCoolingOperation) {
    return impl(this)->setSupplyAirFlowRateDuringCoolingOperation(supplyAirFlowRateDuringCoolingOperation);
  }

  void ZoneHVACTerminalUnitVariableRefrigerantFlow::autosizeSupplyAirFlowRateDuringCoolingOperation() {
    impl(this)->autosizeSupplyAirFlowRateDuringCoolingOperation();
  }

  boost::optional<double> ZoneHVACTerminalUnitVariableRefrigerantFlow::supplyAirFlowRateWhenNoCoolingisNeeded() const {
    return impl(this)->supplyAirFlowRateWhenNoCoolingisNeeded();
  }

  bool ZoneHVACTerminalUnitVariableRefrigerantFlow::isSupplyAirFlowRateWhenNoCoolingisNeededAutosized() const {
    return impl(this)->isSupplyAirFlowRateWhenNoCoolingisNeededAutosized();
  }

  bool ZoneHVACTerminalUnitVariableRefrigerantFlow::setSupplyAirFlowRateWhenNoCoolingisNeeded(double supplyAirFlowRateWhenNoCoolingisNeeded) {
    return impl(this)->setSupplyAirFlowRateWhenNoCoolingisNeeded(supplyAirFlowRateWhenNoCoolingisNeeded);
  }

  void ZoneHVACTerminalUnitVariableRefrigerantFlow::resetSupplyAirFlowRateWhenNoCoolingisNeeded() {
    impl(this)->resetSupplyAirFlowRateWhenNoCoolingisNeeded();
  }

  void ZoneHVACTerminalUnitVariableRefrigerantFlow::autosizeSupplyAirFlowRateWhenNoCoolingisNeeded() {
    impl(this)->autosizeSupplyAirFlowRateWhenNoCoolingisNeeded();
  }

  boost::optional<double> ZoneHVACTerminalUnitVariableRefrigerantFlow::supplyAirFlowRateDuringHeatingOperation() const {
    return impl(this)->supplyAirFlowRateDuringHeatingOperation();
  }

  bool ZoneHVACTerminalUnitVariableRefrigerantFlow::isSupplyAirFlowRateDuringHeatingOperationAutosized() const {
    return impl(this)->isSupplyAirFlowRateDuringHeatingOperationAutosized();
  }

  bool ZoneHVACTerminalUnitVariableRefrigerantFlow::setSupplyAirFlowRateDuringHeatingOperation(double supplyAirFlowRateDuringHeatingOperation) {
    return impl(this)->setSupplyAirFlowRateDuringHeatingOperation(supplyAirFlowRateDuringHeatingOperation);
  }

  void ZoneHVACTerminalUnitVariableRefrigerantFlow::autosizeSupplyAirFlowRateDuringHeatingOperation() {
    impl(this)->autosizeSupplyAirFlowRateDuringHeatingOperation();
  }

  boost::optional<double> ZoneHVACTerminalUnitVariableRefrigerantFlow::supplyAirFlowRateWhenNoHeatingisNeeded() const {
    return impl(this)->supplyAirFlowRateWhenNoHeatingisNeeded();
  }

  bool ZoneHVACTerminalUnitVariableRefrigerantFlow::isSupplyAirFlowRateWhenNoHeatingisNeededAutosized() const {
    return impl(this)->isSupplyAirFlowRateWhenNoHeatingisNeededAutosized();
  }

  bool ZoneHVACTerminalUnitVariableRefrigerantFlow::setSupplyAirFlowRateWhenNoHeatingisNeeded(double supplyAirFlowRateWhenNoHeatingisNeeded) {
    return impl(this)->setSupplyAirFlowRateWhenNoHeatingisNeeded(supplyAirFlowRateWhenNoHeatingisNeeded);
  }

  void ZoneHVACTerminalUnitVariableRefrigerantFlow::resetSupplyAirFlowRateWhenNoHeatingisNeeded() {
    impl(this)->resetSupplyAirFlowRateWhenNoHeatingisNeeded();
  }

  void ZoneHVACTerminalUnitVariableRefrigerantFlow::autosizeSupplyAirFlowRateWhenNoHeatingisNeeded() {
    impl(this)->autosizeSupplyAirFlowRateWhenNoHeatingisNeeded();
  }

  boost::optional<double> ZoneHVACTerminalUnitVariableRefrigerantFlow::outdoorAirFlowRateDuringCoolingOperation() const {
    return impl(this)->outdoorAirFlowRateDuringCoolingOperation();
  }

  bool ZoneHVACTerminalUnitVariableRefrigerantFlow::isOutdoorAirFlowRateDuringCoolingOperationAutosized() const {
    return impl(this)->isOutdoorAirFlowRateDuringCoolingOperationAutosized();
  }

  bool ZoneHVACTerminalUnitVariableRefrigerantFlow::setOutdoorAirFlowRateDuringCoolingOperation(double outdoorAirFlowRateDuringCoolingOperation) {
    return impl(this)->setOutdoorAirFlowRateDuringCoolingOperation(outdoorAirFlowRateDuringCoolingOperation);
  }

  void ZoneHVACTerminalUnitVariableRefrigerantFlow::autosizeOutdoorAirFlowRateDuringCoolingOperation() {
    impl(this)->autosizeOutdoorAirFlowRateDuringCoolingOperation();
  }

  boost::optional<double> ZoneHVACTerminalUnitVariableRefrigerantFlow::outdoorAirFlowRateDuringHeatingOperation() const {
    return impl(this)->outdoorAirFlowRateDuringHeatingOperation();
  }

  bool ZoneHVACTerminalUnitVariableRefrigerantFlow::isOutdoorAirFlowRateDuringHeatingOperationAutosized() const {
    return impl(this)->isOutdoorAirFlowRateDuringHeatingOperationAutosized();
  }

  bool ZoneHVACTerminalUnitVariableRefrigerantFlow::setOutdoorAirFlowRateDuringHeatingOperation(double outdoorAirFlowRateDuringHeatingOperation) {
    return impl(this)->setOutdoorAirFlowRateDuringHeatingOperation(outdoorAirFlowRateDuringHeatingOperation);
  }

  void ZoneHVACTerminalUnitVariableRefrigerantFlow::autosizeOutdoorAirFlowRateDuringHeatingOperation() {
    impl(this)->autosizeOutdoorAirFlowRateDuringHeatingOperation();
  }

  boost::optional<double> ZoneHVACTerminalUnitVariableRefrigerantFlow::outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() const {
    return impl(this)->outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded();
  }

  bool ZoneHVACTerminalUnitVariableRefrigerantFlow::isOutdoorAirFlowRateWhenNoCoolingorHeatingisNeededAutosized() const {
    return impl(this)->isOutdoorAirFlowRateWhenNoCoolingorHeatingisNeededAutosized();
  }

  bool ZoneHVACTerminalUnitVariableRefrigerantFlow::setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(
    double outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded) {
    return impl(this)->setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded);
  }

  void ZoneHVACTerminalUnitVariableRefrigerantFlow::resetOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() {
    impl(this)->resetOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded();
  }

  void ZoneHVACTerminalUnitVariableRefrigerantFlow::autosizeOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() {
    impl(this)->autosizeOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded();
  }

  double ZoneHVACTerminalUnitVariableRefrigerantFlow::zoneTerminalUnitOnParasiticElectricEnergyUse() const {
    return impl(this)->zoneTerminalUnitOnParasiticElectricEnergyUse();
  }

  bool ZoneHVACTerminalUnitVariableRefrigerantFlow::setZoneTerminalUnitOnParasiticElectricEnergyUse(
    double zoneTerminalUnitOnParasiticElectricEnergyUse) {
    return impl(this)->setZoneTerminalUnitOnParasiticElectricEnergyUse(zoneTerminalUnitOnParasiticElectricEnergyUse);
  }

  double ZoneHVACTerminalUnitVariableRefrigerantFlow::zoneTerminalUnitOffParasiticElectricEnergyUse() const {
    return impl(this)->zoneTerminalUnitOffParasiticElectricEnergyUse();
  }

  bool ZoneHVACTerminalUnitVariableRefrigerantFlow::setZoneTerminalUnitOffParasiticElectricEnergyUse(
    double zoneTerminalUnitOffParasiticElectricEnergyUse) {
    return impl(this)->setZoneTerminalUnitOffParasiticElectricEnergyUse(zoneTerminalUnitOffParasiticElectricEnergyUse);
  }

  double ZoneHVACTerminalUnitVariableRefrigerantFlow::ratedTotalHeatingCapacitySizingRatio() const {
    return impl(this)->ratedTotalHeatingCapacitySizingRatio();
  }

  bool ZoneHVACTerminalUnitVariableRefrigerantFlow::setRatedTotalHeatingCapacitySizingRatio(double ratedTotalHeatingCapacitySizingRatio) {
    return impl(this)->setRatedTotalHeatingCapacitySizingRatio(ratedTotalHeatingCapacitySizingRatio);
  }

  boost::optional<double> ZoneHVACTerminalUnitVariableRefrigerantFlow::maximumSupplyAirTemperaturefromSupplementalHeater() const {
    return impl(this)->maximumSupplyAirTemperaturefromSupplementalHeater();
  }

  bool ZoneHVACTerminalUnitVariableRefrigerantFlow::isMaximumSupplyAirTemperaturefromSupplementalHeaterAutosized() const {
    return impl(this)->isMaximumSupplyAirTemperaturefromSupplementalHeaterAutosized();
  }

  bool ZoneHVACTerminalUnitVariableRefrigerantFlow::setMaximumSupplyAirTemperaturefromSupplementalHeater(
    double maximumSupplyAirTemperaturefromSupplementalHeater) {
    return impl(this)->setMaximumSupplyAirTemperaturefromSupplementalHeater(maximumSupplyAirTemperaturefromSupplementalHeater);
  }

  void ZoneHVACTerminalUnitVariableRefrigerantFlow::autosizeMaximumSupplyAirTemperaturefromSupplementalHeater() {
    impl(this)->autosizeMaximumSupplyAirTemperaturefromSupplementalHeater();
  }

  double ZoneHVACTerminalUnitVariableRefrigerantFlow::maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation() const {
    return impl(this)->maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation();
  }

  bool ZoneHVACTerminalUnitVariableRefrigerantFlow::isMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperationDefaulted() const {
    return impl(this)->isMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperationDefaulted();
  }

  bool ZoneHVACTerminalUnitVariableRefrigerantFlow::setMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation(
    double maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation) {
    return impl(this)->setMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation(
      maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation);
  }

  void ZoneHVACTerminalUnitVariableRefrigerantFlow::resetMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation() {
    impl(this)->resetMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation();
  }

  std::string ZoneHVACTerminalUnitVariableRefrigerantFlow::supplyAirFanPlacement() const {
    return impl(this)->supplyAirFanPlacement();
  }

  bool ZoneHVACTerminalUnitVariableRefrigerantFlow::isSupplyAirFanPlacementDefaulted() const {
    return impl(this)->isSupplyAirFanPlacementDefaulted();
  }

  bool ZoneHVACTerminalUnitVariableRefrigerantFlow::setSupplyAirFanPlacement(const std::string& supplyAirFanPlacement) {
    return impl(this)->setSupplyAirFanPlacement(supplyAirFanPlacement);
  }

  void ZoneHVACTerminalUnitVariableRefrigerantFlow::resetSupplyAirFanPlacement() {
    impl(this)->resetSupplyAirFanPlacement();
  }

  HVACComponent ZoneHVACTerminalUnitVariableRefrigerantFlow::supplyAirFan() const {
    return impl(this)->supplyAirFan();
  }

  bool ZoneHVACTerminalUnitVariableRefrigerantFlow::setSupplyAirFan(HVACComponent& fan) {
    return impl(this)->setSupplyAirFan(fan);
  }

  Schedule ZoneHVACTerminalUnitVariableRefrigerantFlow::supplyAirFanOperatingModeSchedule() const {
    return impl(this)->supplyAirFanOperatingModeSchedule();
  }

  bool ZoneHVACTerminalUnitVariableRefrigerantFlow::setSupplyAirFanOperatingModeSchedule(Schedule& schedule) {
    return impl(this)->setSupplyAirFanOperatingModeSchedule(schedule);
  }

  boost::optional<HVACComponent> ZoneHVACTerminalUnitVariableRefrigerantFlow::coolingCoil() const {
    return impl(this)->coolingCoil();
  }

  bool ZoneHVACTerminalUnitVariableRefrigerantFlow::setCoolingCoil(HVACComponent& coil) {
    return impl(this)->setCoolingCoil(coil);
  }

  boost::optional<HVACComponent> ZoneHVACTerminalUnitVariableRefrigerantFlow::heatingCoil() const {
    return impl(this)->heatingCoil();
  }

  bool ZoneHVACTerminalUnitVariableRefrigerantFlow::setHeatingCoil(HVACComponent& coil) {
    return impl(this)->setHeatingCoil(coil);
  }

  boost::optional<HVACComponent> ZoneHVACTerminalUnitVariableRefrigerantFlow::supplementalHeatingCoil() const {
    return impl(this)->supplementalHeatingCoil();
  }

  bool ZoneHVACTerminalUnitVariableRefrigerantFlow::setSupplementalHeatingCoil(HVACComponent& coil) {
    return impl(this)->setSupplementalHeatingCoil(coil);
  }

  void ZoneHVACTerminalUnitVariableRefrigerantFlow::resetSupplementalHeatingCoil() {
    impl(this)->resetSupplementalHeatingCoil();
  }

  boost::optional<ThermalZone> ZoneHVACTerminalUnitVariableRefrigerantFlow::controllingZoneorThermostatLocation() const {
    return impl(this)->controllingZoneorThermostatLocation();
  }

  bool ZoneHVACTerminalUnitVariableRefrigerantFlow::setControllingZoneorThermostatLocation(const ThermalZone& thermalZone) {
    return impl(this)->setControllingZoneorThermostatLocation(thermalZone);
  }

  void ZoneHVACTerminalUnitVariableRefrigerantFlow::resetControllingZoneorThermostatLocation() {
    impl(this)->resetControllingZoneorThermostatLocation();
  }

  std::vector<ModelObject> ZoneHVACTerminalUnitVariableRefrigerantFlow::children() const {
    return impl(this)->children();
  }

  namespace detail {

    Schedule ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::terminalUnitAvailabilityschedule() const {
      auto schedule = getObject<ModelObject>().getModelObjectTarget<Schedule>(
        ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::TerminalUnitAvailabilitySchedule);
      OS_ASSERT(schedule);
      return *schedule;
    }

    bool ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::setTerminalUnitAvailabilityschedule(Schedule& schedule) {
      return ModelObject_Impl::setSchedule(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::TerminalUnitAvailabilitySchedule,
                                           "ZoneHVACTerminalUnitVariableRefrigerantFlow", "Terminal Unit Availability", schedule);
    }

    boost::optional<double> ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::supplyAirFlowRateDuringCoolingOperation() const {
      return getDouble(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::CoolingSupplyAirFlowRate, true);
    }

    bool ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::isSupplyAirFlowRateDuringCoolingOperationAutosized() const {
      bool result = false;
      boost::optional<std::string> value = getString(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::CoolingSupplyAirFlowRate, true);
      if (value) {
        result = openstudio::istringEqual(value.get(), "Autosize");
      }
      return result;
    }

    bool ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::setSupplyAirFlowRateDuringCoolingOperation(
      boost::optional<double> supplyAirFlowRateDuringCoolingOperation) {
      const bool result = supplyAirFlowRateDuringCoolingOperation
                            ? setDouble(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::CoolingSupplyAirFlowRate,
                                        supplyAirFlowRateDuringCoolingOperation.get(), false)
                            : setString(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::CoolingSupplyAirFlowRate, "", false);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::autosizeSupplyAirFlowRateDuringCoolingOperation() {
      bool result = setString(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::CoolingSupplyAirFlowRate, "Autosize", false);
      OS_ASSERT(result);
    }

    // epmodel does not currently resolve autosized values from SQL results.
    boost::optional<double> ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::autosizedSupplyAirFlowRateDuringCoolingOperation() const {
      return boost::none;
    }

    boost::optional<double> ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::supplyAirFlowRateWhenNoCoolingisNeeded() const {
      return getDouble(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::NoCoolingSupplyAirFlowRate, true);
    }

    bool ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::isSupplyAirFlowRateWhenNoCoolingisNeededAutosized() const {
      bool result = false;
      boost::optional<std::string> value = getString(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::NoCoolingSupplyAirFlowRate, true);
      if (value) {
        result = openstudio::istringEqual(value.get(), "Autosize");
      }
      return result;
    }

    bool ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::setSupplyAirFlowRateWhenNoCoolingisNeeded(
      boost::optional<double> supplyAirFlowRateWhenNoCoolingisNeeded) {
      const bool result = supplyAirFlowRateWhenNoCoolingisNeeded
                            ? setDouble(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::NoCoolingSupplyAirFlowRate,
                                        supplyAirFlowRateWhenNoCoolingisNeeded.get(), false)
                            : setString(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::NoCoolingSupplyAirFlowRate, "", false);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::resetSupplyAirFlowRateWhenNoCoolingisNeeded() {
      bool result = setString(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::NoCoolingSupplyAirFlowRate, "", false);
      OS_ASSERT(result);
    }

    void ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::autosizeSupplyAirFlowRateWhenNoCoolingisNeeded() {
      bool result = setString(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::NoCoolingSupplyAirFlowRate, "Autosize", false);
      OS_ASSERT(result);
    }

    boost::optional<double> ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::autosizedSupplyAirFlowRateWhenNoCoolingisNeeded() const {
      return boost::none;
    }

    boost::optional<double> ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::supplyAirFlowRateDuringHeatingOperation() const {
      return getDouble(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::HeatingSupplyAirFlowRate, true);
    }

    bool ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::isSupplyAirFlowRateDuringHeatingOperationAutosized() const {
      bool result = false;
      boost::optional<std::string> value = getString(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::HeatingSupplyAirFlowRate, true);
      if (value) {
        result = openstudio::istringEqual(value.get(), "Autosize");
      }
      return result;
    }

    bool ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::setSupplyAirFlowRateDuringHeatingOperation(
      boost::optional<double> supplyAirFlowRateDuringHeatingOperation) {
      const bool result = supplyAirFlowRateDuringHeatingOperation
                            ? setDouble(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::HeatingSupplyAirFlowRate,
                                        supplyAirFlowRateDuringHeatingOperation.get(), false)
                            : setString(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::HeatingSupplyAirFlowRate, "", false);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::autosizeSupplyAirFlowRateDuringHeatingOperation() {
      bool result = setString(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::HeatingSupplyAirFlowRate, "Autosize", false);
      OS_ASSERT(result);
    }

    boost::optional<double> ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::autosizedSupplyAirFlowRateDuringHeatingOperation() const {
      return boost::none;
    }

    boost::optional<double> ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::supplyAirFlowRateWhenNoHeatingisNeeded() const {
      return getDouble(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::NoHeatingSupplyAirFlowRate, true);
    }

    bool ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::isSupplyAirFlowRateWhenNoHeatingisNeededAutosized() const {
      bool result = false;
      boost::optional<std::string> value = getString(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::NoHeatingSupplyAirFlowRate, true);
      if (value) {
        result = openstudio::istringEqual(value.get(), "Autosize");
      }
      return result;
    }

    bool ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::setSupplyAirFlowRateWhenNoHeatingisNeeded(
      boost::optional<double> supplyAirFlowRateWhenNoHeatingisNeeded) {
      const bool result = supplyAirFlowRateWhenNoHeatingisNeeded
                            ? setDouble(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::NoHeatingSupplyAirFlowRate,
                                        supplyAirFlowRateWhenNoHeatingisNeeded.get(), false)
                            : setString(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::NoHeatingSupplyAirFlowRate, "", false);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::resetSupplyAirFlowRateWhenNoHeatingisNeeded() {
      bool result = setString(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::NoHeatingSupplyAirFlowRate, "", false);
      OS_ASSERT(result);
    }

    void ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::autosizeSupplyAirFlowRateWhenNoHeatingisNeeded() {
      bool result = setString(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::NoHeatingSupplyAirFlowRate, "Autosize", false);
      OS_ASSERT(result);
    }

    boost::optional<double> ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::autosizedSupplyAirFlowRateWhenNoHeatingisNeeded() const {
      return boost::none;
    }

    boost::optional<double> ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::outdoorAirFlowRateDuringCoolingOperation() const {
      return getDouble(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::CoolingOutdoorAirFlowRate, true);
    }

    bool ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::isOutdoorAirFlowRateDuringCoolingOperationAutosized() const {
      bool result = false;
      boost::optional<std::string> value = getString(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::CoolingOutdoorAirFlowRate, true);
      if (value) {
        result = openstudio::istringEqual(value.get(), "Autosize");
      }
      return result;
    }

    bool ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::setOutdoorAirFlowRateDuringCoolingOperation(
      boost::optional<double> outdoorAirFlowRateDuringCoolingOperation) {
      const bool result = outdoorAirFlowRateDuringCoolingOperation
                            ? setDouble(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::CoolingOutdoorAirFlowRate,
                                        outdoorAirFlowRateDuringCoolingOperation.get(), false)
                            : setString(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::CoolingOutdoorAirFlowRate, "", false);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::autosizeOutdoorAirFlowRateDuringCoolingOperation() {
      bool result = setString(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::CoolingOutdoorAirFlowRate, "Autosize", false);
      OS_ASSERT(result);
    }

    boost::optional<double> ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::autosizedOutdoorAirFlowRateDuringCoolingOperation() const {
      return boost::none;
    }

    boost::optional<double> ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::outdoorAirFlowRateDuringHeatingOperation() const {
      return getDouble(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::HeatingOutdoorAirFlowRate, true);
    }

    bool ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::isOutdoorAirFlowRateDuringHeatingOperationAutosized() const {
      bool result = false;
      boost::optional<std::string> value = getString(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::HeatingOutdoorAirFlowRate, true);
      if (value) {
        result = openstudio::istringEqual(value.get(), "Autosize");
      }
      return result;
    }

    bool ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::setOutdoorAirFlowRateDuringHeatingOperation(
      boost::optional<double> outdoorAirFlowRateDuringHeatingOperation) {
      const bool result = outdoorAirFlowRateDuringHeatingOperation
                            ? setDouble(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::HeatingOutdoorAirFlowRate,
                                        outdoorAirFlowRateDuringHeatingOperation.get(), false)
                            : setString(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::HeatingOutdoorAirFlowRate, "", false);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::autosizeOutdoorAirFlowRateDuringHeatingOperation() {
      bool result = setString(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::HeatingOutdoorAirFlowRate, "Autosize", false);
      OS_ASSERT(result);
    }

    boost::optional<double> ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::autosizedOutdoorAirFlowRateDuringHeatingOperation() const {
      return boost::none;
    }

    boost::optional<double> ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() const {
      return getDouble(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::NoLoadOutdoorAirFlowRate, true);
    }

    bool ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::isOutdoorAirFlowRateWhenNoCoolingorHeatingisNeededAutosized() const {
      bool result = false;
      boost::optional<std::string> value = getString(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::NoLoadOutdoorAirFlowRate, true);
      if (value) {
        result = openstudio::istringEqual(value.get(), "Autosize");
      }
      return result;
    }

    bool ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(
      boost::optional<double> outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded) {
      const bool result = outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded
                            ? setDouble(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::NoLoadOutdoorAirFlowRate,
                                        outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded.get(), false)
                            : setString(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::NoLoadOutdoorAirFlowRate, "", false);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::resetOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() {
      bool result = setString(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::NoLoadOutdoorAirFlowRate, "", false);
      OS_ASSERT(result);
    }

    void ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::autosizeOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() {
      bool result = setString(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::NoLoadOutdoorAirFlowRate, "Autosize", false);
      OS_ASSERT(result);
    }

    boost::optional<double> ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::autosizedOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() const {
      return boost::none;
    }

    double ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::zoneTerminalUnitOnParasiticElectricEnergyUse() const {
      boost::optional<double> value =
        getDouble(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::ZoneTerminalUnitOnParasiticElectricEnergyUse, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::setZoneTerminalUnitOnParasiticElectricEnergyUse(
      double zoneTerminalUnitOnParasiticElectricEnergyUse) {
      bool result = setDouble(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::ZoneTerminalUnitOnParasiticElectricEnergyUse,
                              zoneTerminalUnitOnParasiticElectricEnergyUse, false);
      OS_ASSERT(result);
      return result;
    }

    double ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::zoneTerminalUnitOffParasiticElectricEnergyUse() const {
      boost::optional<double> value =
        getDouble(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::ZoneTerminalUnitOffParasiticElectricEnergyUse, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::setZoneTerminalUnitOffParasiticElectricEnergyUse(
      double zoneTerminalUnitOffParasiticElectricEnergyUse) {
      bool result = setDouble(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::ZoneTerminalUnitOffParasiticElectricEnergyUse,
                              zoneTerminalUnitOffParasiticElectricEnergyUse, false);
      OS_ASSERT(result);
      return result;
    }

    double ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::ratedTotalHeatingCapacitySizingRatio() const {
      boost::optional<double> value = getDouble(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::RatedHeatingCapacitySizingRatio, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::setRatedTotalHeatingCapacitySizingRatio(double ratedTotalHeatingCapacitySizingRatio) {
      bool result =
        setDouble(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::RatedHeatingCapacitySizingRatio, ratedTotalHeatingCapacitySizingRatio, false);
      OS_ASSERT(result);
      return result;
    }

    boost::optional<double> ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::maximumSupplyAirTemperaturefromSupplementalHeater() const {
      return getDouble(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::MaximumSupplyAirTemperaturefromSupplementalHeater, false);
    }

    bool ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::isMaximumSupplyAirTemperaturefromSupplementalHeaterAutosized() const {
      bool result = false;
      boost::optional<std::string> value =
        getString(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::MaximumSupplyAirTemperaturefromSupplementalHeater, true);
      if (value) {
        result = openstudio::istringEqual(value.get(), "Autosize");
      }
      return result;
    }

    bool ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::setMaximumSupplyAirTemperaturefromSupplementalHeater(
      double maximumSupplyAirTemperaturefromSupplementalHeater) {
      bool result = setDouble(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::MaximumSupplyAirTemperaturefromSupplementalHeater,
                              maximumSupplyAirTemperaturefromSupplementalHeater, false);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::autosizeMaximumSupplyAirTemperaturefromSupplementalHeater() {
      bool result =
        setString(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::MaximumSupplyAirTemperaturefromSupplementalHeater, "Autosize", false);
      OS_ASSERT(result);
    }

    double ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation() const {
      boost::optional<double> value =
        getDouble(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::MaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::isMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperationDefaulted() const {
      return isEmpty(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::MaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation);
    }

    bool ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::setMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation(
      double maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation) {
      bool result = setDouble(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::MaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation,
                              maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation, false);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::resetMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation() {
      bool result =
        setString(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::MaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation, "", false);
      OS_ASSERT(result);
    }

    std::string ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::supplyAirFanPlacement() const {
      auto value = getString(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::SupplyAirFanPlacement);
      if (!value) {
        return {};
      }
      return value.get();
    }

    bool ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::isSupplyAirFanPlacementDefaulted() const {
      return isEmpty(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::SupplyAirFanPlacement);
    }

    bool ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::setSupplyAirFanPlacement(const std::string& supplyAirFanPlacement) {
      bool result = setString(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::SupplyAirFanPlacement, supplyAirFanPlacement, false);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::resetSupplyAirFanPlacement() {
      bool result = setString(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::SupplyAirFanPlacement, "", false);
      OS_ASSERT(result);
    }

    HVACComponent ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::supplyAirFan() const {
      auto fan = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::SupplyAirFanObjectName);
      OS_ASSERT(fan);
      return *fan;
    }

    bool ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::setSupplyAirFan(HVACComponent& fan) {
      return setPointer(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::SupplyAirFanObjectName, fan.handle());
    }

    Schedule ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::supplyAirFanOperatingModeSchedule() const {
      auto schedule = getObject<ModelObject>().getModelObjectTarget<Schedule>(
        ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::SupplyAirFanOperatingModeScheduleName);
      OS_ASSERT(schedule);
      return *schedule;
    }

    bool ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::setSupplyAirFanOperatingModeSchedule(Schedule& schedule) {
      return ModelObject_Impl::setSchedule(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::SupplyAirFanOperatingModeScheduleName,
                                           "ZoneHVACTerminalUnitVariableRefrigerantFlow", "Supply Air Fan Operating Mode", schedule);
    }

    boost::optional<HVACComponent> ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::coolingCoil() const {
      return getObject<ModelObject>().getModelObjectTarget<HVACComponent>(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::CoolingCoilObjectName);
    }

    bool ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::setCoolingCoil(HVACComponent& coil) {
      return setPointer(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::CoolingCoilObjectName, coil.handle());
    }

    boost::optional<HVACComponent> ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::heatingCoil() const {
      return getObject<ModelObject>().getModelObjectTarget<HVACComponent>(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::HeatingCoilObjectName);
    }

    bool ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::setHeatingCoil(HVACComponent& coil) {
      return setPointer(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::HeatingCoilObjectName, coil.handle());
    }

    boost::optional<HVACComponent> ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::supplementalHeatingCoil() const {
      return getObject<ModelObject>().getModelObjectTarget<HVACComponent>(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::SupplementalHeatingCoilName);
    }

    bool ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::setSupplementalHeatingCoil(HVACComponent& coil) {
      return setPointer(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::SupplementalHeatingCoilName, coil.handle());
    }

    void ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::resetSupplementalHeatingCoil() {
      bool result = setPointer(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::SupplementalHeatingCoilName, Handle());
      OS_ASSERT(result);
    }

    boost::optional<ThermalZone> ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::controllingZoneorThermostatLocation() const {
      return getObject<ModelObject>().getModelObjectTarget<ThermalZone>(
        ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::ControllingZoneorThermostatLocation);
    }

    bool ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::setControllingZoneorThermostatLocation(const ThermalZone& thermalZone) {
      if (thermalZone.model() != model()) {
        return false;
      }
      return setPointer(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::ControllingZoneorThermostatLocation, thermalZone.handle(), false);
    }

    void ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::resetControllingZoneorThermostatLocation() {
      OS_ASSERT(setString(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::ControllingZoneorThermostatLocation, ""));
    }

    std::vector<ModelObject> ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::children() const {
      std::vector<ModelObject> result;

      if (auto fan = getObject<ModelObject>().getTarget(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::SupplyAirFanObjectName)) {
        if (auto mo = model().getModelObject<ModelObject>(fan->handle())) {
          result.push_back(*mo);
        }
      }
      if (auto coil = getObject<ModelObject>().getTarget(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::CoolingCoilObjectName)) {
        if (auto mo = model().getModelObject<ModelObject>(coil->handle())) {
          result.push_back(*mo);
        }
      }
      if (auto coil = getObject<ModelObject>().getTarget(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::HeatingCoilObjectName)) {
        if (auto mo = model().getModelObject<ModelObject>(coil->handle())) {
          result.push_back(*mo);
        }
      }
      if (auto coil = getObject<ModelObject>().getTarget(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::SupplementalHeatingCoilName)) {
        if (auto mo = model().getModelObject<ModelObject>(coil->handle())) {
          result.push_back(*mo);
        }
      }

      return result;
    }

    unsigned ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::inletPort() const {
      return ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::TerminalUnitAirInletNodeName;
    }

    unsigned ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::outletPort() const {
      return ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::TerminalUnitAirOutletNodeName;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
