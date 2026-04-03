/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_PLANTEQUIPMENTOPERATIONOUTDOORWETBULB_HPP
#define EPMODEL_PLANTEQUIPMENTOPERATIONOUTDOORWETBULB_HPP

#include "EPModelAPI.hpp"
#include "PlantEquipmentOperationScheme/PlantEquipmentOperationScheme.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <utility>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class PlantEquipmentOperationOutdoorWetBulb_Impl;
  }

  class EPMODEL_API PlantEquipmentOperationOutdoorWetBulb : public PlantEquipmentOperationScheme
  {
   public:
    explicit PlantEquipmentOperationOutdoorWetBulb(const Model& model);

    virtual ~PlantEquipmentOperationOutdoorWetBulb() override = default;
    PlantEquipmentOperationOutdoorWetBulb(const PlantEquipmentOperationOutdoorWetBulb& other) = default;
    PlantEquipmentOperationOutdoorWetBulb(PlantEquipmentOperationOutdoorWetBulb&& other) = default;
    PlantEquipmentOperationOutdoorWetBulb& operator=(const PlantEquipmentOperationOutdoorWetBulb&) = default;
    PlantEquipmentOperationOutdoorWetBulb& operator=(PlantEquipmentOperationOutdoorWetBulb&&) = default;

    static IddObjectType iddObjectType();

    /**
     * @name Outdoor wet-bulb range scalars
     *
     * Schema Alignment Notes:
     * - API: Exposes the PlantEquipmentOperation:OutdoorWetBulb wet-bulb range scalars so the epmodel API matches the openstudio::model counterpart.
     * - Field Mapping: maximumUpperLimit() and minimumLowerLimit() read the Wet-Bulb Temperature Range upper/lower limits from the last/first extensible groups.
     * - TODO(parity): Add direct helpers for related equipment lists once the generic extensible scaffolding arrives.
     */
    //@{
    double maximumUpperLimit() const;
    double minimumLowerLimit() const;
    //@}

   protected:
    using ImplType = detail::PlantEquipmentOperationOutdoorWetBulb_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit PlantEquipmentOperationOutdoorWetBulb(std::shared_ptr<detail::PlantEquipmentOperationOutdoorWetBulb_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_PLANTEQUIPMENTOPERATIONOUTDOORWETBULB_HPP
