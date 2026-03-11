/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACBASEBOARDCONVECTIVEWATER_IMPL_HPP
#define EPMODEL_ZONEHVACBASEBOARDCONVECTIVEWATER_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <string>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API ZoneHVACBaseboardConvectiveWater_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~ZoneHVACBaseboardConvectiveWater_Impl() override = default;

      std::string heatingDesignCapacityMethod() const;
      boost::optional<double> heatingDesignCapacity() const;
      bool isHeatingDesignCapacityAutosized() const;
      double heatingDesignCapacityPerFloorArea() const;
      double fractionofAutosizedHeatingDesignCapacity() const;

      boost::optional<double> uFactorTimesAreaValue() const;
      bool isUFactorTimesAreaValueDefaulted() const;
      bool isUFactorTimesAreaValueAutosized() const;

      boost::optional<double> maximumWaterFlowRate() const;
      bool isMaximumWaterFlowRateDefaulted() const;
      bool isMaximumWaterFlowRateAutosized() const;

      double convergenceTolerance() const;
      bool isConvergenceToleranceDefaulted() const;

      bool setHeatingDesignCapacityMethod(const std::string& heatingDesignCapacityMethod);
      bool setHeatingDesignCapacity(double heatingDesignCapacity);
      void autosizeHeatingDesignCapacity();
      bool setHeatingDesignCapacityPerFloorArea(double heatingDesignCapacityPerFloorArea);
      bool setFractionofAutosizedHeatingDesignCapacity(double fractionofAutosizedHeatingDesignCapacity);
      bool setUFactorTimesAreaValue(double uFactorTimesAreaValue);
      void resetUFactorTimesAreaValue();
      void autosizeUFactorTimesAreaValue();
      bool setMaximumWaterFlowRate(double maximumWaterFlowRate);
      void resetMaximumWaterFlowRate();
      void autosizeMaximumWaterFlowRate();
      bool setConvergenceTolerance(double convergenceTolerance);
      void resetConvergenceTolerance();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
