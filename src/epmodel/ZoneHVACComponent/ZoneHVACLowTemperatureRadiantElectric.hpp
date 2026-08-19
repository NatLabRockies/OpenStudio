/***********************************************************************************************************************  
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.  
*  See also https://openstudio.net/license  
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACLOWTEMPERATURERADIANTELECTRIC_HPP
#define EPMODEL_ZONEHVACLOWTEMPERATURERADIANTELECTRIC_HPP

#include "EPModelAPI.hpp"
#include "ModelObject/ZoneHVACLowTemperatureRadiantSurfaceGroup.hpp"
#include "PlanarSurface/Surface.hpp"
#include "ZoneHVACComponent/ZoneHVACComponent.hpp"

#include <boost/optional.hpp>
#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class Schedule;

  namespace detail {
    class ZoneHVACLowTemperatureRadiantElectric_Impl;
  }

/** \brief An electric low-temperature radiant system serving a thermal zone.
 *
 * \par EnergyPlus object
 * \epobject{group-radiative-convective-units.html#zonehvaclowtemperatureradiantelectric,ZoneHVAC:LowTemperatureRadiant:Electric} and
 * \epobject{group-radiative-convective-units.html#zonehvaclowtemperatureradiantsurfacegroup,ZoneHVAC:LowTemperatureRadiant:SurfaceGroup}
 *
 * \par Important behavior
 * setRadiantSurfaceType() snapshots matching zone surfaces into the persisted surface group, which is the EnergyPlus representation of the selected surfaces.
 *
 * \par OpenStudio Model API
 * The corresponding OpenStudio Model class is <code>openstudio::model::ZoneHVACLowTemperatureRadiantElectric</code>.
 * EPModel adds a <code>surfaceGroup()</code> view over the persisted EnergyPlus
 * surface rows; Model instead provides its thermal-zone convenience methods.
 *
 * \par Known limitations
 * Later zone or surface edits do not automatically resynchronize the persisted surface group.
 */
  class EPMODEL_API ZoneHVACLowTemperatureRadiantElectric : public ZoneHVACComponent
  {
   public:
    ZoneHVACLowTemperatureRadiantElectric(const Model& model, Schedule& availabilitySchedule, Schedule& heatingTemperatureSchedule);

    virtual ~ZoneHVACLowTemperatureRadiantElectric() override = default;
    ZoneHVACLowTemperatureRadiantElectric(const ZoneHVACLowTemperatureRadiantElectric& other) = default;
    ZoneHVACLowTemperatureRadiantElectric(ZoneHVACLowTemperatureRadiantElectric&& other) = default;
    ZoneHVACLowTemperatureRadiantElectric& operator=(const ZoneHVACLowTemperatureRadiantElectric&) = default;
    ZoneHVACLowTemperatureRadiantElectric& operator=(ZoneHVACLowTemperatureRadiantElectric&&) = default;

    static IddObjectType iddObjectType();
    static std::vector<std::string> temperatureControlTypeValues();


    static std::vector<std::string> radiantSurfaceTypeValues();

    // Availability is canonical required API.
    Schedule availabilitySchedule() const;
    bool setAvailabilitySchedule(Schedule& schedule);

    // Canonical OpenStudio also treats this as required API. Epmodel keeps the
    // getter required. If imported data omits the underlying EnergyPlus field,
    // the getter logs and throws instead of silently inventing new schedule
    // state.
    Schedule heatingSetpointTemperatureSchedule() const;
    bool setHeatingSetpointTemperatureSchedule(Schedule& schedule);

    // `radiantSurfaceType()` is a canonical convenience view, not a first-class
    // EnergyPlus field. We infer it from the persisted EnergyPlus surface-group
    // membership when that membership matches one of the canonical OpenStudio
    // buckets (`Ceilings`, `Floors`, `CeilingsandFloors`, or `AllSurfaces`).
    // If the stored group does not correspond cleanly to one of those buckets,
    // `boost::none` is returned.
    boost::optional<std::string> radiantSurfaceType() const;

    // This preserves the canonical OpenStudio selector while staying anchored
    // to EnergyPlus storage. Today it is intentionally a snapshot rewrite of
    // the persisted EnergyPlus surface group based on the currently attached
    // thermal zone and the currently eligible matching surfaces.
    bool setRadiantSurfaceType(const std::string& radiantSurfaceType);
    void resetRadiantSurfaceType();

    // Returns the surfaces currently stored on the persisted EnergyPlus surface
    // group, not a freshly recomputed live view.
    std::vector<Surface> surfaces() const;

    // Additive epmodel API: canonical openstudio::model does not expose the
    // EnergyPlus surface-group companion object directly. Epmodel returns it
    // here because it is the real persisted storage behind the canonical
    // `radiantSurfaceType()` / `surfaces()` view.
    boost::optional<ZoneHVACLowTemperatureRadiantSurfaceGroup> surfaceGroup() const;

    // Maximum electrical power-to-panel accessors
    boost::optional<double> maximumElectricalPowertoPanel() const;
    bool isMaximumElectricalPowertoPanelDefaulted() const;
    bool isMaximumElectricalPowertoPanelAutosized() const;
    bool setMaximumElectricalPowertoPanel(double maximumElectricalPowertoPanel);
    void resetMaximumElectricalPowertoPanel();
    void autosizeMaximumElectricalPowertoPanel();
    boost::optional<double> autosizedMaximumElectricalPowertoPanel() const;

    // Temperature control type accessors
    std::string temperatureControlType() const;
    bool isTemperatureControlTypeDefaulted() const;
    bool setTemperatureControlType(const std::string& temperatureControlType);
    void resetTemperatureControlType();

    // Setpoint control type accessors
    std::string setpointControlType() const;
    bool isSetpointControlTypeDefaulted() const;
    bool setSetpointControlType(const std::string& setpointControlType);
    void resetSetpointControlType();

    // Heating throttling range accessors
    double heatingThrottlingRange() const;
    bool isHeatingThrottlingRangeDefaulted() const;
    bool setHeatingThrottlingRange(double heatingThrottlingRange);
    void resetHeatingThrottlingRange();

   protected:
    using ImplType = detail::ZoneHVACLowTemperatureRadiantElectric_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ZoneHVACLowTemperatureRadiantElectric(std::shared_ptr<detail::ZoneHVACLowTemperatureRadiantElectric_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
