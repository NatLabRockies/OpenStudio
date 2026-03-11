/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_SURFACEPROPERTYSOLARINCIDENTINSIDE_HPP
#define EPMODEL_SURFACEPROPERTYSOLARINCIDENTINSIDE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class SurfacePropertySolarIncidentInside_Impl;
  }

  class EPMODEL_API SurfacePropertySolarIncidentInside : public ModelObject
  {
   public:
    explicit SurfacePropertySolarIncidentInside(const Model& model);

    virtual ~SurfacePropertySolarIncidentInside() override = default;
    SurfacePropertySolarIncidentInside(const SurfacePropertySolarIncidentInside& other) = default;
    SurfacePropertySolarIncidentInside(SurfacePropertySolarIncidentInside&& other) = default;
    SurfacePropertySolarIncidentInside& operator=(const SurfacePropertySolarIncidentInside&) = default;
    SurfacePropertySolarIncidentInside& operator=(SurfacePropertySolarIncidentInside&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: No openstudio::model counterpart exists, so we honor the IDD-derived SurfacePropertySolarIncidentInside naming
    //   and currently expose only the required Name scalar.
    // - Field Mapping: Name maps directly to the SurfaceProperty:SolarIncidentInside Name field; Surface Name,
    //   Construction Name, and Inside Surface Incident Sun Solar Radiation Schedule Name remain object-list relationships and are
    //   intentionally excluded from this scalar-only pass.
    // - TODO(parity): Provide relationship helpers once schema saturation progresses beyond the scalar-only checkpoint.

   protected:
    using ImplType = detail::SurfacePropertySolarIncidentInside_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SurfacePropertySolarIncidentInside(std::shared_ptr<detail::SurfacePropertySolarIncidentInside_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
