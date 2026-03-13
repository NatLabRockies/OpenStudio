/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILCOOLINGDXVARIABLEREFRIGERANTFLOW_IMPL_HPP
#define EPMODEL_COILCOOLINGDXVARIABLEREFRIGERANTFLOW_IMPL_HPP

#include "HVACComponent_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API CoilCoolingDXVariableRefrigerantFlow_Impl : public HVACComponent_Impl
    {
     public:
      using HVACComponent_Impl::HVACComponent_Impl;
      virtual ~CoilCoolingDXVariableRefrigerantFlow_Impl() override = default;

      boost::optional<double> ratedTotalCoolingCapacity() const;
      bool setRatedTotalCoolingCapacity(double ratedTotalCoolingCapacity);
      bool isRatedTotalCoolingCapacityAutosized() const;
      void autosizeRatedTotalCoolingCapacity();

      boost::optional<double> ratedSensibleHeatRatio() const;
      bool setRatedSensibleHeatRatio(double ratedSensibleHeatRatio);
      bool isRatedSensibleHeatRatioAutosized() const;
      void autosizeRatedSensibleHeatRatio();

      boost::optional<double> ratedAirFlowRate() const;
      bool setRatedAirFlowRate(double ratedAirFlowRate);
      bool isRatedAirFlowRateAutosized() const;
      void autosizeRatedAirFlowRate();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
