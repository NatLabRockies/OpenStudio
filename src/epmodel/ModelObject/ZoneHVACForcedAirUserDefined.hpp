/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACFORCEDAIRUSERDEFINED_HPP
#define EPMODEL_ZONEHVACFORCEDAIRUSERDEFINED_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ZoneHVACForcedAirUserDefined_Impl;
  }

  class EPMODEL_API ZoneHVACForcedAirUserDefined : public ModelObject
  {
   public:
    explicit ZoneHVACForcedAirUserDefined(const Model& model);

    virtual ~ZoneHVACForcedAirUserDefined() override = default;
    ZoneHVACForcedAirUserDefined(const ZoneHVACForcedAirUserDefined& other) = default;
    ZoneHVACForcedAirUserDefined(ZoneHVACForcedAirUserDefined&& other) = default;
    ZoneHVACForcedAirUserDefined& operator=(const ZoneHVACForcedAirUserDefined&) = default;
    ZoneHVACForcedAirUserDefined& operator=(ZoneHVACForcedAirUserDefined&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: IDD-derived naming is preserved because there is no openstudio::model counterpart yet.
    // - Field Mapping: numberofPlantLoopConnections maps directly to EnergyPlus ZoneHVAC:ForcedAir:UserDefined "Number of Plant Loop Connections" field.
    // - Field Mapping: All node links, object-list references, and water storage tank names remain relationship-like and are intentionally excluded from the scalar API.
    // - TODO(parity): Add relationship helpers (node linking, water storage targets) after simple scalar saturation.
    /** @name Number of Plant Loop Connections */
    //@{
    int numberofPlantLoopConnections() const;
    bool setNumberofPlantLoopConnections(int numberofPlantLoopConnections);
    //@}

   protected:
    using ImplType = detail::ZoneHVACForcedAirUserDefined_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ZoneHVACForcedAirUserDefined(std::shared_ptr<detail::ZoneHVACForcedAirUserDefined_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
