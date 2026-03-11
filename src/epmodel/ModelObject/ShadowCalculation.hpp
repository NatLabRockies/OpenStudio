/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SHADOWCALCULATION_HPP
#define EPMODEL_SHADOWCALCULATION_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class ShadowCalculation_Impl;
}

class EPMODEL_API ShadowCalculation : public ModelObject
{
 public:
  explicit ShadowCalculation(const Model& model);

  virtual ~ShadowCalculation() override = default;
  ShadowCalculation(const ShadowCalculation& other) = default;
  ShadowCalculation(ShadowCalculation&& other) = default;
  ShadowCalculation& operator=(const ShadowCalculation&) = default;
  ShadowCalculation& operator=(ShadowCalculation&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> shadingCalculationMethodValues();
  static std::vector<std::string> validShadingCalculationMethodValues();

  static std::vector<std::string> shadingCalculationUpdateFrequencyMethodValues();
  static std::vector<std::string> validShadingCalculationUpdateFrequencyMethodValues();

  static std::vector<std::string> polygonClippingAlgorithmValues();
  static std::vector<std::string> validPolygonClippingAlgorithmValues();

  static std::vector<std::string> skyDiffuseModelingAlgorithmValues();
  static std::vector<std::string> validSkyDiffuseModelingAlgorithmValues();

  // Schema Alignment Notes:
  // - API: Preserve openstudio::model ShadowCalculation scalar accessor names/signatures, including legacy casing/wording.
  // - Field Mapping: Scalar APIs below map directly to EnergyPlus ShadowCalculation fields with matching semantics.
  // - ForwardTranslator Evidence: ForwardTranslateShadowCalculation.cpp writes these preserved APIs to the same E+ fields.
  // - TODO(parity): Keep shading-zone-group extensible relationship APIs out of this scalar-only scaffold pass.
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

 protected:
  using ImplType = detail::ShadowCalculation_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit ShadowCalculation(std::shared_ptr<detail::ShadowCalculation_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
