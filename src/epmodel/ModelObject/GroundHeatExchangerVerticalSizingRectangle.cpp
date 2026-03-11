/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "GroundHeatExchangerVerticalSizingRectangle.hpp"
#include "GroundHeatExchangerVerticalSizingRectangle_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/GroundHeatExchanger_Vertical_Sizing_Rectangle_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

GroundHeatExchangerVerticalSizingRectangle::GroundHeatExchangerVerticalSizingRectangle(const Model& model)
  : ModelObject(GroundHeatExchangerVerticalSizingRectangle::iddObjectType(), model) {
  bool ok = true;
  ok = setAvailableBoreholeFieldLength(100.0);
  OS_ASSERT(ok);
  ok = setAvailableBoreholeFieldWidth(100.0);
  OS_ASSERT(ok);
  ok = setMaximumNumberofBoreholes(100.0);
  OS_ASSERT(ok);
}

GroundHeatExchangerVerticalSizingRectangle::GroundHeatExchangerVerticalSizingRectangle(
  std::shared_ptr<detail::GroundHeatExchangerVerticalSizingRectangle_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType GroundHeatExchangerVerticalSizingRectangle::iddObjectType() {
  return IddObjectType::GroundHeatExchanger_Vertical_Sizing_Rectangle;
}

double GroundHeatExchangerVerticalSizingRectangle::designFlowRatePerBorehole() const {
  return getImpl<detail::GroundHeatExchangerVerticalSizingRectangle_Impl>()->designFlowRatePerBorehole();
}

double GroundHeatExchangerVerticalSizingRectangle::availableBoreholeFieldLength() const {
  return getImpl<detail::GroundHeatExchangerVerticalSizingRectangle_Impl>()->availableBoreholeFieldLength();
}

double GroundHeatExchangerVerticalSizingRectangle::availableBoreholeFieldWidth() const {
  return getImpl<detail::GroundHeatExchangerVerticalSizingRectangle_Impl>()->availableBoreholeFieldWidth();
}

double GroundHeatExchangerVerticalSizingRectangle::maximumNumberofBoreholes() const {
  return getImpl<detail::GroundHeatExchangerVerticalSizingRectangle_Impl>()->maximumNumberofBoreholes();
}

double GroundHeatExchangerVerticalSizingRectangle::minimumBoreholeSpacing() const {
  return getImpl<detail::GroundHeatExchangerVerticalSizingRectangle_Impl>()->minimumBoreholeSpacing();
}

double GroundHeatExchangerVerticalSizingRectangle::maximumBoreholeSpacing() const {
  return getImpl<detail::GroundHeatExchangerVerticalSizingRectangle_Impl>()->maximumBoreholeSpacing();
}

double GroundHeatExchangerVerticalSizingRectangle::minimumBoreholeVerticalLength() const {
  return getImpl<detail::GroundHeatExchangerVerticalSizingRectangle_Impl>()->minimumBoreholeVerticalLength();
}

double GroundHeatExchangerVerticalSizingRectangle::maximumBoreholeVerticalLength() const {
  return getImpl<detail::GroundHeatExchangerVerticalSizingRectangle_Impl>()->maximumBoreholeVerticalLength();
}

double GroundHeatExchangerVerticalSizingRectangle::minimumExitingFluidTemperatureforSizing() const {
  return getImpl<detail::GroundHeatExchangerVerticalSizingRectangle_Impl>()->minimumExitingFluidTemperatureforSizing();
}

double GroundHeatExchangerVerticalSizingRectangle::maximumExitingFluidTemperatureforSizing() const {
  return getImpl<detail::GroundHeatExchangerVerticalSizingRectangle_Impl>()->maximumExitingFluidTemperatureforSizing();
}

bool GroundHeatExchangerVerticalSizingRectangle::isDesignFlowRatePerBoreholeDefaulted() const {
  return getImpl<detail::GroundHeatExchangerVerticalSizingRectangle_Impl>()->isDesignFlowRatePerBoreholeDefaulted();
}

bool GroundHeatExchangerVerticalSizingRectangle::isMinimumBoreholeSpacingDefaulted() const {
  return getImpl<detail::GroundHeatExchangerVerticalSizingRectangle_Impl>()->isMinimumBoreholeSpacingDefaulted();
}

bool GroundHeatExchangerVerticalSizingRectangle::isMaximumBoreholeSpacingDefaulted() const {
  return getImpl<detail::GroundHeatExchangerVerticalSizingRectangle_Impl>()->isMaximumBoreholeSpacingDefaulted();
}

bool GroundHeatExchangerVerticalSizingRectangle::isMinimumBoreholeVerticalLengthDefaulted() const {
  return getImpl<detail::GroundHeatExchangerVerticalSizingRectangle_Impl>()->isMinimumBoreholeVerticalLengthDefaulted();
}

bool GroundHeatExchangerVerticalSizingRectangle::isMaximumBoreholeVerticalLengthDefaulted() const {
  return getImpl<detail::GroundHeatExchangerVerticalSizingRectangle_Impl>()->isMaximumBoreholeVerticalLengthDefaulted();
}

bool GroundHeatExchangerVerticalSizingRectangle::isMinimumExitingFluidTemperatureforSizingDefaulted() const {
  return getImpl<detail::GroundHeatExchangerVerticalSizingRectangle_Impl>()->isMinimumExitingFluidTemperatureforSizingDefaulted();
}

bool GroundHeatExchangerVerticalSizingRectangle::isMaximumExitingFluidTemperatureforSizingDefaulted() const {
  return getImpl<detail::GroundHeatExchangerVerticalSizingRectangle_Impl>()->isMaximumExitingFluidTemperatureforSizingDefaulted();
}

bool GroundHeatExchangerVerticalSizingRectangle::setDesignFlowRatePerBorehole(double designFlowRatePerBorehole) {
  return getImpl<detail::GroundHeatExchangerVerticalSizingRectangle_Impl>()->setDesignFlowRatePerBorehole(designFlowRatePerBorehole);
}

bool GroundHeatExchangerVerticalSizingRectangle::setAvailableBoreholeFieldLength(double availableBoreholeFieldLength) {
  return getImpl<detail::GroundHeatExchangerVerticalSizingRectangle_Impl>()->setAvailableBoreholeFieldLength(availableBoreholeFieldLength);
}

bool GroundHeatExchangerVerticalSizingRectangle::setAvailableBoreholeFieldWidth(double availableBoreholeFieldWidth) {
  return getImpl<detail::GroundHeatExchangerVerticalSizingRectangle_Impl>()->setAvailableBoreholeFieldWidth(availableBoreholeFieldWidth);
}

bool GroundHeatExchangerVerticalSizingRectangle::setMaximumNumberofBoreholes(double maximumNumberofBoreholes) {
  return getImpl<detail::GroundHeatExchangerVerticalSizingRectangle_Impl>()->setMaximumNumberofBoreholes(maximumNumberofBoreholes);
}

bool GroundHeatExchangerVerticalSizingRectangle::setMinimumBoreholeSpacing(double minimumBoreholeSpacing) {
  return getImpl<detail::GroundHeatExchangerVerticalSizingRectangle_Impl>()->setMinimumBoreholeSpacing(minimumBoreholeSpacing);
}

bool GroundHeatExchangerVerticalSizingRectangle::setMaximumBoreholeSpacing(double maximumBoreholeSpacing) {
  return getImpl<detail::GroundHeatExchangerVerticalSizingRectangle_Impl>()->setMaximumBoreholeSpacing(maximumBoreholeSpacing);
}

bool GroundHeatExchangerVerticalSizingRectangle::setMinimumBoreholeVerticalLength(double minimumBoreholeVerticalLength) {
  return getImpl<detail::GroundHeatExchangerVerticalSizingRectangle_Impl>()->setMinimumBoreholeVerticalLength(minimumBoreholeVerticalLength);
}

bool GroundHeatExchangerVerticalSizingRectangle::setMaximumBoreholeVerticalLength(double maximumBoreholeVerticalLength) {
  return getImpl<detail::GroundHeatExchangerVerticalSizingRectangle_Impl>()->setMaximumBoreholeVerticalLength(maximumBoreholeVerticalLength);
}

bool GroundHeatExchangerVerticalSizingRectangle::setMinimumExitingFluidTemperatureforSizing(double minimumExitingFluidTemperatureforSizing) {
  return getImpl<detail::GroundHeatExchangerVerticalSizingRectangle_Impl>()->setMinimumExitingFluidTemperatureforSizing(
    minimumExitingFluidTemperatureforSizing);
}

bool GroundHeatExchangerVerticalSizingRectangle::setMaximumExitingFluidTemperatureforSizing(double maximumExitingFluidTemperatureforSizing) {
  return getImpl<detail::GroundHeatExchangerVerticalSizingRectangle_Impl>()->setMaximumExitingFluidTemperatureforSizing(
    maximumExitingFluidTemperatureforSizing);
}

void GroundHeatExchangerVerticalSizingRectangle::resetDesignFlowRatePerBorehole() {
  getImpl<detail::GroundHeatExchangerVerticalSizingRectangle_Impl>()->resetDesignFlowRatePerBorehole();
}

void GroundHeatExchangerVerticalSizingRectangle::resetMinimumBoreholeSpacing() {
  getImpl<detail::GroundHeatExchangerVerticalSizingRectangle_Impl>()->resetMinimumBoreholeSpacing();
}

void GroundHeatExchangerVerticalSizingRectangle::resetMaximumBoreholeSpacing() {
  getImpl<detail::GroundHeatExchangerVerticalSizingRectangle_Impl>()->resetMaximumBoreholeSpacing();
}

void GroundHeatExchangerVerticalSizingRectangle::resetMinimumBoreholeVerticalLength() {
  getImpl<detail::GroundHeatExchangerVerticalSizingRectangle_Impl>()->resetMinimumBoreholeVerticalLength();
}

void GroundHeatExchangerVerticalSizingRectangle::resetMaximumBoreholeVerticalLength() {
  getImpl<detail::GroundHeatExchangerVerticalSizingRectangle_Impl>()->resetMaximumBoreholeVerticalLength();
}

void GroundHeatExchangerVerticalSizingRectangle::resetMinimumExitingFluidTemperatureforSizing() {
  getImpl<detail::GroundHeatExchangerVerticalSizingRectangle_Impl>()->resetMinimumExitingFluidTemperatureforSizing();
}

void GroundHeatExchangerVerticalSizingRectangle::resetMaximumExitingFluidTemperatureforSizing() {
  getImpl<detail::GroundHeatExchangerVerticalSizingRectangle_Impl>()->resetMaximumExitingFluidTemperatureforSizing();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

double GroundHeatExchangerVerticalSizingRectangle_Impl::designFlowRatePerBorehole() const {
  const auto value = getDouble(openstudio::GroundHeatExchanger_Vertical_Sizing_RectangleFields::DesignFlowRatePerBorehole, true);
  OS_ASSERT(value);
  return *value;
}

double GroundHeatExchangerVerticalSizingRectangle_Impl::availableBoreholeFieldLength() const {
  const auto value = getDouble(openstudio::GroundHeatExchanger_Vertical_Sizing_RectangleFields::AvailableBoreholeFieldLength, true);
  OS_ASSERT(value);
  return *value;
}

double GroundHeatExchangerVerticalSizingRectangle_Impl::availableBoreholeFieldWidth() const {
  const auto value = getDouble(openstudio::GroundHeatExchanger_Vertical_Sizing_RectangleFields::AvailableBoreholeFieldWidth, true);
  OS_ASSERT(value);
  return *value;
}

double GroundHeatExchangerVerticalSizingRectangle_Impl::maximumNumberofBoreholes() const {
  const auto value = getDouble(openstudio::GroundHeatExchanger_Vertical_Sizing_RectangleFields::MaximumNumberofBoreholes, true);
  OS_ASSERT(value);
  return *value;
}

double GroundHeatExchangerVerticalSizingRectangle_Impl::minimumBoreholeSpacing() const {
  const auto value = getDouble(openstudio::GroundHeatExchanger_Vertical_Sizing_RectangleFields::MinimumBoreholeSpacing, true);
  OS_ASSERT(value);
  return *value;
}

double GroundHeatExchangerVerticalSizingRectangle_Impl::maximumBoreholeSpacing() const {
  const auto value = getDouble(openstudio::GroundHeatExchanger_Vertical_Sizing_RectangleFields::MaximumBoreholeSpacing, true);
  OS_ASSERT(value);
  return *value;
}

double GroundHeatExchangerVerticalSizingRectangle_Impl::minimumBoreholeVerticalLength() const {
  const auto value = getDouble(openstudio::GroundHeatExchanger_Vertical_Sizing_RectangleFields::MinimumBoreholeVerticalLength, true);
  OS_ASSERT(value);
  return *value;
}

double GroundHeatExchangerVerticalSizingRectangle_Impl::maximumBoreholeVerticalLength() const {
  const auto value = getDouble(openstudio::GroundHeatExchanger_Vertical_Sizing_RectangleFields::MaximumBoreholeVerticalLength, true);
  OS_ASSERT(value);
  return *value;
}

double GroundHeatExchangerVerticalSizingRectangle_Impl::minimumExitingFluidTemperatureforSizing() const {
  const auto value = getDouble(openstudio::GroundHeatExchanger_Vertical_Sizing_RectangleFields::MinimumExitingFluidTemperatureforSizing, true);
  OS_ASSERT(value);
  return *value;
}

double GroundHeatExchangerVerticalSizingRectangle_Impl::maximumExitingFluidTemperatureforSizing() const {
  const auto value = getDouble(openstudio::GroundHeatExchanger_Vertical_Sizing_RectangleFields::MaximumExitingFluidTemperatureforSizing, true);
  OS_ASSERT(value);
  return *value;
}

bool GroundHeatExchangerVerticalSizingRectangle_Impl::isDesignFlowRatePerBoreholeDefaulted() const {
  return isEmpty(openstudio::GroundHeatExchanger_Vertical_Sizing_RectangleFields::DesignFlowRatePerBorehole);
}

bool GroundHeatExchangerVerticalSizingRectangle_Impl::isMinimumBoreholeSpacingDefaulted() const {
  return isEmpty(openstudio::GroundHeatExchanger_Vertical_Sizing_RectangleFields::MinimumBoreholeSpacing);
}

bool GroundHeatExchangerVerticalSizingRectangle_Impl::isMaximumBoreholeSpacingDefaulted() const {
  return isEmpty(openstudio::GroundHeatExchanger_Vertical_Sizing_RectangleFields::MaximumBoreholeSpacing);
}

bool GroundHeatExchangerVerticalSizingRectangle_Impl::isMinimumBoreholeVerticalLengthDefaulted() const {
  return isEmpty(openstudio::GroundHeatExchanger_Vertical_Sizing_RectangleFields::MinimumBoreholeVerticalLength);
}

bool GroundHeatExchangerVerticalSizingRectangle_Impl::isMaximumBoreholeVerticalLengthDefaulted() const {
  return isEmpty(openstudio::GroundHeatExchanger_Vertical_Sizing_RectangleFields::MaximumBoreholeVerticalLength);
}

bool GroundHeatExchangerVerticalSizingRectangle_Impl::isMinimumExitingFluidTemperatureforSizingDefaulted() const {
  return isEmpty(openstudio::GroundHeatExchanger_Vertical_Sizing_RectangleFields::MinimumExitingFluidTemperatureforSizing);
}

bool GroundHeatExchangerVerticalSizingRectangle_Impl::isMaximumExitingFluidTemperatureforSizingDefaulted() const {
  return isEmpty(openstudio::GroundHeatExchanger_Vertical_Sizing_RectangleFields::MaximumExitingFluidTemperatureforSizing);
}

bool GroundHeatExchangerVerticalSizingRectangle_Impl::setDesignFlowRatePerBorehole(double designFlowRatePerBorehole) {
  return setDouble(openstudio::GroundHeatExchanger_Vertical_Sizing_RectangleFields::DesignFlowRatePerBorehole, designFlowRatePerBorehole);
}

bool GroundHeatExchangerVerticalSizingRectangle_Impl::setAvailableBoreholeFieldLength(double availableBoreholeFieldLength) {
  return setDouble(openstudio::GroundHeatExchanger_Vertical_Sizing_RectangleFields::AvailableBoreholeFieldLength, availableBoreholeFieldLength);
}

bool GroundHeatExchangerVerticalSizingRectangle_Impl::setAvailableBoreholeFieldWidth(double availableBoreholeFieldWidth) {
  return setDouble(openstudio::GroundHeatExchanger_Vertical_Sizing_RectangleFields::AvailableBoreholeFieldWidth, availableBoreholeFieldWidth);
}

bool GroundHeatExchangerVerticalSizingRectangle_Impl::setMaximumNumberofBoreholes(double maximumNumberofBoreholes) {
  return setDouble(openstudio::GroundHeatExchanger_Vertical_Sizing_RectangleFields::MaximumNumberofBoreholes, maximumNumberofBoreholes);
}

bool GroundHeatExchangerVerticalSizingRectangle_Impl::setMinimumBoreholeSpacing(double minimumBoreholeSpacing) {
  return setDouble(openstudio::GroundHeatExchanger_Vertical_Sizing_RectangleFields::MinimumBoreholeSpacing, minimumBoreholeSpacing);
}

bool GroundHeatExchangerVerticalSizingRectangle_Impl::setMaximumBoreholeSpacing(double maximumBoreholeSpacing) {
  return setDouble(openstudio::GroundHeatExchanger_Vertical_Sizing_RectangleFields::MaximumBoreholeSpacing, maximumBoreholeSpacing);
}

bool GroundHeatExchangerVerticalSizingRectangle_Impl::setMinimumBoreholeVerticalLength(double minimumBoreholeVerticalLength) {
  return setDouble(openstudio::GroundHeatExchanger_Vertical_Sizing_RectangleFields::MinimumBoreholeVerticalLength, minimumBoreholeVerticalLength);
}

bool GroundHeatExchangerVerticalSizingRectangle_Impl::setMaximumBoreholeVerticalLength(double maximumBoreholeVerticalLength) {
  return setDouble(openstudio::GroundHeatExchanger_Vertical_Sizing_RectangleFields::MaximumBoreholeVerticalLength, maximumBoreholeVerticalLength);
}

bool GroundHeatExchangerVerticalSizingRectangle_Impl::setMinimumExitingFluidTemperatureforSizing(double minimumExitingFluidTemperatureforSizing) {
  return setDouble(openstudio::GroundHeatExchanger_Vertical_Sizing_RectangleFields::MinimumExitingFluidTemperatureforSizing,
                   minimumExitingFluidTemperatureforSizing);
}

bool GroundHeatExchangerVerticalSizingRectangle_Impl::setMaximumExitingFluidTemperatureforSizing(double maximumExitingFluidTemperatureforSizing) {
  return setDouble(openstudio::GroundHeatExchanger_Vertical_Sizing_RectangleFields::MaximumExitingFluidTemperatureforSizing,
                   maximumExitingFluidTemperatureforSizing);
}

void GroundHeatExchangerVerticalSizingRectangle_Impl::resetDesignFlowRatePerBorehole() {
  OS_ASSERT(setString(openstudio::GroundHeatExchanger_Vertical_Sizing_RectangleFields::DesignFlowRatePerBorehole, ""));
}

void GroundHeatExchangerVerticalSizingRectangle_Impl::resetMinimumBoreholeSpacing() {
  OS_ASSERT(setString(openstudio::GroundHeatExchanger_Vertical_Sizing_RectangleFields::MinimumBoreholeSpacing, ""));
}

void GroundHeatExchangerVerticalSizingRectangle_Impl::resetMaximumBoreholeSpacing() {
  OS_ASSERT(setString(openstudio::GroundHeatExchanger_Vertical_Sizing_RectangleFields::MaximumBoreholeSpacing, ""));
}

void GroundHeatExchangerVerticalSizingRectangle_Impl::resetMinimumBoreholeVerticalLength() {
  OS_ASSERT(setString(openstudio::GroundHeatExchanger_Vertical_Sizing_RectangleFields::MinimumBoreholeVerticalLength, ""));
}

void GroundHeatExchangerVerticalSizingRectangle_Impl::resetMaximumBoreholeVerticalLength() {
  OS_ASSERT(setString(openstudio::GroundHeatExchanger_Vertical_Sizing_RectangleFields::MaximumBoreholeVerticalLength, ""));
}

void GroundHeatExchangerVerticalSizingRectangle_Impl::resetMinimumExitingFluidTemperatureforSizing() {
  OS_ASSERT(setString(openstudio::GroundHeatExchanger_Vertical_Sizing_RectangleFields::MinimumExitingFluidTemperatureforSizing, ""));
}

void GroundHeatExchangerVerticalSizingRectangle_Impl::resetMaximumExitingFluidTemperatureforSizing() {
  OS_ASSERT(setString(openstudio::GroundHeatExchanger_Vertical_Sizing_RectangleFields::MaximumExitingFluidTemperatureforSizing, ""));
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
