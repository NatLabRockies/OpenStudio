/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SHADOWCALCULATION_IMPL_HPP
#define EPMODEL_SHADOWCALCULATION_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {
  namespace detail {

    class EPMODEL_API ShadowCalculation_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~ShadowCalculation_Impl() override = default;

      std::vector<std::string> shadingCalculationMethodValues() const;
      std::vector<std::string> validShadingCalculationMethodValues() const;

      std::vector<std::string> shadingCalculationUpdateFrequencyMethodValues() const;
      std::vector<std::string> validShadingCalculationUpdateFrequencyMethodValues() const;

      std::vector<std::string> polygonClippingAlgorithmValues() const;
      std::vector<std::string> validPolygonClippingAlgorithmValues() const;

      std::vector<std::string> skyDiffuseModelingAlgorithmValues() const;
      std::vector<std::string> validSkyDiffuseModelingAlgorithmValues() const;

      std::string shadingCalculationMethod() const;
      bool setShadingCalculationMethod(const std::string& shadingCalculationMethod);

      std::string shadingCalculationUpdateFrequencyMethod() const;
      bool isShadingCalculationUpdateFrequencyMethodDefaulted() const;
      bool setShadingCalculationUpdateFrequencyMethod(const std::string& shadingCalculationUpdateFrequencyMethod);
      void resetShadingCalculationUpdateFrequencyMethod();

      int shadingCalculationUpdateFrequency() const;
      bool isShadingCalculationUpdateFrequencyDefaulted() const;
      bool setShadingCalculationUpdateFrequency(int shadingCalculationUpdateFrequency);
      void resetShadingCalculationUpdateFrequency();

      int maximumFiguresInShadowOverlapCalculations() const;
      bool isMaximumFiguresInShadowOverlapCalculationsDefaulted() const;
      bool setMaximumFiguresInShadowOverlapCalculations(int maximumFiguresInShadowOverlapCalculations);
      void resetMaximumFiguresInShadowOverlapCalculations();

      std::string polygonClippingAlgorithm() const;
      bool setPolygonClippingAlgorithm(const std::string& polygonClippingAlgorithm);
      void resetPolygonClippingAlgorithm();

      int pixelCountingResolution() const;
      bool setPixelCountingResolution(int pixelCountingResolution);

      std::string skyDiffuseModelingAlgorithm() const;
      bool setSkyDiffuseModelingAlgorithm(const std::string& skyDiffuseModelingAlgorithm);
      void resetSkyDiffuseModelingAlgorithm();

      bool outputExternalShadingCalculationResults() const;
      bool setOutputExternalShadingCalculationResults(bool outputExternalShadingCalculationResults);

      bool disableSelfShadingWithinShadingZoneGroups() const;
      bool setDisableSelfShadingWithinShadingZoneGroups(bool disableSelfShadingWithinShadingZoneGroups);

      bool disableSelfShadingFromShadingZoneGroupstoOtherZones() const;
      bool setDisableSelfShadingFromShadingZoneGroupstoOtherZones(bool disableSelfShadingFromShadingZoneGroupstoOtherZones);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
