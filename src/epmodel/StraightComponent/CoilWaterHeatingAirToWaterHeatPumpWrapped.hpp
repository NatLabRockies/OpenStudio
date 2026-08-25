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

  /** \brief Represents a wrapped evaporator coil of an air-to-water heat-pump water heater.
   *
   * \par EnergyPlus object
   * \epobject{group-heating-and-cooling-coils.html#coilwaterheatingairtowaterheatpumpwrapped,Coil:WaterHeating:AirToWaterHeatPump:Wrapped}.
   *
   * \par Important behavior
   * The persisted scalar and currently supported schedule, curve, and node relationships map directly to the EnergyPlus object.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::CoilWaterHeatingAirToWaterHeatPumpWrapped</code>. EPModel exposes additional explicit default-state queries for EnergyPlus fields. <b>Not yet available:</b> broader AirflowNetwork, tank-link, and higher-level topology conveniences.
   * \par Known limitations
   * No known EPModel-specific limitations beyond the listed API differences.
   */
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
