/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HEATPUMPWATERTOWATEREQUATIONFITHEATING_HPP
#define EPMODEL_HEATPUMPWATERTOWATEREQUATIONFITHEATING_HPP

#include "EPModelAPI.hpp"
#include "WaterToWaterComponent/WaterToWaterComponent.hpp"

#include <utilities/core/Deprecated.hpp>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;
  class CurveQuadLinear;
  class HeatPumpWaterToWaterEquationFitCooling;

  namespace detail {
    class HeatPumpWaterToWaterEquationFitHeating_Impl;
  }

  /** \brief Represents a heating water-to-water heat pump using equation-fit performance curves.
   *
   * \par EnergyPlus object
   * \epobject{group-plant-equipment.html#heatpumpwatertowaterequationfitheating,HeatPump:WaterToWater:EquationFit:Heating}
   *
   * \par Important behavior
   * The model-only constructor creates and attaches default capacity and
   * compressor-power curves; the curve-taking constructor uses the supplied
   * curve objects.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::HeatPumpWaterToWaterEquationFitHeating</code>. No
   * known public API differences.
   *
   * \par Known limitations
   * The autosized-value query methods return no value because EPModel does not
   * yet surface the corresponding autosized results for this family.
   */
  class EPMODEL_API HeatPumpWaterToWaterEquationFitHeating : public WaterToWaterComponent
  {
   public:
    explicit HeatPumpWaterToWaterEquationFitHeating(const Model& model, const CurveQuadLinear& heatingCapacityCurve,
                                                    const CurveQuadLinear& heatingCompressorPowerCurve);
    explicit HeatPumpWaterToWaterEquationFitHeating(const Model& model);

    virtual ~HeatPumpWaterToWaterEquationFitHeating() override = default;
    HeatPumpWaterToWaterEquationFitHeating(const HeatPumpWaterToWaterEquationFitHeating& other) = default;
    HeatPumpWaterToWaterEquationFitHeating(HeatPumpWaterToWaterEquationFitHeating&& other) = default;
    HeatPumpWaterToWaterEquationFitHeating& operator=(const HeatPumpWaterToWaterEquationFitHeating&) = default;
    HeatPumpWaterToWaterEquationFitHeating& operator=(HeatPumpWaterToWaterEquationFitHeating&&) = default;

    static IddObjectType iddObjectType();


    // Reference load-side flow rate
    boost::optional<double> referenceLoadSideFlowRate() const;
    bool setReferenceLoadSideFlowRate(double referenceLoadSideFlowRate);
    void autosizeReferenceLoadSideFlowRate();
    bool isReferenceLoadSideFlowRateAutosized() const;
    boost::optional<double> autosizedReferenceLoadSideFlowRate() const;

    double ratedLoadSideFlowRate() const;
    bool setRatedLoadSideFlowRate(double ratedLoadSideFlowRate);

    // Reference source-side flow rate
    boost::optional<double> referenceSourceSideFlowRate() const;
    bool setReferenceSourceSideFlowRate(double referenceSourceSideFlowRate);
    void autosizeReferenceSourceSideFlowRate();
    bool isReferenceSourceSideFlowRateAutosized() const;
    boost::optional<double> autosizedReferenceSourceSideFlowRate() const;

    double ratedSourceSideFlowRate() const;
    bool setRatedSourceSideFlowRate(double ratedSourceSideFlowRate);

    // Rated heating capacity
    boost::optional<double> ratedHeatingCapacity() const;
    bool setRatedHeatingCapacity(double ratedHeatingCapacity);
    void autosizeRatedHeatingCapacity();
    bool isRatedHeatingCapacityAutosized() const;
    boost::optional<double> autosizedRatedHeatingCapacity() const;

    // Rated heating power consumption
    boost::optional<double> ratedHeatingPowerConsumption() const;
    bool setRatedHeatingPowerConsumption(double ratedHeatingPowerConsumption);
    void autosizeRatedHeatingPowerConsumption();
    bool isRatedHeatingPowerConsumptionAutosized() const;
    boost::optional<double> autosizedRatedHeatingPowerConsumption() const;

    CurveQuadLinear heatingCapacityCurve() const;
    bool setHeatingCapacityCurve(const CurveQuadLinear& heatingCapacityCurve);
    OS_DEPRECATED(3, 2, 0) double heatingCapacityCoefficient1() const;
    OS_DEPRECATED(3, 2, 0) bool setHeatingCapacityCoefficient1(double heatingCapacityCoefficient1);
    OS_DEPRECATED(3, 2, 0) double heatingCapacityCoefficient2() const;
    OS_DEPRECATED(3, 2, 0) bool setHeatingCapacityCoefficient2(double heatingCapacityCoefficient2);
    OS_DEPRECATED(3, 2, 0) double heatingCapacityCoefficient3() const;
    OS_DEPRECATED(3, 2, 0) bool setHeatingCapacityCoefficient3(double heatingCapacityCoefficient3);
    OS_DEPRECATED(3, 2, 0) double heatingCapacityCoefficient4() const;
    OS_DEPRECATED(3, 2, 0) bool setHeatingCapacityCoefficient4(double heatingCapacityCoefficient4);
    OS_DEPRECATED(3, 2, 0) double heatingCapacityCoefficient5() const;
    OS_DEPRECATED(3, 2, 0) bool setHeatingCapacityCoefficient5(double heatingCapacityCoefficient5);

    CurveQuadLinear heatingCompressorPowerCurve() const;
    bool setHeatingCompressorPowerCurve(const CurveQuadLinear& heatingCompressorPowerCurve);
    OS_DEPRECATED(3, 2, 0) double heatingCompressorPowerCoefficient1() const;
    OS_DEPRECATED(3, 2, 0) bool setHeatingCompressorPowerCoefficient1(double heatingCompressorPowerCoefficient1);
    OS_DEPRECATED(3, 2, 0) double heatingCompressorPowerCoefficient2() const;
    OS_DEPRECATED(3, 2, 0) bool setHeatingCompressorPowerCoefficient2(double heatingCompressorPowerCoefficient2);
    OS_DEPRECATED(3, 2, 0) double heatingCompressorPowerCoefficient3() const;
    OS_DEPRECATED(3, 2, 0) bool setHeatingCompressorPowerCoefficient3(double heatingCompressorPowerCoefficient3);
    OS_DEPRECATED(3, 2, 0) double heatingCompressorPowerCoefficient4() const;
    OS_DEPRECATED(3, 2, 0) bool setHeatingCompressorPowerCoefficient4(double heatingCompressorPowerCoefficient4);
    OS_DEPRECATED(3, 2, 0) double heatingCompressorPowerCoefficient5() const;
    OS_DEPRECATED(3, 2, 0) bool setHeatingCompressorPowerCoefficient5(double heatingCompressorPowerCoefficient5);

    // Performance metadata
    double referenceCoefficientofPerformance() const;
    bool setReferenceCoefficientofPerformance(double referenceCoefficientofPerformance);

    double sizingFactor() const;
    bool setSizingFactor(double sizingFactor);

    boost::optional<HeatPumpWaterToWaterEquationFitCooling> companionCoolingHeatPump() const;
    bool setCompanionCoolingHeatPump(const HeatPumpWaterToWaterEquationFitCooling& companionCoolingHeatPump);

   protected:
    using ImplType = detail::HeatPumpWaterToWaterEquationFitHeating_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit HeatPumpWaterToWaterEquationFitHeating(std::shared_ptr<detail::HeatPumpWaterToWaterEquationFitHeating_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
