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

  /** \brief ShadowCalculation.
   *
   * \par EnergyPlus object
   * \epobject{group-simulation-parameters.html#shadowcalculation,ShadowCalculation}.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::ShadowCalculation</code>. Scalar shadow-calculation settings map directly to EnergyPlus. Model's <code>numberofShadingZoneGroups()</code>, <code>addShadingZoneGroup()</code>, and shading-zone-group removal/access methods are not available.
   *
   * \par Known limitations
   * No known EPModel-specific limitations.
   */
  class EPMODEL_API ShadowCalculation : public ModelObject
  {
   public:
    static constexpr bool is_unique = true;  // This is a Unique ModelObject

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
    explicit ShadowCalculation(const Model& model);

    using ImplType = detail::ShadowCalculation_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ShadowCalculation(std::shared_ptr<detail::ShadowCalculation_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
