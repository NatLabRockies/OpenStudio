/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_PLANTEQUIPMENTOPERATIONUSERDEFINED_HPP
#define EPMODEL_PLANTEQUIPMENTOPERATIONUSERDEFINED_HPP

#include "EPModelAPI.hpp"
#include "PlantEquipmentOperationScheme.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class PlantEquipmentOperationUserDefined_Impl;
  }

  /** \brief Selects plant equipment for user defined operation.
   *
   * \par EnergyPlus object
   * \epobject{group-user-defined-hvac-and-plant-component.html#plantequipmentoperationuserdefined,PlantEquipmentOperation:UserDefined}
   *
   * \par OpenStudio Model API
   * OpenStudio Model has no public wrapper for
   * <code>PlantEquipmentOperation:UserDefined</code>; this wrapper is new to
   * the EPModel API.
   *
   * \par Known limitations
   * Program-calling-manager relationships and the extensible equipment rows
   * are not exposed through typed public methods.
   */
  class EPMODEL_API PlantEquipmentOperationUserDefined : public PlantEquipmentOperationScheme
  {
   public:
    explicit PlantEquipmentOperationUserDefined(const Model& model);

    virtual ~PlantEquipmentOperationUserDefined() override = default;
    PlantEquipmentOperationUserDefined(const PlantEquipmentOperationUserDefined& other) = default;
    PlantEquipmentOperationUserDefined(PlantEquipmentOperationUserDefined&& other) = default;
    PlantEquipmentOperationUserDefined& operator=(const PlantEquipmentOperationUserDefined&) = default;
    PlantEquipmentOperationUserDefined& operator=(PlantEquipmentOperationUserDefined&&) = default;

    static IddObjectType iddObjectType();


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
