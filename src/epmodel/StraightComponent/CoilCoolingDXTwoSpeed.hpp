/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILCOOLINGDXTWOSPEED_HPP
#define EPMODEL_COILCOOLINGDXTWOSPEED_HPP

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
    class CoilCoolingDXTwoSpeed_Impl;
  }

  /** \brief Represents a two-speed direct-expansion cooling coil.
   *
   * \par EnergyPlus object
   * \epobject{group-heating-and-cooling-coils.html#coilcoolingdxtwospeed,Coil:Cooling:DX:TwoSpeed}.
   *
   * \par Important behavior
   * The persisted scalar and currently supported schedule, curve, and node relationships map directly to the EnergyPlus object.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::CoilCoolingDXTwoSpeed</code>. <b>Added:</b> EPModel exposes <code>addToNode()</code> and autosize/default-state helpers for supported two-speed fields. <b>Not yet available:</b> the full Model evaporative-condenser, condenser-node, and related tank/topology convenience surface.
   * \par Known limitations
   * No known EPModel-specific limitations beyond the listed API differences.
   */
  class EPMODEL_API CoilCoolingDXTwoSpeed : public StraightComponent
  {
   public:
    explicit CoilCoolingDXTwoSpeed(const Model& model);
    explicit CoilCoolingDXTwoSpeed(const Model& model, Schedule& availabilitySchedule, const Curve& coolingCurveFofTemp,
                                   const Curve& coolingCurveFofFlow, const Curve& energyInputRatioFofTemp, const Curve& energyInputRatioFofFlow,
                                   const Curve& partLoadFraction, const Curve& lowSpeedCoolingCurveFofTemp,
                                   const Curve& lowSpeedEnergyInputRatioFofTemp);

    virtual ~CoilCoolingDXTwoSpeed() override = default;
    CoilCoolingDXTwoSpeed(const CoilCoolingDXTwoSpeed& other) = default;
    CoilCoolingDXTwoSpeed(CoilCoolingDXTwoSpeed&& other) = default;
    CoilCoolingDXTwoSpeed& operator=(const CoilCoolingDXTwoSpeed&) = default;
    CoilCoolingDXTwoSpeed& operator=(CoilCoolingDXTwoSpeed&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> condenserTypeValues();

    Schedule availabilitySchedule() const;
    bool setAvailabilitySchedule(Schedule& schedule);

    boost::optional<double> ratedHighSpeedTotalCoolingCapacity() const;
    bool isRatedHighSpeedTotalCoolingCapacityAutosized() const;
    bool setRatedHighSpeedTotalCoolingCapacity(double ratedHighSpeedTotalCoolingCapacity);
    void autosizeRatedHighSpeedTotalCoolingCapacity();

    boost::optional<double> ratedHighSpeedSensibleHeatRatio() const;
    bool isRatedHighSpeedSensibleHeatRatioAutosized() const;
    bool setRatedHighSpeedSensibleHeatRatio(double ratedHighSpeedSensibleHeatRatio);
    void autosizeRatedHighSpeedSensibleHeatRatio();

    double ratedHighSpeedCOP() const;
    bool setRatedHighSpeedCOP(double ratedHighSpeedCOP);

    boost::optional<double> ratedHighSpeedAirFlowRate() const;
    bool isRatedHighSpeedAirFlowRateAutosized() const;
    bool setRatedHighSpeedAirFlowRate(double ratedHighSpeedAirFlowRate);
    void autosizeRatedHighSpeedAirFlowRate();

    double ratedHighSpeedEvaporatorFanPowerPerVolumeFlowRate2017() const;
    bool setRatedHighSpeedEvaporatorFanPowerPerVolumeFlowRate2017(double ratedHighSpeedEvaporatorFanPowerPerVolumeFlowRate2017);

    double ratedHighSpeedEvaporatorFanPowerPerVolumeFlowRate2023() const;
    bool setRatedHighSpeedEvaporatorFanPowerPerVolumeFlowRate2023(double ratedHighSpeedEvaporatorFanPowerPerVolumeFlowRate2023);

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

    boost::optional<double> ratedLowSpeedTotalCoolingCapacity() const;
    bool isRatedLowSpeedTotalCoolingCapacityAutosized() const;
    bool setRatedLowSpeedTotalCoolingCapacity(double ratedLowSpeedTotalCoolingCapacity);
    void autosizeRatedLowSpeedTotalCoolingCapacity();

    boost::optional<double> ratedLowSpeedSensibleHeatRatio() const;
    bool isRatedLowSpeedSensibleHeatRatioAutosized() const;
    bool setRatedLowSpeedSensibleHeatRatio(double ratedLowSpeedSensibleHeatRatio);
    void autosizeRatedLowSpeedSensibleHeatRatio();

    double ratedLowSpeedCOP() const;
    bool setRatedLowSpeedCOP(double ratedLowSpeedCOP);

    boost::optional<double> ratedLowSpeedAirFlowRate() const;
    bool isRatedLowSpeedAirFlowRateAutosized() const;
    bool setRatedLowSpeedAirFlowRate(double ratedLowSpeedAirFlowRate);
    void autosizeRatedLowSpeedAirFlowRate();

    double ratedLowSpeedEvaporatorFanPowerPerVolumeFlowRate2017() const;
    bool setRatedLowSpeedEvaporatorFanPowerPerVolumeFlowRate2017(double ratedLowSpeedEvaporatorFanPowerPerVolumeFlowRate2017);

    double ratedLowSpeedEvaporatorFanPowerPerVolumeFlowRate2023() const;
    bool setRatedLowSpeedEvaporatorFanPowerPerVolumeFlowRate2023(double ratedLowSpeedEvaporatorFanPowerPerVolumeFlowRate2023);

    Curve lowSpeedTotalCoolingCapacityFunctionOfTemperatureCurve() const;
    bool setLowSpeedTotalCoolingCapacityFunctionOfTemperatureCurve(const Curve& curve);

    Curve lowSpeedEnergyInputRatioFunctionOfTemperatureCurve() const;
    bool setLowSpeedEnergyInputRatioFunctionOfTemperatureCurve(const Curve& curve);

    boost::optional<Schedule> basinHeaterOperatingSchedule() const;
    bool setBasinHeaterOperatingSchedule(Schedule& schedule);
    void resetBasinHeaterOperatingSchedule();

    boost::optional<std::string> condenserAirInletNodeName() const;
    bool setCondenserAirInletNodeName(const std::string& condenserAirInletNodeName);

    std::string condenserType() const;
    bool setCondenserType(const std::string& condenserType);

    double highSpeedEvaporativeCondenserEffectiveness() const;
    bool setHighSpeedEvaporativeCondenserEffectiveness(double highSpeedEvaporativeCondenserEffectiveness);

    boost::optional<double> highSpeedEvaporativeCondenserAirFlowRate() const;
    bool isHighSpeedEvaporativeCondenserAirFlowRateAutosized() const;
    bool setHighSpeedEvaporativeCondenserAirFlowRate(double highSpeedEvaporativeCondenserAirFlowRate);
    void autosizeHighSpeedEvaporativeCondenserAirFlowRate();

    boost::optional<double> highSpeedEvaporativeCondenserPumpRatedPowerConsumption() const;
    bool isHighSpeedEvaporativeCondenserPumpRatedPowerConsumptionAutosized() const;
    bool setHighSpeedEvaporativeCondenserPumpRatedPowerConsumption(double highSpeedEvaporativeCondenserPumpRatedPowerConsumption);
    void autosizeHighSpeedEvaporativeCondenserPumpRatedPowerConsumption();

    double lowSpeedEvaporativeCondenserEffectiveness() const;
    bool setLowSpeedEvaporativeCondenserEffectiveness(double lowSpeedEvaporativeCondenserEffectiveness);

    boost::optional<double> lowSpeedEvaporativeCondenserAirFlowRate() const;
    bool isLowSpeedEvaporativeCondenserAirFlowRateAutosized() const;
    bool setLowSpeedEvaporativeCondenserAirFlowRate(double lowSpeedEvaporativeCondenserAirFlowRate);
    void autosizeLowSpeedEvaporativeCondenserAirFlowRate();

    boost::optional<double> lowSpeedEvaporativeCondenserPumpRatedPowerConsumption() const;
    bool isLowSpeedEvaporativeCondenserPumpRatedPowerConsumptionAutosized() const;
    bool setLowSpeedEvaporativeCondenserPumpRatedPowerConsumption(double lowSpeedEvaporativeCondenserPumpRatedPowerConsumption);
    void autosizeLowSpeedEvaporativeCondenserPumpRatedPowerConsumption();

    double basinHeaterCapacity() const;
    bool setBasinHeaterCapacity(double basinHeaterCapacity);

    double basinHeaterSetpointTemperature() const;
    bool setBasinHeaterSetpointTemperature(double basinHeaterSetpointTemperature);

    double minimumOutdoorDryBulbTemperatureforCompressorOperation() const;
    bool setMinimumOutdoorDryBulbTemperatureforCompressorOperation(double minimumOutdoorDryBulbTemperatureforCompressorOperation);

    double unitInternalStaticAirPressure() const;
    bool setUnitInternalStaticAirPressure(double unitInternalStaticAirPressure);

    bool addToNode(Node& node);

   protected:
    using ImplType = detail::CoilCoolingDXTwoSpeed_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit CoilCoolingDXTwoSpeed(std::shared_ptr<detail::CoilCoolingDXTwoSpeed_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
