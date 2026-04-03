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
  class Schedule;
  class HVACComponent;

  namespace detail {
    class ZoneHVACUnitVentilator_Impl;
  }

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

    // Schema Alignment Notes:
    // - Status: Partial Parity. The unit-ventilator scalar fields are aligned, but the schedule/fan/coil/node relationships remain separate.
    // - Canonical Counterpart: openstudio::model::ZoneHVACUnitVentilator.
    // - Implemented Parity: `maximumSupplyAirFlowRate`, `outdoorAirControlType`, `minimumOutdoorAirFlowRate`, `maximumOutdoorAirFlowRate`, `heatingConvergenceTolerance`, and `coolingConvergenceTolerance` map directly to the EnergyPlus object.
    // - Documented Delta: The outdoor-air temperature/fraction schedule pair remains partially specialized; inlet/outlet nodes continue to come from the shared component topology.
    // - Field/Storage Mapping: Scalar values are stored directly on the EnergyPlus object while schedule, fan, and coil wiring are handled through explicit relationship state.
    // - Evidence: `src/model/ZoneHVACUnitVentilator.hpp`, `src/model/ZoneHVACUnitVentilator.cpp`, `src/energyplus/ForwardTranslator/ForwardTranslateZoneHVACUnitVentilator.cpp`, and `src/epmodel/test/ZoneHVACUnitVentilator_GTest.cpp`.
    // - Remaining Parity Work: Add the missing relationship helpers only if the canonical wrapper still exposes them directly.

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
