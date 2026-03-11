/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_SITEGROUNDREFLECTANCESNOWMODIFIER_IMPL_HPP
#define EPMODEL_SITEGROUNDREFLECTANCESNOWMODIFIER_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API SiteGroundReflectanceSnowModifier_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~SiteGroundReflectanceSnowModifier_Impl() override = default;

      double groundReflectedSolarModifier() const;
      bool isGroundReflectedSolarModifierDefaulted() const;
      bool setGroundReflectedSolarModifier(double groundReflectedSolarModifier);
      void resetGroundReflectedSolarModifier();

      double daylightingGroundReflectedSolarModifier() const;
      bool isDaylightingGroundReflectedSolarModifierDefaulted() const;
      bool setDaylightingGroundReflectedSolarModifier(double daylightingGroundReflectedSolarModifier);
      void resetDaylightingGroundReflectedSolarModifier();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_SITEGROUNDREFLECTANCESNOWMODIFIER_IMPL_HPP
