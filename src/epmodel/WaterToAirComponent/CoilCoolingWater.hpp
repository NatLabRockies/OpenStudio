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

namespace detail {
class CoilCoolingWater_Impl;
}

class EPMODEL_API CoilCoolingWater : public WaterToAirComponent
{
 public:
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
  // - API: Preserve openstudio::model scalar accessor names/signatures for model-counterpart compatibility.
  // - Field Mapping: design* scalar APIs map directly to EnergyPlus Coil:Cooling:Water design scalar fields.
  // - Field Mapping: typeOfAnalysis and heatExchangerConfiguration map directly to EnergyPlus TypeofAnalysis and HeatExchangerConfiguration.
  // - ForwardTranslator evidence: ForwardTranslateCoilCoolingWater.cpp writes these exact scalar fields and autosize semantics.
  // - Field Mapping: availability schedule, node names, and condensate tank linkage fields are relationship-like and excluded in this scalar scaffold phase.
  boost::optional<double> designWaterFlowRate() const;
  bool setDesignWaterFlowRate(double value);
  bool isDesignWaterFlowRateAutosized() const;
  void autosizeDesignWaterFlowRate();

  boost::optional<double> designAirFlowRate() const;
  bool setDesignAirFlowRate(double value);
  bool isDesignAirFlowRateAutosized() const;
  void autosizeDesignAirFlowRate();

  boost::optional<double> designInletWaterTemperature() const;
  bool setDesignInletWaterTemperature(double value);
  bool isDesignInletWaterTemperatureAutosized() const;
  void autosizeDesignInletWaterTemperature();

  boost::optional<double> designInletAirTemperature() const;
  bool setDesignInletAirTemperature(double value);
  bool isDesignInletAirTemperatureAutosized() const;
  void autosizeDesignInletAirTemperature();

  boost::optional<double> designOutletAirTemperature() const;
  bool setDesignOutletAirTemperature(double value);
  bool isDesignOutletAirTemperatureAutosized() const;
  void autosizeDesignOutletAirTemperature();

  boost::optional<double> designInletAirHumidityRatio() const;
  bool setDesignInletAirHumidityRatio(double value);
  bool isDesignInletAirHumidityRatioAutosized() const;
  void autosizeDesignInletAirHumidityRatio();

  boost::optional<double> designOutletAirHumidityRatio() const;
  bool setDesignOutletAirHumidityRatio(double value);
  bool isDesignOutletAirHumidityRatioAutosized() const;
  void autosizeDesignOutletAirHumidityRatio();

  std::string typeOfAnalysis() const;
  bool setTypeOfAnalysis(const std::string& value);

  std::string heatExchangerConfiguration() const;
  bool setHeatExchangerConfiguration(const std::string& value);

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
