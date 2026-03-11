/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SITEGROUNDTEMPERATUREUNDISTURBEDFINITEDIFFERENCE_IMPL_HPP
#define EPMODEL_SITEGROUNDTEMPERATUREUNDISTURBEDFINITEDIFFERENCE_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API SiteGroundTemperatureUndisturbedFiniteDifference_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~SiteGroundTemperatureUndisturbedFiniteDifference_Impl() override = default;

  double soilThermalConductivity() const;
  double soilDensity() const;
  double soilSpecificHeat() const;
  double soilMoistureContentVolumeFraction() const;
  bool isSoilMoistureContentVolumeFractionDefaulted() const;
  double soilMoistureContentVolumeFractionatSaturation() const;
  bool isSoilMoistureContentVolumeFractionatSaturationDefaulted() const;
  double evapotranspirationGroundCoverParameter() const;
  bool isEvapotranspirationGroundCoverParameterDefaulted() const;

  bool setSoilThermalConductivity(double soilThermalConductivity);
  bool setSoilDensity(double soilDensity);
  bool setSoilSpecificHeat(double soilSpecificHeat);
  bool setSoilMoistureContentVolumeFraction(double soilMoistureContentVolumeFraction);
  bool setSoilMoistureContentVolumeFractionatSaturation(double soilMoistureContentVolumeFractionatSaturation);
  bool setEvapotranspirationGroundCoverParameter(double evapotranspirationGroundCoverParameter);

  void resetSoilMoistureContentVolumeFraction();
  void resetSoilMoistureContentVolumeFractionatSaturation();
  void resetEvapotranspirationGroundCoverParameter();
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
