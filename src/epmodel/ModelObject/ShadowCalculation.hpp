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
    static constexpr bool is_unique = true;  // This is a Unique ModelObject

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
