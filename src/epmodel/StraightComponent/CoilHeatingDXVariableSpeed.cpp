/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/CoilHeatingDXVariableSpeed.hpp"
#include "StraightComponent/CoilHeatingDXVariableSpeed_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/Coil_Heating_DX_VariableSpeed_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

CoilHeatingDXVariableSpeed::CoilHeatingDXVariableSpeed(const Model& model)
  : StraightComponent(CoilHeatingDXVariableSpeed::iddObjectType(), model) {
  // Preserve model-constructor scalar defaults while excluding relationship and speed-data fields.
  OS_ASSERT(setNominalSpeedLevel(1));
  autosizeRatedHeatingCapacityAtSelectedNominalSpeedLevel();
  autosizeRatedAirFlowRateAtSelectedNominalSpeedLevel();
  OS_ASSERT(setMinimumOutdoorDryBulbTemperatureforCompressorOperation(-5.0));
  OS_ASSERT(setMaximumOutdoorDryBulbTemperatureforDefrostOperation(5.0));
  OS_ASSERT(setCrankcaseHeaterCapacity(200.0));
  OS_ASSERT(setMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation(10.0));
  OS_ASSERT(setDefrostStrategy("Resistive"));
  OS_ASSERT(setDefrostControl("OnDemand"));
  OS_ASSERT(setDefrostTimePeriodFraction(0.166667));
  autosizeResistiveDefrostHeaterCapacity();
}

CoilHeatingDXVariableSpeed::CoilHeatingDXVariableSpeed(std::shared_ptr<detail::CoilHeatingDXVariableSpeed_Impl> impl)
  : StraightComponent(std::move(impl)) {}

IddObjectType CoilHeatingDXVariableSpeed::iddObjectType() {
  return IddObjectType::Coil_Heating_DX_VariableSpeed;
}

std::vector<std::string> CoilHeatingDXVariableSpeed::defrostStrategyValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::Coil_Heating_DX_VariableSpeedFields::DefrostStrategy);
}

std::vector<std::string> CoilHeatingDXVariableSpeed::defrostControlValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::Coil_Heating_DX_VariableSpeedFields::DefrostControl);
}

int CoilHeatingDXVariableSpeed::nominalSpeedLevel() const {
  return getImpl<detail::CoilHeatingDXVariableSpeed_Impl>()->nominalSpeedLevel();
}

bool CoilHeatingDXVariableSpeed::setNominalSpeedLevel(int nominalSpeedLevel) {
  return getImpl<detail::CoilHeatingDXVariableSpeed_Impl>()->setNominalSpeedLevel(nominalSpeedLevel);
}

boost::optional<double> CoilHeatingDXVariableSpeed::ratedHeatingCapacityAtSelectedNominalSpeedLevel() const {
  return getImpl<detail::CoilHeatingDXVariableSpeed_Impl>()->ratedHeatingCapacityAtSelectedNominalSpeedLevel();
}

bool CoilHeatingDXVariableSpeed::isRatedHeatingCapacityAtSelectedNominalSpeedLevelAutosized() const {
  return getImpl<detail::CoilHeatingDXVariableSpeed_Impl>()->isRatedHeatingCapacityAtSelectedNominalSpeedLevelAutosized();
}

bool CoilHeatingDXVariableSpeed::setRatedHeatingCapacityAtSelectedNominalSpeedLevel(double ratedHeatingCapacityAtSelectedNominalSpeedLevel) {
  return getImpl<detail::CoilHeatingDXVariableSpeed_Impl>()->setRatedHeatingCapacityAtSelectedNominalSpeedLevel(
    ratedHeatingCapacityAtSelectedNominalSpeedLevel);
}

void CoilHeatingDXVariableSpeed::autosizeRatedHeatingCapacityAtSelectedNominalSpeedLevel() {
  getImpl<detail::CoilHeatingDXVariableSpeed_Impl>()->autosizeRatedHeatingCapacityAtSelectedNominalSpeedLevel();
}

boost::optional<double> CoilHeatingDXVariableSpeed::ratedAirFlowRateAtSelectedNominalSpeedLevel() const {
  return getImpl<detail::CoilHeatingDXVariableSpeed_Impl>()->ratedAirFlowRateAtSelectedNominalSpeedLevel();
}

bool CoilHeatingDXVariableSpeed::isRatedAirFlowRateAtSelectedNominalSpeedLevelAutosized() const {
  return getImpl<detail::CoilHeatingDXVariableSpeed_Impl>()->isRatedAirFlowRateAtSelectedNominalSpeedLevelAutosized();
}

bool CoilHeatingDXVariableSpeed::setRatedAirFlowRateAtSelectedNominalSpeedLevel(double ratedAirFlowRateAtSelectedNominalSpeedLevel) {
  return getImpl<detail::CoilHeatingDXVariableSpeed_Impl>()->setRatedAirFlowRateAtSelectedNominalSpeedLevel(
    ratedAirFlowRateAtSelectedNominalSpeedLevel);
}

void CoilHeatingDXVariableSpeed::autosizeRatedAirFlowRateAtSelectedNominalSpeedLevel() {
  getImpl<detail::CoilHeatingDXVariableSpeed_Impl>()->autosizeRatedAirFlowRateAtSelectedNominalSpeedLevel();
}

double CoilHeatingDXVariableSpeed::minimumOutdoorDryBulbTemperatureforCompressorOperation() const {
  return getImpl<detail::CoilHeatingDXVariableSpeed_Impl>()->minimumOutdoorDryBulbTemperatureforCompressorOperation();
}

bool CoilHeatingDXVariableSpeed::setMinimumOutdoorDryBulbTemperatureforCompressorOperation(
  double minimumOutdoorDryBulbTemperatureforCompressorOperation) {
  return getImpl<detail::CoilHeatingDXVariableSpeed_Impl>()->setMinimumOutdoorDryBulbTemperatureforCompressorOperation(
    minimumOutdoorDryBulbTemperatureforCompressorOperation);
}

boost::optional<double> CoilHeatingDXVariableSpeed::outdoorDryBulbTemperaturetoTurnOnCompressor() const {
  return getImpl<detail::CoilHeatingDXVariableSpeed_Impl>()->outdoorDryBulbTemperaturetoTurnOnCompressor();
}

bool CoilHeatingDXVariableSpeed::setOutdoorDryBulbTemperaturetoTurnOnCompressor(double outdoorDryBulbTemperaturetoTurnOnCompressor) {
  return getImpl<detail::CoilHeatingDXVariableSpeed_Impl>()->setOutdoorDryBulbTemperaturetoTurnOnCompressor(
    outdoorDryBulbTemperaturetoTurnOnCompressor);
}

void CoilHeatingDXVariableSpeed::resetOutdoorDryBulbTemperaturetoTurnOnCompressor() {
  getImpl<detail::CoilHeatingDXVariableSpeed_Impl>()->resetOutdoorDryBulbTemperaturetoTurnOnCompressor();
}

double CoilHeatingDXVariableSpeed::maximumOutdoorDryBulbTemperatureforDefrostOperation() const {
  return getImpl<detail::CoilHeatingDXVariableSpeed_Impl>()->maximumOutdoorDryBulbTemperatureforDefrostOperation();
}

bool CoilHeatingDXVariableSpeed::setMaximumOutdoorDryBulbTemperatureforDefrostOperation(double maximumOutdoorDryBulbTemperatureforDefrostOperation) {
  return getImpl<detail::CoilHeatingDXVariableSpeed_Impl>()->setMaximumOutdoorDryBulbTemperatureforDefrostOperation(
    maximumOutdoorDryBulbTemperatureforDefrostOperation);
}

double CoilHeatingDXVariableSpeed::crankcaseHeaterCapacity() const {
  return getImpl<detail::CoilHeatingDXVariableSpeed_Impl>()->crankcaseHeaterCapacity();
}

bool CoilHeatingDXVariableSpeed::setCrankcaseHeaterCapacity(double crankcaseHeaterCapacity) {
  return getImpl<detail::CoilHeatingDXVariableSpeed_Impl>()->setCrankcaseHeaterCapacity(crankcaseHeaterCapacity);
}

double CoilHeatingDXVariableSpeed::maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation() const {
  return getImpl<detail::CoilHeatingDXVariableSpeed_Impl>()->maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation();
}

bool CoilHeatingDXVariableSpeed::setMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation(
  double maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation) {
  return getImpl<detail::CoilHeatingDXVariableSpeed_Impl>()->setMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation(
    maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation);
}

std::string CoilHeatingDXVariableSpeed::defrostStrategy() const {
  return getImpl<detail::CoilHeatingDXVariableSpeed_Impl>()->defrostStrategy();
}

bool CoilHeatingDXVariableSpeed::setDefrostStrategy(const std::string& defrostStrategy) {
  return getImpl<detail::CoilHeatingDXVariableSpeed_Impl>()->setDefrostStrategy(defrostStrategy);
}

std::string CoilHeatingDXVariableSpeed::defrostControl() const {
  return getImpl<detail::CoilHeatingDXVariableSpeed_Impl>()->defrostControl();
}

bool CoilHeatingDXVariableSpeed::setDefrostControl(const std::string& defrostControl) {
  return getImpl<detail::CoilHeatingDXVariableSpeed_Impl>()->setDefrostControl(defrostControl);
}

double CoilHeatingDXVariableSpeed::defrostTimePeriodFraction() const {
  return getImpl<detail::CoilHeatingDXVariableSpeed_Impl>()->defrostTimePeriodFraction();
}

bool CoilHeatingDXVariableSpeed::setDefrostTimePeriodFraction(double defrostTimePeriodFraction) {
  return getImpl<detail::CoilHeatingDXVariableSpeed_Impl>()->setDefrostTimePeriodFraction(defrostTimePeriodFraction);
}

boost::optional<double> CoilHeatingDXVariableSpeed::resistiveDefrostHeaterCapacity() const {
  return getImpl<detail::CoilHeatingDXVariableSpeed_Impl>()->resistiveDefrostHeaterCapacity();
}

bool CoilHeatingDXVariableSpeed::isResistiveDefrostHeaterCapacityAutosized() const {
  return getImpl<detail::CoilHeatingDXVariableSpeed_Impl>()->isResistiveDefrostHeaterCapacityAutosized();
}

bool CoilHeatingDXVariableSpeed::setResistiveDefrostHeaterCapacity(double resistiveDefrostHeaterCapacity) {
  return getImpl<detail::CoilHeatingDXVariableSpeed_Impl>()->setResistiveDefrostHeaterCapacity(resistiveDefrostHeaterCapacity);
}

void CoilHeatingDXVariableSpeed::autosizeResistiveDefrostHeaterCapacity() {
  getImpl<detail::CoilHeatingDXVariableSpeed_Impl>()->autosizeResistiveDefrostHeaterCapacity();
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

unsigned CoilHeatingDXVariableSpeed_Impl::inletPort() const {
  return openstudio::Coil_Heating_DX_VariableSpeedFields::IndoorAirInletNodeName;
}

unsigned CoilHeatingDXVariableSpeed_Impl::outletPort() const {
  return openstudio::Coil_Heating_DX_VariableSpeedFields::IndoorAirOutletNodeName;
}

int CoilHeatingDXVariableSpeed_Impl::nominalSpeedLevel() const {
  const auto value = getInt(openstudio::Coil_Heating_DX_VariableSpeedFields::NominalSpeedLevel, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilHeatingDXVariableSpeed_Impl::setNominalSpeedLevel(int nominalSpeedLevel) {
  const bool result = setInt(openstudio::Coil_Heating_DX_VariableSpeedFields::NominalSpeedLevel, nominalSpeedLevel);
  OS_ASSERT(result);
  return result;
}

boost::optional<double> CoilHeatingDXVariableSpeed_Impl::ratedHeatingCapacityAtSelectedNominalSpeedLevel() const {
  return getDouble(openstudio::Coil_Heating_DX_VariableSpeedFields::RatedHeatingCapacityAtSelectedNominalSpeedLevel, true);
}

bool CoilHeatingDXVariableSpeed_Impl::isRatedHeatingCapacityAtSelectedNominalSpeedLevelAutosized() const {
  return isAutosized(*this, openstudio::Coil_Heating_DX_VariableSpeedFields::RatedHeatingCapacityAtSelectedNominalSpeedLevel);
}

bool CoilHeatingDXVariableSpeed_Impl::setRatedHeatingCapacityAtSelectedNominalSpeedLevel(double ratedHeatingCapacityAtSelectedNominalSpeedLevel) {
  const bool result = setDouble(openstudio::Coil_Heating_DX_VariableSpeedFields::RatedHeatingCapacityAtSelectedNominalSpeedLevel,
                                ratedHeatingCapacityAtSelectedNominalSpeedLevel);
  OS_ASSERT(result);
  return result;
}

void CoilHeatingDXVariableSpeed_Impl::autosizeRatedHeatingCapacityAtSelectedNominalSpeedLevel() {
  const bool result = setString(openstudio::Coil_Heating_DX_VariableSpeedFields::RatedHeatingCapacityAtSelectedNominalSpeedLevel, "autosize");
  OS_ASSERT(result);
}

boost::optional<double> CoilHeatingDXVariableSpeed_Impl::ratedAirFlowRateAtSelectedNominalSpeedLevel() const {
  return getDouble(openstudio::Coil_Heating_DX_VariableSpeedFields::RatedAirFlowRateAtSelectedNominalSpeedLevel, true);
}

bool CoilHeatingDXVariableSpeed_Impl::isRatedAirFlowRateAtSelectedNominalSpeedLevelAutosized() const {
  return isAutosized(*this, openstudio::Coil_Heating_DX_VariableSpeedFields::RatedAirFlowRateAtSelectedNominalSpeedLevel);
}

bool CoilHeatingDXVariableSpeed_Impl::setRatedAirFlowRateAtSelectedNominalSpeedLevel(double ratedAirFlowRateAtSelectedNominalSpeedLevel) {
  const bool result = setDouble(openstudio::Coil_Heating_DX_VariableSpeedFields::RatedAirFlowRateAtSelectedNominalSpeedLevel,
                                ratedAirFlowRateAtSelectedNominalSpeedLevel);
  OS_ASSERT(result);
  return result;
}

void CoilHeatingDXVariableSpeed_Impl::autosizeRatedAirFlowRateAtSelectedNominalSpeedLevel() {
  const bool result = setString(openstudio::Coil_Heating_DX_VariableSpeedFields::RatedAirFlowRateAtSelectedNominalSpeedLevel, "autosize");
  OS_ASSERT(result);
}

double CoilHeatingDXVariableSpeed_Impl::minimumOutdoorDryBulbTemperatureforCompressorOperation() const {
  const auto value = getDouble(openstudio::Coil_Heating_DX_VariableSpeedFields::MinimumOutdoorDryBulbTemperatureforCompressorOperation, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilHeatingDXVariableSpeed_Impl::setMinimumOutdoorDryBulbTemperatureforCompressorOperation(
  double minimumOutdoorDryBulbTemperatureforCompressorOperation) {
  const bool result = setDouble(openstudio::Coil_Heating_DX_VariableSpeedFields::MinimumOutdoorDryBulbTemperatureforCompressorOperation,
                                minimumOutdoorDryBulbTemperatureforCompressorOperation);
  OS_ASSERT(result);
  return result;
}

boost::optional<double> CoilHeatingDXVariableSpeed_Impl::outdoorDryBulbTemperaturetoTurnOnCompressor() const {
  return getDouble(openstudio::Coil_Heating_DX_VariableSpeedFields::OutdoorDryBulbTemperaturetoTurnOnCompressor, true);
}

bool CoilHeatingDXVariableSpeed_Impl::setOutdoorDryBulbTemperaturetoTurnOnCompressor(double outdoorDryBulbTemperaturetoTurnOnCompressor) {
  const bool result = setDouble(openstudio::Coil_Heating_DX_VariableSpeedFields::OutdoorDryBulbTemperaturetoTurnOnCompressor,
                                outdoorDryBulbTemperaturetoTurnOnCompressor);
  OS_ASSERT(result);
  return result;
}

void CoilHeatingDXVariableSpeed_Impl::resetOutdoorDryBulbTemperaturetoTurnOnCompressor() {
  const bool result = setString(openstudio::Coil_Heating_DX_VariableSpeedFields::OutdoorDryBulbTemperaturetoTurnOnCompressor, "");
  OS_ASSERT(result);
}

double CoilHeatingDXVariableSpeed_Impl::maximumOutdoorDryBulbTemperatureforDefrostOperation() const {
  const auto value = getDouble(openstudio::Coil_Heating_DX_VariableSpeedFields::MaximumOutdoorDryBulbTemperatureforDefrostOperation, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilHeatingDXVariableSpeed_Impl::setMaximumOutdoorDryBulbTemperatureforDefrostOperation(
  double maximumOutdoorDryBulbTemperatureforDefrostOperation) {
  return setDouble(openstudio::Coil_Heating_DX_VariableSpeedFields::MaximumOutdoorDryBulbTemperatureforDefrostOperation,
                   maximumOutdoorDryBulbTemperatureforDefrostOperation);
}

double CoilHeatingDXVariableSpeed_Impl::crankcaseHeaterCapacity() const {
  const auto value = getDouble(openstudio::Coil_Heating_DX_VariableSpeedFields::CrankcaseHeaterCapacity, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilHeatingDXVariableSpeed_Impl::setCrankcaseHeaterCapacity(double crankcaseHeaterCapacity) {
  return setDouble(openstudio::Coil_Heating_DX_VariableSpeedFields::CrankcaseHeaterCapacity, crankcaseHeaterCapacity);
}

double CoilHeatingDXVariableSpeed_Impl::maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation() const {
  const auto value =
    getDouble(openstudio::Coil_Heating_DX_VariableSpeedFields::MaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilHeatingDXVariableSpeed_Impl::setMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation(
  double maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation) {
  return setDouble(openstudio::Coil_Heating_DX_VariableSpeedFields::MaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation,
                   maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation);
}

std::vector<std::string> CoilHeatingDXVariableSpeed_Impl::defrostStrategyValues() const {
  return CoilHeatingDXVariableSpeed::defrostStrategyValues();
}

std::string CoilHeatingDXVariableSpeed_Impl::defrostStrategy() const {
  const auto value = getString(openstudio::Coil_Heating_DX_VariableSpeedFields::DefrostStrategy, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilHeatingDXVariableSpeed_Impl::setDefrostStrategy(const std::string& defrostStrategy) {
  return setString(openstudio::Coil_Heating_DX_VariableSpeedFields::DefrostStrategy, defrostStrategy);
}

std::vector<std::string> CoilHeatingDXVariableSpeed_Impl::defrostControlValues() const {
  return CoilHeatingDXVariableSpeed::defrostControlValues();
}

std::string CoilHeatingDXVariableSpeed_Impl::defrostControl() const {
  const auto value = getString(openstudio::Coil_Heating_DX_VariableSpeedFields::DefrostControl, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilHeatingDXVariableSpeed_Impl::setDefrostControl(const std::string& defrostControl) {
  return setString(openstudio::Coil_Heating_DX_VariableSpeedFields::DefrostControl, defrostControl);
}

double CoilHeatingDXVariableSpeed_Impl::defrostTimePeriodFraction() const {
  const auto value = getDouble(openstudio::Coil_Heating_DX_VariableSpeedFields::DefrostTimePeriodFraction, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilHeatingDXVariableSpeed_Impl::setDefrostTimePeriodFraction(double defrostTimePeriodFraction) {
  return setDouble(openstudio::Coil_Heating_DX_VariableSpeedFields::DefrostTimePeriodFraction, defrostTimePeriodFraction);
}

boost::optional<double> CoilHeatingDXVariableSpeed_Impl::resistiveDefrostHeaterCapacity() const {
  return getDouble(openstudio::Coil_Heating_DX_VariableSpeedFields::ResistiveDefrostHeaterCapacity, true);
}

bool CoilHeatingDXVariableSpeed_Impl::isResistiveDefrostHeaterCapacityAutosized() const {
  return isAutosized(*this, openstudio::Coil_Heating_DX_VariableSpeedFields::ResistiveDefrostHeaterCapacity);
}

bool CoilHeatingDXVariableSpeed_Impl::setResistiveDefrostHeaterCapacity(double resistiveDefrostHeaterCapacity) {
  return setDouble(openstudio::Coil_Heating_DX_VariableSpeedFields::ResistiveDefrostHeaterCapacity, resistiveDefrostHeaterCapacity);
}

void CoilHeatingDXVariableSpeed_Impl::autosizeResistiveDefrostHeaterCapacity() {
  const bool result = setString(openstudio::Coil_Heating_DX_VariableSpeedFields::ResistiveDefrostHeaterCapacity, "autosize");
  OS_ASSERT(result);
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
