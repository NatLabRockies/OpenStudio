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
    // - API: Scalar accessors keep the openstudio::model names (maximumSupplyAirFlowRate, outdoorAirControlType,
    //   minimumOutdoorAirFlowRate, maximumOutdoorAirFlowRate, heatingConvergenceTolerance, coolingConvergenceTolerance)
    //   while mapping directly to the EnergyPlus ZoneHVAC:UnitVentilator fields via OS_ZoneHVAC_UnitVentilatorFields.
    //   ForwardTranslateZoneHVACUnitVentilator.cpp documents the field-name drift and autosize semantics that justify this mapping.
    // - Field Mapping: availability/schedule targets (AvailabilityScheduleName, MinimumOutdoorAirScheduleName,
    //   MaximumOutdoorAirFractionorTemperatureScheduleName), SupplyAirFan+/SupplyAirFanOperatingModeSchedule, heating/cooling coil
    //   references, and inlet/outlet node targets remain relationship-only and are intentionally excluded from this scalar surface.
    // - Default/autosize helpers mirror the IDD metadata so required scalars (heating/cooling convergence tolerances) stay strict while the
    //   optional flow fields expose is...Autosized/autosize helpers consistent with the Ruby generator.

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
