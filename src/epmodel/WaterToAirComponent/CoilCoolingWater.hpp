/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILCOOLINGWATER_HPP
#define EPMODEL_COILCOOLINGWATER_HPP

#include "EPModelAPI.hpp"
#include "WaterToAirComponent/WaterToAirComponent.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;
class Schedule;
class ControllerWaterCoil;

namespace detail {
class CoilCoolingWater_Impl;
}

class EPMODEL_API CoilCoolingWater : public WaterToAirComponent
{
 public:
  CoilCoolingWater(const Model& model, Schedule& availabilitySchedule);
  explicit CoilCoolingWater(const Model& model);

  virtual ~CoilCoolingWater() override = default;
  CoilCoolingWater(const CoilCoolingWater& other) = default;
  CoilCoolingWater(CoilCoolingWater&& other) = default;
  CoilCoolingWater& operator=(const CoilCoolingWater&) = default;
  CoilCoolingWater& operator=(CoilCoolingWater&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> typeOfAnalysisValues();
  static std::vector<std::string> heatExchangerConfigurationValues();

  // Schema Alignment Notes:
  // - Status: Partial Parity. The scalar design fields, availability schedule surface, and controller linkage now align,
  //   while AFN helper objects remain outside this wrapper surface.
  // - Canonical Counterpart: openstudio::model::CoilCoolingWater.
  // - Implemented Parity: `setAvailabilitySchedule`, `setAvailableSchedule`, `controllerWaterCoil`,
  //   `designWaterFlowRate`, `designAirFlowRate`, `designInletWaterTemperature`,
  //   `designInletAirTemperature`, `designOutletAirTemperature`, `designInletAirHumidityRatio`,
  //   `designOutletAirHumidityRatio`, `typeOfAnalysis`, `heatExchangerConfiguration`, and their autosize/setter helpers
  //   preserve the canonical coil-facing API.
  // - Documented Delta: Node-name convenience helpers and AFN/equivalent-duct helpers are still not exposed here.
  //   For malformed imported data with no persisted availability schedule, the getter returns the model always-on
  //   discrete schedule without repairing storage.
  // - Field/Storage Mapping: The availability schedule and scalar design fields map directly to EnergyPlus
  //   `Coil:Cooling:Water`. Controller linkage is inferred from the persisted `Controller:WaterCoil` sensor and actuator
  //   nodes because the EnergyPlus controller object does not store a direct back-reference to the coil. If malformed
  //   imported data omits the required availability schedule, the getter falls back to the model always-on discrete
  //   schedule without mutating persisted state.
  // - Evidence: `src/model/CoilCoolingWater.hpp`, `src/model/CoilCoolingWater.cpp`, `src/energyplus/ForwardTranslator/ForwardTranslateCoilCoolingWater.cpp`, and `src/model/test/CoilCoolingWater_GTest.cpp`.
  // - Remaining Parity Work: Add the omitted node-name and AFN helper APIs only if the supporting epmodel wrappers are
  //   developed.
  Schedule availabilitySchedule() const;

  /** \deprecated */
  Schedule availableSchedule() const;

  bool setAvailabilitySchedule(Schedule& schedule);

  /** \deprecated */
  bool setAvailableSchedule(Schedule& schedule);

  boost::optional<double> designWaterFlowRate() const;
  boost::optional<double> autosizedDesignWaterFlowRate() const;
  bool setDesignWaterFlowRate(double value);
  bool isDesignWaterFlowRateAutosized() const;
  void autosizeDesignWaterFlowRate();

  boost::optional<double> designAirFlowRate() const;
  boost::optional<double> autosizedDesignAirFlowRate() const;
  bool setDesignAirFlowRate(double value);
  bool isDesignAirFlowRateAutosized() const;
  void autosizeDesignAirFlowRate();

  boost::optional<double> designInletWaterTemperature() const;
  boost::optional<double> autosizedDesignInletWaterTemperature() const;
  bool setDesignInletWaterTemperature(double value);
  bool isDesignInletWaterTemperatureAutosized() const;
  void autosizeDesignInletWaterTemperature();

  boost::optional<double> designInletAirTemperature() const;
  boost::optional<double> autosizedDesignInletAirTemperature() const;
  bool setDesignInletAirTemperature(double value);
  bool isDesignInletAirTemperatureAutosized() const;
  void autosizeDesignInletAirTemperature();

  boost::optional<double> designOutletAirTemperature() const;
  boost::optional<double> autosizedDesignOutletAirTemperature() const;
  bool setDesignOutletAirTemperature(double value);
  bool isDesignOutletAirTemperatureAutosized() const;
  void autosizeDesignOutletAirTemperature();

  boost::optional<double> designInletAirHumidityRatio() const;
  boost::optional<double> autosizedDesignInletAirHumidityRatio() const;
  bool setDesignInletAirHumidityRatio(double value);
  bool isDesignInletAirHumidityRatioAutosized() const;
  void autosizeDesignInletAirHumidityRatio();

  boost::optional<double> designOutletAirHumidityRatio() const;
  boost::optional<double> autosizedDesignOutletAirHumidityRatio() const;
  bool setDesignOutletAirHumidityRatio(double value);
  bool isDesignOutletAirHumidityRatioAutosized() const;
  void autosizeDesignOutletAirHumidityRatio();

  std::string typeOfAnalysis() const;
  bool setTypeOfAnalysis(const std::string& value);

  std::string heatExchangerConfiguration() const;
  bool setHeatExchangerConfiguration(const std::string& value);

  boost::optional<ControllerWaterCoil> controllerWaterCoil() const;
  boost::optional<double> autosizedDesignCoilLoad() const;

 protected:
  using ImplType = detail::CoilCoolingWater_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit CoilCoolingWater(std::shared_ptr<detail::CoilCoolingWater_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
