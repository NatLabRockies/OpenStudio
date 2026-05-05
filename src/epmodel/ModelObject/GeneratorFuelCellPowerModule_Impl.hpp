/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GENERATORFUELCELLPOWERMODULE_IMPL_HPP
#define EPMODEL_GENERATORFUELCELLPOWERMODULE_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API GeneratorFuelCellPowerModule_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~GeneratorFuelCellPowerModule_Impl() override = default;

      std::string efficiencyCurveMode() const;
      bool setEfficiencyCurveMode(const std::string& efficiencyCurveMode);
      void resetEfficiencyCurveMode();

      double nominalEfficiency() const;
      bool setNominalEfficiency(double nominalEfficiency);
      void resetNominalEfficiency();

      double nominalElectricalPower() const;
      bool setNominalElectricalPower(double nominalElectricalPower);
      void resetNominalElectricalPower();

      double numberofStopsatStartofSimulation() const;
      bool setNumberofStopsatStartofSimulation(double numberofStopsatStartofSimulation);
      void resetNumberofStopsatStartofSimulation();

      double cyclingPerformanceDegradationCoefficient() const;
      bool setCyclingPerformanceDegradationCoefficient(double cyclingPerformanceDegradationCoefficient);
      void resetCyclingPerformanceDegradationCoefficient();

      double numberofRunHoursatBeginningofSimulation() const;
      bool setNumberofRunHoursatBeginningofSimulation(double numberofRunHoursatBeginningofSimulation);
      void resetNumberofRunHoursatBeginningofSimulation();

      double accumulatedRunTimeDegradationCoefficient() const;
      bool setAccumulatedRunTimeDegradationCoefficient(double accumulatedRunTimeDegradationCoefficient);
      void resetAccumulatedRunTimeDegradationCoefficient();

      double runTimeDegradationInitiationTimeThreshold() const;
      bool setRunTimeDegradationInitiationTimeThreshold(double runTimeDegradationInitiationTimeThreshold);
      void resetRunTimeDegradationInitiationTimeThreshold();

      double powerUpTransientLimit() const;
      bool setPowerUpTransientLimit(double powerUpTransientLimit);
      void resetPowerUpTransientLimit();

      double powerDownTransientLimit() const;
      bool setPowerDownTransientLimit(double powerDownTransientLimit);
      void resetPowerDownTransientLimit();

      double startUpTime() const;
      bool setStartUpTime(double startUpTime);
      void resetStartUpTime();

      double startUpFuel() const;
      bool setStartUpFuel(double startUpFuel);
      void resetStartUpFuel();

      double startUpElectricityConsumption() const;
      bool setStartUpElectricityConsumption(double startUpElectricityConsumption);
      void resetStartUpElectricityConsumption();

      double startUpElectricityProduced() const;
      bool setStartUpElectricityProduced(double startUpElectricityProduced);
      void resetStartUpElectricityProduced();

      double shutDownTime() const;
      bool setShutDownTime(double shutDownTime);
      void resetShutDownTime();

      double shutDownFuel() const;
      bool setShutDownFuel(double shutDownFuel);
      void resetShutDownFuel();

      double shutDownElectricityConsumption() const;
      bool setShutDownElectricityConsumption(double shutDownElectricityConsumption);
      void resetShutDownElectricityConsumption();

      double ancillaryElectricityConstantTerm() const;
      bool setAncillaryElectricityConstantTerm(double ancillaryElectricityConstantTerm);
      void resetAncillaryElectricityConstantTerm();

      double ancillaryElectricityLinearTerm() const;
      bool setAncillaryElectricityLinearTerm(double ancillaryElectricityLinearTerm);
      void resetAncillaryElectricityLinearTerm();

      std::string skinLossCalculationMode() const;
      bool setSkinLossCalculationMode(const std::string& skinLossCalculationMode);
      void resetSkinLossCalculationMode();

      double skinLossRadiativeFraction() const;
      bool setSkinLossRadiativeFraction(double skinLossRadiativeFraction);
      void resetSkinLossRadiativeFraction();

      double constantSkinLossRate() const;
      bool setConstantSkinLossRate(double constantSkinLossRate);
      void resetConstantSkinLossRate();

      double skinLossUFactorTimesAreaTerm() const;
      bool setSkinLossUFactorTimesAreaTerm(double skinLossUFactorTimesAreaTerm);
      void resetSkinLossUFactorTimesAreaTerm();

      double dilutionAirFlowRate() const;
      bool setDilutionAirFlowRate(double dilutionAirFlowRate);
      void resetDilutionAirFlowRate();

      double stackHeatlosstoDilutionAir() const;
      bool setStackHeatlosstoDilutionAir(double stackHeatlosstoDilutionAir);
      void resetStackHeatlosstoDilutionAir();

      double minimumOperatingPoint() const;
      bool setMinimumOperatingPoint(double minimumOperatingPoint);
      void resetMinimumOperatingPoint();

      double maximumOperatingPoint() const;
      bool setMaximumOperatingPoint(double maximumOperatingPoint);
      void resetMaximumOperatingPoint();

      std::vector<std::string> efficiencyCurveModeValues() const;
      std::vector<std::string> skinLossCalculationModeValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
