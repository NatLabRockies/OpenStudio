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
  CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl&
    operator=(CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: Preserve openstudio::model scalar accessor names/signatures for model-counterpart compatibility.
  // - Field Mapping: ratedTotalCoolingCapacity and ratedSensibleHeatRatio map directly to matching E+ fields.
  // - Field Mapping: indoorUnitReferenceSuperheating maps directly to E+ IndoorUnitReferenceSuperheating.
  // - ForwardTranslator evidence: ForwardTranslateCoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl.cpp writes these exact E+ fields.
  // - TODO(parity): Add relationship parity (availability schedule, nodes, superheating curve) after scalar saturation.
  boost::optional<double> ratedTotalCoolingCapacity() const;
  bool isRatedTotalCoolingCapacityAutosized() const;
  bool setRatedTotalCoolingCapacity(double ratedTotalCoolingCapacity);
  void autosizeRatedTotalCoolingCapacity();

  boost::optional<double> ratedSensibleHeatRatio() const;
  bool isRatedSensibleHeatRatioAutosized() const;
  bool setRatedSensibleHeatRatio(double ratedSensibleHeatRatio);
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
