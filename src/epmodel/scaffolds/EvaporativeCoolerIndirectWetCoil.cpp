/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "EvaporativeCoolerIndirectWetCoil.hpp"
#include "EvaporativeCoolerIndirectWetCoil_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/EvaporativeCooler_Indirect_WetCoil_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

EvaporativeCoolerIndirectWetCoil::EvaporativeCoolerIndirectWetCoil(const Model& model)
  : ModelObject(EvaporativeCoolerIndirectWetCoil::iddObjectType(), model) {}

EvaporativeCoolerIndirectWetCoil::EvaporativeCoolerIndirectWetCoil(std::shared_ptr<detail::EvaporativeCoolerIndirectWetCoil_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType EvaporativeCoolerIndirectWetCoil::iddObjectType() {
  return IddObjectType::EvaporativeCooler_Indirect_WetCoil;
}

double EvaporativeCoolerIndirectWetCoil::coilMaximumEfficiency() const {
  return getImpl<detail::EvaporativeCoolerIndirectWetCoil_Impl>()->coilMaximumEfficiency();
}

bool EvaporativeCoolerIndirectWetCoil::setCoilMaximumEfficiency(double coilMaximumEfficiency) {
  return getImpl<detail::EvaporativeCoolerIndirectWetCoil_Impl>()->setCoilMaximumEfficiency(coilMaximumEfficiency);
}

boost::optional<double> EvaporativeCoolerIndirectWetCoil::coilFlowRatio() const {
  return getImpl<detail::EvaporativeCoolerIndirectWetCoil_Impl>()->coilFlowRatio();
}

bool EvaporativeCoolerIndirectWetCoil::setCoilFlowRatio(double coilFlowRatio) {
  return getImpl<detail::EvaporativeCoolerIndirectWetCoil_Impl>()->setCoilFlowRatio(coilFlowRatio);
}

void EvaporativeCoolerIndirectWetCoil::resetCoilFlowRatio() {
  getImpl<detail::EvaporativeCoolerIndirectWetCoil_Impl>()->resetCoilFlowRatio();
}

double EvaporativeCoolerIndirectWetCoil::recirculatingWaterPumpPowerConsumption() const {
  return getImpl<detail::EvaporativeCoolerIndirectWetCoil_Impl>()->recirculatingWaterPumpPowerConsumption();
}

bool EvaporativeCoolerIndirectWetCoil::setRecirculatingWaterPumpPowerConsumption(double recirculatingWaterPumpPowerConsumption) {
  return getImpl<detail::EvaporativeCoolerIndirectWetCoil_Impl>()->setRecirculatingWaterPumpPowerConsumption(
    recirculatingWaterPumpPowerConsumption);
}

double EvaporativeCoolerIndirectWetCoil::secondaryAirFanFlowRate() const {
  return getImpl<detail::EvaporativeCoolerIndirectWetCoil_Impl>()->secondaryAirFanFlowRate();
}

bool EvaporativeCoolerIndirectWetCoil::setSecondaryAirFanFlowRate(double secondaryAirFanFlowRate) {
  return getImpl<detail::EvaporativeCoolerIndirectWetCoil_Impl>()->setSecondaryAirFanFlowRate(secondaryAirFanFlowRate);
}

double EvaporativeCoolerIndirectWetCoil::secondaryAirFanTotalEfficiency() const {
  return getImpl<detail::EvaporativeCoolerIndirectWetCoil_Impl>()->secondaryAirFanTotalEfficiency();
}

bool EvaporativeCoolerIndirectWetCoil::setSecondaryAirFanTotalEfficiency(double secondaryAirFanTotalEfficiency) {
  return getImpl<detail::EvaporativeCoolerIndirectWetCoil_Impl>()->setSecondaryAirFanTotalEfficiency(secondaryAirFanTotalEfficiency);
}

double EvaporativeCoolerIndirectWetCoil::secondaryAirFanDeltaPressure() const {
  return getImpl<detail::EvaporativeCoolerIndirectWetCoil_Impl>()->secondaryAirFanDeltaPressure();
}

bool EvaporativeCoolerIndirectWetCoil::setSecondaryAirFanDeltaPressure(double secondaryAirFanDeltaPressure) {
  return getImpl<detail::EvaporativeCoolerIndirectWetCoil_Impl>()->setSecondaryAirFanDeltaPressure(secondaryAirFanDeltaPressure);
}

boost::optional<std::string> EvaporativeCoolerIndirectWetCoil::controlType() const {
  return getImpl<detail::EvaporativeCoolerIndirectWetCoil_Impl>()->controlType();
}

bool EvaporativeCoolerIndirectWetCoil::setControlType(const std::string& controlType) {
  return getImpl<detail::EvaporativeCoolerIndirectWetCoil_Impl>()->setControlType(controlType);
}

void EvaporativeCoolerIndirectWetCoil::resetControlType() {
  getImpl<detail::EvaporativeCoolerIndirectWetCoil_Impl>()->resetControlType();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

double EvaporativeCoolerIndirectWetCoil_Impl::coilMaximumEfficiency() const {
  const auto value = getDouble(openstudio::EvaporativeCooler_Indirect_WetCoilFields::CoilMaximumEfficiency, true);
  OS_ASSERT(value);
  return *value;
}

bool EvaporativeCoolerIndirectWetCoil_Impl::setCoilMaximumEfficiency(double coilMaximumEfficiency) {
  return setDouble(openstudio::EvaporativeCooler_Indirect_WetCoilFields::CoilMaximumEfficiency, coilMaximumEfficiency);
}

boost::optional<double> EvaporativeCoolerIndirectWetCoil_Impl::coilFlowRatio() const {
  return getDouble(openstudio::EvaporativeCooler_Indirect_WetCoilFields::CoilFlowRatio, true);
}

bool EvaporativeCoolerIndirectWetCoil_Impl::setCoilFlowRatio(double coilFlowRatio) {
  return setDouble(openstudio::EvaporativeCooler_Indirect_WetCoilFields::CoilFlowRatio, coilFlowRatio);
}

void EvaporativeCoolerIndirectWetCoil_Impl::resetCoilFlowRatio() {
  OS_ASSERT(setString(openstudio::EvaporativeCooler_Indirect_WetCoilFields::CoilFlowRatio, ""));
}

double EvaporativeCoolerIndirectWetCoil_Impl::recirculatingWaterPumpPowerConsumption() const {
  const auto value = getDouble(openstudio::EvaporativeCooler_Indirect_WetCoilFields::RecirculatingWaterPumpPowerConsumption, true);
  OS_ASSERT(value);
  return *value;
}

bool EvaporativeCoolerIndirectWetCoil_Impl::setRecirculatingWaterPumpPowerConsumption(double recirculatingWaterPumpPowerConsumption) {
  return setDouble(openstudio::EvaporativeCooler_Indirect_WetCoilFields::RecirculatingWaterPumpPowerConsumption,
                   recirculatingWaterPumpPowerConsumption);
}

double EvaporativeCoolerIndirectWetCoil_Impl::secondaryAirFanFlowRate() const {
  const auto value = getDouble(openstudio::EvaporativeCooler_Indirect_WetCoilFields::SecondaryAirFanFlowRate, true);
  OS_ASSERT(value);
  return *value;
}

bool EvaporativeCoolerIndirectWetCoil_Impl::setSecondaryAirFanFlowRate(double secondaryAirFanFlowRate) {
  return setDouble(openstudio::EvaporativeCooler_Indirect_WetCoilFields::SecondaryAirFanFlowRate, secondaryAirFanFlowRate);
}

double EvaporativeCoolerIndirectWetCoil_Impl::secondaryAirFanTotalEfficiency() const {
  const auto value = getDouble(openstudio::EvaporativeCooler_Indirect_WetCoilFields::SecondaryAirFanTotalEfficiency, true);
  OS_ASSERT(value);
  return *value;
}

bool EvaporativeCoolerIndirectWetCoil_Impl::setSecondaryAirFanTotalEfficiency(double secondaryAirFanTotalEfficiency) {
  return setDouble(openstudio::EvaporativeCooler_Indirect_WetCoilFields::SecondaryAirFanTotalEfficiency, secondaryAirFanTotalEfficiency);
}

double EvaporativeCoolerIndirectWetCoil_Impl::secondaryAirFanDeltaPressure() const {
  const auto value = getDouble(openstudio::EvaporativeCooler_Indirect_WetCoilFields::SecondaryAirFanDeltaPressure, true);
  OS_ASSERT(value);
  return *value;
}

bool EvaporativeCoolerIndirectWetCoil_Impl::setSecondaryAirFanDeltaPressure(double secondaryAirFanDeltaPressure) {
  return setDouble(openstudio::EvaporativeCooler_Indirect_WetCoilFields::SecondaryAirFanDeltaPressure, secondaryAirFanDeltaPressure);
}

boost::optional<std::string> EvaporativeCoolerIndirectWetCoil_Impl::controlType() const {
  if (auto value = getString(openstudio::EvaporativeCooler_Indirect_WetCoilFields::ControlType, true)) {
    if (!value->empty()) {
      return value;
    }
  }
  return boost::none;
}

bool EvaporativeCoolerIndirectWetCoil_Impl::setControlType(const std::string& controlType) {
  return setString(openstudio::EvaporativeCooler_Indirect_WetCoilFields::ControlType, controlType);
}

void EvaporativeCoolerIndirectWetCoil_Impl::resetControlType() {
  OS_ASSERT(setString(openstudio::EvaporativeCooler_Indirect_WetCoilFields::ControlType, ""));
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
