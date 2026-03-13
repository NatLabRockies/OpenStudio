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
      bool setSoilThermalConductivity(double soilThermalConductivity);

      double soilDensity() const;
      bool setSoilDensity(double soilDensity);

      double soilSpecificHeat() const;
      bool setSoilSpecificHeat(double soilSpecificHeat);

      double soilMoistureContentVolumeFraction() const;
      bool isSoilMoistureContentVolumeFractionDefaulted() const;
      bool setSoilMoistureContentVolumeFraction(double soilMoistureContentVolumeFraction);
      void resetSoilMoistureContentVolumeFraction();

      double soilMoistureContentVolumeFractionatSaturation() const;
      bool isSoilMoistureContentVolumeFractionatSaturationDefaulted() const;
      bool setSoilMoistureContentVolumeFractionatSaturation(double soilMoistureContentVolumeFractionatSaturation);
      void resetSoilMoistureContentVolumeFractionatSaturation();

      double evapotranspirationGroundCoverParameter() const;
      bool isEvapotranspirationGroundCoverParameterDefaulted() const;
      bool setEvapotranspirationGroundCoverParameter(double evapotranspirationGroundCoverParameter);
      void resetEvapotranspirationGroundCoverParameter();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
