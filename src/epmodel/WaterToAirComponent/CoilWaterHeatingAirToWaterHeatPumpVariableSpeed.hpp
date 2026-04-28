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
  class Schedule;
  class Curve;
  class CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData;

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
    // - Status: Parity with documented deltas.
    // - Canonical Counterpart: openstudio::model::CoilWaterHeatingAirToWaterHeatPumpVariableSpeed.
    // - Implemented Parity: The canonical availability schedule, part-load curve, optional crankcase-heater curve,
    //   scalar rating surface, autosized-query stubs, and speed-data child APIs are exposed here. The required
    //   availability-schedule reference also follows the canonical getter-repair pattern: a missing target is repaired
    //   on read by wiring the model always-on discrete schedule. epmodel preserves the
    //   canonical speed-data children as transient ParentObject wrappers: detached transient wrappers hold their own
    //   OpenStudio-style fields until added to a parent coil, while attached transient wrappers read and write a specific
    //   EnergyPlus extensible speed row on the parent object.
    // - Documented Delta: epmodel promotes this wrapper to `WaterToAirComponent` so the real evaporator-air and
    //   condenser-water ports are explicit. This is an additive hierarchy change compared to canonical model.
    // - Documented Delta: Generic loop-placement APIs remain intentionally rejected because this coil is normally owned
    //   by a compound heat-pump water-heater parent.
    // - Documented Delta: `AirflowNetworkEquivalentDuct` parity is still deferred. High-level child traversal therefore
    //   returns the part-load curve, optional crankcase-heater curve, and speed-data children, but not the canonical
    //   AirflowNetwork companion. The autosized query methods are also API-preserving stubs for now: they return `none`
    //   until epmodel grows the SQL-backed autosized result lookup used by the canonical model layer.
    // - Field/Storage Mapping: Most scalar fields map directly to the corresponding EnergyPlus
    //   `Coil:WaterHeating:AirToWaterHeatPump:VariableSpeed` fields. `Number of Speeds` remains an EnergyPlus parent
    //   field but epmodel derives and maintains it from the current extensible-row count instead of exposing a direct
    //   accessor. When the coil has no speeds, epmodel clears the field rather than writing `0`, matching the current
    //   translator expectation that zero-speed coils stay untranslated. The canonical speed-data children are backed by the parent's real EnergyPlus extensible speed rows,
    //   not by separate persisted EnergyPlus objects.
    Schedule availabilitySchedule() const;
    bool setAvailabilitySchedule(Schedule& schedule);

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
    boost::optional<double> autocalculatedRatedEvaporatorAirFlowRate() const;

    boost::optional<double> ratedCondenserWaterFlowRate() const;
    bool setRatedCondenserWaterFlowRate(double ratedCondenserWaterFlowRate);
    bool isRatedCondenserWaterFlowRateAutocalculated() const;
    void autocalculateRatedCondenserWaterFlowRate();
    boost::optional<double> autocalculatedRatedCondenserWaterFlowRate() const;

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

    boost::optional<Curve> crankcaseHeaterCapacityFunctionofTemperatureCurve() const;
    bool setCrankcaseHeaterCapacityFunctionofTemperatureCurve(const Curve& curve);
    void resetCrankcaseHeaterCapacityFunctionofTemperatureCurve();

    double maximumAmbientTemperatureforCrankcaseHeaterOperation() const;
    bool setMaximumAmbientTemperatureforCrankcaseHeaterOperation(double maximumAmbientTemperatureforCrankcaseHeaterOperation);

    std::string evaporatorAirTemperatureTypeforCurveObjects() const;
    bool setEvaporatorAirTemperatureTypeforCurveObjects(const std::string& evaporatorAirTemperatureTypeforCurveObjects);

    Curve partLoadFractionCorrelationCurve() const;
    bool setPartLoadFractionCorrelationCurve(const Curve& curve);

    std::vector<CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData> speeds() const;
    bool addSpeed(const CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData& speed);
    void removeSpeed(const CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData& speed);
    void removeAllSpeeds();

    std::vector<ModelObject> children() const;

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
