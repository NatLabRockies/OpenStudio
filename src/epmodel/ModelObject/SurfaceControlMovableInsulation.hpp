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

    // Schema Alignment Notes:
    // - API: Preserve openstudio::model SurfaceControlMovableInsulation scalar accessor names/signatures.
    // - Field Mapping: insulationType maps directly to E+ SurfaceControl:MovableInsulation InsulationType field.
    // - Field Mapping: SurfaceName, MaterialName, ScheduleName are relationship fields and excluded from this scaffold.
    // - TODO(parity): Add non-scalar relationship APIs incrementally after scalar saturation.

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
