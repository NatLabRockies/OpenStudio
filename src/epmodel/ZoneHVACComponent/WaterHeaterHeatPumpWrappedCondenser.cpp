/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ZoneHVACComponent/WaterHeaterHeatPumpWrappedCondenser.hpp"
#include "ZoneHVACComponent/WaterHeaterHeatPumpWrappedCondenser_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/WaterHeater_HeatPump_WrappedCondenser_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  WaterHeaterHeatPumpWrappedCondenser::WaterHeaterHeatPumpWrappedCondenser(const Model& model)
    : ModelObject(WaterHeaterHeatPumpWrappedCondenser::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::WaterHeaterHeatPumpWrappedCondenser_Impl>());
  }

  WaterHeaterHeatPumpWrappedCondenser::WaterHeaterHeatPumpWrappedCondenser(std::shared_ptr<detail::WaterHeaterHeatPumpWrappedCondenser_Impl> impl)
    : ModelObject(std::move(impl)) {}

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
      OS_ASSERT(result);
      return result;
    }

    void WaterHeaterHeatPumpWrappedCondenser_Impl::resetFanPlacement() {
      OS_ASSERT(setString(WaterHeater_HeatPump_WrappedCondenserFields::FanPlacement, ""));
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
