/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CHILLERHEATERPERFORMANCEELECTRICEIR_IMPL_HPP
#define EPMODEL_CHILLERHEATERPERFORMANCEELECTRICEIR_IMPL_HPP

#include "ParentObject/ParentObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API ChillerHeaterPerformanceElectricEIR_Impl : public ParentObject_Impl
    {
     public:
      using ParentObject_Impl::ParentObject_Impl;
      virtual ~ChillerHeaterPerformanceElectricEIR_Impl() override = default;

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

      std::vector<std::string> chilledWaterFlowModeTypeValues() const;
      std::vector<std::string> condenserTypeValues() const;
      std::vector<std::string> coolingModeTemperatureCurveCondenserWaterIndependentVariableValues() const;
      std::vector<std::string> heatingModeTemperatureCurveCondenserWaterIndependentVariableValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
