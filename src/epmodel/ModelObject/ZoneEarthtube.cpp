/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ZoneEarthtube.hpp"
#include "ZoneEarthtube_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/ZoneEarthtube_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  ZoneEarthtube::ZoneEarthtube(const Model& model) : ModelObject(ZoneEarthtube::iddObjectType(), model) {}

  ZoneEarthtube::ZoneEarthtube(std::shared_ptr<detail::ZoneEarthtube_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType ZoneEarthtube::iddObjectType() {
    return IddObjectType::ZoneEarthtube;
  }

  std::vector<std::string> ZoneEarthtube::earthtubeTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), ZoneEarthtubeFields::EarthtubeType);
  }

  std::vector<std::string> ZoneEarthtube::soilConditionValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), ZoneEarthtubeFields::SoilCondition);
  }

  std::vector<std::string> ZoneEarthtube::earthTubeModelTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), ZoneEarthtubeFields::EarthTubeModelType);
  }

  double ZoneEarthtube::designFlowRate() const {
    return getImpl<detail::ZoneEarthtube_Impl>()->designFlowRate();
  }

  bool ZoneEarthtube::setDesignFlowRate(double designFlowRate) {
    return getImpl<detail::ZoneEarthtube_Impl>()->setDesignFlowRate(designFlowRate);
  }

  double ZoneEarthtube::minimumZoneTemperaturewhenCooling() const {
    return getImpl<detail::ZoneEarthtube_Impl>()->minimumZoneTemperaturewhenCooling();
  }

  bool ZoneEarthtube::setMinimumZoneTemperaturewhenCooling(double minimumZoneTemperaturewhenCooling) {
    return getImpl<detail::ZoneEarthtube_Impl>()->setMinimumZoneTemperaturewhenCooling(minimumZoneTemperaturewhenCooling);
  }

  double ZoneEarthtube::maximumZoneTemperaturewhenHeating() const {
    return getImpl<detail::ZoneEarthtube_Impl>()->maximumZoneTemperaturewhenHeating();
  }

  bool ZoneEarthtube::setMaximumZoneTemperaturewhenHeating(double maximumZoneTemperaturewhenHeating) {
    return getImpl<detail::ZoneEarthtube_Impl>()->setMaximumZoneTemperaturewhenHeating(maximumZoneTemperaturewhenHeating);
  }

  double ZoneEarthtube::deltaTemperature() const {
    return getImpl<detail::ZoneEarthtube_Impl>()->deltaTemperature();
  }

  bool ZoneEarthtube::setDeltaTemperature(double deltaTemperature) {
    return getImpl<detail::ZoneEarthtube_Impl>()->setDeltaTemperature(deltaTemperature);
  }

  std::string ZoneEarthtube::earthtubeType() const {
    return getImpl<detail::ZoneEarthtube_Impl>()->earthtubeType();
  }

  bool ZoneEarthtube::isEarthtubeTypeDefaulted() const {
    return getImpl<detail::ZoneEarthtube_Impl>()->isEarthtubeTypeDefaulted();
  }

  bool ZoneEarthtube::setEarthtubeType(const std::string& earthtubeType) {
    return getImpl<detail::ZoneEarthtube_Impl>()->setEarthtubeType(earthtubeType);
  }

  void ZoneEarthtube::resetEarthtubeType() {
    getImpl<detail::ZoneEarthtube_Impl>()->resetEarthtubeType();
  }

  double ZoneEarthtube::fanPressureRise() const {
    return getImpl<detail::ZoneEarthtube_Impl>()->fanPressureRise();
  }

  bool ZoneEarthtube::isFanPressureRiseDefaulted() const {
    return getImpl<detail::ZoneEarthtube_Impl>()->isFanPressureRiseDefaulted();
  }

  bool ZoneEarthtube::setFanPressureRise(double fanPressureRise) {
    return getImpl<detail::ZoneEarthtube_Impl>()->setFanPressureRise(fanPressureRise);
  }

  void ZoneEarthtube::resetFanPressureRise() {
    getImpl<detail::ZoneEarthtube_Impl>()->resetFanPressureRise();
  }

  double ZoneEarthtube::fanTotalEfficiency() const {
    return getImpl<detail::ZoneEarthtube_Impl>()->fanTotalEfficiency();
  }

  bool ZoneEarthtube::isFanTotalEfficiencyDefaulted() const {
    return getImpl<detail::ZoneEarthtube_Impl>()->isFanTotalEfficiencyDefaulted();
  }

  bool ZoneEarthtube::setFanTotalEfficiency(double fanTotalEfficiency) {
    return getImpl<detail::ZoneEarthtube_Impl>()->setFanTotalEfficiency(fanTotalEfficiency);
  }

  void ZoneEarthtube::resetFanTotalEfficiency() {
    getImpl<detail::ZoneEarthtube_Impl>()->resetFanTotalEfficiency();
  }

  double ZoneEarthtube::pipeRadius() const {
    return getImpl<detail::ZoneEarthtube_Impl>()->pipeRadius();
  }

  bool ZoneEarthtube::isPipeRadiusDefaulted() const {
    return getImpl<detail::ZoneEarthtube_Impl>()->isPipeRadiusDefaulted();
  }

  bool ZoneEarthtube::setPipeRadius(double pipeRadius) {
    return getImpl<detail::ZoneEarthtube_Impl>()->setPipeRadius(pipeRadius);
  }

  void ZoneEarthtube::resetPipeRadius() {
    getImpl<detail::ZoneEarthtube_Impl>()->resetPipeRadius();
  }

  double ZoneEarthtube::pipeThickness() const {
    return getImpl<detail::ZoneEarthtube_Impl>()->pipeThickness();
  }

  bool ZoneEarthtube::isPipeThicknessDefaulted() const {
    return getImpl<detail::ZoneEarthtube_Impl>()->isPipeThicknessDefaulted();
  }

  bool ZoneEarthtube::setPipeThickness(double pipeThickness) {
    return getImpl<detail::ZoneEarthtube_Impl>()->setPipeThickness(pipeThickness);
  }

  void ZoneEarthtube::resetPipeThickness() {
    getImpl<detail::ZoneEarthtube_Impl>()->resetPipeThickness();
  }

  double ZoneEarthtube::pipeLength() const {
    return getImpl<detail::ZoneEarthtube_Impl>()->pipeLength();
  }

  bool ZoneEarthtube::isPipeLengthDefaulted() const {
    return getImpl<detail::ZoneEarthtube_Impl>()->isPipeLengthDefaulted();
  }

  bool ZoneEarthtube::setPipeLength(double pipeLength) {
    return getImpl<detail::ZoneEarthtube_Impl>()->setPipeLength(pipeLength);
  }

  void ZoneEarthtube::resetPipeLength() {
    getImpl<detail::ZoneEarthtube_Impl>()->resetPipeLength();
  }

  double ZoneEarthtube::pipeThermalConductivity() const {
    return getImpl<detail::ZoneEarthtube_Impl>()->pipeThermalConductivity();
  }

  bool ZoneEarthtube::isPipeThermalConductivityDefaulted() const {
    return getImpl<detail::ZoneEarthtube_Impl>()->isPipeThermalConductivityDefaulted();
  }

  bool ZoneEarthtube::setPipeThermalConductivity(double pipeThermalConductivity) {
    return getImpl<detail::ZoneEarthtube_Impl>()->setPipeThermalConductivity(pipeThermalConductivity);
  }

  void ZoneEarthtube::resetPipeThermalConductivity() {
    getImpl<detail::ZoneEarthtube_Impl>()->resetPipeThermalConductivity();
  }

  double ZoneEarthtube::pipeDepthUnderGroundSurface() const {
    return getImpl<detail::ZoneEarthtube_Impl>()->pipeDepthUnderGroundSurface();
  }

  bool ZoneEarthtube::isPipeDepthUnderGroundSurfaceDefaulted() const {
    return getImpl<detail::ZoneEarthtube_Impl>()->isPipeDepthUnderGroundSurfaceDefaulted();
  }

  bool ZoneEarthtube::setPipeDepthUnderGroundSurface(double pipeDepthUnderGroundSurface) {
    return getImpl<detail::ZoneEarthtube_Impl>()->setPipeDepthUnderGroundSurface(pipeDepthUnderGroundSurface);
  }

  void ZoneEarthtube::resetPipeDepthUnderGroundSurface() {
    getImpl<detail::ZoneEarthtube_Impl>()->resetPipeDepthUnderGroundSurface();
  }

  std::string ZoneEarthtube::soilCondition() const {
    return getImpl<detail::ZoneEarthtube_Impl>()->soilCondition();
  }

  bool ZoneEarthtube::isSoilConditionDefaulted() const {
    return getImpl<detail::ZoneEarthtube_Impl>()->isSoilConditionDefaulted();
  }

  bool ZoneEarthtube::setSoilCondition(const std::string& soilCondition) {
    return getImpl<detail::ZoneEarthtube_Impl>()->setSoilCondition(soilCondition);
  }

  void ZoneEarthtube::resetSoilCondition() {
    getImpl<detail::ZoneEarthtube_Impl>()->resetSoilCondition();
  }

  double ZoneEarthtube::averageSoilSurfaceTemperature() const {
    return getImpl<detail::ZoneEarthtube_Impl>()->averageSoilSurfaceTemperature();
  }

  bool ZoneEarthtube::setAverageSoilSurfaceTemperature(double averageSoilSurfaceTemperature) {
    return getImpl<detail::ZoneEarthtube_Impl>()->setAverageSoilSurfaceTemperature(averageSoilSurfaceTemperature);
  }

  double ZoneEarthtube::amplitudeofSoilSurfaceTemperature() const {
    return getImpl<detail::ZoneEarthtube_Impl>()->amplitudeofSoilSurfaceTemperature();
  }

  bool ZoneEarthtube::setAmplitudeofSoilSurfaceTemperature(double amplitudeofSoilSurfaceTemperature) {
    return getImpl<detail::ZoneEarthtube_Impl>()->setAmplitudeofSoilSurfaceTemperature(amplitudeofSoilSurfaceTemperature);
  }

  double ZoneEarthtube::phaseConstantofSoilSurfaceTemperature() const {
    return getImpl<detail::ZoneEarthtube_Impl>()->phaseConstantofSoilSurfaceTemperature();
  }

  bool ZoneEarthtube::setPhaseConstantofSoilSurfaceTemperature(double phaseConstantofSoilSurfaceTemperature) {
    return getImpl<detail::ZoneEarthtube_Impl>()->setPhaseConstantofSoilSurfaceTemperature(phaseConstantofSoilSurfaceTemperature);
  }

  double ZoneEarthtube::constantTermFlowCoefficient() const {
    return getImpl<detail::ZoneEarthtube_Impl>()->constantTermFlowCoefficient();
  }

  bool ZoneEarthtube::isConstantTermFlowCoefficientDefaulted() const {
    return getImpl<detail::ZoneEarthtube_Impl>()->isConstantTermFlowCoefficientDefaulted();
  }

  bool ZoneEarthtube::setConstantTermFlowCoefficient(double constantTermFlowCoefficient) {
    return getImpl<detail::ZoneEarthtube_Impl>()->setConstantTermFlowCoefficient(constantTermFlowCoefficient);
  }

  void ZoneEarthtube::resetConstantTermFlowCoefficient() {
    getImpl<detail::ZoneEarthtube_Impl>()->resetConstantTermFlowCoefficient();
  }

  double ZoneEarthtube::temperatureTermFlowCoefficient() const {
    return getImpl<detail::ZoneEarthtube_Impl>()->temperatureTermFlowCoefficient();
  }

  bool ZoneEarthtube::isTemperatureTermFlowCoefficientDefaulted() const {
    return getImpl<detail::ZoneEarthtube_Impl>()->isTemperatureTermFlowCoefficientDefaulted();
  }

  bool ZoneEarthtube::setTemperatureTermFlowCoefficient(double temperatureTermFlowCoefficient) {
    return getImpl<detail::ZoneEarthtube_Impl>()->setTemperatureTermFlowCoefficient(temperatureTermFlowCoefficient);
  }

  void ZoneEarthtube::resetTemperatureTermFlowCoefficient() {
    getImpl<detail::ZoneEarthtube_Impl>()->resetTemperatureTermFlowCoefficient();
  }

  double ZoneEarthtube::velocityTermFlowCoefficient() const {
    return getImpl<detail::ZoneEarthtube_Impl>()->velocityTermFlowCoefficient();
  }

  bool ZoneEarthtube::isVelocityTermFlowCoefficientDefaulted() const {
    return getImpl<detail::ZoneEarthtube_Impl>()->isVelocityTermFlowCoefficientDefaulted();
  }

  bool ZoneEarthtube::setVelocityTermFlowCoefficient(double velocityTermFlowCoefficient) {
    return getImpl<detail::ZoneEarthtube_Impl>()->setVelocityTermFlowCoefficient(velocityTermFlowCoefficient);
  }

  void ZoneEarthtube::resetVelocityTermFlowCoefficient() {
    getImpl<detail::ZoneEarthtube_Impl>()->resetVelocityTermFlowCoefficient();
  }

  double ZoneEarthtube::velocitySquaredTermFlowCoefficient() const {
    return getImpl<detail::ZoneEarthtube_Impl>()->velocitySquaredTermFlowCoefficient();
  }

  bool ZoneEarthtube::isVelocitySquaredTermFlowCoefficientDefaulted() const {
    return getImpl<detail::ZoneEarthtube_Impl>()->isVelocitySquaredTermFlowCoefficientDefaulted();
  }

  bool ZoneEarthtube::setVelocitySquaredTermFlowCoefficient(double velocitySquaredTermFlowCoefficient) {
    return getImpl<detail::ZoneEarthtube_Impl>()->setVelocitySquaredTermFlowCoefficient(velocitySquaredTermFlowCoefficient);
  }

  void ZoneEarthtube::resetVelocitySquaredTermFlowCoefficient() {
    getImpl<detail::ZoneEarthtube_Impl>()->resetVelocitySquaredTermFlowCoefficient();
  }

  std::string ZoneEarthtube::earthTubeModelType() const {
    return getImpl<detail::ZoneEarthtube_Impl>()->earthTubeModelType();
  }

  bool ZoneEarthtube::isEarthTubeModelTypeDefaulted() const {
    return getImpl<detail::ZoneEarthtube_Impl>()->isEarthTubeModelTypeDefaulted();
  }

  bool ZoneEarthtube::setEarthTubeModelType(const std::string& earthTubeModelType) {
    return getImpl<detail::ZoneEarthtube_Impl>()->setEarthTubeModelType(earthTubeModelType);
  }

  void ZoneEarthtube::resetEarthTubeModelType() {
    getImpl<detail::ZoneEarthtube_Impl>()->resetEarthTubeModelType();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double ZoneEarthtube_Impl::designFlowRate() const {
      const auto value = getDouble(ZoneEarthtubeFields::DesignFlowRate, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneEarthtube_Impl::setDesignFlowRate(double designFlowRate) {
      return setDouble(ZoneEarthtubeFields::DesignFlowRate, designFlowRate);
    }

    double ZoneEarthtube_Impl::minimumZoneTemperaturewhenCooling() const {
      const auto value = getDouble(ZoneEarthtubeFields::MinimumZoneTemperaturewhenCooling, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneEarthtube_Impl::setMinimumZoneTemperaturewhenCooling(double minimumZoneTemperaturewhenCooling) {
      return setDouble(ZoneEarthtubeFields::MinimumZoneTemperaturewhenCooling, minimumZoneTemperaturewhenCooling);
    }

    double ZoneEarthtube_Impl::maximumZoneTemperaturewhenHeating() const {
      const auto value = getDouble(ZoneEarthtubeFields::MaximumZoneTemperaturewhenHeating, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneEarthtube_Impl::setMaximumZoneTemperaturewhenHeating(double maximumZoneTemperaturewhenHeating) {
      return setDouble(ZoneEarthtubeFields::MaximumZoneTemperaturewhenHeating, maximumZoneTemperaturewhenHeating);
    }

    double ZoneEarthtube_Impl::deltaTemperature() const {
      const auto value = getDouble(ZoneEarthtubeFields::DeltaTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneEarthtube_Impl::setDeltaTemperature(double deltaTemperature) {
      return setDouble(ZoneEarthtubeFields::DeltaTemperature, deltaTemperature);
    }

    std::string ZoneEarthtube_Impl::earthtubeType() const {
      if (auto value = getString(ZoneEarthtubeFields::EarthtubeType, false)) {
        if (!value->empty()) {
          return *value;
        }
      }
      return "Natural";
    }

    bool ZoneEarthtube_Impl::isEarthtubeTypeDefaulted() const {
      return isEmpty(ZoneEarthtubeFields::EarthtubeType);
    }

    bool ZoneEarthtube_Impl::setEarthtubeType(const std::string& earthtubeType) {
      return setString(ZoneEarthtubeFields::EarthtubeType, earthtubeType);
    }

    void ZoneEarthtube_Impl::resetEarthtubeType() {
      const bool result = setString(ZoneEarthtubeFields::EarthtubeType, "");
      OS_ASSERT(result);
    }

    double ZoneEarthtube_Impl::fanPressureRise() const {
      if (auto value = getDouble(ZoneEarthtubeFields::FanPressureRise, false)) {
        return *value;
      }
      return 0.0;
    }

    bool ZoneEarthtube_Impl::isFanPressureRiseDefaulted() const {
      return isEmpty(ZoneEarthtubeFields::FanPressureRise);
    }

    bool ZoneEarthtube_Impl::setFanPressureRise(double fanPressureRise) {
      return setDouble(ZoneEarthtubeFields::FanPressureRise, fanPressureRise);
    }

    void ZoneEarthtube_Impl::resetFanPressureRise() {
      const bool result = setString(ZoneEarthtubeFields::FanPressureRise, "");
      OS_ASSERT(result);
    }

    double ZoneEarthtube_Impl::fanTotalEfficiency() const {
      if (auto value = getDouble(ZoneEarthtubeFields::FanTotalEfficiency, false)) {
        return *value;
      }
      return 1.0;
    }

    bool ZoneEarthtube_Impl::isFanTotalEfficiencyDefaulted() const {
      return isEmpty(ZoneEarthtubeFields::FanTotalEfficiency);
    }

    bool ZoneEarthtube_Impl::setFanTotalEfficiency(double fanTotalEfficiency) {
      return setDouble(ZoneEarthtubeFields::FanTotalEfficiency, fanTotalEfficiency);
    }

    void ZoneEarthtube_Impl::resetFanTotalEfficiency() {
      const bool result = setString(ZoneEarthtubeFields::FanTotalEfficiency, "");
      OS_ASSERT(result);
    }

    double ZoneEarthtube_Impl::pipeRadius() const {
      if (auto value = getDouble(ZoneEarthtubeFields::PipeRadius, false)) {
        return *value;
      }
      return 1.0;
    }

    bool ZoneEarthtube_Impl::isPipeRadiusDefaulted() const {
      return isEmpty(ZoneEarthtubeFields::PipeRadius);
    }

    bool ZoneEarthtube_Impl::setPipeRadius(double pipeRadius) {
      return setDouble(ZoneEarthtubeFields::PipeRadius, pipeRadius);
    }

    void ZoneEarthtube_Impl::resetPipeRadius() {
      const bool result = setString(ZoneEarthtubeFields::PipeRadius, "");
      OS_ASSERT(result);
    }

    double ZoneEarthtube_Impl::pipeThickness() const {
      if (auto value = getDouble(ZoneEarthtubeFields::PipeThickness, false)) {
        return *value;
      }
      return 0.2;
    }

    bool ZoneEarthtube_Impl::isPipeThicknessDefaulted() const {
      return isEmpty(ZoneEarthtubeFields::PipeThickness);
    }

    bool ZoneEarthtube_Impl::setPipeThickness(double pipeThickness) {
      return setDouble(ZoneEarthtubeFields::PipeThickness, pipeThickness);
    }

    void ZoneEarthtube_Impl::resetPipeThickness() {
      const bool result = setString(ZoneEarthtubeFields::PipeThickness, "");
      OS_ASSERT(result);
    }

    double ZoneEarthtube_Impl::pipeLength() const {
      if (auto value = getDouble(ZoneEarthtubeFields::PipeLength, false)) {
        return *value;
      }
      return 15.0;
    }

    bool ZoneEarthtube_Impl::isPipeLengthDefaulted() const {
      return isEmpty(ZoneEarthtubeFields::PipeLength);
    }

    bool ZoneEarthtube_Impl::setPipeLength(double pipeLength) {
      return setDouble(ZoneEarthtubeFields::PipeLength, pipeLength);
    }

    void ZoneEarthtube_Impl::resetPipeLength() {
      const bool result = setString(ZoneEarthtubeFields::PipeLength, "");
      OS_ASSERT(result);
    }

    double ZoneEarthtube_Impl::pipeThermalConductivity() const {
      if (auto value = getDouble(ZoneEarthtubeFields::PipeThermalConductivity, false)) {
        return *value;
      }
      return 200.0;
    }

    bool ZoneEarthtube_Impl::isPipeThermalConductivityDefaulted() const {
      return isEmpty(ZoneEarthtubeFields::PipeThermalConductivity);
    }

    bool ZoneEarthtube_Impl::setPipeThermalConductivity(double pipeThermalConductivity) {
      return setDouble(ZoneEarthtubeFields::PipeThermalConductivity, pipeThermalConductivity);
    }

    void ZoneEarthtube_Impl::resetPipeThermalConductivity() {
      const bool result = setString(ZoneEarthtubeFields::PipeThermalConductivity, "");
      OS_ASSERT(result);
    }

    double ZoneEarthtube_Impl::pipeDepthUnderGroundSurface() const {
      if (auto value = getDouble(ZoneEarthtubeFields::PipeDepthUnderGroundSurface, false)) {
        return *value;
      }
      return 3.0;
    }

    bool ZoneEarthtube_Impl::isPipeDepthUnderGroundSurfaceDefaulted() const {
      return isEmpty(ZoneEarthtubeFields::PipeDepthUnderGroundSurface);
    }

    bool ZoneEarthtube_Impl::setPipeDepthUnderGroundSurface(double pipeDepthUnderGroundSurface) {
      return setDouble(ZoneEarthtubeFields::PipeDepthUnderGroundSurface, pipeDepthUnderGroundSurface);
    }

    void ZoneEarthtube_Impl::resetPipeDepthUnderGroundSurface() {
      const bool result = setString(ZoneEarthtubeFields::PipeDepthUnderGroundSurface, "");
      OS_ASSERT(result);
    }

    std::string ZoneEarthtube_Impl::soilCondition() const {
      if (auto value = getString(ZoneEarthtubeFields::SoilCondition, false)) {
        if (!value->empty()) {
          return *value;
        }
      }
      return "HeavyAndDamp";
    }

    bool ZoneEarthtube_Impl::isSoilConditionDefaulted() const {
      return isEmpty(ZoneEarthtubeFields::SoilCondition);
    }

    bool ZoneEarthtube_Impl::setSoilCondition(const std::string& soilCondition) {
      return setString(ZoneEarthtubeFields::SoilCondition, soilCondition);
    }

    void ZoneEarthtube_Impl::resetSoilCondition() {
      const bool result = setString(ZoneEarthtubeFields::SoilCondition, "");
      OS_ASSERT(result);
    }

    double ZoneEarthtube_Impl::averageSoilSurfaceTemperature() const {
      const auto value = getDouble(ZoneEarthtubeFields::AverageSoilSurfaceTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneEarthtube_Impl::setAverageSoilSurfaceTemperature(double averageSoilSurfaceTemperature) {
      const bool result = setDouble(ZoneEarthtubeFields::AverageSoilSurfaceTemperature, averageSoilSurfaceTemperature);
      OS_ASSERT(result);
      return result;
    }

    double ZoneEarthtube_Impl::amplitudeofSoilSurfaceTemperature() const {
      const auto value = getDouble(ZoneEarthtubeFields::AmplitudeofSoilSurfaceTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneEarthtube_Impl::setAmplitudeofSoilSurfaceTemperature(double amplitudeofSoilSurfaceTemperature) {
      return setDouble(ZoneEarthtubeFields::AmplitudeofSoilSurfaceTemperature, amplitudeofSoilSurfaceTemperature);
    }

    double ZoneEarthtube_Impl::phaseConstantofSoilSurfaceTemperature() const {
      const auto value = getDouble(ZoneEarthtubeFields::PhaseConstantofSoilSurfaceTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneEarthtube_Impl::setPhaseConstantofSoilSurfaceTemperature(double phaseConstantofSoilSurfaceTemperature) {
      return setDouble(ZoneEarthtubeFields::PhaseConstantofSoilSurfaceTemperature, phaseConstantofSoilSurfaceTemperature);
    }

    double ZoneEarthtube_Impl::constantTermFlowCoefficient() const {
      if (auto value = getDouble(ZoneEarthtubeFields::ConstantTermFlowCoefficient, false)) {
        return *value;
      }
      return 1.0;
    }

    bool ZoneEarthtube_Impl::isConstantTermFlowCoefficientDefaulted() const {
      return isEmpty(ZoneEarthtubeFields::ConstantTermFlowCoefficient);
    }

    bool ZoneEarthtube_Impl::setConstantTermFlowCoefficient(double constantTermFlowCoefficient) {
      const bool result = setDouble(ZoneEarthtubeFields::ConstantTermFlowCoefficient, constantTermFlowCoefficient);
      OS_ASSERT(result);
      return result;
    }

    void ZoneEarthtube_Impl::resetConstantTermFlowCoefficient() {
      const bool result = setString(ZoneEarthtubeFields::ConstantTermFlowCoefficient, "");
      OS_ASSERT(result);
    }

    double ZoneEarthtube_Impl::temperatureTermFlowCoefficient() const {
      if (auto value = getDouble(ZoneEarthtubeFields::TemperatureTermFlowCoefficient, false)) {
        return *value;
      }
      return 0.0;
    }

    bool ZoneEarthtube_Impl::isTemperatureTermFlowCoefficientDefaulted() const {
      return isEmpty(ZoneEarthtubeFields::TemperatureTermFlowCoefficient);
    }

    bool ZoneEarthtube_Impl::setTemperatureTermFlowCoefficient(double temperatureTermFlowCoefficient) {
      const bool result = setDouble(ZoneEarthtubeFields::TemperatureTermFlowCoefficient, temperatureTermFlowCoefficient);
      OS_ASSERT(result);
      return result;
    }

    void ZoneEarthtube_Impl::resetTemperatureTermFlowCoefficient() {
      const bool result = setString(ZoneEarthtubeFields::TemperatureTermFlowCoefficient, "");
      OS_ASSERT(result);
    }

    double ZoneEarthtube_Impl::velocityTermFlowCoefficient() const {
      if (auto value = getDouble(ZoneEarthtubeFields::VelocityTermFlowCoefficient, false)) {
        return *value;
      }
      return 0.0;
    }

    bool ZoneEarthtube_Impl::isVelocityTermFlowCoefficientDefaulted() const {
      return isEmpty(ZoneEarthtubeFields::VelocityTermFlowCoefficient);
    }

    bool ZoneEarthtube_Impl::setVelocityTermFlowCoefficient(double velocityTermFlowCoefficient) {
      const bool result = setDouble(ZoneEarthtubeFields::VelocityTermFlowCoefficient, velocityTermFlowCoefficient);
      OS_ASSERT(result);
      return result;
    }

    void ZoneEarthtube_Impl::resetVelocityTermFlowCoefficient() {
      const bool result = setString(ZoneEarthtubeFields::VelocityTermFlowCoefficient, "");
      OS_ASSERT(result);
    }

    double ZoneEarthtube_Impl::velocitySquaredTermFlowCoefficient() const {
      if (auto value = getDouble(ZoneEarthtubeFields::VelocitySquaredTermFlowCoefficient, false)) {
        return *value;
      }
      return 0.0;
    }

    bool ZoneEarthtube_Impl::isVelocitySquaredTermFlowCoefficientDefaulted() const {
      return isEmpty(ZoneEarthtubeFields::VelocitySquaredTermFlowCoefficient);
    }

    bool ZoneEarthtube_Impl::setVelocitySquaredTermFlowCoefficient(double velocitySquaredTermFlowCoefficient) {
      const bool result = setDouble(ZoneEarthtubeFields::VelocitySquaredTermFlowCoefficient, velocitySquaredTermFlowCoefficient);
      OS_ASSERT(result);
      return result;
    }

    void ZoneEarthtube_Impl::resetVelocitySquaredTermFlowCoefficient() {
      const bool result = setString(ZoneEarthtubeFields::VelocitySquaredTermFlowCoefficient, "");
      OS_ASSERT(result);
    }

    std::string ZoneEarthtube_Impl::earthTubeModelType() const {
      if (auto value = getString(ZoneEarthtubeFields::EarthTubeModelType, false)) {
        if (!value->empty()) {
          return *value;
        }
      }
      return "Basic";
    }

    bool ZoneEarthtube_Impl::isEarthTubeModelTypeDefaulted() const {
      return isEmpty(ZoneEarthtubeFields::EarthTubeModelType);
    }

    bool ZoneEarthtube_Impl::setEarthTubeModelType(const std::string& earthTubeModelType) {
      return setString(ZoneEarthtubeFields::EarthTubeModelType, earthTubeModelType);
    }

    void ZoneEarthtube_Impl::resetEarthTubeModelType() {
      const bool result = setString(ZoneEarthtubeFields::EarthTubeModelType, "");
      OS_ASSERT(result);
    }

    std::vector<std::string> ZoneEarthtube_Impl::earthtubeTypeValues() const {
      return openstudio::epmodel::ZoneEarthtube::earthtubeTypeValues();
    }

    std::vector<std::string> ZoneEarthtube_Impl::soilConditionValues() const {
      return openstudio::epmodel::ZoneEarthtube::soilConditionValues();
    }

    std::vector<std::string> ZoneEarthtube_Impl::earthTubeModelTypeValues() const {
      return openstudio::epmodel::ZoneEarthtube::earthTubeModelTypeValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
