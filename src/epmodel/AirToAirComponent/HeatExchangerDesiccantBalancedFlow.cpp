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
    : AirToAirComponent(HeatExchangerDesiccantBalancedFlow::iddObjectType(), model) {}

  HeatExchangerDesiccantBalancedFlow::HeatExchangerDesiccantBalancedFlow(std::shared_ptr<detail::HeatExchangerDesiccantBalancedFlow_Impl> impl)
    : AirToAirComponent(std::move(impl)) {}

  IddObjectType HeatExchangerDesiccantBalancedFlow::iddObjectType() {
    return IddObjectType::HeatExchanger_Desiccant_BalancedFlow;
  }

  // Scalar accessors for Economizer Lockout
  //@{
  bool HeatExchangerDesiccantBalancedFlow::economizerLockout() const {
    return getImpl<detail::HeatExchangerDesiccantBalancedFlow_Impl>()->economizerLockout();
  }

  bool HeatExchangerDesiccantBalancedFlow::setEconomizerLockout(bool economizerLockout) {
    return getImpl<detail::HeatExchangerDesiccantBalancedFlow_Impl>()->setEconomizerLockout(economizerLockout);
  }
  //@}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    HeatExchangerDesiccantBalancedFlow_Impl::HeatExchangerDesiccantBalancedFlow_Impl(const IdfObject& idfObject, Model_Impl* model, bool keepHandle)
      : AirToAirComponent_Impl(idfObject, model, keepHandle) {}

    HeatExchangerDesiccantBalancedFlow_Impl::HeatExchangerDesiccantBalancedFlow_Impl(const openstudio::detail::WorkspaceObject_Impl& other,
                                                                                     Model_Impl* model, bool keepHandle)
      : AirToAirComponent_Impl(other, model, keepHandle) {}

    HeatExchangerDesiccantBalancedFlow_Impl::HeatExchangerDesiccantBalancedFlow_Impl(const HeatExchangerDesiccantBalancedFlow_Impl& other,
                                                                                     Model_Impl* model, bool keepHandle)
      : AirToAirComponent_Impl(other, model, keepHandle) {}

    // Scalar accessors for Economizer Lockout
    //@{
    bool HeatExchangerDesiccantBalancedFlow_Impl::economizerLockout() const {
      const auto value = getString(openstudio::HeatExchanger_Desiccant_BalancedFlowFields::EconomizerLockout, true);
      OS_ASSERT(value);
      return openstudio::istringEqual(*value, "Yes");
    }

    bool HeatExchangerDesiccantBalancedFlow_Impl::setEconomizerLockout(bool economizerLockout) {
      const bool result = setString(openstudio::HeatExchanger_Desiccant_BalancedFlowFields::EconomizerLockout, economizerLockout ? "Yes" : "No");
      OS_ASSERT(result);
      return result;
    }

    unsigned HeatExchangerDesiccantBalancedFlow_Impl::primaryAirInletPort() const {
      return openstudio::HeatExchanger_Desiccant_BalancedFlowFields::RegenerationAirInletNodeName;
    }

    unsigned HeatExchangerDesiccantBalancedFlow_Impl::primaryAirOutletPort() const {
      return openstudio::HeatExchanger_Desiccant_BalancedFlowFields::RegenerationAirOutletNodeName;
    }

    unsigned HeatExchangerDesiccantBalancedFlow_Impl::secondaryAirInletPort() const {
      return openstudio::HeatExchanger_Desiccant_BalancedFlowFields::ProcessAirInletNodeName;
    }

    unsigned HeatExchangerDesiccantBalancedFlow_Impl::secondaryAirOutletPort() const {
      return openstudio::HeatExchanger_Desiccant_BalancedFlowFields::ProcessAirOutletNodeName;
    }
    //@}

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
