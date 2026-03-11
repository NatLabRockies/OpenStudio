/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILWATERHEATINGAIRTOWATERHEATPUMPWRAPPED_IMPL_HPP
#define EPMODEL_COILWATERHEATINGAIRTOWATERHEATPUMPWRAPPED_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl() override = default;

  double ratedHeatingCapacity() const;
  bool setRatedHeatingCapacity(double ratedHeatingCapacity);

  double ratedCOP() const;
  bool isRatedCOPDefaulted() const;
  bool setRatedCOP(double ratedCOP);
  void resetRatedCOP();

  double ratedSensibleHeatRatio() const;
  bool isRatedSensibleHeatRatioDefaulted() const;
  bool setRatedSensibleHeatRatio(double ratedSensibleHeatRatio);
  void resetRatedSensibleHeatRatio();

  double ratedEvaporatorInletAirDryBulbTemperature() const;
  bool isRatedEvaporatorInletAirDryBulbTemperatureDefaulted() const;
  bool setRatedEvaporatorInletAirDryBulbTemperature(double ratedEvaporatorInletAirDryBulbTemperature);
  void resetRatedEvaporatorInletAirDryBulbTemperature();

  double ratedEvaporatorInletAirWetBulbTemperature() const;
  bool isRatedEvaporatorInletAirWetBulbTemperatureDefaulted() const;
  bool setRatedEvaporatorInletAirWetBulbTemperature(double ratedEvaporatorInletAirWetBulbTemperature);
  void resetRatedEvaporatorInletAirWetBulbTemperature();

  double ratedCondenserWaterTemperature() const;
  bool isRatedCondenserWaterTemperatureDefaulted() const;
  bool setRatedCondenserWaterTemperature(double ratedCondenserWaterTemperature);
  void resetRatedCondenserWaterTemperature();

  boost::optional<double> ratedEvaporatorAirFlowRate() const;
  bool setRatedEvaporatorAirFlowRate(double ratedEvaporatorAirFlowRate);
  bool isRatedEvaporatorAirFlowRateAutocalculated() const;
  void autocalculateRatedEvaporatorAirFlowRate();
  void resetRatedEvaporatorAirFlowRate();

  bool evaporatorFanPowerIncludedinRatedCOP() const;
  bool isEvaporatorFanPowerIncludedinRatedCOPDefaulted() const;
  bool setEvaporatorFanPowerIncludedinRatedCOP(bool evaporatorFanPowerIncludedinRatedCOP);
  void resetEvaporatorFanPowerIncludedinRatedCOP();

  double crankcaseHeaterCapacity() const;
  bool isCrankcaseHeaterCapacityDefaulted() const;
  bool setCrankcaseHeaterCapacity(double crankcaseHeaterCapacity);
  void resetCrankcaseHeaterCapacity();

  double maximumAmbientTemperatureforCrankcaseHeaterOperation() const;
  bool isMaximumAmbientTemperatureforCrankcaseHeaterOperationDefaulted() const;
  bool setMaximumAmbientTemperatureforCrankcaseHeaterOperation(double maximumAmbientTemperatureforCrankcaseHeaterOperation);
  void resetMaximumAmbientTemperatureforCrankcaseHeaterOperation();

  std::string evaporatorAirTemperatureTypeforCurveObjects() const;
  bool isEvaporatorAirTemperatureTypeforCurveObjectsDefaulted() const;
  bool setEvaporatorAirTemperatureTypeforCurveObjects(const std::string& evaporatorAirTemperatureTypeforCurveObjects);
  void resetEvaporatorAirTemperatureTypeforCurveObjects();

  std::vector<std::string> evaporatorAirTemperatureTypeforCurveObjectsValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
