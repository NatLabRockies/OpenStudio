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
  // - API: Preserve openstudio::model scalar accessor names/signatures for model-counterpart compatibility.
  // - Field Mapping: ratedTotalHeatingCapacity maps to E+ GrossRatedHeatingCapacity.
  // - Field Mapping: ratedAirFlowRate maps directly to E+ RatedAirFlowRate.
  // - ForwardTranslator evidence: ForwardTranslateCoilHeatingDXVariableRefrigerantFlow.cpp writes these exact E+ fields.
  // - Field Mapping: Relationship fields (availability schedule, curves, node links) are intentionally excluded in this scalar scaffold phase.
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
