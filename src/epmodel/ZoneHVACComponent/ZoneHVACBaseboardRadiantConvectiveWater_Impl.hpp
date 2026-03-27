/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACBASEBOARDRADIANTCONVECTIVEWATER_IMPL_HPP
#define EPMODEL_ZONEHVACBASEBOARDRADIANTCONVECTIVEWATER_IMPL_HPP

#include "ZoneHVACComponent/ZoneHVACComponent_Impl.hpp"

#include <boost/optional.hpp>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API ZoneHVACBaseboardRadiantConvectiveWater_Impl : public ZoneHVACComponent_Impl
    {
     public:
      using ZoneHVACComponent_Impl::ZoneHVACComponent_Impl;
      virtual ~ZoneHVACBaseboardRadiantConvectiveWater_Impl() override = default;

      boost::optional<double> ratedAverageWaterTemperature() const;
      bool isRatedAverageWaterTemperatureDefaulted() const;
      bool setRatedAverageWaterTemperature(double ratedAverageWaterTemperature);
      void resetRatedAverageWaterTemperature();

      boost::optional<double> ratedWaterMassFlowRate() const;
      bool isRatedWaterMassFlowRateDefaulted() const;
      bool setRatedWaterMassFlowRate(double ratedWaterMassFlowRate);
      void resetRatedWaterMassFlowRate();

      boost::optional<double> heatingDesignCapacity() const;
      bool isHeatingDesignCapacityAutosized() const;
      bool setHeatingDesignCapacity(double heatingDesignCapacity);
      void autosizeHeatingDesignCapacity();

      boost::optional<double> maximumWaterFlowRate() const;
      bool isMaximumWaterFlowRateAutosized() const;
      bool setMaximumWaterFlowRate(double maximumWaterFlowRate);
      void autosizeMaximumWaterFlowRate();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
