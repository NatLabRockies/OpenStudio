/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "LayeredConstruction/ConstructionWithInternalSource.hpp"
#include "LayeredConstruction/ConstructionWithInternalSource_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/ConstructionProperty_InternalHeatSource_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

ConstructionWithInternalSource::ConstructionWithInternalSource(const Model& model)
  : ModelObject(ConstructionWithInternalSource::iddObjectType(), model) {}

ConstructionWithInternalSource::ConstructionWithInternalSource(std::shared_ptr<detail::ConstructionWithInternalSource_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType ConstructionWithInternalSource::iddObjectType() {
  return IddObjectType::ConstructionProperty_InternalHeatSource;
}

int ConstructionWithInternalSource::sourcePresentAfterLayerNumber() const {
  return getImpl<detail::ConstructionWithInternalSource_Impl>()->sourcePresentAfterLayerNumber();
}

bool ConstructionWithInternalSource::setSourcePresentAfterLayerNumber(int sourcePresentAfterLayerNumber) {
  return getImpl<detail::ConstructionWithInternalSource_Impl>()->setSourcePresentAfterLayerNumber(sourcePresentAfterLayerNumber);
}

int ConstructionWithInternalSource::temperatureCalculationRequestedAfterLayerNumber() const {
  return getImpl<detail::ConstructionWithInternalSource_Impl>()->temperatureCalculationRequestedAfterLayerNumber();
}

bool ConstructionWithInternalSource::setTemperatureCalculationRequestedAfterLayerNumber(int temperatureCalculationRequestedAfterLayerNumber) {
  return getImpl<detail::ConstructionWithInternalSource_Impl>()->setTemperatureCalculationRequestedAfterLayerNumber(
    temperatureCalculationRequestedAfterLayerNumber);
}

int ConstructionWithInternalSource::dimensionsForTheCTFCalculation() const {
  return getImpl<detail::ConstructionWithInternalSource_Impl>()->dimensionsForTheCTFCalculation();
}

bool ConstructionWithInternalSource::setDimensionsForTheCTFCalculation(int dimensionsForTheCTFCalculation) {
  return getImpl<detail::ConstructionWithInternalSource_Impl>()->setDimensionsForTheCTFCalculation(dimensionsForTheCTFCalculation);
}

double ConstructionWithInternalSource::tubeSpacing() const {
  return getImpl<detail::ConstructionWithInternalSource_Impl>()->tubeSpacing();
}

bool ConstructionWithInternalSource::setTubeSpacing(double tubeSpacing) {
  return getImpl<detail::ConstructionWithInternalSource_Impl>()->setTubeSpacing(tubeSpacing);
}

double ConstructionWithInternalSource::twoDimensionalTemperatureCalculationPosition() const {
  return getImpl<detail::ConstructionWithInternalSource_Impl>()->twoDimensionalTemperatureCalculationPosition();
}

bool ConstructionWithInternalSource::isTwoDimensionalTemperatureCalculationPositionDefaulted() const {
  return getImpl<detail::ConstructionWithInternalSource_Impl>()->isTwoDimensionalTemperatureCalculationPositionDefaulted();
}

bool ConstructionWithInternalSource::setTwoDimensionalTemperatureCalculationPosition(double twoDimensionalTemperatureCalculationPosition) {
  return getImpl<detail::ConstructionWithInternalSource_Impl>()->setTwoDimensionalTemperatureCalculationPosition(
    twoDimensionalTemperatureCalculationPosition);
}

void ConstructionWithInternalSource::resetTwoDimensionalTemperatureCalculationPosition() {
  getImpl<detail::ConstructionWithInternalSource_Impl>()->resetTwoDimensionalTemperatureCalculationPosition();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

int ConstructionWithInternalSource_Impl::sourcePresentAfterLayerNumber() const {
  const auto value = getInt(openstudio::ConstructionProperty_InternalHeatSourceFields::ThermalSourcePresentAfterLayerNumber, true);
  OS_ASSERT(value);
  return *value;
}

bool ConstructionWithInternalSource_Impl::setSourcePresentAfterLayerNumber(int sourcePresentAfterLayerNumber) {
  if (sourcePresentAfterLayerNumber < 1) {
    return false;
  }
  return setInt(openstudio::ConstructionProperty_InternalHeatSourceFields::ThermalSourcePresentAfterLayerNumber,
                sourcePresentAfterLayerNumber);
}

int ConstructionWithInternalSource_Impl::temperatureCalculationRequestedAfterLayerNumber() const {
  const auto value = getInt(openstudio::ConstructionProperty_InternalHeatSourceFields::TemperatureCalculationRequestedAfterLayerNumber, true);
  OS_ASSERT(value);
  return *value;
}

bool ConstructionWithInternalSource_Impl::setTemperatureCalculationRequestedAfterLayerNumber(int temperatureCalculationRequestedAfterLayerNumber) {
  if (temperatureCalculationRequestedAfterLayerNumber < 1) {
    return false;
  }
  return setInt(openstudio::ConstructionProperty_InternalHeatSourceFields::TemperatureCalculationRequestedAfterLayerNumber,
                temperatureCalculationRequestedAfterLayerNumber);
}

int ConstructionWithInternalSource_Impl::dimensionsForTheCTFCalculation() const {
  const auto value = getInt(openstudio::ConstructionProperty_InternalHeatSourceFields::DimensionsfortheCTFCalculation, true);
  OS_ASSERT(value);
  return *value;
}

bool ConstructionWithInternalSource_Impl::setDimensionsForTheCTFCalculation(int dimensionsForTheCTFCalculation) {
  if (dimensionsForTheCTFCalculation < 1 || dimensionsForTheCTFCalculation > 2) {
    return false;
  }
  return setInt(openstudio::ConstructionProperty_InternalHeatSourceFields::DimensionsfortheCTFCalculation, dimensionsForTheCTFCalculation);
}

double ConstructionWithInternalSource_Impl::tubeSpacing() const {
  const auto value = getDouble(openstudio::ConstructionProperty_InternalHeatSourceFields::TubeSpacing, true);
  OS_ASSERT(value);
  return *value;
}

bool ConstructionWithInternalSource_Impl::setTubeSpacing(double tubeSpacing) {
  if (tubeSpacing < 0.01 || tubeSpacing > 1.0) {
    return false;
  }
  return setDouble(openstudio::ConstructionProperty_InternalHeatSourceFields::TubeSpacing, tubeSpacing);
}

double ConstructionWithInternalSource_Impl::twoDimensionalTemperatureCalculationPosition() const {
  const auto value = getDouble(openstudio::ConstructionProperty_InternalHeatSourceFields::TwoDimensionalTemperatureCalculationPosition, true);
  OS_ASSERT(value);
  return *value;
}

bool ConstructionWithInternalSource_Impl::isTwoDimensionalTemperatureCalculationPositionDefaulted() const {
  return !getDouble(openstudio::ConstructionProperty_InternalHeatSourceFields::TwoDimensionalTemperatureCalculationPosition, false);
}

bool ConstructionWithInternalSource_Impl::setTwoDimensionalTemperatureCalculationPosition(double twoDimensionalTemperatureCalculationPosition) {
  if (twoDimensionalTemperatureCalculationPosition < 0.0 || twoDimensionalTemperatureCalculationPosition > 1.0) {
    return false;
  }
  return setDouble(openstudio::ConstructionProperty_InternalHeatSourceFields::TwoDimensionalTemperatureCalculationPosition,
                   twoDimensionalTemperatureCalculationPosition);
}

void ConstructionWithInternalSource_Impl::resetTwoDimensionalTemperatureCalculationPosition() {
  OS_ASSERT(setString(openstudio::ConstructionProperty_InternalHeatSourceFields::TwoDimensionalTemperatureCalculationPosition, ""));
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
