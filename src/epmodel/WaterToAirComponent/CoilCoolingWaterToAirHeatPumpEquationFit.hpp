/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILCOOLINGWATERTOAIRHEATPUMPEQUATIONFIT_HPP
#define EPMODEL_COILCOOLINGWATERTOAIRHEATPUMPEQUATIONFIT_HPP

#include "EPModelAPI.hpp"
#include "WaterToAirComponent.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class CoilCoolingWaterToAirHeatPumpEquationFit_Impl;
  }

  class EPMODEL_API CoilCoolingWaterToAirHeatPumpEquationFit : public WaterToAirComponent
  {
   public:
    explicit CoilCoolingWaterToAirHeatPumpEquationFit(const Model& model);

    virtual ~CoilCoolingWaterToAirHeatPumpEquationFit() override = default;
    CoilCoolingWaterToAirHeatPumpEquationFit(const CoilCoolingWaterToAirHeatPumpEquationFit& other) = default;
    CoilCoolingWaterToAirHeatPumpEquationFit(CoilCoolingWaterToAirHeatPumpEquationFit&& other) = default;
    CoilCoolingWaterToAirHeatPumpEquationFit& operator=(const CoilCoolingWaterToAirHeatPumpEquationFit&) = default;
    CoilCoolingWaterToAirHeatPumpEquationFit& operator=(CoilCoolingWaterToAirHeatPumpEquationFit&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - Status: Scalar Parity. The scalar fit fields and autosize semantics are aligned, while the curve/schedule/duct surface remains intentionally omitted.
    // - Canonical Counterpart: openstudio::model::CoilCoolingWaterToAirHeatPumpEquationFit.
    // - Implemented Parity: `ratedAirFlowRate`, `ratedWaterFlowRate`, `ratedTotalCoolingCapacity`, `ratedSensibleCoolingCapacity`, `ratedCoolingCoefficientofPerformance`, `ratedEnteringWaterTemperature`, `ratedEnteringAirDryBulbTemperature`, `ratedEnteringAirWetBulbTemperature`, `nominalTimeforCondensateRemovaltoBegin`, `ratioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity`, `maximumCyclingRate`, `latentCapacityTimeConstant`, `fanDelayTime`, and the autosize/reset helpers preserve the canonical scalar contract.
    // - Documented Delta: Availability schedule, curve objects, and equivalent-duct helpers are not exposed here even though the canonical model type owns them.
    // - Field/Storage Mapping: Scalar fit fields map directly to the corresponding EnergyPlus `Coil:Cooling:WaterToAirHeatPump:EquationFit` fields.
    // - Evidence: `src/model/CoilCoolingWaterToAirHeatPumpEquationFit.hpp`, `src/model/CoilCoolingWaterToAirHeatPumpEquationFit.cpp`, `src/energyplus/ForwardTranslator/ForwardTranslateCoilCoolingWaterToAirHeatPumpEquationFit.cpp`, and `src/epmodel/test/CoilCoolingWaterToAirHeatPumpEquationFit_GTest.cpp`.
    // - Remaining Parity Work: Add the omitted curve, schedule, and helper APIs only if the family moves beyond scalar parity.
    boost::optional<double> ratedAirFlowRate() const;
    bool isRatedAirFlowRateDefaulted() const;
    bool isRatedAirFlowRateAutosized() const;
    bool setRatedAirFlowRate(double ratedAirFlowRate);
    void resetRatedAirFlowRate();
    void autosizeRatedAirFlowRate();

    boost::optional<double> ratedWaterFlowRate() const;
    bool isRatedWaterFlowRateDefaulted() const;
    bool isRatedWaterFlowRateAutosized() const;
    bool setRatedWaterFlowRate(double ratedWaterFlowRate);
    void resetRatedWaterFlowRate();
    void autosizeRatedWaterFlowRate();

    boost::optional<double> ratedTotalCoolingCapacity() const;
    bool isRatedTotalCoolingCapacityDefaulted() const;
    bool isRatedTotalCoolingCapacityAutosized() const;
    bool setRatedTotalCoolingCapacity(double ratedTotalCoolingCapacity);
    void resetRatedTotalCoolingCapacity();
    void autosizeRatedTotalCoolingCapacity();

    boost::optional<double> ratedSensibleCoolingCapacity() const;
    bool isRatedSensibleCoolingCapacityDefaulted() const;
    bool isRatedSensibleCoolingCapacityAutosized() const;
    bool setRatedSensibleCoolingCapacity(double ratedSensibleCoolingCapacity);
    void resetRatedSensibleCoolingCapacity();
    void autosizeRatedSensibleCoolingCapacity();

    double ratedCoolingCoefficientofPerformance() const;
    bool isRatedCoolingCoefficientofPerformanceDefaulted() const;
    bool setRatedCoolingCoefficientofPerformance(double ratedCoolingCoefficientofPerformance);

    double ratedEnteringWaterTemperature() const;
    bool setRatedEnteringWaterTemperature(double ratedEnteringWaterTemperature);

    double ratedEnteringAirDryBulbTemperature() const;
    bool setRatedEnteringAirDryBulbTemperature(double ratedEnteringAirDryBulbTemperature);

    double ratedEnteringAirWetBulbTemperature() const;
    bool setRatedEnteringAirWetBulbTemperature(double ratedEnteringAirWetBulbTemperature);

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
