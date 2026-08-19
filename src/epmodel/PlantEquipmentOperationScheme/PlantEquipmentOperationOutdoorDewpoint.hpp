/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_PLANTEQUIPMENTOPERATIONOUTDOORDEWPOINT_HPP
#define EPMODEL_PLANTEQUIPMENTOPERATIONOUTDOORDEWPOINT_HPP

#include "EPModelAPI.hpp"
#include "PlantEquipmentOperationScheme/PlantEquipmentOperationScheme.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <utility>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class PlantEquipmentOperationOutdoorDewpoint_Impl;
  }

  /** \brief Selects plant equipment for outdoor-dewpoint operation.
   *
   * \par EnergyPlus object
   * \epobject{group-plant-condenser-control.html#plantequipmentoperationoutdoordewpoint,PlantEquipmentOperation:OutdoorDewpoint}
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::PlantEquipmentOperationOutdoorDewpoint</code>.
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
  class EPMODEL_API PlantEquipmentOperationOutdoorDewpoint : public PlantEquipmentOperationScheme
  {
   public:
    explicit PlantEquipmentOperationOutdoorDewpoint(const Model& model);

    virtual ~PlantEquipmentOperationOutdoorDewpoint() override = default;
    PlantEquipmentOperationOutdoorDewpoint(const PlantEquipmentOperationOutdoorDewpoint& other) = default;
    PlantEquipmentOperationOutdoorDewpoint(PlantEquipmentOperationOutdoorDewpoint&& other) = default;
    PlantEquipmentOperationOutdoorDewpoint& operator=(const PlantEquipmentOperationOutdoorDewpoint&) = default;
    PlantEquipmentOperationOutdoorDewpoint& operator=(PlantEquipmentOperationOutdoorDewpoint&&) = default;

    static IddObjectType iddObjectType();

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
