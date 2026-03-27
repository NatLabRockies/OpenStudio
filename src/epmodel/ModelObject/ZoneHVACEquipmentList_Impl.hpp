/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACEQUIPMENTLIST_IMPL_HPP
#define EPMODEL_ZONEHVACEQUIPMENTLIST_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {
  class ModelObject;
  namespace detail {

    class EPMODEL_API ZoneHVACEquipmentList_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~ZoneHVACEquipmentList_Impl() override = default;

      std::string loadDistributionScheme() const;
      bool setLoadDistributionScheme(const std::string& loadDistributionScheme);
      bool isLoadDistributionSchemeDefaulted() const;
      void resetLoadDistributionScheme();
      std::vector<openstudio::epmodel::ModelObject> equipment() const;
      bool addEquipment(const openstudio::epmodel::ModelObject& component);
      bool removeEquipment(const openstudio::epmodel::ModelObject& component);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
