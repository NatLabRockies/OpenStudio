/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/BoilerHotWater.hpp"
#include "StraightComponent/BoilerHotWater_Impl.hpp"

#include "Loop/PlantLoop.hpp"
#include "Loop/PlantLoop_Impl.hpp"
#include "Model.hpp"
#include "Node.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/Boiler_HotWater_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>

namespace openstudio {
namespace epmodel {

  BoilerHotWater::BoilerHotWater(const Model& model) : StraightComponent(BoilerHotWater::iddObjectType(), model) {
    OS_ASSERT(setNominalThermalEfficiency(0.8));
    OS_ASSERT(setWaterOutletUpperTemperatureLimit(99.0));
    OS_ASSERT(setBoilerFlowMode("ConstantFlow"));
    OS_ASSERT(setSizingFactor(1.0));
    OS_ASSERT(setEndUseSubcategory("General"));
    OS_ASSERT(setOnCycleParasiticElectricLoad(0.0));
    OS_ASSERT(setOffCycleParasiticFuelLoad(0.0));
  }

  BoilerHotWater::BoilerHotWater(std::shared_ptr<detail::BoilerHotWater_Impl> impl) : StraightComponent(std::move(impl)) {}

  IddObjectType BoilerHotWater::iddObjectType() {
    return IddObjectType::Boiler_HotWater;
  }

  std::vector<std::string> BoilerHotWater::validFuelTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Boiler_HotWaterFields::FuelType);
  }

  std::vector<std::string> BoilerHotWater::validEfficiencyCurveTemperatureEvaluationVariableValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::Boiler_HotWaterFields::EfficiencyCurveTemperatureEvaluationVariable);
  }

  std::vector<std::string> BoilerHotWater::validBoilerFlowModeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Boiler_HotWaterFields::BoilerFlowMode);
  }

  std::vector<std::string> BoilerHotWater::fuelTypeValues() {
    return validFuelTypeValues();
  }

  std::vector<std::string> BoilerHotWater::efficiencyCurveTemperatureEvaluationVariableValues() {
    return validEfficiencyCurveTemperatureEvaluationVariableValues();
  }

  std::vector<std::string> BoilerHotWater::boilerFlowModeValues() {
    return validBoilerFlowModeValues();
  }

  std::string BoilerHotWater::fuelType() const {
    return getImpl<detail::BoilerHotWater_Impl>()->fuelType();
  }

  bool BoilerHotWater::setFuelType(const std::string& fuelType) {
    return getImpl<detail::BoilerHotWater_Impl>()->setFuelType(fuelType);
  }

  boost::optional<double> BoilerHotWater::nominalCapacity() const {
    return getImpl<detail::BoilerHotWater_Impl>()->nominalCapacity();
  }

  bool BoilerHotWater::isNominalCapacityAutosized() const {
    return getImpl<detail::BoilerHotWater_Impl>()->isNominalCapacityAutosized();
  }

  bool BoilerHotWater::setNominalCapacity(double nominalCapacity) {
    return getImpl<detail::BoilerHotWater_Impl>()->setNominalCapacity(nominalCapacity);
  }

  void BoilerHotWater::resetNominalCapacity() {
    getImpl<detail::BoilerHotWater_Impl>()->resetNominalCapacity();
  }

  void BoilerHotWater::autosizeNominalCapacity() {
    getImpl<detail::BoilerHotWater_Impl>()->autosizeNominalCapacity();
  }

  double BoilerHotWater::nominalThermalEfficiency() const {
    return getImpl<detail::BoilerHotWater_Impl>()->nominalThermalEfficiency();
  }

  bool BoilerHotWater::setNominalThermalEfficiency(double nominalThermalEfficiency) {
    return getImpl<detail::BoilerHotWater_Impl>()->setNominalThermalEfficiency(nominalThermalEfficiency);
  }

  boost::optional<std::string> BoilerHotWater::efficiencyCurveTemperatureEvaluationVariable() const {
    return getImpl<detail::BoilerHotWater_Impl>()->efficiencyCurveTemperatureEvaluationVariable();
  }

  bool BoilerHotWater::setEfficiencyCurveTemperatureEvaluationVariable(const std::string& efficiencyCurveTemperatureEvaluationVariable) {
    return getImpl<detail::BoilerHotWater_Impl>()->setEfficiencyCurveTemperatureEvaluationVariable(efficiencyCurveTemperatureEvaluationVariable);
  }

  void BoilerHotWater::resetEfficiencyCurveTemperatureEvaluationVariable() {
    getImpl<detail::BoilerHotWater_Impl>()->resetEfficiencyCurveTemperatureEvaluationVariable();
  }

  boost::optional<double> BoilerHotWater::designWaterFlowRate() const {
    return getImpl<detail::BoilerHotWater_Impl>()->designWaterFlowRate();
  }

  bool BoilerHotWater::isDesignWaterFlowRateAutosized() const {
    return getImpl<detail::BoilerHotWater_Impl>()->isDesignWaterFlowRateAutosized();
  }

  bool BoilerHotWater::setDesignWaterFlowRate(double designWaterFlowRate) {
    return getImpl<detail::BoilerHotWater_Impl>()->setDesignWaterFlowRate(designWaterFlowRate);
  }

  void BoilerHotWater::resetDesignWaterFlowRate() {
    getImpl<detail::BoilerHotWater_Impl>()->resetDesignWaterFlowRate();
  }

  void BoilerHotWater::autosizeDesignWaterFlowRate() {
    getImpl<detail::BoilerHotWater_Impl>()->autosizeDesignWaterFlowRate();
  }

  double BoilerHotWater::minimumPartLoadRatio() const {
    return getImpl<detail::BoilerHotWater_Impl>()->minimumPartLoadRatio();
  }

  bool BoilerHotWater::isMinimumPartLoadRatioDefaulted() const {
    return getImpl<detail::BoilerHotWater_Impl>()->isMinimumPartLoadRatioDefaulted();
  }

  bool BoilerHotWater::setMinimumPartLoadRatio(double minimumPartLoadRatio) {
    return getImpl<detail::BoilerHotWater_Impl>()->setMinimumPartLoadRatio(minimumPartLoadRatio);
  }

  void BoilerHotWater::resetMinimumPartLoadRatio() {
    getImpl<detail::BoilerHotWater_Impl>()->resetMinimumPartLoadRatio();
  }

  double BoilerHotWater::maximumPartLoadRatio() const {
    return getImpl<detail::BoilerHotWater_Impl>()->maximumPartLoadRatio();
  }

  bool BoilerHotWater::isMaximumPartLoadRatioDefaulted() const {
    return getImpl<detail::BoilerHotWater_Impl>()->isMaximumPartLoadRatioDefaulted();
  }

  bool BoilerHotWater::setMaximumPartLoadRatio(double maximumPartLoadRatio) {
    return getImpl<detail::BoilerHotWater_Impl>()->setMaximumPartLoadRatio(maximumPartLoadRatio);
  }

  void BoilerHotWater::resetMaximumPartLoadRatio() {
    getImpl<detail::BoilerHotWater_Impl>()->resetMaximumPartLoadRatio();
  }

  double BoilerHotWater::optimumPartLoadRatio() const {
    return getImpl<detail::BoilerHotWater_Impl>()->optimumPartLoadRatio();
  }

  bool BoilerHotWater::isOptimumPartLoadRatioDefaulted() const {
    return getImpl<detail::BoilerHotWater_Impl>()->isOptimumPartLoadRatioDefaulted();
  }

  bool BoilerHotWater::setOptimumPartLoadRatio(double optimumPartLoadRatio) {
    return getImpl<detail::BoilerHotWater_Impl>()->setOptimumPartLoadRatio(optimumPartLoadRatio);
  }

  void BoilerHotWater::resetOptimumPartLoadRatio() {
    getImpl<detail::BoilerHotWater_Impl>()->resetOptimumPartLoadRatio();
  }

  double BoilerHotWater::waterOutletUpperTemperatureLimit() const {
    return getImpl<detail::BoilerHotWater_Impl>()->waterOutletUpperTemperatureLimit();
  }

  bool BoilerHotWater::isWaterOutletUpperTemperatureLimitDefaulted() const {
    return getImpl<detail::BoilerHotWater_Impl>()->isWaterOutletUpperTemperatureLimitDefaulted();
  }

  bool BoilerHotWater::setWaterOutletUpperTemperatureLimit(double waterOutletUpperTemperatureLimit) {
    return getImpl<detail::BoilerHotWater_Impl>()->setWaterOutletUpperTemperatureLimit(waterOutletUpperTemperatureLimit);
  }

  void BoilerHotWater::resetWaterOutletUpperTemperatureLimit() {
    getImpl<detail::BoilerHotWater_Impl>()->resetWaterOutletUpperTemperatureLimit();
  }

  std::string BoilerHotWater::boilerFlowMode() const {
    return getImpl<detail::BoilerHotWater_Impl>()->boilerFlowMode();
  }

  bool BoilerHotWater::isBoilerFlowModeDefaulted() const {
    return getImpl<detail::BoilerHotWater_Impl>()->isBoilerFlowModeDefaulted();
  }

  bool BoilerHotWater::setBoilerFlowMode(const std::string& boilerFlowMode) {
    return getImpl<detail::BoilerHotWater_Impl>()->setBoilerFlowMode(boilerFlowMode);
  }

  void BoilerHotWater::resetBoilerFlowMode() {
    getImpl<detail::BoilerHotWater_Impl>()->resetBoilerFlowMode();
  }

  boost::optional<double> BoilerHotWater::parasiticElectricLoad() const {
    return getImpl<detail::BoilerHotWater_Impl>()->parasiticElectricLoad();
  }

  bool BoilerHotWater::setParasiticElectricLoad(double parasiticElectricLoad) {
    return getImpl<detail::BoilerHotWater_Impl>()->setParasiticElectricLoad(parasiticElectricLoad);
  }

  void BoilerHotWater::resetParasiticElectricLoad() {
    getImpl<detail::BoilerHotWater_Impl>()->resetParasiticElectricLoad();
  }

  double BoilerHotWater::onCycleParasiticElectricLoad() const {
    return getImpl<detail::BoilerHotWater_Impl>()->onCycleParasiticElectricLoad();
  }

  bool BoilerHotWater::setOnCycleParasiticElectricLoad(double onCycleParasiticElectricLoad) {
    return getImpl<detail::BoilerHotWater_Impl>()->setOnCycleParasiticElectricLoad(onCycleParasiticElectricLoad);
  }

  double BoilerHotWater::sizingFactor() const {
    return getImpl<detail::BoilerHotWater_Impl>()->sizingFactor();
  }

  bool BoilerHotWater::isSizingFactorDefaulted() const {
    return getImpl<detail::BoilerHotWater_Impl>()->isSizingFactorDefaulted();
  }

  bool BoilerHotWater::setSizingFactor(double sizingFactor) {
    return getImpl<detail::BoilerHotWater_Impl>()->setSizingFactor(sizingFactor);
  }

  void BoilerHotWater::resetSizingFactor() {
    getImpl<detail::BoilerHotWater_Impl>()->resetSizingFactor();
  }

  std::string BoilerHotWater::endUseSubcategory() const {
    return getImpl<detail::BoilerHotWater_Impl>()->endUseSubcategory();
  }

  bool BoilerHotWater::setEndUseSubcategory(const std::string& endUseSubcategory) {
    return getImpl<detail::BoilerHotWater_Impl>()->setEndUseSubcategory(endUseSubcategory);
  }

  double BoilerHotWater::offCycleParasiticFuelLoad() const {
    return getImpl<detail::BoilerHotWater_Impl>()->offCycleParasiticFuelLoad();
  }

  bool BoilerHotWater::setOffCycleParasiticFuelLoad(double offCycleParasiticFuelLoad) {
    return getImpl<detail::BoilerHotWater_Impl>()->setOffCycleParasiticFuelLoad(offCycleParasiticFuelLoad);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    unsigned BoilerHotWater_Impl::inletPort() const {
      return openstudio::Boiler_HotWaterFields::BoilerWaterInletNodeName;
    }

    unsigned BoilerHotWater_Impl::outletPort() const {
      return openstudio::Boiler_HotWaterFields::BoilerWaterOutletNodeName;
    }

    std::string BoilerHotWater_Impl::fuelType() const {
      const auto value = getString(openstudio::Boiler_HotWaterFields::FuelType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool BoilerHotWater_Impl::setFuelType(const std::string& fuelType) {
      return setString(openstudio::Boiler_HotWaterFields::FuelType, fuelType);
    }

    boost::optional<double> BoilerHotWater_Impl::nominalCapacity() const {
      return getDouble(openstudio::Boiler_HotWaterFields::NominalCapacity, true);
    }

    bool BoilerHotWater_Impl::isNominalCapacityAutosized() const {
      if (auto value = getString(openstudio::Boiler_HotWaterFields::NominalCapacity, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool BoilerHotWater_Impl::setNominalCapacity(double nominalCapacity) {
      return setDouble(openstudio::Boiler_HotWaterFields::NominalCapacity, nominalCapacity);
    }

    void BoilerHotWater_Impl::resetNominalCapacity() {
      OS_ASSERT(setString(openstudio::Boiler_HotWaterFields::NominalCapacity, ""));
    }

    void BoilerHotWater_Impl::autosizeNominalCapacity() {
      OS_ASSERT(setString(openstudio::Boiler_HotWaterFields::NominalCapacity, "autosize"));
    }

    double BoilerHotWater_Impl::nominalThermalEfficiency() const {
      const auto value = getDouble(openstudio::Boiler_HotWaterFields::NominalThermalEfficiency, true);
      OS_ASSERT(value);
      return *value;
    }

    bool BoilerHotWater_Impl::setNominalThermalEfficiency(double nominalThermalEfficiency) {
      return setDouble(openstudio::Boiler_HotWaterFields::NominalThermalEfficiency, nominalThermalEfficiency);
    }

    boost::optional<std::string> BoilerHotWater_Impl::efficiencyCurveTemperatureEvaluationVariable() const {
      return getString(openstudio::Boiler_HotWaterFields::EfficiencyCurveTemperatureEvaluationVariable, true);
    }

    bool BoilerHotWater_Impl::setEfficiencyCurveTemperatureEvaluationVariable(const std::string& efficiencyCurveTemperatureEvaluationVariable) {
      return setString(openstudio::Boiler_HotWaterFields::EfficiencyCurveTemperatureEvaluationVariable, efficiencyCurveTemperatureEvaluationVariable);
    }

    void BoilerHotWater_Impl::resetEfficiencyCurveTemperatureEvaluationVariable() {
      OS_ASSERT(setString(openstudio::Boiler_HotWaterFields::EfficiencyCurveTemperatureEvaluationVariable, ""));
    }

    boost::optional<double> BoilerHotWater_Impl::designWaterFlowRate() const {
      return getDouble(openstudio::Boiler_HotWaterFields::DesignWaterFlowRate, true);
    }

    bool BoilerHotWater_Impl::isDesignWaterFlowRateAutosized() const {
      if (auto value = getString(openstudio::Boiler_HotWaterFields::DesignWaterFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool BoilerHotWater_Impl::setDesignWaterFlowRate(double designWaterFlowRate) {
      return setDouble(openstudio::Boiler_HotWaterFields::DesignWaterFlowRate, designWaterFlowRate);
    }

    void BoilerHotWater_Impl::resetDesignWaterFlowRate() {
      OS_ASSERT(setString(openstudio::Boiler_HotWaterFields::DesignWaterFlowRate, ""));
    }

    void BoilerHotWater_Impl::autosizeDesignWaterFlowRate() {
      OS_ASSERT(setString(openstudio::Boiler_HotWaterFields::DesignWaterFlowRate, "autosize"));
    }

    double BoilerHotWater_Impl::minimumPartLoadRatio() const {
      const auto value = getDouble(openstudio::Boiler_HotWaterFields::MinimumPartLoadRatio, true);
      OS_ASSERT(value);
      return *value;
    }

    bool BoilerHotWater_Impl::isMinimumPartLoadRatioDefaulted() const {
      return isEmpty(openstudio::Boiler_HotWaterFields::MinimumPartLoadRatio);
    }

    bool BoilerHotWater_Impl::setMinimumPartLoadRatio(double minimumPartLoadRatio) {
      return setDouble(openstudio::Boiler_HotWaterFields::MinimumPartLoadRatio, minimumPartLoadRatio);
    }

    void BoilerHotWater_Impl::resetMinimumPartLoadRatio() {
      OS_ASSERT(setString(openstudio::Boiler_HotWaterFields::MinimumPartLoadRatio, ""));
    }

    double BoilerHotWater_Impl::maximumPartLoadRatio() const {
      const auto value = getDouble(openstudio::Boiler_HotWaterFields::MaximumPartLoadRatio, true);
      OS_ASSERT(value);
      return *value;
    }

    bool BoilerHotWater_Impl::isMaximumPartLoadRatioDefaulted() const {
      return isEmpty(openstudio::Boiler_HotWaterFields::MaximumPartLoadRatio);
    }

    bool BoilerHotWater_Impl::setMaximumPartLoadRatio(double maximumPartLoadRatio) {
      return setDouble(openstudio::Boiler_HotWaterFields::MaximumPartLoadRatio, maximumPartLoadRatio);
    }

    void BoilerHotWater_Impl::resetMaximumPartLoadRatio() {
      OS_ASSERT(setString(openstudio::Boiler_HotWaterFields::MaximumPartLoadRatio, ""));
    }

    double BoilerHotWater_Impl::optimumPartLoadRatio() const {
      const auto value = getDouble(openstudio::Boiler_HotWaterFields::OptimumPartLoadRatio, true);
      OS_ASSERT(value);
      return *value;
    }

    bool BoilerHotWater_Impl::isOptimumPartLoadRatioDefaulted() const {
      return isEmpty(openstudio::Boiler_HotWaterFields::OptimumPartLoadRatio);
    }

    bool BoilerHotWater_Impl::setOptimumPartLoadRatio(double optimumPartLoadRatio) {
      return setDouble(openstudio::Boiler_HotWaterFields::OptimumPartLoadRatio, optimumPartLoadRatio);
    }

    void BoilerHotWater_Impl::resetOptimumPartLoadRatio() {
      OS_ASSERT(setString(openstudio::Boiler_HotWaterFields::OptimumPartLoadRatio, ""));
    }

    double BoilerHotWater_Impl::waterOutletUpperTemperatureLimit() const {
      const auto value = getDouble(openstudio::Boiler_HotWaterFields::WaterOutletUpperTemperatureLimit, true);
      OS_ASSERT(value);
      return *value;
    }

    bool BoilerHotWater_Impl::isWaterOutletUpperTemperatureLimitDefaulted() const {
      return isEmpty(openstudio::Boiler_HotWaterFields::WaterOutletUpperTemperatureLimit);
    }

    bool BoilerHotWater_Impl::setWaterOutletUpperTemperatureLimit(double waterOutletUpperTemperatureLimit) {
      const bool result = setDouble(openstudio::Boiler_HotWaterFields::WaterOutletUpperTemperatureLimit, waterOutletUpperTemperatureLimit);
      OS_ASSERT(result);
      return result;
    }

    void BoilerHotWater_Impl::resetWaterOutletUpperTemperatureLimit() {
      OS_ASSERT(setString(openstudio::Boiler_HotWaterFields::WaterOutletUpperTemperatureLimit, ""));
    }

    std::string BoilerHotWater_Impl::boilerFlowMode() const {
      const auto value = getString(openstudio::Boiler_HotWaterFields::BoilerFlowMode, true);
      OS_ASSERT(value);
      return *value;
    }

    bool BoilerHotWater_Impl::isBoilerFlowModeDefaulted() const {
      return isEmpty(openstudio::Boiler_HotWaterFields::BoilerFlowMode);
    }

    bool BoilerHotWater_Impl::setBoilerFlowMode(const std::string& boilerFlowMode) {
      if (openstudio::istringEqual(boilerFlowMode, "VariableFlow")) {
        return setString(openstudio::Boiler_HotWaterFields::BoilerFlowMode, "LeavingSetpointModulated");
      }
      return setString(openstudio::Boiler_HotWaterFields::BoilerFlowMode, boilerFlowMode);
    }

    void BoilerHotWater_Impl::resetBoilerFlowMode() {
      OS_ASSERT(setString(openstudio::Boiler_HotWaterFields::BoilerFlowMode, ""));
    }

    boost::optional<double> BoilerHotWater_Impl::parasiticElectricLoad() const {
      return onCycleParasiticElectricLoad();
    }

    bool BoilerHotWater_Impl::setParasiticElectricLoad(double parasiticElectricLoad) {
      return setOnCycleParasiticElectricLoad(parasiticElectricLoad);
    }

    void BoilerHotWater_Impl::resetParasiticElectricLoad() {
      // Retained for API compatibility: this field is required in current schema.
    }

    double BoilerHotWater_Impl::onCycleParasiticElectricLoad() const {
      const auto value = getDouble(openstudio::Boiler_HotWaterFields::OnCycleParasiticElectricLoad, true);
      OS_ASSERT(value);
      return *value;
    }

    bool BoilerHotWater_Impl::setOnCycleParasiticElectricLoad(double onCycleParasiticElectricLoad) {
      return setDouble(openstudio::Boiler_HotWaterFields::OnCycleParasiticElectricLoad, onCycleParasiticElectricLoad);
    }

    double BoilerHotWater_Impl::sizingFactor() const {
      const auto value = getDouble(openstudio::Boiler_HotWaterFields::SizingFactor, true);
      OS_ASSERT(value);
      return *value;
    }

    bool BoilerHotWater_Impl::isSizingFactorDefaulted() const {
      return isEmpty(openstudio::Boiler_HotWaterFields::SizingFactor);
    }

    bool BoilerHotWater_Impl::setSizingFactor(double sizingFactor) {
      return setDouble(openstudio::Boiler_HotWaterFields::SizingFactor, sizingFactor);
    }

    void BoilerHotWater_Impl::resetSizingFactor() {
      OS_ASSERT(setString(openstudio::Boiler_HotWaterFields::SizingFactor, ""));
    }

    std::string BoilerHotWater_Impl::endUseSubcategory() const {
      const auto value = getString(openstudio::Boiler_HotWaterFields::EndUseSubcategory, true);
      OS_ASSERT(value);
      return *value;
    }

    bool BoilerHotWater_Impl::setEndUseSubcategory(const std::string& endUseSubcategory) {
      return setString(openstudio::Boiler_HotWaterFields::EndUseSubcategory, endUseSubcategory);
    }

    double BoilerHotWater_Impl::offCycleParasiticFuelLoad() const {
      const auto value = getDouble(openstudio::Boiler_HotWaterFields::OffCycleParasiticFuelLoad, true);
      OS_ASSERT(value);
      return *value;
    }

    bool BoilerHotWater_Impl::setOffCycleParasiticFuelLoad(double offCycleParasiticFuelLoad) {
      return setDouble(openstudio::Boiler_HotWaterFields::OffCycleParasiticFuelLoad, offCycleParasiticFuelLoad);
    }

    bool BoilerHotWater_Impl::addToNode(Node& node) {
      for (auto& plant : model().getConcreteModelObjects<openstudio::epmodel::PlantLoop>()) {
        if (!plant.supplyComponent(node.handle())) {
          continue;
        }
        if (StraightComponent_Impl::addToNode(node)) {
          plant.setFluidType("Water");
          return true;
        }
      }

      return false;
    }

    std::vector<std::string> BoilerHotWater_Impl::fuelTypeValues() const {
      return openstudio::epmodel::BoilerHotWater::fuelTypeValues();
    }

    std::vector<std::string> BoilerHotWater_Impl::efficiencyCurveTemperatureEvaluationVariableValues() const {
      return openstudio::epmodel::BoilerHotWater::efficiencyCurveTemperatureEvaluationVariableValues();
    }

    std::vector<std::string> BoilerHotWater_Impl::boilerFlowModeValues() const {
      return openstudio::epmodel::BoilerHotWater::boilerFlowModeValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
