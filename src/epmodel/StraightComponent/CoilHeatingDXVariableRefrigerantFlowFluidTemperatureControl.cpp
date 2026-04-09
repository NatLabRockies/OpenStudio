/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl.hpp"
#include "StraightComponent/CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl_Impl.hpp"

#include "Model.hpp"
#include "StraightComponent/Node.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/Coil_Heating_DX_VariableRefrigerantFlow_FluidTemperatureControl_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl::CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl(const Model& model)
  : StraightComponent(CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl::iddObjectType(), model) {}

CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl::CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl(
  std::shared_ptr<detail::CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl_Impl> impl)
  : StraightComponent(std::move(impl)) {}

IddObjectType CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl::iddObjectType() {
  return IddObjectType::Coil_Heating_DX_VariableRefrigerantFlow_FluidTemperatureControl;
}

boost::optional<double> CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl::ratedTotalHeatingCapacity() const {
  return getImpl<detail::CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl_Impl>()->ratedTotalHeatingCapacity();
}

bool CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl::isRatedTotalHeatingCapacityAutosized() const {
  return getImpl<detail::CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl_Impl>()->isRatedTotalHeatingCapacityAutosized();
}

bool CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl::setRatedTotalHeatingCapacity(double ratedTotalHeatingCapacity) {
  return getImpl<detail::CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl_Impl>()->setRatedTotalHeatingCapacity(ratedTotalHeatingCapacity);
}

void CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl::autosizeRatedTotalHeatingCapacity() {
  getImpl<detail::CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl_Impl>()->autosizeRatedTotalHeatingCapacity();
}

double CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl::indoorUnitReferenceSubcooling() const {
  return getImpl<detail::CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl_Impl>()->indoorUnitReferenceSubcooling();
}

bool CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl::setIndoorUnitReferenceSubcooling(double indoorUnitReferenceSubcooling) {
  return getImpl<detail::CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl_Impl>()->setIndoorUnitReferenceSubcooling(
    indoorUnitReferenceSubcooling);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

unsigned CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl_Impl::inletPort() const {
  return openstudio::Coil_Heating_DX_VariableRefrigerantFlow_FluidTemperatureControlFields::CoilAirInletNode;
}

unsigned CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl_Impl::outletPort() const {
  return openstudio::Coil_Heating_DX_VariableRefrigerantFlow_FluidTemperatureControlFields::CoilAirOutletNode;
}

bool CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl_Impl::addToNode(Node& /*node*/) {
  // This coil has a simple one-inlet/one-outlet air shape, so epmodel exposes
  // it as a StraightComponent. It is still intended to live inside VRF-owned
  // terminal topology, not to participate as standalone loop equipment.
  return false;
}

boost::optional<double> CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl_Impl::ratedTotalHeatingCapacity() const {
  return getDouble(openstudio::Coil_Heating_DX_VariableRefrigerantFlow_FluidTemperatureControlFields::RatedTotalHeatingCapacity, true);
}

bool CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl_Impl::isRatedTotalHeatingCapacityAutosized() const {
  if (const auto value = getString(openstudio::Coil_Heating_DX_VariableRefrigerantFlow_FluidTemperatureControlFields::RatedTotalHeatingCapacity,
                                   true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl_Impl::setRatedTotalHeatingCapacity(double ratedTotalHeatingCapacity) {
  return setDouble(openstudio::Coil_Heating_DX_VariableRefrigerantFlow_FluidTemperatureControlFields::RatedTotalHeatingCapacity,
                   ratedTotalHeatingCapacity);
}

void CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl_Impl::autosizeRatedTotalHeatingCapacity() {
  OS_ASSERT(
    setString(openstudio::Coil_Heating_DX_VariableRefrigerantFlow_FluidTemperatureControlFields::RatedTotalHeatingCapacity, "autosize"));
}

double CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl_Impl::indoorUnitReferenceSubcooling() const {
  const auto value =
    getDouble(openstudio::Coil_Heating_DX_VariableRefrigerantFlow_FluidTemperatureControlFields::IndoorUnitReferenceSubcooling, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl_Impl::setIndoorUnitReferenceSubcooling(
  double indoorUnitReferenceSubcooling) {
  return setDouble(openstudio::Coil_Heating_DX_VariableRefrigerantFlow_FluidTemperatureControlFields::IndoorUnitReferenceSubcooling,
                   indoorUnitReferenceSubcooling);
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
