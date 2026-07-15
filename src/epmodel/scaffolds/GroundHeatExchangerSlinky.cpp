/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "GroundHeatExchangerSlinky.hpp"
#include "GroundHeatExchangerSlinky_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/GroundHeatExchanger_Slinky_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

  GroundHeatExchangerSlinky::GroundHeatExchangerSlinky(const Model& model) : ModelObject(GroundHeatExchangerSlinky::iddObjectType(), model) {
    bool ok = true;
    ok = setDesignFlowRate(0.002);
    OS_ASSERT(ok);
    ok = setSoilThermalConductivity(1.08);
    OS_ASSERT(ok);
    ok = setSoilDensity(962.0);
    OS_ASSERT(ok);
    ok = setSoilSpecificHeat(2576.0);
    OS_ASSERT(ok);
    ok = setPipeThermalConductivity(0.4);
    OS_ASSERT(ok);
    ok = setPipeDensity(641.0);
    OS_ASSERT(ok);
    ok = setPipeSpecificHeat(2405.0);
    OS_ASSERT(ok);
    ok = setPipeOuterDiameter(0.02667);
    OS_ASSERT(ok);
    ok = setPipeThickness(0.002413);
    OS_ASSERT(ok);
    ok = setCoilDiameter(1.0);
    OS_ASSERT(ok);
    ok = setCoilPitch(0.20);
    OS_ASSERT(ok);
    ok = setTrenchDepth(1.8);
    OS_ASSERT(ok);
    ok = setTrenchLength(10.0);
    OS_ASSERT(ok);
    ok = setNumberofTrenches(1);
    OS_ASSERT(ok);
    ok = setHorizontalSpacingBetweenPipes(2.0);
    OS_ASSERT(ok);
  }

  GroundHeatExchangerSlinky::GroundHeatExchangerSlinky(std::shared_ptr<detail::GroundHeatExchangerSlinky_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType GroundHeatExchangerSlinky::iddObjectType() {
    return IddObjectType::GroundHeatExchanger_Slinky;
  }

  std::vector<std::string> GroundHeatExchangerSlinky::heatExchangerConfigurationValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::GroundHeatExchanger_SlinkyFields::HeatExchangerConfiguration);
  }

  std::vector<std::string> GroundHeatExchangerSlinky::undisturbedGroundTemperatureModelTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::GroundHeatExchanger_SlinkyFields::UndisturbedGroundTemperatureModelType);
  }

  double GroundHeatExchangerSlinky::designFlowRate() const {
    return getImpl<detail::GroundHeatExchangerSlinky_Impl>()->designFlowRate();
  }

  bool GroundHeatExchangerSlinky::isDesignFlowRateDefaulted() const {
    return getImpl<detail::GroundHeatExchangerSlinky_Impl>()->isDesignFlowRateDefaulted();
  }

  bool GroundHeatExchangerSlinky::setDesignFlowRate(double designFlowRate) {
    return getImpl<detail::GroundHeatExchangerSlinky_Impl>()->setDesignFlowRate(designFlowRate);
  }

  void GroundHeatExchangerSlinky::resetDesignFlowRate() {
    getImpl<detail::GroundHeatExchangerSlinky_Impl>()->resetDesignFlowRate();
  }

  double GroundHeatExchangerSlinky::soilThermalConductivity() const {
    return getImpl<detail::GroundHeatExchangerSlinky_Impl>()->soilThermalConductivity();
  }

  bool GroundHeatExchangerSlinky::isSoilThermalConductivityDefaulted() const {
    return getImpl<detail::GroundHeatExchangerSlinky_Impl>()->isSoilThermalConductivityDefaulted();
  }

  bool GroundHeatExchangerSlinky::setSoilThermalConductivity(double soilThermalConductivity) {
    return getImpl<detail::GroundHeatExchangerSlinky_Impl>()->setSoilThermalConductivity(soilThermalConductivity);
  }

  void GroundHeatExchangerSlinky::resetSoilThermalConductivity() {
    getImpl<detail::GroundHeatExchangerSlinky_Impl>()->resetSoilThermalConductivity();
  }

  double GroundHeatExchangerSlinky::soilDensity() const {
    return getImpl<detail::GroundHeatExchangerSlinky_Impl>()->soilDensity();
  }

  bool GroundHeatExchangerSlinky::isSoilDensityDefaulted() const {
    return getImpl<detail::GroundHeatExchangerSlinky_Impl>()->isSoilDensityDefaulted();
  }

  bool GroundHeatExchangerSlinky::setSoilDensity(double soilDensity) {
    return getImpl<detail::GroundHeatExchangerSlinky_Impl>()->setSoilDensity(soilDensity);
  }

  void GroundHeatExchangerSlinky::resetSoilDensity() {
    getImpl<detail::GroundHeatExchangerSlinky_Impl>()->resetSoilDensity();
  }

  double GroundHeatExchangerSlinky::soilSpecificHeat() const {
    return getImpl<detail::GroundHeatExchangerSlinky_Impl>()->soilSpecificHeat();
  }

  bool GroundHeatExchangerSlinky::isSoilSpecificHeatDefaulted() const {
    return getImpl<detail::GroundHeatExchangerSlinky_Impl>()->isSoilSpecificHeatDefaulted();
  }

  bool GroundHeatExchangerSlinky::setSoilSpecificHeat(double soilSpecificHeat) {
    return getImpl<detail::GroundHeatExchangerSlinky_Impl>()->setSoilSpecificHeat(soilSpecificHeat);
  }

  void GroundHeatExchangerSlinky::resetSoilSpecificHeat() {
    getImpl<detail::GroundHeatExchangerSlinky_Impl>()->resetSoilSpecificHeat();
  }

  double GroundHeatExchangerSlinky::pipeThermalConductivity() const {
    return getImpl<detail::GroundHeatExchangerSlinky_Impl>()->pipeThermalConductivity();
  }

  bool GroundHeatExchangerSlinky::isPipeThermalConductivityDefaulted() const {
    return getImpl<detail::GroundHeatExchangerSlinky_Impl>()->isPipeThermalConductivityDefaulted();
  }

  bool GroundHeatExchangerSlinky::setPipeThermalConductivity(double pipeThermalConductivity) {
    return getImpl<detail::GroundHeatExchangerSlinky_Impl>()->setPipeThermalConductivity(pipeThermalConductivity);
  }

  void GroundHeatExchangerSlinky::resetPipeThermalConductivity() {
    getImpl<detail::GroundHeatExchangerSlinky_Impl>()->resetPipeThermalConductivity();
  }

  double GroundHeatExchangerSlinky::pipeDensity() const {
    return getImpl<detail::GroundHeatExchangerSlinky_Impl>()->pipeDensity();
  }

  bool GroundHeatExchangerSlinky::isPipeDensityDefaulted() const {
    return getImpl<detail::GroundHeatExchangerSlinky_Impl>()->isPipeDensityDefaulted();
  }

  bool GroundHeatExchangerSlinky::setPipeDensity(double pipeDensity) {
    return getImpl<detail::GroundHeatExchangerSlinky_Impl>()->setPipeDensity(pipeDensity);
  }

  void GroundHeatExchangerSlinky::resetPipeDensity() {
    getImpl<detail::GroundHeatExchangerSlinky_Impl>()->resetPipeDensity();
  }

  double GroundHeatExchangerSlinky::pipeSpecificHeat() const {
    return getImpl<detail::GroundHeatExchangerSlinky_Impl>()->pipeSpecificHeat();
  }

  bool GroundHeatExchangerSlinky::isPipeSpecificHeatDefaulted() const {
    return getImpl<detail::GroundHeatExchangerSlinky_Impl>()->isPipeSpecificHeatDefaulted();
  }

  bool GroundHeatExchangerSlinky::setPipeSpecificHeat(double pipeSpecificHeat) {
    return getImpl<detail::GroundHeatExchangerSlinky_Impl>()->setPipeSpecificHeat(pipeSpecificHeat);
  }

  void GroundHeatExchangerSlinky::resetPipeSpecificHeat() {
    getImpl<detail::GroundHeatExchangerSlinky_Impl>()->resetPipeSpecificHeat();
  }

  double GroundHeatExchangerSlinky::pipeOuterDiameter() const {
    return getImpl<detail::GroundHeatExchangerSlinky_Impl>()->pipeOuterDiameter();
  }

  bool GroundHeatExchangerSlinky::isPipeOuterDiameterDefaulted() const {
    return getImpl<detail::GroundHeatExchangerSlinky_Impl>()->isPipeOuterDiameterDefaulted();
  }

  bool GroundHeatExchangerSlinky::setPipeOuterDiameter(double pipeOuterDiameter) {
    return getImpl<detail::GroundHeatExchangerSlinky_Impl>()->setPipeOuterDiameter(pipeOuterDiameter);
  }

  void GroundHeatExchangerSlinky::resetPipeOuterDiameter() {
    getImpl<detail::GroundHeatExchangerSlinky_Impl>()->resetPipeOuterDiameter();
  }

  double GroundHeatExchangerSlinky::pipeThickness() const {
    return getImpl<detail::GroundHeatExchangerSlinky_Impl>()->pipeThickness();
  }

  bool GroundHeatExchangerSlinky::isPipeThicknessDefaulted() const {
    return getImpl<detail::GroundHeatExchangerSlinky_Impl>()->isPipeThicknessDefaulted();
  }

  bool GroundHeatExchangerSlinky::setPipeThickness(double pipeThickness) {
    return getImpl<detail::GroundHeatExchangerSlinky_Impl>()->setPipeThickness(pipeThickness);
  }

  void GroundHeatExchangerSlinky::resetPipeThickness() {
    getImpl<detail::GroundHeatExchangerSlinky_Impl>()->resetPipeThickness();
  }

  boost::optional<std::string> GroundHeatExchangerSlinky::heatExchangerConfiguration() const {
    return getImpl<detail::GroundHeatExchangerSlinky_Impl>()->heatExchangerConfiguration();
  }

  bool GroundHeatExchangerSlinky::setHeatExchangerConfiguration(const std::string& heatExchangerConfiguration) {
    return getImpl<detail::GroundHeatExchangerSlinky_Impl>()->setHeatExchangerConfiguration(heatExchangerConfiguration);
  }

  void GroundHeatExchangerSlinky::resetHeatExchangerConfiguration() {
    getImpl<detail::GroundHeatExchangerSlinky_Impl>()->resetHeatExchangerConfiguration();
  }

  double GroundHeatExchangerSlinky::coilDiameter() const {
    return getImpl<detail::GroundHeatExchangerSlinky_Impl>()->coilDiameter();
  }

  bool GroundHeatExchangerSlinky::isCoilDiameterDefaulted() const {
    return getImpl<detail::GroundHeatExchangerSlinky_Impl>()->isCoilDiameterDefaulted();
  }

  bool GroundHeatExchangerSlinky::setCoilDiameter(double coilDiameter) {
    return getImpl<detail::GroundHeatExchangerSlinky_Impl>()->setCoilDiameter(coilDiameter);
  }

  void GroundHeatExchangerSlinky::resetCoilDiameter() {
    getImpl<detail::GroundHeatExchangerSlinky_Impl>()->resetCoilDiameter();
  }

  double GroundHeatExchangerSlinky::coilPitch() const {
    return getImpl<detail::GroundHeatExchangerSlinky_Impl>()->coilPitch();
  }

  bool GroundHeatExchangerSlinky::isCoilPitchDefaulted() const {
    return getImpl<detail::GroundHeatExchangerSlinky_Impl>()->isCoilPitchDefaulted();
  }

  bool GroundHeatExchangerSlinky::setCoilPitch(double coilPitch) {
    return getImpl<detail::GroundHeatExchangerSlinky_Impl>()->setCoilPitch(coilPitch);
  }

  void GroundHeatExchangerSlinky::resetCoilPitch() {
    getImpl<detail::GroundHeatExchangerSlinky_Impl>()->resetCoilPitch();
  }

  double GroundHeatExchangerSlinky::trenchDepth() const {
    return getImpl<detail::GroundHeatExchangerSlinky_Impl>()->trenchDepth();
  }

  bool GroundHeatExchangerSlinky::isTrenchDepthDefaulted() const {
    return getImpl<detail::GroundHeatExchangerSlinky_Impl>()->isTrenchDepthDefaulted();
  }

  bool GroundHeatExchangerSlinky::setTrenchDepth(double trenchDepth) {
    return getImpl<detail::GroundHeatExchangerSlinky_Impl>()->setTrenchDepth(trenchDepth);
  }

  void GroundHeatExchangerSlinky::resetTrenchDepth() {
    getImpl<detail::GroundHeatExchangerSlinky_Impl>()->resetTrenchDepth();
  }

  double GroundHeatExchangerSlinky::trenchLength() const {
    return getImpl<detail::GroundHeatExchangerSlinky_Impl>()->trenchLength();
  }

  bool GroundHeatExchangerSlinky::isTrenchLengthDefaulted() const {
    return getImpl<detail::GroundHeatExchangerSlinky_Impl>()->isTrenchLengthDefaulted();
  }

  bool GroundHeatExchangerSlinky::setTrenchLength(double trenchLength) {
    return getImpl<detail::GroundHeatExchangerSlinky_Impl>()->setTrenchLength(trenchLength);
  }

  void GroundHeatExchangerSlinky::resetTrenchLength() {
    getImpl<detail::GroundHeatExchangerSlinky_Impl>()->resetTrenchLength();
  }

  int GroundHeatExchangerSlinky::numberofTrenches() const {
    return getImpl<detail::GroundHeatExchangerSlinky_Impl>()->numberofTrenches();
  }

  bool GroundHeatExchangerSlinky::isNumberofTrenchesDefaulted() const {
    return getImpl<detail::GroundHeatExchangerSlinky_Impl>()->isNumberofTrenchesDefaulted();
  }

  bool GroundHeatExchangerSlinky::setNumberofTrenches(int numberofTrenches) {
    return getImpl<detail::GroundHeatExchangerSlinky_Impl>()->setNumberofTrenches(numberofTrenches);
  }

  void GroundHeatExchangerSlinky::resetNumberofTrenches() {
    getImpl<detail::GroundHeatExchangerSlinky_Impl>()->resetNumberofTrenches();
  }

  double GroundHeatExchangerSlinky::horizontalSpacingBetweenPipes() const {
    return getImpl<detail::GroundHeatExchangerSlinky_Impl>()->horizontalSpacingBetweenPipes();
  }

  bool GroundHeatExchangerSlinky::isHorizontalSpacingBetweenPipesDefaulted() const {
    return getImpl<detail::GroundHeatExchangerSlinky_Impl>()->isHorizontalSpacingBetweenPipesDefaulted();
  }

  bool GroundHeatExchangerSlinky::setHorizontalSpacingBetweenPipes(double horizontalSpacingBetweenPipes) {
    return getImpl<detail::GroundHeatExchangerSlinky_Impl>()->setHorizontalSpacingBetweenPipes(horizontalSpacingBetweenPipes);
  }

  void GroundHeatExchangerSlinky::resetHorizontalSpacingBetweenPipes() {
    getImpl<detail::GroundHeatExchangerSlinky_Impl>()->resetHorizontalSpacingBetweenPipes();
  }

  std::string GroundHeatExchangerSlinky::undisturbedGroundTemperatureModelType() const {
    return getImpl<detail::GroundHeatExchangerSlinky_Impl>()->undisturbedGroundTemperatureModelType();
  }

  bool GroundHeatExchangerSlinky::setUndisturbedGroundTemperatureModelType(const std::string& undisturbedGroundTemperatureModelType) {
    return getImpl<detail::GroundHeatExchangerSlinky_Impl>()->setUndisturbedGroundTemperatureModelType(undisturbedGroundTemperatureModelType);
  }

  boost::optional<double> GroundHeatExchangerSlinky::maximumLengthofSimulation() const {
    return getImpl<detail::GroundHeatExchangerSlinky_Impl>()->maximumLengthofSimulation();
  }

  bool GroundHeatExchangerSlinky::setMaximumLengthofSimulation(double maximumLengthofSimulation) {
    return getImpl<detail::GroundHeatExchangerSlinky_Impl>()->setMaximumLengthofSimulation(maximumLengthofSimulation);
  }

  void GroundHeatExchangerSlinky::resetMaximumLengthofSimulation() {
    getImpl<detail::GroundHeatExchangerSlinky_Impl>()->resetMaximumLengthofSimulation();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double GroundHeatExchangerSlinky_Impl::designFlowRate() const {
      const auto value = getDouble(openstudio::GroundHeatExchanger_SlinkyFields::DesignFlowRate, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatExchangerSlinky_Impl::isDesignFlowRateDefaulted() const {
      return isEmpty(openstudio::GroundHeatExchanger_SlinkyFields::DesignFlowRate);
    }

    bool GroundHeatExchangerSlinky_Impl::setDesignFlowRate(double designFlowRate) {
      const bool result = setDouble(openstudio::GroundHeatExchanger_SlinkyFields::DesignFlowRate, designFlowRate);
      OS_ASSERT(result);
      return result;
    }

    void GroundHeatExchangerSlinky_Impl::resetDesignFlowRate() {
      OS_ASSERT(setString(openstudio::GroundHeatExchanger_SlinkyFields::DesignFlowRate, ""));
    }

    double GroundHeatExchangerSlinky_Impl::soilThermalConductivity() const {
      const auto value = getDouble(openstudio::GroundHeatExchanger_SlinkyFields::SoilThermalConductivity, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatExchangerSlinky_Impl::isSoilThermalConductivityDefaulted() const {
      return isEmpty(openstudio::GroundHeatExchanger_SlinkyFields::SoilThermalConductivity);
    }

    bool GroundHeatExchangerSlinky_Impl::setSoilThermalConductivity(double soilThermalConductivity) {
      const bool result = setDouble(openstudio::GroundHeatExchanger_SlinkyFields::SoilThermalConductivity, soilThermalConductivity);
      OS_ASSERT(result);
      return result;
    }

    void GroundHeatExchangerSlinky_Impl::resetSoilThermalConductivity() {
      OS_ASSERT(setString(openstudio::GroundHeatExchanger_SlinkyFields::SoilThermalConductivity, ""));
    }

    double GroundHeatExchangerSlinky_Impl::soilDensity() const {
      const auto value = getDouble(openstudio::GroundHeatExchanger_SlinkyFields::SoilDensity, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatExchangerSlinky_Impl::isSoilDensityDefaulted() const {
      return isEmpty(openstudio::GroundHeatExchanger_SlinkyFields::SoilDensity);
    }

    bool GroundHeatExchangerSlinky_Impl::setSoilDensity(double soilDensity) {
      const bool result = setDouble(openstudio::GroundHeatExchanger_SlinkyFields::SoilDensity, soilDensity);
      OS_ASSERT(result);
      return result;
    }

    void GroundHeatExchangerSlinky_Impl::resetSoilDensity() {
      OS_ASSERT(setString(openstudio::GroundHeatExchanger_SlinkyFields::SoilDensity, ""));
    }

    double GroundHeatExchangerSlinky_Impl::soilSpecificHeat() const {
      const auto value = getDouble(openstudio::GroundHeatExchanger_SlinkyFields::SoilSpecificHeat, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatExchangerSlinky_Impl::isSoilSpecificHeatDefaulted() const {
      return isEmpty(openstudio::GroundHeatExchanger_SlinkyFields::SoilSpecificHeat);
    }

    bool GroundHeatExchangerSlinky_Impl::setSoilSpecificHeat(double soilSpecificHeat) {
      const bool result = setDouble(openstudio::GroundHeatExchanger_SlinkyFields::SoilSpecificHeat, soilSpecificHeat);
      OS_ASSERT(result);
      return result;
    }

    void GroundHeatExchangerSlinky_Impl::resetSoilSpecificHeat() {
      OS_ASSERT(setString(openstudio::GroundHeatExchanger_SlinkyFields::SoilSpecificHeat, ""));
    }

    double GroundHeatExchangerSlinky_Impl::pipeThermalConductivity() const {
      const auto value = getDouble(openstudio::GroundHeatExchanger_SlinkyFields::PipeThermalConductivity, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatExchangerSlinky_Impl::isPipeThermalConductivityDefaulted() const {
      return isEmpty(openstudio::GroundHeatExchanger_SlinkyFields::PipeThermalConductivity);
    }

    bool GroundHeatExchangerSlinky_Impl::setPipeThermalConductivity(double pipeThermalConductivity) {
      const bool result = setDouble(openstudio::GroundHeatExchanger_SlinkyFields::PipeThermalConductivity, pipeThermalConductivity);
      OS_ASSERT(result);
      return result;
    }

    void GroundHeatExchangerSlinky_Impl::resetPipeThermalConductivity() {
      OS_ASSERT(setString(openstudio::GroundHeatExchanger_SlinkyFields::PipeThermalConductivity, ""));
    }

    double GroundHeatExchangerSlinky_Impl::pipeDensity() const {
      const auto value = getDouble(openstudio::GroundHeatExchanger_SlinkyFields::PipeDensity, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatExchangerSlinky_Impl::isPipeDensityDefaulted() const {
      return isEmpty(openstudio::GroundHeatExchanger_SlinkyFields::PipeDensity);
    }

    bool GroundHeatExchangerSlinky_Impl::setPipeDensity(double pipeDensity) {
      const bool result = setDouble(openstudio::GroundHeatExchanger_SlinkyFields::PipeDensity, pipeDensity);
      OS_ASSERT(result);
      return result;
    }

    void GroundHeatExchangerSlinky_Impl::resetPipeDensity() {
      OS_ASSERT(setString(openstudio::GroundHeatExchanger_SlinkyFields::PipeDensity, ""));
    }

    double GroundHeatExchangerSlinky_Impl::pipeSpecificHeat() const {
      const auto value = getDouble(openstudio::GroundHeatExchanger_SlinkyFields::PipeSpecificHeat, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatExchangerSlinky_Impl::isPipeSpecificHeatDefaulted() const {
      return isEmpty(openstudio::GroundHeatExchanger_SlinkyFields::PipeSpecificHeat);
    }

    bool GroundHeatExchangerSlinky_Impl::setPipeSpecificHeat(double pipeSpecificHeat) {
      const bool result = setDouble(openstudio::GroundHeatExchanger_SlinkyFields::PipeSpecificHeat, pipeSpecificHeat);
      OS_ASSERT(result);
      return result;
    }

    void GroundHeatExchangerSlinky_Impl::resetPipeSpecificHeat() {
      OS_ASSERT(setString(openstudio::GroundHeatExchanger_SlinkyFields::PipeSpecificHeat, ""));
    }

    double GroundHeatExchangerSlinky_Impl::pipeOuterDiameter() const {
      const auto value = getDouble(openstudio::GroundHeatExchanger_SlinkyFields::PipeOuterDiameter, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatExchangerSlinky_Impl::isPipeOuterDiameterDefaulted() const {
      return isEmpty(openstudio::GroundHeatExchanger_SlinkyFields::PipeOuterDiameter);
    }

    bool GroundHeatExchangerSlinky_Impl::setPipeOuterDiameter(double pipeOuterDiameter) {
      const bool result = setDouble(openstudio::GroundHeatExchanger_SlinkyFields::PipeOuterDiameter, pipeOuterDiameter);
      OS_ASSERT(result);
      return result;
    }

    void GroundHeatExchangerSlinky_Impl::resetPipeOuterDiameter() {
      OS_ASSERT(setString(openstudio::GroundHeatExchanger_SlinkyFields::PipeOuterDiameter, ""));
    }

    double GroundHeatExchangerSlinky_Impl::pipeThickness() const {
      const auto value = getDouble(openstudio::GroundHeatExchanger_SlinkyFields::PipeThickness, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatExchangerSlinky_Impl::isPipeThicknessDefaulted() const {
      return isEmpty(openstudio::GroundHeatExchanger_SlinkyFields::PipeThickness);
    }

    bool GroundHeatExchangerSlinky_Impl::setPipeThickness(double pipeThickness) {
      const bool result = setDouble(openstudio::GroundHeatExchanger_SlinkyFields::PipeThickness, pipeThickness);
      OS_ASSERT(result);
      return result;
    }

    void GroundHeatExchangerSlinky_Impl::resetPipeThickness() {
      OS_ASSERT(setString(openstudio::GroundHeatExchanger_SlinkyFields::PipeThickness, ""));
    }

    boost::optional<std::string> GroundHeatExchangerSlinky_Impl::heatExchangerConfiguration() const {
      if (auto value = getString(openstudio::GroundHeatExchanger_SlinkyFields::HeatExchangerConfiguration)) {
        if (!value->empty()) {
          return value;
        }
      }
      return boost::none;
    }

    bool GroundHeatExchangerSlinky_Impl::setHeatExchangerConfiguration(const std::string& heatExchangerConfiguration) {
      const bool result = setString(openstudio::GroundHeatExchanger_SlinkyFields::HeatExchangerConfiguration, heatExchangerConfiguration);
      OS_ASSERT(result);
      return result;
    }

    void GroundHeatExchangerSlinky_Impl::resetHeatExchangerConfiguration() {
      OS_ASSERT(setString(openstudio::GroundHeatExchanger_SlinkyFields::HeatExchangerConfiguration, ""));
    }

    double GroundHeatExchangerSlinky_Impl::coilDiameter() const {
      const auto value = getDouble(openstudio::GroundHeatExchanger_SlinkyFields::CoilDiameter, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatExchangerSlinky_Impl::isCoilDiameterDefaulted() const {
      return isEmpty(openstudio::GroundHeatExchanger_SlinkyFields::CoilDiameter);
    }

    bool GroundHeatExchangerSlinky_Impl::setCoilDiameter(double coilDiameter) {
      const bool result = setDouble(openstudio::GroundHeatExchanger_SlinkyFields::CoilDiameter, coilDiameter);
      OS_ASSERT(result);
      return result;
    }

    void GroundHeatExchangerSlinky_Impl::resetCoilDiameter() {
      OS_ASSERT(setString(openstudio::GroundHeatExchanger_SlinkyFields::CoilDiameter, ""));
    }

    double GroundHeatExchangerSlinky_Impl::coilPitch() const {
      const auto value = getDouble(openstudio::GroundHeatExchanger_SlinkyFields::CoilPitch, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatExchangerSlinky_Impl::isCoilPitchDefaulted() const {
      return isEmpty(openstudio::GroundHeatExchanger_SlinkyFields::CoilPitch);
    }

    bool GroundHeatExchangerSlinky_Impl::setCoilPitch(double coilPitch) {
      const bool result = setDouble(openstudio::GroundHeatExchanger_SlinkyFields::CoilPitch, coilPitch);
      OS_ASSERT(result);
      return result;
    }

    void GroundHeatExchangerSlinky_Impl::resetCoilPitch() {
      OS_ASSERT(setString(openstudio::GroundHeatExchanger_SlinkyFields::CoilPitch, ""));
    }

    double GroundHeatExchangerSlinky_Impl::trenchDepth() const {
      const auto value = getDouble(openstudio::GroundHeatExchanger_SlinkyFields::TrenchDepth, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatExchangerSlinky_Impl::isTrenchDepthDefaulted() const {
      return isEmpty(openstudio::GroundHeatExchanger_SlinkyFields::TrenchDepth);
    }

    bool GroundHeatExchangerSlinky_Impl::setTrenchDepth(double trenchDepth) {
      const bool result = setDouble(openstudio::GroundHeatExchanger_SlinkyFields::TrenchDepth, trenchDepth);
      OS_ASSERT(result);
      return result;
    }

    void GroundHeatExchangerSlinky_Impl::resetTrenchDepth() {
      OS_ASSERT(setString(openstudio::GroundHeatExchanger_SlinkyFields::TrenchDepth, ""));
    }

    double GroundHeatExchangerSlinky_Impl::trenchLength() const {
      const auto value = getDouble(openstudio::GroundHeatExchanger_SlinkyFields::TrenchLength, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatExchangerSlinky_Impl::isTrenchLengthDefaulted() const {
      return isEmpty(openstudio::GroundHeatExchanger_SlinkyFields::TrenchLength);
    }

    bool GroundHeatExchangerSlinky_Impl::setTrenchLength(double trenchLength) {
      const bool result = setDouble(openstudio::GroundHeatExchanger_SlinkyFields::TrenchLength, trenchLength);
      OS_ASSERT(result);
      return result;
    }

    void GroundHeatExchangerSlinky_Impl::resetTrenchLength() {
      OS_ASSERT(setString(openstudio::GroundHeatExchanger_SlinkyFields::TrenchLength, ""));
    }

    int GroundHeatExchangerSlinky_Impl::numberofTrenches() const {
      const auto value = getInt(openstudio::GroundHeatExchanger_SlinkyFields::NumberofTrenches, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatExchangerSlinky_Impl::isNumberofTrenchesDefaulted() const {
      return isEmpty(openstudio::GroundHeatExchanger_SlinkyFields::NumberofTrenches);
    }

    bool GroundHeatExchangerSlinky_Impl::setNumberofTrenches(int numberofTrenches) {
      const bool result = setInt(openstudio::GroundHeatExchanger_SlinkyFields::NumberofTrenches, numberofTrenches);
      OS_ASSERT(result);
      return result;
    }

    void GroundHeatExchangerSlinky_Impl::resetNumberofTrenches() {
      OS_ASSERT(setString(openstudio::GroundHeatExchanger_SlinkyFields::NumberofTrenches, ""));
    }

    double GroundHeatExchangerSlinky_Impl::horizontalSpacingBetweenPipes() const {
      const auto value = getDouble(openstudio::GroundHeatExchanger_SlinkyFields::HorizontalSpacingBetweenPipes, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatExchangerSlinky_Impl::isHorizontalSpacingBetweenPipesDefaulted() const {
      return isEmpty(openstudio::GroundHeatExchanger_SlinkyFields::HorizontalSpacingBetweenPipes);
    }

    bool GroundHeatExchangerSlinky_Impl::setHorizontalSpacingBetweenPipes(double horizontalSpacingBetweenPipes) {
      const bool result = setDouble(openstudio::GroundHeatExchanger_SlinkyFields::HorizontalSpacingBetweenPipes, horizontalSpacingBetweenPipes);
      OS_ASSERT(result);
      return result;
    }

    void GroundHeatExchangerSlinky_Impl::resetHorizontalSpacingBetweenPipes() {
      OS_ASSERT(setString(openstudio::GroundHeatExchanger_SlinkyFields::HorizontalSpacingBetweenPipes, ""));
    }

    std::string GroundHeatExchangerSlinky_Impl::undisturbedGroundTemperatureModelType() const {
      const auto value = getString(openstudio::GroundHeatExchanger_SlinkyFields::UndisturbedGroundTemperatureModelType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatExchangerSlinky_Impl::setUndisturbedGroundTemperatureModelType(const std::string& undisturbedGroundTemperatureModelType) {
      const bool result =
        setString(openstudio::GroundHeatExchanger_SlinkyFields::UndisturbedGroundTemperatureModelType, undisturbedGroundTemperatureModelType);
      OS_ASSERT(result);
      return result;
    }

    boost::optional<double> GroundHeatExchangerSlinky_Impl::maximumLengthofSimulation() const {
      return getDouble(openstudio::GroundHeatExchanger_SlinkyFields::MaximumLengthofSimulation, true);
    }

    bool GroundHeatExchangerSlinky_Impl::setMaximumLengthofSimulation(double maximumLengthofSimulation) {
      const bool result = setDouble(openstudio::GroundHeatExchanger_SlinkyFields::MaximumLengthofSimulation, maximumLengthofSimulation);
      OS_ASSERT(result);
      return result;
    }

    void GroundHeatExchangerSlinky_Impl::resetMaximumLengthofSimulation() {
      OS_ASSERT(setString(openstudio::GroundHeatExchanger_SlinkyFields::MaximumLengthofSimulation, ""));
    }

    std::vector<std::string> GroundHeatExchangerSlinky_Impl::heatExchangerConfigurationValues() const {
      return openstudio::epmodel::GroundHeatExchangerSlinky::heatExchangerConfigurationValues();
    }

    std::vector<std::string> GroundHeatExchangerSlinky_Impl::undisturbedGroundTemperatureModelTypeValues() const {
      return openstudio::epmodel::GroundHeatExchangerSlinky::undisturbedGroundTemperatureModelTypeValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
