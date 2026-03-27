/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILCOOLINGDXVARIABLEREFRIGERANTFLOW_HPP
#define EPMODEL_COILCOOLINGDXVARIABLEREFRIGERANTFLOW_HPP

#include "EPModelAPI.hpp"
#include "HVACComponent.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class CoilCoolingDXVariableRefrigerantFlow_Impl;
  }

  class EPMODEL_API CoilCoolingDXVariableRefrigerantFlow : public HVACComponent
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
    // - Status: Scalar Parity. The scalar rating surface is aligned, while schedule, curve, and connection APIs are still omitted.
    // - Canonical Counterpart: openstudio::model::CoilCoolingDXVariableRefrigerantFlow.
    // - Implemented Parity: `ratedTotalCoolingCapacity`, `ratedSensibleHeatRatio`, `ratedAirFlowRate`, and their autosize helpers preserve the canonical scalar rating contract.
    // - Documented Delta: Availability schedule, performance-curve, and node-link accessors are not exposed yet even though they exist on the canonical model type.
    // - Field/Storage Mapping: The epmodel wrapper maps the preserved scalar fields directly to EnergyPlus `Coil:Cooling:DX:VariableRefrigerantFlow` storage.
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
