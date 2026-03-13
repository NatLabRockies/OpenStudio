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
