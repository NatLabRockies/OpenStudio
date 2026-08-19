/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_SURFACEPROPERTYSURROUNDINGSURFACES_HPP
#define EPMODEL_SURFACEPROPERTYSURROUNDINGSURFACES_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class SurfacePropertySurroundingSurfaces_Impl;
  }

  /** \brief SurfacePropertySurroundingSurfaces.
   *
   * \par EnergyPlus object
   * \epobject{group-advanced-surface-concepts.html#surfacePropertySurroundingSurfaces,SurfaceProperty:SurroundingSurfaces}.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::SurfacePropertySurroundingSurfaces</code>. The sky and ground view factors, including autocalculate behavior, are exposed. Schedule and surrounding-surface extensible relationships are not available.
   *
   * \par Known limitations
   * No known EPModel-specific limitations.
   */
  class EPMODEL_API SurfacePropertySurroundingSurfaces : public ModelObject
  {
   public:
    explicit SurfacePropertySurroundingSurfaces(const Model& model);

    virtual ~SurfacePropertySurroundingSurfaces() override = default;
    SurfacePropertySurroundingSurfaces(const SurfacePropertySurroundingSurfaces& other) = default;
    SurfacePropertySurroundingSurfaces(SurfacePropertySurroundingSurfaces&& other) = default;
    SurfacePropertySurroundingSurfaces& operator=(const SurfacePropertySurroundingSurfaces&) = default;
    SurfacePropertySurroundingSurfaces& operator=(SurfacePropertySurroundingSurfaces&&) = default;

    static IddObjectType iddObjectType();
    boost::optional<double> skyViewFactor() const;
    bool setSkyViewFactor(double skyViewFactor);
    bool isSkyViewFactorAutocalculated() const;
    void autocalculateSkyViewFactor();

    boost::optional<double> groundViewFactor() const;
    bool setGroundViewFactor(double groundViewFactor);
    bool isGroundViewFactorAutocalculated() const;
    void autocalculateGroundViewFactor();

   protected:
    using ImplType = detail::SurfacePropertySurroundingSurfaces_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SurfacePropertySurroundingSurfaces(std::shared_ptr<detail::SurfacePropertySurroundingSurfaces_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
