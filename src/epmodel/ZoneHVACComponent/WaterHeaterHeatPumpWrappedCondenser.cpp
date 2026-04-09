/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ZoneHVACComponent/WaterHeaterHeatPumpWrappedCondenser.hpp"
#include "ZoneHVACComponent/WaterHeaterHeatPumpWrappedCondenser_Impl.hpp"

#include "Model.hpp"
#include "ModelObject/ModelObject.hpp"
#include "ModelObject/ModelObject_Impl.hpp"
#include "HVACComponent/ThermalZone.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"
#include "Schedule/ScheduleConstant.hpp"
#include "StraightComponent/CoilWaterHeatingAirToWaterHeatPumpWrapped.hpp"
#include "StraightComponent/CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl.hpp"
#include "StraightComponent/FanOnOff.hpp"
#include "StraightComponent/Node.hpp"
#include "StraightComponent/StraightComponent.hpp"
#include "WaterToWaterComponent/WaterHeaterStratified.hpp"
#include "WaterToWaterComponent/WaterHeaterStratified_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/WaterHeater_HeatPump_WrappedCondenser_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  namespace {

    // The wrapped-condenser variant owns a simpler child set than the pumped
    // condenser type: one stratified tank, one wrapped DX coil, and one
    // one-in/one-out air-side fan. Keeping those checks local makes the
    // supported child set explicit without growing another shared registry.

    bool isSupportedWrappedCondenserTank(const HVACComponent& component) {
      return static_cast<bool>(component.optionalCast<WaterHeaterStratified>());
    }

    bool isSupportedWrappedCondenserDXCoil(const ModelObject& object) {
      return static_cast<bool>(object.optionalCast<CoilWaterHeatingAirToWaterHeatPumpWrapped>());
    }

    bool clearStringIfNeeded(ModelObject& object, unsigned fieldIndex) {
      if (auto value = object.getString(fieldIndex, true); value && !value->empty()) {
        return object.setString(fieldIndex, "");
      }
      return false;
    }

  }  // namespace

  WaterHeaterHeatPumpWrappedCondenser::WaterHeaterHeatPumpWrappedCondenser(const Model& model)
    : ZoneHVACComponent(WaterHeaterHeatPumpWrappedCondenser::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::WaterHeaterHeatPumpWrappedCondenser_Impl>());

    CoilWaterHeatingAirToWaterHeatPumpWrapped dxCoil(model);
    OS_ASSERT(setDXCoil(dxCoil));

    WaterHeaterStratified tank(model);
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
    OS_ASSERT(setCondenserBottomLocation(0.0));
    OS_ASSERT(setCondenserTopLocation(0.867));
    autocalculateEvaporatorAirFlowRate();
    OS_ASSERT(setInletAirConfiguration("Schedule"));
    OS_ASSERT(setMinimumInletAirTemperatureforCompressorOperation(10.0));
    OS_ASSERT(setMaximumInletAirTemperatureforCompressorOperation(48.89));
    OS_ASSERT(setCompressorLocation("Schedule"));
    OS_ASSERT(setFanPlacement("DrawThrough"));
    OS_ASSERT(setOnCycleParasiticElectricLoad(0.0));
    OS_ASSERT(setOffCycleParasiticElectricLoad(0.0));
    OS_ASSERT(setParasiticHeatRejectionLocation("Outdoors"));
    OS_ASSERT(setTankElementControlLogic("MutuallyExclusive"));
    OS_ASSERT(setControlSensor1Weight(1.0));
  }

  WaterHeaterHeatPumpWrappedCondenser::WaterHeaterHeatPumpWrappedCondenser(std::shared_ptr<detail::WaterHeaterHeatPumpWrappedCondenser_Impl> impl)
    : ZoneHVACComponent(std::move(impl)) {}

  IddObjectType WaterHeaterHeatPumpWrappedCondenser::iddObjectType() {
    return IddObjectType::WaterHeater_HeatPump_WrappedCondenser;
  }

  std::vector<std::string> WaterHeaterHeatPumpWrappedCondenser::inletAirConfigurationValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          WaterHeater_HeatPump_WrappedCondenserFields::InletAirConfiguration);
  }

  std::vector<std::string> WaterHeaterHeatPumpWrappedCondenser::compressorLocationValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          WaterHeater_HeatPump_WrappedCondenserFields::CompressorLocation);
  }

  std::vector<std::string> WaterHeaterHeatPumpWrappedCondenser::fanPlacementValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), WaterHeater_HeatPump_WrappedCondenserFields::FanPlacement);
  }

  std::vector<std::string> WaterHeaterHeatPumpWrappedCondenser::parasiticHeatRejectionLocationValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          WaterHeater_HeatPump_WrappedCondenserFields::ParasiticHeatRejectionLocation);
  }

  std::vector<std::string> WaterHeaterHeatPumpWrappedCondenser::tankElementControlLogicValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          WaterHeater_HeatPump_WrappedCondenserFields::TankElementControlLogic);
  }

  boost::optional<Schedule> WaterHeaterHeatPumpWrappedCondenser::availabilitySchedule() const {
    return getImpl<detail::WaterHeaterHeatPumpWrappedCondenser_Impl>()->availabilitySchedule();
  }

  bool WaterHeaterHeatPumpWrappedCondenser::setAvailabilitySchedule(Schedule& schedule) {
    return getImpl<detail::WaterHeaterHeatPumpWrappedCondenser_Impl>()->setAvailabilitySchedule(schedule);
  }

  void WaterHeaterHeatPumpWrappedCondenser::resetAvailabilitySchedule() {
    getImpl<detail::WaterHeaterHeatPumpWrappedCondenser_Impl>()->resetAvailabilitySchedule();
  }

  Schedule WaterHeaterHeatPumpWrappedCondenser::compressorSetpointTemperatureSchedule() const {
    return getImpl<detail::WaterHeaterHeatPumpWrappedCondenser_Impl>()->compressorSetpointTemperatureSchedule();
  }

  bool WaterHeaterHeatPumpWrappedCondenser::setCompressorSetpointTemperatureSchedule(Schedule& schedule) {
    return getImpl<detail::WaterHeaterHeatPumpWrappedCondenser_Impl>()->setCompressorSetpointTemperatureSchedule(schedule);
  }

  double WaterHeaterHeatPumpWrappedCondenser::deadBandTemperatureDifference() const {
    return getImpl<detail::WaterHeaterHeatPumpWrappedCondenser_Impl>()->deadBandTemperatureDifference();
  }

  bool WaterHeaterHeatPumpWrappedCondenser::isDeadBandTemperatureDifferenceDefaulted() const {
    return getImpl<detail::WaterHeaterHeatPumpWrappedCondenser_Impl>()->isDeadBandTemperatureDifferenceDefaulted();
  }

  bool WaterHeaterHeatPumpWrappedCondenser::setDeadBandTemperatureDifference(double deadBandTemperatureDifference) {
    return getImpl<detail::WaterHeaterHeatPumpWrappedCondenser_Impl>()->setDeadBandTemperatureDifference(deadBandTemperatureDifference);
  }

  void WaterHeaterHeatPumpWrappedCondenser::resetDeadBandTemperatureDifference() {
    getImpl<detail::WaterHeaterHeatPumpWrappedCondenser_Impl>()->resetDeadBandTemperatureDifference();
  }

  double WaterHeaterHeatPumpWrappedCondenser::condenserBottomLocation() const {
    return getImpl<detail::WaterHeaterHeatPumpWrappedCondenser_Impl>()->condenserBottomLocation();
  }

  bool WaterHeaterHeatPumpWrappedCondenser::isCondenserBottomLocationDefaulted() const {
    return getImpl<detail::WaterHeaterHeatPumpWrappedCondenser_Impl>()->isCondenserBottomLocationDefaulted();
  }

  bool WaterHeaterHeatPumpWrappedCondenser::setCondenserBottomLocation(double condenserBottomLocation) {
    return getImpl<detail::WaterHeaterHeatPumpWrappedCondenser_Impl>()->setCondenserBottomLocation(condenserBottomLocation);
  }

  void WaterHeaterHeatPumpWrappedCondenser::resetCondenserBottomLocation() {
    getImpl<detail::WaterHeaterHeatPumpWrappedCondenser_Impl>()->resetCondenserBottomLocation();
  }

  double WaterHeaterHeatPumpWrappedCondenser::condenserTopLocation() const {
    return getImpl<detail::WaterHeaterHeatPumpWrappedCondenser_Impl>()->condenserTopLocation();
  }

  bool WaterHeaterHeatPumpWrappedCondenser::setCondenserTopLocation(double condenserTopLocation) {
    return getImpl<detail::WaterHeaterHeatPumpWrappedCondenser_Impl>()->setCondenserTopLocation(condenserTopLocation);
  }

  boost::optional<double> WaterHeaterHeatPumpWrappedCondenser::evaporatorAirFlowRate() const {
    return getImpl<detail::WaterHeaterHeatPumpWrappedCondenser_Impl>()->evaporatorAirFlowRate();
  }

  bool WaterHeaterHeatPumpWrappedCondenser::isEvaporatorAirFlowRateAutocalculated() const {
    return getImpl<detail::WaterHeaterHeatPumpWrappedCondenser_Impl>()->isEvaporatorAirFlowRateAutocalculated();
  }

  bool WaterHeaterHeatPumpWrappedCondenser::setEvaporatorAirFlowRate(double evaporatorAirFlowRate) {
    return getImpl<detail::WaterHeaterHeatPumpWrappedCondenser_Impl>()->setEvaporatorAirFlowRate(evaporatorAirFlowRate);
  }

  void WaterHeaterHeatPumpWrappedCondenser::resetEvaporatorAirFlowRate() {
    getImpl<detail::WaterHeaterHeatPumpWrappedCondenser_Impl>()->resetEvaporatorAirFlowRate();
  }

  void WaterHeaterHeatPumpWrappedCondenser::autocalculateEvaporatorAirFlowRate() {
    getImpl<detail::WaterHeaterHeatPumpWrappedCondenser_Impl>()->autocalculateEvaporatorAirFlowRate();
  }

  std::string WaterHeaterHeatPumpWrappedCondenser::inletAirConfiguration() const {
    return getImpl<detail::WaterHeaterHeatPumpWrappedCondenser_Impl>()->inletAirConfiguration();
  }

  bool WaterHeaterHeatPumpWrappedCondenser::setInletAirConfiguration(const std::string& inletAirConfiguration) {
    return getImpl<detail::WaterHeaterHeatPumpWrappedCondenser_Impl>()->setInletAirConfiguration(inletAirConfiguration);
  }

  boost::optional<Schedule> WaterHeaterHeatPumpWrappedCondenser::inletAirTemperatureSchedule() const {
    return getImpl<detail::WaterHeaterHeatPumpWrappedCondenser_Impl>()->inletAirTemperatureSchedule();
  }

  bool WaterHeaterHeatPumpWrappedCondenser::setInletAirTemperatureSchedule(Schedule& schedule) {
    return getImpl<detail::WaterHeaterHeatPumpWrappedCondenser_Impl>()->setInletAirTemperatureSchedule(schedule);
  }

  void WaterHeaterHeatPumpWrappedCondenser::resetInletAirTemperatureSchedule() {
    getImpl<detail::WaterHeaterHeatPumpWrappedCondenser_Impl>()->resetInletAirTemperatureSchedule();
  }

  boost::optional<Schedule> WaterHeaterHeatPumpWrappedCondenser::inletAirHumiditySchedule() const {
    return getImpl<detail::WaterHeaterHeatPumpWrappedCondenser_Impl>()->inletAirHumiditySchedule();
  }

  bool WaterHeaterHeatPumpWrappedCondenser::setInletAirHumiditySchedule(Schedule& schedule) {
    return getImpl<detail::WaterHeaterHeatPumpWrappedCondenser_Impl>()->setInletAirHumiditySchedule(schedule);
  }

  void WaterHeaterHeatPumpWrappedCondenser::resetInletAirHumiditySchedule() {
    getImpl<detail::WaterHeaterHeatPumpWrappedCondenser_Impl>()->resetInletAirHumiditySchedule();
  }

  HVACComponent WaterHeaterHeatPumpWrappedCondenser::tank() const {
    return getImpl<detail::WaterHeaterHeatPumpWrappedCondenser_Impl>()->tank();
  }

  bool WaterHeaterHeatPumpWrappedCondenser::setTank(const HVACComponent& waterHeaterStratified) {
    return getImpl<detail::WaterHeaterHeatPumpWrappedCondenser_Impl>()->setTank(waterHeaterStratified);
  }

  ModelObject WaterHeaterHeatPumpWrappedCondenser::dXCoil() const {
    return getImpl<detail::WaterHeaterHeatPumpWrappedCondenser_Impl>()->dXCoil();
  }

  bool WaterHeaterHeatPumpWrappedCondenser::setDXCoil(const ModelObject& heatPumpWaterHeaterDXCoilWrapped) {
    return getImpl<detail::WaterHeaterHeatPumpWrappedCondenser_Impl>()->setDXCoil(heatPumpWaterHeaterDXCoilWrapped);
  }

  double WaterHeaterHeatPumpWrappedCondenser::minimumInletAirTemperatureforCompressorOperation() const {
    return getImpl<detail::WaterHeaterHeatPumpWrappedCondenser_Impl>()->minimumInletAirTemperatureforCompressorOperation();
  }

  bool WaterHeaterHeatPumpWrappedCondenser::isMinimumInletAirTemperatureforCompressorOperationDefaulted() const {
    return getImpl<detail::WaterHeaterHeatPumpWrappedCondenser_Impl>()->isMinimumInletAirTemperatureforCompressorOperationDefaulted();
  }

  bool WaterHeaterHeatPumpWrappedCondenser::setMinimumInletAirTemperatureforCompressorOperation(
    double minimumInletAirTemperatureforCompressorOperation) {
    return getImpl<detail::WaterHeaterHeatPumpWrappedCondenser_Impl>()->setMinimumInletAirTemperatureforCompressorOperation(
      minimumInletAirTemperatureforCompressorOperation);
  }

  void WaterHeaterHeatPumpWrappedCondenser::resetMinimumInletAirTemperatureforCompressorOperation() {
    getImpl<detail::WaterHeaterHeatPumpWrappedCondenser_Impl>()->resetMinimumInletAirTemperatureforCompressorOperation();
  }

  double WaterHeaterHeatPumpWrappedCondenser::maximumInletAirTemperatureforCompressorOperation() const {
    return getImpl<detail::WaterHeaterHeatPumpWrappedCondenser_Impl>()->maximumInletAirTemperatureforCompressorOperation();
  }

  bool WaterHeaterHeatPumpWrappedCondenser::isMaximumInletAirTemperatureforCompressorOperationDefaulted() const {
    return getImpl<detail::WaterHeaterHeatPumpWrappedCondenser_Impl>()->isMaximumInletAirTemperatureforCompressorOperationDefaulted();
  }

  bool WaterHeaterHeatPumpWrappedCondenser::setMaximumInletAirTemperatureforCompressorOperation(
    double maximumInletAirTemperatureforCompressorOperation) {
    return getImpl<detail::WaterHeaterHeatPumpWrappedCondenser_Impl>()->setMaximumInletAirTemperatureforCompressorOperation(
      maximumInletAirTemperatureforCompressorOperation);
  }

  void WaterHeaterHeatPumpWrappedCondenser::resetMaximumInletAirTemperatureforCompressorOperation() {
    getImpl<detail::WaterHeaterHeatPumpWrappedCondenser_Impl>()->resetMaximumInletAirTemperatureforCompressorOperation();
  }

  std::string WaterHeaterHeatPumpWrappedCondenser::compressorLocation() const {
    return getImpl<detail::WaterHeaterHeatPumpWrappedCondenser_Impl>()->compressorLocation();
  }

  bool WaterHeaterHeatPumpWrappedCondenser::setCompressorLocation(const std::string& compressorLocation) {
    return getImpl<detail::WaterHeaterHeatPumpWrappedCondenser_Impl>()->setCompressorLocation(compressorLocation);
  }

  boost::optional<Schedule> WaterHeaterHeatPumpWrappedCondenser::compressorAmbientTemperatureSchedule() const {
    return getImpl<detail::WaterHeaterHeatPumpWrappedCondenser_Impl>()->compressorAmbientTemperatureSchedule();
  }

  bool WaterHeaterHeatPumpWrappedCondenser::setCompressorAmbientTemperatureSchedule(Schedule& schedule) {
    return getImpl<detail::WaterHeaterHeatPumpWrappedCondenser_Impl>()->setCompressorAmbientTemperatureSchedule(schedule);
  }

  void WaterHeaterHeatPumpWrappedCondenser::resetCompressorAmbientTemperatureSchedule() {
    getImpl<detail::WaterHeaterHeatPumpWrappedCondenser_Impl>()->resetCompressorAmbientTemperatureSchedule();
  }

  HVACComponent WaterHeaterHeatPumpWrappedCondenser::fan() const {
    return getImpl<detail::WaterHeaterHeatPumpWrappedCondenser_Impl>()->fan();
  }

  bool WaterHeaterHeatPumpWrappedCondenser::setFan(const HVACComponent& fan) {
    return getImpl<detail::WaterHeaterHeatPumpWrappedCondenser_Impl>()->setFan(fan);
  }

  std::string WaterHeaterHeatPumpWrappedCondenser::fanPlacement() const {
    return getImpl<detail::WaterHeaterHeatPumpWrappedCondenser_Impl>()->fanPlacement();
  }

  bool WaterHeaterHeatPumpWrappedCondenser::isFanPlacementDefaulted() const {
    return getImpl<detail::WaterHeaterHeatPumpWrappedCondenser_Impl>()->isFanPlacementDefaulted();
  }

  bool WaterHeaterHeatPumpWrappedCondenser::setFanPlacement(const std::string& fanPlacement) {
    return getImpl<detail::WaterHeaterHeatPumpWrappedCondenser_Impl>()->setFanPlacement(fanPlacement);
  }

  void WaterHeaterHeatPumpWrappedCondenser::resetFanPlacement() {
    getImpl<detail::WaterHeaterHeatPumpWrappedCondenser_Impl>()->resetFanPlacement();
  }

  double WaterHeaterHeatPumpWrappedCondenser::onCycleParasiticElectricLoad() const {
    return getImpl<detail::WaterHeaterHeatPumpWrappedCondenser_Impl>()->onCycleParasiticElectricLoad();
  }

  bool WaterHeaterHeatPumpWrappedCondenser::isOnCycleParasiticElectricLoadDefaulted() const {
    return getImpl<detail::WaterHeaterHeatPumpWrappedCondenser_Impl>()->isOnCycleParasiticElectricLoadDefaulted();
  }

  bool WaterHeaterHeatPumpWrappedCondenser::setOnCycleParasiticElectricLoad(double onCycleParasiticElectricLoad) {
    return getImpl<detail::WaterHeaterHeatPumpWrappedCondenser_Impl>()->setOnCycleParasiticElectricLoad(onCycleParasiticElectricLoad);
  }

  void WaterHeaterHeatPumpWrappedCondenser::resetOnCycleParasiticElectricLoad() {
    getImpl<detail::WaterHeaterHeatPumpWrappedCondenser_Impl>()->resetOnCycleParasiticElectricLoad();
  }

  double WaterHeaterHeatPumpWrappedCondenser::offCycleParasiticElectricLoad() const {
    return getImpl<detail::WaterHeaterHeatPumpWrappedCondenser_Impl>()->offCycleParasiticElectricLoad();
  }

  bool WaterHeaterHeatPumpWrappedCondenser::isOffCycleParasiticElectricLoadDefaulted() const {
    return getImpl<detail::WaterHeaterHeatPumpWrappedCondenser_Impl>()->isOffCycleParasiticElectricLoadDefaulted();
  }

  bool WaterHeaterHeatPumpWrappedCondenser::setOffCycleParasiticElectricLoad(double offCycleParasiticElectricLoad) {
    return getImpl<detail::WaterHeaterHeatPumpWrappedCondenser_Impl>()->setOffCycleParasiticElectricLoad(offCycleParasiticElectricLoad);
  }

  void WaterHeaterHeatPumpWrappedCondenser::resetOffCycleParasiticElectricLoad() {
    getImpl<detail::WaterHeaterHeatPumpWrappedCondenser_Impl>()->resetOffCycleParasiticElectricLoad();
  }

  std::string WaterHeaterHeatPumpWrappedCondenser::parasiticHeatRejectionLocation() const {
    return getImpl<detail::WaterHeaterHeatPumpWrappedCondenser_Impl>()->parasiticHeatRejectionLocation();
  }

  bool WaterHeaterHeatPumpWrappedCondenser::isParasiticHeatRejectionLocationDefaulted() const {
    return getImpl<detail::WaterHeaterHeatPumpWrappedCondenser_Impl>()->isParasiticHeatRejectionLocationDefaulted();
  }

  bool WaterHeaterHeatPumpWrappedCondenser::setParasiticHeatRejectionLocation(const std::string& parasiticHeatRejectionLocation) {
    return getImpl<detail::WaterHeaterHeatPumpWrappedCondenser_Impl>()->setParasiticHeatRejectionLocation(parasiticHeatRejectionLocation);
  }

  void WaterHeaterHeatPumpWrappedCondenser::resetParasiticHeatRejectionLocation() {
    getImpl<detail::WaterHeaterHeatPumpWrappedCondenser_Impl>()->resetParasiticHeatRejectionLocation();
  }

  boost::optional<Schedule> WaterHeaterHeatPumpWrappedCondenser::inletAirMixerSchedule() const {
    return getImpl<detail::WaterHeaterHeatPumpWrappedCondenser_Impl>()->inletAirMixerSchedule();
  }

  bool WaterHeaterHeatPumpWrappedCondenser::setInletAirMixerSchedule(Schedule& schedule) {
    return getImpl<detail::WaterHeaterHeatPumpWrappedCondenser_Impl>()->setInletAirMixerSchedule(schedule);
  }

  void WaterHeaterHeatPumpWrappedCondenser::resetInletAirMixerSchedule() {
    getImpl<detail::WaterHeaterHeatPumpWrappedCondenser_Impl>()->resetInletAirMixerSchedule();
  }

  std::string WaterHeaterHeatPumpWrappedCondenser::tankElementControlLogic() const {
    return getImpl<detail::WaterHeaterHeatPumpWrappedCondenser_Impl>()->tankElementControlLogic();
  }

  bool WaterHeaterHeatPumpWrappedCondenser::isTankElementControlLogicDefaulted() const {
    return getImpl<detail::WaterHeaterHeatPumpWrappedCondenser_Impl>()->isTankElementControlLogicDefaulted();
  }

  bool WaterHeaterHeatPumpWrappedCondenser::setTankElementControlLogic(const std::string& tankElementControlLogic) {
    return getImpl<detail::WaterHeaterHeatPumpWrappedCondenser_Impl>()->setTankElementControlLogic(tankElementControlLogic);
  }

  void WaterHeaterHeatPumpWrappedCondenser::resetTankElementControlLogic() {
    getImpl<detail::WaterHeaterHeatPumpWrappedCondenser_Impl>()->resetTankElementControlLogic();
  }

  std::string WaterHeaterHeatPumpWrappedCondenser::airInletNodeName() const {
    return getImpl<detail::WaterHeaterHeatPumpWrappedCondenser_Impl>()->airInletNodeName();
  }

  std::string WaterHeaterHeatPumpWrappedCondenser::airOutletNodeName() const {
    return getImpl<detail::WaterHeaterHeatPumpWrappedCondenser_Impl>()->airOutletNodeName();
  }

  boost::optional<Node> WaterHeaterHeatPumpWrappedCondenser::fanOutletNode() const {
    return getImpl<detail::WaterHeaterHeatPumpWrappedCondenser_Impl>()->fanOutletNode();
  }

  boost::optional<Node> WaterHeaterHeatPumpWrappedCondenser::mixedAirNode() const {
    return getImpl<detail::WaterHeaterHeatPumpWrappedCondenser_Impl>()->mixedAirNode();
  }

  boost::optional<Node> WaterHeaterHeatPumpWrappedCondenser::outdoorAirNode() const {
    return getImpl<detail::WaterHeaterHeatPumpWrappedCondenser_Impl>()->outdoorAirNode();
  }

  boost::optional<Node> WaterHeaterHeatPumpWrappedCondenser::reliefAirNode() const {
    return getImpl<detail::WaterHeaterHeatPumpWrappedCondenser_Impl>()->reliefAirNode();
  }

  std::vector<ModelObject> WaterHeaterHeatPumpWrappedCondenser::children() const {
    return getImpl<detail::WaterHeaterHeatPumpWrappedCondenser_Impl>()->children();
  }

  boost::optional<double> WaterHeaterHeatPumpWrappedCondenser::controlSensor1HeightInStratifiedTank() const {
    return getImpl<detail::WaterHeaterHeatPumpWrappedCondenser_Impl>()->controlSensor1HeightInStratifiedTank();
  }

  bool WaterHeaterHeatPumpWrappedCondenser::setControlSensor1HeightInStratifiedTank(double controlSensor1HeightInStratifiedTank) {
    return getImpl<detail::WaterHeaterHeatPumpWrappedCondenser_Impl>()->setControlSensor1HeightInStratifiedTank(controlSensor1HeightInStratifiedTank);
  }

  void WaterHeaterHeatPumpWrappedCondenser::resetControlSensor1HeightInStratifiedTank() {
    getImpl<detail::WaterHeaterHeatPumpWrappedCondenser_Impl>()->resetControlSensor1HeightInStratifiedTank();
  }

  double WaterHeaterHeatPumpWrappedCondenser::controlSensor1Weight() const {
    return getImpl<detail::WaterHeaterHeatPumpWrappedCondenser_Impl>()->controlSensor1Weight();
  }

  bool WaterHeaterHeatPumpWrappedCondenser::isControlSensor1WeightDefaulted() const {
    return getImpl<detail::WaterHeaterHeatPumpWrappedCondenser_Impl>()->isControlSensor1WeightDefaulted();
  }

  bool WaterHeaterHeatPumpWrappedCondenser::setControlSensor1Weight(double controlSensor1Weight) {
    return getImpl<detail::WaterHeaterHeatPumpWrappedCondenser_Impl>()->setControlSensor1Weight(controlSensor1Weight);
  }

  void WaterHeaterHeatPumpWrappedCondenser::resetControlSensor1Weight() {
    getImpl<detail::WaterHeaterHeatPumpWrappedCondenser_Impl>()->resetControlSensor1Weight();
  }

  boost::optional<double> WaterHeaterHeatPumpWrappedCondenser::controlSensor2HeightInStratifiedTank() const {
    return getImpl<detail::WaterHeaterHeatPumpWrappedCondenser_Impl>()->controlSensor2HeightInStratifiedTank();
  }

  bool WaterHeaterHeatPumpWrappedCondenser::setControlSensor2HeightInStratifiedTank(double controlSensor2HeightInStratifiedTank) {
    return getImpl<detail::WaterHeaterHeatPumpWrappedCondenser_Impl>()->setControlSensor2HeightInStratifiedTank(controlSensor2HeightInStratifiedTank);
  }

  void WaterHeaterHeatPumpWrappedCondenser::resetControlSensor2HeightInStratifiedTank() {
    getImpl<detail::WaterHeaterHeatPumpWrappedCondenser_Impl>()->resetControlSensor2HeightInStratifiedTank();
  }

  namespace detail {

    boost::optional<Schedule> WaterHeaterHeatPumpWrappedCondenser_Impl::availabilitySchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(WaterHeater_HeatPump_WrappedCondenserFields::AvailabilityScheduleName);
    }

    bool WaterHeaterHeatPumpWrappedCondenser_Impl::setAvailabilitySchedule(Schedule& schedule) {
      return setSchedule(WaterHeater_HeatPump_WrappedCondenserFields::AvailabilityScheduleName, "WaterHeaterHeatPumpWrappedCondenser",
                         "Availability", schedule);
    }

    void WaterHeaterHeatPumpWrappedCondenser_Impl::resetAvailabilitySchedule() {
      OS_ASSERT(setString(WaterHeater_HeatPump_WrappedCondenserFields::AvailabilityScheduleName, ""));
    }

    Schedule WaterHeaterHeatPumpWrappedCondenser_Impl::compressorSetpointTemperatureSchedule() const {
      auto value = getObject<ModelObject>().getModelObjectTarget<Schedule>(
        WaterHeater_HeatPump_WrappedCondenserFields::CompressorSetpointTemperatureScheduleName);
      OS_ASSERT(value);
      return *value;
    }

    bool WaterHeaterHeatPumpWrappedCondenser_Impl::setCompressorSetpointTemperatureSchedule(Schedule& schedule) {
      return setSchedule(WaterHeater_HeatPump_WrappedCondenserFields::CompressorSetpointTemperatureScheduleName,
                         "WaterHeaterHeatPumpWrappedCondenser", "Compressor Setpoint Temperature", schedule);
    }

    boost::optional<Schedule> WaterHeaterHeatPumpWrappedCondenser_Impl::inletAirTemperatureSchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(WaterHeater_HeatPump_WrappedCondenserFields::InletAirTemperatureScheduleName);
    }

    bool WaterHeaterHeatPumpWrappedCondenser_Impl::setInletAirTemperatureSchedule(Schedule& schedule) {
      return setSchedule(WaterHeater_HeatPump_WrappedCondenserFields::InletAirTemperatureScheduleName,
                         "WaterHeaterHeatPumpWrappedCondenser", "Inlet Air Temperature", schedule);
    }

    void WaterHeaterHeatPumpWrappedCondenser_Impl::resetInletAirTemperatureSchedule() {
      OS_ASSERT(setString(WaterHeater_HeatPump_WrappedCondenserFields::InletAirTemperatureScheduleName, ""));
    }

    boost::optional<Schedule> WaterHeaterHeatPumpWrappedCondenser_Impl::inletAirHumiditySchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(WaterHeater_HeatPump_WrappedCondenserFields::InletAirHumidityScheduleName);
    }

    bool WaterHeaterHeatPumpWrappedCondenser_Impl::setInletAirHumiditySchedule(Schedule& schedule) {
      return setSchedule(WaterHeater_HeatPump_WrappedCondenserFields::InletAirHumidityScheduleName,
                         "WaterHeaterHeatPumpWrappedCondenser", "Inlet Air Humidity", schedule);
    }

    void WaterHeaterHeatPumpWrappedCondenser_Impl::resetInletAirHumiditySchedule() {
      OS_ASSERT(setString(WaterHeater_HeatPump_WrappedCondenserFields::InletAirHumidityScheduleName, ""));
    }

    HVACComponent WaterHeaterHeatPumpWrappedCondenser_Impl::tank() const {
      auto value = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(WaterHeater_HeatPump_WrappedCondenserFields::TankName);
      OS_ASSERT(value);
      return *value;
    }

    bool WaterHeaterHeatPumpWrappedCondenser_Impl::setTank(const HVACComponent& waterHeaterStratified) {
      if ((waterHeaterStratified.model() != model()) || !isSupportedWrappedCondenserTank(waterHeaterStratified)) {
        return false;
      }

      const bool result = setPointer(WaterHeater_HeatPump_WrappedCondenserFields::TankName, waterHeaterStratified.handle(), false);
      if (result) {
        maintainContainedAirPath();
      }
      return result;
    }

    ModelObject WaterHeaterHeatPumpWrappedCondenser_Impl::dXCoil() const {
      auto value = getObject<ModelObject>().getModelObjectTarget<ModelObject>(WaterHeater_HeatPump_WrappedCondenserFields::DXCoilName);
      OS_ASSERT(value);
      return *value;
    }

    bool WaterHeaterHeatPumpWrappedCondenser_Impl::setDXCoil(const ModelObject& heatPumpWaterHeaterDXCoilWrapped) {
      if ((heatPumpWaterHeaterDXCoilWrapped.model() != model()) || !isSupportedWrappedCondenserDXCoil(heatPumpWaterHeaterDXCoilWrapped)) {
        return false;
      }

      const bool result = setPointer(WaterHeater_HeatPump_WrappedCondenserFields::DXCoilName, heatPumpWaterHeaterDXCoilWrapped.handle(), false);
      if (result) {
        maintainContainedAirPath();
      }
      return result;
    }

    boost::optional<Schedule> WaterHeaterHeatPumpWrappedCondenser_Impl::compressorAmbientTemperatureSchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(
        WaterHeater_HeatPump_WrappedCondenserFields::CompressorAmbientTemperatureScheduleName);
    }

    bool WaterHeaterHeatPumpWrappedCondenser_Impl::setCompressorAmbientTemperatureSchedule(Schedule& schedule) {
      return setSchedule(WaterHeater_HeatPump_WrappedCondenserFields::CompressorAmbientTemperatureScheduleName,
                         "WaterHeaterHeatPumpWrappedCondenser", "Compressor Ambient Temperature", schedule);
    }

    void WaterHeaterHeatPumpWrappedCondenser_Impl::resetCompressorAmbientTemperatureSchedule() {
      OS_ASSERT(setString(WaterHeater_HeatPump_WrappedCondenserFields::CompressorAmbientTemperatureScheduleName, ""));
    }

    HVACComponent WaterHeaterHeatPumpWrappedCondenser_Impl::fan() const {
      auto value = getObject<ModelObject>().getModelObjectTarget<StraightComponent>(WaterHeater_HeatPump_WrappedCondenserFields::FanName);
      OS_ASSERT(value);
      return value->cast<HVACComponent>();
    }

    bool WaterHeaterHeatPumpWrappedCondenser_Impl::setFan(const HVACComponent& fanComponent) {
      if ((fanComponent.model() != model()) || !fanComponent.optionalCast<StraightComponent>()) {
        return false;
      }

      const bool result = setPointer(WaterHeater_HeatPump_WrappedCondenserFields::FanName, fanComponent.handle(), false);
      if (result) {
        maintainContainedAirPath();
      }
      return result;
    }

    std::string WaterHeaterHeatPumpWrappedCondenser_Impl::airInletNodeName() const {
      if (openstudio::istringEqual(inletAirConfiguration(), "OutdoorAirOnly")) {
        return {};
      }
      if (auto node = resolvedNodeTarget(WaterHeater_HeatPump_WrappedCondenserFields::AirInletNodeName)) {
        return node->nameString();
      }
      return {};
    }

    std::string WaterHeaterHeatPumpWrappedCondenser_Impl::airOutletNodeName() const {
      if (openstudio::istringEqual(inletAirConfiguration(), "OutdoorAirOnly")) {
        return {};
      }
      if (auto node = resolvedNodeTarget(WaterHeater_HeatPump_WrappedCondenserFields::AirOutletNodeName)) {
        return node->nameString();
      }
      return {};
    }

    boost::optional<Schedule> WaterHeaterHeatPumpWrappedCondenser_Impl::inletAirMixerSchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(WaterHeater_HeatPump_WrappedCondenserFields::InletAirMixerScheduleName);
    }

    bool WaterHeaterHeatPumpWrappedCondenser_Impl::setInletAirMixerSchedule(Schedule& schedule) {
      return setSchedule(WaterHeater_HeatPump_WrappedCondenserFields::InletAirMixerScheduleName, "WaterHeaterHeatPumpWrappedCondenser",
                         "Inlet Air Mixer", schedule);
    }

    void WaterHeaterHeatPumpWrappedCondenser_Impl::resetInletAirMixerSchedule() {
      OS_ASSERT(setString(WaterHeater_HeatPump_WrappedCondenserFields::InletAirMixerScheduleName, ""));
    }

    boost::optional<Node> WaterHeaterHeatPumpWrappedCondenser_Impl::fanOutletNode() const {
      auto fanComponent = getObject<ModelObject>().getModelObjectTarget<StraightComponent>(WaterHeater_HeatPump_WrappedCondenserFields::FanName);
      if (!fanComponent) {
        return boost::none;
      }
      return fanComponent->getImpl<detail::ModelObject_Impl>()->resolvedNodeTarget(fanComponent->outletPort());
    }

    boost::optional<Node> WaterHeaterHeatPumpWrappedCondenser_Impl::mixedAirNode() const {
      return resolvedNodeTarget(WaterHeater_HeatPump_WrappedCondenserFields::InletAirMixerNodeName);
    }

    boost::optional<Node> WaterHeaterHeatPumpWrappedCondenser_Impl::outdoorAirNode() const {
      return resolvedNodeTarget(WaterHeater_HeatPump_WrappedCondenserFields::OutdoorAirNodeName);
    }

    boost::optional<Node> WaterHeaterHeatPumpWrappedCondenser_Impl::reliefAirNode() const {
      return resolvedNodeTarget(WaterHeater_HeatPump_WrappedCondenserFields::ExhaustAirNodeName);
    }

    std::vector<ModelObject> WaterHeaterHeatPumpWrappedCondenser_Impl::children() const {
      std::vector<ModelObject> result;
      if (auto child = getObject<ModelObject>().getModelObjectTarget<ModelObject>(WaterHeater_HeatPump_WrappedCondenserFields::TankName)) {
        result.push_back(*child);
      }
      if (auto child = getObject<ModelObject>().getModelObjectTarget<ModelObject>(WaterHeater_HeatPump_WrappedCondenserFields::DXCoilName)) {
        result.push_back(*child);
      }
      if (auto child = getObject<ModelObject>().getModelObjectTarget<ModelObject>(WaterHeater_HeatPump_WrappedCondenserFields::FanName)) {
        result.push_back(*child);
      }
      return result;
    }

    unsigned WaterHeaterHeatPumpWrappedCondenser_Impl::inletPort() const {
      return WaterHeater_HeatPump_WrappedCondenserFields::AirInletNodeName;
    }

    unsigned WaterHeaterHeatPumpWrappedCondenser_Impl::outletPort() const {
      return WaterHeater_HeatPump_WrappedCondenserFields::AirOutletNodeName;
    }

    bool WaterHeaterHeatPumpWrappedCondenser_Impl::addToThermalZone(ThermalZone& thermalZone) {
      if (!ZoneHVACComponent_Impl::addToThermalZone(thermalZone)) {
        return false;
      }
      setCompressorLocation("Zone");
      setInletAirConfiguration("ZoneAirOnly");
      maintainContainedAirPath();
      return true;
    }

    void WaterHeaterHeatPumpWrappedCondenser_Impl::removeFromThermalZone() {
      ZoneHVACComponent_Impl::removeFromThermalZone();
      maintainContainedAirPath();
    }

    void WaterHeaterHeatPumpWrappedCondenser_Impl::doCanonicalize(LoadContext& context) {
      ZoneHVACComponent_Impl::doCanonicalize(context);
      repairContainedAirPath(context);
    }

    bool WaterHeaterHeatPumpWrappedCondenser_Impl::maintainContainedAirPath() {
      return reconcileContainedAirPath(false, nullptr);
    }

    bool WaterHeaterHeatPumpWrappedCondenser_Impl::repairContainedAirPath(LoadContext& context) {
      return reconcileContainedAirPath(true, &context);
    }

    bool WaterHeaterHeatPumpWrappedCondenser_Impl::reconcileContainedAirPath(bool allowNodeRecovery, LoadContext* /*context*/) {
      auto thisObject = getObject<ModelObject>();
      if (!thisObject.name()) {
        thisObject.createName();
      }
      const std::string baseName = thisObject.nameString();

      auto tankObject = thisObject.getModelObjectTarget<HVACComponent>(WaterHeater_HeatPump_WrappedCondenserFields::TankName);
      auto dxObject = thisObject.getModelObjectTarget<ModelObject>(WaterHeater_HeatPump_WrappedCondenserFields::DXCoilName);
      auto fanObject = thisObject.getModelObjectTarget<StraightComponent>(WaterHeater_HeatPump_WrappedCondenserFields::FanName);

      auto tankComponent = tankObject ? tankObject->optionalCast<WaterHeaterStratified>() : boost::none;
      auto dxCoil = dxObject ? dxObject->optionalCast<CoilWaterHeatingAirToWaterHeatPumpWrapped>() : boost::none;

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

      syncObjectType(WaterHeater_HeatPump_WrappedCondenserFields::TankObjectType,
                     tankObject ? boost::optional<std::string>(tankObject->iddObject().name()) : boost::none);
      syncObjectType(WaterHeater_HeatPump_WrappedCondenserFields::DXCoilObjectType,
                     dxObject ? boost::optional<std::string>(dxObject->iddObject().name()) : boost::none);
      syncObjectType(WaterHeater_HeatPump_WrappedCondenserFields::FanObjectType,
                     fanObject ? boost::optional<std::string>(fanObject->iddObject().name()) : boost::none);

      if (tankComponent) {
        if (auto supplyInlet = tankComponent->getImpl<detail::ModelObject_Impl>()->resolvedNodeTarget(tankComponent->supplyInletPort())) {
          changed = thisObject.getImpl<detail::ModelObject_Impl>()->setPointer(
                      WaterHeater_HeatPump_WrappedCondenserFields::TankUseSideInletNodeName, supplyInlet->handle(), false)
                    || changed;
        } else {
          changed = clearStringIfNeeded(thisObject, WaterHeater_HeatPump_WrappedCondenserFields::TankUseSideInletNodeName) || changed;
        }
        if (auto supplyOutlet = tankComponent->getImpl<detail::ModelObject_Impl>()->resolvedNodeTarget(tankComponent->supplyOutletPort())) {
          changed = thisObject.getImpl<detail::ModelObject_Impl>()->setPointer(
                      WaterHeater_HeatPump_WrappedCondenserFields::TankUseSideOutletNodeName, supplyOutlet->handle(), false)
                    || changed;
        } else {
          changed = clearStringIfNeeded(thisObject, WaterHeater_HeatPump_WrappedCondenserFields::TankUseSideOutletNodeName) || changed;
        }
      }

      if (!tankComponent || !dxCoil || !fanObject) {
        return changed;
      }

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
        airInlet = resolvedOrCreatedNodeTarget(WaterHeater_HeatPump_WrappedCondenserFields::AirInletNodeName, inletName);
        airOutlet = resolvedOrCreatedNodeTarget(WaterHeater_HeatPump_WrappedCondenserFields::AirOutletNodeName, outletName);
        changed =
          thisObject.getImpl<detail::ModelObject_Impl>()->setPointer(WaterHeater_HeatPump_WrappedCondenserFields::AirInletNodeName,
                                                                     airInlet->handle(), false)
          || changed;
        changed =
          thisObject.getImpl<detail::ModelObject_Impl>()->setPointer(WaterHeater_HeatPump_WrappedCondenserFields::AirOutletNodeName,
                                                                     airOutlet->handle(), false)
          || changed;
      } else {
        changed = clearStringIfNeeded(thisObject, WaterHeater_HeatPump_WrappedCondenserFields::AirInletNodeName) || changed;
        changed = clearStringIfNeeded(thisObject, WaterHeater_HeatPump_WrappedCondenserFields::AirOutletNodeName) || changed;
      }

      if (auto zone = thermalZone(); zone && !outdoorOnly && !openstudio::istringEqual(inletAirConfiguration(), "Schedule")) {
        if (auto zoneName = zone->nameString(); !zoneName.empty()) {
          if (auto currentZoneName = thisObject.getString(WaterHeater_HeatPump_WrappedCondenserFields::InletAirZoneName, true);
              !currentZoneName || !openstudio::istringEqual(*currentZoneName, zoneName)) {
            OS_ASSERT(thisObject.setString(WaterHeater_HeatPump_WrappedCondenserFields::InletAirZoneName, zoneName));
            changed = true;
          }
        }
      } else {
        changed = clearStringIfNeeded(thisObject, WaterHeater_HeatPump_WrappedCondenserFields::InletAirZoneName) || changed;
      }

      boost::optional<Node> outdoorAir;
      boost::optional<Node> reliefAir;
      boost::optional<Node> mixedAir;
      boost::optional<Node> splitterNode;
      if (outdoorOnly || zoneAndOutdoorAir) {
        outdoorAir = resolvedOrCreatedNodeTarget(WaterHeater_HeatPump_WrappedCondenserFields::OutdoorAirNodeName, baseName + " Outdoor Air");
        reliefAir = resolvedOrCreatedNodeTarget(WaterHeater_HeatPump_WrappedCondenserFields::ExhaustAirNodeName, baseName + " Exhaust Air");
        changed =
          thisObject.getImpl<detail::ModelObject_Impl>()->setPointer(WaterHeater_HeatPump_WrappedCondenserFields::OutdoorAirNodeName,
                                                                     outdoorAir->handle(), false)
          || changed;
        changed =
          thisObject.getImpl<detail::ModelObject_Impl>()->setPointer(WaterHeater_HeatPump_WrappedCondenserFields::ExhaustAirNodeName,
                                                                     reliefAir->handle(), false)
          || changed;
      } else {
        changed = clearStringIfNeeded(thisObject, WaterHeater_HeatPump_WrappedCondenserFields::OutdoorAirNodeName) || changed;
        changed = clearStringIfNeeded(thisObject, WaterHeater_HeatPump_WrappedCondenserFields::ExhaustAirNodeName) || changed;
      }

      if (zoneAndOutdoorAir) {
        mixedAir = resolvedOrCreatedNodeTarget(WaterHeater_HeatPump_WrappedCondenserFields::InletAirMixerNodeName, baseName + " Mixed Air Node");
        splitterNode =
          resolvedOrCreatedNodeTarget(WaterHeater_HeatPump_WrappedCondenserFields::OutletAirSplitterNodeName, baseName + " Fan Outlet Node");
        changed =
          thisObject.getImpl<detail::ModelObject_Impl>()->setPointer(WaterHeater_HeatPump_WrappedCondenserFields::InletAirMixerNodeName,
                                                                     mixedAir->handle(), false)
          || changed;
        changed =
          thisObject.getImpl<detail::ModelObject_Impl>()->setPointer(WaterHeater_HeatPump_WrappedCondenserFields::OutletAirSplitterNodeName,
                                                                     splitterNode->handle(), false)
          || changed;
      } else {
        changed = clearStringIfNeeded(thisObject, WaterHeater_HeatPump_WrappedCondenserFields::InletAirMixerNodeName) || changed;
        changed = clearStringIfNeeded(thisObject, WaterHeater_HeatPump_WrappedCondenserFields::OutletAirSplitterNodeName) || changed;
      }

      boost::optional<Node> evaporatorInlet;
      boost::optional<Node> evaporatorOutlet;
      boost::optional<Node> fanInlet;
      boost::optional<Node> fanOutlet;

      if (drawThrough) {
        evaporatorInlet = outdoorOnly ? outdoorAir : (zoneAndOutdoorAir ? mixedAir : airInlet);
        if (allowNodeRecovery) {
          evaporatorOutlet = dxCoil->getImpl<detail::ModelObject_Impl>()->resolvedNodeTarget(dxCoil->outletPort());
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
      changed = dxCoil->getImpl<detail::ModelObject_Impl>()->setPointer(dxCoil->inletPort(), evaporatorInlet->handle(), false) || changed;
      changed = dxCoil->getImpl<detail::ModelObject_Impl>()->setPointer(dxCoil->outletPort(), evaporatorOutlet->handle(), false) || changed;

      return changed;
    }

    double WaterHeaterHeatPumpWrappedCondenser_Impl::deadBandTemperatureDifference() const {
      const auto value = getDouble(WaterHeater_HeatPump_WrappedCondenserFields::DeadBandTemperatureDifference, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WaterHeaterHeatPumpWrappedCondenser_Impl::isDeadBandTemperatureDifferenceDefaulted() const {
      return isEmpty(WaterHeater_HeatPump_WrappedCondenserFields::DeadBandTemperatureDifference);
    }

    bool WaterHeaterHeatPumpWrappedCondenser_Impl::setDeadBandTemperatureDifference(double deadBandTemperatureDifference) {
      const bool result = setDouble(WaterHeater_HeatPump_WrappedCondenserFields::DeadBandTemperatureDifference, deadBandTemperatureDifference);
      OS_ASSERT(result);
      return result;
    }

    void WaterHeaterHeatPumpWrappedCondenser_Impl::resetDeadBandTemperatureDifference() {
      OS_ASSERT(setString(WaterHeater_HeatPump_WrappedCondenserFields::DeadBandTemperatureDifference, ""));
    }

    double WaterHeaterHeatPumpWrappedCondenser_Impl::condenserBottomLocation() const {
      const auto value = getDouble(WaterHeater_HeatPump_WrappedCondenserFields::CondenserBottomLocation, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WaterHeaterHeatPumpWrappedCondenser_Impl::isCondenserBottomLocationDefaulted() const {
      return isEmpty(WaterHeater_HeatPump_WrappedCondenserFields::CondenserBottomLocation);
    }

    bool WaterHeaterHeatPumpWrappedCondenser_Impl::setCondenserBottomLocation(double condenserBottomLocation) {
      const bool result = setDouble(WaterHeater_HeatPump_WrappedCondenserFields::CondenserBottomLocation, condenserBottomLocation);
      OS_ASSERT(result);
      return result;
    }

    void WaterHeaterHeatPumpWrappedCondenser_Impl::resetCondenserBottomLocation() {
      OS_ASSERT(setString(WaterHeater_HeatPump_WrappedCondenserFields::CondenserBottomLocation, ""));
    }

    double WaterHeaterHeatPumpWrappedCondenser_Impl::condenserTopLocation() const {
      const auto value = getDouble(WaterHeater_HeatPump_WrappedCondenserFields::CondenserTopLocation, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WaterHeaterHeatPumpWrappedCondenser_Impl::setCondenserTopLocation(double condenserTopLocation) {
      const bool result = setDouble(WaterHeater_HeatPump_WrappedCondenserFields::CondenserTopLocation, condenserTopLocation);
      OS_ASSERT(result);
      return result;
    }

    boost::optional<double> WaterHeaterHeatPumpWrappedCondenser_Impl::evaporatorAirFlowRate() const {
      return getDouble(WaterHeater_HeatPump_WrappedCondenserFields::EvaporatorAirFlowRate, true);
    }

    bool WaterHeaterHeatPumpWrappedCondenser_Impl::isEvaporatorAirFlowRateAutocalculated() const {
      if (auto value = getString(WaterHeater_HeatPump_WrappedCondenserFields::EvaporatorAirFlowRate, true)) {
        return openstudio::istringEqual(*value, "autocalculate");
      }
      return false;
    }

    bool WaterHeaterHeatPumpWrappedCondenser_Impl::setEvaporatorAirFlowRate(double evaporatorAirFlowRate) {
      const bool result = setDouble(WaterHeater_HeatPump_WrappedCondenserFields::EvaporatorAirFlowRate, evaporatorAirFlowRate);
      OS_ASSERT(result);
      return result;
    }

    void WaterHeaterHeatPumpWrappedCondenser_Impl::resetEvaporatorAirFlowRate() {
      OS_ASSERT(setString(WaterHeater_HeatPump_WrappedCondenserFields::EvaporatorAirFlowRate, ""));
    }

    void WaterHeaterHeatPumpWrappedCondenser_Impl::autocalculateEvaporatorAirFlowRate() {
      OS_ASSERT(setString(WaterHeater_HeatPump_WrappedCondenserFields::EvaporatorAirFlowRate, "autocalculate"));
    }

    std::string WaterHeaterHeatPumpWrappedCondenser_Impl::inletAirConfiguration() const {
      const auto value = getString(WaterHeater_HeatPump_WrappedCondenserFields::InletAirConfiguration, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WaterHeaterHeatPumpWrappedCondenser_Impl::setInletAirConfiguration(const std::string& inletAirConfiguration) {
      const bool result = setString(WaterHeater_HeatPump_WrappedCondenserFields::InletAirConfiguration, inletAirConfiguration);
      if (result) {
        maintainContainedAirPath();
      }
      OS_ASSERT(result);
      return result;
    }

    double WaterHeaterHeatPumpWrappedCondenser_Impl::minimumInletAirTemperatureforCompressorOperation() const {
      const auto value = getDouble(WaterHeater_HeatPump_WrappedCondenserFields::MinimumInletAirTemperatureforCompressorOperation, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WaterHeaterHeatPumpWrappedCondenser_Impl::isMinimumInletAirTemperatureforCompressorOperationDefaulted() const {
      return isEmpty(WaterHeater_HeatPump_WrappedCondenserFields::MinimumInletAirTemperatureforCompressorOperation);
    }

    bool WaterHeaterHeatPumpWrappedCondenser_Impl::setMinimumInletAirTemperatureforCompressorOperation(
      double minimumInletAirTemperatureforCompressorOperation) {
      const bool result = setDouble(WaterHeater_HeatPump_WrappedCondenserFields::MinimumInletAirTemperatureforCompressorOperation,
                                    minimumInletAirTemperatureforCompressorOperation);
      OS_ASSERT(result);
      return result;
    }

    void WaterHeaterHeatPumpWrappedCondenser_Impl::resetMinimumInletAirTemperatureforCompressorOperation() {
      OS_ASSERT(setString(WaterHeater_HeatPump_WrappedCondenserFields::MinimumInletAirTemperatureforCompressorOperation, ""));
    }

    double WaterHeaterHeatPumpWrappedCondenser_Impl::maximumInletAirTemperatureforCompressorOperation() const {
      const auto value = getDouble(WaterHeater_HeatPump_WrappedCondenserFields::MaximumInletAirTemperatureforCompressorOperation, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WaterHeaterHeatPumpWrappedCondenser_Impl::isMaximumInletAirTemperatureforCompressorOperationDefaulted() const {
      return isEmpty(WaterHeater_HeatPump_WrappedCondenserFields::MaximumInletAirTemperatureforCompressorOperation);
    }

    bool WaterHeaterHeatPumpWrappedCondenser_Impl::setMaximumInletAirTemperatureforCompressorOperation(
      double maximumInletAirTemperatureforCompressorOperation) {
      const bool result = setDouble(WaterHeater_HeatPump_WrappedCondenserFields::MaximumInletAirTemperatureforCompressorOperation,
                                    maximumInletAirTemperatureforCompressorOperation);
      OS_ASSERT(result);
      return result;
    }

    void WaterHeaterHeatPumpWrappedCondenser_Impl::resetMaximumInletAirTemperatureforCompressorOperation() {
      OS_ASSERT(setString(WaterHeater_HeatPump_WrappedCondenserFields::MaximumInletAirTemperatureforCompressorOperation, ""));
    }

    std::string WaterHeaterHeatPumpWrappedCondenser_Impl::compressorLocation() const {
      const auto value = getString(WaterHeater_HeatPump_WrappedCondenserFields::CompressorLocation, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WaterHeaterHeatPumpWrappedCondenser_Impl::setCompressorLocation(const std::string& compressorLocation) {
      const bool result = setString(WaterHeater_HeatPump_WrappedCondenserFields::CompressorLocation, compressorLocation);
      OS_ASSERT(result);
      return result;
    }

    std::string WaterHeaterHeatPumpWrappedCondenser_Impl::fanPlacement() const {
      const auto value = getString(WaterHeater_HeatPump_WrappedCondenserFields::FanPlacement, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WaterHeaterHeatPumpWrappedCondenser_Impl::isFanPlacementDefaulted() const {
      return isEmpty(WaterHeater_HeatPump_WrappedCondenserFields::FanPlacement);
    }

    bool WaterHeaterHeatPumpWrappedCondenser_Impl::setFanPlacement(const std::string& fanPlacement) {
      const bool result = setString(WaterHeater_HeatPump_WrappedCondenserFields::FanPlacement, fanPlacement);
      if (result) {
        maintainContainedAirPath();
      }
      OS_ASSERT(result);
      return result;
    }

    void WaterHeaterHeatPumpWrappedCondenser_Impl::resetFanPlacement() {
      OS_ASSERT(setString(WaterHeater_HeatPump_WrappedCondenserFields::FanPlacement, ""));
      maintainContainedAirPath();
    }

    double WaterHeaterHeatPumpWrappedCondenser_Impl::onCycleParasiticElectricLoad() const {
      const auto value = getDouble(WaterHeater_HeatPump_WrappedCondenserFields::OnCycleParasiticElectricLoad, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WaterHeaterHeatPumpWrappedCondenser_Impl::isOnCycleParasiticElectricLoadDefaulted() const {
      return isEmpty(WaterHeater_HeatPump_WrappedCondenserFields::OnCycleParasiticElectricLoad);
    }

    bool WaterHeaterHeatPumpWrappedCondenser_Impl::setOnCycleParasiticElectricLoad(double onCycleParasiticElectricLoad) {
      const bool result = setDouble(WaterHeater_HeatPump_WrappedCondenserFields::OnCycleParasiticElectricLoad, onCycleParasiticElectricLoad);
      OS_ASSERT(result);
      return result;
    }

    void WaterHeaterHeatPumpWrappedCondenser_Impl::resetOnCycleParasiticElectricLoad() {
      OS_ASSERT(setString(WaterHeater_HeatPump_WrappedCondenserFields::OnCycleParasiticElectricLoad, ""));
    }

    double WaterHeaterHeatPumpWrappedCondenser_Impl::offCycleParasiticElectricLoad() const {
      const auto value = getDouble(WaterHeater_HeatPump_WrappedCondenserFields::OffCycleParasiticElectricLoad, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WaterHeaterHeatPumpWrappedCondenser_Impl::isOffCycleParasiticElectricLoadDefaulted() const {
      return isEmpty(WaterHeater_HeatPump_WrappedCondenserFields::OffCycleParasiticElectricLoad);
    }

    bool WaterHeaterHeatPumpWrappedCondenser_Impl::setOffCycleParasiticElectricLoad(double offCycleParasiticElectricLoad) {
      const bool result = setDouble(WaterHeater_HeatPump_WrappedCondenserFields::OffCycleParasiticElectricLoad, offCycleParasiticElectricLoad);
      OS_ASSERT(result);
      return result;
    }

    void WaterHeaterHeatPumpWrappedCondenser_Impl::resetOffCycleParasiticElectricLoad() {
      OS_ASSERT(setString(WaterHeater_HeatPump_WrappedCondenserFields::OffCycleParasiticElectricLoad, ""));
    }

    std::string WaterHeaterHeatPumpWrappedCondenser_Impl::parasiticHeatRejectionLocation() const {
      const auto value = getString(WaterHeater_HeatPump_WrappedCondenserFields::ParasiticHeatRejectionLocation, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WaterHeaterHeatPumpWrappedCondenser_Impl::isParasiticHeatRejectionLocationDefaulted() const {
      return isEmpty(WaterHeater_HeatPump_WrappedCondenserFields::ParasiticHeatRejectionLocation);
    }

    bool WaterHeaterHeatPumpWrappedCondenser_Impl::setParasiticHeatRejectionLocation(const std::string& parasiticHeatRejectionLocation) {
      const bool result = setString(WaterHeater_HeatPump_WrappedCondenserFields::ParasiticHeatRejectionLocation, parasiticHeatRejectionLocation);
      OS_ASSERT(result);
      return result;
    }

    void WaterHeaterHeatPumpWrappedCondenser_Impl::resetParasiticHeatRejectionLocation() {
      OS_ASSERT(setString(WaterHeater_HeatPump_WrappedCondenserFields::ParasiticHeatRejectionLocation, ""));
    }

    std::string WaterHeaterHeatPumpWrappedCondenser_Impl::tankElementControlLogic() const {
      const auto value = getString(WaterHeater_HeatPump_WrappedCondenserFields::TankElementControlLogic, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WaterHeaterHeatPumpWrappedCondenser_Impl::isTankElementControlLogicDefaulted() const {
      return isEmpty(WaterHeater_HeatPump_WrappedCondenserFields::TankElementControlLogic);
    }

    bool WaterHeaterHeatPumpWrappedCondenser_Impl::setTankElementControlLogic(const std::string& tankElementControlLogic) {
      const bool result = setString(WaterHeater_HeatPump_WrappedCondenserFields::TankElementControlLogic, tankElementControlLogic);
      OS_ASSERT(result);
      return result;
    }

    void WaterHeaterHeatPumpWrappedCondenser_Impl::resetTankElementControlLogic() {
      OS_ASSERT(setString(WaterHeater_HeatPump_WrappedCondenserFields::TankElementControlLogic, ""));
    }

    boost::optional<double> WaterHeaterHeatPumpWrappedCondenser_Impl::controlSensor1HeightInStratifiedTank() const {
      return getDouble(WaterHeater_HeatPump_WrappedCondenserFields::ControlSensor1HeightInStratifiedTank, true);
    }

    bool WaterHeaterHeatPumpWrappedCondenser_Impl::setControlSensor1HeightInStratifiedTank(double controlSensor1HeightInStratifiedTank) {
      const bool result =
        setDouble(WaterHeater_HeatPump_WrappedCondenserFields::ControlSensor1HeightInStratifiedTank, controlSensor1HeightInStratifiedTank);
      OS_ASSERT(result);
      return result;
    }

    void WaterHeaterHeatPumpWrappedCondenser_Impl::resetControlSensor1HeightInStratifiedTank() {
      OS_ASSERT(setString(WaterHeater_HeatPump_WrappedCondenserFields::ControlSensor1HeightInStratifiedTank, ""));
    }

    double WaterHeaterHeatPumpWrappedCondenser_Impl::controlSensor1Weight() const {
      const auto value = getDouble(WaterHeater_HeatPump_WrappedCondenserFields::ControlSensor1Weight, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WaterHeaterHeatPumpWrappedCondenser_Impl::isControlSensor1WeightDefaulted() const {
      return isEmpty(WaterHeater_HeatPump_WrappedCondenserFields::ControlSensor1Weight);
    }

    bool WaterHeaterHeatPumpWrappedCondenser_Impl::setControlSensor1Weight(double controlSensor1Weight) {
      const bool result = setDouble(WaterHeater_HeatPump_WrappedCondenserFields::ControlSensor1Weight, controlSensor1Weight);
      OS_ASSERT(result);
      return result;
    }

    void WaterHeaterHeatPumpWrappedCondenser_Impl::resetControlSensor1Weight() {
      OS_ASSERT(setString(WaterHeater_HeatPump_WrappedCondenserFields::ControlSensor1Weight, ""));
    }

    boost::optional<double> WaterHeaterHeatPumpWrappedCondenser_Impl::controlSensor2HeightInStratifiedTank() const {
      return getDouble(WaterHeater_HeatPump_WrappedCondenserFields::ControlSensor2HeightInStratifiedTank, true);
    }

    bool WaterHeaterHeatPumpWrappedCondenser_Impl::setControlSensor2HeightInStratifiedTank(double controlSensor2HeightInStratifiedTank) {
      const bool result =
        setDouble(WaterHeater_HeatPump_WrappedCondenserFields::ControlSensor2HeightInStratifiedTank, controlSensor2HeightInStratifiedTank);
      OS_ASSERT(result);
      return result;
    }

    void WaterHeaterHeatPumpWrappedCondenser_Impl::resetControlSensor2HeightInStratifiedTank() {
      OS_ASSERT(setString(WaterHeater_HeatPump_WrappedCondenserFields::ControlSensor2HeightInStratifiedTank, ""));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
