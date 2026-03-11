/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "GroundHeatTransferBasementSurfaceProps.hpp"
#include "GroundHeatTransferBasementSurfaceProps_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/GroundHeatTransfer_Basement_SurfaceProps_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

GroundHeatTransferBasementSurfaceProps::GroundHeatTransferBasementSurfaceProps(const Model& model)
  : ModelObject(GroundHeatTransferBasementSurfaceProps::iddObjectType(), model) {}

GroundHeatTransferBasementSurfaceProps::GroundHeatTransferBasementSurfaceProps(
  std::shared_ptr<detail::GroundHeatTransferBasementSurfaceProps_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType GroundHeatTransferBasementSurfaceProps::iddObjectType() {
  return IddObjectType::GroundHeatTransfer_Basement_SurfaceProps;
}

double GroundHeatTransferBasementSurfaceProps::aLBEDOSurfacealbedoforNosnowconditions() const {
  return getImpl<detail::GroundHeatTransferBasementSurfaceProps_Impl>()->aLBEDOSurfacealbedoforNosnowconditions();
}

double GroundHeatTransferBasementSurfaceProps::aLBEDOSurfacealbedoforsnowconditions() const {
  return getImpl<detail::GroundHeatTransferBasementSurfaceProps_Impl>()->aLBEDOSurfacealbedoforsnowconditions();
}

double GroundHeatTransferBasementSurfaceProps::ePSLNSurfaceemissivityNoSnow() const {
  return getImpl<detail::GroundHeatTransferBasementSurfaceProps_Impl>()->ePSLNSurfaceemissivityNoSnow();
}

double GroundHeatTransferBasementSurfaceProps::ePSLNSurfaceemissivitywithSnow() const {
  return getImpl<detail::GroundHeatTransferBasementSurfaceProps_Impl>()->ePSLNSurfaceemissivitywithSnow();
}

double GroundHeatTransferBasementSurfaceProps::vEGHTSurfaceroughnessNosnowconditions() const {
  return getImpl<detail::GroundHeatTransferBasementSurfaceProps_Impl>()->vEGHTSurfaceroughnessNosnowconditions();
}

double GroundHeatTransferBasementSurfaceProps::vEGHTSurfaceroughnessSnowconditions() const {
  return getImpl<detail::GroundHeatTransferBasementSurfaceProps_Impl>()->vEGHTSurfaceroughnessSnowconditions();
}

bool GroundHeatTransferBasementSurfaceProps::pETFlagPotentialevapotranspirationon() const {
  return getImpl<detail::GroundHeatTransferBasementSurfaceProps_Impl>()->pETFlagPotentialevapotranspirationon();
}

bool GroundHeatTransferBasementSurfaceProps::isALBEDOSurfacealbedoforNosnowconditionsDefaulted() const {
  return getImpl<detail::GroundHeatTransferBasementSurfaceProps_Impl>()->isALBEDOSurfacealbedoforNosnowconditionsDefaulted();
}

bool GroundHeatTransferBasementSurfaceProps::isALBEDOSurfacealbedoforsnowconditionsDefaulted() const {
  return getImpl<detail::GroundHeatTransferBasementSurfaceProps_Impl>()->isALBEDOSurfacealbedoforsnowconditionsDefaulted();
}

bool GroundHeatTransferBasementSurfaceProps::isEPSLNSurfaceemissivityNoSnowDefaulted() const {
  return getImpl<detail::GroundHeatTransferBasementSurfaceProps_Impl>()->isEPSLNSurfaceemissivityNoSnowDefaulted();
}

bool GroundHeatTransferBasementSurfaceProps::isEPSLNSurfaceemissivitywithSnowDefaulted() const {
  return getImpl<detail::GroundHeatTransferBasementSurfaceProps_Impl>()->isEPSLNSurfaceemissivitywithSnowDefaulted();
}

bool GroundHeatTransferBasementSurfaceProps::isVEGHTSurfaceroughnessNosnowconditionsDefaulted() const {
  return getImpl<detail::GroundHeatTransferBasementSurfaceProps_Impl>()->isVEGHTSurfaceroughnessNosnowconditionsDefaulted();
}

bool GroundHeatTransferBasementSurfaceProps::isVEGHTSurfaceroughnessSnowconditionsDefaulted() const {
  return getImpl<detail::GroundHeatTransferBasementSurfaceProps_Impl>()->isVEGHTSurfaceroughnessSnowconditionsDefaulted();
}

bool GroundHeatTransferBasementSurfaceProps::isPETFlagPotentialevapotranspirationonDefaulted() const {
  return getImpl<detail::GroundHeatTransferBasementSurfaceProps_Impl>()->isPETFlagPotentialevapotranspirationonDefaulted();
}

bool GroundHeatTransferBasementSurfaceProps::setALBEDOSurfacealbedoforNosnowconditions(double aLBEDOSurfacealbedoforNosnowconditions) {
  return getImpl<detail::GroundHeatTransferBasementSurfaceProps_Impl>()->setALBEDOSurfacealbedoforNosnowconditions(
    aLBEDOSurfacealbedoforNosnowconditions);
}

bool GroundHeatTransferBasementSurfaceProps::setALBEDOSurfacealbedoforsnowconditions(double aLBEDOSurfacealbedoforsnowconditions) {
  return getImpl<detail::GroundHeatTransferBasementSurfaceProps_Impl>()->setALBEDOSurfacealbedoforsnowconditions(
    aLBEDOSurfacealbedoforsnowconditions);
}

bool GroundHeatTransferBasementSurfaceProps::setEPSLNSurfaceemissivityNoSnow(double ePSLNSurfaceemissivityNoSnow) {
  return getImpl<detail::GroundHeatTransferBasementSurfaceProps_Impl>()->setEPSLNSurfaceemissivityNoSnow(ePSLNSurfaceemissivityNoSnow);
}

bool GroundHeatTransferBasementSurfaceProps::setEPSLNSurfaceemissivitywithSnow(double ePSLNSurfaceemissivitywithSnow) {
  return getImpl<detail::GroundHeatTransferBasementSurfaceProps_Impl>()->setEPSLNSurfaceemissivitywithSnow(ePSLNSurfaceemissivitywithSnow);
}

bool GroundHeatTransferBasementSurfaceProps::setVEGHTSurfaceroughnessNosnowconditions(double vEGHTSurfaceroughnessNosnowconditions) {
  return getImpl<detail::GroundHeatTransferBasementSurfaceProps_Impl>()->setVEGHTSurfaceroughnessNosnowconditions(
    vEGHTSurfaceroughnessNosnowconditions);
}

bool GroundHeatTransferBasementSurfaceProps::setVEGHTSurfaceroughnessSnowconditions(double vEGHTSurfaceroughnessSnowconditions) {
  return getImpl<detail::GroundHeatTransferBasementSurfaceProps_Impl>()->setVEGHTSurfaceroughnessSnowconditions(
    vEGHTSurfaceroughnessSnowconditions);
}

bool GroundHeatTransferBasementSurfaceProps::setPETFlagPotentialevapotranspirationon(bool pETFlagPotentialevapotranspirationon) {
  return getImpl<detail::GroundHeatTransferBasementSurfaceProps_Impl>()->setPETFlagPotentialevapotranspirationon(
    pETFlagPotentialevapotranspirationon);
}

void GroundHeatTransferBasementSurfaceProps::resetALBEDOSurfacealbedoforNosnowconditions() {
  getImpl<detail::GroundHeatTransferBasementSurfaceProps_Impl>()->resetALBEDOSurfacealbedoforNosnowconditions();
}

void GroundHeatTransferBasementSurfaceProps::resetALBEDOSurfacealbedoforsnowconditions() {
  getImpl<detail::GroundHeatTransferBasementSurfaceProps_Impl>()->resetALBEDOSurfacealbedoforsnowconditions();
}

void GroundHeatTransferBasementSurfaceProps::resetEPSLNSurfaceemissivityNoSnow() {
  getImpl<detail::GroundHeatTransferBasementSurfaceProps_Impl>()->resetEPSLNSurfaceemissivityNoSnow();
}

void GroundHeatTransferBasementSurfaceProps::resetEPSLNSurfaceemissivitywithSnow() {
  getImpl<detail::GroundHeatTransferBasementSurfaceProps_Impl>()->resetEPSLNSurfaceemissivitywithSnow();
}

void GroundHeatTransferBasementSurfaceProps::resetVEGHTSurfaceroughnessNosnowconditions() {
  getImpl<detail::GroundHeatTransferBasementSurfaceProps_Impl>()->resetVEGHTSurfaceroughnessNosnowconditions();
}

void GroundHeatTransferBasementSurfaceProps::resetVEGHTSurfaceroughnessSnowconditions() {
  getImpl<detail::GroundHeatTransferBasementSurfaceProps_Impl>()->resetVEGHTSurfaceroughnessSnowconditions();
}

void GroundHeatTransferBasementSurfaceProps::resetPETFlagPotentialevapotranspirationon() {
  getImpl<detail::GroundHeatTransferBasementSurfaceProps_Impl>()->resetPETFlagPotentialevapotranspirationon();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

double GroundHeatTransferBasementSurfaceProps_Impl::aLBEDOSurfacealbedoforNosnowconditions() const {
  const auto value = getDouble(openstudio::GroundHeatTransfer_Basement_SurfacePropsFields::ALBEDO_SurfacealbedoforNosnowconditions, true);
  OS_ASSERT(value);
  return *value;
}

double GroundHeatTransferBasementSurfaceProps_Impl::aLBEDOSurfacealbedoforsnowconditions() const {
  const auto value = getDouble(openstudio::GroundHeatTransfer_Basement_SurfacePropsFields::ALBEDO_Surfacealbedoforsnowconditions, true);
  OS_ASSERT(value);
  return *value;
}

double GroundHeatTransferBasementSurfaceProps_Impl::ePSLNSurfaceemissivityNoSnow() const {
  const auto value = getDouble(openstudio::GroundHeatTransfer_Basement_SurfacePropsFields::EPSLN_SurfaceemissivityNoSnow, true);
  OS_ASSERT(value);
  return *value;
}

double GroundHeatTransferBasementSurfaceProps_Impl::ePSLNSurfaceemissivitywithSnow() const {
  const auto value = getDouble(openstudio::GroundHeatTransfer_Basement_SurfacePropsFields::EPSLN_SurfaceemissivitywithSnow, true);
  OS_ASSERT(value);
  return *value;
}

double GroundHeatTransferBasementSurfaceProps_Impl::vEGHTSurfaceroughnessNosnowconditions() const {
  const auto value = getDouble(openstudio::GroundHeatTransfer_Basement_SurfacePropsFields::VEGHT_SurfaceroughnessNosnowconditions, true);
  OS_ASSERT(value);
  return *value;
}

double GroundHeatTransferBasementSurfaceProps_Impl::vEGHTSurfaceroughnessSnowconditions() const {
  const auto value = getDouble(openstudio::GroundHeatTransfer_Basement_SurfacePropsFields::VEGHT_SurfaceroughnessSnowconditions, true);
  OS_ASSERT(value);
  return *value;
}

bool GroundHeatTransferBasementSurfaceProps_Impl::pETFlagPotentialevapotranspirationon() const {
  const auto value = getString(openstudio::GroundHeatTransfer_Basement_SurfacePropsFields::PET_FlagPotentialevapotranspirationon, true);
  OS_ASSERT(value);
  return openstudio::istringEqual(*value, "TRUE");
}

bool GroundHeatTransferBasementSurfaceProps_Impl::isALBEDOSurfacealbedoforNosnowconditionsDefaulted() const {
  return isEmpty(openstudio::GroundHeatTransfer_Basement_SurfacePropsFields::ALBEDO_SurfacealbedoforNosnowconditions);
}

bool GroundHeatTransferBasementSurfaceProps_Impl::isALBEDOSurfacealbedoforsnowconditionsDefaulted() const {
  return isEmpty(openstudio::GroundHeatTransfer_Basement_SurfacePropsFields::ALBEDO_Surfacealbedoforsnowconditions);
}

bool GroundHeatTransferBasementSurfaceProps_Impl::isEPSLNSurfaceemissivityNoSnowDefaulted() const {
  return isEmpty(openstudio::GroundHeatTransfer_Basement_SurfacePropsFields::EPSLN_SurfaceemissivityNoSnow);
}

bool GroundHeatTransferBasementSurfaceProps_Impl::isEPSLNSurfaceemissivitywithSnowDefaulted() const {
  return isEmpty(openstudio::GroundHeatTransfer_Basement_SurfacePropsFields::EPSLN_SurfaceemissivitywithSnow);
}

bool GroundHeatTransferBasementSurfaceProps_Impl::isVEGHTSurfaceroughnessNosnowconditionsDefaulted() const {
  return isEmpty(openstudio::GroundHeatTransfer_Basement_SurfacePropsFields::VEGHT_SurfaceroughnessNosnowconditions);
}

bool GroundHeatTransferBasementSurfaceProps_Impl::isVEGHTSurfaceroughnessSnowconditionsDefaulted() const {
  return isEmpty(openstudio::GroundHeatTransfer_Basement_SurfacePropsFields::VEGHT_SurfaceroughnessSnowconditions);
}

bool GroundHeatTransferBasementSurfaceProps_Impl::isPETFlagPotentialevapotranspirationonDefaulted() const {
  return isEmpty(openstudio::GroundHeatTransfer_Basement_SurfacePropsFields::PET_FlagPotentialevapotranspirationon);
}

bool GroundHeatTransferBasementSurfaceProps_Impl::setALBEDOSurfacealbedoforNosnowconditions(double aLBEDOSurfacealbedoforNosnowconditions) {
  return setDouble(openstudio::GroundHeatTransfer_Basement_SurfacePropsFields::ALBEDO_SurfacealbedoforNosnowconditions,
                   aLBEDOSurfacealbedoforNosnowconditions);
}

bool GroundHeatTransferBasementSurfaceProps_Impl::setALBEDOSurfacealbedoforsnowconditions(double aLBEDOSurfacealbedoforsnowconditions) {
  return setDouble(openstudio::GroundHeatTransfer_Basement_SurfacePropsFields::ALBEDO_Surfacealbedoforsnowconditions,
                   aLBEDOSurfacealbedoforsnowconditions);
}

bool GroundHeatTransferBasementSurfaceProps_Impl::setEPSLNSurfaceemissivityNoSnow(double ePSLNSurfaceemissivityNoSnow) {
  return setDouble(openstudio::GroundHeatTransfer_Basement_SurfacePropsFields::EPSLN_SurfaceemissivityNoSnow, ePSLNSurfaceemissivityNoSnow);
}

bool GroundHeatTransferBasementSurfaceProps_Impl::setEPSLNSurfaceemissivitywithSnow(double ePSLNSurfaceemissivitywithSnow) {
  return setDouble(openstudio::GroundHeatTransfer_Basement_SurfacePropsFields::EPSLN_SurfaceemissivitywithSnow, ePSLNSurfaceemissivitywithSnow);
}

bool GroundHeatTransferBasementSurfaceProps_Impl::setVEGHTSurfaceroughnessNosnowconditions(double vEGHTSurfaceroughnessNosnowconditions) {
  return setDouble(openstudio::GroundHeatTransfer_Basement_SurfacePropsFields::VEGHT_SurfaceroughnessNosnowconditions,
                   vEGHTSurfaceroughnessNosnowconditions);
}

bool GroundHeatTransferBasementSurfaceProps_Impl::setVEGHTSurfaceroughnessSnowconditions(double vEGHTSurfaceroughnessSnowconditions) {
  return setDouble(openstudio::GroundHeatTransfer_Basement_SurfacePropsFields::VEGHT_SurfaceroughnessSnowconditions,
                   vEGHTSurfaceroughnessSnowconditions);
}

bool GroundHeatTransferBasementSurfaceProps_Impl::setPETFlagPotentialevapotranspirationon(bool pETFlagPotentialevapotranspirationon) {
  const bool result = setString(openstudio::GroundHeatTransfer_Basement_SurfacePropsFields::PET_FlagPotentialevapotranspirationon,
                                pETFlagPotentialevapotranspirationon ? "TRUE" : "FALSE");
  OS_ASSERT(result);
  return result;
}

void GroundHeatTransferBasementSurfaceProps_Impl::resetALBEDOSurfacealbedoforNosnowconditions() {
  OS_ASSERT(setString(openstudio::GroundHeatTransfer_Basement_SurfacePropsFields::ALBEDO_SurfacealbedoforNosnowconditions, ""));
}

void GroundHeatTransferBasementSurfaceProps_Impl::resetALBEDOSurfacealbedoforsnowconditions() {
  OS_ASSERT(setString(openstudio::GroundHeatTransfer_Basement_SurfacePropsFields::ALBEDO_Surfacealbedoforsnowconditions, ""));
}

void GroundHeatTransferBasementSurfaceProps_Impl::resetEPSLNSurfaceemissivityNoSnow() {
  OS_ASSERT(setString(openstudio::GroundHeatTransfer_Basement_SurfacePropsFields::EPSLN_SurfaceemissivityNoSnow, ""));
}

void GroundHeatTransferBasementSurfaceProps_Impl::resetEPSLNSurfaceemissivitywithSnow() {
  OS_ASSERT(setString(openstudio::GroundHeatTransfer_Basement_SurfacePropsFields::EPSLN_SurfaceemissivitywithSnow, ""));
}

void GroundHeatTransferBasementSurfaceProps_Impl::resetVEGHTSurfaceroughnessNosnowconditions() {
  OS_ASSERT(setString(openstudio::GroundHeatTransfer_Basement_SurfacePropsFields::VEGHT_SurfaceroughnessNosnowconditions, ""));
}

void GroundHeatTransferBasementSurfaceProps_Impl::resetVEGHTSurfaceroughnessSnowconditions() {
  OS_ASSERT(setString(openstudio::GroundHeatTransfer_Basement_SurfacePropsFields::VEGHT_SurfaceroughnessSnowconditions, ""));
}

void GroundHeatTransferBasementSurfaceProps_Impl::resetPETFlagPotentialevapotranspirationon() {
  OS_ASSERT(setString(openstudio::GroundHeatTransfer_Basement_SurfacePropsFields::PET_FlagPotentialevapotranspirationon, ""));
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
