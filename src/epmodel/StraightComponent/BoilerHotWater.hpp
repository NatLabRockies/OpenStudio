/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_BOILERHOTWATER_HPP
#define EPMODEL_BOILERHOTWATER_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class Curve;

  namespace detail {
    class BoilerHotWater_Impl;
  }

  /**
   * \brief Hot-water boiler with fuel, efficiency, flow, sizing, and normalized-efficiency-curve controls.
   *
   * \par EnergyPlus object
   * Encapsulates \epobject{group-plant-equipment.html#boilerhotwater,Boiler:HotWater}.
   *
   * \par Important behavior
   * The normalized boiler-efficiency curve is a typed optional relationship to a configured EnergyPlus univariate
   * or bivariate curve. The legacy `VariableFlow` input is normalized to EnergyPlus's `LeavingSetpointModulated`
   * flow mode.
   *
   * \par OpenStudio Model API
   * Counterpart: `openstudio::model::BoilerHotWater`. Fuel, capacity, efficiency, flow, part-load, sizing, and
   * curve APIs are represented, including autosize/default behavior.
   *
   * \par Known limitations
   * Model result helpers <code>autosizedDesignWaterFlowRate()</code> and <code>autosizedNominalCapacity()</code> are not exposed.
   */
  class EPMODEL_API BoilerHotWater : public StraightComponent
  {
   public:
    explicit BoilerHotWater(const Model& model);

    virtual ~BoilerHotWater() override = default;
    BoilerHotWater(const BoilerHotWater& other) = default;
    BoilerHotWater(BoilerHotWater&& other) = default;
    BoilerHotWater& operator=(const BoilerHotWater&) = default;
    BoilerHotWater& operator=(BoilerHotWater&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> validFuelTypeValues();
    static std::vector<std::string> validEfficiencyCurveTemperatureEvaluationVariableValues();
    static std::vector<std::string> validBoilerFlowModeValues();

    static std::vector<std::string> fuelTypeValues();
    static std::vector<std::string> efficiencyCurveTemperatureEvaluationVariableValues();
    static std::vector<std::string> boilerFlowModeValues();

    std::string fuelType() const;
    bool setFuelType(const std::string& fuelType);

    boost::optional<double> nominalCapacity() const;
    bool isNominalCapacityAutosized() const;
    bool setNominalCapacity(double nominalCapacity);
    void resetNominalCapacity();
    void autosizeNominalCapacity();

    double nominalThermalEfficiency() const;
    bool setNominalThermalEfficiency(double nominalThermalEfficiency);

    boost::optional<std::string> efficiencyCurveTemperatureEvaluationVariable() const;
    bool setEfficiencyCurveTemperatureEvaluationVariable(const std::string& efficiencyCurveTemperatureEvaluationVariable);
    void resetEfficiencyCurveTemperatureEvaluationVariable();

    boost::optional<Curve> normalizedBoilerEfficiencyCurve() const;
    bool setNormalizedBoilerEfficiencyCurve(const Curve& normalizedBoilerEfficiencyCurve);
    void resetNormalizedBoilerEfficiencyCurve();

    boost::optional<double> designWaterFlowRate() const;
    bool isDesignWaterFlowRateAutosized() const;
    bool setDesignWaterFlowRate(double designWaterFlowRate);
    void resetDesignWaterFlowRate();
    void autosizeDesignWaterFlowRate();

    double minimumPartLoadRatio() const;
    bool isMinimumPartLoadRatioDefaulted() const;
    bool setMinimumPartLoadRatio(double minimumPartLoadRatio);
    void resetMinimumPartLoadRatio();

    double maximumPartLoadRatio() const;
    bool isMaximumPartLoadRatioDefaulted() const;
    bool setMaximumPartLoadRatio(double maximumPartLoadRatio);
    void resetMaximumPartLoadRatio();

    double optimumPartLoadRatio() const;
    bool isOptimumPartLoadRatioDefaulted() const;
    bool setOptimumPartLoadRatio(double optimumPartLoadRatio);
    void resetOptimumPartLoadRatio();

    double waterOutletUpperTemperatureLimit() const;
    bool isWaterOutletUpperTemperatureLimitDefaulted() const;
    bool setWaterOutletUpperTemperatureLimit(double waterOutletUpperTemperatureLimit);
    void resetWaterOutletUpperTemperatureLimit();

    std::string boilerFlowMode() const;
    bool isBoilerFlowModeDefaulted() const;
    bool setBoilerFlowMode(const std::string& boilerFlowMode);
    void resetBoilerFlowMode();

    boost::optional<double> parasiticElectricLoad() const;
    bool setParasiticElectricLoad(double parasiticElectricLoad);
    void resetParasiticElectricLoad();

    double onCycleParasiticElectricLoad() const;
    bool setOnCycleParasiticElectricLoad(double onCycleParasiticElectricLoad);

    double sizingFactor() const;
    bool isSizingFactorDefaulted() const;
    bool setSizingFactor(double sizingFactor);
    void resetSizingFactor();

    std::string endUseSubcategory() const;
    bool setEndUseSubcategory(const std::string& endUseSubcategory);

    double offCycleParasiticFuelLoad() const;
    bool setOffCycleParasiticFuelLoad(double offCycleParasiticFuelLoad);

   protected:
    using ImplType = detail::BoilerHotWater_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit BoilerHotWater(std::shared_ptr<detail::BoilerHotWater_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
