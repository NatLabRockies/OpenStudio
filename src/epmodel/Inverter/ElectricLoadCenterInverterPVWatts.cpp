/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ElectricLoadCenterInverterPVWatts.hpp"
#include "ElectricLoadCenterInverterPVWatts_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/ElectricLoadCenter_Inverter_PVWatts_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

ElectricLoadCenterInverterPVWatts::ElectricLoadCenterInverterPVWatts(const Model& model)
  : ModelObject(ElectricLoadCenterInverterPVWatts::iddObjectType(), model) {}

ElectricLoadCenterInverterPVWatts::ElectricLoadCenterInverterPVWatts(std::shared_ptr<detail::ElectricLoadCenterInverterPVWatts_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType ElectricLoadCenterInverterPVWatts::iddObjectType() {
  return IddObjectType::ElectricLoadCenter_Inverter_PVWatts;
}

double ElectricLoadCenterInverterPVWatts::dcToACSizeRatio() const {
  return getImpl<detail::ElectricLoadCenterInverterPVWatts_Impl>()->dcToACSizeRatio();
}

bool ElectricLoadCenterInverterPVWatts::isDCToACSizeRatioDefaulted() const {
  return getImpl<detail::ElectricLoadCenterInverterPVWatts_Impl>()->isDCToACSizeRatioDefaulted();
}

bool ElectricLoadCenterInverterPVWatts::setDCToACSizeRatio(double dcToACSizeRatio) {
  return getImpl<detail::ElectricLoadCenterInverterPVWatts_Impl>()->setDCToACSizeRatio(dcToACSizeRatio);
}

void ElectricLoadCenterInverterPVWatts::resetDCToACSizeRatio() {
  getImpl<detail::ElectricLoadCenterInverterPVWatts_Impl>()->resetDCToACSizeRatio();
}

double ElectricLoadCenterInverterPVWatts::inverterEfficiency() const {
  return getImpl<detail::ElectricLoadCenterInverterPVWatts_Impl>()->inverterEfficiency();
}

bool ElectricLoadCenterInverterPVWatts::isInverterEfficiencyDefaulted() const {
  return getImpl<detail::ElectricLoadCenterInverterPVWatts_Impl>()->isInverterEfficiencyDefaulted();
}

bool ElectricLoadCenterInverterPVWatts::setInverterEfficiency(double inverterEfficiency) {
  return getImpl<detail::ElectricLoadCenterInverterPVWatts_Impl>()->setInverterEfficiency(inverterEfficiency);
}

void ElectricLoadCenterInverterPVWatts::resetInverterEfficiency() {
  getImpl<detail::ElectricLoadCenterInverterPVWatts_Impl>()->resetInverterEfficiency();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

double ElectricLoadCenterInverterPVWatts_Impl::dcToACSizeRatio() const {
  const auto value = getDouble(openstudio::ElectricLoadCenter_Inverter_PVWattsFields::DCtoACSizeRatio, true);
  OS_ASSERT(value);
  return *value;
}

bool ElectricLoadCenterInverterPVWatts_Impl::isDCToACSizeRatioDefaulted() const {
  return isEmpty(openstudio::ElectricLoadCenter_Inverter_PVWattsFields::DCtoACSizeRatio);
}

bool ElectricLoadCenterInverterPVWatts_Impl::setDCToACSizeRatio(double dcToACSizeRatio) {
  const bool result = setDouble(openstudio::ElectricLoadCenter_Inverter_PVWattsFields::DCtoACSizeRatio, dcToACSizeRatio);
  OS_ASSERT(result);
  return result;
}

void ElectricLoadCenterInverterPVWatts_Impl::resetDCToACSizeRatio() {
  OS_ASSERT(setString(openstudio::ElectricLoadCenter_Inverter_PVWattsFields::DCtoACSizeRatio, ""));
}

double ElectricLoadCenterInverterPVWatts_Impl::inverterEfficiency() const {
  const auto value = getDouble(openstudio::ElectricLoadCenter_Inverter_PVWattsFields::InverterEfficiency, true);
  OS_ASSERT(value);
  return *value;
}

bool ElectricLoadCenterInverterPVWatts_Impl::isInverterEfficiencyDefaulted() const {
  return isEmpty(openstudio::ElectricLoadCenter_Inverter_PVWattsFields::InverterEfficiency);
}

bool ElectricLoadCenterInverterPVWatts_Impl::setInverterEfficiency(double inverterEfficiency) {
  const bool result = setDouble(openstudio::ElectricLoadCenter_Inverter_PVWattsFields::InverterEfficiency, inverterEfficiency);
  OS_ASSERT(result);
  return result;
}

void ElectricLoadCenterInverterPVWatts_Impl::resetInverterEfficiency() {
  OS_ASSERT(setString(openstudio::ElectricLoadCenter_Inverter_PVWattsFields::InverterEfficiency, ""));
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
