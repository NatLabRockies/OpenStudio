/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "WaterToWaterComponent/HeatPumpWaterToWaterEquationFitHeating.hpp"
#include "WaterToWaterComponent/HeatPumpWaterToWaterEquationFitHeating_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/HeatPump_WaterToWater_EquationFit_Heating_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

HeatPumpWaterToWaterEquationFitHeating::HeatPumpWaterToWaterEquationFitHeating(const Model& model)
  : ModelObject(HeatPumpWaterToWaterEquationFitHeating::iddObjectType(), model) {
  autosizeReferenceLoadSideFlowRate();
  autosizeReferenceSourceSideFlowRate();
  autosizeRatedHeatingCapacity();
  autosizeRatedHeatingPowerConsumption();
  OS_ASSERT(setReferenceCoefficientofPerformance(7.5));
  OS_ASSERT(setSizingFactor(1.0));
}

HeatPumpWaterToWaterEquationFitHeating::HeatPumpWaterToWaterEquationFitHeating(
  std::shared_ptr<detail::HeatPumpWaterToWaterEquationFitHeating_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType HeatPumpWaterToWaterEquationFitHeating::iddObjectType() {
  return IddObjectType::HeatPump_WaterToWater_EquationFit_Heating;
}

boost::optional<double> HeatPumpWaterToWaterEquationFitHeating::referenceLoadSideFlowRate() const {
  return getImpl<detail::HeatPumpWaterToWaterEquationFitHeating_Impl>()->referenceLoadSideFlowRate();
}

double HeatPumpWaterToWaterEquationFitHeating::ratedLoadSideFlowRate() const {
  return getImpl<detail::HeatPumpWaterToWaterEquationFitHeating_Impl>()->ratedLoadSideFlowRate();
}

bool HeatPumpWaterToWaterEquationFitHeating::isReferenceLoadSideFlowRateAutosized() const {
  return getImpl<detail::HeatPumpWaterToWaterEquationFitHeating_Impl>()->isReferenceLoadSideFlowRateAutosized();
}

boost::optional<double> HeatPumpWaterToWaterEquationFitHeating::referenceSourceSideFlowRate() const {
  return getImpl<detail::HeatPumpWaterToWaterEquationFitHeating_Impl>()->referenceSourceSideFlowRate();
}

double HeatPumpWaterToWaterEquationFitHeating::ratedSourceSideFlowRate() const {
  return getImpl<detail::HeatPumpWaterToWaterEquationFitHeating_Impl>()->ratedSourceSideFlowRate();
}

bool HeatPumpWaterToWaterEquationFitHeating::isReferenceSourceSideFlowRateAutosized() const {
  return getImpl<detail::HeatPumpWaterToWaterEquationFitHeating_Impl>()->isReferenceSourceSideFlowRateAutosized();
}

boost::optional<double> HeatPumpWaterToWaterEquationFitHeating::ratedHeatingCapacity() const {
  return getImpl<detail::HeatPumpWaterToWaterEquationFitHeating_Impl>()->ratedHeatingCapacity();
}

bool HeatPumpWaterToWaterEquationFitHeating::isRatedHeatingCapacityAutosized() const {
  return getImpl<detail::HeatPumpWaterToWaterEquationFitHeating_Impl>()->isRatedHeatingCapacityAutosized();
}

boost::optional<double> HeatPumpWaterToWaterEquationFitHeating::ratedHeatingPowerConsumption() const {
  return getImpl<detail::HeatPumpWaterToWaterEquationFitHeating_Impl>()->ratedHeatingPowerConsumption();
}

bool HeatPumpWaterToWaterEquationFitHeating::isRatedHeatingPowerConsumptionAutosized() const {
  return getImpl<detail::HeatPumpWaterToWaterEquationFitHeating_Impl>()->isRatedHeatingPowerConsumptionAutosized();
}

double HeatPumpWaterToWaterEquationFitHeating::referenceCoefficientofPerformance() const {
  return getImpl<detail::HeatPumpWaterToWaterEquationFitHeating_Impl>()->referenceCoefficientofPerformance();
}

double HeatPumpWaterToWaterEquationFitHeating::sizingFactor() const {
  return getImpl<detail::HeatPumpWaterToWaterEquationFitHeating_Impl>()->sizingFactor();
}

bool HeatPumpWaterToWaterEquationFitHeating::setReferenceLoadSideFlowRate(double referenceLoadSideFlowRate) {
  return getImpl<detail::HeatPumpWaterToWaterEquationFitHeating_Impl>()->setReferenceLoadSideFlowRate(referenceLoadSideFlowRate);
}

bool HeatPumpWaterToWaterEquationFitHeating::setRatedLoadSideFlowRate(double ratedLoadSideFlowRate) {
  return getImpl<detail::HeatPumpWaterToWaterEquationFitHeating_Impl>()->setRatedLoadSideFlowRate(ratedLoadSideFlowRate);
}

void HeatPumpWaterToWaterEquationFitHeating::autosizeReferenceLoadSideFlowRate() {
  getImpl<detail::HeatPumpWaterToWaterEquationFitHeating_Impl>()->autosizeReferenceLoadSideFlowRate();
}

bool HeatPumpWaterToWaterEquationFitHeating::setReferenceSourceSideFlowRate(double referenceSourceSideFlowRate) {
  return getImpl<detail::HeatPumpWaterToWaterEquationFitHeating_Impl>()->setReferenceSourceSideFlowRate(referenceSourceSideFlowRate);
}

bool HeatPumpWaterToWaterEquationFitHeating::setRatedSourceSideFlowRate(double ratedSourceSideFlowRate) {
  return getImpl<detail::HeatPumpWaterToWaterEquationFitHeating_Impl>()->setRatedSourceSideFlowRate(ratedSourceSideFlowRate);
}

void HeatPumpWaterToWaterEquationFitHeating::autosizeReferenceSourceSideFlowRate() {
  getImpl<detail::HeatPumpWaterToWaterEquationFitHeating_Impl>()->autosizeReferenceSourceSideFlowRate();
}

bool HeatPumpWaterToWaterEquationFitHeating::setRatedHeatingCapacity(double ratedHeatingCapacity) {
  return getImpl<detail::HeatPumpWaterToWaterEquationFitHeating_Impl>()->setRatedHeatingCapacity(ratedHeatingCapacity);
}

void HeatPumpWaterToWaterEquationFitHeating::autosizeRatedHeatingCapacity() {
  getImpl<detail::HeatPumpWaterToWaterEquationFitHeating_Impl>()->autosizeRatedHeatingCapacity();
}

bool HeatPumpWaterToWaterEquationFitHeating::setRatedHeatingPowerConsumption(double ratedHeatingPowerConsumption) {
  return getImpl<detail::HeatPumpWaterToWaterEquationFitHeating_Impl>()->setRatedHeatingPowerConsumption(ratedHeatingPowerConsumption);
}

void HeatPumpWaterToWaterEquationFitHeating::autosizeRatedHeatingPowerConsumption() {
  getImpl<detail::HeatPumpWaterToWaterEquationFitHeating_Impl>()->autosizeRatedHeatingPowerConsumption();
}

bool HeatPumpWaterToWaterEquationFitHeating::setReferenceCoefficientofPerformance(double referenceCoefficientofPerformance) {
  return getImpl<detail::HeatPumpWaterToWaterEquationFitHeating_Impl>()->setReferenceCoefficientofPerformance(referenceCoefficientofPerformance);
}

bool HeatPumpWaterToWaterEquationFitHeating::setSizingFactor(double sizingFactor) {
  return getImpl<detail::HeatPumpWaterToWaterEquationFitHeating_Impl>()->setSizingFactor(sizingFactor);
}

boost::optional<double> HeatPumpWaterToWaterEquationFitHeating::autosizedReferenceLoadSideFlowRate() const {
  return getImpl<detail::HeatPumpWaterToWaterEquationFitHeating_Impl>()->autosizedReferenceLoadSideFlowRate();
}

boost::optional<double> HeatPumpWaterToWaterEquationFitHeating::autosizedReferenceSourceSideFlowRate() const {
  return getImpl<detail::HeatPumpWaterToWaterEquationFitHeating_Impl>()->autosizedReferenceSourceSideFlowRate();
}

boost::optional<double> HeatPumpWaterToWaterEquationFitHeating::autosizedRatedHeatingCapacity() const {
  return getImpl<detail::HeatPumpWaterToWaterEquationFitHeating_Impl>()->autosizedRatedHeatingCapacity();
}

boost::optional<double> HeatPumpWaterToWaterEquationFitHeating::autosizedRatedHeatingPowerConsumption() const {
  return getImpl<detail::HeatPumpWaterToWaterEquationFitHeating_Impl>()->autosizedRatedHeatingPowerConsumption();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

boost::optional<double> HeatPumpWaterToWaterEquationFitHeating_Impl::referenceLoadSideFlowRate() const {
  return getDouble(openstudio::HeatPump_WaterToWater_EquationFit_HeatingFields::ReferenceLoadSideFlowRate, true);
}

double HeatPumpWaterToWaterEquationFitHeating_Impl::ratedLoadSideFlowRate() const {
  if (auto value = referenceLoadSideFlowRate()) {
    return *value;
  }
  return -999.0;
}

bool HeatPumpWaterToWaterEquationFitHeating_Impl::isReferenceLoadSideFlowRateAutosized() const {
  if (auto value = getString(openstudio::HeatPump_WaterToWater_EquationFit_HeatingFields::ReferenceLoadSideFlowRate, true)) {
    return openstudio::istringEqual(*value, "Autosize");
  }
  return false;
}

boost::optional<double> HeatPumpWaterToWaterEquationFitHeating_Impl::referenceSourceSideFlowRate() const {
  return getDouble(openstudio::HeatPump_WaterToWater_EquationFit_HeatingFields::ReferenceSourceSideFlowRate, true);
}

double HeatPumpWaterToWaterEquationFitHeating_Impl::ratedSourceSideFlowRate() const {
  if (auto value = referenceSourceSideFlowRate()) {
    return *value;
  }
  return -999.0;
}

bool HeatPumpWaterToWaterEquationFitHeating_Impl::isReferenceSourceSideFlowRateAutosized() const {
  if (auto value = getString(openstudio::HeatPump_WaterToWater_EquationFit_HeatingFields::ReferenceSourceSideFlowRate, true)) {
    return openstudio::istringEqual(*value, "Autosize");
  }
  return false;
}

boost::optional<double> HeatPumpWaterToWaterEquationFitHeating_Impl::ratedHeatingCapacity() const {
  return getDouble(openstudio::HeatPump_WaterToWater_EquationFit_HeatingFields::ReferenceHeatingCapacity, true);
}

bool HeatPumpWaterToWaterEquationFitHeating_Impl::isRatedHeatingCapacityAutosized() const {
  if (auto value = getString(openstudio::HeatPump_WaterToWater_EquationFit_HeatingFields::ReferenceHeatingCapacity, true)) {
    return openstudio::istringEqual(*value, "Autosize");
  }
  return false;
}

boost::optional<double> HeatPumpWaterToWaterEquationFitHeating_Impl::ratedHeatingPowerConsumption() const {
  return getDouble(openstudio::HeatPump_WaterToWater_EquationFit_HeatingFields::ReferenceHeatingPowerConsumption, true);
}

bool HeatPumpWaterToWaterEquationFitHeating_Impl::isRatedHeatingPowerConsumptionAutosized() const {
  if (auto value = getString(openstudio::HeatPump_WaterToWater_EquationFit_HeatingFields::ReferenceHeatingPowerConsumption, true)) {
    return openstudio::istringEqual(*value, "Autosize");
  }
  return false;
}

double HeatPumpWaterToWaterEquationFitHeating_Impl::referenceCoefficientofPerformance() const {
  const auto value = getDouble(openstudio::HeatPump_WaterToWater_EquationFit_HeatingFields::ReferenceCoefficientofPerformance, true);
  OS_ASSERT(value);
  return *value;
}

double HeatPumpWaterToWaterEquationFitHeating_Impl::sizingFactor() const {
  const auto value = getDouble(openstudio::HeatPump_WaterToWater_EquationFit_HeatingFields::SizingFactor, true);
  OS_ASSERT(value);
  return *value;
}

bool HeatPumpWaterToWaterEquationFitHeating_Impl::setReferenceLoadSideFlowRate(double referenceLoadSideFlowRate) {
  return setDouble(openstudio::HeatPump_WaterToWater_EquationFit_HeatingFields::ReferenceLoadSideFlowRate, referenceLoadSideFlowRate);
}

bool HeatPumpWaterToWaterEquationFitHeating_Impl::setRatedLoadSideFlowRate(double ratedLoadSideFlowRate) {
  return setReferenceLoadSideFlowRate(ratedLoadSideFlowRate);
}

void HeatPumpWaterToWaterEquationFitHeating_Impl::autosizeReferenceLoadSideFlowRate() {
  const bool result = setString(openstudio::HeatPump_WaterToWater_EquationFit_HeatingFields::ReferenceLoadSideFlowRate, "Autosize");
  OS_ASSERT(result);
}

bool HeatPumpWaterToWaterEquationFitHeating_Impl::setReferenceSourceSideFlowRate(double referenceSourceSideFlowRate) {
  return setDouble(openstudio::HeatPump_WaterToWater_EquationFit_HeatingFields::ReferenceSourceSideFlowRate, referenceSourceSideFlowRate);
}

bool HeatPumpWaterToWaterEquationFitHeating_Impl::setRatedSourceSideFlowRate(double ratedSourceSideFlowRate) {
  return setReferenceSourceSideFlowRate(ratedSourceSideFlowRate);
}

void HeatPumpWaterToWaterEquationFitHeating_Impl::autosizeReferenceSourceSideFlowRate() {
  const bool result = setString(openstudio::HeatPump_WaterToWater_EquationFit_HeatingFields::ReferenceSourceSideFlowRate, "Autosize");
  OS_ASSERT(result);
}

bool HeatPumpWaterToWaterEquationFitHeating_Impl::setRatedHeatingCapacity(double ratedHeatingCapacity) {
  return setDouble(openstudio::HeatPump_WaterToWater_EquationFit_HeatingFields::ReferenceHeatingCapacity, ratedHeatingCapacity);
}

void HeatPumpWaterToWaterEquationFitHeating_Impl::autosizeRatedHeatingCapacity() {
  const bool result = setString(openstudio::HeatPump_WaterToWater_EquationFit_HeatingFields::ReferenceHeatingCapacity, "Autosize");
  OS_ASSERT(result);
}

bool HeatPumpWaterToWaterEquationFitHeating_Impl::setRatedHeatingPowerConsumption(double ratedHeatingPowerConsumption) {
  return setDouble(openstudio::HeatPump_WaterToWater_EquationFit_HeatingFields::ReferenceHeatingPowerConsumption, ratedHeatingPowerConsumption);
}

void HeatPumpWaterToWaterEquationFitHeating_Impl::autosizeRatedHeatingPowerConsumption() {
  const bool result =
    setString(openstudio::HeatPump_WaterToWater_EquationFit_HeatingFields::ReferenceHeatingPowerConsumption, "Autosize");
  OS_ASSERT(result);
}

bool HeatPumpWaterToWaterEquationFitHeating_Impl::setReferenceCoefficientofPerformance(double referenceCoefficientofPerformance) {
  const bool result =
    setDouble(openstudio::HeatPump_WaterToWater_EquationFit_HeatingFields::ReferenceCoefficientofPerformance, referenceCoefficientofPerformance);
  OS_ASSERT(result);
  return result;
}

bool HeatPumpWaterToWaterEquationFitHeating_Impl::setSizingFactor(double sizingFactor) {
  const bool result = setDouble(openstudio::HeatPump_WaterToWater_EquationFit_HeatingFields::SizingFactor, sizingFactor);
  OS_ASSERT(result);
  return result;
}

boost::optional<double> HeatPumpWaterToWaterEquationFitHeating_Impl::autosizedReferenceLoadSideFlowRate() const {
  // epmodel does not currently resolve autosized values from SQL results.
  return boost::none;
}

boost::optional<double> HeatPumpWaterToWaterEquationFitHeating_Impl::autosizedReferenceSourceSideFlowRate() const {
  // epmodel does not currently resolve autosized values from SQL results.
  return boost::none;
}

boost::optional<double> HeatPumpWaterToWaterEquationFitHeating_Impl::autosizedRatedHeatingCapacity() const {
  // epmodel does not currently resolve autosized values from SQL results.
  return boost::none;
}

boost::optional<double> HeatPumpWaterToWaterEquationFitHeating_Impl::autosizedRatedHeatingPowerConsumption() const {
  // epmodel does not currently resolve autosized values from SQL results.
  return boost::none;
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
