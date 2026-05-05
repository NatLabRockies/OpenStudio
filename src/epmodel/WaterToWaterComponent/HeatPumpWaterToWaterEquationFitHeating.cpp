/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "WaterToWaterComponent/HeatPumpWaterToWaterEquationFitHeating.hpp"
#include "WaterToWaterComponent/HeatPumpWaterToWaterEquationFitHeating_Impl.hpp"

#include "Curve/CurveQuadLinear.hpp"
#include "Curve/CurveQuadLinear_Impl.hpp"
#include "Model.hpp"
#include "WaterToWaterComponent/HeatPumpWaterToWaterEquationFitCooling.hpp"
#include "WaterToWaterComponent/HeatPumpWaterToWaterEquationFitCooling_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/HeatPump_WaterToWater_EquationFit_Heating_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  HeatPumpWaterToWaterEquationFitHeating::HeatPumpWaterToWaterEquationFitHeating(const Model& model, const CurveQuadLinear& heatingCapacityCurve,
                                                                                 const CurveQuadLinear& heatingCompressorPowerCurve)
    : WaterToWaterComponent(HeatPumpWaterToWaterEquationFitHeating::iddObjectType(), model) {
    autosizeReferenceLoadSideFlowRate();
    autosizeReferenceSourceSideFlowRate();
    autosizeRatedHeatingCapacity();
    autosizeRatedHeatingPowerConsumption();
    OS_ASSERT(setHeatingCapacityCurve(heatingCapacityCurve));
    OS_ASSERT(setHeatingCompressorPowerCurve(heatingCompressorPowerCurve));
    OS_ASSERT(setReferenceCoefficientofPerformance(7.5));
    OS_ASSERT(setSizingFactor(1.0));
  }

  HeatPumpWaterToWaterEquationFitHeating::HeatPumpWaterToWaterEquationFitHeating(const Model& model)
    : WaterToWaterComponent(HeatPumpWaterToWaterEquationFitHeating::iddObjectType(), model) {
    autosizeReferenceLoadSideFlowRate();
    autosizeReferenceSourceSideFlowRate();
    autosizeRatedHeatingCapacity();
    autosizeRatedHeatingPowerConsumption();

    CurveQuadLinear heatingCapacityCurve(model);
    OS_ASSERT(heatingCapacityCurve.setCoefficient1Constant(-3.33491153));
    OS_ASSERT(heatingCapacityCurve.setCoefficient2w(-0.51451946));
    OS_ASSERT(heatingCapacityCurve.setCoefficient3x(4.51592706));
    OS_ASSERT(heatingCapacityCurve.setCoefficient4y(0.01797107));
    OS_ASSERT(heatingCapacityCurve.setCoefficient5z(0.155797661));
    OS_ASSERT(setHeatingCapacityCurve(heatingCapacityCurve));

    CurveQuadLinear heatingCompressorPowerCurve(model);
    OS_ASSERT(heatingCompressorPowerCurve.setCoefficient1Constant(-8.93121751));
    OS_ASSERT(heatingCompressorPowerCurve.setCoefficient2w(8.57035762));
    OS_ASSERT(heatingCompressorPowerCurve.setCoefficient3x(1.29660976));
    OS_ASSERT(heatingCompressorPowerCurve.setCoefficient4y(-0.21629222));
    OS_ASSERT(heatingCompressorPowerCurve.setCoefficient5z(0.033862378));
    OS_ASSERT(setHeatingCompressorPowerCurve(heatingCompressorPowerCurve));

    OS_ASSERT(setReferenceCoefficientofPerformance(7.5));
    OS_ASSERT(setSizingFactor(1.0));
  }

  HeatPumpWaterToWaterEquationFitHeating::HeatPumpWaterToWaterEquationFitHeating(
    std::shared_ptr<detail::HeatPumpWaterToWaterEquationFitHeating_Impl> impl)
    : WaterToWaterComponent(std::move(impl)) {}

  IddObjectType HeatPumpWaterToWaterEquationFitHeating::iddObjectType() {
    return IddObjectType::HeatPump_WaterToWater_EquationFit_Heating;
  }

  boost::optional<double> HeatPumpWaterToWaterEquationFitHeating::referenceLoadSideFlowRate() const {
    return getImpl<detail::HeatPumpWaterToWaterEquationFitHeating_Impl>()->referenceLoadSideFlowRate();
  }

  double HeatPumpWaterToWaterEquationFitHeating::ratedLoadSideFlowRate() const {
    return getImpl<detail::HeatPumpWaterToWaterEquationFitHeating_Impl>()->ratedLoadSideFlowRate();
  }

  bool HeatPumpWaterToWaterEquationFitHeating::isReferenceLoadSideFlowRateAutosized() const {
    return getImpl<detail::HeatPumpWaterToWaterEquationFitHeating_Impl>()->isReferenceLoadSideFlowRateAutosized();
  }

  bool HeatPumpWaterToWaterEquationFitHeating::setReferenceLoadSideFlowRate(double referenceLoadSideFlowRate) {
    return getImpl<detail::HeatPumpWaterToWaterEquationFitHeating_Impl>()->setReferenceLoadSideFlowRate(referenceLoadSideFlowRate);
  }

  bool HeatPumpWaterToWaterEquationFitHeating::setRatedLoadSideFlowRate(double ratedLoadSideFlowRate) {
    return getImpl<detail::HeatPumpWaterToWaterEquationFitHeating_Impl>()->setRatedLoadSideFlowRate(ratedLoadSideFlowRate);
  }

  void HeatPumpWaterToWaterEquationFitHeating::autosizeReferenceLoadSideFlowRate() {
    getImpl<detail::HeatPumpWaterToWaterEquationFitHeating_Impl>()->autosizeReferenceLoadSideFlowRate();
  }

  boost::optional<double> HeatPumpWaterToWaterEquationFitHeating::autosizedReferenceLoadSideFlowRate() const {
    return getImpl<detail::HeatPumpWaterToWaterEquationFitHeating_Impl>()->autosizedReferenceLoadSideFlowRate();
  }

  boost::optional<double> HeatPumpWaterToWaterEquationFitHeating::referenceSourceSideFlowRate() const {
    return getImpl<detail::HeatPumpWaterToWaterEquationFitHeating_Impl>()->referenceSourceSideFlowRate();
  }

  double HeatPumpWaterToWaterEquationFitHeating::ratedSourceSideFlowRate() const {
    return getImpl<detail::HeatPumpWaterToWaterEquationFitHeating_Impl>()->ratedSourceSideFlowRate();
  }

  bool HeatPumpWaterToWaterEquationFitHeating::isReferenceSourceSideFlowRateAutosized() const {
    return getImpl<detail::HeatPumpWaterToWaterEquationFitHeating_Impl>()->isReferenceSourceSideFlowRateAutosized();
  }

  bool HeatPumpWaterToWaterEquationFitHeating::setReferenceSourceSideFlowRate(double referenceSourceSideFlowRate) {
    return getImpl<detail::HeatPumpWaterToWaterEquationFitHeating_Impl>()->setReferenceSourceSideFlowRate(referenceSourceSideFlowRate);
  }

  bool HeatPumpWaterToWaterEquationFitHeating::setRatedSourceSideFlowRate(double ratedSourceSideFlowRate) {
    return getImpl<detail::HeatPumpWaterToWaterEquationFitHeating_Impl>()->setRatedSourceSideFlowRate(ratedSourceSideFlowRate);
  }

  void HeatPumpWaterToWaterEquationFitHeating::autosizeReferenceSourceSideFlowRate() {
    getImpl<detail::HeatPumpWaterToWaterEquationFitHeating_Impl>()->autosizeReferenceSourceSideFlowRate();
  }

  boost::optional<double> HeatPumpWaterToWaterEquationFitHeating::autosizedReferenceSourceSideFlowRate() const {
    return getImpl<detail::HeatPumpWaterToWaterEquationFitHeating_Impl>()->autosizedReferenceSourceSideFlowRate();
  }

  boost::optional<double> HeatPumpWaterToWaterEquationFitHeating::ratedHeatingCapacity() const {
    return getImpl<detail::HeatPumpWaterToWaterEquationFitHeating_Impl>()->ratedHeatingCapacity();
  }

  bool HeatPumpWaterToWaterEquationFitHeating::isRatedHeatingCapacityAutosized() const {
    return getImpl<detail::HeatPumpWaterToWaterEquationFitHeating_Impl>()->isRatedHeatingCapacityAutosized();
  }

  bool HeatPumpWaterToWaterEquationFitHeating::setRatedHeatingCapacity(double ratedHeatingCapacity) {
    return getImpl<detail::HeatPumpWaterToWaterEquationFitHeating_Impl>()->setRatedHeatingCapacity(ratedHeatingCapacity);
  }

  void HeatPumpWaterToWaterEquationFitHeating::autosizeRatedHeatingCapacity() {
    getImpl<detail::HeatPumpWaterToWaterEquationFitHeating_Impl>()->autosizeRatedHeatingCapacity();
  }

  boost::optional<double> HeatPumpWaterToWaterEquationFitHeating::autosizedRatedHeatingCapacity() const {
    return getImpl<detail::HeatPumpWaterToWaterEquationFitHeating_Impl>()->autosizedRatedHeatingCapacity();
  }

  boost::optional<double> HeatPumpWaterToWaterEquationFitHeating::ratedHeatingPowerConsumption() const {
    return getImpl<detail::HeatPumpWaterToWaterEquationFitHeating_Impl>()->ratedHeatingPowerConsumption();
  }

  bool HeatPumpWaterToWaterEquationFitHeating::isRatedHeatingPowerConsumptionAutosized() const {
    return getImpl<detail::HeatPumpWaterToWaterEquationFitHeating_Impl>()->isRatedHeatingPowerConsumptionAutosized();
  }

  bool HeatPumpWaterToWaterEquationFitHeating::setRatedHeatingPowerConsumption(double ratedHeatingPowerConsumption) {
    return getImpl<detail::HeatPumpWaterToWaterEquationFitHeating_Impl>()->setRatedHeatingPowerConsumption(ratedHeatingPowerConsumption);
  }

  void HeatPumpWaterToWaterEquationFitHeating::autosizeRatedHeatingPowerConsumption() {
    getImpl<detail::HeatPumpWaterToWaterEquationFitHeating_Impl>()->autosizeRatedHeatingPowerConsumption();
  }

  boost::optional<double> HeatPumpWaterToWaterEquationFitHeating::autosizedRatedHeatingPowerConsumption() const {
    return getImpl<detail::HeatPumpWaterToWaterEquationFitHeating_Impl>()->autosizedRatedHeatingPowerConsumption();
  }

  CurveQuadLinear HeatPumpWaterToWaterEquationFitHeating::heatingCapacityCurve() const {
    return getImpl<detail::HeatPumpWaterToWaterEquationFitHeating_Impl>()->heatingCapacityCurve();
  }

  bool HeatPumpWaterToWaterEquationFitHeating::setHeatingCapacityCurve(const CurveQuadLinear& heatingCapacityCurve) {
    return getImpl<detail::HeatPumpWaterToWaterEquationFitHeating_Impl>()->setHeatingCapacityCurve(heatingCapacityCurve);
  }

  double HeatPumpWaterToWaterEquationFitHeating::heatingCapacityCoefficient1() const {
    return heatingCapacityCurve().coefficient1Constant();
  }

  bool HeatPumpWaterToWaterEquationFitHeating::setHeatingCapacityCoefficient1(double heatingCapacityCoefficient1) {
    return heatingCapacityCurve().setCoefficient1Constant(heatingCapacityCoefficient1);
  }

  double HeatPumpWaterToWaterEquationFitHeating::heatingCapacityCoefficient2() const {
    return heatingCapacityCurve().coefficient2w();
  }

  bool HeatPumpWaterToWaterEquationFitHeating::setHeatingCapacityCoefficient2(double heatingCapacityCoefficient2) {
    return heatingCapacityCurve().setCoefficient2w(heatingCapacityCoefficient2);
  }

  double HeatPumpWaterToWaterEquationFitHeating::heatingCapacityCoefficient3() const {
    return heatingCapacityCurve().coefficient3x();
  }

  bool HeatPumpWaterToWaterEquationFitHeating::setHeatingCapacityCoefficient3(double heatingCapacityCoefficient3) {
    return heatingCapacityCurve().setCoefficient3x(heatingCapacityCoefficient3);
  }

  double HeatPumpWaterToWaterEquationFitHeating::heatingCapacityCoefficient4() const {
    return heatingCapacityCurve().coefficient4y();
  }

  bool HeatPumpWaterToWaterEquationFitHeating::setHeatingCapacityCoefficient4(double heatingCapacityCoefficient4) {
    return heatingCapacityCurve().setCoefficient4y(heatingCapacityCoefficient4);
  }

  double HeatPumpWaterToWaterEquationFitHeating::heatingCapacityCoefficient5() const {
    return heatingCapacityCurve().coefficient5z();
  }

  bool HeatPumpWaterToWaterEquationFitHeating::setHeatingCapacityCoefficient5(double heatingCapacityCoefficient5) {
    return heatingCapacityCurve().setCoefficient5z(heatingCapacityCoefficient5);
  }

  CurveQuadLinear HeatPumpWaterToWaterEquationFitHeating::heatingCompressorPowerCurve() const {
    return getImpl<detail::HeatPumpWaterToWaterEquationFitHeating_Impl>()->heatingCompressorPowerCurve();
  }

  bool HeatPumpWaterToWaterEquationFitHeating::setHeatingCompressorPowerCurve(const CurveQuadLinear& heatingCompressorPowerCurve) {
    return getImpl<detail::HeatPumpWaterToWaterEquationFitHeating_Impl>()->setHeatingCompressorPowerCurve(heatingCompressorPowerCurve);
  }

  double HeatPumpWaterToWaterEquationFitHeating::heatingCompressorPowerCoefficient1() const {
    return heatingCompressorPowerCurve().coefficient1Constant();
  }

  bool HeatPumpWaterToWaterEquationFitHeating::setHeatingCompressorPowerCoefficient1(double heatingCompressorPowerCoefficient1) {
    return heatingCompressorPowerCurve().setCoefficient1Constant(heatingCompressorPowerCoefficient1);
  }

  double HeatPumpWaterToWaterEquationFitHeating::heatingCompressorPowerCoefficient2() const {
    return heatingCompressorPowerCurve().coefficient2w();
  }

  bool HeatPumpWaterToWaterEquationFitHeating::setHeatingCompressorPowerCoefficient2(double heatingCompressorPowerCoefficient2) {
    return heatingCompressorPowerCurve().setCoefficient2w(heatingCompressorPowerCoefficient2);
  }

  double HeatPumpWaterToWaterEquationFitHeating::heatingCompressorPowerCoefficient3() const {
    return heatingCompressorPowerCurve().coefficient3x();
  }

  bool HeatPumpWaterToWaterEquationFitHeating::setHeatingCompressorPowerCoefficient3(double heatingCompressorPowerCoefficient3) {
    return heatingCompressorPowerCurve().setCoefficient3x(heatingCompressorPowerCoefficient3);
  }

  double HeatPumpWaterToWaterEquationFitHeating::heatingCompressorPowerCoefficient4() const {
    return heatingCompressorPowerCurve().coefficient4y();
  }

  bool HeatPumpWaterToWaterEquationFitHeating::setHeatingCompressorPowerCoefficient4(double heatingCompressorPowerCoefficient4) {
    return heatingCompressorPowerCurve().setCoefficient4y(heatingCompressorPowerCoefficient4);
  }

  double HeatPumpWaterToWaterEquationFitHeating::heatingCompressorPowerCoefficient5() const {
    return heatingCompressorPowerCurve().coefficient5z();
  }

  bool HeatPumpWaterToWaterEquationFitHeating::setHeatingCompressorPowerCoefficient5(double heatingCompressorPowerCoefficient5) {
    return heatingCompressorPowerCurve().setCoefficient5z(heatingCompressorPowerCoefficient5);
  }

  double HeatPumpWaterToWaterEquationFitHeating::referenceCoefficientofPerformance() const {
    return getImpl<detail::HeatPumpWaterToWaterEquationFitHeating_Impl>()->referenceCoefficientofPerformance();
  }

  bool HeatPumpWaterToWaterEquationFitHeating::setReferenceCoefficientofPerformance(double referenceCoefficientofPerformance) {
    return getImpl<detail::HeatPumpWaterToWaterEquationFitHeating_Impl>()->setReferenceCoefficientofPerformance(referenceCoefficientofPerformance);
  }

  double HeatPumpWaterToWaterEquationFitHeating::sizingFactor() const {
    return getImpl<detail::HeatPumpWaterToWaterEquationFitHeating_Impl>()->sizingFactor();
  }

  bool HeatPumpWaterToWaterEquationFitHeating::setSizingFactor(double sizingFactor) {
    return getImpl<detail::HeatPumpWaterToWaterEquationFitHeating_Impl>()->setSizingFactor(sizingFactor);
  }

  boost::optional<HeatPumpWaterToWaterEquationFitCooling> HeatPumpWaterToWaterEquationFitHeating::companionCoolingHeatPump() const {
    return getImpl<detail::HeatPumpWaterToWaterEquationFitHeating_Impl>()->companionCoolingHeatPump();
  }

  bool HeatPumpWaterToWaterEquationFitHeating::setCompanionCoolingHeatPump(const HeatPumpWaterToWaterEquationFitCooling& companionCoolingHeatPump) {
    return getImpl<detail::HeatPumpWaterToWaterEquationFitHeating_Impl>()->setCompanionCoolingHeatPump(companionCoolingHeatPump);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    boost::optional<double> HeatPumpWaterToWaterEquationFitHeating_Impl::referenceLoadSideFlowRate() const {
      return getDouble(openstudio::HeatPump_WaterToWater_EquationFit_HeatingFields::ReferenceLoadSideFlowRate, true);
    }

    double HeatPumpWaterToWaterEquationFitHeating_Impl::ratedLoadSideFlowRate() const {
      if (auto value = referenceLoadSideFlowRate()) {
        return *value;
      }
      return -999.0;
    }

    bool HeatPumpWaterToWaterEquationFitHeating_Impl::isReferenceLoadSideFlowRateAutosized() const {
      if (auto value = getString(openstudio::HeatPump_WaterToWater_EquationFit_HeatingFields::ReferenceLoadSideFlowRate, true)) {
        return openstudio::istringEqual(*value, "Autosize");
      }
      return false;
    }

    boost::optional<double> HeatPumpWaterToWaterEquationFitHeating_Impl::referenceSourceSideFlowRate() const {
      return getDouble(openstudio::HeatPump_WaterToWater_EquationFit_HeatingFields::ReferenceSourceSideFlowRate, true);
    }

    double HeatPumpWaterToWaterEquationFitHeating_Impl::ratedSourceSideFlowRate() const {
      if (auto value = referenceSourceSideFlowRate()) {
        return *value;
      }
      return -999.0;
    }

    bool HeatPumpWaterToWaterEquationFitHeating_Impl::isReferenceSourceSideFlowRateAutosized() const {
      if (auto value = getString(openstudio::HeatPump_WaterToWater_EquationFit_HeatingFields::ReferenceSourceSideFlowRate, true)) {
        return openstudio::istringEqual(*value, "Autosize");
      }
      return false;
    }

    boost::optional<double> HeatPumpWaterToWaterEquationFitHeating_Impl::ratedHeatingCapacity() const {
      return getDouble(openstudio::HeatPump_WaterToWater_EquationFit_HeatingFields::ReferenceHeatingCapacity, true);
    }

    bool HeatPumpWaterToWaterEquationFitHeating_Impl::isRatedHeatingCapacityAutosized() const {
      if (auto value = getString(openstudio::HeatPump_WaterToWater_EquationFit_HeatingFields::ReferenceHeatingCapacity, true)) {
        return openstudio::istringEqual(*value, "Autosize");
      }
      return false;
    }

    boost::optional<double> HeatPumpWaterToWaterEquationFitHeating_Impl::ratedHeatingPowerConsumption() const {
      return getDouble(openstudio::HeatPump_WaterToWater_EquationFit_HeatingFields::ReferenceHeatingPowerConsumption, true);
    }

    bool HeatPumpWaterToWaterEquationFitHeating_Impl::isRatedHeatingPowerConsumptionAutosized() const {
      if (auto value = getString(openstudio::HeatPump_WaterToWater_EquationFit_HeatingFields::ReferenceHeatingPowerConsumption, true)) {
        return openstudio::istringEqual(*value, "Autosize");
      }
      return false;
    }

    double HeatPumpWaterToWaterEquationFitHeating_Impl::referenceCoefficientofPerformance() const {
      const auto value = getDouble(openstudio::HeatPump_WaterToWater_EquationFit_HeatingFields::ReferenceCoefficientofPerformance, true);
      OS_ASSERT(value);
      return *value;
    }

    double HeatPumpWaterToWaterEquationFitHeating_Impl::sizingFactor() const {
      const auto value = getDouble(openstudio::HeatPump_WaterToWater_EquationFit_HeatingFields::SizingFactor, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HeatPumpWaterToWaterEquationFitHeating_Impl::setReferenceLoadSideFlowRate(double referenceLoadSideFlowRate) {
      return setDouble(openstudio::HeatPump_WaterToWater_EquationFit_HeatingFields::ReferenceLoadSideFlowRate, referenceLoadSideFlowRate);
    }

    bool HeatPumpWaterToWaterEquationFitHeating_Impl::setRatedLoadSideFlowRate(double ratedLoadSideFlowRate) {
      return setReferenceLoadSideFlowRate(ratedLoadSideFlowRate);
    }

    void HeatPumpWaterToWaterEquationFitHeating_Impl::autosizeReferenceLoadSideFlowRate() {
      const bool result = setString(openstudio::HeatPump_WaterToWater_EquationFit_HeatingFields::ReferenceLoadSideFlowRate, "Autosize");
      OS_ASSERT(result);
    }

    bool HeatPumpWaterToWaterEquationFitHeating_Impl::setReferenceSourceSideFlowRate(double referenceSourceSideFlowRate) {
      return setDouble(openstudio::HeatPump_WaterToWater_EquationFit_HeatingFields::ReferenceSourceSideFlowRate, referenceSourceSideFlowRate);
    }

    bool HeatPumpWaterToWaterEquationFitHeating_Impl::setRatedSourceSideFlowRate(double ratedSourceSideFlowRate) {
      return setReferenceSourceSideFlowRate(ratedSourceSideFlowRate);
    }

    void HeatPumpWaterToWaterEquationFitHeating_Impl::autosizeReferenceSourceSideFlowRate() {
      const bool result = setString(openstudio::HeatPump_WaterToWater_EquationFit_HeatingFields::ReferenceSourceSideFlowRate, "Autosize");
      OS_ASSERT(result);
    }

    bool HeatPumpWaterToWaterEquationFitHeating_Impl::setRatedHeatingCapacity(double ratedHeatingCapacity) {
      return setDouble(openstudio::HeatPump_WaterToWater_EquationFit_HeatingFields::ReferenceHeatingCapacity, ratedHeatingCapacity);
    }

    void HeatPumpWaterToWaterEquationFitHeating_Impl::autosizeRatedHeatingCapacity() {
      const bool result = setString(openstudio::HeatPump_WaterToWater_EquationFit_HeatingFields::ReferenceHeatingCapacity, "Autosize");
      OS_ASSERT(result);
    }

    bool HeatPumpWaterToWaterEquationFitHeating_Impl::setRatedHeatingPowerConsumption(double ratedHeatingPowerConsumption) {
      return setDouble(openstudio::HeatPump_WaterToWater_EquationFit_HeatingFields::ReferenceHeatingPowerConsumption, ratedHeatingPowerConsumption);
    }

    void HeatPumpWaterToWaterEquationFitHeating_Impl::autosizeRatedHeatingPowerConsumption() {
      const bool result = setString(openstudio::HeatPump_WaterToWater_EquationFit_HeatingFields::ReferenceHeatingPowerConsumption, "Autosize");
      OS_ASSERT(result);
    }

    CurveQuadLinear HeatPumpWaterToWaterEquationFitHeating_Impl::heatingCapacityCurve() const {
      auto target = getTarget(openstudio::HeatPump_WaterToWater_EquationFit_HeatingFields::HeatingCapacityCurveName);
      OS_ASSERT(target);
      return target->cast<CurveQuadLinear>();
    }

    bool HeatPumpWaterToWaterEquationFitHeating_Impl::setHeatingCapacityCurve(const CurveQuadLinear& heatingCapacityCurve) {
      return setPointer(openstudio::HeatPump_WaterToWater_EquationFit_HeatingFields::HeatingCapacityCurveName, heatingCapacityCurve.handle());
    }

    CurveQuadLinear HeatPumpWaterToWaterEquationFitHeating_Impl::heatingCompressorPowerCurve() const {
      auto target = getTarget(openstudio::HeatPump_WaterToWater_EquationFit_HeatingFields::HeatingCompressorPowerCurveName);
      OS_ASSERT(target);
      return target->cast<CurveQuadLinear>();
    }

    bool HeatPumpWaterToWaterEquationFitHeating_Impl::setHeatingCompressorPowerCurve(const CurveQuadLinear& heatingCompressorPowerCurve) {
      return setPointer(openstudio::HeatPump_WaterToWater_EquationFit_HeatingFields::HeatingCompressorPowerCurveName,
                        heatingCompressorPowerCurve.handle());
    }

    bool HeatPumpWaterToWaterEquationFitHeating_Impl::setReferenceCoefficientofPerformance(double referenceCoefficientofPerformance) {
      const bool result =
        setDouble(openstudio::HeatPump_WaterToWater_EquationFit_HeatingFields::ReferenceCoefficientofPerformance, referenceCoefficientofPerformance);
      OS_ASSERT(result);
      return result;
    }

    bool HeatPumpWaterToWaterEquationFitHeating_Impl::setSizingFactor(double sizingFactor) {
      const bool result = setDouble(openstudio::HeatPump_WaterToWater_EquationFit_HeatingFields::SizingFactor, sizingFactor);
      OS_ASSERT(result);
      return result;
    }

    boost::optional<HeatPumpWaterToWaterEquationFitCooling> HeatPumpWaterToWaterEquationFitHeating_Impl::companionCoolingHeatPump() const {
      return getObject<ModelObject>().getModelObjectTarget<HeatPumpWaterToWaterEquationFitCooling>(
        openstudio::HeatPump_WaterToWater_EquationFit_HeatingFields::CompanionCoolingHeatPumpName);
    }

    bool HeatPumpWaterToWaterEquationFitHeating_Impl::setCompanionCoolingHeatPump(
      const HeatPumpWaterToWaterEquationFitCooling& companionCoolingHeatPump) {
      return setPointer(openstudio::HeatPump_WaterToWater_EquationFit_HeatingFields::CompanionCoolingHeatPumpName, companionCoolingHeatPump.handle());
    }

    boost::optional<double> HeatPumpWaterToWaterEquationFitHeating_Impl::autosizedReferenceLoadSideFlowRate() const {
      // epmodel does not currently resolve autosized values from SQL results.
      return boost::none;
    }

    boost::optional<double> HeatPumpWaterToWaterEquationFitHeating_Impl::autosizedReferenceSourceSideFlowRate() const {
      // epmodel does not currently resolve autosized values from SQL results.
      return boost::none;
    }

    boost::optional<double> HeatPumpWaterToWaterEquationFitHeating_Impl::autosizedRatedHeatingCapacity() const {
      // epmodel does not currently resolve autosized values from SQL results.
      return boost::none;
    }

    boost::optional<double> HeatPumpWaterToWaterEquationFitHeating_Impl::autosizedRatedHeatingPowerConsumption() const {
      // epmodel does not currently resolve autosized values from SQL results.
      return boost::none;
    }

    unsigned HeatPumpWaterToWaterEquationFitHeating_Impl::supplyInletPort() const {
      return openstudio::HeatPump_WaterToWater_EquationFit_HeatingFields::SourceSideInletNodeName;
    }

    unsigned HeatPumpWaterToWaterEquationFitHeating_Impl::supplyOutletPort() const {
      return openstudio::HeatPump_WaterToWater_EquationFit_HeatingFields::SourceSideOutletNodeName;
    }

    unsigned HeatPumpWaterToWaterEquationFitHeating_Impl::demandInletPort() const {
      return openstudio::HeatPump_WaterToWater_EquationFit_HeatingFields::LoadSideInletNodeName;
    }

    unsigned HeatPumpWaterToWaterEquationFitHeating_Impl::demandOutletPort() const {
      return openstudio::HeatPump_WaterToWater_EquationFit_HeatingFields::LoadSideOutletNodeName;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
