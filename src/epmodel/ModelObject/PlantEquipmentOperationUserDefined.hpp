/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_PLANTEQUIPMENTOPERATIONUSERDEFINED_HPP
#define EPMODEL_PLANTEQUIPMENTOPERATIONUSERDEFINED_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class PlantEquipmentOperationUserDefined_Impl;
  }

  class EPMODEL_API PlantEquipmentOperationUserDefined : public ModelObject
  {
   public:
    explicit PlantEquipmentOperationUserDefined(const Model& model);

    virtual ~PlantEquipmentOperationUserDefined() override = default;
    PlantEquipmentOperationUserDefined(const PlantEquipmentOperationUserDefined& other) = default;
    PlantEquipmentOperationUserDefined(PlantEquipmentOperationUserDefined&& other) = default;
    PlantEquipmentOperationUserDefined& operator=(const PlantEquipmentOperationUserDefined&) = default;
    PlantEquipmentOperationUserDefined& operator=(PlantEquipmentOperationUserDefined&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: IDD-derived PlantEquipmentOperation:UserDefined naming is preserved per the EnergyPlus IDD.
    // - Field Mapping: Name is exposed through the base ModelObject scalar API.
    // - Field Mapping: Main Model Program Calling Manager Name, Initialization Program Calling Manager Name, and the extensible Equipment Object Type/Name pairs are relationship-like object-list concepts and intentionally excluded from this scalar-only pass.
    // - TODO(parity): Add targeted helpers for the excluded program/equipment references once extensible/relationship support is required.

   protected:
    using ImplType = detail::PlantEquipmentOperationUserDefined_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit PlantEquipmentOperationUserDefined(std::shared_ptr<detail::PlantEquipmentOperationUserDefined_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
