/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CONSTRUCTIONWINDOWEQUIVALENTLAYER_HPP
#define EPMODEL_CONSTRUCTIONWINDOWEQUIVALENTLAYER_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ConstructionWindowEquivalentLayer_Impl;
  }

  class EPMODEL_API ConstructionWindowEquivalentLayer : public ModelObject
  {
   public:
    explicit ConstructionWindowEquivalentLayer(const Model& model);

    virtual ~ConstructionWindowEquivalentLayer() override = default;
    ConstructionWindowEquivalentLayer(const ConstructionWindowEquivalentLayer& other) = default;
    ConstructionWindowEquivalentLayer(ConstructionWindowEquivalentLayer&& other) = default;
    ConstructionWindowEquivalentLayer& operator=(const ConstructionWindowEquivalentLayer&) = default;
    ConstructionWindowEquivalentLayer& operator=(ConstructionWindowEquivalentLayer&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: This no-counterpart type keeps IDD-derived class/API naming.
    // - Field Mapping: Name remains available through base ModelObject scalar API.
    // - Field Mapping: Outside Layer and Layer 2..11 are object-list relationship fields and excluded from scalar accessors.
    // - TODO(parity): Add relationship APIs incrementally after scalar saturation.

   protected:
    using ImplType = detail::ConstructionWindowEquivalentLayer_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ConstructionWindowEquivalentLayer(std::shared_ptr<detail::ConstructionWindowEquivalentLayer_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
