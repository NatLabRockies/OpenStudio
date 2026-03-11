/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILWATERHEATINGAIRTOWATERHEATPUMPWRAPPED_HPP
#define EPMODEL_COILWATERHEATINGAIRTOWATERHEATPUMPWRAPPED_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl;
}

class EPMODEL_API CoilWaterHeatingAirToWaterHeatPumpWrapped : public ModelObject
{
 public:
  explicit CoilWaterHeatingAirToWaterHeatPumpWrapped(const Model& model);

  virtual ~CoilWaterHeatingAirToWaterHeatPumpWrapped() override = default;
  CoilWaterHeatingAirToWaterHeatPumpWrapped(const CoilWaterHeatingAirToWaterHeatPumpWrapped& other) = default;
  CoilWaterHeatingAirToWaterHeatPumpWrapped(CoilWaterHeatingAirToWaterHeatPumpWrapped&& other) = default;
  CoilWaterHeatingAirToWaterHeatPumpWrapped& operator=(const CoilWaterHeatingAirToWaterHeatPumpWrapped&) = default;
  CoilWaterHeatingAirToWaterHeatPumpWrapped& operator=(CoilWaterHeatingAirToWaterHeatPumpWrapped&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> evaporatorAirTemperatureTypeforCurveObjectsValues();

  // Schema Alignment Notes:
  // - API: Preserves openstudio::model scalar accessor names/signatures for model-counterpart compatibility.
  // - Field Mapping: Scalar APIs map directly to EnergyPlus Coil:WaterHeating:AirToWaterHeatPump:Wrapped scalar fields.
  // - ForwardTranslator evidence: ForwardTranslateCoilWaterHeatingAirToWaterHeatPumpWrapped.cpp writes these exact scalar fields.
  // - Field Mapping: Relationship-like fields (AvailabilityScheduleName, node names, and curve-name references) are intentionally excluded.
  // - TODO(parity): Add relationship APIs incrementally after scalar scaffold saturation.
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

 protected:
  using ImplType = detail::CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit CoilWaterHeatingAirToWaterHeatPumpWrapped(std::shared_ptr<detail::CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
