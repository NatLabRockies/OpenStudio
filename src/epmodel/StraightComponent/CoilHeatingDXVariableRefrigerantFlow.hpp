/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILHEATINGDXVARIABLEREFRIGERANTFLOW_HPP
#define EPMODEL_COILHEATINGDXVARIABLEREFRIGERANTFLOW_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class CoilHeatingDXVariableRefrigerantFlow_Impl;
}

class EPMODEL_API CoilHeatingDXVariableRefrigerantFlow : public StraightComponent
{
 public:
  explicit CoilHeatingDXVariableRefrigerantFlow(const Model& model);

  virtual ~CoilHeatingDXVariableRefrigerantFlow() override = default;
  CoilHeatingDXVariableRefrigerantFlow(const CoilHeatingDXVariableRefrigerantFlow& other) = default;
  CoilHeatingDXVariableRefrigerantFlow(CoilHeatingDXVariableRefrigerantFlow&& other) = default;
  CoilHeatingDXVariableRefrigerantFlow& operator=(const CoilHeatingDXVariableRefrigerantFlow&) = default;
  CoilHeatingDXVariableRefrigerantFlow& operator=(CoilHeatingDXVariableRefrigerantFlow&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - Status: Partial Parity. The scalar rating surface is aligned, and epmodel now treats the coil as a serial air-side component, while
  //   schedule and curve APIs are still omitted.
  // - Canonical Counterpart: openstudio::model::CoilHeatingDXVariableRefrigerantFlow.
  // - Implemented Parity: `ratedTotalHeatingCapacity`, `ratedAirFlowRate`, and their autosize helpers preserve the canonical scalar rating
  //   contract. epmodel also exposes the inherited straight-component inlet and outlet surface because the EnergyPlus object has a fixed
  //   one-inlet/one-outlet air path.
  // - Documented Delta: Unlike the canonical model wrapper, epmodel promotes this coil to `StraightComponent` so compound terminal owners can
  //   rely on the standard serial air-path API. That additive base-class change does not make the coil general loop equipment here:
  //   `addToNode(...)` is still rejected intentionally. Availability schedule and performance-curve APIs are also still omitted.
  // - Field/Storage Mapping: The epmodel wrapper maps the preserved scalar fields directly to EnergyPlus `Coil:Heating:DX:VariableRefrigerantFlow`
  //   storage, and the inherited straight-component topology uses the fixed coil air inlet/outlet node fields on that same object.
  // - Evidence: `src/model/CoilHeatingDXVariableRefrigerantFlow.hpp`, `src/model/CoilHeatingDXVariableRefrigerantFlow.cpp`, `src/energyplus/ForwardTranslator/ForwardTranslateCoilHeatingDXVariableRefrigerantFlow.cpp`, and `src/epmodel/test/CoilHeatingDXVariableRefrigerantFlow_GTest.cpp`.
  // - Remaining Parity Work: Add the omitted schedule, curve, and object-link APIs after the relationship layer is available.
  boost::optional<double> ratedTotalHeatingCapacity() const;
  bool isRatedTotalHeatingCapacityAutosized() const;
  bool setRatedTotalHeatingCapacity(double ratedTotalHeatingCapacity);
  void autosizeRatedTotalHeatingCapacity();

  boost::optional<double> ratedAirFlowRate() const;
  bool isRatedAirFlowRateAutosized() const;
  bool setRatedAirFlowRate(double ratedAirFlowRate);
  void autosizeRatedAirFlowRate();

 protected:
  using ImplType = detail::CoilHeatingDXVariableRefrigerantFlow_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit CoilHeatingDXVariableRefrigerantFlow(std::shared_ptr<detail::CoilHeatingDXVariableRefrigerantFlow_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
