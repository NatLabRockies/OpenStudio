/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILCOOLINGDXVARIABLEREFRIGERANTFLOWFLUIDTEMPERATURECONTROL_HPP
#define EPMODEL_COILCOOLINGDXVARIABLEREFRIGERANTFLOWFLUIDTEMPERATURECONTROL_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl_Impl;
  }

  class EPMODEL_API CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl : public StraightComponent
  {
   public:
    explicit CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl(const Model& model);

    virtual ~CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl() override = default;
    CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl(const CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl& other) = default;
    CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl(CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl&& other) = default;
    CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl&
      operator=(const CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl&) = default;
    CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl& operator=(CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - Status: Partial Parity. The scalar rating and indoor-unit reference surface is aligned, and epmodel now treats the coil as a serial
    //   air-side component, while schedule and curve APIs are still omitted.
    // - Canonical Counterpart: openstudio::model::CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl.
    // - Implemented Parity: `ratedTotalCoolingCapacity`, `ratedSensibleHeatRatio`, `indoorUnitReferenceSuperheating`, and their autosize
    //   helpers preserve the canonical scalar contract. epmodel also exposes the inherited straight-component inlet and outlet surface because
    //   the EnergyPlus object has a fixed one-inlet/one-outlet air path.
    // - Documented Delta: Unlike the canonical model wrapper, epmodel promotes this coil to `StraightComponent` so compound terminal owners can
    //   rely on the standard serial air-path API. That additive base-class change does not make the coil general loop equipment here:
    //   `addToNode(...)` is still rejected intentionally. Availability schedule and superheating-curve APIs are also still omitted.
    // - Field/Storage Mapping: The epmodel wrapper maps the preserved scalar fields directly to EnergyPlus
    //   `Coil:Cooling:DX:VariableRefrigerantFlow:FluidTemperatureControl` storage, and the inherited straight-component topology uses the fixed
    //   coil air inlet/outlet node fields on that same object.
    // - Evidence: `src/model/CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl.hpp`, `src/model/CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl.cpp`, `src/energyplus/ForwardTranslator/ForwardTranslateCoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl.cpp`, and `src/epmodel/test/CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl_GTest.cpp`.
    // - Remaining Parity Work: Add the omitted schedule, curve, and object-link APIs after the relationship layer is available.
    boost::optional<double> ratedTotalCoolingCapacity() const;
    bool setRatedTotalCoolingCapacity(double ratedTotalCoolingCapacity);
    bool isRatedTotalCoolingCapacityAutosized() const;
    void autosizeRatedTotalCoolingCapacity();

    boost::optional<double> ratedSensibleHeatRatio() const;
    bool setRatedSensibleHeatRatio(double ratedSensibleHeatRatio);
    bool isRatedSensibleHeatRatioAutosized() const;
    void autosizeRatedSensibleHeatRatio();

    double indoorUnitReferenceSuperheating() const;
    bool setIndoorUnitReferenceSuperheating(double indoorUnitReferenceSuperheating);

   protected:
    using ImplType = detail::CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl(
      std::shared_ptr<detail::CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
