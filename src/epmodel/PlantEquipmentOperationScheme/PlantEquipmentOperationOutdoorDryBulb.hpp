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

  /** \brief Selects plant equipment for outdoor-dry bulb operation.
   *
   * \par EnergyPlus object
   * \epobject{group-plant-condenser-control.html#plantequipmentoperationoutdoordrybulb,PlantEquipmentOperation:OutdoorDryBulb}
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::PlantEquipmentOperationOutdoorDryBulb</code>.
   *
   * - <b>Not yet available:</b> The load-range and equipment methods inherited
   *   from <code>PlantEquipmentOperationRangeBasedScheme</code>, including
   *   <code>addLoadRange(...)</code>, <code>removeLoadRange(...)</code>,
   *   <code>loadRangeUpperLimits()</code>, <code>equipment(...)</code>, the
   *   add/replace/remove equipment methods, and <code>clearLoadRanges()</code>.
   *
   * \par Known limitations
   * No known EPModel-specific limitations.
   */
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
