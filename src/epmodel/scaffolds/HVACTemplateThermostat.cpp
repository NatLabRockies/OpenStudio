/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "HVACTemplateThermostat.hpp"
#include "HVACTemplateThermostat_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/HVACTemplate_Thermostat_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  HVACTemplateThermostat::HVACTemplateThermostat(const Model& model) : ModelObject(HVACTemplateThermostat::iddObjectType(), model) {}

  HVACTemplateThermostat::HVACTemplateThermostat(std::shared_ptr<detail::HVACTemplateThermostat_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType HVACTemplateThermostat::iddObjectType() {
    return IddObjectType::HVACTemplate_Thermostat;
  }

  boost::optional<double> HVACTemplateThermostat::constantHeatingSetpoint() const {
    return getImpl<detail::HVACTemplateThermostat_Impl>()->constantHeatingSetpoint();
  }

  bool HVACTemplateThermostat::setConstantHeatingSetpoint(double constantHeatingSetpoint) {
    return getImpl<detail::HVACTemplateThermostat_Impl>()->setConstantHeatingSetpoint(constantHeatingSetpoint);
  }

  void HVACTemplateThermostat::resetConstantHeatingSetpoint() {
    getImpl<detail::HVACTemplateThermostat_Impl>()->resetConstantHeatingSetpoint();
  }

  namespace detail {

    boost::optional<double> HVACTemplateThermostat_Impl::constantHeatingSetpoint() const {
      return getDouble(openstudio::HVACTemplate_ThermostatFields::ConstantHeatingSetpoint, true);
    }

    bool HVACTemplateThermostat_Impl::setConstantHeatingSetpoint(double constantHeatingSetpoint) {
      return setDouble(openstudio::HVACTemplate_ThermostatFields::ConstantHeatingSetpoint, constantHeatingSetpoint);
    }

    void HVACTemplateThermostat_Impl::resetConstantHeatingSetpoint() {
      OS_ASSERT(setString(openstudio::HVACTemplate_ThermostatFields::ConstantHeatingSetpoint, ""));
    }

  }  // namespace detail

  boost::optional<double> HVACTemplateThermostat::constantCoolingSetpoint() const {
    return getImpl<detail::HVACTemplateThermostat_Impl>()->constantCoolingSetpoint();
  }

  bool HVACTemplateThermostat::setConstantCoolingSetpoint(double constantCoolingSetpoint) {
    return getImpl<detail::HVACTemplateThermostat_Impl>()->setConstantCoolingSetpoint(constantCoolingSetpoint);
  }

  void HVACTemplateThermostat::resetConstantCoolingSetpoint() {
    getImpl<detail::HVACTemplateThermostat_Impl>()->resetConstantCoolingSetpoint();
  }

  namespace detail {

    boost::optional<double> HVACTemplateThermostat_Impl::constantCoolingSetpoint() const {
      return getDouble(openstudio::HVACTemplate_ThermostatFields::ConstantCoolingSetpoint, true);
    }

    bool HVACTemplateThermostat_Impl::setConstantCoolingSetpoint(double constantCoolingSetpoint) {
      return setDouble(openstudio::HVACTemplate_ThermostatFields::ConstantCoolingSetpoint, constantCoolingSetpoint);
    }

    void HVACTemplateThermostat_Impl::resetConstantCoolingSetpoint() {
      OS_ASSERT(setString(openstudio::HVACTemplate_ThermostatFields::ConstantCoolingSetpoint, ""));
    }

  }  // namespace detail

}  // namespace epmodel
}  // namespace openstudio
