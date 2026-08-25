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

  /** \brief Represents the EnergyPlus HeatExchanger:Desiccant:BalancedFlow object.
   *
   * \par EnergyPlus object
   * \epobject{group-heat-recovery.html#heatexchangerdesiccantbalancedflow,HeatExchanger:Desiccant:BalancedFlow}
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::HeatExchangerDesiccantBalancedFlow</code>. <b>Not yet available:</b> the Model airflow-network equivalent-duct helpers.
   *
   * \par Known limitations
   * The four air-stream nodes and performance object relationship must remain consistent for outdoor-air or relief placement.
   */
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
