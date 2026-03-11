/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "HVACComponent/CoilCoolingDXVariableRefrigerantFlow.hpp"
#include "HVACComponent/CoilCoolingDXVariableRefrigerantFlow_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/Coil_Cooling_DX_VariableRefrigerantFlow_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

CoilCoolingDXVariableRefrigerantFlow::CoilCoolingDXVariableRefrigerantFlow(const Model& model)
  : HVACComponent(CoilCoolingDXVariableRefrigerantFlow::iddObjectType(), model) {}

CoilCoolingDXVariableRefrigerantFlow::CoilCoolingDXVariableRefrigerantFlow(
  std::shared_ptr<detail::CoilCoolingDXVariableRefrigerantFlow_Impl> impl)
  : HVACComponent(std::move(impl)) {}

IddObjectType CoilCoolingDXVariableRefrigerantFlow::iddObjectType() {
  return IddObjectType::Coil_Cooling_DX_VariableRefrigerantFlow;
}

boost::optional<double> CoilCoolingDXVariableRefrigerantFlow::ratedTotalCoolingCapacity() const {
  return getImpl<detail::CoilCoolingDXVariableRefrigerantFlow_Impl>()->ratedTotalCoolingCapacity();
}

bool CoilCoolingDXVariableRefrigerantFlow::isRatedTotalCoolingCapacityAutosized() const {
  return getImpl<detail::CoilCoolingDXVariableRefrigerantFlow_Impl>()->isRatedTotalCoolingCapacityAutosized();
}

bool CoilCoolingDXVariableRefrigerantFlow::setRatedTotalCoolingCapacity(double ratedTotalCoolingCapacity) {
  return getImpl<detail::CoilCoolingDXVariableRefrigerantFlow_Impl>()->setRatedTotalCoolingCapacity(ratedTotalCoolingCapacity);
}

void CoilCoolingDXVariableRefrigerantFlow::autosizeRatedTotalCoolingCapacity() {
  getImpl<detail::CoilCoolingDXVariableRefrigerantFlow_Impl>()->autosizeRatedTotalCoolingCapacity();
}

boost::optional<double> CoilCoolingDXVariableRefrigerantFlow::ratedSensibleHeatRatio() const {
  return getImpl<detail::CoilCoolingDXVariableRefrigerantFlow_Impl>()->ratedSensibleHeatRatio();
}

bool CoilCoolingDXVariableRefrigerantFlow::isRatedSensibleHeatRatioAutosized() const {
  return getImpl<detail::CoilCoolingDXVariableRefrigerantFlow_Impl>()->isRatedSensibleHeatRatioAutosized();
}

bool CoilCoolingDXVariableRefrigerantFlow::setRatedSensibleHeatRatio(double ratedSensibleHeatRatio) {
  return getImpl<detail::CoilCoolingDXVariableRefrigerantFlow_Impl>()->setRatedSensibleHeatRatio(ratedSensibleHeatRatio);
}

void CoilCoolingDXVariableRefrigerantFlow::autosizeRatedSensibleHeatRatio() {
  getImpl<detail::CoilCoolingDXVariableRefrigerantFlow_Impl>()->autosizeRatedSensibleHeatRatio();
}

boost::optional<double> CoilCoolingDXVariableRefrigerantFlow::ratedAirFlowRate() const {
  return getImpl<detail::CoilCoolingDXVariableRefrigerantFlow_Impl>()->ratedAirFlowRate();
}

bool CoilCoolingDXVariableRefrigerantFlow::isRatedAirFlowRateAutosized() const {
  return getImpl<detail::CoilCoolingDXVariableRefrigerantFlow_Impl>()->isRatedAirFlowRateAutosized();
}

bool CoilCoolingDXVariableRefrigerantFlow::setRatedAirFlowRate(double ratedAirFlowRate) {
  return getImpl<detail::CoilCoolingDXVariableRefrigerantFlow_Impl>()->setRatedAirFlowRate(ratedAirFlowRate);
}

void CoilCoolingDXVariableRefrigerantFlow::autosizeRatedAirFlowRate() {
  getImpl<detail::CoilCoolingDXVariableRefrigerantFlow_Impl>()->autosizeRatedAirFlowRate();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

boost::optional<double> CoilCoolingDXVariableRefrigerantFlow_Impl::ratedTotalCoolingCapacity() const {
  return getDouble(openstudio::Coil_Cooling_DX_VariableRefrigerantFlowFields::GrossRatedTotalCoolingCapacity, true);
}

bool CoilCoolingDXVariableRefrigerantFlow_Impl::isRatedTotalCoolingCapacityAutosized() const {
  if (const auto value = getString(openstudio::Coil_Cooling_DX_VariableRefrigerantFlowFields::GrossRatedTotalCoolingCapacity, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool CoilCoolingDXVariableRefrigerantFlow_Impl::setRatedTotalCoolingCapacity(double ratedTotalCoolingCapacity) {
  return setDouble(openstudio::Coil_Cooling_DX_VariableRefrigerantFlowFields::GrossRatedTotalCoolingCapacity, ratedTotalCoolingCapacity);
}

void CoilCoolingDXVariableRefrigerantFlow_Impl::autosizeRatedTotalCoolingCapacity() {
  OS_ASSERT(setString(openstudio::Coil_Cooling_DX_VariableRefrigerantFlowFields::GrossRatedTotalCoolingCapacity, "autosize"));
}

boost::optional<double> CoilCoolingDXVariableRefrigerantFlow_Impl::ratedSensibleHeatRatio() const {
  return getDouble(openstudio::Coil_Cooling_DX_VariableRefrigerantFlowFields::GrossRatedSensibleHeatRatio, true);
}

bool CoilCoolingDXVariableRefrigerantFlow_Impl::isRatedSensibleHeatRatioAutosized() const {
  if (const auto value = getString(openstudio::Coil_Cooling_DX_VariableRefrigerantFlowFields::GrossRatedSensibleHeatRatio, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool CoilCoolingDXVariableRefrigerantFlow_Impl::setRatedSensibleHeatRatio(double ratedSensibleHeatRatio) {
  return setDouble(openstudio::Coil_Cooling_DX_VariableRefrigerantFlowFields::GrossRatedSensibleHeatRatio, ratedSensibleHeatRatio);
}

void CoilCoolingDXVariableRefrigerantFlow_Impl::autosizeRatedSensibleHeatRatio() {
  OS_ASSERT(setString(openstudio::Coil_Cooling_DX_VariableRefrigerantFlowFields::GrossRatedSensibleHeatRatio, "autosize"));
}

boost::optional<double> CoilCoolingDXVariableRefrigerantFlow_Impl::ratedAirFlowRate() const {
  return getDouble(openstudio::Coil_Cooling_DX_VariableRefrigerantFlowFields::RatedAirFlowRate, true);
}

bool CoilCoolingDXVariableRefrigerantFlow_Impl::isRatedAirFlowRateAutosized() const {
  if (const auto value = getString(openstudio::Coil_Cooling_DX_VariableRefrigerantFlowFields::RatedAirFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool CoilCoolingDXVariableRefrigerantFlow_Impl::setRatedAirFlowRate(double ratedAirFlowRate) {
  return setDouble(openstudio::Coil_Cooling_DX_VariableRefrigerantFlowFields::RatedAirFlowRate, ratedAirFlowRate);
}

void CoilCoolingDXVariableRefrigerantFlow_Impl::autosizeRatedAirFlowRate() {
  OS_ASSERT(setString(openstudio::Coil_Cooling_DX_VariableRefrigerantFlowFields::RatedAirFlowRate, "autosize"));
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
