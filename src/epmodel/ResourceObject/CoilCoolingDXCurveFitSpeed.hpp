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
    // - API: Preserves openstudio::model scalar accessor names/signatures for this model-counterpart class.
    // - Field Mapping: Preserved scalar APIs map directly to matching E+ Coil:Cooling:DX:CurveFit:Speed fields.
    // - Field Mapping: Relationship object-link fields (all curve references and operating-mode back-links) are intentionally excluded.
    // - ForwardTranslator evidence: ForwardTranslateCoilCoolingDXCurveFitSpeed writes these scalar fields one-to-one.
    // - TODO(parity): Add relationship/object-link APIs in a dedicated non-scalar parity pass.

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

    double ratedWasteHeatFractionofPowerInput() const;
    bool setRatedWasteHeatFractionofPowerInput(double ratedWasteHeatFractionofPowerInput);

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
