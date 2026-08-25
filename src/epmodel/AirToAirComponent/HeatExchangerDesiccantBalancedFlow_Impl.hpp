/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HEATEXCHANGERDESICCANTBALANCEDFLOW_IMPL_HPP
#define EPMODEL_HEATEXCHANGERDESICCANTBALANCEDFLOW_IMPL_HPP

#include "AirToAirComponent/AirToAirComponent_Impl.hpp"

namespace openstudio {
namespace epmodel {

  class Schedule;
  class HeatExchangerDesiccantBalancedFlowPerformanceDataType1;

  namespace detail {

    class EPMODEL_API HeatExchangerDesiccantBalancedFlow_Impl : public AirToAirComponent_Impl
    {
     public:
      HeatExchangerDesiccantBalancedFlow_Impl(const IdfObject& idfObject, Model_Impl* model, bool keepHandle);
      HeatExchangerDesiccantBalancedFlow_Impl(const openstudio::detail::WorkspaceObject_Impl& other, Model_Impl* model, bool keepHandle);
      HeatExchangerDesiccantBalancedFlow_Impl(const HeatExchangerDesiccantBalancedFlow_Impl& other, Model_Impl* model, bool keepHandle);
      virtual ~HeatExchangerDesiccantBalancedFlow_Impl() override = default;

      std::vector<ModelObject> children() const override;
      std::vector<IdfObject> remove() override;

      Schedule availabilitySchedule() const;
      bool setAvailabilitySchedule(Schedule& schedule);

      HeatExchangerDesiccantBalancedFlowPerformanceDataType1 heatExchangerPerformance() const;
      bool setHeatExchangerPerformance(const HeatExchangerDesiccantBalancedFlowPerformanceDataType1& heatExchangerPerformance);

      /** @name Economizer Lockout */
      //@{
      bool economizerLockout() const;

      bool setEconomizerLockout(bool economizerLockout);
      //@}

      unsigned primaryAirInletPort() const override;
      unsigned primaryAirOutletPort() const override;
      unsigned secondaryAirInletPort() const override;
      unsigned secondaryAirOutletPort() const override;

     protected:
      void doCanonicalize(LoadContext& context) override;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
