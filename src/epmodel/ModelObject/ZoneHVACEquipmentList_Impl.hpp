/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACEQUIPMENTLIST_IMPL_HPP
#define EPMODEL_ZONEHVACEQUIPMENTLIST_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {
  namespace detail {

    class EPMODEL_API ZoneHVACEquipmentList_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~ZoneHVACEquipmentList_Impl() override = default;

      std::string loadDistributionScheme() const;
      bool isLoadDistributionSchemeDefaulted() const;
      bool setLoadDistributionScheme(const std::string& loadDistributionScheme);
      void resetLoadDistributionScheme();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
