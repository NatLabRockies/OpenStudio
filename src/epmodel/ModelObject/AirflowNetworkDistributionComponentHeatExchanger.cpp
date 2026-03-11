/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "AirflowNetworkDistributionComponentHeatExchanger.hpp"
#include "AirflowNetworkDistributionComponentHeatExchanger_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/AirflowNetwork_Distribution_Component_HeatExchanger_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

AirflowNetworkDistributionComponentHeatExchanger::AirflowNetworkDistributionComponentHeatExchanger(const Model& model)
  : ModelObject(AirflowNetworkDistributionComponentHeatExchanger::iddObjectType(), model) {}

AirflowNetworkDistributionComponentHeatExchanger::AirflowNetworkDistributionComponentHeatExchanger(
  std::shared_ptr<detail::AirflowNetworkDistributionComponentHeatExchanger_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType AirflowNetworkDistributionComponentHeatExchanger::iddObjectType() {
  return IddObjectType::AirflowNetwork_Distribution_Component_HeatExchanger;
}

double AirflowNetworkDistributionComponentHeatExchanger::airPathLength() const {
  return getImpl<detail::AirflowNetworkDistributionComponentHeatExchanger_Impl>()->airPathLength();
}

bool AirflowNetworkDistributionComponentHeatExchanger::setAirPathLength(double airPathLength) {
  return getImpl<detail::AirflowNetworkDistributionComponentHeatExchanger_Impl>()->setAirPathLength(airPathLength);
}

double AirflowNetworkDistributionComponentHeatExchanger::airPathHydraulicDiameter() const {
  return getImpl<detail::AirflowNetworkDistributionComponentHeatExchanger_Impl>()->airPathHydraulicDiameter();
}

bool AirflowNetworkDistributionComponentHeatExchanger::setAirPathHydraulicDiameter(double airPathHydraulicDiameter) {
  return getImpl<detail::AirflowNetworkDistributionComponentHeatExchanger_Impl>()->setAirPathHydraulicDiameter(airPathHydraulicDiameter);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

double AirflowNetworkDistributionComponentHeatExchanger_Impl::airPathLength() const {
  const auto value = getDouble(openstudio::AirflowNetwork_Distribution_Component_HeatExchangerFields::AirPathLength, true);
  OS_ASSERT(value);
  return *value;
}

bool AirflowNetworkDistributionComponentHeatExchanger_Impl::setAirPathLength(double airPathLength) {
  return setDouble(openstudio::AirflowNetwork_Distribution_Component_HeatExchangerFields::AirPathLength, airPathLength);
}

double AirflowNetworkDistributionComponentHeatExchanger_Impl::airPathHydraulicDiameter() const {
  const auto value = getDouble(openstudio::AirflowNetwork_Distribution_Component_HeatExchangerFields::AirPathHydraulicDiameter, true);
  OS_ASSERT(value);
  return *value;
}

bool AirflowNetworkDistributionComponentHeatExchanger_Impl::setAirPathHydraulicDiameter(double airPathHydraulicDiameter) {
  return setDouble(openstudio::AirflowNetwork_Distribution_Component_HeatExchangerFields::AirPathHydraulicDiameter, airPathHydraulicDiameter);
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
