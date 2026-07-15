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

    // Schema Alignment Notes:
    // - Canonical Counterpart: openstudio::model::PlantEquipmentOperationHeatingLoad.
    // - API: Inherits the range/equipment helpers from PlantEquipmentOperationRangeBasedScheme.

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
