/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEGROUP_HPP
#define EPMODEL_ZONEGROUP_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ZoneGroup_Impl;
  }

  class EPMODEL_API ZoneGroup : public ModelObject
  {
   public:
    explicit ZoneGroup(const Model& model);

    virtual ~ZoneGroup() override = default;
    ZoneGroup(const ZoneGroup& other) = default;
    ZoneGroup(ZoneGroup&& other) = default;
    ZoneGroup& operator=(const ZoneGroup&) = default;
    ZoneGroup& operator=(ZoneGroup&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - Field Mapping: zoneListMultiplier mirrors the EnergyPlus ZoneGroup "Zone List Multiplier" field.
    // - Field Mapping: Zone List Name is an object-list relationship, so it is excluded from the scalar API and should
    //   be handled via ModelObject target helpers when needed.
    // - TODO(parity): Add ZoneList relationship support once the Ruby generator completes non-scalar APIs.
    int zoneListMultiplier() const;
    bool setZoneListMultiplier(int zoneListMultiplier);
    bool isZoneListMultiplierDefaulted() const;
    void resetZoneListMultiplier();

   protected:
    using ImplType = detail::ZoneGroup_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ZoneGroup(std::shared_ptr<detail::ZoneGroup_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
