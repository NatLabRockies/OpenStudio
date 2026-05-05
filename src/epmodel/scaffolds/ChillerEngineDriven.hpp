/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CHILLERENGINEDRIVEN_HPP
#define EPMODEL_CHILLERENGINEDRIVEN_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ChillerEngineDriven_Impl;
  }

  class EPMODEL_API ChillerEngineDriven : public ModelObject
  {
   public:
    explicit ChillerEngineDriven(const Model& model);

    virtual ~ChillerEngineDriven() override = default;
    ChillerEngineDriven(const ChillerEngineDriven& other) = default;
    ChillerEngineDriven(ChillerEngineDriven&& other) = default;
    ChillerEngineDriven& operator=(const ChillerEngineDriven&) = default;
    ChillerEngineDriven& operator=(ChillerEngineDriven&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> condenserTypeValues();
    static std::vector<std::string> chillerFlowModeValues();
    static std::vector<std::string> fuelTypeValues();

    // Schema Alignment Notes:
    // - API: This no-counterpart type uses IDD-derived scalar accessor names.
    // - Field Mapping: Scalar APIs map directly to EnergyPlus Chiller:EngineDriven fields.
    // - Field Mapping: Relationship fields (node/object-list references) are excluded from this scalar-only scaffold.
    // - TODO(parity): Add excluded relationship APIs in a dedicated relationship pass.
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

    boost::optional<double> designCondenserWaterFlowRate() const;
    bool isDesignCondenserWaterFlowRateAutosized() const;
    bool setDesignCondenserWaterFlowRate(double designCondenserWaterFlowRate);
    void resetDesignCondenserWaterFlowRate();
    void autosizeDesignCondenserWaterFlowRate();

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

    boost::optional<double> coefficient1ofUFactorTimesAreaCurve() const;
    bool setCoefficient1ofUFactorTimesAreaCurve(double coefficient1ofUFactorTimesAreaCurve);
    void resetCoefficient1ofUFactorTimesAreaCurve();

    boost::optional<double> coefficient2ofUFactorTimesAreaCurve() const;
    bool setCoefficient2ofUFactorTimesAreaCurve(double coefficient2ofUFactorTimesAreaCurve);
    void resetCoefficient2ofUFactorTimesAreaCurve();

    boost::optional<double> maximumExhaustFlowperUnitofPowerOutput() const;
    bool setMaximumExhaustFlowperUnitofPowerOutput(double maximumExhaustFlowperUnitofPowerOutput);
    void resetMaximumExhaustFlowperUnitofPowerOutput();

    boost::optional<double> designMinimumExhaustTemperature() const;
    bool setDesignMinimumExhaustTemperature(double designMinimumExhaustTemperature);
    void resetDesignMinimumExhaustTemperature();

    boost::optional<double> fuelHigherHeatingValue() const;
    bool setFuelHigherHeatingValue(double fuelHigherHeatingValue);
    void resetFuelHigherHeatingValue();

    boost::optional<double> designHeatRecoveryWaterFlowRate() const;
    bool isDesignHeatRecoveryWaterFlowRateDefaulted() const;
    bool isDesignHeatRecoveryWaterFlowRateAutosized() const;
    bool setDesignHeatRecoveryWaterFlowRate(double designHeatRecoveryWaterFlowRate);
    void resetDesignHeatRecoveryWaterFlowRate();
    void autosizeDesignHeatRecoveryWaterFlowRate();

    std::string chillerFlowMode() const;
    bool isChillerFlowModeDefaulted() const;
    bool setChillerFlowMode(const std::string& chillerFlowMode);
    void resetChillerFlowMode();

    std::string fuelType() const;
    bool setFuelType(const std::string& fuelType);

    double maximumTemperatureforHeatRecoveryatHeatRecoveryOutletNode() const;
    bool isMaximumTemperatureforHeatRecoveryatHeatRecoveryOutletNodeDefaulted() const;
    bool setMaximumTemperatureforHeatRecoveryatHeatRecoveryOutletNode(double maximumTemperatureforHeatRecoveryatHeatRecoveryOutletNode);
    void resetMaximumTemperatureforHeatRecoveryatHeatRecoveryOutletNode();

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

   protected:
    using ImplType = detail::ChillerEngineDriven_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ChillerEngineDriven(std::shared_ptr<detail::ChillerEngineDriven_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
