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

     private:
      REGISTER_LOGGER("openstudio.epmodel.SurfacePropertyOtherSideCoefficients");
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
