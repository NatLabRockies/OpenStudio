/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_PEOPLE_IMPL_HPP
#define EPMODEL_PEOPLE_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API People_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~People_Impl() override = default;

      std::string clothingInsulationCalculationMethod() const;
      bool setClothingInsulationCalculationMethod(const std::string& clothingInsulationCalculationMethod);
      std::vector<std::string> clothingInsulationCalculationMethodValues() const;

      double coldStressTemperatureThreshold() const;
      bool isColdStressTemperatureThresholdDefaulted() const;
      bool setColdStressTemperatureThreshold(double coldStressTemperatureThreshold);
      void resetColdStressTemperatureThreshold();

      double heatStressTemperatureThreshold() const;
      bool isHeatStressTemperatureThresholdDefaulted() const;
      bool setHeatStressTemperatureThreshold(double heatStressTemperatureThreshold);
      void resetHeatStressTemperatureThreshold();

      bool setMultiplier(double multiplier);
      void resetMultiplier();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
