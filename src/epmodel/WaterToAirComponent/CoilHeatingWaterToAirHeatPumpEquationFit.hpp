/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILHEATINGWATERTOAIRHEATPUMPEQUATIONFIT_HPP
#define EPMODEL_COILHEATINGWATERTOAIRHEATPUMPEQUATIONFIT_HPP

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
    class CoilHeatingWaterToAirHeatPumpEquationFit_Impl;
  }

  /** \brief Represents a water-to-air heating heat-pump coil using equation-fit curves.
   *
   * \par EnergyPlus object
   * \epobject{group-heating-and-cooling-coils.html#coilheatingwatertoairheatpumpequationfit,Coil:Heating:WaterToAirHeatPump:EquationFit}
   *
   * \par Important behavior
   * The availability schedule and required performance curves are stored as
   * EnergyPlus object-list relationships. Autosized-value queries are exposed
   * for API compatibility but currently return no value because EPModel does
   * not read SQL sizing results.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::CoilHeatingWaterToAirHeatPumpEquationFit</code>.
   *
   * - <b>Changed:</b> The airflow-network equivalent-duct methods use
   *   <code>AirflowNetworkDistributionComponentCoil</code> instead of
   *   Model's <code>AirflowNetworkEquivalentDuct</code>.
   *
   * \par Known limitations
   * Autosized values remain unavailable until EPModel gains SQL-backed sizing
   * result lookup.
   */
  class EPMODEL_API CoilHeatingWaterToAirHeatPumpEquationFit : public WaterToAirComponent
  {
   public:
    CoilHeatingWaterToAirHeatPumpEquationFit(const Model& model, const Curve& heatingCapacityCurve, const Curve& heatingPowerConsumptionCurve);
    explicit CoilHeatingWaterToAirHeatPumpEquationFit(const Model& model);

    virtual ~CoilHeatingWaterToAirHeatPumpEquationFit() override = default;
    CoilHeatingWaterToAirHeatPumpEquationFit(const CoilHeatingWaterToAirHeatPumpEquationFit& other) = default;
    CoilHeatingWaterToAirHeatPumpEquationFit(CoilHeatingWaterToAirHeatPumpEquationFit&& other) = default;
    CoilHeatingWaterToAirHeatPumpEquationFit& operator=(const CoilHeatingWaterToAirHeatPumpEquationFit&) = default;
    CoilHeatingWaterToAirHeatPumpEquationFit& operator=(CoilHeatingWaterToAirHeatPumpEquationFit&&) = default;

    static IddObjectType iddObjectType();

    Schedule availabilitySchedule() const;
    bool setAvailabilitySchedule(Schedule& schedule);

    boost::optional<double> ratedAirFlowRate() const;
    bool isRatedAirFlowRateDefaulted() const;
    bool isRatedAirFlowRateAutosized() const;
    bool setRatedAirFlowRate(boost::optional<double> ratedAirFlowRate);
    bool setRatedAirFlowRate(double ratedAirFlowRate);
    void resetRatedAirFlowRate();
    void autosizeRatedAirFlowRate();
    boost::optional<double> autosizedRatedAirFlowRate() const;

    boost::optional<double> ratedWaterFlowRate() const;
    bool isRatedWaterFlowRateDefaulted() const;
    bool isRatedWaterFlowRateAutosized() const;
    bool setRatedWaterFlowRate(boost::optional<double> ratedWaterFlowRate);
    bool setRatedWaterFlowRate(double ratedWaterFlowRate);
    void resetRatedWaterFlowRate();
    void autosizeRatedWaterFlowRate();
    boost::optional<double> autosizedRatedWaterFlowRate() const;

    boost::optional<double> ratedHeatingCapacity() const;
    bool isRatedHeatingCapacityDefaulted() const;
    bool isRatedHeatingCapacityAutosized() const;
    bool setRatedHeatingCapacity(boost::optional<double> ratedHeatingCapacity);
    bool setRatedHeatingCapacity(double ratedHeatingCapacity);
    void resetRatedHeatingCapacity();
    void autosizeRatedHeatingCapacity();
    boost::optional<double> autosizedRatedHeatingCapacity() const;

    double ratedHeatingCoefficientofPerformance() const;
    bool isRatedHeatingCoefficientofPerformanceDefaulted() const;
    bool setRatedHeatingCoefficientofPerformance(double ratedHeatingCoefficientofPerformance);
    void resetRatedHeatingCoefficientofPerformance();

    double ratedEnteringWaterTemperature() const;
    bool setRatedEnteringWaterTemperature(double ratedEnteringWaterTemperature);

    double ratedEnteringAirDryBulbTemperature() const;
    bool setRatedEnteringAirDryBulbTemperature(double ratedEnteringAirDryBulbTemperature);

    Curve heatingCapacityCurve() const;
    bool setHeatingCapacityCurve(const Curve& heatingCapacityCurve);
    OS_DEPRECATED(3, 2, 0) double heatingCapacityCoefficient1() const;
    OS_DEPRECATED(3, 2, 0) bool setHeatingCapacityCoefficient1(double heatingCapacityCoefficient1);
    OS_DEPRECATED(3, 2, 0) double heatingCapacityCoefficient2() const;
    OS_DEPRECATED(3, 2, 0) bool setHeatingCapacityCoefficient2(double heatingCapacityCoefficient2);
    OS_DEPRECATED(3, 2, 0) double heatingCapacityCoefficient3() const;
    OS_DEPRECATED(3, 2, 0) bool setHeatingCapacityCoefficient3(double heatingCapacityCoefficient3);
    OS_DEPRECATED(3, 2, 0) double heatingCapacityCoefficient4() const;
    OS_DEPRECATED(3, 2, 0) bool setHeatingCapacityCoefficient4(double heatingCapacityCoefficient4);
    OS_DEPRECATED(3, 2, 0) double heatingCapacityCoefficient5() const;
    OS_DEPRECATED(3, 2, 0) bool setHeatingCapacityCoefficient5(double heatingCapacityCoefficient5);

    Curve heatingPowerConsumptionCurve() const;
    bool setHeatingPowerConsumptionCurve(const Curve& heatingPowerConsumptionCurve);
    OS_DEPRECATED(3, 2, 0) double heatingPowerConsumptionCoefficient1() const;
    OS_DEPRECATED(3, 2, 0) bool setHeatingPowerConsumptionCoefficient1(double heatingPowerConsumptionCoefficient1);
    OS_DEPRECATED(3, 2, 0) double heatingPowerConsumptionCoefficient2() const;
    OS_DEPRECATED(3, 2, 0) bool setHeatingPowerConsumptionCoefficient2(double heatingPowerConsumptionCoefficient2);
    OS_DEPRECATED(3, 2, 0) double heatingPowerConsumptionCoefficient3() const;
    OS_DEPRECATED(3, 2, 0) bool setHeatingPowerConsumptionCoefficient3(double heatingPowerConsumptionCoefficient3);
    OS_DEPRECATED(3, 2, 0) double heatingPowerConsumptionCoefficient4() const;
    OS_DEPRECATED(3, 2, 0) bool setHeatingPowerConsumptionCoefficient4(double heatingPowerConsumptionCoefficient4);
    OS_DEPRECATED(3, 2, 0) double heatingPowerConsumptionCoefficient5() const;
    OS_DEPRECATED(3, 2, 0) bool setHeatingPowerConsumptionCoefficient5(double heatingPowerConsumptionCoefficient5);

    Curve partLoadFractionCorrelationCurve() const;
    bool setPartLoadFractionCorrelationCurve(const Curve& partLoadFractionCorrelationCurve);

    double ratioofRatedHeatingCapacitytoRatedCoolingCapacity() const;
    bool setRatioofRatedHeatingCapacitytoRatedCoolingCapacity(double ratioofRatedHeatingCapacitytoRatedCoolingCapacity);

    AirflowNetworkDistributionComponentCoil getAirflowNetworkEquivalentDuct(double length, double diameter);
    boost::optional<AirflowNetworkDistributionComponentCoil> airflowNetworkEquivalentDuct() const;

   protected:
    using ImplType = detail::CoilHeatingWaterToAirHeatPumpEquationFit_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit CoilHeatingWaterToAirHeatPumpEquationFit(std::shared_ptr<detail::CoilHeatingWaterToAirHeatPumpEquationFit_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
