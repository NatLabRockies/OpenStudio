/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "EvaporativeCoolerDirectCelDekPad.hpp"
#include "EvaporativeCoolerDirectCelDekPad_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/EvaporativeCooler_Direct_CelDekPad_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

EvaporativeCoolerDirectCelDekPad::EvaporativeCoolerDirectCelDekPad(const Model& model)
  : ModelObject(EvaporativeCoolerDirectCelDekPad::iddObjectType(), model) {}

EvaporativeCoolerDirectCelDekPad::EvaporativeCoolerDirectCelDekPad(std::shared_ptr<detail::EvaporativeCoolerDirectCelDekPad_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType EvaporativeCoolerDirectCelDekPad::iddObjectType() {
  return IddObjectType::EvaporativeCooler_Direct_CelDekPad;
}

boost::optional<double> EvaporativeCoolerDirectCelDekPad::directPadArea() const {
  return getImpl<detail::EvaporativeCoolerDirectCelDekPad_Impl>()->directPadArea();
}

bool EvaporativeCoolerDirectCelDekPad::isDirectPadAreaAutosized() const {
  return getImpl<detail::EvaporativeCoolerDirectCelDekPad_Impl>()->isDirectPadAreaAutosized();
}

bool EvaporativeCoolerDirectCelDekPad::setDirectPadArea(double directPadArea) {
  return getImpl<detail::EvaporativeCoolerDirectCelDekPad_Impl>()->setDirectPadArea(directPadArea);
}

void EvaporativeCoolerDirectCelDekPad::resetDirectPadArea() {
  getImpl<detail::EvaporativeCoolerDirectCelDekPad_Impl>()->resetDirectPadArea();
}

void EvaporativeCoolerDirectCelDekPad::autosizeDirectPadArea() {
  getImpl<detail::EvaporativeCoolerDirectCelDekPad_Impl>()->autosizeDirectPadArea();
}

boost::optional<double> EvaporativeCoolerDirectCelDekPad::directPadDepth() const {
  return getImpl<detail::EvaporativeCoolerDirectCelDekPad_Impl>()->directPadDepth();
}

bool EvaporativeCoolerDirectCelDekPad::isDirectPadDepthAutosized() const {
  return getImpl<detail::EvaporativeCoolerDirectCelDekPad_Impl>()->isDirectPadDepthAutosized();
}

bool EvaporativeCoolerDirectCelDekPad::setDirectPadDepth(double directPadDepth) {
  return getImpl<detail::EvaporativeCoolerDirectCelDekPad_Impl>()->setDirectPadDepth(directPadDepth);
}

void EvaporativeCoolerDirectCelDekPad::resetDirectPadDepth() {
  getImpl<detail::EvaporativeCoolerDirectCelDekPad_Impl>()->resetDirectPadDepth();
}

void EvaporativeCoolerDirectCelDekPad::autosizeDirectPadDepth() {
  getImpl<detail::EvaporativeCoolerDirectCelDekPad_Impl>()->autosizeDirectPadDepth();
}

double EvaporativeCoolerDirectCelDekPad::recirculatingWaterPumpPowerConsumption() const {
  return getImpl<detail::EvaporativeCoolerDirectCelDekPad_Impl>()->recirculatingWaterPumpPowerConsumption();
}

bool EvaporativeCoolerDirectCelDekPad::setRecirculatingWaterPumpPowerConsumption(double recirculatingWaterPumpPowerConsumption) {
  return getImpl<detail::EvaporativeCoolerDirectCelDekPad_Impl>()->setRecirculatingWaterPumpPowerConsumption(
    recirculatingWaterPumpPowerConsumption);
}

boost::optional<std::string> EvaporativeCoolerDirectCelDekPad::controlType() const {
  return getImpl<detail::EvaporativeCoolerDirectCelDekPad_Impl>()->controlType();
}

bool EvaporativeCoolerDirectCelDekPad::setControlType(const std::string& controlType) {
  return getImpl<detail::EvaporativeCoolerDirectCelDekPad_Impl>()->setControlType(controlType);
}

void EvaporativeCoolerDirectCelDekPad::resetControlType() {
  getImpl<detail::EvaporativeCoolerDirectCelDekPad_Impl>()->resetControlType();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

boost::optional<double> EvaporativeCoolerDirectCelDekPad_Impl::directPadArea() const {
  return getDouble(openstudio::EvaporativeCooler_Direct_CelDekPadFields::DirectPadArea, true);
}

bool EvaporativeCoolerDirectCelDekPad_Impl::isDirectPadAreaAutosized() const {
  const auto value = getString(openstudio::EvaporativeCooler_Direct_CelDekPadFields::DirectPadArea, true);
  return value && openstudio::istringEqual(*value, "autosize");
}

bool EvaporativeCoolerDirectCelDekPad_Impl::setDirectPadArea(double directPadArea) {
  return setDouble(openstudio::EvaporativeCooler_Direct_CelDekPadFields::DirectPadArea, directPadArea);
}

void EvaporativeCoolerDirectCelDekPad_Impl::resetDirectPadArea() {
  OS_ASSERT(setString(openstudio::EvaporativeCooler_Direct_CelDekPadFields::DirectPadArea, ""));
}

void EvaporativeCoolerDirectCelDekPad_Impl::autosizeDirectPadArea() {
  OS_ASSERT(setString(openstudio::EvaporativeCooler_Direct_CelDekPadFields::DirectPadArea, "Autosize"));
}

boost::optional<double> EvaporativeCoolerDirectCelDekPad_Impl::directPadDepth() const {
  return getDouble(openstudio::EvaporativeCooler_Direct_CelDekPadFields::DirectPadDepth, true);
}

bool EvaporativeCoolerDirectCelDekPad_Impl::isDirectPadDepthAutosized() const {
  const auto value = getString(openstudio::EvaporativeCooler_Direct_CelDekPadFields::DirectPadDepth, true);
  return value && openstudio::istringEqual(*value, "autosize");
}

bool EvaporativeCoolerDirectCelDekPad_Impl::setDirectPadDepth(double directPadDepth) {
  return setDouble(openstudio::EvaporativeCooler_Direct_CelDekPadFields::DirectPadDepth, directPadDepth);
}

void EvaporativeCoolerDirectCelDekPad_Impl::resetDirectPadDepth() {
  OS_ASSERT(setString(openstudio::EvaporativeCooler_Direct_CelDekPadFields::DirectPadDepth, ""));
}

void EvaporativeCoolerDirectCelDekPad_Impl::autosizeDirectPadDepth() {
  OS_ASSERT(setString(openstudio::EvaporativeCooler_Direct_CelDekPadFields::DirectPadDepth, "Autosize"));
}

double EvaporativeCoolerDirectCelDekPad_Impl::recirculatingWaterPumpPowerConsumption() const {
  const auto value = getDouble(openstudio::EvaporativeCooler_Direct_CelDekPadFields::RecirculatingWaterPumpPowerConsumption, true);
  OS_ASSERT(value);
  return *value;
}

bool EvaporativeCoolerDirectCelDekPad_Impl::setRecirculatingWaterPumpPowerConsumption(double recirculatingWaterPumpPowerConsumption) {
  return setDouble(openstudio::EvaporativeCooler_Direct_CelDekPadFields::RecirculatingWaterPumpPowerConsumption,
                   recirculatingWaterPumpPowerConsumption);
}

boost::optional<std::string> EvaporativeCoolerDirectCelDekPad_Impl::controlType() const {
  if (auto value = getString(openstudio::EvaporativeCooler_Direct_CelDekPadFields::ControlType, true)) {
    if (!value->empty()) {
      return value;
    }
  }
  return boost::none;
}

bool EvaporativeCoolerDirectCelDekPad_Impl::setControlType(const std::string& controlType) {
  return setString(openstudio::EvaporativeCooler_Direct_CelDekPadFields::ControlType, controlType);
}

void EvaporativeCoolerDirectCelDekPad_Impl::resetControlType() {
  OS_ASSERT(setString(openstudio::EvaporativeCooler_Direct_CelDekPadFields::ControlType, ""));
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
