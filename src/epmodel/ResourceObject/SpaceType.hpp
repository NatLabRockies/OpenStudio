/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SPACETYPE_HPP
#define EPMODEL_SPACETYPE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class SpaceType_Impl;
  }

  class EPMODEL_API SpaceType : public ModelObject
  {
   public:
    explicit SpaceType(const Model& model);

    virtual ~SpaceType() override = default;
    SpaceType(const SpaceType& other) = default;
    SpaceType(SpaceType&& other) = default;
    SpaceType& operator=(const SpaceType&) = default;
    SpaceType& operator=(SpaceType&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - IDD type: SpaceList (EnergyPlus). Target class: SpaceType (openstudio::model counterpart).
    // - API: Preserves openstudio::model counterpart naming (`SpaceType`).
    // - Field Mapping: The EnergyPlus SpaceList IDD object has only one non-extensible field: Name
    //   (field index 0). All remaining fields are extensible "Space Name" entries which are
    //   \object-list relationship fields and are excluded from scalar scaffold APIs.
    // - ForwardTranslator evidence: openstudio::model::SpaceType forward-translates to
    //   SpaceList (Name field only for non-relationship content).
    // - Field Mapping: Name remains available through inherited ModelObject scalar accessors.
    // - TODO(parity): Add Space membership relationship methods in a dedicated parity pass.

   protected:
    using ImplType = detail::SpaceType_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SpaceType(std::shared_ptr<detail::SpaceType_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
