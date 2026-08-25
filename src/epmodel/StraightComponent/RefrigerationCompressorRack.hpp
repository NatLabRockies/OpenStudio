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

/** \brief A refrigeration compressor rack.
 *
 * \par EnergyPlus object
 * \epobject{group-refrigeration.html#refrigerationcompressorrack,Refrigeration:CompressorRack}
 *
 * \par Important behavior
 * Rack capacity, curve, condenser schedule, heat-rejection-zone, and plant-demand placement fields map directly to Refrigeration:CompressorRack.
 *
 * \par OpenStudio Model API
 * The corresponding OpenStudio Model type is <code>openstudio::model::RefrigerationCompressorRack</code>.
 *
 * \par Known limitations
 * Refrigerated case, walk-in, and air-chiller list relationships are not available.
 */
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
