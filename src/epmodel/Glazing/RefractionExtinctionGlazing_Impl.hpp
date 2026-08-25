/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_REFRACTIONEXTINCTIONGLAZING_IMPL_HPP
#define EPMODEL_REFRACTIONEXTINCTIONGLAZING_IMPL_HPP

#include "Glazing/Glazing_Impl.hpp"

#include <string>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API RefractionExtinctionGlazing_Impl : public Glazing_Impl
    {
     public:
      using Glazing_Impl::Glazing_Impl;
      virtual ~RefractionExtinctionGlazing_Impl() override = default;

      double thickness() const override;
      bool setThickness(double thickness) override;

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
      void resetSolarDiffusing();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_REFRACTIONEXTINCTIONGLAZING_IMPL_HPP
