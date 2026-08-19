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

  /** \brief Selects plant equipment for outdoor-dry bulb difference operation.
   *
   * \par EnergyPlus object
   * \epobject{group-plant-condenser-control.html#plantequipmentoperationoutdoordrybulbdifference,PlantEquipmentOperation:OutdoorDryBulbDifference}
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::PlantEquipmentOperationOutdoorDryBulbDifference</code>.
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
