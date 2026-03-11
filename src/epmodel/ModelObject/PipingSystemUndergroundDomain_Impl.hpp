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
  double ymax() const;
  double zmax() const;
  int xDirectionMeshDensityParameter() const;
  std::string xDirectionMeshType() const;
  double xDirectionGeometricCoefficient() const;
  int yDirectionMeshDensityParameter() const;
  std::string yDirectionMeshType() const;
  double yDirectionGeometricCoefficient() const;
  int zDirectionMeshDensityParameter() const;
  std::string zDirectionMeshType() const;
  double zDirectionGeometricCoefficient() const;
  double soilThermalConductivity() const;
  double soilDensity() const;
  double soilSpecificHeat() const;
  double soilMoistureContentVolumeFraction() const;
  double soilMoistureContentVolumeFractionatSaturation() const;
  std::string undisturbedGroundTemperatureModelType() const;
  bool thisDomainIncludesBasementSurfaceInteraction() const;
  boost::optional<double> widthofBasementFloorinGroundDomain() const;
  boost::optional<double> depthofBasementWallInGroundDomain() const;
  boost::optional<bool> shiftPipeXCoordinatesByBasementWidth() const;
  double convergenceCriterionfortheOuterCartesianDomainIterationLoop() const;
  int maximumIterationsintheOuterCartesianDomainIterationLoop() const;
  double evapotranspirationGroundCoverParameter() const;
  int numberofPipeCircuitsEnteredforthisDomain() const;

  bool isXDirectionMeshDensityParameterDefaulted() const;
  bool isXDirectionGeometricCoefficientDefaulted() const;
  bool isYDirectionMeshDensityParameterDefaulted() const;
  bool isYDirectionGeometricCoefficientDefaulted() const;
  bool isZDirectionMeshDensityParameterDefaulted() const;
  bool isZDirectionGeometricCoefficientDefaulted() const;
  bool isSoilMoistureContentVolumeFractionDefaulted() const;
  bool isSoilMoistureContentVolumeFractionatSaturationDefaulted() const;
  bool isThisDomainIncludesBasementSurfaceInteractionDefaulted() const;
  bool isConvergenceCriterionfortheOuterCartesianDomainIterationLoopDefaulted() const;
  bool isMaximumIterationsintheOuterCartesianDomainIterationLoopDefaulted() const;
  bool isEvapotranspirationGroundCoverParameterDefaulted() const;

  bool setXmax(double xmax);
  bool setYmax(double ymax);
  bool setZmax(double zmax);
  bool setXDirectionMeshDensityParameter(int xDirectionMeshDensityParameter);
  bool setXDirectionMeshType(const std::string& xDirectionMeshType);
  bool setXDirectionGeometricCoefficient(double xDirectionGeometricCoefficient);
  bool setYDirectionMeshDensityParameter(int yDirectionMeshDensityParameter);
  bool setYDirectionMeshType(const std::string& yDirectionMeshType);
  bool setYDirectionGeometricCoefficient(double yDirectionGeometricCoefficient);
  bool setZDirectionMeshDensityParameter(int zDirectionMeshDensityParameter);
  bool setZDirectionMeshType(const std::string& zDirectionMeshType);
  bool setZDirectionGeometricCoefficient(double zDirectionGeometricCoefficient);
  bool setSoilThermalConductivity(double soilThermalConductivity);
  bool setSoilDensity(double soilDensity);
  bool setSoilSpecificHeat(double soilSpecificHeat);
  bool setSoilMoistureContentVolumeFraction(double soilMoistureContentVolumeFraction);
  bool setSoilMoistureContentVolumeFractionatSaturation(double soilMoistureContentVolumeFractionatSaturation);
  bool setUndisturbedGroundTemperatureModelType(const std::string& undisturbedGroundTemperatureModelType);
  bool setThisDomainIncludesBasementSurfaceInteraction(bool thisDomainIncludesBasementSurfaceInteraction);
  bool setWidthofBasementFloorinGroundDomain(double widthofBasementFloorinGroundDomain);
  bool setDepthofBasementWallInGroundDomain(double depthofBasementWallInGroundDomain);
  bool setShiftPipeXCoordinatesByBasementWidth(boost::optional<bool> shiftPipeXCoordinatesByBasementWidth);
  bool setConvergenceCriterionfortheOuterCartesianDomainIterationLoop(double convergenceCriterionfortheOuterCartesianDomainIterationLoop);
  bool setMaximumIterationsintheOuterCartesianDomainIterationLoop(int maximumIterationsintheOuterCartesianDomainIterationLoop);
  bool setEvapotranspirationGroundCoverParameter(double evapotranspirationGroundCoverParameter);
  bool setNumberofPipeCircuitsEnteredforthisDomain(int numberofPipeCircuitsEnteredforthisDomain);

  void resetXDirectionMeshDensityParameter();
  void resetXDirectionGeometricCoefficient();
  void resetYDirectionMeshDensityParameter();
  void resetYDirectionGeometricCoefficient();
  void resetZDirectionMeshDensityParameter();
  void resetZDirectionGeometricCoefficient();
  void resetSoilMoistureContentVolumeFraction();
  void resetSoilMoistureContentVolumeFractionatSaturation();
  void resetThisDomainIncludesBasementSurfaceInteraction();
  void resetWidthofBasementFloorinGroundDomain();
  void resetDepthofBasementWallInGroundDomain();
  void resetShiftPipeXCoordinatesByBasementWidth();
  void resetConvergenceCriterionfortheOuterCartesianDomainIterationLoop();
  void resetMaximumIterationsintheOuterCartesianDomainIterationLoop();
  void resetEvapotranspirationGroundCoverParameter();

  std::vector<std::string> xDirectionMeshTypeValues() const;
  std::vector<std::string> yDirectionMeshTypeValues() const;
  std::vector<std::string> zDirectionMeshTypeValues() const;
  std::vector<std::string> undisturbedGroundTemperatureModelTypeValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
