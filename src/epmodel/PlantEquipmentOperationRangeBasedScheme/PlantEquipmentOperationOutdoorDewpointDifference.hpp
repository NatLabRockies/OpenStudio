/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_PLANTEQUIPMENTOPERATIONOUTDOORDEWPOINTDIFFERENCE_HPP
#define EPMODEL_PLANTEQUIPMENTOPERATIONOUTDOORDEWPOINTDIFFERENCE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <utility>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class PlantEquipmentOperationOutdoorDewpointDifference_Impl;
  }

  class EPMODEL_API PlantEquipmentOperationOutdoorDewpointDifference : public ModelObject
  {
   public:
    explicit PlantEquipmentOperationOutdoorDewpointDifference(const Model& model);

    virtual ~PlantEquipmentOperationOutdoorDewpointDifference() override = default;
    PlantEquipmentOperationOutdoorDewpointDifference(const PlantEquipmentOperationOutdoorDewpointDifference& other) = default;
    PlantEquipmentOperationOutdoorDewpointDifference(PlantEquipmentOperationOutdoorDewpointDifference&& other) = default;
    PlantEquipmentOperationOutdoorDewpointDifference& operator=(const PlantEquipmentOperationOutdoorDewpointDifference&) = default;
    PlantEquipmentOperationOutdoorDewpointDifference& operator=(PlantEquipmentOperationOutdoorDewpointDifference&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: Mirrors the EnergyPlus PlantEquipmentOperation:OutdoorDewpointDifference object by exposing the same dewpoint-difference range scalars the model counterpart surfaces.
    // - Field Mapping: maximumUpperLimit() and minimumLowerLimit() read the Dewpoint Temperature Difference Range upper/lower limit values from the last/first extensible groups.
    // - TODO(parity): Add helpers for the reference temperature node and range-equipment-list relationships once the general extensible-handling scaffolding arrives.
    double maximumUpperLimit() const;
    double minimumLowerLimit() const;

   protected:
    using ImplType = detail::PlantEquipmentOperationOutdoorDewpointDifference_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit PlantEquipmentOperationOutdoorDewpointDifference(std::shared_ptr<detail::PlantEquipmentOperationOutdoorDewpointDifference_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_PLANTEQUIPMENTOPERATIONOUTDOORDEWPOINTDIFFERENCE_HPP
