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
    // - Documented Delta: Availability and outdoor-air schedules, supply-fan and operating-mode schedules, heating/cooling coil references, and inlet/outlet nodes remain relationship-only.
    // - Field/Storage Mapping: Scalar values are stored directly on the EnergyPlus object while schedule and node wiring are handled through explicit relationship state.
    // - Evidence: `src/model/ZoneHVACUnitVentilator.hpp`, `src/model/ZoneHVACUnitVentilator.cpp`, `src/energyplus/ForwardTranslator/ForwardTranslateZoneHVACUnitVentilator.cpp`, and `src/epmodel/test/ZoneHVACUnitVentilator_GTest.cpp`.
    // - Remaining Parity Work: Add the missing relationship helpers only if the canonical wrapper still exposes them directly.

    /** @name Maximum supply air flow rate */
    //@{
    boost::optional<double> maximumSupplyAirFlowRate() const;
    bool isMaximumSupplyAirFlowRateAutosized() const;
    bool setMaximumSupplyAirFlowRate(double maximumSupplyAirFlowRate);
    void autosizeMaximumSupplyAirFlowRate();
    boost::optional<double> autosizedMaximumSupplyAirFlowRate() const;
    //@}

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
