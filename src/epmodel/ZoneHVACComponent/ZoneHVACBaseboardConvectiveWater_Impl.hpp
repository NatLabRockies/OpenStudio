/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACBASEBOARDCONVECTIVEWATER_IMPL_HPP
#define EPMODEL_ZONEHVACBASEBOARDCONVECTIVEWATER_IMPL_HPP

#include "ZoneHVACComponent/ZoneHVACComponent_Impl.hpp"

#include <string>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API ZoneHVACBaseboardConvectiveWater_Impl : public ZoneHVACComponent_Impl
    {
     public:
      using ZoneHVACComponent_Impl::ZoneHVACComponent_Impl;
      virtual ~ZoneHVACBaseboardConvectiveWater_Impl() override = default;

      std::string heatingDesignCapacityMethod() const;
      bool setHeatingDesignCapacityMethod(const std::string& heatingDesignCapacityMethod);

      boost::optional<double> heatingDesignCapacity() const;
      bool setHeatingDesignCapacity(double heatingDesignCapacity);
      void autosizeHeatingDesignCapacity();
      bool isHeatingDesignCapacityAutosized() const;

      double heatingDesignCapacityPerFloorArea() const;
      bool setHeatingDesignCapacityPerFloorArea(double heatingDesignCapacityPerFloorArea);

      double fractionofAutosizedHeatingDesignCapacity() const;
      bool setFractionofAutosizedHeatingDesignCapacity(double fractionofAutosizedHeatingDesignCapacity);

      boost::optional<double> uFactorTimesAreaValue() const;
      bool setUFactorTimesAreaValue(double uFactorTimesAreaValue);
      void resetUFactorTimesAreaValue();
      void autosizeUFactorTimesAreaValue();
      bool isUFactorTimesAreaValueDefaulted() const;
      bool isUFactorTimesAreaValueAutosized() const;

      boost::optional<double> maximumWaterFlowRate() const;
      bool setMaximumWaterFlowRate(double maximumWaterFlowRate);
      void resetMaximumWaterFlowRate();
      void autosizeMaximumWaterFlowRate();
      bool isMaximumWaterFlowRateDefaulted() const;
      bool isMaximumWaterFlowRateAutosized() const;

      double convergenceTolerance() const;
      bool setConvergenceTolerance(double convergenceTolerance);
      void resetConvergenceTolerance();
      bool isConvergenceToleranceDefaulted() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
