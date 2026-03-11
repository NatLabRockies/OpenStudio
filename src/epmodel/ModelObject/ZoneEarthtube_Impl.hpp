/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEEARTHTUBE_IMPL_HPP
#define EPMODEL_ZONEEARTHTUBE_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API ZoneEarthtube_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~ZoneEarthtube_Impl() override = default;

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

      std::vector<std::string> earthtubeTypeValues() const;
      std::vector<std::string> soilConditionValues() const;
      std::vector<std::string> earthTubeModelTypeValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
