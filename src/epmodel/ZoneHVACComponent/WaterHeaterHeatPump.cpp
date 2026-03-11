/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ZoneHVACComponent/WaterHeaterHeatPump.hpp"
#include "ZoneHVACComponent/WaterHeaterHeatPump_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/WaterHeater_HeatPump_PumpedCondenser_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  WaterHeaterHeatPump::WaterHeaterHeatPump(const Model& model) : ModelObject(WaterHeaterHeatPump::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::WaterHeaterHeatPump_Impl>());

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

  WaterHeaterHeatPump::WaterHeaterHeatPump(std::shared_ptr<detail::WaterHeaterHeatPump_Impl> impl) : ModelObject(std::move(impl)) {}

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
      OS_ASSERT(result);
      return result;
    }

    void WaterHeaterHeatPump_Impl::resetFanPlacement() {
      OS_ASSERT(setString(openstudio::WaterHeater_HeatPump_PumpedCondenserFields::FanPlacement, ""));
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
