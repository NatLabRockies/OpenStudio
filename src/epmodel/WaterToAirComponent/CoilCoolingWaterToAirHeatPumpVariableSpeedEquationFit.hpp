/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILCOOLINGWATERTOAIRHEATPUMPVARIABLESPEEDEQUATIONFIT_HPP
#define EPMODEL_COILCOOLINGWATERTOAIRHEATPUMPVARIABLESPEEDEQUATIONFIT_HPP

#include "EPModelAPI.hpp"
#include "WaterToAirComponent.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl;
  }

class EPMODEL_API CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit : public WaterToAirComponent
  {
   public:
    explicit CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit(const Model& model);

    virtual ~CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit() override = default;
    CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit(const CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit& other) = default;
    CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit(CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit&& other) = default;
    CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit& operator=(const CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit&) = default;
    CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit& operator=(CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: Preserves openstudio::model scalar accessor names/signatures for model-counterpart compatibility.
    // - Field Mapping: useHotGasReheat maps to E+ FlagforUsingHotGasReheat0or1 (0/1 integer) in this epmodel schema.
    // - Field Mapping: relationship-like fields (availability schedule, node names, speed data list/extensibles, and curve references) are excluded.
    // - ForwardTranslator evidence: ForwardTranslateCoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit.cpp writes these exact scalar fields and autosize semantics.
    // - TODO(parity): Add relationship APIs when epmodel relationship scaffolding is enabled.
    int nominalSpeedLevel() const;
    bool setNominalSpeedLevel(int nominalSpeedLevel);

    boost::optional<double> grossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel() const;
    bool setGrossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel(double grossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel);
    bool isGrossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevelAutosized() const;
    void autosizeGrossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel();

    boost::optional<double> ratedAirFlowRateAtSelectedNominalSpeedLevel() const;
    bool setRatedAirFlowRateAtSelectedNominalSpeedLevel(double ratedAirFlowRateAtSelectedNominalSpeedLevel);
    bool isRatedAirFlowRateAtSelectedNominalSpeedLevelAutosized() const;
    void autosizeRatedAirFlowRateAtSelectedNominalSpeedLevel();

    boost::optional<double> ratedWaterFlowRateAtSelectedNominalSpeedLevel() const;
    bool setRatedWaterFlowRateAtSelectedNominalSpeedLevel(double ratedWaterFlowRateAtSelectedNominalSpeedLevel);
    bool isRatedWaterFlowRateAtSelectedNominalSpeedLevelAutosized() const;
    void autosizeRatedWaterFlowRateAtSelectedNominalSpeedLevel();

    double nominalTimeforCondensatetoBeginLeavingtheCoil() const;
    bool setNominalTimeforCondensatetoBeginLeavingtheCoil(double nominalTimeforCondensatetoBeginLeavingtheCoil);

    double initialMoistureEvaporationRateDividedbySteadyStateACLatentCapacity() const;
    bool setInitialMoistureEvaporationRateDividedbySteadyStateACLatentCapacity(
      double initialMoistureEvaporationRateDividedbySteadyStateACLatentCapacity);

    double maximumCyclingRate() const;
    bool setMaximumCyclingRate(double maximumCyclingRate);

    double latentCapacityTimeConstant() const;
    bool setLatentCapacityTimeConstant(double latentCapacityTimeConstant);

    double fanDelayTime() const;
    bool setFanDelayTime(double fanDelayTime);

    bool useHotGasReheat() const;
    bool setUseHotGasReheat(bool useHotGasReheat);

   protected:
    using ImplType = detail::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit(
      std::shared_ptr<detail::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
