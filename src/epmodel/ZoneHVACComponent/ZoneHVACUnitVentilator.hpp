/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACUNITVENTILATOR_HPP
#define EPMODEL_ZONEHVACUNITVENTILATOR_HPP

#include "EPModelAPI.hpp"
#include "ZoneHVACComponent.hpp"

#include <boost/optional.hpp>
#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class ModelObject;
  class Node;
  class Schedule;
  class HVACComponent;

  namespace detail {
    class ZoneHVACUnitVentilator_Impl;
  }

/** \brief A unit ventilator serving a thermal zone.
 *
 * \par EnergyPlus object
 * \epobject{group-zone-forced-air-units.html#zonehvacunitventilator,ZoneHVAC:UnitVentilator}
 *
 * \par Important behavior
 * The fan and coils share a parent-owned path with mixed-air, outdoor-air, exhaust-air, fan-outlet, and cooling-coil-outlet roles that survive save/load and public zone, plant, and child changes. EPModel adds these node accessors.
 *
 * \par OpenStudio Model API
 * The corresponding OpenStudio Model class is <code>openstudio::model::ZoneHVACUnitVentilator</code>.
 *
 * \par Known limitations
 * Clone/cross-model transfer and less common fan/coil combinations have not been exhaustively aligned.
 */
  class EPMODEL_API ZoneHVACUnitVentilator : public ZoneHVACComponent
  {
   public:
    explicit ZoneHVACUnitVentilator(const Model& model);

    virtual ~ZoneHVACUnitVentilator() override = default;
    ZoneHVACUnitVentilator(const ZoneHVACUnitVentilator& other) = default;
    ZoneHVACUnitVentilator(ZoneHVACUnitVentilator&& other) = default;
    ZoneHVACUnitVentilator& operator=(const ZoneHVACUnitVentilator&) = default;
    ZoneHVACUnitVentilator& operator=(ZoneHVACUnitVentilator&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> outdoorAirControlTypeValues();


    Schedule availabilitySchedule() const;
    bool setAvailabilitySchedule(Schedule& schedule);

    /** @name Maximum supply air flow rate */
    //@{
    boost::optional<double> maximumSupplyAirFlowRate() const;
    bool isMaximumSupplyAirFlowRateAutosized() const;
    bool setMaximumSupplyAirFlowRate(double maximumSupplyAirFlowRate);
    void autosizeMaximumSupplyAirFlowRate();
    boost::optional<double> autosizedMaximumSupplyAirFlowRate() const;
    //@}

    Schedule minimumOutdoorAirSchedule() const;
    bool setMinimumOutdoorAirSchedule(Schedule& schedule);

    Schedule maximumOutdoorAirFractionorTemperatureSchedule() const;
    bool setMaximumOutdoorAirFractionorTemperatureSchedule(Schedule& schedule);

    HVACComponent supplyAirFan() const;
    bool setSupplyAirFan(const HVACComponent& supplyAirFan);

    boost::optional<Schedule> supplyAirFanOperatingModeSchedule() const;
    bool setSupplyAirFanOperatingModeSchedule(Schedule& schedule);
    void resetSupplyAirFanOperatingModeSchedule();

    boost::optional<HVACComponent> heatingCoil() const;
    bool setHeatingCoil(const HVACComponent& heatingCoil);
    void resetHeatingCoil();

    boost::optional<HVACComponent> coolingCoil() const;
    bool setCoolingCoil(const HVACComponent& coolingCoil);
    void resetCoolingCoil();

    boost::optional<Node> mixedAirNode() const;
    boost::optional<Node> outdoorAirNode() const;
    boost::optional<Node> exhaustAirNode() const;
    boost::optional<Node> fanOutletNode() const;
    boost::optional<Node> coolingCoilOutletNode() const;

    /** @name Outdoor air control type */
    //@{
    std::string outdoorAirControlType() const;
    bool setOutdoorAirControlType(const std::string& outdoorAirControlType);
    //@}

    /** @name Minimum outdoor air flow rate */
    //@{
    boost::optional<double> minimumOutdoorAirFlowRate() const;
    bool isMinimumOutdoorAirFlowRateAutosized() const;
    bool setMinimumOutdoorAirFlowRate(double minimumOutdoorAirFlowRate);
    void autosizeMinimumOutdoorAirFlowRate();
    boost::optional<double> autosizedMinimumOutdoorAirFlowRate() const;
    //@}

    /** @name Maximum outdoor air flow rate */
    //@{
    boost::optional<double> maximumOutdoorAirFlowRate() const;
    bool isMaximumOutdoorAirFlowRateAutosized() const;
    bool setMaximumOutdoorAirFlowRate(double maximumOutdoorAirFlowRate);
    void autosizeMaximumOutdoorAirFlowRate();
    boost::optional<double> autosizedMaximumOutdoorAirFlowRate() const;
    //@}

    /** @name Convergence tolerances */
    //@{
    double heatingConvergenceTolerance() const;
    bool setHeatingConvergenceTolerance(double heatingConvergenceTolerance);

    double coolingConvergenceTolerance() const;
    bool setCoolingConvergenceTolerance(double coolingConvergenceTolerance);
    //@}

    std::vector<ModelObject> children() const;

   protected:
    using ImplType = detail::ZoneHVACUnitVentilator_Impl;

    explicit ZoneHVACUnitVentilator(std::shared_ptr<detail::ZoneHVACUnitVentilator_Impl> impl);

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;
  };

}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_ZONEHVACUNITVENTILATOR_HPP
