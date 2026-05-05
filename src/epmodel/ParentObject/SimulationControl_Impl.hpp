/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SIMULATIONCONTROL_IMPL_HPP
#define EPMODEL_SIMULATIONCONTROL_IMPL_HPP

#include "ParentObject/ParentObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API SimulationControl_Impl : public ParentObject_Impl
    {
     public:
      using ParentObject_Impl::ParentObject_Impl;
      virtual ~SimulationControl_Impl() override = default;

      bool doZoneSizingCalculation() const;
      bool isDoZoneSizingCalculationDefaulted() const;
      bool setDoZoneSizingCalculation(bool doZoneSizingCalculation);
      void resetDoZoneSizingCalculation();

      bool doSystemSizingCalculation() const;
      bool isDoSystemSizingCalculationDefaulted() const;
      bool setDoSystemSizingCalculation(bool doSystemSizingCalculation);
      void resetDoSystemSizingCalculation();

      bool doPlantSizingCalculation() const;
      bool isDoPlantSizingCalculationDefaulted() const;
      bool setDoPlantSizingCalculation(bool doPlantSizingCalculation);
      void resetDoPlantSizingCalculation();

      bool runSimulationforSizingPeriods() const;
      bool isRunSimulationforSizingPeriodsDefaulted() const;
      bool setRunSimulationforSizingPeriods(bool runSimulationforSizingPeriods);
      void resetRunSimulationforSizingPeriods();

      bool runSimulationforWeatherFileRunPeriods() const;
      bool isRunSimulationforWeatherFileRunPeriodsDefaulted() const;
      bool setRunSimulationforWeatherFileRunPeriods(bool runSimulationforWeatherFileRunPeriods);
      void resetRunSimulationforWeatherFileRunPeriods();

      bool doHVACSizingSimulationforSizingPeriods() const;
      bool isDoHVACSizingSimulationforSizingPeriodsDefaulted() const;
      bool setDoHVACSizingSimulationforSizingPeriods(bool doHVACSizingSimulationforSizingPeriods);
      void resetDoHVACSizingSimulationforSizingPeriods();

      int maximumNumberofHVACSizingSimulationPasses() const;
      bool isMaximumNumberofHVACSizingSimulationPassesDefaulted() const;
      bool setMaximumNumberofHVACSizingSimulationPasses(int maximumNumberofHVACSizingSimulationPasses);
      void resetMaximumNumberofHVACSizingSimulationPasses();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
