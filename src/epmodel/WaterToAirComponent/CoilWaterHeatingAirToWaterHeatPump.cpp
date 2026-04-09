/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "WaterToAirComponent/CoilWaterHeatingAirToWaterHeatPump.hpp"
#include "WaterToAirComponent/CoilWaterHeatingAirToWaterHeatPump_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/Coil_WaterHeating_AirToWaterHeatPump_Pumped_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

CoilWaterHeatingAirToWaterHeatPump::CoilWaterHeatingAirToWaterHeatPump(const Model& model)
  : WaterToAirComponent(CoilWaterHeatingAirToWaterHeatPump::iddObjectType(), model) {}

CoilWaterHeatingAirToWaterHeatPump::CoilWaterHeatingAirToWaterHeatPump(std::shared_ptr<detail::CoilWaterHeatingAirToWaterHeatPump_Impl> impl)
  : WaterToAirComponent(std::move(impl)) {}

IddObjectType CoilWaterHeatingAirToWaterHeatPump::iddObjectType() {
  return IddObjectType::Coil_WaterHeating_AirToWaterHeatPump_Pumped;
}

std::vector<std::string> CoilWaterHeatingAirToWaterHeatPump::evaporatorAirTemperatureTypeforCurveObjectsValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::EvaporatorAirTemperatureTypeforCurveObjects);
}

double CoilWaterHeatingAirToWaterHeatPump::ratedHeatingCapacity() const {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPump_Impl>()->ratedHeatingCapacity();
}

bool CoilWaterHeatingAirToWaterHeatPump::setRatedHeatingCapacity(double ratedHeatingCapacity) {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPump_Impl>()->setRatedHeatingCapacity(ratedHeatingCapacity);
}

double CoilWaterHeatingAirToWaterHeatPump::ratedCOP() const {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPump_Impl>()->ratedCOP();
}

bool CoilWaterHeatingAirToWaterHeatPump::setRatedCOP(double ratedCOP) {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPump_Impl>()->setRatedCOP(ratedCOP);
}

double CoilWaterHeatingAirToWaterHeatPump::ratedSensibleHeatRatio() const {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPump_Impl>()->ratedSensibleHeatRatio();
}

bool CoilWaterHeatingAirToWaterHeatPump::setRatedSensibleHeatRatio(double ratedSensibleHeatRatio) {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPump_Impl>()->setRatedSensibleHeatRatio(ratedSensibleHeatRatio);
}

double CoilWaterHeatingAirToWaterHeatPump::ratedEvaporatorInletAirDryBulbTemperature() const {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPump_Impl>()->ratedEvaporatorInletAirDryBulbTemperature();
}

bool CoilWaterHeatingAirToWaterHeatPump::setRatedEvaporatorInletAirDryBulbTemperature(double ratedEvaporatorInletAirDryBulbTemperature) {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPump_Impl>()->setRatedEvaporatorInletAirDryBulbTemperature(
    ratedEvaporatorInletAirDryBulbTemperature);
}

double CoilWaterHeatingAirToWaterHeatPump::ratedEvaporatorInletAirWetBulbTemperature() const {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPump_Impl>()->ratedEvaporatorInletAirWetBulbTemperature();
}

bool CoilWaterHeatingAirToWaterHeatPump::setRatedEvaporatorInletAirWetBulbTemperature(double ratedEvaporatorInletAirWetBulbTemperature) {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPump_Impl>()->setRatedEvaporatorInletAirWetBulbTemperature(
    ratedEvaporatorInletAirWetBulbTemperature);
}

double CoilWaterHeatingAirToWaterHeatPump::ratedCondenserInletWaterTemperature() const {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPump_Impl>()->ratedCondenserInletWaterTemperature();
}

bool CoilWaterHeatingAirToWaterHeatPump::setRatedCondenserInletWaterTemperature(double ratedCondenserInletWaterTemperature) {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPump_Impl>()->setRatedCondenserInletWaterTemperature(ratedCondenserInletWaterTemperature);
}

boost::optional<double> CoilWaterHeatingAirToWaterHeatPump::ratedEvaporatorAirFlowRate() const {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPump_Impl>()->ratedEvaporatorAirFlowRate();
}

bool CoilWaterHeatingAirToWaterHeatPump::isRatedEvaporatorAirFlowRateAutosized() const {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPump_Impl>()->isRatedEvaporatorAirFlowRateAutosized();
}

bool CoilWaterHeatingAirToWaterHeatPump::setRatedEvaporatorAirFlowRate(double ratedEvaporatorAirFlowRate) {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPump_Impl>()->setRatedEvaporatorAirFlowRate(ratedEvaporatorAirFlowRate);
}

void CoilWaterHeatingAirToWaterHeatPump::autosizeRatedEvaporatorAirFlowRate() {
  getImpl<detail::CoilWaterHeatingAirToWaterHeatPump_Impl>()->autosizeRatedEvaporatorAirFlowRate();
}

boost::optional<double> CoilWaterHeatingAirToWaterHeatPump::ratedCondenserWaterFlowRate() const {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPump_Impl>()->ratedCondenserWaterFlowRate();
}

bool CoilWaterHeatingAirToWaterHeatPump::isRatedCondenserWaterFlowRateAutosized() const {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPump_Impl>()->isRatedCondenserWaterFlowRateAutosized();
}

bool CoilWaterHeatingAirToWaterHeatPump::setRatedCondenserWaterFlowRate(double ratedCondenserWaterFlowRate) {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPump_Impl>()->setRatedCondenserWaterFlowRate(ratedCondenserWaterFlowRate);
}

void CoilWaterHeatingAirToWaterHeatPump::autosizeRatedCondenserWaterFlowRate() {
  getImpl<detail::CoilWaterHeatingAirToWaterHeatPump_Impl>()->autosizeRatedCondenserWaterFlowRate();
}

bool CoilWaterHeatingAirToWaterHeatPump::evaporatorFanPowerIncludedinRatedCOP() const {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPump_Impl>()->evaporatorFanPowerIncludedinRatedCOP();
}

bool CoilWaterHeatingAirToWaterHeatPump::setEvaporatorFanPowerIncludedinRatedCOP(bool evaporatorFanPowerIncludedinRatedCOP) {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPump_Impl>()->setEvaporatorFanPowerIncludedinRatedCOP(
    evaporatorFanPowerIncludedinRatedCOP);
}

bool CoilWaterHeatingAirToWaterHeatPump::condenserPumpPowerIncludedinRatedCOP() const {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPump_Impl>()->condenserPumpPowerIncludedinRatedCOP();
}

bool CoilWaterHeatingAirToWaterHeatPump::setCondenserPumpPowerIncludedinRatedCOP(bool condenserPumpPowerIncludedinRatedCOP) {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPump_Impl>()->setCondenserPumpPowerIncludedinRatedCOP(
    condenserPumpPowerIncludedinRatedCOP);
}

bool CoilWaterHeatingAirToWaterHeatPump::condenserPumpHeatIncludedinRatedHeatingCapacityandRatedCOP() const {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPump_Impl>()->condenserPumpHeatIncludedinRatedHeatingCapacityandRatedCOP();
}

bool CoilWaterHeatingAirToWaterHeatPump::setCondenserPumpHeatIncludedinRatedHeatingCapacityandRatedCOP(
  bool condenserPumpHeatIncludedinRatedHeatingCapacityandRatedCOP) {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPump_Impl>()->setCondenserPumpHeatIncludedinRatedHeatingCapacityandRatedCOP(
    condenserPumpHeatIncludedinRatedHeatingCapacityandRatedCOP);
}

double CoilWaterHeatingAirToWaterHeatPump::condenserWaterPumpPower() const {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPump_Impl>()->condenserWaterPumpPower();
}

bool CoilWaterHeatingAirToWaterHeatPump::setCondenserWaterPumpPower(double condenserWaterPumpPower) {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPump_Impl>()->setCondenserWaterPumpPower(condenserWaterPumpPower);
}

double CoilWaterHeatingAirToWaterHeatPump::fractionofCondenserPumpHeattoWater() const {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPump_Impl>()->fractionofCondenserPumpHeattoWater();
}

bool CoilWaterHeatingAirToWaterHeatPump::setFractionofCondenserPumpHeattoWater(double fractionofCondenserPumpHeattoWater) {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPump_Impl>()->setFractionofCondenserPumpHeattoWater(
    fractionofCondenserPumpHeattoWater);
}

double CoilWaterHeatingAirToWaterHeatPump::crankcaseHeaterCapacity() const {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPump_Impl>()->crankcaseHeaterCapacity();
}

bool CoilWaterHeatingAirToWaterHeatPump::setCrankcaseHeaterCapacity(double crankcaseHeaterCapacity) {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPump_Impl>()->setCrankcaseHeaterCapacity(crankcaseHeaterCapacity);
}

double CoilWaterHeatingAirToWaterHeatPump::maximumAmbientTemperatureforCrankcaseHeaterOperation() const {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPump_Impl>()->maximumAmbientTemperatureforCrankcaseHeaterOperation();
}

bool CoilWaterHeatingAirToWaterHeatPump::setMaximumAmbientTemperatureforCrankcaseHeaterOperation(
  double maximumAmbientTemperatureforCrankcaseHeaterOperation) {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPump_Impl>()->setMaximumAmbientTemperatureforCrankcaseHeaterOperation(
    maximumAmbientTemperatureforCrankcaseHeaterOperation);
}

std::string CoilWaterHeatingAirToWaterHeatPump::evaporatorAirTemperatureTypeforCurveObjects() const {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPump_Impl>()->evaporatorAirTemperatureTypeforCurveObjects();
}

bool CoilWaterHeatingAirToWaterHeatPump::setEvaporatorAirTemperatureTypeforCurveObjects(
  const std::string& evaporatorAirTemperatureTypeforCurveObjects) {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPump_Impl>()->setEvaporatorAirTemperatureTypeforCurveObjects(
    evaporatorAirTemperatureTypeforCurveObjects);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

unsigned CoilWaterHeatingAirToWaterHeatPump_Impl::airInletPort() const {
  return openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::EvaporatorAirInletNodeName;
}

unsigned CoilWaterHeatingAirToWaterHeatPump_Impl::airOutletPort() const {
  return openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::EvaporatorAirOutletNodeName;
}

unsigned CoilWaterHeatingAirToWaterHeatPump_Impl::waterInletPort() const {
  return openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::CondenserWaterInletNodeName;
}

unsigned CoilWaterHeatingAirToWaterHeatPump_Impl::waterOutletPort() const {
  return openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::CondenserWaterOutletNodeName;
}

bool CoilWaterHeatingAirToWaterHeatPump_Impl::addToNode(Node& node) {
  (void)node;
  return false;
}

bool CoilWaterHeatingAirToWaterHeatPump_Impl::addToSplitter(Splitter& splitter) {
  (void)splitter;
  return false;
}

double CoilWaterHeatingAirToWaterHeatPump_Impl::ratedHeatingCapacity() const {
  const auto value = getDouble(openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::RatedHeatingCapacity, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilWaterHeatingAirToWaterHeatPump_Impl::setRatedHeatingCapacity(double ratedHeatingCapacity) {
  return setDouble(openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::RatedHeatingCapacity, ratedHeatingCapacity);
}

double CoilWaterHeatingAirToWaterHeatPump_Impl::ratedCOP() const {
  const auto value = getDouble(openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::RatedCOP, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilWaterHeatingAirToWaterHeatPump_Impl::setRatedCOP(double ratedCOP) {
  return setDouble(openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::RatedCOP, ratedCOP);
}

double CoilWaterHeatingAirToWaterHeatPump_Impl::ratedSensibleHeatRatio() const {
  const auto value = getDouble(openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::RatedSensibleHeatRatio, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilWaterHeatingAirToWaterHeatPump_Impl::setRatedSensibleHeatRatio(double ratedSensibleHeatRatio) {
  return setDouble(openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::RatedSensibleHeatRatio, ratedSensibleHeatRatio);
}

double CoilWaterHeatingAirToWaterHeatPump_Impl::ratedEvaporatorInletAirDryBulbTemperature() const {
  const auto value = getDouble(openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::RatedEvaporatorInletAirDryBulbTemperature, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilWaterHeatingAirToWaterHeatPump_Impl::setRatedEvaporatorInletAirDryBulbTemperature(double ratedEvaporatorInletAirDryBulbTemperature) {
  return setDouble(openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::RatedEvaporatorInletAirDryBulbTemperature,
                   ratedEvaporatorInletAirDryBulbTemperature);
}

double CoilWaterHeatingAirToWaterHeatPump_Impl::ratedEvaporatorInletAirWetBulbTemperature() const {
  const auto value = getDouble(openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::RatedEvaporatorInletAirWetBulbTemperature, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilWaterHeatingAirToWaterHeatPump_Impl::setRatedEvaporatorInletAirWetBulbTemperature(double ratedEvaporatorInletAirWetBulbTemperature) {
  return setDouble(openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::RatedEvaporatorInletAirWetBulbTemperature,
                   ratedEvaporatorInletAirWetBulbTemperature);
}

double CoilWaterHeatingAirToWaterHeatPump_Impl::ratedCondenserInletWaterTemperature() const {
  const auto value = getDouble(openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::RatedCondenserInletWaterTemperature, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilWaterHeatingAirToWaterHeatPump_Impl::setRatedCondenserInletWaterTemperature(double ratedCondenserInletWaterTemperature) {
  return setDouble(openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::RatedCondenserInletWaterTemperature,
                   ratedCondenserInletWaterTemperature);
}

boost::optional<double> CoilWaterHeatingAirToWaterHeatPump_Impl::ratedEvaporatorAirFlowRate() const {
  return getDouble(openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::RatedEvaporatorAirFlowRate, true);
}

bool CoilWaterHeatingAirToWaterHeatPump_Impl::isRatedEvaporatorAirFlowRateAutosized() const {
  if (const auto value = getString(openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::RatedEvaporatorAirFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool CoilWaterHeatingAirToWaterHeatPump_Impl::setRatedEvaporatorAirFlowRate(double ratedEvaporatorAirFlowRate) {
  return setDouble(openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::RatedEvaporatorAirFlowRate, ratedEvaporatorAirFlowRate);
}

void CoilWaterHeatingAirToWaterHeatPump_Impl::autosizeRatedEvaporatorAirFlowRate() {
  OS_ASSERT(setString(openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::RatedEvaporatorAirFlowRate, "autosize"));
}

boost::optional<double> CoilWaterHeatingAirToWaterHeatPump_Impl::ratedCondenserWaterFlowRate() const {
  return getDouble(openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::RatedCondenserWaterFlowRate, true);
}

bool CoilWaterHeatingAirToWaterHeatPump_Impl::isRatedCondenserWaterFlowRateAutosized() const {
  if (const auto value = getString(openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::RatedCondenserWaterFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool CoilWaterHeatingAirToWaterHeatPump_Impl::setRatedCondenserWaterFlowRate(double ratedCondenserWaterFlowRate) {
  return setDouble(openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::RatedCondenserWaterFlowRate, ratedCondenserWaterFlowRate);
}

void CoilWaterHeatingAirToWaterHeatPump_Impl::autosizeRatedCondenserWaterFlowRate() {
  OS_ASSERT(setString(openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::RatedCondenserWaterFlowRate, "autosize"));
}

bool CoilWaterHeatingAirToWaterHeatPump_Impl::evaporatorFanPowerIncludedinRatedCOP() const {
  const auto value = getString(openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::EvaporatorFanPowerIncludedinRatedCOP, true);
  OS_ASSERT(value);
  return openstudio::istringEqual(*value, "Yes");
}

bool CoilWaterHeatingAirToWaterHeatPump_Impl::setEvaporatorFanPowerIncludedinRatedCOP(bool evaporatorFanPowerIncludedinRatedCOP) {
  const bool result = setString(openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::EvaporatorFanPowerIncludedinRatedCOP,
                                evaporatorFanPowerIncludedinRatedCOP ? "Yes" : "No");
  OS_ASSERT(result);
  return result;
}

bool CoilWaterHeatingAirToWaterHeatPump_Impl::condenserPumpPowerIncludedinRatedCOP() const {
  const auto value = getString(openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::CondenserPumpPowerIncludedinRatedCOP, true);
  OS_ASSERT(value);
  return openstudio::istringEqual(*value, "Yes");
}

bool CoilWaterHeatingAirToWaterHeatPump_Impl::setCondenserPumpPowerIncludedinRatedCOP(bool condenserPumpPowerIncludedinRatedCOP) {
  const bool result = setString(openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::CondenserPumpPowerIncludedinRatedCOP,
                                condenserPumpPowerIncludedinRatedCOP ? "Yes" : "No");
  OS_ASSERT(result);
  return result;
}

bool CoilWaterHeatingAirToWaterHeatPump_Impl::condenserPumpHeatIncludedinRatedHeatingCapacityandRatedCOP() const {
  const auto value =
    getString(openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::CondenserPumpHeatIncludedinRatedHeatingCapacityandRatedCOP, true);
  OS_ASSERT(value);
  return openstudio::istringEqual(*value, "Yes");
}

bool CoilWaterHeatingAirToWaterHeatPump_Impl::setCondenserPumpHeatIncludedinRatedHeatingCapacityandRatedCOP(
  bool condenserPumpHeatIncludedinRatedHeatingCapacityandRatedCOP) {
  const bool result = setString(
    openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::CondenserPumpHeatIncludedinRatedHeatingCapacityandRatedCOP,
    condenserPumpHeatIncludedinRatedHeatingCapacityandRatedCOP ? "Yes" : "No");
  OS_ASSERT(result);
  return result;
}

double CoilWaterHeatingAirToWaterHeatPump_Impl::condenserWaterPumpPower() const {
  const auto value = getDouble(openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::CondenserWaterPumpPower, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilWaterHeatingAirToWaterHeatPump_Impl::setCondenserWaterPumpPower(double condenserWaterPumpPower) {
  return setDouble(openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::CondenserWaterPumpPower, condenserWaterPumpPower);
}

double CoilWaterHeatingAirToWaterHeatPump_Impl::fractionofCondenserPumpHeattoWater() const {
  const auto value = getDouble(openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::FractionofCondenserPumpHeattoWater, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilWaterHeatingAirToWaterHeatPump_Impl::setFractionofCondenserPumpHeattoWater(double fractionofCondenserPumpHeattoWater) {
  return setDouble(openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::FractionofCondenserPumpHeattoWater,
                   fractionofCondenserPumpHeattoWater);
}

double CoilWaterHeatingAirToWaterHeatPump_Impl::crankcaseHeaterCapacity() const {
  const auto value = getDouble(openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::CrankcaseHeaterCapacity, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilWaterHeatingAirToWaterHeatPump_Impl::setCrankcaseHeaterCapacity(double crankcaseHeaterCapacity) {
  return setDouble(openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::CrankcaseHeaterCapacity, crankcaseHeaterCapacity);
}

double CoilWaterHeatingAirToWaterHeatPump_Impl::maximumAmbientTemperatureforCrankcaseHeaterOperation() const {
  const auto value =
    getDouble(openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::MaximumAmbientTemperatureforCrankcaseHeaterOperation, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilWaterHeatingAirToWaterHeatPump_Impl::setMaximumAmbientTemperatureforCrankcaseHeaterOperation(
  double maximumAmbientTemperatureforCrankcaseHeaterOperation) {
  return setDouble(openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::MaximumAmbientTemperatureforCrankcaseHeaterOperation,
                   maximumAmbientTemperatureforCrankcaseHeaterOperation);
}

std::string CoilWaterHeatingAirToWaterHeatPump_Impl::evaporatorAirTemperatureTypeforCurveObjects() const {
  const auto value =
    getString(openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::EvaporatorAirTemperatureTypeforCurveObjects, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilWaterHeatingAirToWaterHeatPump_Impl::setEvaporatorAirTemperatureTypeforCurveObjects(
  const std::string& evaporatorAirTemperatureTypeforCurveObjects) {
  return setString(openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::EvaporatorAirTemperatureTypeforCurveObjects,
                   evaporatorAirTemperatureTypeforCurveObjects);
}

std::vector<std::string> CoilWaterHeatingAirToWaterHeatPump_Impl::evaporatorAirTemperatureTypeforCurveObjectsValues() const {
  return openstudio::epmodel::CoilWaterHeatingAirToWaterHeatPump::evaporatorAirTemperatureTypeforCurveObjectsValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
