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

  std::string shadingCalculationMethod() const;

  std::string shadingCalculationUpdateFrequencyMethod() const;
  bool isShadingCalculationUpdateFrequencyMethodDefaulted() const;

  int shadingCalculationUpdateFrequency() const;
  bool isShadingCalculationUpdateFrequencyDefaulted() const;

  int maximumFiguresInShadowOverlapCalculations() const;
  bool isMaximumFiguresInShadowOverlapCalculationsDefaulted() const;

  std::string polygonClippingAlgorithm() const;

  int pixelCountingResolution() const;

  std::string skyDiffuseModelingAlgorithm() const;

  bool outputExternalShadingCalculationResults() const;

  bool disableSelfShadingWithinShadingZoneGroups() const;

  bool disableSelfShadingFromShadingZoneGroupstoOtherZones() const;

  bool setShadingCalculationMethod(const std::string& shadingCalculationMethod);

  bool setShadingCalculationUpdateFrequencyMethod(const std::string& shadingCalculationUpdateFrequencyMethod);
  void resetShadingCalculationUpdateFrequencyMethod();

  bool setShadingCalculationUpdateFrequency(int shadingCalculationUpdateFrequency);
  void resetShadingCalculationUpdateFrequency();

  bool setMaximumFiguresInShadowOverlapCalculations(int maximumFiguresInShadowOverlapCalculations);
  void resetMaximumFiguresInShadowOverlapCalculations();

  bool setPolygonClippingAlgorithm(const std::string& polygonClippingAlgorithm);
  void resetPolygonClippingAlgorithm();

  bool setPixelCountingResolution(int pixelCountingResolution);

  bool setSkyDiffuseModelingAlgorithm(const std::string& skyDiffuseModelingAlgorithm);
  void resetSkyDiffuseModelingAlgorithm();

  bool setOutputExternalShadingCalculationResults(bool outputExternalShadingCalculationResults);

  bool setDisableSelfShadingWithinShadingZoneGroups(bool disableSelfShadingWithinShadingZoneGroups);

  bool setDisableSelfShadingFromShadingZoneGroupstoOtherZones(bool disableSelfShadingFromShadingZoneGroupstoOtherZones);

  std::vector<std::string> shadingCalculationMethodValues() const;
  std::vector<std::string> validShadingCalculationMethodValues() const;

  std::vector<std::string> shadingCalculationUpdateFrequencyMethodValues() const;
  std::vector<std::string> validShadingCalculationUpdateFrequencyMethodValues() const;

  std::vector<std::string> polygonClippingAlgorithmValues() const;
  std::vector<std::string> validPolygonClippingAlgorithmValues() const;

  std::vector<std::string> skyDiffuseModelingAlgorithmValues() const;
  std::vector<std::string> validSkyDiffuseModelingAlgorithmValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
