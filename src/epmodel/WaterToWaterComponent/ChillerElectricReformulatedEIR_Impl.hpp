/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CHILLERELECTRICREFORMULATEDEIR_IMPL_HPP
#define EPMODEL_CHILLERELECTRICREFORMULATEDEIR_IMPL_HPP

#include "WaterToWaterComponent/WaterToWaterComponent_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  class Curve;
  class Schedule;
  class PlantLoop;
  class Node;

  namespace detail {

    class EPMODEL_API ChillerElectricReformulatedEIR_Impl : public WaterToWaterComponent_Impl
    {
     public:
      using WaterToWaterComponent_Impl::WaterToWaterComponent_Impl;
      virtual ~ChillerElectricReformulatedEIR_Impl() override = default;

      bool addToNode(Node& node) override;
      bool addToTertiaryNode(Node& node) override;
      bool removeFromSecondaryPlantLoop() override;

      unsigned supplyInletPort() const override;
      unsigned supplyOutletPort() const override;
      unsigned demandInletPort() const override;
      unsigned demandOutletPort() const override;
      unsigned tertiaryInletPort() const override;
      unsigned tertiaryOutletPort() const override;

      boost::optional<double> referenceCapacity() const;
      bool isReferenceCapacityAutosized() const;
      bool setReferenceCapacity(boost::optional<double> referenceCapacity);
      bool setReferenceCapacity(double referenceCapacity);
      void autosizeReferenceCapacity();

      double referenceCOP() const;
      bool setReferenceCOP(double referenceCOP);

      double referenceLeavingChilledWaterTemperature() const;
      bool isReferenceLeavingChilledWaterTemperatureDefaulted() const;
      bool setReferenceLeavingChilledWaterTemperature(double referenceLeavingChilledWaterTemperature);
      void resetReferenceLeavingChilledWaterTemperature();

      double referenceLeavingCondenserWaterTemperature() const;
      bool isReferenceLeavingCondenserWaterTemperatureDefaulted() const;
      bool setReferenceLeavingCondenserWaterTemperature(double referenceLeavingCondenserWaterTemperature);
      void resetReferenceLeavingCondenserWaterTemperature();

      boost::optional<double> referenceChilledWaterFlowRate() const;
      bool isReferenceChilledWaterFlowRateAutosized() const;
      bool setReferenceChilledWaterFlowRate(boost::optional<double> referenceChilledWaterFlowRate);
      bool setReferenceChilledWaterFlowRate(double referenceChilledWaterFlowRate);
      void resetReferenceChilledWaterFlowRate();
      void autosizeReferenceChilledWaterFlowRate();

      boost::optional<double> referenceCondenserWaterFlowRate() const;
      bool isReferenceCondenserWaterFlowRateAutosized() const;
      bool setReferenceCondenserWaterFlowRate(boost::optional<double> referenceCondenserWaterFlowRate);
      bool setReferenceCondenserWaterFlowRate(double referenceCondenserWaterFlowRate);
      void resetReferenceCondenserWaterFlowRate();
      void autosizeReferenceCondenserWaterFlowRate();
      boost::optional<double> autosizedReferenceCondenserWaterFlowRate() const;

      Curve coolingCapacityFunctionOfTemperature() const;
      bool setCoolingCapacityFunctionOfTemperature(const Curve& curve);

      Curve electricInputToCoolingOutputRatioFunctionOfTemperature() const;
      bool setElectricInputToCoolingOutputRatioFunctionOfTemperature(const Curve& curve);

      std::string electricInputToCoolingOutputRatioFunctionOfPLRType() const;
      bool setElectricInputToCoolingOutputRatioFunctionOfPLRType(const std::string& electricInputToCoolingOutputRatioFunctionOfPLRType);
      void resetElectricInputToCoolingOutputRatioFunctionOfPLRType();

      Curve electricInputToCoolingOutputRatioFunctionOfPLR() const;
      bool setElectricInputToCoolingOutputRatioFunctionOfPLR(const Curve& curve);

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

      double minimumUnloadingRatio() const;
      bool isMinimumUnloadingRatioDefaulted() const;
      bool setMinimumUnloadingRatio(double minimumUnloadingRatio);
      void resetMinimumUnloadingRatio();

      double fractionofCompressorElectricConsumptionRejectedbyCondenser() const;
      bool isFractionofCompressorElectricConsumptionRejectedbyCondenserDefaulted() const;
      bool setFractionofCompressorElectricConsumptionRejectedbyCondenser(double fractionofCompressorElectricConsumptionRejectedbyCondenser);
      void resetFractionofCompressorElectricConsumptionRejectedbyCondenser();

      double leavingChilledWaterLowerTemperatureLimit() const;
      bool isLeavingChilledWaterLowerTemperatureLimitDefaulted() const;
      bool setLeavingChilledWaterLowerTemperatureLimit(double leavingChilledWaterLowerTemperatureLimit);
      void resetLeavingChilledWaterLowerTemperatureLimit();

      std::string chillerFlowMode() const;
      bool isChillerFlowModeDefaulted() const;
      bool setChillerFlowMode(const std::string& chillerFlowMode);
      void resetChillerFlowMode();

      boost::optional<double> designHeatRecoveryWaterFlowRate() const;
      bool isDesignHeatRecoveryWaterFlowRateAutosized() const;
      bool setDesignHeatRecoveryWaterFlowRate(double designHeatRecoveryWaterFlowRate);
      void autosizeDesignHeatRecoveryWaterFlowRate();
      boost::optional<double> autosizedDesignHeatRecoveryWaterFlowRate() const;

      double sizingFactor() const;
      bool isSizingFactorDefaulted() const;
      bool setSizingFactor(double sizingFactor);
      void resetSizingFactor();

      double condenserHeatRecoveryRelativeCapacityFraction() const;
      bool setCondenserHeatRecoveryRelativeCapacityFraction(double condenserHeatRecoveryRelativeCapacityFraction);

      boost::optional<Schedule> heatRecoveryInletHighTemperatureLimitSchedule() const;
      bool setHeatRecoveryInletHighTemperatureLimitSchedule(Schedule& schedule);
      void resetHeatRecoveryInletHighTemperatureLimitSchedule();

      boost::optional<Node> heatRecoveryLeavingTemperatureSetpointNode() const;
      bool setHeatRecoveryLeavingTemperatureSetpointNode(const Node& node);
      void resetHeatRecoveryLeavingTemperatureSetpointNode();

      std::string endUseSubcategory() const;
      bool setEndUseSubcategory(const std::string& endUseSubcategory);

      std::string condenserFlowControl() const;
      bool setCondenserFlowControl(const std::string& condenserFlowControl);

      boost::optional<Curve> condenserLoopFlowRateFractionFunctionofLoopPartLoadRatioCurve() const;
      bool setCondenserLoopFlowRateFractionFunctionofLoopPartLoadRatioCurve(const Curve& curve);
      void resetCondenserLoopFlowRateFractionFunctionofLoopPartLoadRatioCurve();

      boost::optional<Schedule> temperatureDifferenceAcrossCondenserSchedule() const;
      bool setTemperatureDifferenceAcrossCondenserSchedule(Schedule& schedule);
      void resetTemperatureDifferenceAcrossCondenserSchedule();

      double condenserMinimumFlowFraction() const;
      bool setCondenserMinimumFlowFraction(double condenserMinimumFlowFraction);

      boost::optional<Curve> thermosiphonCapacityFractionCurve() const;
      bool setThermosiphonCapacityFractionCurve(const Curve& curve);
      void resetThermosiphonCapacityFractionCurve();

      double thermosiphonMinimumTemperatureDifference() const;
      bool setThermosiphonMinimumTemperatureDifference(double thermosiphonMinimumTemperatureDifference);

      boost::optional<double> autosizedReferenceCapacity() const;
      boost::optional<double> autosizedReferenceChilledWaterFlowRate() const;

      boost::optional<PlantLoop> chilledWaterLoop() const;
      boost::optional<Node> chilledWaterInletNode() const;
      boost::optional<Node> chilledWaterOutletNode() const;

      boost::optional<PlantLoop> condenserWaterLoop() const;
      boost::optional<Node> condenserInletNode() const;
      boost::optional<Node> condenserOutletNode() const;

      boost::optional<PlantLoop> heatRecoveryLoop() const;
      boost::optional<Node> heatRecoveryInletNode() const;
      boost::optional<Node> heatRecoveryOutletNode() const;

      std::vector<std::string> validChillerFlowModeValues() const;
      std::vector<std::string> validCondenserFlowControlValues() const;
      std::vector<std::string> validElectricInputToCoolingOutputRatioFunctionOfPLRTypeValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
