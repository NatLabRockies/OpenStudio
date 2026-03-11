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
  double soilDensity() const;
  double soilSpecificHeat() const;
  double averageSoilSurfaceTemperature() const;
  double soilSurfaceTemperatureAmplitude1() const;
  double soilSurfaceTemperatureAmplitude2() const;
  double phaseShiftofTemperatureAmplitude1() const;
  double phaseShiftofTemperatureAmplitude2() const;

  bool setSoilThermalConductivity(double soilThermalConductivity);
  bool setSoilDensity(double soilDensity);
  bool setSoilSpecificHeat(double soilSpecificHeat);
  bool setAverageSoilSurfaceTemperature(double averageSoilSurfaceTemperature);
  bool setSoilSurfaceTemperatureAmplitude1(double soilSurfaceTemperatureAmplitude1);
  bool setSoilSurfaceTemperatureAmplitude2(double soilSurfaceTemperatureAmplitude2);
  bool setPhaseShiftofTemperatureAmplitude1(double phaseShiftofTemperatureAmplitude1);
  bool setPhaseShiftofTemperatureAmplitude2(double phaseShiftofTemperatureAmplitude2);
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
