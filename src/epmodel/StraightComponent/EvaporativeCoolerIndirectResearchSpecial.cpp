/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/EvaporativeCoolerIndirectResearchSpecial.hpp"
#include "StraightComponent/EvaporativeCoolerIndirectResearchSpecial_Impl.hpp"

#include "Curve/Curve.hpp"
#include "Curve/Curve_Impl.hpp"
#include "HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "Loop/AirLoopHVAC.hpp"
#include "Model.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"
#include "StraightComponent/Node.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/EvaporativeCooler_Indirect_ResearchSpecial_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  EvaporativeCoolerIndirectResearchSpecial::EvaporativeCoolerIndirectResearchSpecial(const Model& model)
    : StraightComponent(EvaporativeCoolerIndirectResearchSpecial::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::EvaporativeCoolerIndirectResearchSpecial_Impl>());

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

  boost::optional<Schedule> EvaporativeCoolerIndirectResearchSpecial::availabilitySchedule() const {
    return getImpl<detail::EvaporativeCoolerIndirectResearchSpecial_Impl>()->availabilitySchedule();
  }

  bool EvaporativeCoolerIndirectResearchSpecial::setAvailabilitySchedule(Schedule& schedule) {
    return getImpl<detail::EvaporativeCoolerIndirectResearchSpecial_Impl>()->setAvailabilitySchedule(schedule);
  }

  void EvaporativeCoolerIndirectResearchSpecial::resetAvailabilitySchedule() {
    getImpl<detail::EvaporativeCoolerIndirectResearchSpecial_Impl>()->resetAvailabilitySchedule();
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

  boost::optional<Curve> EvaporativeCoolerIndirectResearchSpecial::wetbulbEffectivenessFlowRatioModifierCurve() const {
    return getImpl<detail::EvaporativeCoolerIndirectResearchSpecial_Impl>()->wetbulbEffectivenessFlowRatioModifierCurve();
  }

  bool EvaporativeCoolerIndirectResearchSpecial::setWetbulbEffectivenessFlowRatioModifierCurve(const Curve& curve) {
    return getImpl<detail::EvaporativeCoolerIndirectResearchSpecial_Impl>()->setWetbulbEffectivenessFlowRatioModifierCurve(curve);
  }

  void EvaporativeCoolerIndirectResearchSpecial::resetWetbulbEffectivenessFlowRatioModifierCurve() {
    getImpl<detail::EvaporativeCoolerIndirectResearchSpecial_Impl>()->resetWetbulbEffectivenessFlowRatioModifierCurve();
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

  boost::optional<Curve> EvaporativeCoolerIndirectResearchSpecial::drybulbEffectivenessFlowRatioModifierCurve() const {
    return getImpl<detail::EvaporativeCoolerIndirectResearchSpecial_Impl>()->drybulbEffectivenessFlowRatioModifierCurve();
  }

  bool EvaporativeCoolerIndirectResearchSpecial::setDrybulbEffectivenessFlowRatioModifierCurve(const Curve& curve) {
    return getImpl<detail::EvaporativeCoolerIndirectResearchSpecial_Impl>()->setDrybulbEffectivenessFlowRatioModifierCurve(curve);
  }

  void EvaporativeCoolerIndirectResearchSpecial::resetDrybulbEffectivenessFlowRatioModifierCurve() {
    getImpl<detail::EvaporativeCoolerIndirectResearchSpecial_Impl>()->resetDrybulbEffectivenessFlowRatioModifierCurve();
  }

  double EvaporativeCoolerIndirectResearchSpecial::waterPumpPowerSizingFactor() const {
    return getImpl<detail::EvaporativeCoolerIndirectResearchSpecial_Impl>()->waterPumpPowerSizingFactor();
  }

  bool EvaporativeCoolerIndirectResearchSpecial::setWaterPumpPowerSizingFactor(double waterPumpPowerSizingFactor) {
    return getImpl<detail::EvaporativeCoolerIndirectResearchSpecial_Impl>()->setWaterPumpPowerSizingFactor(waterPumpPowerSizingFactor);
  }

  boost::optional<Curve> EvaporativeCoolerIndirectResearchSpecial::waterPumpPowerModifierCurve() const {
    return getImpl<detail::EvaporativeCoolerIndirectResearchSpecial_Impl>()->waterPumpPowerModifierCurve();
  }

  bool EvaporativeCoolerIndirectResearchSpecial::setWaterPumpPowerModifierCurve(const Curve& curve) {
    return getImpl<detail::EvaporativeCoolerIndirectResearchSpecial_Impl>()->setWaterPumpPowerModifierCurve(curve);
  }

  void EvaporativeCoolerIndirectResearchSpecial::resetWaterPumpPowerModifierCurve() {
    getImpl<detail::EvaporativeCoolerIndirectResearchSpecial_Impl>()->resetWaterPumpPowerModifierCurve();
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

  boost::optional<Curve> EvaporativeCoolerIndirectResearchSpecial::secondaryAirFanPowerModifierCurve() const {
    return getImpl<detail::EvaporativeCoolerIndirectResearchSpecial_Impl>()->secondaryAirFanPowerModifierCurve();
  }

  bool EvaporativeCoolerIndirectResearchSpecial::setSecondaryAirFanPowerModifierCurve(const Curve& curve) {
    return getImpl<detail::EvaporativeCoolerIndirectResearchSpecial_Impl>()->setSecondaryAirFanPowerModifierCurve(curve);
  }

  void EvaporativeCoolerIndirectResearchSpecial::resetSecondaryAirFanPowerModifierCurve() {
    getImpl<detail::EvaporativeCoolerIndirectResearchSpecial_Impl>()->resetSecondaryAirFanPowerModifierCurve();
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

    EvaporativeCoolerIndirectResearchSpecial_Impl::EvaporativeCoolerIndirectResearchSpecial_Impl(const IdfObject& idfObject, Model_Impl* model,
                                                                                                 bool keepHandle)
      : StraightComponent_Impl(idfObject, model, keepHandle) {
      OS_ASSERT(idfObject.iddObject().type() == EvaporativeCoolerIndirectResearchSpecial::iddObjectType());
      if (const auto specificPower =
            getDouble(openstudio::EvaporativeCooler_Indirect_ResearchSpecialFields::SecondaryAirFanSizingSpecificPower, true)) {
        m_secondaryFanTotalEfficiency = 1.0;
        m_secondaryFanDeltaPressure = *specificPower;
      }
    }

    EvaporativeCoolerIndirectResearchSpecial_Impl::EvaporativeCoolerIndirectResearchSpecial_Impl(
      const openstudio::detail::WorkspaceObject_Impl& other, Model_Impl* model, bool keepHandle)
      : StraightComponent_Impl(other, model, keepHandle) {
      OS_ASSERT(other.iddObject().type() == EvaporativeCoolerIndirectResearchSpecial::iddObjectType());
      if (const auto specificPower =
            getDouble(openstudio::EvaporativeCooler_Indirect_ResearchSpecialFields::SecondaryAirFanSizingSpecificPower, true)) {
        m_secondaryFanTotalEfficiency = 1.0;
        m_secondaryFanDeltaPressure = *specificPower;
      }
    }

    EvaporativeCoolerIndirectResearchSpecial_Impl::EvaporativeCoolerIndirectResearchSpecial_Impl(
      const EvaporativeCoolerIndirectResearchSpecial_Impl& other, Model_Impl* model, bool keepHandle)
      : StraightComponent_Impl(other, model, keepHandle),
        m_secondaryFanTotalEfficiency(other.m_secondaryFanTotalEfficiency),
        m_secondaryFanDeltaPressure(other.m_secondaryFanDeltaPressure) {}

    bool EvaporativeCoolerIndirectResearchSpecial_Impl::addToNode(Node& node) {
      if (node.airLoopHVACOutdoorAirSystem()) {
        if (StraightComponent_Impl::addToNode(node)) {
          if (auto outletNode = outletModelObject()->optionalCast<Node>()) {
            return setPointer(openstudio::EvaporativeCooler_Indirect_ResearchSpecialFields::SensorNodeName, outletNode->handle(), false);
          }
          return true;
        }
        return false;
      }

      auto airLoop = node.airLoopHVAC();
      if (!(airLoop && airLoop->supplyComponent(node.handle()))) {
        return false;
      }

      if (StraightComponent_Impl::addToNode(node)) {
        if (auto outletNode = outletModelObject()->optionalCast<Node>()) {
          return setPointer(openstudio::EvaporativeCooler_Indirect_ResearchSpecialFields::SensorNodeName, outletNode->handle(), false);
        }
        return true;
      }

      return false;
    }

    unsigned EvaporativeCoolerIndirectResearchSpecial_Impl::inletPort() const {
      return openstudio::EvaporativeCooler_Indirect_ResearchSpecialFields::PrimaryAirInletNodeName;
    }

    unsigned EvaporativeCoolerIndirectResearchSpecial_Impl::outletPort() const {
      return openstudio::EvaporativeCooler_Indirect_ResearchSpecialFields::PrimaryAirOutletNodeName;
    }

    boost::optional<Schedule> EvaporativeCoolerIndirectResearchSpecial_Impl::availabilitySchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(
        openstudio::EvaporativeCooler_Indirect_ResearchSpecialFields::AvailabilityScheduleName);
    }

    bool EvaporativeCoolerIndirectResearchSpecial_Impl::setAvailabilitySchedule(Schedule& schedule) {
      return ModelObject_Impl::setSchedule(openstudio::EvaporativeCooler_Indirect_ResearchSpecialFields::AvailabilityScheduleName,
                                           "EvaporativeCoolerIndirectResearchSpecial", "Availability", schedule);
    }

    void EvaporativeCoolerIndirectResearchSpecial_Impl::resetAvailabilitySchedule() {
      OS_ASSERT(setString(openstudio::EvaporativeCooler_Indirect_ResearchSpecialFields::AvailabilityScheduleName, ""));
    }

    bool EvaporativeCoolerIndirectResearchSpecial_Impl::setReliefAirInletNode(const Node& node) {
      return setPointer(openstudio::EvaporativeCooler_Indirect_ResearchSpecialFields::ReliefAirInletNodeName, node.handle(), false);
    }

    boost::optional<Node> EvaporativeCoolerIndirectResearchSpecial_Impl::reliefAirInletNode() const {
      return resolvedNodeTarget(openstudio::EvaporativeCooler_Indirect_ResearchSpecialFields::ReliefAirInletNodeName);
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
      return boost::none;
    }

    double EvaporativeCoolerIndirectResearchSpecial_Impl::secondaryFanTotalEfficiency() const {
      return m_secondaryFanTotalEfficiency;
    }

    bool EvaporativeCoolerIndirectResearchSpecial_Impl::setSecondaryFanTotalEfficiency(double secondaryFanTotalEfficiency) {
      m_secondaryFanTotalEfficiency = secondaryFanTotalEfficiency;
      return syncSecondaryAirFanSizingSpecificPower();
    }

    double EvaporativeCoolerIndirectResearchSpecial_Impl::secondaryFanDeltaPressure() const {
      return m_secondaryFanDeltaPressure;
    }

    bool EvaporativeCoolerIndirectResearchSpecial_Impl::setSecondaryFanDeltaPressure(double secondaryFanDeltaPressure) {
      m_secondaryFanDeltaPressure = secondaryFanDeltaPressure;
      return syncSecondaryAirFanSizingSpecificPower();
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
      return getDouble(openstudio::EvaporativeCooler_Indirect_ResearchSpecialFields::DriftLossFraction, false);
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

    boost::optional<Curve> EvaporativeCoolerIndirectResearchSpecial_Impl::wetbulbEffectivenessFlowRatioModifierCurve() const {
      return getObject<ModelObject>().getModelObjectTarget<Curve>(
        openstudio::EvaporativeCooler_Indirect_ResearchSpecialFields::WetbulbEffectivenessFlowRatioModifierCurveName);
    }

    bool EvaporativeCoolerIndirectResearchSpecial_Impl::setWetbulbEffectivenessFlowRatioModifierCurve(const Curve& curve) {
      return setPointer(openstudio::EvaporativeCooler_Indirect_ResearchSpecialFields::WetbulbEffectivenessFlowRatioModifierCurveName, curve.handle());
    }

    void EvaporativeCoolerIndirectResearchSpecial_Impl::resetWetbulbEffectivenessFlowRatioModifierCurve() {
      OS_ASSERT(setString(openstudio::EvaporativeCooler_Indirect_ResearchSpecialFields::WetbulbEffectivenessFlowRatioModifierCurveName, ""));
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

    boost::optional<Curve> EvaporativeCoolerIndirectResearchSpecial_Impl::drybulbEffectivenessFlowRatioModifierCurve() const {
      return getObject<ModelObject>().getModelObjectTarget<Curve>(
        openstudio::EvaporativeCooler_Indirect_ResearchSpecialFields::DrybulbEffectivenessFlowRatioModifierCurveName);
    }

    bool EvaporativeCoolerIndirectResearchSpecial_Impl::setDrybulbEffectivenessFlowRatioModifierCurve(const Curve& curve) {
      return setPointer(openstudio::EvaporativeCooler_Indirect_ResearchSpecialFields::DrybulbEffectivenessFlowRatioModifierCurveName, curve.handle());
    }

    void EvaporativeCoolerIndirectResearchSpecial_Impl::resetDrybulbEffectivenessFlowRatioModifierCurve() {
      OS_ASSERT(setString(openstudio::EvaporativeCooler_Indirect_ResearchSpecialFields::DrybulbEffectivenessFlowRatioModifierCurveName, ""));
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

    boost::optional<Curve> EvaporativeCoolerIndirectResearchSpecial_Impl::waterPumpPowerModifierCurve() const {
      return getObject<ModelObject>().getModelObjectTarget<Curve>(
        openstudio::EvaporativeCooler_Indirect_ResearchSpecialFields::WaterPumpPowerModifierCurveName);
    }

    bool EvaporativeCoolerIndirectResearchSpecial_Impl::setWaterPumpPowerModifierCurve(const Curve& curve) {
      return setPointer(openstudio::EvaporativeCooler_Indirect_ResearchSpecialFields::WaterPumpPowerModifierCurveName, curve.handle());
    }

    void EvaporativeCoolerIndirectResearchSpecial_Impl::resetWaterPumpPowerModifierCurve() {
      OS_ASSERT(setString(openstudio::EvaporativeCooler_Indirect_ResearchSpecialFields::WaterPumpPowerModifierCurveName, ""));
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
      return boost::none;
    }

    boost::optional<Curve> EvaporativeCoolerIndirectResearchSpecial_Impl::secondaryAirFanPowerModifierCurve() const {
      return getObject<ModelObject>().getModelObjectTarget<Curve>(
        openstudio::EvaporativeCooler_Indirect_ResearchSpecialFields::SecondaryAirFanPowerModifierCurveName);
    }

    bool EvaporativeCoolerIndirectResearchSpecial_Impl::setSecondaryAirFanPowerModifierCurve(const Curve& curve) {
      return setPointer(openstudio::EvaporativeCooler_Indirect_ResearchSpecialFields::SecondaryAirFanPowerModifierCurveName, curve.handle());
    }

    void EvaporativeCoolerIndirectResearchSpecial_Impl::resetSecondaryAirFanPowerModifierCurve() {
      OS_ASSERT(setString(openstudio::EvaporativeCooler_Indirect_ResearchSpecialFields::SecondaryAirFanPowerModifierCurveName, ""));
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
      return boost::none;
    }

    bool EvaporativeCoolerIndirectResearchSpecial_Impl::syncSecondaryAirFanSizingSpecificPower() {
      if (m_secondaryFanTotalEfficiency > 0.0) {
        return setDouble(openstudio::EvaporativeCooler_Indirect_ResearchSpecialFields::SecondaryAirFanSizingSpecificPower,
                         m_secondaryFanDeltaPressure / m_secondaryFanTotalEfficiency);
      }
      return setString(openstudio::EvaporativeCooler_Indirect_ResearchSpecialFields::SecondaryAirFanSizingSpecificPower, "");
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
