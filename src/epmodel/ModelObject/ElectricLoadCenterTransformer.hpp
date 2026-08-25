/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ELECTRICLOADCENTERTRANSFORMER_HPP
#define EPMODEL_ELECTRICLOADCENTERTRANSFORMER_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ElectricLoadCenterTransformer_Impl;
  }

  /** \brief Represents <code>ElectricLoadCenter:Transformer</code>.
   *
   * \par EnergyPlus object
   * \epobject{group-electric-load-center-generator.html#electricloadcentertransformer,ElectricLoadCenter:Transformer}
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::ElectricLoadCenterTransformer</code>.
   * **Not yet available:** Model relationship and extensible-list conveniences are not exposed unless declared here.
   *
   * \par Known limitations
   * Relationship and extensible data not represented by the public declarations must be maintained by the owning object.
   */
  class EPMODEL_API ElectricLoadCenterTransformer : public ModelObject
  {
   public:
    explicit ElectricLoadCenterTransformer(const Model& model);

    virtual ~ElectricLoadCenterTransformer() override = default;
    ElectricLoadCenterTransformer(const ElectricLoadCenterTransformer& other) = default;
    ElectricLoadCenterTransformer(ElectricLoadCenterTransformer&& other) = default;
    ElectricLoadCenterTransformer& operator=(const ElectricLoadCenterTransformer&) = default;
    ElectricLoadCenterTransformer& operator=(ElectricLoadCenterTransformer&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> transformerUsageValues();
    static std::vector<std::string> phaseValues();
    static std::vector<std::string> conductorMaterialValues();
    static std::vector<std::string> performanceInputMethodValues();
    std::string transformerUsage() const;
    bool isTransformerUsageDefaulted() const;
    bool setTransformerUsage(const std::string& transformerUsage);
    void resetTransformerUsage();

    double radiativeFraction() const;
    bool isRadiativeFractionDefaulted() const;
    bool setRadiativeFraction(double radiativeFraction);
    void resetRadiativeFraction();

    boost::optional<double> ratedCapacity() const;
    bool setRatedCapacity(double ratedCapacity);
    void resetRatedCapacity();

    std::string phase() const;
    bool isPhaseDefaulted() const;
    bool setPhase(const std::string& phase);
    void resetPhase();

    std::string conductorMaterial() const;
    bool isConductorMaterialDefaulted() const;
    bool setConductorMaterial(const std::string& conductorMaterial);
    void resetConductorMaterial();

    double fullLoadTemperatureRise() const;
    bool isFullLoadTemperatureRiseDefaulted() const;
    bool setFullLoadTemperatureRise(double fullLoadTemperatureRise);
    void resetFullLoadTemperatureRise();

    double fractionofEddyCurrentLosses() const;
    bool isFractionofEddyCurrentLossesDefaulted() const;
    bool setFractionofEddyCurrentLosses(double fractionofEddyCurrentLosses);
    void resetFractionofEddyCurrentLosses();

    std::string performanceInputMethod() const;
    bool isPerformanceInputMethodDefaulted() const;
    bool setPerformanceInputMethod(const std::string& performanceInputMethod);
    void resetPerformanceInputMethod();

    boost::optional<double> ratedNoLoadLoss() const;
    bool setRatedNoLoadLoss(double ratedNoLoadLoss);
    void resetRatedNoLoadLoss();

    boost::optional<double> ratedLoadLoss() const;
    bool setRatedLoadLoss(double ratedLoadLoss);
    void resetRatedLoadLoss();

    double nameplateEfficiency() const;
    bool isNameplateEfficiencyDefaulted() const;
    bool setNameplateEfficiency(double nameplateEfficiency);
    void resetNameplateEfficiency();

    double perUnitLoadforNameplateEfficiency() const;
    bool isPerUnitLoadforNameplateEfficiencyDefaulted() const;
    bool setPerUnitLoadforNameplateEfficiency(double perUnitLoadforNameplateEfficiency);
    void resetPerUnitLoadforNameplateEfficiency();

    double referenceTemperatureforNameplateEfficiency() const;
    bool isReferenceTemperatureforNameplateEfficiencyDefaulted() const;
    bool setReferenceTemperatureforNameplateEfficiency(double referenceTemperatureforNameplateEfficiency);
    void resetReferenceTemperatureforNameplateEfficiency();

    boost::optional<double> perUnitLoadforMaximumEfficiency() const;
    bool setPerUnitLoadforMaximumEfficiency(double perUnitLoadforMaximumEfficiency);
    void resetPerUnitLoadforMaximumEfficiency();

    bool considerTransformerLossforUtilityCost() const;
    bool isConsiderTransformerLossforUtilityCostDefaulted() const;
    bool setConsiderTransformerLossforUtilityCost(bool considerTransformerLossforUtilityCost);
    void resetConsiderTransformerLossforUtilityCost();

   protected:
    using ImplType = detail::ElectricLoadCenterTransformer_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ElectricLoadCenterTransformer(std::shared_ptr<detail::ElectricLoadCenterTransformer_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
