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

/** \brief Controls which EnergyPlus sizing and simulation phases are run.
 *
 * \par EnergyPlus object
 * \epobject{group-simulation-parameters.html#simulationcontrol,SimulationControl}
 *
 * \par Important behavior
 * Zone, system, plant, HVAC-sizing, weather-run-period, and warmup/pass-limit controls map directly to the simulation-control object. The no-fail setters preserve requested values without normal validation.
 *
 * \par OpenStudio Model API
 * The corresponding OpenStudio Model class is <code>openstudio::model::SimulationControl</code>.
 * <b>Not yet available:</b> Model's run-period/environment collections, convergence limits, heat-balance and surface-convection algorithms, timestep, shadow, contaminant, and solar-distribution relationships are not exposed.
 *
 * \par Known limitations
 * This wrapper selects simulation phases but does not run EnergyPlus or inspect simulation results.
 */
  class EPMODEL_API SimulationControl : public ParentObject
  {
   public:
    static constexpr bool is_unique = true;  // This is a Unique ModelObject

    virtual ~SimulationControl() override = default;
    SimulationControl(const SimulationControl& other) = default;
    SimulationControl(SimulationControl&& other) = default;
    SimulationControl& operator=(const SimulationControl&) = default;
    SimulationControl& operator=(SimulationControl&&) = default;

    static IddObjectType iddObjectType();

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

    int maximumNumberofWarmupDays() const;
    bool isMaximumNumberofWarmupDaysDefaulted() const;
    bool setMaximumNumberofWarmupDays(int maximumNumberofWarmupDays);
    void resetMaximumNumberofWarmupDays();

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
    explicit SimulationControl(const Model& model);

    using ImplType = detail::SimulationControl_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SimulationControl(std::shared_ptr<detail::SimulationControl_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
