/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILWATERHEATINGAIRTOWATERHEATPUMP_IMPL_HPP
#define EPMODEL_COILWATERHEATINGAIRTOWATERHEATPUMP_IMPL_HPP

#include "WaterToAirComponent_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  class Schedule;
  class Curve;

  namespace detail {

    class EPMODEL_API CoilWaterHeatingAirToWaterHeatPump_Impl : public WaterToAirComponent_Impl
    {
     public:
      using WaterToAirComponent_Impl::WaterToAirComponent_Impl;
      virtual ~CoilWaterHeatingAirToWaterHeatPump_Impl() override = default;

      unsigned airInletPort() const override;
      unsigned airOutletPort() const override;
      unsigned waterInletPort() const override;
      unsigned waterOutletPort() const override;
      bool addToNode(Node& node) override;
      bool addToSplitter(Splitter& splitter) override;

      Schedule availabilitySchedule() const;
      bool setAvailabilitySchedule(Schedule& availabilitySchedule);

      double ratedHeatingCapacity() const;
      bool setRatedHeatingCapacity(double ratedHeatingCapacity);

      double ratedCOP() const;
      bool setRatedCOP(double ratedCOP);

      double ratedSensibleHeatRatio() const;
      bool setRatedSensibleHeatRatio(double ratedSensibleHeatRatio);

      double ratedEvaporatorInletAirDryBulbTemperature() const;
      bool setRatedEvaporatorInletAirDryBulbTemperature(double ratedEvaporatorInletAirDryBulbTemperature);

      double ratedEvaporatorInletAirWetBulbTemperature() const;
      bool setRatedEvaporatorInletAirWetBulbTemperature(double ratedEvaporatorInletAirWetBulbTemperature);

      double ratedCondenserInletWaterTemperature() const;
      bool setRatedCondenserInletWaterTemperature(double ratedCondenserInletWaterTemperature);

      boost::optional<double> ratedEvaporatorAirFlowRate() const;
      bool setRatedEvaporatorAirFlowRate(double ratedEvaporatorAirFlowRate);
      bool isRatedEvaporatorAirFlowRateAutosized() const;
      void autosizeRatedEvaporatorAirFlowRate();

      boost::optional<double> ratedCondenserWaterFlowRate() const;
      bool setRatedCondenserWaterFlowRate(double ratedCondenserWaterFlowRate);
      bool isRatedCondenserWaterFlowRateAutosized() const;
      void autosizeRatedCondenserWaterFlowRate();

      bool evaporatorFanPowerIncludedinRatedCOP() const;
      bool setEvaporatorFanPowerIncludedinRatedCOP(bool evaporatorFanPowerIncludedinRatedCOP);

      bool condenserPumpPowerIncludedinRatedCOP() const;
      bool setCondenserPumpPowerIncludedinRatedCOP(bool condenserPumpPowerIncludedinRatedCOP);

      bool condenserPumpHeatIncludedinRatedHeatingCapacityandRatedCOP() const;
      bool setCondenserPumpHeatIncludedinRatedHeatingCapacityandRatedCOP(bool condenserPumpHeatIncludedinRatedHeatingCapacityandRatedCOP);

      double condenserWaterPumpPower() const;
      bool setCondenserWaterPumpPower(double condenserWaterPumpPower);

      double fractionofCondenserPumpHeattoWater() const;
      bool setFractionofCondenserPumpHeattoWater(double fractionofCondenserPumpHeattoWater);

      double crankcaseHeaterCapacity() const;
      bool setCrankcaseHeaterCapacity(double crankcaseHeaterCapacity);

      boost::optional<Curve> crankcaseHeaterCapacityFunctionofTemperatureCurve() const;
      bool setCrankcaseHeaterCapacityFunctionofTemperatureCurve(const Curve& crankcaseHeaterCapacityFunctionofTemperatureCurve);
      void resetCrankcaseHeaterCapacityFunctionofTemperatureCurve();

      double maximumAmbientTemperatureforCrankcaseHeaterOperation() const;
      bool setMaximumAmbientTemperatureforCrankcaseHeaterOperation(double maximumAmbientTemperatureforCrankcaseHeaterOperation);

      std::string evaporatorAirTemperatureTypeforCurveObjects() const;
      bool setEvaporatorAirTemperatureTypeforCurveObjects(const std::string& evaporatorAirTemperatureTypeforCurveObjects);

      Curve heatingCapacityFunctionofTemperatureCurve() const;
      bool setHeatingCapacityFunctionofTemperatureCurve(const Curve& heatingCapacityFunctionofTemperatureCurve);

      Curve heatingCapacityFunctionofAirFlowFractionCurve() const;
      bool setHeatingCapacityFunctionofAirFlowFractionCurve(const Curve& heatingCapacityFunctionofAirFlowFractionCurve);

      Curve heatingCapacityFunctionofWaterFlowFractionCurve() const;
      bool setHeatingCapacityFunctionofWaterFlowFractionCurve(const Curve& heatingCapacityFunctionofWaterFlowFractionCurve);

      Curve heatingCOPFunctionofTemperatureCurve() const;
      bool setHeatingCOPFunctionofTemperatureCurve(const Curve& heatingCOPFunctionofTemperatureCurve);

      Curve heatingCOPFunctionofAirFlowFractionCurve() const;
      bool setHeatingCOPFunctionofAirFlowFractionCurve(const Curve& heatingCOPFunctionofAirFlowFractionCurve);

      Curve heatingCOPFunctionofWaterFlowFractionCurve() const;
      bool setHeatingCOPFunctionofWaterFlowFractionCurve(const Curve& heatingCOPFunctionofWaterFlowFractionCurve);

      Curve partLoadFractionCorrelationCurve() const;
      bool setPartLoadFractionCorrelationCurve(const Curve& partLoadFractionCorrelationCurve);

      boost::optional<double> autosizedRatedEvaporatorAirFlowRate() const;
      boost::optional<double> autosizedRatedCondenserWaterFlowRate() const;

      std::vector<std::string> evaporatorAirTemperatureTypeforCurveObjectsValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
