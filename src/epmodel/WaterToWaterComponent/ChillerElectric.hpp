/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CHILLERELECTRIC_HPP
#define EPMODEL_CHILLERELECTRIC_HPP

#include "EPModelAPI.hpp"
#include "WaterToWaterComponent/WaterToWaterComponent.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;
class Node;
class PlantLoop;

namespace detail {
class ChillerElectric_Impl;
}

class EPMODEL_API ChillerElectric : public WaterToWaterComponent
{
 public:
  explicit ChillerElectric(const Model& model);

  virtual ~ChillerElectric() override = default;
  ChillerElectric(const ChillerElectric& other) = default;
  ChillerElectric(ChillerElectric&& other) = default;
  ChillerElectric& operator=(const ChillerElectric&) = default;
  ChillerElectric& operator=(ChillerElectric&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> condenserTypeValues();
  static std::vector<std::string> chillerFlowModeValues();

  boost::optional<PlantLoop> chilledWaterLoop() const;
  boost::optional<Node> chilledWaterInletNode() const;
  boost::optional<Node> chilledWaterOutletNode() const;

  boost::optional<PlantLoop> condenserWaterLoop() const;
  boost::optional<Node> condenserInletNode() const;
  boost::optional<Node> condenserOutletNode() const;

  boost::optional<PlantLoop> heatRecoveryLoop() const;
  boost::optional<Node> heatRecoveryInletNode() const;
  boost::optional<Node> heatRecoveryOutletNode() const;

  // Schema Alignment Notes:
  // - Status: Scalar Parity. This type wraps the direct EnergyPlus `Chiller:Electric` object and exposes useful topology accessors, but it does not have a same-name canonical model counterpart.
  // - Canonical Counterpart: none.
  // - Implemented Parity: Scalar accessors for condenser type, nominal capacity/COP, part-load ratios, condenser behavior, chilled-water and condenser-water sizing, heat recovery, end-use metadata, and thermosiphon settings preserve the public IDD-derived API.
  // - Documented Delta: `chilledWaterLoop`, `condenserWaterLoop`, and `heatRecoveryLoop` style navigation are epmodel convenience APIs for EnergyPlus plant topology; canonical `openstudio::model` represents this space through more specific chiller wrappers rather than a one-to-one `ChillerElectric` type.
  // - Field/Storage Mapping: The public API is organized around EnergyPlus `Chiller:Electric` storage and loop wiring, not around a canonical OpenStudio class name.
  // - Evidence: `src/model/ChillerElectricEIR.hpp`, `src/model/ChillerElectricReformulatedEIR.hpp`, `src/model/ChillerElectricASHRAE205.hpp`, and the matching forward translators show how the canonical model splits this EnergyPlus space across multiple more specific wrappers.
  // - Remaining Parity Work: Keep this note conservative and revisit only if a future canonical wrapper is introduced for the aggregated EnergyPlus `Chiller:Electric` object.
  std::string condenserType() const;
  bool isCondenserTypeDefaulted() const;
  bool setCondenserType(const std::string& condenserType);
  void resetCondenserType();

  boost::optional<double> nominalCapacity() const;
  bool isNominalCapacityAutosized() const;
  bool setNominalCapacity(double nominalCapacity);
  void autosizeNominalCapacity();

  double nominalCOP() const;
  bool setNominalCOP(double nominalCOP);

  boost::optional<double> minimumPartLoadRatio() const;
  bool setMinimumPartLoadRatio(double minimumPartLoadRatio);
  void resetMinimumPartLoadRatio();

  boost::optional<double> maximumPartLoadRatio() const;
  bool setMaximumPartLoadRatio(double maximumPartLoadRatio);
  void resetMaximumPartLoadRatio();

  boost::optional<double> optimumPartLoadRatio() const;
  bool setOptimumPartLoadRatio(double optimumPartLoadRatio);
  void resetOptimumPartLoadRatio();

  boost::optional<double> designCondenserInletTemperature() const;
  bool setDesignCondenserInletTemperature(double designCondenserInletTemperature);
  void resetDesignCondenserInletTemperature();

  double temperatureRiseCoefficient() const;
  bool setTemperatureRiseCoefficient(double temperatureRiseCoefficient);

  boost::optional<double> designChilledWaterOutletTemperature() const;
  bool setDesignChilledWaterOutletTemperature(double designChilledWaterOutletTemperature);
  void resetDesignChilledWaterOutletTemperature();

  boost::optional<double> designChilledWaterFlowRate() const;
  bool isDesignChilledWaterFlowRateAutosized() const;
  bool setDesignChilledWaterFlowRate(double designChilledWaterFlowRate);
  void resetDesignChilledWaterFlowRate();
  void autosizeDesignChilledWaterFlowRate();

  boost::optional<double> designCondenserFluidFlowRate() const;
  bool isDesignCondenserFluidFlowRateAutosized() const;
  bool setDesignCondenserFluidFlowRate(double designCondenserFluidFlowRate);
  void resetDesignCondenserFluidFlowRate();
  void autosizeDesignCondenserFluidFlowRate();

  boost::optional<double> coefficient1ofCapacityRatioCurve() const;
  bool setCoefficient1ofCapacityRatioCurve(double coefficient1ofCapacityRatioCurve);
  void resetCoefficient1ofCapacityRatioCurve();

  boost::optional<double> coefficient2ofCapacityRatioCurve() const;
  bool setCoefficient2ofCapacityRatioCurve(double coefficient2ofCapacityRatioCurve);
  void resetCoefficient2ofCapacityRatioCurve();

  boost::optional<double> coefficient3ofCapacityRatioCurve() const;
  bool setCoefficient3ofCapacityRatioCurve(double coefficient3ofCapacityRatioCurve);
  void resetCoefficient3ofCapacityRatioCurve();

  boost::optional<double> coefficient1ofPowerRatioCurve() const;
  bool setCoefficient1ofPowerRatioCurve(double coefficient1ofPowerRatioCurve);
  void resetCoefficient1ofPowerRatioCurve();

  boost::optional<double> coefficient2ofPowerRatioCurve() const;
  bool setCoefficient2ofPowerRatioCurve(double coefficient2ofPowerRatioCurve);
  void resetCoefficient2ofPowerRatioCurve();

  boost::optional<double> coefficient3ofPowerRatioCurve() const;
  bool setCoefficient3ofPowerRatioCurve(double coefficient3ofPowerRatioCurve);
  void resetCoefficient3ofPowerRatioCurve();

  boost::optional<double> coefficient1ofFullLoadRatioCurve() const;
  bool setCoefficient1ofFullLoadRatioCurve(double coefficient1ofFullLoadRatioCurve);
  void resetCoefficient1ofFullLoadRatioCurve();

  boost::optional<double> coefficient2ofFullLoadRatioCurve() const;
  bool setCoefficient2ofFullLoadRatioCurve(double coefficient2ofFullLoadRatioCurve);
  void resetCoefficient2ofFullLoadRatioCurve();

  boost::optional<double> coefficient3ofFullLoadRatioCurve() const;
  bool setCoefficient3ofFullLoadRatioCurve(double coefficient3ofFullLoadRatioCurve);
  void resetCoefficient3ofFullLoadRatioCurve();

  boost::optional<double> chilledWaterOutletTemperatureLowerLimit() const;
  bool setChilledWaterOutletTemperatureLowerLimit(double chilledWaterOutletTemperatureLowerLimit);
  void resetChilledWaterOutletTemperatureLowerLimit();

  std::string chillerFlowMode() const;
  bool isChillerFlowModeDefaulted() const;
  bool setChillerFlowMode(const std::string& chillerFlowMode);
  void resetChillerFlowMode();

  boost::optional<double> designHeatRecoveryWaterFlowRate() const;
  bool isDesignHeatRecoveryWaterFlowRateAutosized() const;
  bool setDesignHeatRecoveryWaterFlowRate(double designHeatRecoveryWaterFlowRate);
  void resetDesignHeatRecoveryWaterFlowRate();
  void autosizeDesignHeatRecoveryWaterFlowRate();

  double sizingFactor() const;
  bool isSizingFactorDefaulted() const;
  bool setSizingFactor(double sizingFactor);
  void resetSizingFactor();

  double basinHeaterCapacity() const;
  bool isBasinHeaterCapacityDefaulted() const;
  bool setBasinHeaterCapacity(double basinHeaterCapacity);
  void resetBasinHeaterCapacity();

  double basinHeaterSetpointTemperature() const;
  bool isBasinHeaterSetpointTemperatureDefaulted() const;
  bool setBasinHeaterSetpointTemperature(double basinHeaterSetpointTemperature);
  void resetBasinHeaterSetpointTemperature();

  boost::optional<double> condenserHeatRecoveryRelativeCapacityFraction() const;
  bool setCondenserHeatRecoveryRelativeCapacityFraction(double condenserHeatRecoveryRelativeCapacityFraction);
  void resetCondenserHeatRecoveryRelativeCapacityFraction();

  std::string endUseSubcategory() const;
  bool isEndUseSubcategoryDefaulted() const;
  bool setEndUseSubcategory(const std::string& endUseSubcategory);
  void resetEndUseSubcategory();

  double thermosiphonMinimumTemperatureDifference() const;
  bool isThermosiphonMinimumTemperatureDifferenceDefaulted() const;
  bool setThermosiphonMinimumTemperatureDifference(double thermosiphonMinimumTemperatureDifference);
  void resetThermosiphonMinimumTemperatureDifference();

 protected:
  using ImplType = detail::ChillerElectric_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit ChillerElectric(std::shared_ptr<detail::ChillerElectric_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
