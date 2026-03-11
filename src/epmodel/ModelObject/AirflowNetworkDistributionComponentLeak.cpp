/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "AirflowNetworkDistributionComponentLeak.hpp"
#include "AirflowNetworkDistributionComponentLeak_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/AirflowNetwork_Distribution_Component_Leak_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

AirflowNetworkDistributionComponentLeak::AirflowNetworkDistributionComponentLeak(const Model& model)
  : ModelObject(AirflowNetworkDistributionComponentLeak::iddObjectType(), model) {}

AirflowNetworkDistributionComponentLeak::AirflowNetworkDistributionComponentLeak(
  std::shared_ptr<detail::AirflowNetworkDistributionComponentLeak_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType AirflowNetworkDistributionComponentLeak::iddObjectType() {
  return IddObjectType::AirflowNetwork_Distribution_Component_Leak;
}

double AirflowNetworkDistributionComponentLeak::airMassFlowCoefficient() const {
  return getImpl<detail::AirflowNetworkDistributionComponentLeak_Impl>()->airMassFlowCoefficient();
}

bool AirflowNetworkDistributionComponentLeak::setAirMassFlowCoefficient(double airMassFlowCoefficient) {
  return getImpl<detail::AirflowNetworkDistributionComponentLeak_Impl>()->setAirMassFlowCoefficient(airMassFlowCoefficient);
}

double AirflowNetworkDistributionComponentLeak::airMassFlowExponent() const {
  return getImpl<detail::AirflowNetworkDistributionComponentLeak_Impl>()->airMassFlowExponent();
}

bool AirflowNetworkDistributionComponentLeak::isAirMassFlowExponentDefaulted() const {
  return getImpl<detail::AirflowNetworkDistributionComponentLeak_Impl>()->isAirMassFlowExponentDefaulted();
}

bool AirflowNetworkDistributionComponentLeak::setAirMassFlowExponent(double airMassFlowExponent) {
  return getImpl<detail::AirflowNetworkDistributionComponentLeak_Impl>()->setAirMassFlowExponent(airMassFlowExponent);
}

void AirflowNetworkDistributionComponentLeak::resetAirMassFlowExponent() {
  getImpl<detail::AirflowNetworkDistributionComponentLeak_Impl>()->resetAirMassFlowExponent();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

double AirflowNetworkDistributionComponentLeak_Impl::airMassFlowCoefficient() const {
  const auto value = getDouble(openstudio::AirflowNetwork_Distribution_Component_LeakFields::AirMassFlowCoefficient, true);
  OS_ASSERT(value);
  return *value;
}

bool AirflowNetworkDistributionComponentLeak_Impl::setAirMassFlowCoefficient(double airMassFlowCoefficient) {
  const bool result = setDouble(openstudio::AirflowNetwork_Distribution_Component_LeakFields::AirMassFlowCoefficient, airMassFlowCoefficient);
  OS_ASSERT(result);
  return result;
}

double AirflowNetworkDistributionComponentLeak_Impl::airMassFlowExponent() const {
  const auto value = getDouble(openstudio::AirflowNetwork_Distribution_Component_LeakFields::AirMassFlowExponent, true);
  OS_ASSERT(value);
  return *value;
}

bool AirflowNetworkDistributionComponentLeak_Impl::isAirMassFlowExponentDefaulted() const {
  return isEmpty(openstudio::AirflowNetwork_Distribution_Component_LeakFields::AirMassFlowExponent);
}

bool AirflowNetworkDistributionComponentLeak_Impl::setAirMassFlowExponent(double airMassFlowExponent) {
  const bool result = setDouble(openstudio::AirflowNetwork_Distribution_Component_LeakFields::AirMassFlowExponent, airMassFlowExponent);
  OS_ASSERT(result);
  return result;
}

void AirflowNetworkDistributionComponentLeak_Impl::resetAirMassFlowExponent() {
  OS_ASSERT(setString(openstudio::AirflowNetwork_Distribution_Component_LeakFields::AirMassFlowExponent, ""));
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
