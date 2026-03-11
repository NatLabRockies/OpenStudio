/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILWATERHEATINGAIRTOWATERHEATPUMP_IMPL_HPP
#define EPMODEL_COILWATERHEATINGAIRTOWATERHEATPUMP_IMPL_HPP

#include "HVACComponent_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API CoilWaterHeatingAirToWaterHeatPump_Impl : public HVACComponent_Impl
{
 public:
  using HVACComponent_Impl::HVACComponent_Impl;
  virtual ~CoilWaterHeatingAirToWaterHeatPump_Impl() override = default;

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
  bool isRatedEvaporatorAirFlowRateAutosized() const;
  bool setRatedEvaporatorAirFlowRate(double ratedEvaporatorAirFlowRate);
  void autosizeRatedEvaporatorAirFlowRate();

  boost::optional<double> ratedCondenserWaterFlowRate() const;
  bool isRatedCondenserWaterFlowRateAutosized() const;
  bool setRatedCondenserWaterFlowRate(double ratedCondenserWaterFlowRate);
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
