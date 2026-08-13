/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HEATEXCHANGERDESICCANTBALANCEDFLOW_HPP
#define EPMODEL_HEATEXCHANGERDESICCANTBALANCEDFLOW_HPP

#include "EPModelAPI.hpp"
#include "AirToAirComponent/AirToAirComponent.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;
  class Schedule;
  class HeatExchangerDesiccantBalancedFlowPerformanceDataType1;

  namespace detail {
    class HeatExchangerDesiccantBalancedFlow_Impl;
  }

  class EPMODEL_API HeatExchangerDesiccantBalancedFlow : public AirToAirComponent
  {
   public:
    explicit HeatExchangerDesiccantBalancedFlow(const Model& model);
    explicit HeatExchangerDesiccantBalancedFlow(const Model& model,
                                                const HeatExchangerDesiccantBalancedFlowPerformanceDataType1& heatExchangerPerformance);

    virtual ~HeatExchangerDesiccantBalancedFlow() override = default;
    HeatExchangerDesiccantBalancedFlow(const HeatExchangerDesiccantBalancedFlow& other) = default;
    HeatExchangerDesiccantBalancedFlow(HeatExchangerDesiccantBalancedFlow&& other) = default;
    HeatExchangerDesiccantBalancedFlow& operator=(const HeatExchangerDesiccantBalancedFlow&) = default;
    HeatExchangerDesiccantBalancedFlow& operator=(HeatExchangerDesiccantBalancedFlow&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - Status: Near Parity. The selected schedule, performance-object, economizer-lockout, and two-stream topology behavior is aligned.
    // - Canonical Counterpart: openstudio::model::HeatExchangerDesiccantBalancedFlow.
    // - Implemented Parity: Construction supplies the required availability schedule and performance data; relationship replacement, validation,
    //   shared-child removal, `economizerLockout`, and coordinated outdoor/relief placement follow the selected canonical behavior.
    // - Documented Delta: Epmodel does not yet expose the airflow-network equivalent-duct helpers present in `openstudio::model`.
    // - Field/Storage Mapping: The schedule, performance type/name pair, and economizer lockout map directly to
    //   `HeatExchanger:Desiccant:BalancedFlow` storage; the two air streams use its four node fields.
    // - Evidence: `src/model/HeatExchangerDesiccantBalancedFlow.hpp`, `src/model/HeatExchangerDesiccantBalancedFlow.cpp`, and `src/energyplus/ForwardTranslator/ForwardTranslateHeatExchangerDesiccantBalancedFlow.cpp` anchor the canonical API and translator behavior.
    // - Remaining Parity Work: Add airflow-network equivalent-duct helpers and numerical performance comparison when a workflow requires them.

    Schedule availabilitySchedule() const;
    bool setAvailabilitySchedule(Schedule& schedule);

    HeatExchangerDesiccantBalancedFlowPerformanceDataType1 heatExchangerPerformance() const;
    bool setHeatExchangerPerformance(const HeatExchangerDesiccantBalancedFlowPerformanceDataType1& heatExchangerPerformance);

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
