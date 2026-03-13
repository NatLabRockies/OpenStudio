/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/CoilCoolingDXSingleSpeed.hpp"
#include "StraightComponent/CoilCoolingDXSingleSpeed_Impl.hpp"

#include "Loop/AirLoopHVAC.hpp"
#include "HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "ModelObject/CoilSystemCoolingDX.hpp"
#include "ModelObject/CoilSystemCoolingDX_Impl.hpp"
#include "Model.hpp"
#include "Node.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/Coil_Cooling_DX_SingleSpeed_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

CoilCoolingDXSingleSpeed::CoilCoolingDXSingleSpeed(const Model& model) : StraightComponent(CoilCoolingDXSingleSpeed::iddObjectType(), model) {
  auto impl = getImpl<detail::CoilCoolingDXSingleSpeed_Impl>();
  OS_ASSERT(impl);
  detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
  impl->canonicalize(context);
}

CoilCoolingDXSingleSpeed::CoilCoolingDXSingleSpeed(std::shared_ptr<detail::CoilCoolingDXSingleSpeed_Impl> impl)
  : StraightComponent(std::move(impl)) {}

IddObjectType CoilCoolingDXSingleSpeed::iddObjectType() {
  return IddObjectType::Coil_Cooling_DX_SingleSpeed;
}

std::vector<std::string> CoilCoolingDXSingleSpeed::condenserTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::Coil_Cooling_DX_SingleSpeedFields::CondenserType);
}

std::string CoilCoolingDXSingleSpeed::condenserType() const {
  return getImpl<detail::CoilCoolingDXSingleSpeed_Impl>()->condenserType();
}

bool CoilCoolingDXSingleSpeed::setCondenserType(const std::string& condenserType) {
  return getImpl<detail::CoilCoolingDXSingleSpeed_Impl>()->setCondenserType(condenserType);
}

double CoilCoolingDXSingleSpeed::ratedCOP() const {
  return getImpl<detail::CoilCoolingDXSingleSpeed_Impl>()->ratedCOP();
}

bool CoilCoolingDXSingleSpeed::setRatedCOP(double ratedCOP) {
  return getImpl<detail::CoilCoolingDXSingleSpeed_Impl>()->setRatedCOP(ratedCOP);
}

double CoilCoolingDXSingleSpeed::ratedEvaporatorFanPowerPerVolumeFlowRate2017() const {
  return getImpl<detail::CoilCoolingDXSingleSpeed_Impl>()->ratedEvaporatorFanPowerPerVolumeFlowRate2017();
}

bool CoilCoolingDXSingleSpeed::setRatedEvaporatorFanPowerPerVolumeFlowRate2017(double ratedEvaporatorFanPowerPerVolumeFlowRate2017) {
  return getImpl<detail::CoilCoolingDXSingleSpeed_Impl>()->setRatedEvaporatorFanPowerPerVolumeFlowRate2017(
    ratedEvaporatorFanPowerPerVolumeFlowRate2017);
}

double CoilCoolingDXSingleSpeed::ratedEvaporatorFanPowerPerVolumeFlowRate2023() const {
  return getImpl<detail::CoilCoolingDXSingleSpeed_Impl>()->ratedEvaporatorFanPowerPerVolumeFlowRate2023();
}

bool CoilCoolingDXSingleSpeed::setRatedEvaporatorFanPowerPerVolumeFlowRate2023(double ratedEvaporatorFanPowerPerVolumeFlowRate2023) {
  return getImpl<detail::CoilCoolingDXSingleSpeed_Impl>()->setRatedEvaporatorFanPowerPerVolumeFlowRate2023(
    ratedEvaporatorFanPowerPerVolumeFlowRate2023);
}

boost::optional<double> CoilCoolingDXSingleSpeed::ratedTotalCoolingCapacity() const {
  return getImpl<detail::CoilCoolingDXSingleSpeed_Impl>()->ratedTotalCoolingCapacity();
}

bool CoilCoolingDXSingleSpeed::isRatedTotalCoolingCapacityAutosized() const {
  return getImpl<detail::CoilCoolingDXSingleSpeed_Impl>()->isRatedTotalCoolingCapacityAutosized();
}

bool CoilCoolingDXSingleSpeed::setRatedTotalCoolingCapacity(double ratedTotalCoolingCapacity) {
  return getImpl<detail::CoilCoolingDXSingleSpeed_Impl>()->setRatedTotalCoolingCapacity(ratedTotalCoolingCapacity);
}

void CoilCoolingDXSingleSpeed::autosizeRatedTotalCoolingCapacity() {
  getImpl<detail::CoilCoolingDXSingleSpeed_Impl>()->autosizeRatedTotalCoolingCapacity();
}

boost::optional<double> CoilCoolingDXSingleSpeed::ratedSensibleHeatRatio() const {
  return getImpl<detail::CoilCoolingDXSingleSpeed_Impl>()->ratedSensibleHeatRatio();
}

bool CoilCoolingDXSingleSpeed::isRatedSensibleHeatRatioAutosized() const {
  return getImpl<detail::CoilCoolingDXSingleSpeed_Impl>()->isRatedSensibleHeatRatioAutosized();
}

bool CoilCoolingDXSingleSpeed::setRatedSensibleHeatRatio(double ratedSensibleHeatRatio) {
  return getImpl<detail::CoilCoolingDXSingleSpeed_Impl>()->setRatedSensibleHeatRatio(ratedSensibleHeatRatio);
}

void CoilCoolingDXSingleSpeed::autosizeRatedSensibleHeatRatio() {
  getImpl<detail::CoilCoolingDXSingleSpeed_Impl>()->autosizeRatedSensibleHeatRatio();
}

boost::optional<double> CoilCoolingDXSingleSpeed::ratedAirFlowRate() const {
  return getImpl<detail::CoilCoolingDXSingleSpeed_Impl>()->ratedAirFlowRate();
}

bool CoilCoolingDXSingleSpeed::isRatedAirFlowRateAutosized() const {
  return getImpl<detail::CoilCoolingDXSingleSpeed_Impl>()->isRatedAirFlowRateAutosized();
}

bool CoilCoolingDXSingleSpeed::setRatedAirFlowRate(double ratedAirFlowRate) {
  return getImpl<detail::CoilCoolingDXSingleSpeed_Impl>()->setRatedAirFlowRate(ratedAirFlowRate);
}

void CoilCoolingDXSingleSpeed::autosizeRatedAirFlowRate() {
  getImpl<detail::CoilCoolingDXSingleSpeed_Impl>()->autosizeRatedAirFlowRate();
}

double CoilCoolingDXSingleSpeed::nominalTimeForCondensateRemovalToBegin() const {
  return getImpl<detail::CoilCoolingDXSingleSpeed_Impl>()->nominalTimeForCondensateRemovalToBegin();
}

bool CoilCoolingDXSingleSpeed::setNominalTimeForCondensateRemovalToBegin(double nominalTimeForCondensateRemovalToBegin) {
  return getImpl<detail::CoilCoolingDXSingleSpeed_Impl>()->setNominalTimeForCondensateRemovalToBegin(nominalTimeForCondensateRemovalToBegin);
}

double CoilCoolingDXSingleSpeed::ratioOfInitialMoistureEvaporationRateAndSteadyStateLatentCapacity() const {
  return getImpl<detail::CoilCoolingDXSingleSpeed_Impl>()->ratioOfInitialMoistureEvaporationRateAndSteadyStateLatentCapacity();
}

bool CoilCoolingDXSingleSpeed::setRatioOfInitialMoistureEvaporationRateAndSteadyStateLatentCapacity(
  double ratioOfInitialMoistureEvaporationRateAndSteadyStateLatentCapacity) {
  return getImpl<detail::CoilCoolingDXSingleSpeed_Impl>()->setRatioOfInitialMoistureEvaporationRateAndSteadyStateLatentCapacity(
    ratioOfInitialMoistureEvaporationRateAndSteadyStateLatentCapacity);
}

double CoilCoolingDXSingleSpeed::maximumCyclingRate() const {
  return getImpl<detail::CoilCoolingDXSingleSpeed_Impl>()->maximumCyclingRate();
}

bool CoilCoolingDXSingleSpeed::setMaximumCyclingRate(double maximumCyclingRate) {
  return getImpl<detail::CoilCoolingDXSingleSpeed_Impl>()->setMaximumCyclingRate(maximumCyclingRate);
}

double CoilCoolingDXSingleSpeed::latentCapacityTimeConstant() const {
  return getImpl<detail::CoilCoolingDXSingleSpeed_Impl>()->latentCapacityTimeConstant();
}

bool CoilCoolingDXSingleSpeed::setLatentCapacityTimeConstant(double latentCapacityTimeConstant) {
  return getImpl<detail::CoilCoolingDXSingleSpeed_Impl>()->setLatentCapacityTimeConstant(latentCapacityTimeConstant);
}

double CoilCoolingDXSingleSpeed::evaporativeCondenserEffectiveness() const {
  return getImpl<detail::CoilCoolingDXSingleSpeed_Impl>()->evaporativeCondenserEffectiveness();
}

bool CoilCoolingDXSingleSpeed::setEvaporativeCondenserEffectiveness(double evaporativeCondenserEffectiveness) {
  return getImpl<detail::CoilCoolingDXSingleSpeed_Impl>()->setEvaporativeCondenserEffectiveness(evaporativeCondenserEffectiveness);
}

boost::optional<double> CoilCoolingDXSingleSpeed::evaporativeCondenserAirFlowRate() const {
  return getImpl<detail::CoilCoolingDXSingleSpeed_Impl>()->evaporativeCondenserAirFlowRate();
}

bool CoilCoolingDXSingleSpeed::isEvaporativeCondenserAirFlowRateAutosized() const {
  return getImpl<detail::CoilCoolingDXSingleSpeed_Impl>()->isEvaporativeCondenserAirFlowRateAutosized();
}

bool CoilCoolingDXSingleSpeed::setEvaporativeCondenserAirFlowRate(double evaporativeCondenserAirFlowRate) {
  return getImpl<detail::CoilCoolingDXSingleSpeed_Impl>()->setEvaporativeCondenserAirFlowRate(evaporativeCondenserAirFlowRate);
}

void CoilCoolingDXSingleSpeed::autosizeEvaporativeCondenserAirFlowRate() {
  getImpl<detail::CoilCoolingDXSingleSpeed_Impl>()->autosizeEvaporativeCondenserAirFlowRate();
}

boost::optional<double> CoilCoolingDXSingleSpeed::evaporativeCondenserPumpRatedPowerConsumption() const {
  return getImpl<detail::CoilCoolingDXSingleSpeed_Impl>()->evaporativeCondenserPumpRatedPowerConsumption();
}

bool CoilCoolingDXSingleSpeed::isEvaporativeCondenserPumpRatedPowerConsumptionAutosized() const {
  return getImpl<detail::CoilCoolingDXSingleSpeed_Impl>()->isEvaporativeCondenserPumpRatedPowerConsumptionAutosized();
}

bool CoilCoolingDXSingleSpeed::setEvaporativeCondenserPumpRatedPowerConsumption(double evaporativeCondenserPumpRatedPowerConsumption) {
  return getImpl<detail::CoilCoolingDXSingleSpeed_Impl>()->setEvaporativeCondenserPumpRatedPowerConsumption(
    evaporativeCondenserPumpRatedPowerConsumption);
}

void CoilCoolingDXSingleSpeed::autosizeEvaporativeCondenserPumpRatedPowerConsumption() {
  getImpl<detail::CoilCoolingDXSingleSpeed_Impl>()->autosizeEvaporativeCondenserPumpRatedPowerConsumption();
}

double CoilCoolingDXSingleSpeed::crankcaseHeaterCapacity() const {
  return getImpl<detail::CoilCoolingDXSingleSpeed_Impl>()->crankcaseHeaterCapacity();
}

bool CoilCoolingDXSingleSpeed::setCrankcaseHeaterCapacity(double crankcaseHeaterCapacity) {
  return getImpl<detail::CoilCoolingDXSingleSpeed_Impl>()->setCrankcaseHeaterCapacity(crankcaseHeaterCapacity);
}

double CoilCoolingDXSingleSpeed::maximumOutdoorDryBulbTemperatureForCrankcaseHeaterOperation() const {
  return getImpl<detail::CoilCoolingDXSingleSpeed_Impl>()->maximumOutdoorDryBulbTemperatureForCrankcaseHeaterOperation();
}

bool CoilCoolingDXSingleSpeed::setMaximumOutdoorDryBulbTemperatureForCrankcaseHeaterOperation(
  double maximumOutdoorDryBulbTemperatureForCrankcaseHeaterOperation) {
  return getImpl<detail::CoilCoolingDXSingleSpeed_Impl>()->setMaximumOutdoorDryBulbTemperatureForCrankcaseHeaterOperation(
    maximumOutdoorDryBulbTemperatureForCrankcaseHeaterOperation);
}

double CoilCoolingDXSingleSpeed::basinHeaterCapacity() const {
  return getImpl<detail::CoilCoolingDXSingleSpeed_Impl>()->basinHeaterCapacity();
}

bool CoilCoolingDXSingleSpeed::setBasinHeaterCapacity(double basinHeaterCapacity) {
  return getImpl<detail::CoilCoolingDXSingleSpeed_Impl>()->setBasinHeaterCapacity(basinHeaterCapacity);
}

double CoilCoolingDXSingleSpeed::basinHeaterSetpointTemperature() const {
  return getImpl<detail::CoilCoolingDXSingleSpeed_Impl>()->basinHeaterSetpointTemperature();
}

bool CoilCoolingDXSingleSpeed::setBasinHeaterSetpointTemperature(double basinHeaterSetpointTemperature) {
  return getImpl<detail::CoilCoolingDXSingleSpeed_Impl>()->setBasinHeaterSetpointTemperature(basinHeaterSetpointTemperature);
}

double CoilCoolingDXSingleSpeed::minimumOutdoorDryBulbTemperatureforCompressorOperation() const {
  return getImpl<detail::CoilCoolingDXSingleSpeed_Impl>()->minimumOutdoorDryBulbTemperatureforCompressorOperation();
}

bool CoilCoolingDXSingleSpeed::setMinimumOutdoorDryBulbTemperatureforCompressorOperation(
  double minimumOutdoorDryBulbTemperatureforCompressorOperation) {
  return getImpl<detail::CoilCoolingDXSingleSpeed_Impl>()->setMinimumOutdoorDryBulbTemperatureforCompressorOperation(
    minimumOutdoorDryBulbTemperatureforCompressorOperation);
}

bool CoilCoolingDXSingleSpeed::addToNode(Node& node) {
  return getImpl<detail::CoilCoolingDXSingleSpeed_Impl>()->addToNode(node);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

unsigned CoilCoolingDXSingleSpeed_Impl::inletPort() const {
  return openstudio::Coil_Cooling_DX_SingleSpeedFields::AirInletNodeName;
}

unsigned CoilCoolingDXSingleSpeed_Impl::outletPort() const {
  return openstudio::Coil_Cooling_DX_SingleSpeedFields::AirOutletNodeName;
}

std::vector<std::string> CoilCoolingDXSingleSpeed_Impl::condenserTypeValues() const {
  return CoilCoolingDXSingleSpeed::condenserTypeValues();
}

std::string CoilCoolingDXSingleSpeed_Impl::condenserType() const {
  const auto value = getString(openstudio::Coil_Cooling_DX_SingleSpeedFields::CondenserType, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilCoolingDXSingleSpeed_Impl::setCondenserType(const std::string& condenserType) {
  return setString(openstudio::Coil_Cooling_DX_SingleSpeedFields::CondenserType, condenserType);
}

double CoilCoolingDXSingleSpeed_Impl::ratedCOP() const {
  const auto value = getDouble(openstudio::Coil_Cooling_DX_SingleSpeedFields::GrossRatedCoolingCOP, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilCoolingDXSingleSpeed_Impl::setRatedCOP(double ratedCOP) {
  return setDouble(openstudio::Coil_Cooling_DX_SingleSpeedFields::GrossRatedCoolingCOP, ratedCOP);
}

double CoilCoolingDXSingleSpeed_Impl::ratedEvaporatorFanPowerPerVolumeFlowRate2017() const {
  const auto value =
    getDouble(openstudio::Coil_Cooling_DX_SingleSpeedFields::RatedEvaporatorFanPowerPerVolumeFlowRate2017, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilCoolingDXSingleSpeed_Impl::setRatedEvaporatorFanPowerPerVolumeFlowRate2017(double ratedEvaporatorFanPowerPerVolumeFlowRate2017) {
  return setDouble(openstudio::Coil_Cooling_DX_SingleSpeedFields::RatedEvaporatorFanPowerPerVolumeFlowRate2017,
                   ratedEvaporatorFanPowerPerVolumeFlowRate2017);
}

double CoilCoolingDXSingleSpeed_Impl::ratedEvaporatorFanPowerPerVolumeFlowRate2023() const {
  const auto value =
    getDouble(openstudio::Coil_Cooling_DX_SingleSpeedFields::RatedEvaporatorFanPowerPerVolumeFlowRate2023, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilCoolingDXSingleSpeed_Impl::setRatedEvaporatorFanPowerPerVolumeFlowRate2023(double ratedEvaporatorFanPowerPerVolumeFlowRate2023) {
  return setDouble(openstudio::Coil_Cooling_DX_SingleSpeedFields::RatedEvaporatorFanPowerPerVolumeFlowRate2023,
                   ratedEvaporatorFanPowerPerVolumeFlowRate2023);
}

boost::optional<double> CoilCoolingDXSingleSpeed_Impl::ratedTotalCoolingCapacity() const {
  return getDouble(openstudio::Coil_Cooling_DX_SingleSpeedFields::GrossRatedTotalCoolingCapacity, true);
}

bool CoilCoolingDXSingleSpeed_Impl::isRatedTotalCoolingCapacityAutosized() const {
  if (const auto value = getString(openstudio::Coil_Cooling_DX_SingleSpeedFields::GrossRatedTotalCoolingCapacity, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool CoilCoolingDXSingleSpeed_Impl::setRatedTotalCoolingCapacity(double ratedTotalCoolingCapacity) {
  return setDouble(openstudio::Coil_Cooling_DX_SingleSpeedFields::GrossRatedTotalCoolingCapacity, ratedTotalCoolingCapacity);
}

void CoilCoolingDXSingleSpeed_Impl::autosizeRatedTotalCoolingCapacity() {
  const bool result = setString(openstudio::Coil_Cooling_DX_SingleSpeedFields::GrossRatedTotalCoolingCapacity, "autosize");
  OS_ASSERT(result);
}

boost::optional<double> CoilCoolingDXSingleSpeed_Impl::ratedSensibleHeatRatio() const {
  return getDouble(openstudio::Coil_Cooling_DX_SingleSpeedFields::GrossRatedSensibleHeatRatio, true);
}

bool CoilCoolingDXSingleSpeed_Impl::isRatedSensibleHeatRatioAutosized() const {
  if (const auto value = getString(openstudio::Coil_Cooling_DX_SingleSpeedFields::GrossRatedSensibleHeatRatio, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool CoilCoolingDXSingleSpeed_Impl::setRatedSensibleHeatRatio(double ratedSensibleHeatRatio) {
  return setDouble(openstudio::Coil_Cooling_DX_SingleSpeedFields::GrossRatedSensibleHeatRatio, ratedSensibleHeatRatio);
}

void CoilCoolingDXSingleSpeed_Impl::autosizeRatedSensibleHeatRatio() {
  const bool result = setString(openstudio::Coil_Cooling_DX_SingleSpeedFields::GrossRatedSensibleHeatRatio, "autosize");
  OS_ASSERT(result);
}

boost::optional<double> CoilCoolingDXSingleSpeed_Impl::ratedAirFlowRate() const {
  return getDouble(openstudio::Coil_Cooling_DX_SingleSpeedFields::RatedAirFlowRate, true);
}

bool CoilCoolingDXSingleSpeed_Impl::isRatedAirFlowRateAutosized() const {
  if (const auto value = getString(openstudio::Coil_Cooling_DX_SingleSpeedFields::RatedAirFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool CoilCoolingDXSingleSpeed_Impl::setRatedAirFlowRate(double ratedAirFlowRate) {
  return setDouble(openstudio::Coil_Cooling_DX_SingleSpeedFields::RatedAirFlowRate, ratedAirFlowRate);
}

void CoilCoolingDXSingleSpeed_Impl::autosizeRatedAirFlowRate() {
  const bool result = setString(openstudio::Coil_Cooling_DX_SingleSpeedFields::RatedAirFlowRate, "autosize");
  OS_ASSERT(result);
}

double CoilCoolingDXSingleSpeed_Impl::nominalTimeForCondensateRemovalToBegin() const {
  const auto value = getDouble(openstudio::Coil_Cooling_DX_SingleSpeedFields::NominalTimeforCondensateRemovaltoBegin, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilCoolingDXSingleSpeed_Impl::setNominalTimeForCondensateRemovalToBegin(double nominalTimeForCondensateRemovalToBegin) {
  return setDouble(openstudio::Coil_Cooling_DX_SingleSpeedFields::NominalTimeforCondensateRemovaltoBegin,
                   nominalTimeForCondensateRemovalToBegin);
}

double CoilCoolingDXSingleSpeed_Impl::ratioOfInitialMoistureEvaporationRateAndSteadyStateLatentCapacity() const {
  const auto value = getDouble(
    openstudio::Coil_Cooling_DX_SingleSpeedFields::RatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilCoolingDXSingleSpeed_Impl::setRatioOfInitialMoistureEvaporationRateAndSteadyStateLatentCapacity(
  double ratioOfInitialMoistureEvaporationRateAndSteadyStateLatentCapacity) {
  return setDouble(openstudio::Coil_Cooling_DX_SingleSpeedFields::RatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity,
                   ratioOfInitialMoistureEvaporationRateAndSteadyStateLatentCapacity);
}

double CoilCoolingDXSingleSpeed_Impl::maximumCyclingRate() const {
  const auto value = getDouble(openstudio::Coil_Cooling_DX_SingleSpeedFields::MaximumCyclingRate, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilCoolingDXSingleSpeed_Impl::setMaximumCyclingRate(double maximumCyclingRate) {
  return setDouble(openstudio::Coil_Cooling_DX_SingleSpeedFields::MaximumCyclingRate, maximumCyclingRate);
}

double CoilCoolingDXSingleSpeed_Impl::latentCapacityTimeConstant() const {
  const auto value = getDouble(openstudio::Coil_Cooling_DX_SingleSpeedFields::LatentCapacityTimeConstant, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilCoolingDXSingleSpeed_Impl::setLatentCapacityTimeConstant(double latentCapacityTimeConstant) {
  return setDouble(openstudio::Coil_Cooling_DX_SingleSpeedFields::LatentCapacityTimeConstant, latentCapacityTimeConstant);
}

double CoilCoolingDXSingleSpeed_Impl::evaporativeCondenserEffectiveness() const {
  const auto value = getDouble(openstudio::Coil_Cooling_DX_SingleSpeedFields::EvaporativeCondenserEffectiveness, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilCoolingDXSingleSpeed_Impl::setEvaporativeCondenserEffectiveness(double evaporativeCondenserEffectiveness) {
  return setDouble(openstudio::Coil_Cooling_DX_SingleSpeedFields::EvaporativeCondenserEffectiveness, evaporativeCondenserEffectiveness);
}

boost::optional<double> CoilCoolingDXSingleSpeed_Impl::evaporativeCondenserAirFlowRate() const {
  return getDouble(openstudio::Coil_Cooling_DX_SingleSpeedFields::EvaporativeCondenserAirFlowRate, true);
}

bool CoilCoolingDXSingleSpeed_Impl::isEvaporativeCondenserAirFlowRateAutosized() const {
  if (const auto value = getString(openstudio::Coil_Cooling_DX_SingleSpeedFields::EvaporativeCondenserAirFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool CoilCoolingDXSingleSpeed_Impl::setEvaporativeCondenserAirFlowRate(double evaporativeCondenserAirFlowRate) {
  return setDouble(openstudio::Coil_Cooling_DX_SingleSpeedFields::EvaporativeCondenserAirFlowRate, evaporativeCondenserAirFlowRate);
}

void CoilCoolingDXSingleSpeed_Impl::autosizeEvaporativeCondenserAirFlowRate() {
  const bool result = setString(openstudio::Coil_Cooling_DX_SingleSpeedFields::EvaporativeCondenserAirFlowRate, "autosize");
  OS_ASSERT(result);
}

boost::optional<double> CoilCoolingDXSingleSpeed_Impl::evaporativeCondenserPumpRatedPowerConsumption() const {
  return getDouble(openstudio::Coil_Cooling_DX_SingleSpeedFields::EvaporativeCondenserPumpRatedPowerConsumption, true);
}

bool CoilCoolingDXSingleSpeed_Impl::isEvaporativeCondenserPumpRatedPowerConsumptionAutosized() const {
  if (const auto value =
        getString(openstudio::Coil_Cooling_DX_SingleSpeedFields::EvaporativeCondenserPumpRatedPowerConsumption, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool CoilCoolingDXSingleSpeed_Impl::setEvaporativeCondenserPumpRatedPowerConsumption(double evaporativeCondenserPumpRatedPowerConsumption) {
  return setDouble(openstudio::Coil_Cooling_DX_SingleSpeedFields::EvaporativeCondenserPumpRatedPowerConsumption,
                   evaporativeCondenserPumpRatedPowerConsumption);
}

void CoilCoolingDXSingleSpeed_Impl::autosizeEvaporativeCondenserPumpRatedPowerConsumption() {
  const bool result = setString(openstudio::Coil_Cooling_DX_SingleSpeedFields::EvaporativeCondenserPumpRatedPowerConsumption, "autosize");
  OS_ASSERT(result);
}

double CoilCoolingDXSingleSpeed_Impl::crankcaseHeaterCapacity() const {
  const auto value = getDouble(openstudio::Coil_Cooling_DX_SingleSpeedFields::CrankcaseHeaterCapacity, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilCoolingDXSingleSpeed_Impl::setCrankcaseHeaterCapacity(double crankcaseHeaterCapacity) {
  return setDouble(openstudio::Coil_Cooling_DX_SingleSpeedFields::CrankcaseHeaterCapacity, crankcaseHeaterCapacity);
}

double CoilCoolingDXSingleSpeed_Impl::maximumOutdoorDryBulbTemperatureForCrankcaseHeaterOperation() const {
  const auto value =
    getDouble(openstudio::Coil_Cooling_DX_SingleSpeedFields::MaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilCoolingDXSingleSpeed_Impl::setMaximumOutdoorDryBulbTemperatureForCrankcaseHeaterOperation(
  double maximumOutdoorDryBulbTemperatureForCrankcaseHeaterOperation) {
  return setDouble(openstudio::Coil_Cooling_DX_SingleSpeedFields::MaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation,
                   maximumOutdoorDryBulbTemperatureForCrankcaseHeaterOperation);
}

double CoilCoolingDXSingleSpeed_Impl::basinHeaterCapacity() const {
  const auto value = getDouble(openstudio::Coil_Cooling_DX_SingleSpeedFields::BasinHeaterCapacity, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilCoolingDXSingleSpeed_Impl::setBasinHeaterCapacity(double basinHeaterCapacity) {
  return setDouble(openstudio::Coil_Cooling_DX_SingleSpeedFields::BasinHeaterCapacity, basinHeaterCapacity);
}

double CoilCoolingDXSingleSpeed_Impl::basinHeaterSetpointTemperature() const {
  const auto value = getDouble(openstudio::Coil_Cooling_DX_SingleSpeedFields::BasinHeaterSetpointTemperature, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilCoolingDXSingleSpeed_Impl::setBasinHeaterSetpointTemperature(double basinHeaterSetpointTemperature) {
  return setDouble(openstudio::Coil_Cooling_DX_SingleSpeedFields::BasinHeaterSetpointTemperature, basinHeaterSetpointTemperature);
}

double CoilCoolingDXSingleSpeed_Impl::minimumOutdoorDryBulbTemperatureforCompressorOperation() const {
  const auto value =
    getDouble(openstudio::Coil_Cooling_DX_SingleSpeedFields::MinimumOutdoorDryBulbTemperatureforCompressorOperation, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilCoolingDXSingleSpeed_Impl::setMinimumOutdoorDryBulbTemperatureforCompressorOperation(
  double minimumOutdoorDryBulbTemperatureforCompressorOperation) {
  return setDouble(openstudio::Coil_Cooling_DX_SingleSpeedFields::MinimumOutdoorDryBulbTemperatureforCompressorOperation,
                   minimumOutdoorDryBulbTemperatureforCompressorOperation);
}

bool CoilCoolingDXSingleSpeed_Impl::addToNode(Node& node) {
  auto airLoop = node.airLoopHVAC();

  if (!(airLoop && airLoop->supplyComponent(node.handle()))) {
    return false;
  }

  return StraightComponent_Impl::addToNode(node);
}

boost::optional<CoilSystemCoolingDX> CoilCoolingDXSingleSpeed_Impl::coilSystemCoolingDX() const {
  const auto thisHandle = handle();

  for (const auto& system : model().getConcreteModelObjects<CoilSystemCoolingDX>()) {
    auto systemImpl = system.getImpl<openstudio::epmodel::detail::CoilSystemCoolingDX_Impl>();
    OS_ASSERT(systemImpl);
    auto coolingCoil = systemImpl->coolingCoil();
    if (coolingCoil && (coolingCoil->handle() == thisHandle)) {
      return system;
    }
  }

  return boost::none;
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
