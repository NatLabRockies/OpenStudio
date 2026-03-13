/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SITEGROUNDTEMPERATUREUNDISTURBEDKUSUDAACHENBACH_IMPL_HPP
#define EPMODEL_SITEGROUNDTEMPERATUREUNDISTURBEDKUSUDAACHENBACH_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API SiteGroundTemperatureUndisturbedKusudaAchenbach_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~SiteGroundTemperatureUndisturbedKusudaAchenbach_Impl() override = default;

      double soilThermalConductivity() const;
      bool setSoilThermalConductivity(double soilThermalConductivity);

      double soilDensity() const;
      bool setSoilDensity(double soilDensity);

      double soilSpecificHeat() const;
      bool setSoilSpecificHeat(double soilSpecificHeat);

      boost::optional<double> averageSoilSurfaceTemperature() const;
      bool setAverageSoilSurfaceTemperature(double averageSoilSurfaceTemperature);
      void resetAverageSoilSurfaceTemperature();

      boost::optional<double> averageAmplitudeofSurfaceTemperature() const;
      bool setAverageAmplitudeofSurfaceTemperature(double averageAmplitudeofSurfaceTemperature);
      void resetAverageAmplitudeofSurfaceTemperature();

      boost::optional<double> phaseShiftofMinimumSurfaceTemperature() const;
      bool setPhaseShiftofMinimumSurfaceTemperature(double phaseShiftofMinimumSurfaceTemperature);
      void resetPhaseShiftofMinimumSurfaceTemperature();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
