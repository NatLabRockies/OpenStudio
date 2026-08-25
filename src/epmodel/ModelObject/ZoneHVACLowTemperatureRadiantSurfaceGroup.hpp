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

  /** \brief ZoneHVACLowTemperatureRadiantSurfaceGroup.
   *
   * \par EnergyPlus object
   * \epobject{group-radiative-convective-units.html#zonehvaclowtemperatureradiantsurfacegroup,ZoneHVAC:LowTemperatureRadiant:SurfaceGroup}.
   *
   * \par OpenStudio Model API
   * There is no corresponding OpenStudio Model class. This thin companion exposes the persisted radiant-surface group used by the low-temperature radiant families, including read-only surface and flow-fraction queries.
   *
   * \par Known limitations
   * The surface and flow-fraction rows cannot be edited through this wrapper.
   */
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
