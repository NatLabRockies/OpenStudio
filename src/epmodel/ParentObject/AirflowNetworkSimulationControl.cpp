/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ParentObject/AirflowNetworkSimulationControl.hpp"
#include "ParentObject/AirflowNetworkSimulationControl_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/AirflowNetwork_SimulationControl_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

AirflowNetworkSimulationControl::AirflowNetworkSimulationControl(const Model& model)
  : ModelObject(AirflowNetworkSimulationControl::iddObjectType(), model) {}

AirflowNetworkSimulationControl::AirflowNetworkSimulationControl(std::shared_ptr<detail::AirflowNetworkSimulationControl_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType AirflowNetworkSimulationControl::iddObjectType() {
  return IddObjectType::AirflowNetwork_SimulationControl;
}

std::vector<std::string> AirflowNetworkSimulationControl::airflowNetworkControlValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::AirflowNetwork_SimulationControlFields::AirflowNetworkControl);
}

std::vector<std::string> AirflowNetworkSimulationControl::windPressureCoefficientTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::AirflowNetwork_SimulationControlFields::WindPressureCoefficientType);
}

std::vector<std::string> AirflowNetworkSimulationControl::heightSelectionforLocalWindPressureCalculationValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::AirflowNetwork_SimulationControlFields::HeightSelectionforLocalWindPressureCalculation);
}

std::vector<std::string> AirflowNetworkSimulationControl::buildingTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::AirflowNetwork_SimulationControlFields::BuildingType);
}

std::vector<std::string> AirflowNetworkSimulationControl::initializationTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::AirflowNetwork_SimulationControlFields::InitializationType);
}

std::vector<std::string> AirflowNetworkSimulationControl::solverValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::AirflowNetwork_SimulationControlFields::Solver);
}

std::string AirflowNetworkSimulationControl::airflowNetworkControl() const {
  return getImpl<detail::AirflowNetworkSimulationControl_Impl>()->airflowNetworkControl();
}

bool AirflowNetworkSimulationControl::isAirflowNetworkControlDefaulted() const {
  return getImpl<detail::AirflowNetworkSimulationControl_Impl>()->isAirflowNetworkControlDefaulted();
}

bool AirflowNetworkSimulationControl::setAirflowNetworkControl(const std::string& airflowNetworkControl) {
  return getImpl<detail::AirflowNetworkSimulationControl_Impl>()->setAirflowNetworkControl(airflowNetworkControl);
}

void AirflowNetworkSimulationControl::resetAirflowNetworkControl() {
  getImpl<detail::AirflowNetworkSimulationControl_Impl>()->resetAirflowNetworkControl();
}

std::string AirflowNetworkSimulationControl::windPressureCoefficientType() const {
  return getImpl<detail::AirflowNetworkSimulationControl_Impl>()->windPressureCoefficientType();
}

bool AirflowNetworkSimulationControl::isWindPressureCoefficientTypeDefaulted() const {
  return getImpl<detail::AirflowNetworkSimulationControl_Impl>()->isWindPressureCoefficientTypeDefaulted();
}

bool AirflowNetworkSimulationControl::setWindPressureCoefficientType(const std::string& windPressureCoefficientType) {
  return getImpl<detail::AirflowNetworkSimulationControl_Impl>()->setWindPressureCoefficientType(windPressureCoefficientType);
}

void AirflowNetworkSimulationControl::resetWindPressureCoefficientType() {
  getImpl<detail::AirflowNetworkSimulationControl_Impl>()->resetWindPressureCoefficientType();
}

std::string AirflowNetworkSimulationControl::heightSelectionforLocalWindPressureCalculation() const {
  return getImpl<detail::AirflowNetworkSimulationControl_Impl>()->heightSelectionforLocalWindPressureCalculation();
}

bool AirflowNetworkSimulationControl::isHeightSelectionforLocalWindPressureCalculationDefaulted() const {
  return getImpl<detail::AirflowNetworkSimulationControl_Impl>()->isHeightSelectionforLocalWindPressureCalculationDefaulted();
}

bool AirflowNetworkSimulationControl::setHeightSelectionforLocalWindPressureCalculation(
  const std::string& heightSelectionforLocalWindPressureCalculation) {
  return getImpl<detail::AirflowNetworkSimulationControl_Impl>()->setHeightSelectionforLocalWindPressureCalculation(
    heightSelectionforLocalWindPressureCalculation);
}

void AirflowNetworkSimulationControl::resetHeightSelectionforLocalWindPressureCalculation() {
  getImpl<detail::AirflowNetworkSimulationControl_Impl>()->resetHeightSelectionforLocalWindPressureCalculation();
}

std::string AirflowNetworkSimulationControl::buildingType() const {
  return getImpl<detail::AirflowNetworkSimulationControl_Impl>()->buildingType();
}

bool AirflowNetworkSimulationControl::isBuildingTypeDefaulted() const {
  return getImpl<detail::AirflowNetworkSimulationControl_Impl>()->isBuildingTypeDefaulted();
}

bool AirflowNetworkSimulationControl::setBuildingType(const std::string& buildingType) {
  return getImpl<detail::AirflowNetworkSimulationControl_Impl>()->setBuildingType(buildingType);
}

void AirflowNetworkSimulationControl::resetBuildingType() {
  getImpl<detail::AirflowNetworkSimulationControl_Impl>()->resetBuildingType();
}

int AirflowNetworkSimulationControl::maximumNumberofIterations() const {
  return getImpl<detail::AirflowNetworkSimulationControl_Impl>()->maximumNumberofIterations();
}

bool AirflowNetworkSimulationControl::isMaximumNumberofIterationsDefaulted() const {
  return getImpl<detail::AirflowNetworkSimulationControl_Impl>()->isMaximumNumberofIterationsDefaulted();
}

bool AirflowNetworkSimulationControl::setMaximumNumberofIterations(int maximumNumberofIterations) {
  return getImpl<detail::AirflowNetworkSimulationControl_Impl>()->setMaximumNumberofIterations(maximumNumberofIterations);
}

void AirflowNetworkSimulationControl::resetMaximumNumberofIterations() {
  getImpl<detail::AirflowNetworkSimulationControl_Impl>()->resetMaximumNumberofIterations();
}

std::string AirflowNetworkSimulationControl::initializationType() const {
  return getImpl<detail::AirflowNetworkSimulationControl_Impl>()->initializationType();
}

bool AirflowNetworkSimulationControl::isInitializationTypeDefaulted() const {
  return getImpl<detail::AirflowNetworkSimulationControl_Impl>()->isInitializationTypeDefaulted();
}

bool AirflowNetworkSimulationControl::setInitializationType(const std::string& initializationType) {
  return getImpl<detail::AirflowNetworkSimulationControl_Impl>()->setInitializationType(initializationType);
}

void AirflowNetworkSimulationControl::resetInitializationType() {
  getImpl<detail::AirflowNetworkSimulationControl_Impl>()->resetInitializationType();
}

double AirflowNetworkSimulationControl::relativeAirflowConvergenceTolerance() const {
  return getImpl<detail::AirflowNetworkSimulationControl_Impl>()->relativeAirflowConvergenceTolerance();
}

bool AirflowNetworkSimulationControl::isRelativeAirflowConvergenceToleranceDefaulted() const {
  return getImpl<detail::AirflowNetworkSimulationControl_Impl>()->isRelativeAirflowConvergenceToleranceDefaulted();
}

bool AirflowNetworkSimulationControl::setRelativeAirflowConvergenceTolerance(double relativeAirflowConvergenceTolerance) {
  return getImpl<detail::AirflowNetworkSimulationControl_Impl>()->setRelativeAirflowConvergenceTolerance(relativeAirflowConvergenceTolerance);
}

void AirflowNetworkSimulationControl::resetRelativeAirflowConvergenceTolerance() {
  getImpl<detail::AirflowNetworkSimulationControl_Impl>()->resetRelativeAirflowConvergenceTolerance();
}

double AirflowNetworkSimulationControl::absoluteAirflowConvergenceTolerance() const {
  return getImpl<detail::AirflowNetworkSimulationControl_Impl>()->absoluteAirflowConvergenceTolerance();
}

bool AirflowNetworkSimulationControl::isAbsoluteAirflowConvergenceToleranceDefaulted() const {
  return getImpl<detail::AirflowNetworkSimulationControl_Impl>()->isAbsoluteAirflowConvergenceToleranceDefaulted();
}

bool AirflowNetworkSimulationControl::setAbsoluteAirflowConvergenceTolerance(double absoluteAirflowConvergenceTolerance) {
  return getImpl<detail::AirflowNetworkSimulationControl_Impl>()->setAbsoluteAirflowConvergenceTolerance(absoluteAirflowConvergenceTolerance);
}

void AirflowNetworkSimulationControl::resetAbsoluteAirflowConvergenceTolerance() {
  getImpl<detail::AirflowNetworkSimulationControl_Impl>()->resetAbsoluteAirflowConvergenceTolerance();
}

double AirflowNetworkSimulationControl::convergenceAccelerationLimit() const {
  return getImpl<detail::AirflowNetworkSimulationControl_Impl>()->convergenceAccelerationLimit();
}

bool AirflowNetworkSimulationControl::isConvergenceAccelerationLimitDefaulted() const {
  return getImpl<detail::AirflowNetworkSimulationControl_Impl>()->isConvergenceAccelerationLimitDefaulted();
}

bool AirflowNetworkSimulationControl::setConvergenceAccelerationLimit(double convergenceAccelerationLimit) {
  return getImpl<detail::AirflowNetworkSimulationControl_Impl>()->setConvergenceAccelerationLimit(convergenceAccelerationLimit);
}

void AirflowNetworkSimulationControl::resetConvergenceAccelerationLimit() {
  getImpl<detail::AirflowNetworkSimulationControl_Impl>()->resetConvergenceAccelerationLimit();
}

double AirflowNetworkSimulationControl::azimuthAngleofLongAxisofBuilding() const {
  return getImpl<detail::AirflowNetworkSimulationControl_Impl>()->azimuthAngleofLongAxisofBuilding();
}

bool AirflowNetworkSimulationControl::isAzimuthAngleofLongAxisofBuildingDefaulted() const {
  return getImpl<detail::AirflowNetworkSimulationControl_Impl>()->isAzimuthAngleofLongAxisofBuildingDefaulted();
}

bool AirflowNetworkSimulationControl::setAzimuthAngleofLongAxisofBuilding(double azimuthAngleofLongAxisofBuilding) {
  return getImpl<detail::AirflowNetworkSimulationControl_Impl>()->setAzimuthAngleofLongAxisofBuilding(azimuthAngleofLongAxisofBuilding);
}

void AirflowNetworkSimulationControl::resetAzimuthAngleofLongAxisofBuilding() {
  getImpl<detail::AirflowNetworkSimulationControl_Impl>()->resetAzimuthAngleofLongAxisofBuilding();
}

double AirflowNetworkSimulationControl::ratioofBuildingWidthAlongShortAxistoWidthAlongLongAxis() const {
  return getImpl<detail::AirflowNetworkSimulationControl_Impl>()->ratioofBuildingWidthAlongShortAxistoWidthAlongLongAxis();
}

bool AirflowNetworkSimulationControl::isRatioofBuildingWidthAlongShortAxistoWidthAlongLongAxisDefaulted() const {
  return getImpl<detail::AirflowNetworkSimulationControl_Impl>()->isRatioofBuildingWidthAlongShortAxistoWidthAlongLongAxisDefaulted();
}

bool AirflowNetworkSimulationControl::setRatioofBuildingWidthAlongShortAxistoWidthAlongLongAxis(
  double ratioofBuildingWidthAlongShortAxistoWidthAlongLongAxis) {
  return getImpl<detail::AirflowNetworkSimulationControl_Impl>()->setRatioofBuildingWidthAlongShortAxistoWidthAlongLongAxis(
    ratioofBuildingWidthAlongShortAxistoWidthAlongLongAxis);
}

void AirflowNetworkSimulationControl::resetRatioofBuildingWidthAlongShortAxistoWidthAlongLongAxis() {
  getImpl<detail::AirflowNetworkSimulationControl_Impl>()->resetRatioofBuildingWidthAlongShortAxistoWidthAlongLongAxis();
}

bool AirflowNetworkSimulationControl::heightDependenceofExternalNodeTemperature() const {
  return getImpl<detail::AirflowNetworkSimulationControl_Impl>()->heightDependenceofExternalNodeTemperature();
}

bool AirflowNetworkSimulationControl::isHeightDependenceofExternalNodeTemperatureDefaulted() const {
  return getImpl<detail::AirflowNetworkSimulationControl_Impl>()->isHeightDependenceofExternalNodeTemperatureDefaulted();
}

void AirflowNetworkSimulationControl::setHeightDependenceofExternalNodeTemperature(bool heightDependenceofExternalNodeTemperature) {
  getImpl<detail::AirflowNetworkSimulationControl_Impl>()->setHeightDependenceofExternalNodeTemperature(heightDependenceofExternalNodeTemperature);
}

void AirflowNetworkSimulationControl::resetHeightDependenceofExternalNodeTemperature() {
  getImpl<detail::AirflowNetworkSimulationControl_Impl>()->resetHeightDependenceofExternalNodeTemperature();
}

std::string AirflowNetworkSimulationControl::solver() const {
  return getImpl<detail::AirflowNetworkSimulationControl_Impl>()->solver();
}

bool AirflowNetworkSimulationControl::isSolverDefaulted() const {
  return getImpl<detail::AirflowNetworkSimulationControl_Impl>()->isSolverDefaulted();
}

bool AirflowNetworkSimulationControl::setSolver(const std::string& solver) {
  return getImpl<detail::AirflowNetworkSimulationControl_Impl>()->setSolver(solver);
}

void AirflowNetworkSimulationControl::resetSolver() {
  getImpl<detail::AirflowNetworkSimulationControl_Impl>()->resetSolver();
}

bool AirflowNetworkSimulationControl::allowUnsupportedZoneEquipment() const {
  return getImpl<detail::AirflowNetworkSimulationControl_Impl>()->allowUnsupportedZoneEquipment();
}

bool AirflowNetworkSimulationControl::isAllowUnsupportedZoneEquipmentDefaulted() const {
  return getImpl<detail::AirflowNetworkSimulationControl_Impl>()->isAllowUnsupportedZoneEquipmentDefaulted();
}

void AirflowNetworkSimulationControl::setAllowUnsupportedZoneEquipment(bool allowUnsupportedZoneEquipment) {
  getImpl<detail::AirflowNetworkSimulationControl_Impl>()->setAllowUnsupportedZoneEquipment(allowUnsupportedZoneEquipment);
}

void AirflowNetworkSimulationControl::resetAllowUnsupportedZoneEquipment() {
  getImpl<detail::AirflowNetworkSimulationControl_Impl>()->resetAllowUnsupportedZoneEquipment();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

std::string AirflowNetworkSimulationControl_Impl::airflowNetworkControl() const {
  const auto value = getString(openstudio::AirflowNetwork_SimulationControlFields::AirflowNetworkControl, true);
  OS_ASSERT(value);
  return *value;
}

bool AirflowNetworkSimulationControl_Impl::isAirflowNetworkControlDefaulted() const {
  return isEmpty(openstudio::AirflowNetwork_SimulationControlFields::AirflowNetworkControl);
}

bool AirflowNetworkSimulationControl_Impl::setAirflowNetworkControl(const std::string& airflowNetworkControl) {
  return setString(openstudio::AirflowNetwork_SimulationControlFields::AirflowNetworkControl, airflowNetworkControl);
}

void AirflowNetworkSimulationControl_Impl::resetAirflowNetworkControl() {
  OS_ASSERT(setString(openstudio::AirflowNetwork_SimulationControlFields::AirflowNetworkControl, ""));
}

std::string AirflowNetworkSimulationControl_Impl::windPressureCoefficientType() const {
  const auto value = getString(openstudio::AirflowNetwork_SimulationControlFields::WindPressureCoefficientType, true);
  OS_ASSERT(value);
  return *value;
}

bool AirflowNetworkSimulationControl_Impl::isWindPressureCoefficientTypeDefaulted() const {
  return isEmpty(openstudio::AirflowNetwork_SimulationControlFields::WindPressureCoefficientType);
}

bool AirflowNetworkSimulationControl_Impl::setWindPressureCoefficientType(const std::string& windPressureCoefficientType) {
  return setString(openstudio::AirflowNetwork_SimulationControlFields::WindPressureCoefficientType, windPressureCoefficientType);
}

void AirflowNetworkSimulationControl_Impl::resetWindPressureCoefficientType() {
  OS_ASSERT(setString(openstudio::AirflowNetwork_SimulationControlFields::WindPressureCoefficientType, ""));
}

std::string AirflowNetworkSimulationControl_Impl::heightSelectionforLocalWindPressureCalculation() const {
  const auto value = getString(openstudio::AirflowNetwork_SimulationControlFields::HeightSelectionforLocalWindPressureCalculation, true);
  OS_ASSERT(value);
  return *value;
}

bool AirflowNetworkSimulationControl_Impl::isHeightSelectionforLocalWindPressureCalculationDefaulted() const {
  return isEmpty(openstudio::AirflowNetwork_SimulationControlFields::HeightSelectionforLocalWindPressureCalculation);
}

bool AirflowNetworkSimulationControl_Impl::setHeightSelectionforLocalWindPressureCalculation(
  const std::string& heightSelectionforLocalWindPressureCalculation) {
  return setString(openstudio::AirflowNetwork_SimulationControlFields::HeightSelectionforLocalWindPressureCalculation,
                   heightSelectionforLocalWindPressureCalculation);
}

void AirflowNetworkSimulationControl_Impl::resetHeightSelectionforLocalWindPressureCalculation() {
  OS_ASSERT(setString(openstudio::AirflowNetwork_SimulationControlFields::HeightSelectionforLocalWindPressureCalculation, ""));
}

std::string AirflowNetworkSimulationControl_Impl::buildingType() const {
  const auto value = getString(openstudio::AirflowNetwork_SimulationControlFields::BuildingType, true);
  OS_ASSERT(value);
  return *value;
}

bool AirflowNetworkSimulationControl_Impl::isBuildingTypeDefaulted() const {
  return isEmpty(openstudio::AirflowNetwork_SimulationControlFields::BuildingType);
}

bool AirflowNetworkSimulationControl_Impl::setBuildingType(const std::string& buildingType) {
  return setString(openstudio::AirflowNetwork_SimulationControlFields::BuildingType, buildingType);
}

void AirflowNetworkSimulationControl_Impl::resetBuildingType() {
  OS_ASSERT(setString(openstudio::AirflowNetwork_SimulationControlFields::BuildingType, ""));
}

int AirflowNetworkSimulationControl_Impl::maximumNumberofIterations() const {
  const auto value = getInt(openstudio::AirflowNetwork_SimulationControlFields::MaximumNumberofIterations, true);
  OS_ASSERT(value);
  return *value;
}

bool AirflowNetworkSimulationControl_Impl::isMaximumNumberofIterationsDefaulted() const {
  return isEmpty(openstudio::AirflowNetwork_SimulationControlFields::MaximumNumberofIterations);
}

bool AirflowNetworkSimulationControl_Impl::setMaximumNumberofIterations(int maximumNumberofIterations) {
  return setInt(openstudio::AirflowNetwork_SimulationControlFields::MaximumNumberofIterations, maximumNumberofIterations);
}

void AirflowNetworkSimulationControl_Impl::resetMaximumNumberofIterations() {
  OS_ASSERT(setString(openstudio::AirflowNetwork_SimulationControlFields::MaximumNumberofIterations, ""));
}

std::string AirflowNetworkSimulationControl_Impl::initializationType() const {
  const auto value = getString(openstudio::AirflowNetwork_SimulationControlFields::InitializationType, true);
  OS_ASSERT(value);
  return *value;
}

bool AirflowNetworkSimulationControl_Impl::isInitializationTypeDefaulted() const {
  return isEmpty(openstudio::AirflowNetwork_SimulationControlFields::InitializationType);
}

bool AirflowNetworkSimulationControl_Impl::setInitializationType(const std::string& initializationType) {
  return setString(openstudio::AirflowNetwork_SimulationControlFields::InitializationType, initializationType);
}

void AirflowNetworkSimulationControl_Impl::resetInitializationType() {
  OS_ASSERT(setString(openstudio::AirflowNetwork_SimulationControlFields::InitializationType, ""));
}

double AirflowNetworkSimulationControl_Impl::relativeAirflowConvergenceTolerance() const {
  const auto value = getDouble(openstudio::AirflowNetwork_SimulationControlFields::RelativeAirflowConvergenceTolerance, true);
  OS_ASSERT(value);
  return *value;
}

bool AirflowNetworkSimulationControl_Impl::isRelativeAirflowConvergenceToleranceDefaulted() const {
  return isEmpty(openstudio::AirflowNetwork_SimulationControlFields::RelativeAirflowConvergenceTolerance);
}

bool AirflowNetworkSimulationControl_Impl::setRelativeAirflowConvergenceTolerance(double relativeAirflowConvergenceTolerance) {
  return setDouble(openstudio::AirflowNetwork_SimulationControlFields::RelativeAirflowConvergenceTolerance,
                   relativeAirflowConvergenceTolerance);
}

void AirflowNetworkSimulationControl_Impl::resetRelativeAirflowConvergenceTolerance() {
  OS_ASSERT(setString(openstudio::AirflowNetwork_SimulationControlFields::RelativeAirflowConvergenceTolerance, ""));
}

double AirflowNetworkSimulationControl_Impl::absoluteAirflowConvergenceTolerance() const {
  const auto value = getDouble(openstudio::AirflowNetwork_SimulationControlFields::AbsoluteAirflowConvergenceTolerance, true);
  OS_ASSERT(value);
  return *value;
}

bool AirflowNetworkSimulationControl_Impl::isAbsoluteAirflowConvergenceToleranceDefaulted() const {
  return isEmpty(openstudio::AirflowNetwork_SimulationControlFields::AbsoluteAirflowConvergenceTolerance);
}

bool AirflowNetworkSimulationControl_Impl::setAbsoluteAirflowConvergenceTolerance(double absoluteAirflowConvergenceTolerance) {
  return setDouble(openstudio::AirflowNetwork_SimulationControlFields::AbsoluteAirflowConvergenceTolerance,
                   absoluteAirflowConvergenceTolerance);
}

void AirflowNetworkSimulationControl_Impl::resetAbsoluteAirflowConvergenceTolerance() {
  OS_ASSERT(setString(openstudio::AirflowNetwork_SimulationControlFields::AbsoluteAirflowConvergenceTolerance, ""));
}

double AirflowNetworkSimulationControl_Impl::convergenceAccelerationLimit() const {
  const auto value = getDouble(openstudio::AirflowNetwork_SimulationControlFields::ConvergenceAccelerationLimit, true);
  OS_ASSERT(value);
  return *value;
}

bool AirflowNetworkSimulationControl_Impl::isConvergenceAccelerationLimitDefaulted() const {
  return isEmpty(openstudio::AirflowNetwork_SimulationControlFields::ConvergenceAccelerationLimit);
}

bool AirflowNetworkSimulationControl_Impl::setConvergenceAccelerationLimit(double convergenceAccelerationLimit) {
  return setDouble(openstudio::AirflowNetwork_SimulationControlFields::ConvergenceAccelerationLimit, convergenceAccelerationLimit);
}

void AirflowNetworkSimulationControl_Impl::resetConvergenceAccelerationLimit() {
  OS_ASSERT(setString(openstudio::AirflowNetwork_SimulationControlFields::ConvergenceAccelerationLimit, ""));
}

double AirflowNetworkSimulationControl_Impl::azimuthAngleofLongAxisofBuilding() const {
  const auto value = getDouble(openstudio::AirflowNetwork_SimulationControlFields::AzimuthAngleofLongAxisofBuilding, true);
  OS_ASSERT(value);
  return *value;
}

bool AirflowNetworkSimulationControl_Impl::isAzimuthAngleofLongAxisofBuildingDefaulted() const {
  return isEmpty(openstudio::AirflowNetwork_SimulationControlFields::AzimuthAngleofLongAxisofBuilding);
}

bool AirflowNetworkSimulationControl_Impl::setAzimuthAngleofLongAxisofBuilding(double azimuthAngleofLongAxisofBuilding) {
  return setDouble(openstudio::AirflowNetwork_SimulationControlFields::AzimuthAngleofLongAxisofBuilding, azimuthAngleofLongAxisofBuilding);
}

void AirflowNetworkSimulationControl_Impl::resetAzimuthAngleofLongAxisofBuilding() {
  OS_ASSERT(setString(openstudio::AirflowNetwork_SimulationControlFields::AzimuthAngleofLongAxisofBuilding, ""));
}

double AirflowNetworkSimulationControl_Impl::ratioofBuildingWidthAlongShortAxistoWidthAlongLongAxis() const {
  const auto value =
    getDouble(openstudio::AirflowNetwork_SimulationControlFields::RatioofBuildingWidthAlongShortAxistoWidthAlongLongAxis, true);
  OS_ASSERT(value);
  return *value;
}

bool AirflowNetworkSimulationControl_Impl::isRatioofBuildingWidthAlongShortAxistoWidthAlongLongAxisDefaulted() const {
  return isEmpty(openstudio::AirflowNetwork_SimulationControlFields::RatioofBuildingWidthAlongShortAxistoWidthAlongLongAxis);
}

bool AirflowNetworkSimulationControl_Impl::setRatioofBuildingWidthAlongShortAxistoWidthAlongLongAxis(
  double ratioofBuildingWidthAlongShortAxistoWidthAlongLongAxis) {
  return setDouble(openstudio::AirflowNetwork_SimulationControlFields::RatioofBuildingWidthAlongShortAxistoWidthAlongLongAxis,
                   ratioofBuildingWidthAlongShortAxistoWidthAlongLongAxis);
}

void AirflowNetworkSimulationControl_Impl::resetRatioofBuildingWidthAlongShortAxistoWidthAlongLongAxis() {
  OS_ASSERT(setString(openstudio::AirflowNetwork_SimulationControlFields::RatioofBuildingWidthAlongShortAxistoWidthAlongLongAxis, ""));
}

bool AirflowNetworkSimulationControl_Impl::heightDependenceofExternalNodeTemperature() const {
  const auto value = getString(openstudio::AirflowNetwork_SimulationControlFields::HeightDependenceofExternalNodeTemperature, true);
  OS_ASSERT(value);
  return istringEqual(*value, "Yes");
}

bool AirflowNetworkSimulationControl_Impl::isHeightDependenceofExternalNodeTemperatureDefaulted() const {
  return isEmpty(openstudio::AirflowNetwork_SimulationControlFields::HeightDependenceofExternalNodeTemperature);
}

void AirflowNetworkSimulationControl_Impl::setHeightDependenceofExternalNodeTemperature(bool heightDependenceofExternalNodeTemperature) {
  OS_ASSERT(setString(openstudio::AirflowNetwork_SimulationControlFields::HeightDependenceofExternalNodeTemperature,
                      heightDependenceofExternalNodeTemperature ? "Yes" : "No"));
}

void AirflowNetworkSimulationControl_Impl::resetHeightDependenceofExternalNodeTemperature() {
  OS_ASSERT(setString(openstudio::AirflowNetwork_SimulationControlFields::HeightDependenceofExternalNodeTemperature, ""));
}

std::string AirflowNetworkSimulationControl_Impl::solver() const {
  const auto value = getString(openstudio::AirflowNetwork_SimulationControlFields::Solver, true);
  OS_ASSERT(value);
  return *value;
}

bool AirflowNetworkSimulationControl_Impl::isSolverDefaulted() const {
  return isEmpty(openstudio::AirflowNetwork_SimulationControlFields::Solver);
}

bool AirflowNetworkSimulationControl_Impl::setSolver(const std::string& solver) {
  return setString(openstudio::AirflowNetwork_SimulationControlFields::Solver, solver);
}

void AirflowNetworkSimulationControl_Impl::resetSolver() {
  OS_ASSERT(setString(openstudio::AirflowNetwork_SimulationControlFields::Solver, ""));
}

bool AirflowNetworkSimulationControl_Impl::allowUnsupportedZoneEquipment() const {
  const auto value = getString(openstudio::AirflowNetwork_SimulationControlFields::AllowUnsupportedZoneEquipment, true);
  OS_ASSERT(value);
  return istringEqual(*value, "Yes");
}

bool AirflowNetworkSimulationControl_Impl::isAllowUnsupportedZoneEquipmentDefaulted() const {
  return isEmpty(openstudio::AirflowNetwork_SimulationControlFields::AllowUnsupportedZoneEquipment);
}

void AirflowNetworkSimulationControl_Impl::setAllowUnsupportedZoneEquipment(bool allowUnsupportedZoneEquipment) {
  OS_ASSERT(setString(openstudio::AirflowNetwork_SimulationControlFields::AllowUnsupportedZoneEquipment,
                      allowUnsupportedZoneEquipment ? "Yes" : "No"));
}

void AirflowNetworkSimulationControl_Impl::resetAllowUnsupportedZoneEquipment() {
  OS_ASSERT(setString(openstudio::AirflowNetwork_SimulationControlFields::AllowUnsupportedZoneEquipment, ""));
}

std::vector<std::string> AirflowNetworkSimulationControl_Impl::airflowNetworkControlValues() const {
  return openstudio::epmodel::AirflowNetworkSimulationControl::airflowNetworkControlValues();
}

std::vector<std::string> AirflowNetworkSimulationControl_Impl::windPressureCoefficientTypeValues() const {
  return openstudio::epmodel::AirflowNetworkSimulationControl::windPressureCoefficientTypeValues();
}

std::vector<std::string> AirflowNetworkSimulationControl_Impl::heightSelectionforLocalWindPressureCalculationValues() const {
  return openstudio::epmodel::AirflowNetworkSimulationControl::heightSelectionforLocalWindPressureCalculationValues();
}

std::vector<std::string> AirflowNetworkSimulationControl_Impl::buildingTypeValues() const {
  return openstudio::epmodel::AirflowNetworkSimulationControl::buildingTypeValues();
}

std::vector<std::string> AirflowNetworkSimulationControl_Impl::initializationTypeValues() const {
  return openstudio::epmodel::AirflowNetworkSimulationControl::initializationTypeValues();
}

std::vector<std::string> AirflowNetworkSimulationControl_Impl::solverValues() const {
  return openstudio::epmodel::AirflowNetworkSimulationControl::solverValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
