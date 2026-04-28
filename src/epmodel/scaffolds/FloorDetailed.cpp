/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "FloorDetailed.hpp"
#include "FloorDetailed_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/Floor_Detailed_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

FloorDetailed::FloorDetailed(const Model& model) : ModelObject(FloorDetailed::iddObjectType(), model) {}

FloorDetailed::FloorDetailed(std::shared_ptr<detail::FloorDetailed_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType FloorDetailed::iddObjectType() {
  return IddObjectType::Floor_Detailed;
}

std::vector<std::string> FloorDetailed::outsideBoundaryConditionValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Floor_DetailedFields::OutsideBoundaryCondition);
}

std::vector<std::string> FloorDetailed::sunExposureValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Floor_DetailedFields::SunExposure);
}

std::vector<std::string> FloorDetailed::windExposureValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Floor_DetailedFields::WindExposure);
}

std::string FloorDetailed::outsideBoundaryCondition() const {
  return getImpl<detail::FloorDetailed_Impl>()->outsideBoundaryCondition();
}

bool FloorDetailed::setOutsideBoundaryCondition(const std::string& outsideBoundaryCondition) {
  return getImpl<detail::FloorDetailed_Impl>()->setOutsideBoundaryCondition(outsideBoundaryCondition);
}

std::string FloorDetailed::sunExposure() const {
  return getImpl<detail::FloorDetailed_Impl>()->sunExposure();
}

bool FloorDetailed::isSunExposureDefaulted() const {
  return getImpl<detail::FloorDetailed_Impl>()->isSunExposureDefaulted();
}

bool FloorDetailed::setSunExposure(const std::string& sunExposure) {
  return getImpl<detail::FloorDetailed_Impl>()->setSunExposure(sunExposure);
}

void FloorDetailed::resetSunExposure() {
  getImpl<detail::FloorDetailed_Impl>()->resetSunExposure();
}

std::string FloorDetailed::windExposure() const {
  return getImpl<detail::FloorDetailed_Impl>()->windExposure();
}

bool FloorDetailed::isWindExposureDefaulted() const {
  return getImpl<detail::FloorDetailed_Impl>()->isWindExposureDefaulted();
}

bool FloorDetailed::setWindExposure(const std::string& windExposure) {
  return getImpl<detail::FloorDetailed_Impl>()->setWindExposure(windExposure);
}

void FloorDetailed::resetWindExposure() {
  getImpl<detail::FloorDetailed_Impl>()->resetWindExposure();
}

boost::optional<double> FloorDetailed::viewFactortoGround() const {
  return getImpl<detail::FloorDetailed_Impl>()->viewFactortoGround();
}

bool FloorDetailed::setViewFactortoGround(double viewFactortoGround) {
  return getImpl<detail::FloorDetailed_Impl>()->setViewFactortoGround(viewFactortoGround);
}

bool FloorDetailed::isViewFactortoGroundAutocalculated() const {
  return getImpl<detail::FloorDetailed_Impl>()->isViewFactortoGroundAutocalculated();
}

void FloorDetailed::autocalculateViewFactortoGround() {
  getImpl<detail::FloorDetailed_Impl>()->autocalculateViewFactortoGround();
}

void FloorDetailed::resetViewFactortoGround() {
  getImpl<detail::FloorDetailed_Impl>()->resetViewFactortoGround();
}

boost::optional<int> FloorDetailed::numberofVertices() const {
  return getImpl<detail::FloorDetailed_Impl>()->numberofVertices();
}

bool FloorDetailed::setNumberofVertices(int numberofVertices) {
  return getImpl<detail::FloorDetailed_Impl>()->setNumberofVertices(numberofVertices);
}

bool FloorDetailed::isNumberofVerticesAutocalculated() const {
  return getImpl<detail::FloorDetailed_Impl>()->isNumberofVerticesAutocalculated();
}

void FloorDetailed::autocalculateNumberofVertices() {
  getImpl<detail::FloorDetailed_Impl>()->autocalculateNumberofVertices();
}

void FloorDetailed::resetNumberofVertices() {
  getImpl<detail::FloorDetailed_Impl>()->resetNumberofVertices();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

std::string FloorDetailed_Impl::outsideBoundaryCondition() const {
  const auto value = getString(openstudio::Floor_DetailedFields::OutsideBoundaryCondition, true);
  OS_ASSERT(value);
  return *value;
}

bool FloorDetailed_Impl::setOutsideBoundaryCondition(const std::string& outsideBoundaryCondition) {
  return setString(openstudio::Floor_DetailedFields::OutsideBoundaryCondition, outsideBoundaryCondition);
}

std::string FloorDetailed_Impl::sunExposure() const {
  const auto value = getString(openstudio::Floor_DetailedFields::SunExposure, true);
  OS_ASSERT(value);
  return *value;
}

bool FloorDetailed_Impl::isSunExposureDefaulted() const {
  return isEmpty(openstudio::Floor_DetailedFields::SunExposure);
}

bool FloorDetailed_Impl::setSunExposure(const std::string& sunExposure) {
  return setString(openstudio::Floor_DetailedFields::SunExposure, sunExposure);
}

void FloorDetailed_Impl::resetSunExposure() {
  OS_ASSERT(setString(openstudio::Floor_DetailedFields::SunExposure, ""));
}

std::string FloorDetailed_Impl::windExposure() const {
  const auto value = getString(openstudio::Floor_DetailedFields::WindExposure, true);
  OS_ASSERT(value);
  return *value;
}

bool FloorDetailed_Impl::isWindExposureDefaulted() const {
  return isEmpty(openstudio::Floor_DetailedFields::WindExposure);
}

bool FloorDetailed_Impl::setWindExposure(const std::string& windExposure) {
  return setString(openstudio::Floor_DetailedFields::WindExposure, windExposure);
}

void FloorDetailed_Impl::resetWindExposure() {
  OS_ASSERT(setString(openstudio::Floor_DetailedFields::WindExposure, ""));
}

boost::optional<double> FloorDetailed_Impl::viewFactortoGround() const {
  return getDouble(openstudio::Floor_DetailedFields::ViewFactortoGround, true);
}

bool FloorDetailed_Impl::setViewFactortoGround(double viewFactortoGround) {
  return setDouble(openstudio::Floor_DetailedFields::ViewFactortoGround, viewFactortoGround);
}

bool FloorDetailed_Impl::isViewFactortoGroundAutocalculated() const {
  if (const auto value = getString(openstudio::Floor_DetailedFields::ViewFactortoGround, true)) {
    return openstudio::istringEqual(*value, "autocalculate");
  }
  return false;
}

void FloorDetailed_Impl::autocalculateViewFactortoGround() {
  OS_ASSERT(setString(openstudio::Floor_DetailedFields::ViewFactortoGround, "autocalculate"));
}

void FloorDetailed_Impl::resetViewFactortoGround() {
  OS_ASSERT(setString(openstudio::Floor_DetailedFields::ViewFactortoGround, ""));
}

boost::optional<int> FloorDetailed_Impl::numberofVertices() const {
  return getInt(openstudio::Floor_DetailedFields::NumberofVertices, true);
}

bool FloorDetailed_Impl::setNumberofVertices(int numberofVertices) {
  return setInt(openstudio::Floor_DetailedFields::NumberofVertices, numberofVertices);
}

bool FloorDetailed_Impl::isNumberofVerticesAutocalculated() const {
  if (const auto value = getString(openstudio::Floor_DetailedFields::NumberofVertices, true)) {
    return openstudio::istringEqual(*value, "autocalculate");
  }
  return false;
}

void FloorDetailed_Impl::autocalculateNumberofVertices() {
  OS_ASSERT(setString(openstudio::Floor_DetailedFields::NumberofVertices, "autocalculate"));
}

void FloorDetailed_Impl::resetNumberofVertices() {
  OS_ASSERT(setString(openstudio::Floor_DetailedFields::NumberofVertices, ""));
}

std::vector<std::string> FloorDetailed_Impl::outsideBoundaryConditionValues() const {
  return openstudio::epmodel::FloorDetailed::outsideBoundaryConditionValues();
}

std::vector<std::string> FloorDetailed_Impl::sunExposureValues() const {
  return openstudio::epmodel::FloorDetailed::sunExposureValues();
}

std::vector<std::string> FloorDetailed_Impl::windExposureValues() const {
  return openstudio::epmodel::FloorDetailed::windExposureValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
