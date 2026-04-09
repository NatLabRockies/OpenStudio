/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl.hpp"
#include "StraightComponent/CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl_Impl.hpp"

#include "Model.hpp"
#include "StraightComponent/Node.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/Coil_Cooling_DX_VariableRefrigerantFlow_FluidTemperatureControl_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl::CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl(const Model& model)
  : StraightComponent(CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl::iddObjectType(), model) {}

CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl::CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl(
  std::shared_ptr<detail::CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl_Impl> impl)
  : StraightComponent(std::move(impl)) {}

IddObjectType CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl::iddObjectType() {
  return IddObjectType::Coil_Cooling_DX_VariableRefrigerantFlow_FluidTemperatureControl;
}

boost::optional<double> CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl::ratedTotalCoolingCapacity() const {
  return getImpl<detail::CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl_Impl>()->ratedTotalCoolingCapacity();
}

bool CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl::isRatedTotalCoolingCapacityAutosized() const {
  return getImpl<detail::CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl_Impl>()->isRatedTotalCoolingCapacityAutosized();
}

bool CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl::setRatedTotalCoolingCapacity(double ratedTotalCoolingCapacity) {
  return getImpl<detail::CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl_Impl>()->setRatedTotalCoolingCapacity(
    ratedTotalCoolingCapacity);
}

void CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl::autosizeRatedTotalCoolingCapacity() {
  getImpl<detail::CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl_Impl>()->autosizeRatedTotalCoolingCapacity();
}

boost::optional<double> CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl::ratedSensibleHeatRatio() const {
  return getImpl<detail::CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl_Impl>()->ratedSensibleHeatRatio();
}

bool CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl::isRatedSensibleHeatRatioAutosized() const {
  return getImpl<detail::CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl_Impl>()->isRatedSensibleHeatRatioAutosized();
}

bool CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl::setRatedSensibleHeatRatio(double ratedSensibleHeatRatio) {
  return getImpl<detail::CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl_Impl>()->setRatedSensibleHeatRatio(
    ratedSensibleHeatRatio);
}

void CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl::autosizeRatedSensibleHeatRatio() {
  getImpl<detail::CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl_Impl>()->autosizeRatedSensibleHeatRatio();
}

double CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl::indoorUnitReferenceSuperheating() const {
  return getImpl<detail::CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl_Impl>()->indoorUnitReferenceSuperheating();
}

bool CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl::setIndoorUnitReferenceSuperheating(double indoorUnitReferenceSuperheating) {
  return getImpl<detail::CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl_Impl>()->setIndoorUnitReferenceSuperheating(
    indoorUnitReferenceSuperheating);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

unsigned CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl_Impl::inletPort() const {
  return openstudio::Coil_Cooling_DX_VariableRefrigerantFlow_FluidTemperatureControlFields::CoilAirInletNode;
}

unsigned CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl_Impl::outletPort() const {
  return openstudio::Coil_Cooling_DX_VariableRefrigerantFlow_FluidTemperatureControlFields::CoilAirOutletNode;
}

bool CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl_Impl::addToNode(Node& /*node*/) {
  // This coil has a simple one-inlet/one-outlet air shape, so epmodel exposes
  // it as a StraightComponent. It is still intended to live inside VRF-owned
  // terminal topology, not to participate as standalone loop equipment.
  return false;
}

boost::optional<double> CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl_Impl::ratedTotalCoolingCapacity() const {
  return getDouble(openstudio::Coil_Cooling_DX_VariableRefrigerantFlow_FluidTemperatureControlFields::RatedTotalCoolingCapacity, true);
}

bool CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl_Impl::isRatedTotalCoolingCapacityAutosized() const {
  if (const auto value = getString(openstudio::Coil_Cooling_DX_VariableRefrigerantFlow_FluidTemperatureControlFields::RatedTotalCoolingCapacity,
                                   true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl_Impl::setRatedTotalCoolingCapacity(double ratedTotalCoolingCapacity) {
  return setDouble(openstudio::Coil_Cooling_DX_VariableRefrigerantFlow_FluidTemperatureControlFields::RatedTotalCoolingCapacity,
                   ratedTotalCoolingCapacity);
}

void CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl_Impl::autosizeRatedTotalCoolingCapacity() {
  OS_ASSERT(
    setString(openstudio::Coil_Cooling_DX_VariableRefrigerantFlow_FluidTemperatureControlFields::RatedTotalCoolingCapacity, "autosize"));
}

boost::optional<double> CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl_Impl::ratedSensibleHeatRatio() const {
  return getDouble(openstudio::Coil_Cooling_DX_VariableRefrigerantFlow_FluidTemperatureControlFields::RatedSensibleHeatRatio, true);
}

bool CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl_Impl::isRatedSensibleHeatRatioAutosized() const {
  if (const auto value =
        getString(openstudio::Coil_Cooling_DX_VariableRefrigerantFlow_FluidTemperatureControlFields::RatedSensibleHeatRatio, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl_Impl::setRatedSensibleHeatRatio(double ratedSensibleHeatRatio) {
  return setDouble(openstudio::Coil_Cooling_DX_VariableRefrigerantFlow_FluidTemperatureControlFields::RatedSensibleHeatRatio,
                   ratedSensibleHeatRatio);
}

void CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl_Impl::autosizeRatedSensibleHeatRatio() {
  OS_ASSERT(
    setString(openstudio::Coil_Cooling_DX_VariableRefrigerantFlow_FluidTemperatureControlFields::RatedSensibleHeatRatio, "autosize"));
}

double CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl_Impl::indoorUnitReferenceSuperheating() const {
  const auto value =
    getDouble(openstudio::Coil_Cooling_DX_VariableRefrigerantFlow_FluidTemperatureControlFields::IndoorUnitReferenceSuperheating, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl_Impl::setIndoorUnitReferenceSuperheating(
  double indoorUnitReferenceSuperheating) {
  return setDouble(openstudio::Coil_Cooling_DX_VariableRefrigerantFlow_FluidTemperatureControlFields::IndoorUnitReferenceSuperheating,
                   indoorUnitReferenceSuperheating);
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
