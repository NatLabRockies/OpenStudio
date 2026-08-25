/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILHEATINGDXSINGLESPEED_HPP
#define EPMODEL_COILHEATINGDXSINGLESPEED_HPP

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
    class CoilHeatingDXSingleSpeed_Impl;
  }

  /** \brief Represents a single-speed direct-expansion heating coil.
   *
   * \par EnergyPlus object
   * \epobject{group-heating-and-cooling-coils.html#coilheatingdxsinglespeed,Coil:Heating:DX:SingleSpeed}.
   *
   * \par Important behavior
   * The persisted scalar and currently supported schedule, curve, and node relationships map directly to the EnergyPlus object.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::CoilHeatingDXSingleSpeed</code>. <b>Added:</b> EPModel exposes <code>addToNode()</code> and rated supply-fan power per volume flow. <b>Not yet available:</b> broader AirflowNetwork, tank-link, and higher-level topology conveniences.
   * \par Known limitations
   * No known EPModel-specific limitations beyond the listed API differences.
   */
  class EPMODEL_API CoilHeatingDXSingleSpeed : public StraightComponent
  {
   public:
    explicit CoilHeatingDXSingleSpeed(const Model& model);
    explicit CoilHeatingDXSingleSpeed(const Model& model, Schedule& availabilitySchedule, Curve& totalHeatingCapacityFunctionofTemperatureCurve,
                                      Curve& totalHeatingCapacityFunctionofFlowFractionCurve, Curve& energyInputRatioFunctionofTemperatureCurve,
                                      Curve& energyInputRatioFunctionofFlowFractionCurve, Curve& partLoadFractionCorrelationCurve);

    virtual ~CoilHeatingDXSingleSpeed() override = default;
    CoilHeatingDXSingleSpeed(const CoilHeatingDXSingleSpeed& other) = default;
    CoilHeatingDXSingleSpeed(CoilHeatingDXSingleSpeed&& other) = default;
    CoilHeatingDXSingleSpeed& operator=(const CoilHeatingDXSingleSpeed&) = default;
    CoilHeatingDXSingleSpeed& operator=(CoilHeatingDXSingleSpeed&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> validDefrostStrategyValues();
    static std::vector<std::string> validDefrostControlValues();

    bool addToNode(Node& node);

    Schedule availabilitySchedule() const;
    bool setAvailabilitySchedule(Schedule& schedule);

    Curve totalHeatingCapacityFunctionofTemperatureCurve() const;
    bool setTotalHeatingCapacityFunctionofTemperatureCurve(const Curve& curve);

    Curve totalHeatingCapacityFunctionofFlowFractionCurve() const;
    bool setTotalHeatingCapacityFunctionofFlowFractionCurve(const Curve& curve);

    Curve energyInputRatioFunctionofTemperatureCurve() const;
    bool setEnergyInputRatioFunctionofTemperatureCurve(const Curve& curve);

    Curve energyInputRatioFunctionofFlowFractionCurve() const;
    bool setEnergyInputRatioFunctionofFlowFractionCurve(const Curve& curve);

    Curve partLoadFractionCorrelationCurve() const;
    bool setPartLoadFractionCorrelationCurve(const Curve& curve);

    boost::optional<Curve> defrostEnergyInputRatioFunctionofTemperatureCurve() const;
    bool setDefrostEnergyInputRatioFunctionofTemperatureCurve(const Curve& curve);
    void resetDefrostEnergyInputRatioFunctionofTemperatureCurve();

    boost::optional<Curve> crankcaseHeaterCapacityFunctionofTemperatureCurve() const;
    bool setCrankcaseHeaterCapacityFunctionofTemperatureCurve(const Curve& curve);
    void resetCrankcaseHeaterCapacityFunctionofTemperatureCurve();

    boost::optional<double> ratedTotalHeatingCapacity() const;
    bool isRatedTotalHeatingCapacityAutosized() const;
    bool setRatedTotalHeatingCapacity(double ratedTotalHeatingCapacity);
    void autosizeRatedTotalHeatingCapacity();

    double ratedCOP() const;
    bool setRatedCOP(double ratedCOP);

    boost::optional<double> ratedAirFlowRate() const;
    bool isRatedAirFlowRateAutosized() const;
    bool setRatedAirFlowRate(double ratedAirFlowRate);
    void autosizeRatedAirFlowRate();

    double ratedSupplyFanPowerPerVolumeFlowRate() const;
    double ratedSupplyFanPowerPerVolumeFlowRate2017() const;
    double ratedSupplyFanPowerPerVolumeFlowRate2023() const;
    bool setRatedSupplyFanPowerPerVolumeFlowRate(double ratedSupplyFanPowerPerVolumeFlowRate);
    bool setRatedSupplyFanPowerPerVolumeFlowRate2017(double ratedSupplyFanPowerPerVolumeFlowRate2017);
    bool setRatedSupplyFanPowerPerVolumeFlowRate2023(double ratedSupplyFanPowerPerVolumeFlowRate2023);

    double minimumOutdoorDryBulbTemperatureforCompressorOperation() const;
    bool isMinimumOutdoorDryBulbTemperatureforCompressorOperationDefaulted() const;
    bool setMinimumOutdoorDryBulbTemperatureforCompressorOperation(double minimumOutdoorDryBulbTemperatureforCompressorOperation);
    void resetMinimumOutdoorDryBulbTemperatureforCompressorOperation();

    double maximumOutdoorDryBulbTemperatureforDefrostOperation() const;
    bool isMaximumOutdoorDryBulbTemperatureforDefrostOperationDefaulted() const;
    bool setMaximumOutdoorDryBulbTemperatureforDefrostOperation(double maximumOutdoorDryBulbTemperatureforDefrostOperation);
    void resetMaximumOutdoorDryBulbTemperatureforDefrostOperation();

    double crankcaseHeaterCapacity() const;
    bool isCrankcaseHeaterCapacityDefaulted() const;
    bool setCrankcaseHeaterCapacity(double crankcaseHeaterCapacity);
    void resetCrankcaseHeaterCapacity();

    double maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation() const;
    bool isMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperationDefaulted() const;
    bool setMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation(double maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation);
    void resetMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation();

    std::string defrostStrategy() const;
    bool isDefrostStrategyDefaulted() const;
    bool setDefrostStrategy(const std::string& defrostStrategy);
    void resetDefrostStrategy();

    std::string defrostControl() const;
    bool isDefrostControlDefaulted() const;
    bool setDefrostControl(const std::string& defrostControl);
    void resetDefrostControl();

    double defrostTimePeriodFraction() const;
    bool isDefrostTimePeriodFractionDefaulted() const;
    bool setDefrostTimePeriodFraction(double defrostTimePeriodFraction);
    void resetDefrostTimePeriodFraction();

    boost::optional<double> resistiveDefrostHeaterCapacity() const;
    bool isResistiveDefrostHeaterCapacityDefaulted() const;
    bool isResistiveDefrostHeaterCapacityAutosized() const;
    bool setResistiveDefrostHeaterCapacity(double resistiveDefrostHeaterCapacity);
    void resetResistiveDefrostHeaterCapacity();
    void autosizeResistiveDefrostHeaterCapacity();

   protected:
    using ImplType = detail::CoilHeatingDXSingleSpeed_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit CoilHeatingDXSingleSpeed(std::shared_ptr<detail::CoilHeatingDXSingleSpeed_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
