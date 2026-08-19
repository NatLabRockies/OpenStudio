/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_SURFACEPROPERTYLOCALENVIRONMENT_HPP
#define EPMODEL_SURFACEPROPERTYLOCALENVIRONMENT_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class SurfacePropertyLocalEnvironment_Impl;
  }

  /** \brief SurfacePropertyLocalEnvironment.
   *
   * \par EnergyPlus object
   * \epobject{group-advanced-surface-concepts.html#surfacePropertylocalEnvironment,SurfaceProperty:LocalEnvironment}.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::SurfacePropertyLocalEnvironment</code>. <b>Changed:</b> EPModel exposes direct construction from <code>Model</code>; Model construction requires a surface or subsurface. The object identity is exposed, but Model's surface, schedule, surrounding-surface, outdoor-air-node, and ground-surface relationships are not available.
   *
   * \par Known limitations
   * No known EPModel-specific limitations.
   */
  class EPMODEL_API SurfacePropertyLocalEnvironment : public ModelObject
  {
   public:
    explicit SurfacePropertyLocalEnvironment(const Model& model);

    virtual ~SurfacePropertyLocalEnvironment() override = default;
    SurfacePropertyLocalEnvironment(const SurfacePropertyLocalEnvironment& other) = default;
    SurfacePropertyLocalEnvironment(SurfacePropertyLocalEnvironment&& other) = default;
    SurfacePropertyLocalEnvironment& operator=(const SurfacePropertyLocalEnvironment&) = default;
    SurfacePropertyLocalEnvironment& operator=(SurfacePropertyLocalEnvironment&&) = default;

    static IddObjectType iddObjectType();

   protected:
    using ImplType = detail::SurfacePropertyLocalEnvironment_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SurfacePropertyLocalEnvironment(std::shared_ptr<detail::SurfacePropertyLocalEnvironment_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
