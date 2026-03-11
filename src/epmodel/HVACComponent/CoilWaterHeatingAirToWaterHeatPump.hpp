/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILWATERHEATINGAIRTOWATERHEATPUMP_HPP
#define EPMODEL_COILWATERHEATINGAIRTOWATERHEATPUMP_HPP

#include "EPModelAPI.hpp"
#include "HVACComponent.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class CoilWaterHeatingAirToWaterHeatPump_Impl;
}

class EPMODEL_API CoilWaterHeatingAirToWaterHeatPump : public HVACComponent
{
 public:
  explicit CoilWaterHeatingAirToWaterHeatPump(const Model& model);

  virtual ~CoilWaterHeatingAirToWaterHeatPump() override = default;
  CoilWaterHeatingAirToWaterHeatPump(const CoilWaterHeatingAirToWaterHeatPump& other) = default;
  CoilWaterHeatingAirToWaterHeatPump(CoilWaterHeatingAirToWaterHeatPump&& other) = default;
  CoilWaterHeatingAirToWaterHeatPump& operator=(const CoilWaterHeatingAirToWaterHeatPump&) = default;
  CoilWaterHeatingAirToWaterHeatPump& operator=(CoilWaterHeatingAirToWaterHeatPump&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> evaporatorAirTemperatureTypeforCurveObjectsValues();

  // Schema Alignment Notes:
  // - API: Preserves openstudio::model scalar accessor names/signatures for model-counterpart compatibility.
  // - Field Mapping: Scalar APIs map directly to EnergyPlus Coil:WaterHeating:AirToWaterHeatPump:Pumped scalar fields.
  // - ForwardTranslator evidence: ForwardTranslateCoilWaterHeatingAirToWaterHeatPump.cpp writes these exact scalar fields.
  // - Field Mapping: Relationship-like fields (AvailabilityScheduleName, curve-name references, and node links) are intentionally excluded.
  // - TODO(parity): Add relationship APIs incrementally after scalar scaffold saturation.
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

 protected:
  using ImplType = detail::CoilWaterHeatingAirToWaterHeatPump_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit CoilWaterHeatingAirToWaterHeatPump(std::shared_ptr<detail::CoilWaterHeatingAirToWaterHeatPump_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
