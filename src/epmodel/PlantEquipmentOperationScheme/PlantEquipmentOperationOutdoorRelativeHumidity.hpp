/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_PLANTEQUIPMENTOPERATIONOUTDOORRELATIVEHUMIDITY_HPP
#define EPMODEL_PLANTEQUIPMENTOPERATIONOUTDOORRELATIVEHUMIDITY_HPP

#include "EPModelAPI.hpp"
#include "PlantEquipmentOperationScheme/PlantEquipmentOperationScheme.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <utility>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class PlantEquipmentOperationOutdoorRelativeHumidity_Impl;
  }

  /** \brief Selects plant equipment for outdoor-relative humidity operation.
   *
   * \par EnergyPlus object
   * \epobject{group-plant-condenser-control.html#plantequipmentoperationoutdoorrelativehumidity,PlantEquipmentOperation:OutdoorRelativeHumidity}
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::PlantEquipmentOperationOutdoorRelativeHumidity</code>.
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
  class EPMODEL_API PlantEquipmentOperationOutdoorRelativeHumidity : public PlantEquipmentOperationScheme
  {
   public:
    explicit PlantEquipmentOperationOutdoorRelativeHumidity(const Model& model);

    virtual ~PlantEquipmentOperationOutdoorRelativeHumidity() override = default;
    PlantEquipmentOperationOutdoorRelativeHumidity(const PlantEquipmentOperationOutdoorRelativeHumidity& other) = default;
    PlantEquipmentOperationOutdoorRelativeHumidity(PlantEquipmentOperationOutdoorRelativeHumidity&& other) = default;
    PlantEquipmentOperationOutdoorRelativeHumidity& operator=(const PlantEquipmentOperationOutdoorRelativeHumidity&) = default;
    PlantEquipmentOperationOutdoorRelativeHumidity& operator=(PlantEquipmentOperationOutdoorRelativeHumidity&&) = default;

    static IddObjectType iddObjectType();

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
