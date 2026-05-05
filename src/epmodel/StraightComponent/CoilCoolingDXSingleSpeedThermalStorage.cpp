/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/CoilCoolingDXSingleSpeedThermalStorage.hpp"
#include "StraightComponent/CoilCoolingDXSingleSpeedThermalStorage_Impl.hpp"

#include "Loop/AirLoopHVAC.hpp"
#include "HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "Model.hpp"
#include "Node.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/Coil_Cooling_DX_SingleSpeed_ThermalStorage_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

  CoilCoolingDXSingleSpeedThermalStorage::CoilCoolingDXSingleSpeedThermalStorage(const Model& model)
    : StraightComponent(CoilCoolingDXSingleSpeedThermalStorage::iddObjectType(), model) {
    bool ok = true;
    auto availability = model.alwaysOnDiscreteSchedule();
    ok = setAvailabilitySchedule(availability);
    OS_ASSERT(ok);

    ok = setOperatingModeControlMethod("ScheduledModes");
    OS_ASSERT(ok);
    ok = setStorageType("Ice");
    OS_ASSERT(ok);
    ok = setGlycolConcentration(0);
    OS_ASSERT(ok);
    autosizeFluidStorageVolume();
    autosizeIceStorageCapacity();
    ok = setStorageCapacitySizingFactor(6.0);
    OS_ASSERT(ok);
    ok = setStorageTanktoAmbientUvalueTimesAreaHeatTransferCoefficient(7.913);
    OS_ASSERT(ok);
    ok = setFluidStorageTankRatingTemperature(26.7);
    OS_ASSERT(ok);
    autosizeRatedEvaporatorAirFlowRate();

    ok = setCoolingOnlyModeAvailable(false);
    OS_ASSERT(ok);
    autosizeCoolingOnlyModeRatedTotalEvaporatorCoolingCapacity();
    ok = setCoolingOnlyModeRatedSensibleHeatRatio(0.7);
    OS_ASSERT(ok);
    ok = setCoolingOnlyModeRatedCOP(3.0);
    OS_ASSERT(ok);

    ok = setCoolingAndChargeModeAvailable(false);
    OS_ASSERT(ok);
    autosizeCoolingAndChargeModeRatedTotalEvaporatorCoolingCapacity();
    ok = setCoolingAndChargeModeCapacitySizingFactor(0.5);
    OS_ASSERT(ok);
    autosizeCoolingAndChargeModeRatedStorageChargingCapacity();
    ok = setCoolingAndChargeModeStorageCapacitySizingFactor(0.5);
    OS_ASSERT(ok);
    ok = setCoolingAndChargeModeRatedSensibleHeatRatio(0.7);
    OS_ASSERT(ok);
    ok = setCoolingAndChargeModeCoolingRatedCOP(3.0);
    OS_ASSERT(ok);
    ok = setCoolingAndChargeModeChargingRatedCOP(3.0);
    OS_ASSERT(ok);

    ok = setCoolingAndDischargeModeAvailable(false);
    OS_ASSERT(ok);
    autosizeCoolingAndDischargeModeRatedTotalEvaporatorCoolingCapacity();
    ok = setCoolingAndDischargeModeEvaporatorCapacitySizingFactor(1.0);
    OS_ASSERT(ok);
    autosizeCoolingAndDischargeModeRatedStorageDischargingCapacity();
    ok = setCoolingAndDischargeModeStorageDischargeCapacitySizingFactor(1.0);
    OS_ASSERT(ok);
    ok = setCoolingAndDischargeModeRatedSensibleHeatRatio(0.7);
    OS_ASSERT(ok);
    ok = setCoolingAndDischargeModeCoolingRatedCOP(3.0);
    OS_ASSERT(ok);
    ok = setCoolingAndDischargeModeDischargingRatedCOP(3.0);
    OS_ASSERT(ok);

    ok = setChargeOnlyModeAvailable(false);
    OS_ASSERT(ok);
    autosizeChargeOnlyModeRatedStorageChargingCapacity();
    ok = setChargeOnlyModeCapacitySizingFactor(1.0);
    OS_ASSERT(ok);
    ok = setChargeOnlyModeChargingRatedCOP(3.0);
    OS_ASSERT(ok);

    ok = setDischargeOnlyModeAvailable(false);
    OS_ASSERT(ok);
    autosizeDischargeOnlyModeRatedStorageDischargingCapacity();
    ok = setDischargeOnlyModeCapacitySizingFactor(1.0);
    OS_ASSERT(ok);
    ok = setDischargeOnlyModeRatedSensibleHeatRatio(0.7);
    OS_ASSERT(ok);
    ok = setDischargeOnlyModeRatedCOP(3.0);
    OS_ASSERT(ok);

    ok = setAncillaryElectricPower(0.0);
    OS_ASSERT(ok);
    ok = setColdWeatherOperationAncillaryPower(0.0);
    OS_ASSERT(ok);

    autosizeCondenserDesignAirFlowRate();
    ok = setCondenserAirFlowSizingFactor(1.0);
    OS_ASSERT(ok);
    ok = setCondenserType("AirCooled");
    OS_ASSERT(ok);
    ok = setEvaporativeCondenserEffectiveness(0.7);
    OS_ASSERT(ok);
    ok = setEvaporativeCondenserPumpRatedPowerConsumption(0.0);
    OS_ASSERT(ok);
    ok = setBasinHeaterCapacity(0.0);
    OS_ASSERT(ok);
    ok = setBasinHeaterSetpointTemperature(2.0);
    OS_ASSERT(ok);
  }

  CoilCoolingDXSingleSpeedThermalStorage::CoilCoolingDXSingleSpeedThermalStorage(
    std::shared_ptr<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl> impl)
    : StraightComponent(std::move(impl)) {}

  IddObjectType CoilCoolingDXSingleSpeedThermalStorage::iddObjectType() {
    return IddObjectType::Coil_Cooling_DX_SingleSpeed_ThermalStorage;
  }

  std::vector<std::string> CoilCoolingDXSingleSpeedThermalStorage::operatingModeControlMethodValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::OperatingModeControlMethod);
  }

  std::vector<std::string> CoilCoolingDXSingleSpeedThermalStorage::storageTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::StorageType);
  }

  std::vector<std::string> CoilCoolingDXSingleSpeedThermalStorage::condenserTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CondenserType);
  }

  Schedule CoilCoolingDXSingleSpeedThermalStorage::availabilitySchedule() const {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->availabilitySchedule();
  }

  bool CoilCoolingDXSingleSpeedThermalStorage::setAvailabilitySchedule(Schedule& schedule) {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->setAvailabilitySchedule(schedule);
  }

  std::string CoilCoolingDXSingleSpeedThermalStorage::operatingModeControlMethod() const {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->operatingModeControlMethod();
  }
  bool CoilCoolingDXSingleSpeedThermalStorage::setOperatingModeControlMethod(const std::string& operatingModeControlMethod) {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->setOperatingModeControlMethod(operatingModeControlMethod);
  }
  boost::optional<Schedule> CoilCoolingDXSingleSpeedThermalStorage::operationModeControlSchedule() const {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->operationModeControlSchedule();
  }
  bool CoilCoolingDXSingleSpeedThermalStorage::setOperationModeControlSchedule(Schedule& schedule) {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->setOperationModeControlSchedule(schedule);
  }
  void CoilCoolingDXSingleSpeedThermalStorage::resetOperationModeControlSchedule() {
    getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->resetOperationModeControlSchedule();
  }
  std::string CoilCoolingDXSingleSpeedThermalStorage::storageType() const {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->storageType();
  }
  bool CoilCoolingDXSingleSpeedThermalStorage::setStorageType(const std::string& storageType) {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->setStorageType(storageType);
  }
  int CoilCoolingDXSingleSpeedThermalStorage::glycolConcentration() const {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->glycolConcentration();
  }
  bool CoilCoolingDXSingleSpeedThermalStorage::setGlycolConcentration(int glycolConcentration) {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->setGlycolConcentration(glycolConcentration);
  }
  boost::optional<double> CoilCoolingDXSingleSpeedThermalStorage::fluidStorageVolume() const {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->fluidStorageVolume();
  }
  bool CoilCoolingDXSingleSpeedThermalStorage::isFluidStorageVolumeAutosized() const {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->isFluidStorageVolumeAutosized();
  }
  bool CoilCoolingDXSingleSpeedThermalStorage::setFluidStorageVolume(double fluidStorageVolume) {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->setFluidStorageVolume(fluidStorageVolume);
  }
  void CoilCoolingDXSingleSpeedThermalStorage::resetFluidStorageVolume() {
    getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->resetFluidStorageVolume();
  }
  void CoilCoolingDXSingleSpeedThermalStorage::autosizeFluidStorageVolume() {
    getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->autosizeFluidStorageVolume();
  }
  boost::optional<double> CoilCoolingDXSingleSpeedThermalStorage::iceStorageCapacity() const {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->iceStorageCapacity();
  }
  bool CoilCoolingDXSingleSpeedThermalStorage::isIceStorageCapacityAutosized() const {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->isIceStorageCapacityAutosized();
  }
  bool CoilCoolingDXSingleSpeedThermalStorage::setIceStorageCapacity(double iceStorageCapacity) {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->setIceStorageCapacity(iceStorageCapacity);
  }
  void CoilCoolingDXSingleSpeedThermalStorage::autosizeIceStorageCapacity() {
    getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->autosizeIceStorageCapacity();
  }
  boost::optional<double> CoilCoolingDXSingleSpeedThermalStorage::storageCapacitySizingFactor() const {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->storageCapacitySizingFactor();
  }
  bool CoilCoolingDXSingleSpeedThermalStorage::setStorageCapacitySizingFactor(double storageCapacitySizingFactor) {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->setStorageCapacitySizingFactor(storageCapacitySizingFactor);
  }
  double CoilCoolingDXSingleSpeedThermalStorage::storageTanktoAmbientUvalueTimesAreaHeatTransferCoefficient() const {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->storageTanktoAmbientUvalueTimesAreaHeatTransferCoefficient();
  }
  bool CoilCoolingDXSingleSpeedThermalStorage::setStorageTanktoAmbientUvalueTimesAreaHeatTransferCoefficient(
    double storageTanktoAmbientUvalueTimesAreaHeatTransferCoefficient) {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->setStorageTanktoAmbientUvalueTimesAreaHeatTransferCoefficient(
      storageTanktoAmbientUvalueTimesAreaHeatTransferCoefficient);
  }
  double CoilCoolingDXSingleSpeedThermalStorage::fluidStorageTankRatingTemperature() const {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->fluidStorageTankRatingTemperature();
  }
  bool CoilCoolingDXSingleSpeedThermalStorage::setFluidStorageTankRatingTemperature(double fluidStorageTankRatingTemperature) {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->setFluidStorageTankRatingTemperature(fluidStorageTankRatingTemperature);
  }
  boost::optional<double> CoilCoolingDXSingleSpeedThermalStorage::ratedEvaporatorAirFlowRate() const {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->ratedEvaporatorAirFlowRate();
  }
  bool CoilCoolingDXSingleSpeedThermalStorage::isRatedEvaporatorAirFlowRateAutosized() const {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->isRatedEvaporatorAirFlowRateAutosized();
  }
  bool CoilCoolingDXSingleSpeedThermalStorage::setRatedEvaporatorAirFlowRate(double ratedEvaporatorAirFlowRate) {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->setRatedEvaporatorAirFlowRate(ratedEvaporatorAirFlowRate);
  }
  void CoilCoolingDXSingleSpeedThermalStorage::autosizeRatedEvaporatorAirFlowRate() {
    getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->autosizeRatedEvaporatorAirFlowRate();
  }
  bool CoilCoolingDXSingleSpeedThermalStorage::coolingOnlyModeAvailable() const {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->coolingOnlyModeAvailable();
  }
  bool CoilCoolingDXSingleSpeedThermalStorage::setCoolingOnlyModeAvailable(bool coolingOnlyModeAvailable) {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->setCoolingOnlyModeAvailable(coolingOnlyModeAvailable);
  }
  boost::optional<double> CoilCoolingDXSingleSpeedThermalStorage::coolingOnlyModeRatedTotalEvaporatorCoolingCapacity() const {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->coolingOnlyModeRatedTotalEvaporatorCoolingCapacity();
  }
  bool CoilCoolingDXSingleSpeedThermalStorage::isCoolingOnlyModeRatedTotalEvaporatorCoolingCapacityAutosized() const {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->isCoolingOnlyModeRatedTotalEvaporatorCoolingCapacityAutosized();
  }
  bool CoilCoolingDXSingleSpeedThermalStorage::setCoolingOnlyModeRatedTotalEvaporatorCoolingCapacity(
    double coolingOnlyModeRatedTotalEvaporatorCoolingCapacity) {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->setCoolingOnlyModeRatedTotalEvaporatorCoolingCapacity(
      coolingOnlyModeRatedTotalEvaporatorCoolingCapacity);
  }
  void CoilCoolingDXSingleSpeedThermalStorage::autosizeCoolingOnlyModeRatedTotalEvaporatorCoolingCapacity() {
    getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->autosizeCoolingOnlyModeRatedTotalEvaporatorCoolingCapacity();
  }
  double CoilCoolingDXSingleSpeedThermalStorage::coolingOnlyModeRatedSensibleHeatRatio() const {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->coolingOnlyModeRatedSensibleHeatRatio();
  }
  bool CoilCoolingDXSingleSpeedThermalStorage::setCoolingOnlyModeRatedSensibleHeatRatio(double coolingOnlyModeRatedSensibleHeatRatio) {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->setCoolingOnlyModeRatedSensibleHeatRatio(
      coolingOnlyModeRatedSensibleHeatRatio);
  }
  double CoilCoolingDXSingleSpeedThermalStorage::coolingOnlyModeRatedCOP() const {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->coolingOnlyModeRatedCOP();
  }
  bool CoilCoolingDXSingleSpeedThermalStorage::setCoolingOnlyModeRatedCOP(double coolingOnlyModeRatedCOP) {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->setCoolingOnlyModeRatedCOP(coolingOnlyModeRatedCOP);
  }
  bool CoilCoolingDXSingleSpeedThermalStorage::coolingAndChargeModeAvailable() const {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->coolingAndChargeModeAvailable();
  }
  bool CoilCoolingDXSingleSpeedThermalStorage::setCoolingAndChargeModeAvailable(bool coolingAndChargeModeAvailable) {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->setCoolingAndChargeModeAvailable(coolingAndChargeModeAvailable);
  }
  boost::optional<double> CoilCoolingDXSingleSpeedThermalStorage::coolingAndChargeModeRatedTotalEvaporatorCoolingCapacity() const {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->coolingAndChargeModeRatedTotalEvaporatorCoolingCapacity();
  }
  bool CoilCoolingDXSingleSpeedThermalStorage::isCoolingAndChargeModeRatedTotalEvaporatorCoolingCapacityAutosized() const {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->isCoolingAndChargeModeRatedTotalEvaporatorCoolingCapacityAutosized();
  }
  bool CoilCoolingDXSingleSpeedThermalStorage::setCoolingAndChargeModeRatedTotalEvaporatorCoolingCapacity(
    double coolingAndChargeModeRatedTotalEvaporatorCoolingCapacity) {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->setCoolingAndChargeModeRatedTotalEvaporatorCoolingCapacity(
      coolingAndChargeModeRatedTotalEvaporatorCoolingCapacity);
  }
  void CoilCoolingDXSingleSpeedThermalStorage::autosizeCoolingAndChargeModeRatedTotalEvaporatorCoolingCapacity() {
    getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->autosizeCoolingAndChargeModeRatedTotalEvaporatorCoolingCapacity();
  }
  double CoilCoolingDXSingleSpeedThermalStorage::coolingAndChargeModeCapacitySizingFactor() const {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->coolingAndChargeModeCapacitySizingFactor();
  }
  bool CoilCoolingDXSingleSpeedThermalStorage::setCoolingAndChargeModeCapacitySizingFactor(double coolingAndChargeModeCapacitySizingFactor) {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->setCoolingAndChargeModeCapacitySizingFactor(
      coolingAndChargeModeCapacitySizingFactor);
  }
  boost::optional<double> CoilCoolingDXSingleSpeedThermalStorage::coolingAndChargeModeRatedStorageChargingCapacity() const {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->coolingAndChargeModeRatedStorageChargingCapacity();
  }
  bool CoilCoolingDXSingleSpeedThermalStorage::isCoolingAndChargeModeRatedStorageChargingCapacityAutosized() const {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->isCoolingAndChargeModeRatedStorageChargingCapacityAutosized();
  }
  bool CoilCoolingDXSingleSpeedThermalStorage::setCoolingAndChargeModeRatedStorageChargingCapacity(
    double coolingAndChargeModeRatedStorageChargingCapacity) {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->setCoolingAndChargeModeRatedStorageChargingCapacity(
      coolingAndChargeModeRatedStorageChargingCapacity);
  }
  void CoilCoolingDXSingleSpeedThermalStorage::autosizeCoolingAndChargeModeRatedStorageChargingCapacity() {
    getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->autosizeCoolingAndChargeModeRatedStorageChargingCapacity();
  }
  double CoilCoolingDXSingleSpeedThermalStorage::coolingAndChargeModeStorageCapacitySizingFactor() const {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->coolingAndChargeModeStorageCapacitySizingFactor();
  }
  bool CoilCoolingDXSingleSpeedThermalStorage::setCoolingAndChargeModeStorageCapacitySizingFactor(
    double coolingAndChargeModeStorageCapacitySizingFactor) {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->setCoolingAndChargeModeStorageCapacitySizingFactor(
      coolingAndChargeModeStorageCapacitySizingFactor);
  }
  double CoilCoolingDXSingleSpeedThermalStorage::coolingAndChargeModeRatedSensibleHeatRatio() const {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->coolingAndChargeModeRatedSensibleHeatRatio();
  }
  bool CoilCoolingDXSingleSpeedThermalStorage::setCoolingAndChargeModeRatedSensibleHeatRatio(double coolingAndChargeModeRatedSensibleHeatRatio) {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->setCoolingAndChargeModeRatedSensibleHeatRatio(
      coolingAndChargeModeRatedSensibleHeatRatio);
  }
  double CoilCoolingDXSingleSpeedThermalStorage::coolingAndChargeModeCoolingRatedCOP() const {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->coolingAndChargeModeCoolingRatedCOP();
  }
  bool CoilCoolingDXSingleSpeedThermalStorage::setCoolingAndChargeModeCoolingRatedCOP(double coolingAndChargeModeCoolingRatedCOP) {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->setCoolingAndChargeModeCoolingRatedCOP(
      coolingAndChargeModeCoolingRatedCOP);
  }
  double CoilCoolingDXSingleSpeedThermalStorage::coolingAndChargeModeChargingRatedCOP() const {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->coolingAndChargeModeChargingRatedCOP();
  }
  bool CoilCoolingDXSingleSpeedThermalStorage::setCoolingAndChargeModeChargingRatedCOP(double coolingAndChargeModeChargingRatedCOP) {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->setCoolingAndChargeModeChargingRatedCOP(
      coolingAndChargeModeChargingRatedCOP);
  }
  bool CoilCoolingDXSingleSpeedThermalStorage::coolingAndDischargeModeAvailable() const {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->coolingAndDischargeModeAvailable();
  }
  bool CoilCoolingDXSingleSpeedThermalStorage::setCoolingAndDischargeModeAvailable(bool coolingAndDischargeModeAvailable) {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->setCoolingAndDischargeModeAvailable(coolingAndDischargeModeAvailable);
  }
  boost::optional<double> CoilCoolingDXSingleSpeedThermalStorage::coolingAndDischargeModeRatedTotalEvaporatorCoolingCapacity() const {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->coolingAndDischargeModeRatedTotalEvaporatorCoolingCapacity();
  }
  bool CoilCoolingDXSingleSpeedThermalStorage::isCoolingAndDischargeModeRatedTotalEvaporatorCoolingCapacityAutosized() const {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->isCoolingAndDischargeModeRatedTotalEvaporatorCoolingCapacityAutosized();
  }
  bool CoilCoolingDXSingleSpeedThermalStorage::setCoolingAndDischargeModeRatedTotalEvaporatorCoolingCapacity(
    double coolingAndDischargeModeRatedTotalEvaporatorCoolingCapacity) {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->setCoolingAndDischargeModeRatedTotalEvaporatorCoolingCapacity(
      coolingAndDischargeModeRatedTotalEvaporatorCoolingCapacity);
  }
  void CoilCoolingDXSingleSpeedThermalStorage::autosizeCoolingAndDischargeModeRatedTotalEvaporatorCoolingCapacity() {
    getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->autosizeCoolingAndDischargeModeRatedTotalEvaporatorCoolingCapacity();
  }
  double CoilCoolingDXSingleSpeedThermalStorage::coolingAndDischargeModeEvaporatorCapacitySizingFactor() const {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->coolingAndDischargeModeEvaporatorCapacitySizingFactor();
  }
  bool CoilCoolingDXSingleSpeedThermalStorage::setCoolingAndDischargeModeEvaporatorCapacitySizingFactor(
    double coolingAndDischargeModeEvaporatorCapacitySizingFactor) {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->setCoolingAndDischargeModeEvaporatorCapacitySizingFactor(
      coolingAndDischargeModeEvaporatorCapacitySizingFactor);
  }
  boost::optional<double> CoilCoolingDXSingleSpeedThermalStorage::coolingAndDischargeModeRatedStorageDischargingCapacity() const {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->coolingAndDischargeModeRatedStorageDischargingCapacity();
  }
  bool CoilCoolingDXSingleSpeedThermalStorage::isCoolingAndDischargeModeRatedStorageDischargingCapacityAutosized() const {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->isCoolingAndDischargeModeRatedStorageDischargingCapacityAutosized();
  }
  bool CoilCoolingDXSingleSpeedThermalStorage::setCoolingAndDischargeModeRatedStorageDischargingCapacity(
    double coolingAndDischargeModeRatedStorageDischargingCapacity) {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->setCoolingAndDischargeModeRatedStorageDischargingCapacity(
      coolingAndDischargeModeRatedStorageDischargingCapacity);
  }
  void CoilCoolingDXSingleSpeedThermalStorage::autosizeCoolingAndDischargeModeRatedStorageDischargingCapacity() {
    getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->autosizeCoolingAndDischargeModeRatedStorageDischargingCapacity();
  }
  double CoilCoolingDXSingleSpeedThermalStorage::coolingAndDischargeModeStorageDischargeCapacitySizingFactor() const {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->coolingAndDischargeModeStorageDischargeCapacitySizingFactor();
  }
  bool CoilCoolingDXSingleSpeedThermalStorage::setCoolingAndDischargeModeStorageDischargeCapacitySizingFactor(
    double coolingAndDischargeModeStorageDischargeCapacitySizingFactor) {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->setCoolingAndDischargeModeStorageDischargeCapacitySizingFactor(
      coolingAndDischargeModeStorageDischargeCapacitySizingFactor);
  }
  double CoilCoolingDXSingleSpeedThermalStorage::coolingAndDischargeModeRatedSensibleHeatRatio() const {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->coolingAndDischargeModeRatedSensibleHeatRatio();
  }
  bool
    CoilCoolingDXSingleSpeedThermalStorage::setCoolingAndDischargeModeRatedSensibleHeatRatio(double coolingAndDischargeModeRatedSensibleHeatRatio) {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->setCoolingAndDischargeModeRatedSensibleHeatRatio(
      coolingAndDischargeModeRatedSensibleHeatRatio);
  }
  double CoilCoolingDXSingleSpeedThermalStorage::coolingAndDischargeModeCoolingRatedCOP() const {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->coolingAndDischargeModeCoolingRatedCOP();
  }
  bool CoilCoolingDXSingleSpeedThermalStorage::setCoolingAndDischargeModeCoolingRatedCOP(double coolingAndDischargeModeCoolingRatedCOP) {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->setCoolingAndDischargeModeCoolingRatedCOP(
      coolingAndDischargeModeCoolingRatedCOP);
  }
  double CoilCoolingDXSingleSpeedThermalStorage::coolingAndDischargeModeDischargingRatedCOP() const {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->coolingAndDischargeModeDischargingRatedCOP();
  }
  bool CoilCoolingDXSingleSpeedThermalStorage::setCoolingAndDischargeModeDischargingRatedCOP(double coolingAndDischargeModeDischargingRatedCOP) {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->setCoolingAndDischargeModeDischargingRatedCOP(
      coolingAndDischargeModeDischargingRatedCOP);
  }
  bool CoilCoolingDXSingleSpeedThermalStorage::chargeOnlyModeAvailable() const {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->chargeOnlyModeAvailable();
  }
  bool CoilCoolingDXSingleSpeedThermalStorage::setChargeOnlyModeAvailable(bool chargeOnlyModeAvailable) {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->setChargeOnlyModeAvailable(chargeOnlyModeAvailable);
  }
  boost::optional<double> CoilCoolingDXSingleSpeedThermalStorage::chargeOnlyModeRatedStorageChargingCapacity() const {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->chargeOnlyModeRatedStorageChargingCapacity();
  }
  bool CoilCoolingDXSingleSpeedThermalStorage::isChargeOnlyModeRatedStorageChargingCapacityAutosized() const {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->isChargeOnlyModeRatedStorageChargingCapacityAutosized();
  }
  bool CoilCoolingDXSingleSpeedThermalStorage::setChargeOnlyModeRatedStorageChargingCapacity(double chargeOnlyModeRatedStorageChargingCapacity) {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->setChargeOnlyModeRatedStorageChargingCapacity(
      chargeOnlyModeRatedStorageChargingCapacity);
  }
  void CoilCoolingDXSingleSpeedThermalStorage::autosizeChargeOnlyModeRatedStorageChargingCapacity() {
    getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->autosizeChargeOnlyModeRatedStorageChargingCapacity();
  }
  double CoilCoolingDXSingleSpeedThermalStorage::chargeOnlyModeCapacitySizingFactor() const {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->chargeOnlyModeCapacitySizingFactor();
  }
  bool CoilCoolingDXSingleSpeedThermalStorage::setChargeOnlyModeCapacitySizingFactor(double chargeOnlyModeCapacitySizingFactor) {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->setChargeOnlyModeCapacitySizingFactor(chargeOnlyModeCapacitySizingFactor);
  }
  double CoilCoolingDXSingleSpeedThermalStorage::chargeOnlyModeChargingRatedCOP() const {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->chargeOnlyModeChargingRatedCOP();
  }
  bool CoilCoolingDXSingleSpeedThermalStorage::setChargeOnlyModeChargingRatedCOP(double chargeOnlyModeChargingRatedCOP) {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->setChargeOnlyModeChargingRatedCOP(chargeOnlyModeChargingRatedCOP);
  }
  bool CoilCoolingDXSingleSpeedThermalStorage::dischargeOnlyModeAvailable() const {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->dischargeOnlyModeAvailable();
  }
  bool CoilCoolingDXSingleSpeedThermalStorage::setDischargeOnlyModeAvailable(bool dischargeOnlyModeAvailable) {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->setDischargeOnlyModeAvailable(dischargeOnlyModeAvailable);
  }
  boost::optional<double> CoilCoolingDXSingleSpeedThermalStorage::dischargeOnlyModeRatedStorageDischargingCapacity() const {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->dischargeOnlyModeRatedStorageDischargingCapacity();
  }
  bool CoilCoolingDXSingleSpeedThermalStorage::isDischargeOnlyModeRatedStorageDischargingCapacityAutosized() const {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->isDischargeOnlyModeRatedStorageDischargingCapacityAutosized();
  }
  bool CoilCoolingDXSingleSpeedThermalStorage::setDischargeOnlyModeRatedStorageDischargingCapacity(
    double dischargeOnlyModeRatedStorageDischargingCapacity) {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->setDischargeOnlyModeRatedStorageDischargingCapacity(
      dischargeOnlyModeRatedStorageDischargingCapacity);
  }
  void CoilCoolingDXSingleSpeedThermalStorage::autosizeDischargeOnlyModeRatedStorageDischargingCapacity() {
    getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->autosizeDischargeOnlyModeRatedStorageDischargingCapacity();
  }
  double CoilCoolingDXSingleSpeedThermalStorage::dischargeOnlyModeCapacitySizingFactor() const {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->dischargeOnlyModeCapacitySizingFactor();
  }
  bool CoilCoolingDXSingleSpeedThermalStorage::setDischargeOnlyModeCapacitySizingFactor(double dischargeOnlyModeCapacitySizingFactor) {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->setDischargeOnlyModeCapacitySizingFactor(
      dischargeOnlyModeCapacitySizingFactor);
  }
  double CoilCoolingDXSingleSpeedThermalStorage::dischargeOnlyModeRatedSensibleHeatRatio() const {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->dischargeOnlyModeRatedSensibleHeatRatio();
  }
  bool CoilCoolingDXSingleSpeedThermalStorage::setDischargeOnlyModeRatedSensibleHeatRatio(double dischargeOnlyModeRatedSensibleHeatRatio) {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->setDischargeOnlyModeRatedSensibleHeatRatio(
      dischargeOnlyModeRatedSensibleHeatRatio);
  }
  double CoilCoolingDXSingleSpeedThermalStorage::dischargeOnlyModeRatedCOP() const {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->dischargeOnlyModeRatedCOP();
  }
  bool CoilCoolingDXSingleSpeedThermalStorage::setDischargeOnlyModeRatedCOP(double dischargeOnlyModeRatedCOP) {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->setDischargeOnlyModeRatedCOP(dischargeOnlyModeRatedCOP);
  }
  boost::optional<double> CoilCoolingDXSingleSpeedThermalStorage::ancillaryElectricPower() const {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->ancillaryElectricPower();
  }
  bool CoilCoolingDXSingleSpeedThermalStorage::setAncillaryElectricPower(double ancillaryElectricPower) {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->setAncillaryElectricPower(ancillaryElectricPower);
  }
  boost::optional<double> CoilCoolingDXSingleSpeedThermalStorage::coldWeatherOperationMinimumOutdoorAirTemperature() const {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->coldWeatherOperationMinimumOutdoorAirTemperature();
  }
  bool CoilCoolingDXSingleSpeedThermalStorage::setColdWeatherOperationMinimumOutdoorAirTemperature(
    double coldWeatherOperationMinimumOutdoorAirTemperature) {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->setColdWeatherOperationMinimumOutdoorAirTemperature(
      coldWeatherOperationMinimumOutdoorAirTemperature);
  }
  void CoilCoolingDXSingleSpeedThermalStorage::resetColdWeatherOperationMinimumOutdoorAirTemperature() {
    getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->resetColdWeatherOperationMinimumOutdoorAirTemperature();
  }
  boost::optional<double> CoilCoolingDXSingleSpeedThermalStorage::coldWeatherOperationAncillaryPower() const {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->coldWeatherOperationAncillaryPower();
  }
  bool CoilCoolingDXSingleSpeedThermalStorage::setColdWeatherOperationAncillaryPower(double coldWeatherOperationAncillaryPower) {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->setColdWeatherOperationAncillaryPower(coldWeatherOperationAncillaryPower);
  }
  boost::optional<double> CoilCoolingDXSingleSpeedThermalStorage::condenserDesignAirFlowRate() const {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->condenserDesignAirFlowRate();
  }
  bool CoilCoolingDXSingleSpeedThermalStorage::isCondenserDesignAirFlowRateAutosized() const {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->isCondenserDesignAirFlowRateAutosized();
  }
  bool CoilCoolingDXSingleSpeedThermalStorage::setCondenserDesignAirFlowRate(double condenserDesignAirFlowRate) {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->setCondenserDesignAirFlowRate(condenserDesignAirFlowRate);
  }
  void CoilCoolingDXSingleSpeedThermalStorage::autosizeCondenserDesignAirFlowRate() {
    getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->autosizeCondenserDesignAirFlowRate();
  }
  double CoilCoolingDXSingleSpeedThermalStorage::condenserAirFlowSizingFactor() const {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->condenserAirFlowSizingFactor();
  }
  bool CoilCoolingDXSingleSpeedThermalStorage::setCondenserAirFlowSizingFactor(double condenserAirFlowSizingFactor) {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->setCondenserAirFlowSizingFactor(condenserAirFlowSizingFactor);
  }
  std::string CoilCoolingDXSingleSpeedThermalStorage::condenserType() const {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->condenserType();
  }
  bool CoilCoolingDXSingleSpeedThermalStorage::setCondenserType(const std::string& condenserType) {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->setCondenserType(condenserType);
  }
  double CoilCoolingDXSingleSpeedThermalStorage::evaporativeCondenserEffectiveness() const {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->evaporativeCondenserEffectiveness();
  }
  bool CoilCoolingDXSingleSpeedThermalStorage::setEvaporativeCondenserEffectiveness(double evaporativeCondenserEffectiveness) {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->setEvaporativeCondenserEffectiveness(evaporativeCondenserEffectiveness);
  }
  boost::optional<double> CoilCoolingDXSingleSpeedThermalStorage::evaporativeCondenserPumpRatedPowerConsumption() const {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->evaporativeCondenserPumpRatedPowerConsumption();
  }
  bool CoilCoolingDXSingleSpeedThermalStorage::isEvaporativeCondenserPumpRatedPowerConsumptionAutosized() const {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->isEvaporativeCondenserPumpRatedPowerConsumptionAutosized();
  }
  bool
    CoilCoolingDXSingleSpeedThermalStorage::setEvaporativeCondenserPumpRatedPowerConsumption(double evaporativeCondenserPumpRatedPowerConsumption) {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->setEvaporativeCondenserPumpRatedPowerConsumption(
      evaporativeCondenserPumpRatedPowerConsumption);
  }
  void CoilCoolingDXSingleSpeedThermalStorage::autosizeEvaporativeCondenserPumpRatedPowerConsumption() {
    getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->autosizeEvaporativeCondenserPumpRatedPowerConsumption();
  }
  double CoilCoolingDXSingleSpeedThermalStorage::basinHeaterCapacity() const {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->basinHeaterCapacity();
  }
  bool CoilCoolingDXSingleSpeedThermalStorage::setBasinHeaterCapacity(double basinHeaterCapacity) {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->setBasinHeaterCapacity(basinHeaterCapacity);
  }
  double CoilCoolingDXSingleSpeedThermalStorage::basinHeaterSetpointTemperature() const {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->basinHeaterSetpointTemperature();
  }
  bool CoilCoolingDXSingleSpeedThermalStorage::setBasinHeaterSetpointTemperature(double basinHeaterSetpointTemperature) {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->setBasinHeaterSetpointTemperature(basinHeaterSetpointTemperature);
  }
  boost::optional<Schedule> CoilCoolingDXSingleSpeedThermalStorage::basinHeaterAvailabilitySchedule() const {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->basinHeaterAvailabilitySchedule();
  }
  bool CoilCoolingDXSingleSpeedThermalStorage::setBasinHeaterAvailabilitySchedule(Schedule& schedule) {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->setBasinHeaterAvailabilitySchedule(schedule);
  }
  void CoilCoolingDXSingleSpeedThermalStorage::resetBasinHeaterAvailabilitySchedule() {
    getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->resetBasinHeaterAvailabilitySchedule();
  }
  bool CoilCoolingDXSingleSpeedThermalStorage::addToNode(Node& node) {
    return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->addToNode(node);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    namespace {

      bool isAutosized(const ModelObject_Impl& impl, int fieldIndex) {
        if (const auto value = impl.getString(fieldIndex, true)) {
          return openstudio::istringEqual(*value, "autosize");
        }
        return false;
      }

      bool getBooleanFieldValue(const ModelObject_Impl& impl, int fieldIndex) {
        const auto value = impl.getString(fieldIndex, true);
        OS_ASSERT(value);
        return openstudio::istringEqual(*value, "yes");
      }

      bool setBooleanFieldValue(ModelObject_Impl& impl, int fieldIndex, bool value) {
        return impl.setString(fieldIndex, value ? "Yes" : "No");
      }

    }  // namespace

    Schedule CoilCoolingDXSingleSpeedThermalStorage_Impl::availabilitySchedule() const {
      auto value = getObject<ModelObject>().getModelObjectTarget<Schedule>(
        openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::AvailabilityScheduleName);
      if (!value) {
        value = this->model().alwaysOnDiscreteSchedule();
        OS_ASSERT(value);
        const_cast<CoilCoolingDXSingleSpeedThermalStorage_Impl*>(this)->setAvailabilitySchedule(*value);
        value = getObject<ModelObject>().getModelObjectTarget<Schedule>(
          openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::AvailabilityScheduleName);
      }
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingDXSingleSpeedThermalStorage_Impl::setAvailabilitySchedule(Schedule& schedule) {
      return setPointer(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::AvailabilityScheduleName, schedule.handle(), false);
    }

    unsigned CoilCoolingDXSingleSpeedThermalStorage_Impl::inletPort() const {
      return openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::EvaporatorAirInletNodeName;
    }

    unsigned CoilCoolingDXSingleSpeedThermalStorage_Impl::outletPort() const {
      return openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::EvaporatorAirOutletNodeName;
    }

    std::vector<std::string> CoilCoolingDXSingleSpeedThermalStorage_Impl::operatingModeControlMethodValues() const {
      return CoilCoolingDXSingleSpeedThermalStorage::operatingModeControlMethodValues();
    }

    std::vector<std::string> CoilCoolingDXSingleSpeedThermalStorage_Impl::storageTypeValues() const {
      return CoilCoolingDXSingleSpeedThermalStorage::storageTypeValues();
    }

    std::vector<std::string> CoilCoolingDXSingleSpeedThermalStorage_Impl::condenserTypeValues() const {
      return CoilCoolingDXSingleSpeedThermalStorage::condenserTypeValues();
    }

    std::string CoilCoolingDXSingleSpeedThermalStorage_Impl::operatingModeControlMethod() const {
      const auto value = getString(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::OperatingModeControlMethod, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingDXSingleSpeedThermalStorage_Impl::setOperatingModeControlMethod(const std::string& operatingModeControlMethod) {
      return setString(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::OperatingModeControlMethod, operatingModeControlMethod);
    }

    boost::optional<Schedule> CoilCoolingDXSingleSpeedThermalStorage_Impl::operationModeControlSchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(
        openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::OperationModeControlScheduleName);
    }

    bool CoilCoolingDXSingleSpeedThermalStorage_Impl::setOperationModeControlSchedule(Schedule& schedule) {
      return setPointer(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::OperationModeControlScheduleName, schedule.handle(), false);
    }

    void CoilCoolingDXSingleSpeedThermalStorage_Impl::resetOperationModeControlSchedule() {
      OS_ASSERT(setPointer(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::OperationModeControlScheduleName, Handle(), false));
    }

    std::string CoilCoolingDXSingleSpeedThermalStorage_Impl::storageType() const {
      const auto value = getString(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::StorageType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingDXSingleSpeedThermalStorage_Impl::setStorageType(const std::string& storageType) {
      return setString(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::StorageType, storageType);
    }

    int CoilCoolingDXSingleSpeedThermalStorage_Impl::glycolConcentration() const {
      // API/schema drift: EnergyPlus has no direct concentration scalar here.
      // Preserve API with a stable fallback until fluid-properties object support is added.
      return 0;
    }

    bool CoilCoolingDXSingleSpeedThermalStorage_Impl::setGlycolConcentration(int glycolConcentration) {
      static_cast<void>(glycolConcentration);
      return true;
    }

    boost::optional<double> CoilCoolingDXSingleSpeedThermalStorage_Impl::fluidStorageVolume() const {
      return getDouble(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::FluidStorageVolume, true);
    }

    bool CoilCoolingDXSingleSpeedThermalStorage_Impl::isFluidStorageVolumeAutosized() const {
      return isAutosized(*this, openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::FluidStorageVolume);
    }

    bool CoilCoolingDXSingleSpeedThermalStorage_Impl::setFluidStorageVolume(double fluidStorageVolume) {
      return setDouble(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::FluidStorageVolume, fluidStorageVolume);
    }

    void CoilCoolingDXSingleSpeedThermalStorage_Impl::resetFluidStorageVolume() {
      const bool result = setString(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::FluidStorageVolume, "");
      OS_ASSERT(result);
    }

    void CoilCoolingDXSingleSpeedThermalStorage_Impl::autosizeFluidStorageVolume() {
      const bool result = setString(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::FluidStorageVolume, "autosize");
      OS_ASSERT(result);
    }

    boost::optional<double> CoilCoolingDXSingleSpeedThermalStorage_Impl::iceStorageCapacity() const {
      return getDouble(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::IceStorageCapacity, true);
    }

    bool CoilCoolingDXSingleSpeedThermalStorage_Impl::isIceStorageCapacityAutosized() const {
      return isAutosized(*this, openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::IceStorageCapacity);
    }

    bool CoilCoolingDXSingleSpeedThermalStorage_Impl::setIceStorageCapacity(double iceStorageCapacity) {
      return setDouble(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::IceStorageCapacity, iceStorageCapacity);
    }

    void CoilCoolingDXSingleSpeedThermalStorage_Impl::autosizeIceStorageCapacity() {
      const bool result = setString(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::IceStorageCapacity, "autosize");
      OS_ASSERT(result);
    }

    boost::optional<double> CoilCoolingDXSingleSpeedThermalStorage_Impl::storageCapacitySizingFactor() const {
      return getDouble(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::StorageCapacitySizingFactor, true);
    }

    bool CoilCoolingDXSingleSpeedThermalStorage_Impl::setStorageCapacitySizingFactor(double storageCapacitySizingFactor) {
      return setDouble(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::StorageCapacitySizingFactor, storageCapacitySizingFactor);
    }

    double CoilCoolingDXSingleSpeedThermalStorage_Impl::storageTanktoAmbientUvalueTimesAreaHeatTransferCoefficient() const {
      const auto value =
        getDouble(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::StorageTanktoAmbientUvalueTimesAreaHeatTransferCoefficient, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingDXSingleSpeedThermalStorage_Impl::setStorageTanktoAmbientUvalueTimesAreaHeatTransferCoefficient(
      double storageTanktoAmbientUvalueTimesAreaHeatTransferCoefficient) {
      return setDouble(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::StorageTanktoAmbientUvalueTimesAreaHeatTransferCoefficient,
                       storageTanktoAmbientUvalueTimesAreaHeatTransferCoefficient);
    }

    double CoilCoolingDXSingleSpeedThermalStorage_Impl::fluidStorageTankRatingTemperature() const {
      const auto value = getDouble(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::FluidStorageTankRatingTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingDXSingleSpeedThermalStorage_Impl::setFluidStorageTankRatingTemperature(double fluidStorageTankRatingTemperature) {
      return setDouble(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::FluidStorageTankRatingTemperature,
                       fluidStorageTankRatingTemperature);
    }

    boost::optional<double> CoilCoolingDXSingleSpeedThermalStorage_Impl::ratedEvaporatorAirFlowRate() const {
      return getDouble(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::RatedEvaporatorAirFlowRate, true);
    }

    bool CoilCoolingDXSingleSpeedThermalStorage_Impl::isRatedEvaporatorAirFlowRateAutosized() const {
      return isAutosized(*this, openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::RatedEvaporatorAirFlowRate);
    }

    bool CoilCoolingDXSingleSpeedThermalStorage_Impl::setRatedEvaporatorAirFlowRate(double ratedEvaporatorAirFlowRate) {
      return setDouble(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::RatedEvaporatorAirFlowRate, ratedEvaporatorAirFlowRate);
    }

    void CoilCoolingDXSingleSpeedThermalStorage_Impl::autosizeRatedEvaporatorAirFlowRate() {
      const bool result = setString(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::RatedEvaporatorAirFlowRate, "autosize");
      OS_ASSERT(result);
    }

    bool CoilCoolingDXSingleSpeedThermalStorage_Impl::coolingOnlyModeAvailable() const {
      return getBooleanFieldValue(*this, openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingOnlyModeAvailable);
    }

    bool CoilCoolingDXSingleSpeedThermalStorage_Impl::setCoolingOnlyModeAvailable(bool coolingOnlyModeAvailable) {
      return setBooleanFieldValue(*this, openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingOnlyModeAvailable,
                                  coolingOnlyModeAvailable);
    }

    boost::optional<double> CoilCoolingDXSingleSpeedThermalStorage_Impl::coolingOnlyModeRatedTotalEvaporatorCoolingCapacity() const {
      return getDouble(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingOnlyModeRatedTotalEvaporatorCoolingCapacity, true);
    }

    bool CoilCoolingDXSingleSpeedThermalStorage_Impl::isCoolingOnlyModeRatedTotalEvaporatorCoolingCapacityAutosized() const {
      return isAutosized(*this, openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingOnlyModeRatedTotalEvaporatorCoolingCapacity);
    }

    bool CoilCoolingDXSingleSpeedThermalStorage_Impl::setCoolingOnlyModeRatedTotalEvaporatorCoolingCapacity(
      double coolingOnlyModeRatedTotalEvaporatorCoolingCapacity) {
      return setDouble(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingOnlyModeRatedTotalEvaporatorCoolingCapacity,
                       coolingOnlyModeRatedTotalEvaporatorCoolingCapacity);
    }

    void CoilCoolingDXSingleSpeedThermalStorage_Impl::autosizeCoolingOnlyModeRatedTotalEvaporatorCoolingCapacity() {
      const bool result =
        setString(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingOnlyModeRatedTotalEvaporatorCoolingCapacity, "autosize");
      OS_ASSERT(result);
    }

    double CoilCoolingDXSingleSpeedThermalStorage_Impl::coolingOnlyModeRatedSensibleHeatRatio() const {
      const auto value = getDouble(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingOnlyModeRatedSensibleHeatRatio, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingDXSingleSpeedThermalStorage_Impl::setCoolingOnlyModeRatedSensibleHeatRatio(double coolingOnlyModeRatedSensibleHeatRatio) {
      return setDouble(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingOnlyModeRatedSensibleHeatRatio,
                       coolingOnlyModeRatedSensibleHeatRatio);
    }

    double CoilCoolingDXSingleSpeedThermalStorage_Impl::coolingOnlyModeRatedCOP() const {
      const auto value = getDouble(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingOnlyModeRatedCOP, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingDXSingleSpeedThermalStorage_Impl::setCoolingOnlyModeRatedCOP(double coolingOnlyModeRatedCOP) {
      return setDouble(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingOnlyModeRatedCOP, coolingOnlyModeRatedCOP);
    }

    bool CoilCoolingDXSingleSpeedThermalStorage_Impl::coolingAndChargeModeAvailable() const {
      return getBooleanFieldValue(*this, openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndChargeModeAvailable);
    }

    bool CoilCoolingDXSingleSpeedThermalStorage_Impl::setCoolingAndChargeModeAvailable(bool coolingAndChargeModeAvailable) {
      return setBooleanFieldValue(*this, openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndChargeModeAvailable,
                                  coolingAndChargeModeAvailable);
    }

    boost::optional<double> CoilCoolingDXSingleSpeedThermalStorage_Impl::coolingAndChargeModeRatedTotalEvaporatorCoolingCapacity() const {
      return getDouble(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndChargeModeRatedTotalEvaporatorCoolingCapacity, true);
    }

    bool CoilCoolingDXSingleSpeedThermalStorage_Impl::isCoolingAndChargeModeRatedTotalEvaporatorCoolingCapacityAutosized() const {
      return isAutosized(*this,
                         openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndChargeModeRatedTotalEvaporatorCoolingCapacity);
    }

    bool CoilCoolingDXSingleSpeedThermalStorage_Impl::setCoolingAndChargeModeRatedTotalEvaporatorCoolingCapacity(
      double coolingAndChargeModeRatedTotalEvaporatorCoolingCapacity) {
      return setDouble(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndChargeModeRatedTotalEvaporatorCoolingCapacity,
                       coolingAndChargeModeRatedTotalEvaporatorCoolingCapacity);
    }

    void CoilCoolingDXSingleSpeedThermalStorage_Impl::autosizeCoolingAndChargeModeRatedTotalEvaporatorCoolingCapacity() {
      const bool result =
        setString(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndChargeModeRatedTotalEvaporatorCoolingCapacity, "autosize");
      OS_ASSERT(result);
    }

    double CoilCoolingDXSingleSpeedThermalStorage_Impl::coolingAndChargeModeCapacitySizingFactor() const {
      const auto value = getDouble(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndChargeModeCapacitySizingFactor, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingDXSingleSpeedThermalStorage_Impl::setCoolingAndChargeModeCapacitySizingFactor(double coolingAndChargeModeCapacitySizingFactor) {
      return setDouble(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndChargeModeCapacitySizingFactor,
                       coolingAndChargeModeCapacitySizingFactor);
    }

    boost::optional<double> CoilCoolingDXSingleSpeedThermalStorage_Impl::coolingAndChargeModeRatedStorageChargingCapacity() const {
      return getDouble(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndChargeModeRatedStorageChargingCapacity, true);
    }

    bool CoilCoolingDXSingleSpeedThermalStorage_Impl::isCoolingAndChargeModeRatedStorageChargingCapacityAutosized() const {
      return isAutosized(*this, openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndChargeModeRatedStorageChargingCapacity);
    }

    bool CoilCoolingDXSingleSpeedThermalStorage_Impl::setCoolingAndChargeModeRatedStorageChargingCapacity(
      double coolingAndChargeModeRatedStorageChargingCapacity) {
      return setDouble(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndChargeModeRatedStorageChargingCapacity,
                       coolingAndChargeModeRatedStorageChargingCapacity);
    }

    void CoilCoolingDXSingleSpeedThermalStorage_Impl::autosizeCoolingAndChargeModeRatedStorageChargingCapacity() {
      const bool result =
        setString(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndChargeModeRatedStorageChargingCapacity, "autosize");
      OS_ASSERT(result);
    }

    double CoilCoolingDXSingleSpeedThermalStorage_Impl::coolingAndChargeModeStorageCapacitySizingFactor() const {
      const auto value =
        getDouble(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndChargeModeStorageCapacitySizingFactor, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingDXSingleSpeedThermalStorage_Impl::setCoolingAndChargeModeStorageCapacitySizingFactor(
      double coolingAndChargeModeStorageCapacitySizingFactor) {
      return setDouble(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndChargeModeStorageCapacitySizingFactor,
                       coolingAndChargeModeStorageCapacitySizingFactor);
    }

    double CoilCoolingDXSingleSpeedThermalStorage_Impl::coolingAndChargeModeRatedSensibleHeatRatio() const {
      const auto value = getDouble(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndChargeModeRatedSensibleHeatRatio, true);
      OS_ASSERT(value);
      return *value;
    }

    bool
      CoilCoolingDXSingleSpeedThermalStorage_Impl::setCoolingAndChargeModeRatedSensibleHeatRatio(double coolingAndChargeModeRatedSensibleHeatRatio) {
      return setDouble(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndChargeModeRatedSensibleHeatRatio,
                       coolingAndChargeModeRatedSensibleHeatRatio);
    }

    double CoilCoolingDXSingleSpeedThermalStorage_Impl::coolingAndChargeModeCoolingRatedCOP() const {
      const auto value = getDouble(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndChargeModeCoolingRatedCOP, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingDXSingleSpeedThermalStorage_Impl::setCoolingAndChargeModeCoolingRatedCOP(double coolingAndChargeModeCoolingRatedCOP) {
      return setDouble(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndChargeModeCoolingRatedCOP,
                       coolingAndChargeModeCoolingRatedCOP);
    }

    double CoilCoolingDXSingleSpeedThermalStorage_Impl::coolingAndChargeModeChargingRatedCOP() const {
      const auto value = getDouble(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndChargeModeChargingRatedCOP, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingDXSingleSpeedThermalStorage_Impl::setCoolingAndChargeModeChargingRatedCOP(double coolingAndChargeModeChargingRatedCOP) {
      return setDouble(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndChargeModeChargingRatedCOP,
                       coolingAndChargeModeChargingRatedCOP);
    }

    bool CoilCoolingDXSingleSpeedThermalStorage_Impl::coolingAndDischargeModeAvailable() const {
      return getBooleanFieldValue(*this, openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndDischargeModeAvailable);
    }

    bool CoilCoolingDXSingleSpeedThermalStorage_Impl::setCoolingAndDischargeModeAvailable(bool coolingAndDischargeModeAvailable) {
      return setBooleanFieldValue(*this, openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndDischargeModeAvailable,
                                  coolingAndDischargeModeAvailable);
    }

    boost::optional<double> CoilCoolingDXSingleSpeedThermalStorage_Impl::coolingAndDischargeModeRatedTotalEvaporatorCoolingCapacity() const {
      return getDouble(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndDischargeModeRatedTotalEvaporatorCoolingCapacity,
                       true);
    }

    bool CoilCoolingDXSingleSpeedThermalStorage_Impl::isCoolingAndDischargeModeRatedTotalEvaporatorCoolingCapacityAutosized() const {
      return isAutosized(*this,
                         openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndDischargeModeRatedTotalEvaporatorCoolingCapacity);
    }

    bool CoilCoolingDXSingleSpeedThermalStorage_Impl::setCoolingAndDischargeModeRatedTotalEvaporatorCoolingCapacity(
      double coolingAndDischargeModeRatedTotalEvaporatorCoolingCapacity) {
      return setDouble(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndDischargeModeRatedTotalEvaporatorCoolingCapacity,
                       coolingAndDischargeModeRatedTotalEvaporatorCoolingCapacity);
    }

    void CoilCoolingDXSingleSpeedThermalStorage_Impl::autosizeCoolingAndDischargeModeRatedTotalEvaporatorCoolingCapacity() {
      const bool result = setString(
        openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndDischargeModeRatedTotalEvaporatorCoolingCapacity, "autosize");
      OS_ASSERT(result);
    }

    double CoilCoolingDXSingleSpeedThermalStorage_Impl::coolingAndDischargeModeEvaporatorCapacitySizingFactor() const {
      const auto value =
        getDouble(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndDischargeModeEvaporatorCapacitySizingFactor, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingDXSingleSpeedThermalStorage_Impl::setCoolingAndDischargeModeEvaporatorCapacitySizingFactor(
      double coolingAndDischargeModeEvaporatorCapacitySizingFactor) {
      return setDouble(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndDischargeModeEvaporatorCapacitySizingFactor,
                       coolingAndDischargeModeEvaporatorCapacitySizingFactor);
    }

    boost::optional<double> CoilCoolingDXSingleSpeedThermalStorage_Impl::coolingAndDischargeModeRatedStorageDischargingCapacity() const {
      return getDouble(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndDischargeModeRatedStorageDischargingCapacity, true);
    }

    bool CoilCoolingDXSingleSpeedThermalStorage_Impl::isCoolingAndDischargeModeRatedStorageDischargingCapacityAutosized() const {
      return isAutosized(*this, openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndDischargeModeRatedStorageDischargingCapacity);
    }

    bool CoilCoolingDXSingleSpeedThermalStorage_Impl::setCoolingAndDischargeModeRatedStorageDischargingCapacity(
      double coolingAndDischargeModeRatedStorageDischargingCapacity) {
      return setDouble(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndDischargeModeRatedStorageDischargingCapacity,
                       coolingAndDischargeModeRatedStorageDischargingCapacity);
    }

    void CoilCoolingDXSingleSpeedThermalStorage_Impl::autosizeCoolingAndDischargeModeRatedStorageDischargingCapacity() {
      const bool result =
        setString(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndDischargeModeRatedStorageDischargingCapacity, "autosize");
      OS_ASSERT(result);
    }

    double CoilCoolingDXSingleSpeedThermalStorage_Impl::coolingAndDischargeModeStorageDischargeCapacitySizingFactor() const {
      const auto value =
        getDouble(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndDischargeModeStorageDischargeCapacitySizingFactor, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingDXSingleSpeedThermalStorage_Impl::setCoolingAndDischargeModeStorageDischargeCapacitySizingFactor(
      double coolingAndDischargeModeStorageDischargeCapacitySizingFactor) {
      return setDouble(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndDischargeModeStorageDischargeCapacitySizingFactor,
                       coolingAndDischargeModeStorageDischargeCapacitySizingFactor);
    }

    double CoilCoolingDXSingleSpeedThermalStorage_Impl::coolingAndDischargeModeRatedSensibleHeatRatio() const {
      const auto value = getDouble(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndDischargeModeRatedSensibleHeatRatio, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingDXSingleSpeedThermalStorage_Impl::setCoolingAndDischargeModeRatedSensibleHeatRatio(
      double coolingAndDischargeModeRatedSensibleHeatRatio) {
      return setDouble(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndDischargeModeRatedSensibleHeatRatio,
                       coolingAndDischargeModeRatedSensibleHeatRatio);
    }

    double CoilCoolingDXSingleSpeedThermalStorage_Impl::coolingAndDischargeModeCoolingRatedCOP() const {
      const auto value = getDouble(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndDischargeModeCoolingRatedCOP, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingDXSingleSpeedThermalStorage_Impl::setCoolingAndDischargeModeCoolingRatedCOP(double coolingAndDischargeModeCoolingRatedCOP) {
      return setDouble(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndDischargeModeCoolingRatedCOP,
                       coolingAndDischargeModeCoolingRatedCOP);
    }

    double CoilCoolingDXSingleSpeedThermalStorage_Impl::coolingAndDischargeModeDischargingRatedCOP() const {
      const auto value = getDouble(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndDischargeModeDischargingRatedCOP, true);
      OS_ASSERT(value);
      return *value;
    }

    bool
      CoilCoolingDXSingleSpeedThermalStorage_Impl::setCoolingAndDischargeModeDischargingRatedCOP(double coolingAndDischargeModeDischargingRatedCOP) {
      return setDouble(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndDischargeModeDischargingRatedCOP,
                       coolingAndDischargeModeDischargingRatedCOP);
    }

    bool CoilCoolingDXSingleSpeedThermalStorage_Impl::chargeOnlyModeAvailable() const {
      return getBooleanFieldValue(*this, openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::ChargeOnlyModeAvailable);
    }

    bool CoilCoolingDXSingleSpeedThermalStorage_Impl::setChargeOnlyModeAvailable(bool chargeOnlyModeAvailable) {
      return setBooleanFieldValue(*this, openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::ChargeOnlyModeAvailable,
                                  chargeOnlyModeAvailable);
    }

    boost::optional<double> CoilCoolingDXSingleSpeedThermalStorage_Impl::chargeOnlyModeRatedStorageChargingCapacity() const {
      return getDouble(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::ChargeOnlyModeRatedStorageChargingCapacity, true);
    }

    bool CoilCoolingDXSingleSpeedThermalStorage_Impl::isChargeOnlyModeRatedStorageChargingCapacityAutosized() const {
      return isAutosized(*this, openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::ChargeOnlyModeRatedStorageChargingCapacity);
    }

    bool
      CoilCoolingDXSingleSpeedThermalStorage_Impl::setChargeOnlyModeRatedStorageChargingCapacity(double chargeOnlyModeRatedStorageChargingCapacity) {
      return setDouble(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::ChargeOnlyModeRatedStorageChargingCapacity,
                       chargeOnlyModeRatedStorageChargingCapacity);
    }

    void CoilCoolingDXSingleSpeedThermalStorage_Impl::autosizeChargeOnlyModeRatedStorageChargingCapacity() {
      const bool result =
        setString(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::ChargeOnlyModeRatedStorageChargingCapacity, "autosize");
      OS_ASSERT(result);
    }

    double CoilCoolingDXSingleSpeedThermalStorage_Impl::chargeOnlyModeCapacitySizingFactor() const {
      const auto value = getDouble(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::ChargeOnlyModeCapacitySizingFactor, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingDXSingleSpeedThermalStorage_Impl::setChargeOnlyModeCapacitySizingFactor(double chargeOnlyModeCapacitySizingFactor) {
      return setDouble(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::ChargeOnlyModeCapacitySizingFactor,
                       chargeOnlyModeCapacitySizingFactor);
    }

    double CoilCoolingDXSingleSpeedThermalStorage_Impl::chargeOnlyModeChargingRatedCOP() const {
      const auto value = getDouble(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::ChargeOnlyModeChargingRatedCOP, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingDXSingleSpeedThermalStorage_Impl::setChargeOnlyModeChargingRatedCOP(double chargeOnlyModeChargingRatedCOP) {
      return setDouble(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::ChargeOnlyModeChargingRatedCOP, chargeOnlyModeChargingRatedCOP);
    }

    bool CoilCoolingDXSingleSpeedThermalStorage_Impl::dischargeOnlyModeAvailable() const {
      return getBooleanFieldValue(*this, openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::DischargeOnlyModeAvailable);
    }

    bool CoilCoolingDXSingleSpeedThermalStorage_Impl::setDischargeOnlyModeAvailable(bool dischargeOnlyModeAvailable) {
      return setBooleanFieldValue(*this, openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::DischargeOnlyModeAvailable,
                                  dischargeOnlyModeAvailable);
    }

    boost::optional<double> CoilCoolingDXSingleSpeedThermalStorage_Impl::dischargeOnlyModeRatedStorageDischargingCapacity() const {
      return getDouble(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::DischargeOnlyModeRatedStorageDischargingCapacity, true);
    }

    bool CoilCoolingDXSingleSpeedThermalStorage_Impl::isDischargeOnlyModeRatedStorageDischargingCapacityAutosized() const {
      return isAutosized(*this, openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::DischargeOnlyModeRatedStorageDischargingCapacity);
    }

    bool CoilCoolingDXSingleSpeedThermalStorage_Impl::setDischargeOnlyModeRatedStorageDischargingCapacity(
      double dischargeOnlyModeRatedStorageDischargingCapacity) {
      return setDouble(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::DischargeOnlyModeRatedStorageDischargingCapacity,
                       dischargeOnlyModeRatedStorageDischargingCapacity);
    }

    void CoilCoolingDXSingleSpeedThermalStorage_Impl::autosizeDischargeOnlyModeRatedStorageDischargingCapacity() {
      const bool result =
        setString(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::DischargeOnlyModeRatedStorageDischargingCapacity, "autosize");
      OS_ASSERT(result);
    }

    double CoilCoolingDXSingleSpeedThermalStorage_Impl::dischargeOnlyModeCapacitySizingFactor() const {
      const auto value = getDouble(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::DischargeOnlyModeCapacitySizingFactor, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingDXSingleSpeedThermalStorage_Impl::setDischargeOnlyModeCapacitySizingFactor(double dischargeOnlyModeCapacitySizingFactor) {
      return setDouble(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::DischargeOnlyModeCapacitySizingFactor,
                       dischargeOnlyModeCapacitySizingFactor);
    }

    double CoilCoolingDXSingleSpeedThermalStorage_Impl::dischargeOnlyModeRatedSensibleHeatRatio() const {
      const auto value = getDouble(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::DischargeOnlyModeRatedSensibleHeatRatio, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingDXSingleSpeedThermalStorage_Impl::setDischargeOnlyModeRatedSensibleHeatRatio(double dischargeOnlyModeRatedSensibleHeatRatio) {
      return setDouble(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::DischargeOnlyModeRatedSensibleHeatRatio,
                       dischargeOnlyModeRatedSensibleHeatRatio);
    }

    double CoilCoolingDXSingleSpeedThermalStorage_Impl::dischargeOnlyModeRatedCOP() const {
      const auto value = getDouble(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::DischargeOnlyModeRatedCOP, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingDXSingleSpeedThermalStorage_Impl::setDischargeOnlyModeRatedCOP(double dischargeOnlyModeRatedCOP) {
      return setDouble(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::DischargeOnlyModeRatedCOP, dischargeOnlyModeRatedCOP);
    }

    boost::optional<double> CoilCoolingDXSingleSpeedThermalStorage_Impl::ancillaryElectricPower() const {
      return getDouble(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::AncillaryElectricPower, true);
    }

    bool CoilCoolingDXSingleSpeedThermalStorage_Impl::setAncillaryElectricPower(double ancillaryElectricPower) {
      return setDouble(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::AncillaryElectricPower, ancillaryElectricPower);
    }

    boost::optional<double> CoilCoolingDXSingleSpeedThermalStorage_Impl::coldWeatherOperationMinimumOutdoorAirTemperature() const {
      return getDouble(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::ColdWeatherOperationMinimumOutdoorAirTemperature, true);
    }

    bool CoilCoolingDXSingleSpeedThermalStorage_Impl::setColdWeatherOperationMinimumOutdoorAirTemperature(
      double coldWeatherOperationMinimumOutdoorAirTemperature) {
      return setDouble(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::ColdWeatherOperationMinimumOutdoorAirTemperature,
                       coldWeatherOperationMinimumOutdoorAirTemperature);
    }

    void CoilCoolingDXSingleSpeedThermalStorage_Impl::resetColdWeatherOperationMinimumOutdoorAirTemperature() {
      const bool result =
        setString(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::ColdWeatherOperationMinimumOutdoorAirTemperature, "");
      OS_ASSERT(result);
    }

    boost::optional<double> CoilCoolingDXSingleSpeedThermalStorage_Impl::coldWeatherOperationAncillaryPower() const {
      return getDouble(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::ColdWeatherOperationAncillaryPower, true);
    }

    bool CoilCoolingDXSingleSpeedThermalStorage_Impl::setColdWeatherOperationAncillaryPower(double coldWeatherOperationAncillaryPower) {
      return setDouble(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::ColdWeatherOperationAncillaryPower,
                       coldWeatherOperationAncillaryPower);
    }

    boost::optional<double> CoilCoolingDXSingleSpeedThermalStorage_Impl::condenserDesignAirFlowRate() const {
      return getDouble(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CondenserDesignAirFlowRate, true);
    }

    bool CoilCoolingDXSingleSpeedThermalStorage_Impl::isCondenserDesignAirFlowRateAutosized() const {
      return isAutosized(*this, openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CondenserDesignAirFlowRate);
    }

    bool CoilCoolingDXSingleSpeedThermalStorage_Impl::setCondenserDesignAirFlowRate(double condenserDesignAirFlowRate) {
      return setDouble(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CondenserDesignAirFlowRate, condenserDesignAirFlowRate);
    }

    void CoilCoolingDXSingleSpeedThermalStorage_Impl::autosizeCondenserDesignAirFlowRate() {
      const bool result = setString(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CondenserDesignAirFlowRate, "autosize");
      OS_ASSERT(result);
    }

    double CoilCoolingDXSingleSpeedThermalStorage_Impl::condenserAirFlowSizingFactor() const {
      const auto value = getDouble(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CondenserAirFlowSizingFactor, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingDXSingleSpeedThermalStorage_Impl::setCondenserAirFlowSizingFactor(double condenserAirFlowSizingFactor) {
      return setDouble(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CondenserAirFlowSizingFactor, condenserAirFlowSizingFactor);
    }

    std::string CoilCoolingDXSingleSpeedThermalStorage_Impl::condenserType() const {
      const auto value = getString(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CondenserType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingDXSingleSpeedThermalStorage_Impl::setCondenserType(const std::string& condenserType) {
      return setString(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CondenserType, condenserType);
    }

    double CoilCoolingDXSingleSpeedThermalStorage_Impl::evaporativeCondenserEffectiveness() const {
      const auto value = getDouble(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::EvaporativeCondenserEffectiveness, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingDXSingleSpeedThermalStorage_Impl::setEvaporativeCondenserEffectiveness(double evaporativeCondenserEffectiveness) {
      return setDouble(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::EvaporativeCondenserEffectiveness,
                       evaporativeCondenserEffectiveness);
    }

    boost::optional<double> CoilCoolingDXSingleSpeedThermalStorage_Impl::evaporativeCondenserPumpRatedPowerConsumption() const {
      return getDouble(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::EvaporativeCondenserPumpRatedPowerConsumption, true);
    }

    bool CoilCoolingDXSingleSpeedThermalStorage_Impl::isEvaporativeCondenserPumpRatedPowerConsumptionAutosized() const {
      return isAutosized(*this, openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::EvaporativeCondenserPumpRatedPowerConsumption);
    }

    bool CoilCoolingDXSingleSpeedThermalStorage_Impl::setEvaporativeCondenserPumpRatedPowerConsumption(
      double evaporativeCondenserPumpRatedPowerConsumption) {
      return setDouble(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::EvaporativeCondenserPumpRatedPowerConsumption,
                       evaporativeCondenserPumpRatedPowerConsumption);
    }

    void CoilCoolingDXSingleSpeedThermalStorage_Impl::autosizeEvaporativeCondenserPumpRatedPowerConsumption() {
      const bool result =
        setString(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::EvaporativeCondenserPumpRatedPowerConsumption, "autosize");
      OS_ASSERT(result);
    }

    double CoilCoolingDXSingleSpeedThermalStorage_Impl::basinHeaterCapacity() const {
      const auto value = getDouble(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::BasinHeaterCapacity, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingDXSingleSpeedThermalStorage_Impl::setBasinHeaterCapacity(double basinHeaterCapacity) {
      return setDouble(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::BasinHeaterCapacity, basinHeaterCapacity);
    }

    double CoilCoolingDXSingleSpeedThermalStorage_Impl::basinHeaterSetpointTemperature() const {
      const auto value = getDouble(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::BasinHeaterSetpointTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingDXSingleSpeedThermalStorage_Impl::setBasinHeaterSetpointTemperature(double basinHeaterSetpointTemperature) {
      return setDouble(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::BasinHeaterSetpointTemperature, basinHeaterSetpointTemperature);
    }

    boost::optional<Schedule> CoilCoolingDXSingleSpeedThermalStorage_Impl::basinHeaterAvailabilitySchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(
        openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::BasinHeaterAvailabilityScheduleName);
    }

    bool CoilCoolingDXSingleSpeedThermalStorage_Impl::setBasinHeaterAvailabilitySchedule(Schedule& schedule) {
      return setPointer(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::BasinHeaterAvailabilityScheduleName, schedule.handle(), false);
    }

    void CoilCoolingDXSingleSpeedThermalStorage_Impl::resetBasinHeaterAvailabilitySchedule() {
      OS_ASSERT(setPointer(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::BasinHeaterAvailabilityScheduleName, Handle(), false));
    }

    bool CoilCoolingDXSingleSpeedThermalStorage_Impl::addToNode(Node& node) {
      auto airLoop = node.airLoopHVAC();

      if (!(airLoop && airLoop->supplyComponent(node.handle()))) {
        return false;
      }

      return StraightComponent_Impl::addToNode(node);
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
