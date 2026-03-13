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

      void autosize();

      void applySizingValues();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
