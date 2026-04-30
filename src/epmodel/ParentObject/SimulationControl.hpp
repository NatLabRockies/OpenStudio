/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SIMULATIONCONTROL_HPP
#define EPMODEL_SIMULATIONCONTROL_HPP

#include "EPModelAPI.hpp"
#include "ParentObject/ParentObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class SimulationControl_Impl;
}

class EPMODEL_API SimulationControl : public ParentObject
{
 public:
  static constexpr bool is_unique = true;  // This is a Unique ModelObject

  explicit SimulationControl(const Model& model);

  virtual ~SimulationControl() override = default;
  SimulationControl(const SimulationControl& other) = default;
  SimulationControl(SimulationControl&& other) = default;
  SimulationControl& operator=(const SimulationControl&) = default;
  SimulationControl& operator=(SimulationControl&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: Preserve openstudio::model::SimulationControl scalar accessor names/signatures for SimulationControl fields.
  // - Field Mapping: do*/run*/HVAC sizing-pass APIs map directly to EnergyPlus SimulationControl fields.
  // - Field Mapping: loadsConvergenceToleranceValue, temperatureConvergenceToleranceValue, solarDistribution,
  //   maximumNumberofWarmupDays, and minimumNumberofWarmupDays are translated via EnergyPlus Building and are
  //   intentionally excluded from this class's scalar API.
  // - ForwardTranslator evidence: ForwardTranslateSimulationControl.cpp writes the retained SimulationControl fields;
  //   ForwardTranslateBuilding.cpp maps the excluded fields from model::SimulationControl to Building.
  // - TODO(parity): Revisit cross-object parity for excluded Building-mapped SimulationControl APIs after scalar saturation.
  bool doZoneSizingCalculation() const;
  bool isDoZoneSizingCalculationDefaulted() const;
  bool setDoZoneSizingCalculation(bool doZoneSizingCalculation);
  void setDoZoneSizingCalculationNoFail(bool doZoneSizingCalculation);
  void resetDoZoneSizingCalculation();

  bool doSystemSizingCalculation() const;
  bool isDoSystemSizingCalculationDefaulted() const;
  bool setDoSystemSizingCalculation(bool doSystemSizingCalculation);
  void setDoSystemSizingCalculationNoFail(bool doSystemSizingCalculation);
  void resetDoSystemSizingCalculation();

  bool doPlantSizingCalculation() const;
  bool isDoPlantSizingCalculationDefaulted() const;
  bool setDoPlantSizingCalculation(bool doPlantSizingCalculation);
  void setDoPlantSizingCalculationNoFail(bool doPlantSizingCalculation);
  void resetDoPlantSizingCalculation();

  bool runSimulationforSizingPeriods() const;
  bool isRunSimulationforSizingPeriodsDefaulted() const;
  bool setRunSimulationforSizingPeriods(bool runSimulationforSizingPeriods);
  void setRunSimulationforSizingPeriodsNoFail(bool runSimulationforSizingPeriods);
  void resetRunSimulationforSizingPeriods();

  bool runSimulationforWeatherFileRunPeriods() const;
  bool isRunSimulationforWeatherFileRunPeriodsDefaulted() const;
  bool setRunSimulationforWeatherFileRunPeriods(bool runSimulationforWeatherFileRunPeriods);
  void setRunSimulationforWeatherFileRunPeriodsNoFail(bool runSimulationforWeatherFileRunPeriods);
  void resetRunSimulationforWeatherFileRunPeriods();

  bool doHVACSizingSimulationforSizingPeriods() const;
  bool isDoHVACSizingSimulationforSizingPeriodsDefaulted() const;
  bool setDoHVACSizingSimulationforSizingPeriods(bool doHVACSizingSimulationforSizingPeriods);
  void setDoHVACSizingSimulationforSizingPeriodsNoFail(bool doHVACSizingSimulationforSizingPeriods);
  void resetDoHVACSizingSimulationforSizingPeriods();

  int maximumNumberofHVACSizingSimulationPasses() const;
  bool isMaximumNumberofHVACSizingSimulationPassesDefaulted() const;
  bool setMaximumNumberofHVACSizingSimulationPasses(int maximumNumberofHVACSizingSimulationPasses);
  void resetMaximumNumberofHVACSizingSimulationPasses();

 protected:
  using ImplType = detail::SimulationControl_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit SimulationControl(std::shared_ptr<detail::SimulationControl_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
