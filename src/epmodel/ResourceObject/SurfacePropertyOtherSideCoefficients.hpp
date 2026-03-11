/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SURFACEPROPERTYOTHERSIDECOEFFICIENTS_HPP
#define EPMODEL_SURFACEPROPERTYOTHERSIDECOEFFICIENTS_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <boost/optional.hpp>
#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class SurfacePropertyOtherSideCoefficients_Impl;
  }

  class EPMODEL_API SurfacePropertyOtherSideCoefficients : public ModelObject
  {
   public:
    explicit SurfacePropertyOtherSideCoefficients(const Model& model);

    virtual ~SurfacePropertyOtherSideCoefficients() override = default;
    SurfacePropertyOtherSideCoefficients(const SurfacePropertyOtherSideCoefficients& other) = default;
    SurfacePropertyOtherSideCoefficients(SurfacePropertyOtherSideCoefficients&& other) = default;
    SurfacePropertyOtherSideCoefficients& operator=(const SurfacePropertyOtherSideCoefficients&) = default;
    SurfacePropertyOtherSideCoefficients& operator=(SurfacePropertyOtherSideCoefficients&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: Preserve openstudio::model scalar accessor names/signatures for SurfacePropertyOtherSideCoefficients.
    // - Field Mapping: Each scalar maps to the corresponding EnergyPlus SurfaceProperty:OtherSideCoefficients field via
    //   SurfaceProperty_OtherSideCoefficientsFields (combined film coefficient, constant temperature, temperature
    //   coefficients, and the optional min/max limits). The constant temperature schedule field is a relationship and is
    //   intentionally excluded from this scalar-only scaffold pass.
    // - ForwardTranslator evidence: ForwardTranslateSurfacePropertyOtherSideCoefficients.cpp writes the same EnergyPlus
    //   fields with the same Yes/No semantics and autosized default handling.
    // - TODO(parity): Reintroduce schedule relationship helpers once epmodel schedule scaffolding advances.

    boost::optional<double> combinedConvectiveRadiativeFilmCoefficient() const;
    double constantTemperature() const;
    bool isConstantTemperatureDefaulted() const;
    double constantTemperatureCoefficient() const;
    bool isConstantTemperatureCoefficientDefaulted() const;
    double externalDryBulbTemperatureCoefficient() const;
    bool isExternalDryBulbTemperatureCoefficientDefaulted() const;
    double groundTemperatureCoefficient() const;
    bool isGroundTemperatureCoefficientDefaulted() const;
    double windSpeedCoefficient() const;
    bool isWindSpeedCoefficientDefaulted() const;
    double zoneAirTemperatureCoefficient() const;
    bool isZoneAirTemperatureCoefficientDefaulted() const;
    bool sinusoidalVariationofConstantTemperatureCoefficient() const;
    bool isSinusoidalVariationofConstantTemperatureCoefficientDefaulted() const;
    double periodofSinusoidalVariation() const;
    bool isPeriodofSinusoidalVariationDefaulted() const;
    double previousOtherSideTemperatureCoefficient() const;
    bool isPreviousOtherSideTemperatureCoefficientDefaulted() const;
    boost::optional<double> minimumOtherSideTemperatureLimit() const;
    boost::optional<double> maximumOtherSideTemperatureLimit() const;

    bool setCombinedConvectiveRadiativeFilmCoefficient(double combinedConvectiveRadiativeFilmCoefficient);
    void resetCombinedConvectiveRadiativeFilmCoefficient();

    bool setConstantTemperature(double constantTemperature);
    void resetConstantTemperature();

    bool setConstantTemperatureCoefficient(double constantTemperatureCoefficient);
    void resetConstantTemperatureCoefficient();

    bool setExternalDryBulbTemperatureCoefficient(double externalDryBulbTemperatureCoefficient);
    void resetExternalDryBulbTemperatureCoefficient();

    bool setGroundTemperatureCoefficient(double groundTemperatureCoefficient);
    void resetGroundTemperatureCoefficient();

    bool setWindSpeedCoefficient(double windSpeedCoefficient);
    void resetWindSpeedCoefficient();

    bool setZoneAirTemperatureCoefficient(double zoneAirTemperatureCoefficient);
    void resetZoneAirTemperatureCoefficient();

    bool setSinusoidalVariationofConstantTemperatureCoefficient(bool sinusoidalVariationofConstantTemperatureCoefficient);
    void resetSinusoidalVariationofConstantTemperatureCoefficient();

    bool setPeriodofSinusoidalVariation(double periodofSinusoidalVariation);
    void resetPeriodofSinusoidalVariation();

    bool setPreviousOtherSideTemperatureCoefficient(double previousOtherSideTemperatureCoefficient);
    void resetPreviousOtherSideTemperatureCoefficient();

    bool setMinimumOtherSideTemperatureLimit(double minimumOtherSideTemperatureLimit);
    void resetMinimumOtherSideTemperatureLimit();

    bool setMaximumOtherSideTemperatureLimit(double maximumOtherSideTemperatureLimit);
    void resetMaximumOtherSideTemperatureLimit();

   protected:
    using ImplType = detail::SurfacePropertyOtherSideCoefficients_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SurfacePropertyOtherSideCoefficients(std::shared_ptr<detail::SurfacePropertyOtherSideCoefficients_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
