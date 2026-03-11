/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ResourceObject/CoilCoolingDXCurveFitSpeed.hpp"
#include "ResourceObject/CoilCoolingDXCurveFitSpeed_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/Coil_Cooling_DX_CurveFit_Speed_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

CoilCoolingDXCurveFitSpeed::CoilCoolingDXCurveFitSpeed(const Model& model) : ModelObject(CoilCoolingDXCurveFitSpeed::iddObjectType(), model) {}

CoilCoolingDXCurveFitSpeed::CoilCoolingDXCurveFitSpeed(std::shared_ptr<detail::CoilCoolingDXCurveFitSpeed_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType CoilCoolingDXCurveFitSpeed::iddObjectType() {
  return IddObjectType::Coil_Cooling_DX_CurveFit_Speed;
}

double CoilCoolingDXCurveFitSpeed::grossTotalCoolingCapacityFraction() const {
  return getImpl<detail::CoilCoolingDXCurveFitSpeed_Impl>()->grossTotalCoolingCapacityFraction();
}

double CoilCoolingDXCurveFitSpeed::evaporatorAirFlowRateFraction() const {
  return getImpl<detail::CoilCoolingDXCurveFitSpeed_Impl>()->evaporatorAirFlowRateFraction();
}

double CoilCoolingDXCurveFitSpeed::condenserAirFlowRateFraction() const {
  return getImpl<detail::CoilCoolingDXCurveFitSpeed_Impl>()->condenserAirFlowRateFraction();
}

boost::optional<double> CoilCoolingDXCurveFitSpeed::grossSensibleHeatRatio() const {
  return getImpl<detail::CoilCoolingDXCurveFitSpeed_Impl>()->grossSensibleHeatRatio();
}

bool CoilCoolingDXCurveFitSpeed::isGrossSensibleHeatRatioAutosized() const {
  return getImpl<detail::CoilCoolingDXCurveFitSpeed_Impl>()->isGrossSensibleHeatRatioAutosized();
}

double CoilCoolingDXCurveFitSpeed::grossCoolingCOP() const {
  return getImpl<detail::CoilCoolingDXCurveFitSpeed_Impl>()->grossCoolingCOP();
}

double CoilCoolingDXCurveFitSpeed::activeFractionofCoilFaceArea() const {
  return getImpl<detail::CoilCoolingDXCurveFitSpeed_Impl>()->activeFractionofCoilFaceArea();
}

double CoilCoolingDXCurveFitSpeed::ratedEvaporatorFanPowerPerVolumeFlowRate() const {
  return getImpl<detail::CoilCoolingDXCurveFitSpeed_Impl>()->ratedEvaporatorFanPowerPerVolumeFlowRate2017();
}

double CoilCoolingDXCurveFitSpeed::ratedEvaporatorFanPowerPerVolumeFlowRate2017() const {
  return getImpl<detail::CoilCoolingDXCurveFitSpeed_Impl>()->ratedEvaporatorFanPowerPerVolumeFlowRate2017();
}

double CoilCoolingDXCurveFitSpeed::ratedEvaporatorFanPowerPerVolumeFlowRate2023() const {
  return getImpl<detail::CoilCoolingDXCurveFitSpeed_Impl>()->ratedEvaporatorFanPowerPerVolumeFlowRate2023();
}

double CoilCoolingDXCurveFitSpeed::evaporativeCondenserPumpPowerFraction() const {
  return getImpl<detail::CoilCoolingDXCurveFitSpeed_Impl>()->evaporativeCondenserPumpPowerFraction();
}

double CoilCoolingDXCurveFitSpeed::evaporativeCondenserEffectiveness() const {
  return getImpl<detail::CoilCoolingDXCurveFitSpeed_Impl>()->evaporativeCondenserEffectiveness();
}

double CoilCoolingDXCurveFitSpeed::ratedWasteHeatFractionofPowerInput() const {
  return getImpl<detail::CoilCoolingDXCurveFitSpeed_Impl>()->ratedWasteHeatFractionofPowerInput();
}

bool CoilCoolingDXCurveFitSpeed::setGrossTotalCoolingCapacityFraction(double grossTotalCoolingCapacityFraction) {
  return getImpl<detail::CoilCoolingDXCurveFitSpeed_Impl>()->setGrossTotalCoolingCapacityFraction(grossTotalCoolingCapacityFraction);
}

bool CoilCoolingDXCurveFitSpeed::setEvaporatorAirFlowRateFraction(double evaporatorAirFlowRateFraction) {
  return getImpl<detail::CoilCoolingDXCurveFitSpeed_Impl>()->setEvaporatorAirFlowRateFraction(evaporatorAirFlowRateFraction);
}

bool CoilCoolingDXCurveFitSpeed::setCondenserAirFlowRateFraction(double condenserAirFlowRateFraction) {
  return getImpl<detail::CoilCoolingDXCurveFitSpeed_Impl>()->setCondenserAirFlowRateFraction(condenserAirFlowRateFraction);
}

bool CoilCoolingDXCurveFitSpeed::setGrossSensibleHeatRatio(double grossSensibleHeatRatio) {
  return getImpl<detail::CoilCoolingDXCurveFitSpeed_Impl>()->setGrossSensibleHeatRatio(grossSensibleHeatRatio);
}

void CoilCoolingDXCurveFitSpeed::autosizeGrossSensibleHeatRatio() {
  getImpl<detail::CoilCoolingDXCurveFitSpeed_Impl>()->autosizeGrossSensibleHeatRatio();
}

bool CoilCoolingDXCurveFitSpeed::setGrossCoolingCOP(double grossCoolingCOP) {
  return getImpl<detail::CoilCoolingDXCurveFitSpeed_Impl>()->setGrossCoolingCOP(grossCoolingCOP);
}

bool CoilCoolingDXCurveFitSpeed::setActiveFractionofCoilFaceArea(double activeFractionofCoilFaceArea) {
  return getImpl<detail::CoilCoolingDXCurveFitSpeed_Impl>()->setActiveFractionofCoilFaceArea(activeFractionofCoilFaceArea);
}

bool CoilCoolingDXCurveFitSpeed::setRatedEvaporatorFanPowerPerVolumeFlowRate(double ratedEvaporatorFanPowerPerVolumeFlowRate) {
  return getImpl<detail::CoilCoolingDXCurveFitSpeed_Impl>()->setRatedEvaporatorFanPowerPerVolumeFlowRate2017(
    ratedEvaporatorFanPowerPerVolumeFlowRate);
}

bool CoilCoolingDXCurveFitSpeed::setRatedEvaporatorFanPowerPerVolumeFlowRate2017(double ratedEvaporatorFanPowerPerVolumeFlowRate2017) {
  return getImpl<detail::CoilCoolingDXCurveFitSpeed_Impl>()->setRatedEvaporatorFanPowerPerVolumeFlowRate2017(
    ratedEvaporatorFanPowerPerVolumeFlowRate2017);
}

bool CoilCoolingDXCurveFitSpeed::setRatedEvaporatorFanPowerPerVolumeFlowRate2023(double ratedEvaporatorFanPowerPerVolumeFlowRate2023) {
  return getImpl<detail::CoilCoolingDXCurveFitSpeed_Impl>()->setRatedEvaporatorFanPowerPerVolumeFlowRate2023(
    ratedEvaporatorFanPowerPerVolumeFlowRate2023);
}

bool CoilCoolingDXCurveFitSpeed::setEvaporativeCondenserPumpPowerFraction(double evaporativeCondenserPumpPowerFraction) {
  return getImpl<detail::CoilCoolingDXCurveFitSpeed_Impl>()->setEvaporativeCondenserPumpPowerFraction(evaporativeCondenserPumpPowerFraction);
}

bool CoilCoolingDXCurveFitSpeed::setEvaporativeCondenserEffectiveness(double evaporativeCondenserEffectiveness) {
  return getImpl<detail::CoilCoolingDXCurveFitSpeed_Impl>()->setEvaporativeCondenserEffectiveness(evaporativeCondenserEffectiveness);
}

bool CoilCoolingDXCurveFitSpeed::setRatedWasteHeatFractionofPowerInput(double ratedWasteHeatFractionofPowerInput) {
  return getImpl<detail::CoilCoolingDXCurveFitSpeed_Impl>()->setRatedWasteHeatFractionofPowerInput(ratedWasteHeatFractionofPowerInput);
}

boost::optional<double> CoilCoolingDXCurveFitSpeed::autosizedGrossSensibleHeatRatio() const {
  return getImpl<detail::CoilCoolingDXCurveFitSpeed_Impl>()->autosizedGrossSensibleHeatRatio();
}

void CoilCoolingDXCurveFitSpeed::autosize() {
  return getImpl<detail::CoilCoolingDXCurveFitSpeed_Impl>()->autosize();
}

void CoilCoolingDXCurveFitSpeed::applySizingValues() {
  return getImpl<detail::CoilCoolingDXCurveFitSpeed_Impl>()->applySizingValues();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

double CoilCoolingDXCurveFitSpeed_Impl::grossTotalCoolingCapacityFraction() const {
  const auto value = getDouble(openstudio::Coil_Cooling_DX_CurveFit_SpeedFields::GrossTotalCoolingCapacityFraction, true);
  OS_ASSERT(value);
  return *value;
}

double CoilCoolingDXCurveFitSpeed_Impl::evaporatorAirFlowRateFraction() const {
  const auto value = getDouble(openstudio::Coil_Cooling_DX_CurveFit_SpeedFields::EvaporatorAirFlowRateFraction, true);
  OS_ASSERT(value);
  return *value;
}

double CoilCoolingDXCurveFitSpeed_Impl::condenserAirFlowRateFraction() const {
  const auto value = getDouble(openstudio::Coil_Cooling_DX_CurveFit_SpeedFields::CondenserAirFlowRateFraction, true);
  OS_ASSERT(value);
  return *value;
}

boost::optional<double> CoilCoolingDXCurveFitSpeed_Impl::grossSensibleHeatRatio() const {
  return getDouble(openstudio::Coil_Cooling_DX_CurveFit_SpeedFields::GrossSensibleHeatRatio, true);
}

bool CoilCoolingDXCurveFitSpeed_Impl::isGrossSensibleHeatRatioAutosized() const {
  if (auto value = getString(openstudio::Coil_Cooling_DX_CurveFit_SpeedFields::GrossSensibleHeatRatio, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

double CoilCoolingDXCurveFitSpeed_Impl::grossCoolingCOP() const {
  const auto value = getDouble(openstudio::Coil_Cooling_DX_CurveFit_SpeedFields::GrossCoolingCOP, true);
  OS_ASSERT(value);
  return *value;
}

double CoilCoolingDXCurveFitSpeed_Impl::activeFractionofCoilFaceArea() const {
  const auto value = getDouble(openstudio::Coil_Cooling_DX_CurveFit_SpeedFields::ActiveFractionofCoilFaceArea, true);
  OS_ASSERT(value);
  return *value;
}

double CoilCoolingDXCurveFitSpeed_Impl::ratedEvaporatorFanPowerPerVolumeFlowRate2017() const {
  const auto value = getDouble(openstudio::Coil_Cooling_DX_CurveFit_SpeedFields::RatedEvaporatorFanPowerPerVolumeFlowRate2017, true);
  OS_ASSERT(value);
  return *value;
}

double CoilCoolingDXCurveFitSpeed_Impl::ratedEvaporatorFanPowerPerVolumeFlowRate2023() const {
  const auto value = getDouble(openstudio::Coil_Cooling_DX_CurveFit_SpeedFields::RatedEvaporatorFanPowerPerVolumeFlowRate2023, true);
  OS_ASSERT(value);
  return *value;
}

double CoilCoolingDXCurveFitSpeed_Impl::evaporativeCondenserPumpPowerFraction() const {
  const auto value = getDouble(openstudio::Coil_Cooling_DX_CurveFit_SpeedFields::EvaporativeCondenserPumpPowerFraction, true);
  OS_ASSERT(value);
  return *value;
}

double CoilCoolingDXCurveFitSpeed_Impl::evaporativeCondenserEffectiveness() const {
  const auto value = getDouble(openstudio::Coil_Cooling_DX_CurveFit_SpeedFields::EvaporativeCondenserEffectiveness, true);
  OS_ASSERT(value);
  return *value;
}

double CoilCoolingDXCurveFitSpeed_Impl::ratedWasteHeatFractionofPowerInput() const {
  const auto value = getDouble(openstudio::Coil_Cooling_DX_CurveFit_SpeedFields::RatedWasteHeatFractionofPowerInput, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilCoolingDXCurveFitSpeed_Impl::setGrossTotalCoolingCapacityFraction(double grossTotalCoolingCapacityFraction) {
  return setDouble(openstudio::Coil_Cooling_DX_CurveFit_SpeedFields::GrossTotalCoolingCapacityFraction, grossTotalCoolingCapacityFraction);
}

bool CoilCoolingDXCurveFitSpeed_Impl::setEvaporatorAirFlowRateFraction(double evaporatorAirFlowRateFraction) {
  return setDouble(openstudio::Coil_Cooling_DX_CurveFit_SpeedFields::EvaporatorAirFlowRateFraction, evaporatorAirFlowRateFraction);
}

bool CoilCoolingDXCurveFitSpeed_Impl::setCondenserAirFlowRateFraction(double condenserAirFlowRateFraction) {
  return setDouble(openstudio::Coil_Cooling_DX_CurveFit_SpeedFields::CondenserAirFlowRateFraction, condenserAirFlowRateFraction);
}

bool CoilCoolingDXCurveFitSpeed_Impl::setGrossSensibleHeatRatio(double grossSensibleHeatRatio) {
  return setDouble(openstudio::Coil_Cooling_DX_CurveFit_SpeedFields::GrossSensibleHeatRatio, grossSensibleHeatRatio);
}

void CoilCoolingDXCurveFitSpeed_Impl::autosizeGrossSensibleHeatRatio() {
  OS_ASSERT(setString(openstudio::Coil_Cooling_DX_CurveFit_SpeedFields::GrossSensibleHeatRatio, "autosize"));
}

bool CoilCoolingDXCurveFitSpeed_Impl::setGrossCoolingCOP(double grossCoolingCOP) {
  return setDouble(openstudio::Coil_Cooling_DX_CurveFit_SpeedFields::GrossCoolingCOP, grossCoolingCOP);
}

bool CoilCoolingDXCurveFitSpeed_Impl::setActiveFractionofCoilFaceArea(double activeFractionofCoilFaceArea) {
  return setDouble(openstudio::Coil_Cooling_DX_CurveFit_SpeedFields::ActiveFractionofCoilFaceArea, activeFractionofCoilFaceArea);
}

bool CoilCoolingDXCurveFitSpeed_Impl::setRatedEvaporatorFanPowerPerVolumeFlowRate2017(double ratedEvaporatorFanPowerPerVolumeFlowRate2017) {
  return setDouble(openstudio::Coil_Cooling_DX_CurveFit_SpeedFields::RatedEvaporatorFanPowerPerVolumeFlowRate2017,
                   ratedEvaporatorFanPowerPerVolumeFlowRate2017);
}

bool CoilCoolingDXCurveFitSpeed_Impl::setRatedEvaporatorFanPowerPerVolumeFlowRate2023(double ratedEvaporatorFanPowerPerVolumeFlowRate2023) {
  return setDouble(openstudio::Coil_Cooling_DX_CurveFit_SpeedFields::RatedEvaporatorFanPowerPerVolumeFlowRate2023,
                   ratedEvaporatorFanPowerPerVolumeFlowRate2023);
}

bool CoilCoolingDXCurveFitSpeed_Impl::setEvaporativeCondenserPumpPowerFraction(double evaporativeCondenserPumpPowerFraction) {
  return setDouble(openstudio::Coil_Cooling_DX_CurveFit_SpeedFields::EvaporativeCondenserPumpPowerFraction,
                   evaporativeCondenserPumpPowerFraction);
}

bool CoilCoolingDXCurveFitSpeed_Impl::setEvaporativeCondenserEffectiveness(double evaporativeCondenserEffectiveness) {
  return setDouble(openstudio::Coil_Cooling_DX_CurveFit_SpeedFields::EvaporativeCondenserEffectiveness, evaporativeCondenserEffectiveness);
}

bool CoilCoolingDXCurveFitSpeed_Impl::setRatedWasteHeatFractionofPowerInput(double ratedWasteHeatFractionofPowerInput) {
  return setDouble(openstudio::Coil_Cooling_DX_CurveFit_SpeedFields::RatedWasteHeatFractionofPowerInput, ratedWasteHeatFractionofPowerInput);
}

boost::optional<double> CoilCoolingDXCurveFitSpeed_Impl::autosizedGrossSensibleHeatRatio() const {
  // epmodel does not currently resolve autosized values from SQL results.
  return boost::none;
}

void CoilCoolingDXCurveFitSpeed_Impl::autosize() {
  autosizeGrossSensibleHeatRatio();
}

void CoilCoolingDXCurveFitSpeed_Impl::applySizingValues() {
  if (auto value = autosizedGrossSensibleHeatRatio()) {
    setGrossSensibleHeatRatio(*value);
  }
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
