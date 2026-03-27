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

  namespace detail {
    class ZoneHVACFourPipeFanCoil_Impl;
  }

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

    // Schema Alignment Notes:
    // - API: Scalar getters/setters map to EnergyPlus ZoneHVAC:FourPipeFanCoil fields (ZoneHVAC_FourPipeFanCoilFields) and ForwardTranslateZoneHVACFourPipeFanCoil.cpp.
    // - Field Mapping: Schedule, fan, coil, node, and operating-mode relationships are intentionally excluded from this scalar-only scaffold.
    // - TODO(parity): Add relationship/link APIs once scalar coverage is stable.

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
