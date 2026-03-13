/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/EvaporativeCoolerIndirectResearchSpecial.hpp"
#include "StraightComponent/EvaporativeCoolerIndirectResearchSpecial_Impl.hpp"

#include "HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "Loop/AirLoopHVAC.hpp"
#include "StraightComponent/Node.hpp"
#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/EvaporativeCooler_Indirect_ResearchSpecial_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  EvaporativeCoolerIndirectResearchSpecial::EvaporativeCoolerIndirectResearchSpecial(const Model& model)
    : StraightComponent(EvaporativeCoolerIndirectResearchSpecial::iddObjectType(), model) {
    setCoolerMaximumEffectiveness(0.75);
    setRecirculatingWaterPumpPowerConsumption(30.0);
    setSecondaryFanTotalEfficiency(0.6);
    setSecondaryFanDeltaPressure(124.6);
    setDewpointEffectivenessFactor(0.9);
    setDriftLossFraction(0.0);
    setWaterPumpPowerSizingFactor(0.1);
    setSecondaryAirFlowScalingFactor(1.0);
    resetBlowdownConcentrationRatio();
  }

  EvaporativeCoolerIndirectResearchSpecial::EvaporativeCoolerIndirectResearchSpecial(
    std::shared_ptr<detail::EvaporativeCoolerIndirectResearchSpecial_Impl> impl)
    : StraightComponent(std::move(impl)) {}

  IddObjectType EvaporativeCoolerIndirectResearchSpecial::iddObjectType() {
    return IddObjectType::EvaporativeCooler_Indirect_ResearchSpecial;
  }

  double EvaporativeCoolerIndirectResearchSpecial::coolerMaximumEffectiveness() const {
    return getImpl<detail::EvaporativeCoolerIndirectResearchSpecial_Impl>()->coolerMaximumEffectiveness();
  }

  bool EvaporativeCoolerIndirectResearchSpecial::setCoolerMaximumEffectiveness(double coolerMaximumEffectiveness) {
    return getImpl<detail::EvaporativeCoolerIndirectResearchSpecial_Impl>()->setCoolerMaximumEffectiveness(coolerMaximumEffectiveness);
  }

  boost::optional<double> EvaporativeCoolerIndirectResearchSpecial::recirculatingWaterPumpPowerConsumption() const {
    return getImpl<detail::EvaporativeCoolerIndirectResearchSpecial_Impl>()->recirculatingWaterPumpPowerConsumption();
  }

  bool EvaporativeCoolerIndirectResearchSpecial::isRecirculatingWaterPumpPowerConsumptionAutosized() const {
    return getImpl<detail::EvaporativeCoolerIndirectResearchSpecial_Impl>()->isRecirculatingWaterPumpPowerConsumptionAutosized();
  }

  bool EvaporativeCoolerIndirectResearchSpecial::setRecirculatingWaterPumpPowerConsumption(double recirculatingWaterPumpPowerConsumption) {
    return getImpl<detail::EvaporativeCoolerIndirectResearchSpecial_Impl>()->setRecirculatingWaterPumpPowerConsumption(
      recirculatingWaterPumpPowerConsumption);
  }

  void EvaporativeCoolerIndirectResearchSpecial::autosizeRecirculatingWaterPumpPowerConsumption() {
    getImpl<detail::EvaporativeCoolerIndirectResearchSpecial_Impl>()->autosizeRecirculatingWaterPumpPowerConsumption();
  }

  boost::optional<double> EvaporativeCoolerIndirectResearchSpecial::autosizedRecirculatingWaterPumpPowerConsumption() const {
    return getImpl<detail::EvaporativeCoolerIndirectResearchSpecial_Impl>()->autosizedRecirculatingWaterPumpPowerConsumption();
  }

  boost::optional<double> EvaporativeCoolerIndirectResearchSpecial::secondaryFanFlowRate() const {
    return getImpl<detail::EvaporativeCoolerIndirectResearchSpecial_Impl>()->secondaryFanFlowRate();
  }

  bool EvaporativeCoolerIndirectResearchSpecial::isSecondaryFanFlowRateAutosized() const {
    return getImpl<detail::EvaporativeCoolerIndirectResearchSpecial_Impl>()->isSecondaryFanFlowRateAutosized();
  }

  bool EvaporativeCoolerIndirectResearchSpecial::setSecondaryFanFlowRate(double secondaryFanFlowRate) {
    return getImpl<detail::EvaporativeCoolerIndirectResearchSpecial_Impl>()->setSecondaryFanFlowRate(secondaryFanFlowRate);
  }

  void EvaporativeCoolerIndirectResearchSpecial::resetSecondaryFanFlowRate() {
    getImpl<detail::EvaporativeCoolerIndirectResearchSpecial_Impl>()->resetSecondaryFanFlowRate();
  }

  void EvaporativeCoolerIndirectResearchSpecial::autosizeSecondaryFanFlowRate() {
    getImpl<detail::EvaporativeCoolerIndirectResearchSpecial_Impl>()->autosizeSecondaryFanFlowRate();
  }

  boost::optional<double> EvaporativeCoolerIndirectResearchSpecial::autosizedSecondaryFanFlowRate() const {
    return getImpl<detail::EvaporativeCoolerIndirectResearchSpecial_Impl>()->autosizedSecondaryFanFlowRate();
  }

  double EvaporativeCoolerIndirectResearchSpecial::secondaryFanTotalEfficiency() const {
    return getImpl<detail::EvaporativeCoolerIndirectResearchSpecial_Impl>()->secondaryFanTotalEfficiency();
  }

  bool EvaporativeCoolerIndirectResearchSpecial::setSecondaryFanTotalEfficiency(double secondaryFanTotalEfficiency) {
    return getImpl<detail::EvaporativeCoolerIndirectResearchSpecial_Impl>()->setSecondaryFanTotalEfficiency(secondaryFanTotalEfficiency);
  }

  double EvaporativeCoolerIndirectResearchSpecial::secondaryFanDeltaPressure() const {
    return getImpl<detail::EvaporativeCoolerIndirectResearchSpecial_Impl>()->secondaryFanDeltaPressure();
  }

  bool EvaporativeCoolerIndirectResearchSpecial::setSecondaryFanDeltaPressure(double secondaryFanDeltaPressure) {
    return getImpl<detail::EvaporativeCoolerIndirectResearchSpecial_Impl>()->setSecondaryFanDeltaPressure(secondaryFanDeltaPressure);
  }

  double EvaporativeCoolerIndirectResearchSpecial::dewpointEffectivenessFactor() const {
    return getImpl<detail::EvaporativeCoolerIndirectResearchSpecial_Impl>()->dewpointEffectivenessFactor();
  }

  bool EvaporativeCoolerIndirectResearchSpecial::setDewpointEffectivenessFactor(double dewpointEffectivenessFactor) {
    return getImpl<detail::EvaporativeCoolerIndirectResearchSpecial_Impl>()->setDewpointEffectivenessFactor(dewpointEffectivenessFactor);
  }

  boost::optional<double> EvaporativeCoolerIndirectResearchSpecial::driftLossFraction() const {
    return getImpl<detail::EvaporativeCoolerIndirectResearchSpecial_Impl>()->driftLossFraction();
  }

  bool EvaporativeCoolerIndirectResearchSpecial::setDriftLossFraction(double driftLossFraction) {
    return getImpl<detail::EvaporativeCoolerIndirectResearchSpecial_Impl>()->setDriftLossFraction(driftLossFraction);
  }

  void EvaporativeCoolerIndirectResearchSpecial::resetDriftLossFraction() {
    getImpl<detail::EvaporativeCoolerIndirectResearchSpecial_Impl>()->resetDriftLossFraction();
  }

  boost::optional<double> EvaporativeCoolerIndirectResearchSpecial::blowdownConcentrationRatio() const {
    return getImpl<detail::EvaporativeCoolerIndirectResearchSpecial_Impl>()->blowdownConcentrationRatio();
  }

  bool EvaporativeCoolerIndirectResearchSpecial::setBlowdownConcentrationRatio(double blowdownConcentrationRatio) {
    return getImpl<detail::EvaporativeCoolerIndirectResearchSpecial_Impl>()->setBlowdownConcentrationRatio(blowdownConcentrationRatio);
  }

  void EvaporativeCoolerIndirectResearchSpecial::resetBlowdownConcentrationRatio() {
    getImpl<detail::EvaporativeCoolerIndirectResearchSpecial_Impl>()->resetBlowdownConcentrationRatio();
  }

  boost::optional<double> EvaporativeCoolerIndirectResearchSpecial::coolerDrybulbDesignEffectiveness() const {
    return getImpl<detail::EvaporativeCoolerIndirectResearchSpecial_Impl>()->coolerDrybulbDesignEffectiveness();
  }

  bool EvaporativeCoolerIndirectResearchSpecial::setCoolerDrybulbDesignEffectiveness(double coolerDrybulbDesignEffectiveness) {
    return getImpl<detail::EvaporativeCoolerIndirectResearchSpecial_Impl>()->setCoolerDrybulbDesignEffectiveness(coolerDrybulbDesignEffectiveness);
  }

  void EvaporativeCoolerIndirectResearchSpecial::resetCoolerDrybulbDesignEffectiveness() {
    getImpl<detail::EvaporativeCoolerIndirectResearchSpecial_Impl>()->resetCoolerDrybulbDesignEffectiveness();
  }

  double EvaporativeCoolerIndirectResearchSpecial::waterPumpPowerSizingFactor() const {
    return getImpl<detail::EvaporativeCoolerIndirectResearchSpecial_Impl>()->waterPumpPowerSizingFactor();
  }

  bool EvaporativeCoolerIndirectResearchSpecial::setWaterPumpPowerSizingFactor(double waterPumpPowerSizingFactor) {
    return getImpl<detail::EvaporativeCoolerIndirectResearchSpecial_Impl>()->setWaterPumpPowerSizingFactor(waterPumpPowerSizingFactor);
  }

  double EvaporativeCoolerIndirectResearchSpecial::secondaryAirFlowScalingFactor() const {
    return getImpl<detail::EvaporativeCoolerIndirectResearchSpecial_Impl>()->secondaryAirFlowScalingFactor();
  }

  bool EvaporativeCoolerIndirectResearchSpecial::setSecondaryAirFlowScalingFactor(double secondaryAirFlowScalingFactor) {
    return getImpl<detail::EvaporativeCoolerIndirectResearchSpecial_Impl>()->setSecondaryAirFlowScalingFactor(secondaryAirFlowScalingFactor);
  }

  boost::optional<double> EvaporativeCoolerIndirectResearchSpecial::secondaryAirFanDesignPower() const {
    return getImpl<detail::EvaporativeCoolerIndirectResearchSpecial_Impl>()->secondaryAirFanDesignPower();
  }

  bool EvaporativeCoolerIndirectResearchSpecial::isSecondaryAirFanDesignPowerAutosized() const {
    return getImpl<detail::EvaporativeCoolerIndirectResearchSpecial_Impl>()->isSecondaryAirFanDesignPowerAutosized();
  }

  bool EvaporativeCoolerIndirectResearchSpecial::setSecondaryAirFanDesignPower(double secondaryAirFanDesignPower) {
    return getImpl<detail::EvaporativeCoolerIndirectResearchSpecial_Impl>()->setSecondaryAirFanDesignPower(secondaryAirFanDesignPower);
  }

  void EvaporativeCoolerIndirectResearchSpecial::autosizeSecondaryAirFanDesignPower() {
    getImpl<detail::EvaporativeCoolerIndirectResearchSpecial_Impl>()->autosizeSecondaryAirFanDesignPower();
  }

  boost::optional<double> EvaporativeCoolerIndirectResearchSpecial::autosizedSecondaryAirFanDesignPower() const {
    return getImpl<detail::EvaporativeCoolerIndirectResearchSpecial_Impl>()->autosizedSecondaryAirFanDesignPower();
  }

  boost::optional<double> EvaporativeCoolerIndirectResearchSpecial::primaryDesignAirFlowRate() const {
    return getImpl<detail::EvaporativeCoolerIndirectResearchSpecial_Impl>()->primaryDesignAirFlowRate();
  }

  bool EvaporativeCoolerIndirectResearchSpecial::isPrimaryDesignAirFlowRateAutosized() const {
    return getImpl<detail::EvaporativeCoolerIndirectResearchSpecial_Impl>()->isPrimaryDesignAirFlowRateAutosized();
  }

  bool EvaporativeCoolerIndirectResearchSpecial::setPrimaryDesignAirFlowRate(double primaryDesignAirFlowRate) {
    return getImpl<detail::EvaporativeCoolerIndirectResearchSpecial_Impl>()->setPrimaryDesignAirFlowRate(primaryDesignAirFlowRate);
  }

  void EvaporativeCoolerIndirectResearchSpecial::resetPrimaryDesignAirFlowRate() {
    getImpl<detail::EvaporativeCoolerIndirectResearchSpecial_Impl>()->resetPrimaryDesignAirFlowRate();
  }

  void EvaporativeCoolerIndirectResearchSpecial::autosizePrimaryDesignAirFlowRate() {
    getImpl<detail::EvaporativeCoolerIndirectResearchSpecial_Impl>()->autosizePrimaryDesignAirFlowRate();
  }

  boost::optional<double> EvaporativeCoolerIndirectResearchSpecial::autosizedPrimaryDesignAirFlowRate() const {
    return getImpl<detail::EvaporativeCoolerIndirectResearchSpecial_Impl>()->autosizedPrimaryDesignAirFlowRate();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    bool EvaporativeCoolerIndirectResearchSpecial_Impl::addToNode(Node& node) {
      auto airLoop = node.airLoopHVAC();

      if (!(airLoop && airLoop->supplyComponent(node.handle()))) {
        return false;
      }

      return StraightComponent_Impl::addToNode(node);
    }

    unsigned EvaporativeCoolerIndirectResearchSpecial_Impl::inletPort() const {
      return openstudio::EvaporativeCooler_Indirect_ResearchSpecialFields::PrimaryAirInletNodeName;
    }

    unsigned EvaporativeCoolerIndirectResearchSpecial_Impl::outletPort() const {
      return openstudio::EvaporativeCooler_Indirect_ResearchSpecialFields::PrimaryAirOutletNodeName;
    }

    double EvaporativeCoolerIndirectResearchSpecial_Impl::coolerMaximumEffectiveness() const {
      const auto value = getDouble(openstudio::EvaporativeCooler_Indirect_ResearchSpecialFields::CoolerWetbulbDesignEffectiveness, true);
      OS_ASSERT(value);
      return *value;
    }

    bool EvaporativeCoolerIndirectResearchSpecial_Impl::setCoolerMaximumEffectiveness(double coolerMaximumEffectiveness) {
      return setDouble(openstudio::EvaporativeCooler_Indirect_ResearchSpecialFields::CoolerWetbulbDesignEffectiveness, coolerMaximumEffectiveness);
    }

    boost::optional<double> EvaporativeCoolerIndirectResearchSpecial_Impl::recirculatingWaterPumpPowerConsumption() const {
      return getDouble(openstudio::EvaporativeCooler_Indirect_ResearchSpecialFields::RecirculatingWaterPumpDesignPower, true);
    }

    bool EvaporativeCoolerIndirectResearchSpecial_Impl::isRecirculatingWaterPumpPowerConsumptionAutosized() const {
      if (const auto value = getString(openstudio::EvaporativeCooler_Indirect_ResearchSpecialFields::RecirculatingWaterPumpDesignPower, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool EvaporativeCoolerIndirectResearchSpecial_Impl::setRecirculatingWaterPumpPowerConsumption(double recirculatingWaterPumpPowerConsumption) {
      const bool result = setDouble(openstudio::EvaporativeCooler_Indirect_ResearchSpecialFields::RecirculatingWaterPumpDesignPower,
                                    recirculatingWaterPumpPowerConsumption);
      OS_ASSERT(result);
      return result;
    }

    void EvaporativeCoolerIndirectResearchSpecial_Impl::autosizeRecirculatingWaterPumpPowerConsumption() {
      OS_ASSERT(setString(openstudio::EvaporativeCooler_Indirect_ResearchSpecialFields::RecirculatingWaterPumpDesignPower, "Autosize"));
    }

    boost::optional<double> EvaporativeCoolerIndirectResearchSpecial_Impl::autosizedRecirculatingWaterPumpPowerConsumption() const {
      // epmodel does not currently resolve autosized values from SQL results.
      return boost::none;
    }

    boost::optional<double> EvaporativeCoolerIndirectResearchSpecial_Impl::secondaryFanFlowRate() const {
      return getDouble(openstudio::EvaporativeCooler_Indirect_ResearchSpecialFields::SecondaryAirDesignFlowRate, true);
    }

    bool EvaporativeCoolerIndirectResearchSpecial_Impl::isSecondaryFanFlowRateAutosized() const {
      if (const auto value = getString(openstudio::EvaporativeCooler_Indirect_ResearchSpecialFields::SecondaryAirDesignFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool EvaporativeCoolerIndirectResearchSpecial_Impl::setSecondaryFanFlowRate(double secondaryFanFlowRate) {
      return setDouble(openstudio::EvaporativeCooler_Indirect_ResearchSpecialFields::SecondaryAirDesignFlowRate, secondaryFanFlowRate);
    }

    void EvaporativeCoolerIndirectResearchSpecial_Impl::resetSecondaryFanFlowRate() {
      OS_ASSERT(setString(openstudio::EvaporativeCooler_Indirect_ResearchSpecialFields::SecondaryAirDesignFlowRate, ""));
    }

    void EvaporativeCoolerIndirectResearchSpecial_Impl::autosizeSecondaryFanFlowRate() {
      OS_ASSERT(setString(openstudio::EvaporativeCooler_Indirect_ResearchSpecialFields::SecondaryAirDesignFlowRate, "Autosize"));
    }

    boost::optional<double> EvaporativeCoolerIndirectResearchSpecial_Impl::autosizedSecondaryFanFlowRate() const {
      // epmodel does not currently resolve autosized values from SQL results.
      return boost::none;
    }

    double EvaporativeCoolerIndirectResearchSpecial_Impl::secondaryFanTotalEfficiency() const {
      const auto value = getDouble(openstudio::EvaporativeCooler_Indirect_ResearchSpecialFields::SecondaryAirFanSizingSpecificPower, true);
      OS_ASSERT(value);
      return *value;
    }

    bool EvaporativeCoolerIndirectResearchSpecial_Impl::setSecondaryFanTotalEfficiency(double secondaryFanTotalEfficiency) {
      return setDouble(openstudio::EvaporativeCooler_Indirect_ResearchSpecialFields::SecondaryAirFanSizingSpecificPower, secondaryFanTotalEfficiency);
    }

    double EvaporativeCoolerIndirectResearchSpecial_Impl::secondaryFanDeltaPressure() const {
      const auto value = getDouble(openstudio::EvaporativeCooler_Indirect_ResearchSpecialFields::SecondaryAirFanSizingSpecificPower, true);
      OS_ASSERT(value);
      return *value;
    }

    bool EvaporativeCoolerIndirectResearchSpecial_Impl::setSecondaryFanDeltaPressure(double secondaryFanDeltaPressure) {
      return setDouble(openstudio::EvaporativeCooler_Indirect_ResearchSpecialFields::SecondaryAirFanSizingSpecificPower, secondaryFanDeltaPressure);
    }

    double EvaporativeCoolerIndirectResearchSpecial_Impl::dewpointEffectivenessFactor() const {
      const auto value = getDouble(openstudio::EvaporativeCooler_Indirect_ResearchSpecialFields::DewpointEffectivenessFactor, true);
      OS_ASSERT(value);
      return *value;
    }

    bool EvaporativeCoolerIndirectResearchSpecial_Impl::setDewpointEffectivenessFactor(double dewpointEffectivenessFactor) {
      const bool result =
        setDouble(openstudio::EvaporativeCooler_Indirect_ResearchSpecialFields::DewpointEffectivenessFactor, dewpointEffectivenessFactor);
      OS_ASSERT(result);
      return result;
    }

    boost::optional<double> EvaporativeCoolerIndirectResearchSpecial_Impl::driftLossFraction() const {
      return getDouble(openstudio::EvaporativeCooler_Indirect_ResearchSpecialFields::DriftLossFraction, true);
    }

    bool EvaporativeCoolerIndirectResearchSpecial_Impl::setDriftLossFraction(double driftLossFraction) {
      return setDouble(openstudio::EvaporativeCooler_Indirect_ResearchSpecialFields::DriftLossFraction, driftLossFraction);
    }

    void EvaporativeCoolerIndirectResearchSpecial_Impl::resetDriftLossFraction() {
      OS_ASSERT(setString(openstudio::EvaporativeCooler_Indirect_ResearchSpecialFields::DriftLossFraction, ""));
    }

    boost::optional<double> EvaporativeCoolerIndirectResearchSpecial_Impl::blowdownConcentrationRatio() const {
      return getDouble(openstudio::EvaporativeCooler_Indirect_ResearchSpecialFields::BlowdownConcentrationRatio, true);
    }

    bool EvaporativeCoolerIndirectResearchSpecial_Impl::setBlowdownConcentrationRatio(double blowdownConcentrationRatio) {
      return setDouble(openstudio::EvaporativeCooler_Indirect_ResearchSpecialFields::BlowdownConcentrationRatio, blowdownConcentrationRatio);
    }

    void EvaporativeCoolerIndirectResearchSpecial_Impl::resetBlowdownConcentrationRatio() {
      OS_ASSERT(setString(openstudio::EvaporativeCooler_Indirect_ResearchSpecialFields::BlowdownConcentrationRatio, ""));
    }

    boost::optional<double> EvaporativeCoolerIndirectResearchSpecial_Impl::coolerDrybulbDesignEffectiveness() const {
      return getDouble(openstudio::EvaporativeCooler_Indirect_ResearchSpecialFields::CoolerDrybulbDesignEffectiveness, true);
    }

    bool EvaporativeCoolerIndirectResearchSpecial_Impl::setCoolerDrybulbDesignEffectiveness(double coolerDrybulbDesignEffectiveness) {
      return setDouble(openstudio::EvaporativeCooler_Indirect_ResearchSpecialFields::CoolerDrybulbDesignEffectiveness,
                       coolerDrybulbDesignEffectiveness);
    }

    void EvaporativeCoolerIndirectResearchSpecial_Impl::resetCoolerDrybulbDesignEffectiveness() {
      OS_ASSERT(setString(openstudio::EvaporativeCooler_Indirect_ResearchSpecialFields::CoolerDrybulbDesignEffectiveness, ""));
    }

    double EvaporativeCoolerIndirectResearchSpecial_Impl::waterPumpPowerSizingFactor() const {
      const auto value = getDouble(openstudio::EvaporativeCooler_Indirect_ResearchSpecialFields::WaterPumpPowerSizingFactor, true);
      OS_ASSERT(value);
      return *value;
    }

    bool EvaporativeCoolerIndirectResearchSpecial_Impl::setWaterPumpPowerSizingFactor(double waterPumpPowerSizingFactor) {
      const bool result =
        setDouble(openstudio::EvaporativeCooler_Indirect_ResearchSpecialFields::WaterPumpPowerSizingFactor, waterPumpPowerSizingFactor);
      OS_ASSERT(result);
      return result;
    }

    double EvaporativeCoolerIndirectResearchSpecial_Impl::secondaryAirFlowScalingFactor() const {
      const auto value = getDouble(openstudio::EvaporativeCooler_Indirect_ResearchSpecialFields::SecondaryAirFlowScalingFactor, true);
      OS_ASSERT(value);
      return *value;
    }

    bool EvaporativeCoolerIndirectResearchSpecial_Impl::setSecondaryAirFlowScalingFactor(double secondaryAirFlowScalingFactor) {
      const bool result =
        setDouble(openstudio::EvaporativeCooler_Indirect_ResearchSpecialFields::SecondaryAirFlowScalingFactor, secondaryAirFlowScalingFactor);
      OS_ASSERT(result);
      return result;
    }

    boost::optional<double> EvaporativeCoolerIndirectResearchSpecial_Impl::secondaryAirFanDesignPower() const {
      return getDouble(openstudio::EvaporativeCooler_Indirect_ResearchSpecialFields::SecondaryAirFanDesignPower, true);
    }

    bool EvaporativeCoolerIndirectResearchSpecial_Impl::isSecondaryAirFanDesignPowerAutosized() const {
      if (const auto value = getString(openstudio::EvaporativeCooler_Indirect_ResearchSpecialFields::SecondaryAirFanDesignPower, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool EvaporativeCoolerIndirectResearchSpecial_Impl::setSecondaryAirFanDesignPower(double secondaryAirFanDesignPower) {
      const bool result =
        setDouble(openstudio::EvaporativeCooler_Indirect_ResearchSpecialFields::SecondaryAirFanDesignPower, secondaryAirFanDesignPower);
      OS_ASSERT(result);
      return result;
    }

    void EvaporativeCoolerIndirectResearchSpecial_Impl::autosizeSecondaryAirFanDesignPower() {
      OS_ASSERT(setString(openstudio::EvaporativeCooler_Indirect_ResearchSpecialFields::SecondaryAirFanDesignPower, "Autosize"));
    }

    boost::optional<double> EvaporativeCoolerIndirectResearchSpecial_Impl::autosizedSecondaryAirFanDesignPower() const {
      // epmodel does not currently resolve autosized values from SQL results.
      return boost::none;
    }

    boost::optional<double> EvaporativeCoolerIndirectResearchSpecial_Impl::primaryDesignAirFlowRate() const {
      return getDouble(openstudio::EvaporativeCooler_Indirect_ResearchSpecialFields::PrimaryAirDesignFlowRate, true);
    }

    bool EvaporativeCoolerIndirectResearchSpecial_Impl::isPrimaryDesignAirFlowRateAutosized() const {
      if (const auto value = getString(openstudio::EvaporativeCooler_Indirect_ResearchSpecialFields::PrimaryAirDesignFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool EvaporativeCoolerIndirectResearchSpecial_Impl::setPrimaryDesignAirFlowRate(double primaryDesignAirFlowRate) {
      return setDouble(openstudio::EvaporativeCooler_Indirect_ResearchSpecialFields::PrimaryAirDesignFlowRate, primaryDesignAirFlowRate);
    }

    void EvaporativeCoolerIndirectResearchSpecial_Impl::resetPrimaryDesignAirFlowRate() {
      OS_ASSERT(setString(openstudio::EvaporativeCooler_Indirect_ResearchSpecialFields::PrimaryAirDesignFlowRate, ""));
    }

    void EvaporativeCoolerIndirectResearchSpecial_Impl::autosizePrimaryDesignAirFlowRate() {
      OS_ASSERT(setString(openstudio::EvaporativeCooler_Indirect_ResearchSpecialFields::PrimaryAirDesignFlowRate, "Autosize"));
    }

    boost::optional<double> EvaporativeCoolerIndirectResearchSpecial_Impl::autosizedPrimaryDesignAirFlowRate() const {
      // epmodel does not currently resolve autosized values from SQL results.
      return boost::none;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
