/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CHILLERELECTRICREFORMULATEDEIR_HPP
#define EPMODEL_CHILLERELECTRICREFORMULATEDEIR_HPP

#include "EPModelAPI.hpp"
#include "WaterToWaterComponent/WaterToWaterComponent.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class Curve;
  class Schedule;
  class Node;
  class PlantLoop;

  namespace detail {
    class ChillerElectricReformulatedEIR_Impl;
  }

  /** \brief Represents an electric chiller using the reformulated energy-input-ratio model.
   *
   * \par EnergyPlus object
   * \epobject{group-plant-equipment.html#chillerelectricreformulatedeir,Chiller:Electric:ReformulatedEIR}
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::ChillerElectricReformulatedEIR</code>. No known
   * public API differences.
   *
   * \par Known limitations
   * The autosized-value query methods return no value because EPModel does not
   * yet surface the corresponding autosized results for this family.
   */
  class EPMODEL_API ChillerElectricReformulatedEIR : public WaterToWaterComponent
  {
   public:
    explicit ChillerElectricReformulatedEIR(const Model& model, const Curve& CCFofT, const Curve& EItoCORFofT, const Curve& EItoCORFofPLR);
    explicit ChillerElectricReformulatedEIR(const Model& model);

    virtual ~ChillerElectricReformulatedEIR() override = default;
    ChillerElectricReformulatedEIR(const ChillerElectricReformulatedEIR& other) = default;
    ChillerElectricReformulatedEIR(ChillerElectricReformulatedEIR&& other) = default;
    ChillerElectricReformulatedEIR& operator=(const ChillerElectricReformulatedEIR&) = default;
    ChillerElectricReformulatedEIR& operator=(ChillerElectricReformulatedEIR&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> validChillerFlowModeValues();
    static std::vector<std::string> validCondenserFlowControlValues();
    static std::vector<std::string> validElectricInputToCoolingOutputRatioFunctionOfPLRTypeValues();

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
    boost::optional<double> autosizedReferenceCondenserWaterFlowRate() const;
    boost::optional<double> autosizedDesignHeatRecoveryWaterFlowRate() const;

    boost::optional<PlantLoop> chilledWaterLoop() const;
    boost::optional<Node> chilledWaterInletNode() const;
    boost::optional<Node> chilledWaterOutletNode() const;

    boost::optional<PlantLoop> condenserWaterLoop() const;
    boost::optional<Node> condenserInletNode() const;
    boost::optional<Node> condenserOutletNode() const;

    boost::optional<PlantLoop> heatRecoveryLoop() const;
    boost::optional<Node> heatRecoveryInletNode() const;
    boost::optional<Node> heatRecoveryOutletNode() const;

   protected:
    using ImplType = detail::ChillerElectricReformulatedEIR_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ChillerElectricReformulatedEIR(std::shared_ptr<detail::ChillerElectricReformulatedEIR_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
