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
    explicit CoilWaterHeatingDesuperheater(const Model& model);

    virtual ~CoilWaterHeatingDesuperheater() override = default;
    CoilWaterHeatingDesuperheater(const CoilWaterHeatingDesuperheater& other) = default;
    CoilWaterHeatingDesuperheater(CoilWaterHeatingDesuperheater&& other) = default;
    CoilWaterHeatingDesuperheater& operator=(const CoilWaterHeatingDesuperheater&) = default;
    CoilWaterHeatingDesuperheater& operator=(CoilWaterHeatingDesuperheater&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - Status: Partial Parity. The canonical scalar surface plus the required availability-schedule and bounded relationship slice are present, while tank-link and broader node-link helpers remain out of scope.
    // - Canonical Counterpart: openstudio::model::CoilWaterHeatingDesuperheater.
    // - Implemented Parity: The dead-band, heat-reclaim, water-flow, pump-power, and parasitic-load helpers preserve the canonical scalar API; `availabilitySchedule`,
    //   the optional reclaim-efficiency curve, the optional heating-source relationship, curve child traversal, and the canonical `addToNode(...)` rejection preserve
    //   the current bounded relationship slice.
    // - Documented Delta: Tank-link helpers remain out of scope for this wrapper.
    // - Field/Storage Mapping: Preserved scalars and relationships map directly to EnergyPlus `Coil:WaterHeating:Desuperheater` fields.
    // - Evidence: `src/model/CoilWaterHeatingDesuperheater.hpp`, `src/energyplus/ForwardTranslator/ForwardTranslateCoilWaterHeatingDesuperheater.cpp`, and `src/epmodel/test/CoilWaterHeatingDesuperheater_GTest.cpp`.
    // - Remaining Parity Work: Add the omitted tank-link and broader relationship helpers without changing the preserved scalar signatures.

    Schedule availabilitySchedule() const;
    bool setAvailabilitySchedule(Schedule& schedule);

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
