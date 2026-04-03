/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_PLANTEQUIPMENTOPERATIONSCHEMES_HPP
#define EPMODEL_PLANTEQUIPMENTOPERATIONSCHEMES_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <boost/optional.hpp>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class PlantEquipmentOperationCoolingLoad;
  class PlantEquipmentOperationHeatingLoad;
  class PlantEquipmentOperationScheme;
  class Schedule;

  namespace detail {
    class PlantEquipmentOperationSchemes_Impl;
  }

  class EPMODEL_API PlantEquipmentOperationSchemes : public ModelObject
  {
   public:
    explicit PlantEquipmentOperationSchemes(const Model& model);

    virtual ~PlantEquipmentOperationSchemes() override = default;
    PlantEquipmentOperationSchemes(const PlantEquipmentOperationSchemes& other) = default;
    PlantEquipmentOperationSchemes(PlantEquipmentOperationSchemes&& other) = default;
    PlantEquipmentOperationSchemes& operator=(const PlantEquipmentOperationSchemes&) = default;
    PlantEquipmentOperationSchemes& operator=(PlantEquipmentOperationSchemes&&) = default;

    static IddObjectType iddObjectType();
    static std::vector<std::string> controlSchemeObjectTypeValues();

    // Schema Alignment Notes:
    // - API: Public epmodel owner wrapper is intentionally read-only; typed PlantLoop-facing mutation remains on the impl layer.
    // - Field Mapping: Exposes typed inspection of the heating, cooling, primary, and component-setpoint control-scheme rows stored on the
    //   EnergyPlus PlantEquipmentOperationSchemes object instead of mirroring numbered extensible-row accessors.
    // - Canonical Counterpart: There is no direct openstudio::model public counterpart for this owner object; it exists here to back the
    //   canonical PlantLoop parity surface without exposing raw extensible-row mutation.

    boost::optional<PlantEquipmentOperationHeatingLoad> plantEquipmentOperationHeatingLoad() const;
    boost::optional<Schedule> plantEquipmentOperationHeatingLoadSchedule() const;

    boost::optional<PlantEquipmentOperationCoolingLoad> plantEquipmentOperationCoolingLoad() const;
    boost::optional<Schedule> plantEquipmentOperationCoolingLoadSchedule() const;

    boost::optional<PlantEquipmentOperationScheme> primaryPlantEquipmentOperationScheme() const;
    boost::optional<Schedule> primaryPlantEquipmentOperationSchemeSchedule() const;

    boost::optional<Schedule> componentSetpointOperationSchemeSchedule() const;

   protected:
    using ImplType = detail::PlantEquipmentOperationSchemes_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit PlantEquipmentOperationSchemes(std::shared_ptr<detail::PlantEquipmentOperationSchemes_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
