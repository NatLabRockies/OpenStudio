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
    // - Status: Partial Parity. The scalar rating surface is aligned, and epmodel now treats the coil as a serial air-side component, while
    //   schedule and curve APIs are still omitted.
    // - Canonical Counterpart: openstudio::model::CoilCoolingDXVariableRefrigerantFlow.
    // - Implemented Parity: `ratedTotalCoolingCapacity`, `ratedSensibleHeatRatio`, `ratedAirFlowRate`, and their autosize helpers preserve the
    //   canonical scalar rating contract. epmodel also exposes the inherited straight-component inlet and outlet surface because the EnergyPlus
    //   object has a fixed one-inlet/one-outlet air path.
    // - Documented Delta: Unlike the canonical model wrapper, epmodel promotes this coil to `StraightComponent` so compound terminal owners can
    //   rely on the standard serial air-path API. That additive base-class change does not make the coil general loop equipment here:
    //   `addToNode(...)` is still rejected intentionally. Availability schedule and performance-curve APIs are also still omitted.
    // - Field/Storage Mapping: The epmodel wrapper maps the preserved scalar fields directly to EnergyPlus
    //   `Coil:Cooling:DX:VariableRefrigerantFlow` storage, and the inherited straight-component topology uses the fixed coil air inlet/outlet
    //   node fields on that same object.
    // - Evidence: `src/model/CoilCoolingDXVariableRefrigerantFlow.hpp`, `src/model/CoilCoolingDXVariableRefrigerantFlow.cpp`, `src/energyplus/ForwardTranslator/ForwardTranslateCoilCoolingDXVariableRefrigerantFlow.cpp`, and `src/epmodel/test/CoilCoolingDXVariableRefrigerantFlow_GTest.cpp`.
    // - Remaining Parity Work: Add the omitted schedule, curve, and object-link APIs after the relationship layer is available.
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
