/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_STANDARDGLAZING_HPP
#define EPMODEL_STANDARDGLAZING_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <boost/optional.hpp>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class StandardGlazing_Impl;
  }

  class EPMODEL_API StandardGlazing : public ModelObject
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
    void setSolarDiffusingNoFail(bool solarDiffusing);
    void resetSolarDiffusing();

    bool setThermalConductivity(double value);
    bool setThermalConductance(double value);
    bool setThermalResistivity(double value);
    bool setThermalResistance(double value);

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
