/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "GeneratorFuelCellPowerModule.hpp"
#include "GeneratorFuelCellPowerModule_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/Generator_FuelCell_PowerModule_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

  GeneratorFuelCellPowerModule::GeneratorFuelCellPowerModule(const Model& model)
    : ModelObject(GeneratorFuelCellPowerModule::iddObjectType(), model) {}

  GeneratorFuelCellPowerModule::GeneratorFuelCellPowerModule(std::shared_ptr<detail::GeneratorFuelCellPowerModule_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType GeneratorFuelCellPowerModule::iddObjectType() {
    return IddObjectType::Generator_FuelCell_PowerModule;
  }

  std::vector<std::string> GeneratorFuelCellPowerModule::efficiencyCurveModeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::Generator_FuelCell_PowerModuleFields::EfficiencyCurveMode);
  }

  std::vector<std::string> GeneratorFuelCellPowerModule::skinLossCalculationModeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::Generator_FuelCell_PowerModuleFields::SkinLossCalculationMode);
  }

  std::string GeneratorFuelCellPowerModule::efficiencyCurveMode() const {
    return getImpl<detail::GeneratorFuelCellPowerModule_Impl>()->efficiencyCurveMode();
  }

  bool GeneratorFuelCellPowerModule::setEfficiencyCurveMode(const std::string& efficiencyCurveMode) {
    return getImpl<detail::GeneratorFuelCellPowerModule_Impl>()->setEfficiencyCurveMode(efficiencyCurveMode);
  }

  void GeneratorFuelCellPowerModule::resetEfficiencyCurveMode() {
    getImpl<detail::GeneratorFuelCellPowerModule_Impl>()->resetEfficiencyCurveMode();
  }

  double GeneratorFuelCellPowerModule::nominalEfficiency() const {
    return getImpl<detail::GeneratorFuelCellPowerModule_Impl>()->nominalEfficiency();
  }

  bool GeneratorFuelCellPowerModule::setNominalEfficiency(double nominalEfficiency) {
    return getImpl<detail::GeneratorFuelCellPowerModule_Impl>()->setNominalEfficiency(nominalEfficiency);
  }

  void GeneratorFuelCellPowerModule::resetNominalEfficiency() {
    getImpl<detail::GeneratorFuelCellPowerModule_Impl>()->resetNominalEfficiency();
  }

  double GeneratorFuelCellPowerModule::nominalElectricalPower() const {
    return getImpl<detail::GeneratorFuelCellPowerModule_Impl>()->nominalElectricalPower();
  }

  bool GeneratorFuelCellPowerModule::setNominalElectricalPower(double nominalElectricalPower) {
    return getImpl<detail::GeneratorFuelCellPowerModule_Impl>()->setNominalElectricalPower(nominalElectricalPower);
  }

  void GeneratorFuelCellPowerModule::resetNominalElectricalPower() {
    getImpl<detail::GeneratorFuelCellPowerModule_Impl>()->resetNominalElectricalPower();
  }

  double GeneratorFuelCellPowerModule::numberofStopsatStartofSimulation() const {
    return getImpl<detail::GeneratorFuelCellPowerModule_Impl>()->numberofStopsatStartofSimulation();
  }

  bool GeneratorFuelCellPowerModule::setNumberofStopsatStartofSimulation(double numberofStopsatStartofSimulation) {
    return getImpl<detail::GeneratorFuelCellPowerModule_Impl>()->setNumberofStopsatStartofSimulation(numberofStopsatStartofSimulation);
  }

  void GeneratorFuelCellPowerModule::resetNumberofStopsatStartofSimulation() {
    getImpl<detail::GeneratorFuelCellPowerModule_Impl>()->resetNumberofStopsatStartofSimulation();
  }

  double GeneratorFuelCellPowerModule::cyclingPerformanceDegradationCoefficient() const {
    return getImpl<detail::GeneratorFuelCellPowerModule_Impl>()->cyclingPerformanceDegradationCoefficient();
  }

  bool GeneratorFuelCellPowerModule::setCyclingPerformanceDegradationCoefficient(double cyclingPerformanceDegradationCoefficient) {
    return getImpl<detail::GeneratorFuelCellPowerModule_Impl>()->setCyclingPerformanceDegradationCoefficient(
      cyclingPerformanceDegradationCoefficient);
  }

  void GeneratorFuelCellPowerModule::resetCyclingPerformanceDegradationCoefficient() {
    getImpl<detail::GeneratorFuelCellPowerModule_Impl>()->resetCyclingPerformanceDegradationCoefficient();
  }

  double GeneratorFuelCellPowerModule::numberofRunHoursatBeginningofSimulation() const {
    return getImpl<detail::GeneratorFuelCellPowerModule_Impl>()->numberofRunHoursatBeginningofSimulation();
  }

  bool GeneratorFuelCellPowerModule::setNumberofRunHoursatBeginningofSimulation(double numberofRunHoursatBeginningofSimulation) {
    return getImpl<detail::GeneratorFuelCellPowerModule_Impl>()->setNumberofRunHoursatBeginningofSimulation(numberofRunHoursatBeginningofSimulation);
  }

  void GeneratorFuelCellPowerModule::resetNumberofRunHoursatBeginningofSimulation() {
    getImpl<detail::GeneratorFuelCellPowerModule_Impl>()->resetNumberofRunHoursatBeginningofSimulation();
  }

  double GeneratorFuelCellPowerModule::accumulatedRunTimeDegradationCoefficient() const {
    return getImpl<detail::GeneratorFuelCellPowerModule_Impl>()->accumulatedRunTimeDegradationCoefficient();
  }

  bool GeneratorFuelCellPowerModule::setAccumulatedRunTimeDegradationCoefficient(double accumulatedRunTimeDegradationCoefficient) {
    return getImpl<detail::GeneratorFuelCellPowerModule_Impl>()->setAccumulatedRunTimeDegradationCoefficient(
      accumulatedRunTimeDegradationCoefficient);
  }

  void GeneratorFuelCellPowerModule::resetAccumulatedRunTimeDegradationCoefficient() {
    getImpl<detail::GeneratorFuelCellPowerModule_Impl>()->resetAccumulatedRunTimeDegradationCoefficient();
  }

  double GeneratorFuelCellPowerModule::runTimeDegradationInitiationTimeThreshold() const {
    return getImpl<detail::GeneratorFuelCellPowerModule_Impl>()->runTimeDegradationInitiationTimeThreshold();
  }

  bool GeneratorFuelCellPowerModule::setRunTimeDegradationInitiationTimeThreshold(double runTimeDegradationInitiationTimeThreshold) {
    return getImpl<detail::GeneratorFuelCellPowerModule_Impl>()->setRunTimeDegradationInitiationTimeThreshold(
      runTimeDegradationInitiationTimeThreshold);
  }

  void GeneratorFuelCellPowerModule::resetRunTimeDegradationInitiationTimeThreshold() {
    getImpl<detail::GeneratorFuelCellPowerModule_Impl>()->resetRunTimeDegradationInitiationTimeThreshold();
  }

  double GeneratorFuelCellPowerModule::powerUpTransientLimit() const {
    return getImpl<detail::GeneratorFuelCellPowerModule_Impl>()->powerUpTransientLimit();
  }

  bool GeneratorFuelCellPowerModule::setPowerUpTransientLimit(double powerUpTransientLimit) {
    return getImpl<detail::GeneratorFuelCellPowerModule_Impl>()->setPowerUpTransientLimit(powerUpTransientLimit);
  }

  void GeneratorFuelCellPowerModule::resetPowerUpTransientLimit() {
    getImpl<detail::GeneratorFuelCellPowerModule_Impl>()->resetPowerUpTransientLimit();
  }

  double GeneratorFuelCellPowerModule::powerDownTransientLimit() const {
    return getImpl<detail::GeneratorFuelCellPowerModule_Impl>()->powerDownTransientLimit();
  }

  bool GeneratorFuelCellPowerModule::setPowerDownTransientLimit(double powerDownTransientLimit) {
    return getImpl<detail::GeneratorFuelCellPowerModule_Impl>()->setPowerDownTransientLimit(powerDownTransientLimit);
  }

  void GeneratorFuelCellPowerModule::resetPowerDownTransientLimit() {
    getImpl<detail::GeneratorFuelCellPowerModule_Impl>()->resetPowerDownTransientLimit();
  }

  double GeneratorFuelCellPowerModule::startUpTime() const {
    return getImpl<detail::GeneratorFuelCellPowerModule_Impl>()->startUpTime();
  }

  bool GeneratorFuelCellPowerModule::setStartUpTime(double startUpTime) {
    return getImpl<detail::GeneratorFuelCellPowerModule_Impl>()->setStartUpTime(startUpTime);
  }

  void GeneratorFuelCellPowerModule::resetStartUpTime() {
    getImpl<detail::GeneratorFuelCellPowerModule_Impl>()->resetStartUpTime();
  }

  double GeneratorFuelCellPowerModule::startUpFuel() const {
    return getImpl<detail::GeneratorFuelCellPowerModule_Impl>()->startUpFuel();
  }

  bool GeneratorFuelCellPowerModule::setStartUpFuel(double startUpFuel) {
    return getImpl<detail::GeneratorFuelCellPowerModule_Impl>()->setStartUpFuel(startUpFuel);
  }

  void GeneratorFuelCellPowerModule::resetStartUpFuel() {
    getImpl<detail::GeneratorFuelCellPowerModule_Impl>()->resetStartUpFuel();
  }

  double GeneratorFuelCellPowerModule::startUpElectricityConsumption() const {
    return getImpl<detail::GeneratorFuelCellPowerModule_Impl>()->startUpElectricityConsumption();
  }

  bool GeneratorFuelCellPowerModule::setStartUpElectricityConsumption(double startUpElectricityConsumption) {
    return getImpl<detail::GeneratorFuelCellPowerModule_Impl>()->setStartUpElectricityConsumption(startUpElectricityConsumption);
  }

  void GeneratorFuelCellPowerModule::resetStartUpElectricityConsumption() {
    getImpl<detail::GeneratorFuelCellPowerModule_Impl>()->resetStartUpElectricityConsumption();
  }

  double GeneratorFuelCellPowerModule::startUpElectricityProduced() const {
    return getImpl<detail::GeneratorFuelCellPowerModule_Impl>()->startUpElectricityProduced();
  }

  bool GeneratorFuelCellPowerModule::setStartUpElectricityProduced(double startUpElectricityProduced) {
    return getImpl<detail::GeneratorFuelCellPowerModule_Impl>()->setStartUpElectricityProduced(startUpElectricityProduced);
  }

  void GeneratorFuelCellPowerModule::resetStartUpElectricityProduced() {
    getImpl<detail::GeneratorFuelCellPowerModule_Impl>()->resetStartUpElectricityProduced();
  }

  double GeneratorFuelCellPowerModule::shutDownTime() const {
    return getImpl<detail::GeneratorFuelCellPowerModule_Impl>()->shutDownTime();
  }

  bool GeneratorFuelCellPowerModule::setShutDownTime(double shutDownTime) {
    return getImpl<detail::GeneratorFuelCellPowerModule_Impl>()->setShutDownTime(shutDownTime);
  }

  void GeneratorFuelCellPowerModule::resetShutDownTime() {
    getImpl<detail::GeneratorFuelCellPowerModule_Impl>()->resetShutDownTime();
  }

  double GeneratorFuelCellPowerModule::shutDownFuel() const {
    return getImpl<detail::GeneratorFuelCellPowerModule_Impl>()->shutDownFuel();
  }

  bool GeneratorFuelCellPowerModule::setShutDownFuel(double shutDownFuel) {
    return getImpl<detail::GeneratorFuelCellPowerModule_Impl>()->setShutDownFuel(shutDownFuel);
  }

  void GeneratorFuelCellPowerModule::resetShutDownFuel() {
    getImpl<detail::GeneratorFuelCellPowerModule_Impl>()->resetShutDownFuel();
  }

  double GeneratorFuelCellPowerModule::shutDownElectricityConsumption() const {
    return getImpl<detail::GeneratorFuelCellPowerModule_Impl>()->shutDownElectricityConsumption();
  }

  bool GeneratorFuelCellPowerModule::setShutDownElectricityConsumption(double shutDownElectricityConsumption) {
    return getImpl<detail::GeneratorFuelCellPowerModule_Impl>()->setShutDownElectricityConsumption(shutDownElectricityConsumption);
  }

  void GeneratorFuelCellPowerModule::resetShutDownElectricityConsumption() {
    getImpl<detail::GeneratorFuelCellPowerModule_Impl>()->resetShutDownElectricityConsumption();
  }

  double GeneratorFuelCellPowerModule::ancillaryElectricityConstantTerm() const {
    return getImpl<detail::GeneratorFuelCellPowerModule_Impl>()->ancillaryElectricityConstantTerm();
  }

  bool GeneratorFuelCellPowerModule::setAncillaryElectricityConstantTerm(double ancillaryElectricityConstantTerm) {
    return getImpl<detail::GeneratorFuelCellPowerModule_Impl>()->setAncillaryElectricityConstantTerm(ancillaryElectricityConstantTerm);
  }

  void GeneratorFuelCellPowerModule::resetAncillaryElectricityConstantTerm() {
    getImpl<detail::GeneratorFuelCellPowerModule_Impl>()->resetAncillaryElectricityConstantTerm();
  }

  double GeneratorFuelCellPowerModule::ancillaryElectricityLinearTerm() const {
    return getImpl<detail::GeneratorFuelCellPowerModule_Impl>()->ancillaryElectricityLinearTerm();
  }

  bool GeneratorFuelCellPowerModule::setAncillaryElectricityLinearTerm(double ancillaryElectricityLinearTerm) {
    return getImpl<detail::GeneratorFuelCellPowerModule_Impl>()->setAncillaryElectricityLinearTerm(ancillaryElectricityLinearTerm);
  }

  void GeneratorFuelCellPowerModule::resetAncillaryElectricityLinearTerm() {
    getImpl<detail::GeneratorFuelCellPowerModule_Impl>()->resetAncillaryElectricityLinearTerm();
  }

  std::string GeneratorFuelCellPowerModule::skinLossCalculationMode() const {
    return getImpl<detail::GeneratorFuelCellPowerModule_Impl>()->skinLossCalculationMode();
  }

  bool GeneratorFuelCellPowerModule::setSkinLossCalculationMode(const std::string& skinLossCalculationMode) {
    return getImpl<detail::GeneratorFuelCellPowerModule_Impl>()->setSkinLossCalculationMode(skinLossCalculationMode);
  }

  void GeneratorFuelCellPowerModule::resetSkinLossCalculationMode() {
    getImpl<detail::GeneratorFuelCellPowerModule_Impl>()->resetSkinLossCalculationMode();
  }

  double GeneratorFuelCellPowerModule::skinLossRadiativeFraction() const {
    return getImpl<detail::GeneratorFuelCellPowerModule_Impl>()->skinLossRadiativeFraction();
  }

  bool GeneratorFuelCellPowerModule::setSkinLossRadiativeFraction(double skinLossRadiativeFraction) {
    return getImpl<detail::GeneratorFuelCellPowerModule_Impl>()->setSkinLossRadiativeFraction(skinLossRadiativeFraction);
  }

  void GeneratorFuelCellPowerModule::resetSkinLossRadiativeFraction() {
    getImpl<detail::GeneratorFuelCellPowerModule_Impl>()->resetSkinLossRadiativeFraction();
  }

  double GeneratorFuelCellPowerModule::constantSkinLossRate() const {
    return getImpl<detail::GeneratorFuelCellPowerModule_Impl>()->constantSkinLossRate();
  }

  bool GeneratorFuelCellPowerModule::setConstantSkinLossRate(double constantSkinLossRate) {
    return getImpl<detail::GeneratorFuelCellPowerModule_Impl>()->setConstantSkinLossRate(constantSkinLossRate);
  }

  void GeneratorFuelCellPowerModule::resetConstantSkinLossRate() {
    getImpl<detail::GeneratorFuelCellPowerModule_Impl>()->resetConstantSkinLossRate();
  }

  double GeneratorFuelCellPowerModule::skinLossUFactorTimesAreaTerm() const {
    return getImpl<detail::GeneratorFuelCellPowerModule_Impl>()->skinLossUFactorTimesAreaTerm();
  }

  bool GeneratorFuelCellPowerModule::setSkinLossUFactorTimesAreaTerm(double skinLossUFactorTimesAreaTerm) {
    return getImpl<detail::GeneratorFuelCellPowerModule_Impl>()->setSkinLossUFactorTimesAreaTerm(skinLossUFactorTimesAreaTerm);
  }

  void GeneratorFuelCellPowerModule::resetSkinLossUFactorTimesAreaTerm() {
    getImpl<detail::GeneratorFuelCellPowerModule_Impl>()->resetSkinLossUFactorTimesAreaTerm();
  }

  double GeneratorFuelCellPowerModule::dilutionAirFlowRate() const {
    return getImpl<detail::GeneratorFuelCellPowerModule_Impl>()->dilutionAirFlowRate();
  }

  bool GeneratorFuelCellPowerModule::setDilutionAirFlowRate(double dilutionAirFlowRate) {
    return getImpl<detail::GeneratorFuelCellPowerModule_Impl>()->setDilutionAirFlowRate(dilutionAirFlowRate);
  }

  void GeneratorFuelCellPowerModule::resetDilutionAirFlowRate() {
    getImpl<detail::GeneratorFuelCellPowerModule_Impl>()->resetDilutionAirFlowRate();
  }

  double GeneratorFuelCellPowerModule::stackHeatlosstoDilutionAir() const {
    return getImpl<detail::GeneratorFuelCellPowerModule_Impl>()->stackHeatlosstoDilutionAir();
  }

  bool GeneratorFuelCellPowerModule::setStackHeatlosstoDilutionAir(double stackHeatlosstoDilutionAir) {
    return getImpl<detail::GeneratorFuelCellPowerModule_Impl>()->setStackHeatlosstoDilutionAir(stackHeatlosstoDilutionAir);
  }

  void GeneratorFuelCellPowerModule::resetStackHeatlosstoDilutionAir() {
    getImpl<detail::GeneratorFuelCellPowerModule_Impl>()->resetStackHeatlosstoDilutionAir();
  }

  double GeneratorFuelCellPowerModule::minimumOperatingPoint() const {
    return getImpl<detail::GeneratorFuelCellPowerModule_Impl>()->minimumOperatingPoint();
  }

  bool GeneratorFuelCellPowerModule::setMinimumOperatingPoint(double minimumOperatingPoint) {
    return getImpl<detail::GeneratorFuelCellPowerModule_Impl>()->setMinimumOperatingPoint(minimumOperatingPoint);
  }

  void GeneratorFuelCellPowerModule::resetMinimumOperatingPoint() {
    getImpl<detail::GeneratorFuelCellPowerModule_Impl>()->resetMinimumOperatingPoint();
  }

  double GeneratorFuelCellPowerModule::maximumOperatingPoint() const {
    return getImpl<detail::GeneratorFuelCellPowerModule_Impl>()->maximumOperatingPoint();
  }

  bool GeneratorFuelCellPowerModule::setMaximumOperatingPoint(double maximumOperatingPoint) {
    return getImpl<detail::GeneratorFuelCellPowerModule_Impl>()->setMaximumOperatingPoint(maximumOperatingPoint);
  }

  void GeneratorFuelCellPowerModule::resetMaximumOperatingPoint() {
    getImpl<detail::GeneratorFuelCellPowerModule_Impl>()->resetMaximumOperatingPoint();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::string GeneratorFuelCellPowerModule_Impl::efficiencyCurveMode() const {
      const auto value = getString(openstudio::Generator_FuelCell_PowerModuleFields::EfficiencyCurveMode, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GeneratorFuelCellPowerModule_Impl::setEfficiencyCurveMode(const std::string& efficiencyCurveMode) {
      return setString(openstudio::Generator_FuelCell_PowerModuleFields::EfficiencyCurveMode, efficiencyCurveMode);
    }

    void GeneratorFuelCellPowerModule_Impl::resetEfficiencyCurveMode() {
      OS_ASSERT(setString(openstudio::Generator_FuelCell_PowerModuleFields::EfficiencyCurveMode, "Annex42"));
    }

    double GeneratorFuelCellPowerModule_Impl::nominalEfficiency() const {
      const auto value = getDouble(openstudio::Generator_FuelCell_PowerModuleFields::NominalEfficiency, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GeneratorFuelCellPowerModule_Impl::setNominalEfficiency(double nominalEfficiency) {
      const bool result = setDouble(openstudio::Generator_FuelCell_PowerModuleFields::NominalEfficiency, nominalEfficiency);
      OS_ASSERT(result);
      return result;
    }

    void GeneratorFuelCellPowerModule_Impl::resetNominalEfficiency() {
      OS_ASSERT(setDouble(openstudio::Generator_FuelCell_PowerModuleFields::NominalEfficiency, 1.0));
    }

    double GeneratorFuelCellPowerModule_Impl::nominalElectricalPower() const {
      const auto value = getDouble(openstudio::Generator_FuelCell_PowerModuleFields::NominalElectricalPower, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GeneratorFuelCellPowerModule_Impl::setNominalElectricalPower(double nominalElectricalPower) {
      const bool result = setDouble(openstudio::Generator_FuelCell_PowerModuleFields::NominalElectricalPower, nominalElectricalPower);
      OS_ASSERT(result);
      return result;
    }

    void GeneratorFuelCellPowerModule_Impl::resetNominalElectricalPower() {
      OS_ASSERT(setDouble(openstudio::Generator_FuelCell_PowerModuleFields::NominalElectricalPower, 3400.0));
    }

    double GeneratorFuelCellPowerModule_Impl::numberofStopsatStartofSimulation() const {
      const auto value = getDouble(openstudio::Generator_FuelCell_PowerModuleFields::NumberofStopsatStartofSimulation, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GeneratorFuelCellPowerModule_Impl::setNumberofStopsatStartofSimulation(double numberofStopsatStartofSimulation) {
      const bool result =
        setDouble(openstudio::Generator_FuelCell_PowerModuleFields::NumberofStopsatStartofSimulation, numberofStopsatStartofSimulation);
      OS_ASSERT(result);
      return result;
    }

    void GeneratorFuelCellPowerModule_Impl::resetNumberofStopsatStartofSimulation() {
      OS_ASSERT(setDouble(openstudio::Generator_FuelCell_PowerModuleFields::NumberofStopsatStartofSimulation, 0.0));
    }

    double GeneratorFuelCellPowerModule_Impl::cyclingPerformanceDegradationCoefficient() const {
      const auto value = getDouble(openstudio::Generator_FuelCell_PowerModuleFields::CyclingPerformanceDegradationCoefficient, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GeneratorFuelCellPowerModule_Impl::setCyclingPerformanceDegradationCoefficient(double cyclingPerformanceDegradationCoefficient) {
      const bool result = setDouble(openstudio::Generator_FuelCell_PowerModuleFields::CyclingPerformanceDegradationCoefficient,
                                    cyclingPerformanceDegradationCoefficient);
      OS_ASSERT(result);
      return result;
    }

    void GeneratorFuelCellPowerModule_Impl::resetCyclingPerformanceDegradationCoefficient() {
      OS_ASSERT(setDouble(openstudio::Generator_FuelCell_PowerModuleFields::CyclingPerformanceDegradationCoefficient, 0.0));
    }

    double GeneratorFuelCellPowerModule_Impl::numberofRunHoursatBeginningofSimulation() const {
      const auto value = getDouble(openstudio::Generator_FuelCell_PowerModuleFields::NumberofRunHoursatBeginningofSimulation, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GeneratorFuelCellPowerModule_Impl::setNumberofRunHoursatBeginningofSimulation(double numberofRunHoursatBeginningofSimulation) {
      const bool result =
        setDouble(openstudio::Generator_FuelCell_PowerModuleFields::NumberofRunHoursatBeginningofSimulation, numberofRunHoursatBeginningofSimulation);
      OS_ASSERT(result);
      return result;
    }

    void GeneratorFuelCellPowerModule_Impl::resetNumberofRunHoursatBeginningofSimulation() {
      OS_ASSERT(setDouble(openstudio::Generator_FuelCell_PowerModuleFields::NumberofRunHoursatBeginningofSimulation, 0.0));
    }

    double GeneratorFuelCellPowerModule_Impl::accumulatedRunTimeDegradationCoefficient() const {
      const auto value = getDouble(openstudio::Generator_FuelCell_PowerModuleFields::AccumulatedRunTimeDegradationCoefficient, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GeneratorFuelCellPowerModule_Impl::setAccumulatedRunTimeDegradationCoefficient(double accumulatedRunTimeDegradationCoefficient) {
      const bool result = setDouble(openstudio::Generator_FuelCell_PowerModuleFields::AccumulatedRunTimeDegradationCoefficient,
                                    accumulatedRunTimeDegradationCoefficient);
      OS_ASSERT(result);
      return result;
    }

    void GeneratorFuelCellPowerModule_Impl::resetAccumulatedRunTimeDegradationCoefficient() {
      OS_ASSERT(setDouble(openstudio::Generator_FuelCell_PowerModuleFields::AccumulatedRunTimeDegradationCoefficient, 0.0));
    }

    double GeneratorFuelCellPowerModule_Impl::runTimeDegradationInitiationTimeThreshold() const {
      const auto value = getDouble(openstudio::Generator_FuelCell_PowerModuleFields::RunTimeDegradationInitiationTimeThreshold, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GeneratorFuelCellPowerModule_Impl::setRunTimeDegradationInitiationTimeThreshold(double runTimeDegradationInitiationTimeThreshold) {
      const bool result = setDouble(openstudio::Generator_FuelCell_PowerModuleFields::RunTimeDegradationInitiationTimeThreshold,
                                    runTimeDegradationInitiationTimeThreshold);
      OS_ASSERT(result);
      return result;
    }

    void GeneratorFuelCellPowerModule_Impl::resetRunTimeDegradationInitiationTimeThreshold() {
      OS_ASSERT(setDouble(openstudio::Generator_FuelCell_PowerModuleFields::RunTimeDegradationInitiationTimeThreshold, 10000.0));
    }

    double GeneratorFuelCellPowerModule_Impl::powerUpTransientLimit() const {
      const auto value = getDouble(openstudio::Generator_FuelCell_PowerModuleFields::PowerUpTransientLimit, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GeneratorFuelCellPowerModule_Impl::setPowerUpTransientLimit(double powerUpTransientLimit) {
      const bool result = setDouble(openstudio::Generator_FuelCell_PowerModuleFields::PowerUpTransientLimit, powerUpTransientLimit);
      OS_ASSERT(result);
      return result;
    }

    void GeneratorFuelCellPowerModule_Impl::resetPowerUpTransientLimit() {
      OS_ASSERT(setDouble(openstudio::Generator_FuelCell_PowerModuleFields::PowerUpTransientLimit, 1.4));
    }

    double GeneratorFuelCellPowerModule_Impl::powerDownTransientLimit() const {
      const auto value = getDouble(openstudio::Generator_FuelCell_PowerModuleFields::PowerDownTransientLimit, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GeneratorFuelCellPowerModule_Impl::setPowerDownTransientLimit(double powerDownTransientLimit) {
      const bool result = setDouble(openstudio::Generator_FuelCell_PowerModuleFields::PowerDownTransientLimit, powerDownTransientLimit);
      OS_ASSERT(result);
      return result;
    }

    void GeneratorFuelCellPowerModule_Impl::resetPowerDownTransientLimit() {
      OS_ASSERT(setDouble(openstudio::Generator_FuelCell_PowerModuleFields::PowerDownTransientLimit, 0.2));
    }

    double GeneratorFuelCellPowerModule_Impl::startUpTime() const {
      const auto value = getDouble(openstudio::Generator_FuelCell_PowerModuleFields::StartUpTime, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GeneratorFuelCellPowerModule_Impl::setStartUpTime(double startUpTime) {
      const bool result = setDouble(openstudio::Generator_FuelCell_PowerModuleFields::StartUpTime, startUpTime);
      OS_ASSERT(result);
      return result;
    }

    void GeneratorFuelCellPowerModule_Impl::resetStartUpTime() {
      OS_ASSERT(setDouble(openstudio::Generator_FuelCell_PowerModuleFields::StartUpTime, 0.0));
    }

    double GeneratorFuelCellPowerModule_Impl::startUpFuel() const {
      const auto value = getDouble(openstudio::Generator_FuelCell_PowerModuleFields::StartUpFuel, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GeneratorFuelCellPowerModule_Impl::setStartUpFuel(double startUpFuel) {
      const bool result = setDouble(openstudio::Generator_FuelCell_PowerModuleFields::StartUpFuel, startUpFuel);
      OS_ASSERT(result);
      return result;
    }

    void GeneratorFuelCellPowerModule_Impl::resetStartUpFuel() {
      OS_ASSERT(setDouble(openstudio::Generator_FuelCell_PowerModuleFields::StartUpFuel, 0.0));
    }

    double GeneratorFuelCellPowerModule_Impl::startUpElectricityConsumption() const {
      const auto value = getDouble(openstudio::Generator_FuelCell_PowerModuleFields::StartUpElectricityConsumption, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GeneratorFuelCellPowerModule_Impl::setStartUpElectricityConsumption(double startUpElectricityConsumption) {
      const bool result = setDouble(openstudio::Generator_FuelCell_PowerModuleFields::StartUpElectricityConsumption, startUpElectricityConsumption);
      OS_ASSERT(result);
      return result;
    }

    void GeneratorFuelCellPowerModule_Impl::resetStartUpElectricityConsumption() {
      OS_ASSERT(setDouble(openstudio::Generator_FuelCell_PowerModuleFields::StartUpElectricityConsumption, 0.0));
    }

    double GeneratorFuelCellPowerModule_Impl::startUpElectricityProduced() const {
      const auto value = getDouble(openstudio::Generator_FuelCell_PowerModuleFields::StartUpElectricityProduced, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GeneratorFuelCellPowerModule_Impl::setStartUpElectricityProduced(double startUpElectricityProduced) {
      const bool result = setDouble(openstudio::Generator_FuelCell_PowerModuleFields::StartUpElectricityProduced, startUpElectricityProduced);
      OS_ASSERT(result);
      return result;
    }

    void GeneratorFuelCellPowerModule_Impl::resetStartUpElectricityProduced() {
      OS_ASSERT(setDouble(openstudio::Generator_FuelCell_PowerModuleFields::StartUpElectricityProduced, 0.0));
    }

    double GeneratorFuelCellPowerModule_Impl::shutDownTime() const {
      const auto value = getDouble(openstudio::Generator_FuelCell_PowerModuleFields::ShutDownTime, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GeneratorFuelCellPowerModule_Impl::setShutDownTime(double shutDownTime) {
      const bool result = setDouble(openstudio::Generator_FuelCell_PowerModuleFields::ShutDownTime, shutDownTime);
      OS_ASSERT(result);
      return result;
    }

    void GeneratorFuelCellPowerModule_Impl::resetShutDownTime() {
      OS_ASSERT(setDouble(openstudio::Generator_FuelCell_PowerModuleFields::ShutDownTime, 0.0));
    }

    double GeneratorFuelCellPowerModule_Impl::shutDownFuel() const {
      const auto value = getDouble(openstudio::Generator_FuelCell_PowerModuleFields::ShutDownFuel, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GeneratorFuelCellPowerModule_Impl::setShutDownFuel(double shutDownFuel) {
      const bool result = setDouble(openstudio::Generator_FuelCell_PowerModuleFields::ShutDownFuel, shutDownFuel);
      OS_ASSERT(result);
      return result;
    }

    void GeneratorFuelCellPowerModule_Impl::resetShutDownFuel() {
      OS_ASSERT(setDouble(openstudio::Generator_FuelCell_PowerModuleFields::ShutDownFuel, 0.0));
    }

    double GeneratorFuelCellPowerModule_Impl::shutDownElectricityConsumption() const {
      const auto value = getDouble(openstudio::Generator_FuelCell_PowerModuleFields::ShutDownElectricityConsumption, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GeneratorFuelCellPowerModule_Impl::setShutDownElectricityConsumption(double shutDownElectricityConsumption) {
      const bool result = setDouble(openstudio::Generator_FuelCell_PowerModuleFields::ShutDownElectricityConsumption, shutDownElectricityConsumption);
      OS_ASSERT(result);
      return result;
    }

    void GeneratorFuelCellPowerModule_Impl::resetShutDownElectricityConsumption() {
      OS_ASSERT(setDouble(openstudio::Generator_FuelCell_PowerModuleFields::ShutDownElectricityConsumption, 0.0));
    }

    double GeneratorFuelCellPowerModule_Impl::ancillaryElectricityConstantTerm() const {
      const auto value = getDouble(openstudio::Generator_FuelCell_PowerModuleFields::AncillaryElectricityConstantTerm, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GeneratorFuelCellPowerModule_Impl::setAncillaryElectricityConstantTerm(double ancillaryElectricityConstantTerm) {
      const bool result =
        setDouble(openstudio::Generator_FuelCell_PowerModuleFields::AncillaryElectricityConstantTerm, ancillaryElectricityConstantTerm);
      OS_ASSERT(result);
      return result;
    }

    void GeneratorFuelCellPowerModule_Impl::resetAncillaryElectricityConstantTerm() {
      OS_ASSERT(setDouble(openstudio::Generator_FuelCell_PowerModuleFields::AncillaryElectricityConstantTerm, 0.0));
    }

    double GeneratorFuelCellPowerModule_Impl::ancillaryElectricityLinearTerm() const {
      const auto value = getDouble(openstudio::Generator_FuelCell_PowerModuleFields::AncillaryElectricityLinearTerm, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GeneratorFuelCellPowerModule_Impl::setAncillaryElectricityLinearTerm(double ancillaryElectricityLinearTerm) {
      const bool result = setDouble(openstudio::Generator_FuelCell_PowerModuleFields::AncillaryElectricityLinearTerm, ancillaryElectricityLinearTerm);
      OS_ASSERT(result);
      return result;
    }

    void GeneratorFuelCellPowerModule_Impl::resetAncillaryElectricityLinearTerm() {
      OS_ASSERT(setDouble(openstudio::Generator_FuelCell_PowerModuleFields::AncillaryElectricityLinearTerm, 0.0));
    }

    std::string GeneratorFuelCellPowerModule_Impl::skinLossCalculationMode() const {
      const auto value = getString(openstudio::Generator_FuelCell_PowerModuleFields::SkinLossCalculationMode, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GeneratorFuelCellPowerModule_Impl::setSkinLossCalculationMode(const std::string& skinLossCalculationMode) {
      return setString(openstudio::Generator_FuelCell_PowerModuleFields::SkinLossCalculationMode, skinLossCalculationMode);
    }

    void GeneratorFuelCellPowerModule_Impl::resetSkinLossCalculationMode() {
      OS_ASSERT(setString(openstudio::Generator_FuelCell_PowerModuleFields::SkinLossCalculationMode, "ConstantRate"));
    }

    double GeneratorFuelCellPowerModule_Impl::skinLossRadiativeFraction() const {
      const auto value = getDouble(openstudio::Generator_FuelCell_PowerModuleFields::SkinLossRadiativeFraction, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GeneratorFuelCellPowerModule_Impl::setSkinLossRadiativeFraction(double skinLossRadiativeFraction) {
      return setDouble(openstudio::Generator_FuelCell_PowerModuleFields::SkinLossRadiativeFraction, skinLossRadiativeFraction);
    }

    void GeneratorFuelCellPowerModule_Impl::resetSkinLossRadiativeFraction() {
      OS_ASSERT(setDouble(openstudio::Generator_FuelCell_PowerModuleFields::SkinLossRadiativeFraction, 1.0));
    }

    double GeneratorFuelCellPowerModule_Impl::constantSkinLossRate() const {
      const auto value = getDouble(openstudio::Generator_FuelCell_PowerModuleFields::ConstantSkinLossRate, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GeneratorFuelCellPowerModule_Impl::setConstantSkinLossRate(double constantSkinLossRate) {
      const bool result = setDouble(openstudio::Generator_FuelCell_PowerModuleFields::ConstantSkinLossRate, constantSkinLossRate);
      OS_ASSERT(result);
      return result;
    }

    void GeneratorFuelCellPowerModule_Impl::resetConstantSkinLossRate() {
      OS_ASSERT(setDouble(openstudio::Generator_FuelCell_PowerModuleFields::ConstantSkinLossRate, 0.0));
    }

    double GeneratorFuelCellPowerModule_Impl::skinLossUFactorTimesAreaTerm() const {
      const auto value = getDouble(openstudio::Generator_FuelCell_PowerModuleFields::SkinLossUFactorTimesAreaTerm, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GeneratorFuelCellPowerModule_Impl::setSkinLossUFactorTimesAreaTerm(double skinLossUFactorTimesAreaTerm) {
      const bool result = setDouble(openstudio::Generator_FuelCell_PowerModuleFields::SkinLossUFactorTimesAreaTerm, skinLossUFactorTimesAreaTerm);
      OS_ASSERT(result);
      return result;
    }

    void GeneratorFuelCellPowerModule_Impl::resetSkinLossUFactorTimesAreaTerm() {
      OS_ASSERT(setDouble(openstudio::Generator_FuelCell_PowerModuleFields::SkinLossUFactorTimesAreaTerm, 1.0));
    }

    double GeneratorFuelCellPowerModule_Impl::dilutionAirFlowRate() const {
      const auto value = getDouble(openstudio::Generator_FuelCell_PowerModuleFields::DilutionAirFlowRate, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GeneratorFuelCellPowerModule_Impl::setDilutionAirFlowRate(double dilutionAirFlowRate) {
      const bool result = setDouble(openstudio::Generator_FuelCell_PowerModuleFields::DilutionAirFlowRate, dilutionAirFlowRate);
      OS_ASSERT(result);
      return result;
    }

    void GeneratorFuelCellPowerModule_Impl::resetDilutionAirFlowRate() {
      OS_ASSERT(setDouble(openstudio::Generator_FuelCell_PowerModuleFields::DilutionAirFlowRate, 0.0));
    }

    double GeneratorFuelCellPowerModule_Impl::stackHeatlosstoDilutionAir() const {
      const auto value = getDouble(openstudio::Generator_FuelCell_PowerModuleFields::StackHeatlosstoDilutionAir, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GeneratorFuelCellPowerModule_Impl::setStackHeatlosstoDilutionAir(double stackHeatlosstoDilutionAir) {
      const bool result = setDouble(openstudio::Generator_FuelCell_PowerModuleFields::StackHeatlosstoDilutionAir, stackHeatlosstoDilutionAir);
      OS_ASSERT(result);
      return result;
    }

    void GeneratorFuelCellPowerModule_Impl::resetStackHeatlosstoDilutionAir() {
      OS_ASSERT(setDouble(openstudio::Generator_FuelCell_PowerModuleFields::StackHeatlosstoDilutionAir, 0.0));
    }

    double GeneratorFuelCellPowerModule_Impl::minimumOperatingPoint() const {
      const auto value = getDouble(openstudio::Generator_FuelCell_PowerModuleFields::MinimumOperatingPoint, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GeneratorFuelCellPowerModule_Impl::setMinimumOperatingPoint(double minimumOperatingPoint) {
      const bool result = setDouble(openstudio::Generator_FuelCell_PowerModuleFields::MinimumOperatingPoint, minimumOperatingPoint);
      OS_ASSERT(result);
      return result;
    }

    void GeneratorFuelCellPowerModule_Impl::resetMinimumOperatingPoint() {
      OS_ASSERT(setDouble(openstudio::Generator_FuelCell_PowerModuleFields::MinimumOperatingPoint, 0.0));
    }

    double GeneratorFuelCellPowerModule_Impl::maximumOperatingPoint() const {
      const auto value = getDouble(openstudio::Generator_FuelCell_PowerModuleFields::MaximumOperatingPoint, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GeneratorFuelCellPowerModule_Impl::setMaximumOperatingPoint(double maximumOperatingPoint) {
      const bool result = setDouble(openstudio::Generator_FuelCell_PowerModuleFields::MaximumOperatingPoint, maximumOperatingPoint);
      OS_ASSERT(result);
      return result;
    }

    void GeneratorFuelCellPowerModule_Impl::resetMaximumOperatingPoint() {
      OS_ASSERT(setDouble(openstudio::Generator_FuelCell_PowerModuleFields::MaximumOperatingPoint, 0.0));
    }

    std::vector<std::string> GeneratorFuelCellPowerModule_Impl::efficiencyCurveModeValues() const {
      return openstudio::epmodel::GeneratorFuelCellPowerModule::efficiencyCurveModeValues();
    }

    std::vector<std::string> GeneratorFuelCellPowerModule_Impl::skinLossCalculationModeValues() const {
      return openstudio::epmodel::GeneratorFuelCellPowerModule::skinLossCalculationModeValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
