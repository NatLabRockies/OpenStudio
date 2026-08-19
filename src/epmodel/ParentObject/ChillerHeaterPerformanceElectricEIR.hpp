/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CHILLERHEATERPERFORMANCEELECTRICEIR_HPP
#define EPMODEL_CHILLERHEATERPERFORMANCEELECTRICEIR_HPP

#include "EPModelAPI.hpp"
#include "ParentObject/ParentObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ChillerHeaterPerformanceElectricEIR_Impl;
  }

/** \brief Stores the performance data for an electric EIR chiller-heater.
 *
 * \par EnergyPlus object
 * \epobject{group-plant-equipment.html#chillerheaterperformancelectriceir,ChillerHeaterPerformance:Electric:EIR}
 *
 * \par Important behavior
 * Reference-mode, flow, temperature, efficiency, curve, and sizing fields are stored directly on the performance object.
 *
 * \par OpenStudio Model API
 * The corresponding OpenStudio Model class is <code>openstudio::model::ChillerHeaterPerformanceElectricEIR</code>.
 * <b>Not yet available:</b> Model's performance-curve setters, autosizing and sizing-result helpers, and reverse navigation to <code>CentralHeatPumpSystem</code> modules and systems are not exposed.
 *
 * \par Known limitations
 * The performance object is a data resource; chiller-heater equipment relationships are managed by the referencing equipment object.
 */
  class EPMODEL_API ChillerHeaterPerformanceElectricEIR : public ParentObject
  {
   public:
    explicit ChillerHeaterPerformanceElectricEIR(const Model& model);

    virtual ~ChillerHeaterPerformanceElectricEIR() override = default;
    ChillerHeaterPerformanceElectricEIR(const ChillerHeaterPerformanceElectricEIR& other) = default;
    ChillerHeaterPerformanceElectricEIR(ChillerHeaterPerformanceElectricEIR&& other) = default;
    ChillerHeaterPerformanceElectricEIR& operator=(const ChillerHeaterPerformanceElectricEIR&) = default;
    ChillerHeaterPerformanceElectricEIR& operator=(ChillerHeaterPerformanceElectricEIR&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> chilledWaterFlowModeTypeValues();
    static std::vector<std::string> condenserTypeValues();
    static std::vector<std::string> coolingModeTemperatureCurveCondenserWaterIndependentVariableValues();
    static std::vector<std::string> heatingModeTemperatureCurveCondenserWaterIndependentVariableValues();

    boost::optional<double> referenceCoolingModeEvaporatorCapacity() const;
    bool isReferenceCoolingModeEvaporatorCapacityAutosized() const;
    bool setReferenceCoolingModeEvaporatorCapacity(double referenceCoolingModeEvaporatorCapacity);
    void autosizeReferenceCoolingModeEvaporatorCapacity();

    double referenceCoolingModeCOP() const;
    bool setReferenceCoolingModeCOP(double referenceCoolingModeCOP);

    double referenceCoolingModeLeavingChilledWaterTemperature() const;
    bool setReferenceCoolingModeLeavingChilledWaterTemperature(double referenceCoolingModeLeavingChilledWaterTemperature);

    double referenceCoolingModeEnteringCondenserFluidTemperature() const;
    bool setReferenceCoolingModeEnteringCondenserFluidTemperature(double referenceCoolingModeEnteringCondenserFluidTemperature);

    double referenceCoolingModeLeavingCondenserWaterTemperature() const;
    bool setReferenceCoolingModeLeavingCondenserWaterTemperature(double referenceCoolingModeLeavingCondenserWaterTemperature);

    double referenceHeatingModeCoolingCapacityRatio() const;
    bool setReferenceHeatingModeCoolingCapacityRatio(double referenceHeatingModeCoolingCapacityRatio);

    double referenceHeatingModeCoolingPowerInputRatio() const;
    bool setReferenceHeatingModeCoolingPowerInputRatio(double referenceHeatingModeCoolingPowerInputRatio);

    double referenceHeatingModeLeavingChilledWaterTemperature() const;
    bool setReferenceHeatingModeLeavingChilledWaterTemperature(double referenceHeatingModeLeavingChilledWaterTemperature);

    double referenceHeatingModeLeavingCondenserWaterTemperature() const;
    bool setReferenceHeatingModeLeavingCondenserWaterTemperature(double referenceHeatingModeLeavingCondenserWaterTemperature);

    double referenceHeatingModeEnteringCondenserFluidTemperature() const;
    bool setReferenceHeatingModeEnteringCondenserFluidTemperature(double referenceHeatingModeEnteringCondenserFluidTemperature);

    double heatingModeEnteringChilledWaterTemperatureLowLimit() const;
    bool setHeatingModeEnteringChilledWaterTemperatureLowLimit(double heatingModeEnteringChilledWaterTemperatureLowLimit);

    std::string chilledWaterFlowModeType() const;
    bool setChilledWaterFlowModeType(const std::string& chilledWaterFlowModeType);

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

    double designHotWaterFlowRate() const;
    bool setDesignHotWaterFlowRate(double designHotWaterFlowRate);

    double compressorMotorEfficiency() const;
    bool setCompressorMotorEfficiency(double compressorMotorEfficiency);

    std::string condenserType() const;
    bool setCondenserType(const std::string& condenserType);

    std::string coolingModeTemperatureCurveCondenserWaterIndependentVariable() const;
    bool setCoolingModeTemperatureCurveCondenserWaterIndependentVariable(
      const std::string& coolingModeTemperatureCurveCondenserWaterIndependentVariable);

    double coolingModeCoolingCapacityOptimumPartLoadRatio() const;
    bool setCoolingModeCoolingCapacityOptimumPartLoadRatio(double coolingModeCoolingCapacityOptimumPartLoadRatio);

    std::string heatingModeTemperatureCurveCondenserWaterIndependentVariable() const;
    bool setHeatingModeTemperatureCurveCondenserWaterIndependentVariable(
      const std::string& heatingModeTemperatureCurveCondenserWaterIndependentVariable);

    double heatingModeCoolingCapacityOptimumPartLoadRatio() const;
    bool setHeatingModeCoolingCapacityOptimumPartLoadRatio(double heatingModeCoolingCapacityOptimumPartLoadRatio);

    double sizingFactor() const;
    bool setSizingFactor(double sizingFactor);

   protected:
    using ImplType = detail::ChillerHeaterPerformanceElectricEIR_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ChillerHeaterPerformanceElectricEIR(std::shared_ptr<detail::ChillerHeaterPerformanceElectricEIR_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
