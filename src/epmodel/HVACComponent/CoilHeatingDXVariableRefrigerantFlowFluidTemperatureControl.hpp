/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILHEATINGDXVARIABLEREFRIGERANTFLOWFLUIDTEMPERATURECONTROL_HPP
#define EPMODEL_COILHEATINGDXVARIABLEREFRIGERANTFLOWFLUIDTEMPERATURECONTROL_HPP

#include "EPModelAPI.hpp"
#include "HVACComponent.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl_Impl;
}

class EPMODEL_API CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl : public HVACComponent
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
  // - API: Preserve openstudio::model scalar accessor names/signatures for model-counterpart compatibility.
  // - Field Mapping: ratedTotalHeatingCapacity maps directly to E+ RatedTotalHeatingCapacity.
  // - Field Mapping: indoorUnitReferenceSubcooling maps directly to E+ IndoorUnitReferenceSubcooling.
  // - ForwardTranslator evidence: ForwardTranslateCoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl.cpp writes these exact E+ fields.
  // - TODO(parity): Add relationship parity (availability schedule, condensing curve, node links) after scalar saturation.
  boost::optional<double> ratedTotalHeatingCapacity() const;
  bool isRatedTotalHeatingCapacityAutosized() const;
  bool setRatedTotalHeatingCapacity(double ratedTotalHeatingCapacity);
  void autosizeRatedTotalHeatingCapacity();

  double indoorUnitReferenceSubcooling() const;
  bool setIndoorUnitReferenceSubcooling(double indoorUnitReferenceSubcooling);

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
