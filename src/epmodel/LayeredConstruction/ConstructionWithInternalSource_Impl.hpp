/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CONSTRUCTIONWITHINTERNALSOURCE_IMPL_HPP
#define EPMODEL_CONSTRUCTIONWITHINTERNALSOURCE_IMPL_HPP

#include "LayeredConstruction/LayeredConstruction_Impl.hpp"

namespace openstudio {
namespace epmodel {
  namespace detail {

    class EPMODEL_API ConstructionWithInternalSource_Impl : public LayeredConstruction_Impl
    {
     public:
      using LayeredConstruction_Impl::LayeredConstruction_Impl;
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
      bool setTwoDimensionalTemperatureCalculationPosition(double twoDimensionalTemperatureCalculationPosition);
      bool isTwoDimensionalTemperatureCalculationPositionDefaulted() const;
      void resetTwoDimensionalTemperatureCalculationPosition();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
