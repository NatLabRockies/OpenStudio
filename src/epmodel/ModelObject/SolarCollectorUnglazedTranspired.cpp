/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SolarCollectorUnglazedTranspired.hpp"
#include "SolarCollectorUnglazedTranspired_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/SolarCollector_UnglazedTranspired_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

SolarCollectorUnglazedTranspired::SolarCollectorUnglazedTranspired(const Model& model)
  : ModelObject(SolarCollectorUnglazedTranspired::iddObjectType(), model) {}

SolarCollectorUnglazedTranspired::SolarCollectorUnglazedTranspired(std::shared_ptr<detail::SolarCollectorUnglazedTranspired_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType SolarCollectorUnglazedTranspired::iddObjectType() {
  return IddObjectType::SolarCollector_UnglazedTranspired;
}

std::vector<std::string> SolarCollectorUnglazedTranspired::holeLayoutPatternforPitchValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::SolarCollector_UnglazedTranspiredFields::HoleLayoutPatternforPitch);
}

std::vector<std::string> SolarCollectorUnglazedTranspired::heatExchangeEffectivenessCorrelationValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::SolarCollector_UnglazedTranspiredFields::HeatExchangeEffectivenessCorrelation);
}

std::vector<std::string> SolarCollectorUnglazedTranspired::roughnessofCollectorValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::SolarCollector_UnglazedTranspiredFields::RoughnessofCollector);
}

double SolarCollectorUnglazedTranspired::diameterofPerforationsinCollector() const {
  return getImpl<detail::SolarCollectorUnglazedTranspired_Impl>()->diameterofPerforationsinCollector();
}

bool SolarCollectorUnglazedTranspired::setDiameterofPerforationsinCollector(double diameterofPerforationsinCollector) {
  return getImpl<detail::SolarCollectorUnglazedTranspired_Impl>()->setDiameterofPerforationsinCollector(diameterofPerforationsinCollector);
}

double SolarCollectorUnglazedTranspired::distanceBetweenPerforationsinCollector() const {
  return getImpl<detail::SolarCollectorUnglazedTranspired_Impl>()->distanceBetweenPerforationsinCollector();
}

bool SolarCollectorUnglazedTranspired::setDistanceBetweenPerforationsinCollector(double distanceBetweenPerforationsinCollector) {
  return getImpl<detail::SolarCollectorUnglazedTranspired_Impl>()->setDistanceBetweenPerforationsinCollector(distanceBetweenPerforationsinCollector);
}

double SolarCollectorUnglazedTranspired::thermalEmissivityofCollectorSurface() const {
  return getImpl<detail::SolarCollectorUnglazedTranspired_Impl>()->thermalEmissivityofCollectorSurface();
}

bool SolarCollectorUnglazedTranspired::setThermalEmissivityofCollectorSurface(double thermalEmissivityofCollectorSurface) {
  return getImpl<detail::SolarCollectorUnglazedTranspired_Impl>()->setThermalEmissivityofCollectorSurface(thermalEmissivityofCollectorSurface);
}

double SolarCollectorUnglazedTranspired::solarAbsorbtivityofCollectorSurface() const {
  return getImpl<detail::SolarCollectorUnglazedTranspired_Impl>()->solarAbsorbtivityofCollectorSurface();
}

bool SolarCollectorUnglazedTranspired::setSolarAbsorbtivityofCollectorSurface(double solarAbsorbtivityofCollectorSurface) {
  return getImpl<detail::SolarCollectorUnglazedTranspired_Impl>()->setSolarAbsorbtivityofCollectorSurface(solarAbsorbtivityofCollectorSurface);
}

double SolarCollectorUnglazedTranspired::effectiveOverallHeightofCollector() const {
  return getImpl<detail::SolarCollectorUnglazedTranspired_Impl>()->effectiveOverallHeightofCollector();
}

bool SolarCollectorUnglazedTranspired::setEffectiveOverallHeightofCollector(double effectiveOverallHeightofCollector) {
  return getImpl<detail::SolarCollectorUnglazedTranspired_Impl>()->setEffectiveOverallHeightofCollector(effectiveOverallHeightofCollector);
}

double SolarCollectorUnglazedTranspired::effectiveGapThicknessofPlenumBehindCollector() const {
  return getImpl<detail::SolarCollectorUnglazedTranspired_Impl>()->effectiveGapThicknessofPlenumBehindCollector();
}

bool SolarCollectorUnglazedTranspired::setEffectiveGapThicknessofPlenumBehindCollector(double effectiveGapThicknessofPlenumBehindCollector) {
  return getImpl<detail::SolarCollectorUnglazedTranspired_Impl>()->setEffectiveGapThicknessofPlenumBehindCollector(
    effectiveGapThicknessofPlenumBehindCollector);
}

double SolarCollectorUnglazedTranspired::effectiveCrossSectionAreaofPlenumBehindCollector() const {
  return getImpl<detail::SolarCollectorUnglazedTranspired_Impl>()->effectiveCrossSectionAreaofPlenumBehindCollector();
}

bool SolarCollectorUnglazedTranspired::setEffectiveCrossSectionAreaofPlenumBehindCollector(
  double effectiveCrossSectionAreaofPlenumBehindCollector) {
  return getImpl<detail::SolarCollectorUnglazedTranspired_Impl>()->setEffectiveCrossSectionAreaofPlenumBehindCollector(
    effectiveCrossSectionAreaofPlenumBehindCollector);
}

std::string SolarCollectorUnglazedTranspired::holeLayoutPatternforPitch() const {
  return getImpl<detail::SolarCollectorUnglazedTranspired_Impl>()->holeLayoutPatternforPitch();
}

bool SolarCollectorUnglazedTranspired::setHoleLayoutPatternforPitch(const std::string& holeLayoutPatternforPitch) {
  return getImpl<detail::SolarCollectorUnglazedTranspired_Impl>()->setHoleLayoutPatternforPitch(holeLayoutPatternforPitch);
}

bool SolarCollectorUnglazedTranspired::isHoleLayoutPatternforPitchDefaulted() const {
  return getImpl<detail::SolarCollectorUnglazedTranspired_Impl>()->isHoleLayoutPatternforPitchDefaulted();
}

void SolarCollectorUnglazedTranspired::resetHoleLayoutPatternforPitch() {
  getImpl<detail::SolarCollectorUnglazedTranspired_Impl>()->resetHoleLayoutPatternforPitch();
}

std::string SolarCollectorUnglazedTranspired::heatExchangeEffectivenessCorrelation() const {
  return getImpl<detail::SolarCollectorUnglazedTranspired_Impl>()->heatExchangeEffectivenessCorrelation();
}

bool SolarCollectorUnglazedTranspired::setHeatExchangeEffectivenessCorrelation(const std::string& heatExchangeEffectivenessCorrelation) {
  return getImpl<detail::SolarCollectorUnglazedTranspired_Impl>()->setHeatExchangeEffectivenessCorrelation(heatExchangeEffectivenessCorrelation);
}

bool SolarCollectorUnglazedTranspired::isHeatExchangeEffectivenessCorrelationDefaulted() const {
  return getImpl<detail::SolarCollectorUnglazedTranspired_Impl>()->isHeatExchangeEffectivenessCorrelationDefaulted();
}

void SolarCollectorUnglazedTranspired::resetHeatExchangeEffectivenessCorrelation() {
  getImpl<detail::SolarCollectorUnglazedTranspired_Impl>()->resetHeatExchangeEffectivenessCorrelation();
}

double SolarCollectorUnglazedTranspired::ratioofActualCollectorSurfaceAreatoProjectedSurfaceArea() const {
  return getImpl<detail::SolarCollectorUnglazedTranspired_Impl>()->ratioofActualCollectorSurfaceAreatoProjectedSurfaceArea();
}

bool SolarCollectorUnglazedTranspired::setRatioofActualCollectorSurfaceAreatoProjectedSurfaceArea(
  double ratioofActualCollectorSurfaceAreatoProjectedSurfaceArea) {
  return getImpl<detail::SolarCollectorUnglazedTranspired_Impl>()->setRatioofActualCollectorSurfaceAreatoProjectedSurfaceArea(
    ratioofActualCollectorSurfaceAreatoProjectedSurfaceArea);
}

bool SolarCollectorUnglazedTranspired::isRatioofActualCollectorSurfaceAreatoProjectedSurfaceAreaDefaulted() const {
  return getImpl<detail::SolarCollectorUnglazedTranspired_Impl>()->isRatioofActualCollectorSurfaceAreatoProjectedSurfaceAreaDefaulted();
}

void SolarCollectorUnglazedTranspired::resetRatioofActualCollectorSurfaceAreatoProjectedSurfaceArea() {
  getImpl<detail::SolarCollectorUnglazedTranspired_Impl>()->resetRatioofActualCollectorSurfaceAreatoProjectedSurfaceArea();
}

std::string SolarCollectorUnglazedTranspired::roughnessofCollector() const {
  return getImpl<detail::SolarCollectorUnglazedTranspired_Impl>()->roughnessofCollector();
}

bool SolarCollectorUnglazedTranspired::setRoughnessofCollector(const std::string& roughnessofCollector) {
  return getImpl<detail::SolarCollectorUnglazedTranspired_Impl>()->setRoughnessofCollector(roughnessofCollector);
}

boost::optional<double> SolarCollectorUnglazedTranspired::collectorThickness() const {
  return getImpl<detail::SolarCollectorUnglazedTranspired_Impl>()->collectorThickness();
}

bool SolarCollectorUnglazedTranspired::setCollectorThickness(double collectorThickness) {
  return getImpl<detail::SolarCollectorUnglazedTranspired_Impl>()->setCollectorThickness(collectorThickness);
}

void SolarCollectorUnglazedTranspired::resetCollectorThickness() {
  getImpl<detail::SolarCollectorUnglazedTranspired_Impl>()->resetCollectorThickness();
}

double SolarCollectorUnglazedTranspired::effectivenessforPerforationswithRespecttoWind() const {
  return getImpl<detail::SolarCollectorUnglazedTranspired_Impl>()->effectivenessforPerforationswithRespecttoWind();
}

bool SolarCollectorUnglazedTranspired::setEffectivenessforPerforationswithRespecttoWind(
  double effectivenessforPerforationswithRespecttoWind) {
  return getImpl<detail::SolarCollectorUnglazedTranspired_Impl>()->setEffectivenessforPerforationswithRespecttoWind(
    effectivenessforPerforationswithRespecttoWind);
}

bool SolarCollectorUnglazedTranspired::isEffectivenessforPerforationswithRespecttoWindDefaulted() const {
  return getImpl<detail::SolarCollectorUnglazedTranspired_Impl>()->isEffectivenessforPerforationswithRespecttoWindDefaulted();
}

void SolarCollectorUnglazedTranspired::resetEffectivenessforPerforationswithRespecttoWind() {
  getImpl<detail::SolarCollectorUnglazedTranspired_Impl>()->resetEffectivenessforPerforationswithRespecttoWind();
}

double SolarCollectorUnglazedTranspired::dischargeCoefficientforOpeningswithRespecttoBuoyancyDrivenFlow() const {
  return getImpl<detail::SolarCollectorUnglazedTranspired_Impl>()->dischargeCoefficientforOpeningswithRespecttoBuoyancyDrivenFlow();
}

bool SolarCollectorUnglazedTranspired::setDischargeCoefficientforOpeningswithRespecttoBuoyancyDrivenFlow(
  double dischargeCoefficientforOpeningswithRespecttoBuoyancyDrivenFlow) {
  return getImpl<detail::SolarCollectorUnglazedTranspired_Impl>()->setDischargeCoefficientforOpeningswithRespecttoBuoyancyDrivenFlow(
    dischargeCoefficientforOpeningswithRespecttoBuoyancyDrivenFlow);
}

bool SolarCollectorUnglazedTranspired::isDischargeCoefficientforOpeningswithRespecttoBuoyancyDrivenFlowDefaulted() const {
  return getImpl<detail::SolarCollectorUnglazedTranspired_Impl>()->isDischargeCoefficientforOpeningswithRespecttoBuoyancyDrivenFlowDefaulted();
}

void SolarCollectorUnglazedTranspired::resetDischargeCoefficientforOpeningswithRespecttoBuoyancyDrivenFlow() {
  getImpl<detail::SolarCollectorUnglazedTranspired_Impl>()->resetDischargeCoefficientforOpeningswithRespecttoBuoyancyDrivenFlow();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

double SolarCollectorUnglazedTranspired_Impl::diameterofPerforationsinCollector() const {
  const auto value = getDouble(openstudio::SolarCollector_UnglazedTranspiredFields::DiameterofPerforationsinCollector, true);
  OS_ASSERT(value);
  return *value;
}

bool SolarCollectorUnglazedTranspired_Impl::setDiameterofPerforationsinCollector(double diameterofPerforationsinCollector) {
  return setDouble(openstudio::SolarCollector_UnglazedTranspiredFields::DiameterofPerforationsinCollector, diameterofPerforationsinCollector);
}

double SolarCollectorUnglazedTranspired_Impl::distanceBetweenPerforationsinCollector() const {
  const auto value = getDouble(openstudio::SolarCollector_UnglazedTranspiredFields::DistanceBetweenPerforationsinCollector, true);
  OS_ASSERT(value);
  return *value;
}

bool SolarCollectorUnglazedTranspired_Impl::setDistanceBetweenPerforationsinCollector(double distanceBetweenPerforationsinCollector) {
  return setDouble(openstudio::SolarCollector_UnglazedTranspiredFields::DistanceBetweenPerforationsinCollector,
                   distanceBetweenPerforationsinCollector);
}

double SolarCollectorUnglazedTranspired_Impl::thermalEmissivityofCollectorSurface() const {
  const auto value = getDouble(openstudio::SolarCollector_UnglazedTranspiredFields::ThermalEmissivityofCollectorSurface, true);
  OS_ASSERT(value);
  return *value;
}

bool SolarCollectorUnglazedTranspired_Impl::setThermalEmissivityofCollectorSurface(double thermalEmissivityofCollectorSurface) {
  return setDouble(openstudio::SolarCollector_UnglazedTranspiredFields::ThermalEmissivityofCollectorSurface,
                   thermalEmissivityofCollectorSurface);
}

double SolarCollectorUnglazedTranspired_Impl::solarAbsorbtivityofCollectorSurface() const {
  const auto value = getDouble(openstudio::SolarCollector_UnglazedTranspiredFields::SolarAbsorbtivityofCollectorSurface, true);
  OS_ASSERT(value);
  return *value;
}

bool SolarCollectorUnglazedTranspired_Impl::setSolarAbsorbtivityofCollectorSurface(double solarAbsorbtivityofCollectorSurface) {
  return setDouble(openstudio::SolarCollector_UnglazedTranspiredFields::SolarAbsorbtivityofCollectorSurface,
                   solarAbsorbtivityofCollectorSurface);
}

double SolarCollectorUnglazedTranspired_Impl::effectiveOverallHeightofCollector() const {
  const auto value = getDouble(openstudio::SolarCollector_UnglazedTranspiredFields::EffectiveOverallHeightofCollector, true);
  OS_ASSERT(value);
  return *value;
}

bool SolarCollectorUnglazedTranspired_Impl::setEffectiveOverallHeightofCollector(double effectiveOverallHeightofCollector) {
  return setDouble(openstudio::SolarCollector_UnglazedTranspiredFields::EffectiveOverallHeightofCollector, effectiveOverallHeightofCollector);
}

double SolarCollectorUnglazedTranspired_Impl::effectiveGapThicknessofPlenumBehindCollector() const {
  const auto value = getDouble(openstudio::SolarCollector_UnglazedTranspiredFields::EffectiveGapThicknessofPlenumBehindCollector, true);
  OS_ASSERT(value);
  return *value;
}

bool SolarCollectorUnglazedTranspired_Impl::setEffectiveGapThicknessofPlenumBehindCollector(double effectiveGapThicknessofPlenumBehindCollector) {
  return setDouble(openstudio::SolarCollector_UnglazedTranspiredFields::EffectiveGapThicknessofPlenumBehindCollector,
                   effectiveGapThicknessofPlenumBehindCollector);
}

double SolarCollectorUnglazedTranspired_Impl::effectiveCrossSectionAreaofPlenumBehindCollector() const {
  const auto value = getDouble(openstudio::SolarCollector_UnglazedTranspiredFields::EffectiveCrossSectionAreaofPlenumBehindCollector, true);
  OS_ASSERT(value);
  return *value;
}

bool SolarCollectorUnglazedTranspired_Impl::setEffectiveCrossSectionAreaofPlenumBehindCollector(
  double effectiveCrossSectionAreaofPlenumBehindCollector) {
  return setDouble(openstudio::SolarCollector_UnglazedTranspiredFields::EffectiveCrossSectionAreaofPlenumBehindCollector,
                   effectiveCrossSectionAreaofPlenumBehindCollector);
}

std::string SolarCollectorUnglazedTranspired_Impl::holeLayoutPatternforPitch() const {
  const auto value = getString(openstudio::SolarCollector_UnglazedTranspiredFields::HoleLayoutPatternforPitch, true);
  OS_ASSERT(value);
  return *value;
}

bool SolarCollectorUnglazedTranspired_Impl::setHoleLayoutPatternforPitch(const std::string& holeLayoutPatternforPitch) {
  return setString(openstudio::SolarCollector_UnglazedTranspiredFields::HoleLayoutPatternforPitch, holeLayoutPatternforPitch);
}

bool SolarCollectorUnglazedTranspired_Impl::isHoleLayoutPatternforPitchDefaulted() const {
  return isEmpty(openstudio::SolarCollector_UnglazedTranspiredFields::HoleLayoutPatternforPitch);
}

void SolarCollectorUnglazedTranspired_Impl::resetHoleLayoutPatternforPitch() {
  OS_ASSERT(setString(openstudio::SolarCollector_UnglazedTranspiredFields::HoleLayoutPatternforPitch, ""));
}

std::string SolarCollectorUnglazedTranspired_Impl::heatExchangeEffectivenessCorrelation() const {
  const auto value = getString(openstudio::SolarCollector_UnglazedTranspiredFields::HeatExchangeEffectivenessCorrelation, true);
  OS_ASSERT(value);
  return *value;
}

bool SolarCollectorUnglazedTranspired_Impl::setHeatExchangeEffectivenessCorrelation(
  const std::string& heatExchangeEffectivenessCorrelation) {
  return setString(openstudio::SolarCollector_UnglazedTranspiredFields::HeatExchangeEffectivenessCorrelation,
                   heatExchangeEffectivenessCorrelation);
}

bool SolarCollectorUnglazedTranspired_Impl::isHeatExchangeEffectivenessCorrelationDefaulted() const {
  return isEmpty(openstudio::SolarCollector_UnglazedTranspiredFields::HeatExchangeEffectivenessCorrelation);
}

void SolarCollectorUnglazedTranspired_Impl::resetHeatExchangeEffectivenessCorrelation() {
  OS_ASSERT(setString(openstudio::SolarCollector_UnglazedTranspiredFields::HeatExchangeEffectivenessCorrelation, ""));
}

double SolarCollectorUnglazedTranspired_Impl::ratioofActualCollectorSurfaceAreatoProjectedSurfaceArea() const {
  const auto value = getDouble(openstudio::SolarCollector_UnglazedTranspiredFields::RatioofActualCollectorSurfaceAreatoProjectedSurfaceArea, true);
  OS_ASSERT(value);
  return *value;
}

bool SolarCollectorUnglazedTranspired_Impl::setRatioofActualCollectorSurfaceAreatoProjectedSurfaceArea(
  double ratioofActualCollectorSurfaceAreatoProjectedSurfaceArea) {
  return setDouble(openstudio::SolarCollector_UnglazedTranspiredFields::RatioofActualCollectorSurfaceAreatoProjectedSurfaceArea,
                   ratioofActualCollectorSurfaceAreatoProjectedSurfaceArea);
}

bool SolarCollectorUnglazedTranspired_Impl::isRatioofActualCollectorSurfaceAreatoProjectedSurfaceAreaDefaulted() const {
  return isEmpty(openstudio::SolarCollector_UnglazedTranspiredFields::RatioofActualCollectorSurfaceAreatoProjectedSurfaceArea);
}

void SolarCollectorUnglazedTranspired_Impl::resetRatioofActualCollectorSurfaceAreatoProjectedSurfaceArea() {
  OS_ASSERT(setString(openstudio::SolarCollector_UnglazedTranspiredFields::RatioofActualCollectorSurfaceAreatoProjectedSurfaceArea, ""));
}

std::string SolarCollectorUnglazedTranspired_Impl::roughnessofCollector() const {
  const auto value = getString(openstudio::SolarCollector_UnglazedTranspiredFields::RoughnessofCollector, true);
  OS_ASSERT(value);
  return *value;
}

bool SolarCollectorUnglazedTranspired_Impl::setRoughnessofCollector(const std::string& roughnessofCollector) {
  return setString(openstudio::SolarCollector_UnglazedTranspiredFields::RoughnessofCollector, roughnessofCollector);
}

boost::optional<double> SolarCollectorUnglazedTranspired_Impl::collectorThickness() const {
  return getDouble(openstudio::SolarCollector_UnglazedTranspiredFields::CollectorThickness, true);
}

bool SolarCollectorUnglazedTranspired_Impl::setCollectorThickness(double collectorThickness) {
  return setDouble(openstudio::SolarCollector_UnglazedTranspiredFields::CollectorThickness, collectorThickness);
}

void SolarCollectorUnglazedTranspired_Impl::resetCollectorThickness() {
  OS_ASSERT(setString(openstudio::SolarCollector_UnglazedTranspiredFields::CollectorThickness, ""));
}

double SolarCollectorUnglazedTranspired_Impl::effectivenessforPerforationswithRespecttoWind() const {
  const auto value = getDouble(openstudio::SolarCollector_UnglazedTranspiredFields::EffectivenessforPerforationswithRespecttoWind, true);
  OS_ASSERT(value);
  return *value;
}

bool SolarCollectorUnglazedTranspired_Impl::setEffectivenessforPerforationswithRespecttoWind(
  double effectivenessforPerforationswithRespecttoWind) {
  return setDouble(openstudio::SolarCollector_UnglazedTranspiredFields::EffectivenessforPerforationswithRespecttoWind,
                   effectivenessforPerforationswithRespecttoWind);
}

bool SolarCollectorUnglazedTranspired_Impl::isEffectivenessforPerforationswithRespecttoWindDefaulted() const {
  return isEmpty(openstudio::SolarCollector_UnglazedTranspiredFields::EffectivenessforPerforationswithRespecttoWind);
}

void SolarCollectorUnglazedTranspired_Impl::resetEffectivenessforPerforationswithRespecttoWind() {
  OS_ASSERT(setString(openstudio::SolarCollector_UnglazedTranspiredFields::EffectivenessforPerforationswithRespecttoWind, ""));
}

double SolarCollectorUnglazedTranspired_Impl::dischargeCoefficientforOpeningswithRespecttoBuoyancyDrivenFlow() const {
  const auto value =
    getDouble(openstudio::SolarCollector_UnglazedTranspiredFields::DischargeCoefficientforOpeningswithRespecttoBuoyancyDrivenFlow, true);
  OS_ASSERT(value);
  return *value;
}

bool SolarCollectorUnglazedTranspired_Impl::setDischargeCoefficientforOpeningswithRespecttoBuoyancyDrivenFlow(
  double dischargeCoefficientforOpeningswithRespecttoBuoyancyDrivenFlow) {
  return setDouble(openstudio::SolarCollector_UnglazedTranspiredFields::DischargeCoefficientforOpeningswithRespecttoBuoyancyDrivenFlow,
                   dischargeCoefficientforOpeningswithRespecttoBuoyancyDrivenFlow);
}

bool SolarCollectorUnglazedTranspired_Impl::isDischargeCoefficientforOpeningswithRespecttoBuoyancyDrivenFlowDefaulted() const {
  return isEmpty(openstudio::SolarCollector_UnglazedTranspiredFields::DischargeCoefficientforOpeningswithRespecttoBuoyancyDrivenFlow);
}

void SolarCollectorUnglazedTranspired_Impl::resetDischargeCoefficientforOpeningswithRespecttoBuoyancyDrivenFlow() {
  OS_ASSERT(setString(openstudio::SolarCollector_UnglazedTranspiredFields::DischargeCoefficientforOpeningswithRespecttoBuoyancyDrivenFlow, ""));
}

std::vector<std::string> SolarCollectorUnglazedTranspired_Impl::holeLayoutPatternforPitchValues() const {
  return openstudio::epmodel::SolarCollectorUnglazedTranspired::holeLayoutPatternforPitchValues();
}

std::vector<std::string> SolarCollectorUnglazedTranspired_Impl::heatExchangeEffectivenessCorrelationValues() const {
  return openstudio::epmodel::SolarCollectorUnglazedTranspired::heatExchangeEffectivenessCorrelationValues();
}

std::vector<std::string> SolarCollectorUnglazedTranspired_Impl::roughnessofCollectorValues() const {
  return openstudio::epmodel::SolarCollectorUnglazedTranspired::roughnessofCollectorValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
