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

  class Node;
  class Schedule;
  class AirflowNetworkDistributionComponentCoil;

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
      bool addToNode(Node& node) override;
      std::vector<IdfObject> remove() override;
      bool removeFromPlantLoop() override;
      std::vector<ModelObject> children() const override;

      Schedule availabilitySchedule() const;
      bool setAvailabilitySchedule(Schedule& schedule);

      boost::optional<double> uFactorTimesAreaValue() const;
      bool setUFactorTimesAreaValue(double value);
      bool isUFactorTimesAreaValueAutosized() const;
      void autosizeUFactorTimesAreaValue();
      boost::optional<double> autosizedUFactorTimesAreaValue() const;

      boost::optional<double> maximumWaterFlowRate() const;
      bool setMaximumWaterFlowRate(double value);
      bool isMaximumWaterFlowRateAutosized() const;
      void autosizeMaximumWaterFlowRate();
      boost::optional<double> autosizedMaximumWaterFlowRate() const;

      std::string performanceInputMethod() const;
      bool setPerformanceInputMethod(const std::string& value);
      std::vector<std::string> performanceInputMethodValues() const;

      boost::optional<double> ratedCapacity() const;
      bool setRatedCapacity(double value);
      bool isRatedCapacityAutosized() const;
      void autosizeRatedCapacity();
      boost::optional<double> autosizedRatedCapacity() const;

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

      AirflowNetworkDistributionComponentCoil getAirflowNetworkEquivalentDuct(double length, double diameter);
      boost::optional<AirflowNetworkDistributionComponentCoil> airflowNetworkEquivalentDuct() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
