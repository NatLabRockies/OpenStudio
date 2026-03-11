/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_PLANTEQUIPMENTOPERATIONOUTDOORRELATIVEHUMIDITY_HPP
#define EPMODEL_PLANTEQUIPMENTOPERATIONOUTDOORRELATIVEHUMIDITY_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <utility>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class PlantEquipmentOperationOutdoorRelativeHumidity_Impl;
  }

  class EPMODEL_API PlantEquipmentOperationOutdoorRelativeHumidity : public ModelObject
  {
   public:
    explicit PlantEquipmentOperationOutdoorRelativeHumidity(const Model& model);

    virtual ~PlantEquipmentOperationOutdoorRelativeHumidity() override = default;
    PlantEquipmentOperationOutdoorRelativeHumidity(const PlantEquipmentOperationOutdoorRelativeHumidity& other) = default;
    PlantEquipmentOperationOutdoorRelativeHumidity(PlantEquipmentOperationOutdoorRelativeHumidity&& other) = default;
    PlantEquipmentOperationOutdoorRelativeHumidity& operator=(const PlantEquipmentOperationOutdoorRelativeHumidity&) = default;
    PlantEquipmentOperationOutdoorRelativeHumidity& operator=(PlantEquipmentOperationOutdoorRelativeHumidity&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: Mirrors EnergyPlus PlantEquipmentOperation:OutdoorRelativeHumidity by exposing the same relative humidity range scalars that the model counterpart surfaces.
    // - Field Mapping: maximumUpperLimit() and minimumLowerLimit() read the Relative Humidity Range Upper/Lower Limit values from the last/first extensible groups.
    // - TODO(parity): Add explicit helpers for the range equipment list once the general extensible scaffolding lands.
    double maximumUpperLimit() const;
    double minimumLowerLimit() const;

   protected:
    using ImplType = detail::PlantEquipmentOperationOutdoorRelativeHumidity_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit PlantEquipmentOperationOutdoorRelativeHumidity(std::shared_ptr<detail::PlantEquipmentOperationOutdoorRelativeHumidity_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_PLANTEQUIPMENTOPERATIONOUTDOORRELATIVEHUMIDITY_HPP
