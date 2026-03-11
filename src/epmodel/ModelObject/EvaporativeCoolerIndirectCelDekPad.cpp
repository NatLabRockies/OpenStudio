/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "EvaporativeCoolerIndirectCelDekPad.hpp"
#include "EvaporativeCoolerIndirectCelDekPad_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/EvaporativeCooler_Indirect_CelDekPad_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

EvaporativeCoolerIndirectCelDekPad::EvaporativeCoolerIndirectCelDekPad(const Model& model)
  : ModelObject(EvaporativeCoolerIndirectCelDekPad::iddObjectType(), model) {}

EvaporativeCoolerIndirectCelDekPad::EvaporativeCoolerIndirectCelDekPad(
  std::shared_ptr<detail::EvaporativeCoolerIndirectCelDekPad_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType EvaporativeCoolerIndirectCelDekPad::iddObjectType() {
  return IddObjectType::EvaporativeCooler_Indirect_CelDekPad;
}

boost::optional<double> EvaporativeCoolerIndirectCelDekPad::directPadArea() const {
  return getImpl<detail::EvaporativeCoolerIndirectCelDekPad_Impl>()->directPadArea();
}

bool EvaporativeCoolerIndirectCelDekPad::isDirectPadAreaAutosized() const {
  return getImpl<detail::EvaporativeCoolerIndirectCelDekPad_Impl>()->isDirectPadAreaAutosized();
}

bool EvaporativeCoolerIndirectCelDekPad::setDirectPadArea(double directPadArea) {
  return getImpl<detail::EvaporativeCoolerIndirectCelDekPad_Impl>()->setDirectPadArea(directPadArea);
}

void EvaporativeCoolerIndirectCelDekPad::resetDirectPadArea() {
  getImpl<detail::EvaporativeCoolerIndirectCelDekPad_Impl>()->resetDirectPadArea();
}

void EvaporativeCoolerIndirectCelDekPad::autosizeDirectPadArea() {
  getImpl<detail::EvaporativeCoolerIndirectCelDekPad_Impl>()->autosizeDirectPadArea();
}

boost::optional<double> EvaporativeCoolerIndirectCelDekPad::directPadDepth() const {
  return getImpl<detail::EvaporativeCoolerIndirectCelDekPad_Impl>()->directPadDepth();
}

bool EvaporativeCoolerIndirectCelDekPad::isDirectPadDepthAutosized() const {
  return getImpl<detail::EvaporativeCoolerIndirectCelDekPad_Impl>()->isDirectPadDepthAutosized();
}

bool EvaporativeCoolerIndirectCelDekPad::setDirectPadDepth(double directPadDepth) {
  return getImpl<detail::EvaporativeCoolerIndirectCelDekPad_Impl>()->setDirectPadDepth(directPadDepth);
}

void EvaporativeCoolerIndirectCelDekPad::resetDirectPadDepth() {
  getImpl<detail::EvaporativeCoolerIndirectCelDekPad_Impl>()->resetDirectPadDepth();
}

void EvaporativeCoolerIndirectCelDekPad::autosizeDirectPadDepth() {
  getImpl<detail::EvaporativeCoolerIndirectCelDekPad_Impl>()->autosizeDirectPadDepth();
}

double EvaporativeCoolerIndirectCelDekPad::recirculatingWaterPumpPowerConsumption() const {
  return getImpl<detail::EvaporativeCoolerIndirectCelDekPad_Impl>()->recirculatingWaterPumpPowerConsumption();
}

bool EvaporativeCoolerIndirectCelDekPad::setRecirculatingWaterPumpPowerConsumption(double recirculatingWaterPumpPowerConsumption) {
  return getImpl<detail::EvaporativeCoolerIndirectCelDekPad_Impl>()->setRecirculatingWaterPumpPowerConsumption(
    recirculatingWaterPumpPowerConsumption);
}

double EvaporativeCoolerIndirectCelDekPad::secondaryAirFanFlowRate() const {
  return getImpl<detail::EvaporativeCoolerIndirectCelDekPad_Impl>()->secondaryAirFanFlowRate();
}

bool EvaporativeCoolerIndirectCelDekPad::setSecondaryAirFanFlowRate(double secondaryAirFanFlowRate) {
  return getImpl<detail::EvaporativeCoolerIndirectCelDekPad_Impl>()->setSecondaryAirFanFlowRate(secondaryAirFanFlowRate);
}

boost::optional<double> EvaporativeCoolerIndirectCelDekPad::secondaryAirFanTotalEfficiency() const {
  return getImpl<detail::EvaporativeCoolerIndirectCelDekPad_Impl>()->secondaryAirFanTotalEfficiency();
}

bool EvaporativeCoolerIndirectCelDekPad::setSecondaryAirFanTotalEfficiency(double secondaryAirFanTotalEfficiency) {
  return getImpl<detail::EvaporativeCoolerIndirectCelDekPad_Impl>()->setSecondaryAirFanTotalEfficiency(secondaryAirFanTotalEfficiency);
}

void EvaporativeCoolerIndirectCelDekPad::resetSecondaryAirFanTotalEfficiency() {
  getImpl<detail::EvaporativeCoolerIndirectCelDekPad_Impl>()->resetSecondaryAirFanTotalEfficiency();
}

double EvaporativeCoolerIndirectCelDekPad::secondaryAirFanDeltaPressure() const {
  return getImpl<detail::EvaporativeCoolerIndirectCelDekPad_Impl>()->secondaryAirFanDeltaPressure();
}

bool EvaporativeCoolerIndirectCelDekPad::setSecondaryAirFanDeltaPressure(double secondaryAirFanDeltaPressure) {
  return getImpl<detail::EvaporativeCoolerIndirectCelDekPad_Impl>()->setSecondaryAirFanDeltaPressure(secondaryAirFanDeltaPressure);
}

double EvaporativeCoolerIndirectCelDekPad::indirectHeatExchangerEffectiveness() const {
  return getImpl<detail::EvaporativeCoolerIndirectCelDekPad_Impl>()->indirectHeatExchangerEffectiveness();
}

bool EvaporativeCoolerIndirectCelDekPad::setIndirectHeatExchangerEffectiveness(double indirectHeatExchangerEffectiveness) {
  return getImpl<detail::EvaporativeCoolerIndirectCelDekPad_Impl>()->setIndirectHeatExchangerEffectiveness(
    indirectHeatExchangerEffectiveness);
}

boost::optional<std::string> EvaporativeCoolerIndirectCelDekPad::controlType() const {
  return getImpl<detail::EvaporativeCoolerIndirectCelDekPad_Impl>()->controlType();
}

bool EvaporativeCoolerIndirectCelDekPad::setControlType(const std::string& controlType) {
  return getImpl<detail::EvaporativeCoolerIndirectCelDekPad_Impl>()->setControlType(controlType);
}

void EvaporativeCoolerIndirectCelDekPad::resetControlType() {
  getImpl<detail::EvaporativeCoolerIndirectCelDekPad_Impl>()->resetControlType();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

boost::optional<double> EvaporativeCoolerIndirectCelDekPad_Impl::directPadArea() const {
  return getDouble(openstudio::EvaporativeCooler_Indirect_CelDekPadFields::DirectPadArea, true);
}

bool EvaporativeCoolerIndirectCelDekPad_Impl::isDirectPadAreaAutosized() const {
  const auto value = getString(openstudio::EvaporativeCooler_Indirect_CelDekPadFields::DirectPadArea, true);
  return value && openstudio::istringEqual(*value, "autosize");
}

bool EvaporativeCoolerIndirectCelDekPad_Impl::setDirectPadArea(double directPadArea) {
  return setDouble(openstudio::EvaporativeCooler_Indirect_CelDekPadFields::DirectPadArea, directPadArea);
}

void EvaporativeCoolerIndirectCelDekPad_Impl::resetDirectPadArea() {
  OS_ASSERT(setString(openstudio::EvaporativeCooler_Indirect_CelDekPadFields::DirectPadArea, ""));
}

void EvaporativeCoolerIndirectCelDekPad_Impl::autosizeDirectPadArea() {
  OS_ASSERT(setString(openstudio::EvaporativeCooler_Indirect_CelDekPadFields::DirectPadArea, "Autosize"));
}

boost::optional<double> EvaporativeCoolerIndirectCelDekPad_Impl::directPadDepth() const {
  return getDouble(openstudio::EvaporativeCooler_Indirect_CelDekPadFields::DirectPadDepth, true);
}

bool EvaporativeCoolerIndirectCelDekPad_Impl::isDirectPadDepthAutosized() const {
  const auto value = getString(openstudio::EvaporativeCooler_Indirect_CelDekPadFields::DirectPadDepth, true);
  return value && openstudio::istringEqual(*value, "autosize");
}

bool EvaporativeCoolerIndirectCelDekPad_Impl::setDirectPadDepth(double directPadDepth) {
  return setDouble(openstudio::EvaporativeCooler_Indirect_CelDekPadFields::DirectPadDepth, directPadDepth);
}

void EvaporativeCoolerIndirectCelDekPad_Impl::resetDirectPadDepth() {
  OS_ASSERT(setString(openstudio::EvaporativeCooler_Indirect_CelDekPadFields::DirectPadDepth, ""));
}

void EvaporativeCoolerIndirectCelDekPad_Impl::autosizeDirectPadDepth() {
  OS_ASSERT(setString(openstudio::EvaporativeCooler_Indirect_CelDekPadFields::DirectPadDepth, "Autosize"));
}

double EvaporativeCoolerIndirectCelDekPad_Impl::recirculatingWaterPumpPowerConsumption() const {
  const auto value = getDouble(openstudio::EvaporativeCooler_Indirect_CelDekPadFields::RecirculatingWaterPumpPowerConsumption, true);
  OS_ASSERT(value);
  return *value;
}

bool EvaporativeCoolerIndirectCelDekPad_Impl::setRecirculatingWaterPumpPowerConsumption(double recirculatingWaterPumpPowerConsumption) {
  return setDouble(openstudio::EvaporativeCooler_Indirect_CelDekPadFields::RecirculatingWaterPumpPowerConsumption,
                   recirculatingWaterPumpPowerConsumption);
}

double EvaporativeCoolerIndirectCelDekPad_Impl::secondaryAirFanFlowRate() const {
  const auto value = getDouble(openstudio::EvaporativeCooler_Indirect_CelDekPadFields::SecondaryAirFanFlowRate, true);
  OS_ASSERT(value);
  return *value;
}

bool EvaporativeCoolerIndirectCelDekPad_Impl::setSecondaryAirFanFlowRate(double secondaryAirFanFlowRate) {
  return setDouble(openstudio::EvaporativeCooler_Indirect_CelDekPadFields::SecondaryAirFanFlowRate, secondaryAirFanFlowRate);
}

boost::optional<double> EvaporativeCoolerIndirectCelDekPad_Impl::secondaryAirFanTotalEfficiency() const {
  return getDouble(openstudio::EvaporativeCooler_Indirect_CelDekPadFields::SecondaryAirFanTotalEfficiency, true);
}

bool EvaporativeCoolerIndirectCelDekPad_Impl::setSecondaryAirFanTotalEfficiency(double secondaryAirFanTotalEfficiency) {
  return setDouble(openstudio::EvaporativeCooler_Indirect_CelDekPadFields::SecondaryAirFanTotalEfficiency, secondaryAirFanTotalEfficiency);
}

void EvaporativeCoolerIndirectCelDekPad_Impl::resetSecondaryAirFanTotalEfficiency() {
  OS_ASSERT(setString(openstudio::EvaporativeCooler_Indirect_CelDekPadFields::SecondaryAirFanTotalEfficiency, ""));
}

double EvaporativeCoolerIndirectCelDekPad_Impl::secondaryAirFanDeltaPressure() const {
  const auto value = getDouble(openstudio::EvaporativeCooler_Indirect_CelDekPadFields::SecondaryAirFanDeltaPressure, true);
  OS_ASSERT(value);
  return *value;
}

bool EvaporativeCoolerIndirectCelDekPad_Impl::setSecondaryAirFanDeltaPressure(double secondaryAirFanDeltaPressure) {
  return setDouble(openstudio::EvaporativeCooler_Indirect_CelDekPadFields::SecondaryAirFanDeltaPressure, secondaryAirFanDeltaPressure);
}

double EvaporativeCoolerIndirectCelDekPad_Impl::indirectHeatExchangerEffectiveness() const {
  const auto value = getDouble(openstudio::EvaporativeCooler_Indirect_CelDekPadFields::IndirectHeatExchangerEffectiveness, true);
  OS_ASSERT(value);
  return *value;
}

bool EvaporativeCoolerIndirectCelDekPad_Impl::setIndirectHeatExchangerEffectiveness(double indirectHeatExchangerEffectiveness) {
  return setDouble(openstudio::EvaporativeCooler_Indirect_CelDekPadFields::IndirectHeatExchangerEffectiveness,
                   indirectHeatExchangerEffectiveness);
}

boost::optional<std::string> EvaporativeCoolerIndirectCelDekPad_Impl::controlType() const {
  if (auto value = getString(openstudio::EvaporativeCooler_Indirect_CelDekPadFields::ControlType, true)) {
    if (!value->empty()) {
      return value;
    }
  }
  return boost::none;
}

bool EvaporativeCoolerIndirectCelDekPad_Impl::setControlType(const std::string& controlType) {
  return setString(openstudio::EvaporativeCooler_Indirect_CelDekPadFields::ControlType, controlType);
}

void EvaporativeCoolerIndirectCelDekPad_Impl::resetControlType() {
  OS_ASSERT(setString(openstudio::EvaporativeCooler_Indirect_CelDekPadFields::ControlType, ""));
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
