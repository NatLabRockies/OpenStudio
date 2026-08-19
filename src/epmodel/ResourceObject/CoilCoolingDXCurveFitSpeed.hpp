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

  /** \brief Defines one speed row for a curve-fit DX cooling operating mode.
   *
   * \par EnergyPlus object
   * \epobject{group-coil-cooling-dx.html#coilcoolingdxcurvefitspeed,Coil:Cooling:DX:CurveFit:Speed}.
   *
   * \par Important behavior
   * The object is an extensible speed row when attached to an operating mode.
   * Its autosized sensible-heat-ratio query returns no value until EPModel can
   * read EnergyPlus SQL sizing results; <code>applySizingValues()</code> can
   * therefore only apply a value when one is available.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::CoilCoolingDXCurveFitSpeed</code>. The deprecated
   * <code>ratedEvaporatorFanPowerPerVolumeFlowRate()</code> accessor remains
   * available in both APIs. The <code>2017</code> and <code>2023</code>
   * accessors select the EnergyPlus rating-standard editions and are also
   * available in both APIs.
   *
   * \par Known limitations
   * Reverse navigation to containing operating modes is not available.
   */
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
