/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "AirflowNetworkMultiZoneSurfaceEffectiveLeakageArea.hpp"
#include "AirflowNetworkMultiZoneSurfaceEffectiveLeakageArea_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/AirflowNetwork_MultiZone_Surface_EffectiveLeakageArea_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

AirflowNetworkMultiZoneSurfaceEffectiveLeakageArea::AirflowNetworkMultiZoneSurfaceEffectiveLeakageArea(const Model& model)
  : ModelObject(AirflowNetworkMultiZoneSurfaceEffectiveLeakageArea::iddObjectType(), model) {}

AirflowNetworkMultiZoneSurfaceEffectiveLeakageArea::AirflowNetworkMultiZoneSurfaceEffectiveLeakageArea(
  std::shared_ptr<detail::AirflowNetworkMultiZoneSurfaceEffectiveLeakageArea_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType AirflowNetworkMultiZoneSurfaceEffectiveLeakageArea::iddObjectType() {
  return IddObjectType::AirflowNetwork_MultiZone_Surface_EffectiveLeakageArea;
}

double AirflowNetworkMultiZoneSurfaceEffectiveLeakageArea::effectiveLeakageArea() const {
  return getImpl<detail::AirflowNetworkMultiZoneSurfaceEffectiveLeakageArea_Impl>()->effectiveLeakageArea();
}

bool AirflowNetworkMultiZoneSurfaceEffectiveLeakageArea::setEffectiveLeakageArea(double effectiveLeakageArea) {
  return getImpl<detail::AirflowNetworkMultiZoneSurfaceEffectiveLeakageArea_Impl>()->setEffectiveLeakageArea(effectiveLeakageArea);
}

double AirflowNetworkMultiZoneSurfaceEffectiveLeakageArea::dischargeCoefficient() const {
  return getImpl<detail::AirflowNetworkMultiZoneSurfaceEffectiveLeakageArea_Impl>()->dischargeCoefficient();
}

bool AirflowNetworkMultiZoneSurfaceEffectiveLeakageArea::isDischargeCoefficientDefaulted() const {
  return getImpl<detail::AirflowNetworkMultiZoneSurfaceEffectiveLeakageArea_Impl>()->isDischargeCoefficientDefaulted();
}

bool AirflowNetworkMultiZoneSurfaceEffectiveLeakageArea::setDischargeCoefficient(double dischargeCoefficient) {
  return getImpl<detail::AirflowNetworkMultiZoneSurfaceEffectiveLeakageArea_Impl>()->setDischargeCoefficient(dischargeCoefficient);
}

void AirflowNetworkMultiZoneSurfaceEffectiveLeakageArea::resetDischargeCoefficient() {
  getImpl<detail::AirflowNetworkMultiZoneSurfaceEffectiveLeakageArea_Impl>()->resetDischargeCoefficient();
}

double AirflowNetworkMultiZoneSurfaceEffectiveLeakageArea::referencePressureDifference() const {
  return getImpl<detail::AirflowNetworkMultiZoneSurfaceEffectiveLeakageArea_Impl>()->referencePressureDifference();
}

bool AirflowNetworkMultiZoneSurfaceEffectiveLeakageArea::isReferencePressureDifferenceDefaulted() const {
  return getImpl<detail::AirflowNetworkMultiZoneSurfaceEffectiveLeakageArea_Impl>()->isReferencePressureDifferenceDefaulted();
}

bool AirflowNetworkMultiZoneSurfaceEffectiveLeakageArea::setReferencePressureDifference(double referencePressureDifference) {
  return getImpl<detail::AirflowNetworkMultiZoneSurfaceEffectiveLeakageArea_Impl>()->setReferencePressureDifference(referencePressureDifference);
}

void AirflowNetworkMultiZoneSurfaceEffectiveLeakageArea::resetReferencePressureDifference() {
  getImpl<detail::AirflowNetworkMultiZoneSurfaceEffectiveLeakageArea_Impl>()->resetReferencePressureDifference();
}

double AirflowNetworkMultiZoneSurfaceEffectiveLeakageArea::airMassFlowExponent() const {
  return getImpl<detail::AirflowNetworkMultiZoneSurfaceEffectiveLeakageArea_Impl>()->airMassFlowExponent();
}

bool AirflowNetworkMultiZoneSurfaceEffectiveLeakageArea::isAirMassFlowExponentDefaulted() const {
  return getImpl<detail::AirflowNetworkMultiZoneSurfaceEffectiveLeakageArea_Impl>()->isAirMassFlowExponentDefaulted();
}

bool AirflowNetworkMultiZoneSurfaceEffectiveLeakageArea::setAirMassFlowExponent(double airMassFlowExponent) {
  return getImpl<detail::AirflowNetworkMultiZoneSurfaceEffectiveLeakageArea_Impl>()->setAirMassFlowExponent(airMassFlowExponent);
}

void AirflowNetworkMultiZoneSurfaceEffectiveLeakageArea::resetAirMassFlowExponent() {
  getImpl<detail::AirflowNetworkMultiZoneSurfaceEffectiveLeakageArea_Impl>()->resetAirMassFlowExponent();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

double AirflowNetworkMultiZoneSurfaceEffectiveLeakageArea_Impl::effectiveLeakageArea() const {
  const auto value =
    getDouble(openstudio::AirflowNetwork_MultiZone_Surface_EffectiveLeakageAreaFields::EffectiveLeakageArea, true);
  OS_ASSERT(value);
  return *value;
}

bool AirflowNetworkMultiZoneSurfaceEffectiveLeakageArea_Impl::setEffectiveLeakageArea(double effectiveLeakageArea) {
  const bool result =
    setDouble(openstudio::AirflowNetwork_MultiZone_Surface_EffectiveLeakageAreaFields::EffectiveLeakageArea, effectiveLeakageArea);
  OS_ASSERT(result);
  return result;
}

double AirflowNetworkMultiZoneSurfaceEffectiveLeakageArea_Impl::dischargeCoefficient() const {
  const auto value =
    getDouble(openstudio::AirflowNetwork_MultiZone_Surface_EffectiveLeakageAreaFields::DischargeCoefficient, true);
  OS_ASSERT(value);
  return *value;
}

bool AirflowNetworkMultiZoneSurfaceEffectiveLeakageArea_Impl::isDischargeCoefficientDefaulted() const {
  return isEmpty(openstudio::AirflowNetwork_MultiZone_Surface_EffectiveLeakageAreaFields::DischargeCoefficient);
}

bool AirflowNetworkMultiZoneSurfaceEffectiveLeakageArea_Impl::setDischargeCoefficient(double dischargeCoefficient) {
  const bool result =
    setDouble(openstudio::AirflowNetwork_MultiZone_Surface_EffectiveLeakageAreaFields::DischargeCoefficient, dischargeCoefficient);
  OS_ASSERT(result);
  return result;
}

void AirflowNetworkMultiZoneSurfaceEffectiveLeakageArea_Impl::resetDischargeCoefficient() {
  OS_ASSERT(setString(openstudio::AirflowNetwork_MultiZone_Surface_EffectiveLeakageAreaFields::DischargeCoefficient, ""));
}

double AirflowNetworkMultiZoneSurfaceEffectiveLeakageArea_Impl::referencePressureDifference() const {
  const auto value =
    getDouble(openstudio::AirflowNetwork_MultiZone_Surface_EffectiveLeakageAreaFields::ReferencePressureDifference, true);
  OS_ASSERT(value);
  return *value;
}

bool AirflowNetworkMultiZoneSurfaceEffectiveLeakageArea_Impl::isReferencePressureDifferenceDefaulted() const {
  return isEmpty(openstudio::AirflowNetwork_MultiZone_Surface_EffectiveLeakageAreaFields::ReferencePressureDifference);
}

bool AirflowNetworkMultiZoneSurfaceEffectiveLeakageArea_Impl::setReferencePressureDifference(double referencePressureDifference) {
  const bool result = setDouble(openstudio::AirflowNetwork_MultiZone_Surface_EffectiveLeakageAreaFields::ReferencePressureDifference,
                                referencePressureDifference);
  OS_ASSERT(result);
  return result;
}

void AirflowNetworkMultiZoneSurfaceEffectiveLeakageArea_Impl::resetReferencePressureDifference() {
  OS_ASSERT(setString(openstudio::AirflowNetwork_MultiZone_Surface_EffectiveLeakageAreaFields::ReferencePressureDifference, ""));
}

double AirflowNetworkMultiZoneSurfaceEffectiveLeakageArea_Impl::airMassFlowExponent() const {
  const auto value =
    getDouble(openstudio::AirflowNetwork_MultiZone_Surface_EffectiveLeakageAreaFields::AirMassFlowExponent, true);
  OS_ASSERT(value);
  return *value;
}

bool AirflowNetworkMultiZoneSurfaceEffectiveLeakageArea_Impl::isAirMassFlowExponentDefaulted() const {
  return isEmpty(openstudio::AirflowNetwork_MultiZone_Surface_EffectiveLeakageAreaFields::AirMassFlowExponent);
}

bool AirflowNetworkMultiZoneSurfaceEffectiveLeakageArea_Impl::setAirMassFlowExponent(double airMassFlowExponent) {
  const bool result =
    setDouble(openstudio::AirflowNetwork_MultiZone_Surface_EffectiveLeakageAreaFields::AirMassFlowExponent, airMassFlowExponent);
  OS_ASSERT(result);
  return result;
}

void AirflowNetworkMultiZoneSurfaceEffectiveLeakageArea_Impl::resetAirMassFlowExponent() {
  OS_ASSERT(setString(openstudio::AirflowNetwork_MultiZone_Surface_EffectiveLeakageAreaFields::AirMassFlowExponent, ""));
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
