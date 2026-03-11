/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_STANDARDGLAZING_IMPL_HPP
#define EPMODEL_STANDARDGLAZING_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <boost/optional.hpp>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API StandardGlazing_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~StandardGlazing_Impl() override = default;

      std::string opticalDataType() const;
      double thickness() const;

      double solarTransmittance() const;
      boost::optional<double> solarTransmittanceatNormalIncidence() const;
      boost::optional<double> frontSideSolarReflectanceatNormalIncidence() const;
      boost::optional<double> backSideSolarReflectanceatNormalIncidence() const;

      boost::optional<double> visibleTransmittanceatNormalIncidence() const;
      boost::optional<double> frontSideVisibleReflectanceatNormalIncidence() const;
      boost::optional<double> backSideVisibleReflectanceatNormalIncidence() const;

      double infraredTransmittance() const;
      double infraredTransmittanceatNormalIncidence() const;
      bool isInfraredTransmittanceatNormalIncidenceDefaulted() const;

      double frontSideInfraredHemisphericalEmissivity() const;
      bool isFrontSideInfraredHemisphericalEmissivityDefaulted() const;
      double backSideInfraredHemisphericalEmissivity() const;
      bool isBackSideInfraredHemisphericalEmissivityDefaulted() const;

      double conductivity() const;
      bool isConductivityDefaulted() const;

      double dirtCorrectionFactorforSolarandVisibleTransmittance() const;
      bool isDirtCorrectionFactorforSolarandVisibleTransmittanceDefaulted() const;

      bool solarDiffusing() const;
      bool isSolarDiffusingDefaulted() const;

      double thermalConductivity() const;
      double thermalConductance() const;
      double thermalResistivity() const;
      double thermalResistance() const;

      double interiorVisibleReflectance() const;
      double exteriorVisibleReflectance() const;

      boost::optional<double> interiorVisibleAbsorptance() const;
      boost::optional<double> exteriorVisibleAbsorptance() const;

      bool setOpticalDataType(const std::string& opticalDataType);
      bool setThickness(double thickness);

      bool setSolarTransmittance(double value);
      bool setSolarTransmittanceatNormalIncidence(double value);
      void resetSolarTransmittanceatNormalIncidence();

      bool setFrontSideSolarReflectanceatNormalIncidence(double value);
      void resetFrontSideSolarReflectanceatNormalIncidence();

      bool setBackSideSolarReflectanceatNormalIncidence(double value);
      void resetBackSideSolarReflectanceatNormalIncidence();

      bool setVisibleTransmittance(double value);
      bool setVisibleTransmittanceatNormalIncidence(double value);
      void resetVisibleTransmittanceatNormalIncidence();

      bool setFrontSideVisibleReflectanceatNormalIncidence(double value);
      void resetFrontSideVisibleReflectanceatNormalIncidence();

      bool setBackSideVisibleReflectanceatNormalIncidence(double value);
      void resetBackSideVisibleReflectanceatNormalIncidence();

      bool setInfraredTransmittance(double value);
      bool setInfraredTransmittanceatNormalIncidence(double value);
      void resetInfraredTransmittanceatNormalIncidence();

      bool setFrontSideInfraredHemisphericalEmissivity(double value);
      void resetFrontSideInfraredHemisphericalEmissivity();

      bool setBackSideInfraredHemisphericalEmissivity(double value);
      void resetBackSideInfraredHemisphericalEmissivity();

      bool setConductivity(double value);
      void resetConductivity();

      bool setDirtCorrectionFactorforSolarandVisibleTransmittance(double value);
      void resetDirtCorrectionFactorforSolarandVisibleTransmittance();

      bool setSolarDiffusing(bool solarDiffusing);
      void resetSolarDiffusing();

      bool setThermalConductivity(double value);
      bool setThermalConductance(double value);
      bool setThermalResistivity(double value);
      bool setThermalResistance(double value);

      std::vector<std::string> opticalDataTypeValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_STANDARDGLAZING_IMPL_HPP
