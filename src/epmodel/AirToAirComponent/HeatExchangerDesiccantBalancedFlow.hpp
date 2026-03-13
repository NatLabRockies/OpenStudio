/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HEATEXCHANGERDESICCANTBALANCEDFLOW_HPP
#define EPMODEL_HEATEXCHANGERDESICCANTBALANCEDFLOW_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class HeatExchangerDesiccantBalancedFlow_Impl;
}

class EPMODEL_API HeatExchangerDesiccantBalancedFlow : public ModelObject
{
 public:
  explicit HeatExchangerDesiccantBalancedFlow(const Model& model);

  virtual ~HeatExchangerDesiccantBalancedFlow() override = default;
  HeatExchangerDesiccantBalancedFlow(const HeatExchangerDesiccantBalancedFlow& other) = default;
  HeatExchangerDesiccantBalancedFlow(HeatExchangerDesiccantBalancedFlow&& other) = default;
  HeatExchangerDesiccantBalancedFlow& operator=(const HeatExchangerDesiccantBalancedFlow&) = default;
  HeatExchangerDesiccantBalancedFlow& operator=(HeatExchangerDesiccantBalancedFlow&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: Preserve openstudio::model scalar accessor names/signatures for counterpart compatibility.
  // - Field Mapping: economizerLockout maps to EnergyPlus HeatExchanger:Desiccant:BalancedFlow, Economizer Lockout.
  // - Field Mapping: Relationship fields (availability schedule, node names, performance object type/name) are intentionally excluded.
  // - TODO(parity): Add non-scalar relationship parity incrementally after scalar scaffold saturation.
  /** @name Economizer Lockout */
  //@{
  bool economizerLockout() const;

  bool setEconomizerLockout(bool economizerLockout);
  //@}

 protected:
  using ImplType = detail::HeatExchangerDesiccantBalancedFlow_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit HeatExchangerDesiccantBalancedFlow(std::shared_ptr<detail::HeatExchangerDesiccantBalancedFlow_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
