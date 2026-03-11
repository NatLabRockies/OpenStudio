/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEEARTHTUBE_HPP
#define EPMODEL_ZONEEARTHTUBE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ZoneEarthtube_Impl;
  }

  class EPMODEL_API ZoneEarthtube : public ModelObject
  {
   public:
    explicit ZoneEarthtube(const Model& model);

    virtual ~ZoneEarthtube() override = default;
    ZoneEarthtube(const ZoneEarthtube& other) = default;
    ZoneEarthtube(ZoneEarthtube&& other) = default;
    ZoneEarthtube& operator=(const ZoneEarthtube&) = default;
    ZoneEarthtube& operator=(ZoneEarthtube&&) = default;

    static IddObjectType iddObjectType();
    static std::vector<std::string> earthtubeTypeValues();
    static std::vector<std::string> soilConditionValues();
    static std::vector<std::string> earthTubeModelTypeValues();

    // Schema Alignment Notes:
    // - API: No openstudio::model counterpart exists, so the public API mirrors the ZoneEarthtube IDD entry directly.
    // - Field Mapping: scalar getters/setters map to their EnergyPlus counterparts (Design Flow Rate, temperature thresholds, Earthtube choices, soil/fan/pipe parameters, and flow coefficient terms).
    // - Field Mapping: relationship fields such as Zone Name, Schedule Name, and Earth Tube Model Parameters are intentionally excluded from this scalar-focused pass.
    // - TODO(parity): Add the excluded relationship helpers once scalar coverage is complete.
    double designFlowRate() const;
    bool setDesignFlowRate(double designFlowRate);

    double minimumZoneTemperaturewhenCooling() const;
    bool setMinimumZoneTemperaturewhenCooling(double minimumZoneTemperaturewhenCooling);

    double maximumZoneTemperaturewhenHeating() const;
    bool setMaximumZoneTemperaturewhenHeating(double maximumZoneTemperaturewhenHeating);

    double deltaTemperature() const;
    bool setDeltaTemperature(double deltaTemperature);

    std::string earthtubeType() const;
    bool isEarthtubeTypeDefaulted() const;
    bool setEarthtubeType(const std::string& earthtubeType);
    void resetEarthtubeType();

    double fanPressureRise() const;
    bool isFanPressureRiseDefaulted() const;
    bool setFanPressureRise(double fanPressureRise);
    void resetFanPressureRise();

    double fanTotalEfficiency() const;
    bool isFanTotalEfficiencyDefaulted() const;
    bool setFanTotalEfficiency(double fanTotalEfficiency);
    void resetFanTotalEfficiency();

    double pipeRadius() const;
    bool isPipeRadiusDefaulted() const;
    bool setPipeRadius(double pipeRadius);
    void resetPipeRadius();

    double pipeThickness() const;
    bool isPipeThicknessDefaulted() const;
    bool setPipeThickness(double pipeThickness);
    void resetPipeThickness();

    double pipeLength() const;
    bool isPipeLengthDefaulted() const;
    bool setPipeLength(double pipeLength);
    void resetPipeLength();

    double pipeThermalConductivity() const;
    bool isPipeThermalConductivityDefaulted() const;
    bool setPipeThermalConductivity(double pipeThermalConductivity);
    void resetPipeThermalConductivity();

    double pipeDepthUnderGroundSurface() const;
    bool isPipeDepthUnderGroundSurfaceDefaulted() const;
    bool setPipeDepthUnderGroundSurface(double pipeDepthUnderGroundSurface);
    void resetPipeDepthUnderGroundSurface();

    std::string soilCondition() const;
    bool isSoilConditionDefaulted() const;
    bool setSoilCondition(const std::string& soilCondition);
    void resetSoilCondition();

    double averageSoilSurfaceTemperature() const;
    bool setAverageSoilSurfaceTemperature(double averageSoilSurfaceTemperature);

    double amplitudeofSoilSurfaceTemperature() const;
    bool setAmplitudeofSoilSurfaceTemperature(double amplitudeofSoilSurfaceTemperature);

    double phaseConstantofSoilSurfaceTemperature() const;
    bool setPhaseConstantofSoilSurfaceTemperature(double phaseConstantofSoilSurfaceTemperature);

    double constantTermFlowCoefficient() const;
    bool isConstantTermFlowCoefficientDefaulted() const;
    bool setConstantTermFlowCoefficient(double constantTermFlowCoefficient);
    void resetConstantTermFlowCoefficient();

    double temperatureTermFlowCoefficient() const;
    bool isTemperatureTermFlowCoefficientDefaulted() const;
    bool setTemperatureTermFlowCoefficient(double temperatureTermFlowCoefficient);
    void resetTemperatureTermFlowCoefficient();

    double velocityTermFlowCoefficient() const;
    bool isVelocityTermFlowCoefficientDefaulted() const;
    bool setVelocityTermFlowCoefficient(double velocityTermFlowCoefficient);
    void resetVelocityTermFlowCoefficient();

    double velocitySquaredTermFlowCoefficient() const;
    bool isVelocitySquaredTermFlowCoefficientDefaulted() const;
    bool setVelocitySquaredTermFlowCoefficient(double velocitySquaredTermFlowCoefficient);
    void resetVelocitySquaredTermFlowCoefficient();

    std::string earthTubeModelType() const;
    bool isEarthTubeModelTypeDefaulted() const;
    bool setEarthTubeModelType(const std::string& earthTubeModelType);
    void resetEarthTubeModelType();

   protected:
    using ImplType = detail::ZoneEarthtube_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ZoneEarthtube(std::shared_ptr<detail::ZoneEarthtube_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
