/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILWATERHEATINGAIRTOWATERHEATPUMP_HPP
#define EPMODEL_COILWATERHEATINGAIRTOWATERHEATPUMP_HPP

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

  namespace detail {
    class CoilWaterHeatingAirToWaterHeatPump_Impl;
  }

  /** \brief Represents a pumped air-to-water heat-pump water-heating coil.
   *
   * \par EnergyPlus object
   * \epobject{group-heating-and-cooling-coils.html#coilwaterheatingairtowaterheatpumppumped,Coil:WaterHeating:AirToWaterHeatPump:Pumped}
   *
   * \par Important behavior
   * The availability schedule getter repairs a missing persisted target with
   * the model's always-on discrete schedule. Curve relationships and the
   * evaporator-air and condenser-water node fields are stored directly on the
   * EnergyPlus object. Autosized-value queries currently return no value.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::CoilWaterHeatingAirToWaterHeatPump</code>.
   * EPModel exposes the same coil fields and curve relationships, but derives
   * from <code>WaterToAirComponent</code> so the air/water topology methods are
   * available.
   *
   * \par Known limitations
   * <code>addToNode()</code> and <code>addToSplitter()</code> reject direct loop
   * placement. This coil is expected to be owned and connected by its
   * compound heat-pump water-heater parent.
   */
  class EPMODEL_API CoilWaterHeatingAirToWaterHeatPump : public WaterToAirComponent
  {
   public:
    explicit CoilWaterHeatingAirToWaterHeatPump(const Model& model, const Curve& heatingCapacityFunctionofTemperatureCurve,
                                                const Curve& heatingCapacityFunctionofAirFlowFractionCurve,
                                                const Curve& heatingCapacityFunctionofWaterFlowFractionCurve,
                                                const Curve& heatingCOPFunctionofTemperatureCurve,
                                                const Curve& heatingCOPFunctionofAirFlowFractionCurve,
                                                const Curve& heatingCOPFunctionofWaterFlowFractionCurve,
                                                const Curve& partLoadFractionCorrelationCurve);
    explicit CoilWaterHeatingAirToWaterHeatPump(const Model& model);

    virtual ~CoilWaterHeatingAirToWaterHeatPump() override = default;
    CoilWaterHeatingAirToWaterHeatPump(const CoilWaterHeatingAirToWaterHeatPump& other) = default;
    CoilWaterHeatingAirToWaterHeatPump(CoilWaterHeatingAirToWaterHeatPump&& other) = default;
    CoilWaterHeatingAirToWaterHeatPump& operator=(const CoilWaterHeatingAirToWaterHeatPump&) = default;
    CoilWaterHeatingAirToWaterHeatPump& operator=(CoilWaterHeatingAirToWaterHeatPump&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> evaporatorAirTemperatureTypeforCurveObjectsValues();

    Schedule availabilitySchedule() const;
    bool setAvailabilitySchedule(Schedule& availabilitySchedule);

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
    bool setRatedEvaporatorAirFlowRate(double ratedEvaporatorAirFlowRate);
    bool isRatedEvaporatorAirFlowRateAutosized() const;
    void autosizeRatedEvaporatorAirFlowRate();

    boost::optional<double> ratedCondenserWaterFlowRate() const;
    bool setRatedCondenserWaterFlowRate(double ratedCondenserWaterFlowRate);
    bool isRatedCondenserWaterFlowRateAutosized() const;
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

    boost::optional<Curve> crankcaseHeaterCapacityFunctionofTemperatureCurve() const;
    bool setCrankcaseHeaterCapacityFunctionofTemperatureCurve(const Curve& crankcaseHeaterCapacityFunctionofTemperatureCurve);
    void resetCrankcaseHeaterCapacityFunctionofTemperatureCurve();

    double maximumAmbientTemperatureforCrankcaseHeaterOperation() const;
    bool setMaximumAmbientTemperatureforCrankcaseHeaterOperation(double maximumAmbientTemperatureforCrankcaseHeaterOperation);

    std::string evaporatorAirTemperatureTypeforCurveObjects() const;
    bool setEvaporatorAirTemperatureTypeforCurveObjects(const std::string& evaporatorAirTemperatureTypeforCurveObjects);

    Curve heatingCapacityFunctionofTemperatureCurve() const;
    bool setHeatingCapacityFunctionofTemperatureCurve(const Curve& heatingCapacityFunctionofTemperatureCurve);

    Curve heatingCapacityFunctionofAirFlowFractionCurve() const;
    bool setHeatingCapacityFunctionofAirFlowFractionCurve(const Curve& heatingCapacityFunctionofAirFlowFractionCurve);

    Curve heatingCapacityFunctionofWaterFlowFractionCurve() const;
    bool setHeatingCapacityFunctionofWaterFlowFractionCurve(const Curve& heatingCapacityFunctionofWaterFlowFractionCurve);

    Curve heatingCOPFunctionofTemperatureCurve() const;
    bool setHeatingCOPFunctionofTemperatureCurve(const Curve& heatingCOPFunctionofTemperatureCurve);

    Curve heatingCOPFunctionofAirFlowFractionCurve() const;
    bool setHeatingCOPFunctionofAirFlowFractionCurve(const Curve& heatingCOPFunctionofAirFlowFractionCurve);

    Curve heatingCOPFunctionofWaterFlowFractionCurve() const;
    bool setHeatingCOPFunctionofWaterFlowFractionCurve(const Curve& heatingCOPFunctionofWaterFlowFractionCurve);

    Curve partLoadFractionCorrelationCurve() const;
    bool setPartLoadFractionCorrelationCurve(const Curve& partLoadFractionCorrelationCurve);

    boost::optional<double> autosizedRatedEvaporatorAirFlowRate() const;
    boost::optional<double> autosizedRatedCondenserWaterFlowRate() const;

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
