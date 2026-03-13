/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILHEATINGDXVARIABLEREFRIGERANTFLOW_IMPL_HPP
#define EPMODEL_COILHEATINGDXVARIABLEREFRIGERANTFLOW_IMPL_HPP

#include "HVACComponent_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API CoilHeatingDXVariableRefrigerantFlow_Impl : public HVACComponent_Impl
    {
     public:
      using HVACComponent_Impl::HVACComponent_Impl;
      virtual ~CoilHeatingDXVariableRefrigerantFlow_Impl() override = default;

      boost::optional<double> ratedTotalHeatingCapacity() const;
      bool setRatedTotalHeatingCapacity(double ratedTotalHeatingCapacity);
      bool isRatedTotalHeatingCapacityAutosized() const;
      void autosizeRatedTotalHeatingCapacity();

      boost::optional<double> ratedAirFlowRate() const;
      bool setRatedAirFlowRate(double ratedAirFlowRate);
      bool isRatedAirFlowRateAutosized() const;
      void autosizeRatedAirFlowRate();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
