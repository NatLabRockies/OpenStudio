/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILCOOLINGDXCURVEFITSPEED_HPP
#define EPMODEL_COILCOOLINGDXCURVEFITSPEED_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Curve;
  class Model;

  namespace detail {
    class CoilCoolingDXCurveFitSpeed_Impl;
  }

  class EPMODEL_API CoilCoolingDXCurveFitSpeed : public ModelObject
  {
   public:
    explicit CoilCoolingDXCurveFitSpeed(const Model& model);

    virtual ~CoilCoolingDXCurveFitSpeed() override = default;
    CoilCoolingDXCurveFitSpeed(const CoilCoolingDXCurveFitSpeed& other) = default;
    CoilCoolingDXCurveFitSpeed(CoilCoolingDXCurveFitSpeed&& other) = default;
    CoilCoolingDXCurveFitSpeed& operator=(const CoilCoolingDXCurveFitSpeed&) = default;
    CoilCoolingDXCurveFitSpeed& operator=(CoilCoolingDXCurveFitSpeed&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - Status: Partial Parity.
    // - Canonical Counterpart: openstudio::model::CoilCoolingDXCurveFitSpeed.
    // - Implemented Parity: Canonical constructor defaults, scalar fields, and all eight optional curve relationships expose the canonical
    //   getter, setter, and reset signatures.
    // - Field/Storage Mapping: Scalars and curve pointers map directly to `Coil:Cooling:DX:CurveFit:Speed` fields.
    // - Evidence: `src/model/CoilCoolingDXCurveFitSpeed.hpp` and `src/epmodel/test/CoilCoolingDXCurveFitSpeed_GTest.cpp`.
    // - Remaining Parity Work: Add operating-mode reverse navigation, clone/removal equivalence, autosized results, and broader scripting evidence.

    /** @name Field Accessors */
    //@{

    double grossTotalCoolingCapacityFraction() const;
    bool setGrossTotalCoolingCapacityFraction(double grossTotalCoolingCapacityFraction);

    double evaporatorAirFlowRateFraction() const;
    bool setEvaporatorAirFlowRateFraction(double evaporatorAirFlowRateFraction);

    double condenserAirFlowRateFraction() const;
    bool setCondenserAirFlowRateFraction(double condenserAirFlowRateFraction);

    boost::optional<double> grossSensibleHeatRatio() const;
    bool isGrossSensibleHeatRatioAutosized() const;
    bool setGrossSensibleHeatRatio(double grossSensibleHeatRatio);
    void autosizeGrossSensibleHeatRatio();
    boost::optional<double> autosizedGrossSensibleHeatRatio() const;

    double grossCoolingCOP() const;
    bool setGrossCoolingCOP(double grossCoolingCOP);

    double activeFractionofCoilFaceArea() const;
    bool setActiveFractionofCoilFaceArea(double activeFractionofCoilFaceArea);

    double ratedEvaporatorFanPowerPerVolumeFlowRate() const;
    bool setRatedEvaporatorFanPowerPerVolumeFlowRate(double ratedEvaporatorFanPowerPerVolumeFlowRate);

    double ratedEvaporatorFanPowerPerVolumeFlowRate2017() const;
    bool setRatedEvaporatorFanPowerPerVolumeFlowRate2017(double ratedEvaporatorFanPowerPerVolumeFlowRate2017);

    double ratedEvaporatorFanPowerPerVolumeFlowRate2023() const;
    bool setRatedEvaporatorFanPowerPerVolumeFlowRate2023(double ratedEvaporatorFanPowerPerVolumeFlowRate2023);

    double evaporativeCondenserPumpPowerFraction() const;
    bool setEvaporativeCondenserPumpPowerFraction(double evaporativeCondenserPumpPowerFraction);

    double evaporativeCondenserEffectiveness() const;
    bool setEvaporativeCondenserEffectiveness(double evaporativeCondenserEffectiveness);

    boost::optional<Curve> totalCoolingCapacityModifierFunctionofTemperatureCurve() const;
    bool setTotalCoolingCapacityModifierFunctionofTemperatureCurve(const Curve& curve);
    void resetTotalCoolingCapacityModifierFunctionofTemperatureCurve();

    boost::optional<Curve> totalCoolingCapacityModifierFunctionofAirFlowFractionCurve() const;
    bool setTotalCoolingCapacityModifierFunctionofAirFlowFractionCurve(const Curve& curve);
    void resetTotalCoolingCapacityModifierFunctionofAirFlowFractionCurve();

    boost::optional<Curve> energyInputRatioModifierFunctionofTemperatureCurve() const;
    bool setEnergyInputRatioModifierFunctionofTemperatureCurve(const Curve& curve);
    void resetEnergyInputRatioModifierFunctionofTemperatureCurve();

    boost::optional<Curve> energyInputRatioModifierFunctionofAirFlowFractionCurve() const;
    bool setEnergyInputRatioModifierFunctionofAirFlowFractionCurve(const Curve& curve);
    void resetEnergyInputRatioModifierFunctionofAirFlowFractionCurve();

    boost::optional<Curve> partLoadFractionCorrelationCurve() const;
    bool setPartLoadFractionCorrelationCurve(const Curve& curve);
    void resetPartLoadFractionCorrelationCurve();

    boost::optional<Curve> wasteHeatModifierFunctionofTemperatureCurve() const;
    bool setWasteHeatModifierFunctionofTemperatureCurve(const Curve& curve);
    void resetWasteHeatModifierFunctionofTemperatureCurve();

    double ratedWasteHeatFractionofPowerInput() const;
    bool setRatedWasteHeatFractionofPowerInput(double ratedWasteHeatFractionofPowerInput);

    boost::optional<Curve> sensibleHeatRatioModifierFunctionofTemperatureCurve() const;
    bool setSensibleHeatRatioModifierFunctionofTemperatureCurve(const Curve& curve);
    void resetSensibleHeatRatioModifierFunctionofTemperatureCurve();

    boost::optional<Curve> sensibleHeatRatioModifierFunctionofFlowFractionCurve() const;
    bool setSensibleHeatRatioModifierFunctionofFlowFractionCurve(const Curve& curve);
    void resetSensibleHeatRatioModifierFunctionofFlowFractionCurve();

    //@}

    void autosize();

    void applySizingValues();

   protected:
    using ImplType = detail::CoilCoolingDXCurveFitSpeed_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit CoilCoolingDXCurveFitSpeed(std::shared_ptr<detail::CoilCoolingDXCurveFitSpeed_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
