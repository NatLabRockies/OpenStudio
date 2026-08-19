/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACCOOLINGPANELRADIANTCONVECTIVEWATER_HPP
#define EPMODEL_ZONEHVACCOOLINGPANELRADIANTCONVECTIVEWATER_HPP

#include "EPModelAPI.hpp"
#include "ZoneHVACComponent/ZoneHVACComponent.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class HVACComponent;
  class Model;
  class ModelObject;
  class Schedule;

  namespace detail {
    class ZoneHVACCoolingPanelRadiantConvectiveWater_Impl;
  }

/** \brief A hot-water radiant-convective cooling panel serving a thermal zone.
 *
 * \par EnergyPlus object
 * \epobject{group-radiative-convective-units.html#zonehvaccoolingpanelradiantconvectivewater,ZoneHVAC:CoolingPanel:RadiantConvective:Water}
 *
 * \par Important behavior
 * The cooling-coil child is a transient view over parent-owned fields and plant branch rows store the panel object. Surface rows are rebuilt on attachment, detachment, canonicalization, or people-radiation changes.
 *
 * \par OpenStudio Model API
 * The corresponding OpenStudio Model class is <code>openstudio::model::ZoneHVACCoolingPanelRadiantConvectiveWater</code>.
 * The cooling coil exposed by EPModel is a transient
 * <code>CoilCoolingWaterPanelRadiant</code> view, not the Model's ordinary
 * persisted coil relationship.
 *
 * \par Known limitations
 * Later edits to zone surfaces do not automatically resynchronize persisted surface rows.
 */
  class EPMODEL_API ZoneHVACCoolingPanelRadiantConvectiveWater : public ZoneHVACComponent
  {
   public:
    explicit ZoneHVACCoolingPanelRadiantConvectiveWater(const Model& model);

    virtual ~ZoneHVACCoolingPanelRadiantConvectiveWater() override = default;
    ZoneHVACCoolingPanelRadiantConvectiveWater(const ZoneHVACCoolingPanelRadiantConvectiveWater& other) = default;
    ZoneHVACCoolingPanelRadiantConvectiveWater(ZoneHVACCoolingPanelRadiantConvectiveWater&& other) = default;
    ZoneHVACCoolingPanelRadiantConvectiveWater& operator=(const ZoneHVACCoolingPanelRadiantConvectiveWater&) = default;
    ZoneHVACCoolingPanelRadiantConvectiveWater& operator=(ZoneHVACCoolingPanelRadiantConvectiveWater&&) = default;

    static IddObjectType iddObjectType();


    Schedule availabilitySchedule() const;
    bool setAvailabilitySchedule(Schedule& schedule);
    void resetAvailabilitySchedule();

    double fractionRadiant() const;
    bool setFractionRadiant(double fractionRadiant);

    double fractionofRadiantEnergyIncidentonPeople() const;
    bool setFractionofRadiantEnergyIncidentonPeople(double fractionofRadiantEnergyIncidentonPeople);

    HVACComponent coolingCoil() const;
    bool setCoolingCoil(HVACComponent& coolingCoil);

    std::vector<ModelObject> children() const;

   protected:
    using ImplType = detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ZoneHVACCoolingPanelRadiantConvectiveWater(std::shared_ptr<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
