/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_REFRACTIONEXTINCTIONGLAZING_HPP
#define EPMODEL_REFRACTIONEXTINCTIONGLAZING_HPP

#include "EPModelAPI.hpp"
#include "Glazing/Glazing.hpp"

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class RefractionExtinctionGlazing_Impl;
  }

  class EPMODEL_API RefractionExtinctionGlazing : public Glazing
  {
   public:
    explicit RefractionExtinctionGlazing(const Model& model, double thickness = 0.1, double solarIndexofRefraction = 1.1,
                                         double solarExtinctionCoefficient = 0.1, double visibleIndexofRefraction = 1.1,
                                         double visibleExtinctionCoefficient = 0.1);

    virtual ~RefractionExtinctionGlazing() override = default;
    RefractionExtinctionGlazing(const RefractionExtinctionGlazing& other) = default;
    RefractionExtinctionGlazing(RefractionExtinctionGlazing&& other) = default;
    RefractionExtinctionGlazing& operator=(const RefractionExtinctionGlazing&) = default;
    RefractionExtinctionGlazing& operator=(RefractionExtinctionGlazing&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: Keeps openstudio::model::RefractionExtinctionGlazing scalar accessor names for thickness, optical index/extinction fields,
    //   conductivity/dirt-correction defaults, and Solar Diffusing so existing epmodel unblock matches the translator surface.
    // - Field Mapping: Maps each accessor to OS:WindowMaterial:Glazing:RefractionExtinctionMethod via
    //   OS_WindowMaterial_Glazing_RefractionExtinctionMethodFields.
    // - ForwardTranslator evidence: ForwardTranslateRefractionExtinctionGlazing.cpp maintains the same EnergyPlus field names for these scalar inputs.

    double thickness() const;
    bool setThickness(double thickness);

    double solarIndexofRefraction() const;
    bool setSolarIndexofRefraction(double solarIndexofRefraction);

    double solarExtinctionCoefficient() const;
    bool setSolarExtinctionCoefficient(double solarExtinctionCoefficient);

    double visibleIndexofRefraction() const;
    bool setVisibleIndexofRefraction(double visibleIndexofRefraction);

    double visibleExtinctionCoefficient() const;
    bool setVisibleExtinctionCoefficient(double visibleExtinctionCoefficient);

    double infraredTransmittanceatNormalIncidence() const;
    bool isInfraredTransmittanceatNormalIncidenceDefaulted() const;
    bool setInfraredTransmittanceatNormalIncidence(double infraredTransmittanceatNormalIncidence);
    void resetInfraredTransmittanceatNormalIncidence();

    double infraredHemisphericalEmissivity() const;
    bool isInfraredHemisphericalEmissivityDefaulted() const;
    bool setInfraredHemisphericalEmissivity(double infraredHemisphericalEmissivity);
    void resetInfraredHemisphericalEmissivity();

    double conductivity() const;
    bool isConductivityDefaulted() const;
    bool setConductivity(double conductivity);
    void resetConductivity();

    double dirtCorrectionFactorforSolarandVisibleTransmittance() const;
    bool isDirtCorrectionFactorforSolarandVisibleTransmittanceDefaulted() const;
    bool setDirtCorrectionFactorforSolarandVisibleTransmittance(double dirtCorrectionFactor);
    void resetDirtCorrectionFactorforSolarandVisibleTransmittance();

    bool solarDiffusing() const;
    bool isSolarDiffusingDefaulted() const;
    bool setSolarDiffusing(bool solarDiffusing);
    void setSolarDiffusingNoFail(bool solarDiffusing);
    void resetSolarDiffusing();

   protected:
    using ImplType = detail::RefractionExtinctionGlazing_Impl;

    explicit RefractionExtinctionGlazing(std::shared_ptr<detail::RefractionExtinctionGlazing_Impl> impl);

    friend class detail::RefractionExtinctionGlazing_Impl;
    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;
  };

}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_REFRACTIONEXTINCTIONGLAZING_HPP
