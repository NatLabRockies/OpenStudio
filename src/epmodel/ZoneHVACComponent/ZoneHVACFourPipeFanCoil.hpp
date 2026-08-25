/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACFOURPIPEFANCOIL_HPP
#define EPMODEL_ZONEHVACFOURPIPEFANCOIL_HPP

#include "EPModelAPI.hpp"
#include "ZoneHVACComponent.hpp"

#include <boost/optional.hpp>
#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class HVACComponent;
  class Node;
  class Schedule;

  namespace detail {
    class ZoneHVACFourPipeFanCoil_Impl;
  }

/** \brief A four-pipe fan-coil unit serving a thermal zone.
 *
 * \par EnergyPlus object
 * \epobject{group-zone-forced-air-units.html#zonehvacfourpipefancoil,ZoneHVAC:FourPipeFanCoil}
 *
 * \par Important behavior
 * The fan and heating/cooling coils share a parent-owned serial path. A locally owned OutdoorAir:Mixer companion is maintained while unattached, including at zero outdoor-air flow. EPModel adds fanOutletNode() and coolingCoilOutletNode().
 *
 * \par OpenStudio Model API
 * The corresponding OpenStudio Model class is <code>openstudio::model::ZoneHVACFourPipeFanCoil</code>.
 * EPModel adds fan/cooling-coil outlet node accessors. Model additionally has
 * outdoor-air mixer-name and autosized-flow/temperature result helpers.
 *
 * \par Known limitations
 * Mixer-only node roles and SQL-backed autosized flow/temperature results are not exposed.
 */
  class EPMODEL_API ZoneHVACFourPipeFanCoil : public ZoneHVACComponent
  {
   public:
    explicit ZoneHVACFourPipeFanCoil(const Model& model);

    virtual ~ZoneHVACFourPipeFanCoil() override = default;
    ZoneHVACFourPipeFanCoil(const ZoneHVACFourPipeFanCoil& other) = default;
    ZoneHVACFourPipeFanCoil(ZoneHVACFourPipeFanCoil&& other) = default;
    ZoneHVACFourPipeFanCoil& operator=(const ZoneHVACFourPipeFanCoil&) = default;
    ZoneHVACFourPipeFanCoil& operator=(ZoneHVACFourPipeFanCoil&&) = default;

    static IddObjectType iddObjectType();
    static std::vector<std::string> capacityControlMethodValues();
    static std::vector<std::string> outdoorAirMixerObjectTypeValues();


    Schedule availabilitySchedule() const;
    bool setAvailabilitySchedule(Schedule& schedule);

    std::string capacityControlMethod() const;
    bool setCapacityControlMethod(const std::string& capacityControlMethod);

    boost::optional<double> maximumSupplyAirFlowRate() const;
    bool isMaximumSupplyAirFlowRateAutosized() const;
    bool setMaximumSupplyAirFlowRate(double maximumSupplyAirFlowRate);
    void autosizeMaximumSupplyAirFlowRate();

    double lowSpeedSupplyAirFlowRatio() const;
    bool isLowSpeedSupplyAirFlowRatioDefaulted() const;
    bool setLowSpeedSupplyAirFlowRatio(double lowSpeedSupplyAirFlowRatio);
    void resetLowSpeedSupplyAirFlowRatio();

    double mediumSpeedSupplyAirFlowRatio() const;
    bool isMediumSpeedSupplyAirFlowRatioDefaulted() const;
    bool setMediumSpeedSupplyAirFlowRatio(double mediumSpeedSupplyAirFlowRatio);
    void resetMediumSpeedSupplyAirFlowRatio();

    boost::optional<double> maximumOutdoorAirFlowRate() const;
    bool isMaximumOutdoorAirFlowRateAutosized() const;
    bool setMaximumOutdoorAirFlowRate(double maximumOutdoorAirFlowRate);
    void autosizeMaximumOutdoorAirFlowRate();

    std::string outdoorAirMixerObjectType() const;
    bool setOutdoorAirMixerObjectType(const std::string& outdoorAirMixerObjectType);

    boost::optional<Schedule> outdoorAirSchedule() const;
    bool setOutdoorAirSchedule(Schedule& schedule);
    void resetOutdoorAirSchedule();

    HVACComponent supplyAirFan() const;
    HVACComponent coolingCoil() const;
    HVACComponent heatingCoil() const;
    boost::optional<Node> fanOutletNode() const;
    boost::optional<Node> coolingCoilOutletNode() const;

    bool setSupplyAirFan(const HVACComponent& fan);
    bool setCoolingCoil(const HVACComponent& coolingCoil);
    bool setHeatingCoil(const HVACComponent& heatingCoil);

    boost::optional<Schedule> supplyAirFanOperatingModeSchedule() const;
    bool setSupplyAirFanOperatingModeSchedule(Schedule& schedule);
    void resetSupplyAirFanOperatingModeSchedule();

    boost::optional<double> maximumColdWaterFlowRate() const;
    bool isMaximumColdWaterFlowRateAutosized() const;
    bool setMaximumColdWaterFlowRate(double maximumColdWaterFlowRate);
    void autosizeMaximumColdWaterFlowRate();

    double minimumColdWaterFlowRate() const;
    bool isMinimumColdWaterFlowRateDefaulted() const;
    bool setMinimumColdWaterFlowRate(double minimumColdWaterFlowRate);
    void resetMinimumColdWaterFlowRate();

    double coolingConvergenceTolerance() const;
    bool isCoolingConvergenceToleranceDefaulted() const;
    bool setCoolingConvergenceTolerance(double coolingConvergenceTolerance);
    void resetCoolingConvergenceTolerance();

    boost::optional<double> maximumHotWaterFlowRate() const;
    bool isMaximumHotWaterFlowRateAutosized() const;
    bool setMaximumHotWaterFlowRate(double maximumHotWaterFlowRate);
    void autosizeMaximumHotWaterFlowRate();

    double minimumHotWaterFlowRate() const;
    bool isMinimumHotWaterFlowRateDefaulted() const;
    bool setMinimumHotWaterFlowRate(double minimumHotWaterFlowRate);
    void resetMinimumHotWaterFlowRate();

    double heatingConvergenceTolerance() const;
    bool isHeatingConvergenceToleranceDefaulted() const;
    bool setHeatingConvergenceTolerance(double heatingConvergenceTolerance);
    void resetHeatingConvergenceTolerance();

    boost::optional<double> minimumSupplyAirTemperatureInCoolingMode() const;
    bool isMinimumSupplyAirTemperatureInCoolingModeAutosized() const;
    bool setMinimumSupplyAirTemperatureInCoolingMode(double minimumSupplyAirTemperatureInCoolingMode);
    void autosizeMinimumSupplyAirTemperatureInCoolingMode();

    boost::optional<double> maximumSupplyAirTemperatureInHeatingMode() const;
    bool isMaximumSupplyAirTemperatureInHeatingModeAutosized() const;
    bool setMaximumSupplyAirTemperatureInHeatingMode(double maximumSupplyAirTemperatureInHeatingMode);
    void autosizeMaximumSupplyAirTemperatureInHeatingMode();

   protected:
    using ImplType = detail::ZoneHVACFourPipeFanCoil_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ZoneHVACFourPipeFanCoil(std::shared_ptr<detail::ZoneHVACFourPipeFanCoil_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_ZONEHVACFOURPIPEFANCOIL_HPP
