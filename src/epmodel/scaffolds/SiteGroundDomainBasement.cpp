/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SiteGroundDomainBasement.hpp"
#include "SiteGroundDomainBasement_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/Site_GroundDomain_Basement_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

SiteGroundDomainBasement::SiteGroundDomainBasement(const Model& model) : ModelObject(SiteGroundDomainBasement::iddObjectType(), model) {}

SiteGroundDomainBasement::SiteGroundDomainBasement(std::shared_ptr<detail::SiteGroundDomainBasement_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType SiteGroundDomainBasement::iddObjectType() {
  return IddObjectType::Site_GroundDomain_Basement;
}

std::vector<std::string> SiteGroundDomainBasement::undisturbedGroundTemperatureModelTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::Site_GroundDomain_BasementFields::UndisturbedGroundTemperatureModelType);
}

std::vector<std::string> SiteGroundDomainBasement::horizontalInsulationExtentsValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::Site_GroundDomain_BasementFields::HorizontalInsulationExtents);
}

std::vector<std::string> SiteGroundDomainBasement::simulationTimestepValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::Site_GroundDomain_BasementFields::SimulationTimestep);
}

double SiteGroundDomainBasement::groundDomainDepth() const {
  return getImpl<detail::SiteGroundDomainBasement_Impl>()->groundDomainDepth();
}

bool SiteGroundDomainBasement::isGroundDomainDepthDefaulted() const {
  return getImpl<detail::SiteGroundDomainBasement_Impl>()->isGroundDomainDepthDefaulted();
}

bool SiteGroundDomainBasement::setGroundDomainDepth(double groundDomainDepth) {
  return getImpl<detail::SiteGroundDomainBasement_Impl>()->setGroundDomainDepth(groundDomainDepth);
}

void SiteGroundDomainBasement::resetGroundDomainDepth() {
  getImpl<detail::SiteGroundDomainBasement_Impl>()->resetGroundDomainDepth();
}

double SiteGroundDomainBasement::aspectRatio() const {
  return getImpl<detail::SiteGroundDomainBasement_Impl>()->aspectRatio();
}

bool SiteGroundDomainBasement::isAspectRatioDefaulted() const {
  return getImpl<detail::SiteGroundDomainBasement_Impl>()->isAspectRatioDefaulted();
}

bool SiteGroundDomainBasement::setAspectRatio(double aspectRatio) {
  return getImpl<detail::SiteGroundDomainBasement_Impl>()->setAspectRatio(aspectRatio);
}

void SiteGroundDomainBasement::resetAspectRatio() {
  getImpl<detail::SiteGroundDomainBasement_Impl>()->resetAspectRatio();
}

double SiteGroundDomainBasement::perimeterOffset() const {
  return getImpl<detail::SiteGroundDomainBasement_Impl>()->perimeterOffset();
}

bool SiteGroundDomainBasement::isPerimeterOffsetDefaulted() const {
  return getImpl<detail::SiteGroundDomainBasement_Impl>()->isPerimeterOffsetDefaulted();
}

bool SiteGroundDomainBasement::setPerimeterOffset(double perimeterOffset) {
  return getImpl<detail::SiteGroundDomainBasement_Impl>()->setPerimeterOffset(perimeterOffset);
}

void SiteGroundDomainBasement::resetPerimeterOffset() {
  getImpl<detail::SiteGroundDomainBasement_Impl>()->resetPerimeterOffset();
}

double SiteGroundDomainBasement::soilThermalConductivity() const {
  return getImpl<detail::SiteGroundDomainBasement_Impl>()->soilThermalConductivity();
}

bool SiteGroundDomainBasement::isSoilThermalConductivityDefaulted() const {
  return getImpl<detail::SiteGroundDomainBasement_Impl>()->isSoilThermalConductivityDefaulted();
}

bool SiteGroundDomainBasement::setSoilThermalConductivity(double soilThermalConductivity) {
  return getImpl<detail::SiteGroundDomainBasement_Impl>()->setSoilThermalConductivity(soilThermalConductivity);
}

void SiteGroundDomainBasement::resetSoilThermalConductivity() {
  getImpl<detail::SiteGroundDomainBasement_Impl>()->resetSoilThermalConductivity();
}

double SiteGroundDomainBasement::soilDensity() const {
  return getImpl<detail::SiteGroundDomainBasement_Impl>()->soilDensity();
}

bool SiteGroundDomainBasement::isSoilDensityDefaulted() const {
  return getImpl<detail::SiteGroundDomainBasement_Impl>()->isSoilDensityDefaulted();
}

bool SiteGroundDomainBasement::setSoilDensity(double soilDensity) {
  return getImpl<detail::SiteGroundDomainBasement_Impl>()->setSoilDensity(soilDensity);
}

void SiteGroundDomainBasement::resetSoilDensity() {
  getImpl<detail::SiteGroundDomainBasement_Impl>()->resetSoilDensity();
}

double SiteGroundDomainBasement::soilSpecificHeat() const {
  return getImpl<detail::SiteGroundDomainBasement_Impl>()->soilSpecificHeat();
}

bool SiteGroundDomainBasement::isSoilSpecificHeatDefaulted() const {
  return getImpl<detail::SiteGroundDomainBasement_Impl>()->isSoilSpecificHeatDefaulted();
}

bool SiteGroundDomainBasement::setSoilSpecificHeat(double soilSpecificHeat) {
  return getImpl<detail::SiteGroundDomainBasement_Impl>()->setSoilSpecificHeat(soilSpecificHeat);
}

void SiteGroundDomainBasement::resetSoilSpecificHeat() {
  getImpl<detail::SiteGroundDomainBasement_Impl>()->resetSoilSpecificHeat();
}

double SiteGroundDomainBasement::soilMoistureContentVolumeFraction() const {
  return getImpl<detail::SiteGroundDomainBasement_Impl>()->soilMoistureContentVolumeFraction();
}

bool SiteGroundDomainBasement::isSoilMoistureContentVolumeFractionDefaulted() const {
  return getImpl<detail::SiteGroundDomainBasement_Impl>()->isSoilMoistureContentVolumeFractionDefaulted();
}

bool SiteGroundDomainBasement::setSoilMoistureContentVolumeFraction(double soilMoistureContentVolumeFraction) {
  return getImpl<detail::SiteGroundDomainBasement_Impl>()->setSoilMoistureContentVolumeFraction(soilMoistureContentVolumeFraction);
}

void SiteGroundDomainBasement::resetSoilMoistureContentVolumeFraction() {
  getImpl<detail::SiteGroundDomainBasement_Impl>()->resetSoilMoistureContentVolumeFraction();
}

double SiteGroundDomainBasement::soilMoistureContentVolumeFractionatSaturation() const {
  return getImpl<detail::SiteGroundDomainBasement_Impl>()->soilMoistureContentVolumeFractionatSaturation();
}

bool SiteGroundDomainBasement::isSoilMoistureContentVolumeFractionatSaturationDefaulted() const {
  return getImpl<detail::SiteGroundDomainBasement_Impl>()->isSoilMoistureContentVolumeFractionatSaturationDefaulted();
}

bool SiteGroundDomainBasement::setSoilMoistureContentVolumeFractionatSaturation(double soilMoistureContentVolumeFractionatSaturation) {
  return getImpl<detail::SiteGroundDomainBasement_Impl>()->setSoilMoistureContentVolumeFractionatSaturation(
    soilMoistureContentVolumeFractionatSaturation);
}

void SiteGroundDomainBasement::resetSoilMoistureContentVolumeFractionatSaturation() {
  getImpl<detail::SiteGroundDomainBasement_Impl>()->resetSoilMoistureContentVolumeFractionatSaturation();
}

std::string SiteGroundDomainBasement::undisturbedGroundTemperatureModelType() const {
  return getImpl<detail::SiteGroundDomainBasement_Impl>()->undisturbedGroundTemperatureModelType();
}

bool SiteGroundDomainBasement::setUndisturbedGroundTemperatureModelType(const std::string& undisturbedGroundTemperatureModelType) {
  return getImpl<detail::SiteGroundDomainBasement_Impl>()->setUndisturbedGroundTemperatureModelType(undisturbedGroundTemperatureModelType);
}

double SiteGroundDomainBasement::evapotranspirationGroundCoverParameter() const {
  return getImpl<detail::SiteGroundDomainBasement_Impl>()->evapotranspirationGroundCoverParameter();
}

bool SiteGroundDomainBasement::isEvapotranspirationGroundCoverParameterDefaulted() const {
  return getImpl<detail::SiteGroundDomainBasement_Impl>()->isEvapotranspirationGroundCoverParameterDefaulted();
}

bool SiteGroundDomainBasement::setEvapotranspirationGroundCoverParameter(double evapotranspirationGroundCoverParameter) {
  return getImpl<detail::SiteGroundDomainBasement_Impl>()->setEvapotranspirationGroundCoverParameter(evapotranspirationGroundCoverParameter);
}

void SiteGroundDomainBasement::resetEvapotranspirationGroundCoverParameter() {
  getImpl<detail::SiteGroundDomainBasement_Impl>()->resetEvapotranspirationGroundCoverParameter();
}

bool SiteGroundDomainBasement::horizontalInsulation() const {
  return getImpl<detail::SiteGroundDomainBasement_Impl>()->horizontalInsulation();
}

bool SiteGroundDomainBasement::isHorizontalInsulationDefaulted() const {
  return getImpl<detail::SiteGroundDomainBasement_Impl>()->isHorizontalInsulationDefaulted();
}

bool SiteGroundDomainBasement::setHorizontalInsulation(bool horizontalInsulation) {
  return getImpl<detail::SiteGroundDomainBasement_Impl>()->setHorizontalInsulation(horizontalInsulation);
}

void SiteGroundDomainBasement::resetHorizontalInsulation() {
  getImpl<detail::SiteGroundDomainBasement_Impl>()->resetHorizontalInsulation();
}

std::string SiteGroundDomainBasement::horizontalInsulationExtents() const {
  return getImpl<detail::SiteGroundDomainBasement_Impl>()->horizontalInsulationExtents();
}

bool SiteGroundDomainBasement::isHorizontalInsulationExtentsDefaulted() const {
  return getImpl<detail::SiteGroundDomainBasement_Impl>()->isHorizontalInsulationExtentsDefaulted();
}

bool SiteGroundDomainBasement::setHorizontalInsulationExtents(const std::string& horizontalInsulationExtents) {
  return getImpl<detail::SiteGroundDomainBasement_Impl>()->setHorizontalInsulationExtents(horizontalInsulationExtents);
}

void SiteGroundDomainBasement::resetHorizontalInsulationExtents() {
  getImpl<detail::SiteGroundDomainBasement_Impl>()->resetHorizontalInsulationExtents();
}

boost::optional<double> SiteGroundDomainBasement::perimeterHorizontalInsulationWidth() const {
  return getImpl<detail::SiteGroundDomainBasement_Impl>()->perimeterHorizontalInsulationWidth();
}

bool SiteGroundDomainBasement::setPerimeterHorizontalInsulationWidth(double perimeterHorizontalInsulationWidth) {
  return getImpl<detail::SiteGroundDomainBasement_Impl>()->setPerimeterHorizontalInsulationWidth(perimeterHorizontalInsulationWidth);
}

void SiteGroundDomainBasement::resetPerimeterHorizontalInsulationWidth() {
  getImpl<detail::SiteGroundDomainBasement_Impl>()->resetPerimeterHorizontalInsulationWidth();
}

boost::optional<double> SiteGroundDomainBasement::basementWallDepth() const {
  return getImpl<detail::SiteGroundDomainBasement_Impl>()->basementWallDepth();
}

bool SiteGroundDomainBasement::setBasementWallDepth(double basementWallDepth) {
  return getImpl<detail::SiteGroundDomainBasement_Impl>()->setBasementWallDepth(basementWallDepth);
}

void SiteGroundDomainBasement::resetBasementWallDepth() {
  getImpl<detail::SiteGroundDomainBasement_Impl>()->resetBasementWallDepth();
}

bool SiteGroundDomainBasement::verticalInsulation() const {
  return getImpl<detail::SiteGroundDomainBasement_Impl>()->verticalInsulation();
}

bool SiteGroundDomainBasement::isVerticalInsulationDefaulted() const {
  return getImpl<detail::SiteGroundDomainBasement_Impl>()->isVerticalInsulationDefaulted();
}

bool SiteGroundDomainBasement::setVerticalInsulation(bool verticalInsulation) {
  return getImpl<detail::SiteGroundDomainBasement_Impl>()->setVerticalInsulation(verticalInsulation);
}

void SiteGroundDomainBasement::resetVerticalInsulation() {
  getImpl<detail::SiteGroundDomainBasement_Impl>()->resetVerticalInsulation();
}

boost::optional<double> SiteGroundDomainBasement::verticalInsulationDepth() const {
  return getImpl<detail::SiteGroundDomainBasement_Impl>()->verticalInsulationDepth();
}

bool SiteGroundDomainBasement::setVerticalInsulationDepth(double verticalInsulationDepth) {
  return getImpl<detail::SiteGroundDomainBasement_Impl>()->setVerticalInsulationDepth(verticalInsulationDepth);
}

void SiteGroundDomainBasement::resetVerticalInsulationDepth() {
  getImpl<detail::SiteGroundDomainBasement_Impl>()->resetVerticalInsulationDepth();
}

std::string SiteGroundDomainBasement::simulationTimestep() const {
  return getImpl<detail::SiteGroundDomainBasement_Impl>()->simulationTimestep();
}

bool SiteGroundDomainBasement::isSimulationTimestepDefaulted() const {
  return getImpl<detail::SiteGroundDomainBasement_Impl>()->isSimulationTimestepDefaulted();
}

bool SiteGroundDomainBasement::setSimulationTimestep(const std::string& simulationTimestep) {
  return getImpl<detail::SiteGroundDomainBasement_Impl>()->setSimulationTimestep(simulationTimestep);
}

void SiteGroundDomainBasement::resetSimulationTimestep() {
  getImpl<detail::SiteGroundDomainBasement_Impl>()->resetSimulationTimestep();
}

int SiteGroundDomainBasement::meshDensityParameter() const {
  return getImpl<detail::SiteGroundDomainBasement_Impl>()->meshDensityParameter();
}

bool SiteGroundDomainBasement::isMeshDensityParameterDefaulted() const {
  return getImpl<detail::SiteGroundDomainBasement_Impl>()->isMeshDensityParameterDefaulted();
}

bool SiteGroundDomainBasement::setMeshDensityParameter(int meshDensityParameter) {
  return getImpl<detail::SiteGroundDomainBasement_Impl>()->setMeshDensityParameter(meshDensityParameter);
}

void SiteGroundDomainBasement::resetMeshDensityParameter() {
  getImpl<detail::SiteGroundDomainBasement_Impl>()->resetMeshDensityParameter();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

double SiteGroundDomainBasement_Impl::groundDomainDepth() const {
  const auto value = getDouble(openstudio::Site_GroundDomain_BasementFields::GroundDomainDepth, true);
  OS_ASSERT(value);
  return *value;
}

bool SiteGroundDomainBasement_Impl::isGroundDomainDepthDefaulted() const {
  return isEmpty(openstudio::Site_GroundDomain_BasementFields::GroundDomainDepth);
}

bool SiteGroundDomainBasement_Impl::setGroundDomainDepth(double groundDomainDepth) {
  return setDouble(openstudio::Site_GroundDomain_BasementFields::GroundDomainDepth, groundDomainDepth);
}

void SiteGroundDomainBasement_Impl::resetGroundDomainDepth() {
  OS_ASSERT(setString(openstudio::Site_GroundDomain_BasementFields::GroundDomainDepth, ""));
}

double SiteGroundDomainBasement_Impl::aspectRatio() const {
  const auto value = getDouble(openstudio::Site_GroundDomain_BasementFields::AspectRatio, true);
  OS_ASSERT(value);
  return *value;
}

bool SiteGroundDomainBasement_Impl::isAspectRatioDefaulted() const {
  return isEmpty(openstudio::Site_GroundDomain_BasementFields::AspectRatio);
}

bool SiteGroundDomainBasement_Impl::setAspectRatio(double aspectRatio) {
  const bool result = setDouble(openstudio::Site_GroundDomain_BasementFields::AspectRatio, aspectRatio);
  OS_ASSERT(result);
  return result;
}

void SiteGroundDomainBasement_Impl::resetAspectRatio() {
  OS_ASSERT(setString(openstudio::Site_GroundDomain_BasementFields::AspectRatio, ""));
}

double SiteGroundDomainBasement_Impl::perimeterOffset() const {
  const auto value = getDouble(openstudio::Site_GroundDomain_BasementFields::PerimeterOffset, true);
  OS_ASSERT(value);
  return *value;
}

bool SiteGroundDomainBasement_Impl::isPerimeterOffsetDefaulted() const {
  return isEmpty(openstudio::Site_GroundDomain_BasementFields::PerimeterOffset);
}

bool SiteGroundDomainBasement_Impl::setPerimeterOffset(double perimeterOffset) {
  return setDouble(openstudio::Site_GroundDomain_BasementFields::PerimeterOffset, perimeterOffset);
}

void SiteGroundDomainBasement_Impl::resetPerimeterOffset() {
  OS_ASSERT(setString(openstudio::Site_GroundDomain_BasementFields::PerimeterOffset, ""));
}

double SiteGroundDomainBasement_Impl::soilThermalConductivity() const {
  const auto value = getDouble(openstudio::Site_GroundDomain_BasementFields::SoilThermalConductivity, true);
  OS_ASSERT(value);
  return *value;
}

bool SiteGroundDomainBasement_Impl::isSoilThermalConductivityDefaulted() const {
  return isEmpty(openstudio::Site_GroundDomain_BasementFields::SoilThermalConductivity);
}

bool SiteGroundDomainBasement_Impl::setSoilThermalConductivity(double soilThermalConductivity) {
  return setDouble(openstudio::Site_GroundDomain_BasementFields::SoilThermalConductivity, soilThermalConductivity);
}

void SiteGroundDomainBasement_Impl::resetSoilThermalConductivity() {
  OS_ASSERT(setString(openstudio::Site_GroundDomain_BasementFields::SoilThermalConductivity, ""));
}

double SiteGroundDomainBasement_Impl::soilDensity() const {
  const auto value = getDouble(openstudio::Site_GroundDomain_BasementFields::SoilDensity, true);
  OS_ASSERT(value);
  return *value;
}

bool SiteGroundDomainBasement_Impl::isSoilDensityDefaulted() const {
  return isEmpty(openstudio::Site_GroundDomain_BasementFields::SoilDensity);
}

bool SiteGroundDomainBasement_Impl::setSoilDensity(double soilDensity) {
  return setDouble(openstudio::Site_GroundDomain_BasementFields::SoilDensity, soilDensity);
}

void SiteGroundDomainBasement_Impl::resetSoilDensity() {
  OS_ASSERT(setString(openstudio::Site_GroundDomain_BasementFields::SoilDensity, ""));
}

double SiteGroundDomainBasement_Impl::soilSpecificHeat() const {
  const auto value = getDouble(openstudio::Site_GroundDomain_BasementFields::SoilSpecificHeat, true);
  OS_ASSERT(value);
  return *value;
}

bool SiteGroundDomainBasement_Impl::isSoilSpecificHeatDefaulted() const {
  return isEmpty(openstudio::Site_GroundDomain_BasementFields::SoilSpecificHeat);
}

bool SiteGroundDomainBasement_Impl::setSoilSpecificHeat(double soilSpecificHeat) {
  return setDouble(openstudio::Site_GroundDomain_BasementFields::SoilSpecificHeat, soilSpecificHeat);
}

void SiteGroundDomainBasement_Impl::resetSoilSpecificHeat() {
  OS_ASSERT(setString(openstudio::Site_GroundDomain_BasementFields::SoilSpecificHeat, ""));
}

double SiteGroundDomainBasement_Impl::soilMoistureContentVolumeFraction() const {
  const auto value = getDouble(openstudio::Site_GroundDomain_BasementFields::SoilMoistureContentVolumeFraction, true);
  OS_ASSERT(value);
  return *value;
}

bool SiteGroundDomainBasement_Impl::isSoilMoistureContentVolumeFractionDefaulted() const {
  return isEmpty(openstudio::Site_GroundDomain_BasementFields::SoilMoistureContentVolumeFraction);
}

bool SiteGroundDomainBasement_Impl::setSoilMoistureContentVolumeFraction(double soilMoistureContentVolumeFraction) {
  return setDouble(openstudio::Site_GroundDomain_BasementFields::SoilMoistureContentVolumeFraction, soilMoistureContentVolumeFraction);
}

void SiteGroundDomainBasement_Impl::resetSoilMoistureContentVolumeFraction() {
  OS_ASSERT(setString(openstudio::Site_GroundDomain_BasementFields::SoilMoistureContentVolumeFraction, ""));
}

double SiteGroundDomainBasement_Impl::soilMoistureContentVolumeFractionatSaturation() const {
  const auto value = getDouble(openstudio::Site_GroundDomain_BasementFields::SoilMoistureContentVolumeFractionatSaturation, true);
  OS_ASSERT(value);
  return *value;
}

bool SiteGroundDomainBasement_Impl::isSoilMoistureContentVolumeFractionatSaturationDefaulted() const {
  return isEmpty(openstudio::Site_GroundDomain_BasementFields::SoilMoistureContentVolumeFractionatSaturation);
}

bool SiteGroundDomainBasement_Impl::setSoilMoistureContentVolumeFractionatSaturation(double soilMoistureContentVolumeFractionatSaturation) {
  return setDouble(openstudio::Site_GroundDomain_BasementFields::SoilMoistureContentVolumeFractionatSaturation,
                   soilMoistureContentVolumeFractionatSaturation);
}

void SiteGroundDomainBasement_Impl::resetSoilMoistureContentVolumeFractionatSaturation() {
  OS_ASSERT(setString(openstudio::Site_GroundDomain_BasementFields::SoilMoistureContentVolumeFractionatSaturation, ""));
}

std::string SiteGroundDomainBasement_Impl::undisturbedGroundTemperatureModelType() const {
  const auto value = getString(openstudio::Site_GroundDomain_BasementFields::UndisturbedGroundTemperatureModelType, true);
  OS_ASSERT(value);
  return *value;
}

bool SiteGroundDomainBasement_Impl::setUndisturbedGroundTemperatureModelType(const std::string& undisturbedGroundTemperatureModelType) {
  return setString(openstudio::Site_GroundDomain_BasementFields::UndisturbedGroundTemperatureModelType,
                   undisturbedGroundTemperatureModelType);
}

double SiteGroundDomainBasement_Impl::evapotranspirationGroundCoverParameter() const {
  const auto value = getDouble(openstudio::Site_GroundDomain_BasementFields::EvapotranspirationGroundCoverParameter, true);
  OS_ASSERT(value);
  return *value;
}

bool SiteGroundDomainBasement_Impl::isEvapotranspirationGroundCoverParameterDefaulted() const {
  return isEmpty(openstudio::Site_GroundDomain_BasementFields::EvapotranspirationGroundCoverParameter);
}

bool SiteGroundDomainBasement_Impl::setEvapotranspirationGroundCoverParameter(double evapotranspirationGroundCoverParameter) {
  return setDouble(openstudio::Site_GroundDomain_BasementFields::EvapotranspirationGroundCoverParameter,
                   evapotranspirationGroundCoverParameter);
}

void SiteGroundDomainBasement_Impl::resetEvapotranspirationGroundCoverParameter() {
  OS_ASSERT(setString(openstudio::Site_GroundDomain_BasementFields::EvapotranspirationGroundCoverParameter, ""));
}

bool SiteGroundDomainBasement_Impl::horizontalInsulation() const {
  const auto value = getString(openstudio::Site_GroundDomain_BasementFields::HorizontalInsulation, true);
  OS_ASSERT(value);
  return openstudio::istringEqual(*value, "Yes");
}

bool SiteGroundDomainBasement_Impl::isHorizontalInsulationDefaulted() const {
  return isEmpty(openstudio::Site_GroundDomain_BasementFields::HorizontalInsulation);
}

bool SiteGroundDomainBasement_Impl::setHorizontalInsulation(bool horizontalInsulation) {
  const bool result = setString(openstudio::Site_GroundDomain_BasementFields::HorizontalInsulation,
                                horizontalInsulation ? "Yes" : "No");
  OS_ASSERT(result);
  return result;
}

void SiteGroundDomainBasement_Impl::resetHorizontalInsulation() {
  OS_ASSERT(setString(openstudio::Site_GroundDomain_BasementFields::HorizontalInsulation, ""));
}

std::string SiteGroundDomainBasement_Impl::horizontalInsulationExtents() const {
  const auto value = getString(openstudio::Site_GroundDomain_BasementFields::HorizontalInsulationExtents, true);
  OS_ASSERT(value);
  return *value;
}

bool SiteGroundDomainBasement_Impl::isHorizontalInsulationExtentsDefaulted() const {
  return isEmpty(openstudio::Site_GroundDomain_BasementFields::HorizontalInsulationExtents);
}

bool SiteGroundDomainBasement_Impl::setHorizontalInsulationExtents(const std::string& horizontalInsulationExtents) {
  return setString(openstudio::Site_GroundDomain_BasementFields::HorizontalInsulationExtents, horizontalInsulationExtents);
}

void SiteGroundDomainBasement_Impl::resetHorizontalInsulationExtents() {
  OS_ASSERT(setString(openstudio::Site_GroundDomain_BasementFields::HorizontalInsulationExtents, ""));
}

boost::optional<double> SiteGroundDomainBasement_Impl::perimeterHorizontalInsulationWidth() const {
  return getDouble(openstudio::Site_GroundDomain_BasementFields::PerimeterHorizontalInsulationWidth, true);
}

bool SiteGroundDomainBasement_Impl::setPerimeterHorizontalInsulationWidth(double perimeterHorizontalInsulationWidth) {
  return setDouble(openstudio::Site_GroundDomain_BasementFields::PerimeterHorizontalInsulationWidth, perimeterHorizontalInsulationWidth);
}

void SiteGroundDomainBasement_Impl::resetPerimeterHorizontalInsulationWidth() {
  OS_ASSERT(setString(openstudio::Site_GroundDomain_BasementFields::PerimeterHorizontalInsulationWidth, ""));
}

boost::optional<double> SiteGroundDomainBasement_Impl::basementWallDepth() const {
  return getDouble(openstudio::Site_GroundDomain_BasementFields::BasementWallDepth, true);
}

bool SiteGroundDomainBasement_Impl::setBasementWallDepth(double basementWallDepth) {
  return setDouble(openstudio::Site_GroundDomain_BasementFields::BasementWallDepth, basementWallDepth);
}

void SiteGroundDomainBasement_Impl::resetBasementWallDepth() {
  OS_ASSERT(setString(openstudio::Site_GroundDomain_BasementFields::BasementWallDepth, ""));
}

bool SiteGroundDomainBasement_Impl::verticalInsulation() const {
  const auto value = getString(openstudio::Site_GroundDomain_BasementFields::VerticalInsulation, true);
  OS_ASSERT(value);
  return openstudio::istringEqual(*value, "Yes");
}

bool SiteGroundDomainBasement_Impl::isVerticalInsulationDefaulted() const {
  return isEmpty(openstudio::Site_GroundDomain_BasementFields::VerticalInsulation);
}

bool SiteGroundDomainBasement_Impl::setVerticalInsulation(bool verticalInsulation) {
  const bool result = setString(openstudio::Site_GroundDomain_BasementFields::VerticalInsulation, verticalInsulation ? "Yes" : "No");
  OS_ASSERT(result);
  return result;
}

void SiteGroundDomainBasement_Impl::resetVerticalInsulation() {
  OS_ASSERT(setString(openstudio::Site_GroundDomain_BasementFields::VerticalInsulation, ""));
}

boost::optional<double> SiteGroundDomainBasement_Impl::verticalInsulationDepth() const {
  return getDouble(openstudio::Site_GroundDomain_BasementFields::VerticalInsulationDepth, true);
}

bool SiteGroundDomainBasement_Impl::setVerticalInsulationDepth(double verticalInsulationDepth) {
  return setDouble(openstudio::Site_GroundDomain_BasementFields::VerticalInsulationDepth, verticalInsulationDepth);
}

void SiteGroundDomainBasement_Impl::resetVerticalInsulationDepth() {
  OS_ASSERT(setString(openstudio::Site_GroundDomain_BasementFields::VerticalInsulationDepth, ""));
}

std::string SiteGroundDomainBasement_Impl::simulationTimestep() const {
  const auto value = getString(openstudio::Site_GroundDomain_BasementFields::SimulationTimestep, true);
  OS_ASSERT(value);
  return *value;
}

bool SiteGroundDomainBasement_Impl::isSimulationTimestepDefaulted() const {
  return isEmpty(openstudio::Site_GroundDomain_BasementFields::SimulationTimestep);
}

bool SiteGroundDomainBasement_Impl::setSimulationTimestep(const std::string& simulationTimestep) {
  return setString(openstudio::Site_GroundDomain_BasementFields::SimulationTimestep, simulationTimestep);
}

void SiteGroundDomainBasement_Impl::resetSimulationTimestep() {
  OS_ASSERT(setString(openstudio::Site_GroundDomain_BasementFields::SimulationTimestep, ""));
}

int SiteGroundDomainBasement_Impl::meshDensityParameter() const {
  const auto value = getInt(openstudio::Site_GroundDomain_BasementFields::MeshDensityParameter, true);
  OS_ASSERT(value);
  return *value;
}

bool SiteGroundDomainBasement_Impl::isMeshDensityParameterDefaulted() const {
  return isEmpty(openstudio::Site_GroundDomain_BasementFields::MeshDensityParameter);
}

bool SiteGroundDomainBasement_Impl::setMeshDensityParameter(int meshDensityParameter) {
  return setInt(openstudio::Site_GroundDomain_BasementFields::MeshDensityParameter, meshDensityParameter);
}

void SiteGroundDomainBasement_Impl::resetMeshDensityParameter() {
  OS_ASSERT(setString(openstudio::Site_GroundDomain_BasementFields::MeshDensityParameter, ""));
}

std::vector<std::string> SiteGroundDomainBasement_Impl::undisturbedGroundTemperatureModelTypeValues() const {
  return openstudio::epmodel::SiteGroundDomainBasement::undisturbedGroundTemperatureModelTypeValues();
}

std::vector<std::string> SiteGroundDomainBasement_Impl::horizontalInsulationExtentsValues() const {
  return openstudio::epmodel::SiteGroundDomainBasement::horizontalInsulationExtentsValues();
}

std::vector<std::string> SiteGroundDomainBasement_Impl::simulationTimestepValues() const {
  return openstudio::epmodel::SiteGroundDomainBasement::simulationTimestepValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
