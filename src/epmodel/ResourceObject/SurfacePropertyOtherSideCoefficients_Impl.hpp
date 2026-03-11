/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SURFACEPROPERTYOTHERSIDECOEFFICIENTS_IMPL_HPP
#define EPMODEL_SURFACEPROPERTYOTHERSIDECOEFFICIENTS_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API SurfacePropertyOtherSideCoefficients_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~SurfacePropertyOtherSideCoefficients_Impl() override = default;

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

     private:
      REGISTER_LOGGER("openstudio.epmodel.SurfacePropertyOtherSideCoefficients");
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
