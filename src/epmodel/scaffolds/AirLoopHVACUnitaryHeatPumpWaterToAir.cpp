/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "AirLoopHVACUnitaryHeatPumpWaterToAir.hpp"
#include "AirLoopHVACUnitaryHeatPumpWaterToAir_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/AirLoopHVAC_UnitaryHeatPump_WaterToAir_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

  AirLoopHVACUnitaryHeatPumpWaterToAir::AirLoopHVACUnitaryHeatPumpWaterToAir(const Model& model)
    : ModelObject(AirLoopHVACUnitaryHeatPumpWaterToAir::iddObjectType(), model) {}

  AirLoopHVACUnitaryHeatPumpWaterToAir::AirLoopHVACUnitaryHeatPumpWaterToAir(std::shared_ptr<detail::AirLoopHVACUnitaryHeatPumpWaterToAir_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType AirLoopHVACUnitaryHeatPumpWaterToAir::iddObjectType() {
    return IddObjectType::AirLoopHVAC_UnitaryHeatPump_WaterToAir;
  }

  std::vector<std::string> AirLoopHVACUnitaryHeatPumpWaterToAir::supplyAirFanObjectTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::SupplyAirFanObjectType);
  }

  std::vector<std::string> AirLoopHVACUnitaryHeatPumpWaterToAir::heatingCoilObjectTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::HeatingCoilObjectType);
  }

  std::vector<std::string> AirLoopHVACUnitaryHeatPumpWaterToAir::coolingCoilObjectTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::CoolingCoilObjectType);
  }

  std::vector<std::string> AirLoopHVACUnitaryHeatPumpWaterToAir::supplementalHeatingCoilObjectTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::SupplementalHeatingCoilObjectType);
  }

  std::vector<std::string> AirLoopHVACUnitaryHeatPumpWaterToAir::fanPlacementValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::FanPlacement);
  }

  std::vector<std::string> AirLoopHVACUnitaryHeatPumpWaterToAir::dehumidificationControlTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::DehumidificationControlType);
  }

  std::vector<std::string> AirLoopHVACUnitaryHeatPumpWaterToAir::heatPumpCoilWaterFlowModeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::HeatPumpCoilWaterFlowMode);
  }

  boost::optional<double> AirLoopHVACUnitaryHeatPumpWaterToAir::supplyAirFlowRate() const {
    return getImpl<detail::AirLoopHVACUnitaryHeatPumpWaterToAir_Impl>()->supplyAirFlowRate();
  }

  bool AirLoopHVACUnitaryHeatPumpWaterToAir::isSupplyAirFlowRateAutosized() const {
    return getImpl<detail::AirLoopHVACUnitaryHeatPumpWaterToAir_Impl>()->isSupplyAirFlowRateAutosized();
  }

  bool AirLoopHVACUnitaryHeatPumpWaterToAir::setSupplyAirFlowRate(double supplyAirFlowRate) {
    return getImpl<detail::AirLoopHVACUnitaryHeatPumpWaterToAir_Impl>()->setSupplyAirFlowRate(supplyAirFlowRate);
  }

  void AirLoopHVACUnitaryHeatPumpWaterToAir::autosizeSupplyAirFlowRate() {
    getImpl<detail::AirLoopHVACUnitaryHeatPumpWaterToAir_Impl>()->autosizeSupplyAirFlowRate();
  }

  std::string AirLoopHVACUnitaryHeatPumpWaterToAir::supplyAirFanObjectType() const {
    return getImpl<detail::AirLoopHVACUnitaryHeatPumpWaterToAir_Impl>()->supplyAirFanObjectType();
  }

  bool AirLoopHVACUnitaryHeatPumpWaterToAir::setSupplyAirFanObjectType(const std::string& supplyAirFanObjectType) {
    return getImpl<detail::AirLoopHVACUnitaryHeatPumpWaterToAir_Impl>()->setSupplyAirFanObjectType(supplyAirFanObjectType);
  }

  std::string AirLoopHVACUnitaryHeatPumpWaterToAir::heatingCoilObjectType() const {
    return getImpl<detail::AirLoopHVACUnitaryHeatPumpWaterToAir_Impl>()->heatingCoilObjectType();
  }

  bool AirLoopHVACUnitaryHeatPumpWaterToAir::setHeatingCoilObjectType(const std::string& heatingCoilObjectType) {
    return getImpl<detail::AirLoopHVACUnitaryHeatPumpWaterToAir_Impl>()->setHeatingCoilObjectType(heatingCoilObjectType);
  }

  double AirLoopHVACUnitaryHeatPumpWaterToAir::heatingConvergence() const {
    return getImpl<detail::AirLoopHVACUnitaryHeatPumpWaterToAir_Impl>()->heatingConvergence();
  }

  bool AirLoopHVACUnitaryHeatPumpWaterToAir::isHeatingConvergenceDefaulted() const {
    return getImpl<detail::AirLoopHVACUnitaryHeatPumpWaterToAir_Impl>()->isHeatingConvergenceDefaulted();
  }

  bool AirLoopHVACUnitaryHeatPumpWaterToAir::setHeatingConvergence(double heatingConvergence) {
    return getImpl<detail::AirLoopHVACUnitaryHeatPumpWaterToAir_Impl>()->setHeatingConvergence(heatingConvergence);
  }

  void AirLoopHVACUnitaryHeatPumpWaterToAir::resetHeatingConvergence() {
    getImpl<detail::AirLoopHVACUnitaryHeatPumpWaterToAir_Impl>()->resetHeatingConvergence();
  }

  std::string AirLoopHVACUnitaryHeatPumpWaterToAir::coolingCoilObjectType() const {
    return getImpl<detail::AirLoopHVACUnitaryHeatPumpWaterToAir_Impl>()->coolingCoilObjectType();
  }

  bool AirLoopHVACUnitaryHeatPumpWaterToAir::setCoolingCoilObjectType(const std::string& coolingCoilObjectType) {
    return getImpl<detail::AirLoopHVACUnitaryHeatPumpWaterToAir_Impl>()->setCoolingCoilObjectType(coolingCoilObjectType);
  }

  double AirLoopHVACUnitaryHeatPumpWaterToAir::coolingConvergence() const {
    return getImpl<detail::AirLoopHVACUnitaryHeatPumpWaterToAir_Impl>()->coolingConvergence();
  }

  bool AirLoopHVACUnitaryHeatPumpWaterToAir::isCoolingConvergenceDefaulted() const {
    return getImpl<detail::AirLoopHVACUnitaryHeatPumpWaterToAir_Impl>()->isCoolingConvergenceDefaulted();
  }

  bool AirLoopHVACUnitaryHeatPumpWaterToAir::setCoolingConvergence(double coolingConvergence) {
    return getImpl<detail::AirLoopHVACUnitaryHeatPumpWaterToAir_Impl>()->setCoolingConvergence(coolingConvergence);
  }

  void AirLoopHVACUnitaryHeatPumpWaterToAir::resetCoolingConvergence() {
    getImpl<detail::AirLoopHVACUnitaryHeatPumpWaterToAir_Impl>()->resetCoolingConvergence();
  }

  std::string AirLoopHVACUnitaryHeatPumpWaterToAir::supplementalHeatingCoilObjectType() const {
    return getImpl<detail::AirLoopHVACUnitaryHeatPumpWaterToAir_Impl>()->supplementalHeatingCoilObjectType();
  }

  bool AirLoopHVACUnitaryHeatPumpWaterToAir::setSupplementalHeatingCoilObjectType(const std::string& supplementalHeatingCoilObjectType) {
    return getImpl<detail::AirLoopHVACUnitaryHeatPumpWaterToAir_Impl>()->setSupplementalHeatingCoilObjectType(supplementalHeatingCoilObjectType);
  }

  boost::optional<double> AirLoopHVACUnitaryHeatPumpWaterToAir::maximumSupplyAirTemperaturefromSupplementalHeater() const {
    return getImpl<detail::AirLoopHVACUnitaryHeatPumpWaterToAir_Impl>()->maximumSupplyAirTemperaturefromSupplementalHeater();
  }

  bool AirLoopHVACUnitaryHeatPumpWaterToAir::isMaximumSupplyAirTemperaturefromSupplementalHeaterAutosized() const {
    return getImpl<detail::AirLoopHVACUnitaryHeatPumpWaterToAir_Impl>()->isMaximumSupplyAirTemperaturefromSupplementalHeaterAutosized();
  }

  bool AirLoopHVACUnitaryHeatPumpWaterToAir::setMaximumSupplyAirTemperaturefromSupplementalHeater(
    double maximumSupplyAirTemperaturefromSupplementalHeater) {
    return getImpl<detail::AirLoopHVACUnitaryHeatPumpWaterToAir_Impl>()->setMaximumSupplyAirTemperaturefromSupplementalHeater(
      maximumSupplyAirTemperaturefromSupplementalHeater);
  }

  void AirLoopHVACUnitaryHeatPumpWaterToAir::autosizeMaximumSupplyAirTemperaturefromSupplementalHeater() {
    getImpl<detail::AirLoopHVACUnitaryHeatPumpWaterToAir_Impl>()->autosizeMaximumSupplyAirTemperaturefromSupplementalHeater();
  }

  double AirLoopHVACUnitaryHeatPumpWaterToAir::maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation() const {
    return getImpl<detail::AirLoopHVACUnitaryHeatPumpWaterToAir_Impl>()->maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation();
  }

  bool AirLoopHVACUnitaryHeatPumpWaterToAir::isMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperationDefaulted() const {
    return getImpl<detail::AirLoopHVACUnitaryHeatPumpWaterToAir_Impl>()->isMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperationDefaulted();
  }

  bool AirLoopHVACUnitaryHeatPumpWaterToAir::setMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation(
    double maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation) {
    return getImpl<detail::AirLoopHVACUnitaryHeatPumpWaterToAir_Impl>()->setMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation(
      maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation);
  }

  void AirLoopHVACUnitaryHeatPumpWaterToAir::resetMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation() {
    getImpl<detail::AirLoopHVACUnitaryHeatPumpWaterToAir_Impl>()->resetMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation();
  }

  std::string AirLoopHVACUnitaryHeatPumpWaterToAir::fanPlacement() const {
    return getImpl<detail::AirLoopHVACUnitaryHeatPumpWaterToAir_Impl>()->fanPlacement();
  }

  bool AirLoopHVACUnitaryHeatPumpWaterToAir::isFanPlacementDefaulted() const {
    return getImpl<detail::AirLoopHVACUnitaryHeatPumpWaterToAir_Impl>()->isFanPlacementDefaulted();
  }

  bool AirLoopHVACUnitaryHeatPumpWaterToAir::setFanPlacement(const std::string& fanPlacement) {
    return getImpl<detail::AirLoopHVACUnitaryHeatPumpWaterToAir_Impl>()->setFanPlacement(fanPlacement);
  }

  void AirLoopHVACUnitaryHeatPumpWaterToAir::resetFanPlacement() {
    getImpl<detail::AirLoopHVACUnitaryHeatPumpWaterToAir_Impl>()->resetFanPlacement();
  }

  std::string AirLoopHVACUnitaryHeatPumpWaterToAir::dehumidificationControlType() const {
    return getImpl<detail::AirLoopHVACUnitaryHeatPumpWaterToAir_Impl>()->dehumidificationControlType();
  }

  bool AirLoopHVACUnitaryHeatPumpWaterToAir::isDehumidificationControlTypeDefaulted() const {
    return getImpl<detail::AirLoopHVACUnitaryHeatPumpWaterToAir_Impl>()->isDehumidificationControlTypeDefaulted();
  }

  bool AirLoopHVACUnitaryHeatPumpWaterToAir::setDehumidificationControlType(const std::string& dehumidificationControlType) {
    return getImpl<detail::AirLoopHVACUnitaryHeatPumpWaterToAir_Impl>()->setDehumidificationControlType(dehumidificationControlType);
  }

  void AirLoopHVACUnitaryHeatPumpWaterToAir::resetDehumidificationControlType() {
    getImpl<detail::AirLoopHVACUnitaryHeatPumpWaterToAir_Impl>()->resetDehumidificationControlType();
  }

  std::string AirLoopHVACUnitaryHeatPumpWaterToAir::heatPumpCoilWaterFlowMode() const {
    return getImpl<detail::AirLoopHVACUnitaryHeatPumpWaterToAir_Impl>()->heatPumpCoilWaterFlowMode();
  }

  bool AirLoopHVACUnitaryHeatPumpWaterToAir::isHeatPumpCoilWaterFlowModeDefaulted() const {
    return getImpl<detail::AirLoopHVACUnitaryHeatPumpWaterToAir_Impl>()->isHeatPumpCoilWaterFlowModeDefaulted();
  }

  bool AirLoopHVACUnitaryHeatPumpWaterToAir::setHeatPumpCoilWaterFlowMode(const std::string& heatPumpCoilWaterFlowMode) {
    return getImpl<detail::AirLoopHVACUnitaryHeatPumpWaterToAir_Impl>()->setHeatPumpCoilWaterFlowMode(heatPumpCoilWaterFlowMode);
  }

  void AirLoopHVACUnitaryHeatPumpWaterToAir::resetHeatPumpCoilWaterFlowMode() {
    getImpl<detail::AirLoopHVACUnitaryHeatPumpWaterToAir_Impl>()->resetHeatPumpCoilWaterFlowMode();
  }

  double AirLoopHVACUnitaryHeatPumpWaterToAir::dXHeatingCoilSizingRatio() const {
    return getImpl<detail::AirLoopHVACUnitaryHeatPumpWaterToAir_Impl>()->dXHeatingCoilSizingRatio();
  }

  bool AirLoopHVACUnitaryHeatPumpWaterToAir::isDXHeatingCoilSizingRatioDefaulted() const {
    return getImpl<detail::AirLoopHVACUnitaryHeatPumpWaterToAir_Impl>()->isDXHeatingCoilSizingRatioDefaulted();
  }

  bool AirLoopHVACUnitaryHeatPumpWaterToAir::setDXHeatingCoilSizingRatio(double dXHeatingCoilSizingRatio) {
    return getImpl<detail::AirLoopHVACUnitaryHeatPumpWaterToAir_Impl>()->setDXHeatingCoilSizingRatio(dXHeatingCoilSizingRatio);
  }

  void AirLoopHVACUnitaryHeatPumpWaterToAir::resetDXHeatingCoilSizingRatio() {
    getImpl<detail::AirLoopHVACUnitaryHeatPumpWaterToAir_Impl>()->resetDXHeatingCoilSizingRatio();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    boost::optional<double> AirLoopHVACUnitaryHeatPumpWaterToAir_Impl::supplyAirFlowRate() const {
      return getDouble(openstudio::AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::SupplyAirFlowRate, true);
    }

    bool AirLoopHVACUnitaryHeatPumpWaterToAir_Impl::isSupplyAirFlowRateAutosized() const {
      if (auto value = getString(openstudio::AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::SupplyAirFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool AirLoopHVACUnitaryHeatPumpWaterToAir_Impl::setSupplyAirFlowRate(double supplyAirFlowRate) {
      return setDouble(openstudio::AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::SupplyAirFlowRate, supplyAirFlowRate);
    }

    void AirLoopHVACUnitaryHeatPumpWaterToAir_Impl::autosizeSupplyAirFlowRate() {
      OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::SupplyAirFlowRate, "autosize"));
    }

    std::string AirLoopHVACUnitaryHeatPumpWaterToAir_Impl::supplyAirFanObjectType() const {
      const auto value = getString(openstudio::AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::SupplyAirFanObjectType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirLoopHVACUnitaryHeatPumpWaterToAir_Impl::setSupplyAirFanObjectType(const std::string& supplyAirFanObjectType) {
      return setString(openstudio::AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::SupplyAirFanObjectType, supplyAirFanObjectType);
    }

    std::string AirLoopHVACUnitaryHeatPumpWaterToAir_Impl::heatingCoilObjectType() const {
      const auto value = getString(openstudio::AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::HeatingCoilObjectType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirLoopHVACUnitaryHeatPumpWaterToAir_Impl::setHeatingCoilObjectType(const std::string& heatingCoilObjectType) {
      return setString(openstudio::AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::HeatingCoilObjectType, heatingCoilObjectType);
    }

    double AirLoopHVACUnitaryHeatPumpWaterToAir_Impl::heatingConvergence() const {
      const auto value = getDouble(openstudio::AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::HeatingConvergence, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirLoopHVACUnitaryHeatPumpWaterToAir_Impl::isHeatingConvergenceDefaulted() const {
      return isEmpty(openstudio::AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::HeatingConvergence);
    }

    bool AirLoopHVACUnitaryHeatPumpWaterToAir_Impl::setHeatingConvergence(double heatingConvergence) {
      return setDouble(openstudio::AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::HeatingConvergence, heatingConvergence);
    }

    void AirLoopHVACUnitaryHeatPumpWaterToAir_Impl::resetHeatingConvergence() {
      OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::HeatingConvergence, ""));
    }

    std::string AirLoopHVACUnitaryHeatPumpWaterToAir_Impl::coolingCoilObjectType() const {
      const auto value = getString(openstudio::AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::CoolingCoilObjectType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirLoopHVACUnitaryHeatPumpWaterToAir_Impl::setCoolingCoilObjectType(const std::string& coolingCoilObjectType) {
      return setString(openstudio::AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::CoolingCoilObjectType, coolingCoilObjectType);
    }

    double AirLoopHVACUnitaryHeatPumpWaterToAir_Impl::coolingConvergence() const {
      const auto value = getDouble(openstudio::AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::CoolingConvergence, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirLoopHVACUnitaryHeatPumpWaterToAir_Impl::isCoolingConvergenceDefaulted() const {
      return isEmpty(openstudio::AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::CoolingConvergence);
    }

    bool AirLoopHVACUnitaryHeatPumpWaterToAir_Impl::setCoolingConvergence(double coolingConvergence) {
      return setDouble(openstudio::AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::CoolingConvergence, coolingConvergence);
    }

    void AirLoopHVACUnitaryHeatPumpWaterToAir_Impl::resetCoolingConvergence() {
      OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::CoolingConvergence, ""));
    }

    std::string AirLoopHVACUnitaryHeatPumpWaterToAir_Impl::supplementalHeatingCoilObjectType() const {
      const auto value = getString(openstudio::AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::SupplementalHeatingCoilObjectType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirLoopHVACUnitaryHeatPumpWaterToAir_Impl::setSupplementalHeatingCoilObjectType(const std::string& supplementalHeatingCoilObjectType) {
      return setString(openstudio::AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::SupplementalHeatingCoilObjectType,
                       supplementalHeatingCoilObjectType);
    }

    boost::optional<double> AirLoopHVACUnitaryHeatPumpWaterToAir_Impl::maximumSupplyAirTemperaturefromSupplementalHeater() const {
      return getDouble(openstudio::AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::MaximumSupplyAirTemperaturefromSupplementalHeater, true);
    }

    bool AirLoopHVACUnitaryHeatPumpWaterToAir_Impl::isMaximumSupplyAirTemperaturefromSupplementalHeaterAutosized() const {
      if (auto value = getString(openstudio::AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::MaximumSupplyAirTemperaturefromSupplementalHeater, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool AirLoopHVACUnitaryHeatPumpWaterToAir_Impl::setMaximumSupplyAirTemperaturefromSupplementalHeater(
      double maximumSupplyAirTemperaturefromSupplementalHeater) {
      const bool result = setDouble(openstudio::AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::MaximumSupplyAirTemperaturefromSupplementalHeater,
                                    maximumSupplyAirTemperaturefromSupplementalHeater);
      OS_ASSERT(result);
      return result;
    }

    void AirLoopHVACUnitaryHeatPumpWaterToAir_Impl::autosizeMaximumSupplyAirTemperaturefromSupplementalHeater() {
      OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::MaximumSupplyAirTemperaturefromSupplementalHeater, "autosize"));
    }

    double AirLoopHVACUnitaryHeatPumpWaterToAir_Impl::maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation() const {
      const auto value =
        getDouble(openstudio::AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::MaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirLoopHVACUnitaryHeatPumpWaterToAir_Impl::isMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperationDefaulted() const {
      return isEmpty(openstudio::AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::MaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation);
    }

    bool AirLoopHVACUnitaryHeatPumpWaterToAir_Impl::setMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation(
      double maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation) {
      return setDouble(openstudio::AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::MaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation,
                       maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation);
    }

    void AirLoopHVACUnitaryHeatPumpWaterToAir_Impl::resetMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation() {
      OS_ASSERT(
        setString(openstudio::AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::MaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation, ""));
    }

    std::string AirLoopHVACUnitaryHeatPumpWaterToAir_Impl::fanPlacement() const {
      const auto value = getString(openstudio::AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::FanPlacement, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirLoopHVACUnitaryHeatPumpWaterToAir_Impl::isFanPlacementDefaulted() const {
      return isEmpty(openstudio::AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::FanPlacement);
    }

    bool AirLoopHVACUnitaryHeatPumpWaterToAir_Impl::setFanPlacement(const std::string& fanPlacement) {
      return setString(openstudio::AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::FanPlacement, fanPlacement);
    }

    void AirLoopHVACUnitaryHeatPumpWaterToAir_Impl::resetFanPlacement() {
      OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::FanPlacement, ""));
    }

    std::string AirLoopHVACUnitaryHeatPumpWaterToAir_Impl::dehumidificationControlType() const {
      const auto value = getString(openstudio::AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::DehumidificationControlType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirLoopHVACUnitaryHeatPumpWaterToAir_Impl::isDehumidificationControlTypeDefaulted() const {
      return isEmpty(openstudio::AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::DehumidificationControlType);
    }

    bool AirLoopHVACUnitaryHeatPumpWaterToAir_Impl::setDehumidificationControlType(const std::string& dehumidificationControlType) {
      return setString(openstudio::AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::DehumidificationControlType, dehumidificationControlType);
    }

    void AirLoopHVACUnitaryHeatPumpWaterToAir_Impl::resetDehumidificationControlType() {
      OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::DehumidificationControlType, ""));
    }

    std::string AirLoopHVACUnitaryHeatPumpWaterToAir_Impl::heatPumpCoilWaterFlowMode() const {
      const auto value = getString(openstudio::AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::HeatPumpCoilWaterFlowMode, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirLoopHVACUnitaryHeatPumpWaterToAir_Impl::isHeatPumpCoilWaterFlowModeDefaulted() const {
      return isEmpty(openstudio::AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::HeatPumpCoilWaterFlowMode);
    }

    bool AirLoopHVACUnitaryHeatPumpWaterToAir_Impl::setHeatPumpCoilWaterFlowMode(const std::string& heatPumpCoilWaterFlowMode) {
      return setString(openstudio::AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::HeatPumpCoilWaterFlowMode, heatPumpCoilWaterFlowMode);
    }

    void AirLoopHVACUnitaryHeatPumpWaterToAir_Impl::resetHeatPumpCoilWaterFlowMode() {
      OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::HeatPumpCoilWaterFlowMode, ""));
    }

    double AirLoopHVACUnitaryHeatPumpWaterToAir_Impl::dXHeatingCoilSizingRatio() const {
      const auto value = getDouble(openstudio::AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::DXHeatingCoilSizingRatio, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirLoopHVACUnitaryHeatPumpWaterToAir_Impl::isDXHeatingCoilSizingRatioDefaulted() const {
      return isEmpty(openstudio::AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::DXHeatingCoilSizingRatio);
    }

    bool AirLoopHVACUnitaryHeatPumpWaterToAir_Impl::setDXHeatingCoilSizingRatio(double dXHeatingCoilSizingRatio) {
      return setDouble(openstudio::AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::DXHeatingCoilSizingRatio, dXHeatingCoilSizingRatio);
    }

    void AirLoopHVACUnitaryHeatPumpWaterToAir_Impl::resetDXHeatingCoilSizingRatio() {
      OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::DXHeatingCoilSizingRatio, ""));
    }

    std::vector<std::string> AirLoopHVACUnitaryHeatPumpWaterToAir_Impl::supplyAirFanObjectTypeValues() const {
      return openstudio::epmodel::AirLoopHVACUnitaryHeatPumpWaterToAir::supplyAirFanObjectTypeValues();
    }

    std::vector<std::string> AirLoopHVACUnitaryHeatPumpWaterToAir_Impl::heatingCoilObjectTypeValues() const {
      return openstudio::epmodel::AirLoopHVACUnitaryHeatPumpWaterToAir::heatingCoilObjectTypeValues();
    }

    std::vector<std::string> AirLoopHVACUnitaryHeatPumpWaterToAir_Impl::coolingCoilObjectTypeValues() const {
      return openstudio::epmodel::AirLoopHVACUnitaryHeatPumpWaterToAir::coolingCoilObjectTypeValues();
    }

    std::vector<std::string> AirLoopHVACUnitaryHeatPumpWaterToAir_Impl::supplementalHeatingCoilObjectTypeValues() const {
      return openstudio::epmodel::AirLoopHVACUnitaryHeatPumpWaterToAir::supplementalHeatingCoilObjectTypeValues();
    }

    std::vector<std::string> AirLoopHVACUnitaryHeatPumpWaterToAir_Impl::fanPlacementValues() const {
      return openstudio::epmodel::AirLoopHVACUnitaryHeatPumpWaterToAir::fanPlacementValues();
    }

    std::vector<std::string> AirLoopHVACUnitaryHeatPumpWaterToAir_Impl::dehumidificationControlTypeValues() const {
      return openstudio::epmodel::AirLoopHVACUnitaryHeatPumpWaterToAir::dehumidificationControlTypeValues();
    }

    std::vector<std::string> AirLoopHVACUnitaryHeatPumpWaterToAir_Impl::heatPumpCoilWaterFlowModeValues() const {
      return openstudio::epmodel::AirLoopHVACUnitaryHeatPumpWaterToAir::heatPumpCoilWaterFlowModeValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
