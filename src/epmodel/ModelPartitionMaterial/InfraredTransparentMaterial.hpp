/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_INFRAREDTRANSPARENTMATERIAL_HPP
#define EPMODEL_INFRAREDTRANSPARENTMATERIAL_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class InfraredTransparentMaterial_Impl;
  }

  class EPMODEL_API InfraredTransparentMaterial : public ModelObject
  {
   public:
    explicit InfraredTransparentMaterial(const Model& model);

    virtual ~InfraredTransparentMaterial() override = default;
    InfraredTransparentMaterial(const InfraredTransparentMaterial& other) = default;
    InfraredTransparentMaterial(InfraredTransparentMaterial&& other) = default;
    InfraredTransparentMaterial& operator=(const InfraredTransparentMaterial&) = default;
    InfraredTransparentMaterial& operator=(InfraredTransparentMaterial&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: Preserves openstudio::model::InfraredTransparentMaterial class/API naming.
    // - Field Mapping: This object has no dedicated scalar fields in current E+ schema; base ModelObject name APIs apply.
    // - ForwardTranslator evidence: ForwardTranslateInfraredTransparentMaterial.cpp writes only Name.
    // - TODO(parity): Introduce an epmodel ModelPartitionMaterial base hierarchy and migrate inheritance when that parity work lands.

   protected:
    using ImplType = detail::InfraredTransparentMaterial_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit InfraredTransparentMaterial(std::shared_ptr<detail::InfraredTransparentMaterial_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
