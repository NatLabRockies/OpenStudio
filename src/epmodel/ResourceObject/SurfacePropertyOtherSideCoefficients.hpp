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

  /** \brief Defines coefficients for calculating a surface's other-side temperature.
   *
   * \par EnergyPlus object
   * \epobject{group-advanced-surface-concepts.html#surfacepropertyothersidecoefficients,SurfaceProperty:OtherSideCoefficients}.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::SurfacePropertyOtherSideCoefficients</code>.
   * EPModel exposes the same scalar fields and default/reset operations, but
   * not Model's <code>constantTemperatureSchedule()</code> relationship and
   * its setter/resetter.
   *
   * \par Known limitations
   * The constant-temperature schedule relationship cannot be assigned through
   * this wrapper.
   */
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

    boost::optional<double> combinedConvectiveRadiativeFilmCoefficient() const;
    bool setCombinedConvectiveRadiativeFilmCoefficient(double combinedConvectiveRadiativeFilmCoefficient);
    void resetCombinedConvectiveRadiativeFilmCoefficient();

    double constantTemperature() const;
    bool isConstantTemperatureDefaulted() const;
    bool setConstantTemperature(double constantTemperature);
    void resetConstantTemperature();

    double constantTemperatureCoefficient() const;
    bool isConstantTemperatureCoefficientDefaulted() const;
    bool setConstantTemperatureCoefficient(double constantTemperatureCoefficient);
    void resetConstantTemperatureCoefficient();

    double externalDryBulbTemperatureCoefficient() const;
    bool isExternalDryBulbTemperatureCoefficientDefaulted() const;
    bool setExternalDryBulbTemperatureCoefficient(double externalDryBulbTemperatureCoefficient);
    void resetExternalDryBulbTemperatureCoefficient();

    double groundTemperatureCoefficient() const;
    bool isGroundTemperatureCoefficientDefaulted() const;
    bool setGroundTemperatureCoefficient(double groundTemperatureCoefficient);
    void resetGroundTemperatureCoefficient();

    double windSpeedCoefficient() const;
    bool isWindSpeedCoefficientDefaulted() const;
    bool setWindSpeedCoefficient(double windSpeedCoefficient);
    void resetWindSpeedCoefficient();

    double zoneAirTemperatureCoefficient() const;
    bool isZoneAirTemperatureCoefficientDefaulted() const;
    bool setZoneAirTemperatureCoefficient(double zoneAirTemperatureCoefficient);
    void resetZoneAirTemperatureCoefficient();

    bool sinusoidalVariationofConstantTemperatureCoefficient() const;
    bool isSinusoidalVariationofConstantTemperatureCoefficientDefaulted() const;
    bool setSinusoidalVariationofConstantTemperatureCoefficient(bool sinusoidalVariationofConstantTemperatureCoefficient);
    void resetSinusoidalVariationofConstantTemperatureCoefficient();

    double periodofSinusoidalVariation() const;
    bool isPeriodofSinusoidalVariationDefaulted() const;
    bool setPeriodofSinusoidalVariation(double periodofSinusoidalVariation);
    void resetPeriodofSinusoidalVariation();

    double previousOtherSideTemperatureCoefficient() const;
    bool isPreviousOtherSideTemperatureCoefficientDefaulted() const;
    bool setPreviousOtherSideTemperatureCoefficient(double previousOtherSideTemperatureCoefficient);
    void resetPreviousOtherSideTemperatureCoefficient();

    boost::optional<double> minimumOtherSideTemperatureLimit() const;
    bool setMinimumOtherSideTemperatureLimit(double minimumOtherSideTemperatureLimit);
    void resetMinimumOtherSideTemperatureLimit();

    boost::optional<double> maximumOtherSideTemperatureLimit() const;
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
