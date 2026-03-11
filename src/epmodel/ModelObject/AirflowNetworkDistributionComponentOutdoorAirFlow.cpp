/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "AirflowNetworkDistributionComponentOutdoorAirFlow.hpp"
#include "AirflowNetworkDistributionComponentOutdoorAirFlow_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/AirflowNetwork_Distribution_Component_OutdoorAirFlow_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

AirflowNetworkDistributionComponentOutdoorAirFlow::AirflowNetworkDistributionComponentOutdoorAirFlow(const Model& model)
  : ModelObject(AirflowNetworkDistributionComponentOutdoorAirFlow::iddObjectType(), model) {}

AirflowNetworkDistributionComponentOutdoorAirFlow::AirflowNetworkDistributionComponentOutdoorAirFlow(
  std::shared_ptr<detail::AirflowNetworkDistributionComponentOutdoorAirFlow_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType AirflowNetworkDistributionComponentOutdoorAirFlow::iddObjectType() {
  return IddObjectType::AirflowNetwork_Distribution_Component_OutdoorAirFlow;
}

double AirflowNetworkDistributionComponentOutdoorAirFlow::airMassFlowCoefficientWhenNoOutdoorAirFlowatReferenceConditions() const {
  return getImpl<detail::AirflowNetworkDistributionComponentOutdoorAirFlow_Impl>()
    ->airMassFlowCoefficientWhenNoOutdoorAirFlowatReferenceConditions();
}

bool AirflowNetworkDistributionComponentOutdoorAirFlow::setAirMassFlowCoefficientWhenNoOutdoorAirFlowatReferenceConditions(
  double airMassFlowCoefficientWhenNoOutdoorAirFlowatReferenceConditions) {
  return getImpl<detail::AirflowNetworkDistributionComponentOutdoorAirFlow_Impl>()
    ->setAirMassFlowCoefficientWhenNoOutdoorAirFlowatReferenceConditions(airMassFlowCoefficientWhenNoOutdoorAirFlowatReferenceConditions);
}

double AirflowNetworkDistributionComponentOutdoorAirFlow::airMassFlowExponentWhenNoOutdoorAirFlow() const {
  return getImpl<detail::AirflowNetworkDistributionComponentOutdoorAirFlow_Impl>()->airMassFlowExponentWhenNoOutdoorAirFlow();
}

bool AirflowNetworkDistributionComponentOutdoorAirFlow::isAirMassFlowExponentWhenNoOutdoorAirFlowDefaulted() const {
  return getImpl<detail::AirflowNetworkDistributionComponentOutdoorAirFlow_Impl>()->isAirMassFlowExponentWhenNoOutdoorAirFlowDefaulted();
}

bool AirflowNetworkDistributionComponentOutdoorAirFlow::setAirMassFlowExponentWhenNoOutdoorAirFlow(double airMassFlowExponentWhenNoOutdoorAirFlow) {
  return getImpl<detail::AirflowNetworkDistributionComponentOutdoorAirFlow_Impl>()
    ->setAirMassFlowExponentWhenNoOutdoorAirFlow(airMassFlowExponentWhenNoOutdoorAirFlow);
}

void AirflowNetworkDistributionComponentOutdoorAirFlow::resetAirMassFlowExponentWhenNoOutdoorAirFlow() {
  getImpl<detail::AirflowNetworkDistributionComponentOutdoorAirFlow_Impl>()->resetAirMassFlowExponentWhenNoOutdoorAirFlow();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

double AirflowNetworkDistributionComponentOutdoorAirFlow_Impl::airMassFlowCoefficientWhenNoOutdoorAirFlowatReferenceConditions() const {
  const auto value = getDouble(
    openstudio::AirflowNetwork_Distribution_Component_OutdoorAirFlowFields::AirMassFlowCoefficientWhenNoOutdoorAirFlowatReferenceConditions,
    true);
  OS_ASSERT(value);
  return *value;
}

bool AirflowNetworkDistributionComponentOutdoorAirFlow_Impl::setAirMassFlowCoefficientWhenNoOutdoorAirFlowatReferenceConditions(
  double airMassFlowCoefficientWhenNoOutdoorAirFlowatReferenceConditions) {
  return setDouble(
    openstudio::AirflowNetwork_Distribution_Component_OutdoorAirFlowFields::AirMassFlowCoefficientWhenNoOutdoorAirFlowatReferenceConditions,
    airMassFlowCoefficientWhenNoOutdoorAirFlowatReferenceConditions);
}

double AirflowNetworkDistributionComponentOutdoorAirFlow_Impl::airMassFlowExponentWhenNoOutdoorAirFlow() const {
  const auto value = getDouble(openstudio::AirflowNetwork_Distribution_Component_OutdoorAirFlowFields::AirMassFlowExponentWhenNoOutdoorAirFlow,
                               true);
  OS_ASSERT(value);
  return *value;
}

bool AirflowNetworkDistributionComponentOutdoorAirFlow_Impl::isAirMassFlowExponentWhenNoOutdoorAirFlowDefaulted() const {
  return isEmpty(openstudio::AirflowNetwork_Distribution_Component_OutdoorAirFlowFields::AirMassFlowExponentWhenNoOutdoorAirFlow);
}

bool AirflowNetworkDistributionComponentOutdoorAirFlow_Impl::setAirMassFlowExponentWhenNoOutdoorAirFlow(
  double airMassFlowExponentWhenNoOutdoorAirFlow) {
  return setDouble(openstudio::AirflowNetwork_Distribution_Component_OutdoorAirFlowFields::AirMassFlowExponentWhenNoOutdoorAirFlow,
                   airMassFlowExponentWhenNoOutdoorAirFlow);
}

void AirflowNetworkDistributionComponentOutdoorAirFlow_Impl::resetAirMassFlowExponentWhenNoOutdoorAirFlow() {
  OS_ASSERT(setString(openstudio::AirflowNetwork_Distribution_Component_OutdoorAirFlowFields::AirMassFlowExponentWhenNoOutdoorAirFlow, ""));
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
