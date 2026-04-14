/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CHILLERABSORPTIONINDIRECT_HPP
#define EPMODEL_CHILLERABSORPTIONINDIRECT_HPP

#include "EPModelAPI.hpp"
#include "WaterToWaterComponent/WaterToWaterComponent.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;
class Curve;
class PlantLoop;

namespace detail {
class ChillerAbsorptionIndirect_Impl;
}

class EPMODEL_API ChillerAbsorptionIndirect : public WaterToWaterComponent
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
  // - Status: Parity with documented deltas. The canonical scalar, curve, and generator-loop relationship surface is aligned.
  // - Canonical Counterpart: openstudio::model::ChillerAbsorptionIndirect.
  // - Implemented Parity: Canonical constructor defaults, required curve relationships, chilled/condenser/generator loop conveniences, and
  //   generator-loop routing semantics preserve the model-side API shape.
  // - Documented Delta: Autosized-value helpers are present but remain epmodel stubs that return `none` until autosized results are surfaced here.
  // - Field/Storage Mapping: Scalar wrappers target EnergyPlus `Chiller:Absorption:Indirect` fields directly; curve and loop relationships are
  //   persisted as normal object links on the same object and interpreted through the shared water-to-water topology layer.
  // - Evidence: `src/model/ChillerAbsorptionIndirect.hpp`, `src/model/ChillerAbsorptionIndirect.cpp`, and
  //   `src/energyplus/ForwardTranslator/ForwardTranslateChillerAbsorptionIndirect.cpp`.
  // - Remaining Parity Work: Further work should only factor shared chiller abstractions if multiple wrappers need the same non-generic behavior.
  boost::optional<double> nominalCapacity() const;
  bool isNominalCapacityAutosized() const;
  bool setNominalCapacity(double nominalCapacity);
  void autosizeNominalCapacity();

  boost::optional<double> nominalPumpingPower() const;
  bool isNominalPumpingPowerAutosized() const;
  bool setNominalPumpingPower(double nominalPumpingPower);
  void autosizeNominalPumpingPower();

  double minimumPartLoadRatio() const;
  bool setMinimumPartLoadRatio(double minimumPartLoadRatio);

  double maximumPartLoadRatio() const;
  bool setMaximumPartLoadRatio(double maximumPartLoadRatio);

  double optimumPartLoadRatio() const;
  bool setOptimumPartLoadRatio(double optimumPartLoadRatio);

  double designCondenserInletTemperature() const;
  bool setDesignCondenserInletTemperature(double designCondenserInletTemperature);

  double condenserInletTemperatureLowerLimit() const;
  bool setCondenserInletTemperatureLowerLimit(double condenserInletTemperatureLowerLimit);

  double chilledWaterOutletTemperatureLowerLimit() const;
  bool setChilledWaterOutletTemperatureLowerLimit(double chilledWaterOutletTemperatureLowerLimit);

  boost::optional<double> designChilledWaterFlowRate() const;
  bool isDesignChilledWaterFlowRateAutosized() const;
  bool setDesignChilledWaterFlowRate(double designChilledWaterFlowRate);
  void autosizeDesignChilledWaterFlowRate();

  boost::optional<double> designCondenserWaterFlowRate() const;
  bool isDesignCondenserWaterFlowRateAutosized() const;
  bool setDesignCondenserWaterFlowRate(double designCondenserWaterFlowRate);
  void autosizeDesignCondenserWaterFlowRate();

  std::string chillerFlowMode() const;
  bool setChillerFlowMode(const std::string& chillerFlowMode);

  Curve generatorHeatInputFunctionofPartLoadRatioCurve() const;
  bool setGeneratorHeatInputFunctionofPartLoadRatioCurve(const Curve& curve);

  Curve pumpElectricInputFunctionofPartLoadRatioCurve() const;
  bool setPumpElectricInputFunctionofPartLoadRatioCurve(const Curve& curve);

  Curve capacityCorrectionFunctionofCondenserTemperatureCurve() const;
  bool setCapacityCorrectionFunctionofCondenserTemperatureCurve(const Curve& curve);

  Curve capacityCorrectionFunctionofChilledWaterTemperatureCurve() const;
  bool setCapacityCorrectionFunctionofChilledWaterTemperatureCurve(const Curve& curve);

  Curve capacityCorrectionFunctionofGeneratorTemperatureCurve() const;
  bool setCapacityCorrectionFunctionofGeneratorTemperatureCurve(const Curve& curve);

  Curve generatorHeatInputCorrectionFunctionofCondenserTemperatureCurve() const;
  bool setGeneratorHeatInputCorrectionFunctionofCondenserTemperatureCurve(const Curve& curve);

  Curve generatorHeatInputCorrectionFunctionofChilledWaterTemperatureCurve() const;
  bool setGeneratorHeatInputCorrectionFunctionofChilledWaterTemperatureCurve(const Curve& curve);

  std::string generatorHeatSourceType() const;
  bool setGeneratorHeatSourceType(const std::string& generatorHeatSourceType);

  boost::optional<double> designGeneratorFluidFlowRate() const;
  bool isDesignGeneratorFluidFlowRateAutosized() const;
  bool setDesignGeneratorFluidFlowRate(double designGeneratorFluidFlowRate);
  void autosizeDesignGeneratorFluidFlowRate();

  double temperatureLowerLimitGeneratorInlet() const;
  bool setTemperatureLowerLimitGeneratorInlet(double temperatureLowerLimitGeneratorInlet);

  double degreeofSubcoolinginSteamGenerator() const;
  bool setDegreeofSubcoolinginSteamGenerator(double degreeofSubcoolinginSteamGenerator);

  double degreeofSubcoolinginSteamCondensateLoop() const;
  bool setDegreeofSubcoolinginSteamCondensateLoop(double degreeofSubcoolinginSteamCondensateLoop);

  double sizingFactor() const;
  bool setSizingFactor(double sizingFactor);

  boost::optional<double> autosizedNominalCapacity() const;
  boost::optional<double> autosizedNominalPumpingPower() const;
  boost::optional<double> autosizedDesignChilledWaterFlowRate() const;
  boost::optional<double> autosizedDesignCondenserWaterFlowRate() const;
  boost::optional<double> autosizedDesignGeneratorFluidFlowRate() const;

  boost::optional<PlantLoop> chilledWaterLoop() const;
  boost::optional<PlantLoop> condenserWaterLoop() const;
  boost::optional<PlantLoop> generatorLoop() const;

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
