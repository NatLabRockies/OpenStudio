/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "FoundationKiva.hpp"
#include "FoundationKiva_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/Foundation_Kiva_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

FoundationKiva::FoundationKiva(const Model& model) : ModelObject(FoundationKiva::iddObjectType(), model) {}

FoundationKiva::FoundationKiva(std::shared_ptr<detail::FoundationKiva_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType FoundationKiva::iddObjectType() {
  return IddObjectType::Foundation_Kiva;
}

boost::optional<double> FoundationKiva::initialIndoorAirTemperature() {
  return getImpl<detail::FoundationKiva_Impl>()->initialIndoorAirTemperature();
}

bool FoundationKiva::setInitialIndoorAirTemperature(double initialIndoorAirTemperature) {
  return getImpl<detail::FoundationKiva_Impl>()->setInitialIndoorAirTemperature(initialIndoorAirTemperature);
}

double FoundationKiva::interiorHorizontalInsulationDepth() const {
  return getImpl<detail::FoundationKiva_Impl>()->interiorHorizontalInsulationDepth();
}

bool FoundationKiva::isInteriorHorizontalInsulationDepthDefaulted() const {
  return getImpl<detail::FoundationKiva_Impl>()->isInteriorHorizontalInsulationDepthDefaulted();
}

bool FoundationKiva::setInteriorHorizontalInsulationDepth(double interiorHorizontalInsulationDepth) {
  return getImpl<detail::FoundationKiva_Impl>()->setInteriorHorizontalInsulationDepth(interiorHorizontalInsulationDepth);
}

void FoundationKiva::resetInteriorHorizontalInsulationDepth() {
  getImpl<detail::FoundationKiva_Impl>()->resetInteriorHorizontalInsulationDepth();
}

boost::optional<double> FoundationKiva::interiorHorizontalInsulationWidth() {
  return getImpl<detail::FoundationKiva_Impl>()->interiorHorizontalInsulationWidth();
}

bool FoundationKiva::setInteriorHorizontalInsulationWidth(double interiorHorizontalInsulationWidth) {
  return getImpl<detail::FoundationKiva_Impl>()->setInteriorHorizontalInsulationWidth(interiorHorizontalInsulationWidth);
}

boost::optional<double> FoundationKiva::interiorVerticalInsulationDepth() {
  return getImpl<detail::FoundationKiva_Impl>()->interiorVerticalInsulationDepth();
}

bool FoundationKiva::setInteriorVerticalInsulationDepth(double interiorVerticalInsulationDepth) {
  return getImpl<detail::FoundationKiva_Impl>()->setInteriorVerticalInsulationDepth(interiorVerticalInsulationDepth);
}

boost::optional<double> FoundationKiva::exteriorHorizontalInsulationDepth() {
  return getImpl<detail::FoundationKiva_Impl>()->exteriorHorizontalInsulationDepth();
}

bool FoundationKiva::setExteriorHorizontalInsulationDepth(double exteriorHorizontalInsulationDepth) {
  return getImpl<detail::FoundationKiva_Impl>()->setExteriorHorizontalInsulationDepth(exteriorHorizontalInsulationDepth);
}

double FoundationKiva::exteriorHorizontalInsulationWidth() const {
  return getImpl<detail::FoundationKiva_Impl>()->exteriorHorizontalInsulationWidth();
}

bool FoundationKiva::isExteriorHorizontalInsulationWidthDefaulted() const {
  return getImpl<detail::FoundationKiva_Impl>()->isExteriorHorizontalInsulationWidthDefaulted();
}

bool FoundationKiva::setExteriorHorizontalInsulationWidth(double exteriorHorizontalInsulationWidth) {
  return getImpl<detail::FoundationKiva_Impl>()->setExteriorHorizontalInsulationWidth(exteriorHorizontalInsulationWidth);
}

void FoundationKiva::resetExteriorHorizontalInsulationWidth() {
  getImpl<detail::FoundationKiva_Impl>()->resetExteriorHorizontalInsulationWidth();
}

boost::optional<double> FoundationKiva::exteriorVerticalInsulationDepth() {
  return getImpl<detail::FoundationKiva_Impl>()->exteriorVerticalInsulationDepth();
}

bool FoundationKiva::setExteriorVerticalInsulationDepth(double exteriorVerticalInsulationDepth) {
  return getImpl<detail::FoundationKiva_Impl>()->setExteriorVerticalInsulationDepth(exteriorVerticalInsulationDepth);
}

double FoundationKiva::wallHeightAboveGrade() const {
  return getImpl<detail::FoundationKiva_Impl>()->wallHeightAboveGrade();
}

bool FoundationKiva::isWallHeightAboveGradeDefaulted() const {
  return getImpl<detail::FoundationKiva_Impl>()->isWallHeightAboveGradeDefaulted();
}

bool FoundationKiva::setWallHeightAboveGrade(double wallHeightAboveGrade) {
  return getImpl<detail::FoundationKiva_Impl>()->setWallHeightAboveGrade(wallHeightAboveGrade);
}

void FoundationKiva::resetWallHeightAboveGrade() {
  getImpl<detail::FoundationKiva_Impl>()->resetWallHeightAboveGrade();
}

double FoundationKiva::wallDepthBelowSlab() const {
  return getImpl<detail::FoundationKiva_Impl>()->wallDepthBelowSlab();
}

bool FoundationKiva::isWallDepthBelowSlabDefaulted() const {
  return getImpl<detail::FoundationKiva_Impl>()->isWallDepthBelowSlabDefaulted();
}

bool FoundationKiva::setWallDepthBelowSlab(double wallDepthBelowSlab) {
  return getImpl<detail::FoundationKiva_Impl>()->setWallDepthBelowSlab(wallDepthBelowSlab);
}

void FoundationKiva::resetWallDepthBelowSlab() {
  getImpl<detail::FoundationKiva_Impl>()->resetWallDepthBelowSlab();
}

double FoundationKiva::footingDepth() const {
  return getImpl<detail::FoundationKiva_Impl>()->footingDepth();
}

bool FoundationKiva::isFootingDepthDefaulted() const {
  return getImpl<detail::FoundationKiva_Impl>()->isFootingDepthDefaulted();
}

bool FoundationKiva::setFootingDepth(double footingDepth) {
  return getImpl<detail::FoundationKiva_Impl>()->setFootingDepth(footingDepth);
}

void FoundationKiva::resetFootingDepth() {
  getImpl<detail::FoundationKiva_Impl>()->resetFootingDepth();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

boost::optional<double> FoundationKiva_Impl::initialIndoorAirTemperature() {
  return getDouble(openstudio::Foundation_KivaFields::InitialIndoorAirTemperature);
}

bool FoundationKiva_Impl::setInitialIndoorAirTemperature(double initialIndoorAirTemperature) {
  const bool result = setDouble(openstudio::Foundation_KivaFields::InitialIndoorAirTemperature, initialIndoorAirTemperature);
  OS_ASSERT(result);
  return result;
}

double FoundationKiva_Impl::interiorHorizontalInsulationDepth() const {
  const auto value = getDouble(openstudio::Foundation_KivaFields::InteriorHorizontalInsulationDepth, true);
  OS_ASSERT(value);
  return *value;
}

bool FoundationKiva_Impl::isInteriorHorizontalInsulationDepthDefaulted() const {
  return isEmpty(openstudio::Foundation_KivaFields::InteriorHorizontalInsulationDepth);
}

bool FoundationKiva_Impl::setInteriorHorizontalInsulationDepth(double interiorHorizontalInsulationDepth) {
  const bool result = setDouble(openstudio::Foundation_KivaFields::InteriorHorizontalInsulationDepth, interiorHorizontalInsulationDepth);
  OS_ASSERT(result);
  return result;
}

void FoundationKiva_Impl::resetInteriorHorizontalInsulationDepth() {
  OS_ASSERT(setString(openstudio::Foundation_KivaFields::InteriorHorizontalInsulationDepth, ""));
}

boost::optional<double> FoundationKiva_Impl::interiorHorizontalInsulationWidth() {
  return getDouble(openstudio::Foundation_KivaFields::InteriorHorizontalInsulationWidth);
}

bool FoundationKiva_Impl::setInteriorHorizontalInsulationWidth(double interiorHorizontalInsulationWidth) {
  const bool result = setDouble(openstudio::Foundation_KivaFields::InteriorHorizontalInsulationWidth, interiorHorizontalInsulationWidth);
  OS_ASSERT(result);
  return result;
}

boost::optional<double> FoundationKiva_Impl::interiorVerticalInsulationDepth() {
  return getDouble(openstudio::Foundation_KivaFields::InteriorVerticalInsulationDepth);
}

bool FoundationKiva_Impl::setInteriorVerticalInsulationDepth(double interiorVerticalInsulationDepth) {
  const bool result = setDouble(openstudio::Foundation_KivaFields::InteriorVerticalInsulationDepth, interiorVerticalInsulationDepth);
  OS_ASSERT(result);
  return result;
}

boost::optional<double> FoundationKiva_Impl::exteriorHorizontalInsulationDepth() {
  return getDouble(openstudio::Foundation_KivaFields::ExteriorHorizontalInsulationDepth);
}

bool FoundationKiva_Impl::setExteriorHorizontalInsulationDepth(double exteriorHorizontalInsulationDepth) {
  const bool result = setDouble(openstudio::Foundation_KivaFields::ExteriorHorizontalInsulationDepth, exteriorHorizontalInsulationDepth);
  OS_ASSERT(result);
  return result;
}

double FoundationKiva_Impl::exteriorHorizontalInsulationWidth() const {
  const auto value = getDouble(openstudio::Foundation_KivaFields::ExteriorHorizontalInsulationWidth, true);
  OS_ASSERT(value);
  return *value;
}

bool FoundationKiva_Impl::isExteriorHorizontalInsulationWidthDefaulted() const {
  return isEmpty(openstudio::Foundation_KivaFields::ExteriorHorizontalInsulationWidth);
}

bool FoundationKiva_Impl::setExteriorHorizontalInsulationWidth(double exteriorHorizontalInsulationWidth) {
  const bool result = setDouble(openstudio::Foundation_KivaFields::ExteriorHorizontalInsulationWidth, exteriorHorizontalInsulationWidth);
  OS_ASSERT(result);
  return result;
}

void FoundationKiva_Impl::resetExteriorHorizontalInsulationWidth() {
  OS_ASSERT(setString(openstudio::Foundation_KivaFields::ExteriorHorizontalInsulationWidth, ""));
}

boost::optional<double> FoundationKiva_Impl::exteriorVerticalInsulationDepth() {
  return getDouble(openstudio::Foundation_KivaFields::ExteriorVerticalInsulationDepth);
}

bool FoundationKiva_Impl::setExteriorVerticalInsulationDepth(double exteriorVerticalInsulationDepth) {
  const bool result = setDouble(openstudio::Foundation_KivaFields::ExteriorVerticalInsulationDepth, exteriorVerticalInsulationDepth);
  OS_ASSERT(result);
  return result;
}

double FoundationKiva_Impl::wallHeightAboveGrade() const {
  const auto value = getDouble(openstudio::Foundation_KivaFields::WallHeightAboveGrade, true);
  OS_ASSERT(value);
  return *value;
}

bool FoundationKiva_Impl::isWallHeightAboveGradeDefaulted() const {
  return isEmpty(openstudio::Foundation_KivaFields::WallHeightAboveGrade);
}

bool FoundationKiva_Impl::setWallHeightAboveGrade(double wallHeightAboveGrade) {
  const bool result = setDouble(openstudio::Foundation_KivaFields::WallHeightAboveGrade, wallHeightAboveGrade);
  OS_ASSERT(result);
  return result;
}

void FoundationKiva_Impl::resetWallHeightAboveGrade() {
  OS_ASSERT(setString(openstudio::Foundation_KivaFields::WallHeightAboveGrade, ""));
}

double FoundationKiva_Impl::wallDepthBelowSlab() const {
  const auto value = getDouble(openstudio::Foundation_KivaFields::WallDepthBelowSlab, true);
  OS_ASSERT(value);
  return *value;
}

bool FoundationKiva_Impl::isWallDepthBelowSlabDefaulted() const {
  return isEmpty(openstudio::Foundation_KivaFields::WallDepthBelowSlab);
}

bool FoundationKiva_Impl::setWallDepthBelowSlab(double wallDepthBelowSlab) {
  const bool result = setDouble(openstudio::Foundation_KivaFields::WallDepthBelowSlab, wallDepthBelowSlab);
  OS_ASSERT(result);
  return result;
}

void FoundationKiva_Impl::resetWallDepthBelowSlab() {
  OS_ASSERT(setString(openstudio::Foundation_KivaFields::WallDepthBelowSlab, ""));
}

double FoundationKiva_Impl::footingDepth() const {
  const auto value = getDouble(openstudio::Foundation_KivaFields::FootingDepth, true);
  OS_ASSERT(value);
  return *value;
}

bool FoundationKiva_Impl::isFootingDepthDefaulted() const {
  return isEmpty(openstudio::Foundation_KivaFields::FootingDepth);
}

bool FoundationKiva_Impl::setFootingDepth(double footingDepth) {
  const bool result = setDouble(openstudio::Foundation_KivaFields::FootingDepth, footingDepth);
  OS_ASSERT(result);
  return result;
}

void FoundationKiva_Impl::resetFootingDepth() {
  OS_ASSERT(setString(openstudio::Foundation_KivaFields::FootingDepth, ""));
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
