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

    // Schema Alignment Notes:
    // - Status: Parity with documented deltas. The canonical schedule, curve, constructor, autosized-query, and deprecated coefficient alias
    //   surface is preserved here.
    // - Canonical Counterpart: openstudio::model::CoilCoolingWaterToAirHeatPumpEquationFit.
    // - Implemented Parity: `availabilitySchedule`, the three required curve relationships, `partLoadFractionCorrelationCurve`, the canonical
    //   constructors, the deprecated coefficient aliases that delegate through the stored curves, the scalar fit fields, and the autosized-value
    //   query helpers preserve the canonical public contract.
    // - Implemented Parity: the canonical equivalent-duct helper surface lands on epmodel's
    //   `AirflowNetworkDistributionComponentCoil`, which is the EnergyPlus object written by the
    //   model-side `AirflowNetworkEquivalentDuct` translator path for coils.
    // - Field/Storage Mapping: Availability schedule and curve relationships are stored directly on the EnergyPlus
    //   `Coil:Cooling:WaterToAirHeatPump:EquationFit` object, and scalar fit fields map directly to the corresponding EnergyPlus fields.
    // - Evidence: `src/model/CoilCoolingWaterToAirHeatPumpEquationFit.hpp`, `src/model/CoilCoolingWaterToAirHeatPumpEquationFit.cpp`,
    //   `src/energyplus/ForwardTranslator/ForwardTranslateCoilCoolingWaterToAirHeatPumpEquationFit.cpp`, and
    //   `src/epmodel/test/CoilCoolingWaterToAirHeatPumpEquationFit_GTest.cpp`.
    // - Remaining Parity Work: Extend the same AFN mapping surface to the remaining water-to-air heat pump coil family wrappers when that campaign reaches them.
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
