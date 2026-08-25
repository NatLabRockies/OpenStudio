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

  /** \brief Selects plant equipment for outdoor-wet bulb operation.
   *
   * \par EnergyPlus object
   * \epobject{group-plant-condenser-control.html#plantequipmentoperationoutdoorwetbulb,PlantEquipmentOperation:OutdoorWetBulb}
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::PlantEquipmentOperationOutdoorWetBulb</code>.
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
