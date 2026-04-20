/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_PIPINGSYSTEMUNDERGROUNDDOMAIN_IMPL_HPP
#define EPMODEL_PIPINGSYSTEMUNDERGROUNDDOMAIN_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API PipingSystemUndergroundDomain_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~PipingSystemUndergroundDomain_Impl() override = default;

      double xmax() const;
      bool setXmax(double xmax);

      double ymax() const;
      bool setYmax(double ymax);

      double zmax() const;
      bool setZmax(double zmax);

      int xDirectionMeshDensityParameter() const;
      bool isXDirectionMeshDensityParameterDefaulted() const;
      bool setXDirectionMeshDensityParameter(int xDirectionMeshDensityParameter);
      void resetXDirectionMeshDensityParameter();

      std::string xDirectionMeshType() const;
      bool setXDirectionMeshType(const std::string& xDirectionMeshType);

      double xDirectionGeometricCoefficient() const;
      bool isXDirectionGeometricCoefficientDefaulted() const;
      bool setXDirectionGeometricCoefficient(double xDirectionGeometricCoefficient);
      void resetXDirectionGeometricCoefficient();

      int yDirectionMeshDensityParameter() const;
      bool isYDirectionMeshDensityParameterDefaulted() const;
      bool setYDirectionMeshDensityParameter(int yDirectionMeshDensityParameter);
      void resetYDirectionMeshDensityParameter();

      std::string yDirectionMeshType() const;
      bool setYDirectionMeshType(const std::string& yDirectionMeshType);

      double yDirectionGeometricCoefficient() const;
      bool isYDirectionGeometricCoefficientDefaulted() const;
      bool setYDirectionGeometricCoefficient(double yDirectionGeometricCoefficient);
      void resetYDirectionGeometricCoefficient();

      int zDirectionMeshDensityParameter() const;
      bool isZDirectionMeshDensityParameterDefaulted() const;
      bool setZDirectionMeshDensityParameter(int zDirectionMeshDensityParameter);
      void resetZDirectionMeshDensityParameter();

      std::string zDirectionMeshType() const;
      bool setZDirectionMeshType(const std::string& zDirectionMeshType);

      double zDirectionGeometricCoefficient() const;
      bool isZDirectionGeometricCoefficientDefaulted() const;
      bool setZDirectionGeometricCoefficient(double zDirectionGeometricCoefficient);
      void resetZDirectionGeometricCoefficient();

      double soilThermalConductivity() const;
      bool setSoilThermalConductivity(double soilThermalConductivity);

      double soilDensity() const;
      bool setSoilDensity(double soilDensity);

      double soilSpecificHeat() const;
      bool setSoilSpecificHeat(double soilSpecificHeat);

      double soilMoistureContentVolumeFraction() const;
      bool isSoilMoistureContentVolumeFractionDefaulted() const;
      bool setSoilMoistureContentVolumeFraction(double soilMoistureContentVolumeFraction);
      void resetSoilMoistureContentVolumeFraction();

      double soilMoistureContentVolumeFractionatSaturation() const;
      bool isSoilMoistureContentVolumeFractionatSaturationDefaulted() const;
      bool setSoilMoistureContentVolumeFractionatSaturation(double soilMoistureContentVolumeFractionatSaturation);
      void resetSoilMoistureContentVolumeFractionatSaturation();

      std::string undisturbedGroundTemperatureModelType() const;
      bool setUndisturbedGroundTemperatureModelType(const std::string& undisturbedGroundTemperatureModelType);

      bool thisDomainIncludesBasementSurfaceInteraction() const;
      bool isThisDomainIncludesBasementSurfaceInteractionDefaulted() const;
      bool setThisDomainIncludesBasementSurfaceInteraction(bool thisDomainIncludesBasementSurfaceInteraction);
      void resetThisDomainIncludesBasementSurfaceInteraction();

      boost::optional<double> widthofBasementFloorinGroundDomain() const;
      bool setWidthofBasementFloorinGroundDomain(double widthofBasementFloorinGroundDomain);
      void resetWidthofBasementFloorinGroundDomain();

      boost::optional<double> depthofBasementWallInGroundDomain() const;
      bool setDepthofBasementWallInGroundDomain(double depthofBasementWallInGroundDomain);
      void resetDepthofBasementWallInGroundDomain();

      boost::optional<bool> shiftPipeXCoordinatesByBasementWidth() const;
      bool setShiftPipeXCoordinatesByBasementWidth(boost::optional<bool> shiftPipeXCoordinatesByBasementWidth);
      void resetShiftPipeXCoordinatesByBasementWidth();

      double convergenceCriterionfortheOuterCartesianDomainIterationLoop() const;
      bool isConvergenceCriterionfortheOuterCartesianDomainIterationLoopDefaulted() const;
      bool setConvergenceCriterionfortheOuterCartesianDomainIterationLoop(double convergenceCriterionfortheOuterCartesianDomainIterationLoop);
      void resetConvergenceCriterionfortheOuterCartesianDomainIterationLoop();

      int maximumIterationsintheOuterCartesianDomainIterationLoop() const;
      bool isMaximumIterationsintheOuterCartesianDomainIterationLoopDefaulted() const;
      bool setMaximumIterationsintheOuterCartesianDomainIterationLoop(int maximumIterationsintheOuterCartesianDomainIterationLoop);
      void resetMaximumIterationsintheOuterCartesianDomainIterationLoop();

      double evapotranspirationGroundCoverParameter() const;
      bool isEvapotranspirationGroundCoverParameterDefaulted() const;
      bool setEvapotranspirationGroundCoverParameter(double evapotranspirationGroundCoverParameter);
      void resetEvapotranspirationGroundCoverParameter();

      int numberofPipeCircuitsEnteredforthisDomain() const;
      bool setNumberofPipeCircuitsEnteredforthisDomain(int numberofPipeCircuitsEnteredforthisDomain);

      std::vector<std::string> xDirectionMeshTypeValues() const;
      std::vector<std::string> yDirectionMeshTypeValues() const;
      std::vector<std::string> zDirectionMeshTypeValues() const;
      std::vector<std::string> undisturbedGroundTemperatureModelTypeValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
