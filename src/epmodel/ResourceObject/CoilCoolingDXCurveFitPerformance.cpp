/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ResourceObject/CoilCoolingDXCurveFitPerformance.hpp"
#include "ResourceObject/CoilCoolingDXCurveFitPerformance_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/Coil_Cooling_DX_CurveFit_Performance_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

CoilCoolingDXCurveFitPerformance::CoilCoolingDXCurveFitPerformance(const Model& model)
  : ModelObject(CoilCoolingDXCurveFitPerformance::iddObjectType(), model) {}

CoilCoolingDXCurveFitPerformance::CoilCoolingDXCurveFitPerformance(std::shared_ptr<detail::CoilCoolingDXCurveFitPerformance_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType CoilCoolingDXCurveFitPerformance::iddObjectType() {
  return IddObjectType::Coil_Cooling_DX_CurveFit_Performance;
}

std::vector<std::string> CoilCoolingDXCurveFitPerformance::capacityControlMethodValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::Coil_Cooling_DX_CurveFit_PerformanceFields::CapacityControlMethod);
}

std::vector<std::string> CoilCoolingDXCurveFitPerformance::compressorFuelTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::Coil_Cooling_DX_CurveFit_PerformanceFields::CompressorFuelType);
}

std::vector<std::string> CoilCoolingDXCurveFitPerformance::validCapacityControlMethodValues() {
  return capacityControlMethodValues();
}

std::vector<std::string> CoilCoolingDXCurveFitPerformance::validCompressorFuelTypeValues() {
  return compressorFuelTypeValues();
}

double CoilCoolingDXCurveFitPerformance::crankcaseHeaterCapacity() const {
  return getImpl<detail::CoilCoolingDXCurveFitPerformance_Impl>()->crankcaseHeaterCapacity();
}

bool CoilCoolingDXCurveFitPerformance::setCrankcaseHeaterCapacity(double crankcaseHeaterCapacity) {
  return getImpl<detail::CoilCoolingDXCurveFitPerformance_Impl>()->setCrankcaseHeaterCapacity(crankcaseHeaterCapacity);
}

double CoilCoolingDXCurveFitPerformance::minimumOutdoorDryBulbTemperatureforCompressorOperation() const {
  return getImpl<detail::CoilCoolingDXCurveFitPerformance_Impl>()->minimumOutdoorDryBulbTemperatureforCompressorOperation();
}

bool CoilCoolingDXCurveFitPerformance::setMinimumOutdoorDryBulbTemperatureforCompressorOperation(
  double minimumOutdoorDryBulbTemperatureforCompressorOperation) {
  return getImpl<detail::CoilCoolingDXCurveFitPerformance_Impl>()->setMinimumOutdoorDryBulbTemperatureforCompressorOperation(
    minimumOutdoorDryBulbTemperatureforCompressorOperation);
}

double CoilCoolingDXCurveFitPerformance::maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation() const {
  return getImpl<detail::CoilCoolingDXCurveFitPerformance_Impl>()->maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation();
}

bool CoilCoolingDXCurveFitPerformance::setMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation(
  double maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation) {
  return getImpl<detail::CoilCoolingDXCurveFitPerformance_Impl>()->setMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation(
    maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation);
}

double CoilCoolingDXCurveFitPerformance::unitInternalStaticAirPressure() const {
  return getImpl<detail::CoilCoolingDXCurveFitPerformance_Impl>()->unitInternalStaticAirPressure();
}

bool CoilCoolingDXCurveFitPerformance::setUnitInternalStaticAirPressure(double unitInternalStaticAirPressure) {
  return getImpl<detail::CoilCoolingDXCurveFitPerformance_Impl>()->setUnitInternalStaticAirPressure(unitInternalStaticAirPressure);
}

std::string CoilCoolingDXCurveFitPerformance::capacityControlMethod() const {
  return getImpl<detail::CoilCoolingDXCurveFitPerformance_Impl>()->capacityControlMethod();
}

bool CoilCoolingDXCurveFitPerformance::setCapacityControlMethod(const std::string& capacityControlMethod) {
  return getImpl<detail::CoilCoolingDXCurveFitPerformance_Impl>()->setCapacityControlMethod(capacityControlMethod);
}

double CoilCoolingDXCurveFitPerformance::evaporativeCondenserBasinHeaterCapacity() const {
  return getImpl<detail::CoilCoolingDXCurveFitPerformance_Impl>()->evaporativeCondenserBasinHeaterCapacity();
}

bool CoilCoolingDXCurveFitPerformance::setEvaporativeCondenserBasinHeaterCapacity(double evaporativeCondenserBasinHeaterCapacity) {
  return getImpl<detail::CoilCoolingDXCurveFitPerformance_Impl>()->setEvaporativeCondenserBasinHeaterCapacity(
    evaporativeCondenserBasinHeaterCapacity);
}

double CoilCoolingDXCurveFitPerformance::evaporativeCondenserBasinHeaterSetpointTemperature() const {
  return getImpl<detail::CoilCoolingDXCurveFitPerformance_Impl>()->evaporativeCondenserBasinHeaterSetpointTemperature();
}

bool CoilCoolingDXCurveFitPerformance::setEvaporativeCondenserBasinHeaterSetpointTemperature(
  double evaporativeCondenserBasinHeaterSetpointTemperature) {
  return getImpl<detail::CoilCoolingDXCurveFitPerformance_Impl>()->setEvaporativeCondenserBasinHeaterSetpointTemperature(
    evaporativeCondenserBasinHeaterSetpointTemperature);
}

std::string CoilCoolingDXCurveFitPerformance::compressorFuelType() const {
  return getImpl<detail::CoilCoolingDXCurveFitPerformance_Impl>()->compressorFuelType();
}

bool CoilCoolingDXCurveFitPerformance::setCompressorFuelType(const std::string& compressorFuelType) {
  return getImpl<detail::CoilCoolingDXCurveFitPerformance_Impl>()->setCompressorFuelType(compressorFuelType);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

double CoilCoolingDXCurveFitPerformance_Impl::crankcaseHeaterCapacity() const {
  const auto value = getDouble(openstudio::Coil_Cooling_DX_CurveFit_PerformanceFields::CrankcaseHeaterCapacity, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilCoolingDXCurveFitPerformance_Impl::setCrankcaseHeaterCapacity(double crankcaseHeaterCapacity) {
  return setDouble(openstudio::Coil_Cooling_DX_CurveFit_PerformanceFields::CrankcaseHeaterCapacity, crankcaseHeaterCapacity);
}

double CoilCoolingDXCurveFitPerformance_Impl::minimumOutdoorDryBulbTemperatureforCompressorOperation() const {
  const auto value =
    getDouble(openstudio::Coil_Cooling_DX_CurveFit_PerformanceFields::MinimumOutdoorDryBulbTemperatureforCompressorOperation, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilCoolingDXCurveFitPerformance_Impl::setMinimumOutdoorDryBulbTemperatureforCompressorOperation(
  double minimumOutdoorDryBulbTemperatureforCompressorOperation) {
  return setDouble(openstudio::Coil_Cooling_DX_CurveFit_PerformanceFields::MinimumOutdoorDryBulbTemperatureforCompressorOperation,
                   minimumOutdoorDryBulbTemperatureforCompressorOperation);
}

double CoilCoolingDXCurveFitPerformance_Impl::maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation() const {
  const auto value = getDouble(openstudio::Coil_Cooling_DX_CurveFit_PerformanceFields::MaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation,
                               true);
  OS_ASSERT(value);
  return *value;
}

bool CoilCoolingDXCurveFitPerformance_Impl::setMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation(
  double maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation) {
  return setDouble(openstudio::Coil_Cooling_DX_CurveFit_PerformanceFields::MaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation,
                   maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation);
}

double CoilCoolingDXCurveFitPerformance_Impl::unitInternalStaticAirPressure() const {
  const auto value = getDouble(openstudio::Coil_Cooling_DX_CurveFit_PerformanceFields::UnitInternalStaticAirPressure, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilCoolingDXCurveFitPerformance_Impl::setUnitInternalStaticAirPressure(double unitInternalStaticAirPressure) {
  return setDouble(openstudio::Coil_Cooling_DX_CurveFit_PerformanceFields::UnitInternalStaticAirPressure, unitInternalStaticAirPressure);
}

std::string CoilCoolingDXCurveFitPerformance_Impl::capacityControlMethod() const {
  const auto value = getString(openstudio::Coil_Cooling_DX_CurveFit_PerformanceFields::CapacityControlMethod, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilCoolingDXCurveFitPerformance_Impl::setCapacityControlMethod(const std::string& capacityControlMethod) {
  return setString(openstudio::Coil_Cooling_DX_CurveFit_PerformanceFields::CapacityControlMethod, capacityControlMethod);
}

double CoilCoolingDXCurveFitPerformance_Impl::evaporativeCondenserBasinHeaterCapacity() const {
  const auto value = getDouble(openstudio::Coil_Cooling_DX_CurveFit_PerformanceFields::EvaporativeCondenserBasinHeaterCapacity, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilCoolingDXCurveFitPerformance_Impl::setEvaporativeCondenserBasinHeaterCapacity(double evaporativeCondenserBasinHeaterCapacity) {
  return setDouble(openstudio::Coil_Cooling_DX_CurveFit_PerformanceFields::EvaporativeCondenserBasinHeaterCapacity,
                   evaporativeCondenserBasinHeaterCapacity);
}

double CoilCoolingDXCurveFitPerformance_Impl::evaporativeCondenserBasinHeaterSetpointTemperature() const {
  const auto value =
    getDouble(openstudio::Coil_Cooling_DX_CurveFit_PerformanceFields::EvaporativeCondenserBasinHeaterSetpointTemperature, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilCoolingDXCurveFitPerformance_Impl::setEvaporativeCondenserBasinHeaterSetpointTemperature(
  double evaporativeCondenserBasinHeaterSetpointTemperature) {
  return setDouble(openstudio::Coil_Cooling_DX_CurveFit_PerformanceFields::EvaporativeCondenserBasinHeaterSetpointTemperature,
                   evaporativeCondenserBasinHeaterSetpointTemperature);
}

std::string CoilCoolingDXCurveFitPerformance_Impl::compressorFuelType() const {
  const auto value = getString(openstudio::Coil_Cooling_DX_CurveFit_PerformanceFields::CompressorFuelType, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilCoolingDXCurveFitPerformance_Impl::setCompressorFuelType(const std::string& compressorFuelType) {
  return setString(openstudio::Coil_Cooling_DX_CurveFit_PerformanceFields::CompressorFuelType, compressorFuelType);
}

std::vector<std::string> CoilCoolingDXCurveFitPerformance_Impl::capacityControlMethodValues() const {
  return openstudio::epmodel::CoilCoolingDXCurveFitPerformance::capacityControlMethodValues();
}

std::vector<std::string> CoilCoolingDXCurveFitPerformance_Impl::compressorFuelTypeValues() const {
  return openstudio::epmodel::CoilCoolingDXCurveFitPerformance::compressorFuelTypeValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
