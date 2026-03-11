/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/GeneratorFuelCellStackCooler.hpp"
#include "StraightComponent/GeneratorFuelCellStackCooler_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/Generator_FuelCell_StackCooler_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

GeneratorFuelCellStackCooler::GeneratorFuelCellStackCooler(const Model& model) : StraightComponent(iddObjectType(), model) {
  OS_ASSERT(setNominalStackTemperature(20.0));
  OS_ASSERT(setActualStackTemperature(20.0));
  OS_ASSERT(setCoefficientr0(0.0));
  OS_ASSERT(setCoefficientr1(0.0));
  OS_ASSERT(setCoefficientr2(0.0));
  OS_ASSERT(setCoefficientr3(0.0));
  OS_ASSERT(setStackCoolantFlowRate(1.0));
  OS_ASSERT(setStackCoolerUFactorTimesAreaValue(1.0));
  OS_ASSERT(setFscogenAdjustmentFactor(0.0));
  OS_ASSERT(setStackCogenerationExchangerArea(1.0));
  OS_ASSERT(setStackCogenerationExchangerNominalFlowRate(1.0));
  OS_ASSERT(setStackCogenerationExchangerNominalHeatTransferCoefficient(0.0));
  OS_ASSERT(setStackCogenerationExchangerNominalHeatTransferCoefficientExponent(0.0));
  OS_ASSERT(setStackCoolerPumpPower(0.0));
  OS_ASSERT(setStackCoolerPumpHeatLossFraction(0.0));
  OS_ASSERT(setStackAirCoolerFanCoefficientf0(0.0));
  OS_ASSERT(setStackAirCoolerFanCoefficientf1(0.0));
  OS_ASSERT(setStackAirCoolerFanCoefficientf2(0.0));
}

GeneratorFuelCellStackCooler::GeneratorFuelCellStackCooler(std::shared_ptr<detail::GeneratorFuelCellStackCooler_Impl> impl)
  : StraightComponent(std::move(impl)) {}

IddObjectType GeneratorFuelCellStackCooler::iddObjectType() {
  return IddObjectType::Generator_FuelCell_StackCooler;
}

double GeneratorFuelCellStackCooler::nominalStackTemperature() const {
  return getImpl<detail::GeneratorFuelCellStackCooler_Impl>()->nominalStackTemperature();
}

double GeneratorFuelCellStackCooler::actualStackTemperature() const {
  return getImpl<detail::GeneratorFuelCellStackCooler_Impl>()->actualStackTemperature();
}

double GeneratorFuelCellStackCooler::coefficientr0() const {
  return getImpl<detail::GeneratorFuelCellStackCooler_Impl>()->coefficientr0();
}

double GeneratorFuelCellStackCooler::coefficientr1() const {
  return getImpl<detail::GeneratorFuelCellStackCooler_Impl>()->coefficientr1();
}

double GeneratorFuelCellStackCooler::coefficientr2() const {
  return getImpl<detail::GeneratorFuelCellStackCooler_Impl>()->coefficientr2();
}

double GeneratorFuelCellStackCooler::coefficientr3() const {
  return getImpl<detail::GeneratorFuelCellStackCooler_Impl>()->coefficientr3();
}

double GeneratorFuelCellStackCooler::stackCoolantFlowRate() const {
  return getImpl<detail::GeneratorFuelCellStackCooler_Impl>()->stackCoolantFlowRate();
}

double GeneratorFuelCellStackCooler::stackCoolerUFactorTimesAreaValue() const {
  return getImpl<detail::GeneratorFuelCellStackCooler_Impl>()->stackCoolerUFactorTimesAreaValue();
}

double GeneratorFuelCellStackCooler::fscogenAdjustmentFactor() const {
  return getImpl<detail::GeneratorFuelCellStackCooler_Impl>()->fscogenAdjustmentFactor();
}

double GeneratorFuelCellStackCooler::stackCogenerationExchangerArea() const {
  return getImpl<detail::GeneratorFuelCellStackCooler_Impl>()->stackCogenerationExchangerArea();
}

double GeneratorFuelCellStackCooler::stackCogenerationExchangerNominalFlowRate() const {
  return getImpl<detail::GeneratorFuelCellStackCooler_Impl>()->stackCogenerationExchangerNominalFlowRate();
}

double GeneratorFuelCellStackCooler::stackCogenerationExchangerNominalHeatTransferCoefficient() const {
  return getImpl<detail::GeneratorFuelCellStackCooler_Impl>()->stackCogenerationExchangerNominalHeatTransferCoefficient();
}

double GeneratorFuelCellStackCooler::stackCogenerationExchangerNominalHeatTransferCoefficientExponent() const {
  return getImpl<detail::GeneratorFuelCellStackCooler_Impl>()->stackCogenerationExchangerNominalHeatTransferCoefficientExponent();
}

double GeneratorFuelCellStackCooler::stackCoolerPumpPower() const {
  return getImpl<detail::GeneratorFuelCellStackCooler_Impl>()->stackCoolerPumpPower();
}

double GeneratorFuelCellStackCooler::stackCoolerPumpHeatLossFraction() const {
  return getImpl<detail::GeneratorFuelCellStackCooler_Impl>()->stackCoolerPumpHeatLossFraction();
}

double GeneratorFuelCellStackCooler::stackAirCoolerFanCoefficientf0() const {
  return getImpl<detail::GeneratorFuelCellStackCooler_Impl>()->stackAirCoolerFanCoefficientf0();
}

double GeneratorFuelCellStackCooler::stackAirCoolerFanCoefficientf1() const {
  return getImpl<detail::GeneratorFuelCellStackCooler_Impl>()->stackAirCoolerFanCoefficientf1();
}

double GeneratorFuelCellStackCooler::stackAirCoolerFanCoefficientf2() const {
  return getImpl<detail::GeneratorFuelCellStackCooler_Impl>()->stackAirCoolerFanCoefficientf2();
}

bool GeneratorFuelCellStackCooler::setNominalStackTemperature(double nominalStackTemperature) {
  return getImpl<detail::GeneratorFuelCellStackCooler_Impl>()->setNominalStackTemperature(nominalStackTemperature);
}

void GeneratorFuelCellStackCooler::resetNominalStackTemperature() {
  getImpl<detail::GeneratorFuelCellStackCooler_Impl>()->resetNominalStackTemperature();
}

bool GeneratorFuelCellStackCooler::setActualStackTemperature(double actualStackTemperature) {
  return getImpl<detail::GeneratorFuelCellStackCooler_Impl>()->setActualStackTemperature(actualStackTemperature);
}

void GeneratorFuelCellStackCooler::resetActualStackTemperature() {
  getImpl<detail::GeneratorFuelCellStackCooler_Impl>()->resetActualStackTemperature();
}

bool GeneratorFuelCellStackCooler::setCoefficientr0(double coefficientr0) {
  return getImpl<detail::GeneratorFuelCellStackCooler_Impl>()->setCoefficientr0(coefficientr0);
}

void GeneratorFuelCellStackCooler::resetCoefficientr0() {
  getImpl<detail::GeneratorFuelCellStackCooler_Impl>()->resetCoefficientr0();
}

bool GeneratorFuelCellStackCooler::setCoefficientr1(double coefficientr1) {
  return getImpl<detail::GeneratorFuelCellStackCooler_Impl>()->setCoefficientr1(coefficientr1);
}

void GeneratorFuelCellStackCooler::resetCoefficientr1() {
  getImpl<detail::GeneratorFuelCellStackCooler_Impl>()->resetCoefficientr1();
}

bool GeneratorFuelCellStackCooler::setCoefficientr2(double coefficientr2) {
  return getImpl<detail::GeneratorFuelCellStackCooler_Impl>()->setCoefficientr2(coefficientr2);
}

void GeneratorFuelCellStackCooler::resetCoefficientr2() {
  getImpl<detail::GeneratorFuelCellStackCooler_Impl>()->resetCoefficientr2();
}

bool GeneratorFuelCellStackCooler::setCoefficientr3(double coefficientr3) {
  return getImpl<detail::GeneratorFuelCellStackCooler_Impl>()->setCoefficientr3(coefficientr3);
}

void GeneratorFuelCellStackCooler::resetCoefficientr3() {
  getImpl<detail::GeneratorFuelCellStackCooler_Impl>()->resetCoefficientr3();
}

bool GeneratorFuelCellStackCooler::setStackCoolantFlowRate(double stackCoolantFlowRate) {
  return getImpl<detail::GeneratorFuelCellStackCooler_Impl>()->setStackCoolantFlowRate(stackCoolantFlowRate);
}

void GeneratorFuelCellStackCooler::resetStackCoolantFlowRate() {
  getImpl<detail::GeneratorFuelCellStackCooler_Impl>()->resetStackCoolantFlowRate();
}

bool GeneratorFuelCellStackCooler::setStackCoolerUFactorTimesAreaValue(double stackCoolerUFactorTimesAreaValue) {
  return getImpl<detail::GeneratorFuelCellStackCooler_Impl>()->setStackCoolerUFactorTimesAreaValue(stackCoolerUFactorTimesAreaValue);
}

void GeneratorFuelCellStackCooler::resetStackCoolerUFactorTimesAreaValue() {
  getImpl<detail::GeneratorFuelCellStackCooler_Impl>()->resetStackCoolerUFactorTimesAreaValue();
}

bool GeneratorFuelCellStackCooler::setFscogenAdjustmentFactor(double fscogenAdjustmentFactor) {
  return getImpl<detail::GeneratorFuelCellStackCooler_Impl>()->setFscogenAdjustmentFactor(fscogenAdjustmentFactor);
}

void GeneratorFuelCellStackCooler::resetFscogenAdjustmentFactor() {
  getImpl<detail::GeneratorFuelCellStackCooler_Impl>()->resetFscogenAdjustmentFactor();
}

bool GeneratorFuelCellStackCooler::setStackCogenerationExchangerArea(double stackCogenerationExchangerArea) {
  return getImpl<detail::GeneratorFuelCellStackCooler_Impl>()->setStackCogenerationExchangerArea(stackCogenerationExchangerArea);
}

void GeneratorFuelCellStackCooler::resetStackCogenerationExchangerArea() {
  getImpl<detail::GeneratorFuelCellStackCooler_Impl>()->resetStackCogenerationExchangerArea();
}

bool GeneratorFuelCellStackCooler::setStackCogenerationExchangerNominalFlowRate(double stackCogenerationExchangerNominalFlowRate) {
  return getImpl<detail::GeneratorFuelCellStackCooler_Impl>()->setStackCogenerationExchangerNominalFlowRate(
    stackCogenerationExchangerNominalFlowRate);
}

void GeneratorFuelCellStackCooler::resetStackCogenerationExchangerNominalFlowRate() {
  getImpl<detail::GeneratorFuelCellStackCooler_Impl>()->resetStackCogenerationExchangerNominalFlowRate();
}

bool GeneratorFuelCellStackCooler::setStackCogenerationExchangerNominalHeatTransferCoefficient(
  double stackCogenerationExchangerNominalHeatTransferCoefficient) {
  return getImpl<detail::GeneratorFuelCellStackCooler_Impl>()->setStackCogenerationExchangerNominalHeatTransferCoefficient(
    stackCogenerationExchangerNominalHeatTransferCoefficient);
}

void GeneratorFuelCellStackCooler::resetStackCogenerationExchangerNominalHeatTransferCoefficient() {
  getImpl<detail::GeneratorFuelCellStackCooler_Impl>()->resetStackCogenerationExchangerNominalHeatTransferCoefficient();
}

bool GeneratorFuelCellStackCooler::setStackCogenerationExchangerNominalHeatTransferCoefficientExponent(
  double stackCogenerationExchangerNominalHeatTransferCoefficientExponent) {
  return getImpl<detail::GeneratorFuelCellStackCooler_Impl>()->setStackCogenerationExchangerNominalHeatTransferCoefficientExponent(
    stackCogenerationExchangerNominalHeatTransferCoefficientExponent);
}

void GeneratorFuelCellStackCooler::resetStackCogenerationExchangerNominalHeatTransferCoefficientExponent() {
  getImpl<detail::GeneratorFuelCellStackCooler_Impl>()->resetStackCogenerationExchangerNominalHeatTransferCoefficientExponent();
}

bool GeneratorFuelCellStackCooler::setStackCoolerPumpPower(double stackCoolerPumpPower) {
  return getImpl<detail::GeneratorFuelCellStackCooler_Impl>()->setStackCoolerPumpPower(stackCoolerPumpPower);
}

void GeneratorFuelCellStackCooler::resetStackCoolerPumpPower() {
  getImpl<detail::GeneratorFuelCellStackCooler_Impl>()->resetStackCoolerPumpPower();
}

bool GeneratorFuelCellStackCooler::setStackCoolerPumpHeatLossFraction(double stackCoolerPumpHeatLossFraction) {
  return getImpl<detail::GeneratorFuelCellStackCooler_Impl>()->setStackCoolerPumpHeatLossFraction(stackCoolerPumpHeatLossFraction);
}

void GeneratorFuelCellStackCooler::resetStackCoolerPumpHeatLossFraction() {
  getImpl<detail::GeneratorFuelCellStackCooler_Impl>()->resetStackCoolerPumpHeatLossFraction();
}

bool GeneratorFuelCellStackCooler::setStackAirCoolerFanCoefficientf0(double stackAirCoolerFanCoefficientf0) {
  return getImpl<detail::GeneratorFuelCellStackCooler_Impl>()->setStackAirCoolerFanCoefficientf0(stackAirCoolerFanCoefficientf0);
}

void GeneratorFuelCellStackCooler::resetStackAirCoolerFanCoefficientf0() {
  getImpl<detail::GeneratorFuelCellStackCooler_Impl>()->resetStackAirCoolerFanCoefficientf0();
}

bool GeneratorFuelCellStackCooler::setStackAirCoolerFanCoefficientf1(double stackAirCoolerFanCoefficientf1) {
  return getImpl<detail::GeneratorFuelCellStackCooler_Impl>()->setStackAirCoolerFanCoefficientf1(stackAirCoolerFanCoefficientf1);
}

void GeneratorFuelCellStackCooler::resetStackAirCoolerFanCoefficientf1() {
  getImpl<detail::GeneratorFuelCellStackCooler_Impl>()->resetStackAirCoolerFanCoefficientf1();
}

bool GeneratorFuelCellStackCooler::setStackAirCoolerFanCoefficientf2(double stackAirCoolerFanCoefficientf2) {
  return getImpl<detail::GeneratorFuelCellStackCooler_Impl>()->setStackAirCoolerFanCoefficientf2(stackAirCoolerFanCoefficientf2);
}

void GeneratorFuelCellStackCooler::resetStackAirCoolerFanCoefficientf2() {
  getImpl<detail::GeneratorFuelCellStackCooler_Impl>()->resetStackAirCoolerFanCoefficientf2();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

unsigned GeneratorFuelCellStackCooler_Impl::inletPort() const {
  // Relationship mapping only: Heat Recovery Water Inlet Node Name
  return openstudio::Generator_FuelCell_StackCoolerFields::HeatRecoveryWaterInletNodeName;
}

unsigned GeneratorFuelCellStackCooler_Impl::outletPort() const {
  // Relationship mapping only: Heat Recovery Water Outlet Node Name
  return openstudio::Generator_FuelCell_StackCoolerFields::HeatRecoveryWaterOutletNodeName;
}

double GeneratorFuelCellStackCooler_Impl::nominalStackTemperature() const {
  const auto value = getDouble(openstudio::Generator_FuelCell_StackCoolerFields::NominalStackTemperature, true);
  OS_ASSERT(value);
  return *value;
}

double GeneratorFuelCellStackCooler_Impl::actualStackTemperature() const {
  const auto value = getDouble(openstudio::Generator_FuelCell_StackCoolerFields::ActualStackTemperature, true);
  OS_ASSERT(value);
  return *value;
}

double GeneratorFuelCellStackCooler_Impl::coefficientr0() const {
  const auto value = getDouble(openstudio::Generator_FuelCell_StackCoolerFields::Coefficientr0, true);
  OS_ASSERT(value);
  return *value;
}

double GeneratorFuelCellStackCooler_Impl::coefficientr1() const {
  const auto value = getDouble(openstudio::Generator_FuelCell_StackCoolerFields::Coefficientr1, true);
  OS_ASSERT(value);
  return *value;
}

double GeneratorFuelCellStackCooler_Impl::coefficientr2() const {
  const auto value = getDouble(openstudio::Generator_FuelCell_StackCoolerFields::Coefficientr2, true);
  OS_ASSERT(value);
  return *value;
}

double GeneratorFuelCellStackCooler_Impl::coefficientr3() const {
  const auto value = getDouble(openstudio::Generator_FuelCell_StackCoolerFields::Coefficientr3, true);
  OS_ASSERT(value);
  return *value;
}

double GeneratorFuelCellStackCooler_Impl::stackCoolantFlowRate() const {
  const auto value = getDouble(openstudio::Generator_FuelCell_StackCoolerFields::StackCoolantFlowRate, true);
  OS_ASSERT(value);
  return *value;
}

double GeneratorFuelCellStackCooler_Impl::stackCoolerUFactorTimesAreaValue() const {
  const auto value = getDouble(openstudio::Generator_FuelCell_StackCoolerFields::StackCoolerUFactorTimesAreaValue, true);
  OS_ASSERT(value);
  return *value;
}

double GeneratorFuelCellStackCooler_Impl::fscogenAdjustmentFactor() const {
  const auto value = getDouble(openstudio::Generator_FuelCell_StackCoolerFields::FscogenAdjustmentFactor, true);
  OS_ASSERT(value);
  return *value;
}

double GeneratorFuelCellStackCooler_Impl::stackCogenerationExchangerArea() const {
  const auto value = getDouble(openstudio::Generator_FuelCell_StackCoolerFields::StackCogenerationExchangerArea, true);
  OS_ASSERT(value);
  return *value;
}

double GeneratorFuelCellStackCooler_Impl::stackCogenerationExchangerNominalFlowRate() const {
  const auto value = getDouble(openstudio::Generator_FuelCell_StackCoolerFields::StackCogenerationExchangerNominalFlowRate, true);
  OS_ASSERT(value);
  return *value;
}

double GeneratorFuelCellStackCooler_Impl::stackCogenerationExchangerNominalHeatTransferCoefficient() const {
  const auto value = getDouble(openstudio::Generator_FuelCell_StackCoolerFields::StackCogenerationExchangerNominalHeatTransferCoefficient, true);
  OS_ASSERT(value);
  return *value;
}

double GeneratorFuelCellStackCooler_Impl::stackCogenerationExchangerNominalHeatTransferCoefficientExponent() const {
  const auto value =
    getDouble(openstudio::Generator_FuelCell_StackCoolerFields::StackCogenerationExchangerNominalHeatTransferCoefficientExponent, true);
  OS_ASSERT(value);
  return *value;
}

double GeneratorFuelCellStackCooler_Impl::stackCoolerPumpPower() const {
  const auto value = getDouble(openstudio::Generator_FuelCell_StackCoolerFields::StackCoolerPumpPower, true);
  OS_ASSERT(value);
  return *value;
}

double GeneratorFuelCellStackCooler_Impl::stackCoolerPumpHeatLossFraction() const {
  const auto value = getDouble(openstudio::Generator_FuelCell_StackCoolerFields::StackCoolerPumpHeatLossFraction, true);
  OS_ASSERT(value);
  return *value;
}

double GeneratorFuelCellStackCooler_Impl::stackAirCoolerFanCoefficientf0() const {
  const auto value = getDouble(openstudio::Generator_FuelCell_StackCoolerFields::StackAirCoolerFanCoefficientf0, true);
  OS_ASSERT(value);
  return *value;
}

double GeneratorFuelCellStackCooler_Impl::stackAirCoolerFanCoefficientf1() const {
  const auto value = getDouble(openstudio::Generator_FuelCell_StackCoolerFields::StackAirCoolerFanCoefficientf1, true);
  OS_ASSERT(value);
  return *value;
}

double GeneratorFuelCellStackCooler_Impl::stackAirCoolerFanCoefficientf2() const {
  const auto value = getDouble(openstudio::Generator_FuelCell_StackCoolerFields::StackAirCoolerFanCoefficientf2, true);
  OS_ASSERT(value);
  return *value;
}

bool GeneratorFuelCellStackCooler_Impl::setNominalStackTemperature(double nominalStackTemperature) {
  const bool result = setDouble(openstudio::Generator_FuelCell_StackCoolerFields::NominalStackTemperature, nominalStackTemperature);
  OS_ASSERT(result);
  return result;
}

void GeneratorFuelCellStackCooler_Impl::resetNominalStackTemperature() {
  OS_ASSERT(setDouble(openstudio::Generator_FuelCell_StackCoolerFields::NominalStackTemperature, 20.0));
}

bool GeneratorFuelCellStackCooler_Impl::setActualStackTemperature(double actualStackTemperature) {
  const bool result = setDouble(openstudio::Generator_FuelCell_StackCoolerFields::ActualStackTemperature, actualStackTemperature);
  OS_ASSERT(result);
  return result;
}

void GeneratorFuelCellStackCooler_Impl::resetActualStackTemperature() {
  OS_ASSERT(setDouble(openstudio::Generator_FuelCell_StackCoolerFields::ActualStackTemperature, 20.0));
}

bool GeneratorFuelCellStackCooler_Impl::setCoefficientr0(double coefficientr0) {
  const bool result = setDouble(openstudio::Generator_FuelCell_StackCoolerFields::Coefficientr0, coefficientr0);
  OS_ASSERT(result);
  return result;
}

void GeneratorFuelCellStackCooler_Impl::resetCoefficientr0() {
  OS_ASSERT(setDouble(openstudio::Generator_FuelCell_StackCoolerFields::Coefficientr0, 0.0));
}

bool GeneratorFuelCellStackCooler_Impl::setCoefficientr1(double coefficientr1) {
  const bool result = setDouble(openstudio::Generator_FuelCell_StackCoolerFields::Coefficientr1, coefficientr1);
  OS_ASSERT(result);
  return result;
}

void GeneratorFuelCellStackCooler_Impl::resetCoefficientr1() {
  OS_ASSERT(setDouble(openstudio::Generator_FuelCell_StackCoolerFields::Coefficientr1, 0.0));
}

bool GeneratorFuelCellStackCooler_Impl::setCoefficientr2(double coefficientr2) {
  const bool result = setDouble(openstudio::Generator_FuelCell_StackCoolerFields::Coefficientr2, coefficientr2);
  OS_ASSERT(result);
  return result;
}

void GeneratorFuelCellStackCooler_Impl::resetCoefficientr2() {
  OS_ASSERT(setDouble(openstudio::Generator_FuelCell_StackCoolerFields::Coefficientr2, 0.0));
}

bool GeneratorFuelCellStackCooler_Impl::setCoefficientr3(double coefficientr3) {
  const bool result = setDouble(openstudio::Generator_FuelCell_StackCoolerFields::Coefficientr3, coefficientr3);
  OS_ASSERT(result);
  return result;
}

void GeneratorFuelCellStackCooler_Impl::resetCoefficientr3() {
  OS_ASSERT(setDouble(openstudio::Generator_FuelCell_StackCoolerFields::Coefficientr3, 0.0));
}

bool GeneratorFuelCellStackCooler_Impl::setStackCoolantFlowRate(double stackCoolantFlowRate) {
  const bool result = setDouble(openstudio::Generator_FuelCell_StackCoolerFields::StackCoolantFlowRate, stackCoolantFlowRate);
  OS_ASSERT(result);
  return result;
}

void GeneratorFuelCellStackCooler_Impl::resetStackCoolantFlowRate() {
  OS_ASSERT(setDouble(openstudio::Generator_FuelCell_StackCoolerFields::StackCoolantFlowRate, 1.0));
}

bool GeneratorFuelCellStackCooler_Impl::setStackCoolerUFactorTimesAreaValue(double stackCoolerUFactorTimesAreaValue) {
  const bool result = setDouble(openstudio::Generator_FuelCell_StackCoolerFields::StackCoolerUFactorTimesAreaValue,
                                stackCoolerUFactorTimesAreaValue);
  OS_ASSERT(result);
  return result;
}

void GeneratorFuelCellStackCooler_Impl::resetStackCoolerUFactorTimesAreaValue() {
  OS_ASSERT(setDouble(openstudio::Generator_FuelCell_StackCoolerFields::StackCoolerUFactorTimesAreaValue, 1.0));
}

bool GeneratorFuelCellStackCooler_Impl::setFscogenAdjustmentFactor(double fscogenAdjustmentFactor) {
  const bool result = setDouble(openstudio::Generator_FuelCell_StackCoolerFields::FscogenAdjustmentFactor, fscogenAdjustmentFactor);
  OS_ASSERT(result);
  return result;
}

void GeneratorFuelCellStackCooler_Impl::resetFscogenAdjustmentFactor() {
  OS_ASSERT(setDouble(openstudio::Generator_FuelCell_StackCoolerFields::FscogenAdjustmentFactor, 0.0));
}

bool GeneratorFuelCellStackCooler_Impl::setStackCogenerationExchangerArea(double stackCogenerationExchangerArea) {
  const bool result = setDouble(openstudio::Generator_FuelCell_StackCoolerFields::StackCogenerationExchangerArea,
                                stackCogenerationExchangerArea);
  OS_ASSERT(result);
  return result;
}

void GeneratorFuelCellStackCooler_Impl::resetStackCogenerationExchangerArea() {
  OS_ASSERT(setDouble(openstudio::Generator_FuelCell_StackCoolerFields::StackCogenerationExchangerArea, 1.0));
}

bool GeneratorFuelCellStackCooler_Impl::setStackCogenerationExchangerNominalFlowRate(double stackCogenerationExchangerNominalFlowRate) {
  const bool result = setDouble(openstudio::Generator_FuelCell_StackCoolerFields::StackCogenerationExchangerNominalFlowRate,
                                stackCogenerationExchangerNominalFlowRate);
  OS_ASSERT(result);
  return result;
}

void GeneratorFuelCellStackCooler_Impl::resetStackCogenerationExchangerNominalFlowRate() {
  OS_ASSERT(setDouble(openstudio::Generator_FuelCell_StackCoolerFields::StackCogenerationExchangerNominalFlowRate, 1.0));
}

bool GeneratorFuelCellStackCooler_Impl::setStackCogenerationExchangerNominalHeatTransferCoefficient(
  double stackCogenerationExchangerNominalHeatTransferCoefficient) {
  const bool result = setDouble(openstudio::Generator_FuelCell_StackCoolerFields::StackCogenerationExchangerNominalHeatTransferCoefficient,
                                stackCogenerationExchangerNominalHeatTransferCoefficient);
  OS_ASSERT(result);
  return result;
}

void GeneratorFuelCellStackCooler_Impl::resetStackCogenerationExchangerNominalHeatTransferCoefficient() {
  OS_ASSERT(setDouble(openstudio::Generator_FuelCell_StackCoolerFields::StackCogenerationExchangerNominalHeatTransferCoefficient, 0.0));
}

bool GeneratorFuelCellStackCooler_Impl::setStackCogenerationExchangerNominalHeatTransferCoefficientExponent(
  double stackCogenerationExchangerNominalHeatTransferCoefficientExponent) {
  const bool result =
    setDouble(openstudio::Generator_FuelCell_StackCoolerFields::StackCogenerationExchangerNominalHeatTransferCoefficientExponent,
              stackCogenerationExchangerNominalHeatTransferCoefficientExponent);
  OS_ASSERT(result);
  return result;
}

void GeneratorFuelCellStackCooler_Impl::resetStackCogenerationExchangerNominalHeatTransferCoefficientExponent() {
  OS_ASSERT(
    setDouble(openstudio::Generator_FuelCell_StackCoolerFields::StackCogenerationExchangerNominalHeatTransferCoefficientExponent, 0.0));
}

bool GeneratorFuelCellStackCooler_Impl::setStackCoolerPumpPower(double stackCoolerPumpPower) {
  const bool result = setDouble(openstudio::Generator_FuelCell_StackCoolerFields::StackCoolerPumpPower, stackCoolerPumpPower);
  OS_ASSERT(result);
  return result;
}

void GeneratorFuelCellStackCooler_Impl::resetStackCoolerPumpPower() {
  OS_ASSERT(setDouble(openstudio::Generator_FuelCell_StackCoolerFields::StackCoolerPumpPower, 0.0));
}

bool GeneratorFuelCellStackCooler_Impl::setStackCoolerPumpHeatLossFraction(double stackCoolerPumpHeatLossFraction) {
  return setDouble(openstudio::Generator_FuelCell_StackCoolerFields::StackCoolerPumpHeatLossFraction, stackCoolerPumpHeatLossFraction);
}

void GeneratorFuelCellStackCooler_Impl::resetStackCoolerPumpHeatLossFraction() {
  OS_ASSERT(setDouble(openstudio::Generator_FuelCell_StackCoolerFields::StackCoolerPumpHeatLossFraction, 0.0));
}

bool GeneratorFuelCellStackCooler_Impl::setStackAirCoolerFanCoefficientf0(double stackAirCoolerFanCoefficientf0) {
  const bool result =
    setDouble(openstudio::Generator_FuelCell_StackCoolerFields::StackAirCoolerFanCoefficientf0, stackAirCoolerFanCoefficientf0);
  OS_ASSERT(result);
  return result;
}

void GeneratorFuelCellStackCooler_Impl::resetStackAirCoolerFanCoefficientf0() {
  OS_ASSERT(setDouble(openstudio::Generator_FuelCell_StackCoolerFields::StackAirCoolerFanCoefficientf0, 0.0));
}

bool GeneratorFuelCellStackCooler_Impl::setStackAirCoolerFanCoefficientf1(double stackAirCoolerFanCoefficientf1) {
  const bool result =
    setDouble(openstudio::Generator_FuelCell_StackCoolerFields::StackAirCoolerFanCoefficientf1, stackAirCoolerFanCoefficientf1);
  OS_ASSERT(result);
  return result;
}

void GeneratorFuelCellStackCooler_Impl::resetStackAirCoolerFanCoefficientf1() {
  OS_ASSERT(setDouble(openstudio::Generator_FuelCell_StackCoolerFields::StackAirCoolerFanCoefficientf1, 0.0));
}

bool GeneratorFuelCellStackCooler_Impl::setStackAirCoolerFanCoefficientf2(double stackAirCoolerFanCoefficientf2) {
  const bool result =
    setDouble(openstudio::Generator_FuelCell_StackCoolerFields::StackAirCoolerFanCoefficientf2, stackAirCoolerFanCoefficientf2);
  OS_ASSERT(result);
  return result;
}

void GeneratorFuelCellStackCooler_Impl::resetStackAirCoolerFanCoefficientf2() {
  OS_ASSERT(setDouble(openstudio::Generator_FuelCell_StackCoolerFields::StackAirCoolerFanCoefficientf2, 0.0));
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
