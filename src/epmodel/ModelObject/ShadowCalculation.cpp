/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ShadowCalculation.hpp"
#include "ShadowCalculation_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/ShadowCalculation_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

ShadowCalculation::ShadowCalculation(const Model& model) : ModelObject(ShadowCalculation::iddObjectType(), model) {
  OS_ASSERT(setShadingCalculationMethod("PolygonClipping"));
  OS_ASSERT(setShadingCalculationUpdateFrequency(20));
  OS_ASSERT(setMaximumFiguresInShadowOverlapCalculations(15000));
  OS_ASSERT(setPixelCountingResolution(512));
  OS_ASSERT(setOutputExternalShadingCalculationResults(false));
  OS_ASSERT(setDisableSelfShadingWithinShadingZoneGroups(false));
  OS_ASSERT(setDisableSelfShadingFromShadingZoneGroupstoOtherZones(false));
}

ShadowCalculation::ShadowCalculation(std::shared_ptr<detail::ShadowCalculation_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType ShadowCalculation::iddObjectType() {
  return IddObjectType::ShadowCalculation;
}

std::vector<std::string> ShadowCalculation::shadingCalculationMethodValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::ShadowCalculationFields::ShadingCalculationMethod);
}

std::vector<std::string> ShadowCalculation::validShadingCalculationMethodValues() {
  return ShadowCalculation::shadingCalculationMethodValues();
}

std::vector<std::string> ShadowCalculation::shadingCalculationUpdateFrequencyMethodValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::ShadowCalculationFields::ShadingCalculationUpdateFrequencyMethod);
}

std::vector<std::string> ShadowCalculation::validShadingCalculationUpdateFrequencyMethodValues() {
  return ShadowCalculation::shadingCalculationUpdateFrequencyMethodValues();
}

std::vector<std::string> ShadowCalculation::polygonClippingAlgorithmValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::ShadowCalculationFields::PolygonClippingAlgorithm);
}

std::vector<std::string> ShadowCalculation::validPolygonClippingAlgorithmValues() {
  return ShadowCalculation::polygonClippingAlgorithmValues();
}

std::vector<std::string> ShadowCalculation::skyDiffuseModelingAlgorithmValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::ShadowCalculationFields::SkyDiffuseModelingAlgorithm);
}

std::vector<std::string> ShadowCalculation::validSkyDiffuseModelingAlgorithmValues() {
  return ShadowCalculation::skyDiffuseModelingAlgorithmValues();
}

std::string ShadowCalculation::shadingCalculationMethod() const {
  return getImpl<detail::ShadowCalculation_Impl>()->shadingCalculationMethod();
}

std::string ShadowCalculation::shadingCalculationUpdateFrequencyMethod() const {
  return getImpl<detail::ShadowCalculation_Impl>()->shadingCalculationUpdateFrequencyMethod();
}

bool ShadowCalculation::isShadingCalculationUpdateFrequencyMethodDefaulted() const {
  return getImpl<detail::ShadowCalculation_Impl>()->isShadingCalculationUpdateFrequencyMethodDefaulted();
}

int ShadowCalculation::shadingCalculationUpdateFrequency() const {
  return getImpl<detail::ShadowCalculation_Impl>()->shadingCalculationUpdateFrequency();
}

bool ShadowCalculation::isShadingCalculationUpdateFrequencyDefaulted() const {
  return getImpl<detail::ShadowCalculation_Impl>()->isShadingCalculationUpdateFrequencyDefaulted();
}

int ShadowCalculation::maximumFiguresInShadowOverlapCalculations() const {
  return getImpl<detail::ShadowCalculation_Impl>()->maximumFiguresInShadowOverlapCalculations();
}

bool ShadowCalculation::isMaximumFiguresInShadowOverlapCalculationsDefaulted() const {
  return getImpl<detail::ShadowCalculation_Impl>()->isMaximumFiguresInShadowOverlapCalculationsDefaulted();
}

std::string ShadowCalculation::polygonClippingAlgorithm() const {
  return getImpl<detail::ShadowCalculation_Impl>()->polygonClippingAlgorithm();
}

int ShadowCalculation::pixelCountingResolution() const {
  return getImpl<detail::ShadowCalculation_Impl>()->pixelCountingResolution();
}

std::string ShadowCalculation::skyDiffuseModelingAlgorithm() const {
  return getImpl<detail::ShadowCalculation_Impl>()->skyDiffuseModelingAlgorithm();
}

bool ShadowCalculation::outputExternalShadingCalculationResults() const {
  return getImpl<detail::ShadowCalculation_Impl>()->outputExternalShadingCalculationResults();
}

bool ShadowCalculation::disableSelfShadingWithinShadingZoneGroups() const {
  return getImpl<detail::ShadowCalculation_Impl>()->disableSelfShadingWithinShadingZoneGroups();
}

bool ShadowCalculation::disableSelfShadingFromShadingZoneGroupstoOtherZones() const {
  return getImpl<detail::ShadowCalculation_Impl>()->disableSelfShadingFromShadingZoneGroupstoOtherZones();
}

bool ShadowCalculation::setShadingCalculationMethod(const std::string& shadingCalculationMethod) {
  return getImpl<detail::ShadowCalculation_Impl>()->setShadingCalculationMethod(shadingCalculationMethod);
}

bool ShadowCalculation::setShadingCalculationUpdateFrequencyMethod(const std::string& shadingCalculationUpdateFrequencyMethod) {
  return getImpl<detail::ShadowCalculation_Impl>()->setShadingCalculationUpdateFrequencyMethod(shadingCalculationUpdateFrequencyMethod);
}

void ShadowCalculation::resetShadingCalculationUpdateFrequencyMethod() {
  getImpl<detail::ShadowCalculation_Impl>()->resetShadingCalculationUpdateFrequencyMethod();
}

bool ShadowCalculation::setShadingCalculationUpdateFrequency(int shadingCalculationUpdateFrequency) {
  return getImpl<detail::ShadowCalculation_Impl>()->setShadingCalculationUpdateFrequency(shadingCalculationUpdateFrequency);
}

void ShadowCalculation::resetShadingCalculationUpdateFrequency() {
  getImpl<detail::ShadowCalculation_Impl>()->resetShadingCalculationUpdateFrequency();
}

bool ShadowCalculation::setMaximumFiguresInShadowOverlapCalculations(int maximumFiguresInShadowOverlapCalculations) {
  return getImpl<detail::ShadowCalculation_Impl>()->setMaximumFiguresInShadowOverlapCalculations(maximumFiguresInShadowOverlapCalculations);
}

void ShadowCalculation::resetMaximumFiguresInShadowOverlapCalculations() {
  getImpl<detail::ShadowCalculation_Impl>()->resetMaximumFiguresInShadowOverlapCalculations();
}

bool ShadowCalculation::setPolygonClippingAlgorithm(const std::string& polygonClippingAlgorithm) {
  return getImpl<detail::ShadowCalculation_Impl>()->setPolygonClippingAlgorithm(polygonClippingAlgorithm);
}

void ShadowCalculation::resetPolygonClippingAlgorithm() {
  getImpl<detail::ShadowCalculation_Impl>()->resetPolygonClippingAlgorithm();
}

bool ShadowCalculation::setPixelCountingResolution(int pixelCountingResolution) {
  return getImpl<detail::ShadowCalculation_Impl>()->setPixelCountingResolution(pixelCountingResolution);
}

bool ShadowCalculation::setSkyDiffuseModelingAlgorithm(const std::string& skyDiffuseModelingAlgorithm) {
  return getImpl<detail::ShadowCalculation_Impl>()->setSkyDiffuseModelingAlgorithm(skyDiffuseModelingAlgorithm);
}

void ShadowCalculation::resetSkyDiffuseModelingAlgorithm() {
  getImpl<detail::ShadowCalculation_Impl>()->resetSkyDiffuseModelingAlgorithm();
}

bool ShadowCalculation::setOutputExternalShadingCalculationResults(bool outputExternalShadingCalculationResults) {
  return getImpl<detail::ShadowCalculation_Impl>()->setOutputExternalShadingCalculationResults(outputExternalShadingCalculationResults);
}

bool ShadowCalculation::setDisableSelfShadingWithinShadingZoneGroups(bool disableSelfShadingWithinShadingZoneGroups) {
  return getImpl<detail::ShadowCalculation_Impl>()->setDisableSelfShadingWithinShadingZoneGroups(disableSelfShadingWithinShadingZoneGroups);
}

bool ShadowCalculation::setDisableSelfShadingFromShadingZoneGroupstoOtherZones(bool disableSelfShadingFromShadingZoneGroupstoOtherZones) {
  return getImpl<detail::ShadowCalculation_Impl>()->setDisableSelfShadingFromShadingZoneGroupstoOtherZones(
    disableSelfShadingFromShadingZoneGroupstoOtherZones);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

std::string ShadowCalculation_Impl::shadingCalculationMethod() const {
  const auto value = getString(openstudio::ShadowCalculationFields::ShadingCalculationMethod, true);
  OS_ASSERT(value);
  return *value;
}

std::string ShadowCalculation_Impl::shadingCalculationUpdateFrequencyMethod() const {
  const auto value = getString(openstudio::ShadowCalculationFields::ShadingCalculationUpdateFrequencyMethod, true);
  OS_ASSERT(value);
  return *value;
}

bool ShadowCalculation_Impl::isShadingCalculationUpdateFrequencyMethodDefaulted() const {
  return isEmpty(openstudio::ShadowCalculationFields::ShadingCalculationUpdateFrequencyMethod);
}

int ShadowCalculation_Impl::shadingCalculationUpdateFrequency() const {
  const auto value = getInt(openstudio::ShadowCalculationFields::ShadingCalculationUpdateFrequency, true);
  OS_ASSERT(value);
  return *value;
}

bool ShadowCalculation_Impl::isShadingCalculationUpdateFrequencyDefaulted() const {
  return isEmpty(openstudio::ShadowCalculationFields::ShadingCalculationUpdateFrequency);
}

int ShadowCalculation_Impl::maximumFiguresInShadowOverlapCalculations() const {
  const auto value = getInt(openstudio::ShadowCalculationFields::MaximumFiguresinShadowOverlapCalculations, true);
  OS_ASSERT(value);
  return *value;
}

bool ShadowCalculation_Impl::isMaximumFiguresInShadowOverlapCalculationsDefaulted() const {
  return isEmpty(openstudio::ShadowCalculationFields::MaximumFiguresinShadowOverlapCalculations);
}

std::string ShadowCalculation_Impl::polygonClippingAlgorithm() const {
  const auto value = getString(openstudio::ShadowCalculationFields::PolygonClippingAlgorithm, true);
  OS_ASSERT(value);
  return *value;
}

int ShadowCalculation_Impl::pixelCountingResolution() const {
  const auto value = getInt(openstudio::ShadowCalculationFields::PixelCountingResolution, true);
  OS_ASSERT(value);
  return *value;
}

std::string ShadowCalculation_Impl::skyDiffuseModelingAlgorithm() const {
  const auto value = getString(openstudio::ShadowCalculationFields::SkyDiffuseModelingAlgorithm, true);
  OS_ASSERT(value);
  return *value;
}

bool ShadowCalculation_Impl::outputExternalShadingCalculationResults() const {
  const auto value = getString(openstudio::ShadowCalculationFields::OutputExternalShadingCalculationResults, true);
  OS_ASSERT(value);
  return openstudio::istringEqual(*value, "Yes");
}

bool ShadowCalculation_Impl::disableSelfShadingWithinShadingZoneGroups() const {
  const auto value = getString(openstudio::ShadowCalculationFields::DisableSelfShadingWithinShadingZoneGroups, true);
  OS_ASSERT(value);
  return openstudio::istringEqual(*value, "Yes");
}

bool ShadowCalculation_Impl::disableSelfShadingFromShadingZoneGroupstoOtherZones() const {
  const auto value = getString(openstudio::ShadowCalculationFields::DisableSelfShadingFromShadingZoneGroupstoOtherZones, true);
  OS_ASSERT(value);
  return openstudio::istringEqual(*value, "Yes");
}

bool ShadowCalculation_Impl::setShadingCalculationMethod(const std::string& shadingCalculationMethod) {
  return setString(openstudio::ShadowCalculationFields::ShadingCalculationMethod, shadingCalculationMethod);
}

bool ShadowCalculation_Impl::setShadingCalculationUpdateFrequencyMethod(const std::string& shadingCalculationUpdateFrequencyMethod) {
  return setString(openstudio::ShadowCalculationFields::ShadingCalculationUpdateFrequencyMethod, shadingCalculationUpdateFrequencyMethod);
}

void ShadowCalculation_Impl::resetShadingCalculationUpdateFrequencyMethod() {
  OS_ASSERT(setString(openstudio::ShadowCalculationFields::ShadingCalculationUpdateFrequencyMethod, ""));
}

bool ShadowCalculation_Impl::setShadingCalculationUpdateFrequency(int shadingCalculationUpdateFrequency) {
  return setInt(openstudio::ShadowCalculationFields::ShadingCalculationUpdateFrequency, shadingCalculationUpdateFrequency);
}

void ShadowCalculation_Impl::resetShadingCalculationUpdateFrequency() {
  OS_ASSERT(setString(openstudio::ShadowCalculationFields::ShadingCalculationUpdateFrequency, ""));
}

bool ShadowCalculation_Impl::setMaximumFiguresInShadowOverlapCalculations(int maximumFiguresInShadowOverlapCalculations) {
  return setInt(openstudio::ShadowCalculationFields::MaximumFiguresinShadowOverlapCalculations, maximumFiguresInShadowOverlapCalculations);
}

void ShadowCalculation_Impl::resetMaximumFiguresInShadowOverlapCalculations() {
  OS_ASSERT(setString(openstudio::ShadowCalculationFields::MaximumFiguresinShadowOverlapCalculations, ""));
}

bool ShadowCalculation_Impl::setPolygonClippingAlgorithm(const std::string& polygonClippingAlgorithm) {
  return setString(openstudio::ShadowCalculationFields::PolygonClippingAlgorithm, polygonClippingAlgorithm);
}

void ShadowCalculation_Impl::resetPolygonClippingAlgorithm() {
  OS_ASSERT(setString(openstudio::ShadowCalculationFields::PolygonClippingAlgorithm, ""));
}

bool ShadowCalculation_Impl::setPixelCountingResolution(int pixelCountingResolution) {
  const bool result = setInt(openstudio::ShadowCalculationFields::PixelCountingResolution, pixelCountingResolution);
  OS_ASSERT(result);
  return result;
}

bool ShadowCalculation_Impl::setSkyDiffuseModelingAlgorithm(const std::string& skyDiffuseModelingAlgorithm) {
  return setString(openstudio::ShadowCalculationFields::SkyDiffuseModelingAlgorithm, skyDiffuseModelingAlgorithm);
}

void ShadowCalculation_Impl::resetSkyDiffuseModelingAlgorithm() {
  OS_ASSERT(setString(openstudio::ShadowCalculationFields::SkyDiffuseModelingAlgorithm, ""));
}

bool ShadowCalculation_Impl::setOutputExternalShadingCalculationResults(bool outputExternalShadingCalculationResults) {
  const bool result = outputExternalShadingCalculationResults
                        ? setString(openstudio::ShadowCalculationFields::OutputExternalShadingCalculationResults, "Yes")
                        : setString(openstudio::ShadowCalculationFields::OutputExternalShadingCalculationResults, "No");
  OS_ASSERT(result);
  return result;
}

bool ShadowCalculation_Impl::setDisableSelfShadingWithinShadingZoneGroups(bool disableSelfShadingWithinShadingZoneGroups) {
  const bool result = disableSelfShadingWithinShadingZoneGroups
                        ? setString(openstudio::ShadowCalculationFields::DisableSelfShadingWithinShadingZoneGroups, "Yes")
                        : setString(openstudio::ShadowCalculationFields::DisableSelfShadingWithinShadingZoneGroups, "No");
  OS_ASSERT(result);
  return result;
}

bool ShadowCalculation_Impl::setDisableSelfShadingFromShadingZoneGroupstoOtherZones(bool disableSelfShadingFromShadingZoneGroupstoOtherZones) {
  const bool result = disableSelfShadingFromShadingZoneGroupstoOtherZones
                        ? setString(openstudio::ShadowCalculationFields::DisableSelfShadingFromShadingZoneGroupstoOtherZones, "Yes")
                        : setString(openstudio::ShadowCalculationFields::DisableSelfShadingFromShadingZoneGroupstoOtherZones, "No");
  OS_ASSERT(result);
  return result;
}

std::vector<std::string> ShadowCalculation_Impl::shadingCalculationMethodValues() const {
  return openstudio::epmodel::ShadowCalculation::shadingCalculationMethodValues();
}

std::vector<std::string> ShadowCalculation_Impl::validShadingCalculationMethodValues() const {
  return openstudio::epmodel::ShadowCalculation::validShadingCalculationMethodValues();
}

std::vector<std::string> ShadowCalculation_Impl::shadingCalculationUpdateFrequencyMethodValues() const {
  return openstudio::epmodel::ShadowCalculation::shadingCalculationUpdateFrequencyMethodValues();
}

std::vector<std::string> ShadowCalculation_Impl::validShadingCalculationUpdateFrequencyMethodValues() const {
  return openstudio::epmodel::ShadowCalculation::validShadingCalculationUpdateFrequencyMethodValues();
}

std::vector<std::string> ShadowCalculation_Impl::polygonClippingAlgorithmValues() const {
  return openstudio::epmodel::ShadowCalculation::polygonClippingAlgorithmValues();
}

std::vector<std::string> ShadowCalculation_Impl::validPolygonClippingAlgorithmValues() const {
  return openstudio::epmodel::ShadowCalculation::validPolygonClippingAlgorithmValues();
}

std::vector<std::string> ShadowCalculation_Impl::skyDiffuseModelingAlgorithmValues() const {
  return openstudio::epmodel::ShadowCalculation::skyDiffuseModelingAlgorithmValues();
}

std::vector<std::string> ShadowCalculation_Impl::validSkyDiffuseModelingAlgorithmValues() const {
  return openstudio::epmodel::ShadowCalculation::validSkyDiffuseModelingAlgorithmValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
