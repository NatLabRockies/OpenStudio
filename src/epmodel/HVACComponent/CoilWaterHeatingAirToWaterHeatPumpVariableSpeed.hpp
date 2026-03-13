/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILWATERHEATINGAIRTOWATERHEATPUMPVARIABLESPEED_HPP
#define EPMODEL_COILWATERHEATINGAIRTOWATERHEATPUMPVARIABLESPEED_HPP

#include "EPModelAPI.hpp"
#include "HVACComponent.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl;
  }

  class EPMODEL_API CoilWaterHeatingAirToWaterHeatPumpVariableSpeed : public HVACComponent
  {
   public:
    explicit CoilWaterHeatingAirToWaterHeatPumpVariableSpeed(const Model& model);

    virtual ~CoilWaterHeatingAirToWaterHeatPumpVariableSpeed() override = default;
    CoilWaterHeatingAirToWaterHeatPumpVariableSpeed(const CoilWaterHeatingAirToWaterHeatPumpVariableSpeed& other) = default;
    CoilWaterHeatingAirToWaterHeatPumpVariableSpeed(CoilWaterHeatingAirToWaterHeatPumpVariableSpeed&& other) = default;
    CoilWaterHeatingAirToWaterHeatPumpVariableSpeed& operator=(const CoilWaterHeatingAirToWaterHeatPumpVariableSpeed&) = default;
    CoilWaterHeatingAirToWaterHeatPumpVariableSpeed& operator=(CoilWaterHeatingAirToWaterHeatPumpVariableSpeed&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> evaporatorAirTemperatureTypeforCurveObjectsValues();

    // Schema Alignment Notes:
    // - API: Preserves openstudio::model scalar accessor names/signatures for model-counterpart compatibility.
    // - Field Mapping: Scalar APIs map directly to EnergyPlus Coil:WaterHeating:AirToWaterHeatPump:VariableSpeed fields.
    // - ForwardTranslator evidence: ForwardTranslateCoilWaterHeatingAirToWaterHeatPumpVariableSpeed.cpp writes these exact scalar fields.
    // - Field Mapping: Relationship-like fields (AvailabilityScheduleName, CrankcaseHeaterCapacityFunctionofTemperatureCurveName,
    //   PartLoadFractionCorrelationCurveName, SpeedDataList) are intentionally excluded in this scalar scaffold phase.
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
    bool setCondenserPumpHeatIncludedinRatedHeatingCapacityandRatedCOP(const std::string& condenserPumpHeatIncludedinRatedHeatingCapacityandRatedCOP);

    double fractionofCondenserPumpHeattoWater() const;
    bool setFractionofCondenserPumpHeattoWater(double fractionofCondenserPumpHeattoWater);

    double crankcaseHeaterCapacity() const;
    bool setCrankcaseHeaterCapacity(double crankcaseHeaterCapacity);

    double maximumAmbientTemperatureforCrankcaseHeaterOperation() const;
    bool setMaximumAmbientTemperatureforCrankcaseHeaterOperation(double maximumAmbientTemperatureforCrankcaseHeaterOperation);

    std::string evaporatorAirTemperatureTypeforCurveObjects() const;
    bool setEvaporatorAirTemperatureTypeforCurveObjects(const std::string& evaporatorAirTemperatureTypeforCurveObjects);

   protected:
    using ImplType = detail::CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit CoilWaterHeatingAirToWaterHeatPumpVariableSpeed(std::shared_ptr<detail::CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
