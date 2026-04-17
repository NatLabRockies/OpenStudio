/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/HeaderedPumpsConstantSpeed.hpp"
#include "StraightComponent/HeaderedPumpsConstantSpeed_Impl.hpp"

#include "Loop/PlantLoop.hpp"
#include "Model.hpp"
#include "StraightComponent/Node.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/HeaderedPumps_ConstantSpeed_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

  HeaderedPumpsConstantSpeed::HeaderedPumpsConstantSpeed(const Model& model) : StraightComponent(HeaderedPumpsConstantSpeed::iddObjectType(), model) {
    autosizeTotalRatedFlowRate();
    OS_ASSERT(setNumberofPumpsinBank(2));
    OS_ASSERT(setFlowSequencingControlScheme("Sequential"));
    OS_ASSERT(setRatedPumpHead(179352.0));
    autosizeRatedPowerConsumption();
    OS_ASSERT(setMotorEfficiency(0.9));
    OS_ASSERT(setFractionofMotorInefficienciestoFluidStream(0.0));
    OS_ASSERT(setPumpControlType("Continuous"));
    OS_ASSERT(setSkinLossRadiativeFraction(0.1));
    OS_ASSERT(setDesignPowerSizingMethod("PowerPerFlowPerPressure"));
    OS_ASSERT(setDesignElectricPowerPerUnitFlowRate(348701.1));
    OS_ASSERT(setDesignShaftPowerPerUnitFlowRatePerUnitHead(1.282051282));
    OS_ASSERT(setEndUseSubcategory("General"));
  }

  HeaderedPumpsConstantSpeed::HeaderedPumpsConstantSpeed(std::shared_ptr<detail::HeaderedPumpsConstantSpeed_Impl> impl)
    : StraightComponent(std::move(impl)) {}

  IddObjectType HeaderedPumpsConstantSpeed::iddObjectType() {
    return IddObjectType::HeaderedPumps_ConstantSpeed;
  }

  std::vector<std::string> HeaderedPumpsConstantSpeed::flowSequencingControlSchemeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::HeaderedPumps_ConstantSpeedFields::FlowSequencingControlScheme);
  }

  std::vector<std::string> HeaderedPumpsConstantSpeed::pumpControlTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::HeaderedPumps_ConstantSpeedFields::PumpControlType);
  }

  std::vector<std::string> HeaderedPumpsConstantSpeed::designPowerSizingMethodValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::HeaderedPumps_ConstantSpeedFields::DesignPowerSizingMethod);
  }

  boost::optional<double> HeaderedPumpsConstantSpeed::totalRatedFlowRate() const {
    return getImpl<detail::HeaderedPumpsConstantSpeed_Impl>()->totalRatedFlowRate();
  }

  bool HeaderedPumpsConstantSpeed::isTotalRatedFlowRateAutosized() const {
    return getImpl<detail::HeaderedPumpsConstantSpeed_Impl>()->isTotalRatedFlowRateAutosized();
  }

  bool HeaderedPumpsConstantSpeed::setTotalRatedFlowRate(double totalRatedFlowRate) {
    return getImpl<detail::HeaderedPumpsConstantSpeed_Impl>()->setTotalRatedFlowRate(totalRatedFlowRate);
  }

  void HeaderedPumpsConstantSpeed::autosizeTotalRatedFlowRate() {
    getImpl<detail::HeaderedPumpsConstantSpeed_Impl>()->autosizeTotalRatedFlowRate();
  }

  boost::optional<double> HeaderedPumpsConstantSpeed::autosizedTotalRatedFlowRate() const {
    return getImpl<detail::HeaderedPumpsConstantSpeed_Impl>()->autosizedTotalRatedFlowRate();
  }

  int HeaderedPumpsConstantSpeed::numberofPumpsinBank() const {
    return getImpl<detail::HeaderedPumpsConstantSpeed_Impl>()->numberofPumpsinBank();
  }

  bool HeaderedPumpsConstantSpeed::setNumberofPumpsinBank(int numberofPumpsinBank) {
    return getImpl<detail::HeaderedPumpsConstantSpeed_Impl>()->setNumberofPumpsinBank(numberofPumpsinBank);
  }

  std::string HeaderedPumpsConstantSpeed::flowSequencingControlScheme() const {
    return getImpl<detail::HeaderedPumpsConstantSpeed_Impl>()->flowSequencingControlScheme();
  }

  bool HeaderedPumpsConstantSpeed::setFlowSequencingControlScheme(const std::string& flowSequencingControlScheme) {
    return getImpl<detail::HeaderedPumpsConstantSpeed_Impl>()->setFlowSequencingControlScheme(flowSequencingControlScheme);
  }

  double HeaderedPumpsConstantSpeed::ratedPumpHead() const {
    return getImpl<detail::HeaderedPumpsConstantSpeed_Impl>()->ratedPumpHead();
  }

  bool HeaderedPumpsConstantSpeed::setRatedPumpHead(double ratedPumpHead) {
    return getImpl<detail::HeaderedPumpsConstantSpeed_Impl>()->setRatedPumpHead(ratedPumpHead);
  }

  boost::optional<double> HeaderedPumpsConstantSpeed::ratedPowerConsumption() const {
    return getImpl<detail::HeaderedPumpsConstantSpeed_Impl>()->ratedPowerConsumption();
  }

  bool HeaderedPumpsConstantSpeed::isRatedPowerConsumptionAutosized() const {
    return getImpl<detail::HeaderedPumpsConstantSpeed_Impl>()->isRatedPowerConsumptionAutosized();
  }

  bool HeaderedPumpsConstantSpeed::setRatedPowerConsumption(double ratedPowerConsumption) {
    return getImpl<detail::HeaderedPumpsConstantSpeed_Impl>()->setRatedPowerConsumption(ratedPowerConsumption);
  }

  void HeaderedPumpsConstantSpeed::autosizeRatedPowerConsumption() {
    getImpl<detail::HeaderedPumpsConstantSpeed_Impl>()->autosizeRatedPowerConsumption();
  }

  boost::optional<double> HeaderedPumpsConstantSpeed::autosizedRatedPowerConsumption() const {
    return getImpl<detail::HeaderedPumpsConstantSpeed_Impl>()->autosizedRatedPowerConsumption();
  }

  double HeaderedPumpsConstantSpeed::motorEfficiency() const {
    return getImpl<detail::HeaderedPumpsConstantSpeed_Impl>()->motorEfficiency();
  }

  bool HeaderedPumpsConstantSpeed::setMotorEfficiency(double motorEfficiency) {
    return getImpl<detail::HeaderedPumpsConstantSpeed_Impl>()->setMotorEfficiency(motorEfficiency);
  }

  double HeaderedPumpsConstantSpeed::fractionofMotorInefficienciestoFluidStream() const {
    return getImpl<detail::HeaderedPumpsConstantSpeed_Impl>()->fractionofMotorInefficienciestoFluidStream();
  }

  bool HeaderedPumpsConstantSpeed::setFractionofMotorInefficienciestoFluidStream(double fractionofMotorInefficienciestoFluidStream) {
    return getImpl<detail::HeaderedPumpsConstantSpeed_Impl>()->setFractionofMotorInefficienciestoFluidStream(
      fractionofMotorInefficienciestoFluidStream);
  }

  std::string HeaderedPumpsConstantSpeed::pumpControlType() const {
    return getImpl<detail::HeaderedPumpsConstantSpeed_Impl>()->pumpControlType();
  }

  bool HeaderedPumpsConstantSpeed::setPumpControlType(const std::string& pumpControlType) {
    return getImpl<detail::HeaderedPumpsConstantSpeed_Impl>()->setPumpControlType(pumpControlType);
  }

  double HeaderedPumpsConstantSpeed::skinLossRadiativeFraction() const {
    return getImpl<detail::HeaderedPumpsConstantSpeed_Impl>()->skinLossRadiativeFraction();
  }

  bool HeaderedPumpsConstantSpeed::setSkinLossRadiativeFraction(double skinLossRadiativeFraction) {
    return getImpl<detail::HeaderedPumpsConstantSpeed_Impl>()->setSkinLossRadiativeFraction(skinLossRadiativeFraction);
  }

  std::string HeaderedPumpsConstantSpeed::designPowerSizingMethod() const {
    return getImpl<detail::HeaderedPumpsConstantSpeed_Impl>()->designPowerSizingMethod();
  }

  bool HeaderedPumpsConstantSpeed::setDesignPowerSizingMethod(const std::string& designPowerSizingMethod) {
    return getImpl<detail::HeaderedPumpsConstantSpeed_Impl>()->setDesignPowerSizingMethod(designPowerSizingMethod);
  }

  double HeaderedPumpsConstantSpeed::designElectricPowerPerUnitFlowRate() const {
    return getImpl<detail::HeaderedPumpsConstantSpeed_Impl>()->designElectricPowerPerUnitFlowRate();
  }

  bool HeaderedPumpsConstantSpeed::setDesignElectricPowerPerUnitFlowRate(double designElectricPowerPerUnitFlowRate) {
    return getImpl<detail::HeaderedPumpsConstantSpeed_Impl>()->setDesignElectricPowerPerUnitFlowRate(designElectricPowerPerUnitFlowRate);
  }

  double HeaderedPumpsConstantSpeed::designShaftPowerPerUnitFlowRatePerUnitHead() const {
    return getImpl<detail::HeaderedPumpsConstantSpeed_Impl>()->designShaftPowerPerUnitFlowRatePerUnitHead();
  }

  bool HeaderedPumpsConstantSpeed::setDesignShaftPowerPerUnitFlowRatePerUnitHead(double designShaftPowerPerUnitFlowRatePerUnitHead) {
    return getImpl<detail::HeaderedPumpsConstantSpeed_Impl>()->setDesignShaftPowerPerUnitFlowRatePerUnitHead(
      designShaftPowerPerUnitFlowRatePerUnitHead);
  }

  std::string HeaderedPumpsConstantSpeed::endUseSubcategory() const {
    return getImpl<detail::HeaderedPumpsConstantSpeed_Impl>()->endUseSubcategory();
  }

  bool HeaderedPumpsConstantSpeed::setEndUseSubcategory(const std::string& endUseSubcategory) {
    return getImpl<detail::HeaderedPumpsConstantSpeed_Impl>()->setEndUseSubcategory(endUseSubcategory);
  }

  bool HeaderedPumpsConstantSpeed::addToNode(Node& node) {
    return getImpl<detail::HeaderedPumpsConstantSpeed_Impl>()->addToNode(node);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    unsigned HeaderedPumpsConstantSpeed_Impl::inletPort() const {
      return openstudio::HeaderedPumps_ConstantSpeedFields::InletNodeName;
    }

    unsigned HeaderedPumpsConstantSpeed_Impl::outletPort() const {
      return openstudio::HeaderedPumps_ConstantSpeedFields::OutletNodeName;
    }

    bool HeaderedPumpsConstantSpeed_Impl::addToNode(Node& node) {
      if (node.plantLoop()) {
        return StraightComponent_Impl::addToNode(node);
      }

      return false;
    }

    boost::optional<double> HeaderedPumpsConstantSpeed_Impl::totalRatedFlowRate() const {
      return getDouble(openstudio::HeaderedPumps_ConstantSpeedFields::TotalDesignFlowRate, true);
    }

    bool HeaderedPumpsConstantSpeed_Impl::isTotalRatedFlowRateAutosized() const {
      if (const auto value = getString(openstudio::HeaderedPumps_ConstantSpeedFields::TotalDesignFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    int HeaderedPumpsConstantSpeed_Impl::numberofPumpsinBank() const {
      const auto value = getInt(openstudio::HeaderedPumps_ConstantSpeedFields::NumberofPumpsinBank, true);
      OS_ASSERT(value);
      return *value;
    }

    std::string HeaderedPumpsConstantSpeed_Impl::flowSequencingControlScheme() const {
      const auto value = getString(openstudio::HeaderedPumps_ConstantSpeedFields::FlowSequencingControlScheme, true);
      OS_ASSERT(value);
      return *value;
    }

    double HeaderedPumpsConstantSpeed_Impl::ratedPumpHead() const {
      const auto value = getDouble(openstudio::HeaderedPumps_ConstantSpeedFields::DesignPumpHead, true);
      OS_ASSERT(value);
      return *value;
    }

    boost::optional<double> HeaderedPumpsConstantSpeed_Impl::ratedPowerConsumption() const {
      return getDouble(openstudio::HeaderedPumps_ConstantSpeedFields::DesignPowerConsumption, true);
    }

    bool HeaderedPumpsConstantSpeed_Impl::isRatedPowerConsumptionAutosized() const {
      if (const auto value = getString(openstudio::HeaderedPumps_ConstantSpeedFields::DesignPowerConsumption, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    double HeaderedPumpsConstantSpeed_Impl::motorEfficiency() const {
      const auto value = getDouble(openstudio::HeaderedPumps_ConstantSpeedFields::MotorEfficiency, true);
      OS_ASSERT(value);
      return *value;
    }

    double HeaderedPumpsConstantSpeed_Impl::fractionofMotorInefficienciestoFluidStream() const {
      const auto value = getDouble(openstudio::HeaderedPumps_ConstantSpeedFields::FractionofMotorInefficienciestoFluidStream, true);
      OS_ASSERT(value);
      return *value;
    }

    std::string HeaderedPumpsConstantSpeed_Impl::pumpControlType() const {
      const auto value = getString(openstudio::HeaderedPumps_ConstantSpeedFields::PumpControlType, true);
      OS_ASSERT(value);
      return *value;
    }

    double HeaderedPumpsConstantSpeed_Impl::skinLossRadiativeFraction() const {
      const auto value = getDouble(openstudio::HeaderedPumps_ConstantSpeedFields::SkinLossRadiativeFraction, true);
      OS_ASSERT(value);
      return *value;
    }

    std::string HeaderedPumpsConstantSpeed_Impl::designPowerSizingMethod() const {
      const auto value = getString(openstudio::HeaderedPumps_ConstantSpeedFields::DesignPowerSizingMethod, true);
      OS_ASSERT(value);
      return *value;
    }

    double HeaderedPumpsConstantSpeed_Impl::designElectricPowerPerUnitFlowRate() const {
      const auto value = getDouble(openstudio::HeaderedPumps_ConstantSpeedFields::DesignElectricPowerperUnitFlowRate, true);
      OS_ASSERT(value);
      return *value;
    }

    double HeaderedPumpsConstantSpeed_Impl::designShaftPowerPerUnitFlowRatePerUnitHead() const {
      const auto value = getDouble(openstudio::HeaderedPumps_ConstantSpeedFields::DesignShaftPowerperUnitFlowRateperUnitHead, true);
      OS_ASSERT(value);
      return *value;
    }

    std::string HeaderedPumpsConstantSpeed_Impl::endUseSubcategory() const {
      const auto value = getString(openstudio::HeaderedPumps_ConstantSpeedFields::EndUseSubcategory, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HeaderedPumpsConstantSpeed_Impl::setTotalRatedFlowRate(double totalRatedFlowRate) {
      return setDouble(openstudio::HeaderedPumps_ConstantSpeedFields::TotalDesignFlowRate, totalRatedFlowRate);
    }

    void HeaderedPumpsConstantSpeed_Impl::autosizeTotalRatedFlowRate() {
      const bool result = setString(openstudio::HeaderedPumps_ConstantSpeedFields::TotalDesignFlowRate, "Autosize");
      OS_ASSERT(result);
    }

    bool HeaderedPumpsConstantSpeed_Impl::setNumberofPumpsinBank(int numberofPumpsinBank) {
      const bool result = setInt(openstudio::HeaderedPumps_ConstantSpeedFields::NumberofPumpsinBank, numberofPumpsinBank);
      OS_ASSERT(result);
      return result;
    }

    bool HeaderedPumpsConstantSpeed_Impl::setFlowSequencingControlScheme(const std::string& flowSequencingControlScheme) {
      return setString(openstudio::HeaderedPumps_ConstantSpeedFields::FlowSequencingControlScheme, flowSequencingControlScheme);
    }

    bool HeaderedPumpsConstantSpeed_Impl::setRatedPumpHead(double ratedPumpHead) {
      const bool result = setDouble(openstudio::HeaderedPumps_ConstantSpeedFields::DesignPumpHead, ratedPumpHead);
      OS_ASSERT(result);
      return result;
    }

    bool HeaderedPumpsConstantSpeed_Impl::setRatedPowerConsumption(double ratedPowerConsumption) {
      const bool result = setDouble(openstudio::HeaderedPumps_ConstantSpeedFields::DesignPowerConsumption, ratedPowerConsumption);
      OS_ASSERT(result);
      return result;
    }

    void HeaderedPumpsConstantSpeed_Impl::autosizeRatedPowerConsumption() {
      const bool result = setString(openstudio::HeaderedPumps_ConstantSpeedFields::DesignPowerConsumption, "Autosize");
      OS_ASSERT(result);
    }

    bool HeaderedPumpsConstantSpeed_Impl::setMotorEfficiency(double motorEfficiency) {
      return setDouble(openstudio::HeaderedPumps_ConstantSpeedFields::MotorEfficiency, motorEfficiency);
    }

    bool HeaderedPumpsConstantSpeed_Impl::setFractionofMotorInefficienciestoFluidStream(double fractionofMotorInefficienciestoFluidStream) {
      return setDouble(openstudio::HeaderedPumps_ConstantSpeedFields::FractionofMotorInefficienciestoFluidStream,
                       fractionofMotorInefficienciestoFluidStream);
    }

    bool HeaderedPumpsConstantSpeed_Impl::setPumpControlType(const std::string& pumpControlType) {
      return setString(openstudio::HeaderedPumps_ConstantSpeedFields::PumpControlType, pumpControlType);
    }

    bool HeaderedPumpsConstantSpeed_Impl::setSkinLossRadiativeFraction(double skinLossRadiativeFraction) {
      return setDouble(openstudio::HeaderedPumps_ConstantSpeedFields::SkinLossRadiativeFraction, skinLossRadiativeFraction);
    }

    bool HeaderedPumpsConstantSpeed_Impl::setDesignPowerSizingMethod(const std::string& designPowerSizingMethod) {
      return setString(openstudio::HeaderedPumps_ConstantSpeedFields::DesignPowerSizingMethod, designPowerSizingMethod);
    }

    bool HeaderedPumpsConstantSpeed_Impl::setDesignElectricPowerPerUnitFlowRate(double designElectricPowerPerUnitFlowRate) {
      return setDouble(openstudio::HeaderedPumps_ConstantSpeedFields::DesignElectricPowerperUnitFlowRate, designElectricPowerPerUnitFlowRate);
    }

    bool HeaderedPumpsConstantSpeed_Impl::setDesignShaftPowerPerUnitFlowRatePerUnitHead(double designShaftPowerPerUnitFlowRatePerUnitHead) {
      return setDouble(openstudio::HeaderedPumps_ConstantSpeedFields::DesignShaftPowerperUnitFlowRateperUnitHead,
                       designShaftPowerPerUnitFlowRatePerUnitHead);
    }

    bool HeaderedPumpsConstantSpeed_Impl::setEndUseSubcategory(const std::string& endUseSubcategory) {
      return setString(openstudio::HeaderedPumps_ConstantSpeedFields::EndUseSubcategory, endUseSubcategory);
    }

    boost::optional<double> HeaderedPumpsConstantSpeed_Impl::autosizedTotalRatedFlowRate() const {
      // epmodel does not currently resolve autosized values from SQL results.
      return boost::none;
    }

    boost::optional<double> HeaderedPumpsConstantSpeed_Impl::autosizedRatedPowerConsumption() const {
      // epmodel does not currently resolve autosized values from SQL results.
      return boost::none;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
