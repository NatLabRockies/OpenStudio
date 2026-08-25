/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILHEATINGDXVARIABLESPEED_HPP
#define EPMODEL_COILHEATINGDXVARIABLESPEED_HPP

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
    class CoilHeatingDXVariableSpeed_Impl;
  }

  /** \brief Represents a variable-speed direct-expansion heating coil.
   *
   * \par EnergyPlus object
   * \epobject{group-heating-and-cooling-coils.html#coilheatingdxvariablespeed,Coil:Heating:DX:VariableSpeed}.
   *
   * \par Important behavior
   * The persisted scalar, schedule, and currently supported performance relationships use the EnergyPlus coil topology.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::CoilHeatingDXVariableSpeed</code>.
   * Not yet available: the corresponding speed-data family and owning speed-list API, plus broader node-link conveniences.
   *
   * \par Known limitations
   * No known EPModel-specific limitations beyond the listed API differences.
   */
  class EPMODEL_API CoilHeatingDXVariableSpeed : public StraightComponent
  {
   public:
    explicit CoilHeatingDXVariableSpeed(const Model& model);
    explicit CoilHeatingDXVariableSpeed(const Model& model, const Curve& partLoadFraction);

    virtual ~CoilHeatingDXVariableSpeed() override = default;
    CoilHeatingDXVariableSpeed(const CoilHeatingDXVariableSpeed& other) = default;
    CoilHeatingDXVariableSpeed(CoilHeatingDXVariableSpeed&& other) = default;
    CoilHeatingDXVariableSpeed& operator=(const CoilHeatingDXVariableSpeed&) = default;
    CoilHeatingDXVariableSpeed& operator=(CoilHeatingDXVariableSpeed&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> defrostStrategyValues();
    static std::vector<std::string> defrostControlValues();

    bool addToNode(Node& node);

    Schedule availabilitySchedule() const;
    bool setAvailabilitySchedule(Schedule& schedule);

    int nominalSpeedLevel() const;
    bool setNominalSpeedLevel(int nominalSpeedLevel);

    boost::optional<double> ratedHeatingCapacityAtSelectedNominalSpeedLevel() const;
    bool isRatedHeatingCapacityAtSelectedNominalSpeedLevelAutosized() const;
    bool setRatedHeatingCapacityAtSelectedNominalSpeedLevel(double ratedHeatingCapacityAtSelectedNominalSpeedLevel);
    void autosizeRatedHeatingCapacityAtSelectedNominalSpeedLevel();

    boost::optional<double> ratedAirFlowRateAtSelectedNominalSpeedLevel() const;
    bool isRatedAirFlowRateAtSelectedNominalSpeedLevelAutosized() const;
    bool setRatedAirFlowRateAtSelectedNominalSpeedLevel(double ratedAirFlowRateAtSelectedNominalSpeedLevel);
    void autosizeRatedAirFlowRateAtSelectedNominalSpeedLevel();

    Curve energyPartLoadFractionCurve() const;
    bool setEnergyPartLoadFractionCurve(const Curve& curve);

    boost::optional<Curve> defrostEnergyInputRatioFunctionofTemperatureCurve() const;
    bool setDefrostEnergyInputRatioFunctionofTemperatureCurve(const Curve& curve);
    void resetDefrostEnergyInputRatioFunctionofTemperatureCurve();

    double minimumOutdoorDryBulbTemperatureforCompressorOperation() const;
    bool setMinimumOutdoorDryBulbTemperatureforCompressorOperation(double minimumOutdoorDryBulbTemperatureforCompressorOperation);

    boost::optional<double> outdoorDryBulbTemperaturetoTurnOnCompressor() const;
    bool setOutdoorDryBulbTemperaturetoTurnOnCompressor(double outdoorDryBulbTemperaturetoTurnOnCompressor);
    void resetOutdoorDryBulbTemperaturetoTurnOnCompressor();

    double maximumOutdoorDryBulbTemperatureforDefrostOperation() const;
    bool setMaximumOutdoorDryBulbTemperatureforDefrostOperation(double maximumOutdoorDryBulbTemperatureforDefrostOperation);

    double crankcaseHeaterCapacity() const;
    bool setCrankcaseHeaterCapacity(double crankcaseHeaterCapacity);

    boost::optional<Curve> crankcaseHeaterCapacityFunctionofTemperatureCurve() const;
    bool setCrankcaseHeaterCapacityFunctionofTemperatureCurve(const Curve& curve);
    void resetCrankcaseHeaterCapacityFunctionofTemperatureCurve();

    double maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation() const;
    bool setMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation(double maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation);

    std::string defrostStrategy() const;
    bool setDefrostStrategy(const std::string& defrostStrategy);

    std::string defrostControl() const;
    bool setDefrostControl(const std::string& defrostControl);

    double defrostTimePeriodFraction() const;
    bool setDefrostTimePeriodFraction(double defrostTimePeriodFraction);

    boost::optional<double> resistiveDefrostHeaterCapacity() const;
    bool isResistiveDefrostHeaterCapacityAutosized() const;
    bool setResistiveDefrostHeaterCapacity(double resistiveDefrostHeaterCapacity);
    void autosizeResistiveDefrostHeaterCapacity();

   protected:
    using ImplType = detail::CoilHeatingDXVariableSpeed_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit CoilHeatingDXVariableSpeed(std::shared_ptr<detail::CoilHeatingDXVariableSpeed_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
