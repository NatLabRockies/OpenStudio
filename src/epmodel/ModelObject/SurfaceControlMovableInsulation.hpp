/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SURFACECONTROLMOVABLEINSULATION_HPP
#define EPMODEL_SURFACECONTROLMOVABLEINSULATION_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class SurfaceControlMovableInsulation_Impl;
  }

  /** \brief SurfaceControlMovableInsulation.
   *
   * \par EnergyPlus object
   * \epobject{group-advanced-surface-concepts.html#surfacecontrolmovableinsulation,SurfaceControl:MovableInsulation}.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::SurfaceControlMovableInsulation</code>. <b>Changed:</b> EPModel exposes direct construction from <code>Model</code>; Model construction requires a surface and material. Model relationship helpers for schedules and surfaces are not available.
   *
   * \par Known limitations
   * No known EPModel-specific limitations.
   */
  class EPMODEL_API SurfaceControlMovableInsulation : public ModelObject
  {
   public:
    explicit SurfaceControlMovableInsulation(const Model& model);

    virtual ~SurfaceControlMovableInsulation() override = default;
    SurfaceControlMovableInsulation(const SurfaceControlMovableInsulation& other) = default;
    SurfaceControlMovableInsulation(SurfaceControlMovableInsulation&& other) = default;
    SurfaceControlMovableInsulation& operator=(const SurfaceControlMovableInsulation&) = default;
    SurfaceControlMovableInsulation& operator=(SurfaceControlMovableInsulation&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> insulationTypeValues();

    /** @name Getters */
    //@{

    std::string insulationType() const;

    //@}

    /** @name Setters */
    //@{

    bool setInsulationType(const std::string& insulationType);

    //@}

   protected:
    using ImplType = detail::SurfaceControlMovableInsulation_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SurfaceControlMovableInsulation(std::shared_ptr<detail::SurfaceControlMovableInsulation_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
