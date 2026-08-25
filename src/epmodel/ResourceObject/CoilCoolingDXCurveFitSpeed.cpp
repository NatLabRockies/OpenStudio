/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ResourceObject/CoilCoolingDXCurveFitSpeed.hpp"
#include "ResourceObject/CoilCoolingDXCurveFitSpeed_Impl.hpp"

#include "Curve/Curve.hpp"
#include "Curve/Curve_Impl.hpp"
#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/Coil_Cooling_DX_CurveFit_Speed_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  CoilCoolingDXCurveFitSpeed::CoilCoolingDXCurveFitSpeed(const Model& model) : ModelObject(CoilCoolingDXCurveFitSpeed::iddObjectType(), model) {
    OS_ASSERT(setGrossTotalCoolingCapacityFraction(1.0));
    OS_ASSERT(setEvaporatorAirFlowRateFraction(1.0));
    OS_ASSERT(setCondenserAirFlowRateFraction(1.0));
    autosizeGrossSensibleHeatRatio();
    OS_ASSERT(setGrossCoolingCOP(3.0));
    OS_ASSERT(setActiveFractionofCoilFaceArea(1.0));
    OS_ASSERT(setRatedEvaporatorFanPowerPerVolumeFlowRate2017(773.3));
    OS_ASSERT(setRatedEvaporatorFanPowerPerVolumeFlowRate2023(934.4));
    OS_ASSERT(setEvaporativeCondenserPumpPowerFraction(1.0));
    OS_ASSERT(setEvaporativeCondenserEffectiveness(0.9));
    OS_ASSERT(setRatedWasteHeatFractionofPowerInput(0.2));
  }

  CoilCoolingDXCurveFitSpeed::CoilCoolingDXCurveFitSpeed(std::shared_ptr<detail::CoilCoolingDXCurveFitSpeed_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType CoilCoolingDXCurveFitSpeed::iddObjectType() {
    return IddObjectType::Coil_Cooling_DX_CurveFit_Speed;
  }

  double CoilCoolingDXCurveFitSpeed::grossTotalCoolingCapacityFraction() const {
    return getImpl<detail::CoilCoolingDXCurveFitSpeed_Impl>()->grossTotalCoolingCapacityFraction();
  }

  bool CoilCoolingDXCurveFitSpeed::setGrossTotalCoolingCapacityFraction(double grossTotalCoolingCapacityFraction) {
    return getImpl<detail::CoilCoolingDXCurveFitSpeed_Impl>()->setGrossTotalCoolingCapacityFraction(grossTotalCoolingCapacityFraction);
  }

  double CoilCoolingDXCurveFitSpeed::evaporatorAirFlowRateFraction() const {
    return getImpl<detail::CoilCoolingDXCurveFitSpeed_Impl>()->evaporatorAirFlowRateFraction();
  }

  bool CoilCoolingDXCurveFitSpeed::setEvaporatorAirFlowRateFraction(double evaporatorAirFlowRateFraction) {
    return getImpl<detail::CoilCoolingDXCurveFitSpeed_Impl>()->setEvaporatorAirFlowRateFraction(evaporatorAirFlowRateFraction);
  }

  double CoilCoolingDXCurveFitSpeed::condenserAirFlowRateFraction() const {
    return getImpl<detail::CoilCoolingDXCurveFitSpeed_Impl>()->condenserAirFlowRateFraction();
  }

  bool CoilCoolingDXCurveFitSpeed::setCondenserAirFlowRateFraction(double condenserAirFlowRateFraction) {
    return getImpl<detail::CoilCoolingDXCurveFitSpeed_Impl>()->setCondenserAirFlowRateFraction(condenserAirFlowRateFraction);
  }

  boost::optional<double> CoilCoolingDXCurveFitSpeed::grossSensibleHeatRatio() const {
    return getImpl<detail::CoilCoolingDXCurveFitSpeed_Impl>()->grossSensibleHeatRatio();
  }

  bool CoilCoolingDXCurveFitSpeed::isGrossSensibleHeatRatioAutosized() const {
    return getImpl<detail::CoilCoolingDXCurveFitSpeed_Impl>()->isGrossSensibleHeatRatioAutosized();
  }

  bool CoilCoolingDXCurveFitSpeed::setGrossSensibleHeatRatio(double grossSensibleHeatRatio) {
    return getImpl<detail::CoilCoolingDXCurveFitSpeed_Impl>()->setGrossSensibleHeatRatio(grossSensibleHeatRatio);
  }

  void CoilCoolingDXCurveFitSpeed::autosizeGrossSensibleHeatRatio() {
    getImpl<detail::CoilCoolingDXCurveFitSpeed_Impl>()->autosizeGrossSensibleHeatRatio();
  }

  double CoilCoolingDXCurveFitSpeed::grossCoolingCOP() const {
    return getImpl<detail::CoilCoolingDXCurveFitSpeed_Impl>()->grossCoolingCOP();
  }

  bool CoilCoolingDXCurveFitSpeed::setGrossCoolingCOP(double grossCoolingCOP) {
    return getImpl<detail::CoilCoolingDXCurveFitSpeed_Impl>()->setGrossCoolingCOP(grossCoolingCOP);
  }

  double CoilCoolingDXCurveFitSpeed::activeFractionofCoilFaceArea() const {
    return getImpl<detail::CoilCoolingDXCurveFitSpeed_Impl>()->activeFractionofCoilFaceArea();
  }

  bool CoilCoolingDXCurveFitSpeed::setActiveFractionofCoilFaceArea(double activeFractionofCoilFaceArea) {
    return getImpl<detail::CoilCoolingDXCurveFitSpeed_Impl>()->setActiveFractionofCoilFaceArea(activeFractionofCoilFaceArea);
  }

  double CoilCoolingDXCurveFitSpeed::ratedEvaporatorFanPowerPerVolumeFlowRate() const {
    return getImpl<detail::CoilCoolingDXCurveFitSpeed_Impl>()->ratedEvaporatorFanPowerPerVolumeFlowRate2017();
  }

  bool CoilCoolingDXCurveFitSpeed::setRatedEvaporatorFanPowerPerVolumeFlowRate(double ratedEvaporatorFanPowerPerVolumeFlowRate) {
    return getImpl<detail::CoilCoolingDXCurveFitSpeed_Impl>()->setRatedEvaporatorFanPowerPerVolumeFlowRate2017(
      ratedEvaporatorFanPowerPerVolumeFlowRate);
  }

  double CoilCoolingDXCurveFitSpeed::ratedEvaporatorFanPowerPerVolumeFlowRate2017() const {
    return getImpl<detail::CoilCoolingDXCurveFitSpeed_Impl>()->ratedEvaporatorFanPowerPerVolumeFlowRate2017();
  }

  bool CoilCoolingDXCurveFitSpeed::setRatedEvaporatorFanPowerPerVolumeFlowRate2017(double ratedEvaporatorFanPowerPerVolumeFlowRate2017) {
    return getImpl<detail::CoilCoolingDXCurveFitSpeed_Impl>()->setRatedEvaporatorFanPowerPerVolumeFlowRate2017(
      ratedEvaporatorFanPowerPerVolumeFlowRate2017);
  }

  double CoilCoolingDXCurveFitSpeed::ratedEvaporatorFanPowerPerVolumeFlowRate2023() const {
    return getImpl<detail::CoilCoolingDXCurveFitSpeed_Impl>()->ratedEvaporatorFanPowerPerVolumeFlowRate2023();
  }

  bool CoilCoolingDXCurveFitSpeed::setRatedEvaporatorFanPowerPerVolumeFlowRate2023(double ratedEvaporatorFanPowerPerVolumeFlowRate2023) {
    return getImpl<detail::CoilCoolingDXCurveFitSpeed_Impl>()->setRatedEvaporatorFanPowerPerVolumeFlowRate2023(
      ratedEvaporatorFanPowerPerVolumeFlowRate2023);
  }

  double CoilCoolingDXCurveFitSpeed::evaporativeCondenserPumpPowerFraction() const {
    return getImpl<detail::CoilCoolingDXCurveFitSpeed_Impl>()->evaporativeCondenserPumpPowerFraction();
  }

  bool CoilCoolingDXCurveFitSpeed::setEvaporativeCondenserPumpPowerFraction(double evaporativeCondenserPumpPowerFraction) {
    return getImpl<detail::CoilCoolingDXCurveFitSpeed_Impl>()->setEvaporativeCondenserPumpPowerFraction(evaporativeCondenserPumpPowerFraction);
  }

  double CoilCoolingDXCurveFitSpeed::evaporativeCondenserEffectiveness() const {
    return getImpl<detail::CoilCoolingDXCurveFitSpeed_Impl>()->evaporativeCondenserEffectiveness();
  }

  bool CoilCoolingDXCurveFitSpeed::setEvaporativeCondenserEffectiveness(double evaporativeCondenserEffectiveness) {
    return getImpl<detail::CoilCoolingDXCurveFitSpeed_Impl>()->setEvaporativeCondenserEffectiveness(evaporativeCondenserEffectiveness);
  }

  boost::optional<Curve> CoilCoolingDXCurveFitSpeed::totalCoolingCapacityModifierFunctionofTemperatureCurve() const {
    return getImpl<detail::CoilCoolingDXCurveFitSpeed_Impl>()->totalCoolingCapacityModifierFunctionofTemperatureCurve();
  }

  bool CoilCoolingDXCurveFitSpeed::setTotalCoolingCapacityModifierFunctionofTemperatureCurve(const Curve& curve) {
    return getImpl<detail::CoilCoolingDXCurveFitSpeed_Impl>()->setTotalCoolingCapacityModifierFunctionofTemperatureCurve(curve);
  }

  void CoilCoolingDXCurveFitSpeed::resetTotalCoolingCapacityModifierFunctionofTemperatureCurve() {
    getImpl<detail::CoilCoolingDXCurveFitSpeed_Impl>()->resetTotalCoolingCapacityModifierFunctionofTemperatureCurve();
  }

  boost::optional<Curve> CoilCoolingDXCurveFitSpeed::totalCoolingCapacityModifierFunctionofAirFlowFractionCurve() const {
    return getImpl<detail::CoilCoolingDXCurveFitSpeed_Impl>()->totalCoolingCapacityModifierFunctionofAirFlowFractionCurve();
  }

  bool CoilCoolingDXCurveFitSpeed::setTotalCoolingCapacityModifierFunctionofAirFlowFractionCurve(const Curve& curve) {
    return getImpl<detail::CoilCoolingDXCurveFitSpeed_Impl>()->setTotalCoolingCapacityModifierFunctionofAirFlowFractionCurve(curve);
  }

  void CoilCoolingDXCurveFitSpeed::resetTotalCoolingCapacityModifierFunctionofAirFlowFractionCurve() {
    getImpl<detail::CoilCoolingDXCurveFitSpeed_Impl>()->resetTotalCoolingCapacityModifierFunctionofAirFlowFractionCurve();
  }

  boost::optional<Curve> CoilCoolingDXCurveFitSpeed::energyInputRatioModifierFunctionofTemperatureCurve() const {
    return getImpl<detail::CoilCoolingDXCurveFitSpeed_Impl>()->energyInputRatioModifierFunctionofTemperatureCurve();
  }

  bool CoilCoolingDXCurveFitSpeed::setEnergyInputRatioModifierFunctionofTemperatureCurve(const Curve& curve) {
    return getImpl<detail::CoilCoolingDXCurveFitSpeed_Impl>()->setEnergyInputRatioModifierFunctionofTemperatureCurve(curve);
  }

  void CoilCoolingDXCurveFitSpeed::resetEnergyInputRatioModifierFunctionofTemperatureCurve() {
    getImpl<detail::CoilCoolingDXCurveFitSpeed_Impl>()->resetEnergyInputRatioModifierFunctionofTemperatureCurve();
  }

  boost::optional<Curve> CoilCoolingDXCurveFitSpeed::energyInputRatioModifierFunctionofAirFlowFractionCurve() const {
    return getImpl<detail::CoilCoolingDXCurveFitSpeed_Impl>()->energyInputRatioModifierFunctionofAirFlowFractionCurve();
  }

  bool CoilCoolingDXCurveFitSpeed::setEnergyInputRatioModifierFunctionofAirFlowFractionCurve(const Curve& curve) {
    return getImpl<detail::CoilCoolingDXCurveFitSpeed_Impl>()->setEnergyInputRatioModifierFunctionofAirFlowFractionCurve(curve);
  }

  void CoilCoolingDXCurveFitSpeed::resetEnergyInputRatioModifierFunctionofAirFlowFractionCurve() {
    getImpl<detail::CoilCoolingDXCurveFitSpeed_Impl>()->resetEnergyInputRatioModifierFunctionofAirFlowFractionCurve();
  }

  boost::optional<Curve> CoilCoolingDXCurveFitSpeed::partLoadFractionCorrelationCurve() const {
    return getImpl<detail::CoilCoolingDXCurveFitSpeed_Impl>()->partLoadFractionCorrelationCurve();
  }

  bool CoilCoolingDXCurveFitSpeed::setPartLoadFractionCorrelationCurve(const Curve& curve) {
    return getImpl<detail::CoilCoolingDXCurveFitSpeed_Impl>()->setPartLoadFractionCorrelationCurve(curve);
  }

  void CoilCoolingDXCurveFitSpeed::resetPartLoadFractionCorrelationCurve() {
    getImpl<detail::CoilCoolingDXCurveFitSpeed_Impl>()->resetPartLoadFractionCorrelationCurve();
  }

  boost::optional<Curve> CoilCoolingDXCurveFitSpeed::wasteHeatModifierFunctionofTemperatureCurve() const {
    return getImpl<detail::CoilCoolingDXCurveFitSpeed_Impl>()->wasteHeatModifierFunctionofTemperatureCurve();
  }

  bool CoilCoolingDXCurveFitSpeed::setWasteHeatModifierFunctionofTemperatureCurve(const Curve& curve) {
    return getImpl<detail::CoilCoolingDXCurveFitSpeed_Impl>()->setWasteHeatModifierFunctionofTemperatureCurve(curve);
  }

  void CoilCoolingDXCurveFitSpeed::resetWasteHeatModifierFunctionofTemperatureCurve() {
    getImpl<detail::CoilCoolingDXCurveFitSpeed_Impl>()->resetWasteHeatModifierFunctionofTemperatureCurve();
  }

  double CoilCoolingDXCurveFitSpeed::ratedWasteHeatFractionofPowerInput() const {
    return getImpl<detail::CoilCoolingDXCurveFitSpeed_Impl>()->ratedWasteHeatFractionofPowerInput();
  }

  bool CoilCoolingDXCurveFitSpeed::setRatedWasteHeatFractionofPowerInput(double ratedWasteHeatFractionofPowerInput) {
    return getImpl<detail::CoilCoolingDXCurveFitSpeed_Impl>()->setRatedWasteHeatFractionofPowerInput(ratedWasteHeatFractionofPowerInput);
  }

  boost::optional<Curve> CoilCoolingDXCurveFitSpeed::sensibleHeatRatioModifierFunctionofTemperatureCurve() const {
    return getImpl<detail::CoilCoolingDXCurveFitSpeed_Impl>()->sensibleHeatRatioModifierFunctionofTemperatureCurve();
  }

  bool CoilCoolingDXCurveFitSpeed::setSensibleHeatRatioModifierFunctionofTemperatureCurve(const Curve& curve) {
    return getImpl<detail::CoilCoolingDXCurveFitSpeed_Impl>()->setSensibleHeatRatioModifierFunctionofTemperatureCurve(curve);
  }

  void CoilCoolingDXCurveFitSpeed::resetSensibleHeatRatioModifierFunctionofTemperatureCurve() {
    getImpl<detail::CoilCoolingDXCurveFitSpeed_Impl>()->resetSensibleHeatRatioModifierFunctionofTemperatureCurve();
  }

  boost::optional<Curve> CoilCoolingDXCurveFitSpeed::sensibleHeatRatioModifierFunctionofFlowFractionCurve() const {
    return getImpl<detail::CoilCoolingDXCurveFitSpeed_Impl>()->sensibleHeatRatioModifierFunctionofFlowFractionCurve();
  }

  bool CoilCoolingDXCurveFitSpeed::setSensibleHeatRatioModifierFunctionofFlowFractionCurve(const Curve& curve) {
    return getImpl<detail::CoilCoolingDXCurveFitSpeed_Impl>()->setSensibleHeatRatioModifierFunctionofFlowFractionCurve(curve);
  }

  void CoilCoolingDXCurveFitSpeed::resetSensibleHeatRatioModifierFunctionofFlowFractionCurve() {
    getImpl<detail::CoilCoolingDXCurveFitSpeed_Impl>()->resetSensibleHeatRatioModifierFunctionofFlowFractionCurve();
  }

  boost::optional<double> CoilCoolingDXCurveFitSpeed::autosizedGrossSensibleHeatRatio() const {
    return getImpl<detail::CoilCoolingDXCurveFitSpeed_Impl>()->autosizedGrossSensibleHeatRatio();
  }

  void CoilCoolingDXCurveFitSpeed::autosize() {
    getImpl<detail::CoilCoolingDXCurveFitSpeed_Impl>()->autosize();
  }

  void CoilCoolingDXCurveFitSpeed::applySizingValues() {
    getImpl<detail::CoilCoolingDXCurveFitSpeed_Impl>()->applySizingValues();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double CoilCoolingDXCurveFitSpeed_Impl::grossTotalCoolingCapacityFraction() const {
      const auto value = getDouble(openstudio::Coil_Cooling_DX_CurveFit_SpeedFields::GrossTotalCoolingCapacityFraction, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingDXCurveFitSpeed_Impl::setGrossTotalCoolingCapacityFraction(double grossTotalCoolingCapacityFraction) {
      return setDouble(openstudio::Coil_Cooling_DX_CurveFit_SpeedFields::GrossTotalCoolingCapacityFraction, grossTotalCoolingCapacityFraction);
    }

    double CoilCoolingDXCurveFitSpeed_Impl::evaporatorAirFlowRateFraction() const {
      const auto value = getDouble(openstudio::Coil_Cooling_DX_CurveFit_SpeedFields::EvaporatorAirFlowRateFraction, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingDXCurveFitSpeed_Impl::setEvaporatorAirFlowRateFraction(double evaporatorAirFlowRateFraction) {
      return setDouble(openstudio::Coil_Cooling_DX_CurveFit_SpeedFields::EvaporatorAirFlowRateFraction, evaporatorAirFlowRateFraction);
    }

    double CoilCoolingDXCurveFitSpeed_Impl::condenserAirFlowRateFraction() const {
      const auto value = getDouble(openstudio::Coil_Cooling_DX_CurveFit_SpeedFields::CondenserAirFlowRateFraction, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingDXCurveFitSpeed_Impl::setCondenserAirFlowRateFraction(double condenserAirFlowRateFraction) {
      return setDouble(openstudio::Coil_Cooling_DX_CurveFit_SpeedFields::CondenserAirFlowRateFraction, condenserAirFlowRateFraction);
    }

    boost::optional<double> CoilCoolingDXCurveFitSpeed_Impl::grossSensibleHeatRatio() const {
      return getDouble(openstudio::Coil_Cooling_DX_CurveFit_SpeedFields::GrossSensibleHeatRatio, true);
    }

    bool CoilCoolingDXCurveFitSpeed_Impl::isGrossSensibleHeatRatioAutosized() const {
      if (auto value = getString(openstudio::Coil_Cooling_DX_CurveFit_SpeedFields::GrossSensibleHeatRatio, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool CoilCoolingDXCurveFitSpeed_Impl::setGrossSensibleHeatRatio(double grossSensibleHeatRatio) {
      return setDouble(openstudio::Coil_Cooling_DX_CurveFit_SpeedFields::GrossSensibleHeatRatio, grossSensibleHeatRatio);
    }

    void CoilCoolingDXCurveFitSpeed_Impl::autosizeGrossSensibleHeatRatio() {
      OS_ASSERT(setString(openstudio::Coil_Cooling_DX_CurveFit_SpeedFields::GrossSensibleHeatRatio, "autosize"));
    }

    double CoilCoolingDXCurveFitSpeed_Impl::grossCoolingCOP() const {
      const auto value = getDouble(openstudio::Coil_Cooling_DX_CurveFit_SpeedFields::GrossCoolingCOP, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingDXCurveFitSpeed_Impl::setGrossCoolingCOP(double grossCoolingCOP) {
      return setDouble(openstudio::Coil_Cooling_DX_CurveFit_SpeedFields::GrossCoolingCOP, grossCoolingCOP);
    }

    double CoilCoolingDXCurveFitSpeed_Impl::activeFractionofCoilFaceArea() const {
      const auto value = getDouble(openstudio::Coil_Cooling_DX_CurveFit_SpeedFields::ActiveFractionofCoilFaceArea, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingDXCurveFitSpeed_Impl::setActiveFractionofCoilFaceArea(double activeFractionofCoilFaceArea) {
      return setDouble(openstudio::Coil_Cooling_DX_CurveFit_SpeedFields::ActiveFractionofCoilFaceArea, activeFractionofCoilFaceArea);
    }

    double CoilCoolingDXCurveFitSpeed_Impl::ratedEvaporatorFanPowerPerVolumeFlowRate2017() const {
      const auto value = getDouble(openstudio::Coil_Cooling_DX_CurveFit_SpeedFields::RatedEvaporatorFanPowerPerVolumeFlowRate2017, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingDXCurveFitSpeed_Impl::setRatedEvaporatorFanPowerPerVolumeFlowRate2017(double ratedEvaporatorFanPowerPerVolumeFlowRate2017) {
      return setDouble(openstudio::Coil_Cooling_DX_CurveFit_SpeedFields::RatedEvaporatorFanPowerPerVolumeFlowRate2017,
                       ratedEvaporatorFanPowerPerVolumeFlowRate2017);
    }

    double CoilCoolingDXCurveFitSpeed_Impl::ratedEvaporatorFanPowerPerVolumeFlowRate2023() const {
      const auto value = getDouble(openstudio::Coil_Cooling_DX_CurveFit_SpeedFields::RatedEvaporatorFanPowerPerVolumeFlowRate2023, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingDXCurveFitSpeed_Impl::setRatedEvaporatorFanPowerPerVolumeFlowRate2023(double ratedEvaporatorFanPowerPerVolumeFlowRate2023) {
      return setDouble(openstudio::Coil_Cooling_DX_CurveFit_SpeedFields::RatedEvaporatorFanPowerPerVolumeFlowRate2023,
                       ratedEvaporatorFanPowerPerVolumeFlowRate2023);
    }

    double CoilCoolingDXCurveFitSpeed_Impl::evaporativeCondenserPumpPowerFraction() const {
      const auto value = getDouble(openstudio::Coil_Cooling_DX_CurveFit_SpeedFields::EvaporativeCondenserPumpPowerFraction, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingDXCurveFitSpeed_Impl::setEvaporativeCondenserPumpPowerFraction(double evaporativeCondenserPumpPowerFraction) {
      return setDouble(openstudio::Coil_Cooling_DX_CurveFit_SpeedFields::EvaporativeCondenserPumpPowerFraction,
                       evaporativeCondenserPumpPowerFraction);
    }

    double CoilCoolingDXCurveFitSpeed_Impl::evaporativeCondenserEffectiveness() const {
      const auto value = getDouble(openstudio::Coil_Cooling_DX_CurveFit_SpeedFields::EvaporativeCondenserEffectiveness, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingDXCurveFitSpeed_Impl::setEvaporativeCondenserEffectiveness(double evaporativeCondenserEffectiveness) {
      return setDouble(openstudio::Coil_Cooling_DX_CurveFit_SpeedFields::EvaporativeCondenserEffectiveness, evaporativeCondenserEffectiveness);
    }

    boost::optional<Curve> CoilCoolingDXCurveFitSpeed_Impl::totalCoolingCapacityModifierFunctionofTemperatureCurve() const {
      return getObject<ModelObject>().getModelObjectTarget<Curve>(
        openstudio::Coil_Cooling_DX_CurveFit_SpeedFields::TotalCoolingCapacityModifierFunctionofTemperatureCurveName);
    }

    bool CoilCoolingDXCurveFitSpeed_Impl::setTotalCoolingCapacityModifierFunctionofTemperatureCurve(const Curve& curve) {
      return curve.model() == model()
             && setPointer(openstudio::Coil_Cooling_DX_CurveFit_SpeedFields::TotalCoolingCapacityModifierFunctionofTemperatureCurveName,
                           curve.handle(), false);
    }

    void CoilCoolingDXCurveFitSpeed_Impl::resetTotalCoolingCapacityModifierFunctionofTemperatureCurve() {
      OS_ASSERT(
        setPointer(openstudio::Coil_Cooling_DX_CurveFit_SpeedFields::TotalCoolingCapacityModifierFunctionofTemperatureCurveName, Handle(), false));
    }

    boost::optional<Curve> CoilCoolingDXCurveFitSpeed_Impl::totalCoolingCapacityModifierFunctionofAirFlowFractionCurve() const {
      return getObject<ModelObject>().getModelObjectTarget<Curve>(
        openstudio::Coil_Cooling_DX_CurveFit_SpeedFields::TotalCoolingCapacityModifierFunctionofAirFlowFractionCurveName);
    }

    bool CoilCoolingDXCurveFitSpeed_Impl::setTotalCoolingCapacityModifierFunctionofAirFlowFractionCurve(const Curve& curve) {
      return curve.model() == model()
             && setPointer(openstudio::Coil_Cooling_DX_CurveFit_SpeedFields::TotalCoolingCapacityModifierFunctionofAirFlowFractionCurveName,
                           curve.handle(), false);
    }

    void CoilCoolingDXCurveFitSpeed_Impl::resetTotalCoolingCapacityModifierFunctionofAirFlowFractionCurve() {
      OS_ASSERT(setPointer(openstudio::Coil_Cooling_DX_CurveFit_SpeedFields::TotalCoolingCapacityModifierFunctionofAirFlowFractionCurveName, Handle(),
                           false));
    }

    boost::optional<Curve> CoilCoolingDXCurveFitSpeed_Impl::energyInputRatioModifierFunctionofTemperatureCurve() const {
      return getObject<ModelObject>().getModelObjectTarget<Curve>(
        openstudio::Coil_Cooling_DX_CurveFit_SpeedFields::EnergyInputRatioModifierFunctionofTemperatureCurveName);
    }

    bool CoilCoolingDXCurveFitSpeed_Impl::setEnergyInputRatioModifierFunctionofTemperatureCurve(const Curve& curve) {
      return curve.model() == model()
             && setPointer(openstudio::Coil_Cooling_DX_CurveFit_SpeedFields::EnergyInputRatioModifierFunctionofTemperatureCurveName, curve.handle(),
                           false);
    }

    void CoilCoolingDXCurveFitSpeed_Impl::resetEnergyInputRatioModifierFunctionofTemperatureCurve() {
      OS_ASSERT(
        setPointer(openstudio::Coil_Cooling_DX_CurveFit_SpeedFields::EnergyInputRatioModifierFunctionofTemperatureCurveName, Handle(), false));
    }

    boost::optional<Curve> CoilCoolingDXCurveFitSpeed_Impl::energyInputRatioModifierFunctionofAirFlowFractionCurve() const {
      return getObject<ModelObject>().getModelObjectTarget<Curve>(
        openstudio::Coil_Cooling_DX_CurveFit_SpeedFields::EnergyInputRatioModifierFunctionofAirFlowFractionCurveName);
    }

    bool CoilCoolingDXCurveFitSpeed_Impl::setEnergyInputRatioModifierFunctionofAirFlowFractionCurve(const Curve& curve) {
      return curve.model() == model()
             && setPointer(openstudio::Coil_Cooling_DX_CurveFit_SpeedFields::EnergyInputRatioModifierFunctionofAirFlowFractionCurveName,
                           curve.handle(), false);
    }

    void CoilCoolingDXCurveFitSpeed_Impl::resetEnergyInputRatioModifierFunctionofAirFlowFractionCurve() {
      OS_ASSERT(
        setPointer(openstudio::Coil_Cooling_DX_CurveFit_SpeedFields::EnergyInputRatioModifierFunctionofAirFlowFractionCurveName, Handle(), false));
    }

    boost::optional<Curve> CoilCoolingDXCurveFitSpeed_Impl::partLoadFractionCorrelationCurve() const {
      return getObject<ModelObject>().getModelObjectTarget<Curve>(
        openstudio::Coil_Cooling_DX_CurveFit_SpeedFields::PartLoadFractionCorrelationCurveName);
    }

    bool CoilCoolingDXCurveFitSpeed_Impl::setPartLoadFractionCorrelationCurve(const Curve& curve) {
      return curve.model() == model()
             && setPointer(openstudio::Coil_Cooling_DX_CurveFit_SpeedFields::PartLoadFractionCorrelationCurveName, curve.handle(), false);
    }

    void CoilCoolingDXCurveFitSpeed_Impl::resetPartLoadFractionCorrelationCurve() {
      OS_ASSERT(setPointer(openstudio::Coil_Cooling_DX_CurveFit_SpeedFields::PartLoadFractionCorrelationCurveName, Handle(), false));
    }

    boost::optional<Curve> CoilCoolingDXCurveFitSpeed_Impl::wasteHeatModifierFunctionofTemperatureCurve() const {
      return getObject<ModelObject>().getModelObjectTarget<Curve>(
        openstudio::Coil_Cooling_DX_CurveFit_SpeedFields::WasteHeatModifierFunctionofTemperatureCurveName);
    }

    bool CoilCoolingDXCurveFitSpeed_Impl::setWasteHeatModifierFunctionofTemperatureCurve(const Curve& curve) {
      return curve.model() == model()
             && setPointer(openstudio::Coil_Cooling_DX_CurveFit_SpeedFields::WasteHeatModifierFunctionofTemperatureCurveName, curve.handle(), false);
    }

    void CoilCoolingDXCurveFitSpeed_Impl::resetWasteHeatModifierFunctionofTemperatureCurve() {
      OS_ASSERT(setPointer(openstudio::Coil_Cooling_DX_CurveFit_SpeedFields::WasteHeatModifierFunctionofTemperatureCurveName, Handle(), false));
    }

    double CoilCoolingDXCurveFitSpeed_Impl::ratedWasteHeatFractionofPowerInput() const {
      const auto value = getDouble(openstudio::Coil_Cooling_DX_CurveFit_SpeedFields::RatedWasteHeatFractionofPowerInput, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingDXCurveFitSpeed_Impl::setRatedWasteHeatFractionofPowerInput(double ratedWasteHeatFractionofPowerInput) {
      return setDouble(openstudio::Coil_Cooling_DX_CurveFit_SpeedFields::RatedWasteHeatFractionofPowerInput, ratedWasteHeatFractionofPowerInput);
    }

    boost::optional<Curve> CoilCoolingDXCurveFitSpeed_Impl::sensibleHeatRatioModifierFunctionofTemperatureCurve() const {
      return getObject<ModelObject>().getModelObjectTarget<Curve>(
        openstudio::Coil_Cooling_DX_CurveFit_SpeedFields::SensibleHeatRatioModifierFunctionofTemperatureCurveName);
    }

    bool CoilCoolingDXCurveFitSpeed_Impl::setSensibleHeatRatioModifierFunctionofTemperatureCurve(const Curve& curve) {
      return curve.model() == model()
             && setPointer(openstudio::Coil_Cooling_DX_CurveFit_SpeedFields::SensibleHeatRatioModifierFunctionofTemperatureCurveName, curve.handle(),
                           false);
    }

    void CoilCoolingDXCurveFitSpeed_Impl::resetSensibleHeatRatioModifierFunctionofTemperatureCurve() {
      OS_ASSERT(
        setPointer(openstudio::Coil_Cooling_DX_CurveFit_SpeedFields::SensibleHeatRatioModifierFunctionofTemperatureCurveName, Handle(), false));
    }

    boost::optional<Curve> CoilCoolingDXCurveFitSpeed_Impl::sensibleHeatRatioModifierFunctionofFlowFractionCurve() const {
      return getObject<ModelObject>().getModelObjectTarget<Curve>(
        openstudio::Coil_Cooling_DX_CurveFit_SpeedFields::SensibleHeatRatioModifierFunctionofFlowFractionCurveName);
    }

    bool CoilCoolingDXCurveFitSpeed_Impl::setSensibleHeatRatioModifierFunctionofFlowFractionCurve(const Curve& curve) {
      return curve.model() == model()
             && setPointer(openstudio::Coil_Cooling_DX_CurveFit_SpeedFields::SensibleHeatRatioModifierFunctionofFlowFractionCurveName, curve.handle(),
                           false);
    }

    void CoilCoolingDXCurveFitSpeed_Impl::resetSensibleHeatRatioModifierFunctionofFlowFractionCurve() {
      OS_ASSERT(
        setPointer(openstudio::Coil_Cooling_DX_CurveFit_SpeedFields::SensibleHeatRatioModifierFunctionofFlowFractionCurveName, Handle(), false));
    }

    boost::optional<double> CoilCoolingDXCurveFitSpeed_Impl::autosizedGrossSensibleHeatRatio() const {
      // epmodel does not currently resolve autosized values from SQL results.
      return boost::none;
    }

    void CoilCoolingDXCurveFitSpeed_Impl::autosize() {
      autosizeGrossSensibleHeatRatio();
    }

    void CoilCoolingDXCurveFitSpeed_Impl::applySizingValues() {
      if (auto value = autosizedGrossSensibleHeatRatio()) {
        setGrossSensibleHeatRatio(*value);
      }
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
