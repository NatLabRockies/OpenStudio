/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILCOOLINGDXSINGLESPEED_HPP
#define EPMODEL_COILCOOLINGDXSINGLESPEED_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class Node;
  class Schedule;
  class Curve;

  namespace detail {
    class CoilCoolingDXSingleSpeed_Impl;
  }

  /** \brief Represents a single-speed direct-expansion cooling coil.
   *
   * \par EnergyPlus object
   * \epobject{group-heating-and-cooling-coils.html#coilcoolingdxsinglespeed,Coil:Cooling:DX:SingleSpeed}
   *
   * \par Important behavior
   * Schedule and curve relationship setters reject objects from another model
   * or object types that are not accepted by the corresponding EnergyPlus
   * field, leaving the existing relationship unchanged. During
   * canonicalization, a genuinely blank availability relationship is repaired
   * with the model's always-on schedule. Setting a condenser air inlet node
   * maintains its outdoor-air declaration and removes obsolete
   * <code>OutdoorAir:NodeList</code> entries when they are no longer used.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::CoilCoolingDXSingleSpeed</code>.
   *
   * - <b>Not yet available:</b> The deprecated
   *   <code>ratedEvaporatorFanPowerPerVolumeFlowRate()</code> getter and both
   *   <code>setRatedEvaporatorFanPowerPerVolumeFlowRate(...)</code> setter
   *   overloads are not available. The replacement fields distinguish the
   *   evaporator-fan power used by the 2017 and 2023 editions of the ANSI/AHRI
   *   210/240 rating procedure. Use
   *   <code>ratedEvaporatorFanPowerPerVolumeFlowRate2017()</code>,
   *   <code>setRatedEvaporatorFanPowerPerVolumeFlowRate2017(...)</code>,
   *   <code>ratedEvaporatorFanPowerPerVolumeFlowRate2023()</code>, and
   *   <code>setRatedEvaporatorFanPowerPerVolumeFlowRate2023(...)</code>
   *   instead.
   * - <b>Not yet available:</b> Optional-value setter overloads are not
   *   available for the scalar fields that have them in OpenStudio Model,
   *   including rated COP, fan-power values, latent-performance values,
   *   evaporative-condenser values, crankcase-heater capacity, and basin-heater
   *   values. EPModel provides concrete-value setters; for autosizable fields,
   *   use <code>autosizeRatedTotalCoolingCapacity()</code>,
   *   <code>autosizeRatedSensibleHeatRatio()</code>,
   *   <code>autosizeRatedAirFlowRate()</code>,
   *   <code>autosizeEvaporativeCondenserAirFlowRate()</code>, or
   *   <code>autosizeEvaporativeCondenserPumpRatedPowerConsumption()</code>.
   * - <b>Not yet available:</b>
   *   <code>getAirflowNetworkEquivalentDuct(...)</code> and
   *   <code>airflowNetworkEquivalentDuct()</code>.
   * - <b>Not yet available:</b> Simulation-result accessors for autosized
   *   values: <code>autosizedRatedAirFlowRate()</code>,
   *   <code>autosizedRatedTotalCoolingCapacity()</code>,
   *   <code>autosizedRatedSensibleHeatRatio()</code>,
   *   <code>autosizedEvaporativeCondenserAirFlowRate()</code>, and
   *   <code>autosizedEvaporativeCondenserPumpRatedPowerConsumption()</code>.
   *
   * \par Known limitations
   * <code>addToNode()</code> currently supports the air-loop supply path. It
   * rejects demand-branch nodes and outboard outdoor-air-system nodes.
   */
  class EPMODEL_API CoilCoolingDXSingleSpeed : public StraightComponent
  {
   public:
    explicit CoilCoolingDXSingleSpeed(const Model& model);
    explicit CoilCoolingDXSingleSpeed(const Model& model, Schedule& availabilitySchedule, const Curve& coolingCurveFofTemp,
                                      const Curve& coolingCurveFofFlow, const Curve& energyInputRatioFofTemp, const Curve& energyInputRatioFofFlow,
                                      const Curve& partLoadFraction);

    virtual ~CoilCoolingDXSingleSpeed() override = default;
    CoilCoolingDXSingleSpeed(const CoilCoolingDXSingleSpeed& other) = default;
    CoilCoolingDXSingleSpeed(CoilCoolingDXSingleSpeed&& other) = default;
    CoilCoolingDXSingleSpeed& operator=(const CoilCoolingDXSingleSpeed&) = default;
    CoilCoolingDXSingleSpeed& operator=(CoilCoolingDXSingleSpeed&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> condenserTypeValues();

    Schedule availabilitySchedule() const;
    bool setAvailabilitySchedule(Schedule& schedule);

    Curve totalCoolingCapacityFunctionOfTemperatureCurve() const;
    bool setTotalCoolingCapacityFunctionOfTemperatureCurve(const Curve& curve);

    Curve totalCoolingCapacityFunctionOfFlowFractionCurve() const;
    bool setTotalCoolingCapacityFunctionOfFlowFractionCurve(const Curve& curve);

    Curve energyInputRatioFunctionOfTemperatureCurve() const;
    bool setEnergyInputRatioFunctionOfTemperatureCurve(const Curve& curve);

    Curve energyInputRatioFunctionOfFlowFractionCurve() const;
    bool setEnergyInputRatioFunctionOfFlowFractionCurve(const Curve& curve);

    Curve partLoadFractionCorrelationCurve() const;
    bool setPartLoadFractionCorrelationCurve(const Curve& curve);

    boost::optional<Curve> crankcaseHeaterCapacityFunctionofTemperatureCurve() const;
    bool setCrankcaseHeaterCapacityFunctionofTemperatureCurve(const Curve& curve);
    void resetCrankcaseHeaterCapacityFunctionofTemperatureCurve();

    boost::optional<Schedule> basinHeaterOperatingSchedule() const;
    bool setBasinHeaterOperatingSchedule(Schedule& schedule);
    void resetBasinHeaterOperatingSchedule();

    boost::optional<std::string> condenserAirInletNodeName() const;
    bool setCondenserAirInletNodeName(const boost::optional<std::string>& condenserAirInletNodeName);

    std::string condenserType() const;
    bool setCondenserType(const std::string& condenserType);

    double ratedCOP() const;
    bool setRatedCOP(double ratedCOP);

    double ratedEvaporatorFanPowerPerVolumeFlowRate2017() const;
    bool setRatedEvaporatorFanPowerPerVolumeFlowRate2017(double ratedEvaporatorFanPowerPerVolumeFlowRate2017);

    double ratedEvaporatorFanPowerPerVolumeFlowRate2023() const;
    bool setRatedEvaporatorFanPowerPerVolumeFlowRate2023(double ratedEvaporatorFanPowerPerVolumeFlowRate2023);

    boost::optional<double> ratedTotalCoolingCapacity() const;
    bool isRatedTotalCoolingCapacityAutosized() const;
    bool setRatedTotalCoolingCapacity(double ratedTotalCoolingCapacity);
    void autosizeRatedTotalCoolingCapacity();

    boost::optional<double> ratedSensibleHeatRatio() const;
    bool isRatedSensibleHeatRatioAutosized() const;
    bool setRatedSensibleHeatRatio(double ratedSensibleHeatRatio);
    void autosizeRatedSensibleHeatRatio();

    boost::optional<double> ratedAirFlowRate() const;
    bool isRatedAirFlowRateAutosized() const;
    bool setRatedAirFlowRate(double ratedAirFlowRate);
    void autosizeRatedAirFlowRate();

    double nominalTimeForCondensateRemovalToBegin() const;
    bool setNominalTimeForCondensateRemovalToBegin(double nominalTimeForCondensateRemovalToBegin);

    double ratioOfInitialMoistureEvaporationRateAndSteadyStateLatentCapacity() const;
    bool
      setRatioOfInitialMoistureEvaporationRateAndSteadyStateLatentCapacity(double ratioOfInitialMoistureEvaporationRateAndSteadyStateLatentCapacity);

    double maximumCyclingRate() const;
    bool setMaximumCyclingRate(double maximumCyclingRate);

    double latentCapacityTimeConstant() const;
    bool setLatentCapacityTimeConstant(double latentCapacityTimeConstant);

    double evaporativeCondenserEffectiveness() const;
    bool setEvaporativeCondenserEffectiveness(double evaporativeCondenserEffectiveness);

    boost::optional<double> evaporativeCondenserAirFlowRate() const;
    bool isEvaporativeCondenserAirFlowRateAutosized() const;
    bool setEvaporativeCondenserAirFlowRate(double evaporativeCondenserAirFlowRate);
    void autosizeEvaporativeCondenserAirFlowRate();

    boost::optional<double> evaporativeCondenserPumpRatedPowerConsumption() const;
    bool isEvaporativeCondenserPumpRatedPowerConsumptionAutosized() const;
    bool setEvaporativeCondenserPumpRatedPowerConsumption(double evaporativeCondenserPumpRatedPowerConsumption);
    void autosizeEvaporativeCondenserPumpRatedPowerConsumption();

    double crankcaseHeaterCapacity() const;
    bool setCrankcaseHeaterCapacity(double crankcaseHeaterCapacity);

    double maximumOutdoorDryBulbTemperatureForCrankcaseHeaterOperation() const;
    bool setMaximumOutdoorDryBulbTemperatureForCrankcaseHeaterOperation(double maximumOutdoorDryBulbTemperatureForCrankcaseHeaterOperation);

    double basinHeaterCapacity() const;
    bool setBasinHeaterCapacity(double basinHeaterCapacity);

    double basinHeaterSetpointTemperature() const;
    bool setBasinHeaterSetpointTemperature(double basinHeaterSetpointTemperature);

    double minimumOutdoorDryBulbTemperatureforCompressorOperation() const;
    bool setMinimumOutdoorDryBulbTemperatureforCompressorOperation(double minimumOutdoorDryBulbTemperatureforCompressorOperation);

    bool addToNode(Node& node);

   protected:
    using ImplType = detail::CoilCoolingDXSingleSpeed_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit CoilCoolingDXSingleSpeed(std::shared_ptr<detail::CoilCoolingDXSingleSpeed_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
