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
  // - Status: Scalar Parity. The scalar design fields and enumerated choices are aligned, while relationship-heavy convenience behavior remains intentionally outside this wrapper surface.
  // - Canonical Counterpart: openstudio::model::CoilCoolingWater.
  // - Implemented Parity: `designWaterFlowRate`, `designAirFlowRate`, `designInletWaterTemperature`, `designInletAirTemperature`, `designOutletAirTemperature`, `designInletAirHumidityRatio`, `designOutletAirHumidityRatio`, `typeOfAnalysis`, `heatExchangerConfiguration`, and their autosize/setter helpers preserve the canonical scalar contract.
  // - Documented Delta: Availability schedule, controller linkage, node-name accessors, and AFN/equivalent-duct helpers are not exposed here even though the canonical model type owns them.
  // - Field/Storage Mapping: Scalar design and choice fields map directly to the corresponding EnergyPlus `Coil:Cooling:Water` fields.
  // - Evidence: `src/model/CoilCoolingWater.hpp`, `src/model/CoilCoolingWater.cpp`, `src/energyplus/ForwardTranslator/ForwardTranslateCoilCoolingWater.cpp`, and `src/model/test/CoilCoolingWater_GTest.cpp`.
  // - Remaining Parity Work: Add the omitted relationship and helper APIs only if this family is brought beyond scalar parity.
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
