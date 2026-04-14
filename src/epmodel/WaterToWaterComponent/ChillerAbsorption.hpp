/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CHILLERABSORPTION_HPP
#define EPMODEL_CHILLERABSORPTION_HPP

#include "EPModelAPI.hpp"
#include "WaterToWaterComponent/WaterToWaterComponent.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class PlantLoop;

  namespace detail {
    class ChillerAbsorption_Impl;
  }

  class EPMODEL_API ChillerAbsorption : public WaterToWaterComponent
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
    // - Status: Parity with documented deltas. The canonical scalar surface, loop conveniences, and generator-loop routing behavior are aligned.
    // - Canonical Counterpart: openstudio::model::ChillerAbsorption.
    // - Implemented Parity: Canonical constructor defaults, scalar accessors, chilled/condenser/generator loop conveniences, and generator-loop
    //   routing semantics preserve the model-side API shape.
    // - Documented Delta: Autosized-value helpers are present but still depend on epmodel having populated autosized results, so they may return
    //   `none` in unit-test contexts without sizing output.
    // - Field/Storage Mapping: Scalar wrappers target EnergyPlus `Chiller:Absorption` fields directly, while loop conveniences read the underlying
    //   water-to-water topology links rather than duplicating them as separate persisted data.
    // - Evidence: `src/model/ChillerAbsorption.hpp`, `src/model/ChillerAbsorption.cpp`, and `src/energyplus/ForwardTranslator/ForwardTranslateChillerAbsorption.cpp` establish the canonical scalar contract and field mapping.
    // - Remaining Parity Work: Only shared water-to-water or broader chiller-family abstractions should be added next if multiple wrappers need the same fix.

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

    boost::optional<double> designChilledWaterFlowRate() const;
    bool isDesignChilledWaterFlowRateAutosized() const;
    bool setDesignChilledWaterFlowRate(double designChilledWaterFlowRate);
    void autosizeDesignChilledWaterFlowRate();

    boost::optional<double> designCondenserWaterFlowRate() const;
    bool isDesignCondenserWaterFlowRateAutosized() const;
    bool setDesignCondenserWaterFlowRate(double designCondenserWaterFlowRate);
    void autosizeDesignCondenserWaterFlowRate();

    double coefficient1oftheHotWaterorSteamUsePartLoadRatioCurve() const;
    bool setCoefficient1oftheHotWaterorSteamUsePartLoadRatioCurve(double coefficient1oftheHotWaterorSteamUsePartLoadRatioCurve);

    double coefficient2oftheHotWaterorSteamUsePartLoadRatioCurve() const;
    bool setCoefficient2oftheHotWaterorSteamUsePartLoadRatioCurve(double coefficient2oftheHotWaterorSteamUsePartLoadRatioCurve);

    double coefficient3oftheHotWaterorSteamUsePartLoadRatioCurve() const;
    bool setCoefficient3oftheHotWaterorSteamUsePartLoadRatioCurve(double coefficient3oftheHotWaterorSteamUsePartLoadRatioCurve);

    double coefficient1ofthePumpElectricUsePartLoadRatioCurve() const;
    bool setCoefficient1ofthePumpElectricUsePartLoadRatioCurve(double coefficient1ofthePumpElectricUsePartLoadRatioCurve);

    double coefficient2ofthePumpElectricUsePartLoadRatioCurve() const;
    bool setCoefficient2ofthePumpElectricUsePartLoadRatioCurve(double coefficient2ofthePumpElectricUsePartLoadRatioCurve);

    double coefficient3ofthePumpElectricUsePartLoadRatioCurve() const;
    bool setCoefficient3ofthePumpElectricUsePartLoadRatioCurve(double coefficient3ofthePumpElectricUsePartLoadRatioCurve);

    double chilledWaterOutletTemperatureLowerLimit() const;
    bool setChilledWaterOutletTemperatureLowerLimit(double chilledWaterOutletTemperatureLowerLimit);

    std::string chillerFlowMode() const;
    bool setChillerFlowMode(const std::string& chillerFlowMode);

    std::string generatorHeatSourceType() const;
    bool setGeneratorHeatSourceType(const std::string& generatorHeatSourceType);

    boost::optional<double> designGeneratorFluidFlowRate() const;
    bool isDesignGeneratorFluidFlowRateAutosized() const;
    bool setDesignGeneratorFluidFlowRate(double designGeneratorFluidFlowRate);
    void autosizeDesignGeneratorFluidFlowRate();

    double degreeofSubcoolinginSteamGenerator() const;
    bool setDegreeofSubcoolinginSteamGenerator(double degreeofSubcoolinginSteamGenerator);

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
    using ImplType = detail::ChillerAbsorption_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ChillerAbsorption(std::shared_ptr<detail::ChillerAbsorption_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
