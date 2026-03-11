/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_PLANTEQUIPMENTOPERATIONOUTDOORDEWPOINT_HPP
#define EPMODEL_PLANTEQUIPMENTOPERATIONOUTDOORDEWPOINT_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <utility>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class PlantEquipmentOperationOutdoorDewpoint_Impl;
  }

  class EPMODEL_API PlantEquipmentOperationOutdoorDewpoint : public ModelObject
  {
   public:
    explicit PlantEquipmentOperationOutdoorDewpoint(const Model& model);

    virtual ~PlantEquipmentOperationOutdoorDewpoint() override = default;
    PlantEquipmentOperationOutdoorDewpoint(const PlantEquipmentOperationOutdoorDewpoint& other) = default;
    PlantEquipmentOperationOutdoorDewpoint(PlantEquipmentOperationOutdoorDewpoint&& other) = default;
    PlantEquipmentOperationOutdoorDewpoint& operator=(const PlantEquipmentOperationOutdoorDewpoint&) = default;
    PlantEquipmentOperationOutdoorDewpoint& operator=(PlantEquipmentOperationOutdoorDewpoint&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: Wraps the EnergyPlus PlantEquipmentOperation:OutdoorDewpoint object with the same scalar dewpoint-range helpers used by the model counterpart.
    // - Field Mapping: maximumUpperLimit() and minimumLowerLimit() read the Dewpoint Temperature Range Upper/Lower Limit values from the last/first extensible groups.
    // - TODO(parity): Add explicit extensible load-range/equipment list helpers once the general extensible-handling scaffold lands.
    double maximumUpperLimit() const;
    double minimumLowerLimit() const;

   protected:
    using ImplType = detail::PlantEquipmentOperationOutdoorDewpoint_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit PlantEquipmentOperationOutdoorDewpoint(std::shared_ptr<detail::PlantEquipmentOperationOutdoorDewpoint_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_PLANTEQUIPMENTOPERATIONOUTDOORDEWPOINT_HPP
