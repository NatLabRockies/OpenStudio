/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "AirflowNetworkDistributionComponentReliefAirFlow.hpp"
#include "AirflowNetworkDistributionComponentReliefAirFlow_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/AirflowNetwork_Distribution_Component_ReliefAirFlow_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  AirflowNetworkDistributionComponentReliefAirFlow::AirflowNetworkDistributionComponentReliefAirFlow(const Model& model)
    : ModelObject(AirflowNetworkDistributionComponentReliefAirFlow::iddObjectType(), model) {}

  AirflowNetworkDistributionComponentReliefAirFlow::AirflowNetworkDistributionComponentReliefAirFlow(
    std::shared_ptr<detail::AirflowNetworkDistributionComponentReliefAirFlow_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType AirflowNetworkDistributionComponentReliefAirFlow::iddObjectType() {
    return IddObjectType::AirflowNetwork_Distribution_Component_ReliefAirFlow;
  }

  double AirflowNetworkDistributionComponentReliefAirFlow::airMassFlowCoefficientWhenNoOutdoorAirFlowatReferenceConditions() const {
    return getImpl<detail::AirflowNetworkDistributionComponentReliefAirFlow_Impl>()
      ->airMassFlowCoefficientWhenNoOutdoorAirFlowatReferenceConditions();
  }

  bool AirflowNetworkDistributionComponentReliefAirFlow::setAirMassFlowCoefficientWhenNoOutdoorAirFlowatReferenceConditions(
    double airMassFlowCoefficientWhenNoOutdoorAirFlowatReferenceConditions) {
    return getImpl<detail::AirflowNetworkDistributionComponentReliefAirFlow_Impl>()
      ->setAirMassFlowCoefficientWhenNoOutdoorAirFlowatReferenceConditions(airMassFlowCoefficientWhenNoOutdoorAirFlowatReferenceConditions);
  }

  double AirflowNetworkDistributionComponentReliefAirFlow::airMassFlowExponentWhenNoOutdoorAirFlow() const {
    return getImpl<detail::AirflowNetworkDistributionComponentReliefAirFlow_Impl>()->airMassFlowExponentWhenNoOutdoorAirFlow();
  }

  bool AirflowNetworkDistributionComponentReliefAirFlow::setAirMassFlowExponentWhenNoOutdoorAirFlow(double airMassFlowExponentWhenNoOutdoorAirFlow) {
    return getImpl<detail::AirflowNetworkDistributionComponentReliefAirFlow_Impl>()->setAirMassFlowExponentWhenNoOutdoorAirFlow(
      airMassFlowExponentWhenNoOutdoorAirFlow);
  }

  bool AirflowNetworkDistributionComponentReliefAirFlow::isAirMassFlowExponentWhenNoOutdoorAirFlowDefaulted() const {
    return getImpl<detail::AirflowNetworkDistributionComponentReliefAirFlow_Impl>()->isAirMassFlowExponentWhenNoOutdoorAirFlowDefaulted();
  }

  void AirflowNetworkDistributionComponentReliefAirFlow::resetAirMassFlowExponentWhenNoOutdoorAirFlow() {
    getImpl<detail::AirflowNetworkDistributionComponentReliefAirFlow_Impl>()->resetAirMassFlowExponentWhenNoOutdoorAirFlow();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double AirflowNetworkDistributionComponentReliefAirFlow_Impl::airMassFlowCoefficientWhenNoOutdoorAirFlowatReferenceConditions() const {
      const auto value = getDouble(
        openstudio::AirflowNetwork_Distribution_Component_ReliefAirFlowFields::AirMassFlowCoefficientWhenNoOutdoorAirFlowatReferenceConditions, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirflowNetworkDistributionComponentReliefAirFlow_Impl::setAirMassFlowCoefficientWhenNoOutdoorAirFlowatReferenceConditions(
      double airMassFlowCoefficientWhenNoOutdoorAirFlowatReferenceConditions) {
      return setDouble(
        openstudio::AirflowNetwork_Distribution_Component_ReliefAirFlowFields::AirMassFlowCoefficientWhenNoOutdoorAirFlowatReferenceConditions,
        airMassFlowCoefficientWhenNoOutdoorAirFlowatReferenceConditions);
    }

    double AirflowNetworkDistributionComponentReliefAirFlow_Impl::airMassFlowExponentWhenNoOutdoorAirFlow() const {
      const auto value =
        getDouble(openstudio::AirflowNetwork_Distribution_Component_ReliefAirFlowFields::AirMassFlowExponentWhenNoOutdoorAirFlow, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirflowNetworkDistributionComponentReliefAirFlow_Impl::setAirMassFlowExponentWhenNoOutdoorAirFlow(
      double airMassFlowExponentWhenNoOutdoorAirFlow) {
      return setDouble(openstudio::AirflowNetwork_Distribution_Component_ReliefAirFlowFields::AirMassFlowExponentWhenNoOutdoorAirFlow,
                       airMassFlowExponentWhenNoOutdoorAirFlow);
    }

    bool AirflowNetworkDistributionComponentReliefAirFlow_Impl::isAirMassFlowExponentWhenNoOutdoorAirFlowDefaulted() const {
      return isEmpty(openstudio::AirflowNetwork_Distribution_Component_ReliefAirFlowFields::AirMassFlowExponentWhenNoOutdoorAirFlow);
    }

    void AirflowNetworkDistributionComponentReliefAirFlow_Impl::resetAirMassFlowExponentWhenNoOutdoorAirFlow() {
      OS_ASSERT(setString(openstudio::AirflowNetwork_Distribution_Component_ReliefAirFlowFields::AirMassFlowExponentWhenNoOutdoorAirFlow, ""));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
