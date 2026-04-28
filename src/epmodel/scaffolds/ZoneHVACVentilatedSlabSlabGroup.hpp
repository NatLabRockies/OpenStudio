/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACVENTILATEDSLABSLABGROUP_HPP
#define EPMODEL_ZONEHVACVENTILATEDSLABSLABGROUP_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ZoneHVACVentilatedSlabSlabGroup_Impl;
  }

  class EPMODEL_API ZoneHVACVentilatedSlabSlabGroup : public ModelObject
  {
   public:
    explicit ZoneHVACVentilatedSlabSlabGroup(const Model& model);

    virtual ~ZoneHVACVentilatedSlabSlabGroup() override = default;
    ZoneHVACVentilatedSlabSlabGroup(const ZoneHVACVentilatedSlabSlabGroup& other) = default;
    ZoneHVACVentilatedSlabSlabGroup(ZoneHVACVentilatedSlabSlabGroup&& other) = default;
    ZoneHVACVentilatedSlabSlabGroup& operator=(const ZoneHVACVentilatedSlabSlabGroup&) = default;
    ZoneHVACVentilatedSlabSlabGroup& operator=(ZoneHVACVentilatedSlabSlabGroup&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: Derived from the EnergyPlus ZoneHVAC:VentilatedSlab:SlabGroup IDD entry; this scalar-only API currently stays at the
    //   inherited Name field because no additional non-extensible scalars exist in the object.
    // - Field Mapping: All relationship-like data (zone/surface memberships, inlet/outlet nodes, and the core diameter/length/numbers)
    //   live inside the extensible group enumerated by ZoneHVAC_VentilatedSlab_SlabGroupExtensibleFields and are intentionally excluded
    //   from the scalar scaffold pass.
    // - TODO(parity): Add typed helpers for the extensible surface/core groups once non-scalar parity efforts begin without altering
    //   the current scalar surface.

   protected:
    using ImplType = detail::ZoneHVACVentilatedSlabSlabGroup_Impl;

    explicit ZoneHVACVentilatedSlabSlabGroup(std::shared_ptr<detail::ZoneHVACVentilatedSlabSlabGroup_Impl> impl);

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;
  };

}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_ZONEHVACVENTILATEDSLABSLABGROUP_HPP
