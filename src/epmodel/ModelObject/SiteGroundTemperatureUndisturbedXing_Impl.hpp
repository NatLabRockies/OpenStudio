/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SITEGROUNDTEMPERATUREUNDISTURBEDXING_IMPL_HPP
#define EPMODEL_SITEGROUNDTEMPERATUREUNDISTURBEDXING_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API SiteGroundTemperatureUndisturbedXing_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~SiteGroundTemperatureUndisturbedXing_Impl() override = default;

      double soilThermalConductivity() const;
      bool setSoilThermalConductivity(double soilThermalConductivity);

      double soilDensity() const;
      bool setSoilDensity(double soilDensity);

      double soilSpecificHeat() const;
      bool setSoilSpecificHeat(double soilSpecificHeat);

      double averageSoilSurfaceTemperature() const;
      bool setAverageSoilSurfaceTemperature(double averageSoilSurfaceTemperature);

      double soilSurfaceTemperatureAmplitude1() const;
      bool setSoilSurfaceTemperatureAmplitude1(double soilSurfaceTemperatureAmplitude1);

      double soilSurfaceTemperatureAmplitude2() const;
      bool setSoilSurfaceTemperatureAmplitude2(double soilSurfaceTemperatureAmplitude2);

      double phaseShiftofTemperatureAmplitude1() const;
      bool setPhaseShiftofTemperatureAmplitude1(double phaseShiftofTemperatureAmplitude1);

      double phaseShiftofTemperatureAmplitude2() const;
      bool setPhaseShiftofTemperatureAmplitude2(double phaseShiftofTemperatureAmplitude2);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
