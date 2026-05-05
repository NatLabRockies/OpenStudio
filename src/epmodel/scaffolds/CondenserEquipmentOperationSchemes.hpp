/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CONDENSEREQUIPMENTOPERATIONSCHEMES_HPP
#define EPMODEL_CONDENSEREQUIPMENTOPERATIONSCHEMES_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class CondenserEquipmentOperationSchemes_Impl;
  }

  class EPMODEL_API CondenserEquipmentOperationSchemes : public ModelObject
  {
   public:
    explicit CondenserEquipmentOperationSchemes(const Model& model);

    virtual ~CondenserEquipmentOperationSchemes() override = default;
    CondenserEquipmentOperationSchemes(const CondenserEquipmentOperationSchemes& other) = default;
    CondenserEquipmentOperationSchemes(CondenserEquipmentOperationSchemes&& other) = default;
    CondenserEquipmentOperationSchemes& operator=(const CondenserEquipmentOperationSchemes&) = default;
    CondenserEquipmentOperationSchemes& operator=(CondenserEquipmentOperationSchemes&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: This no-counterpart type keeps IDD-derived class/API naming.
    // - Field Mapping: Name remains available through base ModelObject scalar API.
    // - Field Mapping: Extensible fields (Control Scheme Object Type, Control Scheme Name, Control Scheme Schedule Name)
    //   are relationship-like link fields and excluded from scalar accessors.
    // - TODO(parity): Add relationship APIs incrementally after scalar saturation.

   protected:
    using ImplType = detail::CondenserEquipmentOperationSchemes_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit CondenserEquipmentOperationSchemes(std::shared_ptr<detail::CondenserEquipmentOperationSchemes_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
