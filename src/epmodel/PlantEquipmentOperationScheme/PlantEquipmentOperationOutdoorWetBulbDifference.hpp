/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_PLANTEQUIPMENTOPERATIONOUTDOORWETBULBDIFFERENCE_HPP
#define EPMODEL_PLANTEQUIPMENTOPERATIONOUTDOORWETBULBDIFFERENCE_HPP

#include "EPModelAPI.hpp"
#include "PlantEquipmentOperationScheme/PlantEquipmentOperationScheme.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <utility>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class PlantEquipmentOperationOutdoorWetBulbDifference_Impl;
  }

  /** \brief Selects plant equipment for outdoor-wet bulb difference operation.
   *
   * \par EnergyPlus object
   * \epobject{group-plant-condenser-control.html#plantequipmentoperationoutdoorwetbulbdifference,PlantEquipmentOperation:OutdoorWetBulbDifference}
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::PlantEquipmentOperationOutdoorWetBulbDifference</code>.
   *
   * - <b>Not yet available:</b> <code>referenceTemperatureNode()</code>,
   *   <code>setReferenceTemperatureNode(...)</code>, and
   *   <code>resetReferenceTemperatureNode()</code>.
   * - <b>Not yet available:</b> The load-range and equipment methods inherited
   *   from <code>PlantEquipmentOperationRangeBasedScheme</code>, including
   *   <code>addLoadRange(...)</code>, <code>removeLoadRange(...)</code>,
   *   <code>loadRangeUpperLimits()</code>, <code>equipment(...)</code>, the
   *   add/replace/remove equipment methods, and <code>clearLoadRanges()</code>.
   *
   * \par Known limitations
   * No known EPModel-specific limitations.
   */
  class EPMODEL_API PlantEquipmentOperationOutdoorWetBulbDifference : public PlantEquipmentOperationScheme
  {
   public:
    explicit PlantEquipmentOperationOutdoorWetBulbDifference(const Model& model);

    virtual ~PlantEquipmentOperationOutdoorWetBulbDifference() override = default;
    PlantEquipmentOperationOutdoorWetBulbDifference(const PlantEquipmentOperationOutdoorWetBulbDifference& other) = default;
    PlantEquipmentOperationOutdoorWetBulbDifference(PlantEquipmentOperationOutdoorWetBulbDifference&& other) = default;
    PlantEquipmentOperationOutdoorWetBulbDifference& operator=(const PlantEquipmentOperationOutdoorWetBulbDifference&) = default;
    PlantEquipmentOperationOutdoorWetBulbDifference& operator=(PlantEquipmentOperationOutdoorWetBulbDifference&&) = default;

    static IddObjectType iddObjectType();

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
