/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_PLANTEQUIPMENTOPERATIONOUTDOORWETBULBDIFFERENCE_HPP
#define EPMODEL_PLANTEQUIPMENTOPERATIONOUTDOORWETBULBDIFFERENCE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <utility>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class PlantEquipmentOperationOutdoorWetBulbDifference_Impl;
  }

  class EPMODEL_API PlantEquipmentOperationOutdoorWetBulbDifference : public ModelObject
  {
   public:
    explicit PlantEquipmentOperationOutdoorWetBulbDifference(const Model& model);

    virtual ~PlantEquipmentOperationOutdoorWetBulbDifference() override = default;
    PlantEquipmentOperationOutdoorWetBulbDifference(const PlantEquipmentOperationOutdoorWetBulbDifference& other) = default;
    PlantEquipmentOperationOutdoorWetBulbDifference(PlantEquipmentOperationOutdoorWetBulbDifference&& other) = default;
    PlantEquipmentOperationOutdoorWetBulbDifference& operator=(const PlantEquipmentOperationOutdoorWetBulbDifference&) = default;
    PlantEquipmentOperationOutdoorWetBulbDifference& operator=(PlantEquipmentOperationOutdoorWetBulbDifference&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: Mirrors the EnergyPlus PlantEquipmentOperation:OutdoorWetBulbDifference range scalars so the epmodel API matches the openstudio::model counterpart.
    // - Field Mapping: maximumUpperLimit()/minimumLowerLimit() read the Wet-Bulb Temperature Difference Range 1 upper/lower limit fields from the last/first extensible groups, matching translatePlantEquipmentOperationOutdoorWetBulbDifference.
    // - TODO(parity): Add helpers for the reference temperature node and the range equipment list relationships once the general extensible/relationship scaffolding arrives.
    double maximumUpperLimit() const;
    double minimumLowerLimit() const;

   protected:
    using ImplType = detail::PlantEquipmentOperationOutdoorWetBulbDifference_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit PlantEquipmentOperationOutdoorWetBulbDifference(std::shared_ptr<detail::PlantEquipmentOperationOutdoorWetBulbDifference_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_PLANTEQUIPMENTOPERATIONOUTDOORWETBULBDIFFERENCE_HPP
