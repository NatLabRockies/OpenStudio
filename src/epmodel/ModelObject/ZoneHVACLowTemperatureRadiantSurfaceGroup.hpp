/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACLOWTEMPERATURERADIANTSURFACEGROUP_HPP
#define EPMODEL_ZONEHVACLOWTEMPERATURERADIANTSURFACEGROUP_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class Surface;

  namespace detail {
    class ZoneHVACLowTemperatureRadiantSurfaceGroup_Impl;
  }

  class EPMODEL_API ZoneHVACLowTemperatureRadiantSurfaceGroup : public ModelObject
  {
   public:
    explicit ZoneHVACLowTemperatureRadiantSurfaceGroup(const Model& model);

    virtual ~ZoneHVACLowTemperatureRadiantSurfaceGroup() override = default;
    ZoneHVACLowTemperatureRadiantSurfaceGroup(const ZoneHVACLowTemperatureRadiantSurfaceGroup& other) = default;
    ZoneHVACLowTemperatureRadiantSurfaceGroup(ZoneHVACLowTemperatureRadiantSurfaceGroup&& other) = default;
    ZoneHVACLowTemperatureRadiantSurfaceGroup& operator=(const ZoneHVACLowTemperatureRadiantSurfaceGroup&) = default;
    ZoneHVACLowTemperatureRadiantSurfaceGroup& operator=(ZoneHVACLowTemperatureRadiantSurfaceGroup&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - Status: Scalar Parity. This is the real persisted EnergyPlus surface-group companion object used by the low-temperature radiant families.
    // - Canonical Counterpart: none. Canonical openstudio::model keeps higher-level radiant-surface intent on the parent wrapper instead of
    //   exposing the emitted EnergyPlus group object directly.
    // - Why This Wrapper Exists: epmodel is anchored to EnergyPlus storage, and the radiant parent now uses this object as the persisted backing
    //   store for canonical `radiantSurfaceType()` / `surfaces()` behavior.
    // - Documented Delta: this wrapper is intentionally thin for now. As the envelope portion of epmodel matures, richer surface-group behavior
    //   may move here and let the parent stop doing some low-level field work directly.

    // This is an EnergyPlus-only emitted companion type with no canonical
    // public peer. Keep the public wrapper read-oriented for now and reserve
    // mutation for the owning parent and `*_Impl` code paths.
    std::vector<Surface> surfaces() const;
    std::vector<double> flowFractions() const;

   protected:
    using ImplType = detail::ZoneHVACLowTemperatureRadiantSurfaceGroup_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ZoneHVACLowTemperatureRadiantSurfaceGroup(std::shared_ptr<detail::ZoneHVACLowTemperatureRadiantSurfaceGroup_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
