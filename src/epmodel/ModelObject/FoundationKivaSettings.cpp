/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "FoundationKivaSettings.hpp"
#include "FoundationKivaSettings_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/Foundation_Kiva_Settings_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

FoundationKivaSettings::FoundationKivaSettings(const Model& model) : ModelObject(FoundationKivaSettings::iddObjectType(), model) {}

FoundationKivaSettings::FoundationKivaSettings(std::shared_ptr<detail::FoundationKivaSettings_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType FoundationKivaSettings::iddObjectType() {
  return IddObjectType::Foundation_Kiva_Settings;
}

std::vector<std::string> FoundationKivaSettings::deepGroundBoundaryConditionValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::Foundation_Kiva_SettingsFields::DeepGroundBoundaryCondition);
}

std::vector<std::string> FoundationKivaSettings::simulationTimestepValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::Foundation_Kiva_SettingsFields::SimulationTimestep);
}

double FoundationKivaSettings::soilConductivity() const {
  return getImpl<detail::FoundationKivaSettings_Impl>()->soilConductivity();
}

bool FoundationKivaSettings::isSoilConductivityDefaulted() const {
  return getImpl<detail::FoundationKivaSettings_Impl>()->isSoilConductivityDefaulted();
}

bool FoundationKivaSettings::setSoilConductivity(double soilConductivity) {
  return getImpl<detail::FoundationKivaSettings_Impl>()->setSoilConductivity(soilConductivity);
}

void FoundationKivaSettings::resetSoilConductivity() {
  getImpl<detail::FoundationKivaSettings_Impl>()->resetSoilConductivity();
}

double FoundationKivaSettings::soilDensity() const {
  return getImpl<detail::FoundationKivaSettings_Impl>()->soilDensity();
}

bool FoundationKivaSettings::isSoilDensityDefaulted() const {
  return getImpl<detail::FoundationKivaSettings_Impl>()->isSoilDensityDefaulted();
}

bool FoundationKivaSettings::setSoilDensity(double soilDensity) {
  return getImpl<detail::FoundationKivaSettings_Impl>()->setSoilDensity(soilDensity);
}

void FoundationKivaSettings::resetSoilDensity() {
  getImpl<detail::FoundationKivaSettings_Impl>()->resetSoilDensity();
}

double FoundationKivaSettings::soilSpecificHeat() const {
  return getImpl<detail::FoundationKivaSettings_Impl>()->soilSpecificHeat();
}

bool FoundationKivaSettings::isSoilSpecificHeatDefaulted() const {
  return getImpl<detail::FoundationKivaSettings_Impl>()->isSoilSpecificHeatDefaulted();
}

bool FoundationKivaSettings::setSoilSpecificHeat(double soilSpecificHeat) {
  return getImpl<detail::FoundationKivaSettings_Impl>()->setSoilSpecificHeat(soilSpecificHeat);
}

void FoundationKivaSettings::resetSoilSpecificHeat() {
  getImpl<detail::FoundationKivaSettings_Impl>()->resetSoilSpecificHeat();
}

double FoundationKivaSettings::groundSolarAbsorptivity() const {
  return getImpl<detail::FoundationKivaSettings_Impl>()->groundSolarAbsorptivity();
}

bool FoundationKivaSettings::isGroundSolarAbsorptivityDefaulted() const {
  return getImpl<detail::FoundationKivaSettings_Impl>()->isGroundSolarAbsorptivityDefaulted();
}

bool FoundationKivaSettings::setGroundSolarAbsorptivity(double groundSolarAbsorptivity) {
  return getImpl<detail::FoundationKivaSettings_Impl>()->setGroundSolarAbsorptivity(groundSolarAbsorptivity);
}

void FoundationKivaSettings::resetGroundSolarAbsorptivity() {
  getImpl<detail::FoundationKivaSettings_Impl>()->resetGroundSolarAbsorptivity();
}

double FoundationKivaSettings::groundThermalAbsorptivity() const {
  return getImpl<detail::FoundationKivaSettings_Impl>()->groundThermalAbsorptivity();
}

bool FoundationKivaSettings::isGroundThermalAbsorptivityDefaulted() const {
  return getImpl<detail::FoundationKivaSettings_Impl>()->isGroundThermalAbsorptivityDefaulted();
}

bool FoundationKivaSettings::setGroundThermalAbsorptivity(double groundThermalAbsorptivity) {
  return getImpl<detail::FoundationKivaSettings_Impl>()->setGroundThermalAbsorptivity(groundThermalAbsorptivity);
}

void FoundationKivaSettings::resetGroundThermalAbsorptivity() {
  getImpl<detail::FoundationKivaSettings_Impl>()->resetGroundThermalAbsorptivity();
}

double FoundationKivaSettings::groundSurfaceRoughness() const {
  return getImpl<detail::FoundationKivaSettings_Impl>()->groundSurfaceRoughness();
}

bool FoundationKivaSettings::isGroundSurfaceRoughnessDefaulted() const {
  return getImpl<detail::FoundationKivaSettings_Impl>()->isGroundSurfaceRoughnessDefaulted();
}

bool FoundationKivaSettings::setGroundSurfaceRoughness(double groundSurfaceRoughness) {
  return getImpl<detail::FoundationKivaSettings_Impl>()->setGroundSurfaceRoughness(groundSurfaceRoughness);
}

void FoundationKivaSettings::resetGroundSurfaceRoughness() {
  getImpl<detail::FoundationKivaSettings_Impl>()->resetGroundSurfaceRoughness();
}

double FoundationKivaSettings::farFieldWidth() const {
  return getImpl<detail::FoundationKivaSettings_Impl>()->farFieldWidth();
}

bool FoundationKivaSettings::isFarFieldWidthDefaulted() const {
  return getImpl<detail::FoundationKivaSettings_Impl>()->isFarFieldWidthDefaulted();
}

bool FoundationKivaSettings::setFarFieldWidth(double farFieldWidth) {
  return getImpl<detail::FoundationKivaSettings_Impl>()->setFarFieldWidth(farFieldWidth);
}

void FoundationKivaSettings::resetFarFieldWidth() {
  getImpl<detail::FoundationKivaSettings_Impl>()->resetFarFieldWidth();
}

std::string FoundationKivaSettings::deepGroundBoundaryCondition() const {
  return getImpl<detail::FoundationKivaSettings_Impl>()->deepGroundBoundaryCondition();
}

bool FoundationKivaSettings::isDeepGroundBoundaryConditionAutoselected() {
  return getImpl<detail::FoundationKivaSettings_Impl>()->isDeepGroundBoundaryConditionAutoselected();
}

bool FoundationKivaSettings::setDeepGroundBoundaryCondition(const std::string& deepGroundBoundaryCondition) {
  return getImpl<detail::FoundationKivaSettings_Impl>()->setDeepGroundBoundaryCondition(deepGroundBoundaryCondition);
}

void FoundationKivaSettings::resetDeepGroundBoundaryCondition() {
  getImpl<detail::FoundationKivaSettings_Impl>()->resetDeepGroundBoundaryCondition();
}

boost::optional<double> FoundationKivaSettings::deepGroundDepth() {
  return getImpl<detail::FoundationKivaSettings_Impl>()->deepGroundDepth();
}

bool FoundationKivaSettings::isDeepGroundDepthAutocalculated() {
  return getImpl<detail::FoundationKivaSettings_Impl>()->isDeepGroundDepthAutocalculated();
}

bool FoundationKivaSettings::setDeepGroundDepth(double deepGroundDepth) {
  return getImpl<detail::FoundationKivaSettings_Impl>()->setDeepGroundDepth(deepGroundDepth);
}

void FoundationKivaSettings::autocalculateDeepGroundDepth() {
  getImpl<detail::FoundationKivaSettings_Impl>()->autocalculateDeepGroundDepth();
}

double FoundationKivaSettings::minimumCellDimension() const {
  return getImpl<detail::FoundationKivaSettings_Impl>()->minimumCellDimension();
}

bool FoundationKivaSettings::isMinimumCellDimensionDefaulted() const {
  return getImpl<detail::FoundationKivaSettings_Impl>()->isMinimumCellDimensionDefaulted();
}

bool FoundationKivaSettings::setMinimumCellDimension(double minimumCellDimension) {
  return getImpl<detail::FoundationKivaSettings_Impl>()->setMinimumCellDimension(minimumCellDimension);
}

void FoundationKivaSettings::resetMinimumCellDimension() {
  getImpl<detail::FoundationKivaSettings_Impl>()->resetMinimumCellDimension();
}

double FoundationKivaSettings::maximumCellGrowthCoefficient() const {
  return getImpl<detail::FoundationKivaSettings_Impl>()->maximumCellGrowthCoefficient();
}

bool FoundationKivaSettings::isMaximumCellGrowthCoefficientDefaulted() const {
  return getImpl<detail::FoundationKivaSettings_Impl>()->isMaximumCellGrowthCoefficientDefaulted();
}

bool FoundationKivaSettings::setMaximumCellGrowthCoefficient(double maximumCellGrowthCoefficient) {
  return getImpl<detail::FoundationKivaSettings_Impl>()->setMaximumCellGrowthCoefficient(maximumCellGrowthCoefficient);
}

void FoundationKivaSettings::resetMaximumCellGrowthCoefficient() {
  getImpl<detail::FoundationKivaSettings_Impl>()->resetMaximumCellGrowthCoefficient();
}

std::string FoundationKivaSettings::simulationTimestep() const {
  return getImpl<detail::FoundationKivaSettings_Impl>()->simulationTimestep();
}

bool FoundationKivaSettings::isSimulationTimestepDefaulted() const {
  return getImpl<detail::FoundationKivaSettings_Impl>()->isSimulationTimestepDefaulted();
}

bool FoundationKivaSettings::setSimulationTimestep(const std::string& simulationTimestep) {
  return getImpl<detail::FoundationKivaSettings_Impl>()->setSimulationTimestep(simulationTimestep);
}

void FoundationKivaSettings::resetSimulationTimestep() {
  getImpl<detail::FoundationKivaSettings_Impl>()->resetSimulationTimestep();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

double FoundationKivaSettings_Impl::soilConductivity() const {
  const auto value = getDouble(openstudio::Foundation_Kiva_SettingsFields::SoilConductivity, true);
  OS_ASSERT(value);
  return *value;
}

bool FoundationKivaSettings_Impl::isSoilConductivityDefaulted() const {
  return isEmpty(openstudio::Foundation_Kiva_SettingsFields::SoilConductivity);
}

bool FoundationKivaSettings_Impl::setSoilConductivity(double soilConductivity) {
  const bool result = setDouble(openstudio::Foundation_Kiva_SettingsFields::SoilConductivity, soilConductivity);
  OS_ASSERT(result);
  return result;
}

void FoundationKivaSettings_Impl::resetSoilConductivity() {
  OS_ASSERT(setString(openstudio::Foundation_Kiva_SettingsFields::SoilConductivity, ""));
}

double FoundationKivaSettings_Impl::soilDensity() const {
  const auto value = getDouble(openstudio::Foundation_Kiva_SettingsFields::SoilDensity, true);
  OS_ASSERT(value);
  return *value;
}

bool FoundationKivaSettings_Impl::isSoilDensityDefaulted() const {
  return isEmpty(openstudio::Foundation_Kiva_SettingsFields::SoilDensity);
}

bool FoundationKivaSettings_Impl::setSoilDensity(double soilDensity) {
  const bool result = setDouble(openstudio::Foundation_Kiva_SettingsFields::SoilDensity, soilDensity);
  OS_ASSERT(result);
  return result;
}

void FoundationKivaSettings_Impl::resetSoilDensity() {
  OS_ASSERT(setString(openstudio::Foundation_Kiva_SettingsFields::SoilDensity, ""));
}

double FoundationKivaSettings_Impl::soilSpecificHeat() const {
  const auto value = getDouble(openstudio::Foundation_Kiva_SettingsFields::SoilSpecificHeat, true);
  OS_ASSERT(value);
  return *value;
}

bool FoundationKivaSettings_Impl::isSoilSpecificHeatDefaulted() const {
  return isEmpty(openstudio::Foundation_Kiva_SettingsFields::SoilSpecificHeat);
}

bool FoundationKivaSettings_Impl::setSoilSpecificHeat(double soilSpecificHeat) {
  const bool result = setDouble(openstudio::Foundation_Kiva_SettingsFields::SoilSpecificHeat, soilSpecificHeat);
  OS_ASSERT(result);
  return result;
}

void FoundationKivaSettings_Impl::resetSoilSpecificHeat() {
  OS_ASSERT(setString(openstudio::Foundation_Kiva_SettingsFields::SoilSpecificHeat, ""));
}

double FoundationKivaSettings_Impl::groundSolarAbsorptivity() const {
  const auto value = getDouble(openstudio::Foundation_Kiva_SettingsFields::GroundSolarAbsorptivity, true);
  OS_ASSERT(value);
  return *value;
}

bool FoundationKivaSettings_Impl::isGroundSolarAbsorptivityDefaulted() const {
  return isEmpty(openstudio::Foundation_Kiva_SettingsFields::GroundSolarAbsorptivity);
}

bool FoundationKivaSettings_Impl::setGroundSolarAbsorptivity(double groundSolarAbsorptivity) {
  const bool result = setDouble(openstudio::Foundation_Kiva_SettingsFields::GroundSolarAbsorptivity, groundSolarAbsorptivity);
  OS_ASSERT(result);
  return result;
}

void FoundationKivaSettings_Impl::resetGroundSolarAbsorptivity() {
  OS_ASSERT(setString(openstudio::Foundation_Kiva_SettingsFields::GroundSolarAbsorptivity, ""));
}

double FoundationKivaSettings_Impl::groundThermalAbsorptivity() const {
  const auto value = getDouble(openstudio::Foundation_Kiva_SettingsFields::GroundThermalAbsorptivity, true);
  OS_ASSERT(value);
  return *value;
}

bool FoundationKivaSettings_Impl::isGroundThermalAbsorptivityDefaulted() const {
  return isEmpty(openstudio::Foundation_Kiva_SettingsFields::GroundThermalAbsorptivity);
}

bool FoundationKivaSettings_Impl::setGroundThermalAbsorptivity(double groundThermalAbsorptivity) {
  const bool result = setDouble(openstudio::Foundation_Kiva_SettingsFields::GroundThermalAbsorptivity, groundThermalAbsorptivity);
  OS_ASSERT(result);
  return result;
}

void FoundationKivaSettings_Impl::resetGroundThermalAbsorptivity() {
  OS_ASSERT(setString(openstudio::Foundation_Kiva_SettingsFields::GroundThermalAbsorptivity, ""));
}

double FoundationKivaSettings_Impl::groundSurfaceRoughness() const {
  const auto value = getDouble(openstudio::Foundation_Kiva_SettingsFields::GroundSurfaceRoughness, true);
  OS_ASSERT(value);
  return *value;
}

bool FoundationKivaSettings_Impl::isGroundSurfaceRoughnessDefaulted() const {
  return isEmpty(openstudio::Foundation_Kiva_SettingsFields::GroundSurfaceRoughness);
}

bool FoundationKivaSettings_Impl::setGroundSurfaceRoughness(double groundSurfaceRoughness) {
  const bool result = setDouble(openstudio::Foundation_Kiva_SettingsFields::GroundSurfaceRoughness, groundSurfaceRoughness);
  OS_ASSERT(result);
  return result;
}

void FoundationKivaSettings_Impl::resetGroundSurfaceRoughness() {
  OS_ASSERT(setString(openstudio::Foundation_Kiva_SettingsFields::GroundSurfaceRoughness, ""));
}

double FoundationKivaSettings_Impl::farFieldWidth() const {
  const auto value = getDouble(openstudio::Foundation_Kiva_SettingsFields::FarFieldWidth, true);
  OS_ASSERT(value);
  return *value;
}

bool FoundationKivaSettings_Impl::isFarFieldWidthDefaulted() const {
  return isEmpty(openstudio::Foundation_Kiva_SettingsFields::FarFieldWidth);
}

bool FoundationKivaSettings_Impl::setFarFieldWidth(double farFieldWidth) {
  const bool result = setDouble(openstudio::Foundation_Kiva_SettingsFields::FarFieldWidth, farFieldWidth);
  OS_ASSERT(result);
  return result;
}

void FoundationKivaSettings_Impl::resetFarFieldWidth() {
  OS_ASSERT(setString(openstudio::Foundation_Kiva_SettingsFields::FarFieldWidth, ""));
}

std::string FoundationKivaSettings_Impl::deepGroundBoundaryCondition() const {
  const auto value = getString(openstudio::Foundation_Kiva_SettingsFields::DeepGroundBoundaryCondition, true);
  OS_ASSERT(value);
  return *value;
}

bool FoundationKivaSettings_Impl::isDeepGroundBoundaryConditionAutoselected() {
  const auto value = getString(openstudio::Foundation_Kiva_SettingsFields::DeepGroundBoundaryCondition, true);
  OS_ASSERT(value);
  return openstudio::istringEqual(*value, "Autoselect");
}

bool FoundationKivaSettings_Impl::setDeepGroundBoundaryCondition(const std::string& deepGroundBoundaryCondition) {
  return setString(openstudio::Foundation_Kiva_SettingsFields::DeepGroundBoundaryCondition, deepGroundBoundaryCondition);
}

void FoundationKivaSettings_Impl::resetDeepGroundBoundaryCondition() {
  OS_ASSERT(setString(openstudio::Foundation_Kiva_SettingsFields::DeepGroundBoundaryCondition, ""));
}

boost::optional<double> FoundationKivaSettings_Impl::deepGroundDepth() {
  return getDouble(openstudio::Foundation_Kiva_SettingsFields::DeepGroundDepth, true);
}

bool FoundationKivaSettings_Impl::isDeepGroundDepthAutocalculated() {
  if (const auto value = getString(openstudio::Foundation_Kiva_SettingsFields::DeepGroundDepth, true)) {
    return openstudio::istringEqual(*value, "Autocalculate");
  }
  return false;
}

bool FoundationKivaSettings_Impl::setDeepGroundDepth(double deepGroundDepth) {
  const bool result = setDouble(openstudio::Foundation_Kiva_SettingsFields::DeepGroundDepth, deepGroundDepth);
  OS_ASSERT(result);
  return result;
}

void FoundationKivaSettings_Impl::autocalculateDeepGroundDepth() {
  OS_ASSERT(setString(openstudio::Foundation_Kiva_SettingsFields::DeepGroundDepth, "Autocalculate"));
}

double FoundationKivaSettings_Impl::minimumCellDimension() const {
  const auto value = getDouble(openstudio::Foundation_Kiva_SettingsFields::MinimumCellDimension, true);
  OS_ASSERT(value);
  return *value;
}

bool FoundationKivaSettings_Impl::isMinimumCellDimensionDefaulted() const {
  return isEmpty(openstudio::Foundation_Kiva_SettingsFields::MinimumCellDimension);
}

bool FoundationKivaSettings_Impl::setMinimumCellDimension(double minimumCellDimension) {
  const bool result = setDouble(openstudio::Foundation_Kiva_SettingsFields::MinimumCellDimension, minimumCellDimension);
  OS_ASSERT(result);
  return result;
}

void FoundationKivaSettings_Impl::resetMinimumCellDimension() {
  OS_ASSERT(setString(openstudio::Foundation_Kiva_SettingsFields::MinimumCellDimension, ""));
}

double FoundationKivaSettings_Impl::maximumCellGrowthCoefficient() const {
  const auto value = getDouble(openstudio::Foundation_Kiva_SettingsFields::MaximumCellGrowthCoefficient, true);
  OS_ASSERT(value);
  return *value;
}

bool FoundationKivaSettings_Impl::isMaximumCellGrowthCoefficientDefaulted() const {
  return isEmpty(openstudio::Foundation_Kiva_SettingsFields::MaximumCellGrowthCoefficient);
}

bool FoundationKivaSettings_Impl::setMaximumCellGrowthCoefficient(double maximumCellGrowthCoefficient) {
  const bool result = setDouble(openstudio::Foundation_Kiva_SettingsFields::MaximumCellGrowthCoefficient, maximumCellGrowthCoefficient);
  OS_ASSERT(result);
  return result;
}

void FoundationKivaSettings_Impl::resetMaximumCellGrowthCoefficient() {
  OS_ASSERT(setString(openstudio::Foundation_Kiva_SettingsFields::MaximumCellGrowthCoefficient, ""));
}

std::string FoundationKivaSettings_Impl::simulationTimestep() const {
  const auto value = getString(openstudio::Foundation_Kiva_SettingsFields::SimulationTimestep, true);
  OS_ASSERT(value);
  return *value;
}

bool FoundationKivaSettings_Impl::isSimulationTimestepDefaulted() const {
  const auto value = getString(openstudio::Foundation_Kiva_SettingsFields::SimulationTimestep, true);
  OS_ASSERT(value);
  return openstudio::istringEqual(*value, "Hourly");
}

bool FoundationKivaSettings_Impl::setSimulationTimestep(const std::string& simulationTimestep) {
  return setString(openstudio::Foundation_Kiva_SettingsFields::SimulationTimestep, simulationTimestep);
}

void FoundationKivaSettings_Impl::resetSimulationTimestep() {
  OS_ASSERT(setString(openstudio::Foundation_Kiva_SettingsFields::SimulationTimestep, ""));
}

std::vector<std::string> FoundationKivaSettings_Impl::deepGroundBoundaryConditionValues() const {
  return openstudio::epmodel::FoundationKivaSettings::deepGroundBoundaryConditionValues();
}

std::vector<std::string> FoundationKivaSettings_Impl::simulationTimestepValues() const {
  return openstudio::epmodel::FoundationKivaSettings::simulationTimestepValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
