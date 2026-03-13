/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "HeatPumpWaterToWaterParameterEstimationCooling.hpp"
#include "HeatPumpWaterToWaterParameterEstimationCooling_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/HeatPump_WaterToWater_ParameterEstimation_Cooling_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  HeatPumpWaterToWaterParameterEstimationCooling::HeatPumpWaterToWaterParameterEstimationCooling(const Model& model)
    : ModelObject(HeatPumpWaterToWaterParameterEstimationCooling::iddObjectType(), model) {}

  HeatPumpWaterToWaterParameterEstimationCooling::HeatPumpWaterToWaterParameterEstimationCooling(
    std::shared_ptr<detail::HeatPumpWaterToWaterParameterEstimationCooling_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType HeatPumpWaterToWaterParameterEstimationCooling::iddObjectType() {
    return IddObjectType::HeatPump_WaterToWater_ParameterEstimation_Cooling;
  }

  boost::optional<double> HeatPumpWaterToWaterParameterEstimationCooling::nominalCOP() const {
    return getImpl<detail::HeatPumpWaterToWaterParameterEstimationCooling_Impl>()->nominalCOP();
  }

  bool HeatPumpWaterToWaterParameterEstimationCooling::setNominalCOP(double nominalCOP) {
    return getImpl<detail::HeatPumpWaterToWaterParameterEstimationCooling_Impl>()->setNominalCOP(nominalCOP);
  }

  boost::optional<double> HeatPumpWaterToWaterParameterEstimationCooling::nominalCapacity() const {
    return getImpl<detail::HeatPumpWaterToWaterParameterEstimationCooling_Impl>()->nominalCapacity();
  }

  bool HeatPumpWaterToWaterParameterEstimationCooling::setNominalCapacity(double nominalCapacity) {
    return getImpl<detail::HeatPumpWaterToWaterParameterEstimationCooling_Impl>()->setNominalCapacity(nominalCapacity);
  }

  boost::optional<double> HeatPumpWaterToWaterParameterEstimationCooling::minimumPartLoadRatio() const {
    return getImpl<detail::HeatPumpWaterToWaterParameterEstimationCooling_Impl>()->minimumPartLoadRatio();
  }

  bool HeatPumpWaterToWaterParameterEstimationCooling::setMinimumPartLoadRatio(double minimumPartLoadRatio) {
    return getImpl<detail::HeatPumpWaterToWaterParameterEstimationCooling_Impl>()->setMinimumPartLoadRatio(minimumPartLoadRatio);
  }

  boost::optional<double> HeatPumpWaterToWaterParameterEstimationCooling::maximumPartLoadRatio() const {
    return getImpl<detail::HeatPumpWaterToWaterParameterEstimationCooling_Impl>()->maximumPartLoadRatio();
  }

  bool HeatPumpWaterToWaterParameterEstimationCooling::setMaximumPartLoadRatio(double maximumPartLoadRatio) {
    return getImpl<detail::HeatPumpWaterToWaterParameterEstimationCooling_Impl>()->setMaximumPartLoadRatio(maximumPartLoadRatio);
  }

  boost::optional<double> HeatPumpWaterToWaterParameterEstimationCooling::optimumPartLoadRatio() const {
    return getImpl<detail::HeatPumpWaterToWaterParameterEstimationCooling_Impl>()->optimumPartLoadRatio();
  }

  bool HeatPumpWaterToWaterParameterEstimationCooling::setOptimumPartLoadRatio(double optimumPartLoadRatio) {
    return getImpl<detail::HeatPumpWaterToWaterParameterEstimationCooling_Impl>()->setOptimumPartLoadRatio(optimumPartLoadRatio);
  }

  boost::optional<double> HeatPumpWaterToWaterParameterEstimationCooling::loadSideFlowRate() const {
    return getImpl<detail::HeatPumpWaterToWaterParameterEstimationCooling_Impl>()->loadSideFlowRate();
  }

  bool HeatPumpWaterToWaterParameterEstimationCooling::setLoadSideFlowRate(double loadSideFlowRate) {
    return getImpl<detail::HeatPumpWaterToWaterParameterEstimationCooling_Impl>()->setLoadSideFlowRate(loadSideFlowRate);
  }

  boost::optional<double> HeatPumpWaterToWaterParameterEstimationCooling::sourceSideFlowRate() const {
    return getImpl<detail::HeatPumpWaterToWaterParameterEstimationCooling_Impl>()->sourceSideFlowRate();
  }

  bool HeatPumpWaterToWaterParameterEstimationCooling::setSourceSideFlowRate(double sourceSideFlowRate) {
    return getImpl<detail::HeatPumpWaterToWaterParameterEstimationCooling_Impl>()->setSourceSideFlowRate(sourceSideFlowRate);
  }

  boost::optional<double> HeatPumpWaterToWaterParameterEstimationCooling::loadSideHeatTransferCoefficient() const {
    return getImpl<detail::HeatPumpWaterToWaterParameterEstimationCooling_Impl>()->loadSideHeatTransferCoefficient();
  }

  bool HeatPumpWaterToWaterParameterEstimationCooling::setLoadSideHeatTransferCoefficient(double loadSideHeatTransferCoefficient) {
    return getImpl<detail::HeatPumpWaterToWaterParameterEstimationCooling_Impl>()->setLoadSideHeatTransferCoefficient(
      loadSideHeatTransferCoefficient);
  }

  boost::optional<double> HeatPumpWaterToWaterParameterEstimationCooling::sourceSideHeatTransferCoefficient() const {
    return getImpl<detail::HeatPumpWaterToWaterParameterEstimationCooling_Impl>()->sourceSideHeatTransferCoefficient();
  }

  bool HeatPumpWaterToWaterParameterEstimationCooling::setSourceSideHeatTransferCoefficient(double sourceSideHeatTransferCoefficient) {
    return getImpl<detail::HeatPumpWaterToWaterParameterEstimationCooling_Impl>()->setSourceSideHeatTransferCoefficient(
      sourceSideHeatTransferCoefficient);
  }

  boost::optional<double> HeatPumpWaterToWaterParameterEstimationCooling::pistonDisplacement() const {
    return getImpl<detail::HeatPumpWaterToWaterParameterEstimationCooling_Impl>()->pistonDisplacement();
  }

  bool HeatPumpWaterToWaterParameterEstimationCooling::setPistonDisplacement(double pistonDisplacement) {
    return getImpl<detail::HeatPumpWaterToWaterParameterEstimationCooling_Impl>()->setPistonDisplacement(pistonDisplacement);
  }

  boost::optional<double> HeatPumpWaterToWaterParameterEstimationCooling::compressorClearanceFactor() const {
    return getImpl<detail::HeatPumpWaterToWaterParameterEstimationCooling_Impl>()->compressorClearanceFactor();
  }

  bool HeatPumpWaterToWaterParameterEstimationCooling::setCompressorClearanceFactor(double compressorClearanceFactor) {
    return getImpl<detail::HeatPumpWaterToWaterParameterEstimationCooling_Impl>()->setCompressorClearanceFactor(compressorClearanceFactor);
  }

  boost::optional<double> HeatPumpWaterToWaterParameterEstimationCooling::compressorSuctionandDischargePressureDrop() const {
    return getImpl<detail::HeatPumpWaterToWaterParameterEstimationCooling_Impl>()->compressorSuctionandDischargePressureDrop();
  }

  bool
    HeatPumpWaterToWaterParameterEstimationCooling::setCompressorSuctionandDischargePressureDrop(double compressorSuctionandDischargePressureDrop) {
    return getImpl<detail::HeatPumpWaterToWaterParameterEstimationCooling_Impl>()->setCompressorSuctionandDischargePressureDrop(
      compressorSuctionandDischargePressureDrop);
  }

  boost::optional<double> HeatPumpWaterToWaterParameterEstimationCooling::superheating() const {
    return getImpl<detail::HeatPumpWaterToWaterParameterEstimationCooling_Impl>()->superheating();
  }

  bool HeatPumpWaterToWaterParameterEstimationCooling::setSuperheating(double superheating) {
    return getImpl<detail::HeatPumpWaterToWaterParameterEstimationCooling_Impl>()->setSuperheating(superheating);
  }

  boost::optional<double> HeatPumpWaterToWaterParameterEstimationCooling::constantPartofElectromechanicalPowerLosses() const {
    return getImpl<detail::HeatPumpWaterToWaterParameterEstimationCooling_Impl>()->constantPartofElectromechanicalPowerLosses();
  }

  bool
    HeatPumpWaterToWaterParameterEstimationCooling::setConstantPartofElectromechanicalPowerLosses(double constantPartofElectromechanicalPowerLosses) {
    return getImpl<detail::HeatPumpWaterToWaterParameterEstimationCooling_Impl>()->setConstantPartofElectromechanicalPowerLosses(
      constantPartofElectromechanicalPowerLosses);
  }

  boost::optional<double> HeatPumpWaterToWaterParameterEstimationCooling::lossFactor() const {
    return getImpl<detail::HeatPumpWaterToWaterParameterEstimationCooling_Impl>()->lossFactor();
  }

  bool HeatPumpWaterToWaterParameterEstimationCooling::setLossFactor(double lossFactor) {
    return getImpl<detail::HeatPumpWaterToWaterParameterEstimationCooling_Impl>()->setLossFactor(lossFactor);
  }

  double HeatPumpWaterToWaterParameterEstimationCooling::highPressureCutOff() const {
    return getImpl<detail::HeatPumpWaterToWaterParameterEstimationCooling_Impl>()->highPressureCutOff();
  }

  bool HeatPumpWaterToWaterParameterEstimationCooling::isHighPressureCutOffDefaulted() const {
    return getImpl<detail::HeatPumpWaterToWaterParameterEstimationCooling_Impl>()->isHighPressureCutOffDefaulted();
  }

  bool HeatPumpWaterToWaterParameterEstimationCooling::setHighPressureCutOff(double highPressureCutOff) {
    return getImpl<detail::HeatPumpWaterToWaterParameterEstimationCooling_Impl>()->setHighPressureCutOff(highPressureCutOff);
  }

  void HeatPumpWaterToWaterParameterEstimationCooling::resetHighPressureCutOff() {
    getImpl<detail::HeatPumpWaterToWaterParameterEstimationCooling_Impl>()->resetHighPressureCutOff();
  }

  double HeatPumpWaterToWaterParameterEstimationCooling::lowPressureCutOff() const {
    return getImpl<detail::HeatPumpWaterToWaterParameterEstimationCooling_Impl>()->lowPressureCutOff();
  }

  bool HeatPumpWaterToWaterParameterEstimationCooling::isLowPressureCutOffDefaulted() const {
    return getImpl<detail::HeatPumpWaterToWaterParameterEstimationCooling_Impl>()->isLowPressureCutOffDefaulted();
  }

  bool HeatPumpWaterToWaterParameterEstimationCooling::setLowPressureCutOff(double lowPressureCutOff) {
    return getImpl<detail::HeatPumpWaterToWaterParameterEstimationCooling_Impl>()->setLowPressureCutOff(lowPressureCutOff);
  }

  void HeatPumpWaterToWaterParameterEstimationCooling::resetLowPressureCutOff() {
    getImpl<detail::HeatPumpWaterToWaterParameterEstimationCooling_Impl>()->resetLowPressureCutOff();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    boost::optional<double> HeatPumpWaterToWaterParameterEstimationCooling_Impl::nominalCOP() const {
      return getDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_CoolingFields::NominalCOP, true);
    }

    bool HeatPumpWaterToWaterParameterEstimationCooling_Impl::setNominalCOP(double nominalCOP) {
      return setDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_CoolingFields::NominalCOP, nominalCOP);
    }

    boost::optional<double> HeatPumpWaterToWaterParameterEstimationCooling_Impl::nominalCapacity() const {
      return getDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_CoolingFields::NominalCapacity, true);
    }

    bool HeatPumpWaterToWaterParameterEstimationCooling_Impl::setNominalCapacity(double nominalCapacity) {
      return setDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_CoolingFields::NominalCapacity, nominalCapacity);
    }

    boost::optional<double> HeatPumpWaterToWaterParameterEstimationCooling_Impl::minimumPartLoadRatio() const {
      return getDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_CoolingFields::MinimumPartLoadRatio, true);
    }

    bool HeatPumpWaterToWaterParameterEstimationCooling_Impl::setMinimumPartLoadRatio(double minimumPartLoadRatio) {
      return setDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_CoolingFields::MinimumPartLoadRatio, minimumPartLoadRatio);
    }

    boost::optional<double> HeatPumpWaterToWaterParameterEstimationCooling_Impl::maximumPartLoadRatio() const {
      return getDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_CoolingFields::MaximumPartLoadRatio, true);
    }

    bool HeatPumpWaterToWaterParameterEstimationCooling_Impl::setMaximumPartLoadRatio(double maximumPartLoadRatio) {
      return setDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_CoolingFields::MaximumPartLoadRatio, maximumPartLoadRatio);
    }

    boost::optional<double> HeatPumpWaterToWaterParameterEstimationCooling_Impl::optimumPartLoadRatio() const {
      return getDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_CoolingFields::OptimumPartLoadRatio, true);
    }

    bool HeatPumpWaterToWaterParameterEstimationCooling_Impl::setOptimumPartLoadRatio(double optimumPartLoadRatio) {
      return setDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_CoolingFields::OptimumPartLoadRatio, optimumPartLoadRatio);
    }

    boost::optional<double> HeatPumpWaterToWaterParameterEstimationCooling_Impl::loadSideFlowRate() const {
      return getDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_CoolingFields::LoadSideFlowRate, true);
    }

    bool HeatPumpWaterToWaterParameterEstimationCooling_Impl::setLoadSideFlowRate(double loadSideFlowRate) {
      return setDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_CoolingFields::LoadSideFlowRate, loadSideFlowRate);
    }

    boost::optional<double> HeatPumpWaterToWaterParameterEstimationCooling_Impl::sourceSideFlowRate() const {
      return getDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_CoolingFields::SourceSideFlowRate, true);
    }

    bool HeatPumpWaterToWaterParameterEstimationCooling_Impl::setSourceSideFlowRate(double sourceSideFlowRate) {
      return setDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_CoolingFields::SourceSideFlowRate, sourceSideFlowRate);
    }

    boost::optional<double> HeatPumpWaterToWaterParameterEstimationCooling_Impl::loadSideHeatTransferCoefficient() const {
      return getDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_CoolingFields::LoadSideHeatTransferCoefficient, true);
    }

    bool HeatPumpWaterToWaterParameterEstimationCooling_Impl::setLoadSideHeatTransferCoefficient(double loadSideHeatTransferCoefficient) {
      return setDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_CoolingFields::LoadSideHeatTransferCoefficient,
                       loadSideHeatTransferCoefficient);
    }

    boost::optional<double> HeatPumpWaterToWaterParameterEstimationCooling_Impl::sourceSideHeatTransferCoefficient() const {
      return getDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_CoolingFields::SourceSideHeatTransferCoefficient, true);
    }

    bool HeatPumpWaterToWaterParameterEstimationCooling_Impl::setSourceSideHeatTransferCoefficient(double sourceSideHeatTransferCoefficient) {
      return setDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_CoolingFields::SourceSideHeatTransferCoefficient,
                       sourceSideHeatTransferCoefficient);
    }

    boost::optional<double> HeatPumpWaterToWaterParameterEstimationCooling_Impl::pistonDisplacement() const {
      return getDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_CoolingFields::PistonDisplacement, true);
    }

    bool HeatPumpWaterToWaterParameterEstimationCooling_Impl::setPistonDisplacement(double pistonDisplacement) {
      return setDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_CoolingFields::PistonDisplacement, pistonDisplacement);
    }

    boost::optional<double> HeatPumpWaterToWaterParameterEstimationCooling_Impl::compressorClearanceFactor() const {
      return getDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_CoolingFields::CompressorClearanceFactor, true);
    }

    bool HeatPumpWaterToWaterParameterEstimationCooling_Impl::setCompressorClearanceFactor(double compressorClearanceFactor) {
      return setDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_CoolingFields::CompressorClearanceFactor, compressorClearanceFactor);
    }

    boost::optional<double> HeatPumpWaterToWaterParameterEstimationCooling_Impl::compressorSuctionandDischargePressureDrop() const {
      return getDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_CoolingFields::CompressorSuctionandDischargePressureDrop, true);
    }

    bool HeatPumpWaterToWaterParameterEstimationCooling_Impl::setCompressorSuctionandDischargePressureDrop(
      double compressorSuctionandDischargePressureDrop) {
      return setDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_CoolingFields::CompressorSuctionandDischargePressureDrop,
                       compressorSuctionandDischargePressureDrop);
    }

    boost::optional<double> HeatPumpWaterToWaterParameterEstimationCooling_Impl::superheating() const {
      return getDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_CoolingFields::Superheating, true);
    }

    bool HeatPumpWaterToWaterParameterEstimationCooling_Impl::setSuperheating(double superheating) {
      return setDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_CoolingFields::Superheating, superheating);
    }

    boost::optional<double> HeatPumpWaterToWaterParameterEstimationCooling_Impl::constantPartofElectromechanicalPowerLosses() const {
      return getDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_CoolingFields::ConstantPartofElectromechanicalPowerLosses, true);
    }

    bool HeatPumpWaterToWaterParameterEstimationCooling_Impl::setConstantPartofElectromechanicalPowerLosses(
      double constantPartofElectromechanicalPowerLosses) {
      return setDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_CoolingFields::ConstantPartofElectromechanicalPowerLosses,
                       constantPartofElectromechanicalPowerLosses);
    }

    boost::optional<double> HeatPumpWaterToWaterParameterEstimationCooling_Impl::lossFactor() const {
      return getDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_CoolingFields::LossFactor, true);
    }

    bool HeatPumpWaterToWaterParameterEstimationCooling_Impl::setLossFactor(double lossFactor) {
      return setDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_CoolingFields::LossFactor, lossFactor);
    }

    double HeatPumpWaterToWaterParameterEstimationCooling_Impl::highPressureCutOff() const {
      const auto value = getDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_CoolingFields::HighPressureCutOff, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HeatPumpWaterToWaterParameterEstimationCooling_Impl::isHighPressureCutOffDefaulted() const {
      return isEmpty(openstudio::HeatPump_WaterToWater_ParameterEstimation_CoolingFields::HighPressureCutOff);
    }

    bool HeatPumpWaterToWaterParameterEstimationCooling_Impl::setHighPressureCutOff(double highPressureCutOff) {
      return setDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_CoolingFields::HighPressureCutOff, highPressureCutOff);
    }

    void HeatPumpWaterToWaterParameterEstimationCooling_Impl::resetHighPressureCutOff() {
      OS_ASSERT(setString(openstudio::HeatPump_WaterToWater_ParameterEstimation_CoolingFields::HighPressureCutOff, ""));
    }

    double HeatPumpWaterToWaterParameterEstimationCooling_Impl::lowPressureCutOff() const {
      const auto value = getDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_CoolingFields::LowPressureCutOff, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HeatPumpWaterToWaterParameterEstimationCooling_Impl::isLowPressureCutOffDefaulted() const {
      return isEmpty(openstudio::HeatPump_WaterToWater_ParameterEstimation_CoolingFields::LowPressureCutOff);
    }

    bool HeatPumpWaterToWaterParameterEstimationCooling_Impl::setLowPressureCutOff(double lowPressureCutOff) {
      return setDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_CoolingFields::LowPressureCutOff, lowPressureCutOff);
    }

    void HeatPumpWaterToWaterParameterEstimationCooling_Impl::resetLowPressureCutOff() {
      OS_ASSERT(setString(openstudio::HeatPump_WaterToWater_ParameterEstimation_CoolingFields::LowPressureCutOff, ""));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
