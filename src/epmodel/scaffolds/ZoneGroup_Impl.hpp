/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEGROUP_IMPL_HPP
#define EPMODEL_ZONEGROUP_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API ZoneGroup_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~ZoneGroup_Impl() override = default;

      int zoneListMultiplier() const;
      bool setZoneListMultiplier(int zoneListMultiplier);

      bool isZoneListMultiplierDefaulted() const;
      void resetZoneListMultiplier();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
