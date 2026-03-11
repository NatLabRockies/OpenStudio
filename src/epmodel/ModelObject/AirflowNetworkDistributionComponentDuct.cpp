/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "AirflowNetworkDistributionComponentDuct.hpp"
#include "AirflowNetworkDistributionComponentDuct_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/AirflowNetwork_Distribution_Component_Duct_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

AirflowNetworkDistributionComponentDuct::AirflowNetworkDistributionComponentDuct(const Model& model)
  : ModelObject(AirflowNetworkDistributionComponentDuct::iddObjectType(), model) {}

AirflowNetworkDistributionComponentDuct::AirflowNetworkDistributionComponentDuct(
  std::shared_ptr<detail::AirflowNetworkDistributionComponentDuct_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType AirflowNetworkDistributionComponentDuct::iddObjectType() {
  return IddObjectType::AirflowNetwork_Distribution_Component_Duct;
}

double AirflowNetworkDistributionComponentDuct::ductLength() const {
  return getImpl<detail::AirflowNetworkDistributionComponentDuct_Impl>()->ductLength();
}

bool AirflowNetworkDistributionComponentDuct::setDuctLength(double ductLength) {
  return getImpl<detail::AirflowNetworkDistributionComponentDuct_Impl>()->setDuctLength(ductLength);
}

double AirflowNetworkDistributionComponentDuct::hydraulicDiameter() const {
  return getImpl<detail::AirflowNetworkDistributionComponentDuct_Impl>()->hydraulicDiameter();
}

bool AirflowNetworkDistributionComponentDuct::setHydraulicDiameter(double hydraulicDiameter) {
  return getImpl<detail::AirflowNetworkDistributionComponentDuct_Impl>()->setHydraulicDiameter(hydraulicDiameter);
}

double AirflowNetworkDistributionComponentDuct::crossSectionArea() const {
  return getImpl<detail::AirflowNetworkDistributionComponentDuct_Impl>()->crossSectionArea();
}

bool AirflowNetworkDistributionComponentDuct::setCrossSectionArea(double crossSectionArea) {
  return getImpl<detail::AirflowNetworkDistributionComponentDuct_Impl>()->setCrossSectionArea(crossSectionArea);
}

double AirflowNetworkDistributionComponentDuct::surfaceRoughness() const {
  return getImpl<detail::AirflowNetworkDistributionComponentDuct_Impl>()->surfaceRoughness();
}

bool AirflowNetworkDistributionComponentDuct::isSurfaceRoughnessDefaulted() const {
  return getImpl<detail::AirflowNetworkDistributionComponentDuct_Impl>()->isSurfaceRoughnessDefaulted();
}

bool AirflowNetworkDistributionComponentDuct::setSurfaceRoughness(double surfaceRoughness) {
  return getImpl<detail::AirflowNetworkDistributionComponentDuct_Impl>()->setSurfaceRoughness(surfaceRoughness);
}

void AirflowNetworkDistributionComponentDuct::resetSurfaceRoughness() {
  getImpl<detail::AirflowNetworkDistributionComponentDuct_Impl>()->resetSurfaceRoughness();
}

double AirflowNetworkDistributionComponentDuct::coefficientforLocalDynamicLossDuetoFitting() const {
  return getImpl<detail::AirflowNetworkDistributionComponentDuct_Impl>()->coefficientforLocalDynamicLossDuetoFitting();
}

bool AirflowNetworkDistributionComponentDuct::isCoefficientforLocalDynamicLossDuetoFittingDefaulted() const {
  return getImpl<detail::AirflowNetworkDistributionComponentDuct_Impl>()->isCoefficientforLocalDynamicLossDuetoFittingDefaulted();
}

bool AirflowNetworkDistributionComponentDuct::setCoefficientforLocalDynamicLossDuetoFitting(double coefficientforLocalDynamicLossDuetoFitting) {
  return getImpl<detail::AirflowNetworkDistributionComponentDuct_Impl>()->setCoefficientforLocalDynamicLossDuetoFitting(
    coefficientforLocalDynamicLossDuetoFitting);
}

void AirflowNetworkDistributionComponentDuct::resetCoefficientforLocalDynamicLossDuetoFitting() {
  getImpl<detail::AirflowNetworkDistributionComponentDuct_Impl>()->resetCoefficientforLocalDynamicLossDuetoFitting();
}

double AirflowNetworkDistributionComponentDuct::heatTransmittanceCoefficientUFactorforDuctWallConstruction() const {
  return getImpl<detail::AirflowNetworkDistributionComponentDuct_Impl>()->heatTransmittanceCoefficientUFactorforDuctWallConstruction();
}

bool AirflowNetworkDistributionComponentDuct::isHeatTransmittanceCoefficientUFactorforDuctWallConstructionDefaulted() const {
  return getImpl<detail::AirflowNetworkDistributionComponentDuct_Impl>()->isHeatTransmittanceCoefficientUFactorforDuctWallConstructionDefaulted();
}

bool AirflowNetworkDistributionComponentDuct::setHeatTransmittanceCoefficientUFactorforDuctWallConstruction(
  double heatTransmittanceCoefficientUFactorforDuctWallConstruction) {
  return getImpl<detail::AirflowNetworkDistributionComponentDuct_Impl>()->setHeatTransmittanceCoefficientUFactorforDuctWallConstruction(
    heatTransmittanceCoefficientUFactorforDuctWallConstruction);
}

void AirflowNetworkDistributionComponentDuct::resetHeatTransmittanceCoefficientUFactorforDuctWallConstruction() {
  getImpl<detail::AirflowNetworkDistributionComponentDuct_Impl>()->resetHeatTransmittanceCoefficientUFactorforDuctWallConstruction();
}

double AirflowNetworkDistributionComponentDuct::overallMoistureTransmittanceCoefficientfromAirtoAir() const {
  return getImpl<detail::AirflowNetworkDistributionComponentDuct_Impl>()->overallMoistureTransmittanceCoefficientfromAirtoAir();
}

bool AirflowNetworkDistributionComponentDuct::isOverallMoistureTransmittanceCoefficientfromAirtoAirDefaulted() const {
  return getImpl<detail::AirflowNetworkDistributionComponentDuct_Impl>()->isOverallMoistureTransmittanceCoefficientfromAirtoAirDefaulted();
}

bool AirflowNetworkDistributionComponentDuct::setOverallMoistureTransmittanceCoefficientfromAirtoAir(
  double overallMoistureTransmittanceCoefficientfromAirtoAir) {
  return getImpl<detail::AirflowNetworkDistributionComponentDuct_Impl>()->setOverallMoistureTransmittanceCoefficientfromAirtoAir(
    overallMoistureTransmittanceCoefficientfromAirtoAir);
}

void AirflowNetworkDistributionComponentDuct::resetOverallMoistureTransmittanceCoefficientfromAirtoAir() {
  getImpl<detail::AirflowNetworkDistributionComponentDuct_Impl>()->resetOverallMoistureTransmittanceCoefficientfromAirtoAir();
}

boost::optional<double> AirflowNetworkDistributionComponentDuct::outsideConvectionCoefficient() const {
  return getImpl<detail::AirflowNetworkDistributionComponentDuct_Impl>()->outsideConvectionCoefficient();
}

bool AirflowNetworkDistributionComponentDuct::setOutsideConvectionCoefficient(double outsideConvectionCoefficient) {
  return getImpl<detail::AirflowNetworkDistributionComponentDuct_Impl>()->setOutsideConvectionCoefficient(outsideConvectionCoefficient);
}

void AirflowNetworkDistributionComponentDuct::resetOutsideConvectionCoefficient() {
  getImpl<detail::AirflowNetworkDistributionComponentDuct_Impl>()->resetOutsideConvectionCoefficient();
}

boost::optional<double> AirflowNetworkDistributionComponentDuct::insideConvectionCoefficient() const {
  return getImpl<detail::AirflowNetworkDistributionComponentDuct_Impl>()->insideConvectionCoefficient();
}

bool AirflowNetworkDistributionComponentDuct::setInsideConvectionCoefficient(double insideConvectionCoefficient) {
  return getImpl<detail::AirflowNetworkDistributionComponentDuct_Impl>()->setInsideConvectionCoefficient(insideConvectionCoefficient);
}

void AirflowNetworkDistributionComponentDuct::resetInsideConvectionCoefficient() {
  getImpl<detail::AirflowNetworkDistributionComponentDuct_Impl>()->resetInsideConvectionCoefficient();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

double AirflowNetworkDistributionComponentDuct_Impl::ductLength() const {
  const auto value = getDouble(openstudio::AirflowNetwork_Distribution_Component_DuctFields::DuctLength, true);
  OS_ASSERT(value);
  return *value;
}

bool AirflowNetworkDistributionComponentDuct_Impl::setDuctLength(double ductLength) {
  return setDouble(openstudio::AirflowNetwork_Distribution_Component_DuctFields::DuctLength, ductLength);
}

double AirflowNetworkDistributionComponentDuct_Impl::hydraulicDiameter() const {
  const auto value = getDouble(openstudio::AirflowNetwork_Distribution_Component_DuctFields::HydraulicDiameter, true);
  OS_ASSERT(value);
  return *value;
}

bool AirflowNetworkDistributionComponentDuct_Impl::setHydraulicDiameter(double hydraulicDiameter) {
  return setDouble(openstudio::AirflowNetwork_Distribution_Component_DuctFields::HydraulicDiameter, hydraulicDiameter);
}

double AirflowNetworkDistributionComponentDuct_Impl::crossSectionArea() const {
  const auto value = getDouble(openstudio::AirflowNetwork_Distribution_Component_DuctFields::CrossSectionArea, true);
  OS_ASSERT(value);
  return *value;
}

bool AirflowNetworkDistributionComponentDuct_Impl::setCrossSectionArea(double crossSectionArea) {
  return setDouble(openstudio::AirflowNetwork_Distribution_Component_DuctFields::CrossSectionArea, crossSectionArea);
}

double AirflowNetworkDistributionComponentDuct_Impl::surfaceRoughness() const {
  const auto value = getDouble(openstudio::AirflowNetwork_Distribution_Component_DuctFields::SurfaceRoughness, true);
  OS_ASSERT(value);
  return *value;
}

bool AirflowNetworkDistributionComponentDuct_Impl::isSurfaceRoughnessDefaulted() const {
  return isEmpty(openstudio::AirflowNetwork_Distribution_Component_DuctFields::SurfaceRoughness);
}

bool AirflowNetworkDistributionComponentDuct_Impl::setSurfaceRoughness(double surfaceRoughness) {
  return setDouble(openstudio::AirflowNetwork_Distribution_Component_DuctFields::SurfaceRoughness, surfaceRoughness);
}

void AirflowNetworkDistributionComponentDuct_Impl::resetSurfaceRoughness() {
  OS_ASSERT(setString(openstudio::AirflowNetwork_Distribution_Component_DuctFields::SurfaceRoughness, ""));
}

double AirflowNetworkDistributionComponentDuct_Impl::coefficientforLocalDynamicLossDuetoFitting() const {
  const auto value = getDouble(openstudio::AirflowNetwork_Distribution_Component_DuctFields::CoefficientforLocalDynamicLossDuetoFitting, true);
  OS_ASSERT(value);
  return *value;
}

bool AirflowNetworkDistributionComponentDuct_Impl::isCoefficientforLocalDynamicLossDuetoFittingDefaulted() const {
  return isEmpty(openstudio::AirflowNetwork_Distribution_Component_DuctFields::CoefficientforLocalDynamicLossDuetoFitting);
}

bool AirflowNetworkDistributionComponentDuct_Impl::setCoefficientforLocalDynamicLossDuetoFitting(double coefficientforLocalDynamicLossDuetoFitting) {
  return setDouble(openstudio::AirflowNetwork_Distribution_Component_DuctFields::CoefficientforLocalDynamicLossDuetoFitting,
                   coefficientforLocalDynamicLossDuetoFitting);
}

void AirflowNetworkDistributionComponentDuct_Impl::resetCoefficientforLocalDynamicLossDuetoFitting() {
  OS_ASSERT(setString(openstudio::AirflowNetwork_Distribution_Component_DuctFields::CoefficientforLocalDynamicLossDuetoFitting, ""));
}

double AirflowNetworkDistributionComponentDuct_Impl::heatTransmittanceCoefficientUFactorforDuctWallConstruction() const {
  const auto value =
    getDouble(openstudio::AirflowNetwork_Distribution_Component_DuctFields::HeatTransmittanceCoefficient_UFactor_forDuctWallConstruction, true);
  OS_ASSERT(value);
  return *value;
}

bool AirflowNetworkDistributionComponentDuct_Impl::isHeatTransmittanceCoefficientUFactorforDuctWallConstructionDefaulted() const {
  return isEmpty(openstudio::AirflowNetwork_Distribution_Component_DuctFields::HeatTransmittanceCoefficient_UFactor_forDuctWallConstruction);
}

bool AirflowNetworkDistributionComponentDuct_Impl::setHeatTransmittanceCoefficientUFactorforDuctWallConstruction(
  double heatTransmittanceCoefficientUFactorforDuctWallConstruction) {
  return setDouble(openstudio::AirflowNetwork_Distribution_Component_DuctFields::HeatTransmittanceCoefficient_UFactor_forDuctWallConstruction,
                   heatTransmittanceCoefficientUFactorforDuctWallConstruction);
}

void AirflowNetworkDistributionComponentDuct_Impl::resetHeatTransmittanceCoefficientUFactorforDuctWallConstruction() {
  OS_ASSERT(setString(openstudio::AirflowNetwork_Distribution_Component_DuctFields::HeatTransmittanceCoefficient_UFactor_forDuctWallConstruction,
                      ""));
}

double AirflowNetworkDistributionComponentDuct_Impl::overallMoistureTransmittanceCoefficientfromAirtoAir() const {
  const auto value = getDouble(openstudio::AirflowNetwork_Distribution_Component_DuctFields::OverallMoistureTransmittanceCoefficientfromAirtoAir,
                               true);
  OS_ASSERT(value);
  return *value;
}

bool AirflowNetworkDistributionComponentDuct_Impl::isOverallMoistureTransmittanceCoefficientfromAirtoAirDefaulted() const {
  return isEmpty(openstudio::AirflowNetwork_Distribution_Component_DuctFields::OverallMoistureTransmittanceCoefficientfromAirtoAir);
}

bool AirflowNetworkDistributionComponentDuct_Impl::setOverallMoistureTransmittanceCoefficientfromAirtoAir(
  double overallMoistureTransmittanceCoefficientfromAirtoAir) {
  return setDouble(openstudio::AirflowNetwork_Distribution_Component_DuctFields::OverallMoistureTransmittanceCoefficientfromAirtoAir,
                   overallMoistureTransmittanceCoefficientfromAirtoAir);
}

void AirflowNetworkDistributionComponentDuct_Impl::resetOverallMoistureTransmittanceCoefficientfromAirtoAir() {
  OS_ASSERT(setString(openstudio::AirflowNetwork_Distribution_Component_DuctFields::OverallMoistureTransmittanceCoefficientfromAirtoAir, ""));
}

boost::optional<double> AirflowNetworkDistributionComponentDuct_Impl::outsideConvectionCoefficient() const {
  return getDouble(openstudio::AirflowNetwork_Distribution_Component_DuctFields::OutsideConvectionCoefficient, true);
}

bool AirflowNetworkDistributionComponentDuct_Impl::setOutsideConvectionCoefficient(double outsideConvectionCoefficient) {
  return setDouble(openstudio::AirflowNetwork_Distribution_Component_DuctFields::OutsideConvectionCoefficient, outsideConvectionCoefficient);
}

void AirflowNetworkDistributionComponentDuct_Impl::resetOutsideConvectionCoefficient() {
  OS_ASSERT(setString(openstudio::AirflowNetwork_Distribution_Component_DuctFields::OutsideConvectionCoefficient, ""));
}

boost::optional<double> AirflowNetworkDistributionComponentDuct_Impl::insideConvectionCoefficient() const {
  return getDouble(openstudio::AirflowNetwork_Distribution_Component_DuctFields::InsideConvectionCoefficient, true);
}

bool AirflowNetworkDistributionComponentDuct_Impl::setInsideConvectionCoefficient(double insideConvectionCoefficient) {
  return setDouble(openstudio::AirflowNetwork_Distribution_Component_DuctFields::InsideConvectionCoefficient, insideConvectionCoefficient);
}

void AirflowNetworkDistributionComponentDuct_Impl::resetInsideConvectionCoefficient() {
  OS_ASSERT(setString(openstudio::AirflowNetwork_Distribution_Component_DuctFields::InsideConvectionCoefficient, ""));
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
