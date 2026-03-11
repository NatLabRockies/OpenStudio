/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "HVACComponent/CoilHeatingDXVariableRefrigerantFlow.hpp"
#include "HVACComponent/CoilHeatingDXVariableRefrigerantFlow_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/Coil_Heating_DX_VariableRefrigerantFlow_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

CoilHeatingDXVariableRefrigerantFlow::CoilHeatingDXVariableRefrigerantFlow(const Model& model)
  : HVACComponent(CoilHeatingDXVariableRefrigerantFlow::iddObjectType(), model) {}

CoilHeatingDXVariableRefrigerantFlow::CoilHeatingDXVariableRefrigerantFlow(
  std::shared_ptr<detail::CoilHeatingDXVariableRefrigerantFlow_Impl> impl)
  : HVACComponent(std::move(impl)) {}

IddObjectType CoilHeatingDXVariableRefrigerantFlow::iddObjectType() {
  return IddObjectType::Coil_Heating_DX_VariableRefrigerantFlow;
}

boost::optional<double> CoilHeatingDXVariableRefrigerantFlow::ratedTotalHeatingCapacity() const {
  return getImpl<detail::CoilHeatingDXVariableRefrigerantFlow_Impl>()->ratedTotalHeatingCapacity();
}

bool CoilHeatingDXVariableRefrigerantFlow::isRatedTotalHeatingCapacityAutosized() const {
  return getImpl<detail::CoilHeatingDXVariableRefrigerantFlow_Impl>()->isRatedTotalHeatingCapacityAutosized();
}

bool CoilHeatingDXVariableRefrigerantFlow::setRatedTotalHeatingCapacity(double ratedTotalHeatingCapacity) {
  return getImpl<detail::CoilHeatingDXVariableRefrigerantFlow_Impl>()->setRatedTotalHeatingCapacity(ratedTotalHeatingCapacity);
}

void CoilHeatingDXVariableRefrigerantFlow::autosizeRatedTotalHeatingCapacity() {
  getImpl<detail::CoilHeatingDXVariableRefrigerantFlow_Impl>()->autosizeRatedTotalHeatingCapacity();
}

boost::optional<double> CoilHeatingDXVariableRefrigerantFlow::ratedAirFlowRate() const {
  return getImpl<detail::CoilHeatingDXVariableRefrigerantFlow_Impl>()->ratedAirFlowRate();
}

bool CoilHeatingDXVariableRefrigerantFlow::isRatedAirFlowRateAutosized() const {
  return getImpl<detail::CoilHeatingDXVariableRefrigerantFlow_Impl>()->isRatedAirFlowRateAutosized();
}

bool CoilHeatingDXVariableRefrigerantFlow::setRatedAirFlowRate(double ratedAirFlowRate) {
  return getImpl<detail::CoilHeatingDXVariableRefrigerantFlow_Impl>()->setRatedAirFlowRate(ratedAirFlowRate);
}

void CoilHeatingDXVariableRefrigerantFlow::autosizeRatedAirFlowRate() {
  getImpl<detail::CoilHeatingDXVariableRefrigerantFlow_Impl>()->autosizeRatedAirFlowRate();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

boost::optional<double> CoilHeatingDXVariableRefrigerantFlow_Impl::ratedTotalHeatingCapacity() const {
  return getDouble(openstudio::Coil_Heating_DX_VariableRefrigerantFlowFields::GrossRatedHeatingCapacity, true);
}

bool CoilHeatingDXVariableRefrigerantFlow_Impl::isRatedTotalHeatingCapacityAutosized() const {
  if (const auto value = getString(openstudio::Coil_Heating_DX_VariableRefrigerantFlowFields::GrossRatedHeatingCapacity, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool CoilHeatingDXVariableRefrigerantFlow_Impl::setRatedTotalHeatingCapacity(double ratedTotalHeatingCapacity) {
  return setDouble(openstudio::Coil_Heating_DX_VariableRefrigerantFlowFields::GrossRatedHeatingCapacity, ratedTotalHeatingCapacity);
}

void CoilHeatingDXVariableRefrigerantFlow_Impl::autosizeRatedTotalHeatingCapacity() {
  OS_ASSERT(setString(openstudio::Coil_Heating_DX_VariableRefrigerantFlowFields::GrossRatedHeatingCapacity, "autosize"));
}

boost::optional<double> CoilHeatingDXVariableRefrigerantFlow_Impl::ratedAirFlowRate() const {
  return getDouble(openstudio::Coil_Heating_DX_VariableRefrigerantFlowFields::RatedAirFlowRate, true);
}

bool CoilHeatingDXVariableRefrigerantFlow_Impl::isRatedAirFlowRateAutosized() const {
  if (const auto value = getString(openstudio::Coil_Heating_DX_VariableRefrigerantFlowFields::RatedAirFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool CoilHeatingDXVariableRefrigerantFlow_Impl::setRatedAirFlowRate(double ratedAirFlowRate) {
  return setDouble(openstudio::Coil_Heating_DX_VariableRefrigerantFlowFields::RatedAirFlowRate, ratedAirFlowRate);
}

void CoilHeatingDXVariableRefrigerantFlow_Impl::autosizeRatedAirFlowRate() {
  OS_ASSERT(setString(openstudio::Coil_Heating_DX_VariableRefrigerantFlowFields::RatedAirFlowRate, "autosize"));
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
