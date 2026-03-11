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
  double grossTotalCoolingCapacityFraction() const;

  double evaporatorAirFlowRateFraction() const;

  double condenserAirFlowRateFraction() const;

  boost::optional<double> grossSensibleHeatRatio() const;

  bool isGrossSensibleHeatRatioAutosized() const;

  double grossCoolingCOP() const;

  double activeFractionofCoilFaceArea() const;

  double ratedEvaporatorFanPowerPerVolumeFlowRate() const;

  double ratedEvaporatorFanPowerPerVolumeFlowRate2017() const;

  double ratedEvaporatorFanPowerPerVolumeFlowRate2023() const;

  double evaporativeCondenserPumpPowerFraction() const;

  double evaporativeCondenserEffectiveness() const;

  double ratedWasteHeatFractionofPowerInput() const;

  bool setGrossTotalCoolingCapacityFraction(double grossTotalCoolingCapacityFraction);

  bool setEvaporatorAirFlowRateFraction(double evaporatorAirFlowRateFraction);

  bool setCondenserAirFlowRateFraction(double condenserAirFlowRateFraction);

  bool setGrossSensibleHeatRatio(double grossSensibleHeatRatio);
  void autosizeGrossSensibleHeatRatio();

  bool setGrossCoolingCOP(double grossCoolingCOP);

  bool setActiveFractionofCoilFaceArea(double activeFractionofCoilFaceArea);

  bool setRatedEvaporatorFanPowerPerVolumeFlowRate(double ratedEvaporatorFanPowerPerVolumeFlowRate);

  bool setRatedEvaporatorFanPowerPerVolumeFlowRate2017(double ratedEvaporatorFanPowerPerVolumeFlowRate2017);

  bool setRatedEvaporatorFanPowerPerVolumeFlowRate2023(double ratedEvaporatorFanPowerPerVolumeFlowRate2023);

  bool setEvaporativeCondenserPumpPowerFraction(double evaporativeCondenserPumpPowerFraction);

  bool setEvaporativeCondenserEffectiveness(double evaporativeCondenserEffectiveness);

  bool setRatedWasteHeatFractionofPowerInput(double ratedWasteHeatFractionofPowerInput);

  boost::optional<double> autosizedGrossSensibleHeatRatio() const;

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
