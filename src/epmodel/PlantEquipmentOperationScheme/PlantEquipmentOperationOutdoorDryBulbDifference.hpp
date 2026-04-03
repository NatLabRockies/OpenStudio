/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_PLANTEQUIPMENTOPERATIONOUTDOORDRYBULBDIFFERENCE_HPP
#define EPMODEL_PLANTEQUIPMENTOPERATIONOUTDOORDRYBULBDIFFERENCE_HPP

#include "EPModelAPI.hpp"
#include "PlantEquipmentOperationScheme/PlantEquipmentOperationScheme.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <utility>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class PlantEquipmentOperationOutdoorDryBulbDifference_Impl;
  }

  class EPMODEL_API PlantEquipmentOperationOutdoorDryBulbDifference : public PlantEquipmentOperationScheme
  {
   public:
    explicit PlantEquipmentOperationOutdoorDryBulbDifference(const Model& model);

    virtual ~PlantEquipmentOperationOutdoorDryBulbDifference() override = default;
    PlantEquipmentOperationOutdoorDryBulbDifference(const PlantEquipmentOperationOutdoorDryBulbDifference& other) = default;
    PlantEquipmentOperationOutdoorDryBulbDifference(PlantEquipmentOperationOutdoorDryBulbDifference&& other) = default;
    PlantEquipmentOperationOutdoorDryBulbDifference& operator=(const PlantEquipmentOperationOutdoorDryBulbDifference&) = default;
    PlantEquipmentOperationOutdoorDryBulbDifference& operator=(PlantEquipmentOperationOutdoorDryBulbDifference&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: Mirrors EnergyPlus PlantEquipmentOperation:OutdoorDryBulbDifference by re-exposing the same dry-bulb temperature difference range scalars from the first/last extensible groups.
    // - Field Mapping: maximumUpperLimit()/minimumLowerLimit() read the Dry-Bulb Temperature Difference Range 1 upper/lower limit fields.
    // - TODO(parity): Add helpers for the reference temperature node and range equipment list relationships once general relationship scaffolding arrives.
    double maximumUpperLimit() const;
    double minimumLowerLimit() const;

   protected:
    using ImplType = detail::PlantEquipmentOperationOutdoorDryBulbDifference_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit PlantEquipmentOperationOutdoorDryBulbDifference(std::shared_ptr<detail::PlantEquipmentOperationOutdoorDryBulbDifference_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_PLANTEQUIPMENTOPERATIONOUTDOORDRYBULBDIFFERENCE_HPP
