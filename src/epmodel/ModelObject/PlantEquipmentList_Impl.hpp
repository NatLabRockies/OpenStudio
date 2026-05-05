/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_PLANTEQUIPMENTLIST_IMPL_HPP
#define EPMODEL_PLANTEQUIPMENTLIST_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  class HVACComponent;

  namespace detail {

    class EPMODEL_API PlantEquipmentList_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~PlantEquipmentList_Impl() override = default;

      std::vector<openstudio::epmodel::HVACComponent> equipment() const;
      bool addEquipment(const openstudio::epmodel::HVACComponent& equipment);
      bool removeEquipment(const openstudio::epmodel::HVACComponent& equipment);
      void removeAllEquipment();
      bool replaceEquipment(const std::vector<openstudio::epmodel::HVACComponent>& equipment);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
