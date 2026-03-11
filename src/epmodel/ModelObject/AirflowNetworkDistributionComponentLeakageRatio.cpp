/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "AirflowNetworkDistributionComponentLeakageRatio.hpp"
#include "AirflowNetworkDistributionComponentLeakageRatio_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/AirflowNetwork_Distribution_Component_LeakageRatio_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

AirflowNetworkDistributionComponentLeakageRatio::AirflowNetworkDistributionComponentLeakageRatio(const Model& model)
  : ModelObject(AirflowNetworkDistributionComponentLeakageRatio::iddObjectType(), model) {}

AirflowNetworkDistributionComponentLeakageRatio::AirflowNetworkDistributionComponentLeakageRatio(
  std::shared_ptr<detail::AirflowNetworkDistributionComponentLeakageRatio_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType AirflowNetworkDistributionComponentLeakageRatio::iddObjectType() {
  return IddObjectType::AirflowNetwork_Distribution_Component_LeakageRatio;
}

boost::optional<double> AirflowNetworkDistributionComponentLeakageRatio::effectiveLeakageRatio() const {
  return getImpl<detail::AirflowNetworkDistributionComponentLeakageRatio_Impl>()->effectiveLeakageRatio();
}

bool AirflowNetworkDistributionComponentLeakageRatio::setEffectiveLeakageRatio(double effectiveLeakageRatio) {
  return getImpl<detail::AirflowNetworkDistributionComponentLeakageRatio_Impl>()->setEffectiveLeakageRatio(effectiveLeakageRatio);
}

void AirflowNetworkDistributionComponentLeakageRatio::resetEffectiveLeakageRatio() {
  getImpl<detail::AirflowNetworkDistributionComponentLeakageRatio_Impl>()->resetEffectiveLeakageRatio();
}

double AirflowNetworkDistributionComponentLeakageRatio::maximumFlowRate() const {
  return getImpl<detail::AirflowNetworkDistributionComponentLeakageRatio_Impl>()->maximumFlowRate();
}

bool AirflowNetworkDistributionComponentLeakageRatio::setMaximumFlowRate(double maximumFlowRate) {
  return getImpl<detail::AirflowNetworkDistributionComponentLeakageRatio_Impl>()->setMaximumFlowRate(maximumFlowRate);
}

double AirflowNetworkDistributionComponentLeakageRatio::referencePressureDifference() const {
  return getImpl<detail::AirflowNetworkDistributionComponentLeakageRatio_Impl>()->referencePressureDifference();
}

bool AirflowNetworkDistributionComponentLeakageRatio::setReferencePressureDifference(double referencePressureDifference) {
  return getImpl<detail::AirflowNetworkDistributionComponentLeakageRatio_Impl>()->setReferencePressureDifference(referencePressureDifference);
}

double AirflowNetworkDistributionComponentLeakageRatio::airMassFlowExponent() const {
  return getImpl<detail::AirflowNetworkDistributionComponentLeakageRatio_Impl>()->airMassFlowExponent();
}

bool AirflowNetworkDistributionComponentLeakageRatio::isAirMassFlowExponentDefaulted() const {
  return getImpl<detail::AirflowNetworkDistributionComponentLeakageRatio_Impl>()->isAirMassFlowExponentDefaulted();
}

bool AirflowNetworkDistributionComponentLeakageRatio::setAirMassFlowExponent(double airMassFlowExponent) {
  return getImpl<detail::AirflowNetworkDistributionComponentLeakageRatio_Impl>()->setAirMassFlowExponent(airMassFlowExponent);
}

void AirflowNetworkDistributionComponentLeakageRatio::resetAirMassFlowExponent() {
  getImpl<detail::AirflowNetworkDistributionComponentLeakageRatio_Impl>()->resetAirMassFlowExponent();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

boost::optional<double> AirflowNetworkDistributionComponentLeakageRatio_Impl::effectiveLeakageRatio() const {
  return getDouble(openstudio::AirflowNetwork_Distribution_Component_LeakageRatioFields::EffectiveLeakageRatio, true);
}

bool AirflowNetworkDistributionComponentLeakageRatio_Impl::setEffectiveLeakageRatio(double effectiveLeakageRatio) {
  return setDouble(openstudio::AirflowNetwork_Distribution_Component_LeakageRatioFields::EffectiveLeakageRatio, effectiveLeakageRatio);
}

void AirflowNetworkDistributionComponentLeakageRatio_Impl::resetEffectiveLeakageRatio() {
  OS_ASSERT(setString(openstudio::AirflowNetwork_Distribution_Component_LeakageRatioFields::EffectiveLeakageRatio, ""));
}

double AirflowNetworkDistributionComponentLeakageRatio_Impl::maximumFlowRate() const {
  const auto value = getDouble(openstudio::AirflowNetwork_Distribution_Component_LeakageRatioFields::MaximumFlowRate, true);
  OS_ASSERT(value);
  return *value;
}

bool AirflowNetworkDistributionComponentLeakageRatio_Impl::setMaximumFlowRate(double maximumFlowRate) {
  return setDouble(openstudio::AirflowNetwork_Distribution_Component_LeakageRatioFields::MaximumFlowRate, maximumFlowRate);
}

double AirflowNetworkDistributionComponentLeakageRatio_Impl::referencePressureDifference() const {
  const auto value = getDouble(openstudio::AirflowNetwork_Distribution_Component_LeakageRatioFields::ReferencePressureDifference, true);
  OS_ASSERT(value);
  return *value;
}

bool AirflowNetworkDistributionComponentLeakageRatio_Impl::setReferencePressureDifference(double referencePressureDifference) {
  return setDouble(openstudio::AirflowNetwork_Distribution_Component_LeakageRatioFields::ReferencePressureDifference, referencePressureDifference);
}

double AirflowNetworkDistributionComponentLeakageRatio_Impl::airMassFlowExponent() const {
  const auto value = getDouble(openstudio::AirflowNetwork_Distribution_Component_LeakageRatioFields::AirMassFlowExponent, true);
  OS_ASSERT(value);
  return *value;
}

bool AirflowNetworkDistributionComponentLeakageRatio_Impl::isAirMassFlowExponentDefaulted() const {
  return isEmpty(openstudio::AirflowNetwork_Distribution_Component_LeakageRatioFields::AirMassFlowExponent);
}

bool AirflowNetworkDistributionComponentLeakageRatio_Impl::setAirMassFlowExponent(double airMassFlowExponent) {
  return setDouble(openstudio::AirflowNetwork_Distribution_Component_LeakageRatioFields::AirMassFlowExponent, airMassFlowExponent);
}

void AirflowNetworkDistributionComponentLeakageRatio_Impl::resetAirMassFlowExponent() {
  OS_ASSERT(setString(openstudio::AirflowNetwork_Distribution_Component_LeakageRatioFields::AirMassFlowExponent, ""));
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
