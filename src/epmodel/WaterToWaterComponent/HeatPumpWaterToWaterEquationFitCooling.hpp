/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HEATPUMPWATERTOWATEREQUATIONFITCOOLING_HPP
#define EPMODEL_HEATPUMPWATERTOWATEREQUATIONFITCOOLING_HPP

#include "EPModelAPI.hpp"
#include "WaterToWaterComponent/WaterToWaterComponent.hpp"

#include <utilities/core/Deprecated.hpp>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;
  class CurveQuadLinear;
  class HeatPumpWaterToWaterEquationFitHeating;

  namespace detail {
    class HeatPumpWaterToWaterEquationFitCooling_Impl;
  }

  /** \brief Represents a cooling water-to-water heat pump using equation-fit performance curves.
   *
   * \par EnergyPlus object
   * \epobject{group-plant-equipment.html#heatpumpwatertowaterequationfitcooling,HeatPump:WaterToWater:EquationFit:Cooling}
   *
   * \par Important behavior
   * The model-only constructor creates and attaches default capacity and
   * compressor-power curves; the curve-taking constructor uses the supplied
   * curve objects.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::HeatPumpWaterToWaterEquationFitCooling</code>. No
   * known public API differences.
   *
   * \par Known limitations
   * The autosized-value query methods return no value because EPModel does not
   * yet surface the corresponding autosized results for this family.
   */
  class EPMODEL_API HeatPumpWaterToWaterEquationFitCooling : public WaterToWaterComponent
  {
   public:
    explicit HeatPumpWaterToWaterEquationFitCooling(const Model& model, const CurveQuadLinear& coolingCapacityCurve,
                                                    const CurveQuadLinear& coolingCompressorPowerCurve);
    explicit HeatPumpWaterToWaterEquationFitCooling(const Model& model);

    virtual ~HeatPumpWaterToWaterEquationFitCooling() override = default;
    HeatPumpWaterToWaterEquationFitCooling(const HeatPumpWaterToWaterEquationFitCooling& other) = default;
    HeatPumpWaterToWaterEquationFitCooling(HeatPumpWaterToWaterEquationFitCooling&& other) = default;
    HeatPumpWaterToWaterEquationFitCooling& operator=(const HeatPumpWaterToWaterEquationFitCooling&) = default;
    HeatPumpWaterToWaterEquationFitCooling& operator=(HeatPumpWaterToWaterEquationFitCooling&&) = default;

    static IddObjectType iddObjectType();


    // Reference load-side flow rate
    boost::optional<double> referenceLoadSideFlowRate() const;
    bool isReferenceLoadSideFlowRateAutosized() const;
    bool setReferenceLoadSideFlowRate(double referenceLoadSideFlowRate);
    void autosizeReferenceLoadSideFlowRate();
    boost::optional<double> autosizedReferenceLoadSideFlowRate() const;

    // Rated load-side flow rate
    double ratedLoadSideFlowRate() const;
    bool setRatedLoadSideFlowRate(double ratedLoadSideFlowRate);

    // Reference source-side flow rate
    boost::optional<double> referenceSourceSideFlowRate() const;
    bool isReferenceSourceSideFlowRateAutosized() const;
    bool setReferenceSourceSideFlowRate(double referenceSourceSideFlowRate);
    void autosizeReferenceSourceSideFlowRate();
    boost::optional<double> autosizedReferenceSourceSideFlowRate() const;

    // Rated source-side flow rate
    double ratedSourceSideFlowRate() const;
    bool setRatedSourceSideFlowRate(double ratedSourceSideFlowRate);

    // Rated cooling capacity
    boost::optional<double> ratedCoolingCapacity() const;
    bool isRatedCoolingCapacityAutosized() const;
    bool setRatedCoolingCapacity(double ratedCoolingCapacity);
    void autosizeRatedCoolingCapacity();
    boost::optional<double> autosizedRatedCoolingCapacity() const;

    // Rated cooling power consumption
    boost::optional<double> ratedCoolingPowerConsumption() const;
    bool isRatedCoolingPowerConsumptionAutosized() const;
    bool setRatedCoolingPowerConsumption(double ratedCoolingPowerConsumption);
    void autosizeRatedCoolingPowerConsumption();
    boost::optional<double> autosizedRatedCoolingPowerConsumption() const;

    CurveQuadLinear coolingCapacityCurve() const;
    bool setCoolingCapacityCurve(const CurveQuadLinear& coolingCapacityCurve);
    OS_DEPRECATED(3, 2, 0) double coolingCapacityCoefficient1() const;
    OS_DEPRECATED(3, 2, 0) bool setCoolingCapacityCoefficient1(double coolingCapacityCoefficient1);
    OS_DEPRECATED(3, 2, 0) double coolingCapacityCoefficient2() const;
    OS_DEPRECATED(3, 2, 0) bool setCoolingCapacityCoefficient2(double coolingCapacityCoefficient2);
    OS_DEPRECATED(3, 2, 0) double coolingCapacityCoefficient3() const;
    OS_DEPRECATED(3, 2, 0) bool setCoolingCapacityCoefficient3(double coolingCapacityCoefficient3);
    OS_DEPRECATED(3, 2, 0) double coolingCapacityCoefficient4() const;
    OS_DEPRECATED(3, 2, 0) bool setCoolingCapacityCoefficient4(double coolingCapacityCoefficient4);
    OS_DEPRECATED(3, 2, 0) double coolingCapacityCoefficient5() const;
    OS_DEPRECATED(3, 2, 0) bool setCoolingCapacityCoefficient5(double coolingCapacityCoefficient5);

    CurveQuadLinear coolingCompressorPowerCurve() const;
    bool setCoolingCompressorPowerCurve(const CurveQuadLinear& coolingCompressorPowerCurve);
    OS_DEPRECATED(3, 2, 0) double coolingCompressorPowerCoefficient1() const;
    OS_DEPRECATED(3, 2, 0) bool setCoolingCompressorPowerCoefficient1(double coolingCompressorPowerCoefficient1);
    OS_DEPRECATED(3, 2, 0) double coolingCompressorPowerCoefficient2() const;
    OS_DEPRECATED(3, 2, 0) bool setCoolingCompressorPowerCoefficient2(double coolingCompressorPowerCoefficient2);
    OS_DEPRECATED(3, 2, 0) double coolingCompressorPowerCoefficient3() const;
    OS_DEPRECATED(3, 2, 0) bool setCoolingCompressorPowerCoefficient3(double coolingCompressorPowerCoefficient3);
    OS_DEPRECATED(3, 2, 0) double coolingCompressorPowerCoefficient4() const;
    OS_DEPRECATED(3, 2, 0) bool setCoolingCompressorPowerCoefficient4(double coolingCompressorPowerCoefficient4);
    OS_DEPRECATED(3, 2, 0) double coolingCompressorPowerCoefficient5() const;
    OS_DEPRECATED(3, 2, 0) bool setCoolingCompressorPowerCoefficient5(double coolingCompressorPowerCoefficient5);

    // Performance tuning
    double referenceCoefficientofPerformance() const;
    bool setReferenceCoefficientofPerformance(double referenceCoefficientofPerformance);

    double sizingFactor() const;
    bool setSizingFactor(double sizingFactor);

    boost::optional<HeatPumpWaterToWaterEquationFitHeating> companionHeatingHeatPump() const;
    bool setCompanionHeatingHeatPump(const HeatPumpWaterToWaterEquationFitHeating& companionHeatingHeatPump);

   protected:
    using ImplType = detail::HeatPumpWaterToWaterEquationFitCooling_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit HeatPumpWaterToWaterEquationFitCooling(std::shared_ptr<detail::HeatPumpWaterToWaterEquationFitCooling_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
