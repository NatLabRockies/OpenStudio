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
    : LayeredConstruction(ConstructionWithInternalSource::iddObjectType(), model) {}

  ConstructionWithInternalSource::ConstructionWithInternalSource(std::shared_ptr<detail::ConstructionWithInternalSource_Impl> impl)
    : LayeredConstruction(std::move(impl)) {}

  IddObjectType ConstructionWithInternalSource::iddObjectType() {
    return IddObjectType::ConstructionProperty_InternalHeatSource;
  }

  // Source present after layer number accessors
  int ConstructionWithInternalSource::sourcePresentAfterLayerNumber() const {
    return getImpl<detail::ConstructionWithInternalSource_Impl>()->sourcePresentAfterLayerNumber();
  }

  bool ConstructionWithInternalSource::setSourcePresentAfterLayerNumber(int sourcePresentAfterLayerNumber) {
    return getImpl<detail::ConstructionWithInternalSource_Impl>()->setSourcePresentAfterLayerNumber(sourcePresentAfterLayerNumber);
  }

  // Temperature calculation requested after layer number accessors
  int ConstructionWithInternalSource::temperatureCalculationRequestedAfterLayerNumber() const {
    return getImpl<detail::ConstructionWithInternalSource_Impl>()->temperatureCalculationRequestedAfterLayerNumber();
  }

  bool ConstructionWithInternalSource::setTemperatureCalculationRequestedAfterLayerNumber(int temperatureCalculationRequestedAfterLayerNumber) {
    return getImpl<detail::ConstructionWithInternalSource_Impl>()->setTemperatureCalculationRequestedAfterLayerNumber(
      temperatureCalculationRequestedAfterLayerNumber);
  }

  // Dimensions for the CTF calculation accessors
  int ConstructionWithInternalSource::dimensionsForTheCTFCalculation() const {
    return getImpl<detail::ConstructionWithInternalSource_Impl>()->dimensionsForTheCTFCalculation();
  }

  bool ConstructionWithInternalSource::setDimensionsForTheCTFCalculation(int dimensionsForTheCTFCalculation) {
    return getImpl<detail::ConstructionWithInternalSource_Impl>()->setDimensionsForTheCTFCalculation(dimensionsForTheCTFCalculation);
  }

  // Tube spacing accessors
  double ConstructionWithInternalSource::tubeSpacing() const {
    return getImpl<detail::ConstructionWithInternalSource_Impl>()->tubeSpacing();
  }

  bool ConstructionWithInternalSource::setTubeSpacing(double tubeSpacing) {
    return getImpl<detail::ConstructionWithInternalSource_Impl>()->setTubeSpacing(tubeSpacing);
  }

  // Two-dimensional temperature calculation position accessors
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

    // Source present after layer number accessors
    int ConstructionWithInternalSource_Impl::sourcePresentAfterLayerNumber() const {
      const auto value = getInt(openstudio::ConstructionProperty_InternalHeatSourceFields::ThermalSourcePresentAfterLayerNumber, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ConstructionWithInternalSource_Impl::setSourcePresentAfterLayerNumber(int sourcePresentAfterLayerNumber) {
      if (sourcePresentAfterLayerNumber < 1) {
        return false;
      }
      return setInt(openstudio::ConstructionProperty_InternalHeatSourceFields::ThermalSourcePresentAfterLayerNumber, sourcePresentAfterLayerNumber);
    }

    // Temperature calculation requested after layer number accessors
    int ConstructionWithInternalSource_Impl::temperatureCalculationRequestedAfterLayerNumber() const {
      const auto value = getInt(openstudio::ConstructionProperty_InternalHeatSourceFields::TemperatureCalculationRequestedAfterLayerNumber, true);
      OS_ASSERT(value);
      return *value;
    }

    bool
      ConstructionWithInternalSource_Impl::setTemperatureCalculationRequestedAfterLayerNumber(int temperatureCalculationRequestedAfterLayerNumber) {
      if (temperatureCalculationRequestedAfterLayerNumber < 1) {
        return false;
      }
      return setInt(openstudio::ConstructionProperty_InternalHeatSourceFields::TemperatureCalculationRequestedAfterLayerNumber,
                    temperatureCalculationRequestedAfterLayerNumber);
    }

    // Dimensions for the CTF calculation accessors
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

    // Tube spacing accessors
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

    // Two-dimensional temperature calculation position accessors
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
