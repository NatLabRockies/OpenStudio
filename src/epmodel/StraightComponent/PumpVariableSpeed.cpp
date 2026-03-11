/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include "StraightComponent/PumpVariableSpeed.hpp"
#include "StraightComponent/PumpVariableSpeed_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/Pump_VariableSpeed_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  PumpVariableSpeed::PumpVariableSpeed(const Model& model) : StraightComponent(PumpVariableSpeed::iddObjectType(), model) {
    auto impl = getImpl<detail::PumpVariableSpeed_Impl>();
    OS_ASSERT(impl);
    detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
    impl->canonicalize(context);
  }

  PumpVariableSpeed::PumpVariableSpeed(std::shared_ptr<detail::PumpVariableSpeed_Impl> impl) : StraightComponent(std::move(impl)) {}

  IddObjectType PumpVariableSpeed::iddObjectType() {
    return IddObjectType::Pump_VariableSpeed;
  }

  std::vector<std::string> PumpVariableSpeed::pumpControlTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Pump_VariableSpeedFields::PumpControlType);
  }

  std::vector<std::string> PumpVariableSpeed::designPowerSizingMethodValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Pump_VariableSpeedFields::DesignPowerSizingMethod);
  }

  std::vector<std::string> PumpVariableSpeed::validPumpControlTypeValues() {
    return pumpControlTypeValues();
  }

  std::vector<std::string> PumpVariableSpeed::vfdControlTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Pump_VariableSpeedFields::VFDControlType);
  }

  boost::optional<double> PumpVariableSpeed::ratedFlowRate() const {
    return getImpl<detail::PumpVariableSpeed_Impl>()->ratedFlowRate();
  }

  bool PumpVariableSpeed::isRatedFlowRateDefaulted() const {
    return getImpl<detail::PumpVariableSpeed_Impl>()->isRatedFlowRateDefaulted();
  }

  bool PumpVariableSpeed::isRatedFlowRateAutosized() const {
    return getImpl<detail::PumpVariableSpeed_Impl>()->isRatedFlowRateAutosized();
  }

  bool PumpVariableSpeed::setRatedFlowRate(double ratedFlowRate) {
    return getImpl<detail::PumpVariableSpeed_Impl>()->setRatedFlowRate(ratedFlowRate);
  }

  void PumpVariableSpeed::resetRatedFlowRate() {
    getImpl<detail::PumpVariableSpeed_Impl>()->resetRatedFlowRate();
  }

  void PumpVariableSpeed::autosizeRatedFlowRate() {
    getImpl<detail::PumpVariableSpeed_Impl>()->autosizeRatedFlowRate();
  }

  double PumpVariableSpeed::ratedPumpHead() const {
    return getImpl<detail::PumpVariableSpeed_Impl>()->ratedPumpHead();
  }

  bool PumpVariableSpeed::isRatedPumpHeadDefaulted() const {
    return getImpl<detail::PumpVariableSpeed_Impl>()->isRatedPumpHeadDefaulted();
  }

  bool PumpVariableSpeed::setRatedPumpHead(double ratedPumpHead) {
    return getImpl<detail::PumpVariableSpeed_Impl>()->setRatedPumpHead(ratedPumpHead);
  }

  void PumpVariableSpeed::resetRatedPumpHead() {
    getImpl<detail::PumpVariableSpeed_Impl>()->resetRatedPumpHead();
  }

  boost::optional<double> PumpVariableSpeed::ratedPowerConsumption() const {
    return getImpl<detail::PumpVariableSpeed_Impl>()->ratedPowerConsumption();
  }

  bool PumpVariableSpeed::isRatedPowerConsumptionDefaulted() const {
    return getImpl<detail::PumpVariableSpeed_Impl>()->isRatedPowerConsumptionDefaulted();
  }

  bool PumpVariableSpeed::isRatedPowerConsumptionAutosized() const {
    return getImpl<detail::PumpVariableSpeed_Impl>()->isRatedPowerConsumptionAutosized();
  }

  bool PumpVariableSpeed::setRatedPowerConsumption(double ratedPowerConsumption) {
    return getImpl<detail::PumpVariableSpeed_Impl>()->setRatedPowerConsumption(ratedPowerConsumption);
  }

  void PumpVariableSpeed::resetRatedPowerConsumption() {
    getImpl<detail::PumpVariableSpeed_Impl>()->resetRatedPowerConsumption();
  }

  void PumpVariableSpeed::autosizeRatedPowerConsumption() {
    getImpl<detail::PumpVariableSpeed_Impl>()->autosizeRatedPowerConsumption();
  }

  double PumpVariableSpeed::motorEfficiency() const {
    return getImpl<detail::PumpVariableSpeed_Impl>()->motorEfficiency();
  }

  bool PumpVariableSpeed::isMotorEfficiencyDefaulted() const {
    return getImpl<detail::PumpVariableSpeed_Impl>()->isMotorEfficiencyDefaulted();
  }

  bool PumpVariableSpeed::setMotorEfficiency(double motorEfficiency) {
    return getImpl<detail::PumpVariableSpeed_Impl>()->setMotorEfficiency(motorEfficiency);
  }

  void PumpVariableSpeed::resetMotorEfficiency() {
    getImpl<detail::PumpVariableSpeed_Impl>()->resetMotorEfficiency();
  }

  double PumpVariableSpeed::fractionofMotorInefficienciestoFluidStream() const {
    return getImpl<detail::PumpVariableSpeed_Impl>()->fractionofMotorInefficienciestoFluidStream();
  }

  bool PumpVariableSpeed::isFractionofMotorInefficienciestoFluidStreamDefaulted() const {
    return getImpl<detail::PumpVariableSpeed_Impl>()->isFractionofMotorInefficienciestoFluidStreamDefaulted();
  }

  bool PumpVariableSpeed::setFractionofMotorInefficienciestoFluidStream(double fractionofMotorInefficienciestoFluidStream) {
    return getImpl<detail::PumpVariableSpeed_Impl>()->setFractionofMotorInefficienciestoFluidStream(fractionofMotorInefficienciestoFluidStream);
  }

  void PumpVariableSpeed::resetFractionofMotorInefficienciestoFluidStream() {
    getImpl<detail::PumpVariableSpeed_Impl>()->resetFractionofMotorInefficienciestoFluidStream();
  }

  double PumpVariableSpeed::coefficient1ofthePartLoadPerformanceCurve() const {
    return getImpl<detail::PumpVariableSpeed_Impl>()->coefficient1ofthePartLoadPerformanceCurve();
  }

  bool PumpVariableSpeed::isCoefficient1ofthePartLoadPerformanceCurveDefaulted() const {
    return getImpl<detail::PumpVariableSpeed_Impl>()->isCoefficient1ofthePartLoadPerformanceCurveDefaulted();
  }

  bool PumpVariableSpeed::setCoefficient1ofthePartLoadPerformanceCurve(double coefficient1ofthePartLoadPerformanceCurve) {
    return getImpl<detail::PumpVariableSpeed_Impl>()->setCoefficient1ofthePartLoadPerformanceCurve(coefficient1ofthePartLoadPerformanceCurve);
  }

  void PumpVariableSpeed::resetCoefficient1ofthePartLoadPerformanceCurve() {
    getImpl<detail::PumpVariableSpeed_Impl>()->resetCoefficient1ofthePartLoadPerformanceCurve();
  }

  double PumpVariableSpeed::coefficient2ofthePartLoadPerformanceCurve() const {
    return getImpl<detail::PumpVariableSpeed_Impl>()->coefficient2ofthePartLoadPerformanceCurve();
  }

  bool PumpVariableSpeed::isCoefficient2ofthePartLoadPerformanceCurveDefaulted() const {
    return getImpl<detail::PumpVariableSpeed_Impl>()->isCoefficient2ofthePartLoadPerformanceCurveDefaulted();
  }

  bool PumpVariableSpeed::setCoefficient2ofthePartLoadPerformanceCurve(double coefficient2ofthePartLoadPerformanceCurve) {
    return getImpl<detail::PumpVariableSpeed_Impl>()->setCoefficient2ofthePartLoadPerformanceCurve(coefficient2ofthePartLoadPerformanceCurve);
  }

  void PumpVariableSpeed::resetCoefficient2ofthePartLoadPerformanceCurve() {
    getImpl<detail::PumpVariableSpeed_Impl>()->resetCoefficient2ofthePartLoadPerformanceCurve();
  }

  double PumpVariableSpeed::coefficient3ofthePartLoadPerformanceCurve() const {
    return getImpl<detail::PumpVariableSpeed_Impl>()->coefficient3ofthePartLoadPerformanceCurve();
  }

  bool PumpVariableSpeed::isCoefficient3ofthePartLoadPerformanceCurveDefaulted() const {
    return getImpl<detail::PumpVariableSpeed_Impl>()->isCoefficient3ofthePartLoadPerformanceCurveDefaulted();
  }

  bool PumpVariableSpeed::setCoefficient3ofthePartLoadPerformanceCurve(double coefficient3ofthePartLoadPerformanceCurve) {
    return getImpl<detail::PumpVariableSpeed_Impl>()->setCoefficient3ofthePartLoadPerformanceCurve(coefficient3ofthePartLoadPerformanceCurve);
  }

  void PumpVariableSpeed::resetCoefficient3ofthePartLoadPerformanceCurve() {
    getImpl<detail::PumpVariableSpeed_Impl>()->resetCoefficient3ofthePartLoadPerformanceCurve();
  }

  double PumpVariableSpeed::coefficient4ofthePartLoadPerformanceCurve() const {
    return getImpl<detail::PumpVariableSpeed_Impl>()->coefficient4ofthePartLoadPerformanceCurve();
  }

  bool PumpVariableSpeed::isCoefficient4ofthePartLoadPerformanceCurveDefaulted() const {
    return getImpl<detail::PumpVariableSpeed_Impl>()->isCoefficient4ofthePartLoadPerformanceCurveDefaulted();
  }

  bool PumpVariableSpeed::setCoefficient4ofthePartLoadPerformanceCurve(double coefficient4ofthePartLoadPerformanceCurve) {
    return getImpl<detail::PumpVariableSpeed_Impl>()->setCoefficient4ofthePartLoadPerformanceCurve(coefficient4ofthePartLoadPerformanceCurve);
  }

  void PumpVariableSpeed::resetCoefficient4ofthePartLoadPerformanceCurve() {
    getImpl<detail::PumpVariableSpeed_Impl>()->resetCoefficient4ofthePartLoadPerformanceCurve();
  }

  double PumpVariableSpeed::minimumFlowRate() const {
    return getImpl<detail::PumpVariableSpeed_Impl>()->minimumFlowRate();
  }

  bool PumpVariableSpeed::isMinimumFlowRateDefaulted() const {
    return getImpl<detail::PumpVariableSpeed_Impl>()->isMinimumFlowRateDefaulted();
  }

  bool PumpVariableSpeed::setMinimumFlowRate(double minimumFlowRate) {
    return getImpl<detail::PumpVariableSpeed_Impl>()->setMinimumFlowRate(minimumFlowRate);
  }

  void PumpVariableSpeed::resetMinimumFlowRate() {
    getImpl<detail::PumpVariableSpeed_Impl>()->resetMinimumFlowRate();
  }

  std::string PumpVariableSpeed::pumpControlType() const {
    return getImpl<detail::PumpVariableSpeed_Impl>()->pumpControlType();
  }

  bool PumpVariableSpeed::isPumpControlTypeDefaulted() const {
    return getImpl<detail::PumpVariableSpeed_Impl>()->isPumpControlTypeDefaulted();
  }

  bool PumpVariableSpeed::setPumpControlType(const std::string& pumpControlType) {
    return getImpl<detail::PumpVariableSpeed_Impl>()->setPumpControlType(pumpControlType);
  }

  void PumpVariableSpeed::resetPumpControlType() {
    getImpl<detail::PumpVariableSpeed_Impl>()->resetPumpControlType();
  }

  boost::optional<double> PumpVariableSpeed::impellerDiameter() const {
    return getImpl<detail::PumpVariableSpeed_Impl>()->impellerDiameter();
  }

  bool PumpVariableSpeed::setImpellerDiameter(double impellerDiameter) {
    return getImpl<detail::PumpVariableSpeed_Impl>()->setImpellerDiameter(impellerDiameter);
  }

  void PumpVariableSpeed::resetImpellerDiameter() {
    getImpl<detail::PumpVariableSpeed_Impl>()->resetImpellerDiameter();
  }

  boost::optional<std::string> PumpVariableSpeed::vFDControlType() const {
    return getImpl<detail::PumpVariableSpeed_Impl>()->vFDControlType();
  }

  bool PumpVariableSpeed::setVFDControlType(const std::string& vFDControlType) {
    return getImpl<detail::PumpVariableSpeed_Impl>()->setVFDControlType(vFDControlType);
  }

  void PumpVariableSpeed::resetVFDControlType() {
    getImpl<detail::PumpVariableSpeed_Impl>()->resetVFDControlType();
  }

  std::string PumpVariableSpeed::endUseSubcategory() const {
    return getImpl<detail::PumpVariableSpeed_Impl>()->endUseSubcategory();
  }

  bool PumpVariableSpeed::setEndUseSubcategory(const std::string& endUseSubcategory) {
    return getImpl<detail::PumpVariableSpeed_Impl>()->setEndUseSubcategory(endUseSubcategory);
  }

  double PumpVariableSpeed::skinLossRadiativeFraction() const {
    return getImpl<detail::PumpVariableSpeed_Impl>()->skinLossRadiativeFraction();
  }

  bool PumpVariableSpeed::setSkinLossRadiativeFraction(double skinLossRadiativeFraction) {
    return getImpl<detail::PumpVariableSpeed_Impl>()->setSkinLossRadiativeFraction(skinLossRadiativeFraction);
  }

  std::string PumpVariableSpeed::designPowerSizingMethod() const {
    return getImpl<detail::PumpVariableSpeed_Impl>()->designPowerSizingMethod();
  }

  bool PumpVariableSpeed::setDesignPowerSizingMethod(const std::string& designPowerSizingMethod) {
    return getImpl<detail::PumpVariableSpeed_Impl>()->setDesignPowerSizingMethod(designPowerSizingMethod);
  }

  double PumpVariableSpeed::designElectricPowerPerUnitFlowRate() const {
    return getImpl<detail::PumpVariableSpeed_Impl>()->designElectricPowerPerUnitFlowRate();
  }

  bool PumpVariableSpeed::setDesignElectricPowerPerUnitFlowRate(double designElectricPowerPerUnitFlowRate) {
    return getImpl<detail::PumpVariableSpeed_Impl>()->setDesignElectricPowerPerUnitFlowRate(designElectricPowerPerUnitFlowRate);
  }

  double PumpVariableSpeed::designShaftPowerPerUnitFlowRatePerUnitHead() const {
    return getImpl<detail::PumpVariableSpeed_Impl>()->designShaftPowerPerUnitFlowRatePerUnitHead();
  }

  bool PumpVariableSpeed::setDesignShaftPowerPerUnitFlowRatePerUnitHead(double designShaftPowerPerUnitFlowRatePerUnitHead) {
    return getImpl<detail::PumpVariableSpeed_Impl>()->setDesignShaftPowerPerUnitFlowRatePerUnitHead(designShaftPowerPerUnitFlowRatePerUnitHead);
  }

  double PumpVariableSpeed::designMinimumFlowRateFraction() const {
    return getImpl<detail::PumpVariableSpeed_Impl>()->designMinimumFlowRateFraction();
  }

  bool PumpVariableSpeed::setDesignMinimumFlowRateFraction(double designMinimumFlowRateFraction) {
    return getImpl<detail::PumpVariableSpeed_Impl>()->setDesignMinimumFlowRateFraction(designMinimumFlowRateFraction);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    unsigned PumpVariableSpeed_Impl::inletPort() const {
      return openstudio::Pump_VariableSpeedFields::InletNodeName;
    }

    unsigned PumpVariableSpeed_Impl::outletPort() const {
      return openstudio::Pump_VariableSpeedFields::OutletNodeName;
    }

    std::vector<std::string> PumpVariableSpeed_Impl::pumpControlTypeValues() const {
      return PumpVariableSpeed::pumpControlTypeValues();
    }

    std::vector<std::string> PumpVariableSpeed_Impl::designPowerSizingMethodValues() const {
      return PumpVariableSpeed::designPowerSizingMethodValues();
    }

    std::vector<std::string> PumpVariableSpeed_Impl::vfdControlTypeValues() const {
      return PumpVariableSpeed::vfdControlTypeValues();
    }

    boost::optional<double> PumpVariableSpeed_Impl::ratedFlowRate() const {
      return getDouble(openstudio::Pump_VariableSpeedFields::DesignMaximumFlowRate, true);
    }

    bool PumpVariableSpeed_Impl::isRatedFlowRateDefaulted() const {
      return isEmpty(openstudio::Pump_VariableSpeedFields::DesignMaximumFlowRate);
    }

    bool PumpVariableSpeed_Impl::isRatedFlowRateAutosized() const {
      if (const auto value = getString(openstudio::Pump_VariableSpeedFields::DesignMaximumFlowRate, true)) {
        return openstudio::istringEqual(value.get(), "autosize");
      }
      return false;
    }

    double PumpVariableSpeed_Impl::ratedPumpHead() const {
      const auto result = getDouble(openstudio::Pump_VariableSpeedFields::DesignPumpHead, true);
      OS_ASSERT(result);
      return result.get();
    }

    bool PumpVariableSpeed_Impl::isRatedPumpHeadDefaulted() const {
      return isEmpty(openstudio::Pump_VariableSpeedFields::DesignPumpHead);
    }

    boost::optional<double> PumpVariableSpeed_Impl::ratedPowerConsumption() const {
      return getDouble(openstudio::Pump_VariableSpeedFields::DesignPowerConsumption, true);
    }

    bool PumpVariableSpeed_Impl::isRatedPowerConsumptionDefaulted() const {
      return isEmpty(openstudio::Pump_VariableSpeedFields::DesignPowerConsumption);
    }

    bool PumpVariableSpeed_Impl::isRatedPowerConsumptionAutosized() const {
      if (const auto value = getString(openstudio::Pump_VariableSpeedFields::DesignPowerConsumption, true)) {
        return openstudio::istringEqual(value.get(), "autosize");
      }
      return false;
    }

    double PumpVariableSpeed_Impl::motorEfficiency() const {
      const auto result = getDouble(openstudio::Pump_VariableSpeedFields::MotorEfficiency, true);
      OS_ASSERT(result);
      return result.get();
    }

    bool PumpVariableSpeed_Impl::isMotorEfficiencyDefaulted() const {
      return isEmpty(openstudio::Pump_VariableSpeedFields::MotorEfficiency);
    }

    double PumpVariableSpeed_Impl::fractionofMotorInefficienciestoFluidStream() const {
      const auto result = getDouble(openstudio::Pump_VariableSpeedFields::FractionofMotorInefficienciestoFluidStream, true);
      OS_ASSERT(result);
      return result.get();
    }

    bool PumpVariableSpeed_Impl::isFractionofMotorInefficienciestoFluidStreamDefaulted() const {
      return isEmpty(openstudio::Pump_VariableSpeedFields::FractionofMotorInefficienciestoFluidStream);
    }

    double PumpVariableSpeed_Impl::coefficient1ofthePartLoadPerformanceCurve() const {
      const auto result = getDouble(openstudio::Pump_VariableSpeedFields::Coefficient1ofthePartLoadPerformanceCurve, true);
      OS_ASSERT(result);
      return result.get();
    }

    bool PumpVariableSpeed_Impl::isCoefficient1ofthePartLoadPerformanceCurveDefaulted() const {
      return isEmpty(openstudio::Pump_VariableSpeedFields::Coefficient1ofthePartLoadPerformanceCurve);
    }

    double PumpVariableSpeed_Impl::coefficient2ofthePartLoadPerformanceCurve() const {
      const auto result = getDouble(openstudio::Pump_VariableSpeedFields::Coefficient2ofthePartLoadPerformanceCurve, true);
      OS_ASSERT(result);
      return result.get();
    }

    bool PumpVariableSpeed_Impl::isCoefficient2ofthePartLoadPerformanceCurveDefaulted() const {
      return isEmpty(openstudio::Pump_VariableSpeedFields::Coefficient2ofthePartLoadPerformanceCurve);
    }

    double PumpVariableSpeed_Impl::coefficient3ofthePartLoadPerformanceCurve() const {
      const auto result = getDouble(openstudio::Pump_VariableSpeedFields::Coefficient3ofthePartLoadPerformanceCurve, true);
      OS_ASSERT(result);
      return result.get();
    }

    bool PumpVariableSpeed_Impl::isCoefficient3ofthePartLoadPerformanceCurveDefaulted() const {
      return isEmpty(openstudio::Pump_VariableSpeedFields::Coefficient3ofthePartLoadPerformanceCurve);
    }

    double PumpVariableSpeed_Impl::coefficient4ofthePartLoadPerformanceCurve() const {
      const auto result = getDouble(openstudio::Pump_VariableSpeedFields::Coefficient4ofthePartLoadPerformanceCurve, true);
      OS_ASSERT(result);
      return result.get();
    }

    bool PumpVariableSpeed_Impl::isCoefficient4ofthePartLoadPerformanceCurveDefaulted() const {
      return isEmpty(openstudio::Pump_VariableSpeedFields::Coefficient4ofthePartLoadPerformanceCurve);
    }

    double PumpVariableSpeed_Impl::minimumFlowRate() const {
      const auto result = getDouble(openstudio::Pump_VariableSpeedFields::DesignMinimumFlowRate, true);
      OS_ASSERT(result);
      return result.get();
    }

    bool PumpVariableSpeed_Impl::isMinimumFlowRateDefaulted() const {
      return isEmpty(openstudio::Pump_VariableSpeedFields::DesignMinimumFlowRate);
    }

    std::string PumpVariableSpeed_Impl::pumpControlType() const {
      const auto result = getString(openstudio::Pump_VariableSpeedFields::PumpControlType, true);
      OS_ASSERT(result);
      return result.get();
    }

    bool PumpVariableSpeed_Impl::isPumpControlTypeDefaulted() const {
      return isEmpty(openstudio::Pump_VariableSpeedFields::PumpControlType);
    }

    boost::optional<double> PumpVariableSpeed_Impl::impellerDiameter() const {
      return getDouble(openstudio::Pump_VariableSpeedFields::ImpellerDiameter, true);
    }

    boost::optional<std::string> PumpVariableSpeed_Impl::vFDControlType() const {
      return getString(openstudio::Pump_VariableSpeedFields::VFDControlType, true);
    }

    double PumpVariableSpeed_Impl::skinLossRadiativeFraction() const {
      const auto result = getDouble(openstudio::Pump_VariableSpeedFields::SkinLossRadiativeFraction, true);
      OS_ASSERT(result);
      return result.get();
    }

    std::string PumpVariableSpeed_Impl::designPowerSizingMethod() const {
      const auto result = getString(openstudio::Pump_VariableSpeedFields::DesignPowerSizingMethod, true);
      OS_ASSERT(result);
      return result.get();
    }

    double PumpVariableSpeed_Impl::designElectricPowerPerUnitFlowRate() const {
      const auto result = getDouble(openstudio::Pump_VariableSpeedFields::DesignElectricPowerperUnitFlowRate, true);
      OS_ASSERT(result);
      return result.get();
    }

    double PumpVariableSpeed_Impl::designShaftPowerPerUnitFlowRatePerUnitHead() const {
      const auto result = getDouble(openstudio::Pump_VariableSpeedFields::DesignShaftPowerperUnitFlowRateperUnitHead, true);
      OS_ASSERT(result);
      return result.get();
    }

    double PumpVariableSpeed_Impl::designMinimumFlowRateFraction() const {
      const auto result = getDouble(openstudio::Pump_VariableSpeedFields::DesignMinimumFlowRateFraction, true);
      OS_ASSERT(result);
      return result.get();
    }

    std::string PumpVariableSpeed_Impl::endUseSubcategory() const {
      const auto result = getString(openstudio::Pump_VariableSpeedFields::EndUseSubcategory, true);
      OS_ASSERT(result);
      return result.get();
    }

    bool PumpVariableSpeed_Impl::setRatedFlowRate(double ratedFlowRate) {
      const bool result = setDouble(openstudio::Pump_VariableSpeedFields::DesignMaximumFlowRate, ratedFlowRate);
      OS_ASSERT(result);
      return result;
    }

    void PumpVariableSpeed_Impl::resetRatedFlowRate() {
      const bool result = setString(openstudio::Pump_VariableSpeedFields::DesignMaximumFlowRate, "");
      OS_ASSERT(result);
    }

    void PumpVariableSpeed_Impl::autosizeRatedFlowRate() {
      const bool result = setString(openstudio::Pump_VariableSpeedFields::DesignMaximumFlowRate, "autosize");
      OS_ASSERT(result);
    }

    bool PumpVariableSpeed_Impl::setRatedPumpHead(double ratedPumpHead) {
      const bool result = setDouble(openstudio::Pump_VariableSpeedFields::DesignPumpHead, ratedPumpHead);
      OS_ASSERT(result);
      return result;
    }

    void PumpVariableSpeed_Impl::resetRatedPumpHead() {
      const bool result = setString(openstudio::Pump_VariableSpeedFields::DesignPumpHead, "");
      OS_ASSERT(result);
    }

    bool PumpVariableSpeed_Impl::setRatedPowerConsumption(double ratedPowerConsumption) {
      const bool result = setDouble(openstudio::Pump_VariableSpeedFields::DesignPowerConsumption, ratedPowerConsumption);
      OS_ASSERT(result);
      return result;
    }

    void PumpVariableSpeed_Impl::resetRatedPowerConsumption() {
      const bool result = setString(openstudio::Pump_VariableSpeedFields::DesignPowerConsumption, "");
      OS_ASSERT(result);
    }

    void PumpVariableSpeed_Impl::autosizeRatedPowerConsumption() {
      const bool result = setString(openstudio::Pump_VariableSpeedFields::DesignPowerConsumption, "autosize");
      OS_ASSERT(result);
    }

    bool PumpVariableSpeed_Impl::setMotorEfficiency(double motorEfficiency) {
      const bool result = setDouble(openstudio::Pump_VariableSpeedFields::MotorEfficiency, motorEfficiency);
      return result;
    }

    void PumpVariableSpeed_Impl::resetMotorEfficiency() {
      const bool result = setString(openstudio::Pump_VariableSpeedFields::MotorEfficiency, "");
      OS_ASSERT(result);
    }

    bool PumpVariableSpeed_Impl::setFractionofMotorInefficienciestoFluidStream(double fractionofMotorInefficienciestoFluidStream) {
      const bool result =
        setDouble(openstudio::Pump_VariableSpeedFields::FractionofMotorInefficienciestoFluidStream, fractionofMotorInefficienciestoFluidStream);
      return result;
    }

    void PumpVariableSpeed_Impl::resetFractionofMotorInefficienciestoFluidStream() {
      const bool result = setString(openstudio::Pump_VariableSpeedFields::FractionofMotorInefficienciestoFluidStream, "");
      OS_ASSERT(result);
    }

    bool PumpVariableSpeed_Impl::setCoefficient1ofthePartLoadPerformanceCurve(double coefficient1ofthePartLoadPerformanceCurve) {
      const bool result =
        setDouble(openstudio::Pump_VariableSpeedFields::Coefficient1ofthePartLoadPerformanceCurve, coefficient1ofthePartLoadPerformanceCurve);
      OS_ASSERT(result);
      return result;
    }

    void PumpVariableSpeed_Impl::resetCoefficient1ofthePartLoadPerformanceCurve() {
      const bool result = setString(openstudio::Pump_VariableSpeedFields::Coefficient1ofthePartLoadPerformanceCurve, "");
      OS_ASSERT(result);
    }

    bool PumpVariableSpeed_Impl::setCoefficient2ofthePartLoadPerformanceCurve(double coefficient2ofthePartLoadPerformanceCurve) {
      const bool result =
        setDouble(openstudio::Pump_VariableSpeedFields::Coefficient2ofthePartLoadPerformanceCurve, coefficient2ofthePartLoadPerformanceCurve);
      OS_ASSERT(result);
      return result;
    }

    void PumpVariableSpeed_Impl::resetCoefficient2ofthePartLoadPerformanceCurve() {
      const bool result = setString(openstudio::Pump_VariableSpeedFields::Coefficient2ofthePartLoadPerformanceCurve, "");
      OS_ASSERT(result);
    }

    bool PumpVariableSpeed_Impl::setCoefficient3ofthePartLoadPerformanceCurve(double coefficient3ofthePartLoadPerformanceCurve) {
      const bool result =
        setDouble(openstudio::Pump_VariableSpeedFields::Coefficient3ofthePartLoadPerformanceCurve, coefficient3ofthePartLoadPerformanceCurve);
      OS_ASSERT(result);
      return result;
    }

    void PumpVariableSpeed_Impl::resetCoefficient3ofthePartLoadPerformanceCurve() {
      const bool result = setString(openstudio::Pump_VariableSpeedFields::Coefficient3ofthePartLoadPerformanceCurve, "");
      OS_ASSERT(result);
    }

    bool PumpVariableSpeed_Impl::setCoefficient4ofthePartLoadPerformanceCurve(double coefficient4ofthePartLoadPerformanceCurve) {
      const bool result =
        setDouble(openstudio::Pump_VariableSpeedFields::Coefficient4ofthePartLoadPerformanceCurve, coefficient4ofthePartLoadPerformanceCurve);
      OS_ASSERT(result);
      return result;
    }

    void PumpVariableSpeed_Impl::resetCoefficient4ofthePartLoadPerformanceCurve() {
      const bool result = setString(openstudio::Pump_VariableSpeedFields::Coefficient4ofthePartLoadPerformanceCurve, "");
      OS_ASSERT(result);
    }

    bool PumpVariableSpeed_Impl::setMinimumFlowRate(double minimumFlowRate) {
      const bool result = setDouble(openstudio::Pump_VariableSpeedFields::DesignMinimumFlowRate, minimumFlowRate);
      OS_ASSERT(result);
      return result;
    }

    void PumpVariableSpeed_Impl::resetMinimumFlowRate() {
      const bool result = setString(openstudio::Pump_VariableSpeedFields::DesignMinimumFlowRate, "");
      OS_ASSERT(result);
    }

    bool PumpVariableSpeed_Impl::setPumpControlType(const std::string& pumpControlType) {
      return setString(openstudio::Pump_VariableSpeedFields::PumpControlType, pumpControlType);
    }

    void PumpVariableSpeed_Impl::resetPumpControlType() {
      const bool result = setString(openstudio::Pump_VariableSpeedFields::PumpControlType, "");
      OS_ASSERT(result);
    }

    bool PumpVariableSpeed_Impl::setImpellerDiameter(double impellerDiameter) {
      const bool result = setDouble(openstudio::Pump_VariableSpeedFields::ImpellerDiameter, impellerDiameter);
      OS_ASSERT(result);
      return result;
    }

    void PumpVariableSpeed_Impl::resetImpellerDiameter() {
      const bool result = setString(openstudio::Pump_VariableSpeedFields::ImpellerDiameter, "");
      OS_ASSERT(result);
    }

    bool PumpVariableSpeed_Impl::setVFDControlType(const std::string& vFDControlType) {
      const bool result = setString(openstudio::Pump_VariableSpeedFields::VFDControlType, vFDControlType);
      OS_ASSERT(result);
      return result;
    }

    void PumpVariableSpeed_Impl::resetVFDControlType() {
      const bool result = setString(openstudio::Pump_VariableSpeedFields::VFDControlType, "");
      OS_ASSERT(result);
    }

    bool PumpVariableSpeed_Impl::setSkinLossRadiativeFraction(double skinLossRadiativeFraction) {
      const bool result = setDouble(openstudio::Pump_VariableSpeedFields::SkinLossRadiativeFraction, skinLossRadiativeFraction);
      OS_ASSERT(result);
      return result;
    }

    bool PumpVariableSpeed_Impl::setDesignPowerSizingMethod(const std::string& designPowerSizingMethod) {
      const bool result = setString(openstudio::Pump_VariableSpeedFields::DesignPowerSizingMethod, designPowerSizingMethod);
      OS_ASSERT(result);
      return result;
    }

    bool PumpVariableSpeed_Impl::setDesignElectricPowerPerUnitFlowRate(double designElectricPowerPerUnitFlowRate) {
      const bool result = setDouble(openstudio::Pump_VariableSpeedFields::DesignElectricPowerperUnitFlowRate, designElectricPowerPerUnitFlowRate);
      OS_ASSERT(result);
      return result;
    }

    bool PumpVariableSpeed_Impl::setDesignShaftPowerPerUnitFlowRatePerUnitHead(double designShaftPowerPerUnitFlowRatePerUnitHead) {
      const bool result =
        setDouble(openstudio::Pump_VariableSpeedFields::DesignShaftPowerperUnitFlowRateperUnitHead, designShaftPowerPerUnitFlowRatePerUnitHead);
      OS_ASSERT(result);
      return result;
    }

    bool PumpVariableSpeed_Impl::setDesignMinimumFlowRateFraction(double designMinimumFlowRateFraction) {
      const bool result = setDouble(openstudio::Pump_VariableSpeedFields::DesignMinimumFlowRateFraction, designMinimumFlowRateFraction);
      OS_ASSERT(result);
      return result;
    }

    bool PumpVariableSpeed_Impl::setEndUseSubcategory(const std::string& endUseSubcategory) {
      const bool result = setString(openstudio::Pump_VariableSpeedFields::EndUseSubcategory, endUseSubcategory);
      OS_ASSERT(result);
      return result;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
