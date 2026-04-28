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

#define EPMODEL_IMPL_FORWARD_0(ret, name) \
  ret CoilCoolingDXSingleSpeedThermalStorage::name() const { return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->name(); }
#define EPMODEL_IMPL_FORWARD_1(ret, name, t1, a1) \
  ret CoilCoolingDXSingleSpeedThermalStorage::name(t1 a1) { return getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->name(a1); }
#define EPMODEL_IMPL_FORWARD_V(name) \
  void CoilCoolingDXSingleSpeedThermalStorage::name() { getImpl<detail::CoilCoolingDXSingleSpeedThermalStorage_Impl>()->name(); }

EPMODEL_IMPL_FORWARD_0(std::string, operatingModeControlMethod)
EPMODEL_IMPL_FORWARD_1(bool, setOperatingModeControlMethod, const std::string&, operatingModeControlMethod)
EPMODEL_IMPL_FORWARD_0(boost::optional<Schedule>, operationModeControlSchedule)
EPMODEL_IMPL_FORWARD_1(bool, setOperationModeControlSchedule, Schedule&, schedule)
EPMODEL_IMPL_FORWARD_V(resetOperationModeControlSchedule)
EPMODEL_IMPL_FORWARD_0(std::string, storageType)
EPMODEL_IMPL_FORWARD_1(bool, setStorageType, const std::string&, storageType)
EPMODEL_IMPL_FORWARD_0(int, glycolConcentration)
EPMODEL_IMPL_FORWARD_1(bool, setGlycolConcentration, int, glycolConcentration)
EPMODEL_IMPL_FORWARD_0(boost::optional<double>, fluidStorageVolume)
EPMODEL_IMPL_FORWARD_0(bool, isFluidStorageVolumeAutosized)
EPMODEL_IMPL_FORWARD_1(bool, setFluidStorageVolume, double, fluidStorageVolume)
EPMODEL_IMPL_FORWARD_V(resetFluidStorageVolume)
EPMODEL_IMPL_FORWARD_V(autosizeFluidStorageVolume)
EPMODEL_IMPL_FORWARD_0(boost::optional<double>, iceStorageCapacity)
EPMODEL_IMPL_FORWARD_0(bool, isIceStorageCapacityAutosized)
EPMODEL_IMPL_FORWARD_1(bool, setIceStorageCapacity, double, iceStorageCapacity)
EPMODEL_IMPL_FORWARD_V(autosizeIceStorageCapacity)
EPMODEL_IMPL_FORWARD_0(boost::optional<double>, storageCapacitySizingFactor)
EPMODEL_IMPL_FORWARD_1(bool, setStorageCapacitySizingFactor, double, storageCapacitySizingFactor)
EPMODEL_IMPL_FORWARD_0(double, storageTanktoAmbientUvalueTimesAreaHeatTransferCoefficient)
EPMODEL_IMPL_FORWARD_1(bool, setStorageTanktoAmbientUvalueTimesAreaHeatTransferCoefficient, double,
                       storageTanktoAmbientUvalueTimesAreaHeatTransferCoefficient)
EPMODEL_IMPL_FORWARD_0(double, fluidStorageTankRatingTemperature)
EPMODEL_IMPL_FORWARD_1(bool, setFluidStorageTankRatingTemperature, double, fluidStorageTankRatingTemperature)
EPMODEL_IMPL_FORWARD_0(boost::optional<double>, ratedEvaporatorAirFlowRate)
EPMODEL_IMPL_FORWARD_0(bool, isRatedEvaporatorAirFlowRateAutosized)
EPMODEL_IMPL_FORWARD_1(bool, setRatedEvaporatorAirFlowRate, double, ratedEvaporatorAirFlowRate)
EPMODEL_IMPL_FORWARD_V(autosizeRatedEvaporatorAirFlowRate)
EPMODEL_IMPL_FORWARD_0(bool, coolingOnlyModeAvailable)
EPMODEL_IMPL_FORWARD_1(bool, setCoolingOnlyModeAvailable, bool, coolingOnlyModeAvailable)
EPMODEL_IMPL_FORWARD_0(boost::optional<double>, coolingOnlyModeRatedTotalEvaporatorCoolingCapacity)
EPMODEL_IMPL_FORWARD_0(bool, isCoolingOnlyModeRatedTotalEvaporatorCoolingCapacityAutosized)
EPMODEL_IMPL_FORWARD_1(bool, setCoolingOnlyModeRatedTotalEvaporatorCoolingCapacity, double, coolingOnlyModeRatedTotalEvaporatorCoolingCapacity)
EPMODEL_IMPL_FORWARD_V(autosizeCoolingOnlyModeRatedTotalEvaporatorCoolingCapacity)
EPMODEL_IMPL_FORWARD_0(double, coolingOnlyModeRatedSensibleHeatRatio)
EPMODEL_IMPL_FORWARD_1(bool, setCoolingOnlyModeRatedSensibleHeatRatio, double, coolingOnlyModeRatedSensibleHeatRatio)
EPMODEL_IMPL_FORWARD_0(double, coolingOnlyModeRatedCOP)
EPMODEL_IMPL_FORWARD_1(bool, setCoolingOnlyModeRatedCOP, double, coolingOnlyModeRatedCOP)
EPMODEL_IMPL_FORWARD_0(bool, coolingAndChargeModeAvailable)
EPMODEL_IMPL_FORWARD_1(bool, setCoolingAndChargeModeAvailable, bool, coolingAndChargeModeAvailable)
EPMODEL_IMPL_FORWARD_0(boost::optional<double>, coolingAndChargeModeRatedTotalEvaporatorCoolingCapacity)
EPMODEL_IMPL_FORWARD_0(bool, isCoolingAndChargeModeRatedTotalEvaporatorCoolingCapacityAutosized)
EPMODEL_IMPL_FORWARD_1(bool, setCoolingAndChargeModeRatedTotalEvaporatorCoolingCapacity, double,
                       coolingAndChargeModeRatedTotalEvaporatorCoolingCapacity)
EPMODEL_IMPL_FORWARD_V(autosizeCoolingAndChargeModeRatedTotalEvaporatorCoolingCapacity)
EPMODEL_IMPL_FORWARD_0(double, coolingAndChargeModeCapacitySizingFactor)
EPMODEL_IMPL_FORWARD_1(bool, setCoolingAndChargeModeCapacitySizingFactor, double, coolingAndChargeModeCapacitySizingFactor)
EPMODEL_IMPL_FORWARD_0(boost::optional<double>, coolingAndChargeModeRatedStorageChargingCapacity)
EPMODEL_IMPL_FORWARD_0(bool, isCoolingAndChargeModeRatedStorageChargingCapacityAutosized)
EPMODEL_IMPL_FORWARD_1(bool, setCoolingAndChargeModeRatedStorageChargingCapacity, double, coolingAndChargeModeRatedStorageChargingCapacity)
EPMODEL_IMPL_FORWARD_V(autosizeCoolingAndChargeModeRatedStorageChargingCapacity)
EPMODEL_IMPL_FORWARD_0(double, coolingAndChargeModeStorageCapacitySizingFactor)
EPMODEL_IMPL_FORWARD_1(bool, setCoolingAndChargeModeStorageCapacitySizingFactor, double, coolingAndChargeModeStorageCapacitySizingFactor)
EPMODEL_IMPL_FORWARD_0(double, coolingAndChargeModeRatedSensibleHeatRatio)
EPMODEL_IMPL_FORWARD_1(bool, setCoolingAndChargeModeRatedSensibleHeatRatio, double, coolingAndChargeModeRatedSensibleHeatRatio)
EPMODEL_IMPL_FORWARD_0(double, coolingAndChargeModeCoolingRatedCOP)
EPMODEL_IMPL_FORWARD_1(bool, setCoolingAndChargeModeCoolingRatedCOP, double, coolingAndChargeModeCoolingRatedCOP)
EPMODEL_IMPL_FORWARD_0(double, coolingAndChargeModeChargingRatedCOP)
EPMODEL_IMPL_FORWARD_1(bool, setCoolingAndChargeModeChargingRatedCOP, double, coolingAndChargeModeChargingRatedCOP)
EPMODEL_IMPL_FORWARD_0(bool, coolingAndDischargeModeAvailable)
EPMODEL_IMPL_FORWARD_1(bool, setCoolingAndDischargeModeAvailable, bool, coolingAndDischargeModeAvailable)
EPMODEL_IMPL_FORWARD_0(boost::optional<double>, coolingAndDischargeModeRatedTotalEvaporatorCoolingCapacity)
EPMODEL_IMPL_FORWARD_0(bool, isCoolingAndDischargeModeRatedTotalEvaporatorCoolingCapacityAutosized)
EPMODEL_IMPL_FORWARD_1(bool, setCoolingAndDischargeModeRatedTotalEvaporatorCoolingCapacity, double,
                       coolingAndDischargeModeRatedTotalEvaporatorCoolingCapacity)
EPMODEL_IMPL_FORWARD_V(autosizeCoolingAndDischargeModeRatedTotalEvaporatorCoolingCapacity)
EPMODEL_IMPL_FORWARD_0(double, coolingAndDischargeModeEvaporatorCapacitySizingFactor)
EPMODEL_IMPL_FORWARD_1(bool, setCoolingAndDischargeModeEvaporatorCapacitySizingFactor, double, coolingAndDischargeModeEvaporatorCapacitySizingFactor)
EPMODEL_IMPL_FORWARD_0(boost::optional<double>, coolingAndDischargeModeRatedStorageDischargingCapacity)
EPMODEL_IMPL_FORWARD_0(bool, isCoolingAndDischargeModeRatedStorageDischargingCapacityAutosized)
EPMODEL_IMPL_FORWARD_1(bool, setCoolingAndDischargeModeRatedStorageDischargingCapacity, double, coolingAndDischargeModeRatedStorageDischargingCapacity)
EPMODEL_IMPL_FORWARD_V(autosizeCoolingAndDischargeModeRatedStorageDischargingCapacity)
EPMODEL_IMPL_FORWARD_0(double, coolingAndDischargeModeStorageDischargeCapacitySizingFactor)
EPMODEL_IMPL_FORWARD_1(bool, setCoolingAndDischargeModeStorageDischargeCapacitySizingFactor, double,
                       coolingAndDischargeModeStorageDischargeCapacitySizingFactor)
EPMODEL_IMPL_FORWARD_0(double, coolingAndDischargeModeRatedSensibleHeatRatio)
EPMODEL_IMPL_FORWARD_1(bool, setCoolingAndDischargeModeRatedSensibleHeatRatio, double, coolingAndDischargeModeRatedSensibleHeatRatio)
EPMODEL_IMPL_FORWARD_0(double, coolingAndDischargeModeCoolingRatedCOP)
EPMODEL_IMPL_FORWARD_1(bool, setCoolingAndDischargeModeCoolingRatedCOP, double, coolingAndDischargeModeCoolingRatedCOP)
EPMODEL_IMPL_FORWARD_0(double, coolingAndDischargeModeDischargingRatedCOP)
EPMODEL_IMPL_FORWARD_1(bool, setCoolingAndDischargeModeDischargingRatedCOP, double, coolingAndDischargeModeDischargingRatedCOP)
EPMODEL_IMPL_FORWARD_0(bool, chargeOnlyModeAvailable)
EPMODEL_IMPL_FORWARD_1(bool, setChargeOnlyModeAvailable, bool, chargeOnlyModeAvailable)
EPMODEL_IMPL_FORWARD_0(boost::optional<double>, chargeOnlyModeRatedStorageChargingCapacity)
EPMODEL_IMPL_FORWARD_0(bool, isChargeOnlyModeRatedStorageChargingCapacityAutosized)
EPMODEL_IMPL_FORWARD_1(bool, setChargeOnlyModeRatedStorageChargingCapacity, double, chargeOnlyModeRatedStorageChargingCapacity)
EPMODEL_IMPL_FORWARD_V(autosizeChargeOnlyModeRatedStorageChargingCapacity)
EPMODEL_IMPL_FORWARD_0(double, chargeOnlyModeCapacitySizingFactor)
EPMODEL_IMPL_FORWARD_1(bool, setChargeOnlyModeCapacitySizingFactor, double, chargeOnlyModeCapacitySizingFactor)
EPMODEL_IMPL_FORWARD_0(double, chargeOnlyModeChargingRatedCOP)
EPMODEL_IMPL_FORWARD_1(bool, setChargeOnlyModeChargingRatedCOP, double, chargeOnlyModeChargingRatedCOP)
EPMODEL_IMPL_FORWARD_0(bool, dischargeOnlyModeAvailable)
EPMODEL_IMPL_FORWARD_1(bool, setDischargeOnlyModeAvailable, bool, dischargeOnlyModeAvailable)
EPMODEL_IMPL_FORWARD_0(boost::optional<double>, dischargeOnlyModeRatedStorageDischargingCapacity)
EPMODEL_IMPL_FORWARD_0(bool, isDischargeOnlyModeRatedStorageDischargingCapacityAutosized)
EPMODEL_IMPL_FORWARD_1(bool, setDischargeOnlyModeRatedStorageDischargingCapacity, double, dischargeOnlyModeRatedStorageDischargingCapacity)
EPMODEL_IMPL_FORWARD_V(autosizeDischargeOnlyModeRatedStorageDischargingCapacity)
EPMODEL_IMPL_FORWARD_0(double, dischargeOnlyModeCapacitySizingFactor)
EPMODEL_IMPL_FORWARD_1(bool, setDischargeOnlyModeCapacitySizingFactor, double, dischargeOnlyModeCapacitySizingFactor)
EPMODEL_IMPL_FORWARD_0(double, dischargeOnlyModeRatedSensibleHeatRatio)
EPMODEL_IMPL_FORWARD_1(bool, setDischargeOnlyModeRatedSensibleHeatRatio, double, dischargeOnlyModeRatedSensibleHeatRatio)
EPMODEL_IMPL_FORWARD_0(double, dischargeOnlyModeRatedCOP)
EPMODEL_IMPL_FORWARD_1(bool, setDischargeOnlyModeRatedCOP, double, dischargeOnlyModeRatedCOP)
EPMODEL_IMPL_FORWARD_0(boost::optional<double>, ancillaryElectricPower)
EPMODEL_IMPL_FORWARD_1(bool, setAncillaryElectricPower, double, ancillaryElectricPower)
EPMODEL_IMPL_FORWARD_0(boost::optional<double>, coldWeatherOperationMinimumOutdoorAirTemperature)
EPMODEL_IMPL_FORWARD_1(bool, setColdWeatherOperationMinimumOutdoorAirTemperature, double, coldWeatherOperationMinimumOutdoorAirTemperature)
EPMODEL_IMPL_FORWARD_V(resetColdWeatherOperationMinimumOutdoorAirTemperature)
EPMODEL_IMPL_FORWARD_0(boost::optional<double>, coldWeatherOperationAncillaryPower)
EPMODEL_IMPL_FORWARD_1(bool, setColdWeatherOperationAncillaryPower, double, coldWeatherOperationAncillaryPower)
EPMODEL_IMPL_FORWARD_0(boost::optional<double>, condenserDesignAirFlowRate)
EPMODEL_IMPL_FORWARD_0(bool, isCondenserDesignAirFlowRateAutosized)
EPMODEL_IMPL_FORWARD_1(bool, setCondenserDesignAirFlowRate, double, condenserDesignAirFlowRate)
EPMODEL_IMPL_FORWARD_V(autosizeCondenserDesignAirFlowRate)
EPMODEL_IMPL_FORWARD_0(double, condenserAirFlowSizingFactor)
EPMODEL_IMPL_FORWARD_1(bool, setCondenserAirFlowSizingFactor, double, condenserAirFlowSizingFactor)
EPMODEL_IMPL_FORWARD_0(std::string, condenserType)
EPMODEL_IMPL_FORWARD_1(bool, setCondenserType, const std::string&, condenserType)
EPMODEL_IMPL_FORWARD_0(double, evaporativeCondenserEffectiveness)
EPMODEL_IMPL_FORWARD_1(bool, setEvaporativeCondenserEffectiveness, double, evaporativeCondenserEffectiveness)
EPMODEL_IMPL_FORWARD_0(boost::optional<double>, evaporativeCondenserPumpRatedPowerConsumption)
EPMODEL_IMPL_FORWARD_0(bool, isEvaporativeCondenserPumpRatedPowerConsumptionAutosized)
EPMODEL_IMPL_FORWARD_1(bool, setEvaporativeCondenserPumpRatedPowerConsumption, double, evaporativeCondenserPumpRatedPowerConsumption)
EPMODEL_IMPL_FORWARD_V(autosizeEvaporativeCondenserPumpRatedPowerConsumption)
EPMODEL_IMPL_FORWARD_0(double, basinHeaterCapacity)
EPMODEL_IMPL_FORWARD_1(bool, setBasinHeaterCapacity, double, basinHeaterCapacity)
EPMODEL_IMPL_FORWARD_0(double, basinHeaterSetpointTemperature)
EPMODEL_IMPL_FORWARD_1(bool, setBasinHeaterSetpointTemperature, double, basinHeaterSetpointTemperature)
EPMODEL_IMPL_FORWARD_0(boost::optional<Schedule>, basinHeaterAvailabilitySchedule)
EPMODEL_IMPL_FORWARD_1(bool, setBasinHeaterAvailabilitySchedule, Schedule&, schedule)
EPMODEL_IMPL_FORWARD_V(resetBasinHeaterAvailabilitySchedule)
EPMODEL_IMPL_FORWARD_1(bool, addToNode, Node&, node)

#undef EPMODEL_IMPL_FORWARD_0
#undef EPMODEL_IMPL_FORWARD_1
#undef EPMODEL_IMPL_FORWARD_V

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
  const auto value = getDouble(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::StorageTanktoAmbientUvalueTimesAreaHeatTransferCoefficient,
                               true);
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
  return isAutosized(*this,
                     openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingOnlyModeRatedTotalEvaporatorCoolingCapacity);
}

bool CoilCoolingDXSingleSpeedThermalStorage_Impl::setCoolingOnlyModeRatedTotalEvaporatorCoolingCapacity(
  double coolingOnlyModeRatedTotalEvaporatorCoolingCapacity) {
  return setDouble(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingOnlyModeRatedTotalEvaporatorCoolingCapacity,
                   coolingOnlyModeRatedTotalEvaporatorCoolingCapacity);
}

void CoilCoolingDXSingleSpeedThermalStorage_Impl::autosizeCoolingOnlyModeRatedTotalEvaporatorCoolingCapacity() {
  const bool result = setString(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingOnlyModeRatedTotalEvaporatorCoolingCapacity,
                                "autosize");
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
  const bool result = setString(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndChargeModeRatedTotalEvaporatorCoolingCapacity,
                                "autosize");
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
  const bool result = setString(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndChargeModeRatedStorageChargingCapacity,
                                "autosize");
  OS_ASSERT(result);
}

double CoilCoolingDXSingleSpeedThermalStorage_Impl::coolingAndChargeModeStorageCapacitySizingFactor() const {
  const auto value = getDouble(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndChargeModeStorageCapacitySizingFactor, true);
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

bool CoilCoolingDXSingleSpeedThermalStorage_Impl::setCoolingAndChargeModeRatedSensibleHeatRatio(double coolingAndChargeModeRatedSensibleHeatRatio) {
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
  return getDouble(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndDischargeModeRatedTotalEvaporatorCoolingCapacity, true);
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
  const bool result =
    setString(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndDischargeModeRatedTotalEvaporatorCoolingCapacity,
              "autosize");
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
  return isAutosized(*this,
                     openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndDischargeModeRatedStorageDischargingCapacity);
}

bool CoilCoolingDXSingleSpeedThermalStorage_Impl::setCoolingAndDischargeModeRatedStorageDischargingCapacity(
  double coolingAndDischargeModeRatedStorageDischargingCapacity) {
  return setDouble(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndDischargeModeRatedStorageDischargingCapacity,
                   coolingAndDischargeModeRatedStorageDischargingCapacity);
}

void CoilCoolingDXSingleSpeedThermalStorage_Impl::autosizeCoolingAndDischargeModeRatedStorageDischargingCapacity() {
  const bool result = setString(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::CoolingAndDischargeModeRatedStorageDischargingCapacity,
                                "autosize");
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

bool CoilCoolingDXSingleSpeedThermalStorage_Impl::setCoolingAndDischargeModeDischargingRatedCOP(double coolingAndDischargeModeDischargingRatedCOP) {
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

bool CoilCoolingDXSingleSpeedThermalStorage_Impl::setChargeOnlyModeRatedStorageChargingCapacity(double chargeOnlyModeRatedStorageChargingCapacity) {
  return setDouble(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::ChargeOnlyModeRatedStorageChargingCapacity,
                   chargeOnlyModeRatedStorageChargingCapacity);
}

void CoilCoolingDXSingleSpeedThermalStorage_Impl::autosizeChargeOnlyModeRatedStorageChargingCapacity() {
  const bool result = setString(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::ChargeOnlyModeRatedStorageChargingCapacity,
                                "autosize");
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
  return setDouble(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::ChargeOnlyModeChargingRatedCOP,
                   chargeOnlyModeChargingRatedCOP);
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
  const bool result = setString(openstudio::Coil_Cooling_DX_SingleSpeed_ThermalStorageFields::DischargeOnlyModeRatedStorageDischargingCapacity,
                                "autosize");
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
