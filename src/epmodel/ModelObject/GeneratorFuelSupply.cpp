/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "GeneratorFuelSupply.hpp"
#include "GeneratorFuelSupply_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/Generator_FuelSupply_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

GeneratorFuelSupply::GeneratorFuelSupply(const Model& model) : ModelObject(GeneratorFuelSupply::iddObjectType(), model) {
  // Keep non-optional counterpart getters strict on a default-constructed object.
  OS_ASSERT(setFuelTemperatureModelingMode("Scheduled"));
  OS_ASSERT(setCompressorHeatLossFactor(1.0));
  OS_ASSERT(setFuelType("GaseousConstituents"));
}

GeneratorFuelSupply::GeneratorFuelSupply(std::shared_ptr<detail::GeneratorFuelSupply_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType GeneratorFuelSupply::iddObjectType() {
  return IddObjectType::Generator_FuelSupply;
}

std::vector<std::string> GeneratorFuelSupply::fuelTemperatureModelingModeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::Generator_FuelSupplyFields::FuelTemperatureModelingMode);
}

std::vector<std::string> GeneratorFuelSupply::fuelTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Generator_FuelSupplyFields::FuelType);
}

std::string GeneratorFuelSupply::fuelTemperatureModelingMode() const {
  return getImpl<detail::GeneratorFuelSupply_Impl>()->fuelTemperatureModelingMode();
}

bool GeneratorFuelSupply::setFuelTemperatureModelingMode(const std::string& fuelTemperatureModelingMode) {
  return getImpl<detail::GeneratorFuelSupply_Impl>()->setFuelTemperatureModelingMode(fuelTemperatureModelingMode);
}

void GeneratorFuelSupply::resetFuelTemperatureModelingMode() {
  getImpl<detail::GeneratorFuelSupply_Impl>()->resetFuelTemperatureModelingMode();
}

double GeneratorFuelSupply::compressorHeatLossFactor() const {
  return getImpl<detail::GeneratorFuelSupply_Impl>()->compressorHeatLossFactor();
}

bool GeneratorFuelSupply::setCompressorHeatLossFactor(double compressorHeatLossFactor) {
  return getImpl<detail::GeneratorFuelSupply_Impl>()->setCompressorHeatLossFactor(compressorHeatLossFactor);
}

void GeneratorFuelSupply::resetCompressorHeatLossFactor() {
  getImpl<detail::GeneratorFuelSupply_Impl>()->resetCompressorHeatLossFactor();
}

std::string GeneratorFuelSupply::fuelType() const {
  return getImpl<detail::GeneratorFuelSupply_Impl>()->fuelType();
}

bool GeneratorFuelSupply::setFuelType(const std::string& fuelType) {
  return getImpl<detail::GeneratorFuelSupply_Impl>()->setFuelType(fuelType);
}

void GeneratorFuelSupply::resetFuelType() {
  getImpl<detail::GeneratorFuelSupply_Impl>()->resetFuelType();
}

boost::optional<double> GeneratorFuelSupply::liquidGenericFuelLowerHeatingValue() const {
  return getImpl<detail::GeneratorFuelSupply_Impl>()->liquidGenericFuelLowerHeatingValue();
}

bool GeneratorFuelSupply::setLiquidGenericFuelLowerHeatingValue(double liquidGenericFuelLowerHeatingValue) {
  return getImpl<detail::GeneratorFuelSupply_Impl>()->setLiquidGenericFuelLowerHeatingValue(liquidGenericFuelLowerHeatingValue);
}

void GeneratorFuelSupply::resetLiquidGenericFuelLowerHeatingValue() {
  getImpl<detail::GeneratorFuelSupply_Impl>()->resetLiquidGenericFuelLowerHeatingValue();
}

boost::optional<double> GeneratorFuelSupply::liquidGenericFuelHigherHeatingValue() const {
  return getImpl<detail::GeneratorFuelSupply_Impl>()->liquidGenericFuelHigherHeatingValue();
}

bool GeneratorFuelSupply::setLiquidGenericFuelHigherHeatingValue(double liquidGenericFuelHigherHeatingValue) {
  return getImpl<detail::GeneratorFuelSupply_Impl>()->setLiquidGenericFuelHigherHeatingValue(liquidGenericFuelHigherHeatingValue);
}

void GeneratorFuelSupply::resetLiquidGenericFuelHigherHeatingValue() {
  getImpl<detail::GeneratorFuelSupply_Impl>()->resetLiquidGenericFuelHigherHeatingValue();
}

boost::optional<double> GeneratorFuelSupply::liquidGenericFuelMolecularWeight() const {
  return getImpl<detail::GeneratorFuelSupply_Impl>()->liquidGenericFuelMolecularWeight();
}

bool GeneratorFuelSupply::setLiquidGenericFuelMolecularWeight(double liquidGenericFuelMolecularWeight) {
  return getImpl<detail::GeneratorFuelSupply_Impl>()->setLiquidGenericFuelMolecularWeight(liquidGenericFuelMolecularWeight);
}

void GeneratorFuelSupply::resetLiquidGenericFuelMolecularWeight() {
  getImpl<detail::GeneratorFuelSupply_Impl>()->resetLiquidGenericFuelMolecularWeight();
}

boost::optional<double> GeneratorFuelSupply::liquidGenericFuelCO2EmissionFactor() const {
  return getImpl<detail::GeneratorFuelSupply_Impl>()->liquidGenericFuelCO2EmissionFactor();
}

bool GeneratorFuelSupply::setLiquidGenericFuelCO2EmissionFactor(double liquidGenericFuelCO2EmissionFactor) {
  return getImpl<detail::GeneratorFuelSupply_Impl>()->setLiquidGenericFuelCO2EmissionFactor(liquidGenericFuelCO2EmissionFactor);
}

void GeneratorFuelSupply::resetLiquidGenericFuelCO2EmissionFactor() {
  getImpl<detail::GeneratorFuelSupply_Impl>()->resetLiquidGenericFuelCO2EmissionFactor();
}

boost::optional<unsigned int> GeneratorFuelSupply::numberofConstituentsinGaseousConstituentFuelSupply() const {
  return getImpl<detail::GeneratorFuelSupply_Impl>()->numberofConstituentsinGaseousConstituentFuelSupply();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

std::string GeneratorFuelSupply_Impl::fuelTemperatureModelingMode() const {
  const auto value = getString(openstudio::Generator_FuelSupplyFields::FuelTemperatureModelingMode, true);
  OS_ASSERT(value);
  return *value;
}

bool GeneratorFuelSupply_Impl::setFuelTemperatureModelingMode(const std::string& fuelTemperatureModelingMode) {
  return setString(openstudio::Generator_FuelSupplyFields::FuelTemperatureModelingMode, fuelTemperatureModelingMode);
}

void GeneratorFuelSupply_Impl::resetFuelTemperatureModelingMode() {
  OS_ASSERT(setString(openstudio::Generator_FuelSupplyFields::FuelTemperatureModelingMode, "Scheduled"));
}

double GeneratorFuelSupply_Impl::compressorHeatLossFactor() const {
  const auto value = getDouble(openstudio::Generator_FuelSupplyFields::CompressorHeatLossFactor, true);
  OS_ASSERT(value);
  return *value;
}

bool GeneratorFuelSupply_Impl::setCompressorHeatLossFactor(double compressorHeatLossFactor) {
  return setDouble(openstudio::Generator_FuelSupplyFields::CompressorHeatLossFactor, compressorHeatLossFactor);
}

void GeneratorFuelSupply_Impl::resetCompressorHeatLossFactor() {
  OS_ASSERT(setDouble(openstudio::Generator_FuelSupplyFields::CompressorHeatLossFactor, 0.0));
}

std::string GeneratorFuelSupply_Impl::fuelType() const {
  const auto value = getString(openstudio::Generator_FuelSupplyFields::FuelType, true);
  OS_ASSERT(value);
  return *value;
}

bool GeneratorFuelSupply_Impl::setFuelType(const std::string& fuelType) {
  return setString(openstudio::Generator_FuelSupplyFields::FuelType, fuelType);
}

void GeneratorFuelSupply_Impl::resetFuelType() {
  OS_ASSERT(setString(openstudio::Generator_FuelSupplyFields::FuelType, "GaseousConstituents"));
}

boost::optional<double> GeneratorFuelSupply_Impl::liquidGenericFuelLowerHeatingValue() const {
  return getDouble(openstudio::Generator_FuelSupplyFields::LiquidGenericFuelLowerHeatingValue, true);
}

bool GeneratorFuelSupply_Impl::setLiquidGenericFuelLowerHeatingValue(double liquidGenericFuelLowerHeatingValue) {
  const bool result = setDouble(openstudio::Generator_FuelSupplyFields::LiquidGenericFuelLowerHeatingValue, liquidGenericFuelLowerHeatingValue);
  OS_ASSERT(result);
  return result;
}

void GeneratorFuelSupply_Impl::resetLiquidGenericFuelLowerHeatingValue() {
  OS_ASSERT(setString(openstudio::Generator_FuelSupplyFields::LiquidGenericFuelLowerHeatingValue, ""));
}

boost::optional<double> GeneratorFuelSupply_Impl::liquidGenericFuelHigherHeatingValue() const {
  return getDouble(openstudio::Generator_FuelSupplyFields::LiquidGenericFuelHigherHeatingValue, true);
}

bool GeneratorFuelSupply_Impl::setLiquidGenericFuelHigherHeatingValue(double liquidGenericFuelHigherHeatingValue) {
  const bool result =
    setDouble(openstudio::Generator_FuelSupplyFields::LiquidGenericFuelHigherHeatingValue, liquidGenericFuelHigherHeatingValue);
  OS_ASSERT(result);
  return result;
}

void GeneratorFuelSupply_Impl::resetLiquidGenericFuelHigherHeatingValue() {
  OS_ASSERT(setString(openstudio::Generator_FuelSupplyFields::LiquidGenericFuelHigherHeatingValue, ""));
}

boost::optional<double> GeneratorFuelSupply_Impl::liquidGenericFuelMolecularWeight() const {
  return getDouble(openstudio::Generator_FuelSupplyFields::LiquidGenericFuelMolecularWeight, true);
}

bool GeneratorFuelSupply_Impl::setLiquidGenericFuelMolecularWeight(double liquidGenericFuelMolecularWeight) {
  const bool result = setDouble(openstudio::Generator_FuelSupplyFields::LiquidGenericFuelMolecularWeight, liquidGenericFuelMolecularWeight);
  OS_ASSERT(result);
  return result;
}

void GeneratorFuelSupply_Impl::resetLiquidGenericFuelMolecularWeight() {
  OS_ASSERT(setString(openstudio::Generator_FuelSupplyFields::LiquidGenericFuelMolecularWeight, ""));
}

boost::optional<double> GeneratorFuelSupply_Impl::liquidGenericFuelCO2EmissionFactor() const {
  return getDouble(openstudio::Generator_FuelSupplyFields::LiquidGenericFuelCO2EmissionFactor, true);
}

bool GeneratorFuelSupply_Impl::setLiquidGenericFuelCO2EmissionFactor(double liquidGenericFuelCO2EmissionFactor) {
  const bool result = setDouble(openstudio::Generator_FuelSupplyFields::LiquidGenericFuelCO2EmissionFactor, liquidGenericFuelCO2EmissionFactor);
  OS_ASSERT(result);
  return result;
}

void GeneratorFuelSupply_Impl::resetLiquidGenericFuelCO2EmissionFactor() {
  OS_ASSERT(setString(openstudio::Generator_FuelSupplyFields::LiquidGenericFuelCO2EmissionFactor, ""));
}

boost::optional<unsigned int> GeneratorFuelSupply_Impl::numberofConstituentsinGaseousConstituentFuelSupply() const {
  return numExtensibleGroups();
}

std::vector<std::string> GeneratorFuelSupply_Impl::fuelTemperatureModelingModeValues() const {
  return openstudio::epmodel::GeneratorFuelSupply::fuelTemperatureModelingModeValues();
}

std::vector<std::string> GeneratorFuelSupply_Impl::fuelTypeValues() const {
  return openstudio::epmodel::GeneratorFuelSupply::fuelTypeValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
