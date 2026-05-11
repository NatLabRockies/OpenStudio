/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_STANDARDGLAZING_IMPL_HPP
#define EPMODEL_STANDARDGLAZING_IMPL_HPP

#include "Material/Material_Impl.hpp"

#include <boost/optional.hpp>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API StandardGlazing_Impl : public Material_Impl
    {
     public:
      using Material_Impl::Material_Impl;
      virtual ~StandardGlazing_Impl() override = default;

      std::string opticalDataType() const;
      bool setOpticalDataType(const std::string& opticalDataType);
      std::vector<std::string> opticalDataTypeValues() const;

      double thickness() const;
      bool setThickness(double thickness);

      double solarTransmittance() const;
      bool setSolarTransmittance(double value);

      boost::optional<double> solarTransmittanceatNormalIncidence() const;
      bool setSolarTransmittanceatNormalIncidence(double value);
      void resetSolarTransmittanceatNormalIncidence();

      boost::optional<double> frontSideSolarReflectanceatNormalIncidence() const;
      bool setFrontSideSolarReflectanceatNormalIncidence(double value);
      void resetFrontSideSolarReflectanceatNormalIncidence();

      boost::optional<double> backSideSolarReflectanceatNormalIncidence() const;
      bool setBackSideSolarReflectanceatNormalIncidence(double value);
      void resetBackSideSolarReflectanceatNormalIncidence();

      boost::optional<double> visibleTransmittanceatNormalIncidence() const;
      bool setVisibleTransmittance(double value);
      bool setVisibleTransmittanceatNormalIncidence(double value);
      void resetVisibleTransmittanceatNormalIncidence();

      boost::optional<double> frontSideVisibleReflectanceatNormalIncidence() const;
      bool setFrontSideVisibleReflectanceatNormalIncidence(double value);
      void resetFrontSideVisibleReflectanceatNormalIncidence();

      boost::optional<double> backSideVisibleReflectanceatNormalIncidence() const;
      bool setBackSideVisibleReflectanceatNormalIncidence(double value);
      void resetBackSideVisibleReflectanceatNormalIncidence();

      double infraredTransmittance() const;
      double infraredTransmittanceatNormalIncidence() const;
      bool isInfraredTransmittanceatNormalIncidenceDefaulted() const;
      bool setInfraredTransmittance(double value);
      bool setInfraredTransmittanceatNormalIncidence(double value);
      void resetInfraredTransmittanceatNormalIncidence();

      double frontSideInfraredHemisphericalEmissivity() const;
      bool isFrontSideInfraredHemisphericalEmissivityDefaulted() const;
      bool setFrontSideInfraredHemisphericalEmissivity(double value);
      void resetFrontSideInfraredHemisphericalEmissivity();

      double backSideInfraredHemisphericalEmissivity() const;
      bool isBackSideInfraredHemisphericalEmissivityDefaulted() const;
      bool setBackSideInfraredHemisphericalEmissivity(double value);
      void resetBackSideInfraredHemisphericalEmissivity();

      double conductivity() const;
      bool isConductivityDefaulted() const;
      bool setConductivity(double value);
      void resetConductivity();

      double dirtCorrectionFactorforSolarandVisibleTransmittance() const;
      bool isDirtCorrectionFactorforSolarandVisibleTransmittanceDefaulted() const;
      bool setDirtCorrectionFactorforSolarandVisibleTransmittance(double value);
      void resetDirtCorrectionFactorforSolarandVisibleTransmittance();

      bool solarDiffusing() const;
      bool isSolarDiffusingDefaulted() const;
      bool setSolarDiffusing(bool solarDiffusing);
      void resetSolarDiffusing();

      double thermalConductivity() const;
      bool setThermalConductivity(double value);

      double thermalConductance() const;
      bool setThermalConductance(double value);

      double thermalResistivity() const;
      bool setThermalResistivity(double value);

      double thermalResistance() const;
      bool setThermalResistance(double value);

      double interiorVisibleReflectance() const;
      double exteriorVisibleReflectance() const;

      boost::optional<double> interiorVisibleAbsorptance() const;
      boost::optional<double> exteriorVisibleAbsorptance() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_STANDARDGLAZING_IMPL_HPP
