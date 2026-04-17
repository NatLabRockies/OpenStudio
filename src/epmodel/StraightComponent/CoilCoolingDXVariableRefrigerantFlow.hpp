/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILCOOLINGDXVARIABLEREFRIGERANTFLOW_HPP
#define EPMODEL_COILCOOLINGDXVARIABLEREFRIGERANTFLOW_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;
  class Node;
  class Schedule;
  class Curve;

  namespace detail {
    class CoilCoolingDXVariableRefrigerantFlow_Impl;
  }

  class EPMODEL_API CoilCoolingDXVariableRefrigerantFlow : public StraightComponent
  {
   public:
    explicit CoilCoolingDXVariableRefrigerantFlow(const Model& model);

    virtual ~CoilCoolingDXVariableRefrigerantFlow() override = default;
    CoilCoolingDXVariableRefrigerantFlow(const CoilCoolingDXVariableRefrigerantFlow& other) = default;
    CoilCoolingDXVariableRefrigerantFlow(CoilCoolingDXVariableRefrigerantFlow&& other) = default;
    CoilCoolingDXVariableRefrigerantFlow& operator=(const CoilCoolingDXVariableRefrigerantFlow&) = default;
    CoilCoolingDXVariableRefrigerantFlow& operator=(CoilCoolingDXVariableRefrigerantFlow&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - Status: Partial Parity. The scalar rating surface is aligned, the required schedule/curve relationships are exposed, and epmodel still
    //   treats the coil as a serial air-side component with a deliberately rejected standalone insertion path.
    // - Canonical Counterpart: openstudio::model::CoilCoolingDXVariableRefrigerantFlow.
    // - Implemented Parity: `availabilitySchedule`, the two cooling-capacity modifier curve relationships, the scalar rating surface, and their
    //   autosize helpers preserve the canonical public contract. epmodel also exposes the inherited straight-component inlet and outlet surface
    //   because the EnergyPlus object has a fixed one-inlet/one-outlet air path.
    // - Documented Delta: Unlike the canonical model wrapper, epmodel promotes this coil to `StraightComponent` so compound component owners can
    //   rely on the standard serial air-path API. That additive base-class change does not make the coil general loop equipment here:
    //   `addToNode(...)` is still rejected intentionally.
    // - Field/Storage Mapping: The preserved scalar fields, required schedule pointer, and required curve pointers map directly to EnergyPlus
    //   `Coil:Cooling:DX:VariableRefrigerantFlow` storage, and the inherited straight-component topology uses the fixed coil air inlet/outlet
    //   node fields on that same object.
    // - Evidence: `src/model/CoilCoolingDXVariableRefrigerantFlow.hpp`, `src/model/CoilCoolingDXVariableRefrigerantFlow.cpp`,
    //   `src/energyplus/ForwardTranslator/ForwardTranslateCoilCoolingDXVariableRefrigerantFlow.cpp`, and
    //   `src/epmodel/test/CoilCoolingDXVariableRefrigerantFlow_GTest.cpp`.
    // - Remaining Parity Work: Autosized-result query helpers remain omitted until shared sizing-result plumbing exists.
    Schedule availabilitySchedule() const;
    bool setAvailabilitySchedule(Schedule& schedule);

    boost::optional<double> ratedTotalCoolingCapacity() const;
    bool setRatedTotalCoolingCapacity(double ratedTotalCoolingCapacity);
    bool isRatedTotalCoolingCapacityAutosized() const;
    void autosizeRatedTotalCoolingCapacity();

    boost::optional<double> ratedSensibleHeatRatio() const;
    bool setRatedSensibleHeatRatio(double ratedSensibleHeatRatio);
    bool isRatedSensibleHeatRatioAutosized() const;
    void autosizeRatedSensibleHeatRatio();

    boost::optional<double> ratedAirFlowRate() const;
    bool setRatedAirFlowRate(double ratedAirFlowRate);
    bool isRatedAirFlowRateAutosized() const;
    void autosizeRatedAirFlowRate();

    Curve coolingCapacityRatioModifierFunctionofTemperatureCurve() const;
    bool setCoolingCapacityRatioModifierFunctionofTemperatureCurve(const Curve& curve);

    Curve coolingCapacityModifierCurveFunctionofFlowFraction() const;
    bool setCoolingCapacityModifierCurveFunctionofFlowFraction(const Curve& curve);

   protected:
    using ImplType = detail::CoilCoolingDXVariableRefrigerantFlow_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit CoilCoolingDXVariableRefrigerantFlow(std::shared_ptr<detail::CoilCoolingDXVariableRefrigerantFlow_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
