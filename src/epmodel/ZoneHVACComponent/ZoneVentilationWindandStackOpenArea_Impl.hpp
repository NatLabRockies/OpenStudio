/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEVENTILATIONWINDANDSTACKOPENAREA_IMPL_HPP
#define EPMODEL_ZONEVENTILATIONWINDANDSTACKOPENAREA_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <boost/optional.hpp>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API ZoneVentilationWindandStackOpenArea_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~ZoneVentilationWindandStackOpenArea_Impl() override = default;

      double openingArea() const;
      bool setOpeningArea(double openingArea);

      boost::optional<double> openingEffectiveness() const;
      bool isOpeningEffectivenessAutocalculated() const;
      bool setOpeningEffectiveness(double openingEffectiveness);
      void autocalculateOpeningEffectiveness();

      double effectiveAngle() const;
      bool setEffectiveAngle(double effectiveAngle);

      double heightDifference() const;
      bool setHeightDifference(double heightDifference);

      boost::optional<double> dischargeCoefficientforOpening() const;
      bool isDischargeCoefficientforOpeningAutocalculated() const;
      bool setDischargeCoefficientforOpening(double dischargeCoefficientforOpening);
      void autocalculateDischargeCoefficientforOpening();

      double minimumIndoorTemperature() const;
      bool setMinimumIndoorTemperature(double minimumIndoorTemperature);

      double maximumIndoorTemperature() const;
      bool setMaximumIndoorTemperature(double maximumIndoorTemperature);

      double deltaTemperature() const;
      bool setDeltaTemperature(double deltaTemperature);

      double minimumOutdoorTemperature() const;
      bool setMinimumOutdoorTemperature(double minimumOutdoorTemperature);

      double maximumOutdoorTemperature() const;
      bool setMaximumOutdoorTemperature(double maximumOutdoorTemperature);

      double maximumWindSpeed() const;
      bool setMaximumWindSpeed(double maximumWindSpeed);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
