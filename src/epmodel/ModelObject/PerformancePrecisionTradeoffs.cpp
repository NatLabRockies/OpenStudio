/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ModelObject/PerformancePrecisionTradeoffs.hpp"
#include "ModelObject/PerformancePrecisionTradeoffs_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/PerformancePrecisionTradeoffs_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

PerformancePrecisionTradeoffs::PerformancePrecisionTradeoffs(const Model& model)
  : ModelObject(PerformancePrecisionTradeoffs::iddObjectType(), model) {}

PerformancePrecisionTradeoffs::PerformancePrecisionTradeoffs(std::shared_ptr<detail::PerformancePrecisionTradeoffs_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType PerformancePrecisionTradeoffs::iddObjectType() {
  return IddObjectType::PerformancePrecisionTradeoffs;
}

std::vector<std::string> PerformancePrecisionTradeoffs::zoneRadiantExchangeAlgorithmValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::PerformancePrecisionTradeoffsFields::ZoneRadiantExchangeAlgorithm);
}

std::vector<std::string> PerformancePrecisionTradeoffs::validZoneRadiantExchangeAlgorithmValues() {
  return PerformancePrecisionTradeoffs::zoneRadiantExchangeAlgorithmValues();
}

std::vector<std::string> PerformancePrecisionTradeoffs::overrideModeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::PerformancePrecisionTradeoffsFields::OverrideMode);
}

std::vector<std::string> PerformancePrecisionTradeoffs::validOverrideModeValues() {
  return PerformancePrecisionTradeoffs::overrideModeValues();
}

bool PerformancePrecisionTradeoffs::useCoilDirectSolutions() const {
  return getImpl<detail::PerformancePrecisionTradeoffs_Impl>()->useCoilDirectSolutions();
}

bool PerformancePrecisionTradeoffs::isUseCoilDirectSolutionsDefaulted() const {
  return getImpl<detail::PerformancePrecisionTradeoffs_Impl>()->isUseCoilDirectSolutionsDefaulted();
}

std::string PerformancePrecisionTradeoffs::zoneRadiantExchangeAlgorithm() const {
  return getImpl<detail::PerformancePrecisionTradeoffs_Impl>()->zoneRadiantExchangeAlgorithm();
}

bool PerformancePrecisionTradeoffs::isZoneRadiantExchangeAlgorithmDefaulted() const {
  return getImpl<detail::PerformancePrecisionTradeoffs_Impl>()->isZoneRadiantExchangeAlgorithmDefaulted();
}

std::string PerformancePrecisionTradeoffs::overrideMode() const {
  return getImpl<detail::PerformancePrecisionTradeoffs_Impl>()->overrideMode();
}

bool PerformancePrecisionTradeoffs::isOverrideModeDefaulted() const {
  return getImpl<detail::PerformancePrecisionTradeoffs_Impl>()->isOverrideModeDefaulted();
}

double PerformancePrecisionTradeoffs::maxZoneTempDiff() const {
  return getImpl<detail::PerformancePrecisionTradeoffs_Impl>()->maxZoneTempDiff();
}

bool PerformancePrecisionTradeoffs::isMaxZoneTempDiffDefaulted() const {
  return getImpl<detail::PerformancePrecisionTradeoffs_Impl>()->isMaxZoneTempDiffDefaulted();
}

double PerformancePrecisionTradeoffs::maxAllowedDelTemp() const {
  return getImpl<detail::PerformancePrecisionTradeoffs_Impl>()->maxAllowedDelTemp();
}

bool PerformancePrecisionTradeoffs::isMaxAllowedDelTempDefaulted() const {
  return getImpl<detail::PerformancePrecisionTradeoffs_Impl>()->isMaxAllowedDelTempDefaulted();
}

bool PerformancePrecisionTradeoffs::useRepresentativeSurfacesforCalculations() const {
  return getImpl<detail::PerformancePrecisionTradeoffs_Impl>()->useRepresentativeSurfacesforCalculations();
}

bool PerformancePrecisionTradeoffs::isUseRepresentativeSurfacesforCalculationsDefaulted() const {
  return getImpl<detail::PerformancePrecisionTradeoffs_Impl>()->isUseRepresentativeSurfacesforCalculationsDefaulted();
}

bool PerformancePrecisionTradeoffs::setUseCoilDirectSolutions(bool useCoilDirectSolutions) {
  return getImpl<detail::PerformancePrecisionTradeoffs_Impl>()->setUseCoilDirectSolutions(useCoilDirectSolutions);
}

void PerformancePrecisionTradeoffs::resetUseCoilDirectSolutions() {
  getImpl<detail::PerformancePrecisionTradeoffs_Impl>()->resetUseCoilDirectSolutions();
}

bool PerformancePrecisionTradeoffs::setZoneRadiantExchangeAlgorithm(const std::string& zoneRadiantExchangeAlgorithm) {
  return getImpl<detail::PerformancePrecisionTradeoffs_Impl>()->setZoneRadiantExchangeAlgorithm(zoneRadiantExchangeAlgorithm);
}

void PerformancePrecisionTradeoffs::resetZoneRadiantExchangeAlgorithm() {
  getImpl<detail::PerformancePrecisionTradeoffs_Impl>()->resetZoneRadiantExchangeAlgorithm();
}

bool PerformancePrecisionTradeoffs::setOverrideMode(const std::string& overrideMode) {
  return getImpl<detail::PerformancePrecisionTradeoffs_Impl>()->setOverrideMode(overrideMode);
}

void PerformancePrecisionTradeoffs::resetOverrideMode() {
  getImpl<detail::PerformancePrecisionTradeoffs_Impl>()->resetOverrideMode();
}

bool PerformancePrecisionTradeoffs::setMaxZoneTempDiff(double maxZoneTempDiff) {
  return getImpl<detail::PerformancePrecisionTradeoffs_Impl>()->setMaxZoneTempDiff(maxZoneTempDiff);
}

void PerformancePrecisionTradeoffs::resetMaxZoneTempDiff() {
  getImpl<detail::PerformancePrecisionTradeoffs_Impl>()->resetMaxZoneTempDiff();
}

bool PerformancePrecisionTradeoffs::setMaxAllowedDelTemp(double maxAllowedDelTemp) {
  return getImpl<detail::PerformancePrecisionTradeoffs_Impl>()->setMaxAllowedDelTemp(maxAllowedDelTemp);
}

void PerformancePrecisionTradeoffs::resetMaxAllowedDelTemp() {
  getImpl<detail::PerformancePrecisionTradeoffs_Impl>()->resetMaxAllowedDelTemp();
}

bool PerformancePrecisionTradeoffs::setUseRepresentativeSurfacesforCalculations(bool useRepresentativeSurfacesforCalculations) {
  return getImpl<detail::PerformancePrecisionTradeoffs_Impl>()->setUseRepresentativeSurfacesforCalculations(
    useRepresentativeSurfacesforCalculations);
}

void PerformancePrecisionTradeoffs::resetUseRepresentativeSurfacesforCalculations() {
  getImpl<detail::PerformancePrecisionTradeoffs_Impl>()->resetUseRepresentativeSurfacesforCalculations();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

bool PerformancePrecisionTradeoffs_Impl::useCoilDirectSolutions() const {
  const auto value = getString(openstudio::PerformancePrecisionTradeoffsFields::UseCoilDirectSolutions, true);
  OS_ASSERT(value);
  return openstudio::istringEqual(*value, "Yes");
}

bool PerformancePrecisionTradeoffs_Impl::isUseCoilDirectSolutionsDefaulted() const {
  return isEmpty(openstudio::PerformancePrecisionTradeoffsFields::UseCoilDirectSolutions);
}

std::string PerformancePrecisionTradeoffs_Impl::zoneRadiantExchangeAlgorithm() const {
  const auto value = getString(openstudio::PerformancePrecisionTradeoffsFields::ZoneRadiantExchangeAlgorithm, true);
  OS_ASSERT(value);
  return *value;
}

bool PerformancePrecisionTradeoffs_Impl::isZoneRadiantExchangeAlgorithmDefaulted() const {
  return isEmpty(openstudio::PerformancePrecisionTradeoffsFields::ZoneRadiantExchangeAlgorithm);
}

std::string PerformancePrecisionTradeoffs_Impl::overrideMode() const {
  const auto value = getString(openstudio::PerformancePrecisionTradeoffsFields::OverrideMode, true);
  OS_ASSERT(value);
  return *value;
}

bool PerformancePrecisionTradeoffs_Impl::isOverrideModeDefaulted() const {
  return isEmpty(openstudio::PerformancePrecisionTradeoffsFields::OverrideMode);
}

double PerformancePrecisionTradeoffs_Impl::maxZoneTempDiff() const {
  const auto value = getDouble(openstudio::PerformancePrecisionTradeoffsFields::MaxZoneTempDiff, true);
  OS_ASSERT(value);
  return *value;
}

bool PerformancePrecisionTradeoffs_Impl::isMaxZoneTempDiffDefaulted() const {
  return isEmpty(openstudio::PerformancePrecisionTradeoffsFields::MaxZoneTempDiff);
}

double PerformancePrecisionTradeoffs_Impl::maxAllowedDelTemp() const {
  const auto value = getDouble(openstudio::PerformancePrecisionTradeoffsFields::MaxAllowedDelTemp, true);
  OS_ASSERT(value);
  return *value;
}

bool PerformancePrecisionTradeoffs_Impl::isMaxAllowedDelTempDefaulted() const {
  return isEmpty(openstudio::PerformancePrecisionTradeoffsFields::MaxAllowedDelTemp);
}

bool PerformancePrecisionTradeoffs_Impl::useRepresentativeSurfacesforCalculations() const {
  const auto value = getString(openstudio::PerformancePrecisionTradeoffsFields::UseRepresentativeSurfacesforCalculations, true);
  OS_ASSERT(value);
  return openstudio::istringEqual(*value, "Yes");
}

bool PerformancePrecisionTradeoffs_Impl::isUseRepresentativeSurfacesforCalculationsDefaulted() const {
  return isEmpty(openstudio::PerformancePrecisionTradeoffsFields::UseRepresentativeSurfacesforCalculations);
}

bool PerformancePrecisionTradeoffs_Impl::setUseCoilDirectSolutions(bool useCoilDirectSolutions) {
  bool result = false;
  if (useCoilDirectSolutions) {
    result = setString(openstudio::PerformancePrecisionTradeoffsFields::UseCoilDirectSolutions, "Yes");
  } else {
    result = setString(openstudio::PerformancePrecisionTradeoffsFields::UseCoilDirectSolutions, "No");
  }
  OS_ASSERT(result);
  return result;
}

void PerformancePrecisionTradeoffs_Impl::resetUseCoilDirectSolutions() {
  OS_ASSERT(setString(openstudio::PerformancePrecisionTradeoffsFields::UseCoilDirectSolutions, ""));
}

bool PerformancePrecisionTradeoffs_Impl::setZoneRadiantExchangeAlgorithm(const std::string& zoneRadiantExchangeAlgorithm) {
  return setString(openstudio::PerformancePrecisionTradeoffsFields::ZoneRadiantExchangeAlgorithm, zoneRadiantExchangeAlgorithm);
}

void PerformancePrecisionTradeoffs_Impl::resetZoneRadiantExchangeAlgorithm() {
  OS_ASSERT(setString(openstudio::PerformancePrecisionTradeoffsFields::ZoneRadiantExchangeAlgorithm, ""));
}

bool PerformancePrecisionTradeoffs_Impl::setOverrideMode(const std::string& overrideMode) {
  return setString(openstudio::PerformancePrecisionTradeoffsFields::OverrideMode, overrideMode);
}

void PerformancePrecisionTradeoffs_Impl::resetOverrideMode() {
  OS_ASSERT(setString(openstudio::PerformancePrecisionTradeoffsFields::OverrideMode, ""));
}

bool PerformancePrecisionTradeoffs_Impl::setMaxZoneTempDiff(double maxZoneTempDiff) {
  return setDouble(openstudio::PerformancePrecisionTradeoffsFields::MaxZoneTempDiff, maxZoneTempDiff);
}

void PerformancePrecisionTradeoffs_Impl::resetMaxZoneTempDiff() {
  OS_ASSERT(setString(openstudio::PerformancePrecisionTradeoffsFields::MaxZoneTempDiff, ""));
}

bool PerformancePrecisionTradeoffs_Impl::setMaxAllowedDelTemp(double maxAllowedDelTemp) {
  return setDouble(openstudio::PerformancePrecisionTradeoffsFields::MaxAllowedDelTemp, maxAllowedDelTemp);
}

void PerformancePrecisionTradeoffs_Impl::resetMaxAllowedDelTemp() {
  OS_ASSERT(setString(openstudio::PerformancePrecisionTradeoffsFields::MaxAllowedDelTemp, ""));
}

bool PerformancePrecisionTradeoffs_Impl::setUseRepresentativeSurfacesforCalculations(bool useRepresentativeSurfacesforCalculations) {
  bool result = false;
  if (useRepresentativeSurfacesforCalculations) {
    result = setString(openstudio::PerformancePrecisionTradeoffsFields::UseRepresentativeSurfacesforCalculations, "Yes");
  } else {
    result = setString(openstudio::PerformancePrecisionTradeoffsFields::UseRepresentativeSurfacesforCalculations, "No");
  }
  OS_ASSERT(result);
  return result;
}

void PerformancePrecisionTradeoffs_Impl::resetUseRepresentativeSurfacesforCalculations() {
  OS_ASSERT(setString(openstudio::PerformancePrecisionTradeoffsFields::UseRepresentativeSurfacesforCalculations, ""));
}

std::vector<std::string> PerformancePrecisionTradeoffs_Impl::zoneRadiantExchangeAlgorithmValues() const {
  return openstudio::epmodel::PerformancePrecisionTradeoffs::zoneRadiantExchangeAlgorithmValues();
}

std::vector<std::string> PerformancePrecisionTradeoffs_Impl::validZoneRadiantExchangeAlgorithmValues() const {
  return openstudio::epmodel::PerformancePrecisionTradeoffs::validZoneRadiantExchangeAlgorithmValues();
}

std::vector<std::string> PerformancePrecisionTradeoffs_Impl::overrideModeValues() const {
  return openstudio::epmodel::PerformancePrecisionTradeoffs::overrideModeValues();
}

std::vector<std::string> PerformancePrecisionTradeoffs_Impl::validOverrideModeValues() const {
  return openstudio::epmodel::PerformancePrecisionTradeoffs::validOverrideModeValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
