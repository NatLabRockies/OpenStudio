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
