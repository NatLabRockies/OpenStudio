/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/PumpConstantSpeed.hpp"
#include "StraightComponent/PumpConstantSpeed_Impl.hpp"

#include "Model.hpp"
#include "Loop/PlantLoop.hpp"
#include "StraightComponent/Node.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/Pump_ConstantSpeed_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  PumpConstantSpeed::PumpConstantSpeed(const Model& model) : StraightComponent(PumpConstantSpeed::iddObjectType(), model) {
    autosizeRatedFlowRate();
    autosizeRatedPowerConsumption();
    OS_ASSERT(setRatedPumpHead(179352.0));
    OS_ASSERT(setMotorEfficiency(0.9));
    OS_ASSERT(setPumpControlType("Intermittent"));
    OS_ASSERT(setFractionofMotorInefficienciestoFluidStream(0.0));
    OS_ASSERT(setDesignPowerSizingMethod("PowerPerFlowPerPressure"));
    OS_ASSERT(setDesignElectricPowerPerUnitFlowRate(348701.1));
    OS_ASSERT(setDesignShaftPowerPerUnitFlowRatePerUnitHead(1.282051282));
    setString(openstudio::Pump_ConstantSpeedFields::PumpFlowRateScheduleName, "");
    setString(openstudio::Pump_ConstantSpeedFields::PumpCurveName, "");
    setString(openstudio::Pump_ConstantSpeedFields::ImpellerDiameter, "");
    setString(openstudio::Pump_ConstantSpeedFields::RotationalSpeed, "");
    setString(openstudio::Pump_ConstantSpeedFields::ZoneName, "");
    setString(openstudio::Pump_ConstantSpeedFields::SkinLossRadiativeFraction, "");
    setEndUseSubcategory("General");
  }

  PumpConstantSpeed::PumpConstantSpeed(std::shared_ptr<detail::PumpConstantSpeed_Impl> impl) : StraightComponent(std::move(impl)) {}

  IddObjectType PumpConstantSpeed::iddObjectType() {
    return IddObjectType::Pump_ConstantSpeed;
  }

  std::vector<std::string> PumpConstantSpeed::pumpControlTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Pump_ConstantSpeedFields::PumpControlType);
  }

  std::vector<std::string> PumpConstantSpeed::designPowerSizingMethodValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Pump_ConstantSpeedFields::DesignPowerSizingMethod);
  }

  boost::optional<double> PumpConstantSpeed::ratedFlowRate() const {
    return getImpl<detail::PumpConstantSpeed_Impl>()->ratedFlowRate();
  }

  bool PumpConstantSpeed::isRatedFlowRateAutosized() const {
    return getImpl<detail::PumpConstantSpeed_Impl>()->isRatedFlowRateAutosized();
  }

  bool PumpConstantSpeed::setRatedFlowRate(double ratedFlowRate) {
    return getImpl<detail::PumpConstantSpeed_Impl>()->setRatedFlowRate(ratedFlowRate);
  }

  void PumpConstantSpeed::resetRatedFlowRate() {
    getImpl<detail::PumpConstantSpeed_Impl>()->resetRatedFlowRate();
  }

  void PumpConstantSpeed::autosizeRatedFlowRate() {
    getImpl<detail::PumpConstantSpeed_Impl>()->autosizeRatedFlowRate();
  }

  double PumpConstantSpeed::ratedPumpHead() const {
    return getImpl<detail::PumpConstantSpeed_Impl>()->ratedPumpHead();
  }

  bool PumpConstantSpeed::isRatedPumpHeadDefaulted() const {
    return getImpl<detail::PumpConstantSpeed_Impl>()->isRatedPumpHeadDefaulted();
  }

  bool PumpConstantSpeed::setRatedPumpHead(double ratedPumpHead) {
    return getImpl<detail::PumpConstantSpeed_Impl>()->setRatedPumpHead(ratedPumpHead);
  }

  void PumpConstantSpeed::resetRatedPumpHead() {
    getImpl<detail::PumpConstantSpeed_Impl>()->resetRatedPumpHead();
  }

  boost::optional<double> PumpConstantSpeed::ratedPowerConsumption() const {
    return getImpl<detail::PumpConstantSpeed_Impl>()->ratedPowerConsumption();
  }

  bool PumpConstantSpeed::isRatedPowerConsumptionAutosized() const {
    return getImpl<detail::PumpConstantSpeed_Impl>()->isRatedPowerConsumptionAutosized();
  }

  bool PumpConstantSpeed::setRatedPowerConsumption(double ratedPowerConsumption) {
    return getImpl<detail::PumpConstantSpeed_Impl>()->setRatedPowerConsumption(ratedPowerConsumption);
  }

  void PumpConstantSpeed::resetRatedPowerConsumption() {
    getImpl<detail::PumpConstantSpeed_Impl>()->resetRatedPowerConsumption();
  }

  void PumpConstantSpeed::autosizeRatedPowerConsumption() {
    getImpl<detail::PumpConstantSpeed_Impl>()->autosizeRatedPowerConsumption();
  }

  double PumpConstantSpeed::motorEfficiency() const {
    return getImpl<detail::PumpConstantSpeed_Impl>()->motorEfficiency();
  }

  bool PumpConstantSpeed::isMotorEfficiencyDefaulted() const {
    return getImpl<detail::PumpConstantSpeed_Impl>()->isMotorEfficiencyDefaulted();
  }

  bool PumpConstantSpeed::setMotorEfficiency(double motorEfficiency) {
    return getImpl<detail::PumpConstantSpeed_Impl>()->setMotorEfficiency(motorEfficiency);
  }

  void PumpConstantSpeed::resetMotorEfficiency() {
    getImpl<detail::PumpConstantSpeed_Impl>()->resetMotorEfficiency();
  }

  double PumpConstantSpeed::fractionofMotorInefficienciestoFluidStream() const {
    return getImpl<detail::PumpConstantSpeed_Impl>()->fractionofMotorInefficienciestoFluidStream();
  }

  bool PumpConstantSpeed::isFractionofMotorInefficienciestoFluidStreamDefaulted() const {
    return getImpl<detail::PumpConstantSpeed_Impl>()->isFractionofMotorInefficienciestoFluidStreamDefaulted();
  }

  bool PumpConstantSpeed::setFractionofMotorInefficienciestoFluidStream(double fractionofMotorInefficienciestoFluidStream) {
    return getImpl<detail::PumpConstantSpeed_Impl>()->setFractionofMotorInefficienciestoFluidStream(fractionofMotorInefficienciestoFluidStream);
  }

  void PumpConstantSpeed::resetFractionofMotorInefficienciestoFluidStream() {
    getImpl<detail::PumpConstantSpeed_Impl>()->resetFractionofMotorInefficienciestoFluidStream();
  }

  std::string PumpConstantSpeed::pumpControlType() const {
    return getImpl<detail::PumpConstantSpeed_Impl>()->pumpControlType();
  }

  bool PumpConstantSpeed::isPumpControlTypeDefaulted() const {
    return getImpl<detail::PumpConstantSpeed_Impl>()->isPumpControlTypeDefaulted();
  }

  bool PumpConstantSpeed::setPumpControlType(const std::string& pumpControlType) {
    return getImpl<detail::PumpConstantSpeed_Impl>()->setPumpControlType(pumpControlType);
  }

  void PumpConstantSpeed::resetPumpControlType() {
    getImpl<detail::PumpConstantSpeed_Impl>()->resetPumpControlType();
  }

  boost::optional<double> PumpConstantSpeed::impellerDiameter() const {
    return getImpl<detail::PumpConstantSpeed_Impl>()->impellerDiameter();
  }

  bool PumpConstantSpeed::setImpellerDiameter(double impellerDiameter) {
    return getImpl<detail::PumpConstantSpeed_Impl>()->setImpellerDiameter(impellerDiameter);
  }

  void PumpConstantSpeed::resetImpellerDiameter() {
    getImpl<detail::PumpConstantSpeed_Impl>()->resetImpellerDiameter();
  }

  boost::optional<double> PumpConstantSpeed::rotationalSpeed() const {
    return getImpl<detail::PumpConstantSpeed_Impl>()->rotationalSpeed();
  }

  bool PumpConstantSpeed::setRotationalSpeed(double rotationalSpeed) {
    return getImpl<detail::PumpConstantSpeed_Impl>()->setRotationalSpeed(rotationalSpeed);
  }

  void PumpConstantSpeed::resetRotationalSpeed() {
    getImpl<detail::PumpConstantSpeed_Impl>()->resetRotationalSpeed();
  }

  boost::optional<double> PumpConstantSpeed::skinLossRadiativeFraction() const {
    return getImpl<detail::PumpConstantSpeed_Impl>()->skinLossRadiativeFraction();
  }

  bool PumpConstantSpeed::setSkinLossRadiativeFraction(double skinLossRadiativeFraction) {
    return getImpl<detail::PumpConstantSpeed_Impl>()->setSkinLossRadiativeFraction(skinLossRadiativeFraction);
  }

  void PumpConstantSpeed::resetSkinLossRadiativeFraction() {
    getImpl<detail::PumpConstantSpeed_Impl>()->resetSkinLossRadiativeFraction();
  }

  std::string PumpConstantSpeed::designPowerSizingMethod() const {
    return getImpl<detail::PumpConstantSpeed_Impl>()->designPowerSizingMethod();
  }

  bool PumpConstantSpeed::setDesignPowerSizingMethod(const std::string& designPowerSizingMethod) {
    return getImpl<detail::PumpConstantSpeed_Impl>()->setDesignPowerSizingMethod(designPowerSizingMethod);
  }

  double PumpConstantSpeed::designElectricPowerPerUnitFlowRate() const {
    return getImpl<detail::PumpConstantSpeed_Impl>()->designElectricPowerPerUnitFlowRate();
  }

  bool PumpConstantSpeed::setDesignElectricPowerPerUnitFlowRate(double designElectricPowerPerUnitFlowRate) {
    return getImpl<detail::PumpConstantSpeed_Impl>()->setDesignElectricPowerPerUnitFlowRate(designElectricPowerPerUnitFlowRate);
  }

  double PumpConstantSpeed::designShaftPowerPerUnitFlowRatePerUnitHead() const {
    return getImpl<detail::PumpConstantSpeed_Impl>()->designShaftPowerPerUnitFlowRatePerUnitHead();
  }

  bool PumpConstantSpeed::setDesignShaftPowerPerUnitFlowRatePerUnitHead(double designShaftPowerPerUnitFlowRatePerUnitHead) {
    return getImpl<detail::PumpConstantSpeed_Impl>()->setDesignShaftPowerPerUnitFlowRatePerUnitHead(designShaftPowerPerUnitFlowRatePerUnitHead);
  }

  std::string PumpConstantSpeed::endUseSubcategory() const {
    return getImpl<detail::PumpConstantSpeed_Impl>()->endUseSubcategory();
  }

  bool PumpConstantSpeed::setEndUseSubcategory(const std::string& endUseSubcategory) {
    return getImpl<detail::PumpConstantSpeed_Impl>()->setEndUseSubcategory(endUseSubcategory);
  }

  bool PumpConstantSpeed::addToNode(Node& node) {
    return getImpl<detail::PumpConstantSpeed_Impl>()->addToNode(node);
  }

  boost::optional<double> PumpConstantSpeed::autosizedRatedFlowRate() const {
    return getImpl<detail::PumpConstantSpeed_Impl>()->autosizedRatedFlowRate();
  }

  boost::optional<double> PumpConstantSpeed::autosizedRatedPowerConsumption() const {
    return getImpl<detail::PumpConstantSpeed_Impl>()->autosizedRatedPowerConsumption();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    unsigned PumpConstantSpeed_Impl::inletPort() const {
      return openstudio::Pump_ConstantSpeedFields::InletNodeName;
    }

    unsigned PumpConstantSpeed_Impl::outletPort() const {
      return openstudio::Pump_ConstantSpeedFields::OutletNodeName;
    }

    bool PumpConstantSpeed_Impl::addToNode(Node& node) {
      if (node.plantLoop()) {
        return StraightComponent_Impl::addToNode(node);
      }

      return false;
    }

    boost::optional<double> PumpConstantSpeed_Impl::ratedFlowRate() const {
      return getDouble(openstudio::Pump_ConstantSpeedFields::DesignFlowRate, true);
    }

    bool PumpConstantSpeed_Impl::isRatedFlowRateAutosized() const {
      if (m_isRatedFlowRateAutosized) {
        return true;
      }
      if (const auto value = getString(openstudio::Pump_ConstantSpeedFields::DesignFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    double PumpConstantSpeed_Impl::ratedPumpHead() const {
      const auto value = getDouble(openstudio::Pump_ConstantSpeedFields::DesignPumpHead, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PumpConstantSpeed_Impl::isRatedPumpHeadDefaulted() const {
      return isEmpty(openstudio::Pump_ConstantSpeedFields::DesignPumpHead);
    }

    boost::optional<double> PumpConstantSpeed_Impl::ratedPowerConsumption() const {
      return getDouble(openstudio::Pump_ConstantSpeedFields::DesignPowerConsumption, true);
    }

    bool PumpConstantSpeed_Impl::isRatedPowerConsumptionAutosized() const {
      if (m_isRatedPowerConsumptionAutosized) {
        return true;
      }
      if (const auto value = getString(openstudio::Pump_ConstantSpeedFields::DesignPowerConsumption, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    double PumpConstantSpeed_Impl::motorEfficiency() const {
      const auto value = getDouble(openstudio::Pump_ConstantSpeedFields::MotorEfficiency, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PumpConstantSpeed_Impl::isMotorEfficiencyDefaulted() const {
      return isEmpty(openstudio::Pump_ConstantSpeedFields::MotorEfficiency);
    }

    double PumpConstantSpeed_Impl::fractionofMotorInefficienciestoFluidStream() const {
      const auto value = getDouble(openstudio::Pump_ConstantSpeedFields::FractionofMotorInefficienciestoFluidStream, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PumpConstantSpeed_Impl::isFractionofMotorInefficienciestoFluidStreamDefaulted() const {
      return isEmpty(openstudio::Pump_ConstantSpeedFields::FractionofMotorInefficienciestoFluidStream);
    }

    std::string PumpConstantSpeed_Impl::pumpControlType() const {
      const auto value = getString(openstudio::Pump_ConstantSpeedFields::PumpControlType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PumpConstantSpeed_Impl::isPumpControlTypeDefaulted() const {
      return isEmpty(openstudio::Pump_ConstantSpeedFields::PumpControlType);
    }

    boost::optional<double> PumpConstantSpeed_Impl::impellerDiameter() const {
      return getDouble(openstudio::Pump_ConstantSpeedFields::ImpellerDiameter, true);
    }

    boost::optional<double> PumpConstantSpeed_Impl::rotationalSpeed() const {
      return getDouble(openstudio::Pump_ConstantSpeedFields::RotationalSpeed, true);
    }

    boost::optional<double> PumpConstantSpeed_Impl::skinLossRadiativeFraction() const {
      return getDouble(openstudio::Pump_ConstantSpeedFields::SkinLossRadiativeFraction, true);
    }

    std::string PumpConstantSpeed_Impl::designPowerSizingMethod() const {
      const auto value = getString(openstudio::Pump_ConstantSpeedFields::DesignPowerSizingMethod, true);
      OS_ASSERT(value);
      return *value;
    }

    double PumpConstantSpeed_Impl::designElectricPowerPerUnitFlowRate() const {
      const auto value = getDouble(openstudio::Pump_ConstantSpeedFields::DesignElectricPowerperUnitFlowRate, true);
      OS_ASSERT(value);
      return *value;
    }

    double PumpConstantSpeed_Impl::designShaftPowerPerUnitFlowRatePerUnitHead() const {
      const auto value = getDouble(openstudio::Pump_ConstantSpeedFields::DesignShaftPowerperUnitFlowRateperUnitHead, true);
      OS_ASSERT(value);
      return *value;
    }

    std::string PumpConstantSpeed_Impl::endUseSubcategory() const {
      const auto value = getString(openstudio::Pump_ConstantSpeedFields::EndUseSubcategory, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PumpConstantSpeed_Impl::setRatedFlowRate(double ratedFlowRate) {
      const bool result = setDouble(openstudio::Pump_ConstantSpeedFields::DesignFlowRate, ratedFlowRate);
      if (result) {
        m_isRatedFlowRateAutosized = false;
      }
      return result;
    }

    void PumpConstantSpeed_Impl::resetRatedFlowRate() {
      setString(openstudio::Pump_ConstantSpeedFields::DesignFlowRate, "", false);
      m_isRatedFlowRateAutosized = true;
    }

    void PumpConstantSpeed_Impl::autosizeRatedFlowRate() {
      setString(openstudio::Pump_ConstantSpeedFields::DesignFlowRate, "Autosize", false);
      m_isRatedFlowRateAutosized = true;
    }

    bool PumpConstantSpeed_Impl::setRatedPumpHead(double ratedPumpHead) {
      return setDouble(openstudio::Pump_ConstantSpeedFields::DesignPumpHead, ratedPumpHead, false);
    }

    void PumpConstantSpeed_Impl::resetRatedPumpHead() {
      const bool result = setString(openstudio::Pump_ConstantSpeedFields::DesignPumpHead, "");
      OS_ASSERT(result);
    }

    bool PumpConstantSpeed_Impl::setRatedPowerConsumption(double ratedPowerConsumption) {
      const bool result = setDouble(openstudio::Pump_ConstantSpeedFields::DesignPowerConsumption, ratedPowerConsumption);
      if (result) {
        m_isRatedPowerConsumptionAutosized = false;
      }
      return result;
    }

    void PumpConstantSpeed_Impl::resetRatedPowerConsumption() {
      setString(openstudio::Pump_ConstantSpeedFields::DesignPowerConsumption, "", false);
      m_isRatedPowerConsumptionAutosized = true;
    }

    void PumpConstantSpeed_Impl::autosizeRatedPowerConsumption() {
      setString(openstudio::Pump_ConstantSpeedFields::DesignPowerConsumption, "Autosize", false);
      m_isRatedPowerConsumptionAutosized = true;
    }

    bool PumpConstantSpeed_Impl::setMotorEfficiency(double motorEfficiency) {
      return setDouble(openstudio::Pump_ConstantSpeedFields::MotorEfficiency, motorEfficiency, false);
    }

    void PumpConstantSpeed_Impl::resetMotorEfficiency() {
      const bool result = setString(openstudio::Pump_ConstantSpeedFields::MotorEfficiency, "");
      OS_ASSERT(result);
    }

    bool PumpConstantSpeed_Impl::setFractionofMotorInefficienciestoFluidStream(double fractionofMotorInefficienciestoFluidStream) {
      return setDouble(openstudio::Pump_ConstantSpeedFields::FractionofMotorInefficienciestoFluidStream, fractionofMotorInefficienciestoFluidStream,
                       false);
    }

    void PumpConstantSpeed_Impl::resetFractionofMotorInefficienciestoFluidStream() {
      const bool result = setString(openstudio::Pump_ConstantSpeedFields::FractionofMotorInefficienciestoFluidStream, "");
      OS_ASSERT(result);
    }

    bool PumpConstantSpeed_Impl::setPumpControlType(const std::string& pumpControlType) {
      return setString(openstudio::Pump_ConstantSpeedFields::PumpControlType, pumpControlType, false);
    }

    void PumpConstantSpeed_Impl::resetPumpControlType() {
      setString(openstudio::Pump_ConstantSpeedFields::PumpControlType, "", false);
    }

    bool PumpConstantSpeed_Impl::setImpellerDiameter(double impellerDiameter) {
      return setDouble(openstudio::Pump_ConstantSpeedFields::ImpellerDiameter, impellerDiameter);
    }

    void PumpConstantSpeed_Impl::resetImpellerDiameter() {
      const bool result = setString(openstudio::Pump_ConstantSpeedFields::ImpellerDiameter, "");
      OS_ASSERT(result);
    }

    bool PumpConstantSpeed_Impl::setRotationalSpeed(double rotationalSpeed) {
      return setDouble(openstudio::Pump_ConstantSpeedFields::RotationalSpeed, rotationalSpeed);
    }

    void PumpConstantSpeed_Impl::resetRotationalSpeed() {
      const bool result = setString(openstudio::Pump_ConstantSpeedFields::RotationalSpeed, "");
      OS_ASSERT(result);
    }

    bool PumpConstantSpeed_Impl::setSkinLossRadiativeFraction(double skinLossRadiativeFraction) {
      return setDouble(openstudio::Pump_ConstantSpeedFields::SkinLossRadiativeFraction, skinLossRadiativeFraction);
    }

    void PumpConstantSpeed_Impl::resetSkinLossRadiativeFraction() {
      const bool result = setString(openstudio::Pump_ConstantSpeedFields::SkinLossRadiativeFraction, "");
      OS_ASSERT(result);
    }

    bool PumpConstantSpeed_Impl::setDesignPowerSizingMethod(const std::string& designPowerSizingMethod) {
      return setString(openstudio::Pump_ConstantSpeedFields::DesignPowerSizingMethod, designPowerSizingMethod, false);
    }

    bool PumpConstantSpeed_Impl::setDesignElectricPowerPerUnitFlowRate(double designElectricPowerPerUnitFlowRate) {
      return setDouble(openstudio::Pump_ConstantSpeedFields::DesignElectricPowerperUnitFlowRate, designElectricPowerPerUnitFlowRate, false);
    }

    bool PumpConstantSpeed_Impl::setDesignShaftPowerPerUnitFlowRatePerUnitHead(double designShaftPowerPerUnitFlowRatePerUnitHead) {
      return setDouble(openstudio::Pump_ConstantSpeedFields::DesignShaftPowerperUnitFlowRateperUnitHead, designShaftPowerPerUnitFlowRatePerUnitHead,
                       false);
    }

    bool PumpConstantSpeed_Impl::setEndUseSubcategory(const std::string& endUseSubcategory) {
      return setString(openstudio::Pump_ConstantSpeedFields::EndUseSubcategory, endUseSubcategory, false);
    }

    boost::optional<double> PumpConstantSpeed_Impl::autosizedRatedFlowRate() const {
      // epmodel does not currently resolve autosized values from SQL results.
      return boost::none;
    }

    boost::optional<double> PumpConstantSpeed_Impl::autosizedRatedPowerConsumption() const {
      // epmodel does not currently resolve autosized values from SQL results.
      return boost::none;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
