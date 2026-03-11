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

    // Schema Alignment Notes:
    // - API: Preserves openstudio::model::SurfacePropertyLocalEnvironment naming and constrains the current surface-local scalar exposure to the required Name field.
    // - Field Mapping: The object name maps to the SurfaceProperty:LocalEnvironment Name field, while all exterior surface, schedule, surrounding surfaces, outdoor air node,
    //   and ground surfaces fields remain relationship references excluded from this scalar pass.
    // - ForwardTranslator evidence: ForwardTranslateSurfacePropertyLocalEnvironment continues to drive the preserved relationship wiring.
    // - TODO(parity): Layer in relationship helpers after the scalar saturation milestone settles.

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
