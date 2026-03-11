/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "AirflowNetworkMultiZoneSurface.hpp"
#include "AirflowNetworkMultiZoneSurface_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/AirflowNetwork_MultiZone_Surface_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

AirflowNetworkMultiZoneSurface::AirflowNetworkMultiZoneSurface(const Model& model)
  : ModelObject(AirflowNetworkMultiZoneSurface::iddObjectType(), model) {}

AirflowNetworkMultiZoneSurface::AirflowNetworkMultiZoneSurface(std::shared_ptr<detail::AirflowNetworkMultiZoneSurface_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType AirflowNetworkMultiZoneSurface::iddObjectType() {
  return IddObjectType::AirflowNetwork_MultiZone_Surface;
}

std::vector<std::string> AirflowNetworkMultiZoneSurface::ventilationControlModeValues() {
  return {"Temperature", "Enthalpy", "Constant", "ASHRAE55Adaptive", "CEN15251Adaptive", "NoVent", "ZoneLevel", "AdjacentTemperature",
          "AdjacentEnthalpy"};
}

std::vector<std::string> AirflowNetworkMultiZoneSurface::equivalentRectangleMethodValues() {
  return {"PolygonHeight", "BaseSurfaceAspectRatio", "UserDefinedAspectRatio"};
}

double AirflowNetworkMultiZoneSurface::windowDoorOpeningFactororCrackFactor() const {
  return getImpl<detail::AirflowNetworkMultiZoneSurface_Impl>()->windowDoorOpeningFactororCrackFactor();
}

bool AirflowNetworkMultiZoneSurface::isWindowDoorOpeningFactororCrackFactorDefaulted() const {
  return getImpl<detail::AirflowNetworkMultiZoneSurface_Impl>()->isWindowDoorOpeningFactororCrackFactorDefaulted();
}

bool AirflowNetworkMultiZoneSurface::setWindowDoorOpeningFactororCrackFactor(double windowDoorOpeningFactororCrackFactor) {
  return getImpl<detail::AirflowNetworkMultiZoneSurface_Impl>()->setWindowDoorOpeningFactororCrackFactor(windowDoorOpeningFactororCrackFactor);
}

void AirflowNetworkMultiZoneSurface::resetWindowDoorOpeningFactororCrackFactor() {
  getImpl<detail::AirflowNetworkMultiZoneSurface_Impl>()->resetWindowDoorOpeningFactororCrackFactor();
}

std::string AirflowNetworkMultiZoneSurface::ventilationControlMode() const {
  return getImpl<detail::AirflowNetworkMultiZoneSurface_Impl>()->ventilationControlMode();
}

bool AirflowNetworkMultiZoneSurface::isVentilationControlModeDefaulted() const {
  return getImpl<detail::AirflowNetworkMultiZoneSurface_Impl>()->isVentilationControlModeDefaulted();
}

bool AirflowNetworkMultiZoneSurface::setVentilationControlMode(const std::string& ventilationControlMode) {
  return getImpl<detail::AirflowNetworkMultiZoneSurface_Impl>()->setVentilationControlMode(ventilationControlMode);
}

void AirflowNetworkMultiZoneSurface::resetVentilationControlMode() {
  getImpl<detail::AirflowNetworkMultiZoneSurface_Impl>()->resetVentilationControlMode();
}

double AirflowNetworkMultiZoneSurface::minimumVentingOpenFactor() const {
  return getImpl<detail::AirflowNetworkMultiZoneSurface_Impl>()->minimumVentingOpenFactor();
}

bool AirflowNetworkMultiZoneSurface::isMinimumVentingOpenFactorDefaulted() const {
  return getImpl<detail::AirflowNetworkMultiZoneSurface_Impl>()->isMinimumVentingOpenFactorDefaulted();
}

bool AirflowNetworkMultiZoneSurface::setMinimumVentingOpenFactor(double minimumVentingOpenFactor) {
  return getImpl<detail::AirflowNetworkMultiZoneSurface_Impl>()->setMinimumVentingOpenFactor(minimumVentingOpenFactor);
}

void AirflowNetworkMultiZoneSurface::resetMinimumVentingOpenFactor() {
  getImpl<detail::AirflowNetworkMultiZoneSurface_Impl>()->resetMinimumVentingOpenFactor();
}

double AirflowNetworkMultiZoneSurface::indoorandOutdoorTemperatureDifferenceLowerLimitForMaximumVentingOpenFactor() const {
  return getImpl<detail::AirflowNetworkMultiZoneSurface_Impl>()
    ->indoorandOutdoorTemperatureDifferenceLowerLimitForMaximumVentingOpenFactor();
}

bool AirflowNetworkMultiZoneSurface::isIndoorandOutdoorTemperatureDifferenceLowerLimitForMaximumVentingOpenFactorDefaulted() const {
  return getImpl<detail::AirflowNetworkMultiZoneSurface_Impl>()
    ->isIndoorandOutdoorTemperatureDifferenceLowerLimitForMaximumVentingOpenFactorDefaulted();
}

bool AirflowNetworkMultiZoneSurface::setIndoorandOutdoorTemperatureDifferenceLowerLimitForMaximumVentingOpenFactor(
  double indoorandOutdoorTemperatureDifferenceLowerLimitForMaximumVentingOpenFactor) {
  return getImpl<detail::AirflowNetworkMultiZoneSurface_Impl>()
    ->setIndoorandOutdoorTemperatureDifferenceLowerLimitForMaximumVentingOpenFactor(
      indoorandOutdoorTemperatureDifferenceLowerLimitForMaximumVentingOpenFactor);
}

void AirflowNetworkMultiZoneSurface::resetIndoorandOutdoorTemperatureDifferenceLowerLimitForMaximumVentingOpenFactor() {
  getImpl<detail::AirflowNetworkMultiZoneSurface_Impl>()->resetIndoorandOutdoorTemperatureDifferenceLowerLimitForMaximumVentingOpenFactor();
}

double AirflowNetworkMultiZoneSurface::indoorandOutdoorTemperatureDifferenceUpperLimitforMinimumVentingOpenFactor() const {
  return getImpl<detail::AirflowNetworkMultiZoneSurface_Impl>()
    ->indoorandOutdoorTemperatureDifferenceUpperLimitforMinimumVentingOpenFactor();
}

bool AirflowNetworkMultiZoneSurface::isIndoorandOutdoorTemperatureDifferenceUpperLimitforMinimumVentingOpenFactorDefaulted() const {
  return getImpl<detail::AirflowNetworkMultiZoneSurface_Impl>()
    ->isIndoorandOutdoorTemperatureDifferenceUpperLimitforMinimumVentingOpenFactorDefaulted();
}

bool AirflowNetworkMultiZoneSurface::setIndoorandOutdoorTemperatureDifferenceUpperLimitforMinimumVentingOpenFactor(
  double indoorandOutdoorTemperatureDifferenceUpperLimitforMinimumVentingOpenFactor) {
  return getImpl<detail::AirflowNetworkMultiZoneSurface_Impl>()->setIndoorandOutdoorTemperatureDifferenceUpperLimitforMinimumVentingOpenFactor(
    indoorandOutdoorTemperatureDifferenceUpperLimitforMinimumVentingOpenFactor);
}

void AirflowNetworkMultiZoneSurface::resetIndoorandOutdoorTemperatureDifferenceUpperLimitforMinimumVentingOpenFactor() {
  getImpl<detail::AirflowNetworkMultiZoneSurface_Impl>()->resetIndoorandOutdoorTemperatureDifferenceUpperLimitforMinimumVentingOpenFactor();
}

double AirflowNetworkMultiZoneSurface::indoorandOutdoorEnthalpyDifferenceLowerLimitForMaximumVentingOpenFactor() const {
  return getImpl<detail::AirflowNetworkMultiZoneSurface_Impl>()
    ->indoorandOutdoorEnthalpyDifferenceLowerLimitForMaximumVentingOpenFactor();
}

bool AirflowNetworkMultiZoneSurface::isIndoorandOutdoorEnthalpyDifferenceLowerLimitForMaximumVentingOpenFactorDefaulted() const {
  return getImpl<detail::AirflowNetworkMultiZoneSurface_Impl>()
    ->isIndoorandOutdoorEnthalpyDifferenceLowerLimitForMaximumVentingOpenFactorDefaulted();
}

bool AirflowNetworkMultiZoneSurface::setIndoorandOutdoorEnthalpyDifferenceLowerLimitForMaximumVentingOpenFactor(
  double indoorandOutdoorEnthalpyDifferenceLowerLimitForMaximumVentingOpenFactor) {
  return getImpl<detail::AirflowNetworkMultiZoneSurface_Impl>()->setIndoorandOutdoorEnthalpyDifferenceLowerLimitForMaximumVentingOpenFactor(
    indoorandOutdoorEnthalpyDifferenceLowerLimitForMaximumVentingOpenFactor);
}

void AirflowNetworkMultiZoneSurface::resetIndoorandOutdoorEnthalpyDifferenceLowerLimitForMaximumVentingOpenFactor() {
  getImpl<detail::AirflowNetworkMultiZoneSurface_Impl>()->resetIndoorandOutdoorEnthalpyDifferenceLowerLimitForMaximumVentingOpenFactor();
}

double AirflowNetworkMultiZoneSurface::indoorandOutdoorEnthalpyDifferenceUpperLimitforMinimumVentingOpenFactor() const {
  return getImpl<detail::AirflowNetworkMultiZoneSurface_Impl>()
    ->indoorandOutdoorEnthalpyDifferenceUpperLimitforMinimumVentingOpenFactor();
}

bool AirflowNetworkMultiZoneSurface::isIndoorandOutdoorEnthalpyDifferenceUpperLimitforMinimumVentingOpenFactorDefaulted() const {
  return getImpl<detail::AirflowNetworkMultiZoneSurface_Impl>()
    ->isIndoorandOutdoorEnthalpyDifferenceUpperLimitforMinimumVentingOpenFactorDefaulted();
}

bool AirflowNetworkMultiZoneSurface::setIndoorandOutdoorEnthalpyDifferenceUpperLimitforMinimumVentingOpenFactor(
  double indoorandOutdoorEnthalpyDifferenceUpperLimitforMinimumVentingOpenFactor) {
  return getImpl<detail::AirflowNetworkMultiZoneSurface_Impl>()->setIndoorandOutdoorEnthalpyDifferenceUpperLimitforMinimumVentingOpenFactor(
    indoorandOutdoorEnthalpyDifferenceUpperLimitforMinimumVentingOpenFactor);
}

void AirflowNetworkMultiZoneSurface::resetIndoorandOutdoorEnthalpyDifferenceUpperLimitforMinimumVentingOpenFactor() {
  getImpl<detail::AirflowNetworkMultiZoneSurface_Impl>()->resetIndoorandOutdoorEnthalpyDifferenceUpperLimitforMinimumVentingOpenFactor();
}

std::string AirflowNetworkMultiZoneSurface::equivalentRectangleMethod() const {
  return getImpl<detail::AirflowNetworkMultiZoneSurface_Impl>()->equivalentRectangleMethod();
}

bool AirflowNetworkMultiZoneSurface::isEquivalentRectangleMethodDefaulted() const {
  return getImpl<detail::AirflowNetworkMultiZoneSurface_Impl>()->isEquivalentRectangleMethodDefaulted();
}

bool AirflowNetworkMultiZoneSurface::setEquivalentRectangleMethod(const std::string& equivalentRectangleMethod) {
  return getImpl<detail::AirflowNetworkMultiZoneSurface_Impl>()->setEquivalentRectangleMethod(equivalentRectangleMethod);
}

void AirflowNetworkMultiZoneSurface::resetEquivalentRectangleMethod() {
  getImpl<detail::AirflowNetworkMultiZoneSurface_Impl>()->resetEquivalentRectangleMethod();
}

double AirflowNetworkMultiZoneSurface::equivalentRectangleAspectRatio() const {
  return getImpl<detail::AirflowNetworkMultiZoneSurface_Impl>()->equivalentRectangleAspectRatio();
}

bool AirflowNetworkMultiZoneSurface::isEquivalentRectangleAspectRatioDefaulted() const {
  return getImpl<detail::AirflowNetworkMultiZoneSurface_Impl>()->isEquivalentRectangleAspectRatioDefaulted();
}

bool AirflowNetworkMultiZoneSurface::setEquivalentRectangleAspectRatio(double equivalentRectangleAspectRatio) {
  return getImpl<detail::AirflowNetworkMultiZoneSurface_Impl>()->setEquivalentRectangleAspectRatio(equivalentRectangleAspectRatio);
}

void AirflowNetworkMultiZoneSurface::resetEquivalentRectangleAspectRatio() {
  getImpl<detail::AirflowNetworkMultiZoneSurface_Impl>()->resetEquivalentRectangleAspectRatio();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

double AirflowNetworkMultiZoneSurface_Impl::windowDoorOpeningFactororCrackFactor() const {
  const auto value = getDouble(openstudio::AirflowNetwork_MultiZone_SurfaceFields::Window_DoorOpeningFactororCrackFactor, true);
  OS_ASSERT(value);
  return *value;
}

bool AirflowNetworkMultiZoneSurface_Impl::isWindowDoorOpeningFactororCrackFactorDefaulted() const {
  return isEmpty(openstudio::AirflowNetwork_MultiZone_SurfaceFields::Window_DoorOpeningFactororCrackFactor);
}

bool AirflowNetworkMultiZoneSurface_Impl::setWindowDoorOpeningFactororCrackFactor(double windowDoorOpeningFactororCrackFactor) {
  return setDouble(openstudio::AirflowNetwork_MultiZone_SurfaceFields::Window_DoorOpeningFactororCrackFactor, windowDoorOpeningFactororCrackFactor);
}

void AirflowNetworkMultiZoneSurface_Impl::resetWindowDoorOpeningFactororCrackFactor() {
  OS_ASSERT(setString(openstudio::AirflowNetwork_MultiZone_SurfaceFields::Window_DoorOpeningFactororCrackFactor, ""));
}

std::string AirflowNetworkMultiZoneSurface_Impl::ventilationControlMode() const {
  const auto value = getString(openstudio::AirflowNetwork_MultiZone_SurfaceFields::VentilationControlMode, true);
  OS_ASSERT(value);
  return *value;
}

bool AirflowNetworkMultiZoneSurface_Impl::isVentilationControlModeDefaulted() const {
  return isEmpty(openstudio::AirflowNetwork_MultiZone_SurfaceFields::VentilationControlMode);
}

bool AirflowNetworkMultiZoneSurface_Impl::setVentilationControlMode(const std::string& ventilationControlMode) {
  return setString(openstudio::AirflowNetwork_MultiZone_SurfaceFields::VentilationControlMode, ventilationControlMode);
}

void AirflowNetworkMultiZoneSurface_Impl::resetVentilationControlMode() {
  OS_ASSERT(setString(openstudio::AirflowNetwork_MultiZone_SurfaceFields::VentilationControlMode, ""));
}

double AirflowNetworkMultiZoneSurface_Impl::minimumVentingOpenFactor() const {
  const auto value = getDouble(openstudio::AirflowNetwork_MultiZone_SurfaceFields::MinimumVentingOpenFactor, true);
  OS_ASSERT(value);
  return *value;
}

bool AirflowNetworkMultiZoneSurface_Impl::isMinimumVentingOpenFactorDefaulted() const {
  return isEmpty(openstudio::AirflowNetwork_MultiZone_SurfaceFields::MinimumVentingOpenFactor);
}

bool AirflowNetworkMultiZoneSurface_Impl::setMinimumVentingOpenFactor(double minimumVentingOpenFactor) {
  return setDouble(openstudio::AirflowNetwork_MultiZone_SurfaceFields::MinimumVentingOpenFactor, minimumVentingOpenFactor);
}

void AirflowNetworkMultiZoneSurface_Impl::resetMinimumVentingOpenFactor() {
  OS_ASSERT(setString(openstudio::AirflowNetwork_MultiZone_SurfaceFields::MinimumVentingOpenFactor, ""));
}

double AirflowNetworkMultiZoneSurface_Impl::indoorandOutdoorTemperatureDifferenceLowerLimitForMaximumVentingOpenFactor() const {
  const auto value =
    getDouble(openstudio::AirflowNetwork_MultiZone_SurfaceFields::IndoorandOutdoorTemperatureDifferenceLowerLimitForMaximumVentingOpenFactor, true);
  OS_ASSERT(value);
  return *value;
}

bool AirflowNetworkMultiZoneSurface_Impl::isIndoorandOutdoorTemperatureDifferenceLowerLimitForMaximumVentingOpenFactorDefaulted() const {
  return isEmpty(openstudio::AirflowNetwork_MultiZone_SurfaceFields::IndoorandOutdoorTemperatureDifferenceLowerLimitForMaximumVentingOpenFactor);
}

bool AirflowNetworkMultiZoneSurface_Impl::setIndoorandOutdoorTemperatureDifferenceLowerLimitForMaximumVentingOpenFactor(
  double indoorandOutdoorTemperatureDifferenceLowerLimitForMaximumVentingOpenFactor) {
  return setDouble(openstudio::AirflowNetwork_MultiZone_SurfaceFields::IndoorandOutdoorTemperatureDifferenceLowerLimitForMaximumVentingOpenFactor,
                   indoorandOutdoorTemperatureDifferenceLowerLimitForMaximumVentingOpenFactor);
}

void AirflowNetworkMultiZoneSurface_Impl::resetIndoorandOutdoorTemperatureDifferenceLowerLimitForMaximumVentingOpenFactor() {
  OS_ASSERT(setString(openstudio::AirflowNetwork_MultiZone_SurfaceFields::IndoorandOutdoorTemperatureDifferenceLowerLimitForMaximumVentingOpenFactor,
                      ""));
}

double AirflowNetworkMultiZoneSurface_Impl::indoorandOutdoorTemperatureDifferenceUpperLimitforMinimumVentingOpenFactor() const {
  const auto value =
    getDouble(openstudio::AirflowNetwork_MultiZone_SurfaceFields::IndoorandOutdoorTemperatureDifferenceUpperLimitforMinimumVentingOpenFactor, true);
  OS_ASSERT(value);
  return *value;
}

bool AirflowNetworkMultiZoneSurface_Impl::isIndoorandOutdoorTemperatureDifferenceUpperLimitforMinimumVentingOpenFactorDefaulted() const {
  return isEmpty(openstudio::AirflowNetwork_MultiZone_SurfaceFields::IndoorandOutdoorTemperatureDifferenceUpperLimitforMinimumVentingOpenFactor);
}

bool AirflowNetworkMultiZoneSurface_Impl::setIndoorandOutdoorTemperatureDifferenceUpperLimitforMinimumVentingOpenFactor(
  double indoorandOutdoorTemperatureDifferenceUpperLimitforMinimumVentingOpenFactor) {
  return setDouble(openstudio::AirflowNetwork_MultiZone_SurfaceFields::IndoorandOutdoorTemperatureDifferenceUpperLimitforMinimumVentingOpenFactor,
                   indoorandOutdoorTemperatureDifferenceUpperLimitforMinimumVentingOpenFactor);
}

void AirflowNetworkMultiZoneSurface_Impl::resetIndoorandOutdoorTemperatureDifferenceUpperLimitforMinimumVentingOpenFactor() {
  OS_ASSERT(setString(openstudio::AirflowNetwork_MultiZone_SurfaceFields::IndoorandOutdoorTemperatureDifferenceUpperLimitforMinimumVentingOpenFactor,
                      ""));
}

double AirflowNetworkMultiZoneSurface_Impl::indoorandOutdoorEnthalpyDifferenceLowerLimitForMaximumVentingOpenFactor() const {
  const auto value =
    getDouble(openstudio::AirflowNetwork_MultiZone_SurfaceFields::IndoorandOutdoorEnthalpyDifferenceLowerLimitForMaximumVentingOpenFactor, true);
  OS_ASSERT(value);
  return *value;
}

bool AirflowNetworkMultiZoneSurface_Impl::isIndoorandOutdoorEnthalpyDifferenceLowerLimitForMaximumVentingOpenFactorDefaulted() const {
  return isEmpty(openstudio::AirflowNetwork_MultiZone_SurfaceFields::IndoorandOutdoorEnthalpyDifferenceLowerLimitForMaximumVentingOpenFactor);
}

bool AirflowNetworkMultiZoneSurface_Impl::setIndoorandOutdoorEnthalpyDifferenceLowerLimitForMaximumVentingOpenFactor(
  double indoorandOutdoorEnthalpyDifferenceLowerLimitForMaximumVentingOpenFactor) {
  return setDouble(openstudio::AirflowNetwork_MultiZone_SurfaceFields::IndoorandOutdoorEnthalpyDifferenceLowerLimitForMaximumVentingOpenFactor,
                   indoorandOutdoorEnthalpyDifferenceLowerLimitForMaximumVentingOpenFactor);
}

void AirflowNetworkMultiZoneSurface_Impl::resetIndoorandOutdoorEnthalpyDifferenceLowerLimitForMaximumVentingOpenFactor() {
  OS_ASSERT(setString(openstudio::AirflowNetwork_MultiZone_SurfaceFields::IndoorandOutdoorEnthalpyDifferenceLowerLimitForMaximumVentingOpenFactor,
                      ""));
}

double AirflowNetworkMultiZoneSurface_Impl::indoorandOutdoorEnthalpyDifferenceUpperLimitforMinimumVentingOpenFactor() const {
  const auto value =
    getDouble(openstudio::AirflowNetwork_MultiZone_SurfaceFields::IndoorandOutdoorEnthalpyDifferenceUpperLimitforMinimumVentingOpenFactor, true);
  OS_ASSERT(value);
  return *value;
}

bool AirflowNetworkMultiZoneSurface_Impl::isIndoorandOutdoorEnthalpyDifferenceUpperLimitforMinimumVentingOpenFactorDefaulted() const {
  return isEmpty(openstudio::AirflowNetwork_MultiZone_SurfaceFields::IndoorandOutdoorEnthalpyDifferenceUpperLimitforMinimumVentingOpenFactor);
}

bool AirflowNetworkMultiZoneSurface_Impl::setIndoorandOutdoorEnthalpyDifferenceUpperLimitforMinimumVentingOpenFactor(
  double indoorandOutdoorEnthalpyDifferenceUpperLimitforMinimumVentingOpenFactor) {
  return setDouble(openstudio::AirflowNetwork_MultiZone_SurfaceFields::IndoorandOutdoorEnthalpyDifferenceUpperLimitforMinimumVentingOpenFactor,
                   indoorandOutdoorEnthalpyDifferenceUpperLimitforMinimumVentingOpenFactor);
}

void AirflowNetworkMultiZoneSurface_Impl::resetIndoorandOutdoorEnthalpyDifferenceUpperLimitforMinimumVentingOpenFactor() {
  OS_ASSERT(setString(openstudio::AirflowNetwork_MultiZone_SurfaceFields::IndoorandOutdoorEnthalpyDifferenceUpperLimitforMinimumVentingOpenFactor,
                      ""));
}

std::string AirflowNetworkMultiZoneSurface_Impl::equivalentRectangleMethod() const {
  const auto value = getString(openstudio::AirflowNetwork_MultiZone_SurfaceFields::EquivalentRectangleMethod, true);
  OS_ASSERT(value);
  return *value;
}

bool AirflowNetworkMultiZoneSurface_Impl::isEquivalentRectangleMethodDefaulted() const {
  return isEmpty(openstudio::AirflowNetwork_MultiZone_SurfaceFields::EquivalentRectangleMethod);
}

bool AirflowNetworkMultiZoneSurface_Impl::setEquivalentRectangleMethod(const std::string& equivalentRectangleMethod) {
  return setString(openstudio::AirflowNetwork_MultiZone_SurfaceFields::EquivalentRectangleMethod, equivalentRectangleMethod);
}

void AirflowNetworkMultiZoneSurface_Impl::resetEquivalentRectangleMethod() {
  OS_ASSERT(setString(openstudio::AirflowNetwork_MultiZone_SurfaceFields::EquivalentRectangleMethod, ""));
}

double AirflowNetworkMultiZoneSurface_Impl::equivalentRectangleAspectRatio() const {
  const auto value = getDouble(openstudio::AirflowNetwork_MultiZone_SurfaceFields::EquivalentRectangleAspectRatio, true);
  OS_ASSERT(value);
  return *value;
}

bool AirflowNetworkMultiZoneSurface_Impl::isEquivalentRectangleAspectRatioDefaulted() const {
  return isEmpty(openstudio::AirflowNetwork_MultiZone_SurfaceFields::EquivalentRectangleAspectRatio);
}

bool AirflowNetworkMultiZoneSurface_Impl::setEquivalentRectangleAspectRatio(double equivalentRectangleAspectRatio) {
  return setDouble(openstudio::AirflowNetwork_MultiZone_SurfaceFields::EquivalentRectangleAspectRatio, equivalentRectangleAspectRatio);
}

void AirflowNetworkMultiZoneSurface_Impl::resetEquivalentRectangleAspectRatio() {
  OS_ASSERT(setString(openstudio::AirflowNetwork_MultiZone_SurfaceFields::EquivalentRectangleAspectRatio, ""));
}

std::vector<std::string> AirflowNetworkMultiZoneSurface_Impl::ventilationControlModeValues() const {
  return openstudio::epmodel::AirflowNetworkMultiZoneSurface::ventilationControlModeValues();
}

std::vector<std::string> AirflowNetworkMultiZoneSurface_Impl::equivalentRectangleMethodValues() const {
  return openstudio::epmodel::AirflowNetworkMultiZoneSurface::equivalentRectangleMethodValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
