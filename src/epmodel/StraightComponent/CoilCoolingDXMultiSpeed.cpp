/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/CoilCoolingDXMultiSpeed.hpp"
#include "StraightComponent/CoilCoolingDXMultiSpeed_Impl.hpp"

#include "Loop/AirLoopHVAC.hpp"
#include "Model.hpp"
#include "StraightComponent/Node.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/Coil_Cooling_DX_MultiSpeed_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

CoilCoolingDXMultiSpeed::CoilCoolingDXMultiSpeed(const Model& model)
  : StraightComponent(CoilCoolingDXMultiSpeed::iddObjectType(), model) {
  // Preserve model-constructor scalar defaults while excluding relationship and stage fields.
  OS_ASSERT(setCondenserType("AirCooled"));
  OS_ASSERT(setApplyPartLoadFractiontoSpeedsGreaterthan1(false));
  OS_ASSERT(setCrankcaseHeaterCapacity(0.0));
  OS_ASSERT(setMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation(10.0));
  OS_ASSERT(setMinimumOutdoorDryBulbTemperatureforCompressorOperation(-25.0));
  OS_ASSERT(setBasinHeaterCapacity(0.0));
  OS_ASSERT(setBasinHeaterSetpointTemperature(2.0));
  OS_ASSERT(setFuelType("NaturalGas"));
}

CoilCoolingDXMultiSpeed::CoilCoolingDXMultiSpeed(std::shared_ptr<detail::CoilCoolingDXMultiSpeed_Impl> impl)
  : StraightComponent(std::move(impl)) {}

IddObjectType CoilCoolingDXMultiSpeed::iddObjectType() {
  return IddObjectType::Coil_Cooling_DX_MultiSpeed;
}

std::vector<std::string> CoilCoolingDXMultiSpeed::condenserTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::Coil_Cooling_DX_MultiSpeedFields::CondenserType);
}

std::vector<std::string> CoilCoolingDXMultiSpeed::fuelTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::Coil_Cooling_DX_MultiSpeedFields::FuelType);
}

bool CoilCoolingDXMultiSpeed::addToNode(Node& node) {
  return getImpl<detail::CoilCoolingDXMultiSpeed_Impl>()->addToNode(node);
}

std::string CoilCoolingDXMultiSpeed::condenserType() const {
  return getImpl<detail::CoilCoolingDXMultiSpeed_Impl>()->condenserType();
}

bool CoilCoolingDXMultiSpeed::setCondenserType(const std::string& condenserType) {
  return getImpl<detail::CoilCoolingDXMultiSpeed_Impl>()->setCondenserType(condenserType);
}

bool CoilCoolingDXMultiSpeed::applyPartLoadFractiontoSpeedsGreaterthan1() const {
  return getImpl<detail::CoilCoolingDXMultiSpeed_Impl>()->applyPartLoadFractiontoSpeedsGreaterthan1();
}

bool CoilCoolingDXMultiSpeed::setApplyPartLoadFractiontoSpeedsGreaterthan1(bool applyPartLoadFractiontoSpeedsGreaterthan1) {
  return getImpl<detail::CoilCoolingDXMultiSpeed_Impl>()->setApplyPartLoadFractiontoSpeedsGreaterthan1(applyPartLoadFractiontoSpeedsGreaterthan1);
}

bool CoilCoolingDXMultiSpeed::applyLatentDegradationtoSpeedsGreaterthan1() const {
  return getImpl<detail::CoilCoolingDXMultiSpeed_Impl>()->applyLatentDegradationtoSpeedsGreaterthan1();
}

bool CoilCoolingDXMultiSpeed::isApplyLatentDegradationtoSpeedsGreaterthan1Defaulted() const {
  return getImpl<detail::CoilCoolingDXMultiSpeed_Impl>()->isApplyLatentDegradationtoSpeedsGreaterthan1Defaulted();
}

bool CoilCoolingDXMultiSpeed::setApplyLatentDegradationtoSpeedsGreaterthan1(bool applyLatentDegradationtoSpeedsGreaterthan1) {
  return getImpl<detail::CoilCoolingDXMultiSpeed_Impl>()->setApplyLatentDegradationtoSpeedsGreaterthan1(applyLatentDegradationtoSpeedsGreaterthan1);
}

void CoilCoolingDXMultiSpeed::resetApplyLatentDegradationtoSpeedsGreaterthan1() {
  getImpl<detail::CoilCoolingDXMultiSpeed_Impl>()->resetApplyLatentDegradationtoSpeedsGreaterthan1();
}

double CoilCoolingDXMultiSpeed::crankcaseHeaterCapacity() const {
  return getImpl<detail::CoilCoolingDXMultiSpeed_Impl>()->crankcaseHeaterCapacity();
}

bool CoilCoolingDXMultiSpeed::setCrankcaseHeaterCapacity(double crankcaseHeaterCapacity) {
  return getImpl<detail::CoilCoolingDXMultiSpeed_Impl>()->setCrankcaseHeaterCapacity(crankcaseHeaterCapacity);
}

double CoilCoolingDXMultiSpeed::maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation() const {
  return getImpl<detail::CoilCoolingDXMultiSpeed_Impl>()->maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation();
}

bool CoilCoolingDXMultiSpeed::setMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation(
  double maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation) {
  return getImpl<detail::CoilCoolingDXMultiSpeed_Impl>()->setMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation(
    maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation);
}

double CoilCoolingDXMultiSpeed::basinHeaterCapacity() const {
  return getImpl<detail::CoilCoolingDXMultiSpeed_Impl>()->basinHeaterCapacity();
}

bool CoilCoolingDXMultiSpeed::setBasinHeaterCapacity(double basinHeaterCapacity) {
  return getImpl<detail::CoilCoolingDXMultiSpeed_Impl>()->setBasinHeaterCapacity(basinHeaterCapacity);
}

double CoilCoolingDXMultiSpeed::basinHeaterSetpointTemperature() const {
  return getImpl<detail::CoilCoolingDXMultiSpeed_Impl>()->basinHeaterSetpointTemperature();
}

bool CoilCoolingDXMultiSpeed::setBasinHeaterSetpointTemperature(double basinHeaterSetpointTemperature) {
  return getImpl<detail::CoilCoolingDXMultiSpeed_Impl>()->setBasinHeaterSetpointTemperature(basinHeaterSetpointTemperature);
}

std::string CoilCoolingDXMultiSpeed::fuelType() const {
  return getImpl<detail::CoilCoolingDXMultiSpeed_Impl>()->fuelType();
}

bool CoilCoolingDXMultiSpeed::setFuelType(const std::string& fuelType) {
  return getImpl<detail::CoilCoolingDXMultiSpeed_Impl>()->setFuelType(fuelType);
}

double CoilCoolingDXMultiSpeed::minimumOutdoorDryBulbTemperatureforCompressorOperation() const {
  return getImpl<detail::CoilCoolingDXMultiSpeed_Impl>()->minimumOutdoorDryBulbTemperatureforCompressorOperation();
}

bool CoilCoolingDXMultiSpeed::setMinimumOutdoorDryBulbTemperatureforCompressorOperation(
  double minimumOutdoorDryBulbTemperatureforCompressorOperation) {
  return getImpl<detail::CoilCoolingDXMultiSpeed_Impl>()->setMinimumOutdoorDryBulbTemperatureforCompressorOperation(
    minimumOutdoorDryBulbTemperatureforCompressorOperation);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

unsigned CoilCoolingDXMultiSpeed_Impl::inletPort() const {
  return openstudio::Coil_Cooling_DX_MultiSpeedFields::AirInletNodeName;
}

unsigned CoilCoolingDXMultiSpeed_Impl::outletPort() const {
  return openstudio::Coil_Cooling_DX_MultiSpeedFields::AirOutletNodeName;
}

bool CoilCoolingDXMultiSpeed_Impl::addToNode(Node& node) {
  auto airLoop = node.airLoopHVAC();

  if (!(airLoop && airLoop->supplyComponent(node.handle()))) {
    return false;
  }

  return StraightComponent_Impl::addToNode(node);
}

std::string CoilCoolingDXMultiSpeed_Impl::condenserType() const {
  const auto value = getString(openstudio::Coil_Cooling_DX_MultiSpeedFields::CondenserType, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilCoolingDXMultiSpeed_Impl::setCondenserType(const std::string& condenserType) {
  return setString(openstudio::Coil_Cooling_DX_MultiSpeedFields::CondenserType, condenserType);
}

bool CoilCoolingDXMultiSpeed_Impl::applyPartLoadFractiontoSpeedsGreaterthan1() const {
  const auto value = getString(openstudio::Coil_Cooling_DX_MultiSpeedFields::ApplyPartLoadFractiontoSpeedsGreaterthan1, true);
  OS_ASSERT(value);
  return openstudio::istringEqual(*value, "Yes");
}

bool CoilCoolingDXMultiSpeed_Impl::setApplyPartLoadFractiontoSpeedsGreaterthan1(bool applyPartLoadFractiontoSpeedsGreaterthan1) {
  return setString(openstudio::Coil_Cooling_DX_MultiSpeedFields::ApplyPartLoadFractiontoSpeedsGreaterthan1,
                   applyPartLoadFractiontoSpeedsGreaterthan1 ? "Yes" : "No");
}

bool CoilCoolingDXMultiSpeed_Impl::applyLatentDegradationtoSpeedsGreaterthan1() const {
  const auto value = getString(openstudio::Coil_Cooling_DX_MultiSpeedFields::ApplyLatentDegradationtoSpeedsGreaterthan1, true);
  OS_ASSERT(value);
  return openstudio::istringEqual(*value, "Yes");
}

bool CoilCoolingDXMultiSpeed_Impl::isApplyLatentDegradationtoSpeedsGreaterthan1Defaulted() const {
  return isEmpty(openstudio::Coil_Cooling_DX_MultiSpeedFields::ApplyLatentDegradationtoSpeedsGreaterthan1);
}

bool CoilCoolingDXMultiSpeed_Impl::setApplyLatentDegradationtoSpeedsGreaterthan1(bool applyLatentDegradationtoSpeedsGreaterthan1) {
  return setString(openstudio::Coil_Cooling_DX_MultiSpeedFields::ApplyLatentDegradationtoSpeedsGreaterthan1,
                   applyLatentDegradationtoSpeedsGreaterthan1 ? "Yes" : "No");
}

void CoilCoolingDXMultiSpeed_Impl::resetApplyLatentDegradationtoSpeedsGreaterthan1() {
  const bool result = setString(openstudio::Coil_Cooling_DX_MultiSpeedFields::ApplyLatentDegradationtoSpeedsGreaterthan1, "");
  OS_ASSERT(result);
}

double CoilCoolingDXMultiSpeed_Impl::crankcaseHeaterCapacity() const {
  const auto value = getDouble(openstudio::Coil_Cooling_DX_MultiSpeedFields::CrankcaseHeaterCapacity, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilCoolingDXMultiSpeed_Impl::setCrankcaseHeaterCapacity(double crankcaseHeaterCapacity) {
  return setDouble(openstudio::Coil_Cooling_DX_MultiSpeedFields::CrankcaseHeaterCapacity, crankcaseHeaterCapacity);
}

double CoilCoolingDXMultiSpeed_Impl::maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation() const {
  const auto value =
    getDouble(openstudio::Coil_Cooling_DX_MultiSpeedFields::MaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilCoolingDXMultiSpeed_Impl::setMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation(
  double maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation) {
  return setDouble(openstudio::Coil_Cooling_DX_MultiSpeedFields::MaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation,
                   maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation);
}

double CoilCoolingDXMultiSpeed_Impl::basinHeaterCapacity() const {
  const auto value = getDouble(openstudio::Coil_Cooling_DX_MultiSpeedFields::BasinHeaterCapacity, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilCoolingDXMultiSpeed_Impl::setBasinHeaterCapacity(double basinHeaterCapacity) {
  return setDouble(openstudio::Coil_Cooling_DX_MultiSpeedFields::BasinHeaterCapacity, basinHeaterCapacity);
}

double CoilCoolingDXMultiSpeed_Impl::basinHeaterSetpointTemperature() const {
  const auto value = getDouble(openstudio::Coil_Cooling_DX_MultiSpeedFields::BasinHeaterSetpointTemperature, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilCoolingDXMultiSpeed_Impl::setBasinHeaterSetpointTemperature(double basinHeaterSetpointTemperature) {
  return setDouble(openstudio::Coil_Cooling_DX_MultiSpeedFields::BasinHeaterSetpointTemperature, basinHeaterSetpointTemperature);
}

std::string CoilCoolingDXMultiSpeed_Impl::fuelType() const {
  const auto value = getString(openstudio::Coil_Cooling_DX_MultiSpeedFields::FuelType, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilCoolingDXMultiSpeed_Impl::setFuelType(const std::string& fuelType) {
  return setString(openstudio::Coil_Cooling_DX_MultiSpeedFields::FuelType, fuelType);
}

double CoilCoolingDXMultiSpeed_Impl::minimumOutdoorDryBulbTemperatureforCompressorOperation() const {
  const auto value = getDouble(openstudio::Coil_Cooling_DX_MultiSpeedFields::MinimumOutdoorDryBulbTemperatureforCompressorOperation, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilCoolingDXMultiSpeed_Impl::setMinimumOutdoorDryBulbTemperatureforCompressorOperation(
  double minimumOutdoorDryBulbTemperatureforCompressorOperation) {
  return setDouble(openstudio::Coil_Cooling_DX_MultiSpeedFields::MinimumOutdoorDryBulbTemperatureforCompressorOperation,
                   minimumOutdoorDryBulbTemperatureforCompressorOperation);
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
