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
      bool setEarthtubeType(const std::string& earthtubeType);
      bool isEarthtubeTypeDefaulted() const;
      void resetEarthtubeType();

      double fanPressureRise() const;
      bool setFanPressureRise(double fanPressureRise);
      bool isFanPressureRiseDefaulted() const;
      void resetFanPressureRise();

      double fanTotalEfficiency() const;
      bool setFanTotalEfficiency(double fanTotalEfficiency);
      bool isFanTotalEfficiencyDefaulted() const;
      void resetFanTotalEfficiency();

      double pipeRadius() const;
      bool setPipeRadius(double pipeRadius);
      bool isPipeRadiusDefaulted() const;
      void resetPipeRadius();

      double pipeThickness() const;
      bool setPipeThickness(double pipeThickness);
      bool isPipeThicknessDefaulted() const;
      void resetPipeThickness();

      double pipeLength() const;
      bool setPipeLength(double pipeLength);
      bool isPipeLengthDefaulted() const;
      void resetPipeLength();

      double pipeThermalConductivity() const;
      bool setPipeThermalConductivity(double pipeThermalConductivity);
      bool isPipeThermalConductivityDefaulted() const;
      void resetPipeThermalConductivity();

      double pipeDepthUnderGroundSurface() const;
      bool setPipeDepthUnderGroundSurface(double pipeDepthUnderGroundSurface);
      bool isPipeDepthUnderGroundSurfaceDefaulted() const;
      void resetPipeDepthUnderGroundSurface();

      std::string soilCondition() const;
      bool setSoilCondition(const std::string& soilCondition);
      bool isSoilConditionDefaulted() const;
      void resetSoilCondition();

      double averageSoilSurfaceTemperature() const;
      bool setAverageSoilSurfaceTemperature(double averageSoilSurfaceTemperature);

      double amplitudeofSoilSurfaceTemperature() const;
      bool setAmplitudeofSoilSurfaceTemperature(double amplitudeofSoilSurfaceTemperature);

      double phaseConstantofSoilSurfaceTemperature() const;
      bool setPhaseConstantofSoilSurfaceTemperature(double phaseConstantofSoilSurfaceTemperature);

      double constantTermFlowCoefficient() const;
      bool setConstantTermFlowCoefficient(double constantTermFlowCoefficient);
      bool isConstantTermFlowCoefficientDefaulted() const;
      void resetConstantTermFlowCoefficient();

      double temperatureTermFlowCoefficient() const;
      bool setTemperatureTermFlowCoefficient(double temperatureTermFlowCoefficient);
      bool isTemperatureTermFlowCoefficientDefaulted() const;
      void resetTemperatureTermFlowCoefficient();

      double velocityTermFlowCoefficient() const;
      bool setVelocityTermFlowCoefficient(double velocityTermFlowCoefficient);
      bool isVelocityTermFlowCoefficientDefaulted() const;
      void resetVelocityTermFlowCoefficient();

      double velocitySquaredTermFlowCoefficient() const;
      bool setVelocitySquaredTermFlowCoefficient(double velocitySquaredTermFlowCoefficient);
      bool isVelocitySquaredTermFlowCoefficientDefaulted() const;
      void resetVelocitySquaredTermFlowCoefficient();

      std::string earthTubeModelType() const;
      bool setEarthTubeModelType(const std::string& earthTubeModelType);
      bool isEarthTubeModelTypeDefaulted() const;
      void resetEarthTubeModelType();

      std::vector<std::string> earthtubeTypeValues() const;
      std::vector<std::string> soilConditionValues() const;
      std::vector<std::string> earthTubeModelTypeValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
