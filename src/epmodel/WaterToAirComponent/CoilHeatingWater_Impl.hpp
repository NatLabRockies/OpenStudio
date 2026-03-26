/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILHEATINGWATER_IMPL_HPP
#define EPMODEL_COILHEATINGWATER_IMPL_HPP

#include "WaterToAirComponent/WaterToAirComponent_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API CoilHeatingWater_Impl : public WaterToAirComponent_Impl
    {
     public:
      using WaterToAirComponent_Impl::WaterToAirComponent_Impl;
      virtual ~CoilHeatingWater_Impl() override = default;

      unsigned airInletPort() const override;
      unsigned airOutletPort() const override;
      unsigned waterInletPort() const override;
      unsigned waterOutletPort() const override;

      boost::optional<double> uFactorTimesAreaValue() const;
      bool setUFactorTimesAreaValue(double value);
      bool isUFactorTimesAreaValueAutosized() const;
      void autosizeUFactorTimesAreaValue();

      boost::optional<double> maximumWaterFlowRate() const;
      bool setMaximumWaterFlowRate(double value);
      bool isMaximumWaterFlowRateAutosized() const;
      void autosizeMaximumWaterFlowRate();

      std::string performanceInputMethod() const;
      bool setPerformanceInputMethod(const std::string& value);
      std::vector<std::string> performanceInputMethodValues() const;

      boost::optional<double> ratedCapacity() const;
      bool setRatedCapacity(double value);
      bool isRatedCapacityAutosized() const;
      void autosizeRatedCapacity();

      double ratedInletWaterTemperature() const;
      bool setRatedInletWaterTemperature(double value);

      double ratedInletAirTemperature() const;
      bool setRatedInletAirTemperature(double value);

      double ratedOutletWaterTemperature() const;
      bool setRatedOutletWaterTemperature(double value);

      double ratedOutletAirTemperature() const;
      bool setRatedOutletAirTemperature(double value);

      double ratedRatioForAirAndWaterConvection() const;
      bool setRatedRatioForAirAndWaterConvection(double value);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
