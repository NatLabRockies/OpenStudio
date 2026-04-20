/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "scaffolds/PumpVariableSpeedCondensate.hpp"
#include "scaffolds/PumpVariableSpeedCondensate_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/Pump_VariableSpeed_Condensate_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  PumpVariableSpeedCondensate::PumpVariableSpeedCondensate(const Model& model) : ModelObject(PumpVariableSpeedCondensate::iddObjectType(), model) {}

  PumpVariableSpeedCondensate::PumpVariableSpeedCondensate(std::shared_ptr<detail::PumpVariableSpeedCondensate_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType PumpVariableSpeedCondensate::iddObjectType() {
    return IddObjectType::Pump_VariableSpeed_Condensate;
  }

  std::vector<std::string> PumpVariableSpeedCondensate::designPowerSizingMethodValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::Pump_VariableSpeed_CondensateFields::DesignPowerSizingMethod);
  }

  boost::optional<double> PumpVariableSpeedCondensate::designSteamVolumeFlowRate() const {
    return getImpl<detail::PumpVariableSpeedCondensate_Impl>()->designSteamVolumeFlowRate();
  }

  bool PumpVariableSpeedCondensate::isDesignSteamVolumeFlowRateAutosized() const {
    return getImpl<detail::PumpVariableSpeedCondensate_Impl>()->isDesignSteamVolumeFlowRateAutosized();
  }

  bool PumpVariableSpeedCondensate::setDesignSteamVolumeFlowRate(double designSteamVolumeFlowRate) {
    return getImpl<detail::PumpVariableSpeedCondensate_Impl>()->setDesignSteamVolumeFlowRate(designSteamVolumeFlowRate);
  }

  void PumpVariableSpeedCondensate::resetDesignSteamVolumeFlowRate() {
    getImpl<detail::PumpVariableSpeedCondensate_Impl>()->resetDesignSteamVolumeFlowRate();
  }

  void PumpVariableSpeedCondensate::autosizeDesignSteamVolumeFlowRate() {
    getImpl<detail::PumpVariableSpeedCondensate_Impl>()->autosizeDesignSteamVolumeFlowRate();
  }

  double PumpVariableSpeedCondensate::designPumpHead() const {
    return getImpl<detail::PumpVariableSpeedCondensate_Impl>()->designPumpHead();
  }

  bool PumpVariableSpeedCondensate::isDesignPumpHeadDefaulted() const {
    return getImpl<detail::PumpVariableSpeedCondensate_Impl>()->isDesignPumpHeadDefaulted();
  }

  bool PumpVariableSpeedCondensate::setDesignPumpHead(double designPumpHead) {
    return getImpl<detail::PumpVariableSpeedCondensate_Impl>()->setDesignPumpHead(designPumpHead);
  }

  void PumpVariableSpeedCondensate::resetDesignPumpHead() {
    getImpl<detail::PumpVariableSpeedCondensate_Impl>()->resetDesignPumpHead();
  }

  boost::optional<double> PumpVariableSpeedCondensate::designPowerConsumption() const {
    return getImpl<detail::PumpVariableSpeedCondensate_Impl>()->designPowerConsumption();
  }

  bool PumpVariableSpeedCondensate::isDesignPowerConsumptionAutosized() const {
    return getImpl<detail::PumpVariableSpeedCondensate_Impl>()->isDesignPowerConsumptionAutosized();
  }

  bool PumpVariableSpeedCondensate::setDesignPowerConsumption(double designPowerConsumption) {
    return getImpl<detail::PumpVariableSpeedCondensate_Impl>()->setDesignPowerConsumption(designPowerConsumption);
  }

  void PumpVariableSpeedCondensate::resetDesignPowerConsumption() {
    getImpl<detail::PumpVariableSpeedCondensate_Impl>()->resetDesignPowerConsumption();
  }

  void PumpVariableSpeedCondensate::autosizeDesignPowerConsumption() {
    getImpl<detail::PumpVariableSpeedCondensate_Impl>()->autosizeDesignPowerConsumption();
  }

  double PumpVariableSpeedCondensate::motorEfficiency() const {
    return getImpl<detail::PumpVariableSpeedCondensate_Impl>()->motorEfficiency();
  }

  bool PumpVariableSpeedCondensate::isMotorEfficiencyDefaulted() const {
    return getImpl<detail::PumpVariableSpeedCondensate_Impl>()->isMotorEfficiencyDefaulted();
  }

  bool PumpVariableSpeedCondensate::setMotorEfficiency(double motorEfficiency) {
    return getImpl<detail::PumpVariableSpeedCondensate_Impl>()->setMotorEfficiency(motorEfficiency);
  }

  void PumpVariableSpeedCondensate::resetMotorEfficiency() {
    getImpl<detail::PumpVariableSpeedCondensate_Impl>()->resetMotorEfficiency();
  }

  double PumpVariableSpeedCondensate::fractionOfMotorInefficienciesToFluidStream() const {
    return getImpl<detail::PumpVariableSpeedCondensate_Impl>()->fractionOfMotorInefficienciesToFluidStream();
  }

  bool PumpVariableSpeedCondensate::isFractionOfMotorInefficienciesToFluidStreamDefaulted() const {
    return getImpl<detail::PumpVariableSpeedCondensate_Impl>()->isFractionOfMotorInefficienciesToFluidStreamDefaulted();
  }

  bool PumpVariableSpeedCondensate::setFractionOfMotorInefficienciesToFluidStream(double fractionOfMotorInefficienciesToFluidStream) {
    return getImpl<detail::PumpVariableSpeedCondensate_Impl>()->setFractionOfMotorInefficienciesToFluidStream(
      fractionOfMotorInefficienciesToFluidStream);
  }

  void PumpVariableSpeedCondensate::resetFractionOfMotorInefficienciesToFluidStream() {
    getImpl<detail::PumpVariableSpeedCondensate_Impl>()->resetFractionOfMotorInefficienciesToFluidStream();
  }

  double PumpVariableSpeedCondensate::coefficient1OfThePartLoadPerformanceCurve() const {
    return getImpl<detail::PumpVariableSpeedCondensate_Impl>()->coefficient1OfThePartLoadPerformanceCurve();
  }

  bool PumpVariableSpeedCondensate::isCoefficient1OfThePartLoadPerformanceCurveDefaulted() const {
    return getImpl<detail::PumpVariableSpeedCondensate_Impl>()->isCoefficient1OfThePartLoadPerformanceCurveDefaulted();
  }

  bool PumpVariableSpeedCondensate::setCoefficient1OfThePartLoadPerformanceCurve(double coefficient1OfThePartLoadPerformanceCurve) {
    return getImpl<detail::PumpVariableSpeedCondensate_Impl>()->setCoefficient1OfThePartLoadPerformanceCurve(
      coefficient1OfThePartLoadPerformanceCurve);
  }

  void PumpVariableSpeedCondensate::resetCoefficient1OfThePartLoadPerformanceCurve() {
    getImpl<detail::PumpVariableSpeedCondensate_Impl>()->resetCoefficient1OfThePartLoadPerformanceCurve();
  }

  double PumpVariableSpeedCondensate::coefficient2OfThePartLoadPerformanceCurve() const {
    return getImpl<detail::PumpVariableSpeedCondensate_Impl>()->coefficient2OfThePartLoadPerformanceCurve();
  }

  bool PumpVariableSpeedCondensate::isCoefficient2OfThePartLoadPerformanceCurveDefaulted() const {
    return getImpl<detail::PumpVariableSpeedCondensate_Impl>()->isCoefficient2OfThePartLoadPerformanceCurveDefaulted();
  }

  bool PumpVariableSpeedCondensate::setCoefficient2OfThePartLoadPerformanceCurve(double coefficient2OfThePartLoadPerformanceCurve) {
    return getImpl<detail::PumpVariableSpeedCondensate_Impl>()->setCoefficient2OfThePartLoadPerformanceCurve(
      coefficient2OfThePartLoadPerformanceCurve);
  }

  void PumpVariableSpeedCondensate::resetCoefficient2OfThePartLoadPerformanceCurve() {
    getImpl<detail::PumpVariableSpeedCondensate_Impl>()->resetCoefficient2OfThePartLoadPerformanceCurve();
  }

  double PumpVariableSpeedCondensate::coefficient3OfThePartLoadPerformanceCurve() const {
    return getImpl<detail::PumpVariableSpeedCondensate_Impl>()->coefficient3OfThePartLoadPerformanceCurve();
  }

  bool PumpVariableSpeedCondensate::isCoefficient3OfThePartLoadPerformanceCurveDefaulted() const {
    return getImpl<detail::PumpVariableSpeedCondensate_Impl>()->isCoefficient3OfThePartLoadPerformanceCurveDefaulted();
  }

  bool PumpVariableSpeedCondensate::setCoefficient3OfThePartLoadPerformanceCurve(double coefficient3OfThePartLoadPerformanceCurve) {
    return getImpl<detail::PumpVariableSpeedCondensate_Impl>()->setCoefficient3OfThePartLoadPerformanceCurve(
      coefficient3OfThePartLoadPerformanceCurve);
  }

  void PumpVariableSpeedCondensate::resetCoefficient3OfThePartLoadPerformanceCurve() {
    getImpl<detail::PumpVariableSpeedCondensate_Impl>()->resetCoefficient3OfThePartLoadPerformanceCurve();
  }

  double PumpVariableSpeedCondensate::coefficient4OfThePartLoadPerformanceCurve() const {
    return getImpl<detail::PumpVariableSpeedCondensate_Impl>()->coefficient4OfThePartLoadPerformanceCurve();
  }

  bool PumpVariableSpeedCondensate::isCoefficient4OfThePartLoadPerformanceCurveDefaulted() const {
    return getImpl<detail::PumpVariableSpeedCondensate_Impl>()->isCoefficient4OfThePartLoadPerformanceCurveDefaulted();
  }

  bool PumpVariableSpeedCondensate::setCoefficient4OfThePartLoadPerformanceCurve(double coefficient4OfThePartLoadPerformanceCurve) {
    return getImpl<detail::PumpVariableSpeedCondensate_Impl>()->setCoefficient4OfThePartLoadPerformanceCurve(
      coefficient4OfThePartLoadPerformanceCurve);
  }

  void PumpVariableSpeedCondensate::resetCoefficient4OfThePartLoadPerformanceCurve() {
    getImpl<detail::PumpVariableSpeedCondensate_Impl>()->resetCoefficient4OfThePartLoadPerformanceCurve();
  }

  boost::optional<double> PumpVariableSpeedCondensate::skinLossRadiativeFraction() const {
    return getImpl<detail::PumpVariableSpeedCondensate_Impl>()->skinLossRadiativeFraction();
  }

  bool PumpVariableSpeedCondensate::setSkinLossRadiativeFraction(double skinLossRadiativeFraction) {
    return getImpl<detail::PumpVariableSpeedCondensate_Impl>()->setSkinLossRadiativeFraction(skinLossRadiativeFraction);
  }

  void PumpVariableSpeedCondensate::resetSkinLossRadiativeFraction() {
    getImpl<detail::PumpVariableSpeedCondensate_Impl>()->resetSkinLossRadiativeFraction();
  }

  std::string PumpVariableSpeedCondensate::designPowerSizingMethod() const {
    return getImpl<detail::PumpVariableSpeedCondensate_Impl>()->designPowerSizingMethod();
  }

  bool PumpVariableSpeedCondensate::isDesignPowerSizingMethodDefaulted() const {
    return getImpl<detail::PumpVariableSpeedCondensate_Impl>()->isDesignPowerSizingMethodDefaulted();
  }

  bool PumpVariableSpeedCondensate::setDesignPowerSizingMethod(const std::string& designPowerSizingMethod) {
    return getImpl<detail::PumpVariableSpeedCondensate_Impl>()->setDesignPowerSizingMethod(designPowerSizingMethod);
  }

  void PumpVariableSpeedCondensate::resetDesignPowerSizingMethod() {
    getImpl<detail::PumpVariableSpeedCondensate_Impl>()->resetDesignPowerSizingMethod();
  }

  double PumpVariableSpeedCondensate::designElectricPowerPerUnitFlowRate() const {
    return getImpl<detail::PumpVariableSpeedCondensate_Impl>()->designElectricPowerPerUnitFlowRate();
  }

  bool PumpVariableSpeedCondensate::isDesignElectricPowerPerUnitFlowRateDefaulted() const {
    return getImpl<detail::PumpVariableSpeedCondensate_Impl>()->isDesignElectricPowerPerUnitFlowRateDefaulted();
  }

  bool PumpVariableSpeedCondensate::setDesignElectricPowerPerUnitFlowRate(double designElectricPowerPerUnitFlowRate) {
    return getImpl<detail::PumpVariableSpeedCondensate_Impl>()->setDesignElectricPowerPerUnitFlowRate(designElectricPowerPerUnitFlowRate);
  }

  void PumpVariableSpeedCondensate::resetDesignElectricPowerPerUnitFlowRate() {
    getImpl<detail::PumpVariableSpeedCondensate_Impl>()->resetDesignElectricPowerPerUnitFlowRate();
  }

  double PumpVariableSpeedCondensate::designShaftPowerPerUnitFlowRatePerUnitHead() const {
    return getImpl<detail::PumpVariableSpeedCondensate_Impl>()->designShaftPowerPerUnitFlowRatePerUnitHead();
  }

  bool PumpVariableSpeedCondensate::isDesignShaftPowerPerUnitFlowRatePerUnitHeadDefaulted() const {
    return getImpl<detail::PumpVariableSpeedCondensate_Impl>()->isDesignShaftPowerPerUnitFlowRatePerUnitHeadDefaulted();
  }

  bool PumpVariableSpeedCondensate::setDesignShaftPowerPerUnitFlowRatePerUnitHead(double designShaftPowerPerUnitFlowRatePerUnitHead) {
    return getImpl<detail::PumpVariableSpeedCondensate_Impl>()->setDesignShaftPowerPerUnitFlowRatePerUnitHead(
      designShaftPowerPerUnitFlowRatePerUnitHead);
  }

  void PumpVariableSpeedCondensate::resetDesignShaftPowerPerUnitFlowRatePerUnitHead() {
    getImpl<detail::PumpVariableSpeedCondensate_Impl>()->resetDesignShaftPowerPerUnitFlowRatePerUnitHead();
  }

  std::string PumpVariableSpeedCondensate::endUseSubcategory() const {
    return getImpl<detail::PumpVariableSpeedCondensate_Impl>()->endUseSubcategory();
  }

  bool PumpVariableSpeedCondensate::isEndUseSubcategoryDefaulted() const {
    return getImpl<detail::PumpVariableSpeedCondensate_Impl>()->isEndUseSubcategoryDefaulted();
  }

  bool PumpVariableSpeedCondensate::setEndUseSubcategory(const std::string& endUseSubcategory) {
    return getImpl<detail::PumpVariableSpeedCondensate_Impl>()->setEndUseSubcategory(endUseSubcategory);
  }

  void PumpVariableSpeedCondensate::resetEndUseSubcategory() {
    getImpl<detail::PumpVariableSpeedCondensate_Impl>()->resetEndUseSubcategory();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    boost::optional<double> PumpVariableSpeedCondensate_Impl::designSteamVolumeFlowRate() const {
      return getDouble(openstudio::Pump_VariableSpeed_CondensateFields::DesignSteamVolumeFlowRate, true);
    }

    bool PumpVariableSpeedCondensate_Impl::isDesignSteamVolumeFlowRateAutosized() const {
      if (auto value = getString(openstudio::Pump_VariableSpeed_CondensateFields::DesignSteamVolumeFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool PumpVariableSpeedCondensate_Impl::setDesignSteamVolumeFlowRate(double designSteamVolumeFlowRate) {
      const bool result = setDouble(openstudio::Pump_VariableSpeed_CondensateFields::DesignSteamVolumeFlowRate, designSteamVolumeFlowRate);
      OS_ASSERT(result);
      return result;
    }

    void PumpVariableSpeedCondensate_Impl::resetDesignSteamVolumeFlowRate() {
      OS_ASSERT(setString(openstudio::Pump_VariableSpeed_CondensateFields::DesignSteamVolumeFlowRate, ""));
    }

    void PumpVariableSpeedCondensate_Impl::autosizeDesignSteamVolumeFlowRate() {
      OS_ASSERT(setString(openstudio::Pump_VariableSpeed_CondensateFields::DesignSteamVolumeFlowRate, "autosize"));
    }

    double PumpVariableSpeedCondensate_Impl::designPumpHead() const {
      const auto value = getDouble(openstudio::Pump_VariableSpeed_CondensateFields::DesignPumpHead, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PumpVariableSpeedCondensate_Impl::isDesignPumpHeadDefaulted() const {
      return isEmpty(openstudio::Pump_VariableSpeed_CondensateFields::DesignPumpHead);
    }

    bool PumpVariableSpeedCondensate_Impl::setDesignPumpHead(double designPumpHead) {
      const bool result = setDouble(openstudio::Pump_VariableSpeed_CondensateFields::DesignPumpHead, designPumpHead);
      OS_ASSERT(result);
      return result;
    }

    void PumpVariableSpeedCondensate_Impl::resetDesignPumpHead() {
      OS_ASSERT(setString(openstudio::Pump_VariableSpeed_CondensateFields::DesignPumpHead, ""));
    }

    boost::optional<double> PumpVariableSpeedCondensate_Impl::designPowerConsumption() const {
      return getDouble(openstudio::Pump_VariableSpeed_CondensateFields::DesignPowerConsumption, true);
    }

    bool PumpVariableSpeedCondensate_Impl::isDesignPowerConsumptionAutosized() const {
      if (auto value = getString(openstudio::Pump_VariableSpeed_CondensateFields::DesignPowerConsumption, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool PumpVariableSpeedCondensate_Impl::setDesignPowerConsumption(double designPowerConsumption) {
      const bool result = setDouble(openstudio::Pump_VariableSpeed_CondensateFields::DesignPowerConsumption, designPowerConsumption);
      OS_ASSERT(result);
      return result;
    }

    void PumpVariableSpeedCondensate_Impl::resetDesignPowerConsumption() {
      OS_ASSERT(setString(openstudio::Pump_VariableSpeed_CondensateFields::DesignPowerConsumption, ""));
    }

    void PumpVariableSpeedCondensate_Impl::autosizeDesignPowerConsumption() {
      OS_ASSERT(setString(openstudio::Pump_VariableSpeed_CondensateFields::DesignPowerConsumption, "autosize"));
    }

    double PumpVariableSpeedCondensate_Impl::motorEfficiency() const {
      const auto value = getDouble(openstudio::Pump_VariableSpeed_CondensateFields::MotorEfficiency, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PumpVariableSpeedCondensate_Impl::isMotorEfficiencyDefaulted() const {
      return isEmpty(openstudio::Pump_VariableSpeed_CondensateFields::MotorEfficiency);
    }

    bool PumpVariableSpeedCondensate_Impl::setMotorEfficiency(double motorEfficiency) {
      return setDouble(openstudio::Pump_VariableSpeed_CondensateFields::MotorEfficiency, motorEfficiency);
    }

    void PumpVariableSpeedCondensate_Impl::resetMotorEfficiency() {
      OS_ASSERT(setString(openstudio::Pump_VariableSpeed_CondensateFields::MotorEfficiency, ""));
    }

    double PumpVariableSpeedCondensate_Impl::fractionOfMotorInefficienciesToFluidStream() const {
      const auto value = getDouble(openstudio::Pump_VariableSpeed_CondensateFields::FractionofMotorInefficienciestoFluidStream, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PumpVariableSpeedCondensate_Impl::isFractionOfMotorInefficienciesToFluidStreamDefaulted() const {
      return isEmpty(openstudio::Pump_VariableSpeed_CondensateFields::FractionofMotorInefficienciestoFluidStream);
    }

    bool PumpVariableSpeedCondensate_Impl::setFractionOfMotorInefficienciesToFluidStream(double fractionOfMotorInefficienciesToFluidStream) {
      return setDouble(openstudio::Pump_VariableSpeed_CondensateFields::FractionofMotorInefficienciestoFluidStream,
                       fractionOfMotorInefficienciesToFluidStream);
    }

    void PumpVariableSpeedCondensate_Impl::resetFractionOfMotorInefficienciesToFluidStream() {
      OS_ASSERT(setString(openstudio::Pump_VariableSpeed_CondensateFields::FractionofMotorInefficienciestoFluidStream, ""));
    }

    double PumpVariableSpeedCondensate_Impl::coefficient1OfThePartLoadPerformanceCurve() const {
      const auto value = getDouble(openstudio::Pump_VariableSpeed_CondensateFields::Coefficient1ofthePartLoadPerformanceCurve, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PumpVariableSpeedCondensate_Impl::isCoefficient1OfThePartLoadPerformanceCurveDefaulted() const {
      return isEmpty(openstudio::Pump_VariableSpeed_CondensateFields::Coefficient1ofthePartLoadPerformanceCurve);
    }

    bool PumpVariableSpeedCondensate_Impl::setCoefficient1OfThePartLoadPerformanceCurve(double coefficient1OfThePartLoadPerformanceCurve) {
      const bool result = setDouble(openstudio::Pump_VariableSpeed_CondensateFields::Coefficient1ofthePartLoadPerformanceCurve,
                                    coefficient1OfThePartLoadPerformanceCurve);
      OS_ASSERT(result);
      return result;
    }

    void PumpVariableSpeedCondensate_Impl::resetCoefficient1OfThePartLoadPerformanceCurve() {
      OS_ASSERT(setString(openstudio::Pump_VariableSpeed_CondensateFields::Coefficient1ofthePartLoadPerformanceCurve, ""));
    }

    double PumpVariableSpeedCondensate_Impl::coefficient2OfThePartLoadPerformanceCurve() const {
      const auto value = getDouble(openstudio::Pump_VariableSpeed_CondensateFields::Coefficient2ofthePartLoadPerformanceCurve, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PumpVariableSpeedCondensate_Impl::isCoefficient2OfThePartLoadPerformanceCurveDefaulted() const {
      return isEmpty(openstudio::Pump_VariableSpeed_CondensateFields::Coefficient2ofthePartLoadPerformanceCurve);
    }

    bool PumpVariableSpeedCondensate_Impl::setCoefficient2OfThePartLoadPerformanceCurve(double coefficient2OfThePartLoadPerformanceCurve) {
      const bool result = setDouble(openstudio::Pump_VariableSpeed_CondensateFields::Coefficient2ofthePartLoadPerformanceCurve,
                                    coefficient2OfThePartLoadPerformanceCurve);
      OS_ASSERT(result);
      return result;
    }

    void PumpVariableSpeedCondensate_Impl::resetCoefficient2OfThePartLoadPerformanceCurve() {
      OS_ASSERT(setString(openstudio::Pump_VariableSpeed_CondensateFields::Coefficient2ofthePartLoadPerformanceCurve, ""));
    }

    double PumpVariableSpeedCondensate_Impl::coefficient3OfThePartLoadPerformanceCurve() const {
      const auto value = getDouble(openstudio::Pump_VariableSpeed_CondensateFields::Coefficient3ofthePartLoadPerformanceCurve, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PumpVariableSpeedCondensate_Impl::isCoefficient3OfThePartLoadPerformanceCurveDefaulted() const {
      return isEmpty(openstudio::Pump_VariableSpeed_CondensateFields::Coefficient3ofthePartLoadPerformanceCurve);
    }

    bool PumpVariableSpeedCondensate_Impl::setCoefficient3OfThePartLoadPerformanceCurve(double coefficient3OfThePartLoadPerformanceCurve) {
      const bool result = setDouble(openstudio::Pump_VariableSpeed_CondensateFields::Coefficient3ofthePartLoadPerformanceCurve,
                                    coefficient3OfThePartLoadPerformanceCurve);
      OS_ASSERT(result);
      return result;
    }

    void PumpVariableSpeedCondensate_Impl::resetCoefficient3OfThePartLoadPerformanceCurve() {
      OS_ASSERT(setString(openstudio::Pump_VariableSpeed_CondensateFields::Coefficient3ofthePartLoadPerformanceCurve, ""));
    }

    double PumpVariableSpeedCondensate_Impl::coefficient4OfThePartLoadPerformanceCurve() const {
      const auto value = getDouble(openstudio::Pump_VariableSpeed_CondensateFields::Coefficient4ofthePartLoadPerformanceCurve, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PumpVariableSpeedCondensate_Impl::isCoefficient4OfThePartLoadPerformanceCurveDefaulted() const {
      return isEmpty(openstudio::Pump_VariableSpeed_CondensateFields::Coefficient4ofthePartLoadPerformanceCurve);
    }

    bool PumpVariableSpeedCondensate_Impl::setCoefficient4OfThePartLoadPerformanceCurve(double coefficient4OfThePartLoadPerformanceCurve) {
      const bool result = setDouble(openstudio::Pump_VariableSpeed_CondensateFields::Coefficient4ofthePartLoadPerformanceCurve,
                                    coefficient4OfThePartLoadPerformanceCurve);
      OS_ASSERT(result);
      return result;
    }

    void PumpVariableSpeedCondensate_Impl::resetCoefficient4OfThePartLoadPerformanceCurve() {
      OS_ASSERT(setString(openstudio::Pump_VariableSpeed_CondensateFields::Coefficient4ofthePartLoadPerformanceCurve, ""));
    }

    boost::optional<double> PumpVariableSpeedCondensate_Impl::skinLossRadiativeFraction() const {
      return getDouble(openstudio::Pump_VariableSpeed_CondensateFields::SkinLossRadiativeFraction, true);
    }

    bool PumpVariableSpeedCondensate_Impl::setSkinLossRadiativeFraction(double skinLossRadiativeFraction) {
      return setDouble(openstudio::Pump_VariableSpeed_CondensateFields::SkinLossRadiativeFraction, skinLossRadiativeFraction);
    }

    void PumpVariableSpeedCondensate_Impl::resetSkinLossRadiativeFraction() {
      OS_ASSERT(setString(openstudio::Pump_VariableSpeed_CondensateFields::SkinLossRadiativeFraction, ""));
    }

    std::string PumpVariableSpeedCondensate_Impl::designPowerSizingMethod() const {
      const auto value = getString(openstudio::Pump_VariableSpeed_CondensateFields::DesignPowerSizingMethod, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PumpVariableSpeedCondensate_Impl::isDesignPowerSizingMethodDefaulted() const {
      return isEmpty(openstudio::Pump_VariableSpeed_CondensateFields::DesignPowerSizingMethod);
    }

    bool PumpVariableSpeedCondensate_Impl::setDesignPowerSizingMethod(const std::string& designPowerSizingMethod) {
      return setString(openstudio::Pump_VariableSpeed_CondensateFields::DesignPowerSizingMethod, designPowerSizingMethod);
    }

    void PumpVariableSpeedCondensate_Impl::resetDesignPowerSizingMethod() {
      OS_ASSERT(setString(openstudio::Pump_VariableSpeed_CondensateFields::DesignPowerSizingMethod, ""));
    }

    double PumpVariableSpeedCondensate_Impl::designElectricPowerPerUnitFlowRate() const {
      const auto value = getDouble(openstudio::Pump_VariableSpeed_CondensateFields::DesignElectricPowerperUnitFlowRate, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PumpVariableSpeedCondensate_Impl::isDesignElectricPowerPerUnitFlowRateDefaulted() const {
      return isEmpty(openstudio::Pump_VariableSpeed_CondensateFields::DesignElectricPowerperUnitFlowRate);
    }

    bool PumpVariableSpeedCondensate_Impl::setDesignElectricPowerPerUnitFlowRate(double designElectricPowerPerUnitFlowRate) {
      return setDouble(openstudio::Pump_VariableSpeed_CondensateFields::DesignElectricPowerperUnitFlowRate, designElectricPowerPerUnitFlowRate);
    }

    void PumpVariableSpeedCondensate_Impl::resetDesignElectricPowerPerUnitFlowRate() {
      OS_ASSERT(setString(openstudio::Pump_VariableSpeed_CondensateFields::DesignElectricPowerperUnitFlowRate, ""));
    }

    double PumpVariableSpeedCondensate_Impl::designShaftPowerPerUnitFlowRatePerUnitHead() const {
      const auto value = getDouble(openstudio::Pump_VariableSpeed_CondensateFields::DesignShaftPowerperUnitFlowRateperUnitHead, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PumpVariableSpeedCondensate_Impl::isDesignShaftPowerPerUnitFlowRatePerUnitHeadDefaulted() const {
      return isEmpty(openstudio::Pump_VariableSpeed_CondensateFields::DesignShaftPowerperUnitFlowRateperUnitHead);
    }

    bool PumpVariableSpeedCondensate_Impl::setDesignShaftPowerPerUnitFlowRatePerUnitHead(double designShaftPowerPerUnitFlowRatePerUnitHead) {
      return setDouble(openstudio::Pump_VariableSpeed_CondensateFields::DesignShaftPowerperUnitFlowRateperUnitHead,
                       designShaftPowerPerUnitFlowRatePerUnitHead);
    }

    void PumpVariableSpeedCondensate_Impl::resetDesignShaftPowerPerUnitFlowRatePerUnitHead() {
      OS_ASSERT(setString(openstudio::Pump_VariableSpeed_CondensateFields::DesignShaftPowerperUnitFlowRateperUnitHead, ""));
    }

    std::string PumpVariableSpeedCondensate_Impl::endUseSubcategory() const {
      const auto value = getString(openstudio::Pump_VariableSpeed_CondensateFields::EndUseSubcategory, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PumpVariableSpeedCondensate_Impl::isEndUseSubcategoryDefaulted() const {
      return isEmpty(openstudio::Pump_VariableSpeed_CondensateFields::EndUseSubcategory);
    }

    bool PumpVariableSpeedCondensate_Impl::setEndUseSubcategory(const std::string& endUseSubcategory) {
      return setString(openstudio::Pump_VariableSpeed_CondensateFields::EndUseSubcategory, endUseSubcategory);
    }

    void PumpVariableSpeedCondensate_Impl::resetEndUseSubcategory() {
      OS_ASSERT(setString(openstudio::Pump_VariableSpeed_CondensateFields::EndUseSubcategory, ""));
    }

    std::vector<std::string> PumpVariableSpeedCondensate_Impl::designPowerSizingMethodValues() const {
      return openstudio::epmodel::PumpVariableSpeedCondensate::designPowerSizingMethodValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
