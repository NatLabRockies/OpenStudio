/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ELECTRICLOADCENTERTRANSFORMER_IMPL_HPP
#define EPMODEL_ELECTRICLOADCENTERTRANSFORMER_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API ElectricLoadCenterTransformer_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~ElectricLoadCenterTransformer_Impl() override = default;

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

      std::vector<std::string> transformerUsageValues() const;
      std::vector<std::string> phaseValues() const;
      std::vector<std::string> conductorMaterialValues() const;
      std::vector<std::string> performanceInputMethodValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
