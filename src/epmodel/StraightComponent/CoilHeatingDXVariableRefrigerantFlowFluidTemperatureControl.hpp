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
  class Schedule;
  class Curve;

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
    // - Status: Partial Parity. The scalar rating surface, availability schedule, and indoor-unit condensing-temperature relationship are
    //   aligned, while epmodel still treats the coil as a serial air-side component.
    // - Canonical Counterpart: openstudio::model::CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl.
    // - Implemented Parity: `availabilitySchedule`, `ratedTotalHeatingCapacity`, `indoorUnitReferenceSubcooling`, and the
    //   indoor-unit condensing-temperature curve preserve the canonical bounded contract. epmodel also exposes the inherited
    //   straight-component inlet and outlet surface because the EnergyPlus object has a fixed one-inlet/one-outlet air path.
    // - Documented Delta: Unlike the canonical model wrapper, epmodel promotes this coil to `StraightComponent` so compound terminal owners can
    //   rely on the standard serial air-path API. That additive base-class change does not make the coil general loop equipment here:
    //   `addToNode(...)` is still rejected intentionally.
    // - Field/Storage Mapping: The epmodel wrapper maps the preserved scalar fields, required schedule pointer, and required curve pointer
    //   directly to EnergyPlus `Coil:Heating:DX:VariableRefrigerantFlow:FluidTemperatureControl` storage, and the inherited
    //   straight-component topology uses the fixed coil air inlet/outlet node fields on that same object.
    // - Default Seeding: The constructor seeds `Model::alwaysOnDiscreteSchedule()`, autosized rated total heating capacity,
    //   `indoorUnitReferenceSubcooling = 5.0`, and the canonical quadratic condensing-temperature curve.
    // - Remaining Parity Work: Autosized-result query helpers remain omitted until shared sizing-result plumbing exists.

    Schedule availabilitySchedule() const;
    bool setAvailabilitySchedule(Schedule& schedule);

    boost::optional<double> ratedTotalHeatingCapacity() const;
    bool isRatedTotalHeatingCapacityAutosized() const;
    bool setRatedTotalHeatingCapacity(double ratedTotalHeatingCapacity);
    void autosizeRatedTotalHeatingCapacity();

    double indoorUnitReferenceSubcooling() const;
    Curve indoorUnitCondensingTemperatureFunctionofSubcoolingCurve() const;
    bool setIndoorUnitReferenceSubcooling(double indoorUnitReferenceSubcooling);
    bool setIndoorUnitCondensingTemperatureFunctionofSubcoolingCurve(const Curve& curve);

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
