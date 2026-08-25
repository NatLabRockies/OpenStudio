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

  /** \brief Represents a standard detailed glazing layer.
   *
   * \par EnergyPlus object
   * \epobject{group-surface-construction-elements.html#windowmaterialglazing,WindowMaterial:Glazing}.
   *
   * \par Important behavior
   * Thermal conductance, resistivity, and resistance are derived from the
   * persisted conductivity and thickness fields. Optical data type and
   * normal-incidence fields remain direct EnergyPlus inputs.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::StandardGlazing</code>. Inherited optical helpers
   * including
   * <code>interiorVisibleAbsorptance()</code> and
   * <code>exteriorVisibleAbsorptance()</code>. Model's
   * <code>windowGlassSpectralDataSet()</code>,
   * <code>setWindowGlassSpectralDataSet()</code>, and
   * <code>resetWindowGlassSpectralDataSet()</code> relationship methods are
   * not available.
   *
   * \par Known limitations
   * A spectral-data set cannot be assigned through this wrapper.
   */
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
