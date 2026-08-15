/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILWATERHEATINGAIRTOWATERHEATPUMPWRAPPED_HPP
#define EPMODEL_COILWATERHEATINGAIRTOWATERHEATPUMPWRAPPED_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class Curve;
  class Schedule;

  namespace detail {
    class CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl;
  }

  class EPMODEL_API CoilWaterHeatingAirToWaterHeatPumpWrapped : public StraightComponent
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
    // - Status: Partial Parity. The scalar rating/control surface, required availability schedule, and six canonical curve relationships are aligned.
    // - Canonical Counterpart: openstudio::model::CoilWaterHeatingAirToWaterHeatPumpWrapped.
    // - Implemented Parity: The wrapped-coil scalar getters/setters, required availability schedule, five required performance curves, and optional crankcase-heater curve preserve the canonical bounded contract. Construction and load canonicalization supply only genuinely blank required relationships.
    // - Documented Delta: epmodel promotes this wrapper to `StraightComponent` so the real evaporator-air ports are explicit. This is an additive hierarchy change compared to canonical model.
    // - Documented Delta: Despite the base-class promotion, generic loop-placement APIs remain intentionally rejected because this coil is normally owned by a compound wrapped-condenser parent.
    // - Field/Storage Mapping: The schedule, curves, and scalar APIs map directly to EnergyPlus `Coil:WaterHeating:AirToWaterHeatPump:Wrapped` storage, including the real evaporator-air node fields.
    // - Evidence: `src/model/CoilWaterHeatingAirToWaterHeatPumpWrapped.hpp`, `src/model/CoilWaterHeatingAirToWaterHeatPumpWrapped.cpp`, `src/energyplus/ForwardTranslator/ForwardTranslateCoilWaterHeatingAirToWaterHeatPumpWrapped.cpp`, and `src/epmodel/test/CoilWaterHeatingAirToWaterHeatPumpWrapped_GTest.cpp`.
    // - Remaining Parity Work: Compound-parent removal and topology policy remain with `WaterHeaterHeatPumpWrappedCondenser`; this wrapper does not claim curve-resource ownership through `children()` or `remove()`.
    Schedule availabilitySchedule() const;
    bool setAvailabilitySchedule(Schedule& schedule);

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

    boost::optional<Curve> crankcaseHeaterCapacityFunctionofTemperatureCurve() const;
    bool setCrankcaseHeaterCapacityFunctionofTemperatureCurve(const Curve& curve);
    void resetCrankcaseHeaterCapacityFunctionofTemperatureCurve();

    double maximumAmbientTemperatureforCrankcaseHeaterOperation() const;
    bool isMaximumAmbientTemperatureforCrankcaseHeaterOperationDefaulted() const;
    bool setMaximumAmbientTemperatureforCrankcaseHeaterOperation(double maximumAmbientTemperatureforCrankcaseHeaterOperation);
    void resetMaximumAmbientTemperatureforCrankcaseHeaterOperation();

    std::string evaporatorAirTemperatureTypeforCurveObjects() const;
    bool isEvaporatorAirTemperatureTypeforCurveObjectsDefaulted() const;
    bool setEvaporatorAirTemperatureTypeforCurveObjects(const std::string& evaporatorAirTemperatureTypeforCurveObjects);
    void resetEvaporatorAirTemperatureTypeforCurveObjects();

    Curve heatingCapacityFunctionofTemperatureCurve() const;
    bool setHeatingCapacityFunctionofTemperatureCurve(const Curve& curve);

    Curve heatingCapacityFunctionofAirFlowFractionCurve() const;
    bool setHeatingCapacityFunctionofAirFlowFractionCurve(const Curve& curve);

    Curve heatingCOPFunctionofTemperatureCurve() const;
    bool setHeatingCOPFunctionofTemperatureCurve(const Curve& curve);

    Curve heatingCOPFunctionofAirFlowFractionCurve() const;
    bool setHeatingCOPFunctionofAirFlowFractionCurve(const Curve& curve);

    Curve partLoadFractionCorrelationCurve() const;
    bool setPartLoadFractionCorrelationCurve(const Curve& curve);

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
