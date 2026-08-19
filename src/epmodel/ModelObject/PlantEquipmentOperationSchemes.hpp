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

  /** \brief PlantEquipmentOperationSchemes.
   *
   * \par EnergyPlus object
   * \epobject{group-plant-condenser-control.html#plantequipmentoperationschemes,PlantEquipmentOperationSchemes}.
   *
   * \par OpenStudio Model API
   * There is no corresponding <code>openstudio::model</code> class. EPModel exposes typed inspection of configured scheme rows, but not public mutation of the underlying extensible rows.
   *
   * \par Known limitations
   * There is no corresponding <code>openstudio::model</code> class. EPModel exposes typed inspection of configured scheme rows, but not public mutation of the underlying extensible rows.
   */
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
