/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILWATERHEATINGAIRTOWATERHEATPUMPVARIABLESPEED_IMPL_HPP
#define EPMODEL_COILWATERHEATINGAIRTOWATERHEATPUMPVARIABLESPEED_IMPL_HPP

#include "HVACComponent_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl : public HVACComponent_Impl
{
 public:
  using HVACComponent_Impl::HVACComponent_Impl;
  virtual ~CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl() override = default;

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
  bool isRatedEvaporatorAirFlowRateAutocalculated() const;
  bool setRatedEvaporatorAirFlowRate(double ratedEvaporatorAirFlowRate);
  void autocalculateRatedEvaporatorAirFlowRate();

  boost::optional<double> ratedCondenserWaterFlowRate() const;
  bool isRatedCondenserWaterFlowRateAutocalculated() const;
  bool setRatedCondenserWaterFlowRate(double ratedCondenserWaterFlowRate);
  void autocalculateRatedCondenserWaterFlowRate();

  std::string evaporatorFanPowerIncludedinRatedCOP() const;
  bool setEvaporatorFanPowerIncludedinRatedCOP(const std::string& evaporatorFanPowerIncludedinRatedCOP);

  std::string condenserPumpPowerIncludedinRatedCOP() const;
  bool setCondenserPumpPowerIncludedinRatedCOP(const std::string& condenserPumpPowerIncludedinRatedCOP);

  std::string condenserPumpHeatIncludedinRatedHeatingCapacityandRatedCOP() const;
  bool setCondenserPumpHeatIncludedinRatedHeatingCapacityandRatedCOP(const std::string& condenserPumpHeatIncludedinRatedHeatingCapacityandRatedCOP);

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
