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
  double soilDensity() const;
  double soilSpecificHeat() const;
  boost::optional<double> averageSoilSurfaceTemperature() const;
  boost::optional<double> averageAmplitudeofSurfaceTemperature() const;
  boost::optional<double> phaseShiftofMinimumSurfaceTemperature() const;

  bool setSoilThermalConductivity(double soilThermalConductivity);
  bool setSoilDensity(double soilDensity);
  bool setSoilSpecificHeat(double soilSpecificHeat);
  bool setAverageSoilSurfaceTemperature(double averageSoilSurfaceTemperature);
  void resetAverageSoilSurfaceTemperature();
  bool setAverageAmplitudeofSurfaceTemperature(double averageAmplitudeofSurfaceTemperature);
  void resetAverageAmplitudeofSurfaceTemperature();
  bool setPhaseShiftofMinimumSurfaceTemperature(double phaseShiftofMinimumSurfaceTemperature);
  void resetPhaseShiftofMinimumSurfaceTemperature();
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
