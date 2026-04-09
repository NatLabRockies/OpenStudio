/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILWATERHEATINGAIRTOWATERHEATPUMPVARIABLESPEED_HPP
#define EPMODEL_COILWATERHEATINGAIRTOWATERHEATPUMPVARIABLESPEED_HPP

#include "EPModelAPI.hpp"
#include "WaterToAirComponent.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl;
  }

  class EPMODEL_API CoilWaterHeatingAirToWaterHeatPumpVariableSpeed : public WaterToAirComponent
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
    // - Status: Scalar Parity. The scalar rating and control surface is aligned, while availability-schedule, curve, and speed-data APIs are still omitted.
    // - Canonical Counterpart: openstudio::model::CoilWaterHeatingAirToWaterHeatPumpVariableSpeed.
    // - Implemented Parity: `evaporatorAirTemperatureTypeforCurveObjectsValues`, the rating setters/getters, pump/fan flags, and flow autocalculate helpers preserve the canonical scalar contract.
    // - Documented Delta: epmodel promotes this wrapper to `WaterToAirComponent` so the real evaporator-air and condenser-water ports are explicit. This is an additive hierarchy change compared to canonical model.
    // - Documented Delta: Despite the base-class promotion, generic loop-placement APIs remain intentionally rejected because this coil is normally owned by a compound heat-pump water-heater parent.
    // - Field/Storage Mapping: The epmodel wrapper maps the preserved scalar fields directly to EnergyPlus `Coil:WaterHeating:AirToWaterHeatPump:VariableSpeed` storage, including the real air and water node fields.
    // - Evidence: `src/model/CoilWaterHeatingAirToWaterHeatPumpVariableSpeed.hpp`, `src/model/CoilWaterHeatingAirToWaterHeatPumpVariableSpeed.cpp`, `src/energyplus/ForwardTranslator/ForwardTranslateCoilWaterHeatingAirToWaterHeatPumpVariableSpeed.cpp`, `src/model/test/CoilSystemIntegratedHeatPumpAirSource_GTest.cpp`, and `src/epmodel/test/CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_GTest.cpp`.
    // - Remaining Parity Work: Add the omitted schedule, curve, and speed-data APIs after the relationship layer is available.
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
