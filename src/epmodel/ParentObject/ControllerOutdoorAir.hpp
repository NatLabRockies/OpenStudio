/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CONTROLLEROUTDOORAIR_HPP
#define EPMODEL_CONTROLLEROUTDOORAIR_HPP

#include "EPModelAPI.hpp"
#include "ParentObject.hpp"

#include <utilities/core/Deprecated.hpp>
#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class ControllerMechanicalVentilation;
  class AirLoopHVACOutdoorAirSystem;

  namespace detail {
    class ControllerOutdoorAir_Impl;
  }

  class EPMODEL_API ControllerOutdoorAir : public ParentObject
  {
   public:
    explicit ControllerOutdoorAir(const Model& model);

    virtual ~ControllerOutdoorAir() override = default;
    ControllerOutdoorAir(const ControllerOutdoorAir& other) = default;
    ControllerOutdoorAir(ControllerOutdoorAir&& other) = default;
    ControllerOutdoorAir& operator=(const ControllerOutdoorAir&) = default;
    ControllerOutdoorAir& operator=(ControllerOutdoorAir&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> economizerControlTypeValues();
    static std::vector<std::string> economizerControlActionTypeValues();
    static std::vector<std::string> lockoutTypeValues();
    static std::vector<std::string> minimumLimitTypeValues();
    static std::vector<std::string> heatRecoveryBypassControlTypeValues();
    static std::vector<std::string> economizerOperationStagingValues();

    // Schema Alignment Notes:
    // - API: Preserve openstudio::model::ControllerOutdoorAir scalar accessor names/signatures.
    // - Field Mapping: Scalar APIs map directly to EnergyPlus Controller:OutdoorAir fields.
    // - Field Mapping: Node/schedule/curve/zone links remain relationship APIs and are intentionally excluded.
    // - ForwardTranslator evidence: ForwardTranslateControllerOutdoorAir.cpp writes these scalar fields directly.
    // - TODO(parity): Add remaining non-scalar parity incrementally without changing preserved scalar signatures.
    boost::optional<double> minimumOutdoorAirFlowRate() const;
    bool isMinimumOutdoorAirFlowRateAutosized() const;
    bool setMinimumOutdoorAirFlowRate(double minimumOutdoorAirFlowRate);
    void autosizeMinimumOutdoorAirFlowRate();

    boost::optional<double> maximumOutdoorAirFlowRate() const;
    bool isMaximumOutdoorAirFlowRateAutosized() const;
    bool setMaximumOutdoorAirFlowRate(double maximumOutdoorAirFlowRate);
    void autosizeMaximumOutdoorAirFlowRate();

    std::string getEconomizerControlType() const;
    bool setEconomizerControlType(const std::string& value);

    std::string getEconomizerControlActionType() const;
    bool setEconomizerControlActionType(const std::string& value);

    boost::optional<double> getEconomizerMaximumLimitDryBulbTemperature() const;
    bool setEconomizerMaximumLimitDryBulbTemperature(double value);
    void resetEconomizerMaximumLimitDryBulbTemperature();

    boost::optional<double> getEconomizerMaximumLimitEnthalpy() const;
    bool setEconomizerMaximumLimitEnthalpy(double value);
    void resetEconomizerMaximumLimitEnthalpy();

    boost::optional<double> getEconomizerMaximumLimitDewpointTemperature() const;
    bool setEconomizerMaximumLimitDewpointTemperature(double value);
    void resetEconomizerMaximumLimitDewpointTemperature();

    boost::optional<double> getEconomizerMinimumLimitDryBulbTemperature() const;
    bool setEconomizerMinimumLimitDryBulbTemperature(double value);
    void resetEconomizerMinimumLimitDryBulbTemperature();

    std::string getLockoutType() const;
    bool setLockoutType(const std::string& value);

    std::string getMinimumLimitType() const;
    bool setMinimumLimitType(const std::string& value);

    boost::optional<bool> getHighHumidityControl() const;
    OS_DEPRECATED(3, 8, 0) bool setHighHumidityControl(bool val);

    double getHighHumidityOutdoorAirFlowRatio() const;
    bool setHighHumidityOutdoorAirFlowRatio(double v);

    bool getControlHighIndoorHumidityBasedOnOutdoorHumidityRatio() const;
    bool setControlHighIndoorHumidityBasedOnOutdoorHumidityRatio(bool v);

    boost::optional<std::string> getHeatRecoveryBypassControlType() const;
    bool setHeatRecoveryBypassControlType(const std::string& v);

    std::string economizerOperationStaging() const;
    bool setEconomizerOperationStaging(const std::string& v);

    ControllerMechanicalVentilation controllerMechanicalVentilation() const;
    bool setControllerMechanicalVentilation(const ControllerMechanicalVentilation& controllerMechanicalVentilation);

    boost::optional<AirLoopHVACOutdoorAirSystem> airLoopHVACOutdoorAirSystem() const;

   protected:
    using ImplType = detail::ControllerOutdoorAir_Impl;

    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;
    friend class Model;

    explicit ControllerOutdoorAir(std::shared_ptr<detail::ControllerOutdoorAir_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
