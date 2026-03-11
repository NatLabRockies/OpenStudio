/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "WaterToWaterComponent/ChillerAbsorptionIndirect.hpp"
#include "WaterToWaterComponent/ChillerAbsorptionIndirect_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/Chiller_Absorption_Indirect_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>

namespace openstudio {
namespace epmodel {

ChillerAbsorptionIndirect::ChillerAbsorptionIndirect(const Model& model) : ModelObject(ChillerAbsorptionIndirect::iddObjectType(), model) {}

ChillerAbsorptionIndirect::ChillerAbsorptionIndirect(std::shared_ptr<detail::ChillerAbsorptionIndirect_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType ChillerAbsorptionIndirect::iddObjectType() {
  return IddObjectType::Chiller_Absorption_Indirect;
}

std::vector<std::string> ChillerAbsorptionIndirect::chillerFlowModeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Chiller_Absorption_IndirectFields::ChillerFlowMode);
}

std::vector<std::string> ChillerAbsorptionIndirect::generatorHeatSourceTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Chiller_Absorption_IndirectFields::GeneratorHeatSourceType);
}

boost::optional<double> ChillerAbsorptionIndirect::nominalCapacity() const {
  return getImpl<detail::ChillerAbsorptionIndirect_Impl>()->nominalCapacity();
}

bool ChillerAbsorptionIndirect::isNominalCapacityAutosized() const {
  return getImpl<detail::ChillerAbsorptionIndirect_Impl>()->isNominalCapacityAutosized();
}

boost::optional<double> ChillerAbsorptionIndirect::nominalPumpingPower() const {
  return getImpl<detail::ChillerAbsorptionIndirect_Impl>()->nominalPumpingPower();
}

bool ChillerAbsorptionIndirect::isNominalPumpingPowerAutosized() const {
  return getImpl<detail::ChillerAbsorptionIndirect_Impl>()->isNominalPumpingPowerAutosized();
}

double ChillerAbsorptionIndirect::minimumPartLoadRatio() const {
  return getImpl<detail::ChillerAbsorptionIndirect_Impl>()->minimumPartLoadRatio();
}

double ChillerAbsorptionIndirect::maximumPartLoadRatio() const {
  return getImpl<detail::ChillerAbsorptionIndirect_Impl>()->maximumPartLoadRatio();
}

double ChillerAbsorptionIndirect::optimumPartLoadRatio() const {
  return getImpl<detail::ChillerAbsorptionIndirect_Impl>()->optimumPartLoadRatio();
}

double ChillerAbsorptionIndirect::designCondenserInletTemperature() const {
  return getImpl<detail::ChillerAbsorptionIndirect_Impl>()->designCondenserInletTemperature();
}

double ChillerAbsorptionIndirect::condenserInletTemperatureLowerLimit() const {
  return getImpl<detail::ChillerAbsorptionIndirect_Impl>()->condenserInletTemperatureLowerLimit();
}

double ChillerAbsorptionIndirect::chilledWaterOutletTemperatureLowerLimit() const {
  return getImpl<detail::ChillerAbsorptionIndirect_Impl>()->chilledWaterOutletTemperatureLowerLimit();
}

boost::optional<double> ChillerAbsorptionIndirect::designChilledWaterFlowRate() const {
  return getImpl<detail::ChillerAbsorptionIndirect_Impl>()->designChilledWaterFlowRate();
}

bool ChillerAbsorptionIndirect::isDesignChilledWaterFlowRateAutosized() const {
  return getImpl<detail::ChillerAbsorptionIndirect_Impl>()->isDesignChilledWaterFlowRateAutosized();
}

boost::optional<double> ChillerAbsorptionIndirect::designCondenserWaterFlowRate() const {
  return getImpl<detail::ChillerAbsorptionIndirect_Impl>()->designCondenserWaterFlowRate();
}

bool ChillerAbsorptionIndirect::isDesignCondenserWaterFlowRateAutosized() const {
  return getImpl<detail::ChillerAbsorptionIndirect_Impl>()->isDesignCondenserWaterFlowRateAutosized();
}

std::string ChillerAbsorptionIndirect::chillerFlowMode() const {
  return getImpl<detail::ChillerAbsorptionIndirect_Impl>()->chillerFlowMode();
}

std::string ChillerAbsorptionIndirect::generatorHeatSourceType() const {
  return getImpl<detail::ChillerAbsorptionIndirect_Impl>()->generatorHeatSourceType();
}

boost::optional<double> ChillerAbsorptionIndirect::designGeneratorFluidFlowRate() const {
  return getImpl<detail::ChillerAbsorptionIndirect_Impl>()->designGeneratorFluidFlowRate();
}

bool ChillerAbsorptionIndirect::isDesignGeneratorFluidFlowRateAutosized() const {
  return getImpl<detail::ChillerAbsorptionIndirect_Impl>()->isDesignGeneratorFluidFlowRateAutosized();
}

double ChillerAbsorptionIndirect::temperatureLowerLimitGeneratorInlet() const {
  return getImpl<detail::ChillerAbsorptionIndirect_Impl>()->temperatureLowerLimitGeneratorInlet();
}

double ChillerAbsorptionIndirect::degreeofSubcoolinginSteamGenerator() const {
  return getImpl<detail::ChillerAbsorptionIndirect_Impl>()->degreeofSubcoolinginSteamGenerator();
}

double ChillerAbsorptionIndirect::degreeofSubcoolinginSteamCondensateLoop() const {
  return getImpl<detail::ChillerAbsorptionIndirect_Impl>()->degreeofSubcoolinginSteamCondensateLoop();
}

double ChillerAbsorptionIndirect::sizingFactor() const {
  return getImpl<detail::ChillerAbsorptionIndirect_Impl>()->sizingFactor();
}

bool ChillerAbsorptionIndirect::setNominalCapacity(double nominalCapacity) {
  return getImpl<detail::ChillerAbsorptionIndirect_Impl>()->setNominalCapacity(nominalCapacity);
}

void ChillerAbsorptionIndirect::autosizeNominalCapacity() {
  getImpl<detail::ChillerAbsorptionIndirect_Impl>()->autosizeNominalCapacity();
}

bool ChillerAbsorptionIndirect::setNominalPumpingPower(double nominalPumpingPower) {
  return getImpl<detail::ChillerAbsorptionIndirect_Impl>()->setNominalPumpingPower(nominalPumpingPower);
}

void ChillerAbsorptionIndirect::autosizeNominalPumpingPower() {
  getImpl<detail::ChillerAbsorptionIndirect_Impl>()->autosizeNominalPumpingPower();
}

bool ChillerAbsorptionIndirect::setMinimumPartLoadRatio(double minimumPartLoadRatio) {
  return getImpl<detail::ChillerAbsorptionIndirect_Impl>()->setMinimumPartLoadRatio(minimumPartLoadRatio);
}

bool ChillerAbsorptionIndirect::setMaximumPartLoadRatio(double maximumPartLoadRatio) {
  return getImpl<detail::ChillerAbsorptionIndirect_Impl>()->setMaximumPartLoadRatio(maximumPartLoadRatio);
}

bool ChillerAbsorptionIndirect::setOptimumPartLoadRatio(double optimumPartLoadRatio) {
  return getImpl<detail::ChillerAbsorptionIndirect_Impl>()->setOptimumPartLoadRatio(optimumPartLoadRatio);
}

bool ChillerAbsorptionIndirect::setDesignCondenserInletTemperature(double designCondenserInletTemperature) {
  return getImpl<detail::ChillerAbsorptionIndirect_Impl>()->setDesignCondenserInletTemperature(designCondenserInletTemperature);
}

bool ChillerAbsorptionIndirect::setCondenserInletTemperatureLowerLimit(double condenserInletTemperatureLowerLimit) {
  return getImpl<detail::ChillerAbsorptionIndirect_Impl>()->setCondenserInletTemperatureLowerLimit(condenserInletTemperatureLowerLimit);
}

bool ChillerAbsorptionIndirect::setChilledWaterOutletTemperatureLowerLimit(double chilledWaterOutletTemperatureLowerLimit) {
  return getImpl<detail::ChillerAbsorptionIndirect_Impl>()->setChilledWaterOutletTemperatureLowerLimit(chilledWaterOutletTemperatureLowerLimit);
}

bool ChillerAbsorptionIndirect::setDesignChilledWaterFlowRate(double designChilledWaterFlowRate) {
  return getImpl<detail::ChillerAbsorptionIndirect_Impl>()->setDesignChilledWaterFlowRate(designChilledWaterFlowRate);
}

void ChillerAbsorptionIndirect::autosizeDesignChilledWaterFlowRate() {
  getImpl<detail::ChillerAbsorptionIndirect_Impl>()->autosizeDesignChilledWaterFlowRate();
}

bool ChillerAbsorptionIndirect::setDesignCondenserWaterFlowRate(double designCondenserWaterFlowRate) {
  return getImpl<detail::ChillerAbsorptionIndirect_Impl>()->setDesignCondenserWaterFlowRate(designCondenserWaterFlowRate);
}

void ChillerAbsorptionIndirect::autosizeDesignCondenserWaterFlowRate() {
  getImpl<detail::ChillerAbsorptionIndirect_Impl>()->autosizeDesignCondenserWaterFlowRate();
}

bool ChillerAbsorptionIndirect::setChillerFlowMode(const std::string& chillerFlowMode) {
  return getImpl<detail::ChillerAbsorptionIndirect_Impl>()->setChillerFlowMode(chillerFlowMode);
}

bool ChillerAbsorptionIndirect::setGeneratorHeatSourceType(const std::string& generatorHeatSourceType) {
  return getImpl<detail::ChillerAbsorptionIndirect_Impl>()->setGeneratorHeatSourceType(generatorHeatSourceType);
}

bool ChillerAbsorptionIndirect::setDesignGeneratorFluidFlowRate(double designGeneratorFluidFlowRate) {
  return getImpl<detail::ChillerAbsorptionIndirect_Impl>()->setDesignGeneratorFluidFlowRate(designGeneratorFluidFlowRate);
}

void ChillerAbsorptionIndirect::autosizeDesignGeneratorFluidFlowRate() {
  getImpl<detail::ChillerAbsorptionIndirect_Impl>()->autosizeDesignGeneratorFluidFlowRate();
}

bool ChillerAbsorptionIndirect::setTemperatureLowerLimitGeneratorInlet(double temperatureLowerLimitGeneratorInlet) {
  return getImpl<detail::ChillerAbsorptionIndirect_Impl>()->setTemperatureLowerLimitGeneratorInlet(temperatureLowerLimitGeneratorInlet);
}

bool ChillerAbsorptionIndirect::setDegreeofSubcoolinginSteamGenerator(double degreeofSubcoolinginSteamGenerator) {
  return getImpl<detail::ChillerAbsorptionIndirect_Impl>()->setDegreeofSubcoolinginSteamGenerator(degreeofSubcoolinginSteamGenerator);
}

bool ChillerAbsorptionIndirect::setDegreeofSubcoolinginSteamCondensateLoop(double degreeofSubcoolinginSteamCondensateLoop) {
  return getImpl<detail::ChillerAbsorptionIndirect_Impl>()->setDegreeofSubcoolinginSteamCondensateLoop(degreeofSubcoolinginSteamCondensateLoop);
}

bool ChillerAbsorptionIndirect::setSizingFactor(double sizingFactor) {
  return getImpl<detail::ChillerAbsorptionIndirect_Impl>()->setSizingFactor(sizingFactor);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

boost::optional<double> ChillerAbsorptionIndirect_Impl::nominalCapacity() const {
  return getDouble(openstudio::Chiller_Absorption_IndirectFields::NominalCapacity, true);
}

bool ChillerAbsorptionIndirect_Impl::isNominalCapacityAutosized() const {
  if (auto value = getString(openstudio::Chiller_Absorption_IndirectFields::NominalCapacity, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

boost::optional<double> ChillerAbsorptionIndirect_Impl::nominalPumpingPower() const {
  return getDouble(openstudio::Chiller_Absorption_IndirectFields::NominalPumpingPower, true);
}

bool ChillerAbsorptionIndirect_Impl::isNominalPumpingPowerAutosized() const {
  if (auto value = getString(openstudio::Chiller_Absorption_IndirectFields::NominalPumpingPower, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

double ChillerAbsorptionIndirect_Impl::minimumPartLoadRatio() const {
  const auto value = getDouble(openstudio::Chiller_Absorption_IndirectFields::MinimumPartLoadRatio, true);
  OS_ASSERT(value);
  return *value;
}

double ChillerAbsorptionIndirect_Impl::maximumPartLoadRatio() const {
  const auto value = getDouble(openstudio::Chiller_Absorption_IndirectFields::MaximumPartLoadRatio, true);
  OS_ASSERT(value);
  return *value;
}

double ChillerAbsorptionIndirect_Impl::optimumPartLoadRatio() const {
  const auto value = getDouble(openstudio::Chiller_Absorption_IndirectFields::OptimumPartLoadRatio, true);
  OS_ASSERT(value);
  return *value;
}

double ChillerAbsorptionIndirect_Impl::designCondenserInletTemperature() const {
  const auto value = getDouble(openstudio::Chiller_Absorption_IndirectFields::DesignCondenserInletTemperature, true);
  OS_ASSERT(value);
  return *value;
}

double ChillerAbsorptionIndirect_Impl::condenserInletTemperatureLowerLimit() const {
  const auto value = getDouble(openstudio::Chiller_Absorption_IndirectFields::CondenserInletTemperatureLowerLimit, true);
  OS_ASSERT(value);
  return *value;
}

double ChillerAbsorptionIndirect_Impl::chilledWaterOutletTemperatureLowerLimit() const {
  const auto value = getDouble(openstudio::Chiller_Absorption_IndirectFields::ChilledWaterOutletTemperatureLowerLimit, true);
  OS_ASSERT(value);
  return *value;
}

boost::optional<double> ChillerAbsorptionIndirect_Impl::designChilledWaterFlowRate() const {
  return getDouble(openstudio::Chiller_Absorption_IndirectFields::DesignChilledWaterFlowRate, true);
}

bool ChillerAbsorptionIndirect_Impl::isDesignChilledWaterFlowRateAutosized() const {
  if (auto value = getString(openstudio::Chiller_Absorption_IndirectFields::DesignChilledWaterFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

boost::optional<double> ChillerAbsorptionIndirect_Impl::designCondenserWaterFlowRate() const {
  return getDouble(openstudio::Chiller_Absorption_IndirectFields::DesignCondenserWaterFlowRate, true);
}

bool ChillerAbsorptionIndirect_Impl::isDesignCondenserWaterFlowRateAutosized() const {
  if (auto value = getString(openstudio::Chiller_Absorption_IndirectFields::DesignCondenserWaterFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

std::string ChillerAbsorptionIndirect_Impl::chillerFlowMode() const {
  const auto value = getString(openstudio::Chiller_Absorption_IndirectFields::ChillerFlowMode, true);
  OS_ASSERT(value);
  return *value;
}

std::string ChillerAbsorptionIndirect_Impl::generatorHeatSourceType() const {
  const auto value = getString(openstudio::Chiller_Absorption_IndirectFields::GeneratorHeatSourceType, true);
  OS_ASSERT(value);
  return *value;
}

boost::optional<double> ChillerAbsorptionIndirect_Impl::designGeneratorFluidFlowRate() const {
  return getDouble(openstudio::Chiller_Absorption_IndirectFields::DesignGeneratorFluidFlowRate, true);
}

bool ChillerAbsorptionIndirect_Impl::isDesignGeneratorFluidFlowRateAutosized() const {
  if (auto value = getString(openstudio::Chiller_Absorption_IndirectFields::DesignGeneratorFluidFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

double ChillerAbsorptionIndirect_Impl::temperatureLowerLimitGeneratorInlet() const {
  const auto value = getDouble(openstudio::Chiller_Absorption_IndirectFields::TemperatureLowerLimitGeneratorInlet, true);
  OS_ASSERT(value);
  return *value;
}

double ChillerAbsorptionIndirect_Impl::degreeofSubcoolinginSteamGenerator() const {
  const auto value = getDouble(openstudio::Chiller_Absorption_IndirectFields::DegreeofSubcoolinginSteamGenerator, true);
  OS_ASSERT(value);
  return *value;
}

double ChillerAbsorptionIndirect_Impl::degreeofSubcoolinginSteamCondensateLoop() const {
  const auto value = getDouble(openstudio::Chiller_Absorption_IndirectFields::DegreeofSubcoolinginSteamCondensateLoop, true);
  OS_ASSERT(value);
  return *value;
}

double ChillerAbsorptionIndirect_Impl::sizingFactor() const {
  const auto value = getDouble(openstudio::Chiller_Absorption_IndirectFields::SizingFactor, true);
  OS_ASSERT(value);
  return *value;
}

bool ChillerAbsorptionIndirect_Impl::setNominalCapacity(double nominalCapacity) {
  return setDouble(openstudio::Chiller_Absorption_IndirectFields::NominalCapacity, nominalCapacity);
}

void ChillerAbsorptionIndirect_Impl::autosizeNominalCapacity() {
  OS_ASSERT(setString(openstudio::Chiller_Absorption_IndirectFields::NominalCapacity, "autosize"));
}

bool ChillerAbsorptionIndirect_Impl::setNominalPumpingPower(double nominalPumpingPower) {
  return setDouble(openstudio::Chiller_Absorption_IndirectFields::NominalPumpingPower, nominalPumpingPower);
}

void ChillerAbsorptionIndirect_Impl::autosizeNominalPumpingPower() {
  OS_ASSERT(setString(openstudio::Chiller_Absorption_IndirectFields::NominalPumpingPower, "autosize"));
}

bool ChillerAbsorptionIndirect_Impl::setMinimumPartLoadRatio(double minimumPartLoadRatio) {
  return setDouble(openstudio::Chiller_Absorption_IndirectFields::MinimumPartLoadRatio, minimumPartLoadRatio);
}

bool ChillerAbsorptionIndirect_Impl::setMaximumPartLoadRatio(double maximumPartLoadRatio) {
  return setDouble(openstudio::Chiller_Absorption_IndirectFields::MaximumPartLoadRatio, maximumPartLoadRatio);
}

bool ChillerAbsorptionIndirect_Impl::setOptimumPartLoadRatio(double optimumPartLoadRatio) {
  return setDouble(openstudio::Chiller_Absorption_IndirectFields::OptimumPartLoadRatio, optimumPartLoadRatio);
}

bool ChillerAbsorptionIndirect_Impl::setDesignCondenserInletTemperature(double designCondenserInletTemperature) {
  const bool result = setDouble(openstudio::Chiller_Absorption_IndirectFields::DesignCondenserInletTemperature, designCondenserInletTemperature);
  OS_ASSERT(result);
  return result;
}

bool ChillerAbsorptionIndirect_Impl::setCondenserInletTemperatureLowerLimit(double condenserInletTemperatureLowerLimit) {
  const bool result =
    setDouble(openstudio::Chiller_Absorption_IndirectFields::CondenserInletTemperatureLowerLimit, condenserInletTemperatureLowerLimit);
  OS_ASSERT(result);
  return result;
}

bool ChillerAbsorptionIndirect_Impl::setChilledWaterOutletTemperatureLowerLimit(double chilledWaterOutletTemperatureLowerLimit) {
  const bool result =
    setDouble(openstudio::Chiller_Absorption_IndirectFields::ChilledWaterOutletTemperatureLowerLimit, chilledWaterOutletTemperatureLowerLimit);
  OS_ASSERT(result);
  return result;
}

bool ChillerAbsorptionIndirect_Impl::setDesignChilledWaterFlowRate(double designChilledWaterFlowRate) {
  return setDouble(openstudio::Chiller_Absorption_IndirectFields::DesignChilledWaterFlowRate, designChilledWaterFlowRate);
}

void ChillerAbsorptionIndirect_Impl::autosizeDesignChilledWaterFlowRate() {
  OS_ASSERT(setString(openstudio::Chiller_Absorption_IndirectFields::DesignChilledWaterFlowRate, "autosize"));
}

bool ChillerAbsorptionIndirect_Impl::setDesignCondenserWaterFlowRate(double designCondenserWaterFlowRate) {
  return setDouble(openstudio::Chiller_Absorption_IndirectFields::DesignCondenserWaterFlowRate, designCondenserWaterFlowRate);
}

void ChillerAbsorptionIndirect_Impl::autosizeDesignCondenserWaterFlowRate() {
  OS_ASSERT(setString(openstudio::Chiller_Absorption_IndirectFields::DesignCondenserWaterFlowRate, "autosize"));
}

bool ChillerAbsorptionIndirect_Impl::setChillerFlowMode(const std::string& chillerFlowMode) {
  return setString(openstudio::Chiller_Absorption_IndirectFields::ChillerFlowMode, chillerFlowMode);
}

bool ChillerAbsorptionIndirect_Impl::setGeneratorHeatSourceType(const std::string& generatorHeatSourceType) {
  return setString(openstudio::Chiller_Absorption_IndirectFields::GeneratorHeatSourceType, generatorHeatSourceType);
}

bool ChillerAbsorptionIndirect_Impl::setDesignGeneratorFluidFlowRate(double designGeneratorFluidFlowRate) {
  const bool result = setDouble(openstudio::Chiller_Absorption_IndirectFields::DesignGeneratorFluidFlowRate, designGeneratorFluidFlowRate);
  OS_ASSERT(result);
  return result;
}

void ChillerAbsorptionIndirect_Impl::autosizeDesignGeneratorFluidFlowRate() {
  OS_ASSERT(setString(openstudio::Chiller_Absorption_IndirectFields::DesignGeneratorFluidFlowRate, "autosize"));
}

bool ChillerAbsorptionIndirect_Impl::setTemperatureLowerLimitGeneratorInlet(double temperatureLowerLimitGeneratorInlet) {
  const bool result =
    setDouble(openstudio::Chiller_Absorption_IndirectFields::TemperatureLowerLimitGeneratorInlet, temperatureLowerLimitGeneratorInlet);
  OS_ASSERT(result);
  return result;
}

bool ChillerAbsorptionIndirect_Impl::setDegreeofSubcoolinginSteamGenerator(double degreeofSubcoolinginSteamGenerator) {
  return setDouble(openstudio::Chiller_Absorption_IndirectFields::DegreeofSubcoolinginSteamGenerator, degreeofSubcoolinginSteamGenerator);
}

bool ChillerAbsorptionIndirect_Impl::setDegreeofSubcoolinginSteamCondensateLoop(double degreeofSubcoolinginSteamCondensateLoop) {
  return setDouble(openstudio::Chiller_Absorption_IndirectFields::DegreeofSubcoolinginSteamCondensateLoop,
                   degreeofSubcoolinginSteamCondensateLoop);
}

bool ChillerAbsorptionIndirect_Impl::setSizingFactor(double sizingFactor) {
  return setDouble(openstudio::Chiller_Absorption_IndirectFields::SizingFactor, sizingFactor);
}

std::vector<std::string> ChillerAbsorptionIndirect_Impl::chillerFlowModeValues() const {
  return openstudio::epmodel::ChillerAbsorptionIndirect::chillerFlowModeValues();
}

std::vector<std::string> ChillerAbsorptionIndirect_Impl::generatorHeatSourceTypeValues() const {
  return openstudio::epmodel::ChillerAbsorptionIndirect::generatorHeatSourceTypeValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
