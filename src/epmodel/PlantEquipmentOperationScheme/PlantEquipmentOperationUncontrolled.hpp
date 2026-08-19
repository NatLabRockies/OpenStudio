/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_PLANTEQUIPMENTOPERATIONUNCONTROLLED_HPP
#define EPMODEL_PLANTEQUIPMENTOPERATIONUNCONTROLLED_HPP

#include "EPModelAPI.hpp"
#include "PlantEquipmentOperationScheme.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class PlantEquipmentOperationUncontrolled_Impl;
  }

  /** \brief Selects plant equipment for uncontrolled operation.
   *
   * \par EnergyPlus object
   * \epobject{group-plant-condenser-control.html#plantequipmentoperationuncontrolled,PlantEquipmentOperation:Uncontrolled}
   *
   * \par OpenStudio Model API
   * OpenStudio Model has no public wrapper for
   * <code>PlantEquipmentOperation:Uncontrolled</code>; this wrapper is new to
   * the EPModel API.
   *
   * \par Known limitations
   * The required equipment-list relationship is not exposed through typed
   * public methods.
   */
  class EPMODEL_API PlantEquipmentOperationUncontrolled : public PlantEquipmentOperationScheme
  {
   public:
    explicit PlantEquipmentOperationUncontrolled(const Model& model);

    virtual ~PlantEquipmentOperationUncontrolled() override = default;
    PlantEquipmentOperationUncontrolled(const PlantEquipmentOperationUncontrolled& other) = default;
    PlantEquipmentOperationUncontrolled(PlantEquipmentOperationUncontrolled&& other) = default;
    PlantEquipmentOperationUncontrolled& operator=(const PlantEquipmentOperationUncontrolled&) = default;
    PlantEquipmentOperationUncontrolled& operator=(PlantEquipmentOperationUncontrolled&&) = default;

    static IddObjectType iddObjectType();


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
