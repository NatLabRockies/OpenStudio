/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILCOOLINGDXCURVEFITSPEED_IMPL_HPP
#define EPMODEL_COILCOOLINGDXCURVEFITSPEED_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API CoilCoolingDXCurveFitSpeed_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~CoilCoolingDXCurveFitSpeed_Impl() override = default;

  double grossTotalCoolingCapacityFraction() const;

  double evaporatorAirFlowRateFraction() const;

  double condenserAirFlowRateFraction() const;

  boost::optional<double> grossSensibleHeatRatio() const;

  bool isGrossSensibleHeatRatioAutosized() const;

  double grossCoolingCOP() const;

  double activeFractionofCoilFaceArea() const;

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

  bool setRatedEvaporatorFanPowerPerVolumeFlowRate2017(double ratedEvaporatorFanPowerPerVolumeFlowRate2017);

  bool setRatedEvaporatorFanPowerPerVolumeFlowRate2023(double ratedEvaporatorFanPowerPerVolumeFlowRate2023);

  bool setEvaporativeCondenserPumpPowerFraction(double evaporativeCondenserPumpPowerFraction);

  bool setEvaporativeCondenserEffectiveness(double evaporativeCondenserEffectiveness);

  bool setRatedWasteHeatFractionofPowerInput(double ratedWasteHeatFractionofPowerInput);

  boost::optional<double> autosizedGrossSensibleHeatRatio() const;

  void autosize();

  void applySizingValues();
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
