/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ElectricLoadCenterInverterSimple.hpp"
#include "ElectricLoadCenterInverterSimple_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/ElectricLoadCenter_Inverter_Simple_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

ElectricLoadCenterInverterSimple::ElectricLoadCenterInverterSimple(const Model& model)
  : ModelObject(ElectricLoadCenterInverterSimple::iddObjectType(), model) {}

ElectricLoadCenterInverterSimple::ElectricLoadCenterInverterSimple(std::shared_ptr<detail::ElectricLoadCenterInverterSimple_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType ElectricLoadCenterInverterSimple::iddObjectType() {
  return IddObjectType::ElectricLoadCenter_Inverter_Simple;
}

boost::optional<double> ElectricLoadCenterInverterSimple::radiativeFraction() const {
  return getImpl<detail::ElectricLoadCenterInverterSimple_Impl>()->radiativeFraction();
}

bool ElectricLoadCenterInverterSimple::setRadiativeFraction(double radiativeFraction) {
  return getImpl<detail::ElectricLoadCenterInverterSimple_Impl>()->setRadiativeFraction(radiativeFraction);
}

void ElectricLoadCenterInverterSimple::resetRadiativeFraction() {
  getImpl<detail::ElectricLoadCenterInverterSimple_Impl>()->resetRadiativeFraction();
}

boost::optional<double> ElectricLoadCenterInverterSimple::inverterEfficiency() const {
  return getImpl<detail::ElectricLoadCenterInverterSimple_Impl>()->inverterEfficiency();
}

bool ElectricLoadCenterInverterSimple::setInverterEfficiency(double inverterEfficiency) {
  return getImpl<detail::ElectricLoadCenterInverterSimple_Impl>()->setInverterEfficiency(inverterEfficiency);
}

void ElectricLoadCenterInverterSimple::resetInverterEfficiency() {
  getImpl<detail::ElectricLoadCenterInverterSimple_Impl>()->resetInverterEfficiency();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

boost::optional<double> ElectricLoadCenterInverterSimple_Impl::radiativeFraction() const {
  return getDouble(openstudio::ElectricLoadCenter_Inverter_SimpleFields::RadiativeFraction, true);
}

bool ElectricLoadCenterInverterSimple_Impl::setRadiativeFraction(double radiativeFraction) {
  const bool result = setDouble(openstudio::ElectricLoadCenter_Inverter_SimpleFields::RadiativeFraction, radiativeFraction);
  return result;
}

void ElectricLoadCenterInverterSimple_Impl::resetRadiativeFraction() {
  OS_ASSERT(setString(openstudio::ElectricLoadCenter_Inverter_SimpleFields::RadiativeFraction, ""));
}

boost::optional<double> ElectricLoadCenterInverterSimple_Impl::inverterEfficiency() const {
  return getDouble(openstudio::ElectricLoadCenter_Inverter_SimpleFields::InverterEfficiency, true);
}

bool ElectricLoadCenterInverterSimple_Impl::setInverterEfficiency(double inverterEfficiency) {
  const bool result = setDouble(openstudio::ElectricLoadCenter_Inverter_SimpleFields::InverterEfficiency, inverterEfficiency);
  return result;
}

void ElectricLoadCenterInverterSimple_Impl::resetInverterEfficiency() {
  OS_ASSERT(setString(openstudio::ElectricLoadCenter_Inverter_SimpleFields::InverterEfficiency, ""));
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
