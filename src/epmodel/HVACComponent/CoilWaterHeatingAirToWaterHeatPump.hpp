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
    // - Status: Scalar Parity. The scalar rating and control surface is aligned, while availability-schedule, curve, and connection APIs are still omitted.
    // - Canonical Counterpart: openstudio::model::CoilWaterHeatingAirToWaterHeatPump.
    // - Implemented Parity: `evaporatorAirTemperatureTypeforCurveObjectsValues`, the rating setters/getters, pump/fan flags, and flow autosize helpers preserve the canonical scalar contract.
    // - Documented Delta: Availability schedule, curve-link, and node-link accessors are not exposed yet even though they exist on the canonical model type.
    // - Field/Storage Mapping: The epmodel wrapper maps the preserved scalar fields directly to EnergyPlus `Coil:WaterHeating:AirToWaterHeatPump:Pumped` storage.
    // - Evidence: `src/model/CoilWaterHeatingAirToWaterHeatPump.hpp`, `src/model/CoilWaterHeatingAirToWaterHeatPump.cpp`, `src/energyplus/ForwardTranslator/ForwardTranslateCoilWaterHeatingAirToWaterHeatPump.cpp`, and `src/epmodel/test/CoilWaterHeatingAirToWaterHeatPump_GTest.cpp`.
    // - Remaining Parity Work: Add the omitted schedule, curve, and object-link APIs after the relationship layer is available.
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
