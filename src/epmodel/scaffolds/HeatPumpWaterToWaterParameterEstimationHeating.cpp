/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "HeatPumpWaterToWaterParameterEstimationHeating.hpp"
#include "HeatPumpWaterToWaterParameterEstimationHeating_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/HeatPump_WaterToWater_ParameterEstimation_Heating_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  HeatPumpWaterToWaterParameterEstimationHeating::HeatPumpWaterToWaterParameterEstimationHeating(const Model& model)
    : ModelObject(HeatPumpWaterToWaterParameterEstimationHeating::iddObjectType(), model) {}

  HeatPumpWaterToWaterParameterEstimationHeating::HeatPumpWaterToWaterParameterEstimationHeating(
    std::shared_ptr<detail::HeatPumpWaterToWaterParameterEstimationHeating_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType HeatPumpWaterToWaterParameterEstimationHeating::iddObjectType() {
    return IddObjectType::HeatPump_WaterToWater_ParameterEstimation_Heating;
  }

  boost::optional<double> HeatPumpWaterToWaterParameterEstimationHeating::nominalCOP() const {
    return getImpl<detail::HeatPumpWaterToWaterParameterEstimationHeating_Impl>()->nominalCOP();
  }

  bool HeatPumpWaterToWaterParameterEstimationHeating::setNominalCOP(double nominalCOP) {
    return getImpl<detail::HeatPumpWaterToWaterParameterEstimationHeating_Impl>()->setNominalCOP(nominalCOP);
  }

  boost::optional<double> HeatPumpWaterToWaterParameterEstimationHeating::nominalCapacity() const {
    return getImpl<detail::HeatPumpWaterToWaterParameterEstimationHeating_Impl>()->nominalCapacity();
  }

  bool HeatPumpWaterToWaterParameterEstimationHeating::setNominalCapacity(double nominalCapacity) {
    return getImpl<detail::HeatPumpWaterToWaterParameterEstimationHeating_Impl>()->setNominalCapacity(nominalCapacity);
  }

  boost::optional<double> HeatPumpWaterToWaterParameterEstimationHeating::minimumPartLoadRatio() const {
    return getImpl<detail::HeatPumpWaterToWaterParameterEstimationHeating_Impl>()->minimumPartLoadRatio();
  }

  bool HeatPumpWaterToWaterParameterEstimationHeating::setMinimumPartLoadRatio(double minimumPartLoadRatio) {
    return getImpl<detail::HeatPumpWaterToWaterParameterEstimationHeating_Impl>()->setMinimumPartLoadRatio(minimumPartLoadRatio);
  }

  boost::optional<double> HeatPumpWaterToWaterParameterEstimationHeating::maximumPartLoadRatio() const {
    return getImpl<detail::HeatPumpWaterToWaterParameterEstimationHeating_Impl>()->maximumPartLoadRatio();
  }

  bool HeatPumpWaterToWaterParameterEstimationHeating::setMaximumPartLoadRatio(double maximumPartLoadRatio) {
    return getImpl<detail::HeatPumpWaterToWaterParameterEstimationHeating_Impl>()->setMaximumPartLoadRatio(maximumPartLoadRatio);
  }

  boost::optional<double> HeatPumpWaterToWaterParameterEstimationHeating::optimumPartLoadRatio() const {
    return getImpl<detail::HeatPumpWaterToWaterParameterEstimationHeating_Impl>()->optimumPartLoadRatio();
  }

  bool HeatPumpWaterToWaterParameterEstimationHeating::setOptimumPartLoadRatio(double optimumPartLoadRatio) {
    return getImpl<detail::HeatPumpWaterToWaterParameterEstimationHeating_Impl>()->setOptimumPartLoadRatio(optimumPartLoadRatio);
  }

  boost::optional<double> HeatPumpWaterToWaterParameterEstimationHeating::loadSideFlowRate() const {
    return getImpl<detail::HeatPumpWaterToWaterParameterEstimationHeating_Impl>()->loadSideFlowRate();
  }

  bool HeatPumpWaterToWaterParameterEstimationHeating::setLoadSideFlowRate(double loadSideFlowRate) {
    return getImpl<detail::HeatPumpWaterToWaterParameterEstimationHeating_Impl>()->setLoadSideFlowRate(loadSideFlowRate);
  }

  boost::optional<double> HeatPumpWaterToWaterParameterEstimationHeating::sourceSideFlowRate() const {
    return getImpl<detail::HeatPumpWaterToWaterParameterEstimationHeating_Impl>()->sourceSideFlowRate();
  }

  bool HeatPumpWaterToWaterParameterEstimationHeating::setSourceSideFlowRate(double sourceSideFlowRate) {
    return getImpl<detail::HeatPumpWaterToWaterParameterEstimationHeating_Impl>()->setSourceSideFlowRate(sourceSideFlowRate);
  }

  boost::optional<double> HeatPumpWaterToWaterParameterEstimationHeating::loadSideHeatTransferCoefficient() const {
    return getImpl<detail::HeatPumpWaterToWaterParameterEstimationHeating_Impl>()->loadSideHeatTransferCoefficient();
  }

  bool HeatPumpWaterToWaterParameterEstimationHeating::setLoadSideHeatTransferCoefficient(double loadSideHeatTransferCoefficient) {
    return getImpl<detail::HeatPumpWaterToWaterParameterEstimationHeating_Impl>()->setLoadSideHeatTransferCoefficient(
      loadSideHeatTransferCoefficient);
  }

  boost::optional<double> HeatPumpWaterToWaterParameterEstimationHeating::sourceSideHeatTransferCoefficient() const {
    return getImpl<detail::HeatPumpWaterToWaterParameterEstimationHeating_Impl>()->sourceSideHeatTransferCoefficient();
  }

  bool HeatPumpWaterToWaterParameterEstimationHeating::setSourceSideHeatTransferCoefficient(double sourceSideHeatTransferCoefficient) {
    return getImpl<detail::HeatPumpWaterToWaterParameterEstimationHeating_Impl>()->setSourceSideHeatTransferCoefficient(
      sourceSideHeatTransferCoefficient);
  }

  boost::optional<double> HeatPumpWaterToWaterParameterEstimationHeating::pistonDisplacement() const {
    return getImpl<detail::HeatPumpWaterToWaterParameterEstimationHeating_Impl>()->pistonDisplacement();
  }

  bool HeatPumpWaterToWaterParameterEstimationHeating::setPistonDisplacement(double pistonDisplacement) {
    return getImpl<detail::HeatPumpWaterToWaterParameterEstimationHeating_Impl>()->setPistonDisplacement(pistonDisplacement);
  }

  boost::optional<double> HeatPumpWaterToWaterParameterEstimationHeating::compressorClearanceFactor() const {
    return getImpl<detail::HeatPumpWaterToWaterParameterEstimationHeating_Impl>()->compressorClearanceFactor();
  }

  bool HeatPumpWaterToWaterParameterEstimationHeating::setCompressorClearanceFactor(double compressorClearanceFactor) {
    return getImpl<detail::HeatPumpWaterToWaterParameterEstimationHeating_Impl>()->setCompressorClearanceFactor(compressorClearanceFactor);
  }

  boost::optional<double> HeatPumpWaterToWaterParameterEstimationHeating::compressorSuctionandDischargePressureDrop() const {
    return getImpl<detail::HeatPumpWaterToWaterParameterEstimationHeating_Impl>()->compressorSuctionandDischargePressureDrop();
  }

  bool
    HeatPumpWaterToWaterParameterEstimationHeating::setCompressorSuctionandDischargePressureDrop(double compressorSuctionandDischargePressureDrop) {
    return getImpl<detail::HeatPumpWaterToWaterParameterEstimationHeating_Impl>()->setCompressorSuctionandDischargePressureDrop(
      compressorSuctionandDischargePressureDrop);
  }

  boost::optional<double> HeatPumpWaterToWaterParameterEstimationHeating::superheating() const {
    return getImpl<detail::HeatPumpWaterToWaterParameterEstimationHeating_Impl>()->superheating();
  }

  bool HeatPumpWaterToWaterParameterEstimationHeating::setSuperheating(double superheating) {
    return getImpl<detail::HeatPumpWaterToWaterParameterEstimationHeating_Impl>()->setSuperheating(superheating);
  }

  boost::optional<double> HeatPumpWaterToWaterParameterEstimationHeating::constantPartofElectromechanicalPowerLosses() const {
    return getImpl<detail::HeatPumpWaterToWaterParameterEstimationHeating_Impl>()->constantPartofElectromechanicalPowerLosses();
  }

  bool
    HeatPumpWaterToWaterParameterEstimationHeating::setConstantPartofElectromechanicalPowerLosses(double constantPartofElectromechanicalPowerLosses) {
    return getImpl<detail::HeatPumpWaterToWaterParameterEstimationHeating_Impl>()->setConstantPartofElectromechanicalPowerLosses(
      constantPartofElectromechanicalPowerLosses);
  }

  boost::optional<double> HeatPumpWaterToWaterParameterEstimationHeating::lossFactor() const {
    return getImpl<detail::HeatPumpWaterToWaterParameterEstimationHeating_Impl>()->lossFactor();
  }

  bool HeatPumpWaterToWaterParameterEstimationHeating::setLossFactor(double lossFactor) {
    return getImpl<detail::HeatPumpWaterToWaterParameterEstimationHeating_Impl>()->setLossFactor(lossFactor);
  }

  double HeatPumpWaterToWaterParameterEstimationHeating::highPressureCutOff() const {
    return getImpl<detail::HeatPumpWaterToWaterParameterEstimationHeating_Impl>()->highPressureCutOff();
  }

  bool HeatPumpWaterToWaterParameterEstimationHeating::isHighPressureCutOffDefaulted() const {
    return getImpl<detail::HeatPumpWaterToWaterParameterEstimationHeating_Impl>()->isHighPressureCutOffDefaulted();
  }

  bool HeatPumpWaterToWaterParameterEstimationHeating::setHighPressureCutOff(double highPressureCutOff) {
    return getImpl<detail::HeatPumpWaterToWaterParameterEstimationHeating_Impl>()->setHighPressureCutOff(highPressureCutOff);
  }

  void HeatPumpWaterToWaterParameterEstimationHeating::resetHighPressureCutOff() {
    getImpl<detail::HeatPumpWaterToWaterParameterEstimationHeating_Impl>()->resetHighPressureCutOff();
  }

  double HeatPumpWaterToWaterParameterEstimationHeating::lowPressureCutOff() const {
    return getImpl<detail::HeatPumpWaterToWaterParameterEstimationHeating_Impl>()->lowPressureCutOff();
  }

  bool HeatPumpWaterToWaterParameterEstimationHeating::isLowPressureCutOffDefaulted() const {
    return getImpl<detail::HeatPumpWaterToWaterParameterEstimationHeating_Impl>()->isLowPressureCutOffDefaulted();
  }

  bool HeatPumpWaterToWaterParameterEstimationHeating::setLowPressureCutOff(double lowPressureCutOff) {
    return getImpl<detail::HeatPumpWaterToWaterParameterEstimationHeating_Impl>()->setLowPressureCutOff(lowPressureCutOff);
  }

  void HeatPumpWaterToWaterParameterEstimationHeating::resetLowPressureCutOff() {
    getImpl<detail::HeatPumpWaterToWaterParameterEstimationHeating_Impl>()->resetLowPressureCutOff();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    boost::optional<double> HeatPumpWaterToWaterParameterEstimationHeating_Impl::nominalCOP() const {
      return getDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_HeatingFields::NominalCOP, true);
    }

    bool HeatPumpWaterToWaterParameterEstimationHeating_Impl::setNominalCOP(double nominalCOP) {
      return setDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_HeatingFields::NominalCOP, nominalCOP);
    }

    boost::optional<double> HeatPumpWaterToWaterParameterEstimationHeating_Impl::nominalCapacity() const {
      return getDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_HeatingFields::NominalCapacity, true);
    }

    bool HeatPumpWaterToWaterParameterEstimationHeating_Impl::setNominalCapacity(double nominalCapacity) {
      return setDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_HeatingFields::NominalCapacity, nominalCapacity);
    }

    boost::optional<double> HeatPumpWaterToWaterParameterEstimationHeating_Impl::minimumPartLoadRatio() const {
      return getDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_HeatingFields::MinimumPartLoadRatio, true);
    }

    bool HeatPumpWaterToWaterParameterEstimationHeating_Impl::setMinimumPartLoadRatio(double minimumPartLoadRatio) {
      return setDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_HeatingFields::MinimumPartLoadRatio, minimumPartLoadRatio);
    }

    boost::optional<double> HeatPumpWaterToWaterParameterEstimationHeating_Impl::maximumPartLoadRatio() const {
      return getDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_HeatingFields::MaximumPartLoadRatio, true);
    }

    bool HeatPumpWaterToWaterParameterEstimationHeating_Impl::setMaximumPartLoadRatio(double maximumPartLoadRatio) {
      return setDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_HeatingFields::MaximumPartLoadRatio, maximumPartLoadRatio);
    }

    boost::optional<double> HeatPumpWaterToWaterParameterEstimationHeating_Impl::optimumPartLoadRatio() const {
      return getDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_HeatingFields::OptimumPartLoadRatio, true);
    }

    bool HeatPumpWaterToWaterParameterEstimationHeating_Impl::setOptimumPartLoadRatio(double optimumPartLoadRatio) {
      return setDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_HeatingFields::OptimumPartLoadRatio, optimumPartLoadRatio);
    }

    boost::optional<double> HeatPumpWaterToWaterParameterEstimationHeating_Impl::loadSideFlowRate() const {
      return getDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_HeatingFields::LoadSideFlowRate, true);
    }

    bool HeatPumpWaterToWaterParameterEstimationHeating_Impl::setLoadSideFlowRate(double loadSideFlowRate) {
      return setDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_HeatingFields::LoadSideFlowRate, loadSideFlowRate);
    }

    boost::optional<double> HeatPumpWaterToWaterParameterEstimationHeating_Impl::sourceSideFlowRate() const {
      return getDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_HeatingFields::SourceSideFlowRate, true);
    }

    bool HeatPumpWaterToWaterParameterEstimationHeating_Impl::setSourceSideFlowRate(double sourceSideFlowRate) {
      return setDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_HeatingFields::SourceSideFlowRate, sourceSideFlowRate);
    }

    boost::optional<double> HeatPumpWaterToWaterParameterEstimationHeating_Impl::loadSideHeatTransferCoefficient() const {
      return getDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_HeatingFields::LoadSideHeatTransferCoefficient, true);
    }

    bool HeatPumpWaterToWaterParameterEstimationHeating_Impl::setLoadSideHeatTransferCoefficient(double loadSideHeatTransferCoefficient) {
      return setDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_HeatingFields::LoadSideHeatTransferCoefficient,
                       loadSideHeatTransferCoefficient);
    }

    boost::optional<double> HeatPumpWaterToWaterParameterEstimationHeating_Impl::sourceSideHeatTransferCoefficient() const {
      return getDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_HeatingFields::SourceSideHeatTransferCoefficient, true);
    }

    bool HeatPumpWaterToWaterParameterEstimationHeating_Impl::setSourceSideHeatTransferCoefficient(double sourceSideHeatTransferCoefficient) {
      return setDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_HeatingFields::SourceSideHeatTransferCoefficient,
                       sourceSideHeatTransferCoefficient);
    }

    boost::optional<double> HeatPumpWaterToWaterParameterEstimationHeating_Impl::pistonDisplacement() const {
      return getDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_HeatingFields::PistonDisplacement, true);
    }

    bool HeatPumpWaterToWaterParameterEstimationHeating_Impl::setPistonDisplacement(double pistonDisplacement) {
      return setDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_HeatingFields::PistonDisplacement, pistonDisplacement);
    }

    boost::optional<double> HeatPumpWaterToWaterParameterEstimationHeating_Impl::compressorClearanceFactor() const {
      return getDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_HeatingFields::CompressorClearanceFactor, true);
    }

    bool HeatPumpWaterToWaterParameterEstimationHeating_Impl::setCompressorClearanceFactor(double compressorClearanceFactor) {
      return setDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_HeatingFields::CompressorClearanceFactor, compressorClearanceFactor);
    }

    boost::optional<double> HeatPumpWaterToWaterParameterEstimationHeating_Impl::compressorSuctionandDischargePressureDrop() const {
      return getDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_HeatingFields::CompressorSuctionandDischargePressureDrop, true);
    }

    bool HeatPumpWaterToWaterParameterEstimationHeating_Impl::setCompressorSuctionandDischargePressureDrop(
      double compressorSuctionandDischargePressureDrop) {
      return setDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_HeatingFields::CompressorSuctionandDischargePressureDrop,
                       compressorSuctionandDischargePressureDrop);
    }

    boost::optional<double> HeatPumpWaterToWaterParameterEstimationHeating_Impl::superheating() const {
      return getDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_HeatingFields::Superheating, true);
    }

    bool HeatPumpWaterToWaterParameterEstimationHeating_Impl::setSuperheating(double superheating) {
      return setDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_HeatingFields::Superheating, superheating);
    }

    boost::optional<double> HeatPumpWaterToWaterParameterEstimationHeating_Impl::constantPartofElectromechanicalPowerLosses() const {
      return getDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_HeatingFields::ConstantPartofElectromechanicalPowerLosses, true);
    }

    bool HeatPumpWaterToWaterParameterEstimationHeating_Impl::setConstantPartofElectromechanicalPowerLosses(
      double constantPartofElectromechanicalPowerLosses) {
      return setDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_HeatingFields::ConstantPartofElectromechanicalPowerLosses,
                       constantPartofElectromechanicalPowerLosses);
    }

    boost::optional<double> HeatPumpWaterToWaterParameterEstimationHeating_Impl::lossFactor() const {
      return getDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_HeatingFields::LossFactor, true);
    }

    bool HeatPumpWaterToWaterParameterEstimationHeating_Impl::setLossFactor(double lossFactor) {
      return setDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_HeatingFields::LossFactor, lossFactor);
    }

    double HeatPumpWaterToWaterParameterEstimationHeating_Impl::highPressureCutOff() const {
      const auto value = getDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_HeatingFields::HighPressureCutOff, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HeatPumpWaterToWaterParameterEstimationHeating_Impl::isHighPressureCutOffDefaulted() const {
      return isEmpty(openstudio::HeatPump_WaterToWater_ParameterEstimation_HeatingFields::HighPressureCutOff);
    }

    bool HeatPumpWaterToWaterParameterEstimationHeating_Impl::setHighPressureCutOff(double highPressureCutOff) {
      return setDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_HeatingFields::HighPressureCutOff, highPressureCutOff);
    }

    void HeatPumpWaterToWaterParameterEstimationHeating_Impl::resetHighPressureCutOff() {
      OS_ASSERT(setString(openstudio::HeatPump_WaterToWater_ParameterEstimation_HeatingFields::HighPressureCutOff, ""));
    }

    double HeatPumpWaterToWaterParameterEstimationHeating_Impl::lowPressureCutOff() const {
      const auto value = getDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_HeatingFields::LowPressureCutOff, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HeatPumpWaterToWaterParameterEstimationHeating_Impl::isLowPressureCutOffDefaulted() const {
      return isEmpty(openstudio::HeatPump_WaterToWater_ParameterEstimation_HeatingFields::LowPressureCutOff);
    }

    bool HeatPumpWaterToWaterParameterEstimationHeating_Impl::setLowPressureCutOff(double lowPressureCutOff) {
      return setDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_HeatingFields::LowPressureCutOff, lowPressureCutOff);
    }

    void HeatPumpWaterToWaterParameterEstimationHeating_Impl::resetLowPressureCutOff() {
      OS_ASSERT(setString(openstudio::HeatPump_WaterToWater_ParameterEstimation_HeatingFields::LowPressureCutOff, ""));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
