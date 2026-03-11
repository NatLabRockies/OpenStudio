/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "EnergyManagementSystemSensor.hpp"
#include "EnergyManagementSystemSensor_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/EnergyManagementSystem_Sensor_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

EnergyManagementSystemSensor::EnergyManagementSystemSensor(const Model& model) : ModelObject(EnergyManagementSystemSensor::iddObjectType(), model) {}

EnergyManagementSystemSensor::EnergyManagementSystemSensor(std::shared_ptr<detail::EnergyManagementSystemSensor_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType EnergyManagementSystemSensor::iddObjectType() {
  return IddObjectType::EnergyManagementSystem_Sensor;
}

boost::optional<std::string> EnergyManagementSystemSensor::keyName() const {
  return getImpl<detail::EnergyManagementSystemSensor_Impl>()->keyName();
}

bool EnergyManagementSystemSensor::setKeyName(const std::string& keyName) {
  return getImpl<detail::EnergyManagementSystemSensor_Impl>()->setKeyName(keyName);
}

void EnergyManagementSystemSensor::resetKeyName() {
  getImpl<detail::EnergyManagementSystemSensor_Impl>()->resetKeyName();
}

std::string EnergyManagementSystemSensor::outputVariableOrMeterName() const {
  return getImpl<detail::EnergyManagementSystemSensor_Impl>()->outputVariableOrMeterName();
}

bool EnergyManagementSystemSensor::setOutputVariableOrMeterName(const std::string& outputVariableOrMeterName) {
  return getImpl<detail::EnergyManagementSystemSensor_Impl>()->setOutputVariableOrMeterName(outputVariableOrMeterName);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

boost::optional<std::string> EnergyManagementSystemSensor_Impl::keyName() const {
  return getString(openstudio::EnergyManagementSystem_SensorFields::Output_VariableorOutput_MeterIndexKeyName, true);
}

bool EnergyManagementSystemSensor_Impl::setKeyName(const std::string& keyName) {
  const bool result = setString(openstudio::EnergyManagementSystem_SensorFields::Output_VariableorOutput_MeterIndexKeyName, keyName);
  OS_ASSERT(result);
  return result;
}

void EnergyManagementSystemSensor_Impl::resetKeyName() {
  OS_ASSERT(setString(openstudio::EnergyManagementSystem_SensorFields::Output_VariableorOutput_MeterIndexKeyName, ""));
}

std::string EnergyManagementSystemSensor_Impl::outputVariableOrMeterName() const {
  const auto value = getString(openstudio::EnergyManagementSystem_SensorFields::Output_VariableorOutput_MeterName, true);
  OS_ASSERT(value);
  return *value;
}

bool EnergyManagementSystemSensor_Impl::setOutputVariableOrMeterName(const std::string& outputVariableOrMeterName) {
  const bool result = setString(openstudio::EnergyManagementSystem_SensorFields::Output_VariableorOutput_MeterName, outputVariableOrMeterName);
  OS_ASSERT(result);
  return result;
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
