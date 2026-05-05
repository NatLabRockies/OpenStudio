/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRLOOPHVACOUTDOORAIRSYSTEMEQUIPMENTLIST_IMPL_HPP
#define EPMODEL_AIRLOOPHVACOUTDOORAIRSYSTEMEQUIPMENTLIST_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <string_view>

namespace openstudio {
namespace epmodel {
  namespace detail {
    struct LoadContext;

    class EPMODEL_API AirLoopHVACOutdoorAirSystemEquipmentList_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~AirLoopHVACOutdoorAirSystemEquipmentList_Impl() override = default;

      std::vector<openstudio::epmodel::ModelObject> equipment() const;
      static bool isValidOASystemEquipmentTypeName(std::string_view typeName);
      static bool isValidOASystemEquipment(const openstudio::epmodel::ModelObject& component);
      bool addEquipment(const openstudio::epmodel::ModelObject& component);
      bool containsEquipment(const openstudio::epmodel::ModelObject& component) const;
      bool removeEquipment(const openstudio::epmodel::ModelObject& component);
      void doCanonicalize(LoadContext& context) override;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
