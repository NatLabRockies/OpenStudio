/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILCOOLINGDXVARIABLEREFRIGERANTFLOWFLUIDTEMPERATURECONTROL_HPP
#define EPMODEL_COILCOOLINGDXVARIABLEREFRIGERANTFLOWFLUIDTEMPERATURECONTROL_HPP

#include "EPModelAPI.hpp"
#include "HVACComponent.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl_Impl;
  }

  class EPMODEL_API CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl : public HVACComponent
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
    // - Status: Scalar Parity. The scalar rating and indoor-unit reference surface is aligned, while schedule, curve, and connection APIs are still omitted.
    // - Canonical Counterpart: openstudio::model::CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl.
    // - Implemented Parity: `ratedTotalCoolingCapacity`, `ratedSensibleHeatRatio`, `indoorUnitReferenceSuperheating`, and their autosize helpers preserve the canonical scalar contract.
    // - Documented Delta: Availability schedule, superheating-curve, and node-link accessors are not exposed yet even though they exist on the canonical model type.
    // - Field/Storage Mapping: The epmodel wrapper maps the preserved scalar fields directly to EnergyPlus `Coil:Cooling:DX:VariableRefrigerantFlow:FluidTemperatureControl` storage.
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
