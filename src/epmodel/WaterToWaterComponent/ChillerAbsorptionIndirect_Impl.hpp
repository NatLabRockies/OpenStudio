/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CHILLERABSORPTIONINDIRECT_IMPL_HPP
#define EPMODEL_CHILLERABSORPTIONINDIRECT_IMPL_HPP

#include "WaterToWaterComponent/WaterToWaterComponent_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

class Curve;
class PlantLoop;
class Node;

namespace detail {

class EPMODEL_API ChillerAbsorptionIndirect_Impl : public WaterToWaterComponent_Impl
{
 public:
  using WaterToWaterComponent_Impl::WaterToWaterComponent_Impl;
  virtual ~ChillerAbsorptionIndirect_Impl() override = default;

  unsigned supplyInletPort() const override;
  unsigned supplyOutletPort() const override;
  unsigned demandInletPort() const override;
  unsigned demandOutletPort() const override;
  unsigned tertiaryInletPort() const override;
  unsigned tertiaryOutletPort() const override;
  bool addToNode(Node& node) override;
  bool addToTertiaryNode(Node& node) override;
  bool removeFromTertiaryPlantLoop() override;
  std::vector<ModelObject> children() const override;

  ComponentType componentType() const override;
  std::vector<FuelType> coolingFuelTypes() const override;
  std::vector<FuelType> heatingFuelTypes() const override;
  std::vector<AppGFuelType> appGHeatingFuelTypes() const override;

  boost::optional<PlantLoop> chilledWaterLoop() const;
  boost::optional<PlantLoop> condenserWaterLoop() const;
  boost::optional<PlantLoop> generatorLoop() const;

  std::vector<std::string> chillerFlowModeValues() const;
  std::vector<std::string> generatorHeatSourceTypeValues() const;

  boost::optional<double> nominalCapacity() const;
  bool isNominalCapacityAutosized() const;
  bool setNominalCapacity(double nominalCapacity);
  void autosizeNominalCapacity();
  boost::optional<double> autosizedNominalCapacity() const;

  boost::optional<double> nominalPumpingPower() const;
  bool isNominalPumpingPowerAutosized() const;
  bool setNominalPumpingPower(double nominalPumpingPower);
  void autosizeNominalPumpingPower();
  boost::optional<double> autosizedNominalPumpingPower() const;

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
  boost::optional<double> autosizedDesignChilledWaterFlowRate() const;

  boost::optional<double> designCondenserWaterFlowRate() const;
  bool isDesignCondenserWaterFlowRateAutosized() const;
  bool setDesignCondenserWaterFlowRate(double designCondenserWaterFlowRate);
  void autosizeDesignCondenserWaterFlowRate();
  boost::optional<double> autosizedDesignCondenserWaterFlowRate() const;

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
  boost::optional<double> autosizedDesignGeneratorFluidFlowRate() const;

  double temperatureLowerLimitGeneratorInlet() const;
  bool setTemperatureLowerLimitGeneratorInlet(double temperatureLowerLimitGeneratorInlet);

  double degreeofSubcoolinginSteamGenerator() const;
  bool setDegreeofSubcoolinginSteamGenerator(double degreeofSubcoolinginSteamGenerator);

  double degreeofSubcoolinginSteamCondensateLoop() const;
  bool setDegreeofSubcoolinginSteamCondensateLoop(double degreeofSubcoolinginSteamCondensateLoop);

  double sizingFactor() const;
  bool setSizingFactor(double sizingFactor);
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
