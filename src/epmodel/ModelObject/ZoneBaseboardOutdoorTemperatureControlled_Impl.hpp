/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEBASEBOARDOUTDOORTEMPERATURECONTROLLED_IMPL_HPP
#define EPMODEL_ZONEBASEBOARDOUTDOORTEMPERATURECONTROLLED_IMPL_HPP

#include "ModelObject_Impl.hpp"
#include <string>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API ZoneBaseboardOutdoorTemperatureControlled_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~ZoneBaseboardOutdoorTemperatureControlled_Impl() override = default;

      double capacityAtLowTemperature() const;
      bool setCapacityAtLowTemperature(double capacityAtLowTemperature);

      double lowTemperature() const;
      bool setLowTemperature(double lowTemperature);

      double capacityAtHighTemperature() const;
      bool setCapacityAtHighTemperature(double capacityAtHighTemperature);

      double highTemperature() const;
      bool setHighTemperature(double highTemperature);

      double fractionRadiant() const;
      bool setFractionRadiant(double fractionRadiant);
      bool isFractionRadiantDefaulted() const;
      void resetFractionRadiant();

      std::string endUseSubcategory() const;
      bool setEndUseSubcategory(const std::string& endUseSubcategory);
      bool isEndUseSubcategoryDefaulted() const;
      void resetEndUseSubcategory();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
