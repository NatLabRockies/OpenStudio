/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILWATERHEATINGDESUPERHEATER_HPP
#define EPMODEL_COILWATERHEATINGDESUPERHEATER_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;
  class Node;
  class Schedule;
  class CurveBiquadratic;
  class ModelObject;

  namespace detail {
    class CoilWaterHeatingDesuperheater_Impl;
  }

  class EPMODEL_API CoilWaterHeatingDesuperheater : public StraightComponent
  {
   public:
    /** EnergyPlus-compatible construction. The object remains structurally incomplete until a setpoint temperature schedule is supplied. */
    explicit CoilWaterHeatingDesuperheater(const Model& model);
    explicit CoilWaterHeatingDesuperheater(const Model& model, Schedule& setpointTemperatureSchedule);

    virtual ~CoilWaterHeatingDesuperheater() override = default;
    CoilWaterHeatingDesuperheater(const CoilWaterHeatingDesuperheater& other) = default;
    CoilWaterHeatingDesuperheater(CoilWaterHeatingDesuperheater&& other) = default;
    CoilWaterHeatingDesuperheater& operator=(const CoilWaterHeatingDesuperheater&) = default;
    CoilWaterHeatingDesuperheater& operator=(CoilWaterHeatingDesuperheater&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - Status: Partial Parity. The canonical scalar and schedule surfaces plus the bounded relationship slice are present, while tank-link and
    //   broader node-link helpers remain out of scope.
    // - Canonical Counterpart: openstudio::model::CoilWaterHeatingDesuperheater.
    // - Implemented Parity: The canonical constructor accepts the required setpoint temperature schedule. Availability and setpoint relationships
    //   enforce their canonical schedule types, and canonicalization repairs blank availability while preserving malformed nonblank evidence. The
    //   dead-band, heat-reclaim, water-flow, pump-power, parasitic-load, curve, heating-source, child-traversal, and `addToNode(...)` surfaces remain.
    // - Documented Delta: The one-argument constructor remains for direct EnergyPlus compatibility, where blank availability is valid, but its result
    //   is structurally incomplete until `setSetpointTemperatureSchedule(...)` succeeds. Tank-link helpers remain out of scope.
    // - Field/Storage Mapping: `availabilitySchedule()` maps to A2 and `setpointTemperatureSchedule()` maps to required A3. Preserved scalars and other
    //   relationships map directly to EnergyPlus `Coil:WaterHeating:Desuperheater` fields. There is intentionally no setpoint reset API.
    // - Canonicalization: Ordinary getters are observational and assume managed schedule pointers. Repair attaches always-on only for truly blank
    //   availability, reattaches unique eligible persisted names through validated setters, never invents a setpoint schedule, and preserves and
    //   reports unresolved, ambiguous, or incompatible nonblank evidence.
    // - Evidence: `src/model/CoilWaterHeatingDesuperheater.hpp`, `src/energyplus/ForwardTranslator/ForwardTranslateCoilWaterHeatingDesuperheater.cpp`, and `src/epmodel/test/CoilWaterHeatingDesuperheater_GTest.cpp`.
    // - Remaining Parity Work: Add the omitted tank-link and broader relationship helpers without changing the preserved public signatures.

    Schedule availabilitySchedule() const;
    bool setAvailabilitySchedule(Schedule& schedule);
    void resetAvailabilitySchedule();

    Schedule setpointTemperatureSchedule() const;
    bool setSetpointTemperatureSchedule(Schedule& schedule);

    boost::optional<CurveBiquadratic> heatReclaimEfficiencyFunctionofTemperatureCurve() const;
    bool setHeatReclaimEfficiencyFunctionofTemperatureCurve(const CurveBiquadratic& curveBiquadratic);
    void resetHeatReclaimEfficiencyFunctionofTemperatureCurve();

    boost::optional<ModelObject> heatingSource() const;
    bool setHeatingSource(const ModelObject& heatingSource);
    void resetHeatingSource();

    bool addToNode(Node& node);

    double deadBandTemperatureDifference() const;
    bool isDeadBandTemperatureDifferenceDefaulted() const;
    bool setDeadBandTemperatureDifference(double deadBandTemperatureDifference);
    void resetDeadBandTemperatureDifference();

    boost::optional<double> ratedHeatReclaimRecoveryEfficiency() const;
    bool setRatedHeatReclaimRecoveryEfficiency(double ratedHeatReclaimRecoveryEfficiency);
    void resetRatedHeatReclaimRecoveryEfficiency();

    double ratedInletWaterTemperature() const;
    bool setRatedInletWaterTemperature(double ratedInletWaterTemperature);

    double ratedOutdoorAirTemperature() const;
    bool setRatedOutdoorAirTemperature(double ratedOutdoorAirTemperature);

    double maximumInletWaterTemperatureforHeatReclaim() const;
    bool setMaximumInletWaterTemperatureforHeatReclaim(double maximumInletWaterTemperatureforHeatReclaim);

    double waterFlowRate() const;
    bool setWaterFlowRate(double waterFlowRate);

    double waterPumpPower() const;
    bool isWaterPumpPowerDefaulted() const;
    bool setWaterPumpPower(double waterPumpPower);
    void resetWaterPumpPower();

    double fractionofPumpHeattoWater() const;
    bool isFractionofPumpHeattoWaterDefaulted() const;
    bool setFractionofPumpHeattoWater(double fractionofPumpHeattoWater);
    void resetFractionofPumpHeattoWater();

    double onCycleParasiticElectricLoad() const;
    bool isOnCycleParasiticElectricLoadDefaulted() const;
    bool setOnCycleParasiticElectricLoad(double onCycleParasiticElectricLoad);
    void resetOnCycleParasiticElectricLoad();

    double offCycleParasiticElectricLoad() const;
    bool isOffCycleParasiticElectricLoadDefaulted() const;
    bool setOffCycleParasiticElectricLoad(double offCycleParasiticElectricLoad);
    void resetOffCycleParasiticElectricLoad();

   protected:
    using ImplType = detail::CoilWaterHeatingDesuperheater_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit CoilWaterHeatingDesuperheater(std::shared_ptr<detail::CoilWaterHeatingDesuperheater_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
