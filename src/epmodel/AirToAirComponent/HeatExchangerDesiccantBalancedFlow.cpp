/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "AirToAirComponent/HeatExchangerDesiccantBalancedFlow.hpp"
#include "AirToAirComponent/HeatExchangerDesiccantBalancedFlow_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/HeatExchanger_Desiccant_BalancedFlow_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

HeatExchangerDesiccantBalancedFlow::HeatExchangerDesiccantBalancedFlow(const Model& model)
  : ModelObject(HeatExchangerDesiccantBalancedFlow::iddObjectType(), model) {}

HeatExchangerDesiccantBalancedFlow::HeatExchangerDesiccantBalancedFlow(
  std::shared_ptr<detail::HeatExchangerDesiccantBalancedFlow_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType HeatExchangerDesiccantBalancedFlow::iddObjectType() {
  return IddObjectType::HeatExchanger_Desiccant_BalancedFlow;
}

bool HeatExchangerDesiccantBalancedFlow::economizerLockout() const {
  return getImpl<detail::HeatExchangerDesiccantBalancedFlow_Impl>()->economizerLockout();
}

bool HeatExchangerDesiccantBalancedFlow::setEconomizerLockout(bool economizerLockout) {
  return getImpl<detail::HeatExchangerDesiccantBalancedFlow_Impl>()->setEconomizerLockout(economizerLockout);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

bool HeatExchangerDesiccantBalancedFlow_Impl::economizerLockout() const {
  const auto value = getString(openstudio::HeatExchanger_Desiccant_BalancedFlowFields::EconomizerLockout, true);
  OS_ASSERT(value);
  return openstudio::istringEqual(*value, "Yes");
}

bool HeatExchangerDesiccantBalancedFlow_Impl::setEconomizerLockout(bool economizerLockout) {
  const bool result = setString(openstudio::HeatExchanger_Desiccant_BalancedFlowFields::EconomizerLockout,
                                economizerLockout ? "Yes" : "No");
  OS_ASSERT(result);
  return result;
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
