/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/CoilCoolingDXVariableSpeed.hpp"
#include "StraightComponent/CoilCoolingDXVariableSpeed_Impl.hpp"

#include "Loop/AirLoopHVAC.hpp"
#include "Model.hpp"
#include "StraightComponent/Node.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/Coil_Cooling_DX_VariableSpeed_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

CoilCoolingDXVariableSpeed::CoilCoolingDXVariableSpeed(const Model& model)
  : StraightComponent(CoilCoolingDXVariableSpeed::iddObjectType(), model) {
  bool ok = true;
  ok = setNominalSpeedLevel(1);
  OS_ASSERT(ok);
  autosizeGrossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel();
  autosizeRatedAirFlowRateAtSelectedNominalSpeedLevel();
  ok = setNominalTimeforCondensatetoBeginLeavingtheCoil(0.0);
  OS_ASSERT(ok);
  ok = setInitialMoistureEvaporationRateDividedbySteadyStateACLatentCapacity(0.0);
  OS_ASSERT(ok);
  ok = setMaximumCyclingRate(2.5);
  OS_ASSERT(ok);
  ok = setLatentCapacityTimeConstant(60.0);
  OS_ASSERT(ok);
  ok = setFanDelayTime(60.0);
  OS_ASSERT(ok);
  ok = setCondenserType("AirCooled");
  OS_ASSERT(ok);
  ok = setEvaporativeCondenserPumpRatedPowerConsumption(0.0);
  OS_ASSERT(ok);
  ok = setCrankcaseHeaterCapacity(0.0);
  OS_ASSERT(ok);
  ok = setMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation(10.0);
  OS_ASSERT(ok);
  ok = setMinimumOutdoorDryBulbTemperatureforCompressorOperation(-25.0);
  OS_ASSERT(ok);
  ok = setBasinHeaterCapacity(0.0);
  OS_ASSERT(ok);
  ok = setBasinHeaterSetpointTemperature(2.0);
  OS_ASSERT(ok);
}

CoilCoolingDXVariableSpeed::CoilCoolingDXVariableSpeed(std::shared_ptr<detail::CoilCoolingDXVariableSpeed_Impl> impl)
  : StraightComponent(std::move(impl)) {}

IddObjectType CoilCoolingDXVariableSpeed::iddObjectType() {
  return IddObjectType::Coil_Cooling_DX_VariableSpeed;
}

  std::vector<std::string> CoilCoolingDXVariableSpeed::condenserTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::Coil_Cooling_DX_VariableSpeedFields::CondenserType);
  }

  bool CoilCoolingDXVariableSpeed::addToNode(Node& node) {
    return getImpl<detail::CoilCoolingDXVariableSpeed_Impl>()->addToNode(node);
  }

int CoilCoolingDXVariableSpeed::nominalSpeedLevel() const {
  return getImpl<detail::CoilCoolingDXVariableSpeed_Impl>()->nominalSpeedLevel();
}

bool CoilCoolingDXVariableSpeed::setNominalSpeedLevel(int nominalSpeedLevel) {
  return getImpl<detail::CoilCoolingDXVariableSpeed_Impl>()->setNominalSpeedLevel(nominalSpeedLevel);
}

boost::optional<double> CoilCoolingDXVariableSpeed::grossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel() const {
  return getImpl<detail::CoilCoolingDXVariableSpeed_Impl>()->grossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel();
}

bool CoilCoolingDXVariableSpeed::isGrossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevelAutosized() const {
  return getImpl<detail::CoilCoolingDXVariableSpeed_Impl>()->isGrossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevelAutosized();
}

bool CoilCoolingDXVariableSpeed::setGrossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel(
  double grossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel) {
  return getImpl<detail::CoilCoolingDXVariableSpeed_Impl>()->setGrossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel(
    grossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel);
}

void CoilCoolingDXVariableSpeed::autosizeGrossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel() {
  getImpl<detail::CoilCoolingDXVariableSpeed_Impl>()->autosizeGrossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel();
}

boost::optional<double> CoilCoolingDXVariableSpeed::ratedAirFlowRateAtSelectedNominalSpeedLevel() const {
  return getImpl<detail::CoilCoolingDXVariableSpeed_Impl>()->ratedAirFlowRateAtSelectedNominalSpeedLevel();
}

bool CoilCoolingDXVariableSpeed::isRatedAirFlowRateAtSelectedNominalSpeedLevelAutosized() const {
  return getImpl<detail::CoilCoolingDXVariableSpeed_Impl>()->isRatedAirFlowRateAtSelectedNominalSpeedLevelAutosized();
}

bool CoilCoolingDXVariableSpeed::setRatedAirFlowRateAtSelectedNominalSpeedLevel(double ratedAirFlowRateAtSelectedNominalSpeedLevel) {
  return getImpl<detail::CoilCoolingDXVariableSpeed_Impl>()->setRatedAirFlowRateAtSelectedNominalSpeedLevel(
    ratedAirFlowRateAtSelectedNominalSpeedLevel);
}

void CoilCoolingDXVariableSpeed::autosizeRatedAirFlowRateAtSelectedNominalSpeedLevel() {
  getImpl<detail::CoilCoolingDXVariableSpeed_Impl>()->autosizeRatedAirFlowRateAtSelectedNominalSpeedLevel();
}

double CoilCoolingDXVariableSpeed::nominalTimeforCondensatetoBeginLeavingtheCoil() const {
  return getImpl<detail::CoilCoolingDXVariableSpeed_Impl>()->nominalTimeforCondensatetoBeginLeavingtheCoil();
}

bool CoilCoolingDXVariableSpeed::setNominalTimeforCondensatetoBeginLeavingtheCoil(double nominalTimeforCondensatetoBeginLeavingtheCoil) {
  return getImpl<detail::CoilCoolingDXVariableSpeed_Impl>()->setNominalTimeforCondensatetoBeginLeavingtheCoil(
    nominalTimeforCondensatetoBeginLeavingtheCoil);
}

double CoilCoolingDXVariableSpeed::initialMoistureEvaporationRateDividedbySteadyStateACLatentCapacity() const {
  return getImpl<detail::CoilCoolingDXVariableSpeed_Impl>()->initialMoistureEvaporationRateDividedbySteadyStateACLatentCapacity();
}

bool CoilCoolingDXVariableSpeed::setInitialMoistureEvaporationRateDividedbySteadyStateACLatentCapacity(
  double initialMoistureEvaporationRateDividedbySteadyStateACLatentCapacity) {
  return getImpl<detail::CoilCoolingDXVariableSpeed_Impl>()->setInitialMoistureEvaporationRateDividedbySteadyStateACLatentCapacity(
    initialMoistureEvaporationRateDividedbySteadyStateACLatentCapacity);
}

double CoilCoolingDXVariableSpeed::maximumCyclingRate() const {
  return getImpl<detail::CoilCoolingDXVariableSpeed_Impl>()->maximumCyclingRate();
}

bool CoilCoolingDXVariableSpeed::setMaximumCyclingRate(double maximumCyclingRate) {
  return getImpl<detail::CoilCoolingDXVariableSpeed_Impl>()->setMaximumCyclingRate(maximumCyclingRate);
}

double CoilCoolingDXVariableSpeed::latentCapacityTimeConstant() const {
  return getImpl<detail::CoilCoolingDXVariableSpeed_Impl>()->latentCapacityTimeConstant();
}

bool CoilCoolingDXVariableSpeed::setLatentCapacityTimeConstant(double latentCapacityTimeConstant) {
  return getImpl<detail::CoilCoolingDXVariableSpeed_Impl>()->setLatentCapacityTimeConstant(latentCapacityTimeConstant);
}

double CoilCoolingDXVariableSpeed::fanDelayTime() const {
  return getImpl<detail::CoilCoolingDXVariableSpeed_Impl>()->fanDelayTime();
}

bool CoilCoolingDXVariableSpeed::setFanDelayTime(double fanDelayTime) {
  return getImpl<detail::CoilCoolingDXVariableSpeed_Impl>()->setFanDelayTime(fanDelayTime);
}

std::string CoilCoolingDXVariableSpeed::condenserType() const {
  return getImpl<detail::CoilCoolingDXVariableSpeed_Impl>()->condenserType();
}

bool CoilCoolingDXVariableSpeed::setCondenserType(const std::string& condenserType) {
  return getImpl<detail::CoilCoolingDXVariableSpeed_Impl>()->setCondenserType(condenserType);
}

boost::optional<double> CoilCoolingDXVariableSpeed::evaporativeCondenserPumpRatedPowerConsumption() const {
  return getImpl<detail::CoilCoolingDXVariableSpeed_Impl>()->evaporativeCondenserPumpRatedPowerConsumption();
}

bool CoilCoolingDXVariableSpeed::isEvaporativeCondenserPumpRatedPowerConsumptionAutosized() const {
  return getImpl<detail::CoilCoolingDXVariableSpeed_Impl>()->isEvaporativeCondenserPumpRatedPowerConsumptionAutosized();
}

bool CoilCoolingDXVariableSpeed::setEvaporativeCondenserPumpRatedPowerConsumption(double evaporativeCondenserPumpRatedPowerConsumption) {
  return getImpl<detail::CoilCoolingDXVariableSpeed_Impl>()->setEvaporativeCondenserPumpRatedPowerConsumption(
    evaporativeCondenserPumpRatedPowerConsumption);
}

void CoilCoolingDXVariableSpeed::autosizeEvaporativeCondenserPumpRatedPowerConsumption() {
  getImpl<detail::CoilCoolingDXVariableSpeed_Impl>()->autosizeEvaporativeCondenserPumpRatedPowerConsumption();
}

double CoilCoolingDXVariableSpeed::crankcaseHeaterCapacity() const {
  return getImpl<detail::CoilCoolingDXVariableSpeed_Impl>()->crankcaseHeaterCapacity();
}

bool CoilCoolingDXVariableSpeed::setCrankcaseHeaterCapacity(double crankcaseHeaterCapacity) {
  return getImpl<detail::CoilCoolingDXVariableSpeed_Impl>()->setCrankcaseHeaterCapacity(crankcaseHeaterCapacity);
}

double CoilCoolingDXVariableSpeed::maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation() const {
  return getImpl<detail::CoilCoolingDXVariableSpeed_Impl>()->maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation();
}

bool CoilCoolingDXVariableSpeed::setMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation(
  double maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation) {
  return getImpl<detail::CoilCoolingDXVariableSpeed_Impl>()->setMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation(
    maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation);
}

double CoilCoolingDXVariableSpeed::basinHeaterCapacity() const {
  return getImpl<detail::CoilCoolingDXVariableSpeed_Impl>()->basinHeaterCapacity();
}

bool CoilCoolingDXVariableSpeed::setBasinHeaterCapacity(double basinHeaterCapacity) {
  return getImpl<detail::CoilCoolingDXVariableSpeed_Impl>()->setBasinHeaterCapacity(basinHeaterCapacity);
}

double CoilCoolingDXVariableSpeed::basinHeaterSetpointTemperature() const {
  return getImpl<detail::CoilCoolingDXVariableSpeed_Impl>()->basinHeaterSetpointTemperature();
}

bool CoilCoolingDXVariableSpeed::setBasinHeaterSetpointTemperature(double basinHeaterSetpointTemperature) {
  return getImpl<detail::CoilCoolingDXVariableSpeed_Impl>()->setBasinHeaterSetpointTemperature(basinHeaterSetpointTemperature);
}

double CoilCoolingDXVariableSpeed::minimumOutdoorDryBulbTemperatureforCompressorOperation() const {
  return getImpl<detail::CoilCoolingDXVariableSpeed_Impl>()->minimumOutdoorDryBulbTemperatureforCompressorOperation();
}

bool CoilCoolingDXVariableSpeed::setMinimumOutdoorDryBulbTemperatureforCompressorOperation(
  double minimumOutdoorDryBulbTemperatureforCompressorOperation) {
  return getImpl<detail::CoilCoolingDXVariableSpeed_Impl>()->setMinimumOutdoorDryBulbTemperatureforCompressorOperation(
    minimumOutdoorDryBulbTemperatureforCompressorOperation);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

namespace {

bool isAutosized(const ModelObject_Impl& impl, int fieldIndex) {
  if (const auto value = impl.getString(fieldIndex, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

}  // namespace

unsigned CoilCoolingDXVariableSpeed_Impl::inletPort() const {
  return openstudio::Coil_Cooling_DX_VariableSpeedFields::IndoorAirInletNodeName;
}

unsigned CoilCoolingDXVariableSpeed_Impl::outletPort() const {
  return openstudio::Coil_Cooling_DX_VariableSpeedFields::IndoorAirOutletNodeName;
}

bool CoilCoolingDXVariableSpeed_Impl::addToNode(Node& node) {
  auto airLoop = node.airLoopHVAC();

  if (!(airLoop && airLoop->supplyComponent(node.handle()))) {
    return false;
  }

  return StraightComponent_Impl::addToNode(node);
}

int CoilCoolingDXVariableSpeed_Impl::nominalSpeedLevel() const {
  const auto value = getInt(openstudio::Coil_Cooling_DX_VariableSpeedFields::NominalSpeedLevel, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilCoolingDXVariableSpeed_Impl::setNominalSpeedLevel(int nominalSpeedLevel) {
  const bool result = setInt(openstudio::Coil_Cooling_DX_VariableSpeedFields::NominalSpeedLevel, nominalSpeedLevel);
  OS_ASSERT(result);
  return result;
}

boost::optional<double> CoilCoolingDXVariableSpeed_Impl::grossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel() const {
  return getDouble(openstudio::Coil_Cooling_DX_VariableSpeedFields::GrossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel, true);
}

bool CoilCoolingDXVariableSpeed_Impl::isGrossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevelAutosized() const {
  return isAutosized(*this, openstudio::Coil_Cooling_DX_VariableSpeedFields::GrossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel);
}

bool CoilCoolingDXVariableSpeed_Impl::setGrossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel(
  double grossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel) {
  const bool result = setDouble(openstudio::Coil_Cooling_DX_VariableSpeedFields::GrossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel,
                                grossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel);
  OS_ASSERT(result);
  return result;
}

void CoilCoolingDXVariableSpeed_Impl::autosizeGrossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel() {
  const bool result =
    setString(openstudio::Coil_Cooling_DX_VariableSpeedFields::GrossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel, "autosize");
  OS_ASSERT(result);
}

boost::optional<double> CoilCoolingDXVariableSpeed_Impl::ratedAirFlowRateAtSelectedNominalSpeedLevel() const {
  return getDouble(openstudio::Coil_Cooling_DX_VariableSpeedFields::RatedAirFlowRateAtSelectedNominalSpeedLevel, true);
}

bool CoilCoolingDXVariableSpeed_Impl::isRatedAirFlowRateAtSelectedNominalSpeedLevelAutosized() const {
  return isAutosized(*this, openstudio::Coil_Cooling_DX_VariableSpeedFields::RatedAirFlowRateAtSelectedNominalSpeedLevel);
}

bool CoilCoolingDXVariableSpeed_Impl::setRatedAirFlowRateAtSelectedNominalSpeedLevel(double ratedAirFlowRateAtSelectedNominalSpeedLevel) {
  const bool result =
    setDouble(openstudio::Coil_Cooling_DX_VariableSpeedFields::RatedAirFlowRateAtSelectedNominalSpeedLevel, ratedAirFlowRateAtSelectedNominalSpeedLevel);
  OS_ASSERT(result);
  return result;
}

void CoilCoolingDXVariableSpeed_Impl::autosizeRatedAirFlowRateAtSelectedNominalSpeedLevel() {
  const bool result = setString(openstudio::Coil_Cooling_DX_VariableSpeedFields::RatedAirFlowRateAtSelectedNominalSpeedLevel, "autosize");
  OS_ASSERT(result);
}

double CoilCoolingDXVariableSpeed_Impl::nominalTimeforCondensatetoBeginLeavingtheCoil() const {
  const auto value = getDouble(openstudio::Coil_Cooling_DX_VariableSpeedFields::NominalTimeforCondensatetoBeginLeavingtheCoil, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilCoolingDXVariableSpeed_Impl::setNominalTimeforCondensatetoBeginLeavingtheCoil(double nominalTimeforCondensatetoBeginLeavingtheCoil) {
  return setDouble(openstudio::Coil_Cooling_DX_VariableSpeedFields::NominalTimeforCondensatetoBeginLeavingtheCoil,
                   nominalTimeforCondensatetoBeginLeavingtheCoil);
}

double CoilCoolingDXVariableSpeed_Impl::initialMoistureEvaporationRateDividedbySteadyStateACLatentCapacity() const {
  const auto value =
    getDouble(openstudio::Coil_Cooling_DX_VariableSpeedFields::InitialMoistureEvaporationRateDividedbySteadyStateACLatentCapacity, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilCoolingDXVariableSpeed_Impl::setInitialMoistureEvaporationRateDividedbySteadyStateACLatentCapacity(
  double initialMoistureEvaporationRateDividedbySteadyStateACLatentCapacity) {
  return setDouble(openstudio::Coil_Cooling_DX_VariableSpeedFields::InitialMoistureEvaporationRateDividedbySteadyStateACLatentCapacity,
                   initialMoistureEvaporationRateDividedbySteadyStateACLatentCapacity);
}

double CoilCoolingDXVariableSpeed_Impl::maximumCyclingRate() const {
  const auto value = getDouble(openstudio::Coil_Cooling_DX_VariableSpeedFields::MaximumCyclingRate, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilCoolingDXVariableSpeed_Impl::setMaximumCyclingRate(double maximumCyclingRate) {
  return setDouble(openstudio::Coil_Cooling_DX_VariableSpeedFields::MaximumCyclingRate, maximumCyclingRate);
}

double CoilCoolingDXVariableSpeed_Impl::latentCapacityTimeConstant() const {
  const auto value = getDouble(openstudio::Coil_Cooling_DX_VariableSpeedFields::LatentCapacityTimeConstant, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilCoolingDXVariableSpeed_Impl::setLatentCapacityTimeConstant(double latentCapacityTimeConstant) {
  return setDouble(openstudio::Coil_Cooling_DX_VariableSpeedFields::LatentCapacityTimeConstant, latentCapacityTimeConstant);
}

double CoilCoolingDXVariableSpeed_Impl::fanDelayTime() const {
  const auto value = getDouble(openstudio::Coil_Cooling_DX_VariableSpeedFields::FanDelayTime, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilCoolingDXVariableSpeed_Impl::setFanDelayTime(double fanDelayTime) {
  return setDouble(openstudio::Coil_Cooling_DX_VariableSpeedFields::FanDelayTime, fanDelayTime);
}

std::vector<std::string> CoilCoolingDXVariableSpeed_Impl::condenserTypeValues() const {
  return CoilCoolingDXVariableSpeed::condenserTypeValues();
}

std::string CoilCoolingDXVariableSpeed_Impl::condenserType() const {
  const auto value = getString(openstudio::Coil_Cooling_DX_VariableSpeedFields::CondenserType, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilCoolingDXVariableSpeed_Impl::setCondenserType(const std::string& condenserType) {
  return setString(openstudio::Coil_Cooling_DX_VariableSpeedFields::CondenserType, condenserType);
}

boost::optional<double> CoilCoolingDXVariableSpeed_Impl::evaporativeCondenserPumpRatedPowerConsumption() const {
  return getDouble(openstudio::Coil_Cooling_DX_VariableSpeedFields::EvaporativeCondenserPumpRatedPowerConsumption, true);
}

bool CoilCoolingDXVariableSpeed_Impl::isEvaporativeCondenserPumpRatedPowerConsumptionAutosized() const {
  return isAutosized(*this, openstudio::Coil_Cooling_DX_VariableSpeedFields::EvaporativeCondenserPumpRatedPowerConsumption);
}

bool CoilCoolingDXVariableSpeed_Impl::setEvaporativeCondenserPumpRatedPowerConsumption(double evaporativeCondenserPumpRatedPowerConsumption) {
  return setDouble(openstudio::Coil_Cooling_DX_VariableSpeedFields::EvaporativeCondenserPumpRatedPowerConsumption,
                   evaporativeCondenserPumpRatedPowerConsumption);
}

void CoilCoolingDXVariableSpeed_Impl::autosizeEvaporativeCondenserPumpRatedPowerConsumption() {
  const bool result = setString(openstudio::Coil_Cooling_DX_VariableSpeedFields::EvaporativeCondenserPumpRatedPowerConsumption, "autosize");
  OS_ASSERT(result);
}

double CoilCoolingDXVariableSpeed_Impl::crankcaseHeaterCapacity() const {
  const auto value = getDouble(openstudio::Coil_Cooling_DX_VariableSpeedFields::CrankcaseHeaterCapacity, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilCoolingDXVariableSpeed_Impl::setCrankcaseHeaterCapacity(double crankcaseHeaterCapacity) {
  return setDouble(openstudio::Coil_Cooling_DX_VariableSpeedFields::CrankcaseHeaterCapacity, crankcaseHeaterCapacity);
}

double CoilCoolingDXVariableSpeed_Impl::maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation() const {
  const auto value =
    getDouble(openstudio::Coil_Cooling_DX_VariableSpeedFields::MaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilCoolingDXVariableSpeed_Impl::setMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation(
  double maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation) {
  return setDouble(openstudio::Coil_Cooling_DX_VariableSpeedFields::MaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation,
                   maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation);
}

double CoilCoolingDXVariableSpeed_Impl::basinHeaterCapacity() const {
  const auto value = getDouble(openstudio::Coil_Cooling_DX_VariableSpeedFields::BasinHeaterCapacity, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilCoolingDXVariableSpeed_Impl::setBasinHeaterCapacity(double basinHeaterCapacity) {
  return setDouble(openstudio::Coil_Cooling_DX_VariableSpeedFields::BasinHeaterCapacity, basinHeaterCapacity);
}

double CoilCoolingDXVariableSpeed_Impl::basinHeaterSetpointTemperature() const {
  const auto value = getDouble(openstudio::Coil_Cooling_DX_VariableSpeedFields::BasinHeaterSetpointTemperature, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilCoolingDXVariableSpeed_Impl::setBasinHeaterSetpointTemperature(double basinHeaterSetpointTemperature) {
  return setDouble(openstudio::Coil_Cooling_DX_VariableSpeedFields::BasinHeaterSetpointTemperature, basinHeaterSetpointTemperature);
}

double CoilCoolingDXVariableSpeed_Impl::minimumOutdoorDryBulbTemperatureforCompressorOperation() const {
  const auto value = getDouble(openstudio::Coil_Cooling_DX_VariableSpeedFields::MinimumOutdoorDryBulbTemperatureforCompressorOperation, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilCoolingDXVariableSpeed_Impl::setMinimumOutdoorDryBulbTemperatureforCompressorOperation(
  double minimumOutdoorDryBulbTemperatureforCompressorOperation) {
  return setDouble(openstudio::Coil_Cooling_DX_VariableSpeedFields::MinimumOutdoorDryBulbTemperatureforCompressorOperation,
                   minimumOutdoorDryBulbTemperatureforCompressorOperation);
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
