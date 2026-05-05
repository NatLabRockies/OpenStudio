/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRLOOPHVACOUTDOORAIRSYSTEMEQUIPMENTLIST_HPP
#define EPMODEL_AIRLOOPHVACOUTDOORAIRSYSTEMEQUIPMENTLIST_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include "../utilities/idd/IddEnums.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class AirLoopHVACOutdoorAirSystemEquipmentList_Impl;
  }

  class EPMODEL_API AirLoopHVACOutdoorAirSystemEquipmentList : public ModelObject
  {
   public:
    explicit AirLoopHVACOutdoorAirSystemEquipmentList(const Model& model);

    virtual ~AirLoopHVACOutdoorAirSystemEquipmentList() override = default;
    AirLoopHVACOutdoorAirSystemEquipmentList(const AirLoopHVACOutdoorAirSystemEquipmentList& other) = default;
    AirLoopHVACOutdoorAirSystemEquipmentList(AirLoopHVACOutdoorAirSystemEquipmentList&& other) = default;
    AirLoopHVACOutdoorAirSystemEquipmentList& operator=(const AirLoopHVACOutdoorAirSystemEquipmentList&) = default;
    AirLoopHVACOutdoorAirSystemEquipmentList& operator=(AirLoopHVACOutdoorAirSystemEquipmentList&&) = default;

    // Schema Alignment Notes:
    // - API: This no-counterpart type keeps IDD-derived class/API naming.
    // - Field Mapping: Name remains available through base ModelObject scalar API.
    // - Field Mapping: Extensible fields (Component Object Type, Component Name) are relationship-like link fields and excluded from scalar accessors.
    // - TODO(parity): Add relationship parity APIs incrementally after scalar saturation.
    std::vector<ModelObject> equipment() const;
    static IddObjectType iddObjectType();

   protected:
    using ImplType = detail::AirLoopHVACOutdoorAirSystemEquipmentList_Impl;

    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;
    friend class Model;

    explicit AirLoopHVACOutdoorAirSystemEquipmentList(std::shared_ptr<detail::AirLoopHVACOutdoorAirSystemEquipmentList_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
