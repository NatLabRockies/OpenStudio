/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CONDENSEREQUIPMENTLIST_HPP
#define EPMODEL_CONDENSEREQUIPMENTLIST_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class CondenserEquipmentList_Impl;
}

class EPMODEL_API CondenserEquipmentList : public ModelObject
{
 public:
  explicit CondenserEquipmentList(const Model& model);

  virtual ~CondenserEquipmentList() override = default;
  CondenserEquipmentList(const CondenserEquipmentList& other) = default;
  CondenserEquipmentList(CondenserEquipmentList&& other) = default;
  CondenserEquipmentList& operator=(const CondenserEquipmentList&) = default;
  CondenserEquipmentList& operator=(CondenserEquipmentList&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: This no-counterpart type keeps IDD-derived class/API naming.
  // - Field Mapping: Name remains available through base ModelObject scalar API.
  // - Field Mapping: Equipment 1 Object Type and Equipment 1 Name are relationship-like extensible link fields and excluded from scalar accessors.
  // - TODO(parity): Add relationship APIs incrementally after scalar saturation.

 protected:
  using ImplType = detail::CondenserEquipmentList_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit CondenserEquipmentList(std::shared_ptr<detail::CondenserEquipmentList_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
