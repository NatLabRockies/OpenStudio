/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILHEATINGDXVARIABLEREFRIGERANTFLOWFLUIDTEMPERATURECONTROL_HPP
#define EPMODEL_COILHEATINGDXVARIABLEREFRIGERANTFLOWFLUIDTEMPERATURECONTROL_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl_Impl;
  }

  class EPMODEL_API CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl : public StraightComponent
  {
   public:
    explicit CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl(const Model& model);

    virtual ~CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl() override = default;
    CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl(const CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl& other) = default;
    CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl(CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl&& other) = default;
    CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl&
      operator=(const CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl&) = default;
    CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl& operator=(CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - Status: Partial Parity. The scalar rating and indoor-unit reference surface is aligned, and epmodel now treats the coil as a serial
    //   air-side component, while schedule and curve APIs are still omitted.
    // - Canonical Counterpart: openstudio::model::CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl.
    // - Implemented Parity: `ratedTotalHeatingCapacity`, `indoorUnitReferenceSubcooling`, and the autosize helper preserve the canonical
    //   scalar contract. epmodel also exposes the inherited straight-component inlet and outlet surface because the EnergyPlus object has a
    //   fixed one-inlet/one-outlet air path.
    // - Documented Delta: Unlike the canonical model wrapper, epmodel promotes this coil to `StraightComponent` so compound terminal owners can
    //   rely on the standard serial air-path API. That additive base-class change does not make the coil general loop equipment here:
    //   `addToNode(...)` is still rejected intentionally. Availability schedule and condensing-curve APIs are also still omitted.
    // - Field/Storage Mapping: The epmodel wrapper maps the preserved scalar fields directly to EnergyPlus
    //   `Coil:Heating:DX:VariableRefrigerantFlow:FluidTemperatureControl` storage, and the inherited straight-component topology uses the
    //   fixed coil air inlet/outlet node fields on that same object.
    // - Evidence: `src/model/CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl.hpp`, `src/model/CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl.cpp`, `src/energyplus/ForwardTranslator/ForwardTranslateCoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl.cpp`, and `src/epmodel/test/CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl_GTest.cpp`.
    // - Remaining Parity Work: Add the omitted schedule, curve, and object-link APIs after the relationship layer is available.
    /** @name Rated total heating capacity */
    //@{
    boost::optional<double> ratedTotalHeatingCapacity() const;
    bool isRatedTotalHeatingCapacityAutosized() const;
    bool setRatedTotalHeatingCapacity(double ratedTotalHeatingCapacity);
    void autosizeRatedTotalHeatingCapacity();
    //@}

    /** @name Indoor unit reference subcooling */
    //@{
    double indoorUnitReferenceSubcooling() const;
    bool setIndoorUnitReferenceSubcooling(double indoorUnitReferenceSubcooling);
    //@}

   protected:
    using ImplType = detail::CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl(
      std::shared_ptr<detail::CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
