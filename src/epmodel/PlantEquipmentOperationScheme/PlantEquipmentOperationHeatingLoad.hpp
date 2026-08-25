/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_PLANTEQUIPMENTOPERATIONHEATINGLOAD_HPP
#define EPMODEL_PLANTEQUIPMENTOPERATIONHEATINGLOAD_HPP

#include "EPModelAPI.hpp"
#include "PlantEquipmentOperationScheme/PlantEquipmentOperationRangeBasedScheme.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <utility>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class PlantEquipmentOperationHeatingLoad_Impl;
  }

  /** \brief Selects plant equipment for heating load operation.
   *
   * \par EnergyPlus object
   * \epobject{group-plant-condenser-control.html#plantequipmentoperationheatingload,PlantEquipmentOperation:HeatingLoad}
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::PlantEquipmentOperationHeatingLoad</code>.
   * No known public API differences.
   *
   * \par Known limitations
   * No known EPModel-specific limitations.
   */
  class EPMODEL_API PlantEquipmentOperationHeatingLoad : public PlantEquipmentOperationRangeBasedScheme
  {
   public:
    explicit PlantEquipmentOperationHeatingLoad(const Model& model);

    virtual ~PlantEquipmentOperationHeatingLoad() override = default;
    PlantEquipmentOperationHeatingLoad(const PlantEquipmentOperationHeatingLoad& other) = default;
    PlantEquipmentOperationHeatingLoad(PlantEquipmentOperationHeatingLoad&& other) = default;
    PlantEquipmentOperationHeatingLoad& operator=(const PlantEquipmentOperationHeatingLoad&) = default;
    PlantEquipmentOperationHeatingLoad& operator=(PlantEquipmentOperationHeatingLoad&&) = default;

    static IddObjectType iddObjectType();


   protected:
    using ImplType = detail::PlantEquipmentOperationHeatingLoad_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit PlantEquipmentOperationHeatingLoad(std::shared_ptr<detail::PlantEquipmentOperationHeatingLoad_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_PLANTEQUIPMENTOPERATIONHEATINGLOAD_HPP
