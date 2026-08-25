/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_PLANTEQUIPMENTOPERATIONOUTDOORDEWPOINTDIFFERENCE_HPP
#define EPMODEL_PLANTEQUIPMENTOPERATIONOUTDOORDEWPOINTDIFFERENCE_HPP

#include "EPModelAPI.hpp"
#include "PlantEquipmentOperationScheme/PlantEquipmentOperationScheme.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <utility>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class PlantEquipmentOperationOutdoorDewpointDifference_Impl;
  }

  /** \brief Selects plant equipment for outdoor-dewpoint difference operation.
   *
   * \par EnergyPlus object
   * \epobject{group-plant-condenser-control.html#plantequipmentoperationoutdoordewpointdifference,PlantEquipmentOperation:OutdoorDewpointDifference}
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::PlantEquipmentOperationOutdoorDewpointDifference</code>.
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
  class EPMODEL_API PlantEquipmentOperationOutdoorDewpointDifference : public PlantEquipmentOperationScheme
  {
   public:
    explicit PlantEquipmentOperationOutdoorDewpointDifference(const Model& model);

    virtual ~PlantEquipmentOperationOutdoorDewpointDifference() override = default;
    PlantEquipmentOperationOutdoorDewpointDifference(const PlantEquipmentOperationOutdoorDewpointDifference& other) = default;
    PlantEquipmentOperationOutdoorDewpointDifference(PlantEquipmentOperationOutdoorDewpointDifference&& other) = default;
    PlantEquipmentOperationOutdoorDewpointDifference& operator=(const PlantEquipmentOperationOutdoorDewpointDifference&) = default;
    PlantEquipmentOperationOutdoorDewpointDifference& operator=(PlantEquipmentOperationOutdoorDewpointDifference&&) = default;

    static IddObjectType iddObjectType();

    double maximumUpperLimit() const;
    double minimumLowerLimit() const;

   protected:
    using ImplType = detail::PlantEquipmentOperationOutdoorDewpointDifference_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit PlantEquipmentOperationOutdoorDewpointDifference(std::shared_ptr<detail::PlantEquipmentOperationOutdoorDewpointDifference_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_PLANTEQUIPMENTOPERATIONOUTDOORDEWPOINTDIFFERENCE_HPP
