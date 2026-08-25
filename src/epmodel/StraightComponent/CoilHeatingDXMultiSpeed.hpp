/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILHEATINGDXMULTISPEED_HPP
#define EPMODEL_COILHEATINGDXMULTISPEED_HPP

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
    class CoilHeatingDXMultiSpeed_Impl;
  }

  /** \brief Represents a multispeed direct-expansion heating coil.
   *
   * \par EnergyPlus object
   * \epobject{group-heating-and-cooling-coils.html#coilheatingdxmultispeed,Coil:Heating:DX:MultiSpeed}.
   *
   * \par Important behavior
   * The persisted scalar, schedule, and currently supported stage-control relationships use the EnergyPlus coil topology.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::CoilHeatingDXMultiSpeed</code>.
   * Not yet available: stage-data ownership and extensible stage-list APIs.
   *
   * \par Known limitations
   * No known EPModel-specific limitations beyond the listed API differences.
   */
  class EPMODEL_API CoilHeatingDXMultiSpeed : public StraightComponent
  {
   public:
    explicit CoilHeatingDXMultiSpeed(const Model& model);

    virtual ~CoilHeatingDXMultiSpeed() override = default;
    CoilHeatingDXMultiSpeed(const CoilHeatingDXMultiSpeed& other) = default;
    CoilHeatingDXMultiSpeed(CoilHeatingDXMultiSpeed&& other) = default;
    CoilHeatingDXMultiSpeed& operator=(const CoilHeatingDXMultiSpeed&) = default;
    CoilHeatingDXMultiSpeed& operator=(CoilHeatingDXMultiSpeed&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> defrostStrategyValues();
    static std::vector<std::string> defrostControlValues();
    static std::vector<std::string> fuelTypeValues();

    bool addToNode(Node& node);

    boost::optional<Schedule> availabilitySchedule() const;
    bool setAvailabilitySchedule(Schedule& schedule);
    void resetAvailabilitySchedule();

    boost::optional<Curve> defrostEnergyInputRatioFunctionofTemperatureCurve() const;
    bool setDefrostEnergyInputRatioFunctionofTemperatureCurve(const Curve& curve);
    void resetDefrostEnergyInputRatioFunctionofTemperatureCurve();

    boost::optional<Curve> crankcaseHeaterCapacityFunctionofTemperatureCurve() const;
    bool setCrankcaseHeaterCapacityFunctionofTemperatureCurve(const Curve& curve);
    void resetCrankcaseHeaterCapacityFunctionofTemperatureCurve();

    double minimumOutdoorDryBulbTemperatureforCompressorOperation() const;
    bool setMinimumOutdoorDryBulbTemperatureforCompressorOperation(double minimumOutdoorDryBulbTemperatureforCompressorOperation);

    boost::optional<double> outdoorDryBulbTemperaturetoTurnOnCompressor() const;
    bool setOutdoorDryBulbTemperaturetoTurnOnCompressor(double outdoorDryBulbTemperaturetoTurnOnCompressor);
    void resetOutdoorDryBulbTemperaturetoTurnOnCompressor();

    double crankcaseHeaterCapacity() const;
    bool setCrankcaseHeaterCapacity(double crankcaseHeaterCapacity);

    double maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation() const;
    bool setMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation(double maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation);

    double maximumOutdoorDryBulbTemperatureforDefrostOperation() const;
    bool setMaximumOutdoorDryBulbTemperatureforDefrostOperation(double maximumOutdoorDryBulbTemperatureforDefrostOperation);

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

    bool applyPartLoadFractiontoSpeedsGreaterthan1() const;
    bool setApplyPartLoadFractiontoSpeedsGreaterthan1(bool applyPartLoadFractiontoSpeedsGreaterthan1);

    std::string fuelType() const;
    bool setFuelType(const std::string& fuelType);

    int regionnumberforCalculatingHSPF() const;
    bool setRegionnumberforCalculatingHSPF(int regionnumberforCalculatingHSPF);

   protected:
    using ImplType = detail::CoilHeatingDXMultiSpeed_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit CoilHeatingDXMultiSpeed(std::shared_ptr<detail::CoilHeatingDXMultiSpeed_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
