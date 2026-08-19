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
  /** \brief SurfacePropertyGroundSurfaces.
   *
   * \par EnergyPlus object
   * \epobject{group-advanced-surface-concepts.html#surfacePropertyGroundSurfaces,SurfaceProperty:GroundSurfaces}.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::SurfacePropertyGroundSurfaces</code>. EPModel currently exposes only the object identity; ground-surface groups and the local-environment relationship are not public APIs.
   *
   * \par Known limitations
   * No known EPModel-specific limitations.
   */
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
