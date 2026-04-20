/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACOUTDOORAIRUNITEQUIPMENTLIST_HPP
#define EPMODEL_ZONEHVACOUTDOORAIRUNITEQUIPMENTLIST_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ZoneHVACOutdoorAirUnitEquipmentList_Impl;
  }

  class EPMODEL_API ZoneHVACOutdoorAirUnitEquipmentList : public ModelObject
  {
   public:
    explicit ZoneHVACOutdoorAirUnitEquipmentList(const Model& model);

    virtual ~ZoneHVACOutdoorAirUnitEquipmentList() override = default;
    ZoneHVACOutdoorAirUnitEquipmentList(const ZoneHVACOutdoorAirUnitEquipmentList& other) = default;
    ZoneHVACOutdoorAirUnitEquipmentList(ZoneHVACOutdoorAirUnitEquipmentList&& other) = default;
    ZoneHVACOutdoorAirUnitEquipmentList& operator=(const ZoneHVACOutdoorAirUnitEquipmentList&) = default;
    ZoneHVACOutdoorAirUnitEquipmentList& operator=(ZoneHVACOutdoorAirUnitEquipmentList&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: IDD-derived ZoneHVAC:OutdoorAirUnit:EquipmentList naming is preserved to stay aligned with EnergyPlus.
    // - Field Mapping: Name remains exposed via the base ModelObject scalar API while Component # Object Type and
    //   Component # Name are relationship-like extensible link fields and intentionally excluded from scalar accessors.
    // - TODO(parity): Add relationship helpers (resolving component references) once scalar saturation is complete.

   protected:
    using ImplType = detail::ZoneHVACOutdoorAirUnitEquipmentList_Impl;

    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;
    friend class openstudio::epmodel::Model;

    explicit ZoneHVACOutdoorAirUnitEquipmentList(std::shared_ptr<detail::ZoneHVACOutdoorAirUnitEquipmentList_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
