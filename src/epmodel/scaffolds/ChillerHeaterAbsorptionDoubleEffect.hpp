/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CHILLERHEATERABSORPTIONDOUBLEEFFECT_HPP
#define EPMODEL_CHILLERHEATERABSORPTIONDOUBLEEFFECT_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ChillerHeaterAbsorptionDoubleEffect_Impl;
  }

  class EPMODEL_API ChillerHeaterAbsorptionDoubleEffect : public ModelObject
  {
   public:
    explicit ChillerHeaterAbsorptionDoubleEffect(const Model& model);

    virtual ~ChillerHeaterAbsorptionDoubleEffect() override = default;
    ChillerHeaterAbsorptionDoubleEffect(const ChillerHeaterAbsorptionDoubleEffect& other) = default;
    ChillerHeaterAbsorptionDoubleEffect(ChillerHeaterAbsorptionDoubleEffect&& other) = default;
    ChillerHeaterAbsorptionDoubleEffect& operator=(const ChillerHeaterAbsorptionDoubleEffect&) = default;
    ChillerHeaterAbsorptionDoubleEffect& operator=(ChillerHeaterAbsorptionDoubleEffect&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> temperatureCurveInputVariableValues();
    static std::vector<std::string> condenserTypeValues();

    // Schema Alignment Notes:
    // - API: This no-counterpart type uses IDD-derived scalar accessor names.
    // - Field Mapping: Scalar APIs map directly to EnergyPlus ChillerHeater:Absorption:DoubleEffect fields.
    // - Field Mapping: Relationship fields (node/object-list references) are excluded from this scalar-only scaffold.
    // - Field Mapping: ExhaustSourceObjectType and ExhaustSourceObjectName are excluded as target-link relationship fields.
    // - TODO(parity): Add excluded relationship APIs in a dedicated relationship pass.
    boost::optional<double> nominalCoolingCapacity() const;
    bool isNominalCoolingCapacityDefaulted() const;
    bool isNominalCoolingCapacityAutosized() const;
    bool setNominalCoolingCapacity(double nominalCoolingCapacity);
    void resetNominalCoolingCapacity();
    void autosizeNominalCoolingCapacity();

    double heatingtoCoolingCapacityRatio() const;
    bool isHeatingtoCoolingCapacityRatioDefaulted() const;
    bool setHeatingtoCoolingCapacityRatio(double heatingtoCoolingCapacityRatio);
    void resetHeatingtoCoolingCapacityRatio();

    double thermalEnergyInputtoCoolingOutputRatio() const;
    bool isThermalEnergyInputtoCoolingOutputRatioDefaulted() const;
    bool setThermalEnergyInputtoCoolingOutputRatio(double thermalEnergyInputtoCoolingOutputRatio);
    void resetThermalEnergyInputtoCoolingOutputRatio();

    double thermalEnergyInputtoHeatingOutputRatio() const;
    bool isThermalEnergyInputtoHeatingOutputRatioDefaulted() const;
    bool setThermalEnergyInputtoHeatingOutputRatio(double thermalEnergyInputtoHeatingOutputRatio);
    void resetThermalEnergyInputtoHeatingOutputRatio();

    double electricInputtoCoolingOutputRatio() const;
    bool isElectricInputtoCoolingOutputRatioDefaulted() const;
    bool setElectricInputtoCoolingOutputRatio(double electricInputtoCoolingOutputRatio);
    void resetElectricInputtoCoolingOutputRatio();

    double electricInputtoHeatingOutputRatio() const;
    bool isElectricInputtoHeatingOutputRatioDefaulted() const;
    bool setElectricInputtoHeatingOutputRatio(double electricInputtoHeatingOutputRatio);
    void resetElectricInputtoHeatingOutputRatio();

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

    double designEnteringCondenserWaterTemperature() const;
    bool isDesignEnteringCondenserWaterTemperatureDefaulted() const;
    bool setDesignEnteringCondenserWaterTemperature(double designEnteringCondenserWaterTemperature);
    void resetDesignEnteringCondenserWaterTemperature();

    double designLeavingChilledWaterTemperature() const;
    bool isDesignLeavingChilledWaterTemperatureDefaulted() const;
    bool setDesignLeavingChilledWaterTemperature(double designLeavingChilledWaterTemperature);
    void resetDesignLeavingChilledWaterTemperature();

    boost::optional<double> designChilledWaterFlowRate() const;
    bool isDesignChilledWaterFlowRateDefaulted() const;
    bool isDesignChilledWaterFlowRateAutosized() const;
    bool setDesignChilledWaterFlowRate(double designChilledWaterFlowRate);
    void resetDesignChilledWaterFlowRate();
    void autosizeDesignChilledWaterFlowRate();

    boost::optional<double> designCondenserWaterFlowRate() const;
    bool isDesignCondenserWaterFlowRateDefaulted() const;
    bool isDesignCondenserWaterFlowRateAutosized() const;
    bool setDesignCondenserWaterFlowRate(double designCondenserWaterFlowRate);
    void resetDesignCondenserWaterFlowRate();
    void autosizeDesignCondenserWaterFlowRate();

    boost::optional<double> designHotWaterFlowRate() const;
    bool isDesignHotWaterFlowRateDefaulted() const;
    bool isDesignHotWaterFlowRateAutosized() const;
    bool setDesignHotWaterFlowRate(double designHotWaterFlowRate);
    void resetDesignHotWaterFlowRate();
    void autosizeDesignHotWaterFlowRate();

    std::string temperatureCurveInputVariable() const;
    bool isTemperatureCurveInputVariableDefaulted() const;
    bool setTemperatureCurveInputVariable(const std::string& temperatureCurveInputVariable);
    void resetTemperatureCurveInputVariable();

    std::string condenserType() const;
    bool isCondenserTypeDefaulted() const;
    bool setCondenserType(const std::string& condenserType);
    void resetCondenserType();

    double chilledWaterTemperatureLowerLimit() const;
    bool isChilledWaterTemperatureLowerLimitDefaulted() const;
    bool setChilledWaterTemperatureLowerLimit(double chilledWaterTemperatureLowerLimit);
    void resetChilledWaterTemperatureLowerLimit();

    double sizingFactor() const;
    bool isSizingFactorDefaulted() const;
    bool setSizingFactor(double sizingFactor);
    void resetSizingFactor();

   protected:
    using ImplType = detail::ChillerHeaterAbsorptionDoubleEffect_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ChillerHeaterAbsorptionDoubleEffect(std::shared_ptr<detail::ChillerHeaterAbsorptionDoubleEffect_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
