/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/CoolingTowerVariableSpeed.hpp"
#include "StraightComponent/CoolingTowerVariableSpeed_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/CoolingTower_VariableSpeed_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>

namespace openstudio {
namespace epmodel {

CoolingTowerVariableSpeed::CoolingTowerVariableSpeed(const Model& model) : StraightComponent(CoolingTowerVariableSpeed::iddObjectType(), model) {}

CoolingTowerVariableSpeed::CoolingTowerVariableSpeed(std::shared_ptr<detail::CoolingTowerVariableSpeed_Impl> impl) : StraightComponent(std::move(impl)) {}

IddObjectType CoolingTowerVariableSpeed::iddObjectType() {
  return IddObjectType::CoolingTower_VariableSpeed;
}

std::vector<std::string> CoolingTowerVariableSpeed::modelTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::CoolingTower_VariableSpeedFields::ModelType);
}

std::vector<std::string> CoolingTowerVariableSpeed::evaporationLossModeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::CoolingTower_VariableSpeedFields::EvaporationLossMode);
}

std::vector<std::string> CoolingTowerVariableSpeed::blowdownCalculationModeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::CoolingTower_VariableSpeedFields::BlowdownCalculationMode);
}

std::vector<std::string> CoolingTowerVariableSpeed::cellControlValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::CoolingTower_VariableSpeedFields::CellControl);
}

boost::optional<std::string> CoolingTowerVariableSpeed::modelType() const {
  return getImpl<detail::CoolingTowerVariableSpeed_Impl>()->modelType();
}

bool CoolingTowerVariableSpeed::setModelType(const std::string& modelType) {
  return getImpl<detail::CoolingTowerVariableSpeed_Impl>()->setModelType(modelType);
}

void CoolingTowerVariableSpeed::resetModelType() {
  getImpl<detail::CoolingTowerVariableSpeed_Impl>()->resetModelType();
}

boost::optional<double> CoolingTowerVariableSpeed::designInletAirWetBulbTemperature() const {
  return getImpl<detail::CoolingTowerVariableSpeed_Impl>()->designInletAirWetBulbTemperature();
}

bool CoolingTowerVariableSpeed::setDesignInletAirWetBulbTemperature(double designInletAirWetBulbTemperature) {
  return getImpl<detail::CoolingTowerVariableSpeed_Impl>()->setDesignInletAirWetBulbTemperature(designInletAirWetBulbTemperature);
}

void CoolingTowerVariableSpeed::resetDesignInletAirWetBulbTemperature() {
  getImpl<detail::CoolingTowerVariableSpeed_Impl>()->resetDesignInletAirWetBulbTemperature();
}

boost::optional<double> CoolingTowerVariableSpeed::designApproachTemperature() const {
  return getImpl<detail::CoolingTowerVariableSpeed_Impl>()->designApproachTemperature();
}

bool CoolingTowerVariableSpeed::setDesignApproachTemperature(double designApproachTemperature) {
  return getImpl<detail::CoolingTowerVariableSpeed_Impl>()->setDesignApproachTemperature(designApproachTemperature);
}

void CoolingTowerVariableSpeed::resetDesignApproachTemperature() {
  getImpl<detail::CoolingTowerVariableSpeed_Impl>()->resetDesignApproachTemperature();
}

boost::optional<double> CoolingTowerVariableSpeed::designRangeTemperature() const {
  return getImpl<detail::CoolingTowerVariableSpeed_Impl>()->designRangeTemperature();
}

bool CoolingTowerVariableSpeed::setDesignRangeTemperature(double designRangeTemperature) {
  return getImpl<detail::CoolingTowerVariableSpeed_Impl>()->setDesignRangeTemperature(designRangeTemperature);
}

void CoolingTowerVariableSpeed::resetDesignRangeTemperature() {
  getImpl<detail::CoolingTowerVariableSpeed_Impl>()->resetDesignRangeTemperature();
}

boost::optional<double> CoolingTowerVariableSpeed::designWaterFlowRate() const {
  return getImpl<detail::CoolingTowerVariableSpeed_Impl>()->designWaterFlowRate();
}

bool CoolingTowerVariableSpeed::isDesignWaterFlowRateAutosized() const {
  return getImpl<detail::CoolingTowerVariableSpeed_Impl>()->isDesignWaterFlowRateAutosized();
}

bool CoolingTowerVariableSpeed::setDesignWaterFlowRate(double designWaterFlowRate) {
  return getImpl<detail::CoolingTowerVariableSpeed_Impl>()->setDesignWaterFlowRate(designWaterFlowRate);
}

void CoolingTowerVariableSpeed::autosizeDesignWaterFlowRate() {
  getImpl<detail::CoolingTowerVariableSpeed_Impl>()->autosizeDesignWaterFlowRate();
}

boost::optional<double> CoolingTowerVariableSpeed::designAirFlowRate() const {
  return getImpl<detail::CoolingTowerVariableSpeed_Impl>()->designAirFlowRate();
}

bool CoolingTowerVariableSpeed::isDesignAirFlowRateAutosized() const {
  return getImpl<detail::CoolingTowerVariableSpeed_Impl>()->isDesignAirFlowRateAutosized();
}

bool CoolingTowerVariableSpeed::setDesignAirFlowRate(double designAirFlowRate) {
  return getImpl<detail::CoolingTowerVariableSpeed_Impl>()->setDesignAirFlowRate(designAirFlowRate);
}

void CoolingTowerVariableSpeed::autosizeDesignAirFlowRate() {
  getImpl<detail::CoolingTowerVariableSpeed_Impl>()->autosizeDesignAirFlowRate();
}

boost::optional<double> CoolingTowerVariableSpeed::designFanPower() const {
  return getImpl<detail::CoolingTowerVariableSpeed_Impl>()->designFanPower();
}

bool CoolingTowerVariableSpeed::isDesignFanPowerAutosized() const {
  return getImpl<detail::CoolingTowerVariableSpeed_Impl>()->isDesignFanPowerAutosized();
}

bool CoolingTowerVariableSpeed::setDesignFanPower(double designFanPower) {
  return getImpl<detail::CoolingTowerVariableSpeed_Impl>()->setDesignFanPower(designFanPower);
}

void CoolingTowerVariableSpeed::autosizeDesignFanPower() {
  getImpl<detail::CoolingTowerVariableSpeed_Impl>()->autosizeDesignFanPower();
}

boost::optional<double> CoolingTowerVariableSpeed::minimumAirFlowRateRatio() const {
  return getImpl<detail::CoolingTowerVariableSpeed_Impl>()->minimumAirFlowRateRatio();
}

bool CoolingTowerVariableSpeed::setMinimumAirFlowRateRatio(double minimumAirFlowRateRatio) {
  return getImpl<detail::CoolingTowerVariableSpeed_Impl>()->setMinimumAirFlowRateRatio(minimumAirFlowRateRatio);
}

void CoolingTowerVariableSpeed::resetMinimumAirFlowRateRatio() {
  getImpl<detail::CoolingTowerVariableSpeed_Impl>()->resetMinimumAirFlowRateRatio();
}

boost::optional<double> CoolingTowerVariableSpeed::fractionofTowerCapacityinFreeConvectionRegime() const {
  return getImpl<detail::CoolingTowerVariableSpeed_Impl>()->fractionofTowerCapacityinFreeConvectionRegime();
}

bool CoolingTowerVariableSpeed::setFractionofTowerCapacityinFreeConvectionRegime(double fractionofTowerCapacityinFreeConvectionRegime) {
  return getImpl<detail::CoolingTowerVariableSpeed_Impl>()->setFractionofTowerCapacityinFreeConvectionRegime(
    fractionofTowerCapacityinFreeConvectionRegime);
}

void CoolingTowerVariableSpeed::resetFractionofTowerCapacityinFreeConvectionRegime() {
  getImpl<detail::CoolingTowerVariableSpeed_Impl>()->resetFractionofTowerCapacityinFreeConvectionRegime();
}

boost::optional<double> CoolingTowerVariableSpeed::basinHeaterCapacity() const {
  return getImpl<detail::CoolingTowerVariableSpeed_Impl>()->basinHeaterCapacity();
}

bool CoolingTowerVariableSpeed::setBasinHeaterCapacity(double basinHeaterCapacity) {
  return getImpl<detail::CoolingTowerVariableSpeed_Impl>()->setBasinHeaterCapacity(basinHeaterCapacity);
}

void CoolingTowerVariableSpeed::resetBasinHeaterCapacity() {
  getImpl<detail::CoolingTowerVariableSpeed_Impl>()->resetBasinHeaterCapacity();
}

boost::optional<double> CoolingTowerVariableSpeed::basinHeaterSetpointTemperature() const {
  return getImpl<detail::CoolingTowerVariableSpeed_Impl>()->basinHeaterSetpointTemperature();
}

bool CoolingTowerVariableSpeed::setBasinHeaterSetpointTemperature(double basinHeaterSetpointTemperature) {
  return getImpl<detail::CoolingTowerVariableSpeed_Impl>()->setBasinHeaterSetpointTemperature(basinHeaterSetpointTemperature);
}

void CoolingTowerVariableSpeed::resetBasinHeaterSetpointTemperature() {
  getImpl<detail::CoolingTowerVariableSpeed_Impl>()->resetBasinHeaterSetpointTemperature();
}

std::string CoolingTowerVariableSpeed::evaporationLossMode() const {
  return getImpl<detail::CoolingTowerVariableSpeed_Impl>()->evaporationLossMode();
}

bool CoolingTowerVariableSpeed::isEvaporationLossModeDefaulted() const {
  return getImpl<detail::CoolingTowerVariableSpeed_Impl>()->isEvaporationLossModeDefaulted();
}

bool CoolingTowerVariableSpeed::setEvaporationLossMode(const std::string& evaporationLossMode) {
  return getImpl<detail::CoolingTowerVariableSpeed_Impl>()->setEvaporationLossMode(evaporationLossMode);
}

void CoolingTowerVariableSpeed::resetEvaporationLossMode() {
  getImpl<detail::CoolingTowerVariableSpeed_Impl>()->resetEvaporationLossMode();
}

double CoolingTowerVariableSpeed::evaporationLossFactor() const {
  return getImpl<detail::CoolingTowerVariableSpeed_Impl>()->evaporationLossFactor();
}

bool CoolingTowerVariableSpeed::isEvaporationLossFactorDefaulted() const {
  return getImpl<detail::CoolingTowerVariableSpeed_Impl>()->isEvaporationLossFactorDefaulted();
}

bool CoolingTowerVariableSpeed::setEvaporationLossFactor(double evaporationLossFactor) {
  return getImpl<detail::CoolingTowerVariableSpeed_Impl>()->setEvaporationLossFactor(evaporationLossFactor);
}

void CoolingTowerVariableSpeed::resetEvaporationLossFactor() {
  getImpl<detail::CoolingTowerVariableSpeed_Impl>()->resetEvaporationLossFactor();
}

boost::optional<double> CoolingTowerVariableSpeed::driftLossPercent() const {
  return getImpl<detail::CoolingTowerVariableSpeed_Impl>()->driftLossPercent();
}

bool CoolingTowerVariableSpeed::setDriftLossPercent(double driftLossPercent) {
  return getImpl<detail::CoolingTowerVariableSpeed_Impl>()->setDriftLossPercent(driftLossPercent);
}

void CoolingTowerVariableSpeed::resetDriftLossPercent() {
  getImpl<detail::CoolingTowerVariableSpeed_Impl>()->resetDriftLossPercent();
}

std::string CoolingTowerVariableSpeed::blowdownCalculationMode() const {
  return getImpl<detail::CoolingTowerVariableSpeed_Impl>()->blowdownCalculationMode();
}

bool CoolingTowerVariableSpeed::isBlowdownCalculationModeDefaulted() const {
  return getImpl<detail::CoolingTowerVariableSpeed_Impl>()->isBlowdownCalculationModeDefaulted();
}

bool CoolingTowerVariableSpeed::setBlowdownCalculationMode(const std::string& blowdownCalculationMode) {
  return getImpl<detail::CoolingTowerVariableSpeed_Impl>()->setBlowdownCalculationMode(blowdownCalculationMode);
}

void CoolingTowerVariableSpeed::resetBlowdownCalculationMode() {
  getImpl<detail::CoolingTowerVariableSpeed_Impl>()->resetBlowdownCalculationMode();
}

boost::optional<double> CoolingTowerVariableSpeed::blowdownConcentrationRatio() const {
  return getImpl<detail::CoolingTowerVariableSpeed_Impl>()->blowdownConcentrationRatio();
}

bool CoolingTowerVariableSpeed::setBlowdownConcentrationRatio(double blowdownConcentrationRatio) {
  return getImpl<detail::CoolingTowerVariableSpeed_Impl>()->setBlowdownConcentrationRatio(blowdownConcentrationRatio);
}

void CoolingTowerVariableSpeed::resetBlowdownConcentrationRatio() {
  getImpl<detail::CoolingTowerVariableSpeed_Impl>()->resetBlowdownConcentrationRatio();
}

boost::optional<int> CoolingTowerVariableSpeed::numberofCells() const {
  return getImpl<detail::CoolingTowerVariableSpeed_Impl>()->numberofCells();
}

bool CoolingTowerVariableSpeed::setNumberofCells(int numberofCells) {
  return getImpl<detail::CoolingTowerVariableSpeed_Impl>()->setNumberofCells(numberofCells);
}

void CoolingTowerVariableSpeed::resetNumberofCells() {
  getImpl<detail::CoolingTowerVariableSpeed_Impl>()->resetNumberofCells();
}

std::string CoolingTowerVariableSpeed::cellControl() const {
  return getImpl<detail::CoolingTowerVariableSpeed_Impl>()->cellControl();
}

bool CoolingTowerVariableSpeed::isCellControlDefaulted() const {
  return getImpl<detail::CoolingTowerVariableSpeed_Impl>()->isCellControlDefaulted();
}

bool CoolingTowerVariableSpeed::setCellControl(const std::string& cellControl) {
  return getImpl<detail::CoolingTowerVariableSpeed_Impl>()->setCellControl(cellControl);
}

void CoolingTowerVariableSpeed::resetCellControl() {
  getImpl<detail::CoolingTowerVariableSpeed_Impl>()->resetCellControl();
}

boost::optional<double> CoolingTowerVariableSpeed::cellMinimumWaterFlowRateFraction() const {
  return getImpl<detail::CoolingTowerVariableSpeed_Impl>()->cellMinimumWaterFlowRateFraction();
}

bool CoolingTowerVariableSpeed::setCellMinimumWaterFlowRateFraction(double cellMinimumWaterFlowRateFraction) {
  return getImpl<detail::CoolingTowerVariableSpeed_Impl>()->setCellMinimumWaterFlowRateFraction(cellMinimumWaterFlowRateFraction);
}

void CoolingTowerVariableSpeed::resetCellMinimumWaterFlowRateFraction() {
  getImpl<detail::CoolingTowerVariableSpeed_Impl>()->resetCellMinimumWaterFlowRateFraction();
}

boost::optional<double> CoolingTowerVariableSpeed::cellMaximumWaterFlowRateFraction() const {
  return getImpl<detail::CoolingTowerVariableSpeed_Impl>()->cellMaximumWaterFlowRateFraction();
}

bool CoolingTowerVariableSpeed::setCellMaximumWaterFlowRateFraction(double cellMaximumWaterFlowRateFraction) {
  return getImpl<detail::CoolingTowerVariableSpeed_Impl>()->setCellMaximumWaterFlowRateFraction(cellMaximumWaterFlowRateFraction);
}

void CoolingTowerVariableSpeed::resetCellMaximumWaterFlowRateFraction() {
  getImpl<detail::CoolingTowerVariableSpeed_Impl>()->resetCellMaximumWaterFlowRateFraction();
}

boost::optional<double> CoolingTowerVariableSpeed::sizingFactor() const {
  return getImpl<detail::CoolingTowerVariableSpeed_Impl>()->sizingFactor();
}

bool CoolingTowerVariableSpeed::setSizingFactor(double sizingFactor) {
  return getImpl<detail::CoolingTowerVariableSpeed_Impl>()->setSizingFactor(sizingFactor);
}

void CoolingTowerVariableSpeed::resetSizingFactor() {
  getImpl<detail::CoolingTowerVariableSpeed_Impl>()->resetSizingFactor();
}

std::string CoolingTowerVariableSpeed::endUseSubcategory() const {
  return getImpl<detail::CoolingTowerVariableSpeed_Impl>()->endUseSubcategory();
}

bool CoolingTowerVariableSpeed::setEndUseSubcategory(const std::string& endUseSubcategory) {
  return getImpl<detail::CoolingTowerVariableSpeed_Impl>()->setEndUseSubcategory(endUseSubcategory);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

unsigned CoolingTowerVariableSpeed_Impl::inletPort() const {
  return openstudio::CoolingTower_VariableSpeedFields::WaterInletNodeName;
}

unsigned CoolingTowerVariableSpeed_Impl::outletPort() const {
  return openstudio::CoolingTower_VariableSpeedFields::WaterOutletNodeName;
}

std::vector<std::string> CoolingTowerVariableSpeed_Impl::modelTypeValues() const {
  return openstudio::epmodel::CoolingTowerVariableSpeed::modelTypeValues();
}

std::vector<std::string> CoolingTowerVariableSpeed_Impl::evaporationLossModeValues() const {
  return openstudio::epmodel::CoolingTowerVariableSpeed::evaporationLossModeValues();
}

std::vector<std::string> CoolingTowerVariableSpeed_Impl::blowdownCalculationModeValues() const {
  return openstudio::epmodel::CoolingTowerVariableSpeed::blowdownCalculationModeValues();
}

std::vector<std::string> CoolingTowerVariableSpeed_Impl::cellControlValues() const {
  return openstudio::epmodel::CoolingTowerVariableSpeed::cellControlValues();
}

boost::optional<std::string> CoolingTowerVariableSpeed_Impl::modelType() const {
  return getString(openstudio::CoolingTower_VariableSpeedFields::ModelType, true);
}

bool CoolingTowerVariableSpeed_Impl::setModelType(const std::string& modelType) {
  return setString(openstudio::CoolingTower_VariableSpeedFields::ModelType, modelType);
}

void CoolingTowerVariableSpeed_Impl::resetModelType() {
  OS_ASSERT(setString(openstudio::CoolingTower_VariableSpeedFields::ModelType, ""));
}

boost::optional<double> CoolingTowerVariableSpeed_Impl::designInletAirWetBulbTemperature() const {
  return getDouble(openstudio::CoolingTower_VariableSpeedFields::DesignInletAirWetBulbTemperature, true);
}

bool CoolingTowerVariableSpeed_Impl::setDesignInletAirWetBulbTemperature(double designInletAirWetBulbTemperature) {
  return setDouble(openstudio::CoolingTower_VariableSpeedFields::DesignInletAirWetBulbTemperature, designInletAirWetBulbTemperature);
}

void CoolingTowerVariableSpeed_Impl::resetDesignInletAirWetBulbTemperature() {
  OS_ASSERT(setString(openstudio::CoolingTower_VariableSpeedFields::DesignInletAirWetBulbTemperature, ""));
}

boost::optional<double> CoolingTowerVariableSpeed_Impl::designApproachTemperature() const {
  return getDouble(openstudio::CoolingTower_VariableSpeedFields::DesignApproachTemperature, true);
}

bool CoolingTowerVariableSpeed_Impl::setDesignApproachTemperature(double designApproachTemperature) {
  return setDouble(openstudio::CoolingTower_VariableSpeedFields::DesignApproachTemperature, designApproachTemperature);
}

void CoolingTowerVariableSpeed_Impl::resetDesignApproachTemperature() {
  OS_ASSERT(setString(openstudio::CoolingTower_VariableSpeedFields::DesignApproachTemperature, ""));
}

boost::optional<double> CoolingTowerVariableSpeed_Impl::designRangeTemperature() const {
  return getDouble(openstudio::CoolingTower_VariableSpeedFields::DesignRangeTemperature, true);
}

bool CoolingTowerVariableSpeed_Impl::setDesignRangeTemperature(double designRangeTemperature) {
  return setDouble(openstudio::CoolingTower_VariableSpeedFields::DesignRangeTemperature, designRangeTemperature);
}

void CoolingTowerVariableSpeed_Impl::resetDesignRangeTemperature() {
  OS_ASSERT(setString(openstudio::CoolingTower_VariableSpeedFields::DesignRangeTemperature, ""));
}

boost::optional<double> CoolingTowerVariableSpeed_Impl::designWaterFlowRate() const {
  return getDouble(openstudio::CoolingTower_VariableSpeedFields::DesignWaterFlowRate, true);
}

bool CoolingTowerVariableSpeed_Impl::isDesignWaterFlowRateAutosized() const {
  if (auto value = getString(openstudio::CoolingTower_VariableSpeedFields::DesignWaterFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool CoolingTowerVariableSpeed_Impl::setDesignWaterFlowRate(double designWaterFlowRate) {
  return setDouble(openstudio::CoolingTower_VariableSpeedFields::DesignWaterFlowRate, designWaterFlowRate);
}

void CoolingTowerVariableSpeed_Impl::autosizeDesignWaterFlowRate() {
  OS_ASSERT(setString(openstudio::CoolingTower_VariableSpeedFields::DesignWaterFlowRate, "autosize"));
}

boost::optional<double> CoolingTowerVariableSpeed_Impl::designAirFlowRate() const {
  return getDouble(openstudio::CoolingTower_VariableSpeedFields::DesignAirFlowRate, true);
}

bool CoolingTowerVariableSpeed_Impl::isDesignAirFlowRateAutosized() const {
  if (auto value = getString(openstudio::CoolingTower_VariableSpeedFields::DesignAirFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool CoolingTowerVariableSpeed_Impl::setDesignAirFlowRate(double designAirFlowRate) {
  return setDouble(openstudio::CoolingTower_VariableSpeedFields::DesignAirFlowRate, designAirFlowRate);
}

void CoolingTowerVariableSpeed_Impl::autosizeDesignAirFlowRate() {
  OS_ASSERT(setString(openstudio::CoolingTower_VariableSpeedFields::DesignAirFlowRate, "autosize"));
}

boost::optional<double> CoolingTowerVariableSpeed_Impl::designFanPower() const {
  return getDouble(openstudio::CoolingTower_VariableSpeedFields::DesignFanPower, true);
}

bool CoolingTowerVariableSpeed_Impl::isDesignFanPowerAutosized() const {
  if (auto value = getString(openstudio::CoolingTower_VariableSpeedFields::DesignFanPower, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool CoolingTowerVariableSpeed_Impl::setDesignFanPower(double designFanPower) {
  return setDouble(openstudio::CoolingTower_VariableSpeedFields::DesignFanPower, designFanPower);
}

void CoolingTowerVariableSpeed_Impl::autosizeDesignFanPower() {
  OS_ASSERT(setString(openstudio::CoolingTower_VariableSpeedFields::DesignFanPower, "autosize"));
}

boost::optional<double> CoolingTowerVariableSpeed_Impl::minimumAirFlowRateRatio() const {
  return getDouble(openstudio::CoolingTower_VariableSpeedFields::MinimumAirFlowRateRatio, true);
}

bool CoolingTowerVariableSpeed_Impl::setMinimumAirFlowRateRatio(double minimumAirFlowRateRatio) {
  return setDouble(openstudio::CoolingTower_VariableSpeedFields::MinimumAirFlowRateRatio, minimumAirFlowRateRatio);
}

void CoolingTowerVariableSpeed_Impl::resetMinimumAirFlowRateRatio() {
  OS_ASSERT(setString(openstudio::CoolingTower_VariableSpeedFields::MinimumAirFlowRateRatio, ""));
}

boost::optional<double> CoolingTowerVariableSpeed_Impl::fractionofTowerCapacityinFreeConvectionRegime() const {
  return getDouble(openstudio::CoolingTower_VariableSpeedFields::FractionofTowerCapacityinFreeConvectionRegime, true);
}

bool CoolingTowerVariableSpeed_Impl::setFractionofTowerCapacityinFreeConvectionRegime(double fractionofTowerCapacityinFreeConvectionRegime) {
  return setDouble(openstudio::CoolingTower_VariableSpeedFields::FractionofTowerCapacityinFreeConvectionRegime,
                   fractionofTowerCapacityinFreeConvectionRegime);
}

void CoolingTowerVariableSpeed_Impl::resetFractionofTowerCapacityinFreeConvectionRegime() {
  OS_ASSERT(setString(openstudio::CoolingTower_VariableSpeedFields::FractionofTowerCapacityinFreeConvectionRegime, ""));
}

boost::optional<double> CoolingTowerVariableSpeed_Impl::basinHeaterCapacity() const {
  return getDouble(openstudio::CoolingTower_VariableSpeedFields::BasinHeaterCapacity, true);
}

bool CoolingTowerVariableSpeed_Impl::setBasinHeaterCapacity(double basinHeaterCapacity) {
  return setDouble(openstudio::CoolingTower_VariableSpeedFields::BasinHeaterCapacity, basinHeaterCapacity);
}

void CoolingTowerVariableSpeed_Impl::resetBasinHeaterCapacity() {
  OS_ASSERT(setString(openstudio::CoolingTower_VariableSpeedFields::BasinHeaterCapacity, ""));
}

boost::optional<double> CoolingTowerVariableSpeed_Impl::basinHeaterSetpointTemperature() const {
  return getDouble(openstudio::CoolingTower_VariableSpeedFields::BasinHeaterSetpointTemperature, true);
}

bool CoolingTowerVariableSpeed_Impl::setBasinHeaterSetpointTemperature(double basinHeaterSetpointTemperature) {
  return setDouble(openstudio::CoolingTower_VariableSpeedFields::BasinHeaterSetpointTemperature, basinHeaterSetpointTemperature);
}

void CoolingTowerVariableSpeed_Impl::resetBasinHeaterSetpointTemperature() {
  OS_ASSERT(setString(openstudio::CoolingTower_VariableSpeedFields::BasinHeaterSetpointTemperature, ""));
}

std::string CoolingTowerVariableSpeed_Impl::evaporationLossMode() const {
  const auto value = getString(openstudio::CoolingTower_VariableSpeedFields::EvaporationLossMode, true);
  OS_ASSERT(value);
  return *value;
}

bool CoolingTowerVariableSpeed_Impl::isEvaporationLossModeDefaulted() const {
  return isEmpty(openstudio::CoolingTower_VariableSpeedFields::EvaporationLossMode);
}

bool CoolingTowerVariableSpeed_Impl::setEvaporationLossMode(const std::string& evaporationLossMode) {
  return setString(openstudio::CoolingTower_VariableSpeedFields::EvaporationLossMode, evaporationLossMode);
}

void CoolingTowerVariableSpeed_Impl::resetEvaporationLossMode() {
  OS_ASSERT(setString(openstudio::CoolingTower_VariableSpeedFields::EvaporationLossMode, ""));
}

double CoolingTowerVariableSpeed_Impl::evaporationLossFactor() const {
  const auto value = getDouble(openstudio::CoolingTower_VariableSpeedFields::EvaporationLossFactor, true);
  OS_ASSERT(value);
  return *value;
}

bool CoolingTowerVariableSpeed_Impl::isEvaporationLossFactorDefaulted() const {
  return isEmpty(openstudio::CoolingTower_VariableSpeedFields::EvaporationLossFactor);
}

bool CoolingTowerVariableSpeed_Impl::setEvaporationLossFactor(double evaporationLossFactor) {
  return setDouble(openstudio::CoolingTower_VariableSpeedFields::EvaporationLossFactor, evaporationLossFactor);
}

void CoolingTowerVariableSpeed_Impl::resetEvaporationLossFactor() {
  OS_ASSERT(setString(openstudio::CoolingTower_VariableSpeedFields::EvaporationLossFactor, ""));
}

boost::optional<double> CoolingTowerVariableSpeed_Impl::driftLossPercent() const {
  return getDouble(openstudio::CoolingTower_VariableSpeedFields::DriftLossPercent, true);
}

bool CoolingTowerVariableSpeed_Impl::setDriftLossPercent(double driftLossPercent) {
  return setDouble(openstudio::CoolingTower_VariableSpeedFields::DriftLossPercent, driftLossPercent);
}

void CoolingTowerVariableSpeed_Impl::resetDriftLossPercent() {
  OS_ASSERT(setString(openstudio::CoolingTower_VariableSpeedFields::DriftLossPercent, ""));
}

std::string CoolingTowerVariableSpeed_Impl::blowdownCalculationMode() const {
  const auto value = getString(openstudio::CoolingTower_VariableSpeedFields::BlowdownCalculationMode, true);
  OS_ASSERT(value);
  return *value;
}

bool CoolingTowerVariableSpeed_Impl::isBlowdownCalculationModeDefaulted() const {
  return isEmpty(openstudio::CoolingTower_VariableSpeedFields::BlowdownCalculationMode);
}

bool CoolingTowerVariableSpeed_Impl::setBlowdownCalculationMode(const std::string& blowdownCalculationMode) {
  return setString(openstudio::CoolingTower_VariableSpeedFields::BlowdownCalculationMode, blowdownCalculationMode);
}

void CoolingTowerVariableSpeed_Impl::resetBlowdownCalculationMode() {
  OS_ASSERT(setString(openstudio::CoolingTower_VariableSpeedFields::BlowdownCalculationMode, ""));
}

boost::optional<double> CoolingTowerVariableSpeed_Impl::blowdownConcentrationRatio() const {
  return getDouble(openstudio::CoolingTower_VariableSpeedFields::BlowdownConcentrationRatio, true);
}

bool CoolingTowerVariableSpeed_Impl::setBlowdownConcentrationRatio(double blowdownConcentrationRatio) {
  return setDouble(openstudio::CoolingTower_VariableSpeedFields::BlowdownConcentrationRatio, blowdownConcentrationRatio);
}

void CoolingTowerVariableSpeed_Impl::resetBlowdownConcentrationRatio() {
  OS_ASSERT(setString(openstudio::CoolingTower_VariableSpeedFields::BlowdownConcentrationRatio, ""));
}

boost::optional<int> CoolingTowerVariableSpeed_Impl::numberofCells() const {
  return getInt(openstudio::CoolingTower_VariableSpeedFields::NumberofCells, true);
}

bool CoolingTowerVariableSpeed_Impl::setNumberofCells(int numberofCells) {
  return setInt(openstudio::CoolingTower_VariableSpeedFields::NumberofCells, numberofCells);
}

void CoolingTowerVariableSpeed_Impl::resetNumberofCells() {
  OS_ASSERT(setString(openstudio::CoolingTower_VariableSpeedFields::NumberofCells, ""));
}

std::string CoolingTowerVariableSpeed_Impl::cellControl() const {
  const auto value = getString(openstudio::CoolingTower_VariableSpeedFields::CellControl, true);
  OS_ASSERT(value);
  return *value;
}

bool CoolingTowerVariableSpeed_Impl::isCellControlDefaulted() const {
  return isEmpty(openstudio::CoolingTower_VariableSpeedFields::CellControl);
}

bool CoolingTowerVariableSpeed_Impl::setCellControl(const std::string& cellControl) {
  return setString(openstudio::CoolingTower_VariableSpeedFields::CellControl, cellControl);
}

void CoolingTowerVariableSpeed_Impl::resetCellControl() {
  OS_ASSERT(setString(openstudio::CoolingTower_VariableSpeedFields::CellControl, ""));
}

boost::optional<double> CoolingTowerVariableSpeed_Impl::cellMinimumWaterFlowRateFraction() const {
  return getDouble(openstudio::CoolingTower_VariableSpeedFields::CellMinimumWaterFlowRateFraction, true);
}

bool CoolingTowerVariableSpeed_Impl::setCellMinimumWaterFlowRateFraction(double cellMinimumWaterFlowRateFraction) {
  return setDouble(openstudio::CoolingTower_VariableSpeedFields::CellMinimumWaterFlowRateFraction, cellMinimumWaterFlowRateFraction);
}

void CoolingTowerVariableSpeed_Impl::resetCellMinimumWaterFlowRateFraction() {
  OS_ASSERT(setString(openstudio::CoolingTower_VariableSpeedFields::CellMinimumWaterFlowRateFraction, ""));
}

boost::optional<double> CoolingTowerVariableSpeed_Impl::cellMaximumWaterFlowRateFraction() const {
  return getDouble(openstudio::CoolingTower_VariableSpeedFields::CellMaximumWaterFlowRateFraction, true);
}

bool CoolingTowerVariableSpeed_Impl::setCellMaximumWaterFlowRateFraction(double cellMaximumWaterFlowRateFraction) {
  return setDouble(openstudio::CoolingTower_VariableSpeedFields::CellMaximumWaterFlowRateFraction, cellMaximumWaterFlowRateFraction);
}

void CoolingTowerVariableSpeed_Impl::resetCellMaximumWaterFlowRateFraction() {
  OS_ASSERT(setString(openstudio::CoolingTower_VariableSpeedFields::CellMaximumWaterFlowRateFraction, ""));
}

boost::optional<double> CoolingTowerVariableSpeed_Impl::sizingFactor() const {
  return getDouble(openstudio::CoolingTower_VariableSpeedFields::SizingFactor, true);
}

bool CoolingTowerVariableSpeed_Impl::setSizingFactor(double sizingFactor) {
  return setDouble(openstudio::CoolingTower_VariableSpeedFields::SizingFactor, sizingFactor);
}

void CoolingTowerVariableSpeed_Impl::resetSizingFactor() {
  OS_ASSERT(setString(openstudio::CoolingTower_VariableSpeedFields::SizingFactor, ""));
}

std::string CoolingTowerVariableSpeed_Impl::endUseSubcategory() const {
  const auto value = getString(openstudio::CoolingTower_VariableSpeedFields::EndUseSubcategory, true);
  OS_ASSERT(value);
  return *value;
}

bool CoolingTowerVariableSpeed_Impl::setEndUseSubcategory(const std::string& endUseSubcategory) {
  return setString(openstudio::CoolingTower_VariableSpeedFields::EndUseSubcategory, endUseSubcategory);
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
