/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ZoneHVACComponent/WaterHeaterHeatPump.hpp"
#include "ZoneHVACComponent/WaterHeaterHeatPump_Impl.hpp"

#include "Model.hpp"
#include "ModelObject/ModelObject.hpp"
#include "ModelObject/ModelObject_Impl.hpp"
#include "HVACComponent/ThermalZone.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"
#include "Schedule/ScheduleConstant.hpp"
#include "StraightComponent/FanOnOff.hpp"
#include "StraightComponent/Node.hpp"
#include "StraightComponent/StraightComponent.hpp"
#include "WaterToAirComponent/CoilWaterHeatingAirToWaterHeatPump.hpp"
#include "WaterToAirComponent/CoilWaterHeatingAirToWaterHeatPump_Impl.hpp"
#include "WaterToAirComponent/CoilWaterHeatingAirToWaterHeatPumpVariableSpeed.hpp"
#include "WaterToAirComponent/CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl.hpp"
#include "WaterToAirComponent/WaterToAirComponent.hpp"
#include "WaterToAirComponent/WaterToAirComponent_Impl.hpp"
#include "WaterToWaterComponent/WaterHeaterMixed.hpp"
#include "WaterToWaterComponent/WaterHeaterMixed_Impl.hpp"
#include "WaterToWaterComponent/WaterHeaterStratified.hpp"
#include "WaterToWaterComponent/WaterHeaterStratified_Impl.hpp"
#include "WaterToWaterComponent/WaterToWaterComponent.hpp"
#include "WaterToWaterComponent/WaterToWaterComponent_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/WaterHeater_HeatPump_PumpedCondenser_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  namespace {

    // This water-heater family owns three concrete child roles:
    // a tank, a water-to-air DX coil, and a one-in/one-out air-side fan.
    // The checks stay local here on purpose so the supported child set is easy
    // to review without pushing another special case into a shared base helper.

    bool isSupportedHeatPumpWaterHeaterTank(const HVACComponent& component) {
      return static_cast<bool>(component.optionalCast<WaterHeaterMixed>()) || static_cast<bool>(component.optionalCast<WaterHeaterStratified>());
    }

    bool isSupportedHeatPumpWaterHeaterDXCoil(const ModelObject& object) {
      return static_cast<bool>(object.optionalCast<CoilWaterHeatingAirToWaterHeatPump>())
             || static_cast<bool>(object.optionalCast<CoilWaterHeatingAirToWaterHeatPumpVariableSpeed>());
    }

    boost::optional<WaterToAirComponent> heatPumpWaterHeaterDXCoil(const ModelObject& object) {
      if (auto coil = object.optionalCast<CoilWaterHeatingAirToWaterHeatPump>()) {
        return coil->cast<WaterToAirComponent>();
      }
      if (auto coil = object.optionalCast<CoilWaterHeatingAirToWaterHeatPumpVariableSpeed>()) {
        return coil->cast<WaterToAirComponent>();
      }
      return boost::none;
    }

    bool clearStringIfNeeded(ModelObject& object, unsigned fieldIndex) {
      if (auto value = object.getString(fieldIndex, true); value && !value->empty()) {
        return object.setString(fieldIndex, "");
      }
      return false;
    }

    bool assignNodeIfPresent(ModelObject& object, unsigned fieldIndex, const boost::optional<Node>& node) {
      if (node) {
        return object.getImpl<detail::ModelObject_Impl>()->setPointer(fieldIndex, node->handle(), false);
      }
      return clearStringIfNeeded(object, fieldIndex);
    }

  }  // namespace

  WaterHeaterHeatPump::WaterHeaterHeatPump(const Model& model) : ZoneHVACComponent(WaterHeaterHeatPump::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::WaterHeaterHeatPump_Impl>());

    CoilWaterHeatingAirToWaterHeatPump dxCoil(model);
    OS_ASSERT(setDXCoil(dxCoil));

    WaterHeaterMixed tank(model);
    OS_ASSERT(setTank(tank));

    FanOnOff fan(model);
    OS_ASSERT(setFan(fan));

    ScheduleConstant availability(model);
    OS_ASSERT(availability.setValue(1.0));
    OS_ASSERT(setAvailabilitySchedule(availability));

    ScheduleConstant compressorSetpoint(model);
    OS_ASSERT(compressorSetpoint.setValue(60.0));
    OS_ASSERT(setCompressorSetpointTemperatureSchedule(compressorSetpoint));

    ScheduleConstant inletAirMixer(model);
    OS_ASSERT(inletAirMixer.setValue(0.2));
    OS_ASSERT(setInletAirMixerSchedule(inletAirMixer));

    ScheduleConstant inletAirTemperature(model);
    OS_ASSERT(inletAirTemperature.setValue(19.7));
    OS_ASSERT(setInletAirTemperatureSchedule(inletAirTemperature));

    ScheduleConstant inletAirHumidity(model);
    OS_ASSERT(inletAirHumidity.setValue(0.5));
    OS_ASSERT(setInletAirHumiditySchedule(inletAirHumidity));

    ScheduleConstant compressorAmbient(model);
    OS_ASSERT(compressorAmbient.setValue(21.0));
    OS_ASSERT(setCompressorAmbientTemperatureSchedule(compressorAmbient));

    OS_ASSERT(setDeadBandTemperatureDifference(5.0));
    autosizeCondenserWaterFlowRate();
    autosizeEvaporatorAirFlowRate();
    OS_ASSERT(setInletAirConfiguration("Schedule"));
    OS_ASSERT(setMinimumInletAirTemperatureforCompressorOperation(10.0));
    OS_ASSERT(setMaximumInletAirTemperatureforCompressorOperation(48.89));
    OS_ASSERT(setCompressorLocation("Schedule"));
    OS_ASSERT(setFanPlacement("DrawThrough"));
    OS_ASSERT(setOnCycleParasiticElectricLoad(0.0));
    OS_ASSERT(setOffCycleParasiticElectricLoad(0.0));
    OS_ASSERT(setParasiticHeatRejectionLocation("Outdoors"));
    OS_ASSERT(setTankElementControlLogic("Simultaneous"));
    OS_ASSERT(setControlSensor1Weight(1.0));
  }

  WaterHeaterHeatPump::WaterHeaterHeatPump(std::shared_ptr<detail::WaterHeaterHeatPump_Impl> impl)
    : ZoneHVACComponent(std::move(impl)) {}

  IddObjectType WaterHeaterHeatPump::iddObjectType() {
    return IddObjectType::WaterHeater_HeatPump_PumpedCondenser;
  }

  std::vector<std::string> WaterHeaterHeatPump::inletAirConfigurationValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::WaterHeater_HeatPump_PumpedCondenserFields::InletAirConfiguration);
  }

  std::vector<std::string> WaterHeaterHeatPump::compressorLocationValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::WaterHeater_HeatPump_PumpedCondenserFields::CompressorLocation);
  }

  std::vector<std::string> WaterHeaterHeatPump::fanPlacementValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::WaterHeater_HeatPump_PumpedCondenserFields::FanPlacement);
  }

  std::vector<std::string> WaterHeaterHeatPump::parasiticHeatRejectionLocationValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::WaterHeater_HeatPump_PumpedCondenserFields::ParasiticHeatRejectionLocation);
  }

  std::vector<std::string> WaterHeaterHeatPump::tankElementControlLogicValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::WaterHeater_HeatPump_PumpedCondenserFields::TankElementControlLogic);
  }

  boost::optional<Schedule> WaterHeaterHeatPump::availabilitySchedule() const {
    return getImpl<detail::WaterHeaterHeatPump_Impl>()->availabilitySchedule();
  }

  bool WaterHeaterHeatPump::setAvailabilitySchedule(Schedule& schedule) {
    return getImpl<detail::WaterHeaterHeatPump_Impl>()->setAvailabilitySchedule(schedule);
  }

  void WaterHeaterHeatPump::resetAvailabilitySchedule() {
    getImpl<detail::WaterHeaterHeatPump_Impl>()->resetAvailabilitySchedule();
  }

  Schedule WaterHeaterHeatPump::compressorSetpointTemperatureSchedule() const {
    return getImpl<detail::WaterHeaterHeatPump_Impl>()->compressorSetpointTemperatureSchedule();
  }

  bool WaterHeaterHeatPump::setCompressorSetpointTemperatureSchedule(Schedule& schedule) {
    return getImpl<detail::WaterHeaterHeatPump_Impl>()->setCompressorSetpointTemperatureSchedule(schedule);
  }

  double WaterHeaterHeatPump::deadBandTemperatureDifference() const {
    return getImpl<detail::WaterHeaterHeatPump_Impl>()->deadBandTemperatureDifference();
  }

  bool WaterHeaterHeatPump::isDeadBandTemperatureDifferenceDefaulted() const {
    return getImpl<detail::WaterHeaterHeatPump_Impl>()->isDeadBandTemperatureDifferenceDefaulted();
  }

  bool WaterHeaterHeatPump::setDeadBandTemperatureDifference(double deadBandTemperatureDifference) {
    return getImpl<detail::WaterHeaterHeatPump_Impl>()->setDeadBandTemperatureDifference(deadBandTemperatureDifference);
  }

  void WaterHeaterHeatPump::resetDeadBandTemperatureDifference() {
    getImpl<detail::WaterHeaterHeatPump_Impl>()->resetDeadBandTemperatureDifference();
  }

  boost::optional<double> WaterHeaterHeatPump::condenserWaterFlowRate() const {
    return getImpl<detail::WaterHeaterHeatPump_Impl>()->condenserWaterFlowRate();
  }

  bool WaterHeaterHeatPump::isCondenserWaterFlowRateAutosized() const {
    return getImpl<detail::WaterHeaterHeatPump_Impl>()->isCondenserWaterFlowRateAutosized();
  }

  bool WaterHeaterHeatPump::setCondenserWaterFlowRate(double condenserWaterFlowRate) {
    return getImpl<detail::WaterHeaterHeatPump_Impl>()->setCondenserWaterFlowRate(condenserWaterFlowRate);
  }

  void WaterHeaterHeatPump::resetCondenserWaterFlowRate() {
    getImpl<detail::WaterHeaterHeatPump_Impl>()->resetCondenserWaterFlowRate();
  }

  void WaterHeaterHeatPump::autosizeCondenserWaterFlowRate() {
    getImpl<detail::WaterHeaterHeatPump_Impl>()->autosizeCondenserWaterFlowRate();
  }

  boost::optional<double> WaterHeaterHeatPump::evaporatorAirFlowRate() const {
    return getImpl<detail::WaterHeaterHeatPump_Impl>()->evaporatorAirFlowRate();
  }

  bool WaterHeaterHeatPump::isEvaporatorAirFlowRateAutosized() const {
    return getImpl<detail::WaterHeaterHeatPump_Impl>()->isEvaporatorAirFlowRateAutosized();
  }

  bool WaterHeaterHeatPump::setEvaporatorAirFlowRate(double evaporatorAirFlowRate) {
    return getImpl<detail::WaterHeaterHeatPump_Impl>()->setEvaporatorAirFlowRate(evaporatorAirFlowRate);
  }

  void WaterHeaterHeatPump::resetEvaporatorAirFlowRate() {
    getImpl<detail::WaterHeaterHeatPump_Impl>()->resetEvaporatorAirFlowRate();
  }

  void WaterHeaterHeatPump::autosizeEvaporatorAirFlowRate() {
    getImpl<detail::WaterHeaterHeatPump_Impl>()->autosizeEvaporatorAirFlowRate();
  }

  std::string WaterHeaterHeatPump::inletAirConfiguration() const {
    return getImpl<detail::WaterHeaterHeatPump_Impl>()->inletAirConfiguration();
  }

  bool WaterHeaterHeatPump::setInletAirConfiguration(const std::string& inletAirConfiguration) {
    return getImpl<detail::WaterHeaterHeatPump_Impl>()->setInletAirConfiguration(inletAirConfiguration);
  }

  boost::optional<Schedule> WaterHeaterHeatPump::inletAirTemperatureSchedule() const {
    return getImpl<detail::WaterHeaterHeatPump_Impl>()->inletAirTemperatureSchedule();
  }

  bool WaterHeaterHeatPump::setInletAirTemperatureSchedule(Schedule& schedule) {
    return getImpl<detail::WaterHeaterHeatPump_Impl>()->setInletAirTemperatureSchedule(schedule);
  }

  void WaterHeaterHeatPump::resetInletAirTemperatureSchedule() {
    getImpl<detail::WaterHeaterHeatPump_Impl>()->resetInletAirTemperatureSchedule();
  }

  boost::optional<Schedule> WaterHeaterHeatPump::inletAirHumiditySchedule() const {
    return getImpl<detail::WaterHeaterHeatPump_Impl>()->inletAirHumiditySchedule();
  }

  bool WaterHeaterHeatPump::setInletAirHumiditySchedule(Schedule& schedule) {
    return getImpl<detail::WaterHeaterHeatPump_Impl>()->setInletAirHumiditySchedule(schedule);
  }

  void WaterHeaterHeatPump::resetInletAirHumiditySchedule() {
    getImpl<detail::WaterHeaterHeatPump_Impl>()->resetInletAirHumiditySchedule();
  }

  HVACComponent WaterHeaterHeatPump::tank() const {
    return getImpl<detail::WaterHeaterHeatPump_Impl>()->tank();
  }

  bool WaterHeaterHeatPump::setTank(const HVACComponent& waterHeater) {
    return getImpl<detail::WaterHeaterHeatPump_Impl>()->setTank(waterHeater);
  }

  ModelObject WaterHeaterHeatPump::dXCoil() const {
    return getImpl<detail::WaterHeaterHeatPump_Impl>()->dXCoil();
  }

  bool WaterHeaterHeatPump::setDXCoil(const ModelObject& heatPumpWaterHeaterDXCoil) {
    return getImpl<detail::WaterHeaterHeatPump_Impl>()->setDXCoil(heatPumpWaterHeaterDXCoil);
  }

  double WaterHeaterHeatPump::minimumInletAirTemperatureforCompressorOperation() const {
    return getImpl<detail::WaterHeaterHeatPump_Impl>()->minimumInletAirTemperatureforCompressorOperation();
  }

  bool WaterHeaterHeatPump::isMinimumInletAirTemperatureforCompressorOperationDefaulted() const {
    return getImpl<detail::WaterHeaterHeatPump_Impl>()->isMinimumInletAirTemperatureforCompressorOperationDefaulted();
  }

  bool WaterHeaterHeatPump::setMinimumInletAirTemperatureforCompressorOperation(double minimumInletAirTemperatureforCompressorOperation) {
    return getImpl<detail::WaterHeaterHeatPump_Impl>()->setMinimumInletAirTemperatureforCompressorOperation(
      minimumInletAirTemperatureforCompressorOperation);
  }

  void WaterHeaterHeatPump::resetMinimumInletAirTemperatureforCompressorOperation() {
    getImpl<detail::WaterHeaterHeatPump_Impl>()->resetMinimumInletAirTemperatureforCompressorOperation();
  }

  double WaterHeaterHeatPump::maximumInletAirTemperatureforCompressorOperation() const {
    return getImpl<detail::WaterHeaterHeatPump_Impl>()->maximumInletAirTemperatureforCompressorOperation();
  }

  bool WaterHeaterHeatPump::isMaximumInletAirTemperatureforCompressorOperationDefaulted() const {
    return getImpl<detail::WaterHeaterHeatPump_Impl>()->isMaximumInletAirTemperatureforCompressorOperationDefaulted();
  }

  bool WaterHeaterHeatPump::setMaximumInletAirTemperatureforCompressorOperation(double maximumInletAirTemperatureforCompressorOperation) {
    return getImpl<detail::WaterHeaterHeatPump_Impl>()->setMaximumInletAirTemperatureforCompressorOperation(
      maximumInletAirTemperatureforCompressorOperation);
  }

  void WaterHeaterHeatPump::resetMaximumInletAirTemperatureforCompressorOperation() {
    getImpl<detail::WaterHeaterHeatPump_Impl>()->resetMaximumInletAirTemperatureforCompressorOperation();
  }

  std::string WaterHeaterHeatPump::compressorLocation() const {
    return getImpl<detail::WaterHeaterHeatPump_Impl>()->compressorLocation();
  }

  bool WaterHeaterHeatPump::setCompressorLocation(const std::string& compressorLocation) {
    return getImpl<detail::WaterHeaterHeatPump_Impl>()->setCompressorLocation(compressorLocation);
  }

  boost::optional<Schedule> WaterHeaterHeatPump::compressorAmbientTemperatureSchedule() const {
    return getImpl<detail::WaterHeaterHeatPump_Impl>()->compressorAmbientTemperatureSchedule();
  }

  bool WaterHeaterHeatPump::setCompressorAmbientTemperatureSchedule(Schedule& schedule) {
    return getImpl<detail::WaterHeaterHeatPump_Impl>()->setCompressorAmbientTemperatureSchedule(schedule);
  }

  void WaterHeaterHeatPump::resetCompressorAmbientTemperatureSchedule() {
    getImpl<detail::WaterHeaterHeatPump_Impl>()->resetCompressorAmbientTemperatureSchedule();
  }

  HVACComponent WaterHeaterHeatPump::fan() const {
    return getImpl<detail::WaterHeaterHeatPump_Impl>()->fan();
  }

  bool WaterHeaterHeatPump::setFan(const HVACComponent& fan) {
    return getImpl<detail::WaterHeaterHeatPump_Impl>()->setFan(fan);
  }

  std::string WaterHeaterHeatPump::fanPlacement() const {
    return getImpl<detail::WaterHeaterHeatPump_Impl>()->fanPlacement();
  }

  bool WaterHeaterHeatPump::isFanPlacementDefaulted() const {
    return getImpl<detail::WaterHeaterHeatPump_Impl>()->isFanPlacementDefaulted();
  }

  bool WaterHeaterHeatPump::setFanPlacement(const std::string& fanPlacement) {
    return getImpl<detail::WaterHeaterHeatPump_Impl>()->setFanPlacement(fanPlacement);
  }

  void WaterHeaterHeatPump::resetFanPlacement() {
    getImpl<detail::WaterHeaterHeatPump_Impl>()->resetFanPlacement();
  }

  double WaterHeaterHeatPump::onCycleParasiticElectricLoad() const {
    return getImpl<detail::WaterHeaterHeatPump_Impl>()->onCycleParasiticElectricLoad();
  }

  bool WaterHeaterHeatPump::isOnCycleParasiticElectricLoadDefaulted() const {
    return getImpl<detail::WaterHeaterHeatPump_Impl>()->isOnCycleParasiticElectricLoadDefaulted();
  }

  bool WaterHeaterHeatPump::setOnCycleParasiticElectricLoad(double onCycleParasiticElectricLoad) {
    return getImpl<detail::WaterHeaterHeatPump_Impl>()->setOnCycleParasiticElectricLoad(onCycleParasiticElectricLoad);
  }

  void WaterHeaterHeatPump::resetOnCycleParasiticElectricLoad() {
    getImpl<detail::WaterHeaterHeatPump_Impl>()->resetOnCycleParasiticElectricLoad();
  }

  double WaterHeaterHeatPump::offCycleParasiticElectricLoad() const {
    return getImpl<detail::WaterHeaterHeatPump_Impl>()->offCycleParasiticElectricLoad();
  }

  bool WaterHeaterHeatPump::isOffCycleParasiticElectricLoadDefaulted() const {
    return getImpl<detail::WaterHeaterHeatPump_Impl>()->isOffCycleParasiticElectricLoadDefaulted();
  }

  bool WaterHeaterHeatPump::setOffCycleParasiticElectricLoad(double offCycleParasiticElectricLoad) {
    return getImpl<detail::WaterHeaterHeatPump_Impl>()->setOffCycleParasiticElectricLoad(offCycleParasiticElectricLoad);
  }

  void WaterHeaterHeatPump::resetOffCycleParasiticElectricLoad() {
    getImpl<detail::WaterHeaterHeatPump_Impl>()->resetOffCycleParasiticElectricLoad();
  }

  std::string WaterHeaterHeatPump::parasiticHeatRejectionLocation() const {
    return getImpl<detail::WaterHeaterHeatPump_Impl>()->parasiticHeatRejectionLocation();
  }

  bool WaterHeaterHeatPump::isParasiticHeatRejectionLocationDefaulted() const {
    return getImpl<detail::WaterHeaterHeatPump_Impl>()->isParasiticHeatRejectionLocationDefaulted();
  }

  bool WaterHeaterHeatPump::setParasiticHeatRejectionLocation(const std::string& parasiticHeatRejectionLocation) {
    return getImpl<detail::WaterHeaterHeatPump_Impl>()->setParasiticHeatRejectionLocation(parasiticHeatRejectionLocation);
  }

  void WaterHeaterHeatPump::resetParasiticHeatRejectionLocation() {
    getImpl<detail::WaterHeaterHeatPump_Impl>()->resetParasiticHeatRejectionLocation();
  }

  Schedule WaterHeaterHeatPump::inletAirMixerSchedule() const {
    return getImpl<detail::WaterHeaterHeatPump_Impl>()->inletAirMixerSchedule();
  }

  bool WaterHeaterHeatPump::setInletAirMixerSchedule(Schedule& schedule) {
    return getImpl<detail::WaterHeaterHeatPump_Impl>()->setInletAirMixerSchedule(schedule);
  }

  std::string WaterHeaterHeatPump::tankElementControlLogic() const {
    return getImpl<detail::WaterHeaterHeatPump_Impl>()->tankElementControlLogic();
  }

  bool WaterHeaterHeatPump::isTankElementControlLogicDefaulted() const {
    return getImpl<detail::WaterHeaterHeatPump_Impl>()->isTankElementControlLogicDefaulted();
  }

  bool WaterHeaterHeatPump::setTankElementControlLogic(const std::string& tankElementControlLogic) {
    return getImpl<detail::WaterHeaterHeatPump_Impl>()->setTankElementControlLogic(tankElementControlLogic);
  }

  void WaterHeaterHeatPump::resetTankElementControlLogic() {
    getImpl<detail::WaterHeaterHeatPump_Impl>()->resetTankElementControlLogic();
  }

  boost::optional<Node> WaterHeaterHeatPump::fanOutletNode() const {
    return getImpl<detail::WaterHeaterHeatPump_Impl>()->fanOutletNode();
  }

  boost::optional<Node> WaterHeaterHeatPump::mixedAirNode() const {
    return getImpl<detail::WaterHeaterHeatPump_Impl>()->mixedAirNode();
  }

  boost::optional<Node> WaterHeaterHeatPump::outdoorAirNode() const {
    return getImpl<detail::WaterHeaterHeatPump_Impl>()->outdoorAirNode();
  }

  boost::optional<Node> WaterHeaterHeatPump::reliefAirNode() const {
    return getImpl<detail::WaterHeaterHeatPump_Impl>()->reliefAirNode();
  }

  boost::optional<Node> WaterHeaterHeatPump::condenserWaterInletNode() const {
    return getImpl<detail::WaterHeaterHeatPump_Impl>()->condenserWaterInletNode();
  }

  boost::optional<Node> WaterHeaterHeatPump::condenserWaterOutletNode() const {
    return getImpl<detail::WaterHeaterHeatPump_Impl>()->condenserWaterOutletNode();
  }

  std::vector<ModelObject> WaterHeaterHeatPump::children() const {
    return getImpl<detail::WaterHeaterHeatPump_Impl>()->children();
  }

  boost::optional<double> WaterHeaterHeatPump::controlSensor1HeightInStratifiedTank() const {
    return getImpl<detail::WaterHeaterHeatPump_Impl>()->controlSensor1HeightInStratifiedTank();
  }

  bool WaterHeaterHeatPump::setControlSensor1HeightInStratifiedTank(double controlSensor1HeightInStratifiedTank) {
    return getImpl<detail::WaterHeaterHeatPump_Impl>()->setControlSensor1HeightInStratifiedTank(controlSensor1HeightInStratifiedTank);
  }

  void WaterHeaterHeatPump::resetControlSensor1HeightInStratifiedTank() {
    getImpl<detail::WaterHeaterHeatPump_Impl>()->resetControlSensor1HeightInStratifiedTank();
  }

  double WaterHeaterHeatPump::controlSensor1Weight() const {
    return getImpl<detail::WaterHeaterHeatPump_Impl>()->controlSensor1Weight();
  }

  bool WaterHeaterHeatPump::isControlSensor1WeightDefaulted() const {
    return getImpl<detail::WaterHeaterHeatPump_Impl>()->isControlSensor1WeightDefaulted();
  }

  bool WaterHeaterHeatPump::setControlSensor1Weight(double controlSensor1Weight) {
    return getImpl<detail::WaterHeaterHeatPump_Impl>()->setControlSensor1Weight(controlSensor1Weight);
  }

  void WaterHeaterHeatPump::resetControlSensor1Weight() {
    getImpl<detail::WaterHeaterHeatPump_Impl>()->resetControlSensor1Weight();
  }

  boost::optional<double> WaterHeaterHeatPump::controlSensor2HeightInStratifiedTank() const {
    return getImpl<detail::WaterHeaterHeatPump_Impl>()->controlSensor2HeightInStratifiedTank();
  }

  bool WaterHeaterHeatPump::setControlSensor2HeightInStratifiedTank(double controlSensor2HeightInStratifiedTank) {
    return getImpl<detail::WaterHeaterHeatPump_Impl>()->setControlSensor2HeightInStratifiedTank(controlSensor2HeightInStratifiedTank);
  }

  void WaterHeaterHeatPump::resetControlSensor2HeightInStratifiedTank() {
    getImpl<detail::WaterHeaterHeatPump_Impl>()->resetControlSensor2HeightInStratifiedTank();
  }

  namespace detail {

    boost::optional<Schedule> WaterHeaterHeatPump_Impl::availabilitySchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(WaterHeater_HeatPump_PumpedCondenserFields::AvailabilityScheduleName);
    }

    bool WaterHeaterHeatPump_Impl::setAvailabilitySchedule(Schedule& schedule) {
      return setSchedule(WaterHeater_HeatPump_PumpedCondenserFields::AvailabilityScheduleName, "WaterHeaterHeatPump", "Availability", schedule);
    }

    void WaterHeaterHeatPump_Impl::resetAvailabilitySchedule() {
      OS_ASSERT(setString(WaterHeater_HeatPump_PumpedCondenserFields::AvailabilityScheduleName, ""));
    }

    Schedule WaterHeaterHeatPump_Impl::compressorSetpointTemperatureSchedule() const {
      auto value = getObject<ModelObject>().getModelObjectTarget<Schedule>(
        WaterHeater_HeatPump_PumpedCondenserFields::CompressorSetpointTemperatureScheduleName);
      OS_ASSERT(value);
      return *value;
    }

    bool WaterHeaterHeatPump_Impl::setCompressorSetpointTemperatureSchedule(Schedule& schedule) {
      return setSchedule(WaterHeater_HeatPump_PumpedCondenserFields::CompressorSetpointTemperatureScheduleName, "WaterHeaterHeatPump",
                         "Compressor Setpoint Temperature", schedule);
    }

    boost::optional<Schedule> WaterHeaterHeatPump_Impl::inletAirTemperatureSchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(WaterHeater_HeatPump_PumpedCondenserFields::InletAirTemperatureScheduleName);
    }

    bool WaterHeaterHeatPump_Impl::setInletAirTemperatureSchedule(Schedule& schedule) {
      return setSchedule(WaterHeater_HeatPump_PumpedCondenserFields::InletAirTemperatureScheduleName, "WaterHeaterHeatPump",
                         "Inlet Air Temperature", schedule);
    }

    void WaterHeaterHeatPump_Impl::resetInletAirTemperatureSchedule() {
      OS_ASSERT(setString(WaterHeater_HeatPump_PumpedCondenserFields::InletAirTemperatureScheduleName, ""));
    }

    boost::optional<Schedule> WaterHeaterHeatPump_Impl::inletAirHumiditySchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(WaterHeater_HeatPump_PumpedCondenserFields::InletAirHumidityScheduleName);
    }

    bool WaterHeaterHeatPump_Impl::setInletAirHumiditySchedule(Schedule& schedule) {
      return setSchedule(WaterHeater_HeatPump_PumpedCondenserFields::InletAirHumidityScheduleName, "WaterHeaterHeatPump",
                         "Inlet Air Humidity", schedule);
    }

    void WaterHeaterHeatPump_Impl::resetInletAirHumiditySchedule() {
      OS_ASSERT(setString(WaterHeater_HeatPump_PumpedCondenserFields::InletAirHumidityScheduleName, ""));
    }

    HVACComponent WaterHeaterHeatPump_Impl::tank() const {
      auto value = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(WaterHeater_HeatPump_PumpedCondenserFields::TankName);
      OS_ASSERT(value);
      return *value;
    }

    bool WaterHeaterHeatPump_Impl::setTank(const HVACComponent& waterHeater) {
      if ((waterHeater.model() != model()) || !isSupportedHeatPumpWaterHeaterTank(waterHeater)) {
        return false;
      }

      const bool result = setPointer(WaterHeater_HeatPump_PumpedCondenserFields::TankName, waterHeater.handle(), false);
      if (result) {
        maintainContainedTopology();
      }
      return result;
    }

    ModelObject WaterHeaterHeatPump_Impl::dXCoil() const {
      auto value = getObject<ModelObject>().getModelObjectTarget<ModelObject>(WaterHeater_HeatPump_PumpedCondenserFields::DXCoilName);
      OS_ASSERT(value);
      return *value;
    }

    bool WaterHeaterHeatPump_Impl::setDXCoil(const ModelObject& heatPumpWaterHeaterDXCoil) {
      if ((heatPumpWaterHeaterDXCoil.model() != model()) || !isSupportedHeatPumpWaterHeaterDXCoil(heatPumpWaterHeaterDXCoil)) {
        return false;
      }

      const bool result = setPointer(WaterHeater_HeatPump_PumpedCondenserFields::DXCoilName, heatPumpWaterHeaterDXCoil.handle(), false);
      if (result) {
        maintainContainedTopology();
      }
      return result;
    }

    boost::optional<Schedule> WaterHeaterHeatPump_Impl::compressorAmbientTemperatureSchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(
        WaterHeater_HeatPump_PumpedCondenserFields::CompressorAmbientTemperatureScheduleName);
    }

    bool WaterHeaterHeatPump_Impl::setCompressorAmbientTemperatureSchedule(Schedule& schedule) {
      return setSchedule(WaterHeater_HeatPump_PumpedCondenserFields::CompressorAmbientTemperatureScheduleName, "WaterHeaterHeatPump",
                         "Compressor Ambient Temperature", schedule);
    }

    void WaterHeaterHeatPump_Impl::resetCompressorAmbientTemperatureSchedule() {
      OS_ASSERT(setString(WaterHeater_HeatPump_PumpedCondenserFields::CompressorAmbientTemperatureScheduleName, ""));
    }

    HVACComponent WaterHeaterHeatPump_Impl::fan() const {
      auto value = getObject<ModelObject>().getModelObjectTarget<StraightComponent>(WaterHeater_HeatPump_PumpedCondenserFields::FanName);
      OS_ASSERT(value);
      return value->cast<HVACComponent>();
    }

    bool WaterHeaterHeatPump_Impl::setFan(const HVACComponent& fanComponent) {
      if ((fanComponent.model() != model()) || !fanComponent.optionalCast<StraightComponent>()) {
        return false;
      }

      const bool result = setPointer(WaterHeater_HeatPump_PumpedCondenserFields::FanName, fanComponent.handle(), false);
      if (result) {
        maintainContainedTopology();
      }
      return result;
    }

    Schedule WaterHeaterHeatPump_Impl::inletAirMixerSchedule() const {
      auto value = getObject<ModelObject>().getModelObjectTarget<Schedule>(WaterHeater_HeatPump_PumpedCondenserFields::InletAirMixerScheduleName);
      OS_ASSERT(value);
      return *value;
    }

    bool WaterHeaterHeatPump_Impl::setInletAirMixerSchedule(Schedule& schedule) {
      return setSchedule(WaterHeater_HeatPump_PumpedCondenserFields::InletAirMixerScheduleName, "WaterHeaterHeatPump",
                         "Inlet Air Mixer", schedule);
    }

    boost::optional<Node> WaterHeaterHeatPump_Impl::fanOutletNode() const {
      auto fanComponent = getObject<ModelObject>().getModelObjectTarget<StraightComponent>(WaterHeater_HeatPump_PumpedCondenserFields::FanName);
      if (!fanComponent) {
        return boost::none;
      }
      return fanComponent->getImpl<detail::ModelObject_Impl>()->resolvedNodeTarget(fanComponent->outletPort());
    }

    boost::optional<Node> WaterHeaterHeatPump_Impl::mixedAirNode() const {
      return resolvedNodeTarget(WaterHeater_HeatPump_PumpedCondenserFields::InletAirMixerNodeName);
    }

    boost::optional<Node> WaterHeaterHeatPump_Impl::outdoorAirNode() const {
      return resolvedNodeTarget(WaterHeater_HeatPump_PumpedCondenserFields::OutdoorAirNodeName);
    }

    boost::optional<Node> WaterHeaterHeatPump_Impl::reliefAirNode() const {
      return resolvedNodeTarget(WaterHeater_HeatPump_PumpedCondenserFields::ExhaustAirNodeName);
    }

    boost::optional<Node> WaterHeaterHeatPump_Impl::condenserWaterInletNode() const {
      return resolvedNodeTarget(WaterHeater_HeatPump_PumpedCondenserFields::CondenserWaterInletNodeName);
    }

    boost::optional<Node> WaterHeaterHeatPump_Impl::condenserWaterOutletNode() const {
      return resolvedNodeTarget(WaterHeater_HeatPump_PumpedCondenserFields::CondenserWaterOutletNodeName);
    }

    std::vector<ModelObject> WaterHeaterHeatPump_Impl::children() const {
      std::vector<ModelObject> result;
      if (auto child = getObject<ModelObject>().getModelObjectTarget<ModelObject>(WaterHeater_HeatPump_PumpedCondenserFields::TankName)) {
        result.push_back(*child);
      }
      if (auto child = getObject<ModelObject>().getModelObjectTarget<ModelObject>(WaterHeater_HeatPump_PumpedCondenserFields::DXCoilName)) {
        result.push_back(*child);
      }
      if (auto child = getObject<ModelObject>().getModelObjectTarget<ModelObject>(WaterHeater_HeatPump_PumpedCondenserFields::FanName)) {
        result.push_back(*child);
      }
      return result;
    }

    unsigned WaterHeaterHeatPump_Impl::inletPort() const {
      return WaterHeater_HeatPump_PumpedCondenserFields::AirInletNodeName;
    }

    unsigned WaterHeaterHeatPump_Impl::outletPort() const {
      return WaterHeater_HeatPump_PumpedCondenserFields::AirOutletNodeName;
    }

    bool WaterHeaterHeatPump_Impl::addToThermalZone(ThermalZone& thermalZone) {
      if (!ZoneHVACComponent_Impl::addToThermalZone(thermalZone)) {
        return false;
      }
      setCompressorLocation("Zone");
      setInletAirConfiguration("ZoneAirOnly");
      maintainContainedTopology();
      return true;
    }

    void WaterHeaterHeatPump_Impl::removeFromThermalZone() {
      ZoneHVACComponent_Impl::removeFromThermalZone();
      maintainContainedTopology();
    }

    void WaterHeaterHeatPump_Impl::doCanonicalize(LoadContext& context) {
      ZoneHVACComponent_Impl::doCanonicalize(context);
      repairContainedTopology(context);
    }

    bool WaterHeaterHeatPump_Impl::maintainContainedTopology() {
      return reconcileContainedTopology(false, nullptr);
    }

    bool WaterHeaterHeatPump_Impl::repairContainedTopology(LoadContext& context) {
      return reconcileContainedTopology(true, &context);
    }

    bool WaterHeaterHeatPump_Impl::reconcileContainedTopology(bool allowNodeRecovery, LoadContext* /*context*/) {
      auto thisObject = getObject<ModelObject>();
      if (!thisObject.name()) {
        thisObject.createName();
      }
      const std::string baseName = thisObject.nameString();

      auto tankObject = thisObject.getModelObjectTarget<HVACComponent>(WaterHeater_HeatPump_PumpedCondenserFields::TankName);
      auto dxObject = thisObject.getModelObjectTarget<ModelObject>(WaterHeater_HeatPump_PumpedCondenserFields::DXCoilName);
      auto fanObject = thisObject.getModelObjectTarget<StraightComponent>(WaterHeater_HeatPump_PumpedCondenserFields::FanName);

      auto tankComponent =
        (tankObject && isSupportedHeatPumpWaterHeaterTank(*tankObject)) ? tankObject->optionalCast<WaterToWaterComponent>() : boost::none;
      auto dxCoil = dxObject ? heatPumpWaterHeaterDXCoil(*dxObject) : boost::none;

      bool changed = false;
      auto syncObjectType = [&](unsigned fieldIndex, const boost::optional<std::string>& expectedType) {
        const auto currentType = thisObject.getString(fieldIndex, true);
        if (expectedType) {
          if (!currentType || !openstudio::istringEqual(*currentType, *expectedType)) {
            OS_ASSERT(thisObject.setString(fieldIndex, *expectedType));
            changed = true;
          }
        } else if (currentType && !currentType->empty()) {
          OS_ASSERT(thisObject.setString(fieldIndex, ""));
          changed = true;
        }
      };

      syncObjectType(WaterHeater_HeatPump_PumpedCondenserFields::TankObjectType,
                     tankObject ? boost::optional<std::string>(tankObject->iddObject().name()) : boost::none);
      syncObjectType(WaterHeater_HeatPump_PumpedCondenserFields::DXCoilObjectType,
                     dxObject ? boost::optional<std::string>(dxObject->iddObject().name()) : boost::none);
      syncObjectType(WaterHeater_HeatPump_PumpedCondenserFields::FanObjectType,
                     fanObject ? boost::optional<std::string>(fanObject->iddObject().name()) : boost::none);

      if (!tankComponent || !dxCoil || !fanObject) {
        return changed;
      }

      changed = assignNodeIfPresent(thisObject, WaterHeater_HeatPump_PumpedCondenserFields::TankUseSideInletNodeName,
                                    tankComponent->getImpl<detail::ModelObject_Impl>()->resolvedNodeTarget(tankComponent->supplyInletPort()))
                || changed;
      changed = assignNodeIfPresent(thisObject, WaterHeater_HeatPump_PumpedCondenserFields::TankUseSideOutletNodeName,
                                    tankComponent->getImpl<detail::ModelObject_Impl>()->resolvedNodeTarget(tankComponent->supplyOutletPort()))
                || changed;

      const bool outdoorOnly = openstudio::istringEqual(inletAirConfiguration(), "OutdoorAirOnly");
      const bool zoneAndOutdoorAir = openstudio::istringEqual(inletAirConfiguration(), "ZoneAndOutdoorAir");
      const bool drawThrough = !openstudio::istringEqual(fanPlacement(), "BlowThrough");

      boost::optional<Node> airInlet;
      boost::optional<Node> airOutlet;
      if (!outdoorOnly) {
        const std::string inletName =
          openstudio::istringEqual(inletAirConfiguration(), "Schedule") ? baseName + " Inlet" : baseName + " Air Inlet Node";
        const std::string outletName =
          openstudio::istringEqual(inletAirConfiguration(), "Schedule") ? baseName + " Outlet" : baseName + " Air Outlet Node";
        airInlet = resolvedOrCreatedNodeTarget(WaterHeater_HeatPump_PumpedCondenserFields::AirInletNodeName, inletName);
        airOutlet = resolvedOrCreatedNodeTarget(WaterHeater_HeatPump_PumpedCondenserFields::AirOutletNodeName, outletName);
        changed =
          thisObject.getImpl<detail::ModelObject_Impl>()->setPointer(WaterHeater_HeatPump_PumpedCondenserFields::AirInletNodeName, airInlet->handle(), false)
          || changed;
        changed =
          thisObject.getImpl<detail::ModelObject_Impl>()->setPointer(WaterHeater_HeatPump_PumpedCondenserFields::AirOutletNodeName, airOutlet->handle(), false)
          || changed;
      } else {
        changed = clearStringIfNeeded(thisObject, WaterHeater_HeatPump_PumpedCondenserFields::AirInletNodeName) || changed;
        changed = clearStringIfNeeded(thisObject, WaterHeater_HeatPump_PumpedCondenserFields::AirOutletNodeName) || changed;
      }

      if (auto zone = thermalZone(); zone && !outdoorOnly && !openstudio::istringEqual(inletAirConfiguration(), "Schedule")) {
        if (auto zoneName = zone->nameString(); !zoneName.empty()) {
          if (auto currentZoneName = thisObject.getString(WaterHeater_HeatPump_PumpedCondenserFields::InletAirZoneName, true);
              !currentZoneName || !openstudio::istringEqual(*currentZoneName, zoneName)) {
            OS_ASSERT(thisObject.setString(WaterHeater_HeatPump_PumpedCondenserFields::InletAirZoneName, zoneName));
            changed = true;
          }
        }
      } else {
        changed = clearStringIfNeeded(thisObject, WaterHeater_HeatPump_PumpedCondenserFields::InletAirZoneName) || changed;
      }

      boost::optional<Node> outdoorAir;
      boost::optional<Node> reliefAir;
      boost::optional<Node> mixedAir;
      boost::optional<Node> splitterNode;
      if (outdoorOnly || zoneAndOutdoorAir) {
        outdoorAir = resolvedOrCreatedNodeTarget(WaterHeater_HeatPump_PumpedCondenserFields::OutdoorAirNodeName, baseName + " Outdoor Air");
        reliefAir = resolvedOrCreatedNodeTarget(WaterHeater_HeatPump_PumpedCondenserFields::ExhaustAirNodeName, baseName + " Exhaust Air");
        changed =
          thisObject.getImpl<detail::ModelObject_Impl>()->setPointer(WaterHeater_HeatPump_PumpedCondenserFields::OutdoorAirNodeName, outdoorAir->handle(), false)
          || changed;
        changed =
          thisObject.getImpl<detail::ModelObject_Impl>()->setPointer(WaterHeater_HeatPump_PumpedCondenserFields::ExhaustAirNodeName, reliefAir->handle(), false)
          || changed;
      } else {
        changed = clearStringIfNeeded(thisObject, WaterHeater_HeatPump_PumpedCondenserFields::OutdoorAirNodeName) || changed;
        changed = clearStringIfNeeded(thisObject, WaterHeater_HeatPump_PumpedCondenserFields::ExhaustAirNodeName) || changed;
      }

      if (zoneAndOutdoorAir) {
        mixedAir = resolvedOrCreatedNodeTarget(WaterHeater_HeatPump_PumpedCondenserFields::InletAirMixerNodeName, baseName + " Mixed Air Node");
        splitterNode =
          resolvedOrCreatedNodeTarget(WaterHeater_HeatPump_PumpedCondenserFields::OutletAirSplitterNodeName, baseName + " Fan Outlet Node");
        changed =
          thisObject.getImpl<detail::ModelObject_Impl>()->setPointer(WaterHeater_HeatPump_PumpedCondenserFields::InletAirMixerNodeName, mixedAir->handle(), false)
          || changed;
        changed =
          thisObject.getImpl<detail::ModelObject_Impl>()->setPointer(WaterHeater_HeatPump_PumpedCondenserFields::OutletAirSplitterNodeName,
                                                                     splitterNode->handle(), false)
          || changed;
      } else {
        changed = clearStringIfNeeded(thisObject, WaterHeater_HeatPump_PumpedCondenserFields::InletAirMixerNodeName) || changed;
        changed = clearStringIfNeeded(thisObject, WaterHeater_HeatPump_PumpedCondenserFields::OutletAirSplitterNodeName) || changed;
      }

      boost::optional<Node> evaporatorInlet;
      boost::optional<Node> evaporatorOutlet;
      boost::optional<Node> fanInlet;
      boost::optional<Node> fanOutlet;

      if (drawThrough) {
        evaporatorInlet = outdoorOnly ? outdoorAir : (zoneAndOutdoorAir ? mixedAir : airInlet);
        if (allowNodeRecovery) {
          evaporatorOutlet =
            dxCoil->getImpl<detail::ModelObject_Impl>()->resolvedNodeTarget(dxCoil->airOutletPort());
        }
        if (!evaporatorOutlet) {
          evaporatorOutlet = model().getOrCreateTransientByName<Node>(baseName + " Evaporator Outlet - Fan Inlet");
        }
        fanInlet = evaporatorOutlet;
        fanOutlet = outdoorOnly ? reliefAir : (zoneAndOutdoorAir ? splitterNode : airOutlet);
      } else {
        fanInlet = outdoorOnly ? outdoorAir : (zoneAndOutdoorAir ? mixedAir : airInlet);
        if (allowNodeRecovery) {
          fanOutlet = fanObject->getImpl<detail::ModelObject_Impl>()->resolvedNodeTarget(fanObject->outletPort());
        }
        if (!fanOutlet) {
          fanOutlet = model().getOrCreateTransientByName<Node>(baseName + " Fan Outlet - Evaporator Inlet");
        }
        evaporatorInlet = fanOutlet;
        evaporatorOutlet = outdoorOnly ? reliefAir : (zoneAndOutdoorAir ? splitterNode : airOutlet);
      }

      changed = fanObject->getImpl<detail::ModelObject_Impl>()->setPointer(fanObject->inletPort(), fanInlet->handle(), false) || changed;
      changed = fanObject->getImpl<detail::ModelObject_Impl>()->setPointer(fanObject->outletPort(), fanOutlet->handle(), false) || changed;
      changed = dxCoil->getImpl<detail::ModelObject_Impl>()->setPointer(dxCoil->airInletPort(), evaporatorInlet->handle(), false) || changed;
      changed = dxCoil->getImpl<detail::ModelObject_Impl>()->setPointer(dxCoil->airOutletPort(), evaporatorOutlet->handle(), false) || changed;

      auto condenserWaterInlet = resolvedOrCreatedNodeTarget(WaterHeater_HeatPump_PumpedCondenserFields::CondenserWaterInletNodeName,
                                                             baseName + " Tank Outlet - Condenser Inlet");
      auto condenserWaterOutlet = resolvedOrCreatedNodeTarget(WaterHeater_HeatPump_PumpedCondenserFields::CondenserWaterOutletNodeName,
                                                              baseName + " Condenser Outlet - Tank Inlet");
      changed = thisObject.getImpl<detail::ModelObject_Impl>()->setPointer(WaterHeater_HeatPump_PumpedCondenserFields::CondenserWaterInletNodeName,
                                                                           condenserWaterInlet.handle(), false)
                || changed;
      changed = thisObject.getImpl<detail::ModelObject_Impl>()->setPointer(WaterHeater_HeatPump_PumpedCondenserFields::CondenserWaterOutletNodeName,
                                                                           condenserWaterOutlet.handle(), false)
                || changed;

      changed =
        tankComponent->getImpl<detail::ModelObject_Impl>()->setPointer(tankComponent->demandOutletPort(), condenserWaterInlet.handle(), false)
        || changed;
      changed =
        tankComponent->getImpl<detail::ModelObject_Impl>()->setPointer(tankComponent->demandInletPort(), condenserWaterOutlet.handle(), false)
        || changed;
      changed = dxCoil->getImpl<detail::ModelObject_Impl>()->setPointer(dxCoil->waterInletPort(), condenserWaterInlet.handle(), false)
                || changed;
      changed = dxCoil->getImpl<detail::ModelObject_Impl>()->setPointer(dxCoil->waterOutletPort(), condenserWaterOutlet.handle(), false)
                || changed;

      return changed;
    }

    double WaterHeaterHeatPump_Impl::deadBandTemperatureDifference() const {
      const auto value = getDouble(openstudio::WaterHeater_HeatPump_PumpedCondenserFields::DeadBandTemperatureDifference, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WaterHeaterHeatPump_Impl::isDeadBandTemperatureDifferenceDefaulted() const {
      return isEmpty(openstudio::WaterHeater_HeatPump_PumpedCondenserFields::DeadBandTemperatureDifference);
    }

    bool WaterHeaterHeatPump_Impl::setDeadBandTemperatureDifference(double deadBandTemperatureDifference) {
      const bool result =
        setDouble(openstudio::WaterHeater_HeatPump_PumpedCondenserFields::DeadBandTemperatureDifference, deadBandTemperatureDifference);
      OS_ASSERT(result);
      return result;
    }

    void WaterHeaterHeatPump_Impl::resetDeadBandTemperatureDifference() {
      OS_ASSERT(setString(openstudio::WaterHeater_HeatPump_PumpedCondenserFields::DeadBandTemperatureDifference, ""));
    }

    boost::optional<double> WaterHeaterHeatPump_Impl::condenserWaterFlowRate() const {
      return getDouble(openstudio::WaterHeater_HeatPump_PumpedCondenserFields::CondenserWaterFlowRate, true);
    }

    bool WaterHeaterHeatPump_Impl::isCondenserWaterFlowRateAutosized() const {
      if (auto value = getString(openstudio::WaterHeater_HeatPump_PumpedCondenserFields::CondenserWaterFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool WaterHeaterHeatPump_Impl::setCondenserWaterFlowRate(double condenserWaterFlowRate) {
      const bool result = setDouble(openstudio::WaterHeater_HeatPump_PumpedCondenserFields::CondenserWaterFlowRate, condenserWaterFlowRate);
      OS_ASSERT(result);
      return result;
    }

    void WaterHeaterHeatPump_Impl::resetCondenserWaterFlowRate() {
      OS_ASSERT(setString(openstudio::WaterHeater_HeatPump_PumpedCondenserFields::CondenserWaterFlowRate, ""));
    }

    void WaterHeaterHeatPump_Impl::autosizeCondenserWaterFlowRate() {
      OS_ASSERT(setString(openstudio::WaterHeater_HeatPump_PumpedCondenserFields::CondenserWaterFlowRate, "autosize"));
    }

    boost::optional<double> WaterHeaterHeatPump_Impl::evaporatorAirFlowRate() const {
      return getDouble(openstudio::WaterHeater_HeatPump_PumpedCondenserFields::EvaporatorAirFlowRate, true);
    }

    bool WaterHeaterHeatPump_Impl::isEvaporatorAirFlowRateAutosized() const {
      if (auto value = getString(openstudio::WaterHeater_HeatPump_PumpedCondenserFields::EvaporatorAirFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool WaterHeaterHeatPump_Impl::setEvaporatorAirFlowRate(double evaporatorAirFlowRate) {
      const bool result = setDouble(openstudio::WaterHeater_HeatPump_PumpedCondenserFields::EvaporatorAirFlowRate, evaporatorAirFlowRate);
      OS_ASSERT(result);
      return result;
    }

    void WaterHeaterHeatPump_Impl::resetEvaporatorAirFlowRate() {
      OS_ASSERT(setString(openstudio::WaterHeater_HeatPump_PumpedCondenserFields::EvaporatorAirFlowRate, ""));
    }

    void WaterHeaterHeatPump_Impl::autosizeEvaporatorAirFlowRate() {
      OS_ASSERT(setString(openstudio::WaterHeater_HeatPump_PumpedCondenserFields::EvaporatorAirFlowRate, "autosize"));
    }

    std::string WaterHeaterHeatPump_Impl::inletAirConfiguration() const {
      const auto value = getString(openstudio::WaterHeater_HeatPump_PumpedCondenserFields::InletAirConfiguration, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WaterHeaterHeatPump_Impl::setInletAirConfiguration(const std::string& inletAirConfiguration) {
      const bool result = setString(openstudio::WaterHeater_HeatPump_PumpedCondenserFields::InletAirConfiguration, inletAirConfiguration);
      if (result) {
        maintainContainedTopology();
      }
      OS_ASSERT(result);
      return result;
    }

    double WaterHeaterHeatPump_Impl::minimumInletAirTemperatureforCompressorOperation() const {
      const auto value = getDouble(openstudio::WaterHeater_HeatPump_PumpedCondenserFields::MinimumInletAirTemperatureforCompressorOperation, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WaterHeaterHeatPump_Impl::isMinimumInletAirTemperatureforCompressorOperationDefaulted() const {
      return isEmpty(openstudio::WaterHeater_HeatPump_PumpedCondenserFields::MinimumInletAirTemperatureforCompressorOperation);
    }

    bool WaterHeaterHeatPump_Impl::setMinimumInletAirTemperatureforCompressorOperation(double minimumInletAirTemperatureforCompressorOperation) {
      const bool result = setDouble(openstudio::WaterHeater_HeatPump_PumpedCondenserFields::MinimumInletAirTemperatureforCompressorOperation,
                                    minimumInletAirTemperatureforCompressorOperation);
      OS_ASSERT(result);
      return result;
    }

    void WaterHeaterHeatPump_Impl::resetMinimumInletAirTemperatureforCompressorOperation() {
      OS_ASSERT(setString(openstudio::WaterHeater_HeatPump_PumpedCondenserFields::MinimumInletAirTemperatureforCompressorOperation, ""));
    }

    double WaterHeaterHeatPump_Impl::maximumInletAirTemperatureforCompressorOperation() const {
      const auto value = getDouble(openstudio::WaterHeater_HeatPump_PumpedCondenserFields::MaximumInletAirTemperatureforCompressorOperation, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WaterHeaterHeatPump_Impl::isMaximumInletAirTemperatureforCompressorOperationDefaulted() const {
      return isEmpty(openstudio::WaterHeater_HeatPump_PumpedCondenserFields::MaximumInletAirTemperatureforCompressorOperation);
    }

    bool WaterHeaterHeatPump_Impl::setMaximumInletAirTemperatureforCompressorOperation(double maximumInletAirTemperatureforCompressorOperation) {
      const bool result = setDouble(openstudio::WaterHeater_HeatPump_PumpedCondenserFields::MaximumInletAirTemperatureforCompressorOperation,
                                    maximumInletAirTemperatureforCompressorOperation);
      OS_ASSERT(result);
      return result;
    }

    void WaterHeaterHeatPump_Impl::resetMaximumInletAirTemperatureforCompressorOperation() {
      OS_ASSERT(setString(openstudio::WaterHeater_HeatPump_PumpedCondenserFields::MaximumInletAirTemperatureforCompressorOperation, ""));
    }

    std::string WaterHeaterHeatPump_Impl::compressorLocation() const {
      const auto value = getString(openstudio::WaterHeater_HeatPump_PumpedCondenserFields::CompressorLocation, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WaterHeaterHeatPump_Impl::setCompressorLocation(const std::string& compressorLocation) {
      const bool result = setString(openstudio::WaterHeater_HeatPump_PumpedCondenserFields::CompressorLocation, compressorLocation);
      OS_ASSERT(result);
      return result;
    }

    std::string WaterHeaterHeatPump_Impl::fanPlacement() const {
      const auto value = getString(openstudio::WaterHeater_HeatPump_PumpedCondenserFields::FanPlacement, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WaterHeaterHeatPump_Impl::isFanPlacementDefaulted() const {
      return isEmpty(openstudio::WaterHeater_HeatPump_PumpedCondenserFields::FanPlacement);
    }

    bool WaterHeaterHeatPump_Impl::setFanPlacement(const std::string& fanPlacement) {
      const bool result = setString(openstudio::WaterHeater_HeatPump_PumpedCondenserFields::FanPlacement, fanPlacement);
      if (result) {
        maintainContainedTopology();
      }
      OS_ASSERT(result);
      return result;
    }

    void WaterHeaterHeatPump_Impl::resetFanPlacement() {
      OS_ASSERT(setString(openstudio::WaterHeater_HeatPump_PumpedCondenserFields::FanPlacement, ""));
      maintainContainedTopology();
    }

    double WaterHeaterHeatPump_Impl::onCycleParasiticElectricLoad() const {
      const auto value = getDouble(openstudio::WaterHeater_HeatPump_PumpedCondenserFields::OnCycleParasiticElectricLoad, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WaterHeaterHeatPump_Impl::isOnCycleParasiticElectricLoadDefaulted() const {
      return isEmpty(openstudio::WaterHeater_HeatPump_PumpedCondenserFields::OnCycleParasiticElectricLoad);
    }

    bool WaterHeaterHeatPump_Impl::setOnCycleParasiticElectricLoad(double onCycleParasiticElectricLoad) {
      const bool result =
        setDouble(openstudio::WaterHeater_HeatPump_PumpedCondenserFields::OnCycleParasiticElectricLoad, onCycleParasiticElectricLoad);
      OS_ASSERT(result);
      return result;
    }

    void WaterHeaterHeatPump_Impl::resetOnCycleParasiticElectricLoad() {
      OS_ASSERT(setString(openstudio::WaterHeater_HeatPump_PumpedCondenserFields::OnCycleParasiticElectricLoad, ""));
    }

    double WaterHeaterHeatPump_Impl::offCycleParasiticElectricLoad() const {
      const auto value = getDouble(openstudio::WaterHeater_HeatPump_PumpedCondenserFields::OffCycleParasiticElectricLoad, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WaterHeaterHeatPump_Impl::isOffCycleParasiticElectricLoadDefaulted() const {
      return isEmpty(openstudio::WaterHeater_HeatPump_PumpedCondenserFields::OffCycleParasiticElectricLoad);
    }

    bool WaterHeaterHeatPump_Impl::setOffCycleParasiticElectricLoad(double offCycleParasiticElectricLoad) {
      const bool result =
        setDouble(openstudio::WaterHeater_HeatPump_PumpedCondenserFields::OffCycleParasiticElectricLoad, offCycleParasiticElectricLoad);
      OS_ASSERT(result);
      return result;
    }

    void WaterHeaterHeatPump_Impl::resetOffCycleParasiticElectricLoad() {
      OS_ASSERT(setString(openstudio::WaterHeater_HeatPump_PumpedCondenserFields::OffCycleParasiticElectricLoad, ""));
    }

    std::string WaterHeaterHeatPump_Impl::parasiticHeatRejectionLocation() const {
      const auto value = getString(openstudio::WaterHeater_HeatPump_PumpedCondenserFields::ParasiticHeatRejectionLocation, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WaterHeaterHeatPump_Impl::isParasiticHeatRejectionLocationDefaulted() const {
      return isEmpty(openstudio::WaterHeater_HeatPump_PumpedCondenserFields::ParasiticHeatRejectionLocation);
    }

    bool WaterHeaterHeatPump_Impl::setParasiticHeatRejectionLocation(const std::string& parasiticHeatRejectionLocation) {
      const bool result =
        setString(openstudio::WaterHeater_HeatPump_PumpedCondenserFields::ParasiticHeatRejectionLocation, parasiticHeatRejectionLocation);
      OS_ASSERT(result);
      return result;
    }

    void WaterHeaterHeatPump_Impl::resetParasiticHeatRejectionLocation() {
      OS_ASSERT(setString(openstudio::WaterHeater_HeatPump_PumpedCondenserFields::ParasiticHeatRejectionLocation, ""));
    }

    std::string WaterHeaterHeatPump_Impl::tankElementControlLogic() const {
      const auto value = getString(openstudio::WaterHeater_HeatPump_PumpedCondenserFields::TankElementControlLogic, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WaterHeaterHeatPump_Impl::isTankElementControlLogicDefaulted() const {
      return isEmpty(openstudio::WaterHeater_HeatPump_PumpedCondenserFields::TankElementControlLogic);
    }

    bool WaterHeaterHeatPump_Impl::setTankElementControlLogic(const std::string& tankElementControlLogic) {
      const bool result = setString(openstudio::WaterHeater_HeatPump_PumpedCondenserFields::TankElementControlLogic, tankElementControlLogic);
      OS_ASSERT(result);
      return result;
    }

    void WaterHeaterHeatPump_Impl::resetTankElementControlLogic() {
      OS_ASSERT(setString(openstudio::WaterHeater_HeatPump_PumpedCondenserFields::TankElementControlLogic, ""));
    }

    boost::optional<double> WaterHeaterHeatPump_Impl::controlSensor1HeightInStratifiedTank() const {
      return getDouble(openstudio::WaterHeater_HeatPump_PumpedCondenserFields::ControlSensor1HeightInStratifiedTank, true);
    }

    bool WaterHeaterHeatPump_Impl::setControlSensor1HeightInStratifiedTank(double controlSensor1HeightInStratifiedTank) {
      const bool result =
        setDouble(openstudio::WaterHeater_HeatPump_PumpedCondenserFields::ControlSensor1HeightInStratifiedTank, controlSensor1HeightInStratifiedTank);
      OS_ASSERT(result);
      return result;
    }

    void WaterHeaterHeatPump_Impl::resetControlSensor1HeightInStratifiedTank() {
      OS_ASSERT(setString(openstudio::WaterHeater_HeatPump_PumpedCondenserFields::ControlSensor1HeightInStratifiedTank, ""));
    }

    double WaterHeaterHeatPump_Impl::controlSensor1Weight() const {
      const auto value = getDouble(openstudio::WaterHeater_HeatPump_PumpedCondenserFields::ControlSensor1Weight, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WaterHeaterHeatPump_Impl::isControlSensor1WeightDefaulted() const {
      return isEmpty(openstudio::WaterHeater_HeatPump_PumpedCondenserFields::ControlSensor1Weight);
    }

    bool WaterHeaterHeatPump_Impl::setControlSensor1Weight(double controlSensor1Weight) {
      const bool result = setDouble(openstudio::WaterHeater_HeatPump_PumpedCondenserFields::ControlSensor1Weight, controlSensor1Weight);
      OS_ASSERT(result);
      return result;
    }

    void WaterHeaterHeatPump_Impl::resetControlSensor1Weight() {
      OS_ASSERT(setString(openstudio::WaterHeater_HeatPump_PumpedCondenserFields::ControlSensor1Weight, ""));
    }

    boost::optional<double> WaterHeaterHeatPump_Impl::controlSensor2HeightInStratifiedTank() const {
      return getDouble(openstudio::WaterHeater_HeatPump_PumpedCondenserFields::ControlSensor2HeightInStratifiedTank, true);
    }

    bool WaterHeaterHeatPump_Impl::setControlSensor2HeightInStratifiedTank(double controlSensor2HeightInStratifiedTank) {
      const bool result =
        setDouble(openstudio::WaterHeater_HeatPump_PumpedCondenserFields::ControlSensor2HeightInStratifiedTank, controlSensor2HeightInStratifiedTank);
      OS_ASSERT(result);
      return result;
    }

    void WaterHeaterHeatPump_Impl::resetControlSensor2HeightInStratifiedTank() {
      OS_ASSERT(setString(openstudio::WaterHeater_HeatPump_PumpedCondenserFields::ControlSensor2HeightInStratifiedTank, ""));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
