/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "WaterToWaterComponent/ChillerAbsorption.hpp"
#include "WaterToWaterComponent/ChillerAbsorption_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/Chiller_Absorption_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>

namespace openstudio {
namespace epmodel {

ChillerAbsorption::ChillerAbsorption(const Model& model) : WaterToWaterComponent(ChillerAbsorption::iddObjectType(), model) {}

ChillerAbsorption::ChillerAbsorption(std::shared_ptr<detail::ChillerAbsorption_Impl> impl) : WaterToWaterComponent(std::move(impl)) {}

IddObjectType ChillerAbsorption::iddObjectType() {
  return IddObjectType::Chiller_Absorption;
}

std::vector<std::string> ChillerAbsorption::chillerFlowModeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Chiller_AbsorptionFields::ChillerFlowMode);
}

std::vector<std::string> ChillerAbsorption::generatorHeatSourceTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Chiller_AbsorptionFields::GeneratorHeatSourceType);
}

boost::optional<double> ChillerAbsorption::nominalCapacity() const {
  return getImpl<detail::ChillerAbsorption_Impl>()->nominalCapacity();
}

bool ChillerAbsorption::isNominalCapacityAutosized() const {
  return getImpl<detail::ChillerAbsorption_Impl>()->isNominalCapacityAutosized();
}

bool ChillerAbsorption::setNominalCapacity(double nominalCapacity) {
  return getImpl<detail::ChillerAbsorption_Impl>()->setNominalCapacity(nominalCapacity);
}

void ChillerAbsorption::autosizeNominalCapacity() {
  getImpl<detail::ChillerAbsorption_Impl>()->autosizeNominalCapacity();
}

boost::optional<double> ChillerAbsorption::nominalPumpingPower() const {
  return getImpl<detail::ChillerAbsorption_Impl>()->nominalPumpingPower();
}

bool ChillerAbsorption::isNominalPumpingPowerAutosized() const {
  return getImpl<detail::ChillerAbsorption_Impl>()->isNominalPumpingPowerAutosized();
}

bool ChillerAbsorption::setNominalPumpingPower(double nominalPumpingPower) {
  return getImpl<detail::ChillerAbsorption_Impl>()->setNominalPumpingPower(nominalPumpingPower);
}

void ChillerAbsorption::autosizeNominalPumpingPower() {
  getImpl<detail::ChillerAbsorption_Impl>()->autosizeNominalPumpingPower();
}

double ChillerAbsorption::minimumPartLoadRatio() const {
  return getImpl<detail::ChillerAbsorption_Impl>()->minimumPartLoadRatio();
}

bool ChillerAbsorption::setMinimumPartLoadRatio(double minimumPartLoadRatio) {
  return getImpl<detail::ChillerAbsorption_Impl>()->setMinimumPartLoadRatio(minimumPartLoadRatio);
}

double ChillerAbsorption::maximumPartLoadRatio() const {
  return getImpl<detail::ChillerAbsorption_Impl>()->maximumPartLoadRatio();
}

bool ChillerAbsorption::setMaximumPartLoadRatio(double maximumPartLoadRatio) {
  return getImpl<detail::ChillerAbsorption_Impl>()->setMaximumPartLoadRatio(maximumPartLoadRatio);
}

double ChillerAbsorption::optimumPartLoadRatio() const {
  return getImpl<detail::ChillerAbsorption_Impl>()->optimumPartLoadRatio();
}

bool ChillerAbsorption::setOptimumPartLoadRatio(double optimumPartLoadRatio) {
  return getImpl<detail::ChillerAbsorption_Impl>()->setOptimumPartLoadRatio(optimumPartLoadRatio);
}

double ChillerAbsorption::designCondenserInletTemperature() const {
  return getImpl<detail::ChillerAbsorption_Impl>()->designCondenserInletTemperature();
}

bool ChillerAbsorption::setDesignCondenserInletTemperature(double designCondenserInletTemperature) {
  return getImpl<detail::ChillerAbsorption_Impl>()->setDesignCondenserInletTemperature(designCondenserInletTemperature);
}

boost::optional<double> ChillerAbsorption::designChilledWaterFlowRate() const {
  return getImpl<detail::ChillerAbsorption_Impl>()->designChilledWaterFlowRate();
}

bool ChillerAbsorption::isDesignChilledWaterFlowRateAutosized() const {
  return getImpl<detail::ChillerAbsorption_Impl>()->isDesignChilledWaterFlowRateAutosized();
}

bool ChillerAbsorption::setDesignChilledWaterFlowRate(double designChilledWaterFlowRate) {
  return getImpl<detail::ChillerAbsorption_Impl>()->setDesignChilledWaterFlowRate(designChilledWaterFlowRate);
}

void ChillerAbsorption::autosizeDesignChilledWaterFlowRate() {
  getImpl<detail::ChillerAbsorption_Impl>()->autosizeDesignChilledWaterFlowRate();
}

boost::optional<double> ChillerAbsorption::designCondenserWaterFlowRate() const {
  return getImpl<detail::ChillerAbsorption_Impl>()->designCondenserWaterFlowRate();
}

bool ChillerAbsorption::isDesignCondenserWaterFlowRateAutosized() const {
  return getImpl<detail::ChillerAbsorption_Impl>()->isDesignCondenserWaterFlowRateAutosized();
}

bool ChillerAbsorption::setDesignCondenserWaterFlowRate(double designCondenserWaterFlowRate) {
  return getImpl<detail::ChillerAbsorption_Impl>()->setDesignCondenserWaterFlowRate(designCondenserWaterFlowRate);
}

void ChillerAbsorption::autosizeDesignCondenserWaterFlowRate() {
  getImpl<detail::ChillerAbsorption_Impl>()->autosizeDesignCondenserWaterFlowRate();
}

double ChillerAbsorption::coefficient1oftheHotWaterorSteamUsePartLoadRatioCurve() const {
  return getImpl<detail::ChillerAbsorption_Impl>()->coefficient1oftheHotWaterorSteamUsePartLoadRatioCurve();
}

bool ChillerAbsorption::setCoefficient1oftheHotWaterorSteamUsePartLoadRatioCurve(double coefficient1oftheHotWaterorSteamUsePartLoadRatioCurve) {
  return getImpl<detail::ChillerAbsorption_Impl>()->setCoefficient1oftheHotWaterorSteamUsePartLoadRatioCurve(
    coefficient1oftheHotWaterorSteamUsePartLoadRatioCurve);
}

double ChillerAbsorption::coefficient2oftheHotWaterorSteamUsePartLoadRatioCurve() const {
  return getImpl<detail::ChillerAbsorption_Impl>()->coefficient2oftheHotWaterorSteamUsePartLoadRatioCurve();
}

bool ChillerAbsorption::setCoefficient2oftheHotWaterorSteamUsePartLoadRatioCurve(double coefficient2oftheHotWaterorSteamUsePartLoadRatioCurve) {
  return getImpl<detail::ChillerAbsorption_Impl>()->setCoefficient2oftheHotWaterorSteamUsePartLoadRatioCurve(
    coefficient2oftheHotWaterorSteamUsePartLoadRatioCurve);
}

double ChillerAbsorption::coefficient3oftheHotWaterorSteamUsePartLoadRatioCurve() const {
  return getImpl<detail::ChillerAbsorption_Impl>()->coefficient3oftheHotWaterorSteamUsePartLoadRatioCurve();
}

bool ChillerAbsorption::setCoefficient3oftheHotWaterorSteamUsePartLoadRatioCurve(double coefficient3oftheHotWaterorSteamUsePartLoadRatioCurve) {
  return getImpl<detail::ChillerAbsorption_Impl>()->setCoefficient3oftheHotWaterorSteamUsePartLoadRatioCurve(
    coefficient3oftheHotWaterorSteamUsePartLoadRatioCurve);
}

double ChillerAbsorption::coefficient1ofthePumpElectricUsePartLoadRatioCurve() const {
  return getImpl<detail::ChillerAbsorption_Impl>()->coefficient1ofthePumpElectricUsePartLoadRatioCurve();
}

bool ChillerAbsorption::setCoefficient1ofthePumpElectricUsePartLoadRatioCurve(double coefficient1ofthePumpElectricUsePartLoadRatioCurve) {
  return getImpl<detail::ChillerAbsorption_Impl>()->setCoefficient1ofthePumpElectricUsePartLoadRatioCurve(
    coefficient1ofthePumpElectricUsePartLoadRatioCurve);
}

double ChillerAbsorption::coefficient2ofthePumpElectricUsePartLoadRatioCurve() const {
  return getImpl<detail::ChillerAbsorption_Impl>()->coefficient2ofthePumpElectricUsePartLoadRatioCurve();
}

bool ChillerAbsorption::setCoefficient2ofthePumpElectricUsePartLoadRatioCurve(double coefficient2ofthePumpElectricUsePartLoadRatioCurve) {
  return getImpl<detail::ChillerAbsorption_Impl>()->setCoefficient2ofthePumpElectricUsePartLoadRatioCurve(
    coefficient2ofthePumpElectricUsePartLoadRatioCurve);
}

double ChillerAbsorption::coefficient3ofthePumpElectricUsePartLoadRatioCurve() const {
  return getImpl<detail::ChillerAbsorption_Impl>()->coefficient3ofthePumpElectricUsePartLoadRatioCurve();
}

bool ChillerAbsorption::setCoefficient3ofthePumpElectricUsePartLoadRatioCurve(double coefficient3ofthePumpElectricUsePartLoadRatioCurve) {
  return getImpl<detail::ChillerAbsorption_Impl>()->setCoefficient3ofthePumpElectricUsePartLoadRatioCurve(
    coefficient3ofthePumpElectricUsePartLoadRatioCurve);
}

double ChillerAbsorption::chilledWaterOutletTemperatureLowerLimit() const {
  return getImpl<detail::ChillerAbsorption_Impl>()->chilledWaterOutletTemperatureLowerLimit();
}

bool ChillerAbsorption::setChilledWaterOutletTemperatureLowerLimit(double chilledWaterOutletTemperatureLowerLimit) {
  return getImpl<detail::ChillerAbsorption_Impl>()->setChilledWaterOutletTemperatureLowerLimit(chilledWaterOutletTemperatureLowerLimit);
}

std::string ChillerAbsorption::chillerFlowMode() const {
  return getImpl<detail::ChillerAbsorption_Impl>()->chillerFlowMode();
}

bool ChillerAbsorption::setChillerFlowMode(const std::string& chillerFlowMode) {
  return getImpl<detail::ChillerAbsorption_Impl>()->setChillerFlowMode(chillerFlowMode);
}

std::string ChillerAbsorption::generatorHeatSourceType() const {
  return getImpl<detail::ChillerAbsorption_Impl>()->generatorHeatSourceType();
}

bool ChillerAbsorption::setGeneratorHeatSourceType(const std::string& generatorHeatSourceType) {
  return getImpl<detail::ChillerAbsorption_Impl>()->setGeneratorHeatSourceType(generatorHeatSourceType);
}

boost::optional<double> ChillerAbsorption::designGeneratorFluidFlowRate() const {
  return getImpl<detail::ChillerAbsorption_Impl>()->designGeneratorFluidFlowRate();
}

bool ChillerAbsorption::isDesignGeneratorFluidFlowRateAutosized() const {
  return getImpl<detail::ChillerAbsorption_Impl>()->isDesignGeneratorFluidFlowRateAutosized();
}

bool ChillerAbsorption::setDesignGeneratorFluidFlowRate(double designGeneratorFluidFlowRate) {
  return getImpl<detail::ChillerAbsorption_Impl>()->setDesignGeneratorFluidFlowRate(designGeneratorFluidFlowRate);
}

void ChillerAbsorption::autosizeDesignGeneratorFluidFlowRate() {
  getImpl<detail::ChillerAbsorption_Impl>()->autosizeDesignGeneratorFluidFlowRate();
}

double ChillerAbsorption::degreeofSubcoolinginSteamGenerator() const {
  return getImpl<detail::ChillerAbsorption_Impl>()->degreeofSubcoolinginSteamGenerator();
}

bool ChillerAbsorption::setDegreeofSubcoolinginSteamGenerator(double degreeofSubcoolinginSteamGenerator) {
  return getImpl<detail::ChillerAbsorption_Impl>()->setDegreeofSubcoolinginSteamGenerator(degreeofSubcoolinginSteamGenerator);
}

double ChillerAbsorption::sizingFactor() const {
  return getImpl<detail::ChillerAbsorption_Impl>()->sizingFactor();
}

bool ChillerAbsorption::setSizingFactor(double sizingFactor) {
  return getImpl<detail::ChillerAbsorption_Impl>()->setSizingFactor(sizingFactor);
}
}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

  boost::optional<double> ChillerAbsorption_Impl::nominalCapacity() const {
    return getDouble(openstudio::Chiller_AbsorptionFields::NominalCapacity, true);
  }

  bool ChillerAbsorption_Impl::isNominalCapacityAutosized() const {
    if (auto value = getString(openstudio::Chiller_AbsorptionFields::NominalCapacity, true)) {
      return openstudio::istringEqual(*value, "autosize");
    }
    return false;
  }

  bool ChillerAbsorption_Impl::setNominalCapacity(double nominalCapacity) {
    return setDouble(openstudio::Chiller_AbsorptionFields::NominalCapacity, nominalCapacity);
  }

  void ChillerAbsorption_Impl::autosizeNominalCapacity() {
    OS_ASSERT(setString(openstudio::Chiller_AbsorptionFields::NominalCapacity, "autosize"));
  }

  boost::optional<double> ChillerAbsorption_Impl::nominalPumpingPower() const {
    return getDouble(openstudio::Chiller_AbsorptionFields::NominalPumpingPower, true);
  }

  bool ChillerAbsorption_Impl::isNominalPumpingPowerAutosized() const {
    if (auto value = getString(openstudio::Chiller_AbsorptionFields::NominalPumpingPower, true)) {
      return openstudio::istringEqual(*value, "autosize");
    }
    return false;
  }

  bool ChillerAbsorption_Impl::setNominalPumpingPower(double nominalPumpingPower) {
    return setDouble(openstudio::Chiller_AbsorptionFields::NominalPumpingPower, nominalPumpingPower);
  }

  void ChillerAbsorption_Impl::autosizeNominalPumpingPower() {
    OS_ASSERT(setString(openstudio::Chiller_AbsorptionFields::NominalPumpingPower, "autosize"));
  }

  double ChillerAbsorption_Impl::minimumPartLoadRatio() const {
    const auto value = getDouble(openstudio::Chiller_AbsorptionFields::MinimumPartLoadRatio, true);
    OS_ASSERT(value);
    return *value;
  }

  bool ChillerAbsorption_Impl::setMinimumPartLoadRatio(double minimumPartLoadRatio) {
    return setDouble(openstudio::Chiller_AbsorptionFields::MinimumPartLoadRatio, minimumPartLoadRatio);
  }

  double ChillerAbsorption_Impl::maximumPartLoadRatio() const {
    const auto value = getDouble(openstudio::Chiller_AbsorptionFields::MaximumPartLoadRatio, true);
    OS_ASSERT(value);
    return *value;
  }

  bool ChillerAbsorption_Impl::setMaximumPartLoadRatio(double maximumPartLoadRatio) {
    return setDouble(openstudio::Chiller_AbsorptionFields::MaximumPartLoadRatio, maximumPartLoadRatio);
  }

  double ChillerAbsorption_Impl::optimumPartLoadRatio() const {
    const auto value = getDouble(openstudio::Chiller_AbsorptionFields::OptimumPartLoadRatio, true);
    OS_ASSERT(value);
    return *value;
  }

  bool ChillerAbsorption_Impl::setOptimumPartLoadRatio(double optimumPartLoadRatio) {
    return setDouble(openstudio::Chiller_AbsorptionFields::OptimumPartLoadRatio, optimumPartLoadRatio);
  }

  double ChillerAbsorption_Impl::designCondenserInletTemperature() const {
    const auto value = getDouble(openstudio::Chiller_AbsorptionFields::DesignCondenserInletTemperature, true);
    OS_ASSERT(value);
    return *value;
  }

  bool ChillerAbsorption_Impl::setDesignCondenserInletTemperature(double designCondenserInletTemperature) {
    const bool result = setDouble(openstudio::Chiller_AbsorptionFields::DesignCondenserInletTemperature, designCondenserInletTemperature);
    OS_ASSERT(result);
    return result;
  }

  boost::optional<double> ChillerAbsorption_Impl::designChilledWaterFlowRate() const {
    return getDouble(openstudio::Chiller_AbsorptionFields::DesignChilledWaterFlowRate, true);
  }

  bool ChillerAbsorption_Impl::isDesignChilledWaterFlowRateAutosized() const {
    if (auto value = getString(openstudio::Chiller_AbsorptionFields::DesignChilledWaterFlowRate, true)) {
      return openstudio::istringEqual(*value, "autosize");
    }
    return false;
  }

  bool ChillerAbsorption_Impl::setDesignChilledWaterFlowRate(double designChilledWaterFlowRate) {
    return setDouble(openstudio::Chiller_AbsorptionFields::DesignChilledWaterFlowRate, designChilledWaterFlowRate);
  }

  void ChillerAbsorption_Impl::autosizeDesignChilledWaterFlowRate() {
    OS_ASSERT(setString(openstudio::Chiller_AbsorptionFields::DesignChilledWaterFlowRate, "autosize"));
  }

  boost::optional<double> ChillerAbsorption_Impl::designCondenserWaterFlowRate() const {
    return getDouble(openstudio::Chiller_AbsorptionFields::DesignCondenserWaterFlowRate, true);
  }

  bool ChillerAbsorption_Impl::isDesignCondenserWaterFlowRateAutosized() const {
    if (auto value = getString(openstudio::Chiller_AbsorptionFields::DesignCondenserWaterFlowRate, true)) {
      return openstudio::istringEqual(*value, "autosize");
    }
    return false;
  }

  bool ChillerAbsorption_Impl::setDesignCondenserWaterFlowRate(double designCondenserWaterFlowRate) {
    return setDouble(openstudio::Chiller_AbsorptionFields::DesignCondenserWaterFlowRate, designCondenserWaterFlowRate);
  }

  void ChillerAbsorption_Impl::autosizeDesignCondenserWaterFlowRate() {
    OS_ASSERT(setString(openstudio::Chiller_AbsorptionFields::DesignCondenserWaterFlowRate, "autosize"));
  }

  double ChillerAbsorption_Impl::coefficient1oftheHotWaterorSteamUsePartLoadRatioCurve() const {
    const auto value = getDouble(openstudio::Chiller_AbsorptionFields::Coefficient1oftheHotWaterorSteamUsePartLoadRatioCurve, true);
    OS_ASSERT(value);
    return *value;
  }

  bool ChillerAbsorption_Impl::setCoefficient1oftheHotWaterorSteamUsePartLoadRatioCurve(double coefficient1oftheHotWaterorSteamUsePartLoadRatioCurve) {
    const bool result = setDouble(openstudio::Chiller_AbsorptionFields::Coefficient1oftheHotWaterorSteamUsePartLoadRatioCurve,
                                  coefficient1oftheHotWaterorSteamUsePartLoadRatioCurve);
    OS_ASSERT(result);
    return result;
  }

  double ChillerAbsorption_Impl::coefficient2oftheHotWaterorSteamUsePartLoadRatioCurve() const {
    const auto value = getDouble(openstudio::Chiller_AbsorptionFields::Coefficient2oftheHotWaterorSteamUsePartLoadRatioCurve, true);
    OS_ASSERT(value);
    return *value;
  }

  bool ChillerAbsorption_Impl::setCoefficient2oftheHotWaterorSteamUsePartLoadRatioCurve(double coefficient2oftheHotWaterorSteamUsePartLoadRatioCurve) {
    const bool result = setDouble(openstudio::Chiller_AbsorptionFields::Coefficient2oftheHotWaterorSteamUsePartLoadRatioCurve,
                                  coefficient2oftheHotWaterorSteamUsePartLoadRatioCurve);
    OS_ASSERT(result);
    return result;
  }

  double ChillerAbsorption_Impl::coefficient3oftheHotWaterorSteamUsePartLoadRatioCurve() const {
    const auto value = getDouble(openstudio::Chiller_AbsorptionFields::Coefficient3oftheHotWaterorSteamUsePartLoadRatioCurve, true);
    OS_ASSERT(value);
    return *value;
  }

  bool ChillerAbsorption_Impl::setCoefficient3oftheHotWaterorSteamUsePartLoadRatioCurve(double coefficient3oftheHotWaterorSteamUsePartLoadRatioCurve) {
    const bool result = setDouble(openstudio::Chiller_AbsorptionFields::Coefficient3oftheHotWaterorSteamUsePartLoadRatioCurve,
                                  coefficient3oftheHotWaterorSteamUsePartLoadRatioCurve);
    OS_ASSERT(result);
    return result;
  }

  double ChillerAbsorption_Impl::coefficient1ofthePumpElectricUsePartLoadRatioCurve() const {
    const auto value = getDouble(openstudio::Chiller_AbsorptionFields::Coefficient1ofthePumpElectricUsePartLoadRatioCurve, true);
    OS_ASSERT(value);
    return *value;
  }

  bool ChillerAbsorption_Impl::setCoefficient1ofthePumpElectricUsePartLoadRatioCurve(double coefficient1ofthePumpElectricUsePartLoadRatioCurve) {
    const bool result = setDouble(openstudio::Chiller_AbsorptionFields::Coefficient1ofthePumpElectricUsePartLoadRatioCurve,
                                  coefficient1ofthePumpElectricUsePartLoadRatioCurve);
    OS_ASSERT(result);
    return result;
  }

  double ChillerAbsorption_Impl::coefficient2ofthePumpElectricUsePartLoadRatioCurve() const {
    const auto value = getDouble(openstudio::Chiller_AbsorptionFields::Coefficient2ofthePumpElectricUsePartLoadRatioCurve, true);
    OS_ASSERT(value);
    return *value;
  }

  bool ChillerAbsorption_Impl::setCoefficient2ofthePumpElectricUsePartLoadRatioCurve(double coefficient2ofthePumpElectricUsePartLoadRatioCurve) {
    const bool result = setDouble(openstudio::Chiller_AbsorptionFields::Coefficient2ofthePumpElectricUsePartLoadRatioCurve,
                                  coefficient2ofthePumpElectricUsePartLoadRatioCurve);
    OS_ASSERT(result);
    return result;
  }

  double ChillerAbsorption_Impl::coefficient3ofthePumpElectricUsePartLoadRatioCurve() const {
    const auto value = getDouble(openstudio::Chiller_AbsorptionFields::Coefficient3ofthePumpElectricUsePartLoadRatioCurve, true);
    OS_ASSERT(value);
    return *value;
  }

  bool ChillerAbsorption_Impl::setCoefficient3ofthePumpElectricUsePartLoadRatioCurve(double coefficient3ofthePumpElectricUsePartLoadRatioCurve) {
    const bool result = setDouble(openstudio::Chiller_AbsorptionFields::Coefficient3ofthePumpElectricUsePartLoadRatioCurve,
                                  coefficient3ofthePumpElectricUsePartLoadRatioCurve);
    OS_ASSERT(result);
    return result;
  }

  double ChillerAbsorption_Impl::chilledWaterOutletTemperatureLowerLimit() const {
    const auto value = getDouble(openstudio::Chiller_AbsorptionFields::ChilledWaterOutletTemperatureLowerLimit, true);
    OS_ASSERT(value);
    return *value;
  }

  bool ChillerAbsorption_Impl::setChilledWaterOutletTemperatureLowerLimit(double chilledWaterOutletTemperatureLowerLimit) {
    const bool result = setDouble(openstudio::Chiller_AbsorptionFields::ChilledWaterOutletTemperatureLowerLimit,
                                  chilledWaterOutletTemperatureLowerLimit);
    OS_ASSERT(result);
    return result;
  }

  std::string ChillerAbsorption_Impl::chillerFlowMode() const {
    const auto value = getString(openstudio::Chiller_AbsorptionFields::ChillerFlowMode, true);
    OS_ASSERT(value);
    return *value;
  }

  bool ChillerAbsorption_Impl::setChillerFlowMode(const std::string& chillerFlowMode) {
    return setString(openstudio::Chiller_AbsorptionFields::ChillerFlowMode, chillerFlowMode);
  }

  std::string ChillerAbsorption_Impl::generatorHeatSourceType() const {
    const auto value = getString(openstudio::Chiller_AbsorptionFields::GeneratorHeatSourceType, true);
    OS_ASSERT(value);
    return *value;
  }

  bool ChillerAbsorption_Impl::setGeneratorHeatSourceType(const std::string& generatorHeatSourceType) {
    return setString(openstudio::Chiller_AbsorptionFields::GeneratorHeatSourceType, generatorHeatSourceType);
  }

  boost::optional<double> ChillerAbsorption_Impl::designGeneratorFluidFlowRate() const {
    return getDouble(openstudio::Chiller_AbsorptionFields::DesignGeneratorFluidFlowRate, true);
  }

  bool ChillerAbsorption_Impl::isDesignGeneratorFluidFlowRateAutosized() const {
    if (auto value = getString(openstudio::Chiller_AbsorptionFields::DesignGeneratorFluidFlowRate, true)) {
      return openstudio::istringEqual(*value, "autosize");
    }
    return false;
  }

  bool ChillerAbsorption_Impl::setDesignGeneratorFluidFlowRate(double designGeneratorFluidFlowRate) {
    return setDouble(openstudio::Chiller_AbsorptionFields::DesignGeneratorFluidFlowRate, designGeneratorFluidFlowRate);
  }

  void ChillerAbsorption_Impl::autosizeDesignGeneratorFluidFlowRate() {
    OS_ASSERT(setString(openstudio::Chiller_AbsorptionFields::DesignGeneratorFluidFlowRate, "autosize"));
  }

  double ChillerAbsorption_Impl::degreeofSubcoolinginSteamGenerator() const {
    const auto value = getDouble(openstudio::Chiller_AbsorptionFields::DegreeofSubcoolinginSteamGenerator, true);
    OS_ASSERT(value);
    return *value;
  }

  bool ChillerAbsorption_Impl::setDegreeofSubcoolinginSteamGenerator(double degreeofSubcoolinginSteamGenerator) {
    const bool result =
      setDouble(openstudio::Chiller_AbsorptionFields::DegreeofSubcoolinginSteamGenerator, degreeofSubcoolinginSteamGenerator);
    OS_ASSERT(result);
    return result;
  }

  double ChillerAbsorption_Impl::sizingFactor() const {
    const auto value = getDouble(openstudio::Chiller_AbsorptionFields::SizingFactor, true);
    OS_ASSERT(value);
    return *value;
  }

  bool ChillerAbsorption_Impl::setSizingFactor(double sizingFactor) {
    return setDouble(openstudio::Chiller_AbsorptionFields::SizingFactor, sizingFactor);
  }

  std::vector<std::string> ChillerAbsorption_Impl::chillerFlowModeValues() const {
    return openstudio::epmodel::ChillerAbsorption::chillerFlowModeValues();
  }

  std::vector<std::string> ChillerAbsorption_Impl::generatorHeatSourceTypeValues() const {
    return openstudio::epmodel::ChillerAbsorption::generatorHeatSourceTypeValues();
  }

  unsigned ChillerAbsorption_Impl::supplyInletPort() const {
    return openstudio::Chiller_AbsorptionFields::ChilledWaterInletNodeName;
  }

  unsigned ChillerAbsorption_Impl::supplyOutletPort() const {
    return openstudio::Chiller_AbsorptionFields::ChilledWaterOutletNodeName;
  }

  unsigned ChillerAbsorption_Impl::demandInletPort() const {
    return openstudio::Chiller_AbsorptionFields::CondenserInletNodeName;
  }

  unsigned ChillerAbsorption_Impl::demandOutletPort() const {
    return openstudio::Chiller_AbsorptionFields::CondenserOutletNodeName;
  }

  unsigned ChillerAbsorption_Impl::tertiaryInletPort() const {
    return openstudio::Chiller_AbsorptionFields::GeneratorInletNodeName;
  }

  unsigned ChillerAbsorption_Impl::tertiaryOutletPort() const {
    return openstudio::Chiller_AbsorptionFields::GeneratorOutletNodeName;
  }

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
