/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILWATERHEATINGAIRTOWATERHEATPUMPVARIABLESPEED_IMPL_HPP
#define EPMODEL_COILWATERHEATINGAIRTOWATERHEATPUMPVARIABLESPEED_IMPL_HPP

#include "WaterToAirComponent_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl : public WaterToAirComponent_Impl
    {
     public:
      using WaterToAirComponent_Impl::WaterToAirComponent_Impl;
      virtual ~CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl() override = default;

      unsigned airInletPort() const override;
      unsigned airOutletPort() const override;
      unsigned waterInletPort() const override;
      unsigned waterOutletPort() const override;
      bool addToNode(Node& node) override;
      bool addToSplitter(Splitter& splitter) override;

      int nominalSpeedLevel() const;
      bool setNominalSpeedLevel(int nominalSpeedLevel);

      double ratedWaterHeatingCapacity() const;
      bool setRatedWaterHeatingCapacity(double ratedWaterHeatingCapacity);

      double ratedEvaporatorInletAirDryBulbTemperature() const;
      bool setRatedEvaporatorInletAirDryBulbTemperature(double ratedEvaporatorInletAirDryBulbTemperature);

      double ratedEvaporatorInletAirWetBulbTemperature() const;
      bool setRatedEvaporatorInletAirWetBulbTemperature(double ratedEvaporatorInletWetDryBulbTemperature);

      double ratedCondenserInletWaterTemperature() const;
      bool setRatedCondenserInletWaterTemperature(double ratedCondenserInletWaterTemperature);

      boost::optional<double> ratedEvaporatorAirFlowRate() const;
      bool setRatedEvaporatorAirFlowRate(double ratedEvaporatorAirFlowRate);
      bool isRatedEvaporatorAirFlowRateAutocalculated() const;
      void autocalculateRatedEvaporatorAirFlowRate();

      boost::optional<double> ratedCondenserWaterFlowRate() const;
      bool setRatedCondenserWaterFlowRate(double ratedCondenserWaterFlowRate);
      bool isRatedCondenserWaterFlowRateAutocalculated() const;
      void autocalculateRatedCondenserWaterFlowRate();

      std::string evaporatorFanPowerIncludedinRatedCOP() const;
      bool setEvaporatorFanPowerIncludedinRatedCOP(const std::string& evaporatorFanPowerIncludedinRatedCOP);

      std::string condenserPumpPowerIncludedinRatedCOP() const;
      bool setCondenserPumpPowerIncludedinRatedCOP(const std::string& condenserPumpPowerIncludedinRatedCOP);

      std::string condenserPumpHeatIncludedinRatedHeatingCapacityandRatedCOP() const;
      bool
        setCondenserPumpHeatIncludedinRatedHeatingCapacityandRatedCOP(const std::string& condenserPumpHeatIncludedinRatedHeatingCapacityandRatedCOP);

      double fractionofCondenserPumpHeattoWater() const;
      bool setFractionofCondenserPumpHeattoWater(double fractionofCondenserPumpHeattoWater);

      double crankcaseHeaterCapacity() const;
      bool setCrankcaseHeaterCapacity(double crankcaseHeaterCapacity);

      double maximumAmbientTemperatureforCrankcaseHeaterOperation() const;
      bool setMaximumAmbientTemperatureforCrankcaseHeaterOperation(double maximumAmbientTemperatureforCrankcaseHeaterOperation);

      std::string evaporatorAirTemperatureTypeforCurveObjects() const;
      bool setEvaporatorAirTemperatureTypeforCurveObjects(const std::string& evaporatorAirTemperatureTypeforCurveObjects);

      std::vector<std::string> evaporatorAirTemperatureTypeforCurveObjectsValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
