/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CHILLERABSORPTIONINDIRECT_HPP
#define EPMODEL_CHILLERABSORPTIONINDIRECT_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class ChillerAbsorptionIndirect_Impl;
}

class EPMODEL_API ChillerAbsorptionIndirect : public ModelObject
{
 public:
  explicit ChillerAbsorptionIndirect(const Model& model);

  virtual ~ChillerAbsorptionIndirect() override = default;
  ChillerAbsorptionIndirect(const ChillerAbsorptionIndirect& other) = default;
  ChillerAbsorptionIndirect(ChillerAbsorptionIndirect&& other) = default;
  ChillerAbsorptionIndirect& operator=(const ChillerAbsorptionIndirect&) = default;
  ChillerAbsorptionIndirect& operator=(ChillerAbsorptionIndirect&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> chillerFlowModeValues();
  static std::vector<std::string> generatorHeatSourceTypeValues();

  // Schema Alignment Notes:
  // - API: Preserve openstudio::model::ChillerAbsorptionIndirect scalar accessor names/signatures for counterpart parity.
  // - Field Mapping: Preserved scalar APIs map directly to EnergyPlus Chiller:Absorption:Indirect scalar fields.
  // - Field Mapping: Node and curve relationship APIs are intentionally excluded in this scalar-only scaffold pass.
  // - ForwardTranslator evidence: model::ForwardTranslateChillerAbsorptionIndirect maps these scalar methods to matching E+ fields.
  // - TODO(parity): Add excluded relationship APIs in a dedicated relationship pass.
  boost::optional<double> nominalCapacity() const;
  bool isNominalCapacityAutosized() const;

  boost::optional<double> nominalPumpingPower() const;
  bool isNominalPumpingPowerAutosized() const;

  double minimumPartLoadRatio() const;
  double maximumPartLoadRatio() const;
  double optimumPartLoadRatio() const;
  double designCondenserInletTemperature() const;
  double condenserInletTemperatureLowerLimit() const;
  double chilledWaterOutletTemperatureLowerLimit() const;

  boost::optional<double> designChilledWaterFlowRate() const;
  bool isDesignChilledWaterFlowRateAutosized() const;

  boost::optional<double> designCondenserWaterFlowRate() const;
  bool isDesignCondenserWaterFlowRateAutosized() const;

  std::string chillerFlowMode() const;
  std::string generatorHeatSourceType() const;

  boost::optional<double> designGeneratorFluidFlowRate() const;
  bool isDesignGeneratorFluidFlowRateAutosized() const;

  double temperatureLowerLimitGeneratorInlet() const;
  double degreeofSubcoolinginSteamGenerator() const;
  double degreeofSubcoolinginSteamCondensateLoop() const;
  double sizingFactor() const;

  bool setNominalCapacity(double nominalCapacity);
  void autosizeNominalCapacity();

  bool setNominalPumpingPower(double nominalPumpingPower);
  void autosizeNominalPumpingPower();

  bool setMinimumPartLoadRatio(double minimumPartLoadRatio);
  bool setMaximumPartLoadRatio(double maximumPartLoadRatio);
  bool setOptimumPartLoadRatio(double optimumPartLoadRatio);
  bool setDesignCondenserInletTemperature(double designCondenserInletTemperature);
  bool setCondenserInletTemperatureLowerLimit(double condenserInletTemperatureLowerLimit);
  bool setChilledWaterOutletTemperatureLowerLimit(double chilledWaterOutletTemperatureLowerLimit);

  bool setDesignChilledWaterFlowRate(double designChilledWaterFlowRate);
  void autosizeDesignChilledWaterFlowRate();

  bool setDesignCondenserWaterFlowRate(double designCondenserWaterFlowRate);
  void autosizeDesignCondenserWaterFlowRate();

  bool setChillerFlowMode(const std::string& chillerFlowMode);
  bool setGeneratorHeatSourceType(const std::string& generatorHeatSourceType);

  bool setDesignGeneratorFluidFlowRate(double designGeneratorFluidFlowRate);
  void autosizeDesignGeneratorFluidFlowRate();

  bool setTemperatureLowerLimitGeneratorInlet(double temperatureLowerLimitGeneratorInlet);
  bool setDegreeofSubcoolinginSteamGenerator(double degreeofSubcoolinginSteamGenerator);
  bool setDegreeofSubcoolinginSteamCondensateLoop(double degreeofSubcoolinginSteamCondensateLoop);
  bool setSizingFactor(double sizingFactor);

 protected:
  using ImplType = detail::ChillerAbsorptionIndirect_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit ChillerAbsorptionIndirect(std::shared_ptr<detail::ChillerAbsorptionIndirect_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
