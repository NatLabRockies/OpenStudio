/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ResourceObject/CoilCoolingDXCurveFitOperatingMode.hpp"
#include "ResourceObject/CoilCoolingDXCurveFitOperatingMode_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/Coil_Cooling_DX_CurveFit_OperatingMode_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

CoilCoolingDXCurveFitOperatingMode::CoilCoolingDXCurveFitOperatingMode(const Model& model)
  : ModelObject(CoilCoolingDXCurveFitOperatingMode::iddObjectType(), model) {}

CoilCoolingDXCurveFitOperatingMode::CoilCoolingDXCurveFitOperatingMode(
  std::shared_ptr<detail::CoilCoolingDXCurveFitOperatingMode_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType CoilCoolingDXCurveFitOperatingMode::iddObjectType() {
  return IddObjectType::Coil_Cooling_DX_CurveFit_OperatingMode;
}

std::vector<std::string> CoilCoolingDXCurveFitOperatingMode::condenserTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::Coil_Cooling_DX_CurveFit_OperatingModeFields::CondenserType);
}

boost::optional<double> CoilCoolingDXCurveFitOperatingMode::ratedGrossTotalCoolingCapacity() const {
  return getImpl<detail::CoilCoolingDXCurveFitOperatingMode_Impl>()->ratedGrossTotalCoolingCapacity();
}

bool CoilCoolingDXCurveFitOperatingMode::isRatedGrossTotalCoolingCapacityAutosized() const {
  return getImpl<detail::CoilCoolingDXCurveFitOperatingMode_Impl>()->isRatedGrossTotalCoolingCapacityAutosized();
}

boost::optional<double> CoilCoolingDXCurveFitOperatingMode::ratedEvaporatorAirFlowRate() const {
  return getImpl<detail::CoilCoolingDXCurveFitOperatingMode_Impl>()->ratedEvaporatorAirFlowRate();
}

bool CoilCoolingDXCurveFitOperatingMode::isRatedEvaporatorAirFlowRateAutosized() const {
  return getImpl<detail::CoilCoolingDXCurveFitOperatingMode_Impl>()->isRatedEvaporatorAirFlowRateAutosized();
}

boost::optional<double> CoilCoolingDXCurveFitOperatingMode::ratedCondenserAirFlowRate() const {
  return getImpl<detail::CoilCoolingDXCurveFitOperatingMode_Impl>()->ratedCondenserAirFlowRate();
}

bool CoilCoolingDXCurveFitOperatingMode::isRatedCondenserAirFlowRateAutosized() const {
  return getImpl<detail::CoilCoolingDXCurveFitOperatingMode_Impl>()->isRatedCondenserAirFlowRateAutosized();
}

double CoilCoolingDXCurveFitOperatingMode::maximumCyclingRate() const {
  return getImpl<detail::CoilCoolingDXCurveFitOperatingMode_Impl>()->maximumCyclingRate();
}

double CoilCoolingDXCurveFitOperatingMode::ratioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity() const {
  return getImpl<detail::CoilCoolingDXCurveFitOperatingMode_Impl>()->ratioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity();
}

double CoilCoolingDXCurveFitOperatingMode::latentCapacityTimeConstant() const {
  return getImpl<detail::CoilCoolingDXCurveFitOperatingMode_Impl>()->latentCapacityTimeConstant();
}

double CoilCoolingDXCurveFitOperatingMode::nominalTimeforCondensateRemovaltoBegin() const {
  return getImpl<detail::CoilCoolingDXCurveFitOperatingMode_Impl>()->nominalTimeforCondensateRemovaltoBegin();
}

bool CoilCoolingDXCurveFitOperatingMode::applyLatentDegradationtoSpeedsGreaterthan1() const {
  return getImpl<detail::CoilCoolingDXCurveFitOperatingMode_Impl>()->applyLatentDegradationtoSpeedsGreaterthan1();
}

std::string CoilCoolingDXCurveFitOperatingMode::condenserType() const {
  return getImpl<detail::CoilCoolingDXCurveFitOperatingMode_Impl>()->condenserType();
}

boost::optional<double> CoilCoolingDXCurveFitOperatingMode::nominalEvaporativeCondenserPumpPower() const {
  return getImpl<detail::CoilCoolingDXCurveFitOperatingMode_Impl>()->nominalEvaporativeCondenserPumpPower();
}

bool CoilCoolingDXCurveFitOperatingMode::isNominalEvaporativeCondenserPumpPowerAutosized() const {
  return getImpl<detail::CoilCoolingDXCurveFitOperatingMode_Impl>()->isNominalEvaporativeCondenserPumpPowerAutosized();
}

unsigned CoilCoolingDXCurveFitOperatingMode::nominalSpeedNumber() const {
  return getImpl<detail::CoilCoolingDXCurveFitOperatingMode_Impl>()->nominalSpeedNumber();
}

bool CoilCoolingDXCurveFitOperatingMode::isNominalSpeedNumberDefaulted() const {
  return getImpl<detail::CoilCoolingDXCurveFitOperatingMode_Impl>()->isNominalSpeedNumberDefaulted();
}

bool CoilCoolingDXCurveFitOperatingMode::setRatedGrossTotalCoolingCapacity(double ratedGrossTotalCoolingCapacity) {
  return getImpl<detail::CoilCoolingDXCurveFitOperatingMode_Impl>()->setRatedGrossTotalCoolingCapacity(ratedGrossTotalCoolingCapacity);
}

void CoilCoolingDXCurveFitOperatingMode::autosizeRatedGrossTotalCoolingCapacity() {
  getImpl<detail::CoilCoolingDXCurveFitOperatingMode_Impl>()->autosizeRatedGrossTotalCoolingCapacity();
}

bool CoilCoolingDXCurveFitOperatingMode::setRatedEvaporatorAirFlowRate(double ratedEvaporatorAirFlowRate) {
  return getImpl<detail::CoilCoolingDXCurveFitOperatingMode_Impl>()->setRatedEvaporatorAirFlowRate(ratedEvaporatorAirFlowRate);
}

void CoilCoolingDXCurveFitOperatingMode::autosizeRatedEvaporatorAirFlowRate() {
  getImpl<detail::CoilCoolingDXCurveFitOperatingMode_Impl>()->autosizeRatedEvaporatorAirFlowRate();
}

bool CoilCoolingDXCurveFitOperatingMode::setRatedCondenserAirFlowRate(double ratedCondenserAirFlowRate) {
  return getImpl<detail::CoilCoolingDXCurveFitOperatingMode_Impl>()->setRatedCondenserAirFlowRate(ratedCondenserAirFlowRate);
}

void CoilCoolingDXCurveFitOperatingMode::autosizeRatedCondenserAirFlowRate() {
  getImpl<detail::CoilCoolingDXCurveFitOperatingMode_Impl>()->autosizeRatedCondenserAirFlowRate();
}

bool CoilCoolingDXCurveFitOperatingMode::setMaximumCyclingRate(double maximumCyclingRate) {
  return getImpl<detail::CoilCoolingDXCurveFitOperatingMode_Impl>()->setMaximumCyclingRate(maximumCyclingRate);
}

bool CoilCoolingDXCurveFitOperatingMode::setRatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity(
  double ratioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity) {
  return getImpl<detail::CoilCoolingDXCurveFitOperatingMode_Impl>()
    ->setRatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity(
      ratioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity);
}

bool CoilCoolingDXCurveFitOperatingMode::setLatentCapacityTimeConstant(double latentCapacityTimeConstant) {
  return getImpl<detail::CoilCoolingDXCurveFitOperatingMode_Impl>()->setLatentCapacityTimeConstant(latentCapacityTimeConstant);
}

bool CoilCoolingDXCurveFitOperatingMode::setNominalTimeforCondensateRemovaltoBegin(double nominalTimeforCondensateRemovaltoBegin) {
  return getImpl<detail::CoilCoolingDXCurveFitOperatingMode_Impl>()->setNominalTimeforCondensateRemovaltoBegin(
    nominalTimeforCondensateRemovaltoBegin);
}

bool CoilCoolingDXCurveFitOperatingMode::setApplyLatentDegradationtoSpeedsGreaterthan1(bool applyLatentDegradationtoSpeedsGreaterthan1) {
  return getImpl<detail::CoilCoolingDXCurveFitOperatingMode_Impl>()->setApplyLatentDegradationtoSpeedsGreaterthan1(
    applyLatentDegradationtoSpeedsGreaterthan1);
}

bool CoilCoolingDXCurveFitOperatingMode::setCondenserType(const std::string& condenserType) {
  return getImpl<detail::CoilCoolingDXCurveFitOperatingMode_Impl>()->setCondenserType(condenserType);
}

bool CoilCoolingDXCurveFitOperatingMode::setNominalEvaporativeCondenserPumpPower(double nominalEvaporativeCondenserPumpPower) {
  return getImpl<detail::CoilCoolingDXCurveFitOperatingMode_Impl>()->setNominalEvaporativeCondenserPumpPower(
    nominalEvaporativeCondenserPumpPower);
}

void CoilCoolingDXCurveFitOperatingMode::autosizeNominalEvaporativeCondenserPumpPower() {
  getImpl<detail::CoilCoolingDXCurveFitOperatingMode_Impl>()->autosizeNominalEvaporativeCondenserPumpPower();
}

bool CoilCoolingDXCurveFitOperatingMode::setNominalSpeedNumber(unsigned nominalSpeedNumber) {
  return getImpl<detail::CoilCoolingDXCurveFitOperatingMode_Impl>()->setNominalSpeedNumber(nominalSpeedNumber);
}

void CoilCoolingDXCurveFitOperatingMode::resetNominalSpeedNumber() {
  getImpl<detail::CoilCoolingDXCurveFitOperatingMode_Impl>()->resetNominalSpeedNumber();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

boost::optional<double> CoilCoolingDXCurveFitOperatingMode_Impl::ratedGrossTotalCoolingCapacity() const {
  return getDouble(openstudio::Coil_Cooling_DX_CurveFit_OperatingModeFields::RatedGrossTotalCoolingCapacity, true);
}

bool CoilCoolingDXCurveFitOperatingMode_Impl::isRatedGrossTotalCoolingCapacityAutosized() const {
  if (auto value = getString(openstudio::Coil_Cooling_DX_CurveFit_OperatingModeFields::RatedGrossTotalCoolingCapacity, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

boost::optional<double> CoilCoolingDXCurveFitOperatingMode_Impl::ratedEvaporatorAirFlowRate() const {
  return getDouble(openstudio::Coil_Cooling_DX_CurveFit_OperatingModeFields::RatedEvaporatorAirFlowRate, true);
}

bool CoilCoolingDXCurveFitOperatingMode_Impl::isRatedEvaporatorAirFlowRateAutosized() const {
  if (auto value = getString(openstudio::Coil_Cooling_DX_CurveFit_OperatingModeFields::RatedEvaporatorAirFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

boost::optional<double> CoilCoolingDXCurveFitOperatingMode_Impl::ratedCondenserAirFlowRate() const {
  return getDouble(openstudio::Coil_Cooling_DX_CurveFit_OperatingModeFields::RatedCondenserAirFlowRate, true);
}

bool CoilCoolingDXCurveFitOperatingMode_Impl::isRatedCondenserAirFlowRateAutosized() const {
  if (auto value = getString(openstudio::Coil_Cooling_DX_CurveFit_OperatingModeFields::RatedCondenserAirFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

double CoilCoolingDXCurveFitOperatingMode_Impl::maximumCyclingRate() const {
  const auto value = getDouble(openstudio::Coil_Cooling_DX_CurveFit_OperatingModeFields::MaximumCyclingRate, true);
  OS_ASSERT(value);
  return *value;
}

double CoilCoolingDXCurveFitOperatingMode_Impl::ratioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity() const {
  const auto value =
    getDouble(openstudio::Coil_Cooling_DX_CurveFit_OperatingModeFields::RatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity,
              true);
  OS_ASSERT(value);
  return *value;
}

double CoilCoolingDXCurveFitOperatingMode_Impl::latentCapacityTimeConstant() const {
  const auto value = getDouble(openstudio::Coil_Cooling_DX_CurveFit_OperatingModeFields::LatentCapacityTimeConstant, true);
  OS_ASSERT(value);
  return *value;
}

double CoilCoolingDXCurveFitOperatingMode_Impl::nominalTimeforCondensateRemovaltoBegin() const {
  const auto value = getDouble(openstudio::Coil_Cooling_DX_CurveFit_OperatingModeFields::NominalTimeforCondensateRemovaltoBegin, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilCoolingDXCurveFitOperatingMode_Impl::applyLatentDegradationtoSpeedsGreaterthan1() const {
  const auto value =
    getString(openstudio::Coil_Cooling_DX_CurveFit_OperatingModeFields::ApplyLatentDegradationtoSpeedsGreaterthan1, true);
  OS_ASSERT(value);
  return openstudio::istringEqual(*value, "Yes");
}

std::string CoilCoolingDXCurveFitOperatingMode_Impl::condenserType() const {
  const auto value = getString(openstudio::Coil_Cooling_DX_CurveFit_OperatingModeFields::CondenserType, true);
  OS_ASSERT(value);
  return *value;
}

boost::optional<double> CoilCoolingDXCurveFitOperatingMode_Impl::nominalEvaporativeCondenserPumpPower() const {
  return getDouble(openstudio::Coil_Cooling_DX_CurveFit_OperatingModeFields::NominalEvaporativeCondenserPumpPower, true);
}

bool CoilCoolingDXCurveFitOperatingMode_Impl::isNominalEvaporativeCondenserPumpPowerAutosized() const {
  if (auto value = getString(openstudio::Coil_Cooling_DX_CurveFit_OperatingModeFields::NominalEvaporativeCondenserPumpPower, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

unsigned CoilCoolingDXCurveFitOperatingMode_Impl::nominalSpeedNumber() const {
  const auto value = getInt(openstudio::Coil_Cooling_DX_CurveFit_OperatingModeFields::NominalSpeedNumber, true);
  OS_ASSERT(value);
  return static_cast<unsigned>(*value);
}

bool CoilCoolingDXCurveFitOperatingMode_Impl::isNominalSpeedNumberDefaulted() const {
  return !getInt(openstudio::Coil_Cooling_DX_CurveFit_OperatingModeFields::NominalSpeedNumber, false);
}

bool CoilCoolingDXCurveFitOperatingMode_Impl::setRatedGrossTotalCoolingCapacity(double ratedGrossTotalCoolingCapacity) {
  return setDouble(openstudio::Coil_Cooling_DX_CurveFit_OperatingModeFields::RatedGrossTotalCoolingCapacity,
                   ratedGrossTotalCoolingCapacity);
}

void CoilCoolingDXCurveFitOperatingMode_Impl::autosizeRatedGrossTotalCoolingCapacity() {
  OS_ASSERT(setString(openstudio::Coil_Cooling_DX_CurveFit_OperatingModeFields::RatedGrossTotalCoolingCapacity, "autosize"));
}

bool CoilCoolingDXCurveFitOperatingMode_Impl::setRatedEvaporatorAirFlowRate(double ratedEvaporatorAirFlowRate) {
  return setDouble(openstudio::Coil_Cooling_DX_CurveFit_OperatingModeFields::RatedEvaporatorAirFlowRate, ratedEvaporatorAirFlowRate);
}

void CoilCoolingDXCurveFitOperatingMode_Impl::autosizeRatedEvaporatorAirFlowRate() {
  OS_ASSERT(setString(openstudio::Coil_Cooling_DX_CurveFit_OperatingModeFields::RatedEvaporatorAirFlowRate, "autosize"));
}

bool CoilCoolingDXCurveFitOperatingMode_Impl::setRatedCondenserAirFlowRate(double ratedCondenserAirFlowRate) {
  return setDouble(openstudio::Coil_Cooling_DX_CurveFit_OperatingModeFields::RatedCondenserAirFlowRate, ratedCondenserAirFlowRate);
}

void CoilCoolingDXCurveFitOperatingMode_Impl::autosizeRatedCondenserAirFlowRate() {
  OS_ASSERT(setString(openstudio::Coil_Cooling_DX_CurveFit_OperatingModeFields::RatedCondenserAirFlowRate, "autosize"));
}

bool CoilCoolingDXCurveFitOperatingMode_Impl::setMaximumCyclingRate(double maximumCyclingRate) {
  return setDouble(openstudio::Coil_Cooling_DX_CurveFit_OperatingModeFields::MaximumCyclingRate, maximumCyclingRate);
}

bool CoilCoolingDXCurveFitOperatingMode_Impl::setRatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity(
  double ratioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity) {
  return setDouble(openstudio::Coil_Cooling_DX_CurveFit_OperatingModeFields::RatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity,
                   ratioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity);
}

bool CoilCoolingDXCurveFitOperatingMode_Impl::setLatentCapacityTimeConstant(double latentCapacityTimeConstant) {
  return setDouble(openstudio::Coil_Cooling_DX_CurveFit_OperatingModeFields::LatentCapacityTimeConstant, latentCapacityTimeConstant);
}

bool CoilCoolingDXCurveFitOperatingMode_Impl::setNominalTimeforCondensateRemovaltoBegin(double nominalTimeforCondensateRemovaltoBegin) {
  return setDouble(openstudio::Coil_Cooling_DX_CurveFit_OperatingModeFields::NominalTimeforCondensateRemovaltoBegin,
                   nominalTimeforCondensateRemovaltoBegin);
}

bool CoilCoolingDXCurveFitOperatingMode_Impl::setApplyLatentDegradationtoSpeedsGreaterthan1(bool applyLatentDegradationtoSpeedsGreaterthan1) {
  const bool result = setString(openstudio::Coil_Cooling_DX_CurveFit_OperatingModeFields::ApplyLatentDegradationtoSpeedsGreaterthan1,
                                applyLatentDegradationtoSpeedsGreaterthan1 ? "Yes" : "No");
  OS_ASSERT(result);
  return result;
}

bool CoilCoolingDXCurveFitOperatingMode_Impl::setCondenserType(const std::string& condenserType) {
  return setString(openstudio::Coil_Cooling_DX_CurveFit_OperatingModeFields::CondenserType, condenserType);
}

bool CoilCoolingDXCurveFitOperatingMode_Impl::setNominalEvaporativeCondenserPumpPower(double nominalEvaporativeCondenserPumpPower) {
  return setDouble(openstudio::Coil_Cooling_DX_CurveFit_OperatingModeFields::NominalEvaporativeCondenserPumpPower,
                   nominalEvaporativeCondenserPumpPower);
}

void CoilCoolingDXCurveFitOperatingMode_Impl::autosizeNominalEvaporativeCondenserPumpPower() {
  OS_ASSERT(setString(openstudio::Coil_Cooling_DX_CurveFit_OperatingModeFields::NominalEvaporativeCondenserPumpPower, "autosize"));
}

bool CoilCoolingDXCurveFitOperatingMode_Impl::setNominalSpeedNumber(unsigned nominalSpeedNumber) {
  return setInt(openstudio::Coil_Cooling_DX_CurveFit_OperatingModeFields::NominalSpeedNumber, static_cast<int>(nominalSpeedNumber));
}

void CoilCoolingDXCurveFitOperatingMode_Impl::resetNominalSpeedNumber() {
  OS_ASSERT(setString(openstudio::Coil_Cooling_DX_CurveFit_OperatingModeFields::NominalSpeedNumber, ""));
}

std::vector<std::string> CoilCoolingDXCurveFitOperatingMode_Impl::condenserTypeValues() const {
  return openstudio::epmodel::CoilCoolingDXCurveFitOperatingMode::condenserTypeValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
