/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_PLANTEQUIPMENTOPERATIONOUTDOORDRYBULB_HPP
#define EPMODEL_PLANTEQUIPMENTOPERATIONOUTDOORDRYBULB_HPP

#include "EPModelAPI.hpp"
#include "PlantEquipmentOperationScheme/PlantEquipmentOperationScheme.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <utility>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class PlantEquipmentOperationOutdoorDryBulb_Impl;
  }

  class EPMODEL_API PlantEquipmentOperationOutdoorDryBulb : public PlantEquipmentOperationScheme
  {
   public:
    explicit PlantEquipmentOperationOutdoorDryBulb(const Model& model);

    virtual ~PlantEquipmentOperationOutdoorDryBulb() override = default;
    PlantEquipmentOperationOutdoorDryBulb(const PlantEquipmentOperationOutdoorDryBulb& other) = default;
    PlantEquipmentOperationOutdoorDryBulb(PlantEquipmentOperationOutdoorDryBulb&& other) = default;
    PlantEquipmentOperationOutdoorDryBulb& operator=(const PlantEquipmentOperationOutdoorDryBulb&) = default;
    PlantEquipmentOperationOutdoorDryBulb& operator=(PlantEquipmentOperationOutdoorDryBulb&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: Mirrors EnergyPlus PlantEquipmentOperation:OutdoorDryBulb by re-exposing the same dry-bulb range scalars that the model counterpart surfaces.
    // - Field Mapping: maximumUpperLimit() and minimumLowerLimit() read the Dry-Bulb Temperature Range upper/lower limit values from the last/first extensible groups.
    // - TODO(parity): Add helpers for the rangelist relationships once the generic extensible scaffolding lands.
    double maximumUpperLimit() const;
    double minimumLowerLimit() const;

   protected:
    using ImplType = detail::PlantEquipmentOperationOutdoorDryBulb_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit PlantEquipmentOperationOutdoorDryBulb(std::shared_ptr<detail::PlantEquipmentOperationOutdoorDryBulb_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_PLANTEQUIPMENTOPERATIONOUTDOORDRYBULB_HPP
