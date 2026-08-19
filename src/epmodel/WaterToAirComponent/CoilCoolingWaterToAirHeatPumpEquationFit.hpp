/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILCOOLINGWATERTOAIRHEATPUMPEQUATIONFIT_HPP
#define EPMODEL_COILCOOLINGWATERTOAIRHEATPUMPEQUATIONFIT_HPP

#include "EPModelAPI.hpp"
#include "WaterToAirComponent.hpp"

#include <utilities/core/Deprecated.hpp>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;
  class Schedule;
  class Curve;
  class AirflowNetworkDistributionComponentCoil;

  namespace detail {
    class CoilCoolingWaterToAirHeatPumpEquationFit_Impl;
  }

  /** \brief Represents a water-to-air cooling heat-pump coil using equation-fit curves.
   *
   * \par EnergyPlus object
   * \epobject{group-heating-and-cooling-coils.html#coilcoolingwatertoairheatpumpequationfit,Coil:Cooling:WaterToAirHeatPump:EquationFit}
   *
   * \par Important behavior
   * The availability schedule and required performance curves are stored as
   * EnergyPlus object-list relationships. Autosized-value queries are exposed
   * for API compatibility but currently return no value because EPModel does
   * not read SQL sizing results.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::CoilCoolingWaterToAirHeatPumpEquationFit</code>.
   *
   * - <b>Changed:</b> The airflow-network equivalent-duct methods use
   *   <code>AirflowNetworkDistributionComponentCoil</code> instead of
   *   Model's <code>AirflowNetworkEquivalentDuct</code>.
   *
   * \par Known limitations
   * Autosized values remain unavailable until EPModel gains SQL-backed sizing
   * result lookup.
   */
  class EPMODEL_API CoilCoolingWaterToAirHeatPumpEquationFit : public WaterToAirComponent
  {
   public:
    CoilCoolingWaterToAirHeatPumpEquationFit(const Model& model, const Curve& totalCoolingCapacityCurve, const Curve& sensibleCoolingCapacityCurve,
                                             const Curve& coolingPowerConsumptionCurve);
    explicit CoilCoolingWaterToAirHeatPumpEquationFit(const Model& model);

    virtual ~CoilCoolingWaterToAirHeatPumpEquationFit() override = default;
    CoilCoolingWaterToAirHeatPumpEquationFit(const CoilCoolingWaterToAirHeatPumpEquationFit& other) = default;
    CoilCoolingWaterToAirHeatPumpEquationFit(CoilCoolingWaterToAirHeatPumpEquationFit&& other) = default;
    CoilCoolingWaterToAirHeatPumpEquationFit& operator=(const CoilCoolingWaterToAirHeatPumpEquationFit&) = default;
    CoilCoolingWaterToAirHeatPumpEquationFit& operator=(CoilCoolingWaterToAirHeatPumpEquationFit&&) = default;

    static IddObjectType iddObjectType();

    Schedule availabilitySchedule() const;
    bool setAvailabilitySchedule(Schedule& schedule);

    boost::optional<double> ratedAirFlowRate() const;
    bool isRatedAirFlowRateDefaulted() const;
    bool isRatedAirFlowRateAutosized() const;
    bool setRatedAirFlowRate(double ratedAirFlowRate);
    void resetRatedAirFlowRate();
    void autosizeRatedAirFlowRate();
    boost::optional<double> autosizedRatedAirFlowRate() const;

    boost::optional<double> ratedWaterFlowRate() const;
    bool isRatedWaterFlowRateDefaulted() const;
    bool isRatedWaterFlowRateAutosized() const;
    bool setRatedWaterFlowRate(double ratedWaterFlowRate);
    void resetRatedWaterFlowRate();
    void autosizeRatedWaterFlowRate();
    boost::optional<double> autosizedRatedWaterFlowRate() const;

    boost::optional<double> ratedTotalCoolingCapacity() const;
    bool isRatedTotalCoolingCapacityDefaulted() const;
    bool isRatedTotalCoolingCapacityAutosized() const;
    bool setRatedTotalCoolingCapacity(double ratedTotalCoolingCapacity);
    void resetRatedTotalCoolingCapacity();
    void autosizeRatedTotalCoolingCapacity();
    boost::optional<double> autosizedRatedTotalCoolingCapacity() const;

    boost::optional<double> ratedSensibleCoolingCapacity() const;
    bool isRatedSensibleCoolingCapacityDefaulted() const;
    bool isRatedSensibleCoolingCapacityAutosized() const;
    bool setRatedSensibleCoolingCapacity(double ratedSensibleCoolingCapacity);
    void resetRatedSensibleCoolingCapacity();
    void autosizeRatedSensibleCoolingCapacity();
    boost::optional<double> autosizedRatedSensibleCoolingCapacity() const;

    double ratedCoolingCoefficientofPerformance() const;
    bool isRatedCoolingCoefficientofPerformanceDefaulted() const;
    bool setRatedCoolingCoefficientofPerformance(double ratedCoolingCoefficientofPerformance);

    double ratedEnteringWaterTemperature() const;
    bool setRatedEnteringWaterTemperature(double ratedEnteringWaterTemperature);

    double ratedEnteringAirDryBulbTemperature() const;
    bool setRatedEnteringAirDryBulbTemperature(double ratedEnteringAirDryBulbTemperature);

    double ratedEnteringAirWetBulbTemperature() const;
    bool setRatedEnteringAirWetBulbTemperature(double ratedEnteringAirWetBulbTemperature);

    Curve totalCoolingCapacityCurve() const;
    bool setTotalCoolingCapacityCurve(const Curve& totalCoolingCapacityCurve);
    OS_DEPRECATED(3, 2, 0) double totalCoolingCapacityCoefficient1() const;
    OS_DEPRECATED(3, 2, 0) bool setTotalCoolingCapacityCoefficient1(double totalCoolingCapacityCoefficient1);
    OS_DEPRECATED(3, 2, 0) double totalCoolingCapacityCoefficient2() const;
    OS_DEPRECATED(3, 2, 0) bool setTotalCoolingCapacityCoefficient2(double totalCoolingCapacityCoefficient2);
    OS_DEPRECATED(3, 2, 0) double totalCoolingCapacityCoefficient3() const;
    OS_DEPRECATED(3, 2, 0) bool setTotalCoolingCapacityCoefficient3(double totalCoolingCapacityCoefficient3);
    OS_DEPRECATED(3, 2, 0) double totalCoolingCapacityCoefficient4() const;
    OS_DEPRECATED(3, 2, 0) bool setTotalCoolingCapacityCoefficient4(double totalCoolingCapacityCoefficient4);
    OS_DEPRECATED(3, 2, 0) double totalCoolingCapacityCoefficient5() const;
    OS_DEPRECATED(3, 2, 0) bool setTotalCoolingCapacityCoefficient5(double totalCoolingCapacityCoefficient5);

    Curve sensibleCoolingCapacityCurve() const;
    bool setSensibleCoolingCapacityCurve(const Curve& sensibleCoolingCapacityCurve);
    OS_DEPRECATED(3, 2, 0) double sensibleCoolingCapacityCoefficient1() const;
    OS_DEPRECATED(3, 2, 0) bool setSensibleCoolingCapacityCoefficient1(double sensibleCoolingCapacityCoefficient1);
    OS_DEPRECATED(3, 2, 0) double sensibleCoolingCapacityCoefficient2() const;
    OS_DEPRECATED(3, 2, 0) bool setSensibleCoolingCapacityCoefficient2(double sensibleCoolingCapacityCoefficient2);
    OS_DEPRECATED(3, 2, 0) double sensibleCoolingCapacityCoefficient3() const;
    OS_DEPRECATED(3, 2, 0) bool setSensibleCoolingCapacityCoefficient3(double sensibleCoolingCapacityCoefficient3);
    OS_DEPRECATED(3, 2, 0) double sensibleCoolingCapacityCoefficient4() const;
    OS_DEPRECATED(3, 2, 0) bool setSensibleCoolingCapacityCoefficient4(double sensibleCoolingCapacityCoefficient4);
    OS_DEPRECATED(3, 2, 0) double sensibleCoolingCapacityCoefficient5() const;
    OS_DEPRECATED(3, 2, 0) bool setSensibleCoolingCapacityCoefficient5(double sensibleCoolingCapacityCoefficient5);
    OS_DEPRECATED(3, 2, 0) double sensibleCoolingCapacityCoefficient6() const;
    OS_DEPRECATED(3, 2, 0) bool setSensibleCoolingCapacityCoefficient6(double sensibleCoolingCapacityCoefficient6);

    Curve coolingPowerConsumptionCurve() const;
    bool setCoolingPowerConsumptionCurve(const Curve& coolingPowerConsumptionCurve);
    OS_DEPRECATED(3, 2, 0) double coolingPowerConsumptionCoefficient1() const;
    OS_DEPRECATED(3, 2, 0) bool setCoolingPowerConsumptionCoefficient1(double coolingPowerConsumptionCoefficient1);
    OS_DEPRECATED(3, 2, 0) double coolingPowerConsumptionCoefficient2() const;
    OS_DEPRECATED(3, 2, 0) bool setCoolingPowerConsumptionCoefficient2(double coolingPowerConsumptionCoefficient2);
    OS_DEPRECATED(3, 2, 0) double coolingPowerConsumptionCoefficient3() const;
    OS_DEPRECATED(3, 2, 0) bool setCoolingPowerConsumptionCoefficient3(double coolingPowerConsumptionCoefficient3);
    OS_DEPRECATED(3, 2, 0) double coolingPowerConsumptionCoefficient4() const;
    OS_DEPRECATED(3, 2, 0) bool setCoolingPowerConsumptionCoefficient4(double coolingPowerConsumptionCoefficient4);
    OS_DEPRECATED(3, 2, 0) double coolingPowerConsumptionCoefficient5() const;
    OS_DEPRECATED(3, 2, 0) bool setCoolingPowerConsumptionCoefficient5(double coolingPowerConsumptionCoefficient5);

    Curve partLoadFractionCorrelationCurve() const;
    bool setPartLoadFractionCorrelationCurve(const Curve& partLoadFractionCorrelationCurve);

    double nominalTimeforCondensateRemovaltoBegin() const;
    bool isNominalTimeforCondensateRemovaltoBeginDefaulted() const;
    bool setNominalTimeforCondensateRemovaltoBegin(double nominalTimeforCondensateRemovaltoBegin);
    void resetNominalTimeforCondensateRemovaltoBegin();

    double ratioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity() const;
    bool isRatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacityDefaulted() const;
    bool
      setRatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity(double ratioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity);
    void resetRatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity();

    double maximumCyclingRate() const;
    bool setMaximumCyclingRate(double maximumCyclingRate);

    double latentCapacityTimeConstant() const;
    bool setLatentCapacityTimeConstant(double latentCapacityTimeConstant);

    double fanDelayTime() const;
    bool setFanDelayTime(double fanDelayTime);

    AirflowNetworkDistributionComponentCoil getAirflowNetworkEquivalentDuct(double length, double diameter);
    boost::optional<AirflowNetworkDistributionComponentCoil> airflowNetworkEquivalentDuct() const;

   protected:
    using ImplType = detail::CoilCoolingWaterToAirHeatPumpEquationFit_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit CoilCoolingWaterToAirHeatPumpEquationFit(std::shared_ptr<detail::CoilCoolingWaterToAirHeatPumpEquationFit_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
