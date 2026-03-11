/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SURFACEPROPERTYGROUNDSURFACES_HPP
#define EPMODEL_SURFACEPROPERTYGROUNDSURFACES_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class SurfacePropertyGroundSurfaces_Impl;
  }

  // Schema Alignment Notes:
  // - API: All scalar work for SurfaceProperty:GroundSurfaces is routed through the base ModelObject name API because
  //   the E+ object only exposes Name plus Ground Surface extensible properties.
  // - Field Mapping: Name maps directly to openstudio::detail::WorkspaceObject, while the extensible Ground Surface groups
  //   (Name, View Factor, Temperature Schedule, Reflectance Schedule) are relationship-like and excluded by contract.
  // - TODO(parity): Add extensible helpers without touching the scalar accessor surface once non-scalar parity work begins.
  class EPMODEL_API SurfacePropertyGroundSurfaces : public ModelObject
  {
   public:
    explicit SurfacePropertyGroundSurfaces(const Model& model);

    virtual ~SurfacePropertyGroundSurfaces() override = default;
    SurfacePropertyGroundSurfaces(const SurfacePropertyGroundSurfaces& other) = default;
    SurfacePropertyGroundSurfaces(SurfacePropertyGroundSurfaces&& other) = default;
    SurfacePropertyGroundSurfaces& operator=(const SurfacePropertyGroundSurfaces&) = default;
    SurfacePropertyGroundSurfaces& operator=(SurfacePropertyGroundSurfaces&&) = default;

    static IddObjectType iddObjectType();

   protected:
    using ImplType = detail::SurfacePropertyGroundSurfaces_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SurfacePropertyGroundSurfaces(std::shared_ptr<detail::SurfacePropertyGroundSurfaces_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
