/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_STANDARDGLAZING_HPP
#define EPMODEL_STANDARDGLAZING_HPP

#include "EPModelAPI.hpp"
#include "Glazing/Glazing.hpp"

#include <boost/optional.hpp>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class StandardGlazing_Impl;
  }

  class EPMODEL_API StandardGlazing : public Glazing
  {
   public:
    explicit StandardGlazing(const Model& model, const std::string& opticalDataType = "SpectralAverage", double thickness = 0.1);

    virtual ~StandardGlazing() override = default;
    StandardGlazing(const StandardGlazing& other) = default;
    StandardGlazing(StandardGlazing&& other) = default;
    StandardGlazing& operator=(const StandardGlazing&) = default;
    StandardGlazing& operator=(StandardGlazing&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> opticalDataTypeValues();

    // Schema Alignment Notes:
    // - API: Preserves openstudio::model::StandardGlazing scalar accessor names/signatures for optical/thermal/basic scalar fields.
    // - Field Mapping: Optical data type, thickness, solar/visible/infrared transmittance and reflectance, conductivity, dirt correction, and thermal conductance/resistivity/resistance map directly to OS_WindowMaterial_Glazing field enums.
    // - ForwardTranslator evidence: ForwardTranslator/ForwardTranslateStandardGlazing.cpp keeps these scalar fields aligned with the EnergyPlus OS:WindowMaterial:Glazing schema.
    // - Field Mapping: Window Glass Spectral Data Set Name is a material-property relationship and is intentionally excluded during this scalar-only scaffolding run.

    std::string opticalDataType() const;
    bool setOpticalDataType(const std::string& opticalDataType);

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
    bool setInfraredTransmittance(double value);

    double infraredTransmittanceatNormalIncidence() const;
    bool setInfraredTransmittanceatNormalIncidence(double value);
    void resetInfraredTransmittanceatNormalIncidence();
    bool isInfraredTransmittanceatNormalIncidenceDefaulted() const;

    double frontSideInfraredHemisphericalEmissivity() const;
    bool setFrontSideInfraredHemisphericalEmissivity(double value);
    void resetFrontSideInfraredHemisphericalEmissivity();
    bool isFrontSideInfraredHemisphericalEmissivityDefaulted() const;

    double backSideInfraredHemisphericalEmissivity() const;
    bool setBackSideInfraredHemisphericalEmissivity(double value);
    void resetBackSideInfraredHemisphericalEmissivity();
    bool isBackSideInfraredHemisphericalEmissivityDefaulted() const;

    double conductivity() const;
    bool setConductivity(double value);
    void resetConductivity();
    bool isConductivityDefaulted() const;

    double dirtCorrectionFactorforSolarandVisibleTransmittance() const;
    bool setDirtCorrectionFactorforSolarandVisibleTransmittance(double value);
    void resetDirtCorrectionFactorforSolarandVisibleTransmittance();
    bool isDirtCorrectionFactorforSolarandVisibleTransmittanceDefaulted() const;

    bool solarDiffusing() const;
    bool setSolarDiffusing(bool solarDiffusing);
    void setSolarDiffusingNoFail(bool solarDiffusing);
    void resetSolarDiffusing();
    bool isSolarDiffusingDefaulted() const;

    double thermalConductivity() const;
    bool setThermalConductivity(double value);

    double thermalConductance() const;
    bool setThermalConductance(double value);

    double thermalResistivity() const;
    bool setThermalResistivity(double value);

    double thermalResistance() const;
    bool setThermalResistance(double value);

    double interiorVisibleReflectance() const;
    bool setInteriorVisibleReflectance(double value);

    double exteriorVisibleReflectance() const;
    bool setExteriorVisibleReflectance(double value);

    boost::optional<double> interiorVisibleAbsorptance() const;

    boost::optional<double> exteriorVisibleAbsorptance() const;

   protected:
    using ImplType = detail::StandardGlazing_Impl;

    explicit StandardGlazing(std::shared_ptr<detail::StandardGlazing_Impl> impl);

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;
  };

}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_STANDARDGLAZING_HPP
