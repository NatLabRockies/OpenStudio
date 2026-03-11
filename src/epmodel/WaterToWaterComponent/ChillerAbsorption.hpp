/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CHILLERABSORPTION_HPP
#define EPMODEL_CHILLERABSORPTION_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class ChillerAbsorption_Impl;
}

class EPMODEL_API ChillerAbsorption : public ModelObject
{
 public:
  explicit ChillerAbsorption(const Model& model);

  virtual ~ChillerAbsorption() override = default;
  ChillerAbsorption(const ChillerAbsorption& other) = default;
  ChillerAbsorption(ChillerAbsorption&& other) = default;
  ChillerAbsorption& operator=(const ChillerAbsorption&) = default;
  ChillerAbsorption& operator=(ChillerAbsorption&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> chillerFlowModeValues();
  static std::vector<std::string> generatorHeatSourceTypeValues();

  // Schema Alignment Notes:
  // - API: Preserve openstudio::model::ChillerAbsorption scalar accessor names/signatures for counterpart parity.
  // - Field Mapping: Preserved scalar APIs map directly to EnergyPlus Chiller:Absorption scalar fields.
  // - Field Mapping: Generator/plant-loop relationship behavior is excluded in epmodel scalar-only scaffold.
  // - ForwardTranslator evidence: model::ForwardTranslateChillerAbsorption maps these scalar methods to matching E+ fields.
  // - TODO(parity): Add excluded node/reference relationship APIs in a dedicated relationship pass.
  boost::optional<double> nominalCapacity() const;
  bool isNominalCapacityAutosized() const;

  boost::optional<double> nominalPumpingPower() const;
  bool isNominalPumpingPowerAutosized() const;

  double minimumPartLoadRatio() const;
  double maximumPartLoadRatio() const;
  double optimumPartLoadRatio() const;
  double designCondenserInletTemperature() const;

  boost::optional<double> designChilledWaterFlowRate() const;
  bool isDesignChilledWaterFlowRateAutosized() const;

  boost::optional<double> designCondenserWaterFlowRate() const;
  bool isDesignCondenserWaterFlowRateAutosized() const;

  double coefficient1oftheHotWaterorSteamUsePartLoadRatioCurve() const;
  double coefficient2oftheHotWaterorSteamUsePartLoadRatioCurve() const;
  double coefficient3oftheHotWaterorSteamUsePartLoadRatioCurve() const;

  double coefficient1ofthePumpElectricUsePartLoadRatioCurve() const;
  double coefficient2ofthePumpElectricUsePartLoadRatioCurve() const;
  double coefficient3ofthePumpElectricUsePartLoadRatioCurve() const;

  double chilledWaterOutletTemperatureLowerLimit() const;

  std::string chillerFlowMode() const;
  std::string generatorHeatSourceType() const;

  boost::optional<double> designGeneratorFluidFlowRate() const;
  bool isDesignGeneratorFluidFlowRateAutosized() const;

  double degreeofSubcoolinginSteamGenerator() const;
  double sizingFactor() const;

  bool setNominalCapacity(double nominalCapacity);
  void autosizeNominalCapacity();

  bool setNominalPumpingPower(double nominalPumpingPower);
  void autosizeNominalPumpingPower();

  bool setMinimumPartLoadRatio(double minimumPartLoadRatio);
  bool setMaximumPartLoadRatio(double maximumPartLoadRatio);
  bool setOptimumPartLoadRatio(double optimumPartLoadRatio);
  bool setDesignCondenserInletTemperature(double designCondenserInletTemperature);

  bool setDesignChilledWaterFlowRate(double designChilledWaterFlowRate);
  void autosizeDesignChilledWaterFlowRate();

  bool setDesignCondenserWaterFlowRate(double designCondenserWaterFlowRate);
  void autosizeDesignCondenserWaterFlowRate();

  bool setCoefficient1oftheHotWaterorSteamUsePartLoadRatioCurve(double coefficient1oftheHotWaterorSteamUsePartLoadRatioCurve);
  bool setCoefficient2oftheHotWaterorSteamUsePartLoadRatioCurve(double coefficient2oftheHotWaterorSteamUsePartLoadRatioCurve);
  bool setCoefficient3oftheHotWaterorSteamUsePartLoadRatioCurve(double coefficient3oftheHotWaterorSteamUsePartLoadRatioCurve);

  bool setCoefficient1ofthePumpElectricUsePartLoadRatioCurve(double coefficient1ofthePumpElectricUsePartLoadRatioCurve);
  bool setCoefficient2ofthePumpElectricUsePartLoadRatioCurve(double coefficient2ofthePumpElectricUsePartLoadRatioCurve);
  bool setCoefficient3ofthePumpElectricUsePartLoadRatioCurve(double coefficient3ofthePumpElectricUsePartLoadRatioCurve);

  bool setChilledWaterOutletTemperatureLowerLimit(double chilledWaterOutletTemperatureLowerLimit);

  bool setChillerFlowMode(const std::string& chillerFlowMode);
  bool setGeneratorHeatSourceType(const std::string& generatorHeatSourceType);

  bool setDesignGeneratorFluidFlowRate(double designGeneratorFluidFlowRate);
  void autosizeDesignGeneratorFluidFlowRate();

  bool setDegreeofSubcoolinginSteamGenerator(double degreeofSubcoolinginSteamGenerator);
  bool setSizingFactor(double sizingFactor);

 protected:
  using ImplType = detail::ChillerAbsorption_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit ChillerAbsorption(std::shared_ptr<detail::ChillerAbsorption_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
