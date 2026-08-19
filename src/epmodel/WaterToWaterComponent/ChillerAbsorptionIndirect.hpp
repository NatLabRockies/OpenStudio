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

  /** \brief Represents an indirect absorption chiller with generator-side performance curves.
   *
   * \par EnergyPlus object
   * \epobject{group-plant-equipment.html#chillerabsorptionindirect,Chiller:Absorption:Indirect}
   *
   * \par Important behavior
   * Attaching a generator plant loop selects <code>HotWater</code> as the
   * generator heat source; removing that loop restores <code>Steam</code>.
   * Selecting <code>Steam</code> while a generator loop is attached is rejected.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::ChillerAbsorptionIndirect</code>. No known public
   * API differences.
   *
   * \par Known limitations
   * No known EPModel-specific limitations.
   */
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
