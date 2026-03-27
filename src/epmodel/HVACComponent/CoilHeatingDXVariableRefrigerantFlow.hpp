/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILHEATINGDXVARIABLEREFRIGERANTFLOW_HPP
#define EPMODEL_COILHEATINGDXVARIABLEREFRIGERANTFLOW_HPP

#include "EPModelAPI.hpp"
#include "HVACComponent.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class CoilHeatingDXVariableRefrigerantFlow_Impl;
}

class EPMODEL_API CoilHeatingDXVariableRefrigerantFlow : public HVACComponent
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
  // - Status: Scalar Parity. The scalar rating surface is aligned, while schedule, curve, and connection APIs are still omitted.
  // - Canonical Counterpart: openstudio::model::CoilHeatingDXVariableRefrigerantFlow.
  // - Implemented Parity: `ratedTotalHeatingCapacity`, `ratedAirFlowRate`, and their autosize helpers preserve the canonical scalar rating contract.
  // - Documented Delta: Availability schedule, performance-curve, and node-link accessors are not exposed yet even though they exist on the canonical model type.
  // - Field/Storage Mapping: The epmodel wrapper maps the preserved scalar fields directly to EnergyPlus `Coil:Heating:DX:VariableRefrigerantFlow` storage.
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
