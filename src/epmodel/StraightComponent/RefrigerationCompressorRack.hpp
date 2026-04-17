/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_REFRIGERATIONCOMPRESSORRACK_HPP
#define EPMODEL_REFRIGERATIONCOMPRESSORRACK_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Curve;
  class Model;
  class Schedule;
  class ThermalZone;

  namespace detail {

    class RefrigerationCompressorRack_Impl;

  }

  class EPMODEL_API RefrigerationCompressorRack : public StraightComponent
  {
   public:
    explicit RefrigerationCompressorRack(const Model& model);

    virtual ~RefrigerationCompressorRack() override = default;
    RefrigerationCompressorRack(const RefrigerationCompressorRack& other) = default;
    RefrigerationCompressorRack(RefrigerationCompressorRack&& other) = default;
    RefrigerationCompressorRack& operator=(const RefrigerationCompressorRack&) = default;
    RefrigerationCompressorRack& operator=(RefrigerationCompressorRack&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> condenserTypeValues();
    static std::vector<std::string> waterCooledLoopFlowTypeValues();

    // Schema Alignment Notes:
    // - Status: Partial Parity. The canonical scalar, curve, schedule, heat-rejection-zone, and plant-demand-only placement behavior are present, while the refrigerated case/walk-in list surface remains deferred.
    // - Canonical Counterpart: openstudio::model::RefrigerationCompressorRack.
    // - Implemented Parity: Constructor defaults, the compressor-rack COP and condenser-fan curve helpers, the condenser schedules, the heat-rejection-zone convenience, and plant-demand-only `addToNode(...)` now match canonical behavior alongside the preserved scalar API.
    // - Documented Delta: The refrigerated case/walk-in/air-chiller list helpers remain omitted because epmodel does not yet model the required `ModelObjectList` / `Refrigeration:CaseAndWalkInList` ownership layer.
    // - Field/Storage Mapping: These accessors map directly to EnergyPlus `Refrigeration:CompressorRack` scalar fields, object pointers, and condenser node fields used by the forward translator.
    // - Evidence: `src/model/RefrigerationCompressorRack.hpp`, `src/model/RefrigerationCompressorRack.cpp`, and `src/energyplus/ForwardTranslator/ForwardTranslateRefrigerationCompressorRack.cpp`.
    // - Remaining Parity Work: Add the refrigerated load-list convenience once epmodel grows the missing list-object support needed to persist canonical rack ownership semantics.

    // Heat rejection
    std::string heatRejectionLocation() const;
    bool setHeatRejectionLocation(const std::string& heatRejectionLocation);

    // Compressor rack performance
    double designCompressorRackCOP() const;
    bool setDesignCompressorRackCOP(double designCompressorRackCOP);

    Curve compressorRackCOPFunctionofTemperatureCurve() const;
    bool setCompressorRackCOPFunctionofTemperatureCurve(const Curve& curve);

    double designCondenserFanPower() const;
    bool setDesignCondenserFanPower(double designCondenserFanPower);

    boost::optional<Curve> condenserFanPowerFunctionofTemperatureCurve() const;
    bool setCondenserFanPowerFunctionofTemperatureCurve(const Curve& curve);
    void resetCondenserFanPowerFunctionofTemperatureCurve();

    // Condenser configuration
    std::string condenserType() const;
    bool setCondenserType(const std::string& condenserType);

    std::string waterCooledLoopFlowType() const;
    bool setWaterCooledLoopFlowType(const std::string& waterCooledLoopFlowType);

    boost::optional<Schedule> waterCooledCondenserOutletTemperatureSchedule() const;
    bool setWaterCooledCondenserOutletTemperatureSchedule(Schedule& schedule);
    void resetWaterCooledCondenserOutletTemperatureSchedule();

    boost::optional<double> waterCooledCondenserDesignFlowRate() const;
    bool setWaterCooledCondenserDesignFlowRate(double waterCooledCondenserDesignFlowRate);
    void resetWaterCooledCondenserDesignFlowRate();

    boost::optional<double> waterCooledCondenserMaximumFlowRate() const;
    bool setWaterCooledCondenserMaximumFlowRate(double waterCooledCondenserMaximumFlowRate);
    void resetWaterCooledCondenserMaximumFlowRate();

    double waterCooledCondenserMaximumWaterOutletTemperature() const;
    bool setWaterCooledCondenserMaximumWaterOutletTemperature(double waterCooledCondenserMaximumWaterOutletTemperature);

    double waterCooledCondenserMinimumWaterInletTemperature() const;
    bool setWaterCooledCondenserMinimumWaterInletTemperature(double waterCooledCondenserMinimumWaterInletTemperature);

    // Evaporative condenser
    boost::optional<Schedule> evaporativeCondenserAvailabilitySchedule() const;
    bool setEvaporativeCondenserAvailabilitySchedule(Schedule& schedule);
    void resetEvaporativeCondenserAvailabilitySchedule();

    double evaporativeCondenserEffectiveness() const;
    bool setEvaporativeCondenserEffectiveness(double evaporativeCondenserEffectiveness);

    boost::optional<double> evaporativeCondenserAirFlowRate() const;
    bool setEvaporativeCondenserAirFlowRate(double evaporativeCondenserAirFlowRate);
    bool isEvaporativeCondenserAirFlowRateAutocalculated() const;
    bool autocalculateEvaporativeCondenserAirFlowRate();

    // Basin heater
    double basinHeaterCapacity() const;
    bool setBasinHeaterCapacity(double basinHeaterCapacity);

    double basinHeaterSetpointTemperature() const;
    bool setBasinHeaterSetpointTemperature(double basinHeaterSetpointTemperature);

    // Evaporative condenser water pump
    boost::optional<double> designEvaporativeCondenserWaterPumpPower() const;
    bool setDesignEvaporativeCondenserWaterPumpPower(double designEvaporativeCondenserWaterPumpPower);
    bool isDesignEvaporativeCondenserWaterPumpPowerAutocalculated() const;
    bool autocalculateDesignEvaporativeCondenserWaterPumpPower();

    // End use categorization
    std::string endUseSubcategory() const;
    bool isEndUseSubcategoryDefaulted() const;
    bool setEndUseSubcategory(const std::string& endUseSubcategory);
    void resetEndUseSubcategory();

    boost::optional<ThermalZone> heatRejectionZone() const;
    bool setHeatRejectionZone(const ThermalZone& thermalZone);
    void resetHeatRejectionZone();

   protected:
    using ImplType = detail::RefrigerationCompressorRack_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit RefrigerationCompressorRack(std::shared_ptr<detail::RefrigerationCompressorRack_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
