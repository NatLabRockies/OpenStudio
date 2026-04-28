/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILHEATINGDXSINGLESPEED_IMPL_HPP
#define EPMODEL_COILHEATINGDXSINGLESPEED_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {
  class Node;
  class Schedule;
  class Curve;
  namespace detail {

    class EPMODEL_API CoilHeatingDXSingleSpeed_Impl : public StraightComponent_Impl
    {
     public:
      using StraightComponent_Impl::StraightComponent_Impl;
      virtual ~CoilHeatingDXSingleSpeed_Impl() override = default;
      bool addToNode(Node& node) override;

      unsigned inletPort() const override;
      unsigned outletPort() const override;
      std::vector<ModelObject> children() const override;

      Schedule availabilitySchedule() const;
      bool setAvailabilitySchedule(Schedule& schedule);

      Curve totalHeatingCapacityFunctionofTemperatureCurve() const;
      bool setTotalHeatingCapacityFunctionofTemperatureCurve(const Curve& curve);

      Curve totalHeatingCapacityFunctionofFlowFractionCurve() const;
      bool setTotalHeatingCapacityFunctionofFlowFractionCurve(const Curve& curve);

      Curve energyInputRatioFunctionofTemperatureCurve() const;
      bool setEnergyInputRatioFunctionofTemperatureCurve(const Curve& curve);

      Curve energyInputRatioFunctionofFlowFractionCurve() const;
      bool setEnergyInputRatioFunctionofFlowFractionCurve(const Curve& curve);

      Curve partLoadFractionCorrelationCurve() const;
      bool setPartLoadFractionCorrelationCurve(const Curve& curve);

      boost::optional<Curve> defrostEnergyInputRatioFunctionofTemperatureCurve() const;
      bool setDefrostEnergyInputRatioFunctionofTemperatureCurve(const Curve& curve);
      void resetDefrostEnergyInputRatioFunctionofTemperatureCurve();

      boost::optional<double> ratedTotalHeatingCapacity() const;
      bool isRatedTotalHeatingCapacityAutosized() const;
      bool setRatedTotalHeatingCapacity(double ratedTotalHeatingCapacity);
      void autosizeRatedTotalHeatingCapacity();

      double ratedCOP() const;
      bool setRatedCOP(double ratedCOP);

      boost::optional<double> ratedAirFlowRate() const;
      bool isRatedAirFlowRateAutosized() const;
      bool setRatedAirFlowRate(double ratedAirFlowRate);
      void autosizeRatedAirFlowRate();

      double ratedSupplyFanPowerPerVolumeFlowRate2017() const;
      bool setRatedSupplyFanPowerPerVolumeFlowRate2017(double ratedSupplyFanPowerPerVolumeFlowRate2017);

      double ratedSupplyFanPowerPerVolumeFlowRate2023() const;
      bool setRatedSupplyFanPowerPerVolumeFlowRate2023(double ratedSupplyFanPowerPerVolumeFlowRate2023);

      double minimumOutdoorDryBulbTemperatureforCompressorOperation() const;
      bool isMinimumOutdoorDryBulbTemperatureforCompressorOperationDefaulted() const;
      bool setMinimumOutdoorDryBulbTemperatureforCompressorOperation(double minimumOutdoorDryBulbTemperatureforCompressorOperation);
      void resetMinimumOutdoorDryBulbTemperatureforCompressorOperation();

      double maximumOutdoorDryBulbTemperatureforDefrostOperation() const;
      bool isMaximumOutdoorDryBulbTemperatureforDefrostOperationDefaulted() const;
      bool setMaximumOutdoorDryBulbTemperatureforDefrostOperation(double maximumOutdoorDryBulbTemperatureforDefrostOperation);
      void resetMaximumOutdoorDryBulbTemperatureforDefrostOperation();

      double crankcaseHeaterCapacity() const;
      bool isCrankcaseHeaterCapacityDefaulted() const;
      bool setCrankcaseHeaterCapacity(double crankcaseHeaterCapacity);
      void resetCrankcaseHeaterCapacity();

      boost::optional<Curve> crankcaseHeaterCapacityFunctionofTemperatureCurve() const;
      bool setCrankcaseHeaterCapacityFunctionofTemperatureCurve(const Curve& curve);
      void resetCrankcaseHeaterCapacityFunctionofTemperatureCurve();

      double maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation() const;
      bool isMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperationDefaulted() const;
      bool setMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation(double maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation);
      void resetMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation();

      std::vector<std::string> validDefrostStrategyValues() const;
      std::string defrostStrategy() const;
      bool isDefrostStrategyDefaulted() const;
      bool setDefrostStrategy(const std::string& defrostStrategy);
      void resetDefrostStrategy();

      std::vector<std::string> validDefrostControlValues() const;
      std::string defrostControl() const;
      bool isDefrostControlDefaulted() const;
      bool setDefrostControl(const std::string& defrostControl);
      void resetDefrostControl();

      double defrostTimePeriodFraction() const;
      bool isDefrostTimePeriodFractionDefaulted() const;
      bool setDefrostTimePeriodFraction(double defrostTimePeriodFraction);
      void resetDefrostTimePeriodFraction();

      boost::optional<double> resistiveDefrostHeaterCapacity() const;
      bool isResistiveDefrostHeaterCapacityDefaulted() const;
      bool isResistiveDefrostHeaterCapacityAutosized() const;
      bool setResistiveDefrostHeaterCapacity(double resistiveDefrostHeaterCapacity);
      void resetResistiveDefrostHeaterCapacity();
      void autosizeResistiveDefrostHeaterCapacity();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
