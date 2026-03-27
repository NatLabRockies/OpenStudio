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
  // - Status: Partial Parity. The core economizer-lockout scalar is aligned, but the canonical performance-object and topology surface is still missing.
  // - Canonical Counterpart: openstudio::model::HeatExchangerDesiccantBalancedFlow.
  // - Implemented Parity: `economizerLockout` preserves the canonical scalar control behavior for the desiccant heat exchanger wrapper.
  // - Documented Delta: Epmodel does not yet expose the canonical availability schedule, performance-object linkage, or airflow-network equivalent-duct helpers present in `openstudio::model`.
  // - Field/Storage Mapping: The implemented scalar maps directly to `HeatExchanger:Desiccant:BalancedFlow` storage.
  // - Evidence: `src/model/HeatExchangerDesiccantBalancedFlow.hpp`, `src/model/HeatExchangerDesiccantBalancedFlow.cpp`, and `src/energyplus/ForwardTranslator/ForwardTranslateHeatExchangerDesiccantBalancedFlow.cpp` anchor the canonical API and translator behavior.
  // - Remaining Parity Work: Add the performance-object, schedule, and airflow-network relationship APIs when the epmodel relationship layer can represent them canonically.
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
