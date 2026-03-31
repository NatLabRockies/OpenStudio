/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_PLANTEQUIPMENTOPERATIONUNCONTROLLED_HPP
#define EPMODEL_PLANTEQUIPMENTOPERATIONUNCONTROLLED_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class PlantEquipmentOperationUncontrolled_Impl;
  }

  class EPMODEL_API PlantEquipmentOperationUncontrolled : public ModelObject
  {
   public:
    explicit PlantEquipmentOperationUncontrolled(const Model& model);

    virtual ~PlantEquipmentOperationUncontrolled() override = default;
    PlantEquipmentOperationUncontrolled(const PlantEquipmentOperationUncontrolled& other) = default;
    PlantEquipmentOperationUncontrolled(PlantEquipmentOperationUncontrolled&& other) = default;
    PlantEquipmentOperationUncontrolled& operator=(const PlantEquipmentOperationUncontrolled&) = default;
    PlantEquipmentOperationUncontrolled& operator=(PlantEquipmentOperationUncontrolled&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: IDD-derived name follows EnergyPlus IDD PlantEquipmentOperation:Uncontrolled.
    // - Field Mapping: Name remains available through the base ModelObject scalar API.
    // - Field Mapping: Equipment List Name is a PlantAndCondenserEquipmentLists object list (see PlantEquipmentOperation_UncontrolledFields::EquipmentListName and ForwardTranslatePlantEquipmentOperationSchemes mapping) and is intentionally excluded from scalar accessors.
    // - TODO(parity): Add helper APIs for the referenced PlantAndCondenserEquipmentLists once scalar parity work is complete.

   protected:
    using ImplType = detail::PlantEquipmentOperationUncontrolled_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit PlantEquipmentOperationUncontrolled(std::shared_ptr<detail::PlantEquipmentOperationUncontrolled_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
