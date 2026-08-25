/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_PLANTEQUIPMENTOPERATIONCOOLINGLOAD_HPP
#define EPMODEL_PLANTEQUIPMENTOPERATIONCOOLINGLOAD_HPP

#include "EPModelAPI.hpp"
#include "PlantEquipmentOperationScheme/PlantEquipmentOperationRangeBasedScheme.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <utility>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class PlantEquipmentOperationCoolingLoad_Impl;
  }

  /** \brief Selects plant equipment for cooling load operation.
   *
   * \par EnergyPlus object
   * \epobject{group-plant-condenser-control.html#plantequipmentoperationcoolingload,PlantEquipmentOperation:CoolingLoad}
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::PlantEquipmentOperationCoolingLoad</code>.
   * No known public API differences.
   *
   * \par Known limitations
   * No known EPModel-specific limitations.
   */
  class EPMODEL_API PlantEquipmentOperationCoolingLoad : public PlantEquipmentOperationRangeBasedScheme
  {
   public:
    explicit PlantEquipmentOperationCoolingLoad(const Model& model);

    virtual ~PlantEquipmentOperationCoolingLoad() override = default;
    PlantEquipmentOperationCoolingLoad(const PlantEquipmentOperationCoolingLoad& other) = default;
    PlantEquipmentOperationCoolingLoad(PlantEquipmentOperationCoolingLoad&& other) = default;
    PlantEquipmentOperationCoolingLoad& operator=(const PlantEquipmentOperationCoolingLoad&) = default;
    PlantEquipmentOperationCoolingLoad& operator=(PlantEquipmentOperationCoolingLoad&&) = default;

    static IddObjectType iddObjectType();


   protected:
    using ImplType = detail::PlantEquipmentOperationCoolingLoad_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit PlantEquipmentOperationCoolingLoad(std::shared_ptr<detail::PlantEquipmentOperationCoolingLoad_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_PLANTEQUIPMENTOPERATIONCOOLINGLOAD_HPP
