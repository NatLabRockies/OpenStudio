/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_REFRACTIONEXTINCTIONGLAZING_IMPL_HPP
#define EPMODEL_REFRACTIONEXTINCTIONGLAZING_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <string>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API RefractionExtinctionGlazing_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~RefractionExtinctionGlazing_Impl() override = default;

      double thickness() const;

      double solarIndexofRefraction() const;

      double solarExtinctionCoefficient() const;

      double visibleIndexofRefraction() const;

      double visibleExtinctionCoefficient() const;

      double infraredTransmittanceatNormalIncidence() const;
      bool isInfraredTransmittanceatNormalIncidenceDefaulted() const;

      double infraredHemisphericalEmissivity() const;
      bool isInfraredHemisphericalEmissivityDefaulted() const;

      double conductivity() const;
      bool isConductivityDefaulted() const;

      double dirtCorrectionFactorforSolarandVisibleTransmittance() const;
      bool isDirtCorrectionFactorforSolarandVisibleTransmittanceDefaulted() const;

      bool solarDiffusing() const;
      bool isSolarDiffusingDefaulted() const;

      bool setThickness(double thickness);

      bool setSolarIndexofRefraction(double solarIndexofRefraction);

      bool setSolarExtinctionCoefficient(double solarExtinctionCoefficient);

      bool setVisibleIndexofRefraction(double visibleIndexofRefraction);

      bool setVisibleExtinctionCoefficient(double visibleExtinctionCoefficient);

      bool setInfraredTransmittanceatNormalIncidence(double infraredTransmittanceatNormalIncidence);
      void resetInfraredTransmittanceatNormalIncidence();

      bool setInfraredHemisphericalEmissivity(double infraredHemisphericalEmissivity);
      void resetInfraredHemisphericalEmissivity();

      bool setConductivity(double conductivity);
      void resetConductivity();

      bool setDirtCorrectionFactorforSolarandVisibleTransmittance(double dirtCorrectionFactor);
      void resetDirtCorrectionFactorforSolarandVisibleTransmittance();

      bool setSolarDiffusing(bool solarDiffusing);
      void resetSolarDiffusing();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_REFRACTIONEXTINCTIONGLAZING_IMPL_HPP
