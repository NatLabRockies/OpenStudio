/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CONSTRUCTIONWITHINTERNALSOURCE_IMPL_HPP
#define EPMODEL_CONSTRUCTIONWITHINTERNALSOURCE_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {
namespace detail {

class EPMODEL_API ConstructionWithInternalSource_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~ConstructionWithInternalSource_Impl() override = default;

  int sourcePresentAfterLayerNumber() const;
  bool setSourcePresentAfterLayerNumber(int sourcePresentAfterLayerNumber);

  int temperatureCalculationRequestedAfterLayerNumber() const;
  bool setTemperatureCalculationRequestedAfterLayerNumber(int temperatureCalculationRequestedAfterLayerNumber);

  int dimensionsForTheCTFCalculation() const;
  bool setDimensionsForTheCTFCalculation(int dimensionsForTheCTFCalculation);

  double tubeSpacing() const;
  bool setTubeSpacing(double tubeSpacing);

  double twoDimensionalTemperatureCalculationPosition() const;
  bool isTwoDimensionalTemperatureCalculationPositionDefaulted() const;
  bool setTwoDimensionalTemperatureCalculationPosition(double twoDimensionalTemperatureCalculationPosition);
  void resetTwoDimensionalTemperatureCalculationPosition();
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
